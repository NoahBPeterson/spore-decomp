// Slice s00e956f0: the single function in this slice is
//   0x00E956F0  SP::cVehicleView::HandleSimulationUpdate   (7096 bytes, __thiscall, ret 8)
//
// Per-simulation-step update of a civ/space vehicle's view (retail layout; the 2008 PDB
// layout of cVehicleView differs, so members below are named from what the code does).
// In order it:
//   - mirrors the vehicle's selection position into the view and the model (+0x4c),
//     sets the model's "hidden/selectable" flag bits, positions the 0x2b255e5 effect;
//   - calls cSpatialObjectView::HandleSimulationUpdate;
//   - drives the model's highlight state (byte +0x5c / flag 8) from rollover,
//     combatant state and the civ tutorial; space mode updates two UI effects;
//   - toggles the debug effect 0x2b255e5 from a global, the 0x5f8d751 effect;
//   - interpolates the view scale toward a property override (zoom-out scale);
//   - builds the model transform from the vehicle (position, scale, orientation)
//     and adds a time-based wobble (boat bob / hover / ufo-stunned shake);
//   - if the vehicle is dead: hides the view and destroys all effects, returns;
//   - drains the vehicle's queued view events (27-case switch of effect commands);
//   - plays/stops the damage, towed item/balloon, cargo, path (wake/contrail) and
//     damage-smoke effects, drives the animator and the 3D movement sound;
//   - civ mode: a tutorial highlight effect on the player's first vehicle.
// Build flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc: the original has no EH frame;
// /fp:fast is needed for the inline fsin/fcos/fsqrt).
#include "types.h"

#pragma warning(disable: 4100)

extern "C" double __cdecl sin(double);
extern "C" double __cdecl cos(double);
extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sin, cos, sqrt)

enum GameModeIDs {
    kGameCiv      = 0x1654C04,
    kGameSpace    = 0x1654C05,
    kScenarioMode = 0x1654C10,
};
enum VehicleLocomotion { kVehicleLand = 0, kVehicleWater = 1, kVehicleAir = 2 };

struct Vector3 { float x, y, z; };
struct Quaternion { float x, y, z, w; };

struct Matrix3 {
    float m[3][3];   // rows: x axis, y axis, z axis
    Matrix3& Assign(const Matrix3& other);   // 0x0041CB40
};

// cTransform / cSPTransform: flags, modification count, offset, scale, rotation (0x38 bytes).
struct cSPTransform {
    uint16_t mFlags;
    uint16_t mModificationCount;
    Vector3  mOffset;
    float    mScale;
    Matrix3  mRotation;

    cSPTransform& operator=(const cSPTransform& other);   // 0x00537DC0
    void Rotate(float angle);                            // 0x006B9050
    void RotateY(float angle);                           // 0x004099B0
    void PreRotateX(float angle);                        // 0x005A2D90

    // offset += rotation * (v * scale)
    void PreTranslate(const Vector3& v) {
        float x = v.x * mScale;
        float y = v.y * mScale;
        float z = v.z * mScale;
        mFlags |= 4;
        mModificationCount++;
        mOffset.x += mRotation.m[0][0] * x + mRotation.m[1][0] * y + mRotation.m[2][0] * z;
        mOffset.y += mRotation.m[0][1] * x + mRotation.m[1][1] * y + mRotation.m[2][1] * z;
        mOffset.z += mRotation.m[0][2] * x + mRotation.m[1][2] * y + mRotation.m[2][2] * z;
    }
};

namespace SP {

extern const Matrix3 kIdentityMatrix3;   // 0x016C624C
extern const Vector3 kWobbleAxisSin;     // 0x016C6270
extern const Vector3 kWobbleAxisCos;     // 0x016C627C
extern float gWobbleAmplitude;           // 0x015A8A54
extern float gScaleOverrideThreshold;    // 0x0169CAB4
extern bool  gShowDebugVehicleEffect;    // 0x0168BCF4
extern uint32_t gModelWorldEffectGroup;  // 0x015A8A44
extern uint32_t gVehicleSpeedSoundParam; // 0x015A8AB0

uint32_t GetCurrentGameMode();                                        // 0x00B5B800
Matrix3* Matrix3FromQuaternion(Matrix3* out, const Quaternion& q);    // 0x0059C190
void Start3dSoundByName(uint32_t name, uint32_t handle, float x, float y, float z);  // 0x00571F80
void SetSoundPosition(uint32_t handle, float x, float y, float z);   // 0x009FBC50
namespace EditorUtils {
void PlayEditorSound(uint32_t handle, uint32_t param, float value, int flag);  // 0x00435F40
}
void AttachSelectionEffect(class cSpatialObject* obj, void* effect, int flag);  // 0x01043860
void AttachRolloverEffect(class cSpatialObject* obj, void* effect, int flag);   // 0x01043A50

struct cSPTimer {
    char mData[0x20];
    void Stop();                          // 0x00BC3110
    void Restart();                       // 0x00BC3130
    uint64_t GetElapsedTime();            // 0x00BC3190
    bool IsRunning();                     // 0x00FEBA90
};

// Graphics model (cSpatialObject::GetModel)
struct cModel {
    void*        vtable;
    uint32_t     mFlags;                  // +0x04
    cSPTransform mTransform;              // +0x08
    char         _pad40[0x0c];
    Vector3      mSelectionPosition;      // +0x4c
    char         _pad58[4];
    uint8_t      mHighlight;              // +0x5c
};

struct IModelWorld {
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
    virtual void _v10(); virtual void _v14(); virtual void _v18(); virtual void _v1c();
    virtual void _v20(); virtual void _v24(); virtual void _v28(); virtual void _v2c();
    virtual void _v30(); virtual void _v34(); virtual void _v38(); virtual void _v3c();
    virtual void _v40(); virtual void _v44(); virtual void _v48(); virtual void _v4c();
    virtual void _v50(); virtual void _v54(); virtual void _v58(); virtual void _v5c();
    virtual void _v60(); virtual void _v64(); virtual void _v68(); virtual void _v6c();
    /* 70h */ virtual void StopEffectGroup(cModel* model, uint32_t group, int a, float b, uint32_t id);
};
IModelWorld* GonzagoModelWorld();          // 0x00B3D520

struct IVisualEffect {
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
    virtual void _v10(); virtual void _v14(); virtual void _v18(); virtual void _v1c();
    virtual void _v20(); virtual void _v24(); virtual void _v28(); virtual void _v2c();
    virtual void _v30(); virtual void _v34(); virtual void _v38(); virtual void _v3c();
    virtual void _v40();
    /* 44h */ virtual void SetParams(int param, float* values, int count);
};

class cSpatialObject {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
    virtual void _v10(); virtual void _v14(); virtual void _v18(); virtual void _v1c();
    virtual void _v20();
    /* 24h */ virtual bool IsRolledOver();
    virtual void _v28(); virtual void _v2c(); virtual void _v30(); virtual void _v34();
    virtual void _v38(); virtual void _v3c(); virtual void _v40(); virtual void _v44();
    virtual void _v48(); virtual void _v4c();
    /* 50h */ virtual bool IsSelected();
    virtual void _v54(); virtual void _v58(); virtual void _v5c(); virtual void _v60();
    virtual void _v64(); virtual void _v68(); virtual void _v6c(); virtual void _v70();
    virtual void _v74(); virtual void _v78(); virtual void _v7c(); virtual void _v80();
    virtual void _v84();
    /* 88h */ virtual bool HasModelChanged();
    virtual void _v8c(); virtual void _v90(); virtual void _v94(); virtual void _v98();
    virtual void _v9c(); virtual void _va0(); virtual void _va4(); virtual void _va8();
    /* ach */ virtual cModel* GetModel();
    virtual void _vb0(); virtual void _vb4();
    /* b8h */ virtual void* Cast(uint32_t type);

    // effect list (non-virtual)
    IVisualEffect* GetEffectObject(uint32_t id);                             // 0x00C888E0
    bool GetEffect(uint32_t id);                                             // 0x00C88910
    void StartEffect(uint32_t id, int restart);                              // 0x00C88980
    void SetEffectRange(uint32_t id, float range);                           // 0x00C88A00
    void SetEffectPosition(uint32_t id, const Vector3* pos);                 // 0x00C88A30
    void SetEffectScale(uint32_t id, float scale);                           // 0x00C8A020
    void StopEffect(uint32_t id, int hard);                                  // 0x00C8AD30
    void DestroyAllEffects(int flag);                                        // 0x00C8B0A0
    void CreateEffect(uint32_t effectID, int group, uint32_t id);            // 0x00C8B130
    void CreateAttachedEffect(uint32_t effectID, int group, uint32_t id);    // 0x00C8B1B0
    bool SetEffectActive(uint32_t effectID, uint32_t id, bool active, int a);// 0x00C8B220
};

// cSpatialObject base of cLocomotiveObject (vehicle + 0x34)
class cLocomotiveObject {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
    virtual void _v10(); virtual void _v14(); virtual void _v18(); virtual void _v1c();
    virtual void _v20(); virtual void _v24(); virtual void _v28();
    /* 2ch */ virtual const Vector3& GetPosition();
    /* 30h */ virtual const Quaternion& GetOrientation();
    /* 34h */ virtual float GetScale();
    virtual void _v38(); virtual void _v3c(); virtual void _v40(); virtual void _v44();
    virtual void _v48(); virtual void _v4c(); virtual void _v50(); virtual void _v54();
    /* 58h */ virtual bool IsPlayerOwned();
    virtual void _v5c(); virtual void _v60(); virtual void _v64(); virtual void _v68();
    virtual void _v6c();
    /* 70h */ virtual float GetBoundingRadius();
    /* 74h */ virtual float GetFootprintRadius();
    virtual void _v78(); virtual void _v7c(); virtual void _v80(); virtual void _v84();
    virtual void _v88(); virtual void _v8c(); virtual void _v90(); virtual void _v94();
    virtual void _v98(); virtual void _v9c(); virtual void _va0(); virtual void _va4();
    virtual void _va8(); virtual void _vac(); virtual void _vb0(); virtual void _vb4();
    virtual void _vb8(); virtual void _vbc(); virtual void _vc0(); virtual void _vc4();
    virtual void _vc8();
    /* cch */ virtual float GetStandardSpeed();

    const Vector3& GetVelocity();         // 0x00D20610
};

// cCombatant base (vehicle + 0x508)
class cCombatant {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
    virtual void _v10(); virtual void _v14(); virtual void _v18(); virtual void _v1c();
    virtual void _v20(); virtual void _v24(); virtual void _v28(); virtual void _v2c();
    virtual void _v30(); virtual void _v34(); virtual void _v38();
    /* 3ch */ virtual bool IsStunned();

    float GetHealthPercentage();          // 0x00BFC490
    bool  IsUnderAttack();                // 0x00BFC5D0
    bool  IsStaticClingStunned();         // 0x00BFC600
};

struct tAttachedEffect {        // 16 bytes
    class cGameData* mpObject;  // +0x00
    int      _pad04;
    uint32_t mEffectID;         // +0x08
    bool     mbActive;          // +0x0c
};
struct tAttachedEffects { tAttachedEffect* mpBegin; tAttachedEffect* mpEnd; };

class cGameData {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
    virtual void _v10(); virtual void _v14(); virtual void _v18(); virtual void _v1c();
    virtual void _v20(); virtual void _v24(); virtual void _v28(); virtual void _v2c();
    virtual void _v30(); virtual void _v34(); virtual void _v38(); virtual void _v3c();
    virtual void _v40(); virtual void _v44(); virtual void _v48();
    /* 4ch */ virtual uint32_t GetPoliticalID();

    struct tOwnerInfo { void* mpOwner; int _pad[3]; int mKind; };
    tOwnerInfo* GetOwnerInfo();            // 0x00CA71D0
    bool IsEffectAttached();               // 0x0104BD50 (on tAttachedEffect::mpObject)
};
struct tGameDataList { cGameData** mpBegin; cGameData** mpEnd; };

class cVehicle {
public:
    char              _pad00[0x34];
    cLocomotiveObject mLocomotive;        // +0x34
    char              _pad38[0x84 - 0x38];
    uint32_t          mFlags;             // +0x84
    char              _pad88[0xd9 - 0x88];
    bool              mbHideZoomOut;      // +0xd9
    char              _padda[0x2a4 - 0xda];
    uint8_t           mCargoFlags;        // +0x2a4
    char              _pad2a5[0x508 - 0x2a5];
    cCombatant        mCombatant;         // +0x508
    char              _pad50c[0xaf4 - 0x50c];
    bool              mbUFOCarried;       // +0xaf4
    char              _padaf5[0xb1c - 0xaf5];
    int               mLocomotion;        // +0xb1c
    char              _padb20[0xbcd - 0xb20];
    bool              mbDead;             // +0xbcd
    char              _padbce[0xc58 - 0xbce];
    float             mSpeedStat;         // +0xc58

    Vector3  GetSelectionPosition();       // 0x00C9F650
    float    GetSoundPitch();              // 0x00C9EBF0
    float    GetSoundParam();              // 0x00C9EC00
    tAttachedEffects* GetAttachedEffects();// 0x00C9EC70
    bool     ScaleAnimationSpeed();        // 0x00C9EEF0
    bool     IsHovering();                 // 0x00C9EF20
    uint32_t GetMovementSound();           // 0x00CA0040
    int      PopViewEvent();               // 0x00CA6F70
};

struct cCityTerritory { char _pad[0x80]; class cCivTutorial* mpTutorial; };
class cCivTutorial {
public:
    bool IsActive();                       // 0x00D09660
    bool IsHighlighted(cVehicle* vehicle); // 0x00D09740
};
class cCivModeStrategy {
public:
    cCityTerritory* GetPlayerTerritory();             // 0x00CF74F0
    bool HasCivTutorialOccurred(uint32_t id);         // 0x00CF7830
    cVehicle* GetFirstVehicle(int index);             // 0x00CF7D40
};
cCivModeStrategy* CivModeStrategy();                   // 0x00CF74C0

struct cGameTimeManager { char _pad[0x48]; uint8_t mPauseFlags; };
cGameTimeManager* GameTimeManager();                   // 0x00B3D380
struct cPlanetModel { char _pad[0xf0]; bool mbIsRetro; };
cPlanetModel* PlanetModel();                           // 0x00B3D350

class cNounManager {
public:
    tGameDataList* GetVehicleList();                   // 0x00AE73B0
    char* GetCityByPoliticalID(uint32_t id);           // 0x00B25F40
};
cNounManager* NounManager();                           // 0x00B3D300

class InputHost { public: void GetAnglesB(float* a, float* b, float* c); };   // 0x00B0F240
InputHost* GetInputHost();                             // 0x00B3D280

struct Property {
    char _pad[0x12];
    int16_t mnType;
    float* GetFloat();                                // 0x0041EA70
};
class PropertyList {
public:
    virtual void AddRef(); virtual void Release();
    virtual void _v08(); virtual void _v0c(); virtual void _v10(); virtual void _v14();
    virtual void _v18(); virtual void _v1c(); virtual void _v20();
    /* 24h */ virtual bool GetProperty(uint32_t id, Property*& prop);
};
class cPropertyManager {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
    virtual void _v10(); virtual void _v14(); virtual void _v18(); virtual void _v1c();
    virtual void _v20(); virtual void _v24(); virtual void _v28(); virtual void _v2c();
    /* 30h */ virtual bool GetPropertyList(uint32_t id, PropertyList*& list);
};
cPropertyManager* PropertyManager();                   // 0x0067DE30

struct PropertyListPtr {
    PropertyList* p;
    PropertyListPtr() : p(0) {}
    ~PropertyListPtr() { if (p) p->Release(); }
    void reset() { if (p) { PropertyList* t = p; p = 0; t->Release(); } }
};

class IAudioSystem {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
    /* 10h */ virtual const float* GetListenerPosition(int index);
    virtual void _v14(); virtual void _v18(); virtual void _v1c();
    /* 20h */ virtual uint32_t NewSoundHandle();
    virtual void _v24(); virtual void _v28(); virtual void _v2c(); virtual void _v30();
    virtual void _v34();
    /* 38h */ virtual void BeginMessage(uint32_t msg);
    virtual void _v3c();
    /* 40h */ virtual void SetParam(uint32_t key, uint32_t value);
    virtual void _v44(); virtual void _v48(); virtual void _v4c(); virtual void _v50();
    virtual void _v54();
    /* 58h */ virtual void SendMessage();
};
}  // namespace SP
namespace EA { namespace Audio { SP::IAudioSystem* GetSystemAT(); } }   // 0x00A206F0
namespace EA { namespace Hash {
uint32_t FNV1_String8(const char* s, uint32_t seed, int lowercase);    // 0x00932E80
} }

namespace SP {

struct cVehicleAnimator {
    bool mbZoomedOut;   // +0x00
    char _pad[0x17];
    void Update(float deltaTime, float speed, float maxSpeed, IModelWorld* world, cModel* model);  // 0x00E94A10
    void AttachEffect(IModelWorld* world, cModel* model, uint32_t effectID);                      // 0x00E94AD0
};

class cSpatialObjectView {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
    /* 10h */ virtual void SetVisible(int visible);
    virtual void _v14(); virtual void _v18(); virtual void _v1c();
    virtual void _v20(); virtual void _v24(); virtual void _v28();
    /* 2ch */ virtual cModel* GetViewModel();

    char            _pad04[8];
    cSpatialObject* mpObject;        // +0x0c
    char            _pad10[8];
    Vector3         mPosition;       // +0x18
    char            _pad24[0x40 - 0x24];

    void HandleSimulationUpdate(int deltaTimeMS, float deltaTime);   // 0x00E92CA0
};

class cVehicleView : public cSpatialObjectView {
public:
    void HandleSimulationUpdate(int deltaTimeMS, float deltaTime);
    void SpawnCargoEffect(cVehicle* vehicle);                                       // 0x00E94E50
    void UpdateTowedItem(cVehicle* vehicle, IVisualEffect* effect, float deltaTime, bool tethered);  // 0x00E94F30
    void ConnectBalloonString(cVehicle* vehicle, IVisualEffect* balloon);           // 0x00E953A0

    char             _pad40[0x58 - 0x40];
    cSPTimer         mPathTimer;          // +0x58
    cSPTimer         mWobbleTimer;        // +0x78
    uint32_t         mSoundHandle;        // +0x98
    uint32_t         mSoundName;          // +0x9c
    uint32_t         mWobbleOffset;       // +0xa0
    float            mTargetScale;        // +0xa4
    float            mScale;              // +0xa8
    float            mScaleOverride;      // +0xac
    cVehicleAnimator mAnimator;           // +0xb0
    char             mSelectionEffect[4]; // +0xc8
    char             mRolloverEffect[4];  // +0xcc
};

static __forceinline float WobbleAngle(uint64_t t)
{
    return (float)(t % 6283) * 0.001f;
}

// @ 0x00E956F0
void cVehicleView::HandleSimulationUpdate(int deltaTimeMS, float deltaTime)
{
    cVehicle* vehicle = mpObject ? (cVehicle*)mpObject->Cast(0x137e8e0) : 0;
    uint32_t gameMode = GetCurrentGameMode();

    if (mpObject->HasModelChanged() && mpObject->GetModel()) {
        Vector3 pos = vehicle->GetSelectionPosition();
        mPosition = pos;
        mpObject->GetModel()->mSelectionPosition = pos;
        if (GetCurrentGameMode() == kScenarioMode) {
            mpObject->GetModel()->mFlags &= ~0x800;
            mpObject->GetModel()->mFlags &= ~4;
        } else {
            if (vehicle->mLocomotive.IsPlayerOwned())
                mpObject->GetModel()->mFlags &= ~0x800;
            else
                mpObject->GetModel()->mFlags |= 0x800;
            mpObject->GetModel()->mFlags |= 4;
        }
        mpObject->SetEffectPosition(0x2b255e5, &mPosition);
    }
    if (vehicle->mbHideZoomOut)
        mAnimator.mbZoomedOut = false;

    cSpatialObjectView::HandleSimulationUpdate(deltaTimeMS, deltaTime);

    mpObject->IsSelected();
    bool rolledOver = mpObject->IsRolledOver();
    bool underAttack = vehicle->mCombatant.IsUnderAttack();
    cModel* model = mpObject->GetModel();
    bool isSpace = gameMode == kGameSpace;

    bool tutorialActive;
    if (CivModeStrategy() && CivModeStrategy()->GetPlayerTerritory() &&
        CivModeStrategy()->GetPlayerTerritory()->mpTutorial &&
        CivModeStrategy()->GetPlayerTerritory()->mpTutorial->IsActive())
        tutorialActive = true;
    else
        tutorialActive = false;

    if (GetCurrentGameMode() != kScenarioMode && model) {
        bool highlight = false;
        if (tutorialActive) {
            if (vehicle->mLocomotive.IsPlayerOwned() &&
                (rolledOver || CivModeStrategy()->GetPlayerTerritory()->mpTutorial->IsHighlighted(vehicle))) {
                model->mHighlight = 2;
                highlight = true;
            }
        } else if ((rolledOver || underAttack) && !(GameTimeManager()->mPauseFlags & 1) && !isSpace) {
            model->mHighlight = 2;
            highlight = true;
        }
        if (highlight)
            model->mFlags |= 8;
        else
            model->mFlags &= ~8;
    }

    if (isSpace) {
        AttachSelectionEffect(mpObject, mSelectionEffect, 0);
        AttachRolloverEffect(mpObject, mRolloverEffect, 0);
    }

    if (gShowDebugVehicleEffect && !mpObject->GetEffect(0x2b255e5)) {
        mpObject->CreateEffect(0x8568321f, 0, 0x2b255e5);
        mpObject->SetEffectPosition(0x2b255e5, &mPosition);
    } else if (!gShowDebugVehicleEffect && mpObject->GetEffect(0x2b255e5)) {
        mpObject->StopEffect(0x2b255e5, 1);
    }

    if (mpObject->SetEffectActive(0xdb4e05f3, 0x5f8d751, vehicle->IsHovering(), 0))
        mpObject->SetEffectScale(0x5f8d751, vehicle->mLocomotive.GetBoundingRadius() * 0.083333336f);

    // zoom-out scale override
    float angleA = 0.0f, angleB = 0.0f, zoom = 0.0f;
    if (GetInputHost())
        GetInputHost()->GetAnglesB(&angleA, &angleB, &zoom);
    if (zoom > gScaleOverrideThreshold) {
        PropertyListPtr propList;
        cPropertyManager* propManager = PropertyManager();
        propList.reset();
        Property* prop;
        if (propManager->GetPropertyList(0xb6a5c63d, propList.p) && propList.p &&
            propList.p->GetProperty(0x1c3818d, prop) && prop->mnType == 0xd)
            mScaleOverride = *prop->GetFloat();
        mTargetScale = mScaleOverride;
    } else {
        mTargetScale = 1.0f;
    }

    if (mScale != mTargetScale) {
        float t = (float)(unsigned int)deltaTimeMS * 0.008f;
        if (t < 0.0f) t = 0.0f;
        if (t > 1.0f) t = 1.0f;
        if (t == 1.0f)
            mScale = mTargetScale;
        else
            mScale = (mTargetScale - mScale) * t + mScale;
    }
    if (model) {
        model->mTransform.mModificationCount++;
        model->mTransform.mScale = mScale;
    }

    // model transform from the vehicle, plus wobble
    cSPTransform transform;
    transform.mFlags = 0;
    transform.mModificationCount = 0;
    transform.mRotation.Assign(kIdentityMatrix3);
    transform.mOffset = vehicle->mLocomotive.GetPosition();
    transform.mFlags |= 4;
    transform.mModificationCount++;
    transform.mScale = vehicle->mLocomotive.GetScale();
    transform.mModificationCount++;
    Matrix3 rotation;
    transform.mRotation = *Matrix3FromQuaternion(&rotation, vehicle->mLocomotive.GetOrientation());
    transform.mFlags |= 2;
    transform.mModificationCount++;

    int locomotion = vehicle->mLocomotion;
    bool bobbing = (vehicle->mFlags & 0x1000) == 0x1000;
    if (locomotion == kVehicleWater && !PlanetModel()->mbIsRetro && bobbing) {
        float roll, amplitude;
        if (GetCurrentGameMode() == kScenarioMode) {
            roll = gWobbleAmplitude * 0.002f;
            amplitude = 0.002f;
        } else {
            roll = gWobbleAmplitude * 0.012f;
            amplitude = 0.15f;
        }
        uint64_t t = mWobbleTimer.GetElapsedTime() + mWobbleOffset;
        uint64_t half = t / 2;
        float angle = WobbleAngle(half + half / 4);
        float s = (float)sin(angle);
        transform.Rotate((float)(cos(angle) * roll));
        roll = s * roll;
        transform.RotateY(roll * 0.5f);
        transform.PreRotateX(roll);
        Vector3 v = { kWobbleAxisSin.x * s * amplitude, kWobbleAxisSin.y * s * amplitude,
                      kWobbleAxisSin.z * s * amplitude };
        transform.PreTranslate(v);
    } else if (vehicle->mbUFOCarried) {
        uint64_t t = mWobbleTimer.GetElapsedTime() + mWobbleOffset;
        float angle = WobbleAngle(t * 16);
        float s = (float)sin(angle);
        transform.Rotate((float)(cos(angle) * 0.025f));
        transform.PreRotateX(s * 0.0125f);
        Vector3 v = { kWobbleAxisSin.x * s * 0.05f, kWobbleAxisSin.y * s * 0.05f,
                      kWobbleAxisSin.z * s * 0.05f };
        transform.PreTranslate(v);
    } else if (locomotion == kVehicleAir) {
        uint64_t t = mWobbleTimer.GetElapsedTime() + mWobbleOffset;
        uint64_t half = t / 2;
        float angle = WobbleAngle(half + half / 4);
        float s = (float)sin(angle);
        float c = (float)cos(angle);
        float k = GetCurrentGameMode() == kScenarioMode ? 0.02f : 1.0f;
        Vector3 v1 = { kWobbleAxisSin.x * s * k, kWobbleAxisSin.y * s * k, kWobbleAxisSin.z * s * k };
        transform.PreTranslate(v1);
        Vector3 v2 = { kWobbleAxisCos.x * c * k, kWobbleAxisCos.y * c * k, kWobbleAxisCos.z * c * k };
        transform.PreTranslate(v2);
    }
    if (model)
        model->mTransform = transform;

    if (vehicle->mbDead) {
        SetVisible(0);
        mpObject->DestroyAllEffects(0);
        return;
    }

    // queued view events
    int event;
    while ((event = vehicle->PopViewEvent()) != 0) {
        switch (event) {
        case 1:
        case 7:
            mpObject->CreateEffect(0x24b83dde, 0, 0x1a2c90a);
            break;
        case 3:
            mpObject->CreateEffect(0x525a3ae7, 0, 0x1a2c90a);
            break;
        case 5:
            mpObject->CreateEffect(0x2b09618, 0, 0x1a2c90a);
            break;
        case 2:
        case 4:
        case 6:
        case 8:
            mpObject->StopEffect(0x1a2c90a, 1);
            break;
        case 9:
            mpObject->CreateEffect(0x2f81eb6c, 0, 0x2cb4945);
            break;
        case 10:
            mpObject->CreateAttachedEffect(0x754300d, 0, 0x2ce1024);
            mpObject->SetEffectRange(0x2ce1024, 3.402823466e+38f);
            mpObject->SetEffectPosition(0x2ce1024, &mPosition);
            break;
        case 12:
            mpObject->CreateEffect(0xd68766, 0, 0x4a34ef1);
            mpObject->CreateEffect(0x4ceb8dd6, 0, 0x4dbff4f);
            mpObject->SetEffectPosition(0x4dbff4f, &mPosition);
            if (!mpObject->GetEffect(0x4ffb17f)) {
                mpObject->CreateEffect(0xda481c1f, 0, 0x4ffb17f);
                SpawnCargoEffect(vehicle);
            } else {
                mpObject->StartEffect(0x4ffb17f, 1);
                SpawnCargoEffect(vehicle);
            }
            break;
        case 14:
            mpObject->StopEffect(0x4ffb17f, 1);
            // fall through
        case 13:
            mpObject->StopEffect(0x4a34ef1, 1);
            mpObject->StopEffect(0x4dbff4f, 1);
            break;
        case 15:
            if (!mpObject->GetEffect(0x4288910)) {
                mpObject->CreateEffect(0x540964f0, 0, 0x4288910);
                mpObject->SetEffectPosition(0x4288910, &mPosition);
            }
            break;
        case 16:
            mpObject->StopEffect(0x4288910, 1);
            if (!mpObject->GetEffect(0x4dbff4e)) {
                mpObject->CreateEffect(0x2c6ea0c4, 0, 0x4dbff4e);
                mpObject->SetEffectPosition(0x4dbff4e, &mPosition);
            } else {
                mpObject->StartEffect(0x4dbff4e, 1);
            }
            break;
        case 17:
            mpObject->StopEffect(0x4dbff4e, 1);
            mpObject->StopEffect(0x4ffb17f, 1);
            break;
        case 18:
            if (!mpObject->GetEffect(0x428890e))
                mpObject->CreateEffect(0x8caee048, 0, 0x428890e);
            break;
        case 19:
            mpObject->StopEffect(0x428890e, 1);
            break;
        case 20:
            mpObject->CreateAttachedEffect(0x2abf6155, 0, 0x428890f);
            mpObject->SetEffectPosition(0x428890f, &mPosition);
            mpObject->SetEffectRange(0x428890f, 1024.0f);
            break;
        case 21:
            mpObject->CreateAttachedEffect(0x2241f9c6, 0, 0x4ebf115);
            mpObject->SetEffectPosition(0x4ebf115, &mPosition);
            mpObject->SetEffectRange(0x4ebf115, 1024.0f);
            break;
        case 22:
            mpObject->StopEffect(0x428890f, 1);
            mpObject->CreateAttachedEffect(0x4f014cd5, 0, 0x4288914);
            mpObject->SetEffectPosition(0x4288914, &mPosition);
            mpObject->SetEffectRange(0x4288914, 1024.0f);
            break;
        case 23:
            mpObject->StopEffect(0x4ebf115, 1);
            mpObject->CreateAttachedEffect(0x4683e546, 0, 0x4ebeeac);
            mpObject->SetEffectPosition(0x4ebeeac, &mPosition);
            mpObject->SetEffectRange(0x4ebeeac, 1024.0f);
            break;
        case 24: {
            mpObject->CreateEffect(0xc6adcb63, 0, 0x41a447a);
            tGameDataList* vehicles = NounManager()->GetVehicleList();
            int count = (int)(vehicles->mpEnd - vehicles->mpBegin);
            for (int i = 0; i < count; i++) {
                cGameData* other = vehicles->mpBegin[i];
                cGameData::tOwnerInfo* info = other->GetOwnerInfo();
                if (info->mKind == 1 && info->mpOwner == vehicle) {
                    char* city = NounManager()->GetCityByPoliticalID(other->GetPoliticalID());
                    if (city)
                        mpObject->SetEffectPosition(0x41a447a, (const Vector3*)(city + 0xc4));
                }
            }
            break;
        }
        case 25:
            mpObject->StopEffect(0x41a447a, 1);
            break;
        case 26:
            if (!mpObject->GetEffect(0x4b72043)) {
                uint32_t effectID = 0x70352681;
                if (locomotion == kVehicleWater)
                    effectID = 0xd1f896dd;
                else if (locomotion == kVehicleAir)
                    effectID = 0xda1b35e4;
                mpObject->CreateEffect(effectID, 0, 0x4b72043);
            }
            break;
        case 27:
            mpObject->StopEffect(0x4b72043, 0);
            break;
        case 28:
            mpObject->StopEffect(0x4b72043, 1);
            break;
        }
    }

    // damage effect
    if (vehicle->mFlags & 0x800) {
        if (!mpObject->GetEffect(0x30e8895)) {
            mpObject->CreateEffect(vehicle->mLocomotion != kVehicleAir ? 0x56191017 : 0x36150560, 0, 0x30e8895);
            mpObject->SetEffectScale(0x30e8895, vehicle->mLocomotive.GetFootprintRadius());
            mpObject->SetEffectRange(0x30e8895, 512.0f);
        }
        vehicle->mFlags &= ~0x800;
    } else if (mpObject->GetEffect(0x30e8895)) {
        mpObject->StopEffect(0x30e8895, 1);
    }

    // towed item / balloon
    IVisualEffect* balloon = mpObject->GetEffectObject(0x4ffb17f);
    if (balloon) {
        if (mpObject->GetEffect(0x4dbff4f))
            UpdateTowedItem(vehicle, mpObject->GetEffectObject(0x4dbff4f), deltaTime, false);
        else if (mpObject->GetEffect(0x4288910))
            UpdateTowedItem(vehicle, mpObject->GetEffectObject(0x4288910), deltaTime, true);
        else if (mpObject->GetEffect(0x4dbff4e))
            UpdateTowedItem(vehicle, mpObject->GetEffectObject(0x4dbff4e), deltaTime, false);
        ConnectBalloonString(vehicle, balloon);
    }

    // cargo effect
    if (vehicle->mCargoFlags & 8) {
        if (!mpObject->GetEffect(0x3572487))
            mpObject->CreateEffect(0xe489024c, 0, 0x3572487);
    } else {
        mpObject->StopEffect(0x3572487, 1);
    }

    // animator
    const Vector3& velocity = vehicle->mLocomotive.GetVelocity();
    float speed = (float)sqrt(velocity.x * velocity.x + velocity.y * velocity.y + velocity.z * velocity.z);
    float animSpeed = speed;
    float maxSpeed = vehicle->mLocomotive.GetStandardSpeed();
    if (vehicle->ScaleAnimationSpeed()) {
        float minFraction;
        switch (vehicle->mLocomotion) {
        case kVehicleWater: minFraction = 0.1f; break;
        case kVehicleAir:   minFraction = 0.4f; break;
        default:            minFraction = 0.3f; break;
        }
        float clamped = speed;
        if (clamped < 0.0f) clamped = 0.0f;
        if (clamped > maxSpeed) clamped = maxSpeed;
        animSpeed = (maxSpeed - minFraction * maxSpeed) * (clamped / maxSpeed) + minFraction * maxSpeed;
    }
    mAnimator.Update(deltaTime, animSpeed, maxSpeed, GonzagoModelWorld(), GetViewModel());

    // effects attached to the vehicle's attached objects
    tAttachedEffects* attached = vehicle->GetAttachedEffects();
    int attachedCount = (int)(attached->mpEnd - attached->mpBegin);
    for (int i = 0; i < attachedCount; i++) {
        tAttachedEffect& entry = attached->mpBegin[i];
        if (entry.mpObject->IsEffectAttached()) {
            if (!entry.mbActive) {
                uint32_t effectID = entry.mEffectID;
                entry.mbActive = true;
                mAnimator.AttachEffect(GonzagoModelWorld(), GetViewModel(), effectID);
            }
        } else if (entry.mbActive) {
            entry.mbActive = false;
            uint32_t effectID = entry.mEffectID;
            cModel* viewModel = GetViewModel();
            IModelWorld* world = GonzagoModelWorld();
            if (world && viewModel && ((viewModel->mFlags >> 14) & 1))
                world->StopEffectGroup(viewModel, gModelWorldEffectGroup, 1, 0.0f, effectID);
        }
    }

    // 3D movement sound
    uint32_t soundName = vehicle->GetMovementSound();
    Vector3 position = vehicle->mLocomotive.GetPosition();
    bool inRange = false;
    if (EA::Audio::GetSystemAT()) {
        const float* listener = EA::Audio::GetSystemAT()->GetListenerPosition(1);
        float dx = listener[0] - position.x;
        float dy = listener[1] - position.y;
        float dz = listener[2] - position.z;
        float distance = (float)sqrt(dx * dx + dy * dy + dz * dz);
        if (distance < 250.0f)
            inRange = true;
    }
    if (!inRange || soundName != mSoundName) {
        uint32_t handle = mSoundHandle;
        if (handle) {
            IAudioSystem* audio = EA::Audio::GetSystemAT();
            if (audio) {
                audio->BeginMessage(0x347536b);
                audio->SetParam(0x3475385, handle);
                audio->SetParam(0x34753a0, 0);
                audio->SendMessage();
            }
            mSoundHandle = 0;
            mSoundName = 0;
        }
    }
    if (inRange && !mSoundHandle && soundName) {
        IAudioSystem* audio = EA::Audio::GetSystemAT();
        uint32_t handle = audio ? audio->NewSoundHandle() : 0;
        mSoundHandle = handle;
        mSoundName = soundName;
        Start3dSoundByName(soundName, handle, position.x, position.y, position.z);
        EditorUtils::PlayEditorSound(mSoundHandle, 0x71bc3009, 1.0f / vehicle->GetSoundPitch(), 1);
    }
    if (mSoundHandle) {
        float speedStat = vehicle->mSpeedStat > 0.33f ? vehicle->mSpeedStat : 0.33f;
        float volume = speed / vehicle->mLocomotive.GetStandardSpeed() * speedStat;
        if (volume < 0.0f) volume = 0.0f;
        if (volume > 1.0f) volume = 1.0f;
        SetSoundPosition(mSoundHandle, position.x, position.y, position.z);
        EditorUtils::PlayEditorSound(mSoundHandle, gVehicleSpeedSoundParam, volume, 0);
        EditorUtils::PlayEditorSound(mSoundHandle, 0x70e47545, vehicle->GetSoundParam(), 0);
    }

    // path effect (ground dust / boat wake / air contrails)
    if (speed > 0.1f) {
        if (!mpObject->GetEffect(0x2b216c7)) {
            mPathTimer.Stop();
            float speedStat = vehicle->mSpeedStat;
            const char* name = 0;
            switch (locomotion) {
            case kVehicleLand:
                if (speedStat < 0.33f)      name = "civ_vehicle_ground_moving_slow";
                else if (speedStat < 0.66f) name = "civ_vehicle_ground_moving_medium";
                else                        name = "civ_vehicle_ground_moving_fast";
                break;
            case kVehicleWater:
                if (speedStat < 0.33f)      name = "civ_vehicle_boat_wake_slow";
                else if (speedStat < 0.66f) name = "civ_vehicle_boat_wake_medium";
                else                        name = "civ_vehicle_boat_wake_fast";
                break;
            case kVehicleAir:
                if (speedStat < 0.33f)      name = "civ_vehicle_air_contrails_slow";
                else if (speedStat < 0.66f) name = "civ_vehicle_air_contrails_medium";
                else                        name = "civ_vehicle_air_contrails_fast";
                break;
            }
            mpObject->CreateEffect(EA::Hash::FNV1_String8(name, 0x811c9dc5, 1), 0, 0x2b216c7);
            mpObject->SetEffectRange(0x2b216c7, 3.402823466e+38f);
            mpObject->SetEffectPosition(0x2b216c7, &mPosition);
        } else if (mPathTimer.IsRunning()) {
            mPathTimer.Stop();
            IVisualEffect* effect = mpObject->GetEffectObject(0x2b216c7);
            float intensity = 1.0f;
            effect->SetParams(4, &intensity, 1);
        }
    } else {
        if (mpObject->GetEffect(0x2b216c7)) {
            if (!mPathTimer.IsRunning())
                mPathTimer.Restart();
            if (mPathTimer.GetElapsedTime() > 1000) {
                mpObject->StopEffect(0x2b216c7, 1);
            } else {
                IVisualEffect* effect = mpObject->GetEffectObject(0x2b216c7);
                if (effect) {
                    float intensity = (float)(1000 - mPathTimer.GetElapsedTime()) * 0.001f;
                    effect->SetParams(4, &intensity, 1);
                }
            }
        }
        if (mpObject->GetEffect(0x2def079))
            mpObject->StopEffect(0x2def079, 1);
    }

    // damage smoke by health
    cCombatant* combatant = &vehicle->mCombatant;
    float health = combatant->GetHealthPercentage();
    // 0: healthy, 1: damaged (light smoke), 2: critical (heavy smoke)
    int damageLevel = health >= 0.66f ? 0 : health >= 0.33f ? 1 : health >= 0.0f ? 2 : -1;
    if (damageLevel >= 0) {
        if (damageLevel != 1 && mpObject->GetEffect(0x49b925c))
            mpObject->StopEffect(0x49b925c, 0);
        if (damageLevel != 2) {
            if (mpObject->GetEffect(0x49b925d))
                mpObject->StopEffect(0x49b925d, 0);
            if (damageLevel == 1 && !mpObject->GetEffect(0x49b925c))
                mpObject->CreateEffect(0xfb03011e, 0, 0x49b925c);
        }
        if (damageLevel == 2 && !mpObject->GetEffect(0x49b925d))
            mpObject->CreateEffect(0xb44e37a2, 0, 0x49b925d);
    }

    mpObject->SetEffectActive(0x55ca6d6, 0x591d09c, combatant->IsStunned(), 0);
    uint32_t clingEffect = EA::Hash::FNV1_String8("SG_ufo_static_cling_stunned_vehicle", 0x811c9dc5, 1);
    mpObject->SetEffectActive(clingEffect, 0x5f8d750, combatant->IsStaticClingStunned(), 0);

    // civ tutorial: highlight the player's first vehicle
    if (gameMode == kGameCiv) {
        cCivModeStrategy* civ = CivModeStrategy();
        bool highlight = civ && civ->HasCivTutorialOccurred(0x64e6678) &&
                         !civ->HasCivTutorialOccurred(0x64e6679) && vehicle == civ->GetFirstVehicle(0);
        mpObject->SetEffectActive(0xc66a87f2, 0x6553e09, highlight, 0);
    }
}

}  // namespace SP
