# Multiple-inheritance this-adjustor thunk: sub ecx,N ; jmp Derived::f
# MSVC emits [thunk]:D::f`adjustor{N}' (?f@D@@W<N>AEXXZ) in the vtable of a non-primary base B1
# at offset N when D overrides a virtual that both the primary base B0 and B1 declare
# (D::f expects this == B0 subobject). The thunk is emitted with the vtable, which an
# out-of-line constructor forces. B0 is padded so that B1 sits at exactly offset N.
PATTERN = "sub ecx, N ; jmp EXT"
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = ""

def mnum(n):
    if n == 0: return "A@"
    if 1 <= n <= 10: return str(n - 1)
    s = ""
    while n:
        s = "ABCDEFGHIJKLMNOP"[n & 15] + s; n >>= 4
    return s + "@"

def emit(va, A, N):
    n = N[0]
    t = "%08x" % va
    pad = " char pad[%d];" % (n - 4) if n > 4 else ""
    packed = n % 4 != 0
    src = ""
    if packed: src += "#pragma pack(push, 1)\n"
    src += ("struct B0_%s { virtual void f();%s };\n"
            "struct B1_%s { virtual void f(); };\n"
            "struct D_%s : B0_%s, B1_%s { void f(); D_%s(); };\n" % (t, pad, t, t, t, t, t))
    if packed: src += "#pragma pack(pop)\n"
    src += "D_%s::D_%s() {}" % (t, t)
    return src, "?f@D_%s@@W%sAEXXZ" % (t, mnum(n))
