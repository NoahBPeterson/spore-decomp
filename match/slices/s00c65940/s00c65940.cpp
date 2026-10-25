// Slice s00c65940: Simulator::cSimpleRotationRing / cSimpleRotationBall helpers.
// Module: Simulator; float helpers compiled with SSE -> /O2 /MD /Gy /TP /arch:SSE.
// Class names from the 2008 dev-build PDB. Both classes derive from cMorphHandle,
// which embeds a cSpatialObject at +0x34.
#include "types.h"
#include <math.h>
#include <intrin.h>

struct cSPVector3    { float x, y, z; };
struct cSPQuaternion { float x, y, z, w; };

struct cSimpleRotationRing;
struct cSimpleRotationBall;

// Object referenced by the +0xd0 view slot (flag word at +0x04).
struct cViewRef {
    char pad0[4];
    int  mFlags;                     // +0x04
};

// Object referenced by the +0x9c event slot (flags at +0x04, kind at +0x5d).
struct cEventRef {
    char          pad0[4];
    unsigned int  mFlags;            // +0x04
    char          pad8[0x5d - 0x08];
    unsigned char mKind;             // +0x5d
};

// Embedded cSpatialObject head at +0x34; its vtable lives here.
struct cSpatialHead {
    void** vftable;                  // +0x00
    void SetKey(const void* key);    // 0xc88810
};

// 0x28-byte transform sub-object at +0x128 (scale + 3x3 matrix).
struct cSub128 {
    float mScale;                            // +0x000
    float mMat00, mMat01, mMat02;            // +0x004,+0x008,+0x00c
    float mMat10, mMat11, mMat12;            // +0x010,+0x014,+0x018
    float mMat20;                            // +0x01c
    union { float mMat21; int mMat21i; };    // +0x020
    union { float mMat22; int mMat22i; };    // +0x024
    void Ctor(int a, int b);                 // 0x93a560
    void Init(int a, int b);                 // 0x93a480
};

// ---------------------------------------------------------------------------
// Shared base. Unknown spans are char pads; every named field is a real offset.
// ---------------------------------------------------------------------------
struct cMorphHandle {
    void**  vftable;                 // +0x000
    void**  vftable004;              // +0x004
    char    pad008[0x034 - 0x008];   // +0x008 .. +0x034
    cSpatialHead mSpatial;           // +0x034
    char    pad038[0x050 - 0x038];   // +0x038 .. +0x050
    unsigned int mEventFlags;        // +0x050
    char    pad054[0x09c - 0x054];   // +0x054 .. +0x09c
    cEventRef* mPtr9c;               // +0x09c
    void*   mPtrA0;                  // +0x0a0
    char    pad0a4[0x0d0 - 0x0a4];   // +0x0a4 .. +0x0d0
    cViewRef* mViewRef;              // +0x0d0
    char    pad0d4[0x118 - 0x0d4];   // +0x0d4 .. +0x118

    // The constructor also stores the sub-object vtable here (see ctors).
    union {
        void**        vftable118;    // +0x118
        unsigned char mFlags118;     // +0x118
    };
    float   mBaseX;                  // +0x11c
    union {
        float         mBaseY;        // +0x120
        unsigned char mByte120;      // +0x120
    };
    union {
        float   mBaseZ;              // +0x124
        int     mBaseZInt;           // +0x124
    };
    cSub128 mSub128;                 // +0x128 (scale + matrix)
    union { float mOffX; int mOffXi; };  // +0x150
    float   mOffY, mOffZ;            // +0x154,+0x158
    float   mAxisX, mAxisY, mAxisZ;  // +0x15c,+0x160,+0x164
    float   mVec1X, mVec1Y, mVec1Z;  // +0x168,+0x16c,+0x170
    float   mLo;                     // +0x174
    float   mHi;                     // +0x178
    float   mT;                      // +0x17c
    float   mU, mV;                  // +0x180,+0x184
    float   mF188;                   // +0x188
    float   mViewX, mViewY, mViewZ;  // +0x18c,+0x190,+0x194
    cSPQuaternion mQuat198;          // +0x198,+0x19c,+0x1a0,+0x1a4
    float   mSpeed;                  // +0x1a8
    float   mPhase;                  // +0x1ac
    float   mAmplitude;              // +0x1b0
    union {
        char  mActive;               // +0x1b4 (ball)
        float mRing1b4;              // +0x1b4 (ring)
    };

    cMorphHandle();                  // 0xc63be0

    // Embedded cSpatialObject (at +0x34) vtable accessors.
    void**  SpatialVt() { return mSpatial.vftable; }
    void SetPosition(cSPVector3* p) {
        ((void(__thiscall*)(void*, cSPVector3*))SpatialVt()[0x38 / 4])(&mSpatial, p);
    }
    void SetOrientation(cSPQuaternion* q) {
        ((void(__thiscall*)(void*, cSPQuaternion*))SpatialVt()[0x3c / 4])(&mSpatial, q);
    }
    void SetScale(float s) {
        ((void(__thiscall*)(void*, float))SpatialVt()[0x40 / 4])(&mSpatial, s);
    }

    void SetFacing(const cSPVector3& dir);   // 0xc65940
    void SetT(float t);                      // 0xc65af0
    void SetTLerp(float t);                  // 0xc65b50
    bool OnEvent(void* p);                   // 0xc65e80
    void OnView(void* view);                 // 0xc660f0
    void SetPhase(float v);                  // 0xc662b0
    void SetAmplitude(float v);              // 0xc66310
    void UpdateMatrix();                     // 0xc66370
    void SetRange(float lo, float hi);       // 0xc666f0

    // Declared-only helpers defined elsewhere in the module (addresses in comments).
    void UpdatePos();                        // 0xc64db0
    void UpdateQuat();                       // 0xc64f00
    void UpdateBallPos();                    // 0xc65610
    void RefreshScale();                     // 0xc63ae0
    char OnEventCheck(void* p);              // 0xc656c0
    void SetRingReset();                     // 0xc64170
};

struct cSimpleRotationRing : cMorphHandle {
    int   mRing1b8;                  // +0x1b8
    float mRing1bc;                  // +0x1bc
    float mRing1c0;                  // +0x1c0
    float mRing1c4;                  // +0x1c4
    float mRing1c8;                  // +0x1c8
    float mRing1cc;                  // +0x1cc
    int   mRing1d0;                  // +0x1d0
    cSimpleRotationRing();                   // 0xc65c00
    void* ScalarDtor(unsigned char flags);   // 0xc65bc0
};
struct cSimpleRotationBall : cMorphHandle {
    cSimpleRotationBall();                   // 0xc65f00
};

// ---- external helpers defined elsewhere in the module ----
cSPVector3* FUN_0059aed0(cSPVector3* out, const cSPVector3* in, const cSPQuaternion* q); // 0x59aed0
cSPQuaternion* SP_QuaternionFromFacingAndUp(cSPQuaternion* out, const cSPVector3* facing,
                                            const cSPVector3* up);                       // 0x69b600
void FUN_00c88810(void* spatial, const void* key); // 0xc88810

// ---- extern data ----
extern const float g_1693DD4, g_1693DD8, g_1693DDC;
extern const float g_1693DC8, g_1693DCC, g_1693DD0;
extern const float g_1693D74, g_1693D78, g_1693D7C;
extern const float g_15777D0, g_15777D4, g_15777D8, g_15777DC;
extern const float g_1485720;
extern const float g_13EC4B8;
extern const float g_13EB8B0;
extern const float g_1485378;
extern void* vtbl_cMorphHandleSub[];   // 0x14711a4
extern void* vtbl_ringPrimary[];       // 0x1471288
extern void* vtbl_ring004[];           // 0x1471274
extern void* vtbl_ring118[];           // 0x14711a8
extern void* vtbl_ring034[];           // 0x14711b0
extern void* vtbl_ballPrimary[];       // 0x14713c8
extern void* vtbl_ball004[];           // 0x14713b4
extern void* vtbl_ball118[];           // 0x14712ec
extern void* vtbl_ball034[];           // 0x14712f0
extern const char DAT_015777FC[];      // 0x15777fc
extern const char DAT_01577808[];      // 0x1577808

// ===========================================================================
// @ 0x00c65940
// ===========================================================================
void cMorphHandle::SetFacing(const cSPVector3& dir)
{
    double dx = dir.x, dy = dir.y, dz = dir.z;
    double lenSq = dx * dx + dy * dy + dz * dz + (double)g_13EC4B8;
    float v = (float)(1.0 / sqrt(lenSq));
    cSPVector3 n;
    n.x = dir.x * v;
    n.y = dir.y * v;
    n.z = dir.z * v;
    if (mAxisX == n.x && mAxisY == n.y && mAxisZ == n.z)
        return;
    mAxisX = n.x; mAxisY = n.y; mAxisZ = n.z;
    cSPVector3 m;
    if ((mAxisX == g_1693DD4 && mAxisY == g_1693DD8 && mAxisZ == g_1693DDC) ||
        (mAxisX == -g_1693DD4 && mAxisY == -g_1693DD8 && mAxisZ == -g_1693DDC)) {
        m.x = g_1693DC8; m.y = g_1693DCC; m.z = g_1693DD0;
    } else {
        m.x = g_1693DD4; m.y = g_1693DD8; m.z = g_1693DDC;
    }
    mVec1X = m.x; mVec1Y = m.y; mVec1Z = m.z;
    UpdatePos();
    UpdateQuat();
}

// ===========================================================================
// @ 0x00c65af0
// ===========================================================================
void cMorphHandle::SetT(float t)
{
    float* pf = &mHi;
    if (mHi > t)
        pf = &t;
    float* pg = &mLo;
    if (*pf > mLo)
        pg = pf;
    if (mT != *pg) {
        mT = *pg;
        UpdatePos();
    }
}

// ===========================================================================
// @ 0x00c65b50
// ===========================================================================
void cMorphHandle::SetTLerp(float t)
{
    float* pf = &mHi;
    float* pg = &mLo;
    t = (mHi - mLo) * t + mLo;
    if (t < *pf)
        pf = &t;
    if (*pf <= *pg)
        pf = pg;
    if (mT != *pf) {
        mT = *pf;
        UpdatePos();
    }
}

// ===========================================================================
// @ 0x00c65bc0  scalar deleting destructor
// ===========================================================================
void* cSimpleRotationRing::ScalarDtor(unsigned char flags)
{
    vftable = vtbl_cMorphHandleSub;
    _ReadWriteBarrier();
    int* p = *(int**)((char*)this + 0x30);
    if (p != 0 && *(p - 1) != 0)
        ::operator delete(p);
    if (flags & 1)
        ::operator delete(this);
    return this;
}

// ===========================================================================
// @ 0x00c65c00  Simulator::cSimpleRotationRing::cSimpleRotationRing
// ===========================================================================
cSimpleRotationRing::cSimpleRotationRing()
{
    vftable118 = vtbl_cMorphHandleSub;      // 0x14711a4
    mByte120 = 0;
    mBaseZInt = 0;
    mSub128.Ctor(4, 0);
    mSub128.Init(0, 0);
    mSub128.mMat21i = 0;
    mSub128.mMat22i = 0;
    mOffXi = 0;
    mAxisX = g_15777D0;
    mAxisY = g_15777D4;
    mAxisZ = g_15777D8;
    mVec1X = g_15777DC;
    vftable = vtbl_ringPrimary;
    vftable004 = vtbl_ring004;
    mSpatial.vftable = vtbl_ring034;
    vftable118 = vtbl_ring118;
    mVec1Z = g_1693DD4;
    mLo = g_1693DD8;
    mHi = g_1693DDC;
    mT = g_1693DC8;
    mU = g_1693DCC;
    mV = g_1693DD0;
    mF188 = g_15777D0;
    mViewX = g_15777D4;
    mViewY = g_15777D8;
    mViewZ = g_15777DC;
    mQuat198.x = g_1693D74;
    mQuat198.y = g_1693D78;
    mQuat198.z = g_1693D7C;
    mQuat198.w = g_15777D0;
    mSpeed = g_15777D4;
    mPhase = g_15777D8;
    mAmplitude = g_15777DC;
    mRing1b4 = 0.0f;
    mRing1b8 = 2;
    mRing1bc = 0.0f;
    mRing1c0 = 0.0f;
    float one = g_1485720;
    mRing1c4 = one;
    mRing1c8 = 0.0f;
    mRing1cc = one;
    mRing1d0 = 0;
    mSpatial.SetKey(DAT_015777FC);
    if (mRing1c8 != 0.0f || mRing1cc != 7.0f) {
        mRing1c8 = 0.0f;
        mRing1cc = 7.0f;
        SetRingReset();
    }
}

// ===========================================================================
// @ 0x00c65e80
// ===========================================================================
bool cMorphHandle::OnEvent(void* p)
{
    mEventFlags |= 8;
    if (!OnEventCheck(p))
        return false;

    mPtr9c->mFlags |= 0x100;
    mPtr9c->mKind = 4;
    bool b = ((int(__thiscall*)(void*, cEventRef*, int))(*(void***)mPtrA0)[0x68 / 4])(
                 mPtrA0, mPtr9c, 0) == 1;
    if (b) {
        ((void(__thiscall*)(void*, cEventRef*, float*, int))(*(void***)mPtrA0)[0x6c / 4])(
            mPtrA0, mPtr9c, &mQuat198.y, 0);
        ((cMorphHandle*)((char*)this - 0x34))->SetRingReset();
    }
    return b;
}

// ===========================================================================
// @ 0x00c65f00  Simulator::cSimpleRotationBall::cSimpleRotationBall
// ===========================================================================
cSimpleRotationBall::cSimpleRotationBall()
{
    vftable118 = vtbl_cMorphHandleSub;      // 0x14711a4
    mByte120 = 0;
    mBaseZInt = 0;
    mSub128.Ctor(4, 0);
    mSub128.Init(0, 0);
    mSub128.mMat21i = 0;
    mSub128.mMat22i = 0;
    mOffXi = 0;
    mAxisX = g_15777D0;
    mAxisY = g_15777D4;
    mAxisZ = g_15777D8;
    mVec1X = g_15777DC;
    vftable = vtbl_ballPrimary;
    vftable004 = vtbl_ball004;
    mSpatial.vftable = vtbl_ball034;
    vftable118 = vtbl_ball118;
    mVec1Z = g_1693D74;
    mLo = g_1693D78;
    mHi = g_1693D7C;
    mT = g_15777D0;
    mU = g_15777D4;
    mV = g_15777D8;
    mF188 = g_15777DC;
    mViewX = g_1693D74;
    mViewY = g_1693D78;
    mViewZ = g_1693D7C;
    mQuat198.x = g_15777D0;
    mQuat198.y = g_15777D4;
    mQuat198.z = g_15777D8;
    mQuat198.w = g_15777DC;
    mSpeed = 0.0f;
    mPhase = 0.0f;
    mAmplitude = g_1485720;
    mActive = 0;
    mSpatial.SetKey(DAT_01577808);
}

// ===========================================================================
// @ 0x00c660f0
// ===========================================================================
void cMorphHandle::OnView(void* view)
{
    if (mViewRef != 0) {
        if (view == 0) {
            mViewRef->mFlags &= ~1;
            return;
        }
        mViewRef->mFlags |= 1;
    }
    if (view == 0)
        return;

    bool changed = false;

    cSPVector3* pp = ((cSPVector3*(__thiscall*)(void*))(*(void***)view)[0x2c / 4])(view);
    cSPVector3 v;
    v.x = pp->x;
    v.y = pp->y;
    v.z = pp->z;
    if (mViewX != v.x || mViewY != v.y || mViewZ != v.z) {
        mViewX = v.x;
        mViewY = v.y;
        mViewZ = v.z;
        changed = true;
    }

    cSPQuaternion* pq = ((cSPQuaternion*(__thiscall*)(void*))(*(void***)view)[0x30 / 4])(view);
    cSPQuaternion q;
    q.x = pq->x;
    q.y = pq->y;
    q.z = pq->z;
    q.w = pq->w;
    if (mQuat198.x != q.x || mQuat198.y != q.y ||
        mQuat198.z != q.z || mQuat198.w != q.w) {
        mQuat198.x = q.x;
        mQuat198.y = q.y;
        mQuat198.z = q.z;
        mQuat198.w = q.w;
        changed = true;
        SetOrientation(&mQuat198);
    }

    float s = ((float(__thiscall*)(void*))(*(void***)view)[0x70 / 4])(view);
    if (mSpeed != s) {
        mSpeed = s;
        if (mActive != 0)
            RefreshScale();
        UpdateBallPos();
    } else if (changed) {
        UpdateBallPos();
    }
}

// ===========================================================================
// @ 0x00c662b0
// ===========================================================================
void cMorphHandle::SetPhase(float v)
{
    if (mPhase != v) {
        mPhase = v;
        UpdateBallPos();
        if (mActive != 0)
            SetScale(mAmplitude * mSpeed + mPhase);
    }
}

// ===========================================================================
// @ 0x00c66310
// ===========================================================================
void cMorphHandle::SetAmplitude(float v)
{
    if (mAmplitude != v) {
        mAmplitude = v;
        UpdateBallPos();
        if (mActive != 0)
            SetScale(mSpeed * mAmplitude + mPhase);
    }
}

// ===========================================================================
// @ 0x00c66370
// ===========================================================================
void cMorphHandle::UpdateMatrix()
{
    cSPVector3 A, B, C;
    ((void(__thiscall*)(void*, cSPVector3*, cSPVector3*))vftable[0x60 / 4])(this, &A, &B);
    ((void(__thiscall*)(void*, cSPVector3*))SpatialVt()[0x5c / 4])(&mSpatial, &C);

    // u = B x C (third component as emitted), then g = -(u x C)
    float u0 = B.y * C.z - B.z * C.y;
    float u1 = B.z * C.x - C.z * B.x;
    float u2 = C.y * B.x - B.y * C.x;
    float g0 = u2 * C.y - u1 * C.z;
    float g1 = u0 * C.z - u2 * C.x;
    float g2 = u1 * C.x - u0 * C.y;

    float lenSq = g2 * g2 + g1 * g1 + g0 * g0 + g_13EC4B8;
    float inv = 1.0f / sqrtf(lenSq);
    g0 *= inv;
    g1 *= inv;
    g2 *= inv;

    float m0, m1, m2;
    if (mFlags118 & 2) {
        float x = mOffX, y = mOffY, z = mOffZ;
        m0 = (mSub128.mMat20 * z + mSub128.mMat10 * y) + mSub128.mMat00 * x;
        m1 = (mSub128.mMat01 * x + mSub128.mMat21 * z) + mSub128.mMat11 * y;
        m2 = (mSub128.mMat02 * x + mSub128.mMat22 * z) + mSub128.mMat12 * y;
    } else {
        m0 = mOffX;
        m1 = mOffY;
        m2 = mOffZ;
    }

    float s = mSub128.mScale;
    float px = mBaseX + m0 * s;
    float py = mBaseY + m1 * s;
    float pz = mBaseZ + m2 * s;

    float dot = (g0 * px + pz * g2) + py * g1;
    float denom = (g0 * B.x + g1 * B.y) + g2 * B.z;
    if (denom == 0.0f)
        return;

    float num = ((A.x * g0 + A.z * g2) + A.y * g1) - dot;
    float t = -(num / denom);
    if (-t < 0.0f)
        return;

    float qx = A.x + t * B.x;
    float qy = A.y + t * B.y;
    float qz = A.z + t * B.z;
    float f = (qy - py) * C.y;
    f += (qx - px) * C.x;
    f += (qz - pz) * C.z;

    float* pf = &mHi;
    if (mHi > f)
        pf = &f;
    float* pg;
    if (*pf > mLo)
        pg = pf;
    else
        pg = &mLo;
    if (mT != *pg) {
        mT = *pg;
        UpdatePos();
    }
}

// ===========================================================================
// @ 0x00c666f0
// ===========================================================================
void cMorphHandle::SetRange(float lo, float hi)
{
    *(volatile float*)&mLo = lo;
    *(volatile float*)&mHi = hi;
    float t = mT;
    float* pf = &mHi;
    if (mHi > t)
        pf = &t;
    float* pg;
    if (*pf > mLo)
        pg = pf;
    else
        pg = &mLo;
    if (mT != *pg) {
        mT = *pg;
        UpdatePos();
    }
}
