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


# ---------------------------------------------------------------------- hybrid-found blind spots (2026-10-12)

def test_untouched_register_clobber_fails():
    # InterpRamp: instruction-for-instruction equivalent but wrote xmm3, which the original never touches; its
    # LTCG caller kept a live value there (crackling audio in the hybrid). The source was fixed on 2026-10-18,
    # so the clobber is put back as a mutant.
    src = os.path.join(ROOT, "src", "game", "SPBake", "Tessellator.cpp")
    text = open(src).read()
    head = "PosDst InterpRamp(u32 pos, s32 step, u32 end, const f32* src, f32* dst)\n{\n"
    assert head in text
    text = text.replace(head, head + "    __asm xorps xmm3, xmm3\n")
    path = os.path.join(ROOT, "src", "game", "SPBake", "_mut_xmm3_Tessellator.cpp")
    open(path, "w").write(text)
    try:
        r = equiv.test_function("s0114da70", 0x0114e780, opts("--src", path))
    finally:
        os.remove(path)
    assert r["verdict"] == "FAIL", r
    assert r["first_mismatch"]["observable"].startswith("xmm3"), r


def test_fake_call_argument_order_fails():
    # cViewer::SetRaster: the renderer virtual takes (handle0, handle1, &rect); the old source
    # passed (&rect, handle0, handle1) and PASSed because fake-call arguments were not compared.
    src = os.path.join(ROOT, "match", "slices", "s007c4be0", "s007c4be0.cpp")
    text = open(src).read()
    old = "r2->v20(handle[0], handle[1], rect);"
    assert old in text
    text = text.replace(old, "r2->v20(rect, handle[0], handle[1]);")
    text = text.replace("virtual void v20(int a, int b, int* out);", "virtual void v20(int* out, int a, int b);")
    os.makedirs(MUT_DIR, exist_ok=True)
    path = os.path.join(MUT_DIR, "s007c4be0_argorder.cpp")
    open(path, "w").write(text)
    r = equiv.test_function("s007c4be0", 0x007c4be0, opts("--src", path))
    assert r["verdict"] == "FAIL" and r["first_mismatch"]["observable"].startswith("fake call"), r
    r = equiv.test_function("s007c4be0", 0x007c4be0, opts())
    assert r["verdict"] in ("PASS", "WEAK") and not r["mismatches"], r


def test_void_declaration_hiding_eax_return_fails():
    # rw::audio pop-front leaf: returns the popped node in eax; declared void it handed callers the
    # list pointer (black window in the hybrid). The harness now compares eax when the original
    # writes it before every ret, whatever the declaration says.
    import re
    src = os.path.join(ROOT, "match", "slices", "s01140b70", "s01140b70.cpp")
    text = open(src).read()
    s = text.index('extern "C" int* FUN_01141200(int* list)')
    e = text.index("\n}\n", s) + 3
    body = re.sub(r"return [^;]+;", "return;", text[s:e].replace("int* FUN_01141200", "void FUN_01141200"))
    text = (text[:s] + body + text[e:]).replace('extern "C" int* FUN_01141200(int* list);', 'extern "C" void FUN_01141200(int* list);')
    os.makedirs(MUT_DIR, exist_ok=True)
    path = os.path.join(MUT_DIR, "s01140b70_void.cpp")
    open(path, "w").write(text)
    r = equiv.test_function("s01140b70", 0x01141200, opts("--src", path))
    assert r["verdict"] == "FAIL" and r["first_mismatch"]["observable"] == "eax", r
    assert r["void_hides_eax"] is True, r


def test_ret_n_mismatch_fails():
    # `ret 4` vs the original's `ret` unbalances the caller's stack; the esp observable catches it. The slice the
    # test first used (LowerBound1c 0x0056fe60) was fixed on 2026-10-19, so the byte-exact cdecl jpeg_fdct_float
    # is made __stdcall as a mutant.
    src = os.path.join(ROOT, "match", "slices", EXACT_SID, EXACT_SID + ".cpp")
    text = open(src).read()
    assert "void jpeg_fdct_float(float* data)" in text
    os.makedirs(MUT_DIR, exist_ok=True)
    path = os.path.join(MUT_DIR, EXACT_SID + "_stdcall.cpp")
    open(path, "w").write(text.replace("void jpeg_fdct_float(float* data)", "void __stdcall jpeg_fdct_float(float* data)"))
    r = equiv.test_function(EXACT_SID, EXACT_VA, opts("--src", path))
    assert r["verdict"] == "FAIL" and r["first_mismatch"]["observable"] in ("esp", "eax"), r


# ---------------------------------------------------------------------- audit binding (2026-10-29 calibration)

def test_own_global_definition_is_bound_to_the_image():
    # InitSpatialObjectAttributes (byte-exact) initialises `Attribute gSpatialObjectAttributes[25]`, which its TU
    # defines: unbound, ours wrote a private copy and every input FAILed. resaudit.audit_bindings ties the
    # definition to the original's .data operand (0x0157a1f8).
    r = equiv.test_function("s01353d90", 0x01353d90, opts())
    assert r["verdict"] == "PASS", r
    assert [b["addr"] for b in r["audit_bound"]] == ["0157a1f8"], r


def test_own_global_binding_keeps_real_differences():
    # the same function with one attribute's name hash changed must still FAIL once the array is bound
    src = os.path.join(ROOT, "match", "slices", "s01353d90", "s01353d90.cpp")
    text = open(src).read()
    assert '"mIsInvalid", 0xd24b464b' in text
    os.makedirs(MUT_DIR, exist_ok=True)
    path = os.path.join(MUT_DIR, "s01353d90_hash.cpp")
    open(path, "w").write(text.replace('"mIsInvalid", 0xd24b464b', '"mIsInvalid", 0xd24b464c'))
    r = equiv.test_function("s01353d90", 0x01353d90, opts("--src", path))
    assert r["verdict"] == "FAIL" and r["first_mismatch"]["observable"].startswith("memory"), r


def test_cxx_throw_is_a_compared_outcome():
    """_CxxThrowException ends the run as a compared outcome (status "exit"), and the status names what was thrown:
    the first CatchableType's TypeDescriptor name and the exception object's bytes, with dwords that point into
    mapped memory reduced to "ptr". Two different thrown types or values give different statuses, so a run where
    the builds throw differently is a mismatch; before this, every throwing input was discarded (228 rows)."""
    import struct
    import machine as M
    import resolve as R
    m = M.Machine(R.Image())
    buf = m.model_data("test_throw", 0x1000)

    def throw(name, words):
        m.write(buf, b"\0" * 0x400)
        td, ct, cta, ti, obj = buf, buf + 0x100, buf + 0x140, buf + 0x180, buf + 0x200
        m.write(td + 8, name + b"\0")
        m.write(ct, struct.pack("<7I", 0, td, 0, 0xFFFFFFFF, 0, 4 * len(words), 0))
        m.write(cta, struct.pack("<2I", 1, ct))
        m.write(ti, struct.pack("<4I", 0, 0, 0, cta))
        m.write(obj, struct.pack("<%dI" % len(words), *words))
        try:
            m.handlers["_CxxThrowException"]["fn"](m, [obj, ti], 0)
        except M.Exit as e:
            return str(e)
        assert False, "the throw returned"

    a = throw(b".?AVcError@ArgScript@EA@@", [8, 0x21, buf])
    assert a == "C++ throw .?AVcError@ArgScript@EA@@ [00000008 00000021 ptr]", a
    assert throw(b".?AVcError@ArgScript@EA@@", [9, 0x21, buf]) != a          # another value
    assert throw(b".?AVbad_alloc@std@@", [8, 0x21, buf]) != a                # another type
    assert throw(b".?AVcError@ArgScript@EA@@", [8, 0x21, buf + 0x40]) == a   # a pointer's address does not matter


def _slice_mutant(sid, old, new, tag):
    src = os.path.join(ROOT, "match", "slices", sid, sid + ".cpp")
    text = open(src).read()
    assert old in text, old
    os.makedirs(MUT_DIR, exist_ok=True)
    path = os.path.join(MUT_DIR, "%s_%s.cpp" % (sid, tag))
    open(path, "w").write(text.replace(old, new, 1))
    return path


def test_cdecl_libm_runs_the_library_function():
    """Vec3_AngleBetween 0x00454aa0 (/Od) calls acos(double); the original calls _CIacos (argument in st0). Alignment
    bound our _acos to the image's _CIacos, which read an empty x87 stack (FAIL on x87 depth). The C symbol now runs
    the acos handler (method crt-model) and the pure math call is not part of the import trace: PASS. asin in its
    place must still FAIL."""
    r = equiv.test_function("s00454330", 0x00454aa0, opts())
    assert r["verdict"] == "PASS", r
    path = _slice_mutant("s00454330", "return (float)acos(d);", "return (float)asin(d);", "asin")
    assert equiv.test_function("s00454330", 0x00454aa0, opts("--src", path))["verdict"] == "FAIL"


def test_memset_fill_is_compared_as_a_byte():
    """memset converts its fill to unsigned char: the original pushes 0x200 (a count's leftover in the upper bytes),
    ours 0, and both fill with 0 (s005e6b40 0x005e7390 was FAIL on import call #0). A different fill byte FAILs."""
    r = equiv.test_function("s005e6b40", 0x005e7390, opts())
    assert r["verdict"] in ("PASS", "WEAK") and not r.get("mismatches"), r      # PASS with the sweep's input count
    path = _slice_mutant("s005e6b40", "memset(p, fill, count);", "memset(p, fill ^ 1, count);", "fill")
    assert equiv.test_function("s005e6b40", 0x005e7390, opts("--src", path))["verdict"] == "FAIL"
