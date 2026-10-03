# Nearest-object search over a vector<Obj*> by squared distance of a virtual (slot 11) position getter on a sub-object.
PATTERN = 'sub esp, N ; mov eax, dword ptr [esp + N] ; movss xmm0, dword ptr [A] ; push ebp ; mov ebp, dword ptr [eax + N] ; push esi ; mov esi, dword ptr [eax] ; xor ecx, ecx ; mov dword ptr [esp + N], ecx ; movss dword ptr [esp + N], xmm0 ; cmp esi, ebp ; je +N ; push ebx ; push edi ; mov edi, dword ptr [esp + N] ; lea esp, [esp] ; mov ebx, dword ptr [esi] ; mov eax, dword ptr [ebx + N] ; mov edx, dword ptr [eax + N] ; lea ecx, [ebx + N] ; call edx ; movss xmm1, dword ptr [eax + N] ; subss xmm1, dword ptr [edi + N] ; movss xmm0, dword ptr [eax] ; subss xmm0, dword ptr [edi] ; movss xmm2, dword ptr [eax + N] ; subss xmm2, dword ptr [edi + N] ; movaps xmm3, xmm1 ; mulss xmm3, xmm1 ; mulss xmm0, xmm0 ; movaps xmm1, xmm2 ; mulss xmm1, xmm2 ; addss xmm0, xmm3 ; addss xmm0, xmm1 ; movss xmm1, dword ptr [esp + N] ; comiss xmm1, xmm0 ; jbe +N ; mov dword ptr [esp + N], ebx ; movss dword ptr [esp + N], xmm0 ; add esi, N ; cmp esi, ebp ; jne +N ; mov eax, dword ptr [esp + N] ; pop edi ; pop ebx ; pop esi ; pop ebp ; add esp, N ; ret  ; pop esi ; mov eax, ecx ; pop ebp ; add esp, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/arch:SSE", "/fp:fast"]
PRELUDE = ""
def emit(va, A, N):
    s = "%08x" % va
    off = N[6]
    src = """struct Pos_S { float x, y, z; };
struct Sub_S { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
  virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10();
  virtual const Pos_S* GetPos(); };
struct Obj_S { char pad[0x%x]; Sub_S sub; };
struct Vec_S { Obj_S** b; Obj_S** e; };
Obj_S* FUN_S(Vec_S* v, const Pos_S* p) {
  Obj_S* best = 0; float bd = 3.402823466e+38f;
  Obj_S** e = v->e; for (Obj_S** it = v->b; it != e; ++it) {
    Obj_S* o = *it; const Pos_S* q = o->sub.GetPos();
    float d = (q->z-p->z)*(q->z-p->z)+((q->y-p->y)*(q->y-p->y)+(q->x-p->x)*(q->x-p->x));
    if (d < bd) { best = o; bd = d; }
  }
  return best;
}""" % off
    src = src.replace("_S", "_" + s)
    return src, "?FUN_%s@@YAPAUObj_%s@@PAUVec_%s@@PBUPos_%s@@@Z" % (s, s, s, s)
