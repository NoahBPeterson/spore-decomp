# EASTL rbtree DoInsertValue(const value&, true_type) -> pair<iterator,bool> (hidden ret), /Od module.
# Local names matter for /Od slot order: extract_key extractKey first, then EASTL names.
PATTERN = 'push ebp ; mov ebp, esp ; sub esp, N ; mov dword ptr [ebp - N], ecx ; mov eax, dword ptr [ebp - N] ; mov ecx, dword ptr [eax + N] ; mov dword ptr [ebp - N], ecx ; mov edx, dword ptr [ebp - N] ; add edx, N ; mov dword ptr [ebp - N], edx ; mov byte ptr [ebp - N], N ; cmp dword ptr [ebp - N], N ; je +N ; mov eax, dword ptr [ebp + N] ; mov ecx, dword ptr [ebp - N] ; mov edx, dword ptr [eax] ; cmp edx, dword ptr [ecx + N] ; sbb eax, eax ; neg eax ; mov byte ptr [ebp - N], al ; mov ecx, dword ptr [ebp - N] ; mov dword ptr [ebp - N], ecx ; movzx edx, byte ptr [ebp - N] ; test edx, edx ; je +N ; mov eax, dword ptr [ebp - N] ; mov ecx, dword ptr [eax + N] ; mov dword ptr [ebp - N], ecx ; jmp +N ; mov edx, dword ptr [ebp - N] ; mov eax, dword ptr [edx] ; mov dword ptr [ebp - N], eax ; jmp +N ; mov ecx, dword ptr [ebp - N] ; mov dword ptr [ebp - N], ecx ; movzx edx, byte ptr [ebp - N] ; test edx, edx ; je +N ; mov eax, dword ptr [ebp - N] ; mov ecx, dword ptr [ebp - N] ; cmp ecx, dword ptr [eax + N] ; je +N ; mov edx, dword ptr [ebp - N] ; push edx ; call EXT ; add esp, N ; mov dword ptr [ebp - N], eax ; jmp +N ; push N ; mov eax, dword ptr [ebp + N] ; push eax ; mov ecx, dword ptr [ebp - N] ; push ecx ; lea edx, [ebp - N] ; push edx ; mov ecx, dword ptr [ebp - N] ; call EXT ; mov byte ptr [ebp - N], N ; lea eax, [ebp - N] ; push eax ; mov ecx, dword ptr [ebp + N] ; call EXT ; mov ecx, dword ptr [ebp + N] ; mov dl, byte ptr [ebp - N] ; mov byte ptr [ecx + N], dl ; mov eax, dword ptr [ebp + N] ; jmp +N ; mov eax, dword ptr [ebp - N] ; mov ecx, dword ptr [ebp + N] ; mov edx, dword ptr [eax + N] ; cmp edx, dword ptr [ecx] ; sbb eax, eax ; neg eax ; movzx ecx, al ; test ecx, ecx ; je +N ; push N ; mov edx, dword ptr [ebp + N] ; push edx ; mov eax, dword ptr [ebp - N] ; push eax ; lea ecx, [ebp - N] ; push ecx ; mov ecx, dword ptr [ebp - N] ; call EXT ; mov byte ptr [ebp - N], N ; lea edx, [ebp - N] ; push edx ; mov ecx, dword ptr [ebp + N] ; call EXT ; mov eax, dword ptr [ebp + N] ; mov cl, byte ptr [ebp - N] ; mov byte ptr [eax + N], cl ; mov eax, dword ptr [ebp + N] ; jmp +N ; mov byte ptr [ebp - N], N ; mov edx, dword ptr [ebp - N] ; push edx ; lea ecx, [ebp - N] ; call EXT ; mov dword ptr [ebp - N], eax ; mov eax, dword ptr [ebp - N] ; push eax ; mov ecx, dword ptr [ebp + N] ; call EXT ; mov ecx, dword ptr [ebp + N] ; mov dl, byte ptr [ebp - N] ; mov byte ptr [ecx + N], dl ; mov eax, dword ptr [ebp + N] ; mov esp, ebp ; pop ebp ; ret N'
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """struct nb { nb* r; nb* l; nb* p; int color; };
struct vn : nb { unsigned key; };
nb* Dec(nb*);
struct It { vn* n; It(vn*); It(const It&); };
struct Pr { It first; bool second; Pr(const It& a, const bool& b) : first(a), second(b) {} };
inline bool LtF(const unsigned& a, const unsigned& b) { return a < b; }
struct EK { const unsigned& operator()(const unsigned& k) const { return k; } };
"""
def emit(va, A, N):
    t = "T_%08x" % va
    src = ("struct %s { int pad; nb anchor; unsigned size;\n"
           "  It Impl(vn* pp, const unsigned& v, bool left);\n"
           "  Pr F(const unsigned& v, int tag);\n};\n"
           "Pr %s::F(const unsigned& v, int tag) {\n"
           "  EK extractKey;\n"
           "  vn* pCurrent = (vn*)anchor.p; vn* pLowerBound = (vn*)&anchor; vn* pParent; bool bValueLessThanNode = true;\n"
           "  while (pCurrent) { bValueLessThanNode = LtF(extractKey(v), extractKey(pCurrent->key)); pLowerBound = pCurrent; if (bValueLessThanNode) pCurrent = (vn*)pCurrent->l; else pCurrent = (vn*)pCurrent->r; }\n"
           "  pParent = pLowerBound;\n"
           "  if (bValueLessThanNode) { if (pLowerBound != (vn*)anchor.l) pLowerBound = (vn*)Dec(pLowerBound);\n"
           "    else { const It it(Impl(pLowerBound, v, false)); return Pr(it, true); } }\n"
           "  if (LtF(extractKey(pLowerBound->key), extractKey(v))) { const It it(Impl(pParent, v, false)); return Pr(it, true); }\n"
           "  return Pr(It(pLowerBound), false);\n}\n") % (t, t)
    return src, "?F@%s@@QAE?AUPr@@ABIH@Z" % t
