# Derived ctor: out-of-line base ctor call, then store own vptr, return this.
# Source shape: struct B { B(); virtual fb(); }; struct D : B { D(); virtual fb(); }; D::D() {}
PATTERN = 'push esi ; mov esi, ecx ; call EXT ; mov dword ptr [esi], A ; mov eax, esi ; pop esi ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = ""
def emit(va, A, N):
    c = "C_%08x" % va
    src = ("struct B_%s { B_%s(); virtual void fb(); };\n"
           "struct %s : B_%s { %s(); virtual void fb(); };\n"
           "%s::%s() {}\n") % (c, c, c, c, c, c, c)
    return src, "??0%s@@QAE@XZ" % c
