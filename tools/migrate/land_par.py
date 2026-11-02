#!/usr/bin/env python3
"""land_par: tools/migrate/land.py on several modules at once, one git worktree per worker.

land.py lands one module at a time: its rollback restores all of src/game/include and commit_obj.sh stages all of
it, so two landings in one tree would take each other's headers.  Here every worker lands its module with land.py
--exact in its own worktree (work/claude/landwt_<k>, detached at main's tip, `work` and `.venv` symlinked to the
main repo's; land.py gets its own LAND_SCRATCH), and the coordinator cherry-picks each landing commit into main:

  - a cherry-pick that conflicts is aborted and the module is landed again at the end, serially, in main;
  - after a clean pick, run_all on the module's manifest in main must still be all byte-exact (two modules may change
    one header in compatible hunks), or the pick is reverted and the module goes to the serial pass;
  - two modules that share a slice never run at the same time (both would edit the slice and its symbols file).

The serial pass is plain land.py in main.  Afterwards `land.py <batch> --check` re-gates every committed module of
the batch in main (headers merged from other modules can change a function that was gated before the merge).

usage: land_par.py <batch> [--workers 4] [--check]     log: work/migrate/land_<batch>.log (workers append to it)
"""
import argparse, json, os, re, subprocess, sys, threading, time

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
PY = os.path.join(ROOT, ".venv", "bin", "python")


def git(*args, cwd=ROOT):
    r = subprocess.run(["git", *args], cwd=cwd, capture_output=True, text=True)
    return r.returncode, r.stdout + r.stderr


def make_worktree(k):
    wt = os.path.join(ROOT, "work", "claude", "landwt_%d" % k)
    if not os.path.isdir(wt):
        rc, out = git("worktree", "add", "-q", "--detach", wt, "main")
        if rc:
            sys.exit("worktree %s: %s" % (wt, out))
    link_missing(ROOT, wt, ".venv")
    link_missing(ROOT, wt, "work")
    return wt


def link_missing(src_root, wt, rel):
    """Symlink src_root/rel into the worktree; where the checkout already made rel a directory (git tracks a few files
    of work/batches, so the worktree has a real work/ holding only those: mig26 failed every module on a missing
    work/batches/mig26.json), link its missing entries one by one instead.  git reset/checkout in the worktree leaves
    the links alone (they are untracked)."""
    dst = os.path.join(wt, rel)
    if not os.path.lexists(dst):
        os.symlink(os.path.join(src_root, rel), dst)
    elif os.path.isdir(dst) and not os.path.islink(dst):
        for name in os.listdir(os.path.join(src_root, rel)):
            if not name.startswith("landwt_"):
                link_missing(src_root, wt, os.path.join(rel, name))


def reset_worktree(wt):
    git("reset", "-q", "--hard", cwd=wt)
    git("clean", "-fdq", "--", "src", "match", "symbols", cwd=wt)
    git("checkout", "-q", "--detach", "main", cwd=wt)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("batch")
    ap.add_argument("--workers", type=int, default=4)
    ap.add_argument("--check", action="store_true", help="re-gate the batch's committed modules in main afterwards")
    a = ap.parse_args()
    logp = os.path.join(ROOT, "work", "migrate", "land_%s.log" % a.batch)
    loglock, gitlock, qlock = threading.Lock(), threading.Lock(), threading.Lock()

    def log(s):
        with loglock:
            print(s, flush=True)
            open(logp, "a").write(s + "\n")

    if git("status", "--porcelain", "--untracked-files=no")[1].strip():
        sys.exit("main has uncommitted changes to tracked files: commit or stash them first")
    ents = json.load(open(os.path.join(ROOT, "work", "batches", a.batch + ".json")))
    mods, sids = [], {}
    for e in ents:
        if e["module"] not in sids:
            mods.append(e["module"])
            sids[e["module"]] = set()
        sids[e["module"]].add(e["id"])
    queue = list(mods)
    running = {}            # module -> its slice ids
    serial, landed = [], []
    log("== %s %s: %d modules, %d workers" % (time.strftime("%Y-%m-%d %H:%M"), a.batch, len(mods), a.workers))

    def take():
        with qlock:
            busy = set().union(*running.values()) if running else set()
            for m in queue:
                if not (sids[m] & busy):
                    queue.remove(m)
                    running[m] = sids[m]
                    return m
            return None if not queue else ""          # "" = something is left but blocked by a running module

    def worker(k):
        wt = make_worktree(k)
        env = dict(os.environ, LAND_SCRATCH=os.path.join(ROOT, "work", "migrate", "land_scratch_%d" % k))
        while True:
            m = take()
            if m is None:
                return
            if m == "":
                time.sleep(5)
                continue
            try:
                with gitlock:
                    reset_worktree(wt)
                wlog = os.path.join(ROOT, "work", "migrate", "land_%s_w%d.log" % (a.batch, k))
                r = subprocess.run([PY, os.path.join(wt, "tools", "migrate", "land.py"), a.batch, "--exact", m,
                                    "--log", wlog], cwd=wt, env=env, capture_output=True, text=True)
                line = next((l for l in r.stdout.splitlines() if l.startswith(m + ":")), "%s: no result (exit %d) %s" % (
                    m, r.returncode, (r.stdout + r.stderr).strip().splitlines()[-1:] if (r.stdout + r.stderr).strip() else ""))
                for l in r.stdout.splitlines():
                    if l.startswith("    "):
                        log(l)
                mm = re.search(r": LANDED .*\) ([0-9a-f]{7,40}) ", line)
                if not mm:
                    log(line)
                    continue
                sha = git("rev-parse", "HEAD", cwd=wt)[1].strip()
                with gitlock:
                    rc, out = git("cherry-pick", sha)
                    if rc:
                        git("cherry-pick", "--abort")
                        log("%s: CONFLICT on cherry-pick into main, landed again serially at the end" % m)
                        serial.append(m)
                        continue
                    rc, out = subprocess.run([PY, "tools/matching/run_all.py", "--manifest", "src/game/%s/manifest.txt" % m],
                                             cwd=ROOT, capture_output=True, text=True).stdout, None
                    last = rc.strip().splitlines()[-1] if rc.strip() else ""
                    ok = re.match(r"(\d+) / (\d+) functions byte-exact", last)
                    if not ok or ok.group(1) != ok.group(2):
                        git("revert", "--no-edit", "HEAD")
                        log("%s: NOT EXACT in main after the pick (%s): reverted, landed again serially" % (m, last))
                        serial.append(m)
                        continue
                    log(line.replace(mm.group(1), git("rev-parse", "--short", "HEAD")[1].strip()))
                    landed.append(m)
            finally:
                with qlock:
                    running.pop(m, None)

    ts = [threading.Thread(target=worker, args=(k,)) for k in range(a.workers)]
    for t in ts:
        t.start()
    for t in ts:
        t.join()
    for m in serial:
        r = subprocess.run([PY, "tools/migrate/land.py", a.batch, "--exact", m, "--log", logp], cwd=ROOT,
                           capture_output=True, text=True)
        print("\n".join(l for l in r.stdout.splitlines() if not l.startswith(("==", "    "))), flush=True)
    if a.check:
        # only what this run landed in parallel (the serial pass landed in main, gated there)
        for m in landed:
            subprocess.run([PY, "tools/migrate/land.py", a.batch, "--check", "--exact", m, "--log",
                            os.path.join(ROOT, "work", "migrate", "check_%s.log" % a.batch)], cwd=ROOT)
    log("== %s %s: done" % (time.strftime("%Y-%m-%d %H:%M"), a.batch))


if __name__ == "__main__":
    main()
