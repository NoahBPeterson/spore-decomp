# "if (g_obj) g_obj->vfunc();" -- /O2 free function that null-checks a global object pointer and
# tail-calls (jmp edx) a no-arg virtual __thiscall method on it (e.g. a manager singleton accessor).
PATTERN = "mov ecx, dword ptr [A] ; test ecx, ecx ; je +N ; mov eax, dword ptr [ecx] ; mov edx, dword ptr [eax + N] ; jmp edx ; ret "
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ("struct VObjG {\n" +
           "".join("    virtual void v%d() = 0;\n" % i for i in range(512)) +
           "};\n")
def emit(va, A, N):
    g = "g_%08x" % A[0]
    src = ("extern VObjG* %s;\nvoid FUN_%08x() {\n    if (%s) %s->v%d();\n}") % (g, va, g, g, N[0] // 4)
    return src, "?FUN_%08x@@YAXXZ" % va
