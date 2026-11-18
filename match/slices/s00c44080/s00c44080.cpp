// Slice s00c44080 - SporeApp 0x00c44080..0x00c45760
// SP::cSPMission empire/planet accessors and small mission helpers.
// Flags: /O2 /Ob1 /MD /Gy /EHsc /TP /arch:SSE /GS-
//
// NOTE: the remaining slice VAs were not reconstructed in this pass and are
// recorded as unreconstructed in partial.txt.
#include "types.h"
#include <math.h>

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

// ---------------------------------------------------------------------------------------------
// Support types
// ---------------------------------------------------------------------------------------------
struct cStarRecord {
    u32 GetStarID();        // 0x00b8de30
    int GetCommContext();   // 0x00ce6950
};

struct cPlanet {
    u8            mPad0000[0x13c];
    cStarRecord*  mpStarRecord13c;   // 0x13c
};

struct cEmpire {
    u8   mPad0000[0x84];
    u32  mEmpireID84;                // 0x84
};

struct cStarManager {
    cEmpire* GetEmpireByID();        // 0x00ba9370
};

struct cUFO {
    int   ComputeCost(u32 starID);   // 0x00ffc4e0
    float ComputeCostFloat(u32 starID);  // 0x00ffc490
};

cStarManager* __stdcall GetStarManager(u32 empireID);  // 0x00b3d2a0
cUFO*         __stdcall GetUFOSimulator(u32 starID);   // 0x00ffbe50

void __cdecl SP_GetPropertyAsString16(void* prop, int key, int value);  // 0x006a1400

struct cProperty {
    u8    mPad0000[0x12];
    u16   mType12;                   // 0x12  property data type (1 = bool)
    bool* GetBool();                 // 0x0041e920
};

struct cPropertyList {
    // vtable slot 9 (offset 0x24), returns whether the key was found
    bool GetProperty(int key, cProperty** out);
};

inline bool cPropertyList::GetProperty(int key, cProperty** out)
{
    return ((bool (__thiscall*)(cPropertyList*, int, cProperty**))
            (*(void***)this)[9])(this, key, out);
}

// vtable slot dispatch helpers (slots 0/1 are AddRef/Release)
static inline void VT_00_0(void* p) { ((void (__thiscall*)(void*))(*(void***)p)[0])(p); }
static inline void VT_04_0(void* p) { ((void (__thiscall*)(void*))(*(void***)p)[1])(p); }
static inline int  VT_60_0(void* p) { return ((int (__thiscall*)(void*))(*(void***)p)[0x18])(p); }

// ---------------------------------------------------------------------------------------------
// SP::cSPMission
// ---------------------------------------------------------------------------------------------
struct cSPMission {
    u8            mPad0000[0x7c];
    int           mUsed7c;                 // 0x7c
    int           mTotal80;                // 0x80
    u8            mPad0084[0x8c - 0x84];
    int           mEmpireID8c;             // 0x8c
    u8            mPad0090[0x94 - 0x90];
    int           mCachedEmpireID94;       // 0x94  (-1 when unset)
    cEmpire*      mpEmpire98;              // 0x98  ref-counted, cached
    cPlanet*      mpOriginPlanet9c;        // 0x9c
    u8            mPad00a0[0x130 - 0xa0];
    u8            mFlags130;               // 0x130
    u8            mPad0131[0x180 - 0x131];
    cPropertyList* mpPropertyList180;      // 0x180
    u8            mPad0184[0x1e8 - 0x184];
    cPlanet*      mpTargetPlanet1e8;       // 0x1e8

    void        SetEmpire(cEmpire* p);                    // 0x00c45250
    cEmpire*    GetEmpire();                              // 0x00c452a0
    int         SetUITextValue(int value);                // 0x00c45310
    bool        IsVisibleInUI();                          // 0x00c45340
    int         GetNumAvailable();                        // 0x00c45380
    int         GetTotalTravelCost();                     // 0x00c45510
    float       GetTotalTravelCostFloat();                // 0x00c45560
    bool        IsAtStar(int empireID, int commContext);  // 0x00c455b0
    int         GetDynamicResponseID(int a, int b);       // 0x00c45740
};

// @ 0x00c45250
// Sets the cached empire: the id is remembered separately so that the empire
// pointer can be re-fetched lazily; the previous empire is released.
void cSPMission::SetEmpire(cEmpire* p)
{
    mCachedEmpireID94 = (p != 0) ? (int)p->mEmpireID84 : -1;
    cEmpire* old = mpEmpire98;
    if (p != old) {
        if (p != 0)
            VT_00_0(p);
        mpEmpire98 = p;
        if (old != 0)
            VT_04_0(old);
    }
}

// @ 0x00c452a0
// Lazily resolves mpEmpire98 from the cached empire id.
cEmpire* cSPMission::GetEmpire()
{
    if (mpEmpire98 != 0)
        return mpEmpire98;
    int id = mCachedEmpireID94;
    if (id == -1)
        return mpEmpire98;
    cStarManager* mgr = GetStarManager((u32)id);
    cEmpire* e = mgr->GetEmpireByID();
    cEmpire* old = mpEmpire98;
    if (e == old)
        return old;
    if (e != 0)
        VT_00_0(e);
    mpEmpire98 = e;
    if (old != 0) {
        VT_04_0(old);
        return mpEmpire98;
    }
    return e;
}

// @ 0x00c45310
// Writes `value` into the mission's UI text property, returning it.
int cSPMission::SetUITextValue(int value)
{
    if (value != 0 && mpPropertyList180 != 0)
        SP_GetPropertyAsString16(mpPropertyList180, 0x00b2ccca, value);
    return value;
}

// @ 0x00c45340
// Whether the mission shows up in the UI: true unless its UI title property
// says otherwise.
bool cSPMission::IsVisibleInUI()
{
    bool visible = true;
    if (mpPropertyList180 != 0) {
        cProperty* prop = 0;
        if (mpPropertyList180->GetProperty(0x05590946, &prop)) {
            if (prop->mType12 == 1)
                visible = *prop->GetBool();
        }
    }
    return visible;
}

static inline const int& max_ref(const int& a, const int& b) { return (a < b) ? b : a; }

// @ 0x00c45380
// Number of unused entries in the 0x7c/0x80 counter pair.
int cSPMission::GetNumAvailable()
{
    u32 total = mTotal80;
    if (total > 0) {
        int zero = 0;
        int d = (int)(total - (u32)mUsed7c);
        return max_ref(d, zero);
    }
    return 0;
}

// @ 0x00c45510
// Round-trip travel cost between the origin and the target planet.
int cSPMission::GetTotalTravelCost()
{
    cPlanet* origin = mpOriginPlanet9c;
    if (origin == 0)
        return 0;
    cPlanet* target = mpTargetPlanet1e8;
    if (target == 0)
        return 0;
    cStarRecord* targetRec = target->mpStarRecord13c;
    cStarRecord* originRec = origin->mpStarRecord13c;
    u32 targetID = targetRec->GetStarID();
    u32 originID = originRec->GetStarID();
    return 2 * GetUFOSimulator(originID)->ComputeCost(targetID);
}

// @ 0x00c45560
float cSPMission::GetTotalTravelCostFloat()
{
    cPlanet* origin = mpOriginPlanet9c;
    if (origin == 0)
        return 0.0f;
    cPlanet* target = mpTargetPlanet1e8;
    if (target == 0)
        return 0.0f;
    cStarRecord* targetRec = target->mpStarRecord13c;
    cStarRecord* originRec = origin->mpStarRecord13c;
    u32 targetID = targetRec->GetStarID();
    u32 originID = originRec->GetStarID();
    return GetUFOSimulator(originID)->ComputeCostFloat(targetID) * 2.0f;
}

// @ 0x00c455b0
// True when the mission's empire is the given one and the mission sits in the
// given comm context, and the mission is in a state that allows a comm call.
bool cSPMission::IsAtStar(int empireID, int commContext)
{
    int state = VT_60_0(this);
    if (state != 3) {
        if (VT_60_0(this) != 5)
            return false;
    }
    if (mpOriginPlanet9c->mpStarRecord13c->GetCommContext() != commContext)
        return 0;
    if (empireID != mEmpireID8c)
        return 0;
    return 1;
}

// @ 0x00c45740
// Reaction id selected by the low flag bit of the mission: -1 when the flag is
// set, otherwise the mission's default reaction.
int cSPMission::GetDynamicResponseID(int a, int b)
{
    (void)a;
    (void)b;
    return (mFlags130 & 1) ? -1 : 0xb6a7851e;
}

// ---------------------------------------------------------------------------------------------
// 0x00c446d0: append/prepend a 16-byte marker to the vector living at +0xf0.
// The destination is an eastl::vector: its fast path is inlined, and both the
// prepend path and the growth path call the vector's out-of-line
// DoInsertValue(position, value) member (`ret 8`, so `this` is the vector in ecx).
// ---------------------------------------------------------------------------------------------
struct cMarker {
    float mx;     // +0x00
    float my;     // +0x04
    float mz;     // +0x08
    int   mFlag;  // +0x0c
};

struct cMarkerVector {            // eastl::vector<cMarker> layout
    cMarker* mpBegin;             // +0x00
    cMarker* mpEnd;               // +0x04
    cMarker* mpCapacity;          // +0x08

    // eastl::vector::insert(position, value) (0x00c43f20): appends in place when
    // the position is the end, otherwise falls through to DoInsertValue.
    void Insert(cMarker* position, const cMarker& value);
    // eastl::vector::DoInsertValue(position, value) (0x00c43cc0): shifts/grows.
    void DoInsertValue(cMarker* position, const cMarker& value);

    // eastl::vector::push_back's spare-capacity path is inlined in AddMarker
    // below; when the vector is full it calls DoInsertValue as well.
};

struct cMarkerOwner {
    u8 mPad0000[0xf0];
    cMarkerVector mMarkers;       // +0x0f0

    void AddMarker(const float* pos, bool front);
};

// @ 0x00c446d0
// `front` selects insert-at-begin, otherwise the entry is appended.
void cMarkerOwner::AddMarker(const float* pos, bool front)
{
    // The coordinates and the flag are also kept in their own locals: retail
    // loads them into xmm0..xmm2/edx and keeps them live across the branch, so
    // the push_back fast path below can fill the new element straight from
    // those registers while the same values are already stored in the
    // temporary that the two out-of-line paths pass by reference.
    float x = pos[0];
    float y = pos[1];
    float z = pos[2];
    int   flag = front ? 1 : 0;
    cMarker marker = { x, y, z, flag };

    cMarkerVector& v = mMarkers;      // takes the vector's address once
    if (front) {
        v.Insert(v.mpBegin, marker);
    } else if (v.mpEnd < v.mpCapacity) {
        // eastl::vector::push_back, spare-capacity path
        cMarker* p = v.mpEnd++;
        if (p) {
            p->mx = x;
            p->my = y;
            p->mz = z;
            p->mFlag = flag;
        }
    } else {
        v.DoInsertValue(v.mpEnd, marker);
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00c44080: SP::cLocomotiveObject::ExecuteSteeringFunctions.
//
// Layout recovered from the body and from the already-reconstructed neighbours:
// the "members" at +0x208..+0x250 are the object's SP::tNavigationGoal (at +0x1f4):
//   +0x208 = goal.nextWaypoint.position      +0x214 = nextWaypoint.radius
//   +0x218 = nextWaypoint.flags              +0x21c/+0x228/+0x234 = nextWaypoint avoidance points
//   +0x244 = goal.facing                     +0x250 = goal.movementMode
// The lazily constructed static at 0x168e748 is an SP::tSteeringData (its ctor is
// 0x00c433f0, its dtor is registered at 0x013c3900), and 0x168e7cc is its `forces`
// vector of 0x2c-byte SP::tForceData records.
//
// Each frame the function builds a steering force towards the goal (a constant force
// towards the last path waypoint, refined by the waypoint's three avoidance points),
// lets the registered steering functions add their own forces, and returns the sum.
// When the summed force is too short it drops hint forces (priority 0), then suggested
// ones (priority 1), and re-evaluates.
// ---------------------------------------------------------------------------------------------
struct Vector3 {
    float x;
    float y;
    float z;
};

struct tNavigationWaypointStub {
    Vector3 position;        // +0x00
    float   radius;          // +0x0c
    int     flags;           // +0x10
    Vector3 avoid0;          // +0x14
    Vector3 avoid1;          // +0x20
    Vector3 avoid2;          // +0x2c
    int     m38;             // +0x38
};

struct tNavigationGoalStub {
    void*   mpPathBegin;             // +0x00  eastl::vector<tNavigationWaypoint>
    void*   mpPathEnd;               // +0x04
    void*   mpPathCap;               // +0x08
    u8      mPad0c[0x14 - 0x0c];
    tNavigationWaypointStub nextWaypoint;  // +0x14
    Vector3 facing;                  // +0x50
    int     movementMode;            // +0x5c
    float   acceptableStopDistance;  // +0x60
    float   stopFacing;              // +0x64
    float   cachedDistanceToGoal;    // +0x68
    float   noProgressTime;          // +0x6c
    int     movementFlags;           // +0x70
    tNavigationGoalStub& operator=(tNavigationGoalStub const&);  // 0x00c43de0
};

struct tForceDataStub {
    int     forceType;       // +0x00  tForceData::eForceType
    int     forcePriority;   // +0x04  tForceData::eForcePriority
    Vector3 dir;             // +0x08
    float   magnitude;       // +0x14
    u8      mPad18[0x2c - 0x18];
};

struct ForceVectorStub {
    tForceDataStub* mpBegin;
    tForceDataStub* mpEnd;
    tForceDataStub* mpCap;

    void DoInsertValue(tForceDataStub* position, tForceDataStub const& value);  // 0x00b47600
    void Erase(tForceDataStub* first, tForceDataStub* last);                    // 0x00fea240
};

struct tSteeringDataStub {
    Vector3            curPosition;  // +0x00
    tNavigationGoalStub goal;        // +0x0c
    void*              pEntity;      // +0x80
    ForceVectorStub    forces;       // +0x84
    tSteeringDataStub() throw();     // 0x00c433f0
    ~tSteeringDataStub() throw();    // 0x013c3900
};

// 0x00c41dc0
void ChoosePair(const Vector3* v, Vector3 p, Vector3* out0, Vector3* out1);
// 0x00c42650
bool SegmentsNear(const Vector3* a1, const Vector3* a2, const Vector3* b1,
                  const Vector3* b2, Vector3* out);
// 0x00b3d310
void* GetGameManager();
// 0x01488874 / 0x0146d060 / 0x013eb1bc
extern const float kMinForceLength;
extern const float kGoalPointRadiusSq;
extern const float kUnitMagnitude;

struct cRoadStub {
    void* mpVtable;                  // +0x00
    u8 mPad04[0x1f4 - 0x04];
    tNavigationGoalStub mGoal;       // +0x1f4
    u8 mPad268[0x490 - 0x268];
    void** mpFnBegin;                // +0x490  sp_fixed_vector<void (*)(tSteeringData&), 4>
    void** mpFnEnd;                  // +0x494

    Vector3 const& GetPosition();                    // vtable slot 11, 0x00c41e00-ish
    Vector3 GetSteeringDirection();                  // vtable slot 23 (returns by value)
    Vector3* GetGoalPosition();                      // 0x00c42de0
    bool IsWithinGoalRadius(float radius);           // 0x00c42210
    Vector3 EvaluateForces(tSteeringDataStub& sd);   // 0x00c42710
    Vector3 ExecuteSteeringFunctions();
};

static inline Vector3 const& RoadGetPosition(cRoadStub* self)
{
    return ((Vector3 const& (__thiscall*)(cRoadStub*))(*(void***)self)[11])(self);
}

static inline Vector3 RoadGetSteeringDirection(cRoadStub* self)
{
    Vector3 out;
    ((Vector3* (__thiscall*)(cRoadStub*, Vector3*))(*(void***)self)[23])(self, &out);
    return out;
}

// @ 0x00c44080
Vector3 cRoadStub::ExecuteSteeringFunctions()
{
    static tSteeringDataStub sd;

    sd.curPosition = RoadGetPosition(this);
    sd.goal = mGoal;
    sd.pEntity = this;
    sd.forces.Erase(sd.forces.mpBegin, sd.forces.mpEnd);

    if (mGoal.movementMode != 0) {
        tNavigationWaypointStub const& wp = mGoal.nextWaypoint;
        float dx = wp.position.x - sd.curPosition.x;
        float dy = wp.position.y - sd.curPosition.y;
        float dz = wp.position.z - sd.curPosition.z;
        float distSq = dz * dz + dx * dx + dy * dy;

        // Already standing at the stop point facing the right way: no steering needed.
        if (mGoal.movementMode == 3 && distSq <= wp.radius * wp.radius)
            return mGoal.facing;

        tForceDataStub force;
        force.forcePriority = 1;
        if (sd.forces.mpEnd < sd.forces.mpCap) {
            tForceDataStub* p = sd.forces.mpEnd++;
            if (p)
                p->forcePriority = 1;
        } else {
            sd.forces.DoInsertValue(sd.forces.mpEnd, force);
        }
        tForceDataStub* f = sd.forces.mpEnd - 1;
        f->forcePriority = 1;

        if (wp.flags != 0 && distSq <= kGoalPointRadiusSq) {
            Vector3 goalPos = *GetGoalPosition();
            Vector3 avoid[3];
            avoid[0] = wp.avoid0;
            avoid[1] = wp.avoid1;
            avoid[2] = wp.avoid2;
            Vector3 out0;
            Vector3 out1;
            ChoosePair(avoid, sd.curPosition, &out0, &out1);

            // The next waypoint on the goal path wins over the goal destination itself.
            Vector3 dest;
            if (mGoal.mpPathBegin == mGoal.mpPathEnd)
                dest = goalPos;
            else
                dest = *(Vector3*)((char*)mGoal.mpPathEnd - 0x3c);

            f->forceType = 4;
            f->magnitude = kUnitMagnitude;
            if (SegmentsNear(&goalPos, &out1, &out0, &sd.curPosition, &dest))
                f->dir = dest;
            else
                f->dir = goalPos;
        } else {
            f->forceType = 4;
            f->dir = *GetGoalPosition();
            f->magnitude = kUnitMagnitude;
        }
    }

    if (mGoal.movementMode != 3 || !IsWithinGoalRadius(mGoal.nextWaypoint.radius)) {
        void** p = mpFnBegin;
        void** end = mpFnEnd;
        while (p != end) {
            ((void (__cdecl*)(tSteeringDataStub&))*p)(sd);
            ++p;
        }
    }

    // Nothing produced a force: steer straight along the current heading.
    if (sd.forces.mpBegin == sd.forces.mpEnd) {
        tForceDataStub force;
        force.forcePriority = 1;
        if (sd.forces.mpEnd < sd.forces.mpCap) {
            tForceDataStub* p = sd.forces.mpEnd++;
            if (p)
                p->forcePriority = 1;
        } else {
            sd.forces.DoInsertValue(sd.forces.mpEnd, force);
        }
        tForceDataStub* f = sd.forces.mpEnd - 1;
        f->forceType = 2;
        f->dir = RoadGetSteeringDirection(this);
    }

    int retried = 0;
    for (;;) {
        Vector3 result = EvaluateForces(sd);
        if (*(int*)((char*)GetGameManager() + 0x20) == 0)
            return result;
        float length = sqrtf(result.x * result.x + result.z * result.z + result.y * result.y);
        if (length >= kMinForceLength)
            return result;

        // Nothing left to prune: coast along the current heading at the minimum speed.
        if (sd.forces.mpBegin == sd.forces.mpEnd) {
            Vector3 dir = RoadGetSteeringDirection(this);
            Vector3 scaled;
            scaled.x = dir.x * kMinForceLength;
            scaled.y = dir.y * kMinForceLength;
            scaled.z = dir.z * kMinForceLength;
            return scaled;
        }

        tForceDataStub* it = sd.forces.mpBegin;
        int count = (int)(sd.forces.mpEnd - sd.forces.mpBegin);
        int i = 0;
        for (; i < count; ++i, ++it) {
            if (it->forcePriority == retried)
                break;
        }
        if (i != count) {
            *it = *(sd.forces.mpEnd - 1);
            --sd.forces.mpEnd;
            continue;
        }
        if (retried != 0)
            return result;
        retried = 1;
    }
}
