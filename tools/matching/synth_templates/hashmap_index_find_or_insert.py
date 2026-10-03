# EASTL-style hash_map::operator[](const key&): find; if end() insert(value_type(key,0), tag) and return &it->second.
# 90-byte __thiscall member (ecx=this, ret 4). Shape reproduced: `it` in an inner scope (so its slot is shared
# with the value_type temp), tag arg is a 1-byte struct passed by value (stored into the dead param slot).
# The member is emitted as a __fastcall free function with an unused edx to get the same codegen as thiscall.
PATTERN = 'sub esp, N ; push esi ; push edi ; mov edi, dword ptr [esp + N] ; push edi ; lea eax, [esp + N] ; push eax ; mov esi, ecx ; call EXT ; mov ecx, dword ptr [esi + N] ; mov edx, dword ptr [esi + N] ; mov eax, dword ptr [esp + N] ; cmp eax, dword ptr [edx + ecx*N] ; jne +N ; mov eax, dword ptr [edi] ; mov dword ptr [esp + N], eax ; xor eax, eax ; mov byte ptr [esp + N], al ; mov ecx, dword ptr [esp + N] ; push ecx ; lea edx, [esp + N] ; mov dword ptr [esp + N], eax ; push edx ; lea eax, [esp + N] ; push eax ; mov ecx, esi ; call EXT ; mov eax, dword ptr [esp + N] ; pop edi ; add eax, N ; pop esi ; add esp, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """struct Node { int a; int val; };
struct It { Node* n; Node** b; };
struct VT { int key; int val; };
struct P { It it; bool b; };
struct Z { bool b; };
struct M {
  int pad; Node** buckets; unsigned nb;
  It find(const int& k);
  P insertz(const VT& v, Z b);
};
"""
def emit(va, A, N):
    body = ("int* __fastcall FUN_%08x(M* m, int, const int& k) {\n"
            "  Node* n;\n  { It it = m->find(k); n = it.n; }\n"
            "  if (n == m->buckets[m->nb]) {\n    VT v = { k, 0 };\n    Z z; z.b = false;\n"
            "    P r = m->insertz(v, z);\n    return &r.it.n->val;\n  }\n  return &n->val;\n}" % va)
    return body, "?FUN_%08x@@YIPAHPAUM@@HABH@Z" % va
