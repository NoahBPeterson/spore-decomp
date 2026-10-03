# Exchange a 32-bit global with the first cdecl arg, returning the old value:
# "mov ecx,[esp+4]; mov eax,[g]; mov [g],ecx; ret". Source: `old = g; g = p; return old;`.
PATTERN = "mov ecx, dword ptr [esp + N] ; mov eax, dword ptr [A] ; mov dword ptr [A], ecx ; ret "
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    g = A[0]
    src = ("extern unsigned int g_%08x;\nunsigned int FUN_%08x(unsigned int p) { unsigned int o = g_%08x; g_%08x = p; return o; }"
           % (g, va, g, g))
    return src, "?FUN_%08x@@YAII@Z" % va
