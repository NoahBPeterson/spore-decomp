# unsigned variant of vec_bounds_checked_at_or_zero (jae, no sign test)
# __thiscall "int C::At(int i) { if (i >= 0 && i < v.size()) return v[i].v; return 0; }"
# v is an embedded vector-like member {begin,end} at fixed offset with inline size() and non-const operator[].
# (Plain "e - b" members get CSE'd and miss the begin reload; the inline-method member form matches.)
# stride 4 -> int element, 8 -> struct whose first dword is returned. N = [4, endoff, beginoff, shift, beginoff, scale, ret]
PATTERN = 'mov edx, dword ptr [ecx + N] ; sub edx, dword ptr [ecx + N] ; mov eax, dword ptr [esp + N] ; sar edx, N ; cmp eax, edx ; jae +N ; mov ecx, dword ptr [ecx + N] ; mov eax, dword ptr [ecx + eax*N] ; ret N ; xor eax, eax ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    eo, bo, scale = N[0], N[1], N[5]
    c = "C_%08x" % va
    e = "E_%08x" % va
    v = "V_%08x" % va
    el = "struct %s { int v; %s };\n" % (e, "int p;" if scale == 8 else "")
    if eo >= bo:
        vec = "%s *b; %s%s *e;" % (e, ("unsigned pad[%d]; " % ((eo - bo - 4) // 4)) if eo - bo > 4 else "", e)
        lead = bo
    else:
        vec = "%s *e; %s%s *b;" % (e, ("unsigned pad[%d]; " % ((bo - eo - 4) // 4)) if bo - eo > 4 else "", e)
        lead = eo
    pad = ("unsigned pad0[%d]; " % (lead // 4)) if lead > 0 else ""
    src = (el + "struct %s { %s unsigned size() const { return e - b; } %s& operator[](unsigned i) { return b[i]; } };\n"
           "struct %s { %s%s m; int At(unsigned i); };\n"
           "int %s::At(unsigned i) { if (i < m.size()) return m[i].v; return 0; }"
           % (v, vec, e, c, pad, v, c))
    return src, "?At@%s@@QAEHI@Z" % c
