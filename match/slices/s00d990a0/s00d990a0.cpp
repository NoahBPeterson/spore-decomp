// Slice s00d990a0: citizen-tree behaviour helpers (extinguish-building tick, stimulus
// filtering/selection, behaviour_stimuli record assignment, planet-surface projection maths).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
// Layouts: cSPCreatureBase (mLocomotive +0xc0, cCombatant +0x120, mB135, mB5a8, anim +0xb4c,
// flags byte +0xb58, mB5e, action tree +0xfb8), cActionCircle stride 0x64 with its position at
// +0x14 and the slot container at +0x50/+0x54, XformMsg (flags/count, position +0x04, matrix
// +0x14, size 0x38), behaviour_stimuli size 0x28.
#include "types.h"
#include <math.h>

#define VSLOT(n) virtual void _v##n();

// ---------------------------------------------------------------------------
// value types
// ---------------------------------------------------------------------------
struct Vector3 {
    float x, y, z;
};

struct Matrix3 {
    float m[3][3];
};

// Transform message posted to the effect system (0x00434040 ctor).
struct XformMsg {
    uint16_t mnFlags;       // +0x00
    uint16_t mnVersion;     // +0x02
    Vector3 mPos;           // +0x04
    uint32_t mnPad10;       // +0x10
    Matrix3 mMatrix;        // +0x14
    XformMsg();             // 0x00434040
};

void normalized_safe(Vector3* pOut, const Vector3* pIn);              // 0x00449c20
void Matrix3FromQuaternion(Matrix3* pOut, const void* pQuat);         // 0x0059c190

// ---------------------------------------------------------------------------
// effects
// ---------------------------------------------------------------------------
class IVisualEffect {
public:
    VSLOT(0) VSLOT(1)
    virtual bool Start(int32_t nFlags);                               // +0x08
    VSLOT(3) VSLOT(4) VSLOT(5)
    virtual void SetTransform(const XformMsg* pMsg);                  // +0x18
};

template <class T>
class AutoRefCount {
public:
    T** AsPPTypeParam();                                              // 0x00a16f40
    T* mpObject;                                                      // +0x00
};

class cIEffectsManager {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8) VSLOT(9)
    VSLOT(10)
    virtual bool CreateVisualEffect(uint32_t nID, int32_t nFlags, IVisualEffect** ppOut);  // +0x2c
};
cIEffectsManager* EffectsManagerPtr();                                // 0x0067ddd0

// ---------------------------------------------------------------------------
// planet
// ---------------------------------------------------------------------------
class cPlanetModel;
cPlanetModel* PlanetModel();                                          // 0x00b3d350

class cPlanetModel {
public:
    float GetWaterHeight();                                           // 0x00b7e390
    // writes the surface orientation of a position into pOut and returns it.
    Vector3* BuildSurfaceOrientation2(Vector3* pOut, const Vector3* pDir,
                                      Vector3* pUp);                  // 0x00b7f250
    Vector3 DirectionToSurfacePosition(const Vector3& pos);           // 0x00b815a0
    Vector3 SnapToSurface(const Vector3& pos);                        // 0x00b81630
};

// ---------------------------------------------------------------------------
// creature
// ---------------------------------------------------------------------------
class cCreatureStatus {
public:
    uint8_t mOpaque[0x75];
    bool mIsAlive;                                                    // +0x75
};

class cCreatureOwner {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8) VSLOT(9)
    VSLOT(10)
    virtual bool IsUnavailable();                                     // +0x2c
};

class cLocomotiveObject {
public:
    bool IsNearGoal();                                                // 0x00c42e20
    uint8_t mOpaque[0x60];
};

class cCombatant {
public:
    int32_t GetDamageState();                                         // 0x008e7f80 (reads +0x34)
    uint8_t mOpaque[0x15];                                            // +0x00 .. +0x14
};

class cAnimState {
public:
    uint8_t mPad00[8];
    float mfProgress;                                                 // +0x08
};

class cAnimationPlayer {
public:
    cAnimState* Play(uint32_t nAnimID, uint32_t nFlags);              // 0x00bc96a0
};

// animation component hung off cSPCreatureBase::mB4c; the player is its second base.
class cAnimation {
public:
    uint8_t mPad00[8];
    cAnimationPlayer mPlayer;                                         // +0x08
};

class cActionSlot {
public:
    uint32_t mField00;                                                // +0x00
    void* mpField04;                                                  // +0x04
    uint8_t mPad08[4];
    Vector3 mPos;                                                     // +0x0c
};

class cActionCircle {
public:
    uint8_t mPad00[0x14];
    Vector3 mPos;                                                     // +0x14
    uint8_t mPad20[0x30];                                             // +0x20 .. +0x4f
    cActionSlot* mpBegin;                                             // +0x50
    cActionSlot* mpEnd;                                               // +0x54
    uint8_t mPad58[0x0c];                                             // +0x58 .. +0x63
    cActionSlot* SlotAt(uint32_t nIndex);                             // 0x00af9ff0
};

// action tree at cSPCreatureBase::mFB8.
class cCreatureTree {
public:
    uint8_t mPad000[0x220];
    cActionCircle* mpCircles;                                         // +0x220
};

class cSPCreatureBase {
public:
    VSLOT(0) VSLOT(1)
    virtual cCreatureStatus* GetStatus();                             // +0x08
    virtual cCreatureOwner* GetOwner();                               // +0x0c
    VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7)
    virtual uint32_t GetTypeID();                                     // +0x20
    VSLOT(9) VSLOT(10)
    virtual bool IsUnavailable();                                     // +0x2c

    int32_t GetDamageState();                                         // 0x008e7f80 (reads +0x34)
    bool AnimationFinished(int32_t nFlags);                           // 0x00c123f0
    void PlayAnimation(uint32_t nAnimID, int32_t nLoops, int32_t nFlags);  // 0x00c12190

    uint8_t mPad04[0x30];                                             // +0x04 .. +0x33
    int32_t mnDamageState;                                            // +0x34
    float mf38;                                                       // +0x38
    uint8_t mPad3c[0x84];                                             // +0x3c .. +0xbf
    cLocomotiveObject mLocomotive;                                    // +0xc0
    cCombatant mCombatant;                                            // +0x120
    bool mB135;                                                       // +0x135
    uint8_t mPad136[0x472];                                           // +0x136 .. +0x5a7
    uint8_t mB5a8;                                                    // +0x5a8
    uint8_t mPad5a9[0x5a3];                                           // +0x5a9 .. +0xb4b
    cAnimation* mB4c;                                                 // +0xb4c
    uint8_t mPadB50[8];                                               // +0xb50 .. +0xb57
    uint8_t mB58;                                                     // +0xb58 (flags)
    uint8_t mPadB59[5];                                               // +0xb59 .. +0xb5d
    bool mB5e;                                                        // +0xb5e
    uint8_t mPadB5f[0x459];                                           // +0xb5f .. +0xfb7
    cCreatureTree* mFB8;                                              // +0xfb8
};

void* CastCreature(void* pObject, uint32_t nTypeID);                  // 0x00ac80d0
void* ResolveObject(void* pObject);                                   // 0x00f19200
cSPCreatureBase* AsCreature(void* pObject);                           // 0x00c0c380

// ---------------------------------------------------------------------------
// stimulus context ("behavior input" record whose +0x2c is the stimulus source)
// ---------------------------------------------------------------------------
class cStimulusSource {
public:
    VSLOT(0) VSLOT(1) VSLOT(2)
    virtual cSPCreatureBase* FindObject(uint32_t nStimulusID);        // +0x0c
};

struct cStimulusContext {
    uint8_t mPad00[0x2c];
    cStimulusSource* mpSource;                                        // +0x2c
};

// ---------------------------------------------------------------------------
// behaviour_stimuli family
// ---------------------------------------------------------------------------
// Attribute interfaces: the reference counted members sit at different vtable slots.
class cStimulusAttrA {
public:
    VSLOT(0)
    VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8) VSLOT(9) VSLOT(10)
    VSLOT(11) VSLOT(12) VSLOT(13) VSLOT(14) VSLOT(15) VSLOT(16) VSLOT(17) VSLOT(18) VSLOT(19)
    VSLOT(20) VSLOT(21) VSLOT(22) VSLOT(23)
    virtual int32_t AddRef();                                         // +0x60
    virtual int32_t Release();                                        // +0x64
};

class cStimulusAttrB {
public:
    virtual int32_t AddRef();                                         // +0x00
    virtual int32_t Release();                                        // +0x04
};

class cStimulusAttrC {
public:
    VSLOT(0)
    virtual int32_t AddRef();                                         // +0x04
    virtual int32_t Release();                                        // +0x08
};

template <class T>
class IntrusivePtr {
public:
    IntrusivePtr& operator=(T* p)
    {
        T* const pOld = mpObject;
        if (p != pOld) {
            if (p)
                p->AddRef();
            mpObject = p;
            if (pOld)
                pOld->Release();
        }
        return *this;
    }
    T* mpObject;                                                      // +0x00
};

// defaults handed out by behavior_stimuli::GetAny (rdata block at 0x0169f2a4).
extern Vector3 gStimulusDefaultVec;

// nSPBehaviorTree::behavior_stimuli (0x28).
struct behavior_stimuli {
    int32_t mStimulusID;                                              // +0x00
    int32_t mField04;                                                 // +0x04
    int32_t mDuration;                                                // +0x08
    Vector3 mOffset;                                                  // +0x0c
    int32_t mField18;                                                 // +0x18
    int32_t mField1c;                                                 // +0x1c
    int32_t mField20;                                                 // +0x20
    float mf24;                                                       // +0x24

    behavior_stimuli& GetAny();                                       // 0x00d997e0
};

// Reflected stimulus record: the three attribute pointers are declared in the order the
// original assigns them (attribute A at +0x04, B at +0x08, C at +0x00).
struct sStimulusRecord {
    cStimulusAttrC* mpC;                                              // +0x00
    cStimulusAttrA* mpA;                                              // +0x04
    cStimulusAttrB* mpB;                                              // +0x08
    Vector3 mOffset;                                                  // +0x0c
    int32_t mField18;                                                 // +0x18
    int32_t mField1c;                                                 // +0x1c
    int32_t mField20;                                                 // +0x20
    float mf24;                                                       // +0x24
};

// Assignment destination: same body plus the trailing float the tick helper zeroes.
struct sStimulusAssignment {
    IntrusivePtr<cStimulusAttrA> mpA;                                 // +0x00
    IntrusivePtr<cStimulusAttrB> mpB;                                 // +0x04
    IntrusivePtr<cStimulusAttrC> mpC;                                 // +0x08
    Vector3 mOffset;                                                  // +0x0c
    int32_t mField18;                                                 // +0x18
    int32_t mField1c;                                                 // +0x1c
    int32_t mField20;                                                 // +0x20
    float mf24;                                                       // +0x24
    float mf28;                                                       // +0x28
};

// Flat 0x28 stimulus description used by the plain (non ref-counting) copy.
struct sStimulusFlat {
    uint32_t mField00;                                                // +0x00
    uint32_t mField04;                                                // +0x04
    uint32_t mField08;                                                // +0x08
    Vector3 mOffset;                                                  // +0x0c
    uint32_t mField18;                                                // +0x18
    uint32_t mField1c;                                                // +0x1c
    uint32_t mField20;                                                // +0x20
    float mf24;                                                       // +0x24
};

struct sStimulusRotated {
    uint32_t mFieldSrc08;                                             // +0x00
    uint32_t mFieldSrc00;                                             // +0x04
    uint32_t mFieldSrc04;                                             // +0x08
    Vector3 mOffset;                                                  // +0x0c
    uint32_t mField18;                                                // +0x18
    uint32_t mField1c;                                                // +0x1c
    uint32_t mField20;                                                // +0x20
    float mf24;                                                       // +0x24
};

void AssignStimulus(const sStimulusRecord* pSrc, sStimulusAssignment* pDst);  // 0x00d99730

// ---------------------------------------------------------------------------
// misc helpers used by the slice
// ---------------------------------------------------------------------------
class cTreeNode {
public:
    uint32_t GetID();                                                 // 0x00c0ee60 (reads +0xe7c)
    uint8_t mOpaque[0xe80];
};

struct cTreeRing {
    cTreeNode* mpNodes[1];                                            // +0x00
    uint8_t mPad04[0x10];                                             // +0x04 .. +0x13
    uint32_t mnIndex;                                                 // +0x14
};

uint32_t SlotOwnerID(cActionSlot* pSlot);                             // 0x00fcc210 (reads +0x04)

struct cStreamSub {
    uint8_t mOpaque[0x70];
};

struct cStreamSlot {
    uint8_t mPad00[0x10];                                             // +0x00 .. +0x0f
    int32_t mNodeIndex;                                               // +0x10
    uint8_t mPad14[0x28];                                             // +0x14 .. +0x3b
    cStreamSub mSub;                                                  // +0x3c
};

struct cStreamTable {
    cStreamSlot mSlots[1];                                            // stride 0xac
};

void UpdateStream(void* pStream, float fDelta);                       // 0x00d98140
bool HasDamage(void* pCombatant);                                     // 0x00d91360

cStreamSub* GetSlotSub(cStreamTable* pTable, uint32_t nIndex);

// spatial bodies used by the distance helpers
class cSpatialObject {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8) VSLOT(9)
    VSLOT(10)
    virtual Vector3* GetPosition(float fT);                           // +0x2c
    VSLOT(12) VSLOT(13) VSLOT(14) VSLOT(15) VSLOT(16) VSLOT(17) VSLOT(18) VSLOT(19) VSLOT(20)
    VSLOT(21) VSLOT(22) VSLOT(23) VSLOT(24) VSLOT(25) VSLOT(26) VSLOT(27) VSLOT(28)
    virtual float GetRadius(const Vector3* pToward);                  // +0x74

    uint8_t mPad04[0x4c];                                             // +0x04 .. +0x4f
    uint32_t mFlags50;                                                // +0x50
};

float DistanceBetweenBodies(const Vector3* pA, float fRadiusA, const Vector3* pB,
                            float fRadiusB, bool bClamp);              // 0x00d99a60
float RecursiveSurfaceProbe(const Vector3* pFrom, const Vector3* pDir, float fLow,
                            float fHigh);                              // 0x00d99cd0

// The third parameter travels in the pointer block (12-byte float/double area + one
// pushed dword per remaining argument), so it is declared as a pointer-sized word.
void WalkTree(float fA, double dB, void* pC, void* pD, void* pE, void* pF, void* pG,
              void* pH);                                              // 0x00bc8ff0

// ===========================================================================
// 0x00d990a0: extinguish-building behaviour tick
// ===========================================================================
struct sExtinguishStep {
    uint32_t mnState;                                                 // +0x00
    uint32_t mnSlotIndex;                                             // +0x04
    uint32_t mnAnimIndex;                                             // +0x08
    cSPCreatureBase* mpCreature;                                      // +0x0c
    AutoRefCount<IVisualEffect> mEffect;                              // +0x10
};

// @ 0x00d990a0
bool ExtinguishBuilding_Tick(cSPCreatureBase* pCreature, void* p2, void* p3, void* p4, void* p5,
                             sExtinguishStep* pStep, void* p7, float fDelta)
{
    if (pStep->mpCreature->IsUnavailable())
        return false;
    if (pStep->mpCreature->mCombatant.GetDamageState() == 2)
        return false;

    switch (pStep->mnState) {
    case 0:
        if (pCreature->mLocomotive.IsNearGoal()) {
            pStep->mnState = 1;
            return true;
        }
        break;

    case 1: {
        cActionCircle* pCircle = &pCreature->mFB8->mpCircles[pStep->mnSlotIndex];
        cActionSlot* pSlot = pCircle->SlotAt(pStep->mnAnimIndex == 0);
        cSPCreatureBase* pTarget = AsCreature((void*)SlotOwnerID(pSlot));
        if (pTarget != 0 && pTarget->mLocomotive.IsNearGoal()) {
            pStep->mnState = 2;
            pCreature->PlayAnimation(pStep->mnAnimIndex * 3 + 0x5305141, 1, -1);
            if (pStep->mnAnimIndex == 0) {
                if (EffectsManagerPtr()->CreateVisualEffect(0x3b2cc158, 0,
                                                            pStep->mEffect.AsPPTypeParam())) {
                    cActionCircle* pSource = &pCreature->mFB8->mpCircles[pStep->mnSlotIndex];
                    cActionSlot* pOne = pSource->SlotAt(1);
                    cActionSlot* pZero = pSource->SlotAt(0);
                    Vector3 mid;
                    mid.x = (pZero->mPos.x + pOne->mPos.x) * 0.5f;
                    mid.y = (pZero->mPos.y + pOne->mPos.y) * 0.5f;
                    mid.z = (pZero->mPos.z + pOne->mPos.z) * 0.5f;
                    Vector3 delta;
                    delta.x = pSource->mPos.x - mid.x;
                    delta.y = pSource->mPos.y - mid.y;
                    delta.z = pSource->mPos.z - mid.z;
                    Vector3 dir;
                    normalized_safe(&dir, &delta);
                    XformMsg xf;
                    xf.mnFlags |= 4;
                    xf.mnVersion += 1;
                    xf.mPos = mid;
                    Vector3 up;
                    Vector3* pQuat = PlanetModel()->BuildSurfaceOrientation2(&dir, &mid, &up);
                    Matrix3 mtx;
                    Matrix3FromQuaternion(&mtx, pQuat);
                    xf.mMatrix = mtx;
                    xf.mnFlags |= 2;
                    xf.mnVersion += 1;
                    pStep->mEffect.mpObject->SetTransform(&xf);
                    pStep->mEffect.mpObject->Start(0);
                }
            }
        }
        break;
    }

    case 2:
        if (pCreature->AnimationFinished(0)) {
            pStep->mnState = 3;
            pCreature->PlayAnimation(pStep->mnAnimIndex * 3 + 0x5305142, 1, -1);
            return true;
        }
        break;

    case 3:
        if (pStep->mnAnimIndex == 0)
            UpdateStream(pStep, fDelta);
        if (pCreature->AnimationFinished(0)) {
            cCombatant* pCombatant =
                pStep->mpCreature ? &pStep->mpCreature->mCombatant : (cCombatant*)0;
            if (HasDamage(pCombatant)) {
                pCreature->PlayAnimation(pStep->mnAnimIndex * 3 + 0x5305142, 1, -1);
            } else {
                pStep->mnState = 4;
                pCreature->PlayAnimation(pStep->mnAnimIndex * 3 + 0x5305143, 1, -1);
            }
            return true;
        }
        break;

    case 4:
        if (pCreature->AnimationFinished(0))
            return false;
        break;
    }
    return true;
}

// ===========================================================================
// 0x00d99420: slot lookup in the 0xac-byte stream table
// ===========================================================================
// @ 0x00d99420
cStreamSub* GetSlotSub(cStreamTable* pTable, uint32_t nIndex)
{
    cStreamSlot* pSlot = &pTable->mSlots[nIndex];
    if (pSlot->mNodeIndex == -1)
        return 0;
    return &pSlot->mSub;
}

// ===========================================================================
// 0x00d99470: creature usable for the extinguish behaviour and flagged as a building
// ===========================================================================
// @ 0x00d99470
cSPCreatureBase* ExtinguishTarget(cSPCreatureBase* pCreature)
{
    if (pCreature != 0 && !pCreature->mB5e && pCreature->mB135 &&
        !pCreature->IsUnavailable()) {
        if (CastCreature(pCreature, 0x18eb45e) == 0 || (pCreature->mB58 & 4) == 0)
            return pCreature;
    }
    return 0;
}

// ===========================================================================
// 0x00d994c0: same filter keeping only type 0x18eb4b7
// ===========================================================================
// @ 0x00d994c0
cSPCreatureBase* FireTarget(cSPCreatureBase* pCreature)
{
    if (pCreature != 0 && pCreature->GetTypeID() == 0x18eb4b7 && !pCreature->mB5e &&
        pCreature->mB135 && !pCreature->IsUnavailable())
        return pCreature;
    return 0;
}

// ===========================================================================
// 0x00d99500: same filter for type 0x18eb45e with the extra flag-bit test
// ===========================================================================
// @ 0x00d99500
cSPCreatureBase* BuildingTarget(cSPCreatureBase* pCreature)
{
    if (pCreature != 0 && pCreature->GetTypeID() == 0x18eb45e && !pCreature->mB5e &&
        pCreature->mB135 && !pCreature->IsUnavailable() && (pCreature->mB58 & 4) == 0)
        return pCreature;
    return 0;
}

// ===========================================================================
// 0x00d99550: animation state still running
// ===========================================================================
// @ 0x00d99550
int32_t IsAnimRunning(cAnimState* pState)
{
    if (pState == 0 || pState->mfProgress < 1.0f)
        return true;
    return false;
}

// ===========================================================================
// 0x00d99570: play a creature animation and report whether it is still running
// ===========================================================================
// @ 0x00d99570
bool PlayIdleAnimation(cSPCreatureBase* pCreature, uint32_t nAnimID, uint32_t nFlags)
{
    if (pCreature == 0 || pCreature->mB4c == 0)
        return false;
    cAnimState* pState = pCreature->mB4c->mPlayer.Play(nAnimID, nFlags);
    if (pState == 0 || pState->mfProgress < 1.0f)
        return true;
    return false;
}

// ===========================================================================
// 0x00d995c0: compare the id of a ring node against a value
// ===========================================================================
// @ 0x00d995c0
bool RingNodeMatches(cTreeRing* pRing, const uint32_t* pValue)
{
    uint32_t nValue = *pValue;
    bool bMatches = pRing->mpNodes[(pRing->mnIndex + 3) * 3]->GetID() == nValue;
    return bMatches;
}

// ===========================================================================
// 0x00d995f0: walk-tree forwarder (the original keeps the x87 argument alive)
// ===========================================================================
// @ 0x00d995f0
void ForwardWalkTree(float fA, double dB, void* pC, void* pD, void* pE, void* pF, void* pG,
                     void* pH)
{
    WalkTree(fA, dB, pC, pD, pE, pF, pG, pH);
}

// ===========================================================================
// 0x00d99630: advance/bounce a menu index
// ===========================================================================
// @ 0x00d99630
bool StepIndex(int32_t* pnValue, int32_t* pnStep, bool* pbBounced, int32_t nLimit, int32_t nMode)
{
    *pbBounced = false;
    switch (nMode) {
    case 0: {
        int32_t nNext = *pnValue + *pnStep;
        if (nNext < 0 || nNext >= nLimit) {
            *pbBounced = true;
            *pnStep = -*pnStep;
        }
        *pnValue += *pnStep;
        return true;
    }
    case 1:
        if (*pnValue == nLimit - 1)
            return false;
        (*pnValue)++;
        return true;
    case 2:
        if (*pnValue == nLimit - 1) {
            *pnValue = 0;
            return true;
        }
        (*pnValue)++;
        return true;
    }
    return false;
}

// ===========================================================================
// 0x00d996b0: fill a stimulus description
// ===========================================================================
struct sStimulusDesc {
    uint32_t mID;                                                     // +0x00
    uint32_t mCount;                                                  // +0x04
    uint32_t mMax;                                                    // +0x08
    Vector3 mOffset;                                                  // +0x0c
};

// @ 0x00d996b0
void MakeStimulusDesc(uint32_t nID, uint32_t nUnused, const Vector3* pOffset,
                      sStimulusDesc* pOut)
{
    pOut->mID = nID;
    pOut->mMax = 1;
    pOut->mCount = 1;
    pOut->mOffset = *pOffset;
}

// ===========================================================================
// 0x00d996e0: plain copy of a flat stimulus record into the rotated layout
// ===========================================================================
// @ 0x00d996e0
void CopyStimulusFlat(const sStimulusFlat* pSrc, sStimulusRotated* pDst)
{
    pDst->mFieldSrc00 = pSrc->mField00;
    pDst->mFieldSrc04 = pSrc->mField04;
    pDst->mOffset = pSrc->mOffset;
    pDst->mFieldSrc08 = pSrc->mField08;
    pDst->mField18 = pSrc->mField18;
    pDst->mField1c = pSrc->mField1c;
    pDst->mField20 = pSrc->mField20;
    pDst->mf24 = pSrc->mf24;
}

// ===========================================================================
// 0x00d99730: behaviour_stimuli assignment (reference counted attributes)
// ===========================================================================
// @ 0x00d99730
void AssignStimulus(const sStimulusRecord* pSrc, sStimulusAssignment* pDst)
{
    pDst->mpA = pSrc->mpA;
    pDst->mpB = pSrc->mpB;
    pDst->mOffset = pSrc->mOffset;
    pDst->mpC = pSrc->mpC;
    pDst->mField18 = pSrc->mField18;
    pDst->mField1c = pSrc->mField1c;
    pDst->mField20 = pSrc->mField20;
    pDst->mf24 = pSrc->mf24;
}

// ===========================================================================
// 0x00d997e0: reset to the "any" stimulus
// ===========================================================================
// @ 0x00d997e0
behavior_stimuli& behavior_stimuli::GetAny()
{
    mStimulusID = 0;
    mField04 = 0;
    mDuration = 0;
    mOffset.x = gStimulusDefaultVec.x;
    mOffset.y = gStimulusDefaultVec.y;
    mOffset.z = gStimulusDefaultVec.z;
    mField18 = 0;
    mField1c = 0;
    mField20 = 0;
    mf24 = 0.0f;
    return *this;
}

// ===========================================================================
// 0x00d99830: build the default assignment on the stack and assign it
// ===========================================================================
// @ 0x00d99830
bool AssignDefaultStimulus(void* p1, void* p2, void* p3, void* p4, void* p5,
                           sStimulusAssignment* pDst, const sStimulusRecord* pSrc)
{
    if (pDst != 0) {
        pDst->mpA.mpObject = 0;
        pDst->mpB.mpObject = 0;
        pDst->mpC.mpObject = 0;
        pDst->mOffset.x = gStimulusDefaultVec.x;
        pDst->mOffset.y = gStimulusDefaultVec.y;
        pDst->mOffset.z = gStimulusDefaultVec.z;
        pDst->mField18 = 0;
        pDst->mField1c = 0;
        pDst->mField20 = 0;
        pDst->mf24 = 0.0f;
        pDst->mf28 = 0.0f;
    }
    AssignStimulus(pSrc, pDst);
    return true;
}

// ===========================================================================
// 0x00d99890: drop the reference counted attributes of an assignment
// (the release order +0x08, +0x04, +0x00 is the reverse of the declaration
// order of sStimulusAssignment; the five leading parameters are unused)
// ===========================================================================
// @ 0x00d99890
void ReleaseStimulusAttributes(void* p1, void* p2, void* p3, void* p4, void* p5,
                               sStimulusAssignment* pDst)
{
    if (pDst == 0)
        return;
    cStimulusAttrC* pC = pDst->mpC.mpObject;
    if (pC != 0)
        pC->Release();
    cStimulusAttrB* pB = pDst->mpB.mpObject;
    if (pB != 0)
        pB->Release();
    cStimulusAttrA* pA = pDst->mpA.mpObject;
    if (pA != 0)
        pA->Release();
}

// ===========================================================================
// 0x00d998d0: forward a lookup to the stimulus source
// ===========================================================================
// @ 0x00d998d0
int32_t QueryStimulus(cStimulusContext* pContext, uint32_t nStimulusID)
{
    if (pContext != 0) {
        cStimulusSource* pSource = pContext->mpSource;
        if (pSource != 0)
            return (int32_t)pSource->FindObject(nStimulusID);
    }
    return 0;
}

// ===========================================================================
// 0x00d998f0: pick the building a creature is fighting at
// ===========================================================================
// @ 0x00d998f0
void* GetExtinguishAnchor(cSPCreatureBase* pCreature)
{
    if (pCreature != 0 && pCreature->mf38 > 0.0000152587890625f) {
        if (pCreature->GetDamageState() != 2) {
            cCreatureStatus* pStatus = pCreature->GetStatus();
            if (pStatus == 0 || pStatus->mIsAlive) {
                cCreatureOwner* pOwner = pCreature->GetOwner();
                if (pOwner == 0)
                    return pCreature;
                if (!pOwner->IsUnavailable()) {
                    void* pResolved = ResolveObject((void*)pCreature->GetOwner());
                    if (pResolved == 0)
                        return pCreature;
                    cSPCreatureBase* pOther = ExtinguishTarget((cSPCreatureBase*)pResolved);
                    if (pOther == 0)
                        return 0;
                    return &pOther->mB5a8;
                }
            }
        }
    }
    return 0;
}

// ===========================================================================
// 0x00d99980: creature referenced by the "animal" stimulus
// ===========================================================================
// @ 0x00d99980
cSPCreatureBase* GetAnimalFromStimulus(cStimulusContext* pContext)
{
    if (pContext != 0) {
        cStimulusSource* pSource = pContext->mpSource;
        if (pSource != 0) {
            cSPCreatureBase* pCreature = pSource->FindObject(0xd0036e08);
            if (pCreature != 0) {
                if (pCreature->mB135 && !pCreature->IsUnavailable() &&
                    (pCreature->mB58 & 4) == 0)
                    return pCreature;
            }
        }
    }
    return 0;
}

// ===========================================================================
// 0x00d999d0: creature referenced by the "memory block" stimulus
// ===========================================================================
// @ 0x00d999d0
cSPCreatureBase* WatchMemoryBlock(cStimulusContext* pContext)
{
    if (pContext != 0) {
        cStimulusSource* pSource = pContext->mpSource;
        if (pSource != 0) {
            cSPCreatureBase* pCreature = pSource->FindObject(0xce9f6639);
            if (pCreature != 0) {
                if (pCreature->mB135 && !pCreature->IsUnavailable())
                    return pCreature;
            }
        }
    }
    return 0;
}

// ===========================================================================
// 0x00d99a10: creature referenced by stimulus 0x13f94d4
// ===========================================================================
// @ 0x00d99a10
cSPCreatureBase* GetStimulusCreature(cStimulusContext* pContext)
{
    if (pContext != 0) {
        cStimulusSource* pSource = pContext->mpSource;
        if (pSource != 0) {
            cSPCreatureBase* pCreature = pSource->FindObject(0x13f94d4);
            if (pCreature != 0) {
                cCreatureStatus* pStatus = pCreature->GetStatus();
                if (pStatus->mIsAlive && !pCreature->GetOwner()->IsUnavailable())
                    return pCreature;
            }
        }
    }
    return 0;
}

// ===========================================================================
// 0x00d99a60: distance between two bodies minus their radii
// ===========================================================================
// @ 0x00d99a60
float DistanceBetweenBodies(const Vector3* pA, float fRadiusA, const Vector3* pB,
                            float fRadiusB, bool bClamp)
{
    Vector3 d;
    d.x = pA->x - pB->x;
    d.y = pA->y - pB->y;
    d.z = pA->z - pB->z;

    float fDist = sqrtf(d.x * d.x + d.y * d.y + d.z * d.z) - (fRadiusA + fRadiusB);
    if (bClamp) {
        // The clamp runs in the float domain (the original stores the distance, then
        // maxes it against zero), so the result is rounded to float before the compare.
        volatile float fStore = fDist;
        if (fStore < 0.0f)
            fStore = 0.0f;
        return fStore;
    }
    return fDist;
}

// ===========================================================================
// 0x00d99ac0: distance between two spatial bodies
// ===========================================================================
// @ 0x00d99ac0
float ComputeBodyDistance(cSpatialObject* pA, cSpatialObject* pB, uint32_t nFlag)
{
    if ((pA->mFlags50 & 0x1000) == 0 && (pB->mFlags50 & 0x1000) == 0) {
        float fRadiusB = pB->GetRadius((const Vector3*)nFlag);
        Vector3* pPosB = pB->GetPosition(fRadiusB);
        float fRadiusA = pA->GetRadius(pPosB);
        Vector3* pPosA = pA->GetPosition(fRadiusA);
        return DistanceBetweenBodies(pPosA, fRadiusA, pPosB, fRadiusB, (bool)nFlag);
    }

    Vector3* pPosA = pA->GetPosition(0.0f);
    float fScale = 1.0f / sqrtf(pPosA->x * pPosA->x + pPosA->y * pPosA->y + pPosA->z * pPosA->z);
    Vector3* pPosB = pB->GetPosition(fScale);
    float fDot = ((pPosB->y - pPosA->y) * (pPosA->y * fScale) +
                  (pPosB->z - pPosA->z) * (pPosA->z * fScale)) +
                 (pPosB->x - pPosA->x) * (pPosA->x * fScale);
    pPosB = pB->GetPosition(fScale);
    float fRadiusA = pA->GetRadius((const Vector3*)0);
    float fRadiusB = pB->GetRadius((const Vector3*)0);
    float fDz = pPosA->z - (pPosB->z - (pPosA->z * fScale) * fDot);
    float fDy = pPosA->y - (pPosB->y - (pPosA->y * fScale) * fDot);
    float fDx = pPosA->x - (pPosB->x - (pPosA->x * fScale) * fDot);
    float fDist = sqrtf(fDx * fDx + (fDy * fDy + fDz * fDz)) - (fRadiusA + fRadiusB);
    if (nFlag != 0 && fDist < 0.0f)
        fDist = 0.0f;
    return fDist;
}

// ===========================================================================
// 0x00d99cd0: binary search along a ray for the point where it leaves the water
// ===========================================================================
// @ 0x00d99cd0
float RecursiveSurfaceProbe(const Vector3* pFrom, const Vector3* pDir, float fLow, float fHigh)
{
    if (fHigh - fLow <= 2.0f)
        return fLow;
    float fMid = (fHigh - fLow) * 0.5f + fLow;
    cPlanetModel* pPlanet = PlanetModel();
    Vector3 pt;
    pt.x = pFrom->x + pDir->x * fMid;
    pt.y = pFrom->y + pDir->y * fMid;
    pt.z = pFrom->z + pDir->z * fMid;
    pt = pPlanet->DirectionToSurfacePosition(pt);
    float fWater = pPlanet->GetWaterHeight();
    if (pt.z * pt.z + pt.y * pt.y + pt.x * pt.x > fWater * fWater)
        return RecursiveSurfaceProbe(pFrom, pDir, fMid, fHigh);
    return RecursiveSurfaceProbe(pFrom, pDir, fLow, fMid);
}

// ===========================================================================
// 0x00d99e20: project a point onto the planet surface seen from another point
// ===========================================================================
// @ 0x00d99e20
void ProjectToSurface(const Vector3* pFrom, Vector3* pTo)
{
    if (pFrom->x == pTo->x && pFrom->y == pTo->y && pFrom->z == pTo->z)
        return;
    cPlanetModel* pPlanet = PlanetModel();
    float fWater = pPlanet->GetWaterHeight();
    float fWaterSq = fWater * fWater;
    if (pFrom->y * pFrom->y + pFrom->z * pFrom->z + pFrom->x * pFrom->x <= fWaterSq) {
        *pTo = pPlanet->SnapToSurface(*pTo);
        return;
    }
    if (fWaterSq <= pTo->z * pTo->z + pTo->y * pTo->y + pTo->x * pTo->x)
        return;
    Vector3 dir;
    dir.x = pTo->x - pFrom->x;
    dir.y = pTo->y - pFrom->y;
    dir.z = pTo->z - pFrom->z;
    float fLen = sqrtf(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);
    float fInv = 1.0f / fLen;
    dir.x = dir.x * fInv;
    dir.y = dir.y * fInv;
    dir.z = dir.z * fInv;
    float fHit = RecursiveSurfaceProbe(pFrom, &dir, 0.0f, fLen);
    pTo->z = dir.z * fHit + pFrom->z;
    pTo->x = pFrom->x + dir.x * fHit;
    pTo->y = pFrom->y + dir.y * fHit;
}
