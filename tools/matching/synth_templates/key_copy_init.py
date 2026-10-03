# Dynamic initializer of a file-scope 12-byte ResourceKey-like global copied from another
# (extern, defined elsewhere) key: three loads into eax/ecx/edx, three stores, ret.
# Source shape: `extern Key src; Key dst = src;` with the implicit copy ctor, /O2.
PATTERN = 'mov eax, dword ptr [A] ; mov ecx, dword ptr [A] ; mov edx, dword ptr [A] ; mov dword ptr [A], eax ; mov dword ptr [A], ecx ; mov dword ptr [A], edx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """struct Key { unsigned int instance, type, group; };
"""
def emit(va, A, N):
    s0, s1, s2, d0, d1, d2 = A
    if (s1, s2, d1, d2) == (s0 + 4, s0 + 8, d0 + 4, d0 + 8):
        return ("extern Key g_%08x;\nKey g_%08x = g_%08x;" % (s0, d0, s0),
                "??__Eg_%08x@@YAXXZ" % d0)
    decls = "".join("extern unsigned int g_%08x;\n" % a for a in A)
    src = decls + "void FUN_%08x() {\n" % va
    src += "".join("    g_%08x = g_%08x;\n" % (d, s) for s, d in zip(A[:3], A[3:]))
    src += "}"
    return src, "?FUN_%08x@@YAXXZ" % va
