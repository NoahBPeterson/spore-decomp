# Member: call helper(mpBegin, mpCapacity) ; mCount = 0 ; if (mpCapacity > 1) EASTL_allocator_deallocate(mpBegin)
# Layout: pad@0, p@4, n@8, count@0xC. Plain /O2.
PATTERN = 'push esi ; mov esi, ecx ; mov eax, dword ptr [esi + N] ; mov ecx, dword ptr [esi + N] ; push eax ; push ecx ; mov ecx, esi ; call EXT ; cmp dword ptr [esi + N], N ; mov dword ptr [esi + N], N ; jbe +N ; mov edx, dword ptr [esi + N] ; push edx ; call EXT ; add esp, N ; pop esi ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = "void EASTL_allocator_deallocate(void* p);\n"
def emit(va, A, N):
    t = "%08x" % va
    src = ("struct C_%s { unsigned pad; void* p; unsigned n; unsigned c;\n"
           " void H(void* p, unsigned n); void FUN_%s(); };\n"
           "void C_%s::FUN_%s() { H(p, n); c = 0; if (n > 1) EASTL_allocator_deallocate(p); }") % (t, t, t, t)
    return src, "?FUN_%s@C_%s@@QAEXXZ" % (t, t)
