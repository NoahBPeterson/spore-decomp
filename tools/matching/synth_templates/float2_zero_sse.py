# Zeroing of two file-scope floats (likely a Vector2 global's runtime initializer, e.g.
# Vector2 g(0,0)) in an /arch:SSE module: xorps xmm0,xmm0; movss [a],xmm0; movss [b],xmm0; ret.
# MSVC /O2 folds the constructor form into static data, so a plain __cdecl function doing the
# two stores (operand order) is emitted instead; globals are extern so shared addresses are fine.
PATTERN = 'xorps xmm0, xmm0 ; movss dword ptr [A], xmm0 ; movss dword ptr [A], xmm0 ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/arch:SSE"]
PRELUDE = ""

def emit(va, A, N):
    decls = "".join("extern float g_%08x;\n" % a for a in sorted(set(A)))
    body = " ".join("g_%08x = 0.0f;" % a for a in A)
    return "%svoid FUN_%08x() { %s }" % (decls, va, body), "?FUN_%08x@@YAXXZ" % va
