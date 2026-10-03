# Dynamic initializer of a file-scope 3-float vector (Vector3 g(x,y,z);) in an unoptimized
# /Od /Ob1 /arch:SSE module: inline ctor gets inlined, each float constant is loaded from
# its __real@ constant with movss and stored to the global.
import os, struct, math
import pefile
_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
def _f(a):
    if not (0x13cc000 <= a < 0x13cc000 + 0x13f5ae):  # only .rdata holds __real@ constants
        return None
    try:
        b = _pe.get_data(a - _pe.OPTIONAL_HEADER.ImageBase, 4)
        v = struct.unpack("<f", b)[0]
    except Exception:
        return None
    if math.isnan(v) or math.isinf(v):
        return None
    s = repr(v)
    if "e" not in s and "." not in s:
        s += ".0"
    return s + "f"

PATTERN = 'push ebp ; mov ebp, esp ; movss xmm0, dword ptr [A] ; movss dword ptr [A], xmm0 ; movss xmm0, dword ptr [A] ; movss dword ptr [A], xmm0 ; movss xmm0, dword ptr [A] ; movss dword ptr [A], xmm0 ; pop ebp ; ret '
FLAGS = ["/Od", "/Ob1", "/arch:SSE", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """struct Vector3 { float x, y, z; Vector3(float a, float b, float c) : x(a), y(b), z(c) {} };
"""
def emit(va, A, N):
    src, dst = A[0::2], A[1::2]
    vals = [_f(a) for a in src]
    if None not in vals and dst[1] == dst[0] + 4 and dst[2] == dst[0] + 8:
        return ("Vector3 g_%08x(%s, %s, %s);" % (dst[0], *vals)), "??__Eg_%08x@@YAXXZ" % dst[0]
    # Non-contiguous destinations, sources that are writable globals (.data), or NaN/inf: plain stores from float globals.
    decl = "".join("extern float g_%08x;\n" % a for a in sorted(set(A)))
    body = "".join("g_%08x = g_%08x; " % (d, s) for s, d in zip(src, dst))
    return decl + "void FUN_%08x() { %s}" % (va, body), "?FUN_%08x@@YAXXZ" % va
