# EASTL fixed_hashtable<uint32_t key,...>::DoRehash(nNew) with an out-of-line DoAllocateBuckets (stdcall-ish
# thiscall helper call EXT taking n) and an inlined fixed-pool DoFreeBuckets (pool range [0x24,0x28),
# free list head 0x1c, inline bucket buffer at 0x30). Only varying shape: mpNext offset in node (N[4]).
PATTERN: 'push ebx ; push ebp ; mov ebp, dword ptr [esp + N] ; push esi ; push edi ; push ebp ; mov esi, ecx ; call EXT ; xor edi, edi ; mov ebx, eax ; cmp dword ptr [esi + N], edi ; jbe +N ; lea esp, [esp] ; mov eax, dword ptr [esi + N] ; mov ecx, dword ptr [eax + edi*N] ; test ecx, ecx ; je +N ; lea ebx, [ebx] ; mov eax, dword ptr [ecx] ; xor edx, edx ; div ebp ; mov ebp, dword ptr [ecx + N] ; mov eax, dword ptr [esi + N] ; mov dword ptr [eax + edi*N], ebp ; mov ebp, dword ptr [esp + N] ; mov eax, dword ptr [ebx + edx*N] ; mov dword ptr [ecx + N], eax ; mov dword ptr [ebx + edx*N], ecx ; mov ecx, dword ptr [esi + N] ; mov ecx, dword ptr [ecx + edi*N] ; test ecx, ecx ; jne +N ; inc edi ; cmp edi, dword ptr [esi + N] ; jb +N ; cmp dword ptr [esi + N], N ; mov eax, dword ptr [esi + N] ; jbe +N ; cmp eax, dword ptr [esi + N] ; je +N ; cmp eax, dword ptr [esi + N] ; jb +N ; cmp eax, dword ptr [esi + N] ; jae +N ; mov edx, dword ptr [esi + N] ; mov dword ptr [eax], edx ; mov dword ptr [esi + N], eax ; pop edi ; mov dword ptr [esi + N], ebx ; mov dword ptr [esi + N], ebp ; pop esi ; pop ebp ; pop ebx ; ret N ; push eax ; call EXT ; add esp, N ; pop edi ; mov dword ptr [esi + N], ebx ; mov dword ptr [esi + N], ebp ; pop esi ; pop ebp ; pop ebx ; ret N'
PATTERN = 'push ebx ; push ebp ; mov ebp, dword ptr [esp + N] ; push esi ; push edi ; push ebp ; mov esi, ecx ; call EXT ; xor edi, edi ; mov ebx, eax ; cmp dword ptr [esi + N], edi ; jbe +N ; lea esp, [esp] ; mov eax, dword ptr [esi + N] ; mov ecx, dword ptr [eax + edi*N] ; test ecx, ecx ; je +N ; lea ebx, [ebx] ; mov eax, dword ptr [ecx] ; xor edx, edx ; div ebp ; mov ebp, dword ptr [ecx + N] ; mov eax, dword ptr [esi + N] ; mov dword ptr [eax + edi*N], ebp ; mov ebp, dword ptr [esp + N] ; mov eax, dword ptr [ebx + edx*N] ; mov dword ptr [ecx + N], eax ; mov dword ptr [ebx + edx*N], ecx ; mov ecx, dword ptr [esi + N] ; mov ecx, dword ptr [ecx + edi*N] ; test ecx, ecx ; jne +N ; inc edi ; cmp edi, dword ptr [esi + N] ; jb +N ; cmp dword ptr [esi + N], N ; mov eax, dword ptr [esi + N] ; jbe +N ; cmp eax, dword ptr [esi + N] ; je +N ; cmp eax, dword ptr [esi + N] ; jb +N ; cmp eax, dword ptr [esi + N] ; jae +N ; mov edx, dword ptr [esi + N] ; mov dword ptr [eax], edx ; mov dword ptr [esi + N], eax ; pop edi ; mov dword ptr [esi + N], ebx ; mov dword ptr [esi + N], ebp ; pop esi ; pop ebp ; pop ebx ; ret N ; push eax ; call EXT ; add esp, N ; pop edi ; mov dword ptr [esi + N], ebx ; mov dword ptr [esi + N], ebp ; pop esi ; pop ebp ; pop ebx ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = r'''typedef unsigned int size_t;
void EASTL_allocator_deallocate(void* p);
'''

def emit(va, A, N):
    nxt = N[4]
    h = "fhashtable_%08x" % va
    pad = "unsigned int pad[%d]; " % ((nxt - 4) // 4) if nxt > 4 else ""
    src = ("struct %(h)s {\n"
           "    struct node { unsigned int key; %(pad)snode* mpNext; };\n"
           "    unsigned int mFunctors; node** mpBucketArray; size_t mnBucketCount; size_t mnElementCount;\n"
           "    unsigned int pad1[3]; struct Link { Link* next; }; Link* mpHead; unsigned int pad2; char* mpPoolBegin; char* mpPoolEnd; unsigned int pad3; void* mpBucketBuffer;\n"
           "    node** DoAllocateBuckets(size_t n);\n"
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
           "    node** p = mpBucketArray;\n"
           "    if (mnBucketCount > 1 && (void*)p != mpBucketBuffer) {\n"
           "        if ((char*)p >= mpPoolBegin && (char*)p < mpPoolEnd) { Link* l = (Link*)p; Link* o = mpHead; mpHead = l; l->next = o; }\n"
           "        else EASTL_allocator_deallocate(p);\n"
           "    }\n"
           "    mnBucketCount = nNewBucketCount;\n"
           "    mpBucketArray = pBucketArray;\n"
           "}") % dict(h=h, pad=pad)
    return src, "?DoRehash@%s@@QAEXI@Z" % h
