#!/usr/bin/env python3
"""Match dev-build functions (with PDB names) to retail functions.

usage: match.py <dev.json> <retail.json> <out.json> [<dev symbols.json> for module-aware gap alignment]
1. Anchors: a token (string literal, distinctive constant) that occurs in exactly one function on each
   side pairs them; so does an identical, unique-on-both-sides string set. Pairs supported by
   conflicting anchors are dropped.
2. Propagation (to a fixpoint): for every matched pair, the unmatched direct callees (and callers)
   are paired when exactly one candidate remains on each side, or when a candidate pair is the
   only one with compatible features (shared strings/constants/imports) among the unmatched.
Output: {retail_va: {dev_va, name, how}} plus counts.
"""
import collections, json, sys


def main(devp, retp, outp):
    dev, ret = json.load(open(devp)), json.load(open(retp))

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

    def compatible(r, d):
        fr, fd = ret[r], dev[d]
        sr, sd = set(fr["strs"]), set(fd["strs"])
        if sr and sd and not (sr & sd):
            return False
        cr, cd = set(fr["consts"]), set(fd["consts"])
        if cr and cd and not (cr & cd) and len(cr) > 2 and len(cd) > 2:
            return False
        if set(fr["imps"]) and set(fd["imps"]) and not (set(fr["imps"]) & set(fd["imps"])):
            return False
        return True

    def score(r, d):
        fr, fd = ret[r], dev[d]
        return (len(set(fr["strs"]) & set(fd["strs"])) * 3 + len(set(fr["consts"]) & set(fd["consts"])) * 2 +
                len(set(fr["imps"]) & set(fd["imps"])))

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
        nr, nd = len(set(fr["calls"])), len(set(fd["calls"]))
        if abs(nr - nd) > max(1, 0.2 * max(nr, nd)):
            return False
        if set(fr["strs"]) & set(fd["strs"]) or set(fr["consts"]) & set(fd["consts"]) or set(fr["imps"]) & set(fd["imps"]):
            return True
        dcalls = set(fd["calls"])
        return any(r2d.get(c) in dcalls for c in set(fr["calls"]))

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

    changed, rounds = True, 0
    while changed and rounds < 50:
        changed, rounds = False, rounds + 1
        for r, d in list(r2d.items()):
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
                for x in ur:
                    scored = sorted(((score(x, y), y) for y in ud if compatible(x, y)), reverse=True)
                    if scored and scored[0][0] > 0 and (len(scored) == 1 or scored[0][0] > scored[1][0]):
                        y = scored[0][1]
                        if y not in d2r and x not in r2d:
                            r2d[x], d2r[y], how[x] = y, x, tag + "-scored"
                            changed = True
                            ud = [z for z in ud if z != y]
        if not changed and syms:
            if gapfill():
                changed = True
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
    c = collections.Counter(how.values())
    print("matched %d of %d retail functions (anchors %d, propagation rounds %d): %s" % (
        len(out), len(ret), anchors, rounds, dict(c)))


if __name__ == "__main__":
    main(*sys.argv[1:4])
