# Forward POD struct range copy returning void: for (; first != last; ++first, ++dest) *dest = *first;
PATTERN = 'mov edx, dword ptr [esp + N] ; mov eax, dword ptr [esp + N] ; push ebx ; mov ebx, dword ptr [esp + N] ; cmp edx, ebx ; je +N ; push esi ; push edi ; mov esi, edx ; mov edi, eax ; add edx, N ; mov ecx, N ; add eax, N ; rep movsd dword ptr es:[edi], dword ptr [esi] ; cmp edx, ebx ; jne +N ; pop edi ; pop esi ; pop ebx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    size = max(N)
    s = "S_%08x" % va
    src = ("struct %s { int d[%d]; };\n"
           "void FUN_%08x(%s* first, %s* last, %s* dest) {\n"
           "    for (; first != last; ++first, ++dest) *dest = *first;\n}\n") % (s, size // 4, va, s, s, s)
    return src, "?FUN_%08x@@YAXPAU%s@@00@Z" % (va, s)
