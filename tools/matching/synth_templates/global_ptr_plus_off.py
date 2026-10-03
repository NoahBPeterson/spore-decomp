# Returns address of a field inside a global-pointed object: mov eax,[g]; add eax,N; ret.
PATTERN = 'mov eax, dword ptr [A] ; add eax, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    g = A[0]
    off = N[-1]
    src = "extern char* g_%08x;\nchar* FUN_%08x() { return g_%08x + 0x%x; }" % (g, va, g, off)
    return src, "?FUN_%08x@@YAPADXZ" % va
