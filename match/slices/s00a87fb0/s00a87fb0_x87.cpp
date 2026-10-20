// Slice s00a87fb0 (x87 half) -- functions that use the 387 FP stack (fld/fsqrt/fmul/fild/fstp),
// which cannot be reproduced under /arch:SSE. Mixed with SSE only for cvtsi2ss/cvttss2si, matching
// the original. Flags: /O2 /MD /Gy /EHsc /TP /GS- /fp:fast
#include "types.h"
#include <intrin.h>
#include <math.h>

// ---------------------------------------------------------------------------
// data globals referenced by literal address
extern const float DAT_01678264;   // 1.0f
extern const float DAT_01678260;   // 1.0f
extern const float DAT_01678278;   // 65536.0f
extern const float DAT_01678300;   // 1/65536
extern const float DAT_01678314;   // degree->radian factor
extern const float DAT_01485720;   // 1.0f
extern const float DAT_01471064;   // 0.5f
extern const float DAT_013f4fd0;   // 4294967296.0f
extern const uint8_t DAT_014582d4[];// cube->sphere index table
extern const float DAT_01677840[]; // ring table (stride 8)

// ---------------------------------------------------------------------------
struct Vector3 { float x, y, z; };

struct cTransform {                // 0x38 bytes
    uint16_t mFlags;               // +0x00
    uint16_t mModificationCount;   // +0x02
    Vector3  mTranslation;         // +0x04
    float    mScale;               // +0x10
    float    mRotation[9];         // +0x14
};

template <class T> struct SpVector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator0;
    uint32_t mAllocator1;
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
    bool empty() const { return mpBegin == mpEnd; }
};

struct cDistributeSample {         // 0x4c bytes
    cTransform mTransform;         // +0x00
    float      mColorAlpha[4];     // +0x38
    int        mNumber;            // +0x48
};

struct cGlobalParams {             // retail offsets (fields used here)
    char     pad00[0x60];
    float*   mpSizeCurve;          // +0x60
    float*   pSizeCurveEnd;        // +0x64
    char     pad68[0x74 - 0x68];
    float    mPitchVary;           // +0x74
    float*   mpPitchCurve;         // +0x78
    float*   pPitchCurveEnd;       // +0x7c
    char     pad80[0x8c - 0x80];
    float*   mpRollCurve;          // +0x8c
    float*   pRollCurveEnd;        // +0x90
    char     pad94[0xa0 - 0x94];
    float*   mpHeadingCurve;       // +0xa0
    float*   pHeadingCurveEnd;     // +0xa4
    char     pada8[0xb4 - 0xa8];
    float    mPitchOffset;         // +0xb4
    float    mPitchAmount;         // +0xb8
    float    mRollOffset;          // +0xbc
    float    mRollAmount;          // +0xc0
    float    mHeadingOffset;       // +0xc4
    float    mHeadingAmount;       // +0xc8
};

struct cDistributeEffect {
    char     pad00[0x14];
    void*    mDesc;                // +0x14
    int      mCollectionIndex;     // +0x18
    void*    mWorld;               // +0x1c
    cGlobalParams* mGlobalParams;  // +0x20
    char     pad24[0x9c - 0x24];
    int      mRenderCount;         // +0x9c
    float    mParamAltitudeRange[2]; // +0xa0
    SpVector<cDistributeSample> mRenderSamples;  // +0xa8
    SpVector<cDistributeSample> mSamples;        // +0xbc
    char     padc8[0xd4 - 0xc8];
    int      mTargetSampleCount;   // +0xd4
    char     padd8[0x188 - 0xd8];
};

// ===========================================================================
// @ 0x00a88400 -- anonymous-namespace'::CubeToSphereSurface(float* out, const float* p)
void FUN_00a88400(float* out, const float* p)
{
    float inv = 1.0f / sqrtf(p[1] * p[1] + p[0] * p[0] + 1.0f);
    int sel = (int)p[2];
    int idx = (sel >> 1) * 4;
    float s = inv;
    if (sel & 1)
        s = -inv;
    out[DAT_014582d4[idx + 0]] = p[0] * s;
    out[DAT_014582d4[idx + 1]] = p[1] * inv;
    out[DAT_014582d4[idx + 2]] = s;
}

// ===========================================================================
// @ 0x00a88250 -- copy [first,last) 0x18-byte transform records into dst
void FUN_00a88250(uint32_t* first, uint32_t* last, uint32_t* dst)
{
    if (first != last) {
        uint32_t* d5 = dst + 5;
        uint32_t* s5 = first + 5;
        do {
            if (dst != 0) {
                *dst = *first;
                d5[-4] = s5[-4];
                d5[-3] = s5[-3];
                d5[-2] = s5[-2];
                d5[-1] = s5[-1];
                *d5 = *s5;
            }
            first = first + 6;
            s5 = s5 + 6;
            dst = dst + 6;
            d5 = d5 + 6;
        } while (first != last);
    }
}
