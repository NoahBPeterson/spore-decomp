// src/game/SPGonzago/SPVehicleBehaviorTree.cpp -- migrated from slice(s) s00dcf2e0, s00dcd720, s00dca100, s00dc7eb0, s00dc77d0, s00dc57a0, s00dc3940, s00dc2720, s00b5b540, s00dd0230, s00dce4d0, s00dcc830, s00dcb8e0, s00dc8d10, s00dc67d0, s00dc48e0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPVehicleBehaviorTree.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "nSPBehaviorTree/behavior_stimuli.h"
#include "SP/cPlanetModel.h"
#include "SP/cLocomotiveObject.h"

// unnamed retail callees and globals (address in the comment)
extern float   DAT_013ec4d0;   // 0x013ec4d0
extern float   DAT_01473c70;   // 0x01473c70
extern float   DAT_0169fa68;   // 0x0169fa68
extern float   DAT_0169fa6c;   // 0x0169fa6c
extern float   DAT_0169fa70;   // 0x0169fa70
extern void* __stdcall SP_PlanetModel(void* a);  // 0xb3d350
#include <math.h>
#include "SP/cActionCircle.h"
#include "SP/cCity.h"
#include "SP/cCommunity.h"
#include "SP/cCulturalTarget.h"
#include "SP/cGameData.h"
#include "SP/cGameNounManager.h"
#include "SP/cRelationshipManager.h"
#include "SP/cSpatialObject.h"
#include "EA/Random/RandomLinearCongruential.h"
#include "SP/cVehicle.h"
#include <new>
#include "nSPBehaviorTree/behavior_memory_block.h"
#include "SP/cAnimatingCreature.h"
#include "SP/cCulturalConvertCityOrder.h"
#include "SP/cCivData.h"
#include "SP/cCombatant.h"
#include "SP/cMilitaryAttackCityOrder.h"
#include "SP/cString.h"
#include "SP/cVehicleGroupOrder.h"
#include "SP/cBehaviorTreeData.h"
#include "SP/cGonzagoSimulator.h"
#include "cSPVector3.h"
#include "SP/cEmpire.h"
#include <intrin.h>
#include "SP/cCivilization.h"
#include "SP/cPlanet.h"
#include "SP/cSPTimer.h"
#include "SP/cStarRecord.h"
#include "SP/cBuilding.h"
#include "SP/cMovingFormation.h"
#include <float.h>
#include <string.h>
#pragma pack(push,1)
#pragma pack(pop)

// ---- items of slice s00dc48e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float   DAT_013eb1bc;   // 0x013eb1bc
extern float   DAT_013ec4b8;   // 0x013ec4b8
extern float   DAT_013eecd8;   // 0x013eecd8
extern float   DAT_01470f1c;   // 0x01470f1c
extern float   DAT_014763b0;   // 0x014763b0
extern float   DAT_0147c368;   // 0x0147c368
extern float   DAT_0147c36c;   // 0x0147c36c
extern float   DAT_0147c390;   // 0x0147c390
extern float   DAT_01485378;   // 0x01485378
extern float   DAT_01485720;   // 0x01485720
struct Obj;
typedef void          (__thiscall *VfnRaw)(void);
typedef void          (__thiscall *Vfn0)(void*);
typedef void*         (__thiscall *VfnP)(void*);
typedef unsigned int  (__thiscall *VfnR)(void*);
typedef unsigned char (__thiscall *VfnB)(void*);
typedef void          (__thiscall *VfnI)(void*, int);
typedef void*         (__thiscall *VfnPI)(void*, int);
typedef void          (__thiscall *VfnV)(void*, void*);
typedef void*         (__thiscall *VfnVV)(void*, void*, void*);
typedef void          (__thiscall *VfnF3)(void*, float*, float, float);
enum VtSlot {
    kVt00 = 0x00 / 4, kVt04 = 0x04 / 4, kVt08 = 0x08 / 4, kVt0C = 0x0c / 4,
    kVt10 = 0x10 / 4, kVt2C = 0x2c / 4, kVt50 = 0x50 / 4, kVt5C = 0x5c / 4,
    kVt60 = 0x60 / 4, kVt64 = 0x64 / 4, kVt6C = 0x6c / 4, kVtB8 = 0xb8 / 4,
    kVtC0 = 0xc0 / 4, kVtE8 = 0xe8 / 4, kVtEC = 0xec / 4
};
struct Vtbl { VfnRaw mSlots[0xf0 / 4]; };
struct Sub {
    Vtbl* mpVtbl;                 // +0x00
    char  IsNearGoal();           // 0xc42e20  SP::cLocomotiveObject::IsNearGoal
    char  Cbfc600();              // 0xbfc600
    float Cbfc400();              // 0xbfc400
    void* Cc41ec0();              // 0xc41ec0
    void* Cc421f0();              // 0xc421f0
};
struct City        { float* GetPositionPtr(); };                  // 0xfa0e00
struct PlanetModel {
    int    GetContinent();                                   // 0xb88590
    float* CalcSurface(void* a, void* b);                    // 0xb81630
    float* DirectionToSurfacePosition(float* a, float* b);   // 0xb815a0
    char   Cb7e3e0(float* v);                                // 0xb7e3e0
};
struct CityVisualizer { void RequestPosition(float* v, uint32_t k); }; // 0xbec2d0
struct Bec660         { void Run(float* v, void* o); };                // 0xbec660
struct AnimCtx   { Obj* mpTarget; };                       // +0x00
struct Obj {
    Vtbl*  mpVtbl;                          // +0x000
    uint8_t mPad004[0x34 - 0x04];           // +0x004
    Sub    mSub34;                          // +0x034
    uint8_t mPad038[0x50 - 0x38];           // +0x038
    int    mField50;                        // +0x050
    uint8_t mPad054[0x5c - 0x54];           // +0x054
    int    mField5c;                        // +0x05C
    uint8_t mPad060[0x108 - 0x60];          // +0x060
    Sub    mSub108;                         // +0x108
    uint8_t mPad10c[0x120 - 0x10c];         // +0x10C
    Sub    mSub120;                         // +0x120
    uint8_t mPad124[0x224 - 0x124];         // +0x124
    float  mF224;                           // +0x224
    uint8_t mPad228[0x2a4 - 0x228];         // +0x228
    uint8_t mByte2a4;                       // +0x2A4
    uint8_t mPad2a5[0x508 - 0x2a5];         // +0x2A5
    Sub    mSub508;                         // +0x508
    uint8_t mPad50c[0xaf0 - 0x50c];         // +0x50C
    Obj*   mpBehaviorTree;                  // +0xAF0
    uint8_t mPadaf4[0xb1c - 0xaf4];         // +0xAF4
    int    mStateB1c;                       // +0xB1C
    uint8_t mPadb20[0xb7c - 0xb20];         // +0xB20
    Obj*   mpObjB7c;                        // +0xB7C
    uint8_t mPadb80[0xb8c - 0xb80];         // +0xB80
    Obj**  mpVecBeginB8c;                   // +0xB8C
    Obj**  mpVecEndB90;                     // +0xB90

    void*  Ca71d0();                        // 0xca71d0
    void   Ca7250(char* msg);               // 0xca7250
    void   Caa900();                        // 0xcaa900
    void*  C9f1c0();                        // 0xc9f1c0
    void   C6c0200();                       // 0x6c0200
    char   C9e960(float* p);                // 0xc9e960  SP::cVehicle::CanOccupyTerrain
    void*  C9fee0();                        // 0xc9fee0
    float* C9e880();                        // 0xc9e880
    void   C9fb40(float x, float y, float z, float a, float b); // 0xc9fb40
    void   Cabe70();                        // 0xcabe70
    float  C9eb80();                        // 0xc9eb80
    float* Cbd9480(float* out);             // 0xbd9480
    int    GetFileCount();                  // 0x8e7f80
};
struct KeyLookup {
    Obj*  mpObj;                    // +0x00
    void* Default(int key);         // 0xb18460
    void* Match2E9(int key);        // 0x00dc4c20
    void* Match3DF(int key);        // 0x00dc4c40
    void  Reset();                  // 0x00dc4c60
};
// ---- items of slice s00dc48e0 end

// ---- items of slice s00dc67d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double __cdecl sqrt(double);
extern char g_1601760;                                             // 0x01601760
extern char    g_1654c10;                                          // 0x01654c10 (game-mode object)
#pragma intrinsic(sqrt)
#define PV(n) virtual void pad##n();
#define NOINLINE __declspec(noinline)
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
    Vector3 operator-(const Vector3& v) const { return Vector3(x - v.x, y - v.y, z - v.z); }
    float Length() const { return (float)sqrt(x * x + y * y + z * z); }
};
struct cSpatialObject {
    // slots: 0x00-0x28 (11 dwords), then GetPosition
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a)
    virtual const Vector3& GetPosition();                          // +0x2c
    PV(0c) PV(0d) PV(0e) PV(0f) PV(10) PV(11) PV(12) PV(13) PV(14)
    PV(15)
    virtual bool Vf58();                                           // +0x58
    // 0x5c..0xb4 must be 23 slots (0x16)
    PV(17) PV(18) PV(19) PV(1a) PV(1b) PV(1c) PV(1d) PV(1e) PV(1f) PV(20) PV(21) PV(22) PV(23) PV(24)
    PV(25) PV(26) PV(27) PV(28) PV(29) PV(2a) PV(2b) PV(2c) PV(2d)
    virtual void* IsType(uint32_t typeID);                         // +0xb8
    virtual void Vbc();                                            // +0xbc
    virtual void Vc0();                                            // +0xc0
    virtual void Vc4(int a, float f);                              // +0xc4
    PV(32) PV(33) PV(34) PV(35) PV(36)
    virtual void Vdc(void* out);                                   // +0xdc
    PV(38)
    virtual void Ve4(const Vector3& v, float f);                   // +0xe4
    virtual void Ve8(const Vector3* p);                            // +0xe8
    virtual void Vec();                                            // +0xec
};
struct cGameData {
    PV(00) PV(01)
    virtual cSpatialObject* GetSpatial();                          // +0x08
    PV(03)
    virtual uint32_t GetOwnerID();                                 // +0x10
    PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b) PV(0c) PV(0d) PV(0e) PV(0f) PV(10) PV(11) PV(12) PV(13)
    virtual void SetAttackTarget(cGameData* target);               // +0x50
    float GetRange();                                              // 0x00bfc400
};
struct cInteractable {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b) PV(0c) PV(0d) PV(0e) PV(0f)
    PV(10) PV(11) PV(12)
    virtual uint32_t GetPoliticalID();                             // +0x4c
    PV(14) PV(15)
    virtual void* CastType(uint32_t typeID);                       // +0x5c
};
struct cGameDataObj {
    PV(00) PV(01) PV(02)
    virtual void* Cast(uint32_t typeID);                           // +0x0c
};
struct Info {
    cGameDataObj* mpObject;                                        // +0x00
    uint32_t dpad04[3];
};
struct cCity {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a)
    virtual bool IsDestroyed();                                    // +0x2c
    PV(0c) PV(0d) PV(0e) PV(0f) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(1a)
    PV(1b) PV(1c) PV(1d) PV(1e) PV(1f) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
    PV(2a) PV(2b) PV(2c) PV(2d) PV(2e) PV(2f) PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38)
    PV(39) PV(3a) PV(3b) PV(3c) PV(3d) PV(3e) PV(3f) PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46) PV(47)
    PV(48) PV(49) PV(4a) PV(4b) PV(4c) PV(4d) PV(4e) PV(4f) PV(50) PV(51) PV(52) PV(53)
    virtual const Vector3& GetPosition();                          // +0x2c
};
struct cCitySpatial {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a)
    virtual const Vector3& GetPosition();                          // +0x2c
};
struct EntityVector { void** mpBegin; void** mpEnd; };
struct cVehicleBase {
    virtual void AddRef();
    virtual void Release();
    PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b) PV(0c) PV(0d) PV(0e) PV(0f)
    PV(10) PV(11) PV(12)
    virtual uint32_t GetPoliticalID();                             // +0x4c
    uint32_t dpad04[(0x34 - 4) / 4];
    cSpatialObject mLoco;                                          // +0x34
};
struct cMoverLike {
    uint32_t pad00[(0x7c) / 4];
    float    m7c;                                                  // +0x7c
    float    m80;                                                  // +0x80
};
struct cVehicle : cVehicleBase {
    uint32_t pad38[(0x2a4 - 0x34 - sizeof(cSpatialObject)) / 4];
    uint8_t  mFlags2a4;                                            // +0x2a4
    uint32_t pad2a5[(0x508 - 0x2a4 - 1) / 4];
    cGameData mGameData;                                           // +0x508
    uint32_t pad50c[(0xaf0 - 0x508 - sizeof(cGameData)) / 4];
    int      mAf0;                                                 // +0xaf0
    uint32_t padAf4[(0xb1c - 0xaf0 - 4) / 4];
    int      mB1c;                                                 // +0xb1c
    int      mState;                                               // +0xb20
    uint32_t padB24[(0xb7c - 0xb20 - 4) / 4];
    void*    mB7c;                                                 // +0xb7c
    Vector3  mPos;                                                 // +0xb80
    uint32_t padB8c[(0xd04 - 0xb80 - sizeof(Vector3)) / 4];
    void*    mD04;                                                 // +0xd04

    EntityVector* GetHostiles();                                   // 0x00c9e860
    const Vector3& GetPosition();                                  // 0x00c9e880 -> +0xb80
    bool CanOccupyTerrain(const Vector3* pos);                     // 0x00c9e960
    void FUN_00c9ec40(int a);                                      // 0x00c9ec40
    cSpatialObject* GetTarget();                                   // 0x00c9fee0
    Info* FUN_00ca71d0();                                          // 0x00ca71d0
    void FUN_00ca7250(const char* msg);                            // 0x00ca7250
    void FUN_00caa900();                                           // 0x00caa900
    void FUN_00ca80e0(int id);                                     // 0x00ca80e0
    void FUN_00ca03a0(void* p);                                    // 0x00ca03a0
    void FUN_00ca33b0(void* p);                                    // 0x00ca33b0
    void FUN_00cabe70();                                           // 0x00cabe70
    void FUN_00c420d0(void* out);                                   // 0x00c420d0 (list at +0x278 from loco)
};
struct cRefObj {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b) PV(0c) PV(0d) PV(0e) PV(0f)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17)
    virtual void AddRef();                                         // +0x60
    virtual void Release();                                        // +0x64
    // 0x68 .. 0xb8 -> 21 slots
    PV(1a) PV(1b) PV(1c) PV(1d) PV(1e) PV(1f) PV(20) PV(21) PV(22) PV(23) PV(24)
    PV(25) PV(26) PV(27) PV(28) PV(29) PV(2a) PV(2b) PV(2c) PV(2d) PV(2e)
    virtual void Vbc();                                            // +0xbc
    virtual void Vc0();                                            // +0xc0
};
struct cCommunity {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b) PV(0c) PV(0d) PV(0e) PV(0f)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(1a) PV(1b) PV(1c) PV(1d) PV(1e) PV(1f)
    PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(2a) PV(2b) PV(2c) PV(2d) PV(2e) PV(2f)
    PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(3a) PV(3b) PV(3c) PV(3d) PV(3e) PV(3f)
    PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46) PV(47) PV(48) PV(49) PV(4a) PV(4b) PV(4c) PV(4d) PV(4e) PV(4f)
    PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56) PV(57) PV(58) PV(59) PV(5a) PV(5b) PV(5c) PV(5d) PV(5e) PV(5f)
    PV(60) PV(61) PV(62) PV(63) PV(64) PV(65) PV(66) PV(67) PV(68) PV(69) PV(6a) PV(6b) PV(6c) PV(6d) PV(6e) PV(6f)
    PV(70) PV(71) PV(72) PV(73) PV(74) PV(75) PV(76) PV(77) PV(78)
    virtual void Release();                                        // +0x64 (heuristic - shared with cRefObj family)
    void* Front();                                                 // 0x00bfec10
    void  Deactivate();                                            // 0x00bfe4d0
    void  FUN_00bff290(void* v);                                   // 0x00bff290
};
struct cNounManager {
    void RemoveNoun(void* noun);                                   // 0x00b225d0
    void* GetEmpire(uint32_t id);                                  // 0x00b25f40
};
cNounManager* __cdecl NounManager();                               // 0x00b3d300
struct cRelationshipManager {
    int FUN_00d00a70(uint32_t a, uint32_t b, int c);               // 0x00d00a70
    bool FUN_00ae2e20(uint32_t a, uint32_t b);                     // 0x00ae2e20
};
cRelationshipManager* __cdecl SP_RelationshipManager();            // 0x00b3d2c0
struct cActionCircleSlot {                                         // 0x18 bytes
    uint32_t m0;
    uint32_t m4;
    uint32_t m8;
    Vector3  mPos;
};
struct cActionCircle {
    uint32_t pad0[0x50 / 4];
    cActionCircleSlot* mpBegin;                                    // +0x50
    cActionCircleSlot* mpEnd;                                      // +0x54
    void FUN_00afafd0();                                           // 0x00afafd0
};
struct cTicker {
    double RandomDoubleUniform();                                  // 0x009360d0
};
extern Vector3 g_169fa68;                                          // 0x0169fa68 (Vector3)
void* __cdecl SP_GetCurrentGameMode();                             // 0x00b5b800
void __cdecl operator delete(void*);                               // 0x00f47380
void Start3dSoundByName(void* name, void* sys, float x, float y, float z);   // 0x00571f80
void KillSetiEffects(void* space, void* a, void* sys);             // 0x00435ed0
void* __cdecl EA_Audio_GetSystemAT();                              // 0x00a206f0
int  __cdecl FUN_008e7f80(void* self);                             // 0x008e7f80 (GetDamageState)
int  __cdecl PlayIdleAnim(void* creature, int a, int b);           // 0x00bc96a0
void* __cdecl FUN_00c420d0(void* loco);                            // 0x00c420d0
struct ClosestVehicleFlags { bool value; };
void* __cdecl FUN_00dc6680(void* a, void* b, ClosestVehicleFlags c);             // 0x00dc6680 (FindClosestVehicle)
void* __cdecl FUN_00afa070(cActionCircleSlot* slot, uint32_t id);  // 0x00afa070 (thiscall slot)
inline void* VCall1(void* obj, int slot)
{
    void** vt = *(void***)obj;
    return ((void* (__thiscall*)(void*))vt[slot / 4])(obj);
}
inline void* VFn(void* obj, int slot)
{
    void** vt = *(void***)obj;
    return vt[slot / 4];
}
struct cRefBase {
    virtual void AddRef();
    virtual void Release();
};
bool IsValidFireTarget(cGameData* mine, cGameData* theirs);        // 0x00dc4e20
bool FUN_00bfcc40(void* self, uint32_t id);                        // 0x00bfcc40
bool FUN_00c0c0e0(void* self);                                     // 0x00c0c0e0
bool FUN_00bd3550(void* self, void* vehicle);                      // 0x00bd3550
bool FUN_00bda6a0(void* a, void* b);                               // 0x00bda6a0
void* FUN_00bd81a0(void* self);                                    // 0x00bd81a0
void* FUN_00cb45b0(void* target);                                  // 0x00cb45b0
void  FUN_00dc4d00(void* self, cSpatialObject* t);                 // 0x00dc4d00
void  FUN_00dc4610(void* self);                                    // 0x00dc4610
void* FUN_00bdca30(void* self, void* out, float a);                // 0x00bdca30
int   FUN_00cabe70(void* self);                                    // 0x00cabe70
void  FUN_00ca80e0(void* self, int id);                            // 0x00ca80e0
void  FUN_00c9ec40(void* self, int a);                             // 0x00c9ec40
void  FUN_00bff290(void* self, void* v);                           // 0x00bff290
void  FUN_00ca33b0(void* self, void* p);                           // 0x00ca33b0
struct NodeState6ce0 {
    uint32_t mState;                                               // +0x00
    cCommunity* mpCommunity;                                       // +0x04
    cRefObj* mpObj;                                                // +0x08
};
struct NodeState7080 {
    cRefObj* mpObj;                                                // +0x00
    Vector3  mPos;                                                 // +0x04
    float    mf10;                                                 // +0x10
};
struct NodeState7150 {
    float mf0;                                                     // +0x00
    bool  mb4;                                                     // +0x04
};
struct NodeState7300 {
    uint32_t mState;                                               // +0x00
    cCommunity* mpCommunity;                                       // +0x04
};
struct RemoveList {
    uint32_t pad0[0x10 / 4];
    void** mpBegin;                                                // +0x10
    void** mpEnd;                                                  // +0x14
};
struct SpotHolder {
    void**   mpBegin;                                              // +0x00
    void**   mpEnd;                                                // +0x04
    uint32_t pad08[(0x60 - 0x08) / 4];
    void*    m60;                                                  // +0x60 (spatial whose position is the anchor)
};
struct RefHolder76e0 {
    void*    mpIndirect;                                           // +0x00 (pointer to the held object)
    uint32_t pad04[0x54 / 4];
    cRefObj* mp58;                                                 // +0x58
};
struct BufHolder {
    uint32_t pad0[2];
    void*    mp8;                                                  // +0x08
};
extern char* g_sVehiclesToRemoveBegin;                             // 0x016a0058
extern char* g_sVehiclesToRemoveEnd;                               // 0x016a005c
// ---- items of slice s00dc67d0 end

// ---- items of slice s00dc8d10 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct CVehicle
{
    /* 000h */ uint8_t  mPad_000[0x2a4];
    /* 2a4h */ uint32_t mFlags_2a4;    // bit 1 = repark pending, bit 2 = reparked

    void OnMoveTick();                 // 0x00cacbe0
};
void AttemptRepark(CVehicle* pVeh);    // 0x00dc9430
struct IRefCounted
{
    virtual void AddRef();
    virtual void Release();
};
struct AutoRefCount
{
    /* 000h */ IRefCounted* mpObject;

    AutoRefCount(IRefCounted* pObject) : mpObject(pObject)
    {
        if (mpObject)
            mpObject->AddRef();
    }

    AutoRefCount(const AutoRefCount& other) : mpObject(other.mpObject)
    {
        if (mpObject)
            mpObject->AddRef();
    }

    ~AutoRefCount()
    {
        if (mpObject)
            mpObject->Release();
    }
};
template<class T>
class SPVector
{
public:
    /* 000h */ T* mpBegin;
    /* 004h */ T* mpEnd;
    /* 008h */ T* mpCapacity;

    void DoInsertPtr(T* pPos, const T& x);      // 0x00aea5d0

    void push_back(const T& x)
    {
        if (mpEnd < mpCapacity)
        {
            T* p = mpEnd;
            mpEnd = p + 1;
            if (p)
                new (p) T(x);
        }
        else
        {
            DoInsertPtr(mpEnd, x);
        }
    }
};
SPVector<AutoRefCount> gLocomotiveList;         // 0x016a0058
// ---- items of slice s00dc8d10 end

// ---- items of slice s00dcb8e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" float sqrtf(float);
extern uint8_t  DAT_01654c10;              // current-game-mode marker
extern void*    gVehicleTicker;            // 0x01699ab8
extern uint32_t gVehicleServiceTable708;   // 0x0147c708
extern uint32_t gVehicleServiceTable714;   // 0x0147c714
typedef int    (__thiscall* FnI)(void*);
typedef float* (__thiscall* FnFP)(void*);
typedef void*  (__thiscall* FnVP)(void*, int);
struct VTable { void* p[64]; };
static inline int CallV(void* obj, int slot)
{
  return ((FnI)(*(VTable**)obj)->p[slot / 4])(obj);
}
static inline int CallVBool(void* obj, int slot)
{
  return ((FnI)(*(VTable**)obj)->p[slot / 4])(obj) & 1;
}
static inline float* CallVPos(void* obj, int slot)
{
  return ((FnFP)(*(VTable**)obj)->p[slot / 4])(obj);
}
static inline void* CallVArgP(void* obj, int slot, int arg)
{
  return ((FnVP)(*(VTable**)obj)->p[slot / 4])(obj, arg);
}
typedef void (__thiscall* FnVFP)(void*, const void*, float);
static void CallVFloatArg(void* obj, int slot, const void* p, float f)
{
  ((FnVFP)(*(VTable**)obj)->p[slot / 4])(obj, p, f);
}
struct Vector24 {
  uint8_t   mPad00[0x24];
  uint32_t* mpBegin;          // +0x24
  uint32_t* mpEnd;            // +0x28
  uint32_t* mpCap;            // +0x2c

  void PushUnique(uint32_t value);
};
struct Locomotive {
  virtual void v00();         // +0x00 (vptr lives here)

  bool IsNearGoal();          // 0x00c42e20
};
struct Stimuli {
  void ClearAll(int flags, int mode);   // 0x00bc98f0
};
struct VectorErase {
  void* mpBegin;              // +0x00
  void* mpEnd;                // +0x04
  void* mpCap;                // +0x08

  void erase(void* first, void* last);  // 0x00b48e40
};
struct Brain {
  void*    mpObj0;            // +0x00
  uint8_t  mPad04[0x0c];      // +0x04
  int      mMode10;           // +0x10
};
struct NounManagerObj {
  void RemoveNoun(uint32_t noun);       // 0x00b225d0
};
extern "C" void FUN_00ca71d0();         // Brain* GetBrain(this)
struct BehaviorObj {
  uint8_t   mPad00[0x10];     // +0x000
  uint32_t* mpNouns;          // +0x010
  uint32_t* mpNounsEnd;       // +0x014
  uint8_t   mPad18[0x0c];     // +0x018
  uint32_t* mpVec24;          // +0x024
  uint32_t* mpVec24End;       // +0x028
  uint32_t* mpVec24Cap;       // +0x02c
  uint8_t   mPad30[0x04];     // +0x030
  Locomotive mLoco;           // +0x034
  VectorErase mVec38;         // +0x038
  uint8_t   mPad44[0x0c];     // +0x044
  uint32_t* mpVec50;          // +0x050
  uint32_t* mpVec50End;       // +0x054
  uint32_t* mpVec50Cap;       // +0x058
  uint8_t   mPad5c[0x34];     // +0x05c
  int       mField90;         // +0x090
  uint8_t   mPad94[0x210];    // +0x094
  uint32_t  mFlags2a4;        // +0x2a4
  uint8_t   mPad2a8[0x260];   // +0x2a8
  void*     mpObj508;         // +0x508
  uint8_t   mPad50c[0x5e4];   // +0x50c
  void*     mpObjAf0;         // +0xaf0
  uint8_t   mPadAf4[0x0c];    // +0xaf4
  int       mFieldB00;        // +0xb00
  uint32_t  mFieldB04;        // +0xb04
  uint32_t  mFieldB08;        // +0xb08
  uint8_t   mPadB0c[0x14];    // +0xb0c
  int       mFieldB20;        // +0xb20
  uint8_t   mPadB24[0x04];    // +0xb24
  int       mFieldB28;        // +0xb28
  uint8_t   mPadB2c[0x2c];    // +0xb2c
  float     mFieldB58;        // +0xb58
  uint8_t   mPadB5c[0x20];    // +0xb5c
  void*     mpObjB7c;         // +0xb7c

  Brain* GetBrain() { return ((Brain* (__thiscall*)(BehaviorObj*))(void*)FUN_00ca71d0)(this); }  // 0x00ca71d0
  void*  GetNearby();                           // 0x00c9fee0
  void   FUN_00cacbe0();                        // 0x00cacbe0
  void   RemoveNouns();                         // 0x00dcc2c0
  void   AddFeedback(void* event);              // 0x00dcc350
};
struct CombatCtx {
  void* mpTarget;             // +0x00
  float mPosX;                // +0x04
  float mPosY;                // +0x08
  float mPosZ;                // +0x0c
  float mTimer;               // +0x10
};
struct TimerCtx {
  float   mTimer;             // +0x00
  uint8_t mFlag;              // +0x04
};
struct StateCtx {
  uint8_t mPad00[0x20];       // +0x00
  uint8_t mFlag20;            // +0x20
  uint8_t mFlag21;            // +0x21
};
struct TradeCtx {
  int     mField0;            // +0x00
  int     mField4;            // +0x04
  uint8_t mFlag8;             // +0x08
};
void*  AllocSimObject(uint32_t size, const char* name, int a, int b, int c, int d);
void*  __stdcall VectorInsertU32(uint32_t* pos, uint32_t* value); // 0x004558a0
void*  __fastcall SimSingleton_ctor(void* mem);         // 0x00dc7d70
void*  FUN_00dc9680(BehaviorObj* self);                 // 0x00dc9680
void*  FUN_00dc5050(BehaviorObj* self, void* city);     // 0x00dc5050
void   FUN_00ca7250(BehaviorObj* self, const char* msg); // 0x00ca7250
void   FUN_00caa900(BehaviorObj* self);                 // 0x00caa900
void   FUN_00ca80e0(BehaviorObj* self, int value);      // 0x00ca80e0
void   FUN_00cacbe0(BehaviorObj* self);                 // 0x00cacbe0
void   AttemptRepark(BehaviorObj* self);                // 0x00dc9430
void   FUN_00dc4ed0(float* a, float* b, BehaviorObj* self, void* obj); // 0x00dc4ed0
void   FUN_00ca97a0(float* pos, float a, float b);      // 0x00ca97a0
void   FUN_00c9fb40(float x, float y, float z, float a, float b); // 0x00c9fb40
float  FUN_00f264b0(BehaviorObj* self);                 // 0x00f264b0
float  FUN_00bfc400();                                  // 0x00bfc400
int    __fastcall GetDamageState(void* combatant);      // SP::cCombatant
char   __fastcall Flag388(void* obj);                   // 0x00c0c0e0
NounManagerObj* NounManager(uint32_t noun);             // 0x00b3d300
void*  FUN_00dcc440(BehaviorObj* self, int specialty, void* exclude); // 0x00dcc440
uint8_t FUN_00dcc0a0(BehaviorObj* self, StateCtx* ctx, float dt); // 0x00dcc0a0
void   FUN_00dcc610(BehaviorObj* self);                 // 0x00dcc610
uint8_t StandardVehicleMoveTick(BehaviorObj* self);     // anonymous namespace
extern "C" float DAT_013f1164;                          // 0x013f1164  move-point height constant
// ---- items of slice s00dcb8e0 end

// ---- items of slice s00dcc830 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma warning(disable : 4100)
namespace SP {
class cRefCounted {
public:
    virtual void r00();
    virtual void Release();                              // +0x04
};
}
namespace SP {
class cAnimatingCreature_s00dc_c830 {
public:
    void Release();                                      // 0x00a05270
};
}
namespace SP {
struct cOrderVTable0 { int mSlot0; };
}
namespace SP {
struct cOrderVTable1 { int mSlot0; };
}
namespace SP {
extern cOrderVTable0 gCulturalConvertCityOrderVtbl0;
}
namespace SP {
extern cOrderVTable1 gCulturalConvertCityOrderVtbl1;
}
namespace SP {
class cCulturalConvertCityOrder_s00dc_c830 {
public:
    cOrderVTable0* volatile mpVtbl0;                     // +0x00
    cOrderVTable1* volatile mpVtbl1;                     // +0x04
    uint8_t            pad008[0x8c];                     // +0x08 .. +0x93
    cRefCounted*       mpField94;                        // +0x94
    uint8_t            pad098[4];                        // +0x98 .. +0x9b
    cAnimatingCreature_s00dc_c830* mpField9c;                       // +0x9c
    cRefCounted*       mpFieldA0;                        // +0xa0
    cRefCounted*       mpFieldA4;                        // +0xa4

    ~cCulturalConvertCityOrder_s00dc_c830();

    // Body of the vehicle-group-order base destructor (0x00b22180).
    void DestroyBase();
};
}
namespace SP {
class cVehicleTree_s00dc_b8e0 {
public:
    void MoveToPointOrder_Activate();
};
}
namespace SP {
class cVehicleTree {
public:
    void TradeWithCityOrder_Tick();
    void OfferToBuyCityOrder_Activate();
    void MoveToPointOrder_Activate();
};
}
namespace SP {
class cVehicleTicker {
public:
    void* GetGroupOrder();
};
}
// ---- items of slice s00dcc830 end

// ---- items of slice s00dce4d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl FUN_00b3d290(void);
extern "C" void* __cdecl FUN_00b3d300(void);                                    // SP::NounManager
extern "C" void  __cdecl FUN_00dc8d10(void*, int, void**);
extern "C" void  __cdecl FUN_00ae6e70(void*, void*);
extern "C" void  __cdecl FUN_00dcd590(void*);
extern "C" void  __cdecl FUN_00dcec60(void*, void*, void*);
extern "C" void* __cdecl FUN_00dcd6e0(void*, void*, void*);
extern "C" void  __cdecl FUN_00dc4cc0(void*, void*, void*);
extern "C" void* __cdecl FUN_00f473a0(int, const char*, int, int, int, int);    // operator_new
extern "C" void  __cdecl FUN_00f47380(void*);                                   // operator_delete_array
extern "C" void  __cdecl FUN_00cd7d10();
extern "C" void  __cdecl FUN_00d3d420();
extern "C" void  __cdecl FUN_00ace0f0();
extern "C" void  __cdecl FUN_00b1e500();
extern char DAT_018eb45e;
#define VF(p, off) (*(void**)((char*)(*(void**)(p)) + (off)))
class TObj {
public:
    // ---- reused __thiscall callees (addresses in comments) -------------------
    void   F_db5b30(void*);                 // 0xdb5b30
    void   F_dc8ed0(void*);                 // 0xdc8ed0  hashtable::operator=
    void   F_d5d4b0(void*);                 // 0xd5d4b0  cActionCircle::operator=
    void   F_ca0940(void*);                 // 0xca0940  RefOps::AssignA
    void*  F_ac15e0();                      // 0xac15e0
    void   F_b48e40(void*, void*);          // 0xb48e40  eastl vector::erase
    void*  F_b21340(void*, void*, void*, void*, void*);   // 0xb21340 GetGameDataVector
    void   F_bab900(void*, void*);          // 0xbab900  eastl vector::insert(pos,val)
    char   F_c0c0e0();                      // 0xc0c0e0  C::Flag388

    // ---- slice targets -------------------------------------------------------
    void  FUN_00dce4d0(void*, uint32_t);
    void  FUN_00dce970(void*);
    void* FUN_00dcea90(void*);
    void  FUN_00dceca0();
    void  FUN_00dced90();
    void  FUN_00dcedb0(void*, uint32_t);
    void* FUN_00dcf180(void*, uint32_t, uint32_t);
};
#define ASSIGN_REF(dst, val) do {                     \
    void* _n = (val);                                 \
    void* _o = (dst);                                 \
    if (_n != _o) {                                   \
        if (_n) ((void(__thiscall*)(void*))VF(_n, 0xbc))(_n); \
        (dst) = _n;                                   \
        if (_o) ((void(__thiscall*)(void*))VF(_o, 0xc0))(_o); \
    }                                                 \
} while (0)
// ---- items of slice s00dce4d0 end

// ---- items of slice s00dd0230 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cSPVector3_s00dd_0230 {
    float x, y, z;
    cSPVector3_s00dd_0230() {}
    cSPVector3_s00dd_0230(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    cSPVector3_s00dd_0230(const cSPVector3_s00dd_0230& v) { x = v.x; y = v.y; z = v.z; }
};
void* operator new(unsigned size, const char* name, int a, int b, int c, int d);   // 0x00f473a0
class cSpatialObject_s00dd_0230 : public IRefCounted {
public:
    virtual void* v08();                                // +0x08 (slot 2)
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
    virtual void v28();
    virtual const cSPVector3_s00dd_0230& GetPosition();            // +0x2c (slot 11)
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
    virtual bool v50();                                 // +0x50 (slot 20)
virtual void v54();
virtual void v58();
virtual void v5c();
virtual void v60();
virtual void v64();
virtual void v68();
virtual void v6c();
virtual void v70();
virtual void v74();
virtual void v78();
virtual void v7c();
virtual void v80();
virtual void v84();
virtual void v88();
virtual void v8c();
virtual void v90();
virtual void v94();
virtual void v98();
virtual void v9c();
virtual void va0();
virtual void va4();
virtual void va8();
virtual void vac();
virtual void vb0();
virtual void vb4();
    virtual void* Cast();                               // +0xb8 (slot 46)
    virtual void vb8();                                 // +0xbc (slot 47)
    virtual void vc0();                                 // +0xc0 (slot 48)
    cSpatialObject_s00dd_0230* CastObject();                       // +0xb8 (typed form)
};
class cLocomotive : public cSpatialObject_s00dd_0230 {
public:
virtual void vbc();
virtual void vc0();
virtual void vc4();
    virtual void MoveTo(const cSPVector3_s00dd_0230& dst, float a, float b, bool rel);   // +0xe0
    virtual void MoveAround(const cSPVector3_s00dd_0230& c, float r);                    // +0xe4
    virtual void MoveTowards(const cSPVector3_s00dd_0230& dst);                          // +0xe8
};
class cCombatant : public IRefCounted {
public:
virtual void v08();
virtual void v0c();
virtual void v10();
    virtual float GetRadius();                          // +0x14
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
    virtual void v50(void* pTarget);                    // +0x50 (slot 20)
    float GetStat();                                    // 0x00bfc400 (thiscall)
};
class cCity_s00dd_0230 : public IRefCounted {
public:
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
    virtual void v28();
    virtual bool v2c();                                 // vtable +0x2c (slot 11)
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
    virtual uint32_t v4c();                             // vtable +0x4c (slot 19)
    char pad04[0x120 - 4];
    struct cCityDisplay {                               // embedded object at +0x120
        char pad00[0x50];
        uint32_t mFlags;                                // +0x50 (absolute +0x170)
    } mDisplay;                                         // +0x120
    char pad174[0x44c - 0x174];
    void* mpSomething_44c;                              // +0x44c
    cCity_s00dd_0230* GetCivilization();                           // 0x00bd9bf0
};
class cVehicle_s00dd_0230 {
public:
    char pad00[0x34];
    cLocomotive mLoco;                                  // +0x34
    char padLoco[0x508 - 0x34 - sizeof(cLocomotive)];
    cCombatant mCombatant;                              // +0x508
    char padCombat[0xb1c - 0x508 - sizeof(cCombatant)];
    uint32_t mLocomotion;                               // +0xb1c
    char padB20[0xb7c - 0xb1c - 4];
    cSpatialObject_s00dd_0230* mpChaseTargetRef;                   // +0xb7c

    void* GetTreeData();                                // 0x00ca71d0 (thiscall)
    void Log(const char* msg);                          // 0x00ca7250 (thiscall)
    void Flush();                                       // 0x00caa900 (thiscall)
    void SetTarget(void* pTarget);                      // 0x00dc4d00 (thiscall, ret 4)
};
void __cdecl Vehicle_ClearOrder(cVehicle_s00dd_0230* pVehicle);             // 0x00dcc610
bool __cdecl IsValidFireTarget(cCombatant* pCombatant, cSpatialObject_s00dd_0230* pTarget);   // 0x00dc4e20
class cVehicleGroupOrder : public IRefCounted {
public:
    virtual void v08();
    virtual void* FindOrderByType(uint32_t type);       // vtable +0x0c (slot 3)
    char pad04[0x50 - 4];
    cVehicle_s00dd_0230** mVehiclesBegin;                          // +0x50
    cVehicle_s00dd_0230** mVehiclesEnd;                            // +0x54
};
class cVehicleTicker_s00dd_0230 {
public:
    cVehicleTicker_s00dd_0230();                                   // 0x00dc7d70
    cVehicleGroupOrder* GetGroupOrder(void* pData);      // 0x00dcd430
    char pad00[0x58];                                   // sizeof == 0x58
};
cVehicleTicker_s00dd_0230* gVehicleTicker_s00dd_0230;                          // 0x01699ab8
class cMilitaryAttackCityOrder : public cVehicleGroupOrder {
public:
    char pad58[0x80 - 0x58];
    uint32_t mBanner_80;                                // +0x80
    uint32_t mMode;                                     // +0x84 (1..5 selector)
    uint32_t mBanner_88;                                // +0x88
    uint32_t mField_8c;                                 // +0x8c
    float mStatScale;                                   // +0x90
    cCity_s00dd_0230* mpCity;                                      // +0x94
    uint32_t mAttackerId;                               // +0x98
    char pad9c[0xac - 0x9c];

    cSpatialObject_s00dd_0230* GetCurrentTarget(cVehicle_s00dd_0230* pVehicle);        // 0x00dcfc90
    uint32_t GetCityBannerId();                                  // 0x00dd0550
    void* QueryInterface(uint32_t type);                         // 0x00dd0590
    bool IsInSimulatorContext();                                 // 0x00dd05e0
    bool IsActive();                                             // 0x00dd0600
    void* QueryInterface2(uint32_t type);                        // 0x00dd0610
    uint32_t GetIconKey();                                       // 0x00dd0650
    uint32_t GetPaletteItemPriority();                           // 0x00641770
    uint32_t GetMissionKey();                                    // 0x00dd06a0
    void SetupOrder(cVehicle_s00dd_0230* pVehicle);                         // 0x00dc8c00 (thiscall, ret 4)
    void ResetOrder(cVehicle_s00dd_0230* pVehicle);                         // 0x00dcc350 (thiscall, ret 4)
    bool OnTick(float dt);                                       // 0x00dd0380 (override, slot 20)
};
uint32_t __cdecl GetPaletteItemPriority();                          // 0x00641770
// ---- items of slice s00dd0230 end

// ---- items of slice s00b5b540 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct AdjustThunk_00b5b5d0 {
    void* FUN_00b5b5d0_adjust(unsigned id);
};
// ---- items of slice s00b5b540 end

// ---- items of slice s00dc2720 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma warning(disable: 4100)
namespace SP {
struct Vec3 { float x, y, z; };
}
namespace SP {
class cSpatialObject_s00dc_2720;
}
namespace SP {
class cSpatialSub;
}
namespace SP {
class cCombatant_s00dc_2720;
}
namespace SP {
class RefCounted {
public:
    virtual void AddRef();                                    // +0x00
    virtual void Release();                                   // +0x04
};
}
namespace SP {
class cCombatant_s00dc_2720 : public RefCounted {
public:
    virtual void v02();
    virtual cSpatialObject_s00dc_2720* GetOwnerNoun();                   // +0x0c
};
}
namespace SP {
class cLocomotion {
public:
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
virtual void v0a();
    virtual const Vec3* GetPosition();                        // +0x2c  0x00c0d6b0
virtual void v0c();
virtual void v0d();
virtual void v0e();
virtual void v0f();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
    virtual const Vec3* GetFacing(Vec3* out);                 // +0x5c
virtual void v18();
virtual void v19();
virtual void v1a();
virtual void v1b();
virtual void v1c();
virtual void v1d();
virtual void v1e();
virtual void v1f();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
virtual void v27();
virtual void v28();
virtual void v29();
virtual void v2a();
virtual void v2b();
virtual void v2c();
virtual void v2d();
virtual void v2e();
virtual void v2f();
virtual void v30();
virtual void v31();
    virtual bool TestGround();                                // +0x48
virtual void v33();
virtual void v34();
virtual void v35();
    virtual bool IsFlying();                                  // +0x58
};
}
namespace SP {
struct cBehaviorTreeData_s00dc_2720 {
    uint32_t pad00[0x1d8 / 4];
    uint32_t mTreeId;                                         // +0x1d8  behaviour-tree fourcc
};
}
namespace SP {
class cSpatialSub {
public:
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
virtual void v0a();
    virtual const Vec3* GetPosition();                        // +0x2c
};
}
namespace SP {
class cGroup {
public:
virtual void v00();
virtual void v01();
virtual void v02();
    virtual cSpatialObject_s00dc_2720* FindMember(uint32_t key);         // +0x0c
};
}
namespace SP {
class cSpatialObject_s00dc_2720 : public RefCounted {
public:
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
    virtual int  GetTypeHash();                               // +0x20  0x00c0...
virtual void v09();
virtual void v0a();
virtual void v0b();
virtual void v0c();
virtual void v0d();
virtual void v0e();
virtual void v0f();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
    virtual int  GetRingKey();                                // +0x60
    virtual void v19();
    uint8_t  pad04[0xc0 - 0x04];
    cLocomotion mLoco;                                        // +0xc0 locomotion sub-object
    uint8_t  padc4[0x120 - 0xc4];
    cSpatialSub mSpatial120;                                  // +0x120 spatial sub-object
    uint8_t  pad124[0x135 - 0x124];
    bool     mbValid135;                                      // +0x135 the leader is usable
    uint8_t  pad136[0x5a8 - 0x136];
    cCombatant_s00dc_2720 mCombatant5a8;                                 // +0x5a8 combatant sub-object
    uint8_t  pad5ac[0x624 - 0x5ac];
    bool     mbDirty624;                                      // +0x624 behaviour state changed
    uint8_t  pad625[0x68c - 0x625];
    int      mFamily68c;                                      // +0x68c family / house id
    bool     mbFlag690;                                       // +0x690
    uint8_t  pad691[0x694 - 0x691];
    Vec3     mBasis694;                                       // +0x694 ring direction
    uint8_t  pad6a0[0x6b0 - 0x6a0];
    int      mRingIndex6b0;                                   // +0x6b0 index within the ring
    float    mField6b4;                                       // +0x6b4
    float    mField6b8;                                       // +0x6b8
    uint8_t  pad6bc[0x6c8 - 0x6bc];
    void*    mpEnv;                                           // +0x6c8 behaviour environment / tree
    uint8_t  pad6cc[0x714 - 0x6cc];
    int      mState714;                                       // +0x714 tuning / model state
    uint8_t  pad718[0x74c - 0x718];
    bool     mbEnabled74c;                                    // +0x74c behaviour switched on
    uint8_t  pad74d[0xb20 - 0x74d];
    void*    mpSpecies;                                       // +0xb20 species profile
    uint8_t  padb24[0xb34 - 0xb24];
    int      mRankB34;                                        // +0xb34 (== 1 for a follower)
    uint8_t  padb38[0xb4c - 0xb38];
    cBehaviorTreeData_s00dc_2720* mpGameData;                            // +0xb4c behaviour-tree data
    uint8_t  padb50[0xb5e - 0xb50];
    bool     mbDeadB5e;                                       // +0xb5e dead / despawned
    uint8_t  padb5f[4];
    // ---- predicates / lookups (plain members, direct calls in the original) ----
    bool          IsBaby();                                   // 0x00c0b770
    bool          IsEpic();                                   // 0x00c0c0e0
    cCombatant_s00dc_2720*   GetCombatantTarget();                       // 0x00c0ee60
    cGroup*       GetTargetGroup();                           // 0x00c38b00
    // ---- posse-member interface (0x00c3daa0 / 0x00c3be70) ----
    void SetTargetDistance(float distance);                   // 0x00c3daa0
    void SetTargetPosition(const Vec3& position);             // 0x00c3be70
};
}
namespace EA {
template <class T>
class AutoRefCount_s00dc_2720 {
public:
    T* mpObj;                                                 // +0x00
    AutoRefCount_s00dc_2720() : mpObj(0) {}
    explicit AutoRefCount_s00dc_2720(T* p) : mpObj(p) { if (mpObj) mpObj->AddRef(); }
    AutoRefCount_s00dc_2720(const AutoRefCount_s00dc_2720& o) : mpObj(o.mpObj) { if (mpObj) mpObj->AddRef(); }
    ~AutoRefCount_s00dc_2720() { if (mpObj) mpObj->Release(); }
    AutoRefCount_s00dc_2720& operator=(const AutoRefCount_s00dc_2720& o) {
        if (mpObj != o.mpObj) {
            T* p = o.mpObj;
            if (p) p->AddRef();
            T* old = mpObj;
            mpObj = p;
            if (old) old->Release();
        }
        return *this;
    }
    T* Get() const { return mpObj; }
};  // namespace EA
}
namespace eastl {
struct AgentDistanceCompare {
    SP::Vec3 mOrigin;
    bool FUN_00ac0730(const SP::cSpatialSub* a, const SP::cSpatialSub* b) const;
};
}
using SP::Vec3;
using SP::cSpatialObject_s00dc_2720;
using SP::cSpatialSub;
using SP::cLocomotion;
using SP::cCombatant_s00dc_2720;
using SP::cGroup;
using eastl::AgentDistanceCompare;
void FUN_00b2af00(cSpatialObject_s00dc_2720** a, cSpatialObject_s00dc_2720** b);                     // swap the two slots
void FUN_00aca890(cSpatialObject_s00dc_2720** begin, cSpatialObject_s00dc_2720** first, AgentDistanceCompare pred);
void FUN_00aca900(cSpatialObject_s00dc_2720** begin, cSpatialObject_s00dc_2720** first, AgentDistanceCompare pred);
void FUN_00aca0c0(cSpatialObject_s00dc_2720** begin, int zero, int count, int start,
                  EA::AutoRefCount_s00dc_2720<cSpatialObject_s00dc_2720> value, AgentDistanceCompare pred);
static __forceinline cSpatialSub* ObjectSpatial(cSpatialObject_s00dc_2720* o)
{
    return o ? &o->mSpatial120 : 0;
}
// ---- items of slice s00dc2720 end

// ---- items of slice s00dc3940 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char  g_mode_1654c10;                      // 0x01654c10
extern char* g_sounds_45a0[1];                    // 0x0147c3a8
extern char* g_sounds_4610[1];                    // 0x0147c3b4
#define VFN(p, off)     (((void**)*(void**)(p))[(off) / 4])
#define VC0(p, off)     ((int(__thiscall*)(void*))VFN(p, off))(p)
#define D(p, off) (*(int*)((char*)(p) + (off)))
void*  EA_GetSystemAT();                                           // 0x00a206f0
// ---- items of slice s00dc3940 end

// ---- items of slice s00dc57a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint32;
struct Vec3f { float x, y, z; };
struct Sub508 {
    float Get();                // thiscall, x87 float return (FUN_00bfc400)
};
struct Obj_s00dc_57a0 {
    char vtbl_pad[4];           // vtable pointer lives at +0; slots called via typed pointers below
};
struct Self {
    char pad[0x508];
    Sub508 mSub;                // +0x508
    Obj_s00dc_57a0* GetObj();              // thiscall, no args (FUN_00c9fee0)
    void Apply(Vec3f v);        // thiscall, Vec3f by value, callee pops 0xc (FUN_00c9fb40)
    void Take(Vec3f* p);        // thiscall, one pointer arg, callee pops 4 (FUN_00ca97a0)
};
void Helper(float* a, float* b, Self* self, Obj_s00dc_57a0* obj);
typedef Vec3f* (__thiscall *Vfn2)(Obj_s00dc_57a0* self, float a, float b); // vslot 11, two float args
// ---- items of slice s00dc57a0 end

// ---- items of slice s00dc77d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void __cdecl FUN_00b5b6f0(void* pTicker);        // 0x00b5b6f0  ticker registration
extern "C" void __cdecl FUN_00b5b690(void* pTicker);        // 0x00b5b690  ticker base teardown
struct cSrc5 {                     // param_2: object pointer at +0, uint at +0x14
  void*    mpObj;                  // +0x00 AutoRefCount<T> (raw pointer)
  uint32_t pad0[4];                // +0x04..+0x13
  uint32_t mVal;                   // +0x14
};
struct cSub5 {                     // sub-object at +0x64 (size 0x14)
  uint8_t pad[0x14];
  void SetFrom(cSrc5* src);        // 0x00ca0940 thiscall, ret 4
};
struct cMgr5 {                     // returned by FUN_00b3d290 (cdecl, no args)
  uint32_t Get();                  // 0x00ac15e0 thiscall, returns eax
};
struct cEffect5 {                  // EA::Swarm::cIVisualEffect (AutoRefCount target at +0x94)
  void Apply(uint32_t v);          // 0x00bdf6d0 thiscall, ret 4
};
struct cAnim5 {                    // SP::cAnimatingCreature (AutoRefCount target at +0x9c)
  void Release();                  // 0x00a05270 thiscall
};
struct cConvertCityOrder5 {
  uint8_t   pad0[0x64];
  cSub5     mSub64;                // +0x64
  uint32_t  m78;                   // +0x78
  uint8_t   pad1[0x90 - 0x7c];
  uint32_t  mGen90;                // +0x90
  void*     mEffect94;             // +0x94 AutoRefCount<cIVisualEffect>
  uint32_t  m98;                   // +0x98
  void*     mAnim9c;               // +0x9c AutoRefCount<cAnimatingCreature>
  uint8_t   pad2[0xac - 0xa0];
  uint8_t   mbFlagAC;              // +0xac

  void Init(cSrc5* src);           // 0x00dc7e00 thiscall, ret 4
  void FUN_00dc7dd0(cSrc5* src);   // 0x00dc7dd0 thiscall, ret 4
};
class cTreeSub {
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
virtual void v28();
  virtual float* v2c();                                  // 0x2c  world position
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
virtual void v5c();
virtual void v60();
virtual void v64();
virtual void v68();
virtual void v6c();
  virtual void v70();
  virtual long double v74();                             // 0x74  radius (x87)
virtual void v78();
virtual void v7c();
virtual void v80();
virtual void v84();
virtual void v88();
virtual void v8c();
virtual void v90();
virtual void v94();
virtual void v98();
virtual void v9c();
virtual void va0();
virtual void va4();
virtual void va8();
virtual void vac();
virtual void vb0();
virtual void vb4();
virtual void vb8();
virtual void vbc();
virtual void vc0();
virtual void vc4();
virtual void vc8();
virtual void vcc();
virtual void vd0();
virtual void vd4();
virtual void vd8();
virtual void vdc();
virtual void ve0();
virtual void ve4();
  virtual void ve8();
  virtual void vec();                                    // 0xec  path-failure notify
};
class cStarEntry {
public:
  virtual void v00();
  virtual void v04();                                    // 0x04  Release
  virtual void v08();
  virtual void* v0c(uint32_t id);                        // 0x0c
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
  virtual float* v2c();                                  // 0x2c  world position
};
struct cStarRecordVector {
  cStarEntry** mpBegin;      // +0x00
  cStarEntry** mpEnd;        // +0x04
  cStarEntry** mpCapacity;   // +0x08
  void Destroy();            // 0x00ae6970
};
class cStarCollector {
public:
  void Collect(int32_t id, cStarRecordVector* pOut);     // 0x00f40d00 thiscall, ret 8
};
class cStarSource {
public:
  uint8_t pad00[0x74];
  cStarCollector* mp74;      // 0x74
};
struct cVehicleTreeState {
  uint8_t pad00[0x4b8];
  int32_t m4b8;              // 0x4b8
  uint8_t pad4bc[8];
  int32_t m4c4;              // 0x4c4
};
class cVehicleTree_s00dc_77d0 {
public:
  cVehicleTreeState* GetState();                         // 0x00c9f1c0
  uint8_t pad04[0x34];
  cTreeSub mSub34;                                       // 0x34
};
class cSimBase {
public:
  cSimBase();                                            // 0x00b5b6c0
};
struct cGroupOrderVector {   // eastl::vector<AutoRefCount<cVehicleGroupOrder>>
  void* mpBegin;             // +0x00
  void* mpEnd;               // +0x04
  void* mpCapacity;          // +0x08
  void Destroy();            // 0x00ae6970
};
struct cSpatialVector {      // eastl::vector<AutoRefCount<cSpatialObject>>
  void* mpBegin;             // +0x00
  void* mpEnd;               // +0x04
  void* mpCapacity;          // +0x08
  void Destroy();            // 0x00ad92d0
};
class cVehicleTicker_s00dc_77d0 : public cSimBase {
public:
  cVehicleTicker_s00dc_77d0();                                      // 0x00dc7d70
  void Destroy();                                        // 0x00dc7cc0

  void* mpVt00;     // 0x00
  uint32_t pad04;            // 0x04
  void* mpVt08;     // 0x08
  uint32_t pad0c;            // 0x0c
  cGroupOrderVector mGroupOrders;   // 0x10
  uint8_t pad1c[8];          // 0x1c
  cSpatialVector mVoxSoundIds;      // 0x24
  uint8_t pad30[8];          // 0x30
  cSpatialVector m38;        // 0x38
};
extern cVehicleTicker_s00dc_77d0* g_1699ab8;    // 0x01699ab8
extern cStarSource* g_16c7aa4;     // 0x016c7aa4
// ---- items of slice s00dc77d0 end

// ---- items of slice s00dc7eb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void __cdecl CopyImpl_do_copy(void* src, void* end, void* dst);
struct CultureHashPayload {
    uint32_t mField00;              // +0x00
    float mField04;                 // +0x04
    float mField08;                 // +0x08
    float mField0c;                 // +0x0c
    float mField10;                 // +0x10
    float mField14;                 // +0x14
    float mField18;                 // +0x18
    float mField1c;                 // +0x1c

    CultureHashPayload& operator=(const CultureHashPayload& src)
    {
        mField04 = src.mField04;
        mField00 = src.mField00;
        mField08 = src.mField08;
        mField0c = src.mField0c;
        mField10 = src.mField10;
        mField14 = src.mField14;
        mField18 = src.mField18;
        mField1c = src.mField1c;
        return *this;
    }
};
struct CultureHashNode {
    CultureHashPayload mPayload;    // +0x00
    CultureHashNode* mpNext;        // +0x20
};
struct CultureHashTail {
    uint32_t a, b, c;               // +0x00..+0x0b
};
struct CultureHash {
    uint32_t mField00;              // +0x00
    CultureHashNode** mBuckets;     // +0x04
    uint32_t mBucketCount;          // +0x08
    uint32_t mElementCount;         // +0x0c
    CultureHashTail mTail;          // +0x10..+0x1b

    CultureHash(const CultureHash& src);
    void Swap(CultureHash& other);
};
struct DecalMapTree {
    uint32_t mPad[0x1c / 4];
    void Find(void* out, const void* key, uint32_t hash);
};
struct Removable {
    virtual void AddRef();
    virtual void Release();
};
union TaggedPtr {
    uint32_t mValue;                // +0x00
    Removable* mPtr;                // +0x00
    struct {
        uint8_t mTag;               // +0x00
        uint8_t mRest[3];           // +0x01
    } mBytes;
};
struct DecalRemover {
    uint32_t mPad[0x34 / 4];        // +0x00..0x33
    DecalMapTree mMap;              // +0x34
    void Remove(Removable* p);
};
struct RemoveLocals {
    Removable* key;                 // +0x00
    uint32_t it[2];                 // +0x04
};
struct RemoveArg : Removable {
    uint32_t mPad04[(0x34 - 0x04) / 4]; // +0x04..0x33
    uint32_t mField34;                  // +0x34
    void Method(int);                   // 0x00ca0000
};
struct DecalEntry {
    uint8_t mData[0x178];
    void RemoveDecal(void* arg);        // 0x00afedf0
};
struct DecalManager {
    virtual void pad00();
    virtual void pad04();
    virtual void pad08();
    virtual void pad0c();
    virtual void pad10();
    virtual void pad14();
    virtual void pad18();
    virtual void pad1c();
    virtual void pad20();
    virtual void pad24();
    virtual void pad28();
    virtual bool Skip();                // +0x2c
    uint32_t mPad04[(0x50 - 0x04) / 4]; // +0x04..0x4f
    Removable** mVec50Begin;            // +0x50
    Removable** mVec50End;              // +0x54
    uint32_t mPad58[(0x7c - 0x58) / 4]; // +0x58..0x7b
    DecalEntry* mDecalBegin;            // +0x7c
    DecalEntry* mDecalEnd;              // +0x80
    void Remove(RemoveArg* arg);
};
// ---- items of slice s00dc7eb0 end

// ---- items of slice s00dca100 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void*              __cdecl GetCurrentGameMode();            // 0x00b5b800
struct Vector3_s00dc_a100 {
    float x, y, z;
    Vector3_s00dc_a100() {}
    Vector3_s00dc_a100(const Vector3_s00dc_a100& v) : x(v.x), y(v.y), z(v.z) {}
};
struct Vector4 {
    float x, y, z, w;
};
struct cSpatialObject_s00dc_a100 {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a)
    virtual const Vector3_s00dc_a100& GetPosition();                          // +0x2c
    PV(0c) PV(0d) PV(0e) PV(0f) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15)
    virtual bool IsPlayerControlled();                             // +0x58
    virtual Vector3_s00dc_a100 GetVelocity();                                 // +0x5c

    bool IsNearGoal();                                             // 0x00c42e20
    bool Fc42210(float f);                                         // 0x00c42210
};
struct cSPTimer_s00dc_a100 {
    void Restart();                                                // 0x00bc3130
    uint64_t GetElapsedTime();                                     // 0x00bc3190
};
struct cCivilization_s00dc_a100 {
    char    pad[0xc4];
    Vector3_s00dc_a100 mPos;                                                  // +0xc4
};
struct cCity_s00dc_a100;
struct cCivNoun {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09)
    PV(0a) PV(0b) PV(0c) PV(0d) PV(0e) PV(0f) PV(10) PV(11) PV(12)
    virtual int Vf4c();                                            // +0x4c
    char     pad0[0x104];
    cSPTimer_s00dc_a100 mTimer108;                                            // +0x108
    char     pad10c[0x128 - 0x10c];
    cSPTimer_s00dc_a100 mTimer128;                                            // +0x128
    char     pad12c[0x434 - 0x129];
    uint32_t mState434;                                            // +0x434
    int      mField438;                                            // +0x438
    cCivilization_s00dc_a100* GetPosHolder();                                 // placeholder
    bool Fbef7e0();                                                // 0x00bef7e0 (mState434 <= 4)
    void Fbf0330(cCity_s00dc_a100* city);                                     // 0x00bf0330
    void Fbef8c0();                                                // 0x00bef8c0 (mTimer108.Restart)
    Vector3_s00dc_a100 mPosC4();                                              // placeholder
    float Fbf0640();                                               // 0x00bf0640
    float Fbf06d0();                                               // 0x00bf06d0
    float GetMoney();                                              // 0x00bef6d0
    void  SpendMoney(float amount);                                // 0x00bef710
    void  FcivicRadiusAccum(float f, int n);                       // 0x00befd80
};
struct cCivNounPos {            // the +0xc4 position of a noun
    char    pad[0xc4];
    Vector3_s00dc_a100 mPos;
};
struct cCity_s00dc_a100 {
virtual void pad0();
virtual void pad1();
virtual void pad2();
    virtual cCity_s00dc_a100* Cast(uint32_t typeID);                          // +0x0c
    PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a)
    virtual bool IsDestroyed();                                    // +0x2c
    PV(0c) PV(0d) PV(0e) PV(0f) PV(10) PV(11) PV(12)
    virtual int Vf4c();                                            // +0x4c
    char           pad50[0x120 - 4];
    cSpatialObject_s00dc_a100 mSpatial;                                       // +0x120
    char           pad124[0x590 - 0x124];
    cCivilization_s00dc_a100* mpCivilization;                                 // +0x590
    char           pad594[0x728 - 0x594];
    cSPTimer_s00dc_a100       mCommTimer;                                     // +0x728

    bool Fbdb200(int nounID);                                      // 0x00bdb200
    void Fbdb3b0(struct cVehicle_s00dc_a100* v, int n);                       // 0x00bdb3b0
    void Fbe1820(int nounID);                                      // 0x00be1820
    cCivilization_s00dc_a100* GetCivilization();                              // 0x00bd9bf0
};
struct cGameData_s00dc_a100 {      // embedded at +0x508 of the vehicle
    PV(00) PV(01) PV(02) PV(03)
    virtual int GetNounID();                                       // +0x10
};
struct CityRef {
    cCity_s00dc_a100* mpCity;
};
struct cVehicle_s00dc_a100 {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b)
    PV(0c) PV(0d) PV(0e) PV(0f) PV(10) PV(11) PV(12)
    virtual int Vf4c();                                            // +0x4c
    char           pad4[0x30];
    cSpatialObject_s00dc_a100 mLoco;                                          // +0x34
    char           pad38[0x2a4 - 0x38];
    union {
        uint8_t    mPathFlags;                                     // +0x2a4
        uint32_t   mPathFlags32;
    };
    char           pad2a8[0x508 - 0x2a8];
    cGameData_s00dc_a100      mGameData;                                      // +0x508

    CityRef* Fca71d0();                                            // 0x00ca71d0
    void Fca7250(const char* msg);                                 // 0x00ca7250
    void Fcaa900();                                                // 0x00caa900
    void Fcac000(cCity_s00dc_a100* city, int a, int b);                       // 0x00cac000
    void Fcacbe0();                                                // 0x00cacbe0
    void Fca80e0(int n);                                           // 0x00ca80e0
};
void __cdecl AttemptRepark(cVehicle_s00dc_a100* v);                            // 0x00dc9430
struct cCommunitySpatial {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a)
    virtual Vector3_s00dc_a100* GetPoint(float f, int n);                     // +0x2c
    PV(0c) PV(0d)
    virtual void SetPosition(const Vector3_s00dc_a100& pos);                  // +0x38
    PV(0f) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15)
    virtual bool IsPlayerControlled();                             // +0x58
};
struct cCommunity_s00dc_a100 {
    PV(00) PV(01) PV(02)
    virtual cCommunity_s00dc_a100* Cast(uint32_t typeID);                     // +0x0c
    PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b)
    PV(0c) PV(0d) PV(0e) PV(0f) PV(10) PV(11) PV(12)
    virtual int Vf4c();                                            // +0x4c
    char pad4[0x30];
    cCommunitySpatial mSpatial;                                    // +0x34
    cCivNoun* GetNoun();                                           // 0x00bfdf80
};
struct cPathArcBuilder {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09)
    PV(0a) PV(0b) PV(0c) PV(0d) PV(0e) PV(0f) PV(10) PV(11)
    virtual void SetCiv(int civ);                                  // +0x48
    char pad4[0x30];
    cCommunitySpatial mSpatial;                                    // +0x34
    void Start(cCivNoun* civ, cCommunity_s00dc_a100* city, const Vector3_s00dc_a100* pos, float speed, int flag);  // 0x00cbe640
};
struct cGameNounManager_s00dc_a100 {
    cCivNoun* Fb25f40(int nounID);                                 // 0x00b25f40
    cPathArcBuilder* Fbfe7a0();                                    // 0x00bfe7a0
};
struct cRelationshipManager_s00dc_a100 {
    float Fd00d60(cCivilization_s00dc_a100* civ, cCivNoun* noun, int n);      // 0x00d00d60
    float RecordEvent(int a, int b, int id, float value);          // 0x00d06240
};
struct cScoreTable {
    float Fceee30(cCity_s00dc_a100* city, cCivNoun* noun);                    // 0x00ceee30
};
struct cStrategy {
    void Fcf9040(cCity_s00dc_a100* city, uint32_t a, uint32_t b, const Vector3_s00dc_a100& pos, const Vector4* v, int c, int d);   // 0x00cf9040
};
struct cStarRecord_s00dc_a100 {
    char pad[0x184];
    int  mCommContext;                                             // +0x184
    int  GetCommContext();                                         // 0x00ce6950
    int  GetCommContext(uint32_t id, uint32_t group, int mode);    // 0x00ce6950
};
struct cPlanet_s00dc_a100 {
    char         pad[0x13c];
    cStarRecord_s00dc_a100* mpStarRecord;                                     // +0x13c
};
struct cCommManager {
    void ShowCommEvent(cCity_s00dc_a100* a, cCity_s00dc_a100* b, int ctx, uint32_t id, uint32_t grp, int e);   // 0x00aeb760
    void ShowCommEvent(cCivNoun* noun, int a, int ctx);                                  // 0x00aeb760
};
struct cSomething {
    void Fae37c0(int n, Vector3_s00dc_a100 pos);                              // 0x00ae37c0
};
struct cAudioSystem {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b)
    PV(0c) PV(0d) PV(0e) PV(0f) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17)
    virtual void PlaySoundAt(uint32_t id, const Vector3_s00dc_a100& pos, const Vector3_s00dc_a100& vel);   // +0x60
};
namespace EA {
namespace Random {
class RandomLinearCongruential_s00dc_a100 { public:
    double RandomDoubleUniform();                                  // 0x009360d0
};
}
}
extern EA::Random::RandomLinearCongruential_s00dc_a100 sMathRandom;           // 0x01601760
extern cScoreTable g_ScoreTable;                                   // 0x0169c254
extern cGameNounManager_s00dc_a100*  __cdecl NounManager_s00dc_a100();                   // 0x00b3d300
extern cRelationshipManager_s00dc_a100* __cdecl RelationshipManager();        // 0x00b3d2c0
extern cAudioSystem*      __cdecl AudioSystem();                   // 0x00b3d240
extern cCommManager*      __cdecl CommManager();                   // 0x00b3d4a0
extern cStrategy*         __cdecl CivModeStrategy();               // 0x00cf74c0
extern cSomething*        __cdecl Fb26930();                       // 0x00b26930
extern cPlanet_s00dc_a100*           __cdecl GetActivePlanet();               // 0x01021260
extern void __cdecl PlayEffectAt(uint32_t id, Vector3_s00dc_a100 pos);        // 0x00dc4560
extern bool __cdecl StandardVehicleMoveTick(cVehicle_s00dc_a100* v);          // 0x00dc95b0
struct TradeMem {
    int     mState;        // 0 heading to city, 1 at city
    float   mTime;
    bool    mFlag8;
    char    pad9[3];
    int     mFieldC;       // selects the mineral / relationship branch at state 1
};
static __forceinline bool Fail(cVehicle_s00dc_a100* self, const char* msg)
{
    self->Fca7250(msg);
    self->Fcaa900();
    return false;
}
static __forceinline bool AlreadyExists(cVehicle_s00dc_a100* self, cCity_s00dc_a100* city, const char* msg)
{
    self->Fca7250(msg);
    self->Fcac000(city, 5, 0);
    return false;
}
// ---- items of slice s00dca100 end

// ---- items of slice s00dcd720 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cSpatialObject_s00dc_d720 {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a)
    virtual const Vector3& GetPosition();                          // +0x2c
    PV(0c) PV(0d) PV(0e) PV(0f) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15)
    virtual bool Vf58();                                           // +0x58
    bool FUN_00c42210(float f);                                    // 0x00c42210
    PV(17) PV(18) PV(19) PV(1a) PV(1b) PV(1c) PV(1d) PV(1e) PV(1f)
    PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(2a) PV(2b) PV(2c) PV(2d)
    virtual void* IsType(uint32_t typeID);                         // +0xb8
};
struct cGameData_s00dc_d720 {
    PV(00) PV(01)
    virtual cSpatialObject_s00dc_d720* GetSpatial();                          // +0x08
    PV(03)
    virtual uint32_t GetOwnerID();                                 // +0x10
    PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b) PV(0c) PV(0d) PV(0e) PV(0f) PV(10) PV(11) PV(12) PV(13)
    virtual void SetAttackTarget(cGameData_s00dc_d720* target);               // +0x50
    float GetRange();                                              // 0x00bfc400
    bool FUN_00bfc600();                                           // 0x00bfc600
};
struct cEntityBase {
    virtual void AddRef();
    PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07)
    virtual uint32_t GetTypeID();                                  // +0x20
    uint32_t dpad04[(0x120 - 4) / 4];
};
struct cEntity : cEntityBase, cGameData_s00dc_d720 {
    uint32_t pad124[(0x290 - 0x120 - sizeof(cGameData_s00dc_d720)) / 4];
    int mf290;                                                     // +0x290
    uint32_t pad294;
    int mf298;                                                     // +0x298
    int mf29c;                                                     // +0x29c
    bool FUN_00bd3280(void* vehicle);                              // 0x00bd3280
};
struct cBuildingBase {
    virtual void AddRef();
    uint32_t dpad04[(0x588 - 4) / 4];
};
struct cBuilding_s00dc_d720 : cBuildingBase, cGameData_s00dc_d720 {
    bool FUN_00bd3550(void* vehicle);                              // 0x00bd3550
};
struct cCulturalConvertCityOrder_s00dc_d720 {
    virtual void AddRef();
    virtual void Release();                                        // +0x04
    PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a)
    virtual bool IsDone();                                         // +0x2c
    void FUN_00dc8c50(void* vehicle);                              // 0x00dc8c50
    void FUN_00dc8c00(void* vehicle);                              // 0x00dc8c00
    void FUN_00dcc350(void* vehicle);                              // 0x00dcc350
};
struct OrderRef {                                                  // EA::AutoRefCount<cCulturalConvertCityOrder>
    cCulturalConvertCityOrder_s00dc_d720* mpObject;
    OrderRef& operator=(cCulturalConvertCityOrder_s00dc_d720* p);             // 0x00b5f950
};
struct cCity_s00dc_d720;
struct cVehicle_s00dc_d720;
struct BuildingVector;
struct EntityVector_s00dc_d720;
struct cCulturalTargetBase {
    virtual void AddRef();
    virtual void Release();                                        // +0x04
    PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a)
    virtual bool IsDestroyed();                                    // +0x2c
    uint32_t dpad04[(0x38 - 4) / 4];
};
struct cCulturalTarget_s00dc_d720 : cCulturalTargetBase {
    cGameData_s00dc_d720 mGameData;                                           // +0x38
    uint32_t pad3c[(0x100 - 0x38 - sizeof(cGameData_s00dc_d720)) / 4];
    cSpatialObject_s00dc_d720 mSpatial;                                       // +0x100
    uint32_t pad104[(0x1d8 - 0x100 - sizeof(cSpatialObject_s00dc_d720)) / 4];
    int mf1d8;                                                     // +0x1d8
    uint32_t mf1dc;                                                // +0x1dc

    cCity_s00dc_d720* FUN_00bd84e0();                                         // 0x00bd84e0 (the target's city)
};
cCulturalTarget_s00dc_d720* __cdecl FUN_00bd8420(void* info);                 // 0x00bd8420
struct Civilization {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b) PV(0c) PV(0d) PV(0e) PV(0f)
    PV(10) PV(11) PV(12)
    virtual uint32_t GetPoliticalID();                             // +0x4c
};
struct cCity_s00dc_d720 {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a)
    virtual bool IsDestroyed();                                    // +0x2c
    Civilization* GetCivilization();                               // 0x00bd9bf0
    bool FUN_00bd7e20();                                           // 0x00bd7e20
    EntityVector_s00dc_d720* GetMembers();                                    // 0x00c8e810 (cTribe)
    void FUN_00be5700(BuildingVector* out);                        // 0x00be5700
    cCulturalTarget_s00dc_d720* FUN_00bd8d70(cVehicle_s00dc_d720* v);                    // 0x00bd8d70
};
struct EntityVector_s00dc_d720 { cEntity** mpBegin; cEntity** mpEnd; };
struct BuildingVector {                                            // fixed eastl::vector<AutoRefCount<cBuilding>>
    cBuilding_s00dc_d720** mpBegin;
    cBuilding_s00dc_d720** mpEnd;
    cBuilding_s00dc_d720** mpCapacity;
    uint32_t mAllocPad;
    cBuilding_s00dc_d720** mpFixedBuffer;                                     // +0x10
    uint32_t mCookie;
    cBuilding_s00dc_d720* mBuffer[32];
    BuildingVector()
    {
        mpBegin = mBuffer;
        mpEnd = mBuffer;
        mpCapacity = mBuffer + 32;
        mpFixedBuffer = mBuffer;
    }
    ~BuildingVector();                                             // 0x008e2b20
};
struct cEmpire_s00dc_d720 {
    int FUN_00bf0d10(cEntity* e);                                  // 0x00bf0d10
};
struct Info_s00dc_d720 {                                                      // FUN_00ca71d0 result
    cGameDataObj* mpObject;
    uint32_t dpad04[3];
    int mKind;                                                     // +0x10
};
struct cVehicleTicker_s00dc_d720 {
    void* GetGroupOrder(Info_s00dc_d720* info);                               // 0x00dcd430
};
cVehicleTicker_s00dc_d720* __cdecl FUN_00c9efc0();                            // 0x00c9efc0 (ticker singleton)
cCulturalConvertCityOrder_s00dc_d720* __cdecl FUN_00dc4c80(void* groupOrder); // 0x00dc4c80 (interface_cast)
struct VehicleList { cVehicle_s00dc_d720** mpBegin; cVehicle_s00dc_d720** mpEnd; };
struct cNounManager_s00dc_d720 {
    cEmpire_s00dc_d720* GetEmpire(uint32_t politicalID);                      // 0x00b25f40
    VehicleList* GetVehicles();                                    // 0x00ae73b0
};
cNounManager_s00dc_d720* __cdecl NounManager_s00dc_d720();                               // 0x00b3d300
struct cVehicleBase_s00dc_d720 {
    virtual void AddRef();
    virtual void Release();                                        // +0x04
    PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b) PV(0c) PV(0d) PV(0e) PV(0f)
    PV(10) PV(11) PV(12)
    virtual uint32_t GetPoliticalID();                             // +0x4c
    uint32_t dpad04[(0x34 - 4) / 4];
    cSpatialObject_s00dc_d720 mLoco;                                          // +0x34
    uint32_t pad38[(0x508 - 0x38) / 4];
};
struct cVehicle_s00dc_d720 : cVehicleBase_s00dc_d720, cGameData_s00dc_d720 {                        // game data base at +0x508
    uint32_t pad50c[(0xb20 - 0x508 - sizeof(cGameData_s00dc_d720)) / 4];
    int mState;                                                    // +0xb20

    void FUN_00caa900();                                           // 0x00caa900 (finish the order)
    void FUN_00ca7250(const char* msg);                            // 0x00ca7250 (log)
    Info_s00dc_d720* FUN_00ca71d0();                                          // 0x00ca71d0
    cSpatialObject_s00dc_d720* GetTarget();                                   // 0x00c9fee0
    cCity_s00dc_d720* FUN_00c9f3d0();                                         // 0x00c9f3d0
    void FUN_00dc4d00(cSpatialObject_s00dc_d720* s);                          // 0x00dc4d00
    void FUN_00c9fa30(cCulturalTarget_s00dc_d720* t);                         // 0x00c9fa30
};
cEntity* __cdecl FUN_00dc4ca0(cSpatialObject_s00dc_d720* target);             // 0x00dc4ca0
bool __cdecl IsValidFireTarget(cGameData_s00dc_d720* mine, cGameData_s00dc_d720* theirs);   // 0x00dc4e20 (anonymous namespace)
cGameData_s00dc_d720* __cdecl FUN_00dc69a0(cVehicle_s00dc_d720* v, Civilization* civ, int a, int b, int c);   // 0x00dc69a0
struct State {
    uint32_t mPoliticalID;
    OrderRef mOrder;                                               // +4
};
// ---- items of slice s00dcd720 end

// ---- items of slice s00dcf2e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void operator delete[](void* p);   // 0x00f47380
namespace SP {
struct cSPVector3 {
    float x, y, z;
    cSPVector3() {}
    cSPVector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    cSPVector3(const cSPVector3& v) { x = v.x; y = v.y; z = v.z; }
    float LengthSquared() const { return x * x + y * y + z * z; }
    cSPVector3 Normalized() const
    {
        float inv = 1.0f / sqrtf(x * x + y * y + z * z + 1e-8f);
        return cSPVector3(x * inv, y * inv, z * inv);
    }
    bool operator==(const cSPVector3& v) const { return x == v.x && y == v.y && z == v.z; }
};
}
namespace SP {
inline cSPVector3 operator-(const cSPVector3& a, const cSPVector3& b) { return cSPVector3(a.x - b.x, a.y - b.y, a.z - b.z); }
}
namespace SP {
class cSpatialObject_s00dc_f2e0 {
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
virtual void v28();
    virtual const cSPVector3& GetPosition();   // +0x2c
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
virtual void v5c();
virtual void v60();
virtual void v64();
virtual void v68();
virtual void v6c();
    virtual void v70();
    virtual float GetFootprintRadius();        // +0x74
virtual void v78();
virtual void v7c();
virtual void v80();
virtual void v84();
virtual void v88();
virtual void v8c();
virtual void v90();
virtual void v94();
virtual void v98();
virtual void v9c();
virtual void va0();
virtual void va4();
virtual void va8();
virtual void vac();
virtual void vb0();
virtual void vb4();
    virtual void* Cast(uint32_t type);         // +0xb8
    virtual void AddRef();                     // +0xbc
    virtual void Release();                    // +0xc0
};
}
namespace SP {
class cTargetAt {
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
virtual void v28();
    virtual const cSPVector3& GetPositionAt(float a, float b);   // +0x2c
};
}
namespace SP {
struct cMoveRequest {
    char pad0[0x14];
    cSPVector3 mDst;                       // +0x14 (used when the waypoint list is empty)
    char pad20[0x5c - 0x20];
    int mField5C;                          // +0x5c
    const cSPVector3* GetDestination();    // 0x00c423c0
};
}
namespace SP {
class cLocomotive_s00dc_f2e0 : public cSpatialObject_s00dc_f2e0 {
public:
    virtual void vc4();
    virtual float GetDesiredSpeed();       // +0xc8
virtual void vcc();
virtual void vd0();
virtual void vd4();
virtual void vd8();
virtual void vdc();
    virtual void MoveTo(const cSPVector3& dst, float goalStopDistance, float acceptableStopDistance, bool relative);   // +0xe0
    virtual void MoveAround(const cSPVector3& center, float radius);   // +0xe4
    virtual void MoveTowards(const cSPVector3& dst);                    // +0xe8
    char pad0[0x270 - 0x4];
    uint32_t mFlags;                       // +0x2a4 in the vehicle
    char pad1[0x4d4 - 0x274];
    cMoveRequest* GetMoveRequest();        // 0x00c41ec0
};
}
namespace SP {
class cCity_s00dc_f2e0;
}
namespace SP {
struct HostileVec;
}
namespace SP {
class cCombatant_s00dc_f2e0 {
public:
virtual void v00();
virtual void v04();
    virtual cSpatialObject_s00dc_f2e0* GetSpatialObject();       // +0x08
    virtual void v0c();
virtual void v10();
virtual float GetRadius();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
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
    virtual void* Cast(uint32_t type);                 // +0x5c
    virtual void AddRef();                             // +0x60
    virtual void Release();                            // +0x64
    char pad[0xb1c - 0x508 - 4];
    float GetStat();                       // 0x00bfc400 (returns 0 when the +0x14 virtual returns 0)
};
}
namespace SP {
class cVehicle_s00dc_f2e0 {
public:
    void* mpVtable;                        // +0x00
    char pad04[0x30];
    cLocomotive_s00dc_f2e0 mLoco;                     // +0x34
    cCombatant_s00dc_f2e0 mCombatant;                 // +0x508
    int mLocomotion;                       // +0xb1c
    cSpatialObject_s00dc_f2e0* GetChaseTarget();      // 0x00c9fee0
    void SetAcceptableCenter(cSPVector3 center);   // 0x00c9fb40
    const cSPVector3* GetDestinationOut(cSPVector3* out);   // 0x00c9fdc0
    void FUN_00cacbe0();
    cCity_s00dc_f2e0* GetCurrentCity();               // 0x00c9f3d0
    struct HostileVec* GetHostiles();      // 0x00c9e860

    bool CanAttack(cCombatant_s00dc_f2e0* pTarget)
    {
        typedef bool (__thiscall *Fn)(cVehicle_s00dc_f2e0*, cCombatant_s00dc_f2e0*);
        return ((Fn)((void**)mpVtable)[0x40 / 4])(this, pTarget);
    }
    void Release()
    {
        typedef void (__thiscall *Fn)(cVehicle_s00dc_f2e0*);
        ((Fn)((void**)mpVtable)[4 / 4])(this);
    }
};
}
namespace SP {
static const uint32_t kVehicleType = 0x137e8e0;
}
namespace SP {
struct tSlot_s00dc_f2e0 {                   // cActionCircle::tSlot (0x18 bytes)
    bool mbOccupied;             // +0x0
    uint32_t pad04[2];
    cSPVector3 mPosition;        // +0xc
    void Occupy(cVehicle_s00dc_f2e0* pVehicle);   // 0x00afa030
};
}
namespace SP {
struct SlotVec {
    tSlot_s00dc_f2e0* mpBegin;
    tSlot_s00dc_f2e0* mpEnd;
    tSlot_s00dc_f2e0* mpCapacity;
    void erase(tSlot_s00dc_f2e0* first, tSlot_s00dc_f2e0* last);   // 0x00afc0d0
};
}
namespace SP {
float CircleRadius(float entityRadius, int count);   // 0x00af9e20 (cdecl)
}
namespace SP {
class cActionCircle_s00dc_f2e0 {
public:
    cSPVector3 mFacing;          // +0x00
    float mRadius;               // +0x0c
    float mSlotRadius;           // +0x10
    cSPVector3 mCenter;          // +0x14
    char pad20[0x50 - 0x20];
    SlotVec mSlots;              // +0x50
    char pad5c[0x64 - 0x5c];
    void Setup(const cSPVector3& center, float radius, const cSPVector3& facing, float altitude);   // 0x00af9cf0
    void Layout(float entityRadius, int count);   // 0x00afd1c0
    void RemoveAgent(cVehicle_s00dc_f2e0* pVehicle);         // 0x00afae50
    void FUN_00c2e4e0();                          // empty
};
}
namespace SP {
struct Formation;
}
namespace SP {
typedef void (__cdecl *SlotFunc)(Formation*, cActionCircle_s00dc_f2e0*, int);
}
namespace SP {
void __cdecl FUN_00dc7590(Formation*, cActionCircle_s00dc_f2e0*, int);
}
namespace SP {
void __cdecl FUN_00dc76e0();
}
namespace SP {
void __cdecl FUN_00dc6430();
}
namespace SP {
struct Formation {
    cLocomotive_s00dc_f2e0** mpEntBegin;    // +0x00
    cLocomotive_s00dc_f2e0** mpEntEnd;      // +0x04
    char pad08[0x58 - 0x08];
    cLocomotive_s00dc_f2e0* mpLeader;       // +0x58
    char pad5c[4];
    cSpatialObject_s00dc_f2e0* mpTarget;    // +0x60
    char pad64[0x7c - 0x64];
    float mMinDistance;          // +0x7c
    float mMaxDistance;          // +0x80
    float mEntityRadius;         // +0x84
    char pad88[0x94 - 0x88];
    float mTimerInterval;        // +0x94
    bool mbWaitingForPath;       // +0x98
    char pad99[0x104 - 0x99];
    cActionCircle_s00dc_f2e0 mCircle;       // +0x104
    SlotFunc mpSlotValidationFunc;   // +0x168
    void* mpLeaderSelectFunc;    // +0x16c
    void* mpMoveCommandFunc;     // +0x170
    char pad174[4];

    Formation();                 // 0x00afbaf0
    ~Formation();                // 0x00afbde0
    void AddEntity(cLocomotive_s00dc_f2e0* p);      // 0x00afed00
    void RemoveEntity(cLocomotive_s00dc_f2e0* p);   // 0x00afedf0
};
}
namespace SP {
struct FormationVec {
    Formation* mpBegin;
    Formation* mpEnd;
    Formation* mpCapacity;
    void DoInsertValue(Formation* pos, const Formation& value);   // 0x00dcf180
    void erase(Formation* first, Formation* last);                // 0x00dcf110

    __forceinline int size() const { return (int)(mpEnd - mpBegin); }
    __forceinline void push_back()
    {
        if (mpEnd < mpCapacity) {
            ::new (mpEnd++) Formation();
        } else {
            Formation tmp;
            DoInsertValue(mpEnd, tmp);
        }
    }
};
}
namespace SP {
template<class T, int N> struct SpFixedVec {
    T*       mpBegin;
    T*       mpEnd;
    T*       mpCapacity;
    uint32_t mAllocator;
    T*       mpFixed;
    uint32_t mPadding;
    T        mBuffer[N];

    __forceinline SpFixedVec() : mpBegin(mBuffer), mpFixed(mBuffer), mpEnd(mBuffer), mpCapacity(mBuffer + N) {}
    __forceinline ~SpFixedVec() { if (mpBegin && mpBegin != mpFixed) operator delete[](mpBegin); }

    void DoInsertValue(T* pos, const T& value);   // 0x00cd0550
    __forceinline int size() const { return (int)(mpEnd - mpBegin); }
    __forceinline void push_back(const T& value)
    {
        if (mpEnd < mpCapacity) {
            T* p = mpEnd++;
            if (p) *p = value;
        } else {
            DoInsertValue(mpEnd, value);
        }
    }
    __forceinline void erase(T* position)
    {
        if (position + 1 < mpEnd)
            memcpy(position, position + 1, (mpEnd - (position + 1)) * sizeof(T));
        --mpEnd;
    }
};
}
namespace SP {
typedef SpFixedVec<cVehicle_s00dc_f2e0*, 60> VehicleVec;
}
namespace SP {
bool __cdecl IsFormationMember(Formation* pFormation, cVehicle_s00dc_f2e0** ppVehicle);
}
namespace SP {
cVehicle_s00dc_f2e0* __cdecl FindClosestVehicle(VehicleVec* pList, const cSPVector3* pPosition, bool b);
}
namespace SP {
void __cdecl AttemptRepark(cVehicle_s00dc_f2e0* pVehicle);   // anonymous namespace, 0x00dc9430
}
namespace SP {
template<class T> inline void AssignRef(T*& slot, T* p)
{
    T* old = slot;
    if (p != old) {
        if (p) p->AddRef();
        slot = p;
        if (old) old->Release();
    }
}
}
namespace SP {
inline cVehicle_s00dc_f2e0* AsVehicle(cSpatialObject_s00dc_f2e0* p) { return p ? (cVehicle_s00dc_f2e0*)p->Cast(kVehicleType) : 0; }
}
namespace SP {
struct InvitedVehicles {
    char pad00[4];               // +0x34
    void* mpHead;                // +0x38
    void* mpTail;                // +0x3c
    uint32_t mAllocator;         // +0x40
    uint32_t mSize;              // +0x44
    uint32_t mFlags;             // +0x48
    void Clear(uint32_t allocator);   // 0x00eb6280

    void Reset()
    {
        mpHead = &mpHead;
        mpTail = &mpHead;
        mAllocator = 0;
        mSize = 0;
        mFlags = 0;
    }
};
}
namespace SP {
struct VehiclePtrVec {
    cVehicle_s00dc_f2e0** mpBegin;          // +0x50
    cVehicle_s00dc_f2e0** mpEnd;            // +0x54
    cVehicle_s00dc_f2e0** mpCapacity;       // +0x58
    void erase(cVehicle_s00dc_f2e0** first, cVehicle_s00dc_f2e0** last);   // 0x00e25bd0
};
}
namespace SP {
class cVehicleGroupOrder_s00dc_f2e0 {
public:
    char pad0[0x34];
    InvitedVehicles mInvitedVehicles;   // +0x34
    char pad4c[0x50 - 0x4c];
    cVehicle_s00dc_f2e0** mpVehiclesBegin;  // +0x50
    cVehicle_s00dc_f2e0** mpVehiclesEnd;    // +0x54
    cVehicle_s00dc_f2e0** mpVehiclesCapacity;   // +0x58
    char pad5c[0x78 - 0x5c];
    uint32_t mGroupMoveId;       // +0x78
    FormationVec mFormations;    // +0x7c

    void FormationMoveToTargets(int);   // 0x00dcf2e0
    void Clear();                       // 0x00dcfc40

    __forceinline void ClearBaseMembers()
    {
        cVehicle_s00dc_f2e0** pVehicleEnd = mpVehiclesEnd;
        cVehicle_s00dc_f2e0** pVehicleBegin = mpVehiclesBegin;
        ((VehiclePtrVec*)&mpVehiclesBegin)->erase(pVehicleBegin, pVehicleEnd);

        InvitedVehicles* pInvited = &mInvitedVehicles;
        pInvited->Clear(pInvited->mAllocator);
        FormationVec* pFormations = &mFormations;
        void** pHead = &pInvited->mpHead;
        *pHead = pHead;
        pInvited->mpTail = pHead;
        pInvited->mAllocator = 0;
        *(uint8_t*)&pInvited->mSize = 0;
        pInvited->mFlags = 0;

        Formation* pFormBegin = pFormations->mpBegin;
        Formation* pFormEnd = pFormations->mpEnd;
        pFormations->erase(pFormBegin, pFormEnd);
    }
};
}
namespace SP {
static const uint32_t kBuildingType = 0xe9cb8ba;
}
namespace SP {
static const uint32_t kProtectBuildingFlag = 0x1007ae63;
}
namespace SP {
class cLocomotiveView {
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
virtual void v28();
    virtual const cSPVector3& GetPosition();      // +0x2c
};
}
namespace SP {
class cBuilding_s00dc_f2e0 {
public:
virtual void v00();
virtual void v04();
virtual void v08();
    virtual int HasFlag(uint32_t flag);            // +0x0c
    char pad04[0x120 - 0x04];
    cCombatant_s00dc_f2e0 mCombatant;                         // +0x120
};
}
namespace SP {
class cCityMemberView {
public:
virtual void v00();
virtual void v04();
virtual void v08();
    virtual int HasFlag(uint32_t flag);            // +0x0c
    char pad04[0x34 - 0x04];
    cLocomotiveView mLoco;                         // +0x34
    char padLoco[0x120 - 0x34 - sizeof(cLocomotiveView)];
    cCombatant_s00dc_f2e0 mCombatant;                         // +0x120
};
}
namespace SP {
struct cTargetProviderView {
    char pad00[0x588];
    cCombatant_s00dc_f2e0 mCombatant;                         // +0x588
};
}
namespace SP {
struct MemberVec {
    cCityMemberView** mpBegin;
    cCityMemberView** mpEnd;
    cCityMemberView** mpCapacity;
};
}
namespace SP {
struct HostileVec {
    cCombatant_s00dc_f2e0** mpBegin;
    cCombatant_s00dc_f2e0** mpEnd;
    cCombatant_s00dc_f2e0** mpCapacity;
};
}
namespace SP {
typedef SpFixedVec<cTargetProviderView*, 16> TargetVec;
}
namespace SP {
class cCivilization_s00dc_f2e0 {
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
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
    virtual uint32_t GetOwnerId();                 // +0x4c
};
}
namespace SP {
class cCity_s00dc_f2e0 {
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
virtual void v28();
    virtual bool IsDestroyed();                    // +0x2c

    cCivilization_s00dc_f2e0* GetCivilization();              // 0x00bd9bf0
    cBuilding_s00dc_f2e0* GetCityHall();                      // 0x00bd9b40
    int DefenseLevel();                            // 0x00bd9bb0
    int Population();                              // 0x00bd9b70
    MemberVec* GetMembers();                       // 0x00c8e810
    void CollectTargets(TargetVec* out);           // 0x00be5700
    cCombatant_s00dc_f2e0* GetBestOpportunityTarget(cVehicle_s00dc_f2e0* pVehicle, cCivilization_s00dc_f2e0* pCiv,
                                         int a, int b, int c);   // 0x00dc69a0
};
}
namespace SP {
struct CombatantRef {
    cCombatant_s00dc_f2e0* mpObject;                          // +0x00
    void Release();                                // 0x00ae6670
    void Set(cCombatant_s00dc_f2e0* pObject);                 // 0x00ae6690
};
}
namespace SP {
struct CombatantRefVec {
    CombatantRef* mpBegin;
    CombatantRef* mpEnd;
    CombatantRef* mpCapacity;
};
}
namespace SP {
class cMilitaryAttackCityOrder_s00dc_f2e0 : public cVehicleGroupOrder_s00dc_f2e0 {
public:
    char pad88[0x94 - 0x88];
    cCity_s00dc_f2e0* mpCity;                                 // +0x94
    uint32_t mAttackerId;                          // +0x98
    CombatantRefVec mCurrentBestTarget;            // +0x9c
    char padA8[0xb0 - 0xa8];
    CombatantRefVec mNextBuildingTarget;           // +0xb0

    cCombatant_s00dc_f2e0* GetCurrentTarget(cVehicle_s00dc_f2e0* pVehicle);   // 0x00dcfc90
};
}
namespace SP {
class cCulturalTarget_s00dc_f2e0 {
public:
    virtual void v00();
    virtual void Release();                        // +0x04
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
    virtual void v28();
    virtual bool IsDestroyed();                    // +0x2c

    void RemoveVehicleGroup(uint32_t groupId);     // 0x00be3230
};
}
namespace SP {
class cCulturalConvertCityOrder_s00dc_f2e0 : public cVehicleGroupOrder_s00dc_f2e0 {
public:
    char pad88[0x94 - 0x88];
    cCulturalTarget_s00dc_f2e0* mpCulturalTarget;             // +0x94
    uint32_t mAttackerId;                          // +0x98
    void* mpHologram;                              // +0x9c
    cVehicle_s00dc_f2e0* mpHoloVehicle;                       // +0xa0
    void* mpHoloEffect;                            // +0xa4

    ~cCulturalConvertCityOrder_s00dc_f2e0();                  // 0x00dd0180
    void ClearHologramEffects();                   // 0x00dc6530
};
}
namespace SP {
bool __cdecl IsValidFireTarget(cCombatant_s00dc_f2e0* pSelf, cCombatant_s00dc_f2e0* pTarget);   // 0x00dc4e20
}
namespace SP {
cBuilding_s00dc_f2e0* __cdecl InterfaceCastBuilding(CombatantRef* pRef);             // 0x00cb4630
}
// ---- items of slice s00dcf2e0 end

// @ 0x00b5b5d0
void* AdjustThunk_00b5b5d0::FUN_00b5b5d0_adjust(unsigned id)
{
    char* self = (char*)this;
    if (id == 0x11416b8) return self - 8;
    if (id == 0x179c807) return (self - 8) ? self : 0;
    return 0;
}

// @ 0x00dc2e40
cSpatialObject_s00dc_2720** FUN_00dc2e40(cSpatialObject_s00dc_2720** first, cSpatialObject_s00dc_2720** last, cSpatialObject_s00dc_2720* cursor, AgentDistanceCompare pred)
{
    for (;;) {
        while (pred.FUN_00ac0730(ObjectSpatial(*first), ObjectSpatial(cursor)))
            ++first;
        do {
            --last;
        } while (pred.FUN_00ac0730(ObjectSpatial(cursor), ObjectSpatial(*last)));

        if (first >= last)
            break;
        FUN_00b2af00(first, last);
        ++first;
    }
    if (cursor)
        cursor->Release();
    return first;
}

// @ 0x00dc2ee0
void FUN_00dc2ee0(cSpatialObject_s00dc_2720** begin, cSpatialObject_s00dc_2720** first, cSpatialObject_s00dc_2720** last, AgentDistanceCompare pred)
{
    FUN_00aca890(begin, first, pred);
    for (cSpatialObject_s00dc_2720** it = first; it < last; ++it) {
        cSpatialObject_s00dc_2720* elem = *it;
        if (!pred.FUN_00ac0730(ObjectSpatial(elem), ObjectSpatial(*begin)))
            continue;

        if (elem)
            elem->AddRef();

        cSpatialObject_s00dc_2720* head = *begin;
        if (head != elem) {
            if (head)
                head->AddRef();
            *it = head;
            if (elem)
                elem->Release();
        }

        FUN_00aca0c0(begin, 0, (int)(first - begin), 0, EA::AutoRefCount_s00dc_2720<cSpatialObject_s00dc_2720>(elem), pred);
        if (elem)
            elem->Release();
    }
    FUN_00aca900(begin, first, pred);
}

// @ 0x00dc4560
void __cdecl FUN_00dc4560(void* name, float x, float y, float z)
{
    void* sys = EA_GetSystemAT();
    void* h = sys != 0 ? (void*)VC0(sys, 0x20) : 0;
    Start3dSoundByName(name, h, x, y, z);
}

// @ 0x00dc45a0
void __cdecl FUN_00dc45a0(void* self)
{
    float* p = (float*)VC0((char*)self + 0x34, 0x2c);
    if (SP_GetCurrentGameMode() == &g_mode_1654c10)
        return;
    void* sys = EA_GetSystemAT();
    void* h = sys != 0 ? (void*)VC0(sys, 0x20) : 0;
    Start3dSoundByName(g_sounds_45a0[D(self, 0xb20)], h, p[0], p[1], p[2]);
}

// @ 0x00dc4610
void __cdecl FUN_00dc4610(void* self)
{
    float* p = (float*)VC0((char*)self + 0x34, 0x2c);
    void* sys = EA_GetSystemAT();
    void* h = sys != 0 ? (void*)VC0(sys, 0x20) : 0;
    Start3dSoundByName(g_sounds_4610[D(self, 0xb20)], h, p[0], p[1], p[2]);
}

// @ 0x00dc4c20
void* KeyLookup::Match2E9(int key)
{
    if (key == 0x2e9ae69)
        return this;
    else
        return key == 0x2e98ab4 ? this : Default(key);
}

// @ 0x00dc4c40
void* KeyLookup::Match3DF(int key)
{
    if (key == 0x3df2cb9)
        return this;
    else
        return key == 0x2e98ab4 ? this : Default(key);
}

// @ 0x00dc4c60
void KeyLookup::Reset()
{
    Obj* p = mpObj;
    mpObj = 0;
    if (p)
        ((Vfn0)p->mpVtbl->mSlots[kVt04])(p);
}

// @ 0x00dc4d40
char FUN_00dc4d40(Obj* self, Obj* ctx)
{
    switch (self->mStateB1c) {
    case 0: {
        void* a = (void*)((VfnP)self->mSub34.mpVtbl->mSlots[kVt2C])(&self->mSub34);
        PlanetModel* pm1 = (PlanetModel*)SP_PlanetModel(a);
        int c1 = pm1->GetContinent();
        void* b = (void*)((VfnP)ctx->mSub120.mpVtbl->mSlots[kVt2C])(&ctx->mSub120);
        PlanetModel* pm2 = (PlanetModel*)SP_PlanetModel(b);
        int c2 = pm2->GetContinent();
        return c1 == c2;
    }
    case 1: {
        float* p = ((City*)ctx)->GetPositionPtr();
        float v[3];
        v[0] = p[0];
        v[1] = p[1];
        v[2] = p[2];
        if (v[0] != DAT_0169fa68 || v[1] != DAT_0169fa6c || v[2] != DAT_0169fa70)
            return self->C9e960(v);
        return 0;
    }
    case 2:
        return 1;
    }
    return 0;
}

// @ 0x00dc4e20
char IsValidFireTarget(Obj* ctx, Obj* target)
{
    if (!target)
        return 0;
    Obj* r = (Obj*)((VfnPI)target->mpVtbl->mSlots[kVt5C])(target, 0x17f243b);
    if (r && ((VfnB)r->mpVtbl->mSlots[kVt2C])(r))
        return 0;
    if (target->GetFileCount() == 2)
        return 0;
    unsigned int a = ((VfnR)ctx->mpVtbl->mSlots[kVt10])(ctx);
    unsigned int b = ((VfnR)target->mpVtbl->mSlots[kVt10])(target);
    if (b == a) {
        unsigned int a2 = ((VfnR)ctx->mpVtbl->mSlots[kVt10])(ctx);
        if (a2 != (unsigned int)-1)
            return 0;
    }
    Obj* h = (Obj*)((VfnPI)target->mpVtbl->mSlots[kVt5C])(target, 0x403df5f);
    if (!h)
        return 1;
    unsigned int hv = ((VfnR)h->mSub108.mpVtbl->mSlots[kVt10])(&h->mSub108);
    if (hv == (unsigned int)-1)
        return 0;
    if (h->mF224 >= DAT_013ec4d0)
        return 0;
    return 1;
}

// @ 0x00dc4ed0
void* FUN_00dc4ed0(float* pMin, float* pRange, Obj* self, Obj* other)
{
    int state = self->mStateB1c;
    uint8_t flag = 0;
    Obj* r = 0;
    if (other) {
        r = (Obj*)((VfnPI)other->mpVtbl->mSlots[kVtB8])(other, 0x137e8e0);
        if (r && r->mStateB1c == 2)
            flag = 1;
    }
    if ((state == 2) != (flag != 0)) {
        Obj* c = (state == 2) ? self : r;
        float f = c->C9eb80();
        if (f < *pRange) {
            double base = *pRange;
            float g = (float)sqrt(base * base - (double)f * (double)f);
            *pRange = g;
            if (g < *pMin)
                *pMin = g;
            return pRange;
        }
        *pRange = DAT_01473c70;
        *pMin = 0.0f;
        return pMin;
    }
    return r;
}

// @ 0x00dc4f90
char FUN_00dc4f90(Obj* self)
{
    Obj* t = ((AnimCtx*)self->Ca71d0())->mpTarget;
    if (t != 0) {
        Obj* target = (Obj*)((VfnPI)t->mpVtbl->mSlots[kVt0C])(t, 0x13f94d4);
        if (target != 0) {
            Obj* ctx = self ? (Obj*)&self->mSub508 : 0;
            if (IsValidFireTarget(ctx, target)) {
                if (((VfnB)self->mSub34.mpVtbl->mSlots[kVt50])(&self->mSub34)) {
                    Obj* d = (Obj*)((VfnP)target->mpVtbl->mSlots[kVt08])(target);
                    d->mField50 |= 0x800;
                }
                return 1;
            }
            self->Ca7250((char*)"(2) Invalid target.");
            self->Caa900();
            return 0;
        }
    }
    self->Ca7250((char*)"(1) No target.");
    self->Caa900();
    return 0;
}

// @ 0x00dc5030
char FUN_00dc5030(Obj* self, void* a1, void* a2, void* a3, void* a4, Obj** a5)
{
    Obj* o = *a5;
    if (((VfnB)o->mpVtbl->mSlots[kVt2C])(o)) {
        self->Caa900();
        return 0;
    }
    return 1;
}

// @ 0x00dc5050
void FUN_00dc5050(Obj* self, Obj* ctx)
{
    float v[3];
    int state = self->mStateB1c;
    if (state == 1) {
        float* p = ((City*)ctx)->GetPositionPtr();
        v[0] = p[0];
        v[1] = p[1];
        v[2] = p[2];
        if (v[0] == DAT_0169fa68 && v[1] == DAT_0169fa6c && v[2] == DAT_0169fa70)
            return;
        ((VfnF3)self->mSub34.mpVtbl->mSlots[kVtE8])(&self->mSub34, v, DAT_0147c368, DAT_0147c36c);
    } else {
        void* o = (void*)((VfnPI)self->mSub34.mpVtbl->mSlots[kVt2C])(&self->mSub34, state);
        void* r = (void*)((VfnVV)ctx->mpVtbl->mSlots[kVt6C])(ctx, v, o);
        ((Bec660*)r)->Run(v, o);
        if (v[0] == DAT_0169fa68 && v[1] == DAT_0169fa6c && v[2] == DAT_0169fa70)
            return;
        ((VfnF3)self->mSub34.mpVtbl->mSlots[kVtE8])(&self->mSub34, v, DAT_0147c368, DAT_0147c36c);
    }
    self->C9fb40(v[0], v[1], v[2], DAT_0147c368, DAT_0147c36c);
}

// @ 0x00dc51c0
void FUN_00dc51c0(Obj* self, Obj* ctx)
{
    float start[3];
    float dir[3];
    float tmp[3];
    if (self->mStateB1c == 1) {
        float* p = ((City*)ctx)->GetPositionPtr();
        start[0] = p[0];
        start[1] = p[1];
        start[2] = p[2];
        if (start[0] == DAT_0169fa68 && start[1] == DAT_0169fa6c && start[2] == DAT_0169fa70)
            return;
        float step = DAT_013eecd8;
        for (;;) {
            float* a = self->Cbd9480(tmp);
            float dx = start[0] - a[0];
            float dy = start[1] - a[1];
            float dz = start[2] - a[2];
            float len = sqrtf((dx * dx + dy * dy + dz * dz) + DAT_013ec4b8);
            float inv = DAT_01485720 / len;
            dir[0] = start[0] + inv * dx * step;
            dir[1] = start[1] + inv * dy * step;
            dir[2] = start[2] + inv * dz * step;
            PlanetModel* pm = (PlanetModel*)SP_PlanetModel(dir);
            float* q = pm->CalcSurface(dir, dir);
            dir[0] = q[0];
            dir[1] = q[1];
            dir[2] = q[2];
            step -= DAT_01470f1c;
            pm = (PlanetModel*)SP_PlanetModel(dir);
            if (pm->Cb7e3e0(dir))
                break;
            if (!(step > DAT_01485378))
                break;
        }
    } else {
        void* r = (void*)((VfnVV)ctx->mpVtbl->mSlots[kVt6C])(ctx, dir, (void*)5);
        ((CityVisualizer*)r)->RequestPosition(dir, 5);
        float* a = self->Cbd9480(tmp);
        float dx = dir[0] - a[0];
        float dy = dir[1] - a[1];
        float dz = dir[2] - a[2];
        float inv = DAT_01485720 / sqrtf(dx * dx + dy * dy + dz * dz);
        dir[0] = dir[0] + inv * dx * DAT_013eecd8;
        dir[1] = dir[1] + inv * dy * DAT_013eecd8;
        dir[2] = dir[2] + inv * dz * DAT_013eecd8;
        PlanetModel* pm = (PlanetModel*)SP_PlanetModel(dir);
        float* q = pm->DirectionToSurfacePosition(dir, dir);
        dir[0] = q[0];
        dir[1] = q[1];
        dir[2] = q[2];
    }
    ((VfnF3)self->mSub34.mpVtbl->mSlots[kVtE8])(&self->mSub34, dir, DAT_0147c368, DAT_0147c36c);
    self->C9fb40(dir[0], dir[1], dir[2], DAT_0147c368, DAT_0147c36c);
}

// @ 0x00dc54e0
float FUN_00dc54e0(Obj* self)
{
    Obj* o = (Obj*)self->C9fee0();
    if (!o)
        return 0.0f;
    Obj* r = (Obj*)((VfnPI)o->mpVtbl->mSlots[kVtB8])(o, 0x17f243b);
    if (r && ((VfnB)r->mpVtbl->mSlots[kVt2C])(r))
        return 0.0f;
    if ((self->mByte2a4 & 6) != 0)
        return 0.0f;
    float* p1 = (float*)((VfnP)o->mpVtbl->mSlots[kVt2C])(o);
    float x1 = p1[0];
    float y1 = p1[1];
    float z1 = p1[2];
    float* p2 = (float*)((VfnP)self->mSub34.mpVtbl->mSlots[kVt2C])(&self->mSub34);
    float dx = p2[0] - x1;
    float dy = p2[1] - y1;
    float dz = p2[2] - z1;
    float dist = sqrtf(dx * dx + (dy * dy + dz * dz));
    float lim = ((Sub*)&self->mSub508)->Cbfc400();
    Obj* h = (Obj*)self->mSub34.Cc41ec0();
    float d;
    if (h->mField5c == 0) {
        d = DAT_013eb1bc;
    } else {
        float* c = (float*)self->mSub34.Cc421f0();
        float ex = c[0] - x1;
        float ey = c[1] - y1;
        float ez = c[2] - z1;
        d = sqrtf(ez * ez + ey * ey + ex * ex);
    }
    if ((lim < dist && (lim < d || d == DAT_013eb1bc)) ||
        (dist < DAT_014763b0 && (d < DAT_014763b0 || d == DAT_013eb1bc)))
        return 1.0f;
    return 0.0f;
}

// @ 0x00dc5670
char FUN_00dc5670(Obj* self, void* a1, void* a2, uint32_t flags)
{
    Obj* o = (Obj*)self->C9fee0();
    if (!o)
        return 0;
    Obj* target = (Obj*)((VfnPI)o->mpVtbl->mSlots[kVtB8])(o, 0x13f94d4);
    if (!target)
        return 0;
    Obj* ctx = self ? (Obj*)&self->mSub508 : 0;
    if (!IsValidFireTarget(ctx, target))
        return 0;
    Obj* d = (Obj*)((VfnP)target->mpVtbl->mSlots[kVt08])(target);
    float* p = (float*)((VfnP)d->mpVtbl->mSlots[kVt2C])(d);
    float* q = self->C9e880();
    float dx = q[0] - p[0];
    float dy = q[1] - p[1];
    float dz = q[2] - p[2];
    float dist = sqrtf(dz * dz + (dy * dy + dx * dx));
    float extra = (flags & 0x100) ? DAT_0147c390 : 0.0f;
    float lim = ((Sub*)&self->mSub508)->Cbfc400() + extra;
    if (lim <= dist)
        return 0;
    ((VfnV)self->mSub508.mpVtbl->mSlots[kVt50])(&self->mSub508, target);
    return 1;
}

// @ 0x00dc5760
void FUN_00dc5760(Obj* self)
{
    Obj* p = self->mpObjB7c;
    if (p) {
        self->mpObjB7c = 0;
        ((Vfn0)p->mpVtbl->mSlots[kVtC0])(p);
    }
    ((VfnI)self->mSub508.mpVtbl->mSlots[kVt50])(&self->mSub508, 0);
    self->Cabe70();
}

// @ 0x00dc59d0
int ComputeAndApply(Self* self, uint32 a2, uint32 a3, uint32 a4, uint32 a5, float* out)
{
    if (out) {
        *out = 0.0f;
    }
    Obj_s00dc_57a0* obj = self->GetObj();
    if (!obj) {
        return 0;
    }
    float f8 = 8.0f;
    float f1 = self->mSub.Get() * 0.75f;
    float fLo = self->mSub.Get() - 1.0f;
    Helper(&f8, &f1, self, obj);
    void** vt = *(void***)obj;
    Vec3f* p1 = ((Vfn2)vt[11])(obj, f8, f1);
    self->Take(p1);
    vt = *(void***)obj;
    Vec3f* p2 = ((Vfn2)vt[11])(obj, f8, fLo);
    self->Apply(*p2);
    return 1;
}

// @ 0x00dc67d0
NOINLINE bool IsOpportunityTarget(cVehicle* self, void* target, void* cmp, bool flag3, bool flag4)
{
    if (!IsValidFireTarget(self ? &self->mGameData : 0, (cGameData*)target))
        return false;
    if (!target)
        return false;
    void* h = ((cInteractable*)target)->CastType(0x17f243b);
    if (!h)
        return false;
    uint32_t owner = self->mGameData.GetOwnerID();
    bool inv = FUN_00bfcc40(target, owner);
    void* e2 = ((cInteractable*)target)->CastType(0x137e8e0);
    void* best = h;
    if (e2) {
        if (flag3 && !inv)
            return false;
        if (cmp) {
            if (((cInteractable*)e2)->GetPoliticalID() != ((cInteractable*)cmp)->GetPoliticalID())
                return false;
        }
        uint32_t mine = ((cInteractable*)self)->GetPoliticalID();
        uint32_t theirs = ((cInteractable*)h)->GetPoliticalID();
        if (SP_RelationshipManager()->FUN_00d00a70(mine, theirs, 1) <= 1)
            return true;
        if (inv)
            return true;
    }
    void* h2 = ((cInteractable*)target)->CastType(0x436f315);
    if (h2) {
        if (self->mState == 1 && FUN_00bd3550(h2, self))
            return false;
        if (flag3 && !inv)
            return false;
        if (cmp) {
            if (((cInteractable*)h2)->GetPoliticalID() != ((cInteractable*)cmp)->GetPoliticalID())
                return false;
        }
        uint32_t mine = ((cInteractable*)self)->GetPoliticalID();
        uint32_t theirs = ((cInteractable*)h)->GetPoliticalID();
        if (SP_RelationshipManager()->FUN_00ae2e20(mine, theirs))
            return true;
        if (inv)
            return true;
    }
    void* t3 = ((cInteractable*)target)->CastType(0xce9f6639);
    if (t3 && FUN_00c0c0e0(t3)) {
        if (!flag4 && inv)
            return true;
    }
    return false;
}

// @ 0x00dc69a0
NOINLINE void* GetBestOpportunityTarget(cVehicle* self, void* a1, void* a2, void* a3, char a4)
{
    EntityVector* v = self->GetHostiles();
    for (void** it = v->mpBegin; it != v->mpEnd; ++it) {
        void* cur = *it;
        if (IsOpportunityTarget(self, cur, a1, (bool)a2, (bool)a3)) {
            if (!a4)
                return cur;
            bool ok = (*(bool(__thiscall**)(cGameData*, void*))VFn(&self->mGameData, 0x40))(
                          &self->mGameData, cur);
            if (ok)
                return cur;
        }
    }
    return 0;
}

// @ 0x00dc6a20
namespace SP {
void RemoveVehicles()
{
    while (g_sVehiclesToRemoveBegin != g_sVehiclesToRemoveEnd) {
        void* n = *(void**)(g_sVehiclesToRemoveEnd - 4);
        NounManager()->RemoveNoun(n);
        g_sVehiclesToRemoveEnd = g_sVehiclesToRemoveEnd - 4;
        void* p = *(void**)g_sVehiclesToRemoveEnd;
        if (p)
            ((cRefBase*)p)->Release();
    }
}
}  // namespace SP

// @ 0x00dc6a70
bool DefendCityOrder_Tick(cVehicle* self, int, int, int, int, float* timer, cCity* defended, float delta)
{
    float t = *timer + delta;
    *timer = t;
    if (t <= 3.0f)
        return true;
    *timer = 0.0f;
    Info* info = self->FUN_00ca71d0();
    if (!info->mpObject)
        goto destroyed;
    {
        cGameDataObj* obj = info->mpObject;
        void* ord = obj->Cast(0xee9b2232);
        if (!ord)
            goto destroyed;
        if ((*(bool(__thiscall**)(void*))VFn(ord, 0x2c))(ord))
            goto destroyed;
        if (((cInteractable*)ord)->GetPoliticalID() != ((cInteractable*)self)->GetPoliticalID())
            goto destroyed;
        {
            void* list = FUN_00bd81a0(ord);
            void* v = FUN_00cb45b0(self->GetTarget());
            void* best = 0;
            if (v && IsValidFireTarget(&self->mGameData, (cGameData*)v) && FUN_00bda6a0(list, &v))
                best = v;
            const Vector3& mp = self->mLoco.GetPosition();
            float bestDist = 3.402823466e+38F;
            void** p = *(void***)list;
            void** end = ((void***)list)[1];
            for (; p != end; ++p) {
                void* cand = *p;
                if (IsOpportunityTarget(self, cand, 0, false, false)) {
                    cSpatialObject* sp = ((cGameData*)cand)->GetSpatial();
                    const Vector3& tp = sp->GetPosition();
                    float d = (mp - tp).Length();
                    if (d < bestDist) {
                        bestDist = d;
                        best = cand;
                    }
                }
            }
            FUN_00dc4d00(self, best ? ((cGameData*)best)->GetSpatial() : 0);
            self->mGameData.SetAttackTarget((cGameData*)best);
            if (self->GetTarget() != 0)
                return true;
            const Vector3& dp = ((cCitySpatial*)((char*)defended + 0x120))->GetPosition();
            const Vector3& sp2 = self->mLoco.GetPosition();
            if ((sp2 - dp).Length() <= *(float*)0x13f1f04)
                return true;
            Vector3 tmp;
            tmp.x = 1.0f;
            tmp.y = 0.0f;
            tmp.z = 0.0f;
            void* r = FUN_00bdca30(&tmp, &self->mLoco, (float)self->mState);
            ((void(__thiscall*)(cSpatialObject*, void*, float))VFn(&self->mLoco, 0xe4))(
                &self->mLoco, r, 1.0f);
        }
    }
    return true;
destroyed:
    self->FUN_00ca7250("(44) DC: defended city destroyed");
    self->FUN_00caa900();
    return false;
}

// @ 0x00dc6ce0
void Node6ce0(cVehicle* self, int, int, int, int, NodeState6ce0* st)
{
    if (st->mState == 4)
        self->FUN_00ca80e0(0xe);
    if (st->mState == 7)
        self->FUN_00ca80e0(0x11);
    if (st->mpCommunity) {
        if (st->mpCommunity->Front() == self && *(int*)((char*)st->mpCommunity + 0x1ec) == 1)
            st->mpCommunity->Deactivate();
        st->mpCommunity->FUN_00bff290(self);
    }
    self->FUN_00c9ec40(1);
    cRefBase* o = (cRefBase*)st->mpObj;
    if (o)
        o->Release();
    cRefBase* c = (cRefBase*)st->mpCommunity;
    if (c)
        c->Release();
}

// @ 0x00dc6d60
float Node6d60(cVehicle* self, int, int, uint32_t flags)
{
    cGameData* t = (cGameData*)GetBestOpportunityTarget(self, 0, 0, 0, 0);
    if (!t)
        return 0.0f;
    cSpatialObject* sp = t->GetSpatial();
    const Vector3& tp = sp->GetPosition();
    float dist = (self->GetPosition() - tp).Length();
    if (dist < self->mGameData.GetRange())
        return 1.0f;
    if ((self->mFlags2a4 & 6) != 0)
        return 0.0f;
    float extra = (flags & 0x100) ? 60.0f : 0.0f;
    if (dist > self->mGameData.GetRange() + extra)
        return 1.0f;
    return 0.0f;
}

// @ 0x00dc6e30
bool Node6e30(cVehicle* self, int, int, int, int)
{
    cGameData* t = (cGameData*)GetBestOpportunityTarget(self, 0, 0, 0, 0);
    if (t) {
        cSpatialObject* sp = t->GetSpatial();
        void* old = self->mB7c;
        if (sp != old) {
            if (sp)
                sp->Vbc();
            self->mB7c = sp;
            if (old)
                ((cSpatialObject*)old)->Vc0();
        }
        self->mGameData.SetAttackTarget(t);
        return true;
    }
    FUN_00cabe70(self);
    return false;
}

// @ 0x00dc7080
bool Node7080(cVehicle* self, int, int, int, int, NodeState7080* st)
{
    if (st)
        st->mpObj = 0;
    st->mf10 = 0.0f;
    cSpatialObject* sp = self->GetTarget();
    cRefObj* p = sp ? (cRefObj*)sp->IsType(0x13f94d4) : 0;
    cRefObj* old = st->mpObj;
    if (p != old) {
        if (p)
            p->AddRef();
        st->mpObj = p;
        if (old)
            old->Release();
    }
    if (!st->mpObj)
        return false;
    st->mPos = g_169fa68;
    if (SP_GetCurrentGameMode() == &g_1654c10)
        FUN_00dc4610(self);
    return true;
}

// @ 0x00dc7130
void Node7130(int, int, int, int, int, cRefObj** pp)
{
    if (pp && *pp)
        (*pp)->Release();
}

// @ 0x00dc7150
bool Node7150(cVehicle* self, int, NodeState7150* st)
{
    st->mf0 = 0.0f;
    st->mb4 = false;
    self->mLoco.Vc4(0, 0.0f);
    {
        struct BigTemp {
            uint32_t m0;
            uint32_t m4;
            uint32_t m8;
            uint32_t mc;
            uint32_t m10;
            float    m14;
            float    m18;
            float    m1c;
            float    m20;
            float    m24;
            float    m28;
            float    m2c;
            uint32_t m30;
            uint32_t m34;
            uint32_t m38;
            uint32_t m3c;
            uint32_t m40;
            uint32_t m44;
            uint32_t m48;
            uint32_t m4c;
            uint32_t m50;
            uint32_t m54;
            uint8_t  m5c;
            uint8_t  m5d;
            uint8_t  m5e;
            uint8_t  m5f;
            float    m60;
            float    m64;
            float    m68;
            uint32_t m6c;
            float    m70;
            float    m74;
            float    m78;
            float    m7c;
            uint32_t m80;
        } temp;
        temp.m0 = 0;
        temp.m4 = 0;
        temp.m8 = 0;
        temp.mc = 0;
        temp.m10 = 0;
        temp.m14 = 0.0f;
        temp.m18 = 0.0f;
        temp.m1c = 0.0f;
        temp.m20 = g_169fa68.x;
        temp.m24 = g_169fa68.y;
        temp.m28 = g_169fa68.z;
        temp.m2c = *(float*)0x1485720;
        temp.m30 = 0;
        temp.m34 = 0;
        temp.m38 = 0;
        temp.m3c = 0;
        temp.m40 = 0;
        temp.m44 = 0;
        temp.m48 = 0;
        temp.m4c = 0;
        temp.m50 = 0;
        temp.m54 = 0;
        temp.m5c = 0;
        temp.m5d = 0;
        temp.m5e = 0;
        temp.m5f = 0;
        temp.m60 = 0.0f;
        temp.m64 = 0.0f;
        temp.m68 = 0.0f;
        temp.m6c = 0;
        temp.m70 = *(float*)0x13ec4b4;
        temp.m74 = 0.0f;
        temp.m78 = *(float*)0x147c3a0;
        temp.m7c = 0.0f;
        temp.m80 = 0;
        self->mLoco.Vdc(&temp);
        uint32_t* p0 = (uint32_t*)temp.m0;
        if (p0 && *(int*)((char*)p0 - 4) != 0)
            operator delete(p0);
    }
    void* mode = SP_GetCurrentGameMode();
    if (mode == &g_1654c10) {
        const Vector3& p = self->mLoco.GetPosition();
        void* sys = EA_Audio_GetSystemAT();
        void* h = sys ? VCall1(sys, 0x20) : 0;
        Start3dSoundByName(*(void**)(&((void**)0x147c438)[self->mState]), h, p.x, p.y, p.z);
    } else {
        if (((cSpatialObject*)&self->mLoco)->Vf58()) {
            void* sys = EA_Audio_GetSystemAT();
            void* h = sys ? VCall1(sys, 0x20) : 0;
            KillSetiEffects((void*)self->mState, ((void**)0x147c42c)[self->mState], h);
        }
    }
    if (self->mD04)
        self->FUN_00ca03a0((void*)0x2481db4);
    return true;
}

// @ 0x00dc7300
void Node7300(cVehicle* self, int, int, int, int, NodeState7300* st)
{
    if (st->mState == 4)
        self->FUN_00ca80e0(0xe);
    if (st->mState == 6)
        self->FUN_00ca80e0(0x11);
    if (st->mpCommunity)
        st->mpCommunity->FUN_00bff290(self);
    self->FUN_00c9ec40(1);
    cRefBase* c = (cRefBase*)st->mpCommunity;
    if (c)
        c->Release();
}

// @ 0x00dc7350
bool Node7350(int, int, int, int, int, void** pp)
{
    if (pp)
        *pp = 0;
    return true;
}

// @ 0x00dc7370
void Node7370(int, int, int, int, int, cRefBase** pp)
{
    if (pp && *pp)
        (*pp)->Release();
}

// @ 0x00dc7390
bool Node7390(cVehicle* self)
{
    int r = PlayIdleAnim((void*)(self->mAf0 + 8), 0x2000, 0);
    if (r == 0 || !(1.52587890625e-05f <= *(float*)(r + 8))) {
        self->mGameData.SetAttackTarget(0);
        return false;
    }
    void* c = 0;
    cSpatialObject* tgt = self->GetTarget();
    if (tgt)
        c = tgt->IsType(0x13f94d4);
    if (!c || FUN_008e7f80(c) == 2) {
        uint32_t owner = self->mGameData.GetOwnerID();
        void* list = 0;
        FUN_00c420d0(&list);
        void** p = *(void***)list;
        void** end = ((void***)list)[1];
        void* chosen = 0;
        for (; p != end; ++p) {
            void* o = *p;
            cSpatialObject* isDone = o ? (cSpatialObject*)((cGameData*)o)->GetSpatial() : 0;
            bool done = 0;
            if (isDone)
                done = (*(bool(__thiscall**)(void*))VFn(isDone, 0x2c))(isDone);
            if (done || !o)
                continue;
            cSpatialObject* c2 = (cSpatialObject*)((cInteractable*)o)->CastType(0x13f94d4);
            if (!c2)
                continue;
            cGameData* gd = ((cGameData*)c2)->GetSpatial() ? (cGameData*)c2 : 0;
            (void)gd;
            if ((*(uint32_t(__thiscall**)(void*))VFn(c2, 0x10))(c2) != owner)
                continue;
            if (!chosen || ((cTicker*)&g_1601760)->RandomDoubleUniform() < 0.5)
                chosen = c2;
        }
        if (chosen) {
            cSpatialObject* sp = ((cGameData*)chosen)->GetSpatial();
            void* old = self->mB7c;
            if (sp != old) {
                if (sp)
                    ((cRefObj*)sp)->Vbc();
                self->mB7c = sp;
                if (old)
                    ((cRefObj*)old)->Vc0();
            }
        }
    }
    return true;
}

// @ 0x00dc7510
void Node7510(cVehicle* self, int, int, int, int, cRefObj** pp)
{
    if (pp && *pp)
        (*pp)->Vc0();
    self->mLoco.Vec();
}

// @ 0x00dc7540
void __fastcall Node7540(RemoveList* self)
{
    if (self->mpBegin != self->mpEnd) {
        do {
            void* n = self->mpEnd[-1];
            NounManager()->RemoveNoun(n);
            self->mpEnd = self->mpEnd - 1;
            cRefBase* p = (cRefBase*)*self->mpEnd;
            if (p)
                p->Release();
        } while (self->mpBegin != self->mpEnd);
    }
}

// @ 0x00dc7590
void __cdecl PopToNearestValidSpot(SpotHolder* self, cActionCircle* circle, bool flag)
{
    if (flag)
        circle->FUN_00afafd0();
    if (self->mpBegin == self->mpEnd)
        return;

    cSpatialObject* loco = (cSpatialObject*)self->m60;
    const Vector3& p = loco->GetPosition();
    float px = p.x, py = p.y, pz = p.z;
    void* mover = *self->mpBegin;
    cMoverLike* veh = (cMoverLike*)(mover ? ((cSpatialObject*)mover)->IsType(0x137e8e0) : 0);

    int n = (int)((char*)circle->mpEnd - (char*)circle->mpBegin) / 0x18;
    if (n > 0) {
        char* slot = (char*)circle->mpBegin;
        do {
            Vector3 sp;
            sp.x = *(float*)(slot + 0xc);
            sp.y = *(float*)(slot + 0x10);
            sp.z = *(float*)(slot + 0x14);
            if (!((cVehicle*)veh)->CanOccupyTerrain(&sp)) {
                FUN_00afa070((cActionCircleSlot*)slot, 1);
            } else {
                float d = (px - sp.x) * (px - sp.x) + (py - sp.y) * (py - sp.y) + (pz - sp.z) * (pz - sp.z);
                d = (float)sqrt(d);
                if (veh->m80 < d || d < veh->m7c)
                    FUN_00afa070((cActionCircleSlot*)slot, 2);
            }
            slot += 0x18;
        } while (--n);
    }
}

// @ 0x00dc76e0
void Node76e0(RefHolder76e0* self)
{
    cRefObj* p = *(cRefObj**)self->mpIndirect;
    cRefObj* old = self->mp58;
    if (p != old) {
        if (p)
            p->Vbc();
        self->mp58 = p;
        if (old)
            old->Vc0();
    }
}

// @ 0x00dc7780
extern "C" void* __cdecl SP_FindClosestVehicleWrap(void* a, void* b)
{
    ClosestVehicleFlags flags;
    flags.value = false;
    return FUN_00dc6680(a, b, flags);
}

// @ 0x00dc77a0
void Node77a0(cVehicle* self, int, int, int, int, BufHolder* h)
{
    if (h) {
        void* p = h->mp8;
        if (p && *(int*)((char*)p - 4) != 0)
            operator delete(p);
    }
    self->mLoco.Vec();
}

// @ 0x00dc77d0
namespace SP {
namespace VehicleTree {
bool Idle_Activate(void * pTree, double a2, unsigned int a3, unsigned int a4, nSPBehaviorTree::behavior_memory_block * a5, nSPBehaviorTree::behavior_memory_block * a6)
{
  cVehicleTree_s00dc_77d0* pThis = (cVehicleTree_s00dc_77d0*)pTree;
  int32_t id = pThis->GetState()->m4c4;
  if (id == -1)
    return 0;

  cStarRecordVector vec;
  vec.mpBegin = 0;
  vec.mpEnd = 0;
  vec.mpCapacity = 0;
  g_16c7aa4->mp74->Collect(id, &vec);
  if (vec.mpBegin == vec.mpEnd) {
    vec.Destroy();
    return 0;
  }

  float* pRef = pThis->mSub34.v2c();
  float fRefX = pRef[0];
  float fRefY = pRef[1];
  float fRefZ = pRef[2];
  int32_t nCount = (int32_t)(vec.mpEnd - vec.mpBegin);
  cStarEntry* pBest = 0;
  float fBest = 3.402823466e+38F;
  for (int32_t i = 0; i < nCount; ++i) {
    cStarEntry* pEntry = vec.mpBegin[i];
    if (pEntry != 0) {
      cStarEntry* pObj = (cStarEntry*)pEntry->v0c(0x1186577);
      if (pObj != 0) {
        float* pPos = pObj->v2c();
        float fDist = (pPos[1] - fRefY) * (pPos[1] - fRefY)
                    + (pPos[2] - fRefZ) * (pPos[2] - fRefZ)
                    + (pPos[0] - fRefX) * (pPos[0] - fRefX);
        if (fDist < fBest) {
          fBest = fDist;
          pBest = pObj;
        }
      }
    }
  }
  for (cStarEntry** pp = vec.mpBegin; pp < vec.mpEnd; ++pp) {
    if (*pp != 0)
      (*pp)->v04();
  }
  if (vec.mpBegin != 0 && ((int32_t*)vec.mpBegin)[-1] != 0)
    FUN_00f47380(vec.mpBegin);
  return pBest;
}
}
}  // namespace SP::VehicleTree

// @ 0x00dc7cc0
void cVehicleTicker_s00dc_77d0::Destroy()
{
  cSpatialVector* pVec38 = &m38;
  mpVt00 = (void*)0x0147c4d8;
  mpVt08 = (void*)0x0147c4b4;
  pVec38->Destroy();
  if (mVoxSoundIds.mpBegin != 0 && ((int32_t*)mVoxSoundIds.mpBegin)[-1] != 0)
    FUN_00f47380(mVoxSoundIds.mpBegin);
  mGroupOrders.Destroy();
  mpVt00 = (void*)0x0147c468;
  mpVt08 = (void*)0x0147c444;
  FUN_00b5b690(this);
  if (g_1699ab8 == this)
    g_1699ab8 = 0;
  mpVt00 = (void*)0x013ec458;
  mpVt08 = (void*)0x013eb938;
}

// @ 0x00dc7d70
cVehicleTicker_s00dc_77d0::cVehicleTicker_s00dc_77d0()
{
  mpVt00 = (void*)0x0147c468;
  mpVt08 = (void*)0x0147c444;
  g_1699ab8 = this;
  FUN_00b5b6f0(this);
  mpVt00 = (void*)0x0147c4d8;
  mpVt08 = (void*)0x0147c4b4;
  // Keep the vector initialization stores in their observed order.
  *(void* volatile*)&mGroupOrders.mpBegin = 0;
  *(void* volatile*)&mGroupOrders.mpEnd = 0;
  *(void* volatile*)&mGroupOrders.mpCapacity = 0;
  *(void* volatile*)&mVoxSoundIds.mpBegin = 0;
  *(void* volatile*)&mVoxSoundIds.mpEnd = 0;
  *(void* volatile*)&mVoxSoundIds.mpCapacity = 0;
  *(void* volatile*)&m38.mpBegin = 0;
  *(void* volatile*)&m38.mpEnd = 0;
  *(void* volatile*)&m38.mpCapacity = 0;
}

// @ 0x00dc7dd0
void cConvertCityOrder5::FUN_00dc7dd0(cSrc5* src)
{
  mSub64.SetFrom(src);
  cMgr5* mgr = (cMgr5*)FUN_00b3d290();
  mGen90 = mgr->Get();
}

// @ 0x00dc7e00
void cConvertCityOrder5::Init(cSrc5* src)
{
  mSub64.SetFrom(src);
  cMgr5* mgr = (cMgr5*)FUN_00b3d290();
  mGen90 = mgr->Get();

  void* obj = src->mpObj;
  void* nw;
  if (obj) {
    nw = ((void* (__thiscall*)(void*, uint32_t))((*(void***)obj)[3]))(obj, 0x3d5c477);
  } else {
    nw = 0;
  }
  void* old = mEffect94;
  if (nw != old) {
    if (nw) ((void (__thiscall*)(void*))((*(void***)nw)[0]))(nw);
    mEffect94 = nw;
    if (old) ((void (__thiscall*)(void*))((*(void***)old)[1]))(old);
  }
  m98 = src->mVal;
  ((cEffect5*)mEffect94)->Apply(m78);
  if (mAnim9c) {
    cAnim5* a = (cAnim5*)mAnim9c;
    mAnim9c = 0;
    a->Release();
  }
  mbFlagAC = 0;
}

// @ 0x00dc8ba0
void CultureHash::Swap(CultureHash& other)
{
    CultureHashTail t = mTail;
    mTail = other.mTail;
    other.mTail = t;
    _ReadWriteBarrier();

    CultureHashNode** bp = mBuckets;
    mBuckets = other.mBuckets;
    other.mBuckets = bp;
    _ReadWriteBarrier();

    uint32_t bc = mBucketCount;
    mBucketCount = other.mBucketCount;
    other.mBucketCount = bc;
    _ReadWriteBarrier();

    uint32_t ec = mElementCount;
    mElementCount = other.mElementCount;
    other.mElementCount = ec;
}

// @ 0x00dc8c00
void DecalRemover::Remove(Removable* p)
{
    RemoveLocals locals;
    locals.key = p;
    if (p)
        p->AddRef();
    TaggedPtr key;
    key.mBytes.mTag = 0;
    mMap.Find(locals.it, &locals.key, key.mValue);
    if (p)
        p->Release();
}

// @ 0x00dc8c50
void DecalManager::Remove(RemoveArg* arg)
{
    arg->Method(0);
    if (!Skip()) {
        Removable** it = mVec50Begin;
        while (it != mVec50End && *it != arg)
            ++it;
        if (it != mVec50End) {
            if (it + 1 < mVec50End)
                CopyImpl_do_copy(it + 1, mVec50End, it);
            --mVec50End;
            Removable* last = *mVec50End;
            if (last)
                last->Release();
        }

        int count = (int)(mDecalEnd - mDecalBegin);
        if (count > 0) {
            uint32_t off = 0;
            int n = count;
            do {
                DecalEntry* e = (DecalEntry*)((uint8_t*)mDecalBegin + off);
                void* target = arg ? (void*)&arg->mField34 : 0;
                e->RemoveDecal(target);
                off += 0x178;
                --n;
            } while (n != 0);
        }
    }
}

// @ 0x00dc95b0
bool StandardVehicleMoveTick(CVehicle* pVeh)
{
    if (pVeh->mFlags_2a4 & 2)
    {
        AttemptRepark(pVeh);
        return true;
    }
    if (pVeh->mFlags_2a4 & 4)
        pVeh->OnMoveTick();
    return true;
}

// @ 0x00dc9680
void FUN_00dc9680(IRefCounted* pObject)
{
    AutoRefCount ref(pObject);
    gLocomotiveList.push_back(ref);
}

// @ 0x00dca100
namespace SP { namespace VehicleTree {
bool EstablishTradeRouteOrder_Tick(cVehicle_s00dc_a100* self, int, int, int, int, TradeMem* mem, int, float dt)
{
    if (self->mPathFlags & 8)
        return Fail(self, "(31) TR: path failure");
    {
        CityRef* ref = self->Fca71d0();
        cCity_s00dc_a100* c = ref->mpCity;
        if (c) {
            cCity_s00dc_a100* city = c->Cast(0xee9b2232);
            int selfCiv;
            if (city && !city->IsDestroyed() && ((selfCiv = self->Vf4c()), selfCiv != city->Vf4c())) {
                if (mem->mState == 0) {
                    if (self->mLoco.IsNearGoal()) {
                        mem->mTime = 0.0f;
                        mem->mState = 1;
                        return true;
                    }
                    if (!mem->mFlag8 && self->mLoco.Fc42210(150.0f)) {
                        mem->mFlag8 = true;
                        city->Fbdb3b0(self, 1);
                    }
                    return StandardVehicleMoveTick(self);
                }
                if (mem->mState != 1) {
                    return Fail(self, "(36) TR: unknown exit");
                }

                bool bSame = city->Vf4c() == self->Vf4c();
                bool bA = city->mSpatial.IsPlayerControlled() && !bSame;
                bool bB = !city->mSpatial.IsPlayerControlled() && !bSame;
                bool bC = false;
                int iState = -1;
                cGameData_s00dc_a100* gd = &self->mGameData;
                cCivNoun* civNoun = NounManager_s00dc_a100()->Fb25f40(gd->GetNounID());

                if (0.0f < mem->mTime) {
                    if (bA && civNoun->Fbef7e0()) {
                        iState = civNoun->mState434;
                        if (iState == 1 || iState == 2) {
                            civNoun->mState434 = 0xffffffff;
                            civNoun->mField438 = 0;
                            bC = (iState == 1);
                        }
                    }
                } else {
                    PlayEffectAt(0x6b36f685, self->mLoco.GetPosition());
                    if (city->Fbdb200(gd->GetNounID()) == 1) {
                        return AlreadyExists(self, city, "(34) TR: already exists");
                    }
                    if (bA && !civNoun->Fbef7e0())
                        civNoun->Fbf0330(city);
                }

                mem->mTime = mem->mTime + dt;
                if (((bB || bSame) && mem->mTime > 3.0f) || iState == 1 || iState == 2) {
                    mem->mTime = 0.0f;
                    self->Fca80e0(0x13);
                    civNoun->mTimer128.Restart();
                    if (city->Fbdb200(gd->GetNounID()) == 1) {
                        return AlreadyExists(self, city, "(35) TR: already exists");
                    }
                    cSpatialObject_s00dc_a100* loco = &self->mLoco;
                    if (loco->IsPlayerControlled())
                        Fb26930()->Fae37c0(2, city->mSpatial.GetPosition());

                    cCivNoun* civNoun2 = NounManager_s00dc_a100()->Fb25f40(gd->GetNounID());
                    RelationshipManager()->Fd00d60(city->GetCivilization(), civNoun2, 1);
                    float score = g_ScoreTable.Fceee30(city, civNoun2);

                    if ((bA && bC) || (bB && (double)score > sMathRandom.RandomDoubleUniform()) || bSame) {
                        PlayEffectAt(0xd5475761, loco->GetPosition());
                        city->Fbe1820(gd->GetNounID());
                        AudioSystem()->PlaySoundAt(0x4288913, loco->GetPosition(), loco->GetVelocity());
                        self->Fcac000(city, 5, 0);
                        if (!bSame) {
                            if (loco->IsPlayerControlled()) {
                                cCivilization_s00dc_a100* civ = city->GetCivilization();
                                Vector4 v;
                                v.x = civ->mPos.x; v.y = civ->mPos.y; v.z = civ->mPos.z; v.w = 1.0f;
                                CivModeStrategy()->Fcf9040(city, 0xb327dc63, 0xaa9a8ed7, loco->GetPosition(), &v, 0, 0);
                                CommManager()->ShowCommEvent(city, city, GetActivePlanet()->mpStarRecord->GetCommContext(),
                                                             0xdbf385bf, 0x9cecad2c, 0);
                                return true;
                            }
                            if (city->mSpatial.IsPlayerControlled()) {
                                cCivNounPos* n = (cCivNounPos*)NounManager_s00dc_a100()->Fb25f40(gd->GetNounID());
                                Vector4 v;
                                v.x = n->mPos.x; v.y = n->mPos.y; v.z = n->mPos.z; v.w = 1.0f;
                                CivModeStrategy()->Fcf9040(city, 0xe1f6430a, 0xaa9a8ed7, loco->GetPosition(), &v, 0, 0);
                            }
                        }
                        return true;
                    }

                    PlayEffectAt(0x5bc0bd48, loco->GetPosition());
                    if (loco->IsPlayerControlled()) {
                        cSPTimer_s00dc_a100* timer = &city->mCommTimer;
                        uint64_t elapsed = timer->GetElapsedTime();
                        if (elapsed > 40000) {
                            cCivilization_s00dc_a100* civ = city->GetCivilization();
                            Vector4 v;
                            v.x = civ->mPos.x; v.y = civ->mPos.y; v.z = civ->mPos.z; v.w = 1.0f;
                            CivModeStrategy()->Fcf9040(city, 0x8b24acc6, 0xaa9a8ed7, loco->GetPosition(), &v, 0, 0);
                            CommManager()->ShowCommEvent(city, city, GetActivePlanet()->mpStarRecord->GetCommContext(),
                                                         0xdbf385bf, 0x26546f31, 0);
                            timer->Restart();
                        }
                    }
                    self->Fcaa900();
                    if (bA)
                        civNoun->Fbef8c0();
                    return true;
                }
                return true;

            }
        }
    }
    return Fail(self, "(32) TR: bad city");
}
}}  // namespace SP::VehicleTree

// @ 0x00dca7b0
namespace SP { namespace VehicleTree {
bool OfferToBuyCityOrder_Tick(cVehicle_s00dc_a100* self, int, int, int, int, TradeMem* mem, int, float)
{
    bool bGameMode = (GetCurrentGameMode() == (void*)0x1654c04);

    if (self->mPathFlags & 8)
        return Fail(self, "(36) BC: path failure");

    cGameData_s00dc_a100* gd = &self->mGameData;
    cCivNoun* civNoun = NounManager_s00dc_a100()->Fb25f40(gd->GetNounID());
    (void)gd->GetNounID();

    CityRef* ref = self->Fca71d0();
    cCity_s00dc_a100* city = ref->mpCity;
    if (city) {
        cCommunity_s00dc_a100* comm = (cCommunity_s00dc_a100*)city->Cast(0x403df5f);
        if (comm) {
            int selfVf4c = self->Vf4c();
            if (comm->Vf4c() != selfVf4c && comm->Vf4c() != -1) {
                (void)comm->mSpatial.IsPlayerControlled();
                if (bGameMode)
                    (void)self->mLoco.IsPlayerControlled();

                switch (mem->mState) {
                case 0:
                    if (self->mLoco.IsNearGoal()) {
                        mem->mTime = 0.0f;
                        mem->mState = 1;
                        return true;
                    }
                    if (!StandardVehicleMoveTick(self))
                        return Fail(self, "(37) BC: move failure");
                    return true;

                case 1:
                    if (mem->mFieldC == 0) {
                        float cost = civNoun->Fbf0640();
                        if (cost > civNoun->GetMoney())
                            return Fail(self, "(39a) BC: not enough money");
                        comm->GetNoun()->FcivicRadiusAccum(cost, 0);
                        civNoun->SpendMoney(cost);

                        cStarRecord_s00dc_a100* star = GetActivePlanet()->mpStarRecord;
                        int ctx = star->GetCommContext(0xdbf385bf, 0x4ce5b975, 0);
                        CommManager()->ShowCommEvent(comm->GetNoun(), 0, ctx);

                        cPathArcBuilder* builder = NounManager_s00dc_a100()->Fbfe7a0();
                        builder->SetCiv(civNoun->Vf4c());
                        builder->mSpatial.SetPosition(self->mLoco.GetPosition());
                        Vector3_s00dc_a100* p = comm->mSpatial.GetPoint(20.0f, 1);
                        builder->Start(civNoun, comm, p, 20.0f, 1);
                        return Fail(self, "(40a) BC: normal completion");
                    } else {
                        float cost = civNoun->Fbf06d0();
                        if (cost > civNoun->GetMoney())
                            return Fail(self, "(39b) BC: not enough money");
                        civNoun->SpendMoney(cost);
                        (void)RelationshipManager()->RecordEvent(comm->Vf4c(), civNoun->Vf4c(), 0x526e4fb, 1.0f);

                        cPathArcBuilder* builder = NounManager_s00dc_a100()->Fbfe7a0();
                        builder->SetCiv(civNoun->Vf4c());
                        builder->mSpatial.SetPosition(self->mLoco.GetPosition());
                        Vector3_s00dc_a100* p = comm->mSpatial.GetPoint(20.0f, 1);
                        builder->Start(civNoun, comm, p, 20.0f, 1);
                        return Fail(self, "(40b) BC: normal completion");
                    }

                default:
                    return Fail(self, "(41) BC: unknown exit");
                }
            }
        }
    }
    return Fail(self, "(38) BC: bad mineral");
}
}}  // namespace SP::VehicleTree

// @ 0x00dcaad0
namespace SP { namespace VehicleTree {
bool MoveToPointOrder_Tick(cVehicle_s00dc_a100* self)
{
    if (self->mPathFlags32 & 2)
        AttemptRepark(self);
    else if (self->mPathFlags32 & 4)
        self->Fcacbe0();

    if (self->mLoco.IsNearGoal()) {
        self->Fca7250("(43) MTP: normal completion");
        self->Fcaa900();
        return false;
    }
    return true;
}
}}  // namespace SP::VehicleTree

// @ 0x00dcb8e0
uint32_t FUN_00dcb8e0(BehaviorObj* self, CombatCtx* ctx, float dt)
{
  int myId = CallV(&self->mLoco, 0x4c);
  if (myId != -1) {
    void* target = ctx->mpTarget;
    void* targetObj = (void*)CallV(target, 0x0c);
    int targetId = CallV(targetObj, 0x4c);
    int selfId = CallV(&self->mLoco, 0x4c);
    if (targetId == selfId &&
        (((uint32_t*)self->mpObjAf0)[0x1c8 / 4] & 0x2000) == 0)
      return 0;
  }

  if (GetDamageState(ctx->mpTarget) == 2)
    return 0;

  void* posObj = (void*)CallV(ctx->mpTarget, 0x08);
  float* targetPos = CallVPos(posObj, 0x2c);
  float tx = targetPos[0];
  float ty = targetPos[1];
  float tz = targetPos[2];
  float* selfPos = CallVPos(&self->mLoco, 0x2c);
  float dx = tx - selfPos[0];
  float dy = ty - selfPos[1];
  float dz = tz - selfPos[2];
  float dist = sqrtf(dx * dx + dy * dy + dz * dz);
  float limit = 0.0f;

  void* mode = SP_GetCurrentGameMode();
  if (mode == &DAT_01654c10) {
    limit = FUN_00f264b0(self);
    if (dist <= limit) {
      ctx->mTimer = 0.0f;
    } else {
      ctx->mTimer = ctx->mTimer + dt;
      if (ctx->mTimer > 5.0f) {
        CallV(self->mpObj508, 0x50);
      }
    }
  }

  float reach = FUN_00bfc400();
  if (dist < reach) {
    ctx->mPosX = tx;
    ctx->mPosY = ty;
    ctx->mPosZ = tz;
    float a = dist - 1.0f;
    float b = dist * 0.75f;
    void* obj = (void*)CallV(ctx->mpTarget, 0x08);
    FUN_00dc4ed0(&a, &b, self, obj);
    FUN_00ca97a0(&tx, a, b);
    FUN_00c9fb40(tx, ty, tz, a, b);
  }
  return 1;
}

// @ 0x00dcbe00
uint32_t FUN_00dcbe00(BehaviorObj* self, TimerCtx* ctx, float dt)
{
  ctx->mTimer = ctx->mTimer + dt;

  float threshold;
  if (SP_GetCurrentGameMode() == &DAT_01654c10)
    threshold = 0.0f;
  else
    threshold = 3.0f;

  if (threshold < ctx->mTimer && ctx->mFlag == 0) {
    ctx->mFlag = 1;
    FUN_00dc9680(self);
  }
  return 1;
}

// @ 0x00dcbeb0
uint32_t FUN_00dcbeb0(BehaviorObj* self)
{
  if (self->mLoco.IsNearGoal()) {
    ((Stimuli*)((uint8_t*)self->mpObjAf0 + 8))->ClearAll(0x1000, 0);
    return 0;
  }
  if ((self->mFlags2a4 & 2) != 0) {
    AttemptRepark(self);
    return 1;
  }
  if ((self->mFlags2a4 & 4) != 0)
    FUN_00cacbe0(self);
  return 1;
}

// @ 0x00dcc0a0
uint8_t FUN_00dcc0a0(BehaviorObj* self, StateCtx* ctx, float dt)
{
  float px = 0.0f, py = 0.0f, pz = 0.0f;

  if ((self->mFlags2a4 & 8) != 0) {
    ctx->mFlag21 = 1;
    float* pos = CallVPos(&self->mLoco, 0x2c);
    px = pos[0]; py = pos[1]; pz = pos[2];
    float heading = (float)CallV(&self->mLoco, 0x74);
    CallVArgP(&self->mLoco, 0xe4, *(int*)&heading);
    FUN_00c9fb40(px, py, pz, 0.0f, (float)CallV(&self->mLoco, 0x74));
    return 1;
  }

  if (ctx->mFlag20 == 0) {
    if (!self->mLoco.IsNearGoal() && dt <= 120.0f) {
      ctx->mFlag20 = 1;
      return StandardVehicleMoveTick(self);
    }
    ctx->mFlag20 = 1;
    if (ctx->mFlag21 != 0) {
      ctx->mFlag21 = 0;
      return 1;
    }
  }
  return 1;
}

// @ 0x00dcc2c0
void BehaviorObj::RemoveNouns()
{
  mVec38.erase(mVec38.mpBegin, mVec38.mpEnd);

  int count = (int)(mpNounsEnd - mpNouns);
  for (int i = 0; i < count; ++i) {
    uint32_t noun = mpNouns[i];
    NounManager(noun)->RemoveNoun(noun);
  }
}

// @ 0x00dcc300
void Vector24::PushUnique(uint32_t value)
{
  uint32_t** v = &mpBegin;
  uint32_t* end = v[1];
  uint32_t* p = v[0];

  if (p != end) {
    do {
      if (*p == value)
        break;
      ++p;
    } while (p != end);
  }
  if (p != end)
    return;

  if (end < v[2]) {
    uint32_t* slot = end;
    v[1] = slot + 1;
    if (slot != 0) {
      *slot = value;
      return;
    }
  } else {
    VectorInsertU32(end, &value);
  }
}

// @ 0x00dcc350
void BehaviorObj::AddFeedback(void* event)
{
  if (event != 0)
    CallV(event, 0x00);

  uint32_t* p = mpVec50;
  while (p != mpVec50End) {
    if ((void*)*p == event)
      break;
    ++p;
  }
  if (p != mpVec50End)
    return;

  if (event != 0)
    CallV(event, 0x00);

  if (mpVec50End < mpVec50Cap) {
    uint32_t* slot = mpVec50End;
    mpVec50End = slot + 1;
    if (slot != 0)
      *slot = (uint32_t)event;
  } else {
    VectorInsertU32(mpVec50End, (uint32_t*)&event);
  }

  if (event != 0)
    CallV(event, 0x04);
}

// @ 0x00dcc440
__declspec(noinline) void* FUN_00dcc440(BehaviorObj* self, int specialty, void* exclude)
{
  if (self->mpObj508 == 0)
    return 0;

  int handle = CallV(self->mpObj508, 0x10);
  NounManagerObj* nm = NounManager((uint32_t)handle);
  if (nm == 0)
    return 0;

  void* first = 0;
  (void)specialty;
  (void)exclude;
  return first;
}

// @ 0x00dcc5c0
void FUN_00dcc5c0(BehaviorObj* self)
{
  int index = self->mFieldB20;

  if (gVehicleTicker == 0)
    gVehicleTicker = new ("Simulator/SimSingleton", 0, 0, 0, 0) cVehicleTicker_s00dd_0230;

  ((Vector24*)gVehicleTicker)->PushUnique(
      (&gVehicleServiceTable708)[index]);
}

// @ 0x00dcc610
void FUN_00dcc610(BehaviorObj* self)
{
  if (!((char (__thiscall*)(void*))(*(void***)&self->mLoco)[0x58 / 4])(&self->mLoco))
    return;

  int mode = 0;
  Brain* brain = self->GetBrain();

  switch (brain->mMode10) {
  case 1: {
    void* nearby = self->GetNearby();
    if (nearby != 0) {
      void* p = CallVArgP(nearby, 0xb8, 0xd0036e08);
      if (p != 0 && Flag388(p))
        mode = 1;
    }
    break;
  }
  case 8: {
    int r = CallV(brain->mpObj0, 0x20);
    mode = (r != 0x403df5c) + 2;
    break;
  }
  }

  int index = self->mFieldB20;

  if (gVehicleTicker == 0)
    gVehicleTicker = new ("Simulator/SimSingleton", 0, 0, 0, 0) cVehicleTicker_s00dd_0230;

  ((Vector24*)gVehicleTicker)->PushUnique(
      (&gVehicleServiceTable714)[index + mode * 3]);
}

// @ 0x00dcc6e0
bool FUN_00dcc6e0(BehaviorObj* self)
{
  Brain* brain = self->GetBrain();

  void* found;
  if (brain->mpObj0 != 0)
    found = CallVArgP(brain->mpObj0, 0x0c, 0x01186577);
  else
    found = 0;

  void* old = self->mpObjB7c;
  if (found != old) {
    if (found != 0)
      CallV(found, 0xbc);
    self->mpObjB7c = found;
    if (old != 0)
      CallV(old, 0xc0);
  }

  FUN_00dcc610(self);
  return true;
}

// @ 0x00dcc750
uint32_t TradeWithCityOrder_Activate(BehaviorObj* self, int a2, int a3, int a4, int a5, TradeCtx* ctx)
{
  if (ctx != 0) {
    ctx->mField0 = 0;
    ctx->mFlag8 = 0;
  }

  if (self->mFieldB28 == 1 && self->mFieldB58 != 0.0f) {
    ctx->mField0 = 3;
    Brain* brain = self->GetBrain();
    if (brain->mpObj0 != 0) {
      void* city = CallVArgP(brain->mpObj0, 0x0c, 0xee9b2232);
      if (city != 0) {
        if (!CallVBool(city, 0x2c)) {
          FUN_00dc5050(self, city);
          FUN_00ca80e0(self, 0x14);
          return 1;
        }
      }
    }
    FUN_00ca7250(self, "(20) trade: no city");
    FUN_00caa900(self);
    return 0;
  }

  ctx->mField0 = 0;
  void* city = FUN_00dcc440(self, 2, 0);
  if (city == 0) {
    FUN_00ca7250(self, "(19) trade: no city");
    FUN_00caa900(self);
    return 0;
  }
  FUN_00dc5050(self, city);
  return 1;
}

// @ 0x00dcc830
namespace SP {
void __thiscall cVehicleTree::TradeWithCityOrder_Tick()
{
}
}  // namespace SP

// @ 0x00dcce90
extern "C" void* FUN_00bc96a0();   // 0x00bc96a0 PlayIdleAnimation
namespace SP {
struct Out_s00dcce90 {
    uint32_t mf0;      // +0x00
    float    mf4;      // +0x04
    float    mf8;      // +0x08
    uint32_t mf0c;     // +0x0c
};
bool __cdecl FUN_00dcce90(BehaviorObj* self, Out_s00dcce90* out)
{
    if (out) {
        out->mf0 = 0;
        out->mf4 = 0.0f;
        out->mf8 = 0.0f;
    }
    ::cSpatialObject* sp = (::cSpatialObject*)((char*)self + 0x34);
    Brain* brain = self->GetBrain();
    void* m = 0;
    if (brain->mpObj0)
        m = ((void* (__thiscall*)(void*, uint32_t))(*(void***)brain->mpObj0)[0x0c / 4])(
            brain->mpObj0, 0x403df5f);
    if (m) {
            int mine = ((int (__thiscall*)(BehaviorObj*))(*(void***)self)[0x4c / 4])(self);
            int theirs = ((int (__thiscall*)(void*))(*(void***)m)[0x4c / 4])(m);
            if (theirs != mine) {
                if (((int (__thiscall*)(void*))(*(void***)m)[0x4c / 4])(m) != -1) {
                    void* msub = (char*)m + 0x34;
                    const Vector3* pos = ((const Vector3* (__thiscall*)(void*, float, float))
                        (*(void***)msub)[0x2c / 4])(msub, DAT_01473c70, DAT_013eecd8);
                    sp->Ve8(pos);
                    const Vector3* pos2 = ((const Vector3* (__thiscall*)(void*, float, float))
                        (*(void***)msub)[0x2c / 4])(msub, DAT_01473c70, DAT_013eecd8);
                    ((void (__thiscall*)(BehaviorObj*, Vector3))(void*)FUN_00c9fb40)(self, *pos2);
                    void* r = ((void* (__thiscall*)(void*, int, int))FUN_00bc96a0)(
                        (char*)self->mpObjAf0 + 8, 0x800, 0);
                    out->mf0c = *((uint32_t*)r + 3);
                    out->mf0 = 0;
                    ((void (__cdecl*)(BehaviorObj*))FUN_00dcc610)(self);
                    return true;
                }
            }
    }
    ((void (__thiscall*)(BehaviorObj*, const char*))FUN_00ca7250)(self, "(35) BC: bad mineral");
    ((void (__thiscall*)(BehaviorObj*))FUN_00caa900)(self);
    return false;
}
}  // namespace SP

// @ 0x00dccfd0
namespace SP {
bool __cdecl MoveToPointOrder_Activate(BehaviorObj* self)
{
    Brain* brain = ((Brain* (__thiscall*)(BehaviorObj*))(void*)FUN_00ca71d0)(self);
    if (brain->mMode10 == 6) {
        ((void (__thiscall*)(BehaviorObj*, Vector3, float, float))FUN_00c9fb40)(self, *(Vector3*)((char*)brain + 0x04), 0.0f, *(float*)0x013f1164);
        ((::cSpatialObject*)((char*)self + 0x34))->Ve4(*(Vector3*)((char*)brain + 0x04), 1.0f);
        FUN_00dcc610(self);
        return true;
    } else {
        ((void (__thiscall*)(BehaviorObj*, const char*))FUN_00ca7250)(self, "(42) MTP: bad orders");
        ((void (__thiscall*)(BehaviorObj*))FUN_00caa900)(self);
        return false;
    }
}
}  // namespace SP

// @ 0x00dcd050
namespace SP {
struct Out_s00dcd050 {
    void* mp0;      // +0x00
    void* mp4;      // +0x04
    void* mp8;      // +0x08
    float mf0c;     // +0x0c
};
bool __cdecl FUN_00dcd050(BehaviorObj* self, int, int, int, int, Out_s00dcd050* out)
{
    if (out) {
        out->mp0 = 0;
        out->mp4 = 0;
        out->mp8 = 0;
        out->mf0c = 0.0f;
    }

    Brain* brain = self->GetBrain();
    void* t = 0;
    if (brain->mpObj0)
        t = ((void* (__thiscall*)(void*, uint32_t))VF(brain->mpObj0, 0x0c))(brain->mpObj0, 0x403df5f);
    void* old4 = out->mp4;
    if (t != old4) {
        if (t)
            ((void (__thiscall*)(void*))VF(t, 0))(t);
        out->mp4 = t;
        if (old4)
            ((void (__thiscall*)(void*))VF(old4, 4))(old4);
    }

    brain = self->GetBrain();
    void* t2;
    if (brain->mpObj0)
        t2 = ((void* (__thiscall*)(void*, uint32_t))VF(brain->mpObj0, 0x0c))(brain->mpObj0, 0xee02c7);
    else
        t2 = 0;
    void* old8 = out->mp8;
    if (t2 != old8) {
        if (t2)
            ((void (__thiscall*)(void*))VF(t2, 0))(t2);
        out->mp8 = t2;
        if (old8)
            ((void (__thiscall*)(void*))VF(old8, 4))(old8);
    }

    void* io = out->mp8;
    void* sub;
    if (io) {
        sub = (char*)io + 0x34;
    } else {
        void* q = out->mp4;
        if (q) {
            int id = ((int (__thiscall*)(void*))VF(q, 0x4c))(q);
            if (id != -1) {
                if (((int (__thiscall*)(void*))VF(self, 0x4c))(self) != id)
                    return false;
            }
        }
        void* r = out->mp4;
        sub = r ? (char*)r + 0x34 : 0;
    }

    void* oldB7c = self->mpObjB7c;
    if (sub != oldB7c) {
        if (sub)
            ((void (__thiscall*)(void*))VF(sub, 0xbc))(sub);
        self->mpObjB7c = sub;
        if (oldB7c)
            ((void (__thiscall*)(void*))VF(oldB7c, 0xc0))(oldB7c);
    }

    FUN_00dcc610(self);
    return true;
}
}  // namespace SP

// @ 0x00dcd180
extern "C" void* FUN_00b25f40();                 // NounManager query, thiscall, no args
extern "C" void  FUN_00435ed0(uint32_t, void*);
namespace SP {
bool __cdecl FUN_00dcd180(BehaviorObj* self, int, int, int, int, float* out)
{
    if (out)
        *out = 0.0f;

    void* sub = &self->mpObj508;
    void* v = ((void* (__thiscall*)(void*))VF(sub, 0x10))(sub);
    void* nm = ((void* (__stdcall*)(void*))FUN_00b3d300)(v);
    void* r = ((void* (__thiscall*)(void*))FUN_00b25f40)(nm);
    if (r) {
        void* city = ((void* (__cdecl*)(BehaviorObj*, int, void*))FUN_00dcc440)(self, -1, 0);
        if (city) {
            ((void* (__cdecl*)(BehaviorObj*, void*))FUN_00dc5050)(self, city);
            void* loco = (char*)self + 0x34;
            if (((char (__thiscall*)(void*))VF(loco, 0x58))(loco)) {
                void* obj = (void*)EA_Audio_GetSystemAT();
                FUN_00435ed0(0x67fa83cd, obj ? ((void* (__thiscall*)(void*))VF(obj, 0x20))(obj) : 0);
            }
        }
    }
    return true;
}
}  // namespace SP

// @ 0x00dcd220
namespace SP {
void __fastcall FUN_00dcd220(void* this_, int unused)
{
    (void)this_;
}
}  // namespace SP

// @ 0x00dcd430
namespace SP {
void* __thiscall cVehicleTicker::GetGroupOrder()
{
    return 0;
}
}  // namespace SP

// @ 0x00dcd530
namespace SP {
cCulturalConvertCityOrder_s00dc_c830::~cCulturalConvertCityOrder_s00dc_c830()
{
    mpVtbl0 = (cOrderVTable0*)0x0145efe8;
    mpVtbl1 = (cOrderVTable1*)0x0145efd8;
    _ReadWriteBarrier();
    if (mpFieldA4)
        mpFieldA4->Release();
    if (mpFieldA0)
        mpFieldA0->Release();
    if (mpField9c)
        mpField9c->Release();
    if (mpField94)
        mpField94->Release();
    DestroyBase();
}
}  // namespace SP

// @ 0x00dcd590
namespace SP {
void __fastcall FUN_00dcd590(void* this_, int unused)
{
    (void)this_;
}
}  // namespace SP

// @ 0x00dcdac0
namespace SP { namespace VehicleTree {
bool ConvertCityOrder_Tick(cVehicle_s00dc_d720* self, int, int, int, int, State* st)
{
    if (st->mOrder.mpObject->IsDone()) {
        self->FUN_00caa900();
        return false;
    }
    Info_s00dc_d720* info = self->FUN_00ca71d0();
    if (info->mKind == 3) {
        if (info->mpObject) {
            cCulturalTarget_s00dc_d720* tgt = (cCulturalTarget_s00dc_d720*)info->mpObject->Cast(0x3d5c477);
            if (tgt && !tgt->IsDestroyed()) {
                cCity_s00dc_d720* city = tgt->FUN_00bd84e0();
                if (city && !city->IsDestroyed()) {
                    if (city->GetCivilization()->GetPoliticalID() != st->mPoliticalID) {
                        self->FUN_00ca7250("(6.5) Convert city order complete");
                        self->FUN_00caa900();
                        return false;
                    }
                    int cntA = 0;
                    int cntB = 0;
                    VehicleList* list = NounManager_s00dc_d720()->GetVehicles();
                    int n = (int)(list->mpEnd - list->mpBegin);
                    for (int i = 0; i < n; ++i) {
                        cVehicle_s00dc_d720* v = list->mpBegin[i];
                        if (v != self) {
                            uint32_t mine = self->GetPoliticalID();
                            if (v->GetPoliticalID() == mine && v->mState == 1) {
                                Info_s00dc_d720* vi = v->FUN_00ca71d0();
                                if (vi->mKind == 3) {
                                    cCulturalTarget_s00dc_d720* vt = FUN_00bd8420(vi);
                                    if (vt && vt->FUN_00bd84e0() == city) {
                                        if (v->GetTarget() == &vt->mSpatial)
                                            ++cntA;
                                        if (FUN_00dc4ca0(v->GetTarget()) == 0)
                                            ++cntB;
                                    }
                                }
                            }
                        }
                    }
                    if (cntB > 0) {
                        cEntity* e = FUN_00dc4ca0(self->GetTarget());
                        if (e && e->mf290 <= 1 && !e->FUN_00bfc600())
                            return true;
                    }
                    if (cntA < 1 && city->FUN_00bd7e20())
                        goto phase2;

                    {
                        cBuilding_s00dc_d720* best = 0;
                        float bestDist = 3.402823466e+38F;
                        BuildingVector found;
                        city->FUN_00be5700(&found);
                        cBuilding_s00dc_d720** it = found.mpBegin;
                        cBuilding_s00dc_d720** end = found.mpEnd;
                        for (; it != end; ++it) {
                            cBuilding_s00dc_d720* o = *it;
                            if (IsValidFireTarget(self, o) && !o->FUN_00bd3550(self)) {
                                VehicleList* list2 = NounManager_s00dc_d720()->GetVehicles();
                                int n2 = (int)(list2->mpEnd - list2->mpBegin);
                                for (int j = 0; j < n2; ++j) {
                                    cVehicle_s00dc_d720* v = list2->mpBegin[j];
                                    uint32_t mine = self->GetPoliticalID();
                                    if (v->GetPoliticalID() == mine && v->mState == 1) {
                                        Info_s00dc_d720* vi = v->FUN_00ca71d0();
                                        if (vi->mKind == 3) {
                                            cCulturalTarget_s00dc_d720* vt = FUN_00bd8420(vi);
                                            if (vt && vt->FUN_00bd84e0() == city) {
                                                cSpatialObject_s00dc_d720* os = o->GetSpatial();
                                                const Vector3& vp = v->mLoco.GetPosition();
                                                const Vector3& op = os->GetPosition();
                                                float d = (op - vp).Length();
                                                if (d < o->GetRange() + 10.0f) {
                                                    cSpatialObject_s00dc_d720* os2 = o->GetSpatial();
                                                    const Vector3& mp = self->mLoco.GetPosition();
                                                    const Vector3& op2 = os2->GetPosition();
                                                    float d2 = (op2 - mp).Length();
                                                    if (d2 < bestDist) {
                                                        best = o;
                                                        bestDist = d2;
                                                    }
                                                    break;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        if (best) {
                            self->FUN_00dc4d00(best->GetSpatial());
                            self->SetAttackTarget(best);
                            return true;
                        }
                        if (self->FUN_00c9f3d0() == city) {
                            cGameData_s00dc_d720* g = FUN_00dc69a0(self, city->GetCivilization(), 1, 1, 1);
                            if (g) {
                                int cnt = 0;
                                bool ok = true;
                                if (self->mLoco.Vf58()) {
                                    VehicleList* list3 = NounManager_s00dc_d720()->GetVehicles();
                                    int n3 = (int)(list3->mpEnd - list3->mpBegin);
                                    for (int k = 0; k < n3; ++k) {
                                        cVehicle_s00dc_d720* v = list3->mpBegin[k];
                                        if (v != self) {
                                            uint32_t mine = self->GetPoliticalID();
                                            if (v->GetPoliticalID() == mine && v->mState == 1) {
                                                int kind = v->FUN_00ca71d0()->mKind;
                                                if (kind == 1 || kind == 3) {
                                                    cSpatialObject_s00dc_d720* gs = g->GetSpatial();
                                                    if (v->GetTarget() == gs)
                                                        ++cnt;
                                                }
                                            }
                                        }
                                    }
                                    if (cnt >= 2)
                                        ok = false;
                                }
                                if (ok) {
                                    self->FUN_00dc4d00(g->GetSpatial());
                                    self->SetAttackTarget(g);
                                    return true;
                                }
                            }
                        }
                    }
                phase2:
                    if (self->FUN_00c9f3d0() == city && !city->FUN_00bd7e20()) {
                        EntityVector_s00dc_d720* members = city->GetMembers();
                        for (unsigned i = 0; i < (unsigned)(members->mpEnd - members->mpBegin); ++i) {
                            cEntity* m = members->mpBegin[i];
                            if (IsValidFireTarget(self, m) && !m->FUN_00bd3280(self) && m->GetTypeID() == 0x1a56aba
                                && ((m->mf298 - m->mf29c) > 0 || m->mf290 > 0)) {
                                if (NounManager_s00dc_d720()->GetEmpire(self->GetPoliticalID())->FUN_00bf0d10(m) == 0) {
                                    self->FUN_00dc4d00(m->GetSpatial());
                                    self->SetAttackTarget(m);
                                    return true;
                                }
                            }
                        }
                    }
                    cSpatialObject_s00dc_d720* ts = self->GetTarget();
                    cEntity* te = ts ? (cEntity*)ts->IsType(0x1a55e4d) : 0;
                    if (!te || te->mf290 > 1 || te->FUN_00bfc600()) {
                        if (self->mLoco.FUN_00c42210(90.0f) && tgt->mf1d8 == 2 && tgt->mf1dc != self->GetOwnerID()) {
                            cCulturalTarget_s00dc_d720* nt = city->FUN_00bd8d70(self);
                            if (!nt) {
                                self->FUN_00ca7250("(7) No culture target when rescanning");
                                self->FUN_00caa900();
                                return false;
                            }
                            self->FUN_00c9fa30(nt);
                            cCulturalConvertCityOrder_s00dc_d720* ord = FUN_00dc4c80(FUN_00c9efc0()->GetGroupOrder(self->FUN_00ca71d0()));
                            if (ord && !ord->IsDone()) {
                                st->mPoliticalID = nt->mGameData.GetOwnerID();
                                st->mOrder.mpObject->FUN_00dc8c50(self);
                                ord->FUN_00dc8c00(self);
                                ord->FUN_00dcc350(self);
                                st->mOrder = ord;
                                self->FUN_00dc4d00(&nt->mSpatial);
                                self->SetAttackTarget(&nt->mGameData);
                                return true;
                            }
                        }
                        self->FUN_00dc4d00(&tgt->mSpatial);
                        self->SetAttackTarget(&tgt->mGameData);
                    }
                    return true;
                }
                self->FUN_00ca7250("(8) bad city");
            }
        }
        self->FUN_00ca7250("(9) bad culture target");
    }
    self->FUN_00ca7250("(10) orders mismatch");
    self->FUN_00caa900();
    return false;
}
}}  // namespace SP::VehicleTree

// @ 0x00dce970
void TObj::FUN_00dce970(void* param_2)
{
    char* d = (char*)this;
    char* s = (char*)param_2;
    ((TObj*)(d + 0x64))->F_ca0940(param_2);
    TObj* t = (TObj*)FUN_00b3d290();
    *(uint32_t*)(d + 0x90) = (uint32_t)t->F_ac15e0();
    uint32_t src = *(uint32_t*)s;
    uint32_t nv;
    if (src != 0) {
        nv = ((uint32_t(__thiscall*)(void*, uint32_t))VF((void*)src, 0xc))((void*)src, 0xee9b2232);
    } else {
        nv = 0;
    }
    uint32_t ov = *(uint32_t*)(d + 0x94);
    if (nv != ov) {
        if (nv != 0) {
            ((void(__thiscall*)(void*))VF((void*)nv, 0))((void*)nv);
        }
        *(uint32_t*)(d + 0x94) = nv;
        if (ov != 0) {
            ((void(__thiscall*)(void*))VF((void*)ov, 4))((void*)ov);
        }
    }
    *(uint32_t*)(d + 0x98) = *(uint32_t*)(s + 0x14);
    ((TObj*)(d + 0x64))->F_ca0940(param_2);
    uint32_t* v1 = (uint32_t*)(d + 0x9c);
    uint32_t e1 = v1[1];
    uint32_t b1 = v1[0];
    int n1 = (int)(e1 - b1) >> 2;
    if ((uint32_t)n1 < 3u) {
        void* z = 0;
        FUN_00dc8d10((void*)e1, 3 - n1, &z);
    } else {
        FUN_00ae6e70((void*)(b1 + 0xc), (void*)e1);
    }
    uint32_t* v2 = (uint32_t*)(d + 0xb0);
    uint32_t e2 = v2[1];
    uint32_t b2 = v2[0];
    int n2 = (int)(e2 - b2) >> 2;
    if ((uint32_t)n2 < 3u) {
        void* z = 0;
        FUN_00dc8d10((void*)e2, 3 - n2, &z);
    } else {
        FUN_00ae6e70((void*)(b2 + 0xc), (void*)e2);
    }
}

// @ 0x00dcea90
void* TObj::FUN_00dcea90(void* param_2)
{
    char* s = (char*)param_2;
    char* d = (char*)this;
    ((TObj*)this)->F_db5b30(param_2);
    ((TObj*)(d + 0x38))->F_dc8ed0(s + 0x38);
    ASSIGN_REF(*(void**)(d + 0x58), *(void**)(s + 0x58));
    ASSIGN_REF(*(void**)(d + 0x5c), *(void**)(s + 0x5c));
    ASSIGN_REF(*(void**)(d + 0x60), *(void**)(s + 0x60));
    *(uint32_t*)(d + 0x64) = *(uint32_t*)(s + 0x64);
    *(uint32_t*)(d + 0x68) = *(uint32_t*)(s + 0x68);
    *(uint32_t*)(d + 0x6c) = *(uint32_t*)(s + 0x6c);
    *(uint32_t*)(d + 0x70) = *(uint32_t*)(s + 0x70);
    *(uint32_t*)(d + 0x74) = *(uint32_t*)(s + 0x74);
    *(uint32_t*)(d + 0x78) = *(uint32_t*)(s + 0x78);
    *(float*)(d + 0x7c) = *(float*)(s + 0x7c);
    *(float*)(d + 0x80) = *(float*)(s + 0x80);
    *(float*)(d + 0x84) = *(float*)(s + 0x84);
    *(float*)(d + 0x88) = *(float*)(s + 0x88);
    *(float*)(d + 0x8c) = *(float*)(s + 0x8c);
    *(float*)(d + 0x90) = *(float*)(s + 0x90);
    *(float*)(d + 0x94) = *(float*)(s + 0x94);
    *(uint8_t*)(d + 0x98) = *(uint8_t*)(s + 0x98);
    *(float*)(d + 0x9c) = *(float*)(s + 0x9c);
    ((TObj*)(d + 0xa0))->F_d5d4b0(s + 0xa0);
    ((TObj*)(d + 0x104))->F_d5d4b0(s + 0x104);
    *(uint32_t*)(d + 0x168) = *(uint32_t*)(s + 0x168);
    *(uint32_t*)(d + 0x16c) = *(uint32_t*)(s + 0x16c);
    *(uint32_t*)(d + 0x170) = *(uint32_t*)(s + 0x170);
    *(uint32_t*)(d + 0x174) = *(uint32_t*)(s + 0x174);
    return this;
}

// @ 0x00dceca0
void TObj::FUN_00dceca0()
{
    char* d = (char*)this;
    ((TObj*)(d + 0x38))->F_b48e40(*(void**)(d + 0x38), *(void**)(d + 0x3c));
    TObj* nm = (TObj*)FUN_00b3d300();
    char* vec = (char*)nm->F_b21340((void*)FUN_00cd7d10, (void*)FUN_00d3d420,
                                   (void*)FUN_00ace0f0, (void*)FUN_00b1e500, &DAT_018eb45e);
    void** begin = *(void***)(vec + 4);
    void** end = *(void***)(vec + 8);
    while (begin != end) {
        TObj* o = (TObj*)*begin;
        if (o != 0 && *(uint8_t*)((char*)o + 0x135) != 0 && ((TObj*)o)->F_c0c0e0() != 0) {
            TObj* e = (TObj*)((char*)o + 0xc0);
            void* local = e;
            if (e != 0) {
                ((void(__thiscall*)(void*))VF(e, 0xbc))(e);
            }
            void** pos = *(void***)(d + 0x3c);
            if (pos < *(void***)(d + 0x40)) {
                *(void***)(d + 0x3c) = pos + 1;
                if (pos != 0) {
                    *pos = e;
                    if (e != 0) {
                        ((void(__thiscall*)(void*))VF(e, 0xbc))(e);
                    }
                }
            } else {
                ((TObj*)(d + 0x38))->F_bab900(pos, &local);
            }
            if (e != 0) {
                ((void(__thiscall*)(void*))VF(e, 0xc0))(e);
            }
        }
        begin++;
    }
}

// @ 0x00dced90
void TObj::FUN_00dced90()
{
    ((TObj*)this)->FUN_00dceca0();
    *(uint32_t*)((char*)this + 0x50) = 0x3e8;
    *(uint32_t*)((char*)this + 0x54) = 0;
}

// @ 0x00dcf180
void* TObj::FUN_00dcf180(void* param_2, uint32_t param_3, uint32_t param_4)
{
    uint32_t* v = (uint32_t*)this;
    if (v[1] != v[2]) {
        uint32_t b = param_4;
        if (param_3 <= param_4 && param_4 < v[1]) {
            b = param_4 + 0x178;
        }
        if (v[1] != 0) {
            FUN_00dcd590((void*)(v[1] - 0x178));
        }
        FUN_00dcec60(param_2, (void*)(v[1] - 0x178), (void*)v[1]);
        ((TObj*)param_2)->FUN_00dcea90((void*)b);
        v[1] = v[1] + 0x178;
        return this;
    }
    int cnt = (int)((v[1] - v[0])) / 0x178;
    int cap;
    if (cnt == 0) {
        cap = 1;
    } else {
        cap = cnt * 2;
        if (cap == 0) {
            cap = 0;
            goto have;
        }
    }
    {
        int sz = cap * 0x178;
        (void)sz;
    }
have:
    int cap2;
    if (cnt == 0) {
        cap2 = 1;
    } else {
        cap2 = cnt * 2;
    }
    void* buf = 0;
    if (cap2 != 0) {
        buf = FUN_00f473a0(cap2 * 0x178, "Simulator", 0, 0, 0x13ebb38, 0xd1);
    }
    uint32_t first = v[0];
    uint32_t iVar3 = (uint32_t)FUN_00dcd6e0((void*)first, param_2, buf);
    FUN_00dc4cc0((void*)first, param_2, buf);
    if (iVar3 != 0) {
        FUN_00dcd590((void*)param_4);
    }
    uint32_t last = v[1];
    uint32_t iVar4 = (uint32_t)FUN_00dcd6e0(param_2, (void*)last, (void*)(iVar3 + 0x178));
    FUN_00dc4cc0(param_2, (void*)last, (void*)(iVar3 + 0x178));
    uint32_t old = v[0];
    if (old != 0 && *(uint32_t*)(old - 4) != 0) {
        FUN_00f47380((void*)old);
    }
    v[0] = (uint32_t)buf;
    v[1] = iVar4;
    v[2] = (uint32_t)(cap2 * 0x178 + (int)buf);
    return this;
}

// @ 0x00dcf2e0
namespace SP {
void cVehicleGroupOrder_s00dc_f2e0::FormationMoveToTargets(int)
{
    int numVehicles = (int)(mpVehiclesEnd - mpVehiclesBegin);
    for (int i = 0; i < numVehicles; i++) {
        cVehicle_s00dc_f2e0* pVehicle = mpVehiclesBegin[i];
        cSpatialObject_s00dc_f2e0* pTarget = pVehicle->GetChaseTarget();
        if (!pTarget)
            continue;

        int current = -1;
        int best = -1;
        int numFormations = mFormations.size();
        for (int j = 0; j < numFormations; j++) {
            Formation* pFormation = &mFormations.mpBegin[j];
            if (pFormation->mpEntBegin == pFormation->mpEntEnd)
                continue;
            cVehicle_s00dc_f2e0* pOther = 0;
            if (pFormation->mpLeader)
                pOther = AsVehicle(pFormation->mpLeader);
            if (!pOther)
                pOther = AsVehicle(*pFormation->mpEntBegin);
            if (pOther && pFormation->mpTarget == pTarget && pOther->mLocomotion == pVehicle->mLocomotion) {
                const cSPVector3& a = pTarget->GetPosition();
                const cSPVector3& b = pOther->mLoco.GetPosition();
                cSPVector3 d = b - a;
                if (d.LengthSquared() < FLT_MAX)
                    best = j;
                if (IsFormationMember(pFormation, &pVehicle))
                    current = j;
            }
        }
        if (current != best) {
            if (current != -1) {
                cLocomotive_s00dc_f2e0* pLoco = pVehicle ? &pVehicle->mLoco : 0;
                mFormations.mpBegin[current].RemoveEntity(pLoco);
                mFormations.mpBegin[current].mCircle.RemoveAgent(pVehicle);
            }
            if (best != -1) {
                cLocomotive_s00dc_f2e0* pLoco = pVehicle ? &pVehicle->mLoco : 0;
                Formation* pBest = &mFormations.mpBegin[best];
                pBest->AddEntity(pLoco);
                const cSPVector3& c = ((cTargetAt*)pTarget)->GetPositionAt(pBest->mMinDistance, pBest->mMaxDistance);
                pVehicle->SetAcceptableCenter(c);
            }
            current = best;
        }

        if (current == -1) {
            mFormations.push_back();
            Formation* pNew = mFormations.mpEnd - 1;
            pNew->mpSlotValidationFunc = FUN_00dc7590;
            pNew->mpLeaderSelectFunc = (void*)FUN_00dc76e0;
            pNew->mpMoveCommandFunc = (void*)FUN_00dc6430;
            AssignRef(pNew->mpTarget, pTarget);
            pNew->mMinDistance = 8.0f;
            pNew->mMaxDistance = pVehicle->mCombatant.GetStat() * 0.75f;
            cLocomotive_s00dc_f2e0* pLoco = &pVehicle->mLoco;
            pNew->mEntityRadius = pLoco->GetFootprintRadius() + 2.0f;
            pNew->mTimerInterval = 0.1f;
            pNew->AddEntity(pLoco);
            AssignRef(pNew->mpLeader, pLoco);
            pNew->mbWaitingForPath = true;
            pLoco->MoveTowards(((cTargetAt*)pTarget)->GetPositionAt(pNew->mMinDistance, pNew->mMaxDistance * 0.5f));
            pVehicle->SetAcceptableCenter(((cTargetAt*)pTarget)->GetPositionAt(0.0f, 1.0f));
            pNew->mCircle.mSlots.erase(pNew->mCircle.mSlots.mpBegin, pNew->mCircle.mSlots.mpEnd);
        }
        else {
            Formation* pFormation = &mFormations.mpBegin[current];
            cActionCircle_s00dc_f2e0* pCircle = &pFormation->mCircle;
            cLocomotive_s00dc_f2e0* pLoco = pVehicle ? &pVehicle->mLoco : 0;
            if (pLoco == pFormation->mpLeader) {
                cMoveRequest* pRequest = pVehicle->mLoco.GetMoveRequest();
                if (pRequest->mField5C) {
                    cSPVector3 dst = *pRequest->GetDestination();
                    if (pCircle->mSlots.mpBegin == pCircle->mSlots.mpEnd) {
                        cSPVector3 d = pTarget->GetPosition() - dst;
                        cSPVector3 dir = d.Normalized();
                        float radius = CircleRadius(pFormation->mEntityRadius, (int)(pFormation->mpEntEnd - pFormation->mpEntBegin));
                        pCircle->Setup(dst, radius, dir, 0.0f);
                        pCircle->Layout(pFormation->mEntityRadius, (int)(pFormation->mpEntEnd - pFormation->mpEntBegin));
                        pFormation->mpSlotValidationFunc(pFormation, pCircle, 1);
                    }
                }
            } else {
                cLocomotive_s00dc_f2e0* pSp = &pVehicle->mLoco;
                if (pSp->GetDesiredSpeed() == 0.0f && !(pVehicle->mLoco.mFlags & 4) &&
                    pCircle->mSlots.mpBegin != pCircle->mSlots.mpEnd) {
                    const cSPVector3& p = pSp->GetPosition();
                    cSPVector3 d = p - pCircle->mCenter;
                    float r = pCircle->mRadius;
                    if (r + r < sqrtf(d.x * d.x + d.y * d.y + d.z * d.z))
                        pSp->MoveAround(pCircle->mCenter, r * 1.75f);
                }
            }
        }
    }

    int numFormations = mFormations.size();
    for (int j = 0; j < numFormations; j++) {
        Formation* pFormation = &mFormations.mpBegin[j];
        if (pFormation->mpEntBegin == pFormation->mpEntEnd || pFormation->mCircle.mSlots.mpBegin == pFormation->mCircle.mSlots.mpEnd)
            continue;
        VehicleVec list;
        cActionCircle_s00dc_f2e0* pCircle = &pFormation->mCircle;
        int count = (int)(pFormation->mpEntEnd - pFormation->mpEntBegin);
        for (int k = 0; k < count; k++) {
            cVehicle_s00dc_f2e0* pV = AsVehicle(pFormation->mpEntBegin[k]);
            const cSPVector3& p = pV->mLoco.GetPosition();
            cSPVector3 d = p - pCircle->mCenter;
            float dist = sqrtf(d.x * d.x + d.y * d.y + d.z * d.z);
            if (dist < pCircle->mRadius + pCircle->mRadius)
                list.push_back(pV);
        }
        int remaining = list.size();
        int numSlots = (int)(pCircle->mSlots.mpEnd - pCircle->mSlots.mpBegin);
        if (numSlots > 0 && remaining > 0) {
            pFormation->mpSlotValidationFunc(pFormation, pCircle, 1);
            for (int s = 0; s < numSlots; s++) {
                if (remaining <= 0)
                    break;
                tSlot_s00dc_f2e0* pSlot = &pCircle->mSlots.mpBegin[s];
                if (!pSlot->mbOccupied) {
                    bool flag = false;
                    cVehicle_s00dc_f2e0* pClosest = FindClosestVehicle(&list, &pSlot->mPosition, flag);
                    if (pClosest) {
                        pSlot->Occupy(pClosest);
                        cSPVector3 tmp;
                        const cSPVector3* pCur = pClosest->GetDestinationOut(&tmp);
                        if (!(*pCur == pSlot->mPosition))
                            pClosest->mLoco.MoveTo(pSlot->mPosition, 1.0f, 2.0f, false);
                        cVehicle_s00dc_f2e0** it = list.mpBegin;
                        for (; it != list.mpEnd; ++it) {
                            if (*it == pClosest) {
                                list.erase(it);
                                break;
                            }
                        }
                        --remaining;
                    }
                }
            }
            for (int k = 0; k < list.size(); k++) {
                cVehicle_s00dc_f2e0* pV = list.mpBegin[k];
                uint32_t flags = pV->mLoco.mFlags;
                if (flags & 2)
                    AttemptRepark(pV);
                else if (flags & 4)
                    pV->FUN_00cacbe0();
            }
        }
        pCircle->FUN_00c2e4e0();
    }
}
}  // namespace SP

// @ 0x00dcfc40
namespace SP {
void cVehicleGroupOrder_s00dc_f2e0::Clear()
{
    ClearBaseMembers();
}
}  // namespace SP

// @ 0x00dcfc90
namespace SP {
cCombatant_s00dc_f2e0* cMilitaryAttackCityOrder_s00dc_f2e0::GetCurrentTarget(cVehicle_s00dc_f2e0* pVehicle)
{
    if (mpCity->IsDestroyed())
        return 0;
    if (mpVehiclesBegin == mpVehiclesEnd)
        return 0;
    if (mpCity->GetCivilization()->GetOwnerId() == mAttackerId)
        return 0;

    int locomotion = pVehicle->mLocomotion;
    CombatantRef* pCurrent = &mCurrentBestTarget.mpBegin[locomotion];
    CombatantRef* pNext = &mNextBuildingTarget.mpBegin[locomotion];

    if (pCurrent->mpObject && IsValidFireTarget(&pVehicle->mCombatant, pCurrent->mpObject)) {
        cBuilding_s00dc_f2e0* pBuilding = (cBuilding_s00dc_f2e0*)pCurrent->mpObject->Cast(kBuildingType);
        cVehicle_s00dc_f2e0* pTargetVehicle = (cVehicle_s00dc_f2e0*)pCurrent->mpObject->Cast(kVehicleType);
        if (pBuilding) {
            if (pBuilding->HasFlag(kProtectBuildingFlag) && mpCity->DefenseLevel() > 1)
                goto clear_current;
            if (mpCity->Population() > 0)
                goto clear_current;
            {
                HostileVec* pHostiles = pVehicle->GetHostiles();
                if (pHostiles->mpBegin != pHostiles->mpEnd)
                    goto clear_current;
            }
            return pCurrent->mpObject;
        }
        if (pTargetVehicle) {
            if (pVehicle->CanAttack(&pTargetVehicle->mCombatant))
                return pCurrent->mpObject;
        }
    }

clear_current:
    {
        cCombatant_s00dc_f2e0* pOld = pCurrent->mpObject;
        pCurrent->mpObject = 0;
        if (pOld)
            pOld->Release();
    }
    mFormations.erase(mFormations.mpBegin, mFormations.mpEnd);

    if (pNext->mpObject && IsValidFireTarget(&pVehicle->mCombatant, pNext->mpObject)) {
        cBuilding_s00dc_f2e0* pNextBuilding = InterfaceCastBuilding(pNext);
        if (pNextBuilding) {
            if (pNextBuilding->HasFlag(kProtectBuildingFlag) && mpCity->DefenseLevel() > 1) {
                // protected building: fall through to the member scan
            } else if (mpCity->Population() > 0) {
                // city still has inhabitants: fall through to the member scan
            } else {
                goto choose_city_target;
            }
        } else {
            goto choose_city_target;
        }
    }

    pNext->Release();
    {
        float bestDist = FLT_MAX;
        MemberVec* pMembers = mpCity->GetMembers();
        for (cCityMemberView** ppMember = pMembers->mpBegin; ppMember != pMembers->mpEnd; ++ppMember) {
            cCityMemberView* pMember = *ppMember;
            if (pMember->HasFlag(kProtectBuildingFlag))
                continue;
            cCombatant_s00dc_f2e0* pTarget = &pMember->mCombatant;
            if (!IsValidFireTarget(&pVehicle->mCombatant, pTarget))
                continue;
            const cSPVector3& a = pVehicle->mLoco.GetPosition();
            const cSPVector3& b = pMember->mLoco.GetPosition();
            cSPVector3 d = b - a;
            float dist = sqrtf(d.x * d.x + d.y * d.y + d.z * d.z);
            if (bestDist > dist) {
                pNext->Set(pTarget);
                bestDist = dist;
            }
        }
        if (!pNext->mpObject) {
            cBuilding_s00dc_f2e0* pHall = mpCity->GetCityHall();
            pNext->Set(pHall ? &pHall->mCombatant : 0);
        }
    }

choose_city_target:
    {
        float bestDist = FLT_MAX;
        cTargetProviderView* pBest = 0;
        TargetVec targets;
        mpCity->CollectTargets(&targets);
        for (int i = 0; i < targets.size(); ++i) {
            cTargetProviderView* pCandidate = targets.mpBegin[i];
            if (!pCandidate)
                continue;
            cCombatant_s00dc_f2e0* pTarget = &pCandidate->mCombatant;
            if (!IsValidFireTarget(&pVehicle->mCombatant, pTarget))
                continue;
            const cSPVector3& a = pVehicle->mLoco.GetPosition();
            cSpatialObject_s00dc_f2e0* pSpatial = pTarget->GetSpatialObject();
            const cSPVector3& b = pSpatial->GetPosition();
            cSPVector3 d = b - a;
            float dist = sqrtf(d.x * d.x + d.y * d.y + d.z * d.z);
            float reach = pTarget->GetStat() + 5.0f;
            if (dist >= reach)
                continue;
            if (bestDist > dist) {
                pBest = pCandidate;
                bestDist = dist;
            }
        }
        if (pBest)
            pCurrent->Set(&pBest->mCombatant);
    }

    if (!pCurrent->mpObject) {
        if (pVehicle->GetCurrentCity() == mpCity) {
            cCombatant_s00dc_f2e0* pOpportunity =
                mpCity->GetBestOpportunityTarget(pVehicle, mpCity->GetCivilization(), 1, 1, 1);
            if (pOpportunity) {
                cVehicle_s00dc_f2e0* pOpportunityVehicle = (cVehicle_s00dc_f2e0*)pOpportunity->Cast(kVehicleType);
                if (pOpportunityVehicle)
                    pCurrent->Set(&pOpportunityVehicle->mCombatant);
            }
        }
    }
    if (!pCurrent->mpObject && pNext->mpObject)
        pCurrent->Set(pNext->mpObject);
    return pCurrent->mpObject;
}
}  // namespace SP

// @ 0x00dd0180
namespace SP {
cCulturalConvertCityOrder_s00dc_f2e0::~cCulturalConvertCityOrder_s00dc_f2e0()
{
    ClearBaseMembers();
    if (mpCulturalTarget) {
        if (!mpCulturalTarget->IsDestroyed())
            mpCulturalTarget->RemoveVehicleGroup(mGroupMoveId);
    }
    if (mpCulturalTarget) {
        cCulturalTarget_s00dc_f2e0* pOldTarget = mpCulturalTarget;
        *(cCulturalTarget_s00dc_f2e0* volatile*)&mpCulturalTarget = 0;
        pOldTarget->Release();
    }
    ClearHologramEffects();
    cVehicle_s00dc_f2e0* pOldHolo = mpHoloVehicle;
    *(cVehicle_s00dc_f2e0* volatile*)&mpHoloVehicle = 0;
    if (pOldHolo)
        pOldHolo->Release();
}
}  // namespace SP

// @ 0x00dd0230
bool __cdecl VehicleTree_AttackCityOrder_Activate(cVehicle_s00dd_0230* pVehicle, uint32_t, uint32_t, uint32_t, uint32_t, cMilitaryAttackCityOrder** ppOrder)
{
    if (ppOrder != 0)
        *ppOrder = 0;

    void* pData = pVehicle->GetTreeData();

    if (gVehicleTicker_s00dd_0230 == 0)
        gVehicleTicker_s00dd_0230 = new ("Simulator/SimSingleton", 0, 0, 0, 0) cVehicleTicker_s00dd_0230;

    cVehicleGroupOrder* pOrder = gVehicleTicker_s00dd_0230->GetGroupOrder(pData);
    cMilitaryAttackCityOrder* pCityOrder;
    if (pOrder != 0
        && (pCityOrder = (cMilitaryAttackCityOrder*)pOrder->FindOrderByType(0x2e9ae69)) != 0) {
        pCityOrder->SetupOrder(pVehicle);
        pCityOrder->ResetOrder(pVehicle);
        {
            cMilitaryAttackCityOrder* pOld = *ppOrder;
            if (pCityOrder != pOld) {
                pCityOrder->AddRef();
                *ppOrder = pCityOrder;
                if (pOld != 0)
                    pOld->Release();
            }
        }

        cSpatialObject_s00dd_0230* pTarget = pCityOrder->GetCurrentTarget(pVehicle);
        if (pTarget != 0 && IsValidFireTarget(pVehicle ? &pVehicle->mCombatant : 0, pTarget)) {
            pVehicle->SetTarget(pTarget->v08());
            Vehicle_ClearOrder(pVehicle);
            return true;
        }

        if (pVehicle->mpChaseTargetRef != 0) {
            cSpatialObject_s00dd_0230* pOld = pVehicle->mpChaseTargetRef;
            pVehicle->mpChaseTargetRef = 0;
            pOld->vc0();
        }
        pVehicle->Log("(3.1) No target");
        pVehicle->Flush();
        return false;
    }

    pVehicle->Log("(3) No attack order");
    pVehicle->Flush();
    return false;
}
