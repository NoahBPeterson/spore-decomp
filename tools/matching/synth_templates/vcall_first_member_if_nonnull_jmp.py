# "void C::f() { if (p) p->vf(); }" with p at offset 0, virtual slot at byte offset N[0]
# -> mov ecx,[ecx]; test; je; mov eax,[ecx]; mov edx,[eax+slot]; jmp edx; ret
PATTERN = 'mov ecx, dword ptr [ecx] ; test ecx, ecx ; je +N ; mov eax, dword ptr [ecx] ; mov edx, dword ptr [eax + N] ; jmp edx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = ""

def emit(va, A, N):
    slot = N[-1] // 4
    t = "%08x" % va
    virt = "".join(" virtual void s%d();" % i for i in range(slot)) + " virtual void FUN_%s();" % t
    src = ("struct V_%s {%s};\n"
           "struct C_%s { V_%s* p; void FUN_%s(); };\n"
           "void C_%s::FUN_%s() { V_%s* q = p; if (q) q->FUN_%s(); }") % (t, virt, t, t, t, t, t, t, t)
    return src, "?FUN_%s@C_%s@@QAEXXZ" % (t, t)
