// s00b4a720: SP::cLocomotiveObject per-frame velocity integration (retail layout, ModAPI offsets).
#include "types.h"
#include <math.h>

struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(const Vec3& o) { x = o.x; y = o.y; z = o.z; }
};

// Queued velocity impulse: xyz plus a mode (0 = add, 1 = add and zero the carried velocity).
struct Impulse { float x, y, z; int mode; };

struct Planet {
    bool IsLoaded();                    // 0xb7ec40
    float GetRadiusAt(const Vec3* p);   // 0xb7ef70
    float GetWaterHeight();             // 0xb7e390
    float FUN_00b7e490();               // 0xb7e490
    Vec3* FUN_00b7e3b0(Vec3* out, const Vec3* p);  // 0xb7e3b0
};

struct Bounds { float pad0[2]; float lo; float pad1[2]; float hi; };

struct Sim { char pad[0x31]; bool b31; };

struct Component {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual const void* GetType();      // +0x20
};
struct ComponentB : Component { bool FUN_00c232c0(); };

struct Loco {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10();
    virtual const Vec3* GetPosition();                 // +0x2c
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25();
    virtual Bounds* GetBounds();                       // +0x68
    virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30();
    virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34();
    virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38();
    virtual void v39(); virtual void v40(); virtual void v41(); virtual void v42();
    virtual void v43(); virtual void v44(); virtual void v45();
    virtual Component* GetComponent(uint32_t id);      // +0xb8
    virtual void v47(); virtual void v48(); virtual void v49(); virtual void v50();
    virtual void v51();
    virtual float GetMaxAccel();                       // +0xd0
    virtual void v53(); virtual void v54(); virtual void v55(); virtual void v56();
    virtual void v57(); virtual void v58(); virtual void v59(); virtual void v60();
    virtual void v61();
    virtual bool IsIdleAnimating();                    // +0xf8

    char pad04[0x50 - 4];
    uint32_t mFlags;                                   // +0x50
    char pad54[0x71 - 0x54];
    char mFlag71;                                      // +0x71
    char pad72[5];
    bool mGrounded;                                    // +0x77
    char pad78[0xf0 - 0x78];
    Impulse* mImpBegin;                                // +0xf0
    Impulse* mImpEnd;                                  // +0xf4
    char padf8[0x1c8 - 0xf8];
    Vec3 mVelocity;                                    // +0x1c8
    Vec3 mAngVelocity;                                 // +0x1d4
    char pad1e0[0x1f0 - 0x1e0];
    int mPlanetCorrection;                             // +0x1f0
    char pad1f4[0x268 - 0x1f4];
    bool mSelfPowered;                                 // +0x268
    char pad269[0x4cc - 0x269];
    int mStrategy;                                     // +0x4cc

    const Vec3* GetVelocity();                         // 0xd20610
    void SetVelocity(const Vec3* v);                   // 0xc41d60
    void SetAngularVelocity(const Vec3* v);            // 0xc41d90
    void FUN_00c431a0(uint32_t dt);                    // 0xc431a0
};

extern Vec3 kZero;            // 0x167eb8c
extern bool gFlag74;          // 0x167eb74
Planet* GetPlanetModel();     // 0xb3d350
Sim* GetSim();                // 0xb3d310
void* GetUniverseContext();   // 0x1021080
bool FUN_0059ab70(const Vec3* v);  // 0x59ab70
void FUN_00b444c0(const Vec3* v, Loco* self);  // 0xb444c0

static const void* const kTypeA = (const void*)0x18eb45e;
static const void* const kTypeB = (const void*)0x18eb4b7;

static inline float VelDot(const Vec3* v, const Vec3& acc, const Vec3* pos)
{
    return ((v->x + acc.x) * pos->x + (v->z + acc.z) * pos->z) + (v->y + acc.y) * pos->y;
}

// @ 0x00b4a720
void FUN_00b4a720(Loco* self, uint32_t dtMs, char flag, char applyCorrection)
{
    float dt = (float)dtMs * 0.001f;
    const Vec3* pv = self->GetVelocity();
    Vec3 vel0 = *pv;
    Vec3 acc = kZero;
    bool replace = false;

    for (Impulse* p = self->mImpBegin; p != self->mImpEnd; ++p) {
        switch (p->mode) {
        case 1:
            replace = true;
        case 0:
            acc.x = acc.x + p->x;
            acc.y = p->y + acc.y;
            acc.z = p->z + acc.z;
            break;
        }
    }
    {
        // mImpulses.clear(): erase(begin, end)
        Impulse* last = self->mImpEnd;
        Impulse* first = self->mImpBegin;
        Impulse* d = first;
        for (Impulse* s = last; s != last; ++s, ++d)
            *d = *s;
        self->mImpEnd = self->mImpEnd - (last - d);
    }
    if (!FUN_0059ab70(&acc))
        acc = kZero;

    Planet* pm = GetPlanetModel();
    bool grounded = self->mGrounded;
    switch (self->mPlanetCorrection) {
    case 0:
    case 1:
        flag = 0;
        if (!GetUniverseContext() && pm && pm->IsLoaded()) {
            float r = pm->GetRadiusAt(self->GetPosition());
            float w = pm->GetWaterHeight();
            Bounds* b = self->GetBounds();
            float h = (b->hi - b->lo) * 0.55f;
            if (r > w - h) {
                grounded = true;
                self->mGrounded = grounded;
            } else {
                grounded = false;
                self->mGrounded = grounded;
            }
        } else {
            self->mGrounded = true;
        }
        break;
    case 2:
    case 3: {
        const Vec3* pos = self->GetPosition();
        if (pm) {
            float r = pm->GetRadiusAt(pos);
            if (gFlag74) {
                float w = pm->GetWaterHeight();
                const float* m = &w;
                if (!(w > r))
                    m = &r;
                r = *m;
            }
            float lim = r + 1.52587890625e-05f;
            if (lim * lim < (pos->x * pos->x + pos->y * pos->y) + pos->z * pos->z ||
                0.0f < VelDot(self->GetVelocity(), acc, pos))
                grounded = false;
            else
                grounded = true;
            if (!gFlag74) {
                float w = pm->GetWaterHeight();
                Bounds* b = self->GetBounds();
                float h = (b->hi - b->lo) * 0.55f;
                if (r < w - h)
                    grounded = false;
            }
        }
        self->mGrounded = grounded;
        break;
    }
    case 4:
        self->mGrounded = false;
        break;
    case 5:
        self->mGrounded = false;
        flag = 0;
        break;
    case 6:
        flag = 0;
        break;
    }

    if (self->IsIdleAnimating()) {
        if (self->mSelfPowered) {
            self->FUN_00c431a0(dtMs);
            self->SetAngularVelocity(&kZero);
        }
    } else if (grounded) {
        self->SetVelocity(&kZero);
        self->SetAngularVelocity(&kZero);
    }

    Vec3 newVel;
    if (replace) {
        vel0.x = 0.0f; vel0.y = 0.0f; vel0.z = 0.0f;
        newVel.x = 0.0f; newVel.y = 0.0f; newVel.z = 0.0f;
    } else {
        const Vec3* v = self->GetVelocity();
        newVel = *v;
    }

    Component* comp = self->GetComponent(0xce9f6639);
    if (!GetSim()->b31 && comp) {
        bool ok = true;
        if (comp->GetType() != kTypeA) {
            ComponentB* cb = (comp->GetType() == kTypeB) ? (ComponentB*)comp : 0;
            if (!cb->FUN_00c232c0())
                ok = false;
        }
        if (ok) {
            float inv = 1.0f / dt;
            float ax = (newVel.x - vel0.x) * inv;
            float ay = (newVel.y - vel0.y) * inv;
            float az = (newVel.z - vel0.z) * inv;
            float aa = (az * az + ay * ay) + ax * ax;
            float len = sqrtf(aa);
            if (0.0f < (ay * vel0.y + az * vel0.z) + ax * vel0.x &&
                self->GetMaxAccel() < len) {
                float lim = self->GetMaxAccel();
                float k = 1.0f / sqrtf(aa + 1e-08f);
                newVel.x = (((k * ax) * lim) * dt) + vel0.x;
                newVel.y = (((ay * k) * lim) * dt) + vel0.y;
                newVel.z = (((az * k) * lim) * dt) + vel0.z;
            }
        }
    }
    newVel.x = newVel.x + acc.x;
    newVel.y = newVel.y + acc.y;
    newVel.z = newVel.z + acc.z;

    if (pm && !(self->mFlags & 0x100) && !self->mFlag71) {
        float F = pm->FUN_00b7e490();
        if ((!self->mSelfPowered || self->mStrategy == 0) && self->mGrounded) {
            const Vec3* pos = self->GetPosition();
            const Vec3* n0 = pm->FUN_00b7e3b0(&vel0, pos);
            float ni = 1.0f / sqrtf(n0->z * n0->z + n0->y * n0->y + n0->x * n0->x);
            Vec3 n;
            n.x = ni * n0->x; n.y = ni * n0->y; n.z = ni * n0->z;
            const Vec3* q = self->GetPosition();
            float qi = 1.0f / sqrtf(q->z * q->z + q->y * q->y + q->x * q->x);
            float h = ((-n.z * ((q->z * qi) * F) + -n.y * ((q->y * qi) * F)) +
                       -n.x * ((qi * q->x) * F)) * dt;
            float vv = (newVel.z * newVel.z + newVel.y * newVel.y) + newVel.x * newVel.x;
            if (vv < h * h) {
                newVel = kZero;
            } else {
                float k = 1.0f / sqrtf(vv);
                newVel.x = -(k * newVel.x) * h + newVel.x;
                newVel.y = -(newVel.y * k) * h + newVel.y;
                newVel.z = -(newVel.z * k) * h + newVel.z;
            }
        } else if (flag && !self->mGrounded) {
            const Vec3* p = self->GetPosition();
            float len = sqrtf(p->z * p->z + p->y * p->y + p->x * p->x);
            if (1.52587890625e-05f < len) {
                const Vec3* p2 = self->GetPosition();
                float k = 1.0f / len;
                newVel.x = ((k * p2->x) * F) * dt + newVel.x;
                newVel.y = ((p2->y * k) * F) * dt + newVel.y;
                newVel.z = ((p2->z * k) * F) * dt + newVel.z;
            }
        }
    }
    self->SetVelocity(&newVel);
    if (applyCorrection) {
        const Vec3* p = self->GetPosition();
        Vec3 out;
        out.x = newVel.x * dt + p->x;
        out.y = newVel.y * dt + p->y;
        out.z = newVel.z * dt + p->z;
        FUN_00b444c0(&out, self);
    }
}
