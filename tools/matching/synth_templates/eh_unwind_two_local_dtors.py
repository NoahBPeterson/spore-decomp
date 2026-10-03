# Two C++ EH unwind funclets + __ehhandler of a /GS- function (shape: .text$x tail of an EH function):
#   lea ecx,[ebp-N0]; jmp ~A ; lea ecx,[ebp-N1]; jmp ~B ; mov eax,__ehfuncinfo$f; jmp ___CxxFrameHandler3
# The EH registration occupies [ebp-0xC..ebp); the first funclet destroys the first-constructed object.
# cl /O2 frame layout of address-taken locals: in small frames, sorted by size (largest nearest ebp);
# in larger frames, by reference density (refs/size, densest nearest esp). Ties go to declaration order.
# So the object sizes come from the offsets, and EXTRA eh_ext(&low) calls pin the lower object down.
# Special shapes:
#   N0 == N1: one object D : A whose inline ctor can throw (funclets for the A base and the whole D).
#   N0 < N1 with the lower gap larger than the upper object: E { pad; A m; } with an inline throwing
#     ctor (funclet for member m first, then for the whole E).
#   N0 > N1 with a bigger than b in a small frame: shrink a and fill the gap with address-taken
#     uint32_t pads sized between a and b (4 refs each, so they stay below b in big frames too).
#   adjacent byte-sized objects (0x15/0x16, 0x26/0x27): uint32_t p[] + char q[] pads above them.
# Shape-equivalent: the parent body is a stand-in; only the funclet+handler bytes are verified.
PATTERN = 'lea ecx, [ebp - N] ; jmp EXT ; lea ecx, [ebp - N] ; jmp EXT ; mov eax, A ; jmp EXT'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GS-"]
EXTRA = 10
PRELUDE = "typedef unsigned int uint32_t;\nvoid eh_ext(void*);\n"

def field(size):
    return "uint32_t a[%d];" % (size // 4) if size % 4 == 0 else "char a[%d];" % size

def chunks(total, hi, lo):
    """split total (a multiple of 4) into multiples of 4, each in (lo, hi]; None if impossible"""
    if total == 0:
        return []
    for n in range(max(1, -(-total // hi)), total // 4 + 1):
        base = (total // n) // 4 * 4
        parts = [base] * n
        for i in range((total - base * n) // 4):
            parts[i] += 4
        if all(lo < q <= hi for q in parts):
            return parts
    return None

def emit(va, A, N):
    n0, n1 = N[0], N[1]
    ta, tb = "SA_%08x" % va, "SB_%08x" % va
    if n0 == n1:
        src = "struct %s { %s %s(); ~%s(); };\n" % (ta, field(max(n0 - 0xC, 1)), ta, ta)
        src += "struct %s : %s { %s() { eh_ext(this); } };\n" % (tb, ta, tb)
        src += "void FUN_%08x() { %s d; eh_ext(&d); }" % (va, tb)
        return src, "__unwindfunclet$?FUN_%08x@@YAXXZ$1" % va
    if n0 < n1 and n1 - n0 > n0 - 0xC:   # member funclet (higher) then whole object (lower)
        gap = n1 - n0
        pad = "uint32_t pad[%d];" % (gap // 4) if gap % 4 == 0 else "char pad[%d];" % gap
        src = "struct %s { %s %s(); ~%s(); };\n" % (ta, field(n0 - 0xC), ta, ta)
        src += "struct %s { %s %s m; %s() { eh_ext(this); } ~%s(); };\n" % (tb, pad, ta, tb, tb)
        src += "void FUN_%08x() { %s e; eh_ext(&e); }" % (va, tb)
        return src, "__unwindfunclet$?FUN_%08x@@YAXXZ$1" % va
    decls, extra, prefs = [], EXTRA, 1   # address-taken non-EH pads: (declaration, name)
    if n0 < n1:   # a above b
        sa, sb, low = n0 - 0xC, n1 - n0, "b"
        if sb == 1 and sa % 4:   # two byte-sized objects below a 4-aligned pad block
            area = sa - 1
            sa, extra = 1, 0
            decls.append(("uint32_t p[%d];" % (area // 4), "p"))
            if area % 4:
                decls.append(("char q[%d];" % (area % 4), "q"))
    else:         # b above a
        sb, sa, low = n1 - 0xC, n0 - n1, "a"
        if sa > sb and n0 < 0xA0:   # small frame: pure size order; shrink a, pads (sa, sb) between
            gap = n0 - n1
            small = gap % 4 or 4
            parts = chunks(gap - small, sb - 4, small) if sb > 4 else None
            if parts is not None:
                sa, prefs = small, 4   # denser than b, so b stays on top in big frames too
                decls += [("uint32_t p%d[%d];" % (i, q // 4), "p%d" % i) for i, q in enumerate(parts)]
    src = "struct %s { %s %s(); ~%s(); };\n" % (ta, field(sa), ta, ta)
    src += "struct %s { %s %s(); ~%s(); };\n" % (tb, field(sb), tb, tb)
    uses = "eh_ext(&a); eh_ext(&b); " + ("eh_ext(&%s); " % low) * extra
    uses += "".join("eh_ext(%s); " % n for _, n in decls) * prefs
    pre = "".join(d + " " for d, _ in decls)
    src += "void FUN_%08x() { %s%s a; %s b; %s}" % (va, pre, ta, tb, uses)
    return src, "__unwindfunclet$?FUN_%08x@@YAXXZ$0" % va
