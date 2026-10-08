// Slice s00dcf2e0 -- vehicle group order: assign each active vehicle to a moving formation around its
// chase target, then lay the formations' action-circle slots out and send vehicles to them.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-  (no /EHsc: the local fixed_vector gets no EH frame; /GS- or the buffer gets a cookie)
//
// PDB candidate: SP::cVehicleGroupOrder::FormationMoveToTargets. Retail layouts differ from the 2008 PDB:
// cMovingFormation is 0x178 bytes (leader at +0x58, target at +0x60, circle at +0x104).
#include <math.h>
#include <float.h>
#include <string.h>
#include <new>
#include "types.h"

void operator delete[](void* p);   // 0x00f47380

namespace SP {

struct cSPVector3 {
    float x, y, z;
    cSPVector3() {}
    cSPVector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    cSPVector3(const cSPVector3& v) { x = v.x; y = v.y; z = v.z; }
    float LengthSquared() const { return x * x + y * y + z * z; }
    cSPVector3 Normalized() const
    {
        float inv = 1.0f / sqrtf(x * x + y * y + z * z + 1e-8f);
        return cSPVector3(x * inv, y * inv, z * inv);
    }
    bool operator==(const cSPVector3& v) const { return x == v.x && y == v.y && z == v.z; }
};
inline cSPVector3 operator-(const cSPVector3& a, const cSPVector3& b) { return cSPVector3(a.x - b.x, a.y - b.y, a.z - b.z); }

// The vtable of the chase target (an AutoRefCount'd cSpatialObject). Slot 0x2c is GetPosition().
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
    virtual float GetFootprintRadius();        // +0x74
    virtual void v78(); virtual void v7c(); virtual void v80(); virtual void v84();
    virtual void v88(); virtual void v8c(); virtual void v90(); virtual void v94();
    virtual void v98(); virtual void v9c(); virtual void va0(); virtual void va4();
    virtual void va8(); virtual void vac(); virtual void vb0(); virtual void vb4();
    virtual void* Cast(uint32_t type);         // +0xb8
    virtual void AddRef();                     // +0xbc
    virtual void Release();                    // +0xc0
};

// The same chase-target object, seen through the other overload of slot 0x2c that takes the
// formation's min/max distances (the original calls slot 0x2c with and without two float arguments).
class cTargetAt {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual const cSPVector3& GetPositionAt(float a, float b);   // +0x2c
};

struct cMoveRequest {
    char pad0[0x14];
    cSPVector3 mDst;                       // +0x14 (used when the waypoint list is empty)
    char pad20[0x5c - 0x20];
    int mField5C;                          // +0x5c
    const cSPVector3* GetDestination();    // 0x00c423c0
};

class cLocomotive : public cSpatialObject {
public:
    virtual void vc4();
    virtual float GetDesiredSpeed();       // +0xc8
    virtual void vcc(); virtual void vd0(); virtual void vd4(); virtual void vd8(); virtual void vdc();
    virtual void MoveTo(const cSPVector3& dst, float goalStopDistance, float acceptableStopDistance, bool relative);   // +0xe0
    virtual void MoveAround(const cSPVector3& center, float radius);   // +0xe4
    virtual void MoveTowards(const cSPVector3& dst);                    // +0xe8
    char pad0[0x270 - 0x4];
    uint32_t mFlags;                       // +0x2a4 in the vehicle
    char pad1[0x4d4 - 0x274];
    cMoveRequest* GetMoveRequest();        // 0x00c41ec0
};

class cCombatant {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual float GetRadius();   // +0x14
    char pad[0xb1c - 0x508 - 4];
    float GetStat();                       // 0x00bfc400 (returns 0 when the +0x14 virtual returns 0)
};

class cVehicle {
public:
    char pad0[0x34];
    cLocomotive mLoco;                     // +0x34
    cCombatant mCombatant;                 // +0x508
    int mLocomotion;                       // +0xb1c
    cSpatialObject* GetChaseTarget();      // 0x00c9fee0
    void SetAcceptableCenter(cSPVector3 center);   // 0x00c9fb40
    const cSPVector3* GetDestinationOut(cSPVector3* out);   // 0x00c9fdc0
    void FUN_00cacbe0();
};
static const uint32_t kVehicleType = 0x137e8e0;

struct tSlot {                   // cActionCircle::tSlot (0x18 bytes)
    bool mbOccupied;             // +0x0
    uint32_t pad04[2];
    cSPVector3 mPosition;        // +0xc
    void Occupy(cVehicle* pVehicle);   // 0x00afa030
};

struct SlotVec {
    tSlot* mpBegin;
    tSlot* mpEnd;
    tSlot* mpCapacity;
    void erase(tSlot* first, tSlot* last);   // 0x00afc0d0
};

float CircleRadius(float entityRadius, int count);   // 0x00af9e20 (cdecl)

class cActionCircle {
public:
    cSPVector3 mFacing;          // +0x00
    float mRadius;               // +0x0c
    float mSlotRadius;           // +0x10
    cSPVector3 mCenter;          // +0x14
    char pad20[0x50 - 0x20];
    SlotVec mSlots;              // +0x50
    char pad5c[0x64 - 0x5c];
    void Setup(const cSPVector3& center, float radius, const cSPVector3& facing, float altitude);   // 0x00af9cf0
    void Layout(float entityRadius, int count);   // 0x00afd1c0
    void RemoveAgent(cVehicle* pVehicle);         // 0x00afae50
    void FUN_00c2e4e0();                          // empty
};

struct Formation;
typedef void (__cdecl *SlotFunc)(Formation*, cActionCircle*, int);
void __cdecl FUN_00dc7590(Formation*, cActionCircle*, int);
void __cdecl FUN_00dc76e0();
void __cdecl FUN_00dc6430();

struct Formation {
    cLocomotive** mpEntBegin;    // +0x00
    cLocomotive** mpEntEnd;      // +0x04
    char pad08[0x58 - 0x08];
    cLocomotive* mpLeader;       // +0x58
    char pad5c[4];
    cSpatialObject* mpTarget;    // +0x60
    char pad64[0x7c - 0x64];
    float mMinDistance;          // +0x7c
    float mMaxDistance;          // +0x80
    float mEntityRadius;         // +0x84
    char pad88[0x94 - 0x88];
    float mTimerInterval;        // +0x94
    bool mbWaitingForPath;       // +0x98
    char pad99[0x104 - 0x99];
    cActionCircle mCircle;       // +0x104
    SlotFunc mpSlotValidationFunc;   // +0x168
    void* mpLeaderSelectFunc;    // +0x16c
    void* mpMoveCommandFunc;     // +0x170
    char pad174[4];

    Formation();                 // 0x00afbaf0
    ~Formation();                // 0x00afbde0
    void AddEntity(cLocomotive* p);      // 0x00afed00
    void RemoveEntity(cLocomotive* p);   // 0x00afedf0
};

struct FormationVec {
    Formation* mpBegin;
    Formation* mpEnd;
    Formation* mpCapacity;
    void DoInsertValue(Formation* pos, const Formation& value);   // 0x00dcf180

    __forceinline int size() const { return (int)(mpEnd - mpBegin); }
    __forceinline void push_back()
    {
        if (mpEnd < mpCapacity) {
            ::new (mpEnd++) Formation();
        } else {
            Formation tmp;
            DoInsertValue(mpEnd, tmp);
        }
    }
};

// eastl::vector<T> with a fixed inline buffer (sp_fixed_vector); a heap block is freed unless it is the buffer.
template<class T, int N> struct SpFixedVec {
    T*       mpBegin;
    T*       mpEnd;
    T*       mpCapacity;
    uint32_t mAllocator;
    T*       mpFixed;
    uint32_t mPadding;
    T        mBuffer[N];

    __forceinline SpFixedVec() : mpBegin(mBuffer), mpFixed(mBuffer), mpEnd(mBuffer), mpCapacity(mBuffer + N) {}
    __forceinline ~SpFixedVec() { if (mpBegin && mpBegin != mpFixed) operator delete[](mpBegin); }

    void DoInsertValue(T* pos, const T& value);   // 0x00cd0550
    __forceinline int size() const { return (int)(mpEnd - mpBegin); }
    __forceinline void push_back(const T& value)
    {
        if (mpEnd < mpCapacity) {
            T* p = mpEnd++;
            if (p) *p = value;
        } else {
            DoInsertValue(mpEnd, value);
        }
    }
    __forceinline void erase(T* position)
    {
        if (position + 1 < mpEnd)
            memcpy(position, position + 1, (mpEnd - (position + 1)) * sizeof(T));
        --mpEnd;
    }
};
typedef SpFixedVec<cVehicle*, 60> VehicleVec;

// 0x00dc6640: is the vehicle's locomotive one of the formation's entities?
bool __cdecl IsFormationMember(Formation* pFormation, cVehicle** ppVehicle);
// 0x00dc6680: the vehicle in the list closest to the position
cVehicle* __cdecl FindClosestVehicle(VehicleVec* pList, const cSPVector3* pPosition, bool b);
void __cdecl AttemptRepark(cVehicle* pVehicle);   // anonymous namespace, 0x00dc9430

template<class T> inline void AssignRef(T*& slot, T* p)
{
    T* old = slot;
    if (p != old) {
        if (p) p->AddRef();
        slot = p;
        if (old) old->Release();
    }
}

inline cVehicle* AsVehicle(cSpatialObject* p) { return p ? (cVehicle*)p->Cast(kVehicleType) : 0; }

class cVehicleGroupOrder {
public:
    char pad0[0x50];
    cVehicle** mpVehiclesBegin;  // +0x50
    cVehicle** mpVehiclesEnd;    // +0x54
    char pad58[0x7c - 0x58];
    FormationVec mFormations;    // +0x7c

    void FormationMoveToTargets(int);   // 0x00dcf2e0
};

// @ 0x00dcf2e0
void cVehicleGroupOrder::FormationMoveToTargets(int)
{
    int numVehicles = (int)(mpVehiclesEnd - mpVehiclesBegin);
    for (int i = 0; i < numVehicles; i++) {
        cVehicle* pVehicle = mpVehiclesBegin[i];
        cSpatialObject* pTarget = pVehicle->GetChaseTarget();
        if (!pTarget)
            continue;

        int current = -1;
        int best = -1;
        int numFormations = mFormations.size();
        for (int j = 0; j < numFormations; j++) {
            Formation* pFormation = &mFormations.mpBegin[j];
            if (pFormation->mpEntBegin == pFormation->mpEntEnd)
                continue;
            cVehicle* pOther = 0;
            if (pFormation->mpLeader)
                pOther = AsVehicle(pFormation->mpLeader);
            if (!pOther)
                pOther = AsVehicle(*pFormation->mpEntBegin);
            if (pOther && pFormation->mpTarget == pTarget && pOther->mLocomotion == pVehicle->mLocomotion) {
                const cSPVector3& a = pTarget->GetPosition();
                const cSPVector3& b = pOther->mLoco.GetPosition();
                cSPVector3 d = b - a;
                if (d.LengthSquared() < FLT_MAX)
                    best = j;
                if (IsFormationMember(pFormation, &pVehicle))
                    current = j;
            }
        }
        if (current != best) {
            if (current != -1) {
                cLocomotive* pLoco = pVehicle ? &pVehicle->mLoco : 0;
                mFormations.mpBegin[current].RemoveEntity(pLoco);
                mFormations.mpBegin[current].mCircle.RemoveAgent(pVehicle);
            }
            if (best != -1) {
                cLocomotive* pLoco = pVehicle ? &pVehicle->mLoco : 0;
                Formation* pBest = &mFormations.mpBegin[best];
                pBest->AddEntity(pLoco);
                const cSPVector3& c = ((cTargetAt*)pTarget)->GetPositionAt(pBest->mMinDistance, pBest->mMaxDistance);
                pVehicle->SetAcceptableCenter(c);
            }
            current = best;
        }

        if (current == -1) {
            mFormations.push_back();
            Formation* pNew = mFormations.mpEnd - 1;
            pNew->mpSlotValidationFunc = FUN_00dc7590;
            pNew->mpLeaderSelectFunc = (void*)FUN_00dc76e0;
            pNew->mpMoveCommandFunc = (void*)FUN_00dc6430;
            AssignRef(pNew->mpTarget, pTarget);
            pNew->mMinDistance = 8.0f;
            pNew->mMaxDistance = pVehicle->mCombatant.GetStat() * 0.75f;
            cLocomotive* pLoco = &pVehicle->mLoco;
            pNew->mEntityRadius = pLoco->GetFootprintRadius() + 2.0f;
            pNew->mTimerInterval = 0.1f;
            pNew->AddEntity(pLoco);
            AssignRef(pNew->mpLeader, pLoco);
            pNew->mbWaitingForPath = true;
            pLoco->MoveTowards(((cTargetAt*)pTarget)->GetPositionAt(pNew->mMinDistance, pNew->mMaxDistance * 0.5f));
            pVehicle->SetAcceptableCenter(((cTargetAt*)pTarget)->GetPositionAt(0.0f, 1.0f));
            pNew->mCircle.mSlots.erase(pNew->mCircle.mSlots.mpBegin, pNew->mCircle.mSlots.mpEnd);
        }
        else {
            Formation* pFormation = &mFormations.mpBegin[current];
            cActionCircle* pCircle = &pFormation->mCircle;
            cLocomotive* pLoco = pVehicle ? &pVehicle->mLoco : 0;
            if (pLoco == pFormation->mpLeader) {
                cMoveRequest* pRequest = pVehicle->mLoco.GetMoveRequest();
                if (pRequest->mField5C) {
                    cSPVector3 dst = *pRequest->GetDestination();
                    if (pCircle->mSlots.mpBegin == pCircle->mSlots.mpEnd) {
                        cSPVector3 d = pTarget->GetPosition() - dst;
                        cSPVector3 dir = d.Normalized();
                        float radius = CircleRadius(pFormation->mEntityRadius, (int)(pFormation->mpEntEnd - pFormation->mpEntBegin));
                        pCircle->Setup(dst, radius, dir, 0.0f);
                        pCircle->Layout(pFormation->mEntityRadius, (int)(pFormation->mpEntEnd - pFormation->mpEntBegin));
                        pFormation->mpSlotValidationFunc(pFormation, pCircle, 1);
                    }
                }
            } else {
                cLocomotive* pSp = &pVehicle->mLoco;
                if (pSp->GetDesiredSpeed() == 0.0f && !(pVehicle->mLoco.mFlags & 4) &&
                    pCircle->mSlots.mpBegin != pCircle->mSlots.mpEnd) {
                    const cSPVector3& p = pSp->GetPosition();
                    cSPVector3 d = p - pCircle->mCenter;
                    float r = pCircle->mRadius;
                    if (r + r < sqrtf(d.x * d.x + d.y * d.y + d.z * d.z))
                        pSp->MoveAround(pCircle->mCenter, r * 1.75f);
                }
            }
        }
    }

    int numFormations = mFormations.size();
    for (int j = 0; j < numFormations; j++) {
        Formation* pFormation = &mFormations.mpBegin[j];
        if (pFormation->mpEntBegin == pFormation->mpEntEnd || pFormation->mCircle.mSlots.mpBegin == pFormation->mCircle.mSlots.mpEnd)
            continue;
        VehicleVec list;
        cActionCircle* pCircle = &pFormation->mCircle;
        int count = (int)(pFormation->mpEntEnd - pFormation->mpEntBegin);
        for (int k = 0; k < count; k++) {
            cVehicle* pV = AsVehicle(pFormation->mpEntBegin[k]);
            const cSPVector3& p = pV->mLoco.GetPosition();
            cSPVector3 d = p - pCircle->mCenter;
            float dist = sqrtf(d.x * d.x + d.y * d.y + d.z * d.z);
            if (dist < pCircle->mRadius + pCircle->mRadius)
                list.push_back(pV);
        }
        int remaining = list.size();
        int numSlots = (int)(pCircle->mSlots.mpEnd - pCircle->mSlots.mpBegin);
        if (numSlots > 0 && remaining > 0) {
            pFormation->mpSlotValidationFunc(pFormation, pCircle, 1);
            for (int s = 0; s < numSlots; s++) {
                if (remaining <= 0)
                    break;
                tSlot* pSlot = &pCircle->mSlots.mpBegin[s];
                if (!pSlot->mbOccupied) {
                    bool flag = false;
                    cVehicle* pClosest = FindClosestVehicle(&list, &pSlot->mPosition, flag);
                    if (pClosest) {
                        pSlot->Occupy(pClosest);
                        cSPVector3 tmp;
                        const cSPVector3* pCur = pClosest->GetDestinationOut(&tmp);
                        if (!(*pCur == pSlot->mPosition))
                            pClosest->mLoco.MoveTo(pSlot->mPosition, 1.0f, 2.0f, false);
                        cVehicle** it = list.mpBegin;
                        for (; it != list.mpEnd; ++it) {
                            if (*it == pClosest) {
                                list.erase(it);
                                break;
                            }
                        }
                        --remaining;
                    }
                }
            }
            for (int k = 0; k < list.size(); k++) {
                cVehicle* pV = list.mpBegin[k];
                uint32_t flags = pV->mLoco.mFlags;
                if (flags & 2)
                    AttemptRepark(pV);
                else if (flags & 4)
                    pV->FUN_00cacbe0();
            }
        }
        pCircle->FUN_00c2e4e0();
    }
}

}  // namespace SP
