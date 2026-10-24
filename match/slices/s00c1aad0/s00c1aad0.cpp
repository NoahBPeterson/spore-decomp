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

// A 3x3 rotation block plus the frame that wraps a location:
// { uint16 kind; uint16 pad; Vector3 pos; float scale; cSPMatrix3 basis; } = 0x38 bytes.
struct cSPMatrix3 {
    float mRows[9];
    void Assign(const float* src);                                  // 0x0041cb40 (ret 4)
};

struct cSPLocalFrame {
    uint16_t kind;            // +0x0  (0)
    uint16_t pad0;            // +0x2  (0)
    Vector3 pos;              // +0x4  (kZeroVec)
    float scale;              // +0x10 (1.0f)
    cSPMatrix3 basis;         // +0x14 (source 0x0168db30)
};

// Object returned by Body::FUN_00c41ec0(); only +0x5c is read.
struct cAnimState {
    char pad[0x5c];
    int field5c;              // +0x5c
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
    void LocalToWorldTransform(cSPLocalFrame* frame);               // 0x00c897e0 (ret 4)
    cAnimState* FUN_00c41ec0();                                     // 0x00c41ec0
};

// Species data.
struct SpeciesData {
    char pad0[0x548];
    float mLeapRangeAir;       // +0x548
    char pad54c[4];
    float mLeapRange;          // +0x550
    char pad554[0x5c8 - 0x554];
    uint32_t mSprintTime;      // +0x5c8 (sprint duration, ms)
    float mSprintScale;        // +0x5cc (countdown ms per tick)
    int mSprintRate;           // +0x5d0 (added/subtracted from +0xfa0)
    char pad5d4[0x610 - 0x5d4];
    uint32_t m610;             // +0x610
    char pad614[8];
    uint32_t m61c;             // +0x61c
    char pad620[0x698 - 0x620];
    uint32_t m698;             // +0x698
    char pad69c[0x6b0 - 0x69c];
    float mSprintPitch;        // +0x6b0 (pitch applied while sprinting; <= 0 disables)
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
    char pad138[0x2a0 - 0x138];
    float mTurnRate;                 // +0x2a0 (FUN_00c0ce80 result)
    char pad2a4[0x2b0 - 0x2a4];
    int mState;                      // +0x2b0
    char pad2b4[0xb20 - 0x2b4];
    SpeciesData* mpSpecies;          // +0xb20
    char padb24[0xb58 - 0xb24];
    unsigned int mMovePad0 : 8;      // +0xb58 bits 0..7
    unsigned int mbFlagB8 : 1;       // +0xb58 bit 8
    unsigned int mbFlagB9 : 1;       // +0xb58 bit 9
    unsigned int mMovePad1 : 22;     // +0xb58 bits 10..31
    char padb5c[0xb80 - 0xb5c];
    float mStealthRate;              // +0xb80
    char padb84[0xbb0 - 0xb84];
    bool mbBB0;                      // +0xbb0 (sprinting)
    bool mbBB1;                      // +0xbb1 (stealthed)
    char padbb2[0xbb4 - 0xbb2];
    uint32_t mBB4;                   // +0xbb4 (sprint countdown)
    char padbb8[0xe58 - 0xbb8];
    float mE58;                      // +0xe58
    char pade5c[0xe7c - 0xe5c];
    IQueryTarget* mpTargetHolder;    // +0xe7c
    char pade80[0xf98 - 0xe80];
    int mF98;                        // +0xf98
    char padf9c[4];
    int mFA0;                        // +0xfa0
    unsigned int mFA4Pad0 : 5;       // +0xfa4 bits 0..4
    unsigned int mbSpeedBoost : 1;   // +0xfa4 bit 5
    unsigned int mFA4Pad1 : 26;      // +0xfa4 bits 6..31

    float FUN_00c0ce80(int a, int b);                               // 0x00c0ce80 (ret 8)
    void FUN_00c15dc0(float f);                                     // 0x00c15dc0 (ret 4)
    void FUN_00c18b40(int arg);                                     // 0x00c18b40 (ret 4)
    void InterruptAnimation(uint32_t id, int a, int b);             // 0x00c12310 (ret 0xc)
    int  FUN_00c0c080(int name);                                    // 0x00c0c080 (FindIndex, ret 4)
    void FUN_00c197a0(int index);                                   // 0x00c197a0 (ret 4)
    void FUN_00c0cff0(int a);                                       // 0x00c0cff0 (ret 4)
    void FUN_00c1aad0(unsigned int ms);
    void FUN_00c1ac70(int a, int b, int c, int d, int e, float f);
    void CanReachPointWithBodyPart(const cSPLocalFrame* frame, int a, int b, int c, int d,
                                   int e, float f);                 // 0x00c175d0 (ret 0x1c)
    void SetSprinting(bool sprint);
    void SetStealthed(bool enable, bool force);
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

// ---------------------------------------------------------------------------
// Movement-mode bookkeeping (sprint / stealth), body-part reachability and the
// two container helpers behind the creature goal vector / a 16-byte record vector.
// ---------------------------------------------------------------------------

class IMessageServer {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void Send(uint32_t id, int a, int b);                   // slot 5 (+0x14)
};
IMessageServer* MessageServer();                                    // 0x0067dcc0

struct cGameMode { int mUnused; };
struct cGameModeMgr {
    cGameMode* GetCurrentGameMode();                                // 0x00a42730
};
cGameModeMgr* FUN_00b3d320();                                       // 0x00b3d320
extern cGameMode kGameModeScenario;                                 // 0x01654c10
extern cGameMode kGameModeEditor;                                   // 0x01654c01
extern bool gFlag169e37c;                                           // 0x0169e37c
extern const float kSprintBonus;                                    // 0x0150c900
extern const float kStealthRateDefault;                             // 0x0150c8c0
extern const float kMatrix3Source[3];                               // 0x0168db30

class IAudioSystem {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7();
    virtual void* GetListener();                                    // slot 8 (+0x20)
};
IAudioSystem* GetSystemAT();                                        // 0x00a206f0
void Start3dSoundByName(uint32_t id, void* listener, float x, float y, float z);  // 0x00571f80

// @ 0x00c1aad0
void cSPCreatureBase::FUN_00c1aad0(unsigned int ms)
{
    char mode9 = (char)mbFlagB9;
    char mode8 = (char)mbFlagB8;
    if (mode9 || mode8) {
        unsigned int timer = mBB4;
        if (mbBB0) {
            SpeciesData* sp = mpSpecies;
            float pitch = sp->mSprintPitch;
            if (timer <= sp->mSprintTime && (pitch <= 0.0f || mE58 > 0.0f)) {
                FUN_00c15dc0((ms * 0.001f) * pitch);
                mBB4 = timer + ms;
                return;
            }
            mbBB0 = false;
            mBB4 = sp->mSprintTime;
            if (mbSpeedBoost) {
                mbSpeedBoost = false;
                mFA0 -= sp->mSprintRate;
                float speed;
                if (mbBB0)
                    speed = FUN_00c0ce80(2, 1) + kSprintBonus;
                else
                    speed = FUN_00c0ce80(mF98, 0);
                mTurnRate = speed;
            }
            int idx = FUN_00c0c080(0x27);
            if (idx == -1)
                idx = FUN_00c0c080(0x50);
            FUN_00c197a0(idx);
            return;
        }
        if (timer != 0) {
            unsigned int dec = (unsigned int)((float)ms * mpSpecies->mSprintScale);
            if (timer >= dec)
                mBB4 = timer - dec;
            else
                mBB4 = 0;
        }
    }
}

// @ 0x00c1ac70
void cSPCreatureBase::FUN_00c1ac70(int a, int b, int c, int d, int e, float f)
{
    cSPLocalFrame frame;
    frame.kind = 0;
    frame.pad0 = 0;
    frame.pos.x = kZeroVec.x;
    frame.pos.y = kZeroVec.y;
    frame.pos.z = kZeroVec.z;
    frame.scale = 1.0f;
    frame.basis.Assign(kMatrix3Source);
    mBody.LocalToWorldTransform(&frame);
    CanReachPointWithBodyPart(&frame, a, b, c, d, e, f);
}

// @ 0x00c1ad10
void cSPCreatureBase::SetSprinting(bool sprint)
{
    bool bBusy = mBody.FUN_00c41ec0()->field5c != 0;

    if (sprint) {
        if ((char)mbFlagB9) {
            if (FUN_00b3d320()->GetCurrentGameMode() == &kGameModeScenario)
                MessageServer()->Send(0x7c772b7, 0, 0);
        }
        uint8_t boosted = (uint8_t)mbSpeedBoost;
        mbBB0 = true;
        mbSpeedBoost = true;
        if (boosted != 1) {
            mFA0 += mpSpecies->mSprintRate * (boosted == 0 ? 1 : -1);
            float speed;
            if (mbBB0)
                speed = FUN_00c0ce80(2, 1) + kSprintBonus;
            else
                speed = FUN_00c0ce80(mF98, 0);
            mTurnRate = speed;
        }
        if (((char)mbFlagB9) && FUN_00b3d320()->GetCurrentGameMode() == &kGameModeEditor) {
            if (!bBusy) {
                gFlag169e37c = true;
                return;
            }
            FUN_00c0cff0(mF98);
            return;
        }
    } else {
        if ((char)mbFlagB9) {
            int idx = FUN_00c0c080(0x27);
            if (idx == -1)
                idx = FUN_00c0c080(0x50);
            FUN_00c197a0(idx);
        }
        mbBB0 = false;
        if (mbSpeedBoost) {
            mbSpeedBoost = false;
            mFA0 -= mpSpecies->mSprintRate;
            float speed;
            if (mbBB0)
                speed = FUN_00c0ce80(2, 1) + kSprintBonus;
            else
                speed = FUN_00c0ce80(mF98, 0);
            mTurnRate = speed;
        }
    }

    if (bBusy)
        FUN_00c0cff0(mF98);
}

// @ 0x00c1aed0
void cSPCreatureBase::SetStealthed(bool enable, bool force)
{
    if (enable) {
        if (!force && FUN_00c0c080(0xd) == -1 && FUN_00c0c080(0x52) == -1)
            return;
        mStealthRate = 0.0f;
        if (mbBB1)
            return;
        mbBB1 = true;
        const Vector3* pos = mBody.GetPos();
        IAudioSystem* sys = GetSystemAT();
        void* listener = sys ? sys->GetListener() : 0;
        Start3dSoundByName(0xc881120e, listener, pos->x, pos->y, pos->z);
    } else {
        if (!mbBB1)
            return;
        char mode9 = (char)mbFlagB9;
        if (mode9) {
            int idx = FUN_00c0c080(0xd);
            if (idx == -1)
                idx = FUN_00c0c080(0x52);
            FUN_00c197a0(idx);
        } else {
            mStealthRate = kStealthRateDefault;
        }
        mbBB1 = false;
        const Vector3* pos = mBody.GetPos();
        IAudioSystem* sys = GetSystemAT();
        void* listener = sys ? sys->GetListener() : 0;
        Start3dSoundByName(0x529fec69, listener, pos->x, pos->y, pos->z);
    }
}

// ----- creature goal vector (60-byte records) ------------------------------

struct cGoalRecord {                 // 0x3c bytes
    uint32_t mWords[15];
};

// Raw byte pointers (EASTL-style storage); one record is 0x3c bytes.
struct cGoalVector {
    char* mpBegin;                   // +0x0
    char* mpEnd;                     // +0x4
    char* mpCapacity;                // +0x8
    cGoalVector& Assign(const cGoalVector& src);        // 0x00c1b790 (ret 4)
};

char* FUN_00c19cb0(int n, const char* first, const char* last);             // 0x00c19cb0
char* FUN_00ac4360(const char* first, const char* last, char* dest);        // 0x00ac4360
cGoalRecord FUN_00b3f260(const char* first, const char* last, char* dest,
                         const char* extra);                            // 0x00b3f260

// @ 0x00c1b790
cGoalVector& cGoalVector::Assign(const cGoalVector& other)
{
    if (&other != this) {
        int n = (other.mpEnd - other.mpBegin) / 60;
        if ((uint32_t)((mpCapacity - mpBegin) / 60) < (uint32_t)n) {
            char* p = FUN_00c19cb0(n, other.mpBegin, other.mpEnd);
            // EASTL allocation header: the element count lives 4 bytes before the block.
            if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0)
                operator_delete__(mpBegin);
            mpBegin = p;
            mpCapacity = p + n * 60;
        } else {
            int m = (mpEnd - mpBegin) / 60;
            if ((uint32_t)m >= (uint32_t)n) {
                FUN_00ac4360(other.mpBegin, other.mpEnd, mpBegin);
            } else {
                FUN_00ac4360(other.mpBegin, other.mpBegin + m * 60, mpBegin);
                FUN_00b3f260(other.mpBegin + m * 60, other.mpEnd, mpEnd, other.mpEnd);
            }
        }
        mpEnd = mpBegin + n * 60;
    }
    return *this;
}

// ----- 16-byte record vector loaded from a stream ---------------------------

struct Quad16 {                      // 0x10 bytes
    uint32_t mWords[4];
};

struct cQuad16Vector {
    Quad16* mpBegin;                 // +0x0
    Quad16* mpEnd;                   // +0x4
    Quad16* mpCapacity;              // +0x8
    void reserve(int n);             // 0x00c53690 (ret 4)
    void PushBackSlow(Quad16* pos, const Quad16* value);   // 0x00c19d10 (ret 8)
};

class IStreamNode {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5();
    virtual IStreamNode* GetReader();    // +0x18
    virtual void EndChunk();             // +0x1c
    virtual IStreamNode* GetSubNode();   // +0x20
};

Quad16* copy_705250(const Quad16* first, const Quad16* last, Quad16* dest);   // 0x00705250
void* ReadInt32(void* reader, int* out, int count, int flags);                 // 0x0093a780
void FUN_00c0b100(IStreamNode* s, Quad16* out);                                // 0x00c0b100


// @ 0x00c1b8c0
void FUN_00c1b8c0(IStreamNode* s, cQuad16Vector* v)
{
    Quad16* first = v->mpBegin;
    Quad16* last = v->mpEnd;
    copy_705250(last, last, first);
    v->mpEnd -= (last - first);

    int count = 0;
    IStreamNode* sub = s->GetSubNode();
    void* reader = sub->GetReader();
    ReadInt32(reader, &count, 1, 0);
    v->reserve(count);
    for (unsigned int i = 0; i < (unsigned int)count; ++i) {
        Quad16 e;
        FUN_00c0b100(s, &e);
        if (v->mpEnd < v->mpCapacity) {
            Quad16* p = v->mpEnd;
            v->mpEnd = p + 1;
            if (p)
                *p = e;
        } else {
            v->PushBackSlow(v->mpEnd, &e);
        }
    }
    s->EndChunk();
}
