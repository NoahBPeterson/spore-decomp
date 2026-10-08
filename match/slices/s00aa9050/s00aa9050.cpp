// Slice s00aa9050: Swarm particle collider, "collide one particle against the surface for one
// step" (__thiscall(cParticle*, float dt) -> bool keep-alive). The collider owns a transform
// (this+0x100, used when mbLocal is set to bring the particle into the surface's space), a
// surface object (this+0x1b0: Contains / HeightAt / NormalAt / v28) and a description
// (this+0x24) whose flags (+8) select the response:
//   bit 15: replace the velocity by the surface vector, scaled     bit 16: add it to the velocity
//   bit 14: look one step ahead along the velocity and push away from the surface (soft wall)
//   none  : hard reflection off the surface height (bounce factor desc+0x1C0, 0 = slide)
// Returns false to kill the particle. Class/field names are Claude-coined from usage; the
// transform layout matches s00a9ddd0's Xform and the helpers are s007cd6d0's / s00a7ca50's.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"
#include <math.h>

struct Vec3 {
    float x, y, z;
    __forceinline Vec3() {}
    __forceinline Vec3(const Vec3& o) : x(o.x), y(o.y), z(o.z) {}
    __forceinline Vec3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
};

static inline bool Bit(uint32_t v, int n) { return (v >> n) & 1; }

struct RandomLinearCongruential { double RandomDoubleUniform(); };   // 0x009360D0
extern RandomLinearCongruential g_Random;                            // 0x016778DC (sRandom_Swarm)

struct Xform {
    uint32_t flags;      // +0x00 (bit 1: has rotation)
    Vec3 t;              // +0x04
    float scale;         // +0x10
    float m[9];          // +0x14
    void Transform(Vec3* v);                // 0x007CDEE0
    void InverseTransformPoint(Vec3* v);    // 0x007CDA70
    void InverseTransformDir(Vec3* v);      // 0x00A78E90
    void InverseRotate(Vec3* v);            // 0x00A7CA50

};

#define V(n) virtual void v##n()
struct cSurface {
    V(00); V(04); V(08); V(0c); V(10); V(14);
    virtual bool Contains(const Vec3* pos);                          // +0x18
    V(1c);
    virtual float HeightAt(const Vec3* pos);                         // +0x20
    virtual void NormalAt(Vec3* out, const Vec3* pos);               // +0x24
    virtual void DirectionAt(Vec3* out, const Vec3* pos);            // +0x28
};

struct cParticleDesc {
    uint32_t pad_00[2];
    uint32_t mFlags;                                                 // +0x08
    uint8_t pad_0c[0x1C0 - 0x0C];
    float mBounce;                                                   // +0x1C0
    float mFloorMin;                                                 // +0x1C4
    float mStrength;                                                 // +0x1C8
    float mLookAhead;                                                // +0x1CC
    float mScaleZ;                                                   // +0x1D0
    float mKillBelow;                                                // +0x1D4
    float mKillChance;                                               // +0x1D8
};

struct cParticle {
    uint8_t pad_00[0x10];
    Vec3 mPos;                                                       // +0x10
    Vec3 mVel;                                                       // +0x1C
};

struct cCollider {
    uint8_t pad_00[0x24];
    cParticleDesc* mpDesc;                                           // +0x24
    uint8_t pad_28[0x100 - 0x28];
    Xform mXform;                                                    // +0x100
    uint8_t pad_138[0x180 - 0x138];
    float mDamping;                                                  // +0x180
    uint8_t pad_184[0x1B0 - 0x184];
    cSurface* mpSurface;                                             // +0x1B0
    uint8_t pad_1b4[0x1BC - 0x1B4];
    bool mbLocal;                                                    // +0x1BC

    bool Collide(cParticle* p, float dt);                            // 0x00AA9050
};

// @ 0x00AA9050
bool cCollider::Collide(cParticle* p, float dt)
{
    Vec3 N;   // surface normal
    Vec3 W;   // shared scratch: rotation temp, then the surface vector / probe point
    Vec3 P(p->mPos.x, p->mPos.y, p->mPos.z);
    if (mbLocal) {
        // inlined point transform: rotation by m, then scale and translate
        if (mXform.flags & 2) {
            P = Vec3((mXform.m[6] * P.z + mXform.m[3] * P.y) + mXform.m[0] * P.x,
                     (mXform.m[7] * P.z + mXform.m[4] * P.y) + mXform.m[1] * P.x,
                     (mXform.m[8] * P.z + mXform.m[5] * P.y) + mXform.m[2] * P.x);
        }
        P.x = mXform.t.x + mXform.scale * P.x;
        P.y = mXform.t.y + mXform.scale * P.y;
        P.z = mXform.t.z + mXform.scale * P.z;
    }
    if (!mpSurface->Contains(&P))
        return !Bit(mpDesc->mFlags, 17);

    cParticleDesc* desc = mpDesc;
    uint32_t flags = desc->mFlags;
    if (Bit(flags, 15)) {
        mpSurface->DirectionAt(&W, &P);
        if (mbLocal)
            mXform.InverseTransformDir(&W);
        float s = mpDesc->mStrength;
        float d = mDamping;
        p->mVel.x = (W.x * s) * d;
        p->mVel.y = (W.y * s) * d;
        p->mVel.z = (W.z * s) * d;
        return true;
    }
    if (Bit(flags, 16)) {
        mpSurface->DirectionAt(&W, &P);
        if (mbLocal)
            mXform.InverseTransformDir(&W);
        float s = mpDesc->mStrength;
        float d = mDamping;
        p->mVel.x = p->mVel.x + ((W.x * s) * dt) * d;
        p->mVel.y = p->mVel.y + ((W.y * s) * dt) * d;
        p->mVel.z = p->mVel.z + ((W.z * s) * dt) * d;
        return true;
    }
    if (Bit(flags, 14)) {
        float s = desc->mLookAhead;
        float vx = p->mVel.x, vy = p->mVel.y, vz = p->mVel.z;
        float len = sqrtf((vx * vx + vy * vy) + vz * vz);
        if (len > 10.0f) {
            float inv = 1.0f / len;
            W = Vec3(inv * (vx * s), inv * (vy * s), inv * (vz * s));
        } else {
            W = Vec3((vx * s) * 0.1f, (vy * s) * 0.1f, (vz * s) * 0.1f);
        }
        if (mbLocal)
            mXform.Transform(&W);
        W = Vec3(W.x + P.x, W.y + P.y, W.z + P.z);
        if (mpSurface->Contains(&W)) {
            float depth = W.z - mpSurface->HeightAt(&W);
            cParticleDesc* d = mpDesc;
            if (depth < d->mKillBelow)
                return false;
            if (depth < d->mFloorMin) {
                mpSurface->NormalAt(&N, &W);
                if (mbLocal)
                    mXform.InverseRotate(&N);
                d = mpDesc;
                float t = d->mFloorMin - depth;
                t = t * t;
                float k = (d->mStrength * mDamping) * dt;
                p->mVel.x = p->mVel.x + (N.x * t) * k;
                p->mVel.y = p->mVel.y + (N.y * t) * k;
                p->mVel.z = p->mVel.z + (d->mScaleZ * (N.z * t)) * k;
                return true;
            }
        }
        return true;
    }

    if (desc->mBounce == 0.0f) {
        float h = mpSurface->HeightAt(&P);
        if (!Bit(mpDesc->mFlags, 18) && !(h > P.z))
            return true;
        p->mPos.x = P.x;
        p->mPos.y = P.y;
        p->mPos.z = h;
        mpSurface->NormalAt(&N, &P);
        if (mbLocal) {
            mXform.InverseTransformPoint(&p->mPos);
            mXform.InverseRotate(&N);
        }
        float d = -((p->mVel.x * N.x + p->mVel.z * N.z) + p->mVel.y * N.y);
        if (d > 0.0f) {
            p->mVel.x = p->mVel.x + N.x * d;
            p->mVel.y = p->mVel.y + N.y * d;
            p->mVel.z = p->mVel.z + N.z * d;
        }
        return true;
    }

    float h = mpSurface->HeightAt(&P);
    if (!(h > P.z))
        return true;
    float chance = mpDesc->mKillChance;
    if (chance != 0.0f) {
        if (chance == 1.0f)
            return false;
        if (!(mpDesc->mKillChance < g_Random.RandomDoubleUniform()))
            return false;
    }
    p->mPos.x = P.x;
    p->mPos.y = P.y;
    p->mPos.z = h;
    mpSurface->NormalAt(&N, &P);
    if (mbLocal) {
        mXform.InverseTransformPoint(&p->mPos);
        mXform.InverseRotate(&N);
    }
    float d = (p->mVel.x * N.x + p->mVel.z * N.z) + p->mVel.y * N.y;
    d = d * (mpDesc->mBounce + 1.0f);
    p->mVel.x = p->mVel.x - N.x * d;
    p->mVel.y = p->mVel.y - N.y * d;
    p->mVel.z = p->mVel.z - N.z * d;
    return true;
}
