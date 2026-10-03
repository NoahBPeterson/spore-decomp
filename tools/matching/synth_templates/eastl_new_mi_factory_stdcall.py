# Factory returning a secondary-base pointer: "return (Base2*)new(\"Name\") T;" with T : A, B (B at +off)
#   push 0 x4 ; push "Name" ; push sizeof(T) ; call new ; add esp,18h ; test ; je ; mov ecx,eax ; call T::T
#   test eax ; je ; add eax,off ; ret 8 ; xor eax,eax ; ret 8      (__stdcall, two ignored args)
PATTERN = "push N ; push N ; push N ; push N ; push A ; push N ; call EXT ; add esp, N ; test eax, eax ; je +N ; mov ecx, eax ; call EXT ; test eax, eax ; je +N ; add eax, N ; ret N ; xor eax, eax ; ret N"
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ("typedef unsigned int size_t;\n"
           "void* operator new(size_t size, const char* name, int flags, unsigned debugFlags, const char* file, int line);\n")

def emit(va, A, N):
    # N = [f4,f3,f2,f1,size,0x18,off,ret,ret]
    line, file_, dbg, flags, size, off, rn = N[0], N[1], N[2], N[3], N[4], N[6], N[7]
    t = "T_%08x" % va
    src = ("struct %s_A { char d[%d]; }; struct %s_B { char d[1]; };\n"
           "struct %s : %s_A, %s_B { %s(); char e[%d]; };\n"
           "void* __stdcall FUN_%08x(int, int) { return (%s_B*)new(\"%s\", %d, %du, (const char*)%d, %d) %s; }"
           % (t, off, t, t, t, t, t, size - off - 1, va, t, t, flags, dbg, file_, line, t))
    return src, "?FUN_%08x@@YGPAXHH@Z" % va
