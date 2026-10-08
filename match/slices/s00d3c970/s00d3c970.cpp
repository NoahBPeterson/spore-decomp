// Slice s00d3c970: SP::cCreatureModeStrategy::SignalCreatureEvent (0x00d3cdc0).
// /O2 /arch:SSE /fp:fast module, no /EHsc.  A switch over creature-game event ids that
// advances the tutorial/cinematic state machine and awards achievements.
#include "types.h"

// ---- callee stubs (bodies elsewhere; declared without bodies so cl keeps the calls) ----
struct TutorialState {                                          // global at 0x169e230
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
