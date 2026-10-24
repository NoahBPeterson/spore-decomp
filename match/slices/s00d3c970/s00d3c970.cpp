// Slice s00d3c970: SP::cCreatureModeStrategy::SignalCreatureEvent (0x00d3cdc0).
// /O2 /arch:SSE /fp:fast module, no /EHsc.  A switch over creature-game event ids that
// advances the tutorial/cinematic state machine and awards achievements.
#include "types.h"
#include <math.h>

// ---- callee stubs (bodies elsewhere; declared without bodies so cl keeps the calls) ----
struct TutorialState {                                          // global at 0x169e230
    virtual void v00();                                         // +0x00
    virtual void v01();                                         // +0x04
    virtual void v02();                                         // +0x08
    virtual void v03();                                         // +0x0c
    virtual void Lock(int a, int b);                            // +0x10
    void SetStageA(uint32_t id);                                // 0x00b700f0
    void SetStageB(uint32_t id);                                // 0x00b706a0
    void SetStageC(uint32_t id);                                // 0x00b707a0
};
TutorialState* GetTutorialState();                              // 0x00d37cb0
void MarkEventAsOccurred(uint32_t id);                          // 0x00d387c0 (anonymous namespace)

struct Controller {                                             // Achievements::Controller
    uint32_t GetRequiredCount(uint32_t id);                     // 0x006766e0
    bool     IsAwarded(uint32_t id);                            // 0x00675e80
    void     AwardAchievement(uint32_t id);                     // 0x00676710
    void     AutoTest(uint32_t id, int n);                      // 0x00676e90
};
Controller* AchievementsController();                           // 0x00675250

struct IdVec { int* mpBegin; };
struct Item { char pad[0x104]; uint32_t mHi; uint32_t mLo; };   // +0x104 / +0x108
struct Record { Item* mpItem; char pad[0x2bc - 4]; };
struct RecordMgr { char pad[0x2e4]; Record* mpRecords; };
struct HolderB54 { char pad[0x17c]; RecordMgr* mpMgr; };

struct SpeciesProfile {
    char pad[0x594];
    float mfCount;                                              // +0x594
    char pad598[0x5d4 - 0x598];
    uint32_t m5d4, m5d8, m5dc, m5e0, m5e4, m5e8, m5ec, m5f0, m5f4;   // +0x5d4..
    char pad5f8[0x600 - 0x5f8];
    uint32_t m600, m604;
    char pad608[0x610 - 0x608];
    uint32_t m610, m614;
    char pad618[0x61c - 0x618];
    uint32_t m61c;
    IdVec* GetIds(HolderB54* h);                                // 0x004d9030
};

struct cSPCreatureBase {                                        // the avatar
    char pad[0xb20];
    SpeciesProfile* mpProfile;                                  // +0xb20
    char padb24[0xb34 - 0xb24];
    int mb34;
    char padb38[0xb54 - 0xb38];
    HolderB54* mpB54;                                           // +0xb54
    char padb58[0xb5e - 0xb58];
    bool mbB5e;
    bool FUN_c0b780();                                          // 0x00c0b780
    bool FUN_c0b7a0();                                          // 0x00c0b7a0
    bool FUN_c0b770();                                          // 0x00c0b770
    cSPCreatureBase* FUN_c0ee90();                              // 0x00c0ee90
    SpeciesProfile* GetSpeciesProfile();                        // 0x00c0bbd0
    void* FUN_c0bc00(void* a, void* b, void* c);                // 0x00c0bc00
};
struct TerrainSphere { float FUN_c75680(int i); };              // 0x00c75680
struct cGameNounManager {
    cSPCreatureBase* GetAvatar();                               // 0x00b1fdb0
    TerrainSphere* GetCurrentTerrainSphere();                   // 0x00f67d90
};
cGameNounManager* NounManager();                                // 0x00b3d300

struct Msg { uint32_t a, b, c, d; };
struct MessageServer { void Send(uint32_t id, Msg* m, void* cin); };   // 0x00adde90
MessageServer* GetMessageServer();                              // 0x00b3d4d0

struct InsRes { void* it; bool ok; };
struct Tree64 {
    char pad[0xc];
    void* mpRoot;
    uint32_t pad10;
    uint32_t mnSize;
    uint32_t pool[(0x340 - 0x18) / 4];
    Tree64();                                                   // 0x00d3b760
    void Insert(InsRes* out, const uint64_t* key);              // 0x00d3ca60
    void DoNuke(void* root);                                    // 0x00d3b370
    ~Tree64() { DoNuke(mpRoot); }
};
inline int ToInt(float f) { return (int)f; }
inline uint64_t MakeKey(uint32_t hi, uint32_t lo) { return ((uint64_t)hi << 32) | lo; }

struct DramaManager { char pad[0x10]; bool mbFlag; void FUN_d4d5c0(int n); };   // 0x00d4d5c0
DramaManager* GetDramaManager();                                // 0x00d51660

struct TestSystem { char pad[0x70]; void* mpNext; };
extern TestSystem* sTestSystem;                                 // 0x015fd928
struct ConfigMgr { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
                   virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
                   virtual void v10(); virtual void v11(); virtual int Query(uint32_t id); };   // +0x30
ConfigMgr* ConfigManager();                                     // 0x0067dd30
extern float* DAT_0169e35c;                                     // vector begin
extern float* DAT_0169e360;                                     // vector end
float FUN_d2e360();                                             // 0x00d2e360

namespace SP {
class cCreatureModeStrategy {
public:
    bool HasCreatureTutorialOccurred(uint32_t id);              // 0x00d38980
    int  RunCinematicIfNotOccurred(const char* name, uint32_t id, int flag);   // 0x00d399b0
    void AddStat(int a, int b);                                 // 0x00d39670
    void RunCinematic(const char* name, uint32_t id);           // 0x00d389d0
    bool FUN_d38900();                                          // 0x00d38900
    void FUN_d38930(uint32_t id);                               // 0x00d38930
    void SignalCreatureEvent(uint32_t eventId);                 // 0x00d3cdc0
    char mPad00[0xdd];
    bool mbDD;                                                  // +0xdd
};
}
using namespace SP;

// @ 0x00d3cdc0
void cCreatureModeStrategy::SignalCreatureEvent(uint32_t eventId)
{
    TutorialState* state = GetTutorialState();
    switch (eventId) {
    case 0x335dd8bb:
        state->SetStageC(0x85aca414);
        MarkEventAsOccurred(0x56b6c955);
        return;
    case 0x135f21b5: {
        cSPCreatureBase* avatar = NounManager()->GetAvatar();
        if (avatar) {
            SpeciesProfile* prof = avatar->mpProfile;
            int required = (int)AchievementsController()->GetRequiredCount(0x58ab9d73);
            if (avatar->mpB54 && !AchievementsController()->IsAwarded(0x58ab9d73)) {
                if ((int)prof->mfCount >= required) {
                    Tree64 tree;
                    IdVec* ids = avatar->mpProfile->GetIds(avatar->mpB54);
                    for (uint32_t i = 0; (float)i < prof->mfCount; i++) {
                        Item* item = avatar->mpB54->mpMgr->mpRecords[ids->mpBegin[i]].mpItem;
                        uint64_t key = MakeKey(item->mHi, item->mLo);
                        InsRes r;
                        tree.Insert(&r, &key);
                    }
                    if ((int)tree.mnSize >= required)
                        AchievementsController()->AwardAchievement(0x58ab9d73);
                }
            }
            int n = 0;
            if (prof->m5d4 >= 5) n++;
            if (prof->m5d8 >= 5) n++;
            if (prof->m5dc >= 5) n++;
            if (prof->m5e0 >= 5) n++;
            if (prof->m5e4 >= 5) n++;
            if (prof->m5e8 >= 5) n++;
            if (prof->m5ec >= 5) n++;
            if (prof->m5f0 >= 5) n++;
            if (prof->m5f4 >= 5) n++;
            if (prof->m600 >= 5) n++;
            if (prof->m604 >= 5) n++;
            if (prof->m610 >= 5) n++;
            if (prof->m614 >= 5) n++;
            if (prof->m61c >= 5) n++;
            if ((uint32_t)n >= AchievementsController()->GetRequiredCount(0x7055b10b))
                AchievementsController()->AwardAchievement(0x7055b10b);
        }
        return;
    }
    case 0x533535d6: {
        if (HasCreatureTutorialOccurred(0x7aee5ee7))
            return;
        state->SetStageA(0x22c77df1);
        state->SetStageA(0x8d61d137);
        state->SetStageA(0x4ad11866);
        cSPCreatureBase* avatar = NounManager()->GetAvatar();
        if (avatar->FUN_c0b780() && avatar->FUN_c0b7a0()) {
            state->SetStageB(0x8d61d137);
            return;
        }
        if (avatar->FUN_c0b780()) {
            state->SetStageB(0x22c77df1);
            return;
        }
        state->SetStageB(0x4ad11866);
        return;
    }
    case 0x533535d8: {
        if (!HasCreatureTutorialOccurred(0xea7666af)) {
            Msg msg;
            msg.b = 0;
            msg.c = 0;
            msg.d = 0x9569a644;
            float f0 = NounManager()->GetCurrentTerrainSphere()->FUN_c75680(0);
            float f1 = NounManager()->GetCurrentTerrainSphere()->FUN_c75680(1);
            if (f0 == 0.0f && f1 == 0.0f)
                msg.a = 0x4599f0e;
            else if (f0 > f1)
                msg.a = 0x61d8186;
            else
                msg.a = 0x61d8045;
            int cin = RunCinematicIfNotOccurred("CRG_FirstDNA", 0xea7666af, 0);
            if (cin != 0)
                GetMessageServer()->Send(0x7046e98b, &msg, (void*)cin);
        }
        cSPCreatureBase* avatar = NounManager()->GetAvatar();
        float* pThresh = DAT_0169e35c;
        if (pThresh != DAT_0169e360 && *pThresh <= FUN_d2e360() && avatar->FUN_c0b770() &&
            !avatar->mbB5e && !HasCreatureTutorialOccurred(0x56b6c955))
            state->SetStageB(0x85aca414);
        if (FUN_d38900()) {
            state->SetStageB(0xf3e5f2c5);
            return;
        }
        return;
    }
    case 0x533535d9:
        RunCinematicIfNotOccurred("CRG_FirstPartUnlock", 0xb721f66f, 0);
        AddStat(1, 0);
        return;
    case 0x533535da:
        RunCinematicIfNotOccurred("CRG_FirstPosse", 0x532fb9d6, 0);
        return;
    case 0x533535db: {
        cSPCreatureBase* avatar = NounManager()->GetAvatar();
        cSPCreatureBase* target = avatar->FUN_c0ee90();
        if (target && target->GetSpeciesProfile() != avatar->GetSpeciesProfile()) {
            RunCinematicIfNotOccurred("CRG_TargetedCreature", 0x135f531f, 0);
            FUN_d38930(0xfeee0549);
            GetDramaManager()->mbFlag = false;
            state->SetStageC(0x861883b4);
            return;
        }
        return;
    }
    case 0xd3353639:
        AchievementsController()->AutoTest(0xba577381, 1);
        GetDramaManager()->FUN_d4d5c0(8);
        return;
    case 0xd35dd8c3:
        MarkEventAsOccurred(0x7aee5ee7);
        state->SetStageC(0x22c77df1);
        state->SetStageC(0x8d61d137);
        state->SetStageC(0x4ad11866);
        if (!HasCreatureTutorialOccurred(0xfeee0549)) {
            GetDramaManager()->mbFlag = true;
            state->SetStageB(0x861883b4);
            return;
        }
        return;
    case 0xd3e071da:
        if (!sTestSystem || sTestSystem->mpNext == (char*)sTestSystem + 0x70) {
            if (ConfigManager()->Query(0x4ea96cb) && !HasCreatureTutorialOccurred(0x33e07240))
                RunCinematic("CRG_SocialFailure", 0x33e07240);
        }
        return;
    }
}

// ============================================================================
// Event-driven strategy helpers.
// ============================================================================

struct cRefCounted {
    virtual void v00();                                         // +0x00
    virtual void Release();                                     // +0x04
};

struct cInputStrategy {
    char mPad00[0x38];
    cRefCounted mRef;                                           // +0x38
    void Detach();                                              // 0x00d2cea0
};

struct cRefVector {
    void** mpBegin;                                             // +0x00
    void** mpEnd;                                               // +0x04
    void** erase(void** pBegin, void** pEnd);                   // 0x005c2170
};

extern SP::cCreatureModeStrategy* g_pCreatureStrategy;          // 0x0169e294
extern cRefCounted* g_pGlobalRef;                               // 0x0169e3e4
extern "C" void Fn_00d3c3b0();                                  // 0x00d3c3b0
extern "C" void __cdecl RemoveHandler(void* a, void* b, void* c, void* d, unsigned int e); // 0x00571db0

struct cStrategyFields {
    char mPad00[0x68];
    cInputStrategy* mpInput;                                    // +0x68
    char mPad6c[0x70 - 0x6c];
    void* mpMsg0;                                               // +0x70
    void* mpMsg4;                                               // +0x74
    void* mpMsg8;                                               // +0x78
    void* mpMsgC;                                               // +0x7c
    unsigned int mnMsg10;                                       // +0x80
    char mPad84[0xb4 - 0x84];
    cRefCounted* mpRefB4;                                       // +0xb4
    cRefCounted* mpRefB8;                                       // +0xb8
    cRefVector mScenarios;                                      // +0xbc
    bool Shutdown();
};

// ----------------------------------------------------------------------------
// @ 0x00d3cd00
bool cStrategyFields::Shutdown()
{
    if (mpInput) {
        mpInput->Detach();
        cInputStrategy* pIn = mpInput;
        if (pIn) {
            mpInput = 0;
            pIn->mRef.Release();
        }
    }
    Fn_00d3c3b0();
    if (g_pGlobalRef) {
        cRefCounted* pRef = g_pGlobalRef;
        g_pGlobalRef = 0;
        pRef->Release();
    }
    if (mpRefB4) {
        cRefCounted* pRef = mpRefB4;
        mpRefB4 = 0;
        pRef->Release();
    }
    if (mpRefB8) {
        cRefCounted* pRef = mpRefB8;
        mpRefB8 = 0;
        pRef->Release();
    }
    mScenarios.erase(mScenarios.mpBegin, mScenarios.mpEnd);
    if (mpMsg0) {
        void* p0 = mpMsg0;
        void* p4 = mpMsg4;
        void* p8 = mpMsg8;
        void* pC = mpMsgC;
        unsigned int n = mnMsg10;
        mpMsg0 = 0;
        RemoveHandler(p0, p4, p8, pC, n);
    }
    return true;
}

// ----------------------------------------------------------------------------
struct cLogVec {
    void** mpBegin;                                             // +0x00
    void** mpEnd;                                               // +0x04
    void** erase(void** pBegin, void** pEnd);                   // 0x00e25bd0
};

struct cLogHolder {
    char mPad00[4];
    cLogVec mList;                                              // +0x04
};

// @ 0x00d3d420
void Fn_00d3d420(cLogHolder* p)
{
    void** pEnd = p->mList.mpEnd;
    void** pBegin = p->mList.mpBegin;
    p->mList.erase(pBegin, pEnd);
}

// ----------------------------------------------------------------------------
// @ 0x00d3d4c0
void Fn_00d3d4c0()
{
    SP::cCreatureModeStrategy* pStrategy = g_pCreatureStrategy;
    pStrategy->mbDD = 1;
    pStrategy->SignalCreatureEvent(0x533535d6);
    TutorialState* state = GetTutorialState();
    state->Lock(0, 0);
}

// ----------------------------------------------------------------------------
// Int vector assignment (00d3c970).
struct cIntVector;

extern int* Fn_00d3b3c0(int* pSrcBegin, int* pSrcEnd, int* pDst);          // 0x00d3b3c0
extern void Fn_00a69490(void** ppOther, int* pSrcMid, int* pSrcEnd,
                        int* pDstEnd, cIntVector* pOther);                 // 0x00a69490
extern void Fn_00f47380(void* p);                                          // 0x00f47380

struct cIntVector {
    int* mpBegin;                                               // +0x00
    int* mpEnd;                                                 // +0x04
    int* mpCap;                                                 // +0x08
    cIntVector* Assign(cIntVector* pOther);
    int* AllocCopy(int nCount, int* pBegin, int* pEnd);         // 0x00d3b570
    void DestroyRange(int* pBegin, int* pEnd);                  // 0x004e3210
};

// @ 0x00d3c970
cIntVector* cIntVector::Assign(cIntVector* pOther)
{
    cIntVector* pSrc = pOther;
    if (pSrc == this)
        return this;

    int* pSrcBegin = pSrc->mpBegin;
    int* pSrcEnd = pSrc->mpEnd;
    unsigned int nNew = (unsigned int)(pSrcEnd - pSrcBegin);
    unsigned int nCap = (unsigned int)(mpCap - mpBegin);
    if (nNew > nCap) {
        int* pNew = AllocCopy(nNew, pSrcBegin, pSrcEnd);
        DestroyRange(mpBegin, mpEnd);
        if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0)
            Fn_00f47380(mpBegin);
        mpCap = pNew + nNew;
        mpEnd = pNew + nNew;
        mpBegin = pNew;
        return this;
    }

    unsigned int nCur = (unsigned int)(mpEnd - mpBegin);
    if (nNew > nCur) {
        Fn_00d3b3c0(pSrcBegin, pSrcBegin + nCur, mpBegin);
        Fn_00a69490((void**)&pOther, pSrc->mpBegin + (mpEnd - mpBegin),
                    pSrc->mpEnd, mpEnd, pSrc);
        mpEnd = mpBegin + nNew;
        return this;
    }

    int* pNewEnd = Fn_00d3b3c0(pSrcBegin, pSrcEnd, mpBegin);
    DestroyRange(pNewEnd, mpEnd);
    mpEnd = mpBegin + nNew;
    return this;
}

// ----------------------------------------------------------------------------
// Property-list import helpers (00d3ca90).
struct cEntry {
    unsigned int mId;                                           // +0x00
    int mValue;                                                 // +0x04
};

extern cEntry* g_pEntries;                                      // 0x01583298
extern cEntry* g_pEntriesEnd;                                   // 0x0158329c

struct cProperty;

class cPropertyObject {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08();
    virtual bool GetProperty(unsigned int nId, cProperty** ppProp);  // +0x24
};

struct cProperty {
    char mPad00[0x12];
    unsigned short mType;                                       // +0x12
    int* GetInt();                                              // 0x0041e990
};

extern "C" void __cdecl Fn_00d3bc40(cEntry* pBegin, cEntry* pEnd, void* pContext); // 0x00d3bc40

static __forceinline void ImportIntProperty(cPropertyObject* pObj,
                                            unsigned int nPropId,
                                            unsigned int nEntryId,
                                            cProperty** ppProp)
{
    if (pObj->GetProperty(nPropId, ppProp) && (*ppProp)->mType == 9) {
        int nValue = *(*ppProp)->GetInt();
        cEntry* e = g_pEntries;
        while (e != g_pEntriesEnd && e->mId != nEntryId)
            ++e;
        if (e != g_pEntriesEnd)
            e->mValue = nValue;
    }
}

// @ 0x00d3ca90
void Fn_00d3ca90(cPropertyObject* pObj)
{
    cProperty* pProp;
    if (pObj) {
        ImportIntProperty(pObj, 0x816e292, 0x887c91bb, &pProp);
        ImportIntProperty(pObj, 0xdda63aed, 0x9d62e363, &pProp);
        ImportIntProperty(pObj, 0xc77a6c53, 0x91ca5e8c, &pProp);
        ImportIntProperty(pObj, 0xda7e582a, 0xde8f240b, &pProp);
        ImportIntProperty(pObj, 0xd0780e75, 0x228d8f36, &pProp);
        ImportIntProperty(pObj, 0x261fa6b9, 0x7f466450, &pProp);
        ImportIntProperty(pObj, 0x80b1e465, 0xa0325a4f, &pProp);
    }
    Fn_00d3bc40(g_pEntries, g_pEntriesEnd, pProp);
}

// ============================================================================
// Scenario item-unlock effect (00d3d4f0).
// ============================================================================
struct Vector3f { float x, y, z; };
struct Quaternionf { float x, y, z, w; };
struct Matrix33f { float m[9]; };

struct XformMsg {                       // 0x38 bytes; ctor @ 0x434040
    unsigned short flags;               // +0x00
    unsigned short count;               // +0x02
    Vector3f pos;                       // +0x04
    float scale;                        // +0x10
    Matrix33f rot;                      // +0x14
    XformMsg();
};

void SplitItemId(unsigned long long id, unsigned int* pHi, unsigned int* pLo);   // 0x00593960

struct cScaleHolder {
    char mPad00[0x14];
    float mScale;                       // +0x14
};

class cUnlockOwner {
public:
    virtual void v00();                                 // +0x00
    virtual void v04();                                 // +0x04
    virtual void v08();                                 // +0x08
    virtual cUnlockOwner* GetChild(unsigned int id);    // +0x0c
    virtual void v10();                                 // +0x10
    virtual void v14();                                 // +0x14
    virtual void v18();                                 // +0x18
    virtual void v1c();                                 // +0x1c
    virtual void v20();                                 // +0x20
    virtual void v24();                                 // +0x24
    virtual void v28();                                 // +0x28
    virtual Vector3f* GetDirection();                   // +0x2c
    virtual void v30();                                 // +0x30
    virtual void v34();                                 // +0x34
    virtual void v38();                                 // +0x38
    virtual void v3c();                                 // +0x3c
    virtual void v40();                                 // +0x40
    virtual void v44();                                 // +0x44
    virtual void v48();                                 // +0x48
    virtual void v4c();                                 // +0x4c
    virtual void v50();                                 // +0x50
    virtual void v54();                                 // +0x54
    virtual void v58();                                 // +0x58
    virtual void v5c();                                 // +0x5c
    virtual void v60();                                 // +0x60
    virtual void v64();                                 // +0x64
    virtual cScaleHolder* GetScaleHolder();             // +0x68
};

class cPlanetModel {
public:
    Quaternionf BuildSurfaceOrientation(const Vector3f& pos);      // 0x00b7f190
};
cPlanetModel* PlanetModel();                                       // 0x00b3d350
Matrix33f& Matrix3FromQuaternion(Matrix33f& out, const Quaternionf& q);   // 0x0059c190

class IEffectObj {
public:
    virtual void v00();                                 // +0x00
    virtual void Release();                             // +0x04
    virtual void Start(int flag);                       // +0x08
    virtual void v0c();                                 // +0x0c
    virtual void v10();                                 // +0x10
    virtual void v14();                                 // +0x14
    virtual void SetTransform(XformMsg* msg);           // +0x18
};

class cEffectsMgr {
public:
    virtual void e00();                                 // +0x00
    virtual void e04();                                 // +0x04
    virtual void e08();                                 // +0x08
    virtual void e0c();                                 // +0x0c
    virtual void e10();                                 // +0x10
    virtual void e14();                                 // +0x14
    virtual void e18();                                 // +0x18
    virtual void e1c();                                 // +0x1c
    virtual void e20();                                 // +0x20
    virtual void e24();                                 // +0x24
    virtual void e28();                                 // +0x28
    virtual bool CreateEffect(unsigned int key, int unused, IEffectObj** ppOut);   // +0x2c
};
cEffectsMgr* EffectsManagerPtr();                       // 0x0067ddd0

class IPropObj {
public:
    virtual void p00();                                 // +0x00
    virtual void Release();                             // +0x04
};

class cPropMgr {
public:
    virtual void r00();                                 // +0x00
    virtual void r04();                                 // +0x04
    virtual void r08();                                 // +0x08
    virtual void r0c();                                 // +0x0c
    virtual void r10();                                 // +0x10
    virtual void r14();                                 // +0x14
    virtual void r18();                                 // +0x18
    virtual void r1c();                                 // +0x1c
    virtual void r20();                                 // +0x20
    virtual void r24();                                 // +0x24
    virtual void r28();                                 // +0x28
    virtual bool FindProperty(unsigned int a, unsigned int b, void** ppOut);   // +0x2c
};
cPropMgr* PropertyManagerPtr();                         // 0x0067de30

struct CardArea {
    unsigned int x, y, z;
    CardArea(unsigned int a, unsigned int b, unsigned int c) : x(a), y(b), z(c) {}
};

class cMissionManager {
public:
    virtual void m00();                                 // +0x00
    virtual void m04();                                 // +0x04
    virtual void m08();                                 // +0x08
    virtual void m0c();                                 // +0x0c
    virtual void m10();                                 // +0x10
    virtual void m14();                                 // +0x14
    virtual void m18();                                 // +0x18
    virtual void m1c();                                 // +0x1c
    virtual void m20();                                 // +0x20
    virtual void m24();                                 // +0x24
    virtual void FUN_0a(void* p);                       // +0x28
    void SetCardArea(CardArea area);                    // 0x00d37f10
};
extern cMissionManager* g_pMissionManager;              // 0x0169e230
extern unsigned char g_bUnlockFlag;                     // 0x0169e290
extern float g_fUnlockX;                                // 0x0169e298
extern float g_fUnlockY;                                // 0x0169e29c
extern float g_fUnlockZ;                                // 0x0169e2a0

class cCollectableItems {
public:
    unsigned int GetItemFlags(unsigned long long id);   // 0x00596e40
};

class cPanel {
public:
    void FUN_00e19350(unsigned int key, int arg);       // 0x00e19350
};
void* Fn_00b3d3f0(int a, void* b);                      // 0x00b3d3f0

struct Triple { unsigned int a, b, c; };
void Fn_00e39710(unsigned int id, void* p);             // 0x00e39710
unsigned int GetGameModeId();                           // 0x00b5b800

// @ 0x00d3d4f0
void __stdcall Fn_00d3d4f0(unsigned long long nItemId, cUnlockOwner* pOwner,
                  cCollectableItems* pItems, bool bFlag)
{
    Vector3f pos;
    pos.x = g_fUnlockX;
    pos.y = g_fUnlockY;
    pos.z = g_fUnlockZ;

    if (pOwner != 0) {
        cUnlockOwner* pObj = pOwner->GetChild(0x1186577);
        if (pObj != 0) {
            Vector3f* pDir = pObj->GetDirection();
            pos = *pDir;
            float fInv = 1.0f / sqrtf(pos.z * pos.z + pos.x * pos.x + pos.y * pos.y);
            Vector3f unit;
            unit.x = pos.x * fInv;
            unit.y = pos.y * fInv;
            unit.z = pos.z * fInv;
            float fScale = pObj->GetScaleHolder()->mScale;
            pos.x += unit.x * fScale;
            pos.y += unit.y * fScale;
            pos.z += unit.z * fScale;
        }
    }

    unsigned int nHi;
    unsigned int nLo;
    SplitItemId(nItemId, &nHi, &nLo);

    if (GetGameModeId() == 0x1654c01) {
        SP::cCreatureModeStrategy* pStrategy = g_pCreatureStrategy;
        GetTutorialState();
        pStrategy->RunCinematicIfNotOccurred("CRG_FirstPartUnlock", 0xb721f66f, 0);
        pStrategy->AddStat(1, 0);
        if (bFlag || g_bUnlockFlag != 0)
            g_pMissionManager->SetCardArea(CardArea(nLo, 0xb1b104, nHi));
        cPanel* pPanel = (cPanel*)Fn_00b3d3f0(-0xf, (void*)nLo);
        pPanel->FUN_00e19350(0xfffffff1u, (int)nLo);
        cSPCreatureBase* pAvatar = NounManager()->GetAvatar();
        if (pAvatar != 0) {
            Triple areaA = { 0, 0, 0 };
            Triple areaB = { 0, 0, 0 };
            Triple item = { nLo, 0xb1b104, nHi };
            void* pOut = pAvatar->FUN_c0bc00(&areaA, &areaB, &item);
            Fn_00e39710(0xae2329c6, pOut);
        }
    }

    cPropMgr* pPropMgr = PropertyManagerPtr();
    void* pProp = 0;
    if (pPropMgr->FindProperty(nLo, nHi, &pProp)) {
        unsigned int nItem = pItems->GetItemFlags(nItemId);
        if (nItem != 0 && bFlag) {
            IEffectObj* pEffect = 0;
            cEffectsMgr* pEffects = EffectsManagerPtr();
            if (pEffect != 0)
                pEffect->Release();
            if (pEffects->CreateEffect(nItem, 0, &pEffect)) {
                XformMsg msg;
                msg.flags |= 4;
                msg.pos = pos;
                ++msg.count;
                Quaternionf quat = PlanetModel()->BuildSurfaceOrientation(pos);
                Matrix33f mat;
                Matrix3FromQuaternion(mat, quat);
                msg.rot = mat;
                msg.flags |= 2;
                ++msg.count;
                pEffect->SetTransform(&msg);
                pEffect->Start(0);
            }
            if (pEffect != 0)
                pEffect->Release();
        }
    }
    g_pMissionManager->FUN_0a(0);
    if (pProp != 0)
        ((IPropObj*)pProp)->Release();
}
