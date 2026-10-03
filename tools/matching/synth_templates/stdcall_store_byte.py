# stdcall void f(char *p, int...) { *p = imm; }  -> mov eax,[esp+4]; mov byte [eax],imm; ret 4*k
PATTERN = 'mov eax, dword ptr [esp + N] ; mov byte ptr [eax], N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    val, ret = N[1], N[2]
    k = ret // 4
    params = ["char *p"] + ["int a%d" % i for i in range(1, k)]
    src = "void __stdcall FUN_%08x(%s) { *p = %d; }" % (va, ", ".join(params), val)
    return src, "?FUN_%08x@@YGXPAD%s@Z" % (va, "H" * (k - 1))
