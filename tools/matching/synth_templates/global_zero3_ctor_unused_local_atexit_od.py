# Dynamic initializer of a file-scope global with an inline ctor zeroing three words (e.g. begin/end/cap
# pointers) and an out-of-line dtor, in an unoptimized (/Od /Ob1) module. The `push ecx` slot comes from
# an unused local inside the inline ctor.
PATTERN = 'push ebp ; mov ebp, esp ; push ecx ; mov dword ptr [A], N ; mov dword ptr [A], N ; mov dword ptr [A], N ; push A ; call EXT ; add esp, N ; mov esp, ebp ; pop ebp ; ret '
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """struct V3 { int* a; int* b; int* c; V3() : a(0), b(0), c(0) { int unused; } ~V3(); };
"""
def emit(va, A, N):
    return "V3 g_%08x;" % min(A[:3]), "??__Eg_%08x@@YAXXZ" % min(A[:3])
