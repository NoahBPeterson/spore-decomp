# vector<4-byte T>::resize(n): if (n > size) Fill(end, n-size, T()) else Erase(begin+n, end); both helpers external calls with end/ptr args pushed, no ecx.
PATTERN = 'mov edx, dword ptr [ecx] ; mov eax, dword ptr [esp + N] ; push esi ; mov esi, dword ptr [ecx + N] ; push edi ; mov edi, esi ; sub edi, edx ; sar edi, N ; cmp eax, edi ; jbe +N ; lea edi, [esp + N] ; push edi ; mov edi, esi ; sub edi, edx ; sar edi, N ; sub eax, edi ; push eax ; push esi ; mov dword ptr [esp + N], N ; call EXT ; pop edi ; pop esi ; ret N ; push esi ; lea eax, [edx + eax*N] ; push eax ; call EXT ; pop edi ; pop esi ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = ""
def emit(va, A, N):
    t = "%08x" % va
    src = """struct V_@ { unsigned* b; unsigned* e; unsigned* c; unsigned size() const { return (unsigned)(e - b); } void FUN_@(unsigned n); };
void __stdcall F_@(unsigned* pos, unsigned n, const unsigned* v);
void __stdcall E_@(unsigned* f, unsigned* l);
void V_@::FUN_@(unsigned n) {
  unsigned* be = b; unsigned* en = e;
  if (n > size()) { unsigned x = 0; F_@(en, n - size(), &x); }
  else E_@(be + n, en);
}""".replace("@", t)
    return src, "?FUN_%s@V_%s@@QAEXI@Z" % (t, t)
