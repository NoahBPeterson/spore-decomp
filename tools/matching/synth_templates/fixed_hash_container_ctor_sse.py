# EASTL fixed_hash_map/set constructor (/O2 /arch:SSE): builds a fixed_hashtable_allocator temporary over the
# in-object node buffer, calls base hashtable ctor(GetPrevBucketCountOnly(n), ...), then
# rehash_policy(prime_rehash_policy(f1, f2)) (assign + GetBucketCount + conditional rehash).
# Layout: hashtable base 0x34 bytes, bucket buffer (n+1 words), node buffer at +N[5].
# KNOWN GAP: original passes &param3 three times without CSE (separate lea per arg); we CSE them into
# one lea + mov. Not yet byte-exact; unexplored source shape for the three functor refs.
PATTERN = 'sub esp, N ; push esi ; push edi ; push N ; push N ; mov esi, ecx ; push N ; push N ; lea edi, [esi + N] ; push edi ; lea ecx, [esp + N] ; mov dword ptr [esp + N], N ; call EXT ; mov dword ptr [esp + N], edi ; lea eax, [esi + N] ; add edi, N ; push N ; mov dword ptr [esp + N], edi ; mov dword ptr [esp + N], N ; mov dword ptr [esp + N], eax ; call EXT ; add esp, N ; lea ecx, [esp + N] ; push ecx ; mov ecx, dword ptr [esp + N] ; lea edx, [esp + N] ; push edx ; push ecx ; lea edx, [esp + N] ; push edx ; mov edx, dword ptr [esp + N] ; lea ecx, [esp + N] ; push ecx ; push edx ; push eax ; mov ecx, esi ; call EXT ; movss xmm0, dword ptr [A] ; movss dword ptr [esp + N], xmm0 ; movss xmm0, dword ptr [A] ; mov ecx, dword ptr [esp + N] ; movss dword ptr [esp + N], xmm0 ; mov edx, dword ptr [esp + N] ; xor eax, eax ; mov dword ptr [esi + N], ecx ; mov dword ptr [esi + N], edx ; mov dword ptr [esp + N], eax ; mov dword ptr [esi + N], eax ; mov eax, dword ptr [esi + N] ; push eax ; lea ecx, [esp + N] ; call EXT ; cmp eax, dword ptr [esi + N] ; jbe +N ; push eax ; mov ecx, esi ; call EXT ; pop edi ; mov eax, esi ; pop esi ; add esp, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/arch:SSE", "/GR-"]
PRELUDE = r'''typedef unsigned int size_t;
struct E1 {}; struct E2 {}; struct E3 {}; struct E {};
struct prime_rehash_policy {
    float mfMaxLoadFactor; float mfGrowthFactor; size_t mnNextResize;
    prime_rehash_policy(float f, float g) : mfMaxLoadFactor(f), mfGrowthFactor(g), mnNextResize(0) {}
    size_t GetBucketCount(size_t n) const;
};
size_t __cdecl GetPrev(size_t n);
inline size_t gp(size_t n) { return GetPrev(n); }
struct fixed_pool {
    void* mpHead; void* mpReserved; void* mpNext; void* mpCapacity; size_t mnNodeSize;
    void init(void* pMemory, size_t memorySize, size_t nodeSize, size_t alignment, size_t alignmentOffset);
};
struct alloc_t {
    fixed_pool mPool; void* mpBucketBuffer;
    alloc_t(char* p, void* bb, size_t sz, size_t node, size_t al) {
        mPool.mpHead = 0; mPool.init(p, sz, node, al, 0);
        mPool.mpNext = p; mPool.mpCapacity = p + sz; mPool.mnNodeSize = node; mpBucketBuffer = bb;
    }
};
struct HT {
    void* pad0; void* mpBuckets; size_t mnBucketCount; size_t mnElementCount; prime_rehash_policy mRehashPolicy; unsigned pad[6];
    HT(size_t n, E, const E1&, const E2&, E, const E3&, const alloc_t&);
    void rehash(size_t);
    void rehash_policy(const prime_rehash_policy& p) {
        mRehashPolicy = p; size_t n = p.GetBucketCount(mnElementCount); if (n > mnBucketCount) rehash(n);
    }
};
'''
def emit(va, A, N):
    align, node, size, off, nb = N[2], N[3], N[4], N[5], N[12]
    nwords = (off - 0x34) // 4
    c = "FHM_%08x" % va
    src = ("extern float gF1_%(v)08x, gF2_%(v)08x;\n"
           "struct %(c)s : HT {\n"
           "    void* mBucketBuffer[%(nw)d];\n"
           "    char mNodeBuffer[%(sz)d];\n"
           "    %(c)s(E a, E b);\n"
           "};\n"
           "%(c)s::%(c)s(E a, E b) : HT(gp(%(nb)d), a, (const E1&)b, (const E2&)b, b, (const E3&)b,"
           " alloc_t(mNodeBuffer, mBucketBuffer, %(sz)d, %(node)d, %(al)d)) {\n"
           "    rehash_policy(prime_rehash_policy(gF1_%(v)08x, gF2_%(v)08x));\n"
           "}") % dict(c=c, v=va, nw=nwords, sz=size, nb=nb, node=node, al=align)
    return src, "??0%s@@QAE@UE@@0@Z" % c
