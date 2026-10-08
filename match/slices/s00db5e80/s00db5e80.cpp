// Slice s00db5e80 -- SP::IDLE_VIGNETTE_Decide (0x00db65a0, 1643 bytes), the "decide" half of the citizen idle
// vignette behavior (PDB name). __cdecl, returns the decision priority in st0 (1.0 = chosen / 0.0 = none).
//   arg0 creature (cSPCreatureCitizen*), arg1/arg2 unused, arg3 flags (bit 5 = flag, 0x400 = disabled),
//   arg4 behavior_stimuli* (receives the chosen vignette), arg5 bool* (set to true when something was chosen).
// Flow: bail out unless the creature may idle. A creature in state 1 without flag bit 5 first looks the active
// event up in a global list (0x168b56c); a hit becomes the stimulus. Otherwise roll against the property
// 0x633e78a1 (default 0.5), pick the vignette table by key, find the tribe slot closest to the creature (slots
// are 0x14-byte records at tribe+0x294; disabled ones are skipped), measure the context of the tribe (day phase,
// crowd count, tribe role mask, relationship to the player's tribe) and collect every table entry (0x7b4 bytes)
// whose limits accept that context into a fixed vector, from which one is picked at random and stored as stimulus
// ints [3] = vignette index, [4] = tribe slot, [5] = table key.
// Names are Claude-coined except the PDB ones. Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (no EH frame),
// like the sibling SP::TRIBE_TAKE_OUT_TOOL_Tick (s00db4f60).
#include "types.h"

#include <float.h>

void* operator new(unsigned size, void* p);
inline void* operator new(unsigned, void* p) { return p; }
void operator delete(void* p);                                    // 0x00f47380

namespace SP {

struct Vec3 {
    float x, y, z;
};

#define PV(n) virtual void pv##n();

// Spatial/locomotive sub-object (creature+0xc0, tribe+0x120).
struct Loco {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a)
    virtual const Vec3* GetPosition();                                 // +0x2c
};

struct cTribe;

struct cSPCreatureCitizen {
    char pad00[0xc0];
    Loco mLoco;                                                        // +0xc0
    char padc4[0x135 - 0xc4];
    bool mbF135;                                                       // +0x135
    char pad136[0xb4c - 0x136];
    struct Behavior {
        char pad00[0x1d8];
        int  mId;                                                      // +0x1d8
    }* mpBehavior;                                                     // +0xb4c
    char padb50[0xb58 - 0xb50];
    unsigned mFlagsB58;                                                // +0xb58
    char padb5c[0xb5e - 0xb5c];
    bool mbB5e;                                                        // +0xb5e
    char padb5f[0xf90 - 0xb5f];
    bool mbCanIdle;                                                    // +0xf90

    char IsState1();                                                   // 0x00c0b770 (state at +0xb34 == 1)
    bool FUN_00c24560();                                               // 0x00c24560
    cTribe* GetTribe();                                                // 0x00c22f50
};

struct TribeSlot {                                                     // 0x14 bytes
    Vec3 mPos;
    int  mUnk0c;
    bool mbDisabled;                                                   // +0x10
};

struct TribeMember {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b) PV(0c) PV(0d) PV(0e)
    PV(0f) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15)
    virtual int GetRole();                                             // +0x58
};

struct CitizenRange { cSPCreatureCitizen** mpBegin; cSPCreatureCitizen** mpEnd; };
struct MemberRange  { TribeMember** mpBegin; TribeMember** mpEnd; };

struct cTribe {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b)
    PV(0c) PV(0d) PV(0e) PV(0f) PV(10) PV(11) PV(12)
    virtual int GetTribeId();                                          // +0x4c
    PV(14) PV(15) PV(16) PV(17)
    virtual float GetRadius();                                         // +0x60
    PV(19) PV(1a) PV(1b) PV(1c) PV(1d) PV(1e) PV(1f) PV(20) PV(21) PV(22) PV(23)
    virtual CitizenRange* GetCitizens();                               // +0x90
    PV(25) PV(26) PV(27) PV(28) PV(29) PV(2a) PV(2b) PV(2c) PV(2d) PV(2e)
    virtual MemberRange* GetMembers();                                 // +0xbc
    char pad04[0x120 - 0x4];
    Loco mLoco;                                                        // +0x120
    char pad124[0x294 - 0x124];
    TribeSlot* mpSlotsBegin;                                           // +0x294
    TribeSlot* mpSlotsEnd;                                             // +0x298

    float GetRating();                                                 // 0x00fc7f80 (returns 0.0)
};

struct DayNight {
    int IsDay(const Vec3* pos);                                        // 0x00bc2b80 (thiscall, ret 4)
};
DayNight* TimeOfDay();                                                 // 0x00bc30b0

struct RelationshipMgr {
    int GetRelationship(int a, int b, int c);                          // 0x00d00a70 (thiscall, ret 0xc)
};
RelationshipMgr* GetRelationshipManager();                             // 0x00b3d2c0

struct NounMgr {
    cTribe* GetPlayerTribe();                                          // 0x00bfc5f0
};
NounMgr* NounManager();                                                // 0x00b3d300

struct VignetteDef {                                                   // 0x7b4 bytes
    char pad00[4];
    int    mMinCrowd;                                                  // +0x004
    char pad08[0x78c - 0x8];
    float  mMinRating;                                                 // +0x78c
    float  mMaxRating;                                                 // +0x790
    char pad794[0x7a0 - 0x794];
    int    mDayPhase;                                                  // +0x7a0 (0 = any)
    int    mRelationship;                                              // +0x7a4 (-1 = any)
    char pad7a8[0x7ac - 0x7a8];
    unsigned mRoleMask;                                                // +0x7ac
    char pad7b0[4];
};
struct VignetteRange { VignetteDef* mpBegin; VignetteDef* mpEnd; };
struct VignetteTable {
    VignetteRange* Find(unsigned key, int a);                          // 0x00bc7610 (thiscall, ret 8)
};
VignetteTable* GetVignetteTable();                                     // 0x00b3d4e0

struct ActiveList {
    void* Find(unsigned id, bool (*pred)(void*, void*), void* ctx);    // 0x00bca620 (thiscall, ret 0xc)
};
ActiveList* GetActiveList();                                           // 0x00bc9b00
bool IdleEventPredicate(void* entry, void* ctx);                       // 0x00da7140

struct PropertyList;
float GetPropertyT_float(PropertyList* list, unsigned id, float def);  // 0x004e1c70 (cdecl)
extern PropertyList* g_DebugProps;                                     // 0x01581288

struct RandomLCG {
    double   RandomDoubleUniform();                                    // 0x009360d0
    unsigned RandomUint32Uniform(unsigned n);                          // 0x00a68fb0 (thiscall, ret 4)
};
extern RandomLCG gMathRandom;                                          // 0x01601760

} // namespace SP

#undef PV

namespace nSPBehaviorTree {
struct behavior_stimuli {
    struct stimulus {
        unsigned __int64 StimulusID;                                   // +0x0
        float Duration;                                                // +0x8
        unsigned Ints[8];                                              // +0xc
        unsigned pad2c;
        void GetAny();                                                 // 0x00d997e0 (resets the stimulus)
    } Stimuli[8];
};
}
using nSPBehaviorTree::behavior_stimuli;

namespace SP {

// eastl::fixed_vector<int, 16>
struct IntFixedVector {
    int*     mpBegin;
    int*     mpEnd;
    int*     mpCapacity;
    unsigned pad0c;
    int*     mpPoolBegin;
    unsigned pad14;
    int      mBuffer[16];

    IntFixedVector() : mpBegin(mBuffer), mpEnd(mBuffer), mpCapacity(mBuffer + 16), mpPoolBegin(mBuffer) {}
    ~IntFixedVector()
    {
        if (mpBegin && mpBegin != mpPoolBegin)
            operator delete(mpBegin);
    }
    void DoInsertValue(int* pos, const int& value);                    // 0x004281d0 (thiscall, ret 8)
    void push_back(const int& value)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) int(value);
        else
            DoInsertValue(mpEnd, value);
    }
    int* begin() { return mpBegin; }
    int* end() { return mpEnd; }
};

// @ 0x00db65a0
float IDLE_VIGNETTE_Decide(cSPCreatureCitizen* creature, int unused1, int unused2, unsigned flags,
                           behavior_stimuli* stimuli, bool* pChosen)
{
    if (!creature->mbCanIdle || (flags & 0x400))
        return 0.0f;

    unsigned char bit5 = (flags >> 5) & 1;
    char state1 = creature->IsState1();
    if (!bit5 && state1 == 1) {
        void* entry = GetActiveList()->Find(0x55241ec, IdleEventPredicate, creature);
        if (entry) {
            if (stimuli)
                stimuli->Stimuli[0].GetAny();
            *pChosen = true;
            *(unsigned*)stimuli = (unsigned)entry;
            return 1.0f;
        }
    }

    float chance = GetPropertyT_float(g_DebugProps, 0x633e78a1, 0.5f);
    if (gMathRandom.RandomDoubleUniform() > chance)
        return 0.0f;

    unsigned key;
    if (state1 == 0)
        key = 0x7dcc4e7e;
    else
        key = (bit5 ? 0xb546d379u : 0u) + 0x5523ddc;

    VignetteRange* table = GetVignetteTable()->Find(key, 0);
    if (table->mpBegin == table->mpEnd)
        return 0.0f;

    cTribe* tribe = creature->GetTribe();
    int nearest = -1;
    float nearestDist = FLT_MAX;
    const Vec3* pos = creature->mLoco.GetPosition();

    int slotCount = (int)(tribe->mpSlotsEnd - tribe->mpSlotsBegin);
    for (unsigned i = 0; i < (unsigned)slotCount; ++i) {
        TribeSlot* slot = &tribe->mpSlotsBegin[i];
        if (!slot->mbDisabled) {
            float dx = pos->x - slot->mPos.x;
            float dz = pos->z - slot->mPos.z;
            float dy = pos->y - slot->mPos.y;
            float d = dx * dx + dy * dy + dz * dz;
            if (d < nearestDist) {
                nearestDist = d;
                nearest = i;
            }
        }
    }
    if (nearest == -1)
        return 0.0f;

    const Vec3* tribePos = tribe->mLoco.GetPosition();
    int phase = -(TimeOfDay()->IsDay(tribePos) != 0) + 2;
    float rating = tribe->GetRating();
    int crowd = 0;
    float radius = tribe->GetRadius();
    float radiusSq = radius * radius;
    CitizenRange* citizens = tribe->GetCitizens();
    cSPCreatureCitizen** citizensEnd = citizens->mpEnd;
    for (cSPCreatureCitizen** it = citizens->mpBegin; it != citizensEnd; ++it) {
        cSPCreatureCitizen* c = *it;
        if (c->IsState1() && c->mbF135 && !c->mbB5e && c->FUN_00c24560() && !(c->mFlagsB58 & 0x10)
            && c->mpBehavior->mId != 0x5524115) {
            const Vec3* cp = c->mLoco.GetPosition();
            float dy = cp->y - tribePos->y;
            float dz = cp->z - tribePos->z;
            float dx = cp->x - tribePos->x;
            if (dz * dz + dy * dy + dx * dx < radiusSq)
                ++crowd;
        }
    }

    unsigned roleMask = 0;
    MemberRange* members = tribe->GetMembers();
    TribeMember** membersEnd = members->mpEnd;
    for (TribeMember** m = members->mpBegin; m != membersEnd; ++m)
        roleMask |= 1 << (*m)->GetRole();

    int relationship = -1;
    int tribeId = tribe->GetTribeId();
    cTribe* player = NounManager()->GetPlayerTribe();
    if (player && player != tribe) {
        int playerId = player->GetTribeId();
        relationship = GetRelationshipManager()->GetRelationship(tribeId, playerId, 1);
    }

    VignetteRange* defs = table;
    int defCount = (int)(defs->mpEnd - defs->mpBegin);
    IntFixedVector picks;
    for (int i = 0; i < defCount; ++i) {
        VignetteDef* d = &defs->mpBegin[i];
        if (d->mMinRating > rating)
            continue;
        if (rating > d->mMaxRating)
            continue;
        if (d->mDayPhase != 0 && d->mDayPhase != phase)
            continue;
        if (d->mRelationship != -1 && relationship != -1 && d->mRelationship != relationship)
            continue;
        if (d->mMinCrowd > crowd)
            continue;
        if (d->mRoleMask != 0 && (d->mRoleMask & roleMask) != d->mRoleMask)
            continue;
        picks.push_back(i);
    }
    if (picks.begin() == picks.end())
        return 0.0f;

    int chosen = picks.begin()[gMathRandom.RandomUint32Uniform((unsigned)(picks.end() - picks.begin()))];
    if (stimuli)
        stimuli->Stimuli[0].GetAny();
    stimuli->Stimuli[0].Ints[4] = nearest;
    stimuli->Stimuli[0].Ints[3] = chosen;
    stimuli->Stimuli[0].Ints[5] = key;
    *pChosen = true;
    return 1.0f;
}

} // namespace SP
