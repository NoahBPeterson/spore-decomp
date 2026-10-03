# basic_string<wchar_t>::resize(n): n>size -> append(n-size, 0); n<size -> erase tail with memmove incl. terminator.
PATTERN = 'push esi ; push edi ; mov edi, ecx ; mov esi, dword ptr [edi + N] ; mov edx, dword ptr [edi] ; mov ecx, dword ptr [esp + N] ; mov eax, esi ; sub eax, edx ; sar eax, N ; cmp ecx, eax ; jae +N ; push ebx ; lea ebx, [edx + ecx*N] ; cmp ebx, esi ; je +N ; mov eax, esi ; sub eax, esi ; sar eax, N ; lea ecx, [eax + eax + N] ; push ecx ; push esi ; push ebx ; call dword ptr [A] ; sub esi, ebx ; sar esi, N ; neg esi ; add esi, esi ; add esp, N ; add dword ptr [edi + N], esi ; pop ebx ; pop edi ; pop esi ; ret N ; jbe +N ; sub ecx, eax ; push N ; push ecx ; mov ecx, edi ; call EXT ; pop edi ; pop esi ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = "#include <string.h>\n"
def emit(va, A, N):
    t = "%08x" % va
    src = ("struct S_%s { wchar_t* b; wchar_t* e; wchar_t* c;\n"
           " void fill(unsigned n, wchar_t v); void FUN_%s(unsigned n); };\n"
           "void S_%s::FUN_%s(unsigned n) {\n"
           "  unsigned sz = (unsigned)(e - b);\n"
           "  if (n < sz) { wchar_t* f = b + n; wchar_t* l = e;\n"
           "    if (f != l) { memmove(f, l, (e - l + 1) * 2); e -= (l - f); } }\n"
           "  else if (n > sz) fill(n - sz, 0);\n"
           "}") % (t, t, t, t)
    return src, "?FUN_%s@S_%s@@QAEXI@Z" % (t, t)
