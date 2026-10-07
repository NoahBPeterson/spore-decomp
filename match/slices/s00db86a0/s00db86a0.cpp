// slice s00db86a0: group-follow update (Claude-coined name cGroupFollower::Update).
// A leader object (+0x18c) is followed along an A* path (+0x08, eastl::vector<Waypoint>) toward a
// target (+0x190); each member (+0x1c, vector of objects) is steered to its slot of a formation
// (+0x1d4).  Per-member bookkeeping lives in a hash_map<Object*, MemberInfo> at +0x54.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)
inline float sqrtf(float x) { return (float)sqrt((double)x); }

#define PV(n) virtual void pad##n();

struct Vector3 {
    float x, y, z;
};
struct Quaternion {
    float x, y, z, w;
};
struct Matrix3 {
    float m[3][3];
};

bool operator!=(const Vector3& a, const Vector3& b);                     // 0x0041dd30
void Matrix3FromQuaternion(Matrix3* out, const Quaternion* q);           // 0x0059c190

// one waypoint of an A* path (0x3c bytes; copy ctor 0x00ac1ff0)
struct Waypoint {
    Vector3 pos;      // 0x00
    float weight;     // 0x0c
    int flags;        // 0x10
    Vector3 v14;      // 0x14
    Vector3 v20;      // 0x20
    Vector3 v2c;      // 0x2c
    bool b38;         // 0x38
    Waypoint(const Vector3& p) : pos(p), weight(1.0f), flags(0), b38(false) {}
    Waypoint(const Waypoint& o);
};

struct WaypointVector {   // eastl::vector<Waypoint>
    Waypoint* mpBegin;
    Waypoint* mpEnd;
    Waypoint* mpCapacity;
    int mAllocator;
    Waypoint* erase(Waypoint* first, Waypoint* last);   // 0x00ac4570
    void push_back(const Waypoint& v);                  // 0x00ac4de0
    void clear() { erase(mpBegin, mpEnd); }
    int size() const { return (int)(mpEnd - mpBegin); }
    Waypoint& operator[](int i) { return mpBegin[i]; }
};

struct CastIface {   // result of Cast(0x017f243b)
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual bool IsBusy();   // 0x2c
};

struct LocoState {
    char pad0[0x5c];
    int mHasGoal;            // 0x5c
    const Vector3* GetGoal();                 // 0x00c423c0
};

struct Object;

struct Creature {   // SP::cSPCreatureBase (Cast 0xce9f6639)
    char pad0[0xf90];
    bool bF90;               // 0xf90
    int GetMode();                            // 0x00c0c2f0
    void MoveToPointAtSpeed(int how, const Vector3* pos, float a, float b);   // 0x00c1c1d0
};

struct Object {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual const Vector3* GetPosition();      // 0x2c
    PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21)
    virtual bool v58(int);                     // 0x58
    PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30) PV(31) PV(32)
    PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42)
    PV(43) PV(44) PV(45)
    virtual void* Cast(uint32_t id);           // 0xb8
    PV(47)
    virtual void vc0();                        // 0xc0
    PV(49) PV(50) PV(51) PV(52) PV(53) PV(54) PV(55)
    virtual void MoveTo(const Vector3* pos, float a, float b, int c);   // 0xe0
    PV(57) PV(58)
    virtual void StopMoving();                 // 0xec

    char fpad4[0x75 - 4];
    bool mbAlive;                              // 0x75

    LocoState* GetLoco();                      // 0x00c41ec0
    bool IsNearGoal();                         // 0x00c42e20
};

// same object seen through an interface whose slot 0x58 takes no argument
struct ObjectView {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21)
    virtual bool v58();                        // 0x58
};

struct PlanetModel {
    void BuildSurfaceOrientation(Quaternion* out, const Vector3* pos);   // 0x00b7f190
    Vector3 DirectionToSurfacePosition(const Vector3& dir);              // 0x00b815a0
};
PlanetModel* GetPlanetModel();                 // 0x00b3d350

struct cGroupFollower;
struct AStarMethod { int unused; };
extern AStarMethod gAStarSearchLandAvoidCities;    // 0x01565b68

struct Pathfinder {
    void Cancel(cGroupFollower* owner);        // 0x00ac4ef0
    void FindPath(AStarMethod* method, const Vector3* start, const Vector3* goal, float a, float b,
                  WaypointVector* out, cGroupFollower* owner, int canSwim);   // 0x00ac65d0
};
Pathfinder* GetPathfinder();                   // 0x00b3d290

struct FormationSlot {   // 0x18 bytes
    bool mbTaken;          // 0x00
    char pad1[7];
    int mOwnerRef;         // 0x08
    Vector3 mOffset;       // 0x0c
    int GetOwner();                            // 0x00fcc210
    void Assign(int who);                      // 0x00afa030
};

struct Formation {
    char pad0[0x14];
    Vector3 mPosition;     // 0x14
    char pad20[0x2c - 0x20];
    Quaternion mOrientation;  // 0x2c
    char pad3c[0x64 - 0x3c];
    bool IsPlaced();                                                      // 0x00af9ee0
    void Place(const Vector3* pos, const Quaternion* q, float spacing);   // 0x00af9d60
    void Layout(int a, float spacing);                                    // 0x00afef10
    void Reset();                                                         // 0x00afafd0
    FormationSlot* GetSlot(int index);                                    // 0x00af9ff0
};

struct MemberInfo {
    float mTimeNear;      // 0x0
    float mDistSq;        // 0x4
    int mSlot;            // 0x8
};

struct MemberMap {   // eastl::hash_map<Object*, MemberInfo>
    char pad[0x20];
    MemberInfo& operator[](Object* const& key);   // 0x00db5cf0
};

typedef void (*FollowCallback)(cGroupFollower* self, Formation* f, int b);

extern float gGroupMinSpeed;   // 0x01572070
extern float gGroupMaxSpeed;   // 0x0157206c

template <class T> inline const T& max_(const T& a, const T& b) { return (a < b) ? b : a; }

struct cGroupFollower {
    char pad0[8];
    WaypointVector mPath;            // 0x08
    char pad18[4];
    Object** mMembersBegin;          // 0x1c
    Object** mMembersEnd;            // 0x20
    char pad24[0x54 - 0x24];
    MemberMap mInfo;                 // 0x54
    char pad74[0x18c - 0x74];
    Object* mpLeader;                // 0x18c
    Object* mpTarget;                // 0x190
    Vector3 mTargetPos;              // 0x194
    Vector3 mPathGoal;               // 0x1a0
    float mRepathTimer;              // 0x1ac
    float mRepathInterval;           // 0x1b0
    float mSpacing;                  // 0x1b4
    float m1b8;                      // 0x1b8
    float mRadius;                   // 0x1bc
    float m1c0;                      // 0x1c0
    float mSpread;                   // 0x1c4
    float mAvgDistSq;                // 0x1c8
    int mState;                      // 0x1cc
    bool mbReset;                    // 0x1d0
    bool mbRepath;                   // 0x1d1
    char pad1d2[2];
    Formation mFormation;            // 0x1d4
    FollowCallback mCallback;        // 0x238
    char pad23c[4];
    int mPathIndex;                  // 0x240

    void ResetMembers();                       // 0x00daad10
    void ApplyFormation(Matrix3* m);           // 0x00db80c0
    void Update(float dt);
};

void cGroupFollower::Update(float dt) {
    if (!((mRepathTimer -= dt) < 0.0f || mbRepath))
        return;
    if (mMembersBegin == mMembersEnd)
        return;

    mRepathTimer = mRepathInterval;
    if (mbReset) {
        ResetMembers();
        mbReset = false;
    }

    if (mpTarget) {
        if (!mpTarget->mbAlive) {
            Object* t = mpTarget;
            if (t) {
                mpTarget = 0;
                t->vc0();
            }
            return;
        }
        CastIface* ci;
        if (!mpTarget || !(ci = (CastIface*)mpTarget->Cast(0x017f243b)) || !ci->IsBusy()) {
            Vector3 pos = *mpTarget->GetPosition();
            if (mTargetPos != pos) {
                mTargetPos = pos;
                float r = mRadius;
                if (r > 0.0f)
                    r = r * r;
                else
                    r = 100.0f;
                float dz = mPathGoal.z - mTargetPos.z;
                float dy = mPathGoal.y - mTargetPos.y;
                float dx = mPathGoal.x - mTargetPos.x;
                mbRepath = (dz * dz + dy * dy + dx * dx > r) ? true : false;
                if (mbRepath)
                    mPathGoal = pos;
            }
        }
    }

    float spacing = mSpacing * 2.0f;
    bool grew = false;
    float spread = sqrtf((float)(int)(mMembersEnd - mMembersBegin) * spacing * spacing);
    if (spread > mSpread) {
        grew = true;
        mSpread = spread;
    }
    spacing += mSpread;

    if (mbRepath) {
        mPathIndex = 0;
        mPath.clear();
        const Vector3* lp = mpLeader->GetPosition();
        float dz = lp->z - mTargetPos.z;
        float dy = lp->y - mTargetPos.y;
        float dx = lp->x - mTargetPos.x;
        if (dz * dz + dy * dy + dx * dx > 10000.0f) {
            GetPathfinder()->Cancel(this);
            Object* leader = mpLeader;
            GetPathfinder()->FindPath(&gAStarSearchLandAvoidCities, leader->GetPosition(), &mTargetPos,
                                      m1b8, mRadius, &mPath, this, leader->v58(0));
        } else {
            mPath.push_back(Waypoint(mTargetPos));
        }
        mbRepath = false;
        mState = 1;
    }

    if (mPath.mpBegin == mPath.mpEnd)
        return;

    Vector3 wp = mPath[mPathIndex].pos;
    bool isLast = mPathIndex == mPath.size() - 1;
    if (isLast) {
        wp = mTargetPos;
    } else {
        const Vector3* lp = mpLeader->GetPosition();
        float dx = lp->x - wp.x;
        float dz = lp->z - wp.z;
        float dy = lp->y - wp.y;
        if (spacing * spacing > dx * dx + dz * dz + dy * dy) {
            mPathIndex += 1;
            wp = mPath[mPathIndex].pos;
            mState = 1;
        }
    }

    PlanetModel* planet = GetPlanetModel();
    Quaternion orient;
    planet->BuildSurfaceOrientation(&orient, &wp);
    Matrix3 mat;
    Matrix3FromQuaternion(&mat, &orient);

    if (mFormation.IsPlaced() && !grew) {
        Vector3 p = wp;
        mFormation.mPosition = p;
        mFormation.mOrientation = orient;
    } else {
        mFormation.Place(&wp, &orient, spacing);
        mFormation.Layout(0, mSpacing);
    }

    int mode;
    bool flag;
    Creature* cr;
    if (mpLeader && (cr = (Creature*)mpLeader->Cast(0xce9f6639)) != 0) {
        mode = cr->GetMode();
        flag = cr->bF90;
    } else {
        mode = 2;
        flag = false;
    }
    if (mCallback && (((ObjectView*)mpLeader)->v58() || mode == 2 || (flag && mode == 1)))
        mCallback(this, &mFormation, 1);
    else
        mFormation.Reset();

    if (mState == 2 || mState == 1) {
        ApplyFormation(&mat);
        mState = 0;
    }

    mAvgDistSq = 0.0f;
    float minSpeed = gGroupMinSpeed;
    float maxSpeed = gGroupMaxSpeed;
    if (isLast && mRadius > 1.5258789e-05f) {
        minSpeed = max_(minSpeed, mRadius);
        maxSpeed = max_(maxSpeed, mRadius);
    }

    for (Object **it = mMembersBegin, **itEnd = mMembersEnd; it != itEnd; ++it) {
        Object* obj = *it;
        int key;
        if (obj)
            key = (int)obj->Cast(0x017f243b);
        else
            key = 0;
        MemberInfo& info = mInfo[obj];
        Vector3 target = mTargetPos;
        if (info.mSlot == -2) {
            const Vector3* p = obj->GetPosition();
            float dx = p->x - mTargetPos.x;
            float dz = p->z - mTargetPos.z;
            float dy = p->y - mTargetPos.y;
            mAvgDistSq += dx * dx + dz * dz + dy * dy;
        } else {
            FormationSlot* slot;
            if (info.mSlot < 0 || (slot = mFormation.GetSlot(info.mSlot)) == 0) {
                obj->StopMoving();
                mState = 2;
                continue;
            }
            if (slot->mbTaken && (slot->mOwnerRef != 0 || slot->GetOwner() != key)) {
                obj->StopMoving();
                info.mSlot = -1;
                mState = 2;
                mRepathTimer = 0.0f;
                continue;
            }
            slot->Assign(key);
            const Vector3& o = slot->mOffset;
            Vector3 dir;
            dir.x = o.z * mat.m[2][0] + o.y * mat.m[1][0] + o.x * mat.m[0][0] + wp.x;
            dir.y = o.x * mat.m[0][1] + o.z * mat.m[2][1] + o.y * mat.m[1][1] + wp.y;
            dir.z = o.x * mat.m[0][2] + o.z * mat.m[2][2] + o.y * mat.m[1][2] + wp.z;
            target = planet->DirectionToSurfacePosition(dir);
            const Vector3* p = obj->GetPosition();
            float dz = p->z - target.z;
            float dx = p->x - target.x;
            float dy = p->y - target.y;
            float d = dx * dx + dz * dz + dy * dy;
            info.mDistSq = d;
            mAvgDistSq += d;
        }

        if (info.mTimeNear < 1.5258789e-05f) {
            LocoState* loco = obj->GetLoco();
            bool move = true;
            if (loco->mHasGoal != 0) {
                const Vector3* g = loco->GetGoal();
                float dx = g->x - target.x;
                float dz = g->z - target.z;
                float dy = g->y - target.y;
                move = dx * dx + dz * dz + dy * dy > minSpeed * minSpeed;
            }
            if (move) {
                Creature* c = (Creature*)obj->Cast(0xce9f6639);
                if (c)
                    c->MoveToPointAtSpeed(2, &target, minSpeed, maxSpeed);
                else
                    obj->MoveTo(&target, minSpeed, maxSpeed, 0);
            }
        }
        if (obj->IsNearGoal() && isLast)
            mInfo[obj].mTimeNear += dt;
    }

    mAvgDistSq = mAvgDistSq / (float)(unsigned)(mMembersEnd - mMembersBegin);
}
