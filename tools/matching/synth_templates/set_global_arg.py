# Trivial cdecl setter storing its first argument into a 32-bit global:
# "mov eax, [esp+4] ; mov dword ptr [g], eax ; ret". /O2 leaf function, e.g. a static
# `void SetInstance(T* p) { sInstance = p; }`. Source: `g = arg;`.
PATTERN = "mov eax, dword ptr [esp + N] ; mov dword ptr [A], eax ; ret "
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    g = A[0]
    k = (N[0] - 4) // 4  # argument index (normally 0)
    params = ", ".join("unsigned int p%d" % i for i in range(k + 1))
    src = ("extern unsigned int g_%08x;\nvoid FUN_%08x(%s) { g_%08x = p%d; }"
           % (g, va, params, g, k))
    return src, "?FUN_%08x@@YAX%s@Z" % (va, "I" * (k + 1))
