# cdecl f(A*, B*): ext(b->h, (int)cvtss2si(a->x)); return 0;  (inline asm cvtss2si, /O2 /arch:SSE)
PATTERN = 'mov eax, dword ptr [esp + N] ; movss xmm0, dword ptr [eax + N] ; movss dword ptr [esp + N], xmm0 ; cvtss2si eax, dword ptr [esp + N] ; mov ecx, dword ptr [esp + N] ; mov edx, dword ptr [ecx + N] ; push eax ; push edx ; call EXT ; add esp, N ; xor eax, eax ; ret '
FLAGS = ["/O2", "/arch:SSE", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """#pragma warning(disable:4035)
__forceinline int RoundF(float f) { __asm cvtss2si eax, f }
void ext_call(void*, int);
"""
def emit(va, A, N):
    oa, ob = N[1], N[5]
    return ("struct SA_%08x { char p[%d]; float x; };\nstruct SB_%08x { char p[%d]; void* h; };\n"
            "int FUN_%08x(SA_%08x* a, SB_%08x* b) { ext_call(b->h, RoundF(a->x)); return 0; }"
            % (va, oa, va, ob, va, va, va)), "?FUN_%08x@@YAHPAUSA_%08x@@PAUSB_%08x@@@Z" % (va, va, va)
