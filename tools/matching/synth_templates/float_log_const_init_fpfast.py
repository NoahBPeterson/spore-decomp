# Dynamic initializer of a file-scope float set to the natural log of a literal, /O2 /fp:fast (x87,
# no /arch:SSE): fld qword [__real@k] ; fldln2 ; fxch st(1) ; fyl2x ; fstp dword [dst] ; ret
# Source: "float dst = logf(k);" (/fp:fast inlines log as fyl2x and does not constant-fold it).
# k is read from the image (double); emitted as a float literal when exactly representable.
import os, struct, pefile
PATTERN = "fld qword ptr [A] ; fldln2  ; fxch st(N) ; fyl2x  ; fstp dword ptr [A] ; ret "
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
    k, dst = A[0], A[1]
    v = _f64(k)
    f = struct.unpack("<f", struct.pack("<f", v))[0]
    if f == v:
        lit = "%.9gf" % v
        if "." not in lit and "e" not in lit:
            lit = lit[:-1] + ".0f"
        expr = "logf(%s)" % lit
    else:
        expr = "(float)log(%.17g)" % v
    return "float g_%08x = %s;" % (dst, expr), "??__Eg_%08x@@YAXXZ" % dst
