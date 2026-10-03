# if (p) { T* t = p; p = 0; t->vfn(); }  -> tail-call jmp through vtable
PATTERN = 'mov eax, dword ptr [ecx + N] ; test eax, eax ; je +N ; mov dword ptr [ecx + N], N ; mov edx, dword ptr [eax] ; mov ecx, eax ; mov eax, dword ptr [edx + N] ; jmp eax ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    off, idx = N[0], N[-1] // 4
    vs = "".join("virtual void v%d(); " % i for i in range(idx + 1))
    pad = "char pad[%d]; " % off if off else ""
    return ("struct S_%08x_I { %s};\nstruct S_%08x { %sS_%08x_I* p; void f(); };\n"
            "void S_%08x::f() { if (p) { S_%08x_I* t = p; p = 0; t->v%d(); } }" % (va, vs, va, pad, va, va, va, idx),
            "?f@S_%08x@@QAEXXZ" % va)
