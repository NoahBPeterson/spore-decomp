# cdecl f(a, b) { callee(a, b, K1, K2); return a; }  (callee cdecl, result ignored)
# /O2: mov eax,[esp+8]; push esi; mov esi,[esp+8]; push K2; push K1; push eax; push esi; call; add esp,16; mov eax,esi
import os, struct
import pefile

_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase

def _callee(va):
    rel = struct.unpack("<i", _pe.get_data(va + 0x10 - _base, 4))[0]
    return va + 0x14 + rel

PATTERN = 'mov eax, dword ptr [esp + N] ; push esi ; mov esi, dword ptr [esp + N] ; push N ; push N ; push eax ; push esi ; call EXT ; add esp, N ; mov eax, esi ; pop esi ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    tgt = _callee(va)
    k2, k1 = N[2], N[3]
    src = ("void __cdecl FUN_%08x(void*, void*, int, int);\n"
           "void* FUN_%08x(void* a, void* b) { FUN_%08x(a, b, %d, %d); return a; }" % (tgt, va, tgt, k1, k2))
    return src, "?FUN_%08x@@YAPAXPAX0@Z" % va
