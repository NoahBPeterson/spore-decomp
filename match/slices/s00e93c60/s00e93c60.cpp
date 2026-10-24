// Slice s00e93c60: Simulator view family (cSpatialObjectView / cTribeView / cVehicleView).
//   0x00e93c60  cSpatialObjectView::CreateTribeView (232 bytes) - allocates a cTribeView, copies the tribe's
//               colour into the view and hands the view's model to the tribe interface.
//   0x00e93d70  cSpatialObjectView::SetupTribeView  (149 bytes) - MakeView + colour/target-binding helper.
//   0x00e93e10  cTribeView::UpdateHighlight         (310 bytes) - highlight the tribe (and its children) when the
//               correct game mode + terrain cursor select it, and drive the highlight effect 0x50b2c616.
//   0x00e93f50  cTribeView::UpdateDamageState       (1272 bytes) - per-tribe damage/transition state machine.
//   0x00e94450  cTribeView::UpdateMatingEffect      (605 bytes) - drives the mating/love-heart effects.
//   0x00e946b0  cTribeView::HandleSimulationUpdate  (509 bytes) - base update + per-tribe view bookkeeping.
//   0x00e948b0 / 0x00e94900 / 0x00e94ad0            - stdcall effect-emitter loops.
//   0x00e94970  cTribeView::Init                    (70 bytes)
//   0x00e949c0  cVehicleView::Init                  (53 bytes)
//   0x00e94a00  cVehicleView::ToggleShowPaths       (16 bytes)
//   0x00e94a10  cEffectToggle::Update              (177 bytes)
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include <math.h>
#include <new>
#include "types.h"

#define PV(n) virtual void pv##n();

struct Vec3 { float x, y, z; };
struct Quat { float x, y, z, w; };

// --------------------------------------------------------------------- EA random
namespace EA { namespace Random {
class RandomLinearCongruential {
 public:
    uint32_t RandomUint32Uniform(uint32_t range);            // 0x00a68fb0
};
} }

// --------------------------------------------------------------------- global constants (read from the image)
extern EA::Random::RandomLinearCongruential sMathRandom;     // 0x01601760
extern uint8_t  gShowVehiclePaths;                           // 0x016c5c88
extern uint8_t  gGameModeSentinel;                           // 0x01654c04
extern const float    kZeroPoint1;                           // 0x01488874  (0.1f)
extern const float    kZeroPoint999;                         // 0x01486cd8  (0.999f)
extern const float    kExactlyOne;                           // 0x01485720  (1.0f)
extern const float    kEpsilon;                              // 0x013ec4b8  (1e-8f)
extern const float    kQuarter;                              // 0x013ec480  (0.2f)
extern const float    kOneThousandTwentyFour;                // 0x013ef574  (1024.0f)
extern const float    kTwenty;                               // 0x013eecd8  (20.0f)
extern const float    kEmitterDivisor;                       // 0x015a8aac
extern float    kDamageScaleA;                               // 0x016c5c7c
extern float    kDamageScaleB;                               // 0x016c5c80
extern uint32_t kDamageScaleFlags;                           // 0x016c5c84
extern const Vec3     kDefaultOffset;                        // 0x016c5c70
extern uint32_t kEffectId3c;                                 // 0x015a8a3c
extern uint32_t kEffectId40;                                 // 0x015a8a40
extern uint32_t kEffectId44;                                 // 0x015a8a44

void* operator_new(size_t size, const char* name, int a, int b, int c, int d);  // 0x00f473a0

float* Matrix3FromQuaternion(float* out, const Quat* q);     // 0x0059c190
void*  GonzagoModelWorld(void* model, const Vec3* color);    // 0x00b3d520
void*  GetCurrentGameMode();                                 // 0x00b5b800
void*  GetGameTerrainCursor();                               // 0x00b30d70
Vec3*  FUN_00b6f0c0(void* obj);                              // 0x00b6f0c0
int    FUN_00a1ad10();                                       // 0x00a1ad10
void   FUN_00c91970();                                       // 0x00c91970
void   FUN_00c9a960();                                       // 0x00c9a960

namespace SP {

class cSpatialObjectView;
class cTribe;
class cTribeView;
class cVehicleView;
class cEmitter;
class cEffectTarget;
class cEffectsView;
class cSimSingleton;
class cDamageState;

// --------------------------------------------------------------------- Matrix3
class Matrix3 {
 public:
    float m[9];
    Matrix3() {}
    Matrix3(const Matrix3& src);                             // 0x0041cb40
    void Assign(const Matrix3* src);                         // 0x0041cb40
};

extern const Matrix3 kDefaultRotationMatrix;                 // 0x016c5c4c

// --------------------------------------------------------------------- cSPTimer
class cSPTimer {
 public:
    void               Start();                              // 0x00bc30f0
    void               Restart();                            // 0x00bc3130
    unsigned long long GetElapsedTime();                     // 0x00bc3190
    void               FUN_00bc3170();                       // 0x00bc3170
    uint8_t pad[0x20];
};

// --------------------------------------------------------------------- the embedded spatial sub-object (at cTribe+0x34,
//                                                                     and at each tribe child +0x34)
class cSpatial {
 public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual const Vec3* GetPosition();                       // +0x2c
    PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25)
    virtual float* GetBounds();                              // +0x68
    PV(27) PV(28) PV(29) PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36)
    virtual void  SetPos(const Vec3* p);                     // +0x94
    virtual Vec3* GetVec3();                                 // +0x98
    PV(39) PV(40) PV(41) PV(42)
    virtual cEffectsView* GetEffectsView();                  // +0xac
    virtual void* SlotB0();                                  // +0xb0
    uint8_t pad[0x1c];
};

// --------------------------------------------------------------------- the "effect list item" pushed at +4 flags / +0x4c colour / +0x5c state
class cEffectsView {
 public:
    uint8_t  pad00[0x04];
    uint32_t mFlags_4;                                       // +0x04
    uint8_t  pad08[0x4c - 0x08];
    Vec3     mColor_4c;                                      // +0x4c
    float    mFloat_58;                                      // +0x58
    uint8_t  mState_5c;                                      // +0x5c
};

// --------------------------------------------------------------------- the emitter object (vtable +0x64/+0x70/+0x74/+0x7c)
class cEmitter {
 public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12)
    PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24)
    virtual int  EmitterCount(void* target);                 // +0x64
    PV(26) PV(27)
    virtual void EmitterAdd(void* target, uint32_t id, int mode, float f, int i);   // +0x70
    virtual void EmitterAdd2(void* target, uint32_t id, float f, int i);            // +0x74
    PV(30)
    virtual void EmitterScale(void* target, float f);        // +0x7c
};

// --------------------------------------------------------------------- the effect target (flags dword at +4)
struct cEffectFlags {
    uint32_t mBit0_13  : 14;
    uint32_t mBit14    : 1;                                  // visibility / hold flag
    uint32_t mBit15_17 : 3;
    uint32_t mBit18    : 1;                                  // "hidden" flag
    uint32_t mBit19_31 : 13;
};

class cEffectTarget {
 public:
    uint8_t  pad00[0x04];
    cEffectFlags mFlags_4;                                   // +0x04
};

// --------------------------------------------------------------------- object at cTribe+0x2d0
class cTribeSubObj {
 public:
    PV(0)
    virtual void Slot4();                                    // +0x04
    PV(2)
    virtual void SlotC(int a);                               // +0x0c
    PV(4)
    virtual bool Slot10();                                   // +0x10
};

// --------------------------------------------------------------------- cTribe (the value returned by AsInterface/GetTribe)
class cTribe {
 public:
    PV(0) PV(1) PV(2)
    virtual void* AsInterface(uint32_t id);                  // +0x0c
    PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17)
    PV(18) PV(19) PV(20) PV(21)
    virtual void* GetTribe();                                // +0x58
    PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36)
    PV(37) PV(38) PV(39) PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46)
    virtual void* GetList();                                 // +0xbc
    uint8_t  pad00[0x34 - 0x04];
    cSpatial mSpatial;                                       // +0x34
    uint8_t  pad54[0x120 - (0x34 + sizeof(cSpatial))];
    cTribe*  mpTribe_120;                                    // +0x120
    uint8_t  pad124[0x170 - 0x124];
    uint32_t mFlags_170;                                     // +0x170
    uint8_t  pad174[0x1e8 - 0x174];
    Vec3     mPosA_1e8;                                      // +0x1e8
    Vec3     mPosB_1f4;                                      // +0x1f4
    Vec3     mPosC_200;                                      // +0x200
    Vec3     mPosD_20c;                                      // +0x20c
    uint8_t  mByte_218;                                      // +0x218
    uint8_t  pad219[0x21c - 0x219];
    int      mInt_21c;                                       // +0x21c
    uint8_t  pad220[0x234 - 0x220];
    void*    mpObj_234;                                      // +0x234
    uint8_t  pad238[0x2d0 - 0x238];
    cTribeSubObj* mpSub_2d0;                                 // +0x2d0
    uint8_t  pad2d4[0x556 - 0x2d4];
    uint8_t  mByte_556;                                      // +0x556

    bool FUN_00c9bf10();                                     // 0x00c9bf10
    int  FUN_00a1ad10b();                                    // 0x00a1ad10
    void ChooseNewHutModel();                                // 0x00c99c30
};

// --------------------------------------------------------------------- cSpatialObjectView (base of cTribeView / cVehicleView,
//                                                                        and the type of cSpatialObjectView::mpObject)
struct OpaqueModel { uint8_t b[0x11]; };

class cSpatialObjectView {
 public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
    virtual bool  Slot24();                                  // +0x24
    virtual void  Slot28(void* a, void* model);              // +0x28
    virtual cEffectsView* Slot2c();                          // +0x2c
    virtual void* Slot30();                                  // +0x30
    PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21)
    virtual void* Slot58();                                  // +0x58
    PV(23) PV(24) PV(25)
    virtual float* Slot68();                                 // +0x68
    PV(27) PV(28) PV(29) PV(30) PV(31) PV(32) PV(33)
    virtual bool  Slot88();                                  // +0x88
    PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42)
    virtual cEffectsView* SlotAC();                          // +0xac
    virtual void* SlotB0();                                  // +0xb0
    PV(45)
    virtual cTribe* AsInterface(uint32_t id);                // +0xb8
    virtual void* SlotBC();                                  // +0xbc
    PV(48)
    virtual void  SlotC4(cEffectsView* e, int a, int b, int c);  // +0xc4

    uint8_t  pad04[0x08];
    cSpatialObjectView* mpObject;                            // +0x0c
    uint8_t  pad10[0x08];
    Vec3     mColor;                                         // +0x18
    OpaqueModel mModel_24;                                   // +0x24
    uint8_t  mbTransition_35;                                // +0x35
    uint8_t  pad36[0x02];
    uint32_t mTimerTarget_38;                                // +0x38
    uint32_t mTimerTargetHi_3c;                              // +0x3c
    cSPTimer mTimer_40;                                      // +0x40
    int      mState_60;                                      // +0x60
    uint8_t  pad64[0x78 - 0x64];
    cSPTimer mTimer_78;                                      // +0x78
    uint8_t  pad98[0x08];
    uint32_t mMovementSoundID_a0;                            // +0xa0
    uint8_t  padA4[0x0c];
    uint8_t  mbZoomOutScale_b0;                              // +0xb0

    void   MakeView_740(void* a, void* b, void* c, void* d); // 0x00e92740
    void   Init(void* a);                                    // 0x00e92910
    void   HandleSimulationUpdateBase(void* a, void* b);     // 0x00e92ca0
    cTribeView* CreateTribeView(cTribe* iface);              // 0x00e93c60
    void   SetupTribeView(void* a, void* b, void* c, void* d); // 0x00e93d70

    bool   GetEffect(uint32_t id);                           // 0x00c88910
    bool   IsEffectActive(uint32_t id);                      // 0x00c88940
    void   EnableEffect(uint32_t id, int on);                // 0x00c8ad30
    void*  CreateEffect(uint32_t id, int a, uint32_t id2);   // 0x00c8b130
    void*  GetEffectObj(uint32_t id);                        // 0x00c888e0
    void   RemoveEffect(uint32_t id);                        // 0x00c8b1a0
    void   SetEffectFloatA(uint32_t id, float f);            // 0x00c88a00
    void   SetEffectFloatB(uint32_t id, float f);            // 0x00c8a020
    void   SetEffectX(uint32_t id);                          // 0x00c8b210
};

// --------------------------------------------------------------------- cTribeView
class cTribeView : public cSpatialObjectView {
 public:
    cTribeView();                                            // 0x00e93b80

    void Init(void* a, void* b, void* c, void* d);           // 0x00e94970
    void UpdateHighlight(cTribe* param_2);                   // 0x00e93e10
    void UpdateDamageState(cTribe* param_2, cTribe* param_3);// 0x00e93f50
    void UpdateMatingEffect(cTribe* param_2);                // 0x00e94450
    void HandleSimulationUpdate(void* a, void* b);           // 0x00e946b0
    void FUN_00e93160(int a, int b);                         // 0x00e93160
};

// --------------------------------------------------------------------- cVehicleView
class cVehicleView : public cSpatialObjectView {
 public:
    void Init(void* a);                                      // 0x00e949c0
    void ToggleShowPaths();                                  // 0x00e94a00
};

// --------------------------------------------------------------------- tiny effect toggle holder (byte flag at +0)
class cEffectToggle {
 public:
    uint8_t mbActive;                                        // +0x00
    void Update(int a2, float t, float f2, cEmitter* emitter, cEffectTarget* target); // 0x00e94a10
};

// --------------------------------------------------------------------- cSimSingleton
class cSimSingleton {
 public:
    cSimSingleton();                                         // 0x00ae5c30
    bool FUN_00ae3d40(cTribe* tribe);                        // 0x00ae3d40
};
extern cSimSingleton* gSimSingleton;                         // 0x0167a60c

// --------------------------------------------------------------------- stdcall emitter helpers
void __stdcall FUN_00e948b0(cEmitter* self, cEffectTarget* target);              // 0x00e948b0
void __stdcall FUN_00e94900(cEmitter* self, cEffectTarget* target);              // 0x00e94900
void __stdcall FUN_00e94ad0(cEmitter* self, cEffectTarget* target, int i);       // 0x00e94ad0

// ===================================================================== 0x00e93c60
// Allocate a cTribeView for the tribe behind the interface object, copy the tribe's
// colour into the view and hand the freshly-built model to the interface.
// @ 0x00e93c60
cTribeView* cSpatialObjectView::CreateTribeView(cTribe* iface)
{
    void* mem = operator_new(0x68, "Simulator/cTribeView", 0, 0, 0, 0);
    cTribeView* view = mem ? new(mem) cTribeView() : 0;
    cTribe* t = iface ? (cTribe*)iface->AsInterface(0xee02c7) : 0;
    cTribe* tribe = t ? (cTribe*)t->GetTribe() : 0;
    if (tribe)
    {
        mColor = *FUN_00b6f0c0(tribe->mpObj_234);
    }
    Vec3* sp = t->mSpatial.GetVec3();
    if (sp->x == 0.0f && sp->y == 0.0f && sp->z == 0.0f)
    {
        view->Slot28(iface, GonzagoModelWorld(&mModel_24, &mColor));
        return view;
    }
    view->Slot28(iface, GonzagoModelWorld(t->mSpatial.GetVec3(), &mColor));
    return view;
}

// ===================================================================== 0x00e93d70
// MakeView then bind the tribe's colour/target into the view's effect list item.
// @ 0x00e93d70
void cSpatialObjectView::SetupTribeView(void* a, void* b, void* c, void* d)
{
    MakeView_740(a, b, c, d);
    if (a == 0)
        return;
    cTribe* t = (cTribe*)((cTribe*)a)->AsInterface(0xee02c7);
    if (t == 0)
        return;
    cTribe* tribe = (cTribe*)t->GetTribe();
    cEffectsView* e = Slot2c();
    if (tribe != 0)
    {
        if (e != 0)
        {
            mColor = *FUN_00b6f0c0(tribe->mpObj_234);
            e->mFlags_4 |= 4;
        }
        return;
    }
    if (e != 0)
        e->mFloat_58 = kZeroPoint1;
}

// ===================================================================== 0x00e93e10
// Highlight the tribe (and its children) when the right game mode + terrain cursor selects it,
// then drive the 0x50b2c616 highlight effect.
// @ 0x00e93e10
void cTribeView::UpdateHighlight(cTribe* param_2)
{
    bool sel = mpObject->Slot24();
    cEffectsView* e = mpObject->SlotAC();
    void* mode = GetCurrentGameMode();
    if (mode == &gGameModeSentinel && e != 0)
    {
        bool cursor = false;
        void* cur = GetGameTerrainCursor();
        if (cur != 0)
            cursor = (*(bool (__thiscall**)(void*))(*(uint32_t*)cur + 0xa8))(cur);
        sel = sel & (cursor == false);
        if (sel == 0)
        {
            e->mFlags_4 &= 0xfffffff7;
        }
        else
        {
            e->mFlags_4 |= 8;
            e->mState_5c = 2;
        }
        void** list = (void**)param_2->GetList();
        for (void** it = (void**)list[0]; it != (void**)list[1]; ++it)
        {
            cSpatial* sp = (cSpatial*)*(void**)((char*)*it + 0x34);
            cEffectsView* ce;
            if (sel == 0)
            {
                ce = sp->GetEffectsView();
                ce->mFlags_4 &= 0xfffffff7;
            }
            else
            {
                ce = sp->GetEffectsView();
                ce->mFlags_4 |= 8;
                ce = sp->GetEffectsView();
                ce->mState_5c = 2;
            }
        }
    }
    bool active = (*(bool (__thiscall**)(void*))((char*)param_2->mpTribe_120 + 0x58))(param_2->mpTribe_120);
    cSpatialObjectView* obj = mpObject;
    if (active == 0)
    {
        if (obj->GetEffect(0x50b2c616))
            obj->EnableEffect(0x50b2c616, 1);
    }
    else
    {
        if (obj->GetEffect(0x50b2c616) == 0)
        {
            obj->CreateEffect(0x50b2c616, 0, 0x44c5ccd5);
            return;
        }
    }
}

// ===================================================================== 0x00e93f50
// Per-tribe damage/transition state machine.
// @ 0x00e93f50
void cTribeView::UpdateDamageState(cTribe* param_2, cTribe* param_3)
{
    int mode = param_2->FUN_00a1ad10b();
    uint32_t id;
    if (mode == 0)
        id = 0x79610ed9;
    else if (mode == 1)
        id = 0x5de08196;
    else
        id = 0x4ae13146;

    if (param_2->FUN_00c9bf10() == 0 || mpObject->IsEffectActive(id))
    {
        if (param_2->FUN_00c9bf10() == 0 && mpObject->IsEffectActive(id))
            mpObject->EnableEffect(id, 1);
    }
    else
    {
        mpObject->RemoveEffect(id);
        void* e = mpObject->GetEffectObj(id);
        Vec3 off = kDefaultOffset;
        Matrix3 rot(kDefaultRotationMatrix);
        const Vec3* pos = param_2->mSpatial.GetPosition();
        float len;
        {
            Vec3 dir = *pos;
            float inv = 1.0f / sqrtf(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z + kEpsilon);
            dir.x *= inv;
            dir.y *= inv;
            dir.z *= inv;
            float* b = mpObject->Slot68();
            float h = b[5];
            off.x += dir.x * h;
            off.y += dir.y * h;
            off.z += dir.z * h;
            len = h;
        }
        Quat* q = (Quat*)mpObject->Slot30();
        float rot3[9];
        Matrix3FromQuaternion(rot3, q);
        for (int i = 0; i < 9; ++i)
            rot.m[i] = rot3[i];
        (void)len;
        (void)e;
    }

    if ((kDamageScaleFlags & 1) == 0)
    {
        kDamageScaleFlags |= 1;
        kDamageScaleB = 0.0f;
    }
    if ((kDamageScaleFlags & 2) == 0)
    {
        kDamageScaleFlags |= 2;
        kDamageScaleA = 0.0f;
    }

    float t = 0.0f;
    int state;
    if (t > 0.0f)
    {
        if (kDamageScaleA <= t)
        {
            if (kDamageScaleB <= t)
            {
                state = 2;
                if (kZeroPoint999 <= t)
                    state = 1;
            }
            else
            {
                state = 3;
            }
        }
        else
        {
            state = 4;
        }
    }
    else
    {
        state = 5;
    }

    int old = mState_60;
    bool changed = false;
    if (state != old)
    {
        if (old == 0 || state == 1)
        {
            changed = true;
        }
        else if (state == 5)
        {
            mbTransition_35 = 1;
            mTimer_40.Restart();
            mTimerTarget_38 = 0x12c;
            mTimerTargetHi_3c = 0;
            int mode2 = param_3->FUN_00a1ad10b();
            uint32_t id2;
            if (mode2 == 0)
                id2 = 0x8324e848;
            else if (mode2 == 1)
                id2 = 0x47604335;
            else
                id2 = 0xa4f54965;
            mpObject->EnableEffect(id2, 1);
            mpObject->SetEffectX(id2);
        }
        else
        {
            mbTransition_35 = 0;
            changed = true;
        }
    }

    if (mbTransition_35 != 0)
    {
        unsigned long long el = mTimer_40.GetElapsedTime();
        uint32_t hi = (uint32_t)(el >> 32);
        uint32_t lo = (uint32_t)el;
        if (hi >= mTimerTargetHi_3c && (hi > mTimerTargetHi_3c || lo > mTimerTarget_38))
        {
            mTimer_40.FUN_00bc3170();
            mbTransition_35 = 0;
            changed = true;
        }
    }

    void* mode3 = GetCurrentGameMode();
    if (mode3 == &gGameModeSentinel)
    {
        if (gSimSingleton == 0)
        {
            void* mem = operator_new(0xc8, "Simulator/SimSingleton", 0, 0, 0, 0);
            gSimSingleton = mem ? new(mem) cSimSingleton() : 0;
        }
        if (gSimSingleton->FUN_00ae3d40(param_3))
        {
            mState_60 = state;
            return;
        }
    }

    if (!changed)
    {
        mState_60 = state;
        return;
    }

    Vec3 target;
    target.x = target.y = target.z = 0.0f;
    switch (state)
    {
    case 1:
        target = param_2->mPosD_20c;
        break;
    case 2:
        target = param_2->mPosA_1e8;
        break;
    case 3:
        target = param_2->mPosB_1f4;
        break;
    case 4:
        target = param_2->mPosC_200;
        break;
    case 5:
        target.x = -1290983.8f;
        target.y = 1.6318384e-38f;
        target.z = 1.6441538e-12f;
        break;
    default:
        param_2->ChooseNewHutModel();
        mState_60 = state;
        return;
    }
    if (target.x != 0.0f)
    {
        param_2->mSpatial.SetPos(&target);
        mState_60 = state;
        return;
    }
    param_2->ChooseNewHutModel();
    mState_60 = state;
}

// ===================================================================== 0x00e94450
// Drives the mating / love-heart effects on the tribe.
// @ 0x00e94450
void cTribeView::UpdateMatingEffect(cTribe* param_2)
{
    if (param_2->mByte_218 == 0 && param_2->mInt_21c < 1)
    {
        FUN_00e93160(0, 0);
        if (mpObject->GetEffect(0x50b2c615))
            mpObject->EnableEffect(0x50b2c615, 1);
        if (mpObject->GetEffect(0x50b2c617))
        {
            mpObject->EnableEffect(0x50b2c617, 1);
            return;
        }
    }
    else
    {
        FUN_00e93160(1, 0);
        uint32_t id;
        if (param_2->mByte_218 == 0)
        {
            if (mpObject->GetEffect(0x50b2c617))
                return;
            mpObject->CreateEffect(0x50b2c617, 0, 0x55d8efe6);
            id = 0x50b2c617;
        }
        else
        {
            if (mpObject->GetEffect(0x50b2c615))
                return;
            mpObject->CreateEffect(0x50b2c615, 0, 0xe0a5a6c2);
            id = 0x50b2c615;
        }
        cEffectsView* e = (cEffectsView*)mpObject->GetEffectObj(id);
        if (e != 0)
        {
            Vec3 pos;
            pos.x = 0.0f;
            pos.y = kDefaultOffset.x;
            pos.z = kDefaultOffset.y;
            e->mFlags_4 |= 4;
            e->mState_5c = 2;
            (void)pos;
            float* b = (float*)param_2->mSpatial.GetBounds();
            float scale = b[5] - b[2];
            const Vec3* p = param_2->mSpatial.GetPosition();
            float inv = 1.0f / sqrtf(p->x * p->x + p->y * p->y + p->z * p->z + kEpsilon);
            e->mColor_4c.x = p->x * inv * scale + pos.x;
            e->mColor_4c.y = p->y * inv * scale + pos.y;
            e->mColor_4c.z = p->z * inv * scale + pos.z;
        }
    }
}

// ===================================================================== 0x00e946b0
// Base update plus per-tribe view bookkeeping.
// @ 0x00e946b0
void cTribeView::HandleSimulationUpdate(void* a, void* b)
{
    bool sel = mpObject->Slot88();
    HandleSimulationUpdateBase(a, b);
    cTribe* iface = mpObject ? mpObject->AsInterface(0xee02c7) : 0;
    cTribe* tribe = iface ? (cTribe*)iface->GetTribe() : 0;
    if (tribe != 0)
    {
        UpdateHighlight(tribe);
        FUN_00c91970();
        UpdateDamageState(iface, tribe);
        UpdateMatingEffect(iface);
        cEffectsView* e = mpObject->SlotAC();
        if (e != 0)
        {
            if (sel != 0)
            {
                e->mFlags_4 |= 4;
                e->mColor_4c.x = mColor.x;
                e->mColor_4c.y = mColor.y;
                e->mColor_4c.z = mColor.z;
            }
            if (tribe->mByte_556 == 0 || mState_60 > 2)
            {
                void* w = iface->mSpatial.SlotB0();
                (*(void (__thiscall**)(void*, cEffectsView*, int, int, int))(*(uint32_t*)w + 0xc4))(w, e, 1, 1, 0);
            }
            else
            {
                void* w = iface->mSpatial.SlotB0();
                (*(void (__thiscall**)(void*, cEffectsView*, int, int, int))(*(uint32_t*)w + 0xc4))(w, e, 0, 1, 0);
                e->mColor_4c.x = kQuarter;
                e->mColor_4c.y = kQuarter;
                e->mColor_4c.z = kQuarter;
            }
            if (tribe->mpSub_2d0 != 0)
            {
                if (tribe->mpSub_2d0->Slot10() == 0)
                {
                    e->mFlags_4 |= 1;
                    tribe->mpSub_2d0->SlotC(1);
                    if (tribe->mpSub_2d0 != 0)
                    {
                        cTribeSubObj* o = tribe->mpSub_2d0;
                        tribe->mpSub_2d0 = 0;
                        o->Slot4();
                    }
                }
                else if (sel != 0)
                {
                    e->mFlags_4 &= 0xfffffffe;
                }
            }
        }
        FUN_00c9a960();
    }
    if ((tribe->mFlags_170 & 0x800) != 0)
    {
        if (mpObject->GetEffect(0x5de3b92) == 0)
        {
            mpObject->CreateEffect(0x5de3b92, 0, 0x56192017);
            mpObject->SetEffectFloatA(0x5de3b92, kOneThousandTwentyFour);
            mpObject->SetEffectFloatB(0x5de3b92, kTwenty);
        }
        tribe->mFlags_170 &= 0xfffff7ff;
        return;
    }
    if (mpObject->GetEffect(0x5de3b92))
        mpObject->EnableEffect(0x5de3b92, 1);
}

// ===================================================================== 0x00e948b0
// @ 0x00e948b0
void __stdcall FUN_00e948b0(cEmitter* self, cEffectTarget* target)
{
    if (self == 0)
        return;
    if (target == 0)
        return;
    int n = self->EmitterCount(target);
    for (int i = 0; i < n; ++i)
        self->EmitterAdd(target, kEffectId3c, 0, 0.0f, i);
}

// ===================================================================== 0x00e94900
// @ 0x00e94900
void __stdcall FUN_00e94900(cEmitter* self, cEffectTarget* target)
{
    if (self == 0)
        return;
    if (target == 0)
        return;
    int n = self->EmitterCount(target);
    for (int i = 0; i < n; ++i)
    {
        self->EmitterAdd(target, kEffectId3c, 1, 0.0f, i);
        self->EmitterAdd2(target, kEffectId3c, 0.0f, i);
    }
}

// ===================================================================== 0x00e94970
// @ 0x00e94970
void cTribeView::Init(void* a, void* b, void* c, void* d)
{
    MakeView_740(a, b, c, d);
    mbZoomOutScale_b0 = 0;
    mTimer_78.Start();
    mMovementSoundID_a0 = sMathRandom.RandomUint32Uniform(0x188b);
}

// ===================================================================== 0x00e949c0
// @ 0x00e949c0
void cVehicleView::Init(void* a)
{
    cSpatialObjectView::Init(a);
    mbZoomOutScale_b0 = 0;
    mTimer_78.Start();
    mMovementSoundID_a0 = sMathRandom.RandomUint32Uniform(0x188b);
}

// ===================================================================== 0x00e94a00
// @ 0x00e94a00
void cVehicleView::ToggleShowPaths()
{
    gShowVehiclePaths = (gShowVehiclePaths == 0);
}

// ===================================================================== 0x00e94a10
// @ 0x00e94a10
void cEffectToggle::Update(int a2, float t, float f2, cEmitter* emitter, cEffectTarget* target)
{
    (void)a2;
    if (target == 0)
        return;
    if (target->mFlags_4.mBit14 == 0)
        return;
    if (target->mFlags_4.mBit18 != 0)
        return;
    if (kZeroPoint1 < t)
    {
        if (mbActive == 0)
        {
            FUN_00e948b0(emitter, target);
            mbActive = 1;
        }
        emitter->EmitterScale(target, (f2 / kEmitterDivisor) * (t / f2));
        return;
    }
    if (mbActive != 0)
    {
        FUN_00e94900(emitter, target);
        mbActive = 0;
        emitter->EmitterScale(target, kExactlyOne);
    }
}

// ===================================================================== 0x00e94ad0
// @ 0x00e94ad0
void __stdcall FUN_00e94ad0(cEmitter* self, cEffectTarget* target, int i)
{
    if (self == 0)
        return;
    if (target == 0)
        return;
    if (target->mFlags_4.mBit14 == 0)
        return;
    self->EmitterAdd2(target, kEffectId44, 0.0f, i);
    self->EmitterAdd(target, kEffectId44, 0, 0.0f, i);
    self->EmitterAdd2(target, kEffectId40, 0.0f, i);
    self->EmitterAdd(target, kEffectId40, 2, 0.0f, i);
}

}  // namespace SP