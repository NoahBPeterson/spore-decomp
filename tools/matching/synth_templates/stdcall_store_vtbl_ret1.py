PATTERN = 'mov eax, dword ptr [esp + N] ; test eax, eax ; je +N ; mov dword ptr [eax], A ; mov eax, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    src = ("int __stdcall FUN_%08x(unsigned int* p, int) {\n"
           "  if (p) *p = 0x%x;\n  return 1;\n}\n") % (va, A[0])
    return src, "?FUN_%08x@@YGHPAIH@Z" % va
