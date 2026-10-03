# Key is a 64-bit integer: hash = low dword, equality = 64-bit compare (low then high).
# eastl::hashtable DoInsertValue (unique insert, pair<iterator,bool>) for a 2-dword key: hash = key.first,
# equality compares both words (e.g. ResourceKey-like instance/group). Same shape as
# eastl_hashtable_insert_unique_u32 otherwise. Node: key at +0, mpNext at +sizeof(value_type) (N[9]).
PATTERN = 'sub esp, N ; push ebx ; mov ebx, dword ptr [esp + N] ; mov eax, dword ptr [ebx] ; push ebp ; push esi ; mov esi, ecx ; xor edx, edx ; push edi ; mov edi, dword ptr [esi + N] ; mov dword ptr [esp + N], eax ; div edi ; mov eax, dword ptr [esi + N] ; mov ebp, edx ; mov ecx, dword ptr [eax + ebp*N] ; lea edx, [eax + ebp*N] ; test ecx, ecx ; je +N ; lea esp, [esp] ; mov eax, dword ptr [ebx] ; cmp eax, dword ptr [ecx] ; jne +N ; mov eax, dword ptr [ebx + N] ; cmp eax, dword ptr [ecx + N] ; je +N ; mov ecx, dword ptr [ecx + N] ; test ecx, ecx ; jne +N ; mov ecx, dword ptr [esi + N] ; push N ; push ecx ; push edi ; lea edx, [esp + N] ; push edx ; lea ecx, [esi + N] ; call EXT ; push ebx ; mov ecx, esi ; call EXT ; cmp byte ptr [esp + N], N ; mov edi, eax ; je +N ; mov ecx, dword ptr [esp + N] ; mov eax, dword ptr [esp + N] ; xor edx, edx ; div ecx ; push ecx ; mov ecx, esi ; mov ebp, edx ; call EXT ; mov eax, dword ptr [esi + N] ; lea ecx, [ebp*N] ; mov edx, dword ptr [ecx + eax] ; mov dword ptr [edi + N], edx ; mov eax, dword ptr [esi + N] ; mov dword ptr [ecx + eax], edi ; mov eax, dword ptr [esp + N] ; inc dword ptr [esi + N] ; mov edx, dword ptr [esi + N] ; mov dword ptr [eax], edi ; pop edi ; pop esi ; add edx, ecx ; pop ebp ; mov byte ptr [eax + N], N ; mov dword ptr [eax + N], edx ; pop ebx ; add esp, N ; ret N ; mov eax, dword ptr [esp + N] ; pop edi ; pop esi ; pop ebp ; mov dword ptr [eax], ecx ; mov byte ptr [eax + N], N ; mov dword ptr [eax + N], edx ; pop ebx ; add esp, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = r'''
typedef unsigned __int64 Key;
namespace eastl {
struct true_type {};
template <typename T1, typename T2> struct pair { T1 first; T2 second;
    pair() {} pair(const T1& a, const T2& b) : first(a), second(b) {} };
struct prime_rehash_policy {
    float mfMaxLoadFactor; float mfGrowthFactor; unsigned mnNextResize;
    pair<bool, unsigned> GetRehashRequired(unsigned nBucketCount, unsigned nElementCount, unsigned nElementAdd) const;
};
}
#define HASHTABLE_INSERT_UNIQUE2(T, VSIZE) \
struct T { \
    struct value_type { Key first; unsigned pad[(VSIZE) / 4 - 2]; }; \
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
    node_type* DoFindNode(node_type* pNode, const value_type& k) const { \
        for(; pNode; pNode = pNode->mpNext) \
            if(k.first == pNode->mValue.first) return pNode; \
        return 0; } \
    eastl::pair<iterator, bool> DoInsertValue(const value_type& value, eastl::true_type); \
}; \
eastl::pair<T::iterator, bool> T::DoInsertValue(const value_type& value, eastl::true_type) \
{ \
    const unsigned c = (unsigned)value.first; \
    unsigned n = c % mnBucketCount; \
    node_type* const pNode = DoFindNode(mpBucketArray[n], value); \
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
    t = "HashtableK2_%08x" % va
    vs = N[9]
    return ("HASHTABLE_INSERT_UNIQUE2(%s, %d)" % (t, vs),
            "?DoInsertValue@%s@@QAE?AU?$pair@Uiterator@%s@@_N@eastl@@ABUvalue_type@1@Utrue_type@3@@Z" % (t, t))
