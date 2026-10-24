// Slice s00c45860 - SP::cSPMission reward/relation, mission-effect, tool-bag and
// pressure-event helpers, plus the Simulator::cGenericPressureEvent ctor/dtor.
// All functions are __thiscall with `this` in ecx unless noted.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /GS- /fp:fast

#include <math.h>

typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef int                i32;
typedef float              f32;
typedef unsigned long long u64;
typedef long long          i64;

// ---------------------------------------------------------------------------
// eastl containers (retail layout: begin/end/capacity).
// ---------------------------------------------------------------------------
template <class T>
struct Vec {
    T*  mpBegin;      // 0x00
    T*  mpEnd;        // 0x04
    T*  mpCap;        // 0x08
};
typedef Vec<u32> VecU32;

struct Timer20 {                 // cSPMission + 0x38 / +0x58
    u32 raw[8];
    void Ctor();                 // 0x00b63890
    void Dtor();                 // 0x00b638b0
};

// 12-byte element of the mission tool vectors (EA::ResourceMan::Key-like).
struct Key12 { u32 a, b, c; };
typedef Vec<Key12> VecKey12;

// ---------------------------------------------------------------------------
// cProperty: the tagged value the mission's property bag hands back.
// ---------------------------------------------------------------------------
struct cProperty {
    void*  mpValue;    // 0x00
    u32    pad04;      // 0x04
    i32    mCount;     // 0x08
    u32    pad0c;      // 0x0c
    u16    mFlags;     // 0x10
    u16    mType;      // 0x12
    u8*    GetBool();  // 0x0041e920  ?GetBool@cProperty@@QAEPA_NXZ
    f32*   GetFloat(); // 0x0041ea70  Property::GetFloat
};

// The mission's property bag (cSPMission+0x180).  Getters are vtable slots.
struct MissionPropList {
    virtual void vf00(); virtual void vf04(); virtual void vf08();
    virtual void vf0c(); virtual void vf10(); virtual void vf14();
    virtual void vf18();
    virtual bool HasProperty(u32 key);                    // slot +0x1c
    virtual void vf20();
    virtual bool GetProperty(u32 key, cProperty** out);   // slot +0x24
    virtual cProperty* GetPropertyByKey(u32 key);         // slot +0x28
};

// ---------------------------------------------------------------------------
// cEmpire / cPlanet-ish surfaces.
// ---------------------------------------------------------------------------
struct cEntity {
    u32 pad000[0x21];        // 0x00
    u32 mEmpireID;           // 0x84
    u32 GetWeaponryLevel();  // 0x00c317a0
    u8  EmpireCommAllowed(void* planetClue);  // 0x00c308e0
};

struct cPlanetClueObj {
    cPlanetClueObj* SortBanners(u32 zero);               // 0x00b8de30
    void FUN_00bb9c10();                                 // 0x00bb9c10
};

struct cPlanet {
    u32 pad000[0x4f];        // 0x00
    cPlanetClueObj* mpPlanetClue;     // 0x13c
    void* GetRandomAnimalSpecies();   // 0x00c70c10
    void* FUN_00c71e30();             // 0x00c71e30
};

// cSPSimulatorSpaceGame and the player inventory, reached from SpaceGameGet().
struct cPlayerInventory {
    void* GetToolByKeySlot68(void* key);        // vtable +0x68 (this, key)
    void* GetToolByKey(u32 which, void* key);   // vtable +0x64 (this, which, key)
    void* ResolveTool(void* item);              // vtable +0x60 (this, item)
    void  AddTool(Key12* key);                  // 0x00ff45e0
};

struct cSimSpaceGame {
    cPlayerInventory* GetPlayerInventory();     // 0x00a1ad60
};

// ---------------------------------------------------------------------------
// Simulator::cGenericPressureEvent (0x00c46500 ctor / 0x00c46540 dtor).
// ---------------------------------------------------------------------------
struct cGameDataBase {
    void Ctor();           // 0x00b18660
    void Dtor();           // 0x00b184c0
};

class cGenericPressureEvent : public cGameDataBase {
 public:
    void* mpVtbl;          // 0x000
    void* mpVtbl4;         // 0x004
    u32   pad008[0xb];     // 0x008
    void* mpVtbl34;        // 0x034
    Timer20 mTimer38;      // 0x038
    Timer20 mTimer58;      // 0x058

    cGenericPressureEvent* ctor();           // 0x00c46500
    void* ScalarDeletingDtor(u32 flags);     // 0x00c46540
};

// ---------------------------------------------------------------------------
// SP::cSPMission -- fields touched by this slice, at retail offsets.
// ---------------------------------------------------------------------------
class cSPMission {
 public:
    void* mpVtbl0;             // 0x000
    void* mpVtbl4;             // 0x004
    u32   pad008[5];           // 0x008
    VecU32 mVec1c;             // 0x01c
    u32   pad028[3];           // 0x028
    void* mpVtbl34;            // 0x034
    Timer20 mTimer38;          // 0x038
    Timer20 mTimer58;          // 0x058
    f32   mRewardMoney;        // 0x078
    u32   pad07c;              // 0x07c
    u32   mDuration;           // 0x080
    u32   mState;              // 0x084  (eMissionState)
    u8    mSystemsShutdown;    // 0x088
    u8    pad089[3];           // 0x089
    u32   mOwnerEmpireID;      // 0x08c
    void* mpOwnerEmpire;       // 0x090
    u32   pad094[2];           // 0x094
    cPlanet* mpSourcePlanet;   // 0x09c
    u32   pad0a0[0x18];        // 0x0a0
    u32   mStarMapIconEffect;  // 0x100
    u32   mStarMapDestEffect;  // 0x104
    VecU32 mStarMapEffects;    // 0x108
    u32   pad114[7];           // 0x114
    u32   mFlags130;           // 0x130
    VecU32 mEventLogsToRemove; // 0x134
    u32   pad140[2];           // 0x140
    u32   mProgressEventID;    // 0x148
    u32   pad14c[8];           // 0x14c
    void* mTargetAnimalSpecies;// 0x16c
    u32   mTargetSpeciesKey[3];// 0x170
    u32   pad17c;              // 0x17c
    void* mpMissionPropList;   // 0x180
    u32   mRewardToolKey;      // 0x184
    u32   pad188[3];           // 0x188
    VecKey12 mVec194;          // 0x194
    u32   pad1a0[2];           // 0x1a0
    VecKey12 mVec1a8;          // 0x1a8
    u32   pad1b4[2];           // 0x1b4
    VecKey12 mVec1bc;          // 0x1bc
    u32   pad1c8[7];           // 0x1c8
    u32   mField1e4;           // 0x1e4
    cPlanet* mpTargetPlanet;   // 0x1e8

    // helpers defined in the same object elsewhere
    void* GetOwnerEmpire();                 // 0x00c451e0
    f32   GetPunishmentRelation();          // 0x00c45920
    f32   FUN_00c45970();                   // 0x00c45970

    // this slice
    f32   GetRewardRelation();              // 0x00c45860
    u32   CalculateDuration();              // 0x00c45a10
    u32   ReadTargetPlanetType();           // 0x00c45b40
    u32   ReadTargetAnimalSpeciesType();    // 0x00c45b60
    u8    ReadPickClosestStar();            // 0x00c45c60
    Key12* GetMessageVector(Key12* out);    // 0x00c45ca0
    void  SetOwnerEmpire(cEntity* empire);  // 0x00c45d30
    u32   IsTargetPlanetClue(u32 clue);     // 0x00c45d80
    u32   GetMissionIconEffect();           // 0x00c45db0
    u32   GetMissionIconEffectGroup();      // 0x00c45de0
    void  UpdateStarMapEffects(u8 useZero);// 0x00c45e10
    u8    IsTutorialMission();              // 0x00c45f80
    void  UpdateHints(u8 param);            // 0x00c45f90
    u8    CanShowOnMap();                   // 0x00c460f0
    u32   HasValidDescription();            // 0x00c46120
    void  RemoveToolVector194();            // 0x00c46160
    void  RemoveToolVector1bc();            // 0x00c461d0
    void  RemoveToolVector1a8();            // 0x00c46250
    u8    SerializeVarList(void* stream);   // 0x00c46310
    void  WriteUintVector(VecU32* vec, void* stream); // 0x00c46470
    void  ShutdownSystems();                // 0x00c46590
    void  PostLoad();                       // 0x00c466d0
    u8    PickTargetAnimalSpecies();        // 0x00c46790
    u32   QueueConversation();              // 0x00c46800
    u32   CanAccept();                      // 0x00c46840
    void  OnReject();                       // 0x00c468b0
    void  OnFail();                         // 0x00c469f0
};

// ---------------------------------------------------------------------------
// External callees / globals (relocated; addresses in comments).
// ---------------------------------------------------------------------------
extern "C" {
  extern f32 g_missionTimeScale;    // 0x013ec5b4
  extern f32 g_oneHalf;             // 0x013f9428
  extern f32 g_defaultHintValue;    // 0x0146d130
  extern u32 g_zeroSpeciesKey[3];   // 0x0168e844
}

struct cStarMap {
    void RemoveVisual();                                 // 0x01045a60
};
struct cSPUIEventLog {
    void RemoveEvent(u32 id, u32 flag);                  // 0x00dd6d10
};
struct cCommManager {
    void RemoveMatching(i32 a, i32 b, void* mission);    // 0x00aea720
};

f32   __cdecl GetPropertyAsFloat();                      // 0x0041ea70
u32   __cdecl GetPlayerEmpireID();                       // 0x01021090
void* __cdecl GetPlayerEmpire();                         // 0x01021300
void  __cdecl GetPropertyAsFloatArray(void* list, u32 key, i32* count, f32* out); // 0x006a08b0
u8    __cdecl GetPropertyAsKeyInstance(void* list, u32 key, void** out);          // 0x006a12a0
void* __cdecl NounManager();                             // 0x00b3d300
void* __cdecl GameTimeManager();                         // 0x00b3d380
u64   __cdecl GameTimeGet(u32 a);                        // 0x00b316c0
u64   __cdecl aullrem(u64 a, u64 b, u64 c);              // 0x011e0e20
cStarMap* __stdcall GetStarMap(u32 handle, u32 flag);    // 0x01046fc0
void* __cdecl StarMapHelper(u32 a, u32 b);               // 0x01045120
void* __cdecl GetTerrainSphere();                        // 0x00f67d90
f32   __cdecl TerrainSphereGetValue();                   // 0x00c75c30
void* __cdecl SpaceGameGet();                            // 0x01002bd0
void* __cdecl SpaceGameGet(int a);                       // 0x01002bd0
void* __cdecl FUN_010666a0(void* p);                     // 0x010666a0
void  __cdecl FUN_0106f120(void* p);                     // 0x0106f120
void* __cdecl FUN_01005180(u32 a);                       // 0x01005180
void  __cdecl IntVectorResize(void* v, u32 n);           // 0x007eb820
void* __cdecl GetMissionManager();                       // 0x00feb9f0
void  __cdecl MissionMgrRemove(void* mission);           // 0x00febe00
void  __cdecl MissionMgrEvent(void* mission);            // 0x00fecbb0
struct cMissionManager {
    void* GetOtherVec();                                 // 0x00897670
    void* GetVec();                                      // 0x00febaa0
};
void* __cdecl PropertyManager();                         // 0x0067de30
cSPUIEventLog* __cdecl EventLog();                       // 0x00b3d3e0
cCommManager* __cdecl CommManager();                     // 0x00b3d4a0
void* __cdecl CommFindEntry(u32 empire, void* ctx);      // 0x00ae93f0
void  __cdecl CommRemoveByPtr(void* entry);              // 0x00aea7f0
void  __cdecl CommAdd(u32 empire, void* ctx, u32 a, u32 b, u32 c, u32 d, u32 e); // 0x00aeb7a0
void* __cdecl GetCommContext(u32 a, u32 b, u32 c, u32 d, u32 e);  // 0x00ce6950
void  __cdecl WriteUint32(void* stream, void* value, u32 count, u32 flag); // 0x0093aa70
void* __cdecl GetSourcePlanetClue();                     // 0x00c452a0
void  __cdecl AddVisual(void* a);                        // 0x00c46590
void  __cdecl cSPUILayoutCtor();                         // 0x00dd1ca0
void  __cdecl cSPUILayoutAdd();                          // 0x00dd27c0
void  __cdecl TerraformingManagerAdd(void* a);           // 0x00bc1b10
struct cRelationshipManager {
    void RecordEvent(u32 a, u32 b, u32 ev, f32 v);       // 0x00d06240
    f32 RelGetRelation(u32 a, u32 b, u32 c);             // 0x00d00a10
};
cRelationshipManager* __cdecl RelationshipManager();     // 0x00b3d2c0
struct cSpaceRelationshipTuning {
    f32 TuningGetThreshold();                            // 0x01040860
};
cSpaceRelationshipTuning* __cdecl GetSpaceRelationshipTuning();  // 0x010407c0
void  __cdecl OperatorDeleteArray(void* p);              // 0x00f47380

// cVarListSerializer
struct cVarListSerializer {
    void Ctor(void* self, void* mission, const char* name, u32 id);  // 0x00692f90
    u8   Serialize(void* stream);                                    // 0x00692900
};

// ---------------------------------------------------------------------------
// 0x00c45860 - SP::cSPMission::GetRewardRelation
// ---------------------------------------------------------------------------
// @ 0x00c45860
f32 cSPMission::GetRewardRelation()
{
    u32 relation = 0;
    cEntity* owner = (cEntity*)GetOwnerEmpire();
    if (owner != 0)
        relation = owner->mEmpireID;
    f32 result = 0.0f;
    if (mpMissionPropList == 0)
        return result;
    u32 key = 0x6fa6f0f4;
    if (relation == 1)
        key = 0x5cf5e5e0;
    else if (relation == 2)
        key = 0xaef74c9a;
    else if (relation == 3)
        key = 0xe3833365;
    MissionPropList* list = (MissionPropList*)mpMissionPropList;
    if (list->HasProperty(key))
        key = key;
    if (list->HasProperty(key) && mpMissionPropList != 0) {
        cProperty* prop = 0;
        if (list->GetProperty(key, &prop) && prop->mType == 0xd) {
            result = *prop->GetFloat();
        }
    }
    return result;
}

// ---------------------------------------------------------------------------
// 0x00c45a10 - SP::cSPMission::CalculateDuration
// ---------------------------------------------------------------------------
// @ 0x00c45a10
u32 cSPMission::CalculateDuration()
{
    f32 duration = 0.0f;
    if (mpMissionPropList != 0) {
        cProperty* prop = 0;
        if (((MissionPropList*)mpMissionPropList)->GetProperty(0xd71a8119, &prop) &&
            prop->mType == 0xd)
            duration = *prop->GetFloat();
    }
    u8 carry = 0;
    if (mpMissionPropList != 0) {
        cProperty* prop = 0;
        if (((MissionPropList*)mpMissionPropList)->GetProperty(0xd71a811a, &prop) &&
            prop->mType == 1)
            carry = *prop->GetBool();
    }
    if (carry != 0)
        mFlags130 |= 0x20;
    else
        mFlags130 &= ~0x20;
    if (mTargetSpeciesKey[1] != 0xffffffff &&
        mTargetSpeciesKey[1] != GetPlayerEmpireID()) {
        i32 count = 0;
        f32 value = 0.0f;
        GetPropertyAsFloatArray(mpMissionPropList, 0x5efaf8b, &count, &value);
        if (count > 0) {
            cEntity* owner = (cEntity*)GetOwnerEmpire();
            owner->GetWeaponryLevel();
        }
    }
    f32 scale = TerrainSphereGetValue();
    f32 total = (scale * duration) * g_missionTimeScale;
    mRewardMoney = total;
    mDuration = (u32)(i64)total;
    return (u32)(i64)total;
}

// ---------------------------------------------------------------------------
// 0x00c45b40 - SP::cSPMission::ReadTargetPlanetType
// ---------------------------------------------------------------------------
// @ 0x00c45b40
u32 cSPMission::ReadTargetPlanetType()
{
    void* out;
    GetPropertyAsKeyInstance(mpMissionPropList, 0x1f7aaaaa, &out);
    return (u32)out;
}

// ---------------------------------------------------------------------------
// 0x00c45b60 - SP::cSPMission::ReadTargetAnimalSpeciesType
// ---------------------------------------------------------------------------
// @ 0x00c45b60
u32 cSPMission::ReadTargetAnimalSpeciesType()
{
    void* out;
    GetPropertyAsKeyInstance(mpMissionPropList, 0x1f7aaaab, &out);
    return (u32)out;
}

// ---------------------------------------------------------------------------
// 0x00c45c60 - SP::cSPMission::ReadPickClosestStar
// ---------------------------------------------------------------------------
// @ 0x00c45c60
u8 cSPMission::ReadPickClosestStar()
{
    if (mpMissionPropList != 0) {
        cProperty* prop = 0;
        if (((MissionPropList*)mpMissionPropList)->GetProperty(0x1f707857, &prop) &&
            prop->mType == 1)
            return *prop->GetBool();
    }
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00c45ca0 - SP::cSPMission::GetMessageVector
// ---------------------------------------------------------------------------
// @ 0x00c45ca0
Key12* cSPMission::GetMessageVector(Key12* out)
{
    void* vec;
    if ((mFlags130 & 1) != 0) {
        cMissionManager* mgr = (cMissionManager*)GetMissionManager();
        vec = mgr->GetOtherVec();
    } else {
        cMissionManager* mgr = (cMissionManager*)GetMissionManager();
        vec = mgr->GetVec();
    }
    *out = *(Key12*)vec;
    return out;
}

// ---------------------------------------------------------------------------
// 0x00c45d30 - SP::cSPMission::SetOwnerEmpire
// ---------------------------------------------------------------------------
// @ 0x00c45d30
void cSPMission::SetOwnerEmpire(cEntity* empire)
{
    mOwnerEmpireID = empire != 0 ? empire->mEmpireID : 0xffffffff;
    void* old = mpOwnerEmpire;
    if (empire != (cEntity*)old) {
        if (empire != 0)
            (*(void(__thiscall**)(void*))*(void**)empire)(empire);
        mpOwnerEmpire = empire;
        if (old != 0)
            (*(void(__thiscall**)(void*))((char*)*(void**)old + 4))(old);
    }
}

// ---------------------------------------------------------------------------
// 0x00c45d80 - SP::cSPMission::IsTargetPlanetClue
// ---------------------------------------------------------------------------
// @ 0x00c45d80
u32 cSPMission::IsTargetPlanetClue(u32 clue)
{
    if (mpTargetPlanet != 0 &&
        *(u32*)((char*)mpTargetPlanet->mpPlanetClue + 0x13c) == clue)
        return 1;
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00c45db0 - SP::cSPMission::GetMissionIconEffect
// ---------------------------------------------------------------------------
// @ 0x00c45db0
u32 cSPMission::GetMissionIconEffect()
{
    if (mpMissionPropList != 0) {
        void* out;
        if (GetPropertyAsKeyInstance(mpMissionPropList, 0x45c00672, &out))
            return (u32)out;
    }
    return 0xcda5f5d;
}

// ---------------------------------------------------------------------------
// 0x00c45de0 - SP::cSPMission::GetMissionIconEffectGroup
// ---------------------------------------------------------------------------
// @ 0x00c45de0
u32 cSPMission::GetMissionIconEffectGroup()
{
    if (mpMissionPropList != 0) {
        void* out;
        if (GetPropertyAsKeyInstance(mpMissionPropList, 0xf924ebf3, &out))
            return (u32)out;
    }
    return 0x166521a5;
}

// ---------------------------------------------------------------------------
// 0x00c45e10 - SP::cSPMission::UpdateStarMapEffects
// ---------------------------------------------------------------------------
// @ 0x00c45e10
void cSPMission::UpdateStarMapEffects(u8 useZero)
{
    GameTimeManager();
    u64 time = GameTimeGet(0);
    u64 rem = aullrem(time, 1000, 0);
    f32 frac = (f32)(i64)(rem & 0x7fffffffffffffffULL);
    frac = frac * g_oneHalf;

    if (mStarMapIconEffect != 0xffffffff) {
        f32 v = useZero != 0 ? g_defaultHintValue : frac;
        GetStarMap(mStarMapIconEffect, 0);
        void* obj = StarMapHelper(0, mStarMapIconEffect);
        if (obj != 0)
            (*(void(__thiscall**)(void*, u32, f32*, u32))((char*)*(void**)obj + 0x44))(obj, 4, &v, 1);
    }
    if (mStarMapDestEffect != 0xffffffff) {
        f32 v = useZero != 0 ? g_defaultHintValue : frac;
        GetStarMap(mStarMapDestEffect, 0);
        void* obj = StarMapHelper(0, mStarMapDestEffect);
        if (obj != 0)
            (*(void(__thiscall**)(void*, u32, f32*, u32))((char*)*(void**)obj + 0x44))(obj, 4, &v, 1);
    }
    if (mStarMapEffects.mpBegin != mStarMapEffects.mpEnd) {
        i32 n = (i32)(mStarMapEffects.mpEnd - mStarMapEffects.mpBegin);
        if (n > 0) {
            i32 i = 0;
            do {
                u32 h = mStarMapEffects.mpBegin[i];
                if (h != 0xffffffff) {
                    f32 v = useZero != 0 ? g_defaultHintValue : frac;
                    GetStarMap(h, 0);
                    void* obj = StarMapHelper(0, h);
                    if (obj != 0)
                        (*(void(__thiscall**)(void*, u32, f32*, u32))((char*)*(void**)obj + 0x44))(obj, 4, &v, 1);
                }
                ++i;
            } while (i < n);
        }
    }
}

// ---------------------------------------------------------------------------
// 0x00c45f80 - SP::cSPMission::IsTutorialMission
// ---------------------------------------------------------------------------
// @ 0x00c45f80
u8 cSPMission::IsTutorialMission()
{
    return (u8)(~(u8)(mFlags130 >> 1)) & 1;
}

// ---------------------------------------------------------------------------
// 0x00c45f90 - SP::cSPMission::UpdateHints
// ---------------------------------------------------------------------------
// @ 0x00c45f90
void cSPMission::UpdateHints(u8 param)
{
    if (mpMissionPropList != 0) {
        cProperty* prop = 0;
        if (((MissionPropList*)mpMissionPropList)->GetProperty(0x5590946, &prop) &&
            prop->mType == 1 && *prop->GetBool() == 0)
            goto body;
    }
body:
    {
        u32 e1;
        cEntity* owner1 = (cEntity*)GetOwnerEmpire();
        if (owner1 != 0) {
            owner1 = (cEntity*)GetOwnerEmpire();
            e1 = owner1->mEmpireID;
        } else {
            e1 = 0xffffffff;
        }
        void* ctx1 = GetCommContext(0xc8fbf7d7, 0x305a4a16, 0,
                                    (u32)mpSourcePlanet->mpPlanetClue, 0);
        void* entry1 = CommFindEntry(e1, ctx1);
        if (entry1 != 0)
            CommRemoveByPtr(entry1);

        u32 e2;
        cEntity* owner2 = (cEntity*)GetOwnerEmpire();
        if (owner2 != 0) {
            owner2 = (cEntity*)GetOwnerEmpire();
            e2 = owner2->mEmpireID;
        } else {
            e2 = 0xffffffff;
        }
        void* ctx2 = GetCommContext(0xc8fbf7d7, 0xa789391d, 0,
                                    (u32)mpSourcePlanet->mpPlanetClue, 0);
        void* entry2 = CommFindEntry(e2, ctx2);
        if (entry2 != 0)
            CommRemoveByPtr(entry2);

        u32 e3;
        cEntity* owner3 = (cEntity*)GetOwnerEmpire();
        if (owner3 != 0) {
            owner3 = (cEntity*)GetOwnerEmpire();
            e3 = owner3->mEmpireID;
        } else {
            e3 = 0xffffffff;
        }
        u32 key = param != 0 ? 0xa789391d : (0x88d110f9 + 0xa789391d);
        void* ctx3 = GetCommContext(0xc8fbf7d7, key, 0,
                                    (u32)mpSourcePlanet->mpPlanetClue, 0);
        CommAdd(e3, ctx3, 0xc8fbf7d7, key, 0, 1, 0x493e0);
    }
}

// ---------------------------------------------------------------------------
// 0x00c460f0 - SP::cSPMission::CanShowOnMap
// ---------------------------------------------------------------------------
// @ 0x00c460f0
u8 cSPMission::CanShowOnMap()
{
    u32 flags = mFlags130;
    u32 bit5 = flags >> 5;
    if ((bit5 & 1) != 0) {
        u32 bit6 = flags >> 6;
        if ((bit6 & 1) == 0)
            return 0;
    }
    u8 r = (*(u8(__thiscall**)(void*))((char*)*(void**)this + 0xf8))(this);
    bool b = (r == 0);
    return b;
}

// ---------------------------------------------------------------------------
// 0x00c46120 - SP::cSPMission::HasValidDescription
// ---------------------------------------------------------------------------
// @ 0x00c46120
u32 cSPMission::HasValidDescription()
{
    u32 n = (*(u32(__thiscall**)(void*))((char*)*(void**)this + 0xa8))(this);
    if (n > 0 && (mFlags130 & 1) == 0) {
        if ((*(u8(__thiscall**)(void*))((char*)*(void**)this + 0x104))(this) != 0)
            return 1;
    }
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00c46160 - remove a set of mission tools from the player inventory
// ---------------------------------------------------------------------------
// @ 0x00c46160
void cSPMission::RemoveToolVector194()
{
    i32 n = (i32)(mVec194.mpEnd - mVec194.mpBegin);
    if (n > 0) {
        i32 off = 0;
        do {
            cSimSpaceGame* game = (cSimSpaceGame*)SpaceGameGet();
            cPlayerInventory* inv = game->GetPlayerInventory();
            void* key = (void*)((char*)mVec194.mpBegin + off);
            void* item = (*(void*(__thiscall**)(void*, void*))((char*)*(void**)inv + 0x68))(inv, key);
            if (item != 0) {
                void* r = FUN_010666a0(item);
                FUN_0106f120(r);
            }
            off += 0xc;
            --n;
        } while (n != 0);
    }
}

// ---------------------------------------------------------------------------
// 0x00c461d0 - remove vector-1bc mission tools
// ---------------------------------------------------------------------------
// @ 0x00c461d0
void cSPMission::RemoveToolVector1bc()
{
    cSimSpaceGame* game = (cSimSpaceGame*)SpaceGameGet();
    cPlayerInventory* inv = game->GetPlayerInventory();
    i32 n = (i32)(mVec1bc.mpEnd - mVec1bc.mpBegin);
    if (n > 0) {
        i32 off = 0;
        do {
            void* key = (void*)((char*)mVec1bc.mpBegin + off);
            void* item = (*(void*(__thiscall**)(void*, u32, void*))((char*)*(void**)inv + 0x64))(inv, 0, key);
            item = (*(void*(__thiscall**)(void*, void*))((char*)*(void**)inv + 0x60))(inv, item);
            if (item != 0) {
                void* r = FUN_010666a0(item);
                FUN_0106f120(r);
            }
            off += 0xc;
            --n;
        } while (n != 0);
    }
}

// ---------------------------------------------------------------------------
// 0x00c46250 - remove vector-1a8 mission tools
// ---------------------------------------------------------------------------
// @ 0x00c46250
void cSPMission::RemoveToolVector1a8()
{
    cSimSpaceGame* game = (cSimSpaceGame*)SpaceGameGet();
    cPlayerInventory* inv = game->GetPlayerInventory();
    i32 n = (i32)(mVec1a8.mpEnd - mVec1a8.mpBegin);
    if (n > 0) {
        i32 off = 0;
        do {
            void* key = (void*)((char*)mVec1a8.mpBegin + off);
            void* item = (*(void*(__thiscall**)(void*, u32, void*))((char*)*(void**)inv + 0x64))(inv, 1, key);
            item = (*(void*(__thiscall**)(void*, void*))((char*)*(void**)inv + 0x60))(inv, item);
            if (item != 0) {
                void* r = FUN_010666a0(item);
                FUN_0106f120(r);
            }
            off += 0xc;
            --n;
        } while (n != 0);
    }
}

// ---------------------------------------------------------------------------
// 0x00c46310 - serialize the mission variable list
// ---------------------------------------------------------------------------
// @ 0x00c46310
u8 cSPMission::SerializeVarList(void* stream)
{
    cVarListSerializer ser;
    ser.Ctor(&ser, this, "Mission", 0x1a80d26);
    u8 result = ser.Serialize(stream);
    i32 n = (i32)(mVec1c.mpEnd - mVec1c.mpBegin);
    void* o = (*(void*(__thiscall**)(void*))((char*)*(void**)stream + 0x20))(stream);
    void* s = (*(void*(__thiscall**)(void*))((char*)*(void**)o + 0x18))(o);
    i32 count = n;
    WriteUint32(s, &count, 1, 0);
    for (i32 i = 0; i < n; ++i) {
        i32 field = *(i32*)((char*)mVec1c.mpBegin[i] + 0x70);
        void* o2 = (*(void*(__thiscall**)(void*))((char*)*(void**)stream + 0x20))(stream);
        void* s2 = (*(void*(__thiscall**)(void*))((char*)*(void**)o2 + 0x18))(o2);
        i32 v = field;
        WriteUint32(s2, &v, 1, 0);
    }
    return result;
}

// ---------------------------------------------------------------------------
// 0x00c463d0 - release an AutoRefCount-like pointer member
// ---------------------------------------------------------------------------
// @ 0x00c463d0
void** __fastcall ReleaseRefMember(void** self)
{
    void* obj = *self;
    if (obj != 0) {
        *self = 0;
        (*(void(__thiscall**)(void*))((char*)*(void**)obj + 8))(obj);
    }
    return self;
}

// ---------------------------------------------------------------------------
// 0x00c46470 - serialize a vector of u32 through a stream interface
// ---------------------------------------------------------------------------
// @ 0x00c46470
void cSPMission::WriteUintVector(VecU32* vec, void* stream)
{
    i32 n = (i32)(vec->mpEnd - vec->mpBegin);
    void* o = (*(void*(__thiscall**)(void*))((char*)*(void**)stream + 0x20))(stream);
    void* s = (*(void*(__thiscall**)(void*))((char*)*(void**)o + 0x18))(o);
    i32 count = n;
    WriteUint32(s, &count, 1, 0);
    u32* p = vec->mpBegin;
    u32* end = vec->mpEnd;
    while (p != end) {
        void* o2 = (*(void*(__thiscall**)(void*))((char*)*(void**)stream + 0x20))(stream);
        void* s2 = (*(void*(__thiscall**)(void*))((char*)*(void**)o2 + 0x18))(o2);
        u32 v = *p;
        WriteUint32(s2, &v, 1, 0);
        ++p;
    }
    (*(void(__thiscall**)(void*))((char*)*(void**)stream + 0x1c))(stream);
}

// ---------------------------------------------------------------------------
// 0x00c46500 - Simulator::cGenericPressureEvent::cGenericPressureEvent
// ---------------------------------------------------------------------------
// @ 0x00c46500
cGenericPressureEvent* cGenericPressureEvent::ctor()
{
    Ctor();
    *(void* volatile*)((char*)this + 0x34) = (void*)0x13eb384;
    mpVtbl = (void*)0x146d188;
    mpVtbl4 = (void*)0x146d174;
    mpVtbl34 = (void*)0x146d164;
    mTimer38.Ctor();
    mTimer58.Ctor();
    return this;
}

// ---------------------------------------------------------------------------
// 0x00c46540 - Simulator::cGenericPressureEvent scalar deleting destructor
// ---------------------------------------------------------------------------
// @ 0x00c46540
void* cGenericPressureEvent::ScalarDeletingDtor(u32 flags)
{
    mpVtbl = (void*)0x146d188;
    mpVtbl4 = (void*)0x146d174;
    mpVtbl34 = (void*)0x146d164;
    mTimer58.Dtor();
    mTimer38.Dtor();
    mpVtbl34 = (void*)0x13eb394;
    Dtor();
    if ((flags & 1) != 0)
        OperatorDeleteArray(this);
    return this;
}

// ---------------------------------------------------------------------------
// 0x00c46590 - SP::cSPMission::ShutdownSystems
// ---------------------------------------------------------------------------
// @ 0x00c46590
void cSPMission::ShutdownSystems()
{
    mSystemsShutdown = 1;
    CommManager()->RemoveMatching(-1, -1, this);
    if (mStarMapIconEffect != 0xffffffff) {
        GetStarMap(mStarMapIconEffect, 0)->RemoveVisual();
        mStarMapIconEffect = 0xffffffff;
    }
    if (mStarMapDestEffect != 0xffffffff) {
        GetStarMap(mStarMapDestEffect, 0)->RemoveVisual();
        mStarMapDestEffect = 0xffffffff;
    }
    i32 n = (i32)(mStarMapEffects.mpEnd - mStarMapEffects.mpBegin);
    if (n > 0) {
        do {
            u32 handle = mStarMapEffects.mpEnd[-1];
            GetStarMap(handle, 0)->RemoveVisual();
            mStarMapEffects.mpEnd -= 1;
            --n;
        } while (n != 0);
    }
    if (mpTargetPlanet != 0) {
        cPlanetClueObj* clue = mpTargetPlanet->mpPlanetClue;
        clue->SortBanners(0)->FUN_00bb9c10();
    }
    if (mProgressEventID != 0xffffffff) {
        EventLog()->RemoveEvent(mProgressEventID, 1);
        mProgressEventID = 0xffffffff;
    }
    (*(void(__thiscall**)(void*))((char*)*(void**)this + 0x148))(this);
    i32 m = (i32)(mEventLogsToRemove.mpEnd - mEventLogsToRemove.mpBegin);
    if (m > 0) {
        do {
            u32 id = mEventLogsToRemove.mpEnd[-1];
            mEventLogsToRemove.mpEnd -= 1;
            EventLog()->RemoveEvent(id, 0);
            --m;
        } while (m != 0);
    }
}

// ---------------------------------------------------------------------------
// 0x00c466d0 - SP::cSPMission::PostLoad
// ---------------------------------------------------------------------------
// @ 0x00c466d0
void cSPMission::PostLoad()
{
    void* mgr = PropertyManager();
    void* old = mpMissionPropList;
    if (old != 0) {
        mpMissionPropList = 0;
        (*(void(__thiscall**)(void*))((char*)*(void**)old + 4))(old);
    }
    (*(void(__thiscall**)(void*, u32, u32, void**))((char*)*(void**)mgr + 0x2c))(mgr, mRewardToolKey, 0x2ae1a8e, &mpMissionPropList);
    if (mpMissionPropList == 0) {
        mState = 1;
        GetMissionManager();
        MissionMgrRemove(this);
        (*(void(__thiscall**)(void*))((char*)*(void**)this + 0x44))(this);
    }
    if (mState == 2 || mState == 3) {
        (*(void(__thiscall**)(void*))((char*)*(void**)this + 0x144))(this);
        (*(void(__thiscall**)(void*))((char*)*(void**)this + 0x194))(this);
    }
    if (mpTargetPlanet != 0)
        TerraformingManagerAdd(mpTargetPlanet);
    (*(void(__thiscall**)(void*, u32))((char*)*(void**)this + 0x190))(this, 0);
}

// ---------------------------------------------------------------------------
// 0x00c46790 - SP::cSPMission::PickTargetAnimalSpecies
// ---------------------------------------------------------------------------
// @ 0x00c46790
u8 cSPMission::PickTargetAnimalSpecies()
{
    void* species = mpTargetPlanet->GetRandomAnimalSpecies();
    mTargetAnimalSpecies = species;
    if (species == 0) {
        u32 zero0 = g_zeroSpeciesKey[0];
        mTargetSpeciesKey[0] = zero0;
        mTargetSpeciesKey[1] = g_zeroSpeciesKey[1];
        mTargetSpeciesKey[2] = g_zeroSpeciesKey[2];
        return 0;
    }
    *(Key12*)mTargetSpeciesKey = *(Key12*)((char*)species + 0x504);
    return 1;
}

// ---------------------------------------------------------------------------
// 0x00c46800 - SP::cSPMission::QueueConversation
// ---------------------------------------------------------------------------
// @ 0x00c46800
u32 cSPMission::QueueConversation()
{
    cEntity* owner = (cEntity*)GetOwnerEmpire();
    if (mOwnerEmpireID != 0xffffffff && owner != 0) {
        cPlanet* planet = mpSourcePlanet;
        void* clue;
        if (planet != 0) {
            clue = planet->mpPlanetClue;
            if (owner->EmpireCommAllowed(clue) == 0)
                return 0;
        }
    }
    return 1;
}

// ---------------------------------------------------------------------------
// 0x00c46840 - SP::cSPMission::CanAccept
// ---------------------------------------------------------------------------
// @ 0x00c46840
u32 cSPMission::CanAccept()
{
    cEntity* owner = (cEntity*)GetOwnerEmpire();
    if (mOwnerEmpireID != 0xffffffff && owner != 0) {
        cEntity* player = (cEntity*)GetPlayerEmpire();
        if (owner != player) {
            player = (cEntity*)GetPlayerEmpire();
            u32 pid = player->mEmpireID;
            u32 oid = owner->mEmpireID;
            f32 relation = RelationshipManager()->RelGetRelation(oid, pid, 0);
            f32 threshold = GetSpaceRelationshipTuning()->TuningGetThreshold();
            if (relation < threshold)
                return 0;
        }
    }
    return 1;
}

// ---------------------------------------------------------------------------
// 0x00c468b0 - SP::cSPMission::OnReject
// ---------------------------------------------------------------------------
// @ 0x00c468b0
void cSPMission::OnReject()
{
    if ((mFlags130 & 8) != 0) {
        GetMissionManager();
        MissionMgrEvent(this);
    }
    cEntity* owner = (cEntity*)GetOwnerEmpire();
    if (owner != 0 && owner != (cEntity*)GetPlayerEmpire()) {
        f32 rel = FUN_00c45970();
        rel = fabsf(rel);
        {
            u32 oid = owner->mEmpireID;
            u32 id = GetPlayerEmpireID();
            cRelationshipManager* rm = RelationshipManager();
            rm->RecordEvent(oid, id, 0x526e51d, rel);
        }
        {
            u32 oid2 = owner->mEmpireID;
            u32 id2 = GetPlayerEmpireID();
            cRelationshipManager* rm2 = RelationshipManager();
            rm2->RelGetRelation(oid2, id2, 0);
        }
        cSPUILayoutCtor();
        cSPUILayoutAdd();
    }
    SpaceGameGet(4);
    void* v = FUN_01005180(4);
    IntVectorResize(v, 8);
    *(f32*)((char*)*(void**)((char*)v + 0xc) + 0x1c) = mRewardMoney;

    cProperty* prop = ((MissionPropList*)mpMissionPropList)->GetPropertyByKey(0x1625a62e);
    u16 flags = prop->mFlags & 0x30;
    i32 count;
    if (flags != 0) {
        count = prop->mCount;
        if (count <= 0)
            return;
    } else {
        if (prop->mType == 0)
            return;
        count = 1;
    }
    do {
        Key12 key;
        key.a = *(u32*)prop->mpValue;
        key.b = 0;
        key.c = 0;
        cSimSpaceGame* game = (cSimSpaceGame*)SpaceGameGet();
        cPlayerInventory* inv = game->GetPlayerInventory();
        inv->AddTool(&key);
        --count;
    } while (count != 0);
}

// ---------------------------------------------------------------------------
// 0x00c469f0 - SP::cSPMission::OnFail
// ---------------------------------------------------------------------------
// @ 0x00c469f0
void cSPMission::OnFail()
{
    cEntity* owner = (cEntity*)GetOwnerEmpire();
    if (owner != 0 && owner != (cEntity*)GetPlayerEmpire()) {
        f32 rel = GetPunishmentRelation();
        rel = fabsf(rel);
        {
            u32 oid = owner->mEmpireID;
            u32 id = GetPlayerEmpireID();
            cRelationshipManager* rm = RelationshipManager();
            rm->RecordEvent(oid, id, 0x526e51c, rel);
        }
        {
            u32 oid2 = owner->mEmpireID;
            u32 id2 = GetPlayerEmpireID();
            cRelationshipManager* rm2 = RelationshipManager();
            rm2->RelGetRelation(oid2, id2, 0);
        }
        cSPUILayoutCtor();
        cSPUILayoutAdd();
    }
    SpaceGameGet(7);
    void* v = FUN_01005180(7);
    IntVectorResize(v, 8);
    *(f32*)((char*)*(void**)((char*)v + 0xc) + 0x1c) = mRewardMoney;
    if ((mFlags130 & 1) != 0)
        UpdateHints(0);
    (*(void(__thiscall**)(void*))((char*)*(void**)this + 0x84))(this);
}
