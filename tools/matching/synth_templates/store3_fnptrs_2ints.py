# void f(){ g.a=fn0; g.c=fn1; g.d=fn2; g.e=K; g.f=K; } stores into a global struct at +0,+8,+0xc,+0x14,+0x18.
# A[0..2] are function pointers, A[3..4] data addresses, N[0] the constant (loaded into eax first).
PATTERN = 'mov eax, N ; mov dword ptr [A], A ; mov dword ptr [A], A ; mov dword ptr [A], A ; mov dword ptr [A], eax ; mov dword ptr [A], eax ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    base = A[0]
    # operand order: A = [g0, fn0, g1, fn1, g2, fn2, g3, g4]
    g0, f0, g1, f1, g2, f2, g3, g4 = A[:8]
    sym = "?g_%08x@@3Ug_%08x_t@@A" % (base, base)
    src = ("struct g_%08x_t { void* a; int p0; void* c; void* d; int p1; int e; int f; };\n"
           "extern \"C\" { g_%08x_t g_%08x; }\n"
           "void FUN_%08x() { g_%08x.a = (void*)0x%08xu; g_%08x.c = (void*)0x%08xu; g_%08x.d = (void*)0x%08xu; g_%08x.e = %d; g_%08x.f = %d; }"
           % (base, base, base, va, base, f0, base, f1, base, f2, base, N[0], base, N[0]))
    return src, "?FUN_%08x@@YAXXZ" % va
