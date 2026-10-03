# Od vector dtor: if (b) { n = (e-b)/sz*sz; T* q=b; if (((int*)q)[-1]) { T* r=q; dealloc(r);} }
PATTERN = 'push ebp ; mov ebp, esp ; sub esp, N ; mov dword ptr [ebp - N], ecx ; mov eax, dword ptr [ebp - N] ; cmp dword ptr [eax], N ; je +N ; mov ecx, dword ptr [ebp - N] ; mov edx, dword ptr [ebp - N] ; mov eax, dword ptr [ecx + N] ; sub eax, dword ptr [edx] ; cdq  ; mov ecx, N ; idiv ecx ; imul eax, eax, N ; mov dword ptr [ebp - N], eax ; mov edx, dword ptr [ebp - N] ; mov eax, dword ptr [edx] ; mov dword ptr [ebp - N], eax ; mov ecx, dword ptr [ebp - N] ; cmp dword ptr [ecx - N], N ; je +N ; mov edx, dword ptr [ebp - N] ; mov dword ptr [ebp - N], edx ; mov eax, dword ptr [ebp - N] ; push eax ; call EXT ; add esp, N ; mov esp, ebp ; pop ebp ; ret '
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = "void EASTL_allocator_deallocate(void* p);\n"
def emit(va, A, N):
    t = "%08x" % va
    sz = N[8]
    src = ("struct T_%(t)s { char c[%(sz)d]; };\n"
           "inline void fa_%(t)s(void* p) { EASTL_allocator_deallocate(p); }\n"
           "inline void dp_%(t)s(T_%(t)s* p, unsigned n) { if (((int*)p)[-1]) { T_%(t)s* q = p; fa_%(t)s(q); } }\n"
           "struct C_%(t)s { T_%(t)s* b; void* x; T_%(t)s* e; void FUN_%(t)s(); };\n"
           "void C_%(t)s::FUN_%(t)s() { if (b) dp_%(t)s(b, (e - b) * sizeof(T_%(t)s)); }") % dict(t=t, sz=sz)
    return src, "?FUN_%s@C_%s@@QAEXXZ" % (t, t)
