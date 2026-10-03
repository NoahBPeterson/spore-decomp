# Member fn forwarding to a thiscall method on a sub-object at this+off with (string-literal/global addr, arg):
#   mov eax,[esp+4]; push eax; push A; add ecx,off; call EXT; ret 4
# Source: struct O { char pad[off]; S s; void f(int a){ s.m((const char*)A, a); } };
import os, struct
import pefile
_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase

PATTERN = "mov eax, dword ptr [esp + N] ; push eax ; push A ; add ecx, N ; call EXT ; ret N"
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    t = "%08x" % va
    rel = struct.unpack("<i", _pe.get_data(va + 0xe - _base + 1, 4))[0]
    tgt = "%08x" % ((va + 0x12 + rel) & 0xffffffff)
    off = N[1]
    src = ("struct S_%s { void FUN_%s(const char*, int); };\n"
           "struct O_%s { char pad[%d]; S_%s s; void FUN_%s(int a) { s.FUN_%s((const char*)0x%x, a); } };\n"
           "void (O_%s::*fp_%s)(int) = &O_%s::FUN_%s;\n") % (t, tgt, t, off, t, t, tgt, A[0], t, t, t, t)
    return src, "?FUN_%s@O_%s@@QAEXH@Z" % (t, t)
