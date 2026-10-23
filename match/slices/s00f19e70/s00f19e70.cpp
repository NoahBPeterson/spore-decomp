// slice s00f19e70 -- scenario play-mode goals / progress-bar helpers around 0x00f19e70.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc, no /GS: no EH frames or cookies)
#include "types.h"
#include <math.h>
#include <stdlib.h>

#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4

struct Vec3 { float x, y, z; };
struct BBox { Vec3 mMin; Vec3 mMax; };
struct Avatar;

// ---------------------------------------------------------------------------
// collaborators
// ---------------------------------------------------------------------------
struct IClassId { int* FUN_006c0200();                       // 0x006c0200
                  void FUN_00c8ad30(uint32_t id, int a); };   // 0x00c8ad30
// spatial interface used by the object query (slots 0x2c/0x68/0x6c/0x74)
struct ISpatial
{
    PV8 PV2 PV                                        // 0x00..0x28
    virtual Vec3* GetPos();                           // 0x2c
    PV8 PV4 PV2                                       // 0x30..0x64
    virtual BBox* GetBBoxAt68();                      // 0x68
    virtual BBox* GetBBox(BBox* out);                 // 0x6c
    virtual void v70();                               // 0x70
    virtual float GetRadius();                        // 0x74
};

struct ObjHdr
{
    PV PV PV
    virtual void* Query(uint32_t id);                 // 0x0c
    PV4
    virtual uint32_t GetTypeID();                     // 0x20
    PV2
    virtual bool IsDestroyed();                       // 0x2c
    PV8 PV8 PV8 PV8 PV2
    virtual void* QueryClassId(uint32_t id);          // 0xb8
    void FUN_00b18530();                              // 0x00b18530
};

struct cGameNounManager
{
    Avatar* GetAvatar();                              // 0x00b1fdb0
    void* GetItemID();                                // 0x00b1f9c0
    void RemoveNoun(void* noun);                      // 0x00b225d0
};

struct Avatar
{
    char pad0[0xc0];
    ISpatial mSpatial;                                // 0xc0
    char pad1[0x4e4];
    int Count();                                      // 0x00c0f780
    ObjHdr* At(int idx);                              // 0x00c0f8a0
    int Next(int idx);                                // 0x00c0f810
    void SetSprinting(int b);                         // 0x00c1ad10
};

cGameNounManager* __cdecl NounManager();              // 0x00b3d300

struct cGameTimeManager
{
    void IncPauseGate(uint32_t gate);                 // 0x00b32220
};
cGameTimeManager* __cdecl GameTimeManager();          // 0x00b3d380

struct ICreatureAnim
{
    void PlayAnimation(int id, int a, int b);         // 0x00c12190
    void FUN_00bfc470(int a);                         // 0x00bfc470
};

struct ICreatureFlags { char pad[0xb4c]; struct ICreatureData* mpData; };
struct ICreatureData  { char pad[0x5fc]; uint32_t mFlags; };
struct ICreatureFlags50 { char pad[0x50]; uint32_t mFlags; };

struct ICreatureComp
{
    bool Flag388();                                    // 0x00c0c0e0
};

struct Stopwatch
{
    uint32_t mnStartTimeLo;                           // +0x00
    uint32_t mnStartTimeHi;                           // +0x04
    uint32_t mnTotalElapsedTimeLo;                    // +0x08
    uint32_t mnTotalElapsedTimeHi;                    // +0x0c
    int      mnUnits;                                 // +0x10
    float    mfCyclesToUnits;                         // +0x14
    void Restart();                                   // 0x00571e80
};

struct cScenarioPlaySummary
{
    int   mNumCreaturesKilled;                        // +0x00
    int   mNumBuildingsDestroyed;                     // +0x04
    int   mNumVehiclesDestroyed;                      // +0x08
    int   mNumCastMembersDefended;                    // +0x0c
    int   mNumCreaturesBefriended;                    // +0x10
    int   mNumObjectsCollected;                       // +0x14
    int   field_18;                                   // +0x18
    int   mNumGoalsCompleted;                         // +0x1c
    int   mNumDeaths;                                 // +0x20
    int   mNumPosseMembersLost;                       // +0x24
    uint32_t mAmountDamageDealt;                      // +0x28
    int   mNumTimesUsedJetPack;                       // +0x2c
    int   mNumTimesUsedSprint;                        // +0x30
    int   mNumBarrelsDestroyed;                       // +0x34
    int   mNumCastMembersTalkedTo;                    // +0x38
    float mAmountHealthRegained;                      // +0x3c
    float mAmountDamageReceived;                      // +0x40
    float mAmountEnergyUsed;                          // +0x44
};

struct cScenarioGoal
{
    int mType;                                        // +0x24 in goal
    uint32_t mTargetID;                               // +0x28 in goal
};

struct cScenarioPlayModeGoal                         // 0x1ac bytes
{
    bool mIsCompleted;                                // +0x00
    bool field_1;
    int  mCount;                                      // +0x04
    char field_8[0x1c];                               // +0x08
    cScenarioGoal mGoal;                              // +0x24
    int  field_2c;                                    // +0x2c
    char pad[0x1ac - 0x30];
};

struct cScenarioClassRef                              // field_CC
{
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual void* Cast(uint32_t typeID);              // +0x0c
    char pad[0x18];
    int  mClassID;                                    // +0x1c
};

struct cScenarioActEntry                             // 0x188 bytes
{
    int mType;                                        // +0x00
    int mTargetID;                                    // +0x04
    char pad[0x188 - 8];
};

struct cScenarioAct
{
    char pad[0x84];
    cScenarioActEntry* mEntriesBegin;                 // +0x84
    cScenarioActEntry* mEntriesEnd;                   // +0x88
};

struct cScenarioResource
{
    char pad0[0x23c];
    cScenarioAct* mActsBegin;                         // +0x23c
    cScenarioAct* mActsEnd;                           // +0x240
    char pad1[0x2c10 - 0x244];
    void* mGoalEntriesBegin;                          // +0x2c10
    void* mGoalEntriesEnd;                            // +0x2c14
    char pad2[0x2c24 - 0x2c18];
    uint32_t mGoalEntryIndex;                         // +0x2c24
};

struct cScenarioData
{
    char pad0[0x10];
    cScenarioResource* mpResource;                    // +0x10
    int GetActCount();                                // 0x00f3be30
    cScenarioAct* GetAct(int actIndex);               // 0x00f3be60
    void* FUN_00f3e8a0(int id);                       // 0x00f3e8a0
    void* FUN_00f3d780(void* key);                    // 0x00f3d780
    void* FUN_00f3e900(void* obj);                    // 0x00f3e900
};

struct cScenarioPanel { void FUN_00e15620();                              // 0x00e15620
                        void FUN_00e154d0(int); };                        // 0x00e154d0
struct cScenarioPanel2 { void FUN_00f18660(void* playMode); };             // 0x00f18660
struct cScenarioDisplay
{
    char pad0[0x12c];
    cScenarioPanel2* mpPanel;                          // +0x12c
    char pad1[0x148 - 0x130];
    cScenarioPanel* mpPanel2;                          // +0x148
};

struct cScenarioMode
{
    char pad0[0x6c];
    cScenarioDisplay* mpScenarioDisplayStrategy;       // +0x6c
    char pad1[4];
    cScenarioData* mpData;                             // +0x74
    char pad2[0x58];
    int  mPlayType;                                    // +0xd0
};

extern cScenarioMode* sScenarioMode;                   // 0x016c7aa4

struct cActionTarget
{
    int mValue;
    cActionTarget(void* ref);                          // 0x00ad7a30
    ~cActionTarget();                                  // 0x00ad7ad0
};

struct cTriggerMgr
{
    char pad[0x3c4];
    int  mCurrentTriggerType;                          // +0x3c4
    void PostAction(uint32_t id, cActionTarget* target, int a);   // 0x00ae09b0
    int  PostTrigger(uint32_t id, int a, int b, int c, int d, int e);   // 0x00ae0930
};
cTriggerMgr* __cdecl GetTriggerMgr();                  // 0x00b3d4d0

struct IAudio
{
    PV8 PV8 PV4                                        // 0x00..0x34
    virtual void SetA(uint32_t id);                    // 0x38
    virtual void SetB(uint32_t id);                    // 0x3c
    virtual void SetC(uint32_t id, int b);             // 0x40
    virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void SetD(uint32_t id, void* pos);         // 0x50
    virtual void v54();
    virtual void SetE();                               // 0x58
};
IAudio* __cdecl GetSystemAT();                         // 0x00a206f0

struct ICreatureComp84
{
    PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV                         // 0x00..0x80
    virtual void SetSomething(int a, void* b, int c);          // 0x84
};

// scenario-object (goal entry) accessors for 0xf1ad00
struct IGoalObj
{
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual void* Query(uint32_t id);                  // +0x0c
    char pad[0x38 - 0x10];
    int mState;                                        // +0x38
};

struct IControlObj
{
    virtual void v00();
    char pad[0x70 - 4];
    int mState74;                                      // +0x70
};

// ---------------------------------------------------------------------------
// globals used by these functions
// ---------------------------------------------------------------------------
extern float g_1471064;      // 0.5f           0x01471064
extern float g_1473c70;      // 10.0f          0x01473c70
extern float g_15ad940;      // 0x015ad940
extern float g_15ad93c;      // 0x015ad93c
extern float g_15ad938;      // 0x015ad938
extern float g_15ad934;      // 0x015ad934
extern float g_15ad930;      // 0x015ad930
extern float g_15ad92c;      // 0x015ad92c
extern float g_15ad928;      // 0x015ad928
extern float g_15ad924;      // 0x015ad924
extern uint32_t g_15ada60;   // 0x015ada60
extern uint32_t g_15ada6c;   // 0x015ada6c

// ---------------------------------------------------------------------------
// other TU entry points
// ---------------------------------------------------------------------------
void* __cdecl FUN_00b3d240();                          // 0x00b3d240
bool __cdecl cScenarioPlayProgressBar_Pred(void*);     // 0x00f19e00
void __cdecl ScenarioTutorials_CloseWindow();          // 0x00efcae0
void __cdecl FUN_00572020(void* p, int b);             // 0x00572020
int  __cdecl GetRecorderState();                       // 0x00435e90
void __cdecl KillSetiEffects(uint32_t id, int state);  // 0x00435ed0
void __cdecl CalloutMessageBox(void* a, void* b);      // 0x00809db0
void* __cdecl ObjectTemplateDB();                      // 0x0067cb40
void __cdecl FUN_00eed9c0(void* a, void* b);           // 0x00eed9c0
void __cdecl FUN_00eeda20(void* a, void* b);           // 0x00eeda20
void __cdecl FUN_00f24190(void* a, void* b);           // 0x00f24190
void* __cdecl FUN_00f238e0(void* key);                 // 0x00f238e0
void __cdecl FUN_00f1a910();                           // 0x00f1a910
int  __cdecl FUN_00ebfdc0(void* obj);                  // 0x00ebfdc0
void __cdecl cScenarioPlayProgressBar_SetAttr(ObjHdr* target);   // 0x00f19530

struct IScenarioHolder
{
    bool FUN_00f27730();                               // 0x00f27730
    bool FUN_00f25330();                               // 0x00f25330
};

struct IObjTemplateDB
{
    PV8 PV8 PV4 PV2
    virtual void FUN_58(void* key, int b);             // 0x58
};

struct IDateTime { void Set(int v); };                 // 0x0092e3d0

// ---------------------------------------------------------------------------
// Simulator::cScenarioPlayMode
// ---------------------------------------------------------------------------
namespace Simulator {

class cScenarioPlayMode
{
public:
    virtual ~cScenarioPlayMode();
    virtual bool HandleMessage(uint32_t messageID, void* msg);

    void UpdateGoalStatus();                                         // 0x00f1c4b0
    void StartAdventure();                                           // 0x00f198d0
    void OnTimerMessage();                                           // 0x00f1c2f0
    void CompleteGoal(cScenarioPlayModeGoal* goal, void* by);        // 0x00f1ae10
    void SetState(int state);                                        // 0x00f1aae0

    void FUN_00f1a120(void* refA, cScenarioClassRef* refB);
    int  FUN_00f1a320(Avatar* who, ObjHdr* target, char* outFlag);
    bool FUN_00f1a440(int idx, ObjHdr* target);
    bool FUN_00f1a640(int idx);
    bool FUN_00f1a7a0(int type, ObjHdr* target);
    void FUN_00f1a7f0(ObjHdr* target);
    void FUN_00f1a890();
    void FUN_00f1a970(int b);

    /* 04h */ void* mpRefVtbl;
    /* 08h */ int   mnRefCount;
    /* 0Ch */ cScenarioPlaySummary mSummary;
    /* 54h */ char  mFailReason[0x10];
    /* 64h */ cScenarioPlayModeGoal* mCurrentGoalsBegin;
    /* 68h */ cScenarioPlayModeGoal* mCurrentGoalsEnd;
    /* 6Ch */ char  pad6c[0x24];
    /* 90h */ int   mCurrentPlayModeState;
    /* 94h */ int   mCurrentEndCinematicState;
    /* 98h */ Stopwatch mStopwatch;
    /* B0h */ int   field_B0;
    /* B4h */ int   field_B4;
    /* B8h */ int   mCurrentActIndex;
    /* BCh */ char  padbc[0x0c];
    /* C8h */ void* field_C8;
    /* CCh */ cScenarioClassRef* field_CC;
    /* D0h */ int   field_D0;
    /* D4h */ int   mCurrentDialogBoxIndex;
    /* D8h */ int   field_D8;
    /* DCh */ char  paddc[0x14];
    /* F0h */ void* field_F0;
    /* F4h */ void* field_F4;
    /* F8h */ float mIntroFadeinTimer;
    /* FCh */ bool  mIsIntroFadeinActive;
};

}  // namespace Simulator

using Simulator::cScenarioPlayMode;

// ---------------------------------------------------------------------------
// @ 0x00f19e70
// ---------------------------------------------------------------------------
void __cdecl FUN_00f19e70(void* target, bool* outA, bool* outB)
{
    cGameNounManager* nouns = NounManager();
    Avatar* avatar = nouns->GetAvatar();

    ISpatial* targetSp = 0;
    if (target)
        targetSp = (ISpatial*)((ObjHdr*)target)->Query(0x1186577);

    BBox boxA;
    BBox* a = avatar->mSpatial.GetBBox(&boxA);
    Vec3 centerA;
    centerA.x = (a->mMax.x + a->mMin.x) * g_1471064;
    centerA.y = (a->mMax.y + a->mMin.y) * g_1471064;
    centerA.z = (a->mMax.z + a->mMin.z) * g_1471064;

    BBox boxB;
    BBox* b = targetSp->GetBBox(&boxB);
    Vec3 centerB;
    centerB.x = (b->mMax.x + b->mMin.x) * g_1471064;
    centerB.y = (b->mMax.y + b->mMin.y) * g_1471064;
    centerB.z = (b->mMax.z + b->mMin.z) * g_1471064;

    float dx = centerA.x - centerB.x;
    float dy = centerA.y - centerB.y;
    float dz = centerA.z - centerB.z;
    float dist = sqrtf(dx * dx + (dy * dy + dz * dz));
    float d = dist - avatar->mSpatial.GetRadius();
    d = d - targetSp->GetRadius();

    if (g_15ad940 > d)
    {
        int selected = 0;
        void* mgr = FUN_00b3d240();
        void* vt = *(void**)mgr;
        typedef bool (__thiscall* Fn)(void*, Vec3*, Vec3*, bool (__cdecl*)(void*), int*, BBox*, int);
        Fn fn = (Fn)((void**)vt)[0x50 / 4];
        if (fn(mgr, &centerA, &centerB, cScenarioPlayProgressBar_Pred, &selected, &boxA, 1)
            && (void*)selected == target)
        {
            *outA = true;
            *outB = d < g_15ad93c;
            if (selected)
            {
                void* obj = (void*)selected;
                void* ovt = *(void**)obj;
                ((void (__thiscall*)(void*))((void**)ovt)[1])(obj);
            }
            return;
        }
        if (selected)
        {
            void* obj = (void*)selected;
            void* ovt = *(void**)obj;
            ((void (__thiscall*)(void*))((void**)ovt)[1])(obj);
        }
    }
    *outA = false;
    *outB = false;
}

// ---------------------------------------------------------------------------
// @ 0x00f1a070
// ---------------------------------------------------------------------------
bool __stdcall FUN_00f1a070(ObjHdr* target)
{
    Avatar* avatar = NounManager()->GetAvatar();
    ISpatial* targetSp;
    if (target)
        targetSp = (ISpatial*)target->Query(0x1186577);
    else
        targetSp = 0;
    Vec3* tp = targetSp->GetPos();
    Vec3* ap = avatar->mSpatial.GetPos();

    float dx = ap->x - tp->x;
    float dy = ap->y - tp->y;
    float dz = ap->z - tp->z;
    return sqrtf((dz * dz + dx * dx) + dy * dy)
           < avatar->mSpatial.GetRadius() + targetSp->GetRadius() + g_15ad93c;
}

// ---------------------------------------------------------------------------
// @ 0x00f1a120
// ---------------------------------------------------------------------------
void cScenarioPlayMode::FUN_00f1a120(void* refA, cScenarioClassRef* refB)
{
    ObjHdr* target = (ObjHdr*)refB;
    if (target)
    {
        ISpatial* sp = (ISpatial*)target->Query(0x1186577);
        if (sp)
        {
            IAudio* audio = GetSystemAT();
            if (audio)
            {
                audio->SetA(0x7f43dc0);
                audio->SetD(0x39e41ea, sp->GetPos());
                audio->SetC(0x39e3c9f, 1);
                audio->SetE();
            }
        }
    }
    field_C8 = refA;
    field_CC = refB;

    void* classRef = 0;
    if (target)
        classRef = target->Query(0x1186577);

    cActionTarget action(classRef);
    GetTriggerMgr()->PostAction(0x57c38207, &action, 0);

    Avatar* avatar = NounManager()->GetAvatar();
    ObjHdr* comp = 0;
    if (avatar)
        comp = (ObjHdr*)((ObjHdr*)avatar)->Query(0xce9f6639);

    void* arg = 0;
    if (target)
        arg = target->Query(0x13f94d4);
    ((ICreatureComp84*)comp)->SetSomething(1, arg, 0);

    ICreatureComp84* other = 0;
    if (target)
        other = (ICreatureComp84*)target->Query(0xce9f6639);
    if (other)
        other->SetSomething(1, (char*)avatar + 0x5a8, 0);

    mCurrentDialogBoxIndex = -1;
    field_D8 = GetTriggerMgr()->PostTrigger(0x148c2c8, 1, 0, 0, 0, 0);

    int mode = 0;
    if (target)
    {
        if (target->Query(0x0e9cb8ba))
            goto done;
        if (target->Query(0x137e8e0))
        {
            mode = 1;
            goto done;
        }
    }
    if (other)
    {
        if (((ICreatureComp*)other)->Flag388())
        {
            mode = 2;
            goto done;
        }
        ICreatureData* data = *(ICreatureData**)((char*)other + 0xb4c);
        mode = (data->mFlags & 0x200) ? 3 : 4;
    }
done:
    GetTriggerMgr()->mCurrentTriggerType = mode;
    ++mSummary.mNumCastMembersTalkedTo;
    field_D0 = mode;
}

// ---------------------------------------------------------------------------
// @ 0x00f1a320
// ---------------------------------------------------------------------------
int cScenarioPlayMode::FUN_00f1a320(Avatar* who, ObjHdr* target, char* outFlag)
{
    int found = -1;
    int first = who->Count();
    int i = first;
    do
    {
        if (i == -1)
            return first;
        for (;;)
        {
            if (found != -1)
                return found;
            ObjHdr* obj = who->At(i);
            void* classRef = 0;
            if (obj)
                classRef = obj->QueryClassId(0x17f243b);

            unsigned count = (unsigned)(mCurrentGoalsEnd - mCurrentGoalsBegin);
            unsigned n = 0;
            if (count != 0)
            {
                for (;;)
                {
                    cScenarioPlayModeGoal* goal = mCurrentGoalsBegin + n;
                    if (goal->mGoal.mType == 9 && !goal->mIsCompleted)
                    {
                        int* a = ((IClassId*)classRef)->FUN_006c0200();
                        if (a)
                        {
                            if (goal->mGoal.mTargetID == *a)
                            {
                                int* b = ((IClassId*)target)->FUN_006c0200();
                                if (b)
                                {
                                    if (goal->field_2c == *b)
                                    {
                                        found = i;
                                        if (outFlag)
                                            *outFlag = 1;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    ++n;
                    if (n >= count)
                        break;
                }
            }
            if (found != -1)
                continue;
            i = who->Next(i);
            if (i == -1)
                return first;
        }
    } while (true);
}

// ---------------------------------------------------------------------------
// @ 0x00f1a440
// ---------------------------------------------------------------------------
bool cScenarioPlayMode::FUN_00f1a440(int idx, ObjHdr* target)
{
    Avatar* avatar = NounManager()->GetAvatar();
    ObjHdr* obj = avatar->At(idx);
    void* ref = 0;
    if (obj)
        ref = obj->QueryClassId(0x17f243b);
    int* a = ((IClassId*)ref)->FUN_006c0200();
    if (!a)
        return false;
    int id1 = *a;

    int* b = ((IClassId*)target)->FUN_006c0200();
    if (!b)
        return false;
    int id2 = *b;

    cScenarioData* data = sScenarioMode->mpData;
    void* holder = data->FUN_00f3e8a0(id2);
    if (holder && !((IScenarioHolder*)holder)->FUN_00f25330())
        return false;

    bool typeMatch = false;
    uint32_t type = target->GetTypeID();
    if (type != 0x70703b3)
    {
        type = target->GetTypeID();
        typeMatch = type == 0x18c6de8;
    }
    else
        typeMatch = true;

    int count = (int)(mCurrentGoalsEnd - mCurrentGoalsBegin);
    bool sawTarget = false;
    bool sawPair = false;
    cScenarioPlayModeGoal* goal = mCurrentGoalsBegin;
    for (int n = 0; n < count; ++n, ++goal)
    {
        if (((goal->mGoal.mType == 9 && !goal->mIsCompleted)
             || (goal->mGoal.mType == 8 && goal->mIsCompleted))
            && goal->mGoal.mTargetID == id1)
        {
            sawTarget = true;
            if (goal->field_2c == id2)
                sawPair = true;
        }
    }
    if (sawTarget)
    {
        if (!sawPair)
            return false;
        return true;
    }

    bool result = false;
    if (!typeMatch)
    {
        result = true;
        int actIndex = mCurrentActIndex + 1;
        int actCount = data->GetActCount();
        while (actIndex < actCount)
        {
            cScenarioAct* act = data->GetAct(actIndex);
            int n = (int)(act->mEntriesEnd - act->mEntriesBegin);
            cScenarioActEntry* e = act->mEntriesBegin;
            for (int i = 0; i < n; ++i, ++e)
            {
                if ((e->mType == 9 || e->mType == 8) && e->mTargetID == id1)
                {
                    result = false;
                    i = n;
                    break;
                }
            }
            ++actIndex;
            actCount = data->GetActCount();
        }
    }
    return result;
}

// ---------------------------------------------------------------------------
// @ 0x00f1a640
// ---------------------------------------------------------------------------
bool cScenarioPlayMode::FUN_00f1a640(int idx)
{
    bool result = true;
    Avatar* avatar = NounManager()->GetAvatar();
    ObjHdr* obj = avatar->At(idx);
    void* ref = 0;
    if (obj)
        ref = obj->QueryClassId(0x17f243b);
    int* a = ((IClassId*)ref)->FUN_006c0200();
    if (!a)
        return true;
    int id = *a;

    cScenarioData* data = sScenarioMode->mpData;
    void* holder = data->FUN_00f3e8a0(id);
    if (holder && ((IScenarioHolder*)holder)->FUN_00f27730())
        return false;

    int count = (int)(mCurrentGoalsEnd - mCurrentGoalsBegin);
    cScenarioPlayModeGoal* goal = mCurrentGoalsBegin;
    for (int n = 0; n < count; ++n, ++goal)
    {
        if (goal->mGoal.mTargetID != id)
            continue;
        if (goal->mGoal.mType == 9 && !goal->mIsCompleted)
            return false;
        if (goal->mGoal.mType == 8 && goal->mIsCompleted)
            return false;
    }

    int actIndex = mCurrentActIndex + 1;
    int actCount = data->GetActCount();
    while (actIndex < actCount)
    {
        cScenarioAct* act = data->GetAct(actIndex);
        int n = (int)(act->mEntriesEnd - act->mEntriesBegin);
        cScenarioActEntry* e = act->mEntriesBegin;
        for (int i = 0; i < n; ++i, ++e)
        {
            if ((e->mType == 9 || e->mType == 8) && e->mTargetID == id)
            {
                result = false;
                i = n;
                break;
            }
        }
        ++actIndex;
        actCount = data->GetActCount();
    }
    return result;
}

// ---------------------------------------------------------------------------
// @ 0x00f1a7a0
// ---------------------------------------------------------------------------
bool cScenarioPlayMode::FUN_00f1a7a0(int type, ObjHdr* target)
{
    if (target && ((cScenarioClassRef*)target)->mClassID >= 0)
    {
        for (cScenarioPlayModeGoal* g = mCurrentGoalsBegin; g != mCurrentGoalsEnd; ++g)
        {
            if (!g->mIsCompleted && g->mGoal.mType == type
                && ((cScenarioClassRef*)target)->mClassID == g->mGoal.mTargetID)
                return true;
        }
    }
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x00f1a7f0
// ---------------------------------------------------------------------------
void cScenarioPlayMode::FUN_00f1a7f0(ObjHdr* target)
{
    if (target)
    {
        ObjHdr* comp = (ObjHdr*)target->Query(0x1186577);
        if (comp)
        {
            target->FUN_00b18530();
            int id = *((IClassId*)target)->FUN_006c0200();

            bool matched = false;
            cScenarioPlayModeGoal* g = mCurrentGoalsBegin;
            if (g != mCurrentGoalsEnd)
            {
                do
                {
                    if (matched)
                        break;
                    if (g->mGoal.mTargetID == id)
                    {
                        if (g->mGoal.mType == 7)
                            matched = true;
                        else if (g->mGoal.mType == 8)
                            matched = ((((ICreatureFlags50*)comp)->mFlags >> 8) & 1) == 0;
                    }
                    ++g;
                } while (g != mCurrentGoalsEnd);
            }
            if (matched)
                cScenarioPlayProgressBar_SetAttr(target);
            else
                ((IClassId*)comp)->FUN_00c8ad30(0x7b0f76d, 1);
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x00f1a890
// ---------------------------------------------------------------------------
void cScenarioPlayMode::FUN_00f1a890()
{
    int* vec = (int*)NounManager()->GetItemID();
    int count = (vec[1] - vec[0]) >> 2;
    for (int i = 0; i < count; ++i)
    {
        ObjHdr* item = ((ObjHdr**)vec[0])[i];
        int anim;
        if (mCurrentPlayModeState == 5)
            anim = 0x7ba46b7;
        else if (mCurrentPlayModeState == 6)
            anim = 0x7b66a9b + (field_B0 ? 0x3dc23 : 0);
        else
            anim = FUN_00ebfdc0(item);
        ((ICreatureAnim*)item)->PlayAnimation(anim, 1, -1);
    }
}

// ---------------------------------------------------------------------------
// @ 0x00f1a910
// ---------------------------------------------------------------------------
void __cdecl FUN_00f1a910()
{
    Avatar* avatar = NounManager()->GetAvatar();
    if (avatar)
        ((ICreatureAnim*)((char*)avatar + 0x5a8))->FUN_00bfc470(1);

    void* vecP = NounManager()->GetItemID();
    int* vec = (int*)vecP;
    int count = (vec[1] - vec[0]) >> 2;
    for (int i = 0; i < count; ++i)
    {
        ObjHdr* item = ((ObjHdr**)vec[0])[i];
        if (item)
            ((ICreatureAnim*)((char*)item + 0x5a8))->FUN_00bfc470(1);
    }
}

// ---------------------------------------------------------------------------
// @ 0x00f1a970
// ---------------------------------------------------------------------------
void cScenarioPlayMode::FUN_00f1a970(int b)
{
    (void)b;
    if (sScenarioMode->mPlayType == 1 || sScenarioMode->mPlayType == 2)
    {
        void* dt = (char*)sScenarioMode->mpData->mpResource + 8;
        int local[5];
        local[2] = -1;
        local[3] = 0x7fffffff;
        local[4] = 0x7fffffff;
        if (*(int*)dt)
        {
            FUN_00eed9c0(dt, &local[2]);
            ((IDateTime*)&local[0])->Set(1);
            int v = 0;
            if (local[3] != 0x7fffffff)
                v = local[3];
            local[3] = v + 1;
            local[2] = local[0];
            FUN_00eeda20(dt, &local[2]);
            ((IObjTemplateDB*)ObjectTemplateDB())->FUN_58(dt, 1);
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x00f1aa10
// ---------------------------------------------------------------------------
float __stdcall FUN_00f1aa10(char flag, ObjHdr* obj)
{
    if (obj)
    {
        float a, b;
        if (flag)
        {
            a = g_15ad92c;
            b = g_15ad930;
        }
        else
        {
            a = g_15ad934;
            b = g_15ad938;
        }
        BBox* box = ((ISpatial*)obj)->GetBBoxAt68();
        float dx = box->mMax.x - box->mMin.x;
        float dy = box->mMax.y - box->mMin.y;
        float dz = box->mMax.z - box->mMin.z;
        float dist = sqrtf(dz * dz + (dx * dx + dy * dy));
        float t = __max(dist, g_15ad924);
        t = __min(t, g_15ad928);
        return (t - g_15ad924) / (g_15ad928 - g_15ad924) * (b - a) + a;
    }
    return 0.0f;
}

// ---------------------------------------------------------------------------
// @ 0x00f1aae0
// ---------------------------------------------------------------------------
void cScenarioPlayMode::SetState(int state)
{
    int old = mCurrentPlayModeState;
    if (old == state)
        return;
    if (state == 4 && (old == 6 || old == 5))
        return;
    mCurrentPlayModeState = state;

    switch (state)
    {
    case 4:
        {
            cGameTimeManager* timeManager = GameTimeManager();
            timeManager->IncPauseGate(0x4bf38a7);
            CalloutMessageBox(&g_15ada60, &g_15ada6c);
        }
        return;
    case 5:
        FUN_00f1a910();
        FUN_00f1a970(1);
        {
            Avatar* avatar = NounManager()->GetAvatar();
            if (avatar)
                avatar->SetSprinting(0);
        }
        if (field_F0)
        {
            FUN_00572020(field_F0, 0);
            field_F0 = 0;
            field_F4 = 0;
        }
        if (old == 3)
        {
            cScenarioPanel* panel = sScenarioMode->mpScenarioDisplayStrategy->mpPanel2;
            ScenarioTutorials_CloseWindow();
            panel->FUN_00e154d0(1);
            FUN_00f1a890();
            mStopwatch.Restart();
            mCurrentEndCinematicState = 0;
            int recorderState = GetRecorderState();
            KillSetiEffects(0xd8329acc, recorderState);
        }
        return;
    case 6:
        {
            bool b = (sScenarioMode->mPlayType == 1 || sScenarioMode->mPlayType == 2);
            FUN_00f1a910();
            FUN_00f1a970(0);
            Avatar* avatar = NounManager()->GetAvatar();
            if (avatar)
                avatar->SetSprinting(0);
            if (field_F0)
            {
                FUN_00572020(field_F0, 0);
                field_F0 = 0;
                field_F4 = 0;
            }
            ScenarioTutorials_CloseWindow();
            if (old == 3 || old == 1 || (!b && old == 0))
            {
                FUN_00f1a890();
                mStopwatch.Restart();
                mCurrentEndCinematicState = 0;
                sScenarioMode->mpScenarioDisplayStrategy->mpPanel2->FUN_00e15620();
                if (!field_B0)
                {
                    int recorderState = GetRecorderState();
                    KillSetiEffects(0x789b782e, recorderState);
                }
                else
                {
                    int recorderState = GetRecorderState();
                    KillSetiEffects(0xf7f59104, recorderState);
                }
            }
            else if (old == 4)
            {
                sScenarioMode->mpScenarioDisplayStrategy->mpPanel->FUN_00f18660(this);
                mCurrentEndCinematicState = 2;
            }
        }
        return;
    default:
        return;
    }
}

// ---------------------------------------------------------------------------
// @ 0x00f1ad00
// ---------------------------------------------------------------------------
struct cGoalEntry { uint32_t mFlags; void* mKey; char pad[0x238 - 8]; };

void __cdecl FUN_00f1ad00(int param)
{
    cScenarioResource* res = sScenarioMode->mpData->mpResource;
    cGoalEntry* cur;
    if (res->mGoalEntryIndex < 0x3fffffffu)
        cur = (cGoalEntry*)((char*)res->mGoalEntriesBegin + res->mGoalEntryIndex * 0x238);
    else
        cur = (cGoalEntry*)res->mGoalEntriesEnd;

    if ((void*)cur == res->mGoalEntriesEnd)
        return;

    for (;;)
    {
        void* key = &cur->mKey;
        void* obj = sScenarioMode->mpData->FUN_00f3d780(key);
        if (obj)
        {
            void* holder = sScenarioMode->mpData->FUN_00f3e900(obj);
            if (holder)
            {
                void* comp = ((IGoalObj*)obj)->Query(0x175cdc9);
                bool b9 = comp && ((IGoalObj*)comp)->mState == 9;
                IControlObj* ctl = (IControlObj*)holder;
                bool b10 = *(int*)(param * 0x4e0 + 0x4a4 + ctl->mState74) < 0;
                if (b9)
                {
                    if (b10)
                        NounManager()->RemoveNoun(obj);
                }
                else if (!b10)
                {
                    void* e = FUN_00f238e0(key);
                    *(void**)((char*)e + 0x18) = key;
                    *(int*)((char*)e + 0x1c) = *(int*)key;
                    FUN_00f24190(e, obj);
                }
            }
        }
        for (;;)
        {
            uint32_t flags = cur->mFlags;
            cur = (cGoalEntry*)((char*)cur + 0x238);
            if ((flags >> 30) & 1)
                break;
            if (*(int*)cur >= 0)
                continue;
            break;
        }
        if ((void*)cur == res->mGoalEntriesEnd)
            break;
    }
}
