# stdcall function ignoring N/4 int args and returning 0: xor eax,eax ; ret N
PATTERN = 'xor eax, eax ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    n = N[-1] // 4
    params = ", ".join("int" for _ in range(n)) or "void"
    sig = ("H" * n) if n else "X"
    return ("int __stdcall FUN_%08x(%s) { return 0; }" % (va, params),
            "?FUN_%08x@@YGH" % va + sig + "@Z" if n else "?FUN_%08x@@YGHXZ" % va)
