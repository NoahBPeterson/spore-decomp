// src/game/SPGonzago/SPCreatureMissionManager.cpp -- migrated from slice(s) s00d377f0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCreatureMissionManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPCreatureBase.h"
#include "SP/cGameNounManager.h"
#include "SP/cGonzagoTimer.h"
#include "SP/cTerrainSphere.h"
#include "SP/cVarListSerializer.h"

// unnamed retail callees and globals (address in the comment)
extern "C" bool  __cdecl X_WriteUint32(void*, const void*, int, int);        // 0x0093aa70
extern "C" bool  __cdecl X_ReadInt32(void*, void*, int, int);                // 0x0093a780
extern void* g_CreatureMissionManager;     // 0x00169e230

// ---- items of slice s00d377f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  u8;
typedef unsigned int   u32;
typedef void* (__thiscall *FnP0)(void*);
static inline void** VTBL(void* p) { return *(void***)p; }
extern "C" bool  __cdecl X_WriteUint32(void*, const void*, int, int);        // 0x0093aa70
extern "C" bool  __cdecl X_ReadInt32(void*, void*, int, int);                // 0x0093a780
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
struct cARC {                              // EA::AutoRefCount<mission>
    void* mpObj;                           // +0x00
    cARC* Assign(void* p);                 // 0x00b5f950
    void  FUN_ac9480(cARC* src);           // 0x00ac9480
    void  FUN_572660(void* p);             // 0x00572660  AutoRefCount ctor
};
struct cVarListSerializer {
    u8   mData[0xa14];
    void Ctor(void* pObject, void* pVarList, u32 signature);   // 0x00692f90
    bool SerializeWrite(void* stream);                         // 0x00692900
    bool SerializeRead(void* stream);                          // 0x00693e10
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
