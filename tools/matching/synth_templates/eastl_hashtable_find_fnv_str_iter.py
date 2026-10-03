# EASTL hashtable<const char* key, FNV-1 string hash>::find(const key&) returning iterator (hidden ret ptr), /O2.
PATTERN = 'mov eax, dword ptr [esp + N] ; sub esp, N ; push ebx ; push ebp ; push esi ; mov esi, dword ptr [eax] ; movzx edx, byte ptr [esi] ; push edi ; mov eax, A ; test edx, edx ; je +N ; lea esp, [esp] ; imul eax, eax, A ; inc esi ; xor eax, edx ; movzx edx, byte ptr [esi] ; test edx, edx ; jne +N ; mov edi, dword ptr [ecx + N] ; xor edx, edx ; div edi ; mov ebx, dword ptr [ecx + N] ; mov esi, dword ptr [ebx + edx*N] ; lea ebp, [ebx + edx*N] ; test esi, esi ; je +N ; mov ecx, dword ptr [esp + N] ; push esi ; push ecx ; call EXT ; add esp, N ; test al, al ; jne +N ; mov esi, dword ptr [esi + N] ; test esi, esi ; jne +N ; mov edx, dword ptr [ebx + edi*N] ; lea eax, [ebx + edi*N] ; mov dword ptr [esp + N], edx ; mov dword ptr [esp + N], eax ; mov eax, dword ptr [esp + N] ; pop edi ; lea ecx, [esp + N] ; mov edx, dword ptr [ecx] ; mov ecx, dword ptr [ecx + N] ; pop esi ; pop ebp ; mov dword ptr [eax], edx ; mov dword ptr [eax + N], ecx ; pop ebx ; add esp, N ; ret N ; test esi, esi ; je +N ; mov dword ptr [esp + N], esi ; mov dword ptr [esp + N], ebp ; jmp +N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = ""
def emit(va, A, N):
    nxt = N[8]
    h = "HT_%08x" % va
    pad = "unsigned int pad[%d]; " % ((nxt - 4) // 4) if nxt > 4 else ""
    src = ("struct %(h)s {\n"
           "    struct node { const char* key; %(pad)snode* mpNext; };\n"
           "    struct iterator { node* mpNode; node** mpBucket; iterator(node* n, node** b) : mpNode(n), mpBucket(b) {} iterator(node** b) : mpNode(*b), mpBucket(b) {} iterator(const iterator& o) : mpNode(o.mpNode), mpBucket(o.mpBucket) {} };\n"
           "    unsigned int pad0; node** mpBucketArray; unsigned int mnBucketCount;\n"
           "    static bool __cdecl eq(const char* const&, node*);\n"
           "    iterator find(const char* const& k);\n"
           "};\n"
           "%(h)s::iterator %(h)s::find(const char* const& k) {\n"
           "    const unsigned char* c = (const unsigned char*)k;\n"
           "    unsigned int h = 0x811c9dc5u;\n"
           "    unsigned int ch;\n"
           "    while ((ch = *c++) != 0) h = (h * 16777619u) ^ ch;\n"
           "    const unsigned int cnt = mnBucketCount;\n"
           "    const unsigned int n = h %% cnt;\n"
           "    node** const arr = mpBucketArray;\n"
           "    node** const pBucket = arr + n;\n"
           "    node* pNode = *pBucket;\n"
           "    for (; pNode; pNode = pNode->mpNext)\n"
           "        if (eq(k, pNode)) break;\n"
           "    return pNode ? iterator(pNode, pBucket) : iterator(arr + cnt);\n"
           "}") % dict(h=h, pad=pad)
    return src, "?find@%s@@QAE?AUiterator@1@ABQBD@Z" % h
