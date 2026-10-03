# Lazy-init 8-byte getter: if (!flag) Init(); *out = pair;  (__thiscall, out ptr, ret 4)
PATTERN = 'push esi ; mov esi, ecx ; cmp dword ptr [esi + N], N ; jne +N ; call EXT ; mov ecx, dword ptr [esi + N] ; mov eax, dword ptr [esp + N] ; mov dword ptr [eax], ecx ; mov edx, dword ptr [esi + N] ; mov dword ptr [eax + N], edx ; pop esi ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    flag, off = N[0], N[2]
    c = "C_%08x" % va
    src = ("struct P_%08x { int a; int b; };\n"
           "#pragma pack(push, 1)\n"
           "struct %s { char pad0[0x%x]; int flag; char pad1[0x%x]; P_%08x val; void Init(); void Get(P_%08x* out); };\n"
           "#pragma pack(pop)\n"
           "void %s::Get(P_%08x* out) { if (flag == 0) Init(); out->a = val.a; out->b = val.b; }"
           % (va, c, flag, off - flag - 4, va, va, c, va))
    return src, "?Get@%s@@QAEXPAUP_%08x@@@Z" % (c, va)
