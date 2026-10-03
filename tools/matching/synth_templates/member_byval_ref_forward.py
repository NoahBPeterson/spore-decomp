# Thiscall method taking a by-value struct (ret N) that forwards a reference to it to a sub-object member:
#   void C::f(S s) { m.g(s); }  with g(const S&). /O2 gives lea eax,[esp+4]; push eax; add ecx,off; call; ret sizeof(S)
import os, struct
import pefile
_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase

PATTERN = "lea eax, [esp + N] ; push eax ; add ecx, N ; call EXT ; ret N"
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-", "/GS-"]
PRELUDE = ""

def emit(va, A, N):
    off, sz = N[1], N[2]
    t = "%08x" % va
    ilen = 3 if off < 0x80 else 6
    b = _pe.get_data(va - _base + 4 + ilen, 5)
    tgt = "%08x" % ((va + 4 + ilen + 5 + struct.unpack("<i", b[1:5])[0]) & 0xffffffff)
    pad = " char pad[%d];" % off if off else ""
    src = ("struct S_%s { int b[%d]; };\n"
           "struct M_%s_%s { void FUN_%s(const S_%s&); };\n"
           "struct C_%s {%s M_%s_%s m; void FUN_%s(S_%s); };\n"
           "void C_%s::FUN_%s(S_%s s) { m.FUN_%s(s); }") % (t, sz // 4, t, tgt, tgt, t, t, pad, t, tgt, t, t, t, t, t, tgt)
    return src, "?FUN_%s@C_%s@@QAEXUS_%s@@@Z" % (t, t, t)
