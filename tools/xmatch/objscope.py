"""Object-scoped pairing, the last phase of match.py (docs/xmatch.md).

The module map (work/migrate/modmap.json, tools/migrate/modmap.py) places most retail functions in a dev object. Inside one
object the candidates for an unmatched retail function are the object's few hundred unmatched dev functions instead
of all 145,000, so evidence that is too weak binary-wide decides here: matched callees and callers that correspond,
shared tokens (strings, constants, imports, constant-pool values), similar size and call count. Function order is
not used: inside an object, retail and dev order differ.

A pair is kept when it is the best for both functions, by at least `MARGIN` over the runner-up on each side, with a
score of at least `MIN_SCORE`; new pairs feed the next round. Only high-confidence pairs count as evidence, and a
lower-confidence pair (caller-*) on either function gives way.
"""
import collections, json, math, re

MIN_CONF = 0.7      # modmap tiers below this (library 0.3, vote tiers 0.4-0.5) are too unsure to scope by
MIN_SCORE = 2.0
MARGIN = 1.0
ROUNDS = 8


def norm_module(path):
    """dev PDB module path -> modmap module name (`SPBake/SPEditorBlock.obj`)."""
    return re.split(r"DebugRelease(?:_CrossDependent)?\\", path)[-1].replace("\\", "/")


def run(dev, ret, r2d, d2r, how, dev_modules, modmap_path, high, log):
    """Adds pairs to r2d/d2r/how in place (how = "object-scoped"); returns how many."""
    mm = json.load(open(modmap_path))["functions"]
    rmod = {v: r["module"] for v, r in mm.items() if (r.get("confidence") or 0) >= MIN_CONF and v in ret}
    dmod = {d: norm_module(m) for d, m in dev_modules.items() if d in dev}
    ev = {r: d for r, d in r2d.items() if how[r] in high}        # evidence: high-confidence pairs only
    ev_d = {d: r for r, d in ev.items()}

    def feats(f):
        return set(["s:" + s for s in f.get("strs", ())] + ["c:%x" % c for c in f.get("consts", ())] +
                   ["i:" + i for i in f.get("imps", ())] + ["v:%x" % v for v in f.get("vals", ())])
    F = {("r", va): feats(f) for va, f in ret.items()}
    F.update({("d", va): feats(f) for va, f in dev.items()})
    rcallers, dcallers = collections.defaultdict(set), collections.defaultdict(set)
    for side, cl in ((ret, rcallers), (dev, dcallers)):
        for va, f in side.items():
            for c in set(f["calls"]):
                cl[c].add(va)
    dindeg = collections.Counter(c for f in dev.values() for c in set(f["calls"]))
    tokfreq = collections.Counter(t for (s, _), fs in F.items() if s == "d" for t in fs)
    dcalls = {va: set(f["calls"]) for va, f in dev.items()}
    by_obj_d = collections.defaultdict(list)
    for d, m in sorted(dmod.items()):
        by_obj_d[m].append(d)

    def score(x, y):
        a, b = ret[x]["size"], dev[y]["size"]
        if a <= 0 or b <= 0:
            return None
        lr = abs(math.log(a / b))
        if lr > math.log(3.0):
            return None
        s = 0.0
        for c in set(ret[x]["calls"]):                       # matched callees that correspond
            dc = ev.get(c)
            if dc and dc in dcalls[y]:
                s += 2.0 if dindeg[dc] < 40 else 0.3         # hubs (operator new, atexit) say little
        for c in rcallers[x]:                                # matched callers that correspond
            dc = ev.get(c)
            if dc and dc in dcallers[y]:
                s += 2.0
        fr, fd = F[("r", x)], F[("d", y)]
        sh = fr & fd
        s += sum(1.5 if tokfreq[t] < 20 else 0.3 for t in sh)
        if fr and fd and not sh and len(fr) > 2 and len(fd) > 2:
            s -= 2.0                                         # both have tokens, none shared
        nr, nd = len(set(ret[x]["calls"])), len(dcalls[y])
        s -= 2.0 * abs(nr - nd) / max(1, nr, nd)
        s -= 1.5 * lr
        return s

    total = 0
    for rnd in range(ROUNDS):
        by_obj_r = collections.defaultdict(list)
        for x in sorted(rmod):
            if x not in ev:
                by_obj_r[rmod[x]].append(x)
        new = []
        for obj, R in sorted(by_obj_r.items()):
            D = [y for y in by_obj_d.get(obj, ()) if y not in ev_d]
            if not D:
                continue
            best_r, best_d = collections.defaultdict(list), collections.defaultdict(list)
            for x in R:
                for y in D:
                    s = score(x, y)
                    if s is not None:
                        best_r[x].append((s, y)); best_d[y].append((s, x))
            for x, L in sorted(best_r.items()):
                L.sort(reverse=True)
                s1, y = L[0]
                if s1 < MIN_SCORE or (len(L) > 1 and s1 - L[1][0] < MARGIN):
                    continue
                M = sorted(best_d[y], reverse=True)
                if M[0][1] != x or (len(M) > 1 and M[0][0] - M[1][0] < MARGIN):
                    continue
                new.append((x, y))
        for x, y in new:
            if x in ev or y in ev_d:
                continue
            for z in {x, d2r.get(y)} - {None}:              # a weaker pair on either function gives way
                if z in r2d:
                    d2r.pop(r2d.pop(z), None); how.pop(z, None)
            r2d[x], d2r[y], how[x] = y, x, "object-scoped"
            ev[x], ev_d[y] = y, x
        total += len(new)
        log("  object-scoped round %d: +%d" % (rnd + 1, len(new)))
        if not new:
            break
    return total
