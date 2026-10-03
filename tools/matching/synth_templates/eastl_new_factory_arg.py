# Factory with one forwarded argument: "return new(\"Name\") T(arg);" via EASTL operator new.
# Ctor call is call+ret (not a tail jmp) in the original; modelled with a non-ctor-looking
# thiscall member returning void* so the optimizer does not tail-jump.
PATTERN = 'push N ; push N ; push N ; push N ; push A ; push N ; call EXT ; add esp, N ; test eax, eax ; je +N ; mov ecx, dword ptr [esp + N] ; push ecx ; mov ecx, eax ; call EXT ; ret  ; xor eax, eax ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ("typedef unsigned int size_t;\n"
           "void* operator new(size_t size, const char* name, int flags, unsigned debugFlags, const char* file, int line);\n")

def emit(va, A, N):
    line, file_, dbg, flags, size = N[0], N[1], N[2], N[3], N[4]
    t = "T_%08x" % va
    src = ("struct %s { %s(void*); char d[%d]; };\n"
           "void* FUN_%08x(void* a) { return new(\"n\", %d, %du, (const char*)%d, %d) %s(a); }"
           % (t, t, size, va, flags, dbg, file_, line, t))
    return src, "?FUN_%08x@@YAPAXPAX@Z" % va
