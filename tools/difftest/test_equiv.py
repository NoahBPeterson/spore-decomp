"""Self-tests for the equivalence harness (run: .venv/bin/python -m pytest tools/difftest/test_equiv.py).

(a) a byte-exact function from a slice manifest must PASS;
(b) the same source with one operator changed must FAIL;
(c) real nonmatching functions get a verdict (any of the four) without crashing;
(d) regressions for checker artifacts: argument-slot pointers, state leaking between runs, code
    writes, generated pointers into code, string literal mapping, extern "C" signatures, flags.
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


# ---------------------------------------------------------------------- harness-artifact regressions

ARG_SID, ARG_VA = "s00d00ee0", 0x00d01410      # RelBook::FindRel: find(&it, key) out-iterator
ARG_OLD = "RBNode* it;\n    t->find(&it, key);"


def arg_mutant(new, tag):
    src = os.path.join(ROOT, "match", "slices", ARG_SID, ARG_SID + ".cpp")
    text = open(src).read()
    assert ARG_OLD in text
    os.makedirs(MUT_DIR, exist_ok=True)
    path = os.path.join(MUT_DIR, "%s_%s.cpp" % (ARG_SID, tag))
    open(path, "w").write(text.replace(ARG_OLD, new, 1))
    return path


def test_argument_slot_pointer_is_a_stack_pointer():
    # the out-iterator lives in the function's own incoming 'b' slot (the original uses 'a's,
    # the old checker reported FAIL): only the pointer passed to find differs, not observable
    path = arg_mutant("t->find((RBNode**)&b, key);\n    RBNode* it = *(RBNode**)&b;", "argslot")
    r = equiv.test_function(ARG_SID, ARG_VA, opts("--src", path))
    assert r["verdict"] in ("PASS", "WEAK") and not r["mismatches"], r


def test_argument_slot_different_value_fails():
    # same, but a different value is written through the argument-slot pointer
    path = arg_mutant("t->find((RBNode**)&b, key);\n    *(char**)&b += 4;\n    RBNode* it = *(RBNode**)&b;",
                      "argslot_write")
    r = equiv.test_function(ARG_SID, ARG_VA, opts("--src", path))
    assert r["verdict"] == "FAIL", r


def test_state_is_restored_between_runs():
    import machine as M
    m = equiv.context()["m"]
    m.take_dirty()
    far = M.DYN_BASE + 0x01230000                 # beyond dyn_next: reached through a garbage index
    m.write(far, b"leak")
    m.write(M.MISC_BASE + 0x90000, b"leak")       # scratch part of MISC
    dyn, misc = m.take_dirty()
    assert far in dyn and (M.MISC_BASE + 0x90000) in misc
    assert m.read(far, 4) == b"\0\0\0\0"
    assert m.read(M.MISC_BASE + 0x90000, 4) == m.misc_baseline[0x90000:0x90004]
    # handler writes (memcpy) into code fault instead of patching it
    import pytest
    from unicorn import UcError
    with pytest.raises(UcError):
        m.write(0x006b709a, b"\x90" * 16)


def test_generated_values_avoid_code():
    t = equiv.prepare(EXACT_SID, EXACT_VA)
    runner = equiv.Runner(t, opts())
    try:
        g = runner.gen
        assert not any(lo <= v < hi for v in g.dic for lo, hi in g.code)
        v = g.fin(0x004b229e)                     # a jump target inside a function (an immediate)
        assert not any(lo <= v < hi for lo, hi in g.code)
    finally:
        runner.close()


def test_string_literal_mapping():
    img = equiv.context()["img"]
    assert img.rdata_find(b"Graphics\0") == 0x013eb8a4      # follows a float constant, no NUL before
    assert img.rdata_find(b":\0") == 0x013fe618             # not the ':' inside a UTF-16 string


def test_extern_c_signature():
    import sig as SIG
    text = open(os.path.join(ROOT, "match", "slices", "s010af750", "s010af750.cpp")).read()
    s = SIG.parse_c_decl("hkPoweredChain_ScanAndEnableMotors", [text])
    assert s.ret == "void" and s.params == [("ptr", 1)] * 3 and s.conv == "cdecl"


def test_flag_order():
    import slice as S
    # an explicit 'flags ...' note in the reason wins over loose tokens and comments
    f, how = S.choose_flags("s004604f0", 0x00460bf0)
    assert how == "reason" and "/Od" in f and "/fp:fast" in f
