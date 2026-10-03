# Free cdecl wrapper forwarding to a thiscall member with one argument:
#   mov eax,[esp+4] ; mov ecx,[esp+8] ; push eax ; call C::m ; ret
# Source: "void f(int a, C* p) { p->m(a); }" under plain /O2 (callee non-inline, external).
# If the stack offsets are swapped, the object pointer is the first parameter.
# The rel32 call target is a relocation (masked); callee class/method named after the target VA.
import os, struct
import pefile
_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase

PATTERN = "mov eax, dword ptr [esp + N] ; mov ecx, dword ptr [esp + N] ; push eax ; call EXT ; ret "
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    t = "%08x" % va
    rel = struct.unpack("<i", _pe.get_data(va + 9 - _base + 1, 4))[0]
    tgt = "%08x" % ((va + 14 + rel) & 0xffffffff)
    cls = "C_%s_%s" % (t, tgt)
    if N[:2] == [8, 4]:
        src = ("struct %s { void FUN_%s(int); };\n"
               "void FUN_%s(%s* p, int a) { p->FUN_%s(a); }") % (cls, tgt, t, cls, tgt)
        sym = "?FUN_%s@@YAXPAU%s@@H@Z" % (t, cls)
    else:
        src = ("struct %s { void FUN_%s(int); };\n"
               "void FUN_%s(int a, %s* p) { p->FUN_%s(a); }") % (cls, tgt, t, cls, tgt)
        sym = "?FUN_%s@@YAXHPAU%s@@@Z" % (t, cls)
    return src, sym
