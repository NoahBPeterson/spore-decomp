# hash_map<Key8, T>::operator[]: it = find(key); if (it == end()) it = insert(pair(key, 0), true_type()); return &it->second.
# find/insert return a 12-byte iterator-ish object via hidden pointer; Tag is an empty struct passed by value
# (explains the byte store into the dead key-arg slot). Two stack layouts exist, picked by the `sub esp` immediate:
#   0x18: `it` scoped so its slot is shared with the pair temp; result of insert is a separate object.
#   0x1c: insert result constructed straight into `it` (placement new defeats the temp copy) and the pair has
#         a 4-byte unused tail (int extra) which makes the frame 0x1c.
# Callee bodies are external (relocations masked), so member declarations stand in for the real EASTL calls.
PATTERN = 'sub esp, N ; push esi ; push edi ; mov edi, dword ptr [esp + N] ; push edi ; lea eax, [esp + N] ; push eax ; mov esi, ecx ; call EXT ; mov ecx, dword ptr [esi + N] ; mov edx, dword ptr [esi + N] ; mov eax, dword ptr [esp + N] ; cmp eax, dword ptr [edx + ecx*N] ; jne +N ; mov eax, dword ptr [edi] ; mov ecx, dword ptr [edi + N] ; mov dword ptr [esp + N], eax ; xor eax, eax ; mov byte ptr [esp + N], al ; mov edx, dword ptr [esp + N] ; mov dword ptr [esp + N], eax ; push edx ; mov dword ptr [esp + N], ecx ; lea eax, [esp + N] ; push eax ; lea ecx, [esp + N] ; push ecx ; mov ecx, esi ; call EXT ; mov eax, dword ptr [esp + N] ; pop edi ; add eax, N ; pop esi ; add esp, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """inline void* operator new(unsigned, void* p) { return p; }
struct Key { int a, b; };
struct VT { Key first; int second; };
struct VT4 { Key first; int second; int extra; };
struct It { int *node; int *bk; int x; };
struct It2 { int *node; int *bk; int x; It2(){} It2(const It2& o):node(o.node),bk(o.bk),x(o.x){} };
struct Tag {};
"""
def emit(va, A, N):
    if N and N[0] == 0x1c:
        src = """struct M_%08x {
  int pad; int **buckets; int nb;
  It2 find(const Key& k);
  It2 insert(const VT4& v, Tag t);
  int& idx(const Key& k);
};
int& M_%08x::idx(const Key& k) {
  It2 it = find(k);
  if (it.node == buckets[nb]) {
    VT4 v; v.first = k; v.second = 0;
    new (&it) It2(insert(v, Tag()));
  }
  return it.node[2];
}""" % (va, va)
    else:
        src = """struct M_%08x {
  int pad; int **buckets; int nb;
  It find(const Key& k);
  It insert(const VT& v, Tag t);
  int& idx(const Key& k);
};
int& M_%08x::idx(const Key& k) {
  int* n;
  { It it = find(k); n = it.node; }
  if (n == buckets[nb]) {
    VT v; v.first = k; v.second = 0;
    It t = insert(v, Tag());
    return t.node[2];
  }
  return n[2];
}""" % (va, va)
    return src, "?idx@M_%08x@@QAEAAHABUKey@@@Z" % va
