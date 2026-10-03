# this->s.m(this->s) where s is an 8-byte POD at [this+N], m a thiscall taking S by value.
import os, struct
import pefile
_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase

PATTERN = 'mov eax, dword ptr [ecx + N] ; mov edx, dword ptr [ecx + N] ; add ecx, N ; push eax ; push edx ; call EXT ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = ""

def emit(va, A, N):
    off = N[0] - 0 
    n = N[1]
    t = "%08x" % va
    callat = 0x0b if n < 0x80 else 0x14
    rel = struct.unpack("<i", _pe.get_data(va - _base + callat + 1, 4))[0]
    tgt = "%08x" % ((va + callat + 5 + rel) & 0xffffffff)
    pad = " unsigned pad[%d];" % (n // 4) if n else ""
    src = ("struct S_%s { int a; int b; void FUN_%s(S_%s); };\n"
           "struct C_%s {%s S_%s s; void FUN_%s(); };\n"
           "void C_%s::FUN_%s() { s.FUN_%s(s); }") % (t, tgt, t, t, pad, t, t, t, t, tgt)
    return src, "?FUN_%s@C_%s@@QAEXXZ" % (t, t)
