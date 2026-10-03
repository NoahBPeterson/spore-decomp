# cdecl f(a1..ak) { return ak; }  ->  mov eax,[esp+4*k] ; ret   (N[0] = stack displacement)
PATTERN = 'mov eax, dword ptr [esp + N] ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    k = N[0] // 4
    params = ", ".join("int a%d" % i for i in range(1, k + 1))
    return ("int FUN_%08x(%s) { return a%d; }" % (va, params, k),
            "?FUN_%08x@@YA%s@Z" % (va, "H" * (k + 1)))
