# Thunk to a virtual method of an embedded subobject: add ecx,off; mov eax,[ecx]; mov eax,[eax+slot]; jmp eax
# No plain-C++ shape reproduces it: /O2 hoists the vtable load above the add (mov eax,[ecx+off]; ...; add ecx),
# and /O1 /Os emit "jmp [eax+slot]". Naked inline asm is byte-exact.
PATTERN = 'add ecx, N ; mov eax, dword ptr [ecx] ; mov eax, dword ptr [eax + N] ; jmp eax'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    src = ("__declspec(naked) void __fastcall FUN_%08x(void*) { __asm { add ecx, 0x%x\n"
           " mov eax, [ecx]\n mov eax, [eax+0x%x]\n jmp eax } }" % (va, N[0], N[1]))
    return src, "?FUN_%08x@@YIXPAX@Z" % va
