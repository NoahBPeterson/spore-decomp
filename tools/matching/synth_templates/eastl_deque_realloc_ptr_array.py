# EASTL deque_base::DoReallocPtrArray(nAdditional, side): recenter or reallocate the subarray pointer map.
PATTERN = 'push ecx ; mov eax, dword ptr [esp + N] ; push ebx ; push ebp ; push esi ; mov esi, ecx ; mov ecx, dword ptr [esi + N] ; mov edx, dword ptr [esi + N] ; sub edx, ecx ; mov ebx, edx ; sar ebx, N ; inc ebx ; push edi ; lea edi, [ebx + eax] ; mov eax, dword ptr [esi + N] ; lea ebp, [edi + edi] ; cmp eax, ebp ; ja +N ; mov edx, dword ptr [esp + N] ; cmp dword ptr [esi + N], edx ; lea ecx, [esi + N] ; jae +N ; lea ecx, [esp + N] ; mov ecx, dword ptr [ecx] ; push N ; push A ; push N ; lea ebp, [ecx + eax + N] ; push N ; lea edx, [ebp*N] ; push A ; push edx ; call EXT ; mov ecx, dword ptr [esi + N] ; mov edi, dword ptr [esp + N] ; mov dword ptr [esp + N], eax ; mov eax, dword ptr [esi] ; mov edx, ecx ; sub edx, eax ; sar edx, N ; add esp, N ; neg edi ; sbb edi, edi ; not edi ; and edi, dword ptr [esp + N] ; add edx, edi ; mov edi, dword ptr [esp + N] ; lea edi, [edi + edx*N] ; test eax, eax ; je +N ; mov eax, dword ptr [esi + N] ; sub eax, ecx ; add eax, N ; push eax ; push ecx ; push edi ; call EXT ; add esp, N ; mov eax, dword ptr [esi] ; test eax, eax ; je +N ; push eax ; call EXT ; add esp, N ; mov ecx, dword ptr [esp + N] ; mov dword ptr [esi], ecx ; mov dword ptr [esi + N], ebp ; jmp +N ; sub eax, edi ; mov edi, dword ptr [esp + N] ; shr eax, N ; neg edi ; sbb edi, edi ; not edi ; and edi, dword ptr [esp + N] ; add eax, edi ; mov edi, dword ptr [esi] ; lea edi, [edi + eax*N] ; cmp edi, ecx ; jae +N ; add edx, N ; push edx ; push ecx ; push edi ; call EXT ; jmp +N ; lea eax, [edx + N] ; push eax ; sar eax, N ; mov edx, ebx ; sub edx, eax ; push ecx ; lea eax, [edi + edx*N] ; push eax ; call dword ptr [A] ; add esp, N ; mov dword ptr [esi + N], edi ; mov eax, dword ptr [edi] ; mov dword ptr [esi + N], eax ; add eax, N ; mov dword ptr [esi + N], eax ; lea eax, [edi + ebx*N - N] ; mov dword ptr [esi + N], eax ; mov eax, dword ptr [eax] ; mov dword ptr [esi + N], eax ; pop edi ; add eax, N ; mov dword ptr [esi + N], eax ; pop esi ; pop ebp ; pop ebx ; pop ecx ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """#include <string.h>
extern "C" {
void* __cdecl EASTL_allocator_allocate(unsigned, const char*, int, int, const char*, int);
void __cdecl EASTL_allocator_deallocate(void*);
}
"""
TPL = """extern const char s_@[]; extern const char n_@[];
struct E_@ { char d[SZ]; };
struct D_@ {
  E_@** pa; unsigned n;
  E_@ *bc, *bb, *be; E_@** bp;
  E_@ *ec, *eb, *ee; E_@** ep;
  void f(unsigned add, int front);
};
template<class T> inline const T& mx_@(const T& a, const T& b) { return (a < b) ? b : a; }
void D_@::f(unsigned add, int side) {
    E_@** b0 = bp;
    int d = (int)ep - (int)b0;
    unsigned used = (unsigned)(d >> 2) + 1;
    unsigned nn = add + used;
    E_@** t;
    if (n <= nn * 2) {
      unsigned ns = n + mx_@(n, add) + 2;
      E_@** np = (E_@**)EASTL_allocator_allocate(ns * sizeof(E_@*), n_@, 0, 0, s_@, 0xd1);
      t = np + (((int)bp - (int)pa >> 2) + (side ? 0 : add));
      if (pa) memcpy(t, bp, (size_t)((int)ep - (int)bp + 4));
      if (pa) EASTL_allocator_deallocate(pa);
      pa = np; n = ns;
    } else {
      t = pa + ((n - nn) / 2) + (side ? 0 : add);
      if (t < b0) memcpy(t, b0, (size_t)(d + 4));
      else memmove(t + (used - ((unsigned)(d + 4) >> 2)), b0, (size_t)(d + 4));
    }
    bp = t;
    bb = *bp; be = (E_@*)((char*)bb + SZ);
    ep = bp + (used - 1);
    eb = *ep; ee = (E_@*)((char*)eb + SZ);
}
"""
def emit(va, A, N):
    s = TPL.replace("SZ", str(N[39])).replace("@", "%08x" % va)
    return s, "?f@D_%08x@@QAEXIH@Z" % va
