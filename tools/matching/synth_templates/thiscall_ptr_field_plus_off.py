# char* C::Get() { return ptr + K; }  -> mov eax,[ecx+off]; add eax,K; ret
PATTERN = 'mov eax, dword ptr [ecx + N] ; add eax, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    off, k = N[0], N[1]
    c = "C_%08x" % va
    src = ("#pragma pack(push, 1)\nstruct %s { char pad[0x%x]; char* field; char* Get(); };\n#pragma pack(pop)\n"
           "char* %s::Get() { return field + 0x%x; }" % (c, off, c, k))
    return src, "?Get@%s@@QAEPADXZ" % c
