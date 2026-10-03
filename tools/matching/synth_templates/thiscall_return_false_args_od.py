# /Od thiscall member taking k int args and returning false (bool): spill ecx, xor al,al, ret 4*k.
PATTERN = 'push ebp ; mov ebp, esp ; push ecx ; mov dword ptr [ebp - N], ecx ; xor al, al ; mov esp, ebp ; pop ebp ; ret N'
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    k = N[-1] // 4
    params = ", ".join("int a%d" % i for i in range(k))
    return ("struct C_%08x { bool f(%s); };\nbool C_%08x::f(%s) { return false; }" % (va, params, va, params),
            "?f@C_%08x@@QAE_N%s@Z" % (va, "H" * k if k else "XZ"[:1]) if k else "?f@C_%08x@@QAE_NXZ" % va)
