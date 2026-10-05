// Slice s00719e10: SP::cMeshBuilder methods (BeginMesh/ClearMeshInfo/etc.) and the
// eastl::vector<T28>::resize instance. Optimized module with SSE:
// /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast.
#include "types.h"
#include <intrin.h>

typedef unsigned int size_t;

void SpFree(void* p);                                        // 0x00f47380
void* SpAlloc(unsigned size, const char* area, int a, int b, const char* file, int line); // 0x00f473a0

struct cSPVector2 { float x, y; };
struct cSPVector3 { float x, y, z; };
struct tMDUByte4 { unsigned char a, b, c, d; };
struct Float4 { float x, y, z, w; };

// sp_vector: 3 pointers + a 4-byte allocator (16 bytes total).
template <typename T>
struct spvec {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAlloc[1];
    spvec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    __forceinline ~spvec() { if (mpBegin && ((uint32_t*)mpBegin)[-1]) SpFree(mpBegin); }
    void clear();
    void erase(T* first, T* last);
    void resize(uint32_t n);
};
template <typename T>
struct spvec1 { spvec<T> v; uint32_t mAfter; };

// 0x28-byte element: two 16-byte vectors at +0 and +0x14 (scalars at +0x10, +0x24).
struct T28 {
    int* mB0; int* mE0; int* mC0; uint32_t mA0;   // +0x00
    uint32_t mX;                                  // +0x10
    int* mB1; int* mE1; int* mC1; uint32_t mA1;   // +0x14
    uint32_t mY;                                  // +0x24
    T28() { mB0 = 0; mE0 = 0; mC0 = 0; mB1 = 0; mE1 = 0; mC1 = 0; }
    ~T28() throw() { if (mB1 && ((uint32_t*)mB1)[-1]) SpFree(mB1);
                     if (mB0 && ((uint32_t*)mB0)[-1]) SpFree(mB0); }
};
struct Vec28 {
    T28* mpBegin; T28* mpEnd; T28* mpCapacity; uint32_t mAlloc[1];
    void insert(T28* position, uint32_t n, const T28& value);   // 0x00719a00
    void erase(T28* first, T28* last);                          // 0x007199b0
    void resize(uint32_t n);
};

// 0xd0-byte element (fills cMeshBuilder::mSections).
struct T140 { uint32_t mData[0x34]; T140(); ~T140(); T140(const T140&); };

// Simple non-atomic refcounted base for the AutoRefCount<> field.
struct RefCounted {
    void** mpVtbl;      // +0x0
    long   mnRefCount;  // +0x4
    int Release()
    {
        if (_InterlockedExchangeAdd(&mnRefCount, -1) == 1) {
            mnRefCount = 1;
            ((void (__thiscall*)(RefCounted*, int))mpVtbl[0])(this, 1);
            return 0;
        }
        return mnRefCount;
    }
};

struct cMeshBuilder {
    char pad_00[0x8];
    spvec1<cSPVector3> mPositions;                   // +0x08
    spvec1<cSPVector3> mNormals;                     // +0x1c
    spvec1<cSPVector2> mTexCoords[4];                // +0x30
    spvec1<tMDUByte4>  mColors[2];                   // +0x80
    spvec1<int>        mV0;                          // +0xa8
    spvec1<int>        mV1;                          // +0xbc
    spvec1<T140>       mSections;                    // +0xd0
    spvec1<Float4>     mV2;                          // +0xe4   (0x14-byte element)
    spvec1<uint64_t>   mV3;                          // +0xf8   (8-byte element)
    spvec1<int>        mV4;                          // +0x10c
    spvec1<int>        mV5;                          // +0x120
    spvec1<int>        mV6;                          // +0x134
    RefCounted*        mMeshData;                    // +0x148
    uint32_t           mKey;                         // +0x14c
    bool               mInMesh;                      // +0x150
    char pad_151[7];
    int                m158;                         // +0x158
    int                m15c;                         // +0x15c
    int                m160;                         // +0x160
    int                m164;                         // +0x164
    int                m168;                         // +0x168
    int                m16c;                         // +0x16c
    int                m170;                         // +0x170
    int                m174;                         // +0x174
    int                m178;                         // +0x178
    int                m17c;                         // +0x17c
    int                m180;                         // +0x180
    int                m184;                         // +0x184
    char pad_188[0x1c8 - 0x188];

    void BeginMesh();
    void ClearMeshInfo();
};

int  cMeshBuilder_ClearChildVec(cMeshBuilder* self, int a, void* b);   // 0x00717820
void ClearAnimatedBabyVec(uint32_t a, uint32_t b);                     // 0x009c69f0

// ===========================================================================
// @ 0x0071a930
void Vec28::resize(uint32_t n)
{
    if (n > (uint32_t)(mpEnd - mpBegin)) {
        T28 v;
        insert(mpEnd, n - (uint32_t)(mpEnd - mpBegin), v);
    } else {
        erase(mpBegin + n, mpEnd);
    }
}

// @ 0x0071aa20
void cMeshBuilder::BeginMesh()
{
    mInMesh = true;
    if (mMeshData == 0)
        ClearMeshInfo();
    if (mMeshData != 0) {
        RefCounted* p = mMeshData;
        mMeshData = 0;
        p->Release();
    }
    mKey = 0x9f84a565;
    m164 = (int)(mSections.v.mpEnd - mSections.v.mpBegin);
    m168 = (int)(mPositions.v.mpEnd - mPositions.v.mpBegin);
    m16c = (int)(mNormals.v.mpEnd - mNormals.v.mpBegin);
    m170 = (int)(mTexCoords[0].v.mpEnd - mTexCoords[0].v.mpBegin);
    m174 = (int)(mTexCoords[1].v.mpEnd - mTexCoords[1].v.mpBegin);
    m178 = (int)(mTexCoords[2].v.mpEnd - mTexCoords[2].v.mpBegin);
    m17c = (int)(mTexCoords[3].v.mpEnd - mTexCoords[3].v.mpBegin);
    m180 = (int)(mColors[0].v.mpEnd - mColors[0].v.mpBegin);
    m184 = (int)(mColors[1].v.mpEnd - mColors[1].v.mpBegin);
    m158 = -1;
    m15c = -1;
    m160 = -1;
}

// @ 0x0071a650
void cMeshBuilder::ClearMeshInfo()
{
    mV0.v.clear();
    mV1.v.clear();
    mV2.v.clear();
    mV3.v.clear();
    for (int i = 0; i < 4; ++i)
        mTexCoords[i].v.clear();
    for (int i = 0; i < 2; ++i)
        mColors[i].v.clear();
    ClearAnimatedBabyVec((uint32_t)(size_t)mV4.v.mpEnd, (uint32_t)(size_t)mV5.v.mpEnd);
    mV5.v.erase(mV5.v.mpBegin, mV5.v.mpEnd);
    mV6.v.erase(mV6.v.mpBegin, mV6.v.mpEnd);
    mV2.v.erase(mV2.v.mpBegin, mV2.v.mpEnd);
    mV6.v.erase(mV6.v.mpBegin, mV6.v.mpEnd);
    mV2.v.erase(mV2.v.mpBegin, mV2.v.mpEnd);
    mV3.v.erase(mV3.v.mpBegin, mV3.v.mpEnd);
}

// @ 0x0071ab60
void cMeshBuilder_Transform(cMeshBuilder* self, uint32_t param)
{
    self->mV5.v.resize(param);
    Float4 m[3];
    float* p = (float*)m;
    for (int i = 0; i < 12; ++i)
        p[i] = 0.0f;
    m[0].x = 1.0f;
    m[1].y = 1.0f;
    m[2].z = 1.0f;
    cMeshBuilder_ClearChildVec(self, param, m);
}

// @ 0x00719e10
// Large vertex-assembly routine: recomputes the per-attribute dirty mask from the
// 8 optional vertex streams, grows/adjusts the section vector (T140), then walks the
// primitive list emitting position/normal/texcoord/colour indices into the target
// section's streams.  Behavioural skeleton only (partial): the mask/entry helpers and
// the attribute loop are summarised rather than reproduced.
void cMeshBuilder_EndMesh(cMeshBuilder* self)
{
    unsigned mask = 0;
    if (self->mPositions.v.mpEnd != self->mPositions.v.mpBegin) mask |= 1;
    if (self->mNormals.v.mpEnd   != self->mNormals.v.mpBegin)   mask |= 2;
    if (self->mTexCoords[0].v.mpEnd != self->mTexCoords[0].v.mpBegin) mask |= 4;
    if (self->mTexCoords[1].v.mpEnd != self->mTexCoords[1].v.mpBegin) mask |= 8;
    if (self->mTexCoords[2].v.mpEnd != self->mTexCoords[2].v.mpBegin) mask |= 0x10;
    if (self->mTexCoords[3].v.mpEnd != self->mTexCoords[3].v.mpBegin) mask |= 0x20;
    if (self->mColors[0].v.mpEnd   != self->mColors[0].v.mpBegin)   mask |= 0x40;
    if (self->mColors[1].v.mpEnd   != self->mColors[1].v.mpBegin)   mask |= 0x80;
    (void)mask;
}
