PATTERN = 'mov eax, dword ptr [esp + N] ; push esi ; mov esi, ecx ; cmp eax, N ; jbe +N ; push edi ; push N ; push A ; push N ; push N ; lea edi, [eax + eax] ; push A ; push edi ; call EXT ; add esp, N ; add edi, eax ; mov dword ptr [esi + N], edi ; pop edi ; mov dword ptr [esi], eax ; mov dword ptr [esi + N], eax ; pop esi ; ret N ; mov dword ptr [esi], A ; mov dword ptr [esi + N], A ; mov dword ptr [esi + N], A ; pop esi ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ("typedef unsigned int size_t;\n"
           "void* EAL(size_t size, const char* name, int flags, unsigned dbg, const char* file, int line);\n")
def emit(va, A, N):
    src = ("extern const char s_%08x[]; extern const char s_%08x[]; extern const unsigned short e_%08x[];\n"
           "struct S_%08x { unsigned short *b, *e, *c;\n"
           "  void FUN_%08x(unsigned n);\n};\n"
           "void S_%08x::FUN_%08x(unsigned n) {\n"
           "  if (n > 1) { unsigned short* p = (unsigned short*)EAL(n * 2, s_%08x, 0, 0, s_%08x, %d); c = p + n; b = p; e = p; }\n"
           "  else { b = (unsigned short*)e_%08x; e = (unsigned short*)e_%08x; c = (unsigned short*)e_%08x + 1; }\n}\n"
           % (A[0], A[1], A[2], va, va, va, va, A[1], A[0], N[2], A[2], A[3], A[4]-2))
    return src, "?FUN_%08x@S_%08x@@QAEXI@Z" % (va, va)
