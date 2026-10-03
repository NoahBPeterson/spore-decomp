# Uninit-copy of POD struct returning a one-pointer class with a user ctor (hidden return ptr, no eax set):
# R r(dest); for (; first != last; ++first, ++r.p) new (r.p) T(*first); return r;  -> rep movsd, first/last in memory.
PATTERN = 'mov edx, dword ptr [esp + N] ; mov eax, dword ptr [esp + N] ; push esi ; mov esi, dword ptr [esp + N] ; mov dword ptr [eax], edx ; cmp esi, dword ptr [esp + N] ; je +N ; push edi ; test edx, edx ; je +N ; mov ecx, N ; mov edi, edx ; rep movsd dword ptr es:[edi], dword ptr [esi] ; mov esi, dword ptr [esp + N] ; add esi, N ; add edx, N ; mov dword ptr [esp + N], esi ; cmp esi, dword ptr [esp + N] ; jne +N ; mov dword ptr [eax], edx ; pop edi ; pop esi ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "#include <new>\n"
def emit(va, A, N):
    size = N[4] * 4
    s = "S%08x" % va
    r = "R%08x" % va
    i = "I%08x" % va
    src = ("struct %(s)s { char d[0x%(sz)x]; };\n"
           "struct %(i)s { %(s)s* p; %(s)s& operator*() const { return *p; } %(i)s& operator++() { ++p; return *this; }\n"
           "  bool operator!=(const %(i)s& o) const { return p != o.p; } };\n"
           "struct %(r)s { %(s)s* p; %(r)s(%(s)s* q) : p(q) {} };\n"
           "%(r)s FUN_%(va)08x(%(i)s first, %(i)s last, %(s)s* dest) {\n"
           "    %(r)s r(dest);\n"
           "    for (; first != last; ++first, ++r.p) new (r.p) %(s)s(*first);\n"
           "    return r;\n"
           "}\n") % dict(s=s, r=r, i=i, sz=size, va=va)
    return src, "?FUN_%08x@@YA?AU%s@@U%s@@0PAU%s@@@Z" % (va, r, i, s)
