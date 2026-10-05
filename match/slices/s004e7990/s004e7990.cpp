// w1g1 slice s004e7990 -- /Od EASTL container glue and colour-variation helpers
// around the editor verb-icon data.
//
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast.

typedef unsigned int uint32_t;

// A 12-byte EASTL vector of refcounted elements; the destructor at 0x004b5440
// releases each element and frees the buffer.
struct RefVec {
    void* mBegin; // +0
    void* mEnd;   // +4
    void* mCap;   // +8
    RefVec() { mBegin = 0; mEnd = 0; mCap = 0; }
    ~RefVec();
};

void FillRefVec18(RefVec* out, void* value); // 0x004e7990
void FillRefVec3(void* a, RefVec* out, void* b, float c); // 0x004e7eb0

struct VerbSink {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void Deliver(RefVec* v); // vtable +0x14
};

struct TreeNode;

// rbtree anchor/owner laid out as: [+0 pad][+4 next][+8 prev][+0xc root]
// [+0x10 flag][+0x14 count].
struct TreeHead {
    uint32_t        pad0;
    void*           mNext;   // +0x4
    void*           mPrev;   // +0x8
    TreeNode*       mRoot;   // +0xc
    unsigned char   mFlag;   // +0x10
    char            pad1[3];
    int             mCount;  // +0x14

    void FreeNode(TreeNode* node); // 0x004e8a30
    void Reset();                  // @ 0x004e8850
};

// @ 0x004e8850
// Reinitialises the tree: frees the node chain, points the anchor at itself,
// then clears root/flag/count.
void TreeHead::Reset()
{
    FreeNode(mRoot);
    mNext = &mNext;
    mPrev = &mNext;
    mRoot = 0;
    mFlag = 0;
    mCount = 0;
}

// ---------------------------------------------------------------------------
// Skeletons for the large /Od bodies.
// ---------------------------------------------------------------------------

// @ 0x004e7990
// 1028-byte /Od helper taking a vector plus an Element and dispatching through
// a vtable.  Skeleton.
void VectorDispatch(void* self, void* vec, void* elem)
{
    (void)self; (void)vec; (void)elem;
}

// @ 0x004e7da0
// 167-byte /Od container conversion helper.  Skeleton.
void ConvertOwnerEntries(void* owner, void* out)
{
    (void)owner; (void)out;
}

// @ 0x004e7e50
// Builds a refcounted vector from owner+0x18 and dispatches it through a sink.
void BuildAndDispatch18(void* owner, VerbSink* sink)
{
    RefVec vec;
    FillRefVec18(&vec, *(void**)((char*)owner + 0x18));
    sink->Deliver(&vec);
}

// @ 0x004e7eb0
// 2368-byte /Od body.  Skeleton.
void BigBuilder2368(void* a, void* b, void* c, void* d)
{
    (void)a; (void)b; (void)c; (void)d;
}

// @ 0x004e87f0
// Builds a refcounted vector from three args and dispatches it through a sink.
void BuildAndDispatch3(void* a, VerbSink* sink, void* b, float c)
{
    uint32_t scratch[8];
    RefVec vec;
    FillRefVec3(a, &vec, b, c);
    sink->Deliver(&vec);
}
