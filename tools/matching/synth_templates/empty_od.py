# Empty function in an unoptimized (/Od /Ob1) module: push ebp; mov ebp,esp; pop ebp; ret
PATTERN = "push ebp ; mov ebp, esp ; pop ebp ; ret "
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    return "void FUN_%08x() {}" % va, "?FUN_%08x@@YAXXZ" % va
