# C++ EH unwind funclet (cdecl call with 4 zero args, a string literal and a saved frame slot [ebp+N])
# followed by its __ehhandler stub (mov eax, ehfuncinfo; jmp handler). Funclets run on the parent's ebp,
# so instances are emitted as naked inline asm; call/jmp targets and addresses are masked relocations.
import os, struct
import pefile
_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase

PATTERN = 'push N ; push N ; push N ; push N ; push A ; mov eax, dword ptr [ebp + N] ; push eax ; call EXT ; add esp, N ; ret  ; mov eax, A ; jmp EXT'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GS-"]
PRELUDE = ""

def _tgt(va):
    b = _pe.get_data(va - _base, 40)
    c = 17
    t1 = (va + c + 5 + struct.unpack("<i", b[c + 1:c + 5])[0]) & 0xffffffff
    j = 27 + 5
    t2 = (va + j + 5 + struct.unpack("<i", b[j + 1:j + 5])[0]) & 0xffffffff
    return t1, t2

def emit(va, A, N):
    t1, t2 = _tgt(va)
    ext = "extern \"C\" void X_%08x();\n" % t1
    if t2 != t1:
        ext += "extern \"C\" void X_%08x();\n" % t2
    ext += "extern \"C\" char g_%08x[];\nextern \"C\" char g_%08x[];\n" % (A[0], A[1])
    lines = "        push 0\n" * 4
    lines += "        push offset g_%08x\n        mov eax, dword ptr [ebp + %d]\n        push eax\n" % (A[0], N[4])
    lines += "        call X_%08x\n        add esp, 18h\n        ret\n" % t1
    lines += "        mov eax, offset g_%08x\n        jmp X_%08x\n" % (A[1], t2)
    src = "%s__declspec(naked) void FUN_%08x() {\n    __asm {\n%s    }\n}" % (ext, va, lines)
    return src, "?FUN_%08x@@YAXXZ" % va
