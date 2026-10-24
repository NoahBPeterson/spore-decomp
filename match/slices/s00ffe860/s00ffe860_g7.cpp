// Slice s00ffe860 (gold7): player-UFO sort helpers, handle-message and star-move handler.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
//
//  * 0x00fff270  cSPSimulatorSpaceGame::PlayerHasStarOf  -- walk the player's star ring
//  * 0x00fff2a0  guarded insertion sort  (eastl insertion_sort)
//  * 0x00fff370  unguarded insertion sort (eastl __unguarded_insertion_sort)
//  * 0x00fff440  sift-down / adjust-heap  (followed by a push-heap at 0x00ffd2e0)
//  * 0x00fff5f0  cSPSimulatorPlayerUFO::HandleMessage   (max health / energy refresh)
//  * 0x00fff6a0  cSPSimulatorPlayerUFO::OnStarMoveDone
#include "types.h"

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};

// Trivial 12-byte position (city/star coordinates, copied as a plain block).
struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(const Vec3& o) : x(o.x), y(o.y), z(o.z) {}
};
struct Quat    { float x, y, z, w; };

// ---------------------------------------------------------------------------
// Intrusively ref-counted object (vtable slot 0 AddRef, slot 1 Release).
// ---------------------------------------------------------------------------
struct RefObj {
    virtual void AddRef();              // +0x00
    virtual void Release();             // +0x04
    virtual void v08();                 // +0x08
    virtual void v0c(int);              // +0x0c
};

// 4-byte counted reference; copy ctor AddRefs, dtor Releases.
struct AutoRef {
    RefObj* mpObject;

    AutoRef() : mpObject(0) {}
    AutoRef(RefObj* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    AutoRef(const AutoRef& o) : mpObject(o.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRef() { if (mpObject) mpObject->Release(); }

    AutoRef& operator=(const AutoRef& o)
    {
        RefObj* pNew = o.mpObject;
        RefObj* old = mpObject;
        if (pNew != old) {
            if (pNew) pNew->AddRef();
            mpObject = pNew;
            if (old) old->Release();
        }
        return *this;
    }
};

// Distance comparator: 'this' is the Vector3 reference point (0x00ac0810).
struct PosLess {
    bool Less(RefObj* a, RefObj* b) const;
};

static inline bool LessAt(const Vector3& pos, RefObj* a, RefObj* b)
{
    return ((const PosLess*)&pos)->Less(a, b);
}

// Push-heap (0x00ffd2e0); cdecl, caller cleans 0x1c bytes.
void PushHeap(AutoRef* base, int top, int hole, AutoRef value, Vector3 pos);

// ---------------------------------------------------------------------------
// 0x00fff270 -- ring search at this+0x70 for the record referenced by arg+0x84.
// ---------------------------------------------------------------------------
struct cEmpireRef {
    char  pad00[0x84];
    void* mpRecord;                     // +0x84
};

struct StarNode {
    StarNode* mpNext;                   // +0x00
    void*     mpPad04;                  // +0x04
    void*     mpRecord;                 // +0x08
};

struct cSPSimulatorSpaceGame {
    char     pad00[0x70];
    StarNode mStarList;                 // +0x70 (circular list head)
    bool     PlayerHasStarOf(cEmpireRef* pEmpire);
};

// @ 0x00fff270
bool cSPSimulatorSpaceGame::PlayerHasStarOf(cEmpireRef* pEmpire)
{
    void* rec = pEmpire->mpRecord;
    for (StarNode* n = mStarList.mpNext; n != &mStarList; n = n->mpNext) {
        if (n->mpRecord == rec)
            return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// 0x00fff2a0 -- eastl insertion_sort over AutoRef elements.
// ---------------------------------------------------------------------------
// @ 0x00fff2a0
void SortInsertion(AutoRef* first, AutoRef* last, Vector3 pos)
{
    if (first != last) {
        for (AutoRef* i = first + 1; i != last; ++i) {
            AutoRef value = *i;
            AutoRef* j = i;
            while (j != first && LessAt(pos, value.mpObject, j[-1].mpObject)) {
                *j = j[-1];
                --j;
            }
            *j = value;
        }
    }
}

// ---------------------------------------------------------------------------
// 0x00fff370 -- eastl __unguarded_insertion_sort over AutoRef elements.
// ---------------------------------------------------------------------------
// @ 0x00fff370
void SortInsertionUnguarded(AutoRef* first, AutoRef* last, Vector3 pos)
{
    for (AutoRef* i = first; i != last; ++i) {
        AutoRef* j = i;
        AutoRef value = *i;
        while (LessAt(pos, value.mpObject, j[-1].mpObject)) {
            *j = j[-1];
            --j;
        }
        *j = value;
    }
}

// ---------------------------------------------------------------------------
// 0x00fff440 -- eastl __adjust_heap over AutoRef elements.
// ---------------------------------------------------------------------------
// @ 0x00fff440
void AdjustHeap(AutoRef* first, int top, int len, int hole, AutoRef value, Vector3 pos)
{
    int child = hole * 2 + 2;
    while (child < len) {
        if (LessAt(pos, first[child].mpObject, first[child - 1].mpObject))
            --child;
        first[hole] = first[child];
        hole = child;
        child = child * 2 + 2;
    }
    if (child == len) {
        first[hole] = first[child - 1];
        hole = child - 1;
    }
    PushHeap(first, top, hole, value, pos);
}

// ---------------------------------------------------------------------------
// 0x00fff5f0 -- cSPSimulatorPlayerUFO::HandleMessage
// ---------------------------------------------------------------------------
struct cUFOHealth {
    char  pad000[0x534];
    float mMaxHealth;                   // +0x534
    char  pad538[0x540 - 0x538];
    float mHealth;                      // +0x540
    char  pad544[0x7f4 - 0x544];
    float mCurEnergy;                   // +0x7f4
    float mMaxEnergy;                   // +0x7f8
};

struct cSPSimulatorPlayerUFOBody {
    float CalculateMaxHealth();         // 0x00ffd8e0
    float CalculateMaxEnergy();         // 0x00ffda80
};

struct cSPSimulatorPlayerUFOHandler {
    char  pad00[0x30];
    cUFOHealth* mpHealth;               // +0x30
    bool  HandleMessage(int msg, int ctx);
};

// @ 0x00fff5f0
bool cSPSimulatorPlayerUFOHandler::HandleMessage(int msg, int ctx)
{
    if (msg == 0x57f3749) {
        cUFOHealth* pH = mpHealth;
        float oldHealth = pH->mMaxHealth;
        pH->mMaxHealth =
            ((cSPSimulatorPlayerUFOBody*)((char*)this - 0x10))->CalculateMaxHealth();
        if (mpHealth->mMaxHealth != oldHealth)
            mpHealth->mHealth = mpHealth->mMaxHealth;

        pH = mpHealth;
        float oldEnergy = pH->mMaxEnergy;
        pH->mMaxEnergy =
            ((cSPSimulatorPlayerUFOBody*)((char*)this - 0x10))->CalculateMaxEnergy();
        if (mpHealth->mMaxEnergy != oldEnergy)
            mpHealth->mCurEnergy = mpHealth->mMaxEnergy;
    }
    return false;
}

// ---------------------------------------------------------------------------
// 0x00fff6a0 -- cSPSimulatorPlayerUFO::OnStarMoveDone
// ---------------------------------------------------------------------------
bool  FUN_00ffdbb0();                              // 0x00ffdbb0
void  FUN_01041c50(const char*, int, int);         // 0x01041c50
int   FUN_01021240();                              // 0x01021240

struct cStarMap {
    void FUN_01048e00(int);                        // 0x01048e00 (ret 4)
    void FilterHelperRebuildAll();                 // 0x01048ce0
};
cStarMap* StarMapGet();                            // 0x01046fc0

struct cSkyTuning {
    void FUN_01036d30(Vec3* pos);                  // 0x01036d30 (ret 4)
};
cSkyTuning* SkyTuningGet();                        // 0x00b3d470

struct cTerrainSphere {
    bool IsSpace();                                // 0x00c77410
    void FUN_00c79f20(int);                        // 0x00c79f20 (ret 4)
    void RemoveStarFromPlayerCaptureProgressList(int);  // 0x00c7ad40 (ret 4)
};
bool FUN_00c8bb00(int);                            // 0x00c8bb00

struct cNounManager {
    cTerrainSphere* GetCurrentTerrainSphere();     // 0x00f67d90
};
cNounManager* NounManager();                       // 0x00b3d300

struct cTriggerMgr {
    void PostAction(int id, void* target, int flags);   // 0x00ae09b0 (ret 0xc)
};
cTriggerMgr* GetTriggerMgr();                      // 0x00b3d4d0

// Camera/action-target message local (0x30 bytes), ctor 0x00ad79d0, dtor 0x00ad7ad0.
struct cActionTarget {
    char  data[0x30];
    cActionTarget(const Vec3* pPos, const Quat* pRot);
    ~cActionTarget();
};

// The star record returned by 0x01021240 is used as an object (this=ecx).
struct cStarData {
    int      AddRef();                             // 0x00801920
    bool     Flag5c();                             // 0x00bb9c00
    bool     Flag4c();                             // 0x00bb9fb0
    Vec3*    GetCities();                          // 0x005c65e0
};

struct cSPSimulatorPlayerUFO {
    char        pad00[0x44];
    RefObj*     mpHitSphere;                       // +0x44
    void        FUN_00ffdde0(int tag, Vec3 pos);   // 0x00ffdde0 (ret 0x10)
    void        OnStarMoveDone();
};

// @ 0x00fff6a0
void cSPSimulatorPlayerUFO::OnStarMoveDone()
{
    if (FUN_00ffdbb0())
        FUN_01041c50("SPG_TravelNearCore", 0x5f776d6, 0);

    if (mpHitSphere) {
        mpHitSphere->v0c(1);
        if (mpHitSphere) {
            RefObj* p = mpHitSphere;
            mpHitSphere = 0;
            p->Release();
        }
    }

    int id = FUN_01021240();
    cStarData* pData = (cStarData*)(size_t)id;

    StarMapGet()->FUN_01048e00(id);

    FUN_00ffdde0(pData->AddRef(), *pData->GetCities());
    SkyTuningGet()->FUN_01036d30(pData->GetCities());

    if (!pData->Flag5c()) {
        if (NounManager()->GetCurrentTerrainSphere()->IsSpace()) {
            NounManager()->GetCurrentTerrainSphere()->FUN_00c79f20(id);
            StarMapGet()->FilterHelperRebuildAll();
        }
    }

    cTerrainSphere* pTerrain = NounManager()->GetCurrentTerrainSphere();
    if (FUN_00c8bb00(id))
        pTerrain->RemoveStarFromPlayerCaptureProgressList(id);

    if (pData->Flag4c()) {
        Quat rot;
        cActionTarget target(pData->GetCities(), &rot);
        GetTriggerMgr()->PostAction(0x5f4a3cdb, &target, 0);
        FUN_01041c50("SPG_SETI", 0x5b15124, 0);
    }
}
