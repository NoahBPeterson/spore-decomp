// src/game/SPGonzago/_at_00d30000.cpp -- migrated from slice(s) s00d377f0 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00d30000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPCreatureBase.h"
#include "SP/cGameNounManager.h"
#include "SP/cGonzagoTimer.h"
#include "SP/cTerrainSphere.h"
#include "SP/cVarListSerializer.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* __cdecl X_NounManager();                      // 0x00b3d300
extern "C" void* __cdecl X_GetCardPanel();                     // 0x00b3d400
extern "C" void* __cdecl X_GlobalGet();                        // 0x00b3d410
extern "C" void  __cdecl X_FUN_00829110(void*, void*, void*, void*, void*); // 0x00829110
extern "C" void  __cdecl X_FUN_00f47380(void*);                // 0x00f47380  operator_delete
extern "C" void* __cdecl X_FUN_00b6f4f0(void*, void*, void*, void*);         // 0x00b6f4f0
extern float g_len1582e38[4];              // 0x001582e38   length-distribution bounds
extern void* g_CreatureMissionManager;     // 0x00169e230

// ---- items of slice s00d377f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  u8;
typedef unsigned int   u32;
struct RectT_M { u32 a, b, c; };
typedef void  (__thiscall *FnV0)(void*);
static inline void** VTBL(void* p) { return *(void***)p; }
extern "C" void* __cdecl X_NounManager();                      // 0x00b3d300
extern "C" void* __cdecl X_GetCardPanel();                     // 0x00b3d400
extern "C" void* __cdecl X_GlobalGet();                        // 0x00b3d410
extern "C" void  __cdecl X_FUN_00829110(void*, void*, void*, void*, void*); // 0x00829110
extern "C" void  __cdecl X_FUN_00f47380(void*);                // 0x00f47380  operator_delete
extern "C" void* __cdecl X_FUN_00b6f4f0(void*, void*, void*, void*);         // 0x00b6f4f0
extern float g_len1582e38[4];              // 0x001582e38   length-distribution bounds
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
struct Cls_e3f7a0 {                       // global object, adds a timer fraction
    float F(u32 event);                    // 0x00e3f7a0
};
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
// ---- items of slice s00d377f0 end

// @ 0x00d37ea0
void cSPCreatureMissionManager::SetupNestMissionCard()
{
    RefreshCards();
    cMissionCardPanel* panel = (cMissionCardPanel*)X_GetCardPanel();
    if (panel != 0 && mNestMission.mpObj != 0)
        panel->SetupMissionCard(mNestMission.mpObj, 0, 1, 1);
}

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

// @ 0x00d37ef0
bool cSPCreatureMissionManager::IsTracked(void* p)
{
    if (p == mNestMission.mpObj)
        return true;
    return IsTrackedBase(p);
}

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
