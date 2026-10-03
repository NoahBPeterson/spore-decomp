# eastl::hashtable<uint32_t key,...>::find(const key_type&) returning iterator (node, bucket) by hidden pointer;
# bucket walk inline, end() = (*(buckets+count), buckets+count). Node mpNext at +VSIZE (varying immediate).
PATTERN = 'mov eax, dword ptr [esp + N] ; sub esp, N ; push esi ; mov esi, dword ptr [eax] ; xor edx, edx ; push edi ; mov edi, dword ptr [ecx + N] ; mov eax, esi ; div edi ; mov ecx, dword ptr [ecx + N] ; mov eax, dword ptr [ecx + edx*N] ; lea edx, [ecx + edx*N] ; test eax, eax ; je +N ; cmp esi, dword ptr [eax] ; je +N ; mov eax, dword ptr [eax + N] ; test eax, eax ; jne +N ; lea eax, [ecx + edi*N] ; mov ecx, dword ptr [eax] ; mov dword ptr [esp + N], ecx ; mov dword ptr [esp + N], eax ; mov eax, dword ptr [esp + N] ; lea ecx, [esp + N] ; mov edx, dword ptr [ecx] ; mov ecx, dword ptr [ecx + N] ; pop edi ; mov dword ptr [eax], edx ; mov dword ptr [eax + N], ecx ; pop esi ; add esp, N ; ret N ; mov dword ptr [esp + N], eax ; mov dword ptr [esp + N], edx ; jmp +N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = r'''
template<int N> struct HTV { unsigned first; unsigned pad[N]; };
template<> struct HTV<0> { unsigned first; };
#define HT_FIND(T, VSIZE) \
struct T { \
    typedef HTV<(VSIZE) / 4 - 1> value_type; \
    struct node_type { value_type mValue; node_type* mpNext; }; \
    struct iterator_base { node_type* mpNode; node_type** mpBucket; \
        iterator_base(node_type* p, node_type** b) : mpNode(p), mpBucket(b) {} }; \
    struct iterator : iterator_base { \
        iterator(node_type* p = 0, node_type** b = 0) : iterator_base(p, b) {} \
        iterator(const iterator& x) : iterator_base(x.mpNode, x.mpBucket) {} }; \
    int mFunctors; node_type** mpBucketArray; unsigned mnBucketCount; unsigned mnElementCount; \
    iterator end() { return iterator(mpBucketArray[mnBucketCount], mpBucketArray + mnBucketCount); } \
    node_type* DoFindNode(node_type* pNode, const unsigned& k) const { \
        for(; pNode; pNode = pNode->mpNext) if(k == pNode->mValue.first) return pNode; \
        return 0; } \
    iterator find(const unsigned& k); \
}; \
T::iterator T::find(const unsigned& k) \
{ \
    const unsigned c = mnBucketCount; node_type** const pb = mpBucketArray; \
    const unsigned n = k % c; \
    node_type* const pNode = DoFindNode(pb[n], k); \
    return pNode ? iterator(pNode, pb + n) : iterator(pb[c], pb + c); \
}
'''
def emit(va, A, N):
    t = "Hashtable_%08x" % va
    return ("HT_FIND(%s, %d)" % (t, N[6]),
            "?find@%s@@QAE?AUiterator@1@ABI@Z" % t)
