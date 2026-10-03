# eastl::vector<4-byte T>::resize(n, value): grow via DoInsertValues, shrink via inlined erase (memcpy of 0 bytes).
PATTERN = 'push esi ; push edi ; mov edi, ecx ; mov esi, dword ptr [edi + N] ; mov edx, dword ptr [edi] ; mov ecx, dword ptr [esp + N] ; mov eax, esi ; sub eax, edx ; sar eax, N ; cmp ecx, eax ; jbe +N ; mov edx, dword ptr [esp + N] ; push edx ; sub ecx, eax ; push ecx ; push esi ; mov ecx, edi ; call EXT ; pop edi ; pop esi ; ret N ; push ebx ; mov eax, esi ; sub eax, esi ; push eax ; lea ebx, [edx + ecx*N] ; push esi ; push ebx ; call EXT ; sub esi, ebx ; sar esi, N ; neg esi ; add esp, N ; add esi, esi ; add esi, esi ; add dword ptr [edi + N], esi ; pop ebx ; pop edi ; pop esi ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """#include <string.h>
typedef unsigned int u32;
struct V { u32* b; u32* e; u32* c; void __thiscall ins(u32* pos, u32 n, const u32& v); };
"""
def emit(va, A, N):
    s = ("struct R%08x : V { void __thiscall resize_%08x(u32 n, const u32& v); };\n"
         "void __thiscall R%08x::resize_%08x(u32 n, const u32& v) {\n"
         "  u32 sz = (u32)(e - b);\n"
         "  if (n > sz) ins(e, n - sz, v);\n"
         "  else { u32* f = b + n; u32* l = e; memcpy(f, l, (char*)e - (char*)l); e = e - (l - f); }\n"
         "}" % (va, va, va, va))
    return s, "?resize_%08x@R%08x@@QAEXIABI@Z" % (va, va)
