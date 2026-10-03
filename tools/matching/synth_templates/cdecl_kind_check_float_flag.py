# float f(Obj* o): r = Lookup(o->a->b); if (r && r->kind==K) { sub=(u16 @0x12 is 0xa/0x10 ? (fl&0x30 ? *p : type?p:0) : &gdef); return *sub >= 3 ? gfloat : 0.0f } return 0
PATTERN = 'mov eax, dword ptr [esp + N] ; mov ecx, dword ptr [eax + N] ; mov ecx, dword ptr [ecx + N] ; call EXT ; test eax, eax ; je +N ; cmp dword ptr [eax], N ; jne +N ; lea ecx, [eax + N] ; movzx eax, word ptr [ecx + N] ; cmp ax, N ; je +N ; cmp ax, N ; je +N ; mov eax, A ; jmp +N ; test byte ptr [ecx + N], N ; je +N ; mov eax, dword ptr [ecx] ; jmp +N ; movzx eax, ax ; neg eax ; sbb eax, eax ; and eax, ecx ; cmp dword ptr [eax], N ; jb +N ; movss xmm0, dword ptr [A] ; movss dword ptr [esp + N], xmm0 ; fld dword ptr [esp + N] ; ret  ; xorps xmm0, xmm0 ; movss dword ptr [esp + N], xmm0 ; fld dword ptr [esp + N] ; ret  ; fldz  ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/arch:SSE"]
PRELUDE = ""

def emit(va, A, N):
    src = """extern unsigned g_%(a0)08x;
extern float g_%(a1)08x;
#pragma pack(push, 1)
struct Sub_%(h)s { unsigned p; char pad[0xc]; unsigned char fl; char pad2; unsigned short type; };
struct Rec_%(h)s { unsigned kind; char pad[0x49]; Sub_%(h)s s; };
#pragma pack(pop)
struct Inner_%(h)s { int x; };
struct Mgr_%(h)s { char pad[0x10]; Inner_%(h)s *in; };
struct Obj_%(h)s { int a; Mgr_%(h)s *m; };
Rec_%(h)s* __fastcall ext_%(h)s(Inner_%(h)s*);
float FUN_%(h)s(Obj_%(h)s *o) {
  Rec_%(h)s *r = ext_%(h)s(o->m->in);
  if (r && r->kind == %(k)d) {
    Sub_%(h)s *s = &r->s; unsigned *v;
    if (s->type != 10 && s->type != 0x10) v = &g_%(a0)08x;
    else if (s->fl & 0x30) v = (unsigned*)s->p;
    else v = s->type ? (unsigned*)s : 0;
    return (*v >= 3) ? g_%(a1)08x : 0.0f;
  }
  return 0.0f;
}""" % dict(a0=A[0], a1=A[1], h="%08x" % va, k=N[3])
    return src, "?FUN_%08x@@YAMPAUObj_%08x@@@Z" % (va, va)
