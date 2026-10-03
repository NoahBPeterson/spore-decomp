# Static accessor reading a field of a global object pointer: mov eax,[g]; mov eax,[eax+off]; ret. /O2.
PATTERN = 'mov eax, dword ptr [A] ; mov eax, dword ptr [eax + N] ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    g = A[0]
    src = ("extern char* g_%08x;\n"
           "unsigned FUN_%08x() { return *(unsigned*)(g_%08x + %d); }\n") % (g, va, g, N[0])
    return src, "?FUN_%08x@@YAIXZ" % va
