# EASTL vector<T*>::set_capacity/reserve(n): if (n > capacity) realloc, memcpy, free, update pointers.
PATTERN = 'push ebx ; mov ebx, dword ptr [esp + N] ; push esi ; mov esi, ecx ; mov eax, dword ptr [esi + N] ; sub eax, dword ptr [esi] ; sar eax, N ; cmp ebx, eax ; jbe +N ; push edi ; test ebx, ebx ; je +N ; push N ; push A ; push N ; push N ; lea ecx, [ebx*N] ; push A ; push ecx ; call EXT ; add esp, N ; mov edi, eax ; jmp +N ; xor edi, edi ; mov eax, dword ptr [esi] ; mov edx, dword ptr [esi + N] ; sub edx, eax ; push edx ; push eax ; push edi ; call EXT ; mov eax, dword ptr [esi] ; add esp, N ; test eax, eax ; je +N ; cmp dword ptr [eax - N], N ; je +N ; push eax ; call EXT ; add esp, N ; mov eax, dword ptr [esi + N] ; sub eax, dword ptr [esi] ; lea ecx, [edi + ebx*N] ; sar eax, N ; lea eax, [edi + eax*N] ; mov dword ptr [esi], edi ; mov dword ptr [esi + N], eax ; mov dword ptr [esi + N], ecx ; pop edi ; pop esi ; pop ebx ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """#include <string.h>
extern "C" {
void* __cdecl EASTL_allocator_allocate(unsigned, const char*, int, int, const char*, int);
void __cdecl EASTL_allocator_deallocate(void*);
}
extern const char s_file[];
"""
def emit(va, A, N):
    a_file, a_name = A[0], A[1]
    src = """extern const char n_%08x[];
struct V_%08x { unsigned *b, *e, *c; void f(unsigned n); };
void V_%08x::f(unsigned n) {
    if (n > (unsigned)(c - b)) {
        unsigned* p = n ? (unsigned*)EASTL_allocator_allocate(n * 4, n_%08x, 0, 0, s_file, 0xd1) : 0;
        memcpy(p, b, (char*)e - (char*)b);
        if (b && ((int*)b)[-1]) EASTL_allocator_deallocate(b);
        unsigned* ne = p + (e - b);
        b = p; e = ne; c = p + n;
    }
}
""" % (va, va, va, va)
    return src, "?f@V_%08x@@QAEXI@Z" % va
