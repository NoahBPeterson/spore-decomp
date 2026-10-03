# eastl::hashtable<uint32_t key, ...>::DoInsertValue(const value_type& value, true_type)  (unique-key insert,
# i.e. hash_map/hash_set::insert returning pair<iterator,bool>), EASTL source shape with exceptions disabled:
#   n = key % mnBucketCount; pNode = DoFindNode(mpBucketArray[n], k) (inline walk);
#   if (!pNode) { bRehash = mRehashPolicy.GetRehashRequired(mnBucketCount, mnElementCount, 1);
#                 pNodeNew = DoAllocateNode(value); if (bRehash.first) { n = k % bRehash.second; DoRehash(bRehash.second); }
#                 link at bucket head; ++mnElementCount; return pair(iterator(pNodeNew, mpBucketArray + n), true); }
#   return pair(iterator(pNode, mpBucketArray + n), false);
# Layout: +4 mpBucketArray, +8 mnBucketCount, +0xc mnElementCount, +0x10 prime_rehash_policy.
# Node: key at +0, mpNext at +sizeof(value_type) (the varying immediate N[18]).
# The iterator must be EASTL's hashtable_iterator : hashtable_iterator_base with its user copy-ctor
# (base_type(x.mpNode, x.mpBucket)); the implicit copy reorders the result stores (38-byte diff).
# Callees (GetRehashRequired, DoAllocateNode, DoRehash) are relocations, one class per instance.
PATTERN = 'push ebp ; mov ebp, esp ; sub esp, N ; mov dword ptr [ebp - N], ecx ; mov eax, dword ptr [ebp + N] ; mov dword ptr [ebp - N], eax ; mov ecx, dword ptr [ebp - N] ; mov edx, dword ptr [ecx] ; mov dword ptr [ebp - N], edx ; mov eax, dword ptr [ebp - N] ; mov dword ptr [ebp - N], eax ; mov ecx, dword ptr [ebp - N] ; mov eax, dword ptr [ebp - N] ; xor edx, edx ; div dword ptr [ecx + N] ; mov dword ptr [ebp - N], edx ; mov edx, dword ptr [ebp - N] ; mov eax, dword ptr [edx + N] ; mov ecx, dword ptr [ebp - N] ; mov edx, dword ptr [eax + ecx*N] ; mov dword ptr [ebp - N], edx ; jmp +N ; mov eax, dword ptr [ebp - N] ; mov ecx, dword ptr [eax + N] ; mov dword ptr [ebp - N], ecx ; cmp dword ptr [ebp - N], N ; je +N ; mov edx, dword ptr [ebp - N] ; mov eax, dword ptr [ebp - N] ; mov ecx, dword ptr [edx] ; xor edx, edx ; cmp ecx, dword ptr [eax] ; sete dl ; movzx eax, dl ; test eax, eax ; je +N ; mov ecx, dword ptr [ebp - N] ; mov dword ptr [ebp - N], ecx ; jmp +N ; jmp +N ; mov dword ptr [ebp - N], N ; cmp dword ptr [ebp - N], N ; jne +N ; push N ; mov edx, dword ptr [ebp - N] ; mov eax, dword ptr [edx + N] ; push eax ; mov ecx, dword ptr [ebp - N] ; mov edx, dword ptr [ecx + N] ; push edx ; lea eax, [ebp - N] ; push eax ; mov ecx, dword ptr [ebp - N] ; add ecx, N ; call EXT ; mov ecx, dword ptr [ebp + N] ; push ecx ; mov ecx, dword ptr [ebp - N] ; call EXT ; mov dword ptr [ebp - N], eax ; movzx edx, byte ptr [ebp - N] ; test edx, edx ; je +N ; mov eax, dword ptr [ebp - N] ; xor edx, edx ; div dword ptr [ebp - N] ; mov dword ptr [ebp - N], edx ; mov eax, dword ptr [ebp - N] ; push eax ; mov ecx, dword ptr [ebp - N] ; call EXT ; mov ecx, dword ptr [ebp - N] ; mov edx, dword ptr [ecx + N] ; mov eax, dword ptr [ebp - N] ; mov ecx, dword ptr [ebp - N] ; mov edx, dword ptr [edx + ecx*N] ; mov dword ptr [eax + N], edx ; mov eax, dword ptr [ebp - N] ; mov ecx, dword ptr [eax + N] ; mov edx, dword ptr [ebp - N] ; mov eax, dword ptr [ebp - N] ; mov dword ptr [ecx + edx*N], eax ; mov ecx, dword ptr [ebp - N] ; mov edx, dword ptr [ecx + N] ; add edx, N ; mov eax, dword ptr [ebp - N] ; mov dword ptr [eax + N], edx ; mov byte ptr [ebp - N], N ; mov ecx, dword ptr [ebp - N] ; mov edx, dword ptr [ecx + N] ; mov eax, dword ptr [ebp - N] ; lea ecx, [edx + eax*N] ; mov dword ptr [ebp - N], ecx ; mov edx, dword ptr [ebp - N] ; mov dword ptr [ebp - N], edx ; mov eax, dword ptr [ebp - N] ; mov dword ptr [ebp - N], eax ; mov ecx, dword ptr [ebp - N] ; mov dword ptr [ebp - N], ecx ; mov edx, dword ptr [ebp - N] ; mov dword ptr [ebp - N], edx ; mov eax, dword ptr [ebp + N] ; mov ecx, dword ptr [ebp - N] ; mov dword ptr [eax], ecx ; mov edx, dword ptr [ebp + N] ; mov eax, dword ptr [ebp - N] ; mov dword ptr [edx + N], eax ; mov ecx, dword ptr [ebp + N] ; mov dl, byte ptr [ebp - N] ; mov byte ptr [ecx + N], dl ; mov eax, dword ptr [ebp + N] ; jmp +N ; mov byte ptr [ebp - N], N ; mov eax, dword ptr [ebp - N] ; mov ecx, dword ptr [eax + N] ; mov edx, dword ptr [ebp - N] ; lea eax, [ecx + edx*N] ; mov dword ptr [ebp - N], eax ; mov ecx, dword ptr [ebp - N] ; mov dword ptr [ebp - N], ecx ; mov edx, dword ptr [ebp - N] ; mov dword ptr [ebp - N], edx ; mov eax, dword ptr [ebp - N] ; mov dword ptr [ebp - N], eax ; mov ecx, dword ptr [ebp - N] ; mov dword ptr [ebp - N], ecx ; mov edx, dword ptr [ebp + N] ; mov eax, dword ptr [ebp - N] ; mov dword ptr [edx], eax ; mov ecx, dword ptr [ebp + N] ; mov edx, dword ptr [ebp - N] ; mov dword ptr [ecx + N], edx ; mov eax, dword ptr [ebp + N] ; mov cl, byte ptr [ebp - N] ; mov byte ptr [eax + N], cl ; mov eax, dword ptr [ebp + N] ; mov esp, ebp ; pop ebp ; ret N'
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
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
    struct hashf { static unsigned h0(const unsigned& x) { return x; } static unsigned h(const unsigned& x) { return h0(x); } }; \
    struct eqf { static bool e(const unsigned& a, const unsigned& b) { return a == b; } }; \
    int mFunctors; node_type** mpBucketArray; unsigned mnBucketCount; unsigned mnElementCount; \
    eastl::prime_rehash_policy mRehashPolicy; \
    node_type* DoAllocateNode(const value_type& value); \
    void DoRehash(unsigned nBucketCount); \
    node_type* DoFindNode(node_type* pNode, const unsigned& k) const { \
        for(; pNode; pNode = pNode->mpNext) if(eqf::e(k, pNode->mValue.first)) return pNode; \
        return 0; } \
    eastl::pair<iterator, bool> DoInsertValue(const value_type& value, eastl::true_type); \
}; \
eastl::pair<T::iterator, bool> T::DoInsertValue(const value_type& value, eastl::true_type) \
{ \
    const unsigned& k = value.first; \
    const unsigned c = hashf::h(k); \
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
    return ("HASHTABLE_INSERT_UNIQUE(%s, %d)" % (t, N[18]),
            "?DoInsertValue@%s@@QAE?AU?$pair@Uiterator@%s@@_N@eastl@@ABUvalue_type@1@Utrue_type@3@@Z" % (t, t))
