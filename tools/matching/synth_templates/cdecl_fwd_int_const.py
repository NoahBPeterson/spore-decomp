# cdecl wrapper: f(p) { callee(p, CONST); } with integer (possibly imm32) constant.
# Plain /O2: mov eax,[esp+4]; push imm; push eax; call; add esp,8; ret. Callee decoded from the call opcode.
import os, struct
import pefile

_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase

def _callee(va):
    d = _pe.get_data(va - _base, 24)
    i = d.index(b"\xe8")
    rel = struct.unpack("<i", d[i + 1:i + 5])[0]
    return va + i + 5 + rel

PATTERN = 'mov eax, dword ptr [esp + N] ; push N ; push eax ; call EXT ; add esp, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    tgt = _callee(va)
    src = ("void __cdecl FUN_%08x(void*, int);\n"
           "void FUN_%08x(void* p) { FUN_%08x(p, 0x%x); }" % (tgt, va, tgt, N[1]))
    return src, "?FUN_%08x@@YAXPAX@Z" % va
