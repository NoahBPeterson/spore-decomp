# atexit destructor (??__F) of a file-scope global holding a single pointer whose allocation
# carries a header word at p[-1] (count/refcount); freed only if p && p[-1] != 0:
#   mov eax,[g]; test eax,eax; je; cmp [eax-4],0; je; push eax; call EASTL_allocator_deallocate; pop ecx; ret
# Source shape: struct with one pointer member and an inline dtor, global object at /O2.
PATTERN = 'mov eax, dword ptr [A] ; test eax, eax ; je +N ; cmp dword ptr [eax - N], N ; je +N ; push eax ; call EXT ; pop ecx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """void EASTL_allocator_deallocate(void* p);
struct HdrPtr {
    int* mp;
    ~HdrPtr() { if (mp && mp[-1]) EASTL_allocator_deallocate(mp); }
};
"""
def emit(va, A, N):
    if N[-2:] == [4, 0]:
        return "HdrPtr g_%08x;" % A[0], "??__Fg_%08x@@YAXXZ" % A[0]
    return "// unsupported N=%r\nvoid FUN_%08x() {}" % (N, va), "?FUN_%08x@@YAXXZ" % va
