// Slice s010317d0 -- SP::cAbductionBeamLocomotion::Update (0x010317d0): per-tick movement of an object
// held in a UFO abduction beam. Moves the object along the beam (tractor: toward the UFO, otherwise
// drops away from it), reorients it toward the beam direction, rescales it and writes its velocity.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no EH frame in the original).
#include "types.h"

typedef unsigned int uint;
typedef void *P;

struct Vec3 { float x, y, z; };

// Inline SSE clamp helper used by this module (maxss/minss with SSE NaN semantics).
inline float Clamp(float x, float lo, float hi)
{
    __asm {
        movss xmm0, x
        maxss xmm0, lo
        minss xmm0, hi
        movss x, xmm0
    }
    return x;
}
template <class T> inline const T &Max(const T &a, const T &b) { return (a < b) ? b : a; }

#include <math.h>
#pragma intrinsic(sqrt)

inline float Length(const Vec3 *v)
{
    float sq = (v->z * v->z + v->y * v->y) + v->x * v->x;
    return sqrtf(sq);
}

// ---------------------------------------------------------------- external classes (stubs)
struct PlantIface {
    P GetSpeciesKey();                         // 0x00c3e290 (ecx+0x650)
};
struct Species {
    P GetScaleKey();                           // 0x00b8f860
};
struct PlantSpeciesMgr {
    Species *GetSpeciesFromID(P id);           // 0x00b90410 (ret 4)
};

struct PlanetModelT {
    float GetRadiusAt(const Vec3 *pos);                                  // 0x00b7ef70 (ret 4)
    void  Func_b81630(Vec3 *out, const Vec3 *in);                        // 0x00b81630 (ret 8)
    Vec3 *Func_b82110(Vec3 *out, const Vec3 *from, const Vec3 *dir);     // 0x00b82110 (ret 0xc)
};

struct Tuning {
    char  pad[0x198];
    float tractorLo, tractorHi;   // +0x198, +0x19c
    float dropLo, dropHi;         // +0x1a0, +0x1a4
};

struct UFOData { char pad[0x714]; int mode; };               // cSPGameDataUFO (mode at +0x714)
struct BeamOwner { char pad[0x114]; P mpRef; };              // +0x114: AutoRefCount to the spatial object

struct SpatialObj {
    char pad04[0x77 - 4];
    uint8_t  b77;
    char pad78[0x1f0 - 0x78];
    uint32_t f1f0;
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a();
    virtual Vec3 *GetPosition();               // slot 0x2c
    virtual void v0c();
    virtual float GetScale();                  // slot 0x34
    virtual void v0e();
    virtual void SetOrientation(P q);          // slot 0x3c
    virtual void SetScale(float s);            // slot 0x40
    virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16();
    virtual void GetUp(Vec3 *out);             // slot 0x5c
    virtual void v18(); virtual void v19(); virtual void v1a(); virtual void v1b();
    virtual void v1c(); virtual void v1d(); virtual void v1e(); virtual void v1f();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v2a(); virtual void v2b();
    virtual void v2c(); virtual void v2d();
    virtual P QueryInterface(uint id);         // slot 0xb8
    void SetLocomotion(P loco);                // 0x00c421b0 (ret 4)
};

struct Beam {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a();
    virtual bool IsFinished();                 // slot 0x2c
    char pad[0x134 - 4];
    BeamOwner *mpOwner;                        // +0x134
    void GetEndPoints(Vec3 *a, Vec3 *b);       // 0x00cb8ba0 (ret 8)
};

struct LocoCtx {
    Vec3  vel;
    float f0c;
    float dt;           // +0x10
    SpatialObj *obj;    // +0x14
};

struct Matrix3 { float m[9]; };
struct Quat4 { float q[4]; };

// ---- callees (calling conventions checked against the callers / callee epilogues)
PlantSpeciesMgr *PlantSpeciesManager();          // 0x00b3d420 (cdecl, no args)
float    FUN_01030d50(P key);                    // cdecl, 1 stack arg
PlanetModelT *PlanetModel();                     // 0x00b3d350
Tuning  *GetTuning();                            // 0x00c37360
uint     GetCurrentGameMode();                   // 0x00b5b800
UFOData *interface_cast_UFO(P *ref);             // 0x00c9f040 EA::COM::interface_cast<cSPGameDataUFO*,...>
void     normalized_safe(Vec3 *out, const Vec3 *v);   // 0x00449c20 (cdecl)
void     FUN_00afa0c0(Matrix3 *out, const Vec3 *a, const Vec3 *b, const Vec3 *c);   // cdecl, 4 args
P        FUN_0046d660(const Vec3 *a, const Matrix3 *m);     // cdecl, 2 args
P        FUN_00c64ad0(Quat4 *out, P in);                    // cdecl, 2 args
P        FUN_01030e20(SpatialObj *o);                       // cdecl, 1 arg
void *   operator_new(uint size, const char *name, int a, int b, int c, int d);   // 0x00f473a0

extern Vec3  g_016ded38;
extern float g_015b7668;

struct AbductionBeamLoco {
    void  *vptr0, *vptr4;
    P      pad8, padc;
    Beam  *mpBeam;          // +0x10
    float  mDistance;       // +0x14
    bool   mbTractor;       // +0x18
    float  mOriginalScale;  // +0x1c
    bool   mFirstUpdate;    // +0x20
    float  mSpeed;          // +0x24

    void Update(LocoCtx *ctx);    // ret 4
};

// SP::cAbductionBeamLocomotion::Update @ 0x010317d0
void AbductionBeamLoco::Update(LocoCtx *ctx)
{
    if (mFirstUpdate) {
        mOriginalScale = ctx->obj->GetScale();
        if (!mbTractor && ctx->obj) {
            PlantIface *plant = (PlantIface *)ctx->obj->QueryInterface(0xaeb336b4);
            if (plant) {
                P id = plant->GetSpeciesKey();
                Species *sp = PlantSpeciesManager()->GetSpeciesFromID(id);
                mOriginalScale = FUN_01030d50(sp->GetScaleKey());
            }
        }
        mFirstUpdate = false;
    }

    if (mpBeam == 0 || mpBeam->IsFinished()) {
        P *loco = (P *)operator_new(0x14, "Simulator/cDropToGroundLocomotion", 0, 0, 0, 0);
        if (loco == 0) {
            ctx->obj->SetLocomotion(0);
            return;
        }
        loco[2] = (P)0x013ec458;
        loco[3] = 0;
        loco[0] = (P)0x01499590;
        loco[2] = (P)0x01499580;
        loco[4] = 0;
        ctx->obj->SetLocomotion(loco);
        return;
    }

    ctx->obj->f1f0 = 4;
    ctx->obj->b77 = 0;
    Vec3 a, b;
    mpBeam->GetEndPoints(&a, &b);
    Vec3 *cur = ctx->obj->GetPosition();

    if (mDistance < 0.0f) {
        if (mbTractor) {
            float dx = a.x - cur->x, dy = a.y - cur->y, dz = a.z - cur->z;
            mDistance = (float)sqrt((double)(dy * dy + (dx * dx + dz * dz)));
        } else {
            mDistance = 0.0f;
        }
    }

    float len0 = Length(cur);
    float height = len0 - PlanetModel()->GetRadiusAt(cur);
    float t = Clamp(height, 0.0f, 500.0f) * 0.002f;
    float smooth = (3.0f - t * 2.0f) * t * t;

    Tuning *tune = GetTuning();
    if (mbTractor) {
        float v = (tune->tractorHi - tune->tractorLo) * smooth + tune->tractorLo;
        if (GetCurrentGameMode() != 0x1654c05)
            v = v * 0.5f;
        float spd = v;
        BeamOwner *owner = mpBeam->mpOwner;
        if (owner && owner->mpRef) {
            UFOData *ufo = interface_cast_UFO(&owner->mpRef);
            if (ufo && ufo->mode == 5)
                spd = g_015b7668 * v;
        }
        mDistance = mDistance - spd * ctx->dt;
        if (mDistance < 0.0f)
            mDistance = 0.0f;
    } else {
        mDistance = ((tune->dropHi - tune->dropLo) * smooth + tune->dropLo) * ctx->dt + mDistance;
    }

    if (mDistance < 1.5258789e-05f)
        return;

    Vec3 d;
    d.x = b.x - a.x; d.y = b.y - a.y; d.z = b.z - a.z;
    Vec3 dir;
    normalized_safe(&dir, &d);
    Vec3 p2;
    p2.x = mDistance * dir.x + a.x;
    p2.y = dir.y * mDistance + a.y;
    p2.z = dir.z * mDistance + a.z;
    PlanetModelT *model = PlanetModel();
    if (model) {
        model->Func_b81630(&d, &p2);
        float lenD = (float)sqrt((double)((d.y * d.y + d.z * d.z) + d.x * d.x));
        float lenP = (float)sqrt((double)((p2.z * p2.z + p2.y * p2.y) + p2.x * p2.x));
        if (lenP < lenD) {
            Vec3 tmp;
            p2 = *model->Func_b82110(&tmp, &a, &dir);
            float dx = a.x - p2.x, dy = a.y - p2.y, dz = a.z - p2.z;
            mDistance = (float)sqrt((double)((dz * dz + dy * dy) + dx * dx));
        }
    }

    float inv = 1.0f / ctx->dt;
    ctx->vel.x = inv * (p2.x - cur->x);
    ctx->vel.y = (p2.y - cur->y) * inv;
    ctx->vel.z = (p2.z - cur->z) * inv;

    d.x = -dir.x; d.y = -dir.y; d.z = -dir.z;
    Vec3 n = d;
    if (d.x != g_016ded38.x || d.y != g_016ded38.y || d.z != g_016ded38.z) {
        Vec3 u;
        ctx->obj->GetUp(&u);
        Vec3 c;
        c.x = u.y * d.z - u.z * d.y;
        c.y = u.z * d.x - d.z * u.x;
        c.z = d.y * u.x - u.y * d.x;
        Vec3 w;
        w.x = d.y * c.z - c.y * d.z;
        w.y = d.z * c.x - d.x * c.z;
        w.z = c.y * d.x - d.y * c.x;
        Matrix3 m;
        FUN_00afa0c0(&m, &w, &n, &c);
        SpatialObj *o = ctx->obj;
        Quat4 q;
        o->SetOrientation(FUN_00c64ad0(&q, FUN_0046d660(&n, &m)));
    }

    float ratio = 0.0f;
    {
        float dx = a.x - b.x, dy = a.y - b.y, dz = a.z - b.z;
        float len = (float)sqrt((double)((dz * dz + dy * dy) + dx * dx));
        if (1.5258789e-05f < len)
            ratio = mDistance / len;
    }

    if (ctx->obj && ctx->obj->QueryInterface(0xaeb336b4)) {
        float s = mOriginalScale * ratio;
        ctx->obj->SetScale(Max(0.2f, s));
        return;
    }
    P p = FUN_01030e20(ctx->obj);
    if (p)
        *(float *)((char *)p + 0x660) = ratio;
}
