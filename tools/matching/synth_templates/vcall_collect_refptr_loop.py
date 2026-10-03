# Loader helper: begin(v); n=0; a->vf20()->vf18() -> ext(x,&n,1,0); v->reserve(n); loop n times:
# a->vf28(ID,&p,0); v->push_back(p) with AddRef vcall (slot N0) and Release vcall (slot N1); a->vf1c().
PATTERN = 'push ecx ; push ebp ; push esi ; mov esi, dword ptr [esp + N] ; mov eax, dword ptr [esi + N] ; mov ecx, dword ptr [esi] ; push edi ; push eax ; push ecx ; mov ecx, esi ; call EXT ; mov edi, dword ptr [esp + N] ; mov edx, dword ptr [edi] ; mov eax, dword ptr [edx + N] ; mov ecx, edi ; mov dword ptr [esp + N], N ; call eax ; mov edx, dword ptr [eax] ; mov ecx, eax ; mov eax, dword ptr [edx + N] ; call eax ; push N ; push N ; lea ecx, [esp + N] ; push ecx ; push eax ; call EXT ; mov edx, dword ptr [esp + N] ; add esp, N ; push edx ; mov ecx, esi ; call EXT ; xor ebp, ebp ; cmp dword ptr [esp + N], ebp ; jbe +N ; lea ebx, [ebx] ; mov eax, dword ptr [edi] ; mov edx, dword ptr [eax + N] ; push N ; lea ecx, [esp + N] ; push ecx ; push A ; mov ecx, edi ; mov dword ptr [esp + N], N ; call edx ; mov eax, dword ptr [esi + N] ; cmp eax, dword ptr [esi + N] ; jae +N ; lea ecx, [eax + N] ; mov dword ptr [esi + N], ecx ; test eax, eax ; je +N ; mov edx, dword ptr [esp + N] ; mov dword ptr [eax], edx ; mov ecx, dword ptr [esp + N] ; test ecx, ecx ; je +N ; mov eax, dword ptr [ecx] ; mov edx, dword ptr [eax + N] ; call edx ; jmp +N ; lea ecx, [esp + N] ; push ecx ; push eax ; mov ecx, esi ; call EXT ; mov ecx, dword ptr [esp + N] ; test ecx, ecx ; je +N ; mov edx, dword ptr [ecx] ; mov eax, dword ptr [edx + N] ; call eax ; inc ebp ; cmp ebp, dword ptr [esp + N] ; jb +N ; mov edx, dword ptr [edi] ; mov eax, dword ptr [edx + N] ; mov ecx, edi ; call eax ; pop edi ; pop esi ; pop ebp ; pop ecx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def _cls(name, slots):
    # slots: {index: decl}; fill the rest with placeholder virtuals
    top = max(slots) + 1
    lines = ["struct %s {" % name]
    for k in range(top):
        lines.append("  " + slots.get(k, "virtual void p%d();" % k))
    return lines

def emit(va, A, N):
    add_slot, rel_slot = N[24] // 4, N[27] // 4
    ref = _cls("R%08x" % va, {add_slot: "virtual void add();", rel_slot: "virtual void rel();"}) + ["};"]
    nm = "R%08x" % va
    src = []
    src += ref
    src += ["struct X%08x { virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual int q(); };" % va]
    src += _cls("I%08x" % va, {7: "virtual void fin();", 8: "virtual X%08x* gx();" % va,
                              10: "virtual void mk(unsigned, %s**, int);" % nm}) + ["};"]
    src += ["struct V%08x { %s **b, **e, **c;" % (va, nm),
            "  void __thiscall a1(int, int); void __thiscall a2(unsigned); void __thiscall grow(%s**, %s* const*); };" % (nm, nm),
            "extern int __cdecl x%08x(int, unsigned*, int, int);" % va]
    src += ["void FUN_%08x(I%08x* a, V%08x* v) {" % (va, va, va),
            "  v->a1((int)v->b, (int)v->e);",
            "  unsigned n = 0;",
            "  int t = a->gx()->q();", "  x%08x(t, &n, 1, 0);" % va,
            "  v->a2(n);",
            "  for (unsigned i = 0; i < n; ++i) {",
            "    %s* p = 0;" % nm,
            "    a->mk(0x%08x, &p, 0);" % A[0],
            "    if (v->e < v->c) { %s** q = v->e++; if (q) { *q = p; if (p) p->add(); } } else v->grow(v->e, &p);" % nm,
            "    if (p) p->rel();",
            "  }",
            "  a->fin();",
            "}"]
    return "\n".join(src), "?FUN_%08x@@YAXPAUI%08x@@PAUV%08x@@@Z" % (va, va, va)
