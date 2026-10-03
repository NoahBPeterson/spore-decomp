# Intrusive smart pointer operator=(T*): vcall slot A on new, store, vcall slot B on old, return this.
PATTERN = 'push ebx ; mov ebx, dword ptr [esp + N] ; push esi ; mov esi, ecx ; push edi ; mov edi, dword ptr [esi] ; cmp ebx, edi ; je +N ; test ebx, ebx ; je +N ; mov eax, dword ptr [ebx] ; mov edx, dword ptr [eax + N] ; mov ecx, ebx ; call edx ; mov dword ptr [esi], ebx ; test edi, edi ; je +N ; mov eax, dword ptr [edi] ; mov edx, dword ptr [eax + N] ; mov ecx, edi ; call edx ; pop edi ; mov eax, esi ; pop esi ; pop ebx ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    a, b = N[1] // 4, N[2] // 4
    v = "%08x" % va
    src = (
        "struct O_V { void** vt; };\n"
        "struct P_V { O_V* p; P_V& assign(O_V* q); };\n"
        "P_V& P_V::assign(O_V* q) {\n"
        "  O_V* old = p;\n"
        "  if (q != old) {\n"
        "    if (q) ((void(__thiscall*)(void*))q->vt[AA])(q);\n"
        "    p = q;\n"
        "    if (old) ((void(__thiscall*)(void*))old->vt[BB])(old);\n"
        "  }\n"
        "  return *this;\n"
        "}\n"
    ).replace("_V", "_" + v).replace("AA", str(a)).replace("BB", str(b))
    return src, "?assign@P_%s@@QAEAAU1@PAUO_%s@@@Z" % (v, v)
