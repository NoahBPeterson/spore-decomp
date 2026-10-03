# Scalar deleting dtor of D : Base with inline ~D(){} that destroys a member at offset N (out-of-line dtor)
# then the base: lea ecx,[esi+N]; mov [esi],vftable; call ~Member; mov ecx,esi; call ~Base; delete.
PATTERN = 'push esi ; mov esi, ecx ; lea ecx, [esi + N] ; mov dword ptr [esi], A ; call EXT ; mov ecx, esi ; call EXT ; test byte ptr [esp + N], N ; je +N ; push esi ; call EXT ; add esp, N ; mov eax, esi ; pop esi ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/TP"]
PRELUDE = "struct Base { Base(); virtual ~Base(); };\nstruct Mem { ~Mem(); };\n"

def emit(va, A, N):
    c = "C_%08x" % va
    pad = (N[0] - 4) // 4
    padf = ("unsigned pad[%d]; " % pad) if pad > 0 else ""
    src = ("struct %s : Base { %sMem m; %s(); virtual ~%s() {} };\n"
           "%s::%s() {}" % (c, padf, c, c, c, c))
    return src, "??_G%s@@UAEPAXI@Z" % c
