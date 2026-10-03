# EASTL partial_sort over intrusive pointers (AddRef slot0 / Release slot1), by-value 4-byte comparator (/O2).
# make_heap(first,middle,comp); for i in [middle,last): if comp(*i,*first) pop_heap-inline; sort_heap(first,middle,comp)
PATTERN = 'mov eax, dword ptr [esp + N] ; push ebx ; mov ebx, dword ptr [esp + N] ; push ebp ; push esi ; mov esi, dword ptr [esp + N] ; push edi ; push eax ; push ebx ; push esi ; call EXT ; add esp, N ; cmp ebx, dword ptr [esp + N] ; jae +N ; mov eax, dword ptr [esi] ; mov ecx, dword ptr [ebx] ; push eax ; push ecx ; lea ecx, [esp + N] ; call EXT ; test al, al ; je +N ; mov edi, dword ptr [ebx] ; test edi, edi ; je +N ; mov edx, dword ptr [edi] ; mov eax, dword ptr [edx] ; mov ecx, edi ; call eax ; mov esi, dword ptr [esi] ; mov ebp, dword ptr [ebx] ; cmp esi, ebp ; je +N ; test esi, esi ; je +N ; mov edx, dword ptr [esi] ; mov eax, dword ptr [edx] ; mov ecx, esi ; call eax ; mov dword ptr [ebx], esi ; test ebp, ebp ; je +N ; mov edx, dword ptr [ebp] ; mov eax, dword ptr [edx + N] ; mov ecx, ebp ; call eax ; mov ecx, dword ptr [esp + N] ; push ecx ; push ecx ; mov eax, esp ; mov dword ptr [eax], edi ; test edi, edi ; je +N ; mov edx, dword ptr [edi] ; mov eax, dword ptr [edx] ; mov ecx, edi ; call eax ; mov eax, dword ptr [esp + N] ; mov ecx, dword ptr [esp + N] ; sub ecx, eax ; push N ; sar ecx, N ; push ecx ; push N ; push eax ; call EXT ; add esp, N ; test edi, edi ; je +N ; mov edx, dword ptr [edi] ; mov eax, dword ptr [edx + N] ; mov ecx, edi ; call eax ; mov esi, dword ptr [esp + N] ; add ebx, N ; cmp ebx, dword ptr [esp + N] ; jb +N ; mov ebx, dword ptr [esp + N] ; mov ecx, dword ptr [esp + N] ; push ecx ; push ebx ; push esi ; call EXT ; add esp, N ; pop edi ; pop esi ; pop ebp ; pop ebx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/TP"]
PRELUDE = """struct O { virtual void AddRef(); virtual void Release(); };
struct P { O* p;
  P(const P& o):p(o.p){ if(p) p->AddRef(); }
  ~P(){ if(p) p->Release(); }
  P& operator=(const P& o){ O* q=o.p; O* old=p; if(q!=old){ if(q) q->AddRef(); p=q; if(old) old->Release(); } return *this; } };
struct C { int x; bool operator()(O* a, O* b) const; };
"""
def emit(va, A, N):
    src = ("void mh%08x(P*, P*, C);\n"
           "void ah%08x(P*, int, int, int, P, C);\n"
           "void sh%08x(P*, P*, C);\n"
           "void FUN_%08x(P* first, P* middle, P* last, C comp) {\n"
           "  mh%08x(first, middle, comp);\n"
           "  for (P* i = middle; i < last; ++i) {\n"
           "    O* b = first->p; O* a = i->p;\n"
           "    if (comp(a, b)) {\n"
           "      P v = *i;\n"
           "      *i = *first;\n"
           "      ah%08x(first, 0, middle - first, 0, v, comp);\n"
           "    }\n"
           "  }\n"
           "  sh%08x(first, middle, comp);\n}") % ((va,)*7)
    return src, "?FUN_%08x@@YAXPAUP@@00UC@@@Z" % va
