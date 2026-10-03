# void f(Obj* o){ Desc d={f0..f3,b0,1}; o->Reg(&d,-1,K); Desc e={...}; o->Reg(&e,K,-1); } stack descriptor reused
PATTERN = 'sub esp, N ; push esi ; mov esi, dword ptr [esp + N] ; push N ; push -N ; lea eax, [esp + N] ; push eax ; mov ecx, esi ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov byte ptr [esp + N], N ; mov byte ptr [esp + N], N ; call EXT ; push -N ; push N ; lea ecx, [esp + N] ; push ecx ; mov ecx, esi ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; mov byte ptr [esp + N], N ; mov byte ptr [esp + N], N ; call EXT ; pop esi ; add esp, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """struct Desc { void* a; void* b; void* c; void* d; bool e; bool f; int pad; };
struct Obj { void Reg(Desc* d, int x, int y); };
"""
def emit(va, A, N):
    f = ["(void*)0x%08xu" % x for x in A]
    K = N[2]; e1 = N[10]; e2 = N[21]
    src = ("void FUN_%08x(Obj* o) {\n"
           "    Desc d; d.a = %s; d.b = %s; d.c = %s; d.d = %s; d.e = %s; d.f = true;\n    o->Reg(&d, -1, %d);\n"
           "    d.a = %s; d.b = %s; d.c = %s; d.d = %s; d.e = %s; d.f = true;\n    o->Reg(&d, %d, -1);\n}"
           % (va, f[0], f[1], f[2], f[3], "true" if e1 else "false", K,
              f[4], f[5], f[6], f[7], "true" if e2 else "false", K))
    return src, "?FUN_%08x@@YAXPAUObj@@@Z" % va
