PATTERN = 'mov eax, dword ptr [esp + N] ; mov ecx, dword ptr [esp + N] ; mov edx, dword ptr [ecx] ; mov edx, dword ptr [edx] ; push esi ; mov esi, dword ptr [eax + N] ; push edi ; mov edi, dword ptr [esp + N] ; mov eax, dword ptr [edi + N] ; add esi, dword ptr [edi + N] ; add eax, eax ; push N ; add eax, eax ; push eax ; call edx ; test eax, eax ; je +N ; mov ecx, dword ptr [esp + N] ; mov dword ptr [ecx + N], eax ; mov edx, dword ptr [edi + N] ; mov dword ptr [ecx + N], edx ; mov dword ptr [ecx], A ; xor ecx, ecx ; cmp dword ptr [edi + N], ecx ; jbe +N ; mov edx, dword ptr [esi] ; mov dword ptr [eax], edx ; inc ecx ; add esi, N ; add eax, N ; cmp ecx, dword ptr [edi + N] ; jb +N ; pop edi ; mov al, N ; pop esi ; ret  ; pop edi ; xor al, al ; pop esi ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ("class Al { public: virtual void* Alloc(unsigned, unsigned); };\n"
           "struct Src { unsigned pad0; char* base; };\n"
           "struct Rng { unsigned pad[4]; unsigned off; unsigned cnt; };\n"
           "struct Dst { void* vp; unsigned* data; unsigned cnt; };\n")
def emit(va, A, N):
    vt = "vt_%08x" % A[0]
    src = ("extern char %s[];\n"
           "bool FUN_%08x(Dst* d, Src* s, Rng* r, Al* a) {\n"
           "  unsigned* src = (unsigned*)(s->base + r->off);\n"
           "  unsigned* dst = (unsigned*)a->Alloc(r->cnt * 4, 4);\n"
           "  if (dst) {\n"
           "    d->data = dst; d->cnt = r->cnt; d->vp = %s;\n"
           "    for (unsigned i = 0; i < r->cnt; i++, src++, dst++) *dst = *src;\n"
           "    return true;\n  }\n  return false;\n}" % (vt, va, vt))
    return src, "?FUN_%08x@@YA_NPAUDst@@PAUSrc@@PAURng@@PAVAl@@@Z" % va
