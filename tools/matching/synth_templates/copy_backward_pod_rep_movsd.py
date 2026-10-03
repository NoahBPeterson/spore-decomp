# Backward element-wise copy loop (std::copy_backward) over a trivially-assignable POD struct of
# N dwords: struct assignment becomes inline rep movsd. Returns dest.
PATTERN = 'mov edx, dword ptr [esp + N] ; mov eax, dword ptr [esp + N] ; push ebx ; mov ebx, dword ptr [esp + N] ; cmp edx, ebx ; je +N ; push esi ; push edi ; sub edx, N ; sub eax, N ; mov ecx, N ; mov esi, edx ; mov edi, eax ; rep movsd dword ptr es:[edi], dword ptr [esi] ; cmp edx, ebx ; jne +N ; pop edi ; pop esi ; pop ebx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    n = N[-1]
    s = "S_%08x" % va
    src = ("struct %s { unsigned d[%d]; };\n"
           "%s* FUN_%08x(%s* first, %s* last, %s* dest) {\n"
           "    while (last != first) *--dest = *--last;\n    return dest;\n}\n") % (s, n, s, va, s, s, s)
    return src, "?FUN_%08x@@YAPAU%s@@PAU1@00@Z" % (va, s)
