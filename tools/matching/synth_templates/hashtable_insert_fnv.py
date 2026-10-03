# EASTL-style hashtable unique insert (FNV-1 string hash, chained buckets, rehash policy). Best attempt; not byte-exact.
PATTERN = 'mov eax, dword ptr [esp + N] ; sub esp, N ; push ebx ; push ebp ; push esi ; mov esi, ecx ; mov ecx, dword ptr [eax] ; movzx eax, byte ptr [ecx] ; push edi ; mov ebp, A ; test eax, eax ; je +N ; jmp +N ; lea ecx, [ecx] ; imul ebp, ebp, A ; inc ecx ; xor ebp, eax ; movzx eax, byte ptr [ecx] ; test eax, eax ; jne +N ; mov ecx, dword ptr [esi + N] ; xor edx, edx ; mov eax, ebp ; div ecx ; mov ecx, dword ptr [esi + N] ; mov ebx, edx ; mov edi, dword ptr [ecx + ebx*N] ; lea eax, [ecx + ebx*N] ; mov dword ptr [esp + N], eax ; test edi, edi ; je +N ; lea esp, [esp] ; mov edx, dword ptr [esp + N] ; push edi ; push edx ; call EXT ; add esp, N ; test al, al ; jne +N ; mov edi, dword ptr [edi + N] ; test edi, edi ; jne +N ; jmp +N ; test edi, edi ; jne +N ; mov eax, dword ptr [esi + N] ; push N ; push eax ; mov eax, dword ptr [esi + N] ; push eax ; lea ecx, [esp + N] ; push ecx ; lea ecx, [esi + N] ; call EXT ; mov edx, dword ptr [esp + N] ; push edx ; mov ecx, esi ; call EXT ; cmp byte ptr [esp + N], N ; mov edi, eax ; je +N ; mov ecx, dword ptr [esp + N] ; xor edx, edx ; mov eax, ebp ; div ecx ; push ecx ; mov ecx, esi ; mov ebx, edx ; call EXT ; mov eax, dword ptr [esi + N] ; lea ecx, [ebx*N] ; mov edx, dword ptr [ecx + eax] ; mov dword ptr [edi + N], edx ; mov eax, dword ptr [esi + N] ; mov dword ptr [ecx + eax], edi ; mov eax, dword ptr [esp + N] ; inc dword ptr [esi + N] ; mov edx, dword ptr [esi + N] ; mov dword ptr [eax], edi ; pop edi ; pop esi ; add edx, ecx ; pop ebp ; mov dword ptr [eax + N], edx ; mov byte ptr [eax + N], N ; pop ebx ; add esp, N ; ret N ; mov eax, dword ptr [esp + N] ; mov ecx, dword ptr [esp + N] ; mov dword ptr [eax], edi ; pop edi ; pop esi ; pop ebp ; mov dword ptr [eax + N], ecx ; mov byte ptr [eax + N], N ; pop ebx ; add esp, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """typedef unsigned int u32;
struct Node { char pad[0x14]; Node* next; };
struct Key { const char* s; };
bool cmp(const Key*, Node*);
struct Res { Node* node; Node** bucket; bool ins; };
struct RR { bool need; u32 n; };
struct Policy { char p[16]; RR req(u32 b, u32 e, u32 a); };
struct Tab {
  int pad0; Node** buckets; u32 nb; u32 ne; Policy pol;
  void rehash(u32 n);
  Node* alloc(const Key* k);
};
"""
BODY = """Res T_%(v)s::ins(const Key& kr, int) {
  Res r;
  const Key* k = &kr;
  u32 h = 0x811c9dc5;
  const unsigned char* s = (const unsigned char*)k->s;
  u32 c = *s;
  while (c) { h = (h * 0x1000193) ^ c; c = *++s; }
  u32 i = h %% nb;
  Node** bk = buckets + i;
  Node* n = *bk;
  for (; n; n = n->next)
    if (cmp(k, n)) break;
  if (n) { r.node = n; r.bucket = bk; r.ins = false; return r; }
  RR rr = pol.req(nb, ne, 1);
  Node* nn = alloc(k);
  if (rr.need) { i = h %% rr.n; rehash(rr.n); }
  nn->next = buckets[i];
  buckets[i] = nn;
  ++ne;
  r.node = nn; r.bucket = buckets + i; r.ins = true;
  return r;
}"""
def emit(va, A, N):
    v = "%08x" % va
    return "struct T_%s : Tab { Res ins(const Key&, int); };\n" % v + BODY % {"v": v}, "?ins@T_%s@@QAE?AURes@@ABUKey@@H@Z" % v
