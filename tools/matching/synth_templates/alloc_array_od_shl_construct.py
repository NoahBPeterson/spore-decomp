# /Od member: p = n ? alloc(this+0xc, n*sz, 4, 0) : 0; construct(a, b, p); return p;
PATTERN = 'push ebp ; mov ebp, esp ; sub esp, N ; mov dword ptr [ebp - N], ecx ; cmp dword ptr [ebp + N], N ; je +N ; push N ; push N ; mov eax, dword ptr [ebp + N] ; shl eax, N ; push eax ; mov ecx, dword ptr [ebp - N] ; add ecx, N ; push ecx ; call EXT ; add esp, N ; mov dword ptr [ebp - N], eax ; jmp +N ; mov dword ptr [ebp - N], N ; mov edx, dword ptr [ebp - N] ; mov dword ptr [ebp - N], edx ; mov eax, dword ptr [ebp - N] ; push eax ; mov ecx, dword ptr [ebp + N] ; push ecx ; mov edx, dword ptr [ebp + N] ; push edx ; call EXT ; add esp, N ; mov eax, dword ptr [ebp - N] ; mov esp, ebp ; pop ebp ; ret N'
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    sz = N[7]
    pd = N[0] - 16
    PADS = ("char pad[%d]; char q[32];" % (pd - 32)) if pd > 64 else ("char pad[%d];" % pd)
    c = "C_%08x" % va
    src = ("void* AL_%08x(void* a, unsigned n, unsigned al, unsigned fl);\n"
           "void CT_%08x(unsigned a, unsigned b, void* p);\n"
           "struct %s { char d[12]; char al; void* f(int n, unsigned a, unsigned b); };\n"
           "void* %s::f(int n, unsigned a, unsigned b) {\n"
           "    %s\n"
           "    void* p = n ? AL_%08x(&al, n << %d, 4, 0) : 0;\n"
           "    CT_%08x(a, b, p);\n    return p;\n}\n") % (va, va, c, c, PADS, va, sz, va)
    return src, "?f@%s@@QAEPAXHII@Z" % c
