# /Od /Ob1 cdecl thunk passing the address of a global to an external cdecl function:
#   push ebp; mov ebp,esp; push offset g; call f; add esp,4; pop ebp; ret
# Typically compiler-style init/teardown helpers (e.g. ctor/dtor/atexit wrappers) in unoptimized modules.
PATTERN = "push ebp ; mov ebp, esp ; push A ; call EXT ; add esp, N ; pop ebp ; ret "
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "void ext_cdecl_ptr(void*);\n"
def emit(va, A, N):
    g = "g_%08x" % A[0]
    if N and N[0] != 4:
        return "// unexpected arg size", "?unexpected_%08x@@YAXXZ" % va
    src = "extern int %s;\nvoid FUN_%08x() { ext_cdecl_ptr(&%s); }" % (g, va, g)
    return src, "?FUN_%08x@@YAXXZ" % va
