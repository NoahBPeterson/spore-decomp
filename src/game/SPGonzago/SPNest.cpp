// src/game/SPGonzago/SPNest.cpp -- migrated from slice(s) s01347830, s00c6a4d0, s00c6a430, s00c6a270, s00c69be0, s00c69a70, s00c69a00, s00c699a0, s0134d380, s00c6b660, s00c6e710, s00c6c630, s00c6a550, s00c69300 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPNest.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
// addresses retail relocates here, named so the build relocates them too
extern "C" char g_1471ba0[];
extern "C" char g_1471b8c[];
extern "C" char g_1471ac8[];
extern "C" char g_1471aac[];
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include "SP/cGameData.h"
#include "SP/cHerd.h"
#include "SP/cPlanetModel.h"
#include "SP/cNest.h"
#include "SP/cEgg.h"
#include "SP/cVarListSerializer.h"
#include <math.h>
#include "SP/cSpatialObject.h"
#include "SP/cInteractionTarget.h"
#include "SP/cCombatant.h"
#include "SP/cGonzagoTimer.h"

// ---- items of slice s00c69300 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char u8;
typedef unsigned int  u32;
struct cPlanetModel {
    void SnapB();                 // 0x00b82970
};
struct cCreatureModeStrategy {
    bool HasCreatureTutorialOccurred();   // 0x00d38980
};
struct cVec3 {
    float mX;                     // 0x00
    float mY;                     // 0x04
    float mZ;                     // 0x08
};
u32 __stdcall SP_PlanetModel(u32 a, u32 b, u32 c);            // 0x00b3d350
u32 GetCurrentGameMode();                                     // 0x00b5b800
cCreatureModeStrategy* __stdcall GetCreatureModeStrategy(u32 key);  // 0x00d38840
static inline bool VT_2C_0(void* p)
{
    return ((bool (__thiscall*)(void*))(*(void***)p)[11])(p);
}
struct cObjectBase {
    void* CastBase(int type);     // 0x00b18460
};
struct cObject {
    void* Cast(int type);         // 0x00c69db0
};
struct cHerd {
    u8     mPad0000[0x15c];
    int    mState15c;             // 0x15c
    u8     mPad0160[0x208 - 0x160];
    u8     mFlag208;              // 0x208
    u8     mPad0209[0x20c - 0x209];
    cVec3  mTarget20c;            // 0x20c

    void SetTarget(const cVec3* v);   // 0x00c69ff0
    bool ShouldActivate();            // 0x00c6a030
};
// ---- items of slice s00c69300 end

// ---- items of slice s00c6a550 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  __cdecl FUN_00c6a100(void* egg);                     // 0x00c6a100 egg effect refresh
extern "C" void* __cdecl FUN_00b530e0(void* p, int a);                // 0x00b530e0
extern "C" void* __cdecl FUN_00401090();                              // returns the species manager
extern "C" void* __stdcall FUN_00b3d4c0(void* a, int b, int c);
extern "C" int   __cdecl FUN_00ba3f90(void* a, int b, int c);
extern "C" void* __cdecl PlanetModel();                               // 0x00b3d350
extern "C" void* __cdecl TerraformingManager();                       // 0x00b3d430
extern "C" void* __cdecl NounManager();                               // 0x00b3d300
extern "C" void* __stdcall FUN_00b18460(int id);
extern "C" void* __cdecl FUN_00d51660();                              // 0x00d51660
extern "C" void* __cdecl FUN_00c099e0(void* a, int b, int c, int d, int e);
extern "C" void  __cdecl FUN_00bc97f0(int a, int key, float f, int b);
extern "C" void* __cdecl FUN_00d99500(void* noun);
extern "C" void  __cdecl FUN_00c02c20(void* a, int b);
extern "C" void  __cdecl FUN_00ae2e40(void* stream, const void* key);
extern "C" int   __cdecl FUN_00c0b770(void* o);
extern "C" void* __cdecl FUN_00c04590(void* o);
extern "C" void* __cdecl FUN_00c884f0(void* spatial, int id);         // AsInterface thunk
extern "C" void* __cdecl FUN_00ac0320(void* it, int id);              // AsInterface thunk
extern "C" void* __cdecl FUN_00c0bbd0(void* creature);                // GetSpeciesProfile
extern "C" void* __cdecl FUN_00b1fdb0(void* nounManager);             // GetAvatar
extern "C" void  __cdecl FUN_00c09fa0(void* pos, int key, int count, float f, void* herd);  // SpawnHerdAnimals
extern "C" char  __cdecl FindClosestWater(void* planet, const void* pos, float dist, void* out);  // 0xb8bb70
extern "C" void* __cdecl FUN_00b815a0(void* planet, void* out, const void* dir);  // DirectionToSurfacePosition
extern "C" void* __cdecl FUN_00b7f190(void* planet, void* out, const void* pos);  // BuildSurfaceOrientation
extern "C" void* __cdecl FUN_00b7f250(void* planet, void* out, const void* p1, const void* p2);  // BuildSurfaceOrientation2
extern "C" void  __cdecl FUN_00449c20(void* out, const void* in);     // normalized_safe
extern "C" int   __cdecl FUN_00b18590(void* gd, void* stream);        // cGameData::Write
extern "C" int   __cdecl FUN_00c88a90(void* so, void* stream);        // cSpatialObject::Write
extern "C" int   __cdecl FUN_00bfc4a0(void* cb, void* stream);        // cCombatant::Write
extern "C" void  __cdecl FUN_00692f90(void* ser, void* obj, void** list, int sig);  // cVarListSerializer ctor
extern "C" int   __cdecl FUN_00692900(void* ser, void* stream);       // cVarListSerializer::Serialize
extern "C" void* __cdecl FUN_0067dd10();                              // SP::App
extern "C" void  __cdecl FUN_007c3d30(void* viewer, void* a, void* b, void* c, void* d);  // GetCameraLocationInfo
extern "C" void* __cdecl FUN_00c89160(void* so, const void* ext, int flag);   // SetLocalExtents
extern float gHalf;              // 0x01471064  0.5f
extern float gEpsilon;           // 0x014718ec  1.52587890625e-05f
extern float gZeroF;             // 0x01485378  0.0f
extern float gFiveF;             // 0x01486110  5.0f
extern float gWaterSearchDist;   // 0x01582e8c  100.0f
extern float gFiftyF;            // 0x01582f5c  50.0f
extern float gViewerOrigin[3];   // 0x01693e50..0x01693e58
extern int   gViewerGuard;       // 0x01693e4c
extern SP::cDataSerializerGeneric gEggSerializerList; // 0x015778f0
#pragma warning(disable : 4100)

namespace EA {
namespace IO {
bool WriteUint32(void* sink, const void* src, int count, int flags);       // 0x0093aa70
}
}
struct cSpeciesMgr {
void* GetProfile(const void* key);              // 0x4df550
void* GetAvatarProfile();                       // 0x4df420
};
extern u32   gViewerData[3];     // 0x01693e40..0x01693e48
namespace SP {
struct Vec3 { float x, y, z; };
}
namespace SP {
struct Quat { float x, y, z, w; };
}
namespace SP {
struct cSPTimerStub { void Restart(); };
}
namespace SP {
class ThisStubs
{
  public:
    void A();   // 0x00b18660 cGameData ctor
    void B();   // 0x00c89630 cSpatialObject ctor
    void C();   // 0x00ac03d0 cInteractionTarget ctor
    void D();   // 0x00ac0520 cInteractionTarget dtor-ish
    void E();   // 0x00c8a420 cSpatialObject dtor-ish
    void F();   // 0x00b184c0 cGameData dtor
    void G();   // 0x00ac0450 cInteractionTarget clear
    void H();   // 0x00c8b2e0 cSpatialObject clear
    void I();   // 0x00bbc3f0 TerraformingManager footstep
    bool WriteGameData(void* stream);   // 0x00b18590
    bool WriteSpatial(void* stream);    // 0x00c88a90
    bool WriteCombatant(void* stream);  // 0x00bfc4a0
};
}
namespace SP {
class IOStream
{
  public:
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
    virtual void v1c();
    virtual void* GetWriter();          // +0x20
};
}
namespace SP {
class IWriter
{
  public:
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
    virtual void* GetSink();            // +0x18
    virtual void  Finish();             // +0x1c
};
}
namespace SP {
class ISpatial
{
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
    virtual const Vec3* GetPosition();          // +0x2c
virtual void v30();
virtual void v34();
virtual void v38();
    virtual void SetPosition(const Vec3*);      // +0x38 (ret 4)
    virtual void SetOrientation(const Quat*);   // +0x3c (ret 4)
virtual void v40();
virtual void v44();
    virtual void SetLocalExtents(const void*);  // +0x48
};
}
namespace SP {
class cVarListSerializer_s00c6_a550
{
  public:
    bool Serialize(IOStream* stream);
    unsigned char mData[0xa14];
};
}
namespace SP {
class RefObj
{
  public:
    virtual void AddRef();              // +0x00
    virtual void Release();             // +0x04
    virtual void slot08();
    virtual void slot0c();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1c();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual bool IsValid();             // +0x2c
};
}
namespace SP {
class cEgg_s00c6_a550
{
  public:
    enum EggState { kWell = 0, kCrack1 = 1, kCrack2 = 2, kHatched = 3, kBroken = 4, kReadyToHatch = 5, kLaid = 6 };

    bool Write(IOStream* stream);               // 0xc6a550 (ret 4)
    void SetState(EggState state);              // 0xc6a670 (ret 4)
    __declspec(noinline) bool StateStep();      // 0xc6a6e0
    void Update(int dt);                        // 0xc6b040 (ret 4)

    ISpatial* Spatial() { return reinterpret_cast<ISpatial*>(reinterpret_cast<char*>(this) + 0x34); }

    unsigned char pad000[0x154];
    u32 mCombatDamageState;                     // 0x154
    unsigned char pad158[0x1e8 - 0x158];
    EggState mState;                            // 0x1e8
    u8 effectShouldUpdate;                      // 0x1ec
    unsigned char pad1ed[0x3];
    int mTimeToHatch;                           // 0x1f0
    RefObj* mpHerd;                             // 0x1f4
    unsigned char mBrokenTimer[0x20];           // 0x1f8
    RefObj* mpToHatch;                          // 0x218
    RefObj* mpWhoIsInteractingWithMe;           // 0x21c
    float mEffectScale;                         // 0x220
};
}
namespace SP {
class cNest_s00c6_a550
{
  public:
    cNest_s00c6_a550();                                    // 0xc6a870
    ~cNest_s00c6_a550();                                   // 0xc6a970
    void RemoveOwner();                         // 0xc6a9c0
    void MoveNest(const Vec3& pos);             // 0xc6aab0 (ret 4)
    void AddFootprint();                        // 0xc6ab90
    bool LoadModel(void* modelWorld);           // 0xc6b410 (ret 4)
    void* AsInterface(int id);                  // 0xc6b390 (ret 4)
    bool CanSpawn();                            // 0xc6aa50

    ISpatial* Spatial() { return reinterpret_cast<ISpatial*>(reinterpret_cast<char*>(this) + 0x34); }

    unsigned char pad000[0x2c];
    RefObj* mpOwner2c;                          // 0x2c
    unsigned char pad030[0xd0 - 0x30];
    void* mp0d0;                                // 0xd0
    unsigned char pad0d4[0x120 - 0xd4];
    u8 mbShowPlacement;                         // 0x120
    unsigned char pad121[0x124 - 0x121];
    void* mp124;                                // 0x124
    RefObj* mpOwner128;                         // 0x128
    void* mpFootprint12c;                       // 0x12c
};
}
namespace SP {
class cHerd_s00c6_a550
{
  public:
    void* GetProfileForGeneration(unsigned gen);        // 0xc6abf0 (ret 4)
    void  OnAnimalRemoved(void* animal);                // 0xc6b440 (ret 4)
    void  FindWateringHole();                           // 0xc6b5b0
    void  SpawnAnimalsIfUnderfilled();                  // 0xc6b540
    float FUN_00c69f80();                               // 0xc69f80 (baby fraction)
    void  SetEnabled(u8 on);                            // 0xc6ace0 (ret 4)
    bool  UnbrokenEggsInNest();                         // 0xc6ac40
    int   ClearLocationStatus(int i);                   // 0xc6ac90 (ret 4)
    int   GetHerdAnimalFlag();                          // 0xc6aa10

    unsigned char pad000[0x40];
    void** mpHerdBegin;                         // 0x40
    void** mpHerdEnd;                           // 0x44
    unsigned char pad048[0x54 - 0x48];
    void** mpListBegin;                         // 0x54
    void** mpListEnd;                           // 0x58
    unsigned char pad05c[0xa4 - 0x5c];
    u32 mSpeciesKey;                            // 0xa4
    int mEvolvedKeysBegin;                       // 0xa8
    int mEvolvedKeysEnd;                         // 0xac
    unsigned char pad0b0[0xf4 - 0xb0];
    int mHead;                                  // 0xf4
    int mTail;                                  // 0xf8
    unsigned char pad0fc[0x108 - 0xfc];
    float mNumBabies;                           // 0x108
    unsigned char pad10c[0x15c - 0x10c];
    int mLocationState;                         // 0x15c
    void* mpNest;                               // 0x160
    RefObj* mCreaturePersonality;               // 0x164
    unsigned char pad168[0x190 - 0x168];
    u8 mbEnabled;                               // 0x190
    u8 mb191;                                   // 0x191
    unsigned char pad192[0x194 - 0x192];
    void* mpEggLayer;                           // 0x194
    unsigned char pad198[0x1e0 - 0x198];
    int* mValidLocations;                       // 0x1e0
    unsigned char pad1e4[0x1f4 - 0x1e4];
    u8* mLocationStatus;                        // 0x1f4
    u8* mLocationStatusEnd;                     // 0x1f8
    unsigned char pad1fc[0x20c - 0x1fc];
    Vec3 mWateringHolePosition;                 // 0x20c
};
}
namespace SP {
class cNearNoun
{
  public:
    const Vec3* GetPosition();                  // 0xc6acc0
    void SetEnabled();                          // 0xc6ad30

    unsigned char pad000[0x54];
    void** mpListBegin;                         // 0x54
    void** mpListEnd;                           // 0x58
    unsigned char pad05c[0x160 - 0x5c];
    void* mp160;                                // 0x160
    unsigned char pad164[0x190 - 0x164];
    u8  mb190;                                  // 0x190
    unsigned char pad191[0x218 - 0x191];
    u8  mb218;                                  // 0x218
};
}
namespace SP {
struct AnimalNoun
{
    unsigned char pad000[0xc0];
    void* mpC0;                                 // 0xc0
    unsigned char padC4[0x135 - 0xc4];
    u8  mb135;                                  // 0x135
    unsigned char pad136[0x590 - 0x136];
    float mF590;                                // 0x590
    unsigned char pad594[0xb20 - 0x594];
    u32 mSpeciesKey;                            // 0xb20
    unsigned char padB24[0xb4c - 0xb24];
    void* mpB4c;                                // 0xb4c
    unsigned char padB50[0xb58 - 0xb50];
    u32 mFlagsB58;                              // 0xb58
    unsigned char padB5c[0xb5e - 0xb5c];
    u8  mbB5e;                                  // 0xb5e

    ISpatial* spatialC0() { return reinterpret_cast<ISpatial*>(reinterpret_cast<char*>(this) + 0xc0); }
};
}
extern "C" bool  __cdecl FUN_00c8a550(void* so, void* modelWorld);     // cSpatialObject::LoadModel
// ---- items of slice s00c6a550 end

// ---- items of slice s00c6e710 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef          int   s32;
void* __cdecl SP_NounManager();                  // 0x00b3d300 SP::NounManager()
void* __cdecl FUN_00b3d300();                    // 0x00b3d300 (alias)
void* __cdecl FUN_00b3d350();                    // 0x00b3d350 (alias)
void* __cdecl FUN_00b20c60(void* self, u32 id);  // 0x00b20c60 cGameNounManager::CreateNoun
void  __cdecl FUN_00b225d0(void* self, void* noun); // 0x00b225d0 cGameNounManager::RemoveNoun
void* __cdecl FUN_00b20e40(void* self, void*, void*); // 0x00b20e40 cGameNounManager::CreateDebugNoun
void* __cdecl FUN_00b5f950(void* self, void*);    // 0x00b5f950 AutoRefCount::operator=<IWinText>
void  __cdecl FUN_00b06d90(void* self, u32 n);    // 0x00b06d90 RefVec::resize
void  __cdecl FUN_00babb70(void* end, u32 n, void* value); // 0x00babb70 vector::insert(end,n,value)
void* __cdecl FUN_00e25bd0(void* a, void* b);     // 0x00e25bd0 eastl::vector::erase
float __cdecl FUN_00c6a180(float x);              // 0x00c6a180 herd-scale helper
void  __cdecl FUN_00b18400(void* self, int, void*, void*, void*); // 0x00b18400 cGameData::Init
void* __cdecl FUN_00b9a750(u32 id, void* a, int b, int c, void* out); // 0x00b9a750 create-object helper
void* __cdecl FUN_00401090(u32 a, u32 b);         // 0x00401090 GetSetting9
void* __cdecl FUN_004e0050(void* self, u32 a);    // 0x004e0050 SpeciesManager::GetSpeciesArchetype
void* __cdecl FUN_00c6e200(void* self, void*, int); // 0x00c6e200 cHerd::UpdateFromArchetype
void  __cdecl FUN_004e3e10(void* self, void* value); // 0x004e3e10 vector<Key>::DoInsertValue
float __cdecl FUN_00b7ef70(void* self, void* pos);  // 0x00b7ef70 cPlanetModel::GetRadiusAt
extern u8    DAT_014718b8[4]; // axis-permutation table (bytes)
// ---- items of slice s00c6e710 end

// ---- items of slice s00c6b660 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  __fastcall FUN_00c6b5b0(void* ecxHerd);            // 0x00c6b5b0 SP::cHerd::FindWateringHole
extern "C" void  __cdecl FUN_00f47380(void* p);                     // 0x00f47380 operator delete
extern "C" float __cdecl FUN_00694fe0(void* out, const void* vec2); // 0x00694fe0 cTypedValueToStringT<Vector2>::Write
extern "C" void* __cdecl FUN_0093c5a0(void* out, int name, int n);  // 0x0093c5a0 EA::ConvertToString16
extern "C" void* __cdecl FUN_0093c6d0(void* out, const void* in);   // 0x0093c6d0 EA::ConvertToString16
extern "C" void  __cdecl FUN_0056e2d0(void* dst, const void* src);  // 0x0056e2d0 eastl::wstring copy ctor
extern "C" void  __cdecl FUN_00579a90(void* self, int n);           // 0x00579a90 eastl::wstring::range_initialize
extern "C" char  __cdecl FUN_00ac8050(void* ser, int nameChar, void* elem);   // 0x00ac8050 write list<ref>
extern "C" char  __cdecl FUN_00ae5530(void* ser, int nameChar, void* elem, const wchar_t* cls); // 0x00ae5530 write list<Key>
extern u8    gUnknownFlag;  // 0x015d8b55
namespace SP {
class RefObj_s00c6_b660
{
  public:
    virtual void AddRef();              // +0x00
    virtual void Release();             // +0x04
    virtual bool IsValid();             // +0x2c
};
}
namespace SP {
class ISpatial_s00c6_b660
{
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
    virtual const Vec3* GetPosition();          // +0x2c
};
}
namespace SP {
class cHerd_s00c6_b660
{
  public:
    cHerd_s00c6_b660();                             // 0x00c6c110
    ~cHerd_s00c6_b660();                            // 0x00c6bde0
    // 0x00c6b660
    float* GuardLocation(Vec3* out, int index);  // 0x00c6b660 (SP::cHerd::GuardLocation)
    // 0x00c6b8e0
    int ClaimEmptyGuardLocation(float unused, Vec3* out);
    // 0x00c6ba20
    void SetPosition(const Vec3* pos);  // 0x00c6ba20 (SP::cHerd::SetPosition)
    // 0x00c6bdc0
    Vec3* GetWateringHolePosition();  // 0x00c6bdc0 (SP::cHerd::GetWateringHolePosition)

    ISpatial_s00c6_b660* NestSpatial() { return reinterpret_cast<ISpatial_s00c6_b660*>(mpNest); }
    const Vec3* OwnPosition() { return reinterpret_cast<const Vec3*>(this); }

    unsigned char pad000[0x34];
    Vec3 mInitialPosition;               // 0x34
    unsigned char pad040[0x54 - 0x40];
    void** mpEggsBegin;                  // 0x54
    void** mpEggsEnd;                    // 0x58
    unsigned char pad05c[0x80 - 0x5c];
    int   mCurrentFeedingGrounds;        // 0x80  (= -1)
    u8    mb084;                         // 0x84
    u8    mbShouldEvolve;                // 0x85  (= 1)
    unsigned char pad086[0x94 - 0x86];
    float mDNAEvolutionThreshold;        // 0x94
    unsigned char pad098[0xa4 - 0x98];
    void* mpSpeciesProfile;              // 0xa4
    unsigned char pad0a8[0x108 - 0xa8];
    float mTerritoryRadius;              // 0x108
    int   mNumGuardsPerLocation;         // 0x10c
    int   mNumGuards;                    // 0x110  (= 1)
    float mGuardMinRadius;               // 0x114  (= 10.0f)
    float mGuardMaxRadius;               // 0x118  (= 15.0f)
    unsigned char pad11c[0x120 - 0x11c];
    int   mNumGuardLocations;            // 0x120
    int   mActivateBrainLevel;           // 0x124
    unsigned char pad128[0x130 - 0x128];
    unsigned char mGonzagoTimer130[0x20];// 0x130
    float mScaleMultiplier;              // 0x150
    float mHitpointOverride;             // 0x154
    float mDamageMultiplier;             // 0x158
    unsigned char pad15c[0x160 - 0x15c];
    void* mpNest;                        // 0x160
    RefObj_s00c6_b660* mpHerdMom;                   // 0x164
    unsigned char pad168[0x190 - 0x168];
    u8    mbExtinction;                  // 0x190
    u8    mbBestFriends;                 // 0x191
    u8    mbTransientHerd;               // 0x192
    void* mpEggLayer;                    // 0x194
    u8    mbEggsInNest;                  // 0x198
    unsigned char pad199[0x1a0 - 0x199];
    unsigned char mGonzagoTimer1a0[0x20];// 0x1a0
    unsigned char mChangeFeedingGrounds[0x20]; // 0x1c0
    int*  mValidLocationsBegin;          // 0x1e0
    int*  mValidLocationsEnd;            // 0x1e4
    int*  mValidLocationsCap;            // 0x1e8
    unsigned char pad1ec[0x1f4 - 0x1ec];
    u8*   mLocationStatusBegin;          // 0x1f4
    u8*   mLocationStatusEnd;            // 0x1f8
    u8*   mLocationStatusCap;            // 0x1fc
    unsigned char pad200[0x208 - 0x200];
    u8    mbCheckedForWateringHole;      // 0x208
    unsigned char pad209[0x20c - 0x209];
    Vec3  mWateringHolePosition;         // 0x20c
};  // namespace SP
}
// ---- items of slice s00c6b660 end

// ---- items of slice s0134d380 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace eastl {
 struct string8_s0134_d380; 
}
typedef eastl::string8_s0134_d380 string8_s0134_d380;
namespace Simulator {
class ISerializerReadStream;
}
namespace Simulator {
class ISerializerWriteStream;
}
namespace Simulator {
struct Attribute;
}
namespace Simulator {
typedef bool  (*ReadFunction_t)(ISerializerReadStream*, void*);
}
namespace Simulator {
typedef bool  (*WriteFunction_t)(ISerializerWriteStream*, void*);
}
namespace Simulator {
typedef void  (*ReadTextFunction_t)(const string8_s0134_d380&, void*);
}
namespace Simulator {
typedef void  (*WriteTextFunction_t)(char*, void*);
}
namespace Simulator {
typedef bool  (*ValidateFunction_t)();
}
namespace Simulator {
typedef bool  (*ToXmlFunction_t)(void*, const char*, int);
}
namespace Simulator {
typedef void* (*OffsetFunction_t)(Attribute*);
}
namespace Simulator {
typedef void  (*SetDefaultFunction_t)(Attribute*);
}
namespace Simulator {
void* DefaultOffset(Attribute* pAttr);   // 0x00692ca0: pAttr->pCurrentObject + pAttr->offset
}
namespace Simulator {
struct Attribute
{
    Attribute(const char* pName, uint32_t nID, uint32_t nOffset,
              ReadFunction_t pRead, WriteFunction_t pWrite,
              ReadTextFunction_t pReadText, WriteTextFunction_t pWriteText,
              ValidateFunction_t pValidate, ToXmlFunction_t pToXml,
              SetDefaultFunction_t pSetDefault = 0)
    {
        name = pName;
        id = nID;
        pCurrentObject = 0;
        setDefaultFunction = pSetDefault;
        offsetFunction = DefaultOffset;
        readFunction = pRead;
        writeFunction = pWrite;
        readTextFunction = pReadText;
        writeTextFunction = pWriteText;
        validateFunction = pValidate;
        toXmlFunction = pToXml;
        offset = nOffset;
    }

    /* 00h */ const char* name;
    /* 04h */ uint32_t id;
    /* 08h */ uint32_t offset;
    /* 0Ch */ int field_0C;   // not initialized
    /* 10h */ int field_10;   // not initialized
    /* 14h */ int field_14;   // not initialized
    /* 18h */ void* pCurrentObject;
    /* 1Ch */ SetDefaultFunction_t setDefaultFunction;
    /* 20h */ OffsetFunction_t offsetFunction;
    /* 24h */ ReadFunction_t readFunction;
    /* 28h */ WriteFunction_t writeFunction;
    /* 2Ch */ ReadTextFunction_t readTextFunction;
    /* 30h */ WriteTextFunction_t writeTextFunction;
    /* 34h */ ValidateFunction_t validateFunction;
    /* 38h */ ToXmlFunction_t toXmlFunction;
};
}
namespace Simulator {
struct Vec3Default { float x, y, z; };
}
namespace Simulator {
extern float sDNAEvolutionThresholdDefault;   // 0x01693e3c
}
namespace Simulator {
extern float sHerdDefaultVec3[3];             // 0x01693e40
}
namespace Simulator {
extern unsigned char sHerdDefaultVec3Guard;   // 0x01693e4c
}
namespace Simulator {
void SetDefault_00c6a0e0(Attribute* pAttr);  // 0x00c6a0e0
}
namespace Simulator {
void SetDefault_00c6ae30(Attribute* pAttr);  // 0x00c6ae30
}
namespace Simulator {
bool Read_00572810(ISerializerReadStream* pStream, void* pData);  // 0x00572810
}
namespace Simulator {
bool Read_00ac8750(ISerializerReadStream* pStream, void* pData);  // 0x00ac8750
}
namespace Simulator {
bool Read_00acdf10(ISerializerReadStream* pStream, void* pData);  // 0x00acdf10
}
namespace Simulator {
bool Read_00ae3430(ISerializerReadStream* pStream, void* pData);  // 0x00ae3430
}
namespace Simulator {
bool Read_00ae3470(ISerializerReadStream* pStream, void* pData);  // 0x00ae3470
}
namespace Simulator {
bool Read_00b20510(ISerializerReadStream* pStream, void* pData);  // 0x00b20510
}
namespace Simulator {
bool Read_00b6e3a0(ISerializerReadStream* pStream, void* pData);  // 0x00b6e3a0
}
namespace Simulator {
bool Read_00c41210(ISerializerReadStream* pStream, void* pData);  // 0x00c41210
}
namespace Simulator {
bool Read_00c6a080(ISerializerReadStream* pStream, void* pData);  // 0x00c6a080
}
namespace Simulator {
bool Read_00c6bce0(ISerializerReadStream* pStream, void* pData);  // 0x00c6bce0
}
namespace Simulator {
bool Read_00c6cd50(ISerializerReadStream* pStream, void* pData);  // 0x00c6cd50
}
namespace Simulator {
bool Read_00c6ce30(ISerializerReadStream* pStream, void* pData);  // 0x00c6ce30
}
namespace Simulator {
bool Read_00c95780(ISerializerReadStream* pStream, void* pData);  // 0x00c95780
}
namespace Simulator {
bool Write_00572840(ISerializerWriteStream* pStream, void* pData);  // 0x00572840
}
namespace Simulator {
bool Write_00ac8780(ISerializerWriteStream* pStream, void* pData);  // 0x00ac8780
}
namespace Simulator {
bool Write_00ac88c0(ISerializerWriteStream* pStream, void* pData);  // 0x00ac88c0
}
namespace Simulator {
bool Write_00ac88f0(ISerializerWriteStream* pStream, void* pData);  // 0x00ac88f0
}
namespace Simulator {
bool Write_00aca730(ISerializerWriteStream* pStream, void* pData);  // 0x00aca730
}
namespace Simulator {
bool Write_00ae3450(ISerializerWriteStream* pStream, void* pData);  // 0x00ae3450
}
namespace Simulator {
bool Write_00ae3490(ISerializerWriteStream* pStream, void* pData);  // 0x00ae3490
}
namespace Simulator {
bool Write_00bca960(ISerializerWriteStream* pStream, void* pData);  // 0x00bca960
}
namespace Simulator {
bool Write_00c40e80(ISerializerWriteStream* pStream, void* pData);  // 0x00c40e80
}
namespace Simulator {
bool Write_00c46470(ISerializerWriteStream* pStream, void* pData);  // 0x00c46470
}
namespace Simulator {
bool Write_00c6a0b0(ISerializerWriteStream* pStream, void* pData);  // 0x00c6a0b0
}
namespace Simulator {
bool Write_00c6adc0(ISerializerWriteStream* pStream, void* pData);  // 0x00c6adc0
}
namespace Simulator {
void ReadText_00692ff0(const string8_s0134_d380& text, void* pData);  // 0x00692ff0
}
namespace Simulator {
void ReadText_00693090(const string8_s0134_d380& text, void* pData);  // 0x00693090
}
namespace Simulator {
void ReadText_006930b0(const string8_s0134_d380& text, void* pData);  // 0x006930b0
}
namespace Simulator {
void ReadText_006930d0(const string8_s0134_d380& text, void* pData);  // 0x006930d0
}
namespace Simulator {
void ReadText_006930f0(const string8_s0134_d380& text, void* pData);  // 0x006930f0
}
namespace Simulator {
void ReadText_00693150(const string8_s0134_d380& text, void* pData);  // 0x00693150
}
namespace Simulator {
void ReadText_00c2e4e0(const string8_s0134_d380& text, void* pData);  // 0x00c2e4e0
}
namespace Simulator {
void WriteText_00692fb0(char* pBuffer, void* pData);  // 0x00692fb0
}
namespace Simulator {
void WriteText_00694ee0(char* pBuffer, void* pData);  // 0x00694ee0
}
namespace Simulator {
void WriteText_00694f00(char* pBuffer, void* pData);  // 0x00694f00
}
namespace Simulator {
void WriteText_00694fa0(char* pBuffer, void* pData);  // 0x00694fa0
}
namespace Simulator {
void WriteText_00694fc0(char* pBuffer, void* pData);  // 0x00694fc0
}
namespace Simulator {
void WriteText_00694fe0(char* pBuffer, void* pData);  // 0x00694fe0
}
namespace Simulator {
void WriteText_00695010(char* pBuffer, void* pData);  // 0x00695010
}
namespace Simulator {
void WriteText_00695080(char* pBuffer, void* pData);  // 0x00695080
}
namespace Simulator {
bool Validate_00ae3310();  // 0x00ae3310
}
namespace Simulator {
bool Validate_00b1fbf0();  // 0x00b1fbf0
}
namespace Simulator {
bool Validate_00b6f550();  // 0x00b6f550
}
namespace Simulator {
bool Validate_00b6f860();  // 0x00b6f860
}
namespace Simulator {
bool ToXml_0057cde0(void* pData, const char* pName, int depth);  // 0x0057cde0
}
namespace Simulator {
bool ToXml_0057ce00(void* pData, const char* pName, int depth);  // 0x0057ce00
}
namespace Simulator {
bool ToXml_00675ca0(void* pData, const char* pName, int depth);  // 0x00675ca0
}
namespace Simulator {
bool ToXml_00ac8050(void* pData, const char* pName, int depth);  // 0x00ac8050
}
namespace Simulator {
bool ToXml_00acbb80(void* pData, const char* pName, int depth);  // 0x00acbb80
}
namespace Simulator {
bool ToXml_00acbba0(void* pData, const char* pName, int depth);  // 0x00acbba0
}
namespace Simulator {
bool ToXml_00ae5720(void* pData, const char* pName, int depth);  // 0x00ae5720
}
namespace Simulator {
bool ToXml_00c41b00(void* pData, const char* pName, int depth);  // 0x00c41b00
}
namespace Simulator {
bool ToXml_00c6c0f0(void* pData, const char* pName, int depth);  // 0x00c6c0f0
}
namespace Simulator {
bool ToXml_00c6c390(void* pData, const char* pName, int depth);  // 0x00c6c390
}
namespace Simulator {
bool ToXml_00c6c4e0(void* pData, const char* pName, int depth);  // 0x00c6c4e0
}
namespace Simulator {
bool ToXml_00c6c630(void* pData, const char* pName, int depth);  // 0x00c6c630
}
namespace Simulator {
struct AttrStorage { char data[sizeof(Attribute)]; };
}
namespace Simulator {
AttrStorage cHerd_sAttributes[43];   // 0x01577bc8
}
// ---- items of slice s0134d380 end

// ---- items of slice s00c699a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Component_s00c6_99a0 {
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
virtual void v4c();
virtual void v50();
virtual void v54();
    virtual bool IsBlocked();  // slot 0x58
};
struct Object_s00c6_99a0 {
    char pad000[0xc0];
    Component_s00c6_99a0 mComponent;  // +0xc0
    char pad0c4[0xb20 - 0xc4];
    int mOwnerId;                     // +0xb20

    bool IsActive();  // 0x00c0b770
};
struct Target_s00c6_99a0 {
    char pad00[0xa4];
    int mOwnerId;  // +0xa4
};
struct Manager_s00c6_99a0 {
    Object_s00c6_99a0* GetCurrent();  // 0x00a1ad10
};
int IsRegistered_s00c6_99a0(Object_s00c6_99a0* obj);  // 0x00d99500
Manager_s00c6_99a0* GetManager_s00c6_99a0();          // 0x00d51660
// ---- items of slice s00c699a0 end

// ---- items of slice s00c69a00 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Base00_s00c6_9a00 {
    char pad00[0x34];
    void* Cast(unsigned int type);  // 0x00b18460
};
struct Base34_s00c6_9a00 {
    char pad00[0x108 - 0x34];
    void* Cast(unsigned int type);  // 0x00c884f0
};
struct Base108_s00c6_9a00 {
    char pad00[0x120 - 0x108];
};
struct Base120_s00c6_9a00 {
    char pad00[4];
    void* Cast(unsigned int type);  // 0x00bfc380
};
struct Object_s00c6_9a00 : Base00_s00c6_9a00, Base34_s00c6_9a00, Base108_s00c6_9a00, Base120_s00c6_9a00 {
    void* Cast(unsigned int type);
};
// ---- items of slice s00c69a00 end

// ---- items of slice s00c6a270 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct IRefObj_s00c6_a270 {
    virtual int AddRef();
    virtual int Release();
};
struct RefPtr_s00c6_a270 {
    IRefObj_s00c6_a270* mp;

    RefPtr_s00c6_a270() : mp(0) {}
};
struct Member1f8_s00c6_a270 {
    char pad00[0x20];
    Member1f8_s00c6_a270();  // 0x00b63890
};
struct Base00a_s00c6_a270 { virtual void v00(); };
struct Base00b_s00c6_a270 { virtual void v00(); };
struct Base00_s00c6_a270 : Base00a_s00c6_a270, Base00b_s00c6_a270 {
    char pad08[0x34 - 8];
    Base00_s00c6_a270();  // 0x00b18660
};
struct ResourceKey_s00c6_a270 {
    unsigned int mInstanceID;
    unsigned int mTypeID;
    unsigned int mGroupID;

    ResourceKey_s00c6_a270(unsigned int instance, unsigned int type, unsigned int group)
        : mInstanceID(instance), mTypeID(type), mGroupID(group) {}
};
struct Base34_s00c6_a270 {
    virtual void v00();
    char pad38[0x88 - 0x38];
    int m88;               // +0x88
    char pad8c[0xa5 - 0x8c];
    bool ma5;              // +0xa5
    char pada6[0xc4 - 0xa6];
    ResourceKey_s00c6_a270 mKey;  // +0xc4
    char padd0[0x108 - 0xd0];
    Base34_s00c6_a270();  // 0x00c89630 (leaves mKey to the derived class)
};
struct Base108_s00c6_a270 {
    virtual void v00();
    char pad04[0x120 - 0x10c];
    Base108_s00c6_a270();  // 0x00ac03d0
};
struct Base120_s00c6_a270 {
    virtual void v00();
    char pad04[0x1e8 - 0x124];
    Base120_s00c6_a270();  // 0x00bfd4e0
};
struct Object_s00c6_a270 : Base00_s00c6_a270, Base34_s00c6_a270, Base108_s00c6_a270, Base120_s00c6_a270 {
    int m1e8;                       // +0x1e8
    bool m1ec;                      // +0x1ec
    int m1f0;                       // +0x1f0
    RefPtr_s00c6_a270 mpRef1f4;     // +0x1f4
    Member1f8_s00c6_a270 m1f8;      // +0x1f8
    RefPtr_s00c6_a270 mpRef218;     // +0x218
    RefPtr_s00c6_a270 mpRef21c;     // +0x21c
    float m220;                     // +0x220

    virtual void v00();
    Object_s00c6_a270();
};
// ---- items of slice s00c6a270 end

// ---- items of slice s00c6a430 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct IRefObj_s00c6_a430 {
    virtual int AddRef();
    virtual int Release();
};
struct RefPtr_s00c6_a430 {
    IRefObj_s00c6_a430* mp;

    ~RefPtr_s00c6_a430() { if (mp) mp->Release(); }
};
struct Member1f8_s00c6_a430 {
    char pad00[0x20];
    ~Member1f8_s00c6_a430();  // 0x00b638b0
};
struct Base00a_s00c6_a430 { virtual void v00(); };
struct Base00b_s00c6_a430 { virtual void v00(); };
struct Base00_s00c6_a430 : Base00a_s00c6_a430, Base00b_s00c6_a430 {
    char pad08[0x34 - 8];
    ~Base00_s00c6_a430();  // 0x00b184c0
};
struct Base34_s00c6_a430 {
    virtual void v00();
    char pad04[0x108 - 0x38];
    ~Base34_s00c6_a430();  // 0x00c8a420
};
struct Base108_s00c6_a430 {
    virtual void v00();
    char pad04[0x120 - 0x10c];
    ~Base108_s00c6_a430();  // 0x00ac0520
};
struct Base120_s00c6_a430 {
    virtual void v00();
    char pad04[0x1f4 - 0x124];
    ~Base120_s00c6_a430();  // 0x00bfcd00
};
struct Object_s00c6_a430 : Base00_s00c6_a430, Base34_s00c6_a430, Base108_s00c6_a430, Base120_s00c6_a430 {
    RefPtr_s00c6_a430 mpRef1f4;     // +0x1f4
    Member1f8_s00c6_a430 m1f8;      // +0x1f8
    RefPtr_s00c6_a430 mpRef218;     // +0x218
    RefPtr_s00c6_a430 mpRef21c;     // +0x21c

    virtual void v00();
    ~Object_s00c6_a430();
};
// ---- items of slice s00c6a430 end

// ---- items of slice s00c6a4d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
class RefObj_c6a4d0
{
  public:
    virtual void AddRef();   // +0x00
    virtual void Release();  // +0x04
};
class SpatialObject_c6a4d0
{
  public:
    void Clear();            // 0x00c8b2e0

  private:
    unsigned char mBytes[0xd4];
};
class InteractionTarget_c6a4d0
{
  public:
    void Clear();            // 0x00ac0450

  private:
    unsigned char mBytes[0x18];
};
class Combatant_c6a4d0
{
  public:
    void ReleaseSlots();     // 0x00bfc720

  private:
    unsigned char mBytes[0xc8];
};
class Egg_c6a4d0
{
  public:
    void Shutdown();

  private:
    unsigned char beforeRef2c[0x2c];
    RefObj_c6a4d0* mpRef2c;                              // +0x2c
    unsigned char afterRef2c[0x34 - 0x30];               // cGameData retail size 0x34
    SpatialObject_c6a4d0 mSpatialObject;                 // +0x34
    InteractionTarget_c6a4d0 mInteractionTarget;         // +0x108
    Combatant_c6a4d0 mCombatant;                         // +0x120
    unsigned char beforeHerd[0x1f4 - 0x120 - 0xc8];
    RefObj_c6a4d0* mpHerd;                               // +0x1f4
    unsigned char beforeToHatch[0x218 - 0x1f8];
    RefObj_c6a4d0* mpToHatch;                            // +0x218
    RefObj_c6a4d0* mpWhoIsInteractingWithMe;             // +0x21c
};
// ---- items of slice s00c6a4d0 end

// ---- items of slice s01347830 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace eastl {
 struct string8_s0134_7830; 
}
typedef eastl::string8_s0134_7830 string8_s0134_7830;
namespace Simulator {
struct Attribute_s0134_7830;
}
namespace Simulator {
typedef void  (*ReadTextFunction_t_s0134_7830)(const string8_s0134_7830&, void*);
}
namespace Simulator {
typedef void* (*OffsetFunction_t_s0134_7830)(Attribute_s0134_7830*);
}
namespace Simulator {
typedef void  (*SetDefaultFunction_t_s0134_7830)(Attribute_s0134_7830*);
}
namespace Simulator {
void* DefaultOffset(Attribute_s0134_7830* pAttr);   // 0x00692ca0: pAttr->pCurrentObject + pAttr->offset
}
namespace Simulator {
void* StaticOffset(Attribute_s0134_7830* pAttr);    // 0x011874d0: (void*)pAttr->offset (class statics)
}
namespace Simulator {
struct Attribute_s0134_7830
{
    // Member attribute: offset is relative to the current object.
    Attribute_s0134_7830(const char* pName, uint32_t nID, uint32_t nOffset,
              ReadFunction_t pRead, WriteFunction_t pWrite,
              ReadTextFunction_t_s0134_7830 pReadText, WriteTextFunction_t pWriteText,
              ValidateFunction_t pValidate, ToXmlFunction_t pToXml,
              SetDefaultFunction_t_s0134_7830 pSetDefault = 0)
    {
        name = pName;
        id = nID;
        pCurrentObject = 0;
        setDefaultFunction = pSetDefault;
        offsetFunction = DefaultOffset;
        readFunction = pRead;
        writeFunction = pWrite;
        readTextFunction = pReadText;
        writeTextFunction = pWriteText;
        validateFunction = pValidate;
        toXmlFunction = pToXml;
        offset = nOffset;
    }

    // Static attribute: the offset field holds the static's address; no ToXml callback.
    Attribute_s0134_7830(const char* pName, uint32_t nID, void* pStatic,
              ReadFunction_t pRead, WriteFunction_t pWrite,
              ReadTextFunction_t_s0134_7830 pReadText, WriteTextFunction_t pWriteText,
              ValidateFunction_t pValidate)
    {
        name = pName;
        id = nID;
        pCurrentObject = 0;
        setDefaultFunction = 0;
        offsetFunction = StaticOffset;
        readFunction = pRead;
        writeFunction = pWrite;
        readTextFunction = pReadText;
        writeTextFunction = pWriteText;
        validateFunction = pValidate;
        toXmlFunction = 0;
        offset = (uint32_t)pStatic;
    }

    /* 00h */ const char* name;
    /* 04h */ uint32_t id;
    /* 08h */ uint32_t offset;
    /* 0Ch */ int field_0C;   // not initialized
    /* 10h */ int field_10;   // not initialized
    /* 14h */ int field_14;   // not initialized
    /* 18h */ void* pCurrentObject;
    /* 1Ch */ SetDefaultFunction_t_s0134_7830 setDefaultFunction;
    /* 20h */ OffsetFunction_t_s0134_7830 offsetFunction;
    /* 24h */ ReadFunction_t readFunction;
    /* 28h */ WriteFunction_t writeFunction;
    /* 2Ch */ ReadTextFunction_t_s0134_7830 readTextFunction;
    /* 30h */ WriteTextFunction_t writeTextFunction;
    /* 34h */ ValidateFunction_t validateFunction;
    /* 38h */ ToXmlFunction_t toXmlFunction;
};
}
namespace Simulator {
template<typename T> bool Read4(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
template<typename T> bool Write4(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
template<typename T> void ReadTextInt(const string8_s0134_7830& text, void* pData);
}
namespace Simulator {
template<typename T> bool AlwaysValid();
}
namespace Simulator {
bool Read_00ac8750_s0134_7830(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00ac8780_s0134_7830(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00ac88f0_s0134_7830(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
void ReadText_00692ff0_s0134_7830(const string8_s0134_7830& text, void* pData);
}
namespace Simulator {
void ReadText_006930b0_s0134_7830(const string8_s0134_7830& text, void* pData);
}
namespace Simulator {
void ReadText_00c2e4e0(const string8_s0134_7830& text, void* pData);
}
namespace Simulator {
void WriteText_00694ee0_s0134_7830(char* pBuffer, void* pData);
}
namespace Simulator {
void WriteText_00694fa0_s0134_7830(char* pBuffer, void* pData);
}
namespace Simulator {
void WriteText_00694fc0_s0134_7830(char* pBuffer, void* pData);
}
namespace Simulator {
bool ToXml_0057cde0_s0134_7830(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_0057ce00_s0134_7830(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00acbb80_s0134_7830(void* pData, const char* pName, int depth);
}
namespace Simulator {
struct AttrSlot { uint32_t d[15]; };
}
namespace Simulator {
#define INT_ATTR   Read4<int>, Write4<int>, ReadText_00692ff0_s0134_7830, WriteText_00694ee0_s0134_7830, AlwaysValid<int>, ToXml_0057cde0_s0134_7830
}
namespace Simulator {
#define FLOAT_ATTR Read4<float>, Write_00ac88f0_s0134_7830, ReadText_006930b0_s0134_7830, WriteText_00694fc0_s0134_7830, AlwaysValid<float>, ToXml_00acbb80_s0134_7830
}
namespace Simulator {
#define BOOL_ATTR  Read_00ac8750_s0134_7830, Write_00ac8780_s0134_7830, ReadTextInt<bool>, WriteText_00694fa0_s0134_7830, AlwaysValid<bool>, ToXml_0057ce00_s0134_7830
}
namespace Simulator {
bool Read_00b20540(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00b02540(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
extern AttrSlot cEgg_sAttributes[6];         // 0x015778f0
}
namespace Simulator {
#define ADD_EGG(IDX, ...)   { Attribute_s0134_7830 a(__VA_ARGS__); *(Attribute_s0134_7830*)&cEgg_sAttributes[IDX] = a; }
}
// ---- items of slice s01347830 end

// @ 0x00c699a0
int CanTarget_s00c6_99a0(Object_s00c6_99a0* obj, Target_s00c6_99a0* target)
{
    if (IsRegistered_s00c6_99a0(obj) && obj->IsActive() && !obj->mComponent.IsBlocked() &&
        obj->mOwnerId == target->mOwnerId && GetManager_s00c6_99a0()->GetCurrent() != obj)
        return 1;
    return 0;
}

// @ 0x00c69a00
void* Object_s00c6_9a00::Cast(unsigned int type)
{
    if (type == 0xee3f516e || type == 0x02a0349a)
        return this;
    if (type != 0x102a041a) {
        if (void* p = Base00_s00c6_9a00::Cast(type))
            return p;
        if (void* p = Base120_s00c6_9a00::Cast(type))
            return p;
        return Base34_s00c6_9a00::Cast(type);
    }
    return static_cast<Base108_s00c6_9a00*>(this);
}

// @ 0x00c69bc0
u32 __stdcall SP_CreatePlanetAndSnap(u32 a, u32 b)
{
    cPlanetModel* model = (cPlanetModel*)SP_PlanetModel(a, b, 0);
    model->SnapB();
    return a;
}

// @ 0x00c69db0
void* cObject::Cast(int type)
{
    if (type == (int)0xee3f516e)
        return this;
    if (type == (int)0x52aa6117)
        return this;
    return ((cObjectBase*)this)->CastBase(type);
}

// @ 0x00c69e30
int SP_ObjectCheck(void* p)
{
    if (p != 0) {
        if (VT_2C_0(p))
            return 1;
    }
    return 0;
}

// @ 0x00c69ff0
void cHerd::SetTarget(const cVec3* v)
{
    mFlag208 = 1;
    mTarget20c = *v;
}

// @ 0x00c6a030
bool cHerd::ShouldActivate()
{
    if (mState15c == 9) {
        if (GetCurrentGameMode() == 0x01654c01u) {
            cCreatureModeStrategy* strategy = GetCreatureModeStrategy(0x7aee5ee7);
            return strategy->HasCreatureTutorialOccurred() == false;
        }
        return false;
    }
    return true;
}

// @ 0x00c6a270
Object_s00c6_a270::Object_s00c6_a270()
: m1e8(0), m1ec(true), m1f0(10000), m220(1.0f)
{
    m88 = 5;
    mKey = ResourceKey_s00c6_a270(0xa76cd528, 0, 0);
    ma5 = false;
}

// @ 0x00c6a430
Object_s00c6_a430::~Object_s00c6_a430()
{
}

// @ 0x00c6a4d0
void Egg_c6a4d0::Shutdown()
{
    if (RefObj_c6a4d0* p = mpHerd) {
        mpHerd = 0;
        p->Release();
    }
    if (RefObj_c6a4d0* p = mpToHatch) {
        mpToHatch = 0;
        p->Release();
    }
    if (RefObj_c6a4d0* p = mpWhoIsInteractingWithMe) {
        mpWhoIsInteractingWithMe = 0;
        p->Release();
    }
    if (RefObj_c6a4d0* p = mpRef2c) {
        mpRef2c = 0;
        p->Release();
    }
    mSpatialObject.Clear();
    mCombatant.ReleaseSlots();
    mInteractionTarget.Clear();
}

// @ 0x00c6a550
namespace SP {
bool SP::cEgg_s00c6_a550::Write(SP::IOStream* stream)
{
    IWriter* __restrict writer = static_cast<IWriter*>(stream->GetWriter());
    u32 tag = 0x2a0349a;
    void* sink = writer->GetSink();
    EA::IO::WriteUint32(sink, &tag, 1, 0);
    bool ok = reinterpret_cast<ThisStubs*>(this)->WriteGameData(stream)
        && reinterpret_cast<ThisStubs*>((char*)this + 0x34)->WriteSpatial(stream)
        && reinterpret_cast<ThisStubs*>((char*)this + 0x120)->WriteCombatant(stream);
    if (mpHerd != 0 && mpHerd->IsValid()) {
        RefObj* previous = mpHerd;
        if (previous != 0) {
            mpHerd = 0;
            previous->Release();
        }
    }
    if (mpToHatch != 0 && mpToHatch->IsValid()) {
        RefObj* previous = mpToHatch;
        if (previous != 0) {
            mpToHatch = 0;
            previous->Release();
        }
    }
    SP::cVarListSerializer ser(this, &gEggSerializerList,
        SP::cVarListSerializer::kSignature);
    if (ok && ser.Serialize(*reinterpret_cast<SP::cIObjectDatabaseOStream*>(stream)))
        return true;
    return false;
}
}  // namespace SP

// @ 0x00c6a670
namespace SP {
void SP::cEgg_s00c6_a550::SetState(SP::cEgg_s00c6_a550::EggState state)
{
    RefObj* herd = mpHerd;
    mState = state;
    effectShouldUpdate = 1;
    if (herd)
        *(u8*)((char*)herd + 0xfc) = 1;
    if (state != kWell)
        FUN_00c6a100(this);
    if (state == kBroken || state == kHatched) {
        ((cSPTimerStub*)mBrokenTimer)->Restart();
        FUN_00b530e0((char*)this + 0x34, 0);
    }
    if (state == kBroken)
        mCombatDamageState = 2;
}
}  // namespace SP

// @ 0x00c6a6e0
namespace SP {
bool SP::cEgg_s00c6_a550::StateStep()
{
    switch (mState) {
    case kWell:
    case kLaid:
        SetState(kCrack1);
        return mState == kBroken;
    case kCrack1:
        SetState(kCrack2);
        return mState == kBroken;
    case kCrack2:
        SetState(kBroken);
        return mState == kBroken;
    default:
        return 0;
    }
}
}  // namespace SP

// @ 0x00c6a7f0
namespace SP {
void __fastcall FUN_00c6a7f0(void* ecx_this, void* edx, const float* ext, int flag)
{
    float e[6];
    e[0] = ext[0];
    e[1] = ext[1];
    e[2] = 0.0f;
    e[3] = ext[3];
    e[4] = ext[4];
    e[5] = (float)fabs(ext[2]) + ext[5];
    ((void*(__thiscall*)(void*, const void*, int))FUN_00c89160)(ecx_this, e, flag);
    *(float*)((char*)ecx_this + 0x5c) = *(float*)((char*)ecx_this + 0x4c) * gHalf;
}
}  // namespace SP

// @ 0x00c6a870
namespace SP {
SP::cNest_s00c6_a550::cNest_s00c6_a550()
{
    ((ThisStubs*)this)->A();                          // cGameData ctor
    ((ThisStubs*)((char*)this + 0x34))->B();          // cSpatialObject ctor
    ((ThisStubs*)((char*)this + 0x108))->C();         // cInteractionTarget ctor
    mbShowPlacement = 0;
    mp124 = 0;
    *(void**)this = (void*)g_1471ba0;
    *(void**)((char*)this + 4) = (void*)g_1471b8c;
    *(void**)((char*)this + 0x34) = (void*)g_1471ac8;
    *(void**)((char*)this + 0x108) = (void*)g_1471aac;
    _ReadWriteBarrier();
    mpOwner128 = 0;
    mpFootprint12c = 0;
}
}  // namespace SP

// @ 0x00c6a970
namespace SP {
SP::cNest_s00c6_a550::~cNest_s00c6_a550()
{
    *(void**)this = (void*)g_1471ba0;
    *(void**)((char*)this + 4) = (void*)g_1471b8c;
    *(void**)((char*)this + 0x34) = (void*)g_1471ac8;
    *(void**)((char*)this + 0x108) = (void*)g_1471aac;
    _ReadWriteBarrier();
    if (mpOwner128)
        mpOwner128->Release();
    ((ThisStubs*)((char*)this + 0x108))->D();         // cInteractionTarget dtor-ish
    ((ThisStubs*)((char*)this + 0x34))->E();          // cSpatialObject dtor-ish
    ((ThisStubs*)this)->F();                          // cGameData dtor
}
}  // namespace SP

// @ 0x00c6a9c0
namespace SP {
void SP::cNest_s00c6_a550::RemoveOwner()
{
    if (mpOwner128) {
        RefObj* o = mpOwner128;
        mpOwner128 = 0;
        o->Release();
    }
    ((ThisStubs*)((char*)this + 0x108))->G();         // cInteractionTarget clear
    if (mpOwner2c) {
        RefObj* o = mpOwner2c;
        mpOwner2c = 0;
        o->Release();
    }
    ((ThisStubs*)((char*)this + 0x34))->H();          // cSpatialObject clear
}
}  // namespace SP

// @ 0x00c6aa10
namespace SP {
u8 __fastcall FUN_00c6aa10(void* ecx_this, void* edx)
{
    void* h = *(void**)((char*)ecx_this + 0xf4);
    if (h)
        return *(u8*)((char*)h + 0x84);
    return 0;
}
}  // namespace SP

// @ 0x00c6aa50
namespace SP {
bool SP::cNest_s00c6_a550::CanSpawn()
{
    cHerd_s00c6_a550* h = (cHerd_s00c6_a550*)mpOwner128;
    int prof = (int)((cSpeciesMgr*)FUN_00401090())->GetAvatarProfile();
    if (h->mSpeciesKey != (u32)prof && !((cHerd_s00c6_a550*)mpOwner128)->mb191 &&
        !((cHerd_s00c6_a550*)mpOwner128)->mbEnabled) {
        void* p = FUN_00b3d4c0((char*)((cHerd_s00c6_a550*)mpOwner128) + 0x98, 0, 0);
        if (((int(__thiscall*)(void*))FUN_00ba3f90)(p) != 4)
            return false;
    }
    return true;
}
}  // namespace SP

// @ 0x00c6aab0
namespace SP {
void SP::cNest_s00c6_a550::MoveNest(const Vec3& pos)
{
    ISpatial* sp = Spatial();
    const Vec3* cur = sp->GetPosition();
    if (cur->x == pos.x && cur->y == pos.y && cur->z == pos.z)
        return;
    if (mpFootprint12c) {
        void* planet = PlanetModel();
        if (planet && *(void**)((char*)planet + 0x24)) {
            void* pm = *(void**)((char*)PlanetModel() + 0x24);
            (*(void(__thiscall**)(void*, void*, int))(*(char**)pm + 0x58))(pm, mpFootprint12c, 0);
            mpFootprint12c = 0;
        }
    }
    Vec3 surfPos;
    FUN_00b815a0(PlanetModel(), &surfPos, &pos);
    sp->SetPosition(&surfPos);
    Quat orient;
    FUN_00b7f190(PlanetModel(), &orient, sp->GetPosition());
    sp->SetOrientation(&orient);
    mbShowPlacement = 1;
}
}  // namespace SP

// 0x00c6ab90 (byte-exact lifted version: match/slices/s00c6ab90/s00c6ab90.cpp)
namespace SP {
void SP::cNest_s00c6_a550::AddFootprint()
{
    if (mpFootprint12c != 0)
        return;
    void* o = mp0d0;
    if (!o || !*(void**)((char*)o + 0x90))
        return;
    void* planet = PlanetModel();
    if (*(void**)((char*)planet + 0x24)) {
        void* pm = *(void**)((char*)PlanetModel() + 0x24);
        void* arg = *(void**)((char*)mp0d0 + 0x90);
        int f = (*(int(__thiscall**)(void*, void*, void*))(*(char**)pm + 0x54))(pm, (char*)mp0d0 + 8, arg);
        mpFootprint12c = (void*)f;
    }
    void* tm = TerraformingManager();
    if (tm)
        ((ThisStubs*)tm)->I();                        // TerraformingManager footstep
}
}  // namespace SP

// @ 0x00c6abf0
namespace SP {
void* SP::cHerd_s00c6_a550::GetProfileForGeneration(unsigned gen)
{
    void* profile = 0;
    unsigned count = (unsigned)((mEvolvedKeysEnd - mEvolvedKeysBegin) / 0xc);
    if (gen < count) {
        _ReadWriteBarrier();
        const void* key = (const void*)(mEvolvedKeysBegin + gen * 0xc);
        profile = ((cSpeciesMgr*)FUN_00401090())->GetProfile(key);
    }
    return profile;
}
}

// @ 0x00c6ac40
namespace SP {
bool SP::cHerd_s00c6_a550::UnbrokenEggsInNest()
{
    int n = (int)(mLocationStatusEnd - mLocationStatus);
    if (n <= 0)
        return false;
    u8* base = mLocationStatus;
    for (int i = 0; i < n; ++i) {
        if (base[i] == 0) {
            int v = mValidLocations[i];
            if (v == 1 || v == 2)
                return true;
        }
    }
    return false;
}
}  // namespace SP

// @ 0x00c6ac90
namespace SP {
int SP::cHerd_s00c6_a550::ClearLocationStatus(int i)
{
    if (i >= 0 && i < mLocationStatusEnd - mLocationStatus)
        mLocationStatus[i] = 0;
    return i;
}
}  // namespace SP

// @ 0x00c6acc0
namespace SP {
const SP::Vec3* SP::cNearNoun::GetPosition()
{
    if (mp160 != 0) {
        ISpatial* sp = (ISpatial*)((char*)mp160 + 0x34);
        return sp->GetPosition();
    }
    return (const Vec3*)((char*)this + 0x34);
}
}  // namespace SP

// @ 0x00c6ace0
namespace SP {
void SP::cHerd_s00c6_a550::SetEnabled(u8 on)
{
    u8* self = (u8*)this;
    self[0x218] = on;
    if (mpNest)
        *(u8*)((char*)mpNest + 0xa9) = on;
    if (on) {
        void** it = mpListBegin;
        void** end = mpListEnd;
        while (it != end)
            *(u8*)((char*)*it++ + 0x1ec) = 1;
    }
}
}  // namespace SP

// @ 0x00c6ad30
namespace SP {
void SP::cNearNoun::SetEnabled()
{
    if (mb190 == 0) {
        mb190 = 1;
        if (mp160)
            *(u8*)((char*)mp160 + 0x120) = 1;
    }
}
}  // namespace SP

// @ 0x00c6ad60
namespace SP {
void __fastcall FUN_00c6ad60(void* ecx_this, void* edx)
{
    cHerd_s00c6_a550* self = (cHerd_s00c6_a550*)ecx_this;
    void* h = (void*)self->mSpeciesKey;
    if (!h)
        return;
    if (self->mLocationState == 0 && *(float*)((char*)h + 0x590) > gZeroF && self->mpNest != 0) {
        self->mLocationState = 4;
        return;
    }
    if (self->mLocationState == 4) {
        float f = *(float*)((char*)h + 0x590);
        if (gEpsilon > f)
            self->mLocationState = 0;
    }
}
}  // namespace SP

// @ 0x00c6adc0
namespace SP {
void __cdecl FUN_00c6adc0(void* obj, void** vec)
{
    int count = (int)((char*)vec[1] - (char*)vec[0]) / 0xc;
    IOStream* stream = (IOStream*)obj;
    IWriter* writer = (IWriter*)stream->GetWriter();
    EA::IO::WriteUint32(writer->GetSink(), &count, 1, 0);
    for (void* p = vec[0]; p != vec[1]; p = (char*)p + 0xc)
        FUN_00ae2e40(obj, p);
    (*(void(__thiscall**)(void*))(*(char**)obj + 0x1c))(obj);
}
}  // namespace SP

// @ 0x00c6ae30
namespace SP {
void __cdecl FUN_00c6ae30(void* obj)
{
    struct Cb { char pad[0x20]; u32* (__cdecl* fn)(void*); };
    u32* out = ((Cb*)obj)->fn(obj);
    if ((gViewerGuard & 1) == 0)
        gViewerGuard |= 1;
    out[0] = gViewerData[0];
    out[1] = gViewerData[1];
    out[2] = gViewerData[2];
}
}  // namespace SP

// @ 0x00c6ae70
namespace SP {
void** __cdecl FUN_00c6ae70(void** first, void** last, void** out, char (__cdecl* pred)(void*))
{
    if (first == last)
        return out;
    do {
        if (!pred(*first)) {
            void* src = *first;
            void* dst = *out;
            if (src != dst) {
                if (src)
                    (*(void(__thiscall**)(void*))(*(char**)src))(src);
                *out = src;
                if (dst)
                    (*(void(__thiscall**)(void*))(*(char**)dst + 4))(dst);
            }
            ++out;
        }
        ++first;
    } while (first != last);
    return out;
}
}  // namespace SP

// @ 0x00c6af40
namespace SP {
int __cdecl FUN_00c6af40(AnimalNoun* a, void* herdPtr)
{
    cHerd_s00c6_a550* herd = (cHerd_s00c6_a550*)herdPtr;
    if (a && !a->mbB5e && ((bool(__thiscall*)(void*))FUN_00c0b770)(a)
        && !(bool)((a->mFlagsB58 >> 8) & 1) && a->mSpeciesKey == herd->mSpeciesKey) {
        if ((bool)((a->mFlagsB58 >> 9) & 1)) {
            const Vec3* p1 = ((cNearNoun*)((void*(__thiscall*)(void*))FUN_00c04590)(a))->GetPosition();
            const Vec3* p2 = a->spatialC0()->GetPosition();
            float dx = p2->x - p1->x;
            float dy = p2->y - p1->y;
            float dz = p2->z - p1->z;
            float d2 = dx * dx;
            d2 += dy * dy;
            d2 += dz * dz;
            if (!(d2 < gFiftyF * gFiftyF))
                return 0;
        }
        return 1;
    }
    return 0;
}
}  // namespace SP

// @ 0x00c6b040
namespace SP {
void SP::cEgg_s00c6_a550::Update(int dt)
{
    if (mTimeToHatch <= 0)
        return;
    if (mTimeToHatch == 0x7fffffff)
        return;
    if (mpHerd && *(u8*)((char*)mpHerd + 0x190))
        return;
    int remaining = mTimeToHatch - dt;
    mTimeToHatch = remaining < 0 ? 0 : remaining;
    if (mTimeToHatch != 0)
        return;

    mState = kHatched;
    effectShouldUpdate = 1;
    if (mpHerd)
        *(u8*)((char*)mpHerd + 0xfc) = 1;
    FUN_00c6a100(this);
    ((cSPTimerStub*)mBrokenTimer)->Restart();
    FUN_00b530e0((char*)this + 0x34, 0);

    if (mpToHatch) {
        void* planet = PlanetModel();
        ISpatial* sp = Spatial();
        const Vec3* pos = sp->GetPosition();
        Vec3 v;
        v.x = pos->x;
        v.y = pos->y;
        v.z = pos->z;
        void* app = FUN_0067dd10();
        void* mgr = (*(void*(__thiscall**)(void*))(*(char**)app + 0x50))(app);
        void* viewer = (*(void*(__thiscall**)(void*))(*(char**)mgr + 0x1c))(mgr);
        Vec3 cam;
        cam.x = gViewerOrigin[0];
        cam.y = gViewerOrigin[1];
        cam.z = gViewerOrigin[2];
        if (viewer) {
            float zero = 0.0f;
            FUN_007c3d30(viewer, &cam, &zero, &zero, &zero);
        }
        void* node = FUN_00d51660();
        int parent = (*(int(__thiscall**)(void*))(*(char**)node + 0x1c))(node);
        Quat orient;
        if (parent == 0) {
            Vec3 dir;
            dir.x = cam.x - v.x;
            dir.y = cam.y - v.y;
            dir.z = cam.z - v.z;
            Vec3 n;
            FUN_00449c20(&n, &dir);
            *(Quat*)&orient = *(Quat*)FUN_00b7f250(planet, &orient, &v, &n);
        } else {
            ISpatial* isp = (ISpatial*)((char*)parent + 0xc0);
            const Vec3* ip = isp->GetPosition();
            Vec3 dir;
            dir.x = ip->x - v.x;
            dir.y = ip->y - v.y;
            dir.z = ip->z - v.z;
            Vec3 n;
            FUN_00449c20(&n, &dir);
            *(Quat*)&orient = *(Quat*)FUN_00b7f250(planet, &orient, &v, &n);
        }
        void* hatch = mpToHatch;
        ISpatial* tgt = (ISpatial*)((char*)hatch + 0xc0);
        (*(void(__thiscall**)(ISpatial*, const Vec3*, const Quat*))(*(char**)tgt + 0x44))(tgt, &v, &orient);
        *(u32*)((char*)hatch + 0xb58) &= ~0x800;
        *(u8*)((char*)hatch + 0x135) = 1;
        FUN_00bc97f0(0, 0x1000000, gFiveF, 0);
        return;
    }

    void* herd = mpHerd;
    u32 key = *(u32*)((char*)herd + 0xa4);
    const Vec3* pos = Spatial()->GetPosition();
    void* egg = FUN_00c099e0((void*)pos, 0, 0, (int)herd, key);
    (void)egg;
    FUN_00bc97f0(0, 0x1000000, gFiveF, 0);
}
}  // namespace SP

// @ 0x00c6b350
namespace SP {
void __fastcall FUN_00c6b350(void* ecx_this, void* edx, int a1, int a2, int a3, int a4, int a5)
{
    void* egg = (char*)ecx_this - 0x120;
    if (((cEgg_s00c6_a550*)egg)->StateStep() != 0)
        *(int*)((char*)ecx_this + 0x34) = 2;
}
}  // namespace SP

// @ 0x00c6b390
namespace SP {
void* SP::cNest_s00c6_a550::AsInterface(int id)
{
    if (id == 0x40ce1b1) {
        void* avatar = ((void*(__thiscall*)(void*))FUN_00b1fdb0)(NounManager());
        if (avatar) {
            int mine = mpOwner128 ? (int)((cHerd_s00c6_a550*)mpOwner128)->mSpeciesKey : 0;
            if (mine == (int)((void*(__thiscall*)(void*))FUN_00c0bbd0)(avatar))
                return this;
        }
        return 0;
    }
    if (id == 0x1b92b27)
        return this;
    void* p = FUN_00b18460(id);
    if (!p) {
        p = ((void*(__thiscall*)(void*, int))FUN_00c884f0)((char*)this + 0x34, id);
        if (!p)
            p = ((void*(__thiscall*)(void*, int))FUN_00ac0320)((char*)this + 0x108, id);
    }
    return p;
}
}  // namespace SP

// @ 0x00c6b410
// cNest's LoadModel override is reached through its cSpatialObject sub-object, so the incoming ecx is
// the cSpatialObject (cNest + 0x34); AddFootprint is the cNest method at ecx - 0x34.
bool __fastcall FUN_00c6b410(void* spatialThis, void* edx, SP::cIModelWorld * modelWorld)
{
    bool ok = ((bool(__thiscall*)(void*, void*))FUN_00c8a550)(spatialThis, modelWorld);
    if (ok)
        ((SP::cNest_s00c6_a550*)((char*)spatialThis - 0x34))->AddFootprint();
    return ok;
}

// @ 0x00c6b440
namespace SP {
void SP::cHerd_s00c6_a550::OnAnimalRemoved(void* animal)
{
    if (mCreaturePersonality == animal) {
        if (mCreaturePersonality)
            *(u32*)((char*)(*(void**)((char*)mCreaturePersonality + 0xb4c)) + 0x5fc) &= 0xffbfffff;
        if (mCreaturePersonality) {
            RefObj* o = mCreaturePersonality;
            mCreaturePersonality = 0;
            o->Release();
        }
        for (int i = 0; i < mpHerdEnd - mpHerdBegin; ++i) {
            void* a = FUN_00d99500(mpHerdBegin[i]);
            if (a != animal && FUN_00c6af40((AnimalNoun*)a, this)) {
                RefObj* cur = mCreaturePersonality;
                if ((RefObj*)a != cur) {
                    if (a)
                        (*(void(__thiscall**)(void*))(*(char**)a))(a);
                    mCreaturePersonality = (RefObj*)a;
                    if (cur)
                        (*(void(__thiscall**)(void*))(*(char**)cur + 4))(cur);
                }
                *(u32*)((char*)(*(void**)((char*)mCreaturePersonality + 0xb4c)) + 0x5fc) |= 0x400000;
                break;
            }
        }
    }
    if (mpEggLayer == animal) {
        ((void(__thiscall*)(void*, int))FUN_00c02c20)(animal, 0);
        if (mpEggLayer) {
            RefObj* o = (RefObj*)mpEggLayer;
            mpEggLayer = 0;
            o->Release();
        }
    }
}
}  // namespace SP

// @ 0x00c6b540
namespace SP {
void SP::cHerd_s00c6_a550::SpawnAnimalsIfUnderfilled()
{
    if (mbEnabled)
        return;
    int count = mHead - (int)(mpHerdEnd - mpHerdBegin) - mTail;
    if (count <= 0)
        return;
    const Vec3* pos;
    if (void* nest = mpNest)
        pos = ((ISpatial*)((char*)nest + 0x34))->GetPosition();
    else
        pos = (const Vec3*)((char*)this + 0x34);
    FUN_00c09fa0((void*)pos, (int)mSpeciesKey, count, FUN_00c69f80(), this);
}
}  // namespace SP

// @ 0x00c6b5b0
namespace SP {
void SP::cHerd_s00c6_a550::FindWateringHole()
{
    void* planet = PlanetModel();
    Vec3 out;
    out.x = gViewerOrigin[0];
    out.y = gViewerOrigin[1];
    out.z = gViewerOrigin[2];
    float dist = mNumBabies > gEpsilon ? mNumBabies : gWaterSearchDist;
    const Vec3* pos;
    if (mpNest)
        pos = ((ISpatial*)((char*)mpNest + 0x34))->GetPosition();
    else
        pos = (const Vec3*)((char*)this + 0x34);
    if (((char(__thiscall*)(void*, const void*, float, void*))FindClosestWater)(planet, pos, dist, &out))
        mWateringHolePosition = out;
}
}  // namespace SP

struct NestRef_c6bd60 { virtual void v0(); virtual void Release(); };
struct NestNode_c6bd60 { NestNode_c6bd60* mpNext; NestNode_c6bd60* mpPrev; NestRef_c6bd60* mpRef; };
struct NestList_c6bd60 { NestNode_c6bd60* mpNext; NestNode_c6bd60* mpPrev; char pad08[0x10]; NestNode_c6bd60* mpFree; };

// @ 0x00c6bd60
void __fastcall FUN_00c6bd60(void* self)
{
    NestList_c6bd60* list = (NestList_c6bd60*)self;
    NestNode_c6bd60* node = list->mpNext;
    while (node != (NestNode_c6bd60*)list) {
        NestNode_c6bd60* cur = node;
        node = node->mpNext;
        if (cur->mpRef)
            cur->mpRef->Release();
        cur->mpNext = list->mpFree;
        list->mpFree = cur;
    }
}

// @ 0x00c6bdc0
SP::Vec3* SP::cHerd_s00c6_b660::GetWateringHolePosition()
{
    if (!mbCheckedForWateringHole) {
        mbCheckedForWateringHole = 1;
        FUN_00c6b5b0(this);
    }
    return &mWateringHolePosition;
}

// @ 0x00c6bf20
u8 __cdecl FUN_00c6bf20(void** serializer, int name, const void* vec2, int elem)
{
    struct WStr { wchar_t* begin; wchar_t* end; wchar_t* cap; };
    WStr A;
    A.begin = (wchar_t*)0x1667bac;
    A.end   = (wchar_t*)0x1667bac;
    A.cap   = (wchar_t*)0x1667bad;
    FUN_00694fe0(&A, vec2);
    if (A.begin == A.end)
        goto done;
    {
        WStr B;
        bool noName = (name == 0);
        if (noName) {
            B.begin = (wchar_t*)0x1667bac;
            B.end   = (wchar_t*)0x1667bac;
            B.cap   = (wchar_t*)0x1667bae;
        } else {
            FUN_0093c5a0(&B, name, -1);
        }
        WStr C;
        FUN_0056e2d0(&C, &B);
        if (noName && ((char*)B.cap - (char*)B.begin & ~1) > 2 && B.begin)
            FUN_00f47380(B.begin);
        if (!noName && ((char*)B.cap - (char*)B.begin & ~1) > 2 && B.begin)
            FUN_00f47380(B.begin);

        WStr D;
        FUN_0093c6d0(&D, &A);
        bool ok;
        if (D.begin == D.end) {
            ok = (*(char(__thiscall**)(void**, int))(*(char**)serializer))(serializer, elem) != 0;
        } else {
            ok = (*(char(__thiscall**)(void**, wchar_t*))(*(char**)serializer))(serializer, D.begin) != 0;
            if (ok && gUnknownFlag != 0)
                ok = (*(char(__thiscall**)(void**, const wchar_t*, int))
                       (*(char**)serializer + 8))(serializer, L"type", elem) != 0;
        }
        if (ok) {
            if (D.begin == D.end)
                ok = (*(char(__thiscall**)(void**, int))(*(char**)serializer + 0xc))(serializer, elem) != 0;
            if (ok) {
                if (D.begin == D.end)
                    ok = (*(char(__thiscall**)(void**, int))(*(char**)serializer + 4))(serializer, elem) != 0;
                else
                    ok = (*(char(__thiscall**)(void**, wchar_t*))(*(char**)serializer + 4))
                         (serializer, D.begin) != 0;
            }
        }
        if (((char*)D.cap - (char*)D.begin & ~1) > 2 && D.begin)
            FUN_00f47380(D.begin);
        if (((char*)C.cap - (char*)C.begin & ~1) > 2 && C.begin)
            FUN_00f47380(C.begin);
        u8 r = ok ? 1 : 0;
        if (((char*)A.cap - (char*)A.begin) > 1 && A.begin)
            FUN_00f47380(A.begin);
        return r;
    }
done:
    if (((char*)A.cap - (char*)A.begin) > 1 && A.begin)
        FUN_00f47380(A.begin);
    return 1;
}

// @ 0x00c6c390
u8 __cdecl FUN_00c6c390(void** serializer, int name, void** list)
{
    struct WStr { wchar_t* begin; wchar_t* end; wchar_t* cap; };
    if (list[0] == list[1])
        return 1;

    bool noName = (name == 0);
    WStr N;
    if (noName) {
        N.begin = 0; N.end = 0; N.cap = 0;
        FUN_00579a90(&N, 0);
    } else {
        FUN_0093c5a0(&N, name, -1);
    }
    WStr C;
    FUN_0056e2d0(&C, &N);
    if (noName && ((char*)N.cap - (char*)N.begin & ~1) > 2 && N.begin)
        FUN_00f47380(N.begin);
    if (!noName && ((char*)N.cap - (char*)N.begin & ~1) > 2 && N.begin)
        FUN_00f47380(N.begin);

    (*(void(__thiscall**)(void**, wchar_t*))(*(char**)serializer))
        (serializer, (C.begin == C.end) ? (wchar_t*)0x13f58ac : C.begin);

    u8 ok = 1;
    char* end = (char*)list[1];
    for (char* it = (char*)list[0]; it != end; it += 4) {
        if (ok)
            ok = FUN_00ac8050(serializer, 0, it) != 0;
    }
    (*(void(__thiscall**)(void**, wchar_t*))(*(char**)serializer + 4))
        (serializer, (C.begin == C.end) ? (wchar_t*)0x13f58ac : C.begin);
    if (((char*)C.cap - (char*)C.begin & ~1) > 2 && C.begin)
        FUN_00f47380(C.begin);
    return ok;
}

// @ 0x00c6c4e0
u8 __cdecl FUN_00c6c4e0(void** serializer, int name, void** list)
{
    struct WStr { wchar_t* begin; wchar_t* end; wchar_t* cap; };
    if (list[0] == list[1])
        return 1;

    bool noName = (name == 0);
    WStr N;
    if (noName) {
        N.begin = 0; N.end = 0; N.cap = 0;
        FUN_00579a90(&N, 0);
    } else {
        FUN_0093c5a0(&N, name, -1);
    }
    WStr C;
    FUN_0056e2d0(&C, &N);
    if (noName && ((char*)N.cap - (char*)N.begin & ~1) > 2 && N.begin)
        FUN_00f47380(N.begin);
    if (!noName && ((char*)N.cap - (char*)N.begin & ~1) > 2 && N.begin)
        FUN_00f47380(N.begin);

    (*(void(__thiscall**)(void**, wchar_t*))(*(char**)serializer))
        (serializer, (C.begin == C.end) ? (wchar_t*)0x13f58ac : C.begin);

    u8 ok = 1;
    char* end = (char*)list[1];
    for (char* it = (char*)list[0]; it != end; it += 0xc) {
        if (ok)
            ok = FUN_00ae5530(serializer, 0, it, L"EA::ResourceMan::Key") != 0;
    }
    (*(void(__thiscall**)(void**, wchar_t*))(*(char**)serializer + 4))
        (serializer, (C.begin == C.end) ? (wchar_t*)0x13f58ac : C.begin);
    if (((char*)C.cap - (char*)C.begin & ~1) > 2 && C.begin)
        FUN_00f47380(C.begin);
    return ok;
}

// @ 0x00c6c630
u8 __cdecl FUN_00c6c630(void** serializer, int name, void** list)
{
    struct WStr { wchar_t* begin; wchar_t* end; wchar_t* cap; };
    u8 ok = 1;
    WStr N;
    if (list[0] != list[1]) {
        int flags;
        if (name != 0) {
            FUN_0093c5a0(&N, name, -1);
            flags = 1;
        } else {
            N.begin = 0; N.end = 0; N.cap = 0;
            ((void(__thiscall*)(void*, int))FUN_00579a90)(&N, 0);
            flags = 2;
        }
        WStr C;
        ((void(__thiscall*)(void*, const void*))FUN_0056e2d0)(&C, &N);
        if ((flags & 2) && ((char*)N.cap - (char*)N.begin & ~1) > 2 && N.begin)
            FUN_00f47380(N.begin);
        if ((flags & 1) && ((char*)N.cap - (char*)N.begin & ~1) > 2 && N.begin)
            FUN_00f47380(N.begin);

        (*(void(__thiscall**)(void**, wchar_t*))(*(char**)serializer))
            (serializer, (C.begin == C.end) ? (wchar_t*)0x13f58ac : C.begin);

        char* end = (char*)list[1];
        for (char* it = (char*)list[0]; it != end; it += 4) {
            ok = (ok != 0);
        }
        (*(void(__thiscall**)(void**, wchar_t*))(*(char**)serializer + 4))
            (serializer, (C.begin == C.end) ? (wchar_t*)0x13f58ac : C.begin);
        if (((char*)C.cap - (char*)C.begin & ~1) > 2 && C.begin)
            FUN_00f47380(C.begin);
    }
    return ok;
}

// @ 0x00c6c760
void __cdecl Write()
{
}

// @ 0x00c6c8c0
void __cdecl RemoveOwner()
{
}

// @ 0x00c6cbf0
void __cdecl FUN_00c6cbf0()
{
}

extern "C" void __cdecl ReadInt32_00c6ce30(void* io, void* dst, int count, int ver); // 0x0093a780
extern "C" void* __cdecl memmove(void* dst, const void* src, unsigned n);
struct IntVec_s00c6_ce30 {
    int* begin;
    int* end;
    int* cap;
    void Reserve(uint32_t n);                       // 0x00d01790
    void InsertSlow(int* pos, const int* value);    // 0x00b96600
    int* erase(int* first, int* last) {
        memmove(first, last, (size_t)((char*)end - (char*)last));
        end -= (last - first);
        return first;
    }
    void clear() { erase(begin, end); }
    void push_back(int v) {
        if (end < cap) {
            int* p = end++;
            if (p) *p = v;
        } else {
            InsertSlow(end, &v);
        }
    }
};
struct IoStream_s00c6ce30 {
    virtual void f00(); virtual void f04(); virtual void f08(); virtual void f0c();
    virtual void f10(); virtual void f14();
    virtual void* GetStream();                      // +0x18
};
struct Reader_s00c6ce30 {
    virtual void f00(); virtual void f04(); virtual void f08(); virtual void f0c();
    virtual void f10(); virtual void f14(); virtual void f18();
    virtual void Done();                            // +0x1c
    virtual IoStream_s00c6ce30* GetIO();            // +0x20
};

// @ 0x00c6ce30
void __cdecl FUN_00c6ce30(void* pstream, IntVec_s00c6_ce30* vec)
{
    Reader_s00c6ce30* stream = (Reader_s00c6ce30*)pstream;
    vec->clear();
    uint32_t count = 0;
    void* io = stream->GetIO()->GetStream();
    ReadInt32_00c6ce30(io, &count, 1, 0);
    vec->Reserve(count);
    for (uint32_t i = 0; i < count; ++i) {
        int value;
        void* io2 = stream->GetIO()->GetStream();
        ReadInt32_00c6ce30(io2, &value, 1, 0);
        vec->push_back(value);
    }
    stream->Done();
}

// @ 0x00c6cf10
void __cdecl AddEggInNest()
{
}

// @ 0x00c6e710
void __fastcall FUN_00c6e710(void* self, void* /*edx*/, u32 count)
{
  char* p = (char*)self;
  void* mgr = SP_NounManager();
  s32 cur = (s32)(*(u32**)(p + 0x58) - *(u32**)(p + 0x54)) >> 2;
  u32 i = count;
  (void)cur;

  if (cur < (s32)count) {
    char* arche = *(char**)(p + 0xa4);
    float scale = FUN_00c6a180(
        *(float*)(arche + 0x554) * *(float*)(arche + 0x554) +
        *(float*)(arche + 0x558) * *(float*)(arche + 0x558) +
        *(float*)(arche + 0x55c) * *(float*)(arche + 0x55c));
    (void)scale;
    FUN_00b06d90(p + 0x54, count);
    if (cur < (s32)count) {
      u32 idx = (u32)cur;
      do {
        char* noun = (char*)FUN_00b20c60(mgr, 0x02a034cd);
        if (noun != 0) {
          ((void(__thiscall*)(void*))(*(void***)noun)[0 / 4])(noun);
        }
        // +0x1f4 = ref to owning herd
        void* oldHerd = *(void**)(noun + 0x1f4);
        if (p != oldHerd) {
          ((void(__thiscall*)(void*))(*(void***)p)[0 / 4])(p);
          *(void**)(noun + 0x1f4) = p;
          if (oldHerd != 0) {
            ((void(__thiscall*)(void*))(*(void***)oldHerd)[4 / 4])(oldHerd);
          }
        }
        // +0x220 = egg scale; +0x34 = transform whose vtable slot 0x40 sets it
        *(float*)(noun + 0x220) = scale;
        ((void(__thiscall*)(void*, float))(*(void***)(noun + 0x34))[0x40 / 4])(noun + 0x34, scale);
        u32* vec = *(u32**)(p + 0x54);
        void* oldSlot = (void*)vec[idx];
        if (noun != oldSlot) {
          ((void(__thiscall*)(void*))(*(void***)noun)[0 / 4])(noun);
          vec[idx] = (u32)noun;
          if (oldSlot != 0) {
            ((void(__thiscall*)(void*))(*(void***)oldSlot)[4 / 4])(oldSlot);
          }
        }
        ((void(__thiscall*)(void*))(*(void***)noun)[4 / 4])(noun);
        cur++;
        idx++;
      } while (cur < (s32)count);
      return;
    }
  } else if ((s32)count < cur) {
    do {
      char* noun = *(char**)(*(u32**)(p + 0x54) + i * 4);
      // +0x1f4 herd-ref, +0x218 secondary ref
      void* r1 = *(void**)(noun + 0x1f4);
      if (r1 != 0) {
        *(u32*)(noun + 0x1f4) = 0;
        ((void(__thiscall*)(void*))(*(void***)r1)[4 / 4])(r1);
      }
      void* r2 = *(void**)(noun + 0x218);
      if (r2 != 0) {
        *(u32*)(noun + 0x218) = 0;
        ((void(__thiscall*)(void*))(*(void***)r2)[4 / 4])(r2);
      }
      FUN_00b225d0(mgr, noun);
      i++;
    } while ((s32)i < cur);
    u32* vec = *(u32**)(p + 0x54);
    u32* end = *(u32**)(p + 0x58);
    if ((u32)((end - vec) >> 2) < count) {
      u32 n = count - (u32)((end - vec) >> 2);
      u32 zero = 0;
      FUN_00babb70(end, n, &zero);
      return;
    }
    FUN_00e25bd0(vec + count, end);
  }
}

// @ 0x00c6e8f0
u8 __fastcall FUN_00c6e8f0(void* self, void* /*edx*/, void* def, void* keys, char* owner)
{
  char* p = (char*)self;
  float p0, p1, p2;
  float* src = (float*)((owner != 0) ? owner : (p + 0x34));
  p0 = src[0]; p1 = src[1]; p2 = src[2];
  float a0 = (p0 < 0.0f) ? -p0 : p0;
  float a1 = (p1 < 0.0f) ? -p1 : p1;
  float a2 = (p2 < 0.0f) ? -p2 : p2;

  // Choose the dominant axis and quantise the other two into [0,127].
  s32 q0, q1; u32 axis;
  if (a0 >= a2 && a1 >= a2) {
    q0 = (s32)((p0 / p2 + 1.0f) * 64.0f);
    q1 = (s32)((p1 / p2 + 1.0f) * 64.0f);
    axis = (p2 < 0.0f) ? 1u : 0u;
  } else if (a0 >= a1) {
    q0 = (s32)((p2 / p1 + 1.0f) * 64.0f);
    q1 = (s32)((p0 / a1 + 1.0f) * 64.0f);
    axis = (p1 < 0.0f) ? 5u : 4u;
  } else {
    q0 = (s32)((p1 / p0 + 1.0f) * 64.0f);
    q1 = (s32)((p2 / a0 + 1.0f) * 64.0f);
    axis = (p0 < 0.0f) ? 3u : 2u;
  }
  if (q0 == 0x80) q0 = 0x7f;
  if (q1 == 0x80) q1 = 0x7f;

  // Turn the quantised pair back into a unit direction on the chosen axis.
  u32 off = (axis >> 1) * 4;
  const u8* perm = DAT_014718b8 + off;
  float c0 = (float)q0;
  float c1 = (float)q1;
  float v = (c0 + 0.5f) * 0.015625f - 1.0f;
  float w = (c1 + 0.5f) * 0.015625f - 1.0f;
  float inv = 1.0f / (float)sqrtf(v * v + w * w + 1.0f);
  float sgn = (axis & 1) ? -v : v;
  float dir[4];
  dir[perm[0]] = sgn * inv;
  dir[perm[1]] = w * inv;
  dir[perm[2]] = sgn;
  (void)sgn;
  // Re-normalise the two quantised components by the unit length.
  dir[0] = v * inv;
  dir[1] = w * inv;

  // Scale the orientation vector by the planet radius at that direction.
  float local[3];
  local[0] = dir[0];
  local[1] = dir[1];
  local[2] = dir[2];
  void* pm = FUN_00b3d350();
  float radius = FUN_00b7ef70(pm, local);
  local[0] = local[0] * radius;
  local[1] = local[1] * radius;
  local[2] = local[2] * radius;

  extern u8 FUN_00b18400_ret(void);
  u8 ok = ((u8(__thiscall*)(void*, void*, void*, void*))FUN_00b18400)(
      self, def, keys, local);
  if (ok == 0) return ok;

  void* defv = def;
  *(float*)(p + 0x34) = local[0];
  *(float*)(p + 0x38) = local[1];
  *(float*)(p + 0x3c) = local[2];
  *(u32*)(p + 0x8c) = 0;
  *(u32*)(p + 0xf0) = 0;

  char* k = (char*)keys;
  if (k != 0) {
    *(u32*)(p + 0xf4) = *(u32*)(k + 0xc);
    *(u32*)(p + 0x15c) = *(u32*)(k + 0x10);
    if (*(u32*)(k + 0x14) == 0 && defv != 0) {
      void* nm = FUN_00b3d300();
      void* dbg = FUN_00b20e40(nm, defv, local);
      FUN_00b5f950(p + 0x160, dbg);
    }
    *(u32*)(p + 0x8c) = *(u32*)k;
    if (*(float*)(k + 0x18) > 0.0f) *(float*)(p + 0x150) = *(float*)(k + 0x18);
    if (*(float*)(k + 0x1c) > 0.0f) *(float*)(p + 0x154) = *(float*)(k + 0x1c);
    if (*(float*)(k + 0x20) > 0.0f) *(float*)(p + 0x158) = *(float*)(k + 0x20);
    if (*(float*)(k + 0x24) > 0.0f) *(float*)(p + 0x108) = *(float*)(k + 0x24);
    u32 v0 = *(u32*)(k + 0x28);
    u32 v1 = *(u32*)(k + 0x2c);
    *(u32*)(p + 0x120) = v0;
    *(u32*)(p + 0x124) = v1;
    if (v0 == 0 && v1 == 0) *(u32*)(p + 0x124) = 5;
  }

  // Build the object from the definition view.
  u32 defArg = *(u32*)((char*)def + 8);
  u32 idA = *(u32*)(p + 0x8c);
  u8 localFlag = 0;
  void* obj = FUN_00b9a750(idA, (void*)defArg, 0, 0, &localFlag);
  *(void**)(p + 0xa4) = obj;
  void* arch = FUN_004e0050(FUN_00401090(defArg, 0), 0);
  FUN_00c6e200(self, arch, 0);
  if (*(void**)(p + 0xa4) == 0) return 0;

  char* o = *(char**)(p + 0xa4);
  *(u32*)(p + 0x98) = *(u32*)(o + 0x504);
  *(u32*)(p + 0x9c) = *(u32*)(o + 0x508);
  *(u32*)(p + 0xa0) = *(u32*)(o + 0x50c);
  *(u32*)(p + 0x88) = *(u32*)((char*)def + 8);
  ((void(__thiscall*)(void*))(*(void***)p)[0x54 / 4])(p);
  void* dbg = *(void**)(p + 0x160);
  *(u8*)(p + 0x218) = 0;
  if (dbg != 0) *(u8*)((char*)dbg + 0xa9) = 0;

  // Append the archetype key list to the mKeys vector at +0xa8.
  char* src2 = *(char**)(p + 0xa4);
  u32* beg = *(u32**)(p + 0xa8);
  u32* end = *(u32**)(p + 0xac);
  src2 += 0x504;
  if ((u32)end < *(u32*)(p + 0xb0)) {
    *(u32*)(p + 0xac) = (u32)(end + 3);
    if (end != 0) {
      end[0] = *(u32*)(src2 + 0);
      end[1] = *(u32*)(src2 + 4);
      end[2] = *(u32*)(src2 + 8);
    }
  } else {
    FUN_004e3e10(p + 0xa8, src2);
  }
  (void)beg;

  char* keyList = (char*)keys;
  u32 n = (u32)((*(u32**)(keyList + 0x3c8) - *(u32**)(keyList + 0x3c4)) >> 2);
  u32 idx = 0;
  if (n > 0) {
    do {
      u32 kA = *(u32*)(p + 0x88);
      u32 kB = *(u32*)(p + 0x8c);
      u8 flag2 = 0;
      void* obj2 = FUN_00b9a750(kB, (void*)kA, (int)(idx + 1), *(u32*)(p + 0xa4), &flag2);
      if (obj2 == 0) {
        *(u8*)(p + 0x85) = 0;
        break;
      }
      u32* e2 = *(u32**)(p + 0xac);
      char* s3 = (char*)obj2 + 0x504;
      if ((u32)e2 < *(u32*)(p + 0xb0)) {
        *(u32*)(p + 0xac) = (u32)(e2 + 3);
        if (e2 != 0) {
          e2[0] = *(u32*)(s3 + 0);
          e2[1] = *(u32*)(s3 + 4);
          e2[2] = *(u32*)(s3 + 8);
        }
      } else {
        FUN_004e3e10(p + 0xa8, s3);
      }
      idx++;
    } while (idx < n);
  }
  return 1;
}

// @ 0x0134cf40
namespace Simulator {
void InitEggAttributes()
{
    ADD_EGG(0, "mState",       0x5268a36e, 0x1e8, Read4<int>, Write4<int>, ReadText_00692ff0_s0134_7830, WriteText_00694ee0_s0134_7830, AlwaysValid<int>, ToXml_0057cde0_s0134_7830)
    ADD_EGG(1, "mpHerd",       0xd2afa598, 0x1f4, Read_00b20540, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f550, ToXml_00ac8050)
    ADD_EGG(2, "mTimeToHatch", 0xf301c18b, 0x1f0, Read4<int>, Write4<int>, ReadText_00692ff0_s0134_7830, WriteText_00694ee0_s0134_7830, AlwaysValid<int>, ToXml_0057cde0_s0134_7830)
    ADD_EGG(3, "mBrokenTimer", 0xd301c1ab, 0x1f8, Read_00ae3470, Write_00ae3490, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00ae3310, ToXml_00ac8050)
    ADD_EGG(4, "mpToHatch",    0x5301c42e, 0x218, Read_00b02540, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00b6f550, ToXml_00ac8050)
    ADD_EGG(5, "mEffectScale", 0x7301c22a, 0x220, Read4<float>, Write_00ac88f0_s0134_7830, ReadText_006930b0_s0134_7830, WriteText_00694fc0_s0134_7830, AlwaysValid<float>, ToXml_00acbb80_s0134_7830)
}
}  // namespace Simulator

// @ 0x0134d380
namespace Simulator {
void InitHerdAttributes()
{
    {
        Attribute a("mHerd", 0x021e6db2, 0x040,
                  Read_00acdf10, Write_00aca730, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00b6f860, ToXml_00c6c390);
        *(Attribute*)&cHerd_sAttributes[0] = a;
    }
    {
        Attribute a("mEggs", 0x52689e83, 0x054,
                  Read_00c6cd50, Write_00aca730, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00b6f860, ToXml_00c6c390);
        *(Attribute*)&cHerd_sAttributes[1] = a;
    }
    {
        Attribute a("mOwnedByAvatar", 0x021e6dae, 0x084,
                  Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
                  Validate_00b1fbf0, ToXml_0057ce00);
        *(Attribute*)&cHerd_sAttributes[2] = a;
    }
    {
        Attribute a("mArchetype", 0x030bbb5d, 0x088,
                  Read_00572810, Write_00572840, ReadText_00693090, WriteText_00694f00,
                  Validate_00b1fbf0, ToXml_00675ca0);
        *(Attribute*)&cHerd_sAttributes[3] = a;
    }
    {
        Attribute a("mArchetypeGroup", 0x04894af5, 0x08c,
                  Read_00572810, Write_00572840, ReadText_00693090, WriteText_00694f00,
                  Validate_00b1fbf0, ToXml_00675ca0);
        *(Attribute*)&cHerd_sAttributes[4] = a;
    }
    {
        Attribute a("mScheduleIndex", 0x04ea45ca, 0x090,
                  Read_00572810, Write_00572840, ReadText_00693090, WriteText_00694f00,
                  Validate_00b1fbf0, ToXml_00675ca0);
        *(Attribute*)&cHerd_sAttributes[5] = a;
    }
    {
        Attribute a("mOwnerSpeciesKey", 0x03f64453, 0x098,
                  Read_00ae3430, Write_00ae3450, ReadText_00693150, WriteText_00695080,
                  Validate_00b1fbf0, ToXml_00ae5720);
        *(Attribute*)&cHerd_sAttributes[6] = a;
    }
    {
        Attribute a("mGeneration", 0x039a2b58, 0x0f0,
                  Read_00572810, Write_00572840, ReadText_00693090, WriteText_00694f00,
                  Validate_00b1fbf0, ToXml_00675ca0);
        *(Attribute*)&cHerd_sAttributes[7] = a;
    }
    {
        Attribute a("mEvolvedSpeciesProfileKeys", 0x9493bd27, 0x0a8,
                  Read_00c95780, Write_00c6adc0, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00b1fbf0, ToXml_00c6c4e0);
        *(Attribute*)&cHerd_sAttributes[8] = a;
    }
    {
        Attribute a("mInitialShortfall", 0x03fe8d35, 0x0f8,
                  Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
                  Validate_00b1fbf0, ToXml_0057cde0);
        *(Attribute*)&cHerd_sAttributes[9] = a;
    }
    {
        Attribute a("mScaleMultiplier", 0x03fe8d8b, 0x150,
                  Read_00572810, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0,
                  Validate_00b1fbf0, ToXml_00acbb80);
        *(Attribute*)&cHerd_sAttributes[10] = a;
    }
    {
        Attribute a("mHitpointOverride", 0x03fe8e9c, 0x154,
                  Read_00572810, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0,
                  Validate_00b1fbf0, ToXml_00acbb80);
        *(Attribute*)&cHerd_sAttributes[11] = a;
    }
    {
        Attribute a("mDamageMultiplier", 0x03fe8eb3, 0x158,
                  Read_00572810, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0,
                  Validate_00b1fbf0, ToXml_00acbb80);
        *(Attribute*)&cHerd_sAttributes[12] = a;
    }
    {
        Attribute a("mTargetHerdSize", 0x021e6db0, 0x0f4,
                  Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
                  Validate_00b1fbf0, ToXml_0057cde0);
        *(Attribute*)&cHerd_sAttributes[13] = a;
    }
    {
        Attribute a("mbEggStatusChanged", 0x021e6dad, 0x0fc,
                  Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
                  Validate_00b1fbf0, ToXml_0057ce00);
        *(Attribute*)&cHerd_sAttributes[14] = a;
    }
    {
        Attribute a("mNumGuards", 0x12689e6f, 0x100,
                  Read_00572810, Write_00572840, ReadText_00693090, WriteText_00694f00,
                  Validate_00b1fbf0, ToXml_00675ca0);
        *(Attribute*)&cHerd_sAttributes[15] = a;
    }
    {
        Attribute a("mRespawnRate", 0x0320d9e2, 0x11c,
                  Read_00572810, Write_00572840, ReadText_00693090, WriteText_00694f00,
                  Validate_00b1fbf0, ToXml_00675ca0);
        *(Attribute*)&cHerd_sAttributes[16] = a;
    }
    {
        Attribute a("mCreaturePersonality", 0x52ae4e7b, 0x15c,
                  Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
                  Validate_00b1fbf0, ToXml_0057cde0);
        *(Attribute*)&cHerd_sAttributes[17] = a;
    }
    {
        Attribute a("mpNest", 0xd2aa6604, 0x160,
                  Read_00c6bce0, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00b6f550, ToXml_00ac8050);
        *(Attribute*)&cHerd_sAttributes[18] = a;
    }
    {
        Attribute a("mpEggLayer", 0x12ae4eca, 0x194,
                  Read_00b20510, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00b6f550, ToXml_00ac8050);
        *(Attribute*)&cHerd_sAttributes[19] = a;
    }
    {
        Attribute a("mpHerdMom", 0x73d72126, 0x164,
                  Read_00b20510, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00b6f550, ToXml_00ac8050);
        *(Attribute*)&cHerd_sAttributes[20] = a;
    }
    {
        Attribute a("mbEggsInNest", 0x021e6db1, 0x198,
                  Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
                  Validate_00b1fbf0, ToXml_0057ce00);
        *(Attribute*)&cHerd_sAttributes[21] = a;
    }
    {
        Attribute a("mValidLocations", 0x32689ec8, 0x1e0,
                  Read_00c6ce30, Write_00c46470, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00b1fbf0, ToXml_00c6c630);
        *(Attribute*)&cHerd_sAttributes[22] = a;
    }
    {
        Attribute a("mbEnabled", 0xd2ae8fdc, 0x218,
                  Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
                  Validate_00b1fbf0, ToXml_0057ce00);
        *(Attribute*)&cHerd_sAttributes[23] = a;
    }
    {
        Attribute a("mTerritoryRadius", 0x0403e2b1, 0x108,
                  Read_00572810, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0,
                  Validate_00b1fbf0, ToXml_00acbb80);
        *(Attribute*)&cHerd_sAttributes[24] = a;
    }
    {
        Attribute a("mActivateBrainLevel", 0x0403e2b2, 0x120,
                  Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
                  Validate_00b1fbf0, ToXml_0057cde0);
        *(Attribute*)&cHerd_sAttributes[25] = a;
    }
    {
        Attribute a("mDeactivateBrainLevel", 0x0403e2b3, 0x124,
                  Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
                  Validate_00b1fbf0, ToXml_0057cde0);
        *(Attribute*)&cHerd_sAttributes[26] = a;
    }
    {
        Attribute a("mbCheckedForWateringHole", 0x04cfbbf9, 0x208,
                  Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
                  Validate_00b1fbf0, ToXml_0057ce00);
        *(Attribute*)&cHerd_sAttributes[27] = a;
    }
    {
        Attribute a("mWateringHolePosition", 0x041fa3ba, 0x20c,
                  Read_00b6e3a0, Write_00ac88c0, ReadText_006930f0, WriteText_00695010,
                  Validate_00b1fbf0, ToXml_00acbba0);
        *(Attribute*)&cHerd_sAttributes[28] = a;
    }
    {
        Attribute a("mbCheckedForForests", 0x04cfcaee, 0x07c,
                  Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
                  Validate_00b1fbf0, ToXml_0057ce00);
        *(Attribute*)&cHerd_sAttributes[29] = a;
    }
    {
        Attribute a("mCurrentFeedingGrounds", 0x04cfe14e, 0x080,
                  Read_00572810, Write_00572840, ReadText_00693090, WriteText_00694f00,
                  Validate_00b1fbf0, ToXml_00675ca0);
        *(Attribute*)&cHerd_sAttributes[30] = a;
    }
    {
        Attribute a("mChangeFeedingGroundsTimer", 0x04cfe1f5, 0x1c0,
                  Read_00ae3470, Write_00ae3490, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00ae3310, ToXml_00ac8050);
        *(Attribute*)&cHerd_sAttributes[31] = a;
    }
    {
        Attribute a("mFeedingGrounds", 0x04cfcaf6, 0x068,
                  Read_00c41210, Write_00c40e80, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00b1fbf0, ToXml_00c41b00);
        *(Attribute*)&cHerd_sAttributes[32] = a;
    }
    {
        Attribute a("mNumGuardLocations", 0x04447955, 0x10c,
                  Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
                  Validate_00b1fbf0, ToXml_0057cde0);
        *(Attribute*)&cHerd_sAttributes[33] = a;
    }
    {
        Attribute a("mNumGuardsPerLocation", 0x04447959, 0x110,
                  Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
                  Validate_00b1fbf0, ToXml_0057cde0);
        *(Attribute*)&cHerd_sAttributes[34] = a;
    }
    {
        Attribute a("mGuardMinMaxRadius", 0x04447971, 0x114,
                  Read_00c6a080, Write_00c6a0b0, ReadText_006930d0, WriteText_00694fe0,
                  Validate_00b1fbf0, ToXml_00c6c0f0);
        *(Attribute*)&cHerd_sAttributes[35] = a;
    }
    {
        Attribute a("mEggIndex", 0x1368374c, 0x12c,
                  Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
                  Validate_00b1fbf0, ToXml_0057cde0);
        *(Attribute*)&cHerd_sAttributes[36] = a;
    }
    {
        Vec3Default tmp = { 0.0f, 0.0f, 0.0f };
        sHerdDefaultVec3[0] = tmp.x;
        sHerdDefaultVec3[1] = tmp.y;
        sHerdDefaultVec3[2] = tmp.z;
        if (sHerdDefaultVec3Guard == 0)
            sHerdDefaultVec3Guard = 1;
        Attribute a("mInitialPosition", 0x1368374d, 0x034,
                  Read_00b6e3a0, Write_00ac88c0, ReadText_006930f0, WriteText_00695010,
                  Validate_00b1fbf0, ToXml_00acbba0,
                  SetDefault_00c6ae30);
        *(Attribute*)&cHerd_sAttributes[37] = a;
    }
    {
        sDNAEvolutionThresholdDefault = 3.402823466e+38f;
        Attribute a("mDNAEvolutionThreshold", 0x0517a7b0, 0x094,
                  Read_00572810, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0,
                  Validate_00b1fbf0, ToXml_00acbb80,
                  SetDefault_00c6a0e0);
        *(Attribute*)&cHerd_sAttributes[38] = a;
    }
    {
        Attribute a("mbShouldEvolve", 0x0517ad97, 0x085,
                  Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
                  Validate_00b1fbf0, ToXml_0057ce00);
        *(Attribute*)&cHerd_sAttributes[39] = a;
    }
    {
        Attribute a("mbBestFriends", 0x342dfbf3, 0x191,
                  Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
                  Validate_00b1fbf0, ToXml_0057ce00);
        *(Attribute*)&cHerd_sAttributes[40] = a;
    }
    {
        Attribute a("mbExtinction", 0xf42dfbf4, 0x190,
                  Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
                  Validate_00b1fbf0, ToXml_0057ce00);
        *(Attribute*)&cHerd_sAttributes[41] = a;
    }
    {
        Attribute a("mbTransientHerd", 0x05c82085, 0x192,
                  Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
                  Validate_00b1fbf0, ToXml_0057ce00);
        *(Attribute*)&cHerd_sAttributes[42] = a;
    }
}
}  // namespace Simulator
