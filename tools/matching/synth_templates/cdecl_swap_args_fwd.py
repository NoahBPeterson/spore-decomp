# cdecl wrapper forwarding its two args swapped to an external cdecl function.
PATTERN = 'mov eax, dword ptr [esp + N] ; mov ecx, dword ptr [esp + N] ; push eax ; push ecx ; call EXT ; add esp, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    return ("void ext_%08x(int, int);\nvoid FUN_%08x(int a, int b) { ext_%08x(b, a); }" % (va, va, va),
            "?FUN_%08x@@YAXHH@Z" % va)
