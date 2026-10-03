# /Od thiscall member returning a constant: ecx spilled to [ebp-4], mov eax,N.
PATTERN = 'push ebp ; mov ebp, esp ; push ecx ; mov dword ptr [ebp - N], ecx ; mov eax, N ; mov esp, ebp ; pop ebp ; ret '
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    v = N[-1]
    return ("struct C_%08x { int f(); };\nint C_%08x::f() { return %d; }" % (va, va, v),
            "?f@C_%08x@@QAEHXZ" % va)
