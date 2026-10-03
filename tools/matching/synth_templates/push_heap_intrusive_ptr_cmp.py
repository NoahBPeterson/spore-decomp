# EASTL push_heap sift-up (adjust toward top) over intrusive pointers; P value by value, empty comparator by value (/O2).
PATTERN = 'push ebx ; push ebp ; mov ebp, dword ptr [esp + N] ; push esi ; mov esi, dword ptr [esp + N] ; push edi ; lea edi, [esi - N] ; sar edi, N ; cmp esi, dword ptr [esp + N] ; jle +N ; mov ecx, dword ptr [esp + N] ; mov eax, dword ptr [ebp + edi*N] ; push ecx ; push eax ; lea ecx, [esp + N] ; call EXT ; test al, al ; je +N ; mov ecx, dword ptr [ebp + esi*N] ; mov ebx, dword ptr [ebp + edi*N] ; mov dword ptr [esp + N], ecx ; cmp ebx, ecx ; je +N ; test ebx, ebx ; je +N ; mov edx, dword ptr [ebx] ; mov eax, dword ptr [edx] ; mov ecx, ebx ; call eax ; mov ecx, dword ptr [esp + N] ; mov dword ptr [ebp + esi*N], ebx ; test ecx, ecx ; je +N ; mov edx, dword ptr [ecx] ; mov eax, dword ptr [edx + N] ; call eax ; mov esi, edi ; dec edi ; sar edi, N ; cmp esi, dword ptr [esp + N] ; jg +N ; mov ecx, dword ptr [esp + N] ; mov edi, dword ptr [ebp + esi*N] ; mov ebx, ecx ; cmp ecx, edi ; je +N ; test ecx, ecx ; je +N ; mov edx, dword ptr [ecx] ; mov eax, dword ptr [edx] ; call eax ; mov ecx, dword ptr [esp + N] ; mov dword ptr [ebp + esi*N], ebx ; test edi, edi ; je +N ; mov edx, dword ptr [edi] ; mov eax, dword ptr [edx + N] ; mov ecx, edi ; call eax ; mov ecx, dword ptr [esp + N] ; pop edi ; pop esi ; pop ebp ; pop ebx ; test ecx, ecx ; je +N ; mov edx, dword ptr [ecx] ; mov eax, dword ptr [edx + N] ; jmp eax ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    s = "struct O_%08x { virtual void v0(); virtual void v1(); };\n" % va
    s += ("struct P_%08x { O_%08x* p; P_%08x(const P_%08x& o) : p(o.p) { if (p) p->v0(); }\n"
          "  P_%08x& operator=(const P_%08x& o) { O_%08x* q = o.p; O_%08x* old = p; if (q != old) { if (q) q->v0(); p = q; if (old) old->v1(); } return *this; }\n"
          "  ~P_%08x() { if (p) p->v1(); } O_%08x* get() const { return p; } };\n") % ((va,) * 10)
    s += "struct C_%08x { bool operator()(O_%08x*, O_%08x*) const; };\n" % ((va,) * 3)
    s += ("void __cdecl F_%08x(P_%08x* first, int top, int hole, P_%08x value, C_%08x comp) {\n"
          "  int parent = (hole - 1) >> 1;\n"
          "  while (hole > top && comp(first[parent].get(), value.get())) {\n"
          "    first[hole] = first[parent]; hole = parent; parent = (hole - 1) >> 1; }\n"
          "  first[hole] = value; }\n") % ((va,) * 4)
    return s, "?F_%08x@@YAXPAUP_%08x@@HHU1@UC_%08x@@@Z" % ((va,) * 3)
