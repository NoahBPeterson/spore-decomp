# eastl rb_tree<wstring,...>::DoInsertKey(const key&, true_type): hand-inlined compare, std::min by reference.
PATTERN = 'sub esp, N ; push ebx ; push ebp ; mov ebp, dword ptr [esp + N] ; push esi ; mov ebx, ecx ; push edi ; mov edi, dword ptr [ebx + N] ; mov dword ptr [esp + N], ebx ; lea esi, [ebx + N] ; mov al, N ; test edi, edi ; je +N ; mov ebx, dword ptr [ebp] ; mov ebp, dword ptr [ebp + N] ; sub ebp, ebx ; sar ebp, N ; mov dword ptr [esp + N], ebx ; mov dword ptr [esp + N], ebp ; jmp +N ; mov ebx, dword ptr [esp + N] ; mov ecx, dword ptr [edi + N] ; mov esi, dword ptr [edi + N] ; sub esi, ecx ; sar esi, N ; cmp esi, ebp ; mov dword ptr [esp + N], esi ; lea eax, [esp + N] ; jl +N ; lea eax, [esp + N] ; mov edx, dword ptr [eax] ; mov eax, ebx ; test edx, edx ; jbe +N ; jmp +N ; lea ecx, [ecx] ; mov bx, word ptr [eax] ; cmp bx, word ptr [ecx] ; jne +N ; add eax, N ; add ecx, N ; sub edx, N ; jne +N ; jmp +N ; movzx eax, word ptr [eax] ; cmp ax, word ptr [ecx] ; sbb eax, eax ; and eax, A ; add eax, N ; jne +N ; cmp ebp, esi ; jge +N ; or eax, A ; jmp +N ; xor eax, eax ; cmp ebp, esi ; setg al ; test eax, eax ; setl al ; mov esi, edi ; test al, al ; je +N ; mov edi, dword ptr [edi + N] ; jmp +N ; mov edi, dword ptr [edi] ; test edi, edi ; jne +N ; mov ebx, dword ptr [esp + N] ; mov ebp, dword ptr [esp + N] ; mov edi, esi ; test al, al ; je +N ; cmp esi, dword ptr [ebx + N] ; je +N ; push esi ; call EXT ; add esp, N ; mov esi, eax ; mov eax, dword ptr [ebp + N] ; mov ecx, dword ptr [ebp] ; mov edx, dword ptr [esi + N] ; push eax ; mov eax, dword ptr [esi + N] ; push ecx ; push edx ; push eax ; call EXT ; add esp, N ; test eax, eax ; jge +N ; push N ; push ebp ; push edi ; jmp +N ; push N ; push ebp ; push esi ; lea ecx, [esp + N] ; push ecx ; mov ecx, ebx ; call EXT ; mov eax, dword ptr [esp + N] ; mov edx, dword ptr [esp + N] ; pop edi ; pop esi ; pop ebp ; mov dword ptr [eax], edx ; mov byte ptr [eax + N], N ; pop ebx ; add esp, N ; ret N ; mov eax, dword ptr [esp + N] ; pop edi ; mov dword ptr [eax], esi ; pop esi ; pop ebp ; mov byte ptr [eax + N], N ; pop ebx ; add esp, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """struct S { wchar_t* b; wchar_t* e; wchar_t* c; };
struct Node { Node* right; Node* left; Node* parent; int color; S key; };
struct It { Node* p; };
struct R { Node* p; bool b; };
template<class T> __forceinline const T& mn(const T& a, const T& b) { return (b < a) ? b : a; }
static __forceinline int cmpi(const wchar_t* p, const wchar_t* q, unsigned n) {
  for (; n > 0; --n) { if (*p != *q) return *p < *q ? -1 : 1; ++p; ++q; }
  return 0;
}
static __forceinline bool lessf(const S& a, const S& b) {
  int la = (int)(a.e - a.b), lb = (int)(b.e - b.b);
  int r = cmpi(a.b, b.b, mn(la, lb));
  if (!r) r = (la < lb) ? -1 : (la > lb);
  return r < 0;
}
"""
def emit(va, A, N):
    f = "%08x" % va
    src = """struct T_%(f)s {
  int cmp; Node* aRight; Node* aLeft; Node* aParent;
  It __thiscall ins(Node* parent, const S& key, bool);
  R __thiscall K(const S& key, bool);
};
Node* __cdecl dec_%(f)s(Node*);
int __cdecl cmpf_%(f)s(const wchar_t*, const wchar_t*, const wchar_t*, const wchar_t*);
R T_%(f)s::K(const S& key, bool) {
  Node* lb = (Node*)&aRight; Node* cur = aParent; bool less = true;
  while (cur) { less = lessf(key, cur->key); lb = cur; cur = less ? cur->left : cur->right; }
  Node* par = lb;
  R r;
  if (less) {
    if (lb != aLeft) lb = dec_%(f)s(lb);
    else { It i = ins(par, key, false); r.p = i.p; r.b = true; return r; }
  }
  if (cmpf_%(f)s(lb->key.b, lb->key.e, key.b, key.e) < 0) { It i = ins(par, key, false); r.p = i.p; r.b = true; return r; }
  r.p = lb; r.b = false; return r;
}""" % dict(f=f)
    return src, "?K@T_%s@@QAE?AUR@@ABUS@@_N@Z" % f
