# Scalar deleting destructor (??_G) of a class with an inline empty virtual dtor (vptr store kept)
# and a class-specific operator delete returning the block to a global pool: g->Free(p, p->mSize16, TAG).
# Same as scalar_deldtor_pool_free_o1 but dtor is inlined (test first, vptr store, no call).
PATTERN = 'test byte ptr [esp + N], N ; push esi ; mov esi, ecx ; mov dword ptr [esi], A ; je +N ; movzx edx, word ptr [esi + N] ; mov ecx, dword ptr [A] ; mov eax, dword ptr [ecx] ; push N ; push edx ; push esi ; call dword ptr [eax + N] ; mov eax, esi ; pop esi ; ret N'
FLAGS = ["/O1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ("struct PoolAlloc {\n" +
           "".join("    virtual void v%d(void* p, unsigned int size, int tag);\n" % i for i in range(64)) +
           "};\n")

def emit(va, A, N):
    # A = [vftable, g_alloc]; N = [1(test), off, TAG, 4(ret)] (vftable is A[0])
    off, tag, slot = N[-3], N[-2], 5
    c = "C_%08x" % va
    pad = "    char pad[%d];\n" % (off - 4) if off > 4 else ""
    src = ("extern PoolAlloc* g_%08x;\n"
           "struct %s {\n    %s();\n    virtual ~%s() {}\n%s    unsigned short mSize;\n"
           "    static __forceinline void operator delete(void* p) {\n"
           "        g_%08x->v%d(p, ((%s*)p)->mSize, 0x%x);\n    }\n};\n"
           "%s::%s() {}") % (A[1], c, c, c, pad, A[1], slot, c, tag, c, c)
    return src, "??_G%s@@UAEPAXI@Z" % c
