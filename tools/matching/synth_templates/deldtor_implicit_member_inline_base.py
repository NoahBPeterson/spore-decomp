# Scalar deleting dtor of D : Base (Base has inline virtual ~Base(){}), D has a member at offset N with an
# out-of-line dtor and an IMPLICIT dtor: lea ecx,[esi+N]; call ~Mem; test; mov [esi],Base vftable; je; delete.
# (An explicit inline ~D(){} would store D's vptr first; the implicit one does not.) /EHsc must be absent.
PATTERN = 'push esi ; mov esi, ecx ; lea ecx, [esi + N] ; call EXT ; test byte ptr [esp + N], N ; mov dword ptr [esi], A ; je +N ; push esi ; call EXT ; add esp, N ; mov eax, esi ; pop esi ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/TP"]
PRELUDE = "struct Mem { ~Mem(); };\nstruct Base { virtual ~Base() {} virtual void g(); };\n"

def emit(va, A, N):
    c = "C_%08x" % va
    pad = (N[0] - 4) // 4
    padf = ("unsigned pad[%d]; " % pad) if pad > 0 else ""
    src = ("struct %s : Base { %sMem m; %s(); };\n"
           "%s::%s() {}" % (c, padf, c, c, c))
    return src, "??_G%s@@UAEPAXI@Z" % c
