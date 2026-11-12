// src/game/SPGonzago/_at_00c90000.cpp -- migrated from slice(s) s00c9c1b0, s00c9afb0, s00c982a0 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00c90000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cActionCircle.h"
#include "SP/cGameData.h"
#include "SP/cPropertyManager.h"
#include "SP/cReservationGrid.h"
#include "SP/cSpatialObject.h"
#include <math.h>
#include "SP/cGameNounManager.h"
#include "SP/cPlanetModel.h"
#include "SP/cCombatant.h"
#include "SP/cGonzagoTimer.h"
#include "SP/cInteractionTarget.h"
#include "SP/cSPTimer.h"
#include "SP/cTribeHut.h"
#include "SP/cVarListSerializer.h"

// ---- items of slice s00c982a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
class cGameData_s00c9_82a0;
}
namespace SP {
struct Vec3 { float x, y, z; };
}
namespace SP {
struct cSpatialView {                   // vtable view embedded at object +0x34 / +0x70
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
virtual void v28();
    virtual const Vec3* GetPosition();          // +0x2c
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
    virtual const Vec3* GetFacing(Vec3* out);   // +0x5c
virtual void v60();
virtual void v64();
virtual void v68();
virtual void v6c();
    virtual void v70();
    virtual float GetHeight();                  // +0x74
};
}
namespace SP {
struct cSpatialObject_s00c9_82a0 {                 // object whose spatial interface sits at +0x34
    char pad0[0x34];
    cSpatialView mSpatial;
};
}
namespace SP {
struct cSpatialObject70 {               // object whose spatial interface sits at +0x70
    char pad0[0x70];
    cSpatialView mSpatial;
};
}
namespace SP {
struct cSpeciesProfile_s00c9_82a0;
}
namespace SP {
struct cActionSlot {                    // 0x18-byte element of cActionCircle's slot array
    uint8_t mbOccupied;                 // +0x00
    char pad1[3];
    void* mpObject;                     // +0x04
    void* mpUnk08;                      // +0x08
    Vec3 mPlacement;                    // +0x0c, handed back by cTribe::ReserveToolSlot
    void Clear();                       // 0x00afa0a0
    void Reserve(void* object);         // 0x00afa030
    void* GetObject();                  // 0x00fcc210
};
}
namespace SP {
struct cActionCircle_s00c9_82a0 {
    char pad0[0x14];
    float mPosition[3];                 // 0x14, weighted-position input of the slot search
    char pad20[0x30];
    cActionSlot* mpSlotsBegin;          // 0x50
    cActionSlot* mpSlotsEnd;            // 0x54
    cActionSlot* At(int index);                                 // 0x00af9ff0
    void SetAtCenter(const Vec3* center, float radius, const Vec3* facing, float altitude);  // 0x00af9cf0
    void ConfigureSlots(float radius, float height, int layout);    // 0x00afdc00
    int FindClosestFreeSlotWeighted(int weight);                // 0x00afa7c0
};
}
namespace SP {
struct cActionCircleMap {
    cActionCircle_s00c9_82a0* FindOrAdd(int* key);                // 0x00c27d20
};
}
namespace SP {
struct cReservationGrid_s00c9_82a0 {
    char mData[0x1374];                                 // opaque body, methods address into it
    void* GetReservedList();                            // 0x00cc7070, returns this + 0x984
    void RemoveReservedByID(void* entries, const void* id);      // 0x00cc86a0
    void AddReserved(void* entries, const Vec3* pos, float radius, const void* id);  // 0x00cc8350
};
}
namespace SP {
struct cToolContext {                   // interface embedded in cGameData at +0xc0
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
virtual void v28();
    virtual int ComputeWeight(float* position, float radius);      // +0x2c
};
}
namespace SP {
struct cGameData_s00c9_82a0 {                      // slice-local view: only +0xc0 is used here
    char pad0[0xc0];
    cToolContext mToolContext;          // 0xc0
};
}
namespace SP {
class cTribe_s00c9_82a0
{ public:
    void UpdateToolPosition(int toolType);                     // 0x00c987b0
    cSpatialObject_s00c9_82a0* GetToolOfType(int toolType);               // 0x00c8f6e0
    void FindSpot(int spot, int index);                        // 0x00c98750
    void* ReserveToolSlot(int weight, int* outIndex, cGameData_s00c9_82a0* gameData);   // 0x00c986d0
    void GetToolPositionAndFacing(int type, Vec3* outPos, Vec3* outFacing);  // 0x00c905c0

    char pad0[0x260];
    cSpatialObject_s00c9_82a0* mpHut260;           // 0x260
    char pad264[0x368 - 0x264];
    cSpatialObject_s00c9_82a0* mpHut368;           // 0x368
    char pad36c[0x394 - 0x36c];
    cActionCircleMap mActionCircleMap;  // 0x394
    char pad398[0x504 - 0x398];
    Vec3 mToolAnchor;                   // 0x504
    char pad510[0x558 - 0x510];
    cReservationGrid_s00c9_82a0 mReservationGrid558;   // 0x558, size 0x1374 -> ends at 0x18cc
    cSpeciesProfile_s00c9_82a0* mpProfile18CC;     // 0x18cc
    char pad18d0[0x19c4 - 0x18d0];
    cSpatialObject70* mpTool19C4;       // 0x19c4
    cSpatialObject70* mpTool19C8;       // 0x19c8
    char pad19cc[0x19d0 - 0x19cc];
    cSpatialObject_s00c9_82a0* mpTotem19D0;        // 0x19d0
};
}
// ---- items of slice s00c982a0 end

// ---- items of slice s00c9afb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_TribeFoodProps;                                   // 0x0157c320
struct Vector3 { float x, y, z; };
struct RefCounted {
    virtual int   AddRef();                 // +0x00
    virtual void  Release();                // +0x04
    virtual void  r08();                    // +0x08
    virtual void  r0c();                    // +0x0c
    virtual void  r10();                    // +0x10
    virtual void  r14();                    // +0x14
    virtual void  r18();                    // +0x18
    virtual void  r1c();                    // +0x1c
    virtual void  r20();                    // +0x20
    virtual void  r24();                    // +0x24
    virtual void  r28();                    // +0x28
    virtual void* GetPosition();            // +0x2c
    virtual void  r30();                    // +0x30
    virtual void  r34();                    // +0x34
    virtual void  r38();                    // +0x38
    virtual void  r3c();                    // +0x3c
    virtual void  r40();                    // +0x40
    virtual void  r44();                    // +0x44
    virtual void  r48();                    // +0x48
    virtual void  r4c();                    // +0x4c
    virtual void  r50();                    // +0x50
    virtual void  r54();                    // +0x54
    virtual void* v58();                    // +0x58
    virtual void* v5c(void* out);           // +0x5c
    virtual void  v60();                    // +0x60
};
struct SimSerializable {
    virtual void  w00();
    virtual void  w04();
    virtual void  w08();
    virtual void  w0c();
};
struct cGameData_s00c9_afb0 : RefCounted, SimSerializable {
    cGameData_s00c9_afb0();                                        // 0x00b18660
    ~cGameData_s00c9_afb0();                                       // 0x00b184c0
    bool  IsDestroyed(void* ctx);                       // 0x00bfd0d0
    bool  Write(void* io);                              // 0x00b18590
    void  SetGameDataOwner2(void* owner);               // 0x00b18550
    void* Cast(int type);                               // 0x00b18460
    void  Func80();                                     // 0x00c88510
    void  TribalEvent(int arg);                         // 0x00c9be90
    char  mData[0x34 - 8];
};
struct CompactObj {
    virtual void  k00();                    // +0x00
    virtual void  k04();                    // +0x04
    virtual void  k08();                    // +0x08
    virtual void  k0c();                    // +0x0c
    virtual void  k10();                    // +0x10
    virtual void  k14();                    // +0x14
    virtual void  k18(float value, int id); // +0x18
    virtual void  k1c();                    // +0x1c
    virtual void  k20();                    // +0x20
    virtual void  k24();                    // +0x24
    virtual void  k28();                    // +0x28
    virtual void* k2c();                    // +0x2c
    char mTail[0x18];                       // total 0x1c
};
struct cSpatialObject_s00c9_afb0 {
    virtual void s00();
    cSpatialObject_s00c9_afb0();                                   // 0x00c89630
    ~cSpatialObject_s00c9_afb0();                                  // 0x00c8a420
    void  SetLocalExtents(void* ext, float radius);     // 0x00c89160
    void* Cast(int type);                               // 0x00c884f0
    bool  Write(void* io);                              // 0x00c88a90
    void  func80h();                                    // 0x00c88510
    void  func54h(void* a);                             // 0x00c88670
    void  func58h(void* a);                             // 0x00c886d0
    void  OnExtentsChanged(void* a, float b);           // 0x00c9be50

    char      mPad004[0x50];                            // +0x004
    int       mMaterialType;                            // +0x054 (abs +0x088)
    char      mPad058[0x38];                            // +0x058
    uint32_t  mModelInstance;                           // +0x090 (abs +0x0c4)
    uint32_t  mPad094;                                  // +0x094
    uint32_t  mModelGroup;                              // +0x098 (abs +0x0cc)
    char      mPad09c[8];                               // +0x09c
    void*     mpTribe;                                  // +0x0a4 (abs +0x0d8)
    char      mPad0a8[0x10];                            // +0x0a8
    CompactObj mSub;                                    // +0x0b8 (abs +0x0ec)
};
struct cInteractionTarget_s00c9_afb0 {
    virtual void i00();
    cInteractionTarget_s00c9_afb0();                               // 0x00ac03d0
    ~cInteractionTarget_s00c9_afb0();                              // 0x00ac0520
    void* Cast(int type);                               // 0x00ac0320
    char  mData[0x14];
};
struct cCombatant_s00c9_afb0 {
    virtual void c00();
    cCombatant_s00c9_afb0();                                       // 0x00bfd4e0
    ~cCombatant_s00c9_afb0();                                      // 0x00bfcd00
    void* Cast(int type);                               // 0x00bfc380
    float mf04;                                         // +0x004 (abs +0x124)
    char  mData[0xc0];
};
template <class T>
struct RefPtr {
    T* p;
    RefPtr() : p(0) {}
    ~RefPtr() { if (p) ((RefCounted*)p)->Release(); }
};
struct cTribeFoodMat : cGameData_s00c9_afb0, cSpatialObject_s00c9_afb0 {
    cTribeFoodMat();                                    // 0x00c9ba80
    virtual ~cTribeFoodMat();                           // 0x00c9bda0 (scalar deleting)
    void SetOwner(void* owner);                         // 0x00c9bb80
    bool Write(void* io);                               // 0x00c9bc00
    bool IsPlayerTribe();                               // 0x00c9bd30
    void Func54h(void* a);                              // 0x00c9bd50
    bool  mFlag108;                                     // +0x108
    char  mPad109[3];
    RefPtr<RefCounted> mpOwner10c;                      // +0x10c
};
struct cGonzagoTimer_s00c9_afb0 {
    cGonzagoTimer_s00c9_afb0();                                    // 0x00b63890
    ~cGonzagoTimer_s00c9_afb0();                                   // 0x00b638b0
    char mData[0x10];
};
struct cTribeHut_s00c9_afb0 : cGameData_s00c9_afb0, cSpatialObject_s00c9_afb0, cInteractionTarget_s00c9_afb0, cCombatant_s00c9_afb0 {
    cTribeHut_s00c9_afb0();                                        // 0x00c9bf90
    virtual ~cTribeHut_s00c9_afb0();                               // 0x00c9c120
    void* Cast(int type);                               // 0x00c9bdf0
    void  SetRefCountDelta(char on);                    // 0x00c9bef0
    void  UpdateEmpireColor();                          // 0x00c9bf30

    void* mpModel1e8;                                   // +0x1e8
    void* mpModel1ec;                                   // +0x1ec
    void* mpModel1f0;                                   // +0x1f0
    void* mpModel1f4;                                   // +0x1f4
    void* mpModel1f8;                                   // +0x1f8
    void* mpModel1fc;                                   // +0x1fc
    void* mpModel200;                                   // +0x200
    void* mpModel204;                                   // +0x204
    void* mpModel208;                                   // +0x208
    void* mpModel20c;                                   // +0x20c
    void* mpModel210;                                   // +0x210
    void* mpModel214;                                   // +0x214
    bool  mFlag218;                                     // +0x218
    char  mPad219[3];
    void* mp218;                                        // +0x21c
    bool  mFlag220;                                     // +0x220
    bool  mFlag221;                                     // +0x221
    char  mPad222[2];
    char  mPad224[4];
    void* mp228;                                        // +0x228
    void* mp22c;                                        // +0x22c
    RefPtr<RefCounted> mpTribe230;                      // +0x230
    RefPtr<RefCounted> mpHitSphere234;                  // +0x234
    int   mRef238;                                      // +0x238
    char  mPad23c[4];
    cGonzagoTimer_s00c9_afb0 mTimer;                               // +0x240
};
struct NounMgr {
    void* GetGameDataVector(int a, int b, int c, int d, int e);  // 0x00b21340
    void* GetPlayerTribe();                                      // 0x00bfc5f0
};
struct IOStream {
virtual void s00();
virtual void s04();
virtual void s08();
virtual void s0c();
virtual void s10();
virtual void s14();
    virtual void* GetBuffer();                                   // +0x18
};
struct IODevice {
virtual void d00();
virtual void d04();
virtual void d08();
virtual void d0c();
virtual void d10();
virtual void d14();
virtual void d18();
virtual void d1c();
    virtual void* GetStream();                                   // +0x20
};
struct cVarListSerializer_s00c9_afb0 {
    cVarListSerializer_s00c9_afb0(void* owner, void* props, int id);        // 0x00692f90
    bool Serialize(void* io);                                    // 0x00692900
    char mData[0xa14];
};
NounMgr* __cdecl NounManager();                                  // 0x00b3d300
uint32_t __cdecl FNVHash(const char* str, uint32_t basis, int mode);   // 0x00932e80
void  __cdecl WriteUint32(void* stream, uint32_t* value, int count, int flag);  // 0x0093aa70
namespace SP {
class cTribe_s00c9_afb0 { public:
    static uint32_t SetupHotSpot(const Vector3& dir, int force = 0);  // 0x00c9afb0 (SP::cTribe::SetupHotSpot)
    const Vector3* GetClosestWater();                            // 0x00c8fe20
    void func54h(void* a);                                       // 0x00c88670
    bool IsPlayerTribe();                                        // 0x00c9bd30
    void HandleEvent(void* a);                                   // 0x00c9bd50
    char mPad000[0xd8];
    void* mpTribeD8;                                             // +0x0d8
    char mPad0dc[0x120 - 0x0dc];
    CompactObj mSub120;                                          // +0x120
};  // namespace SP
}
// ---- items of slice s00c9afb0 end

// ---- items of slice s00c9c1b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cTribeToolData {
    uint8_t  pad00[0x10];
    int      mField10;                               // +0x10
    int      mField14;                               // +0x14
    uint8_t  pad18[0x38 - 0x18];
    int      mField38;                               // +0x38
    bool IsNotType10();                              // 00c9cf70
};
extern cTribeToolData* gTribeTools[12];              // 01699a14
// ---- items of slice s00c9c1b0 end

// @ 0x00c986d0
void* SP::cTribe_s00c9_82a0::ReserveToolSlot(int weight, int* outIndex, cGameData_s00c9_82a0* gameData)
{
    int key = weight;
    cActionCircle_s00c9_82a0* circle = mActionCircleMap.FindOrAdd(&key);
    cToolContext* context = &gameData->mToolContext;
    int score = context->ComputeWeight(circle->mPosition, 0.8f);
    int index = circle->FindClosestFreeSlotWeighted(score);
    *outIndex = index;
    if (index >= 0) {
        cActionSlot* slot = circle->mpSlotsBegin + index;
        if (slot) {
            slot->Reserve(gameData);
            return &slot->mPlacement;
        }
    }
    return circle->mPosition;
}

// @ 0x00c9ba80
cTribeFoodMat::cTribeFoodMat()
{
    mFlag108 = true;
    mMaterialType = 2;
    mModelInstance = FNVHash("trg_sacrifice_altar1", 0x811c9dc5, 1);
    mModelGroup = FNVHash("TribalTools", 0x811c9dc5, 1);
}

// @ 0x00c9bb80
void cTribeFoodMat::SetOwner(void* owner)
{
    SetGameDataOwner2(owner);
    void* old = mpOwner10c.p;
    if (owner != old) {
        if (owner)
            ((RefCounted*)owner)->AddRef();
        mpOwner10c.p = (RefCounted*)owner;
        if (old)
            ((RefCounted*)old)->Release();
    }
}

// @ 0x00c9bc00
bool cTribeFoodMat::Write(void* io)
{
    void* buf = ((IOStream*)((IODevice*)io)->GetStream())->GetBuffer();
    uint32_t value = 0x0629baec;
    WriteUint32(buf, &value, 1, 0);
    bool ok;
    if (cGameData_s00c9_afb0::Write(io) && ((cSpatialObject_s00c9_afb0*)((char*)this + 0x34))->Write(io))
        ok = true;
    else
        ok = false;
    cVarListSerializer_s00c9_afb0 ser(this, &g_TribeFoodProps, 0x1a80d26);
    bool result = ok && ser.Serialize(io);
    return result;
}

// @ 0x00c9bd30
bool SP::cTribe_s00c9_afb0::IsPlayerTribe()
{
    void* tribe = mpTribeD8;
    return NounManager()->GetPlayerTribe() == tribe;
}

// @ 0x00c9bda0
cTribeFoodMat::~cTribeFoodMat()
{
}

// Retail hut interface offsets are 0x000, 0x034, 0x108 and 0x120.
struct TribeHutInterfaceView {
    cGameData_s00c9_afb0 mGameData;
    cSpatialObject_s00c9_afb0 mSpatialObject;
    cInteractionTarget_s00c9_afb0 mInteractionTarget;
    cCombatant_s00c9_afb0 mCombatant;
};

// @ 0x00c9bdf0
void* cTribeHut_s00c9_afb0::Cast(int type)
{
    TribeHutInterfaceView* hut = reinterpret_cast<TribeHutInterfaceView*>(this);
    if (type != 0x00ee02c7) {
        void* r = hut->mGameData.Cast(type);
        if (r)
            return r;
        r = hut->mCombatant.Cast(type);
        if (r)
            return r;
        r = hut->mInteractionTarget.Cast(type);
        if (r)
            return r;
        return hut->mSpatialObject.Cast(type);
    }
    return this;
}

// @ 0x00c9cec0
uint32_t FUN_00c9cec0(int i)
{
    if ((unsigned)(i - 1) <= 0xa)
        return (uint32_t)gTribeTools[i];
    return (uint32_t)gTribeTools[0];
}
