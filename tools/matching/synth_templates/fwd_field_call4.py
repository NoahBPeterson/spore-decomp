# cdecl f(p,a,b,c,d) { ext(p->field, a,b,c,d); } with the tail call (jmp) suppressed.
# Shape-equivalent only: the real source blocker is unknown; an empty inline-asm label
# (__asm { l: }) blocks cl's tail-call optimization at zero byte cost.
PATTERN = 'mov eax, dword ptr [esp + N] ; mov ecx, dword ptr [esp + N] ; mov edx, dword ptr [esp + N] ; push eax ; mov eax, dword ptr [esp + N] ; push ecx ; mov ecx, dword ptr [esp + N] ; push edx ; mov edx, dword ptr [ecx + N] ; push eax ; push edx ; call EXT ; add esp, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    off = N[-2] if len(N) >= 2 else 0
    return ("struct S_%08x { int pad[%d]; int f; };\n"
            "void ext_%08x(int, int, int, int, int);\n"
            "void FUN_%08x(S_%08x* p, int a, int b, int c, int d) { ext_%08x(p->f, a, b, c, d); __asm { l1: } }"
            % (va, off // 4, va, va, va, va)), "?FUN_%08x@@YAXPAUS_%08x@@HHHH@Z" % (va, va)
