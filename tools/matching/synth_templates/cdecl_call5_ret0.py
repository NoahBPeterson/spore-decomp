# int f() { ext(a,b,c,d,e); return 0; } cdecl /O2 (openssl ERR_put_error stubs).
import os, struct
import pefile

_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase

def _callee(va):
    rel = struct.unpack("<i", _pe.get_data(va + 14 - _base, 4))[0]
    return va + 18 + rel

PATTERN = 'push N ; push N ; push N ; push N ; push N ; call EXT ; add esp, N ; xor eax, eax ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    tgt = _callee(va)
    a = N[4::-1]
    src = ("void __cdecl FUN_%08x(int,int,int,int,int);\n"
           "int FUN_%08x() { FUN_%08x(%d,%d,%d,%d,%d); return 0; }" % ((tgt, va, tgt) + tuple(a)))
    return src, "?FUN_%08x@@YAHXZ" % va
