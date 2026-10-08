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
