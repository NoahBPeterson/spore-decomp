# Plugin descriptor registration: store &descriptor into a global slot, call a cdecl
# registrar with (&name, &attr, 0), return &descriptor. Plain /O2.
PATTERN = "push N ; push A ; push A ; mov dword ptr [A], A ; call EXT ; add esp, N ; mov eax, A ; ret "
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "void ext_reg(void*, void*, int);\n"
def emit(va, A, N):
    p2, p1, slot, d = A[0], A[1], A[2], A[3]
    src = ("extern char g_%08x[], g_%08x[], g_%08x[];\nextern void* g_%08x;\n"
           "void* FUN_%08x() { g_%08x = g_%08x; ext_reg(g_%08x, g_%08x, 0); return g_%08x; }"
           % (p1, p2, d, slot, va, slot, d, p1, p2, d))
    return src, "?FUN_%08x@@YAPAXXZ" % va
