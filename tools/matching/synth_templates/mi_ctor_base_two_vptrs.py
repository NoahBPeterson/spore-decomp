# Multiple-inheritance ctor: out-of-line primary base ctor, then store two vptrs (offset 0 and 4).
# Source shape: struct D : B, X { D(); virtual f; }; D::D() {} with B polymorphic w/ external ctor.
PATTERN = 'push esi ; mov esi, ecx ; call EXT ; mov dword ptr [esi], A ; mov dword ptr [esi + N], A ; mov eax, esi ; pop esi ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = ""
def emit(va, A, N):
    c = "C_%08x" % va
    src = ("struct B_%s { B_%s(); virtual void fb(); };\n"
           "struct __declspec(novtable) X_%s { virtual void fx(); };\n"
           "struct %s : B_%s, X_%s { %s(); virtual void fb(); virtual void fx(); };\n"
           "%s::%s() {}\n") % (c, c, c, c, c, c, c, c, c)
    return src, "??0%s@@QAE@XZ" % c
