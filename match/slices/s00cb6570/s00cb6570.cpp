// Slice s00cb6570 -- combat/ballistic object helpers around FUN_00cb6570.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

extern "C" double __cdecl sqrt(double x);
#pragma intrinsic(sqrt)

// ---------------------------------------------------------------------------
// callees (call targets are relocation-masked by the checker)
// ---------------------------------------------------------------------------
#define TCS(ret, params, name) ((ret(__thiscall*)params) name)

int   FUN_00cb6570(void*, void*, float, void*, void*, void*, void*, void*); // 0x00cb6570 cdecl
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
struct Float3 { float x, y, z; };

Float3 g_waterPoint;                // 0x0169a414  world water-sphere centre
float  g_169a9e8[3];                // 0x0169a9e8  reference up vector

void* g_vft_1475470[2];             // 0x01475470
void* g_vft_147545c[2];             // 0x0147545c
void* g_vft_1475360[2];             // 0x01475360
void* g_vft_1475354[2];             // 0x01475354
void* g_vft_147532c[2];             // 0x0147532c

char g_13f94d4;                             // 0x013f94d4  interface-id descriptor

// terrain/water query object returned by FUN_00b3d240
struct IPlanetProbe {
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0C();
    virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1C();
    virtual void s20(); virtual void s24(); virtual void s28(); virtual void s2C();
    virtual void s30(); virtual void s34(); virtual void s38(); virtual void s3C();
    virtual void s40(); virtual void s44(); virtual void s48(); virtual void s4C();
    virtual bool s50(const float* origin, const Float3* end, void* callback,
                     RefCnt** pHit, Float3* out, void* arg);      // 0x00cb6570
};

struct cPlanetModel {
    void  SampleTerrain(Float3* out, const float* pos, const float* dir); // 0x00b82060
    float GetWaterHeight();                                               // 0x00b7e390
};

IPlanetProbe* __cdecl FUN_00b3d240();       // 0x00b3d240
void*         __cdecl FUN_00b3d350();       // 0x00b3d350  SP::PlanetModel
char __cdecl FUN_005a9c40(const float*, const float*, const float*, float, float*); // 0x005a9c40 IntersectRaySphere
void  SP_QuaternionFromDirections(void*, const float*, const float*); // 0x00698180
void  FUN_00b18660();                       // 0x00b18660  SP::cGameData::cGameData
void  FUN_00c43860();                       // 0x00c43860
void* FUN_0104f930();                       // 0x0104f930  SP::cSPSpaceToolData::GetStrategy

// ===========================================================================
// @ 0x00cb6a50
// ===========================================================================
uint32_t __cdecl FUN_00cb6a50(float* p1, float* p2, float dist, float* out)
{
    float px = g_waterPoint.x;
    float py = g_waterPoint.y;
    float pz = g_waterPoint.z;
    float t  = dist + 1.0f;
    float t0 = t;

    cPlanetModel* planet = (cPlanetModel*)FUN_00b3d350();
    float water  = planet->GetWaterHeight();
    float x      = p1[0];

    if (water * water <= (x * x + p1[1] * p1[1]) + p1[2] * p1[2]
        && FUN_005a9c40(p1, p2, &g_waterPoint.x, water, &t) != 0) {
        if (t <= dist) {
            px = x + p2[0] * t;
            py = p1[1] + p2[1] * t;
            pz = p1[2] + p2[2] * t;
        } else {
            t = t0;
        }
    }

    Float3 s;
    cPlanetModel* planet2 = (cPlanetModel*)FUN_00b3d350();
    planet2->SampleTerrain(&s, p1, p2);

    if (s.x != g_waterPoint.x || s.y != g_waterPoint.y || s.z != g_waterPoint.z)
        t0 = (float)sqrt((((double)s.z - p1[2]) * ((double)s.z - p1[2]) +
                          ((double)s.y - p1[1]) * ((double)s.y - p1[1])) +
                         ((double)s.x - x) * ((double)s.x - x));

    uint32_t r;
    if (t <= t0) {
        out[0] = px;
        out[1] = py;
        out[2] = pz;
        r = 2;
    } else {
        out[0] = s.x;
        out[1] = s.y;
        out[2] = s.z;
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
int __cdecl FUN_00cb6570(void* p1v, void* p2v, float fDist,
                         void* pHitSlot, void* pOutSlot, void* a5, void* a6,
                         void* callback)
{
    const float* p1  = (const float*)p1v;
    const float* p2  = (const float*)p2v;
    void**       ppHit = (void**)pHitSlot;
    float*       pOut  = (float*)pOutSlot;

    Float3 n;
    Float3 end;
    Float3 probe;
    Float3 terrain;
    RefCnt* pHit = 0;
    float fProbeDist;
    float fWaterT;
    float fTerrainDist;
    float fLenPlus = fDist + 1.0f;

    {
        double d2 = (double)p2[0] * (double)p2[0] +
                    ((double)p2[1] * (double)p2[1] + (double)p2[2] * (double)p2[2]);
        float inv = (float)(1.0 / sqrt(d2));
        n.x = p2[0] * inv;
        n.y = p2[1] * inv;
        n.z = p2[2] * inv;
    }

    end.x = p1[0] + n.x * fDist;
    end.y = p1[1] + n.y * fDist;
    end.z = p1[2] + n.z * fDist;

    fProbeDist = fLenPlus;
    if (FUN_00b3d240()->s50(p1, &end, callback, &pHit, &probe, a6)) {
        double dx = (double)probe.x - p1[0];
        double dy = (double)probe.y - p1[1];
        double dz = (double)probe.z - p1[2];
        fProbeDist = (float)sqrt((dx * dx + dy * dy) + dz * dz);
    }

    end.x = g_waterPoint.x;
    end.y = g_waterPoint.y;
    end.z = g_waterPoint.z;
    fWaterT = fLenPlus;

    {
        cPlanetModel* planet = (cPlanetModel*)FUN_00b3d350();
        float water = planet->GetWaterHeight();
        float len2  = (p1[1] * p1[1] + p1[2] * p1[2]) + p1[0] * p1[0];
        if (len2 >= water * water
            && FUN_005a9c40(p1, &n.x, &g_waterPoint.x, water, &fWaterT) != 0) {
            if (fWaterT > fDist) {
                fWaterT = fLenPlus;
            } else {
                end.x = p1[0] + n.x * fWaterT;
                end.y = p1[1] + n.y * fWaterT;
                end.z = p1[2] + n.z * fWaterT;
            }
        }
    }

    {
        cPlanetModel* planet = (cPlanetModel*)FUN_00b3d350();
        planet->SampleTerrain(&terrain, p1, &n.x);
    }

    fTerrainDist = fLenPlus;
    if (terrain.x != g_waterPoint.x || terrain.y != g_waterPoint.y ||
        terrain.z != g_waterPoint.z) {
        double dx = (double)terrain.x - p1[0];
        double dy = (double)terrain.y - p1[1];
        double dz = (double)terrain.z - p1[2];
        fTerrainDist = (float)sqrt((dx * dx + dy * dy) + dz * dz);
    }

    int   code;
    float fSelected;
    if (fWaterT > fTerrainDist) {
        if (fProbeDist > fTerrainDist) {
            pOut[0] = terrain.x;
            pOut[1] = terrain.y;
            pOut[2] = terrain.z;
            code = 1;
            fSelected = fTerrainDist;
        } else {
            pOut[0] = probe.x;
            pOut[1] = probe.y;
            pOut[2] = probe.z;
            code = 0;
            fSelected = fProbeDist;
        }
    } else {
        if (fProbeDist > fWaterT) {
            pOut[0] = end.x;
            pOut[1] = end.y;
            pOut[2] = end.z;
            code = 2;
            fSelected = fWaterT;
        } else {
            pOut[0] = probe.x;
            pOut[1] = probe.y;
            pOut[2] = probe.z;
            code = 0;
            fSelected = fProbeDist;
        }
    }

    if (fDist < fSelected) {
        pOut[0] = p1[0] + n.x * fDist;
        pOut[1] = p1[1] + n.y * fDist;
        pOut[2] = p1[2] + n.z * fDist;
        if (pHit != 0)
            pHit->vf1();
        return 3;
    }

    if (code == 0) {
        RefCnt* old = (RefCnt*)*ppHit;
        if (pHit != old) {
            if (pHit != 0)
                pHit->vf0();
            *ppHit = pHit;
            if (old != 0)
                old->vf1();
        }
    }
    if (pHit != 0)
        pHit->vf1();
    return code;
}

// ===========================================================================
// SP::cArtilleryProjectile::Update -- runs one combat-line probe per frame.
// The receiver is the +0x504 base sub-object, so the owning projectile is
// recovered by walking back 0x504 bytes.
// ===========================================================================
struct ILoco {
    virtual void l00(); virtual void l04(); virtual void l08(); virtual void l0C();
    virtual void l10(); virtual void l14(); virtual void l18(); virtual void l1C();
    virtual void l20(); virtual void l24(); virtual void l28();
    virtual Float3* GetPosition();                  // slot 0x2c
    virtual void l30(); virtual void l34();
    virtual void SetPosition(Float3* pos);          // slot 0x38
};

struct IHit {
    virtual void h00();                             // slot 0x00  AddRef
    virtual void h04();                             // slot 0x04  Release
    virtual void h08();
    virtual void* AsInterface(const void* id);      // slot 0x0c
    virtual uint32_t v10();                         // slot 0x10
};

struct IProjObj {
    virtual void p00(); virtual void p04(); virtual void p08(); virtual void p0C();
    virtual void p10(); virtual void p14(); virtual void p18(); virtual void p1C();
    virtual void p20(); virtual void p24(); virtual void p28(); virtual void p2C();
    virtual void p30(); virtual void p34(); virtual void p38(); virtual void p3C();
    virtual void p40(); virtual void p44(); virtual void p48();
    virtual uint32_t v4C();                         // slot 0x4c
    virtual void v50();                             // slot 0x50
    virtual void v54();                             // slot 0x54
};

struct IToolData {
    void* GetStrategy();                            // 0x0104f930
};

struct IToolStrategy {
    virtual void t00(); virtual void t04(); virtual void t08(); virtual void t0C();
    virtual void t10(); virtual void t14(); virtual void t18(); virtual void t1C();
    virtual void t20(); virtual void t24(); virtual void t28(); virtual void t2C();
    virtual void Use(void* tool, Float3* pos, uint32_t code, uint32_t unused); // slot 0x30
};

struct ProjSub {                     // view from the +0x504 sub-object
    void*  mpVt;                     // +0x000  (object +0x504)
    char   _p004[0x14 - 0x04];
    Float3 mPos;                     // +0x014  (object +0x518)
    void*  mpCtx;                    // +0x020  (object +0x524)
    char   _p024[0x30 - 0x24];
    void*  mpTool;                   // +0x030  (object +0x534)

    bool Update();                   // 0x00cb7110
};

// ===========================================================================
// @ 0x00cb7110
// ===========================================================================
bool ProjSub::Update()
{
    ILoco*    loco = (ILoco*)((char*)this - 0x4d0);
    IProjObj* obj  = (IProjObj*)this;

    Float3* v = loco->GetPosition();
    float dx = v->x - mPos.x;
    float dy = v->y - mPos.y;
    float dz = v->z - mPos.z;
    float dist = (float)sqrt((dx * dx + dy * dy) + dz * dz);

    if (dist > 0.0f) {
        float inv = 1.0f / dist;

        Float3 delta;
        delta.x = dx * inv;
        delta.y = dy * inv;
        delta.z = dz * inv;

        Float3 out;
        void*  hit = 0;
        int    code = ((int(__cdecl*)(void*, void*, float, void*, void*, CtxObj*, void*))
                       SP_CombatLineTest)(&mPos, &delta, dist, &hit, &out,
                                          (CtxObj*)mpCtx, (void*)4);

        if (hit == 0 || ((IHit*)hit)->AsInterface((const void*)0x0ed7fc07) == 0) {
            if (code != 3) {
                IHit* other = (IHit*)0;
                if (hit != 0) {
                    other = (IHit*)((IHit*)hit)->AsInterface(&g_13f94d4);
                    if (other != 0) {
                        uint32_t a = obj->v4C();
                        uint32_t b = other->v10();
                        if (b == a)
                            goto release;
                    }
                }
                loco->SetPosition(&out);
                obj->v54();
                if (mpTool != 0) {
                    IToolStrategy* strategy =
                        (IToolStrategy*)((IToolData*)mpTool)->GetStrategy();
                    if (strategy != 0)
                        strategy->Use(mpTool, &out, (uint32_t)code, 0);
                }
                ((IHit*)hit)->h04();
                return false;
            }
        }
        if (hit != 0)
            ((IHit*)hit)->h04();
    }
release:
    Float3* v2 = loco->GetPosition();
    mPos = *v2;
    return true;
}