// Slice s00d964a0: two SP::CitizenTree behaviour-tree callbacks (cdecl, citizen creature first).
//   0x00d964a0  Policeman_Tick   (2299 bytes) - keeps a policeman citizen's attention on its target: walks to the
//               target when it is more than 12 units away, turns to face it, otherwise plays the arrest beam effect
//               (8 points along the line to the target) and applies a small impulse to the target.
//   0x00d96da0  SimFeedback_Activate (1656 bytes) - picks a random route segment of the citizen's city, picks one of
//               its two directions and an activity mode by the segment's probabilities, and starts the citizen on a
//               2- or 3-point path along it.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (same module as s00d98140).
#include <math.h>
#include "types.h"

#define PV(n) virtual void pv##n();

struct Vec3 { float x, y, z; };

struct Matrix3 {
    float m[9];
    Matrix3() {}
    Matrix3(const Matrix3& o);          // 0x0041cb40 (out of line copy)
};

struct Transform {                       // 0x38 bytes: flags, count, offset, scale, rotation
    uint16_t mnFlags;
    uint16_t mnCount;
    Vec3     mOffset;
    float    mfScale;
    Matrix3  mRotation;
    struct InlineInit {};
    Transform(InlineInit);
    void SetOffset(const Vec3& v) { mOffset = v; mnFlags |= 4; ++mnCount; }
};
extern Vec3 sZeroVector;                 // 0x0169f28c
extern Matrix3 sIdentityMatrix;          // 0x0169f268
__forceinline Transform::Transform(InlineInit) : mnFlags(0), mnCount(0), mOffset(sZeroVector), mfScale(1.0f), mRotation(sIdentityMatrix) {}

struct Quat { float x, y, z, w; };

struct PlanetModel {
    Quat* BuildSurfaceOrientation(Quat* out, const Vec3* pos, const Vec3* dir);      // 0x00b7f250 (stdcall)
    Vec3* MakeRandomWorldPosition(Vec3* out, const Vec3* center, float minDist, float maxDist);   // 0x00b81780 (stdcall)
};
PlanetModel* GetPlanetModel();           // 0x00b3d350

struct EffectHandle {
    PV(0)
    virtual void Release();              // +4
    virtual void Start(int);             // +8
    virtual void Stop(int);              // +0xc
    PV(4) PV(5)
    virtual void SetTransform(const Transform* t);       // +0x18
    PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15)
    virtual void SetPoints(int id, const Vec3* pts, int count);   // +0x40
};
struct EffectsManager {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual void PlayEffect(uint32_t id, int flags, EffectHandle** out);   // +0x2c
};
EffectsManager* GetEffectsManager();     // 0x0067ddd0

struct Spatial {                         // object returned by target->GetSpatial()
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual const Vec3* GetPosition();                 // +0x2c
    PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25)
    PV(26)
    virtual const float* GetBoundingBox(void* buf);    // +0x6c
};

struct Target {                          // reference counted game object
    PV(0) PV(1)
    virtual Spatial* GetSpatial();                     // +8
    PV(3) PV(4) PV(5)
    virtual void ApplyImpulse(float mag, void* source, int kind, const Vec3* dir, const void* extra);   // +0x18
    PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20)
    PV(21)
    virtual float GetScale();                          // +0x58
    PV(23)
    virtual void AddRef();                             // +0x60
    virtual void Release();                            // +0x64
};

struct Path { const Vec3* Back(); };     // 0x00c423c0 (last waypoint position)

struct Waypoint {                        // 0x3c bytes
    Vec3     pos;                         // +0
    float    speed;                       // +0xc
    int      i10;                         // +0x10
    float    rest[9];                     // +0x14 .. +0x38 (left uninitialised by the creator)
    uint8_t  flag;                        // +0x38
    Waypoint(float x, float y, float z) { pos.x = x; pos.y = y; pos.z = z; speed = 1.0f; i10 = 0; flag = 0; }
    Waypoint(const Waypoint& o);          // 0x00ac1ff0
};

void EaFree(void*);                       // 0x00f47380 operator delete[]
inline void* operator new(unsigned int, void* p) { return p; }

struct WaypointVector {                   // sp_vector<Waypoint>
    Waypoint* mpBegin;
    Waypoint* mpEnd;
    Waypoint* mpCapacity;
    WaypointVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~WaypointVector() { if (mpBegin && ((int*)mpBegin)[-1] != 0) EaFree(mpBegin); }
    void DoInsertValue(Waypoint* pos, const Waypoint& v);     // 0x00ac45e0
    void push_back(const Waypoint& v)
    {
        if (mpEnd < mpCapacity)
            ::new((void*)mpEnd++) Waypoint(v);
        else
            DoInsertValue(mpEnd, v);
    }
};

struct PathRequest {                      // 0x74 bytes; first word is the waypoint array
    Waypoint* mpBegin;
    uint32_t  rest[28];
    PathRequest(const WaypointVector& v);   // 0x00c1bad0
    ~PathRequest() { if (mpBegin && ((int*)mpBegin)[-1] != 0) EaFree(mpBegin); }
};

struct Locomotion {                      // sub-object at creature + 0xc0
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual const Vec3* GetPosition();                 // +0x2c
    PV(12) PV(13)
    virtual void SetPosition(const Vec3* p);           // +0x38
    virtual void SetOrientation(const Quat* q);        // +0x3c
    PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22)
    virtual const Vec3* GetForward(Vec3* tmp);         // +0x5c
    PV(24) PV(25) PV(26)
    virtual const float* GetBoundingBox(void* buf);    // +0x6c
    PV(28) PV(29) PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41)
    PV(42) PV(43) PV(44) PV(45) PV(46) PV(47) PV(48) PV(49) PV(50) PV(51) PV(52) PV(53) PV(54)
    virtual void SetPath(const PathRequest& p);        // +0xdc
    PV(56) PV(57) PV(58)
    virtual void StopMoving();                         // +0xec
    Path* GetPath();                                   // 0x00c41ec0 (returns this + 0x1f4)
};

struct Owner {
    uint32_t pad[0xa28 / 4];
    int      mCounter;                // +0xa28
    uint32_t pad2[(0xa58 - 0xa2c) / 4];
    Target*  mpTarget;                // +0xa58
};

struct Creature {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13)
    PV(14) PV(15) PV(16) PV(17) PV(18)
    virtual void* GetSource();                         // +0x4c
    uint32_t pad04[(0xc0 - 4) / 4];
    Locomotion mLoco;                 // +0xc0 : sub-object with its own vptr (size not modelled)
    uint32_t padLoco[(0x330 - 0xc4) / 4];
    uint32_t mField330;               // +0x330
    uint32_t pad334[(0x5a8 - 0x334) / 4];
    uint32_t mField5a8;               // +0x5a8
    uint32_t pad5ac[(0xfb8 - 0x5ac) / 4];
    Owner*   mpOwner;                 // +0xfb8
    uint32_t pad_fbc;
    int      mFieldFC0;               // +0xfc0
    void MoveToPointAndFacingAtSpeed(int mode, const Vec3* pos, const Vec3* facing, float speed, float turn);   // 0x00c1c5c0 (ret 0x14)
    void SetMoveState(int state);     // 0x00c0cff0
    void Method_c0d0c0(int a, int b); // 0x00c0d0c0
};
struct City;
struct CitizenCreature : Creature {
    City* GetCity();                  // 0x00c23e40 (returns [this + 0x1010])
};

// ------------------------------------------------------------------------------------------------------------
namespace EA { namespace Random {
struct RandomLinearCongruential {
    uint32_t RandomUint32Uniform(uint32_t limit);   // 0x00a68fb0
    double   RandomDoubleUniform();                 // 0x009360d0
};
}}
extern EA::Random::RandomLinearCongruential sMathRandom;   // 0x01601760

struct RouteSegment {                     // 0x50 bytes, element of the city's route list
    uint32_t pad00[2];
    float    probsA[3];               // +0x08: activity probabilities when walked U -> V
    float    probsB[3];               // +0x14: when walked V -> U
    Vec3     pointU;                  // +0x20
    Vec3     pointV;                  // +0x2c
    Vec3     dirU;                    // +0x38
    Vec3     dirV;                    // +0x44
};
struct RouteList { RouteSegment* mpBegin; RouteSegment* mpEnd; };
struct City { RouteList* GetRoutes(); };      // 0x00bd8230 (returns this + 0x684)

namespace SP {
namespace CitizenTree {

struct PolicemanState {
    Target*       mpTarget;           // +0
    EffectHandle* mpEffect;           // +4
};

// @ 0x00d964a0
bool Policeman_Tick(Creature* c, int a2, int a3, int a4, int a5, PolicemanState* st, int a7, float dt)
{
    Target* newTarget = c->mpOwner->mpTarget;
    Target* oldTarget = st->mpTarget;
    if (newTarget != oldTarget)
    {
        if (newTarget)
            newTarget->AddRef();
        st->mpTarget = newTarget;
        if (oldTarget)
            oldTarget->Release();
    }
    if (!st->mpTarget)
        return false;

    const Vec3* tp = st->mpTarget->GetSpatial()->GetPosition();
    Vec3 tpos = *tp;
    Locomotion* loco = &c->mLoco;
    const Vec3* mp = loco->GetPosition();
    Vec3 mpos = *mp;
    Vec3 d;
    d.x = tpos.x - mpos.x;
    d.y = tpos.y - mpos.y;
    d.z = tpos.z - mpos.z;
    float dist = sqrtf((d.x * d.x + d.z * d.z) + d.y * d.y);
    float inv = 1.0f / dist;
    Vec3 dir;
    dir.x = inv * d.x;
    dir.y = d.y * inv;
    dir.z = d.z * inv;
    bool far = dist > 12.0f;
    Vec3 ftmp;
    const Vec3* fwd = loco->GetForward(&ftmp);
    bool notFacing = 0.9f > (fwd->z * dir.z + fwd->y * dir.y) + dir.x * fwd->x;

    if (far)
    {
        const Vec3* goal = loco->GetPath()->Back();
        float gx = goal->x - tpos.x;
        float gy = goal->y - tpos.y;
        float gz = goal->z - tpos.z;
        if (sqrtf((gx * gx + gz * gz) + gy * gy) > 12.0f)
        {
            Vec3 rnd;
            GetPlanetModel()->MakeRandomWorldPosition(&rnd, &tpos, 6.0f, 10.0f);
            c->MoveToPointAndFacingAtSpeed(2, &rnd, &dir, 1.0f, 2.0f);
        }
    }
    else if (notFacing)
    {
        c->MoveToPointAndFacingAtSpeed(2, &mpos, &dir, 1.0f, 2.0f);
    }
    else
    {
        loco->StopMoving();
        if (!st->mpEffect)
        {
            EffectsManager* mgr = GetEffectsManager();
            if (st->mpEffect)
            {
                EffectHandle* old = st->mpEffect;
                st->mpEffect = 0;
                old->Release();
            }
            mgr->PlayEffect(0xcd7bc525, 0, &st->mpEffect);
            if (st->mpEffect)
                st->mpEffect->Start(0);
        }
        if (st->mpEffect)
        {
            uint32_t buf[12];
            const float* b = loco->GetBoundingBox(buf);
            Vec3 ctmp;
            ctmp.x = (b[0] + b[3]) * 0.5f;
            ctmp.y = (b[4] + b[1]) * 0.5f;
            ctmp.z = (b[5] + b[2]) * 0.5f;
            Vec3 C = ctmp;
            uint32_t buf2[12];
            const float* b2 = st->mpTarget->GetSpatial()->GetBoundingBox(buf2);
            float tx = (b2[0] + b2[3]) * 0.5f;
            float ty = (b2[4] + b2[1]) * 0.5f;
            float tz = (b2[5] + b2[2]) * 0.5f;
            float ex = tx - C.x;
            float ey = ty - C.y;
            float ez = tz - C.z;
            float len = sqrtf((ez * ez + ey * ey) + ex * ex);
            float ilen = 1.0f / len;
            float step = len * 0.14285715f;
            float sx = (ilen * ex) * step;
            float sy = (ey * ilen) * step;
            float sz = (ez * ilen) * step;
            Vec3 pts[8];
            pts[0] = C;
            pts[1].x = sx + C.x;  pts[1].y = sy + C.y;  pts[1].z = sz + C.z;
            pts[2].x = sx * 2.0f + C.x;  pts[2].y = sy * 2.0f + C.y;  pts[2].z = sz * 2.0f + C.z;
            pts[3].x = sx * 3.0f + C.x;  pts[3].y = sy * 3.0f + C.y;  pts[3].z = sz * 3.0f + C.z;
            pts[4].x = sx * 4.0f + C.x;  pts[4].y = sy * 4.0f + C.y;  pts[4].z = sz * 4.0f + C.z;
            pts[5].x = sx * 5.0f + C.x;  pts[5].y = sy * 5.0f + C.y;  pts[5].z = sz * 5.0f + C.z;
            pts[6].x = sx * 6.0f + C.x;  pts[6].y = sy * 6.0f + C.y;  pts[6].z = sz * 6.0f + C.z;
            pts[7].x = sx * 7.0f + C.x;  pts[7].y = sy * 7.0f + C.y;  pts[7].z = sz * 7.0f + C.z;
            st->mpEffect->SetPoints(13, pts, 8);

            Transform xf((Transform::InlineInit()));
            xf.mRotation = sIdentityMatrix;
            xf.SetOffset(C);
            xf.mfScale = 1.0f;
            st->mpEffect->SetTransform(&xf);
        }

        float mag = (st->mpTarget->GetScale() * dt) * 0.1f;
        Vec3 away;
        away.x = mpos.x - tpos.x;
        away.y = mpos.y - tpos.y;
        away.z = mpos.z - tpos.z;
        float ia = 1.0f / sqrtf(((away.z * away.z + away.y * away.y) + away.x * away.x) + 1e-8f);
        Vec3 u;
        u.x = ia * away.x;
        u.y = away.y * ia;
        u.z = away.z * ia;
        st->mpTarget->ApplyImpulse(mag, c->GetSource(), 1, &u, &c->mField5a8);
        return true;
    }

    if (st->mpEffect)
    {
        st->mpEffect->Stop(0);
        EffectHandle* e = st->mpEffect;
        st->mpEffect = 0;
        if (e)
            e->Release();
    }
    return true;
}

struct RouteChoice {                      // output of SimFeedback_Activate
    Vec3 start;                           // +0
    Vec3 end;                             // +0xc
    int  mode;                            // +0x18
};

// @ 0x00d96da0
bool SimFeedback_Activate(CitizenCreature* c, int a2, int a3, uint8_t flags, int a5, RouteChoice* out)
{
    RouteList* routes = c->GetCity()->GetRoutes();
    if (routes->mpBegin == routes->mpEnd)
        return false;
    uint32_t n = (uint32_t)(((char*)routes->mpEnd - (char*)routes->mpBegin) / 0x50);
    RouteSegment* seg = routes->mpBegin + sMathRandom.RandomUint32Uniform(n);

    Vec3 S, E, dS, dE;
    float p1, p2, p3;
    if (0.5f <= sMathRandom.RandomDoubleUniform())
    {
        S = seg->pointV;
        dS = seg->dirV;
        E = seg->pointU;
        dE = seg->dirU;
        p1 = seg->probsB[0];
        p2 = seg->probsB[1];
        p3 = seg->probsB[2];
    }
    else
    {
        S = seg->pointU;
        dS = seg->dirU;
        E = seg->pointV;
        dE = seg->dirV;
        p1 = seg->probsA[0];
        p2 = seg->probsA[1];
        p3 = seg->probsA[2];
    }

    float r = (float)sMathRandom.RandomDoubleUniform();
    if (r < p1)
    {
        out->mode = 0;
        c->mFieldFC0 = 0;
    }
    else
    {
        int m;
        if (p2 + p1 > r)
            m = 1;
        else if ((p3 + p2) + p1 > r)
        {
            out->mode = 2;
            c->Method_c0d0c0(2, 1);
            c->mFieldFC0 = 2;
            goto modeDone;
        }
        else
            m = 3;
        out->mode = m;
        c->mFieldFC0 = m;
    }
modeDone:
    out->start = S;
    out->end = E;

    WaypointVector path;
    Locomotion* loco = &c->mLoco;
    if (flags & 1)
    {
        float t = (float)sMathRandom.RandomDoubleUniform();
        Vec3 P;
        P.x = (E.x - S.x) * t + S.x;
        P.y = (E.y - S.y) * t + S.y;
        P.z = (E.z - S.z) * t + S.z;
        loco->SetPosition(&P);
        Vec3 d;
        d.x = E.x - S.x;
        d.y = E.y - S.y;
        d.z = E.z - S.z;
        float inv = 1.0f / sqrtf(((d.x * d.x + d.z * d.z) + d.y * d.y) + 1e-8f);
        Vec3 u;
        u.x = inv * d.x;
        u.y = d.y * inv;
        u.z = d.z * inv;
        Quat q;
        loco->SetOrientation(GetPlanetModel()->BuildSurfaceOrientation(&q, &S, &u));
        path.push_back(Waypoint(dE.x * 3.0f + E.x, dE.y * 3.0f + E.y, dE.z * 3.0f + E.z));
        path.push_back(Waypoint(E.x, E.y, E.z));
    }
    else
    {
        loco->SetPosition(&S);
        Quat q;
        loco->SetOrientation(GetPlanetModel()->BuildSurfaceOrientation(&q, &S, &dS));
        path.push_back(Waypoint(dS.x * 3.0f + S.x, dS.y * 3.0f + S.y, dS.z * 3.0f + S.z));
        path.push_back(Waypoint(dE.x * 3.0f + E.x, dE.y * 3.0f + E.y, dE.z * 3.0f + E.z));
        path.push_back(Waypoint(E.x, E.y, E.z));
    }
    loco->SetPath(PathRequest(path));
    c->SetMoveState(2);
    c->mField330 = 0;
    c->mpOwner->mCounter++;
    return true;
}

}  // namespace CitizenTree
}  // namespace SP
