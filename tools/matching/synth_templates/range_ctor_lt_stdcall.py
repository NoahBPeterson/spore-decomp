# __stdcall void f(T* first, T* last): for (; first < last; ++first) first->f();  (relational compare, aligned loop)
PATTERN = 'push esi ; mov esi, dword ptr [esp + N] ; push edi ; mov edi, dword ptr [esp + N] ; cmp esi, edi ; jae +N ; mov edi, edi ; mov ecx, esi ; call EXT ; add esi, N ; cmp esi, edi ; jb +N ; pop edi ; pop esi ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    size = N[2]
    s = "S_%08x" % va
    src = ("struct %s { char d[0x%x]; void f(); };\n"
           "void __stdcall FUN_%08x(%s* first, %s* last) {\n"
           "    for (; first < last; ++first) first->f();\n}\n") % (s, size, va, s, s)
    return src, "?FUN_%08x@@YGXPAU%s@@0@Z" % (va, s)
