# Three C++ EH unwind funclets + __ehhandler of a /GS- function (the .text$x tail of an EH function):
#   lea ecx,[ebp-N0]; jmp X0 ; lea ecx,[ebp-N1]; jmp X1 ; lea ecx,[ebp-N2]; jmp X2 ;
#   mov eax,__ehfuncinfo$f; jmp ___CxxFrameHandler3
# Three address-taken EH locals: cl /O2 frame layout is a heuristic (size / reference density) and the
# funclets may repeat an offset (member-of-inline-ctor + whole-object), so real source cannot be
# derived from offsets alone; instances are emitted as naked inline asm (shape-equivalent). The jmp
# targets and the ehfuncinfo address are masked relocations; displacement widths come from N.
import os, struct
import pefile
_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase

PATTERN = 'lea ecx, [ebp - N] ; jmp EXT ; lea ecx, [ebp - N] ; jmp EXT ; lea ecx, [ebp - N] ; jmp EXT ; mov eax, A ; jmp EXT'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GS-"]
PRELUDE = ""

def _tgt(va):
    # decode each jmp rel32 from the original bytes; funclets have variable lea length
    b = _pe.get_data(va - _base, 48)
    out, p = [], 0
    for _ in range(4):
        if b[p] == 0x8d:                      # lea ecx,[ebp-disp]
            p += 3 if b[p + 1] == 0x4d else 6
        else:                                 # mov eax, imm32
            p += 5
        out.append((va + p + 5 + struct.unpack("<i", b[p + 1:p + 5])[0]) & 0xffffffff)
        p += 5
    return out

def emit(va, A, N):
    t = _tgt(va)
    ext = "".join("extern \"C\" void X_%08x();\n" % x for x in dict.fromkeys(t))
    ext += "extern \"C\" char g_%08x[];\n" % A[0]
    lines = ""
    for i in range(3):
        lines += "        lea ecx, [ebp - %d]\n        jmp X_%08x\n" % (N[i], t[i])
    lines += "        mov eax, offset g_%08x\n        jmp X_%08x\n" % (A[0], t[3])
    src = "%s__declspec(naked) void FUN_%08x() {\n    __asm {\n%s    }\n}" % (ext, va, lines)
    return src, "?FUN_%08x@@YAXXZ" % va
