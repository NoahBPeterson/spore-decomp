# Partial match (not byte-exact): stdcall(a,b,c,obj) calling callee(b,a,c,obj), then a 0x30-stride
# element loop calling elem ctor, then negating 3 floats if a float field changed.
# Remaining diff is scheduling (arg loads) and the loop-end reload (mov eax,[edi]; cmp esi,eax).
PATTERN = 'mov edx, dword ptr [esp + N] ; push esi ; push edi ; mov edi, dword ptr [esp + N] ; mov eax, dword ptr [edi + N] ; mov esi, dword ptr [edi] ; push edi ; push edx ; mov edx, dword ptr [esp + N] ; mov dword ptr [esp + N], eax ; mov eax, dword ptr [esp + N] ; push eax ; push edx ; call EXT ; cmp esi, dword ptr [edi] ; jae +N ; jmp +N ; lea ecx, [ecx] ; push esi ; mov ecx, esi ; call EXT ; mov eax, dword ptr [edi] ; add esi, N ; cmp esi, eax ; jb +N ; fld dword ptr [edi + N] ; fld dword ptr [esp + N] ; fucompp  ; fnstsw ax ; test ah, N ; jnp +N ; fld dword ptr [edi + N] ; fchs  ; fstp dword ptr [edi + N] ; fld dword ptr [edi + N] ; fchs  ; fstp dword ptr [edi + N] ; fld dword ptr [edi + N] ; fchs  ; fstp dword ptr [edi + N] ; pop edi ; pop esi ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """struct El89 { void __thiscall elem(El89*); unsigned pad[12]; };
struct F89 { float v; };
struct O89 { El89 *b; char pad[0x1c]; float f20,f24,f28; char pad2[0x3008]; F89 s; };
void __stdcall callee89(int,int,int,O89*);
"""
def emit(va, A, N):
    return ("""void __stdcall FUN_%08x(int a, int b, int c, O89 *p) {
  F89 old = p->s;
  El89 *it = p->b;
  callee89(b, a, c, p);
  for (; it < p->b; ++it) it->elem(it);
  if (p->s.v != old.v) { p->f20 = -p->f20; p->f24 = -p->f24; p->f28 = -p->f28; }
}""" % va, "?FUN_%08x@@YGXHHHPAUO89@@@Z" % va)
