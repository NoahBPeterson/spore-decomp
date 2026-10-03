# Derived-class dtor: loop ~E() over [b,e) (end cached), base ~B() (inline: EASTL header-checked free) inlined at end.
# Throwing dealloc decl removes the state=-1 store. Unwind funclet in original calls out-of-line B::~B.
PATTERN = 'push -N ; push A ; mov eax, dword ptr fs:[N] ; push eax ; mov dword ptr fs:[N], esp ; push ecx ; push ebx ; push esi ; mov ebx, ecx ; push edi ; mov dword ptr [esp + N], ebx ; mov edi, dword ptr [ebx + N] ; mov esi, dword ptr [ebx] ; mov dword ptr [esp + N], N ; cmp esi, edi ; jae +N ; mov ecx, esi ; call EXT ; add esi, N ; cmp esi, edi ; jb +N ; mov ebx, dword ptr [ebx] ; test ebx, ebx ; je +N ; cmp dword ptr [ebx - N], N ; je +N ; push ebx ; call EXT ; add esp, N ; mov ecx, dword ptr [esp + N] ; pop edi ; pop esi ; pop ebx ; mov dword ptr fs:[N], ecx ; add esp, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-", "/GS-"]
PRELUDE = "extern void __cdecl EASTL_allocator_deallocate(void*) throw();\n"
def emit(va, A, N):
    t = "%08x" % va
    stride = N[7]
    src = ("struct E_%s { char pad[%d]; ~E_%s(); };\n"
           "struct B_%s { E_%s* b; E_%s* e; ~B_%s() { if (b && ((int*)b)[-1]) EASTL_allocator_deallocate(b); } };\n"
           "struct V_%s : B_%s { ~V_%s() { E_%s* l = e; for (E_%s* i = b; i < l; ++i) i->~E_%s(); } };\n"
           "void FUN_%s(V_%s* v) { v->~V_%s(); }") % ((t, stride, t) + (t,)*4 + (t,)*6 + (t,)*3)
    return src, "??1V_%s@@QAE@XZ" % t
