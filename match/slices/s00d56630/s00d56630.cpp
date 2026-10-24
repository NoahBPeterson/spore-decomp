// Slice s00d56630: SP::cBehaviorSpaceTurret::Init (0x00d56630) and
// SP::cBehaviorSpaceTurret::StopDefense (0x00d56870).
// /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
//
// Retail layout of the owning object (identical to slice s00d56c30):
//   +0x0c mTargetList (spstl::slot_vector, 0x1c bytes), +0x2c mAgentList,
//   +0x74 mStateMap, +0x90 mLifeTimer, +0xb0 mNextFiringTime (u64),
//   +0xbc mCityCenter, +0xc8 mAaShotsPerTurret, +0xd0 mSdrBeamLifetime (u64),
//   +0xd8 mbWasHostile, +0xe0 mScanTimer.
#include "types.h"

struct Vector3 { float x, y, z; };

// ---- generic object interfaces (only the slots this slice uses) ------------
struct IObj;

struct IAgent {
    virtual void     a00();
    virtual void     a04();
    virtual IObj*    a08();              // 0x08 (no stack argument)
    virtual IObj*    a0c();              // 0x0c
    virtual int      a10();              // 0x10
    virtual void     a14(); virtual void a18(); virtual void a1c();
    virtual void     a20(); virtual void a24(); virtual void a28(); virtual void a2c();
    virtual void     a30(); virtual void a34(); virtual void a38(); virtual void a3c();
    virtual void     a40(); virtual void a44(); virtual void a48(); virtual void a4c();
    virtual void     a50(); virtual void a54(); virtual void a58();
    virtual void*    a5c(uint32_t id);   // 0x5c GetBehavior(id)
    virtual void     a60(); virtual void a64(); virtual void a68(); virtual void a6c();
    virtual void     a70(); virtual void a74(); virtual void a78(); virtual void a7c();
    virtual void     a80(); virtual void a84(); virtual void a88(); virtual void a8c();
    virtual void     a90(); virtual void a94(); virtual void a98(); virtual void a9c();
    virtual void     aa0(); virtual void aa4(); virtual void aa8(); virtual void aac();
    virtual void     ab0(); virtual void ab4();
    virtual void*    ab8(uint32_t id);   // 0xb8
};

struct ISpatial {
    virtual void           v00(); virtual void v04(); virtual void v08();
    virtual void           v0c(); virtual void v10(); virtual void v14();
    virtual void           v18(); virtual void v1c(); virtual void v20();
    virtual void           v24(); virtual void v28();
    virtual const Vector3& GetPosition();  // 0x2c
};

struct IObj {
    virtual void   v00();
    virtual IObj*  Cast4(uint32_t id);     // 0x04
    virtual IObj*  Cast8(uint32_t id);     // 0x08
    virtual IObj*  v0c();                  // 0x0c
    virtual int    v10();                  // 0x10
    virtual void   v14(); virtual void v18(); virtual void v1c();
    virtual void   v20(); virtual void v24(); virtual void v28();
    virtual const Vector3& GetPosition();  // 0x2c
};

struct IValid { virtual bool IsValid(); };     // 0x2c bool result
struct IFlagged { bool Flag388(); };           // 0x00c0c0e0

// ---- combatant / tool pieces ---------------------------------------------
struct cCombatant {
    int  GetDamageState();                 // 0x008e7f80
    bool IsDestroyed();                    // 0x00bfc600
    bool HasEntry(uint32_t id);            // 0x00bfcc40
};

struct cCombatantView {                    // cCombatant subobject at turret+0x588
    virtual void   v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual int    GetTargetID();          // 0x10
    virtual void   v14(); virtual void v18(); virtual void v1c();
    virtual void   v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void   v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void   v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void   SetTarget(void* target); // 0x50
    int  GetDamageState();                 // 0x008e7f80
    bool IsDestroyed();                    // 0x00bfc600
};

struct cTool {
    int GetRefireMs();                     // 0x0104bde0
};

struct cPointerList {                      // turret+0x2ac
    void** mpBegin;
    void** mpEnd;
};

struct cTurret {
    uint32_t pad00[0x34 / 4];
    ISpatial mSpatial;                     // 0x34
    uint32_t pad38[(0x2ac - 0x38) / 4];
    cPointerList mCandidateList;           // 0x2ac (0x00c420d0 returns &this)
    uint32_t pad2b4[(0x588 - 0x2b4) / 4];
    cCombatantView mCombatant;             // 0x588
    uint32_t pad58c[(0x688 - 0x58c) / 4];
    IObj*        mpField688;               // 0x688 (0x00bce5c0)
    uint32_t pad68c[(0x698 - 0x68c) / 4];
    cTool*       mpPrimaryTool;            // 0x698 (0x00bce3d0)

    cTurret* GetSomething() { return this; }
    cTool* GetPrimaryTool();
    IObj*  FUN_00bce5c0();
    cPointerList* GetCandidateList();      // 0x00c420d0 -> &mCandidateList
};

struct cCity {                             // cast target 0xee9b2232
    uint32_t pad00[0x324 / 4];
    ISpatial mSpatial;                     // 0x324
    Vector3* GetLocation(Vector3* out);    // 0x00bd9480
};

struct cPlanetModel {
    Vector3* DirectionToSurfacePosition(uint32_t dirId, const Vector3* dir);  // 0x00b815a0
};

// ---- spstl::slot_vector model (see slice s00abe110) -----------------------
struct SlotVector;
struct SlotEntry { uint32_t mNext; void* mpData; };

struct SlotIter {
    SlotVector* mpOwner;
    uint32_t    mIndex;
    void increment();                      // 0x00abe9b0
};

static const uint32_t kSlotEmpty = 0x3fffffff;

int __cdecl SlotDistance(SlotIter first, SlotIter last);   // 0x00abea00

struct SlotBlock { SlotEntry mEntries[128]; };

struct SlotVector {
    SlotBlock** mpBegin;                   // +0x00
    SlotBlock** mpEnd;                     // +0x04
    void*       mpField08;                 // +0x08
    void*       mpField0c;                 // +0x0c
    void*       mpField10;                 // +0x10
    uint32_t    mEndSlot;                  // +0x14
    uint32_t    mBeginIndex;               // +0x18
    uint32_t    mFreeHead;                 // +0x1c

    SlotEntry* entry(uint32_t i) { return &mpBegin[i >> 7]->mEntries[i & 0x7f]; }
    uint32_t endIndex() { return (uint32_t)((mpEnd - mpBegin) * 128) + mEndSlot - 0x7f; }
    SlotIter begin() { SlotIter it; it.mpOwner = this; it.mIndex = mBeginIndex; return it; }
    SlotIter end()   { SlotIter it; it.mpOwner = this; it.mIndex = endIndex();  return it; }
    uint32_t key(SlotIter& it) { return (uint32_t)it.mpOwner + it.mIndex; }
    uint32_t size() {
        uint32_t end = endIndex();
        uint32_t first = mBeginIndex;
        if (first >= kSlotEmpty) first = end;
        typedef int(__cdecl* Distance5)(SlotVector*, uint32_t, SlotVector*, uint32_t, SlotVector*);
        return ((Distance5)SlotDistance)(this, first, this, end, this);
    }
};

struct cSpaceTurretStateInfo {              // mStateMap value
    uint32_t pad00[2];
    uint64_t mNextFireTime;                 // +0x08
    uint64_t mNextBeamToggle;               // +0x10
    uint64_t mBeamEndTime;                  // +0x18
    int      mBeamOn;                       // +0x20
};

extern Vector3 g_vDirConstant;              // 0x0169ebe4

// ---- callees -------------------------------------------------------------
cPlanetModel* PlanetModel();                          // 0x00b3d350
Vector3* normalized_safe(Vector3* out, const Vector3* in);  // 0x00449c20
float Dot3(const Vector3& a, const Vector3& b);       // 0x00455cc0
void* FUN_00ae33b0(void* obj);                        // 0x00ae33b0 (OnAbduction)
bool  FUN_00c0c0e0(void* obj);                        // 0x00c0c0e0 (Flag388)

// ---- the behaviour -------------------------------------------------------
struct cTimer {
    uint32_t mData[8];
    void   Restart();                     // 0x00bc3130
    uint64_t GetElapsedTime();            // 0x00bc3190
};

struct cBehaviorSpaceTurret {
    uint32_t pad00[3];
    SlotVector mTargetList;               // 0x0c
    SlotVector mAgentList;                // 0x2c
    uint32_t pad48[(0x74 - 0x48) / 4];
    cSpaceTurretStateInfo* GetState(IObj* agent);   // 0x00d56510 (mStateMap)
    uint32_t pad74[(0x90 - 0x78) / 4];
    cTimer   mLifeTimer;                  // 0x90
    uint64_t mNextFiringTime;             // 0xb0
    uint32_t padb8;
    Vector3  mCityCenter;                 // 0xbc
    int      mAaShotsPerTurret;           // 0xc8
    uint32_t padcc;
    uint64_t mSdrBeamLifetime;            // 0xd0
    bool     mbWasHostile;                // 0xd8
    uint32_t paddc;
    cTimer   mScanTimer;                  // 0xe0

    void UpdateWeaponData();              // 0x00d547e0
    void Init(int arg);                   // 0x00d56630
    void StopDefense();                   // 0x00d56870
};

// ---------------------------------------------------------------------------
// @ 0x00d56630
void cBehaviorSpaceTurret::Init(int arg)
{
    mLifeTimer.Restart();
    mScanTimer.Restart();
    mNextFiringTime = mLifeTimer.GetElapsedTime();

    if (mTargetList.mBeginIndex != kSlotEmpty) {
        IObj* pFront = (IObj*)mTargetList.entry(mTargetList.mBeginIndex)->mpData;
        cCity* pCity = pFront ? (cCity*)pFront->Cast4(0xee9b2232) : 0;
        Vector3 v;
        Vector3* pPosition;
        if (pCity)
            pPosition = pCity->GetLocation(&v);
        else
            pPosition = PlanetModel()->DirectionToSurfacePosition(0x0169ebe4, &v);
        mCityCenter = *pPosition;
    }

    UpdateWeaponData();

    if (mAgentList.mBeginIndex != kSlotEmpty) {
        uint32_t first = mAgentList.mBeginIndex;
        if (first >= kSlotEmpty)
            first = mAgentList.endIndex();

        IObj* pAgent = (IObj*)mAgentList.entry(first)->mpData;
        cTurret* pTurret = pAgent ? (cTurret*)pAgent->Cast8(0x436f315) : 0;
        cTool* pTool = pTurret->GetPrimaryTool();

        uint32_t step = (uint32_t)pTool->GetRefireMs() / mAgentList.size();

        uint64_t seg = 0;
        SlotIter it = mAgentList.begin();
        uint32_t lastKey = mAgentList.key(mAgentList.end());
        while (mAgentList.key(it) != lastKey) {
            IObj* agent = (IObj*)it.mpOwner->entry(it.mIndex)->mpData;
            GetState(agent)->mNextFireTime = seg;
            GetState(agent)->mNextBeamToggle = 0;
            GetState(agent)->mBeamEndTime = 0;
            seg += step;
            it.increment();
        }
    }
    (void)arg;
}

// ---------------------------------------------------------------------------
// @ 0x00d56870
void cBehaviorSpaceTurret::StopDefense()
{
    uint64_t elapsed = mScanTimer.GetElapsedTime();
    if (elapsed <= 1000)
        return;

    mScanTimer.Restart();

    SlotIter it = mAgentList.begin();
    uint32_t lastKey = mAgentList.key(mAgentList.end());
    while (mAgentList.key(it) != lastKey) {
        IObj* pAgent = (IObj*)it.mpOwner->entry(it.mIndex)->mpData;
        cTurret* pTurret = pAgent ? (cTurret*)pAgent->Cast8(0x436f315) : 0;
        GetState(pAgent);
        cCombatantView* pCombatant = (cCombatantView*)((uint8_t*)pTurret + 0x588);
        int myTargetID = pCombatant->GetTargetID();

        if (pCombatant->GetDamageState() == 2 || pCombatant->IsDestroyed()) {
            pCombatant->SetTarget(0);
        } else {
            uint32_t bestPriority = 0;
            IObj* pBest = 0;

            cPointerList* pList = pTurret->GetCandidateList();
            for (void** pp = pList->mpBegin; pp != pList->mpEnd; ++pp) {
                IAgent* pCand = (IAgent*)*pp;
                if (pCand == 0)
                    continue;
                IObj* pOther = (IObj*)pCand->ab8(0x013f94d4);
                if (pOther == 0)
                    continue;
                if (((cCombatant*)pOther)->GetDamageState() == 2)
                    continue;
                if (((IValid*)pOther->v0c())->IsValid())
                    continue;
                if (pOther->v10() == myTargetID)
                    continue;

                uint32_t priority = 0;
                void* pBehavior = pCand->a5c(0x137e8e0);
                if (pBehavior != 0) {
                    cCombatant* pHost = (cCombatant*)((uint8_t*)pBehavior + 0x508);
                    if (pHost->GetDamageState() == 2)
                        continue;
                    if (pHost->HasEntry((uint32_t)myTargetID))
                        priority = 4;
                } else {
                    void* pPart = pCand->a5c(0x4f176642);
                    if (pPart != 0) {
                        if (((cCombatant*)((uint8_t*)pPart + 0x5a8))->HasEntry((uint32_t)myTargetID))
                            priority = 1;
                    } else {
                        void* pBio = FUN_00ae33b0(pCand);
                        if (pBio != 0 && FUN_00c0c0e0(pBio))
                            priority = 2;
                    }
                }

                if (priority > bestPriority) {
                    IObj* pSelf = pTurret->FUN_00bce5c0();
                    const Vector3& a = ((ISpatial*)((uint8_t*)pSelf + 0x120))->GetPosition();
                    const Vector3& b = pTurret->mSpatial.GetPosition();
                    Vector3 d1;
                    d1.x = b.x - a.x;
                    d1.y = b.y - a.y;
                    d1.z = b.z - a.z;
                    Vector3 n1;
                    normalized_safe(&n1, &d1);

                    IObj* pSelf2 = pTurret->FUN_00bce5c0();
                    const Vector3& a2 = ((ISpatial*)((uint8_t*)pSelf2 + 0x120))->GetPosition();
                    const Vector3& b2 = pCand->a08()->GetPosition();
                    Vector3 d2;
                    d2.x = b2.x - a2.x;
                    d2.y = b2.y - a2.y;
                    d2.z = b2.z - a2.z;
                    Vector3 n2;
                    normalized_safe(&n2, &d2);

                    if (Dot3(n1, n2) > 0.5f) {
                        bestPriority = priority;
                        pBest = pOther;
                    }
                }
            }
            pCombatant->SetTarget(pBest);
        }
        it.increment();
    }
}
