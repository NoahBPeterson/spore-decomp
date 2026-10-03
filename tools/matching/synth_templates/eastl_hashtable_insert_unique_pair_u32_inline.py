# eastl::hashtable DoInsertValue (unique), 8-byte value {u32 key, u32 second} copy-constructed inline in DoAllocateNode (node 12 bytes).
PATTERN = 'mov eax, dword ptr [esp + N] ; sub esp, N ; push ebx ; mov ebx, dword ptr [eax] ; push ebp ; push esi ; mov esi, ecx ; xor edx, edx ; push edi ; mov edi, dword ptr [esi + N] ; mov eax, ebx ; div edi ; mov ecx, dword ptr [esi + N] ; mov ebp, edx ; lea edx, [ecx + ebp*N] ; mov ecx, dword ptr [edx] ; test ecx, ecx ; je +N ; cmp ebx, dword ptr [ecx] ; je +N ; mov ecx, dword ptr [ecx + N] ; test ecx, ecx ; jne +N ; mov edx, dword ptr [esi + N] ; push N ; push edx ; push edi ; lea eax, [esp + N] ; push eax ; lea ecx, [esi + N] ; call EXT ; push N ; push A ; push N ; push N ; push A ; push N ; call EXT ; mov edi, eax ; add esp, N ; test edi, edi ; je +N ; mov eax, dword ptr [esp + N] ; mov ecx, dword ptr [eax] ; mov dword ptr [edi], ecx ; mov edx, dword ptr [eax + N] ; mov dword ptr [edi + N], edx ; mov dword ptr [edi + N], N ; cmp byte ptr [esp + N], N ; je +N ; mov ecx, dword ptr [esp + N] ; xor edx, edx ; mov eax, ebx ; div ecx ; push ecx ; mov ecx, esi ; mov ebp, edx ; call EXT ; mov eax, dword ptr [esi + N] ; lea ecx, [ebp*N] ; mov edx, dword ptr [ecx + eax] ; mov dword ptr [edi + N], edx ; mov eax, dword ptr [esi + N] ; mov dword ptr [ecx + eax], edi ; mov eax, dword ptr [esp + N] ; inc dword ptr [esi + N] ; mov edx, dword ptr [esi + N] ; mov dword ptr [eax], edi ; pop edi ; pop esi ; add edx, ecx ; pop ebp ; mov byte ptr [eax + N], N ; mov dword ptr [eax + N], edx ; pop ebx ; add esp, N ; ret N ; mov eax, dword ptr [esp + N] ; pop edi ; pop esi ; pop ebp ; mov dword ptr [eax], ecx ; mov byte ptr [eax + N], N ; mov dword ptr [eax + N], edx ; pop ebx ; add esp, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/TP", "/GR-"]
PRELUDE = r'''
typedef unsigned int size_t;
inline void* operator new(size_t, void* p) { return p; }
namespace eastl {
template <typename T1, typename T2> struct pair { T1 first; T2 second;
    pair() {} pair(const T1& a, const T2& b) : first(a), second(b) {} };
struct prime_rehash_policy {
    float mfMaxLoadFactor; float mfGrowthFactor; unsigned mnNextResize;
    pair<bool, unsigned> GetRehashRequired(unsigned nBucketCount, unsigned nElementCount, unsigned nElementAdd) const;
};
}
struct true_type_t {};
void* eastl_alloc(size_t, const char*, int, unsigned, const char*, int);
#define HASHTABLE_INSERT_UNIQUE_ALLOC(T, VSIZE, VOFF, NSIZE, FILE, NAME, LINE) \
struct T { \
     \
    struct value_type { unsigned first; unsigned second; value_type(const value_type& v) : first(v.first), second(v.second) {} }; \
    struct node_type { value_type mValue; node_type* mpNext; }; \
    struct iterator_base { node_type* mpNode; node_type** mpBucket; \
        iterator_base(node_type* p, node_type** b) : mpNode(p), mpBucket(b) {} }; \
    struct iterator : iterator_base { \
        iterator(node_type* p = 0, node_type** b = 0) : iterator_base(p, b) {} \
        iterator(const iterator& x) : iterator_base(x.mpNode, x.mpBucket) {} }; \
    int mFunctors; node_type** mpBucketArray; unsigned mnBucketCount; unsigned mnElementCount; \
    eastl::prime_rehash_policy mRehashPolicy; \
    void DoRehash(unsigned nBucketCount); \
    __forceinline node_type* DoAllocateNode(const value_type& value) { \
        node_type* const pNode = (node_type*)eastl_alloc(NSIZE, NAME, 0, 0u, FILE, LINE); \
        ::new(&pNode->mValue) value_type(value); \
        pNode->mpNext = 0; \
        return pNode; } \
    node_type* DoFindNode(node_type* pNode, const unsigned& k) const { \
        for(; pNode; pNode = pNode->mpNext) if(k == pNode->mValue.first) return pNode; \
        return 0; } \
    eastl::pair<iterator, bool> DoInsertValue(const value_type& value, true_type_t); \
}; \
eastl::pair<T::iterator, bool> T::DoInsertValue(const value_type& value, true_type_t) \
{ \
    const unsigned& k = value.first; \
    const unsigned c = k; \
    unsigned n = c % mnBucketCount; \
    node_type* const pNode = DoFindNode(mpBucketArray[n], k); \
    if(pNode == 0) { \
        const eastl::pair<bool, unsigned> bRehash = mRehashPolicy.GetRehashRequired(mnBucketCount, mnElementCount, 1); \
        node_type* const pNodeNew = DoAllocateNode(value); \
        if(bRehash.first) { \
            n = c % bRehash.second; \
            DoRehash(bRehash.second); \
        } \
        pNodeNew->mpNext = mpBucketArray[n]; \
        mpBucketArray[n] = pNodeNew; \
        ++mnElementCount; \
        return eastl::pair<iterator, bool>(iterator(pNodeNew, mpBucketArray + n), true); \
    } \
    return eastl::pair<iterator, bool>(iterator(pNode, mpBucketArray + n), false); \
}
'''

def emit(va, A, N):
    t = "Hashtable8_%08x" % va
    return ("extern const char f_%08x[]; extern const char s_%08x[];\n"
            "HASHTABLE_INSERT_UNIQUE_ALLOC(%s, 8, 0, 12, f_%08x, s_%08x, %d)" % (va, va, t, va, va, 0xd1),
            "?DoInsertValue@%s@@QAE?AU?$pair@Uiterator@%s@@_N@eastl@@ABUvalue_type@1@Utrue_type_t@@@Z" % (t, t))
