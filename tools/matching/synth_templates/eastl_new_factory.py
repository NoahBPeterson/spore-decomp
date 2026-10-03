# Factory function: "return new(\"Name\") T;" through EASTL's debug operator new
#   push 0 x4 ; push "Name" ; push sizeof(T) ; call operator new(size, name, flags, debugFlags, file, line)
#   add esp,18h ; test eax,eax ; je null ; mov ecx,eax ; jmp T::T ; null: xor eax,eax ; ret
# /O2 turns the constructor call into a tail jump because MSVC ctors return `this` in eax.
# T is modelled as an opaque struct of the right size with an out-of-line ctor (call/jmp targets
# and the name string are relocations, masked). Allocation goes through an extern placement-style
# operator new taking EASTL's 6-argument signature (the callee is EASTL_allocator_allocate).
PATTERN = "push N ; push N ; push N ; push N ; push A ; push N ; call EXT ; add esp, N ; test eax, eax ; je +N ; mov ecx, eax ; jmp EXT ; xor eax, eax ; ret "
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ("typedef unsigned int size_t;\n"
           "void* operator new(size_t size, const char* name, int flags, unsigned debugFlags, const char* file, int line);\n")

def emit(va, A, N):
    # N = [f4(line), f3(file), f2(debugFlags), f1(flags), size]
    line, file_, dbg, flags, size = N[0], N[1], N[2], N[3], N[4]
    t = "T_%08x" % va
    src = ("struct %s { %s(); char d[%d]; };\n"
           "void* FUN_%08x() { return new(\"%s\", %d, %du, (const char*)%d, %d) %s; }"
           % (t, t, size, va, t, flags, dbg, file_, line, t))
    return src, "?FUN_%08x@@YAPAXXZ" % va
