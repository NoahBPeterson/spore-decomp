// Slice s00e92ca0: 0x00E92CA0..0x00E93C00.  Simulator view classes deriving from
// SP::cSpatialObjectView (ctor 0x00e92af0): the per-step update of a generic spatial
// object view, the damage/transition state machine of the tribe tool and tribe views,
// and their ctors/dtors.
//
//  0x00e92ca0  SP::cSpatialObjectView::HandleSimulationUpdate   (1214 B, ret 8)
//  0x00e93160  SP::cSpatialObjectView::OnDamageStateChanged     (313 B, ret 8)
//  0x00e932a0  Simulator::cTribeToolView::cTribeToolView        (42 B)
//  0x00e932d0  Simulator::cTribeToolView::~cTribeToolView       (140 B)
//  0x00e93380  SP::cTribeToolView::MakeView                     (363 B, ret 4)
//  0x00e934f0  SP::cTribeToolView::UpdateDamageState            (1220 B)
//  0x00e939c0  SP::cBabySackView::HandleSimulationUpdate        (441 B, ret 8)
//  0x00e93b80  Simulator::cTribeView::cTribeView                (118 B)
//  0x00e93c00  Simulator::cTribeView::~cTribeView               (85 B)
//
// Flags: /O2 /MD /Gy /TP /arch:SSE (MSVC 2008 SP1; no /EHsc, which adds EH
// frames that the virtual dtors do not have in the original).
#include "types.h"
#include <math.h>

// ---------------------------------------------------------------------------
// Raw virtual-call / field helpers.  The exact class of most objects here is
// not recovered, so their vtables are indexed by byte offset.
// ---------------------------------------------------------------------------
#define VS(o, off)              (*(void**)(*(char**)(o) + (off)))
#define VC0(R, o, off)          ((R (__thiscall*)(void*))VS(o, off))((void*)(o))
#define VC1(R, o, off, T1, a1)  ((R (__thiscall*)(void*, T1))VS(o, off))((void*)(o), (a1))
#define VC2(R, o, off, T1, a1, T2, a2) \
    ((R (__thiscall*)(void*, T1, T2))VS(o, off))((void*)(o), (a1), (a2))
#define VC3(R, o, off, T1, a1, T2, a2, T3, a3) \
    ((R (__thiscall*)(void*, T1, T2, T3))VS(o, off))((void*)(o), (a1), (a2), (a3))
#define VC4(R, o, off, T1, a1, T2, a2, T3, a3, T4, a4) \
    ((R (__thiscall*)(void*, T1, T2, T3, T4))VS(o, off))((void*)(o), (a1), (a2), (a3), (a4))
#define FU8(p, off)   (*(uint8_t*)((char*)(p) + (off)))
#define FI32(p, off)  (*(int32_t*)((char*)(p) + (off)))
#define FU32(p, off)  (*(uint32_t*)((char*)(p) + (off)))
#define FF32(p, off)  (*(float*)((char*)(p) + (off)))

// ---------------------------------------------------------------------------
// Layouts.
// ---------------------------------------------------------------------------
class Key {                                  // EA::ResourceMan::Key  (0xc)
public:
    uint32_t mInstance;                      // +0x0
    uint32_t mType;                          // +0x4
    uint32_t mGroup;                         // +0x8
};

struct Vec3 { float x, y, z; };
struct Matrix33 { float m[9]; };

// cTransform-like message sent to visual effects (0x38).
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

// One tEffectInfo entry of cSpatialObjectView's effect list (0x3c bytes).
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

struct cSpatialObject {
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
    Key mModelKey;                           // +0x70
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

// cGonzagoTimer : cSPTimer (0x20) -- ctor 0x00b63890, dtor 0x00b638b0,
// Restart 0x00bc3130, GetElapsedTime 0x00bc3190, Cancel 0x00bc3170.
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

// The generic spatial-object view (retail size 0x34, ctor 0x00e92af0).
class cSpatialObjectView {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24();
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

    cSpatialObjectView();                                // 0x00e92af0
    __declspec(noinline) ~cSpatialObjectView();          // 0x00e92660

    uint32_t mField04;                                   // +0x04
    uint32_t mField08;                                   // +0x08
    cSpatialObject* mpObject;                            // +0x0c
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
    void OnDamageStateChanged(int state, Key* key);               // 0x00e93160
    void v926d0(void* model);                                     // 0x00e926d0
};

// Simulator::cTribeToolView (0x70)
class cTribeToolView : public cSpatialObjectView {
public:
    cTribeToolView();                                    // 0x00e932a0
    ~cTribeToolView();                                   // 0x00e932d0
    cSpatialObjectView* MakeView(void* gameData);        // 0x00e93380
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

// Simulator::cTribeView (0x68)
class cTribeView : public cSpatialObjectView {
public:
    cTribeView();                                        // 0x00e93b80
    ~cTribeView();                                       // 0x00e93c00

    uint8_t  mbDrawPerimeter;                            // +0x34
    uint8_t  mbTransition;                               // +0x35
    char     pad_36[2];
    int32_t  mDamageState;                               // +0x38
    cGonzagoTimer mTransitionTimer;                      // +0x40
    uint32_t mTransitionEnd;                             // +0x60
};

// The baby-sack view shares cTribeToolView's member layout for the range it
// touches in its HandleSimulationUpdate (+0x34, +0x38, timer at +0x40).
class cBabySackView : public cTribeToolView {
public:
    void HandleSimulationUpdate(int a, int b);           // 0x00e939c0
};

// ---------------------------------------------------------------------------
// Flat helpers.
// ---------------------------------------------------------------------------
int      GetCurrentGameMode();                        // 0x00b5b800
void*    GonzagoModelWorld(void* key);                // 0x00b3d520
void*    GetGameTerrainCursor();                      // 0x00b30d70
void*    GameTimeManager();                           // 0x00b3d380
float    GameTimeManager_GetDelta(void* self);        // 0x00b31730
void*    sim_b3d310(void* p, int a);                  // 0x00b3d310
void     sim_b48770(void* p, int a);                  // 0x00b48770
float*   Matrix3FromQuaternion(float* out, void* q);  // 0x0059c190
bool     b45480(void* p);                             // 0x00b45480
void     b34040(void);                                // 0x00434040
void     b571d40(void* obj, Vec3* v);                 // 0x00571d40
void     b69b1c0(void* out, void* a, void* b);        // 0x0069b1c0
float*   b46d660(float* a, float* b);                 // 0x0046d660
float    bfc490(void* p);                             // 0x00bfc490
float    c104bdb0();                                  // 0x0104bdb0
float    ce6920();                                    // 0x00ce6920
void*    sub_c9d9e0(void* p);                         // 0x00c9d9e0
bool     sub_c9cfc0(void* p);                         // 0x00c9cfc0
void*    sub_c9cec0(void* p);                         // 0x00c9cec0
bool     ae3d40(void* self, void* a);                 // 0x00ae3d40
class SimSingleton {
public:
    SimSingleton();                                   // 0x00ae5c30
};
void* operator new(unsigned int size, const char* name, int flags, unsigned int align,
                   const char* file, int line);         // 0x00f473a0
void     operator_delete_sp(void* p);                 // 0x00f47380
void     Matrix3Assign(void* dst, const void* src);   // 0x0041cb40
void*    b767760(void* a);                            // 0x00767760 (ecx = &local)
bool     b7cb90(void* self, void* out);               // 0x00bfcb90
float*   b6f0c0(void* p);                             // 0x00b6f0c0
uint8_t* GetPropertyBool(void* p);                    // 0x0041e920
void     e92a10_c(void* p);                           // 0x00e92a10
void     c537dc0(void* p, void* q);                   // 0x00537dc0 (cSPTransformOps::Assign)
void*    g_pSimSingleton;                             // 0x0167a60c
float    g_16c5b94;                                   // 0x016c5b94  (0.95 threshold)
float    g_16c5b98;                                   // 0x016c5b98  (0.90 threshold)
uint32_t g_16c5b9c;                                   // 0x016c5b9c  (init guards)
float    g_1486cd8;                                   // 0x01486cd8  (0.80 threshold)

// @ 0x00e92ca0
void cSpatialObjectView::HandleSimulationUpdate(int deltaTimeMS, int deltaTime)
{
    cSpatialObject* obj = mpObject;
    if (FU8(&obj->mModelKey, 5) == 0)
        return;

    void* model = GetModel();

    bool transition = false;
    if (mbField30) {
        if (model == 0) {
            mbField30 = 0;
            obj->mFlags &= ~0x10u;
        } else if (VC0(bool, mpObject, 0x9c)) {
            mbField30 = 0;
            transition = true;
            v926d0(model);
        }
    }

    if (VC0(bool, mpObject, 0x88)) {
        float* pos = (float*)VC1(void*, mpObject, 0x98, void*, &mColor);
        void* world = GonzagoModelWorld(pos);
        void* m = (void*)VC1(void*, this, 0x0c, void*, world);
        v28(m);
        cSpatialObject* o = mpObject;
        if ((FU8(o, 0x50) & 8) != 0) {
            void* p = 0;
            if (o)
                p = (void*)VC1(void*, o, 0xb8, uint32_t, 0x17f243b);
            void* q = sim_b3d310(p, 1);
            sim_b48770(q, 1);
        }
        model = GetModel();
    }

    if ((FU8(mpObject, 0x50) & 4) != 0 && model != 0) {
        Matrix3Assign((char*)model + 8, (void*)0x016c5b34);
        VC1(void, this, 0x38, void*, (char*)model + 8);
        float* a = (float*)((char*)model + 0x24);
        float* b = (float*)((char*)this + 0x2c);
        VC1(void, this, 0x3c, void*, b46d660(a, b));
    }

    if ((FU32(mpObject, 0x50) & 0x400) == 0) {
        mpObject->KillEffect(0x48e3a72, 1);
    } else if (!mpObject->GetEffect(0x48e3a72)) {
        mpObject->CreateEffect2(0x65c2d751, 0, 0x48e3a72);
    }

    float t = (float)(uint32_t)deltaTimeMS * 0.001f;
    mpObject->c88550_f(t);

    cSpatialObject* o = mpObject;
    if (FU8(&o->mModelKey, 4) != 0) {
        FU8(&o->mModelKey, 4) = 0;
    } else if (!transition) {
        goto LAB_00e9300b;
    }

    if (model == 0 && !mpObject->c888c0_f())
        goto LAB_00e9300b;

    {
        XformMsg msg;
        msg.mFlags = 0;
        msg.mModCount = 0;
        msg.mTranslation.x = *(float*)0x016c5b28;
        msg.mTranslation.y = *(float*)0x016c5b2c;
        msg.mTranslation.z = *(float*)0x016c5b30;
        msg.mScale = 1.0f;
        Matrix3Assign(&msg.mRotation, (void*)0x016c5b34);
        float* pos = (float*)GetModel();
        msg.mTranslation.x = pos[0];
        msg.mTranslation.y = pos[1];
        msg.mTranslation.z = pos[2];
        msg.mFlags |= 4;
        msg.mModCount++;
        msg.mScale = GetScale();
        msg.mModCount++;
        void* q = GetTransform();
        float rot[9];
        Matrix3FromQuaternion(rot, q);
        for (int i = 0; i < 9; ++i)
            msg.mRotation.m[i] = rot[i];
        msg.mFlags |= 2;
        msg.mModCount++;
        if (model != 0)
            c537dc0((char*)model + 8, (void*)0x016c5b28);
        mpObject->c89d60_f(&msg);
    }

    if (GetCurrentGameMode() == 0x1654c01 && FU8(&mpObject->mModelKey, 1) == 0) {
        cSpatialObject* o = mpObject;
        if ((o->mFlags & 0x1000) != 0) {
            void* p = sim_b3d310(o, 0);
            if (b45480(p)) {
                void* e = mpObject->FindEffectRaw(0x48021ef);
                if (e == 0 || !VC0(bool, e, 0x10)) {
                    mpObject->CreateEffect3(0x2775920e, 0, 0x48021ef);
                    e = mpObject->FindEffectRaw(0x48021ef);
                    if (e) {
                        XformMsg msg;
                        VC1(void, e, 0x20, void*, &msg);
                        msg.mScale = VC0(float, mpObject, 0x74);
                        msg.mModCount++;
                        VC1(void, e, 0x18, void*, &msg);
                    }
                }
            }
        } else {
            mpObject->KillEffect(0x48021ef, 0);
        }
    }

    mpObject->c89d60_f((void*)0x016c5b28);

LAB_00e9300b:
    mpObject->c8aa60_f();
    if (model)
        e92a10_c(mpObject);

    void* cb = mpObjectCombatant;
    if (cb != 0) {
        void* g = VC0(void*, cb, 0x34);
        if (g != 0 && b7cb90(mpObjectCombatant, &g)) {
            cIVisualEffect* e = (cIVisualEffect*)mpObject->FindEffectRaw(0x5417c7a);
            if (e == 0)
                e = (cIVisualEffect*)mpObject->CreateEffect3(0x5417c7a, 0, (uint32_t)g);
            if (e != 0) {
                if (!VC0(bool, e, 0x10))
                    VC1(void, e, 0x8, int, 0);
                b34040();
                Vec3 pos;
                pos.x = -*(float*)((char*)&g + 0);
                pos.y = -*(float*)((char*)&g + 4);
                pos.z = -*(float*)((char*)&g + 8);
                XformMsg msg;
                b69b1c0(&msg, (void*)0x016c5b88, &pos);
                for (int i = 0; i < 9; ++i)
                    msg.mRotation.m[i] = (&pos.x)[i];
                msg.mFlags |= 2;
                msg.mModCount++;
                msg.mScale = VC0(float, mpObject, 0x70) * 0.083333336f;
                msg.mModCount++;
                VC1(void, e, 0x18, void*, &msg);
            }
        }
    }

    FU8(mpObject, 0xa5) = 0;
}

// @ 0x00e93160
void cSpatialObjectView::OnDamageStateChanged(int state, Key* key)
{
    void* model = (void*)VC0(void*, mpObject, 0xac);
    void* model2 = (void*)VC0(void*, mpObject, 0xb0);
    if (model == 0 || model2 == 0)
        return;
    if (((FU32(model, 4) >> 0xe) & 1) == 0)
        return;
    if (mbDamageState == (uint8_t)state)
        return;
    mbDamageState = (uint8_t)state;

    int n = VC1(int, model2, 0x64, void*, model);
    for (int i = 0; i < n; ++i) {
        void* elem = VC2(void*, model2, 0x68, void*, model, int, i);
        uint32_t vec[4];
        b767760(elem);
        int cnt = VC2(int, model2, 0x6c, void*, model, int, i);
        for (int j = 0; j < cnt; ++j) {
            uint32_t e = *(uint32_t*)&vec[j];
            if (key == 0 || e == key->mInstance)
                VC4(void, model2, 0x70, void*, model, uint32_t, e, void*, vec, int, 0);
        }
    }
}

// @ 0x00e932a0
cTribeToolView::cTribeToolView()
    : mbDrawPerimeter(0), mbTransition(0), mDamageState(0), mDamageEffect(0)
{
}

// @ 0x00e932d0
cTribeToolView::~cTribeToolView()
{
    *(void**)this = (void*)0x1486c54;
    cIVisualEffect* e = mDamageEffect;
    if (e) {
        VC1(void, e, 0xc, int, 1);
        e = mDamageEffect;
        if (e) {
            mDamageEffect = 0;
            VC0(void, e, 4);
        }
    }
    if (mpObject->FindEffectRaw(0x49b925c))
        mpObject->KillEffect(0x49b925c, 1);
    if (mpObject->FindEffectRaw(0x49b925d))
        mpObject->KillEffect(0x49b925d, 1);
    e = mDamageEffect;
    if (e)
        VC0(void, e, 4);
}

// @ 0x00e93380
cSpatialObjectView* cTribeToolView::MakeView(void* gameData)
{
    cTribeToolView* view = new("Simulator/cTribeToolView", 0, 0, 0, 0) cTribeToolView();

    cSpatialObject* obj = 0;
    if (gameData)
        obj = (cSpatialObject*)VC1(void*, gameData, 0x0c, uint32_t, 0x1186577);

    cSpatialObject* old = view->mpObject;
    if (obj != old) {
        if (obj)
            VC0(void, obj, 0xbc);
        view->mpObject = obj;
        if (old)
            VC0(void, old, 0xc0);
    }

    if (gameData) {
        void* g = (void*)VC1(void*, gameData, 0x0c, uint32_t, 0x116d858);
        void* h = g ? sub_c9d9e0(g) : 0;
        if (h) {
            float* v = b6f0c0(*(void**)((char*)h + 0x234));
            view->mColor.x = v[0];
            view->mColor.y = v[1];
            view->mColor.z = v[2];
        }
    }

    void* model;
    if (VC0(bool, view->mpObject, 0x90))
        model = (void*)VC1(void*, view->mpObject, 0x98, void*, &view->mColor);
    else
        model = (char*)view + 0x24;
    view->v28(GonzagoModelWorld(model));

    if (view->GetModel() != 0) {
        void* o = view->GetModel();
        uint8_t b = 0;
        void* p = *(void**)((char*)o + 0x90);
        if (p) {
            int16_t* out = 0;
            if (VC2(bool, p, 0x24, uint32_t, 0x4245bb4, int16_t**, &out) && *(int16_t*)((char*)out + 0x12) == 1)
                b = *GetPropertyBool(out);
        }
        view->mbDrawPerimeter = b;
    }
    return view;
}

// @ 0x00e934f0
void cTribeToolView::UpdateDamageState()
{
    void* obj = 0;
    if (mpObject)
        obj = (void*)VC1(void*, mpObject, 0xb8, uint32_t, 0x116d858);

    if (sub_c9cfc0(obj)) {
        if (!mpObject->GetEffect(0x4a6b8058)) {
            mpObject->sub_b1a0(0x4a6b8058);
            cIVisualEffect* e = (cIVisualEffect*)mpObject->FindEffectRaw(0x4a6b8058);
            XformMsg msg;
            msg.mFlags = 0;
            msg.mModCount = 0;
            msg.mTranslation.x = *(float*)0x016c5c00;
            msg.mTranslation.y = *(float*)0x016c5c04;
            msg.mTranslation.z = *(float*)0x016c5c08;
            msg.mScale = 1.0f;
            Matrix3Assign(&msg.mRotation, (void*)0x016c5bdc);
            float* pos = (float*)((void*(__thiscall*)(void*))VS((char*)obj + 0x34, 0x2c))((char*)obj + 0x34);
            float inv = 1.0f / sqrtf(pos[0]*pos[0] + pos[1]*pos[1] + pos[2]*pos[2] + 1e-08f);
            Vec3 dir;
            dir.x = pos[0] * inv;
            dir.y = inv * pos[1];
            dir.z = inv * pos[2];
            float s = FF32(VC0(void*, mpObject, 0x68), 0x14);
            Vec3 p2;
            p2.x = s * dir.x;
            p2.y = s * dir.y;
            p2.z = s * dir.z;
            float* o2 = (float*)((void*(__thiscall*)(void*))VS((char*)obj + 0x34, 0x2c))((char*)obj + 0x34);
            p2.x = p2.x + o2[0];
            p2.z = o2[2] + p2.z;
            p2.y = o2[1] + p2.y;
            msg.mFlags |= 4;
            msg.mModCount++;
            msg.mTranslation = p2;
            void* q = VC0(void*, mpObject, 0x30);
            float rot[9];
            Matrix3FromQuaternion(rot, q);
            for (int i = 0; i < 9; ++i) msg.mRotation.m[i] = rot[i];
            msg.mFlags |= 2;
            msg.mModCount++;
            VC1(void, e, 0x18, void*, &msg);
        }
    } else if (!sub_c9cfc0(obj)) {
        if (mpObject->GetEffect(0x4a6b8058))
            mpObject->KillEffect(0x4a6b8058, 1);
    }

    if ((g_16c5b9c & 1) == 0) {
        g_16c5b9c |= 1;
        g_16c5b98 = c104bdb0();
    }
    if ((g_16c5b9c & 2) == 0) {
        g_16c5b9c |= 2;
        g_16c5b94 = ce6920();
    }

    float health = bfc490((char*)obj + 0x120);
    int state;
    if (health <= 0.0f)
        state = 5;
    else if (health >= g_16c5b94)
        state = 4;
    else if (health >= g_16c5b98)
        state = 3;
    else if (health < g_1486cd8)
        state = 2;
    else
        state = 1;

    bool changed = false;
    if (state != mDamageState) {
        if (mDamageState == 0) {
            changed = true;
        } else if (state == 1) {
            mbTransition = 1;
            mTransitionTimer.Restart();
            mTransitionEnd = 500;
            mTransitionTime = 0;
        } else if (state == 5) {
            mbTransition = 1;
            mTransitionTimer.Restart();
            mTransitionEnd = 300;
            mTransitionTime = 0;
            mpObject->sub_b210(0xc3fef02b);
        } else {
            mbTransition = 0;
            changed = true;
        }
    }

    if (mbTransition) {
        uint64_t el = mTransitionTimer.GetElapsedTime();
        if ((uint32_t)(el >> 32) > mTransitionTime ||
            ((uint32_t)(el >> 32) == mTransitionTime && (uint32_t)el > mTransitionEnd)) {
            mTransitionTimer.Cancel();
            mbTransition = 0;
            changed = true;
            // implicit member dtor handles mTransitionTimer
        }
    }

    if (GetCurrentGameMode() == 0x1654c04) {
        if (g_pSimSingleton == 0)
            g_pSimSingleton = new("Simulator/SimSingleton", 0, 0, 0, 0) SimSingleton();
        if (ae3d40(g_pSimSingleton, sub_c9d9e0(obj)))
            changed = false;
    }

    mDamageState = state;
    if (!changed)
        return;

    int v = VC0(int, obj, 0x58);
    int tmp[3];
    switch (mDamageState) {
    case 1:
        if (v == 10) return;
        tmp[0] = FI32(sub_c9cec0((void*)v), 0x14);
        tmp[1] = FI32(sub_c9cec0((void*)v), 0x18);
        tmp[2] = FI32(sub_c9cec0((void*)v), 0x1c);
        break;
    case 2:
        tmp[0] = FI32(sub_c9cec0((void*)v), 0x5c);
        tmp[1] = FI32(sub_c9cec0((void*)v), 0x60);
        tmp[2] = FI32(sub_c9cec0((void*)v), 0x64);
        break;
    case 3:
        tmp[0] = FI32(sub_c9cec0((void*)v), 0x50);
        tmp[1] = FI32(sub_c9cec0((void*)v), 0x54);
        tmp[2] = FI32(sub_c9cec0((void*)v), 0x58);
        break;
    case 4:
        tmp[0] = FI32(sub_c9cec0((void*)v), 0x44);
        tmp[1] = FI32(sub_c9cec0((void*)v), 0x48);
        tmp[2] = FI32(sub_c9cec0((void*)v), 0x4c);
        break;
    case 5: {
        void* c = sub_c9cec0((void*)v);
        tmp[0] = 0x790cb2;
        tmp[1] = FI32(c, 0x18);
        tmp[2] = FI32(c, 0x1c);
        break;
    }
    default:
        return;
    }
    if (tmp[0] != 0)
        VC1(void, obj, 0x94, void*, tmp);
}

// @ 0x00e939c0
void cBabySackView::HandleSimulationUpdate(int a, int b)
{
    cSpatialObjectView::HandleSimulationUpdate(a, b);

    if (mpObject == 0)
        return;
    void* g = (void*)VC1(void*, mpObject, 0xb8, uint32_t, 0x116d858);
    if (g == 0)
        return;

    void* h = sub_c9d9e0(g);
    (void)h;
    UpdateDamageState();

    uint8_t vis = VC0(uint8_t, mpObject, 0x24);
    void* t = (void*)VC0(void*, mpObject, 0xac);
    if (t == 0 || ((FU32(t, 4) >> 0xe) & 1) == 0)
        return;

    if (mbDrawPerimeter)
        FU32(t, 4) |= 4;
    else
        FU32(t, 4) &= ~2u;

    if (GetCurrentGameMode() == 0x1654c04) {
        uint8_t s = 0;
        void* cur = GetGameTerrainCursor();
        if (cur)
            s = VC0(uint8_t, cur, 0xa8);
        bool cond = (vis != 0 && s == 0);
        FU8(t, 0x5c) = 2;
        if (cond)
            FU32(t, 4) |= 8;
        else
            FU32(t, 4) &= ~8u;
    }

    if (((FU32(t, 4) >> 0xf) & 1) == 0)
        return;

    if (FU8(sub_c9d9e0(g), 0x556) != 0) {
        int v = VC0(int, g, 0x58);
        void* p = VC0(void*, g, 0xb0);
        if (v == 10)
            VC4(void, p, 0xc4, void*, t, int, 0, int, 1, uint32_t, 0xb35b8557);
        else
            VC4(void, p, 0xc4, void*, t, int, 0, int, 1, uint32_t, 0);
        FU32(t, 0x4c) = 0x3e4ccccd;
        FU32(t, 0x50) = 0x3e4ccccd;
        FU32(t, 0x54) = 0x3e4ccccd;
    }

    if (FF32(t, 0x8c) > 0.0f) {
        OnDamageStateChanged(0, 0);
        return;
    }
    OnDamageStateChanged(1, 0);
    float dt;
    if ((FU8(GameTimeManager(), 0x48) & 1) == 0)
        dt = GameTimeManager_GetDelta(GameTimeManager());
    else
        dt = 0.0f;
    void* p = VC0(void*, g, 0xb0);
    VC2(void, p, 0x7c, void*, t, float, dt);
}

// @ 0x00e93b80
cTribeView::cTribeView()
    : mbDrawPerimeter(false), mbTransition(false)
{
    Vec3 v = { 0.0f, 1.0f, 0.0f };
    mColor = v;
    mField24 = 0xd749c1;
    mField28 = 0;
    mField2c = 0x5c4fce4c;
    mTransitionEnd = 0;
}

// @ 0x00e93c00
cTribeView::~cTribeView()
{
    *(void**)this = (void*)0x1486ca4;
    mpObject->KillEffect(0x50b2c615, 1);
    mpObject->KillEffect(0x50b2c617, 1);
    mpObject->KillEffect(0x50b2c616, 1);
    mpObject->KillEffect(0x05daac1a, 1);
}

cSpatialObjectView::~cSpatialObjectView()
{
}
