# this->f4 = this->f0; this->m(a, &by_value_param); return this;
PATTERN = 'mov edx, dword ptr [esp + N] ; push esi ; mov esi, dword ptr [esp + N] ; mov eax, dword ptr [esi] ; lea ecx, [esp + N] ; push ecx ; push edx ; mov ecx, esi ; mov dword ptr [esi + N], eax ; call EXT ; mov eax, esi ; pop esi ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "struct S { int a; int b; void m(int, const int&); };\n"
def emit(va, A, N):
    off = N[-1] if N else 4
    return ("struct S%08x { int a; int b; void m(int, const int&); };\n"
            "S%08x* FUN_%08x(S%08x* t, int x, int y) { t->b = t->a; t->m(x, y); return t; }"
            % (va, va, va, va)), "?FUN_%08x@@YAPAUS%08x@@PAU1@HH@Z" % (va, va)
