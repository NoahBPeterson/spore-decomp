#!/usr/bin/env python3
"""Read a coverage dump from a `build.py --coverage` run.

usage: covread.py <run.cov.bin> [--sidecar X.exe.cov.json] [--hooks X.exe.hooks.json]
                  [--json OUT] [--timeline] [--top N]

The dump is the 16-byte g_cov header ('SCOV', n, t0, hits) followed by n first-hit times
(ms since entry + 1; 0 = never), in the order of the sidecar's rows [bp, va, name]. Prints how many
functions ran, how many of the hooked ones ran, and the first-hit timeline; --json writes
{va: first_hit_ms} for the executed functions (hex keys) for other tools.
"""
import argparse, json, os, struct, sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))


def load(path, sidecar):
    d = open(path, "rb").read()
    magic, n, t0, hits = struct.unpack_from("<4sIII", d, 0)
    if magic != b"SCOV":
        raise SystemExit("%s: not a coverage dump" % path)
    sc = json.load(open(sidecar))
    if sc["n"] != n:
        raise SystemExit("sidecar has %d rows, dump has %d" % (sc["n"], n))
    ticks = struct.unpack_from("<%dI" % n, d, 16)
    return sc["rows"], ticks, hits


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("dump")
    ap.add_argument("--sidecar", help="default: the newest work/hybrid/*.exe.cov.json")
    ap.add_argument("--hooks", help="hooks.json of the same build, for per-slice hooked/executed counts")
    ap.add_argument("--json", help="write {va: ms} of executed functions")
    ap.add_argument("--timeline", action="store_true", help="functions first hit per second")
    ap.add_argument("--tiers", action="store_true", help="executed / not executed by source tier (imports tools/status.py)")
    ap.add_argument("--missing", help="write the executed functions without complete source, in first-hit order")
    ap.add_argument("--top", type=int, default=0, help="print the first N functions in hit order")
    a = ap.parse_args()
    sidecar = a.sidecar
    if not sidecar:
        cands = sorted((os.path.getmtime(p), p) for p in
                       (os.path.join(ROOT, "work", "hybrid", f) for f in os.listdir(os.path.join(ROOT, "work", "hybrid")))
                       if p.endswith(".exe.cov.json"))
        sidecar = cands[-1][1]
    rows, ticks, hits = load(a.dump, sidecar)
    ran = [(t - 1, bp, va, name) for (bp, va, name), t in zip(rows, ticks) if t]
    ran.sort()
    hooked = [r for r in rows if r[0] != r[1]]
    hooked_ran = [r for r in ran if r[1] != r[2]]
    print("%s: %d of %d functions executed (hits counter %d); last first-hit at %.1f s" %
          (os.path.basename(a.dump), len(ran), len(rows), hits, ran[-1][0] / 1000 if ran else 0))
    if hooked:
        print("hooked functions: %d of %d executed (%.1f%%)" % (len(hooked_ran), len(hooked), 100.0 * len(hooked_ran) / len(hooked)))
    if a.hooks:
        hk = json.load(open(a.hooks))["hooks"]
        by_va = {int(h["va"], 16): h["slice"] for h in hk}
        per = {}
        for r in rows:
            if r[0] != r[1]:
                per.setdefault(by_va.get(r[1], "?"), [0, 0])[0] += 1
        for r in hooked_ran:
            per[by_va.get(r[2], "?")][1] += 1
        never = sorted((s for s, (n, e) in per.items() if e == 0))
        print("slices with hooks: %d; with no hook executed: %d" % (len(per), len(never)))
    if a.tiers or a.missing:
        sys.path.insert(0, os.path.join(ROOT, "tools"))
        import status as st          # a few seconds: reads every manifest and the image
        tiers = [("byte-exact", st.byte_exact), ("equivalent", st.equiv), ("partial", st.part),
                 ("no source", st.nosrc), ("library", set(st.lib_in_funcs))]
        ran_set = {va for _t, _bp, va, _n in ran}
        sz = lambda S: sum(st.funcs[v]["size"] for v in S) / 2 ** 20
        print("%-12s %18s %18s" % ("tier", "executed", "not executed"))
        for name, S in tiers:
            e, ne = S & ran_set, S - ran_set
            print("%-12s %7d %7.2f MB %7d %7.2f MB" % (name, len(e), sz(e), len(ne), sz(ne)))
        if a.missing:
            tier_of = {}
            for name, S in tiers:
                for v in S:
                    tier_of.setdefault(v, name)
            with open(a.missing, "w") as f:
                f.write("# first-hit-s  va  size  tier  name   (executed in %s, no complete source)\n" % os.path.basename(a.dump))
                for t, bp, va, name in ran:
                    if tier_of.get(va) in ("partial", "no source"):
                        f.write("%8.3f %08x %6d %-9s %s\n" % (t / 1000, va, st.funcs[va]["size"], tier_of[va].replace(" ", "-"), name))
            print("wrote", a.missing)
    if a.timeline:
        import collections
        bins = collections.Counter(t // 1000 for t, *_ in ran)
        for s in range(0, (max(bins) if bins else 0) + 1):
            print("  %4ds %6d %s" % (s, bins.get(s, 0), "#" * min(60, bins.get(s, 0) // 50)))
    for t, bp, va, name in ran[:a.top]:
        print("  %7.3fs %08x %s%s" % (t / 1000, va, name, "  (hooked)" if bp != va else ""))
    if a.json:
        json.dump({"%08x" % va: t for t, bp, va, name in ran}, open(a.json, "w"))
        print("wrote", a.json)


if __name__ == "__main__":
    main()
