# Fixed-size pool alloc(n): size=n*4+4; if size==K pop freelist (else vcall slot2 on sub-allocator, stats),
# elif size==M*4 use inline buffer; memset(p,0,n*4); ((char*)p)[n*4]=-1.
import re
PATTERN = 'push ebx ; mov ebx, dword ptr [esp + N] ; add ebx, ebx ; push esi ; add ebx, ebx ; push edi ; lea eax, [ebx + N] ; xor edi, edi ; mov esi, ecx ; cmp eax, N ; jne +N ; mov eax, dword ptr [esi + N] ; test eax, eax ; je +N ; mov ecx, dword ptr [eax] ; mov dword ptr [esi + N], ecx ; jmp +N ; mov edx, dword ptr [esi + N] ; mov eax, dword ptr [esi + N] ; mov edx, dword ptr [edx + N] ; lea ecx, [esi + N] ; push eax ; call edx ; test eax, eax ; je +N ; inc dword ptr [esi + N] ; mov ecx, dword ptr [esi + N] ; cmp ecx, dword ptr [esi + N] ; jbe +N ; mov dword ptr [esi + N], ecx ; mov edi, eax ; jmp +N ; mov ecx, dword ptr [esi + N] ; add ecx, ecx ; add ecx, ecx ; cmp eax, ecx ; jne +N ; mov edi, dword ptr [esi + N] ; push ebx ; push N ; push edi ; call EXT ; add esp, N ; mov dword ptr [ebx + edi], A ; mov eax, edi ; pop edi ; pop esi ; pop ebx ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """#include <string.h>
struct SubAlloc { virtual void a0(); virtual void a1(); virtual void* alloc(void* arg); };
struct PoolBase { char pad0[0x28]; SubAlloc sub; };
"""
def emit(va, A, N):
    K = N[2]
    src = ("struct Pool_%08x { char pad0[0x28]; SubAlloc sub; char pad1[0x34-0x28-sizeof(SubAlloc)]; void* arg; char pad2[0x40-0x38]; void** head; unsigned count; unsigned maxc; unsigned bufn; void* buf;\n"
           "  void* __thiscall FUN_%08x(unsigned n); };\n"
           "void* Pool_%08x::FUN_%08x(unsigned n) {\n"
           "  unsigned size = n*4+4;\n  void* p = 0;\n"
           "  if (size == 0x%x) {\n    void* q = head;\n    if (q) head = (void**)*head; else q = sub.alloc(arg);\n"
           "    if (q) { ++count; if (count > maxc) maxc = count; }\n    p = q;\n"
           "  } else if (size == bufn*4) p = buf;\n"
           "  memset(p, 0, n*4);\n  *(int*)((char*)p + n*4) = -1;\n  return p;\n}") % (va, va, va, va, K)
    return src, "?FUN_%08x@Pool_%08x@@QAEPAXI@Z" % (va, va)
