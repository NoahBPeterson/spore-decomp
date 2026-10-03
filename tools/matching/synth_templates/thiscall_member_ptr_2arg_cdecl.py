# Thiscall member forwarding two stack args to a cdecl free function with the pointer member at [this+N]:
#   mov eax,[esp+8]; mov edx,[esp+4]; push eax; mov eax,[ecx+N]; push edx; push eax; call g; add esp,12; ret 8
# Source: "void C::f(int a, int b) { g(p, a, b); }" with g a non-inline cdecl (void*,int,int), /O2.
import os, struct
import pefile
_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase

PATTERN = 'mov eax, dword ptr [esp + N] ; mov edx, dword ptr [esp + N] ; push eax ; mov eax, dword ptr [ecx + N] ; push edx ; push eax ; call EXT ; add esp, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = ""

def emit(va, A, N):
    n = N[2]
    t = "%08x" % va
    off = 0x11 if n >= 0x80 else 0xe
    rel = struct.unpack("<i", _pe.get_data(va - _base + off + 1, 4))[0]
    tgt = "%08x" % ((va + off + 5 + rel) & 0xffffffff)
    pad = " unsigned pad[%d];" % (n // 4) if n else ""
    src = ("struct T_%s;\nvoid __cdecl FUN_%s(T_%s*, int, int);\n"
           "struct C_%s {%s T_%s* p; void FUN_%s(int a, int b); };\n"
           "void C_%s::FUN_%s(int a, int b) { FUN_%s(p, a, b); }") % (t, tgt, t, t, pad, t, t, t, t, tgt)
    return src, "?FUN_%s@C_%s@@QAEXHH@Z" % (t, t)
