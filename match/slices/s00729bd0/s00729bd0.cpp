// Slice s00729bd0 — vertex-buffer / span helpers around the UV pipeline.
// Simple accessors/constructors reconstructed; the large bulk/copy routines are partial.
#include "types.h"
#include <intrin.h>

void operator_delete(void* p);   // 0x00f47380

extern "C" {
    void* FUN_00f473a0(unsigned size, const char* name, int f, int df, const char* file, int line);
    void  FUN_0042f0a0(void* p, int n, void* local, int m);                 // 0x0042f0a0
    int   FUN_0071ddc0(void* p, int a, int b, int c, int d);                // 0x0071ddc0
    double sqrt(double x);                                                  // CRT: inlined as fsqrt
    void* FUN_00720010(int size);                                           // 0x00720010  AllocEltBuffer
    void* MemCopy(void* dst, const void* src, unsigned n);                  // 0x011e0744
}

// The index/vertex buffer the pipeline locks segments of.
struct IBuf {
    uint8_t  pad00[8];                                                      // +0x00
    int      mCount;                                                        // +0x08
    uint8_t  pad0c[0x0c];                                                   // +0x0c .. +0x17
    void*    mpData;                                                        // +0x18

    unsigned Lock(unsigned n, void* pOut);                                  // 0x011f4f20
    void*    Unlock(void** pIn);                                            // 0x011f4fd0
};

// The buffer hands back bare vtable-bearing pointers; only slot 0 (a no-argument
// refresh) is ever invoked on them.
typedef void (__thiscall *VSlot0)(void*);

static inline void CallSlot0(void* p)
{
    VSlot0* vt = *(VSlot0**)p;
    vt[0](p);
}

struct Box { float mn[3]; float mx[3]; };
struct SplitNode {            // 0x40 bytes; also the scratch type FUN_0072a080 resets
    int      axis;            // +0
    float    pos;             // +4
    unsigned nLeft;           // +8
    unsigned nRight;          // +0xc
    Box      left;            // +0x10
    Box      right;           // +0x28
};


// @ 0x0072a130  iterator/span-ctor (thiscall, ret 4)
struct SpanIter {
    int   count;   // +0
    int   base;    // +4
    short a;       // +8
    short b;       // +0xa
    int*  owner;   // +0xc
};

struct SpanOwner {
    void*  vptr;   // +0
    char   pad4[8];
    int*   mpBegin;   // +0xc
    int*   mpEnd;     // +0x10
    SpanIter* MakeIter(SpanIter* out);
};

SpanIter* SpanOwner::MakeIter(SpanIter* out)
{
    int base = (int)mpBegin;
    out->count = ((int)mpEnd - base) / 0x30;
    *(short*)((char*)out + 0xa) = 0x30;
    out->base = base;
    *(short*)(out + 2) = 0x30;
    out->owner = (int*)this;
    (*(void(**)(void))vptr)();
    return out;
}

// @ 0x0072a180  release a span buffer unless it aliases the inline storage (fastcall)
void __fastcall FUN_0072a180(int* self)
{
    int* p = (int*)self[0];
    if (p != 0 && p != (int*)self[4])
        operator_delete(p);
}

// @ 0x0072a1a0  vector-like span ctor (thiscall, ret 8)
struct SpanAlloc {
    int* mpBegin;   // +0
    int* mpEnd;     // +4
    int* mpCap;     // +8
    int  pad0;      // +0xc
    int  stride;    // +0x10
    SpanAlloc* Init(int n, int* other);
};

SpanAlloc* SpanAlloc::Init(int n, int* other)
{
    stride = other[1];
    if (n != 0) {
        int* p = (int*)FUN_00f473a0(n * 4, "Graphics", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1);
        mpBegin = p;
        mpEnd   = p;
        mpCap   = p + n;
        return this;
    }
    mpBegin = 0;
    mpEnd   = 0;
    mpCap   = mpBegin + n;
    return this;
}

// @ 0x0072a080 FUN_0072a080  reset the child boxes to inverted-infinite; retail keeps `this` in eax
__declspec(noinline) SplitNode* __fastcall FUN_0072a080(SplitNode* self)
{
    const float kMax =  3.402823466e+38F;
    const float kMin = -3.402823466e+38F;
    self->left.mn[0] = kMax; self->left.mn[1] = kMax; self->left.mn[2] = kMax;
    self->left.mx[0] = kMin; self->left.mx[1] = kMin; self->left.mx[2] = kMin;
    self->right.mn[0] = kMax; self->right.mn[1] = kMax; self->right.mn[2] = kMax;
    self->right.mx[0] = kMin; self->right.mx[1] = kMin; self->right.mx[2] = kMin;
    return self;
}

// ---------------------------------------------------------------------------
// large functions (partial)
// ---------------------------------------------------------------------------

// The lock token the buffer fills in: three words, only the first of which is
// ever read back.
struct LockHandle {
    void* mpPtr;                                                            // +0x00
    void* mpPad1;                                                           // +0x04
    void* mpPad2;                                                           // +0x08
};

// @ 0x00729bd0  returns the locked segment, copying the buffer through it when
// the buffer has not been materialised yet
void* FUN_00729bd0(IBuf* p1, void* p2, void** p3)
{
    void* rb = p1->mpData;
    if (rb != 0) {
        if (p2 != 0) {
            *p3 = p2;
            CallSlot0(p2);
        }
        return rb;
    }

    LockHandle lh;
    if (p1->Lock(1, &lh)) {
        int   size = p1->mCount * 2;
        void* seg  = FUN_00720010(size);
        if (seg != 0) {
            rb = (char*)seg + 0xc;
            MemCopy(rb, lh.mpPtr, (unsigned)size);
            *p3 = seg;
            CallSlot0(seg);
        }
        p1->Unlock(&lh.mpPtr);
    }
    return rb;
}

// A refcounted stream owner held by the vertex table (vtable slots 0/1 are
// AddRef and Release).
struct RefObj {
    void** vptr;                                                            // +0x00

    void AddRef()  { ((void (__thiscall*)(RefObj*))vptr[0])(this); }
    void Release() { ((void (__thiscall*)(RefObj*))vptr[1])(this); }
};

// The model header: only the stream-table pointer is needed here.
struct MeshModel {
    uint8_t pad00[8];                                                       // +0x00 .. +0x07
    void*   mpStreams;                                                      // +0x08
};

// A vertex-stream record (0x20 bytes; the usable fields start at +0x10).
struct MeshStream {
    int            nCount;                                                  // +0x10
    const float*   mpVerts;                                                 // +0x14
    uint16_t       mUnk18;                                                  // +0x18
    uint16_t       mStride;                                                 // +0x1a  byte stride between vertices
    RefObj*        mpOwner;                                                 // +0x1c
};

struct StreamRecord {
    uint8_t    pad00[0x10];                                                 // +0x00 .. +0x0f
    MeshStream entry;                                                       // +0x10
};

// A vertex/point triple. The stream's box is the same 6-float layout as Box,
// spelled with named members so its copies can be struct assignments.
struct Vec3 { float x, y, z; };

struct Box6 {
    Vec3 mn;                                                                // +0x00
    Vec3 mx;                                                                // +0x0c
};

// Grow a box with one vertex, which counts as a degenerate (point) box.
static inline void ExpandPoint(Box6& cur, const float* v)
{
    if (cur.mn.x > cur.mx.x) {
        cur.mn = *(const Vec3*)v;
        cur.mx = *(const Vec3*)v;
    } else {
        if (cur.mn.x > v[0]) cur.mn.x = v[0];
        else if (v[0] > cur.mx.x) cur.mx.x = v[0];
        if (cur.mn.y > v[1]) cur.mn.y = v[1];
        else if (v[1] > cur.mx.y) cur.mx.y = v[1];
        if (cur.mn.z > v[2]) cur.mn.z = v[2];
        else if (v[2] > cur.mx.z) cur.mx.z = v[2];
    }
}

// @ 0x00729c60 FUN_00729c60  grow a box over one vertex stream and track the largest radius
void FUN_00729c60(MeshModel* model, Box6* box, float* radius)
{
    int idx = FUN_0071ddc0(model, 1, 0, 3, 0xe);
    if (idx < 0)
        return;

    StreamRecord* rec    = (StreamRecord*)((char*)model->mpStreams + (idx << 5));
    MeshStream*   entry  = &rec->entry;
    int           count  = entry->nCount;
    uint16_t      stride = entry->mStride;
    RefObj*       obj    = entry->mpOwner;
    const float*  v      = entry->mpVerts;

    if (obj != 0)
        obj->AddRef();

    float len2 = 0.0f;
    if (count > 0) {
        const float* p = v + 1;
        do {
            if (box != 0)
                ExpandPoint(*box, p - 1);
            float d = (p[-1] * p[-1] + p[1] * p[1]) + p[0] * p[0];
            if (len2 < d)
                len2 = d;
            p = (const float*)((const char*)p + stride);
            --count;
        } while (count != 0);
    }

    if (radius != 0) {
        double s = sqrt(len2);
        len2 = (float)s;
        const float* q = (s > *radius) ? &len2 : radius;
        *radius = *q;
    }

    if (obj != 0)
        obj->Release();
}

static inline void ExpandBox(Box& cur, const Box& e)
{
    if (cur.mn[0] <= cur.mx[0]) {
        if (cur.mn[0] > e.mn[0]) cur.mn[0] = e.mn[0];
        if (e.mx[0] > cur.mx[0]) cur.mx[0] = e.mx[0];
        if (cur.mn[1] > e.mn[1]) cur.mn[1] = e.mn[1];
        if (e.mx[1] > cur.mx[1]) cur.mx[1] = e.mx[1];
        if (cur.mn[2] > e.mn[2]) cur.mn[2] = e.mn[2];
        if (e.mx[2] > cur.mx[2]) cur.mx[2] = e.mx[2];
    } else {
        cur = e;
    }
}

// @ 0x00729de0 FUN_00729de0  partition idx[0..n) around node->axis / node->pos by box centre; fills child boxes and counts
__declspec(noinline) void FUN_00729de0(SplitNode* node, const Box* box, Box* const* items, unsigned* idx, int n)
{
    Box inv;
    inv.mx[0] = box->mx[0]; inv.mx[1] = box->mx[1]; inv.mx[2] = box->mx[2];
    inv.mn[0] = box->mn[0]; inv.mn[1] = box->mn[1]; inv.mn[2] = box->mn[2];
    node->right.mn[0] = inv.mx[0]; node->right.mn[1] = inv.mx[1]; node->right.mn[2] = inv.mx[2];
    node->right.mx[0] = inv.mn[0]; node->right.mx[1] = inv.mn[1]; node->right.mx[2] = inv.mn[2];
    node->left = node->right;

    // Retail reads `c[node->axis]` from the stack slot array before it has stored the
    // current element's box copy, so an out-of-range axis sees the *previous* iteration's
    // values (or the initial `<box>` copy on the first pass).  The /O2 schedule used to
    // store the copy first, which changed the partition for axis > 2.  Model those slots
    // explicitly: c[3..6] are the previous element's mn[0..2]/mx[0]; c[7..8] are the
    // current element's mx[1]/mx[2] (retail stores those two before the compare).
    float staleMn0 = box->mx[0];
    float staleMn1 = box->mx[1];
    float staleMn2 = box->mx[2];
    float staleMx0 = box->mn[0];

    int i = 0;
    int j = n - 1;
    if (j >= 0) {
        do {
            unsigned k = idx[i];
            const Box& src = (*items)[k];
            float c0 = (src.mx[0] + src.mn[0]) * 0.5f;
            float c1 = (src.mx[1] + src.mn[1]) * 0.5f;
            float c2 = (src.mx[2] + src.mn[2]) * 0.5f;

            int a = node->axis;
            float cv;
            if (a == 0)       cv = c0;
            else if (a == 1)  cv = c1;
            else if (a == 2)  cv = c2;
            else if (a == 3)  cv = staleMn0;
            else if (a == 4)  cv = staleMn1;
            else if (a == 5)  cv = staleMn2;
            else if (a == 6)  cv = staleMx0;
            else if (a == 7)  cv = src.mx[1];
            else if (a == 8)  cv = src.mx[2];
            else {
                // Retail computes `[esp + axis*4 + 0x10]` with 32-bit wrapping; with its
                // frame at E-0x34 at that point the effective address is E-0x24+axis*4
                // (E = entry ESP).  Reproduce the same wrapped read so huge / negative
                // axes observe the same pool or stack bytes instead of an arbitrary c0.
                unsigned int E = (unsigned int)(uintptr_t)_AddressOfReturnAddress();
                unsigned int addr = E - 0x24u + ((unsigned int)a << 2);
                cv = *(const float*)(uintptr_t)addr;
            }

            staleMn0 = src.mn[0]; staleMn1 = src.mn[1];
            staleMn2 = src.mn[2]; staleMx0 = src.mx[0];

            if (cv > node->pos) {
                idx[i] = idx[j];
                idx[j] = k;
                --j;
                ExpandBox(node->right, src);
            } else {
                ++i;
                ExpandBox(node->left, src);
            }
        } while (i <= j);
    }
    node->nLeft = (unsigned)i;
    node->nRight = (unsigned)(n - i);
}

// ---- KD-tree / BVH split search (0x0072a200) ----
// @ 0x00729de0 partitions idx[0..n) around node->axis/pos, filling counts and child boxes (stub below)
// (FUN_00729de0 defined above)
// @ 0x007298b0 surface-area-heuristic cost of a split (returns x87 float)
float FUN_007298b0(const Box* box, const SplitNode* node);

static inline Box MakeBox(const float* mn, const float* mx)
{
    Box r;
    r.mn[0] = mn[0]; r.mn[1] = mn[1]; r.mn[2] = mn[2];
    r.mx[0] = mx[0]; r.mx[1] = mx[1]; r.mx[2] = mx[2];
    return r;
}

static inline float SurfaceArea(const Box& b)
{
    float dx = b.mx[0] - b.mn[0];
    float dy = b.mx[1] - b.mn[1];
    float dz = b.mx[2] - b.mn[2];
    return ((dz * dx) + (dy * dx) + (dz * dy)) * 2.0f;
}

// @ 0x0072a200  returns true when a split was found
bool FUN_0072a200(SplitNode* out, const Box* box, Box* const* items, unsigned* idx, unsigned n)
{
    SplitNode best;
    FUN_0072a080(&best);

    Box b;
    {
        const Box& e0 = (*items)[idx[0]];
        b.mn[0] = e0.mn[0]; b.mn[1] = e0.mn[1]; b.mn[2] = e0.mn[2];
        b.mx[0] = e0.mx[0]; b.mx[1] = e0.mx[1]; b.mx[2] = e0.mx[2];
    }
    for (unsigned i = 1; i < n; ++i) {
        const Box& e = (*items)[idx[i]];
        if (!(b.mn[0] > b.mx[0])) {
            if (e.mn[0] < b.mn[0]) b.mn[0] = e.mn[0];
            if (b.mx[0] < e.mx[0]) b.mx[0] = e.mx[0];
            if (e.mn[1] < b.mn[1]) b.mn[1] = e.mn[1];
            if (b.mx[1] < e.mx[1]) b.mx[1] = e.mx[1];
            if (e.mn[2] < b.mn[2]) b.mn[2] = e.mn[2];
            if (b.mx[2] < e.mx[2]) b.mx[2] = e.mx[2];
        } else {
            b = e;
        }
    }

    float parentArea;
    {
        float dy = box->mx[1] - box->mn[1];
        float dz = box->mx[2] - box->mn[2];
        float dx = box->mx[0] - box->mn[0];
        parentArea = ((dz * dx) + (dy * dx) + (dz * dy)) * 2.0f;
    }
    float bestCost = parentArea;
    unsigned a = 0;
    do {
        Box c = *box;
        c.mx[a] = b.mx[a];
        float cost = SurfaceArea(c);
        if (cost < bestCost) {
            best.axis = (int)a;
            best.pos = b.mx[a];
            best.nLeft = n;
            best.nRight = 0;
            best.left = b;
            {
                Box inv;
                inv.mn[0] = box->mx[0]; inv.mn[1] = box->mx[1]; inv.mn[2] = box->mx[2];
                inv.mx[0] = box->mn[0]; inv.mx[1] = box->mn[1]; inv.mx[2] = box->mn[2];
                best.right = inv;
            }
            bestCost = cost;
        }
        c = *box;
        c.mn[a] = b.mn[a];
        cost = SurfaceArea(c);
        if (cost < bestCost) {
            best.axis = (int)a;
            best.pos = b.mn[a];
            best.nLeft = 0;
            best.nRight = n;
            {
                Box inv;
                inv.mn[0] = box->mx[0]; inv.mn[1] = box->mx[1]; inv.mn[2] = box->mx[2];
                inv.mx[0] = box->mn[0]; inv.mx[1] = box->mn[1]; inv.mx[2] = box->mn[2];
                best.left = inv;
            }
            best.right = b;
            bestCost = cost;
        }
        ++a;
    } while (a < 3);

    if (parentArea * 0.6f > bestCost) {
        *out = best;
        return true;
    }

    b.mn[0] = (b.mx[0] + b.mn[0]) * 0.5f;
    b.mn[1] = (b.mx[1] + b.mn[1]) * 0.5f;
    b.mn[2] = (b.mx[2] + b.mn[2]) * 0.5f;
    float bestSplit = 1.0f;
    for (unsigned a = 0; a < 3; ++a) {
        best.axis = (int)a;
        best.pos = b.mn[a];
        FUN_00729de0(&best, box, items, idx, (int)n);
        float cost = FUN_007298b0(box, &best);
        if (best.nLeft != 0 && best.nRight != 0 && cost < bestSplit) {
            *out = best;
            bestSplit = cost;
        }
    }
    if (!(bestSplit < 0.95f))
        return false;
    FUN_00729de0(out, box, items, idx, (int)n);
    return true;
}

// A 48-byte scratch block handed to the element constructor (kept free of any
// array member so /GS does not add a stack cookie).
struct Scratch48 {
    int w0, w1, w2, w3, w4, w5, w6, w7, w8, w9, w10, w11;
};

// An array of 0x30-byte elements allocated through the game allocator (the
// EASTL vector form used by the UV pipeline).
struct EAArray {
    void* mpBegin;                                                          // +0x00
    void* mpEnd;                                                            // +0x04
    void* mpCap;                                                            // +0x08

    EAArray* Init(int n, int reserved);
};

// @ 0x0072aa80  allocate n elements of 0x30 bytes and default-construct them
EAArray* EAArray::Init(int n, int reserved)
{
    (void)reserved;
    Scratch48 local_30;
    void* buf;
    if (n != 0)
        buf = FUN_00f473a0(n * 0x30, "Graphics", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1);
    else
        buf = 0;
    mpBegin = buf;
    mpEnd   = buf;
    mpCap   = (char*)buf + n * 0x30;
    FUN_0042f0a0(buf, n, &local_30, n);
    mpEnd = (char*)mpBegin + n * 0x30;
    return this;
}

// The EA fixed allocator singleton the kd-tree node pool is carved from.
struct NodeAllocator {
    void* Malloc();                                                         // 0x004fde40
};
extern NodeAllocator gNodeAllocator;                                        // 0x0162b1e0

// A kd-tree node: the box it covers, the slice of the shared index array it owns,
// the axis the parent split on and the two children that split produced (0x34 bytes).
struct BspNode {
    void*    mpOwner;                                                       // +0x00  tree this node lives in
    int      mLevel;                                                        // +0x04  level in the tree (parent + 1)
    Box      mBox;                                                          // +0x08  bounds of this node's slice
    unsigned mFirst;                                                        // +0x20  offset of the slice's first index
    unsigned mCount;                                                        // +0x24  number of indices in the slice
    int      mAxis;                                                         // +0x28  axis the parent split on
    BspNode* mpLeft;                                                        // +0x2c  below-plane child (0 if unsplit)
    BspNode* mpRight;                                                       // +0x30  above-plane child (0 if unsplit)

    // 0x00729820
    BspNode* Init(void* owner, float* box, int first, int count);
    int      Build(Box* const* items, unsigned* idx, unsigned n, int depth);
};

// @ 0x0072a8c0  split this node's index slice once and recurse into both children
int BspNode::Build(Box* const* items, unsigned* idx, unsigned n, int depth)
{
    SplitNode split;
    FUN_0072a080(&split);

    if (depth != 0 && mCount > n) {
        if (FUN_0072a200(&split, &mBox, items, idx + mFirst, mCount)) {
            int axis = split.axis;
            mAxis = axis;

            Box left = mBox;
            left.mx[axis] = split.left.mx[axis];

            Box right = mBox;
            right.mn[axis] = split.right.mn[axis];

            BspNode* node = (BspNode*)gNodeAllocator.Malloc();
            node = (node != 0) ? node->Init(this, (float*)&left, (int)mFirst, (int)split.nLeft) : 0;
            mpLeft = node;

            node = (BspNode*)gNodeAllocator.Malloc();
            node = (node != 0) ? node->Init(this, (float*)&right, (int)(mFirst + split.nLeft), (int)split.nRight) : 0;
            mpRight = node;

            mpLeft->mLevel = mLevel + 1;
            int c1 = mpLeft->Build(items, idx, n, depth - 1);
            mpRight->mLevel = mpLeft->mLevel + c1 + 1;
            int c2 = mpRight->Build(items, idx, n, depth - 1);
            return c2 + c1 + 2;
        }
    }
    return 0;
}
