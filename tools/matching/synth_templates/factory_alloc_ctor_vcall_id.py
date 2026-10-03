# Factory: stdcall (ICoreAllocator-like unused arg, allocator*) ; allocator defaults to global;
#   p = Alloc(size, align, "Name", allocator); if (p && (p = T::T(p))) return p->vN(ID); return 0;
PATTERN = 'mov eax, dword ptr [esp + N] ; test eax, eax ; jne +N ; call EXT ; push eax ; push A ; push N ; push N ; call EXT ; add esp, N ; test eax, eax ; je +N ; mov ecx, eax ; call EXT ; test eax, eax ; je +N ; mov edx, dword ptr [eax] ; mov ecx, eax ; mov eax, dword ptr [edx + N] ; push A ; call eax ; ret N ; xor eax, eax ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ("struct Alc;\nAlc* GetDefaultAlc();\n"
           "void* __cdecl AllocX(unsigned size, unsigned align, const char* name, Alc* a);\n"
           "struct VB { " + "".join("virtual void* v%d(unsigned id) = 0; " % i for i in range(64)) + "};\n")
def emit(va, A, N):
    align, size, slot = N[1], N[2], N[4] // 4
    t = "T_%08x" % va
    src = ("struct %s { %s* init(); };\n"
           "void* __stdcall FUN_%08x(int, Alc* a) {\n"
           "  if (!a) a = GetDefaultAlc();\n"
           "  void* m = AllocX(%d, %d, \"%s\", a);\n"
           "  if (m) { %s* q = ((%s*)m)->init(); if (q) return ((VB*)q)->v%d(0x%08xu); }\n"
           "  return 0;\n}") % (t, t, va, size, align, "N%08x" % va, t, t, slot, A[1])
    return src, "?FUN_%08x@@YGPAXHPAUAlc@@@Z" % va
