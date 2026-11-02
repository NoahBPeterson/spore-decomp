// src/game/SPGonzago/_at_01050000.cpp -- migrated from slice(s) s0105d790, s0105b960 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_01050000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cEmpire.h"
#include "SP/cGameNounManager.h"
#include "SP/cPlanetModel.h"
#include "SP/cStarManager.h"
#include "SP/cSpatialObject.h"
#include "SP/cStar.h"

// unnamed retail callees and globals (address in the comment)
extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)

// ---- items of slice s0105b960 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float a, float b, float c) : x(a), y(b), z(c) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
};
inline Vector3 operator*(const Vector3& v, float s)
{
    Vector3 r;
    r.x = v.x * s;
    r.y = v.y * s;
    r.z = v.z * s;
    return r;
}
inline Vector3 operator-(const Vector3& a, const Vector3& b)
{
    Vector3 r;
    r.x = a.x - b.x;
    r.y = a.y - b.y;
    r.z = a.z - b.z;
    return r;
}
struct Matrix33 { float m[9]; };                 // 0x24 bytes
struct ResourceKey {
    uint32_t mInstanceID;                        // +0x00
    uint32_t mTypeID;                            // +0x04
    uint32_t mGroupID;                           // +0x08
};
struct XformMsg {
    uint16_t  mFlags;                            // +0x00
    uint16_t  mCount;                            // +0x02
    Vector3   mPos;                              // +0x04
    float     mScale;                            // +0x10
    Matrix33  mMat;                              // +0x14
    XformMsg();
    void SetPos(const Vector3& v);               // 0x00571d40
    void SetRot(const Matrix33& r)               // inline in the original
    {
        mMat = r;
        mFlags |= 2;
        ++mCount;
    }
};
extern Matrix33 g_effectRotation;                // 0x016e20d8 (effect frame, filled at start-up)
extern Vector3 g_effectPosition;                 // 0x016e20fc
class cGameObject;
class cSpaceToolData;
class cLocatable;
class cGameNounManager;
class cEffectsManager;
class cEffectInstance;
class cEffectFactory;
class cAudioSystem;
struct tShipListNode;
cGameNounManager* NounManager();                                     // 0x00b3d300
cEffectsManager* EffectsManagerPtr();                                 // 0x0067ddd0
class cUFOViewer* GetUFOSimulator();                                  // 0x00ffbe50
class cStarManager* StarManager();                                    // 0x00b3d2a0
cGameObject* GetPlayerEmpire();                                       // 0x01021300
void FUN_00435ed0(uint32_t soundID, void* context);                   // 0x00435ed0 (KillSetiEffects)
cAudioSystem* GetAudioSystem();                                       // 0x00a206f0
class cLocatable {                                // transform sub-object (embedded at +0x34 / +0x120)
public:
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v0a();
    virtual const Vector3* GetPosition();                        // +0x2c
virtual void v0c();
virtual void v0d();
virtual void v0e();
virtual void v0f();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
    virtual bool IsActive();                                     // +0x58
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v1a();
    virtual void v1b();
    virtual float GetRadius();                                   // +0x70
virtual void v1d();
virtual void v1e();
virtual void v1f();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
virtual void v27();
virtual void v28();
virtual void v29();
virtual void v2a();
virtual void v2b();
virtual void v2c();
virtual void v2d();
    virtual cGameObject* Cast(uint32_t typeID);                  // +0xb8
};
class cGameObject {
public:
    virtual void AddRef();                                       // +0x00
virtual void v01();
virtual void v02();
virtual void v03();
    virtual void Release();                                      // +0x04
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v0a();
virtual void v0b();
virtual void v0c();
virtual void v0d();
virtual void v0e();
virtual void v0f();
virtual void v10();
virtual void v11();
virtual void v12();
    virtual uint32_t GetPoliticalID();                           // +0x4c
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v1a();
virtual void v1b();
virtual void v1c();
virtual void v1d();
virtual void v1e();
virtual void v1f();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
virtual void v27();
virtual void v28();
virtual void v29();
virtual void v2a();
virtual void v2b();
virtual void v2c();
virtual void v2d();
    virtual cGameObject* Cast(uint32_t typeID);                  // +0xb8
    uint32_t pad04[(0x34 - 0x04) / 4];                           // +0x04
    cLocatable mLocation;                                        // +0x34
    void FUN_00c389c0(int a, int b);                             // 0x00c389c0
};
class cSpaceToolData {
public:
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
    virtual const ResourceKey& GetToolID();                      // +0x18
    virtual void* CreateImpact();                                 // +0x1c (no stack args)
    uint32_t pad20[(0x30 - 0x04) / 4];                            // +0x04
    void* mpToolProperties;                                      // +0x30 (property list)
    uint32_t pad34[(0x114 - 0x34) / 4];                           // +0x34
    cLocatable* mpToolOwner;                                     // +0x114 (owner transform)
    uint32_t pad118[(0x124 - 0x118) / 4];                         // +0x118
    cGameObject* mpOwnerObject;                                  // +0x124
    uint32_t pad128[(0x170 - 0x128) / 4];                         // +0x128
    uint32_t mLastErrorID;                                       // +0x170
    float FUN_0104bdb0();                                        // 0x0104bdb0 (first scalar, ecx = this)
};
class cGameNounManager {
public:
    void* GetGameDataVector(void* fn1, void* fn2, void* fn3, void* fn4, void* key);  // 0x00b21340
};
class cGameDataVector {
public:
    void* mpAllocator;                                            // +0x00
    cGameObject** mpBegin;                                        // +0x04
    cGameObject** mpEnd;                                          // +0x08
};
class cStarManager {
public:
    class cEmpire* GetEmpireByID(uint32_t empireID);               // 0x00ba9370
};
class cEmpire {
public:
    uint32_t pad00[(0x58 - 0x00) / 4];
    int mType;                                                     // +0x58
};
struct tShipListNode {                                             // intrusive list node
    tShipListNode* mpNext;                                         // +0x00
    tShipListNode* mpPrev;                                         // +0x04
    uint32_t mEmpireID;                                            // +0x08
};
class cUFOViewer {
public:
    tShipListNode* GetVehicleList();                                // 0x0108db30
};
class cAudioSystem {
public:
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
    virtual void* GetState();                                        // +0x20
};
class cEffectInstance {
public:
    virtual void AddRef();                                           // +0x00
    virtual void Release();                                          // +0x04
    virtual void Enable(int flag);                                   // +0x08
virtual void v03();
virtual void v04();
virtual void v05();
    virtual void SetXform(const XformMsg* msg);                      // +0x18
};
class cEffectFactory {
public:
    virtual void v00();
    virtual void v01();
    virtual bool CreateInstance(void* key, int unused, cEffectInstance** out);  // +0x08
};
class cEffectsManager {
public:
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v0a();
    virtual void CreateEffectAt(uint32_t effectID, const Vector3* position,
                                cEffectInstance** out);              // +0x2c
virtual void v0c();
virtual void v0d();
virtual void v0e();
virtual void v0f();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
    virtual void v14();
    virtual cEffectFactory* GetFactory(uint32_t effectID);           // +0x54
};
class cSPToolStrategy {
public:
    virtual bool DoToolAction(cSpaceToolData* pTool, const Vector3& position, int a3, int a4);
    void StartTool(cSpaceToolData* pTool, const Vector3& position, int a3);          // 0x010568b0
    char OnHit(cSpaceToolData* pTool, const Vector3& position, int hitType, int);    // 0x010593e0
};
class cSPRallyCallToolStrategy : public cSPToolStrategy {
public:
    void StartTool(cSpaceToolData* pTool, const Vector3& position, int a3);
};
static bool ListContains(tShipListNode* list, uint32_t empireID)
{
    for (tShipListNode* node = list->mpNext; node != list; node = node->mpNext) {
        if (node->mEmpireID == empireID)
            return true;
    }
    return false;
}
// ---- items of slice s0105b960 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern Matrix33 g_effectRotation;                // 0x016e20d8 (effect frame, filled at start-up)
extern Vector3 g_effectPosition;                 // 0x016e20fc

// ---- items of slice s0105d790 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double __cdecl fabs(double);
extern "C" double __cdecl sin(double);
extern "C" double __cdecl cos(double);
#pragma pack(push, 8)
#pragma intrinsic(sqrt, fabs, sin, cos)
inline float sqrtf(float x) { return (float)sqrt((double)x); }
inline float fabsf(float x) { return (float)fabs((double)x); }
inline float sinf(float x) { return (float)sin((double)x); }
inline float cosf(float x) { return (float)cos((double)x); }
struct Vector3_s0105_d790 {
    float x, y, z;
    Vector3_s0105_d790() {}
    Vector3_s0105_d790(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3_s0105_d790(const Vector3_s0105_d790& v) : x(v.x), y(v.y), z(v.z) {}
    Vector3_s0105_d790& operator=(const Vector3_s0105_d790& v) { x = v.x; y = v.y; z = v.z; return *this; }
    Vector3_s0105_d790 operator+(const Vector3_s0105_d790& b) const { return Vector3_s0105_d790(x + b.x, y + b.y, z + b.z); }
    Vector3_s0105_d790 operator-(const Vector3_s0105_d790& b) const { return Vector3_s0105_d790(x - b.x, y - b.y, z - b.z); }
    Vector3_s0105_d790 operator*(float f) const { return Vector3_s0105_d790(x * f, y * f, z * f); }
    float Dot(const Vector3_s0105_d790& b) const { return x * b.x + y * b.y + z * b.z; }
    float Length() const { return sqrtf(x * x + y * y + z * z); }
    Vector3_s0105_d790 Normalized() const { float inv = 1.0f / sqrtf(x * x + y * y + z * z); return Vector3_s0105_d790(x * inv, y * inv, z * inv); }
};
namespace SP {
struct cBoundingBox {
    Vector3_s0105_d790 mMin;
    Vector3_s0105_d790 mMax;
};
}
namespace SP {
struct Matrix3 {
    float m[9];
    void Assign(const float* pSource);              // 0x0041cb40 (ret 4)
};
}
namespace SP {
struct cSPTransform {
    uint32_t mFlags;                    // +0x00
    Vector3_s0105_d790  mTranslation;              // +0x04
    float    mScale;                    // +0x10
    Matrix3  mMatrix;                   // +0x14
    void Invert();                      // 0x0040efa0
};
}
namespace SP {
class cSpatialObject_s0105_d790 {
public:
virtual void _v00();
virtual void _v04();
virtual void _v08();
virtual void _v0c();
virtual void _v10();
virtual void _v14();
virtual void _v18();
virtual void _v1c();
virtual void _v20();
virtual void _v24();
virtual void _v28();
    virtual const Vector3_s0105_d790* GetAnchor();                              // +0x2c
virtual void _v30();
virtual void _v34();
virtual void _v38();
virtual void _v3c();
virtual void _v40();
virtual void _v44();
virtual void _v48();
virtual void _v4c();
virtual void _v50();
virtual void _v54();
virtual void _v58();
virtual void _v5c();
virtual void _v60();
virtual void _v64();
    virtual const cBoundingBox* GetBoundingBox();                    // +0x68
    void LocalToWorldTransform(cSPTransform* pOut);                  // 0x00c897e0
};
}
namespace SP {
struct cSteered {
    uint32_t   pad00[0x34 / 4];
    cSpatialObject_s0105_d790 mSpatial;                // +0x34
    uint32_t   pad38[(0x718 - 0x38) / 4];
    Vector3_s0105_d790    mPos;                        // +0x718
    Vector3_s0105_d790    mVel;                        // +0x724
    float      mQuat[4];                    // +0x730
    Vector3_s0105_d790    mUp;                         // +0x740
    uint8_t    pad74c[3];
    uint8_t    mbAimValid;                  // +0x74c
    float GetRadius();                      // 0x00c3be10
    void SetUp(const Vector3_s0105_d790* pUp);         // 0x00c381e0
};
}
namespace SP {
struct Quaternion { float x, y, z, w; };
}
namespace SP {
Quaternion* QuaternionFromFacingAndUp(Quaternion* pOut, const Vector3_s0105_d790* pFacing,
                                      const Vector3_s0105_d790* pUp);                     // 0x0069b600
}
namespace SP {
Vector3_s0105_d790* FUN_0059aed0(const Vector3_s0105_d790* pAxis, const Vector3_s0105_d790* pPos, Vector3_s0105_d790* pOut); // 0x0059aed0
}
namespace SP {
void* FUN_01021230();                                                          // 0x01021230
}
namespace SP {
struct cStar_s0105_d790 { int GetType(); };                                               // 0x00c8b550
}
namespace SP {
class cSubsystem {
public:
virtual void _v00();
virtual void _v04();
virtual void _v08();
    virtual void* FindProperty(uint32_t id);                                   // +0x0c
};
}
namespace SP {
class cAppFeature {
public:
virtual void _v00();
virtual void _v04();
virtual void _v08();
virtual void _v0c();
virtual void _v10();
virtual void _v14();
virtual void _v18();
virtual void _v1c();
virtual void _v20();
virtual void _v24();
virtual void _v28();
virtual void _v2c();
virtual void _v30();
virtual void _v34();
    virtual cSubsystem* GetSubsystem();                                        // +0x38
};
}
namespace SP {
class cApp {
public:
virtual void _v00();
virtual void _v04();
virtual void _v08();
virtual void _v0c();
virtual void _v10();
virtual void _v14();
virtual void _v18();
virtual void _v1c();
virtual void _v20();
virtual void _v24();
virtual void _v28();
virtual void _v2c();
virtual void _v30();
virtual void _v34();
virtual void _v38();
virtual void _v3c();
virtual void _v40();
virtual void _v44();
virtual void _v48();
virtual void _v4c();
    virtual cAppFeature* GetFeature();                                         // +0x50
};
}
namespace SP {
cApp* App();                                                                   // 0x0067dd10
}
namespace SP {
struct cPropertyValue {
    uint32_t pad00[0xbc / 4];
    float    mfValue;                                                          // +0xbc
};
}
namespace SP {
struct cBodyRef {
    uint32_t pad00[0x14 / 4];
    char*    mpBody;                                                           // +0x14
};
}
namespace SP {
extern const Vector3_s0105_d790 kAxis;              // 0x015b8da8  (fallback position)
}
namespace SP {
extern const Vector3_s0105_d790 kUnit;              // 0x015b8db4  (reference unit vector)
}
namespace SP {
extern const float kSpinMin;             // 0x015b8dfc
}
namespace SP {
extern const float kSpinMax;             // 0x015b8e00
}
namespace SP {
extern const float kUpBlend;             // 0x015b8e04
}
namespace SP {
extern const float kFalloff;             // 0x015b8e08
}
namespace SP {
extern const float kCapMax;              // 0x015b8e0c
}
namespace SP {
extern const float kCapMin;              // 0x015b8e10
}
namespace SP {
extern const float kMagnitudeScale;      // 0x013f9428
}
namespace SP {
extern const float kHalf;                // 0x01471064
}
namespace SP {
extern const float kNegOne;              // 0x013eb1bc
}
namespace SP {
extern const float kMinLength;           // 0x0149bfc0 = 1.5258789e-05
}
// ---- items of slice s0105d790 end

// @ 0x0105bfb0
void cSPRallyCallToolStrategy::StartTool(cSpaceToolData* pTool, const Vector3& position, int a3)
{
    cSPToolStrategy::StartTool(pTool, position, a3);

    if (pTool->mpToolOwner) {
        cGameObject* owner = pTool->mpToolOwner->Cast(0xb033b403);
        if (owner)
            owner->FUN_00c389c0(3, 1);
    }

    tShipListNode* vehicles = GetUFOSimulator()->GetVehicleList();
    cGameDataVector* ships = (cGameDataVector*)NounManager()->GetGameDataVector(
        (void*)0x00cd7d10, (void*)0x00d3d420, (void*)0x00ad48b0, (void*)0x00b1e500,
        (void*)0x018ebadc);
    int shipCount = (int)(ships->mpEnd - ships->mpBegin);
    for (int i = 0; i < shipCount; ++i) {
        cGameObject* ship = ships->mpBegin[i];
        if ((ship ? &ship->mLocation : 0) == pTool->mpToolOwner)
            continue;
        uint32_t empireID = ship->GetPoliticalID();
        if (!ListContains(vehicles, empireID))
            continue;
        ship->FUN_00c389c0(3, 1);
        cEmpire* empire = StarManager()->GetEmpireByID(ship->GetPoliticalID());
        if (!empire)
            continue;
        uint32_t soundID = 0;
        switch (empire->mType) {
        case 0: soundID = 0xa52e7c0f; break;
        case 1: soundID = 0x443798e6; break;
        case 2: soundID = 0x74ceeaf7; break;
        case 3: soundID = 0x7ea8ae64; break;
        case 4: soundID = 0x5ab8c85e; break;
        case 5: soundID = 0x30ae8cc7; break;
        case 6: soundID = 0x45bcbe0e; break;
        case 7: soundID = 0x15032a5e; break;
        case 8: soundID = 0xd11144c7; break;
        default:
            if (GetPlayerEmpire() == (cGameObject*)empire)  // empire object identity
                soundID = 0x21e00685;
            break;
        }
        cAudioSystem* audio = GetAudioSystem();
        FUN_00435ed0(soundID, audio ? audio->GetState() : 0);
    }

    cGameDataVector* markers = (cGameDataVector*)NounManager()->GetGameDataVector(
        (void*)0x00cd7d10, (void*)0x00d3d420, (void*)0x00b5fa10, (void*)0x00b1e500,
        (void*)0x0436f342);
    int markerCount = (int)(markers->mpEnd - markers->mpBegin);
    for (int i = 0; i < markerCount; ++i) {
        cGameObject* marker = markers->mpBegin[i];
        if (!marker->mLocation.IsActive() && !ListContains(vehicles, marker->GetPoliticalID()))
            continue;

        cEffectInstance* effect = 0;
        cEffectsManager* manager = EffectsManagerPtr();
        if (effect) {
            effect = 0;
            effect->Release();
        }
        manager->CreateEffectAt(0x20316487, 0, &effect);
        if (!effect)
            continue;

        XformMsg msg;
        msg.mFlags = 0;
        msg.mCount = 0;
        msg.mPos = g_effectPosition;
        msg.mScale = 1.0f;
        msg.mMat = g_effectRotation;
        msg.SetPos(*marker->mLocation.GetPosition());
        effect->SetXform(&msg);
        effect->Enable(0);
        effect->Release();
    }
}

// @ 0x0105e290
namespace SP {
void __stdcall FUN_0105e290(void* pWrapper, int nMagnitude)
{
    float mag = (float)(uint32_t)nMagnitude;
    float scaled = mag * kMagnitudeScale;

    cBodyRef* pRef = (cBodyRef*)pWrapper;
    char* pBody = pRef->mpBody;
    cSteered* p = pBody ? (cSteered*)(pBody - 0x34) : 0;

    cAppFeature* pFeature = App()->GetFeature();
    cSubsystem* pSub = pFeature->GetSubsystem();
    if (!pSub)
        return;
    cPropertyValue* pProp = (cPropertyValue*)pSub->FindProperty(0x303154cc);
    if (!pProp)
        return;
    float cap = pProp->mfValue;

    Vector3_s0105_d790& pos = p->mPos;
    float norm = sqrtf(pos.x * pos.x + pos.y * pos.y + pos.z * pos.z);
    if (norm < kMinLength)
        pos = kAxis;

    float invCap = 1.0f / kCapMax;
    float blend = ((kCapMax - kCapMin) * cap + kCapMin) - norm;
    float f1 = scaled / ((fabsf(blend) * invCap) * kFalloff);
    float c1 = (1.0f <= f1) ? 1.0f : f1;
    float newDist = blend * c1 + norm;

    float inv = 1.0f / sqrtf(pos.x * pos.x + pos.y * pos.y + pos.z * pos.z + 1e-8f);
    pos.x = pos.x * inv * newDist;
    pos.y = pos.y * inv * newDist;
    pos.z = pos.z * inv * newDist;

    float f2 = invCap * newDist;
    float c2 = (1.0f <= f2) ? 1.0f : f2;

    Vector3_s0105_d790 up = p->mUp;
    float t = kUpBlend * c2;
    Vector3_s0105_d790 newUp((kUnit.x * t - up.x) * c1 + up.x,
                  (kUnit.y * t - up.y) * c1 + up.y,
                  (kUnit.z * t - up.z) * c1 + up.z);
    p->SetUp(&newUp);

    float sign = (((cStar_s0105_d790*)FUN_01021230())->GetType() == 3) ? kNegOne : 1.0f;
    float angle = (((1.0f - c2) * (kSpinMin * kSpinMax - kSpinMax) + kSpinMax) * mag * sign) * kHalf;

    float s = sinf(angle);
    float c = cosf(angle);
    Vector3_s0105_d790 axisRot(s * kUnit.x, s * kUnit.y, s * kUnit.z);

    Vector3_s0105_d790 outPos;
    pos = *FUN_0059aed0(&axisRot, &pos, &outPos);
    (void)c;

    const Vector3_s0105_d790& pp = p->mPos;
    float cx = pp.y * kUnit.z - pp.z * kUnit.y;
    float cy = pp.z * kUnit.x - pp.x * kUnit.z;
    float cz = pp.x * kUnit.y - pp.y * kUnit.x;
    float invCross = 1.0f / sqrtf(cx * cx + cy * cy + cz * cz);
    Vector3_s0105_d790 facing(invCross * cx * sign, invCross * cy * sign, invCross * cz * sign);

    Quaternion q;
    QuaternionFromFacingAndUp(&q, &facing, &kUnit);
    p->mQuat[0] = q.x;
    p->mQuat[1] = q.y;
    p->mQuat[2] = q.z;
    p->mQuat[3] = q.w;
    p->mbAimValid = 1;
}
}  // namespace SP
