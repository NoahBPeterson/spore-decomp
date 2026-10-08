// Slice s00b48110: locomotion steering step (MSVC 2008 SP1, /O2 /arch:SSE).
// Raw retail offsets are used; object/state layouts recovered from the asm.
#include <math.h>

struct Vec3 { float x, y, z; };
struct Quat { float x, y, z, w; };

struct StateElem { unsigned int d[15]; };           // 0x3c-byte queue entry

struct LocoState {                                   // embedded in the object at +0x1f4
    StateElem* mpBegin;                              // +0x00
    StateElem* mpEnd;                                // +0x04
    char pad0[0x14 - 8];
    Vec3 mTarget;                                    // +0x14
    float mArriveDist;                               // +0x20
    char pad1[0x50 - 0x24];
    Vec3 mAxis;                                      // +0x50
    int mMode;                                       // +0x5c
    float mSlowDist;                                 // +0x60
    float mAxisLimit;                                // +0x64
    float mLastDist;                                 // +0x68
    float mTimer;                                    // +0x6c

    void PopFront(StateElem* e);                     // 0x00b47520 (thiscall ret 4)
};

extern "C" void operator_delete__(void* p);          // 0x00f47380 (cdecl)

struct LocoReq {                                     // Simulator::cLocomotionRequest, 0x74 bytes
    char* mpData;                                    // +0
    char pad0[0x14 - 4];
    Vec3 mTarget;                                    // +0x14
    char pad1[0x74 - 0x20];

    LocoReq();                                       // 0x00ac9850
    LocoReq(LocoState* st);                          // 0x00b46d90 (thiscall ret 4)
    ~LocoReq() { if (mpData && ((int*)mpData)[-1] != 0) operator_delete__(mpData); }
};

struct Loco {                                        // SP::cLocomotiveObject
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10();
    virtual const Vec3* GetPosition();               // +0x2c
    virtual const Quat* GetOrientation();            // +0x30
    virtual void s13(); virtual void s14();
    virtual void SetOrientation(const Quat* q);      // +0x3c
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20();
    virtual void s21(); virtual void s22();
    virtual const Vec3* GetFacing(Vec3* out);        // +0x5c
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28();
    virtual void s29(); virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33();
    virtual void s34(); virtual void s35(); virtual void s36(); virtual void s37(); virtual void s38();
    virtual void s39(); virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
    virtual void s44(); virtual void s45();
    virtual void* QueryInfo(const void* key);        // +0xb8
    virtual void s47(); virtual void s48();
    virtual void Stop(float t, int flag);            // +0xc4
    virtual float GetMaxSpeed();                     // +0xc8
    virtual void s51();
    virtual float GetSomething();                    // +0xd0
    virtual void s53(); virtual void s54();
    virtual void SetRequest(LocoReq* req);           // +0xdc
    char pad0[0x77 - 4];
    char mbFlag;                                     // +0x77
    char pad1[0x1e8 - 0x78];
    float mTurnRate;                                 // +0x1e8

    const Vec3* GetVelocity();                       // 0x00d20610 (&this[0x1c8])
    LocoState* GetState();                           // 0x00c41ec0 (&this[0x1f4])
    void GetDirection(Vec3* out);                    // 0x00c44080 (thiscall ret 4)
};

struct PlanetModel {
    char pad[0x24]; void* mpTerrain;
    void BuildSurfaceOrientation(Quat* out, const Vec3* pos, const Vec3* facing);   // 0x00b7f250 (ret 0xc)
    Vec3* DirectionToSurfacePosition(const Vec3* dir, Vec3* out);                   // 0x00b815a0 (ret 8)
};
PlanetModel* GetPlanetModel();                       // 0x00b3d350
extern "C" Vec3* normalized_safe(Vec3* out, const Vec3* in);                        // 0x00449c20 (cdecl)
extern "C" Quat* Slerp(Quat* out, const Quat* a, const Quat* b, float t);           // 0x005b2500 (cdecl)

struct Params {
    Vec3 vel;                                        // +0
    float pad;                                       // +0xc
    float dt;                                        // +0x10
    Loco* obj;                                       // +0x14
};

struct Steering {
    float Probe(Loco* obj, Vec3* q, float dt, float speed, float turn);             // 0x00b46df0 (thiscall ret 0x14, float in ST0)
    void Update(Params* P);
};

// @ 0x00b48110  Steering::Update
void Steering::Update(Params* P) {
    P->obj->GetSomething();
    P->obj->GetVelocity();
    P->obj->QueryInfo((const void*)0x0137e8e0);
    Vec3 dir;
    P->obj->GetDirection(&dir);
    float len = sqrt(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);
    if (1.52587890625e-05f <= len) {
        float s = 1.0f / len;
        dir.x = s * dir.x;
        dir.y = dir.y * s;
        dir.z = dir.z * s;
    } else {
        Vec3 tmp;
        const Vec3* f = P->obj->GetFacing(&tmp);
        dir.x = f->x * 0.1f;
        dir.y = f->y * 0.1f;
        dir.z = f->z * 0.1f;
    }
    const Vec3* pp = P->obj->GetPosition();
    Vec3 pos;
    pos.x = pp->x; pos.y = pp->y; pos.z = pp->z;
    Vec3 facing;
    P->obj->GetFacing(&facing);
    float speed = P->obj->GetMaxSpeed();
    float turn = P->obj->mTurnRate;
    LocoState* st = P->obj->GetState();
    PlanetModel* pm = GetPlanetModel();
    float dist;
    if (st->mMode == 0) {
        dist = 0.0f;
    } else {
        float dx = pos.x - st->mTarget.x;
        float dy = pos.y - st->mTarget.y;
        float dz = pos.z - st->mTarget.z;
        dist = sqrt((dz * dz + dy * dy) + dx * dx);
    }

    if (!P->obj->mbFlag) {
        const Vec3* v = P->obj->GetVelocity();
        P->vel = *v;
        const Vec3* cur = P->obj->GetPosition();
        Vec3 f2;
        P->obj->GetFacing(&f2);
        Quat target;
        pm->BuildSurfaceOrientation(&target, cur, &f2);
        float t = P->dt;
        Quat sl;
        Quat r = *Slerp(&sl, P->obj->GetOrientation(), &target, t);
        Quat r2 = r;
        P->obj->SetOrientation(&r2);
        return;
    }

    int mode = st->mMode;
    float arriveDist = st->mArriveDist;
    bool notMode3 = (mode != 3);
    bool arrived = false;
    if (mode == 0) {
        speed = 0.0f;
    } else if (mode != 2) {
        bool tick;
        if (!(dist >= st->mLastDist)) {
            tick = false;
        } else {
            float dt = P->dt;
            float tm = st->mTimer;
            tick = true;
            st->mTimer = dt + tm;
            if (0.25f < dt + tm) {
                Vec3* r = pm->DirectionToSurfacePosition(&facing, &st->mTarget);
                st->mTarget = *r;
            }
        }
        if (arriveDist > dist) {
            arrived = true;
        } else if (!(P->dt * speed >= dist)) {
            if (tick && st->mSlowDist > dist) arrived = true;
        } else {
            speed = (dist / P->dt) * 0.95f;
        }
        st->mLastDist = dist;
        if (arrived) {
            if (st->mpBegin == st->mpEnd) {
                speed = 0.0f;
            } else {
                StateElem* e = st->mpBegin;
                st->mTimer = 0.0f;
                *(StateElem*)&st->mTarget = *e;
                st->PopFront(e);
                arrived = false;
            }
        }
    }
    if (st->mMode != 0) {
        if ((speed / turn) * 2.0f > dist) {
            Vec3 d;
            d.x = st->mTarget.x - pos.x;
            d.y = st->mTarget.y - pos.y;
            d.z = st->mTarget.z - pos.z;
            Vec3 nrm;
            const Vec3* n = normalized_safe(&nrm, &d);
            if (0.5f > (n->y * facing.y + n->z * facing.z) + n->x * facing.x) {
                float lim = (dist * turn) * 0.5f;
                const float* p = &lim;
                if (speed <= lim) p = &speed;
                speed = *p;
            }
        }
    }
    Vec3 q;
    q.x = pos.x + dir.x;
    q.y = pos.y + dir.y;
    q.z = pos.z + dir.z;
    if (Probe(P->obj, &q, P->dt, speed, turn) > 0.0f) {
        P->vel.y = dir.y * speed;
        P->vel.z = dir.z * speed;
        P->vel.x = dir.x * speed;
    } else {
        P->vel.y = 0.0f;
        P->vel.z = 0.0f;
        P->vel.x = 0.0f;
    }
    if (!notMode3) {
        Vec3 f3;
        const Vec3* fp = P->obj->GetFacing(&f3);
        notMode3 = (fp->z * st->mAxis.z + fp->y * st->mAxis.y) + fp->x * st->mAxis.x > st->mAxisLimit;
    }
    if (arrived) {
        if (notMode3) {
            {
                LocoReq req;
                P->obj->SetRequest(&req);
            }
            P->obj->Stop(0.0f, 1);
            P->vel.x = 0.0f; P->vel.y = 0.0f; P->vel.z = 0.0f;
            return;
        } else {
            LocoReq req(P->obj->GetState());
            req.mTarget = pos;
            P->obj->SetRequest(&req);
        }
    }
}
