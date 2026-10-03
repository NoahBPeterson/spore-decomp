# EASTL-style sort(first,last,cmp) with a 12-byte by-value comparator (3 floats, user copy ctor), /arch:SSE.
# Same shape as eastl_sort_wrapper; elements are 4 bytes.
import os
import pefile
_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase
PATTERN = 'push ebx ; mov ebx, dword ptr [esp + N] ; push esi ; push edi ; mov edi, dword ptr [esp + N] ; cmp edi, ebx ; je +N ; movss xmm0, dword ptr [esp + N] ; sub esp, N ; mov eax, esp ; movss dword ptr [eax], xmm0 ; movss xmm0, dword ptr [esp + N] ; mov esi, ebx ; sub esi, edi ; movss dword ptr [eax + N], xmm0 ; movss xmm0, dword ptr [esp + N] ; sar esi, N ; movss dword ptr [eax + N], xmm0 ; mov eax, esi ; xor ecx, ecx ; test eax, eax ; je +N ; sar eax, N ; inc ecx ; test eax, eax ; jne +N ; lea eax, [ecx + ecx - N] ; push eax ; push ebx ; push edi ; call EXT ; movss xmm0, dword ptr [esp + N] ; add esp, N ; sub esp, N ; cmp esi, N ; mov eax, esp ; movss dword ptr [eax], xmm0 ; movss xmm0, dword ptr [esp + N] ; movss dword ptr [eax + N], xmm0 ; movss xmm0, dword ptr [esp + N] ; movss dword ptr [eax + N], xmm0 ; jle +N ; lea esi, [edi + N] ; push esi ; push edi ; call EXT ; movss xmm0, dword ptr [esp + N] ; add esp, N ; mov eax, esp ; movss dword ptr [eax], xmm0 ; movss xmm0, dword ptr [esp + N] ; movss dword ptr [eax + N], xmm0 ; movss xmm0, dword ptr [esp + N] ; push ebx ; push esi ; movss dword ptr [eax + N], xmm0 ; call EXT ; add esp, N ; pop edi ; pop esi ; pop ebx ; ret  ; push ebx ; push edi ; call EXT ; add esp, N ; pop edi ; pop esi ; pop ebx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/arch:SSE"]
PRELUDE = ("struct C { float a, b, c; C() {} C(const C& o) : a(o.a), b(o.b), c(o.c) {} };\n"
           "inline int L2(int n){ int k=0; while(n){ n>>=1; ++k;} return k; }\n")

def _calls(va):
    import capstone
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    code = _pe.get_data(va - _base, 0xe0)
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
    f = "FUN_%08x"
    src = ("void %s(int*, int*, int, C);\n"
           "void %s(int*, int*, C);\n"
           "void %s(int*, int*, C);\n"
           "void FUN_%08x(int* first, int* last, C cmp) {\n"
           "    if (first != last) {\n"
           "        "
           "        %s(first, last, L2(last - first) * 2 - 2, cmp);\n"
           "        if (last - first > 28) {\n"
           "            %s(first, first + 28, cmp);\n"
           "            %s(first + 28, last, cmp);\n"
           "        } else %s(first, last, cmp);\n"
           "    }\n}\n") % (f % quick, f % ins, f % ung, va, f % quick, f % ins, f % ung, f % ins)
    return src, "?FUN_%08x@@YAXPAH0UC@@@Z" % va
