// Slice s00e91ce0 -- SP::cRotationRingView and SP::cSpatialObjectView helpers.
//
//  0x00e91ce0  SP::cRotationRingView::GetRingAnimationPercentage   (313 B, ret 4)
//  0x00e91e40  SP::cRotationRingView::HandleSimulationUpdate       (1386 B, ret 8)
//  0x00e923b0  SP::cRotationRingView::MakeView                     (619 B, ret 4)
//  0x00e92620  SP::cSpatialObjectView::SetIsInWorld                (50 B, ret 4)
//  0x00e92660  SP::cSpatialObjectView::~cSpatialObjectView         (110 B)
//  0x00e926d0  SP::cSpatialObjectView::SetModel_926d0              (106 B, ret 4)
//  0x00e92740  SP::cSpatialObjectView::MakeView_740                (463 B, ret 0x10)
//  0x00e92910  SP::cSpatialObjectView::Init                        (153 B, ret 4)
//  0x00e929b0  SP::cSpatialObjectView::SetModel                    (20 B)
//  0x00e929f0  SP::cSpatialObjectView::GetData                     (26 B)
//  0x00e92a10  SP::cSpatialObjectView::UpdateFadeState             (210 B)
//  0x00e92af0  SP::cSpatialObjectView::cSpatialObjectView          (83 B)
//  0x00e92b50  SP::cSpatialObjectView::MakeView                    (264 B, ret 4)
//  0x00e92c60  SP::cSpatialObjectView::GetIsInWorld                (23 B)
//  0x00e92c80  SP::cSpatialObjectView::GetIsVisible                (20 B)
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE (no /EHsc in this region).
#include "types.h"
#include <math.h>
#include <float.h>
#include <string.h>

// ---- basic types -----------------------------------------------------------
struct V3 { float x, y, z; };
struct Key { uint32_t mInstance, mType, mGroup; };
struct Matrix33 { float m[9]; };

// ---- property hashing ------------------------------------------------------
uint32_t __cdecl FNVHash(const char* s, uint32_t seed, int lowercase);   // 0x00932e80
uint32_t __cdecl SPIDFromName(const char* name);                        // 0x00571cf0
static inline uint32_t id(const char* s) { return FNVHash(s, 0x811c9dc5, 1); }

// GetPropertyT_DO_NOT_USE<float>(group, 0, prop, def)  -> float
float __cdecl GetPropertyF(uint32_t group, int a, uint32_t prop, float def);  // 0x00bcea30

// GetPropertyT_DO_NOT_USE<Vector3>(out, group, 0, prop, def) -> Vector3*
V3* __cdecl GetPropertyV3a(V3* out, uint32_t group, int a, uint32_t prop, V3 def); // 0x00e91410
V3* __cdecl GetPropertyV3b(V3* out, uint32_t group, int a, uint32_t prop, V3 def); // 0x00e914f0

// GetPropertyT_DO_NOT_USE<int>(group, 0, prop, def) -> int
int __cdecl GetPropertyI(uint32_t group, int a, uint32_t prop, int def);      // 0x00bda3b0

// EA allocator new: new("App", 0, 0, 0, 0) T(...)
void* __cdecl operator_new_sp(unsigned int size, const char* pName,
                              int a, int b, int c, int d);               // 0x00f473a0

// ---- global singletons -----------------------------------------------------
void* __cdecl GonzagoModelWorld();                                       // 0x00b3d520
void* __cdecl GetCurrentGameMode();                                      // 0x00b5b800

// ---- matrix / transform helpers -------------------------------------------
void  Matrix3Assign(void* dst, const void* src);                         // 0x0041cb40
void* Matrix3FromFacingAndUp(void* out, const void* facing, const void* up); // 0x0069b440
void* Mat3MulV3(void* out, const void* m, const void* v);                // 0x0059aed0
void* cSPTransformAssign(void* self, const void* src);                   // 0x00537dc0
void  FUN_00478db0(void* p);                                             // 0x00478db0

// ---- misc ------------------------------------------------------------------
void* FUN_00b3d310(void* p, int a);                                      // 0x00b3d310
void  FUN_00b48770(void* p, int a);                                      // 0x00b48770
void* FUN_00ae66d0(void* p);                                             // 0x00ae66d0
void* FUN_00efe5a0();                                                    // 0x00efe5a0
float __cdecl pow_f(double x, double y);                                 // 0x011e08f0

// retail constant addresses used verbatim by the original code
const float  f_1485720 = 1.0f;      // one
const float  f_13eb960 = 0.01f;
const float  f_13ec4b8 = 1e-08f;
const float  f_13f4fd0 = 0.0f;      // bias added to negative int->float
const float  f_13fe160 = 0.1f;
const float  f_147b9f0 = 30.0f;
const float  f_13ebc68 = 1.0f;

// default view colour (loaded with SSE in the original; extern float forces movss)
extern float g_defaultColorR;   // 0x15a89c0
extern float g_defaultColorG;   // 0x15a89c4
extern float g_defaultColorB;   // 0x15a89c8

// ===========================================================================
// cSpatialObject / cSpatialObjectView (layouts shared with slice s00e92ca0).
// ===========================================================================
struct cSpatialObject {
    char pad_00[0x50];
    uint32_t mFlags50;                       // +0x50
    char pad_54[0x70 - 0x54];
    Key mModelKey;                           // +0x70
    char pad_7c[0xc0 - 0x7c];

    void* GetDataRaw(uint32_t id);           // vtable +0xb8
};

class cSpatialObjectView {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24();
    virtual void* v28(void*);                // +0x28
    virtual void* GetModel();                // +0x2c
    virtual void* GetTransform();            // +0x30
    virtual float GetScale();                // +0x34
    virtual void  SetRotation(void*);        // +0x38
    virtual void  SetModelMatrix(void*);     // +0x3c
    virtual void  v40(); virtual void  v44(void*);
    virtual void  v48(int, int, int);
    virtual void  v4c(); virtual void  v50(); virtual void  v54();
    virtual void  v58(); virtual void  v5c(); virtual void  v60();
    virtual void  v64(void*, float);
    virtual void  v68(); virtual void  v6c(); virtual void  v70();
    virtual void  v74();
    virtual void* v78(void*);                // +0x78

    cSpatialObjectView();                    // 0x00e92af0
    ~cSpatialObjectView();                   // 0x00e92660

    uint32_t mField04;                       // +0x04
    uint32_t mField08;                       // +0x08
    cSpatialObject* mpObject;                // +0x0c
    void*    mpObjectCombatant;              // +0x10
    uint8_t  mField14;                       // +0x14
    char     pad_15[3];
    V3       mColor;                         // +0x18
    uint32_t mField24;                       // +0x24
    uint32_t mField28;                       // +0x28
    uint32_t mField2c;                       // +0x2c
    uint8_t  mbField30;                      // +0x30
    uint8_t  mbField31;                      // +0x31
    uint8_t  mbField32;                      // +0x32

    void  SetIsInWorld(bool b);              // 0x00e92620
    uint8_t GetIsInWorld();                  // 0x00e92c60
    uint8_t GetIsVisible();                  // 0x00e92c80
    void  SetModel_926d0(void* model);       // 0x00e926d0
    void  MakeView_740(void* a, void* b, void* c, void* d);  // 0x00e92740
    void  Init(void* gamedata);              // 0x00e92910
    void* SetModel();                        // 0x00e929b0
    void* GetData();                         // 0x00e929f0
    void  UpdateFadeState();                 // 0x00e92a10
};

// cRotationRing : cSpatialObject (base at +0x0).  Only used vtable slots named.
class cRotationRing {
public:
    virtual void v00(); virtual void v04();
    virtual void* v08(); virtual void* v0c();
    virtual void  v10(); virtual void  v14(); virtual void v18();
    virtual void  v1c(); virtual void  v20();
    virtual void  v24();
    virtual void  v28();
    virtual void  v2c();
    virtual void  v30();
    virtual void  v34();
    virtual void* v38();
    virtual void  v3c();
    virtual void  v40();
    virtual void  v44();
    virtual void  v48();
    virtual void  v4c();
    virtual void  v50();
    virtual void  v54();
    virtual void  v58(); virtual void  v5c();
    virtual void  v60();
    virtual void  v64();
    virtual void  v68();
    virtual void  v6c();
    virtual void* v70();
};

// The rotation-ring view (retail size 0x20).
class cRotationRingView {
public:
    virtual void v00(void*); virtual void v04(int);
    virtual cRotationRingView* MakeView(void* gamedata);   // +0x08
    virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1c();

    float GetRingAnimationPercentage(float param);   // 0x00e91ce0
    void  HandleSimulationUpdate(int a, int b);      // 0x00e91e40

    uint32_t mField04;                       // +0x04
    uint32_t mField08;                       // +0x08
    cRotationRing* mpObject;                 // +0x0c
    void*    mpGameDataView;                 // +0x10
    void*    mModel;                         // +0x14
    uint32_t mAnimID;                        // +0x18
    int      mLifeTimer;                     // +0x1c
};

// ---- shared vtable-call helpers -------------------------------------------
#define VF(o, off)  (*(void**)(*(char**)(o) + (off)))
#define VC0(R, o, off)               ((R (__thiscall*)(void*))VF(o, off))((void*)(o))
#define VC1(R, o, off, T1, a1)       ((R (__thiscall*)(void*, T1))VF(o, off))((void*)(o), (a1))
#define VC2(R, o, off, T1, a1, T2, a2) \
    ((R (__thiscall*)(void*, T1, T2))VF(o, off))((void*)(o), (a1), (a2))
#define VC3(R, o, off, T1, a1, T2, a2, T3, a3) \
    ((R (__thiscall*)(void*, T1, T2, T3))VF(o, off))((void*)(o), (a1), (a2), (a3))

// ===========================================================================
// cRotationRingView
// ===========================================================================

// @ 0x00e91ce0
float cRotationRingView::GetRingAnimationPercentage(float param)
{
    if (GetCurrentGameMode() == (void*)0x01654c10) {
        cRotationRing* obj = mpObject;
        if (obj != 0)
            return VC0(float, obj, 0x68) * 0.01f;
    }
    else {
        cRotationRing* obj = mpObject;
        if (param != 0.0f) {
            cRotationRing* other = *(cRotationRing**)((char*)(uintptr_t)param + 0xc);
            if (other != 0)
                obj = other;
        }
        if (obj != 0) {
            float scale = GetPropertyF(id("CommunityEditor"), 0,
                                       id("CityRotationHandleRadiusScaleFactor"),
                                       *(float*)0x1486b88);
            void* pi = (void*)VC0(void*, obj, 0x70);
            if (pi != 0) {
                if (VC1(int, pi, 0xc, uint32_t, 0x4f396a66) != 0)
                    scale = GetPropertyF(id("CommunityEditor"), 0,
                                         id("TribeRotationHandleRadiusScaleFactor"),
                                         *(float*)0x1486b5c);
            }
            return VC0(float, obj, 0x68) * scale;
        }
    }
    return GetPropertyF(id("CommunityEditor"), 0,
                        id("RotationHandleRadiusDefault"), *(float*)0x13fe160);
}

// @ 0x00e91e40
void cRotationRingView::HandleSimulationUpdate(int a, int b)
{
    (void)a; (void)b;
    cRotationRing* obj = mpObject;
    if (obj == 0)
        return;

    if (VC0(int, obj, 0x58) == 0) {
        *(uint32_t*)((char*)mModel + 4) &= 0xfffffffeu;
        mLifeTimer = 0;
        return;
    }
    *(uint32_t*)((char*)mModel + 4) |= 1u;

    float ringScale = GetPropertyF(id("CommunityEditor"), 0,
                                   id("CityRotationRingScaleFactor"), f_13ebc68);
    V3 ringOffset;
    GetPropertyV3a(&ringOffset, id("CommunityEditor"), 0,
                   id("CityRotationRingOffset"), *(V3*)0x016c5ac0);

    if (GetCurrentGameMode() != (void*)0x01654c10) {
        void* pi = (void*)VC0(void*, mpObject, 0x70);
        if (pi != 0 && VC1(int, pi, 0xc, uint32_t, 0x4f396a66) != 0) {
            ringScale = GetPropertyF(SPIDFromName("CommunityEditor"), 0,
                                     SPIDFromName("TribeRotationRingScaleFactor"),
                                     f_147b9f0);
            GetPropertyV3a(&ringOffset, SPIDFromName("CommunityEditor"), 0,
                           SPIDFromName("TribeRotationRingOffset"), *(V3*)0x016c5ac0);
        }
    }

    VC0(void, (char*)mpObject + 0x34, 0x30);

    void* mw = (void*)VC0(void*, mpObject, 0x58);
    V3 off2;
    Mat3MulV3(&off2, &ringOffset, (void*)VC0(void*, mw, 0x30));

    void* mw2 = (void*)VC0(void*, mpObject, 0x58);
    V3 base;
    memcpy(&base, (void*)VC1(void*, mw2, 0x2c, void*, 0), sizeof(V3));

    void* mw3 = (void*)VC0(void*, mpObject, 0x58);
    V3 dir;
    VC1(void, mw3, 0x60, void*, &dir);
    float inv = 1.0f / sqrtf(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z + f_13ec4b8);
    V3 ndir;
    ndir.x = dir.x * inv;
    ndir.y = inv * dir.y;
    ndir.z = inv * dir.z;

    Matrix33 mat;
    Matrix3Assign(&mat, (void*)0x016c5afc);

    V3 sum;
    sum.x = base.x + off2.x;
    sum.y = base.y + off2.y;
    sum.z = base.z + off2.z;

    V3 upv;
    VC1(void, (void*)VC0(void*, mpObject, 0x58), 0x5c, void*, &upv);
    V3 faceOut;
    Matrix3FromFacingAndUp(&faceOut, &ndir, &upv);

    // transform message (0x38 bytes): flags/modcount/translation/scale/rotation
    struct Xform {
        uint16_t flags;      // +0x00
        uint16_t modcount;   // +0x02
        V3       trans;      // +0x04
        float    scale;      // +0x10
        Matrix33 rot;        // +0x14
    } xf;
    xf.flags = 6;
    xf.modcount = 2;
    xf.trans = sum;
    xf.scale = 1.0f;
    memcpy(&xf.rot, &faceOut, sizeof(Matrix33));
    cSPTransformAssign((char*)mModel + 8, &xf);

    uint32_t* modc = (uint32_t*)((char*)mModel + 0xc);
    (void)modc;
    *(uint16_t*)((char*)mModel + 0xa) += 1;
    *(float*)((char*)mModel + 8 + 0x10) = base.x;

    bool rollover = false;
    if (!VC0(bool, mpObject, 0x80) && !VC0(bool, mpObject, 0x24))
        rollover = false;
    else
        rollover = true;

    V3 color;
    if (!rollover)
        GetPropertyV3b(&color, id("CommunityEditor"), 0, id("HandleColorDefault"),
                       *(V3*)0x1486aa4);
    else
        GetPropertyV3b(&color, id("CommunityEditor"), 0, id("HandleColorRollover"),
                       *(V3*)0x1486ab8);
    void* model = mModel;
    *(V3*)((char*)model + 0x4c) = color;

    float f0 = 0.0f;
    float f1 = 0.0f;
    void* gw = GonzagoModelWorld();
    VC2(void, gw, 0x80, void*, mModel, void*, 0);   // (model, animID, &f0, &f1, 0)
    (void)f0; (void)f1;

    float pct = GetRingAnimationPercentage(0.0f);
    int popMs = GetPropertyI(id("CommunityEditor"), 0, id("RotationHandlePopTimeMS"), 200);
    double dd = pow_f((double)mLifeTimer, (double)popMs);
    float v = (float)(dd * (1.0 - 0.0) * pct + 0.0);
    void* gw2 = GonzagoModelWorld();
    VC2(void, gw2, 0x74, void*, mModel, void*, 0);  // (model, animID, v, 0)
    (void)v;
    void* gw3 = GonzagoModelWorld();
    VC1(void, gw3, 0x10c, void*, mModel);
    mLifeTimer++;
    if ((uint32_t)popMs < (uint32_t)mLifeTimer)
        mLifeTimer = popMs;
}

// @ 0x00e923b0
cRotationRingView* cRotationRingView::MakeView(void* gamedata)
{
    cRotationRingView* view = (cRotationRingView*)operator_new_sp(
        0x20, "Simulator/cRotationRingView", 0, 0, 0, 0);
    if (view != 0) {
        view->mField04 = 0;
        view->mField08 = 0;
        *(void**)view = (void*)0x1486b1c;
        view->mField08 = 0;
        view->mField04 = 0;
        view->mpObject = 0;
        view->mpGameDataView = 0;
        view->mModel = 0;
        view->mAnimID = 0;
        view->mLifeTimer = 0;
    }
    else {
        view = 0;
    }
    // assign gamedata view with refcount
    void* old = view->mpGameDataView;
    if (gamedata != old) {
        if (gamedata != 0)
            (*(void(__thiscall**)(void*))gamedata)(gamedata);       // AddRef
        view->mpGameDataView = gamedata;
        if (old != 0)
            (*(void(__thiscall**)(void*, int))(*(void**)old))(old, 0);  // Release+? via slot 1
    }
    (void)view;
    return view;
}

// ===========================================================================
// cSpatialObjectView
// ===========================================================================

// @ 0x00e92620
void cSpatialObjectView::SetIsInWorld(bool b)
{
    void* p = (void*)VC0(void*, this, 0x2c);
    if (p == 0)
        return;
    typedef void (__thiscall* Fn)(void*, int);
    Fn fn = (Fn)VF(p, 0x16c);
    if (b)
        fn(p, 1);
    else
        fn(p, 0);
}

// @ 0x00e92660
cSpatialObjectView::~cSpatialObjectView()
{
    cSpatialObject* o = mpObject;
    *(void**)this = (void*)0x1486c00;
    if (o != 0)
        VC0(void, o, 0xa4);

    o = mpObject;
    if (o != 0) {
        mpObject = 0;
        VC0(void, o, 0xc0);
    }
    void* c = mpObjectCombatant;
    mpObjectCombatant = 0;
    if (c != 0)
        VC0(void, c, 0x64);

    c = mpObjectCombatant;
    if (c != 0)
        VC0(void, c, 0x64);

    o = mpObject;
    if (o != 0)
        VC0(void, o, 0xc0);

    *(void**)this = (void*)0x1455648;
}

// @ 0x00e926d0
void cSpatialObjectView::SetModel_926d0(void* model)
{
    *(uint32_t*)((char*)mpObject + 0x50) &= 0xffffffefu;
    void* o = mpObject;
    void** vt = *(void***)o;
    float scale = ((float(__thiscall*)(void*))vt[0x34 / 4])(o);
    ((void(__thiscall*)(void*, void*, float))vt[0x64 / 4])(o, (char*)model + 0x70, scale);

    if (mpObject != 0) {
        void* p = (void*)VC1(void*, mpObject, 0xb8, uint32_t, 0x17f243b);
        void* q = FUN_00b3d310(p, 1);
        FUN_00b48770(q, 1);
        return;
    }
    {
        void* q = FUN_00b3d310(0, 1);
        FUN_00b48770(q, 1);
    }
}

// @ 0x00e92740
void cSpatialObjectView::MakeView_740(void* a, void* b, void* c, void* d)
{
    void* newObj = 0;
    if (a != 0)
        newObj = (void*)VC1(void*, a, 0xc, uint32_t, 0x1186577);

    if (newObj != mpObject) {
        if (newObj != 0)
            VC0(void, newObj, 0xbc);
        cSpatialObject* old = mpObject;
        mpObject = (cSpatialObject*)newObj;
        if (old != 0)
            VC0(void, old, 0xc0);
    }
    if (mpObject == 0)
        return;

    void* sub = (void*)VC0(void*, mpObject, 0xac);
    bool doSet = false;
    if (sub != 0) {
        void* have = (void*)VC0(void*, mpObject, 0x98);
        bool same = (*(uint32_t*)have == *(uint32_t*)d)
                 && (*(uint32_t*)((char*)have + 4) == *(uint32_t*)((char*)d + 4))
                 && (*(uint32_t*)((char*)have + 8) == *(uint32_t*)((char*)d + 8));
        if (!same || VC0(bool, mpObject, 0x88)) {
            VC1(void, mpObject, 0x94, void*, d);
            if (VC1(bool, mpObject, 0xa0, void*, a)) {
                void* s2 = (void*)VC0(void*, mpObject, 0xac);
                if (s2 != 0) {
                    bool vis = VC0(bool, mpObject, 0x9c);
                    mbField30 = !vis;
                    if (vis)
                        SetModel_926d0(s2);
                }
            }
            doSet = true;
        }
    }

    if (doSet) {
        if (mField14) {
            *(V3*)((char*)this + 0x18) = *(V3*)((char*)sub + 0x4c);
        }
        else {
            *(V3*)((char*)this + 0x18) = *(V3*)c;
            *(V3*)((char*)sub + 0x4c) = *(V3*)c;
        }
        void* oldc = *(void**)((char*)sub + 0x64);
        if (a != oldc) {
            if (a != 0)
                (*(void(__thiscall**)(void*))a)(a);
            *(void**)((char*)sub + 0x64) = a;
            if (oldc != 0)
                (*(void(__thiscall**)(void*, int))(*(void**)oldc))(oldc, 0);
        }
        *(uint32_t*)((char*)sub + 0x60) = VC0(uint32_t, a, 0x20);
        VC1(void, mpObject, 0x8c, int, 0);
        mbField31 = 0;
    }

    {
        void* v = 0;
        if (mpObject != 0)
            v = (void*)VC1(void*, mpObject, 0xb8, uint32_t, 0x13f94d4);
        void* oldv = mpObjectCombatant;
        if (v != oldv) {
            if (v != 0)
                VC0(void, v, 0x60);
            mpObjectCombatant = v;
            if (oldv != 0)
                VC0(void, oldv, 0x64);
        }
    }
}

// @ 0x00e92910
void cSpatialObjectView::Init(void* gamedata)
{
    void* newObj = 0;
    if (gamedata != 0)
        newObj = (void*)VC1(void*, gamedata, 0xc, uint32_t, 0x1186577);

    if (newObj != mpObject) {
        if (newObj != 0)
            VC0(void, newObj, 0xbc);
        cSpatialObject* old = mpObject;
        mpObject = (cSpatialObject*)newObj;
        if (old != 0)
            VC0(void, old, 0xc0);
    }
    if (mpObject == 0)
        return;
    void* sub = (void*)VC0(void*, mpObject, 0xac);
    if (sub == 0)
        return;

    void* oldc = *(void**)((char*)sub + 0x64);
    if (gamedata != oldc) {
        if (gamedata != 0)
            (*(void(__thiscall**)(void*))gamedata)(gamedata);
        *(void**)((char*)sub + 0x64) = gamedata;
        if (oldc != 0)
            (*(void(__thiscall**)(void*, int))(*(void**)oldc))(oldc, 0);
    }
    *(uint32_t*)((char*)sub + 0x60) = VC0(uint32_t, gamedata, 0x20);
}

// @ 0x00e929b0
void* cSpatialObjectView::SetModel()
{
    cSpatialObject* o = mpObject;
    if (o != 0)
        return (void*)VC0(void*, o, 0xac);
    return 0;
}

// @ 0x00e929f0
void* cSpatialObjectView::GetData()
{
    cSpatialObject* o = mpObject;
    if (o != 0)
        return (void*)VC1(void*, o, 0xb8, uint32_t, 0x17f243b);
    return 0;
}

// @ 0x00e92a10
void cSpatialObjectView::UpdateFadeState()
{
    void* g = *(void**)0x016c7aa4;
    if (g == 0)
        return;
    if (*(int*)((char*)g + 0xcc) != 1)
        return;

    void* self = (void*)VC0(void*, this, 0xac);
    if (self == 0)
        return;
    cSpatialObject* obj = mpObject;
    if (*(char*)((char*)obj + 0x6f) == 0)
        return;
    if (!VC0(bool, this, 0x20))
        return;

    bool b = false;
    void* p = FUN_00ae66d0(this);
    if (p != 0 && p == FUN_00efe5a0())
        b = true;

    if (*(char*)((char*)obj + 0x6e) != 0) {
        *(uint32_t*)((char*)self + 4) |= 8u;
        *(uint8_t*)((char*)self + 0x5c) = 1;
        return;
    }
    if (*(char*)((char*)obj + 0x78) != 0) {
        *(uint32_t*)((char*)self + 4) |= 8u;
        *(uint8_t* const)((char*)self + 0x5c) = 4;
        return;
    }
    if (b) {
        bool r = VC0(bool, this, 0x24);
        *(uint32_t*)((char*)self + 4) |= 8u;
        *(uint8_t*)((char*)self + 0x5c) = r ? 3 : 0;
        return;
    }
    if (VC0(bool, this, 0x24)) {
        *(uint32_t*)((char*)self + 4) |= 8u;
        *(uint8_t*)((char*)self + 0x5c) = 2;
        return;
    }
LAB_off:
    *(uint32_t*)((char*)self + 4) &= 0xfffffff7u;
}

// @ 0x00e92af0
cSpatialObjectView::cSpatialObjectView()
{
    mField08 = 0;
    mField04 = 0;
    *(void**)this = (void*)0x1486c00;
    mpObject = 0;
    mpObjectCombatant = 0;
    mField14 = 0;
    mColor.x = g_defaultColorR;
    mColor.y = g_defaultColorG;
    mColor.z = g_defaultColorB;
    mField24 = 0;
    mField28 = 0;
    mField2c = 0;
    mbField30 = 0;
    mbField31 = 0;
    mbField32 = 0;
}

// @ 0x00e92b50
cSpatialObjectView* MakeView_92b50(void* gamedata)
{
    cSpatialObjectView* v = (cSpatialObjectView*)operator_new_sp(
        0x34, "Simulator/cSpatialObjectView", 0, 0, 0, 0);
    if (v != 0) {
        v->mField08 = 0;
        v->mField04 = 0;
        *(void**)v = (void*)0x1486c00;
        v->mpObject = 0;
        v->mpObjectCombatant = 0;
        v->mField14 = 0;
        v->mColor.x = g_defaultColorR;
        v->mColor.y = g_defaultColorG;
        v->mColor.z = g_defaultColorB;
        v->mField24 = 0;
        v->mField28 = 0;
        v->mField2c = 0;
        v->mbField30 = 0;
        v->mbField31 = 0;
        v->mbField32 = 0;
    }
    else {
        v = 0;
    }
    if (gamedata != 0) {
        void* obj = (void*)VC1(void*, gamedata, 0xc, uint32_t, 0x1186577);
        if (obj != 0) {
            v->mField14 = 1;
            if (VC0(bool, obj, 0x90)) {
                void* pos = (void*)VC0(void*, obj, 0x98);
                V3 p = *(V3*)pos;
                void* world = GonzagoModelWorld();
                VC2(void, v, 0x28, void*, gamedata, void*, world);
                (void)p;
                return v;
            }
            VC1(void, v, 0x24, void*, gamedata);
        }
    }
    return v;
}

// @ 0x00e92c60
unsigned char cSpatialObjectView::GetIsInWorld()
{
    void* p = (void*)VC0(void*, this, 0x2c);
    if (p != 0)
        return (*(uint32_t*)((char*)p + 4) >> 0xf) & 1;
    return 0;
}

// @ 0x00e92c80
unsigned char cSpatialObjectView::GetIsVisible()
{
    void* p = (void*)VC0(void*, this, 0x2c);
    if (p == 0)
        return 0;
    return *(uint8_t*)((char*)p + 4) & 1;
}
