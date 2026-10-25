// src/game/SPGonzago/SPCreaturePersonality.cpp -- migrated from slice(s) s00d6f1c0, s00d6e3a0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCreaturePersonality.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "nSPBehaviorTree/behavior_stimuli.h"
#include "SP/cGameNounManager.h"
#pragma pack(push, 1)
#pragma pack(pop)

// ---- items of slice s00d6e3a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define TC0(ret, name) ((ret(__thiscall*)(void*)) name)
#define TC1(ret, name) ((ret(__thiscall*)(void*, void*)) name)
#define TC2(ret, name) ((ret(__thiscall*)(void*, void*, void*)) name)
#define TCS(ret, params, name) ((ret(__thiscall*)params) name)
void*  SP_NounManager();                              // 0x00b3d300 cdecl
void*  FUN_00b1fdb0(void*);                           // 0x00b1fdb0 thiscall (GetAvatar)
void*  FUN_00d99500(void*);                           // 0x00d99500 cdecl
float  FUN_00d99ac0(void*, void*, int);               // 0x00d99ac0 cdecl
void   FUN_00d997e0(void*);                           // 0x00d997e0 thiscall
void*  FUN_00d20610(void*);                           // 0x00d20610 thiscall (GetVelocity)
void*  FUN_00c0ee60(void*);                           // 0x00c0ee60 thiscall
void*  FUN_00c41ec0(void*);                           // 0x00c41ec0 thiscall
int    FUN_00c0f570(void*);                           // 0x00c0f570 thiscall (CountValid)
uint32_t FUN_00c0f780(void*);                         // 0x00c0f780 thiscall (FindFirstValid)
void*  FUN_00c0f8a0(void*, uint32_t);                 // 0x00c0f8a0 thiscall (GetAt)
char   FUN_00c0b860(void*, void*);                    // 0x00c0b860 thiscall
char   FUN_00c0e8d0(void*, void*, int);               // 0x00c0e8d0 thiscall
char   FUN_00c02600(void*, void*);                    // 0x00c02600 thiscall (IsValidNeighbourEntry)
void   FUN_00b3d850(void*);                           // 0x00b3d850 thiscall
void*  FUN_00bc97f0(void*, int, int, float, void*);   // 0x00bc97f0 thiscall
char   FUN_00d6e1a0(void*, void*);                    // 0x00d6e1a0 cdecl
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
float            g_1471064;    // 0x01471064
float            g_147bc9c;    // 0x0147bc9c
float            g_1473c70;    // 0x01473c70
float            g_147bc98;    // 0x0147bc98
unsigned char    g_1582df6;    // 0x01582df6
struct Vec3 { float x, y, z; };
struct Spatial {
    void* vptr;              // +0x00
    char  _p004[0x14 - 0x04];
    Vec3  mPos;              // +0x14
    char  _p020[0x5c - 0x20];
    int   mField5c;          // +0x5c
};
struct Stimuli {
    char  _p00[4];
    void* mpAny;             // +0x04  (object reached through a vtable)
};
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
struct Holder {
    char   _p000[0x600];
    State* mpState;          // +0x600
};
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
// ---- items of slice s00d6e3a0 end

// ---- items of slice s00d6f1c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma warning(disable : 4100)
namespace SP {
struct cBehaviorStimuli {
    uint8_t pad000[8];                                  // +0x00 .. +0x07

    void ClearAll(uint32_t mask, uint32_t flags);        // 0x00bc98f0
};
}
namespace SP {
struct cBehaviorTree {
    uint8_t        pad000[8];                           // +0x00 .. +0x07
    cBehaviorStimuli mStimuli;                          // +0x08
};
}
namespace SP {
class cBehaviorActor {
public:
virtual void v000();
virtual void v004();
virtual void v008();
virtual void v00c();
virtual void v010();
virtual void v014();
virtual void v018();
virtual void v01c();
virtual void v020();
virtual void v024();
virtual void v028();
virtual void v02c();
virtual void v030();
virtual void v034();
virtual void v038();
virtual void v03c();
virtual void v040();
virtual void v044();
virtual void v048();
virtual void v04c();
virtual void v050();
virtual void v054();
virtual void v058();
virtual void v05c();
virtual void v060();
virtual void v064();
virtual void v068();
virtual void v06c();
virtual void v070();
virtual void v074();
virtual void v078();
virtual void v07c();
    virtual void v080();
    virtual void PushTargetAction(void* pTarget, int mode, int flags); // +0x84

    uint8_t        pad004[0xb48];                       // +0x004 .. +0xb4b
    cBehaviorTree* mpBehavior;                          // +0xb4c
};
}
namespace SP {
bool __cdecl PATROL_TOOFAR_Decide(cBehaviorActor* pActor, int param, int32_t* pResult); // 0x00d6f430
}
// ---- items of slice s00d6f1c0 end

// @ 0x00d6e3a0
uint8_t __cdecl PLAY_FIGHT_Tick(Creature* self, int a1, int a2, int a3, int a4, int a5, int a6, float dt)
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

// @ 0x00d6e680
float __cdecl FUN_00d6e680(Creature* self, int a1, int a2, int a3, Stimuli* stimuli, char* out)
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

// @ 0x00d6eeb0
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

// @ 0x00d6ef50
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

// @ 0x00d6f090
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

// @ 0x00d6f1c0
namespace SP {
void __fastcall FUN_00d6f1c0(cBehaviorActor* this_, int unused)
{
    (void)this_;
}
}  // namespace SP

// @ 0x00d6f430
namespace SP {
bool __cdecl PATROL_TOOFAR_Decide(cBehaviorActor* pActor, int param, int32_t* pResult)
{
    (void)pActor;
    (void)param;
    if (pResult)
        *pResult = 0;
    return true;
}
}  // namespace SP
