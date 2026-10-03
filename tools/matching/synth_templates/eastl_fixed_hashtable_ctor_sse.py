# EASTL hashtable constructor instantiated for a fixed_hash_map/fixed_hash_set
# (fixed_hashtable_allocator), compiled /O2 /arch:SSE:
#   hashtable(size_type nBucketCount, const H1&, const H2&, const H&, const Eq&, const EK&,
#             const allocator_type& a)
#     : mnBucketCount(0), mnElementCount(0), mRehashPolicy(), mAllocator(a)
#   { if (nBucketCount < 2) reset(); else { mnBucketCount = mRehashPolicy.GetNextBucketCount(n);
#                                           mpBucketArray = DoAllocateBuckets(mnBucketCount); } }
# Layout: +0 empty functors, +4 mpBucketArray, +8 mnBucketCount, +0xc mnElementCount,
# +0x10 prime_rehash_policy {1.0f, 2.0f, mnNextResize}, +0x1c allocator (fixed_pool of five words
# + mpBucketBuffer). The allocator copy-ctor re-inits the pool over x's buffer with the
# per-instantiation (memorySize, nodeSize, alignment) constants; those are the varying immediates.
# Callees (fixed_pool::init, GetNextBucketCount, DoAllocateBuckets) are relocations (masked).
PATTERN = 'movss xmm0, dword ptr [A] ; push ebx ; push ebp ; push esi ; push edi ; mov esi, ecx ; mov ecx, dword ptr [esp + N] ; xor eax, eax ; push eax ; mov dword ptr [esi + N], eax ; mov dword ptr [esi + N], eax ; lea ebx, [esi + N] ; push N ; movss dword ptr [ebx], xmm0 ; movss xmm0, dword ptr [A] ; push N ; movss dword ptr [ebx + N], xmm0 ; mov dword ptr [ebx + N], eax ; mov ebp, dword ptr [ecx] ; lea edi, [esi + N] ; push N ; push ebp ; mov ecx, edi ; mov dword ptr [edi], eax ; call EXT ; mov edx, dword ptr [esp + N] ; mov dword ptr [edi + N], ebp ; add ebp, N ; mov dword ptr [edi + N], ebp ; mov dword ptr [edi + N], N ; mov eax, dword ptr [edx + N] ; mov dword ptr [edi + N], eax ; mov eax, dword ptr [esp + N] ; cmp eax, N ; jae +N ; xor eax, eax ; pop edi ; mov dword ptr [esi + N], eax ; mov dword ptr [esi + N], eax ; mov dword ptr [esi + N], N ; mov dword ptr [esi + N], A ; mov eax, esi ; pop esi ; pop ebp ; pop ebx ; ret N ; push eax ; mov ecx, ebx ; call EXT ; push eax ; mov ecx, esi ; mov dword ptr [esi + N], eax ; call EXT ; pop edi ; mov dword ptr [esi + N], eax ; mov eax, esi ; pop esi ; pop ebp ; pop ebx ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/arch:SSE", "/GR-"]
PRELUDE = r'''typedef unsigned int size_t;
struct prime_rehash_policy {
    float mfMaxLoadFactor; float mfGrowthFactor; size_t mnNextResize;
    prime_rehash_policy(float f = 1.0f) : mfMaxLoadFactor(f), mfGrowthFactor(2.0f), mnNextResize(0) {}
    size_t GetNextBucketCount(size_t n) const;
};
struct fixed_pool {
    void* mpHead; void* mpReserved; void* mpNext; void* mpCapacity; size_t mnNodeSize;
    void init(void* pMemory, size_t memorySize, size_t nodeSize, size_t alignment, size_t alignmentOffset);
};
extern void* gpEmptyBucketArray[2];
struct hash_functor {};
template <size_t kSize, size_t kNode, size_t kAlign>
struct fixed_hashtable_allocator {
    fixed_pool mPool; void* mpBucketBuffer;
    fixed_hashtable_allocator(const fixed_hashtable_allocator& x) {
        char* p = (char*)x.mPool.mpHead;
        mPool.mpHead = 0;
        mPool.init(p, kSize, kNode, kAlign, 0);
        mPool.mpNext = p; mPool.mpCapacity = p + kSize; mPool.mnNodeSize = kNode;
        mpBucketBuffer = x.mpBucketBuffer;
    }
};
'''

def emit(va, A, N):
    # N: [0x2c, 8, 0xc, 0x10, align, node, 4, 8, 0x1c, size, ...]
    align, node, size = N[4], N[5], N[9]
    h = "hashtable_%08x" % va
    al = "fixed_hashtable_allocator<%#x,%#x,%d>" % (size, node, align)
    F = "const hash_functor&"
    src = ("struct %(h)s {\n"
           "    hash_functor mFunctors; void** mpBucketArray; size_t mnBucketCount; size_t mnElementCount;\n"
           "    prime_rehash_policy mRehashPolicy; %(al)s mAllocator;\n"
           "    void** DoAllocateBuckets(size_t n);\n"
           "    void reset() { mnBucketCount = 1; mpBucketArray = (void**)&gpEmptyBucketArray[0]; mnElementCount = 0; mRehashPolicy.mnNextResize = 0; }\n"
           "    %(h)s(size_t nBucketCount, %(F)s, %(F)s, %(F)s, %(F)s, %(F)s, const %(al)s& a);\n"
           "};\n"
           "%(h)s::%(h)s(size_t nBucketCount, %(F)s, %(F)s, %(F)s, %(F)s, %(F)s, const %(al)s& a)\n"
           "  : mnBucketCount(0), mnElementCount(0), mRehashPolicy(), mAllocator(a)\n"
           "{\n"
           "    if (nBucketCount < 2) reset();\n"
           "    else { mnBucketCount = mRehashPolicy.GetNextBucketCount(nBucketCount); mpBucketArray = DoAllocateBuckets(mnBucketCount); }\n"
           "}") % dict(h=h, al=al, F=F)
    sym = "??0%s@@QAE@IABUhash_functor@@0000ABU?$fixed_hashtable_allocator@$0%s$0%s$0%s@@@Z" % (
        h, mangle_int(size), mangle_int(node), mangle_int(align))
    return src, sym

def mangle_int(v):
    if 1 <= v <= 10:
        return str(v - 1)
    s = ""
    while v:
        s = "ABCDEFGHIJKLMNOP"[v & 15] + s
        v >>= 4
    return s + "@"
