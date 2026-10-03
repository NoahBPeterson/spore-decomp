# EASTL pop_heap_aux for intrusive_ptr<T>*: value = last[-1]; last[-1] = *first;
# adjust_heap(first, 0, (last-first)-1, 0, value, cmp)   (cdecl)
PATTERN = 'push ebx ; push ebp ; push esi ; mov esi, dword ptr [esp + N] ; mov ebx, dword ptr [esi - N] ; push edi ; test ebx, ebx ; je +N ; mov eax, dword ptr [ebx] ; mov edx, dword ptr [eax] ; mov ecx, ebx ; call edx ; mov eax, dword ptr [esp + N] ; mov edi, dword ptr [eax] ; mov ebp, dword ptr [esi - N] ; cmp edi, ebp ; je +N ; test edi, edi ; je +N ; mov edx, dword ptr [edi] ; mov eax, dword ptr [edx] ; mov ecx, edi ; call eax ; mov dword ptr [esi - N], edi ; test ebp, ebp ; je +N ; mov edx, dword ptr [ebp] ; mov eax, dword ptr [edx + N] ; mov ecx, ebp ; call eax ; mov ecx, dword ptr [esp + N] ; push ecx ; push ecx ; mov eax, esp ; mov dword ptr [eax], ebx ; test ebx, ebx ; je +N ; mov edx, dword ptr [ebx] ; mov eax, dword ptr [edx] ; mov ecx, ebx ; call eax ; mov eax, dword ptr [esp + N] ; sub esi, eax ; push N ; sar esi, N ; dec esi ; push esi ; push N ; push eax ; call EXT ; add esp, N ; test ebx, ebx ; je +N ; mov edx, dword ptr [ebx] ; mov eax, dword ptr [edx + N] ; mov ecx, ebx ; pop edi ; pop esi ; pop ebp ; pop ebx ; jmp eax ; pop edi ; pop esi ; pop ebp ; pop ebx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    s = "struct O_%08x { virtual void v0(); virtual void v1(); };\n" % va
    s = s.replace("v1();", "v1();")
    s += ("struct P_%08x { O_%08x* p; P_%08x(const P_%08x& o) : p(o.p) { if (p) p->v0(); }\n"
          "  P_%08x& operator=(const P_%08x& o) { O_%08x* q = o.p; O_%08x* old = p; if (q != old) { if (q) q->v0(); p = q; if (old) old->v1(); } return *this; }\n"
          "  ~P_%08x() { if (p) p->v1(); } };\n") % ((va,) * 9)
    s += "void H_%08x(P_%08x*, int, int, int, P_%08x, int);\n" % ((va,) * 3)
    s += ("void __cdecl F_%08x(P_%08x* first, P_%08x* last, int c) {\n"
          "  P_%08x v(last[-1]); last[-1] = first[0];\n"
          "  H_%08x(first, 0, (int)(last - first) - 1, 0, v, c); }\n") % ((va,) * 5)
    return s, "?F_%08x@@YAXPAUP_%08x@@0H@Z" % (va, va)
