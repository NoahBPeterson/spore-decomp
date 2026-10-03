# Dynamic initializer (??__E) of a file-scope uint32 global set to a runtime FNV hash of a
# string literal, in an unoptimized (/Od /Ob1) module:
#   push ebp; mov ebp,esp; push 1; push 0x811c9dc5; push str; call FNVHash; add esp,0xc;
#   mov [g],eax; pop ebp; ret
# Source shape: `unsigned int g = FNVHash("name", 0x811C9DC5, 1);` at file scope.
PATTERN = 'push ebp ; mov ebp, esp ; push N ; push A ; push A ; call EXT ; add esp, N ; mov dword ptr [A], eax ; pop ebp ; ret '
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "unsigned int FNVHash(const char* s, unsigned int basis, int flag);\n"

def g(a): return "g_%08x" % a

def emit(va, A, N):
    basis, s, d = A
    flag = N[0]
    src = ("extern const char s_%08x[];\nunsigned int %s = FNVHash(s_%08x, 0x%X, %d);"
           % (s, g(d), s, basis, flag))
    return src, "??__E%s@@YAXXZ" % g(d)
