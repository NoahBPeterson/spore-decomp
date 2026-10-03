# C++ EH unwind funclet + __ehhandler with a positive frame offset (lea ecx,[ebp+N]; jmp X; mov eax,ehfuncinfo; jmp handler).
# The object lives above ebp (frame layout not derivable from ordinary source), so the instances are emitted
# as naked inline asm (shape-equivalent); jmp targets and the ehfuncinfo address are masked relocations.
import os, struct
import pefile
_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase

PATTERN = 'lea ecx, [ebp + N] ; jmp EXT ; mov eax, A ; jmp EXT'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GS-"]
PRELUDE = ""

def _tgt(va):
    b = _pe.get_data(va - _base, 24)
    out, p = [], 0
    for _ in range(2):
        if b[p] == 0x8d:
            p += 3 if b[p + 1] == 0x4d else 6
        else:
            p += 5
        out.append((va + p + 5 + struct.unpack("<i", b[p + 1:p + 5])[0]) & 0xffffffff)
        p += 5
    return out

def emit(va, A, N):
    t = _tgt(va)
    ext = "".join("extern \"C\" void X_%08x();\n" % x for x in dict.fromkeys(t))
    ext += "extern \"C\" char g_%08x[];\n" % A[0]
    lines = "        lea ecx, [ebp + %d]\n        jmp X_%08x\n" % (N[0], t[0])
    lines += "        mov eax, offset g_%08x\n        jmp X_%08x\n" % (A[0], t[1])
    src = "%s__declspec(naked) void FUN_%08x() {\n    __asm {\n%s    }\n}" % (ext, va, lines)
    return src, "?FUN_%08x@@YAXXZ" % va
