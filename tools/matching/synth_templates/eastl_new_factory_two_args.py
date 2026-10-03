# Factory with two forwarded args: "return new(\"Name\") T(a, b);" via EASTL operator new; ctor call+ret.
PATTERN = 'push N ; push N ; push N ; push N ; push A ; push N ; call EXT ; add esp, N ; test eax, eax ; je +N ; mov ecx, dword ptr [esp + N] ; mov edx, dword ptr [esp + N] ; push ecx ; push edx ; mov ecx, eax ; call EXT ; ret  ; xor eax, eax ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ("typedef unsigned int size_t;\n"
           "void* operator new(size_t size, const char* name, int flags, unsigned debugFlags, const char* file, int line);\n")

def emit(va, A, N):
    size = N[4]
    t = "T_%08x" % va
    src = ("struct %s { void* init(void*, void*); char d[%d]; };\n"
           "void* FUN_%08x(void* a, void* b) { %s* p = new((const char*)%d, 0, 0u, (const char*)0, 0) %s; return p ? p->init(a, b) : 0; }"
           % (t, size, va, t, A[0], t))
    return src, "?FUN_%08x@@YAPAXPAX0@Z" % va
