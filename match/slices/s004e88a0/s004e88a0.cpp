// w1g1 slice s004e88a0 -- /Od EASTL rbtree/hashtable plumbing around 0x4e88a0.
//
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast.

typedef unsigned int uint32_t;

// allocator deallocate thunk (one pointer arg, cdecl)
void AllocFree(void* p); // 0x00f47380

// allocator allocate (allocator, size, alignment, extra) -- 0x0042dee0
void* AllocNodeMem(void* alloc, uint32_t size, uint32_t align, uint32_t extra);

struct Key5 {
    int m0, m1, m2, m3, m4;
};

struct NodeAlloc {
    char pad[0x18];
    Key5* Allocate(const Key5* rp); // @ 0x004e8d30
};

struct FreeCtx {
    void FreeNodes(void* p); // @ 0x004e8a30
};

// rbtree node: [+0 left][+4 right][+8 parent?][+0xc colour?][+0x10 key].
struct RBNode {
    RBNode* mLeft;   // +0
    RBNode* mRight;  // +4
    RBNode* mParent; // +8
    int     mColor;  // +0xc
    int     mKey;    // +0x10
};

struct RBSink {
    void Init(void* node); // 0x00566c50
};

inline bool KeyLess(int a, int b) { return a < b; }

struct RBTree {
    int      pad0;    // +0
    void*    mAnchor; // +4
    void*    mAnchor2;// +8
    RBNode*  mRoot;   // +0xc
    int      pad10;   // +0x10
    int      mCount;  // +0x14

    void* LowerBound(RBSink* out, int* key); // @ 0x004e89c0
};

// @ 0x004e8a30
// Post-order free of a node chain: recurse into the first field, deallocate the
// node, then continue with its second field.
void FreeCtx::FreeNodes(void* p)
{
    while (p != 0) {
        FreeNodes(*(void**)p);
        void* next;
        void* tmp = ((void**)p)[1];
        next = p;
        AllocFree(next);
        p = tmp;
    }
}

// ---------------------------------------------------------------------------
// Skeletons for the remaining /Od bodies.
// ---------------------------------------------------------------------------

// @ 0x004e88a0
// 217-byte /Od body.  Skeleton.
void Body88a0(void* a, void* b, void* c)
{
    (void)a; (void)b; (void)c;
}

// @ 0x004e89c0
// rbtree lower_bound: descend to the first node whose key is not less than *key.
void* RBTree::LowerBound(RBSink* out, int* key)
{
    RBNode* current = mRoot;
    RBNode* candidate = (RBNode*)&mAnchor;
    void* unused;
    while (current != 0) {
        if (KeyLess(current->mKey, *key)) {
            current = current->mLeft;
        } else {
            candidate = current;
            current = current->mRight;
        }
    }
    out->Init(candidate);
    return out;
}

// @ 0x004e8a80
// 352-byte /Od body.  Skeleton.
void Body8a80(void* a, void* b, void* c)
{
    (void)a; (void)b; (void)c;
}

// @ 0x004e8be0
// 145-byte /Od rbtree insert helper.  Skeleton.
void* RBInsert8be0(void* self, void* result, void* pos, void* value, char flag)
{
    (void)self; (void)result; (void)pos; (void)value; (void)flag;
    return result;
}

// @ 0x004e8c80
// 174-byte /Od body.  Skeleton.
void Body8c80(void* a, void* b, void* c)
{
    (void)a; (void)b; (void)c;
}

// @ 0x004e8d30
// Allocates a 0x24-byte node and stores the 0x14-byte key at node+0x10.
Key5* NodeAlloc::Allocate(const Key5* rp)
{
    void* foo = AllocNodeMem((char*)this + 0x18, 0x24, 4, 0);
    Key5* cc = (Key5*)((char*)foo + 0x10);
    Key5* tmp;
    if (cc != 0) {
        *cc = *rp;
        tmp = cc;
    } else {
        tmp = 0;
    }
    return tmp;
}

// @ 0x004e8da0
// 309-byte /Od body.  Skeleton.
void Body8da0(void* a, void* b, void* c)
{
    (void)a; (void)b; (void)c;
}

// @ 0x004e8ee0
// 140-byte /Od copy-with-virtual-apply loop.  Skeleton.
void* ApplyCopyLoop8ee0(void* out, void* first, void* last, void* dest)
{
    (void)out; (void)first; (void)last; (void)dest;
    return out;
}

// @ 0x004e8f70
// 218-byte /Od body.  Skeleton.
void Body8f70(void* a, void* b, void* c)
{
    (void)a; (void)b; (void)c;
}

// @ 0x004e9050
// 1194-byte /Od body.  Skeleton.
void Body9050(void* a, void* b, void* c, void* d)
{
    (void)a; (void)b; (void)c; (void)d;
}

// @ 0x004e9500
// 223-byte /Od body.  Skeleton.
void Body9500(void* a, void* b, void* c)
{
    (void)a; (void)b; (void)c;
}
