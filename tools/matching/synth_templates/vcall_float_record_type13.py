# float C::Get() { float r=0; if (m) { Rec* p; if (m->vN(ID,&p) && p->type==0xd) r=*Ext(); } return r; }
PATTERN = 'sub esp, N ; mov ecx, dword ptr [ecx + N] ; xorps xmm0, xmm0 ; movss dword ptr [esp], xmm0 ; test ecx, ecx ; je +N ; mov eax, dword ptr [ecx] ; mov eax, dword ptr [eax + N] ; lea edx, [esp + N] ; push edx ; push A ; call eax ; test al, al ; je +N ; mov ecx, dword ptr [esp + N] ; cmp word ptr [ecx + N], N ; jne +N ; call EXT ; movss xmm0, dword ptr [eax] ; movss dword ptr [esp], xmm0 ; fld dword ptr [esp] ; add esp, N ; ret '
FLAGS = ["/O2", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP", "/arch:SSE"]
PRELUDE = "float* ExtF();\nstruct Rec { char p[0x12]; unsigned short t; };\n"
def emit(va, A, N):
    off, slot, tv = N[1], N[2], N[-2]
    h = "%08x" % va
    vs = "".join("virtual void d%d();" % i for i in range(slot // 4))
    src = ("struct O_%s { %s virtual bool vf(unsigned id, Rec** out); };\n"
           "struct C_%s { char pad[0x%x]; O_%s* m; float FUN_%s(); };\n"
           "float C_%s::FUN_%s() { float r = 0.0f; O_%s* o = m; if (o) { Rec* p; if (o->vf(0x%08xu, &p) && p->t == %d) r = *ExtF(); } return r; }"
           % (h, vs, h, off, h, h, h, h, h, A[0], tv))
    return src, "?FUN_%s@C_%s@@QAEMXZ" % (h, h)
