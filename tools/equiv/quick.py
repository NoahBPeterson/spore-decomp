"""Quick verdict for a function that is not byte-exact (tools/contrib/check.py runs it after the instruction diff).

In seconds, it answers the question a contributor needs next: is the source WRONG (fix the logic), or does it only
compile differently (try a codegen lever from docs/codegen.md, or prove it equivalent with tools/contrib/prove.py)?

  1. register renaming (tools/equiv/rename.py): milliseconds; when it proves the function, the bytes differ only by
     register names and the order of independent instructions.
  0. closeness (tools/equiv/closeness.py): milliseconds; the shape (calls, stores, branches) and a register-insensitive
     similarity, so an undecided function still says how far off it is. Structure only, not correctness.
  2. angr (tools/equiv/angr_layer.py), capped at a few seconds, without prove.py's mutant self-test: a proof says the
     function is very likely equivalent (prove.py --record runs the full proof and records it); a counterexample is
     a definite difference, printed in words with the inputs that show it.
  3. the emulator test (tools/difftest/equiv.py), only when angr did not decide: random inputs through both
     builds. A mismatch is a real bug with a replayable input; no mismatch is only a hint, never a proof.

Nothing here is recorded: prove.py is the tool that records proofs. Layers that are not installed are skipped with a
note (angr: tools/equiv/LAYERS.md; the emulator needs unicorn and numpy).
"""
import json, os, re, subprocess, sys, tempfile, time

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
for p in (os.path.join(ROOT, "tools", "equiv"), os.path.join(ROOT, "tools", "contrib")):
    if p not in sys.path:
        sys.path.insert(0, p)

PRESERVED = {"ebx", "esi", "edi", "ebp"}


def _what(token):
    """one difference token from angr ('call#1 target', 'ret#0 eax', ...) -> words"""
    m = re.match(r"(call|ret|diverge)#(\d+)\s+(.*)", token.strip())
    if not m:
        return token.strip()
    kind, k, obs = m.group(1), int(m.group(2)), m.group(3)
    n = "event #%d" % k
    if kind == "call":
        if obs == "target":
            return "%s calls a different function" % n
        if obs == "esp":
            return "%s (a call) sees a different stack: different arguments pushed, or a different frame" % n
        if obs == "memory":
            return "%s (a call): memory differs when it is made (an argument or a store before the call)" % n
        return "%s (a call): %s differs (an argument or a register the callee reads)" % (n, obs)
    if kind == "ret":
        if obs in ("eax", "edx"):
            return "the return value (%s) differs" % obs
        if obs in PRESERVED:
            return "%s, which callers rely on, is not restored the same way at return" % obs
        if obs == "esp":
            return "returns with a different stack pointer (stack imbalance)"
        if obs == "memory":
            return "the memory it writes differs"
        if obs == "return target":
            return "tail-calls a different function"
        return "%s differs at return" % obs
    return "%s: %s" % (n, obs)


def explain(detail):
    """angr's detail string -> (list of differences in words, inputs that show it, raw reason)"""
    m = re.search(r"difference: (\{.*?\})(?: \||$)", detail)
    if not m:
        return [], {}, detail
    try:
        d = json.loads(m.group(1))
    except ValueError:
        return [], {}, detail
    what = d.get("what", "")
    if what.startswith("event sequence"):
        diffs = ["a different sequence of calls and returns (%s)" % what[len("event sequence "):]]
    else:
        diffs = [_what(t) for t in what.split(",") if t.strip()]
    if d.get("addr"):
        diffs = [x + (" at %s" % d["addr"] if "memory" in x else "") for x in diffs]
    inputs = {k[3:]: v for k, v in d.items() if k.startswith("in_") and v not in ("0x0", 0)}
    return diffs, inputs, detail


def _layer(name):
    try:
        import importlib
        return importlib.import_module(name)
    except ImportError as e:
        return str(e)


def run(va, angr_timeout=15.0, emu_timeout=10, log=print):
    """Print the quick verdict for va. Returns 'equivalent' | 'differs' | 'likely-differs' | 'undecided' | 'skipped'."""
    import func as FN
    import facts
    import asm_audit
    t0 = time.time()
    try:
        retail, ours = FN.retail_func(va), FN.our_func(va)
    except SystemExit as e:
        log("quick check: skipped (%s)" % str(e).splitlines()[0])
        return "skipped"
    if asm_audit.transcribed(os.path.join(ROOT, ours.meta["src"])).get("%08x" % va):
        log("quick check: skipped (an assembly transcription: write it as C++ first)")
        return "skipped"
    import task as T
    if va in set(T.equivalent()):
        log("quick check: already recorded as proven equivalent (equivalent.txt); a byte-exact match would still count")
        return "equivalent"
    same, why, _fa = facts.same(retail, ours)
    level = "L1" if same else "L2"
    nc = re.match(r"retail makes (\d+) calls, ours (\d+)", why or "")
    if nc:
        log("quick check: retail makes %s calls and ours %s: a callee is inlined (or not) differently, or calls are"
            " missing or extra. Compare the call lines of the diff above first." % nc.groups())
    elif not same:
        log("quick check: our register use differs from retail's (%s), so it is checked at L2 (every register)" % why)
    import closeness
    log("closeness: " + closeness.describe(closeness.compare(retail, ours)))
    import rename
    r = rename.prove(retail, ours, level)
    if r["status"] == "proved":
        log("quick check: EQUIVALENT by register renaming at %s: the bytes differ only in register names and the order"
            " of independent instructions. Record it: tools/contrib/prove.py 0x%08x --record" % (level, va))
        return "equivalent"
    angr = _layer("angr_layer")
    verdict = "undecided"
    if isinstance(angr, str):
        log("quick check: angr is not installed, so no symbolic check (tools/equiv/LAYERS.md)")
    else:
        r = angr.prove(retail, ours, level, None, angr_timeout)
        if r["status"] == "proved":
            log("quick check: very likely EQUIVALENT: angr proves it at %s in %.0fs (the mutant self-test is not run"
                " here). Record it: tools/contrib/prove.py 0x%08x --record" % (level, r["seconds"], va))
            return "equivalent"
        diffs, inputs, raw = explain(r["detail"])
        ins = ", ".join("%s=%s" % kv for kv in inputs.items())
        if r["status"] == "refuted":
            log("quick check: DIFFERS from the original (angr, %s): the source computes something else; fix the logic,"
                " not the codegen." % level)
            for x in diffs:
                log("  - " + x)
            if ins:
                log("  inputs that show it: " + ins)
            return "differs"
        nt = re.search(r"not trusted \((.*?)\): difference", raw)
        if diffs and nt:
            log("quick check: LIKELY DIFFERS (angr found a difference, but it rests on: %s)" % nt.group(1))
            for x in diffs:
                log("  - " + x)
            verdict = "likely-differs"
        else:
            reason = re.sub(r"\s*\|.*$", "", raw).strip()
            log("quick check: angr could not decide in %.0fs: %s" % (r["seconds"], reason[:200]))
    # the emulator: a quick refuter for what angr left open
    try:
        import importlib.util
        if importlib.util.find_spec("unicorn") is None or importlib.util.find_spec("numpy") is None:
            raise ImportError
    except ImportError:
        log("quick check: the emulator test needs unicorn and numpy (pip install unicorn numpy); skipped")
        return verdict
    _src, ident = T.locate(va)
    with tempfile.TemporaryDirectory() as tmp:
        out = os.path.join(tmp, "r.json")
        subprocess.run([sys.executable, os.path.join(ROOT, "tools", "difftest", "equiv.py"), ident, "%08x" % va,
                        "--src", os.path.join(ROOT, ours.meta["src"]), "--time-limit", str(emu_timeout),
                        "--json", out], capture_output=True, text=True, timeout=emu_timeout + 120)
        try:
            res = json.load(open(out))[0]
        except (OSError, ValueError, IndexError):
            log("quick check: the emulator test gave no result")
            return verdict
    v, reason = res.get("verdict", ""), (res.get("reason") or "")[:240]
    if v.startswith("FAIL"):
        log("quick check: DIFFERS (emulator): a concrete input gives a different result: %s" % reason)
        return "differs"
    if v.startswith(("PASS", "WEAK")):
        log("quick check: the emulator found no mismatch on random inputs (%s); a hint, not a proof" % v)
    else:
        log("quick check: the emulator could not run it (%s %s)" % (v, reason[:120]))
    log("  (quick check took %.0fs)" % (time.time() - t0))
    return verdict


if __name__ == "__main__":
    va = int(sys.argv[1], 16)
    sys.exit(0 if run(va) == "equivalent" else 1)
