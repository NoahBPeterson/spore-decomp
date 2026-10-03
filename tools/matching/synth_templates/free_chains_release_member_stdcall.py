# DoFreeNodes(node** p, n) stdcall: for each chain, call vslot on node->mpObj (if nonnull), deallocate node. /O2.
PATTERN = 'push ebx ; xor ebx, ebx ; cmp dword ptr [esp + N], ebx ; jbe +N ; push ebp ; mov ebp, dword ptr [esp + N] ; push esi ; push edi ; mov esi, dword ptr [ebp + ebx*N] ; test esi, esi ; je +N ; mov edi, esi ; mov ecx, dword ptr [edi + N] ; mov esi, dword ptr [esi + N] ; test ecx, ecx ; je +N ; mov eax, dword ptr [ecx] ; mov edx, dword ptr [eax + N] ; call edx ; push edi ; call EXT ; add esp, N ; test esi, esi ; jne +N ; mov dword ptr [ebp + ebx*N], N ; inc ebx ; cmp ebx, dword ptr [esp + N] ; jb +N ; pop edi ; pop esi ; pop ebp ; pop ebx ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = r'''typedef unsigned int size_t;
void EASTL_allocator_deallocate(void* p);
'''
def emit(va, A, N):
    import sys
    # N: 0xc,0xc,4,objoff,nextoff,slot,4,...
    objoff, nextoff, slot = N[3], N[4], N[5]
    pad = "unsigned int pad[%d]; " % (objoff // 4) if objoff > 0 else ""
    gap = nextoff - objoff - 4
    pad2 = "unsigned int pad2[%d]; " % (gap // 4) if gap > 0 else ""
    n = "node_%08x" % va
    i = "iface_%08x" % va
    vf = "".join("virtual void v%d() {} " % k for k in range(slot // 4 + 1)) if False else ""
    decl = "".join("virtual void v%d(); " % k for k in range(slot // 4)) + "virtual void rel();"
    src = ("struct %s { %s };\n"
           "struct %s { %s%s* mpObj; %s%s* mpNext; };\n"
           "void __stdcall FUN_%08x(%s** p, size_t n) {\n"
           "    for (size_t i = 0; i < n; ++i) {\n"
           "        %s* pNode = p[i];\n"
           "        while (pNode) {\n"
           "            %s* pCur = pNode; pNode = pNode->mpNext;\n"
           "            %s* o = pCur->mpObj; if (o) o->rel();\n"
           "            EASTL_allocator_deallocate(pCur);\n"
           "        }\n"
           "        p[i] = 0;\n"
           "    }\n}") % (i, decl, n, pad, i, pad2, n, va, n, n, n, i)
    return src, "?FUN_%08x@@YGXPAPAUnode_%08x@@I@Z" % (va, va)
