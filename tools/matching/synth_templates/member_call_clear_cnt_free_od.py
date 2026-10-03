# Od: this->Callee(p, n); this->c = 0; if (n > 1) { q = p; dealloc(q); } with inlined locals
PATTERN = 'push ebp ; mov ebp, esp ; sub esp, N ; mov dword ptr [ebp - N], ecx ; mov eax, dword ptr [ebp - N] ; mov ecx, dword ptr [eax + N] ; push ecx ; mov edx, dword ptr [ebp - N] ; mov eax, dword ptr [edx + N] ; push eax ; mov ecx, dword ptr [ebp - N] ; call EXT ; mov ecx, dword ptr [ebp - N] ; mov dword ptr [ecx + N], N ; mov edx, dword ptr [ebp - N] ; mov eax, dword ptr [edx + N] ; mov dword ptr [ebp - N], eax ; mov ecx, dword ptr [ebp - N] ; mov edx, dword ptr [ecx + N] ; mov dword ptr [ebp - N], edx ; cmp dword ptr [ebp - N], N ; jbe +N ; mov eax, dword ptr [ebp - N] ; mov dword ptr [ebp - N], eax ; mov ecx, dword ptr [ebp - N] ; push ecx ; call EXT ; add esp, N ; mov esp, ebp ; pop ebp ; ret '
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = "void EASTL_allocator_deallocate(void* p);\n"
def emit(va, A, N):
    t = "%08x" % va
    src = ("struct C_%(t)s;\n"
           "void Callee_%(t)s(C_%(t)s* self, void* p, unsigned n);\n"
           "struct C_%(t)s { int pad0; void* p; unsigned n; int c; void Callee(void* p, unsigned n); void FUN_%(t)s(); };\n"
           "inline void fr_%(t)s(void* p, unsigned n) { if (n > 1) { void* q = p; EASTL_allocator_deallocate(q); } }\n"
           "void C_%(t)s::FUN_%(t)s() { Callee(p, n); c = 0; fr_%(t)s(p, n); }") % dict(t=t)
    src = src.replace("void Callee_%s(C_%s* self, void* p, unsigned n);\n" % (t, t), "")
    src = src.replace("void Callee(void* p, unsigned n);", "void __thiscall Callee(void* p, unsigned n);")
    src = src.replace("Callee(", "Callee_%s(" % t)
    return src, "?FUN_%s@C_%s@@QAEXXZ" % (t, t)
