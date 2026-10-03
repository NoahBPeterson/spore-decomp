# this->v->vfn(*Lookup(arg,1)) stored as float into this->q->[off1]->[off2]
PATTERN = 'push esi ; mov esi, ecx ; mov ecx, dword ptr [esp + N] ; push N ; call EXT ; mov ecx, dword ptr [esi + N] ; mov edx, dword ptr [ecx] ; mov eax, dword ptr [eax] ; mov edx, dword ptr [edx + N] ; push eax ; call edx ; mov eax, dword ptr [esi + N] ; mov ecx, dword ptr [eax + N] ; fstp dword ptr [ecx + N] ; pop esi ; ret N'
FLAGS = ["/O2", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "struct Src { int* Lookup(int); };\n"
def _pad(n):
    return "char p[%d];" % n if n else ""
def emit(va, A, N):
    vt, o1, o2 = N[3], N[5], N[6]
    vs = "".join("virtual void d%d();" % i for i in range(vt // 4))
    h = "%08x" % va
    src = ("struct V_%s { %s virtual float vf(int x); };\n"
           "struct P_%s { %s float f; };\n"
           "struct Q_%s { %s P_%s* c; };\n"
           "struct R_%s { int a; V_%s* v; int b; Q_%s* q; void FUN_%s(Src* s); };\n"
           "void R_%s::FUN_%s(Src* s) { int* a = s->Lookup(1); q->c->f = v->vf(*a); }\n"
           % (h, vs, h, _pad(o2), h, _pad(o1), h, h, h, h, h, h, h))
    return src, "?FUN_%s@R_%s@@QAEXPAUSrc@@@Z" % (h, h)
