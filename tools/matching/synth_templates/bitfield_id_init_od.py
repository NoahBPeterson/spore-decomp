# Dynamic initializer of a file-scope 32-bit global in an unoptimized (/Od /Ob1) module, built from
# a temporary of a bitfield struct: inline ctor zeroes the word, sets the 2-bit top field to 1 and
# two 8-bit fields (bits 16..23 and 8..15) from ctor args, then the temporary is converted to
# unsigned and stored: `unsigned g = BitfieldId(b, c);`. Constructing the global directly as the
# bitfield type writes straight into the global (no [ebp-4] temp) and does not match.
PATTERN = 'push ebp ; mov ebp, esp ; push ecx ; mov dword ptr [ebp - N], N ; mov eax, dword ptr [ebp - N] ; and eax, A ; or eax, A ; mov dword ptr [ebp - N], eax ; mov ecx, N ; and ecx, N ; shl ecx, N ; mov edx, dword ptr [ebp - N] ; and edx, A ; or edx, ecx ; mov dword ptr [ebp - N], edx ; mov eax, N ; and eax, N ; shl eax, N ; mov ecx, dword ptr [ebp - N] ; and ecx, A ; or ecx, eax ; mov dword ptr [ebp - N], ecx ; mov edx, dword ptr [ebp - N] ; mov dword ptr [A], edx ; mov esp, ebp ; pop ebp ; ret '
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """struct BitfieldId {
    unsigned lo : 8; unsigned c : 8; unsigned b : 8; unsigned x : 6; unsigned top : 2;
    BitfieldId(unsigned bb, unsigned cc) { *(unsigned*)this = 0; top = 1; b = bb; c = cc; }
    operator unsigned() const { return *(const unsigned*)this; }
};
"""
def emit(va, A, N):
    m0, m1, m2, m3, dst = A
    b, c = N[4], N[9]
    if (m0, m1, m2, m3) != (0x3fffffff, 0x40000000, 0xff00ffff, 0xffff00ff) or N[5:7] != [255, 16] or N[10:12] != [255, 8]:
        return "// unsupported variant", "?FUN_%08x@@YAXXZ" % va
    return "unsigned g_%08x = BitfieldId(0x%x, 0x%x);" % (dst, b, c), "??__Eg_%08x@@YAXXZ" % dst
