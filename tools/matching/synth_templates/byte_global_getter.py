# Trivial getter returning a byte-sized global: mov al,[g]; ret
PATTERN = 'mov al, byte ptr [A] ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    g = "g_%08x" % A[0]
    src = "extern unsigned char %s;\nunsigned char FUN_%08x() { return %s; }" % (g, va, g)
    return src, "?FUN_%08x@@YAEXZ" % va
