# cdecl bool f(Obj* self, void* p): if (p) self->Register(p, &g_xxx, L"name"); return true;
#   mov eax,[esp+8]; test; je; mov ecx,[esp+4]; push name; push g; push eax; call; mov al,1; ret
PATTERN = 'mov eax, dword ptr [esp + N] ; test eax, eax ; je +N ; mov ecx, dword ptr [esp + N] ; push A ; push A ; push eax ; call EXT ; mov al, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "struct Obj { void Reg(void* p, const void* g, const wchar_t* name); };\n"

def emit(va, A, N):
    return ("extern char g_%08x;\nbool FUN_%08x(Obj* self, void* p) { if (p) self->Reg(p, &g_%08x, L\"n%08x\"); return true; }"
            % (A[1], va, A[1], va)), "?FUN_%08x@@YA_NPAUObj@@PAX@Z" % va
