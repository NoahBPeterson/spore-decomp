# Stdcall range destroy: for each stride-sized element with char* begin/end/cap, free begin if capacity>1 and non-null.
PATTERN = 'push esi ; mov esi, dword ptr [esp + N] ; push edi ; mov edi, dword ptr [esp + N] ; cmp esi, edi ; jae +N ; mov edi, edi ; mov eax, dword ptr [esi] ; mov ecx, dword ptr [esi + N] ; sub ecx, eax ; cmp ecx, N ; jle +N ; test eax, eax ; je +N ; push eax ; call EXT ; add esp, N ; add esi, N ; cmp esi, edi ; jb +N ; pop edi ; pop esi ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "void EASTL_allocator_deallocate(void* p);\n"
def emit(va, A, N):
    stride = N[-2]
    s = "S_%08x" % va
    pad = "char pad[%d]; " % (stride - 12) if stride > 12 else ""
    src = ("struct %s { char* b; char* e; char* c; %s};\n"
           "void __stdcall FUN_%08x(%s* first, %s* last) {\n"
           "  for (; first < last; ++first) { char* p = first->b; if (first->c - p > 1 && p) EASTL_allocator_deallocate(p); }\n}") % (s, pad, va, s, s)
    return src, "?FUN_%08x@@YGXPAU%s@@0@Z" % (va, s)
