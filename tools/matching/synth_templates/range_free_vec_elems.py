# Range loop over elements holding {begin,?,cap}; frees begin if (cap-begin)>1 and begin!=0; returns advanced dest.
PATTERN = 'push ebx ; mov ebx, dword ptr [esp + N] ; push esi ; mov esi, dword ptr [esp + N] ; cmp esi, ebx ; je +N ; push edi ; mov edi, dword ptr [esp + N] ; mov eax, dword ptr [esi] ; mov ecx, dword ptr [esi + N] ; sub ecx, eax ; cmp ecx, N ; jle +N ; test eax, eax ; je +N ; push eax ; call EXT ; add esp, N ; add esi, N ; add edi, N ; cmp esi, ebx ; jne +N ; mov eax, edi ; pop edi ; pop esi ; pop ebx ; ret  ; mov eax, dword ptr [esp + N] ; pop esi ; pop ebx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    off, stride = N[3], N[6]
    s = "S_%08x" % va
    mid = "char mid[%d]; " % (off - 4) if off > 4 else ""
    tail = "char tail[%d]; " % (stride - off - 4) if stride - off - 4 > 0 else ""
    src = ("void dealloc_%08x(char*);\n"
           "struct %s { char* b; %schar* c; %s};\n"
           "%s* FUN_%08x(%s* first, %s* last, %s* dest) {\n"
           "  for (; first != last; ++first, ++dest) { char* p = first->b; if ((first->c - p) > 1 && p) dealloc_%08x(p); }\n"
           "  return dest;\n}") % (va, s, mid, tail, s, va, s, s, s, va)
    return src, "?FUN_%08x@@YAPAU%s@@PAU1@00@Z" % (va, s)
