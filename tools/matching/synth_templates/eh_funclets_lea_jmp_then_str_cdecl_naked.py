# EH unwind funclets of a /GS- function: lea ecx,[ebp-N]; jmp X ; then a cdecl funclet
# (4 zero pushes, string literal, saved frame slot [ebp+-N], call, add esp 18h, ret) ; then more
# lea/jmp funclets ; __ehhandler stub (mov eax,ehfuncinfo; jmp ___CxxFrameHandler3).
# Decoded straight from the original bytes and emitted as naked inline asm (funclets run on the
# parent's ebp); jmp/call targets and addresses are masked relocations.
import os, struct
import pefile
_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase

PATTERN = 'lea ecx, [ebp - N] ; jmp EXT ; push N ; push N ; push N ; push N ; push A ; mov eax, dword ptr [ebp - N] ; push eax ; call EXT ; add esp, N ; ret  ; lea ecx, [ebp - N] ; jmp EXT ; mov eax, A ; jmp EXT'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GS-"]
PRELUDE = ""

def _s32(b): return struct.unpack("<i", b)[0]

def emit(va, A, N):
    b = _pe.get_data(va - _base, 96)
    p, lines, ext = 0, "", {}
    def X(t):
        ext[t] = 1
        return "X_%08x" % t
    gl = {}
    def G(a):
        gl[a] = 1
        return "g_%08x" % a
    while True:
        op = b[p]
        if op == 0x8d:
            if b[p + 1] == 0x4d: d, p = -(256 - b[p + 2]) if b[p + 2] > 127 else b[p + 2], p + 3
            else: d, p = _s32(b[p + 2:p + 6]), p + 6
            lines += "        lea ecx, [ebp %s %d]\n" % ("-" if d < 0 else "+", abs(d))
            t = (va + p + 5 + _s32(b[p + 1:p + 5])) & 0xffffffff; p += 5
            lines += "        jmp %s\n" % X(t)
        elif op == 0x6a:
            lines += "        push %d\n" % b[p + 1]; p += 2
        elif op == 0x68:
            lines += "        push offset %s\n" % G(struct.unpack("<I", b[p + 1:p + 5])[0]); p += 5
        elif op == 0x8b:
            if b[p + 1] == 0x45: d, p = struct.unpack("<b", b[p + 2:p + 3])[0], p + 3
            else: d, p = _s32(b[p + 2:p + 6]), p + 6
            lines += "        mov eax, dword ptr [ebp %s %d]\n" % ("-" if d < 0 else "+", abs(d))
        elif op == 0x50:
            lines += "        push eax\n"; p += 1
        elif op == 0xe8:
            t = (va + p + 5 + _s32(b[p + 1:p + 5])) & 0xffffffff; p += 5
            lines += "        call %s\n" % X(t)
        elif op == 0x83:
            lines += "        add esp, %d\n" % b[p + 2]; p += 3
        elif op == 0xc3:
            lines += "        ret\n"; p += 1
        elif op == 0xb8:
            lines += "        mov eax, offset %s\n" % G(struct.unpack("<I", b[p + 1:p + 5])[0]); p += 5
            t = (va + p + 5 + _s32(b[p + 1:p + 5])) & 0xffffffff; p += 5
            lines += "        jmp %s\n" % X(t)
            break
        else:
            raise Exception("op %x" % op)
    decl = "".join("extern \"C\" void X_%08x();\n" % t for t in ext)
    decl += "".join("extern \"C\" char g_%08x[];\n" % a for a in gl)
    src = "%s__declspec(naked) void FUN_%08x() {\n    __asm {\n%s    }\n}" % (decl, va, lines)
    return src, "?FUN_%08x@@YAXXZ" % va
