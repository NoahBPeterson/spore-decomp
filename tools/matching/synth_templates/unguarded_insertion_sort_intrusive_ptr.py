# Unguarded insertion sort over intrusive pointers (AddRef slot0 / Release slot1) with a by-value comparator (/O2, no EH).
# STATUS: sizes match (205 bytes) but register allocation differs (v/j swapped vs original); 0 byte-exact so far.
PATTERN = 'push ecx ; push ebp ; mov ebp, dword ptr [esp + N] ; mov dword ptr [esp + N], ebp ; cmp ebp, dword ptr [esp + N] ; je +N ; push ebx ; push esi ; push edi ; mov ebx, dword ptr [ebp] ; mov esi, ebp ; mov dword ptr [esp + N], ebx ; test ebx, ebx ; je +N ; mov eax, dword ptr [ebx] ; mov edx, dword ptr [eax] ; mov ecx, ebx ; call edx ; mov eax, dword ptr [ebp - N] ; lea edi, [ebp - N] ; push eax ; push ebx ; lea ecx, [esp + N] ; call EXT ; test al, al ; je +N ; mov ebx, dword ptr [edi] ; mov ebp, dword ptr [esi] ; cmp ebx, ebp ; je +N ; test ebx, ebx ; je +N ; mov eax, dword ptr [ebx] ; mov edx, dword ptr [eax] ; mov ecx, ebx ; call edx ; mov dword ptr [esi], ebx ; test ebp, ebp ; je +N ; mov eax, dword ptr [ebp] ; mov edx, dword ptr [eax + N] ; mov ecx, ebp ; call edx ; mov esi, edi ; mov eax, dword ptr [esi - N] ; lea edi, [esi - N] ; push eax ; mov eax, dword ptr [esp + N] ; push eax ; lea ecx, [esp + N] ; call EXT ; test al, al ; jne +N ; mov ebp, dword ptr [esp + N] ; mov ebx, dword ptr [esp + N] ; mov edi, dword ptr [esi] ; cmp ebx, edi ; je +N ; test ebx, ebx ; je +N ; mov edx, dword ptr [ebx] ; mov eax, dword ptr [edx] ; mov ecx, ebx ; call eax ; mov dword ptr [esi], ebx ; test edi, edi ; je +N ; mov edx, dword ptr [edi] ; mov eax, dword ptr [edx + N] ; mov ecx, edi ; call eax ; test ebx, ebx ; je +N ; mov edx, dword ptr [ebx] ; mov eax, dword ptr [edx + N] ; mov ecx, ebx ; call eax ; add ebp, N ; mov dword ptr [esp + N], ebp ; cmp ebp, dword ptr [esp + N] ; jne +N ; pop edi ; pop esi ; pop ebx ; pop ebp ; pop ecx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/TP"]
PRELUDE = """struct O { virtual void AddRef(); virtual void Release(); };
struct P { O* p;
  P(const P& o):p(o.p){ if(p) p->AddRef(); }
  ~P(){ if(p) p->Release(); }
  P& operator=(const P& o){ O* q=o.p; O* old=p; if(q!=old){ if(q) q->AddRef(); p=q; if(old) old->Release(); } return *this; } };
struct C { int x; bool operator()(O* a, O* b) const; };
"""
def emit(va, A, N):
    src = ("void FUN_%08x(P* first, P* last, C comp) {\n"
           "  for (P* i = first; i != last; ++i) {\n"
           "    P* j = i;\n"
           "    P v = *i;\n"
           "    P* k = j - 1;\n"
           "    while (comp(v.p, k->p)) { *j = *k; j = k; k = j - 1; }\n"
           "    *j = v;\n"
           "  }\n}") % va
    return src, "?FUN_%08x@@YAXPAUP@@0UC@@@Z" % va
