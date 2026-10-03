# int C::Get() { return p ? p->field : 0; }  (p at [this+off1], field at [p+off2])
PATTERN = 'mov eax, dword ptr [ecx + N] ; test eax, eax ; je +N ; mov eax, dword ptr [eax + N] ; ret  ; xor eax, eax ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    o1, o2 = N[0], N[1]
    c = "C_%08x" % va
    d = "D_%08x" % va
    src = ("#pragma pack(push, 1)\nstruct %s { char pad[0x%x]; int field; };\n"
           "struct %s { char pad[0x%x]; %s* p; int Get(); };\n#pragma pack(pop)\n"
           "int %s::Get() { return p ? p->field : 0; }" % (d, o2, c, o1, d, c))
    return src, "?Get@%s@@QAEHXZ" % c
