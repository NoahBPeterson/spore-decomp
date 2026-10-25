// src/game/SPGonzago/SPEmpireGrowthSim.cpp -- migrated from slice(s) s00fea240 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPEmpireGrowthSim.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Variant.h"
#include "EA/ArgScript/cArgumentSpec.h"
#include "EA/ArgScript/cCommandBase.h"
#include "SP/cGonzagoSimulator.h"
#include "SP/cPropertyList.h"
#include "SP/cStarManager.h"
#include "SP/cViewer.h"

// unnamed retail callees and globals (address in the comment)
extern char sEmptyString;      // 0x013ec47c
extern char sGameModeSpace;                       // 0x01654c05
extern float g_TickRate;                           // 0x0145c19c
#include <stddef.h>
#include <string.h>
#include <new>

// ---- items of slice s00fea240 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Rule {
    float baseValue;        // +0x00
    float weights[10];      // +0x04
};
struct RuleVector {
    Rule* mpBegin;          // +0x00
    Rule* mpEnd;            // +0x04
    Rule* mpCapacity;       // +0x08
    uint32_t mAllocPad0;    // +0x0c
    Rule* mpBuffer;         // +0x10
    uint32_t mAllocPad1;    // +0x14
    Rule mBuffer[18];       // +0x18 (0x318 bytes)

    Rule* erase(Rule* first, Rule* last);
    void insert(Rule* pos, uint32_t n, const Rule* value);
    void resize(uint32_t newSize);
};
void CopyStrings(void* src, void* end, void* dst); // 0x007c8b70
struct Property {
    void* mpData;        // +0x00
    uint32_t mPad04;
    uint32_t mCount;     // +0x08
    uint32_t mPad0c;
    uint16_t mFlags;     // +0x10
    uint16_t mType;      // +0x12
    int* GetInt();       // 0x0041e990
};
struct cPropertyList {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual bool GetProperty(uint32_t key, Property** out); // +0x24
    uint32_t mPad04[11];       // +0x04..0x30
    int mModificationCount;    // +0x30
    int mDescriptionCount;     // +0x34
    int GetModificationCount(); // 0x006237a0
};
bool TryGetUIntProperty(cPropertyList* pl, uint32_t key, void* out); // 0x00410370
namespace EA {
namespace ArgScript {
struct cCommandBase_s00fe_a240 {
    cCommandBase_s00fe_a240();                              // 0x0083c800
    virtual void Execute(void* args);            // slot 0
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    void* mpParser;      // +0x04
    void* mpState;       // +0x08
    uint32_t mRefCount;  // +0x0c
};
}
}
namespace EA {
namespace ArgScript {
struct cArgumentSpec_s00fe_a240 {
    uint8_t mData[0xc8];
    cArgumentSpec_s00fe_a240(bool flag);                              // 0x0083a9f0
    void Parse(void* args, void* parser);                  // 0x0083b9d0
};
}
}
void ConstructSpec(EA::ArgScript::cArgumentSpec_s00fe_a240* spec, const char* name, ...); // 0x0083bcd0
class BehaviorRule : public EA::ArgScript::cCommandBase_s00fe_a240 {
public:
    BehaviorRule();
    virtual void Execute(void* args);

    EA::ArgScript::cArgumentSpec_s00fe_a240 mArgSpec; // +0x10
    float mBaseValue;          // +0xd8
    float mNearMe;             // +0xdc
    float mNearEnemy;          // +0xe0
    float mNearNeutral;        // +0xe4
    float mNearAlly;           // +0xe8
    float mEmpireStars;        // +0xec
    float mEmpireColonies;     // +0xf0
    float mFriend;             // +0xf4
    float mEnemy;              // +0xf8
    float mRelationship;       // +0xfc
    float mPlayer;             // +0x100
    char* mActionName;         // +0x104
    char* mColorName;          // +0x108
};
extern char sEmptyString;      // 0x013ec47c
struct Vec {
    void* mpBegin;       // +0x00
    void* mpEnd;         // +0x04
    void* mpCapacity;    // +0x08
    uint32_t mAlloc0;    // +0x0c
    uint32_t mAlloc1;    // +0x10
    void Reserve(uint32_t n);        // 0x004cd3c0
};
class cGonzagoSimulator {
public:
    cGonzagoSimulator();   // 0x00b5b6c0
    void* mpVtable0;       // +0x00
    uint32_t mPad04;       // +0x04
    void* mpVtable8;       // +0x08
    uint32_t mPad0c;       // +0x0c
};
struct StringVector {
    void* mpBegin;       // +0x00
    void* mpEnd;         // +0x04
    void* mpCapacity;    // +0x08
    void StringVectorResize(uint32_t n); // 0x00553be0
};
class cEmpireGrowthSim : public cGonzagoSimulator {
public:
    cEmpireGrowthSim();
    void OnTick(uint32_t dtLo, uint32_t dtHi);
    void TakeTurn(uint32_t empireID);                 // 0x00fe9580
    bool IsPlayerProtected();                         // 0x00fe8990
    uint8_t FillOutBehaviorRules(uint32_t mode, StringVector* list);

    Vec mStarColorWeights;            // +0x10
    Vec mStarRelationshipModifier;    // +0x24
    uint64_t mElapsedTimeSinceLastTick; // +0x38
    uint64_t mElapsedTimeInContext;     // +0x40
    uint8_t mbPaused;                 // +0x48
    uint8_t mbTickPaused;             // +0x49
    uint16_t mPad4a;                  // +0x4a
    int mMinTimeMin;                  // +0x4c
    int mMaxTimeMin;                  // +0x50
    int mInitForcedTurnCount;         // +0x54
    int mForcedTurnCount;             // +0x58
    int mLastContext;                 // +0x5c
    Vec mEmpireStack;                 // +0x60
    uint32_t mPad74;                  // +0x74
    Vec mEmpireIDs;                   // +0x78
    uint32_t mPad8c;                  // +0x8c
    cPropertyList* mpPropList;        // +0x90
    int mPropListModCount;            // +0x94
    RuleVector mRuleSet[3];           // +0x98 (0x990 bytes)
};
void* GetCurrentGameMode();                       // 0x00b5b800
extern char sGameModeSpace;                       // 0x01654c05
int GetUniverseContext();                         // 0x01021080
void* StarManager(void* arg);                     // 0x00b3d2a0
void* GetAvatar(void* record);                    // 0x00b1fdb0
void* GetEmpireByID(void* avatar);                // 0x00ba9370
void* GetPlayerEmpire();                          // 0x01021300
uint32_t GetItemInstanceID(void* item);           // 0x00c87040
void* MessageServer();                            // 0x0067dcc0
void InsertSet(Vec* set, void* out, void* value); // 0x00554020
void FUN_00d04080(void* rp);                       // 0x00d04080
void* RelationshipManager(Vec* set);               // 0x00b3d2c0
void DestroyRecordList(void* p);                   // 0x00ae6970
extern float g_TickRate;                           // 0x0145c19c
struct StarQuery {
    void* FUN_00c8b360();                          // 0x00c8b360
};
StarQuery* FUN_01021230(void* out, void* params);  // 0x01021230
struct cStarManager {
    void* GetStarRecords();                        // 0x00bb1080
};
struct IMessageServer {
    virtual void s00();
    virtual void s04();
    virtual void s08();
    virtual void s0c();
    virtual void s10();
    virtual void s14(uint32_t id, int a, int b);   // +0x14
};
// ---- items of slice s00fea240 end

// @ 0x00fea240
Rule* RuleVector::erase(Rule* first, Rule* last)
{
    Rule* dst = first;
    Rule* src = last;
    Rule* const end = mpEnd;
    while (src != end)
        *dst++ = *src++;
    mpEnd += last - first;
    return first;
}

// @ 0x00fea460
void RuleVector::resize(uint32_t newSize)
{
    if (newSize > (uint32_t)(mpEnd - mpBegin)) {
        Rule empty;
        empty.baseValue = 0.0f;
        empty.weights[0] = 0.0f;
        empty.weights[1] = 0.0f;
        empty.weights[2] = 0.0f;
        empty.weights[3] = 0.0f;
        empty.weights[4] = 0.0f;
        empty.weights[5] = 0.0f;
        empty.weights[6] = 0.0f;
        empty.weights[7] = 0.0f;
        empty.weights[8] = 0.0f;
        empty.weights[9] = 0.0f;
        insert(mpEnd, newSize - (uint32_t)(mpEnd - mpBegin), &empty);
    } else {
        erase(mpBegin + newSize, mpEnd);
    }
}

// @ 0x00fea510
void cEmpireGrowthSim::OnTick(uint32_t dtLo, uint32_t dtHi)
{
    if (GetCurrentGameMode() != &sGameModeSpace)
        return;
    if (IsPlayerProtected() && mForcedTurnCount == 0)
        return;

    cPropertyList* pl = mpPropList;
    int mod = (pl->mModificationCount == 0) ? 0 : pl->GetModificationCount();
    int stamp = pl->mDescriptionCount + mod;
    if (stamp != mPropListModCount) {
        int mod2 = (pl->mModificationCount == 0) ? 0 : pl->GetModificationCount();
        mPropListModCount = pl->mDescriptionCount + mod2;
        TryGetUIntProperty(pl, 0x429d68c, &mMinTimeMin);
        TryGetUIntProperty(mpPropList, 0x429d69c, &mMaxTimeMin);
    }

    if (mEmpireStack.mpBegin != mEmpireStack.mpEnd) {
        uint32_t empireID = ((uint32_t*)mEmpireStack.mpEnd)[-1];
        mEmpireStack.mpEnd = (char*)mEmpireStack.mpEnd - 4;
        TakeTurn(empireID);
        uint32_t out;
        uint32_t value = empireID;
        InsertSet(&mEmpireIDs, &out, &value);
        return;
    }

    if (mEmpireIDs.mpBegin != mEmpireIDs.mpEnd) {
        void* rp = RelationshipManager(&mEmpireIDs);
        FUN_00d04080(rp);
        mEmpireIDs.mpEnd = mEmpireIDs.mpBegin;
    }

    int ctx = GetUniverseContext();
    uint32_t savedLo = 0;
    uint32_t savedHi = 0;
    if (!IsPlayerProtected()) {
        if ((mLastContext == 2) == (ctx == 2)) {
            mElapsedTimeSinceLastTick += ((uint64_t)dtHi << 32) | dtLo;
        } else {
            savedLo = (uint32_t)mElapsedTimeSinceLastTick;
            savedHi = (uint32_t)(mElapsedTimeSinceLastTick >> 32);
            mElapsedTimeSinceLastTick = 0;
            mLastContext = ctx;
        }
        mElapsedTimeInContext += ((uint64_t)dtHi << 32) | dtLo;
    }

    uint64_t saved = ((uint64_t)savedHi << 32) | savedLo;
    if ((ctx == 2 && (double)mMinTimeMin * (double)g_TickRate <= (double)(int64_t)saved) ||
        ((double)mMaxTimeMin * (double)g_TickRate <= (double)(int64_t)mElapsedTimeInContext) ||
        (mForcedTurnCount != 0)) {
        if (mForcedTurnCount != 0)
            mForcedTurnCount -= 1;

        mElapsedTimeSinceLastTick = 0;
        mElapsedTimeInContext = 0;

        uint8_t q0[0x18] = {0};
        uint8_t q1[0x18] = {0};
        StarQuery* q = FUN_01021230(&q1, &q0);
        void* ctxObj = q->FUN_00c8b360();
        cStarManager* sm = (cStarManager*)StarManager(ctxObj);
        struct StarRecordList {
            void* mpBegin;
            void* mpEnd;
            void* mpCapacity;
        }* recs = (StarRecordList*)sm->GetStarRecords();

        int count = (int)((char*)recs->mpEnd - (char*)recs->mpBegin) >> 2;
        for (int i = 0; i < count; ++i) {
            void* record = ((void**)recs->mpBegin)[i];
            void* avatar = GetAvatar(record);
            void* empire = GetEmpireByID(avatar);
            void* playerEmpire = GetPlayerEmpire();
            if (avatar != *(void**)((char*)playerEmpire + 0x84) &&
                (GetItemInstanceID(record) & 0x100) == 0 &&
                ((*(uint32_t*)((char*)empire + 0x50) >> 6) & 1) == 0) {
                uint32_t out;
                uint32_t value = (uint32_t)(size_t)record;
                InsertSet(&mEmpireIDs, &out, &value);
            }
        }

        if (mEmpireStack.mpBegin != mEmpireStack.mpEnd)
            ((IMessageServer*)MessageServer())->s14(0x609f3d9, 0, 0);
        DestroyRecordList(&q0);
    }
}

// @ 0x00fea840
bool FUN_00fea840(cPropertyList* manager, uint32_t key, uint16_t type, Vec* dst)
{
    if (manager != 0) {
        Property* prop;
        if (manager->GetProperty(key, &prop) &&
            prop->mType == type &&
            (prop->mFlags & 0x10) != 0) {
            uint32_t count = (prop->mFlags & 0x30) ? prop->mCount
                                                   : (uint32_t)(prop->mType != 0);
            void* src = (prop->mFlags & 0x30) ? prop->mpData
                                              : (prop->mType != 0 ? (void*)prop : 0);
            dst->Reserve(count);
            memcpy(dst->mpBegin, src, count * 4);
            return true;
        }
    }
    return false;
}

// @ 0x00fea8d0
bool FUN_00fea8d0(cPropertyList* manager, uint32_t key, uint16_t type, StringVector* dst)
{
    if (manager != 0) {
        Property* prop;
        if (manager->GetProperty(key, &prop) &&
            prop->mType == type &&
            (prop->mFlags & 0x10) != 0) {
            uint32_t count = (prop->mFlags & 0x30) ? prop->mCount
                                                   : (uint32_t)(prop->mType != 0);
            void* src = (prop->mFlags & 0x30) ? prop->mpData
                                              : (prop->mType != 0 ? (void*)prop : 0);
            dst->StringVectorResize(count);
            CopyStrings(src, (char*)src + count * 16, dst->mpBegin);
            return true;
        }
    }
    return false;
}

// @ 0x00fea960
BehaviorRule::BehaviorRule()
: mArgSpec(true) {
    ConstructSpec(&mArgSpec,
                  "Behavior Definition",
                  "<value:float>",
                  &mBaseValue,
                  "base value",
                  "<action:cstring>",
                  &mActionName,
                  "action Type",
                  "-color <name:cstring>",
                  &mColorName,
                  "color of star to deal with",
                  "-nearMe <val:float>",
                  &mNearMe,
                  "value modifier for nearMe",
                  "-nearEnemy <val:float>",
                  &mNearEnemy,
                  "value modifier for nearEnemy",
                  "-nearNeutral <val:float>",
                  &mNearNeutral,
                  "value modifier for nearNeutral",
                  "-nearAlly <val:float>",
                  &mNearAlly,
                  "value modifier for nearAlly",
                  "-relationship <val:float>",
                  &mRelationship,
                  "multiplier for the actual relationship value",
                  "-ally <val:float>",
                  &mFriend,
                  "value modifier for Friendly Star",
                  "-enemy <val:float>",
                  &mEnemy,
                  "value modifier for Enemy Star",
                  "-empireStars <val:float>",
                  &mEmpireStars,
                  "value modifier for number of empire stars",
                  "-empireColonies <val:float>",
                  &mEmpireColonies,
                  "value modifier for number of empire colonies",
                  "-player <val:float>",
                  &mPlayer,
                  "value modifier for player",
                  0);
}

// @ 0x00feaa70
void BehaviorRule::Execute(void* args)
{
    void* parser = mpParser;
    mBaseValue = 0.0f;
    mNearEnemy = 0.0f;
    mNearNeutral = 0.0f;
    mNearAlly = 0.0f;
    mEmpireStars = 0.0f;
    mEmpireColonies = 0.0f;
    mNearMe = 0.0f;
    mFriend = 0.0f;
    mEnemy = 0.0f;
    mPlayer = 0.0f;
    mRelationship = 0.0f;
    mColorName = &sEmptyString;
    mArgSpec.Parse(args, parser);
}
