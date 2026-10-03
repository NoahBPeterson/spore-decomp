# this->v->vfn(*Lookup(arg,1)) stored as float into this->q->[off]
PATTERN = 'push esi ; mov esi, ecx ; mov ecx, dword ptr [esp + N] ; push N ; call EXT ; mov ecx, dword ptr [esi + N] ; mov edx, dword ptr [ecx] ; mov eax, dword ptr [eax] ; mov edx, dword ptr [edx + N] ; push eax ; call edx ; mov eax, dword ptr [esi + N] ; fstp dword ptr [eax + N] ; pop esi ; ret N'
FLAGS = ["/O2", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "struct Src { int* Lookup(int); };\n"
def emit(va, A, N):
    vt, off = N[3], N[5]
    vs = "".join("virtual void d%d();" % i for i in range(vt // 4))
    h = "%08x" % va
    pad = "char p[%d];" % off if off else ""
    src = ("struct V_%s { %s virtual float vf(int x); };\n"
           "struct Q_%s { %s float f; };\n"
           "struct R_%s { int a; V_%s* v; int b; Q_%s* q; void FUN_%s(Src* s); };\n"
           "void R_%s::FUN_%s(Src* s) { int* a = s->Lookup(1); q->f = v->vf(*a); }\n"
           % (h, vs, h, pad, h, h, h, h, h, h))
    return src, "?FUN_%s@R_%s@@QAEXPAUSrc@@@Z" % (h, h)
