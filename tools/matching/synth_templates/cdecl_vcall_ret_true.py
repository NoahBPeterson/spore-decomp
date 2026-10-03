# cdecl bool f(a, obj) / f(obj, a): obj->vfunc[N](a); return true;
PATTERN = 'mov ecx, dword ptr [esp + N] ; mov eax, dword ptr [ecx] ; mov edx, dword ptr [esp + N] ; mov eax, dword ptr [eax + N] ; push edx ; call eax ; mov al, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    off = N[2]
    idx = off // 4
    name = "FUN_%08x" % va
    vs = "".join("virtual void v%d(void*);\n" % i for i in range(idx))
    cls = "struct C_%08x { %s virtual void m(void*); };\n" % (va, vs)
    if N[0] == 8:
        sig, ty = "void* a, C_%08x* o" % va, ""
    else:
        sig = "C_%08x* o, void* a" % va
    src = cls + "bool %s(%s) { o->m(a); return true; }" % (name, sig)
    return src, "?%s@@YA_N%s@Z" % (name, ("PAXPAUC_%08x@@" % va) if N[0] == 8 else ("PAUC_%08x@@PAX" % va))
