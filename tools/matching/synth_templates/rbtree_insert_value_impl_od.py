# EASTL rbtree DoInsertValueImpl(pParent, value, bForceToLeft) returning iterator, unoptimized module.
PATTERN = 'push ebp ; mov ebp, esp ; sub esp, N ; mov dword ptr [ebp - N], ecx ; movzx eax, byte ptr [ebp + N] ; test eax, eax ; jne +N ; mov ecx, dword ptr [ebp - N] ; add ecx, N ; cmp dword ptr [ebp + N], ecx ; je +N ; mov edx, dword ptr [ebp + N] ; mov eax, dword ptr [ebp + N] ; mov ecx, dword ptr [edx] ; cmp ecx, dword ptr [eax + N] ; sbb edx, edx ; neg edx ; movzx eax, dl ; test eax, eax ; je +N ; mov dword ptr [ebp - N], N ; jmp +N ; mov dword ptr [ebp - N], N ; mov ecx, dword ptr [ebp + N] ; push ecx ; mov ecx, dword ptr [ebp - N] ; call EXT ; mov dword ptr [ebp - N], eax ; mov edx, dword ptr [ebp - N] ; push edx ; mov eax, dword ptr [ebp - N] ; add eax, N ; push eax ; mov ecx, dword ptr [ebp + N] ; push ecx ; mov edx, dword ptr [ebp - N] ; push edx ; call EXT ; add esp, N ; mov eax, dword ptr [ebp - N] ; mov ecx, dword ptr [eax + N] ; add ecx, N ; mov edx, dword ptr [ebp - N] ; mov dword ptr [edx + N], ecx ; mov eax, dword ptr [ebp - N] ; push eax ; mov ecx, dword ptr [ebp + N] ; call EXT ; mov eax, dword ptr [ebp + N] ; mov esp, ebp ; pop ebp ; ret N'
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """struct RbNode { RbNode* l; RbNode* r; RbNode* p; int color; };
struct RbVNode : RbNode { unsigned key; };
struct RbCmp { bool operator()(const unsigned& a, const unsigned& b) const { return a < b; } };
struct RbIter { RbVNode* n; RbIter(RbVNode* x); };
inline bool RbLess(const unsigned& a, const unsigned& b) { return a < b; }
void RbInsert(RbVNode*, RbVNode*, RbNode*, int);
"""
def emit(va, A, N):
    src = ("struct T_%08x { int pad; RbNode anchor; unsigned size;\n"
           "  RbVNode* Create(const unsigned&);\n"
           "  RbIter F(RbVNode* pp, const unsigned& v, bool left);\n};\n"
           "RbIter T_%08x::F(RbVNode* pp, const unsigned& v, bool left) {\n"
           "    int side; RbCmp cmp;\n"
           "    if (left || pp == (RbVNode*)&anchor || cmp(v, pp->key)) side = 0; else side = 1;\n"
           "    RbVNode* node = Create(v);\n"
           "    RbInsert(node, pp, &anchor, side);\n"
           "    ++size;\n"
           "    return RbIter(node);\n  }\n") % (va, va)
    return src, "?F@T_%08x@@QAE?AURbIter@@PAURbVNode@@ABI_N@Z" % va
