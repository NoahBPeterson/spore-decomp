# if (flags & 4) Release(1); Set(a,0,p,b,1); return this;   (member, __thiscall, ret 4)
PATTERN = 'push esi ; mov esi, ecx ; test byte ptr [esi + N], N ; je +N ; push N ; call EXT ; mov eax, dword ptr [esp + N] ; push N ; push N ; push eax ; push N ; push N ; mov ecx, esi ; call EXT ; mov eax, esi ; pop esi ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """struct Obj {
    char pad[0x10]; unsigned char flags;
    void Release(int a);
    void Set(int a, int b, void* p, int c, int d);
};
"""
def emit(va, A, N):
    a, m, b = N[-2], N[-3], N[-4]
    n = "O%08x" % va
    src = ("struct %s : Obj { %s* f(void* p); };\n"
           "%s* %s::f(void* p) { if (flags & 4) Release(1); Set(%d, %d, p, %d, 1); return this; }\n" % (n, n, n, n, a, m, b))
    return src, "?f@%s@@QAEPAU1@PAX@Z" % n
