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

usage: land.py <batch> [--only SUBSTR | --exact MODULE] [--log work/migrate/land_<batch>.log] [--check]
       (several modules at once: tools/migrate/land_par.py)
"""
import argparse, glob, json, os, re, subprocess, sys, time

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
PY = os.path.join(ROOT, ".venv", "bin", "python")
SWEEP = os.path.join(ROOT, "work", "sweep_pod")
RANK = {"PASS": 4, "PASS-FP": 4, "WEAK": 3, "WEAK-FP": 3, "TIMEOUT": 2, "UNSUPPORTED": 1, "FAIL": 0}
# one scratch per worktree when tools/migrate/land_par.py runs several (work/ is shared through a symlink there)
SCRATCH = os.environ.get("LAND_SCRATCH") or os.path.join(ROOT, "work", "migrate", "land_scratch")


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
        if not sid:
            # an ERROR line names no slice (symbol not found in the module TU): the sweep record of the VA, if it has
            # exactly one (mig23: 0x0107e560 PASS -> WEAK landed with no baseline)
            recs = glob.glob(os.path.join(SWEEP, "s*_%s.json" % va))
            sid = os.path.basename(recs[0]).split("_")[0] if len(recs) == 1 else None
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
    ap.add_argument("--only", help="modules whose name contains SUBSTR")
    ap.add_argument("--exact", help="only this module")
    ap.add_argument("--log")
    ap.add_argument("--check", action="store_true", help="gate the batch's committed modules as they are; no rewrite, commit or rollback")
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
        if e["module"] not in mods and (not a.only or a.only in e["module"]) and (not a.exact or a.exact == e["module"]):
            mods.append(e["module"])
    log("== %s %s: %d modules" % (time.strftime("%Y-%m-%d %H:%M"), a.batch, len(mods)))
    for m in mods if a.check else []:
        if os.path.exists(os.path.join(ROOT, module_files(m)[0])):
            ok, why = gate(m, log)
            log("%s: %s %s" % (m, "GATE OK" if ok else "GATE FAIL", why))
    for m in mods if not a.check else []:
        # stdout only: git warns on stderr about a directory that does not exist yet (src/game/Havok/)
        dirty = subprocess.run(["git", "status", "--porcelain", "--"] + module_files(m), cwd=ROOT,
                               capture_output=True, text=True).stdout
        if dirty.strip():
            log("%s: skipped, uncommitted changes in its files" % m)
            continue
        sids = [e["id"] for e in ents if e["module"] == m]
        t0 = time.time()
        failed = []
        for sid in sids:
            rc, out = run([PY, "tools/migrate/rewrite.py", sid, "--module", m, "--batch", a.batch,
                           "--scratch", os.path.join(SCRATCH, "rw"), "--apply", "--quiet"])
            if rc:
                log("  %s %s: rewrite exit %d: %s" % (m, sid, rc, out.strip().splitlines()[-1][:200] if out.strip() else ""))
            elif "COMPILE FAILED" in out:
                # rewrite.py restores the TU and exits 0: the gate then passes the unchanged TU and commit_obj.sh finds nothing
                # to commit (mig27: 20 modules logged as "nothing added to commit")
                err = next((l.strip() for l in out.splitlines() if re.search(r"error C\d+", l)), "?")
                failed.append(sid)
                log("  %s %s: rewrite COMPILE FAILED: %s" % (m, sid, re.sub(r"^.*\\src\\game\\", "", err)[:200]))
        if failed and len(failed) == len(sids):
            rollback(m, sids)
            log("%s: ROLLED BACK (%d slices, %.0fs) rewrite compile failed in every slice (%s)" % (
                m, len(sids), time.time() - t0, " ".join(failed)))
            continue
        ok, why = gate(m, log)
        if ok:
            # the gate just ran run_all and the asm audit on these files: commit_obj.sh need not repeat them
            rc, out = run(["env", "LAND_GATED=1", "bash", "tools/migrate/commit_obj.sh", a.batch, m])
            ok, why = rc == 0, (out.strip().splitlines() or [""])[-1][:200]
        if not ok:
            rollback(m, sids)
        log("%s: %s (%d slices, %.0fs) %s" % (m, "LANDED" if ok else "ROLLED BACK", len(sids), time.time() - t0, why))


if __name__ == "__main__":
    main()
