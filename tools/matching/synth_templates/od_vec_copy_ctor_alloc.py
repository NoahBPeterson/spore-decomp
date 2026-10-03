# /Od vector copy ctor: n=(o.end-o.begin)>>s; b=n?alloc(&al,n<<s,al,0):0; begin=b; end=begin; cap=begin+n; end=copy(o.begin,o.end,begin)
import re
PATTERN = 'push ebp ; mov ebp, esp ; sub esp, N ; mov dword ptr [ebp - N], ecx ; mov eax, dword ptr [ebp + N] ; mov ecx, dword ptr [ebp + N] ; mov edx, dword ptr [eax + N] ; sub edx, dword ptr [ecx] ; sar edx, N ; mov dword ptr [ebp - N], edx ; cmp dword ptr [ebp - N], N ; je +N ; push N ; push N ; mov eax, dword ptr [ebp - N] ; shl eax, N ; push eax ; mov ecx, dword ptr [ebp - N] ; add ecx, N ; push ecx ; call EXT ; add esp, N ; mov dword ptr [ebp - N], eax ; jmp +N ; mov dword ptr [ebp - N], N ; mov edx, dword ptr [ebp - N] ; mov eax, dword ptr [ebp - N] ; mov dword ptr [edx], eax ; mov ecx, dword ptr [ebp - N] ; mov edx, dword ptr [ebp - N] ; mov eax, dword ptr [edx] ; mov dword ptr [ecx + N], eax ; mov ecx, dword ptr [ebp - N] ; mov edx, dword ptr [ecx] ; mov eax, dword ptr [ebp - N] ; lea ecx, [edx + eax*N] ; mov edx, dword ptr [ebp - N] ; mov dword ptr [edx + N], ecx ; mov eax, dword ptr [ebp - N] ; mov ecx, dword ptr [eax] ; push ecx ; mov edx, dword ptr [ebp + N] ; mov eax, dword ptr [edx + N] ; push eax ; mov ecx, dword ptr [ebp + N] ; mov edx, dword ptr [ecx] ; push edx ; call EXT ; add esp, N ; mov ecx, dword ptr [ebp - N] ; mov dword ptr [ecx + N], eax ; mov eax, dword ptr [ebp - N] ; mov esp, ebp ; pop ebp ; ret N'
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    F, sh, al = N[0], N[5], N[10]
    pad = F - 16
    c = "V_%08x" % va
    src = ("struct E_%08x { char d[%d]; };\n"
           "void* AL_%08x(void* a, unsigned n, unsigned al, unsigned fl);\n"
           "E_%08x* CP_%08x(const E_%08x* a, const E_%08x* b, E_%08x* p);\n"
           "struct %s { E_%08x *b, *e, *c; char a;\n"
           "  %s(const %s& o);\n};\n"
           "%s::%s(const %s& o) {\n"
           "    unsigned n = o.e - o.b;\n"
           "    char pad[%d];\n"
           "    b = n ? (E_%08x*)AL_%08x(&a, n << %d, %d, 0) : 0;\n"
           "    e = b;\n    c = b + n;\n"
           "    e = CP_%08x(o.b, o.e, b);\n}\n"
           ) % (va, 1 << sh, va, va, va, va, va, va, c, va, c, c, c, c, c, pad, va, va, sh, al, va)
    return src, "??0%s@@QAE@ABU0@@Z" % c
