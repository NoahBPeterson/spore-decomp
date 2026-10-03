# EASTL vector<intrusive_ptr<T>>::DoInsertValues(pos, n, const T&) fully inlined (memcpy relocation, AddRef/Release vcalls).
# Not byte-exact yet: register allocation of n/after/pos and pNew store placement still differ (see findings).
PATTERN = 'push ecx ; push ebx ; mov ebx, dword ptr [esp + N] ; push ebp ; push esi ; mov esi, ecx ; mov eax, dword ptr [esi + N] ; mov ecx, dword ptr [esi + N] ; sub ecx, eax ; sar ecx, N ; push edi ; cmp ebx, ecx ; ja +N ; test ebx, ebx ; jbe +N ; mov edx, dword ptr [esp + N] ; mov ecx, dword ptr [edx] ; mov dword ptr [esp + N], ecx ; test ecx, ecx ; je +N ; mov eax, dword ptr [ecx] ; mov edx, dword ptr [eax + N] ; call edx ; mov ebp, dword ptr [esi + N] ; sub ebp, dword ptr [esp + N] ; mov eax, dword ptr [esp + N] ; mov edi, dword ptr [esi + N] ; sar ebp, N ; push eax ; cmp ebx, ebp ; jae +N ; add ebx, ebx ; push edi ; add ebx, ebx ; mov ebp, edi ; push edi ; sub ebp, ebx ; lea ecx, [esp + N] ; push ebp ; push ecx ; call EXT ; add dword ptr [esi + N], ebx ; mov esi, dword ptr [esp + N] ; push edi ; push ebp ; push esi ; call EXT ; lea edx, [esp + N] ; push edx ; add ebx, esi ; push ebx ; push esi ; call EXT ; add esp, N ; jmp +N ; lea ecx, [esp + N] ; push ecx ; sub ebx, ebp ; push ebx ; push edi ; call EXT ; mov ecx, dword ptr [esp + N] ; lea edx, [ebx*N] ; add dword ptr [esi + N], edx ; mov eax, dword ptr [esi + N] ; mov ebx, dword ptr [esp + N] ; push ecx ; push eax ; push edi ; lea edx, [esp + N] ; push ebx ; push edx ; call EXT ; lea ecx, [esp + N] ; push ecx ; lea eax, [ebp*N] ; add dword ptr [esi + N], eax ; push edi ; push ebx ; call EXT ; add esp, N ; mov ecx, dword ptr [esp + N] ; test ecx, ecx ; je +N ; mov edx, dword ptr [ecx] ; mov eax, dword ptr [edx + N] ; call eax ; pop edi ; pop esi ; pop ebp ; pop ebx ; pop ecx ; ret N ; sub eax, dword ptr [esi] ; sar eax, N ; lea ecx, [eax + eax] ; test eax, eax ; ja +N ; mov ecx, N ; add eax, ebx ; cmp ecx, eax ; jbe +N ; mov dword ptr [esp + N], ecx ; jmp +N ; mov dword ptr [esp + N], eax ; mov ecx, eax ; test ecx, ecx ; je +N ; push N ; push A ; push N ; push N ; add ecx, ecx ; add ecx, ecx ; push A ; push ecx ; call EXT ; add esp, N ; mov dword ptr [esp + N], eax ; jmp +N ; mov dword ptr [esp + N], N ; mov eax, dword ptr [esi] ; mov ebp, dword ptr [esp + N] ; mov edx, dword ptr [esp + N] ; mov edi, ebp ; sub edi, eax ; push edi ; push eax ; push edx ; call EXT ; mov ecx, dword ptr [esp + N] ; sar edi, N ; lea edi, [eax + edi*N] ; mov eax, dword ptr [esp + N] ; push eax ; push ecx ; push ebx ; push edi ; call EXT ; lea ebx, [edi + ebx*N] ; mov edi, dword ptr [esi + N] ; sub edi, ebp ; push edi ; push ebp ; push ebx ; call EXT ; sar edi, N ; lea edi, [eax + edi*N] ; mov eax, dword ptr [esi] ; add esp, N ; test eax, eax ; je +N ; cmp dword ptr [eax - N], N ; je +N ; push eax ; call EXT ; add esp, N ; mov eax, dword ptr [esp + N] ; mov edx, dword ptr [esp + N] ; mov dword ptr [esi], eax ; lea eax, [eax + edx*N] ; mov dword ptr [esi + N], edi ; mov dword ptr [esi + N], eax ; pop edi ; pop esi ; pop ebp ; pop ebx ; pop ecx ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """#include <string.h>
extern "C" {
void* __cdecl EASTL_allocator_allocate(unsigned, const char*, int, int, const char*, int) throw();
void __cdecl EASTL_allocator_deallocate(void*);
}
"""
PRELUDE += "struct RefObj {\n" + "".join("  virtual int v%d() throw();\n" % i for i in range(64)) + "};\n"
TPL = """struct IP_@ {
  RefObj* p;
  IP_@(const IP_@& o) throw() : p(o.p) { if (p) p->vADD(); }
  ~IP_@() throw() { if (p) p->vREL(); }
};
void __cdecl um(void*, IP_@*, IP_@*, IP_@*, IP_@*) throw();
void __cdecl cb(IP_@*, IP_@*, IP_@*) throw();
void __cdecl fl(IP_@*, IP_@*, IP_@*) throw();
void __cdecl ufn(IP_@*, unsigned, const IP_@*, IP_@*) throw();
extern const char s_@[]; extern const char n_@[];
struct V_@ {
  IP_@ *b, *e, *c;
  void f(IP_@* pos, unsigned n, const IP_@& v);
};
void V_@::f(IP_@* pos, unsigned n, const IP_@& v) {
  IP_@* pNew;
  if (n <= (unsigned)(c - e)) {
    if (n > 0) {
      IP_@ temp = v;
      IP_@* oe = e;
      unsigned after = e - pos;
      if (n < after) {
        um(&pNew, e - n, oe, oe, pos);
        e += n;
        cb(pos, oe - n, oe);
        fl(pos, pos + n, &temp);
      } else {
        ufn(oe, n - after, &temp, pos);
        e += n - after;
        um(&pos, pos, oe, e, pos);
        e += after;
        fl(pos, oe, &temp);
      }
    }
  } else {
    unsigned sz = e - b;
    unsigned grow = sz > 0 ? 2 * sz : 1;
    unsigned cap = grow > sz + n ? grow : sz + n;
    pNew = cap ? (IP_@*)EASTL_allocator_allocate(cap * 4, n_@, 0, 0, s_@, 0xd1) : 0;
    IP_@* p = pos;
    int d1 = (char*)p - (char*)b;
    IP_@* np = (IP_@*)memcpy(pNew, b, d1);
    np += d1 >> 2;
    ufn(np, n, &v, pos);
    np += n;
    int d2 = (char*)e - (char*)p;
    np = (IP_@*)memcpy(np, p, d2);
    np += d2 >> 2;
    if (b && ((int*)b)[-1]) EASTL_allocator_deallocate(b);
    b = pNew; e = np; c = pNew + cap;
  }
}

"""
def emit(va, A, N):
    s = TPL.replace("@", "%08x" % va).replace("vADD", "v%d" % (N[6] // 4)).replace("vREL", "v%d" % (N[29] // 4))
    return s, "?f@V_%08x@@QAEXPAUIP_%08x@@IABU2@@Z" % (va, va)
