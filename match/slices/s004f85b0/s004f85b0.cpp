// w1g1 slice s004f85b0 -- SP::ForceGrid: a 512-bucket spatial hash of 0x80-byte SphereFields
// blocks (four spheres per block, one per SIMD lane).  Skinner module, unoptimized:
// /Od /Ob1 /MD /Gy /TP /arch:SSE2 /fp:fast (no /EHsc).
#include "s004f85b0.h"

// Reproduces the unused stack slots that the original's declined inline callees left behind.
template <int N> inline void ScratchSlots() { uint32_t s[N]; }

// ===========================================================================
// @ 0x004f8750
// Aligned allocation wrapper: 16-byte-aligns the block and stamps a header.
// ===========================================================================
void* FUN_004f8750(int size, int param2)
{
    int v33, n40, len;
    v33 = (int)FUN_00f473a0((uint32_t)(size + 0x1f), "Skinner/AlignedAlloc", 0, 0, 0, 0);
    len = (v33 + 0xf) & 0xfffffff0;
    n40 = len;
    *(int*)(n40) = 0xd6d6d6d6;
    *(int*)(n40 + 4) = v33;
    *(int*)(n40 + 8) = param2;
    *(int*)(n40 + 0xc) = 0x29292929;
    n40 += 0x10;
    return (void*)n40;
}

// ===========================================================================
// @ 0x004f85b0
// Constructor: stamps the vtables, picks the evaluator for this CPU, allocates
// the grid block, the field blocks and the 512 bucket heads.
// ===========================================================================
ForceGrid* ForceGrid::Init(float cost)
{
    uint32_t i;
    SphereFields** ptr;
    mpVtbl = (void*)&g_vtbl_13ef094;
    mnRefCount = 0;
    mpVtbl = (void*)&g_vtbl_13f1140;
    mnPointCount = 0;
    mnCapacity = 100;
    mpFields = 0;
    mfRadScale = 0.001f;
    mChunks.FUN_004fc4a0();
    mpBump = 0;
    mnRemaining = 0;
    FUN_004f8580(cost);
    int v = FUN_004f8120();
    uint32_t count;
    if (v >= 2)
        mpEval = (EvalFn)&ForceGrid::FUN_004f90a0;
    else if (v == 1)
        mpEval = &ForceGrid::FUN_004f9180;
    else
        mpEval = &ForceGrid::FUN_004f8d80;
    g_bForceGridInit = 1;
    count = 2;
    mpGridBlock = (Vector3*)FUN_004f8750(count * 4 * 4, 0);
    mpGridScale = mpGridBlock;
    mpGridOrigin = (Vector3*)((char*)mpGridBlock + 0x10);
    mpFields = (SphereFields*)FUN_004f8750((int)(mnCapacity << 7), 0);
    for (i = 0; i < mnCapacity; i++)
        mpFields[i].Clear(-1);
    ScratchSlots<9>();
    ptr = (SphereFields**)FUN_00f473a0(0x800, "Skinner/Surface", 0, 0, 0, 0);
    mppBuckets = ptr;
    memset(mppBuckets, 0, 0x800);
    FUN_004fc320(0);
    return this;
}

// ===========================================================================
// @ 0x004f87f0
// Destructor: releases the bucket table, the grid block and the field blocks,
// then the chunk list, and restores the base vtable.
// ===========================================================================
void ForceGrid::FUN_004f87f0()
{
    mpVtbl = (void*)&g_vtbl_13f1140;
    FUN_004fc320(1);
    FUN_00f47380(mppBuckets);
    FUN_004f80b0(mpGridBlock);
    FUN_004f80b0(mpFields);
    for (char* i = (char*)mChunks.mpBegin; i < (char*)mChunks.mpEnd; i += 4) {
    }
    FUN_004c0b80(&mChunks);
    mpVtbl = (void*)&g_vtbl_13ef094;
}

// ===========================================================================
// @ 0x004f8880
// Bump allocator for SphereFields blocks: carves an aligned sub-block out of the
// current pool chunk (or a fresh one, at least 0x8000 bytes) and stamps it with
// the same header FUN_004f8750 writes, so FUN_004f80b0 can free it.
// ===========================================================================
void* ForceGrid::FUN_004f8880(uint32_t size, int param3)
{
    size += 0x10;
    size = (size + 0xf) & 0xfffffff0u;
    char* base = mpBump;
    if (size > mnRemaining) {
        uint32_t nMin = 0x8000;
        uint32_t chunk = (size > nMin) ? size : nMin;
        base = (char*)g_pSPMemPool->FUN_00928a30(chunk, 0x10, 0, 0, 0, 0, 0, 0);
        mChunks.FUN_004fc610((void**)&base);
        mpBump = base;
        mnRemaining = chunk;
    }
    mpBump += size;
    mnRemaining -= size;
    uint32_t* p = (uint32_t*)((uint32_t)(base + 0xf) & 0xfffffff0u);
    p[0] = 0xd6d6d6d6;
    p[1] = (uint32_t)base;
    p[2] = (uint32_t)param3;
    p[3] = 0x29292929;
    return p + 4;
}

// ===========================================================================
// @ 0x004f89a0
// Chunk-list teardown: returns every chunk to the global pool and clears the
// bump state.
// ===========================================================================
void ForceGrid::FUN_004f89a0()
{
    int i = 0;
    SimpleVector* chunks = &mChunks;
    int count = (int)(chunks->mpEnd - chunks->mpBegin) / 4;
    for (; i < count; i++)
        g_pSPMemPool->FUN_009276c0(chunks->mpBegin[i]);
    mChunks.erase(mChunks.mpBegin, mChunks.mpEnd);
    mpBump = 0;
    mnRemaining = 0;
}

__forceinline const float& HkMax(const float& a, const float& b) { return a > b ? a : b; }

// ===========================================================================
// @ 0x004f8a40
// Insert one sphere: grow the block array if it is full, store the sphere in
// the next lane and widen the AABB.
// ===========================================================================
void ForceGrid::Insert(const Vector3* point, float strength, float radius, int id)
{
    strength = HkMax(strength, 0.0f);
    radius = HkMax(radius, 0.0f);
    if (mnPointCount == mnCapacity * 4) {
        uint32_t newCap = mnCapacity * 2 + 1;
        SphereFields* newBase = (SphereFields*)FUN_004f8750((int)(newCap << 7), 0);
        uint32_t i;
        for (i = 0; i < mnCapacity; i++)
            newBase[i] = mpFields[i];
        for (; i < newCap; i++)
            newBase[i].Clear(-1);
        FUN_004f80b0(mpFields);
        mpFields = newBase;
        mnCapacity = newCap;
    }
    uint32_t entryIdx = mnPointCount >> 2;
    uint32_t sub = mnPointCount & 3;
    mpFields[entryIdx].Set((int)sub, point, strength, radius, id);
    ((uint32_t*)((char*)mpFields - 8))[0] = entryIdx + 1;
    mnPointCount++;
    Vector3 rad;
    rad.x = radius; rad.y = radius; rad.z = radius;
    Vector3 diff;
    Vector3* pDiff = FUN_0041db10(&diff, point, &rad);
    Vector3 lo = *pDiff;
    Vector3 tMin;
    Vector3* pMin = FUN_0041c0c0(&tMin, &mMin, &lo);
    mMin = *pMin;
    Vector3 sum;
    Vector3* pSum = FUN_0041dc10(&sum, point, &rad);
    Vector3 hi = *pSum;
    Vector3 tMax;
    Vector3* pMax = FUN_0041bfb0(&tMax, &mMax, &hi);
    mMax = *pMax;
}

// ===========================================================================
// @ 0x004f8580
// Store the cost and its negation (the evaluators seed their sum with the latter).
// ===========================================================================
void ForceGrid::FUN_004f8580(float cost)
{
    mfNegCost = -cost;
    mfCost = cost;
}

// ===========================================================================
// @ 0x004f8d80
// Scalar evaluator: -cost plus every sphere's weighted contribution.
// ===========================================================================
void ForceGrid::FUN_004f8d80(const float* point, float* out)
{
    float sum = -mfCost;
    SphereFields* table = FUN_004f8f70(point);
    if (table != 0) {
        uint32_t n = *(uint32_t*)((char*)table - 8);
        for (uint32_t i = 0; i < n; i++)
            sum = ((SphereFields*)((char*)table + (i << 7)))->Distance(point) + sum;
    }
    *out = sum;
}

// ===========================================================================
// @ 0x004f8e20
// Weighted distance sum of the four lanes of a block.
// ===========================================================================
float SphereFields::Distance(const float* point)
{
    float sum = 0.0f;
    for (int i = 0; i < 4; i++) {
        if (mRadiusSq[i] != 0.0) {
            float dx = point[0] - mX[i];
            float dy = point[1] - mY[i];
            float dz = point[2] - mZ[i];
            float d2 = (dx * dx + dy * dy) + dz * dz;
            if (d2 < mRadiusSq[i]) {
                float t = d2 * mInvRadiusSq[i] - 1.0f;
                float t2 = t * t;
                sum = (mStrength[i] * t2) * t2 + sum;
            }
        }
    }
    return sum;
}

// ===========================================================================
// @ 0x004f8f70
// Bucket lookup: quantize the offset from the grid origin to a 64x8x4 cell and
// return that bucket's block array.
// ===========================================================================
SphereFields* ForceGrid::FUN_004f8f70(const float* point)
{
    Vector3 rel;
    Vector3* pRel = FUN_0041db10(&rel, (const Vector3*)point, mpGridOrigin);
    Vector3 off = *pRel;
    Vector3 grid;
    Vector3* pGrid = FUN_004fc510(&grid, &off, mpGridScale);
    Vector3 g = *pGrid;
    uint32_t idx = (uint32_t)((int)g.x * 64 + (int)g.y * 8 + (int)g.z);
    if (idx < 0x200)
        return mppBuckets[idx];
    return 0;
}

// ===========================================================================
// @ 0x004f9250
// Accumulate the cost and the force direction contributed by every block in the
// bucket that contains the point.
// ===========================================================================
bool ForceGrid::FUN_004f9250(const float* point, float* out)
{
    float cost = -mfCost;
    Vector3 acc;
    acc.x = 0.0f;
    acc.y = 0.0f;
    acc.z = 0.0f;
    SphereFields* table = FUN_004f8f70(point);
    if (table != 0) {
        uint32_t n = *(uint32_t*)((char*)table - 8);
        for (uint32_t i = 0; i < n; i++)
            ((SphereFields*)((char*)table + (i << 7)))->Accumulate(point, &cost, &acc.x);
    }
    out[0] = acc.x;
    out[1] = acc.y;
    out[2] = acc.z;
    return acc.x * acc.x + acc.y * acc.y + acc.z * acc.z > 1e-8f;
}

// ===========================================================================
// @ 0x004f9360
// Accumulate one block's contribution: the weighted cost sum and the gradient
// pushed into acc.
// ===========================================================================
void SphereFields::Accumulate(const float* point, float* cost, float* acc)
{
    for (int i = 0; i < 4; i++) {
        if (mRadiusSq[i] != 0.0) {
            float dx = point[0] - mX[i];
            float dy = point[1] - mY[i];
            float dz = point[2] - mZ[i];
            float d2 = (dx * dx + dy * dy) + dz * dz;
            if (d2 < mRadiusSq[i]) {
                float t = d2 * mInvRadiusSq[i] - 1.0f;
                float t2 = t * t;
                float g = (8.0f * mScaledStrength[i]) * t2 * t;
                *cost = (mStrength[i] * t2) * t2 + *cost;
                acc[0] = g * dx + acc[0];
                acc[1] = g * dy + acc[1];
                acc[2] = g * dz + acc[2];
            }
        }
    }
}
