// Swarm skin-paint particle: paint-variable evaluator helpers (color packing,
// channel-mask dispatch, index ring, evaluator setup/destruction).
// Unoptimized module: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"
#include <string.h>

struct Vector3 {
    float x, y, z;
};

// Vector math helpers: first argument is the result buffer, the caller pops.
Vector3* Vector3_Sub(Vector3* out, const Vector3* a, const Vector3* b);   // 0x41db10
Vector3* Vector3_Mul(Vector3* out, const Vector3* v, const float* s);     // 0x41dca0
Vector3* Vector3_Scale(Vector3* out, const float* s, const Vector3* v);   // 0x41de40
Vector3* Vector3_Add(Vector3* out, const Vector3* a, const Vector3* b);   // 0x41dc10
Vector3* Vector3_Div(Vector3* out, const Vector3* v, const float* s);     // 0x453880

// ------------------------------------------------------------------ color
// Four bytes in memory order b, g, r, a (the order 0x53e190 stores them in and
// the order 0x53eba0 truncates a float triple to).
struct cColor32 {
    union {
        struct {
            uint8_t mB;
            uint8_t mG;
            uint8_t mR;
            uint8_t mA;
        };
        uint32_t mBits;
    };
    cColor32* Set(uint8_t r, uint8_t g, uint8_t b, uint8_t a);  // 0x0053e190
};

// ------------------------------------------------------------ channel key
// Per-variable channel mask used by the paint evaluator (size 0x20).
struct cPaintKey {
    uint8_t mVariable;        // +0x00  paint variable index
    uint8_t mVariableXor;     // +0x01  mVariable ^ 1
    uint8_t mVariableBit;     // +0x02  1 << mVariable
    uint8_t mVariableBitXor;  // +0x03  1 << mVariableXor
    uint8_t mMaskChannel[4];  // +0x04  one bit per channel, taken from each color
    uint32_t mValue;          // +0x08
    uint8_t mMaskAll;         // +0x0c  OR of mMaskChannel[]
    uint8_t mApplyMode;       // +0x0d  mMaskAll & mask, shifted by mVariable
    uint8_t mPad0e[2];        // +0x0e
    cColor32 mChannels[4];    // +0x10  one packed 24-bit channel per source color

    cPaintKey* Init(uint8_t variable, uint32_t* pC0, uint32_t* pC1,
                    uint32_t* pC2, uint32_t* pC3, uint32_t* pValue); // 0x0053e1d0
    uint8_t    ApplyMask(uint8_t mask);                              // 0x0053e3a0
};

// ---------------------------------------------------------------- vectors
struct RingEntry {            // 8-byte slot of the 0x4000-entry rings
    union {
        struct {
            uint32_t mValue;  // +0x00
            uint32_t mIndex;  // +0x04
        };
        uint8_t mRaw[8];
    };
};

struct BatchEntry {           // 0x18-byte slot of the batch list at +0x50
    uint32_t mField00;        // +0x00
    int32_t  mOutIndex;       // +0x04
    int32_t  mVariableIndex;  // +0x08
    Vector3  mVec;            // +0x0c
};

// One 0x80-byte evaluator vertex block: three float planes of four lanes.
struct VertexBlock {
    float   mX[4];            // +0x00
    float   mY[4];            // +0x10
    float   mZ[4];            // +0x20
    uint8_t mRest[0x60];      // +0x30
};

typedef void (__thiscall* FnVecResize)(void* self, uint32_t count);
typedef void (__thiscall* FnVecDestroy)(void* self);

void FUN_005407a0();   // 0x5407a0  vector<8-byte>::resize
void FUN_00540950();   // 0x540950  vector<12-byte>::resize
void FUN_005404a0();   // 0x5404a0  vector<24-byte>::resize
void FUN_0045daf0();   // 0x45daf0  vector<8-byte> destroy
void FUN_004fd940();   // 0x4fd940  vector<24-byte> destroy
void FUN_00540520();   // 0x540520  vector<12-byte> destroy

struct VecPairs {
    RingEntry* mpBegin;     // +0x00
    RingEntry* mpEnd;       // +0x04
    RingEntry* mpCapacity;  // +0x08
    uint32_t   mAllocator[2];
    void Resize(uint32_t n) { ((FnVecResize)FUN_005407a0)(this, n); }
    void Destroy() { ((FnVecDestroy)FUN_0045daf0)(this); }
};

struct VecBatches {
    BatchEntry* mpBegin;
    BatchEntry* mpEnd;
    BatchEntry* mpCapacity;
    uint32_t    mAllocator[2];
    void Resize(uint32_t n) { ((FnVecResize)FUN_005404a0)(this, n); }
    void Destroy() { ((FnVecDestroy)FUN_004fd940)(this); }
};

struct VecVec3 {
    Vector3* mpBegin;
    Vector3* mpEnd;
    Vector3* mpCapacity;
    uint32_t mAllocator[2];
    void Resize(uint32_t n) { ((FnVecResize)FUN_00540950)(this, n); }
    void Destroy() { ((FnVecDestroy)FUN_00540520)(this); }
};

// -------------------------------------------------------------- evaluator
// Refcounted grid evaluator stored at +0x90/+0x94.  The dispatch table lives
// inside the object: +0x08 is the combine entry (ecx = the evaluator).
struct cPaintVarEvalGrid {
    void*    mpVptr;         // +0x00
    int32_t  mRefCount;      // +0x04
    void*    mpCombine;      // +0x08
    uint32_t mField0c;       // +0x0c
    uint32_t mField10;       // +0x10
    uint32_t mVertexCount;   // +0x14
    uint32_t mField18;       // +0x18
    VertexBlock* mpBlocks;   // +0x1c
    Vector3  mMin;           // +0x20
    Vector3  mMax;           // +0x2c
    Vector3  mCenter;        // +0x38

    Vector3* GetCenter(Vector3* out);                // 0x4f9660
    bool     GetBounds(Vector3* pMin, Vector3* pMax); // 0x4f95e0
};

struct RefCounted {
    void*   mpVptr;          // +0x00
    int32_t mRefCount;       // +0x04
    void Release();          // 0x453540
};

typedef char (__thiscall* FnCombine)(void* self, const Vector3* value, float* pDist);

// ------------------------------------------------------- paint context
struct cPaintVarCtx {
    void*      mpVptr;         // +0x00
    int32_t    mRefCount;      // +0x04
    Vector3    mOffset;        // +0x08  evaluator-space origin
    float      mScale;         // +0x14
    float      mInvScale;      // +0x18
    uint32_t   mLookupFlags;   // +0x1c
    VecPairs   mRing;          // +0x20  ring of emitted entries
    uint32_t   mField34;       // +0x34
    uint32_t   mNextSlot;      // +0x38
    VecPairs   mTable;         // +0x3c  value -> ring slot table
    VecBatches mBatches;       // +0x50
    uint32_t   mField64;       // +0x64
    VecVec3    mPts68;         // +0x68
    VecVec3    mPts7c;         // +0x7c
    cPaintVarEvalGrid* mpEval;    // +0x90
    cPaintVarEvalGrid* mpEvalAux; // +0x94

    void        Destroy();                                  // 0x0053e470
    void        Reset();                                    // 0x0053e580
    char        Generate();                                 // 0x0053e690
    cColor32*   MapColor(cColor32* out, const Vector3* p);  // 0x0053eba0
    Vector3*    ToLocal(Vector3* out, uint32_t color);      // 0x0053eb10
    void        ResetOffset();                              // 0x0053eca0
    RingEntry*  Register(uint32_t value, uint32_t slot);    // 0x0053ece0
};

// 0x53eaa0 (cdecl): out = pa + pb, w cleared
cColor32* VecAdd3(cColor32* out, const cColor32* pa, const cColor32* pb); // 0x53eaa0

extern void* gVtPaintVarCtx[];    // 0x13f3464  derived vtable stored by the destructor
extern void* gVtGmeRefCount[];    // 0x13ef094  shared RefCountTemplate vtable
extern float gHKRealZero;         // 0x1485378  _HK_REAL_ZERO
extern float gZero;               // 0x13eb1bc  g_zero
extern cColor32 gPaintVarModNormal[8];  // 0x15e2d08 modifier offsets

// =====================================================================
// Signed division that rounds the remainder like a floor() division,
// optionally reporting the quotient.
// @ 0x0053e120
int FUN_0053e120(int value, int divisor, int* pQuotient)
{
    int remainder;
    if (value >= 0) {
        if (pQuotient != 0)
            *pQuotient = value / divisor;
        return value % divisor;
    } else {
        if (pQuotient != 0)
            *pQuotient = -(-value / divisor + 1);
        remainder = -value % divisor;
        if (remainder != 0)
            remainder = divisor - remainder;
        return remainder;
    }
}

// @ 0x0053e190
cColor32* cColor32::Set(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    mB = b;
    mG = g;
    mR = r;
    mA = a;
    return this;
}

// One channel's contribution to the mask: a bit selected by its three bytes.
static __inline uint8_t ChannelBit(const cColor32* pChan)
{
    return (uint8_t)(1 << (pChan->mB | (pChan->mG << 1) | (pChan->mR << 2)));
}

// @ 0x0053e1d0
cPaintKey* cPaintKey::Init(uint8_t variable, uint32_t* pC0, uint32_t* pC1,
                           uint32_t* pC2, uint32_t* pC3, uint32_t* pValue)
{
    mVariable = variable;
    mValue = *pValue;
    {
        // slot walk over the four packed channels (kept as in the original)
        int* pScan = (int*)&mChannels[0];
        int count = 4;
        while (--count >= 0)
            ++pScan;
    }
    mChannels[0].mBits = *pC0;
    mChannels[1].mBits = *pC1;
    mChannels[2].mBits = *pC2;
    mChannels[3].mBits = *pC3;
    mMaskChannel[0] = ChannelBit(&mChannels[0]);
    mMaskChannel[1] = ChannelBit(&mChannels[1]);
    mMaskChannel[2] = ChannelBit(&mChannels[2]);
    mMaskChannel[3] = ChannelBit(&mChannels[3]);
    mMaskAll = (uint8_t)(mMaskChannel[0] | mMaskChannel[1] | mMaskChannel[2] | mMaskChannel[3]);
    mApplyMode = ApplyMask(mMaskAll);
    mVariableBit = (uint8_t)(1 << mVariable);
    mVariableXor = mVariable ^ 1;
    mVariableBitXor = (uint8_t)(1 << mVariableXor);
    return this;
}

// @ 0x0053e3a0
uint8_t cPaintKey::ApplyMask(uint8_t mask)
{
    uint8_t result = (uint8_t)(mMaskAll & mask);
    switch (mVariable) {
    case 0:
        result <<= 1;
        break;
    case 1:
        result >>= 1;
        break;
    case 2:
        result <<= 2;
        break;
    case 3:
        result >>= 2;
        break;
    case 4:
        result <<= 4;
        break;
    case 5:
        result >>= 4;
        break;
    }
    return result;
}

// Inline reference-count release used by the destructor.
static void SafeRelease(cPaintVarEvalGrid*& pEval)
{
    if (pEval != 0)
        ((RefCounted*)pEval)->Release();
}

// @ 0x0053e470
void cPaintVarCtx::Destroy()
{
    mpVptr = gVtPaintVarCtx;
    SafeRelease(mpEvalAux);
    SafeRelease(mpEval);
    mPts7c.Destroy();
    mPts68.Destroy();
    VecBatches* pBatches = &mBatches;
    for (BatchEntry* p = pBatches->mpBegin; p < pBatches->mpEnd; ++p) {
    }
    pBatches->Destroy();
    VecPairs* pTable = &mTable;
    for (RingEntry* p = pTable->mpBegin; p < pTable->mpEnd; ++p) {
    }
    pTable->Destroy();
    VecPairs* pRing = &mRing;
    for (RingEntry* p = pRing->mpBegin; p < pRing->mpEnd; ++p) {
    }
    pRing->Destroy();
    mpVptr = gVtGmeRefCount;
}

// @ 0x0053e580
void cPaintVarCtx::Reset()
{
    mRing.Resize(0x4000);
    mField34 = 0;
    mNextSlot = 0;
    VecPairs* pTable = &mTable;
    pTable->Resize(0x4000);
    memset(&pTable->mpBegin[0], 0xff, 0x20000);
    VecVec3* pPts68 = &mPts68;
    pPts68->Resize(0x8000);
    memset(&pPts68->mpBegin[0], 0xff, 0x60000);
    VecVec3* pPts7c = &mPts7c;
    pPts7c->Resize(0x8000);
    memset(&pPts7c->mpBegin[0], 0xff, 0x60000);
    mBatches.Resize(0x8000);
    mField64 = 0;
}

// @ 0x0053e690
char cPaintVarCtx::Generate()
{
    cPaintVarEvalGrid* ev = mpEval;
    Vector3 center;
    Vector3 color;
    Vector3_Div(&color, ev->GetCenter(&center), &mScale);
    if (color.x <= gHKRealZero || color.x >= 255.0f
        || color.y <= gHKRealZero || color.y >= 255.0f
        || color.z <= gHKRealZero || color.z >= 255.0f)
        return 0;

    float dist = gZero;
    uint32_t key = 0;
    cPaintVarEvalGrid* grid = mpEval;
    uint32_t blockCount = (grid->mVertexCount + 3) >> 2;
    for (uint32_t block = 0; block < blockCount; ++block) {
        VertexBlock* pBlock = &grid->mpBlocks[block];
        for (int lane = 0; lane < 4; ++lane) {
            Vector3 pos;
            pos.x = pBlock->mX[lane];
            pos.y = pBlock->mY[lane];
            pos.z = pBlock->mZ[lane];
            cColor32 packed;
            MapColor(&packed, &pos);
            for (uint32_t mod = 0; mod < 8; ++mod) {
                cColor32 shifted;
                VecAdd3(&shifted, &packed, &gPaintVarModNormal[mod]);
                key = shifted.mBits;
                Vector3 at;
                ToLocal(&at, key);
                ((FnCombine)ev->mpCombine)(ev, &at, &dist);
                if (dist >= 0.0f)
                    goto found;
            }
        }
    }
found:
    if (dist < 0.0f)
        return 0;

    Vector3 best;
    uint32_t iter = 0;
    cColor32 step;
    step.mB = 1;
    step.mG = 0;
    step.mR = 0;
    step.mA = 0;
    float dist2;
    do {
        cColor32 shifted;
        VecAdd3(&shifted, (const cColor32*)&key, &step);
        uint32_t candidate = shifted.mBits;
        Vector3 at;
        ToLocal(&at, candidate);
        ((FnCombine)ev->mpCombine)(ev, &at, &dist2);
        if (dist2 >= 0.0f) {
            key = candidate;
            best = at;
            dist = dist2;
        }
        ++iter;
        if (iter > 0x80)
            return 0;
    } while (dist2 >= 0.0f);

    RingEntry* pEntry = Register(key, 0);
    pEntry->mRaw[4] = 0;
    pEntry->mRaw[3] = 0;
    pEntry->mRaw[5] = 0;
    return 1;
}

// @ 0x0053eaa0
cColor32* VecAdd3(cColor32* out, const cColor32* pa, const cColor32* pb)
{
    uint8_t tB = (uint8_t)(pb->mB + pa->mB);
    uint8_t tG = (uint8_t)(pb->mG + pa->mG);
    uint8_t tR = (uint8_t)(pb->mR + pa->mR);
    out->mB = tB;
    out->mG = tG;
    out->mR = tR;
    out->mA = 0;
    return out;
}

// @ 0x0053eb10
Vector3* cPaintVarCtx::ToLocal(Vector3* out, uint32_t color)
{
    Vector3 c;
    c.x = (float)(uint8_t)(color >> 0x10);
    c.y = (float)(uint8_t)(color >> 8);
    c.z = (float)(uint8_t)(color & 0xff);
    Vector3 scaled;
    Vector3 local;
    Vector3* pLocal = Vector3_Add(&local, &mOffset, Vector3_Scale(&scaled, &mScale, &c));
    out->x = pLocal->x;
    out->y = pLocal->y;
    out->z = pLocal->z;
    return out;
}

// @ 0x0053eba0
cColor32* cPaintVarCtx::MapColor(cColor32* out, const Vector3* p)
{
    Vector3 delta;
    Vector3 scaled;
    Vector3* pScaled = Vector3_Mul(&scaled, Vector3_Sub(&delta, p, &mOffset), &mInvScale);
    int iX = (int)pScaled->x;
    int iY = (int)pScaled->y;
    int iZ = (int)pScaled->z;
    uint8_t vB = (uint8_t)iZ;
    uint8_t vG = (uint8_t)iY;
    uint8_t vR = (uint8_t)iX;
    out->mB = vB;
    out->mG = vG;
    out->mR = vR;
    out->mA = 0;
    return out;
}

// @ 0x0053eca0
void cPaintVarCtx::ResetOffset()
{
    Vector3 vMin;
    Vector3 vMax;
    cPaintVarEvalGrid* pEval = mpEval;
    pEval->GetBounds(&vMin, &vMax);
    mOffset = vMin;
}

// @ 0x0053ece0
RingEntry* cPaintVarCtx::Register(uint32_t value, uint32_t slot)
{
    uint32_t stored;
    uint32_t* pStored = &stored;
    mLookupFlags = (mNextSlot & 0xffffc000) | mLookupFlags;   // keep the overflow bits
    mNextSlot = mNextSlot & 0x3fff;
    mRing.mpBegin[mNextSlot].mValue = value;
    uint32_t index = mNextSlot;
    VecPairs* pTable = &mTable;
    *pStored = value;
    pTable->mpBegin[slot & 0x3fff].mValue = *pStored;
    pTable->mpBegin[slot & 0x3fff].mIndex = index;
    int32_t old = (int32_t)mNextSlot;
    mNextSlot = mNextSlot + 1;
    return &mRing.mpBegin[old];
}
