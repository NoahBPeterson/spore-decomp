# Member: H(mpBegin, n) ; if (mpBegin && ((int*)mpBegin)[-1]) EASTL_allocator_deallocate(mpBegin)
PATTERN = 'push esi ; mov esi, ecx ; mov eax, dword ptr [esi + N] ; mov ecx, dword ptr [esi] ; push eax ; push ecx ; mov ecx, esi ; call EXT ; mov esi, dword ptr [esi] ; test esi, esi ; je +N ; cmp dword ptr [esi - N], N ; je +N ; push esi ; call EXT ; add esp, N ; pop esi ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = "void EASTL_allocator_deallocate(void* p);\n"
def emit(va, A, N):
    t = "%08x" % va
    src = ("struct C_%s { int* p; void* n;\n"
           " void H(int* p, void* n); void FUN_%s(); };\n"
           "void C_%s::FUN_%s() { H(p, n); if (p && p[-1]) EASTL_allocator_deallocate(p); }") % (t, t, t, t)
    return src, "?FUN_%s@C_%s@@QAEXXZ" % (t, t)
