# Fixed-pool hashtable DoFreeNodes(node** p, n) thiscall: nodes inside the pool go back on its freelist, others are deallocated. /O2.
PATTERN = 'push ebx ; xor ebx, ebx ; push edi ; mov edi, ecx ; cmp dword ptr [esp + N], ebx ; jbe +N ; push ebp ; mov ebp, dword ptr [esp + N] ; push esi ; mov esi, dword ptr [ebp + ebx*N] ; test esi, esi ; je +N ; lea ebx, [ebx] ; mov eax, esi ; mov esi, dword ptr [esi + N] ; cmp eax, dword ptr [edi + N] ; je +N ; cmp eax, dword ptr [edi + N] ; jb +N ; cmp eax, dword ptr [edi + N] ; jae +N ; mov ecx, dword ptr [edi + N] ; mov dword ptr [eax], ecx ; mov dword ptr [edi + N], eax ; jmp +N ; push eax ; call EXT ; add esp, N ; test esi, esi ; jne +N ; mov dword ptr [ebp + ebx*N], N ; inc ebx ; cmp ebx, dword ptr [esp + N] ; jb +N ; pop esi ; pop ebp ; pop edi ; pop ebx ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = r'''typedef unsigned int size_t;
void EASTL_allocator_deallocate(void* p);
'''
def emit(va, A, N):
    off = N[3]
    n = "node_%08x" % va
    pad = "unsigned int pad[%d]; " % (off // 4) if off > 0 else ""
    src = ("struct %s { %s%s* mpNext; };\n"
           "struct pool_%08x {\n"
           "    unsigned int p0[7]; void* mpHead; unsigned int p1[1]; char* mpBegin; char* mpEnd; unsigned int p2; void* mpSkip;\n"
           "    void FUN_%08x(%s** p, size_t n);\n};\n"
           "void pool_%08x::FUN_%08x(%s** p, size_t n) {\n"
           "    for (size_t i = 0; i < n; ++i) {\n"
           "        %s* pNode = p[i];\n"
           "        while (pNode) {\n"
           "            %s* pCur = pNode; pNode = pNode->mpNext;\n"
           "            if (pCur != (%s*)mpSkip) {\n"
           "                if ((char*)pCur >= mpBegin && (char*)pCur < mpEnd) { *(void**)pCur = mpHead; mpHead = pCur; }\n"
           "                else EASTL_allocator_deallocate(pCur);\n"
           "            }\n"
           "        }\n"
           "        p[i] = 0;\n"
           "    }\n}") % (n, pad, n, va, va, n, va, va, n, n, n, n)
    return src, "?FUN_%08x@pool_%08x@@QAEXPAPAUnode_%08x@@I@Z" % (va, va, va)
