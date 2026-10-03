# Runtime initializer of a 12-byte ResourceKey-like global {instance=imm, type=0, group=0}:
#   xor eax,eax; mov [g],imm; mov [g+4],eax; mov [g+8],eax; ret
# The original is likely a compiler-generated dynamic initializer (??__E...), but MSVC /O2
# folds every constructor spelling tried into static data. A plain __cdecl function doing the
# three stores (in operand order) yields the same bytes. Globals are extern declarations
# (relocations are masked) so instances sharing an address never redefine anything.
PATTERN = "xor eax, eax ; mov dword ptr [A], A ; mov dword ptr [A], eax ; mov dword ptr [A], eax ; ret "
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def g(a): return "g_%08x" % a

def emit(va, A, N):
    if len(A) == 4:
        a0, imm, a1, a2 = A
    else:
        (a0, a1, a2), imm = A, N[0]
    decls = "".join("extern unsigned int %s;\n" % g(a) for a in (a0, a1, a2))
    src = ("%svoid FUN_%08x() { %s = 0x%X; %s = 0; %s = 0; }"
           % (decls, va, g(a0), imm, g(a1), g(a2)))
    return src, "?FUN_%08x@@YAXXZ" % va
