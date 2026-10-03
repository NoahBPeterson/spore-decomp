# __stdcall void f(int, S2*): p->b = imm; p->a = imm (ret 8)
PATTERN = 'mov eax, dword ptr [esp + N] ; mov dword ptr [eax + N], N ; mov dword ptr [eax], N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "struct S2 { int a, b; };\n"
def emit(va, A, N):
    return ("void __stdcall FUN_%08x(int, S2* p) { p->b = 0x%x; p->a = 0x%x; }"
            % (va, N[2], N[3])), "?FUN_%08x@@YGXHPAUS2@@@Z" % va
