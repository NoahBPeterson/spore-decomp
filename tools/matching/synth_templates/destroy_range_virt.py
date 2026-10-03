# Range loop calling virtual dtor on each element, advancing a dest pointer in lockstep; returns dest.
PATTERN = 'push ebx ; mov ebx, dword ptr [esp + N] ; push esi ; mov esi, dword ptr [esp + N] ; cmp esi, ebx ; je +N ; push edi ; mov edi, dword ptr [esp + N] ; mov eax, dword ptr [esi] ; mov edx, dword ptr [eax] ; push N ; mov ecx, esi ; call edx ; add esi, N ; add edi, N ; cmp esi, ebx ; jne +N ; mov eax, edi ; pop edi ; pop esi ; pop ebx ; ret  ; mov eax, dword ptr [esp + N] ; pop esi ; pop ebx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    s = N[4]
    src = ("struct T_%08x { virtual ~T_%08x(); char pad[%d]; };\n"
           "T_%08x* FUN_%08x(T_%08x* first, T_%08x* last, T_%08x* dest) {\n"
           "  for (; first != last; ++first, ++dest) first->~T_%08x();\n"
           "  return dest;\n}\n") % (va, va, s - 4, va, va, va, va, va, va)
    return src, "?FUN_%08x@@YAPAUT_%08x@@PAU1@00@Z" % (va, va)
