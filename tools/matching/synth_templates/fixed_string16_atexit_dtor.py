# atexit destructor (??__F) of a file-scope EASTL fixed_string<wchar_t>-like global:
#   if ((mpCapacity - mpBegin) > 1 && mpBegin && mpBegin != mAllocator.mpPoolBegin) deallocate(mpBegin)
# Layout: mpBegin@0, mpEnd@4, mpCapacity@8, allocator {name@0xC, mpPoolBegin@0x10}.
# (cap-begin)/2 > 1 is strength-reduced to ((cap-begin) & ~1) > 2. Plain /O2.
PATTERN = 'mov ecx, dword ptr [A] ; mov eax, dword ptr [A] ; sub ecx, eax ; and ecx, A ; cmp ecx, N ; jle +N ; test eax, eax ; je +N ; cmp eax, dword ptr [A] ; je +N ; push eax ; call EXT ; pop ecx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """void EASTL_allocator_deallocate(void* p);
struct FixedAlloc16 {
    void* mpName;
    void* mpPoolBegin;
    void deallocate(void* p, unsigned n) { if (p != mpPoolBegin) EASTL_allocator_deallocate(p); }
};
struct FixedString16 {
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity; FixedAlloc16 mAllocator;
    void DoFree(wchar_t* p, unsigned n) { if (p) mAllocator.deallocate(p, n); }
    ~FixedString16() { if ((mpCapacity - mpBegin) > 1) DoFree(mpBegin, (unsigned)(mpCapacity - mpBegin)); }
};
"""
def emit(va, A, N):
    cap, begin, mask, pool = A
    if (cap, mask, pool, N) == (begin + 8, 0xfffffffe, begin + 0x10, [2]):
        return "FixedString16 g_%08x;" % begin, "??__Fg_%08x@@YAXXZ" % begin
    src = ("extern char* g_%08x; extern char* g_%08x; extern char* g_%08x;\n"
           "void FUN_%08x() {\n"
           "    if (((g_%08x - g_%08x) & ~1) > %d && g_%08x && g_%08x != g_%08x) EASTL_allocator_deallocate(g_%08x);\n"
           "}" % (cap, begin, pool, va, cap, begin, N[0], begin, begin, pool, begin))
    return src, "?FUN_%08x@@YAXXZ" % va
