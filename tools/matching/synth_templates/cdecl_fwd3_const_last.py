# cdecl wrapper: f(a, b, c) { callee(a, b, c, CONST); }
# Plain /O2: mov eax,[esp+c]; mov ecx,[esp+8]; mov edx,[esp+4]; push imm; push eax; push ecx; push edx; call; add esp,0x10; ret.
# Callee address decoded from the call at +0x11.
import os, struct
import pefile

_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase

def _callee(va):
    rel = struct.unpack("<i", _pe.get_data(va + 0x12 - _base, 4))[0]
    return va + 0x16 + rel

PATTERN = 'mov eax, dword ptr [esp + N] ; mov ecx, dword ptr [esp + N] ; mov edx, dword ptr [esp + N] ; push N ; push eax ; push ecx ; push edx ; call EXT ; add esp, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    tgt = _callee(va)
    src = ("void __cdecl FUN_%08x(void*, void*, void*, int);\n"
           "void FUN_%08x(void* a, void* b, void* c) { FUN_%08x(a, b, c, %d); }" % (tgt, va, tgt, N[3]))
    return src, "?FUN_%08x@@YAXPAX00@Z" % va
