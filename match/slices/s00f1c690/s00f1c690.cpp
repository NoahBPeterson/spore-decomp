// @ 0x00f1c690  Simulator::cScenarioPlayMode::HandleMessage (slot 1 of the primary vtable 0x0148c2fc;
// the constructor at 0x00f1e450 installs it). Layout and member names from the Spore ModAPI
// cScenarioPlayMode / cScenarioPlaySummary headers, which match every offset used here.
// Every handled message returns false (the message is never consumed).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc: the string16 locals get no EH frame;
// /fp:fast for the fild/fadd [mem] float->uint32 update of mAmountDamageDealt).

#include "types.h"

typedef unsigned int uint;

extern "C" void operator_delete_array(void* p);       // 0x00f47380 (operator delete[])

namespace eastl {

struct allocator { allocator() {} };

// eastl::basic_string<wchar_t, eastl::allocator>
struct string16
{
    wchar_t*  mpBegin;
    wchar_t*  mpEnd;
    wchar_t*  mpCapacity;
    allocator mAllocator;

    string16(const wchar_t* p, const allocator& a = allocator())
    {
        mpBegin = 0;
        mpEnd = 0;
        mpCapacity = 0;
        RangeInitialize(p);
    }
    ~string16() { DeallocateSelf(); }

    uint length() const { return (uint)(mpEnd - mpBegin); }

    void RangeInitialize(const wchar_t* p);             // 0x00579a90
    void DeallocateSelf()
    {
        if ((mpCapacity - mpBegin) > 1 && mpBegin)
            operator_delete_array(mpBegin);
    }
};

// eastl::hashtable iteration (node: value at +4, next at +8)
struct hash_node { uint key; void* mValue; hash_node* mpNext; };
struct hashtable_iterator
{
    hash_node*  mpNode;
    hash_node** mpBucket;

    hashtable_iterator() {}
    hashtable_iterator(const hashtable_iterator& x) : mpNode(x.mpNode), mpBucket(x.mpBucket) {}

    void increment()
    {
        mpNode = mpNode->mpNext;
        while (mpNode == 0)
            mpNode = *++mpBucket;
    }
    hashtable_iterator& operator++() { increment(); return *this; }
};
struct hashtable
{
    uint        mUnused;
    hash_node** mpBucketArray;        // +0x04
    uint        mnBucketCount;        // +0x08

    hashtable_iterator begin();       // 0x00594410
    hash_node* end_node() const { return mpBucketArray[mnBucketCount]; }
};

}  // namespace eastl

// ---------------------------------------------------------------------------
// collaborators
// ---------------------------------------------------------------------------
struct cEffectObject                     // effect instance found through the model's effect table
{
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual bool IsRunning();            // +0x10
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20();
    virtual void v24(); virtual void v28();
    virtual void SetHidden(bool b);      // +0x2c
    virtual void SetPaused(bool b);      // +0x30
};

struct cModelEffect { char pad[0x8c]; cEffectObject* mpEffect; };

struct cModelWorld { char pad[0x17a0]; eastl::hashtable mEffects; };

struct cModelData
{
    char  pad0[0x80];
    float mAlpha;                        // +0x80
    char  pad1[0xf8];
    cModelWorld* mpWorld;                // +0x17c
    uint* mpGroupBits;                   // +0x180 (bitset of 64 groups at +0x44)
};

struct cCreatureData { char pad0[0x5fc]; uint mFlags; };

struct cCreatureBase
{
    char pad0[0xb4c];
    cCreatureData* mpData;               // +0xb4c
    char pad1[4];
    cModelData* mpModel;                 // +0xb54
    uint mFlags;                         // +0xb58

    void Hide();                         // 0x00c0f280
    int  GetPosseCount();                // 0x00c0f4f0
    void* GetPosseMember(int i);         // 0x00c0f8a0
    bool IsCaptain();                    // 0x00c0c0e0
};

struct cGameNounManager { cCreatureBase* GetAvatar(); };   // 0x00b1fdb0
cGameNounManager* NounManager();                           // 0x00b3d300

struct IModelManager
{
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual uint GetGroupIndex(uint id, int flags);          // +0x28
};
IModelManager* ModelManager();                             // 0x0067dd80

struct IRenderer { virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
                   virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
                   virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
                   virtual void v30(); virtual void v34(); virtual void* GetView(); };   // +0x38
struct IApp { virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
              virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
              virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
              virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
              virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
              virtual IRenderer* GetRenderer(); };                                  // +0x50
IApp* App();                                               // 0x0067dd10

struct cCameraController
{
    void SetMinDistance(float f);        // 0x00d25ca0
    void SetMaxDistance(float f);        // 0x00d20910
};
cCameraController* GetCameraController(void* view);       // 0x00b60a50

struct cAchievementsController { void Trigger(uint id, int count); };   // 0x00676e90
cAchievementsController* AchievementsController();        // 0x00675250

struct cGameModeManager { void SetActiveModeByID(uint id); };           // 0x00b1e410
cGameModeManager* GameModeManager();                      // 0x00b3d320

struct cGameTimeManager { void Resume(uint gateID); };                  // 0x00b32250
cGameTimeManager* GameTimeManager();                      // 0x00b3d380

struct cScenarioCinematicState { char pad[0x3c4]; int mResult; };
cScenarioCinematicState* GetCinematicState();             // 0x00b3d4d0

uint GetCurrentGameMode();                                // 0x00b5b800
void ScenarioTutorials_CloseWindow();                     // 0x00efcae0

enum { kGameSpace = 0x01654c05, kScenarioMode = 0x01654c10 };

struct cScenarioDialog                   // 0x44 bytes
{
    int  mType;                          // +0x00
    struct Text { const wchar_t* Get(); } mText;   // +0x04 (0x00f26360)
    char pad[0x38];
    int  mResult;                        // +0x40
};
struct DialogVector                     // eastl::vector<cScenarioDialog>
{
    cScenarioDialog* mpBegin;
    cScenarioDialog* mpEnd;
    cScenarioDialog* mpCapacity;
    uint mAllocator;
    uint size() const { return (uint)(mpEnd - mpBegin); }
    cScenarioDialog& operator[](uint n) { return mpBegin[n]; }
};
struct cScenarioAct { char pad[0x18]; DialogVector mDialogs; };

cScenarioAct* GetScenarioAct(void* resource, int actIndex, uint classID);       // 0x00f264d0
struct cScenarioData
{
    char pad[0x10];
    void* mpResource;
    uint GetActCount();                                                         // 0x00f3be30
    cScenarioAct* GetAct(int actIndex, uint classID) { return GetScenarioAct(mpResource, actIndex, classID); }
};

struct ICastObject { virtual void v00(); virtual void v04(); virtual void v08(); char pad[0x18];
                     uint mClassID; };   // +0x1c
struct cScenarioClassRef                 // field_CC
{
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual void* Cast(uint typeID);     // +0x0c
    char pad[0x18];
    uint mClassID;                       // +0x1c
};

struct cScenarioDisplay { char pad[0x12c]; struct Panel { void Close(void* playMode); }* mpPanel;   // 0x00f18660
                          void ShowUI(bool b); };                                                 // 0x00f0e4a0

struct cScenarioMode
{
    char pad0[0x6c];
    cScenarioDisplay* mpScenarioDisplayStrategy;   // +0x6c
    char pad1[4];
    cScenarioData* mpData;                         // +0x74
    char pad2[0x58];
    int  mPlayType;                                // +0xd0 (0 = editor test, 1 = ..., 2 = real play)

    void OnEditorTestFinished();                   // 0x00ef1360
    void OnFinished1();                            // 0x00ef00b0
    void OnRestart();                              // 0x00ef1400
};
extern cScenarioMode* sScenarioMode;               // 0x016c7aa4

struct cCombatant
{
    virtual void v00(); virtual void v04();
    virtual cCreatureBase* GetOwner(int i);        // +0x08
    virtual ICastObject* GetCastInfo();            // +0x0c
    int GetDamageState();                          // 0x008e7f80
};

struct cGameObjectEffect { virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
                           virtual void Stop(int flags); };   // +0x10
struct cScenarioPosseItem { virtual void v00(); char pad[0x5c]; };
struct cPosseMemberA { void** vtbl; };
struct cPosseMemberB { char pad[0x14]; cGameObjectEffect* mpEffect; };

struct IPosseHolder { virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
                      virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
                      virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
                      virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
                      virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
                      virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
                      virtual void Dismiss(int flags); };   // +0x60
IPosseHolder*  GetPosseHolder(void* member);       // 0x00d2ec10
cPosseMemberB* GetPosseEffectHolder(void* member); // 0x00ae66d0

struct cBarrel { char pad[0x38]; int mType; };
cBarrel* AsBarrel(cCombatant* c);                  // 0x00ec0250
cCreatureBase* AsCreature(void* c);                // 0x00ae33b0
void* AsVehicle(cCombatant* c);                    // 0x00ae3350
void* AsBuilding(cCombatant* c);                   // 0x00f191e0
cCreatureBase* GetClassCreature(cScenarioClassRef* ref);   // 0x00f19200

struct cBoundingBox { char pad[8]; float mMinZ; char pad1[8]; float mMaxZ; };
struct IBoundedObject { virtual void v00(); char pad[0x64]; };
struct cScenarioModel
{
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38();
    virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c(); virtual void v60();
    virtual void v64();
    virtual cBoundingBox* GetBoundingBox();        // +0x68
};
cScenarioModel* GetClassModel(cScenarioClassRef* ref);   // 0x00b18e00

extern const float kIntroFadeinTime;     // 0x015ad948
extern const float kSmallSizeLimit;      // 0x015ad958
extern const float kMediumSizeLimit;     // 0x015ad95c

struct cScenarioGoal { int mType; uint mTargetID; };

struct cScenarioPlayModeGoal             // 0x1ac bytes
{
    bool mIsCompleted;                   // +0x00
    bool field_1;
    int  mCount;                         // +0x04
    char field_8[0x1c];                  // +0x08 eastl::map<uint32_t, int>
    cScenarioGoal mGoal;                 // +0x24 (type at +0x24, target at +0x28)
    char pad[0x1ac - 0x2c];
};

struct cScenarioPlaySummary
{
    int   mNumCreaturesKilled;           // +0x00
    int   mNumBuildingsDestroyed;        // +0x04
    int   mNumVehiclesDestroyed;         // +0x08
    int   mNumCastMembersDefended;       // +0x0c
    int   mNumCreaturesBefriended;       // +0x10
    int   mNumObjectsCollected;          // +0x14
    int   field_18;
    int   mNumGoalsCompleted;            // +0x1c
    int   mNumDeaths;                    // +0x20
    int   mNumPosseMembersLost;          // +0x24
    uint  mAmountDamageDealt;            // +0x28
    int   mNumTimesUsedJetPack;          // +0x2c
    int   mNumTimesUsedSprint;           // +0x30
    int   mNumBarrelsDestroyed;          // +0x34
    int   mNumCastMembersTalkedTo;       // +0x38
    float mAmountHealthRegained;         // +0x3c
    float mAmountDamageReceived;         // +0x40
    float mAmountEnergyUsed;             // +0x44
};

struct Message { char pad[8]; union { int mValue; float mAmount; cCombatant* mpVictim; }; int pad1;
                 cCombatant* mpAttacker; };

namespace Simulator {

class cScenarioPlayMode
{
public:
    virtual ~cScenarioPlayMode();
    virtual bool HandleMessage(uint messageID, void* msg);

    void UpdateGoalStatus();                                         // 0x00f1c4b0
    void StartAdventure();                                           // 0x00f198d0
    void OnTimerMessage();                                           // 0x00f1c2f0
    void CompleteGoal(cScenarioPlayModeGoal* goal, cCreatureBase* by);   // 0x00f1ae10
    void SetState(int state);                                        // 0x00f1aae0

    /* 04h */ void* mpRefVtbl;
    /* 08h */ int   mnRefCount;
    /* 0Ch */ cScenarioPlaySummary mSummary;
    /* 54h */ char  mFailReason[0x10];
    /* 64h */ cScenarioPlayModeGoal* mCurrentGoalsBegin;
    /* 68h */ cScenarioPlayModeGoal* mCurrentGoalsEnd;
    /* 6Ch */ char  pad6c[0x24];
    /* 90h */ int   mCurrentPlayModeState;
    /* 94h */ int   mCurrentEndCinematicState;
    /* 98h */ char  pad98[0x20];
    /* B8h */ int   mCurrentActIndex;
    /* BCh */ char  padbc[0x10];
    /* CCh */ cScenarioClassRef* field_CC;
    /* D0h */ int   field_D0;
    /* D4h */ int   mCurrentDialogBoxIndex;
    /* D8h */ int   field_D8;
    /* DCh */ char  paddc[0x1c];
    /* F8h */ float mIntroFadeinTimer;
    /* FCh */ bool  mIsIntroFadeinActive;
};

// Sets or clears the avatar model's group bit for group id 0x06669387.
static inline bool Bit(uint v, uint n) { return (v >> n) & 1; }

static inline uint* GroupWord(cModelData* model, uint idx) { return &model->mpGroupBits[(idx >> 5) + 0x11]; }

// dialogs of the current act for the cast member in field_CC
static __forceinline DialogVector& CurrentDialogs(cScenarioPlayMode* p)
{
    return sScenarioMode->mpData->GetAct(p->mCurrentActIndex, p->field_CC->mClassID)->mDialogs;
}

// ---------------------------------------------------------------------------
// @ 0x00f1c690
// ---------------------------------------------------------------------------
bool cScenarioPlayMode::HandleMessage(uint messageID, void* pMsg)
{
    Message* msg = (Message*)pMsg;

    switch (messageID)
    {
    case 0x044f1189:
        if (GetCurrentGameMode() != kScenarioMode)
            break;
        if (mCurrentPlayModeState == 1)
        {
            cCreatureBase* avatar = NounManager()->GetAvatar();
            if (avatar)
            {
                avatar->mpModel->mAlpha = 1.0f;
                avatar->mFlags &= ~0x800;
                IModelManager* mm = ModelManager();
                cModelData* model = avatar->mpModel;
                uint idx = mm->GetGroupIndex(0x06669387, 0);
                if (idx < 0x40)
                    *GroupWord(model, idx) &= ~(1 << (idx & 0x1f));
                mIsIntroFadeinActive = false;
                mIntroFadeinTimer = 0.0f;

                eastl::hashtable& effects = avatar->mpModel->mpWorld->mEffects;
                eastl::hashtable_iterator it = effects.begin();
                eastl::hash_node* end = effects.end_node();
                for (; it.mpNode != end; ++it)
                {
                    cEffectObject* effect = ((cModelEffect*)it.mpNode->mValue)->mpEffect;
                    if (effect && effect->IsRunning())
                    {
                        effect->SetHidden(false);
                        effect->SetPaused(false);
                    }
                }
            }
            UpdateGoalStatus();
            if (mCurrentPlayModeState == 1)
            {
                mCurrentPlayModeState = 3;
                StartAdventure();
            }
            cCameraController* camera = GetCameraController(App()->GetRenderer()->GetView());
            if (camera)
            {
                camera->SetMinDistance(12.0f);
                camera->SetMaxDistance(20.0f);
            }
        }
        else if (mCurrentPlayModeState == 5 || mCurrentPlayModeState == 6)
        {
            sScenarioMode->mpScenarioDisplayStrategy->ShowUI(true);
            ScenarioTutorials_CloseWindow();
            sScenarioMode->mpScenarioDisplayStrategy->mpPanel->Close(this);
            mCurrentEndCinematicState = 2;
        }
        else if (msg->mValue == field_D8)
        {
            OnTimerMessage();
        }
        break;

    case 0x01622184:   // a combatant took damage
    {
        cCombatant* victim = msg->mpVictim;
        cCombatant* attacker = msg->mpAttacker;
        if (victim->GetDamageState() != 2)
            break;
        uint castID = victim->GetCastInfo()->mClassID;
        if (castID != 0xffffffff)
        {
            cScenarioPlayModeGoal* goal = mCurrentGoalsBegin;
            cScenarioPlayModeGoal* end = mCurrentGoalsEnd;
            for (; goal != end; ++goal)
            {
                if (!goal->mIsCompleted && goal->mGoal.mType == 3 && goal->mGoal.mTargetID == castID)
                    CompleteGoal(goal, victim->GetOwner(0));
            }
        }
        if (mCurrentPlayModeState == 3)
            UpdateGoalStatus();

        cBarrel* barrel = AsBarrel(victim);
        if (barrel && barrel->mType == 0xf)
            mSummary.mNumBarrelsDestroyed += 1;
        cCreatureBase* creature = AsCreature(victim);
        if (creature)
        {
            if (Bit(creature->mFlags, 9))
                mSummary.mNumDeaths += 1;
            if (Bit(creature->mFlags, 8))
                mSummary.mNumPosseMembersLost += 1;
        }

        cCreatureBase* by = AsCreature(attacker);
        if (by == 0 || !Bit(by->mFlags, 9))
            break;

        cCreatureBase* killed = AsCreature(victim);
        void* vehicle = AsVehicle(victim);
        void* building = AsBuilding(victim);
        if (killed)
        {
            if (sScenarioMode->mPlayType == 2)
            {
                AchievementsController()->Trigger(0x34c7c0af, 1);
                if (killed->IsCaptain())
                    AchievementsController()->Trigger(0xcba1a092, 1);
            }
            mSummary.mNumCreaturesKilled += 1;
        }
        else if (vehicle)
        {
            if (sScenarioMode->mPlayType == 2)
                AchievementsController()->Trigger(0x452ef89c, 1);
            mSummary.mNumVehiclesDestroyed += 1;
        }
        else if (building)
        {
            if (sScenarioMode->mPlayType == 2)
                AchievementsController()->Trigger(0x2f8fab8f, 1);
            mSummary.mNumBuildingsDestroyed += 1;
        }
        break;
    }

    case 0x070b18c7:
        if (msg->mValue == 2)
            sScenarioMode->OnRestart();
        else if (msg->mValue == 1)
        {
            switch (sScenarioMode->mPlayType)
            {
            case 0:
                sScenarioMode->OnEditorTestFinished();
                break;
            case 1:
                sScenarioMode->OnFinished1();
                break;
            case 2:
                GameModeManager()->SetActiveModeByID(kGameSpace);
                break;
            }
        }
        break;

    case 0x0750d732:   // any dialog left after the current one?
        if (GetCurrentGameMode() == kScenarioMode)
        {
            DialogVector& dialogs = CurrentDialogs(this);
            int idx = mCurrentDialogBoxIndex;
            int count = (int)dialogs.size();
            int result = idx >= count - 1;
            if (!result)
            {
                for (++idx; idx < count; ++idx)
                {
                    eastl::string16 text(dialogs[idx].mText.Get());
                    if (text.length() > 0)
                        goto done750;
                }
                result = 1;
            }
        done750:
            GetCinematicState()->mResult = result;
        }
        break;

    case 0x0754ae8a:   // advance to the next dialog box
        if (GetCurrentGameMode() == kScenarioMode)
        {
            ++mCurrentDialogBoxIndex;
            DialogVector& dialogs = CurrentDialogs(this);
            int idx = mCurrentDialogBoxIndex;
            int result;
            if (idx < (int)dialogs.size())
            {
                eastl::string16 text(dialogs[idx].mText.Get());
                if (text.length() == 0)
                    result = 4;
                else
                {
                    switch (dialogs[mCurrentDialogBoxIndex].mType)
                    {
                    case 0:  result = 0; break;
                    case 1:  result = 1; break;
                    case 2:  result = 2; break;
                    default: result = 3; break;
                    }
                }
            }
            else
                result = 4;
            GetCinematicState()->mResult = result;
        }
        break;

    case 0x078eab55:   // start the captain fade-in
    {
        cCreatureBase* avatar = NounManager()->GetAvatar();
        if (avatar)
        {
            avatar->mpModel->mAlpha = 0.0f;
            IModelManager* mm = ModelManager();
            cModelData* model = avatar->mpModel;
            uint idx = mm->GetGroupIndex(0x06669387, 0);
            if (idx < 0x40)
                *GroupWord(model, idx) |= 1 << (idx & 0x1f);
            mIntroFadeinTimer = kIntroFadeinTime;
            mIsIntroFadeinActive = true;
        }
        break;
    }

    case 0x07688cad:
        if (GetCurrentGameMode() == kScenarioMode)
        {
            int result = 0;
            cCreatureBase* creature = GetClassCreature(field_CC);
            if (creature)
            {
                if (creature->IsCaptain())
                    result = 2;
                else
                    result = ~(creature->mpData->mFlags >> 9) & 1;
            }
            GetCinematicState()->mResult = result;
        }
        break;

    case 0x07aaa58c:   // dialog finished?
        if (GetCurrentGameMode() == kScenarioMode)
        {
            int result = 0;
            DialogVector& dialogs = CurrentDialogs(this);
            if (mCurrentDialogBoxIndex >= (int)dialogs.size())
                result = 1;
            GetCinematicState()->mResult = result;
        }
        break;

    case 0x07b509fe:   // hide the avatar and its posse
    {
        cCreatureBase* avatar = NounManager()->GetAvatar();
        if (avatar == 0)
            break;
        avatar->Hide();
        int i = 0;
        int count = avatar->GetPosseCount();
        for (; i < count; ++i)
        {
            void* member = avatar->GetPosseMember(i);
            if (member == 0)
                continue;
            IPosseHolder* holder = GetPosseHolder(member);
            if (holder)
                holder->Dismiss(0);
            else
            {
                cPosseMemberB* b = GetPosseEffectHolder(member);
                if (b && b->mpEffect)
                    b->mpEffect->Stop(0);
            }
        }
        eastl::hashtable& effects = avatar->mpModel->mpWorld->mEffects;
        eastl::hashtable_iterator it = effects.begin();
        eastl::hash_node* end = effects.end_node();
        for (; it.mpNode != end; it.increment())
        {
            cEffectObject* effect = ((cModelEffect*)it.mpNode->mValue)->mpEffect;
            if (effect && effect->IsRunning())
            {
                effect->SetHidden(true);
                effect->SetPaused(true);
            }
        }
        break;
    }

    case 0x07c63e20:
        mSummary.mAmountDamageDealt = (uint)((float)mSummary.mAmountDamageDealt + msg->mAmount);
        break;

    case 0x07c66a67:
        mSummary.mNumTimesUsedJetPack += 1;
        break;

    case 0x07c6551e:
        mSummary.mAmountDamageReceived += msg->mAmount;
        break;

    case 0x07c772b7:
        mSummary.mNumTimesUsedSprint += 1;
        break;

    case 0x07c789f8:
        mSummary.mAmountHealthRegained += msg->mAmount;
        break;

    case 0x07c7945f:
        if (GetCurrentGameMode() == kScenarioMode)
        {
            int result = 0;
            if (field_CC && field_CC->Cast(0xce9f6639))
                result = CurrentDialogs(this)[mCurrentDialogBoxIndex].mResult;
            GetCinematicState()->mResult = result;
        }
        break;

    case 0x07c7a52e:
        mSummary.mAmountEnergyUsed += msg->mAmount;
        break;

    case 0x07d0c530:   // size class of the cast member
        if (GetCurrentGameMode() == kScenarioMode)
        {
            cBoundingBox* box = GetClassModel(field_CC)->GetBoundingBox();
            float height = box->mMaxZ - box->mMinZ;
            int result = 2;
            if (kSmallSizeLimit > height)
                result = 0;
            else if (kMediumSizeLimit > height)
                result = 1;
            GetCinematicState()->mResult = result;
        }
        break;

    case 0x07da0410:   // result of the first non-empty dialog box
        if (GetCurrentGameMode() == kScenarioMode)
        {
            int result = 0;
            DialogVector& dialogs = CurrentDialogs(this);
            uint count = dialogs.size();
            for (uint i = 0; i < count; ++i)
            {
                eastl::string16 text(dialogs[i].mText.Get());
                if (text.length() > 0)
                {
                    result = dialogs[i].mResult;
                    break;
                }
            }
            GetCinematicState()->mResult = result;
        }
        break;

    case 0xc2edd1e8:   // end-of-act cinematic finished
        GameTimeManager()->Resume(0x04bf38a7);
        if (msg->mValue == 0x05107b1a)
        {
            if (mCurrentActIndex == (int)sScenarioMode->mpData->GetActCount() - 1 &&
                mCurrentGoalsBegin == mCurrentGoalsEnd)
            {
                mCurrentPlayModeState = 3;
                SetState(5);
            }
            else
                SetState(6);
        }
        else if (msg->mValue == 0x05107b17 && mCurrentPlayModeState != 3)
            mCurrentPlayModeState = 3;
        break;
    }
    return false;
}

}  // namespace Simulator
