# EASTL rb-tree set/map hinted insert: rbtree::DoInsertKey(const_iterator position, const key_type& key, true_type)
# (real EASTL source shape: inlined DoInsertValueImpl, RBTreeIncrement, fallback DoInsertKey(key, true_type())).
PATTERN = 'mov eax, dword ptr [esp + N] ; sub esp, N ; push ebx ; push ebp ; push esi ; mov esi, ecx ; mov ebx, dword ptr [esi + N] ; lea ebp, [esi + N] ; push edi ; cmp eax, ebx ; je +N ; cmp eax, ebp ; je +N ; push eax ; call EXT ; mov edx, dword ptr [esp + N] ; mov ebx, eax ; mov eax, dword ptr [esp + N] ; mov ecx, dword ptr [eax] ; add esp, N ; cmp dword ptr [edx + N], ecx ; jae +N ; cmp ecx, dword ptr [ebx + N] ; jae +N ; cmp dword ptr [edx], N ; mov ecx, esi ; je +N ; push eax ; call EXT ; push N ; push ebp ; mov edi, eax ; push ebx ; push edi ; call EXT ; mov eax, dword ptr [esp + N] ; add esp, N ; inc dword ptr [esi + N] ; mov dword ptr [eax], edi ; pop edi ; pop esi ; pop ebp ; pop ebx ; add esp, N ; ret N ; mov edi, dword ptr [esp + N] ; push N ; push eax ; push edx ; push edi ; call EXT ; mov eax, edi ; pop edi ; pop esi ; pop ebp ; pop ebx ; add esp, N ; ret N ; cmp dword ptr [esi + N], N ; mov eax, dword ptr [esp + N] ; je +N ; mov ecx, dword ptr [eax] ; cmp dword ptr [ebx + N], ecx ; jae +N ; cmp ebx, ebp ; je +N ; mov dword ptr [esp + N], N ; cmp ecx, dword ptr [ebx + N] ; jae +N ; mov dword ptr [esp + N], N ; push eax ; mov ecx, esi ; call EXT ; mov edx, dword ptr [esp + N] ; push edx ; jmp +N ; mov byte ptr [esp + N], N ; mov ecx, dword ptr [esp + N] ; push ecx ; push eax ; lea edx, [esp + N] ; push edx ; mov ecx, esi ; call EXT ; mov eax, dword ptr [esp + N] ; mov ecx, dword ptr [esp + N] ; pop edi ; pop esi ; pop ebp ; mov dword ptr [eax], ecx ; pop ebx ; add esp, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """
typedef unsigned int u32;
struct NodeBase { NodeBase* r; NodeBase* l; NodeBase* p; u32 color; };
struct Node : NodeBase { u32 key; };
struct Iter { Node* n; };
struct Pair { Iter first; bool second; };
struct TT {};
NodeBase* __cdecl Inc(const NodeBase*);
void __cdecl RBInsert(NodeBase*, NodeBase*, NodeBase*, int);
struct Tree {
  char pad0[4];
  NodeBase anchor;
  u32 size;
  Node* CreateNode(const u32& k);
  Iter InsImpl(Node* parent, const u32& key, bool forceLeft);
  void InsKey(Pair& out, const u32& key, TT);
};
Iter Tree::InsImpl(Node* parent, const u32& key, bool forceLeft) {
  int side = (forceLeft || parent == (Node*)&anchor || key < parent->key) ? 0 : 1;
  Node* n = CreateNode(key);
  RBInsert(n, parent, &anchor, side);
  ++size;
  Iter it = { n };
  return it;
}
"""
def emit(va, A, N):
    s = """struct T_%08x : Tree { Iter Ins(Iter pos, const u32& key, TT); };
Iter T_%08x::Ins(Iter pos, const u32& key, TT) {
  if (pos.n != (Node*)anchor.r && pos.n != (Node*)&anchor) {
    Iter nx = { (Node*)Inc(pos.n) };
    if (pos.n->key < key && key < nx.n->key) {
      if (pos.n->r) return InsImpl(nx.n, key, true);
      return InsImpl(pos.n, key, false);
    }
    { Pair p; InsKey(p, key, TT()); return p.first; }
  }
  if (size && ((Node*)anchor.r)->key < key)
    return InsImpl((Node*)anchor.r, key, false);
  { Pair p; InsKey(p, key, TT()); return p.first; }
}""" % (va, va)
    return s, "?Ins@T_%08x@@QAE?AUIter@@U2@ABIUTT@@@Z" % va
