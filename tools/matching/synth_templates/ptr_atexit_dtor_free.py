# atexit destructor (??__F) of a file-scope global holding one pointer, freed if non-null:
#   mov eax,[g]; test eax,eax; je; push eax; call EASTL_allocator_deallocate; pop ecx; ret
PATTERN = 'mov eax, dword ptr [A] ; test eax, eax ; je +N ; push eax ; call EXT ; pop ecx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """void EASTL_allocator_deallocate(void* p);
struct PtrFree {
    int* mp;
    ~PtrFree() { if (mp) EASTL_allocator_deallocate(mp); }
};
"""
def emit(va, A, N):
    return "PtrFree g_%08x;" % A[0], "??__Fg_%08x@@YAXXZ" % A[0]
