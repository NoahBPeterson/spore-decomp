// Slice s00db0130 -- SP::TRIBE_NPC_GIFT_Activate (0x00DB0130, __cdecl, /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast).
// Tribe "NPC gift" behaviour activation: finds (or creates) the "TribeNPCGift" task object for the
// (tribe, citizen) pair, works out where the gift giver stands and which way it faces (toward the other
// citizen, or toward the tribe's tool/centre), spawns the "GiftActionCircle" effect and starts the task.
// Arguments (cdecl): citizen, 4 unused, behaviour state block (6th), parameter object (7th).
#include <math.h>
#include "types.h"

struct Vec3 { float x, y, z; Vec3() {} Vec3(float a, float b, float c) : x(a), y(b), z(c) {} };

#define PV(n) virtual void pv##n();

struct IRef { virtual void AddRef(); virtual void Release(); };

struct Spatial {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual const Vec3* GetPosition();                 // +0x2c
    PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21)
    virtual bool vf58();                               // +0x58
    virtual const Vec3* GetOffset(Vec3* out);          // +0x5c
    PV(24) PV(25) PV(26) PV(27) PV(28)
    virtual float GetRadius();                         // +0x74
    char* __thiscall FUN_00cee330();                   // bundle query: returns the first bundle entry or 0
};

struct IWinTextHolder {                                // EA::AutoRefCount<...> out of line operator=
    IRef* mp;
    void __thiscall Assign(IRef* p);                   // 0x00b5f950, ret 4
};
struct TargetHolder {
    IRef* mp;
    void __thiscall Assign(void* p);                   // 0x00c35d50, ret 4
};

struct Tribe {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13)
    PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24)
    virtual void vf64();                               // +0x64
    uint32_t pad04[(0x120 - 4) / 4];
    Spatial  mPos;                                     // +0x120
    uint32_t pad124[(0x260 - 0x124) / 4];
    struct Obj260* mpObj;                              // +0x260
    uint32_t pad264[1];
    float    mfRadius;                                 // +0x268
    Vec3* __thiscall FUN_00c91190(Vec3* out, int a);   // ret 8
};
struct Obj260 {
    uint32_t pad[0x34 / 4];
    Spatial  mSpatial;                                 // +0x34
};

struct AnimCtl {
    void* __thiscall PlayIdleAnimation(unsigned id, int a);        // 0x00bc96a0, ret 8
    void  __thiscall FUN_00bc97f0(int a, int b, float c, int d);   // ret 0x10
};
struct GiftTask;
struct Citizen;
struct AnimOwner {
    uint32_t pad[2];
    AnimCtl  mCtl;                                     // +8
    void __thiscall FUN_00bcb480(GiftTask* t, Citizen* c, int a, int b);   // ret 0x10
};
struct MgrB48 {
    void __thiscall FUN_00bca810(int a, int b, Citizen* c, float f, int d, int e);   // ret 0x18
};

struct Citizen {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13)
    PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26)
    PV(27) PV(28) PV(29) PV(30) PV(31) PV(32)
    virtual void vf84(void* part, int a, int b);       // +0x84
    Tribe* __thiscall GetTribe();                      // 0x00c22f50
    uint32_t pad04[(0x34 - 4) / 4];
    Spatial  mBundle;                                  // +0x34
    uint32_t pad38[(0xc0 - 0x38) / 4];
    Spatial  mLoco;                                    // +0xc0
    uint32_t padc4[(0xb48 - 0xc4) / 4];
    MgrB48*    mpB48;                                  // +0xb48
    AnimOwner* mpAnim;                                 // +0xb4c
};

struct Target {
    virtual void AddRef(); virtual void Release();
    uint32_t pad04[(0x34 - 4) / 4];
    Spatial  mSpatial;                                 // +0x34
    uint32_t pad38[(0x128 - 0x38) / 4];
    void*    mp128;                                    // +0x128
};
struct TargetQuery {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual IRef* Query(uint32_t id);                  // +0xc
};
struct ParamObj {
    uint32_t pad[2];
    TargetQuery* mpQuery;                              // +8
};

struct EffectCircle {                                  // 100 bytes, "Simulator/GiftActionCircle"
    uint32_t data[25];
    EffectCircle();                                    // 0x00afba10
    void __thiscall FUN_00af9cf0(const Vec3* p, float r, const Vec3* dir, float z);   // ret 0x10
    void __thiscall FUN_00afef10(int a, float s);      // ret 8
};
void* __cdecl operator new(unsigned size, const char* name, int a, int b, int c, int d);   // 0x00f473a0

struct TaskBase0 {
    uint32_t pad0[6];
    int      mCount;                                   // +0x18
    uint32_t pad1c[(0x1a4 - 0x1c) / 4];
    void __thiscall FUN_00bc9b20(Citizen* c);          // ret 4
};
struct GiftBase {                                      // sub-object at +0x1a4
    Vec3  pos;                                         // +0
    Vec3  dir;                                         // +0xc
    int   mi18;
    float f1c;
    bool  mbFlag;                                      // +0x20
    EffectCircle* mpEffect;                            // +0x24
    uint32_t pad28;
    IRef* mpTribe;                                     // +0x2c
    Citizen* mpOther;                                  // +0x30
};
struct GiftTask : TaskBase0 {
    GiftBase mGift;                                    // +0x1a4
};

struct TaskMgr {
    GiftTask* __thiscall Find(uint32_t kind, void* fn, void* key);                          // 0x00bca620, ret 0xc
    GiftTask* __thiscall Create(uint32_t kind, int n, void* p, const char* name);           // 0x00bcb0b0, ret 0x10
};
TaskMgr* __cdecl FUN_00bc9b00();

struct Mgr1 {
    void* __thiscall FUN_00ac79d0();
    void  __thiscall FUN_00ac7de0(void* a, void* b);   // ret 8
};
Mgr1* __cdecl FUN_00b3d2b0();

struct cPlanetModel {
    Vec3* __thiscall DirectionToSurfacePosition(Vec3* out, const Vec3* dir);   // 0xB815A0
};

struct GiftState {                                     // behaviour state block
    int            mDone;                              // +0
    IWinTextHolder mHolder4;                           // +4
    Tribe*         mpTribe;                            // +8 (an AutoRefCount in the source)
    Citizen*       mpCitizen;                          // +0xc
    Target*        mpTarget;                           // +0x10
    TargetHolder   mHolder14;                          // +0x14
    Vec3           mTargetPos;                         // +0x18
    int            mi24;
    uint32_t       pad28[(0x34 - 0x28) / 4];
    float          mf34;
};

namespace SP {
cPlanetModel* __cdecl PlanetModel();                   // 0xB3D350
Vec3* __cdecl normalized_safe(Vec3* out, const Vec3* in);   // 0x449C20
bool __cdecl TRIBE_NPC_GIFT_Activate(Citizen* c, int p2, int p3, int p4, int p5, GiftState* st, ParamObj* prm);
}
using namespace SP;

Vec3* __cdecl Vector3_Normalize(Vec3* out, const Vec3* in);   // 0x436CE0
IRef* __cdecl FUN_00d998d0(void* obj, uint32_t id);
float __cdecl GetPropertyFloat(void* props, unsigned id, float def);   // 0x004e1c70
void __cdecl FUN_00d9aa20(EffectCircle* e);

extern void* g_pProps1581288;                          // 0x1581288
extern const float kF13ebc5c;                          // 0x013ebc5c
extern const float kF147c218;                          // 0x0147c218

static inline Vec3 operator-(const Vec3& a, const Vec3& b) { return Vec3(a.x - b.x, a.y - b.y, a.z - b.z); }
static inline Vec3 operator*(const Vec3& a, float k) { return Vec3(a.x * k, a.y * k, a.z * k); }
static inline Vec3 MulAdd(const Vec3& a, float k, const Vec3& p) { return Vec3(a.x * k + p.x, a.y * k + p.y, a.z * k + p.z); }

static inline void AssignRef(IRef*& slot, IRef* p)
{
    IRef* old = slot;
    if (p != old) {
        if (p) p->AddRef();
        slot = p;
        if (old) old->Release();
    }
}

// @ 0x00DB0130
bool __cdecl SP::TRIBE_NPC_GIFT_Activate(Citizen* c, int, int, int, int, GiftState* st, ParamObj* prm)
{
    ParamObj* pp = prm;
    if (st) {
        st->mHolder4.mp = 0;
        st->mpTribe = 0;
        st->mpCitizen = 0;
        st->mpTarget = 0;
        st->mHolder14.mp = 0;
    }
    void* anim = c->mpAnim->mCtl.PlayIdleAnimation(0x2000, 0);
    if (anim) {
        AssignRef((IRef*&)st->mpTribe, FUN_00d998d0(anim, 0x4f396a66));
        if (!st->mpTribe) {
            AssignRef((IRef*&)st->mpCitizen, FUN_00d998d0(anim, 0x4f176642));
            if (st->mpCitizen)
                ((IWinTextHolder*)&st->mpTribe)->Assign((IRef*)st->mpCitizen->GetTribe());
        }
    }
    if (!st->mpTribe)
        return false;

    st->mi24 = -1;
    st->mf34 = 0.0f;
    if (pp) {
        TargetQuery* q = pp->mpQuery;
        IRef* o = q ? q->Query(0x4ffcdeda) : 0;
        AssignRef((IRef*&)st->mpTarget, o);
    }

    Vec3 vA, vB, vC;
    struct { Tribe* t; Citizen* c; } key = { st->mpTribe, st->mpCitizen };
    GiftTask* task = FUN_00bc9b00()->Find(0x567cb99, (void*)0xdabbe0, &key);
    if (!task) {
        task = FUN_00bc9b00()->Create(0x567cb99, 0xf, (void*)0x18eb4b7, "TribeNPCGift");
        GiftBase* g = &task->mGift;
        if (g) {
            g->mpTribe = 0;
            g->mpOther = 0;
        }
        float dflt = kF13ebc5c;
        g->mbFlag = false;
        g->mi18 = 0;
        g->f1c = GetPropertyFloat(g_pProps1581288, 0xd9471e5f, dflt);
        AssignRef(g->mpTribe, (IRef*)st->mpTribe);
        AssignRef((IRef*&)g->mpOther, (IRef*)st->mpCitizen);
        if (g->mpOther)
            g->mpOther->mpAnim->mCtl.FUN_00bc97f0(0, 2, 1.0f, 0);

        Spatial* loco = &c->mLoco;
        float r;
        if (loco->vf58()) {
            if (g->mpOther) {
                st->mi24 = -1;
                Spatial* other = &g->mpOther->mLoco;
                const Vec3* p1 = loco->GetPosition();
                const Vec3* p2v = other->GetPosition();
                vB.x = p2v->x - p1->x;
                vB.y = p2v->y - p1->y;
                vB.z = p2v->z - p1->z;
                SP::normalized_safe(&vA, &vB);
                g->pos = *g->mpOther->mLoco.GetPosition();
                Vector3_Normalize(&vB, &g->pos);
                float nx = vA.x, ny = vA.y, nz = vA.z;
                float ux = vB.x, uy = vB.y, uz = vB.z;
                float dot = (ny * uy + nz * uz) + ux * nx;
                g->dir.x = nx - ux * dot;
                g->dir.y = ny - uy * dot;
                g->dir.z = nz - uz * dot;
                g->dir = *SP::normalized_safe(&vC, &g->dir);
            } else {
                st->mi24 = -1;
                Spatial* sp = &st->mpTribe->mpObj->mSpatial;
                g->pos = *sp->GetPosition();
                g->dir = *st->mpTribe->mpObj->mSpatial.GetOffset(&vC);
            }
        } else {
            st->mpTribe->vf64();
            vB = *st->mpTribe->FUN_00c91190(&vC, 1);
            vA = vB;
            float k = (loco->GetRadius() + 1.0f) * 4.0f;
            const Vec3* tp = st->mpTribe->mPos.GetPosition();
            vB.x = vB.x - tp->x;
            vB.y = vB.y - tp->y;
            vB.z = vB.z - tp->z;
            const Vec3* rv = SP::normalized_safe(&vC, &vB);
            vA.x = rv->x * k + vA.x;
            vA.y = rv->y * k + vA.y;
            vA.z = rv->z * k + vA.z;
            g->pos = *SP::PlanetModel()->DirectionToSurfacePosition(&vC, &vA);
            const Vec3* tp2 = st->mpTribe->mPos.GetPosition();
            vB.x = tp2->x - vA.x;
            vB.y = tp2->y - vA.y;
            vB.z = tp2->z - vA.z;
            SP::normalized_safe(&vA, &vB);
            g->dir = vA;
        }

        if (st->mpTarget) {
            st->mTargetPos = *st->mpTarget->mSpatial.GetPosition();
            st->mHolder14.Assign(st->mpTarget->mp128);
        }

        Vec3* q;
        if (g->mpOther) {
            float a = c->GetTribe()->mfRadius * 0.5f;
            a = a + a;
            r = (float)sqrt((double)((float)task->mCount * a * a));
            g->mpEffect = new ("Simulator/GiftActionCircle", 0, 0, 0, 0) EffectCircle();
            float rt = g->mpOther->GetTribe()->mfRadius;
            float h = c->GetTribe()->mfRadius + rt + r;
            vB.x = g->dir.x * h;
            vB.y = g->dir.y * h;
            vB.z = g->dir.z * h;
            const Vec3* op = g->mpOther->mLoco.GetPosition();
            vA.x = op->x - vB.x;
            vA.y = op->y - vB.y;
            vA.z = op->z - vB.z;
            q = &vA;
        } else {
            float rad = st->mpTribe->mpObj->mSpatial.GetRadius();
            float t1 = c->GetTribe()->mfRadius + rad;
            float a = c->GetTribe()->mfRadius * 0.5f;
            a = a + a;
            r = (float)sqrt((double)((float)task->mCount * a * a));
            g->mpEffect = new ("Simulator/GiftActionCircle", 0, 0, 0, 0) EffectCircle();
            float h = r + t1;
            vB.x = g->pos.x - h * g->dir.x;
            vB.y = g->pos.y - g->dir.y * h;
            vB.z = g->pos.z - g->dir.z * h;
            q = &vB;
        }
        SP::PlanetModel()->DirectionToSurfacePosition(&vC, q);
        g->mpEffect->FUN_00af9cf0(&vC, r, &g->dir, 0.0f);
        g->mpEffect->FUN_00afef10(0, c->GetTribe()->mfRadius * 0.5f + 1.0f);
        FUN_00d9aa20(g->mpEffect);
    }
    c->mpAnim->FUN_00bcb480(task, c, 0, 0);
    char* b = c->mBundle.FUN_00cee330();
    if (b) {
        if (*(int*)(b + 0x12c) == 5 && !task->mGift.mbFlag) {
            task->FUN_00bc9b20(c);
            st->mHolder4.Assign((IRef*)b);
            task->mGift.mbFlag = true;
        } else {
            FUN_00b3d2b0()->FUN_00ac7de0(b, FUN_00b3d2b0()->FUN_00ac79d0());
        }
    }
    st->mDone = 1;
    c->mpB48->FUN_00bca810(1, 2, c, kF147c218, 0, 0);
    if (task->mGift.mpOther)
        c->vf84((char*)task->mGift.mpOther + 0x5a8, 0, 2);
    return true;
}
