// Slice s0105b960: space-mode tool strategies (DoToolAction/StartTool overrides), the place-object
// CanUseToolAtLocation placement check and the three tool-radius helpers.
// /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc: none of these bodies installs an EH frame).
// Out-of-line callees are only declared; their original addresses are in the trailing comments.
#include "types.h"

typedef unsigned int size_t;

// ---------------------------------------------------------------------------------------------
// small math types
// ---------------------------------------------------------------------------------------------
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
extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)
inline float Length(const Vector3& v)
{
    return (float)sqrt((double)(v.z * v.z + v.y * v.y + v.x * v.x));
}
inline float Distance(const Vector3& a, const Vector3& b)
{
    return Length(a - b);
}

struct Quaternion { float x, y, z, w; };
struct Matrix33 { float m[9]; };                 // 0x24 bytes

struct ResourceKey {
    uint32_t mInstanceID;                        // +0x00
    uint32_t mTypeID;                            // +0x04
    uint32_t mGroupID;                           // +0x08
};
inline bool KeyEquals(const ResourceKey& a, const ResourceKey& b)
{
    return a.mInstanceID == b.mInstanceID && a.mTypeID == b.mTypeID && a.mGroupID == b.mGroupID;
}

// Effect transform-update message (0x38 bytes; ctor @0x00434040, SetPos @0x00571d40).
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

// ---------------------------------------------------------------------------------------------
// data globals touched by this slice
// ---------------------------------------------------------------------------------------------
extern ResourceKey k_placeuberturret;            // 0x016e1db4 (zero-filled .bss key)
extern Vector3 g_upAxis;                         // 0x015b8db4 = (0, 0, 1)
extern float g_radius100;                        // 0x013ec4d0 = 100.0f
extern float g_radius10;                         // 0x01473c70 = 10.0f
extern float g_scale12;                          // 0x013f6b68 = 12.0f
extern float g_scale6;                           // 0x0147b9f0 = 6.0f
extern float g_scale15;                          // 0x014007f4 = 15.0f
extern float g_scale2p4;                         // 0x0149bfc4 = 2.4f
extern float g_one;                              // 0x01485720 = 1.0f
extern float g_ratio0p2;                         // 0x015b8ddc = 0.2f
extern float g_ratio0p5;                         // 0x015b8dd8 = 0.5f
extern Matrix33 g_effectRotation;                // 0x016e20d8 (effect frame, filled at start-up)
extern Vector3 g_effectPosition;                 // 0x016e20fc
extern char g_spaceMode;                         // 0x01654c05 (current-game-mode token)

// ---------------------------------------------------------------------------------------------
// engine singletons and free functions
// ---------------------------------------------------------------------------------------------
class cGameObject;
class cSpaceToolData;
class cSpaceShip;
class cLocatable;
class cGameNounManager;
class cSpaceGame;
class cPlanetModel;
class cAvatar;
class cEffectsManager;
class cEffectInstance;
class cEffectFactory;
class cApp;
class cConfigNode;
class cAudioSystem;
struct tShipListNode;

cGameNounManager* NounManager();                                     // 0x00b3d300
void* GetTriggerMgr();                                               // 0x00b3d4d0
void* GetCurrentGameMode();                                          // 0x00b5b800
cSpaceGame* SpaceGameGet();                                          // 0x01002bd0
cPlanetModel* PlanetModel();                                         // 0x00b3d350 (getter)
class cGameTerrainCursor* GetGameTerrainCursor();                     // 0x00b30d70
cEffectsManager* EffectsManagerPtr();                                 // 0x0067ddd0
class cUFOViewer* GetUFOSimulator();                                  // 0x00ffbe50
class cStarManager* StarManager();                                    // 0x00b3d2a0
uint32_t GetPlayerEmpireID();                                         // 0x01021090
cApp* App();                                                          // 0x0067dd10
cGameObject* GetPlayerEmpire();                                       // 0x01021300
// EA operator new (0x00f473a0): (size, name, flags, debugFlags, file, line)
void* __cdecl EAOperatorNew(size_t size, const char* name, int flags, int debugFlags, int file, int line);
inline void* operator new(size_t n, const char* name, int flags, int debugFlags, int file, int line)
{
    return EAOperatorNew(n, name, flags, debugFlags, file, line);
}
void FUN_00fdc340(const Vector3& position, float radius);             // 0x00fdc340
void FUN_010527f0(cSpaceToolData* pTool, uint32_t errorID, int show);  // 0x010527f0
void FUN_01058c90();                                                  // 0x01058c90 (marker callback)
class cSpaceCombatTuning* GetSpaceCombatTuning();                     // 0x01029940
int  FUN_00c70880(cSpaceToolData* pTool);                             // 0x00c70880
bool FUN_00c71540(cSpaceToolData* pTool);                             // 0x00c71540
void* FUN_00c37360();                                                 // 0x00c37360 (sim tuning block)
float FUN_01017030(int which);                                        // 0x01017030
float FUN_01017070(int which);                                        // 0x01017070

cGameObject* FUN_00ac9310(void** begin, const Vector3& position, bool);  // 0x00ac9310

bool FUN_0105a050(cSpaceToolData* pTool, const Vector3& position, int a3, int a4);  // 0x0105a050
void GetPropertyAsKeyInstance(void* propertyList, uint32_t key, void** out);  // 0x006a12a0
Matrix33& QuaternionToMatrix(Matrix33& out, const Quaternion& q);     // 0x004a9b40
void FUN_00435ed0(uint32_t soundID, void* context);                   // 0x00435ed0 (KillSetiEffects)
cAudioSystem* GetAudioSystem();                                       // 0x00a206f0
void FUN_00ff8560(void* impact, const Vector3& position, float health);  // 0x00ff8560
void FUN_0102b780(void* impact, const Vector3& position);             // 0x0102b780

// ---------------------------------------------------------------------------------------------
// simulator objects (only the members this slice touches)
// ---------------------------------------------------------------------------------------------
class cLocatable {                                // transform sub-object (embedded at +0x34 / +0x120)
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a();
    virtual const Vector3* GetPosition();                        // +0x2c
    virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15();
    virtual bool IsActive();                                     // +0x58
    virtual void v17(); virtual void v18(); virtual void v19(); virtual void v1a();
    virtual void v1b();
    virtual float GetRadius();                                   // +0x70
    virtual void v1d(); virtual void v1e(); virtual void v1f();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v2a(); virtual void v2b();
    virtual void v2c(); virtual void v2d();
    virtual cGameObject* Cast(uint32_t typeID);                  // +0xb8
};

class cGameObject {
public:
    virtual void AddRef();                                       // +0x00
    virtual void v01(); virtual void v02(); virtual void v03();
    virtual void Release();                                      // +0x04
    virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
    virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
    virtual void v10(); virtual void v11(); virtual void v12();
    virtual uint32_t GetPoliticalID();                           // +0x4c
    virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual void v18(); virtual void v19(); virtual void v1a(); virtual void v1b();
    virtual void v1c(); virtual void v1d(); virtual void v1e(); virtual void v1f();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v2a(); virtual void v2b();
    virtual void v2c(); virtual void v2d();
    virtual cGameObject* Cast(uint32_t typeID);                  // +0xb8
    uint32_t pad04[(0x34 - 0x04) / 4];                           // +0x04
    cLocatable mLocation;                                        // +0x34
    void FUN_00c389c0(int a, int b);                             // 0x00c389c0
};

class cSpaceToolData {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05();
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

class cPlanetModel {
public:
    bool FUN_00b7e3e0(const Vector3& position);                   // 0x00b7e3e0
    const Vector3* FUN_00b81630(Vector3* out, const Vector3& position);  // 0x00b81630
    Quaternion* BuildSurfaceOrientation(Quaternion* out, const Vector3& position);  // 0x00b7f190
};

class cSpaceShip {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
    virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
    virtual void v10(); virtual void v11(); virtual void v12();
    uint32_t pad04[(0x34 - 0x04) / 4];                            // +0x04
    cLocatable mLocation;                                         // +0x34 (vptr-only view of the sub-object)
    uint32_t pad48[(0x750 - 0x38) / 4];                           // +0x38
    Vector3 mDirection;                                           // +0x750
    float mPad75c;                                                // +0x75c
    float mPad760[2];                                             // +0x760
    float mRadius;                                                // +0x768
    float GetReach();                                             // 0x00c37120
};

class cSpaceCombatTuning {
public:
    float GetColonyObjectHealth();                                // 0x0102a7f0
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

class cAvatar {
public:
    void FUN_00ff88c0(const Vector3& position, cEffectInstance* effect);  // 0x00ff88c0
    void FUN_00ff6450(const Vector3& position);                    // 0x00ff6450
};

class cSpaceGame {
public:
    uint32_t pad00[(0x54 - 0x00) / 4];                             // +0x00 (space game has no vptr slot used)
    cAvatar* GetAvatar();                                          // 0x00b1fdb0 ([this+0x54])
};

// config/mode node reached through App() -> +0x50 -> +0x38
class cConfigNode {
public:
    virtual void v00(); virtual void v01(); virtual void v02();
    virtual cConfigNode* GetTag(uint32_t typeID);                   // +0x0c
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
    virtual void v0c(); virtual void v0d();
    virtual cConfigNode* GetSubNode();                              // +0x38
    virtual void v0f(); virtual void v10(); virtual void v11(); virtual void v12();
    virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16();
    virtual float GetFloat();                                       // +0x5c
};

class cApp {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
    virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual cConfigNode* GetModeHolder();                            // +0x50
};

class cAudioSystem {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void* GetState();                                        // +0x20
};

class cEffectInstance {
public:
    virtual void AddRef();                                           // +0x00
    virtual void Release();                                          // +0x04
    virtual void Enable(int flag);                                   // +0x08
    virtual void v03(); virtual void v04(); virtual void v05();
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
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a();
    virtual void CreateEffectAt(uint32_t effectID, const Vector3* position,
                                cEffectInstance** out);              // +0x2c
    virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14();
    virtual cEffectFactory* GetFactory(uint32_t effectID);           // +0x54
};

class cGameTerrainCursor {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
    virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual void v18(); virtual void v19(); virtual void v1a(); virtual void v1b();
    virtual void v1c(); virtual void v1d(); virtual void v1e(); virtual void v1f();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v2a(); virtual void v2b();
    virtual void v2c(); virtual void v2d(); virtual void v2e(); virtual void v2f();
    virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33();
    virtual void v34();
    virtual cGameObject* GetHoverObject();                           // +0xd4
};

// ---------------------------------------------------------------------------------------------
// the tool strategies
// ---------------------------------------------------------------------------------------------
class cSPToolStrategy {
public:
    virtual bool DoToolAction(cSpaceToolData* pTool, const Vector3& position, int a3, int a4);
    void StartTool(cSpaceToolData* pTool, const Vector3& position, int a3);          // 0x010568b0
    char OnHit(cSpaceToolData* pTool, const Vector3& position, int hitType, int);    // 0x010593e0
};

class cSPDefaultProjectileWeapon : public cSPToolStrategy {
public:
    virtual bool DoToolAction(cSpaceToolData* pTool, const Vector3& position, int a3, int a4);  // 0x0105b350
};

// ---------------------------------------------------------------------------------------------
// SimSingleton: AddMarker (0x00ae49d0) creates the navigation marker for a placed object.
// ---------------------------------------------------------------------------------------------
namespace Simulator {
class SimSingleton {
public:
    uint32_t pad00[0x18 / 4];                                    // +0x00
    uint32_t mPlayerEmpireID;                                    // +0x18
    uint32_t pad1c[(0xc8 - 0x1c) / 4];

    SimSingleton();                                              // 0x00ae5c30
    void* AddMarker(void* callback, int empireID, const Vector3* position, int kind,
                    uint32_t typeID, void* info, const Quaternion* orientation, int flag);  // 0x00ae49d0

    static SimSingleton* sInstance;                              // 0x0167a60c
    static __forceinline SimSingleton* Get()
    {
        if (!sInstance)
            sInstance = new ("Simulator/SimSingleton", 0, 0, 0, 0) SimSingleton();
        return sInstance;
    }
};
}
using Simulator::SimSingleton;

// ---------------------------------------------------------------------------------------------
// 0x0105b960 -- place the navigation marker for the placed object
// ---------------------------------------------------------------------------------------------
class cSPCityMarkerStrategy : public cSPDefaultProjectileWeapon {
public:
    virtual bool DoToolAction(cSpaceToolData* pTool, const Vector3& position, int a3, int a4);
};

// @ 0x0105b960
bool cSPCityMarkerStrategy::DoToolAction(cSpaceToolData* pTool, const Vector3& position, int a3, int a4)
{
    if (cSPDefaultProjectileWeapon::DoToolAction(pTool, position, a3, 0)) {
        FUN_00fdc340(position, g_radius100);
        SimSingleton::Get()->AddMarker((void*)&FUN_01058c90, (int)GetPlayerEmpireID(), &position,
                                       0, 0xfd701f6f, 0, 0, 0);
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------------------------
// 0x0105bc70 -- place-object DoToolAction: spawn the object and apply its health
// ---------------------------------------------------------------------------------------------
class cSPPlaceObjectStrategy : public cSPDefaultProjectileWeapon {
public:
    virtual bool DoToolAction(cSpaceToolData* pTool, const Vector3& position, int a3, int a4);
};

// @ 0x0105bc70
bool cSPPlaceObjectStrategy::DoToolAction(cSpaceToolData* pTool, const Vector3& position, int a3, int a4)
{
    if (cSPDefaultProjectileWeapon::DoToolAction(pTool, position, a3, 0)) {
        if (!KeyEquals(pTool->GetToolID(), k_placeuberturret)) {
            float health = GetSpaceCombatTuning()->GetColonyObjectHealth();
            FUN_00ff8560(pTool->CreateImpact(), position, health);
            return true;
        }
        FUN_0102b780(pTool->CreateImpact(), position);
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------------------------
// 0x0105ba00 -- place-object placement check against cities and nearby objects
// ---------------------------------------------------------------------------------------------
class cSpaceCity {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    uint32_t pad04[(0x120 - 0x04) / 4];                           // +0x04
    cLocatable mLocation;                                         // +0x120
};

class cSPPlaceObjectToolStrategy : public cSPPlaceObjectStrategy {
public:
    bool CanUseToolAction(cSpaceToolData* pTool, const Vector3& position, int a3);  // 0x01053980
    bool CanUseToolAtLocation(cSpaceToolData* pTool, const Vector3& position, int a3);
};

// @ 0x0105ba00
bool cSPPlaceObjectToolStrategy::CanUseToolAtLocation(cSpaceToolData* pTool, const Vector3& position,
                                                      int a3)
{
    if (!CanUseToolAction(pTool, position, a3))
        return false;
    cPlanetModel* model = PlanetModel();
    if (model && model->FUN_00b7e3e0(position)) {
        FUN_010527f0(pTool, 0xcebd3c75, a3);
        return false;
    }

    cGameObject* hover = GetGameTerrainCursor()->GetHoverObject();
    cGameObject* obj = hover ? hover->Cast(0x2450023) : 0;
    if (obj)
        obj->AddRef();

    cGameDataVector* cities = (cGameDataVector*)NounManager()->GetGameDataVector(
        (void*)0x00cd7d10, (void*)0x00d3d420, (void*)0x00acdff0, (void*)0x00b1e500,
        (void*)0x018c43e8);
    cGameObject** cityEnd = cities->mpEnd;
    for (cGameObject** it = cities->mpBegin; it != cityEnd; ++it) {
        cSpaceCity* city = (cSpaceCity*)*it;
        float dist = Distance(*city->mLocation.GetPosition(), *obj->mLocation.GetPosition());
        if (dist < obj->mLocation.GetRadius() + city->mLocation.GetRadius()) {
            FUN_010527f0(pTool, 0x9ad55101, a3);
            if (obj)
                obj->Release();
            return false;
        }
    }

    cGameDataVector* others = (cGameDataVector*)NounManager()->GetGameDataVector(
        (void*)0x00cd7d10, (void*)0x00d3d420, (void*)0x00dc3250, (void*)0x00b1e500,
        (void*)0x04e3fab5);
    cGameObject** otherEnd = others->mpEnd;
    for (cGameObject** it = others->mpBegin; it != otherEnd; ++it) {
        cGameObject* other = *it;
        float dist = Distance(*other->mLocation.GetPosition(), *obj->mLocation.GetPosition());
        if (dist < obj->mLocation.GetRadius() + g_radius10) {
            FUN_010527f0(pTool, 0x90ab2881, a3);
            if (obj)
                obj->Release();
            return false;
        }
    }

    if (obj)
        obj->Release();
    return true;
}

// ---------------------------------------------------------------------------------------------
// 0x0105bd00 -- artillery weapon: the hit handler is the whole action
// ---------------------------------------------------------------------------------------------
class cSPArtilleryWeaponStrategy : public cSPToolStrategy {
public:
    virtual bool DoToolAction(cSpaceToolData* pTool, const Vector3& position, int a3, int a4);
};

// @ 0x0105bd00
bool cSPArtilleryWeaponStrategy::DoToolAction(cSpaceToolData* pTool, const Vector3& position, int a3, int a4)
{
    return cSPToolStrategy::OnHit(pTool, position, a3, 0);
}

// ---------------------------------------------------------------------------------------------
// 0x0105bd20 -- mind-erase: remember the erased city's position and effect height
// ---------------------------------------------------------------------------------------------
struct tErasedCityRecord {                         // 0x14-byte element of the list at +0x2b8
    Vector3 mPosition;                             // +0x00
    float   mEffectHeight;                         // +0x0c
    uint32_t mPad10;                               // +0x10
};
struct tErasedCityList {
    tErasedCityRecord* mpBegin;                    // +0x00
    tErasedCityRecord* mpEnd;                      // +0x04
    tErasedCityRecord* mpCapacity;                 // +0x08
    void FUN_00bdf3e0();                           // 0x00bdf3e0 (append a default element)
};
class cErasedCityObject {
public:
    uint32_t pad00[0x2b8 / 4];
    tErasedCityList mRecords;                      // +0x2b8
};

class cSPMindEraseToolStrategy : public cSPToolStrategy {
public:
    virtual bool DoToolAction(cSpaceToolData* pTool, const Vector3& position, int a3, int a4);
};

// @ 0x0105bd20
bool cSPMindEraseToolStrategy::DoToolAction(cSpaceToolData* pTool, const Vector3& position, int a3, int a4)
{
    if (FUN_0105a050(pTool, position, a3, 0) && pTool->mpOwnerObject) {
        float height = pTool->FUN_0104bdb0();
        cGameDataVector* cities = (cGameDataVector*)NounManager()->GetGameDataVector(
            (void*)0x00cd7d10, (void*)0x00d3d420, (void*)0x00acdff0, (void*)0x00b1e500,
            (void*)0x018c43e8);
        cErasedCityObject* city =
            (cErasedCityObject*)FUN_00ac9310((void**)&cities->mpBegin, position, false);
        if (city) {
            city->mRecords.FUN_00bdf3e0();
            tErasedCityRecord* record = city->mRecords.mpEnd - 1;
            record->mPosition = position;
            city->mRecords.mpEnd[-1].mEffectHeight = height;
        }
    }
    return true;
}

// ---------------------------------------------------------------------------------------------
// 0x0105bf50 -- genesis device: kick the avatar's power
// ---------------------------------------------------------------------------------------------
class cSPGenesisDeviceToolStrategy : public cSPDefaultProjectileWeapon {
public:
    virtual bool DoToolAction(cSpaceToolData* pTool, const Vector3& position, int a3, int a4);
};

// @ 0x0105bf50
bool cSPGenesisDeviceToolStrategy::DoToolAction(cSpaceToolData* pTool, const Vector3& position, int a3, int a4)
{
    if (cSPDefaultProjectileWeapon::DoToolAction(pTool, position, a3, 0)) {
        cSpaceGame* game = SpaceGameGet();
        if (game && GetCurrentGameMode() == &g_spaceMode) {
            game->GetAvatar()->FUN_00ff6450(position);
            return true;
        }
        return false;
    }
    return false;
}

// ---------------------------------------------------------------------------------------------
// 0x0105bde0 -- crop circles: spawn the effect at the planet surface orientation
// ---------------------------------------------------------------------------------------------
class cCropCirclesToolStrategy : public cSPDefaultProjectileWeapon {
public:
    virtual bool DoToolAction(cSpaceToolData* pTool, const Vector3& position, int a3, int a4);
};

// @ 0x0105bde0
bool cCropCirclesToolStrategy::DoToolAction(cSpaceToolData* pTool, const Vector3& position, int a3, int a4)
{
    if (cSPDefaultProjectileWeapon::DoToolAction(pTool, position, a3, 0)) {
        cSpaceGame* game = SpaceGameGet();
        if (game && GetCurrentGameMode() == &g_spaceMode) {
            cEffectFactory* factory = EffectsManagerPtr()->GetFactory(0x3701a5c);
            void* key = 0;
            GetPropertyAsKeyInstance(pTool->mpToolProperties, 0x719f6876, &key);
            cEffectInstance* effect = 0;
            if (key && factory->CreateInstance(key, 0, &effect)) {
                XformMsg msg;
                msg.SetPos(position);
                Quaternion orientation;
                Matrix33 rot;
                msg.SetRot(QuaternionToMatrix(
                    rot, *PlanetModel()->BuildSurfaceOrientation(&orientation, position)));
                effect->SetXform(&msg);
                effect->Enable(0);
            }
            game->GetAvatar()->FUN_00ff88c0(position, effect);
            if (effect)
                effect->Release();
            return true;
        }
        return false;
    }
    return false;
}

// ---------------------------------------------------------------------------------------------
// 0x0105bfb0 -- rally call: silence every flagged empire's SETI effects, then post the rally fx
// ---------------------------------------------------------------------------------------------
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

// shared sub-node/tag lookup: both radius helpers fall back to one default value
static float TagFloat(cConfigNode* node, uint32_t tagID, const float& dflt)
{
    if (node) {
        cConfigNode* tag = node->GetTag(tagID);
        if (tag)
            return tag->GetFloat();
    }
    return dflt;
}

// ---------------------------------------------------------------------------------------------
// 0x0105c3d0 -- tool radius curve (modes 1/2 use the planet-editor trigger range)
// ---------------------------------------------------------------------------------------------
// @ 0x0105c3d0
void FUN_0105c3d0(Vector3* out, cSpaceToolData* pTool, float t)
{
    float radius;
    int mode = *(int*)((char*)GetTriggerMgr() + 0x2c);
    if (mode == 1 || mode == 2) {
        float editorScale = FUN_00c70880(pTool) == 1 ? g_scale12 : g_scale6;
        radius = (t + 1.0f) * editorScale;
    } else {
        float base = TagFloat(App()->GetModeHolder()->GetSubNode(), 0x303154cc, g_radius10);
        float* tuning = (float*)FUN_00c37360();
        float low = tuning[0x13c / 4];
        float probeA = FUN_01017030(1);
        const float& near = (low > probeA) ? low : probeA;
        float high = tuning[0x140 / 4];
        float probeB = FUN_01017070(1);
        const float& far = (probeB > high) ? probeB : high;
        float ratio = (base - near) / (far - near);
        float minScale = 0.0f;
        float maxScale = 1.0f;
        if (ratio < minScale)
            ratio = minScale;
        if (ratio > maxScale)
            ratio = maxScale;
        float mid = (tuning[0x138 / 4] - tuning[0x134 / 4]) * ratio + tuning[0x134 / 4];
        float scale;
        if (FUN_00c70880(pTool) == 1)
            scale = g_scale15;
        else if (FUN_00c71540(pTool))
            scale = g_scale2p4;
        else
            scale = g_scale6;
        radius = scale * mid;
    }
    out->z = g_upAxis.z * radius;
    out->y = g_upAxis.y * radius;
    out->x = g_upAxis.x * radius;
}

// ---------------------------------------------------------------------------------------------
// 0x0105c5d0 -- tool radius curve for the second tool family (offsets 0x15c..0x168)
// ---------------------------------------------------------------------------------------------
// @ 0x0105c5d0
void FUN_0105c5d0(Vector3* out, cSpaceToolData* pTool, float t)
{
    float radius;
    int mode = *(int*)((char*)GetTriggerMgr() + 0x2c);
    if (mode == 1 || mode == 2) {
        float base = TagFloat(App()->GetModeHolder()->GetSubNode(), 0x303154cc, g_one);
        float scaled = g_ratio0p2 * base;
        const float& limit = (g_ratio0p5 > scaled) ? scaled : g_ratio0p5;
        radius = (t + 1.0f) * limit;
    } else {
        float base = TagFloat(App()->GetModeHolder()->GetSubNode(), 0x303154cc, g_one);
        float* tuning = (float*)FUN_00c37360();
        float low = tuning[0x164 / 4];
        float probeA = FUN_01017030(2);
        const float& near = (low > probeA) ? low : probeA;
        float high = tuning[0x168 / 4];
        float probeB = FUN_01017070(2);
        const float& far = (probeB > high) ? probeB : high;
        float ratio = (base - near) / (far - near);
        float minScale = 0.0f;
        float maxScale = 1.0f;
        if (ratio < minScale)
            ratio = minScale;
        if (ratio > maxScale)
            ratio = maxScale;
        radius = (tuning[0x160 / 4] - tuning[0x15c / 4]) * ratio + tuning[0x15c / 4];
    }
    out->z = g_upAxis.z * radius;
    out->y = g_upAxis.y * radius;
    out->x = g_upAxis.x * radius;
}

// ---------------------------------------------------------------------------------------------
// 0x0105c7e0 -- grow a ship's bounding radius to cover a planet surface offset and rescale its
//               direction vector with it
// ---------------------------------------------------------------------------------------------
// @ 0x0105c7e0
void FUN_0105c7e0(cSpaceShip* ship, const Vector3& position, float extra)
{
    Vector3 surface;
    const Vector3* offset = PlanetModel()->FUN_00b81630(&surface, position);
    float radius = Length(*offset) + extra;
    float reach = ship->GetReach();
    if (radius > reach) {
        ship->mRadius = radius;
        reach = radius;
    }
    float inv = 1.0f / Length(ship->mDirection);
    Vector3 dir = ship->mDirection * inv;
    ship->mDirection.x = dir.x * reach;
    ship->mDirection.y = dir.y * reach;
    ship->mDirection.z = dir.z * reach;
}
