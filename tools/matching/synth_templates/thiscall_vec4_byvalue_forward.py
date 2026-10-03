# thiscall(this=16-byte struct ptr, a*, b*) copies three 16-byte structs by value to a cdecl callee (hidden sret ptr)
PATTERN = 'mov edx, dword ptr [ecx] ; sub esp, N ; sub esp, N ; mov eax, esp ; mov dword ptr [eax], edx ; mov edx, dword ptr [ecx + N] ; mov dword ptr [eax + N], edx ; mov edx, dword ptr [ecx + N] ; mov dword ptr [eax + N], edx ; mov ecx, dword ptr [ecx + N] ; mov dword ptr [eax + N], ecx ; mov ecx, dword ptr [esp + N] ; mov edx, dword ptr [ecx] ; sub esp, N ; mov eax, esp ; mov dword ptr [eax], edx ; mov edx, dword ptr [ecx + N] ; mov dword ptr [eax + N], edx ; mov edx, dword ptr [ecx + N] ; mov dword ptr [eax + N], edx ; mov ecx, dword ptr [ecx + N] ; mov dword ptr [eax + N], ecx ; mov ecx, dword ptr [esp + N] ; mov edx, dword ptr [ecx] ; sub esp, N ; mov eax, esp ; mov dword ptr [eax], edx ; mov edx, dword ptr [ecx + N] ; mov dword ptr [eax + N], edx ; mov edx, dword ptr [ecx + N] ; mov dword ptr [eax + N], edx ; mov ecx, dword ptr [ecx + N] ; lea edx, [esp + N] ; push edx ; mov dword ptr [eax + N], ecx ; call EXT ; add esp, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "struct Y { unsigned a, b, c, d; Y(const Y& o) : a(o.a), b(o.b), c(o.c), d(o.d) {} };\n"
def emit(va, A, N):
    return (
        "Y __cdecl EXT_%08x(Y, Y, Y);\n"
        "struct T_%08x : Y { void __thiscall M(const Y* a, const Y* b, int c); };\n"
        "void T_%08x::M(const Y* a, const Y* b, int c) { EXT_%08x(*a, *b, *this); }\n" % (va, va, va, va),
        "?M@T_%08x@@QAEXPBUY@@0H@Z" % va)
