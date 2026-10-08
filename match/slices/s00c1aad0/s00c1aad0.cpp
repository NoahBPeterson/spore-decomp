// Slice s00c1aad0: SP::cSPCreatureBase::FUN_00c1b020 (1898 bytes, __thiscall, one int argument).
//
// Creature "leap at the target" step. Looks the creature's current target up (holder at +0xe7c,
// interface 0xce9f6639) and, when the target direction is non-zero and within 0.7 (cosine) of this
// creature's forward vector, computes a launch velocity that arrives at the target's bounds centre
// (ballistic arc over the planet: tangential speed capped by the species data, vertical speed from
// the planet radius and gravity), pushes it as a velocity request (FUN_00c446d0) and switches the
// creature's animation (InterruptAnimation); at the end a locomotion request towards the target is
// submitted through the body's vtable slot 0xdc. Falls back to FUN_00c18b40 when there is no
// target, no direction, or the target is not in front.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (creature module: x87 for sqrt/divides, no EH frame).
#include "types.h"
#include <math.h>

struct Vector3 { float x, y, z; };

void operator_delete__(void* p);                                    // 0x00f47380 (cdecl)
extern const Vector3 kZeroVec;                                      // 0x0168d910
extern const float kLeapMargin;                                     // 0x01582fd8 (3.0)
extern const float kLeapSpeedDefault;                               // 0x01582fc0 (10.0)

// A locomotion request (0x74 bytes): a std-like vector at +0 plus goal data.
struct cLocomotionRequest {
    char* mpBegin;
    uint32_t pad[0x73 / 4];
    cLocomotionRequest();                                           // 0x00ac9850
    cLocomotionRequest(const Vector3* pos, float a, float b);       // 0x00ad29d0 (ret 0xc)
    __forceinline ~cLocomotionRequest()
    {
        if (mpBegin && ((int*)mpBegin)[-1])
            operator_delete__(mpBegin);
    }
};

// Secondary base at +0xc0 of a creature.
class Body {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10();
    virtual const Vector3* GetPos();                                // 0x2c
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16();
    virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21();
    virtual void s22();
    virtual const Vector3* GetForward(Vector3* out);                // 0x5c
    virtual void s24(); virtual void s25(); virtual void s26();
    virtual const float* GetBounds(float* out);                     // 0x6c (6 floats: min, max)
    virtual void s28();
    virtual float GetRadius();                                      // 0x74
    virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34();
    virtual void s35(); virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
    virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43(); virtual void s44();
    virtual void s45(); virtual void s46(); virtual void s47(); virtual void s48(); virtual void s49();
    virtual void s50(); virtual void s51(); virtual void s52(); virtual void s53(); virtual void s54();
    virtual void Submit(const cLocomotionRequest& req);             // 0xdc
    const Vector3* GetVelocity();                                   // 0x00d20610 (lea eax,[ecx+0x1c8])
    void FUN_00c446d0(const Vector3* v, bool flag);                 // 0x00c446d0 (ret 8)
};

// Species data.
struct SpeciesData {
    char pad0[0x548];
    float mLeapRangeAir;       // +0x548
    char pad54c[4];
    float mLeapRange;          // +0x550
    char pad554[0x610 - 0x554];
    uint32_t m610;             // +0x610
    char pad614[8];
    uint32_t m61c;             // +0x61c
    char pad620[0x698 - 0x620];
    uint32_t m698;             // +0x698
};

class PlanetModel {
public:
    float FUN_00b7e490();                                           // 0x00b7e490 (float in st0)
    float GetRadiusAt(const Vector3* pos);                          // 0x00b7ef70 (ret 4)
    float FUN_00b82310(Vector3* p);                                 // 0x00b82310 (ret 4)
};
PlanetModel* GetPlanetModel();                                      // 0x00b3d350
Vector3* normalized_safe(Vector3* out, const Vector3* in);          // 0x00449c20 (cdecl, sret-style: out first, returns out)

class IQueryTarget {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22();
    virtual void* Query(uint32_t id);                               // 0x5c
};

class cSPCreatureBase {
public:
    uint32_t vptr;
    char pad04[0xbc];
    Body mBody;                      // +0xc0
    char padc4[0x110 - 0xc4];
    uint32_t mFlags;                 // +0x110
    char pad114[0x137 - 0x114];
    bool mbLeaping;                  // +0x137
    char pad138[0x2b0 - 0x138];
    int mState;                      // +0x2b0
    char pad2b4[0xb20 - 0x2b4];
    SpeciesData* mpSpecies;          // +0xb20
    char padb24[0xbb0 - 0xb24];
    bool mbBB0;                      // +0xbb0
    char padbb1[0xe7c - 0xbb1];
    IQueryTarget* mpTargetHolder;    // +0xe7c

    float FUN_00c0ce80(int a, int b);                               // 0x00c0ce80 (ret 8)
    void FUN_00c15dc0(float f);                                     // 0x00c15dc0 (ret 4)
    void FUN_00c18b40(int arg);                                     // 0x00c18b40 (ret 4)
    void InterruptAnimation(uint32_t id, int a, int b);             // 0x00c12310 (ret 0xc)
    void FUN_00c1b020(int arg);
};

// A creature as seen through its target interface.
struct TargetCreature {
    char pad[0xc0];
    Body mBody;
};

// @ 0x00C1B020
void cSPCreatureBase::FUN_00c1b020(int arg)
{
    if (mpTargetHolder) {
        TargetCreature* other = (TargetCreature*)mpTargetHolder->Query(0xce9f6639);
        if (other) {
            Body* me = &mBody;
            Body* ob = &other->mBody;
            const Vector3* myPos = me->GetPos();
            const Vector3* otherPos = ob->GetPos();
            Vector3 d;
            d.z = otherPos->z - myPos->z;
            d.y = otherPos->y - myPos->y;
            d.x = otherPos->x - myPos->x;
            float inv = 1.0f / sqrtf((d.z * d.z + d.y * d.y) + d.x * d.x + 1e-8f);
            d.x = inv * d.x;
            d.y = d.y * inv;
            d.z = d.z * inv;
            Vector3 fwdTmp;
            if (!(d.x == kZeroVec.x && d.y == kZeroVec.y && d.z == kZeroVec.z)) {
                const Vector3* fwd = me->GetForward(&fwdTmp);
                if ((fwd->y * d.y + fwd->z * d.z) + fwd->x * d.x > 0.7f) {
                    float boundsTmp[6];
                    const float* bb = ob->GetBounds(boundsTmp);
                    Vector3 center;
                    center.x = (bb[3] + bb[0]) * 0.5f;
                    center.y = (bb[4] + bb[1]) * 0.5f;
                    center.z = (bb[5] + bb[2]) * 0.5f;
                    float otherRadius = ob->GetRadius();
                    ob->GetVelocity();
                    SpeciesData* sp = mpSpecies;
                    if (sp->m610 != 0) {
                        float thr = (me->GetRadius() * me->GetRadius() + otherRadius * otherRadius) +
                                    kLeapMargin * kLeapMargin;
                        const Vector3* p = me->GetPos();
                        float dz = p->z - center.z;
                        float dy = p->y - center.y;
                        float dx = p->x - center.x;
                        if (!(thr > (dz * dz + dy * dy) + dx * dx)) {
                            bool bLeaping = mbLeaping;
                            float range;
                            if (bLeaping) {
                                range = sp->mLeapRangeAir;
                            } else {
                                if (mFlags & 0x1000)
                                    goto L_submit;
                                range = sp->mLeapRange;
                            }
                            if (range > 0.0f) {
                                bool bBig;
                                if (sp->m61c > 0u || sp->mLeapRange > 0.0f)
                                    bBig = true;
                                else
                                    bBig = false;
                                PlanetModel* pm = GetPlanetModel();
                                float g = pm->FUN_00b7e490();
                                const Vector3* pos = me->GetPos();
                                Vector3 fwd2;
                                me->GetForward(&fwd2);
                                float pinv = 1.0f / sqrtf((pos->x * pos->x + pos->y * pos->y) + pos->z * pos->z + 1e-8f);
                                Vector3 up;
                                up.x = pos->x * pinv;
                                up.y = pinv * pos->y;
                                up.z = pinv * pos->z;
                                const Vector3* vel = ob->GetVelocity();
                                float posLen = sqrtf((pos->z * pos->z + pos->y * pos->y) + pos->x * pos->x);
                                pm->GetRadiusAt(pos);
                                float vup = (vel->x * up.x + vel->y * up.y) + vel->z * up.z;
                                Vector3 t;
                                t.x = vel->x - up.x * vup;
                                t.y = vel->y - up.y * vup;
                                t.z = vel->z - up.z * vup;
                                Vector3 t2;
                                t2.x = t.x;
                                t2.y = t.y;
                                t2.z = t.z;
                                float speed = sqrtf((t.x * t.x + t.z * t.z) + t.y * t.y);
                                float cap = kLeapSpeedDefault;
                                if (!bBig) {
                                    float v;
                                    if (mbBB0)
                                        v = FUN_00c0ce80(2, 1) + 10.0f;
                                    else
                                        v = FUN_00c0ce80(2, 0);
                                    const float* pc = &speed;
                                    if (v > speed)
                                        pc = &v;
                                    cap = *pc;
                                }
                                float dotv;
                                if (speed > 0.1f) {
                                    Vector3* n = normalized_safe(&t, &t2);
                                    dotv = (n->y * fwd2.y + n->z * fwd2.z) + n->x * fwd2.x;
                                } else {
                                    dotv = 1.0f;
                                }
                                float w = dotv + 0.5f;
                                float lo = 0.3f, hi = 1.0f;
                                __asm {
                                    movss xmm0, w
                                    maxss xmm0, lo
                                    minss xmm0, hi
                                    movss w, xmm0
                                }
                                float groundR = pm->FUN_00b82310(&center);
                                Vector3 e;
                                e.x = center.x - pos->x;
                                e.z = center.z - pos->z;
                                e.y = center.y - pos->y;
                                float e2 = (e.x * e.x + e.z * e.z) + e.y * e.y;
                                float tt = sqrtf(e2) / cap;
                                float einv = 1.0f / sqrtf(e2 + 1e-8f);
                                float vz = (groundR - posLen) / tt - (tt * g) * 0.5f;
                                const float* pv = &range;
                                if (!(vz > range))
                                    pv = &vz;
                                float vzc = *pv;
                                Vector3 acc;
                                acc.x = (up.x * vzc + (einv * e.x) * cap) - vel->x;
                                acc.y = (up.y * vzc + (e.y * einv) * cap) - vel->y;
                                acc.z = (up.z * vzc + (e.z * einv) * cap) - vel->z;
                                me->FUN_00c446d0(&acc, false);
                                FUN_00c15dc0((float)arg);
                                if (bLeaping) {
                                    if (sp->m698 > 0u)
                                        InterruptAnimation(0x77300f2, -1, 0);
                                    else
                                        InterruptAnimation(0x5261d56, -1, 0);
                                    mState = 3;
                                    mbLeaping = false;
                                } else {
                                    if (sp->m698 > 0u)
                                        InterruptAnimation(0x77300ff, -1, 0);
                                    else
                                        InterruptAnimation(0x5485a4c, -1, 0);
                                    me->Submit(cLocomotionRequest());
                                }
                            }
                        }
                    }
                L_submit:
                    me->Submit(cLocomotionRequest(ob->GetPos(), 1.0f, 2.0f));
                    return;
                }
            }
        }
    }
    FUN_00c18b40(arg);
}
