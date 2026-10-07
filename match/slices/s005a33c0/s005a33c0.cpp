// Slice s005a33c0 -- SP::cEditorCameraController::UpdateAutoZoom (0x005a33c0), a wrapper and a large UI function.
// Module flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast.
#include "types.h"

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
struct cSPEditorHandle {
    bool IsFlagSet();                                  // 0x0047f290
    cSPEditorModelObject* GetModel();                  // 0x0047e680
};

struct cSPEditorBlock {
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

struct cSPEditorModel {
    int             GetBlockCount();                   // 0x004accf0
    cSPEditorBlock* GetBlock(int i);                   // 0x004accb0
};

struct cFrustumCull {
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
    void SetViewAngle(float angle);                    // cViewer_SetViewAngle 0x007c5350
};
}  // namespace App

namespace SP {
class cEditorCameraController {
public:
    uint32_t pad_000[0x28 / 4];
    float    mInitialCameraZoom;                       // +0x28
    uint32_t pad_02c[(0x38 - 0x2c) / 4];
    float    mTargetCameraZoom;                        // +0x38
    uint32_t pad_03c[(0x58 - 0x3c) / 4];
    float    mCameraMinZoomDistance;                   // +0x58
    float    mCameraMaxZoomDistance;                   // +0x5c
    uint32_t pad_060[(0x70 - 0x60) / 4];
    float    mFieldOfView;                             // +0x70
    uint32_t pad_074[(0x8c - 0x74) / 4];
    float    mEditorScale;                             // +0x8c
    uint32_t pad_090[(0x9c - 0x90) / 4];
    bool     mbFOVisCurrent;                           // +0x9c
    uint8_t  pad_09d[3];
    uint32_t pad_0a0[(0xe8 - 0xa0) / 4];
    App::cViewer* mpViewer;                            // +0xe8

    void ClampTargetZoom()
    {
        if (mTargetCameraZoom > mCameraMaxZoomDistance)
            mTargetCameraZoom = mCameraMaxZoomDistance;
        else if (mTargetCameraZoom < mCameraMinZoomDistance)
            mTargetCameraZoom = mCameraMinZoomDistance;
    }

    void UpdateAutoZoom(cSPEditorModel* model, uint32_t deltaMs);
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
}  // namespace SP

// @ 0x005a3e10
void FUN_005a3e10(void* self)
{
    (void)self;
}
