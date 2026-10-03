# Trivial getter: "mov eax, imm32 ; ret" where imm32 < 0x400000 (small constant, e.g. a count,
# size or enum value). /O2 leaf function returning a constant; never relocated.
PATTERN = "mov eax, N ; ret "
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    return "unsigned int FUN_%08x() { return 0x%xu; }" % (va, N[0]), "?FUN_%08x@@YAIXZ" % va
