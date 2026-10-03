# EASTL basic_string<char16_t>::set_capacity(n): grow in place via allocate+memcpy, else resize/copy/swap temp.
PATTERN = 'mov eax, dword ptr [esp + N] ; sub esp, N ; push esi ; mov esi, ecx ; cmp eax, -N ; je +N ; mov ecx, dword ptr [esi + N] ; sub ecx, dword ptr [esi] ; sar ecx, N ; cmp eax, ecx ; jbe +N ; push ebx ; push ebp ; push edi ; push N ; push A ; push N ; push N ; lea ebp, [eax + eax] ; push A ; push ebp ; call EXT ; mov ecx, dword ptr [esi] ; mov edi, eax ; mov eax, dword ptr [esi + N] ; sub eax, ecx ; sar eax, N ; add eax, eax ; mov ebx, eax ; push ebx ; push ecx ; push edi ; call EXT ; add ebx, edi ; xor edx, edx ; mov word ptr [ebx], dx ; mov eax, dword ptr [esi] ; mov ecx, dword ptr [esi + N] ; sub ecx, eax ; and ecx, A ; add esp, N ; cmp ecx, N ; jle +N ; test eax, eax ; je +N ; cmp eax, dword ptr [esi + N] ; je +N ; push eax ; call EXT ; add esp, N ; add ebp, edi ; mov dword ptr [esi], edi ; pop edi ; mov dword ptr [esi + N], ebp ; pop ebp ; mov dword ptr [esi + N], ebx ; pop ebx ; pop esi ; add esp, N ; ret N ; mov edx, dword ptr [esi + N] ; sub edx, dword ptr [esi] ; sar edx, N ; cmp eax, edx ; jae +N ; push eax ; mov ecx, esi ; call EXT ; push esi ; lea ecx, [esp + N] ; call EXT ; lea eax, [esp + N] ; push eax ; mov ecx, esi ; call EXT ; mov ecx, dword ptr [esp + N] ; mov eax, dword ptr [esp + N] ; sub ecx, eax ; and ecx, A ; cmp ecx, N ; jle +N ; test eax, eax ; je +N ; cmp eax, dword ptr [esp + N] ; je +N ; push eax ; call EXT ; add esp, N ; pop esi ; add esp, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = """#include <string.h>
extern "C" {
void* __cdecl EASTL_allocator_allocate(unsigned, const char*, int, int, const char*, int) throw();
void __cdecl EASTL_allocator_deallocate(void*) throw();
}
"""
TPL = """extern const char s_@[]; extern const char n_@[];
inline wchar_t* cp_@(const wchar_t* f, const wchar_t* l, wchar_t* d){ memcpy(d,f,(l-f)*2); return d+(l-f);}
struct S_@ {
  wchar_t *b, *e, *c; unsigned x; wchar_t* h;
  S_@(const S_@&) throw();
  void rs(unsigned) throw();
  void sw(S_@&) throw();
  ~S_@() throw() { if ((int)((char*)c - (char*)b & ~1u) > 2 && b && b != h) EASTL_allocator_deallocate(b); }
  void f(unsigned n);
};
void S_@::f(unsigned n) {
  if (n != (unsigned)-1 && n > (unsigned)(e - b)) {
    wchar_t* nb = (wchar_t*)EASTL_allocator_allocate(n * 2, n_@, 0, 0, s_@, 0xd1);
    wchar_t* ne = cp_@(b, e, nb);
    *ne = 0;
    if ((int)((char*)c - (char*)b & ~1u) > 2 && b && b != h) EASTL_allocator_deallocate(b);
    b = nb; c = nb + n; e = ne;
  } else {
    if (n < (unsigned)(e - b)) rs(n);
    S_@ t(*this);
    sw(t);
  }
}
"""
def emit(va, A, N):
    return TPL.replace("@", "%08x" % va), "?f@S_%08x@@QAEXI@Z" % va
