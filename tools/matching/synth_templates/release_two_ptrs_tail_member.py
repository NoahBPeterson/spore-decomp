# Release two owned interface pointers (virtual call, null first), then tail-call a member subobject method.
PATTERN = 'push esi ; mov esi, ecx ; mov ecx, dword ptr [esi + N] ; test ecx, ecx ; je +N ; mov dword ptr [esi + N], N ; mov eax, dword ptr [ecx] ; mov edx, dword ptr [eax + N] ; call edx ; mov ecx, dword ptr [esi + N] ; test ecx, ecx ; je +N ; mov dword ptr [esi + N], N ; mov eax, dword ptr [ecx] ; mov edx, dword ptr [eax + N] ; call edx ; lea ecx, [esi + N] ; pop esi ; jmp EXT'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    o1, _, _, v1, o2, _, _, v2, y = N[:9]
    name = "FUN_%08x" % va
    src = """struct Sub%08x { void m(); };
struct T%08x { void f(); };
void T%08x::f() {
    char* t = (char*)this;
    void*& a = *(void**)(t + 0x%x);
    if (a) { void* p = a; a = 0; ((void (__thiscall *)(void*))(*(void***)p)[0x%x/4])(p); }
    void*& b = *(void**)(t + 0x%x);
    if (b) { void* p = b; b = 0; ((void (__thiscall *)(void*))(*(void***)p)[0x%x/4])(p); }
    ((Sub%08x*)(t + 0x%x))->m();
}
""" % (va, va, va, o1, v1, o2, v2, va, y)
    return src, "?f@T%08x@@QAEXXZ" % va
