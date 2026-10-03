# Bare __ehhandler$ stub of an EH function: mov eax,__ehfuncinfo$f ; jmp ___CxxFrameHandler3.
# The stub is a compiler-emitted tail (no own source function), so it is emitted as a naked function.
import os, struct
import pefile
_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase

PATTERN = 'mov eax, A ; jmp EXT'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GS-"]
PRELUDE = ""

def emit(va, A, N):
    b = _pe.get_data(va - _base, 10)
    t = (va + 10 + struct.unpack("<i", b[6:10])[0]) & 0xffffffff
    src = ("extern \"C\" void X_%08x();\nextern \"C\" char g_%08x[];\n"
           "__declspec(naked) void FUN_%08x() {\n    __asm {\n        mov eax, offset g_%08x\n        jmp X_%08x\n    }\n}"
           % (t, A[0], va, A[0], t))
    return src, "?FUN_%08x@@YAXXZ" % va
