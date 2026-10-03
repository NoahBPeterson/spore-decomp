# x87 /Od dynamic initializer: float dst = k / (float)(x * c);  (x float, c double, k float; all extern)
#   fld [x]; fmul qword [c]; fstp [ebp-4]; fld [ebp-4]; fdivr [k]; fstp [dst]
PATTERN = 'push ebp ; mov ebp, esp ; push ecx ; fld dword ptr [A] ; fmul qword ptr [A] ; fstp dword ptr [ebp - N] ; fld dword ptr [ebp - N] ; fdivr dword ptr [A] ; fstp dword ptr [A] ; mov esp, ebp ; pop ebp ; ret '
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    x, c, k, dst = A[0], A[1], A[2], A[3]
    s = "extern float g_%08x;\nextern const double g_%08x;\nextern float g_%08x;\n" % (x, c, k)
    s += "float g_%08x = g_%08x / (float)(g_%08x * g_%08x);\n" % (dst, k, x, c)
    return s, "??__Eg_%08x@@YAXXZ" % dst
