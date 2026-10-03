# Dynamic initializer "float dst = sqrtf(k) * src;" /O2 /fp:fast (x87):
#   fld qword [__real@k] ; fsqrt ; fmul dword [src] ; fstp dword [dst] ; ret
import os, struct, pefile
PATTERN = "fld qword ptr [A] ; fsqrt  ; fmul dword ptr [A] ; fstp dword ptr [A] ; ret "
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/fp:fast"]
PRELUDE = "#include <math.h>\n"
_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = None
def _f64(va):
    global _pe
    if _pe is None:
        _pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
    return struct.unpack("<d", _pe.get_data(va - _pe.OPTIONAL_HEADER.ImageBase, 8))[0]
def emit(va, A, N):
    k, src, dst = A[0], A[1], A[2]
    v = _f64(k)
    f = struct.unpack("<f", struct.pack("<f", v))[0]
    if f == v:
        lit = "%.9gf" % v
        if "." not in lit and "e" not in lit:
            lit = lit[:-1] + ".0f"
        expr = "sqrtf(%s)" % lit
    else:
        expr = "(float)sqrt(%.17g)" % v
    return ("extern float g_%08x;\nfloat g_%08x = %s * g_%08x;" % (src, dst, expr, src)), "??__Eg_%08x@@YAXXZ" % dst
