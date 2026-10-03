# /Od module: member returning this+N (address of embedded member). push ebp; spill ecx; add eax,N
PATTERN = 'push ebp ; mov ebp, esp ; push ecx ; mov dword ptr [ebp - N], ecx ; mov eax, dword ptr [ebp - N] ; add eax, N ; mov esp, ebp ; pop ebp ; ret '
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    off = N[-1]
    return ("struct S_%08x { char pad[%d]; char m; void* f(); };\nvoid* S_%08x::f() { return &m; }" % (va, off, va),
            "?f@S_%08x@@QAEPAXXZ" % va)
