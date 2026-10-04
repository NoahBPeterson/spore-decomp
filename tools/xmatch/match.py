#!/usr/bin/env python3
"""Match dev-build functions (with PDB names) to retail functions.

usage: match.py <dev.json> <retail.json> <out.json> [<dev symbols.json> [<tables.json>]]
  symbols.json enables module-aware gap alignment; tables.json (tools/xmatch/tables.py) enables the
  initializer-table and vtable phases.
1. Anchors: a token (string literal, distinctive constant) that occurs in exactly one function on each
   side pairs them; so does an identical, unique-on-both-sides string set. Pairs supported by
   conflicting anchors are dropped.
2. Propagation (to a fixpoint): for every matched pair, the unmatched direct callees (and callers)
   are paired when exactly one candidate remains on each side, or when a candidate pair is the
   only one with compatible features (shared strings/constants/imports) among the unmatched.
3. Gap alignment (Needleman-Wunsch between matched neighbours of one dev module), evidence-gated.
4. Table alignment: the dynamic-initializer tables (xcu-align) and paired vtables (vtable-slot) are
   ordered lists on both sides; matched entries anchor them and the entries between anchors are aligned
   the same way. Vtables are paired by votes from already-matched slots at the same index.
Output: {retail_va: {dev_va, name, how}} plus counts; vtable pairs in <out>_vtables.json.
"""
import collections, functools, json, sys


def main(devp, retp, outp):
    dev, ret = json.load(open(devp)), json.load(open(retp))
    for side in (dev, ret):  # sets once, not per comparison
        for f in side.values():
            for k in ("strs", "consts", "imps", "vals"):
                f["S" + k] = frozenset(f.get(k, ()))
            f["Scalls"] = frozenset(f["calls"])

    def tokens(f):
        return ["s:" + s for s in f["strs"]] + ["c:%x" % c for c in f["consts"]]

    def index(side):
        idx = collections.defaultdict(set)
        for va, f in side.items():
            for t in tokens(f):
                idx[t].add(va)
        return idx

    di, ri = index(dev), index(ret)
    votes = collections.defaultdict(lambda: collections.Counter())
    for t, rs in ri.items():
        ds = di.get(t)
        if ds and len(ds) == 1 and len(rs) == 1:
            votes[next(iter(rs))][next(iter(ds))] += 1
    # unique identical string sets
    def setidx(side):
        m = collections.defaultdict(list)
        for va, f in side.items():
            if len(f["strs"]) >= 2:
                m[tuple(f["strs"])].append(va)
        return m
    ds_, rs_ = setidx(dev), setidx(ret)
    for k, rl in rs_.items():
        dl = ds_.get(k)
        if dl and len(dl) == 1 and len(rl) == 1:
            votes[rl[0]][dl[0]] += 2

    r2d, d2r, how = {}, {}, {}
    # accept unambiguous anchors; resolve one-to-many by vote majority with margin
    cand = []
    for r, c in votes.items():
        (d, v), *rest = c.most_common()
        if not rest or v >= 2 * rest[0][1]:
            cand.append((v, r, d))
    cand.sort(reverse=True)
    for v, r, d in cand:
        if r not in r2d and d not in d2r:
            r2d[r], d2r[d], how[r] = d, r, "anchor"
    anchors = len(r2d)
    import os, random
    holdout = {}
    frac = float(os.environ.get("XMATCH_HOLDOUT", "0"))
    if frac > 0:
        rnd = random.Random(1)
        for r in sorted(r2d):
            if rnd.random() < frac:
                holdout[r] = r2d.pop(r); d2r.pop(holdout[r]); how.pop(r)

    # call graph (callees + callers)
    def graph(side):
        callees = {va: [c for c in f["calls"] if c in side] for va, f in side.items()}
        callers = collections.defaultdict(list)
        for va, cs in callees.items():
            for c in cs:
                callers[c].append(va)
        return callees, callers
    dce, dcr = graph(dev)
    rce, rcr = graph(ret)

    @functools.lru_cache(maxsize=4_000_000)
    def compatible(r, d):
        fr, fd = ret[r], dev[d]
        sr, sd = fr["Sstrs"], fd["Sstrs"]
        if sr and sd and not (sr & sd):
            return False
        cr, cd = fr["Sconsts"], fd["Sconsts"]
        if cr and cd and not (cr & cd) and len(cr) > 2 and len(cd) > 2:
            return False
        if fr["Simps"] and fd["Simps"] and not (fr["Simps"] & fd["Simps"]):
            return False
        return True

    def score(r, d):
        fr, fd = ret[r], dev[d]
        return (len(fr["Sstrs"] & fd["Sstrs"]) * 3 + len(fr["Sconsts"] & fd["Sconsts"]) * 2 +
                len(fr["Simps"] & fd["Simps"]))

    import bisect, math
    syms = json.load(open(sys.argv[4])) if len(sys.argv) > 4 else None
    dmod = {}
    if syms:
        for f in syms["functions"]:
            dmod.setdefault("%08x" % f["va"], f["module"])
    dsorted = sorted(dev)
    rsorted = sorted(ret)

    def evidence(x, y):
        fr, fd = ret[x], dev[y]
        nr, nd = len(fr["Scalls"]), len(fd["Scalls"])
        if abs(nr - nd) > max(1, 0.2 * max(nr, nd)):
            return False
        if fr["Sstrs"] & fd["Sstrs"] or fr["Sconsts"] & fd["Sconsts"] or fr["Simps"] & fd["Simps"]:
            return True
        dcalls = fd["Scalls"]
        return any(r2d.get(c) in dcalls for c in fr["Scalls"])

    def vals_shared(x, y):
        return bool(ret[x]["Svals"] & dev[y]["Svals"])

    dindeg = collections.Counter(c for f in dev.values() for c in set(f["calls"]))

    def specific(x, y):
        """evidence() without the call-graph shortcut through ubiquitous callees (atexit, operator new)."""
        fr, fd = ret[x], dev[y]
        nr, nd = len(fr["Scalls"]), len(fd["Scalls"])
        if abs(nr - nd) > max(1, 0.2 * max(nr, nd)):
            return False
        if fr["Sstrs"] & fd["Sstrs"] or fr["Sconsts"] & fd["Sconsts"] or vals_shared(x, y) or fr["Simps"] & fd["Simps"]:
            return True
        dcalls = fd["Scalls"]
        return any(r2d.get(c) in dcalls and dindeg[r2d[c]] < 40 for c in fr["Scalls"])

    def sizeok(x, y, lim=1.8):
        a, b = ret[x]["size"], dev[y]["size"]
        return a > 0 and b > 0 and abs(math.log(a / b)) < math.log(lim)

    def align(R, D, tag, positional):
        """Align two ordered lists. Anchors: entries already matched to each other (longest increasing
        chain). Gaps of equal length are paired position-by-position when `positional` (vtables);
        otherwise gaps are DP-aligned and every pair must pass specific()."""
        dpos = collections.defaultdict(list)
        for j, y in enumerate(D):
            dpos[y].append(j)
        pairs = sorted((i, j) for i, x in enumerate(R) if x in r2d for j in dpos.get(r2d[x], ()))
        # longest chain strictly increasing in both i and j (patience LIS over j, ties by i)
        tails, tidx, prev = [], [], [-1] * len(pairs)
        for k, (i, j) in enumerate(pairs):
            lo = bisect.bisect_left(tails, j)
            while lo > 0 and pairs[tidx[lo - 1]][0] == i:  # one anchor per i
                lo -= 1
            if lo == len(tails):
                tails.append(j); tidx.append(k)
            else:
                tails[lo], tidx[lo] = j, k
            prev[k] = tidx[lo - 1] if lo else -1
        chain, k = [], tidx[-1] if tidx else -1
        while k >= 0:
            chain.append(pairs[k]); k = prev[k]
        chain = [(-1, -1)] + chain[::-1] + [(len(R), len(D))]
        added = 0
        for (i1, j1), (i2, j2) in zip(chain, chain[1:]):
            GR, GD = R[i1 + 1:i2], D[j1 + 1:j2]
            if not GR or not GD:
                continue
            if positional and len(GR) == len(GD):
                for x, y in zip(GR, GD):
                    if x in ret and y in dev and x not in r2d and y not in d2r and compatible(x, y) and sizeok(x, y, 2.5):
                        r2d[x], d2r[y], how[x] = y, x, tag; added += 1
                continue
            GR = [x for x in GR if x in ret and x not in r2d]
            GD = [y for y in GD if y in dev and y not in d2r]
            if not GR or not GD or len(GR) > 200 or len(GD) > 300:
                continue
            n, mm, INF = len(GR), len(GD), 1e9
            pc = lambda x, y: (abs(math.log(ret[x]["size"] / dev[y]["size"]))
                               if ret[x]["size"] > 0 and dev[y]["size"] > 0 and compatible(x, y) and sizeok(x, y, 2.5) else INF)
            dp = [[0.0] * (mm + 1) for _ in range(n + 1)]
            bt = [[0] * (mm + 1) for _ in range(n + 1)]
            for i in range(1, n + 1):
                dp[i][0], bt[i][0] = dp[i - 1][0] + 1.2, 1
            for j in range(1, mm + 1):
                dp[0][j], bt[0][j] = dp[0][j - 1] + 0.9, 2
            for i in range(1, n + 1):
                for j in range(1, mm + 1):
                    best, b = dp[i - 1][j - 1] + pc(GR[i - 1], GD[j - 1]), 0
                    if dp[i - 1][j] + 1.2 < best: best, b = dp[i - 1][j] + 1.2, 1
                    if dp[i][j - 1] + 0.9 < best: best, b = dp[i][j - 1] + 0.9, 2
                    dp[i][j], bt[i][j] = best, b
            i, j = n, mm
            while i > 0 and j > 0:
                b = bt[i][j]
                if b == 0:
                    x, y = GR[i - 1], GD[j - 1]
                    if pc(x, y) < math.log(1.8) and x not in r2d and y not in d2r and specific(x, y):
                        r2d[x], d2r[y], how[x] = y, x, tag; added += 1
                    i, j = i - 1, j - 1
                elif b == 1:
                    i -= 1
                else:
                    j -= 1
        return added

    tables = json.load(open(sys.argv[5])) if len(sys.argv) > 5 else None
    vtpairs = {}
    if tables:
        dvt_of = collections.defaultdict(list)  # (dev fn, slot index) -> dev vtables
        for dva, t in tables["dev_vt"].items():
            for i, y in enumerate(t["slots"]):
                dvt_of[(y, i)].append(dva)
        dvt_count = collections.Counter(y for t in tables["dev_vt"].values() for y in set(t["slots"]))

    def table_anchors(R, D, tag):
        """Tokens (string, constant, constant-pool value) unique within both lists pair their entries,
        even when the token occurs elsewhere in the binary."""
        def idx(L, side):
            m = collections.defaultdict(set)
            for x in L:
                if x in side:
                    f = side[x]
                    for t in ["s:" + v for v in f["strs"]] + ["c:%x" % v for v in f["consts"]] + ["v:%x" % v for v in f["vals"]]:
                        m[t].add(x)
            return m
        ri, di = idx(R, ret), idx(D, dev)
        votes = collections.defaultdict(collections.Counter)
        for t, rs in ri.items():
            ds = di.get(t)
            if ds and len(ds) == 1 and len(rs) == 1:
                votes[next(iter(rs))][next(iter(ds))] += 1
        added = 0
        for x, c in votes.items():
            (y, n), *rest = c.most_common()
            if not rest and x not in r2d and y not in d2r and compatible(x, y) and sizeok(x, y, 6):  # retail inlines more
                r2d[x], d2r[y], how[x] = y, x, tag; added += 1
        return added

    def tablefill():
        added = 0
        if not vtpairs:  # first visit
            added += table_anchors(tables["ret_xcu"], tables["dev_xcu"], "xcu-anchor")
        added += align(tables["ret_xcu"], tables["dev_xcu"], "xcu-align", False)
        # pair vtables: votes from matched slots at the same index; slots shared by many vtables
        # (base-class methods, _purecall) don't vote
        cands = []
        for rva, slots in tables["ret_vt"].items():
            if rva in vtpairs:
                continue
            v = collections.Counter()
            for i, x in enumerate(slots):
                y = r2d.get(x)
                if y and dvt_count[y] <= 3:
                    for dva in dvt_of.get((y, i), ()):
                        v[dva] += 1
            if v:
                (d, n), *rest = v.most_common()
                if n >= 2 and (not rest or n >= 2 * rest[0][1]):
                    cands.append((n, rva, d))
        taken = set(vtpairs.values())
        for n, rva, d in sorted(cands, reverse=True):
            if d not in taken and rva not in vtpairs:
                vtpairs[rva] = d; taken.add(d)
        for rva, d in vtpairs.items():
            added += align(tables["ret_vt"][rva], tables["dev_vt"][d]["slots"], "vtable-slot", True)
        return added

    def gapfill():
        added = 0
        pairs = sorted((int(r, 16), int(d, 16)) for r, d in r2d.items())
        for (r1, d1), (r2, d2) in zip(pairs, pairs[1:]):
            if d2 <= d1 or dmod.get("%08x" % d1) != dmod.get("%08x" % d2):
                continue
            R = [x for x in rsorted[bisect.bisect_right(rsorted, "%08x" % r1):bisect.bisect_left(rsorted, "%08x" % r2)] if x not in r2d]
            D = [x for x in dsorted[bisect.bisect_right(dsorted, "%08x" % d1):bisect.bisect_left(dsorted, "%08x" % d2)]
                 if x not in d2r and dmod.get(x) == dmod.get("%08x" % d1)]
            if not R or not D or len(R) > 150 or len(D) > 300:
                continue
            INF = 1e9
            def pc(x, y):
                a, b = ret[x]["size"], dev[y]["size"]
                if a <= 0 or b <= 0 or not compatible(x, y):
                    return INF
                lr = abs(math.log(a / b))
                return lr if lr < math.log(2.5) else INF
            def skd(y):
                return 0.25 if dev[y]["size"] < 48 else 0.9
            SKR = 1.2
            n, mm = len(R), len(D)
            dp = [[0.0] * (mm + 1) for _ in range(n + 1)]
            bt = [[0] * (mm + 1) for _ in range(n + 1)]
            for i in range(1, n + 1):
                dp[i][0] = dp[i - 1][0] + SKR; bt[i][0] = 1
            for j in range(1, mm + 1):
                dp[0][j] = dp[0][j - 1] + skd(D[j - 1]); bt[0][j] = 2
            for i in range(1, n + 1):
                for j in range(1, mm + 1):
                    best, b = dp[i - 1][j - 1] + pc(R[i - 1], D[j - 1]), 0
                    v = dp[i - 1][j] + SKR
                    if v < best: best, b = v, 1
                    v = dp[i][j - 1] + skd(D[j - 1])
                    if v < best: best, b = v, 2
                    dp[i][j], bt[i][j] = best, b
            i, j = n, mm
            while i > 0 and j > 0:
                b = bt[i][j]
                if b == 0:
                    x, y = R[i - 1], D[j - 1]
                    if pc(x, y) < math.log(1.8) and x not in r2d and y not in d2r and evidence(x, y):
                        r2d[x], d2r[y], how[x] = y, x, "gap-align"; added += 1
                    i, j = i - 1, j - 1
                elif b == 1:
                    i -= 1
                else:
                    j -= 1
        return added

    # worklist: only pairs whose call-graph neighbourhood gained a match since they were last visited
    changed, rounds, seen = True, 0, 0
    dirty, seen = set(r2d), len(r2d)
    while changed and rounds < 200:
        changed, rounds = False, rounds + 1
        for r in sorted(dirty):  # sorted: deterministic regardless of PYTHONHASHSEED
            d = r2d[r]
            for rel_r, rel_d, tag in ((rce, dce, "callee"), (rcr, dcr, "caller")):
                ur = list(dict.fromkeys(x for x in rel_r.get(r, []) if x not in r2d))
                ud = list(dict.fromkeys(x for x in rel_d.get(d, []) if x not in d2r))
                if not ur or not ud:
                    continue
                if len(ur) == 1 and len(ud) == 1:
                    if compatible(ur[0], ud[0]):
                        r2d[ur[0]], d2r[ud[0]], how[ur[0]] = ud[0], ur[0], tag + "-single"
                        changed = True
                    continue
                if len(ur) * len(ud) > 40000:  # hub (operator new, atexit): too ambiguous, too slow
                    continue
                for x in ur:
                    scored = sorted(((score(x, y), y) for y in ud if compatible(x, y)), reverse=True)
                    if scored and scored[0][0] > 0 and (len(scored) == 1 or scored[0][0] > scored[1][0]):
                        y = scored[0][1]
                        if y not in d2r and x not in r2d:
                            r2d[x], d2r[y], how[x] = y, x, tag + "-scored"
                            changed = True
                            ud = [z for z in ud if z != y]
        print("round %d: %d matched (visited %d)" % (rounds, len(r2d), len(dirty)), file=sys.stderr, flush=True)
        if not changed and syms:
            if gapfill():
                changed = True
            print("  gapfill -> %d" % len(r2d), file=sys.stderr, flush=True)
        if not changed and tables:
            if tablefill():
                changed = True
            print("  tablefill -> %d (vtables paired %d)" % (len(r2d), len(vtpairs)), file=sys.stderr, flush=True)
        keys = list(r2d)
        new, seen = keys[seen:], len(keys)
        dirty = set(new)
        for x in new:
            dirty.update(y for y in rce.get(x, ()) if y in r2d)
            dirty.update(y for y in rcr.get(x, ()) if y in r2d)
    if holdout:
        res = collections.defaultdict(lambda: [0, 0, 0])
        for r, d in holdout.items():
            if r not in r2d:
                res["(not recovered)"][2] += 1
            else:
                res[how[r]][0 if r2d[r] == d else 1] += 1
        print("HOLD-OUT (%d hidden anchors): correct / wrong per method:" % len(holdout))
        for k, (c, w, n) in sorted(res.items()):
            print("  %-16s correct %4d wrong %4d%s" % (k, c, w, ("  not recovered %d" % n) if n else ""))
    out = {r: {"dev": d, "name": dev[d]["name"], "how": how[r]} for r, d in r2d.items()}
    json.dump(out, open(outp, "w"))
    if tables:
        json.dump({r: {"dev": d, "name": tables["dev_vt"][d]["name"]} for r, d in vtpairs.items()},
                  open(outp.rsplit(".", 1)[0] + "_vtables.json", "w"))
        print("vtables paired: %d of %d retail" % (len(vtpairs), len(tables["ret_vt"])))
    c = collections.Counter(how.values())
    print("matched %d of %d retail functions (anchors %d, propagation rounds %d): %s" % (
        len(out), len(ret), anchors, rounds, dict(c)))


if __name__ == "__main__":
    main(*sys.argv[1:4])  # argv[4], argv[5] read inside
