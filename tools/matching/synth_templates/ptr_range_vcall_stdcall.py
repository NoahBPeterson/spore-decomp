# __stdcall(first,last) loop calling vtable slot on each non-null element pointer; returns void.
PATTERN = 'push esi ; mov esi, dword ptr [esp + N] ; push edi ; mov edi, dword ptr [esp + N] ; cmp esi, edi ; jae +N ; mov edi, edi ; mov ecx, dword ptr [esi] ; test ecx, ecx ; je +N ; mov eax, dword ptr [ecx] ; mov edx, dword ptr [eax + N] ; call edx ; add esi, N ; cmp esi, edi ; jb +N ; pop edi ; pop esi ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    voff, stride = N[-3], N[-2]
    slot = voff // 4
    v = "".join("virtual void v%d(); " % i for i in range(slot + 1))
    pad = "char pad[%d]; " % (stride - 4) if stride > 4 else ""
    src = ("struct I_%08x { %s};\nstruct E_%08x { I_%08x* p; %s};\n"
           "void __stdcall FUN_%08x(E_%08x* a, E_%08x* b) {\n"
           "  for (; a < b; ++a) if (a->p) a->p->v%d();\n}"
           % (va, v, va, va, pad, va, va, va, slot))
    return src, "?FUN_%08x@@YGXPAUE_%08x@@0@Z" % (va, va)
