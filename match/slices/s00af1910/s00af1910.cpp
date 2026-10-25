// Slice s00af1910: field-by-field copy assignment of the 0xF0-byte sweep/hit
// record shared by the planet-surface cast helpers (probe / sweep / path-trace
// results; the derived records append their own tail at +0xF0).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

typedef unsigned char u8;
typedef unsigned int  u32;

struct Vec3 { float x, y, z; };

// 0x38-byte transform record carried at +0x70 of the hit record.  This copy only
// needs its change-detecting assignment helper (cSPTransformOps::Assign).
struct cSPTransform {
    u32 mElems[0x38 / 4];                           // +0x00 transform payload
    cSPTransform* Assign(const cSPTransform& src);  // 0x00537DC0
};

// 0xF0-byte sweep/hit record.
struct cSweepResult {
    // The +0x00..+0x1F head is copied as one 32-byte aggregate.
    struct Head {
        u32   mNounID;        // +0x00
        void* mpObject;       // +0x04
        float mSpeedFactor;   // +0x08
        int   mbHeadOn;       // +0x0c
        u32   mReserved[4];   // +0x10
    } mHead;
    u32          mHitKind;         // +0x20
    u32          mHitSlot;         // +0x24
    Vec3         mHitCenter;       // +0x28
    Vec3         mHitNormal;       // +0x34
    u8           mbFlag;           // +0x40
    u8           mPad41[3];
    float        mDist;            // +0x44
    Vec3         mHitPos;          // +0x48
    float        mRadius;          // +0x54
    Vec3         mBoxMax;          // +0x58
    Vec3         mBoxMin;          // +0x64
    cSPTransform mTransform;       // +0x70 (0x38 bytes)
    Vec3         mMeshPoint;       // +0xa8
    u32          mVertCount;       // +0xb4
    void*        mpVerts;          // +0xb8
    u32          mSurfaceId;       // +0xbc
    u32          mSurfaceFlags;    // +0xc0
    u32          mExtraC4;         // +0xc4
    float        mExtraRadius;     // +0xc8
    Vec3         mExtraCC;         // +0xcc
    Vec3         mExtraD8;         // +0xd8
    Vec3         mExtraE4;         // +0xe4

    cSweepResult& operator=(const cSweepResult& src);   // 0x00af1910
};

// @ 0x00af1910
cSweepResult& cSweepResult::operator=(const cSweepResult& src)
{
    mHead      = src.mHead;             // +0x00..+0x1F, one aggregate copy
    mHitKind   = src.mHitKind;          // +0x20
    mHitSlot   = src.mHitSlot;          // +0x24
    mHitCenter = src.mHitCenter;        // +0x28
    mHitNormal = src.mHitNormal;        // +0x34
    mbFlag     = src.mbFlag;            // +0x40
    mDist      = src.mDist;             // +0x44
    mHitPos    = src.mHitPos;           // +0x48
    mRadius    = src.mRadius;           // +0x54
    mBoxMin    = src.mBoxMin;           // +0x64 (assigned before the +0x58 box)
    mBoxMax    = src.mBoxMax;           // +0x58
    mTransform.Assign(src.mTransform);  // +0x70, 0x00537DC0
    mMeshPoint    = src.mMeshPoint;     // +0xa8
    mVertCount    = src.mVertCount;     // +0xb4
    mpVerts       = src.mpVerts;        // +0xb8
    mSurfaceId    = src.mSurfaceId;     // +0xbc
    mSurfaceFlags = src.mSurfaceFlags;  // +0xc0
    mExtraC4      = src.mExtraC4;       // +0xc4
    mExtraRadius  = src.mExtraRadius;   // +0xc8
    mExtraCC      = src.mExtraCC;       // +0xcc
    mExtraD8      = src.mExtraD8;       // +0xd8
    mExtraE4      = src.mExtraE4;       // +0xe4
    return *this;
}
