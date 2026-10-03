# (end - begin) / sizeof(T) on a vector-like {begin,end} via ecx; element size recovered from magic.
PATTERN = 'push esi ; mov esi, dword ptr [ecx + N] ; sub esi, dword ptr [ecx] ; mov eax, A ; imul esi ; add edx, esi ; sar edx, N ; mov eax, edx ; shr eax, N ; add eax, edx ; pop esi ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "struct VecRange { char* b; char* e; };\n"
def _size(m, s):
    for d in range(3, 5000):
        if (d - 1).bit_length() - 1 == s and (((1 << (32 + s)) + d - 1) // d) & 0xffffffff == m:
            return d
    raise ValueError
def emit(va, A, N):
    d = _size(A[0], N[1])
    return ("struct E_%08x { char c[%d]; };\nstruct V_%08x { E_%08x* b; E_%08x* e; };\n"
            "int __fastcall FUN_%08x(V_%08x* v) { return (int)(v->e - v->b); }" % (va, d, va, va, va, va, va),
            "?FUN_%08x@@YIHPAUV_%08x@@@Z" % (va, va))
