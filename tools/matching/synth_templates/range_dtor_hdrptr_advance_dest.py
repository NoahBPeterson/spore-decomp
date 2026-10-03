# Range loop: for (; first != last; first += sz, dest += sz) destroy member hdr-pointer at +off
# (free if p && p[-1]); returns dest.
import re
PATTERN = 'push ebx ; mov ebx, dword ptr [esp + N] ; push esi ; mov esi, dword ptr [esp + N] ; cmp esi, ebx ; je +N ; push edi ; mov edi, dword ptr [esp + N] ; mov eax, dword ptr [esi + N] ; test eax, eax ; je +N ; cmp dword ptr [eax - N], N ; je +N ; push eax ; call EXT ; add esp, N ; add esi, N ; add edi, N ; cmp esi, ebx ; jne +N ; mov eax, edi ; pop edi ; pop esi ; pop ebx ; ret  ; mov eax, dword ptr [esp + N] ; pop esi ; pop ebx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "void EASTL_allocator_deallocate(void* p);\n"
def emit(va, A, N):
    # N: 0xc, 0xc, 0x18, off, -4(4), 0, 4, size, size, 0x14
    off, size = N[3], N[7]
    s = "S_%08x" % va
    src = ("struct %s { char d[0x%x]; ~%s() { int* p = *(int**)(d + 0x%x); if (p && p[-1]) EASTL_allocator_deallocate(p); } };\n"
           "%s* FUN_%08x(%s* first, %s* last, %s* dest) {\n"
           "    for (; first != last; ++first, ++dest) first->~%s();\n"
           "    return dest;\n}\n") % (s, size, s, off, s, va, s, s, s, s)
    return src, "?FUN_%08x@@YAPAU%s@@PAU1@00@Z" % (va, s)
