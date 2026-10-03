# Dynamic initializer of a file-scope global constructed with an out-of-line 2-int-argument
# constructor and out-of-line destructor (atexit ??__F stub): `GObj2 g(a1,a2);` at /O2.
PATTERN = 'push N ; push N ; mov ecx, A ; call EXT ; push A ; call EXT ; pop ecx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """struct GObj2 { GObj2(int, int); ~GObj2(); int pad; };
"""
def emit(va, A, N):
    return ("GObj2 g_%08x(%d, %d);" % (A[0], N[1], N[0]),
            "??__Eg_%08x@@YAXXZ" % A[0])
