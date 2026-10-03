# EASTL basic_string<char16_t>::append(first, last) with ptr range: grow via allocate+2 memcpy when
# old+n > capacity (newcap = max(cap>8 ? cap*2 : 8, old+n)), else in-place memcpy tail + terminator.
import json, os
_P = json.load(open(os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "..", "..", "work/patterns.json")))
PATTERN = next(p["pattern"] for p in _P if p["pattern"].startswith("push ecx ; mov edx, dword ptr [esp + N] ; mov eax, dword ptr [esp + N] ; push esi ; mov esi, ecx ; cmp eax, edx ; je +N ; push ebx ; mov ebx, dword ptr [esi] ; push ebp"))
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = """#include <string.h>
extern "C" {
void* __cdecl EASTL_allocator_allocate(unsigned, const char*, int, int, const char*, int) throw();
void __cdecl EASTL_allocator_deallocate(void*) throw();
}
inline wchar_t* cp(const wchar_t* f, const wchar_t* l, wchar_t* d){ memcpy(d,f,(l-f)*2); return d+(l-f);}
template<class T> inline const T& mx(const T& a, const T& b){ return (a<b)?b:a; }
"""
TPL = """extern const char s_@[]; extern const char n_@[];
struct S_@ {
  wchar_t *b, *e, *c; unsigned x; wchar_t* h;
  S_@& f(const wchar_t* pb, const wchar_t* pe);
};
S_@& S_@::f(const wchar_t* pb, const wchar_t* pe) {
  if (pb != pe) {
    const unsigned old = (unsigned)(e - b);
    const int n = (int)(pe - pb);
    const unsigned cap = (unsigned)(c - b) - 1;
    if (old + n > cap) {
      const unsigned len = old + n;
      unsigned nc = cap > 8 ? cap * 2 : 8u;
      nc = mx(nc, len);
      ++nc;
      wchar_t* nb = (wchar_t*)EASTL_allocator_allocate(nc * 2, n_@, 0, 0, s_@, 0xd1);
      wchar_t* ne;
      ne = cp(b, e, nb);
      ne = cp(pb, pe, ne);
      *ne = 0;
      if ((int)((char*)c - (char*)b & ~1u) > 2 && b && b != h) EASTL_allocator_deallocate(b);
      b = nb; e = ne; c = nb + nc;
    } else {
      const wchar_t* p1 = pb + 1;
      cp(p1, pe, e + 1);
      e[n] = 0;
      *e = *pb;
      e += n;
    }
  }
  return *this;
}
"""
def emit(va, A, N):
    return TPL.replace("@", "%08x" % va), "?f@S_%08x@@QAEAAU1@PB_W0@Z" % va
