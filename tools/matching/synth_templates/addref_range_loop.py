# Range loop that calls vtable slot (AddRef-like) on a pointer member of each element; returns advanced dest.
PATTERN = 'push ebx ; mov ebx, dword ptr [esp + N] ; push esi ; mov esi, dword ptr [esp + N] ; cmp esi, ebx ; je +N ; push edi ; mov edi, dword ptr [esp + N] ; mov ecx, dword ptr [esi + N] ; test ecx, ecx ; je +N ; mov eax, dword ptr [ecx] ; mov edx, dword ptr [eax + N] ; call edx ; add esi, N ; add edi, N ; cmp esi, ebx ; jne +N ; mov eax, edi ; pop edi ; pop esi ; pop ebx ; ret  ; mov eax, dword ptr [esp + N] ; pop esi ; pop ebx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    off, vt, stride = N[3], N[4] // 4, N[5]
    s = "S_%08x" % va
    virt = "".join("virtual void v%d(); " % i for i in range(vt + 1))
    pad = "char pad[%d]; " % off if off else ""
    pad2 = "char pad2[%d]; " % (stride - off - 4) if stride - off - 4 > 0 else ""
    src = ("struct I_%08x { %s};\nstruct %s { %sI_%08x* p; %s};\n"
           "%s* FUN_%08x(%s* first, %s* last, %s* dest) {\n"
           "  for (; first != last; ++first, ++dest) { I_%08x* q = first->p; if (q) q->v%d(); }\n"
           "  return dest;\n}") % (va, virt, s, pad, va, pad2, s, va, s, s, s, va, vt)
    return src, "?FUN_%08x@@YAPAU%s@@PAU1@00@Z" % (va, s)
