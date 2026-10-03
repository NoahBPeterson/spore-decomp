# Container dtor: for each element [begin,end) with stride S, call vtable[1] on the pointer member at offset off, then EASTL deallocate header-checked buffer.
PATTERN = 'push ebx ; push esi ; mov ebx, ecx ; mov esi, dword ptr [ebx] ; push edi ; mov edi, dword ptr [ebx + N] ; cmp esi, edi ; jae +N ; mov edi, edi ; mov ecx, dword ptr [esi + N] ; test ecx, ecx ; je +N ; mov eax, dword ptr [ecx] ; mov edx, dword ptr [eax + N] ; call edx ; add esi, N ; cmp esi, edi ; jb +N ; mov eax, dword ptr [ebx] ; pop edi ; pop esi ; pop ebx ; test eax, eax ; je +N ; cmp dword ptr [eax - N], N ; je +N ; push eax ; call EXT ; pop ecx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = "extern void __cdecl EASTL_allocator_deallocate(void*);\n"
def emit(va, A, N):
    off, stride = N[1], N[3]
    t = "%08x" % va
    s = "struct I_%s { %s virtual void Release(); };\n" % (t, "".join("virtual void v%d(); " % k for k in range(N[2] // 4)))
    s += "struct E_%s { %s I_%s* p; %s };\n" % (t, ("int pad[%d];" % (off // 4)) if off else "", t,
          ("int pad2[%d];" % ((stride - off - 4) // 4)) if stride - off - 4 else "")
    s += "struct C_%s { E_%s* b; E_%s* e; void Run(); };\n" % (t, t, t)
    s += ("void C_%s::Run() {\n E_%s* last = e;\n for (E_%s* i = b; i < last; ++i) { I_%s* q = i->p; if (q) q->Release(); }\n"
          " if (b && ((int*)b)[-1]) EASTL_allocator_deallocate(b);\n}") % (t, t, t, t)
    return s, "?Run@C_%s@@QAEXXZ" % t
