# bool getter: return *(int*)(this+off) == 0  (xor eax,eax; cmp [ecx+off],eax; sete al)
PATTERN = 'xor eax, eax ; cmp dword ptr [ecx + N], eax ; sete al ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    off = N[0]
    src = "bool __fastcall FUN_%08x(void* p) { return *(int*)((char*)p + %d) == 0; }" % (va, off)
    return src, "?FUN_%08x@@YI_NPAX@Z" % va
