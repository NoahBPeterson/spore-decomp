# Stdcall(1 arg): node = alloc(size,"App",0,0,file,209); new(&node->v) pair(*p) (inline first copy + ext copy-ctor of second); return node.
PATTERN = 'push -N ; push A ; mov eax, dword ptr fs:[N] ; push eax ; mov dword ptr fs:[N], esp ; sub esp, N ; push esi ; push N ; push A ; push N ; push N ; push A ; push N ; call EXT ; mov esi, eax ; lea eax, [esi + N] ; add esp, N ; mov dword ptr [esp + N], esi ; mov dword ptr [esp + N], eax ; mov dword ptr [esp + N], N ; test eax, eax ; je +N ; mov ecx, dword ptr [esp + N] ; mov edx, dword ptr [ecx] ; add ecx, N ; push ecx ; lea ecx, [eax + N] ; mov dword ptr [eax], edx ; call EXT ; mov ecx, dword ptr [esp + N] ; mov eax, esi ; pop esi ; mov dword ptr fs:[N], ecx ; add esp, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GS-"]
PRELUDE = ("typedef unsigned int size_t;\n"
           "inline void* operator new(size_t, void* p) { return p; }\n"
           "inline void operator delete(void*, void*) {}\n"
           "void* __cdecl EASTL_alloc(size_t, const char*, int, unsigned, const char*, int);\n")

def emit(va, A, N):
    t = "T_%08x" % va
    size = N[7]
    src = ("extern const char s_%08x[];\nextern const char f_%08x[];\n"
           "struct S_%08x { S_%08x(const S_%08x&); int d; };\n"
           "struct P_%08x { int first; S_%08x second; P_%08x(const P_%08x& o) : first(o.first), second(o.second) {} };\n"
           "struct %s { int pad[4]; P_%08x v; };\n"
           "%s* __stdcall FUN_%08x(const P_%08x* a) {\n"
           "  %s* n = (%s*)EASTL_alloc(%d, s_%08x, 0, 0u, f_%08x, 209);\n"
           "  ::new(&n->v) P_%08x(*a);\n  return n;\n}"
           % (A[2], A[1], va, va, va, va, va, va, va, t, va, t, va, va, t, t, size, A[2], A[1], va))
    return src, "?FUN_%08x@@YGPAU%s@@PBUP_%08x@@@Z" % (va, t, va)
