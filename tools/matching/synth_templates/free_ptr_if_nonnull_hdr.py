# Fastcall(this): p = *(T**)(this+N); if (p && ((int*)p)[-1]) dealloc(p);  (shape-equivalent free function)
PATTERN = 'mov eax, dword ptr [ecx + N] ; test eax, eax ; je +N ; cmp dword ptr [eax - N], N ; je +N ; push eax ; call EXT ; pop ecx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "void __cdecl EASTL_allocator_deallocate(void*);\n"
def emit(va, A, N):
    off = N[0]
    return ("void __fastcall FUN_%08x(char* t) {\n"
            "  int* p = *(int**)(t + %d);\n"
            "  if (p && p[-1] != 0) EASTL_allocator_deallocate(p);\n}" % (va, off)), "?FUN_%08x@@YIXPAD@Z" % va
