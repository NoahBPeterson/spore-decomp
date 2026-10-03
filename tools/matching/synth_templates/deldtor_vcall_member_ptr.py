# Scalar deleting dtor of a class whose member (own inline dtor; vptr store then precedes) calls virtual slot K on pointer at offset N if non-null:
#   push esi; mov esi,ecx; mov [esi],vftable; mov ecx,[esi+N]; test; je; mov eax,[ecx]; mov edx,[eax+K]; call edx; delete.
PATTERN = 'push esi ; mov esi, ecx ; mov dword ptr [esi], A ; mov ecx, dword ptr [esi + N] ; test ecx, ecx ; je +N ; mov eax, dword ptr [ecx] ; mov edx, dword ptr [eax + N] ; call edx ; test byte ptr [esp + N], N ; je +N ; push esi ; call EXT ; add esp, N ; mov eax, esi ; pop esi ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    c = "C_%08x" % va
    off, slot = N[0], N[1]
    pad = (off - 4) // 4
    padf = ("unsigned pad[%d]; " % pad) if pad > 0 else ""
    k = slot // 4
    vf = " ".join("virtual void f%d();" % i for i in range(k + 1))
    src = ("struct I_%08x { %s };\n"
           "struct H_%08x { I_%08x* p; ~H_%08x() { if (p) p->f%d(); } };\n"
           "struct %s { %sH_%08x h; %s(); virtual ~%s() {} };\n"
           "%s::%s() {}" % (va, vf, va, va, va, k, c, padf, va, c, c, c, c))
    return src, "??_G%s@@UAEPAXI@Z" % c
