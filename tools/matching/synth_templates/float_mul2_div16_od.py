# g2 = (float)(g1 * 2.0) / 16.0f with a float temp, /Od
PATTERN = 'push ebp ; mov ebp, esp ; push ecx ; fld dword ptr [A] ; fmul qword ptr [A] ; fstp dword ptr [ebp - N] ; fld dword ptr [ebp - N] ; fdiv dword ptr [A] ; fstp dword ptr [A] ; mov esp, ebp ; pop ebp ; ret '
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    s, d = "g_%08x" % A[0], "g_%08x" % A[3]
    k2, k16 = "g_%08x" % A[1], "g_%08x" % A[2]
    src = "extern float %s, %s, %s;\nextern double %s;\nvoid FUN_%08x() { float t = %s * %s; %s = t / %s; }" % (s, d, k16, k2, va, s, k2, d, k16)
    return src, "?FUN_%08x@@YAXXZ" % va
