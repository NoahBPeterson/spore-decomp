# Store descriptor address into global, call cdecl f(a,b,c) with three data addresses, return descriptor address.
PATTERN = 'push A ; push A ; push A ; mov dword ptr [A], A ; call EXT ; add esp, N ; mov eax, A ; ret '
FLAGS = ["/O2", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP", "/GS-"]
PRELUDE = "extern \"C\" void FUN_0112dae0(void*, void*, void*);\n"
def emit(va, A, N):
    c, b, a, gp, d = A[0], A[1], A[2], A[3], A[4]
    src = ("extern char g_%08x[], g_%08x[], g_%08x[], g_%08x[]; extern void* g_%08x;\n"
           "void* FUN_%08x() { g_%08x = g_%08x; FUN_0112dae0(g_%08x, g_%08x, g_%08x); return g_%08x; }"
           % (a, b, c, d, gp, va, gp, d, a, b, c, d))
    return src, "?FUN_%08x@@YAPAXXZ" % va
