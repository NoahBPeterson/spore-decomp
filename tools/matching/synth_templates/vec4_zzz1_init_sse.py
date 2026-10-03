# Dynamic initializer of a file-scope 4-float struct {0, 0, 0, c} (identity Quaternion style, c is
# usually __real@3f800000) in an /O2 /arch:SSE module:
#   xorps xmm0,xmm0; movss [g],xmm0; [g+4],xmm0; [g+8],xmm0; movss xmm0,[c]; movss [g+12],xmm0; ret
# /O2 folds a plain inline-ctor `Quaternion g(0,0,0,1)` into static data; volatile members keep
# all four stores in the ??__E initializer. Non-contiguous destinations or a non-.rdata constant
# fall back to a plain __cdecl function doing the stores in operand order.
import os, struct, math
import pefile
_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
def _f(a):
    if not (0x13cc000 <= a < 0x13cc000 + 0x13f5ae):  # only .rdata holds __real@ constants
        return None
    try:
        v = struct.unpack("<f", _pe.get_data(a - _pe.OPTIONAL_HEADER.ImageBase, 4))[0]
    except Exception:
        return None
    if math.isnan(v) or math.isinf(v) or v == 0.0:
        return None
    s = repr(v)
    if "e" not in s and "." not in s:
        s += ".0"
    if float(s) != v or struct.pack("<f", float(s)) != struct.pack("<f", v):
        return None
    return s + "f"

PATTERN = 'xorps xmm0, xmm0 ; movss dword ptr [A], xmm0 ; movss dword ptr [A], xmm0 ; movss dword ptr [A], xmm0 ; movss xmm0, dword ptr [A] ; movss dword ptr [A], xmm0 ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/arch:SSE"]
PRELUDE = """struct Vector4V {
    volatile float x, y, z, w;
    Vector4V(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {}
};
"""
def emit(va, A, N):
    d0, d1, d2, c, d3 = A
    val = _f(c)
    if val is not None and (d1, d2, d3) == (d0 + 4, d0 + 8, d0 + 12):
        return ("Vector4V g_%08x(0.0f, 0.0f, 0.0f, %s);" % (d0, val), "??__Eg_%08x@@YAXXZ" % d0)
    decl = "".join("extern float g_%08x;\n" % a for a in sorted({d0, d1, d2, d3}))
    decl += "extern const float g_%08x;\n" % c
    return (decl + "void FUN_%08x() { g_%08x = 0.0f; g_%08x = 0.0f; g_%08x = 0.0f; g_%08x = g_%08x; }"
            % (va, d0, d1, d2, d3, c)), "?FUN_%08x@@YAXXZ" % va
