# Backward copy loop (*--dest = *--last) of a struct { u32 a; [pad]; B b; } whose
# implicit copy-assign copies a then calls B's out-of-line operator= on the sub-object at +off.
PATTERN = 'push ebx ; mov ebx, dword ptr [esp + N] ; push esi ; mov esi, dword ptr [esp + N] ; cmp esi, ebx ; je +N ; push edi ; mov edi, dword ptr [esp + N] ; mov eax, dword ptr [esi - N] ; sub esi, N ; lea ecx, [esi + N] ; sub edi, N ; push ecx ; lea ecx, [edi + N] ; mov dword ptr [edi], eax ; call EXT ; cmp esi, ebx ; jne +N ; mov eax, edi ; pop edi ; pop esi ; pop ebx ; ret  ; mov eax, dword ptr [esp + N] ; pop esi ; pop ebx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    size, off = N[3], N[5]
    s, b = "S_%08x" % va, "B_%08x" % va
    pad = "" if off == 8 else "".join("unsigned p%d; " % i for i in range((off - 4) // 4))
    al = "__declspec(align(8)) " if off == 8 else ""
    tail = "".join("unsigned q%d; " % i for i in range((size - off) // 4 - 1))
    src = ("%sstruct %s { %s& operator=(const %s&); %s };\n"
           "struct %s { unsigned a; %s %s b; };\n"
           "%s* FUN_%08x(%s* first, %s* last, %s* dest) {\n"
           "    while (last != first) *--dest = *--last;\n"
           "    return dest;\n}\n") % (al, b, b, b, "unsigned x; " + tail, s, pad, b, s, va, s, s, s)
    return src, "?FUN_%08x@@YAPAU%s@@PAU1@00@Z" % (va, s)
