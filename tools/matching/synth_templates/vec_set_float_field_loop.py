# Set-all-elements float field over a vector of 0x4e0-byte records (6 instances differ only in field offset).
# NOT byte-exact: original re-evaluates (end-begin)/0x4e0 every iteration of BOTH loops and keeps the bool result
# in bl across the calls; every source shape tried hoists the count in the read-only loop (see findings).
PATTERN = 'mov ecx, dword ptr [esp + N] ; cmp byte ptr [ecx + N], N ; mov eax, dword ptr [esp + N] ; movss xmm0, dword ptr [eax + N] ; movss xmm1, dword ptr [esp + N] ; push ebx ; push esi ; push edi ; je +N ; mov esi, dword ptr [ecx + N] ; sub esi, dword ptr [ecx + N] ; mov eax, A ; imul esi ; add edx, esi ; sar edx, N ; mov eax, edx ; shr eax, N ; add eax, edx ; xor edi, edi ; test eax, eax ; jle +N ; mov ebx, dword ptr [ecx + N] ; add ebx, N ; jmp +N ; lea ecx, [ecx] ; movss xmm2, dword ptr [ebx] ; ucomiss xmm2, xmm1 ; lahf  ; test ah, N ; jp +N ; mov esi, dword ptr [ecx + N] ; sub esi, dword ptr [ecx + N] ; mov eax, A ; imul esi ; add edx, esi ; sar edx, N ; mov eax, edx ; shr eax, N ; inc edi ; add eax, edx ; add ebx, N ; cmp edi, eax ; jl +N ; ucomiss xmm1, xmm0 ; lahf  ; test ah, N ; jnp +N ; mov esi, dword ptr [ecx + N] ; sub esi, dword ptr [ecx + N] ; mov eax, A ; imul esi ; add edx, esi ; sar edx, N ; mov eax, edx ; shr eax, N ; add eax, edx ; xor edi, edi ; mov bl, N ; test eax, eax ; jle +N ; push ebp ; xor ebp, ebp ; mov edi, edi ; mov edx, dword ptr [ecx + N] ; movss dword ptr [edx + ebp + N], xmm0 ; mov esi, dword ptr [ecx + N] ; sub esi, dword ptr [ecx + N] ; mov eax, A ; imul esi ; add edx, esi ; sar edx, N ; mov eax, edx ; shr eax, N ; inc edi ; add eax, edx ; add ebp, N ; cmp edi, eax ; jl +N ; mov ecx, dword ptr [A] ; mov ecx, dword ptr [ecx + N] ; pop ebp ; call EXT ; pop edi ; pop esi ; mov al, bl ; pop ebx ; ret  ; mov edx, dword ptr [A] ; mov ecx, dword ptr [edx + N] ; xor bl, bl ; call EXT ; pop edi ; pop esi ; mov al, bl ; pop ebx ; ret  ; ucomiss xmm1, xmm0 ; lahf  ; test ah, N ; jnp +N ; mov bl, N ; mov ecx, dword ptr [A] ; mov ecx, dword ptr [ecx + N] ; call EXT ; pop edi ; pop esi ; mov al, bl ; pop ebx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/arch:SSE", "/fp:fast"]
PRELUDE = "struct Tgt_G { void __thiscall A(); void __thiscall B(); };\nstruct Sys_G { unsigned pad[29]; Tgt_G* t; };\nextern Sys_G* g_016c7aa4;\n"
def emit(va, A, N):
    off, gl = N[4], A[4]
    s = "%08x" % va
    src = """struct Elem_S { unsigned pad[0x%x/4]; float v; unsigned pad2[(0x4e0-0x%x-4)/4]; };
struct Other_S { unsigned pad[0x%x/4]; float v; };
struct Obj_S { unsigned pad0[8]; bool flag; unsigned pad1[(0x70-0x24)/4]; Elem_S* b; Elem_S* e;
  int size() const { return (int)(e - b); } };
bool FUN_S(Obj_S* o, Other_S* p, float x) {
  float cur = p->v;
  if (o->flag) {
    int i;
    for (i = 0; i < o->size(); i++) if (o->b[i].v != x) goto set;
    if (x == cur) goto fail;
   set:
    for (i = 0; i < o->size(); i++) o->b[i].v = cur;
  } else if (x == cur) goto fail;
  g_016c7aa4->t->B();
  return true;
 fail:
  g_016c7aa4->t->A();
  return false;
}""" % (off, off, off)
    src = src.replace("_S", "_" + s)
    return src, "?FUN_%s@@YA_NPAUObj_%s@@PAUOther_%s@@M@Z" % (s, s, s)
