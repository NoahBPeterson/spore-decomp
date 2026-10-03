# Dynamic initializer (??__E) of a file-scope 12-byte ResourceKey global whose instance is a
# runtime FNV hash of a string and type/group are 0:
#   push 1; push 0x811c9dc5; push str; call FNVHash; mov [g],eax; xor eax,eax; add esp,0xc;
#   mov [g+4],eax; mov [g+8],eax; ret
# Source shape: `Key g = Key(FNVHash(str, 0x811C9DC5, 1));` with an inline Key ctor, /O2.
PATTERN = 'push N ; push A ; push A ; call EXT ; mov dword ptr [A], eax ; xor eax, eax ; add esp, N ; mov dword ptr [A], eax ; mov dword ptr [A], eax ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """unsigned int FNVHash(const char* s, unsigned int basis, int flag);
struct Key {
    unsigned int instance, type, group;
    Key(unsigned int i, unsigned int t = 0, unsigned int g = 0) : instance(i), type(t), group(g) {}
};
"""

def g(a): return "g_%08x" % a

def emit(va, A, N):
    basis, s, d0, d1, d2 = A
    flag = N[0]
    if (d1, d2) == (d0 + 4, d0 + 8):
        src = ("extern const char s_%08x[];\nKey %s(FNVHash(s_%08x, 0x%X, %d));"
               % (s, g(d0), s, basis, flag))
        return src, "??__E%s@@YAXXZ" % g(d0)
    decls = "".join("extern unsigned int %s;\n" % g(a) for a in (d0, d1, d2))
    src = ("extern const char s_%08x[];\n%svoid FUN_%08x() { %s = FNVHash(s_%08x, 0x%X, %d); %s = 0; %s = 0; }"
           % (s, decls, va, g(d0), s, basis, flag, g(d1), g(d2)))
    return src, "?FUN_%08x@@YAXXZ" % va
