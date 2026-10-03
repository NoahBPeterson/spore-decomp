# void f() { callee((void*)ADDR, SMALL); } cdecl, /O2: push small; push addr; call; add esp,8; ret.
# Callee decoded from the call at +4 (after 2-byte push imm8 and 5-byte push imm32 -> call at +7).
import os, struct
import pefile

_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase

def _callee(va):
    rel = struct.unpack("<i", _pe.get_data(va + 8 - _base, 4))[0]
    return va + 12 + rel

PATTERN = 'push N ; push A ; call EXT ; add esp, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    tgt = _callee(va)
    src = ("void __cdecl FUN_%08x(void*, int);\n"
           "void FUN_%08x() { FUN_%08x((void*)0x%x, %d); }" % (tgt, va, tgt, A[0], N[0]))
    return src, "?FUN_%08x@@YAXXZ" % va
