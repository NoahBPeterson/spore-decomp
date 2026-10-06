// GonzagoHintConditions  @ 0x00e07e70  (5747 bytes, __cdecl, /O2 /arch:SSE)
//
//   bool GonzagoHintConditions(uint32_t condition)
//
// Evaluates one tutorial/hint ("Gonzago") condition, identified by a 32-bit hash.  The
// first ten ids are mode independent; the rest are grouped by the current game mode
// (creature 0x1654c01, civ 0x1654c04, tribe 0x1654c02, space 0x1654c05).  An id that is
// not handled by the active mode's block falls through to the next mode check and finally
// returns false.
//
// Callee names come from the card (index names); several of them are only approximate
// (e.g. 0x00b3d300 "NounManager", 0x00f67d90 "GetCurrentTerrainSphere").  Every callee
// and global is a masked relocation, so the stub classes below only fix the calling
// convention, the argument list and the vtable slot / field offsets used here.

#include "types.h"

#define CAT2_(a, b) a##b
#define CAT_(a, b) CAT2_(a, b)
#define PV virtual void CAT_(_pv, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8
#define PV32 PV16 PV16

// --- game-mode ids returned by SP::GetCurrentGameMode() -------------------------------
enum
{
    kGameModeEditor   = 0x00dbdba1,
    kGameModeCell     = 0x01654c00,
    kGameModeCreature = 0x01654c01,
    kGameModeTribe    = 0x01654c02,
    kGameModeCiv      = 0x01654c04,
    kGameModeSpace    = 0x01654c05,
};

template <class T> struct PtrVector
{
    T** mpBegin;
    T** mpEnd;
    T** mpCapacity;
    int mAllocator;

    int size() const { return (int)(mpEnd - mpBegin); }
};

// subobject at +0x34 of a city/building (vtable slot 0x48: bool query, 0x50: bool query)
struct cBuildingIface
{
    PV16 PV2
    virtual bool IsQuery48();   // +0x48
    PV
    virtual bool IsQuery50();   // +0x50
};

struct cBuilding
{
    uint32_t pad[0x34 / 4];
    cBuildingIface mIface;      // +0x34
};

struct cCity
{
    cBuilding* GetCityHall();   // 0x00bd9b40
    bool       FUN_00bd7df0();
    bool       FUN_00c004c0(int which);
};

struct cHintTracker             // 0x00f67d90 result
{
    bool IsDone(uint32_t id);   // 0x00c772c0
    void MarkDone(uint32_t id); // 0x00c77bf0
};

struct cAvatarSub5a8
{
    float FUN_00bfc490();
};

struct cAvatar
{
    uint32_t      pad0[0x5a8 / 4];
    cAvatarSub5a8 mSub5a8;          // +0x5a8
    uint32_t      pad1[(0xb5e - 0x5ac) / 4];
    uint16_t      pad2;
    bool          mbFlagB5E;        // +0xb5e

    float FUN_00c0b9c0();
    bool  FUN_00c0b770();
};

struct cCivilization
{
    uint32_t pad0[0x98 / 4];
    float    mF98;                  // +0x98
    uint32_t pad1[(0x430 - 0x9c) / 4];
    bool     mb430;                 // +0x430
    bool     mb431;                 // +0x431

    int                  FUN_00bf0c60(int a, int b, int c, int d);
    int                  FUN_00bf0cf0(int a, int b, int c);
    PtrVector<cCity>*    GetCities();   // 0x00bef6c0
};

struct cGameNounManager             // 0x00b3d300 result
{
    cHintTracker*          GetHintTracker();          // 0x00f67d90
    cAvatar*               GetAvatar();               // 0x00b1fdb0
    cCity*                 FUN_00b25c30();
    struct cCivilization*  GetPlayerCivilization();   // 0x00b25fb0
    struct cTribe*         GetPlayerTribe();          // 0x00bfc5f0
    PtrVector<cBuilding>*  FUN_00ae6030();
    PtrVector<struct cTribeNoun>* FUN_00ace2c0();
};

struct cSporeGuide { uint32_t pad[0x1c / 4]; bool mb1C; };
struct cGameTimeManager { uint32_t pad[0x48 / 4]; uint8_t mFlags48; };

struct cPosseSimulator
{
    int FUN_00d52df0();
    int FUN_00d52e10();
};

struct cValue14 { uint32_t pad[0x14 / 4]; float mF14; };

struct cAppSub
{
    PV8 PV4 PV2
    virtual int vf38();             // +0x38
};
struct cApp
{
    PV16 PV4
    virtual cAppSub* vf50();        // +0x50
};

struct cFlags_d2e340 { uint8_t pad[0xe]; bool mbE; bool mbF; bool mb10; };

// --- civ ---------------------------------------------------------------------------
struct cHintTarget                  // object reached through +0x80 / +0x5c / +0x20
{
    bool FUN_00d09660();
};

struct cCivPlanner { uint32_t pad[0x80 / 4]; cHintTarget* mp80; };

struct cCivModeStrategy
{
    cCivPlanner* FUN_00cf74f0();
    cBuilding*   FUN_00cf7d40(int i);
};

struct cTurnInfo { uint32_t pad[0xac / 4]; int mAC; int mB0; };

// --- tribe -------------------------------------------------------------------------
struct cTribeToolInfo { int mType; };

struct cTribeMemberSub { cTribeToolInfo* FUN_00bca2c0(); };

struct cTribeMember
{
    uint32_t         pad0[0xb4c / 4];
    cTribeMemberSub* mpB4C;         // +0xb4c
    uint32_t         pad1[(0xb58 - 0xb50) / 4];
    uint32_t         mFlagsB58;     // +0xb58

    int  FUN_00c22dc0();
    bool FUN_00c0bb90();
};

struct cTribeSub20c { float FUN_00cee380(); };

struct cTribeQuery { int a, b, c, mIndex, e; };

struct cTribe
{
    PV32 PV4
    virtual PtrVector<cTribeMember>* GetMembers();  // +0x90
    PV8 PV2
    virtual int vfa4();                             // +0xa4
    PV4 PV
    virtual PtrVector<void>* vfbc();                // +0xbc

    bool        FUN_00c8e850();
    bool        FUN_00c8e870();
    cTribeQuery FUN_00c8e890(int a, int b);
    void*       GetToolOfType(int type);            // 0x00c8f6e0
    cTribeSub20c* Sub20c() { return (cTribeSub20c*)((char*)this + 0x20c); }
};

struct cTribeNoun                    // 0x00ace2c0 element
{
    PV16 PV8 PV2 PV
    virtual struct cTribeNounSub* vf6c();           // +0x6c
};
struct cTribeNounSub { bool FUN_00bec860(); };

struct cTribePlan { uint32_t pad[0x5c / 4]; cHintTarget* mp5C; };

struct cTribeModeStrategy
{
    PV16 PV8 PV2
    virtual int        vf68();                      // +0x68
    PV
    virtual cTribePlan* vf70();                     // +0x70

    bool FUN_00cd6ef0(int i);
};

struct cTribeTable { uint32_t pad[0x38 / 4]; int m38; };

struct cToolGroup { bool FUN_00b6fa60(uint32_t id); };

// --- space -------------------------------------------------------------------------
struct cCargo
{
    PV16 PV4 PV2
    virtual float vf58();                           // +0x58
};

struct cInventoryItem
{
    PV4 PV2
    virtual int vf18();                             // +0x18
};

struct cPlayerInventory
{
    PV16 PV8 PV4 PV
    virtual bool vf74(const void* key);             // +0x74
    // non-virtual layout
    bool            FUN_00ff3bf0();
    cInventoryItem* FUN_00ff3f00();
};

// the vtable pointer of cPlayerInventory sits at +0, cargo at +0x508, float at +0x540
struct cPlayerInventoryLayout
{
    uint32_t pad0[0x508 / 4];
    cCargo   mCargo;                                // +0x508
    uint32_t pad1[(0x540 - 0x50c) / 4];
    float    mF540;                                 // +0x540
};

struct cSPSimulatorSpaceGame
{
    cPlayerInventory* GetPlayerInventory();         // 0x00a1ad60
};

struct cUFOSimulator
{
    cPlayerInventory* GetPlayerInventory();         // 0x00a1ad60 (same function)
    bool              FUN_00ffbfe0();
};

struct cSpaceGame
{
    uint32_t     pad[0x20 / 4];
    cHintTarget* mp20;                              // +0x20

    cPlayerInventory* GetPlayerInventory();         // 0x00a1ad60
};

struct cSPMission
{
    PV32 PV16 PV8 PV4 PV2
    virtual bool vff8();                            // +0xf8

    bool IsActive();                                // 0x00c44c80
    int  GetTargetPlanet();                         // 0x00970b30
};

struct cSPMissionFetch
{
    PV32 PV16 PV8 PV4 PV2
    virtual bool vff8();                            // +0xf8

    bool IsActive();                                // 0x00c44c80
};

struct cMissionExtra
{
    bool FUN_00c5f150();
    int  FUN_00c5f3b0();
    bool FUN_00c5f170();
};

struct cMissionTarget
{
    int  GetTargetPlanet();                         // 0x00970b30
    bool FUN_00c60af0();
    bool FUN_00c60cc0();
};

struct cMissionList { bool FUN_00c405e0(); };

struct cSPMissionManager
{
    int                     GetNumNonEventMissions(int a);
    cSPMission*             GetMissionByID(uint32_t id);
    PtrVector<cSPMission>*  GetMissionList();
    bool                    FUN_00feba70();
};

struct cEmpire
{
    int FUN_00c30c60();
    int FUN_00c30cb0();
};

struct cTerraformingManager { bool FUN_00bbe5c0(int a); };
struct cObj_b3d4a0 { bool FUN_00ae9390(); };
struct cObj_b3d4d0 { bool FUN_00ac80f0(); };
struct cObj_67caf0 { bool FUN_00678ed0(); };

// --- free functions ----------------------------------------------------------------
bool                  FUN_00de4380();
int                   SP_GetCurrentGameMode();                      // 0x00b5b800
cSporeGuide*          SP_SporeGuide();                              // 0x00401040
cGameTimeManager*     SP_GameTimeManager();                         // 0x00b3d380
cGameNounManager*     SP_NounManager();                             // 0x00b3d300
float                 FUN_00d2e360();
cPosseSimulator*      cPosseSimulator_Instance();                   // 0x00d539d0
cApp*                 SP_App();                                     // 0x0067dd10
cValue14*             FUN_00b60a50(int id);
cFlags_d2e340*        FUN_00d2e340();
cCivModeStrategy*     cCivModeStrategy_Get();                       // 0x00cf74c0
cTurnInfo*            FUN_00b26930();
cTribeModeStrategy*   cTribeModeStrategy_Instance();                // 0x00cd40b0
cToolGroup*           FUN_00cd3440();
cTribeTable*          FUN_00c9cec0(int i);
cSpaceGame*           SP_SpaceGameGet();                            // 0x01002bd0
cUFOSimulator*        SP_GetUFOSimulator();                         // 0x00ffbe50
int                   cSPLivingUniverse_GetUniverseContext();       // 0x01021080
cSPMissionManager*    SP_GetMissionManager();                       // 0x00feb9f0
cSPMissionFetch*      interface_cast_cSPMissionFetch(cSPMission* m);// 0x00c559c0
cMissionExtra*        FUN_00e07e30(cSPMission* m);
int                   cSPLivingUniverse_GetActivePlanetRecord();    // 0x010212a0
cMissionTarget*       FUN_00aed410(cSPMission* m);
int                   cSPLivingUniverse_GetActivePlanet();          // 0x01021260
cObj_b3d4a0*          FUN_00b3d4a0();
cEmpire*              cSPLivingUniverse_GetPlayerEmpire();          // 0x01021300
int                   FUN_01021240();
bool                  FUN_004eb930(int item, const void* key);
cTerraformingManager* SP_TerraformingManager();                     // 0x00b3d430
cMissionList*         FUN_00e07e50(cSPMission** pp);
cObj_b3d4d0*          FUN_00b3d4d0();
cObj_67caf0*          FUN_0067caf0();

extern float  DAT_01582e1c;
extern float  DAT_01687a10;
extern float* DAT_0169e35c;
extern const char k_interplanetarydrive_016a19b8[];
extern const char k_scan_016a1b20[];
extern const char k_abduct_016a1aa8[];

static inline cPlayerInventoryLayout* Layout(cPlayerInventory* p)
{
    return (cPlayerInventoryLayout*)p;
}

static inline bool IsTribeReady(cTribe* tribe)
{
    int          n     = tribe->vfa4();
    cTribeTable* table = FUN_00c9cec0(1);
    if ((unsigned)tribe->vfbc()->size() > 1)
        return true;
    return n >= table->m38;
}

// @ 0x00e07e70
bool GonzagoHintConditions(uint32_t condition)
{
    if (condition == 0xbb2129cd)
        return FUN_00de4380();

    if (condition == 0x29930bb7)
        return SP_GetCurrentGameMode() == kGameModeEditor;
    if (condition == 0x3d97a8ef)
        return SP_GetCurrentGameMode() == kGameModeCell;
    if (condition == 0x2b978c55)
        return SP_GetCurrentGameMode() == kGameModeCreature;
    if (condition == 0x256ca1de)
        return SP_GetCurrentGameMode() == kGameModeTribe;
    if (condition == 0x27978581)
        return SP_GetCurrentGameMode() == kGameModeCiv;
    if (condition == 0x297079fb)
        return SP_GetCurrentGameMode() == kGameModeSpace;

    if (condition == 0x3158bf4f)
    {
        if (SP_SporeGuide()->mb1C)
            SP_NounManager()->GetHintTracker()->MarkDone(0x52da204);
        return SP_NounManager()->GetHintTracker()->IsDone(0x52da204);
    }
    if (condition == 0xadfcd351)
    {
        if (SP_GameTimeManager()->mFlags48 & 1)
            SP_NounManager()->GetHintTracker()->MarkDone(0x52da205);
        return SP_NounManager()->GetHintTracker()->IsDone(0x52da205);
    }
    if (condition == 0xbc8e7902)
        return false;

    // ---------------------------------------------------------------- creature stage
    if (SP_GetCurrentGameMode() == kGameModeCreature)
    {
        if (condition == 0x3481f823)
            return false;
        if (condition == 0xab5783e0)
        {
            cAvatar* avatar = SP_NounManager()->GetAvatar();
            if (!(avatar->mSub5a8.FUN_00bfc490() >= DAT_01582e1c))
                return false;
            if (avatar->mbFlagB5E)
                return false;
            return true;
        }
        if (condition == 0x3e79c333)
        {
            cAvatar* avatar = SP_NounManager()->GetAvatar();
            if (!(avatar->FUN_00c0b9c0() < DAT_01687a10))
                return false;
            if (avatar->mbFlagB5E)
                return false;
            return true;
        }
        if (condition == 0x9c9ee7b8)
        {
            cAvatar*     avatar    = SP_NounManager()->GetAvatar();
            const float& threshold = *DAT_0169e35c;
            if (!(FUN_00d2e360() >= threshold))
                return false;
            if (!avatar->FUN_00c0b770())
                return false;
            if (avatar->mbFlagB5E)
                return false;
            return true;
        }
        if (condition == 0x25ef4c2b)
            return SP_NounManager()->GetHintTracker()->IsDone(0x52da1fe);
        if (condition == 0xeef27c1c)
        {
            cPosseSimulator* posse = cPosseSimulator_Instance();
            return posse->FUN_00d52df0() == posse->FUN_00d52e10();
        }
        if (condition == 0x3c848fbf)
            return cPosseSimulator_Instance()->FUN_00d52e10() > 0;
        if (condition == 0xfea3ff33)
            return cPosseSimulator_Instance()->FUN_00d52df0() > 0;
        if (condition == 0x47298c4b)
        {
            cValue14* v = FUN_00b60a50(SP_App()->vf50()->vf38());
            if (v == 0)
                return false;
            if (v->mF14 > 25.0f)
                return true;
            return false;
        }
        if (condition == 0xd3df9e3f)
            return FUN_00d2e340()->mbE || FUN_00d2e340()->mb10;
    }

    // ---------------------------------------------------------------- civ stage
    if (SP_GetCurrentGameMode() == kGameModeCiv)
    {
        if (condition == 0x3481f823)
            return false;
        if (condition == 0x48e18de8)
            return cCivModeStrategy_Get()->FUN_00cf74f0()->mp80->FUN_00d09660();
        if (condition == 0x556bb739)
            return false;
        if (condition == 0xec28a285)
        {
            cBuilding* b = cCivModeStrategy_Get()->FUN_00cf7d40(0);
            return b && b->mIface.IsQuery48();
        }
        if (condition == 0xd436d975)
        {
            cCity* city = SP_NounManager()->FUN_00b25c30();
            if (city == 0)
                return false;
            if (!city->GetCityHall()->mIface.IsQuery48())
                return false;
            return true;
        }
        if (condition == 0x8788c629)
        {
            cCity* city = SP_NounManager()->FUN_00b25c30();
            if (city == 0)
                return false;
            if (!city->FUN_00bd7df0())
                return false;
            return true;
        }
        if (condition == 0x70ca6ada)
        {
            cCity* city = SP_NounManager()->FUN_00b25c30();
            if (city == 0)
                return false;
            if (city->FUN_00bd7df0())
                return false;
            return true;
        }
        if (condition == 0xb6dfbff2)
        {
            PtrVector<cBuilding>* buildings = SP_NounManager()->FUN_00ae6030();
            int n = buildings->size();
            for (int i = 0; i < n; i++)
            {
                if (buildings->mpBegin[i]->mIface.IsQuery48())
                    return true;
            }
            return false;
        }
        if (condition == 0x5fd1f4b5)
            return SP_NounManager()->GetPlayerCivilization()->mb430;
        if (condition == 0xef0ba57a)
            return SP_NounManager()->GetPlayerCivilization()->mb431;
        if (condition == 0x9625df47)
            return SP_NounManager()->GetPlayerCivilization()->FUN_00bf0c60(0, -1, -1, 0) > 0;
        if (condition == 0xd13264ed)
            return SP_NounManager()->GetPlayerCivilization()->FUN_00bf0c60(2, -1, -1, 0) > 0;
        if (condition == 0x7bac62f1)
            return SP_NounManager()->GetPlayerCivilization()->FUN_00bf0c60(1, -1, -1, 0) > 0;
        if (condition == 0xc480a83c)
            return SP_NounManager()->GetPlayerCivilization()->FUN_00bf0cf0(0, -1, -1) > 0;
        if (condition == 0x87775c72)
            return SP_NounManager()->GetPlayerCivilization()->FUN_00bf0cf0(2, -1, -1) > 0;
        if (condition == 0x14c89726)
            return SP_NounManager()->GetPlayerCivilization()->FUN_00bf0cf0(1, -1, -1) > 0;
        if (condition == 0xf302fa1e)
        {
            cBuilding* b = cCivModeStrategy_Get()->FUN_00cf7d40(0);
            if (b && b->mIface.IsQuery50())
                SP_NounManager()->GetHintTracker()->MarkDone(0x5300aea);
            return SP_NounManager()->GetHintTracker()->IsDone(0x5300aea);
        }
        if (condition == 0xb815d50d)
            return SP_NounManager()->GetPlayerCivilization()->mF98 > 100.0f;
        if (condition == 0x91531c40)
            return SP_NounManager()->GetHintTracker()->IsDone(0x52da1f4);
        if (condition == 0x622cbb2a)
            return SP_NounManager()->GetHintTracker()->IsDone(0x52da1f5);
        if (condition == 0x79de641e)
            return SP_NounManager()->GetHintTracker()->IsDone(0x566493f);
        if (condition == 0x0696e746)
            return SP_NounManager()->GetHintTracker()->IsDone(0x566492c);
        if (condition == 0xde91118c)
            return SP_NounManager()->GetHintTracker()->IsDone(0x52da1f6);
        if (condition == 0xf6f4b4ed)
        {
            cCivilization* civ = SP_NounManager()->GetPlayerCivilization();
            if (civ == 0)
                return false;
            PtrVector<cCity>* cities = civ->GetCities();
            for (cCity** it = cities->mpBegin, **end = cities->mpEnd; it != end; ++it)
            {
                cCity* city = *it;
                if (city->FUN_00c004c0(0) || city->FUN_00c004c0(1))
                {
                    if (!city->GetCityHall()->mIface.IsQuery48())
                        return true;
                }
            }
            return false;
        }
        if (condition == 0xd69adad0)
            return SP_NounManager()->GetHintTracker()->IsDone(0x52da1f2);
        if (condition == 0x72598a58)
            return SP_NounManager()->GetHintTracker()->IsDone(0x52da1f8);
        if (condition == 0x3682aad8)
            return SP_NounManager()->GetHintTracker()->IsDone(0x52da1f9);
        if (condition == 0xff24a90d)
            return SP_NounManager()->GetPlayerCivilization()->GetCities()->size() == 1;
        if (condition == 0xd349682d)
            return FUN_00b26930()->mB0 < FUN_00b26930()->mAC - 1;
    }

    // ---------------------------------------------------------------- tribe stage
    if (SP_GetCurrentGameMode() == kGameModeTribe)
    {
        cHintTracker* hints = SP_NounManager()->GetHintTracker();

        if (condition == 0x3481f823)
            return false;
        if (condition == 0x48e18de8)
            return cTribeModeStrategy_Instance()->vf70()->mp5C->FUN_00d09660();
        if (condition == 0x061e0a7b)
            return SP_NounManager()->GetPlayerTribe()->Sub20c()->FUN_00cee380() > 0.0f;
        if (condition == 0x7e62ec64)
            return !hints->IsDone(0x56d1871);
        if (condition == 0x275737b5)
            return hints->IsDone(0x64c010f);
        if (condition == 0x97b16dd9)
            return hints->IsDone(0x53203528);
        if (condition == 0xd8f723f7)
            return hints->IsDone(0x83861976);
        if (condition == 0xc2ead12b)
            return hints->IsDone(0x64d44f9);
        if (condition == 0x35a01971)
            return hints->IsDone(0x64e70b3);
        if (condition == 0x75b7cd30)
            return hints->IsDone(0x5ac72d7c);
        if (condition == 0x1dec9c9a)
            return hints->IsDone(0x14363974);
        if (condition == 0xbd713587)
        {
            cTribe* tribe = SP_NounManager()->GetPlayerTribe();
            bool    b850  = tribe->FUN_00c8e850();
            bool    b870  = tribe->FUN_00c8e870();
            PtrVector<cTribeMember>* members = tribe->GetMembers();
            for (cTribeMember** it = members->mpBegin, **end = members->mpEnd; it != end; ++it)
            {
                cTribeToolInfo* tool = (*it)->mpB4C->FUN_00bca2c0();
                if (tool == 0)
                    continue;
                switch (tool->mType)
                {
                case 1:
                    return true;
                case 2:
                    if (b850)
                        return true;
                    break;
                case 10:
                case 27:
                    if (b870)
                        return true;
                    break;
                }
            }
            return false;
        }
        if (condition == 0x4d0dcd7b)
        {
            bool a = FUN_00cd3440()->FUN_00b6fa60(0x391c432);
            bool b = FUN_00cd3440()->FUN_00b6fa60(0x69ba7f0d);
            bool c = FUN_00cd3440()->FUN_00b6fa60(0x2d99d0b);
            return a || b || c;
        }
        if (condition == 0xc51300e7)
            return IsTribeReady(SP_NounManager()->GetPlayerTribe());
        if (condition == 0x0f413a4d)
            return (unsigned)SP_NounManager()->GetPlayerTribe()->vfbc()->size() > 1;
        if (condition == 0x6a1c27ee)
        {
            PtrVector<cTribeMember>* members = SP_NounManager()->GetPlayerTribe()->GetMembers();
            for (cTribeMember** it = members->mpBegin, **end = members->mpEnd; it != end; ++it)
            {
                if ((*it)->FUN_00c22dc0())
                    return true;
            }
            return false;
        }
        if (condition == 0xef287d3d)
            return cTribeModeStrategy_Instance()->vf68() > 0;
        if (condition == 0x0faa7e34)
            return SP_NounManager()->GetPlayerTribe()->FUN_00c8e890(9, 0).mIndex != -1;
        if (condition == 0x63ea4966)
            return hints->IsDone(0x11ade9ce);
        if (condition == 0x9cbaa90a)
        {
            PtrVector<cTribeMember>* members = SP_NounManager()->GetPlayerTribe()->GetMembers();
            for (cTribeMember** it = members->mpBegin; it != members->mpEnd; ++it)
            {
                if (((*it)->mFlagsB58 >> 4) & 1)
                    return true;
            }
            return false;
        }
        if (condition == 0x5fb54387)
            return SP_NounManager()->GetPlayerTribe()->GetToolOfType(9) != 0;
        if (condition == 0x7f13dd2c)
            return cTribeModeStrategy_Instance()->FUN_00cd6ef0(9);
        if (condition == 0xfc5f4372)
        {
            PtrVector<cTribeMember>* members = SP_NounManager()->GetPlayerTribe()->GetMembers();
            for (cTribeMember** it = members->mpBegin, **end = members->mpEnd; it != end; ++it)
            {
                if ((*it)->FUN_00c0bb90())
                    return true;
            }
            return false;
        }
        if (condition == 0xa28a67e8)
            return SP_NounManager()->GetPlayerTribe()->FUN_00c8e870();
        if (condition == 0x2dfb4f9f)
            return SP_NounManager()->GetPlayerTribe()->FUN_00c8e850();

        uint32_t hintId;
        if (condition == 0x95336dd4)
            hintId = 0x55e9382;
        else if (condition == 0x28090349)
            hintId = 0x55e9383;
        else if (condition == 0x7208a087)
            hintId = 0x55e9384;
        else
            goto notTribe;

        if (hints->IsDone(hintId))
            return true;
        if (IsTribeReady(SP_NounManager()->GetPlayerTribe()))
            return true;
        return false;
    }
notTribe:

    // ---------------------------------------------------------------- space stage
    if (SP_GetCurrentGameMode() != kGameModeSpace)
        return false;

    uint32_t hintId;
    switch (0) { default:
    if (condition == 0x3481f823)
        return SP_SpaceGameGet()->mp20->FUN_00d09660();
    if (condition == 0x54f013a4)
    {
        cPlayerInventoryLayout* inv  = Layout(SP_GetUFOSimulator()->GetPlayerInventory());
        float                   have = Layout(SP_GetUFOSimulator()->GetPlayerInventory())->mF540;
        return inv->mCargo.vf58() * 0.33333334f > have;
    }
    if (condition == 0x0deeb47e)
    {
        cPlayerInventoryLayout* inv  = Layout(SP_GetUFOSimulator()->GetPlayerInventory());
        float                   have = Layout(SP_GetUFOSimulator()->GetPlayerInventory())->mF540;
        return have == inv->mCargo.vf58();
    }
    if (condition == 0xd6ffef0b)
        return cSPLivingUniverse_GetUniverseContext() == 1;
    if (condition == 0xaeb1d92e)
        return cSPLivingUniverse_GetUniverseContext() == 2;
    if (condition == 0x42e2f55c)
        return cSPLivingUniverse_GetUniverseContext() == 0;
    if (condition == 0x955b074a) { hintId = 0x563843a; break; }
    if (condition == 0x01268402)
        return SP_GetMissionManager()->GetNumNonEventMissions(0) > 0;
    if (condition == 0x5defa826)
        return SP_SpaceGameGet()->GetPlayerInventory()->FUN_00ff3bf0();
    if (condition == 0x86f36f23)
        return SP_SpaceGameGet()->GetPlayerInventory()->vf74(k_interplanetarydrive_016a19b8);
    if (condition == 0x06cbf2fd) { hintId = 0x56e2b87; break; }
    if (condition == 0x4e29c875)
    {
        cSPMission* m = SP_GetMissionManager()->GetMissionByID(0xfe773af7);
        return m && m->IsActive();
    }

    {
        uint32_t missionId;
        if (condition == 0x470530d6)
            missionId = 0x89238409;
        else if (condition == 0x451b77d8)
            missionId = 0xbb448992;
        else if (condition == 0x91f48b8f)
            missionId = 0x509cc23f;
        else if (condition == 0xe34b36e8)
            missionId = 0xfdfda2a0;
        else
            goto notActiveNotDone;
        // mission active and not yet finished
        cSPMission* m = SP_GetMissionManager()->GetMissionByID(missionId);
        return m && m->IsActive() && !m->vff8();
    }
notActiveNotDone:
    {
        uint32_t missionId;
        if (condition == 0x27280957)
            missionId = 0x89238409;
        else if (condition == 0xd515e82b)
            missionId = 0xbb448992;
        else if (condition == 0xc0a1abbc)
            missionId = 0x509cc23f;
        else if (condition == 0x436f3e21)
            missionId = 0xfdfda2a0;
        else
            goto notActiveDone;
        // mission active and finished
        cSPMission* m = SP_GetMissionManager()->GetMissionByID(missionId);
        return m && m->IsActive() && m->vff8();
    }
notActiveDone:
    if (condition == 0xdf4bf1f1)
    {
        cSPMission* m = SP_GetMissionManager()->GetMissionByID(0xbb448992);
        if (m == 0)
            return false;
        cSPMissionFetch* fetch = interface_cast_cSPMissionFetch(m);
        return fetch && fetch->IsActive() &&
               (fetch->vff8() || *(int*)((char*)fetch + 0x1f0) == 1);
    }
    if (condition == 0xb0bac452)
    {
        cSPMission* m = SP_GetMissionManager()->GetMissionByID(0xbb448992);
        if (m == 0)
            return false;
        cSPMissionFetch* fetch = interface_cast_cSPMissionFetch(m);
        if (fetch == 0)
            return false;
        return fetch->IsActive() && !fetch->vff8() && *(int*)((char*)fetch + 0x1f0) == 1;
    }
    if (condition == 0x19d15449)
    {
        cSPMission* m = SP_GetMissionManager()->GetMissionByID(0xfe773af7);
        return m && m->vff8();
    }
    if (condition == 0xfe0d4443)
        return SP_GetMissionManager()->FUN_00feba70();
    if (condition == 0xfb2784de)
    {
        cSPMission* m = SP_GetMissionManager()->GetMissionByID(0x7bdbb97d);
        if (m == 0)
            return false;
        cMissionExtra* extra = FUN_00e07e30(m);
        if (extra == 0)
            return false;
        return extra->FUN_00c5f150() &&
               extra->FUN_00c5f3b0() == cSPLivingUniverse_GetActivePlanetRecord();
    }
    if (condition == 0xa30bda29)
    {
        cSPMission* m = SP_GetMissionManager()->GetMissionByID(0x7bdbb97d);
        if (m == 0)
            return false;
        cMissionExtra* extra = FUN_00e07e30(m);
        if (extra == 0)
            return false;
        return extra->FUN_00c5f170();
    }
    if (condition == 0xe90651e7)
    {
        cSPMission* m = SP_GetMissionManager()->GetMissionByID(0xd85005e9);
        if (m == 0)
            return false;
        cMissionTarget* t = FUN_00aed410(m);
        if (t == 0)
            return false;
        return cSPLivingUniverse_GetUniverseContext() == 0 &&
               t->GetTargetPlanet() == cSPLivingUniverse_GetActivePlanet() &&
               t->FUN_00c60af0();
    }
    if (condition == 0x3d02ae50)
    {
        cSPMission* m = SP_GetMissionManager()->GetMissionByID(0xd85005e9);
        if (m == 0)
            return false;
        cMissionTarget* t = FUN_00aed410(m);
        if (t == 0)
            return false;
        return cSPLivingUniverse_GetUniverseContext() == 0 &&
               t->GetTargetPlanet() == cSPLivingUniverse_GetActivePlanet() &&
               t->FUN_00c60cc0();
    }
    if (condition == 0x393b7089)
        return FUN_00b3d4a0()->FUN_00ae9390();
    if (condition == 0x4adce397)
    {
        PtrVector<cSPMission>* missions = SP_GetMissionManager()->GetMissionList();
        for (cSPMission** it = missions->mpBegin, **end = missions->mpEnd; it != end; ++it)
        {
            if (*it && (*it)->GetTargetPlanet() == cSPLivingUniverse_GetActivePlanet())
                return true;
        }
        return false;
    }
    if (condition == 0x9edf5003) { hintId = 0x56e2b88; break; }
    if (condition == 0x5d8f3346)
    {
        int n = cSPLivingUniverse_GetPlayerEmpire()->FUN_00c30c60();
        return FUN_01021240() != n;
    }
    if (condition == 0x603d1d36) { hintId = 0x5638438; break; }
    if (condition == 0xb143fed9) { hintId = 0x5638439; break; }
    if (condition == 0x5dad999e) { hintId = 0x52f172d; break; }
    if (condition == 0xedb4ed03)
    {
        cInventoryItem* item = SP_SpaceGameGet()->GetPlayerInventory()->FUN_00ff3f00();
        return item && FUN_004eb930(item->vf18(), k_scan_016a1b20);
    }
    if (condition == 0xff704845)
    {
        cInventoryItem* item = SP_SpaceGameGet()->GetPlayerInventory()->FUN_00ff3f00();
        return item && FUN_004eb930(item->vf18(), k_abduct_016a1aa8);
    }
    if (condition == 0xed752383)
    {
        PtrVector<cTribeNoun>* nouns = SP_NounManager()->FUN_00ace2c0();
        for (cTribeNoun** it = nouns->mpBegin; it != nouns->mpEnd; ++it)
        {
            if ((*it)->vf6c()->FUN_00bec860())
                return true;
        }
        return false;
    }
    if (condition == 0x12034974)
        return false;
    if (condition == 0xf935c428)
        return SP_TerraformingManager()->FUN_00bbe5c0(0);
    if (condition == 0xb0c6e178) { hintId = 0x56d1872; break; }
    if (condition == 0xa749726f) { hintId = 0x56d1873; break; }
    if (condition == 0x655be05d) { hintId = 0x56d1874; break; }
    if (condition == 0x7ed25ea7) { hintId = 0x574ac66; break; }
    if (condition == 0xfab78e4b) { hintId = 0x574ac68; break; }
    if (condition == 0x383e4d29) { hintId = 0x574ac67; break; }
    if (condition == 0x793012a5) { hintId = 0x574ac69; break; }
    if (condition == 0x9b0dce32) { hintId = 0x574ac6a; break; }
    if (condition == 0x07af254b) { hintId = 0x57f6a86; break; }
    if (condition == 0x41ea7a72)
        return SP_GetUFOSimulator()->FUN_00ffbfe0();
    if (condition == 0x081e4b7d) { hintId = 0x5c2d1ab; break; }
    if (condition == 0x5d7c8660)
        return cSPLivingUniverse_GetPlayerEmpire()->FUN_00c30cb0() <= 0;
    if (condition == 0xb815d50d)
        return cSPLivingUniverse_GetPlayerEmpire()->FUN_00c30cb0() > 0;
    if (condition == 0xa44acc08)
    {
        PtrVector<cSPMission>* missions = SP_GetMissionManager()->GetMissionList();
        int n = missions->size();
        for (int i = 0; i < n; i++)
        {
            cMissionList* l = FUN_00e07e50(&missions->mpBegin[i]);
            if (l)
                return l->FUN_00c405e0();
        }
        return false;
    }
    if (condition == 0x2b620b6b)
        return !FUN_00b3d4d0()->FUN_00ac80f0();
    if (condition == 0x0a938a38)
        return FUN_0067caf0()->FUN_00678ed0();
    return false;
    }

    return SP_NounManager()->GetHintTracker()->IsDone(hintId);
}
