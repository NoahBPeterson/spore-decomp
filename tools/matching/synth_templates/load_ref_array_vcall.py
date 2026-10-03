# Load-array-from-object: vec.f(b,e); n=0; obj->vf20()->vf18() -> Count(x,&n,1,0); vec.reserve(n);
# for i<n: p=0; obj->vf28(id,&p,0); vec.push_back(p) (AddRef/Release inline); obj->vf1c().
# /O2 cdecl, no /EHsc.
PATTERN = 'push ecx ; push ebp ; push esi ; mov esi, dword ptr [esp + N] ; mov eax, dword ptr [esi + N] ; mov ecx, dword ptr [esi] ; push edi ; push eax ; push ecx ; mov ecx, esi ; call EXT ; mov edi, dword ptr [esp + N] ; mov edx, dword ptr [edi] ; mov eax, dword ptr [edx + N] ; mov ecx, edi ; mov dword ptr [esp + N], N ; call eax ; mov edx, dword ptr [eax] ; mov ecx, eax ; mov eax, dword ptr [edx + N] ; call eax ; push N ; push N ; lea ecx, [esp + N] ; push ecx ; push eax ; call EXT ; mov edx, dword ptr [esp + N] ; add esp, N ; push edx ; mov ecx, esi ; call EXT ; xor ebp, ebp ; cmp dword ptr [esp + N], ebp ; jbe +N ; lea ebx, [ebx] ; mov eax, dword ptr [edi] ; mov edx, dword ptr [eax + N] ; push N ; lea ecx, [esp + N] ; push ecx ; push A ; mov ecx, edi ; mov dword ptr [esp + N], N ; call edx ; mov eax, dword ptr [esi + N] ; cmp eax, dword ptr [esi + N] ; jae +N ; lea ecx, [eax + N] ; mov dword ptr [esi + N], ecx ; test eax, eax ; je +N ; mov edx, dword ptr [esp + N] ; mov dword ptr [eax], edx ; mov ecx, dword ptr [esp + N] ; test ecx, ecx ; je +N ; mov eax, dword ptr [ecx] ; mov edx, dword ptr [eax] ; call edx ; jmp +N ; lea ecx, [esp + N] ; push ecx ; push eax ; mov ecx, esi ; call EXT ; mov ecx, dword ptr [esp + N] ; test ecx, ecx ; je +N ; mov edx, dword ptr [ecx] ; mov eax, dword ptr [edx + N] ; call eax ; inc ebp ; cmp ebp, dword ptr [esp + N] ; jb +N ; mov edx, dword ptr [edi] ; mov eax, dword ptr [edx + N] ; mov ecx, edi ; call eax ; pop edi ; pop esi ; pop ebp ; pop ecx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/TP"]
PRELUDE = ("struct RefObj { virtual void AddRef() = 0; virtual void Release() = 0; };\n"
           "struct Vec { RefObj** b; RefObj** e; RefObj** c; void f(RefObj** b, RefObj** e); void ins(RefObj** pos, RefObj** v); void rsv(unsigned n); };\n"
           "struct Sub { virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void* v18() = 0; };\n"
           "struct Obj { virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4(); virtual void a5(); virtual void a6(); virtual void v1c() = 0; virtual Sub* v20() = 0; virtual void a9(); virtual void v28(unsigned id, RefObj** out, int z) = 0; };\n"
           "void Count(void* x, unsigned* n, int a, int b);\n")
def emit(va, A, N):
    src = ("void FUN_%08x(Obj* o, Vec* v) {\n"
           "    v->f(v->b, v->e);\n"
           "    unsigned n = 0;\n"
           "    void* x = o->v20()->v18(); Count(x, &n, 1, 0);\n"
           "    v->rsv(n);\n"
           "    for (unsigned i = 0; i < n; ++i) {\n"
           "        RefObj* p = 0;\n"
           "        o->v28(0x%08xu, &p, 0);\n"
           "        if (v->e < v->c) { RefObj** d = v->e++; if (d) { *d = p; if (p) p->AddRef(); } }\n"
           "        else v->ins(v->e, &p);\n"
           "        if (p) p->Release();\n"
           "    }\n"
           "    o->v1c();\n}") % (va, A[0])
    return src, "?FUN_%08x@@YAXPAUObj@@PAUVec@@@Z" % va
