# Thiscall member (hidden-ret style): copies this-> and two pointed 16-byte structs by value
# (user copy ctor, per-field) and calls a cdecl callee(ret, a, b, *this); returns ret. 4th stack arg unused.
PATTERN = 'mov edx, dword ptr [ecx] ; push esi ; sub esp, N ; mov eax, esp ; mov dword ptr [eax], edx ; mov edx, dword ptr [ecx + N] ; mov dword ptr [eax + N], edx ; mov edx, dword ptr [ecx + N] ; mov dword ptr [eax + N], edx ; mov ecx, dword ptr [ecx + N] ; mov dword ptr [eax + N], ecx ; mov ecx, dword ptr [esp + N] ; mov edx, dword ptr [ecx] ; mov esi, dword ptr [esp + N] ; sub esp, N ; mov eax, esp ; mov dword ptr [eax], edx ; mov edx, dword ptr [ecx + N] ; mov dword ptr [eax + N], edx ; mov edx, dword ptr [ecx + N] ; mov dword ptr [eax + N], edx ; mov ecx, dword ptr [ecx + N] ; mov dword ptr [eax + N], ecx ; mov ecx, dword ptr [esp + N] ; mov edx, dword ptr [ecx] ; sub esp, N ; mov eax, esp ; mov dword ptr [eax], edx ; mov edx, dword ptr [ecx + N] ; mov dword ptr [eax + N], edx ; mov edx, dword ptr [ecx + N] ; mov dword ptr [eax + N], edx ; mov ecx, dword ptr [ecx + N] ; push esi ; mov dword ptr [eax + N], ecx ; call EXT ; add esp, N ; mov eax, esi ; pop esi ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """struct V { unsigned a,b,c,d; V(){} V(const V&o):a(o.a),b(o.b),c(o.c),d(o.d){} };
void __cdecl callee(void* r, V x, V y, V z);
"""
def emit(va, A, N):
    # members must be declared in class; use a per-instance struct instead
    s = ("struct C_%08x { V v; void* f(void* r, const V* a, const V* b, int u); };\n"
         "void* C_%08x::f(void* r, const V* a, const V* b, int u) { callee(r, *a, *b, v); return r; }" % (va, va))
    return s, "?f@C_%08x@@QAEPAXPAXPBUV@@1H@Z" % va
