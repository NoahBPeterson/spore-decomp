# __stdcall void f(S*): store 0 to [0], then fields +8, +4, +12 (ret 4)
PATTERN = 'mov eax, dword ptr [esp + N] ; mov dword ptr [eax], N ; mov dword ptr [eax + N], N ; mov dword ptr [eax + N], N ; mov dword ptr [eax + N], N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "struct S4 { int a, b, c, d; };\n"
def emit(va, A, N):
    return ("void __stdcall FUN_%08x(S4* p) { p->a = 0; p->c = 0x%x; p->b = 0x%x; p->d = 0x%x; }"
            % (va, N[3], N[5], N[7])), "?FUN_%08x@@YGXPAUS4@@@Z" % va
