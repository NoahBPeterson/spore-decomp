# int-arg == K ? &global : 0  (setne/dec/and select)
PATTERN = 'xor eax, eax ; cmp dword ptr [esp + N], N ; setne al ; dec eax ; and eax, A ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    g = "g_%08x" % A[0]
    k = N[-1] if len(N) > 1 else N[0]
    k = N[1]
    return ("extern char %s;\nchar* FUN_%08x(int a) { return a == 0x%x ? &%s : 0; }" % (g, va, k, g),
            "?FUN_%08x@@YAPADH@Z" % va)
