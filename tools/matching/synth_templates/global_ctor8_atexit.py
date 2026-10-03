# Dynamic initializer of a file-scope global object constructed with an out-of-line 8-argument
# constructor and destroyed by an out-of-line destructor (registered via atexit ??__F stub):
#   push a8..a1; mov ecx, &g; call T::T; push ??__Fg; call atexit; pop ecx; ret
# Real ??__E<var>@@YAXXZ form is reproduced: `T g(a1,...,a8);` at /O2. Instances observed use
# (size, 0, 0x80, 0, -1, 0, 0, 0) - likely an allocator/pool-like object; ctor/dtor are relocs.
PATTERN = 'push N ; push N ; push N ; push -N ; push N ; push N ; push N ; push N ; mov ecx, A ; call EXT ; push A ; call EXT ; pop ecx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """struct GObj8 { GObj8(int, int, int, int, int, int, int, int); ~GObj8(); int pad; };
"""
def emit(va, A, N):
    a = list(N[:8]); a[3] = -a[3]
    a.reverse()
    return ("GObj8 g_%08x(%s);" % (A[0], ", ".join("%d" % x for x in a)),
            "??__Eg_%08x@@YAXXZ" % A[0])
