# Thunk calling a thiscall member on a global object with arg -1:
#   push -1 ; mov ecx, offset g ; call C::m ; ret
# Source: "extern C g; void f() { g.m(-1); }" under /O2 (callee external).
import os, struct
import pefile
_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase

PATTERN = "push -N ; mov ecx, A ; call EXT ; ret "
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    t = "%08x" % va
    rel = struct.unpack("<i", _pe.get_data(va + 7 - _base + 1, 4))[0]
    tgt = "%08x" % ((va + 12 + rel) & 0xffffffff)
    cls = "C_%s" % tgt
    g = "g_%08x" % A[0]
    src = ("#ifndef D_%s\n#define D_%s\nstruct %s { void FUN_%s(int); };\n#endif\nextern %s %s;\n"
           "void FUN_%s() { %s.FUN_%s(-1); }") % (tgt, tgt, cls, tgt, cls, g, t, g, tgt)
    return src, "?FUN_%s@@YAXXZ" % t
