# EASTL-style sort(first,last,cmp) where cmp is a plain 4-byte scalar passed through (kept in ebx, ebp/edi/esi alloc).
# Element size = 1<<N[2]; callees read from the rel32 calls.
import os
import pefile
_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase

PATTERN = 'push ebp ; mov ebp, dword ptr [esp + N] ; push edi ; mov edi, dword ptr [esp + N] ; cmp edi, ebp ; je +N ; push esi ; mov esi, ebp ; sub esi, edi ; sar esi, N ; mov eax, esi ; xor ecx, ecx ; test eax, eax ; je +N ; mov edi, edi ; sar eax, N ; inc ecx ; test eax, eax ; jne +N ; push ebx ; mov ebx, dword ptr [esp + N] ; push ebx ; lea eax, [ecx + ecx - N] ; push eax ; push ebp ; push edi ; call EXT ; add esp, N ; cmp esi, N ; push ebx ; jle +N ; lea esi, [edi + N] ; push esi ; push edi ; call EXT ; push ebx ; push ebp ; push esi ; call EXT ; add esp, N ; pop ebx ; pop esi ; pop edi ; pop ebp ; ret  ; push ebp ; push edi ; call EXT ; add esp, N ; pop ebx ; pop esi ; pop edi ; pop ebp ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "inline int L2(int n){ int k=0; while(n){ n>>=1; ++k;} return k; }\n"

def _calls(va):
    import capstone
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    code = _pe.get_data(va - _base, 0x90)
    out = []
    for i in md.disasm(code, va):
        if i.mnemonic == "call":
            out.append(int(i.op_str, 0))
        if i.mnemonic == "ret" and len(out) >= 4:
            break
    return out

def emit(va, A, N):
    c = _calls(va)
    quick, ins, ung = c[0], c[1], c[2]
    t = "T_%08x" % va
    size = 1 << N[2]
    f = "FUN_%08x"
    src = ("struct %s { char d[%d]; };\n"
           "void %s(%s*, %s*, int, int);\n"
           "void %s(%s*, %s*, int);\n"
           "void %s(%s*, %s*, int);\n"
           "void FUN_%08x(%s* first, %s* last, int cmp) {\n"
           "    if (first != last) {\n"
           "        int lg = L2(last - first);\n"
           "        %s(first, last, lg * 2 - 2, cmp);\n"
           "        if (last - first > 28) {\n"
           "            %s(first, first + 28, cmp);\n"
           "            %s(first + 28, last, cmp);\n"
           "        } else %s(first, last, cmp);\n"
           "    }\n}\n") % (t, size, f % quick, t, t, f % ins, t, t, f % ung, t, t, va, t, t,
                              f % quick, f % ins, f % ung, f % ins)
    return src, "?FUN_%08x@@YAXPAU%s@@0H@Z" % (va, t)
