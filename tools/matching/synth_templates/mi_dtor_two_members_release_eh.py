# Non-deleting destructor with EH frame of class D : B1, B2 { pad; P lo; P hi; } where P has a dtor
# that calls virtual slot k of its pointer if non-null. Bases are polymorphic with trivial inline dtors;
# vptrs are re-set at the end (offset 0 first, then the second base).
PATTERN = 'push -N ; push A ; mov eax, dword ptr fs:[N] ; push eax ; mov dword ptr fs:[N], esp ; push ecx ; push esi ; mov esi, ecx ; mov dword ptr [esp + N], esi ; mov dword ptr [esi], A ; mov dword ptr [esi + N], A ; mov ecx, dword ptr [esi + N] ; mov dword ptr [esp + N], N ; test ecx, ecx ; je +N ; mov eax, dword ptr [ecx] ; mov edx, dword ptr [eax + N] ; call edx ; mov ecx, dword ptr [esi + N] ; mov byte ptr [esp + N], N ; test ecx, ecx ; je +N ; mov eax, dword ptr [ecx] ; mov edx, dword ptr [eax + N] ; call edx ; mov ecx, dword ptr [esp + N] ; mov dword ptr [esi], A ; mov dword ptr [esi + N], A ; pop esi ; mov dword ptr fs:[N], ecx ; add esp, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GS-"]
PRELUDE = "struct Iface { virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); };\n"

def emit(va, A, N):
    off2, hi, slot_hi, lo, slot_lo = N[4], N[5], N[8], N[9], N[12]
    c = "C_%08x" % va
    pad1 = ("char pad1[%d]; " % (off2 - 4)) if off2 > 4 else ""
    mlo = min(hi, lo)
    pad2 = ("char pad2[%d]; " % (mlo - off2 - 4)) if mlo > off2 + 4 else ""
    gap = abs(hi - lo) - 4
    pad3 = ("char pad3[%d]; " % gap) if gap > 0 else ""
    def P(n, slot):
        return "struct P%s_%s { Iface* p; ~P%s_%s() { if (p) p->s%d(); } };\n" % (n, c, n, c, slot // 4)
    PH, PL = "H", "L"
    mem = {hi: ("H", slot_hi), lo: ("L", slot_lo)}
    src = "struct X_%s { virtual ~X_%s() {} %s};\nstruct Y_%s { virtual ~Y_%s() {} %s};\n" % (c, c, pad1, c, c, pad2)
    src += P("H", slot_hi) + P("L", slot_lo)
    decl = ""
    for o in sorted(mem):
        n = mem[o][0]
        decl += "P%s_%s m%s; " % (n, c, n)
        if o == min(hi, lo): decl += pad3
    src += "struct %s : X_%s, Y_%s { %s%s(); ~%s(); };\n%s::~%s() {}" % (c, c, c, decl, c, c, c, c)
    return src, "??1%s@@UAE@XZ" % c
