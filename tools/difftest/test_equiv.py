"""Self-tests for the equivalence harness (run: .venv/bin/python -m pytest tools/difftest/test_equiv.py).

(a) a byte-exact function from a slice manifest must PASS;
(b) the same source with one operator changed must FAIL;
(c) real nonmatching functions get a verdict (any of the four) without crashing.
"""
import os, sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, HERE)
import equiv  # noqa: E402

EXACT_SID, EXACT_VA = "s0085f1e0", 0x0085f1e0     # jpeg_fdct_float, byte-exact (manifest)
MUT_DIR = os.path.join(ROOT, "work", "difftest", "mut")


def opts(*extra):
    return equiv.parse_args(["x", "--inputs", "220", "--time-limit", "60", *extra])


def test_byte_exact_passes():
    r = equiv.test_function(EXACT_SID, EXACT_VA, opts())
    assert r["verdict"] == "PASS", r


def mutant(old, new, tag):
    src = os.path.join(ROOT, "match", "slices", EXACT_SID, EXACT_SID + ".cpp")
    text = open(src).read()
    assert old in text, old
    os.makedirs(MUT_DIR, exist_ok=True)
    path = os.path.join(MUT_DIR, "%s_%s.cpp" % (EXACT_SID, tag))
    open(path, "w").write(text.replace(old, new, 1))
    return path


def test_changed_operator_fails():
    path = mutant("dataptr[4] = tmp10 - tmp11;", "dataptr[4] = tmp11 - tmp10;", "op")
    r = equiv.test_function(EXACT_SID, EXACT_VA, opts("--src", path))
    assert r["verdict"] == "FAIL", r
    assert r["first_mismatch"]["observable"].startswith("memory"), r


def test_changed_constant_fails():
    # first pass only, ~2 ulp: 0.541196100f -> 0.5411962f
    path = mutant("((float)0.541196100)", "((float)0.5411962)", "const")
    r = equiv.test_function(EXACT_SID, EXACT_VA, opts("--src", path))
    assert r["verdict"] == "FAIL", r


def test_real_nonmatching_get_a_verdict():
    for sid, va in (("s00f7d9d0", 0x00f7d9d0), ("s0116c750", 0x0116c750), ("s010b48b0", 0x010b48b0)):
        r = equiv.test_function(sid, va, equiv.parse_args(["x", "--inputs", "60", "--time-limit", "25"]))
        assert r["verdict"] in ("PASS", "WEAK", "FAIL", "UNSUPPORTED"), r
        assert r["reason"]
