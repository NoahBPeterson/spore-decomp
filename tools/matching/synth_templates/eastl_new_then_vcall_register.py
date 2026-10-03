# void f(Mgr* m) { m->v8(new("App") T, ID, "Name"); }  -- vcall slot 8 (+0x20) with a freshly
# EASTL-allocated object, a type id and a name string; ctor call is not a tail call.
PATTERN = 'push N ; push N ; push N ; push N ; push A ; push N ; call EXT ; add esp, N ; test eax, eax ; je +N ; mov ecx, eax ; call EXT ; jmp +N ; xor eax, eax ; mov ecx, dword ptr [esp + N] ; mov edx, dword ptr [ecx] ; push A ; push A ; push eax ; mov eax, dword ptr [edx + N] ; call eax ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ("typedef unsigned int size_t;\n"
           "void* operator new(size_t size, const char* name, int flags, unsigned debugFlags, const char* file, int line);\n"
           "struct Mgr { " + "".join("virtual void v%d(void*, unsigned, const char*) {} " % i for i in range(32)) + "};\n")

def emit(va, A, N):
    size, slot = N[4], N[7] // 4
    t = "T_%08x" % va
    src = ("struct %s { %s(); char d[%d]; };\n"
           "void FUN_%08x(Mgr* m) { m->v%d(new(\"App\", 0, 0u, (const char*)0, 0) %s, 0x%xu, (const char*)0x%x); }"
           % (t, t, size, va, slot, t, A[2], A[1]))
    return src, "?FUN_%08x@@YAXPAUMgr@@@Z" % va
