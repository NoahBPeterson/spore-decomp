// Slice s005a33c0 -- SP::cEditorCameraController::UpdateAutoZoom (0x005a33c0), a wrapper and a large UI function.
// Module flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast.
#include "types.h"
#include <math.h>

extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)
inline float Abs(float x) { float r = (float)fabs(x); return r; }

// Retail float constants (address in the comment).
extern float kRate_13f6a30;      // 0x013f6a30  0.008f
extern float kClampLo_13eb960;   // 0x013eb960  0.01f
extern float kOne_1485720;       // 0x01485720  1.0f
extern float kNegTurn_13f6a3c;   // 0x013f6a3c -0.2f
extern float kPosTurn_13f69ac;   // 0x013f69ac  0.2f
extern float kNegZoom_13f6a38;   // 0x013f6a38 -0.05f
extern float kPosZoom_13ec478;   // 0x013ec478  0.05f
extern float kHalfPi_150f2c4;    // 0x0150f2c4  1.5707964f
extern float kHalf_1471064;      // 0x01471064  0.5f
extern float kPointOne_1488874;  // 0x01488874  0.1f
extern float kSmooth_13f6a34;    // 0x013f6a34  0.37f

// Angle helpers (cdecl, float in / float out).
extern "C" float WrapAngle(float base, float value);                  // 0x00699730
extern "C" float SP_AngleClamp(float cur, float base, float delta);   // 0x0069b840

typedef unsigned int size_t;

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8
#define PV32 PV16 PV16

struct Wrapper;

struct IVtObj {
    PV4                                 // 0x00..0x0c
    virtual IVtObj* GetObj();           // 0x10
    PV                                  // 0x14
    PV4                                 // 0x18..0x24
    virtual int Check();                // 0x28
    PV16                                // 0x2c..0x68
    PV4                                 // 0x6c..0x78
    virtual void SetFlag(int a, bool b); // 0x7c
    PV16                                // 0x80..0xbc
    PV8                                 // 0xc0..0xdc
    PV2                                 // 0xe0..0xe4
    virtual void DoE8(IVtObj* w);       // 0xe8
};

struct Wrapper {
    char    pad[0x10];
    IVtObj* mpObject;   // +0x10
    bool FUN_005a41e0();          // 0x005a41e0
    void FUN_005a4200(bool flag); // 0x005a4200
};

// ===========================================================================
// @ 0x005a41e0
bool Wrapper::FUN_005a41e0()
{
    if (mpObject)
        return (mpObject->Check() & 1) != 0;
    return false;
}

// ===========================================================================
// @ 0x005a4200
void Wrapper::FUN_005a4200(bool flag)
{
    if (mpObject) {
        mpObject->SetFlag(1, flag);
        if (flag) {
            if (mpObject->GetObj())
                mpObject->GetObj()->DoE8(mpObject);
        }
    }
}

// ===========================================================================
// SP::cEditorCameraController auto-zoom (retail layout; offsets from the disassembly,
// names from the dev PDB / ModAPI EditorCamera.h).
// ===========================================================================
inline float Clamp(float x, float lo, float hi)
{
    __asm {
        movss xmm0, x
        maxss xmm0, lo
        minss xmm0, hi
        movss x, xmm0
    }
    return x;
}

struct cSPVector3 {
    float x, y, z;
    cSPVector3() {}
    cSPVector3(const cSPVector3& v) : x(v.x), y(v.y), z(v.z) {}
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};

// GameInput: only the key bitset (8*32) is touched here (ModAPI Input.h layout).
struct GameInput {
    uint32_t keys[8];                    // +0x00 bitset<8*32>
    uint8_t  pad_020[0x48 - 0x20];
    bool IsKeyDown(int vkey) const { return (keys[vkey >> 5] >> (vkey & 31)) & 1; }
};

// rw::math::fpu::Vector3Template<float,0>: three floats, memberwise copy.
struct cSwarmVec3 {
    float x, y, z;
    cSwarmVec3& operator=(const cSwarmVec3& o) { x = o.x; y = o.y; z = o.z; return *this; }
};

struct cSPMatrix3 {
    float m[9];
    void Assign(const void* src);        // 0x0041cb40
};

namespace EA { namespace Swarm {
// PDB EA::Swarm::cTransform (see src/game/include/EA/Swarm/cTransform.h).
struct cTransform {
    uint16_t    mFlags;                  // +0x00
    uint16_t    mModificationCount;      // +0x02
    cSwarmVec3  mTranslation;            // +0x04
    float       mScale;                  // +0x10
    cSPMatrix3  mRotation;               // +0x14
};
}}  // namespace EA::Swarm

// Runtime BSS state the editor camera inherits from (readable only in the shipped game).
extern cSwarmVec3 gDefaultTranslation;   // 0x015e6a6c
extern cSPMatrix3 gDefaultRotation;      // 0x015e6b9c

struct cSPTransform;

struct cSPBoundingBox {
    cSPVector3 mMin, mMax;
    bool IsEmpty() const { return mMin[0] > mMax[0]; }
    void Transform(const cSPTransform* xf);            // cSPBoundingBox::Transform 0x00409dd0
    void Add(const cSPBoundingBox& o);                 // 0x0043f050 (out of line)
    // the same code as Add, inlined
    void AddInline(const cSPBoundingBox& o)
    {
        if (IsEmpty()) {
            mMin = o.mMin;
            mMax = o.mMax;
        } else {
            if (mMin[0] > o.mMin[0]) mMin[0] = o.mMin[0];
            if (mMax[0] < o.mMax[0]) mMax[0] = o.mMax[0];
            if (mMin[1] > o.mMin[1]) mMin[1] = o.mMin[1];
            if (mMax[1] < o.mMax[1]) mMax[1] = o.mMax[1];
            if (mMin[2] > o.mMin[2]) mMin[2] = o.mMin[2];
            if (mMax[2] < o.mMax[2]) mMax[2] = o.mMax[2];
        }
    }
};

struct cSPMatrix4 { float m[16]; };

struct cSPTransform { uint32_t data[0x40 / 4]; };

struct cSPEditorModelObject {                          // what cSPEditorHandle::GetModel returns
    uint32_t       pad_000[8 / 4];
    cSPTransform   mTransform;                         // +0x08
    uint32_t       pad_048[(0x70 - 0x48) / 4];
    cSPBoundingBox mBBox;                              // +0x70
};

namespace SP {
class cSPEditorHandle { public:
    bool IsFlagSet();                                  // 0x0047f290
    cSPEditorModelObject* GetModel();                  // 0x0047e680
};

class cSPEditorBlock { public:
    uint32_t         pad_000[0x160 / 4];
    cSPEditorHandle* mpBallHandle;                     // +0x160 (name guessed)
    uint32_t         pad_164[(0xdc8 - 0x164) / 4];
    uint32_t         mFlags;                           // +0xdc8

    bool IsFlagSet(uint32_t bit) const { return ((mFlags >> bit) & 1) != 0; }

    cSPBoundingBox   GetBBox(int type, bool a, bool b);  // SP::cSPEditorBlock::GetBBox 0x0044ae00
    cSPEditorHandle* GetPinHandle(int i);                // 0x0043ce00 (name guessed)
    int              GetDeformHandleCount();             // 0x0043c040
    cSPEditorHandle* GetDeformHandle(int i);             // 0x0043c270
};

class cSPEditorModel { public:
    int             GetBlockCount();                   // 0x004accf0
    cSPEditorBlock* GetBlock(int i);                   // 0x004accb0
};

class cFrustumCull { public:
    uint32_t data[0xf0 / 4];
    void Set(const cSPMatrix4& viewProjection);        // 0x006ffe00
    // bit 7 of the result set = outside
    signed char FrustumTestSphere(const cSPVector3* mn, const cSPVector3* mx, int flags);  // 0x00700120
};
}  // namespace SP

namespace App {
struct cViewer {
    uint32_t   pad_000[0xc0 / 4];
    cSPMatrix4 mViewProjection;                        // +0xc0 (name guessed)
    void SetViewAngle(float angle);                    // 0x007c5350
    void SetNearClip(float clip);                      // 0x007c4ba0
    void SetFarClip(float clip);                       // 0x007c4bc0
    void SetBasis(void* basis);                        // 0x007c4d00
};
}  // namespace App

namespace SP {
class cEditorCameraController {
public:
    uint32_t   pad_000[0x28 / 4];
    float      mInitialCameraZoom;                     // +0x28
    uint32_t   pad_02c[(0x30 - 0x2c) / 4];
    float      mInitialHeading;                        // +0x30
    float      mInitialPitch;                          // +0x34
    float      mTargetCameraZoom;                      // +0x38
    float      mTargetOffsetX;                         // +0x3c
    float      mTargetOffsetY;                         // +0x40
    float      mHeading;                               // +0x44
    float      mPitch;                                 // +0x48
    float      mZoom;                                  // +0x4c
    float      mOffsetX;                               // +0x50
    float      mOffsetY;                               // +0x54
    float      mCameraMinZoomDistance;                 // +0x58
    float      mCameraMaxZoomDistance;                 // +0x5c
    uint32_t   pad_060[(0x68 - 0x60) / 4];
    float      mfNearClip;                             // +0x68
    float      mfFarClip;                              // +0x6c
    float      mFieldOfView;                           // +0x70
    cSPVector3 mCameraPosition;                        // +0x74
    cSPVector3 mTargetPosition;                        // +0x80
    float      mEditorScale;                           // +0x8c
    uint32_t   pad_090[(0x9c - 0x90) / 4];
    bool       mbFOVisCurrent;                         // +0x9c
    uint8_t    pad_09d[3];
    GameInput  mInput;                                 // +0xa0
    App::cViewer* mpViewer;                            // +0xe8

    void ClampTargetZoom()
    {
        if (mTargetCameraZoom > mCameraMaxZoomDistance)
            mTargetCameraZoom = mCameraMaxZoomDistance;
        else if (mTargetCameraZoom < mCameraMinZoomDistance)
            mTargetCameraZoom = mCameraMinZoomDistance;
    }

    void UpdateAutoZoom(cSPEditorModel* model, uint32_t deltaMs);
    void Update(int nDeltaTime, App::cViewer* pViewer);
    void FUN_005a3080(EA::Swarm::cTransform* xf);      // 0x005a3080
};

// @ 0x005a33c0
// Zooms the editor camera in while every visible block fits the normal frustum, and out
// (towards the initial zoom) when some block falls outside a 0.9x narrower frustum.
void cEditorCameraController::UpdateAutoZoom(cSPEditorModel* model, uint32_t deltaMs)
{
    if (mpViewer == 0 || mbFOVisCurrent)
        return;

    float rate = Clamp((float)deltaMs * 0.008f, 0.01f, 1.0f);

    float fov = mFieldOfView;
    mpViewer->SetViewAngle(fov);
    cSPMatrix4 wide = mpViewer->mViewProjection;
    mpViewer->SetViewAngle(fov * 0.9f);
    cSPMatrix4 narrow = mpViewer->mViewProjection;
    mpViewer->SetViewAngle(fov);

    cFrustumCull wideCull;
    wideCull.Set(wide);
    cFrustumCull narrowCull;
    narrowCull.Set(narrow);

    int count = model->GetBlockCount();
    for (int i = 0; i < count; ++i) {
        cSPEditorBlock* block = model->GetBlock(i);
        if (block == 0 || block->IsFlagSet(2))
            continue;
        cSPBoundingBox box = block->GetBBox(0, false, false);
        if (block->mpBallHandle && block->mpBallHandle->IsFlagSet()) {
            cSPBoundingBox hb = block->mpBallHandle->GetModel()->mBBox;
            hb.Transform(&block->mpBallHandle->GetModel()->mTransform);
            box.Add(hb);
        }
        for (int j = 0; j < 3; ++j) {
            if (block->GetPinHandle(j) && block->GetPinHandle(j)->IsFlagSet()) {
                cSPBoundingBox hb = block->GetPinHandle(j)->GetModel()->mBBox;
                hb.Transform(&block->GetPinHandle(j)->GetModel()->mTransform);
                box.AddInline(hb);
            }
        }
        int numDeform = block->GetDeformHandleCount();
        for (int j = 0; j < numDeform; ++j) {
            if (block->GetDeformHandle(j) && block->GetDeformHandle(j)->IsFlagSet()) {
                cSPBoundingBox hb = block->GetDeformHandle(j)->GetModel()->mBBox;
                hb.Transform(&block->GetDeformHandle(j)->GetModel()->mTransform);
                box.AddInline(hb);
            }
        }
        if ((wideCull.FrustumTestSphere(&box.mMin, &box.mMax, 0) & 0x80) == 0) {
            mTargetCameraZoom = mEditorScale * rate * 0.2f + mTargetCameraZoom;
            ClampTargetZoom();
            return;
        }
    }

    bool allOutside = true;
    count = model->GetBlockCount();
    for (int i = 0; i < count; ++i) {
        cSPEditorBlock* block = model->GetBlock(i);
        if (block == 0 || block->IsFlagSet(2))
            continue;
        cSPBoundingBox box = block->GetBBox(0, false, false);
        if (block->mpBallHandle && block->mpBallHandle->IsFlagSet()) {
            cSPBoundingBox hb = block->mpBallHandle->GetModel()->mBBox;
            hb.Transform(&block->mpBallHandle->GetModel()->mTransform);
            box.AddInline(hb);
        }
        for (int j = 0; j < 3; ++j) {
            if (block->GetPinHandle(j) && block->GetPinHandle(j)->IsFlagSet()) {
                cSPBoundingBox hb = block->GetPinHandle(j)->GetModel()->mBBox;
                hb.Transform(&block->GetPinHandle(j)->GetModel()->mTransform);
                box.AddInline(hb);
            }
        }
        int numDeform = block->GetDeformHandleCount();
        for (int j = 0; j < numDeform; ++j) {
            if (block->GetDeformHandle(j) && block->GetDeformHandle(j)->IsFlagSet()) {
                cSPBoundingBox hb = block->GetDeformHandle(j)->GetModel()->mBBox;
                hb.Transform(&block->GetDeformHandle(j)->GetModel()->mTransform);
                box.AddInline(hb);
            }
        }
        if ((narrowCull.FrustumTestSphere(&box.mMin, &box.mMax, 0) & 0x80) == 0)
            allOutside = false;
    }
    if (!allOutside)
        return;

    mTargetCameraZoom = mTargetCameraZoom - mEditorScale * rate * 0.2f;
    if (mTargetCameraZoom < mInitialCameraZoom)
        mTargetCameraZoom = mInitialCameraZoom;
    ClampTargetZoom();
}

// @ 0x005a3e10
// Per-frame editor camera update: turns/zooms from the numpad/OEM keys, damps the
// heading/pitch/offset/position towards their targets, then hands the resulting
// transform to the viewer.
void cEditorCameraController::Update(int nDeltaTime, App::cViewer* pViewer)
{
    float fDelta = (float)(uint32_t)nDeltaTime;
    mpViewer = pViewer;

    float rate = Clamp(fDelta * 0.008f, 0.01f, 1.0f);

    if (mfNearClip > 0.0f)
        pViewer->SetNearClip(mfNearClip);
    if (mfFarClip > 0.0f)
        pViewer->SetFarClip(mfFarClip);

    float zoomDelta = 0.0f;
    float headingDelta = 0.0f;
    if (mInput.IsKeyDown(188))                 // VK_OEM_COMMA
        headingDelta = rate * kNegTurn_13f6a3c;
    if (mInput.IsKeyDown(190))                 // VK_OEM_PERIOD
        headingDelta = rate * kPosTurn_13f69ac;
    if (mInput.IsKeyDown(187) || mInput.IsKeyDown(107)) {   // VK_OEM_PLUS / VK_ADD
        zoomDelta = rate * kNegZoom_13f6a38;
        mbFOVisCurrent = 1;
    }
    if (mInput.IsKeyDown(189) || mInput.IsKeyDown(109)) {   // VK_OEM_MINUS / VK_SUBTRACT
        zoomDelta = rate * kPosZoom_13ec478;
        mbFOVisCurrent = 1;
    }

    mInitialHeading += headingDelta;
    mTargetCameraZoom = (zoomDelta + kOne_1485720) * mTargetCameraZoom;
    ClampTargetZoom();

    mZoom = (mTargetCameraZoom - mZoom) * rate + mZoom;

    float pitchOffset = (kPointOne_1488874 - (Abs(mPitch) / kHalfPi_150f2c4) * kHalf_1471064) * mEditorScale;

    mPitch = SP_AngleClamp(mPitch, mInitialPitch, WrapAngle(mInitialPitch, mPitch) * rate);
    mHeading = SP_AngleClamp(mHeading, mInitialHeading, WrapAngle(mInitialHeading, mHeading) * rate);

    mOffsetX = (mTargetOffsetX - mOffsetX) * rate + mOffsetX;
    mOffsetY = ((mTargetOffsetY + pitchOffset) - mOffsetY) * rate + mOffsetY;

    float dx = (mTargetPosition.x - mCameraPosition.x) * rate;
    float dy = (mTargetPosition.y - mCameraPosition.y) * rate;
    float dz = (mTargetPosition.z - mCameraPosition.z) * rate;
    mCameraPosition.x += dx * kSmooth_13f6a34;
    mCameraPosition.y += dy * kSmooth_13f6a34;
    mCameraPosition.z += dz * kSmooth_13f6a34;

    EA::Swarm::cTransform xf;
    xf.mFlags = 0;
    xf.mModificationCount = 0;
    xf.mTranslation = gDefaultTranslation;
    xf.mScale = kOne_1485720;
    xf.mRotation.Assign(&gDefaultRotation);

    FUN_005a3080(&xf);
    pViewer->SetBasis(&xf);
}
}  // namespace SP
