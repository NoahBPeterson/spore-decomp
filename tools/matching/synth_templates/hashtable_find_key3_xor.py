# eastl::hashtable<ResourceKey-like 3-dword key, ...>::find(const key_type&) returning iterator by hidden pointer;
# hash = a ^ c, inline bucket walk, end() = (*(buckets+count), buckets+count). Node mpNext at +VSIZE (varying).
PATTERN = 'sub esp, N ; push ebx ; push ebp ; mov ebp, dword ptr [ecx + N] ; push esi ; mov esi, dword ptr [esp + N] ; mov ebx, dword ptr [esi] ; push edi ; mov edi, dword ptr [esi + N] ; mov eax, ebx ; xor eax, edi ; xor edx, edx ; div ebp ; mov ecx, dword ptr [ecx + N] ; mov eax, dword ptr [ecx + edx*N] ; lea edx, [ecx + edx*N] ; mov dword ptr [esp + N], edx ; test eax, eax ; je +N ; lea esp, [esp] ; cmp ebx, dword ptr [eax] ; jne +N ; mov edx, dword ptr [esi + N] ; cmp edx, dword ptr [eax + N] ; jne +N ; cmp edi, dword ptr [eax + N] ; je +N ; mov eax, dword ptr [eax + N] ; test eax, eax ; jne +N ; lea eax, [ecx + ebp*N] ; mov ecx, dword ptr [eax] ; mov dword ptr [esp + N], ecx ; pop edi ; lea ecx, [esp + N] ; mov dword ptr [esp + N], eax ; mov edx, dword ptr [ecx] ; mov eax, dword ptr [esp + N] ; mov ecx, dword ptr [ecx + N] ; pop esi ; pop ebp ; mov dword ptr [eax], edx ; mov dword ptr [eax + N], ecx ; pop ebx ; add esp, N ; ret N ; mov dword ptr [esp + N], eax ; mov eax, dword ptr [esp + N] ; jmp +N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = r'''
struct Key { unsigned a; unsigned b; unsigned c; };
inline bool operator==(const Key& x, const Key& y) { return x.a == y.a && x.b == y.b && x.c == y.c; }
template<int N> struct HTV3 { Key first; unsigned pad[N]; };
template<> struct HTV3<0> { Key first; };
#define HT_FIND3(T, VSIZE) \
struct T { \
    typedef HTV3<(VSIZE) / 4 - 3> value_type; \
    struct node_type { value_type mValue; node_type* mpNext; }; \
    struct iterator_base { node_type* mpNode; node_type** mpBucket; \
        iterator_base(node_type* p, node_type** b) : mpNode(p), mpBucket(b) {} }; \
    struct iterator : iterator_base { \
        iterator(node_type* p = 0, node_type** b = 0) : iterator_base(p, b) {} \
        iterator(const iterator& x) : iterator_base(x.mpNode, x.mpBucket) {} }; \
    int mFunctors; node_type** mpBucketArray; unsigned mnBucketCount; unsigned mnElementCount; \
    __forceinline node_type* DoFindNode(node_type* pNode, const Key& k) const { \
        for(; pNode; pNode = pNode->mpNext) if(k == pNode->mValue.first) return pNode; \
        return 0; } \
    iterator find(const Key& k); \
}; \
T::iterator T::find(const Key& k) \
{ \
    const unsigned cnt = mnBucketCount; \
    const unsigned n = (k.a ^ k.c) % cnt; \
    node_type** const pb = mpBucketArray; \
    node_type* const pNode = DoFindNode(pb[n], k); \
    return pNode ? iterator(pNode, pb + n) : iterator(pb[cnt], pb + cnt); \
}
'''
def emit(va, A, N):
    t = "HashtableK3_%08x" % va
    return ("HT_FIND3(%s, %d)" % (t, N[11]),
            "?find@%s@@QAE?AUiterator@1@ABUKey@@@Z" % t)
