# Dynamic initializer (??__E) of a file-scope registered object (vptr, FNV hash, intrusive list next,
# uint32 value) that links itself into a global list head and registers an atexit dtor.
# Same as cheat_flag_register_atexit but with a 32-bit trailing member.
PATTERN = 'push N ; push A ; push A ; call EXT ; mov dword ptr [A], eax ; mov eax, dword ptr [A] ; push A ; mov dword ptr [A], eax ; mov dword ptr [A], A ; mov dword ptr [A], A ; mov dword ptr [A], A ; call EXT ; add esp, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """unsigned int FNVHash(const char* s, unsigned int basis, int flag);
struct B { virtual ~B(); unsigned hash; B* next;
  B(const char* s, unsigned basis, int f, B*& head) : hash(FNVHash(s, basis, f)), next(head) { head = this; } };
struct F : B { unsigned v; F(const char* s, unsigned basis, int f, B*& head, unsigned b) : B(s, basis, f, head), v(b) {} virtual ~F(); };
"""
def g(a): return "g_%08x" % a
def emit(va, A, N):
    basis, s, d0, head, val = A[0], A[1], A[2], A[3], A[-1]
    flag = N[0]
    gn = g(d0 - 4)
    src = ("extern const char s_%08x[];\nextern B* h_%08x;\nF %s(s_%08x, 0x%X, %d, h_%08x, 0x%Xu);"
           % (s, head, gn, s, basis, flag, head, val))
    return src, "??__E%s@@YAXXZ" % gn
