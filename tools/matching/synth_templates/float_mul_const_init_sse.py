# Dynamic initializer of a file-scope float scaled by a float literal, /O2 /arch:SSE /fp:fast:
#   movss xmm0,[src] ; mulss xmm0,[__real@k] ; movss [dst],xmm0 ; ret
# Source: "float dst = src * k;" with src an extern float (other TU), k read from the image.
import os, struct, pefile
PATTERN = "movss xmm0, dword ptr [A] ; mulss xmm0, dword ptr [A] ; movss dword ptr [A], xmm0 ; ret "
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/arch:SSE", "/fp:fast"]
PRELUDE = ""
_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = None
def _f32(va):
    global _pe
    if _pe is None:
        _pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
    raw = _pe.get_data(va - _pe.OPTIONAL_HEADER.ImageBase, 4)
    return struct.unpack("<I", raw)[0]
def emit(va, A, N):
    src, k, dst = A[0], A[1], A[2]
    bits = _f32(k)
    v = struct.unpack("<f", struct.pack("<I", bits))[0]
    lit = "%.9gf" % v
    if "." not in lit and "e" not in lit and "inf" not in lit and "nan" not in lit:
        lit = lit[:-1] + ".0f"
    s = ""
    if src != dst:
        s += "extern float g_%08x;\n" % src
    s += "float g_%08x = g_%08x * %s;" % (dst, src, lit)
    return s, "??__Eg_%08x@@YAXXZ" % dst
