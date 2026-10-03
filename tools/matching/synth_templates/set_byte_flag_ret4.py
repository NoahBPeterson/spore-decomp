# thiscall member with ignored stack args (ret 4/8) that stores a byte constant at [this+off]
PATTERN = 'mov byte ptr [ecx + N], N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    off, val, ret = N[0], N[1], N[2]
    n = ret // 4
    params = ",".join("int" for _ in range(n))
    src = ("struct S_%08x { char pad[%d]; char f; void m(%s); };\n"
           "void S_%08x::m(%s) { f = %d; }" % (va, off, params, va, params, val))
    return src, "?m@S_%08x@@QAEX%s@Z" % (va, "H" * n)
