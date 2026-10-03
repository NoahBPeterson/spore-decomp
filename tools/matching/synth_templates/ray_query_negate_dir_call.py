# __thiscall (this, a, b, const S* p, n, m) stdarg-5 wrapper: copies 48-byte S, negates S.b, builds one or two
# 16-aligned vptr query objects (vptr, 0x7f7fffee, pad, V4 copy of p->b, n) and forwards to a thiscall callee.
# NOT byte-exact yet: cl folds p->b into [eax+0x10] addressing where the original keeps a separate p+0x10 pointer.
PATTERN = 'push ebp ; mov ebp, esp ; and esp, A ; sub esp, N ; mov eax, dword ptr [ebp + N] ; fld dword ptr [eax + N] ; mov edx, ecx ; push esi ; fchs  ; push edi ; mov esi, eax ; add eax, N ; mov ecx, N ; lea edi, [esp + N] ; rep movsd dword ptr es:[edi], dword ptr [esi] ; fstp dword ptr [esp + N] ; fld dword ptr [eax + N] ; fchs  ; fstp dword ptr [esp + N] ; fld dword ptr [eax + N] ; fchs  ; fstp dword ptr [esp + N] ; fld dword ptr [eax + N] ; fchs  ; fstp dword ptr [esp + N] ; mov ecx, eax ; mov edi, dword ptr [ecx] ; mov dword ptr [esp + N], edi ; mov edi, dword ptr [ecx + N] ; mov dword ptr [esp + N], edi ; mov edi, dword ptr [ecx + N] ; mov ecx, dword ptr [ecx + N] ; mov dword ptr [esp + N], ecx ; mov ecx, dword ptr [ebp + N] ; mov dword ptr [esp + N], ecx ; mov ecx, dword ptr [ebp + N] ; test ecx, ecx ; mov esi, A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], esi ; mov dword ptr [esp + N], edi ; je +N ; mov dword ptr [esp + N], esi ; mov esi, dword ptr [eax] ; mov dword ptr [esp + N], esi ; mov esi, dword ptr [eax + N] ; mov dword ptr [esp + N], esi ; mov esi, dword ptr [eax + N] ; mov eax, dword ptr [eax + N] ; mov dword ptr [esp + N], ecx ; lea ecx, [esp + N] ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], esi ; mov dword ptr [esp + N], eax ; push ecx ; jmp +N ; push N ; lea eax, [esp + N] ; push eax ; mov eax, dword ptr [ebp + N] ; lea ecx, [esp + N] ; push ecx ; mov ecx, dword ptr [ebp + N] ; push eax ; push ecx ; mov ecx, edx ; call EXT ; pop edi ; pop esi ; mov esp, ebp ; pop ebp ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """struct V4 { float x,y,z,w; };
struct S { V4 a; V4 b; V4 c; };
struct __declspec(align(16)) Q { virtual void vf(); unsigned f; unsigned p0,p1; V4 v; unsigned n; };
struct Q2 : Q { Q2(const V4& d, unsigned nn){ f=0x7f7fffee; v=d; n=nn;} };
struct T { void __thiscall callee(int,int,const S*,const Q*,const Q*); };
"""
def emit(va, A, N):
    src = """struct T_%08x : T { void __thiscall f(int a,int b,const S* p,unsigned n,unsigned m); };
void __thiscall T_%08x::f(int a,int b,const S* p,unsigned n,unsigned m){
  S s = *p;
  s.b.x=-p->b.x; s.b.y=-p->b.y; s.b.z=-p->b.z; s.b.w=-p->b.w;
  Q2 q(p->b,n);
  if (m) { Q2 q2(p->b,m); callee(b,a,&s,&q,&q2);} else callee(b,a,&s,&q,0);
}""" % (va, va)
    return src, "?f@T_%08x@@QAEXHHPBUS@@II@Z" % va
