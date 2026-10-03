# EH unwind funclet "operator delete(ptr=[ebp-N], size)" (cdecl) + __ehhandler tail:
#   push SIZE ; mov eax,[ebp-N] ; push eax ; call X ; add esp,8 ; ret ; mov eax,ehfuncinfo ; jmp handler
# Funclet frame offsets are not derivable from ordinary source, so emitted as naked inline asm.
import os, struct
import pefile
_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase

PATTERN = 'push N ; mov eax, dword ptr [ebp - N] ; push eax ; call EXT ; add esp, N ; ret  ; mov eax, A ; jmp EXT'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GS-"]
PRELUDE = ""

def emit(va, A, N):
    b = _pe.get_data(va - _base, 40)
    p = 5 if b[0] == 0x68 else 2
    size = struct.unpack("<I", b[1:5])[0] if b[0] == 0x68 else b[1]
    p0 = p
    disp = struct.unpack("<i", b[p+2:p+6])[0] if b[p+1] == 0x85 else struct.unpack("<b", b[p+2:p+3])[0]
    p += 6 if b[p+1] == 0x85 else 3
    p += 1  # push eax
    c = (va + p + 5 + struct.unpack("<i", b[p+1:p+5])[0]) & 0xffffffff
    p += 5 + 3 + 1  # call, add esp,8, ret
    h = (va + p + 5 + struct.unpack("<i", b[p+6:p+10])[0] + 5) & 0xffffffff
    src = ("extern \"C\" void X_%08x();\nextern \"C\" void X_%08x();\nextern \"C\" char g_%08x[];\n"
           "__declspec(naked) void FUN_%08x() {\n    __asm {\n"
           "        push %d\n        mov eax, dword ptr [ebp%+d]\n        push eax\n        call X_%08x\n"
           "        add esp, 8\n        ret\n        mov eax, offset g_%08x\n        jmp X_%08x\n    }\n}"
           % (c, h, A[-1], va, size, disp, c, A[-1], h))
    return src, "?FUN_%08x@@YAXXZ" % va
