# Derived ctor: out-of-line base ctor call, store own vptr, zero one member at offset N[0].
# Source shape: struct D : B { char pad[off-4]; int m; D(); virtual f; }; D::D() : m(0) {}
PATTERN = 'push esi ; mov esi, ecx ; call EXT ; mov dword ptr [esi], A ; mov dword ptr [esi + N], N ; mov eax, esi ; pop esi ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = ""
def emit(va, A, N):
    c = "C_%08x" % va
    off = N[0]
    pad = ("char pad[%d]; " % (off - 4)) if off > 4 else ""
    src = ("struct B_%s { B_%s(); virtual void fb(); };\n"
           "struct %s : B_%s { %sint m; %s(); virtual void fb(); };\n"
           "%s::%s() : m(0) {}\n") % (c, c, c, c, pad, c, c, c)
    return src, "??0%s@@QAE@XZ" % c
