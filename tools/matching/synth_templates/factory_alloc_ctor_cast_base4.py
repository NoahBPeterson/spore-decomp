# Factory: stdcall (unused arg, allocator*); allocator defaults to global;
#   p = Alloc(size, align, "Name", a); if (p && (q = T::T(p))) return (B1*)q;  // B1 at offset 4
PATTERN = 'mov eax, dword ptr [esp + N] ; test eax, eax ; jne +N ; call EXT ; push eax ; push A ; push N ; push N ; call EXT ; add esp, N ; test eax, eax ; je +N ; mov ecx, eax ; call EXT ; test eax, eax ; je +N ; add eax, N ; ret N ; xor eax, eax ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ("struct Alc;\nAlc* GetDefaultAlc();\n"
           "void* __cdecl AllocX(unsigned size, unsigned align, const char* name, Alc* a);\n"
           "struct B0 { virtual void f0(); };\nstruct B1 { virtual void f1(); };\n")
def emit(va, A, N):
    align, size = N[1], N[2]
    t = "T_%08x" % va
    src = ("struct %s : B0, B1 { %s* init(); };\n"
           "B1* __stdcall FUN_%08x(int, Alc* a) {\n"
           "  if (!a) a = GetDefaultAlc();\n"
           "  void* m = AllocX(%d, %d, \"%s\", a);\n"
           "  if (m) { %s* q = ((%s*)m)->init(); return q; }\n"
           "  return 0;\n}") % (t, t, va, size, align, "N%08x" % va, t, t)
    return src, "?FUN_%08x@@YGPAUB1@@HPAUAlc@@@Z" % va
