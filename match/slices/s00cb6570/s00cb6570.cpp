// Slice s00cb6570 -- combat/ballistic object helpers around FUN_00cb6570.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

// ---------------------------------------------------------------------------
// callees (call targets are relocation-masked by the checker)
// ---------------------------------------------------------------------------
#define TCS(ret, params, name) ((ret(__thiscall*)params) name)

void  FUN_00cb6570(void*, void*, float, void*, void*, void*, void*, void*); // 0x00cb6570 cdecl
void  FUN_00cb64c0();                        // 0x00cb64c0 default callback
void  FUN_00cb64e0();                        // 0x00cb64e0 alt callback
void  FUN_00cb63c0();                        // 0x00cb63c0 default callback
void  FUN_00cb63e0();                        // 0x00cb63e0 alt callback
void* FUN_00f473a0(size_t, const char*, int, int, int, int); // 0x00f473a0 cdecl operator new
void  FUN_00f47380(void*);                   // 0x00f47380 cdecl operator delete[]
void  FUN_00c421b0();                        // 0x00c421b0 thiscall
void  FUN_00b184c0();                        // 0x00b184c0 thiscall cGameData dtor

char     g_169a408;   // 0x0169a408  byte flag store
uint32_t g_169a40c;   // 0x0169a40c
void*    g_vft_145dca8[4];  // 0x0145dca8  vtable reset stored into +0x504

// ---------------------------------------------------------------------------
// small "combat line" context: byte at +8 is saved/restored around the call,
// byte at +9 selects the alternate callback.
// ---------------------------------------------------------------------------
struct CtxObj {
    char _p000[0x08];
    char mState;                 // +0x08
    char mAlt;                   // +0x09
};

// ---------------------------------------------------------------------------
// ref-counted pointer whose vtable[1] releases the object
// ---------------------------------------------------------------------------
struct RefCnt {
    virtual void vf0();          // vtable[0]
    virtual void vf1();          // vtable[1]  Release
};

// cLocomotiveObject sub-object at +0x34 (non-virtual methods)
struct Loco {
    void Shutdown();             // 0x00c43f90
    void Destroy();              // 0x00c432e0
    char _p000[0x1fc - 0x34];
};

// ---------------------------------------------------------------------------
// the game object built out of cGameData + Object
// ---------------------------------------------------------------------------
struct GameObject {
    char     _p000[0x2c];
    void*    mp2c;               // +0x2c
    char     _p030[4];
    Loco     mLoco;              // +0x34
    void*    mp1fc;              // +0x1fc
    void*    mp200;              // +0x200
    void*    mp204;              // +0x204
    char     _p208[0x224 - 0x208];
    uint32_t m224;               // +0x224
    char     _p228[0x504 - 0x228];
    void*    mp504;              // +0x504
    char     _p508[0x518 - 0x508];
    void*    mp518;              // +0x518
    void*    mp51c;              // +0x51c
    void*    mp520;              // +0x520
    void*    mp524;              // +0x524
    char     _p528[0x534 - 0x528];
    void*    mp534;              // +0x534

    void       RemoveOwner();
    GameObject* _virtual_dtor(unsigned char flags);
    void       DestroyRefs();
    void       SetBallistic(const uint32_t* src);
    void       SetForwardDir(void* arg);
};

// ===========================================================================
// @ 0x00cb6d20
// ===========================================================================
void GameObject::RemoveOwner()
{
    void* p;

    p = mp518;
    if (p != 0) {
        mp518 = 0;
        ((void(__thiscall*)(void*)) (*(void***)p)[4 / 4])(p);
    }

    p = mp51c;
    if (p != 0) {
        mp51c = 0;
        ((void(__thiscall*)(void*)) (*(void***)p)[4 / 4])(p);
    }

    p = mp2c;
    if (p != 0) {
        mp2c = 0;
        ((void(__thiscall*)(void*)) (*(void***)p)[4 / 4])(p);
    }

    mLoco.Shutdown();
}

// ===========================================================================
// @ 0x00cb6fe0
// ===========================================================================
GameObject* GameObject::_virtual_dtor(unsigned char flags)
{
    void* p;

    p = mp534;
    if (p != 0)
        ((void(__thiscall*)(void*)) (*(void***)p)[8 / 4])(p);

    p = mp524;
    if (p != 0)
        ((void(__thiscall*)(void*)) (*(void***)p)[0x64 / 4])(p);

    mp504 = (void*)g_vft_145dca8;    // vtable pointer reset on the +0x34 subobj
    mLoco.Destroy();
    ((void(__thiscall*)(void*)) FUN_00b184c0)(this);

    if ((flags & 1) != 0)
        FUN_00f47380(this);

    return this;
}

// ===========================================================================
// @ 0x00cb6960
// ===========================================================================
void __cdecl FUN_00cb6960(void* a0, void* a1, float a2, void* a3, void* a4,
                          CtxObj* a5, void* a6, char a7)
{
    char  old = 0;
    void* fp  = (void*)&FUN_00cb64c0;

    if (a5 != 0) {
        old = a5->mState;
        a5->mState = 1;
        if (a5->mAlt != 0) {
            fp = (void*)&FUN_00cb64e0;
            g_169a40c = ((uint32_t(__thiscall*)(void*)) (*(void***)a5)[0x10 / 4])(a5);
        }
        g_169a408 = a7;
    }

    FUN_00cb6570(a0, a1, a2, a3, a4, a5, a6, fp);

    if (a5 != 0)
        a5->mState = old;
}

// ===========================================================================
// @ 0x00cb69e0
// ===========================================================================
void __cdecl SP_CombatLineTest(void* a0, void* a1, float a2, void* a3, void* a4,
                               CtxObj* a5, void* a6)
{
    char  old = 0;
    void* fp  = (void*)&FUN_00cb63c0;

    if (a5 != 0) {
        old = a5->mState;
        a5->mState = 1;
        if (a5->mAlt != 0) {
            fp = (void*)&FUN_00cb63e0;
            g_169a40c = ((uint32_t(__thiscall*)(void*)) (*(void***)a5)[0x10 / 4])(a5);
        }
    }

    FUN_00cb6570(a0, a1, a2, a3, a4, a5, a6, fp);

    if (a5 != 0)
        a5->mState = old;
}

// ===========================================================================
// @ 0x00cb6ca0
// ===========================================================================
void GameObject::DestroyRefs()
{
    void* p;

    p = mp518;
    if (p != 0) {
        mp518 = 0;
        ((void(__thiscall*)(void*)) (*(void***)p)[4 / 4])(p);
    }

    p = mp51c;
    if (p != 0) {
        mp51c = 0;
        ((void(__thiscall*)(void*)) (*(void***)p)[4 / 4])(p);
    }

    p = mp520;
    if (p != 0) {
        mp520 = 0;
        ((void(__thiscall*)(void*)) (*(void***)p)[0x64 / 4])(p);
    }

    p = mp524;
    if (p != 0) {
        mp524 = 0;
        ((void(__thiscall*)(void*)) (*(void***)p)[8 / 4])(p);
    }

    p = mp2c;
    if (p != 0) {
        mp2c = 0;
        ((void(__thiscall*)(void*)) (*(void***)p)[4 / 4])(p);
    }

    mLoco.Shutdown();
}

// ===========================================================================
// @ 0x00cb7040
// ===========================================================================
void* g_vft_13ec458[2];   // 0x013ec458  base vtable written into the new object
void* g_vft_1475164[2];   // 0x01475164
void* g_vft_1475114[2];   // 0x01475114

struct BallisticLocomotion {
    void* mpVt0;              // +0x00
    void* m04;                // +0x04
    void* mpVt8;              // +0x08
    void* m0c;                // +0x0c
};

void GameObject::SetBallistic(const uint32_t* src)
{
    uint32_t* p = (uint32_t*)
        ((void*(__thiscall*)(void*)) (*(void***)((char*)this + 0x34))[0x2c / 4])((char*)this + 0x34);

    mp518 = (void*)p[0];
    mp51c = (void*)p[1];
    mp520 = (void*)p[2];
    m224  = 4;

    BallisticLocomotion* o = (BallisticLocomotion*)
        FUN_00f473a0(0x10, "Simulator/cBallisticLocomotion", 0, 0, 0, 0);
    if (o != 0) {
        o->mpVt8 = (void*)g_vft_13ec458;
        o->m0c   = 0;
        o->mpVt0 = (void*)g_vft_1475164;
        o->mpVt8 = (void*)g_vft_1475114;
    } else {
        o = 0;
    }

    ((void(__thiscall*)(void*, void*)) FUN_00c421b0)((char*)this + 0x34, o);

    mp1fc = (void*)src[0];
    mp200 = (void*)src[1];
    mp204 = (void*)src[2];
}

// ===========================================================================
// declarations used by the ray/water probing helpers below
// ===========================================================================
float g_169a414;                    // 0x0169a414  world plane point (x)
float g_169a418;                    // 0x0169a418  world plane point (y)
float g_169a41c;                    // 0x0169a41c  world plane point (z)
float g_169a9e8[3];                 // 0x0169a9e8  reference up vector

void* g_vft_1475470[2];             // 0x01475470
void* g_vft_147545c[2];             // 0x0147545c
void* g_vft_1475360[2];             // 0x01475360
void* g_vft_1475354[2];             // 0x01475354
void* g_vft_147532c[2];             // 0x0147532c

void* FUN_00b3d240();                       // 0x00b3d240
void* FUN_00b3d350(...);                    // 0x00b3d350  SP::PlanetModel
void  FUN_00b7e390();                       // 0x00b7e390  cPlanetModel::GetWaterHeight (thiscall)
void  FUN_00b82060();                       // 0x00b82060  thiscall (planet, a, b, c)
char  FUN_005a9c40(float*, float*, float*, float, float*); // 0x005a9c40 IntersectRaySphere
void  SP_QuaternionFromDirections(void*, const float*, const float*); // 0x00698180
void  FUN_00b18660();                       // 0x00b18660  SP::cGameData::cGameData
void  FUN_00c43860();                       // 0x00c43860
void* FUN_0104f930();                       // 0x0104f930  SP::cSPSpaceToolData::GetStrategy

// ===========================================================================
// @ 0x00cb6a50
// ===========================================================================
uint32_t __cdecl FUN_00cb6a50(float* p1, float* p2, float dist, float* out)
{
    float px = g_169a414;
    float py = g_169a418;
    float pz = g_169a41c;
    float t  = dist + 1.0f;
    float t0 = t;

    void* planet = FUN_00b3d350();
    float water  = ((float(__thiscall*)(void*)) FUN_00b7e390)(planet);
    float x      = p1[0];

    if (water * water <= (x * x + p1[1] * p1[1]) + p1[2] * p1[2]
        && FUN_005a9c40(p1, p2, &g_169a414, water, &t) != 0) {
        if (t <= dist) {
            px = x + p2[0] * t;
            py = p1[1] + p2[1] * t;
            pz = p1[2] + p2[2] * t;
        } else {
            t = t0;
        }
    }

    float sx, sy, sz;
    void* planet2 = FUN_00b3d350();
    ((void(__thiscall*)(void*, float*, float*, float*)) FUN_00b82060)(planet2, &sx, p1, p2);

    if (sx != g_169a414 || sy != g_169a418 || sz != g_169a41c)
        t0 = sqrtf((sz - p1[2]) * (sz - p1[2]) + (sy - p1[1]) * (sy - p1[1]) + (sx - x) * (sx - x));

    uint32_t r;
    if (t <= t0) {
        out[0] = px;
        out[1] = py;
        out[2] = pz;
        r = 2;
    } else {
        out[0] = sx;
        out[1] = sy;
        out[2] = sz;
        r = 1;
        t = t0;
    }

    if (dist < t) {
        out[0] = x + p2[0] * dist;
        out[1] = p1[1] + p2[1] * dist;
        out[2] = p1[2] + p2[2] * dist;
        r = 3;
    }
    return r;
}

// ===========================================================================
// @ 0x00cb6dc0
// ===========================================================================
void GameObject::SetForwardDir(void* arg)
{
    void* loco = (void*)&mLoco;
    float* v = (float*)((void*(__thiscall*)(void*)) (*(void***)loco)[0x2c / 4])(loco);
    float  x = v[0];

    float inv = 1.0f / (float)sqrt((x * x + v[1] * v[1]) + v[2] * v[2] + 1e-08f);

    float n[3];
    n[0] = x * inv;
    n[1] = v[1] * inv;
    n[2] = v[2] * inv;

    char q[16];
    SP_QuaternionFromDirections(q, g_169a9e8, n);
    ((void(__thiscall*)(void*, void*)) (*(void***)loco)[0x3c / 4])(loco, q);

    void* old = mp520;
    if (arg != old) {
        if (arg != 0)
            ((void(__thiscall*)(void*)) (*(void***)arg)[0x60 / 4])(arg);
        mp520 = arg;
        if (old != 0)
            ((void(__thiscall*)(void*)) (*(void***)old)[0x64 / 4])(old);
    }
    m224 = 5;
}

// ===========================================================================
// SP::cArtilleryProjectile -- projectile with a ballistic locomotion driver
// ===========================================================================
struct ArtilleryProjectile {
    void*  mpVt0;                    // +0x00
    void*  mpVt1;                    // +0x04
    char   _p008[0x34 - 0x08];
    void*  mpVtLoco;                 // +0x34
    char   _p038[0x108 - 0x38];
    void*  mpVt3;                    // +0x108
    char   _p10c[0x504 - 0x10c];
    void*  mpVt4;                    // +0x504
    float  mTargetOffset[3];         // +0x508
    char   mFlag;                    // +0x514
    char   _p515[0x524 - 0x515];
    void*  mpOwner;                  // +0x524
    int    mMinDamage;               // +0x528
    int    mMaxDamage;               // +0x52c
    int    mDamageType;              // +0x530
    void*  mTool;                    // +0x534

    void   ctor();
};

// ===========================================================================
// @ 0x00cb6ed0
// ===========================================================================
void ArtilleryProjectile::ctor()
{
    ((void(__thiscall*)(void*)) FUN_00b18660)(this);
    ((void(__thiscall*)(void*)) FUN_00c43860)(&mpVtLoco);

    mpVt4 = (void*)g_vft_145dca8;
    mTargetOffset[0] = 0.0f;
    mTargetOffset[1] = 0.0f;
    mTargetOffset[2] = 0.0f;
    mFlag = 0;
    mpVt0 = (void*)g_vft_1475470;
    mpVt1 = (void*)g_vft_147545c;
    mpVtLoco = (void*)g_vft_1475360;
    mpVt3 = (void*)g_vft_1475354;
    mpVt4 = (void*)g_vft_147532c;
    mpOwner = 0;
    mMinDamage = 0;
    mMaxDamage = 1;
    mDamageType = 0;
    mTool = 0;
}

// ===========================================================================
// @ 0x00cb6570
// ===========================================================================
int __cdecl FUN_00cb6570(float* p1, float* p2, float dist,
                         void* a3, void* a4, void* a5, void* a6, void* cb)
{
    float nx = p2[0];
    float t  = dist + 1.0f;
    float tWater = 0.0f;

    float inv = 1.0f / sqrtf(nx * nx + p2[1] * p2[1] + p2[2] * p2[2]);
    float ny = p2[1] * inv;
    float nz = p2[2] * inv;
    nx *= inv;

    float ex = nx * dist + p1[0];
    float ey = p1[1] + ny * dist;
    float ez = p1[2] + nz * dist;

    float  best = 0.0f;
    float* out  = &tWater;
    void*  probe = FUN_00b3d240();
    uint32_t ok = ((uint32_t(__thiscall*)(void*, float*, float*, void*))
                   (*(void***)probe)[0x50 / 4])(probe, p1, &ex, cb);
    if (ok != 0) {
        best = sqrtf((nz - p1[2]) * (nz - p1[2]) + (ny - p1[1]) * (ny - p1[1]) + (nx - p1[0]) * (nx - p1[0]));
    }

    float wx = g_169a414;
    float wy = g_169a418;
    float wz = g_169a41c;
    void* planet = FUN_00b3d350();
    float water  = ((float(__thiscall*)(void*)) FUN_00b7e390)(planet);
    float w      = water;
    float x      = p1[0];

    if (w * w <= (p1[1] * p1[1] + p1[2] * p1[2]) + x * x
        && FUN_005a9c40(p1, p2, &g_169a414, water, &best) != 0
        && (float)best <= ex) {
        wx = x + ny * best;
        wy = p1[1] + nz * best;
        wz = p1[2] + tWater * best;
    }

    float sx, sy, sz;
    void* planet2 = FUN_00b3d350(&sx, p1, &best);
    ((void(__thiscall*)(void*, float*, float*, float*)) FUN_00b82060)(planet2, &sx, p1, &best);

    if (sx != g_169a414 || sy != g_169a418 || sz != g_169a41c)
        best = sqrtf((sy - p1[1]) * (sy - p1[1]) + ((sz - p1[2]) * (sz - p1[2]) + (sx - x) * (sx - x)));

    int r;
    if (best <= (float)best) {
        out[0] = wx;
        out[1] = wy;
        out[2] = wz;
        r = 2;
    } else {
        out[0] = nx;
        out[1] = ny;
        out[2] = nz;
        r = 0;
    }

    if (ex < t) {
        out[0] = ny * ex + p1[0];
        out[1] = p1[1] + nz * ex;
        out[2] = p1[2] + tWater * ex;
        if (out != 0)
            ((void(__thiscall*)(void*)) (*(void***)out)[4 / 4])(out);
        return 3;
    }
    if (out != 0)
        ((void(__thiscall*)(void*)) (*(void***)out)[4 / 4])(out);
    return r;
}

// ===========================================================================
// SP::cArtilleryProjectile::Update -- runs one combat-line probe per frame.
// The receiver is the +0x504 base sub-object, so the owning projectile is
// recovered by walking back 0x504 bytes.
// ===========================================================================
struct ProjSub {                     // view from the +0x504 sub-object
    void*  mpVt;                     // +0x000  (object +0x504)
    char   _p004[0x14 - 0x04];
    float  mPos[3];                  // +0x014  (object +0x518)
    void*  mpCtx;                    // +0x020  (object +0x524)
    char   _p024[0x30 - 0x24];
    void*  mpTool;                   // +0x030  (object +0x534)

    uint32_t Update();               // 0x00cb7110
};

// ===========================================================================
// @ 0x00cb7110
// ===========================================================================
uint32_t ProjSub::Update()
{
    char* obj = (char*)this - 0x504;
    float* dirv = (float*)((float*(__thiscall*)(void*))
        (*(void***)(obj + 0x34))[0x2c / 4])(obj + 0x34);

    float d0 = dirv[0] - mPos[0];
    float d1 = dirv[1] - mPos[1];
    float d2 = dirv[2] - mPos[2];
    float dist = sqrtf(d0 * d0 + (d1 * d1 + d2 * d2));

    if (dist <= 0.0f)
        goto tail;

    {
        float u0 = d0 * (1.0f / dist);
        float u1 = d1 * (1.0f / dist);
        float u2 = d2 * (1.0f / dist);

        void* hit = 0;
        uint32_t code = ((uint32_t(__cdecl*)(void*, void*, float, void*, void*, void*, void*))
                         SP_CombatLineTest)(mPos, &u0, dist, &hit, &u0, mpCtx, (void*)4);

        if (hit == 0
            || ((uint32_t(__thiscall*)(void*, void*)) (*(void***)hit)[0xc / 4])(hit, (void*)0x0ed7fc07) == 0) {
            if (code != 3) {
                if (hit == 0)
                    goto tail;
                void* other = (void*)(size_t)((uint32_t(__thiscall*)(void*, void*))
                    (*(void***)hit)[0xc / 4])(hit, (void*)&g_vft_1475470);
                if (other == 0) {
                LAB_:
                    ((void(__thiscall*)(void*, float*)) (*(void***)(obj + 0x34))[0x38 / 4])(obj + 0x34, &u0);
                    ((void(__thiscall*)(void*)) (*(void***)obj)[0x54 / 4])(obj);
                    if (mpTool != 0) {
                        void* strat = FUN_0104f930();
                        if (strat != 0)
                            ((void(__thiscall*)(void*, void*, void*, void*, void*))
                             (*(void***)strat)[0x30 / 4])(strat, mpTool, &u0, hit, 0);
                    }
                    uint32_t rr = ((uint32_t(__thiscall*)(void*)) (*(void***)hit)[4 / 4])(hit);
                    return rr & 0xffffff00u;
                }
                uint32_t a = ((uint32_t(__thiscall*)(void*)) (*(void***)obj)[0x4c / 4])(obj);
                uint32_t b = ((uint32_t(__thiscall*)(void*)) (*(void***)other)[0x10 / 4])(other);
                if (b != a)
                    goto LAB_;
            }
            if (hit == 0)
                goto tail;
        }
        ((void(__thiscall*)(void*)) (*(void***)hit)[4 / 4])(hit);
    }

tail:
    {
        float* dirv2 = (float*)((float*(__thiscall*)(void*))
            (*(void***)(obj + 0x34))[0x2c / 4])(obj + 0x34);
        mPos[0] = dirv2[0];
        mPos[1] = dirv2[1];
        mPos[2] = dirv2[2];
    }
    return 1;
}