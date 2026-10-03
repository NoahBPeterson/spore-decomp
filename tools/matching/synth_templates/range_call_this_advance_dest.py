# Range loop calling a thiscall member on each element while advancing a second cursor:
# for (; first != last; first += sz, dest += sz) first->f(); return dest;
PATTERN = 'push ebx ; mov ebx, dword ptr [esp + N] ; push esi ; mov esi, dword ptr [esp + N] ; cmp esi, ebx ; je +N ; push edi ; mov edi, dword ptr [esp + N] ; mov ecx, esi ; call EXT ; add esi, N ; add edi, N ; cmp esi, ebx ; jne +N ; mov eax, edi ; pop edi ; pop esi ; pop ebx ; ret  ; mov eax, dword ptr [esp + N] ; pop esi ; pop ebx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    size = N[4]
    s = "S_%08x" % va
    src = ("struct %s { char d[0x%x]; void f(); };\n"
           "%s* FUN_%08x(%s* first, %s* last, %s* dest) {\n"
           "    for (; first != last; ++first, ++dest) first->f();\n"
           "    return dest;\n}\n") % (s, size, s, va, s, s, s)
    return src, "?FUN_%08x@@YAPAU%s@@PAU1@00@Z" % (va, s)
