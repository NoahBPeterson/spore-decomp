PATTERN = 'push ecx ; push esi ; mov esi, ecx ; mov eax, dword ptr [esi + N] ; cmp eax, N ; jne +N ; mov ecx, dword ptr [A] ; push N ; push N ; push N ; push N ; push N ; push N ; push N ; push N ; call EXT ; mov ecx, dword ptr [esi + N] ; mov dword ptr [esp + N], eax ; cmp ecx, dword ptr [esi + N] ; jae +N ; lea edx, [ecx + N] ; mov dword ptr [esi + N], edx ; test ecx, ecx ; je +N ; mov dword ptr [ecx], eax ; mov dword ptr [esi + N], N ; pop esi ; pop ecx ; ret  ; lea eax, [esp + N] ; push eax ; push ecx ; mov ecx, esi ; call EXT ; mov dword ptr [esi + N], N ; pop esi ; pop ecx ; ret  ; inc eax ; mov dword ptr [esi + N], eax ; pop esi ; pop ecx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ("struct Alloc { void* Do(unsigned size, unsigned align, int, int, int, int, int, int); };\n"
           "struct Vec { char pad0[4]; void** end; void** cap; char pad1[8]; int idx;\n"
           "  void Grow(void** pos, void** const& v);\n"
           "  void Advance(Alloc* a, unsigned size, unsigned align);\n};\n")
def emit(va, A, N):
    size, align = N[9], N[8]
    src = ("extern Alloc* g_%08x;\n"
           "void __fastcall FUN_%08x(Vec* v) {\n"
           "  if (v->idx == 127) {\n"
           "    void* p = g_%08x->Do(%d, %d, 0, 0, 0, 0, 0, 0);\n"
           "    if (v->end < v->cap) { void** q = v->end; v->end = q + 1; if (q) *q = p; }\n"
           "    else v->Grow(v->end, (void** const&)p);\n"
           "    v->idx = 0;\n"
           "  } else v->idx++;\n}" % (A[0], va, A[0], size, align))
    return src, "?FUN_%08x@@YIXPAUVec@@@Z" % va
