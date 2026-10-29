#!/usr/bin/env python3
"""Run the resolution audit (resaudit.py) over many rows: byte-exact manifest rows and nonmatching rows.

Byte-exact compares mask relocations, so a byte-exact row can still name the wrong callee or global; equivalence
rows can only be trusted when every mapped reference agrees with the original. This sweep compiles (cached) and
audits only; nothing is emulated.

usage: resaudit_all.py [--slices id,...] [--part K/N] [--out work/resaudit/<name>.jsonl]
  default: every match/slices/*/{manifest,nonmatching}.txt row and every src/**/*.manifest.txt row.
  --part K/N audits every N-th source file starting at K (run N processes for parallelism).
Summary: resaudit_all.py --summary work/resaudit/*.jsonl"""
import glob, json, os, sys, time

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, HERE)


def _hex(x):
    try:
        int(x, 16)
        return len(x) in (6, 7, 8)
    except ValueError:
        return False


def rows():
    """-> [(kind, sid, src, va, flags)], grouped so one source compiles once."""
    out = []
    for d in sorted(glob.glob(os.path.join(ROOT, "match", "slices", "*"))):
        sid = os.path.basename(d)
        src = os.path.join(d, sid + ".cpp")
        m = os.path.join(d, "manifest.txt")
        if os.path.exists(m):
            for line in open(m, errors="replace"):
                p = line.split("#", 1)[0].split()
                if len(p) >= 3 and _hex(p[2]):
                    out.append(("exact", sid, os.path.normpath(os.path.join(ROOT, "match", p[0])), int(p[2], 16),
                                " ".join(p[3:]) or None))
        n = os.path.join(d, "nonmatching.txt")
        if os.path.exists(n):
            for line in open(n, errors="replace"):
                p = line.split()
                if p and len(p[0]) == 8:
                    try:
                        out.append(("nonmatching", sid, src, int(p[0], 16), None))
                    except ValueError:
                        pass
    for m in sorted(glob.glob(os.path.join(ROOT, "src", "**", "*.manifest.txt"), recursive=True)):
        for line in open(m, errors="replace"):
            p = line.split("#", 1)[0].split()
            if len(p) >= 3 and _hex(p[2]):
                out.append(("exact", "src:" + os.path.relpath(m, ROOT), os.path.normpath(os.path.join(ROOT, "match", p[0])),
                            int(p[2], 16), " ".join(p[3:]) or None))
    return out


def summarize(paths):
    recs = [json.loads(l) for p in paths for l in open(p)]
    by = {}
    for r in recs:
        by.setdefault((r["kind"], r["status"]), []).append(r)
    print("%d rows audited" % len(recs))
    for (k, st), rs in sorted(by.items()):
        print("  %-12s %-12s %5d" % (k, st, len(rs)))
    bad = [r for r in recs if r["status"] == "disagree"]
    if bad:
        print("\nDISAGREE (resolved address differs from the original's operand):")
        for r in bad:
            for d in r["disagree"]:
                print("  %s %s %-12s %s resolved %s operand %s, original %s at %s" % (r["va"], r["sid"], r["kind"], d["symbol"][:60],
                                                                         d["resolved"], d.get("expected", "?"), d["original"], d["at"]))
    loc = [r for r in recs if r.get("local_copy")]
    if loc:
        print("\nLOCAL COPIES (our own copy runs where the original calls a real function), %d rows; first 30:" % len(loc))
        for r in loc[:30]:
            print("  %s %s %-12s %s" % (r["va"], r["sid"], r["kind"],
                                        "; ".join("%s -> %s" % (d["symbol"][:70], ",".join(d["original"])) for d in r["local_copy"])))


if __name__ == "__main__":
    if "--summary" in sys.argv:
        summarize([a for a in sys.argv[1:] if a != "--summary"])
        sys.exit(0)
    os.environ.setdefault("DIFFTEST_NO_LEDGER", "1")
    import equiv as E
    import resaudit as RA
    args = sys.argv[1:]
    out = os.path.join(ROOT, "work", "resaudit", "all.jsonl")
    if "--out" in args:
        out = args[args.index("--out") + 1]
    R = rows()
    if "--slices" in args:
        keep = set(args[args.index("--slices") + 1].split(","))
        R = [r for r in R if r[1] in keep]
    srcs = sorted({r[2] for r in R})
    if "--part" in args:
        k, n = map(int, args[args.index("--part") + 1].split("/"))
        mine = set(srcs[k::n])
        R = [r for r in R if r[2] in mine]
    os.makedirs(os.path.dirname(out), exist_ok=True)
    img = E.context()["img"]
    t0 = time.time()
    with open(out, "w") as f:
        for kind, sid, src, va, flags in R:
            rec = {"kind": kind, "sid": sid, "va": "%08x" % va, "src": os.path.relpath(src, ROOT)}
            try:
                psid = sid if not sid.startswith("src:") else os.path.basename(src).rsplit(".", 1)[0]
                t = E.prepare(psid, va, flags, lambda *x: None, src)
                if not hasattr(t, "orig_insns"):
                    rec.update(status="not-audited", reason=(getattr(t, "reason", "") or "")[:200])
                else:
                    a = RA.audit(t.coff, t.fsym, t.res, t.orig_insns, img)
                    rec.update(status="disagree" if a["disagree"] else ("unverified" if a["unverified"] else "agree"),
                               disagree=a["disagree"], unverified=a["unverified"], local_copy=a["local_copy"],
                               agree=len(a["agree"]), same_code=a["same_code"], symbol=t.sym)
            except Exception as e:
                rec.update(status="error", reason=("%s: %s" % (type(e).__name__, e))[:200])
            f.write(json.dumps(rec) + "\n")
            f.flush()
    print("%d rows in %.0fs -> %s" % (len(R), time.time() - t0, os.path.relpath(out, ROOT)))
