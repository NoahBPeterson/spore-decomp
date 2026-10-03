# EASTL basic_string<char16>::append(n, c): grow via reserve(max(newcap, size+n)), then fill n chars + terminator.
import json, os
PATTERN = json.load(open(os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "..", "..", "work/patterns.json")))
PATTERN = next(p["pattern"] for p in PATTERN if "rep stosw word ptr es:[edi], ax ; pop ebp ; mov eax, dword ptr [esi + N] ; mov word ptr [eax], bx" in p["pattern"] and "sar ecx, N ; push edi ; lea edx, [ecx - N]" in p["pattern"])
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "template<class T> inline const T& mx(const T& a, const T& b){ return (a<b)?b:a; }\ninline void fillp(unsigned short* f, unsigned short* l, unsigned short v){ for(; f<l; ++f) *f = v; }\n"
TPL = """struct S_@ {
  unsigned short *b, *e, *c;
  void grow(unsigned n);
  void reserve(unsigned n) {
    n = mx(n, (unsigned)(e - b));
    if (n + 1 > (unsigned)(c - b)) grow(n + 1);
  }
  S_@& f(unsigned n, unsigned short ch);
};
S_@& S_@::f(unsigned n, unsigned short ch) {
  const unsigned prev = (unsigned)(e - b);
  const unsigned cap = (unsigned)(c - b) - 1;
  if (prev + n > cap) {
    unsigned tot = prev + n;
    unsigned nc = (cap > 8) ? cap * 2 : 8;
    reserve(mx(nc, tot));
  }
  if (n > 0) {
    { unsigned short* p = e + 1; fillp(p, p + (n - 1), ch); }
    *e = ch;
    e += n;
    *e = 0;
  }
  return *this;
}
"""
def emit(va, A, N):
    t = "%08x" % va
    return TPL.replace("@", t), "?f@S_%s@@QAEAAU1@IG@Z" % t
