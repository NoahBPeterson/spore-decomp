# "if (g) (*(fn*)(vtbl+N))(g);" -- /O2 free function: null-check a global object pointer, call a vtable slot
# as __stdcall with the object pointer pushed as an explicit arg (e.g. Release slot 2).
PATTERN = "mov eax, dword ptr [A] ; test eax, eax ; je +N ; mov ecx, dword ptr [eax] ; mov edx, dword ptr [ecx + N] ; push eax ; call edx ; ret "
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "typedef void (__stdcall *VFn)(void*);\n"
def emit(va, A, N):
    g = "g_%08x" % A[0]
    src = ("extern void** %s;\nvoid FUN_%08x() {\n    if (%s) ((VFn)(*(void***)%s)[%d])(%s);\n}") % (g, va, g, g, N[0] // 4, g)
    return src, "?FUN_%08x@@YAXXZ" % va
