# Dynamic initializer of a file-scope global constructed with an out-of-line 1-int-argument
# constructor and out-of-line destructor (atexit ??__F stub): `GObj1 g(a);` at /O2.
PATTERN = 'push N ; mov ecx, A ; call EXT ; push A ; call EXT ; pop ecx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """struct GObj1 { GObj1(int); ~GObj1(); int pad; };
"""
def emit(va, A, N):
    return ("GObj1 g_%08x(%d);" % (A[0], N[0]),
            "??__Eg_%08x@@YAXXZ" % A[0])
