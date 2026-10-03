# __thiscall member forwarding to another thiscall callee on the same this (ecx live, so not tail jmp):
#  ret 0xc: f(a,b,c) { this->g(b,a,c); }    ret 8: f(a,b) { this->g(a,b,b) (b volatile); }
import os, struct
import pefile

_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase

def _callee(va):
    rel = struct.unpack("<i", _pe.get_data(va + 0x11 - _base, 4))[0]
    return (va + 0x15 + rel) & 0xffffffff

PATTERN = 'mov eax, dword ptr [esp + N] ; mov edx, dword ptr [esp + N] ; push eax ; mov eax, dword ptr [esp + N] ; push edx ; push eax ; call EXT ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    if N[-1] == 8:
        src = ("struct C_%08x { void ext(int, int, int); void FUN_%08x(int a, volatile int b); };\n"
               "void C_%08x::FUN_%08x(int a, volatile int b) { ext(a, b, b); }" % (va, va, va, va))
        return src, "?FUN_%08x@C_%08x@@QAEXHH@Z" % (va, va)
    src = ("struct C_%08x { void ext(int, int, int); void FUN_%08x(int a, int b, int c); };\n"
           "void C_%08x::FUN_%08x(int a, int b, int c) { ext(b, a, c); }" % (va, va, va, va))
    return src, "?FUN_%08x@C_%08x@@QAEXHHH@Z" % (va, va)
