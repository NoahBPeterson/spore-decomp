"""Which declaration a '// @ 0x' marker names (resolve.source_annotations)."""
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import resolve as R   # noqa: E402


def annots(tmp_path, text):
    p = tmp_path / "t.cpp"
    p.write_text(text)
    return {a[0]: a[2] for a in R.source_annotations([str(p)])}


def test_marker_skips_externs_above_its_definition(tmp_path):
    # s013ac650: the extern took the function's marker and the hybrid recursed into itself
    got = annots(tmp_path, "// @ 0x013B52D0\nextern float FUN_010c9050();\nextern float g_015ba2d8;\n"
                           "void FUN_013b52d0() {\n    g_015ba2d8 = FUN_010c9050();\n}\n")
    assert got.get("FUN_013b52d0") == 0x13B52D0
    assert "FUN_010c9050" not in got


def test_marker_names_an_extern_followed_by_the_next_marker(tmp_path):
    # s011b1520: marker / extern pairs for callees
    got = annots(tmp_path, "// @ 0x01180d50\nextern \"C\" void ERR_put_error(int lib);\n"
                           "// @ 0x01183410\nextern \"C\" void* CRYPTO_malloc(int num);\n")
    assert got == {"ERR_put_error": 0x1180D50, "CRYPTO_malloc": 0x1183410}


def test_marker_names_an_extern_followed_by_other_code(tmp_path):
    # s0108e080: the marker is the extern's, the next definition is unrelated
    got = annots(tmp_path, "// @ 0x0107f530\nextern void hkArrayUtil_reserveMore(void* a, int n);\n\n"
                           "class hkVector4 { public: float m_x; };\nvoid Other() {\n}\n")
    assert got.get("hkArrayUtil_reserveMore") == 0x107F530


def test_marker_naming_the_extern_keeps_it(tmp_path):
    # s0108e080: the marker comment spells the extern's name; a static helper follows
    got = annots(tmp_path, "// @ 0x01080e40  hkMath::equal(float a, float b, float eps)\n"
                           "extern bool hkMath_equal(float a, float b, float eps);\n\n"
                           "static float hkAbsF(float v) { return v < 0.0f ? -v : v; }\n")
    assert got.get("hkMath_equal") == 0x1080E40
