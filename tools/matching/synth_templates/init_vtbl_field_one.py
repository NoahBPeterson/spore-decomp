# cdecl init(p, x): p->[0]=&global; p->[4]=x; p->[8]=1
PATTERN = 'mov eax, dword ptr [esp + N] ; mov ecx, dword ptr [esp + N] ; mov dword ptr [eax], A ; mov dword ptr [eax + N], ecx ; mov dword ptr [eax + N], N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    n = N[-1] if N else 1
    src = ("extern char g_%08x[];\n"
           "void FUN_%08x(void** p, int x) { p[0] = g_%08x; p[1] = (void*)x; p[2] = (void*)%d; }\n") % (A[0], va, A[0], n)
    return src, "?FUN_%08x@@YAXPAPAXH@Z" % va
