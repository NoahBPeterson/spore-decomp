# Global dtor: if (FUN_00935ad0(g) && g) EASTL_allocator_deallocate(g)
PATTERN = 'mov eax, dword ptr [A] ; push eax ; call EXT ; add esp, N ; test al, al ; je +N ; mov eax, dword ptr [A] ; test eax, eax ; je +N ; push eax ; call EXT ; pop ecx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = "void EASTL_allocator_deallocate(void* p);\nbool FUN_00935ad0(void* p);\n"
def emit(va, A, N):
    return ("extern void* g_%08x;\n"
            "void FUN_%08x() { if (FUN_00935ad0(g_%08x) && g_%08x) EASTL_allocator_deallocate(g_%08x); }"
            % (A[0], va, A[0], A[0], A[0])), "?FUN_%08x@@YAXXZ" % va
