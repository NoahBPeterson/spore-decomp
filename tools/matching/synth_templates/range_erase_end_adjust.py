# Range-erase style member: r = h1(last, end, first); h2(r, end); end += last-first; return first. Element stride varies.
PATTERN = 'push ebx ; mov ebx, dword ptr [esp + N] ; push esi ; push edi ; mov edi, dword ptr [esp + N] ; mov esi, ecx ; mov eax, dword ptr [esi + N] ; push ebx ; push eax ; push edi ; call EXT ; mov ecx, dword ptr [esi + N] ; add esp, N ; push ecx ; push eax ; mov ecx, esi ; call EXT ; sub edi, ebx ; mov eax, A ; imul edi ; sar edx, N ; mov eax, edx ; shr eax, N ; add eax, edx ; lea edx, [eax + eax*N] ; add edx, edx ; add edx, edx ; add edx, edx ; add dword ptr [esi + N], edx ; pop edi ; pop esi ; mov eax, ebx ; pop ebx ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    off = N[2]
    stride = (N[7] + 1) * 8
    s = "S_%08x" % va
    t = "T_%08x" % va
    src = ("struct %s { char b[%d]; };\n"
           "%s* H1_%08x(%s*, %s*, %s*);\n"
           "struct %s { char pad[%d]; %s* e; void H2_%08x(%s*, %s*);\n"
           "  %s* FUN_%08x(%s* f, %s* l); };\n"
           "%s* %s::FUN_%08x(%s* f, %s* l) { %s* r = H1_%08x(l, e, f); H2_%08x(r, e); e -= (l - f); return f; }"
           ) % (t, stride, t, va, t, t, t, s, off, t, va, t, t, t, va, t, t, t, s, va, t, t, t, va, va)
    return src, "?FUN_%08x@%s@@QAEPAU%s@@PAU2@0@Z" % (va, s, t)
