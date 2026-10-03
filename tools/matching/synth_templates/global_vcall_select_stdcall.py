# if (g1) { if (a3) g2->vt[X](g2,a1,g1,a2) else g2->vt[Y](g2,a1,g1,a2) } -- /O2 cdecl 3-arg function,
# stdcall vtable slots with explicit this pushed.
PATTERN = 'mov eax, dword ptr [A] ; test eax, eax ; je +N ; cmp dword ptr [esp + N], N ; mov ecx, dword ptr [A] ; mov edx, dword ptr [ecx] ; push esi ; mov esi, dword ptr [esp + N] ; push esi ; push eax ; mov eax, dword ptr [esp + N] ; push eax ; push ecx ; je +N ; mov ecx, dword ptr [edx + N] ; call ecx ; pop esi ; ret  ; mov ecx, dword ptr [edx + N] ; call ecx ; pop esi ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ("struct SO;\ntypedef void (__stdcall *SFn)(SO*, void*, void*, void*);\n"
           "struct SO { SFn* vt; };\n")
def emit(va, A, N):
    g1, g2 = "g_%08x" % A[0], "g_%08x" % A[1]
    x, y = N[-2] // 4, N[-1] // 4
    src = ("extern void* %s;\nextern SO* %s;\nvoid FUN_%08x(void* a, void* b, int c) {\n"
           "    if (%s) {\n        if (c) %s->vt[%d](%s, a, %s, b);\n        else %s->vt[%d](%s, a, %s, b);\n    }\n}"
           ) % (g1, g2, va, g1, g2, x, g2, g1, g2, y, g2, g1)
    return src, "?FUN_%08x@@YAXPAX0H@Z" % va
