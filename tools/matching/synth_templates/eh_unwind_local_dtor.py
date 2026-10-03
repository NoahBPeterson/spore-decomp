# Last C++ EH unwind funclet + __ehhandler of a /GS- function holding a local object with a destructor:
#   __unwindfunclet$f$0: lea ecx,[ebp-N]; jmp ~T     __ehhandler$f: mov eax,__ehfuncinfo$f; jmp ___CxxFrameHandler3
# The EH registration occupies [ebp-0xC..ebp). N%4==0: one 4-aligned local of size N-0xC lands at [ebp-N].
# Odd N: a 1-byte object; byte-sized locals pack downward from the last 4-aligned slot, so uint32 and
# char pad locals fill the space up to [ebp-N+1]. /GS- is required (no cookie check in __ehhandler).
# Shape-equivalent: the parent function body is a stand-in; only the funclet+handler bytes are verified.
PATTERN = 'lea ecx, [ebp - N] ; jmp EXT ; mov eax, A ; jmp EXT'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GS-"]
PRELUDE = "typedef unsigned int uint32_t;\nvoid eh_ext1(void*);\nvoid eh_ext2(void*, void*);\nvoid eh_ext3(void*, void*, void*);\n"
def emit(va, A, N):
    n = N[0]
    if n % 4 == 0:
        src = ("struct S_%08x { uint32_t a[%d]; S_%08x(); ~S_%08x(); };\n"
               "void FUN_%08x() { S_%08x o; eh_ext1(&o); }" % (va, max((n - 0xC) // 4, 1), va, va, va, va))
    else:
        top = n & ~3
        words, chars = (top - 0xC) // 4, n - top - 1
        decl = ("uint32_t p[%d]; " % words if words else "") + ("char q[%d]; " % chars if chars else "")
        args = ", ".join(["&o"] + (["p"] if words else []) + (["q"] if chars else []))
        src = ("struct S_%08x { char a; S_%08x(); ~S_%08x(); };\n"
               "void FUN_%08x() { %sS_%08x o; eh_ext%d(%s); }" % (va, va, va, va, decl, va, args.count(",") + 1, args))
    return src, "__unwindfunclet$?FUN_%08x@@YAXXZ$0" % va
