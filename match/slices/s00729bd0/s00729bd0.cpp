// Slice s00729bd0 — vertex-buffer / span helpers around the UV pipeline.
// Simple accessors/constructors reconstructed; the large bulk/copy routines are partial.
#include "types.h"

void operator_delete(void* p);   // 0x00f47380

extern "C" {
    void* FUN_00f473a0(unsigned size, const char* name, int f, int df, const char* file, int line);
    int   FUN_011f4f20(int a, void* b);
    void  FUN_011f4fd0(void* a);
    void  FUN_00720010(unsigned size);
    void  FUN_0042f0a0(int a, int b, int c, int d);
    void  FUN_0071ddc0(void* p, int a, int b, int c, int d);
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

// @ 0x0072a080  reset the child boxes to inverted-infinite (PARTIAL form: SSE stack-roundtrip not reproduced)
__declspec(noinline) void __fastcall FUN_0072a080(SplitNode* self)
{
    const float kMax =  3.402823466e+38F;
    const float kMin = -3.402823466e+38F;
    self->left.mn[0] = kMax; self->left.mn[1] = kMax; self->left.mn[2] = kMax;
    self->left.mx[0] = kMin; self->left.mx[1] = kMin; self->left.mx[2] = kMin;
    self->right.mn[0] = kMax; self->right.mn[1] = kMax; self->right.mn[2] = kMax;
    self->right.mx[0] = kMin; self->right.mx[1] = kMin; self->right.mx[2] = kMin;
}

// ---------------------------------------------------------------------------
// large functions (partial)
// ---------------------------------------------------------------------------

// @ 0x00729bd0  (PARTIAL)
void* FUN_00729bd0(int a, void* b, void* c)
{
    (void)a; (void)b; (void)c;
    return 0;
}

// @ 0x00729c60  (PARTIAL)
void FUN_00729c60(void* p, float* a, float* b)
{
    (void)p; (void)a; (void)b;
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

// @ 0x00729de0  partition idx[0..n) around node->axis / node->pos by box centre; fills child boxes and counts
__declspec(noinline) void FUN_00729de0(SplitNode* node, const Box* box, Box* const* items, unsigned* idx, int n)
{
    Box inv;
    inv.mx[0] = box->mx[0]; inv.mx[1] = box->mx[1]; inv.mx[2] = box->mx[2];
    inv.mn[0] = box->mn[0]; inv.mn[1] = box->mn[1]; inv.mn[2] = box->mn[2];
    node->right.mn[0] = inv.mx[0]; node->right.mn[1] = inv.mx[1]; node->right.mn[2] = inv.mx[2];
    node->right.mx[0] = inv.mn[0]; node->right.mx[1] = inv.mn[1]; node->right.mx[2] = inv.mn[2];
    node->left = node->right;

    int i = 0;
    int j = n - 1;
    if (j >= 0) {
        do {
            unsigned k = idx[i];
            struct { float c[3]; Box e; } L;   // centre then box: contiguous, as in the original frame
            Box& e = L.e;
            float* c = L.c;
            const Box& src = (*items)[k];
            e.mx[0] = src.mx[0]; e.mx[1] = src.mx[1]; e.mx[2] = src.mx[2];
            e.mn[0] = src.mn[0]; e.mn[1] = src.mn[1]; e.mn[2] = src.mn[2];
            c[0] = (e.mx[0] + e.mn[0]) * 0.5f;
            c[1] = (e.mx[1] + e.mn[1]) * 0.5f;
            c[2] = (e.mx[2] + e.mn[2]) * 0.5f;
            if (c[node->axis] > node->pos) {
                idx[i] = idx[j];
                idx[j] = k;
                --j;
                ExpandBox(node->right, e);
            } else {
                ++i;
                ExpandBox(node->left, e);
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

// @ 0x0072a8c0  (PARTIAL)
int FUN_0072a8c0(void* a, int b, int c, unsigned d, int e)
{
    (void)a; (void)b; (void)c; (void)d; (void)e;
    return 0;
}

// @ 0x0072aa80  (PARTIAL)
void* FUN_0072aa80(void* self, int n, int a, int b)
{
    (void)self; (void)n; (void)a; (void)b;
    return self;
}
