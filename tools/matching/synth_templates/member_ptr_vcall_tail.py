# void C::m(args) { V* q = p; if (q) q->f(args); }  -> tail call via jmp eax, ret 4*n on null path
PATTERN = 'mov ecx, dword ptr [ecx + N] ; test ecx, ecx ; je +N ; mov eax, dword ptr [ecx] ; mov eax, dword ptr [eax + N] ; jmp eax ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    off, vo, rn = N[0], N[1], N[2]
    n = rn // 4
    params = ", ".join("int a%d" % i for i in range(n))
    args = ", ".join("a%d" % i for i in range(n))
    dummies = "".join("virtual void d%d(); " % i for i in range(vo // 4))
    pad = "unsigned pad[%d]; " % (off // 4) if off else ""
    src = ("struct V_%08x { %svirtual void f(%s); };\n"
           "struct C_%08x { %sV_%08x* p; void m(%s); };\n"
           "void C_%08x::m(%s) { V_%08x* q = p; if (q) q->f(%s); }\n") % (
        va, dummies, ", ".join(["int"] * n), va, pad, va, params, va, params, va, args)
    return src, "?m@C_%08x@@QAEX%s@Z" % (va, "H" * n)
