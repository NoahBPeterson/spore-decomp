// src/game/SPGonzago/SPTribeToolView.cpp -- migrated from slice(s) s00e92ca0, s00d0c010, s00c91a40 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPTribeToolView.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cPropertyManager.h"
#include "SP/cTribe.h"
#include "SP/cCity.h"
#include "EA/ResourceMan/Key.h"
#include "SP/cGonzagoTimer.h"
#include "SP/cSpatialObject.h"
#include <math.h>

// ---- items of slice s00c91a40 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char u8;
typedef unsigned int  u32;
typedef int           i32;
typedef float         f32;
namespace SP {
    extern u8 DAT_01654c02;              // 0x01654c02  current-game-mode sentinel
}
namespace SP {
class cTool;
}
namespace SP {
class cRefCounted {
public:
    virtual void AddRef(void);           // 0x00
    virtual void Release(void);          // 0x04
};
}
namespace SP {
template <class T>
class AutoRefCount {
public:
    T *mPtr;
    AutoRefCount &operator=(T *p)
    {
        T *old = mPtr;
        if (p != old) {
            p->AddRef();
            mPtr = p;
            if (old != 0)
                old->Release();
        }
        return *this;
    }
};
}
namespace SP {
class cModel {
public:
virtual void vm00(void);
virtual void vm01(void);
virtual void vm02(void);
virtual void vm03(void);
virtual void vm04(void);
virtual void vm05(void);
virtual void vm06(void);
virtual void vm07(void);
virtual void vm08(void);
virtual void vm09(void);
virtual void vm10(void);
virtual void vm11(void);
virtual void vm12(void);
virtual void vm13(void);
virtual void vm14(void);
virtual void vm15(void);
virtual void vm16(void);
virtual void vm17(void);
virtual void vm18(void);
virtual void vm19(void);
virtual void vm20(void);
virtual void vm21(void);
virtual void vm22(void);
virtual void vm23(void);
virtual void vm24(void);
virtual void vm25(void);
virtual void vm26(void);
virtual void vm27(void);
virtual void vm28(void);
virtual void vm29(void);
virtual void vm30(void);
virtual void vm31(void);
virtual void vm32(void);
virtual void vm33(void);
virtual void vm34(void);
virtual void vm35(void);
    virtual void vm36(void);
    virtual void SetDesc(const void *desc);          // 0x94
virtual void vm38(void);
virtual void vm39(void);
    virtual void SetWorld(void *world);              // 0xa0
virtual void vm41(void);
virtual void vm42(void);
    virtual void *GetOwner(void);                    // 0xac
};
}
namespace SP {
class cToolDef {
public:
virtual void vd00(void);
virtual void vd01(void);
virtual void vd02(void);
virtual void vd03(void);
virtual void vd04(void);
virtual void vd05(void);
virtual void vd06(void);
virtual void vd07(void);
virtual void vd08(void);
virtual void vd09(void);
virtual void vd10(void);
virtual void vd11(void);
virtual void vd12(void);
virtual void vd13(void);
virtual void vd14(void);
virtual void vd15(void);
virtual void vd16(void);
virtual void vd17(void);
virtual void vd18(void);
virtual void vd19(void);
virtual void vd20(void);
    virtual void vd21(void);
    virtual bool IsActive(void);                     // 0x58
};
}
namespace SP {
class cTool : public cRefCounted {
public:
    unsigned char pad_04[0x34 - 4];
    cModel        mModel;                // 0x34  the tool's rendered model
    unsigned char pad_38[0x120 - 0x38];
    cToolDef      mDef;                  // 0x120 the tool's definition

    void RefreshModel(void);             // 0x00c9d030  thiscall
    void UpdateTransform(void);          // 0x00c9dd50  thiscall
};
}
namespace SP {
class cModelOwner {
public:
    unsigned char        pad_00[0x64];
    AutoRefCount<cTool>  mTool;          // 0x64  the tool currently bound to this model
};
}
namespace SP {
class cHutModelState {
public:
    unsigned char pad_00[0x608];
    i32           m608;                  // 0x608
    i32           m60c;                  // 0x60c
};
}
namespace SP {
class cTribe_s00c9_1a40 {
public:
    cTool *GetToolOfType(int toolType);  // 0x00c8f6e0
    i32    GetModeVariant(void);         // 0x00a1ad10
    void   GetClosestWater(void);        // 0x00c8fe20
};
}
namespace SP {
class cTribeToolView : public cTribe_s00c9_1a40 {
public:
    unsigned char pad_00[0x120];         // (the empty cTribe base occupies no bytes)
    cToolDef      mDef;                  // 0x120
    unsigned char pad_124[0x300 - 0x124];
    u8            m300;                  // 0x300  water-query dirty/valid byte
    unsigned char pad_301[0x310 - 0x301];
    f32           m310;                  // 0x310  closest-water / ground height
    unsigned char pad_314[0x18cc - 0x314];
    cHutModelState *m18cc;               // 0x18cc

    void UpdateModel(void);              // 0x00c91a40
    void *ChooseNewHutModel(void);       // 0x00c91b60
    f32  GetWaterOrHeight(void);         // 0x00c91c80
};
}
namespace SP {
    void  *GetCurrentGameMode(void);     // 0x00b5b800
}
namespace SP {
    void  *GonzagoModelWorld(void);      // 0x00b3d520
}
struct SP_ToolDesc {
    u32 id;
    u32 param0;
    u32 param1;
};
// ---- items of slice s00c91a40 end

// ---- items of slice s00d0c010 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma warning(disable : 4100)
namespace SP {
struct cTribeToolView_s00d0_c010 {
    uint8_t pad000[4];                                  // +0x000

    bool UpdateRotationSound();  // 0x00d0c170 (SP::cTribeToolView::UpdateRotationSound)
};
}
// ---- items of slice s00d0c010 end

// ---- items of slice s00e92ca0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define VS(o, off)              (*(void**)(*(char**)(o) + (off)))
#define VC0(R, o, off)          ((R (__thiscall*)(void*))VS(o, off))((void*)(o))
#define VC1(R, o, off, T1, a1)  ((R (__thiscall*)(void*, T1))VS(o, off))((void*)(o), (a1))
#define VC2(R, o, off, T1, a1, T2, a2) \
    ((R (__thiscall*)(void*, T1, T2))VS(o, off))((void*)(o), (a1), (a2))
#define VC4(R, o, off, T1, a1, T2, a2, T3, a3, T4, a4) \
    ((R (__thiscall*)(void*, T1, T2, T3, T4))VS(o, off))((void*)(o), (a1), (a2), (a3), (a4))
#define FU8(p, off)   (*(uint8_t*)((char*)(p) + (off)))
#define FU32(p, off)  (*(uint32_t*)((char*)(p) + (off)))
#define FF32(p, off)  (*(float*)((char*)(p) + (off)))
class Key {                                  // EA::ResourceMan::Key  (0xc)
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
class cTribeToolView_s00e9_2ca0 : public cSpatialObjectView {
public:
    cTribeToolView_s00e9_2ca0();                                    // 0x00e932a0
    ~cTribeToolView_s00e9_2ca0();                                   // 0x00e932d0
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
class cBabySackView : public cTribeToolView_s00e9_2ca0 {
public:
    void HandleSimulationUpdate(int a, int b);           // 0x00e939c0
};
int      GetCurrentGameMode_s00e9_2ca0();                        // 0x00b5b800
void*    GetGameTerrainCursor();                      // 0x00b30d70
void*    GameTimeManager();                           // 0x00b3d380
float    GameTimeManager_GetDelta(void* self);        // 0x00b31730
void*    sub_c9d9e0(void* p);                         // 0x00c9d9e0
cSpatialObjectView::~cSpatialObjectView()
{
}
// ---- items of slice s00e92ca0 end

// @ 0x00c91a40
void SP::cTribeToolView::UpdateModel(void)
{
    cTool *pTool = GetToolOfType(10);

    SP_ToolDesc desc;
    desc.id     = 0x1ae006ab;
    desc.param0 = 0;
    desc.param1 = 0xf37c24e6;

    if (GetCurrentGameMode() != &DAT_01654c02) {
        switch (GetModeVariant()) {
        case 0: desc.id = 0x9ce9ce8c; break;
        case 1: desc.id = 0x9ce9ce8f; break;
        case 2: desc.id = 0x9ce9ce8e; break;
        }
    } else {
        switch (GetModeVariant()) {
        case 0: desc.id = 0x1ae006ab; break;
        case 1: desc.id = 0x1ae006a8; break;
        case 2: desc.id = 0x1ae006a9; break;
        }
    }

    cModel *pModel = &pTool->mModel;
    pModel->SetDesc(&desc);
    pModel->SetWorld(GonzagoModelWorld());

    if (pModel->GetOwner() != 0) {
        cModelOwner *pOwner = (cModelOwner *)pModel->GetOwner();
        pOwner->mTool = pTool;
    }

    pTool->RefreshModel();
    pTool->UpdateTransform();
}

// @ 0x00d0c170
namespace SP {
bool __thiscall cTribeToolView_s00d0_c010::UpdateRotationSound()
{
    return false;
}
}  // namespace SP

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

    if (GetCurrentGameMode_s00e9_2ca0() == 0x1654c04) {
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
