// Slice s00d377f0 -- 0x00d377f0 .. 0x00d38900 (25 functions).
//
// This translation unit holds the scenario-edit input strategy, the creature mission manager
// and a handful of anonymous-namespace helpers:
//
//   * SP::Simulator::cScenarioEditModeInputStrategy (derived retail vtbl 0x147a8b4 over the base
//     vtbl 0x14771e0): the teardown (00d377f0), the constructor (00d37970) and the destructor
//     (00d37b60).  The class carries two small eastl int-keyed rbtrees (+0x04 and +0x20), a
//     cSPUILayoutManager-style rbtree (+0x6c), an EA::Messaging handler (+0x88), a cGonzagoTimer
//     (+0xa0) and a pair of cSPVector3 (+0xc8 / +0xd4).
//
//   * SP::cSPCreatureMissionManager (retail vtbls 0x147a96c / 0x147a948 / 0x147a938): ctor,
//     Write/Read, the nest-mission card helpers, the per-tick update and the dead-noun sweep.
//     The retail object is four bytes wider than the dev PDB type, so the base fields live at
//     +0x14 (mission list), +0x28 (uint hash_map), +0x48 (ResourceMan::Key hash_map),
//     +0x68 / +0x6c (displayed missions), +0x70 (dirty flag), and the derived fields at
//     +0x74 (nest mission), +0x78 (nest flag) and +0x7c (species mission).
//
//   * The anonymous helpers: the space-point progress query (00d386a0), its icon selector
//     (00d38780), MarkEventAsOccurred (00d387c0), cCreatureLevelUpScenario::EvaluateEvent
//     (00d38800) and the small input-manager forwarding thunks.
//
// Every field below is named by the role its offset plays in this slice; the offsets come from
// the disassembly, not from the dev PDB (which is wider/narrower at several places).
//
// Flags: /O2 /MD /Gy /TP

#include "types.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

// ---------------------------------------------------------------------------------------------
// small shared types
// ---------------------------------------------------------------------------------------------
struct cSPVector3 { float x, y, z; };

struct RectT_M { u32 a, b, c; };

// -- vtable dispatch shorthands ----------------------------------------------------------------
typedef void  (__thiscall *FnV0)(void*);
typedef void* (__thiscall *FnP0)(void*);
typedef int   (__thiscall *FnI0)(void*);
typedef bool  (__thiscall *FnB0)(void*);
typedef void  (__thiscall *FnVI0)(void*, int);
typedef void  (__thiscall *FnVV0)(void*, void*);
typedef void* (__thiscall *FnPP0)(void*, void*);
typedef void  (__thiscall *FnVIFFI)(void*, int, float, float, int);
static inline void** VTBL(void* p) { return *(void***)p; }

// ---------------------------------------------------------------------------------------------
// external helpers (cdecl / free functions)
// ---------------------------------------------------------------------------------------------
extern "C" void* __cdecl X_NounManager();                      // 0x00b3d300
extern "C" void* __cdecl X_GameInputManager();                 // 0x00b3d250
extern "C" void* __cdecl X_GetCardPanel();                     // 0x00b3d400
extern "C" void* __cdecl X_GlobalGet();                        // 0x00b3d410
extern "C" void* __cdecl X_CreatureModeStrategy_Instance();    // 0x00d38840
extern "C" void* __cdecl X_FUN_00d99500(void*);                // 0x00d99500
extern "C" void* __cdecl X_RBTreeIncrement(void*);             // 0x00921580
extern "C" void  __cdecl X_FUN_00829110(void*, void*, void*, void*, void*); // 0x00829110
extern "C" void  __cdecl X_FUN_00f47380(void*);                // 0x00f47380  operator_delete
extern "C" void  __cdecl X_RemoveHandler(void*, u32, u32, u32, u32);         // 0x00571db0
extern "C" bool  __cdecl X_WriteUint32(void*, const void*, int, int);        // 0x0093aa70
extern "C" bool  __cdecl X_ReadInt32(void*, void*, int, int);                // 0x0093a780
extern "C" void* __cdecl X_FUN_00b6f4f0(void*, void*, void*, void*);         // 0x00b6f4f0

// ---------------------------------------------------------------------------------------------
// globals addressed by the slice
// ---------------------------------------------------------------------------------------------
extern cSPVector3 g_vDefault_169e17c;      // 0x00169e17c   default (x,y,z) copied twice in the ctor
extern float g_len1582e38[4];              // 0x001582e38   length-distribution bounds
extern const float g_kNegOne;              // 0x0013eb1bc   -1.0f
extern const float g_kOne;                 // 0x001485720    1.0f
extern const float g_thirdPlus;            // 0x0013f26dc    0.33333334f
extern const float g_thirdMinus;           // 0x00140d0cc   -0.33333334f
extern u8* g_sTestSystem;                  // 0x0015fd928

// ---------------------------------------------------------------------------------------------
// the manager-aware classes used only for this file
// ---------------------------------------------------------------------------------------------
struct NounVec {                           // cGameNounManager::GetGameDataVector result
    u32   mField00;                        // +0x00
    void** mpBegin;                        // +0x04
    void** mpEnd;                          // +0x08
    u32   mField0c;                        // +0x0c
    u32   mField10;                        // +0x10
};

struct PtrVec {                            // local eastl vector<void*> used by the sweep
    void** mpBegin;                        // +0x00
    void** mpEnd;                          // +0x04
    void** mpCapacity;                     // +0x08
    void ctor(u32 n, void* src);           // 0x00b93c60
};

struct HashTable {                         // eastl hash_map sub-object
    u32   mField00;                        // +0x00
    u32*  mpBuckets;                       // +0x04
    u32   mBucketCount;                    // +0x08
    u32   mSize;                           // +0x0c
    u32   mField10;                        // +0x10
    u32   mField14;                        // +0x14
    u32   mField18;                        // +0x18
    u32   mField1c;                        // +0x1c
    void  Find(void* outIter, void* key);  // 0x00833840
    void* FUN_d380c0(u32* key);            // 0x00d380c0  find-or-insert, returns &value
    int   Erase(u32* key);                 // 0x00d37fe0
    int   EraseU32(u32* key);              // 0x00b6faa0
    void  FUN_b6fe40(void*, void*, void*);// 0x00b6fe40
};

struct HashTableU32 {                      // eastl hash_map<uint> sub-object (0x1c bytes)
    u32   mField00;                        // +0x00
    u32*  mpBuckets;                       // +0x04
    u32   mBucketCount;                    // +0x08
    u32   mSize;                           // +0x0c
    u32   mField10;                        // +0x10
    u32   mField14;                        // +0x14
    u32   mField18;                        // +0x18
    int   EraseU32(void* key);             // 0x00b6faa0
};

struct ARCList {                           // eastl vector<AutoRefCount<mission>>
    void* mpBegin;                         // +0x00
    void* mpEnd;                           // +0x04
    void* mpCapacity;                      // +0x08
    void* Erase(void* first, void* last);  // 0x00e25bd0
    void  PushBack(void* value);           // 0x00e1c7f0
};

struct ModelVec {                          // eastl vector<AutoRefCount<cMWModel>>
    void* mpBegin;                         // +0x00
    void* mpEnd;                           // +0x04
    void* mpCapacity;                      // +0x08
    void  DoDestroyValues(void*, void*);   // 0x005f3680
};

struct cMission {                          // the mission object held by an AutoRefCount
    bool  FUN_c2f300();                    // 0x00c2f300
    void  FUN_c2fc80();                    // 0x00c2fc80
    void  FUN_c2fc10();                    // 0x00c2fc10
    void  FUN_c2ebc0();                    // 0x00c2ebc0
    void* FUN_c2e7a0();                    // 0x00c2e7a0  mission key
    void* FUN_c2e780();                    // 0x00c2e780  species profile
    void  FUN_c30100(u32);                 // 0x00c30100  cSPCreatureNestMission::Init
    void  FUN_c301c0(void*);               // 0x00c301c0
};

struct cARC {                              // EA::AutoRefCount<mission>
    void* mpObj;                           // +0x00
    cARC* Assign(void* p);                 // 0x00b5f950
    void  FUN_ac9480(cARC* src);           // 0x00ac9480
    void  FUN_572660(void* p);             // 0x00572660  AutoRefCount ctor
};

struct cGameNounManager {
    void*     GetAvatar();                                     // 0x00b1fdb0
    void*     CreateNoun(u32 typeID);                          // 0x00b20c60
    void      RemoveNoun(void* noun);                          // 0x00b225d0
    NounVec*  GetGameDataVector(u32,u32,u32,u32,u32);          // 0x00b21340
};

struct cTerrainEditor {
    void* GetCurrentTerrainSphere();                           // 0x00f67d90
};

struct cTerrainSphere {
    u32 mField0000;
    u8  mPad0004[0x10e8 - 4];
    void* mpSomething10e8;                 // +0x10e8
    float FUN_c75680(int which);           // 0x00c75680
    void  FUN_c78420(void* event);         // 0x00c78420
    bool  FUN_00594330();                  // 0x00594330
};

struct cMissionCardPanel {
    void RemoveMissionCard(void* mission);                     // 0x00e17fb0
    void SetupMissionCard(void* mission, int a, int b, int c); // 0x00e18200
    void ExpandMissionCard(int);                               // 0x00e15b90
    void CollapseMissionCard(void* mission);                   // 0x00e15c00
    void SetPanelArea(RectT_M area);                           // 0x00e14d00
};

struct cCreatureBase {                     // cSPCreatureBase / cGameData-derived
    u8  mPad0000[0xb28];
    u32 mSpeciesKey_b28;                   // +0xb28  (ResourceMan::Key)
    u32 mSpeciesKey_b2c;                   // +0xb2c
    u32 mSpeciesKey_b30;                   // +0xb30
    void* ApplyCombatTarget();             // 0x00c0ee90
    bool  Flag388();                       // 0x00c0c0e0
    void* GetSpeciesProfile();             // 0x00c0bbd0
};

struct Cls_e3f7a0 {                       // global object, adds a timer fraction
    float F(u32 event);                    // 0x00e3f7a0
};

struct cVarListSerializer {
    u8   mData[0xa14];
    void Ctor(void* pObject, void* pVarList, u32 signature);   // 0x00692f90
    bool SerializeWrite(void* stream);                         // 0x00692900
    bool SerializeRead(void* stream);                          // 0x00693e10
};

struct RBTree {                            // eastl int-keyed rbtree  (0x18 bytes)
    void* mParent;                         // +0x00
    void* mSelf;                           // +0x04
    void* mEnd;                            // +0x08
    void* mCount;                          // +0x0c
    u8    mFlag;                           // +0x10
    u32   mField14;                        // +0x14
    void FUN_b1b830(void* value);          // 0x00b1b830
    void FUN_e4b990(void* value);          // 0x00e4b990
    void DoNukeSubtree(void* node);        // 0x009a9600
};

struct cGonzagoTimer {
    u32 mData[8];
    void Ctor();                           // 0x00b63890
    void Dtor();                           // 0x00b638b0
};

// =============================================================================================
// SP::Simulator::cScenarioEditModeInputStrategy
// =============================================================================================
class cCreatureModeInputStrategy {
public:
    void CleanUpCreatureHitBoxes();        // 0x00d34230
};

class cScenarioEditModeInputStrategy : public cCreatureModeInputStrategy {
public:
    void*  mpVtbl;                         // +0x00
    RBTree mTree4;                         // +0x04
    u32    mField1c;                       // +0x1c
    RBTree mTree20;                        // +0x20
    u32    mField38;                       // +0x38
    void*  mpSubVtbl3c;                    // +0x3c
    u32    mField40;                       // +0x40
    void*  mpSubVtbl44;                    // +0x44
    void*  mpSubVtbl48;                    // +0x48
    void*  mpSubVtbl4c;                    // +0x4c
    u32    mField50;                       // +0x50
    u8     mFlag54;                        // +0x54
    u8     mPad55[3];                      // +0x55
    u32    mField58;                       // +0x58
    u32    mField5c;                       // +0x5c
    u32    mField60;                       // +0x60
    u32    mField64;                       // +0x64
    u32    mField68;                       // +0x68
    RBTree mTree6c;                        // +0x6c
    u32    mField84;                       // +0x84
    void*  mpHandler88;                    // +0x88
    u32    mHandler8c;                     // +0x8c
    u32    mHandler90;                     // +0x90
    u32    mHandler94;                     // +0x94
    u32    mHandler98;                     // +0x98
    u32    mField9c;                       // +0x9c
    cGonzagoTimer mTimerA0;                // +0xa0
    u8     mFlagC0;                        // +0xc0
    u8     mFlagC1;                        // +0xc1
    u8     mPadC2[2];                      // +0xc2
    void*  mpObjC4;                        // +0xc4
    cSPVector3 mVecC8;                     // +0xc8
    cSPVector3 mVecD4;                     // +0xd4
    void*  mpObjE0;                        // +0xe0
    u32    mFieldE4;                       // +0xe4
    u32    mFieldE8;                       // +0xe8
    u32    mFieldEc;                       // +0xec
    void*  mpObjF0;                        // +0xf0
    void*  mpObjF4;                        // +0xf4
    u32    mFieldF8;                       // +0xf8
    u8     mFlagFc;                        // +0xfc
    u8     mPadFd[3];                      // +0xfd
    float  mFloat100;                      // +0x100
    u8     mFlag104;                       // +0x104
    u8     mFlag105;                       // +0x105
    u8     mFlag106;                       // +0x106
public:
    void  CleanUp();                                    // 0x00d377f0
    cScenarioEditModeInputStrategy* Construct();        // 0x00d37970
    void  Destroy();                                    // 0x00d37b60
};

// =============================================================================================
// SP::cSPCreatureMissionManager
// =============================================================================================
extern void* g_CreatureMissionManager;     // 0x00169e230

class cSPMissionManagerBase {
public:
    void  InitBase();                          // 0x00b70820   base ctor
    void  TermBase();                          // 0x00b705a0   base dtor
    bool  WriteBase(void* stream);             // 0x00b6f570
    bool  ReadBase(void* stream);              // 0x00b6f5e0
    void  RefreshCards();                      // 0x00b6f760
    void  FUN_b70070();                        // 0x00b70070
    bool  IsTrackedBase(void* p);              // 0x00b6f800
    void  NotifyAll();                         // 0x00b6f7d0
    void  FUN_b6f650(void* a, void* b);        // 0x00b6f650
};

class cSPCreatureMissionManager : public cSPMissionManagerBase {
public:
    void*  mpVtbl00;                       // +0x00
    u32    mField04;                       // +0x04
    void*  mpVtbl08;                       // +0x08
    u32    mField0c;                       // +0x0c
    void*  mpVtbl10;                       // +0x10
    ARCList mMissionList;                  // +0x14
    u32    mField20;                       // +0x20
    u32    mField24;                       // +0x24
    HashTableU32 mCreatureMissions;         // +0x28
    u32    mField44;                       // +0x44
    HashTable mSpeciesMissions;            // +0x48
    cARC   mDisplayedSpeciesMission;       // +0x68
    cARC   mDisplayedTutorialMission;      // +0x6c
    u8     mbMissionDataDirty;             // +0x70
    u8     mPad71[3];                      // +0x71
    cARC   mNestMission;                   // +0x74
    u8     mNestFlag78;                    // +0x78
    u8     mPad79[3];                      // +0x79
    cARC   mSpeciesMission;                // +0x7c
public:
    cSPCreatureMissionManager* Init();                            // 0x00d37cf0
    bool  Write(void* stream);                                    // 0x00d37d80
    bool  Read(void* stream);                                     // 0x00d37e10
    void  SetupNestMissionCard();                                 // 0x00d37ea0
    void  ReleaseNestMission();                                   // 0x00d37ed0
    bool  IsTracked(void* p);                                     // 0x00d37ef0
    void  SetCardArea(u32 a, u32 b, u32 c);                       // 0x00d37f10
    void* ScalarDeletingDtor(u32 flags);                          // 0x00d37f50
    void  OnTick(void* a, void* b);                               // 0x00d38150
    void  SweepDeadMissions(void* unused);                        // 0x00d38530
};

// =============================================================================================
// anonymous-namespace helpers
// =============================================================================================
class cCreatureLevelUpScenario {
public:
    u32 mPad00[0xa0 / 4];                  // +0x00
    u32 mFieldA0;                          // +0xa0
    bool HasBrainUpgrade();                // 0x00d38880
};

class cCreatureModeStrategy {
public:
    void OnMouseWheel();                                   // 0x00d38890
    void OnMouseMove(int a, float b, float c, int d);      // 0x00d388a0
    void OnMouseButton(int a, float b, float c, int d);    // 0x00d388d0
};

// ---------------------------------------------------------------------------------------------
// 0x00d377f0 -- teardown of the scenario-edit input strategy.
// ---------------------------------------------------------------------------------------------
// @ 0x00d377f0
void cScenarioEditModeInputStrategy::CleanUp()
{
    CleanUpCreatureHitBoxes();

    // release the objects stored in the +0x6c layout tree
    for (void* node = mTree6c.mEnd; node != (void*)&mTree6c.mSelf;
         node = X_RBTreeIncrement(node))
    {
        void** slot = (void**)((char*)node + 0x14);
        void* obj = *slot;
        if (obj != 0)
            ((FnVI0)VTBL(obj)[0])(obj, 1);
    }

    // free the +0x6c tree nodes themselves
    for (void** p = (void**)mTree6c.mCount; p != 0; )
    {
        void** next = (void**)p[1];
        mTree6c.DoNukeSubtree(p[0]);
        X_FUN_00f47380(p);
        p = next;
    }
    mTree6c.mSelf  = &mTree6c.mSelf;
    mTree6c.mEnd   = &mTree6c.mSelf;
    mTree6c.mCount = 0;
    mTree6c.mFlag  = 0;
    mTree6c.mField14 = 0;

    // unhook the EA::Messaging handler
    if (mpHandler88 != 0)
    {
        void* h = mpHandler88;
        mpHandler88 = 0;
        X_RemoveHandler(h, mHandler8c, mHandler90, mHandler94, mHandler98);
    }

    mTree4.FUN_b1b830(mTree4.mCount);
    mTree4.mSelf  = &mTree4.mSelf;
    mTree4.mEnd   = &mTree4.mSelf;
    mTree4.mCount = 0;
    mTree4.mFlag  = 0;
    mTree4.mField14 = 0;

    mTree20.FUN_e4b990(mTree20.mCount);
    mTree20.mSelf  = &mTree20.mSelf;
    mTree20.mEnd   = &mTree20.mSelf;
    mTree20.mCount = 0;
    mTree20.mFlag  = 0;
    mTree20.mField14 = 0;

    if (mpObjC4 != 0)
    {
        void* o = mpObjC4;
        mpObjC4 = 0;
        ((FnV0)VTBL(o)[0xc0 / 4])(o);
    }
    if (mpObjE0 != 0)
    {
        ((FnVI0)VTBL(mpObjE0)[0xc / 4])(mpObjE0, 1);
        if (mpObjE0 != 0)
        {
            void* o = mpObjE0;
            mpObjE0 = 0;
            ((FnV0)VTBL(o)[1])(o);
        }
    }
    if (mpObjF0 != 0)
    {
        ((FnVI0)VTBL(mpObjF0)[0xc / 4])(mpObjF0, 1);
        if (mpObjF0 != 0)
        {
            void* o = mpObjF0;
            mpObjF0 = 0;
            ((FnV0)VTBL(o)[1])(o);
        }
    }
    if (mpObjF4 != 0)
    {
        void* o = mpObjF4;
        mpObjF4 = 0;
        ((FnV0)VTBL(o)[1])(o);
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00d37970 -- constructor of the scenario-edit input strategy.
// ---------------------------------------------------------------------------------------------
// @ 0x00d37970
cScenarioEditModeInputStrategy* cScenarioEditModeInputStrategy::Construct()
{
    mpVtbl = (void*)0x14771e0;

    mTree4.mEnd = 0; mTree4.mCount = 0; mTree4.mField14 = 0;
    mTree4.mSelf = &mTree4.mSelf;
    mTree4.mEnd = &mTree4.mSelf;
    mTree4.mCount = 0;
    mTree4.mFlag = 0;
    mTree4.mField14 = 0;

    mTree20.mCount = 0; mTree20.mEnd = 0; mTree20.mField14 = 0;
    mTree20.mSelf = &mTree20.mSelf;
    mTree20.mEnd = &mTree20.mSelf;
    mTree20.mCount = 0;
    mTree20.mFlag = 0;
    mTree20.mField14 = 0;

    ((void(__thiscall*)(void*))0x008014a0)((char*)this + 0x3c);

    mpSubVtbl44 = (void*)0x14426a0;
    mpSubVtbl48 = (void*)0x13eb384;
    mpSubVtbl4c = (void*)0x13ec458;
    mField50 = 0;

    mpVtbl = (void*)0x147a8b4;
    mpSubVtbl3c = (void*)0x147a89c;
    mpSubVtbl44 = (void*)0x147a880;
    mpSubVtbl48 = (void*)0x147a870;
    mpSubVtbl4c = (void*)0x147a860;

    mFlag54 = 1;
    mField58 = 0;
    mField5c = 0;
    mField60 = 0;

    mTree6c.mEnd = 0; mTree6c.mCount = 0; mTree6c.mField14 = 0;
    mTree6c.mSelf = &mTree6c.mSelf;
    mTree6c.mEnd = &mTree6c.mSelf;
    mTree6c.mCount = 0;
    mTree6c.mFlag = 0;
    mTree6c.mField14 = 0;

    mpHandler88 = 0;
    mHandler8c = 0;
    mHandler90 = 0;
    mHandler94 = 0;
    mHandler98 = 0;
    mTimerA0.Ctor();

    mFlagC0 = 1;
    mFlagC1 = 1;
    mpObjC4 = 0;

    mVecC8 = g_vDefault_169e17c;
    mVecD4 = g_vDefault_169e17c;

    mpObjE0 = 0;
    mpObjF0 = 0;
    mpObjF4 = 0;
    mFieldF8 = 0x1002;
    mFlagFc = 1;
    mFloat100 = 0.0f;
    mFlag105 = 0;
    mFlag106 = 1;

    ((void(__thiscall*)(void*))0x00d33c30)(this);
    return this;
}

// ---------------------------------------------------------------------------------------------
// 0x00d37b60 -- destructor of the scenario-edit input strategy.
// ---------------------------------------------------------------------------------------------
// @ 0x00d37b60
void cScenarioEditModeInputStrategy::Destroy()
{
    mpVtbl = (void*)0x147a8b4;
    mpSubVtbl3c = (void*)0x147a89c;
    mpSubVtbl44 = (void*)0x147a880;
    mpSubVtbl48 = (void*)0x147a870;
    mpSubVtbl4c = (void*)0x147a860;

    if (mpObjF4 != 0) ((FnV0)VTBL(mpObjF4)[1])(mpObjF4);
    if (mpObjF0 != 0) ((FnV0)VTBL(mpObjF0)[1])(mpObjF0);
    if (mpObjE0 != 0) ((FnV0)VTBL(mpObjE0)[1])(mpObjE0);
    if (mpObjC4 != 0) ((FnV0)VTBL(mpObjC4)[0xc0 / 4])(mpObjC4);

    mTimerA0.Dtor();

    if (mpHandler88 != 0)
    {
        void* h = mpHandler88;
        mpHandler88 = 0;
        X_RemoveHandler(h, mHandler8c, mHandler90, mHandler94, mHandler98);
    }

    mTree6c.DoNukeSubtree(mTree6c.mCount);

    ModelVec* mv = (ModelVec*)((char*)this + 0x58);
    mv->DoDestroyValues(mv->mpBegin, mv->mpEnd);
    if (mv->mpBegin != 0)
    {
        if (((u32*)mv->mpBegin)[-1] != 0)
            X_FUN_00f47380(mv->mpBegin);
    }

    mpSubVtbl4c = (void*)0x13ec458;
    mpSubVtbl48 = (void*)0x13eb394;
    mpSubVtbl44 = (void*)0x13eb938;

    ((void(__thiscall*)(void*))0x008014b0)((char*)this + 0x3c);
    mpVtbl = (void*)0x14771e0;

    mTree20.FUN_e4b990(mTree20.mCount);
    mTree4.FUN_b1b830(mTree4.mCount);
}

// ---------------------------------------------------------------------------------------------
// 0x00d37cf0 -- constructor of the creature mission manager.
// ---------------------------------------------------------------------------------------------
// @ 0x00d37cf0
cSPCreatureMissionManager* cSPCreatureMissionManager::Init()
{
    InitBase();

    mpVtbl00 = (void*)0x147a96c;
    mpVtbl08 = (void*)0x147a948;
    mpVtbl10 = (void*)0x147a938;
    mNestMission.mpObj = 0;
    mNestFlag78 = 0;
    mSpeciesMission.mpObj = 0;
    g_CreatureMissionManager = (void*)this;

    return this;
}

// ---------------------------------------------------------------------------------------------
// 0x00d37d80 -- cSPCreatureMissionManager::Write.
// ---------------------------------------------------------------------------------------------
// @ 0x00d37d80
bool cSPCreatureMissionManager::Write(void* stream)
{
    void* s = ((FnP0)VTBL(stream)[0x20 / 4])(stream);
    u32 key = 0x1406729e;
    void* out = ((FnP0)VTBL(s)[0x18 / 4])(s);
    X_WriteUint32(out, &key, 1, 0);

    bool ok = WriteBase(stream);

    cVarListSerializer ser;
    ser.Ctor((char*)this - 8, (void*)0x1582d30, 0x1a80d26);
    if (ok && ser.SerializeWrite(stream))
        return true;
    return false;
}

// ---------------------------------------------------------------------------------------------
// 0x00d37e10 -- cSPCreatureMissionManager::Read.
// ---------------------------------------------------------------------------------------------
// @ 0x00d37e10
bool cSPCreatureMissionManager::Read(void* stream)
{
    void* s = ((FnP0)VTBL(stream)[0x20 / 4])(stream);
    u32 key = 0;
    void* out = ((FnP0)VTBL(s)[0x18 / 4])(s);
    X_ReadInt32(out, &key, 1, 0);

    bool ok = ReadBase(stream);

    cVarListSerializer ser;
    ser.Ctor((char*)this - 8, (void*)0x1582d30, 0x1a80d26);
    if (ok && ser.SerializeRead(stream))
        return true;
    return false;
}

// ---------------------------------------------------------------------------------------------
// 0x00d37ea0 -- refresh the cards then re-setup the nest-mission card.
// ---------------------------------------------------------------------------------------------
// @ 0x00d37ea0
void cSPCreatureMissionManager::SetupNestMissionCard()
{
    RefreshCards();
    cMissionCardPanel* panel = (cMissionCardPanel*)X_GetCardPanel();
    if (panel != 0 && mNestMission.mpObj != 0)
        panel->SetupMissionCard(mNestMission.mpObj, 0, 1, 1);
}

// ---------------------------------------------------------------------------------------------
// 0x00d37ed0 -- refresh the cards then release the nest mission.
// ---------------------------------------------------------------------------------------------
// @ 0x00d37ed0
void cSPCreatureMissionManager::ReleaseNestMission()
{
    FUN_b70070();
    if (mNestMission.mpObj != 0)
    {
        void* p = mNestMission.mpObj;
        mNestMission.mpObj = 0;
        ((FnV0)VTBL(p)[1])(p);
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00d37ef0 -- is the given object tracked by this manager?
// ---------------------------------------------------------------------------------------------
// @ 0x00d37ef0
bool cSPCreatureMissionManager::IsTracked(void* p)
{
    if (p == mNestMission.mpObj)
        return true;
    return IsTrackedBase(p);
}

// ---------------------------------------------------------------------------------------------
// 0x00d37f10 -- lazily hook the nest mission and set the card panel area.
// ---------------------------------------------------------------------------------------------
// @ 0x00d37f10
void cSPCreatureMissionManager::SetCardArea(u32 a, u32 b, u32 c)
{
    if (mNestFlag78 == 0 && mNestMission.mpObj != 0)
    {
        mNestFlag78 = 1;
        ((cMission*)mNestMission.mpObj)->FUN_c2ebc0();
    }
    RectT_M area = { a, b, c };
    ((cMissionCardPanel*)X_GetCardPanel())->SetPanelArea(area);
}

// ---------------------------------------------------------------------------------------------
// 0x00d37f50 -- creature mission manager scalar deleting destructor.
// ---------------------------------------------------------------------------------------------
// @ 0x00d37f50
void* cSPCreatureMissionManager::ScalarDeletingDtor(u32 flags)
{
    mpVtbl00 = (void*)0x147a96c;
    mpVtbl08 = (void*)0x147a948;
    mpVtbl10 = (void*)0x147a938;
    g_CreatureMissionManager = 0;

    if (mSpeciesMission.mpObj != 0)
        ((FnV0)VTBL(mSpeciesMission.mpObj)[1])(mSpeciesMission.mpObj);
    if (mNestMission.mpObj != 0)
        ((FnV0)VTBL(mNestMission.mpObj)[1])(mNestMission.mpObj);

    TermBase();

    if ((flags & 1) != 0)
        X_FUN_00f47380(this);

    return this;
}

// ---------------------------------------------------------------------------------------------
// 0x00d37fe0 -- erase every entry whose key matches from a ResourceMan::Key hash_map.
// ---------------------------------------------------------------------------------------------
// @ 0x00d37fe0
int HashTable::Erase(u32* key)
{
    int oldSize = (int)mSize;

    u32 h = (key[0] ^ key[2]) % mBucketCount;
    u32** bucket = (u32**)((u8*)mpBuckets + h * 4);

    if (*bucket != 0)
    {
        u32** pos = bucket;
        u32* node;
        for (;;)
        {
            node = *pos;
            if (key[0] == node[0] && key[1] == node[1] && key[2] == node[2])
                break;
            pos = (u32**)(node + 4);
            if (node[4] == 0)
                break;
        }

        for (;;)
        {
            void* entry = *pos;
            if (entry == 0)
                break;
            u32* e = (u32*)entry;
            if (!(key[0] == e[0] && key[1] == e[1] && key[2] == e[2]))
                break;

            *pos = (u32*)e[4];
            if (e[3] != 0)
                ((FnV0)VTBL((void*)e[3])[1])((void*)e[3]);
            X_FUN_00f47380(e);
            mSize = mSize - 1;
        }
    }

    return oldSize - (int)mSize;
}

// ---------------------------------------------------------------------------------------------
// 0x00d38080 -- find the first element equal to *value, then remove it from the range.
// ---------------------------------------------------------------------------------------------
// @ 0x00d38080
void** X_FUN_00d38080(void** first, void** last, void** value)
{
    if (first == last)
        return first;

    void* v = *value;
    do
    {
        if (*first == v)
            break;
        ++first;
    } while (first != last);

    if (first != last)
        return (void**)X_FUN_00b6f4f0(first + 1, last, first, value);
    return first;
}

// ---------------------------------------------------------------------------------------------
// 0x00d380c0 -- find-or-insert a key in a ResourceMan::Key hash_map and return &value.
// ---------------------------------------------------------------------------------------------
// @ 0x00d380c0
void* HashTable::FUN_d380c0(u32* key)
{
    u32 it[3];
    Find(it, key);
    if ((void*)it[0] != *(void**)((u8*)mpBuckets + mBucketCount * 4))
        return (u8*)it[0] + 0xc;

    u32 stored[3];
    stored[0] = key[0];
    stored[1] = key[1];
    stored[2] = key[2];
    FUN_b6fe40(it, stored, 0);
    return (u8*)it[0] + 0xc;
}

// ---------------------------------------------------------------------------------------------
// 0x00d38150 -- cSPCreatureMissionManager::OnTick.
// ---------------------------------------------------------------------------------------------
// @ 0x00d38150
void cSPCreatureMissionManager::OnTick(void* a, void* b)
{
    cMissionCardPanel* panel = (cMissionCardPanel*)X_GetCardPanel();

    if (mSpeciesMission.mpObj != 0 && ((cMission*)mSpeciesMission.mpObj)->FUN_c2f300() && panel != 0)
    {
        if (mDisplayedSpeciesMission.mpObj != 0)
        {
            panel->RemoveMissionCard(mDisplayedSpeciesMission.mpObj);
            ((cMission*)mDisplayedSpeciesMission.mpObj)->FUN_c2fc80();
            if (mDisplayedSpeciesMission.mpObj != 0)
            {
                void* p = mDisplayedSpeciesMission.mpObj;
                mDisplayedSpeciesMission.mpObj = 0;
                ((FnV0)VTBL(p)[1])(p);
            }
        }
        mDisplayedSpeciesMission.FUN_ac9480(&mSpeciesMission);
        panel->SetupMissionCard(mDisplayedSpeciesMission.mpObj, 0, 1, 0);
        panel->ExpandMissionCard((int)mDisplayedSpeciesMission.mpObj);
        if (mSpeciesMission.mpObj != 0)
        {
            void* p = mSpeciesMission.mpObj;
            mSpeciesMission.mpObj = 0;
            ((FnV0)VTBL(p)[1])(p);
        }
    }

    NotifyAll();

    if (mbMissionDataDirty == 0)
        return;

    cGameNounManager* nm = (cGameNounManager*)X_NounManager();
    void* av = nm->GetAvatar();
    cCreatureBase* cr = (cCreatureBase*)X_FUN_00d99500(((cCreatureBase*)av)->ApplyCombatTarget());

    if (cr != 0 &&
        !((FnB0)VTBL(cr)[0xd0 / 4])(cr) &&
        !cr->Flag388())
    {
        void* key = (void*)((char*)cr + 0xb28);

        void* it;
        mSpeciesMissions.Find(&it, key);
        if (it == *(void**)((u8*)mSpeciesMissions.mpBuckets + mSpeciesMissions.mBucketCount * 4))
        {
            cGameNounManager* nm2 = (cGameNounManager*)X_NounManager();
            cMission* mission = (cMission*)nm2->CreateNoun(0x1406a572);
            mission->FUN_c301c0(cr);
            cARC* slot = (cARC*)mSpeciesMissions.FUN_d380c0((u32*)key);
            slot->Assign(mission);
            cARC tmp;
            tmp.FUN_572660(mission);
            mMissionList.PushBack(&tmp);
            if (tmp.mpObj != 0)
            {
                void* p = tmp.mpObj;
                tmp.mpObj = 0;
                ((FnV0)VTBL(p)[1])(p);
            }
        }

        cARC* slot2 = (cARC*)mSpeciesMissions.FUN_d380c0((u32*)key);
        void* candidate = slot2->mpObj;

        if (mDisplayedSpeciesMission.mpObj != 0)
        {
            ((cMission*)mDisplayedSpeciesMission.mpObj)->FUN_c2e780();
            void* prof = cr->GetSpeciesProfile();
            if (slot2->mpObj == prof)
                goto afterDisplay;
        }
        if (mSpeciesMission.mpObj != candidate)
        {
            mSpeciesMission.Assign(candidate);
            ((cMission*)mSpeciesMission.mpObj)->FUN_c2fc10();
        }
    }
    else
    {
        if (mDisplayedSpeciesMission.mpObj != 0 && panel != 0)
            panel->CollapseMissionCard(mDisplayedSpeciesMission.mpObj);
    }

afterDisplay:
    if (mDisplayedSpeciesMission.mpObj != 0)
        ((FnV0)VTBL(mDisplayedSpeciesMission.mpObj)[0x80 / 4])(mDisplayedSpeciesMission.mpObj);

    cTerrainEditor* te = (cTerrainEditor*)X_NounManager();
    cTerrainSphere* ts = (cTerrainSphere*)te->GetCurrentTerrainSphere();
    if (ts->mpSomething10e8 != 0 &&
        (g_sTestSystem == 0 || *(void**)(g_sTestSystem + 0x70) == (void*)(g_sTestSystem + 0x70)) &&
        *(u8*)((char*)X_CreatureModeStrategy_Instance() + 0xdd) != 0)
    {
        bool allowSpawn = !ts->FUN_00594330();

        if (!allowSpawn && mNestMission.mpObj != 0 &&
            ((FnI0)VTBL(mNestMission.mpObj)[0x60 / 4])(mNestMission.mpObj) != 5)
        {
            ((cMission*)mNestMission.mpObj)->FUN_c2ebc0();
        }

        if (mNestMission.mpObj != 0 &&
            ((FnI0)VTBL(mNestMission.mpObj)[0x60 / 4])(mNestMission.mpObj) == 5 &&
            !((FnB0)VTBL(mNestMission.mpObj)[0x64 / 4])(mNestMission.mpObj))
        {
            if (panel != 0)
                panel->RemoveMissionCard(mNestMission.mpObj);

            void* newEnd = X_FUN_00d38080((void**)mMissionList.mpBegin,
                                          (void**)mMissionList.mpEnd,
                                          (void**)&mNestMission);
            mMissionList.Erase(newEnd, mMissionList.mpEnd);

            ((FnV0)VTBL(mNestMission.mpObj)[0x44 / 4])(mNestMission.mpObj);

            void* p = mNestMission.mpObj;
            X_NounManager();
            ((cGameNounManager*)X_NounManager())->RemoveNoun(p);
            if (mNestMission.mpObj != 0)
            {
                void* pp = mNestMission.mpObj;
                mNestMission.mpObj = 0;
                ((FnV0)VTBL(pp)[1])(pp);
            }
        }

        if (!allowSpawn && mNestMission.mpObj == 0)
        {
            cGameNounManager* nm3 = (cGameNounManager*)X_NounManager();
            cMission* mission = (cMission*)nm3->CreateNoun(0x14d9597f);
            mNestMission.Assign(mission);
            if (mNestFlag78 != 0)
                ((cMission*)mNestMission.mpObj)->FUN_c30100(0x134711cf);
            else
                ((cMission*)mNestMission.mpObj)->FUN_c30100(0xc0ecaaae);
            cARC tmp;
            tmp.FUN_572660(mission);
            mMissionList.PushBack(&tmp);
            if (tmp.mpObj != 0)
            {
                void* p = tmp.mpObj;
                tmp.mpObj = 0;
                ((FnV0)VTBL(p)[1])(p);
            }
            if (panel != 0)
                panel->SetupMissionCard(mNestMission.mpObj, 0, 1, 1);
        }
    }

    FUN_b6f650(a, b);
    mbMissionDataDirty = 0;
}

// ---------------------------------------------------------------------------------------------
// 0x00d38530 -- remove the missions whose noun has just died.
// ---------------------------------------------------------------------------------------------
// @ 0x00d38530
void cSPCreatureMissionManager::SweepDeadMissions(void* unused)
{
    (void)unused;

    cGameNounManager* nm = (cGameNounManager*)X_NounManager();
    NounVec* v = nm->GetGameDataVector(0x00cd7d10, 0x00d3d420, 0x00d384b0, 0x00b1e500, 0x1406a572);

    PtrVec local;
    local.ctor((u32)(v->mpEnd - v->mpBegin), &v->mField10);

    X_FUN_00829110(&local, v->mpBegin, v->mpEnd, local.mpEnd, nm);

    for (void** it = local.mpBegin; it != local.mpEnd; ++it)
    {
        void* noun = *it;
        if (((cMission*)noun)->FUN_c2e780() != 0)
            continue;

        // remove the matching mission from the +0x14 list
        void** first = (void**)mMissionList.mpBegin;
        void** last  = (void**)mMissionList.mpEnd;
        while (first != last && *first != noun)
            ++first;
        if (first != last)
            X_FUN_00b6f4f0(first + 1, last, first, &noun);
        mMissionList.Erase(first, mMissionList.mpEnd);

        // drop it from both hash maps
        mSpeciesMissions.Erase((u32*)((cMission*)noun)->FUN_c2e7a0());
        if (*(void**)((char*)noun + 0x78) != 0)
            mCreatureMissions.EraseU32((u32*)((char*)noun + 0x78));

        nm->RemoveNoun(noun);

        if (mDisplayedSpeciesMission.mpObj == noun)
        {
            if (mDisplayedSpeciesMission.mpObj != 0)
            {
                void* p = mDisplayedSpeciesMission.mpObj;
                mDisplayedSpeciesMission.mpObj = 0;
                ((FnV0)VTBL(p)[1])(p);
            }
        }
    }

    for (void** p = local.mpBegin; p < local.mpEnd; ++p)
    {
        if (*p != 0)
            ((FnV0)VTBL(*p)[1])(*p);
    }
    if (local.mpBegin != 0)
    {
        if (((u32*)local.mpBegin)[-1] != 0)
            X_FUN_00f47380(local.mpBegin);
    }
}

// =============================================================================================
// anonymous-namespace helpers
// =============================================================================================

// ---------------------------------------------------------------------------------------------
// 0x00d386a0 -- fraction of creature-space progress between the two length-distribution bounds.
// ---------------------------------------------------------------------------------------------
// @ 0x00d386a0
float FUN_00d386a0()
{
    float a = ((cTerrainSphere*)((cTerrainEditor*)X_NounManager())->GetCurrentTerrainSphere())->FUN_c75680(0);
    float b = ((cTerrainSphere*)((cTerrainEditor*)X_NounManager())->GetCurrentTerrainSphere())->FUN_c75680(1);

    float total = ((g_len1582e38[3] + g_len1582e38[2]) + g_len1582e38[1]) + g_len1582e38[0];
    float t = 0.0f;
    if (0.0f < total)
        t = (a - b) / total;

    if (X_GlobalGet() != 0)
        t = t + ((Cls_e3f7a0*)X_GlobalGet())->F(0xa426730b);

    if (t < -1.0f) t = -1.0f;
    if (t > 1.0f)  t = 1.0f;
    return t;
}

// ---------------------------------------------------------------------------------------------
// 0x00d38780 -- pick a brain-upgrade icon id from the progress fraction.
// ---------------------------------------------------------------------------------------------
// @ 0x00d38780
u32 FUN_00d38780()
{
    float f = FUN_00d386a0();
    if (f >= 0.33333334f)
        return 0x17e5ef84;
    if (f < -0.33333334f)
        return 0xfd159d91;
    return 0xb9de15f2;
}

// ---------------------------------------------------------------------------------------------
// 0x00d387c0 -- MarkEventAsOccurred.
// ---------------------------------------------------------------------------------------------
// @ 0x00d387c0
void MarkEventAsOccurred(u32 event)
{
    u32 local[3];
    local[0] = event;
    local[1] = 0;
    local[2] = 0x68dd6929;

    cTerrainSphere* ts = (cTerrainSphere*)((cTerrainEditor*)X_NounManager())->GetCurrentTerrainSphere();
    if (ts != 0)
        ts->FUN_c78420(local);
}

// ---------------------------------------------------------------------------------------------
// 0x00d38800 -- cCreatureLevelUpScenario::EvaluateEvent.
// ---------------------------------------------------------------------------------------------
// @ 0x00d38800
const char* EvaluateEvent(int event)
{
    const char* name = 0;
    switch (event)
    {
    case 1: return "CRG_BrainUpgrade1";
    case 2: return "CRG_BrainUpgrade2";
    case 3: return "CRG_BrainUpgrade3";
    case 4: name = "CRG_BrainUpgrade4";
    }
    return name;
}

// ---------------------------------------------------------------------------------------------
// 0x00d38880 -- true unless the scenario state is the "done" 0x0d.
// ---------------------------------------------------------------------------------------------
// @ 0x00d38880
bool cCreatureLevelUpScenario::HasBrainUpgrade()
{
    return mFieldA0 != 0xd;
}

// ---------------------------------------------------------------------------------------------
// 0x00d38890 -- SP::cCreatureModeStrategy::OnMouseWheel.
// ---------------------------------------------------------------------------------------------
// @ 0x00d38890
void cCreatureModeStrategy::OnMouseWheel()
{
    void* m = X_GameInputManager();
    ((FnV0)VTBL(m)[0x48 / 4])(m);
}

// ---------------------------------------------------------------------------------------------
// 0x00d388a0 -- forward a mouse-move to the input manager.
// ---------------------------------------------------------------------------------------------
// @ 0x00d388a0
void cCreatureModeStrategy::OnMouseMove(int a, float b, float c, int d)
{
    void* m = X_GameInputManager();
    ((FnVIFFI)VTBL(m)[0x58 / 4])(m, a, b, c, d);
}

// ---------------------------------------------------------------------------------------------
// 0x00d388d0 -- forward a mouse-button message to the input manager.
// ---------------------------------------------------------------------------------------------
// @ 0x00d388d0
void cCreatureModeStrategy::OnMouseButton(int a, float b, float c, int d)
{
    void* m = X_GameInputManager();
    ((FnVIFFI)VTBL(m)[0x54 / 4])(m, a, b, c, d);
}

// ---------------------------------------------------------------------------------------------
// 0x00d38900 -- is the current avatar in state 4?
// ---------------------------------------------------------------------------------------------
// @ 0x00d38900
bool FUN_00d38900()
{
    cGameNounManager* nm = (cGameNounManager*)X_NounManager();
    void* av = nm->GetAvatar();
    if (av != 0)
        return ((FnI0)VTBL(av)[0xd8 / 4])(av) == 4;
    return false;
}