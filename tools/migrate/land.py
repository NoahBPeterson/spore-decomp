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


MARK = re.compile(r"(?m)^// @ 0x0*([0-9a-fA-F]+)")


def markers_at_head(m):
    r = subprocess.run(["git", "show", "HEAD:" + module_files(m)[0]], cwd=ROOT, capture_output=True, text=True)
    return {v.lower() for v in MARK.findall(r.stdout)} if r.returncode == 0 else set()


def markers_now(m):
    p = os.path.join(ROOT, module_files(m)[0])
    return {v.lower() for v in MARK.findall(open(p, errors="replace").read())} if os.path.exists(p) else set()


def bodies(text):
    """VA -> text from its marker to the end of its first brace block (a function's definition)."""
    out = {}
    for mk in re.finditer(r"(?m)^// @ 0x0*([0-9a-fA-F]+)[^\n]*\n", text):
        i = j = text.find("{", mk.end())
        d = 0
        while 0 <= j < len(text):
            d += {"{": 1, "}": -1}.get(text[j], 0)
            if d == 0:
                break
            j += 1
        out[mk.group(1).lower()] = text[mk.end():j + 1]
    return out


def changed_landed(m):
    """Functions that were in the TU at HEAD and whose text the rewrite changed or removed. A re-applied slice carries the
    slice's text, which can undo a fix made in src/game after the first landing (2026-11-14: forward-port of 290 slices,
    96 would have changed landed functions)."""
    r = subprocess.run(["git", "show", "HEAD:" + module_files(m)[0]], cwd=ROOT, capture_output=True, text=True)
    p = os.path.join(ROOT, module_files(m)[0])
    if r.returncode or not os.path.exists(p):
        return []
    # rewrite.py's own clash renames (`FUN_00c308d0` -> `FUN_00c308d0_s00c7_5e70`, SPPlayer 2026-11-14) are not edits
    sfx = lambda s: re.sub(r"_s[0-9a-f]{4}_[0-9a-f]{4}\b", "", s) if s is not None else None
    a, b = bodies(r.stdout), bodies(open(p, errors="replace").read())
    return sorted(va for va in a if sfx(a[va]) != sfx(b.get(va)))


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
        return False, "no TU written", set()
    rc, out = run([PY, "tools/matching/run_all.py", "--manifest", "src/game/%s/%s/manifest.txt" % (d, stem)])
    last = out.strip().splitlines()[-1] if out.strip() else ""
    mm = re.match(r"(\d+) / (\d+) functions byte-exact", last)
    if not mm or mm.group(1) != mm.group(2):
        bad = {p[2] for p in (l.split() for l in out.splitlines()) if len(p) >= 3 and p[0] == "FAIL" and re.match(r"[0-9a-f]{8}$", p[2])}
        return False, "run_all: " + last, bad
    rc, out = run([PY, "tools/matching/asm_audit.py", "--all-rows", tu])
    if rc:
        return False, "asm audit: " + out.strip()[:200], set()
    rc, out = run([PY, "tools/migrate/samecode.py", tu])
    if "Traceback" in out:
        # mig27 SPUIBehavior: the traceback's first line was gated as a row ("verdict None -> None at Traceback")
        return False, "samecode crashed: " + out.strip().splitlines()[-1][:200], set()
    drops = []
    for line in out.splitlines():
        p = line.split()
        if len(p) < 2 or p[1] == "SAME" or not re.match(r"[0-9a-f]{8}$", p[0]):
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
            # every row is checked, so one retry can drop all of them (land_module)
            drops.append((va, before, after))
    if drops:
        return False, "; ".join("verdict %s -> %s at %s" % (b, f, va) for va, b, f in drops)[:400], {va for va, _b, _f in drops}
    return True, last, set()


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
            ok, why, _bad = gate(m, log)
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
        dropped, bname, rounds = set(), a.batch, 0
        try:
            while True:
                ok, why, bad = land_once(m, sids, bname, a.batch, log)
                head = markers_at_head(m)
                new = {e for e in bad if e.lstrip("0") not in head}
                # the gate named failing functions, all of them new: land the rest without them (mig34: 9 of 14 objects of
                # 16-20 slices rolled back on one or a few rows).  A failing row that was landed before, a non-row failure
                # (compile, audit, commit) or a 4th round ends it
                if ok or not bad or new != bad or rounds == 3:
                    break
                rounds += 1
                dropped |= bad
                log("  %s: retry %d without %s (%s)" % (m, rounds, " ".join(sorted(dropped)), why[:160]))
                bname = "_land_%s_%d" % (os.path.basename(m), os.getpid())
                json.dump([dict(e, vas=[v for v in e["vas"] if v not in dropped]) if e["module"] == m else e for e in ents],
                          open(os.path.join(ROOT, "work", "batches", bname + ".json"), "w"))
        finally:
            if bname != a.batch:
                os.remove(os.path.join(ROOT, "work", "batches", bname + ".json"))
        log("%s: %s (%d slices, %.0fs) %s%s" % (m, "LANDED" if ok else "ROLLED BACK", len(sids), time.time() - t0, why,
                                                "; left in slices: " + " ".join(sorted(dropped)) if ok and dropped else ""))


def land_once(m, sids, bname, batch, log):
    """rewrite every slice of the module from batch file bname, gate, commit (commit_obj.sh reads the real batch's slice
    list) or roll back.  -> (ok, why, VAs the gate named)"""
    why_none = {}
    before = markers_at_head(m)
    # a slice whose listed functions live in a flag-variant source (s00a80240_g7.cpp) needs one more rewrite.py run per
    # variant, which the plain run names in a VARIANT SOURCE line (mig33: 10 modules rolled back with nothing written)
    todo = [(sid, None) for sid in sids]
    while todo:
        sid, var = todo.pop(0)
        rc, out = run([PY, "tools/migrate/rewrite.py", sid, "--module", m, "--batch", bname,
                       "--scratch", os.path.join(SCRATCH, "rw"), "--apply", "--quiet"] + (["--variant", var] if var is not None else []))
        if var is None:
            todo[:0] = [(sid, v.strip('"')) for v in re.findall(r"(?m)^VARIANT SOURCE: .* --variant (\S+)$", out)]
        if rc:
            log("  %s %s: rewrite exit %d: %s" % (m, sid, rc, out.strip().splitlines()[-1][:200] if out.strip() else ""))
        elif "COMPILE FAILED" in out:
            # rewrite.py restores the TU and exits 0: the gate then passes the unchanged TU and commit_obj.sh finds nothing
            # to commit (mig27: 20 modules logged as "nothing added to commit")
            err = next((l.strip() for l in out.splitlines() if re.search(r"error C\d+", l)), "?")
            why_none.setdefault("compile failed", []).append(sid)
            log("  %s %s: rewrite COMPILE FAILED: %s" % (m, sid, re.sub(r"^.*\\src\\game\\", "", err)[:200]))
        elif "no reconstructed functions" in out:
            # markers only in a banner or after macro lines (s006d0940 DEFINE_BAKE), or the code is a vendored
            # #include (s008894a0 EAWebKit): nothing rewrite.py can move
            why_none.setdefault("no line-start markers", []).append(sid)
    if not (markers_now(m) - before):
        # nothing new reached the TU: commit_obj.sh would fail on an empty commit (mig27: 20 modules)
        rollback(m, sids)
        return False, "no new function written%s" % (
            "".join("; %s: %s" % (k, " ".join(v)) for k, v in sorted(why_none.items())) or "; every listed function stayed in its slice"), set()
    touched = changed_landed(m)
    if touched:
        rollback(m, sids)
        return False, "changed %d function(s) already in the TU: %s" % (len(touched), " ".join(touched[:8])), set()
    ok, why, bad = gate(m, log)
    if ok:
        # the gate just ran run_all and the asm audit on these files: commit_obj.sh need not repeat them
        rc, out = run(["env", "LAND_GATED=1", "bash", "tools/migrate/commit_obj.sh", batch, m])
        ok, why = rc == 0, (out.strip().splitlines() or [""])[-1][:200]
    if not ok:
        rollback(m, sids)
    return ok, why, bad

if __name__ == "__main__":
    main()
