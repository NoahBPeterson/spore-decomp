# bool getter: return *(int*)(this+off) == imm   (xor eax,eax; cmp [ecx+off],imm; sete al)
PATTERN = "xor eax, eax ; cmp dword ptr [ecx + N], N ; sete al ; ret "
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    off, imm = N[0], N[1]
    src = "bool __fastcall FUN_%08x(void* p) { return *(int*)((char*)p + %d) == %d; }" % (va, off, imm)
    return src, "?FUN_%08x@@YI_NPAX@Z" % va
