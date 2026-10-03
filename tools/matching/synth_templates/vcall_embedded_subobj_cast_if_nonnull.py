# "return p ? p->sub.Cast(ID) : 0;" -- virtual call through an embedded subobject at offset N[1]
# (lea ecx,[eax+off]; mov eax,[ecx]; mov edx,[eax+slot]; push id; call edx), null-checked arg.
PATTERN = 'mov eax, dword ptr [esp + N] ; test eax, eax ; je +N ; lea ecx, [eax + N] ; mov eax, dword ptr [ecx] ; mov edx, dword ptr [eax + N] ; push A ; call edx ; ret  ; xor eax, eax ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = ""
def emit(va, A, N):
    off, slot = N[1], N[-1] // 4
    t = "%08x" % va
    virt = "".join(" virtual void* s%d(unsigned id);" % i for i in range(slot)) + " virtual void* Cast(unsigned id);"
    src = ("struct S_%s {%s};\n"
           "struct C_%s { char pad[%d]; S_%s s; };\n"
           "void* FUN_%s(C_%s* p) {\n    if (p) return p->s.Cast(0x%08xu);\n    return 0;\n}") % (t, virt, t, off, t, t, t, A[0])
    return src, "?FUN_%s@@YAPAXPAUC_%s@@@Z" % (t, t)
