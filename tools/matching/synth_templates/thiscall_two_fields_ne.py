# __thiscall bool: return field_a != field_b (mov eax,[ecx+a]; xor edx,edx; cmp eax,[ecx+b]; setne dl; mov al,dl)
PATTERN = 'mov eax, dword ptr [ecx + N] ; xor edx, edx ; cmp eax, dword ptr [ecx + N] ; setne dl ; mov al, dl ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    a, b = N[0], N[1]
    c = "C_%08x" % va
    src = ("struct %s { bool Ne(); };\n"
           "bool %s::Ne() { return *(int*)((char*)this + %d) != *(int*)((char*)this + %d); }" % (c, c, a, b))
    return src, "?Ne@%s@@QAE_NXZ" % c
