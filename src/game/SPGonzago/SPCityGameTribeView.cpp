// src/game/SPGonzago/SPCityGameTribeView.cpp -- migrated from slice(s) s00e93c60 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCityGameTribeView.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Random/RandomLinearCongruential.h"
#include "SP/cSPTimer.h"
#include "SP/cTribe.h"

// unnamed retail callees and globals (address in the comment)
extern const float    kZeroPoint1;                           // 0x01488874  (0.1f)
#include <math.h>
#include <new>

// ---- items of slice s00e93c60 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV(n) virtual void pv##n();
struct Vec3 { float x, y, z; };
extern const float    kZeroPoint1;                           // 0x01488874  (0.1f)
Vec3*  FUN_00b6f0c0(void* obj);                              // 0x00b6f0c0
namespace SP {
class cSpatialObjectView;
}
namespace SP {
class cTribe_s00e9_3c60;
}
namespace SP {
class cTribeView;
}
namespace SP {
class cEffectsView;
}
namespace SP {
class cSPTimer_s00e9_3c60 {
 public:
    void               Start();                              // 0x00bc30f0
    void               Restart();                            // 0x00bc3130
    unsigned long long GetElapsedTime();                     // 0x00bc3190
    void               FUN_00bc3170();                       // 0x00bc3170
    uint8_t pad[0x20];
};
}
namespace SP {
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
}
namespace SP {
class cEffectsView {
 public:
    uint8_t  pad00[0x04];
    uint32_t mFlags_4;                                       // +0x04
    uint8_t  pad08[0x4c - 0x08];
    Vec3     mColor_4c;                                      // +0x4c
    float    mFloat_58;                                      // +0x58
    uint8_t  mState_5c;                                      // +0x5c
};
}
namespace SP {
class cTribeSubObj {
 public:
    PV(0)
    virtual void Slot4();                                    // +0x04
    PV(2)
    virtual void SlotC(int a);                               // +0x0c
    PV(4)
    virtual bool Slot10();                                   // +0x10
};
}
namespace SP {
class cTribe_s00e9_3c60 {
 public:
    PV(0) PV(1) PV(2)
    virtual void* AsInterface(uint32_t id);                  // +0x0c 0x00c8e420
    PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17)
    PV(18) PV(19) PV(20) PV(21)
    virtual void* GetTribe();                                // +0x58
    PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36)
    PV(37) PV(38) PV(39) PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46)
    virtual void* GetList();                                 // +0xbc
    uint8_t  pad00[0x34 - 0x04];
    cSpatial mSpatial;                                       // +0x34
    uint8_t  pad54[0x120 - (0x34 + sizeof(cSpatial))];
    cTribe_s00e9_3c60*  mpTribe_120;                                    // +0x120
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
}
namespace SP {
struct OpaqueModel { uint8_t b[0x11]; };
}
namespace SP {
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
    virtual cTribe_s00e9_3c60* AsInterface(uint32_t id);                // +0xb8
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
    cSPTimer_s00e9_3c60 mTimer_40;                                      // +0x40
    int      mState_60;                                      // +0x60
    uint8_t  pad64[0x78 - 0x64];
    cSPTimer_s00e9_3c60 mTimer_78;                                      // +0x78
    uint8_t  pad98[0x08];
    uint32_t mMovementSoundID_a0;                            // +0xa0
    uint8_t  padA4[0x0c];
    uint8_t  mbZoomOutScale_b0;                              // +0xb0

    void   MakeView_740(void* a, void* b, void* c, void* d); // 0x00e92740
    void   Init(void* a);                                    // 0x00e92910
    void   HandleSimulationUpdateBase(void* a, void* b);     // 0x00e92ca0
    cTribeView* CreateTribeView(cTribe_s00e9_3c60* iface);              // 0x00e93c60
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
}
namespace SP {
class cTribeView : public cSpatialObjectView {
 public:
    cTribeView();                                            // 0x00e93b80

    void Init(void* a, void* b, void* c, void* d);           // 0x00e94970
    void UpdateHighlight(cTribe_s00e9_3c60* param_2);                   // 0x00e93e10
    void UpdateDamageState(cTribe_s00e9_3c60* param_2, cTribe_s00e9_3c60* param_3);// 0x00e93f50
    void UpdateMatingEffect(cTribe_s00e9_3c60* param_2);                // 0x00e94450
    void HandleSimulationUpdate(void* a, void* b);           // 0x00e946b0
    void FUN_00e93160(int a, int b);                         // 0x00e93160
};
}
// ---- items of slice s00e93c60 end

// @ 0x00e93d70
namespace SP {
void cSpatialObjectView::SetupTribeView(void* a, void* b, void* c, void* d)
{
    MakeView_740(a, b, c, d);
    if (a == 0)
        return;
    cTribe_s00e9_3c60* t = (cTribe_s00e9_3c60*)((cTribe_s00e9_3c60*)a)->AsInterface(0xee02c7);
    if (t == 0)
        return;
    cTribe_s00e9_3c60* tribe = (cTribe_s00e9_3c60*)t->GetTribe();
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
}  // namespace SP
