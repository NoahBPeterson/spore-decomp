// src/game/SPGonzago/SPSpaceGameBehaviorSlowDeath.cpp -- migrated from slice(s) s01033de0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPSpaceGameBehaviorSlowDeath.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPCreatureBase.h"
#include "SP/cPlanetModel.h"
#include "SP/cSPTimer.h"
#include "EA/Variant.h"
#include "SP/cSolarSystem.h"
#include <math.h>

// ---- items of slice s01033de0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV(n) virtual void pv##n();
struct Vec3 { float x, y, z; };
#define G_STR_16DF2F8    ((void*)0x016df2f8)
#define G_STR_SIMULATOR  ((void*)0x013f09b4)
#define G_VT_BEHAVIOUR_A ((uint32_t)0x01499810)
#define G_VT_BEHAVIOUR_B ((uint32_t)0x01499800)
void* operator_new(uint32_t size, void* name, int a, int b, int c, int d);   // 0x00f473a0
void  operator_delete_array(void* p);                                        // 0x00f47380
struct PlanetModel {
    Vec3* DirectionToSurfacePosition(Vec3* out, const Vec3* pos);            // 0x00b815a0
};
PlanetModel* GetPlanetModel();                                               // 0x00b3d350
struct Iface {                                  // reference-counted interface (+0x00 vtable)
    PV(0)
    virtual void pv1();                         // +0x04  Release
    virtual void pv2(int value);                // +0x08
    virtual void pv3(int value);                // +0x0c
    virtual bool pv4();                         // +0x10
};
struct ObjA0 {                                  // object looked up at +0xa0
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
    PV(30) PV(31) PV(32)
    virtual void pv33(void* name, uint32_t value);   // +0x84
};
struct TuningSource {                           // object pointed at by +0x13c
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
    virtual bool pv9(uint32_t key, void** out); // +0x24
    virtual uint32_t pv10(uint32_t value);      // +0x28
};
struct Loco {                                   // locomotion sub-object
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual Vec3* pv11();                       // +0x2c  GetPosition
    PV(12) PV(13)
    virtual void pv14(const Vec3* pos);         // +0x38
    void FUN_c41d60(void* str);                 // 0x00c41d60
    void FUN_c41d90(void* str);                 // 0x00c41d90
};
struct Queryable {                              // object returned by the behaviour's vt+0x58 slot
    PV(0) PV(1)
    virtual Queryable* pv2(uint32_t tag);       // +0x08
    PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15)
    PV(16) PV(17) PV(18) PV(19) PV(20)
    virtual void pv21();                        // +0x54
    PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30) PV(31)
    PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41)
    PV(42) PV(43) PV(44) PV(45) PV(46) PV(47) PV(48) PV(49)
    virtual void pv50(int value);               // +0xc8
    uint8_t mPad04_to_c0[0xc0 - 0x04];
    Loco    mLoco;                              // +0xc0 (embedded sub-object)
    uint8_t mPadC4[0x130 - 0xc4];
    uint8_t mFlag130;                           // +0x130
};
struct SlowDeathTimer {                         // SP::cGonzagoTimer (0x20 bytes)
    uint8_t mPad00[0x20];
    void ctor();                                // 0x00b63890
    void dtor();                                // 0x00b638b0
    void Restart();                             // 0x00bc3130  (this == &mTimer, cSPTimer::Restart)
};
struct SlowDeathCore {                          // 0xa0-byte cInteraction-derived behaviour object
    uint32_t mVt0;                              // +0x00
    uint32_t mVt4;                              // +0x04
    uint8_t  mPad08[0x74 - 0x08];
    int32_t  mMode;                             // +0x74
    SlowDeathTimer mTimer;                      // +0x78
    int32_t  mAnimId;                           // +0x98
    uint8_t  mPad9C[0xa0 - 0x9c];

    void baseCtor();                            // 0x00abf320
    void baseDtor();                            // 0x00abf190

    void* FUN_01033e60(uint8_t del);
};
struct AgentRefChunk;                           // blocks of the agent reference table
struct AgentRefEntry {                          // 8-byte entry inside a block
    void*    mAgent;                            // +0x00
    uint32_t mType;                             // +0x04
};
struct AgentRefChunk {
    uint32_t      mCount;                       // +0x00
    AgentRefEntry mEntries[1];                  // +0x04
};
struct AgentRef {                               // argument of RemoveAgent
    AgentRefChunk** mChunks;                    // +0x00
};
struct RemoveArgs {                             // 0x18-byte argument block of cInteraction::RemoveAgent
    void*    mRef;                              // +0x00
    uint32_t mIndex;                            // +0x04
    int32_t  mA;                                // +0x08
    int32_t  mB;                                // +0x0c
    int32_t  mC;                                // +0x10
    int32_t  mD;                                // +0x14
};
struct Behavior {                               // large behaviour/editor subject
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    PV(20) PV(21)
    virtual Queryable* pv22();                  // +0x58

    uint32_t mVt4;                              // +0x04
    uint8_t  mPad08[0x60 - 0x08];
    Iface*   mIface60;                          // +0x60
    Iface*   mIface64;                          // +0x64
    Iface*   mIface68;                          // +0x68
    uint8_t  mPad6C[0x74 - 0x6c];
    int32_t  m74;                               // +0x74
    uint8_t  mPad78[0x90 - 0x78];
    Iface*   mIface90;                          // +0x90
    uint8_t  mPad94[0x98 - 0x94];
    int32_t  m98;                               // +0x98
    uint8_t  mPad9C[0xa0 - 0x9c];
    ObjA0*   mObjA0;                            // +0xa0
    uint8_t  mPadA4[0x130 - 0xa4];
    uint8_t  m130;                              // +0x130
    uint8_t  mPad131[0x13c - 0x131];
    TuningSource* mTuning13C;                   // +0x13c

    bool FUN_00abf640(int value);               // 0x00abf640
    void baseRemoveAgent(RemoveArgs args);      // 0x00abedb0

    int  FUN_01033f50();
    void FUN_01034260(int deathType);
    void FUN_01034950(int mode, int unused);
    void FUN_01034b90(void* star);

    bool   FUN_01033ea0(int value);
    void   RemoveAgent(AgentRef* ref, uint32_t index, int a2, int a3, int a4, int a5);
    void   FUN_010346e0();
    void   FUN_010347e0();
    void   FUN_01034810();
    void   FUN_01034840();
    void   FUN_01034880();
};
// ---- items of slice s01033de0 end

// @ 0x01033de0
void* FUN_01033de0()
{
    SlowDeathCore* p = (SlowDeathCore*)operator_new(0xa0, G_STR_SIMULATOR, 0, 0, 0, 0);
    if (p != 0) {
        p->baseCtor();
        p->mVt0 = G_VT_BEHAVIOUR_A;
        p->mVt4 = G_VT_BEHAVIOUR_B;
        p->mMode = 0;
        p->mTimer.ctor();
        p->mAnimId = 0;
        return p;
    }
    return 0;
}

// @ 0x01033e60
void* SlowDeathCore::FUN_01033e60(uint8_t del)
{
    mVt0 = G_VT_BEHAVIOUR_A;
    mVt4 = G_VT_BEHAVIOUR_B;
    mTimer.dtor();
    baseDtor();
    if ((del & 1) != 0) {
        operator_delete_array(this);
    }
    return this;
}

// @ 0x01033ea0
bool Behavior::FUN_01033ea0(int value)
{
    bool result = FUN_00abf640(value);
    Queryable* owner = pv22();
    if (owner != 0) {
        Queryable* agent = owner->pv2(0xce9f6639);
        if (agent != 0) {
            agent->pv21();
            Loco* loco = &agent->mLoco;
            Vec3 point;
            loco->pv14(GetPlanetModel()->DirectionToSurfacePosition(&point, loco->pv11()));
            agent->mFlag130 = 0;
            loco->FUN_c41d60(G_STR_16DF2F8);
            loco->FUN_c41d90(G_STR_16DF2F8);
        }
    }
    return result;
}

// @ 0x010345b0
void Behavior::RemoveAgent(AgentRef* ref, uint32_t index, int a2, int a3, int a4, int a5)
{
    void* agent = ref->mChunks[index >> 7]->mEntries[index & 0x7f].mAgent;
    RemoveArgs args;
    args.mRef = ref;
    args.mIndex = index;
    args.mA = a2;
    args.mB = a3;
    args.mC = a4;
    args.mD = a5;
    baseRemoveAgent(args);
    if (agent != 0) {
        Queryable* query = ((Queryable*)agent)->pv2(0xce9f6639);
        if (query != 0) {
            query->pv50(0);
        }
    }
}
