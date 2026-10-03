# vector<T*>::erase(first,last) for intrusive ptrs: p = copy(last,end,first); call vslot on each [p,end); end -= (last-first)
PATTERN = 'push ebx ; mov ebx, dword ptr [esp + N] ; push ebp ; push esi ; push edi ; mov edi, ecx ; mov ecx, dword ptr [esp + N] ; mov eax, dword ptr [edi + N] ; push ecx ; push eax ; push ebx ; call EXT ; mov ebp, dword ptr [edi + N] ; add esp, N ; mov esi, eax ; cmp eax, ebp ; jae +N ; mov ecx, dword ptr [esi] ; test ecx, ecx ; je +N ; mov edx, dword ptr [ecx] ; mov eax, dword ptr [edx + N] ; call eax ; add esi, N ; cmp esi, ebp ; jb +N ; mov eax, dword ptr [esp + N] ; sub ebx, eax ; sar ebx, N ; neg ebx ; add ebx, ebx ; add ebx, ebx ; add dword ptr [edi + N], ebx ; pop edi ; pop esi ; pop ebp ; pop ebx ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    slot = [n for n in N if n % 4 == 0 and n >= 4 and n not in (4,)]
    vt = N[5] // 4
    s = "struct I_%08x { %s};\n" % (va, "".join("virtual void v%d(); " % i for i in range(vt + 1)))
    s += "struct P_%08x { I_%08x* p; };\n" % (va, va)
    s += "P_%08x* X_%08x(P_%08x*, P_%08x*, P_%08x*);\n" % ((va,)*5)
    s += "struct V_%08x { int a; P_%08x* e; void f(P_%08x*, P_%08x*); };\n" % ((va,)*4)
    s += ("void V_%08x::f(P_%08x* first, P_%08x* last) {\n  P_%08x* p = X_%08x(last, e, first);\n  P_%08x* end = e;\n"
          "  for (P_%08x* i = p; i < end; ++i) if (i->p) i->p->v%d();\n  e = (P_%08x*)((char*)e - ((char*)last - (char*)first)); }\n") % ((va,)*7 + (vt,va))
    return s, "?f@V_%08x@@QAEXPAUP_%08x@@0@Z" % (va, va)
