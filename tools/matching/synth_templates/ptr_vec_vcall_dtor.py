# Container-of-element-structs destructor: call virtual slot on each element's first pointer, then EASTL deallocate.
PATTERN = 'push ebx ; push esi ; mov ebx, ecx ; mov esi, dword ptr [ebx] ; push edi ; mov edi, dword ptr [ebx + N] ; cmp esi, edi ; jae +N ; mov edi, edi ; mov ecx, dword ptr [esi] ; test ecx, ecx ; je +N ; mov eax, dword ptr [ecx] ; mov edx, dword ptr [eax + N] ; call edx ; add esi, N ; cmp esi, edi ; jb +N ; mov eax, dword ptr [ebx] ; pop edi ; pop esi ; pop ebx ; test eax, eax ; je +N ; cmp dword ptr [eax - N], N ; je +N ; push eax ; call EXT ; pop ecx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = "extern void __cdecl EASTL_allocator_deallocate(void*);\n"
def emit(va, A, N):
    slot = N[1] // 4
    stride = N[2]
    pad = stride // 4 - 1
    s = "struct V_%08x { " % va
    s += "".join("virtual void v%d(); " % i for i in range(slot)) + "virtual void f(); };\n"
    s += "struct E_%08x { V_%08x* p; %s };\n" % (va, va, ("int pad[%d];" % pad) if pad else "")
    s += "struct C_%08x { E_%08x* b; E_%08x* e; void Run(); };\n" % (va, va, va)
    s += ("void C_%08x::Run() {\n E_%08x* last = e;\n for (E_%08x* i = b; i < last; ++i) if (i->p) i->p->f();\n"
          " if (b && ((int*)b)[-1]) EASTL_allocator_deallocate(b);\n}") % (va, va, va)

    return s, "?Run@C_%08x@@QAEXXZ" % va
