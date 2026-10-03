# Dynamic initializer of a file-scope float "sqrtf(k1 / (src * k2))", /O2 /fp:fast (x87):
#   fld dword [src] ; fmul dword [__real@k2] ; fdivr dword [__real@k1] ; fsqrt ; fstp dword [dst] ; ret
# Source: "float dst = sqrtf(k1 / (src * k2));" with src an extern float (other TU); k1/k2 read
# from the image (spherical-harmonic normalization constants, e.g. sqrtf(3.0f / (pi * 4.0f))).
import os, struct, pefile
PATTERN = 'fld dword ptr [A] ; fmul dword ptr [A] ; fdivr dword ptr [A] ; fsqrt  ; fstp dword ptr [A] ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/fp:fast"]
PRELUDE = "#include <math.h>\n"
_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = None
def _img(va, n):
    global _pe
    if _pe is None:
        _pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
    return _pe.get_data(va - _pe.OPTIONAL_HEADER.ImageBase, n)
def _flt(va):
    v = struct.unpack("<f", _img(va, 4))[0]
    s = repr(v)
    if struct.unpack("<f", struct.pack("<f", float(s)))[0] != v or "inf" in s or "nan" in s:
        return "(*(const float*)\"%s\")" % "".join("\\x%02x" % c for c in _img(va, 4))
    if "e" not in s and "." not in s: s += ".0"
    return s + "f"
def emit(va, A, N):
    src, k2, k1, dst = A[0], A[1], A[2], A[3]
    s = ""
    if src != dst:
        s += "extern float g_%08x;\n" % src
    s += "float g_%08x = sqrtf(%s / (g_%08x * %s));" % (dst, _flt(k1), src, _flt(k2))
    return s, "??__Eg_%08x@@YAXXZ" % dst
