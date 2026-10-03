# Virtual-call thunk: mov eax,[ecx]; mov eax,[eax+N]; jmp eax  (naked inline asm; MSVC would emit jmp [eax+N])
PATTERN = 'mov eax, dword ptr [ecx] ; mov eax, dword ptr [eax + N] ; jmp eax'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    off = N[0] if N else 0
    src = ("__declspec(naked) void __fastcall FUN_%08x(void*) { __asm { mov eax, [ecx]\n"
           " mov eax, [eax+0x%x]\n jmp eax } }" % (va, off))
    return src, "?FUN_%08x@@YIXPAX@Z" % va
