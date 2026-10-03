# C++ EH unwind funclets: lea ecx,[ebp+N0] (stack arg); jmp X0 ; lea ecx,[ebp-N1] (local); jmp X1 ;
# mov eax,__ehfuncinfo; jmp ___CxxFrameHandler3. Emitted as naked inline asm (shape-equivalent);
# jmp targets and ehfuncinfo address are masked relocations.
import os, struct
import pefile
_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase

PATTERN = 'lea ecx, [ebp + N] ; jmp EXT ; lea ecx, [ebp - N] ; jmp EXT ; mov eax, A ; jmp EXT'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GS-"]
PRELUDE = ""

def _dec(va):
    b = _pe.get_data(va - _base, 48)
    out, p = [], 0
    for _ in range(3):
        if b[p] == 0x8d:
            if b[p + 1] == 0x4d:
                d = struct.unpack("<b", b[p + 2:p + 3])[0]; p += 3
            else:
                d = struct.unpack("<i", b[p + 2:p + 6])[0]; p += 6
        else:
            d = None; p += 5
        out.append(((va + p + 5 + struct.unpack("<i", b[p + 1:p + 5])[0]) & 0xffffffff, d))
        p += 5
    return out

def emit(va, A, N):
    t = _dec(va)
    ext = "".join("extern \"C\" void X_%08x();\n" % x for x in dict.fromkeys(a for a, _ in t))
    ext += "extern \"C\" char g_%08x[];\n" % A[0]
    lines = ""
    for a, d in t[:2]:
        lines += "        lea ecx, [ebp %s %d]\n        jmp X_%08x\n" % ("+" if d >= 0 else "-", abs(d), a)
    lines += "        mov eax, offset g_%08x\n        jmp X_%08x\n" % (A[0], t[2][0])
    src = "%s__declspec(naked) void FUN_%08x() {\n    __asm {\n%s    }\n}" % (ext, va, lines)
    return src, "?FUN_%08x@@YAXXZ" % va
