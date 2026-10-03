# vector<4-byte T>::resize(n): if (n > size) insert-fill(end, n-size, T()) else erase(begin+n, end) (memcpy of 0 bytes inlined).
PATTERN = 'push esi ; push edi ; mov edi, ecx ; mov esi, dword ptr [edi + N] ; mov edx, dword ptr [edi] ; mov ecx, dword ptr [esp + N] ; mov eax, esi ; sub eax, edx ; sar eax, N ; cmp ecx, eax ; jbe +N ; lea edx, [esp + N] ; push edx ; sub ecx, eax ; push ecx ; push esi ; mov ecx, edi ; mov dword ptr [esp + N], N ; call EXT ; pop edi ; pop esi ; ret N ; push ebx ; mov eax, esi ; sub eax, esi ; push eax ; lea ebx, [edx + ecx*N] ; push esi ; push ebx ; call EXT ; sub esi, ebx ; sar esi, N ; neg esi ; add esp, N ; add esi, esi ; add esi, esi ; add dword ptr [edi + N], esi ; pop ebx ; pop edi ; pop esi ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = "#include <string.h>\n"
def emit(va, A, N):
    t = "%08x" % va
    src = ("struct V_%s { unsigned* b; unsigned* e; unsigned* c;\n"
           " void fill(unsigned* pos, unsigned n, const unsigned& v); void FUN_%s(unsigned n); };\n"
           "void V_%s::FUN_%s(unsigned n) {\n"
           "  unsigned sz = (unsigned)(e - b);\n"
           "  if (n > sz) { unsigned v = 0; fill(e, n - sz, v); }\n"
           "  else { unsigned* f = b + n; unsigned* l = e; memcpy(f, l, (char*)e - (char*)l); e -= (l - f); }\n"
           "}") % (t, t, t, t)
    return src, "?FUN_%s@V_%s@@QAEXI@Z" % (t, t)
