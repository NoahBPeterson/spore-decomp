# Red-black tree recursive erase: recurse left, release virtual member, deallocate node, iterate right.
import subprocess
PATTERN = 'push ebx ; push esi ; mov esi, dword ptr [esp + N] ; mov ebx, ecx ; test esi, esi ; je +N ; push edi ; lea ecx, [ecx] ; mov eax, dword ptr [esi] ; push eax ; mov ecx, ebx ; call +N ; mov ecx, dword ptr [esi + N] ; mov edi, dword ptr [esi + N] ; test ecx, ecx ; je +N ; mov edx, dword ptr [ecx] ; mov eax, dword ptr [edx + N] ; call eax ; push esi ; call EXT ; add esp, N ; mov esi, edi ; test edi, edi ; jne +N ; pop edi ; pop esi ; pop ebx ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "void EASTL_allocator_deallocate(void*);\n"
def emit(va, A, N):
    off = N[1]; slot = N[3] // 4
    vf = "".join("virtual void v%d(){}\n    " % i for i in range(slot)) + "virtual void rel(){}"
    src = ("struct Obj%08x { %s };\n"
           "struct Node%08x { Node%08x* l; Node%08x* r; char pad[%d]; Obj%08x* o; };\n"
           "struct Tree%08x { void Erase(Node%08x* n); };\n"
           "void Tree%08x::Erase(Node%08x* n) {\n"
           "  while (n) { Erase(n->l); Obj%08x* o = n->o; Node%08x* r = n->r; if (o) o->rel();\n"
           "    EASTL_allocator_deallocate(n); n = r; }\n}\n") % ((va,vf)+(va,)*3+(off-8,)+(va,)*7)
    return src, "?Erase@Tree%08x@@QAEXPAUNode%08x@@@Z" % (va, va)
