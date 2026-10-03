# EASTL hashtable<const wchar_t* key (FNV-1 wide string hash), ...>::DoRehash(size_type), /O2, allocate/free inlined.
PATTERN = 'push ebx ; push ebp ; push esi ; mov esi, dword ptr [esp + N] ; push edi ; push N ; push A ; push N ; add esi, esi ; push N ; add esi, esi ; lea eax, [esi + N] ; push A ; push eax ; mov edi, ecx ; call EXT ; push esi ; mov ebp, eax ; push N ; push ebp ; call EXT ; xor ebx, ebx ; add esp, N ; mov dword ptr [esi + ebp], A ; cmp dword ptr [edi + N], ebx ; jbe +N ; mov ecx, dword ptr [edi + N] ; mov ecx, dword ptr [ecx + ebx*N] ; test ecx, ecx ; je +N ; mov esi, dword ptr [ecx] ; movzx edx, word ptr [esi] ; mov eax, A ; test edx, edx ; je +N ; mov edi, edi ; imul eax, eax, A ; add esi, N ; xor eax, edx ; movzx edx, word ptr [esi] ; test edx, edx ; jne +N ; xor edx, edx ; div dword ptr [esp + N] ; mov esi, dword ptr [ecx + N] ; mov eax, dword ptr [edi + N] ; mov dword ptr [eax + ebx*N], esi ; mov eax, dword ptr [ebp + edx*N] ; mov dword ptr [ecx + N], eax ; mov dword ptr [ebp + edx*N], ecx ; mov ecx, dword ptr [edi + N] ; mov ecx, dword ptr [ecx + ebx*N] ; test ecx, ecx ; jne +N ; inc ebx ; cmp ebx, dword ptr [edi + N] ; jb +N ; cmp dword ptr [edi + N], N ; jbe +N ; mov edx, dword ptr [edi + N] ; push edx ; call EXT ; mov eax, dword ptr [esp + N] ; add esp, N ; mov dword ptr [edi + N], ebp ; mov dword ptr [edi + N], eax ; pop edi ; pop esi ; pop ebp ; pop ebx ; ret N ; mov ecx, dword ptr [esp + N] ; mov dword ptr [edi + N], ebp ; mov dword ptr [edi + N], ecx ; pop edi ; pop esi ; pop ebp ; pop ebx ; ret N'
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
           "    struct node { const wchar_t* key; %(pad)snode* mpNext; };\n"
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
           "            const unsigned short* c = (const unsigned short*)pNode->key;\n"
           "            unsigned int h = 0x811c9dc5u;\n"
           "            unsigned int ch;\n"
           "            while ((ch = *c++) != 0) h = (h * 16777619u) ^ ch;\n"
           "            const size_t nNewBucketIndex = h %% nNewBucketCount;\n"
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
