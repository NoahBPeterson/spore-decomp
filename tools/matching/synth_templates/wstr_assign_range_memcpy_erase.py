# basic_string<wchar_t>::assign(first,last) with ptr range: shorter -> memcpy + append rest via helper; else memcpy + erase tail (memmove incl. terminator)
PATTERN = 'push ebx ; mov ebx, dword ptr [esp + N] ; push esi ; mov esi, ecx ; mov edx, dword ptr [esi] ; mov ecx, dword ptr [esi + N] ; push edi ; mov edi, dword ptr [esp + N] ; mov eax, ebx ; sub eax, edi ; sub ecx, edx ; sar eax, N ; sar ecx, N ; cmp eax, ecx ; ja +N ; push ebp ; lea ebp, [eax + eax] ; push ebp ; push edi ; push edx ; call EXT ; mov ebx, dword ptr [esi] ; mov edi, dword ptr [esi + N] ; add ebx, ebp ; add esp, N ; pop ebp ; cmp ebx, edi ; je +N ; mov eax, edi ; sub eax, edi ; sar eax, N ; lea ecx, [eax + eax + N] ; push ecx ; push edi ; push ebx ; call dword ptr [A] ; sub edi, ebx ; sar edi, N ; neg edi ; add esp, N ; add edi, edi ; add dword ptr [esi + N], edi ; pop edi ; mov eax, esi ; pop esi ; pop ebx ; ret N ; lea eax, [ecx + ecx] ; push eax ; push edi ; push edx ; call EXT ; mov ecx, dword ptr [esi + N] ; sub ecx, dword ptr [esi] ; add esp, N ; sar ecx, N ; lea edx, [edi + ecx*N] ; push ebx ; push edx ; mov ecx, esi ; call EXT ; pop edi ; mov eax, esi ; pop esi ; pop ebx ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = "#include <string.h>\n"
def emit(va, A, N):
    t = "%08x" % va
    src = ("struct S_%s { wchar_t* b; wchar_t* e; wchar_t* c;\n"
           " S_%s& app(const wchar_t* f, const wchar_t* l);\n"
           " S_%s& FUN_%s(const wchar_t* f, const wchar_t* l); };\n"
           "S_%s& S_%s::FUN_%s(const wchar_t* f, const wchar_t* l) {\n"
           "  unsigned n = l - f;\n"
           "  if (n <= (unsigned)(e - b)) {\n"
           "    memcpy(b, f, n * 2);\n"
           "    wchar_t* d = b + n; wchar_t* q = e;\n"
           "    if (d != q) { memmove(d, q, (e - q + 1) * 2); e -= (q - d); }\n"
           "  } else {\n"
           "    memcpy(b, f, (e - b) * 2);\n"
           "    app(f + (e - b), l);\n"
           "  }\n"
           "  return *this;\n}") % ((t,)*7)
    return src, "?FUN_%s@S_%s@@QAEAAU1@PB_W0@Z" % (t, t)
