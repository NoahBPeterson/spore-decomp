# float getter returning a global float: fld dword ptr [g]; ret
PATTERN = 'fld dword ptr [A] ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    return ("extern float g_%08x;\nfloat FUN_%08x() { return g_%08x; }" % (A[0], va, A[0]),
            "?FUN_%08x@@YAMXZ" % va)
