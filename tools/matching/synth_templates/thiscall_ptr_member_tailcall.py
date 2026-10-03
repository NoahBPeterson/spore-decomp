# Pointer-member forwarding thunk: mov ecx,[ecx+N] ; jmp Member::g
# /O2 turns "void C::f() { p->g(); }" (p a pointer member at offset N, g a non-inline thiscall
# member with no stack args) into a this-reload + tail jump. The rel32 target is a relocation
# (masked); the callee class is named after the target VA.
import os, struct
import pefile
_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase

PATTERN = "mov ecx, dword ptr [ecx + N] ; jmp EXT"
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = ""

def emit(va, A, N):
    n = N[0]
    t = "%08x" % va
    ilen = 3 if n < 0x80 else 6
    b = _pe.get_data(va - _base + ilen, 5)
    tgt = ("%08x" % ((va + ilen + 5 + struct.unpack("<i", b[1:5])[0]) & 0xffffffff)) if b[0] == 0xE9 else t + "_tgt"
    pad = " char pad[%d];" % n if n else ""
    src = ("struct M_%s_%s { void FUN_%s(); };\n"
           "struct C_%s {%s M_%s_%s* p; void FUN_%s(); };\n"
           "void C_%s::FUN_%s() { p->FUN_%s(); }") % (t, tgt, tgt, t, pad, t, tgt, t, t, t, tgt)
    return src, "?FUN_%s@C_%s@@QAEXXZ" % (t, t)
