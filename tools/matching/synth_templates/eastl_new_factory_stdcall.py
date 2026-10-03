# Factory "return new(\"Name\") T;" as __stdcall(int,int) with out-of-line ctor:
#   push 0 x4 ; push "Name" ; push sizeof(T) ; call new ; add esp,18h ; test ; je ; mov ecx,eax ; call T::T ; ret 8 ; xor eax,eax ; ret 8
PATTERN = "push N ; push N ; push N ; push N ; push A ; push N ; call EXT ; add esp, N ; test eax, eax ; je +N ; mov ecx, eax ; call EXT ; ret N ; xor eax, eax ; ret N"
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ("typedef unsigned int size_t;\n"
           "void* operator new(size_t size, const char* name, int flags, unsigned debugFlags, const char* file, int line);\n")

def emit(va, A, N):
    line, file_, dbg, flags, size = N[0], N[1], N[2], N[3], N[4]
    t = "T_%08x" % va
    src = ("struct %s { %s(); char d[%d]; };\n"
           "void* __stdcall FUN_%08x(int, int) { return new(\"%s\", %d, %du, (const char*)%d, %d) %s; }"
           % (t, t, size, va, t, flags, dbg, file_, line, t))
    return src, "?FUN_%08x@@YGPAXHH@Z" % va
