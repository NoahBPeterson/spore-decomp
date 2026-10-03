# bool-returning stub: mov al,1 ; ret N  (__stdcall with N/4 dword args)
PATTERN = 'mov al, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    n = N[-1] // 4
    args = ", ".join("int" for _ in range(n)) or "void"
    mang = "H" * n + "@Z" if n else "XZ"
    if N[0] == 1:
        return ("bool __stdcall FUN_%08x(%s) { return true; }" % (va, args),
                "?FUN_%08x@@YG_N%s" % (va, mang))
    return ("char __stdcall FUN_%08x(%s) { return %d; }" % (va, args, N[0]),
            "?FUN_%08x@@YGD%s" % (va, mang))
