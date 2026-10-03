# (end - begin) / sizeof(E) for non-power-of-two element sizes: imul magic, sar, sign fixup
PATTERN = 'mov edx, dword ptr [ecx + N] ; sub edx, dword ptr [ecx + N] ; mov eax, A ; imul edx ; sar edx, N ; mov eax, edx ; shr eax, N ; add eax, edx ; ret '
FLAGS = ["/O2", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    end, beg, sh = N[0], N[1], N[2]
    magic = A[0]
    if magic >= 1 << 31: magic -= 1 << 32
    sz = round((1 << (32 + sh)) / magic)
    s = ("struct S_%08x { char pad[%d]; struct E { char b[%d]; } *mBegin; E *mEnd; int Count() const; };\n"
         "int S_%08x::Count() const { return (int)(mEnd - mBegin); }" % (va, beg, sz, va))
    return s, "?Count@S_%08x@@QBEHXZ" % va
