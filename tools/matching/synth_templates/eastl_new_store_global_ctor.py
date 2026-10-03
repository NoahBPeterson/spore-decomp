# Global singleton init: "g = new(\"Name\") T;" through EASTL's debug operator new, ctor called out of line.
#   push 0 x4 ; push "Name" ; push sizeof(T) ; call new ; add esp,18h ; test ; je null ;
#   mov ecx,eax ; call T::T ; mov [g],eax ; ret ; null: mov [g],0 ; ret
PATTERN = 'push N ; push N ; push N ; push N ; push A ; push N ; call EXT ; add esp, N ; test eax, eax ; je +N ; mov ecx, eax ; call EXT ; mov dword ptr [A], eax ; ret  ; mov dword ptr [A], N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ("typedef unsigned int size_t;\n"
           "void* operator new(size_t size, const char* name, int flags, unsigned debugFlags, const char* file, int line);\n")

def emit(va, A, N):
    line, file_, dbg, flags, size = N[0], N[1], N[2], N[3], N[4]
    t = "T_%08x" % va
    src = ("struct %s { %s(); char d[%d]; };\n"
           "%s* g_%08x;\n"
           "void FUN_%08x() { g_%08x = new(\"%s\", %d, %du, (const char*)%d, %d) %s; }"
           % (t, t, size, t, A[1], va, A[1], t, flags, dbg, file_, line, t))
    return src, "?FUN_%08x@@YAXXZ" % va
