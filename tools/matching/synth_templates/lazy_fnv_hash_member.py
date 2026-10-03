# __thiscall getter that lazily caches an FNV hash of a constant string in a member:
#   push esi; mov esi,ecx; cmp [esi+off],0; jne L; push flag; push basis; push str; call FNVHash;
#   add esp,0xc; mov [esi+off],eax; L: mov eax,[esi+off]; pop esi; ret
# Source: /O2 out-of-line member "unsigned C::Get() { if (!h) h = FNVHash(s, basis, flag); return h; }"
PATTERN = 'push esi ; mov esi, ecx ; cmp dword ptr [esi + N], N ; jne +N ; push N ; push A ; push A ; call EXT ; add esp, N ; mov dword ptr [esi + N], eax ; mov eax, dword ptr [esi + N] ; pop esi ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "unsigned int FNVHash(const char* s, unsigned int basis, int flag);\n"

def emit(va, A, N):
    basis, s = A
    off, flag = N[0], N[2]
    c = "C_%08x" % va
    src = ("extern const char s_%08x[];\n#pragma pack(push, 1)\n"
           "struct %s { char pad[0x%x]; unsigned int h; unsigned int Get(); };\n#pragma pack(pop)\n"
           "unsigned int %s::Get() { if (!h) h = FNVHash(s_%08x, 0x%X, %d); return h; }"
           % (s, c, off, c, s, basis, flag))
    return src, "?Get@%s@@QAEIXZ" % c
