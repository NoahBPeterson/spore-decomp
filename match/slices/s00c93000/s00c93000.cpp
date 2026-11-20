// Slice s00c93000 -- cTribeToolView: lazily create the tribe's hut effect (348 bytes).
//
// If the view does not hold a hut effect yet, ask the view which hut model to use, create the cost-effect
// object for it through the effects manager and keep it in the view. The freshly created effect is then
// placed: a Transform is initialised to identity (zero position, unit scale, identity rotation), the hut
// model's spatial object supplies the rotation (as a quaternion converted to a matrix) and the position,
// and the transform is handed to the effect. The effect is then attached to this view, given palette
// colour slot 5 (three channels) from the view's colour index, and finished with mode 0.
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include <stddef.h>

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4

// ---------------------------------------------------------------------------
// math
// ---------------------------------------------------------------------------
struct Vector3 {
    float x, y, z;
};

struct Quaternion {
    float x, y, z, w;
};

struct Matrix3 {
    float m[9];

    Matrix3& Assign(const Matrix3& src);        // 0x0041cb40 (out of line)
};

extern const Vector3 kZeroVector;      // 0x016953e4
extern const Matrix3 kIdentityMatrix;  // 0x016953c0
extern const float kOne;               // 0x01485720 (g_one)

struct Transform {
    uint16_t mFlags;      // bit1 rotated, bit2 translated
    uint16_t mVersion;
    Vector3 mPos;
    float mScale;
    Matrix3 mRot;

    void SetRotation(const Matrix3& m) { mRot = m; mFlags |= 2; mVersion++; }
    void SetOffset(const Vector3& v) { mPos = v; mFlags |= 4; mVersion++; }
};

// ---------------------------------------------------------------------------
// types
// ---------------------------------------------------------------------------
struct cEffect;
struct cEffectsManager;

// ---------------------------------------------------------------------------
// imports
// ---------------------------------------------------------------------------
Matrix3 Matrix3FromQuaternion(const Quaternion& q);  // 0x0059c190

const Vector3& GetColor(uint32_t nIndex);            // 0x00b6f0c0

cEffectsManager* EffectsManagerPtr();                // 0x0067ddd0

struct cEffect {
    PV
    virtual void Release();                                       // +0x04
    virtual void Finish(int nMode);                               // +0x08
    PV2 PV
    virtual void SetTransform(const Transform& xform);            // +0x18
    PV8 PV2
    virtual void SetColor(int nSlot, const Vector3& color, int nChannels);  // +0x44
    PV
    virtual void Attach(int nMode, void* pOwner);                 // +0x4c
};

struct cEffectsManager {
    PV8 PV2 PV
    virtual bool CreateEffect(void* pModel, int nFlags, cEffect** ppOut);   // +0x2c
};

struct cSpatialObject {
    PV8 PV2 PV
    virtual Vector3* GetPosition();        // +0x2c
    virtual Quaternion* GetRotation();     // +0x30
};

struct cModel {
    uint8_t pad00[0x34];
    cSpatialObject mSpatial;               // +0x34 (secondary vtable base)
};

struct cTribeToolView {
    uint8_t pad000[0x234];
    uint32_t mColorIndex;                  // +0x234
    uint8_t pad238[0x2d0 - 0x238];
    cEffect* mpHutEffect;                  // +0x2d0
    uint8_t pad2d4[0x368 - 0x2d4];
    cModel* mpModel;                       // +0x368

    void* ChooseNewHutModel();             // 0x00c91b60
    void CreateHutEffect();
};

// ---------------------------------------------------------------------------
// cTribeToolView::CreateHutEffect
// ---------------------------------------------------------------------------
// @ 0x00c93000
void cTribeToolView::CreateHutEffect()
{
    if (mpHutEffect)
        return;

    void* pModel = ChooseNewHutModel();
    cEffectsManager* pManager = EffectsManagerPtr();

    if (mpHutEffect) {
        cEffect* pOld = mpHutEffect;
        mpHutEffect = 0;
        pOld->Release();
    }

    if (!pManager->CreateEffect(pModel, 0, &mpHutEffect))
        return;

    Transform xform;
    xform.mFlags = 0;
    xform.mVersion = 0;
    xform.mPos.x = kZeroVector.x;
    xform.mPos.y = kZeroVector.y;
    xform.mPos.z = kZeroVector.z;
    xform.mScale = kOne;
    xform.mRot.Assign(kIdentityMatrix);

    Matrix3 mRot = Matrix3FromQuaternion(*mpModel->mSpatial.GetRotation());
    xform.SetRotation(mRot);
    xform.SetOffset(*mpModel->mSpatial.GetPosition());

    mpHutEffect->SetTransform(xform);
    mpHutEffect->Attach(1, this);
    cEffect* pEffect = mpHutEffect;
    const Vector3& color = GetColor(mColorIndex);
    pEffect->SetColor(5, color, 3);
    mpHutEffect->Finish(0);
}
