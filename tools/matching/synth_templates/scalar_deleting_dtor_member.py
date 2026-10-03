# Scalar deleting destructor: sets vptr, destroys member at +N (out-of-line dtor), class operator delete.
PATTERN = 'push esi ; mov esi, ecx ; lea ecx, [esi + N] ; mov dword ptr [esi], A ; call EXT ; test byte ptr [esp + N], N ; je +N ; push esi ; call EXT ; add esp, N ; mov eax, esi ; pop esi ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = ""
def emit(va, A, N):
    off = N[0]
    pad = "  unsigned pad[%d];\n" % ((off - 4) // 4) if off > 4 else ""
    s = ("struct M_%(v)08x { ~M_%(v)08x(); };\n"
         "struct C_%(v)08x {\n  virtual ~C_%(v)08x();\n%(pad)s  M_%(v)08x m;\n  static void operator delete(void*);\n  C_%(v)08x();\n};\n"
         "C_%(v)08x::~C_%(v)08x() {}\nC_%(v)08x::C_%(v)08x() {}\n") % dict(v=va, pad=pad)
    return s, "??_GC_%08x@@UAEPAXI@Z" % va
