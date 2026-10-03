# Uninitialized-copy loop (VC9 _Uninit_copy shape) with the destination cursor held in a struct:
# r->p = init; for (; first != last; ++first, ++r->p) new(r->p) T(*first); return r;
# Key lever: first/last are by-value one-pointer struct iterators (kept in memory, not registers).
# T's copy ctor is out of line, thiscall, throw() (no EH frame).
PATTERN = 'mov eax, dword ptr [esp + N] ; push esi ; mov esi, dword ptr [esp + N] ; mov dword ptr [esi], eax ; mov eax, dword ptr [esp + N] ; cmp eax, dword ptr [esp + N] ; je +N ; mov ecx, dword ptr [esi] ; test ecx, ecx ; je +N ; push eax ; call EXT ; mov eax, dword ptr [esp + N] ; add dword ptr [esi], N ; add eax, N ; mov dword ptr [esp + N], eax ; cmp eax, dword ptr [esp + N] ; jne +N ; mov eax, esi ; pop esi ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "#include <new>\n"
def emit(va, A, N):
    size = N[5]
    s = "S%08x" % va
    r = "R%08x" % va
    i = "I%08x" % va
    src = ("struct %(s)s { char d[0x%(sz)x]; %(s)s(const %(s)s&) throw(); };\n"
           "struct %(r)s { %(s)s* p; };\n"
           "struct %(i)s { %(s)s* p; %(s)s& operator*() const { return *p; } %(i)s& operator++() { ++p; return *this; }\n"
           "  bool operator!=(const %(i)s& o) const { return p != o.p; } };\n"
           "%(r)s* FUN_%(va)08x(%(r)s* r, %(i)s first, %(i)s last, %(s)s* init) {\n"
           "    r->p = init;\n"
           "    for (; first != last; ++first, ++r->p) new (r->p) %(s)s(*first);\n"
           "    return r;\n}\n") % dict(s=s, r=r, i=i, sz=size, va=va)
    return src, "?FUN_%08x@@YAPAU%s@@PAU1@U%s@@1PAU%s@@@Z" % (va, r, i, s)
