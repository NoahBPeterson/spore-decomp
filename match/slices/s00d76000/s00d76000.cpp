// Slice s00d76000 -- SP::TRIBE_GATHER_Tick (0x00D76000, __cdecl, /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast).
// Tribe-member "gather" behaviour tick: a 26-state machine keyed on st->mState (the 6th stack
// argument). Like its sibling behaviour ticks it takes 8 stack arguments (creature, 4 scalars,
// the state block, 2 more); only the creature and the state block are used here.
//
// States (read from the jump table at 0xD772B4):
//   0 pick the next job      1 walk to target     2 arrive / choose tool anim   3 pick animation
//   4 wait for anim event    5/6 finish / drop    7 start 'carry' anim          8 wait, then deposit
//   0xb..0xe spawn + carry an effect object       0xf..0x11 walk to the target and hit it
//   0x12..0x16 find a spot, attack, collect       0x17..0x19 repair/consume loop
// Many helpers are not yet named; they keep their FUN_ addresses.
#include "types.h"

struct Vec3 { float x, y, z; };

#define V4(a) virtual void a##0(); virtual void a##1(); virtual void a##2(); virtual void a##3();
struct IRefObj { virtual void v0(); virtual void Release(); void __thiscall FUN_00b00080(int a, int b); };  // ret 8      // slot at +4

// Spatial interface (the sub-object with a vtable that sits inside creatures/objects).
struct Spatial {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10();
    virtual const Vec3* GetPosition();                 // +0x2c
    virtual void v12(); virtual void v13();
    virtual float GetBundleValue(int which);           // +0x38
    virtual void v15(); virtual void v16(); virtual void v17();
    virtual bool vf48();                               // +0x48
    virtual void v19(); virtual void v20(); virtual void v21();
    virtual bool vf58();                               // +0x58
    virtual const Vec3* GetOffset(Vec3* out);          // +0x5c
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28();
    virtual float GetRadius();                         // +0x74
    bool __thiscall IsNearGoal();                      // 0xC42E20 (SP::cLocomotiveObject::IsNearGoal)
    // 0xCEE330 / 0xCEE380: queries on the creature's bundle container (at +0x34)
    char* __thiscall FUN_00cee330();
    float __thiscall FUN_00cee380();
};

// Tribe object (GetTribe() result): vtable slot 0xAC/4 = 43 is called once at entry.
struct VecRange { Vec3* begin; Vec3* end; };
struct cTribe {
    V4(a) V4(b) V4(c) V4(d) V4(e) V4(f) V4(g) V4(h) V4(i) V4(j)
    virtual void k0(); virtual void k1(); virtual void k2();
    virtual void TickHook();                                         // +0xAC
    VecRange* __thiscall FUN_00c97020();
    Vec3* __thiscall FUN_00c91190(Vec3* out, int a);                  // ret 8
    void __thiscall FUN_00c94b50(float v);                            // ret 4
    char* __thiscall FUN_00c8e820(int a);                             // ret 4
    void __thiscall FindSpot(int a, int b);                           // 0xC98750, ret 8
};

// Resource node referenced by st->mpResource.
struct ResourceNode {
    void __thiscall GetSpotPosition(Vec3* out, int idx);          // 0xB02B90
};

struct Positionable {   // sub-object at +0x34 of the spawned effect; slot +0x38
    V4(a) V4(b) V4(c) virtual void d0(); virtual void d1();
    virtual void SetPosition(const Vec3* p);
};
struct Attacher { V4(a) V4(b) V4(c) virtual void Attach(void* obj); };  // slot +0x30
struct RefPtr { IRefObj* mp; void __thiscall Assign(void* p); };    // 0xB5F950

struct Mgr1 {  // returned by 0xB3D2B0
    void* __thiscall FUN_00ac79d0();
    char* __thiscall FUN_00ac7ab0(float amount, void* what, int n);   // ret 0xC
    void  __thiscall FUN_00ac7eb0(void* a, void* b);                  // ret 8
};
struct Mgr2 {  // returned by 0xB3D440
    void __thiscall FUN_00b09b80(void* node, int idx, int zero);      // ret 0xC
};
namespace SP { struct cSPCreatureCitizen; }
using namespace SP;
struct Mgr3 {  // returned by 0xAF13B0
    bool __thiscall FUN_00af0bd0(cSPCreatureCitizen* c, int a, int b); // ret 0xC
};
struct cPlanetModel {
    Vec3* __thiscall DirectionToSurfacePosition(Vec3* out, const Vec3* dir);  // 0xB815A0
};
struct UIntMap { unsigned& __thiscall operator_idx(const unsigned& key); };    // 0x643A40

// The behaviour state block (6th stack arg).
struct TribeGatherState {
    int      mState;         // +0x00
    IRefObj* mpTarget;       // +0x04  object being gathered from / attacked
    ResourceNode* mpResource;// +0x08
    int      mSpotIndex;     // +0x0c
    float    mTimer;         // +0x10
    float    mAccum;         // +0x14
    unsigned mCount;         // +0x18
    bool     mFlag1c;        // +0x1c
    bool     mFlag1d;        // +0x1d
    int      mFoundSpot;     // +0x20
    char*    mpEffect;       // +0x24  spawned effect object (AutoRefCount)
};

namespace SP {
struct cSPCreatureCitizen {
    cTribe* __thiscall GetTribe();                                     // 0xC22F50
    bool    __thiscall HasSpecializedTool(int tool);                   // 0xC236E0
    int     __thiscall GetToolEffect(int tool);                        // 0xC235E0
    bool    __thiscall IsLeader();                                     // 0xC232D0
    void    __thiscall PlayAnimation(unsigned guid, int a, int b);     // 0xC12190
    void    __thiscall PlayAnimationWithTarget(unsigned guid, const Vec3* t, int b);              // 0xC14910
    void    __thiscall PlayAnimationWithTarget2(unsigned guid, void* t, int b, void* other);      // 0xC14940
    unsigned __thiscall GetCurrentAnimationGUID();                     // 0xC0E040
    bool    __thiscall IsAnimationQueuedOrCurrent();                   // 0xC0D240
    bool    __thiscall WaitForAnimEventOrEnd(unsigned ev, unsigned* t, int a, int b, int c);      // 0xC14EF0
    bool    __thiscall AnimationFinished(int a);                       // 0xC123F0
    void    __thiscall CreateBodyEffect(unsigned t, unsigned a, unsigned b);                      // 0xC14F70
    void    __thiscall MoveToPointAtSpeed(int kind, const Vec3* p, float a, float b);             // 0xC1C1D0
    void    __thiscall MoveToPointAndFacingAtSpeed(int kind, const Vec3* p, const Vec3* f, float a, float b); // 0xC1C5C0
    bool    __thiscall FUN_00c26c90(unsigned a, int b);
    int     __thiscall FUN_00c22a70();
    char    __thiscall FUN_00c22850();
    void    __thiscall FUN_00c22860(int a);
    void    __thiscall FUN_00c22870();
    void    __thiscall FUN_00c227f0(Vec3 v);
    void    __thiscall FUN_00c234a0(Vec3 v);
    float   __thiscall FUN_00c0b9c0();
    void    __thiscall FUN_00c0b9d0(float v);
    bool    __thiscall FUN_00c25530(int a);
    bool    __thiscall FUN_00c25a50(void* a);
    int     __thiscall FUN_00c0dfd0(unsigned a);
    void    __thiscall FUN_00c15150(unsigned a, int b);
    void    __thiscall FUN_00c0d1e0(Vec3* v);
    unsigned* __thiscall FUN_00c0fa10(void* a, int b);
};
bool __cdecl TRIBE_GATHER_Tick(cSPCreatureCitizen* c, int p2, int p3, unsigned p4, unsigned p5,
                               TribeGatherState* st, int p7, float p8);
cPlanetModel* __cdecl PlanetModel();                 // 0xB3D350
Vec3* __cdecl normalized_safe(Vec3* out, const Vec3* in);   // 0x449C20
}
using namespace SP;

struct CombatantPart { float __thiscall FUN_00bfc490(); void __thiscall PartialRepair(float v); };  // at c+0x5a8
Mgr1* __cdecl FUN_00b3d2b0();
Mgr2* __cdecl FUN_00b3d440();
Mgr3* __cdecl FUN_00af13b0();
unsigned __cdecl FUN_00ac8fa0(void* props, unsigned id, int n);
float __cdecl GetPropertyFloat(void* props, unsigned id, float def);   // SP::GetPropertyT<float>
bool __cdecl FUN_0041dd30(const Vec3* a, const Vec3* b);
void __cdecl FUN_00da6270(cSPCreatureCitizen* c, int a);
bool __cdecl FUN_00d75f40(cSPCreatureCitizen* c, TribeGatherState* st);
void __cdecl FUN_00d75700(cSPCreatureCitizen* c, TribeGatherState* st);
void __cdecl FUN_00d754b0(cSPCreatureCitizen* c, TribeGatherState* st, int a);
bool __cdecl FUN_00d75870(cSPCreatureCitizen* c, ResourceNode* r);
int  __cdecl FUN_00dba630(cSPCreatureCitizen* c, int a);
void __cdecl FUN_00e398e0(unsigned id, void* a, void* b, void* d, int e, int f, int g);

extern void* g_pProps;        // 0x158128C
extern float g_f1581298;      // 0x1581298
extern float g_f158129c;      // 0x158129C
extern float g_f15812a0;      // 0x15812A0
extern UIntMap g_map15812a4;  // 0x15812A4
extern float g_f1687a10;      // 0x1687A10
extern float g_f1687a14;      // 0x1687A14
extern Vec3 g_v169ef40;       // 0x169EF40
extern Vec3 g_v169ef8c;       // 0x169EF8C

static inline Spatial* BundleOf(cSPCreatureCitizen* c) { return (Spatial*)((char*)c + 0x34); }
static inline Spatial* LocoOf(cSPCreatureCitizen* c)   { return (Spatial*)((char*)c + 0xc0); }
static inline void ReleaseRef(IRefObj*& r) { IRefObj* p = r; if (p) { r = 0; p->Release(); } }
static inline Spatial* SpatialOfPtr(void* obj) { return obj ? (Spatial*)((char*)obj + 0x34) : (Spatial*)0; }



// @ 0x00D76000
bool __cdecl SP::TRIBE_GATHER_Tick(cSPCreatureCitizen* c, int p2, int p3, unsigned p4, unsigned p5,
                                   TribeGatherState* st, int p7, float p8)
{
    (void)p2; (void)p3; (void)p4; (void)p5; (void)p7; (void)p8;
    cTribe* tribe = c->GetTribe();
    tribe->TickHook();

    switch (st->mState) {
    case 0: {
        Spatial* loco = LocoOf(c);
        Spatial* bundle = BundleOf(c);
        if (!loco->vf58()) {
            unsigned lim = FUN_00ac8fa0(g_pProps, 0x78f4963a, 4);
            if (st->mCount > lim)
                goto fail;
        }
        {
            float have = bundle->FUN_00cee380();
            float cap = bundle->GetBundleValue(1);
            bool toIdle = (cap <= have);
            if (!toIdle && st->mFlag1d) {
                if (!FUN_00af13b0()->FUN_00af0bd0(c, 4, 0))
                    toIdle = true;
            }
            if (toIdle) {
                if (!bundle->FUN_00cee330())
                    goto fail;
                st->mState = 0x12;
            }
        }
        if (c->HasSpecializedTool(7)) {
            if (bundle->FUN_00cee380() > 0.0f && c->FUN_00c0b9c0() < g_f1687a14) {
                st->mTimer = g_f1581298;
                st->mState = 0x17;
            }
        }
        if (st->mState != 0)
            return true;
        if (!bundle->FUN_00cee330() && !c->FUN_00c26c90(0x30000, 0))
            return true;
        if (st->mpTarget) {
            ReleaseRef(*(IRefObj**)((char*)st->mpTarget + 0x108));
            ReleaseRef(st->mpTarget);
        }
        if (FUN_00d75f40(c, st)) {
            cPlanetModel* pm = PlanetModel();
            if (!st->mpResource) {
                st->mState = 0xf;
                st->mFlag1c = true;
                return true;
            }
            Vec3 dirTmp;
            Vec3 surf;
            st->mpResource->GetSpotPosition(&dirTmp, st->mSpotIndex);
            pm->DirectionToSurfacePosition(&surf, &dirTmp);
            float radius = ((float*)st->mpResource)[0x6c / 4];
            float h = loco->GetRadius();
            float height = (h + radius) + 0.3f;
            const Vec3* rp = (const Vec3*)((char*)st->mpResource + 0x10);
            Vec3 d;
            d.x = surf.x - rp->x;
            d.y = surf.y - rp->y;
            d.z = surf.z - rp->z;
            Vec3 nTmp;
            Vec3 n = *normalized_safe(&nTmp, &d);
            Vec3 b;
            b.x = n.x * height + surf.x;
            b.y = n.y * height + surf.y;
            b.z = n.z * height + surf.z;
            Vec3 bOut;
            Vec3 b2 = *pm->DirectionToSurfacePosition(&bOut, &b);
            Vec3 negN;
            negN.x = -n.x;
            negN.y = -n.y;
            negN.z = -n.z;
            c->MoveToPointAndFacingAtSpeed(2, &b2, &negN, 0.05f, h * 2.0f);
            st->mState = 2;
            st->mFlag1c = false;
            return true;
        }
        if (bundle->FUN_00cee330()) {
            st->mState = 0x12;
            return true;
        }
        if (!st->mFlag1d)
            goto fail;
        {
            VecRange* spots = c->GetTribe()->FUN_00c97020();
            Vec3* first = spots->begin;
            if (first == spots->end)
                goto fail;
            Vec3 pos;
            PlanetModel()->DirectionToSurfacePosition(&pos, first);
            float twiceR = loco->GetRadius() + loco->GetRadius();
            const Vec3* me = loco->GetPosition();
            float dx = me->x - pos.x;
            float dz = me->z - pos.z;
            float dy = me->y - pos.y;
            if ((dx * dx + dz * dz) + dy * dy < 4.0f) {
                Vec3 tmp;
                const Vec3* v = c->GetTribe()->FUN_00c91190(&tmp, 1);
                pos.x = v->x;
                pos.y = v->y;
                pos.z = v->z;
                char* t260 = *(char**)((char*)c->GetTribe() + 0x260);
                if (t260)
                    twiceR = ((Spatial*)(*(char**)((char*)c->GetTribe() + 0x260) + 0x34))->GetRadius() + twiceR;
                if (!loco->vf48() && !loco->vf58()) {
                    ReleaseRef(st->mpTarget);
                    if (c->HasSpecializedTool(7)) {
                        st->mTimer = GetPropertyFloat(g_pProps, 0x98fbef73, 2.0f);
                        st->mState = 6;
                        return true;
                    }
                    st->mTimer = GetPropertyFloat(g_pProps, 0x6da643bd, 1.0f);
                    st->mState = 6;
                    return true;
                }
            }
            c->MoveToPointAtSpeed(2, &pos, twiceR, 2.0f);
            st->mState = 1;
            return true;
        }
    }
    case 1: {
        Spatial* bundle = BundleOf(c);
        char* cc = (char*)c;
        if (!bundle->FUN_00cee330() || *(int*)(cc + 0xfc8) != *(int*)(cc + 0xfc4)) {
            if (!c->FUN_00c26c90(0x30000, 0))
                return true;
        }
        if (LocoOf(c)->IsNearGoal())
            goto state0;
        if (!st->mFlag1d)
            return true;
        if (FUN_00af13b0()->FUN_00af0bd0(c, 4, 0))
            return true;
        goto fail;
    }
    case 2: {
        Spatial* bundle = BundleOf(c);
        if (!(((bundle->FUN_00cee330() != 0) && c->FUN_00c22850() == 1) || c->FUN_00c26c90(0x30000, 0)))
            return true;
        if (!LocoOf(c)->IsNearGoal())
            return true;
        int effect = c->GetToolEffect(7);
        if (c->FUN_00c22a70() != effect) {
            if (c->HasSpecializedTool(7)) {
                if (c->FUN_00c22850() == 1)
                    c->FUN_00c234a0(g_v169ef8c);
                st->mState = 2;
                return true;
            }
            bool r = FUN_00d75870(c, st->mpResource);
            st->mState = (r == 0) * 4 + 3;
            return true;
        }
        {
            bool leader = c->IsLeader();
            unsigned anim = (leader ? 0x299bd0a : 0) + 0x2df4b12;
            char* obj = (char*)st->mpResource;
            if (!obj) {
                c->PlayAnimation(anim, 1, -1);
                st->mState = 0xb;
                return true;
            }
            float scale = *(float*)(obj + 0x6c) * 2.0f;
            const Vec3* op = (const Vec3*)(obj + 0x10);
            Vec3 nTmp;
            const Vec3* n = normalized_safe(&nTmp, op);
            Vec3 target;
            target.x = n->x * scale + op->x;
            target.y = op->y + n->y * scale;
            target.z = op->z + n->z * scale;
            c->PlayAnimationWithTarget(anim, &target, -1);
            st->mState = 0xb;
            return true;
        }
    }
    case 3: {
        Vec3 v = g_v169ef40;
        if (st->mpResource)
            st->mpResource->GetSpotPosition(&v, st->mSpotIndex);
        if (!FUN_0041dd30(&v, &g_v169ef40))
            c->PlayAnimation(0x2df4b0a, 1, -1);
        else
            c->PlayAnimationWithTarget(0x2df4b0a, &v, -1);
        st->mState = 4;
        return true;
    }
    case 4: {
        if (c->GetCurrentAnimationGUID() == 0x2df4b0a) {
            if (st->mpResource) {
                Vec3 tmp;
                st->mpResource->GetSpotPosition(&tmp, st->mSpotIndex);
                c->FUN_00c0d1e0(&tmp);
            } else {
                c->IsAnimationQueuedOrCurrent();
            }
        }
        unsigned t = (unsigned)-1;
        if (!c->WaitForAnimEventOrEnd(0xbf775c1f, &t, -1, 0, 1))
            return true;
        c->IsAnimationQueuedOrCurrent();
        if (t != (unsigned)-1 && !st->mFlag1c) {
            st->mFlag1c = true;
            FUN_00b3d440()->FUN_00b09b80(st->mpResource, st->mSpotIndex, 0);
            c->CreateBodyEffect(t, 0xae024c94, 0x2735294);
            st->mTimer = GetPropertyFloat(g_pProps, 0x6da643bd, 1.0f);
        }
        goto state5;
    }
    case 5:
        if (!c->AnimationFinished(0))
            return true;
        if (g_f1687a14 > c->FUN_00c0b9c0() && st->mTimer > 0.01f)
            goto state17;
        goto doDrop;
    case 6: {
        if (!c->AnimationFinished(0))
            return true;
        if (c->FUN_00c0dfd0(0x2735294))
            c->FUN_00c15150(0x2735294, 1);
        void* bundlePtr = c ? (void*)BundleOf(c) : (void*)0;
        FUN_00b3d2b0()->FUN_00ac7ab0(st->mTimer, bundlePtr, 1);
        st->mTimer = 0.0f;
        if (BundleOf(c)->FUN_00cee330())
            c->FUN_00c22860(1);
        goto state0;
    }
    case 7: {
        st->mCount++;
        Vec3 tmp;
        st->mpResource->GetSpotPosition(&tmp, st->mSpotIndex);
        c->PlayAnimationWithTarget(0x2df4b10, &tmp, -1);
        st->mState = 8;
        return true;
    }
    case 8:
        if (!c->AnimationFinished(0))
            return true;
        FUN_00d754b0(c, st, 0);
        st->mState = 0;
        return true;
    case 0xb: {
        Spatial* bundle = BundleOf(c);
        if (bundle->FUN_00cee330() && c->FUN_00c22850() == 1)
            c->FUN_00c234a0(g_v169ef8c);
        unsigned t = (unsigned)-1;
        if (!c->WaitForAnimEventOrEnd(0x428ae400, &t, -1, 0, 1))
            return true;
        int effect = c->GetToolEffect(7);
        if (c->FUN_00c22a70() == effect) {
            FUN_00b3d440()->FUN_00b09b80(st->mpResource, st->mSpotIndex, 0);
            char* res = (char*)st->mpResource;
            int n = (int)(float)(int)g_map15812a4.operator_idx(*(unsigned*)(res + 0x58)) - 1;
            unsigned long long mask = *(unsigned long long*)(res + 0x48);
            unsigned lim = (unsigned)(mask >> 32);
            unsigned i = 0;
            if (lim != 0) {
                do {
                    if (n < 1)
                        break;
                    char* r2 = (char*)st->mpResource;
                    unsigned long long m2 = *(unsigned long long*)(r2 + 0x48);
                    if (((1ULL << i) & m2) != 0) {
                        FUN_00b3d440()->FUN_00b09b80(r2, i, 0);
                        n--;
                    }
                    i++;
                } while (i < lim);
            }
        }
        st->mState = 0xc;
        return true;
    }
    case 0xc: {
        if (!st->mFlag1c) {
            unsigned t;
            if (c->WaitForAnimEventOrEnd(0xbf775c1f, &t, -1, 0, 1)) {
                st->mFlag1c = true;
                float cnt = (float)(int)g_map15812a4.operator_idx(*(unsigned*)((char*)st->mpResource + 0x58));
                float prop = GetPropertyFloat(g_pProps, 0x98fbef73, 2.0f);
                Spatial* bundle = BundleOf(c);
                float cap = bundle->GetBundleValue(1);
                float diff = cap - bundle->FUN_00cee380();
                float prod = prop * cnt;
                float amount = (prod > diff) ? diff : prod;
                if (bundle->FUN_00cee330()) {
                    FUN_00b3d2b0()->FUN_00ac7ab0(amount, bundle, 1);
                } else {
                    Spatial* loco = LocoOf(c);
                    Vec3 offTmp;
                    Vec3 off = *loco->GetOffset(&offTmp);
                    const Vec3* pos = loco->GetPosition();
                    Vec3 sum;
                    sum.x = pos->x + off.x;
                    sum.y = pos->y + off.y;
                    sum.z = pos->z + off.z;
                    Mgr1* mgr = FUN_00b3d2b0();
                    char* obj = mgr->FUN_00ac7ab0(amount, mgr->FUN_00ac79d0(), 1);
                    *(int*)(obj + 0x130) = 1;
                    *(bool*)(obj + 0x124) = true;
                    ((Positionable*)(obj + 0x34))->SetPosition(&sum);
                    (*(Attacher**)(obj + 0x128))->Attach(obj);
                    ((RefPtr*)(obj + 0x120))->Assign(c);
                    ((RefPtr*)&st->mpEffect)->Assign(obj);
                }
            }
        }
        if (c->AnimationFinished(0) && st->mFlag1c) {
            st->mState = 0xd;
            return true;
        }
        return true;
    }
    case 0xd:
        if (c->FUN_00c25530(1)) {
            st->mState = 0xe;
            return true;
        }
        return true;
    case 0xe:
        if (c->FUN_00c25a50(st->mpEffect)) {
            char* eff = st->mpEffect;
            if (eff)
                ReleaseRef(*(IRefObj**)(eff + 0x120));
            IRefObj* e = (IRefObj*)st->mpEffect;
            if (e) {
                st->mpEffect = 0;
                e->Release();
            }
            st->mState = 0;
            return true;
        }
        return true;
    case 0xf: {
        if (!st->mpTarget)
            return false;
        const Vec3* pos = ((Spatial*)((char*)st->mpTarget + 0x34))->GetPosition();
        Spatial* loco = LocoOf(c);
        float a = loco->GetRadius() * 1.5f;
        float b = loco->GetRadius();
        c->MoveToPointAtSpeed(2, pos, b, a);
        st->mState = 0x10;
        return true;
    }
    case 0x10: {
        if (!LocoOf(c)->IsNearGoal())
            return true;
        if (!st->mpTarget)
            goto state0;
        c->PlayAnimationWithTarget(0x2796b31, ((Spatial*)((char*)st->mpTarget + 0x34))->GetPosition(), -1);
        st->mState = 0x11;
        return true;
    }
    case 0x11: {
        if (!c->FUN_00c0dfd0(0x2735294)) {
            unsigned t;
            if (c->WaitForAnimEventOrEnd(0xbfa50b5a, &t, -1, 0, 1)) {
                st->mpTarget->FUN_00b00080(5, 1);
                c->CreateBodyEffect(t, 0xae024c94, 0x2735294);
                st->mTimer = GetPropertyFloat(g_pProps, 0x6da643bd, 1.0f);
            }
        }
        if (!c->AnimationFinished(0))
            return true;
        goto doDrop;
    }
    case 0x12:
        st->mState = 0x13;
        return true;
    case 0x13: {
        int spot = FUN_00dba630(c, 0xd);
        st->mFoundSpot = spot;
        if (spot != -1) {
            st->mState = 0x14;
            return true;
        }
        return true;
    }
    case 0x14: {
        if (!LocoOf(c)->IsNearGoal())
            return true;
        char* cc = (char*)c;
        void* other = *(void**)(cc + 0xfc8);
        char* owner = BundleOf(c)->FUN_00cee330();
        unsigned* found = c->FUN_00c0fa10(owner ? owner + 0x34 : (char*)0, 0);
        if (found)
            other = (void*)*found;
        char* t260 = *(char**)((char*)tribe + 0x260);
        c->PlayAnimationWithTarget2(0x4ffb325, t260 ? t260 + 0x34 : (char*)0, -1, other);
        st->mState = 0x15;
        return true;
    }
    case 0x15: {
        unsigned t = (unsigned)-1;
        if (!c->WaitForAnimEventOrEnd(0xbfa50b5a, &t, -1, 0, 1))
            return true;
        char* owner = BundleOf(c)->FUN_00cee330();
        if (owner) {
            if (LocoOf(c)->vf58()) {
                float amt = *(float*)(owner + 0x134);
                cTribe* tr = c->GetTribe();
                int tribeVal = *(int*)((char*)tr + 0x234);
                Vec3 zeroA = { 0.0f, 0.0f, 0.0f };
                Vec3 zeroB = { 0.0f, 0.0f, 0.0f };
                int amtInt = (int)amt;
                char* hub = c->GetTribe()->FUN_00c8e820(0);
                FUN_00e398e0(0x5e9a7fcf, hub + 0x504, &zeroB, &zeroA, tribeVal, 0, amtInt);
            }
            tribe->FUN_00c94b50(*(float*)(owner + 0x134));
            st->mAccum = *(float*)(owner + 0x134) + st->mAccum;
            c->FUN_00c22860(1);
            c->FUN_00c227f0(g_v169ef40);
            c->FUN_00c22870();
            FUN_00b3d2b0()->FUN_00ac7eb0(owner, (char*)tribe + 0x20c);
        }
        st->mState = 0x16;
        return true;
    }
    case 0x16: {
        if (!c->AnimationFinished(0))
            return true;
        tribe->FindSpot(0xd, st->mFoundSpot);
        if (LocoOf(c)->vf58() && g_f1687a10 <= ((CombatantPart*)((char*)c + 0x5a8))->FUN_00bfc490() * 100.0f) {
            if (!st->mFlag1d)
                goto state0;
            if (FUN_00af13b0()->FUN_00af0bd0(c, 4, 0)) {
                st->mState = 0;
                return true;
            }
        }
        goto fail;
    }
    case 0x17: {
        float v = c->FUN_00c0b9c0();
        if (v <= g_f1687a14 && 0.01f < st->mTimer) {
            st->mState = 0x18;
            return true;
        }
        if (st->mTimer < 0.01f || c->HasSpecializedTool(7)) {
            st->mTimer = 0.0f;
            st->mState = 0;
            return true;
        }
        goto state5;
    }
    case 0x18:
        if (!c->AnimationFinished(0))
            return true;
        c->PlayAnimation(0x2796b38, 1, -1);
        st->mState = 0x19;
        return true;
    case 0x19: {
        if (!c->AnimationFinished(0))
            return true;
        float g = g_f1581298;
        float* pf = &st->mTimer;
        float* pick = (g > st->mTimer) ? pf : &g;
        float m = *pick;
        c->FUN_00c0b9d0((float)(g * g_f158129c + c->FUN_00c0b9c0()));
        ((CombatantPart*)((char*)c + 0x5a8))->PartialRepair(g * g_f15812a0);
        float f = *pf - m;
        *pf = f;
        if (0.01f > f) {
            *pf = 0.0f;
            c->FUN_00c15150(0x2735294, 1);
        }
        goto state17;
    }
    default:
        return true;
    }
fail:
    FUN_00da6270(c, 2);
    return false;
state0:
    st->mState = 0;
    return true;
state5:
    st->mState = 5;
    return true;
state17:
    st->mState = 0x17;
    return true;
doDrop:
    FUN_00d75700(c, st);
    st->mState = 6;
    return true;
}
