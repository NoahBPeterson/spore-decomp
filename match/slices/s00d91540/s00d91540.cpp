// Decompiled from SporeApp.exe (gold6 batch, worker 33).
// Slice s00d91540: citizen-tree animation/state helpers, lane-node search, and
// UFO fear/open-clump activations.

typedef unsigned int   u32;
typedef int            s32;
typedef unsigned char  u8;
typedef float          f32;

// ---------------------------------------------------------------------------
// vtable call shapes
// ---------------------------------------------------------------------------
typedef void  (__thiscall* FnV)(void*);
typedef void  (__thiscall* Fn1)(void*, u32);
typedef void  (__thiscall* Fn2)(void*, u32, u32);
typedef void  (__thiscall* Fn3)(void*, u32, u32, u32);
typedef void  (__thiscall* Fn4)(void*, u32, u32, u32, u32);
typedef void* (__thiscall* FnP)(void*);
typedef u32   (__thiscall* FnU1P)(void*, void*);

// ---------------------------------------------------------------------------
// free functions / runtime helpers
// ---------------------------------------------------------------------------
void* FUN_00b3d4e0();                                        // 0x00b3d4e0
extern "C" void* __cdecl SP_PlanetModel();                 // 0x00b3d350
extern "C" void  __cdecl FUN_00d90ac0(void*, void*);       // 0x00d90ac0
extern "C" double __cdecl pow(double, double);

// ---------------------------------------------------------------------------
// small objects defined in other translation units
// ---------------------------------------------------------------------------
struct Vec3f;
struct C14750 { void Do(u32); };                           // 0x00c14750
struct BC3DF0 { u8   Do(u32); };                           // 0x00bc3df0
struct BC52A0 { void Do(u32, u32); };                      // 0x00bc52a0
struct BC5040 { void Do(u32); };                           // 0x00bc5040
struct BC64A0 { u32  Do(u32, u32, u32, u32); };            // 0x00bc64a0
struct BC4900 { void Do(u32, u32, u32); };                  // 0x00bc4900
struct C0E370 { s32  Do(); };                              // 0x00c0e370
struct C0E0C0 { u8   Do(u32); };                           // 0x00c0e0c0
struct NearGoal { u8  Do(); };                             // 0x00c42e20
struct PlayAnim { u32  Do(u32, u32, u32); };               // 0x00c12190
struct PlayAnim2 { u32 Do(u32, u32, u32); };               // 0x00c12190
struct Interrupt { void Do(u32, u32, u32); };              // 0x00c12310
struct MoveTo { void Do(u32, void*, f32, f32); };          // 0x00c1c1d0
struct GetCity { void* Do(); };                            // 0x00c23e40
struct GetLane { void** Do(); };                           // 0x0095fa00
struct RandDbl { float Do(); };                            // 0x009360d0
struct RandU32 { u32  Do(u32); };                          // 0x00a68fb0
struct Sub5A8 { u8 mPad[0x38]; void Set(f32); };           // 0x00f924e0
struct PlanetModel {
    Vec3f* MakeRandomWorldPosition(void*, void*, f32, f32); // 0x00b81780
};

// ---------------------------------------------------------------------------
// data layouts
// ---------------------------------------------------------------------------
struct Vec3f { f32 x, y, z; };

struct C0Sub { void* mpVtbl; };                            // +0x00

struct LaneNode { Vec3f v; u8 mPad0C[0x14]; };
struct LaneInfo { LaneNode* mpBegin; LaneNode* mpEnd; };

struct FB8Obj {
    u8      mPad000[0x144];                                // +0x000
    Vec3f*  mpBegin;                                       // +0x144
    Vec3f*  mpEnd;                                         // +0x148
};

struct B54Obj { u8 mPad00[0x80]; f32 mf80; };

struct Creature {
    void*   mpVtbl;                                        // +0x000
    u8      mPad004[0x0c0 - 0x004];
    C0Sub   mC0;                                           // +0x0c0
    u8      mPad0C4[0x110 - 0x0c4];
    u32     mn110;                                         // +0x110
    u8      mPad114[0x2b0 - 0x114];
    u32     mn2B0;                                         // +0x2b0
    u8      mPad2B4[0x5a8 - 0x2b4];
    Sub5A8  mSub5A8;                                       // +0x5a8
    f32     mf5E0;                                         // +0x5e0
    u8      mPad5E4[0xb54 - 0x5e4];
    void*   mpB54;                                         // +0xb54
    u8      mPadB58[0xb5e - 0xb58];
    u8      mbB5E;                                         // +0xb5e
    u8      mPadB5F[0xb62 - 0xb5f];
    u8      mbB62;                                         // +0xb62
    u8      mPadB63[0xfb8 - 0xb63];
    void*   mpFB8;                                         // +0xfb8
};

struct AnimState {
    u8  mPad00[0x0c];                                      // +0x00
    u8  mb0C;                                              // +0x0c
    u8  mPad0D[3];
    u32 mn10;                                              // +0x10
    u32 mn14;                                              // +0x14
};

struct DeadState {
    u32 mn00;                                              // +0x00
    f32 mf04;                                              // +0x04
    u32 mn08;                                              // +0x08
    f32 mf0C;                                              // +0x0c
    union { u32 mn10; u8 mb10; };                          // +0x10
    union { f32 mf14; u32 mn14; };                         // +0x14
    u8  mb18;                                              // +0x18
    u8  mPad19[3];
};

struct UfoState { u8 mb00; u8 mPad01[3]; f32 mf04; };

// ---------------------------------------------------------------------------

// @ 0x00d91540
bool FUN_00d91540(void* self)
{
    Creature* c = (Creature*)self;
    C0Sub* s = &c->mC0;
    ((FnV)((void**)s->mpVtbl)[0xec / 4])(s);
    ((C14750*)c)->Do(0);
    return true;
}

// @ 0x00d91570
bool FUN_00d91570(void* self, u32 a1, u32 a2, u32 a3, u32 a4, u32* out)
{
    Creature* c = (Creature*)self;
    C0Sub* s = &c->mC0;
    Vec3f local;
    ((FnV)((void**)s->mpVtbl)[0xec / 4])(s);
    ((C14750*)c)->Do(0);
    u32 id = ((BC64A0*)FUN_00b3d4e0())
                 ->Do(0x499c0285, 0xa080e6cd,
                      (u32)((FnP)((void**)s->mpVtbl)[0x2c / 4])(s),
                      ((FnU1P)((void**)s->mpVtbl)[0x5c / 4])(s, &local));
    *out = id;
    if (id != 0xffffffff) {
        ((BC4900*)FUN_00b3d4e0())->Do(id, (u32)c, 0);
        return true;
    }
    return false;
}

// @ 0x00d91600
bool FUN_00d91600(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32* p)
{
    u8 r = ((BC3DF0*)FUN_00b3d4e0())->Do(*p);
    return r == 0;
}

// @ 0x00d91620
void FUN_00d91620(u32 p1, u32 a1, u32 a2, u32 a3, u32 a4, u32* p)
{
    ((BC52A0*)FUN_00b3d4e0())->Do(*p, p1);
    ((BC5040*)FUN_00b3d4e0())->Do(*p);
}

// @ 0x00d91650
bool FUN_00d91650(void* p0, u32 a1, u32 a2, u32 a3, u32 a4, AnimState* st)
{
    Creature* c = (Creature*)p0;
    if (st->mb0C != 0) {
        if (((NearGoal*)&c->mC0)->Do()) {
            st->mb0C = 0;
            st->mn14 = ((PlayAnim*)c)->Do(((u32*)0x147c0fc)[st->mn10], 1, 0xffffffff);
        }
        return true;
    }
    return ((C0E370*)c)->Do() < 1;
}

// @ 0x00d916b0
bool FUN_00d916b0(void* p0, u32 a1, u32 a2, u32 flags, u32 a4, u8* flag)
{
    Creature* c = (Creature*)p0;
    if ((flags & 0x6000000) == 0)
        return false;
    if (((NearGoal*)&c->mC0)->Do() && *flag == 0) {
        *flag = 1;
        double r = ((RandDbl*)0x1601760)->Do();
        if ((flags | 0x2000000) != 0) {
            (r < *(f32*)0x1471064)
                ? ((PlayAnim*)c)->Do(0x62d64e3, 1, 0xffffffff)
                : ((PlayAnim2*)c)->Do(0x62d64e4, 1, 0xffffffff);
            return true;
        }
        u32 anim = (r < *(f32*)0x1471064) ? 0x2481dcb : 0x2481dcc;
        ((PlayAnim*)c)->Do(anim, 1, 0xffffffff);
    }
    return true;
}

// @ 0x00d91750
f32 FUN_00d91750(void* p0)
{
    Creature* c = (Creature*)p0;
    if (c->mbB62)
        return 1.0f;
    return 0.0f;
}

// @ 0x00d91770
bool FUN_00d91770(void* p0, u32 a1, u32 a2, u32 a3, u32 a4, UfoState* st,
                  u32 a6, f32 dt)
{
    Creature* c = (Creature*)p0;
    if (((NearGoal*)&c->mC0)->Do()) {
        if (st->mb00 == 0) {
            u32 idx = ((RandU32*)0x1601760)->Do(5);
            ((Interrupt*)c)->Do(((u32*)0x147c108)[idx], 0xffffffff, 0);
            st->mb00 = 1;
        }
        st->mf04 += dt;
        if (st->mf04 > 3.0f)
            return false;
    }
    return true;
}

// @ 0x00d917e0
u32 FUN_00d917e0(u32 a0, u32 a1, u32 a2, u32 flags)
{
    return (flags >> 27) & 1;
}

// @ 0x00d917f0
f32* FUN_00d917f0(f32* out, void* citizen)
{
    Creature* c = (Creature*)citizen;
    Vec3f* src = (Vec3f*)((FnP)((void**)c->mC0.mpVtbl)[0x2c / 4])(&c->mC0);
    Vec3f pos;
    pos.x = src->x;
    pos.y = src->y;
    pos.z = src->z;
    out[0] = pos.x;
    out[1] = pos.y;
    out[2] = pos.z;

    f32 best = *(f32*)0x147c0f4;
    LaneInfo* info = (LaneInfo*)((GetLane*)((GetCity*)c)->Do())->Do();
    LaneNode* b = info->mpBegin;
    s32 n = (s32)(info->mpEnd - info->mpBegin);
    s32 i = 0;

    for (; i < n; ++i) {
        LaneNode* p = b + i;
        f32 dx = pos.x - p->v.x;
        f32 dy = pos.y - p->v.y;
        f32 dz = pos.z - p->v.z;
        f32 d = (dx * dx + dz * dz) + dy * dy;
        if (d < best) {
            *(Vec3f*)out = p->v;
            best = d;
        }
    }
    return out;
}

// @ 0x00d91a40
bool FUN_00d91a40(void* p0, u32 a1, u32 a2, u32 a3, u32 a4, DeadState* st,
                  u32 a6, f32 dt)
{
    Creature* c = (Creature*)p0;
    u32 state = st->mn00;
    st->mf04 += dt;

    if (state == 0) {
        st->mn08 += 1;
        if (st->mn08 >= 2)
            st->mn00 = 1;
        return true;
    }
    if (state == 1) {
        if (c->mn2B0 == 3 && (c->mn110 & 0x1000) == 0)
            return true;
        st->mn00 = 2;
        u32 anim = c->mbB5E ? 0x2481db4 : 0x3cc7f35;
        ((Interrupt*)c)->Do(anim, 0xffffffff, 0);
        ((FnV)((void**)c->mpVtbl)[0x54 / 4])(c);
        return true;
    }
    if (state != 2)
        return true;

    if (st->mb10 != 0) {
        f32 t = st->mf14 - dt;
        st->mf14 = t;
        if (t > 0.0f) {
            if (c->mpB54 != 0) {
                B54Obj* o = (B54Obj*)c->mpB54;
                double r = pow(0.1, (double)dt);
                o->mf80 = (f32)((1.0 - r) * (double)*(f32*)0x13eb960
                                + (double)o->mf80 * r);
                return true;
            }
        } else {
            ((Fn1)((void**)c->mpVtbl)[0xc8 / 4])(c, 0);
            return true;
        }
    }

    if (c->mbB5E != 0) {
        if (st->mb18 == 0 || !((C0E0C0*)c)->Do(0x2481db4)) {
            st->mb18 = 1;
            ((PlayAnim*)c)->Do(0x2481db4, 1, 0xffffffff);
        }
        st->mf0C -= dt;
        if (st->mf0C > 0.0f)
            return true;
        if (((FnP)((void**)c->mC0.mpVtbl)[0x48 / 4])(&c->mC0)) {
            st->mb10 = 1;
            st->mf14 = 1.5f;
            return true;
        }
        ((Fn1)((void**)c->mpVtbl)[0xc8 / 4])(c, 0);
        return true;
    }

    f32 v = c->mf5E0 - dt * 5.0f;
    if (v < 0.0f)
        v = 0.0f;
    c->mSub5A8.Set(v);
    FUN_00d90ac0(c, st);
    return true;
}

// @ 0x00d91fb0
bool FUN_00d91fb0(void* p0, u32 a1, u32 a2, u32 a3, u32 a4, u32* out)
{
    Creature* c = (Creature*)p0;
    if (out != 0)
        *out = 0xffffffff;

    FB8Obj* p = (FB8Obj*)c->mpFB8;
    f32 best = *(f32*)0x147c0f4;
    u32 idx = 0xffffffff;

    for (u32 i = 0; i < (u32)(p->mpEnd - p->mpBegin); ++i) {
        Vec3f* node = p->mpBegin + i;
        Vec3f* pos = (Vec3f*)((FnP)((void**)c->mC0.mpVtbl)[0x2c / 4])(&c->mC0);
        f32 dx = pos->x - node->x;
        f32 dz = pos->z - node->z;
        f32 dy = pos->y - node->y;
        f32 d = dx * dx + dz * dz + dy * dy;
        if (d < best) {
            best = d;
            idx = i;
        }
    }

    if (idx != 0xffffffff) {
        ((Interrupt*)c)->Do(0x2481db0, 0xffffffff, 0);
        ((MoveTo*)c)->Do(3, p->mpBegin + idx, 1.0f, 6.0f);
        *out = idx;
        return true;
    }
    return false;
}

// @ 0x00d921c0
bool FUN_00d921c0(void* p0, u32 a1, u32 a2, u32 flags, u32 a4, u32* out)
{
    Creature* c = (Creature*)p0;
    if (out != 0)
        out[0] = 0;
    out[1] = flags & 2;

    Vec3f pos;
    FUN_00d917f0((f32*)&pos, c);

    Vec3f* cur = (Vec3f*)((FnP)((void**)c->mC0.mpVtbl)[0x2c / 4])(&c->mC0);
    Vec3f tmp;
    if (pos.x == cur->x && pos.y == cur->y && pos.z == cur->z) {
        Vec3f* r = ((PlanetModel*)SP_PlanetModel())->MakeRandomWorldPosition(
            &tmp, (Vec3f*)((FnP)((void**)c->mC0.mpVtbl)[0x2c / 4])(&c->mC0),
            *(f32*)0x1470f1c, *(f32*)0x14853e0);
        pos = *r;
    }

    Vec3f* r2 = ((PlanetModel*)SP_PlanetModel())->MakeRandomWorldPosition(
        &tmp, &pos, 0.0f, *(f32*)0x14007f4);
    pos = *r2;

    ((Interrupt*)c)->Do(0x2481db0, 0xffffffff, 0);
    ((MoveTo*)c)->Do(2, &pos, 1.0f, *(f32*)0x147b9f0);
    return true;
}
