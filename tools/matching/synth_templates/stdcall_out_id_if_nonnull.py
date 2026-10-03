# "if (out && arg2) *out = ID; return 1;" -- /O2 __stdcall (ret 8) leaf with two stack args.
# Typical shape: a GetID-style callback writing a hash constant through an out pointer.
PATTERN = "mov eax, dword ptr [esp + N] ; test eax, eax ; je +N ; cmp dword ptr [esp + N], N ; je +N ; mov dword ptr [eax], A ; mov eax, N ; ret N"
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    v = A[0] if A else N[3]
    src = ("int __stdcall FUN_%08x(unsigned int* out, int arg) {\n"
           "    if (out && arg) *out = 0x%08xu;\n    return 1;\n}") % (va, v)
    return src, "?FUN_%08x@@YGHPAIH@Z" % va
