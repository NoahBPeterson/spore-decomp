# Tree insert_unique -> pair<iterator,bool> for a map keyed by a (begin,end) byte range with memcmp-style compare.
# Shape-close but NOT byte-exact: this lands in ebp instead of ebx, kl in ebx (lazy push), y/j roles swapped.
PATTERN = 'sub esp, N ; push ebx ; push ebp ; push esi ; mov ebx, ecx ; push edi ; mov edi, dword ptr [ebx + N] ; lea esi, [ebx + N] ; mov al, N ; test edi, edi ; je +N ; mov eax, dword ptr [esp + N] ; mov edx, dword ptr [eax] ; mov ebp, dword ptr [eax + N] ; sub ebp, edx ; mov dword ptr [esp + N], edx ; mov dword ptr [esp + N], ebp ; jmp +N ; lea ebx, [ebx] ; mov edx, dword ptr [esp + N] ; mov eax, dword ptr [edi + N] ; mov esi, dword ptr [edi + N] ; sub esi, eax ; cmp esi, ebp ; mov dword ptr [esp + N], esi ; lea ecx, [esp + N] ; jl +N ; lea ecx, [esp + N] ; mov ecx, dword ptr [ecx] ; push ecx ; push eax ; push edx ; call EXT ; add esp, N ; test eax, eax ; jne +N ; cmp ebp, esi ; jge +N ; or eax, A ; jmp +N ; xor eax, eax ; cmp ebp, esi ; setg al ; test eax, eax ; setl al ; mov esi, edi ; test al, al ; je +N ; mov edi, dword ptr [edi + N] ; jmp +N ; mov edi, dword ptr [edi] ; test edi, edi ; jne +N ; mov edi, esi ; test al, al ; je +N ; cmp esi, dword ptr [ebx + N] ; je +N ; push esi ; call EXT ; add esp, N ; mov esi, eax ; mov ebp, dword ptr [esp + N] ; lea edx, [esi + N] ; push ebp ; push edx ; call EXT ; add esp, N ; test al, al ; je +N ; push N ; push ebp ; push edi ; jmp +N ; mov edx, dword ptr [esp + N] ; push N ; push edx ; push esi ; lea eax, [esp + N] ; push eax ; mov ecx, ebx ; call EXT ; mov eax, dword ptr [esp + N] ; mov ecx, dword ptr [esp + N] ; pop edi ; pop esi ; pop ebp ; mov dword ptr [eax], ecx ; mov byte ptr [eax + N], N ; pop ebx ; add esp, N ; ret N ; mov eax, dword ptr [esp + N] ; pop edi ; mov dword ptr [eax], esi ; pop esi ; pop ebp ; mov byte ptr [eax + N], N ; pop ebx ; add esp, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """extern "C" int __cdecl FUN_005f7870(const char*, const char*, int);
struct Str { const char* b; const char* e; };
struct Node { Node* r; Node* l; Node* p; int c; Str key; };
struct Res { Node* it; bool ins; };
Node* __cdecl FUN_009215c0(Node*);
bool __cdecl FUN_00812210(const Str*, const Str*);
struct T2 {
  int pad0; Node* hdr; Node* lm; Node* root;
  void __thiscall Link(Node**, Node*, const Str&, int);
};
static inline int cmp(const char* ab, int la, const Str& b) {
  int lb = (int)(b.e - b.b);
  const int& m = (lb < la) ? lb : la;
  int r = FUN_005f7870(ab, b.b, m);
  if (r) return r;
  return la < lb ? -1 : (la > lb);
}
"""
BODY = """Res T2::Ins(const Str* kp, int) {
  Node* y = (Node*)&hdr; Node* x = root; bool less = true;
  if (x) {
    const char* kb = kp->b; int kl = (int)(kp->e-kp->b);
    do { less = cmp(kb, kl, x->key) < 0; y = x; x = less ? x->l : x->r; } while (x);
  }
  Node* j = y;
  Res res;
  if (less) {
    if (y == lm) goto ins;
    j = FUN_009215c0(y);
  }
  if (FUN_00812210(&j->key, kp)) goto ins;
  res.it = j; res.ins = false; return res;
ins:
  Link((Node**)&kp, y, *kp, 0);
  res.it = *(Node**)&kp; res.ins = true; return res;
}"""
def emit(va, A, N):
    # one class per instance so member names stay distinct
    n = "T_%08x" % va
    src = ("struct %s : T2 { Res __thiscall Ins(const Str* kp, int); };\n" % n) + BODY.replace("T2::Ins", n + "::Ins").replace("Res T2", "Res T2")
    src = src.replace("Link(", "T2::Link(")
    return src, "?Ins@%s@@QAE?AURes@@PBUStr@@H@Z" % n
