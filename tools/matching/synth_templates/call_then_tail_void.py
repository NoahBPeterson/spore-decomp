# void f() { a(); b(); } with both void() cdecl: call a; jmp b (second is a tail call). Targets read from the binary.
import os, struct
import pefile
_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase

PATTERN = 'call EXT ; jmp EXT'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    b = _pe.get_data(va - _base, 10)
    t1 = (va + 5 + struct.unpack("<i", b[1:5])[0]) & 0xffffffff
    t2 = (va + 10 + struct.unpack("<i", b[6:10])[0]) & 0xffffffff
    src = "void FUN_%08x();\nvoid FUN_%08x();\nvoid FUN_%08x() { FUN_%08x(); FUN_%08x(); }" % (t1, t2, va, t1, t2)
    return src, "?FUN_%08x@@YAXXZ" % va
