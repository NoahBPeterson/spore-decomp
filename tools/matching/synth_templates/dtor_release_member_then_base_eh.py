# Non-virtual destructor D : B { pad; P m; } with EH frame: P's dtor calls virtual slot k of its pointer
# if non-null; then B's out-of-line dtor is called (B has no vptr write in D).
PATTERN = 'push -N ; push A ; mov eax, dword ptr fs:[N] ; push eax ; mov dword ptr fs:[N], esp ; push ecx ; push esi ; mov esi, ecx ; mov dword ptr [esp + N], esi ; mov ecx, dword ptr [esi + N] ; mov dword ptr [esp + N], N ; test ecx, ecx ; je +N ; mov eax, dword ptr [ecx] ; mov edx, dword ptr [eax + N] ; call edx ; mov ecx, esi ; mov dword ptr [esp + N], A ; call EXT ; mov ecx, dword ptr [esp + N] ; pop esi ; mov dword ptr fs:[N], ecx ; add esp, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GS-"]
PRELUDE = "struct Iface { virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); };\n"

def emit(va, A, N):
    # N order: -1, [esp+4], member off, [esp+N]=0x10 state, slot, ...
    off = N[4]; slot = N[7]
    c = "C_%08x" % va
    s = "struct B_%s { %s~B_%s(); };\n" % (c, ("char pad[%d]; " % off) if off else "", c)
    s += "struct P_%s { Iface* p; ~P_%s() { if (p) p->s%d(); } };\n" % (c, c, slot // 4)
    s += "struct %s : B_%s { P_%s m; ~%s(); };\n%s::~%s() {}" % (c, c, c, c, c, c)
    return s, "??1%s@@QAE@XZ" % c
