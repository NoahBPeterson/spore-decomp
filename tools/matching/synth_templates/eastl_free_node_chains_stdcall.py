# EASTL hashtable DoFreeNodes(node** pArr, size_t n) as a stdcall free function, /O2.
import re
PATTERN = 'push ebp ; mov ebp, dword ptr [esp + N] ; push edi ; xor edi, edi ; test ebp, ebp ; jbe +N ; push ebx ; mov ebx, dword ptr [esp + N] ; push esi ; mov esi, dword ptr [ebx + edi*N] ; test esi, esi ; je +N ; lea esp, [esp] ; mov eax, esi ; mov esi, dword ptr [esi + N] ; push eax ; call EXT ; add esp, N ; test esi, esi ; jne +N ; mov dword ptr [ebx + edi*N], N ; inc edi ; cmp edi, ebp ; jb +N ; pop esi ; pop ebx ; pop edi ; pop ebp ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = r'''typedef unsigned int size_t;
void EASTL_allocator_deallocate(void* p);
'''
def emit(va, A, N):
    off = N[3]
    pad = "unsigned int pad[%d]; " % (off // 4) if off > 0 else ""
    n = "node_%08x" % va
    src = ("struct %s { %s%s* mpNext; };\n"
           "void __stdcall FUN_%08x(%s** p, size_t n) {\n"
           "    for (size_t i = 0; i < n; ++i) {\n"
           "        %s* pNode = p[i];\n"
           "        while (pNode) { %s* pCur = pNode; pNode = pNode->mpNext; EASTL_allocator_deallocate(pCur); }\n"
           "        p[i] = 0;\n"
           "    }\n}") % (n, pad, n, va, n, n, n)
    return src, "?FUN_%08x@@YGXPAPAUnode_%08x@@I@Z" % (va, va)
