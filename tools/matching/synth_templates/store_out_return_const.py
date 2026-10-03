# int f(int,..., int* out) { *out = A; return B; } cdecl, /O2; out at [esp+N0]
PATTERN = 'mov eax, dword ptr [esp + N] ; mov dword ptr [eax], N ; mov eax, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    k = N[0] // 4  # total args, out is last
    params = ", ".join(["int"] * (k - 1) + ["int* out"])
    return ("int FUN_%08x(%s) { *out = %d; return %d; }" % (va, params, N[1], N[2]),
            "?FUN_%08x@@YAH%s@Z" % (va, "H" * (k - 1) + "PAH"))
