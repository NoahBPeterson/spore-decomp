# "int C::f() { if (p && p->vf()) return 1; return 0; }" p at N[0], slot byte offset N[1]
# -> mov ecx,[ecx+off]; test; je; mov eax,[ecx]; mov edx,[eax+slot]; call edx; test al,al; je; mov eax,1; ret; xor eax,eax; ret
PATTERN = 'mov ecx, dword ptr [ecx + N] ; test ecx, ecx ; je +N ; mov eax, dword ptr [ecx] ; mov edx, dword ptr [eax + N] ; call edx ; test al, al ; je +N ; mov eax, N ; ret  ; xor eax, eax ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = ""

def emit(va, A, N):
    off, slot = N[0], N[1] // 4
    t = "%08x" % va
    pad = " unsigned pad[%d];" % (off // 4) if off else ""
    virt = "".join(" virtual void s%d();" % i for i in range(slot)) + " virtual bool v();"
    src = ("struct V_%s {%s};\n"
           "struct C_%s {%s V_%s* p; int FUN_%s(); };\n"
           "int C_%s::FUN_%s() { V_%s* q = p; if (q && q->v()) return 1; return 0; }") % (t, virt, t, pad, t, t, t, t, t)
    return src, "?FUN_%s@C_%s@@QAEHXZ" % (t, t)
