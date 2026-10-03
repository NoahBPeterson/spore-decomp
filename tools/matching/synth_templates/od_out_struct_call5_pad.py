# /Od function f(a,b,c) that returns an int through a hidden out-slot: copies its 3 args to a local struct
# (right to left), then calls ext(&r, k.a, k.b, k.c, u.c) cdecl with an uninitialized byte, returns r.
# Local slot order at /Od depends on local names (pukr, i.e. r->"p", u->"u", k->"k", pad->"r" matched);
# the unused pad struct size comes from the `sub esp, N` immediate (N[0]).
PATTERN = 'push ebp ; mov ebp, esp ; sub esp, N ; mov eax, dword ptr [ebp + N] ; mov dword ptr [ebp - N], eax ; mov ecx, dword ptr [ebp + N] ; mov dword ptr [ebp - N], ecx ; mov edx, dword ptr [ebp + N] ; mov dword ptr [ebp - N], edx ; movzx eax, byte ptr [ebp - N] ; push eax ; mov ecx, dword ptr [ebp - N] ; push ecx ; mov edx, dword ptr [ebp - N] ; push edx ; mov eax, dword ptr [ebp - N] ; push eax ; lea ecx, [ebp - N] ; push ecx ; call EXT ; add esp, N ; mov eax, dword ptr [ebp - N] ; mov esp, ebp ; pop ebp ; ret '
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """struct K521 { int a, b, c; };
struct U521 { char a, b, c, d; };
"""
def emit(va, A, N):
    n = (N[0] - 0x14) // 4
    callee = "ext_%08x" % va
    src = ("void %s(int*, int, int, int, char);\n"
           "int FUN_%08x(int a, int b, int c) {\n"
           "  struct P { int v[%d]; };\n"
           "  int p; U521 u; K521 k; P r;\n"
           "  k.c = c; k.b = b; k.a = a;\n"
           "  %s(&p, k.a, k.b, k.c, u.c);\n"
           "  return p;\n}") % (callee, va, n, callee)
    return src, "?FUN_%08x@@YAHHHH@Z" % va
