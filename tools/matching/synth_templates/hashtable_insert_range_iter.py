# EASTL hashtable::insert(first, last) over hashtable iterators: n = distance(first, last, tag);
# policy.GetRehashRequired(buckets, elems, n); rehash if needed; loop DoInsertValue(node, false_type).
# Iterators are by-value (node, bucket*) structs; the uninitialized empty tag local `Tag t;` gives the
# junk 5th push of eax. Next-pointer offset (4/8/16) comes from the node layout.
PATTERN = 'mov eax, dword ptr [esp + N] ; mov edx, dword ptr [esp + N] ; sub esp, N ; push esi ; push eax ; mov eax, dword ptr [esp + N] ; mov esi, ecx ; mov ecx, dword ptr [esp + N] ; push ecx ; mov ecx, dword ptr [esp + N] ; push edx ; push eax ; push ecx ; call EXT ; mov edx, dword ptr [esi + N] ; add esp, N ; push eax ; mov eax, dword ptr [esi + N] ; push edx ; push eax ; lea ecx, [esp + N] ; push ecx ; lea ecx, [esi + N] ; call EXT ; cmp byte ptr [esp + N], N ; je +N ; mov edx, dword ptr [esp + N] ; push edx ; mov ecx, esi ; call EXT ; mov eax, dword ptr [esp + N] ; cmp eax, dword ptr [esp + N] ; je +N ; lea ebx, [ebx] ; mov byte ptr [esp + N], N ; mov ecx, dword ptr [esp + N] ; push ecx ; push eax ; lea edx, [esp + N] ; push edx ; mov ecx, esi ; call EXT ; mov eax, dword ptr [esp + N] ; mov eax, dword ptr [eax + N] ; mov dword ptr [esp + N], eax ; test eax, eax ; jne +N ; mov ecx, dword ptr [esp + N] ; lea ebx, [ebx] ; add ecx, N ; mov dword ptr [esp + N], ecx ; mov eax, dword ptr [ecx] ; mov dword ptr [esp + N], eax ; test eax, eax ; je +N ; cmp eax, dword ptr [esp + N] ; jne +N ; pop esi ; add esp, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """struct Ft {};
struct Tag {};
struct Pr { bool b; unsigned n; };
struct Pol { void need(Pr*, unsigned, unsigned, unsigned); };
"""
def emit(va, A, N):
    off = N[21]
    s = """struct N_%(v)08x { char v[%(o)d]; N_%(v)08x* next; };
struct Res_%(v)08x { N_%(v)08x* n; N_%(v)08x** b; bool x; };
struct It_%(v)08x {
  N_%(v)08x* n; N_%(v)08x** b;
  void inc() { n = n->next; while (!n) n = *++b; }
  It_%(v)08x& operator++() { inc(); return *this; }
  bool operator!=(const It_%(v)08x& o) const { return n != o.n; }
};
unsigned __cdecl dist_%(v)08x(It_%(v)08x, It_%(v)08x, Tag);
struct H_%(v)08x {
  void* pad[2]; unsigned nb; unsigned ne; Pol pol;
  void rehash(unsigned);
  Res_%(v)08x ins(N_%(v)08x*, Ft);
  void f(It_%(v)08x first, It_%(v)08x last);
};
void H_%(v)08x::f(It_%(v)08x first, It_%(v)08x last) {
  Tag t;
  unsigned n = dist_%(v)08x(first, last, t);
  Pr r; pol.need(&r, nb, ne, n);
  if (r.b) rehash(r.n);
  for (; first != last; ++first) ins(first.n, Ft());
}""" % dict(v=va, o=off)
    return s, "?f@H_%08x@@QAEXUIt_%08x@@0@Z" % (va, va)
