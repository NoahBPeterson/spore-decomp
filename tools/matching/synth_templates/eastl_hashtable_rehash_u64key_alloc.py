# EASTL hashtable<pair key (2 words xor)>::DoRehash with inlined DoAllocateBuckets (allocate + memset + sentinel -1)
# and inlined DoFreeBuckets. Varying: node mpNext offset (N), allocator name string (A[1]).
PATTERN = 'push ebx ; push ebp ; mov ebp, dword ptr [esp + N] ; push esi ; push edi ; push N ; push A ; push N ; push N ; lea edi, [ebp*N] ; lea eax, [edi + N] ; push A ; push eax ; mov esi, ecx ; call EXT ; push edi ; mov ebx, eax ; push N ; push ebx ; call EXT ; mov dword ptr [edi + ebx], A ; xor edi, edi ; add esp, N ; cmp dword ptr [esi + N], edi ; jbe +N ; lea esp, [esp] ; mov ecx, dword ptr [esi + N] ; mov ecx, dword ptr [ecx + edi*N] ; test ecx, ecx ; je +N ; lea ebx, [ebx] ; mov eax, dword ptr [ecx + N] ; xor eax, dword ptr [ecx] ; xor edx, edx ; div dword ptr [esp + N] ; mov ebp, dword ptr [ecx + N] ; mov eax, dword ptr [esi + N] ; mov dword ptr [eax + edi*N], ebp ; mov eax, dword ptr [ebx + edx*N] ; mov dword ptr [ecx + N], eax ; mov dword ptr [ebx + edx*N], ecx ; mov ecx, dword ptr [esi + N] ; mov ecx, dword ptr [ecx + edi*N] ; test ecx, ecx ; jne +N ; inc edi ; cmp edi, dword ptr [esi + N] ; jb +N ; mov ebp, dword ptr [esp + N] ; cmp dword ptr [esi + N], N ; jbe +N ; mov edx, dword ptr [esi + N] ; push edx ; call EXT ; add esp, N ; pop edi ; mov dword ptr [esi + N], ebx ; mov dword ptr [esi + N], ebp ; pop esi ; pop ebp ; pop ebx ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = r'''typedef unsigned int size_t;
void* EASTL_allocator_allocate(size_t n, const char* name, int flags, int align, const char* file, int line);
void EASTL_allocator_deallocate(void* p);
void* memset(void*, int, size_t);
extern const char s_file[];
'''

def emit(va, A, N):
    nxt = N[13]
    h = "rehash_ht_%08x" % va
    src = ("extern const char nm_%(a)08x[];\n"
           "struct %(h)s {\n"
           "    struct node { unsigned int k0; unsigned int p1; unsigned int k2; %(pad)s node* mpNext; };\n"
           "    unsigned int f0; node** mpBucketArray; size_t mnBucketCount;\n"
           "    void DoRehash(size_t nNew);\n"
           "};\n"
           "void %(h)s::DoRehash(size_t nNew) {\n"
           "    const size_t sz = nNew * sizeof(node*);\n"
           "    node** const pNew = (node**)EASTL_allocator_allocate(sz + sizeof(node*), nm_%(a)08x, 0, 0, s_file, 209);\n"
           "    memset(pNew, 0, sz);\n"
           "    pNew[nNew] = (node*)0xffffffff;\n"
           "    node* pNode;\n"
           "    for (size_t i = 0; i < mnBucketCount; ++i) {\n"
           "        while ((pNode = mpBucketArray[i]) != 0) {\n"
           "            const size_t idx = (pNode->k0 ^ pNode->k2) %% nNew;\n"
           "            mpBucketArray[i] = pNode->mpNext;\n"
           "            pNode->mpNext = pNew[idx];\n"
           "            pNew[idx] = pNode;\n"
           "        }\n"
           "    }\n"
           "    if (mnBucketCount > 1) EASTL_allocator_deallocate(mpBucketArray);\n"
           "    mnBucketCount = nNew;\n"
           "    mpBucketArray = pNew;\n"
           "}") % dict(h=h, a=A[1], pad=("char pad[%d];" % (nxt - 12) if nxt > 12 else ""))
    return src, "?DoRehash@%s@@QAEXI@Z" % h
