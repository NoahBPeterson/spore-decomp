# __stdcall(a,b,c,d): local polymorphic object {vptr, char 0, int d}; cdecl ext(b, a, c, &obj)
PATTERN = 'sub esp, N ; mov eax, dword ptr [esp + N] ; mov edx, dword ptr [esp + N] ; lea ecx, [esp] ; push ecx ; mov ecx, dword ptr [esp + N] ; mov dword ptr [esp + N], eax ; mov eax, dword ptr [esp + N] ; push edx ; push eax ; push ecx ; mov byte ptr [esp + N], N ; mov dword ptr [esp + N], A ; call EXT ; add esp, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    t = "S_%08x" % va
    src = ("struct %s { void* const* vt; char b; int v; };\n"
           "extern void* const vt_%08x[];\n"
           "void ext_%08x(int, int, int, %s*);\n"
           "void __stdcall FUN_%08x(int a, int b, int c, int d) { %s s; s.v = d; s.b = 0; s.vt = vt_%08x; ext_%08x(b, a, c, &s); }"
           % (t, A[0], va, t, va, t, A[0], va))
    return src, "?FUN_%08x@@YGXHHHH@Z" % va
