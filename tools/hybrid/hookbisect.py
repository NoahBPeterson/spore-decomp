#!/usr/bin/env python3
"""Find which hooked function breaks the hybrid's boot, by bisection.

usage: hookbisect.py [--exclude @FILE|ids] [--secs 60] [--tag bis]

Candidates are the PASS functions (minus --exclude). A subset is "good" when boottest.sh reports
ALIVE at --secs seconds with no dialog, "bad" otherwise. Assumes one culprit per run: tests the
first half; if bad, recurses into it, else into the second half (if both halves are good the
failure needs several hooks together, which is reported). Each step builds the subset
(work/hybrid/<tag>_N.exe) and boots it; results go to work/hybrid/<tag>.log. Known culprits can be
fed back through --exclude to find the next one.
"""
import argparse, os, subprocess, sys, time

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, HERE)
import build as B  # noqa: E402

BOOTS = 3
ALWAYS = []    # hooks included in every build (--always)
FAULT = None   # --fault: only a crash at this address counts as bad (other crashes are other bugs)
ASK = False    # --ask: a human judges each boot that passed the automatic checks (e.g. audio crackle)
ASK_WAIT = 75  # seconds to wait for the human's answer before repeating the boot
PY = os.path.join(ROOT, ".venv", "bin", "python")


def is_good(verdict):
    if verdict.startswith("ALIVE"):
        # "hung?" = alive but ~0% CPU (black screen). That is a failure of its own: bad in a plain
        # bisect, "not the bug being bisected" when --fault targets a specific crash.
        return not (("hung?" in verdict or "black screen" in verdict or "no scene" in verdict) and not FAULT)
    if FAULT and verdict.startswith(("GONE", "CRASH")) and ("addr=" in verdict):
        a = int(verdict.rsplit("addr=", 1)[1].split()[0], 16)
        if FAULT == "wild":
            # a jump through a garbage pointer lands anywhere; its value shifts with heap layout
            in_image = 0x400000 <= a < 0x2000000
            if in_image:
                return True   # a crash inside real code: some other bug
        elif not ("%x" % a).startswith(FAULT):
            return True   # crashed somewhere else: not the bug being bisected
    return False


def test(subset, tag, n, secs, log, k0=0):
    lst = os.path.join(ROOT, "work", "hybrid", "%s_%d.txt" % (tag, n))
    exe = os.path.join(ROOT, "work", "hybrid", "%s_%d.exe" % (tag, n))
    with open(lst, "w") as f:
        for s, v in list(subset) + ALWAYS:
            f.write("%s %s\n" % (s, v))
    t0 = time.time()
    r = subprocess.run([PY, os.path.join(HERE, "build.py"), "--hook", lst, "--out", exe], capture_output=True, text=True)
    if r.returncode:
        log("step %d: build failed: %s" % (n, r.stderr[-400:]))
        sys.exit(1)
    # the crash is nondeterministic: "good" needs every one of --boots boots clean, "bad" one crash
    # The user may close the game window by hand once it has been up for a while (boottest.sh
    # reports "ALIVE ... (closed by hand)"); a close before that is INCONCLUSIVE and is redone.
    if ASK:
        return ask_test(subset, tag, n, exe, log, t0)
    verdicts = []
    k = k0
    while len(verdicts) < BOOTS:
        v = subprocess.run([os.path.join(HERE, "boottest.sh"), exe, str(secs), "%s_%d_%d" % (tag, n, k)],
                           capture_output=True, text=True).stdout.strip().splitlines()
        k += 1
        verdict = v[-1] if v else "no output"
        if verdict.startswith("INCONCLUSIVE"):
            log("  (boot closed early, repeating)")
            continue
        verdicts.append(verdict)
        if not is_good(verdict):
            break
    good = all(is_good(v) for v in verdicts)
    if good and ASK:
        # the symptom needs a human (crackling audio): wait for work/hybrid/<tag>.answer = good|bad
        ans = os.path.join(ROOT, "work", "hybrid", tag + ".answer")
        log("step %d: %d hooks -> %s; waiting %ds for %s (good|bad)" % (n, len(subset), verdicts[-1][:40], ASK_WAIT, os.path.relpath(ans, ROOT)))
        t1 = time.time()
        while not os.path.exists(ans) and time.time() - t1 < ASK_WAIT:
            time.sleep(3)
        if not os.path.exists(ans):
            # no answer = the human did not catch that boot: boot the same subset again
            log("  (no answer, booting step %d again)" % n)
            return test(subset, tag, n, secs, log, k)
        a = open(ans).read().strip().lower()
        os.remove(ans)
        good = a.startswith("good")
        verdicts.append("human: " + a)
    log("step %d: %d hooks -> %s  (%ds)" % (n, len(subset), " | ".join(verdicts), time.time() - t0))
    return good


def ask_test(subset, tag, n, exe, log, t0):
    """Human-judged boot: the game stays up until work/hybrid/<tag>.answer appears (good|bad); the
    answer closes it. If the game ends by itself first (crash, dialog, closed by hand), a crash is
    bad, otherwise the answer is still awaited for ASK_WAIT seconds and the step repeated without one."""
    ans = os.path.join(ROOT, "work", "hybrid", tag + ".answer")
    if os.path.exists(ans):
        os.remove(ans)
    k = 0
    while True:
        log("step %d: %d hooks -> booting (%s_%d_%d); answer with good|bad in %s" % (n, len(subset), tag, n, k, os.path.relpath(ans, ROOT)))
        proc = subprocess.Popen([os.path.join(HERE, "boottest.sh"), exe, "900", "%s_%d_%d" % (tag, n, k)],
                                stdout=subprocess.PIPE, stderr=subprocess.DEVNULL, text=True)
        while proc.poll() is None and not os.path.exists(ans):
            time.sleep(3)
        if os.path.exists(ans):
            subprocess.run(["pkill", "-f", "SporeApp_hybrid.exe"])
        else:
            t1 = time.time()
            while not os.path.exists(ans) and time.time() - t1 < ASK_WAIT:
                time.sleep(3)
        out = proc.communicate()[0].strip().splitlines()
        verdict = out[-1] if out else "no output"
        if not os.path.exists(ans):
            if verdict.startswith(("CRASH", "DIALOG")):
                log("step %d: %d hooks -> %s  (%ds)" % (n, len(subset), verdict, time.time() - t0))
                return False
            log("  (no answer, booting step %d again)" % n)
            k += 1
            continue
        a = open(ans).read().strip().lower()
        os.remove(ans)
        good = a.startswith("good") and not verdict.startswith("CRASH")
        log("step %d: %d hooks -> %s | human: %s  (%ds)" % (n, len(subset), verdict[:60], a, time.time() - t0))
        return good


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--exclude", default="")
    ap.add_argument("--secs", type=int, default=60)
    ap.add_argument("--tag", default="bis")
    ap.add_argument("--boots", type=int, default=3, help="clean boots needed to call a subset good")
    ap.add_argument("--fault", help="hex fault address of the crash being bisected; other crashes count as good")
    ap.add_argument("--cands", help="FILE of '<slice> <va>' lines to bisect instead of every PASS function")
    ap.add_argument("--always", help="FILE of hooks included in every build (pair search: bisect one half "
                                     "with the other half pinned, then swap)")
    ap.add_argument("--ask", action="store_true", help="a human judges every boot the automatic checks pass (answer file)")
    ap.add_argument("--skip-full", action="store_true", help="do not test the full candidate set first (known bad)")
    a = ap.parse_args()
    global BOOTS, FAULT, ALWAYS, ASK
    BOOTS = a.boots
    ASK = a.ask
    # hex prefix ('28f63' matches 28f632ca..), or 'wild' for any crash outside the image
    FAULT = None if not a.fault else ("wild" if a.fault == "wild" else "%x" % int(a.fault, 16))
    ALWAYS = B.file_targets(a.always) if a.always else []
    cands = B.file_targets(a.cands) if a.cands else B.pass_targets()
    if a.exclude:
        ex = open(a.exclude[1:]).read().split() if a.exclude.startswith("@") else a.exclude.split(",")
        ex = {e.strip().lower() for e in ex if e.strip()}
        cands = [(s, v) for s, v in cands if s not in ex and v not in ex]
    logf = open(os.path.join(ROOT, "work", "hybrid", a.tag + ".log"), "a")

    def log(msg):
        print(msg, flush=True)
        logf.write(msg + "\n")
        logf.flush()

    log("bisect over %d candidates" % len(cands))
    n = 0
    cur = cands
    if a.skip_full or not test(cur, a.tag, n, a.secs, log):
        while len(cur) > 1:
            n += 1
            half = cur[:len(cur) // 2]
            if not test(half, a.tag, n, a.secs, log):
                cur = half
                continue
            n += 1
            other = cur[len(cur) // 2:]
            if not test(other, a.tag, n, a.secs, log):
                cur = other
                continue
            log("both halves boot on their own: the failure needs hooks from both (%d candidates left)" % len(cur))
            for s, v in cur:
                log("  %s %s" % (s, v))
            return
        log("culprit: %s %s" % cur[0])
    else:
        log("the full set boots; nothing to bisect")


if __name__ == "__main__":
    main()
