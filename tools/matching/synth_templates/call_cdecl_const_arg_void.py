# void* f() { return callee(&g); } cdecl, /O2: push imm; call callee; add esp,4; ret (Ghidra says void but the callee result is passed through in eax; with return the ret is preceded by add esp,4, void gives pop ecx).
# Callee address decoded from the call at +5.
import os, struct
import pefile

_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase

def _callee(va):
    rel = struct.unpack("<i", _pe.get_data(va + 6 - _base, 4))[0]
    return va + 10 + rel

PATTERN = "push A ; call EXT ; add esp, N ; ret "
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    tgt = _callee(va)
    src = ("extern char g_%08x;\nvoid* __cdecl FUN_%08x(void*);\n"
           "void* FUN_%08x() { return FUN_%08x(&g_%08x); }" % (A[0], tgt, va, tgt, A[0]))
    return src, "?FUN_%08x@@YAPAXXZ" % va
