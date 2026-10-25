// src/game/SPGonzago/SPVehicleBehaviorTree.cpp -- migrated from slice(s) s00dd0230, s00dce4d0, s00dcc830, s00dcb8e0, s00dc8d10, s00dc67d0, s00dc48e0 by tools/migrate/rewrite.py
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
#pragma pack(push,1)
#pragma pack(pop)

// ---- items of slice s00dc48e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float   DAT_013ec4d0;   // 0x013ec4d0
extern float   DAT_01473c70;   // 0x01473c70
extern float   DAT_0169fa68;   // 0x0169fa68
extern float   DAT_0169fa6c;   // 0x0169fa6c
extern float   DAT_0169fa70;   // 0x0169fa70
struct Obj;
typedef void          (__thiscall *VfnRaw)(void);
typedef void*         (__thiscall *VfnP)(void*);
typedef unsigned int  (__thiscall *VfnR)(void*);
typedef unsigned char (__thiscall *VfnB)(void*);
typedef void*         (__thiscall *VfnPI)(void*, int);
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
extern void* __stdcall SP_PlanetModel(void* a);  // 0xb3d350
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
    PV(3b)
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
void* __cdecl FUN_00dc6680(void* a, void* b, void* c);             // 0x00dc6680 (FindClosestVehicle)
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
extern uint32_t gVehicleServiceTable714;   // 0x0147c714
typedef int    (__thiscall* FnI)(void*);
typedef float* (__thiscall* FnFP)(void*);
typedef void*  (__thiscall* FnVP)(void*, int);
struct VTable { void* p[64]; };
static inline int CallV(void* obj, int slot)
{
  return ((FnI)(*(VTable**)obj)->p[slot / 4])(obj);
}
static inline float* CallVPos(void* obj, int slot)
{
  return ((FnFP)(*(VTable**)obj)->p[slot / 4])(obj);
}
static inline void* CallVArgP(void* obj, int slot, int arg)
{
  return ((FnVP)(*(VTable**)obj)->p[slot / 4])(obj, arg);
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

  Brain* GetBrain();                            // 0x00ca71d0
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
struct StateCtx {
  uint8_t mPad00[0x20];       // +0x00
  uint8_t mFlag20;            // +0x20
  uint8_t mFlag21;            // +0x21
};
void*  AllocSimObject(uint32_t size, const char* name, int a, int b, int c, int d);
void*  __stdcall VectorInsertU32(uint32_t* pos, uint32_t* value); // 0x004558a0
void*  __fastcall SimSingleton_ctor(void* mem);         // 0x00dc7d70
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

// @ 0x00dc4c40
void* KeyLookup::Match3DF(int key)
{
    if (key == 0x3df2cb9 || key == 0x2e98ab4)
        return this;
    return Default(key);
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
    if (t) {
        Obj* target = (Obj*)((VfnPI)t->mpVtbl->mSlots[kVt0C])(t, 0x13f94d4);
        if (target) {
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
    return FUN_00dc6680(a, b, 0);
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
void* FUN_00dcc440(BehaviorObj* self, int specialty, void* exclude)
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

// @ 0x00dcc610
void FUN_00dcc610(BehaviorObj* self)
{
  if (!CallV(&self->mLoco, 0x58))
    return;

  int mode = 0;
  Brain* brain = self->GetBrain();

  if (brain->mMode10 == 1) {
    void* nearby = self->GetNearby();
    if (nearby != 0) {
      void* p = CallVArgP(nearby, 0xb8, 0xd0036e08);
      if (p != 0 && Flag388(p))
        mode = 1;
    }
  } else if (brain->mMode10 == 8) {
    int r = CallV(brain->mpObj0, 0x20);
    mode = (r != 0x403df5c) + 2;
  }

  int index = self->mFieldB20;
  index = index + mode * 3;

  if (gVehicleTicker == 0) {
    void* mem = AllocSimObject(0x58, "Simulator/SimSingleton", 0, 0, 0, 0);
    void* obj;
    if (mem != 0)
      obj = SimSingleton_ctor(mem);
    else
      obj = 0;
    gVehicleTicker = obj;
  }

  ((Vector24*)gVehicleTicker)->PushUnique(
      (&gVehicleServiceTable714)[index]);
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

// @ 0x00dcc830
namespace SP {
void __thiscall cVehicleTree::TradeWithCityOrder_Tick()
{
}
}  // namespace SP

// @ 0x00dcce90
namespace SP {
void __thiscall cVehicleTree::OfferToBuyCityOrder_Activate()
{
}
}  // namespace SP

// @ 0x00dccfd0
namespace SP {
void __thiscall cVehicleTree::MoveToPointOrder_Activate()
{
}
}  // namespace SP

// @ 0x00dcd050
namespace SP {
void __fastcall FUN_00dcd050(void* this_, int unused)
{
    (void)this_;
}
}  // namespace SP

// @ 0x00dcd180
namespace SP {
void __fastcall FUN_00dcd180(void* this_, int unused)
{
    (void)this_;
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
    mpVtbl0 = &gCulturalConvertCityOrderVtbl0;
    mpVtbl1 = &gCulturalConvertCityOrderVtbl1;
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
