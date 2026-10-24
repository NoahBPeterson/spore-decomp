// SP::cEmpireGrowthSim / SP::BehaviorRule and the eastl::fixed_vector<Rule,18,1>
// template helpers (retail 0x00fea240..0x00feb117).
//
// The three rule sets live in a fixed_vector whose inline storage is 18 Rule
// records of 44 bytes; the retail block stride is 0x330 (0x18 header + 0x318
// array).  Rule = { float baseValue; float weights[10]; }.
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
// (the OnTick time comparison keeps the retail x87 fild/fcompi sequence, so no
// /fp:fast; the Rule zero-fill still needs SSE movss.)

#include "types.h"
#include <stddef.h>
#include <string.h>
#include <new>

// ---------------------------------------------------------------------------
// Rule element / eastl::fixed_vector<Rule,18,1>
// ---------------------------------------------------------------------------

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

// ---------------------------------------------------------------------------
// eastl helpers (same allocator / copy machinery as the retail template)
// ---------------------------------------------------------------------------

void* AllocateBlocks(uint32_t size, const char* name, int a, int b, const char* file, int line); // 0x00f473a0
void FreeArray(void* p);                                                                          // 0x00f47380
Rule* CopyRange(Rule* first, Rule* last, Rule* dst);                                             // 0x00b3d890
void FillConstruct(Rule* dst, uint32_t n, const Rule* value);                                    // 0x00fe8df0
void UninitCopy(void* out, Rule* first, Rule* last, Rule* dst, Rule* tag);                        // 0x00fe8db0
void CopyBackward(Rule* first, Rule* last, Rule* dst);                                            // 0x00fe8f20
void DestroyRange(Rule* first, Rule* last, const Rule* value);                                    // 0x00fe8d80

static const char* const kAllocFile =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";

void CopyStrings(void* src, void* end, void* dst); // 0x007c8b70

// @ 0x00fea240
Rule* RuleVector::erase(Rule* first, Rule* last) {
    Rule* dst = first;
    Rule* src = last;
    Rule* const end = mpEnd;
    while (src != end)
        *dst++ = *src++;
    mpEnd += last - first;
    return first;
}

// @ 0x00fea2a0
void RuleVector::insert(Rule* pos, uint32_t n, const Rule* value) {
    if ((uint32_t)(mpCapacity - mpEnd) < n) {
        int count = (int)(mpEnd - mpBegin);
        uint32_t newCap = (uint32_t)count * 2;
        if (count == 0)
            newCap = 1;
        uint32_t need = (uint32_t)count + n;
        if (need > newCap)
            newCap = need;
        Rule* buf = 0;
        if (newCap)
            buf = (Rule*)AllocateBlocks(newCap * 0x2c, "Simulator", 0, 0, kAllocFile, 0xd1);
        Rule* mid = CopyRange(mpBegin, pos, buf);
        FillConstruct(mid, n, value);
        Rule* end = CopyRange(pos, mpEnd, (Rule*)((char*)mid + n * 0x2c));
        Rule* old = mpBegin;
        if (old != 0 && old != mpBuffer)
            FreeArray(old);
        mpBegin = buf;
        mpEnd = end;
        mpCapacity = (Rule*)((char*)buf + newCap * 0x2c);
    } else if (n != 0) {
        Rule tmp = *value;
        Rule* oldEnd = mpEnd;
        uint32_t after = (uint32_t)(oldEnd - pos);
        if (after <= n) {
            uint32_t extra = n - after;
            FillConstruct(oldEnd, extra, &tmp);
            mpEnd = (Rule*)((char*)mpEnd + extra * 0x2c);
            UninitCopy(pos, pos, oldEnd, mpEnd, pos);
            mpEnd = (Rule*)((char*)mpEnd + after * 0x2c);
            DestroyRange(pos, oldEnd, &tmp);
        } else {
            Rule* split = (Rule*)((char*)oldEnd - n * 0x2c);
            UninitCopy(split, split, oldEnd, oldEnd, pos);
            mpEnd = (Rule*)((char*)mpEnd + n * 0x2c);
            CopyBackward(pos, split, oldEnd);
            DestroyRange(pos, (Rule*)((char*)pos + n * 0x2c), &tmp);
        }
    }
}

// @ 0x00fea460
void RuleVector::resize(uint32_t newSize) {
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

// ---------------------------------------------------------------------------
// Property list / script parser types (only the touched members are named)
// ---------------------------------------------------------------------------

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

struct IPropertyManager {
    virtual void m00();
    virtual void m04();
    virtual void m08();
    virtual void m0c();
    virtual void m10();
    virtual void m14();
    virtual void m18();
    virtual void m1c();
    virtual void m20();
    virtual void m24();
    virtual void m28();
    virtual void m2c(uint32_t a, uint32_t b, cPropertyList** out); // +0x2c
};

bool TryGetUIntProperty(cPropertyList* pl, uint32_t key, void* out); // 0x00410370

// ---------------------------------------------------------------------------
// EA::ArgScript (BehaviorRule command/spec)
// ---------------------------------------------------------------------------

namespace EA {
namespace ArgScript {

struct cCommandBase {
    cCommandBase();                              // 0x0083c800
    virtual void Execute(void* args);            // slot 0
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    void* mpParser;      // +0x04
    void* mpState;       // +0x08
    uint32_t mRefCount;  // +0x0c
};

struct cArgumentSpec {
    uint8_t mData[0xc8];
    cArgumentSpec(bool flag);                              // 0x0083a9f0
    void Parse(void* args, void* parser);                  // 0x0083b9d0
};

} // namespace ArgScript
} // namespace EA

void ConstructSpec(EA::ArgScript::cArgumentSpec* spec, const char* name, ...); // 0x0083bcd0

class BehaviorRule : public EA::ArgScript::cCommandBase {
public:
    BehaviorRule();
    virtual void Execute(void* args);

    EA::ArgScript::cArgumentSpec mArgSpec; // +0x10
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

// @ 0x00fea960
BehaviorRule::BehaviorRule() : mArgSpec(true) {
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
void BehaviorRule::Execute(void* args) {
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

// ---------------------------------------------------------------------------
// cEmpireGrowthSim
// ---------------------------------------------------------------------------

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

// ---------------------------------------------------------------------------
// External entry points / globals used by the sim
// ---------------------------------------------------------------------------

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
void FUN_00555bc0(void* a, void* b, void* c);      // 0x00555bc0
void FUN_007c81c0(void* a, void* b, void* c);      // 0x007c81c0
void SPVector_reserve(Vec* v, uint32_t n);         // 0x004e0880
void* CreateParser();                              // 0x008408d0
void* AllocateBehaviorRule(uint32_t size);         // 0x006abeb0
void AddRuleToParser(void* parser, const char* name, BehaviorRule* rule); // 0x001458378
void PlayoutBehavior(BehaviorRule* rule, const char* text);              // 0x00fe8b90

IPropertyManager* PropertyManager();                    // 0x0067de30
void GetPlayerEmpireID();                               // 0x01021090
struct IUniverseCtx { bool FUN_010449e0(); };
IUniverseCtx* __stdcall FUN_01046fc0(int which);          // 0x01046fc0

struct cViewer {
    cViewer* FUN_007c3f70();                            // 0x007c3f70
    bool Init(bool flag);                               // 0x007c4dd0
    void FUN_007c3ba0();                                // 0x007c3ba0
    void FUN_007c4000();                                // 0x007c4000
};

struct VtableHolder {
    void* mpVtable;   // +0x00
    void* mpField4;   // +0x04
};

struct ViewerHolder {
    void* mpUnk0;     // +0x00
    void* mpViewer;   // +0x04
};

extern float g_TickRate;                           // 0x0145c19c
extern float g_FilterConst;                        // 0x013eb1bc
extern float g_FilterConst2;                       // 0x014853bc

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

struct IParser {
    virtual void Reset();                          // 0x00
    virtual void Destroy();                        // 0x04
    virtual void s08();                            // 0x08
    virtual void s0c();                            // 0x0c
    virtual void s10();                            // 0x10
    virtual void s14(const char* name, BehaviorRule* rule, void* extra); // 0x14
    virtual void s18();
    virtual void s1c();
    virtual void s20();
    virtual void s24();
    virtual void s28();
    virtual void s2c();
    virtual void s30();
    virtual void s34(uint32_t flag);               // 0x34
    virtual void s38();
    virtual void s3c();
    virtual void s40();
    virtual void s44();
    virtual void s48();
    virtual void s4c();
    virtual bool s50(const char* text);            // 0x50
};

// @ 0x00fea510
void cEmpireGrowthSim::OnTick(uint32_t dtLo, uint32_t dtHi) {
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
bool FUN_00fea840(cPropertyList* manager, uint32_t key, uint16_t type, Vec* dst) {
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
bool FUN_00fea8d0(cPropertyList* manager, uint32_t key, uint16_t type, StringVector* dst) {
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

// @ 0x00feab10
uint8_t cEmpireGrowthSim::FillOutBehaviorRules(uint32_t mode, StringVector* list) {
    IParser* parser = (IParser*)CreateParser();
    if (parser)
        parser->Reset();
    parser->s08();

    BehaviorRule* rule = (BehaviorRule*)AllocateBehaviorRule(0x10c);
    if (rule) {
        rule = new (rule) BehaviorRule();
        rule->v0c();
    }
    parser->s14("data", rule, 0);
    parser->s30();

    bool good = true;
    uint32_t count = (uint32_t)(((char*)list->mpEnd - (char*)list->mpBegin) >> 4);
    for (uint32_t i = 0; i < count; ++i) {
        char* text = *(char**)((char*)list->mpBegin + i * 16);
        if (good)
            good = parser->s50(text);
        PlayoutBehavior(rule, text);
    }

    parser->s34(good ? 1 : 0);
    parser->s0c();
    if (rule)
        rule->v10();
    parser->Destroy();
    return (uint8_t)good;
}

// @ 0x00feacd0
cEmpireGrowthSim::cEmpireGrowthSim() {
    mpVtable0 = (void*)0x01494498;
    mpVtable8 = (void*)0x01494474;

    mStarColorWeights = Vec();
    mStarRelationshipModifier = Vec();
    mElapsedTimeSinceLastTick = 0;
    mElapsedTimeInContext = 0;
    mbPaused = 0;
    mbTickPaused = 0;
    mMinTimeMin = 0;
    mMaxTimeMin = 0;
    mInitForcedTurnCount = 0;
    mForcedTurnCount = 0;
    mLastContext = -1;
    mEmpireStack = Vec();
    mEmpireIDs = Vec();
    mpPropList = 0;

    for (int i = 0; i < 3; ++i) {
        RuleVector& r = mRuleSet[i];
        r.mpBuffer = r.mBuffer;
        r.mpBegin = r.mBuffer;
        r.mpEnd = r.mBuffer;
        r.mpCapacity = r.mBuffer + 18;
    }

    IPropertyManager* pm = (IPropertyManager*)PropertyManager();
    if (mpPropList) {
        mpPropList = 0;
    }
    pm->m2c(0x249e8357, 0x2ae0c7e, &mpPropList);

    int mod = (mpPropList->mModificationCount == 0) ? 0 : mpPropList->GetModificationCount();
    mPropListModCount = mpPropList->mDescriptionCount + mod;

    Property* prop = 0;
    if (mpPropList->GetProperty(0x429d68c, &prop) && prop->mType == 9)
        mMinTimeMin = *prop->GetInt();
    if (mpPropList->GetProperty(0x429d69c, &prop) && prop->mType == 9)
        mMaxTimeMin = *prop->GetInt();
    if (mpPropList->GetProperty(0x56e61e5, &prop) && prop->mType == 9)
        mInitForcedTurnCount = *prop->GetInt();

    mStarColorWeights.Reserve(3);
    mStarRelationshipModifier.Reserve(9);
    FUN_00fea840(mpPropList, 0x553cc31, 9, &mStarColorWeights);
    FUN_00fea840(mpPropList, 0x553cc32, 9, &mStarRelationshipModifier);

    for (int i = 0; i < 3; ++i)
        mRuleSet[i].resize(0x12);

    void* buf = AllocateBlocks(0xa0, "Simulator", 0, 0, kAllocFile, 0xd1);
    FUN_00555bc0(0, 0, buf);
    FUN_007c81c0(0, 0, buf);

    StringVector list = {};
    list.mpBegin = buf;
    list.mpEnd = buf;
    list.mpCapacity = (char*)buf + 0xa0;

    for (uint32_t i = 0; i < 3; ++i) {
        FUN_00fea8d0(mpPropList, 0x56e61e1 + i, 0x12, &list);
        FillOutBehaviorRules(i, &list);
    }

    if (buf)
        FreeArray(buf);
}

// @ 0x00feb050
void* __fastcall FUN_00feb050(VtableHolder* self) {
    self->mpVtable = (void*)0x014948a4;
    self->mpField4 = 0;
    return self;
}

// @ 0x00feb060
void __fastcall FUN_00feb060(ViewerHolder* self) {
    void* mem = AllocateBlocks(0x174, "Simulator", 0, 0, 0, 0);
    cViewer* viewer;
    if (mem)
        viewer = ((cViewer*)mem)->FUN_007c3f70();
    else
        viewer = 0;
    self->mpViewer = viewer;
    viewer->Init(false);
}

// @ 0x00feb0b0
bool __stdcall FUN_00feb0b0(uint32_t empireID) {
    GetPlayerEmpireID();
    if (((IUniverseCtx*)FUN_01046fc0(1))->FUN_010449e0())
        return true;
    if (((IUniverseCtx*)FUN_01046fc0(0))->FUN_010449e0()) {
        if (empireID == (uint32_t)(size_t)GetPlayerEmpire())
            return true;
    }
    return false;
}

// @ 0x00feb0f0
void __fastcall FUN_00feb0f0(ViewerHolder* self) {
    if (self->mpViewer) {
        ((cViewer*)self->mpViewer)->FUN_007c3ba0();
        void* viewer = self->mpViewer;
        if (viewer) {
            ((cViewer*)viewer)->FUN_007c4000();
            FreeArray(viewer);
        }
    }
}
