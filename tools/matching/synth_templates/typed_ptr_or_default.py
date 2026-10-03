# thiscall: if type (u16 @0x12) is K or 0x10: if flags(@0x10)&0x30 return *(void**)this, else return type?this:0;
# otherwise return &global default.
PATTERN = 'movzx eax, word ptr [ecx + N] ; cmp ax, N ; je +N ; cmp ax, N ; je +N ; mov eax, A ; ret  ; test byte ptr [ecx + N], N ; je +N ; mov eax, dword ptr [ecx] ; ret  ; movzx eax, ax ; neg eax ; sbb eax, eax ; and eax, ecx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    c = "C_%08x" % va
    k = N[1]
    src = ("extern char g_%08x;\n#pragma pack(push, 1)\n"
           "struct %s { void *p; char pad[0xc]; unsigned char fl; char pad2; unsigned short type; void *Get(); };\n#pragma pack(pop)\n"
           "void *%s::Get() {\n  if (type != %d && type != 0x10) return &g_%08x;\n"
           "  if (fl & 0x30) return p;\n  return type ? this : 0;\n}" % (A[0], c, c, k, A[0]))
    return src, "?Get@%s@@QAEPAXXZ" % c
