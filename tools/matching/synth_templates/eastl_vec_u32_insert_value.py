# EASTL vector<u32-sized POD>::DoInsertValue(pos, const T&) fully inlined; memmove for shift, memcpy for relocation.
PATTERN = 'push ecx ; push ebx ; push esi ; mov esi, ecx ; mov eax, dword ptr [esi + N] ; push edi ; cmp eax, dword ptr [esi + N] ; je +N ; mov ecx, dword ptr [esp + N] ; mov edi, dword ptr [esp + N] ; mov ebx, ecx ; cmp ecx, edi ; jb +N ; cmp ecx, eax ; jae +N ; lea ebx, [ecx + N] ; test eax, eax ; je +N ; mov ecx, dword ptr [eax - N] ; mov dword ptr [eax], ecx ; mov ecx, dword ptr [esi + N] ; lea eax, [ecx - N] ; sub eax, edi ; push eax ; sar eax, N ; add eax, eax ; add eax, eax ; sub ecx, eax ; push edi ; push ecx ; call dword ptr [A] ; mov edx, dword ptr [ebx] ; add esp, N ; mov dword ptr [edi], edx ; add dword ptr [esi + N], N ; pop edi ; pop esi ; pop ebx ; pop ecx ; ret N ; sub eax, dword ptr [esi] ; push ebp ; sar eax, N ; test eax, eax ; jbe +N ; add eax, eax ; mov dword ptr [esp + N], eax ; test eax, eax ; je +N ; push N ; push A ; push N ; push N ; add eax, eax ; add eax, eax ; push A ; push eax ; call EXT ; add esp, N ; mov ebp, eax ; jmp +N ; mov dword ptr [esp + N], N ; mov eax, dword ptr [esp + N] ; jmp +N ; xor ebp, ebp ; mov eax, dword ptr [esi] ; mov ebx, dword ptr [esp + N] ; mov edi, ebx ; sub edi, eax ; push edi ; push eax ; push ebp ; call EXT ; sar edi, N ; lea eax, [eax + edi*N] ; add esp, N ; test eax, eax ; je +N ; mov ecx, dword ptr [esp + N] ; mov edx, dword ptr [ecx] ; mov dword ptr [eax], edx ; mov edi, dword ptr [esi + N] ; sub edi, ebx ; push edi ; add eax, N ; push ebx ; push eax ; call EXT ; sar edi, N ; lea edi, [eax + edi*N] ; mov eax, dword ptr [esi] ; add esp, N ; test eax, eax ; je +N ; cmp dword ptr [eax - N], N ; je +N ; push eax ; call EXT ; add esp, N ; mov eax, dword ptr [esp + N] ; mov dword ptr [esi], ebp ; lea ecx, [ebp + eax*N] ; pop ebp ; mov dword ptr [esi + N], edi ; pop edi ; mov dword ptr [esi + N], ecx ; pop esi ; pop ebx ; pop ecx ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """#include <string.h>
extern "C" {
void* __cdecl EASTL_allocator_allocate(unsigned, const char*, int, int, const char*, int) throw();
void __cdecl EASTL_allocator_deallocate(void*);
}
"""
TPL = """extern const char s_@[]; extern const char n_@[];
struct V_@ {
  unsigned *b, *e, *c;
  void f(unsigned* pos, const unsigned& v);
};
void V_@::f(unsigned* pos, const unsigned& v) {
  if (e != c) {
    const unsigned* pv = &v;
    if (pv >= pos && pv < e) ++pv;
    if (e) *e = *(e - 1);
    unsigned* last = e - 1;
    memmove(e - (last - pos), pos, (char*)last - (char*)pos);
    *pos = *pv;
    ++e;
  } else {
    unsigned cnt = e - b;
    unsigned n = cnt > 0 ? 2 * cnt : 1;
    unsigned* nb = n ? (unsigned*)EASTL_allocator_allocate(n * 4, n_@, 0, 0, s_@, 0xd1) : 0;
    int n1 = (char*)pos - (char*)b;
    unsigned* np = (unsigned*)memcpy(nb, b, n1);
    np += n1 >> 2;
    if (np) *np = v;
    ++np;
    int n2 = (char*)e - (char*)pos;
    np = (unsigned*)memcpy(np, pos, n2);
    np += n2 >> 2;
    if (b && ((int*)b)[-1]) EASTL_allocator_deallocate(b);
    b = nb; e = np; c = nb + n;
  }
}
"""
def emit(va, A, N):
    s = TPL.replace("@", "%08x" % va)
    return s, "?f@V_%08x@@QAEXPAIABI@Z" % va
