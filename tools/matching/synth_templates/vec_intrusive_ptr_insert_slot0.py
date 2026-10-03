# EASTL vector<intrusive_ptr<T>>::DoInsertValue inlined; AddRef slot 0, Release slot 1.
PATTERN = 'sub esp, N ; push ebx ; push ebp ; push esi ; push edi ; mov edi, ecx ; mov eax, dword ptr [edi + N] ; cmp eax, dword ptr [edi + N] ; je +N ; mov ecx, dword ptr [esp + N] ; mov ebp, dword ptr [esp + N] ; mov esi, ecx ; cmp ecx, ebp ; jb +N ; cmp ecx, eax ; jae +N ; lea esi, [ecx + N] ; test eax, eax ; je +N ; mov ecx, dword ptr [eax - N] ; mov dword ptr [eax], ecx ; test ecx, ecx ; je +N ; mov eax, dword ptr [ecx] ; mov edx, dword ptr [eax] ; call edx ; mov eax, dword ptr [edi + N] ; push eax ; add eax, -N ; push eax ; push ebp ; call EXT ; mov esi, dword ptr [esi] ; mov ebx, dword ptr [ebp] ; add esp, N ; cmp esi, ebx ; je +N ; test esi, esi ; je +N ; mov eax, dword ptr [esi] ; mov edx, dword ptr [eax] ; mov ecx, esi ; call edx ; mov dword ptr [ebp], esi ; test ebx, ebx ; je +N ; mov eax, dword ptr [ebx] ; mov edx, dword ptr [eax + N] ; mov ecx, ebx ; call edx ; add dword ptr [edi + N], N ; pop edi ; pop esi ; pop ebp ; pop ebx ; add esp, N ; ret N ; sub eax, dword ptr [edi] ; sar eax, N ; test eax, eax ; jbe +N ; add eax, eax ; mov dword ptr [esp + N], eax ; test eax, eax ; je +N ; push N ; push A ; push N ; push N ; add eax, eax ; add eax, eax ; push A ; push eax ; call EXT ; add esp, N ; mov dword ptr [esp + N], eax ; jmp +N ; mov dword ptr [esp + N], N ; mov eax, dword ptr [esp + N] ; jmp +N ; mov dword ptr [esp + N], N ; mov eax, dword ptr [edi] ; mov ebp, dword ptr [esp + N] ; mov ecx, dword ptr [esp + N] ; mov esi, ebp ; sub esi, eax ; push esi ; push eax ; push ecx ; call EXT ; sar esi, N ; lea ebx, [eax + esi*N] ; add esp, N ; test ebx, ebx ; je +N ; mov edx, dword ptr [esp + N] ; mov ecx, dword ptr [edx] ; mov dword ptr [ebx], ecx ; test ecx, ecx ; je +N ; mov eax, dword ptr [ecx] ; mov edx, dword ptr [eax] ; call edx ; mov esi, dword ptr [edi + N] ; sub esi, ebp ; push esi ; add ebx, N ; push ebp ; push ebx ; call EXT ; sar esi, N ; lea esi, [eax + esi*N] ; mov eax, dword ptr [edi] ; add esp, N ; test eax, eax ; je +N ; cmp eax, dword ptr [edi + N] ; je +N ; push eax ; call EXT ; add esp, N ; mov eax, dword ptr [esp + N] ; mov ecx, dword ptr [esp + N] ; lea edx, [eax + ecx*N] ; mov dword ptr [edi + N], esi ; mov dword ptr [edi], eax ; mov dword ptr [edi + N], edx ; pop edi ; pop esi ; pop ebp ; pop ebx ; add esp, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """#include <string.h>
extern "C" {
void* __cdecl EASTL_allocator_allocate(unsigned, const char*, int, int, const char*, int) throw();
void __cdecl EASTL_allocator_deallocate(void*);
}
inline void* operator new(unsigned, void* p) throw() { return p; }
inline void operator delete(void*, void*) {}
"""
PRELUDE += "struct RefObj {\n" + "".join("  virtual int v%d() throw();\n" % i for i in range(64)) + "};\n"
TPL = """extern const char s_@[]; extern const char n_@[];
struct IP_@ {
  RefObj* p;
  IP_@(const IP_@& o) throw() : p(o.p) { if (p) p->vADD(); }
  IP_@& operator=(const IP_@& o) throw() { RefObj* q = o.p; RefObj* old = p; if (q != old) { if (q) q->vADD(); p = q; if (old) old->vREL(); } return *this; }
};
IP_@* __cdecl h1_@(IP_@*, IP_@*, IP_@*) throw();
struct V_@ {
  IP_@ *b, *e, *c; int pad; IP_@* fixed;
  void f(IP_@* pos, const IP_@& v);
  static unsigned newcap(unsigned n) { return n > 0 ? 2 * n : 1; }
  static IP_@* alloc(unsigned n) { return n ? (IP_@*)EASTL_allocator_allocate(n * sizeof(IP_@), n_@, 0, 0, s_@, 0xd1) : 0; }
};
void V_@::f(IP_@* pos, const IP_@& v) {
  if (e != c) {
    const IP_@* pv = &v;
    if (pv >= pos && pv < e) ++pv;
    if (e) ::new((void*)e) IP_@(*(e - 1));
    h1_@(pos, e - 1, e);
    *pos = *pv;
    ++e;
  } else {
    unsigned n = newcap(e - b);
    IP_@* nb = alloc(n);
    int d1 = (char*)pos - (char*)b;
    IP_@* np = (IP_@*)memcpy(nb, b, d1);
    np += d1 >> 2;
    if (np) ::new((void*)np) IP_@(v);
    ++np;
    int d2 = (char*)e - (char*)pos;
    np = (IP_@*)memcpy(np, pos, d2);
    np += d2 >> 2;
    if (b && b != fixed) EASTL_allocator_deallocate(b);
    b = nb; e = np; c = nb + n;
  }
}
"""
def emit(va, A, N):
    s = TPL.replace("@", "%08x" % va).replace("vADD", "v0").replace("vREL", "v1")
    return s, "?f@V_%08x@@QAEXPAUIP_%08x@@ABU2@@Z" % (va, va)
