# EASTL-style sort(first,last,compare): introsort quick_sort_impl(depth=2*log2(n)) then
# insertion_sort of first 28 elements + unguarded_insertion_sort of the rest (or insertion_sort if n<=28).
# Element size = 1<<N[2]; callee targets read from the rel32 calls (relocation-masked); compare is a 4-byte by-value arg.
import os, struct
import pefile
_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase

PATTERN = 'push ebx ; mov ebx, dword ptr [esp + N] ; push edi ; mov edi, dword ptr [esp + N] ; cmp edi, ebx ; je +N ; push esi ; mov esi, ebx ; sub esi, edi ; sar esi, N ; mov eax, esi ; xor ecx, ecx ; test eax, eax ; je +N ; mov edi, edi ; sar eax, N ; inc ecx ; test eax, eax ; jne +N ; mov eax, dword ptr [esp + N] ; push eax ; lea ecx, [ecx + ecx - N] ; push ecx ; push ebx ; push edi ; call EXT ; add esp, N ; cmp esi, N ; jle +N ; mov edx, dword ptr [esp + N] ; push edx ; lea esi, [edi + N] ; push esi ; push edi ; call EXT ; mov eax, dword ptr [esp + N] ; push eax ; push ebx ; push esi ; call EXT ; add esp, N ; pop esi ; pop edi ; pop ebx ; ret  ; mov ecx, dword ptr [esp + N] ; push ecx ; push ebx ; push edi ; call EXT ; add esp, N ; pop esi ; pop edi ; pop ebx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "struct C { int x; };\ninline int L2(int n){ int k=0; while(n){ n>>=1; ++k;} return k; }\n"

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
           "void %s(%s*, %s*, int, C);\n\n"
           "void %s(%s*, %s*, C);\n"
           "void %s(%s*, %s*, C);\n"
           "void FUN_%08x(%s* first, %s* last, C cmp) {\n"
           "    if (first != last) {\n"
           "        int lg = L2(last - first); int n = last - first;\n"
           "        %s(first, last, lg * 2 - 2, cmp);\n"
           "        if (n > 28) {\n"
           "            %s(first, first + 28, cmp);\n"
           "            %s(first + 28, last, cmp);\n"
           "        } else %s(first, last, cmp);\n"
           "    }\n}\n") % (t, size, f % quick, t, t, f % ins, t, t, f % ung, t, t, va, t, t,
                              f % quick, f % ins, f % ung, f % ins)
    return src, "?FUN_%08x@@YAXPAU%s@@0UC@@@Z" % (va, t)
