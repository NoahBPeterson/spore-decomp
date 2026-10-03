# EASTL basic_string<char16>::push_back(c): if full, reserve(max(max(cap*2,8),size+1)) via ref-returning min/max, then store c + terminator.
import json, os
_P = json.load(open(os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "..", "..", "work/patterns.json")))
PATTERN = next(p["pattern"] for p in _P if p["pattern"].startswith("sub esp, N ; push esi ; mov esi, ecx ; mov eax, dword ptr [esi + N] ; mov ecx, dword ptr [esi + N] ; lea edx, [eax + N] ; cmp edx, ecx ; jne +N ; mov edx, dword ptr [esi] ; sub ecx, edx") and "mov cx, word ptr [esp + N]" in p["pattern"])
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "template<class T> inline const T& mx(const T& a, const T& b){ return (a<b)?b:a; }\n"
TPL = """struct S_@ {
  unsigned short *b, *e, *c;
  void grow(unsigned n);
  void reserve(unsigned n) {
    n = mx(n, (unsigned)(e - b));
    if (n + 1 > (unsigned)(c - b)) grow(n + 1);
  }
  void f(unsigned short ch);
};
void S_@::f(unsigned short ch) {
  if (e + 1 == c) {
    const unsigned prev = (unsigned)(e - b);
    const unsigned tot = prev + 1;
    const unsigned cap = (unsigned)(c - b) - 1;
    reserve(mx((unsigned)((cap > 8) ? cap * 2 : 8), tot));
  }
  *e++ = ch;
  *e = 0;
}
"""
def emit(va, A, N):
    t = "%08x" % va
    return TPL.replace("@", t), "?f@S_%s@@QAEXG@Z" % t
