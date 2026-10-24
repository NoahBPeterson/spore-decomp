// Slice s00d213b0 -- SP::cCreatureCamera message handling, pitch/mode queries, anchor and pitch
// helpers, and the free-camera update step.
// Flags: /O2 /Ob2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
//
// Retail layout is the s00d28900 cCreatureCamera layout (3 vptrs: ICamBase +0x00, IGB1 +0x04,
// RefCountV +0x08, reference count +0x0c, camera fields from +0x10).  HandleMessage is delivered to
// the IGB1 subobject, so its incoming `this` is camera+4; every other entry point receives the
// camera base.
#include "types.h"
#include <math.h>

// ------------------------------------------------------------------------------------------ types
struct Vec2 { float x, y; };
struct Vec3 { float x, y, z; };
struct Quat { float x, y, z, w; };
struct Vec4 { float x, y, z, w; };

struct Matrix44 {
    Vec4 xAxis, yAxis, zAxis, wAxis;
    void FUN_007c3da0(float* dst);                          // 0x007c3da0 (3x3 copy)
};

// -------------------------------------------------------------------------------------- constants
extern const float kOne;          // 0x01485720  1.0
extern const float kNegOne;       // 0x013eb1bc  -1.0
extern const float kHalf;         // 0x01471064  0.5
extern const float kTenth;        // 0x0148874   0.1
extern const float kEpsilon;      // 0x013ec4b8  1e-8
extern const Vec2  kInputConst;   // 0x0169dea8
extern const Vec3  kZeroVec;      // 0x0169deb0  (0,0,0)
extern const char  gModeCreatureB;  // 0x01654c01  creature-mode sentinel
extern const char  gModeCreatureA;  // 0x01654c10
extern unsigned char gUsePitchArg;  // 0x0169de80  GetPitch mode flag
extern unsigned char gUsePitchRefine;  // 0x0169de81

// --------------------------------------------------------------------------------------- callees
struct cGameNounManager;
struct cPlanetModel;
struct cApp;
cGameNounManager* NounManager();                       // 0x00b3d300
cPlanetModel* PlanetModel();                           // 0x00b3d350
cApp*  App();                                          // 0x0067dd10
void*  GetCurrentGameMode();                           // 0x00b5b800
void*  GameInputManager();                             // 0x00b3d250
void* FUN_0067cab0();                                 // 0x0067cab0
float* normalized_safe(float* out, const float* v);    // 0x00449c20
float* FUN_0046d660(float* out, const float* m);       // 0x0046d660
Vec3*  FUN_0059aed0(Vec3* out, const Vec3* v, const Quat* q);  // 0x0059aed0
float  Acos(float x);                                  // 0x011e08c8

// Pitch helpers: both receive the camera in ecx (thiscall) although they are not camera members.
struct cCameraMathView {
    float RefinePitch(float v);                        // 0x00d20620  ret 4
    float AdjustPitchAndDistance(float a, float b);    // 0x00d20700  ret 8
};

// A message object: vf10() -> selector, selector->vf1c(1) -> pointer whose first word is the payload.
struct cMsgObj {
    virtual void  pv0();
    virtual void  pv1();
    virtual void  pv2();
    virtual void  pv3();
    virtual void* vf10();                              // +0x10
    virtual void  pv5();
    virtual void  pv6();
    virtual void** vf1c(int which);                     // +0x1c
};

struct cApp {
    virtual void pv00(); virtual void pv01(); virtual void pv02(); virtual void pv03();
    virtual void pv04(); virtual void pv05(); virtual void pv06(); virtual void pv07();
    virtual void pv08(); virtual void pv09(); virtual void pv0a(); virtual void pv0b();
    virtual void pv0c(); virtual void pv0d(); virtual void pv0e(); virtual void pv0f();
    virtual void pv10(); virtual void pv11(); virtual void pv12(); virtual void pv13();
    virtual void pv14(); virtual void pv15();
    virtual void* vf58();                              // +0x58 -> cViewer
};

struct cGameInputManager {
    virtual void pv0(); virtual void pv1(); virtual void pv2();
    virtual void pv3(); virtual void pv4(); virtual void pv5();
    virtual bool vf18(int id);                         // +0x18
};

struct cUiObject {
    void Set40(bool on);                               // 0x008013d0
    void Set(bool on);                                 // 0x00801980
};

struct cCreatureModeInputStrategy {
    char pad54[0x54];
    unsigned char mb54;                                // +0x54
    char pad55[3];
    bool DidDoubleClick(int id);                       // 0x00d30ee0
};

struct cCreatureModeStrategy {
    char pad64[0x64];
    cCreatureModeInputStrategy* mpInputStrategy;       // +0x64
    static cCreatureModeStrategy* Instance();          // 0x00d38840
};

struct cLocoAnimState {
    char pad14[0x14];
    float mf14;                                        // +0x14
};

struct cLoco {
    virtual void pv00(); virtual void pv01(); virtual void pv02(); virtual void pv03();
    virtual void pv04(); virtual void pv05(); virtual void pv06(); virtual void pv07();
    virtual void pv08(); virtual void pv09(); virtual void pv0a();
    virtual Vec3* vf2c();                              // +0x2c  position
    virtual void pv0c(); virtual void pv0d(); virtual void pv0e(); virtual void pv0f();
    virtual void pv10(); virtual void pv11(); virtual void pv12(); virtual void pv13();
    virtual void pv14(); virtual void pv15(); virtual void pv16();
    virtual Vec3* vf5c(Vec3* out);                     // +0x5c  anchor position
    virtual void pv18(); virtual void pv19();
    virtual cLocoAnimState* vf68();                    // +0x68
};

struct cAvatar {
    char padC0[0xc0];
    cLoco mLoco;                                       // +0xc0
};

struct cPlanetModel {
    Vec3* DirectionToSurfacePosition(Vec3* out, const Vec3* in);  // 0x00b815a0
    Vec3* FUN_00b81630(Vec3* out, const Vec3* in);                // 0x00b81630
};

struct cGameNounManager {
    cAvatar* GetAvatar();                              // 0x00b1fdb0
};

struct cViewer {
    Matrix44 mCameraToWorldTransform;   // +0x00
    void GetCameraLocationInfo(Vec3* pos, Vec3* dir, Vec3* up, Vec3* right);  // 0x007c3d30
};

struct cLocalInputState {
    char data[0x48];
    void OnMouseDown(unsigned int id, float x, float y, unsigned int flags);  // 0x00697ab0
};

// ---------------------------------------------------------------------------- cCreatureCamera
struct ICamBase { void* mVptr; };
struct IGB1 { void* mVptr; };
struct RefCountV { void* mVptr; int mRefCount; };
struct RbTreeAnchor {
    RbTreeAnchor* mpRight;
    RbTreeAnchor* mpLeft;
    RbTreeAnchor* mpParent;
    unsigned int mColor;
    unsigned int mnSize;
};

// The message handler is delivered to the IGB1 subobject, i.e. camera+4, so its own member layout
// sits four bytes below the camera's.  Member names keep the camera's offsets and the comments give
// the corresponding camera offset.
class cCreatureCameraIGB1 : public IGB1 {
public:
    char mPad004[0x128 - 0x004];
    float mF12C;                                             // camera +0x12c
    float mF130;                                             // camera +0x130
    char mPad130[0x1e4 - 0x130];
    unsigned int mI1E8;                                      // camera +0x1e8
    unsigned int mI1EC;                                      // camera +0x1ec
    unsigned int mI1F0;                                      // camera +0x1f0
    bool mb1F4;                                              // camera +0x1f4
    char mPad1F1[0x295 - 0x1f1];
    bool mbCameraReverse;                                    // camera +0x299
    char mPad296[0x310 - 0x296];
    bool mb314;                                              // camera +0x314
    bool mb315;                                              // camera +0x315
    bool HandleMessage(unsigned int id, void* msg);          // 0x00d213b0
};

class cCreatureCamera : public ICamBase, public IGB1, public RefCountV {
public:
    bool OnMouseDown(unsigned int id, float x, float y, unsigned int flags);  // 0x00d217e0
    float GetPitch(float a, float b);                        // 0x00d21810
    Vec3* GetAudioAnchorPosition(Vec3* out);                 // 0x00d21c50
    void UpdateCamera_Free();                                // 0x00d21d90
    void SetCameraUI(bool on);                               // 0x00d20430
    void FUN_00d21b10(float x, float y, float z);            // 0x00d21b10
    void FUN_00d21bc0(float x, float y, float z);            // 0x00d21bc0

    bool mbEnableInput;                       // +0x10
    bool mbSkipInit;                          // +0x11
    Vec2 mInputConst;                         // +0x14
    float mDt, mOscillationTime, mBreathOffset;            // +0x1c
    Vec3 mShakeOffset;                                     // +0x28
    float mRoll;                                           // +0x34
    Vec3 mReferenceHeading;                                // +0x38
    float mWantInterpolationTimer;                         // +0x44
    Vec3 mV48;                                             // +0x48
    Vec3 mV54;                                             // +0x54
    Quat mQ60;                                             // +0x60
    Vec3 mV70, mV7c, mV88, mV94, mVa0, mVac, mVb8, mVc4;   // +0x70 ..
    Vec3 mBoundsMin;                                       // +0xd0
    Vec3 mBoundsMax;                                       // +0xdc
    bool mbE8, mbE9;                                       // +0xe8
    float mFieldEC, mFieldF0, mFieldF4, mFieldF8, mFieldFC; // +0xec
    float mField100;                                       // +0x100
    bool mb104, mb105;                                     // +0x104
    Vec3 mV108, mV114, mV120;                              // +0x108
    float mF12C, mF130, mF134, mF138;                       // +0x12c
    Vec3 mV13C, mV148;                                     // +0x13c
    Quat mQ154;                                            // +0x154
    bool mb164;                                            // +0x164
    Vec3 mV168;                                            // +0x168
    float mF174, mF178, mF17C;                             // +0x174
    float mF180, mF184, mF188, mF18C, mF190, mF194, mF198; // +0x180
    bool mb19C, mb19D;                                     // +0x19c
    float mF1A0, mF1A4, mF1A8;                             // +0x1a0
    Vec3 mV1AC;                                            // +0x1ac
    Quat mQ1B8;                                            // +0x1b8
    Vec3 mAudioAnchor;                                     // +0x1c8
    Quat mQ1D4;                                            // +0x1d4
    float mF1E4;                                           // +0x1e4
    unsigned int mI1E8, mI1EC, mI1F0;                      // +0x1e8
    bool mb1F4;                                            // +0x1f4
    float mMouseSensitivityX, mMouseSensitivityY;          // +0x1f8
    float mMouseSensitivityZ;                              // +0x200
    float mMaxAnchorDistance;                              // +0x204
    Vec2 mPitchLimits;                                     // +0x208
    float mMinCameraPhi;                                   // +0x210
    float mMaxCameraPhi;                                   // +0x214
    float mMinCameraDistance, mMaxCameraDistance;          // +0x218
    float mInitialDistance, mInitialRotation;              // +0x220
    float mNearClip, mFarClip, mInterpolateAnchorTime;     // +0x228
    float mInterpolateOrientationTime;                     // +0x234
    float mInterpolateThetaTime;                           // +0x238
    bool mbAutoPitchActive;                                // +0x23c
    float mInterpolatePitchTime;                           // +0x240
    float mInterpolateDistanceTime;                        // +0x244
    float mAutoPitch248, mAutoPitch24C, mAutoPitch250, mAutoPitch254;  // +0x248
    float mInterpolateAnchorMultiplier;                    // +0x258
    float mField25C;                                       // +0x25c
    char mCameraToWorld[0x38];                             // +0x260
    bool mTransformNeedsUpdating;                          // +0x298
    bool mCameraReverse;                                   // +0x299
    unsigned int mMsgReg[5];                               // +0x29c
    bool mbCanToggleFirstPersonView;                       // +0x2b0
    bool mbLockOutPlayerDeltas, mbAllowRealignment, mbRealignAvatar, mbB4;  // +0x2b1
    float mLftMouseDownDuration;                           // +0x2b8
    cLocalInputState mLocalInputState;                     // +0x2bc
    bool mbActive;                                         // +0x304
    void* mConfig;                                         // +0x308
    char pad30c[0x314 - 0x30c];
    bool mb314, mb315;                                     // +0x314
    unsigned int pad318;
    RbTreeAnchor mTree;                                    // +0x31c
};

// ===========================================================================================
// @ 0x00d213b0  cCreatureCameraIGB1::HandleMessage
// Delivered to the IGB1 subobject (camera+4); the payload is *(selector->vf1c(1)).
// ===========================================================================================
bool cCreatureCameraIGB1::HandleMessage(unsigned int id, void* msg)
{
    unsigned int p = 0;

    switch (id) {
    case 0x25db76a:
    case 0x25db76f:
    case 0x35f7b83:
    case 0x51cbb29:
    case 0x51cbb2d:
    case 0x507cc87f:
    case 0x6493c83:
    case 0x705673e1:
    case 0x705673e9: {
        cMsgObj* m = (cMsgObj*)msg;
        cMsgObj* sel = (cMsgObj*)m->vf10();
        unsigned int* payload = (unsigned int*)sel->vf1c(1);
        p = payload ? *payload : 0;
        break;
    }
    }

    switch (id) {
    case 0x25db76a:
        mI1E8 = (p > 0) ? 4 : 0;
        break;
    case 0x25db76f:
        mI1E8 = (p > 0) ? 5 : 0;
        break;
    case 0x705673e1:
        mI1E8 = (p > 0) ? 1 : 0;
        break;
    case 0x705673e9:
        mI1E8 = (p > 0) ? 2 : 0;
        break;
    case 0x51cbb29:
        mI1E8 = (p > 0) ? 6 : 0;
        break;
    case 0x51cbb2d:
        mI1E8 = (p > 0) ? 7 : 0;
        break;
    case 0x50567351:
        if (mI1EC == 2)
            break;
        mI1E8 = 3;
        break;
    case 0x1c38e3b:
        if (mI1EC == 2)
            break;
        mI1F0 = 0;
        break;
    case 0x19edcf3:
        if (mI1EC == 2)
            break;
        mI1F0 = 0;
        mb315 = true;
        break;
    case 0x27c67ea:
        if (mI1EC == 2)
            break;
        if (!mb315)
            mI1F0 = 1;
        if (mI1F0 == 1)
            break;
        mb1F4 = false;
        break;
    case 0x27c7119:
        if (mI1EC == 2)
            break;
        if (!mb315)
            mI1F0 = 1;
        mb1F4 = true;
        break;
    case 0x35f7b83: {
        cCreatureModeStrategy* strategy = cCreatureModeStrategy::Instance();
        cCreatureModeInputStrategy*& input = strategy->mpInputStrategy;
        bool doubleClicked = false;
        if (input && input->mb54 && input->DidDoubleClick(0x18))
            doubleClicked = true;
        if (p && !doubleClicked)
            break;
        mF12C = 0.0f;
        mF130 = 0.0f;
        break;
    }
    case 0x507cc87f:
        if (mbCameraReverse != (p > 0))
            mbCameraReverse = (p > 0);
        break;
    case 0x6493c83:
        ((cCreatureCamera*)((char*)this - 4))->SetCameraUI(p > 0);
        break;
    case 0xd02dcc68: {
        if (mI1EC == 2)
            break;
        cGameInputManager* input = (cGameInputManager*)GameInputManager();
        if (!input) {
            mb315 = false;
            break;
        }
        bool active = input->vf18(1) || input->vf18(2) || input->vf18(3) || input->vf18(4);
        mb315 = false;
        mI1F0 = active ? 1 : 0;
        break;
    }
    case 0x62663dd:
    case 0x4d9686f:
    case 0xd33b6aa2:
    case 0xf3327645: {
        void* mode = GetCurrentGameMode();
        if (mode == &gModeCreatureB || mode == &gModeCreatureA) {
            ((cUiObject*)FUN_0067cab0())->Set40(true);
            ((cUiObject*)FUN_0067cab0())->Set(false);
            mb314 = false;
            mb315 = false;
        }
        break;
    }
    }
    return false;
}
// ===========================================================================================
// @ 0x00d217e0  SP::cCreatureCamera::OnMouseDown
// ===========================================================================================
bool cCreatureCamera::OnMouseDown(unsigned int id, float x, float y, unsigned int flags)
{
    mLocalInputState.OnMouseDown(id, x, y, flags);
    return true;
}

// ===========================================================================================
// @ 0x00d21810  SP::cCreatureCamera::GetPitch
// ===========================================================================================
float cCreatureCamera::GetPitch(float a, float b)
{
    if (gUsePitchArg) {
        b = a;
    } else if (gUsePitchRefine) {
        b = ((cCameraMathView*)this)->RefinePitch(b);
    } else {
        b = ((cCameraMathView*)this)->AdjustPitchAndDistance(a, b);
    }

    cAvatar* avatar = (cAvatar*)NounManager()->GetAvatar();
    if (avatar) {
        if (PlanetModel()) {
            Vec3 pos = *avatar->mLoco.vf2c();
            float len = sqrtf(pos.x * pos.x + pos.y * pos.y + pos.z * pos.z);
            float inv = 1.0f / sqrtf(mV48.x * mV48.x + mV48.y * mV48.y + mV48.z * mV48.z + 1e-8f);
            Vec3 scaled;
            scaled.x = (mV48.x * inv) * len;
            scaled.y = (mV48.y * inv) * len;
            scaled.z = (mV48.z * inv) * len;

            Vec3 target;
            ((cPlanetModel*)PlanetModel())->FUN_00b81630(&target, &mV48);

            Vec3 d;
            d.x = scaled.x - pos.x;
            d.y = scaled.y - pos.y;
            d.z = scaled.z - pos.z;
            float invD = 1.0f / sqrtf(d.x * d.x + d.y * d.y + d.z * d.z + 1e-8f);
            Vec3 u;
            u.x = d.x * invD;
            u.y = d.y * invD;
            u.z = d.z * invD;

            Vec3 w;
            w.x = target.x - pos.x;
            w.y = target.y - pos.y;
            w.z = target.z - pos.z;
            float invW = 1.0f / sqrtf(w.x * w.x + w.y * w.y + w.z * w.z + 1e-8f);
            w.x = w.x * invW;
            w.y = w.y * invW;
            w.z = w.z * invW;

            float dot = (w.x * u.x + w.z * u.z) + w.y * u.y;
            if (dot < -1.0f)
                dot = -1.0f;
            if (dot > 1.0f)
                dot = 1.0f;

            float ang = Acos(dot);
            mF1E4 = ang;
            float sign = (len <= sqrtf((target.x * target.x + target.z * target.z) + target.y * target.y))
                             ? 1.0f : -1.0f;
            mF1E4 = ang * sign;
            b = ang * sign + b;
        }
    }
    return b;
}

// ===========================================================================================
// @ 0x00d21b10  FUN_00d21b10 (camera pitch/orientation store)
// ===========================================================================================
void cCreatureCamera::FUN_00d21b10(float x, float y, float z)
{
    mF180 = x;
    mF18C = x;
    // retail clamps with maxss/minss: the value is the second operand on NaN, so the
    // comparison forms below (not "if (v < lo)") are the ones with matching semantics.
    float yy = y > mPitchLimits.x ? y : mPitchLimits.x;
    yy = yy < mPitchLimits.y ? yy : mPitchLimits.y;
    mF184 = yy;
    mF190 = yy;
    float zz = z > 0.1f ? z : 0.1f;
    mF188 = zz;
    mF194 = zz;
    mTransformNeedsUpdating = true;
}

// ===========================================================================================
// @ 0x00d21bc0  FUN_00d21bc0 (camera translation store)
// ===========================================================================================
void cCreatureCamera::FUN_00d21bc0(float x, float y, float z)
{
    mF180 = x;
    float yy = y > mPitchLimits.x ? y : mPitchLimits.x;
    yy = yy < mPitchLimits.y ? yy : mPitchLimits.y;
    mF184 = yy;
    mF188 = z > 0.1f ? z : 0.1f;
}

// ===========================================================================================
// @ 0x00d21c50  SP::cCreatureCamera::GetAudioAnchorPosition
// ===========================================================================================
Vec3* cCreatureCamera::GetAudioAnchorPosition(Vec3* out)
{
    cPlanetModel* planet = (cPlanetModel*)PlanetModel();
    if (planet) {
        planet->DirectionToSurfacePosition(out, &mAudioAnchor);
        return out;
    }
    out->x = mAudioAnchor.x;
    out->y = mAudioAnchor.y;
    out->z = mAudioAnchor.z;
    return out;
}

// ===========================================================================================
// |v| written as a positive test first: the original builds the sign flip with a branch,
// so a plain "if (v < 0) v = -v" is not the right source shape here.
static inline float AbsValue(float v)
{
    if (v >= 0.0f)
        return v;
    return -v;
}

// @ 0x00d21ca0  FUN_00d21ca0 (axis-aligned point proximity test)
// ===========================================================================================
int FUN_00d21ca0(const Vec3* a, const Vec3* b, float tolerance)
{
    if (AbsValue(a->x - b->x) <= tolerance) {
        if (AbsValue(a->y - b->y) <= tolerance) {
            if (AbsValue(a->z - b->z) <= tolerance)
                return 1;
        }
    }
    return 0;
}

// ===========================================================================================
// @ 0x00d21d10  FUN_00d21d10 (axis/angle rotation applied to a vector)
// ===========================================================================================
Vec3* FUN_00d21d10(Vec3* out, const Vec3* v, const Vec3* axis, float angle)
{
    float half = angle * 0.5f;
    float s = sinf(half);
    float c = cosf(half);
    Quat q;
    q.x = axis->x;
    q.y = axis->y;
    q.z = axis->z;
    q.x = q.x * s;
    q.y = q.y * s;
    q.z = q.z * s;
    q.w = c;
    Vec3 tmp;
    Vec3* r = FUN_0059aed0(&tmp, v, &q);
    out->x = r->x;
    out->y = r->y;
    out->z = r->z;
    return out;
}

// ===========================================================================================
// @ 0x00d21d90  SP::cCreatureCamera::UpdateCamera_Free
// ===========================================================================================
void cCreatureCamera::UpdateCamera_Free()
{
    cAvatar* avatar = (cAvatar*)NounManager()->GetAvatar();
    cViewer* viewer = (cViewer*)App()->vf58();
    if (avatar && viewer) {
        cLoco* loco = &avatar->mLoco;

        Vec3 anchor;
        Vec3* anchorPos = loco->vf5c(&anchor);
        mVb8.x = anchorPos->x;
        mVb8.y = anchorPos->y;
        mVb8.z = anchorPos->z;

        Vec3* velocity = loco->vf2c();
        float inv = 1.0f / sqrtf(velocity->x * velocity->x + velocity->y * velocity->y
                                 + velocity->z * velocity->z + 1e-8f);
        mVc4.x = velocity->x * inv;
        mVc4.y = velocity->y * inv;
        mVc4.z = velocity->z * inv;

        float scale = loco->vf68()->mf14;
        Vec3 offset;
        offset.x = mVc4.x * scale;
        offset.y = mVc4.y * scale;
        offset.z = mVc4.z * scale;
        Vec3* position = loco->vf2c();
        mVa0.x = position->x + offset.x;
        mVa0.y = position->y + offset.y;
        mVa0.z = position->z + offset.z;

        mV114 = mVa0;
        mV1AC = mVa0;
        mAudioAnchor = mVa0;

        if (!mbSkipInit) {
            Vec3 camPos, camDir, camUp, camRight;
            viewer->GetCameraLocationInfo(&camPos, &camDir, &camUp, &camRight);

            float mat9[9];
            viewer->mCameraToWorldTransform.FUN_007c3da0(mat9);

            mV48 = camPos;
            mV13C = camPos;

            Quat q;
            FUN_0046d660(&q.x, mat9);
            mQ60 = q;
            mQ154 = q;
            mQ1B8 = q;
            mQ1D4 = q;

            float dx = mV114.x - mV48.x;
            float dy = mV114.y - mV48.y;
            float dz = mV114.z - mV48.z;
            float dist = sqrtf(dx * dx + dy * dy + dz * dz);
            if (dist < mMinCameraPhi)
                dist = mMinCameraPhi;
            if (dist > mMaxCameraPhi)
                dist = mMaxCameraPhi;

            Vec3 normal;
            normalized_safe(&normal.x, &mV48.x);
            float d1 = (normal.x * camDir.x + normal.z * camDir.z) + normal.y * camDir.y;
            Vec3 projected;
            projected.x = camDir.x - normal.x * d1;
            projected.y = camDir.y - normal.y * d1;
            projected.z = camDir.z - normal.z * d1;

            Vec3 up;
            normalized_safe(&up.x, &projected.x);
            float d2 = (up.x * camDir.x + up.y * camDir.y) + up.z * camDir.z;
            if (d2 < -1.0f)
                d2 = -1.0f;
            if (d2 > 1.0f)
                d2 = 1.0f;

            mReferenceHeading = up;
            mF174 = 0.0f;
            mFieldF8 = 0.0f;
            mF17C = dist;
            mField100 = dist;
            mF188 = dist;
            mF194 = dist;

            float ang = Acos(d2);
            float lifted = ((cCameraMathView*)this)->AdjustPitchAndDistance(ang, dist);
            mF178 = lifted;
            mFieldFC = lifted;
        }

        mTransformNeedsUpdating = true;
        mInputConst = kInputConst;
        mV54 = kZeroVec;
        mV148 = kZeroVec;
        mOscillationTime = 0.0f;
        mBreathOffset = 0.0f;
        mShakeOffset = kZeroVec;
        mRoll = 0.0f;
        mb104 = false;
        mb105 = false;
        mF130 = 0.0f;
        mF12C = 0.0f;
        mF138 = 0.0f;
        mF134 = 0.0f;
        mV108.x = mVa0.x - mVb8.x;
        mV108.y = mVa0.y - mVb8.y;
        mV108.z = mVa0.z - mVb8.z;
        mF1E4 = 0.0f;
    }
    mbSkipInit = false;
}
