// Slice s00d48010: `anonymous namespace'::cCreatureCollectableItemsScenario::EvaluateEvent (0x00d48010).
// Flags: /O2 /MD /Gy /TP /arch:SSE (no EH frame).
//
//   bool __thiscall EvaluateEvent(uint32_t eventID, ScenarioEvent* ev)   (ret 8)
//
// Creature-game scenario that hands out collectable items (parts) for creature events. ev->actor must be
// the avatar (except for 0xd335362c, which any actor may raise). By event id:
//   0x5371f11   one search (with ev->value) and notify every unlocked item
//   0x49b56d7   repeated searches over the avatar's slots (count from vtable slot 0x36), notify each hit
//   0x61b1320   report a "mood" code 6/3/5 to the item tracker (depends on the terrain sphere kind, then on the
//               two unsigned counters at actor->0xb20->0x608/0x60c)
//   0xd3353635  add ev->value to the tracker's running total
//   0x60b4123, 0xd335362c, 0xd335363a
//               "other creature" interaction: the other creature (ev->other cast to type 0x18eb45e) is
//               eligible only if it is not busy, is not in the actor's group, and (for 0xd335362c when the
//               game mode is not 0x01654c05) a timer / posse test passes; a random roll against two
//               tuning thresholds then decides whether a search is run and its hits notified.
#include "types.h"

void operator delete[](void* p);   // 0x00f47380

// fixed buffer vector of (id, count) pairs: begin, end, capacity end, buffer, then 8 inline slots
struct ItemPair { uint32_t a, b; };
struct ItemVector
{
    ItemPair* mpBegin;
    ItemPair* mpEnd;
    ItemPair* mpCapacity;
    ItemPair* mpBuffer;
    ItemPair mBuffer[8];
    ItemVector() : mpBegin(mBuffer), mpEnd(mBuffer), mpCapacity(mBuffer + 8), mpBuffer(mBuffer) {}
};

class cItemTracker   // object at terrain sphere +0x10e8
{
public:
    int  GetNumSlots(int arg);          // 0x00593a10 (ret 4)
    void AddTotal(int n);               // 0x005939b0 (ret 4)
};

class cTerrainSphere
{
public:
    uint32_t pad00[0x10e8 / 4];
    cItemTracker* mpTracker;            // +0x10e8
    uint32_t pad10ec[(0x10fc - 0x10ec) / 4];
    uint32_t mKind;                     // +0x10fc
};

class cSporeCreature;
struct CreatureCounters { char pad[0x608]; uint32_t count0; uint32_t count1; };   // at creature +0xb20
struct CreatureBrain { char pad[0x17c]; int mState; };                                // at creature +0xb54

class cTimerRef   // SP::cSPTimer at creature +0xfe0
{
public:
    uint32_t pad00[6];
    char mRunning;                      // +0x18
    bool IsRunning();                   // 0x00feba90
    uint64_t GetElapsedTime();          // 0x00bc3190
};

class cSporeCreature
{
public:
    uint32_t pad00[0xb20 / 4];
    CreatureCounters* mpCounters;       // +0xb20
    uint32_t padb24;
    char mPadStats[0x2c];               // +0xb28 (passed by address)
    uint32_t padb54[1];
    CreatureBrain* mpBrain;             // +0xb54
    uint32_t mFlags;                    // +0xb58
    char padb5c[0xfe0 - 0xb5c];
    cTimerRef mTimer;                   // +0xfe0
    // at +0xc0: sub-object with virtual slot 0x58 (IsInPosse)
    void* GetTargetKey();               // 0x00c0bc00 (returns a pointer to the key to search for)
    bool IsFollower();                  // 0x00c0b770
    struct TuningData* GetTuning();     // 0x00c0c1a0
};
struct TuningData { char pad[0x32c]; int mItemSlot; };

class cNounManager
{
public:
    cSporeCreature* GetAvatar();                     // 0x00b1fdb0
    cTerrainSphere* GetCurrentTerrainSphere();       // 0x00f67d90
};
cNounManager* NounManager();                         // 0x00b3d300
int GetCurrentGameMode();                            // 0x00b5b800
void* CastGameObject(void* obj, uint32_t typeID);   // 0x00ac80d0 (cdecl)

class cGlobalMood   // returned by 0x00b3d4c0
{
public:
    int Query(void* subject, int a, int b);          // 0x00ba3f90 (ret 0xc)
};
cGlobalMood* GetGlobalMood();                        // 0x00b3d4c0

struct RandomLinearCongruential
{
    double RandomDoubleUniform();   // 0x009360d0
};
extern RandomLinearCongruential sMathRandom;         // 0x01601760

extern const float kSearchRadius0;                   // 0x01582f68
extern const float kSearchRadius1;                   // 0x01582f6c
extern const float kSlotRadius0;                     // 0x01582f70
extern const float kSlotRadius1;                     // 0x01582f74
extern const float kChanceNear;                      // 0x01582f78
extern const float kChanceFar;                       // 0x01582f7c
extern const float kMsToSec;                        // 0x013f9428 (0.001f)
extern const float kTimerLimit;                      // 0x01582f84

struct ScenarioEvent
{
    cSporeCreature* actor;              // +0
    cSporeCreature* other;              // +4
    int value;                          // +8
};

class cCreatureCollectableItemsScenario
{
public:
    bool EvaluateEvent(uint32_t eventID, ScenarioEvent* ev);                                       // 0x00d48010

    bool FindItems(cItemTracker* t, void* key, float r0, float r1, ItemVector* out, int a, int b);   // 0x00d47ea0 (ret 0x1c)
    void NotifyUnlockedItem(uint32_t a, uint32_t b, cSporeCreature* who, cItemTracker* t, bool first); // 0x00d3d4f0 (ret 0x14)
    void Finish();                                                                                  // 0x00d40930
    void ReportMood(cItemTracker* t, int code);                                                     // 0x00d3b690 (ret 8)
};

static inline void FreeVector(ItemVector& v)
{
    if (v.mpBegin != 0 && v.mpBegin != v.mpBuffer)
        operator delete[](v.mpBegin);
}

// @ 0x00d48010
bool cCreatureCollectableItemsScenario::EvaluateEvent(uint32_t eventID, ScenarioEvent* ev)
{
    if (ev->actor == 0)
        return false;
    if (ev->actor != NounManager()->GetAvatar() && eventID != 0xd335362c)
        return false;

    switch (eventID)
    {
    case 0x5371f11:
    {
        cTerrainSphere* sphere = NounManager()->GetCurrentTerrainSphere();
        cSporeCreature* avatar = NounManager()->GetAvatar();
        if (sphere == 0 || sphere->mpTracker == 0 || avatar == 0)
            return true;
        int value = ev->value;
        ItemVector vec;
        if (FindItems(sphere->mpTracker, avatar->GetTargetKey(), kSearchRadius0, kSearchRadius1, &vec, value, -1))
        {
            bool first = true;
            for (ItemPair* p = vec.mpBegin; p != vec.mpEnd; ++p)
            {
                NotifyUnlockedItem(p->a, p->b, ev->actor, sphere->mpTracker, first);
                first = false;
            }
        }
        Finish();
        FreeVector(vec);
        return true;
    }

    case 0x49b56d7:
    {
        cTerrainSphere* sphere = NounManager()->GetCurrentTerrainSphere();
        cSporeCreature* avatar = NounManager()->GetAvatar();
        if (sphere != 0 && sphere->mpTracker != 0 && avatar != 0)
        {
            int slot = ((int (__thiscall*)(void*))(*(void***)avatar)[0xd8 / 4])(avatar);
            int n = sphere->mpTracker->GetNumSlots(slot);
            int i = 0;
            if (n > 0)
            {
                do
                {
                    cItemTracker* t = sphere->mpTracker;
                    ItemVector vec;
                    if (FindItems(t, avatar->GetTargetKey(), kSlotRadius0, kSlotRadius1, &vec, -1, n - i))
                    {
                        bool first = true;
                        for (ItemPair* p = vec.mpBegin; p != vec.mpEnd; ++p)
                        {
                            ++i;
                            NotifyUnlockedItem(p->a, p->b, ev->actor, sphere->mpTracker, first);
                            first = false;
                        }
                    }
                    else
                        ++i;
                    FreeVector(vec);
                } while (i < n);
            }
            Finish();
        }
        return true;
    }

    case 0x61b1320:
    {
        cTerrainSphere* sphere = NounManager()->GetCurrentTerrainSphere();
        NounManager()->GetAvatar();
        if (sphere != 0 && sphere->mpTracker != 0 && ev->actor != 0)
        {
            cItemTracker* t = sphere->mpTracker;
            uint32_t kind = sphere->mKind;
            int code;
            if (kind == 0xa8ec6f99)
                code = 6;
            else if (kind == 0xcfb01b93)
                code = 3;
            else if (kind == 0x5ece4770)
                code = 5;
            else
            {
                CreatureCounters* c = ev->actor->mpCounters;
                float a = (float)c->count0;
                code = 6;
                if (a > 0.0f)
                {
                    float b = (float)c->count1;
                    if (b > 0.0f)
                        code = 5;
                    else
                        code = 3;
                }
            }
            ReportMood(t, code);
        }
        return true;
    }

    case 0xd3353635:
    {
        cTerrainSphere* sphere = NounManager()->GetCurrentTerrainSphere();
        if (sphere != 0 && sphere->mpTracker != 0)
            sphere->mpTracker->AddTotal(ev->value);
        return true;
    }

    case 0x60b4123:
    case 0xd335362c:
    case 0xd335363a:
    {
        cTerrainSphere* sphere = NounManager()->GetCurrentTerrainSphere();
        cSporeCreature* avatar = NounManager()->GetAvatar();
        if (sphere == 0 || sphere->mpTracker == 0 || avatar == 0 || ev->actor == 0)
            return true;

        bool eligible = true;
        int a = -1;
        uint32_t b = 1;
        if (GetCurrentGameMode() == 0x1654c05)
            eligible = false;

        cSporeCreature* target = 0;
        bool skipSearch = false;
        if (ev->other != 0)
        {
            target = (cSporeCreature*)CastGameObject(ev->other, 0x18eb45e);
            if (target != 0)
            {
                if (eventID == 0xd335362c && eligible)
                {
                    void* stats = (char*)ev->actor + 0xc0;
                    bool inPosse = ((bool (__thiscall*)(void*))(*(void***)stats)[0x58 / 4])(stats);
                    if (inPosse)
                        eligible = true;
                    else
                    {
                        int mood = GetGlobalMood()->Query((char*)ev->actor + 0xb28, 0, 0);
                        bool recent = false;
                        if (mood == 6 && target->mTimer.IsRunning())
                        {
                            double ms = (double)target->mTimer.GetElapsedTime();
                            if (ms * kMsToSec < kTimerLimit)
                                recent = true;
                        }
                        eligible = recent;
                    }
                }
                // eligibility gates on the other creature
                if (target->mpBrain == 0 || target->mpBrain->mState == 0 || (target->mFlags & 2) != 0 ||
                    avatar->mpCounters == target->mpCounters || !target->IsFollower() || !eligible)
                    return true;
                a = target->GetTuning()->mItemSlot;
                if (a != -1)
                    b = 0xffffffff;
                float roll = (float)sMathRandom.RandomDoubleUniform();
                float limit = (target->mFlags & 1) ? kChanceNear : kChanceFar;
                if (!(limit >= roll))
                    return true;
            }
            else if (!eligible)
                return true;
        }
        else if (!eligible)
            return true;

        cItemTracker* t = sphere->mpTracker;
        ItemVector vec;
        if (FindItems(t, avatar->GetTargetKey(), kSearchRadius0, kSearchRadius1, &vec, a, b))
        {
            bool first = true;
            for (ItemPair* p = vec.mpBegin; p != vec.mpEnd; ++p)
            {
                cSporeCreature* who = ev->other;
                if (who == 0)
                    who = avatar;
                NotifyUnlockedItem(p->a, p->b, who, sphere->mpTracker, first);
                first = false;
            }
            if (target != 0)
                target->mFlags |= 2;
        }
        Finish();
        FreeVector(vec);
        return true;
    }

    default:
        return false;
    }
}

// ---------------------------------------------------------------------------
// Simulator creature-GUI button table (global at 0x0169e3ec)
//   five categories of five {id, flag} entries, followed by the two category
//   base ids (0xd0/0xd4) and the id count shared by every range (0xcc).
// ---------------------------------------------------------------------------
struct ButtonEntry
{
    int32_t mID;          // +0x00 (-1 = unused slot)
    uint8_t mFlag;        // +0x04
    uint8_t pad05[3];     // +0x05
};

struct ButtonCategory
{
    ButtonEntry mEntries[5];   // +0x00 .. +0x27
};

struct ButtonTable
{
    union
    {
        ButtonEntry mAllEntries[0x19];    // +0x000 (flat view used by the filler loop)
        ButtonCategory mCategories[5];    // +0x000 (category view used by the lookups)
    };
    uint32_t mFieldC8;                    // +0x0c8
    uint32_t mCategoryCount;              // +0x0cc (ids per category range)
    uint32_t mBase0;                      // +0x0d0 (first id of categories 0/1)
    uint32_t mBase1;                      // +0x0d4 (first id of categories 3/4)
};

extern ButtonTable* gButtonTable;         // 0x0169e3ec

void operator delete(void* p);                                    // 0x00f47380
void* operator new(uint32_t size, const char* name, int, int, int, int);   // 0x00f473a0

// ---------------------------------------------------------------------------
// Wide string (EASTL basic_string<wchar_t>)
// ---------------------------------------------------------------------------
struct WString
{
    wchar_t* mpBegin;        // +0
    wchar_t* mpEnd;          // +4
    wchar_t* mpCapacity;     // +8

    WString& assign(const wchar_t* s);                            // 0x005c3d90 (ret 4)
    WString& Assign(const wchar_t* first, const wchar_t* last);   // 0x00423650 (ret 8)
};

class cSpeciesProfile
{
public:
    void GetUiName(WString* out);            // 0x004da330 (ret 4)
};

class cCivTokenTranslator
{
public:
    cCivTokenTranslator();                                           // 0x00b32470
    virtual bool TranslateToken(const wchar_t* token, WString* out); // 0x00b324f0 (ret 8)
    uint32_t pad04[2];                                               // +0x04 .. +0x0b
};

class cCreatureTokenTranslator : public cCivTokenTranslator
{
public:
    cCreatureTokenTranslator();                                      // 0x00d486f0

    uint32_t mValueC;                // +0x0c
    uint32_t mValue10;               // +0x10
    uint32_t mValue14;               // +0x14
    uint32_t mValue18;               // +0x18
    cSpeciesProfile* mpProfile;      // +0x1c
    int32_t mValue20;                // +0x20
    int32_t mValue24;                // +0x24
    const wchar_t* mpText;           // +0x28 (null = no token)
    float mValue2c;                  // +0x2c

    bool TranslateToken(const wchar_t* token, WString* out);         // 0x00d48750
};

extern const wchar_t kTokenError[];      // 0x0147ae78 L"*TOKEN ERROR*"
extern const wchar_t kTokenNumberSep[];  // 0x013ec468 number prefix text

uint32_t __cdecl FNV1_String16(const wchar_t* s, uint32_t seed, int fold);   // 0x00932f30
void __cdecl SetNumberString(int64_t value, wchar_t* buf, int cch);          // 0x00881ae0
void __cdecl FormatNumberDouble(double value, wchar_t* buf, int cch, int flags); // 0x00881ea0

static inline void AssignWideLiteral(WString* out, const wchar_t* s)
{
    const wchar_t* end = s;
    while (*end != 0)
        ++end;
    out->Assign(s, end);
}

// @ 0x00d486f0
cCreatureTokenTranslator::cCreatureTokenTranslator()
    : mValueC(0), mValue10(0), mValue14(0), mpProfile(0), mValue20(0), mpText(0), mValue2c(0.0f)
{
}

// @ 0x00d48750
bool cCreatureTokenTranslator::TranslateToken(const wchar_t* token, WString* out)
{
    wchar_t buf[64];
    switch (FNV1_String16(token, 0x811c9dc5, 1))
    {
    case 0x7142102a:                        // species profile name
        AssignWideLiteral(out, kTokenError);
        if (mpProfile == 0)
            return true;
        mpProfile->GetUiName(out);
        return true;

    case 0x4276d4e:                         // signed count
        out->assign(kTokenError);
        SetNumberString((int64_t)mValue20, buf, 0x40);
        buf[0x3f] = 0;
        out->assign(buf);
        return true;

    case 0x171f9d3:                         // unsigned count
        out->assign(kTokenError);
        SetNumberString((int64_t)(uint32_t)mValue18, buf, 0x40);
        buf[0x3f] = 0;
        out->assign(buf);
        return true;

    case 0x5edec022:                        // unsigned count
        out->assign(kTokenError);
        SetNumberString((int64_t)(uint32_t)mValueC, buf, 0x40);
        buf[0x3f] = 0;
        out->assign(buf);
        return true;

    case 0x801ac859:                        // unsigned count
        out->assign(kTokenNumberSep);
        SetNumberString((int64_t)mValue24, buf, 0x40);
        buf[0x3f] = 0;
        out->assign(buf);
        return true;

    case 0xe976268a:                        // float value
        out->assign(kTokenNumberSep);
        FormatNumberDouble((double)mValue2c, buf, 0x40, 0);
        buf[0x3f] = 0;
        out->assign(buf);
        return true;

    case 0x548c1df2:                        // unsigned count
        out->assign(kTokenError);
        SetNumberString((int64_t)(uint32_t)mValue10, buf, 0x40);
        buf[0x3f] = 0;
        out->assign(buf);
        return true;

    case 0xe37cf60f:                        // unsigned count
        out->assign(kTokenError);
        SetNumberString((int64_t)(uint32_t)mValue14, buf, 0x40);
        buf[0x3f] = 0;
        out->assign(buf);
        return true;

    case 0x485fc991:                        // literal text
    case 0xdb8f7823:
    case 0xd004e927:
        if (mpText == 0)
            return true;
        out->assign(mpText);
        return true;

    default:
        return cCivTokenTranslator::TranslateToken(token, out);
    }
}

// @ 0x00d48a00
void InitButtonTable()
{
    gButtonTable = (ButtonTable*)operator new(0xd8, "Simulator", 0, 0, 0, 0);
    switch (GetCurrentGameMode())
    {
    case 0x1654c01:                         // creature editor / creature game
    case 0x1654c10:
        gButtonTable->mFieldC8 = 5;
        gButtonTable->mCategoryCount = 5;
        gButtonTable->mBase0 = 0x1012010;
        gButtonTable->mBase1 = 0x1012020;
        break;

    case 0x1654c02:                         // tribe/civ stage
        gButtonTable->mFieldC8 = 5;
        gButtonTable->mCategoryCount = 3;
        gButtonTable->mBase0 = 0x1012060;
        gButtonTable->mBase1 = 0x1012050;
        break;
    }
    ButtonTable* t = gButtonTable;
    for (int i = 0; i < 0x19; ++i)
    {
        t->mAllEntries[i].mID = -1;
        t->mAllEntries[i].mFlag = 0;
    }
}

// @ 0x00d48ae0
void FreeButtonTable()
{
    if (gButtonTable != 0)
        operator delete(gButtonTable);
    gButtonTable = 0;
}

void* FUN_00d1e610();                                     // 0x00d1e610
void UseAbility(void* user, int index);                    // 0x00d1e930
void ActivateAbilityTarget(int index);                     // 0x00d1fe00

// @ 0x00d48b00
void SelectAbility(int index)
{
    void* user = FUN_00d1e610();
    if (user != 0)
    {
        int count = ((int (__thiscall*)(void*))(*(void***)user)[0xb0 / 4])(user);
        if (index < count)
        {
            UseAbility(user, index);
            return;
        }
        if (GetCurrentGameMode() == 0x1654c02)
            ActivateAbilityTarget(index - count);
    }
}

class cSPUILayout
{
public:
    void* FindWindowByID(uint32_t windowID, int unused);   // 0x008105b0 (ret 8)
};

cSPUILayout* FUN_00d39000();      // 0x00d39000
cSPUILayout* FUN_00cc8990();      // 0x00cc8990
class cUILayoutManager
{
public:
    cSPUILayout* GetCurrentLayout();    // 0x00ef0dc0
};
extern cUILayoutManager* gUILayoutManager;   // 0x016c7aa4

// @ 0x00d48b50
void* GetCreatureGUIWindow(uint32_t windowID)
{
    cSPUILayout* layout;
    switch (GetCurrentGameMode())
    {
    case 0x1654c01: layout = FUN_00d39000(); break;
    case 0x1654c02: layout = FUN_00cc8990(); break;
    case 0x1654c10: layout = gUILayoutManager->GetCurrentLayout(); break;
    default: layout = 0; break;
    }
    return layout->FindWindowByID(windowID, 1);
}

// @ 0x00d48bc0
bool sGetButtonCategoryFromButtonID(uint32_t buttonID, int32_t* outIndex, int32_t* outCategory)
{
    if (gButtonTable == 0)
        return false;
    if (buttonID >= gButtonTable->mBase0 && buttonID < gButtonTable->mBase0 + gButtonTable->mCategoryCount)
    {
        *outCategory = 0;
        *outIndex = (int32_t)(buttonID - gButtonTable->mBase0);
        return true;
    }
    if (buttonID >= gButtonTable->mBase1 && buttonID < gButtonTable->mBase1 + gButtonTable->mCategoryCount)
    {
        *outCategory = 1;
        *outIndex = (int32_t)(buttonID - gButtonTable->mBase1);
        return true;
    }
    if (buttonID >= 0x1012030 && buttonID < 0x1012030 + gButtonTable->mCategoryCount)
    {
        *outCategory = 2;
        *outIndex = (int32_t)(buttonID - 0x1012030);
        return true;
    }
    if (buttonID >= 0x1012040 && buttonID < 0x1012040 + gButtonTable->mCategoryCount)
    {
        *outCategory = 4;
        *outIndex = (int32_t)(buttonID - 0x1012040);
        return true;
    }
    return false;
}

// @ 0x00d48cb0
uint32_t FindButtonIDBySlot(uint32_t buttonID)
{
    ButtonTable* t = gButtonTable;
    for (int cat = 0; cat < 5; ++cat)
    {
        for (int i = 0; i < 5; ++i)
        {
            if (t->mCategories[cat].mEntries[i].mID == (int32_t)buttonID)
            {
                switch (cat)
                {
                case 0:  return t->mBase0 + i;
                case 1:  return t->mBase1 + i;
                case 2:  return 0x1012030 + i;
                case 4:  return 0x1012040 + i;
                }
            }
        }
    }
    return 0;
}
