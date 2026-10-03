# cdecl forwarder: returns a 16-byte struct by value and takes three 16-byte structs by value,
# forwarding all of them to another cdecl function with the same signature:
#   S f(S a, S b, S c) { return g(a, b, c); }   (hidden return ptr in esi, returned in eax)
# S needs a user-defined copy ctor (non-trivial copy -> by-value args are copied member-wise
# with mov eax,esp; mov [eax+k],reg) and integer-register members (float members emit fld/fstp
# under x87; the copies here are type-agnostic dword moves). /O2 default flags.
PATTERN = 'mov ecx, dword ptr [esp + N] ; push esi ; sub esp, N ; mov eax, esp ; mov dword ptr [eax], ecx ; mov edx, dword ptr [esp + N] ; mov dword ptr [eax + N], edx ; mov ecx, dword ptr [esp + N] ; mov dword ptr [eax + N], ecx ; mov edx, dword ptr [esp + N] ; mov dword ptr [eax + N], edx ; mov ecx, dword ptr [esp + N] ; mov esi, dword ptr [esp + N] ; sub esp, N ; mov eax, esp ; mov dword ptr [eax], ecx ; mov edx, dword ptr [esp + N] ; mov dword ptr [eax + N], edx ; mov ecx, dword ptr [esp + N] ; mov dword ptr [eax + N], ecx ; mov edx, dword ptr [esp + N] ; mov dword ptr [eax + N], edx ; mov ecx, dword ptr [esp + N] ; sub esp, N ; mov eax, esp ; mov dword ptr [eax], ecx ; mov edx, dword ptr [esp + N] ; mov dword ptr [eax + N], edx ; mov ecx, dword ptr [esp + N] ; mov dword ptr [eax + N], ecx ; mov edx, dword ptr [esp + N] ; push esi ; mov dword ptr [eax + N], edx ; call EXT ; add esp, N ; mov eax, esi ; pop esi ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ("struct Quad16 { int a, b, c, d; Quad16() {} "
           "Quad16(const Quad16& o) : a(o.a), b(o.b), c(o.c), d(o.d) {} };\n"
           "Quad16 Quad16_Op3(Quad16, Quad16, Quad16);\n")
def emit(va, A, N):
    if N[0] != 0x28 or N[1] != 0x10:
        return "// unexpected frame", "?unexpected_%08x@@YAXXZ" % va
    src = "Quad16 FUN_%08x(Quad16 a, Quad16 b, Quad16 c) { return Quad16_Op3(a, b, c); }" % va
    return src, "?FUN_%08x@@YA?AUQuad16@@U1@00@Z" % va
