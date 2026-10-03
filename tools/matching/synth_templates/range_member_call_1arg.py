# Loop over [first, last) calling an out-of-line __thiscall member with one by-value
# argument (std::for_each / destroy-range-with-allocator shape):
#   for (; first != last; ++first) first->f(arg);
PATTERN = 'push esi ; mov esi, dword ptr [esp + N] ; push edi ; mov edi, dword ptr [esp + N] ; cmp esi, edi ; je +N ; push ebx ; mov ebx, dword ptr [esp + N] ; push ebx ; mov ecx, esi ; call EXT ; add esi, N ; cmp esi, edi ; jne +N ; pop ebx ; pop edi ; pop esi ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    size = N[3]
    s = "S_%08x" % va
    src = ("struct %s { char d[0x%x]; void f(int); };\n"
           "void FUN_%08x(%s* first, %s* last, int arg) {\n"
           "    for (; first != last; ++first) first->f(arg);\n}\n") % (s, size, va, s, s)
    return src, "?FUN_%08x@@YAXPAU%s@@0H@Z" % (va, s)
