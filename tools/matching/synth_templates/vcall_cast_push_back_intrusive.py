# void f(Owner* o, Src* s): r = s ? (RefObj*)s->Cast(ID) : 0; (AddRef r); o->vec.push_back(r) (AddRef again);
# Release r.  /O2 cdecl, no /EHsc (no EH frame; raw refcount calls inline). vec begin/end/cap at +4/+8/+0xc,
# slow path is an external __thiscall Vec::ins(end, &t) (callee pops 8). Two locals (r in esi, t in the stack slot) are
# required so the fast path keeps using the register copy.
PATTERN = "mov ecx, dword ptr [esp + N] ; push esi ; test ecx, ecx ; je +N ; mov eax, dword ptr [ecx] ; mov edx, dword ptr [eax + N] ; push A ; call edx ; mov esi, eax ; jmp +N ; xor esi, esi ; mov dword ptr [esp + N], esi ; test esi, esi ; je +N ; mov eax, dword ptr [esi] ; mov edx, dword ptr [eax] ; mov ecx, esi ; call edx ; mov ecx, dword ptr [esp + N] ; mov eax, dword ptr [ecx + N] ; add ecx, N ; cmp eax, dword ptr [ecx + N] ; jae +N ; lea edx, [eax + N] ; mov dword ptr [ecx + N], edx ; test eax, eax ; je +N ; mov dword ptr [eax], esi ; test esi, esi ; je +N ; mov eax, dword ptr [esi] ; mov edx, dword ptr [eax] ; mov ecx, esi ; call edx ; jmp +N ; lea edx, [esp + N] ; push edx ; push eax ; call EXT ; mov esi, dword ptr [esp + N] ; test esi, esi ; je +N ; mov eax, dword ptr [esi] ; mov edx, dword ptr [eax + N] ; mov ecx, esi ; pop esi ; jmp edx ; pop esi ; ret "
FLAGS = ["/O2", "/MD", "/Gy", "/TP"]
PRELUDE = ("struct Src {\n" +
           "".join("    virtual void* v%d(unsigned int id) = 0;\n" % i for i in range(64)) +
           "};\n"
           "struct RefObj { virtual void AddRef() = 0; virtual void Release() = 0; };\n"
           "struct Vec { RefObj** b; RefObj** e; RefObj** c; void ins(RefObj** pos, RefObj** v); };\n"
           "struct Owner { int pad; Vec v; };\n")
def emit(va, A, N):
    idx = N[1] // 4
    src = ("void FUN_%08x(Owner* o, Src* s) {\n"
           "    RefObj* r = (RefObj*)(s ? s->v%d(0x%08xu) : 0);\n"
           "    RefObj* t = r;\n"
           "    if (r) r->AddRef();\n"
           "    Vec* v = &o->v;\n"
           "    if (v->e < v->c) { RefObj** d = v->e++; if (d) { *d = r; if (r) r->AddRef(); } }\n"
           "    else { v->ins(v->e, &t); r = t; }\n"
           "    if (r) r->Release();\n}") % (va, idx, A[0])
    return src, "?FUN_%08x@@YAXPAUOwner@@PAUSrc@@@Z" % va
