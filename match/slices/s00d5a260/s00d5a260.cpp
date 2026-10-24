// Slice s00d5a260: locomotion steering update for a creature following a locomotion request
// (path of waypoints, stop distances, gait switch walk/run). Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-.
#include "types.h"
#include <math.h>
#include <string.h>
#pragma intrinsic(sqrt)

void __cdecl operator delete[](void* p);                   // 0x00f47380

struct Vec3 { float x, y, z; };
struct Waypoint { float f[15]; };                          // 0x3c bytes

// Request the creature's locomotion object is working on (Spore ModAPI: cLocomotionRequest), 0x74 bytes.
struct LocRequest {
    Waypoint* mpBegin;                                     // +0x00 waypoint vector
    Waypoint* mpEnd;                                       // +0x04
    char      pad08[0x14 - 0x08];
    Vec3      mDst;                                        // +0x14 (start of the current 0x3c-byte waypoint)
    float     mGoalStopDistance;                           // +0x20
    char      pad24[0x50 - 0x24];
    Vec3      mField50;                                    // +0x50 (reference direction)
    int       mType;                                       // +0x5c (0 none, 1/3 follow, 2 hold)
    float     mAcceptableStopDistance;                     // +0x60
    float     mField64;                                    // +0x64 (alignment threshold)
    float     mPrevDistance;                               // +0x68
    float     mElapsed;                                    // +0x6c
    int       mField70;                                    // +0x70

    LocRequest(const LocRequest& o);                       // 0x00b46d90 (copy ctor, thiscall ret 4)
    LocRequest() {}
    ~LocRequest()                                          // heap block freed through the array cookie check
    {
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            operator delete[](mpBegin);
    }
    void EraseWaypoint(const Waypoint* pos);               // 0x00b47520 (vector::erase, thiscall ret 4)
};

extern float gDefaultDstX;                                 // 0x0169ec28 (default request position)
extern float gDefaultDstY;                                 // 0x0169ec2c
extern float gDefaultDstZ;                                 // 0x0169ec30
extern const float gMaxApproach;                           // 0x01583e68

struct cLocoObj {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a();
    virtual const Vec3* GetPosition();                     // 0x2c
    virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15(); virtual void v16();
    virtual const Vec3* GetDirection(Vec3* out);           // 0x5c
    virtual void v18(); virtual void v19(); virtual void v1a(); virtual void v1b();
    virtual void v1c(); virtual void v1d(); virtual void v1e(); virtual void v1f();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v2a(); virtual void v2b();
    virtual void v2c(); virtual void v2d(); virtual void v2e(); virtual void v2f();
    virtual void v30();
    virtual void SetDesiredSpeed(float speed, int flag);   // 0xc4
    virtual float GetDesiredSpeed();                       // 0xc8
    virtual float v33();
    virtual float funcD0h();                               // 0xd0
    virtual void v35(); virtual void v36();
    virtual void SetRequest(const LocRequest& r);          // 0xdc

    char pad04[0x1e8 - 4];
    float mTurnRate;                                       // +0x1e8
    Vec3* GetVelocity();                                   // 0x00d20610 (lea eax,[ecx+0x1c8])
    void  GetSteerDirection(Vec3* out);                    // 0x00c44080
    LocRequest* GetRequest();                              // 0x00c41ec0 (lea eax,[ecx+0x1f4])
};

struct cWalkerInfo { char pad[0x698]; unsigned mState; };
struct cCreature {
    char pad0[0x2b0];
    int  mAnimMode;                                        // +0x2b0
    char pad2b4[0xb20 - 0x2b4];
    cWalkerInfo* mpInfo;                                   // +0xb20
    void InterruptAnimation(unsigned id, int a, int b);    // 0x00c12310
};

struct cPlanetModel {
    Vec3* DirectionToSurfacePosition(Vec3* out, const Vec3* dir);   // 0x00b815a0
};
cPlanetModel* __cdecl PlanetModel();                       // 0x00b3d350
Vec3* __cdecl NormalizedSafe(Vec3* out, const Vec3* in);   // 0x00449c20

struct cSteerCtx {
    Vec3  out;                                             // +0x00 steering velocity written here
    char  pad0c[4];
    float dt;                                              // +0x10
    cLocoObj* obj;                                         // +0x14
};

struct cFollowBehavior {
    char pad0[0x10];
    cCreature* mpCreature;                                 // +0x10
    bool mbRun;                                            // +0x14
    float Approach(cLocoObj* obj, const Vec3* target, float dt, float speed, float turn);  // 0x00d59b00
    void Update(cSteerCtx* ctx);                           // 0x00d5a260
};

static inline float SqLen(const Vec3& d)
{
    return (float)sqrt(d.z * d.z + d.y * d.y + d.x * d.x);
}

// @ 0x00d5a260
void cFollowBehavior::Update(cSteerCtx* ctx)
{
    cLocoObj* obj = ctx->obj;
    obj->funcD0h();
    obj->GetVelocity();
    Vec3 dir;
    obj->GetSteerDirection(&dir);
    float dirLen = (float)sqrt(dir.y * dir.y + dir.z * dir.z + dir.x * dir.x);
    if (1.52587890625e-05f <= dirLen) {
        float inv = 1.0f / dirLen;
        dir.x = inv * dir.x;
        dir.y = dir.y * inv;
        dir.z = dir.z * inv;
    } else {
        Vec3 tmp;
        const Vec3* d = obj->GetDirection(&tmp);
        dir.x = d->x * 0.1f;
        dir.y = d->y * 0.1f;
        dir.z = d->z * 0.1f;
    }

    const Vec3* pp = obj->GetPosition();
    Vec3 pos;
    pos.x = pp->x;
    pos.y = pp->y;
    pos.z = pp->z;
    Vec3 fwd;
    obj->GetDirection(&fwd);
    float speed = obj->GetDesiredSpeed();
    float turn = obj->mTurnRate;
    LocRequest* req = obj->GetRequest();
    PlanetModel();

    int type = req->mType;
    float dist;
    if (type == 0) {
        dist = 0.0f;
    } else {
        float dz = pos.z - req->mDst.z, dy = pos.y - req->mDst.y, dx = pos.x - req->mDst.x;
        dist = (float)sqrt(dz * dz + dy * dy + dx * dx);
    }
    bool notHold3 = type != 3;
    bool stop = false;
    if (type == 0) {
        speed = 0.0f;
    } else if (type != 2) {
        float prev = req->mPrevDistance;
        bool progressed = false;
        if (dist >= prev) {
            req->mElapsed = ctx->dt + req->mElapsed;
            progressed = true;
        }
        if (req->mGoalStopDistance > dist) {
            stop = true;
        } else if (ctx->dt * speed < dist) {
            if (progressed && req->mAcceptableStopDistance > dist)
                stop = true;
        } else {
            speed = (dist / ctx->dt) * 0.95f;
        }
        req->mPrevDistance = dist;
        if (stop) {
            if (req->mpBegin == req->mpEnd) {
                speed = 0.0f;
            } else {
                req->mElapsed = 0.0f;
                Waypoint* first = req->mpBegin;
                *(Waypoint*)&req->mDst = *first;
                req->EraseWaypoint(first);
                stop = false;
                float dz = pos.z - req->mDst.z, dy = pos.y - req->mDst.y, dx = pos.x - req->mDst.x;
                dist = (float)sqrt(dz * dz + dy * dy + dx * dx);
            }
        }
    }

    if (req->mType != 0 && dist < (speed / turn) * 2.0f) {
        float dz = req->mDst.z - pos.z, dy = req->mDst.y - pos.y, dx = req->mDst.x - pos.x;
        float inv = 1.0f / (float)sqrt(dz * dz + dy * dy + dx * dx + 1e-08f);
        float dot = fwd.z * (dz * inv) + fwd.y * (dy * inv) + (inv * dx) * fwd.x;
        if (dot < 0.5f) {
            float cap = (dist * turn) * 0.5f;
            const float* p = &cap;
            if (speed <= cap) p = &speed;
            speed = *p;
        }
    }

    Vec3 target;
    target.z = pos.z + dir.z;
    target.x = pos.x + dir.x;
    target.y = pos.y + dir.y;
    float moved = Approach(ctx->obj, &target, ctx->dt, speed, turn);
    if (moved <= 0.0f) {
        mpCreature->mAnimMode = 0;
        ctx->out.x = 0.0f;
        ctx->out.y = 0.0f;
        ctx->out.z = 0.0f;
    } else {
        mpCreature->mAnimMode = 5;
        ctx->out.x = dir.x * speed;
        ctx->out.y = dir.y * speed;
        ctx->out.z = dir.z * speed;
        bool oldRun = mbRun;
        if (!oldRun) {
            if (dist > 6.0f) mbRun = true;
        } else {
            if (3.0f > dist) mbRun = false;
        }
        float dt = ctx->dt;
        Vec3 next;
        next.x = dt * ctx->out.x + pos.x;
        next.y = dt * ctx->out.y + pos.y;
        next.z = dt * ctx->out.z + pos.z;
        Vec3 ground;
        PlanetModel()->DirectionToSurfacePosition(&ground, &next);
        float h = (float)sqrt(next.x * next.x + next.z * next.z + next.y * next.y) -
                  (float)sqrt(ground.x * ground.x + ground.y * ground.y + ground.z * ground.z);
        Vec3 nbuf;
        const Vec3* nd;
        float amount;
        if (!mbRun) {
            if (0.0f <= h) {
                float t = (h / ctx->dt) * -1.0f;
                float lo = -1.0f;
                const float* p = &t;
                if (t <= -1.0f) p = &lo;
                nd = NormalizedSafe(&nbuf, &next);
                amount = *p;
            } else {
                float t = (h / ctx->dt) * -1.0f;
                nd = NormalizedSafe(&nbuf, &next);
                amount = t;
            }
        } else {
            if (0.0f <= h) {
                float t = (6.0f - h) / ctx->dt;
                const float* p = &t;
                if (gMaxApproach <= t) p = &gMaxApproach;
                nd = NormalizedSafe(&nbuf, &next);
                amount = *p;
            } else {
                float t = ((h - 0.1f) / ctx->dt) * -1.0f;
                nd = NormalizedSafe(&nbuf, &next);
                amount = t;
            }
        }
        ctx->out.x = nd->x * amount + ctx->out.x;
        ctx->out.z = nd->z * amount + ctx->out.z;
        ctx->out.y = nd->y * amount + ctx->out.y;
        if (mbRun != oldRun) {
            cCreature* c = mpCreature;
            if (!mbRun)
                c->InterruptAnimation(0x2481db0, -1, 0);
            else if (c->mpInfo->mState <= 0)
                c->InterruptAnimation(0x5261d78, -1, 0);
            else
                c->InterruptAnimation(0x77300fb, -1, 0);
        }
    }

    if (!notHold3) {
        Vec3 q2;
        const Vec3* q = obj->GetDirection(&q2);
        float d = q->z * req->mField50.z + q->y * req->mField50.y + q->x * req->mField50.x;
        notHold3 = true;
        if (!(d > req->mField64))
            notHold3 = false;
    }

    if (stop) {
        if (notHold3) {
            LocRequest goal;
            goal.mpBegin = 0;
            ((int*)&goal)[1] = 0;
            ((int*)&goal)[2] = 0;
            goal.mDst.x = gDefaultDstX;
            goal.mDst.y = gDefaultDstY;
            goal.mDst.z = gDefaultDstZ;
            goal.mGoalStopDistance = 1.0f;
            *(int*)&goal.pad24[0] = 0;
            *(char*)&goal.pad24[0x28] = 0;
            goal.mField50.x = 0.0f;
            goal.mField50.y = 0.0f;
            goal.mField50.z = 0.0f;
            goal.mType = 0;
            goal.mAcceptableStopDistance = 2.0f;
            goal.mField64 = 0.9f;
            goal.mPrevDistance = 3.402823466e+38f;
            goal.mElapsed = 0.0f;
            goal.mField70 = 0;
            ctx->obj->SetRequest(goal);
            ctx->obj->SetDesiredSpeed(0.0f, 1);
            ctx->out.x = 0.0f;
            ctx->out.y = 0.0f;
            ctx->out.z = 0.0f;
        } else {
            LocRequest goal(*ctx->obj->GetRequest());
            goal.mDst.x = pos.x;
            goal.mDst.y = pos.y;
            goal.mDst.z = pos.z;
            ctx->obj->SetRequest(goal);
        }
    }
}

// ===========================================================================
// Container helpers and tribe trail update in the same translation unit.
// ===========================================================================

void __cdecl operator delete(void* p);                     // 0x00f47380
typedef uint32_t u32;

// ---------------------------------------------------------------------------
// 0x00d5aae0 -- erase every element equal to *ppValue from a vector of
// reference-counted pointers, keeping the remaining elements in order.
// ---------------------------------------------------------------------------
struct RefCounted
{
    virtual void AddRef();                                 // slot 0
    virtual void Release();                                // slot 1
};

struct RefPtr
{
    RefCounted* mpObject;                                  // +0x00

    RefPtr& operator=(const RefPtr& other)
    {
        if (mpObject != other.mpObject)
        {
            if (other.mpObject != 0)
                other.mpObject->AddRef();
            RefCounted* old = mpObject;
            mpObject = other.mpObject;
            if (old != 0)
                old->Release();
        }
        return *this;
    }
};

struct RefPtrVector
{
    RefPtr* mpBegin;                                       // +0x00
    RefPtr* mpEnd;                                         // +0x04
    RefPtr* mpCapacity;                                    // +0x08

    void erase(RefPtr* first, RefPtr* last);               // 0x00e25bd0
};

int __cdecl EraseRefValue(RefPtrVector* vec, const RefPtr* pValue);

// @ 0x00d5aae0
int __cdecl EraseRefValue(RefPtrVector* vec, const RefPtr* pValue)
{
    RefPtr* first = vec->mpBegin;
    RefPtr* last = vec->mpEnd;
    RefCounted* target = pValue->mpObject;
    if (first != last)
    {
        do
        {
            if (first->mpObject == target)
                break;
            ++first;
        } while (first != last);
    }

    RefPtr* newEnd = first;
    if (first != last)
    {
        do
        {
            if (first->mpObject != pValue->mpObject)
                *newEnd++ = *first;
            ++first;
        } while (first != last);

        if (newEnd != last)
        {
            vec->erase(newEnd, last);
            return (int)(last - newEnd);
        }
    }
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00d5acc0 -- swap two fixed-capacity Vector3 vectors.  Equal allocator
// tags allow a straight pointer swap; otherwise copy through a temporary.
// ---------------------------------------------------------------------------
struct Vec3AllocVector
{
    Vec3* mpBegin;                                         // +0x00
    Vec3* mpEnd;                                           // +0x04
    Vec3* mpCapacity;                                      // +0x08
    uint32_t mAllocTag;                                    // +0x0c
    Vec3* mpInlineBuffer;                                  // +0x10
    uint32_t mAllocField14;                                // +0x14

    void CopyConstruct(const Vec3AllocVector& src);        // 0x00d59750
    Vec3AllocVector& operator=(const Vec3AllocVector& src);// 0x00d5a010
    void swap(Vec3AllocVector& other);                     // 0x00d5acc0
};

// @ 0x00d5acc0
void Vec3AllocVector::swap(Vec3AllocVector& other)
{
    if (&mAllocTag == &other.mAllocTag)
    {
        Vec3* ob = other.mpBegin;
        Vec3* tb = mpBegin;
        mpBegin = ob;
        other.mpBegin = tb;
        Vec3* te = mpEnd;
        Vec3* oe = other.mpEnd;
        mpEnd = oe;
        other.mpEnd = te;
        Vec3* oc = other.mpCapacity;
        Vec3* tc = mpCapacity;
        mpCapacity = oc;
        other.mpCapacity = tc;
        return;
    }

    Vec3AllocVector tmp;
    tmp.CopyConstruct(*this);
    *this = other;
    other = tmp;
    if (tmp.mpBegin != 0 && tmp.mpBegin != tmp.mpInlineBuffer)
        operator delete(tmp.mpBegin);
}

// ---------------------------------------------------------------------------
// 0x00d5ad40 -- insert a 16-byte value at the end in place when capacity is
// available, otherwise delegate to the growing insert.
// ---------------------------------------------------------------------------
struct Vec4
{
    uint32_t mKey;                                         // +0x00
    float y, z, w;                                         // +0x04
};

struct Vec4Vector
{
    Vec4* mpBegin;                                         // +0x00
    Vec4* mpEnd;                                           // +0x04
    Vec4* mpCapacity;                                      // +0x08

    void InsertGrow(Vec4* pos, const Vec4* value);         // 0x00d5a140
    Vec4* insert(Vec4* pos, const Vec4& value);            // 0x00d5ad40
};

// @ 0x00d5ad40
Vec4* Vec4Vector::insert(Vec4* pos, const Vec4& value)
{
    int index = (int)(pos - mpBegin);
    Vec4* end = mpEnd;
    if (pos == end && end != mpCapacity)
    {
        mpEnd = end + 1;
        if (end != 0)
        {
            end->mKey = value.mKey;
            end->y = value.y;
            end->z = value.z;
            end->w = value.w;
        }
    }
    else
    {
        InsertGrow(pos, &value);
    }
    return mpBegin + index;
}

// ---------------------------------------------------------------------------
// 0x00d5adf0 -- stop every pending sound handle and empty the handle list.
// ---------------------------------------------------------------------------
struct AudioSystem
{
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual u32  Create();                                 // 0x20
    virtual void v24();
    virtual bool IsPlaying(u32 h);                         // 0x28
    virtual void v2c(); virtual void v30(); virtual void v34();
    virtual void Begin(u32 id);                            // 0x38
    virtual void v3c();
    virtual void SetParam(u32 id, u32 value);              // 0x40
    virtual void v44(); virtual void v48(); virtual void v4c(); virtual void v50(); virtual void v54();
    virtual void Commit();                                 // 0x58
};

AudioSystem* GetSystemAT();                                // 0x00a206f0

struct SoundHandleList
{
    int mBegin;                                            // +0x00
    int mEnd;                                              // +0x04
};

namespace SP
{
    void StopAndClearSoundList(SoundHandleList* handles);  // 0x00d5adf0
}

// @ 0x00d5adf0
void SP::StopAndClearSoundList(SoundHandleList* handles)
{
    int i = 0;
    u32 handle;
    if (((handles->mEnd - handles->mBegin) & ~3) > 0)
    {
        do
        {
            handle = ((u32*)handles->mBegin)[i];
            AudioSystem* audio = GetSystemAT();
            if (audio)
            {
                audio->Begin(0x347536b);
                audio->SetParam(0x3475385, handle);
                audio->SetParam(0x34753a0, 0);
                audio->Commit();
            }
            i++;
        } while (i < (handles->mEnd - handles->mBegin) >> 2);
    }

    u32* last = (u32*)handles->mEnd;
    u32* first = (u32*)handles->mBegin;
    memcpy(first, last, (char*)last - (char*)last);
    handles->mEnd += -((((int)last - (int)first) >> 2)) * 4;
}

// ---------------------------------------------------------------------------
// 0x00d5ae80 -- tribe trail (surface positions of nearby members) update.
// ---------------------------------------------------------------------------
struct TribeVirtualCreature
{
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual Vec3* GetPosition();                           // +0x2c
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual float GetSpeed();                              // +0x70
};

struct TribeCreature
{
    char mPad00[0x34];                                     // +0x00
    TribeVirtualCreature mVirtual;                         // +0x34
};

struct TribeMemberList
{
    TribeCreature** mpBegin;                               // +0x00
    TribeCreature** mpEnd;                                 // +0x04
    int Size() const { return (int)(mpEnd - mpBegin); }
    TribeCreature* operator[](int i) const { return mpBegin[i]; }
};

struct TribeObject
{
    TribeMemberList* GetMembers();                         // 0x00c8e810
};

struct Vec3TrailVector
{
    Vec3* mpBegin;                                         // +0x00
    Vec3* mpEnd;                                           // +0x04
    Vec3* mpCapacity;                                      // +0x08
    uint32_t mAllocTag;                                    // +0x0c
    Vec3* mpInlineBuffer;                                  // +0x10

    void erase(Vec3* first, Vec3* last);                   // 0x0050f740
    void DoInsertValue(Vec3* pos, const Vec3* value);      // 0x004b5ad0
    void push_back(const Vec3& value)
    {
        Vec3* end = mpEnd;
        if (end < mpCapacity)
        {
            mpEnd = end + 1;
            if (end != 0)
            {
                end->x = value.x;
                end->y = value.y;
                end->z = value.z;
            }
        }
        else
        {
            DoInsertValue(end, &value);
        }
    }
};

struct TribeTrailOwner
{
    char mPad00[0x138];                                    // +0x000
    Vec3 mCurrentPosition;                                 // +0x138
    Vec3TrailVector mTrail;                                // +0x144
    Vec3 mPreviousPosition;                                // +0x158
    char mPad164[0xaf0 - 0x164];                           // +0x164
    TribeObject* mpTribe;                                  // +0xaf0

    void UpdateTrail();                                    // 0x00d5ae80
};

extern const float kTrailMoveThreshold;                    // 0x014853e0
extern const float kTrailNormalizeEpsilon;                 // 0x013ec4b8

// @ 0x00d5ae80
void TribeTrailOwner::UpdateTrail()
{
    float dz = mPreviousPosition.z - mCurrentPosition.z;
    float dy = mPreviousPosition.y - mCurrentPosition.y;
    float dx = mPreviousPosition.x - mCurrentPosition.x;
    if (dz * dz + dy * dy + dx * dx > kTrailMoveThreshold)
    {
        mPreviousPosition = mCurrentPosition;

        mTrail.erase(mTrail.mpBegin, mTrail.mpEnd);

        Vec3 ground;
        PlanetModel()->DirectionToSurfacePosition(&ground, &mCurrentPosition);

        TribeMemberList* members = mpTribe->GetMembers();
        for (uint32_t i = 0; i < (uint32_t)members->Size(); ++i)
        {
            TribeCreature* creature = (*members)[i];
            float speed = creature->mVirtual.GetSpeed();
            const Vec3* pos = creature->mVirtual.GetPosition();

            float mdz = pos->z - ground.z;
            float mdy = pos->y - ground.y;
            float mdx = pos->x - ground.x;
            float inv = 1.0f / (float)sqrt(mdz * mdz + mdy * mdy + mdx * mdx + kTrailNormalizeEpsilon);

            float vx = (inv * mdx) * speed;
            float vy = (mdy * inv) * speed;
            float vz = (mdz * inv) * speed;

            const Vec3* pos2 = creature->mVirtual.GetPosition();
            Vec3 target;
            target.x = pos2->x + vx;
            target.y = pos2->y + vy;
            target.z = pos2->z + vz;

            Vec3 tmp;
            Vec3 surface = *PlanetModel()->DirectionToSurfacePosition(&tmp, &target);
            mTrail.push_back(surface);
        }
    }
}
