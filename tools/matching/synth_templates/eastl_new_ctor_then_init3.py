# "T* p = new(\"Swarm\") T; Init(a, b, p); return p;" via EASTL operator new, out-of-line ctor,
# cdecl Init(a,b,p) call after construction (not inlined).
PATTERN = 'push esi ; push N ; push N ; push N ; push N ; push A ; push N ; call EXT ; add esp, N ; test eax, eax ; je +N ; mov ecx, eax ; call EXT ; mov esi, eax ; jmp +N ; xor esi, esi ; mov eax, dword ptr [esp + N] ; mov ecx, dword ptr [esp + N] ; push esi ; push eax ; push ecx ; call EXT ; add esp, N ; mov eax, esi ; pop esi ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ("typedef unsigned int size_t;\n"
           "void* operator new(size_t size, const char* name, int flags, unsigned debugFlags, const char* file, int line);\n")

def emit(va, A, N):
    size = N[-1] if False else None
    # N order: push 0 x4 (line,file,dbg,flags), size, then stack offsets
    line, file_, dbg, flags, size = N[0], N[1], N[2], N[3], N[4]
    t = "T_%08x" % va
    src = ("struct %s { %s(); char d[%d]; };\n"
           "void I_%08x(int, int, %s*);\n"
           "%s* FUN_%08x(int a, int b) { %s* p = new(\"n\", %d, %du, (const char*)%d, %d) %s; I_%08x(a, b, p); return p; }"
           % (t, t, size, va, t, t, va, t, flags, dbg, file_, line, t, va))
    return src, "?FUN_%08x@@YAPAU%s@@HH@Z" % (va, t)
