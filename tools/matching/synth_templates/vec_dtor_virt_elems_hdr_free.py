# Container dtor: explicit virtual ~T() on each element [begin,end) then EASTL deallocate of header-checked buffer.
PATTERN = 'push ebx ; push esi ; mov ebx, ecx ; mov esi, dword ptr [ebx] ; push edi ; mov edi, dword ptr [ebx + N] ; cmp esi, edi ; jae +N ; mov edi, edi ; mov eax, dword ptr [esi] ; mov edx, dword ptr [eax] ; push N ; mov ecx, esi ; call edx ; add esi, N ; cmp esi, edi ; jb +N ; mov ebx, dword ptr [ebx] ; test ebx, ebx ; je +N ; cmp dword ptr [ebx - N], N ; je +N ; push ebx ; call EXT ; add esp, N ; pop edi ; pop esi ; pop ebx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = "extern void __cdecl EASTL_allocator_deallocate(void*);\n"
def emit(va, A, N):
    stride = N[2]
    pad = stride // 4 - 1
    t = "%08x" % va
    s = "struct E_%s { virtual ~E_%s(); %s };\n" % (t, t, ("int pad[%d];" % pad) if pad else "")
    s += "struct C_%s { E_%s* b; E_%s* e; void Run(); };\n" % (t, t, t)
    s += ("void C_%s::Run() {\n E_%s* last = e;\n for (E_%s* i = b; i < last; ++i) i->~E_%s();\n"
          " if (b && ((int*)b)[-1]) EASTL_allocator_deallocate(b);\n}") % (t, t, t, t)
    return s, "?Run@C_%s@@QAEXXZ" % t
