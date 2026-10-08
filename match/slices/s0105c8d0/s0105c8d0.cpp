// Slice s0105c8d0 -- FUN_0105c9d0: moving-object steering update (re-seats the object on the
// point-on-sphere constraint around a center, blends its velocity toward a heading, re-aims the
// target point and refreshes the follow position).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc: no EH-requiring locals).
#include "types.h"
#include <math.h>

#define VPAD(n) virtual void vpad##n()

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float a, float b, float c) : x(a), y(b), z(c) {}
};
Vector3 normalized_safe(const Vector3& v);              // 0x00449c20 (cdecl, hidden sret)

struct cSpatialPart {                                   // sub-object at +0x34
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8); VPAD(9); VPAD(10);
    virtual const Vector3* GetPosition();               // +0x2c
};

struct cSPTimer {
    void Stop();                                        // 0x00bc3110
    void Restart();                                     // 0x00bc3130
};

struct cSteerConfig {                                   // singleton at 0x0168df68
    float GetBlend();                                   // 0x00c37470 (+0xc8)
    float GetDamping();                                 // 0x00c37480 (+0xcc)
};
cSteerConfig* SteerConfig();                            // 0x00c37360

extern const float kCoupling;                           // 0x015b8df4 = 5.0
extern const float kMinSpeed;                           // 0x015b8df0 = 0.001
extern const float kHeadingDot;                         // 0x015b8dec = -0.8
extern const float kRetargetDist;                       // 0x015b8de8 = 5.0
extern const float kDirDot;                             // 0x015b8de4 = -0.8
extern const float kLead;                               // 0x015b8de0 = 2.0

struct cSteered {
    uint32_t pad00[0x34 / 4];
    cSpatialPart mAnchor;                               // +0x34
    uint32_t pad38[(0x60c - 0x38) / 4];
    Vector3 mPush;                                      // +0x60c
    uint32_t pad618[(0x624 - 0x618) / 4];
    uint8_t mb624;
    uint8_t pad625[0x648 - 0x625];
    cSPTimer mTimerA;                                   // +0x648
    uint32_t pad64c[(0x668 - 0x64c) / 4];
    cSPTimer mTimerB;                                   // +0x668
    uint32_t pad66c[(0x718 - 0x66c) / 4];
    Vector3 mPos;                                       // +0x718
    Vector3 mVel;                                       // +0x724
    uint32_t pad730[(0x74c - 0x730) / 4];
    uint8_t mbTargetValid;                              // +0x74c
    uint8_t pad74d[3];
    Vector3 mTarget;                                    // +0x750
    uint32_t pad75c[(0x768 - 0x75c) / 4];
    float mTargetDist;                                  // +0x768 (read via GetTargetDist)

    float GetTargetDist();                              // 0x00c37120
    void SetTargetDist(float d);                        // 0x00c3daa0
    float GetFollowDist();                              // 0x00c3be10
    void SetFollow(float w, const Vector3* v);          // 0x00c3db50
};

// @ 0x0105c9d0
void __stdcall FUN_0105c9d0(cSteered* o, const Vector3* a2, const Vector3* a3, float a4)
{
    const Vector3* c = o->mAnchor.GetPosition();
    Vector3 pos = o->mPos;
    float iu = 1.0f / sqrtf(pos.x * pos.x + pos.y * pos.y + pos.z * pos.z + 1e-8f);
    Vector3 up(pos.x * iu, pos.y * iu, pos.z * iu);
    Vector3 d(pos.x - c->x, pos.y - c->y, pos.z - c->z);
    float speed = sqrtf(o->mVel.x * o->mVel.x + o->mVel.y * o->mVel.y + o->mVel.z * o->mVel.z);
    float dl = sqrtf(d.x * d.x + d.y * d.y + d.z * d.z);
    float delta = dl - sqrtf(a2->x * a2->x + a2->y * a2->y + a2->z * a2->z);
    float id = 1.0f / sqrtf(d.x * d.x + d.y * d.y + d.z * d.z + 1e-8f);
    o->mPos.x = a2->x + (c->x + (id * d.x) * delta);
    o->mPos.y = a2->y + (c->y + (id * d.y) * delta);
    o->mPos.z = a2->z + (c->z + (id * d.z) * delta);

    float blend = SteerConfig()->GetBlend();
    float damp = SteerConfig()->GetDamping();
    float k = fabsf(o->mVel.x * a3->x + o->mVel.z * a3->z + o->mVel.y * a3->y) * (blend + 1.0f);
    Vector3 t(a3->x * k, a3->y * k, a3->z * k);
    o->mPush.y += t.y * kCoupling;
    o->mPush.x += t.x * kCoupling;
    o->mPush.z += t.z * kCoupling;
    Vector3 nv(t.x + o->mVel.x, o->mVel.y + t.y, o->mVel.z + t.z);
    if (nv.z * nv.z + nv.y * nv.y + nv.x * nv.x < 1.52587890625e-05f)
        nv = up;

    Vector3 heading;
    const Vector3* h;
    if (speed > 1.52587890625e-05f) {
        float vx = o->mVel.x, vy = o->mVel.y, vz = o->mVel.z;
        float iv = 1.0f / sqrtf(vz * vz + vy * vy + vx * vx + 1e-8f);
        heading = Vector3(iv * vx, iv * vy, iv * vz);
        h = &heading;
    } else {
        h = &up;
    }
    float dot = (h->z * a3->z + h->y * a3->y) + h->x * a3->x;
    float blendDot = dot + 1.0f;
    float in = 1.0f / sqrtf(nv.x * nv.x + nv.y * nv.y + nv.z * nv.z + 1e-8f);
    Vector3 nd(in * nv.x, nv.y * in, in * nv.z);
    if (blendDot <= 0.0f)
        blendDot = 0.0f;
    if (1.0f <= blendDot)
        blendDot = 1.0f;
    const float* sp = &speed;
    if (speed <= kMinSpeed)
        sp = &kMinSpeed;
    float nspeed = *sp * ((1.0f - damp) * blendDot + damp);
    o->mVel.x = nd.x * nspeed;
    o->mVel.y = nd.y * nspeed;
    o->mVel.z = nd.z * nspeed;

    float len;
    bool reaim = true;
    if (!o->mbTargetValid && !(dot < kHeadingDot)) {
        Vector3 tg(o->mTarget.x - pos.x, o->mTarget.y - pos.y, o->mTarget.z - pos.z);
        float tl = sqrtf(tg.y * tg.y + tg.z * tg.z + tg.x * tg.x);
        if (!(tl < kRetargetDist)) {
            Vector3 dir = normalized_safe(tg);
            const Vector3& aim = normalized_safe(*a2);
            if (!((aim.y * dir.y + aim.z * dir.z) + dir.x * aim.x < kDirDot))
                reaim = false;
        }
    }
    if (reaim) {
        float l2 = a2->x * a2->x + a2->y * a2->y + a2->z * a2->z;
        float lead = sqrtf(l2) + kLead;
        float il = 1.0f / sqrtf(l2 + 1e-8f);
        o->mTarget.x = (a2->x * il) * lead + pos.x;
        o->mTarget.y = (a2->y * il) * lead + pos.y;
        o->mTarget.z = (a2->z * il) * lead + pos.z;
        o->mbTargetValid = 0;
        o->mTimerA.Stop();
        o->mb624 = 0;
        len = sqrtf(o->mTarget.x * o->mTarget.x + o->mTarget.y * o->mTarget.y + o->mTarget.z * o->mTarget.z);
        o->SetTargetDist(len);
    } else {
        len = sqrtf(o->mTarget.x * o->mTarget.x + o->mTarget.y * o->mTarget.y + o->mTarget.z * o->mTarget.z);
        if (len > o->GetTargetDist())
            o->SetTargetDist(len);
    }
    o->mTimerB.Restart();
    float f = o->GetFollowDist();
    float ia = 1.0f / sqrtf(a2->z * a2->z + (a2->y * a2->y + a2->x * a2->x) + 1e-8f);
    Vector3 np(o->mPos.x - (a2->x * ia) * f, o->mPos.y - (a2->y * ia) * f, o->mPos.z - (a2->z * ia) * f);
    o->SetFollow(a4, &np);
}
