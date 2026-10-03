# EASTL-style rbtree operator= (clear; copy anchor; DoCopySubtree; leftmost/rightmost; size)
PATTERN = 'push ebp ; mov ebp, dword ptr [esp + N] ; push esi ; mov esi, ecx ; cmp esi, ebp ; je +N ; mov eax, dword ptr [esi + N] ; push edi ; push eax ; call EXT ; lea edi, [esi + N] ; mov dword ptr [edi], edi ; mov dword ptr [esi + N], edi ; mov dword ptr [esi + N], N ; mov byte ptr [esi + N], N ; mov dword ptr [esi + N], N ; mov eax, dword ptr [ebp + N] ; test eax, eax ; je +N ; push edi ; push eax ; mov ecx, esi ; call EXT ; mov ecx, eax ; mov dword ptr [esi + N], eax ; mov edx, dword ptr [ecx] ; test edx, edx ; je +N ; jmp +N ; lea ecx, [ecx] ; mov ecx, edx ; mov edx, dword ptr [ecx] ; test edx, edx ; jne +N ; mov dword ptr [edi], ecx ; mov ecx, eax ; mov eax, dword ptr [ecx + N] ; test eax, eax ; je +N ; mov ecx, eax ; mov eax, dword ptr [ecx + N] ; test eax, eax ; jne +N ; mov dword ptr [esi + N], ecx ; mov ecx, dword ptr [ebp + N] ; mov dword ptr [esi + N], ecx ; pop edi ; mov eax, esi ; pop esi ; pop ebp ; ret N ; mov eax, esi ; pop esi ; pop ebp ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "struct Nd { Nd* l; Nd* r; };\n"
def emit(va, A, N):
    t = "T_%08x" % va
    src = """struct %(t)s {
    static void __stdcall nuke(Nd*);
    int cmp; Nd* h_l; Nd* h_r; Nd* root; char color; unsigned n;
    
    Nd* __thiscall copy(Nd*, Nd*);
    %(t)s& operator=(const %(t)s& x);
};
%(t)s& %(t)s::operator=(const %(t)s& x) {
        if (this != &x) {
            nuke(root);
            h_l = (Nd*)&h_l; h_r = (Nd*)&h_l; root = 0; color = 0; n = 0;
            if (x.root) {
                root = copy(x.root, (Nd*)&h_l);
                Nd* a = root; while (a->l) a = a->l; h_l = a;
                Nd* b = root; while (b->r) b = b->r; h_r = b;
                n = x.n;
            }
        }
        return *this;
}
""" % dict(t=t, v=va)
    return src, "??4%s@@QAEAAU0@ABU0@@Z" % t
