# Dynamic initializer (??__E) of a file-scope registered flag object (vptr, FNV hash, intrusive
# list next, bool) that links itself into a global list head and registers an atexit dtor.
# Source shape: base B(name) inline ctor registers into list; derived F adds bool and its own vptr
# (runtime vptr store survives only via the derived class); /O2.
PATTERN = 'push N ; push A ; push A ; call EXT ; mov dword ptr [A], eax ; mov eax, dword ptr [A] ; push A ; mov dword ptr [A], eax ; mov dword ptr [A], A ; mov dword ptr [A], A ; mov byte ptr [A], N ; call EXT ; add esp, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """unsigned int FNVHash(const char* s, unsigned int basis, int flag);
struct B { virtual ~B(); unsigned hash; B* next;
  B(const char* s, unsigned basis, int f, B*& head) : hash(FNVHash(s, basis, f)), next(head) { head = this; } };
struct F : B { bool v; F(const char* s, unsigned basis, int f, B*& head, bool b) : B(s, basis, f, head), v(b) {} virtual ~F(); };
"""
def g(a): return "g_%08x" % a
def emit(va, A, N):
    basis, s, d0, head = A[0], A[1], A[2], A[3]
    flag, val = N[0], N[1]
    gn = g(d0 - 4)
    src = ("extern const char s_%08x[];\nextern B* h_%08x;\nF %s(s_%08x, 0x%X, %d, h_%08x, %s);"
           % (s, head, gn, s, basis, flag, head, "true" if val else "false"))
    return src, "??__E%s@@YAXXZ" % gn
