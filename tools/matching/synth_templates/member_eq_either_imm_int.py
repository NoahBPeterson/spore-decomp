# int getter: field == a || field == b ? 1 : 0   (mov eax,[ecx+off]; cmp/je; cmp/je; xor eax,eax; ret; mov eax,1; ret)
PATTERN = 'mov eax, dword ptr [ecx + N] ; cmp eax, N ; je +N ; cmp eax, N ; je +N ; xor eax, eax ; ret  ; mov eax, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    off, a, b = N[0], N[1], N[2]
    src = ("int __fastcall FUN_%08x(void* p) { int v = *(int*)((char*)p + %d); "
           "if (v == %d || v == %d) return 1; return 0; }") % (va, off, a, b)
    return src, "?FUN_%08x@@YIHPAX@Z" % va
