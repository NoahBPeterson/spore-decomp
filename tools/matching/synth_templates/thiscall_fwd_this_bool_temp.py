# Thiscall member that forwards its untouched `this` (ecx live) to another member taking a by-value
# 1-byte struct temp B() as 3rd arg; returns the first stack arg. ecx live forces edx for arg 2.
PATTERN = 'push ecx ; mov edx, dword ptr [esp + N] ; push esi ; mov esi, dword ptr [esp + N] ; mov byte ptr [esp + N], N ; mov eax, dword ptr [esp + N] ; push eax ; push edx ; push esi ; call EXT ; mov eax, esi ; pop esi ; pop ecx ; ret N'
FLAGS = ["/O2", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "struct B { bool b; };\n"
def emit(va, A, N):
    src = ("struct T%08x { void* FUN_%08x(void* o, int a); void m2(void* o, int a, B); };\n"
           "void* T%08x::FUN_%08x(void* o, int a) { m2(o, a, B()); return o; }" % (va, va, va, va))
    return src, "?FUN_%08x@T%08x@@QAEPAXPAXH@Z" % (va, va)
