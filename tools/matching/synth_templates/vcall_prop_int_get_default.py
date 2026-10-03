# int C::Get() { int r = DEF; if (m) { Rec* p; if (m->vN(ID,&p) && p->t==9) r = *Ext(); } return r; }
PATTERN = 'push ecx ; mov ecx, dword ptr [ecx + N] ; push esi ; mov esi, N ; test ecx, ecx ; je +N ; mov eax, dword ptr [ecx] ; mov eax, dword ptr [eax + N] ; lea edx, [esp + N] ; push edx ; push A ; call eax ; test al, al ; je +N ; mov ecx, dword ptr [esp + N] ; cmp word ptr [ecx + N], N ; jne +N ; call EXT ; mov eax, dword ptr [eax] ; pop esi ; pop ecx ; ret  ; mov eax, esi ; pop esi ; pop ecx ; ret '
FLAGS = ["/O2", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "int* ExtI();\nstruct Rec { char p[0x12]; unsigned short t; };\n"
def emit(va, A, N):
    off, d, slot, tv = N[0], N[1], N[2], N[-1]
    h = "%08x" % va
    vs = "".join("virtual void d%d();" % i for i in range(slot // 4))
    src = ("struct O_%s { %s virtual bool vf(unsigned id, Rec** out); };\n"
           "struct C_%s { char pad[0x%x]; O_%s* m; int FUN_%s(); };\n"
           "int C_%s::FUN_%s() { int r = %d; O_%s* o = m; if (o) { Rec* p; if (o->vf(0x%08xu, &p) && p->t == %d) r = *ExtI(); } return r; }"
           % (h, vs, h, off, h, h, h, h, d, h, A[0], tv))
    return src, "?FUN_%s@C_%s@@QAEHXZ" % (h, h)
