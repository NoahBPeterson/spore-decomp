# thiscall method (1 stack arg) forwarding (this->field@off, arg) to a cdecl free function
PATTERN = 'mov eax, dword ptr [esp + N] ; mov ecx, dword ptr [ecx + N] ; push eax ; push ecx ; call EXT ; add esp, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    off = N[1]
    src = ("void __cdecl CALLEE_%08x(void*, void*);\n"
           "struct S_%08x { char pad[%d]; void* f; void m(void* a); };\n"
           "void S_%08x::m(void* a) { CALLEE_%08x(f, a); }" % (va, va, off, va, va))
    return src, "?m@S_%08x@@QAEXPAX@Z" % va
