# Factory with an inlined ctor of T : A, B (A = vptr only, B = vptr + int member zeroed), __stdcall(int,int):
#   return new("Name") T;   -> allocate 12, B vptr/zero, A vptr, B final vptr, ret 8
PATTERN = "push N ; push N ; push N ; push N ; push A ; push N ; call EXT ; add esp, N ; test eax, eax ; je +N ; mov dword ptr [eax + N], A ; mov dword ptr [eax + N], N ; mov dword ptr [eax], A ; mov dword ptr [eax + N], A ; ret N ; xor eax, eax ; ret N"
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ("typedef unsigned int size_t;\n"
           "void* operator new(size_t size, const char* name, int flags, unsigned debugFlags, const char* file, int line);\n")

def emit(va, A, N):
    line, file_, dbg, flags = N[0], N[1], N[2], N[3]
    t = "T_%08x" % va
    src = ("struct %s_A { virtual void ga(); };\n"
           "struct %s_B { virtual void fb(); int x; %s_B() : x(0) {} };\n"
           "struct %s : %s_A, %s_B { %s() {} virtual void ga(); virtual void fb(); };\n"
           "void* __stdcall FUN_%08x(int, int) { return new(\"%s\", %d, %du, (const char*)%d, %d) %s; }"
           % (t, t, t, t, t, t, t, va, t, flags, dbg, file_, line, t))
    return src, "?FUN_%08x@@YGPAXHH@Z" % va
