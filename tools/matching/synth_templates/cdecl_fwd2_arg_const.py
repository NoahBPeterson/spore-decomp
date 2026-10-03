# cdecl wrapper: f(a, b) { callee(a, b, CONST); } (e.g. ASN1_item_i2d(x, &out, &item_template)).
# Plain /O2: mov eax,[esp+8]; mov ecx,[esp+4]; push imm; push eax; push ecx; call; add esp,0xc; ret.
# Callee address decoded from the call at +0xF.
import os, struct
import pefile

_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase

def _callee(va):
    rel = struct.unpack("<i", _pe.get_data(va + 16 - _base, 4))[0]
    return va + 20 + rel

PATTERN = 'mov eax, dword ptr [esp + N] ; mov ecx, dword ptr [esp + N] ; push A ; push eax ; push ecx ; call EXT ; add esp, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    tgt = _callee(va)
    src = ("void __cdecl FUN_%08x(void*, void*, void*);\n"
           "void FUN_%08x(void* a, void* b) { FUN_%08x(a, b, (void*)0x%x); }" % (tgt, va, tgt, A[0]))
    return src, "?FUN_%08x@@YAXPAX0@Z" % va
