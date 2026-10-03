# EASTL intrusive-style list clear: walk nodes, vcall slot on node->ptr, deallocate node. /O2.
PATTERN = 'push ebx ; mov ebx, ecx ; push esi ; mov esi, dword ptr [ebx] ; cmp esi, ebx ; je +N ; push edi ; jmp +N ; lea ecx, [ecx] ; mov edi, esi ; mov ecx, dword ptr [edi + N] ; mov esi, dword ptr [esi] ; test ecx, ecx ; je +N ; mov eax, dword ptr [ecx] ; mov edx, dword ptr [eax + N] ; call edx ; push edi ; call EXT ; add esp, N ; cmp esi, ebx ; jne +N ; pop edi ; pop esi ; pop ebx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = 'void EASTL_allocator_deallocate(void* p);\n'
def emit(va, A, N):
    off, slot = N[0], N[1] // 4
    pad = "unsigned int pad[%d]; " % ((off - 8) // 4) if off > 8 else ""
    vs = "".join("virtual void v%d(); " % i for i in range(slot + 1))
    o, n, l = "obj_%08x" % va, "node_%08x" % va, "list_%08x" % va
    nodebody = "%s* mpNext; %s* mpPrev; " % (n, n)
    if off > 8:
        nodebody += "unsigned int pad[%d]; " % ((off - 8) // 4)
    src = ("struct %s { %s};\nstruct %s { %s%s* mpObj; };\n"
           "struct %s { %s* mpNext; %s* mpPrev; void clear_%08x(); };\n"
           "void %s::clear_%08x() {\n"
           "    %s* p = mpNext;\n"
           "    while ((void*)p != (void*)this) {\n"
           "        %s* q = p; p = p->mpNext;\n"
           "        obj_%08x* o = q->mpObj; if (o) o->v%d();\n"
           "        EASTL_allocator_deallocate(q);\n"
           "    }\n}") % (o, vs, n, nodebody, o, l, n, n, va, l, va, n, n, va, slot)
    return src, "?clear_%08x@list_%08x@@QAEXXZ" % (va, va)
