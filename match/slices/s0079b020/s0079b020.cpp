// slice s0079b020: model-split / index-buffer helper vectors (EASTL vector<ushort>, vector<vector<ushort>>)
// and the plane splitter of triangle lists (SP model compile, c:\...\UTFKernel + EASTL).
// /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

typedef unsigned int size_t;
extern "C" void* __cdecl memcpy(void*, const void*, size_t);
extern void* __cdecl EASTL_allocate(size_t size, const char* name, int a, int b, const char* file, int line);  // 0x00f473a0
extern void  __cdecl EASTL_free(void* p);                                                                       // 0x00f47380

#define EASTL_ALLOC_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
static inline void* DoAlloc(size_t n)
{
    return EASTL_allocate(n, "Graphics", 0, 0, EASTL_ALLOC_FILE, 0xd1);
}
static inline void DoFree(void* p)
{
    if (p && ((int*)p)[-1] != 0) EASTL_free(p);
}
inline void* operator new(size_t, void* p) { return p; }
inline void operator delete(void*, void*) {}

struct UShortVecBase {
    uint16_t* mpBegin;
    uint16_t* mpEnd;
    uint16_t* mpCapacity;
    UShortVecBase() {}
    ~UShortVecBase() { DoFree(mpBegin); }
};
struct UShortVec : UShortVecBase {

    uint16_t* DoRealloc(int n, const uint16_t* first, const uint16_t* last);   // 0x0079ae60
    void DoInsertValue(uint16_t* pos, const uint16_t& v);                      // 0x006f5bc0
    UShortVec& CopyFrom(const UShortVec& x);   // 0x0079b360 operator= (named so the checker can find our symbol)
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

// 0x14-byte record: a vector<uint16_t> followed by two more words.
struct UShortVecRec : UShortVec {
    int       mExtra0;
    int       mExtra1;

    UShortVecRec(const UShortVecRec& x)
    {
        int n = (int)(x.mpEnd - x.mpBegin);
        uint16_t* p = n ? (uint16_t*)DoAlloc(n * 2) : 0;
        mpBegin = p;
        mpEnd = p;
        mpCapacity = p + n;
        int bytes = (int)((char*)x.mpEnd - (char*)x.mpBegin);
        mpEnd = (uint16_t*)memcpy(p, x.mpBegin, bytes) + (bytes >> 1);
    }
    void DestructRange(uint16_t* first, uint16_t* last);   // 0x008dede0
    __forceinline ~UShortVecRec()
    {
        DestructRange(mpBegin, mpEnd);
    }
};

struct UShortVecSrc : UShortVec {
    int mAllocState;    // +0xc
};
struct UShortVecDst : UShortVec {
    void DoCreate(int n, void* alloc);    // 0x00799840
    UShortVecDst* Assign(const UShortVecSrc& x);   // 0x0079b150
};

// @ 0x0079b150  copy-construct a vector<ushort> from one that carries allocator state at +0xc
UShortVecDst* UShortVecDst::Assign(const UShortVecSrc& x)
{
    DoCreate((int)(x.mpEnd - x.mpBegin), (void*)&x.mAllocState);
    int bytes = (int)((char*)x.mpEnd - (char*)x.mpBegin);
    mpEnd = (uint16_t*)memcpy(mpBegin, x.mpBegin, bytes) + (bytes >> 1);
    return this;
}

// @ 0x0079b360  eastl::vector<uint16_t>::operator=
UShortVec& UShortVec::CopyFrom(const UShortVec& x)
{
    if (&x != this) {
        const uint16_t* const pFirst = x.mpBegin;
        const uint16_t* const pLast = x.mpEnd;
        const unsigned n = (unsigned)(pLast - pFirst);
        if (n > (unsigned)(mpCapacity - mpBegin)) {
            uint16_t* const pNewData = DoRealloc(n, pFirst, pLast);
            DoFree(mpBegin);
            mpBegin = pNewData;
            mpCapacity = pNewData + n;
            mpEnd = pNewData + n;
        } else if (n > (unsigned)(mpEnd - mpBegin)) {
            const unsigned sz = (unsigned)(mpEnd - mpBegin);
            memcpy(mpBegin, pFirst, sz * 2);
            const uint16_t* pMid = x.mpBegin + (mpEnd - mpBegin);
            memcpy(mpEnd, pMid, (char*)x.mpEnd - (char*)pMid);
            mpEnd = mpBegin + n;
        } else {
            memcpy(mpBegin, pFirst, (char*)pLast - (char*)pFirst);
            mpEnd = mpBegin + n;
        }
    }
    return *this;
}

extern void __cdecl UninitCopyRecs(UShortVecRec** out, UShortVecRec* first, UShortVecRec* last, UShortVecRec* dest, const void* extra);   // 0x0079a710

struct RecVecBase {
    UShortVecRec* mpBegin;
    UShortVecRec* mpEnd;
    UShortVecRec* mpCapacity;
    RecVecBase() {}
    ~RecVecBase() { DoFree(mpBegin); }
};
struct RecVec : RecVecBase {
    RecVec(const RecVec& x);
    ~RecVec();
};

void __stdcall DestroyRecs(UShortVecRec* first, UShortVecRec* last);
RecVec::~RecVec() { DestroyRecs(mpBegin, mpEnd); }

// @ 0x0079b020  eastl::vector<UShortVecRec> copy constructor
RecVec::RecVec(const RecVec& x)
{
    int n = (int)(x.mpEnd - x.mpBegin);
    UShortVecRec* p = n ? (UShortVecRec*)DoAlloc(n * 0x14) : 0;
    mpBegin = p;
    mpEnd = p;
    mpCapacity = p + n;
    UShortVecRec* res = 0;
    UninitCopyRecs(&res, x.mpBegin, x.mpEnd, p, &x);
    mpEnd = res;
}

// @ 0x0079b0d0  destroy a range of records
void __stdcall DestroyRecs(UShortVecRec* first, UShortVecRec* last)
{
    for (; first < last; ++first)
        first->~UShortVecRec();
}

// @ 0x0079b1c0  uninitialized_copy of records, destination iterator kept in *out
UShortVecRec** __cdecl UninitCopyRecs2(UShortVecRec** out, UShortVecRec* first, UShortVecRec* last, UShortVecRec* dest)
{
    *out = dest;
    for (; first != last; ++first) {
        UShortVecRec* cur = *out;
        if (cur)
            new (cur) UShortVecRec(*first);
        *out = *out + 1;
    }
    return out;
}

// @ 0x0079b2a0  uninitialized_fill_n of records
void __cdecl UninitFillRecs(UShortVecRec* dest, unsigned n, const UShortVecRec& x)
{
    for (; n > 0; --n, ++dest) {
        if (dest)
            new (dest) UShortVecRec(x);
    }
}

// ---------------------------------------------------------------------------------------------
// Split-mesh builder
struct Rec16 {          // vertex/edge origin record
    int   mSub;
    int   mA;
    int   mB;
    float mT;
    Rec16(int sub, int a, int b, float t) : mSub(sub), mA(a), mB(b), mT(t) {}
};
struct Rec20 {          // 5-word group record
    int mA, mIdx, mLimit, mSize, mExtra;
};

struct Rec16Vec {
    Rec16* mpBegin;
    Rec16* mpEnd;
    Rec16* mpCapacity;
    void DoInsertValue(Rec16* pos, const Rec16& v);       // 0x0079ace0
    void push_back(const Rec16& v)
    {
        if (mpEnd < mpCapacity) {
            Rec16* p = mpEnd;
            mpEnd = p + 1;
            if (p) *p = v;
        } else
            DoInsertValue(mpEnd, v);
    }
};
struct Rec20Vec {
    Rec20* mpBegin;
    Rec20* mpEnd;
    Rec20* mpCapacity;
    void DoInsertValue(Rec20* pos, const Rec20& v);       // 0x00428900
    void push_back(const Rec20& v)
    {
        if (mpEnd < mpCapacity) {
            Rec20* p = mpEnd;
            mpEnd = p + 1;
            if (p) *p = v;
        } else
            DoInsertValue(mpEnd, v);
    }
};
struct SplitParent {
    char     pad[0x30];
    Rec20Vec mGroups;
};

struct SplitCtx {
    SplitParent*  mpParent;     // +0
    Rec16Vec      mVerts;       // +4
    char          pad10[8];
    UShortVecRec* mpIndexSets;  // +0x18
    char          pad1c[0x10];
    Rec20         mCur;         // +0x2c (mCur.mIdx at +0x30 is the current index set)
    void AddVertex(int sub, int i);                       // 0x0079b4b0
    void AddEdge(int sub, int i, int j, float t);         // 0x0079b520
    void AddIndex(uint16_t v);                            // 0x0079b590
    void FinishGroup();                                   // 0x0079b5d0
};

// @ 0x0079b4b0  record "vertex i of sub-mesh sub is copied unchanged"
void SplitCtx::AddVertex(int sub, int i)
{
    mVerts.push_back(Rec16(sub, i, 0, 0.0f));
}

// @ 0x0079b520  record "new vertex on edge i..j at parameter t"
void SplitCtx::AddEdge(int sub, int i, int j, float t)
{
    mVerts.push_back(Rec16(sub, i, j, t));
}

// @ 0x0079b590  append an index to the current index set
void SplitCtx::AddIndex(uint16_t v)
{
    mpIndexSets[mCur.mIdx].push_back(v);
}

// @ 0x0079b5d0  close the current group: if its set grew past the limit, record it in the parent
void SplitCtx::FinishGroup()
{
    UShortVec& set = mpIndexSets[mCur.mIdx];
    mCur.mSize = (int)(set.mpEnd - set.mpBegin);
    if (mCur.mLimit < mCur.mSize)
        mpParent->mGroups.push_back(mCur);
}

struct SplitOuter {
    SplitParent*  mpParent;     // +0
    int           mPad4;
    SplitCtx      mCtx;         // +8
    UShortVecRec* mpSets;       // +0x48
    char          pad4c[0x10];
    Rec20         mCur;         // +0x5c
    void Flush(int a, int idx, int unused0, int unused1, int extra);   // 0x0079b630
};

// @ 0x0079b630
void SplitOuter::Flush(int a, int idx, int unused0, int unused1, int extra)
{
    mCtx.FinishGroup();
    UShortVec& set = mpSets[idx];
    mCur.mSize = (int)(set.mpEnd - set.mpBegin);
    if (mCur.mLimit < mCur.mSize) {
        mCur.mA = a;
        mCur.mIdx = idx;
        mCur.mExtra = extra;
        mpParent->mGroups.push_back(mCur);
    }
}

// ---------------------------------------------------------------------------------------------
struct SubmeshRef {
    void* mpModel;
    int   mVal;
};
struct ModelHdr {
    char     pad[0x30];
    struct Vec20 {                      // vector of 0x14-byte records at +0x30
        char* mpBegin;
        char* mpEnd;
        int size() const { return (int)((mpEnd - mpBegin) / 0x14); }
    } mRecords;
};
struct PairRec { void* mA; int mB; };
struct PairVec {
    PairRec* mpBegin;
    PairRec* mpEnd;
    PairRec* mpCapacity;
    void DoInsertValue(PairRec* pos, const PairRec& v);   // 0x006ec390
};
struct PtrVec {
    void** mpBegin;
    void** mpEnd;
    void** mpCapacity;
    void reserve(int n);                                   // 0x007658f0
    ~PtrVec() { DoFree(mpBegin); }
};
extern void __cdecl CompileToRwMeshes(void* model, int, PtrVec* out, int, int, int, int, int, int);   // 0x0072b630

// @ 0x0079b6b0  SP::anonymous_namespace::CompileSplitModelElement
void __cdecl CompileSplitModelElement(PairVec* out, SubmeshRef* ref)
{
    PtrVec meshes;
    meshes.mpBegin = 0;
    meshes.mpEnd = 0;
    meshes.mpCapacity = 0;
    meshes.reserve(((ModelHdr*)ref->mpModel)->mRecords.size());
    CompileToRwMeshes(ref->mpModel, 0, &meshes, 0, 0, 0, 0, 0, -1);
    int count = (int)(meshes.mpEnd - meshes.mpBegin);
    for (int i = 0; i < count; ++i) {
        PairRec r;
        r.mA = meshes.mpBegin[i];
        r.mB = ref->mVal;
        if (out->mpEnd < out->mpCapacity) {
            PairRec* p = out->mpEnd;
            out->mpEnd = p + 1;
            if (p) *p = r;
        } else
            out->DoInsertValue(out->mpEnd, r);
    }
}

// ---------------------------------------------------------------------------------------------
// Plane split of a triangle list.
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
    char     pad18[0x2c];
    Remap*   mpRemapBegin;              // +0x44
    Remap*   mpRemapEnd;                // +0x48
    char     pad4c[0x8c - 0x4c];
};
struct VertStream {                     // 0x20-byte vertex stream description
    int      pad0;
    char*    mpData;                    // +4
    uint16_t mFormat;                   // +8
    uint16_t mStride;                   // +0xa
    char     pad[0x20 - 0xc];
};
struct SplitModel {
    char        pad[8];
    VertStream* mpStreams;              // +8
    char        pad0c[0x10];
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
struct SplitPlane {
    int     pad0[2];
    int     mMode;          // +8
    PlaneEq mEq;            // +0xc
    int     mSide;          // +0x1c
    void SplitTriangles(SplitModel* model, SplitRange* rng, UShortVec* out, SplitCtx* ctx);   // 0x0079b7b0
};

static inline uint32_t FetchIndex(const IndexBuf* ib, int streamSel, int i)
{
    uint32_t mask = g_IndexMask[ib->mFormat];
    if (ib->mpRemapBegin == ib->mpRemapEnd)
        return *(uint32_t*)(ib->mStride * i + ib->mpData) & mask;
    const Remap* r = (const Remap*)((char*)ib->mpRemapBegin + *(int16_t*)(ib->mpRemapSel + 2 + streamSel * 4) * 0x10);
    return *(uint32_t*)((*(uint32_t*)(ib->mStride * i + ib->mpData) & mask) * r->mStride + r->mpData) & g_IndexMask[r->mFormat];
}
static inline uint16_t FetchIndex16(const IndexBuf* ib, int i)
{
    return *(uint16_t*)(ib->mStride * i + ib->mpData) & (uint16_t)g_IndexMask[ib->mFormat];
}

// @ 0x0079b7b0
void SplitPlane::SplitTriangles(SplitModel* model, SplitRange* rng, UShortVec* out, SplitCtx* ctx)
{
    int streamSel = FindStream(model, 1, 0, 3, 0xe);
    VertStream* vs = (VertStream*)((char*)model->mpStreams + streamSel * 0x20 + 0x10);
    IndexBuf* ib = model->mpIndexBufs + rng->mSub;
    int i = rng->mStart;
    if (i >= rng->mEnd)
        return;
    do {
        uint32_t i0, i1, i2;
        if (ib->mpRemapBegin == ib->mpRemapEnd) {
            uint32_t mask = g_IndexMask[ib->mFormat];
            uint32_t stride = ib->mStride;
            i0 = *(uint32_t*)(stride * i + ib->mpData) & mask;
            i1 = *(uint32_t*)(stride * (i + 1) + ib->mpData) & mask;
            i2 = *(uint32_t*)(stride * (i + 2) + ib->mpData) & mask;
        } else {
            uint32_t mask = g_IndexMask[ib->mFormat];
            const Remap* r = (const Remap*)((char*)ib->mpRemapBegin + *(int16_t*)(ib->mpRemapSel + 2 + streamSel * 4) * 0x10);
            uint32_t stride = ib->mStride;
            i0 = *(uint32_t*)((*(uint32_t*)(stride * i + ib->mpData) & mask) * r->mStride + r->mpData) & g_IndexMask[r->mFormat];
            i1 = *(uint32_t*)((*(uint32_t*)(stride * (i + 1) + ib->mpData) & mask) * r->mStride + r->mpData) & g_IndexMask[r->mFormat];
            i2 = *(uint32_t*)((*(uint32_t*)(stride * (i + 2) + ib->mpData) & mask) * r->mStride + r->mpData) & g_IndexMask[r->mFormat];
        }
        const float* v0 = (const float*)(vs->mStride * i0 + vs->mpData);
        const float* v1 = (const float*)(vs->mStride * i1 + vs->mpData);
        const float* v2 = (const float*)(vs->mStride * i2 + vs->mpData);
        int s0 = ((mEq.z * v0[2] + mEq.y * v0[1] + mEq.x * v0[0]) > mEq.d) == mSide;
        int s1 = ((mEq.z * v1[2] + mEq.y * v1[1] + mEq.x * v1[0]) > mEq.d) == mSide;
        int s2 = ((mEq.z * v2[2] + mEq.y * v2[1] + mEq.x * v2[0]) > mEq.d) == mSide;
        int sum = s1 + s2 + s0;
        uint16_t first;
        if (sum % 3 == 0) {
            if (s0 == sum % 3)
                goto next;
            first = FetchIndex16(ib, i);
            goto emit;
        }
        switch (mMode) {
        case 0:
            first = FetchIndex16(ib, i);
            goto emit;
        case 2:
            if (sum > 1) {
                first = FetchIndex16(ib, i);
                goto emit;
            }
            goto next;
        case 3: {
            int sub = rng->mSub;
            uint32_t base = (uint32_t)(ctx->mVerts.mpEnd - ctx->mVerts.mpBegin);
            uint16_t b16 = (uint16_t)base;
            if (s0 == 0) {
                if (s1 == 0) {
                    ctx->AddEdge(sub, i + 2, i, mEq.Intersect(v2, v0));
                    ctx->AddEdge(sub, i + 2, i + 1, mEq.Intersect(v2, v1));
                    ctx->AddVertex(sub, i + 2);
                } else {
                    ctx->AddEdge(sub, i + 1, i, mEq.Intersect(v1, v0));
                    ctx->AddVertex(sub, i + 1);
                    if (s2 == 0) {
                        ctx->AddEdge(sub, i + 1, i + 2, mEq.Intersect(v1, v2));
                    } else {
                        ctx->AddVertex(sub, i + 2);
                        ctx->AddEdge(sub, i + 2, i, mEq.Intersect(v2, v0));
                    }
                }
            } else {
                ctx->AddVertex(sub, i);
                if (s1 == 0) {
                    ctx->AddEdge(sub, i, i + 1, mEq.Intersect(v0, v1));
                    if (s2 != 0) {
                        ctx->AddEdge(sub, i + 2, i + 1, mEq.Intersect(v2, v1));
                        ctx->AddVertex(sub, i + 2);
                    } else {
                        ctx->AddEdge(sub, i, i + 2, mEq.Intersect(v0, v2));
                    }
                } else {
                    ctx->AddVertex(sub, i + 1);
                    ctx->AddEdge(sub, i + 1, i + 2, mEq.Intersect(v1, v2));
                    ctx->AddEdge(sub, i, i + 2, mEq.Intersect(v0, v2));
                }
            }
            ctx->AddIndex(b16);
            ctx->AddIndex((uint16_t)(base + 1));
            ctx->AddIndex((uint16_t)(base + 2));
            if (sum > 1) {
                ctx->AddIndex(b16);
                ctx->AddIndex((uint16_t)(base + 2));
                ctx->AddIndex((uint16_t)(base + 3));
            }
            goto next;
        }
        default:
            goto next;
        }
    emit:
        out->push_back(first);
        out->push_back(FetchIndex16(ib, i + 1));
        out->push_back(FetchIndex16(ib, i + 2));
    next:
        i += 3;
    } while (i < rng->mEnd);
}
