# Forward POD struct range copy (std::copy shape) as a returning function template: the dest
# pointer lives in eax at exit, and the non-void template form schedules dest's load first.
PATTERN = 'mov edx, dword ptr [esp + N] ; mov eax, dword ptr [esp + N] ; push ebx ; mov ebx, dword ptr [esp + N] ; cmp edx, ebx ; je +N ; push esi ; push edi ; mov esi, edx ; mov edi, eax ; add edx, N ; mov ecx, N ; add eax, N ; rep movsd dword ptr es:[edi], dword ptr [esi] ; cmp edx, ebx ; jne +N ; pop edi ; pop esi ; pop ebx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    size = max(N)
    s = "S_%08x" % va
    src = ("struct %s { int d[%d]; };\n"
           "template<class P> P* cp_%08x(P* first, P* last, P* dest) {\n"
           "    for (; first != last; ++dest, ++first) *dest = *first;\n    return dest;\n}\n"
           "template %s* cp_%08x<%s>(%s*, %s*, %s*);\n") % (s, size // 4, va, s, va, s, s, s, s)
    return src, "??$cp_%08x@U%s@@@@YAPAU%s@@PAU0@00@Z" % (va, s, s)
