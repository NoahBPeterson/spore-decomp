// slice s0079d190: two-sided plane split of a triangle list (SP model compile).
// Sibling of SplitPlane::SplitTriangles (0x0079b7b0, slice s0079b020): this variant keeps
// both halves, writing whole triangles to an "above" and a "below" index list and, in
// cut mode, emitting the new vertices/indices for both sides through two SplitCtx builders.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
#include "types.h"

inline void* operator new(unsigned int, void* p) { return p; }
inline void operator delete(void*, void*) {}

// eastl::vector<uint16_t>
struct UShortVec {
    uint16_t* mpBegin;
    uint16_t* mpEnd;
    uint16_t* mpCapacity;
    int       mAllocator;
    void DoInsertValue(uint16_t* pos, const uint16_t& v);       // 0x006f5bc0
    void push_back_call(const uint16_t& v);                     // 0x006f66a0 (out-of-line push_back)
    void push_back(const uint16_t& v)
    {
        if (mpEnd < mpCapacity) {
            uint16_t* p = mpEnd;
            mpEnd = p + 1;
            if (p) *p = v;
        } else
            DoInsertValue(mpEnd, v);
    }
};

// 0x14-byte record: a vector<uint16_t> plus one more word.
struct UShortVecRec : UShortVec {
    int mExtra;
};

struct Rec16 {          // vertex/edge origin record
    int   mSub;
    int   mA;
    int   mB;
    float mT;
};
struct Rec16Vec {
    Rec16* mpBegin;
    Rec16* mpEnd;
    Rec16* mpCapacity;
};

struct SplitCtx {
    void*         mpParent;     // +0
    Rec16Vec      mVerts;       // +4
    int           pad10[2];
    UShortVecRec* mpIndexSets;  // +0x18
    int           pad1c[5];
    int           mCurIdx;      // +0x30 current index set
    void AddVertex(int sub, int i);                       // 0x0079b4b0
    void AddEdge(int sub, int i, int j, float t);         // 0x0079b520
    void AddIndex(uint16_t v);                            // 0x0079b590
    int VertexCount() const { return (int)(mVerts.mpEnd - mVerts.mpBegin); }
    void AddIndexInline(uint16_t v) { mpIndexSets[mCurIdx].push_back(v); }
};

extern uint32_t g_IndexMask[];          // 0x0140f544: mask per index-format code

struct Remap {                          // 0x10-byte index remap table
    int      pad0;
    char*    mpData;                    // +4
    uint16_t mFormat;                   // +8
    uint16_t mStride;                   // +0xa
    int      pad[1];
};
struct IndexBuf {                       // 0x8c-byte index buffer description
    int      pad0;
    char*    mpData;                    // +4
    uint16_t mFormat;                   // +8
    uint16_t mStride;                   // +0xa
    int      pad[2];
    char*    mpRemapSel;                // +0x14
    int      pad18[11];
    Remap*   mpRemapBegin;              // +0x44
    Remap*   mpRemapEnd;                // +0x48
    int      pad4c[(0x8c - 0x4c) / 4];
};
struct VertStream {                     // 0x20-byte vertex stream description
    int      pad0;
    char*    mpData;                    // +4
    uint16_t mFormat;                   // +8
    uint16_t mStride;                   // +0xa
    int      pad[5];
};
struct SplitModel {
    int         pad[2];
    VertStream* mpStreams;              // +8
    int         pad0c[4];
    IndexBuf*   mpIndexBufs;            // +0x1c
};
struct SplitRange {
    int pad0;
    int mSub;       // +4
    int mStart;     // +8
    int mEnd;       // +0xc
};
extern int __cdecl FindStream(SplitModel* model, int a, int b, int c, int d);    // 0x0071ddc0

struct PlaneEq {
    float x, y, z, d;
    float Intersect(const float* a, const float* b);      // 0x007998a0
};

static inline uint16_t FetchIndex16(const IndexBuf* ib, int i)
{
    return *(uint16_t*)(ib->mStride * i + ib->mpData) & (uint16_t)g_IndexMask[ib->mFormat];
}

struct SplitPlane2 {
    int     pad0[2];
    int     mMode;          // +8: 0 keep straddlers above, 1 below, 2 by majority, 3 cut
    PlaneEq mEq;            // +0xc
    void SplitTriangles(SplitModel* model, SplitRange* rng, UShortVec* above, UShortVec* below,
                        SplitCtx* ctxAbove, SplitCtx* ctxBelow);
};

// @ 0x0079d190
void SplitPlane2::SplitTriangles(SplitModel* model, SplitRange* rng, UShortVec* above, UShortVec* below,
                                 SplitCtx* ctxAbove, SplitCtx* ctxBelow)
{
    int streamSel = FindStream(model, 1, 0, 3, 0xe);
    IndexBuf* ib = model->mpIndexBufs + rng->mSub;
    VertStream* vs = (VertStream*)((char*)model->mpStreams + streamSel * 0x20 + 0x10);
    for (int i = rng->mStart; i < rng->mEnd; i += 3) {
        uint32_t i0, i1, i2;
        if (ib->mpRemapBegin == ib->mpRemapEnd) {
            uint32_t mask = g_IndexMask[ib->mFormat];
            uint32_t stride = ib->mStride;
            i0 = *(uint32_t*)(stride * i + ib->mpData) & mask;
            i1 = *(uint32_t*)(stride * (i + 1) + ib->mpData) & mask;
            i2 = *(uint32_t*)(stride * (i + 2) + ib->mpData) & mask;
        } else {
            const Remap* r = (const Remap*)((char*)ib->mpRemapBegin + *(int16_t*)(ib->mpRemapSel + 2 + streamSel * 4) * 0x10);
            uint32_t stride = ib->mStride;
            uint32_t mask = g_IndexMask[ib->mFormat];
            i0 = *(uint32_t*)((*(uint32_t*)(stride * i + ib->mpData) & mask) * r->mStride + r->mpData) & g_IndexMask[r->mFormat];
            i1 = *(uint32_t*)((*(uint32_t*)(stride * (i + 1) + ib->mpData) & mask) * r->mStride + r->mpData) & g_IndexMask[r->mFormat];
            i2 = *(uint32_t*)((*(uint32_t*)(stride * (i + 2) + ib->mpData) & mask) * r->mStride + r->mpData) & g_IndexMask[r->mFormat];
        }
        const float* v0 = (const float*)(vs->mStride * i0 + vs->mpData);
        const float* v1 = (const float*)(vs->mStride * i1 + vs->mpData);
        const float* v2 = (const float*)(vs->mStride * i2 + vs->mpData);
        int s0 = (mEq.z * v0[2] + mEq.y * v0[1] + mEq.x * v0[0]) > mEq.d;
        int s1 = (mEq.z * v1[2] + mEq.y * v1[1] + mEq.x * v1[0]) > mEq.d;
        int s2 = (mEq.z * v2[2] + mEq.y * v2[1] + mEq.x * v2[0]) > mEq.d;
        int sum = s2 + s1 + s0;
        if (sum % 3 == 0) {
            // whole triangle on one side
            if (s0 == sum % 3)
                goto emitBelow;
            goto emitAbove;
        }
        switch (mMode) {
        case 0:
            goto emitAbove;
        case 1:
            goto emitBelow;
        case 2: {
            UShortVec* dst = sum > 1 ? above : below;
            dst->push_back_call(FetchIndex16(ib, i));
            dst->push_back_call(FetchIndex16(ib, i + 1));
            dst->push_back_call(FetchIndex16(ib, i + 2));
            continue;
        }
        case 3: {
            int baseA = ctxAbove->VertexCount();
            int baseB = ctxBelow->VertexCount();
            if (s0 != 0) {
                ctxAbove->AddVertex(rng->mSub, i);
                if (s1 != 0) {
                    float t12 = mEq.Intersect(v1, v2);
                    float t02 = mEq.Intersect(v0, v2);
                    ctxAbove->AddVertex(rng->mSub, i + 1);
                    ctxAbove->AddEdge(rng->mSub, i + 1, i + 2, t12);
                    ctxAbove->AddEdge(rng->mSub, i, i + 2, t02);
                    ctxBelow->AddEdge(rng->mSub, i + 2, i, 1.0f - t02);
                    ctxBelow->AddEdge(rng->mSub, i + 2, i + 1, 1.0f - t12);
                    ctxBelow->AddVertex(rng->mSub, i + 2);
                } else {
                    float t01 = mEq.Intersect(v0, v1);
                    ctxAbove->AddEdge(rng->mSub, i, i + 1, t01);
                    ctxBelow->AddEdge(rng->mSub, i + 1, i, 1.0f - t01);
                    ctxBelow->AddVertex(rng->mSub, i + 1);
                    if (s2 != 0) {
                        float t21 = mEq.Intersect(v2, v1);
                        ctxAbove->AddEdge(rng->mSub, i + 2, i + 1, t21);
                        ctxAbove->AddVertex(rng->mSub, i + 2);
                        ctxBelow->AddEdge(rng->mSub, i + 1, i + 2, 1.0f - t21);
                    } else {
                        float t02 = mEq.Intersect(v0, v2);
                        ctxAbove->AddEdge(rng->mSub, i, i + 2, t02);
                        ctxBelow->AddVertex(rng->mSub, i + 2);
                        ctxBelow->AddEdge(rng->mSub, i + 2, i, 1.0f - t02);
                    }
                }
            } else {
                ctxBelow->AddVertex(rng->mSub, i);
                if (s1 != 0) {
                    float t10 = mEq.Intersect(v1, v0);
                    ctxAbove->AddEdge(rng->mSub, i + 1, i, t10);
                    ctxAbove->AddVertex(rng->mSub, i + 1);
                    ctxBelow->AddEdge(rng->mSub, i, i + 1, 1.0f - t10);
                    if (s2 != 0) {
                        float t20 = mEq.Intersect(v2, v0);
                        ctxAbove->AddVertex(rng->mSub, i + 2);
                        ctxAbove->AddEdge(rng->mSub, i + 2, i, t20);
                        ctxBelow->AddEdge(rng->mSub, i, i + 2, 1.0f - t20);
                    } else {
                        float t12 = mEq.Intersect(v1, v2);
                        ctxAbove->AddEdge(rng->mSub, i + 1, i + 2, t12);
                        ctxBelow->AddEdge(rng->mSub, i + 2, i + 1, 1.0f - t12);
                        ctxBelow->AddVertex(rng->mSub, i + 2);
                    }
                } else {
                    float t20 = mEq.Intersect(v2, v0);
                    float t21 = mEq.Intersect(v2, v1);
                    ctxAbove->AddEdge(rng->mSub, i + 2, i, t20);
                    ctxAbove->AddEdge(rng->mSub, i + 2, i + 1, t21);
                    ctxAbove->AddVertex(rng->mSub, i + 2);
                    ctxBelow->AddVertex(rng->mSub, i + 1);
                    ctxBelow->AddEdge(rng->mSub, i + 1, i + 2, 1.0f - t21);
                    ctxBelow->AddEdge(rng->mSub, i, i + 2, 1.0f - t20);
                }
            }
            ctxAbove->AddIndexInline((uint16_t)baseA);
            ctxAbove->AddIndexInline((uint16_t)(baseA + 1));
            ctxAbove->AddIndexInline((uint16_t)(baseA + 2));
            ctxBelow->AddIndexInline((uint16_t)baseB);
            ctxBelow->AddIndexInline((uint16_t)(baseB + 1));
            ctxBelow->AddIndexInline((uint16_t)(baseB + 2));
            // the side holding two original vertices is a quad: add its second triangle
            SplitCtx* quad = ctxBelow;
            int base = baseB;
            if (sum > 1) {
                base = baseA;
                quad = ctxAbove;
            }
            quad->AddIndex((uint16_t)base);
            quad->AddIndex((uint16_t)(base + 2));
            quad->AddIndex((uint16_t)(base + 3));
            continue;
        }
        default:
            continue;
        }
    emitAbove:
        above->push_back(FetchIndex16(ib, i));
        above->push_back(FetchIndex16(ib, i + 1));
        above->push_back(FetchIndex16(ib, i + 2));
        continue;
    emitBelow:
        below->push_back(FetchIndex16(ib, i));
        below->push_back(FetchIndex16(ib, i + 1));
        below->push_back(FetchIndex16(ib, i + 2));
    }
}
