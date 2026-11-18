// Slice s01012820: one function.
//
//   0x01012820  mission spawn into an intrusive list  (230 B, ret 8)
//
// Module is SporeApp Simulator/game code (VC9 SP1), not Havok.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

// ---------------------------------------------------------------- shared types
//
// The class owning 0x01012820 has no PDB name in the symbol map; the layout is
// taken from the code: a refcounted pointer is appended to the vector passed as
// the second argument (begin/end/capacity at +0x00/+0x04/+0x08).

struct cRefObj {
    virtual void AddRef();                  // +0x00
    virtual void Release();                 // +0x04
};

struct cMission {
    virtual void  v0();                     // +0x00
    virtual void  v1();                     // +0x04
    virtual void  v2();                     // +0x08
    virtual void* GetEvent(int id);         // +0x0c
};

struct cRaidEvent {
    void SetTarget(int target);             // 0x00c5b370
    void FUN_c47180(int a);                 // 0x00c47180
    int  GenerateBomberCount();             // 0x00c5b530
    void FUN_c5b390(int a);                 // 0x00c5b390
    void Accept();                          // 0x00c485b0
};

struct cNounMgr {
    void* FUN_b8de30();                     // 0x00b8de30
    void* FUN_b1fdb0();                     // 0x00b1fdb0
};

struct cStarManager {
    void* GetEmpireByID(void* key);         // 0x00ba9370
};

struct cSPMissionManager {
    void* CreateMissionFromID(int id, int a, void* b, int c);   // 0x00fec590
};

// the destination list: an intrusive vector of refcounted mission pointers
struct cMissionList {
    cRefObj** mBegin;                       // +0x00
    cRefObj** mEnd;                         // +0x04
    cRefObj** mCapacity;                    // +0x08

    void insert(cRefObj** pos, cRefObj** value);   // 0x00aea5d0
};

void* __cdecl GetMissionManager();          // 0x00feb9f0
void* __cdecl StarManager();                // 0x00b3d2a0

// ---------------------------------------------------------------- 0x01012820

struct cMissionSpawn {
    int Add(int arg1, cMissionList* list);  // 0x01012820  (ret 8)
};

// @ 0x01012820
int cMissionSpawn::Add(int arg1, cMissionList* list)
{
    cSPMissionManager* mm = (cSPMissionManager*)GetMissionManager();
    if (arg1 != 0)
    {
        void* avatar = ((cNounMgr*)arg1)->FUN_b8de30();
        void* av2    = ((cNounMgr*)avatar)->FUN_b1fdb0();
        void* civ    = ((cStarManager*)StarManager())->GetEmpireByID(av2);

        cRefObj* mission = (cRefObj*)mm->CreateMissionFromID(0xd646c543, arg1, civ, 0);
        if (mission != 0) {
            void* raid = ((cMission*)mission)->GetEvent(0x3960c0a);
            if (raid != 0) {
                ((cRaidEvent*)raid)->SetTarget(0);
                ((cRaidEvent*)raid)->FUN_c47180(arg1);
                int count = ((cRaidEvent*)raid)->GenerateBomberCount();
                ((cRaidEvent*)raid)->FUN_c5b390(count);
                ((cRaidEvent*)raid)->Accept();
            }
        }

        cRefObj* tmp = mission;
        if (mission != 0)
            mission->AddRef();

        if (list->mEnd < list->mCapacity) {
            cRefObj** slot = list->mEnd++;
            if (slot != 0) {
                *slot = mission;
                if (mission != 0)
                    mission->AddRef();
            }
        } else {
            list->insert(list->mEnd, &tmp);
            mission = tmp;
        }

        if (mission != 0)
            mission->Release();
        return 1;
    }
    return 0;
}
