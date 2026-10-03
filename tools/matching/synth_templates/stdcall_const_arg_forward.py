# void f() { callee(IMM); } where callee is __stdcall (callee pops): push imm; call callee; ret
# Same bytes for a thiscall member forwarding ecx. Callee decoded from call at +2.
import os, struct
import pefile

_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase

def _callee(va):
    rel = struct.unpack("<i", _pe.get_data(va + 3 - _base, 4))[0]
    return va + 7 + rel

PATTERN = "push N ; call EXT ; ret "
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    tgt = _callee(va)
    src = ("void __stdcall FUN_%08x(int);\n"
           "void FUN_%08x() { FUN_%08x(%d); }" % (tgt, va, tgt, N[0]))
    return src, "?FUN_%08x@@YAXXZ" % va
