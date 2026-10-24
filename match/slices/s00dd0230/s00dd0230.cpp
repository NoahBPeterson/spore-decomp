// Slice s00dd0230 -- SporeApp.exe 0x00dd0230..0x00dd1250.
//
//  Mix of modules (contiguous in the image, several TUs):
//   00dd0230  SP::VehicleTree::AttackCityOrder_Activate (SPGonzago)
//   00dd0380  SP::cMilitaryAttackCityOrder::OnTick
//   00dd0550..00dd06a0  small cMilitaryAttackCityOrder helpers
//   00dd0710..00dd1250  UI::AssetDiscovery_Data / TimelineSporepediaCardData (Spui)
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"
#include <math.h>
#include <new>

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4

// ---------------------------------------------------------------------------------------------------
// Shared tiny types
// ---------------------------------------------------------------------------------------------------

struct cSPVector3 {
    float x, y, z;
    cSPVector3() {}
    cSPVector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    cSPVector3(const cSPVector3& v) { x = v.x; y = v.y; z = v.z; }
};

void* operator new(unsigned size, const char* name, int a, int b, int c, int d);   // 0x00f473a0
void operator delete[](void* p);                                                   // 0x00f47380

// IRefCount-shaped interface: slot 0 = AddRef, slot 1 = Release.
struct IRefCounted {
    virtual void AddRef();                     // +0x00
    virtual void Release();                    // +0x04
};

// ---------------------------------------------------------------------------------------------------
// SP spatial object family
// ---------------------------------------------------------------------------------------------------

class cSpatialObject : public IRefCounted {
public:
    virtual void* v08();                                // +0x08 (slot 2)
    virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28();
    virtual const cSPVector3& GetPosition();            // +0x2c (slot 11)
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual bool v50();                                 // +0x50 (slot 20)
    virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74();
    virtual void v78(); virtual void v7c(); virtual void v80(); virtual void v84();
    virtual void v88(); virtual void v8c(); virtual void v90(); virtual void v94();
    virtual void v98(); virtual void v9c(); virtual void va0(); virtual void va4();
    virtual void va8(); virtual void vac(); virtual void vb0(); virtual void vb4();
    virtual void* Cast();                               // +0xb8 (slot 46)
    virtual void vb8();                                 // +0xbc (slot 47)
    virtual void vc0();                                 // +0xc0 (slot 48)
    cSpatialObject* CastObject();                       // +0xb8 (typed form)
};

class cLocomotive : public cSpatialObject {
public:
    virtual void vbc(); virtual void vc0(); virtual void vc4();
    virtual void MoveTo(const cSPVector3& dst, float a, float b, bool rel);   // +0xe0
    virtual void MoveAround(const cSPVector3& c, float r);                    // +0xe4
    virtual void MoveTowards(const cSPVector3& dst);                          // +0xe8
};

class cCombatant : public IRefCounted {
public:
    virtual void v08(); virtual void v0c(); virtual void v10();
    virtual float GetRadius();                          // +0x14
    virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34();
    virtual void v38(); virtual void v3c(); virtual void v40(); virtual void v44();
    virtual void v48(); virtual void v4c();
    virtual void v50(void* pTarget);                    // +0x50 (slot 20)
    float GetStat();                                    // 0x00bfc400 (thiscall)
};

// SP::cCity: +0x2c = bIsSomething, +0x4c = GetOwnerId, +0x44c owner pointer.
class cCity : public IRefCounted {
public:
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28();
    virtual bool v2c();                                 // vtable +0x2c (slot 11)
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48();
    virtual uint32_t v4c();                             // vtable +0x4c (slot 19)
    char pad04[0x120 - 4];
    struct cCityDisplay {                               // embedded object at +0x120
        char pad00[0x50];
        uint32_t mFlags;                                // +0x50 (absolute +0x170)
    } mDisplay;                                         // +0x120
    char pad174[0x44c - 0x174];
    void* mpSomething_44c;                              // +0x44c
    cCity* GetCivilization();                           // 0x00bd9bf0
};

class cVehicle {
public:
    char pad00[0x34];
    cLocomotive mLoco;                                  // +0x34
    char padLoco[0x508 - 0x34 - sizeof(cLocomotive)];
    cCombatant mCombatant;                              // +0x508
    char padCombat[0xb1c - 0x508 - sizeof(cCombatant)];
    uint32_t mLocomotion;                               // +0xb1c
    char padB20[0xb7c - 0xb1c - 4];
    cSpatialObject* mpChaseTargetRef;                   // +0xb7c

    void* GetTreeData();                                // 0x00ca71d0 (thiscall)
    void Log(const char* msg);                          // 0x00ca7250 (thiscall)
    void Flush();                                       // 0x00caa900 (thiscall)
    void SetTarget(void* pTarget);                      // 0x00dc4d00 (thiscall, ret 4)
};

// ---------------------------------------------------------------------------------------------------
// Vehicle tree / group order
// ---------------------------------------------------------------------------------------------------

void __cdecl Vehicle_ClearOrder(cVehicle* pVehicle);             // 0x00dcc610
bool __cdecl IsValidFireTarget(cCombatant* pCombatant, cSpatialObject* pTarget);   // 0x00dc4e20

// SP::cVehicleGroupOrder: vtable slot 3 = FindOrderByType; data members at +0x50/+0x54.
class cVehicleGroupOrder : public IRefCounted {
public:
    virtual void v08();
    virtual void* FindOrderByType(uint32_t type);       // vtable +0x0c (slot 3)
    char pad04[0x50 - 4];
    cVehicle** mVehiclesBegin;                          // +0x50
    cVehicle** mVehiclesEnd;                            // +0x54
};

class cVehicleTicker {
public:
    cVehicleTicker();                                   // 0x00dc7d70
    cVehicleGroupOrder* GetGroupOrder(void* pData);      // 0x00dcd430
    char pad00[0x58];                                   // sizeof == 0x58
};
cVehicleTicker* gVehicleTicker;                          // 0x01699ab8

// SP::cMilitaryAttackCityOrder (retail: mpCity +0x94, mAttackerId +0x98, mode +0x84).
class cMilitaryAttackCityOrder : public cVehicleGroupOrder {
public:
    char pad58[0x80 - 0x58];
    uint32_t mBanner_80;                                // +0x80
    uint32_t mMode;                                     // +0x84 (1..5 selector)
    uint32_t mBanner_88;                                // +0x88
    uint32_t mField_8c;                                 // +0x8c
    float mStatScale;                                   // +0x90
    cCity* mpCity;                                      // +0x94
    uint32_t mAttackerId;                               // +0x98
    char pad9c[0xac - 0x9c];

    cSpatialObject* GetCurrentTarget(cVehicle* pVehicle);        // 0x00dcfc90
    uint32_t GetCityBannerId();                                  // 0x00dd0550
    void* QueryInterface(uint32_t type);                         // 0x00dd0590
    bool IsInSimulatorContext();                                 // 0x00dd05e0
    bool IsActive();                                             // 0x00dd0600
    void* QueryInterface2(uint32_t type);                        // 0x00dd0610
    uint32_t GetIconKey();                                       // 0x00dd0650
    uint32_t GetPaletteItemPriority();                           // 0x00641770
    uint32_t GetMissionKey();                                    // 0x00dd06a0
    void SetupOrder(cVehicle* pVehicle);                         // 0x00dc8c00 (thiscall, ret 4)
    void ResetOrder(cVehicle* pVehicle);                         // 0x00dcc350 (thiscall, ret 4)
    bool OnTick(float dt);                                       // 0x00dd0380 (override, slot 20)
};

struct StarManagerObj;
struct EmpiresObj;
struct StarManagerObj {
    uint32_t GetBannerId(uint32_t id);                   // 0x00ba6dc0 (thiscall)
    EmpiresObj* GetEmpireByID(uint32_t id);              // 0x00ba9370 (thiscall, ret 4)
};
struct EmpiresObj {
    void* GetCities();                                   // 0x005c65e0 (thiscall)
};
struct CivNameSource {
    const wchar_t* mpName;                               // +0x00
};
// A three-dword resource key (scene/stat descriptor).
struct SceneKey {
    uint32_t mTag;                                       // +0x00
    uint32_t mId;                                        // +0x04
    uint32_t mFlags;                                     // +0x08
};
StarManagerObj* __cdecl StarManager();                   // 0x00b3d2a0
int __cdecl GetUniverseContext();                                    // 0x1021080
uint32_t __cdecl GetPaletteItemPriority();                          // 0x00641770
bool __cdecl FUN_00b6e250();                                         // 0x00b6e250
uint32_t __cdecl FUN_00b6f0d0(uint32_t id);                          // 0x00b6f0d0
void* __cdecl NounManager();                                         // 0x00b3d300
struct GameNounManagerObj {
    void* GetPlayerCivilization();                                   // 0x00b25fb0 (thiscall)
};
struct CivModeStrategyObj {
    bool IsValid();                                                  // 0x00cf7a90 (thiscall)
};
CivModeStrategyObj* __cdecl CivModeStrategy();                       // 0x00cf74c0
float __cdecl Combatant_GetStat(cCombatant* pCombatant);             // 0x00bfc400

// ---------------------------------------------------------------------------------------------------
// UI::AssetDiscovery_Data / TimelineSporepediaCardData (Spui module)
// ---------------------------------------------------------------------------------------------------

struct cString_s006b_47a0 {                             // SP::cString, retail 0x14 bytes
    uint32_t d[5];
    cString_s006b_47a0();                               // 0x006b5060
    ~cString_s006b_47a0();                              // 0x006b5240
    void Construct() { CtorImpl(); }                    // 0x006b5060 (thiscall, named wrapper)
    void CtorImpl();                                    // 0x006b5060
    void Load(uint32_t table, uint32_t id, int flag, const wchar_t* name);  // 0x006b54b0
    const wchar_t* GetText();                           // 0x006b55c0
};

// The UI data payload: pScenario->mpPayload->mpInner (fields read at 0xdd0710).
struct UI_ScenarioInner {
    uint32_t mField00;                                  // +0x00
    uint32_t mField04;                                  // +0x04
    uint32_t mField08;                                  // +0x08
    uint32_t mField0c;                                  // +0x0c
    uint32_t mField10;                                  // +0x10
    uint32_t mField14;                                  // +0x14
    uint32_t mField18;                                  // +0x18
    uint32_t mField1c;                                  // +0x1c
    uint32_t mField20;                                  // +0x20
    void*    mpField24;                                // +0x24
    uint32_t mField28;                                  // +0x28
    float    mField2c;                                  // +0x2c
};

struct UI_ScenarioPayload {
    char pad00[0x0c];
    UI_ScenarioInner* mpInner;                          // +0x0c
};

struct UI_ScenarioDataSrc {
    char pad00[0x0c];
    UI_ScenarioPayload* mpPayload;                      // +0x0c
};

// EASTL helpers used by the UI code.
struct eastl_wstring {
    wchar_t* mpBegin;                                   // +0x00
    wchar_t* mpEnd;                                     // +0x04
    void*    mpCapacity;                                // +0x08
    void Append(const wchar_t* pText);                  // 0x005c3d90
    void Assign(const wchar_t* first, const wchar_t* last);   // 0x00423650
    void DeallocateSelf();                              // 0x00933960
};
void __cdecl WString_FromCStr(eastl_wstring* pOut, const wchar_t* pText);   // 0x0041df50 (ret 8)

struct eastl_u32vec {
    uint32_t* mpBegin;                                  // +0x00
    uint32_t* mpEnd;                                    // +0x04
    uint32_t* mpCapacity;                               // +0x08
    void DoInsertValue(uint32_t* pos, const uint32_t& value);   // 0x004558a0
    void push_back(uint32_t v)
    {
        if (mpEnd < mpCapacity) {
            uint32_t* p = mpEnd++;
            if (p != 0)
                *p = v;
        } else {
            DoInsertValue(mpEnd, v);
        }
    }
};

// Interface stubs for the vtable call sites in the slice.
struct IPropertyHandle {
    virtual void AddRef();                              // +0x00
    virtual void Release();                             // +0x04
};

struct IPropertyManager {
    PV8 PV4
    virtual void GetProperty(uint32_t key, void** ppOut);     // +0x30 (slot 12)
};

struct IResourceManager {
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual bool LoadKey(const void* pKey, int a, int b, int c, int d, int e);   // +0x0c (slot 3)
};

// The object at 0x15fd8f8 exposes slot 8 (+0x20) returning an asset ref, then its slot 12.
struct IMgr67de40 {
    PV8 PV8
    virtual IPropertyHandle* v20();                     // +0x20 (slot 8)
};
struct IHaveProp12 {
    PV8 PV4
    virtual void GetPropertyAt12(void* a, void* b, int c);   // +0x30 (slot 12)
};

void* __cdecl Mgr67de40();                              // 0x0067de40
void* __cdecl ResourceManager();                        // 0x0067dcd0
void* __cdecl PropertyManager();                        // 0x0067de30
void* __cdecl GetPropertyAsKey(void* pHandle, uint32_t key, void* pOut);   // 0x006a1250
void* __cdecl GetMessageServer67dcc0();                 // 0x0067dcc0 (SP::MessageServer)

// AssetDiscovery_Data's asset-holding back end.
void* __fastcall FUN_00b8d8e0(void* p);                        // 0x00b8d8e0 (ecx=this)
void* __cdecl FUN_00b8d8f0(void* p);                        // 0x00b8d8f0
void* __fastcall FUN_00b8de30(void* p);                        // 0x00b8de30 (ecx=p)
void* __fastcall FUN_00bb9de0(void* p);                        // 0x00bb9de0 (ecx=p)
void* __cdecl FUN_00bb9ae0(void* p);                        // 0x00bb9ae0
void* __cdecl StarManager_GetEmpireByID(void* pStar, uint32_t id);         // 0x00ba9370
void* __cdecl CivData_GetCities(void* pCiv);                              // 0x005c65e0
struct AvatarNameObj;
struct AvatarNameObj {
    uint32_t* GetName();                                 // 0x00ecdba0 (thiscall)
};
struct TerrainSphereObj {
    void* Find(uint32_t id);                            // 0x00c756e0 (thiscall, ret 4)
};
struct NounObj {
    void* GetTerrainSphere();                           // 0x00f67d90 (thiscall)
};
void* __cdecl GameNounManager_GetAvatar(void* pNoun);                     // 0x00b1fdb0
void* __cdecl GetStringFromId(void* out, uint32_t id, int flag, void* pString);   // 0x00b6ec50
void* __cdecl FUN_00401090(void* pData);                    // 0x00401090
void* __fastcall FUN_004df400(void* pData);                 // 0x004df400 (ecx=pData)
unsigned char __cdecl FUN_004eb930(void* pA);               // 0x004eb930
extern wchar_t gEmptyString16[];                            // 0x01667bac

// UI::AssetDiscovery_Data: base TimelineSporepediaCardData (0x78) then the discovery fields.
// SIZE is exactly 0x9c -- the SP::cString member belongs to the derived cString variant.
class AssetDiscovery_Data {
public:
    uint32_t mField_04;                                 // +0x04
    uint32_t mField_08;                                 // +0x08
    uint32_t mField_0c;                                 // +0x0c
    char pad10[0x78 - 0x10];
    uint32_t mField_78;                                 // +0x78
    uint32_t mField_7c;                                 // +0x7c
    uint32_t mField_80;                                 // +0x80
    uint32_t mField_84;                                 // +0x84
    uint32_t mField_88;                                 // +0x88
    int32_t  mEnumValue;                                // +0x8c
    float    mField_90;                                 // +0x90
    void*    mpField_94;                                // +0x94
    UI_ScenarioPayload* mpPayload;                      // +0x98

    virtual void v04(); virtual void v08();
    virtual void* v0c();                                // +0x0c (slot 3)
    PV8 PV8 PV8 PV8 PV4 PV PV                          // slots 3..40
    virtual void vA4(uint32_t owner);                   // +0xa4 (slot 41)
    virtual void vA8();                                 // +0xa8 (slot 42)
    virtual void vAC(uint32_t owner);                   // +0xac (slot 43)
    PV2
    virtual void* vB8();                                // +0xb8 (slot 46)
    virtual void vbc();                                 // +0xbc (slot 47)
    virtual void vC0();                                 // +0xc0 (slot 48)
    virtual void vC4();                                 // +0xc4 (slot 49)

    void AssignFromScenario(void* pSrc, uint32_t owner);         // 0x00dd0710
    void UpdateEnumValue();                                      // 0x00dd07f0
    uint32_t GetAvatarName();                                    // 0x00dd0940
    uint32_t GetCreatureName();                                  // 0x00dd0960
    void GetSceneKey(uint32_t* pOut);                            // 0x00dd0990
    uint32_t* GetSceneKeyOut(uint32_t* pOut);                    // 0x00dd0a00
    uint32_t* GetStatKeyOut(uint32_t* pOut);                     // 0x00dd0ac0
    uint64_t GetField78();                                       // 0x00dd0b30
    void* ConstructBase();                                       // 0x00dd0b50
    void* ConstructPlain();                                      // 0x00dd0da0
    bool CollectTerrainKeys(eastl_u32vec* pOut);                 // 0x00dd1070
    bool CollectTerrainKeysBase(eastl_u32vec* pOut);             // 0x00642700 (TimelineSporepediaCardData)
};

// The cString-carrying variant (allocated by CreateAssetDiscoveryData): base + SP::cString at +0x9c.
class AssetDiscovery_DataCStr : public AssetDiscovery_Data {
public:
    cString_s006b_47a0 mString;                         // +0x9c

    void AssignCityName(eastl_wstring* pOut);                    // 0x00dd0c00
    void* ConstructString();                                    // 0x00dd0ca0
    void* Delete(unsigned char flags);                          // 0x00dd0cf0
    const wchar_t* GetDisplayText();                            // 0x00dd0e10
};

void __fastcall TimelineSporepediaCardData_Ctor(void* pThis);        // 0x00642100 (ecx=this)
void __fastcall TimelineSporepediaCardData_Dtor(void* pThis);        // 0x00642190 (ecx=this)
extern float gMinusOneFloat;                                        // 0x013eb1bc = -1.0f

// ===================================================================================================
// SP::VehicleTree::AttackCityOrder_Activate -- 0x00dd0230
// ===================================================================================================

// @ 0x00dd0230
// SP::VehicleTree::AttackCityOrder_Activate(cVehicle*, uint32_t, uint32_t, uint32_t, uint32_t,
//                                           cMilitaryAttackCityOrder** ppOrder)
bool __cdecl VehicleTree_AttackCityOrder_Activate(cVehicle* pVehicle, uint32_t, uint32_t, uint32_t,
                                                  uint32_t, cMilitaryAttackCityOrder** ppOrder)
{
    if (ppOrder != 0)
        *ppOrder = 0;

    void* pData = pVehicle->GetTreeData();

    if (gVehicleTicker == 0)
        gVehicleTicker = new ("Simulator/SimSingleton", 0, 0, 0, 0) cVehicleTicker;

    cVehicleGroupOrder* pOrder = gVehicleTicker->GetGroupOrder(pData);
    cMilitaryAttackCityOrder* pCityOrder;
    if (pOrder != 0
        && (pCityOrder = (cMilitaryAttackCityOrder*)pOrder->FindOrderByType(0x2e9ae69)) != 0) {
        pCityOrder->SetupOrder(pVehicle);
        pCityOrder->ResetOrder(pVehicle);
        {
            cMilitaryAttackCityOrder* pOld = *ppOrder;
            if (pCityOrder != pOld) {
                pCityOrder->AddRef();
                *ppOrder = pCityOrder;
                if (pOld != 0)
                    pOld->Release();
            }
        }

        cSpatialObject* pTarget = pCityOrder->GetCurrentTarget(pVehicle);
        if (pTarget != 0 && IsValidFireTarget(pVehicle ? &pVehicle->mCombatant : 0, pTarget)) {
            pVehicle->SetTarget(pTarget->v08());
            Vehicle_ClearOrder(pVehicle);
            return true;
        }

        if (pVehicle->mpChaseTargetRef != 0) {
            cSpatialObject* pOld = pVehicle->mpChaseTargetRef;
            pVehicle->mpChaseTargetRef = 0;
            pOld->vc0();
        }
        pVehicle->Log("(3.1) No target");
        pVehicle->Flush();
        return false;
    }

    pVehicle->Log("(3) No attack order");
    pVehicle->Flush();
    return false;
}

// ===================================================================================================
// SP::cMilitaryAttackCityOrder::OnTick -- 0x00dd0380
// ===================================================================================================

// @ 0x00dd0380
bool cMilitaryAttackCityOrder::OnTick(float)
{
    if (mVehiclesBegin == mVehiclesEnd)
        return false;
    cCity* pCity = mpCity;
    if (pCity == 0 || pCity->v2c())
        return false;
    if (mpCity->GetCivilization()->v2c())
        return false;
    if (CivModeStrategy()->IsValid()) {
        void* pPlayerCity = ((GameNounManagerObj*)NounManager())->GetPlayerCivilization();
        if (((cCity*)pPlayerCity)->mpSomething_44c == mpCity)
            return false;
    }
    if (mpCity->GetCivilization()->v4c() == mAttackerId)
        return false;

    bool bAnyTarget = false;
    bool bAnyCityOrder = false;
    cVehicle** it = mVehiclesBegin;
    cVehicle** pEnd = mVehiclesEnd;
    while (it != pEnd) {
        cVehicle* pVehicle = *it;
        cSpatialObject* pTarget = GetCurrentTarget(pVehicle);
        if (pTarget != 0) {
            pVehicle->SetTarget(pTarget->v08());
            if (pVehicle->mLocomotion != 2) {
                const cSPVector3& a = ((cSpatialObject*)pTarget->v08())->GetPosition();
                const cSPVector3& b = pVehicle->mLoco.GetPosition();
                float d = (float)sqrt(((double)a.z - b.z) * ((double)a.z - b.z)
                                    + ((double)a.y - b.y) * ((double)a.y - b.y)
                                    + ((double)a.x - b.x) * ((double)a.x - b.x));
                cCombatant* pCombatant = &pVehicle->mCombatant;
                if (pCombatant->GetStat() > d)
                    pCombatant->v50(pTarget);
            }
            bAnyTarget = true;
        } else {
            if (pVehicle->mpChaseTargetRef != 0) {
                cSpatialObject* pOld = pVehicle->mpChaseTargetRef;
                pVehicle->mpChaseTargetRef = 0;
                pOld->vc0();
            }
        }
        if (pVehicle->mLoco.v50())
            bAnyCityOrder = true;
        ++it;
    }
    if (!bAnyTarget)
        return false;
    if (bAnyCityOrder)
        mpCity->mDisplay.mFlags |= 0x800;
    return true;
}

// ===================================================================================================
// Small cMilitaryAttackCityOrder helpers
// ===================================================================================================

// @ 0x00dd0550
uint32_t cMilitaryAttackCityOrder::GetCityBannerId()
{
    StarManagerObj* pStar = StarManager();
    if (pStar != 0 && mBanner_80 != 0)
        return pStar->GetBannerId(mBanner_80);
    return 0;
}

// @ 0x00dd0590
void* cMilitaryAttackCityOrder::QueryInterface(uint32_t type)
{
    if (type <= 0x93d55b46u) {
        if (type == 0x93d55b46u || type == 0x13d55dc8u || type == 0x13d6b42bu)
            return (char*)this - 0x10;
        goto fail;
    }
    if (type != 0xee3f516eu)
        goto fail;
    return ((char*)this - 0x10) != 0 ? (void*)this : 0;
fail:
    return 0;
}

// @ 0x00dd05e0
bool cMilitaryAttackCityOrder::IsInSimulatorContext()
{
    if (GetUniverseContext() == 1 || GetUniverseContext() == 2)
        return true;
    return false;
}

// @ 0x00dd0600
// Slot +0x0c viewed as a no-argument predicate (see cVGO_PredView).
struct cVGO_PredView {
    PV2 PV
    virtual void* PredSlot3();
};
bool cMilitaryAttackCityOrder::IsActive()
{
    return ((cVGO_PredView*)this)->PredSlot3() != 0;
}

// @ 0x00dd0610
void* cMilitaryAttackCityOrder::QueryInterface2(uint32_t type)
{
    if (type <= 0x13d6b42bu) {
        if (type == 0x13d6b42bu || type == 0x5b6b834u || type == 0x13d55dc8u)
            return (char*)this - 0x10;
        goto fail;
    }
    if (type == 0x93d55b46u)
        return (char*)this - 0x10;
    if (type != 0xee3f516eu)
        goto fail;
    return ((char*)this - 0x10) != 0 ? (void*)this : 0;
fail:
    return 0;
}

// @ 0x00dd0650
uint32_t cMilitaryAttackCityOrder::GetIconKey()
{
    uint32_t mode = mMode;
    --mode;
    switch (mode) {
    case 0: return 0x9ea3031au;
    case 1: return 0x372e2c04u;
    case 3: return 0xccc35c46u;
    case 4: return 0x65672adeu;
    }
    return GetPaletteItemPriority();
}

// @ 0x00dd06a0
uint32_t cMilitaryAttackCityOrder::GetMissionKey()
{
    if (mMode == 1)
        return (mBanner_88 == 2) ? 0xfffff045u : (0xff577f34u + 0xfffff045u);
    if (mBanner_88 != 0xff576f79u && FUN_00b6e250())
        return FUN_00b6f0d0(mBanner_88);
    return 0xff576f79u;
}

// ===================================================================================================
// UI::AssetDiscovery_Data -- data assignment and enum resolution
// ===================================================================================================

// @ 0x00dd0710
void AssetDiscovery_Data::AssignFromScenario(void* pSrc, uint32_t owner)
{
    UI_ScenarioDataSrc* pScenario = (UI_ScenarioDataSrc*)pSrc;
    if (pScenario->mpPayload != 0) {
        mpPayload = pScenario->mpPayload;
        mField_78 = pScenario->mpPayload->mpInner->mField00;
        mField_08 = pScenario->mpPayload->mpInner->mField04;
        mField_04 = pScenario->mpPayload->mpInner->mField08;
        mField_0c = pScenario->mpPayload->mpInner->mField0c;
        mField_7c = pScenario->mpPayload->mpInner->mField10;
        mField_80 = pScenario->mpPayload->mpInner->mField14;
        mField_84 = pScenario->mpPayload->mpInner->mField18;
        mField_88 = pScenario->mpPayload->mpInner->mField1c;
        mpField_94 = pScenario->mpPayload->mpInner->mpField24;
        mField_90 = pScenario->mpPayload->mpInner->mField2c;
        vC4();
        vA4(owner);
        vA8();
    }
    vAC(owner);
}

// @ 0x00dd07f0
void AssetDiscovery_Data::UpdateEnumValue()
{
    UI_ScenarioPayload* pPayload = mpPayload;
    if (pPayload == 0)
        return;
    if (pPayload->mpInner->mField10 == 6) {
        mEnumValue = -2;
        return;
    }
    mEnumValue = 3;
    uint32_t state = pPayload->mpInner->mField20;
    if (state == 0xffffffffu) {
        mEnumValue = -3;
        return;
    }
    switch (mField_84) {
    case 1:
        switch (state) {
        case 1: mEnumValue = 2; return;
        case 6: case 7:
            {
                unsigned char r = FUN_004eb930(FUN_004df400(FUN_00401090(&mField_04)));
                mEnumValue = (-(uint32_t)(r != 0) & 0x7ffffffau) + 5;
            }
            return;
        case 0: case 3: mEnumValue = 3; return;
        case 2: mEnumValue = 1; return;
        case 4: mEnumValue = 4; return;
        case 5: mEnumValue = 0; return;
        default: return;
        }
    case 2: case 4: case 5:
        switch (state) {
        case 0: mEnumValue = 0; return;
        case 1: mEnumValue = 1; return;
        case 2: mEnumValue = 3; return;
        case 3: mEnumValue = 4; return;
        case 4:
            mEnumValue = (-(uint32_t)(mField_88 != 0x53dbcf1u) & 0x80000006u) + 0x7fffffffu;
            return;
        default: return;
        }
    }
}

// ===================================================================================================
// Accessors -- 0x00dd0940 .. 0x00dd0b30
// ===================================================================================================

// @ 0x00dd0940
uint32_t AssetDiscovery_Data::GetAvatarName()
{
    void* p = vB8();
    if (p != 0) {
        uint32_t* pRef = ((AvatarNameObj*)p)->GetName();
        return *pRef;
    }
    return 0;
}

// @ 0x00dd0960
uint32_t AssetDiscovery_Data::GetCreatureName()
{
    uint32_t result = 0;
    void* p = vB8();
    if (p != 0) {
        void* q = FUN_00b8de30(p);
        if (q != 0) {
            uint32_t* pRef = (uint32_t*)FUN_00bb9de0(q);
            result = *pRef;
        }
    }
    return result;
}

// @ 0x00dd0990
void AssetDiscovery_Data::GetSceneKey(uint32_t* pOut)
{
    uint32_t mode = mField_84;
    pOut[0] = 0;
    pOut[1] = 0x2f7d0004u;
    pOut[2] = 0xca14de92u;
    switch (mode) {
    case 1: pOut[0] = 0xe04dd8b1u; return;
    case 2: pOut[0] = 0x3f185edbu; return;
    case 4: pOut[0] = 0xdc1b3879u; return;
    case 5: pOut[0] = 0x89b74761u; return;
    }
}

// @ 0x00dd0a00
uint32_t* AssetDiscovery_Data::GetSceneKeyOut(uint32_t* pOut)
{
    pOut[0] = 0;
    pOut[1] = 0;
    pOut[2] = 0;
    void* p = vB8();
    if (p != 0) {
        uint32_t* pv = (uint32_t*)FUN_00b8d8e0(p);
        SceneKey* pk = (SceneKey*)pOut;
        *(SceneKey*)pOut = *(SceneKey*)pv;
        pk->mId = 0x2f7d0004u;
        pk->mFlags = (pk->mFlags & 0xffffff01u) | 1u;
    }
    IResourceManager* pMgr = (IResourceManager*)ResourceManager();
    if (!pMgr->LoadKey(pOut, 0, 0, 0, 0, 0)) {
        IPropertyHandle* prop = 0;
        IPropertyManager* pm = (IPropertyManager*)PropertyManager();
        if (prop != 0) {
            IPropertyHandle* pOld = prop;
            prop = 0;
            pOld->Release();
        }
        pm->GetProperty(0x120b89ceu, (void**)&prop);
        GetPropertyAsKey(prop, 0x287652bu, pOut);
        if (prop != 0)
            prop->Release();
    }
    return pOut;
}

// @ 0x00dd0ac0
uint32_t* AssetDiscovery_Data::GetStatKeyOut(uint32_t* pOut)
{
    IPropertyHandle* prop = 0;
    IPropertyManager* pm = (IPropertyManager*)PropertyManager();
    if (prop != 0) {
        IPropertyHandle* pOld = prop;
        prop = 0;
        pOld->Release();
    }
    pm->GetProperty(0x120b89ceu, (void**)&prop);
    pOut[0] = 0;
    pOut[1] = 0;
    pOut[2] = 0;
    GetPropertyAsKey(prop, 0x1a0553ceu, pOut);
    if (prop != 0)
        prop->Release();
    return pOut;
}

// @ 0x00dd0b30
uint64_t AssetDiscovery_Data::GetField78()
{
    return mField_78;
}

// ===================================================================================================
// UI construction / destruction -- 0x00dd0b50 .. 0x00dd0df0
// ===================================================================================================

// @ 0x00dd0b50
void* AssetDiscovery_Data::ConstructBase()
{
    TimelineSporepediaCardData_Ctor(this);
    float fMinusOne = gMinusOneFloat;
    mField_78 = 0;
    mField_7c = 0;
    mField_84 = 0;
    mField_88 = 0;
    mpPayload = 0;
    ((void**)this)[0] = (void*)0x147c9f8;
    ((void**)this)[4] = (void*)0x147c9e8;
    ((void**)this)[5] = (void*)0x147cc78;
    mField_80 = 0xffffffffu;
    mEnumValue = 0x7fffffff;
    mField_90 = fMinusOne;
    return this;
}

// @ 0x00dd0c00
void AssetDiscovery_DataCStr::AssignCityName(eastl_wstring* pOut)
{
    EmpiresObj* pEmpire = StarManager()->GetEmpireByID((uint32_t)(uintptr_t)mpField_94);
    if (pEmpire == 0)
        return;
    CivNameSource* pSrc = (CivNameSource*)pEmpire->GetCities();
    const wchar_t* first = pSrc->mpName;
    const wchar_t* pIt = first;
    while (*pIt)
        ++pIt;
    pOut->Assign(first, first + (pIt - first));
}

// @ 0x00dd0c50
void* __cdecl CreateAssetDiscoveryDataTag()
{
    AssetDiscovery_Data* p = (AssetDiscovery_Data*)operator new(0x9c, "Spui", 0, 0, 0, 0);
    if (p != 0) {
        p->ConstructBase();
        ((void**)p)[0] = (void*)0x147cac0;
        ((void**)p)[4] = (void*)0x147cc88;
        ((void**)p)[5] = (void*)0x147cc78;
        return p;
    }
    return 0;
}

// @ 0x00dd0ca0
void* AssetDiscovery_DataCStr::ConstructString()
{
    ConstructBase();
    ((void**)this)[0] = (void*)0x147cbb0;
    ((void**)this)[4] = (void*)0x147cba0;
    ((void**)this)[5] = (void*)0x147cb90;
    mString.Construct();
    return this;
}

// @ 0x00dd0cf0
void* AssetDiscovery_DataCStr::Delete(unsigned char flags)
{
    ((void**)this)[0] = (void*)0x147cbb0;
    ((void**)this)[4] = (void*)0x147cba0;
    ((void**)this)[5] = (void*)0x147cb90;
    mString.~cString_s006b_47a0();
    ((void**)this)[0] = (void*)0x147c9f8;
    ((void**)this)[4] = (void*)0x147c9e8;
    ((void**)this)[5] = (void*)0x147cc78;
    TimelineSporepediaCardData_Dtor(this);
    if (flags & 1)
        operator delete[](this);
    return this;
}

// @ 0x00dd0d50
void* __cdecl CreateAssetDiscoveryData()
{
    AssetDiscovery_DataCStr* p = (AssetDiscovery_DataCStr*)operator new(0xb0, "Spui", 0, 0, 0, 0);
    if (p != 0) {
        p->ConstructBase();
        cString_s006b_47a0* pStr = &p->mString;
        ((void**)p)[0] = (void*)0x147cbb0;
        ((void**)p)[4] = (void*)0x147cba0;
        ((void**)p)[5] = (void*)0x147cb90;
        pStr->Construct();
        return p;
    }
    return 0;
}

// @ 0x00dd0da0
// Plain variant construct: installs the base vtable (0x00dd0da0, followed at 0x00dd0dc0 by the
// factory that this slice VA's range also covers -- see nonmatching.txt).
void* AssetDiscovery_Data::ConstructPlain()
{
    ConstructBase();
    ((void**)this)[0] = (void*)0x147c9f8;
    ((void**)this)[4] = (void*)0x147cc88;
    ((void**)this)[5] = (void*)0x147cc78;
    return this;
}

// @ 0x00dd0dc0 (factory immediately after ConstructPlain; part of the 00dd0da0 range)
void* __cdecl CreateAssetDiscoveryDataPlain()
{
    AssetDiscovery_Data* p = (AssetDiscovery_Data*)operator new(0x9c, "Spui", 0, 0, 0, 0);
    if (p == 0)
        return 0;
    return p->ConstructPlain();
}

// ===================================================================================================
// UI strings -- 0x00dd0e10
// ===================================================================================================

// @ 0x00dd0e10
const wchar_t* AssetDiscovery_DataCStr::GetDisplayText()
{
    eastl_wstring* pText = (eastl_wstring*)v0c();
    if (pText == 0)
        return 0;

    switch (mField_84) {
    case 1:
        {
            eastl_wstring local;
            local.mpBegin = gEmptyString16;
            local.mpEnd = gEmptyString16;
            local.mpCapacity = (void*)0x1667bae;
            if (mField_88 == 2) {
                local.Append(pText->mpBegin);
                mString.Load(0xad56080c, 0x95b72bu, 0, L"~Epic");
            } else if (mField_88 == 3) {
                local.Append(pText->mpBegin);
                mString.Load(0xad56080c, 0x94acb6f7u, 0, L"~MiniBoss");
            } else {
                return 0;
            }
            {
                IMgr67de40* pMgr = (IMgr67de40*)Mgr67de40();
                IPropertyHandle* pH = pMgr->v20();
                ((IHaveProp12*)pH)->GetPropertyAt12(&mString, 0, 1);
            }
            return mString.GetText();
        }
    case 2:
        {
            eastl_wstring local;
            WString_FromCStr(&local, pText->mpBegin);
            if (mField_88 == 0x53dbcf1u || mField_88 == 0x53dbcf3u)
                GetStringFromId(&local, mField_88, 0xe, &mString);
            else
                GetStringFromId(&local, mField_88, 0, &mString);
            local.DeallocateSelf();
            return mString.GetText();
        }
    case 4:
        {
            eastl_wstring local;
            WString_FromCStr(&local, pText->mpBegin);
            if (mField_88 == 0x53dbcf1u || mField_88 == 0x53dbcf3u)
                GetStringFromId(&local, mField_88, 0xd, &mString);
            else
                GetStringFromId(&local, mField_88, 1, &mString);
            local.DeallocateSelf();
            return mString.GetText();
        }
    case 5:
        {
            void* p = vB8();
            if (p == 0)
                return 0;
            FUN_00b8d8f0(p);
            void* q = FUN_00b8de30(p);
            if (q == 0)
                return 0;
            if ((uint32_t)(uintptr_t)FUN_00bb9ae0(q) != 5)
                return 0;
            void* pAvatar = GameNounManager_GetAvatar(q);
            void* pStar = StarManager();
            void* pCiv = StarManager_GetEmpireByID(pStar, (uint32_t)(uintptr_t)pAvatar);
            if (pCiv == 0)
                return 0;
            return *(const wchar_t**)CivData_GetCities(pCiv);
        }
    }
    return pText->mpBegin;
}

// ===================================================================================================
// Terrain key collection -- 0x00dd1070
// ===================================================================================================

// @ 0x00dd1070
bool AssetDiscovery_Data::CollectTerrainKeys(eastl_u32vec* pOut)
{
    if (mEnumValue == 0x7fffffff) {
        if (mField_08 == 0x2b978c46u) {
            void* pSphere = ((NounObj*)NounManager())->GetTerrainSphere();
            uint32_t v;
            if ((int)mField_84 >= 1)
                v = (uint32_t)(uintptr_t)((TerrainSphereObj*)pSphere)->Find(0xa426730bu);
            else
                v = 0;
            pOut->push_back(v);
            if ((int)mField_84 >= 2)
                v = (uint32_t)(uintptr_t)((TerrainSphereObj*)pSphere)->Find(0xad56080cu);
            else
                v = 0;
            pOut->push_back(v);
            if ((int)mField_84 >= 4)
                v = (uint32_t)(uintptr_t)((TerrainSphereObj*)pSphere)->Find(0xf71fa311u);
            else
                v = 0;
            pOut->push_back(v);
            if ((int)mField_84 >= 5)
                v = (uint32_t)(uintptr_t)((TerrainSphereObj*)pSphere)->Find(0xbeb528cbu);
            else
                v = 0;
            pOut->push_back(v);
            if ((int)mField_84 >= 5)
                v = (uint32_t)(uintptr_t)((TerrainSphereObj*)pSphere)->Find(0x2db6dad3u);
            else
                v = 0;
            pOut->push_back(v);
            return true;
        }
    } else if (mEnumValue != -3) {
        return false;
    }
    return CollectTerrainKeysBase(pOut);
}

// ===================================================================================================
// Misc helpers -- 0x00dd1240, 0x00dd1250
// ===================================================================================================

// @ 0x00dd1240
struct SomeObj {
    char pad[0x28];
    uint32_t mKey_28;                                   // +0x28
    uint8_t  mFlag_2c;                                  // +0x2c
    void SetKeyAgain(uint32_t arg);                     // 0x00dd1240 (thiscall, 1 stack arg)
};
void SomeObj::SetKeyAgain(uint32_t)
{
    mKey_28 = 0x1510d07u;
    mFlag_2c = 1;
}

// @ 0x00dd1250
// pMsg points at a message object whose type tag lives at +0x0c.
struct SomeMessage {
    char pad00[0xc];
    uint32_t mType_0c;                                  // +0x0c
};
bool __stdcall SomeObj_DoMessage(void* pUnused, SomeMessage* pMsg)
{
    (void)pUnused;
    if (pMsg->mType_0c != 0x452c168u)
        return false;
    void* pServer = GetMessageServer67dcc0();
    ((void(__thiscall*)(void*, uint32_t, int, int))((void**)*(void**)pServer)[5])(pServer, 0x452e0cau, 0, 0);
    return true;
}
