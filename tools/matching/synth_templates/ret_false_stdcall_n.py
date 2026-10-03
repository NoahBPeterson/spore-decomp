# bool-returning stub: xor al,al ; ret N  (__stdcall with N/4 dword args)
PATTERN = 'xor al, al ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    n = N[-1] // 4
    args = ", ".join("int" for _ in range(n)) or "void"
    mang = "H" * n + "@Z" if n else "XZ"
    return ("bool __stdcall FUN_%08x(%s) { return false; }" % (va, args),
            "?FUN_%08x@@YG_N%s" % (va, mang))
