# Havok-style reflection registration thunk: thiscall on a global object with 10 stack args:
#   f(name, 0, size, 0, 0, &members, nmembers, &enums, nenums, 0); ecx = &global
PATTERN = 'push N ; push N ; push A ; push N ; push A ; push N ; push N ; push N ; push N ; push A ; mov ecx, A ; call EXT ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = '''struct Reg { void __thiscall f(const char*, int, int, int, int, const void*, int, const void*, int, int); };
'''
import os, sys
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
def _str(va):
    import synth
    pe = synth.pe
    off = pe.get_offset_from_rva(va - pe.OPTIONAL_HEADER.ImageBase) if va > 0x10000000 and va - pe.OPTIONAL_HEADER.ImageBase > 0 and False else None
    data = pe.get_data(va - pe.OPTIONAL_HEADER.ImageBase, 128)
    return data.split(b"\0")[0].decode("latin1")
def emit(va, A, N):
    a2, a1, name, g = A[0], A[1], A[2], A[3]
    n_enum, n_mem, size = N[1], N[2], N[5]
    s = _str(name).replace("\\", "\\\\").replace('"', '\\"')
    src = ("extern char g_%08x[]; extern char m_%08x[]; extern char e_%08x[];\n"
           "void FUN_%08x() { ((Reg*)g_%08x)->f(\"%s\", 0, %d, 0, 0, m_%08x, %d, e_%08x, %d, 0); }"
           % (g, a1, a2, va, g, s, size, a1, n_mem, a2, n_enum))
    return src, "?FUN_%08x@@YAXXZ" % va
