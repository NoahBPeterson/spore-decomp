# Global fixed-vector dtor: if (begin && begin != buffer) EASTL_allocator_deallocate(begin)
PATTERN = 'mov eax, dword ptr [A] ; test eax, eax ; je +N ; cmp eax, dword ptr [A] ; je +N ; push eax ; call EXT ; pop ecx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = "void EASTL_allocator_deallocate(void* p);\n"
def emit(va, A, N):
    return ("extern void* g_%08x; extern void* g_%08x;\n"
            "void FUN_%08x() { if (g_%08x && g_%08x != g_%08x) EASTL_allocator_deallocate(g_%08x); }"
            % (A[0], A[1], va, A[0], A[0], A[1], A[0])), "?FUN_%08x@@YAXXZ" % va
