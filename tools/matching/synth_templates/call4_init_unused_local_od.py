# Dynamic initializer of a file-scope 32-bit global in an unoptimized (/Od /Ob1) module, assigned the
# result of an external 4-arg cdecl call (typically the out-of-line bitfield ID packer FUN_004018a0):
#   push ebp; mov ebp,esp; push ecx; push d; push c; push b; push a; call f; add esp,16;
#   mov [g],eax; mov esp,ebp; pop ebp; ret
# The `push ecx` is a 4-byte stack slot that is reserved but never touched. It comes from an inline
# (/Ob1-expanded) wrapper whose unused local stays in the caller frame. A plain `g = f(a,b,c,d)`
# gives no slot, and a struct-by-value return stores through [ebp-4].
PATTERN = 'push ebp ; mov ebp, esp ; push ecx ; push N ; push N ; push N ; push N ; call EXT ; add esp, N ; mov dword ptr [A], eax ; mov esp, ebp ; pop ebp ; ret '
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """unsigned ext_call4(unsigned, unsigned, unsigned, unsigned);
inline unsigned call4_wrap(unsigned a, unsigned b, unsigned c, unsigned d) { unsigned unused; return ext_call4(a, b, c, d); }
"""
def emit(va, A, N):
    if len(N) != 5 or N[4] != 0x10:
        return "// unsupported variant", "?FUN_%08x@@YAXXZ" % va
    d, c, b, a = N[:4]
    return ("unsigned g_%08x = call4_wrap(0x%x, 0x%x, 0x%x, 0x%x);" % (A[0], a, b, c, d),
            "??__Eg_%08x@@YAXXZ" % A[0])
