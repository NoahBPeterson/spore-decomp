# EASTL basic_string<char16_t> copy ctor: zero b/e/c, copy allocator (+0x10), reserve(n+1), memcpy, terminate.
# Key: load end before begin into locals, allocator as a member with a copy ctor.
PATTERN = 'push ebx ; push ebp ; xor eax, eax ; push esi ; mov esi, ecx ; mov ecx, dword ptr [esp + N] ; mov dword ptr [esi], eax ; mov dword ptr [esi + N], eax ; mov dword ptr [esi + N], eax ; mov eax, dword ptr [ecx + N] ; mov dword ptr [esi + N], eax ; mov eax, dword ptr [ecx + N] ; mov ebx, dword ptr [ecx] ; push edi ; sub eax, ebx ; mov edi, eax ; sar edi, N ; lea ecx, [edi + N] ; push ecx ; mov ecx, esi ; call EXT ; mov ebp, dword ptr [esi] ; add edi, edi ; push edi ; push ebx ; push ebp ; call EXT ; lea eax, [edi + ebp] ; add esp, N ; mov dword ptr [esi + N], eax ; xor edx, edx ; pop edi ; mov word ptr [eax], dx ; mov eax, esi ; pop esi ; pop ebp ; pop ebx ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = """#include <string.h>
inline wchar_t* cp_str(const wchar_t* f, const wchar_t* l, wchar_t* d){ memcpy(d,f,(l-f)*2); return d+(l-f);}
struct Al_str { unsigned h; Al_str(const Al_str& a) throw() : h(a.h) {} };
"""
def emit(va, A, N):
    return ("""struct S_%08x { wchar_t *b, *e, *c; unsigned x; Al_str a; void rs(unsigned) throw(); S_%08x(const S_%08x& o) throw(); };
S_%08x::S_%08x(const S_%08x& o) throw() : b(0), e(0), c(0), a(o.a) {
  const wchar_t* l = o.e; const wchar_t* f = o.b;
  rs((unsigned)(l - f) + 1);
  e = cp_str(f, l, b);
  *e = 0;
}""" % ((va,) * 6)), "??0S_%08x@@QAE@ABU0@@Z" % va
