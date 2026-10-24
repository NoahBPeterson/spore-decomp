// Slice s00d6e3a0 -- SP behaviour-tree combat tick / decide callbacks.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

// ---------------------------------------------------------------------------
// callees (call targets are masked by the checker).  All addresses are used
// through explicit calling-convention casts so cl emits the right ABI.
// ---------------------------------------------------------------------------
#define TC0(ret, name) ((ret(__thiscall*)(void*)) name)
#define TC1(ret, name) ((ret(__thiscall*)(void*, void*)) name)
#define TC2(ret, name) ((ret(__thiscall*)(void*, void*, void*)) name)
#define TC3(ret, name) ((ret(__thiscall*)(void*, void*, void*, void*)) name)
#define TC4(ret, name) ((ret(__thiscall*)(void*, void*, void*, void*, void*)) name)
#define TC5(ret, name) ((ret(__thiscall*)(void*, void*, void*, void*, void*, void*)) name)
#define TCS(ret, params, name) ((ret(__thiscall*)params) name)

void*  SP_NounManager();                              // 0x00b3d300 cdecl
void*  FUN_00b1fdb0(void*);                           // 0x00b1fdb0 thiscall (GetAvatar)
void*  FUN_00d99500(void*);                           // 0x00d99500 cdecl
void*  FUN_00d99470(void*);                           // 0x00d99470 cdecl
void*  FUN_00d99420(void*, void*);                    // 0x00d99420 cdecl
void*  FUN_00d996e0(void*, void*);                    // 0x00d996e0 cdecl
float  FUN_00d99ac0(void*, void*, int);               // 0x00d99ac0 cdecl
void   FUN_00d997e0(void*);                           // 0x00d997e0 thiscall
void   FUN_00d99e20(void*, void*);                    // 0x00d99e20 cdecl
void*  FUN_00d20610(void*);                           // 0x00d20610 thiscall (GetVelocity)
void*  FUN_00c0ee60(void*);                           // 0x00c0ee60 thiscall
void*  FUN_00c0ee70(void*);                           // 0x00c0ee70 thiscall
void*  FUN_00c41ec0(void*);                           // 0x00c41ec0 thiscall
void*  FUN_00c0bc00(void*, void*, void*);             // 0x00c0bc00 thiscall
void*  FUN_00b3d4c0();                                // 0x00b3d4c0 cdecl
int    FUN_00ba3f90(void*, void*, void*, void*);      // 0x00ba3f90 thiscall
int    FUN_00c0f570(void*);                           // 0x00c0f570 thiscall (CountValid)
uint32_t FUN_00c0f780(void*);                         // 0x00c0f780 thiscall (FindFirstValid)
void*  FUN_00c0f8a0(void*, uint32_t);                 // 0x00c0f8a0 thiscall (GetAt)
char   FUN_00c0b860(void*, void*);                    // 0x00c0b860 thiscall
char   FUN_00c0e8d0(void*, void*, int);               // 0x00c0e8d0 thiscall
char   FUN_00c02600(void*, void*);                    // 0x00c02600 thiscall (IsValidNeighbourEntry)
void   FUN_00b3d850(void*);                           // 0x00b3d850 thiscall
void*  FUN_00bc97f0(void*, int, int, float, void*);   // 0x00bc97f0 thiscall
char   FUN_00d6e1a0(void*, void*);                    // 0x00d6e1a0 cdecl
int    FUN_00bc96a0(void*, int, int);                 // 0x00bc96a0 thiscall (Play)

// PLAY_FIGHT / PERSONAL_SPACE tick callees
void*  FUN_00c04590(void*);                           // 0x00c04590 thiscall (Get)
char   FUN_00c12400(void*, int);                      // 0x00c12400 thiscall (AnimationFinished)
char   FUN_00c42e20(void*);                           // 0x00c42e20 thiscall (IsNearGoal)
uint32_t FUN_00a68fb0(void*, uint32_t);               // 0x00a68fb0 thiscall (RandomUint32Uniform)
int    FUN_00c149c0(void*, int, void*, int, int);     // 0x00c149c0 thiscall
char   FUN_00bc9b50(void*);                           // 0x00bc9b50 thiscall
void*  FUN_00c6acc0(void*, float, float);             // 0x00c6acc0 thiscall (GetPosition)
void*  FUN_00b3d350(void*, void*);                    // 0x00b3d350 (PlanetModel)
void   FUN_00b81780(void*, void*, void*);             // 0x00b81780 thiscall (MakeRandomWorldPosition)
float* FUN_00449c20(void*, void*);                    // 0x00449c20 cdecl (normalized_safe)
void   FUN_00c1c5c0(void*, int, void*, void*, int);   // 0x00c1c5c0 thiscall
char   FUN_00c123f0(void*, int);                      // 0x00c123f0 thiscall
void   FUN_00c14940(void*, int, void*, int, int);     // 0x00c14940 thiscall
void*  FUN_00699800(void*, void*);                    // 0x00699800 cdecl (SegmentPhysics)
void   FUN_00b815a0(void*, void*, void*);             // 0x00b815a0 thiscall (DirectionToSurfacePosition)
void   FUN_00c14750(int);                             // 0x00c14750
char   FUN_00c0e0c0(int);                             // 0x00c0e0c0

float            g_1471064;    // 0x01471064
float            g_147bc9c;    // 0x0147bc9c
float            g_147bc8c;    // 0x0147bc8c
float            g_147bc88;    // 0x0147bc88
float            g_1470f1c;    // 0x01470f1c
float            g_1485720;    // 0x01485720
float            g_1486110;    // 0x01486110
float            g_1473c70;    // 0x01473c70
float            g_13eb8b0;    // 0x013eb8b0
float            g_147bc98;    // 0x0147bc98
float            g_13ec480;    // 0x013ec480
unsigned char    g_1582df6;    // 0x01582df6

// ---------------------------------------------------------------------------
// object layouts
// ---------------------------------------------------------------------------
struct Vec3 { float x, y, z; };

// locomotive / spatial sub-object (sits at Creature+0xc0 and is returned by
// several helpers).  Methods are dispatched through the leading vptr.
struct Spatial {
    void* vptr;              // +0x00
    char  _p004[0x14 - 0x04];
    Vec3  mPos;              // +0x14
    char  _p020[0x5c - 0x20];
    int   mField5c;          // +0x5c
};

// nSPBehaviorTree::behavior_stimuli
struct Stimuli {
    char  _p00[4];
    void* mpAny;             // +0x04  (object reached through a vtable)
};

// behaviour state stored at self->mpB4C->mp600
struct State {
    char   _p000[0x10];
    int    mField10;         // +0x10
    char   _p014[0x1a4 - 0x14];
    int    mMode;            // +0x1a4
    float  mAccum;           // +0x1a8
    void*  mpPartner;        // +0x1ac
    int    mAnim0;           // +0x1b0
    int    mAnim1;           // +0x1b4
};

// PERSONAL_SPACE state (arg in personal-space tick/decide); the game struct is
// byte-packed, so mField2d sits at the unaligned offset +0x2d.
#pragma pack(push, 1)
struct PState {
    int    mField0;          // +0x00
    int    mMode;            // +0x04
    float  mAccum;           // +0x08
    int    mAnim;            // +0x0c
    char   _p010[0x2d - 0x10];
    int    mField2d;         // +0x2d
};
#pragma pack(pop)

struct Holder {
    char   _p000[0x600];
    State* mpState;          // +0x600
};

// neighbour entry filtering iterator (12-byte local)
struct NIter {
    void** mpCur;            // +0x00
    void** mpEnd;            // +0x04
    void*  mpFilt;           // +0x08
};

struct Creature {
    void*      vptr;                          // +0x0000
    char       _p004[0x0c0 - 0x004];
    Spatial    mLoco;                         // +0x00c0
    char       _p120[0x5a8 - 0x120];
    char       mSub5a8[0xb20 - 0x5a8];        // +0x05a8
    void*      mpB20;                         // +0x0b20
    char       _p0b24[0xb4c - 0x0b24];
    Holder*    mpB4C;                         // +0x0b4c
    char       _p0b50[0xb58 - 0x0b50];
    uint32_t   mFlagsB58;                     // +0x0b58
    uint8_t    mByteB5C;                      // +0x0b5c
    uint8_t    _p0b5d;
    uint8_t    mByteB5E;                      // +0x0b5e
    char       _p0b5f[0x1124 - 0x0b5f];
    void**     mpBegin1124;                   // +0x1124
    void**     mpEnd1128;                     // +0x1128
    char       _p112c[0x140c - 0x112c];
    void**     mpBegin140c;                   // +0x140c
    void**     mpEnd1410;                     // +0x1410
};

// ===========================================================================
// @ 0x00d6e3a0  SP::PLAY_FIGHT_Tick
// ===========================================================================
uint8_t __cdecl PLAY_FIGHT_Tick(Creature* self, int a1, int a2, int a3,
                                int a4, int a5, int a6, float dt)
{
    (void)a1; (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    State* st = self->mpB4C->mpState;
    if (st->mMode != 0 && st->mField10 == 1)
        return 0;
    Creature* partner = (Creature*)st->mpPartner;
    if (self == partner)
        return 1;

    Spatial* goal = (Spatial*)TC0(void*, FUN_00c04590)((void*)self);

    int mode = st->mMode;
    if (mode == 0) {
        float acc = st->mAccum - dt;
        st->mAccum = acc;
        if (acc < 0.0f)
            return 0;
        if (!TC0(char, FUN_00bc9b50)((void*)st))
            return 1;
        st->mMode = 1;
        void* p1 = TCS(void*, (void*, float, float), FUN_00c6acc0)((void*)goal, 5.0f, 10.0f);
        void* pm1 = FUN_00b3d350(p1, (void*)0);
        Vec3 vA; Vec3 vB;
        TC2(void, FUN_00b81780)(pm1, &vA, p1);
        void* p2 = TCS(void*, (void*, float, float), FUN_00c6acc0)((void*)goal, 5.0f, 10.0f);
        void* pm2 = FUN_00b3d350(p2, &vA);
        TC2(void, FUN_00b81780)(pm2, &vB, p2);

        Vec3 d1;
        d1.x = vB.x - vA.x;
        d1.y = vB.y - vA.y;
        d1.z = vB.z - vA.z;
        Vec3 n1;
        FUN_00449c20(&n1, &d1);
        TCS(void, (void*, int, void*, void*, int), FUN_00c1c5c0)((void*)self, 2, &vA, &n1, 1);

        Vec3 d2;
        d2.x = vA.x - vB.x;
        d2.y = vA.y - vB.y;
        d2.z = vA.z - vB.z;
        Vec3 n2;
        FUN_00449c20(&n2, &d2);
        TCS(void, (void*, int, void*, void*, int), FUN_00c1c5c0)((void*)partner, 2, &vB, &n2, 1);
        return 1;
    }
    if (mode == 1) {
        if (!TC0(char, FUN_00c42e20)((void*)&self->mLoco))
            return 1;
        if (!TC0(char, FUN_00c42e20)((void*)&partner->mLoco))
            return 1;
        st->mMode = 2;
        void* pa = partner ? (void*)&partner->mSub5a8 : 0;
        ((void(__thiscall*)(void*, void*, int, int)) (*(void***)self)[0x84 / 4])
            ((void*)self, pa, 1, 0);
        ((void(__thiscall*)(void*, void*, int, int)) (*(void***)partner)[0x84 / 4])
            ((void*)partner, (void*)&self->mSub5a8, 1, 0);
        uint32_t r = TCS(uint32_t, (void*, uint32_t), FUN_00a68fb0)((void*)0x1601760, 2);
        int animA = 0x530282c - (uint32_t)(r != 0);
        st->mAnim0 = TCS(int, (void*, int, void*, int, int), FUN_00c149c0)((void*)self, animA, pa, -1, -1);
        uint32_t r2 = TCS(uint32_t, (void*, uint32_t), FUN_00a68fb0)((void*)0x1601760, 2);
        int animB = 0x530282e - (uint32_t)(r2 != 0);
        st->mAnim1 = TCS(int, (void*, int, void*, int, int), FUN_00c149c0)((void*)partner, animB,
                                            (void*)&self->mSub5a8, -1, -1);
        return 1;
    }
    if (mode == 2) {
        if (TCS(char, (void*, int), FUN_00c12400)((void*)self, st->mAnim0)
            && TCS(char, (void*, int), FUN_00c12400)((void*)partner, st->mAnim1))
            return 0;
    }
    return 1;
}

// ===========================================================================
// @ 0x00d6e680
// ===========================================================================
float __cdecl FUN_00d6e680(Creature* self, int a1, int a2, int a3,
                           Stimuli* stimuli, char* out)
{
    (void)a1; (void)a2; (void)a3;
    void* mgr = SP_NounManager();
    void* av  = TC0(void*, FUN_00b1fdb0)(mgr);
    Creature* other = (Creature*)FUN_00d99500(av);
    if (other != 0) {
        void* iVar7 = self ? (void*)&self->mSub5a8 : 0;
        void* iVar5 = TC0(void*, FUN_00c0ee60)((void*)other);
        if (iVar5 != iVar7) {
            if (stimuli != 0)
                TC0(void, FUN_00d997e0)((void*)stimuli);
            *out = 1;
            stimuli->mpAny = (void*)&other->mSub5a8;
            void* p = self ? (void*)&self->mLoco : 0;
            Spatial* pcVar1 = &other->mLoco;
            float r = FUN_00d99ac0((void*)pcVar1, p, 1);
            if (r < g_1471064) {
                float* vel = (float*)TC0(void*, FUN_00d20610)((void*)pcVar1);
                float v2 = vel[1] * vel[1] + vel[2] * vel[2] + vel[0] * vel[0];
                if (v2 > g_147bc9c) {
                    Spatial* q = (Spatial*)TC0(void*, FUN_00c41ec0)((void*)&self->mLoco);
                    if (q->mField5c != 0) {
                        Vec3* pos = ((Vec3*(__thiscall*)(void*))
                                     (*(void***)pcVar1)[0x2c / 4])((void*)pcVar1);
                        float f9  = q->mPos.x - pos->x;
                        float f10 = q->mPos.y - pos->y;
                        float f11 = q->mPos.z - pos->z;
                        if (f9 * f9 + f10 * f10 + f11 * f11 < r)
                            return 0.0f;
                    }
                    return 1.0f;
                }
            }
        }
    }
    return 0.0f;
}

// ===========================================================================
// @ 0x00d6e7c0  SP::PERSONAL_SPACE_Decide
// ===========================================================================
float __cdecl FUN_00d6e7c0(Creature* self, int a1, int a2, int a3,
                           Stimuli* stimuli, char* out, int a6, PState* p7)
{
    (void)a1; (void)a2; (void)a3; (void)a6;
    if (stimuli != 0)
        TC0(void, FUN_00d997e0)((void*)stimuli);
    *out = 1;

    void* uVar2 = FUN_00d99420((void*)((char*)self->mpB4C + 0x1d0),
                               (void*)p7->mField2d);
    FUN_00d996e0(uVar2, (void*)stimuli);

    void* piVar1 = stimuli->mpAny;
    uint32_t arg = piVar1
        ? ((uint32_t(__thiscall*)(void*, uint32_t)) (*(void***)piVar1)[0x5c / 4])
              (piVar1, 0xce9f6639u)
        : 0;
    Creature* pcVar3 = (Creature*)FUN_00d99470((void*)arg);

    Spatial* pfVar6;
    if (pcVar3 == 0) {
        pfVar6 = 0;
    } else {
        pfVar6 = &pcVar3->mLoco;
        if (pfVar6 != 0)
            goto have_partner;
    }

    if (TCS(int, (void*, int, int), FUN_00bc96a0)((void*)((char*)self->mpB4C + 8), 0x4000000, 0)) {
        void* av = TC0(void*, FUN_00b1fdb0)(SP_NounManager());
        pcVar3 = (Creature*)av;
        if (av == 0)
            pfVar6 = 0;
        else
            pfVar6 = &((Creature*)av)->mLoco;
        void* av2 = TC0(void*, FUN_00b1fdb0)(SP_NounManager());
        void* val = av2 ? (void*)&((Creature*)av2)->mSub5a8 : 0;
        stimuli->mpAny = val;
    }

have_partner:
    if (pcVar3 != 0) {
        void* t = TC0(void*, FUN_00c0ee70)((void*)pcVar3);
        if (t != (void*)self) {
            float thr = g_147bc88;
            void* iv = FUN_00b3d4c0();
            if (iv != 0) {
                void* u = TC2(void*, FUN_00c0bc00)((void*)self, (void*)self,
                                                   (void*)pcVar3);
                int r = TC3(int, FUN_00ba3f90)(iv, u, (void*)self, (void*)pcVar3);
                if (r == 4 || r == 6)
                    thr = g_1470f1c;
            }
            float res = FUN_00d99ac0((void*)pfVar6, (void*)&self->mLoco, 1);
            if (res < thr)
                return 1.0f;
        }
    }
    return 0.0f;
}

// ===========================================================================
// @ 0x00d6e910  SP::PERSONAL_SPACE_Tick
// ===========================================================================
uint8_t __cdecl PERSONAL_SPACE_Tick(Creature* self, int a1, int a2, int a3,
                                    PState* other, PState* st, float dt)
{
    (void)a1; (void)a2; (void)a3;
    void* t = TC0(void*, FUN_00c0ee70)((void*)self);
    Creature* pcVar3 = (Creature*)FUN_00d99470(t);
    if (pcVar3 == 0)
        return 0;
    void* t2 = TC0(void*, FUN_00c0ee70)((void*)pcVar3);
    if (t2 == (void*)self)
        return 0;

    Spatial* pfVar7  = &pcVar3->mLoco;
    Spatial* pfVar11 = self ? &self->mLoco : 0;

    if (st->mMode == 0) {
        float r = FUN_00d99ac0((void*)pfVar7, (void*)pfVar11, 1);
        if (1.0f <= r) {
            if (st->mAnim == 0 || TCS(char, (void*, int), FUN_00c123f0)((void*)self, st->mAnim)) {
                st->mAnim = 0x4212960;
                TCS(void, (void*, int, void*, int, int), FUN_00c14940)((void*)self, 0x4212960, (void*)pfVar7, -1, -1);
            }
            st->mAccum = st->mAccum + dt;
            if (st->mAccum <= 5.0f)
                return 1;
        }
        st->mMode = 1;
        return 1;
    }

    if (st->mMode == 1) {
        float f12 = ((float(__thiscall*)(void*))
                     (*(void***)pfVar7)[0x74 / 4])((void*)pfVar7);
        float f13 = ((float(__thiscall*)(void*))
                     (*(void***)pfVar11)[0x74 / 4])((void*)pfVar11);
        char c = ((char(__thiscall*)(void*))
                  (*(void***)self)[0xd0 / 4])((void*)self);
        float dist = (c == 0) ? 7.5f : 1.0f;
        dist = dist + (f13 + f12);

        Vec3* pfa = ((Vec3*(__thiscall*)(void*))
                     (*(void***)pfVar7)[0x2c / 4])((void*)pfVar7);
        Vec3* pfb = ((Vec3*(__thiscall*)(void*))
                     (*(void***)pfVar11)[0x2c / 4])((void*)pfVar11);
        Vec3 d;
        d.x = pfb->x - pfa->x;
        d.y = pfb->y - pfa->y;
        d.z = pfb->z - pfa->z;
        Vec3 n;
        FUN_00449c20(&n, &d);
        Vec3 step;
        step.x = n.x * dist;
        step.y = n.y * dist;
        step.z = n.z * dist;
        Vec3* pfa2 = ((Vec3*(__thiscall*)(void*))
                      (*(void***)pfVar7)[0x2c / 4])((void*)pfVar7);
        Vec3 tgt;
        tgt.x = pfa2->x + step.x;
        tgt.y = pfa2->y + step.y;
        tgt.z = pfa2->z + step.z;

        float rr = FUN_00d99ac0((void*)pfVar11, (void*)pfVar7, 1);
        if (rr < 1.0f) {
            float d2 = dist + 1.0f;
            Vec3* fwd = ((Vec3*(__thiscall*)(void*, void*))
                         (*(void***)pfVar7)[0x5c / 4])((void*)pfVar7, (void*)0);
            Vec3 neg;
            neg.x = -fwd->x;
            neg.y = -fwd->y;
            neg.z = -fwd->z;
            ((void*(__thiscall*)(void*, void*))
             (*(void***)pfVar11)[0x2c / 4])((void*)pfVar11, &neg);
            float fa = ((float(__thiscall*)(void*))
                        (*(void***)pfVar7)[0x74 / 4])((void*)pfVar7);
            void* ub = ((void*(__thiscall*)(void*))
                        (*(void***)pfVar7)[0x2c / 4])((void*)pfVar7);
            void* sp = FUN_00699800(ub, (void*)(uint32_t)fa);
            Vec3 p2;
            p2.x = ((float*)sp)[0];
            p2.y = ((float*)sp)[1];
            p2.z = ((float*)sp)[2];
            Vec3* pa = ((Vec3*(__thiscall*)(void*))
                        (*(void***)pfVar7)[0x2c / 4])((void*)pfVar7);
            Vec3 dd;
            dd.x = p2.x - pa->x;
            dd.y = p2.y - pa->y;
            dd.z = p2.z - pa->z;
            Vec3 nn;
            FUN_00449c20(&nn, &dd);
            Vec3 stp;
            stp.x = nn.x * d2;
            stp.y = nn.y * d2;
            stp.z = nn.z * d2;
            Vec3* pa3 = ((Vec3*(__thiscall*)(void*))
                         (*(void***)pfVar7)[0x2c / 4])((void*)pfVar7);
            tgt.x = pa3->x + stp.x;
            tgt.y = pa3->y + stp.y;
            tgt.z = pa3->z + step.z;
        }

        Vec3* pp = ((Vec3*(__thiscall*)(void*))
                    (*(void***)pfVar11)[0x2c / 4])((void*)pfVar11);
        FUN_00d99e20(pp, &tgt);
        float dx = pp->x - tgt.x, dy = pp->y - tgt.y, dz = pp->z - tgt.z;
        if (dx * dx + dy * dy + dz * dz < g_147bc8c) {
            Vec3* pf2 = ((Vec3*(__thiscall*)(void*))
                         (*(void***)pfVar7)[0x2c / 4])((void*)pfVar7);
            Vec3 dd;
            dd.x = pf2->x - pp->x;
            dd.y = pf2->y - pp->y;
            dd.z = pf2->z - pp->z;
            Vec3 nn;
            FUN_00449c20(&nn, &dd);
            Vec3 stp;
            stp.x = nn.x * dist;
            stp.y = nn.y * dist;
            stp.z = nn.z * dist;
            Vec3* pf3 = ((Vec3*(__thiscall*)(void*))
                         (*(void***)pfVar7)[0x2c / 4])((void*)pfVar7);
            tgt.x = stp.x + pf3->x;
            tgt.y = stp.y + pf3->y;
            tgt.z = stp.z + pf3->z;
            FUN_00d99e20(pp, &tgt);
        }

        ((void*(__thiscall*)(void*, void*, int, int))
         (*(void***)pfVar11)[0x5c / 4])((void*)pfVar11, (void*)0, 1, 2);
        Vec3 outv;
        void* pm = FUN_00b3d350(&outv, &tgt);
        TC2(void, FUN_00b815a0)(pm, &outv, &tgt);
        TCS(void, (void*, int, void*, void*, int), FUN_00c1c5c0)((void*)self, 2, &tgt, &outv, 1);
        Creature* r = (Creature*)TC0(void*, FUN_00c41ec0)((void*)&self->mLoco);
        r->mLoco.mField5c = 4;
        other->mMode = 2;
        return 1;
    }

    if (st->mMode != 2)
        return 1;

    if (TC0(char, FUN_00c42e20)((void*)&self->mLoco))
        return 0;
    if (self->mByteB5C == 0 && (self->mFlagsB58 & 0x1000) == 0) {
        FUN_00c14750(0);
        return 1;
    }
    if (FUN_00c0e0c0(0x26f1f86))
        return 1;
    TCS(void, (void*, int, void*, int, int), FUN_00c14940)((void*)self, 0x26f1f86, (void*)&pcVar3->mLoco, -1, -1);
    return 1;
}

// ===========================================================================
// @ 0x00d6eeb0
// ===========================================================================
float __cdecl FUN_00d6eeb0(Creature* self)
{
    if (TC0(int, FUN_00c0f570)((void*)self) > 0)
        return 0.0f;

    NIter it;
    it.mpCur = self->mpBegin140c;
    it.mpEnd = self->mpEnd1410;
    if (it.mpCur == it.mpEnd)
        return 0.0f;

    if (!TC1(char, FUN_00c02600)(&it.mpFilt, *it.mpCur))
        TC0(void, FUN_00b3d850)(&it);

    while (it.mpCur != it.mpEnd) {
        void* e = *it.mpCur;
        if (FUN_00d6e1a0(e, (void*)self))
            return 1.0f;
        do {
            it.mpCur = it.mpCur + 1;
            if (it.mpCur == it.mpEnd)
                return 0.0f;
        } while (!TC1(char, FUN_00c02600)(&it.mpFilt, *it.mpCur));
    }
    return 0.0f;
}

// ===========================================================================
// @ 0x00d6ef50
// ===========================================================================
float __cdecl FUN_00d6ef50(Creature* self)
{
    if (TC0(int, FUN_00c0f570)((void*)self) > 0) {
        uint32_t idx = TC0(uint32_t, FUN_00c0f780)((void*)self);
        Creature* combatant = (Creature*)TCS(void*, (void*, uint32_t), FUN_00c0f8a0)((void*)self, idx);
        if (combatant == 0
            || (combatant = (Creature*)((void*(__thiscall*)(void*, int))
                    (*(void***)combatant)[0xb8 / 4])((void*)combatant, 0x398420d)) == 0
            || *(int*)((char*)combatant + 0x110) != 4)
        {
            NIter it;
            it.mpCur = self->mpBegin1124;
            it.mpEnd = self->mpEnd1128;
            if (it.mpCur == it.mpEnd)
                return 0.0f;

            if (!TC1(char, FUN_00c02600)(&it.mpFilt, *it.mpCur))
                TC0(void, FUN_00b3d850)(&it);

            while (it.mpCur != it.mpEnd) {
                int* e = (int*)*it.mpCur;
                Creature* owner = (Creature*)e[2];
                if (owner->mpB20 != self->mpB20
                    && TC1(char, FUN_00c0b860)((void*)self, (void*)owner)
                    && *(char*)((char*)e + 4) != 0
                    && (owner->mByteB5E == 0 || g_1582df6 != 0))
                {
                    void* r = TCS(void*, (void*, int, int, float, void*), FUN_00bc97f0)
                                  ((void*)((char*)self->mpB4C + 8), 0, 0x40000,
                                   g_1473c70, (void*)owner);
                    if (r != 0) {
                        *(int*)((char*)r + 0xc) = 3;
                        return 1.0f;
                    }
                }
                do {
                    it.mpCur = it.mpCur + 1;
                    if (it.mpCur == it.mpEnd)
                        return 0.0f;
                } while (!TC1(char, FUN_00c02600)(&it.mpFilt, *it.mpCur));
            }
        }
    }
    return 0.0f;
}

// ===========================================================================
// @ 0x00d6f090
// ===========================================================================
float __cdecl FUN_00d6f090(Creature* self)
{
    if (TC0(int, FUN_00c0f570)((void*)self) > 0) {
        NIter it;
        it.mpCur = self->mpBegin1124;
        it.mpEnd = self->mpEnd1128;
        if (it.mpCur == it.mpEnd)
            return 0.0f;

        if (!TC1(char, FUN_00c02600)(&it.mpFilt, *it.mpCur))
            TC0(void, FUN_00b3d850)(&it);

        while (it.mpCur != it.mpEnd) {
            int* e = (int*)*it.mpCur;
            Creature* owner = (Creature*)e[2];
            if (owner->mpB20 != self->mpB20
                && ((unsigned char)(self->mFlagsB58 >> 8) & 1) == 0
                && TCS(char, (void*, void*, int), FUN_00c0e8d0)((void*)self, (void*)owner, 4)
                && ((unsigned char)(owner->mFlagsB58 >> 9) & 1) != 0
                && *(char*)((char*)e + 4) != 0)
            {
                void* r = TCS(void*, (void*, int, int, float, void*), FUN_00bc97f0)
                              ((void*)((char*)self->mpB4C + 8), 0, 0x40000,
                               g_147bc98, (void*)owner);
                if (r != 0) {
                    *(int*)((char*)r + 0xc) = 6;
                    *(int*)((char*)r + 0x10) = TC0(uint32_t, FUN_00c0f780)((void*)self);
                    return 1.0f;
                }
            }
            do {
                it.mpCur = it.mpCur + 1;
                if (it.mpCur == it.mpEnd)
                    return 0.0f;
            } while (!TC1(char, FUN_00c02600)(&it.mpFilt, *it.mpCur));
        }
    }
    return 0.0f;
}