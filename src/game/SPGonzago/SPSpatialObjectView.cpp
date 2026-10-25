// src/game/SPGonzago/SPSpatialObjectView.cpp -- migrated from slice(s) s00e92ca0, s00e91ce0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPSpatialObjectView.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cRotationRing.h"
#include "SP/cSpatialObject.h"

// unnamed retail callees and globals (address in the comment)
extern float g_defaultColorR;   // 0x15a89c0
extern float g_defaultColorG;   // 0x15a89c4
extern float g_defaultColorB;   // 0x15a89c8
#include <math.h>
#include <float.h>
#include <string.h>
#include "SP/cGonzagoTimer.h"

// ---- items of slice s00e91ce0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct V3 { float x, y, z; };
struct Key { uint32_t mInstance, mType, mGroup; };
uint32_t __cdecl FNVHash(const char* s, uint32_t seed, int lowercase);   // 0x00932e80
static inline uint32_t id(const char* s) { return FNVHash(s, 0x811c9dc5, 1); }
void* __cdecl operator_new_sp(unsigned int size, const char* pName,
                              int a, int b, int c, int d);               // 0x00f473a0
void* __cdecl GonzagoModelWorld();                                       // 0x00b3d520
void* FUN_00b3d310(void* p, int a);                                      // 0x00b3d310
void  FUN_00b48770(void* p, int a);                                      // 0x00b48770
void* FUN_00ae66d0(void* p);                                             // 0x00ae66d0
void* FUN_00efe5a0();                                                    // 0x00efe5a0
extern float g_defaultColorR;   // 0x15a89c0
extern float g_defaultColorG;   // 0x15a89c4
extern float g_defaultColorB;   // 0x15a89c8
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
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
    virtual void* v28(void*);                // +0x28
    virtual void* GetModel();                // +0x2c
    virtual void* GetTransform();            // +0x30
    virtual float GetScale();                // +0x34
    virtual void  SetRotation(void*);        // +0x38
    virtual void  SetModelMatrix(void*);     // +0x3c
virtual void  v40();
virtual void  v44(void*);
    virtual void  v48(int, int, int);
virtual void  v4c();
virtual void  v50();
virtual void  v54();
virtual void  v58();
virtual void  v5c();
virtual void  v60();
    virtual void  v64(void*, float);
virtual void  v68();
virtual void  v6c();
virtual void  v70();
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
#define VF(o, off)  (*(void**)(*(char**)(o) + (off)))
#define VC0(R, o, off)               ((R (__thiscall*)(void*))VF(o, off))((void*)(o))
#define VC1(R, o, off, T1, a1)       ((R (__thiscall*)(void*, T1))VF(o, off))((void*)(o), (a1))
#define VC2(R, o, off, T1, a1, T2, a2) \
    ((R (__thiscall*)(void*, T1, T2))VF(o, off))((void*)(o), (a1), (a2))
// ---- items of slice s00e91ce0 end

// ---- items of slice s00e92ca0 begin (TODO(rewrite): local stubs, replace by canonical classes)
class Key_s00e9_2ca0 {                                  // EA::ResourceMan::Key  (0xc)
public:
    uint32_t mInstance;                      // +0x0
    uint32_t mType;                          // +0x4
    uint32_t mGroup;                         // +0x8
};
struct Vec3 { float x, y, z; };
struct Matrix33 { float m[9]; };
struct XformMsg {
    uint16_t mFlags;                         // +0x00  bit 2 translation, bit 1 rotation
    uint16_t mModCount;                      // +0x02
    Vec3     mTranslation;                   // +0x04
    float    mScale;                         // +0x10
    Matrix33 mRotation;                      // +0x14
    XformMsg();                              // 0x00434040
    void SetPosition(const Vec3* p);         // 0x00571d40
};
struct cIVisualEffect {
    virtual int  AddRef();
    virtual int  Release();
    virtual void Start(int);
    virtual void Stop(int);
    virtual bool IsRunning();
    virtual void SetTransform(XformMsg*);
    virtual void Move(XformMsg*);
    virtual void Method20(XformMsg*);
    virtual bool Method24(int, void*);
    virtual void Method2c();
    virtual int  Method58();
    virtual int  Method5c();
    virtual int  Method60();
    virtual int  Method64(void*);
    virtual void* Method68(void*, int);
    virtual void Method6c(void*, int, int);
    virtual void Method70(void*, void*, int, float, int);
    virtual void Method74();
    virtual void Method7c(void*, float);
};
struct EffectInfo {
    int32_t mId;                             // +0x00
    int32_t mOwner;                          // +0x04
    uint8_t mFlag8;                          // +0x08
    char    pad_09[3];
    float   mF0c;                            // +0x0c
    uint8_t mFlag10;                         // +0x10
    char    pad_11[3];
    float   mF14;                            // +0x14
    float   mF18;                            // +0x18
    int32_t mI1c, mI20, mI24;
    uint8_t mFlag28;                         // +0x28
    char    pad_29[0x38 - 0x29];
    cIVisualEffect* mpEffect;                // +0x38
};
struct cSpatialObject_s00e9_2ca0 {
    char pad_00[0x38];
    uint32_t mFlags;                         // +0x38
    uint32_t mMaterialType;                  // +0x3c
    char pad_40[0x50 - 0x40];
    uint8_t mIsSelected;                     // +0x50
    uint8_t mIsRolledOver;                   // +0x51
    uint8_t mIsInvalid;                      // +0x52
    uint8_t mbPickable;                      // +0x53
    char pad_54[0x5c - 0x54];
    uint8_t mbKeepPinnedToPlanet;            // +0x5c
    char pad_5d[0x70 - 0x5d];
    Key_s00e9_2ca0 mModelKey;                           // +0x70
    char pad_7c[0xc0 - 0x7c];
    EffectInfo* mEffectsBegin;               // +0xc0
    EffectInfo* mEffectsEnd;                 // +0xc4

    // effect-list helpers (retail methods on cSpatialObject).
    void* FindEffectRaw(uint32_t id);        // 0x00c888e0
    bool  GetEffect(uint32_t id);            // 0x00c88910
    void  KillEffect(uint32_t id, int flag); // 0x00c8ad30
    void  CreateEffect2(uint32_t id, int a, int b); // 0x00c8b130
    void* CreateEffect3(uint32_t a, uint32_t b, uint32_t c); // 0x00c8b060
    void  sub_b1a0(int id);                  // 0x00c8b1a0
    void  sub_b210(int id);                  // 0x00c8b210
    void  c88550_f(float dt);                // 0x00c88550
    void  c8aa60_f();                        // 0x00c8aa60
    bool  c888c0_f();                        // 0x00c888c0
    void  c89d60_f(void* msg);               // 0x00c89d60
};
struct cGonzagoTimer {
    void*    mField00;                       // +0x00 (vptr)
    uint32_t mRefCount;                      // +0x04
    uint64_t mElapsedTime;                   // +0x08
    uint64_t mBaseTime;                      // +0x10
    uint8_t  mRunning;                       // +0x18
    char     pad_19[3];
    void*    mGetTime;                       // +0x1c
    cGonzagoTimer();
    ~cGonzagoTimer() throw();
    void Restart();
    uint64_t GetElapsedTime();
    void Cancel();
};
class cSpatialObjectView_s00e9_2ca0 {
public:
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
    virtual void* v28(void*);                            // +0x28
    virtual void* GetModel();                            // +0x2c
    virtual void* GetTransform();                        // +0x30
    virtual float GetScale();                            // +0x34
    virtual void  SetRotation(XformMsg*);                // +0x38
    virtual void  SetModelMatrix(void*);                 // +0x3c
    virtual void  v40();
    virtual void  UpdateShadow(XformMsg*);               // +0x44
    virtual void  SetEffectRange(int, int, int);         // +0x48
    virtual void  v4c();
    virtual void  v50();
    virtual void  v54();
    virtual void  v58();
    virtual void  v5c();
    virtual void  v60();
    virtual void  v64();
    virtual void  v68();
    virtual void  v6c();
    virtual void  v70();
    virtual void  v74();
    virtual void* v78(void*);                            // +0x78

    cSpatialObjectView_s00e9_2ca0();                                // 0x00e92af0
    __declspec(noinline) ~cSpatialObjectView_s00e9_2ca0();          // 0x00e92660

    uint32_t mField04;                                   // +0x04
    uint32_t mField08;                                   // +0x08
    cSpatialObject_s00e9_2ca0* mpObject;                            // +0x0c
    void*           mpObjectCombatant;                   // +0x10
    uint8_t mField14;                                    // +0x14
    char    pad_15[3];
    Vec3    mColor;                                      // +0x18
    uint32_t mField24;                                   // +0x24
    uint32_t mField28;                                   // +0x28
    uint32_t mField2c;                                   // +0x2c
    uint8_t mbField30;                                   // +0x30
    uint8_t mbDamageState;                               // +0x31
    uint8_t mbField32;                                   // +0x32
    char    pad_33[1];

    void HandleSimulationUpdate(int deltaTimeMS, int deltaTime);  // 0x00e92ca0
    void OnDamageStateChanged(int state, Key_s00e9_2ca0* key);               // 0x00e93160
    void v926d0(void* model);                                     // 0x00e926d0
};
class cTribeToolView : public cSpatialObjectView_s00e9_2ca0 {
public:
    cTribeToolView();                                    // 0x00e932a0
    ~cTribeToolView();                                   // 0x00e932d0
    cSpatialObjectView_s00e9_2ca0* MakeView(void* gameData);        // 0x00e93380
    void UpdateDamageState();                            // 0x00e934f0

    uint8_t  mbDrawPerimeter;                            // +0x34
    uint8_t  mbTransition;                               // +0x35
    char     pad_36[2];
    int32_t  mDamageState;                               // +0x38
    cGonzagoTimer mTransitionTimer;                      // +0x40
    uint32_t mTransitionEnd;                             // +0x60
    uint32_t mTransitionTime;                            // +0x64
    cIVisualEffect* mDamageEffect;                       // +0x68
};
cSpatialObjectView_s00e9_2ca0::~cSpatialObjectView_s00e9_2ca0()
{
}
// ---- items of slice s00e92ca0 end

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

// @ 0x00e932a0
cTribeToolView::cTribeToolView()
: mbDrawPerimeter(0), mbTransition(0), mDamageState(0), mDamageEffect(0)
{
}
