# __thiscall member returning this->[N0] - this->[N1] (int fields)
PATTERN = 'mov eax, dword ptr [ecx + N] ; sub eax, dword ptr [ecx + N] ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    a, b = N[0], N[1]
    hi = max(a, b) // 4 + 1
    return ("struct S_%08x { int f[%d]; int get() const; };\n"
            "int S_%08x::get() const { return f[%d] - f[%d]; }" % (va, hi, va, a // 4, b // 4)), "?get@S_%08x@@QBEHXZ" % va
