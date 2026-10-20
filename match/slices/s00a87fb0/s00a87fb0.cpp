// Slice s00a87fb0 -- EA::Swarm::cDistributeEffect description IO + sample helpers.
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /fp:fast /arch=SSE
#include "types.h"
#include <intrin.h>

// ---------------------------------------------------------------------------
// IO helpers (cdecl)
extern "C" void FUN_0093a780(void* s, void* buf, int n, int pad);   // ReadInt32
extern "C" void FUN_0093a800(void* s, void* buf, int n, int pad);   // ReadUInt64
extern "C" void FUN_0093a700(void* s, void* buf, int n, int pad);   // ReadUInt16
extern "C" void FUN_0093a6c0(void* s, void* buf, int n);            // ReadUInt8
extern "C" void FUN_007d27d0(void* s, void* dst);                   // ReadIntVector
extern "C" void FUN_007ed920(void* s, void* dst);                   // IO read helper
extern "C" void FUN_00a85b00(void* s, void* dst);                   // IO read helper
extern "C" void FUN_00a87f50(void* s, void* dst);                   // IO read helper

// ---------------------------------------------------------------------------
// data globals referenced by literal address
extern const float DAT_01678264;
extern const float DAT_01678260;
extern const float DAT_01678278;
extern const float DAT_01678300;
extern const float DAT_01678314;
extern const float DAT_01485720;
extern const float DAT_01471064;
extern const float DAT_013f4fd0;
extern const float DAT_014853e0;
extern const float DAT_0147b9f0;
extern const float DAT_0156502c;
extern const float DAT_013eb8a0;
extern const float DAT_01677840[];
extern const uint8_t DAT_014582d4[];
extern const float DAT_01485378;
extern const float DAT_01678300;
extern const float DAT_01677840[];

// ---------------------------------------------------------------------------
// Layouts (retail: eastl sp_vector is 0x14 bytes)
struct Vector3 { float x, y, z; };
struct Vector2 { float x, y; };
struct Vector4 { float x, y, z, w; };
struct Matrix3 { float m[9]; };
struct U32Pair { uint32_t lo, hi; };   // 8-byte MSVC return (edx:eax)
union U64 { struct { uint32_t lo, hi; }; uint64_t v; };

struct cTransform {                    // 0x38 bytes
    uint16_t mFlags;                   // +0x00
    uint16_t mModificationCount;       // +0x02
    Vector3  mTranslation;             // +0x04
    float    mScale;                   // +0x10
    Matrix3  mRotation;                // +0x14
};

template <class T> struct SpVector {   // eastl::vector with sp_vector_allocator (retail 0x14 bytes)
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator0;
    uint32_t mAllocator1;
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
    bool empty() const { return mpBegin == mpEnd; }
};

struct cDistributeSample {             // 0x4c bytes
    cTransform mTransform;             // +0x00
    Vector4    mColorAlpha;            // +0x38
    int        mNumber;                // +0x48
};

struct cSurfaceRec {                   // 0x18 bytes
    void*    mSurface;                 // +0x00
    void*    mSurfaceInfo;             // +0x04
    uint32_t mNumStateBytes;           // +0x08
    uint32_t mStateDataOffset;         // +0x0c
    uint32_t mNumParticleBytes;        // +0x10
    uint32_t mParticleDataOffset;      // +0x14
};

// cIRenderer::cDrawInfo, embedded in cDistributeDescription at +0x118
struct cDrawInfo {                     // 0x20 bytes
    uint64_t mResourceID;              // +0x00
    uint8_t  mFormat;                  // +0x08
    uint8_t  mDrawMode;                // +0x09
    uint8_t  mDrawFlags;               // +0x0a
    uint8_t  mBuffer;                  // +0x0b
    int16_t  mLayer;                   // +0x0c
    float    mSortOffset;              // +0x10
    uint64_t mResourceID2;             // +0x18
};

// cGlobalParams (retail offsets; only fields touched by this slice are named)
struct cGlobalParams {                 // 0x120 bytes
    char     pad00[0x60];
    float*   mpSizeCurve;              // +0x60
    float*   pSizeCurveEnd;            // +0x64
    char     pad68[0x74 - 0x68];
    float    mPitchVary;               // +0x74
    float*   mpPitchCurve;             // +0x78
    float*   pPitchCurveEnd;           // +0x7c
    char     pad80[0x8c - 0x80];
    float*   mpRollCurve;              // +0x8c
    float*   pRollCurveEnd;            // +0x90
    char     pad94[0xa0 - 0x94];
    float*   mpHeadingCurve;           // +0xa0
    float*   pHeadingCurveEnd;         // +0xa4
    char     pada8[0xb4 - 0xa8];
    float    mPitchOffset;             // +0xb4
    float    mPitchAmount;             // +0xb8
    float    mRollOffset;              // +0xbc
    float    mRollAmount;              // +0xc0
    float    mHeadingOffset;           // +0xc4
    float    mHeadingAmount;           // +0xc8
};

// cIEffectsWorld : vtable only
struct cIEffectsWorld {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void* v20();  // +0x20 -> object with +0x24 / +0x38 methods
};

// returned by cIEffectsWorld::v20() on the cEffectsWorld implementation
struct IWorldThing {
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual void SetVisibleA(int id, bool visible);   // +0x24
    virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34();
    virtual void SetVisibleB(int id, bool visible);   // +0x38
};

// cDistributeEffect (retail offsets)
struct cDistributeEffect {
    char        pad00[0x14];
    void*       mDesc;                 // +0x14
    int         mCollectionIndex;      // +0x18
    cIEffectsWorld* mWorld;            // +0x1c
    cGlobalParams*  mGlobalParams;     // +0x20
    void*       mChildParams;          // +0x24
    uint32_t    mFlags;                // +0x28
    cTransform  mSourceTransform;      // +0x2c
    cTransform  mRigidTransform;       // +0x64
    int         mRenderCount;          // +0x9c
    Vector2     mParamAltitudeRange;   // +0xa0
    SpVector<cDistributeSample> mRenderSamples;  // +0xa8
    SpVector<cDistributeSample> mSamples;        // +0xbc
    int         mCurrentSampleCount;   // +0xc8
    int         mTargetSampleCount;    // +0xd4
    char        padd0[0xdc - 0xd0];
    SpVector<void*> mEffects;          // +0xd0
    int         mSetID;                // +0xe0
    uint64_t    mOverrideID;           // +0xe8
    uint8_t     mCurrentFormat;        // +0xf0
    uint8_t     mOffsets[5];           // +0xf1
    char        padf6[0xf8 - 0xf6];
    Vector3     mSubdivOffset;         // +0xf8
    Vector3     mSubdivScale;          // +0x104
    void*       mSubdivOwner;          // +0x110
    SpVector<cSurfaceRec> mSurfaceRecs;// +0x114
    SpVector<uint8_t> mSurfaceStateData; // +0x124
    SpVector<uint8_t> mSurfaceSampleData;// +0x134
    int         mSampleDataSize;       // +0x144
    void*       mEmitMap;              // +0x148
    void*       mColorMap;             // +0x14c
    void*       mPinMap;               // +0x150
    uint32_t    mMapModCount;          // +0x154
    float       mUpdateTime;           // +0x158
    Vector3     mColorScale;           // +0x15c
    float       mCurrentAlphaScale;    // +0x168
    float       mAlphaScale;           // +0x16c
    Vector2     mLODAlphaScale;        // +0x170
    float       mSizeScale;            // +0x178
    uint32_t    mSeqID;                // +0x17c
    uint32_t    mSeqCount;             // +0x180

    void FUN_00a87fb0(void* stream, int base);                        // 0x00a87fb0
    __int64 FUN_00a88220();                                       // 0x00a88220
    bool FUN_00a88350();                                              // 0x00a88350
    int  FUN_00a88390(int count, void** outBegin, void** outStride);  // 0x00a88390
    void FUN_00a886f0(int visible);                                   // 0x00a886f0
    void FUN_00a887b0(int index, float value);                        // 0x00a887b0
};

// @ 0x00a87fb0
void cDistributeEffect::FUN_00a87fb0(void* stream, int base)
{
    int tmp;
    FUN_0093a780(stream, &tmp, 1, 0);
    *(uint32_t*)(base + 8) = (uint32_t)tmp & 0xffff;
    FUN_0093a780(stream, (void*)(base + 0xc), 1, 0);
    FUN_0093a780(stream, (void*)(base + 0x10), 1, 0);
    FUN_0093a6c0(stream, (void*)(base + 0x14), 1);
    FUN_0093a780(stream, (void*)(base + 0x18), 1, 0);
    FUN_0093a6c0(stream, (void*)(base + 0x1c), 1);
    FUN_0093a780(stream, (void*)(base + 0x20), 1, 0);
    char* b = (char*)(base + 0x24);
    FUN_0093a700(stream, b, 1, 0);
    FUN_0093a780(stream, b + 0x10, 1, 0);
    ((void(__thiscall*)(void*, void*, int))(*(void***)stream)[0x30 / 4])(stream, b + 0x14, 0x24);
    ((void(__thiscall*)(void*, void*, int))(*(void***)stream)[0x30 / 4])(stream, b + 4, 0xc);
    FUN_007d27d0(stream, (void*)(base + 0x60));
    FUN_0093a780(stream, (void*)(base + 0x74), 1, 0);
    FUN_007d27d0(stream, (void*)(base + 0x78));
    FUN_007d27d0(stream, (void*)(base + 0x8c));
    FUN_007d27d0(stream, (void*)(base + 0xa0));
    FUN_0093a780(stream, (void*)(base + 0xb4), 1, 0);
    FUN_0093a780(stream, (void*)(base + 0xb8), 1, 0);
    FUN_0093a780(stream, (void*)(base + 0xbc), 1, 0);
    FUN_0093a780(stream, (void*)(base + 0xc0), 1, 0);
    FUN_0093a780(stream, (void*)(base + 0xc4), 1, 0);
    FUN_0093a780(stream, (void*)(base + 0xc8), 1, 0);
    FUN_007ed920(stream, (void*)(base + 0xcc));
    ((void(__thiscall*)(void*, void*, int))(*(void***)stream)[0x30 / 4])(stream, (void*)(base + 0xe0), 0xc);
    FUN_007d27d0(stream, (void*)(base + 0xec));
    FUN_0093a780(stream, (void*)(base + 0x100), 1, 0);
    FUN_00a87f50(stream, (void*)(base + 0x104));
    FUN_0093a800(stream, (void*)(base + 0x118), 1, 0);
    FUN_0093a800(stream, (void*)(base + 0x120), 1, 0);
    FUN_0093a800(stream, (void*)(base + 0x128), 1, 0);
    ((void(__thiscall*)(void*, void*, int))(*(void***)stream)[0x30 / 4])(stream, (void*)(base + 0x130), 8);
    FUN_00a85b00(stream, (void*)(base + 0x138));
    FUN_0093a6c0(stream, (void*)(base + 0x158), 1);
    FUN_0093a780(stream, (void*)(base + 0x15c), 1, 0);
    if (tmp > 3) {
        FUN_0093a780(stream, (void*)(base + 0x160), 1, 0);
        FUN_0093a780(stream, (void*)(base + 0x164), 1, 0);
        FUN_0093a780(stream, (void*)(base + 0x168), 1, 0);
        FUN_007d27d0(stream, (void*)(base + 0x16c));
    }
}

// @ 0x00a88220 -- returns the 8-byte (edx:eax) pair (a, b)
__int64 cDistributeEffect::FUN_00a88220()
{
    uint32_t a = *(uint32_t*)((char*)this + 0xf0);
    uint32_t b = *(uint32_t*)((char*)this + 0xf4);
    if ((a & b) == (uint32_t)-1) {
        char* w = *(char**)((char*)this + 0x14);
        a = *(uint32_t*)(w + 0x138);
        b = *(uint32_t*)(w + 0x13c);
    }
    U64 r;
    r.lo = a;
    r.hi = b;
    return r.v;
}

// @ 0x00a88350
bool cDistributeEffect::FUN_00a88350()
{
    void* v = *(void**)((char*)this + 0x15c);
    if (v == 0)
        return false;
    unsigned x = mFlags >> 10;
    if (x & 1)
        return false;
    int r = ((int(__thiscall*)(void*))(*(void***)v)[0x10 / 4])(v);
    if (r != *(int*)((char*)this + 0x168))
        return true;
    return false;
}

// @ 0x00a88390
int cDistributeEffect::FUN_00a88390(int count, void** outBegin, void** outStride)
{
    if (*(int*)((char*)this + 0xc) == 0 && count > 0) {
        void* src = *(void**)((char*)this + 4);
        ((void(__thiscall*)(void*))(*(void***)src)[0x08 / 4])(src);
        void* fn = *(void**)(*(void***)(*(void**)((char*)this + 4)))[0];
        int got = ((int(__stdcall*)(void*, void*, void*))fn)(
            *(void**)((char*)this + 8), (void*)((char*)this + 0x10), (void*)((char*)this + 0x14));
        *(int*)((char*)this + 8) -= got;
        *(int*)((char*)this + 0xc) = got;
    }
    int avail = *(int*)((char*)this + 0xc);
    *outStride = *(void**)((char*)this + 0x14);
    if (count > avail)
        count = avail;
    *outBegin = *(void**)((char*)this + 0x10);
    *(int*)((char*)this + 0xc) -= count;
    *(int*)((char*)this + 0x10) += *(int*)((char*)this + 0x14) * count * 4;
    return count;
}

// @ 0x00a88490 -- SquareToRing(float* out, float x, float y, float z)
void FUN_00a88490(float* out, float param_2, float param_3, float param_4)
{
    float fVar3 = param_3 * 2.0f - DAT_01678264;
    float fVar5 = param_2 * 2.0f - DAT_01678260;
    float fVar4, fVar2;
    if (fVar5 <= -fVar3) {
        if (fVar5 < fVar3) {
            fVar4 = (fVar3 / fVar5 + DAT_014853e0) * (DAT_0156502c * DAT_013eb8a0);
            fVar2 = -fVar5;
        }
        else {
            fVar4 = 0.0f;
            if (fVar3 != 0.0f)
                fVar4 = (DAT_0147b9f0 - fVar5 / fVar3) * (DAT_0156502c * DAT_013eb8a0);
            fVar2 = fVar3;
        }
    }
    else if (fVar3 < fVar5) {
        fVar4 = (fVar3 / fVar5) * (DAT_0156502c * DAT_013eb8a0);
        fVar2 = fVar5;
    }
    else {
        fVar4 = (2.0f - fVar5 / fVar3) * (DAT_0156502c * DAT_013eb8a0);
        fVar2 = fVar3;
    }
    float t = DAT_01678278 * fVar4 + 12582912.0f;
    fVar4 = fVar4 - (float)((int)t + (int)0xb4c00000) * DAT_01678300;
    float a = (fVar2 * param_4 + DAT_01485720) - param_4;
    unsigned sel = (unsigned)t & 0xf;
    float c2 = DAT_01677840[sel * 2 + 1];
    float c1 = DAT_01677840[sel * 2];
    out[0] = (c2 - ((c2 * fVar4) * DAT_01471064 + c1) * fVar4) * a;
    out[1] = ((c2 - (c1 * fVar4) * DAT_01471064) * fVar4 + c1) * a;
}

// @ 0x00a88640 -- call renderer vtable slots for active sub-surfaces
void FUN_00a88640(int base, void* renderer)
{
    short* p = (short*)(base + 2);
    for (int i = 0; i < 0x19; ++i) {
        unsigned int n = (unsigned short)*p;
        if (n != 0) {
            unsigned int off = (unsigned short)p[-1];
            void* arr = *(void**)(base + 0x64);
            ((void(__thiscall*)(void*, int, void*, unsigned int))(*(void***)renderer)[0x1c / 4])(
                renderer, i, (char*)arr + off * 4, n);
        }
        p += 2;
    }
    p = (short*)(base + 0x7a);
    for (int i = 0; i < 0xa; ++i) {
        unsigned int n = (unsigned short)*p;
        if (n != 0) {
            unsigned int off = (unsigned short)p[-1];
            void* arr = *(void**)(base + 0xa0);
            ((void(__thiscall*)(void*, int, void*, unsigned int))(*(void***)renderer)[0x20 / 4])(
                renderer, i, (char*)arr + off * 4, n);
        }
        p += 2;
    }
    int* q = (int*)(base + 0xb4);
    for (int i = 0; i < 9; ++i) {
        int v = *q;
        if (v != 0)
            ((void(__thiscall*)(void*, int, int))(*(void***)renderer)[0x24 / 4])(renderer, i, v);
        ++q;
    }
}

// @ 0x00a886f0 (EA::Swarm::cDistributeEffect::SetIsVisible)
void cDistributeEffect::FUN_00a886f0(int visible)
{
    if ((visible & 0xff) == 0)
        mFlags &= ~2u;
    else
        mFlags |= 2;

    if ((mFlags & 1) == 0)
        return;

    if (*(int*)((char*)this + 0xec) >= 0) {
        char b;
        if ((visible & 0xff) != 0 && *(int*)((char*)this + 0xd4) > 0) {
            b = 1;
            if (*(int*)((char*)this + 0xd4) != *(int*)((char*)this + 0xd0))
                b = 0;
        }
        else {
            b = 0;
        }
        int flag = (*(uint32_t*)((char*)mDesc + 8) >> 8) & 1;
        IWorldThing* thing = (IWorldThing*)mWorld->v20();
        if (flag)
            thing->SetVisibleA(*(int*)((char*)this + 0xec), b);
        else
            thing->SetVisibleB(*(int*)((char*)this + 0xec), b);
    }

    int n = (int)(*(void***)((char*)this + 0xdc) - *(void***)((char*)this + 0xd8));
    for (int i = 0; i < n; ++i) {
        void* o = *(void**)(*(char**)((char*)this + 0xd8) + i * 4);
        ((void(__thiscall*)(void*, int))(*(void***)o)[0x28 / 4])(o, visible);
    }
}

// @ 0x00a887b0
void cDistributeEffect::FUN_00a887b0(int index, float value)
{
    if (*(int*)((char*)this + 0xbc) == *(int*)((char*)this + 0xc0)) {
        if (*(int*)((char*)this + 0xa8) != *(int*)((char*)this + 0xac)) {
            *(float*)(index * 0x4c + 0x44 + *(int*)((char*)this + 0xa8)) = value;
            return;
        }
    }
    else {
        *(float*)(index * 0x4c + 0x44 + *(int*)((char*)this + 0xbc)) = value;
    }
}
