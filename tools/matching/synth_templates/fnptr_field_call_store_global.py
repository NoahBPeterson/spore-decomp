# void f(S* p) { *p->fn(p) = g; } with fn a cdecl function-pointer field at +0x20 returning int*.
PATTERN = 'mov eax, dword ptr [esp + N] ; push eax ; mov eax, dword ptr [eax + N] ; call eax ; mov ecx, dword ptr [A] ; add esp, N ; mov dword ptr [eax], ecx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "struct S { unsigned pad[8]; int* (__cdecl *fn)(S*); };\n"

def emit(va, A, N):
    g = "g_%08x" % A[0]
    return ("extern int %s;\nvoid FUN_%08x(S* p) { *p->fn(p) = %s; }" % (g, va, g)), "?FUN_%08x@@YAXPAUS@@@Z" % va
