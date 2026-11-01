#!/usr/bin/env python3
"""land: migrate a batch's modules mechanically, gate each one, commit or roll back.

For every module of work/batches/<batch>.json (entries {id, vas, module}, tools: work/claude/make_wave.py):
  1. tools/migrate/rewrite.py <slice> --module M --batch <batch> --apply for each of its entries;
  2. gate: every manifest row byte-exact (run_all), asm audit clean, and every nonmatching row either
     compiles to the same code as in its slice (tools/migrate/samecode.py) or gets an equiv.py verdict no
     worse than the strict sweep's verdict for the slice row (work/sweep_pod/<slice>_<va>.json; no sweep
     record = no baseline, the new verdict is logged);
  3. pass: tools/migrate/commit_obj.sh <batch> M (re-checks run_all and the audit, commits);
     fail: the module's files are restored to HEAD and the reason is logged.

usage: land.py <batch> [--only SUBSTR] [--log work/migrate/land_<batch>.log]
"""
import argparse, glob, json, os, re, subprocess, sys, time

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
PY = os.path.join(ROOT, ".venv", "bin", "python")
SWEEP = os.path.join(ROOT, "work", "sweep_pod")
RANK = {"PASS": 4, "PASS-FP": 4, "WEAK": 3, "WEAK-FP": 3, "TIMEOUT": 2, "UNSUPPORTED": 1, "FAIL": 0}
SCRATCH = os.path.join(ROOT, "work", "migrate", "land_scratch")


def run(args, timeout=3600):
    r = subprocess.run(args, cwd=ROOT, capture_output=True, text=True, timeout=timeout)
    return r.returncode, r.stdout + r.stderr


def verdict(path):
    try:
        d = json.load(open(path))
    except (OSError, ValueError):
        return None
    d = d[0] if isinstance(d, list) and d else d
    return d.get("verdict") if isinstance(d, dict) else None


def module_files(m):
    d, stem = os.path.split(m)
    return ["src/game/%s/%s.cpp" % (d, stem), "src/game/%s/%s" % (d, stem)]


def rollback(m, sids):
    paths = module_files(m) + ["symbols/slices/%s.txt" % s for s in sids] + ["src/game/include"]
    tracked = run(["git", "ls-files", "--"] + paths)[1].split()
    if tracked:
        run(["git", "checkout", "HEAD", "--"] + tracked)
    run(["git", "clean", "-fdq", "--"] + paths)


def gate(m, log):
    d, stem = os.path.split(m)
    tu = "src/game/%s/%s.cpp" % (d, stem)
    if not os.path.exists(os.path.join(ROOT, tu)):
        return False, "no TU written"
    rc, out = run([PY, "tools/matching/run_all.py", "--manifest", "src/game/%s/%s/manifest.txt" % (d, stem)])
    last = out.strip().splitlines()[-1] if out.strip() else ""
    mm = re.match(r"(\d+) / (\d+) functions byte-exact", last)
    if not mm or mm.group(1) != mm.group(2):
        return False, "run_all: " + last
    rc, out = run([PY, "tools/matching/asm_audit.py", "--all-rows", tu])
    if rc:
        return False, "asm audit: " + out.strip()[:200]
    rc, out = run([PY, "tools/migrate/samecode.py", tu])
    for line in out.splitlines():
        p = line.split()
        if len(p) < 2 or p[1] == "SAME":
            continue
        va = p[0]
        ms = re.search(r"\((s[0-9a-f]{8})\)\s*$", line)
        sid = ms.group(1) if ms else None
        before = verdict(os.path.join(SWEEP, "%s_%s.json" % (sid, va))) if sid else None
        js = os.path.join(SCRATCH, "%s_%s.json" % (stem, va))
        run([PY, "tools/difftest/equiv.py", stem, va, "--src", tu, "--fp-tol", "--max-mismatch", "200", "--json", js])
        after = verdict(js)
        log("    %s %s -> equiv %s (sweep had %s)" % (va, " ".join(p[1:])[:80], after, before))
        if after is None or (before is not None and RANK.get(after, 0) < RANK.get(before, 0)):
            return False, "verdict %s -> %s at %s" % (before, after, va)
    return True, last


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("batch")
    ap.add_argument("--only")
    ap.add_argument("--log")
    a = ap.parse_args()
    os.makedirs(SCRATCH, exist_ok=True)
    logp = a.log or os.path.join(ROOT, "work", "migrate", "land_%s.log" % a.batch)
    lf = open(logp, "a")

    def log(s):
        print(s, flush=True)
        lf.write(s + "\n")
        lf.flush()

    ents = json.load(open(os.path.join(ROOT, "work", "batches", a.batch + ".json")))
    mods = []
    for e in ents:
        if e["module"] not in mods and (not a.only or a.only in e["module"]):
            mods.append(e["module"])
    log("== %s %s: %d modules" % (time.strftime("%Y-%m-%d %H:%M"), a.batch, len(mods)))
    for m in mods:
        # stdout only: git warns on stderr about a directory that does not exist yet (src/game/Havok/)
        dirty = subprocess.run(["git", "status", "--porcelain", "--"] + module_files(m), cwd=ROOT,
                               capture_output=True, text=True).stdout
        if dirty.strip():
            log("%s: skipped, uncommitted changes in its files" % m)
            continue
        sids = [e["id"] for e in ents if e["module"] == m]
        t0 = time.time()
        for sid in sids:
            rc, out = run([PY, "tools/migrate/rewrite.py", sid, "--module", m, "--batch", a.batch,
                           "--scratch", os.path.join(SCRATCH, "rw"), "--apply", "--quiet"])
            if rc:
                log("  %s %s: rewrite exit %d: %s" % (m, sid, rc, out.strip().splitlines()[-1][:200] if out.strip() else ""))
        ok, why = gate(m, log)
        if ok:
            rc, out = run(["bash", "tools/migrate/commit_obj.sh", a.batch, m])
            ok, why = rc == 0, (out.strip().splitlines() or [""])[-1][:200]
        if not ok:
            rollback(m, sids)
        log("%s: %s (%d slices, %.0fs) %s" % (m, "LANDED" if ok else "ROLLED BACK", len(sids), time.time() - t0, why))


if __name__ == "__main__":
    main()
