# Stdcall(1 arg) factory: p = new("Name") T(arg); p->f14 = 0; return p;  with old-style EH frame.
PATTERN = 'push -N ; push A ; mov eax, dword ptr fs:[N] ; push eax ; mov dword ptr fs:[N], esp ; sub esp, N ; push esi ; push N ; push A ; push N ; push N ; push A ; push N ; call EXT ; mov esi, eax ; add esp, N ; mov dword ptr [esp + N], esi ; mov dword ptr [esp + N], esi ; mov dword ptr [esp + N], N ; test esi, esi ; je +N ; mov eax, dword ptr [esp + N] ; push eax ; mov ecx, esi ; call EXT ; mov ecx, dword ptr [esp + N] ; mov dword ptr [esi + N], N ; mov eax, esi ; pop esi ; mov dword ptr fs:[N], ecx ; add esp, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GS-"]
PRELUDE = ("typedef unsigned int size_t;\n"
           "void* operator new(size_t, const char*, int, unsigned, const char*, int);\n"
           "void operator delete(void*, const char*, int, unsigned, const char*, int);\n")

def emit(va, A, N):
    t = "T_%08x" % va
    src = ("extern const char s_%08x[];\nextern const char f_%08x[];\n"
           "struct %s { %s(void*); int d[5]; int x; };\n"
           "%s* __stdcall FUN_%08x(void* a) { %s* p = new(s_%08x, 0, 0u, f_%08x, %d) %s(a); p->x = 0; return p; }"
           % (A[2], A[1], t, t, t, va, t, A[2], A[1], N[N.index(209)], t))
    return src, "?FUN_%08x@@YGPAU%s@@PAX@Z" % (va, t)
