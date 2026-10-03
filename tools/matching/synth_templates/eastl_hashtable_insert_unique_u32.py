# eastl::hashtable<uint32_t key, ...>::DoInsertValue(const value_type& value, true_type)  (unique-key insert,
# i.e. hash_map/hash_set::insert returning pair<iterator,bool>), EASTL source shape with exceptions disabled:
#   n = key % mnBucketCount; pNode = DoFindNode(mpBucketArray[n], k) (inline walk);
#   if (!pNode) { bRehash = mRehashPolicy.GetRehashRequired(mnBucketCount, mnElementCount, 1);
#                 pNodeNew = DoAllocateNode(value); if (bRehash.first) { n = k % bRehash.second; DoRehash(bRehash.second); }
#                 link at bucket head; ++mnElementCount; return pair(iterator(pNodeNew, mpBucketArray + n), true); }
#   return pair(iterator(pNode, mpBucketArray + n), false);
# Layout: +4 mpBucketArray, +8 mnBucketCount, +0xc mnElementCount, +0x10 prime_rehash_policy.
# Node: key at +0, mpNext at +sizeof(value_type) (the varying immediate N[5]).
# The iterator must be EASTL's hashtable_iterator : hashtable_iterator_base with its user copy-ctor
# (base_type(x.mpNode, x.mpBucket)); the implicit copy reorders the result stores (38-byte diff).
# Callees (GetRehashRequired, DoAllocateNode, DoRehash) are relocations, one class per instance.
PATTERN = 'mov eax, dword ptr [esp + N] ; sub esp, N ; push ebx ; mov ebx, dword ptr [eax] ; push ebp ; push esi ; mov esi, ecx ; xor edx, edx ; push edi ; mov edi, dword ptr [esi + N] ; mov eax, ebx ; div edi ; mov ecx, dword ptr [esi + N] ; mov ebp, edx ; lea edx, [ecx + ebp*N] ; mov ecx, dword ptr [edx] ; test ecx, ecx ; je +N ; cmp ebx, dword ptr [ecx] ; je +N ; mov ecx, dword ptr [ecx + N] ; test ecx, ecx ; jne +N ; mov edx, dword ptr [esi + N] ; push N ; push edx ; push edi ; lea eax, [esp + N] ; push eax ; lea ecx, [esi + N] ; call EXT ; mov ecx, dword ptr [esp + N] ; push ecx ; mov ecx, esi ; call EXT ; cmp byte ptr [esp + N], N ; mov edi, eax ; je +N ; mov ecx, dword ptr [esp + N] ; xor edx, edx ; mov eax, ebx ; div ecx ; push ecx ; mov ecx, esi ; mov ebp, edx ; call EXT ; mov edx, dword ptr [esi + N] ; lea ecx, [ebp*N] ; mov eax, dword ptr [ecx + edx] ; mov dword ptr [edi + N], eax ; mov edx, dword ptr [esi + N] ; mov eax, dword ptr [esp + N] ; mov dword ptr [ecx + edx], edi ; inc dword ptr [esi + N] ; mov edx, dword ptr [esi + N] ; mov dword ptr [eax], edi ; pop edi ; pop esi ; add edx, ecx ; pop ebp ; mov byte ptr [eax + N], N ; mov dword ptr [eax + N], edx ; pop ebx ; add esp, N ; ret N ; mov eax, dword ptr [esp + N] ; pop edi ; pop esi ; pop ebp ; mov dword ptr [eax], ecx ; mov byte ptr [eax + N], N ; mov dword ptr [eax + N], edx ; pop ebx ; add esp, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = r'''
namespace eastl {
struct true_type {};
template <typename T1, typename T2> struct pair { T1 first; T2 second;
    pair() {} pair(const T1& a, const T2& b) : first(a), second(b) {} };
struct prime_rehash_policy {
    float mfMaxLoadFactor; float mfGrowthFactor; unsigned mnNextResize;
    pair<bool, unsigned> GetRehashRequired(unsigned nBucketCount, unsigned nElementCount, unsigned nElementAdd) const;
};
}
#define HASHTABLE_INSERT_UNIQUE(T, VSIZE) \
struct T { \
    struct value_type { unsigned first; unsigned pad[(VSIZE) / 4 - 1]; }; \
    struct node_type { value_type mValue; node_type* mpNext; }; \
    struct iterator_base { node_type* mpNode; node_type** mpBucket; \
        iterator_base(node_type* p, node_type** b) : mpNode(p), mpBucket(b) {} }; \
    struct iterator : iterator_base { \
        iterator(node_type* p = 0, node_type** b = 0) : iterator_base(p, b) {} \
        iterator(const iterator& x) : iterator_base(x.mpNode, x.mpBucket) {} }; \
    int mFunctors; node_type** mpBucketArray; unsigned mnBucketCount; unsigned mnElementCount; \
    eastl::prime_rehash_policy mRehashPolicy; \
    node_type* DoAllocateNode(const value_type& value); \
    void DoRehash(unsigned nBucketCount); \
    node_type* DoFindNode(node_type* pNode, const unsigned& k) const { \
        for(; pNode; pNode = pNode->mpNext) if(k == pNode->mValue.first) return pNode; \
        return 0; } \
    eastl::pair<iterator, bool> DoInsertValue(const value_type& value, eastl::true_type); \
}; \
eastl::pair<T::iterator, bool> T::DoInsertValue(const value_type& value, eastl::true_type) \
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
    t = "Hashtable_%08x" % va
    return ("HASHTABLE_INSERT_UNIQUE(%s, %d)" % (t, N[5]),
            "?DoInsertValue@%s@@QAE?AU?$pair@Uiterator@%s@@_N@eastl@@ABUvalue_type@1@Utrue_type@3@@Z" % (t, t))
