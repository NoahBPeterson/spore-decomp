# Range loop: for (; first < last; first += sz) free member hdr-pointer at +off (free if p && p[-1]); stdcall ret 8.
PATTERN = 'push esi ; mov esi, dword ptr [esp + N] ; push edi ; mov edi, dword ptr [esp + N] ; cmp esi, edi ; jae +N ; mov edi, edi ; mov eax, dword ptr [esi + N] ; test eax, eax ; je +N ; cmp dword ptr [eax - N], N ; je +N ; push eax ; call EXT ; add esp, N ; add esi, N ; cmp esi, edi ; jb +N ; pop edi ; pop esi ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "void EASTL_allocator_deallocate(void* p);\n"
def emit(va, A, N):
    off, size = N[2], N[-2]
    s = "S_%08x" % va
    src = ("struct %s { char d[0x%x]; };\n"
           "void __stdcall FUN_%08x(%s* first, %s* last) {\n"
           "    for (; first < last; ++first) { int* p = *(int**)(first->d + 0x%x); if (p && p[-1]) EASTL_allocator_deallocate(p); }\n}\n") % (s, size, va, s, s, off)
    return src, "?FUN_%08x@@YGXPAU%s@@0@Z" % (va, s)
