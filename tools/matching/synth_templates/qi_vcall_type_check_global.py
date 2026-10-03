# "if (m_p && m_p->vN(ID, &t) && t->type == K) return *Getter(); return 0;" -- thiscall member with a
# member interface pointer queried through a virtual (id, out**) call, then a 16-bit type check.
PATTERN = 'push ecx ; mov ecx, dword ptr [ecx + N] ; push esi ; xor esi, esi ; test ecx, ecx ; je +N ; mov eax, dword ptr [ecx] ; mov eax, dword ptr [eax + N] ; lea edx, [esp + N] ; push edx ; push A ; call eax ; test al, al ; je +N ; mov ecx, dword ptr [esp + N] ; cmp word ptr [ecx + N], N ; jne +N ; call EXT ; mov eax, dword ptr [eax] ; pop esi ; pop ecx ; ret  ; mov eax, esi ; pop esi ; pop ecx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ("struct Rec { unsigned short pad[9]; unsigned short type; };\n"
           "struct QObj {\n" +
           "".join("    virtual bool q%d(unsigned int id, Rec** out) = 0;\n" % i for i in range(64)) +
           "};\n"
           "unsigned int* GetterX();\n")
def emit(va, A, N):
    src = ("struct H_%08x { unsigned int pad[%d]; QObj* p;\n"
           "    unsigned int f();\n};\n"
           "unsigned int H_%08x::f() {\n"
           "    unsigned int r0 = 0; Rec* r; QObj* o = p;\n"
           "    if (o && o->q%d(0x%08xu, &r) && r->type == %d) r0 = *GetterX();\n"
           "    return r0;\n}") % (va, N[0] // 4, va, N[1] // 4, A[0], N[5])
    return src, "?f@H_%08x@@QAEIXZ" % va
