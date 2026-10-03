# vector copy: this->_Buy(count, &o->alloc); this->last = _Ucopy(&slot, o->first, o->last, this->first, o)
PATTERN = 'push esi ; mov esi, ecx ; push edi ; mov edi, dword ptr [esp + N] ; mov ecx, dword ptr [edi + N] ; sub ecx, dword ptr [edi] ; lea eax, [edi + N] ; push eax ; mov eax, A ; imul ecx ; add edx, ecx ; sar edx, N ; mov ecx, edx ; shr ecx, N ; add ecx, edx ; push ecx ; mov ecx, esi ; call EXT ; mov edx, dword ptr [esp + N] ; mov eax, dword ptr [esi] ; mov ecx, dword ptr [edi + N] ; mov edi, dword ptr [edi] ; push edx ; push eax ; push ecx ; lea eax, [esp + N] ; push edi ; push eax ; call EXT ; mov ecx, dword ptr [esp + N] ; add esp, N ; pop edi ; mov dword ptr [esi + N], ecx ; mov eax, esi ; pop esi ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    sh = N[3]
    size = 15 * (1 << (sh - 3)) if A[0] == 0x88888889 else 7 * (1 << (sh - 2))
    t = "T_%08x" % va
    src = ("struct %s { char d[%d]; };\n"
           "struct V_%08x {\n  %s *b, *e, *c; int al;\n"
           "  void Buy(int n, const int* a);\n"
           "  V_%08x& __thiscall FUN_%08x(const V_%08x* o);\n};\n"
           "void Ucopy_%08x(%s** out, %s* f, %s* l, %s* d, const void* a);\n"
           "V_%08x& V_%08x::FUN_%08x(const V_%08x* o) {\n"
           "  const V_%08x* p = o;\n"
           "  Buy(p->e - p->b, &p->al);\n"
           "  Ucopy_%08x((%s**)&o, p->b, p->e, b, o);\n"
           "  e = (%s*)o;\n  return *this;\n}"
           ) % (t, size, va, t, va, va, va, va, t, t, t, t, va, va, va, va, va, va, t, t)
    return src, "?FUN_%08x@V_%08x@@QAEAAU1@PBU1@@Z" % (va, va)
