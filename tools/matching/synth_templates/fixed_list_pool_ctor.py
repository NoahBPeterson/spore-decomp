# Fixed-pool container ctor (list-like: anchor node at +4, fixed_pool allocator at +0x18) copy-constructing
# its allocator from x (re-init pool over x's buffer with per-instantiation size/node/alignment), /O2.
PATTERN = 'push ebx ; push ebp ; push esi ; xor eax, eax ; push edi ; mov esi, ecx ; mov ecx, dword ptr [esp + N] ; mov dword ptr [esi + N], eax ; lea edi, [esi + N] ; push eax ; mov dword ptr [edi + N], eax ; mov dword ptr [edi + N], eax ; push N ; mov dword ptr [edi + N], eax ; push N ; mov dword ptr [esi + N], eax ; mov ebx, dword ptr [ecx] ; lea ebp, [esi + N] ; push N ; push ebx ; mov ecx, ebp ; mov dword ptr [ebp], eax ; call EXT ; mov dword ptr [ebp + N], ebx ; mov dword ptr [ebp + N], N ; add ebx, N ; mov dword ptr [ebp + N], ebx ; xor eax, eax ; mov dword ptr [esi + N], edi ; mov dword ptr [edi], edi ; pop edi ; mov dword ptr [esi + N], eax ; mov byte ptr [esi + N], al ; mov dword ptr [esi + N], eax ; mov eax, esi ; pop esi ; pop ebp ; pop ebx ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = r'''typedef unsigned int size_t;
struct fixed_pool {
    void* mpHead; void* mpReserved; void* mpNext; void* mpCapacity; size_t mnNodeSize;
    void init(void* pMemory, size_t memorySize, size_t nodeSize, size_t alignment, size_t alignmentOffset);
};
struct rest_t { void* prev; size_t a; size_t b; };
struct list_node { void* mpNext; rest_t r; list_node() : mpNext(0), r() {} };
template <size_t kSize, size_t kNode, size_t kAlign>
struct fixed_node_allocator {
    fixed_pool mPool;
    fixed_node_allocator() { mPool.mpHead = 0; }
    fixed_node_allocator(const fixed_node_allocator& x) {
        char* p = (char*)x.mPool.mpHead;
        mPool.mpHead = 0;
        mPool.init(p, kSize, kNode, kAlign, 0);
        mPool.mpNext = p; mPool.mpCapacity = p + kSize; mPool.mnNodeSize = kNode;
    }
};
'''

def emit(va, A, N):
    # N order: 4,4,4,8,0x0c(+8?),... find push constants: kAlign, kNode, kSize
    ints = N
    # pushes appear in order: align, node, size
    align, node, size = ints[5], ints[7], ints[10]
    two = (N[0] == 0x18)
    ex = "int, " if two else ""
    h = "flist_%08x" % va
    al = "fixed_node_allocator<%#x,%#x,%d>" % (size, node, align)
    src = ("struct %(h)s {\n"
           "    int mPad; list_node mAnchor; size_t mX;\n"
           "    %(al)s mAllocator;\n"
           "    %(h)s(%(ex)sconst %(al)s& a);\n"
           "};\n"
           "%(h)s::%(h)s(%(ex)sconst %(al)s& a)\n"
           "  : mAnchor(), mX(0), mAllocator(a)\n"
           "{ mAnchor.mpNext = (void*)&mAnchor; mAnchor.r.prev = (void*)&mAnchor; mAnchor.r.a = 0; *(char*)&mAnchor.r.b = 0; mX = 0; }") % dict(h=h, al=al, ex=ex)
    sym = "??0%s@@QAE@%sABU?$fixed_node_allocator@$0%s$0%s$0%s@@@Z" % (h, "H" if two else "", mangle_int(size), mangle_int(node), mangle_int(align))
    return src, sym

def mangle_int(v):
    if 1 <= v <= 10:
        return str(v - 1)
    s = ""
    while v:
        s = "ABCDEFGHIJKLMNOP"[v & 15] + s
        v >>= 4
    return s + "@"
