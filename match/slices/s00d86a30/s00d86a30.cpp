#include <stddef.h>

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef unsigned long long u64;
typedef float f32;
typedef double f64;

#define VT(p) (*(void***)(p))
#define MOPS(p) ((COps*)(p))

struct COps;

struct cSub34 { void* mVtbl; };

struct cNodeState {
    u32 m0;                         // +0x00
    union U4 { void* p; u32 u; u8 b; } m4;       // +0x04
    union U8 { void* p; u32 u; } m8;             // +0x08
    union UC { void* p; u32 u; u8 b; } mC;       // +0x0c
    union U10 { u32 u; f32 f; u8 b; u8 pad[3]; } m10; // +0x10
    union U14 { u32 u; f32 f; } m14;             // +0x14
    union U18 {
        u32 u;
        f32 f;
        struct { u8 b18; u8 b19; u8 pad[2]; } bytes;
    } m18;                           // +0x18
    union U1C { void* p; u8 b; } m1C; // +0x1c
    u32 m20;                         // +0x20
    u8 m24;                          // +0x24
    u8 pad25[3];
    union U28 { void* p; u32 u; } m28; // +0x28
    u8 m2C;                          // +0x2c
    u8 pad2D[3];
    u32 m30;                         // +0x30
};

struct cCreatureEntry {
    u32 mId;                         // +0x00
    u32 pad04[7];                    // +0x04
    void* mObj20;                    // +0x20
};

struct cB20 {
    u8 pad0[0x590];
    f32 m590;                        // +0x590
};

struct cStimuli { u8 pad0[8]; };
struct cBehaviorTree {
    u32 pad0[2];
    cStimuli mStimuli;               // +0x08
};

struct cCreatureSub { void* mVtbl; };

struct cCreature {
    u8 pad000[0xC0];
    cCreatureSub mC0;                // +0xc0
    u8 padC4[0x108 - 0xC4];
    void* m108;                      // +0x108
    u8 pad10C[0xB20 - 0x10C];
    cB20* mB20;                      // +0xb20
    u8 padB24[0xB4C - 0xB24];
    cBehaviorTree* mB4C;             // +0xb4c
    u8 padB50[0xB58 - 0xB50];
    u32 mB58;                        // +0xb58
    u8 mB5C;                         // +0xb5c
    u8 padB5D[0xE40 - 0xB5D];
    cCreatureEntry* mE40;            // +0xe40
};

struct cAnimObj {
    void* mVtbl;                     // +0x00
    u32 pad04[2];
    u32 m0C;                         // +0x0c
    u32 m10;                         // +0x10
    u32 pad14[6];
    void* m2C;                       // +0x2c
    u32 pad30;
    cSub34 m34;                      // +0x34
    u8 pad38[0x68 - 0x38];
    void* m68;                       // +0x68
    u8 pad6C[0xA3 - 0x6C];
    u8 mA3;                          // +0xa3
    u8 padA4[0xA9 - 0xA4];
    u8 mA9;                          // +0xa9
    u8 padAA[0x108 - 0xAA];
    void* m108;                      // +0x108
    u8 pad10C[0x148 - 0x10C];
    u8 m148;                         // +0x148
    u8 pad149[0x16C - 0x149];
    u32 m16C;                        // +0x16c
};

struct cHolder {
    u8 pad0[0x160];
    cAnimObj* m160;                  // +0x160
};

struct COps {
    u32 FUN_00c0f780();
    void FUN_00bc98f0(u32 a, u32 b);
    void* FUN_00bc96a0(u32 a, u32 b);
    void FUN_00c14750(u32 a);
    u8 FUN_00c14ef0(u32 a, void* b, u32 c, u32 d, u32 e);
    u8 FUN_00c12400(u32 a);
    s32 FUN_00c40200();
    void* FUN_00b5f950(void* obj);
    u32 FUN_00c0ee60(u32 a, u32 b);
    void* FUN_00c04590();
    void FUN_00c15d50(void* a, u32 b, u32 c);
    void FUN_00b225d0(void* noun);
    s32 FUN_00c0f4f0();
    u8 FUN_00c0f5f0();
    void FUN_00c15bd0(u32 a, u32 b, u32 c);
    void FUN_00c1c5c0(u32 a, void* b, u32 c);
    u8 FUN_00c42e20();
    u32 FUN_00c14990(u32 a, void* b, s32 c);
    void FUN_00d39360(u32 a, void* b);
};

void* __cdecl FUN_00ad2670(void* arg);
void* __cdecl FUN_00d38840();
void* __cdecl FUN_00d998d0(void* anim, u32 key);
void* __cdecl FUN_0067dcc0();
f32 __cdecl FUN_00572a10(f32 a, f32 b);
void __cdecl FUN_00f47380(void* p);
void* __stdcall FUN_00b3d300(void* noun);
void __cdecl FUN_00d7d2c0(void* a, void* b);
void __cdecl FUN_00d85540(void* a);
u32 __cdecl FUN_00436ce0(void* out, void* in, f32 a, f32 b);

extern f32 g169f03c;
extern f32 g169f040;
extern f32 g169f044;
extern f32 g13ec4b4;
extern f32 g147c030;
extern void* g1590c40;

static const f32 kZero = 0.0f;
static const f32 kHalf = 0.5f;
static const f32 kOne = 1.0f;
static const f32 kTwo = 2.0f;
static const f32 kFour = 4.0f;
static const f32 kTenth = 0.1f;

// @ 0x00d86a30
u8 FUN_00d86a30(cCreature* creature, u32 a2, u32 a3, void** a4, void** a5, cNodeState* state)
{
    if (state->m8.p == 0)
        return 0;

    cAnimObj* ornament = (cAnimObj*)((void* (__thiscall*)(void*, u32))VT(state->m8.p)[0xb8 / 4])(state->m8.p, 0x3a25119);
    if (ornament == 0)
        return 0;

    cCreature* old = (cCreature*)ornament->m108;
    if (old != 0 && old != creature && ((creature->mB58 >> 9) & 1) == 0)
        return 0;

    if (creature != old) {
        if (creature)
            ((void (__thiscall*)(void*))VT(creature)[0 / 4])(creature);
        ornament->m108 = creature;
        if (old)
            ((void (__thiscall*)(void*))VT(old)[4 / 4])(old);
    }

    void* obj = *a5;
    f32 f44 = g169f044;
    f32 f40 = g169f03c;
    f32 f3c = g169f040;
    f32 f38 = g169f044;
    if (obj == 0)
        return 0;

    f32 f4 = ((f32 (__thiscall*)(void*))VT(obj)[0x74 / 4])(obj);
    f32* pf = (f32*)((void* (__thiscall*)(void*, void*))VT(obj)[0x6c / 4])(obj, &f4);
    f44 = (pf[0] + pf[3]) * kHalf;
    f40 = (pf[4] + pf[1]) * kHalf;
    f3c = (pf[5] + pf[2]) * kHalf;
    f38 = f44;
    f32 f34 = f40;
    f32 f30 = f3c;

    f32* pf2 = (f32*)((void* (__thiscall*)(void*))VT(obj)[0x2c / 4])(obj);
    f32 f11 = pf2[0];
    f32 f2 = pf2[1];
    f32 f3 = pf2[2];

    u32 st = state->m0;
    if (st == 0) {
        cCreatureSub* cs = &creature->mC0;
        f32 f9 = ((f32 (__thiscall*)(void*))VT(cs)[0x74 / 4])(cs);
        f4 = f9 + f4 + kTenth;
        f32* pf3 = (f32*)((void* (__thiscall*)(void*))VT(cs)[0x2c / 4])(cs);
        f32 f13 = f4 + kOne;
        f38 = f11 - pf3[0];
        f34 = f2 - pf3[1];
        f30 = f3 - pf3[2];
        u32 n = FUN_00436ce0(&f44, &f38, f4, f13);
        MOPS(creature)->FUN_00c1c5c0(2, &f44, n);
        if (MOPS(cs)->FUN_00c42e20()) {
            if (*a4)
                *(u8*)((u8*)*a4 + 0x71) = 1;
            state->m4.u = 0x3df6dff;
            state->mC.u = MOPS(creature)->FUN_00c14990(0x3df6dff, &f44, -1);
            FUN_00d85540(creature);
            state->m0 = 1;
        }
    }
    else if (st == 1) {
        if (!MOPS(creature)->FUN_00c14ef0((u32)(size_t)g1590c40, &f4, state->m4.u, 0, 1) &&
            !MOPS(creature)->FUN_00c12400(state->mC.u))
            return 1;
        MOPS(ornament)->FUN_00c40200();
        ornament->mA3 = 0;
        state->m0 = 2;
        u32 u = (u32)(size_t)FUN_00ad2670(a4);
        (void)u;
        void* inst = FUN_00d38840();
        MOPS(inst)->FUN_00d39360(0xd3353638, &f44);
    }
    else if (st == 2) {
        return 0;
    }
    return 1;
}

// @ 0x00d86d30
u8 FUN_00d86d30(cCreature* creature, u32 a2, u32 a3, u32 a4, u32 a5, cNodeState* state)
{
    if (state)
        state->m8.p = 0;
    state->m0 = 0;
    void* p = state->m8.p;
    if (p) {
        state->m8.p = 0;
        ((void (__thiscall*)(void*))VT(p)[0xc0 / 4])(p);
    }
    state->m4.b = 0;
    state->mC.b = 0;
    state->m10.u = 0xffffffff;
    u32 idx = MOPS(creature)->FUN_00c0f780();
    if (idx == 0xffffffff)
        return 0;
    cCreatureEntry* e = &creature->mE40[idx];
    state->m10.u = e->mId;
    void* obj = e->mObj20;
    if (obj == 0)
        return 0;
    void* prev = state->m8.p;
    if (obj != prev) {
        ((void (__thiscall*)(void*))VT(obj)[0xbc / 4])(obj);
        state->m8.p = obj;
        if (prev)
            ((void (__thiscall*)(void*))VT(prev)[0xc0 / 4])(prev);
    }
    f32 f = creature->mB20->m590;
    if (f == kZero)
        state->mC.b = 1;
    return 1;
}

// @ 0x00d86df0
void FUN_00d86df0(cCreature* creature, u32 a2, u32 a3, u32 a4, u32 a5, cNodeState* state)
{
    void* p = state->m8.p;
    if (p) {
        state->m8.p = 0;
        ((void (__thiscall*)(void*))VT(p)[0xc0 / 4])(p);
    }
    MOPS(&creature->mB4C->mStimuli)->FUN_00bc98f0(0, 0x40000);
    MOPS(creature)->FUN_00c14750(0);
    if (state && state->m8.p) {
        void* q = state->m8.p;
        return ((void (__thiscall*)(void*))VT(q)[0xc0 / 4])(q);
    }
}

// @ 0x00d86e50
u8 FUN_00d86e50(cCreature* creature, u32 a2, u32 a3, u32 a4, u32 a5, cNodeState* state)
{
    if (state) {
        state->m4.u = 0;
        state->mC.u = 0;
    }
    cAnimObj* anim = (cAnimObj*)MOPS(&creature->mB4C->mStimuli)->FUN_00bc96a0(0x20, 0);
    if (anim == 0)
        return 0;
    state->m10.b = 0;
    state->m0 = anim->m0C;
    if (anim->m2C) {
        void* obj = ((void* (__thiscall*)(void*, u32))VT(anim->m2C)[0xc / 4])(anim->m2C, 0x2c9cc8e);
        if (obj) {
            void* prev = state->mC.p;
            if (obj != prev) {
                ((void (__thiscall*)(void*))VT(obj)[0 / 4])(obj);
                state->mC.p = obj;
                if (prev)
                    ((void (__thiscall*)(void*))VT(prev)[4 / 4])(prev);
            }
            ((void (__thiscall*)(void*, u32, u32, u32))VT(creature)[0x84 / 4])(creature, 0, 0, 0);
            return 1;
        }
    }
    if (anim->m2C) {
        void* obj = ((void* (__thiscall*)(void*, u32))VT(anim->m2C)[0xc / 4])(anim->m2C, 0x581147f);
        if (obj) {
            MOPS(&state->m4.p)->FUN_00b5f950(obj);
            state->m8.u = anim->m10;
            ((void (__thiscall*)(void*, u32, u32, u32))VT(creature)[0x84 / 4])(creature, 0, 0, 0);
            return 1;
        }
    }
    if ((creature->mB58 >> 9) & 1) {
        cAnimObj* v = (cAnimObj*)((void* (__thiscall*)(void*, u32))VT(creature)[0xb4 / 4])(creature, state->m0);
        if (v) {
            u32 r = 0;
            if (v->m0C == 1)
                r = 1;
            else if (v->m0C == 0)
                r = 2;
            u32 arg = MOPS(creature)->FUN_00c0ee60(1, r);
            ((void (__thiscall*)(void*, u32))VT(creature)[0x84 / 4])(creature, arg);
        }
    }
    return 1;
}

// @ 0x00d86f90
void FUN_00d86f90(cCreature* creature, u32 a2, u32 a3, u32 a4, u32 a5, cNodeState* state)
{
    struct Local {
        u32 m0;
        u32 m4;
        u32 m8;
        f32 mC;
        f32 m10;
        f32 m14;
        f32 m18;
        f32 m1C;
        f32 m20;
        u32 m24;
        u32 m28;
        u8 pad2C[0x20];
        u8 m4C;
        u8 pad4D[3];
        f32 m50;
        f32 m54;
        f32 m58;
        u32 m5C;
        f32 m60;
        f32 m64;
        f32 m68;
        f32 m6C;
        u32 m70;
    } local;
    local.m0 = 0;
    local.m4 = 0;
    local.m8 = 0;
    local.m10 = g169f03c;
    local.m18 = g169f040;
    local.m1C = g169f044;
    local.m20 = kOne;
    local.m24 = 0;
    local.m4C = 0;
    local.m50 = 0.0f;
    local.m54 = 0.0f;
    local.m58 = 0.0f;
    local.m5C = 0;
    local.m60 = kTwo;
    local.m64 = g13ec4b4;
    local.m68 = g147c030;
    local.m6C = 0.0f;
    local.m70 = 0;
    ((void (__thiscall*)(void*, void*))VT(&creature->mC0)[0xdc / 4])(&creature->mC0, &local);
    void* p = *(void**)((u8*)&local + 0);
    if (p) {
        if (((u32*)p)[-1] != 0)
            FUN_00f47380(p);
    }
    MOPS(&creature->mB4C->mStimuli)->FUN_00bc98f0(0x20, 0);
    if (state) {
        if (state->mC.p)
            ((void (__thiscall*)(void*))VT(state->mC.p)[4 / 4])(state->mC.p);
        if (state->m4.p) {
            void* q = state->m4.p;
            return ((void (__thiscall*)(void*))VT(q)[4 / 4])(q);
        }
    }
}

// @ 0x00d870b0
u8 FUN_00d870b0(cCreature* creature, u32 a2, u32 a3, u32 a4, u32 a5, cNodeState* state)
{
    if (state) {
        state->m4.u = 0;
        state->m10.u = 0;
        state->m14.u = 0;
        state->m18.u = 0;
    }
    state->m0 = 0;
    void* p = state->m4.p;
    if (p) {
        state->m4.p = 0;
        ((void (__thiscall*)(void*))VT(p)[4 / 4])(p);
    }
    state->m8.u = 0;
    state->mC.u = 0x53ecd29;
    state->m1C.b = 0;
    cAnimObj* anim = (cAnimObj*)MOPS(&creature->mB4C->mStimuli)->FUN_00bc96a0(0x200000, 0);
    if (anim == 0)
        return 0;
    cAnimObj* obj = (cAnimObj*)FUN_00d998d0(anim, 0x1b92b27);
    if (obj == 0)
        return 0;
    if (obj->mA9 == 0)
        return 0;
    if (((u8 (__thiscall*)(void*))VT(obj)[0x2c / 4])(obj))
        return 0;
    if (MOPS(creature)->FUN_00c04590() == 0)
        return 0;
    cHolder* h = (cHolder*)MOPS(creature)->FUN_00c04590();
    if (h->m160 == 0)
        return 0;
    MOPS(&state->m4.p)->FUN_00b5f950(obj);
    cHolder* h2 = (cHolder*)MOPS(creature)->FUN_00c04590();
    cAnimObj* o = h2->m160;
    f32* pos = (f32*)((void* (__thiscall*)(void*))VT(&o->m34)[0x98 / 4])(&o->m34);
    state->m10.f = pos[0];
    state->m14.f = pos[1];
    state->m18.f = pos[2];
    return 1;
}

// @ 0x00d871a0
void FUN_00d871a0(cCreature* creature, u32 a2, u32 a3, u32 a4, u32 a5, cNodeState* state)
{
    void* p = state->m4.p;
    if (p) {
        state->m4.p = 0;
        ((void (__thiscall*)(void*))VT(p)[4 / 4])(p);
    }
    MOPS(&creature->mB4C->mStimuli)->FUN_00bc98f0(0x200000, 0);
    void* ms = FUN_0067dcc0();
    ((void (__thiscall*)(void*, u32, u32, u32))VT(ms)[0x14 / 4])(ms, 0x445f729, 0, 0);
    if (state && state->m4.p) {
        void* q = state->m4.p;
        return ((void (__thiscall*)(void*))VT(q)[4 / 4])(q);
    }
}

// @ 0x00d87200
u8 FUN_00d87200(cCreature* creature, u32 a2, u32 a3, u32 a4, u32 a5, cNodeState* state)
{
    if (state)
        state->m4.u = 0;
    state->m0 = 0;
    void* p = state->m4.p;
    if (p) {
        state->m4.p = 0;
        ((void (__thiscall*)(void*))VT(p)[4 / 4])(p);
    }
    state->m8.u = 0;
    state->mC.u = 0x53ecd2a;
    cAnimObj* anim = (cAnimObj*)MOPS(&creature->mB4C->mStimuli)->FUN_00bc96a0(0x200000, 0);
    if (anim == 0)
        return 0;
    cAnimObj* obj = (cAnimObj*)FUN_00d998d0(anim, 0x1b92b27);
    if (obj == 0)
        return 0;
    if (obj->mA9 == 0)
        return 0;
    if (((u8 (__thiscall*)(void*))VT(obj)[0x2c / 4])(obj))
        return 0;
    MOPS(&state->m4.p)->FUN_00b5f950(obj);
    cAnimObj* o = (cAnimObj*)state->m4.p;
    f32 f = ((f32 (__thiscall*)(void*))VT(&o->m34)[0x74 / 4])(&o->m34);
    state->m10.f = FUN_00572a10(f + f, kFour * f);
    return 1;
}

// @ 0x00d872d0
void FUN_00d872d0(cCreature* creature, u32 a2, u32 a3, u32 a4, u32 a5, cNodeState* state)
{
    void* p = state->m4.p;
    if (p) {
        state->m4.p = 0;
        ((void (__thiscall*)(void*))VT(p)[4 / 4])(p);
    }
    MOPS(&creature->mB4C->mStimuli)->FUN_00bc98f0(0x200000, 0);
    if (state && state->m4.p) {
        void* q = state->m4.p;
        return ((void (__thiscall*)(void*))VT(q)[4 / 4])(q);
    }
}

// @ 0x00d87320
u8 FUN_00d87320(cCreature* creature, u32 a2, u32 a3, u32 a4, u32 a5, cNodeState* state)
{
    if (state) {
        state->m8.p = 0;
        state->m1C.p = 0;
        state->m28.p = 0;
    }
    state->m4.u = 0x10;
    void* p = state->m8.p;
    if (p) {
        state->m8.p = 0;
        ((void (__thiscall*)(void*))VT(p)[4 / 4])(p);
    }
    state->m10.u = 0xffffffff;
    state->m18.bytes.b18 = 0;
    state->m18.bytes.b19 = 0;
    state->m14.u = 0;
    state->m20 = 0xffffffff;
    state->m2C = 0;
    state->m30 = 0xffffffff;
    cAnimObj* anim = (cAnimObj*)MOPS(&creature->mB4C->mStimuli)->FUN_00bc96a0(1, 0);
    if (anim) {
        cAnimObj* o1 = (cAnimObj*)FUN_00d998d0(anim, 0x2c9cc8e);
        void* prev = state->m8.p;
        if (o1 != prev) {
            if (o1)
                ((void (__thiscall*)(void*))VT(o1)[0 / 4])(o1);
            state->m8.p = o1;
            if (prev)
                ((void (__thiscall*)(void*))VT(prev)[4 / 4])(prev);
        }
        if (state->m8.p == 0) {
            cAnimObj* o2 = (cAnimObj*)FUN_00d998d0(anim, 0x581147f);
            void* prev2 = state->m1C.p;
            if (o2 != prev2) {
                if (o2)
                    ((void (__thiscall*)(void*))VT(o2)[0 / 4])(o2);
                state->m1C.p = o2;
                if (prev2)
                    ((void (__thiscall*)(void*))VT(prev2)[4 / 4])(prev2);
            }
            state->m20 = anim->m0C;
        }
    }
    void** slot;
    if (state->m8.p)
        slot = (void**)((u8*)state->m8.p + 0x108);
    else if (state->m1C.p)
        slot = (void**)((u8*)state->m1C.p + 0x68);
    else
        return 0;
    if (!(((creature->mB58 >> 9) & 1) || *slot == 0 || *slot == creature))
        return 0;
    void* old = *slot;
    if (creature != old) {
        ((void (__thiscall*)(void*))VT(creature)[0 / 4])(creature);
        *slot = creature;
        if (old)
            ((void (__thiscall*)(void*))VT(old)[4 / 4])(old);
    }
    state->m0 = 0;
    creature->mB5C = 0;
    if (MOPS(creature)->FUN_00c0f4f0() == 0)
        return 0;
    if (MOPS(creature)->FUN_00c0f4f0() > 0) {
        if (MOPS(creature)->FUN_00c0f5f0()) {
            MOPS(creature)->FUN_00c15bd0(0, 0, 0);
            if (MOPS(creature)->FUN_00c0f5f0())
                return 0;
        }
    }
    if (state->m8.p && ((creature->mB58 >> 9) & 1)) {
        state->m24 = 0;
        return 1;
    }
    state->m24 = 1;
    return 1;
}

// @ 0x00d874e0
void FUN_00d874e0(cCreature* creature, u32 a2, u32 a3, u32 a4, u32 a5, cNodeState* state)
{
    cAnimObj* anim = (cAnimObj*)MOPS(&creature->mB4C->mStimuli)->FUN_00bc96a0(1, 0);
    cAnimObj* obj = anim ? (cAnimObj*)FUN_00d998d0(anim, 0x2c9cc8e) : 0;
    if (state->m1C.p != 0 || obj == 0 || obj == (cAnimObj*)state->m8.p)
        MOPS(&creature->mB4C->mStimuli)->FUN_00bc98f0(1, 0);

    if (state->m18.bytes.b18) {
        if (state->m8.p) {
            cAnimObj* o = (cAnimObj*)state->m8.p;
            MOPS(creature)->FUN_00c15d50(&o->m34, 0, 0);
            if (o->m148 & 1) {
                void* nm = FUN_00b3d300(o);
                MOPS(nm)->FUN_00b225d0(o);
            }
        }
        state->m18.bytes.b18 = 0;
    }

    void** slot;
    if (state->m8.p)
        slot = (void**)((u8*)state->m8.p + 0x108);
    else if (state->m1C.p)
        slot = (void**)((u8*)state->m1C.p + 0x68);
    else
        goto after_slot;
    if (*slot == creature && *slot != 0) {
        void* old = *slot;
        *slot = 0;
        ((void (__thiscall*)(void*))VT(old)[4 / 4])(old);
    }

after_slot:
    if (state->m0 != 5 && state->m8.p && ((cAnimObj*)state->m8.p)->m16C == 3)
        FUN_00d7d2c0(&((cAnimObj*)state->m8.p)->m34, creature);

    void* p = state->m8.p;
    if (p) {
        state->m8.p = 0;
        ((void (__thiscall*)(void*))VT(p)[4 / 4])(p);
    }
    void* q = state->m28.p;
    if (q) {
        state->m28.p = 0;
        ((void (__thiscall*)(void*))VT(q)[4 / 4])(q);
    }
    if (state->m28.p)
        ((void (__thiscall*)(void*))VT(state->m28.p)[4 / 4])(state->m28.p);
    if (state->m1C.p)
        ((void (__thiscall*)(void*))VT(state->m1C.p)[4 / 4])(state->m1C.p);
    if (state->m8.p) {
        void* r = state->m8.p;
        return ((void (__thiscall*)(void*))VT(r)[4 / 4])(r);
    }
}
