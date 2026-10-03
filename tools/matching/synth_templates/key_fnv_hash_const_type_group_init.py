# Dynamic initializer (??__E) of a 12-byte ResourceKey global whose instance is a runtime FNV
# hash of a string and whose type/group are non-zero constants:
#   push 1; push 0x811c9dc5; push str; call FNVHash; add esp,0xc; mov [g],eax; mov [g+4],type; mov [g+8],group; ret
# Source shape: `Key g(FNVHash(str, 0x811C9DC5, 1), type, group);` with an inline Key ctor, /O2.
PATTERN = 'push N ; push A ; push A ; call EXT ; add esp, N ; mov dword ptr [A], eax ; mov dword ptr [A], A ; mov dword ptr [A], A ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """unsigned int FNVHash(const char* s, unsigned int basis, int flag);
struct Key {
    unsigned int instance, type, group;
    Key(unsigned int i, unsigned int t = 0, unsigned int g = 0) : instance(i), type(t), group(g) {}
};
"""

def g(a): return "g_%08x" % a

def emit(va, A, N):
    basis, s, d0, d1, t, d2, grp = A
    flag = N[0]
    src = ("extern const char s_%08x[];\nKey %s(FNVHash(s_%08x, 0x%X, %d), 0x%X, 0x%X);"
           % (s, g(d0), s, basis, flag, t, grp))
    return src, "??__E%s@@YAXXZ" % g(d0)
