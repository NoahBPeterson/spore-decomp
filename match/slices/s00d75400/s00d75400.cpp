// Slice s00d75400.
//
// "Pick a fruit off a tree": the target-selection helpers of the tribe
// citizen/fish behaviour plus the small intrusive-pointer state block they
// share.
//
//   00d75400  SP::cTribeGameBehaviorFish::CalledByStimulus
//   00d75450  FruitState::~FruitState
//   00d754b0  SP_BindFruitNode
//   00d755b0  SP_PickFruitAndMove
//   00d75700  SP_DropFruitTarget
//   00d75740  SP_NearestFruitIndex
//   00d75870  SP::CanReachFruit
//   00d759a0  SP_UpdateFruitTarget
//   00d75b10  SP_TryStartFruitRun
//   00d75c40  SP_PickNearbyFruitTree
//   00d75e00  SP_GetClosestGroundFruit
//   00d75f40  SP::PickFruitTarget
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"

#define PV(n) virtual void pv##n();

class IWin;

// --- globals ---------------------------------------------------------------
extern const float kZeroX;          // 0x0169ef40
extern const float kZeroY;          // 0x0169ef44
extern const float kZeroZ;          // 0x0169ef48
extern const float kZeroF;          // 0x01485378
extern const float kFloatMax;       // 0x0147bef4
extern const float kTwo;            // 0x01470f1c
extern const float kTwoB;           // 0x0146a308
extern const float kTen;            // 0x01473c70
extern const float kThirty;         // 0x014853bc
extern const float kFive;           // 0x01486110
extern const float kSqrtEps;        // 0x013ec4b8  (1e-08)
extern const float kGroundSearch;   // 0x015d9c6c
extern IWin*      g_pPropertyMgr;   // 0x0158128c
extern void*      g_pTreeQueryCtx;  // 0x0158427c

struct Vector3 { float x, y, z; };

class cGameObject;
class cObject;

void operator delete[](void* p);    // 0x00f47380

extern "C" double __cdecl sqrt(double x);
#pragma intrinsic(sqrt)

// ---------------------------------------------------------------------------
// UTFWin style COM object.  Only the vtable slots this slice reaches are
// named; the rest are placeholders so the offsets line up.
// ---------------------------------------------------------------------------
class IWin {
 public:
    virtual void AddRef();                                   // +0x00
    virtual void Release();                                  // +0x04
    PV(2)
    virtual cGameObject* pv03(uint32_t id);                  // +0x0c
    PV(4) PV(5) PV(6) PV(7) PV(8)
    virtual char pv09(uint32_t id, void** out);              // +0x24
    PV(10)
    virtual float* pv11();                                   // +0x2c
    PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21)
    virtual char pv22();                                     // +0x58
    PV(23) PV(24) PV(25)
    virtual void* pv26();                                    // +0x68
    PV(27) PV(28)
    virtual double pv29();                                   // +0x74
};

// EA::AutoRefCount<...>::operator= for the instantiation whose body lives in
// another object file, so assignments through it stay real calls (0x00b5f950).
// Its inlined forms are written out explicitly at each site below.
class RefText {
 public:
    RefText& operator=(IWin* p);                             // 0x00b5f950

    IWin* mpRef;                                             // +0x00
};

static void RefClear(IWin** pp)
{
    IWin* p = *pp;
    if (p != 0)
    {
        *pp = 0;
        p->Release();
    }
}

static void RefAssign(IWin** pp, IWin* p)
{
    IWin* old = *pp;
    if (p != old)
    {
        if (p != 0)
            p->AddRef();
        *pp = p;
        if (old != 0)
            old->Release();
    }
}

static void RefRelease(IWin** pp)
{
    if (*pp != 0)
        (*pp)->Release();
}

// ---------------------------------------------------------------------------
// Small engine objects reached through the creature.
// ---------------------------------------------------------------------------
class cPlanetMgr {                                           // creature->mB20
 public:
    uint8_t pad00[0x590];
    float   mField590;                                       // +0x590
};

class cAnimObj {                                             // mLoco_c0.pv26()
 public:
    uint8_t pad00[8];
    float   mLow_08;                                         // +0x08
    uint8_t pad0c[8];
    float   mHigh_14;                                        // +0x14
};

class cSubQuery {                                            // creature->mSub5c
 public:
    PV(0)
};

class cFruitRequest {                                        // SP_TryStartFruitRun arg 7
 public:
    uint8_t  pad00[0x18];
    uint32_t mFlag_18;                                       // +0x18
};

class cSpatialObject : public IWin {                         // creature->mSpatial34
 public:
    void*  FUN_00cee330();                                   // 0x00cee330
    double FUN_00cee380();                                   // 0x00cee380
};

class cOrderRecord;

class cAgentOrderManager {                                   // creature->mB4c
 public:
    cOrderRecord* FirstPending();                            // 0x00bca2c0
};

struct cOrderRecord {
    uint32_t mType00;                                        // +0x00
    uint8_t  pad04[0x0c];
    Vector3  mPos10;                                         // +0x10
    uint8_t  pad1c[0x0c];
    IWin*    mpOwner28;                                      // +0x28
    float    mX2c;                                           // +0x2c
    float    mY30;                                           // +0x30
    float    mZ34;                                           // +0x34
    uint8_t  pad38[0x34];
    float    mField6c;                                       // +0x6c
};

class cTargetInfo {                                          // pv09(0x2ffd8df3)
 public:
    union {
        float* mpFloat00;                                    // +0x00 (dereferenced)
        float  mValue00;                                     // +0x00 (read as a float)
    };
    uint8_t  pad04[0x0c];
    uint8_t  mFlags10;                                       // +0x10
    uint8_t  pad11;
    uint16_t mKind12;                                        // +0x12
};

class cSpecies;
class cModelWorld;
class cSpeciesMgr  { public: cSpecies* FUN_00b90410(); };    // 0x00b90410
class cSpecies     { public: cModelWorld* GetModelWorld(); };// 0x00ad2830
class cModelWorld  { public: uint32_t FUN_004d9070(); };     // 0x004d9070

class cObject {                                              // generic engine handle
 public:
    void         FUN_00ac79e0(void* p);                      // 0x00ac79e0
    void         FindSpot();                                 // 0x00c98750
    void         FUN_00c97d40();                             // 0x00c97d40
    void         FUN_00c97020();                             // 0x00c97020
};

class cTreeQuery {
 public:
    void FUN_00b06bd0(float radius, void** out);             // 0x00b06bd0
    void FUN_00b0a0c0(void** out, void* buf, void* ctx, float d,
                      int a, int b, int c);                  // 0x00b0a0c0
};

class cPlanetModel {
 public:
    void* DirectionToSurfacePosition(float* out, float* in); // 0x00b815a0
};

void*        FUN_00b3d420(void* p);                          // 0x00b3d420
cObject*     FUN_00b3d2b0(void* a, void* b);                 // 0x00b3d2b0
cTreeQuery*  FUN_00b3d440(float* pos, float radius,
                          void** a, void** b);               // 0x00b3d440
cTreeQuery*  FUN_00b3d440_8(void* a, void* b, void* c, void* d,
                            void* e, void* f, void* g, void* h);
cPlanetModel* PlanetModel(float* out, float* in);            // 0x00b3d350
cPlanetModel* PlanetModel3(float* out, float* in, float d);  // 0x00b3d350
double       GetPropFloat(IWin* mgr, uint32_t id, float def); // 0x004e1c70

// The +0xc0 locomotion object (slot layout shared by this cluster).
class cSimLoco : public IWin {
};

// The same +0xc0 object as reached from 00d75b10, whose vtable slot 29 takes
// the tick scale; 00d759a0 reaches a creature whose slot 29 takes no argument,
// hence the second view of the same object.
class cSimLocoTick {
 public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20)
    PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28)
    virtual double pv29t(float scale);                       // +0x74
};

// ---------------------------------------------------------------------------
// The creature (and the fruit tree it harvests from) -- one layout.
// ---------------------------------------------------------------------------
class cGameObject : public IWin {
 public:
    void           FUN_00c25f80();                           // 0x00c25f80
    char           FUN_00c22850();                           // 0x00c22850
    void           FUN_00c22860(int a);                      // 0x00c22860
    void           FUN_00c227f0(Vector3 v);                  // 0x00c227f0
    void           FUN_00c15150(int a, int b);               // 0x00c15150
    void           FUN_00c14750(int a);                      // 0x00c14750
    void           PerformSocialAction(uint32_t a, int b);   // 0x00c23300
    cObject*       GetTribe(int a, void* b);                 // 0x00c22f50
    cObject*       GetTribe();                               // 0x00c22f50
    void           MoveToPointAtSpeed(int a, void* p);       // 0x00c1c1d0
    void           GetFruitPos(float* out, uint32_t index);  // 0x00b02b90
    double         GetFruitHeight();                         // 0x00aff240
    cGameObject*   FUN_00b058a0();                           // 0x00b058a0
    char           FUN_00c1ac70(float* pos, int kind, int a, int b,
                                int c, float d);             // 0x00c1ac70

    uint8_t        pad04[0x0c];                              // +0x04..+0x10
    Vector3        mPos10;                                   // +0x10
    uint8_t        pad1c[0x18];                              // +0x1c..+0x34
    cSpatialObject mSpatial34;                               // +0x34
    uint8_t        pad38[0x10];                              // +0x38..+0x48
    uint64_t       mMask48;                                  // +0x48
    uint8_t        pad50[0x08];                              // +0x50..+0x58
    RefText        mField58;                                 // +0x58
    cSubQuery      mSub5c;                                   // +0x5c
    uint8_t        pad60[0x08];                              // +0x60..+0x68
    RefText        m68;                                      // +0x68
    float          m6c;                                      // +0x6c
    uint8_t        pad70[0x0c];                              // +0x70..+0x7c
    uint8_t        m7c;                                      // +0x7c
    uint8_t        pad7d[0x43];                              // +0x7d..+0xc0
    cSimLoco       mLoco_c0;                                 // +0xc0
    uint8_t        padc4[0x44];                              // +0xc4..+0x108
    RefText        m108;                                     // +0x108
    uint8_t        pad10c[0x14];                             // +0x10c..+0x120
    RefText        m120;                                     // +0x120
    uint8_t        pad124[0x48];                             // +0x124..+0x16c
    uint32_t       m16c;                                     // +0x16c
    uint8_t        pad170[0x9b0];                            // +0x170..+0xb20
    cPlanetMgr*    mB20;                                     // +0xb20
    uint8_t        padb24[0x28];                             // +0xb24..+0xb4c
    cAgentOrderManager* mB4c;                                // +0xb4c
};

// ---------------------------------------------------------------------------
// Behaviour target block shared by the two selection helpers.
// ---------------------------------------------------------------------------
struct FruitState {
    uint32_t m00;                                            // +0x00
    RefText  m04;                                            // +0x04
    RefText  m08;                                            // +0x08
    uint32_t m0c;                                            // +0x0c
    float    m10;                                            // +0x10
    float    m14;                                            // +0x14
    void*    m18;                                            // +0x18
    uint8_t  m1c;                                            // +0x1c
    uint8_t  m1d;                                            // +0x1d
    uint8_t  pad1e[2];                                       // +0x1e
    uint32_t m20;                                            // +0x20
    RefText  m24;                                            // +0x24

    ~FruitState();                                           // 0x00d75450
};

class cTargetSlot {
 public:
    uint8_t pad00[0x28];
    uint8_t mFlag_28;                                        // +0x28
};

class cFishOwner {                                           // behaviour->+0x74
 public:
    cTargetSlot* FUN_00d73bc0(RefText** pp);                 // 0x00d73bc0
};

class cStimulus {
 public:
    uint8_t pad00[0x14];
    int32_t mKind_14;                                        // +0x14
};

class cTribeGameBehaviorFish : public IWin {
 public:
    void OnLayout(cGameObject* a, cStimulus* s);             // 0x00b267f0
    void CalledByStimulus(cGameObject* a, cStimulus* s);     // 0x00d75400

    uint8_t    pad04[0x70];                                  // +0x04..+0x74
    cFishOwner mObj74;                                       // +0x74
};

// @ 0x00d75400
void cTribeGameBehaviorFish::CalledByStimulus(cGameObject* a1, cStimulus* a2)
{
    OnLayout(a1, a2);

    if (a2 != 0 && a2->mKind_14 == 1)
    {
        RefText* target;
        if (a1 != 0)
            target = &a1->mField58;
        else
            target = 0;
        mObj74.FUN_00d73bc0(&target)->mFlag_28 = 1;
    }
}

// @ 0x00d75450
FruitState::~FruitState()
{
    // body: reset the two target slots (the inlined intrusive-pointer clear)
    RefClear(&m04.mpRef);
    RefClear(&m08.mpRef);
    // implicit member destructors, emitted in reverse declaration order
    RefRelease(&m24.mpRef);
    RefRelease(&m08.mpRef);
    RefRelease(&m04.mpRef);
}

// @ 0x00d754b0
void SP_BindFruitNode(cGameObject* a1, FruitState* a2, cGameObject* a3)
{
    if (a3 != 0 && a2->m08.mpRef == a3)
    {
        // the node is already bound: only fill in its vacant +0x68 slot
        cGameObject* t = (cGameObject*)a2->m08.mpRef;
        if (t->m68.mpRef == 0)
            t->m68 = a1;
    }
    else
    {
        cGameObject* t = (cGameObject*)a2->m08.mpRef;
        if (t != 0)
        {
            if (t->m68.mpRef == a1)
            {
                IWin* p = t->m68.mpRef;
                if (p != 0)
                {
                    t->m68.mpRef = 0;
                    p->Release();
                }
            }
            IWin* q = a2->m08.mpRef;
            if (q != 0)
            {
                a2->m08.mpRef = 0;
                q->Release();
            }
        }

        IWin* old = a2->m08.mpRef;
        if (a3 != old)
        {
            if (a3 != 0)
                a3->AddRef();
            a2->m08.mpRef = a3;
            if (old != 0)
                old->Release();
        }

        cGameObject* u = (cGameObject*)a2->m08.mpRef;
        if (u != 0)
            RefAssign(&u->m68.mpRef, a1);
    }

    // drop the tree held by the +0x04 slot, then the slot itself
    cGameObject* o = (cGameObject*)a2->m04.mpRef;
    if (o != 0)
    {
        IWin* r = o->m108.mpRef;
        if (r != 0)
        {
            o->m108.mpRef = 0;
            r->Release();
        }
    }
    IWin* s = a2->m04.mpRef;
    if (s != 0)
    {
        a2->m04.mpRef = 0;
        s->Release();
    }
}

// @ 0x00d755b0
void SP_PickFruitAndMove(cGameObject* a1, void* a2, void* a3, void* a4, void* a5,
                         FruitState* a6)
{
    // drop the previously bound fruit on the +0x24 slot
    cGameObject* p = (cGameObject*)a6->m24.mpRef;
    if (p != 0)
    {
        IWin* r = p->m120.mpRef;
        if (r != 0)
        {
            p->m120.mpRef = 0;
            r->Release();
        }
    }
    IWin* q = a6->m24.mpRef;
    if (q != 0)
    {
        a6->m24.mpRef = 0;
        q->Release();
    }

    a1->FUN_00c25f80();
    char b = a1->FUN_00c22850();
    a1->FUN_00c22860(1);

    Vector3 zero;
    zero.x = kZeroX;
    zero.y = kZeroY;
    zero.z = kZeroZ;
    a1->FUN_00c227f0(zero);

    a1->FUN_00c15150(0x2735294, 1);

    void* v = a1->mSpatial34.FUN_00cee330();
    if (v != 0)
    {
        double f = a1->mSpatial34.FUN_00cee380();
        if (f == 0.0)
        {
            cObject* o = FUN_00b3d2b0(v, a1 != 0 ? (void*)&a1->mSpatial34 : 0);
            o->FUN_00ac79e0(0);
        }
        else if (b == 0)
        {
            a1->PerformSocialAction((uint32_t)v, -1);
        }
    }

    cGameObject* t = (cGameObject*)a6->m04.mpRef;
    if (t != 0)
    {
        IWin* r2 = t->m108.mpRef;
        if (r2 != 0)
        {
            t->m108.mpRef = 0;
            r2->Release();
        }
    }

    SP_BindFruitNode(a1, a6, 0);
    a1->GetTribe(0xd, (void*)a6->m20)->FindSpot();
    a1->GetTribe(0xd, (void*)a1)->FUN_00c97d40();

    a6->~FruitState();
}

// @ 0x00d75700
void SP_DropFruitTarget(void* a1, FruitState* a2)
{
    cGameObject* o = (cGameObject*)a2->m04.mpRef;
    if (o != 0)
    {
        IWin* r = o->m108.mpRef;
        if (r != 0)
        {
            o->m108.mpRef = 0;
            r->Release();
        }
        IWin* s = a2->m04.mpRef;
        if (s != 0)
        {
            a2->m04.mpRef = 0;
            s->Release();
        }
    }
}

// @ 0x00d75740
uint32_t SP_NearestFruitIndex(cGameObject* a1, cGameObject* a2)
{
    uint32_t index = 0xffffffff;
    float    best  = kFloatMax;

    cSpeciesMgr* sm = (cSpeciesMgr*)FUN_00b3d420((void*)&a2->mSub5c);
    cSpecies*    sp = sm->FUN_00b90410();
    cModelWorld* mw = sp->GetModelWorld();
    uint32_t     n  = mw->FUN_004d9070();

    if (n == 0)
        return index;

    for (uint32_t i = 0; i < n; i++)
    {
        if ((((uint64_t)1 << i) & a2->mMask48) != 0)
        {
            Vector3 p;
            p.x = kZeroX;
            p.y = kZeroY;
            p.z = kZeroZ;
            a2->GetFruitPos((float*)&p, i);

            float* q = a1->mLoco_c0.pv11();
            float d = (q[2] - p.z) * (q[2] - p.z)
                    + (q[1] - p.y) * (q[1] - p.y)
                    + (q[0] - p.x) * (q[0] - p.x);
            if (d < best)
            {
                best  = d;
                index = i;
            }
        }
    }
    return index;
}

// @ 0x00d75870
uint32_t SP_CanReachFruit(cGameObject* a1, cGameObject* a2)
{
    Vector3 base;
    cPlanetModel* pm = PlanetModel((float*)&base, (float*)&a2->mPos10);
    pm->DirectionToSurfacePosition((float*)&base, (float*)&a2->mPos10);

    float h = (float)a2->GetFruitHeight();

    float inv = (float)(1.0 / sqrt((double)base.x * base.x + (double)base.y * base.y
                                 + (double)base.z * base.z + kSqrtEps));

    Vector3 target;
    target.x = (inv * base.x) * h + base.x;
    target.y = (base.y * inv) * h + base.y;
    target.z = (inv * base.z) * h + base.z;

    cAnimObj* o = (cAnimObj*)a1->mLoco_c0.pv26();
    int kind = (a1->mB20->mField590 == kZeroF) ? 2 : 0xb;

    if ((o->mHigh_14 - o->mLow_08) * kTwoB < h)
    {
        if (!a1->FUN_00c1ac70((float*)&target, kind, -1, 0, 0, kTwo))
            return 0;
    }
    return 1;
}

// @ 0x00d759a0
Vector3* SP_UpdateFruitTarget(Vector3* out, cGameObject* a1, FruitState* a2,
                              float* f4)
{
    out->x = kZeroX;
    out->y = kZeroY;
    out->z = kZeroZ;

    cOrderRecord* rec = a1->mB4c->FirstPending();
    if (rec == 0 || rec->mType00 != 2)
        return out;

    cGameObject* o1 = 0;
    cGameObject* o2 = 0;
    if (rec->mpOwner28 != 0)
        o1 = rec->mpOwner28->pv03(0x2c9cc8e);
    if (rec->mpOwner28 != 0)
        o2 = rec->mpOwner28->pv03(0x581147f);

    RefAssign(&a2->m08.mpRef, (IWin*)o2);
    RefClear(&a2->m04.mpRef);

    if (o1 != 0)
    {
        if (o1->m16c == 0)
            a2->m08 = (IWin*)o1->FUN_00b058a0();
        else
            a2->m04 = o1;
    }

    double v = a1->mLoco_c0.pv29();
    float  t = (float)(v + v);
    *f4 = t;

    if (o2 != 0)
    {
        out->x = o2->mPos10.x;
        out->y = o2->mPos10.y;
        out->z = o2->mPos10.z;
        *f4 = o2->m6c + t;
    }
    else if (o1 != 0)
    {
        float* p = o1->mSpatial34.pv11();
        out->x = p[0];
        out->y = p[1];
        out->z = p[2];
    }
    return out;
}

// @ 0x00d75b10
char SP_TryStartFruitRun(cGameObject* a1, void* a2, void* a3, void* a4, void* a5,
                         FruitState* a6, cFruitRequest* a7)
{
    if (a6 != 0)
    {
        a6->m00 = 0;
        a6->m04.mpRef = 0;
        a6->m08.mpRef = 0;
        a6->m0c = 0xffffffff;
        a6->m10 = kZeroX;
        a6->m14 = kZeroY;
        a6->m18 = 0;
        a6->m1c = 0;
        a6->m1d = 0;
        a6->m20 = 0xffffffff;
        a6->m24.mpRef = 0;
    }

    if (a7 != 0)
        a6->m1d = (a7->mFlag_18 != 0);

    a6->m00 = 0;
    a1->FUN_00c14750(0);

    if (!a1->mLoco_c0.pv22())
        return 1;

    float   h = 0.0f;
    Vector3 v;
    SP_UpdateFruitTarget(&v, a1, a6, &h);

    if (v.x != kZeroX || v.y != kZeroY || v.z != kZeroZ)
    {
        cSimLocoTick* loco = (cSimLocoTick*)&a1->mLoco_c0;
        float d = (float)loco->pv29t(kTwo) + h;

        Vector3 out;
        cPlanetModel* pm = PlanetModel3((float*)&out, (float*)&v, d);
        void* dir = pm->DirectionToSurfacePosition((float*)&out, (float*)&v);
        a1->MoveToPointAtSpeed(2, dir);
        a6->m00 = 1;
        return 1;
    }

    a1->GetTribe()->FUN_00c97020();
    return 1;
}

// @ 0x00d75c40
cGameObject* SP_PickNearbyFruitTree(cGameObject* a1, FruitState* a2)
{
    float dist;

    cTargetInfo* target = 0;
    char haveTarget = 0;
    if (g_pPropertyMgr != 0)
        haveTarget = g_pPropertyMgr->pv09(0x2ffd8df3u, (void**)&target);

    if (haveTarget && target != 0)
    {
        int kind = target->mKind12;
        if (kind == 0xd || kind == 0x10)
        {
            if ((target->mFlags10 & 0x30) != 0)
                dist = *target->mpFloat00;
            else if (kind != 0)
                dist = target->mValue00;
            else
                dist = 0.0f;
        }
        else
        {
            dist = kGroundSearch;
        }
    }
    else
    {
        dist = kTen;
    }

    cOrderRecord* rec = a1->mB4c->FirstPending();
    if (rec == 0 || rec->mType00 != 2)
        return 0;

    Vector3 pos;
    pos.x = rec->mX2c;
    pos.y = rec->mY30;
    pos.z = rec->mZ34;

    if (!a1->mLoco_c0.pv22())
        dist = (float)GetPropFloat(g_pPropertyMgr, 0x8c8f9f71u, kThirty);

    void* aStack[64];
    void** begin = aStack;
    void** end   = begin;

    cTreeQuery* q = FUN_00b3d440_8((void*)&pos, &dist, &end, &begin, 0, 0, 0, 0);
    q->FUN_00b0a0c0((void**)&begin, aStack, g_pTreeQueryCtx, dist, 1, 0, 1);

    if (begin == end)
    {
        if (begin != 0 && ((uint32_t*)begin)[-1] != 0)
            operator delete[](begin);
        return 0;
    }

    cGameObject* best = 0;
    for (void** it = begin; it != end; it++)
    {
        cGameObject* tr = (cGameObject*)*it;
        if (tr->m68.mpRef == 0)
        {
            if (best == 0)
                best = tr;
            if (SP_CanReachFruit(a1, tr))
                break;
        }
    }

    if (begin != 0 && ((uint32_t*)begin)[-1] != 0)
        operator delete[](begin);

    return best;
}

// @ 0x00d75e00
cGameObject* SP_GetClosestGroundFruit(cGameObject* a1, float radius)
{
    void* aStack[64];
    void** begin = aStack;
    void** end   = begin;

    cGameObject* best = 0;
    float bestDist = kFloatMax;

    float* pos = a1->mLoco_c0.pv11();
    cTreeQuery* q = FUN_00b3d440(pos, radius, (void**)&end, (void**)&begin);
    q->FUN_00b06bd0(radius, (void**)&begin);

    for (void** it = begin; it != end; it++)
    {
        cGameObject* o = (cGameObject*)*it;
        if (o->m108.mpRef == 0)
        {
            float* p1 = o->mSpatial34.pv11();
            float* p2 = a1->mLoco_c0.pv11();
            float d = (p2[2] - p1[2]) * (p2[2] - p1[2])
                    + (p2[1] - p1[1]) * (p2[1] - p1[1])
                    + (p2[0] - p1[0]) * (p2[0] - p1[0]);
            if (d < bestDist)
            {
                best     = o;
                bestDist = d;
            }
        }
    }

    for (void** it = begin; it < end; it++)
    {
        cGameObject* o = (cGameObject*)*it;
        if (o != 0)
            o->Release();
    }

    if (begin != 0 && ((uint32_t*)begin)[-1] != 0)
        operator delete[](begin);

    return best;
}

// @ 0x00d75f40
char SP_PickFruitTarget(cGameObject* a1, FruitState* a2)
{
    cGameObject* o = SP_GetClosestGroundFruit(a1, kFive);

    if (o != 0)
    {
        SP_BindFruitNode(a1, a2, 0);
        RefAssign(&a2->m04.mpRef, (IWin*)o);
        return 1;
    }

    cGameObject* t = (cGameObject*)a2->m08.mpRef;
    if (t == 0 || t->m7c != 0 || (uint32_t)t->mMask48 == 0
        || (t->m68.mpRef != 0 && t->m68.mpRef != a1))
    {
        SP_BindFruitNode(a1, a2, 0);
        t = SP_PickNearbyFruitTree(a1, a2);
        if (t == 0)
            return 0;
    }

    SP_BindFruitNode(a1, a2, t);
    a2->m0c = SP_NearestFruitIndex(a1, (cGameObject*)a2->m08.mpRef);
    return 1;
}