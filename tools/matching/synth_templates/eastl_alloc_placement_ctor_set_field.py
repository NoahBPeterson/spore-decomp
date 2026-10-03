# Stdcall(1 arg) EASTL node factory with old-style EH frame:
#   p = (T*)EASTL_allocator_allocate(0x18,"Name",0,0,file,209); ::new(p) T(arg); p->x = 0; return p;
# Placement new/delete must be declared inline with a matching placement delete(void*,void*) so the EH
# frame (unwind: delete(p,p)) is emitted.
PATTERN = 'push -N ; push A ; mov eax, dword ptr fs:[N] ; push eax ; mov dword ptr fs:[N], esp ; sub esp, N ; push esi ; push N ; push A ; push N ; push N ; push A ; push N ; call EXT ; mov esi, eax ; add esp, N ; mov dword ptr [esp + N], esi ; mov dword ptr [esp + N], esi ; mov dword ptr [esp + N], N ; test esi, esi ; je +N ; mov eax, dword ptr [esp + N] ; push eax ; mov ecx, esi ; call EXT ; mov ecx, dword ptr [esp + N] ; mov dword ptr [esi + N], N ; mov eax, esi ; pop esi ; mov dword ptr fs:[N], ecx ; add esp, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GS-"]
PRELUDE = ("typedef unsigned int size_t;\n"
           "inline void* operator new(size_t, void* p) { return p; }\n"
           "inline void operator delete(void*, void*) {}\n"
           "void* eastl_alloc(size_t, const char*, int, unsigned, const char*, int);\n")

def emit(va, A, N):
    t = "T_%08x" % va
    i = N.index(0xd1)
    size, off, line = N[i + 3], N[i + 11], N[i]
    src = ("extern const char s_%08x[];\nextern const char f_%08x[];\n"
           "struct %s { %s(void*); char d[%d]; int x; char e[%d]; };\n"
           "%s* __stdcall FUN_%08x(void* a) { %s* p = (%s*)eastl_alloc(%d, s_%08x, 0, 0u, f_%08x, %d); ::new(p) %s(a); p->x = 0; return p; }"
           % (A[2], A[1], t, t, off, size - off - 4, t, va, t, t, size, A[2], A[1], line, t))
    return src, "?FUN_%08x@@YGPAU%s@@PAX@Z" % (va, t)
