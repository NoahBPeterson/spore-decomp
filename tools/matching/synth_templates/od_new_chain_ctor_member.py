# /Od member factory: return new("Name") T; with T : M : B chain inlined (/Ob1): B vptr + int zeroed, M vptr, T vptr.
PATTERN = 'push ebp ; mov ebp, esp ; sub esp, N ; mov dword ptr [ebp - N], ecx ; push N ; push N ; push N ; push N ; push A ; push N ; call EXT ; add esp, N ; mov dword ptr [ebp - N], eax ; cmp dword ptr [ebp - N], N ; je +N ; mov eax, dword ptr [ebp - N] ; mov dword ptr [eax], A ; mov ecx, dword ptr [ebp - N] ; mov dword ptr [ecx + N], N ; mov edx, dword ptr [ebp - N] ; mov dword ptr [edx], A ; mov eax, dword ptr [ebp - N] ; mov dword ptr [eax], A ; mov ecx, dword ptr [ebp - N] ; mov dword ptr [ebp - N], ecx ; jmp +N ; mov dword ptr [ebp - N], N ; mov eax, dword ptr [ebp - N] ; mov esp, ebp ; pop ebp ; ret '
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ("typedef unsigned int size_t;\n"
           "void* operator new(size_t size, const char* name, int flags, unsigned debugFlags, const char* file, int line);\n")

def emit(va, A, N):
    line, file_, dbg, flags, size = N[2], N[3], N[4], N[5], N[6]
    t = "T_%08x" % va
    src = ("struct %s_B { virtual void fb(); int x; %s_B() : x(0) {} };\n"
           "struct %s_M : %s_B { %s_M() {} virtual void fb(); };\n"
           "struct %s : %s_M { %s() {} virtual void fb(); };\n"
           "struct C_%08x { void* FUN_%08x(); };\n"
           "void* C_%08x::FUN_%08x() { return new(\"%s\", %d, %du, (const char*)%d, %d) %s; }"
           % (t, t, t, t, t, t, t, t, va, va, va, va, t, flags, dbg, file_, line, t))
    return src, "?FUN_%08x@C_%08x@@QAEPAXXZ" % (va, va)
