// Fight behaviour helpers of the SP "FIGHT" module (SP::`anonymous namespace' + the
// cTribeFightSlots pool).  Same translation unit as SP::FIGHT_Tick / TRIBE_FIGHT_Tick.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

#pragma intrinsic(asin)

namespace SP {

struct Vec3 { float x, y, z; };

// ---------------------------------------------------------------------------
// fight slot pool (global instance at 0x1583f5c)
// ---------------------------------------------------------------------------
struct SlotBody {
    uint32_t mBitmap;     // +0x00  bitmap of used sub-slots
    uint32_t mCount;      // +0x04  number of sub-slots
    uint32_t m0c;         // +0x08
    uint32_t m10;         // +0x0c
    int      mRefCount;   // +0x10
};

struct cTribeFightSlots {
    union {
        struct {
            uint32_t mIndex  : 30;   // +0x00  bits 0..29: slot index of the owner
            uint32_t mFlag30 : 1;    // +0x00  bit 30
            uint32_t mUsed   : 1;    // +0x00  bit 31: set while the slot is taken
        };
        uint32_t mFlags;             // +0x00  the whole flag word
    };
    SlotBody mBody;                  // +0x04
};

class cResizableObjectPoolT {
public:
    cTribeFightSlots* mpData;        // +0x00  (0x1583f5c)
    cTribeFightSlots* mpEnd;         // +0x04  (0x1583f60)
    uint32_t          pad08[3];      // +0x08
    int               mFreeIndex;    // +0x14
    int               mLastIndex;    // +0x18

    void GetObject(uint32_t id);     // 0xd66d60
    int  NextFree(int idx);          // 0xd660a0
};

extern cResizableObjectPoolT sTribeFightSlotsPool;

// ---------------------------------------------------------------------------
// spatial / loco sub-object embedded in every creature at +0xc0 (own vtable)
// ---------------------------------------------------------------------------
struct PtrRange { void** mpBegin; void** mpEnd; };  // returned by FUN_00c420d0

class Loco {
public:
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s10();
    virtual Vec3* GetPosition();                       // +0x2c
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21();
    virtual bool IsMoving();                           // +0x58
    virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26();
    virtual void s27(); virtual void s28();
    virtual float GetRadius();                         // +0x74

    PtrRange* GetNeighbourRange();                     // 0xc420d0
};

// spatial object handed out by cCombatant::GetSpatial()
class CombatSpatial : public Loco {
};

class cSPCreatureBase;

// ---------------------------------------------------------------------------
// objects living in the neighbour list of a creature
// ---------------------------------------------------------------------------
struct NeighbourEntry {
    float            mDistance;    // +0x00
    uint32_t         m04;          // +0x04
    cSPCreatureBase* mpCreature;   // +0x08
};

struct AbilityMask {
    uint32_t mBits[3];                              // +0x00
    bool IsValid(NeighbourEntry* e);                // SP::IsValidNeighbourEntry 0xc02600
};

struct NeighbourIter {
    NeighbourEntry** mpCur;                         // +0x00
    void SkipInvalid();                             // 0xb3d850
};

// ---------------------------------------------------------------------------
// behaviours
// ---------------------------------------------------------------------------
struct FightGroup {
    char        pad00[0x1a4];       // +0x00
    int         m1a4;               // +0x1a4
    bool        m1a8;               // +0x1a8
};

struct Behav {
    char        pad00[0x1d8];       // +0x00
    int         m1d8;               // +0x1d8
    char        pad1dc[0x600 - 0x1dc];
    FightGroup* mpGroup;            // +0x600
    void SetTargetFromGroup();      // 0xbcb430
};

struct CreatureStateFlags {
    uint32_t mBits0  : 8;   // +0x00  bits 0..7
    uint32_t mFlag8  : 1;   // +0x00  bit 8
    uint32_t mRest   : 23;
};

// ---------------------------------------------------------------------------
// the creature / citizen
// ---------------------------------------------------------------------------
struct TargetObj { char pad[0x578]; };   // opaque sub-object living at creature+0x5a8

class cSPCreatureBase {
public:
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual uint32_t GetTypeId();                      // +0x20
    virtual void s09(); virtual void s10();
    virtual bool IsDead();                             // +0x2c
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18();
    virtual int GetSpatialId();                        // +0x4c
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
    virtual void s28();
    virtual float GetRadius();                         // +0x74  (0xd66250)
    virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33();
    virtual void s34(); virtual void s35(); virtual void s36(); virtual void s37();
    virtual void s38(); virtual void s39(); virtual void s40(); virtual void s41();
    virtual void s42(); virtual void s43(); virtual void s44();
    virtual void* GetAbility(int idx);                 // +0xb4
    virtual cSPCreatureBase* GetByTypeHash(uint32_t hash);  // +0xb8
    virtual void s47();
    virtual bool CanReach(void* o, float a, float b);  // +0xc0

    char      pad004[0xc0 - 4];
    Loco      mLoco;                                   // +0xc0
    char      pad0c4[0x135 - 0xc4];
    uint8_t   mb135;                                   // +0x135
    char      pad136[0x5a8 - 0x136];
    TargetObj mTargetObj;                              // +0x5a8
    int       mB20;                                    // +0xb20
    char      padb24[0xb4c - 0xb24];
    Behav*    mpBehav;                                 // +0xb4c
    char      padb50[0xb58 - 0xb50];
    CreatureStateFlags mStateFlags;                    // +0xb58
    char      padb5c[0xb5e - 0xb5c];
    uint8_t   mB5E;                                    // +0xb5e
    char      padb5f[0x1124 - 0xb5f];
    NeighbourEntry** mNeighbourBegin;                  // +0x1124
    NeighbourEntry** mNeighbourEnd;                    // +0x1128

    int  GetTribe();                                   // 0xc22f50
    void* GetCombatTarget();                           // 0xc0ee60
    cSPCreatureBase* GetCombatTargetCreature();        // 0xc0ee90
    bool IsTribal();                                   // 0xc232c0
    bool CanBeFightTarget();                           // 0xc0b770
    int  GetFightState();                              // 0xc0c2f0
    struct SpeciesTraits* GetTraits();                 // 0xc0c1a0
    bool Flag388();                                    // 0xc0c0e0
    bool IsInRange(cSPCreatureBase* other);            // 0xc02eb0
    int  GetFightValue(cSPCreatureBase* other);        // 0xc0b8e0
    int  CheckRange(AbilityMask* mask, float range, int a, int b, int c,
                    int d, int e);                     // 0xc12410
};

typedef cSPCreatureBase cSPCreatureCitizen;

class cTribeFightSlotInfo {
public:
    int   m00;      // +0x00
    int   mSlot;    // +0x04
    int   m08;      // +0x08
    int   mCount;   // +0x0c
};

class cCombatant {
public:
    virtual void s00(); virtual void s01();
    virtual Loco* GetSpatial();                        // +0x08
    virtual cSPCreatureBase* GetCreature();            // +0x0c
    int GetDamageState();                              // 0x8e7f80
};

// ---------------------------------------------------------------------------
// fight memory block (retail layout)
// ---------------------------------------------------------------------------
struct RBNode { RBNode* mpLeft; RBNode* mpRight; RBNode* mpParent; uint8_t mColor; };
struct CooldownMap { int mCompare; RBNode mAnchor; int mSize; };   // 0x18 bytes

struct PropValue {
    union {
        float        f;      // +0x00
        const void*  p;      // +0x00
    } mPayload;
    uint32_t pad04[3];       // +0x04
    uint8_t  mFlags;         // +0x10
    uint8_t  pad11;
    uint16_t mType;          // +0x12
};

struct PropertyList {
    virtual void s0(); virtual void s1(); virtual void s2();
    virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6();
    virtual void s7(); virtual void s8();
    virtual bool GetProperty(uint32_t hash, PropValue** out);  // +0x24
};

class cCreatureModeStrategy { public: char pad[0xb4]; PropertyList* mpProps; };
extern cCreatureModeStrategy* g_CreatureModeStrategy;          // 0x169e294

struct SpeciesTraits { char pad[0x3f0]; int m3f0; short m3f4; };

struct FightMem {
    int      mTarget;               // +0x00
    float    mEvalTimer;            // +0x04
    float    mMoveTimer;            // +0x08
    float    mNoActivityTimer;      // +0x0c
    float    mMaxRange;             // +0x10
    float    mAbilityTimer;         // +0x14
    int      mState;                // +0x18
    float    mDistance;             // +0x1c
    int      m20;                   // +0x20
    short    mStandardAttackCounter;// +0x24
    char     pad26[2];
    cSPCreatureBase* mpCreature;    // +0x28
    int      m2c;                   // +0x2c
    int      mAttackAnim;           // +0x30
    int      m34;                   // +0x34
    int      mFrustrationAnim;      // +0x38
    int      m3c;                   // +0x3c
    float    m40;                   // +0x40
    bool     m44;                   // +0x44
    char     pad45[0x48 - 0x45];
    void*    mp48;                  // +0x48
    short    m4c;                   // +0x4c
    bool     m4e;                   // +0x4e
    bool     mbAttackOnSight;       // +0x4f
    float    m50;                   // +0x50
    float    m54;                   // +0x54
    float    m58;                   // +0x58
    float    m5c;                   // +0x5c
    int      m60;                   // +0x60
    CooldownMap mCooldowns;         // +0x64
    bool     m44b;                  // +0x7c

    FightMem* Init(cSPCreatureBase* c);   // 0xd66e70
    void Release();                       // 0xd670e0
};

// ---------------------------------------------------------------------------
// externals
// ---------------------------------------------------------------------------
extern unsigned char DAT_01582df5;  // byte passed to the range query
extern int   DAT_01582ee8;          // default behaviour flags
extern int   DAT_0147bc04;          // 31 (hard cap of slots)
extern float DAT_0147bc0c;          // FLT_MAX
extern float DAT_01473c70;          // 10.0f
extern float DAT_01470f1c;          // 2.0f
extern float DAT_015d9c6c;          // 0.0f
extern float DAT_01485544;          // 0.75f
extern float DAT_0169ed08;          // arc constant used by the slot estimate
extern PropertyList* g_GamePropertyList;   // 0x1581288

int    FUN_00c02eb0_unused();
void   FUN_00d65500(int arg);
float  FUN_00d38a30(int which, cSPCreatureBase* c);
cSPCreatureBase* FUN_00d99500(void* obj);
void*  FUN_00ae3390(void* p);
extern "C" float __cdecl _CIasin(float x);
float  DistanceBetweenBodies(const Vec3* a, float rA, const Vec3* b, float rB, bool clamp);
float  GetPropertyT_float(PropertyList* props, uint32_t hash, float def);
uint32_t GetPropertyAsUint32(PropertyList* props, uint32_t hash, uint32_t* out);

template <class T> static const T& MinRef(const T& a, const T& b) { return (a < b) ? a : b; }
template <class T> static const T& MaxRef(const T& a, const T& b) { return (a > b) ? a : b; }

static void CopySlotBody(SlotBody* dst, const SlotBody* src)
{
    if (dst)
        *dst = *src;
}

// ---------------------------------------------------------------------------
// slot pool helpers
// ---------------------------------------------------------------------------
// @ 0x00d66320
SlotBody* GetFightSlotBody(uint32_t id)
{
    uint32_t count = (uint32_t)(sTribeFightSlotsPool.mpEnd - sTribeFightSlotsPool.mpData);
    id &= 0xbfffffff;
    if (id < count) {
        bool used = sTribeFightSlotsPool.mpData[id].mUsed;
        if (!used)
            return &sTribeFightSlotsPool.mpData[id].mBody;
    }
    return 0;
}

// @ 0x00d661a0
cTribeFightSlots* CopyFightSlots(cTribeFightSlots* first, cTribeFightSlots* last,
                                 cTribeFightSlots* dst)
{
    for (; first != last; ++first, ++dst) {
        if (dst) {
            dst->mFlags = first->mFlags;
            bool used = first->mUsed;
            if (!used && &dst->mBody)
                CopySlotBody(&dst->mBody, &first->mBody);
        }
    }
    return dst;
}

// @ 0x00d66250
void ComputeFightSlot(cTribeFightSlotInfo* out, cSPCreatureBase* c, float dist)
{
    uint32_t maxSlots = 0x1f;
    if (c) {
        cSPCreatureBase* sub = c->GetByTypeHash(0x4f176642);
        if (sub && sub->IsTribal()) {
            GetPropertyAsUint32(g_GamePropertyList, 0x816289e0, &maxSlots);
            if (maxSlots > 0x1f)
                maxSlots = (uint32_t)DAT_0147bc04;
        }
    }
    float radius = c->GetRadius();
    float t = DAT_0169ed08 / (2.0f * asin(dist / (radius + dist)));
    int n = (int)floorf(t);
    out->mSlot = MinRef(n, (int)maxSlots);
    out->mCount = n;
}

// @ 0x00d66370
bool GetFightSlots(cSPCreatureBase* /*c*/, int* pSlot, uint32_t id)
{
    SlotBody* b = GetFightSlotBody(id);
    if ((uint32_t)*pSlot < b->mCount && (b->mBitmap & (1u << *pSlot)) != 0)
        return true;
    *pSlot = -1;
    for (uint32_t i = 0; i < b->mCount; ++i) {
        uint32_t bit = 1u << i;
        if ((b->mBitmap & bit) == 0) {
            *pSlot = i;
            b->mBitmap |= bit;
            return true;
        }
    }
    return false;
}

// @ 0x00d66400
NeighbourEntry* FindNeighbourEntry(cSPCreatureBase* c, cSPCreatureBase* exclude)
{
    if (!exclude)
        return 0;
    if (c->GetFightState() != 2)
        return 0;

    Loco* myLoco = &c->mLoco;
    Vec3* myPos = myLoco->GetPosition();
    float myRadius = myLoco->GetRadius();

    AbilityMask mask;
    mask.mBits[0] = 0xffffffff;
    mask.mBits[1] = 0xffffffff;
    mask.mBits[2] = 0x00ffffff;

    float dist = DistanceBetweenBodies(myPos, myRadius, exclude->mLoco.GetPosition(),
                                       exclude->mLoco.GetRadius(), true);
    if (c->CheckRange(&mask, dist, 0, 0, DAT_01582df5, 0, 0) != -1)
        return 0;

    NeighbourEntry* best = 0;
    NeighbourEntry** end = c->mNeighbourEnd;
    NeighbourIter it;
    it.mpCur = c->mNeighbourBegin;
    if (it.mpCur != end && !mask.IsValid(*it.mpCur))
        it.SkipInvalid();
    if (it.mpCur == end)
        return best;

    for (;;) {
        NeighbourEntry* e = *it.mpCur;
        cSPCreatureBase* cand = e->mpCreature;
        if (cand && cand->GetTypeId() == 0x18eb4b7 && cand != exclude && cand->mB5E == 0
            && cand->CanBeFightTarget() && cand->GetCombatTarget() == (void*)&c->mTargetObj) {
            float d = DistanceBetweenBodies(myPos, myRadius, cand->mLoco.GetPosition(),
                                            cand->mLoco.GetRadius(), true);
            if (dist > d) {
                dist = d;
                best = e;
            }
        }
        do {
            ++it.mpCur;
            if (it.mpCur == end)
                return best;
        } while (!mask.IsValid(*it.mpCur));
    }
}

// @ 0x00d66600
cSPCreatureBase* FindNeighbourCreature(cSPCreatureBase* c, cSPCreatureBase* tgt)
{
    if (!tgt)
        return 0;
    if (c->GetCombatTargetCreature() == tgt)
        return 0;
    if (c->mpBehav->m1d8 != 0x02d852e6)
        return 0;

    NeighbourEntry** end = tgt->mNeighbourEnd;
    AbilityMask mask;
    mask.mBits[0] = 0xffffffff;
    mask.mBits[1] = 0xffffffff;
    mask.mBits[2] = 0x00ffffff;
    NeighbourIter it;
    it.mpCur = tgt->mNeighbourBegin;
    if (it.mpCur == end)
        return 0;
    if (!mask.IsValid(*it.mpCur))
        it.SkipInvalid();
    if (it.mpCur == end)
        return 0;

    for (;;) {
        NeighbourEntry* e = *it.mpCur;
        if (e->mDistance > FUN_00d38a30(5, tgt))
            return 0;
        cSPCreatureBase* cand = e->mpCreature;
        if (cand) {
            cSPCreatureBase* o = cand->GetByTypeHash(0xd0036e08);
            if (o && o != c && cand->mB5E == 0 && tgt->IsInRange(o) && c->GetFightValue(o) > 0)
                return o;
        }
        do {
            ++it.mpCur;
            if (it.mpCur == end)
                return 0;
        } while (!mask.IsValid(*it.mpCur));
    }
}

// @ 0x00d669c0
TargetObj* CheckForNewTarget(cSPCreatureCitizen* me, cCombatant* target, int tribe)
{
    bool fighting = (target->GetDamageState() == 2);
    bool moving = me->mLoco.IsMoving();
    if (!moving && me->GetFightState() < 2 && !fighting)
        return 0;

    Loco* myLoco = &me->mLoco;
    Loco* tgtSpatial = target->GetSpatial();
    Vec3* myPos = myLoco->GetPosition();
    float myRadius = myLoco->GetRadius();

    float maxDist = DAT_0147bc0c;
    if (!fighting) {
        float d = DistanceBetweenBodies(myPos, myRadius, tgtSpatial->GetPosition(),
                                        tgtSpatial->GetRadius(), true);
        AbilityMask mask;
        mask.mBits[0] = 0xffffffff;
        mask.mBits[1] = 0xffffffff;
        mask.mBits[2] = 0x00ffffff;
        if (me->CheckRange(&mask, d, 0, 0, DAT_01582df5, 0, 0) != -1)
            return 0;
        maxDist = d * DAT_01485544;
    }

    TargetObj* best = 0;
    int myTribe = me->GetTribe();
    PtrRange* range = myLoco->GetNeighbourRange();
    void** it = range->mpBegin;
    void** end = range->mpEnd;

    cSPCreatureBase* animal = target->GetCreature();
    if (animal && animal->GetTypeId() != 0x18eb4b7)
        animal = 0;
    cSPCreatureBase* citizen = target->GetCreature();
    if (citizen && citizen->GetTypeId() != 0x18eb45e)
        citizen = 0;

    if (animal) {
        for (; it != end; ++it) {
            cSPCreatureBase* c = 0;
            if (*it)
                c = ((cSPCreatureBase*)*it)->GetByTypeHash(0x4f176642);
            if (c) {
                if (!c->IsDead() && c->mb135 && c->mB5E == 0 && c->GetTribe() == tribe
                    && c->CanBeFightTarget()) {
                    float d = DistanceBetweenBodies(myPos, myRadius, c->mLoco.GetPosition(),
                                                    c->mLoco.GetRadius(), true);
                    if (maxDist > d) {
                        maxDist = d;
                        best = &c->mTargetObj;
                    }
                }
            }
        }
        return best;
    }

    if (citizen) {
        int wanted = citizen->mB20;
        int myId = me->GetSpatialId();
        for (; it != end; ++it) {
            void* o = 0;
            if (*it)
                o = ((cSPCreatureBase*)*it)->GetByTypeHash(0xd0036e08);
            cSPCreatureBase* c = FUN_00d99500(o);
            if (c && c->mB20 == wanted && c->GetSpatialId() != myId
                && c->mpBehav->m1d8 == 0x02d852e6) {
                cSPCreatureCitizen* cit = (cSPCreatureCitizen*)FUN_00ae3390(c->GetCombatTarget());
                if (cit && cit->IsTribal() && cit->GetTribe() == myTribe) {
                    float d = DistanceBetweenBodies(myPos, myRadius, c->mLoco.GetPosition(),
                                                    c->mLoco.GetRadius(), true);
                    if (maxDist > d) {
                        maxDist = d;
                        best = &c->mTargetObj;
                    }
                }
            }
        }
    }
    return best;
}

// @ 0x00d66d60
void cResizableObjectPoolT::GetObject(uint32_t id)
{
    id &= 0xbfffffff;
    cTribeFightSlots* s = mpData + id;
    s->mIndex = mLastIndex;
    s->mUsed = 1;
    mLastIndex = id;
    if (mFreeIndex == (int)id)
        mFreeIndex = NextFree((int)id);
}

// @ 0x00d66db0
void ReleaseFightSlot(uint32_t id)
{
    SlotBody* b = GetFightSlotBody(id);
    if (b) {
        if (--b->mRefCount == 0)
            sTribeFightSlotsPool.GetObject(id);
    }
}

// @ 0x00d66e10
void FUN_00d66e10(cSPCreatureBase* c, uint32_t slot)
{
    FightGroup* g = c->mpBehav->mpGroup;
    if (g) {
        SlotBody* b = GetFightSlotBody(g->m1a4);
        if (slot < b->mCount)
            b->mBitmap &= ~(1u << slot);
        ReleaseFightSlot(g->m1a4);
    }
    c->mpBehav->SetTargetFromGroup();
}

// @ 0x00d66e70
FightMem* FightMem::Init(cSPCreatureBase* c)
{
    m20 = 0;
    mCooldowns.mAnchor.mpRight = 0;
    mCooldowns.mAnchor.mpParent = 0;
    mCooldowns.mAnchor.mColor = 0;
    mCooldowns.mAnchor.mpLeft = &mCooldowns.mAnchor;
    mCooldowns.mAnchor.mpRight = &mCooldowns.mAnchor;
    mCooldowns.mSize = 0;
    mStandardAttackCounter = 0;
    m5c = 0.0f;
    m60 = -1;
    m58 = 0.0f;
    mTarget = -1;
    mEvalTimer = 0.0f;
    mMoveTimer = 0.0f;
    mNoActivityTimer = 0.0f;
    mMaxRange = DAT_0147bc0c;
    mState = 0;
    mDistance = 0.0f;
    mpCreature = c;
    m2c = c->mStateFlags.mFlag8 ? 0x20 : DAT_01582ee8;
    mAttackAnim = 0;
    m34 = 0;
    mFrustrationAnim = 0;
    m4c = 1;
    m4e = false;
    m3c = 0;
    m40 = 0.0f;
    mp48 = c->GetTraits();
    if (mp48) {
        m4c = ((SpeciesTraits*)mp48)->m3f4;
        m2c = ((SpeciesTraits*)mp48)->m3f0;
    }
    if (c->Flag388())
        m4e = true;

    mAbilityTimer = GetPropertyT_float(g_CreatureModeStrategy->mpProps,
                                      0x6848e35e + (c->Flag388() ? 0xe365473b : 0),
                                      DAT_01473c70);

    PropValue* pv;
    float propA;
    if (!g_CreatureModeStrategy->mpProps ||
        !g_CreatureModeStrategy->mpProps->GetProperty(0x9224aa67, &pv))
        propA = DAT_01470f1c;
    else if (pv->mType == 0xd || pv->mType == 0x10) {
        if (pv->mFlags & 0x30)
            propA = *(const float*)pv->mPayload.p;
        else
            propA = pv->mPayload.f;
    } else
        propA = DAT_015d9c6c;

    float propB;
    if (!g_CreatureModeStrategy->mpProps ||
        !g_CreatureModeStrategy->mpProps->GetProperty(0x8fc666ce, &pv))
        propB = DAT_01470f1c;
    else if (pv->mType == 0xd || pv->mType == 0x10) {
        if (pv->mFlags & 0x30)
            propB = *(const float*)pv->mPayload.p;
        else
            propB = pv->mPayload.f;
    } else
        propB = DAT_015d9c6c;

    m50 = MaxRef(FUN_00d38a30(1, c), propB);
    m54 = MaxRef(FUN_00d38a30(2, c), propA);
    mbAttackOnSight = false;
    return this;
}

// @ 0x00d670e0
void FightMem::Release()
{
    cSPCreatureBase* c = mpCreature;
    FightGroup* g = c->mpBehav->mpGroup;
    if (g) {
        if (g->m1a8 && mState == 1)
            FUN_00d65500(0);
        FUN_00d66e10(c, mTarget);
        mTarget = -1;
    }
    mMaxRange = mAbilityTimer;
    mState = 0;
    mMoveTimer = 0.0f;
    mNoActivityTimer = 0.0f;
}

} // namespace SP
