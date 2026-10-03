# thunk: this->field->vfunc() tail call: mov ecx,[ecx+off]; mov eax,[ecx]; mov edx,[eax+v]; jmp edx
PATTERN = 'mov ecx, dword ptr [ecx + N] ; mov eax, dword ptr [ecx] ; mov edx, dword ptr [eax + N] ; jmp edx'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    off, v = N[0], N[1]
    k = v // 4
    virts = " ".join("virtual void v%d();" % i for i in range(k + 1))
    pad = "char pad[%d]; " % off if off else ""
    src = ("struct I_%08x { %s };\nstruct S_%08x { %sI_%08x* p; void FUN_%08x(); };\n"
           "void S_%08x::FUN_%08x() { p->v%d(); }" % (va, virts, va, pad, va, va, va, va, k))
    return src, "?FUN_%08x@S_%08x@@QAEXXZ" % (va, va)
