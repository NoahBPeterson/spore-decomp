# EASTL hashtable<uint32_t key, ...>::DoRehash(size_type nNewBucketCount), /O2, with
# DoAllocateBuckets / DoFreeBuckets / allocator::allocate inlined. The allocator is the EASTL
# default allocator whose allocate() forwards to EASTL_allocator_allocate(n, name, 0, 0,
# __FILE__ (allocator.h), 0xd1) with a per-module name string ("Editor", "Graphics", ...).
# Hash is identity (eastl::hash<uint32_t>), mod_range_hashing => div. The only varying shape
# is the offset of mpNext inside the node (N[12]); name string is a masked relocation.
PATTERN = 'push ebx ; push ebp ; mov ebp, dword ptr [esp + N] ; push esi ; push edi ; push N ; push A ; push N ; push N ; lea edi, [ebp*N] ; lea eax, [edi + N] ; push A ; push eax ; mov esi, ecx ; call EXT ; push edi ; mov ebx, eax ; push N ; push ebx ; call EXT ; mov dword ptr [edi + ebx], A ; xor edi, edi ; add esp, N ; cmp dword ptr [esi + N], edi ; jbe +N ; lea esp, [esp] ; mov ecx, dword ptr [esi + N] ; mov ecx, dword ptr [ecx + edi*N] ; test ecx, ecx ; je +N ; lea ebx, [ebx] ; mov eax, dword ptr [ecx] ; xor edx, edx ; div dword ptr [esp + N] ; mov ebp, dword ptr [ecx + N] ; mov eax, dword ptr [esi + N] ; mov dword ptr [eax + edi*N], ebp ; mov eax, dword ptr [ebx + edx*N] ; mov dword ptr [ecx + N], eax ; mov dword ptr [ebx + edx*N], ecx ; mov ecx, dword ptr [esi + N] ; mov ecx, dword ptr [ecx + edi*N] ; test ecx, ecx ; jne +N ; inc edi ; cmp edi, dword ptr [esi + N] ; jb +N ; mov ebp, dword ptr [esp + N] ; cmp dword ptr [esi + N], N ; jbe +N ; mov edx, dword ptr [esi + N] ; push edx ; call EXT ; add esp, N ; pop edi ; mov dword ptr [esi + N], ebx ; mov dword ptr [esi + N], ebp ; pop esi ; pop ebp ; pop ebx ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = r'''typedef unsigned int size_t;
extern "C" void* __cdecl memset(void*, int, size_t);
#pragma intrinsic(memset)
void* EASTL_allocator_allocate(size_t n, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);
void EASTL_allocator_deallocate(void* p);
'''

def emit(va, A, N):
    nxt = N[12]
    h = "hashtable_%08x" % va
    pad = "unsigned int pad[%d]; " % ((nxt - 4) // 4) if nxt > 4 else ""
    src = ("extern const char s_%(h)s[];\n"
           "struct %(h)s {\n"
           "    struct node { unsigned int key; %(pad)snode* mpNext; };\n"
           "    unsigned int mFunctors; node** mpBucketArray; size_t mnBucketCount; size_t mnElementCount;\n"
           "    void* alloc(size_t n) { return EASTL_allocator_allocate(n, s_%(h)s, 0, 0, \"allocator.h\", 0xd1); }\n"
           "    node** DoAllocateBuckets(size_t n) {\n"
           "        node** const p = (node**)alloc((n + 1) * sizeof(node*));\n"
           "        memset(p, 0, n * sizeof(node*));\n"
           "        p[n] = (node*)(unsigned int)~0;\n"
           "        return p;\n"
           "    }\n"
           "    void DoFreeBuckets(node** p, size_t n) { if (n > 1) EASTL_allocator_deallocate(p); }\n"
           "    void DoRehash(size_t nNewBucketCount);\n"
           "};\n"
           "void %(h)s::DoRehash(size_t nNewBucketCount) {\n"
           "    node** const pBucketArray = DoAllocateBuckets(nNewBucketCount);\n"
           "    node* pNode;\n"
           "    for (size_t i = 0; i < mnBucketCount; ++i) {\n"
           "        while ((pNode = mpBucketArray[i]) != 0) {\n"
           "            const size_t nNewBucketIndex = pNode->key %% nNewBucketCount;\n"
           "            mpBucketArray[i] = pNode->mpNext;\n"
           "            pNode->mpNext = pBucketArray[nNewBucketIndex];\n"
           "            pBucketArray[nNewBucketIndex] = pNode;\n"
           "        }\n"
           "    }\n"
           "    DoFreeBuckets(mpBucketArray, mnBucketCount);\n"
           "    mnBucketCount = nNewBucketCount;\n"
           "    mpBucketArray = pBucketArray;\n"
           "}") % dict(h=h, pad=pad)
    return src, "?DoRehash@%s@@QAEXI@Z" % h
