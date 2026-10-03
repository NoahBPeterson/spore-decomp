# Two C++ EH unwind funclets (cdecl call: 4 zero args, string literal, saved frame slot [ebp-N]) back to
# back, then the __ehhandler stub (mov eax, ehfuncinfo; jmp handler). Emitted as naked inline asm
# (shape-equivalent); call/jmp targets and frame offsets are decoded from the original bytes.
import os, struct
import pefile
_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase

PATTERN = 'push N ; push N ; push N ; push N ; push A ; mov eax, dword ptr [ebp - N] ; push eax ; call EXT ; add esp, N ; ret  ; push N ; push N ; push N ; push N ; push A ; mov eax, dword ptr [ebp - N] ; push eax ; call EXT ; add esp, N ; ret  ; mov eax, A ; jmp EXT'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GS-"]
PRELUDE = ""

def _dec(va):
    b = _pe.get_data(va - _base, 96)
    r = []
    p = 0
    for _ in range(2):
        p += 13
        if b[p + 1] == 0x45:
            d = struct.unpack("<b", b[p + 2:p + 3])[0]; p += 3
        else:
            d = struct.unpack("<i", b[p + 2:p + 6])[0]; p += 6
        p += 1
        t = (va + p + 5 + struct.unpack("<i", b[p + 1:p + 5])[0]) & 0xffffffff
        p += 5 + 3 + 1
        r.append((d, t))
    p += 5
    r.append((None, (va + p + 5 + struct.unpack("<i", b[p + 1:p + 5])[0]) & 0xffffffff))
    return r

def emit(va, A, N):
    f = _dec(va)
    ext = "".join("extern \"C\" void X_%08x();\n" % x for x in dict.fromkeys(t for _, t in f))
    for a in dict.fromkeys(A[:3]):
        ext += "extern \"C\" char g_%08x[];\n" % a
    lines = ""
    for i in range(2):
        d, t = f[i]
        lines += "        push 0\n" * 4
        lines += "        push offset g_%08x\n        mov eax, dword ptr [ebp - %d]\n        push eax\n" % (A[i], -d)
        lines += "        call X_%08x\n        add esp, 18h\n        ret\n" % t
    lines += "        mov eax, offset g_%08x\n        jmp X_%08x\n" % (A[2], f[2][1])
    return "%s__declspec(naked) void FUN_%08x() {\n    __asm {\n%s    }\n}" % (ext, va, lines), "?FUN_%08x@@YAXXZ" % va
