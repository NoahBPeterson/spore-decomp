// Slice s00d79470: SP::cTribeGameBehaviorParty::Action (vtable 0x0147bf60 slot 6, same slot as
// cTribeGameBehaviorFish::Action in s00d74060). The tribe party: while the party has to be
// (re)configured, every participating creature gets a slot on the action circle around the
// party target and walks there; afterwards the per-agent dance state machine runs (wait in the
// circle, then 7 dance moves) and, once everybody is in the circle, the dance starts with a sound.
// Retail layout differs from the 2008 PDB (cInteraction is 8 bytes larger: the agent list is at
// +0x2c, the agent-info map at +0x74, mUpdateConfiguration at +0x100), so members are named by
// retail offset. Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (no /EHsc: the local fixed_vector
// gets no EH frame).
#include <math.h>
#include "types.h"

void operator delete[](void* p);   // 0x00f47380

namespace SP {
static const uint32_t kPartyTargetType = 0x0116d858;
static const uint32_t kCreatureType = 0x4f176642;

struct cSPVector3 {
    float x, y, z;
    cSPVector3() {}
    cSPVector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    cSPVector3(const cSPVector3& v) { x = v.x; y = v.y; z = v.z; }
    cSPVector3 Normalized() const
    {
        float inv = 1.0f / sqrtf(x * x + y * y + z * z + 1e-8f);
        return cSPVector3(inv * x, y * inv, z * inv);
    }
    float LengthSquared() const { return x * x + y * y + z * z; }
    cSPVector3& operator+=(const cSPVector3& v) { x += v.x; y += v.y; z += v.z; return *this; }
    bool operator==(const cSPVector3& v) const { return x == v.x && y == v.y && z == v.z; }
};
inline cSPVector3 operator-(const cSPVector3& a, const cSPVector3& b) { return cSPVector3(a.x - b.x, a.y - b.y, a.z - b.z); }
inline cSPVector3 operator*(const cSPVector3& a, float s) { return cSPVector3(a.x * s, a.y * s, a.z * s); }
inline float Dot(const cSPVector3& a, const cSPVector3& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }

extern const cSPVector3 kZeroVector;   // 0x0169efec

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float a, float b, float c) : x(a), y(b), z(c) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
};
inline Vector3 Sub(const cSPVector3& a, const cSPVector3& b)
{
    Vector3 r(a.x - b.x, a.y - b.y, a.z - b.z);
    return r;
}
struct cSPVector3Arg : cSPVector3 {
    cSPVector3Arg(const Vector3& v) : cSPVector3(v.x, v.y, v.z) {}
};
cSPVector3 normalized_safe(const cSPVector3Arg& v);   // 0x00449c20

// fixed_vector<T, N> with the sp allocator: the word before the inline buffer is 0, a heap block
// has a non-zero header there.
template<class T, int N> struct FixedVector {
    T*       mpBegin;
    T*       mpEnd;
    T*       mpCapacity;
    uint32_t mAllocator[2];
    int      mBufferHeader;
    T        mBuffer[N];

    __forceinline FixedVector() : mpBegin(mBuffer), mpEnd(mBuffer), mpCapacity(mBuffer + N), mBufferHeader(0) {}
    __forceinline ~FixedVector() { if (mpBegin && ((int*)mpBegin)[-1]) operator delete[](mpBegin); }

    __forceinline uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    void DoInsertValue(T* pos, const T& value);   // 0x00b96600
    __forceinline void push_back(const T& value)
    {
        if (mpEnd < mpCapacity) {
            T* p = mpEnd++;
            if (p) *p = value;
        } else {
            DoInsertValue(mpEnd, value);
        }
    }
};

class cSpatialObject {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual const cSPVector3& GetPosition();   // +0x2c
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70();
    virtual float GetBoundingRadius();         // +0x74
};

struct cLocomotionState {
    uint32_t pad00[0x17];
    int field_5c;                          // non-zero while a move goal is set
    const cSPVector3& GetGoal();           // 0x00c423c0
};

class cLocomotiveObject : public cSpatialObject {
public:
    cLocomotionState* GetState();          // 0x00c41ec0
    bool IsNearGoal();                     // 0x00c42e20
};

class cInteractionAgent { uint32_t mFirst; };

class cSPCreatureBase {
public:
    virtual void v00();
    uint32_t pad04[0x15];
    cInteractionAgent mAgent;              // +0x58
    uint32_t pad5c[0x19];
    cLocomotiveObject mLocomotion;         // +0xc0

    enum eSpeedState { kSpeedRun = 2 };
    void MoveToPointAndFacingAtSpeed(eSpeedState speed, const cSPVector3& point,
                                     const cSPVector3& facing, float f1, float f2);   // 0x00c1c5c0
    bool IsInSubInteraction();                                     // 0x00c232c0 (field +0x1014 != 0)
    bool IsIdle(int a, int b);                                     // 0x00c25480
    void InterruptAnimation(uint32_t animID, int a, int b);        // 0x00c12310
    bool AnimationFinished(int a);                                 // 0x00c123f0
};

class cCreatureCitizen;

class cTribe {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8();
    virtual class cPartyTarget* GetLeader();  // +0xac
    uint32_t pad04[0x99];
    float mPartyRadius;                    // +0x268
    void SetParty(bool b);                 // 0x00c8e7d0
};

// the party target (cast from the interaction's first target)
class cPartyTarget {
public:
    virtual void v00();
    uint32_t pad04[0xc];
    cSpatialObject mSpatial;               // +0x34
    cTribe* GetTribe();                    // 0x00c9d9e0
};

class cInteractionTarget {
public:
    virtual void v00();
    virtual cPartyTarget* Cast(uint32_t typeID);   // +0x4
};

class cInteractionAgentObject {
public:
    virtual void v00(); virtual void v04();
    virtual cSPCreatureBase* Cast(uint32_t typeID);   // +0x8
};

struct tSlotEntry { uint32_t mSlotInfo; void* mpData; };

// spstl::slot_deque<EA::AutoRefCount<T>, eastl::allocator, 128>
struct AgentDeque {
    tSlotEntry** mpBlocks;
    int Count();                           // 0x00abefd0
};

struct AgentFilter {
    class cTribeGameBehaviorParty* mpOwner;
    bool mbFlag;
    AgentFilter(class cTribeGameBehaviorParty* pOwner, bool flag) : mpOwner(pOwner), mbFlag(flag) {}
};

// iterator over the live agents of the agent list (range: current and end position + filter)
struct AgentIterator {
    AgentDeque* mpDeque;
    uint32_t mIndex;
    AgentDeque* mpEndDeque;
    uint32_t mEndIndex;
    AgentFilter mFilter;

    AgentIterator(AgentDeque* pDeque, const AgentFilter& filter);   // 0x00abf010
    void Next();                                                     // 0x00abeb20
    __forceinline bool IsDone() const { return (uint32_t)mpDeque + mIndex == (uint32_t)mpEndDeque + mEndIndex; }
    __forceinline cInteractionAgentObject* Get() const
    {
        return (cInteractionAgentObject*)mpDeque->mpBlocks[mIndex >> 7][mIndex & 0x7f].mpData;
    }
};

struct cAgentInfo {
    int mState;                            // InteractionState
    uint32_t mDanceIndex;
    bool mbSuccess;
};

// eastl::map<cInteractionAgent*, cAgentInfo>
struct AgentInfoMap {
    uint32_t mData[7];
    cAgentInfo& operator[](cInteractionAgent* const& key);   // 0x00d79350
};

struct tSlot {                   // cActionCircle::tSlot (0x18 bytes)
    bool mbOccupied;             // +0x0
    uint32_t pad04[2];
    cSPVector3 mPosition;        // +0xc
    void Occupy(cSPCreatureBase* pCreature);   // 0x00afa030
};

class cActionCircle {
public:
    uint32_t pad00[0x14];
    tSlot* mSlotsBegin;          // +0x50 (mSlots)
    tSlot* mSlotsEnd;            // +0x54
    void SetCenter(const cSPVector3& pos, float radius, const cSPVector3& dir, float altitude);   // 0x00af9cf0
    void SetSlots(int arg, float spacing);                                                    // 0x00afef10
};
void UpdateActionCircle(cActionCircle* pCircle);   // 0x00d9aa20

class IBehaviorManager {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual uint32_t GetDeltaTimeMS();   // +0x10
};
IBehaviorManager* BehaviorManager();     // 0x00b3d260

// 0x00da1060: orders the members around their centre (cdecl, centre by value)
void SortSectionMembers(cSPCreatureBase** first, cSPCreatureBase** last, cSPVector3 center);

extern const uint32_t kDanceMoves[7];    // 0x0158441c
extern float kPartyWalkSpeedA;           // 0x01572070
extern float kPartyWalkSpeedB;           // 0x0157206c

enum InteractionState {
    kNone = 0,
    kInSubInteraction = 1,
    kMoveToSpotOnCircle = 2,
    kWaitingInCircle = 3,
    kStartDancing = 4,
    kStartDanceMove = 5,
    kDancing = 6,
    kLastDance = 7,
};

class cTribeGameBehaviorParty {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14();
    virtual int Action();                                   // +0x18
    virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28();
    virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38();
    virtual void v3c(); virtual void v40();
    virtual void AgentFinished(AgentIterator it);           // +0x44

    bool IsActiveAgent(cInteractionAgent* pAgent);          // 0x00abea40
    __forceinline cInteractionTarget* GetFirstTarget()
    {
        if (mTargetFirst == 0x3fffffff)
            return 0;
        return (cInteractionTarget*)mTargetBlocks[mTargetFirst >> 7][mTargetFirst & 0x7f].mpData;
    }
    __forceinline cPartyTarget* GetPartyTarget()
    {
        cInteractionTarget* p = GetFirstTarget();
        if (p)
            return p->Cast(kPartyTargetType);
        return 0;
    }
    AgentIterator FindAgent(cInteractionAgent* pAgent);     // 0x00abf110

    uint32_t pad04[2];
    tSlotEntry** mTargetBlocks;            // +0x0c mTargetList
    uint32_t pad10[5];
    uint32_t mTargetFirst;                 // +0x24
    uint32_t pad28;
    AgentDeque mAgentList;                 // +0x2c
    uint32_t pad30[0x11];
    AgentInfoMap mAgentInfoMap;            // +0x74
    uint32_t mSoundHandle;                 // +0x90
    int mPartyState;                       // +0x94
    float mTimer;                          // +0x98
    cActionCircle mActionCircle;           // +0x9c
    uint32_t padf4[3];
    bool mUpdateConfiguration;             // +0x100
};

namespace EA_Audio {
class IAudioSystem {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual uint32_t NewHandle();          // +0x20
};
IAudioSystem* GetSystemAT();               // 0x00a206f0
}
void Start3dSoundByName(uint32_t soundID, uint32_t handle, float x, float y, float z);   // 0x00571f80


// @ 0x00d79470  SP::cTribeGameBehaviorParty::Action
int cTribeGameBehaviorParty::Action()
{
    AgentIterator it(&mAgentList, AgentFilter(this, false));
    if (it.IsDone())
        return 1;

    cPartyTarget* pTarget = GetPartyTarget();
    if (!pTarget)
        return 0;

    if (mPartyState == 1) {
        mTimer += (float)BehaviorManager()->GetDeltaTimeMS() * 0.001f;
        if (mTimer > 1.0f) {
            mTimer = 0.0f;
            mUpdateConfiguration = true;
        }
    }

    if (mUpdateConfiguration) {
        // place every participant on the action circle around the party target
        cTribe* pTribe = pTarget->GetTribe();
        mUpdateConfiguration = false;
        pTribe->SetParty(true);
        int count = mAgentList.Count();
        float slotRadius = pTribe->mPartyRadius;
        float radius = pTarget->mSpatial.GetBoundingRadius() + slotRadius;
        const cSPVector3& center = pTarget->mSpatial.GetPosition();
        cSPVector3 dir = normalized_safe(Sub(pTribe->GetLeader()->mSpatial.GetPosition(), center));
        mActionCircle.SetCenter(center, sqrtf((float)count * slotRadius * slotRadius + radius * radius), dir, 0.0f);
        mActionCircle.SetSlots(0, slotRadius * 0.5f);
        UpdateActionCircle(&mActionCircle);

        cSPVector3 groupCenter(kZeroVector);
        FixedVector<cSPCreatureBase*, 16> creatures;
        for (; !it.IsDone(); it.Next()) {
            cInteractionAgentObject* pAgent = it.Get();
            cSPCreatureBase* pCreature;
            if (pAgent && (pCreature = pAgent->Cast(kCreatureType)) != 0 && IsActiveAgent(&pCreature->mAgent)) {
                creatures.push_back(pCreature);
                groupCenter += pCreature->mLocomotion.GetPosition();
            }
        }
        float inv = 1.0f / (float)creatures.size();
        groupCenter = groupCenter * inv;
        SortSectionMembers(creatures.mpBegin, creatures.mpEnd, groupCenter);

        uint32_t n = creatures.size();
        for (uint32_t i = 0; i < n; ++i) {
            cSPCreatureBase* pCreature = creatures.mpBegin[i];
            const cSPVector3& pos = pCreature->mLocomotion.GetPosition();
            cSPVector3 dirFromCenter = (pos - groupCenter).Normalized();
            if (dirFromCenter == kZeroVector)
                dirFromCenter = (pos - center).Normalized();

            uint32_t bestSlot = (uint32_t)-1;
            float bestScore = 0.0f;
            uint32_t numSlots = (uint32_t)(mActionCircle.mSlotsEnd - mActionCircle.mSlotsBegin);
            for (uint32_t k = 0; k < numSlots; ++k) {
                if (!mActionCircle.mSlotsBegin[k].mbOccupied) {
                    cSPVector3 toSlot = mActionCircle.mSlotsBegin[k].mPosition - center;
                    float invLen = 1.0f / sqrtf(toSlot.x * toSlot.x + toSlot.y * toSlot.y + toSlot.z * toSlot.z);
                    float score = (Dot(toSlot * invLen, dirFromCenter) + 1.0f) * invLen;
                    if (score > bestScore) {
                        bestSlot = k;
                        bestScore = score;
                    }
                }
            }
            if (bestSlot != (uint32_t)-1) {
                tSlot* pSlot = &mActionCircle.mSlotsBegin[bestSlot];
                cSPVector3 facing = (center - pSlot->mPosition).Normalized();
                pSlot->Occupy(pCreature);
                // (re)send the creature unless it is already heading to this slot
                cLocomotionState* pState = pCreature->mLocomotion.GetState();
                if (pState->field_5c == 0 || (pState->GetGoal() - pSlot->mPosition).LengthSquared() > 1.5258789e-05f) {
                    pCreature->MoveToPointAndFacingAtSpeed(cSPCreatureBase::kSpeedRun, pSlot->mPosition, facing,
                                                           kPartyWalkSpeedA, kPartyWalkSpeedB);
                    mAgentInfoMap[&pCreature->mAgent].mState = kInSubInteraction;
                }
            } else {
                AgentFinished(FindAgent(&pCreature->mAgent));
            }
        }
        return 1;
    }

    // per-agent dance state machine
    bool anyInSubInteraction = false;
    bool anyWaiting = false;
    for (; !it.IsDone(); it.Next()) {
        cInteractionAgentObject* pAgent = it.Get();
        cSPCreatureBase* pCreature;
        if (pAgent && (pCreature = pAgent->Cast(kCreatureType)) != 0 && pCreature->IsInSubInteraction() &&
            IsActiveAgent(&pCreature->mAgent)) {
            cAgentInfo& info = mAgentInfoMap[&pCreature->mAgent];
            switch (info.mState) {
            case kInSubInteraction:
                anyInSubInteraction = true;
                if (pCreature->IsIdle(0, 1) && pCreature->mLocomotion.IsNearGoal())
                    info.mState = kWaitingInCircle;
                break;
            case kWaitingInCircle:
                anyWaiting = true;
                break;
            case kStartDancing:
                info.mState = kStartDanceMove;
                break;
            case kDancing:
                if (!pCreature->AnimationFinished(0))
                    break;
                // fall through
            case kStartDanceMove:
                if (info.mDanceIndex >= 7) {
                    info.mState = kLastDance;
                } else {
                    pCreature->InterruptAnimation(kDanceMoves[info.mDanceIndex % 7], -1, 0);
                    info.mDanceIndex++;
                    info.mState = info.mDanceIndex < 7 ? kDancing : kLastDance;
                }
                break;
            case kLastDance:
                if (pCreature->AnimationFinished(0)) {
                    info.mbSuccess = true;
                    AgentFinished(it);
                }
                break;
            }
        }
    }

    if (anyWaiting) {
        if (anyInSubInteraction) {
            mPartyState = 1;
            return 1;
        }
        // everybody is in the circle: start dancing
        mPartyState = 2;
        AgentIterator it2(&mAgentList, AgentFilter(this, false));
        if (mSoundHandle == 0) {
            EA_Audio::IAudioSystem* pAudio = EA_Audio::GetSystemAT();
            mSoundHandle = pAudio ? pAudio->NewHandle() : 0;
            const cSPVector3& pos = pTarget->mSpatial.GetPosition();
            Start3dSoundByName(0x19dc06df, mSoundHandle, pos.x, pos.y, pos.z);
        }
        for (; !it2.IsDone(); it2.Next()) {
            cInteractionAgentObject* pAgent = it2.Get();
            cSPCreatureBase* pCreature;
            if (pAgent && (pCreature = pAgent->Cast(kCreatureType)) != 0 && pCreature->IsInSubInteraction() &&
                IsActiveAgent(&pCreature->mAgent))
                mAgentInfoMap[&pCreature->mAgent].mState = kStartDancing;
        }
    }
    return 1;
}

}  // namespace SP
