# /Od: if (*pp) { t = uninit_u; t = *pp; return t->vN(imm); } else 0.  Local names matter (MSVC /Od frame order follows symbol hash).
PATTERN = 'push ebp ; mov ebp, esp ; sub esp, N ; mov eax, dword ptr [ebp + N] ; mov ecx, dword ptr [eax] ; mov dword ptr [ebp - N], ecx ; cmp dword ptr [ebp - N], N ; je +N ; mov edx, dword ptr [ebp - N] ; mov dword ptr [ebp - N], edx ; mov eax, dword ptr [ebp + N] ; mov ecx, dword ptr [eax] ; mov dword ptr [ebp - N], ecx ; push A ; mov edx, dword ptr [ebp - N] ; mov eax, dword ptr [edx] ; mov ecx, dword ptr [ebp - N] ; mov edx, dword ptr [eax + N] ; call edx ; mov dword ptr [ebp - N], eax ; jmp +N ; mov dword ptr [ebp - N], N ; mov eax, dword ptr [ebp - N] ; mov esp, ebp ; pop ebp ; ret '
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ("struct IObjV {\n" +
           "".join("    virtual void* v%d(unsigned id);\n" % i for i in range(64)) + "};\n")
def emit(va, A, N):
    disp = N[11]
    slot = disp // 4
    src = ("void* FUN_%08x(IObjV** pp) {\n"
           "    IObjV* a; IObjV* b; IObjV* c; void* e;\n"
           "    a = *pp;\n"
           "    if (a) { c = b; c = *pp; e = c->v%d(0x%xu); } else e = 0;\n"
           "    return e;\n}") % (va, slot, A[0])
    return src, "?FUN_%08x@@YAPAXPAPAUIObjV@@@Z" % va
