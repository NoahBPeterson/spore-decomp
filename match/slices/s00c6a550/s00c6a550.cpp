// Slice s00c6a550 -- SPGonzago/SPGameNounManager.obj.
// cEgg serialisation + egg state machine, cNest ctor/dtor/RemoveOwner/MoveNest/AddFootprint/
// LoadModel/AsInterface, cHerd small helpers (GetProfileForGeneration, OnAnimalRemoved,
// FindWateringHole, SpawnAnimalsIfUnderfilled), and a couple of noun position/enable helpers.
//
// The shared src/game/include headers carry the 2008 dev-PDB layout; the retail offsets of
// cEgg/cNest/cHerd in this object are shifted, so offsets below come from the disassembly and are
// used through byte-offset accessors on locally declared stub classes.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

#pragma warning(disable : 4100)

typedef unsigned int u32;
typedef unsigned char u8;

// ---------------------------------------------------------------------------------------------
// retail callees / globals
// ---------------------------------------------------------------------------------------------
namespace EA { namespace IO {
bool WriteUint32(void* sink, const void* src, int count, int flags);       // 0x0093aa70
}}

extern "C" {
void  __cdecl FUN_00c6a100(void* egg);                     // 0x00c6a100 egg effect refresh
void* __cdecl FUN_00b530e0(void* p, int a);                // 0x00b530e0
int   __cdecl FUN_004df420(int);                           // GetAvatarProfile
void* __cdecl FUN_00401090();                              // returns the species manager
struct cSpeciesMgr {
    void* GetProfile(const void* key);              // 0x4df550
    void* GetAvatarProfile();                       // 0x4df420
};
void* __cdecl FUN_00b3d4c0(void* a, int b, int c);
int   __cdecl FUN_00ba3f90(void* a, int b, int c);
void* __cdecl PlanetModel();                               // 0x00b3d350
void* __cdecl TerraformingManager();                       // 0x00b3d430
void* __cdecl NounManager();                               // 0x00b3d300
void  __cdecl FUN_00bbc3f0(void* tm);
void* __cdecl FUN_00b18460(int id);
void* __cdecl FUN_00d51660();                              // 0x00d51660
void* __cdecl FUN_00c099e0(void* a, int b, int c, int d, int e);
void  __cdecl FUN_00bc97f0(int a, int key, float f, int b);
void* __cdecl FUN_00d99500(void* noun);
void  __cdecl FUN_00c02c20(void* a, int b);
void  __cdecl FUN_00ae2e40(void* stream, const void* key);
int   __cdecl FUN_00c0b770(void* o);
void* __cdecl FUN_00c04590(void* o);
void* __cdecl FUN_00c884f0(void* spatial, int id);         // AsInterface thunk
void* __cdecl FUN_00ac0320(void* it, int id);              // AsInterface thunk
void  __cdecl FUN_00ac0450(void* it);
void  __cdecl FUN_00ac0520(void* it);
void  __cdecl FUN_00c8a420(void* spatial);
void  __cdecl FUN_00c8b2e0(void* spatial);
void  __cdecl FUN_00b184c0(void* gameData);                // cGameData::~cGameData
void* __cdecl FUN_00c0bbd0(void* creature);                // GetSpeciesProfile
void* __cdecl FUN_00b1fdb0(void* nounManager);             // GetAvatar
void  __cdecl FUN_00c09fa0(void* pos, int key, int count, float f);  // SpawnHerdAnimals
float __cdecl FUN_00c69f80(void* herd);                    // 0x00c69f80
char  __cdecl FindClosestWater(void* planet, const void* pos, float dist, void* out);  // 0xb8bb70
void* __cdecl FUN_00b815a0(void* planet, void* out, const void* dir);  // DirectionToSurfacePosition
void* __cdecl FUN_00b7f190(void* planet, void* out, const void* pos);  // BuildSurfaceOrientation
void* __cdecl FUN_00b7f250(void* planet, void* out, const void* p1, const void* p2);  // BuildSurfaceOrientation2
void  __cdecl FUN_00449c20(void* out, const void* in);     // normalized_safe
void  __cdecl FUN_00b18660(void* gameData);                // cGameData ctor
void  __cdecl FUN_00c89630(void* spatial);                 // cSpatialObject ctor
void  __cdecl FUN_00ac03d0(void* it);                      // cInteractionTarget ctor
int   __cdecl FUN_00b18590(void* gd, void* stream);        // cGameData::Write
int   __cdecl FUN_00c88a90(void* so, void* stream);        // cSpatialObject::Write
int   __cdecl FUN_00bfc4a0(void* cb, void* stream);        // cCombatant::Write
void  __cdecl FUN_00692f90(void* ser, void* obj, void** list, int sig);  // cVarListSerializer ctor
int   __cdecl FUN_00692900(void* ser, void* stream);       // cVarListSerializer::Serialize
void  __fastcall FUN_00bc3130_dummy(void* ecx_timer, void* edx);  // (unused)
void* __cdecl FUN_0067dd10();                              // SP::App
void  __cdecl FUN_007c3d30(void* viewer, void* a, void* b, void* c, void* d);  // GetCameraLocationInfo
void* __cdecl FUN_00c89160(void* so, const void* ext, int flag);   // SetLocalExtents
void* __cdecl FUN_00ff0420(void* p);                       // DatabasePackedFile access flags
int   __cdecl FUN_00c8a550(void* so, void* modelWorld);     // cSpatialObject::LoadModel
}

extern float gHalf;              // 0x01471064  0.5f
extern float gEpsilon;           // 0x014718ec  1.52587890625e-05f
extern float gZeroF;             // 0x01485378  0.0f
extern float gFiveF;             // 0x01486110  5.0f
extern float gWaterSearchDist;   // 0x01582e8c  100.0f
extern float gFiftyF;            // 0x01582f5c  50.0f
extern float gViewerOrigin[3];   // 0x01693e50..0x01693e58
extern int   gViewerGuard;       // 0x01693e4c
extern u32   gViewerData[3];     // 0x01693e40..0x01693e48
extern void* gEggSerializerList; // 0x015778f0

namespace SP {

struct Vec3 { float x, y, z; };
struct Quat { float x, y, z, w; };

// thiscall helpers reached through ecx only (no edx); modelled as member calls so MSVC emits a
// bare `mov ecx, ...; call` (the call relocation is masked, so the symbol name is irrelevant).
struct cSPTimerStub { void Restart(); };

// Parameterless thiscall helpers (each address noted); the name is irrelevant because the call
// relocation is masked, only the `mov ecx,obj; call` shape matters.
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
};

// cGameData-head vtable fragment (the object stream). +0x20 = GetWriter.
class IOStream
{
  public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18();
    virtual void v1c();
    virtual void* GetWriter();          // +0x20
};

// The writer object; +0x18 yields the actual sink and +0x1c flushes it.
class IWriter
{
  public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14();
    virtual void* GetSink();            // +0x18
    virtual void  Finish();             // +0x1c
};

// A stream whose +0x20 slot returns the sink buffer directly (used by FUN_00c6ae30).
class BufWriter
{
  public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual u32* Get();                 // +0x20
};

// cSpatialObject vtable fragment (only the used slots named).
class ISpatial
{
  public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual const Vec3* GetPosition();          // +0x2c
    virtual void v30(); virtual void v34(); virtual void v38();
    virtual void SetPosition(const Vec3*);      // +0x38 (ret 4)
    virtual void SetOrientation(const Quat*);   // +0x3c (ret 4)
    virtual void v40(); virtual void v44();
    virtual void SetLocalExtents(const void*);  // +0x48
};

// The object stream is a stack object of 0xa14 bytes.
class cVarListSerializer
{
  public:
    bool Serialize(IOStream* stream);
    unsigned char mData[0xa14];
};

// A reference-counted object (the intrusive list node type).
class RefObj
{
  public:
    virtual void AddRef();              // +0x00
    virtual void Release();             // +0x04
    virtual bool IsValid();             // +0x2c
};

class cEgg
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

class cNest
{
  public:
    cNest();                                    // 0xc6a870
    ~cNest();                                   // 0xc6a970
    void RemoveOwner();                         // 0xc6a9c0
    void MoveNest(const Vec3& pos);             // 0xc6aab0 (ret 4)
    void AddFootprint();                        // 0xc6ab90
    bool LoadModel(void* modelWorld);           // 0xc6b410 (ret 4)
    void* AsInterface(int id);                  // 0xc6b390 (ret 4)
    int  CanSpawn();                            // 0xc6aa50

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

// cHerd: only the members touched here, with the retail byte offsets.
class cHerd
{
  public:
    void* GetProfileForGeneration(unsigned gen);        // 0xc6abf0 (ret 4)
    void  OnAnimalRemoved(void* animal);                // 0xc6b440 (ret 4)
    void  FindWateringHole();                           // 0xc6b5b0
    void  SpawnAnimalsIfUnderfilled();                  // 0xc6b540
    void  SetEnabled(u8 on);                            // 0xc6ace0 (ret 4)
    bool  UnbrokenEggsInNest();                         // 0xc6ac40
    void  ClearLocationStatus(int i);                   // 0xc6ac90 (ret 4)
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
    int mNumBabies;                             // 0x108
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

// A "near noun" whose +0x160 may hold a herd-like object; +0x218 is an enable byte.
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

// A herd animal noun (the object FUN_00c6af40 screens).
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

// ---------------------------------------------------------------------------------------------
// 0x00c6a550 -- SP::cEgg::Write
// ---------------------------------------------------------------------------------------------
// @ 0x00c6a550
bool SP::cEgg::Write(SP::IOStream* stream)
{
    u32 tag = 0x2a0349a;
    IWriter* writer = (IWriter*)stream->GetWriter();
    EA::IO::WriteUint32(writer->GetSink(), &tag, 1, 0);
    if (!FUN_00b18590((void*)this, stream))
        return false;
    if (!FUN_00c88a90((char*)this + 0x34, stream))
        return false;
    bool ok = FUN_00bfc4a0((char*)this + 0x120, stream) != 0;
    if (mpHerd != 0 && mpHerd->IsValid()) {
        mpHerd = 0;
        mpHerd->Release();
    }
    if (mpToHatch != 0 && mpToHatch->IsValid()) {
        mpToHatch = 0;
        mpToHatch->Release();
    }
    cVarListSerializer ser;
    FUN_00692f90(&ser, (void*)this, (void**)&gEggSerializerList, 0x1a80d26);
    if (ok && FUN_00692900(&ser, stream))
        return true;
    return false;
}

// ---------------------------------------------------------------------------------------------
// 0x00c6a670 -- SP::cEgg::SetState
// ---------------------------------------------------------------------------------------------
// @ 0x00c6a670
void SP::cEgg::SetState(SP::cEgg::EggState state)
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

// ---------------------------------------------------------------------------------------------
// 0x00c6a6e0 -- SP::cEgg::StateStep
// ---------------------------------------------------------------------------------------------
// @ 0x00c6a6e0
bool SP::cEgg::StateStep()
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

// ---------------------------------------------------------------------------------------------
// 0x00c6a7f0 -- FUN_00c6a7f0 (cSpatialObject extents setter, ret 8)
// ---------------------------------------------------------------------------------------------
// @ 0x00c6a7f0
void __fastcall FUN_00c6a7f0(void* ecx_this, void* edx, const float* ext, int flag)
{
    float e[6];
    e[0] = ext[0];
    e[1] = ext[1];
    e[2] = ext[3];
    e[3] = 0.0f;
    e[4] = ext[4];
    e[5] = (ext[2] < 0.0f ? -ext[2] : ext[2]) + ext[5];
    FUN_00c89160(ecx_this, e, flag);
    *(float*)((char*)ecx_this + 0x5c) = *(float*)((char*)ecx_this + 0x4c) * gHalf;
}

// ---------------------------------------------------------------------------------------------
// 0x00c6a870 -- SP::cNest::cNest
// ---------------------------------------------------------------------------------------------
// @ 0x00c6a870
SP::cNest::cNest()
{
    ((ThisStubs*)this)->A();                          // cGameData ctor
    ((ThisStubs*)((char*)this + 0x34))->B();          // cSpatialObject ctor
    ((ThisStubs*)((char*)this + 0x108))->C();         // cInteractionTarget ctor
    mbShowPlacement = 0;
    mp124 = 0;
    *(void**)this = (void*)0x1471ba0;
    *(void**)((char*)this + 4) = (void*)0x1471b8c;
    *(void**)((char*)this + 0x34) = (void*)0x1471ac8;
    *(void**)((char*)this + 0x108) = (void*)0x1471aac;
    mpOwner128 = 0;
    mpFootprint12c = 0;
}

// ---------------------------------------------------------------------------------------------
// 0x00c6a970 -- SP::cNest::~cNest
// ---------------------------------------------------------------------------------------------
// @ 0x00c6a970
SP::cNest::~cNest()
{
    *(void**)this = (void*)0x1471ba0;
    *(void**)((char*)this + 4) = (void*)0x1471b8c;
    *(void**)((char*)this + 0x34) = (void*)0x1471ac8;
    *(void**)((char*)this + 0x108) = (void*)0x1471aac;
    if (mpOwner128)
        mpOwner128->Release();
    ((ThisStubs*)((char*)this + 0x108))->D();         // cInteractionTarget dtor-ish
    ((ThisStubs*)((char*)this + 0x34))->E();          // cSpatialObject dtor-ish
    ((ThisStubs*)this)->F();                          // cGameData dtor
}

// ---------------------------------------------------------------------------------------------
// 0x00c6a9c0 -- SP::cNest::RemoveOwner
// ---------------------------------------------------------------------------------------------
// @ 0x00c6a9c0
void SP::cNest::RemoveOwner()
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

// ---------------------------------------------------------------------------------------------
// 0x00c6aa10 -- FUN_00c6aa10 (herd animal flag getter)
// ---------------------------------------------------------------------------------------------
// @ 0x00c6aa10
u8 __fastcall FUN_00c6aa10(void* ecx_this, void* edx)
{
    void* h = *(void**)((char*)ecx_this + 0xf4);
    if (h)
        return *(u8*)((char*)h + 0x84);
    return 0;
}
// ---------------------------------------------------------------------------------------------
// 0x00c6aa50 -- SP::cNest::CanSpawn
// ---------------------------------------------------------------------------------------------
// @ 0x00c6aa50
int SP::cNest::CanSpawn()
{
    cHerd* h = (cHerd*)mpOwner128;
    int prof = (int)((cSpeciesMgr*)FUN_00401090())->GetAvatarProfile();
    if (h->mSpeciesKey != (u32)prof && !h->mb191 && !h->mbEnabled) {
        void* p = FUN_00b3d4c0((char*)h + 0x98, 0, 0);
        if (FUN_00ba3f90(p, 0, 0) != 4)
            return 0;
    }
    return 1;
}

// ---------------------------------------------------------------------------------------------
// 0x00c6aab0 -- SP::cNest::MoveNest (ret 4)
// ---------------------------------------------------------------------------------------------
// @ 0x00c6aab0
void SP::cNest::MoveNest(const Vec3& pos)
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

// ---------------------------------------------------------------------------------------------
// 0x00c6ab90 -- SP::cNest::AddFootprint
// ---------------------------------------------------------------------------------------------
// @ 0x00c6ab90
void SP::cNest::AddFootprint()
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

// ---------------------------------------------------------------------------------------------
// 0x00c6abf0 -- SP::cHerd::GetProfileForGeneration (ret 4)
// ---------------------------------------------------------------------------------------------
// @ 0x00c6abf0
void* SP::cHerd::GetProfileForGeneration(unsigned gen)
{
    if ((int)gen < (mEvolvedKeysEnd - mEvolvedKeysBegin) / 0xc)
        return ((cSpeciesMgr*)FUN_00401090())->GetProfile((const void*)(mEvolvedKeysBegin + (int)gen * 0xc));
    return 0;
}

// ---------------------------------------------------------------------------------------------
// 0x00c6ac40 -- SP::cHerd::UnbrokenEggsInNest
// ---------------------------------------------------------------------------------------------
// @ 0x00c6ac40
bool SP::cHerd::UnbrokenEggsInNest()
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

// ---------------------------------------------------------------------------------------------
// 0x00c6ac90 -- SP::cHerd::ClearLocationStatus (ret 4)
// ---------------------------------------------------------------------------------------------
// @ 0x00c6ac90
void SP::cHerd::ClearLocationStatus(int i)
{
    if (i >= 0 && i < (int)(mLocationStatusEnd - mLocationStatus))
        mLocationStatus[i] = 0;
}

// ---------------------------------------------------------------------------------------------
// 0x00c6acc0 -- SP::cNearNoun::GetPosition
// ---------------------------------------------------------------------------------------------
// @ 0x00c6acc0
const SP::Vec3* SP::cNearNoun::GetPosition()
{
    if (mp160 != 0) {
        ISpatial* sp = (ISpatial*)((char*)mp160 + 0x34);
        return sp->GetPosition();
    }
    return (const Vec3*)((char*)this + 0x34);
}

// ---------------------------------------------------------------------------------------------
// 0x00c6ace0 -- SP::cHerd::SetEnabled (ret 4)
// ---------------------------------------------------------------------------------------------
// @ 0x00c6ace0
void SP::cHerd::SetEnabled(u8 on)
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

// ---------------------------------------------------------------------------------------------
// 0x00c6ad30 -- SP::cNearNoun::SetEnabled
// ---------------------------------------------------------------------------------------------
// @ 0x00c6ad30
void SP::cNearNoun::SetEnabled()
{
    if (mb190 == 0) {
        mb190 = 1;
        if (mp160)
            *(u8*)((char*)mp160 + 0x120) = 1;
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00c6ad60 -- FUN_00c6ad60 (herd location-state update)
// ---------------------------------------------------------------------------------------------
// @ 0x00c6ad60
void __fastcall FUN_00c6ad60(void* ecx_this, void* edx)
{
    cHerd* self = (cHerd*)ecx_this;
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

// ---------------------------------------------------------------------------------------------
// 0x00c6adc0 -- FUN_00c6adc0 (serialise an evolved-key vector, cdecl)
// ---------------------------------------------------------------------------------------------
// @ 0x00c6adc0
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

// ---------------------------------------------------------------------------------------------
// 0x00c6ae30 -- FUN_00c6ae30 (copy the viewer origin into a writer buffer, cdecl)
// ---------------------------------------------------------------------------------------------
// @ 0x00c6ae30
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

// ---------------------------------------------------------------------------------------------
// 0x00c6ae70 -- FUN_00c6ae70 (copy_if, cdecl: filter refs between two iterators)
// ---------------------------------------------------------------------------------------------
// @ 0x00c6ae70
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

// ---------------------------------------------------------------------------------------------
// 0x00c6af40 -- FUN_00c6af40 (screen a herd animal, cdecl)
// ---------------------------------------------------------------------------------------------
// @ 0x00c6af40
int __cdecl FUN_00c6af40(AnimalNoun* a, void* herdPtr)
{
    cHerd* herd = (cHerd*)herdPtr;
    if (!a)
        return 0;
    if (a->mbB5e)
        return 0;
    if (!FUN_00c0b770(a))
        return 0;
    if ((a->mFlagsB58 >> 8) & 1)
        return 0;
    if (a->mSpeciesKey != herd->mSpeciesKey)
        return 0;
    if ((a->mFlagsB58 >> 9) & 1) {
        const Vec3* p1 = ((cNearNoun*)FUN_00c04590(a))->GetPosition();
        const Vec3* p2 = a->spatialC0()->GetPosition();
        float dx = p2->x - p1->x;
        float dy = p2->y - p1->y;
        float dz = p2->z - p1->z;
        if (gFiftyF * gFiftyF <= dx * dx + dy * dy + dz * dz)
            return 0;
    }
    return 1;
}

// ---------------------------------------------------------------------------------------------
// 0x00c6b040 -- SP::cEgg::Update (ret 4)
// ---------------------------------------------------------------------------------------------
// @ 0x00c6b040
void SP::cEgg::Update(int dt)
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

// ---------------------------------------------------------------------------------------------
// 0x00c6b350 -- combatant-slot thunk (ret 0x14): step the egg machine, set damage state
// ---------------------------------------------------------------------------------------------
// @ 0x00c6b350
void __fastcall FUN_00c6b350(void* ecx_this, void* edx, int a1, int a2, int a3, int a4, int a5)
{
    void* egg = (char*)ecx_this - 0x120;
    if (((cEgg*)egg)->StateStep() != 0)
        *(int*)((char*)ecx_this + 0x34) = 2;
}

// ---------------------------------------------------------------------------------------------
// 0x00c6b390 -- SP::cNest::AsInterface (ret 4)
// ---------------------------------------------------------------------------------------------
// @ 0x00c6b390
void* SP::cNest::AsInterface(int id)
{
    if (id != 0x40ce1b1) {
        if (id == 0x1b92b27)
            return this;
        void* p = FUN_00b18460(id);
        if (!p) {
            p = FUN_00c884f0((char*)this + 0x34, id);
            if (!p)
                p = FUN_00ac0320((char*)this + 0x108, id);
        }
        return p;
    }
    void* avatar = FUN_00b1fdb0(NounManager());
    if (avatar) {
        int mine = mpOwner128 ? (int)((cHerd*)mpOwner128)->mSpeciesKey : 0;
        if (mine == (int)FUN_00c0bbd0(avatar))
            return this;
    }
    return 0;
}

// ---------------------------------------------------------------------------------------------
// 0x00c6b410 -- SP::cNest::LoadModel (ret 4)
// ---------------------------------------------------------------------------------------------
// @ 0x00c6b410
bool SP::cNest::LoadModel(void* modelWorld)
{
    bool ok = FUN_00c8a550((char*)this + 0x34, modelWorld) != 0;
    if (ok)
        AddFootprint();
    return ok;
}

// ---------------------------------------------------------------------------------------------
// 0x00c6b440 -- SP::cHerd::OnAnimalRemoved (ret 4)
// ---------------------------------------------------------------------------------------------
// @ 0x00c6b440
void SP::cHerd::OnAnimalRemoved(void* animal)
{
    if (mCreaturePersonality == animal) {
        if (mCreaturePersonality)
            *(u32*)((char*)(*(void**)((char*)mCreaturePersonality + 0xb4c)) + 0x5fc) &= 0xffbfffff;
        if (mCreaturePersonality) {
            RefObj* o = mCreaturePersonality;
            mCreaturePersonality = 0;
            o->Release();
        }
        int count = (int)((char*)mpHerdEnd - (char*)mpHerdBegin) / 4;
        for (int i = 0; i < count; ++i) {
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
        FUN_00c02c20(animal, 0);
        if (mpEggLayer) {
            RefObj* o = (RefObj*)mpEggLayer;
            mpEggLayer = 0;
            o->Release();
        }
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00c6b540 -- SP::cHerd::SpawnAnimalsIfUnderfilled
// ---------------------------------------------------------------------------------------------
// @ 0x00c6b540
void SP::cHerd::SpawnAnimalsIfUnderfilled()
{
    if (mbEnabled)
        return;
    int count = mHead - (int)((char*)mpHerdEnd - (char*)mpHerdBegin) / 4 - mTail;
    if (count <= 0)
        return;
    const Vec3* pos;
    if (mpNest)
        pos = ((ISpatial*)((char*)mpNest + 0x34))->GetPosition();
    else
        pos = (const Vec3*)((char*)this + 0x34);
    float radius = FUN_00c69f80(this);
    FUN_00c09fa0((void*)pos, (int)mSpeciesKey, count, radius);
}

// ---------------------------------------------------------------------------------------------
// 0x00c6b5b0 -- SP::cHerd::FindWateringHole
// ---------------------------------------------------------------------------------------------
// @ 0x00c6b5b0
void SP::cHerd::FindWateringHole()
{
    void* planet = PlanetModel();
    Vec3 out;
    out.x = gViewerOrigin[0];
    out.y = gViewerOrigin[1];
    out.z = gViewerOrigin[2];
    float dist = (float)mNumBabies;
    if (!(dist > gEpsilon))
        dist = gWaterSearchDist;
    const Vec3* pos;
    if (mpNest)
        pos = ((ISpatial*)((char*)mpNest + 0x34))->GetPosition();
    else
        pos = (const Vec3*)((char*)this + 0x34);
    if (FindClosestWater(planet, pos, dist, &out)) {
        mWateringHolePosition.x = out.x;
        mWateringHolePosition.y = out.y;
        mWateringHolePosition.z = out.z;
    }
}

}  // namespace SP
