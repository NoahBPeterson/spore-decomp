# UNSOLVED (0 byte-exact). Funclets: placement delete (ptr at [ebp-A]) then dtor of a local at [ebp-B], then __ehhandler.
# Best shape so far: temp P(new(...)T) passed to a call gives delete-then-dtor funclet order, but the compiler puts the
# alloc slot at [ebp-0x10] and the object at [ebp-0x14]; the original shares the slot (A==B in 5/11 instances).
PATTERN = 'push N ; push N ; push N ; push N ; push A ; mov eax, dword ptr [ebp - N] ; push eax ; call EXT ; add esp, N ; ret  ; lea ecx, [ebp - N] ; jmp EXT ; mov eax, A ; jmp EXT'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GS-"]
PRELUDE = ("typedef unsigned int size_t;\n"
           "void* operator new(size_t, const char*, int, unsigned, const char*, int);\n"
           "void operator delete(void*, const char*, int, unsigned, const char*, int);\n")

def emit(va, A, N):
    t = "T_%08x" % va
    src = ("extern const char s_%08x[];\n"
           "struct %s { %s(); int d; };\n"
           "struct P_%08x { %s* p; P_%08x(%s* q) : p(q) {} ~P_%08x(); };\n"
           "void eh_use(const P_%08x&);\n"
           "void F_%08x() { eh_use(P_%08x(new(s_%08x, 0, 0u, (const char*)0, 0) %s)); }"
           % (A[0], t, t, va, t, va, t, va, va, va, va, A[0], t))
    return src, "__unwindfunclet$?F_%08x@@YAXXZ$0" % va
