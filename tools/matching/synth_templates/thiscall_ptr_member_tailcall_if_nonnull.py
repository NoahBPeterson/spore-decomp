# "void C::f() { if (p) p->g(); }" -> mov ecx,[ecx+N]; test; je; jmp g; ret
import os, struct
import pefile
_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase

PATTERN = 'mov ecx, dword ptr [ecx + N] ; test ecx, ecx ; je +N ; jmp EXT ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = ""

def emit(va, A, N):
    n = N[0]
    t = "%08x" % va
    ilen = 3 if n < 0x80 else 6
    off = ilen + 4
    b = _pe.get_data(va - _base + off, 5)
    tgt = ("%08x" % ((va + off + 5 + struct.unpack("<i", b[1:5])[0]) & 0xffffffff)) if b[0] == 0xE9 else t + "_tgt"
    pad = " char pad[%d];" % n if n else ""
    src = ("struct M_%s_%s { void FUN_%s(); };\n"
           "struct C_%s {%s M_%s_%s* p; void FUN_%s(); };\n"
           "void C_%s::FUN_%s() { if (p) p->FUN_%s(); }") % (t, tgt, tgt, t, pad, t, tgt, t, t, t, tgt)
    return src, "?FUN_%s@C_%s@@QAEXXZ" % (t, t)
