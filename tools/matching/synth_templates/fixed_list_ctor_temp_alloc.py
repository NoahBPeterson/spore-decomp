# Fixed-pool list ctor: anchor (next,prev) at +0 self-linked, size at +8?; fixed_node_allocator at +8 copy-constructed
# from a temporary allocator built over the inline buffer at +0x1c. /O2.
PATTERN = 'sub esp, N ; push ebx ; push esi ; push edi ; push N ; push N ; mov esi, ecx ; push N ; push N ; lea edi, [esi + N] ; push edi ; lea ecx, [esp + N] ; mov dword ptr [esp + N], N ; call EXT ; mov ebx, dword ptr [esp + N] ; xor eax, eax ; push eax ; push N ; mov dword ptr [esp + N], edi ; add edi, N ; push N ; mov dword ptr [esp + N], edi ; mov dword ptr [esi], eax ; lea edi, [esi + N] ; push N ; mov dword ptr [esi + N], eax ; push ebx ; mov ecx, edi ; mov dword ptr [esp + N], N ; mov dword ptr [edi], eax ; call EXT ; mov dword ptr [edi + N], ebx ; add ebx, N ; mov dword ptr [edi + N], ebx ; mov dword ptr [edi + N], N ; pop edi ; mov dword ptr [esi], esi ; mov dword ptr [esi + N], esi ; mov eax, esi ; pop esi ; pop ebx ; add esp, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = r'''typedef unsigned int size_t;
struct fixed_pool {
    void* mpHead; void* mpReserved; void* mpNext; void* mpCapacity; size_t mnNodeSize;
    void init(void* pMemory, size_t memorySize, size_t nodeSize, size_t alignment, size_t alignmentOffset);
};
template <size_t kSize, size_t kNode, size_t kAlign>
struct fixed_node_allocator {
    fixed_pool mPool;
    fixed_node_allocator(void* buf) {
        mPool.mpHead = 0;
        mPool.init(buf, kSize, kNode, kAlign, 0);
        mPool.mpNext = buf; mPool.mpCapacity = (char*)buf + kSize; mPool.mnNodeSize = kNode;
    }
    fixed_node_allocator(const fixed_node_allocator& x) {
        char* p = (char*)x.mPool.mpHead;
        mPool.mpHead = 0;
        mPool.init(p, kSize, kNode, kAlign, 0);
        mPool.mpNext = p; mPool.mpCapacity = p + kSize; mPool.mnNodeSize = kNode;
    }
};
'''
def mangle_int(v):
    if 1 <= v <= 10:
        return str(v - 1)
    s = ""
    while v:
        s = "ABCDEFGHIJKLMNOP"[v & 15] + s
        v >>= 4
    return s + "@"

def emit(va, A, N):
    # pushes in order: align(0), 4... find: N[0]=0x14(sub),... size/node from push imms
    size, node = N[4], N[3]
    h = "flist_%08x" % va
    al = "fixed_node_allocator<%#x,%#x,4>" % (size, node)
    src = ("struct node_%(h)s { void* mNext; void* mPrev; node_%(h)s() : mNext(0), mPrev(0) {} };\n"
           "struct base_%(h)s : node_%(h)s {\n"
           "    %(al)s mAllocator;\n"
           "    base_%(h)s(const %(al)s& a) : mAllocator(a) {}\n"
           "};\n"
           "struct %(h)s : base_%(h)s {\n"
           "    char mBuf[%(size)d];\n"
           "    %(h)s();\n"
           "};\n"
           "%(h)s::%(h)s() : base_%(h)s(%(al)s(mBuf)) { mNext = this; mPrev = this; }") % dict(h=h, al=al, size=size)
    sym = "??0%s@@QAE@XZ" % h
    return src, sym
