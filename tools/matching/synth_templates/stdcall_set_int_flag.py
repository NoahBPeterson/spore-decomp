# void __stdcall f(S* p): p->a = N; p->b = 1;  (ret 4)
PATTERN = 'mov eax, dword ptr [esp + N] ; mov dword ptr [eax], N ; mov byte ptr [eax + N], N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "struct S638 { int a; bool b; };\n"
def emit(va, A, N):
    return ("void __stdcall FUN_%08x(S638* p) { p->a = %d; p->b = true; }" % (va, N[1]),
            "?FUN_%08x@@YGXPAUS638@@@Z" % va)
