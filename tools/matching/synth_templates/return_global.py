# Trivial getter returning a 32-bit global: "mov eax, dword ptr [g] ; ret". /O2 leaf function,
# e.g. a static accessor `T* Get() { return sInstance; }`. Source: `return g;`.
PATTERN = "mov eax, dword ptr [A] ; ret "
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    g = A[0]
    src = "extern unsigned int g_%08x;\nunsigned int FUN_%08x() { return g_%08x; }" % (g, va, g)
    return src, "?FUN_%08x@@YAIXZ" % va
