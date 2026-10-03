# "bool C::f(int a..) { if (p) return p->vf(a..); return false; }" p at offset N[0], slot byte offset N[1], ret N[2]
# -> mov ecx,[ecx+off]; test; je; mov eax,[ecx]; mov eax,[eax+slot]; jmp eax; xor al,al; ret n
PATTERN = 'mov ecx, dword ptr [ecx + N] ; test ecx, ecx ; je +N ; mov eax, dword ptr [ecx] ; mov eax, dword ptr [eax + N] ; jmp eax ; xor al, al ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = ""

def emit(va, A, N):
    off, slot, n = N[0], N[1] // 4, N[2] // 4
    t = "%08x" % va
    params = ", ".join("int a%d" % i for i in range(n))
    args = ", ".join("a%d" % i for i in range(n))
    pad = " unsigned pad[%d];" % (off // 4) if off else ""
    virt = "".join(" virtual void s%d();" % i for i in range(slot)) + " virtual bool FUN_%s(%s);" % (t, params)
    src = ("struct V_%s {%s};\n"
           "struct C_%s {%s V_%s* p; bool FUN_%s(%s); };\n"
           "bool C_%s::FUN_%s(%s) { V_%s* q = p; if (q) return q->FUN_%s(%s); return false; }") % (
           t, virt, t, pad, t, t, params, t, t, params, t, t, args)
    return src, "?FUN_%s@C_%s@@QAE_N%s@Z" % (t, t, "H" * n if n else "XZ"[:0] + "")
