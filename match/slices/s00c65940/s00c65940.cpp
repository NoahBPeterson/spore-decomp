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

// ---------------------------------------------------------------------------
// Shared base. Unknown spans are char pads; every named field is a real offset.
// ---------------------------------------------------------------------------
struct cMorphHandle {
    void**  vftable;                 // +0x000
    char    pad004[0x118 - 0x004];   // +0x004 .. +0x118
    unsigned int mFlags18;           // +0x118

    float   mBaseX, mBaseY, mBaseZ;  // +0x11c,+0x120,+0x124
    float   mScale;                  // +0x128
    float   mMat00, mMat01, mMat02;  // +0x12c,+0x130,+0x134
    float   mMat10, mMat11, mMat12;  // +0x138,+0x13c,+0x140
    float   mMat20, mMat21, mMat22;  // +0x144,+0x148,+0x14c
    float   mOffX, mOffY, mOffZ;     // +0x150,+0x154,+0x158
    float   mAxisX, mAxisY, mAxisZ;  // +0x15c,+0x160,+0x164
    float   mVec1X, mVec1Y, mVec1Z;  // +0x168,+0x16c,+0x170
    float   mLo;                     // +0x174
    float   mHi;                     // +0x178
    float   mT;                      // +0x17c
    float   mU, mV;                  // +0x180,+0x184
    char    pad188[0x198 - 0x188];   // +0x188 .. +0x198
    cSPVector3 mDir;                 // +0x198
    char    pad1a4[0x1a8 - 0x1a4];   // +0x1a4 .. +0x1a8
    float   mSpeed;                  // +0x1a8
    float   mPhase;                  // +0x1ac
    float   mAmplitude;              // +0x1b0
    char    mActive;                 // +0x1b4
    char    pad1b5[0x1d8 - 0x1b5];   // +0x1b5 .. end of object

    // Embedded cSpatialObject (at +0x34) vtable accessors.
    void**  SpatialVt() { return *(void***)((char*)this + 0x34); }
    void SetPosition(cSPVector3* p) {
        ((void(__thiscall*)(void*, cSPVector3*))SpatialVt()[0x38 / 4])((char*)this + 0x34, p);
    }
    void SetOrientation(cSPQuaternion* q) {
        ((void(__thiscall*)(void*, cSPQuaternion*))SpatialVt()[0x3c / 4])((char*)this + 0x34, q);
    }
    void SetScale(float s) {
        ((void(__thiscall*)(void*, float))SpatialVt()[0x40 / 4])((char*)this + 0x34, s);
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
extern const float g_1485720;
extern const float g_13EC4B8;
extern const float g_13EB8B0;
extern const float g_1485378;
extern void* vtbl_cMorphHandleSub[];   // 0x14711a4

// ===========================================================================
// @ 0x00c65940
// ===========================================================================
void cMorphHandle::SetFacing(const cSPVector3& dir)
{
    float v = 1.0f / sqrtf(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z + g_13EC4B8);
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
}

// ===========================================================================
// @ 0x00c65e80
// ===========================================================================
bool cMorphHandle::OnEvent(void* p)
{
    *(unsigned int*)((char*)this + 0x50) |= 8;
    bool b = false;
    if (OnEventCheck(p) != 0) {
        void* m = *(void**)((char*)this + 0x9c);
        *(unsigned int*)((char*)m + 4) |= 0x100;
        *(unsigned char*)((char*)m + 0x5d) = 4;
        void* world = *(void**)((char*)this + 0xa0);
        void** vt = *(void***)world;
        b = ((int(__thiscall*)(void*, void*, int))vt[0x68 / 4])(world, m, 0) == 1;
        if (b) {
            ((void(__thiscall*)(void*, void*, void*, int))vt[0x6c / 4])(
                world, m, (char*)this + 0x19c, 0);
            ((cMorphHandle*)((char*)this - 0x34))->SetRingReset();
        }
    }
    return b;
}

// ===========================================================================
// @ 0x00c65f00  Simulator::cSimpleRotationBall::cSimpleRotationBall
// ===========================================================================
cSimpleRotationBall::cSimpleRotationBall()
{
}

// ===========================================================================
// @ 0x00c660f0
// ===========================================================================
void cMorphHandle::OnView(void* view)
{
    (void)view;
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
}

// ===========================================================================
// @ 0x00c666f0
// ===========================================================================
void cMorphHandle::SetRange(float lo, float hi)
{
    mLo = lo;
    mHi = hi;
    float t = mT;
    float* pf = &mHi;
    if (mHi > t)
        pf = &t;
    float* pg = pf;
    if (*pf <= mLo)
        pg = &mLo;
    if (mT != *pg) {
        mT = *pg;
        UpdatePos();
    }
}
