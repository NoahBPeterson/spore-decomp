// src/game/SPGonzago/SPTribeGameBehaviorGather.cpp -- migrated from slice(s) s00d76000, s00d75400 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPTribeGameBehaviorGather.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPCreatureCitizen.h"
#include "SP/cModelWorld.h"
#include "SP/cPlanetModel.h"
#include "SP/cSpatialObject.h"
#include "SP/cCombatant.h"
#include "SP/cLocomotiveObject.h"
#include "SP/cTribe.h"

// unnamed retail callees and globals (address in the comment)
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
extern void*      g_pTreeQueryCtx;  // 0x0158427c
extern "C" double __cdecl sqrt(double x);
#pragma intrinsic(sqrt)

// ---- items of slice s00d75400 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV(n) virtual void pv##n();
class IWin;
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
cTreeQuery*  FUN_00b3d440(float* pos, float radius,
                          void** a, void** b);               // 0x00b3d440
cTreeQuery*  FUN_00b3d440_8(void* a, void* b, void* c, void* d,
                            void* e, void* f, void* g, void* h);
cPlanetModel* PlanetModel(float* out, float* in);            // 0x00b3d350
cPlanetModel* PlanetModel3(float* out, float* in, float d);  // 0x00b3d350
double       GetPropFloat(IWin* mgr, uint32_t id, float def); // 0x004e1c70
class cSimLoco : public IWin {
};
class cSimLocoTick {
 public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20)
    PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28)
    virtual double pv29t(float scale);                       // +0x74
};
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
// ---- items of slice s00d75400 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern IWin*      g_pPropertyMgr;   // 0x0158128c

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void SP_BindFruitNode(cGameObject* a1, FruitState* a2, cGameObject* a3);  // 0x00d754b0 (stays in the slice: not this object's)

// ---- items of slice s00d76000 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_pProps;        // 0x158128C
extern float g_f1581298;      // 0x1581298
extern float g_f158129c;      // 0x158129C
extern float g_f15812a0;      // 0x15812A0
extern float g_f1687a10;      // 0x1687A10
extern float g_f1687a14;      // 0x1687A14
struct Vec3 { float x, y, z; };
#define V4(a) virtual void a##0(); virtual void a##1(); virtual void a##2(); virtual void a##3();
struct IRefObj { virtual void v0(); virtual void Release(); void __thiscall FUN_00b00080(int a, int b); };  // ret 8      // slot at +4
struct Spatial {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
    virtual const Vec3* GetPosition();                 // +0x2c
virtual void v12();
virtual void v13();
    virtual float GetBundleValue(int which);           // +0x38
virtual void v15();
virtual void v16();
virtual void v17();
    virtual bool vf48();                               // +0x48
virtual void v19();
virtual void v20();
virtual void v21();
    virtual bool vf58();                               // +0x58
    virtual const Vec3* GetOffset(Vec3* out);          // +0x5c
virtual void v24();
virtual void v25();
virtual void v26();
virtual void v27();
virtual void v28();
    virtual float GetRadius();                         // +0x74
    bool __thiscall IsNearGoal();                      // 0xC42E20 (SP::cLocomotiveObject::IsNearGoal)
    // 0xCEE330 / 0xCEE380: queries on the creature's bundle container (at +0x34)
    char* __thiscall FUN_00cee330();
    float __thiscall FUN_00cee380();
};
struct VecRange { Vec3* begin; Vec3* end; };
struct cTribe_s00d7_6000 {
    V4(a) V4(b) V4(c) V4(d) V4(e) V4(f) V4(g) V4(h) V4(i) V4(j)
virtual void k0();
virtual void k1();
virtual void k2();
    virtual void TickHook();                                         // +0xAC
    VecRange* __thiscall FUN_00c97020();
    Vec3* __thiscall FUN_00c91190(Vec3* out, int a);                  // ret 8
    void __thiscall FUN_00c94b50(float v);                            // ret 4
    char* __thiscall FUN_00c8e820(int a);                             // ret 4
    void __thiscall FindSpot(int a, int b);                           // 0xC98750, ret 8
};
struct ResourceNode {
    void __thiscall GetSpotPosition(Vec3* out, int idx);          // 0xB02B90
};
struct Positionable {   // sub-object at +0x34 of the spawned effect; slot +0x38
V4(a) V4(b) V4(c) virtual void d0();
virtual void d1();
    virtual void SetPosition(const Vec3* p);
};
struct Attacher { V4(a) V4(b) V4(c) virtual void Attach(void* obj); };  // slot +0x30
struct RefPtr {
    IRefObj* mp;
    void __thiscall Assign(void* p);  // 0x00b5f950
};
struct Mgr1 {  // returned by 0xB3D2B0
    void* __thiscall FUN_00ac79d0();
    char* __thiscall FUN_00ac7ab0(float amount, void* what, int n);   // ret 0xC
    void  __thiscall FUN_00ac7eb0(void* a, void* b);                  // ret 8
};
struct Mgr2 {  // returned by 0xB3D440
    void __thiscall FUN_00b09b80(void* node, int idx, int zero);      // ret 0xC
};
namespace SP {
 class cSPCreatureCitizen_s00d7_6000; 
}
struct Mgr3 {  // returned by 0xAF13B0
    bool __thiscall FUN_00af0bd0(SP::cSPCreatureCitizen_s00d7_6000* c, int a, int b); // ret 0xC
};
struct cPlanetModel_s00d7_6000 {
    Vec3* __thiscall DirectionToSurfacePosition(Vec3* out, const Vec3* dir);  // 0xB815A0
};
struct UIntMap {
    unsigned& __thiscall operator_idx(const unsigned& key);  // 0x00643a40
};
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
class cSPCreatureCitizen_s00d7_6000 { public:
    cTribe_s00d7_6000* __thiscall GetTribe();                                     // 0xC22F50
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
}
namespace SP {
bool __cdecl TRIBE_GATHER_Tick(cSPCreatureCitizen_s00d7_6000* c, int p2, int p3, unsigned p4, unsigned p5,
                               TribeGatherState* st, int p7, float p8);
}
namespace SP {
cPlanetModel_s00d7_6000* __cdecl PlanetModel();                 // 0xB3D350
}
namespace SP {
Vec3* __cdecl normalized_safe(Vec3* out, const Vec3* in);   // 0x449C20
}
struct CombatantPart {  // at c+0x5a8
    float __thiscall FUN_00bfc490();
    void __thiscall PartialRepair(float v);  // 0x00bfd1a0
};
Mgr1* __cdecl FUN_00b3d2b0();
Mgr2* __cdecl FUN_00b3d440();
Mgr3* __cdecl FUN_00af13b0();
unsigned __cdecl FUN_00ac8fa0(void* props, unsigned id, int n);
float __cdecl GetPropertyFloat(void* props, unsigned id, float def);   // 0x004e1c70 SP::GetPropertyT<float>
bool __cdecl FUN_0041dd30(const Vec3* a, const Vec3* b);
void __cdecl FUN_00da6270(SP::cSPCreatureCitizen_s00d7_6000* c, int a);
bool __cdecl FUN_00d75f40(SP::cSPCreatureCitizen_s00d7_6000* c, TribeGatherState* st);
void __cdecl FUN_00d75700(SP::cSPCreatureCitizen_s00d7_6000* c, TribeGatherState* st);
void __cdecl FUN_00d754b0(SP::cSPCreatureCitizen_s00d7_6000* c, TribeGatherState* st, int a);
bool __cdecl FUN_00d75870(SP::cSPCreatureCitizen_s00d7_6000* c, ResourceNode* r);
int  __cdecl FUN_00dba630(SP::cSPCreatureCitizen_s00d7_6000* c, int a);
void __cdecl FUN_00e398e0(unsigned id, void* a, void* b, void* d, int e, int f, int g);
extern UIntMap g_map15812a4;  // 0x15812A4
extern Vec3 g_v169ef40;       // 0x169EF40
extern Vec3 g_v169ef8c;       // 0x169EF8C
static inline Spatial* BundleOf(SP::cSPCreatureCitizen_s00d7_6000* c) { return (Spatial*)((char*)c + 0x34); }
static inline Spatial* LocoOf(SP::cSPCreatureCitizen_s00d7_6000* c)   { return (Spatial*)((char*)c + 0xc0); }
static inline void ReleaseRef(IRefObj*& r) { IRefObj* p = r; if (p) { r = 0; p->Release(); } }
// ---- items of slice s00d76000 end

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
Vector3* SP_UpdateFruitTarget(Vector3* out, cGameObject* a1, FruitState* a2, float* f4)
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
char SP_TryStartFruitRun(cGameObject* a1, void* a2, void* a3, void* a4, void* a5, FruitState* a6, cFruitRequest* a7)
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

// @ 0x00d76000
bool __cdecl SP::TRIBE_GATHER_Tick(SP::cSPCreatureCitizen_s00d7_6000* c, int p2, int p3, unsigned p4, unsigned p5, TribeGatherState* st, int p7, float p8)
{
    (void)p2; (void)p3; (void)p4; (void)p5; (void)p7; (void)p8;
    cTribe_s00d7_6000* tribe = c->GetTribe();
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
            cPlanetModel_s00d7_6000* pm = SP::PlanetModel();
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
            Vec3 n = *SP::normalized_safe(&nTmp, &d);
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
            SP::PlanetModel()->DirectionToSurfacePosition(&pos, first);
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
            const Vec3* n = SP::normalized_safe(&nTmp, op);
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
                cTribe_s00d7_6000* tr = c->GetTribe();
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
