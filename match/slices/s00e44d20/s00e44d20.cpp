// Slice s00e44d20 -- SP::EditorValidity (editor cell validity / upgrade-parts builder).
//   Tick                       : 12-state timed-tooltip sequence tick           (byte-exact)
//   AddCellUpgradeParts        : rebuild the validity match set for a cell kind  (nonmatching)
// Flags: Tick /O2 /MD /Gy /EHsc /TP /arch=SSE /fp=fast;
//        AddCellUpgradeParts /O2 /MD /Gy /TP /GS- /arch=SSE /fp=fast.
typedef unsigned char uchar;

// ---------------------------------------------------------------------------------------------
// externs
// ---------------------------------------------------------------------------------------------
extern const float gkHalf;                                   // 0x01471064  (0.5f)
extern const float gkSettleTime;                             // 0x01486374  (0.8f)
extern const float gkHoldTime;                               // 0x01481ca8  (0.2f)

extern uchar gPendingUpgrade;                                // 0x015a5a84

// ---------------------------------------------------------------------------------------------
// stopwatch-backed property part (EA::Stopwatch at +0x00, cDirectPropertyList interface)
// ---------------------------------------------------------------------------------------------
struct TimedPropertyPart {
    char mPad000[0x18];

    float GetElapsedTimeFloat();                             // 0x005ff1a0
    void  SetBoolProperty();                                 // 0x0093a2e0
    void  Restart();                                         // 0x00571e80
};

// ---------------------------------------------------------------------------------------------
// SP::FunctionalMatch::Constraint -- 0x0c bytes, key/type/value triple
// ---------------------------------------------------------------------------------------------
const int kEqualConstraint = 0;

struct Constraint {
    int mKey;                                                // +0x00
    int mType;                                               // +0x04
    int mValue;                                              // +0x08

    Constraint(int key, int type, int value);                // 0x00558960
    ~Constraint();                                           // 0x006066f0
};

// SP::FunctionalMatch::ConstraintNode -- 0x24-byte element of the scratch list
struct ConstraintNode {
    Constraint mConstraint;                                  // +0x00
    char mPad00c[0x24 - 0x0c];

    ConstraintNode(const Constraint& value);                 // 0x00606880
};

// eastl::vector<Constraint, sp_vector_allocator>
struct ConstraintVector {
    Constraint* mpBegin;                                     // +0x00
    Constraint* mpEnd;                                       // +0x04
    Constraint* mpCap;                                       // +0x08

    int  Count() const { return (int)(mpEnd - mpBegin); }
    void PushBack(const Constraint& value);                  // 0x004e18e0
};

// eastl::vector<ConstraintNode, sp_vector_allocator>
struct ConstraintNodeVector {
    ConstraintNode* mpBegin;                                 // +0x00
    ConstraintNode* mpEnd;                                   // +0x04
    ConstraintNode* mpCap;                                   // +0x08

    void PushBack(const Constraint& value);                  // 0x004e38d0 / 0x004e39d0
};

// a key produced by the template-DB query -- the same 0x0c bytes as Constraint
typedef Constraint TemplateKey;

struct TemplateKeyVector {
    TemplateKey* mpBegin;                                    // +0x00
    TemplateKey* mpEnd;                                      // +0x04
    TemplateKey* mpCap;                                      // +0x08
};

struct ObjectTemplateDB {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08();
    // vtable +0x24: collect the templates matching one constraint round
    virtual void QueryMatchingParts(TemplateKeyVector* pOut, int round, ConstraintNodeVector* pPending);
};

extern ObjectTemplateDB* gObjectTemplateDB;                  // 0x015a5a90

// the per-cell slot collectors (free functions over the slot vector)
extern "C" void __cdecl CollectUpgradeHead(ConstraintVector* pSlots);      // 0x00e434a0
extern "C" void __cdecl CollectUpgradeBody(ConstraintVector* pSlots);      // 0x00e435c0
extern "C" void __cdecl CollectUpgradeLimb(ConstraintVector* pSlots);      // 0x00e3ede0
extern "C" void __cdecl CollectUpgradeCreature(ConstraintVector* pSlots);  // 0x00e43710

// ---------------------------------------------------------------------------------------------
// the validity object itself (thiscall methods)
// ---------------------------------------------------------------------------------------------
struct EditorValidity {
    char mPad000[0x3f0];
    int  mState;                                             // +0x3f0
    char mPad3f4[0x450 - 0x3f4];
    float mField450;                                         // +0x450
    uchar mDone;                                             // +0x454
    char mPad455[0x45c - 0x455];
    int  mCell;                                              // +0x45c
    ConstraintVector mUpgradeSlots;                          // +0x460
    char mPad46c[0x474 - 0x46c];
    TemplateKey* mpOutBegin;                                 // +0x474
    TemplateKey* mpOutEnd;                                   // +0x478
    char mPad47c[0x494 - 0x47c];
    float mField494;                                         // +0x494
    float mField498;                                         // +0x498
    uchar mCancelled;                                        // +0x49c
    char mPad49d[0x4f0 - 0x49d];
    TimedPropertyPart mPart4f0;                              // +0x4f0
    uchar mField508;                                         // +0x508
    char mPad509[0x510 - 0x509];
    TimedPropertyPart mPart510;                              // +0x510
    uchar mField528;                                         // +0x528
    char mPad529[0x530 - 0x529];
    TimedPropertyPart mPart530;                              // +0x530
    TimedPropertyPart mPart548;                              // +0x548

    bool UpdateA();                                          // 0x00e36cd0
    bool UpdateB();                                          // 0x00e36d30
    bool UpdateC();                                          // 0x00e36d80
    bool StepBack();                                         // 0x00e38bb0
    bool Step();                                             // 0x00e38c90
    void StartFadeOut();                                     // 0x00e390d0
    void ShowValidity();                                     // 0x00e39200
    bool PushUpgrade();                                      // 0x00e3b0b0
    void RefreshLayout();                                    // 0x00e40420

    void CommitUpgradeSlots();                               // 0x004f6b70.. (slot range commit)
    void AddCellUpgradeParts(int cell);                      // 0x00e44d20
    void Tick();                                             // 0x00e45460
};

// @ 0x00e45460
void EditorValidity::Tick()
{
    switch (mState) {
    case 1:
        if (gkHalf < mPart4f0.GetElapsedTimeFloat()) {
            mPart4f0.SetBoolProperty();
            StartFadeOut();
            mState = 2;
        }
        return;

    case 2:
        if (gkHalf < mPart530.GetElapsedTimeFloat()) {
            mPart530.SetBoolProperty();
            mPart548.Restart();
            mState = 3;
        }
        return;

    case 3:
        if (gkSettleTime < mPart548.GetElapsedTimeFloat()) {
            mPart548.SetBoolProperty();
            ShowValidity();
            mState = 4;
        }
        return;

    case 4:
        if (gkHalf < mPart530.GetElapsedTimeFloat()) {
            mPart530.SetBoolProperty();
            mField508 = 1;
            mState = 5;
        }
        return;

    case 5:
        mField494 = mField498 * gkHalf;
        mDone = 0;
        mCancelled = 0;
        gPendingUpgrade = 1;
        PushUpgrade();
        mState = 6;
        return;

    case 6:
        if (UpdateA() && StepBack())
            mState = 8;
        return;

    case 8:
        if (gPendingUpgrade != 0) {
            AddCellUpgradeParts(mCell);
            gPendingUpgrade = 0;
        }
        if (UpdateC()) {
            RefreshLayout();
            mState = 7;
        }
        return;

    case 7:
        if (UpdateC()) {
            if (PushUpgrade()) {
                mState = 6;
            } else {
                mDone = 1;
                mState = 0;
            }
        }
        return;

    case 9:
        if (mCancelled != 0) {
            mDone = 1;
            mState = 0;
            return;
        }
        if (mUpgradeSlots.Count() == 0)
            AddCellUpgradeParts(mCell);
        if (UpdateB()) {
            mField450 = gkHoldTime;
            if (StepBack())
                mState = 11;
        }
        return;

    case 11:
        if (UpdateC()) {
            RefreshLayout();
            mState = 10;
        }
        return;

    case 10:
        if (UpdateC()) {
            if (Step()) {
                mState = 9;
            } else {
                mDone = 1;
                mState = 0;
            }
        }
        return;

    case 12:
        if (gkHalf < mPart510.GetElapsedTimeFloat()) {
            mPart510.SetBoolProperty();
            mField528 = 1;
            mState = 0;
        }
        return;
    }
}

// ---------------------------------------------------------------------------------------------
// 00e44d20: rebuild the validity match set for one editor cell kind: collect the cell's upgrade
// slots, add the cell's own fallback constraint when the list is short, then top the list up to
// 15 entries with template-DB queries (one to three rounds, depending on the cell kind).
// ---------------------------------------------------------------------------------------------
const int kMaxUpgradeParts = 15;

const int kCellUpgradeHead     = 0x1654c00;
const int kCellUpgradeHeadAlt  = 0x1654c01;
const int kCellUpgradeBody     = 0x1654c02;
const int kCellUpgradeLimb     = 0x1654c04;
const int kCellUpgradeCreature = 0x1654c05;

// @ 0x00e44d20
void EditorValidity::AddCellUpgradeParts(int cell)
{
    ConstraintNodeVector pending = { 0, 0, 0 };
    int rounds = 0;

    switch (cell) {
    case kCellUpgradeHead:
        CollectUpgradeHead(&mUpgradeSlots);
        if (mUpgradeSlots.Count() < kMaxUpgradeParts)
            pending.PushBack(Constraint(0x2dc9d1e, kEqualConstraint, 0xdfad9f51));
        rounds = 1;
        break;

    case kCellUpgradeHeadAlt:
        CollectUpgradeHead(&mUpgradeSlots);
        if (mUpgradeSlots.Count() < kMaxUpgradeParts)
            pending.PushBack(Constraint(0x2dc9d1e, kEqualConstraint, 0x9ea3031a));
        rounds = 1;
        break;

    case kCellUpgradeBody:
        CollectUpgradeBody(&mUpgradeSlots);
        if (mUpgradeSlots.Count() < kMaxUpgradeParts)
            pending.PushBack(Constraint(0x2dc9d1e, kEqualConstraint, 0x372e2c04));
        rounds = 2;
        break;

    case kCellUpgradeLimb:
        CollectUpgradeLimb(&mUpgradeSlots);
        if (mUpgradeSlots.Count() < kMaxUpgradeParts)
            pending.PushBack(Constraint(0x2dd90af, kEqualConstraint, 0x24682294));
        rounds = 3;
        break;

    case kCellUpgradeCreature:
        CollectUpgradeCreature(&mUpgradeSlots);
        if (mUpgradeSlots.Count() < kMaxUpgradeParts)
            pending.PushBack(Constraint(0x2dd90af, kEqualConstraint, 0x476a98c7));
        rounds = 3;
        break;

    default:
        return;
    }

    int missing = kMaxUpgradeParts - mUpgradeSlots.Count();
    for (int round = 0; round < rounds && round < missing; ++round) {
        pending.PushBack(Constraint(0x3cc89b1, kEqualConstraint, 0x913b23be));

        TemplateKeyVector keys = { 0, 0, 0 };
        gObjectTemplateDB->QueryMatchingParts(&keys, round, &pending);
        for (TemplateKey* pKey = keys.mpBegin; pKey != keys.mpEnd; ++pKey)
            mUpgradeSlots.PushBack(*pKey);

        // the cell's own fallback constraint is repeated on the first two rounds
        if (cell == kCellUpgradeBody) {
            if (round == 0)
                pending.PushBack(Constraint(0x2dc9d1e, kEqualConstraint, 0x372e2c04));
        } else if (cell == kCellUpgradeLimb) {
            if (round == 0)
                pending.PushBack(Constraint(0x2dc9d1e, kEqualConstraint, 0xccc35c46));
            else if (round == 1)
                pending.PushBack(Constraint(0x2dd90af, kEqualConstraint, 0x2399be55));
        } else if (cell == kCellUpgradeCreature) {
            if (round == 0)
                pending.PushBack(Constraint(0x2dc9d1e, kEqualConstraint, 0x65672ade));
            else if (round == 1)
                pending.PushBack(Constraint(0x2dd90af, kEqualConstraint, 0x2399be55));
        }
    }

    CommitUpgradeSlots();
}
