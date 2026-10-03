# Insertion sort over intrusive pointers (v0 slot0 / v1 slot1) with a by-value 4-byte comparator object (/O2).
PATTERN = 'push ecx ; mov eax, dword ptr [esp + N] ; push edi ; mov edi, dword ptr [esp + N] ; cmp edi, eax ; je +N ; push ebx ; lea ebx, [edi + N] ; mov dword ptr [esp + N], ebx ; cmp ebx, eax ; je +N ; push ebp ; push esi ; jmp +N ; mov edi, dword ptr [esp + N] ; mov ebp, dword ptr [ebx] ; test ebp, ebp ; je +N ; mov eax, dword ptr [ebp] ; mov edx, dword ptr [eax] ; mov ecx, ebp ; call edx ; mov esi, ebx ; cmp ebx, edi ; je +N ; nop  ; mov eax, dword ptr [esi - N] ; push eax ; push ebp ; lea ecx, [esp + N] ; call EXT ; test al, al ; je +N ; mov edi, dword ptr [esi - N] ; mov ebx, dword ptr [esi] ; cmp edi, ebx ; je +N ; test edi, edi ; je +N ; mov eax, dword ptr [edi] ; mov edx, dword ptr [eax] ; mov ecx, edi ; call edx ; mov dword ptr [esi], edi ; test ebx, ebx ; je +N ; mov eax, dword ptr [ebx] ; mov edx, dword ptr [eax + N] ; mov ecx, ebx ; call edx ; mov ebx, dword ptr [esp + N] ; add esi, -N ; cmp esi, dword ptr [esp + N] ; jne +N ; mov edi, dword ptr [esi] ; cmp ebp, edi ; je +N ; test ebp, ebp ; je +N ; mov eax, dword ptr [ebp] ; mov edx, dword ptr [eax] ; mov ecx, ebp ; call edx ; mov dword ptr [esi], ebp ; test edi, edi ; je +N ; mov eax, dword ptr [edi] ; mov edx, dword ptr [eax + N] ; mov ecx, edi ; call edx ; test ebp, ebp ; je +N ; mov eax, dword ptr [ebp] ; mov edx, dword ptr [eax + N] ; mov ecx, ebp ; call edx ; add ebx, N ; mov dword ptr [esp + N], ebx ; cmp ebx, dword ptr [esp + N] ; jne +N ; pop esi ; pop ebp ; pop ebx ; pop edi ; pop ecx ; ret '
FLAGS = ["/O2","/MD","/TP","/Gs"]
PRELUDE = """struct O { virtual void v0(); virtual void v1(); };
struct P { O* p;
  P(const P& o){ p=o.p; if(p) p->v0(); }
  ~P(){ if(p) p->v1(); }
  P& operator=(O* np){ O* old=p; if(np!=old){ if(np) np->v0(); p=np; if(old) old->v1(); } return *this; } };
struct C { int x; bool operator()(O* a, O* b) const; };
"""
def emit(va, A, N):
    src = ("void FUN_%08x(P* first, P* last, C comp) {\n"
           "  if (first == last) return;\n"
           "  for (P* i = first + 1; i != last; ++i) {\n"
           "    P v = *i;\n"
           "    P* j = i;\n"
           "    for (; j != first && comp(v.p, j[-1].p); --j) *j = j[-1].p;\n"
           "    *j = v.p;\n"
           "  }\n}") % va
    return src, "?FUN_%08x@@YAXPAUP@@0UC@@@Z" % va
