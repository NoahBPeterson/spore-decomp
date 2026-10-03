# atexit destructor (??__F) of a global {Base sub@0; void* mp@4; unsigned mCap@8; int mSize@0xC}:
#   sub.Release(mp, mCap); mSize = 0; if (mCap > 1) EASTL_allocator_deallocate(mp);
PATTERN = 'mov eax, dword ptr [A] ; mov ecx, dword ptr [A] ; push eax ; push ecx ; mov ecx, A ; call EXT ; cmp dword ptr [A], N ; mov dword ptr [A], N ; jbe +N ; mov edx, dword ptr [A] ; push edx ; call EXT ; pop ecx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """void EASTL_allocator_deallocate(void* p);
struct Sub { void Release(void* p, unsigned n); };
struct CapBuf {
    Sub mSub; void* mp; unsigned mCap; int mSize;
    ~CapBuf() { mSub.Release(mp, mCap); mSize = 0; if (mCap > 1) EASTL_allocator_deallocate(mp); }
};
"""
def emit(va, A, N):
    base = A[2]
    if A[1] == base + 4 and A[0] == base + 8 and A[4] == base + 0xC and N == [1, 0]:
        return "CapBuf g_%08x;" % base, "??__Fg_%08x@@YAXXZ" % base
    return "// unsupported A=%r N=%r\nvoid FUN_%08x() {}" % (A, N, va), "?FUN_%08x@@YAXXZ" % va
