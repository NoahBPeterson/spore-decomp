# thiscall Cast(type): return type == K ? this : 0
PATTERN = "xor eax, eax ; cmp dword ptr [esp + N], A ; setne al ; dec eax ; and eax, ecx ; ret N"
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    k = A[0] if A else N[1]
    return ("struct C_%08x { void* F(unsigned t) { return t == 0x%xu ? this : 0; } };\n"
            "void* (C_%08x::*p_%08x)(unsigned) = &C_%08x::F;" % (va, k & 0xffffffff, va, va, va)), "?F@C_%08x@@QAEPAXI@Z" % va
