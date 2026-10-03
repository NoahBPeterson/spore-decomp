# (final vptr stores share one vtable address, so written explicitly) Non-deleting dtor of a 3-base MI class (bases at 0, 4, 0xc) with an array of interface pointers released in a forward loop, then base vptrs reset (last base first).
PATTERN = 'push ebx ; push esi ; push edi ; mov edi, ecx ; mov dword ptr [edi], A ; mov dword ptr [edi + N], A ; mov dword ptr [edi + N], A ; lea esi, [edi + N] ; mov ebx, N ; cmp dword ptr [esi], N ; je +N ; mov ecx, dword ptr [esi] ; mov eax, dword ptr [ecx] ; mov edx, dword ptr [eax + N] ; call edx ; add esi, N ; sub ebx, N ; jne +N ; mov eax, A ; mov dword ptr [edi + N], eax ; mov dword ptr [edi + N], eax ; mov dword ptr [edi], eax ; pop edi ; pop esi ; pop ebx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/TP"]
PRELUDE = "struct Iface { virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); };\nextern char vt_shared[];\n"

def emit(va, A, N):
    moff, cnt = N[2], N[3]
    c = "C_%08x" % va
    pad = ("char pad[%d]; " % (moff - 0x10)) if moff > 0x10 else ""
    src = ("struct X_%(c)s { virtual void fx(); };\n"
           "struct Y_%(c)s { virtual void fy(); char p[4]; };\n"
           "struct Z_%(c)s { virtual void fz(); };\n"
           "struct %(c)s : X_%(c)s, Y_%(c)s, Z_%(c)s { %(pad)sIface* m[%(cnt)d]; virtual ~%(c)s(); };\n"
           "%(c)s::~%(c)s() { for (int i = 0; i < %(cnt)d; i++) if (m[i]) m[i]->s1(); "
           "void** p = (void**)this; p[3] = vt_shared; p[1] = vt_shared; p[0] = vt_shared; }" % dict(c=c, pad=pad, cnt=cnt))
    return src, "??1%s@@UAE@XZ" % c
