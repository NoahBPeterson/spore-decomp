# Uninit-copy of intrusive refptrs (copy ctor stores ptr, AddRef via vtable slot), cursor held in a struct.
PATTERN = 'mov ecx, dword ptr [esp + N] ; mov eax, dword ptr [esp + N] ; push esi ; mov esi, dword ptr [esp + N] ; mov dword ptr [esi], eax ; cmp ecx, dword ptr [esp + N] ; je +N ; mov eax, dword ptr [esi] ; test eax, eax ; je +N ; mov ecx, dword ptr [ecx] ; mov dword ptr [eax], ecx ; test ecx, ecx ; je +N ; mov edx, dword ptr [ecx] ; mov eax, dword ptr [edx + N] ; call eax ; mov ecx, dword ptr [esp + N] ; add dword ptr [esi], N ; add ecx, N ; mov dword ptr [esp + N], ecx ; cmp ecx, dword ptr [esp + N] ; jne +N ; mov eax, esi ; pop esi ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "#include <new>\n"
def emit(va, A, N):
    slot = N[4] // 4
    o = "O%08x" % va; p = "P%08x" % va; r = "R%08x" % va; i = "I%08x" % va
    virt = "".join("virtual void v%d() throw(); " % k for k in range(slot + 1))
    src = ("struct %(o)s { %(virt)s};\n"
           "struct %(p)s { %(o)s* m; %(p)s(const %(p)s& x) throw() : m(x.m) { if (m) m->v%(s)d(); } };\n"
           "struct %(r)s { %(p)s* p; };\n"
           "struct %(i)s { %(p)s* p; %(p)s& operator*() const { return *p; } %(i)s& operator++() { ++p; return *this; }\n"
           "  bool operator!=(const %(i)s& o) const { return p != o.p; } };\n"
           "%(r)s* FUN_%(va)08x(%(r)s* r, %(i)s first, %(i)s last, %(p)s* init) {\n"
           "    r->p = init;\n"
           "    for (; first != last; ++first, ++r->p) new (r->p) %(p)s(*first);\n"
           "    return r;\n}\n") % dict(o=o, p=p, r=r, i=i, s=slot, virt=virt, va=va)
    return src, "?FUN_%08x@@YAPAU%s@@PAU1@U%s@@1PAU%s@@@Z" % (va, r, i, p)
