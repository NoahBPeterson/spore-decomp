# Virtual-call thunk: mov eax,[ecx]; mov edx,[eax+N]; jmp edx (naked inline asm; MSVC would emit jmp [eax+N])
PATTERN = 'mov eax, dword ptr [ecx] ; mov edx, dword ptr [eax + N] ; jmp edx'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    off = N[0] if N else 0
    src = ("__declspec(naked) void __fastcall FUN_%08x(void*) { __asm { mov eax, [ecx]\n"
           " mov edx, [eax+0x%x]\n jmp edx } }" % (va, off))
    return src, "?FUN_%08x@@YIXPAX@Z" % va
