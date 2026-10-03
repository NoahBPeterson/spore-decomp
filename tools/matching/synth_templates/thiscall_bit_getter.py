# __thiscall getter of one flag bit: mov eax,[ecx+off]; shr eax,n; and al,1; ret
# Source: bool C::Get() { unsigned char r = (field >> n) & 1; return r; } (the uchar local gives "and al,1"; a direct bool return gives "and eax,1").
PATTERN = "mov eax, dword ptr [ecx + N] ; shr eax, N ; and al, N ; ret "
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    off, sh = N[0], N[1]
    c = "C_%08x" % va
    src = ("#pragma pack(push, 1)\nstruct %s { char pad[0x%x]; unsigned int field; bool Get(); };\n#pragma pack(pop)\n"
           "bool %s::Get() { unsigned char r = (field >> %d) & 1; return r; }" % (c, off, c, sh))
    return src, "?Get@%s@@QAE_NXZ" % c
