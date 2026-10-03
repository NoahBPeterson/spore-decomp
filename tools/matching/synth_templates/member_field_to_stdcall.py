# Member function passing one of its fields to a __stdcall free function:
#   mov eax,[ecx+N]; push eax; call g; ret   (callee pops, so no add esp)
# Source: "void C::f() { g(field); }" with "void __stdcall g(int)" under /O2.
import os, struct
import pefile
_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase

PATTERN = 'mov eax, dword ptr [ecx + N] ; push eax ; call EXT ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    t = "%08x" % va
    rel = struct.unpack("<i", _pe.get_data(va + 5 - _base, 4))[0]
    tgt = "%08x" % ((va + 9 + rel) & 0xffffffff)
    off = N[0]
    src = ("void __stdcall FUN_%s(int);\n"
           "struct C_%s { char pad[%d]; int f; void FUN_%s(); };\n"
           "void C_%s::FUN_%s() { FUN_%s(f); }") % (tgt, t, off, t, t, t, tgt)
    return src, "?FUN_%s@C_%s@@QAEXXZ" % (t, t)
