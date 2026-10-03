# (end - begin) element count of two adjacent pointer members at [ecx+N]; element size 4/8/16
PATTERN = 'mov eax, dword ptr [ecx + N] ; sub eax, dword ptr [ecx + N] ; sar eax, N ; ret '
FLAGS = ["/O2", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    end, beg, sh = N[0], N[1], N[2]
    sz = 1 << sh
    s = ("struct S_%08x { char pad[%d]; struct E { char b[%d]; } *mBegin; E *mEnd; int Count() const; };\n"
         "int S_%08x::Count() const { return (int)(mEnd - mBegin); }" % (va, beg, sz, va))
    return s, "?Count@S_%08x@@QBEHXZ" % va
