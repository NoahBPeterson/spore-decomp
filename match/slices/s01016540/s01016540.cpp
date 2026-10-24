// match/slices/s01016540/s01016540.cpp
// Slice s01016540 -- cSPSimulatorWalkAround cluster + cSPCameraControllerSolarSystem Write/Read.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS- /Isrc/game/include

typedef unsigned int   u32;
typedef signed   int   i32;
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned long long u64;

// ---------------------------------------------------------------------------
// External free callees (globals / accessors)
// ---------------------------------------------------------------------------
void* __cdecl   SP_PlanetModel();                       // 0x00b3d350
void* __cdecl   SP_NounManager(int p);                  // 0x00b3d300 (ret 4)
void* __cdecl   FUN_00b3d470();                         // 0x00b3d470
void* __cdecl   FUN_00b3d3c0();                         // 0x00b3d3c0
void* __cdecl   FUN_00b3d310();                         // 0x00b3d310
void* __cdecl   FUN_00b3d230(int id);                   // 0x00b3d230 (ret 4)
void* __cdecl   FUN_00b3d4d0();                         // 0x00b3d4d0
void* __cdecl   SP_SimTicker();                         // 0x00b3d330
void* __cdecl   SP_GetUFOSimulator();                   // 0x00ffbe50
void* __cdecl   SP_App();                               // 0x0067dd10
void* __cdecl   SP_ConfigManager();                     // 0x0067dd30
void* __cdecl   SP_EffectsManager();                    // 0x0067ddd0
void* __cdecl   FUN_010666a0();                         // 0x010666a0
void* __cdecl   FUN_010408b0();                         // 0x010408b0
void* __cdecl   FUN_0067cac0(int a, int b);             // 0x0067cac0 (ret 8)
void* __cdecl   FUN_00fd9c60();                         // 0x00fd9c60
void* __cdecl   FUN_00c0ee60_sim(void* obj);            // 0x00c0ee60 (thiscall-style getter)
float* __cdecl  SP_GetPropertyAsFloat(void* prop);      // 0x0041ea70 (ret 4)
void   __cdecl  FUN_00572020(void* p, int a);           // 0x00572020 (ret 8)
void   __cdecl  copy_impl(void* first, void* last, void* dst); // 0x006782c0 (ret 0xc)
void   __cdecl  AudioSetListener3(void* a, float x, float y, float z); // 0x009fbc50 (ret 0x10)
float  __cdecl  FUN_01041cd0(float a, float b, int c);  // 0x01041cd0 (ret 0xc)
void*  __cdecl  FUN_00c0ee60_dummy();
void*  __cdecl  SP_SpaceGameGet(int a);                 // 0x01002bd0 (ret 4)
void   __cdecl  FUN_00b76d20(void* a, float f, int b, int c, int d); // 0x00b76d20 (ret 0x14)
void*  __cdecl   FUN_00b3d3b0();                        // 0x00b3d3b0
void*  __cdecl   FUN_00b3d420_p();                     // 0x00b3d420 (0-arg getter)
void*  __cdecl   FUN_00401090_p();                     // 0x00401090 (0-arg getter)
void   __cdecl   FUN_00aea5d0(void* end, void* val);    // 0x00aea5d0 (ret 8)
void   __cdecl   FUN_00b22930(void* noun);              // 0x00b22930 (ret 4)
void*  __cdecl   FUN_00c04590();                        // 0x00c04590

extern float g_15b6dd4;
extern float g_15b6dd8;
extern float g_1485544;    // 0.75f
extern float g_16dd3d0;
extern float g_16dd384;
extern float g_16dd3b4;
extern float g_16dd374;
extern float g_16dd3e8;
extern float g_16dd3ec;
extern float g_1485720;    // 1.0f
extern float g_13ec4d0;
extern float g_13ebca0;
extern float g_16dd3f0;
extern float g_16dd3f4;
extern float g_1471064;
extern char  g_1654c05;
extern char  g_169e380, g_169e381;
extern float g_169e384;

// ---------------------------------------------------------------------------
// Shared stub types
// ---------------------------------------------------------------------------
struct Vec3 { float x, y, z; };
struct Mat3 {
    void Assign(const void* src);  // 0x41cb40 ret 4
};

// A named game property.  Property lookups write the found Property* into an
// out slot; GetFloat() returns a pointer to the stored float.
struct Property {
    u8  pad_00[0x12];
    u16 mType_12;                       // +0x12
    float* GetFloat();                  // 0x0041ea70 ret 4
};

// The trigger manager (0x00b3d4d0).
struct TriggerMgr {
    u8  pad_00[0x2c];
    int mState_2c;                      // +0x2c
};

// The object returned by 0x00b3d310 (a gameplay manager).
struct GameMgr {
    u8  pad_00[0x20];
    int mField_20;                      // +0x20
};

// The avatar handle object referenced by cSPSimulatorWalkAround::mpAvatar's
// +0xb54 slot.
struct AvatarHandle {
    u8   pad_00[0x80];
    float mFloat_80;                    // +0x80
};

static inline char* vpt(void* o) { return *(char**)o; }

struct Blk64 { u32 w[16]; };

// A reference-counted object: vtable slot 0 = AddRef, slot 1 = Release.
struct RefObj {
    void AddRef() { (**(void(__thiscall**)(void*))vptr)(this); }
    void Release() { (**(void(__thiscall**)(void*))(vptr + 4))(this); }
private:
    void** vptr; // +0x00
};

// cVarListSerializer (0xa14 bytes of state)
struct cVarListSerializer {
    u32  mData[0xa14 / 4];
    void Ctor(void* a, void* b, u32 c);      // 0x00692f90 ret 0xc
    void Serialize(void* o);                 // 0x00692900 ret 4
    u8   Read(void* o);                      // 0x00693e10 ret 4
};

void __cdecl EA_IO_WriteUint32(void* stream, void* val, int n, int b); // 0x0093aa70 ret 0x10
void __cdecl EA_IO_ReadInt32(void* stream, void* out, int n, int b);   // 0x0093a780 ret 0x10

// A keyed stream (vtable slot 0x20 = GetOutStream, 0x18 = GetIO, 0x3c = GetVersion).
struct Stream {
    void* GetSub_20() { return (**(void*(__thiscall**)(void*))(*(void***)this + 8))(this); }
private:
    char pad0[4];
};

// The space-game simulator (cSPSimulatorSpaceGame); only the accessor is
// exercised by this slice.
struct cSPSimulatorSpaceGame {
    void* GetPlayerInventory();              // 0x00a1ad60 ret 4
};

// The UFO player inventory (cSPGameDataUFO).
struct UFOInv {
    void FUN_00c3daa0(float f);              // 0x00c3daa0 ret 4
    void PopToDestination();                 // 0x00c37e60
    void FUN_00c37120();                     // 0x00c37120
    void StartPlayerDeathSequence();         // 0x00c3c520
    void SetPlanetDestination(void* dest);   // 0x00ffc350 ret 0x14
    float mCollisionTimer_540;               // +0x540
    u8    mFlag_74c;                         // +0x74c
};

// The walking-around simulator (cSPSimulatorWalkAround).  Members are named by
// role and retail offset; the dev-PDB layout is uniformly shifted by 4 here.
struct SimTimer {                            // cSPTimer, at +0x20
    void  Stop();                            // 0x00bc3110
    void  Restart();                         // 0x00bc3130
    u8    IsRunning();                       // 0x00feba90
    u64   GetElapsed();                      // 0x00bc3190
};

struct cSPSimulatorWalkAround {
    u32   mFlags_0x0;                        // +0x00 (base vptr, unused here)
    u8    pad_04[0xc];
    bool  mIsWalkingAround;                  // +0x10
    void* mpAvatar;                          // +0x14  AutoRefCount<cSPCreatureAnimal>
    void* mpStrategy;                        // +0x18  AutoRefCount<cWalkAroundInputStrategy>
    i32   mBeamingState;                     // +0x1c
    SimTimer mBeamingTimer;                  // +0x20
    u8    pad_24[0x1c];                      // 0x24..0x3f
    float mRescueDelay;                      // +0x40
    void* mpX_44;                            // +0x44
    // eastl::vector<AutoRefCount<...>> at +0x48 (0x14 bytes)
    void** mHighLODPlantsBegin;              // +0x48
    void** mHighLODPlantsEnd;                // +0x4c
    void** mHighLODPlantsCap;                // +0x50
    u8    pad_54[8];                         // 0x54..0x5b
    void** mHighLODObstaclesBegin;           // +0x5c
    void** mHighLODObstaclesEnd;             // +0x60
    void** mHighLODObstaclesCap;             // +0x64
    u8    pad_68[8];                         // 0x68..0x6f

    // members
    void RemoveHighLODPlant(void* plant, char flag);   // 01016540 ret 8
    u8   ClearOldestPlant();                           // 01016630
    void SetHighLODPlant(void* plant);                 // 010166c0 ret 4
    void ShutdownForGame();                            // 010168c0
    void FUN_01016950();                               // 01016950
    void FUN_01016ad0();                               // 01016ad0
    void FUN_01016e50(void* a);                        // 01016e50 ret 4

    // external thiscall callees
    void  RemoveNoun0(void* noun);                     // 0x00b225d0 ret 4
    float FUN_00b7e4d0();                              // 0x00b7e4d0 (planet-model getter)
    void* GetPlayerInventory();                        // 0x00a1ad60
    void  AnimStop();                                  // 0x00b72640
    void  LoadStateMachine();                          // 0x00fe1a20
    void  ClearDirty();                                // 0x00b78860
    void  ShowCameraControls(int a);                   // 0x01065c30 ret 4
};

struct cGameNounManager {
    void RemoveNoun(void* noun);                       // 0x00b225d0 ret 4
};

// Sub-object at plant+0x34 with a vtable (a cGameData / asset object).
struct ObstacleData {
    void* mpVtbl_00;                                   // +0x00
    u8  pad_04[0x30];                                  // 0x04..0x33
    u32 mFlags_34;                                     // +0x34 (bit2 used)
    u8  pad_38[0xc];                                   // 0x38..0x43
    float mFloat_44;                                   // +0x44
    u8  pad_48[0xc];                                   // 0x48..0x53
    u32 mFlag_54;                                      // +0x54
    u8  pad_58[0x24];                                  // 0x58..0x7b
    void* mpKey_7c;                                    // +0x7c
    void FUN_00b73de0(int a);                          // 0x00b73de0 ret 4
    void FUN_00b73e70_desc(void* out);                 // 0x00b73e70 ret 4
};

// A high-LOD plant / obstacle record.
struct Plant {
    void* mpVtbl;                                      // +0x00
    u8  pad_04[0x30];
    u32 mFlags_34;                                     // +0x34
    u8  pad_38[0xc];
    float mFloat_44;                                   // +0x44
    u8  mFlag_54;                                      // +0x54
    u8  pad_55[0x27];
    void* mpKey_7c;                                    // +0x7c
    void* GetDesc();                                   // 0x00b73e70 ret 4 (thiscall)
    void FUN_00b73de0(int a);                          // 0x00b73de0 ret 4
};

// The avatar creature (mpAvatar).  Only the +0xb54 slot is read by this slice.
struct AvatarFields {
    u8    pad_00[0xb54];
    void* mpHandle_b54;                                // +0xb54
};

// Descriptor returned by Plant::GetDesc() (0x38 bytes).
struct PlantDesc {
    u16 a;            // +0x00
    u16 b;            // +0x02
    float x;          // +0x04
    float y;          // +0x08
    float z;          // +0x0c
    float w;          // +0x10
    Mat3  m;          // +0x14 (0x24 bytes)
};

// A newly created plant object (from FUN_00b2b430).  The obstacle record is
// embedded at +0x34.
struct NewPlant {
    void* mpVtbl_0;                                    // +0x00
    u8  pad_04[0x30];                                  // 0x04..0x33
    ObstacleData mData_34;                             // +0x34 (embedded)
    float mFloat_44;                                   // +0x44
    void FUN_00c3e270(float f);                        // 0x00c3e270 ret 4
};

// The plant-species manager (found through the global getter 0xb3d3b0).
struct SpeciesMgr {
    void* FUN_00b2b430(Vec3 v, int a, void* profile, void* key, void* desc); // ret 0x1c
};

struct SpeciesProfile {
    u8 pad_00[0x90];
    float mField_90;                                   // +0x90
};

// Lookups reached through the 0-arg getters FUN_00b3d420 / FUN_00401090.
struct PlantSpeciesManager {
    SpeciesProfile* GetSpeciesFromID(void* key);       // 0x00b90410 ret 4
};
struct EditorSpeciesManager {
    SpeciesProfile* GetPlantProfile(void* key);        // 0x004df440 ret 4
};

struct cSPCameraControllerSolarSystem {
    // vtable-using base (cDefaultCameraController) occupies 0x00..0x67
    u8  pad_00[0x68];
    Vec3 mVec_68;                                      // +0x68 (saved/desired)
    Vec3 mVec_74;                                      // +0x74 (current)
    u8   pad_80[4];                                    // 0x80..0x83
    void* mpProperty_84;                               // +0x84 (property manager)
    u8   pad_88[8];                                    // 0x88..0x8f
    float mFloat_90;                                   // +0x90
    u8  pad_94[0x64];                                  // 0x94..0xf7
    Blk64 mBlk_f8;                                     // +0xf8 (0x40 bytes)
    u8   pad_138[4];                                   // 0x138..0x13b
    u8   mFlag_13c;                                    // +0x13c
    u8   mFlag_13d;                                    // +0x13d
    u8   pad_13e[2];                                   // 0x13e..0x13f
    u8   mFlag_140;                                    // +0x140
    u8   pad_141[0x53];                                // 0x141..0x193
    u8   mFlag_194;                                    // +0x194
    u8   pad_195[3];                                   // 0x195..0x197
    u32  mFlags_198;                                   // +0x198

    // members
    void FUN_010170e0();                               // 010170e0
    void FUN_01017170(float f);                        // 01017170 ret 4
    void FUN_010171b0(float f);                        // 010171b0 ret 4
    void FUN_01017200(void* out);                      // 01017200 ret 4
    u32  FUN_01017260();                               // 01017260
    void FUN_01017270(char b);                         // 01017270 ret 4
    void Write(void* stream);                          // 01017290 ret 4
    u8   Read(void* stream);                           // 01017300 ret 4
    float FUN_01017410(int a);                         // 01017410 ret 4
};

// ===========================================================================
// @ 0x01017010
// ===========================================================================
float FUN_01017010(int a)
{
    if (a != 2)
        return g_15b6dd4;
    return g_15b6dd8 * g_1485544;
}

// ===========================================================================
// @ 0x01017030
// ===========================================================================
float FUN_01017030(int a)
{
    float v = 0.0f;
    if (a == 1)
        v = g_16dd3d0;
    else if (a == 2)
        v = g_16dd384;
    return v;
}

// ===========================================================================
// @ 0x01017070
// ===========================================================================
float FUN_01017070(int a)
{
    float v = 0.0f;
    if (a == 1)
        v = g_16dd3b4;
    else if (a == 2)
        v = g_16dd374;
    return v;
}

// ===========================================================================
// @ 0x01017220
// ===========================================================================
float FUN_01017220()
{
    return ((cSPSimulatorWalkAround*)SP_PlanetModel())->FUN_00b7e4d0() + g_16dd3e8;
}

// ===========================================================================
// @ 0x01017240
// ===========================================================================
float FUN_01017240()
{
    return ((cSPSimulatorWalkAround*)SP_PlanetModel())->FUN_00b7e4d0() + g_16dd3ec;
}

// ===========================================================================
// @ 0x01017150
// ===========================================================================
void FUN_01017150()
{
    cSPSimulatorSpaceGame* sim = (cSPSimulatorSpaceGame*)SP_GetUFOSimulator();
    UFOInv* inv = (UFOInv*)sim->GetPlayerInventory();
    inv->FUN_00c37120();
}

// ===========================================================================
// @ 0x01017390
// ===========================================================================
void FUN_01017390()
{
    u8* p = (u8*)FUN_00b3d470() + 0xc4;
    if (*(int*)p == 0)
        return;
    u8* p2 = (u8*)FUN_00b3d470() + 0xc4;
    void* q = *(void**)p2;
    (**(void(__thiscall**)(void*, int))(vpt(q) + 0xc))(q, 1);
    u8* base = (u8*)FUN_00b3d470();
    void*& slot = *(void**)(base + 0xc4);
    void* r = slot;
    if (r == 0)
        return;
    slot = 0;
    (**(void(__thiscall**)(void*))(vpt(r) + 4))(r);
}
// ===========================================================================
// @ 0x010170e0
// ===========================================================================
void cSPCameraControllerSolarSystem::FUN_010170e0()
{
    (**(void(__thiscall**)(void*))(vpt(this) + 0x58))(this);
    mFlag_194 = 0;
    float elapsed = ((cSPSimulatorWalkAround*)SP_PlanetModel())->FUN_00b7e4d0();
    cSPSimulatorSpaceGame* sim = (cSPSimulatorSpaceGame*)SP_GetUFOSimulator();
    UFOInv* inv = (UFOInv*)sim->GetPlayerInventory();
    inv->FUN_00c3daa0(g_16dd3f0 + elapsed);
    inv->PopToDestination();
    inv->FUN_00c3daa0(g_16dd3f4 + elapsed);
    mFlag_13d = 1;
}

// ===========================================================================
// @ 0x01017260
// ===========================================================================
u32 cSPCameraControllerSolarSystem::FUN_01017260()
{
    return ~(mFlags_198 >> 1) & 1;
}

// ===========================================================================
// @ 0x01017170
// ===========================================================================
void cSPCameraControllerSolarSystem::FUN_01017170(float f)
{
    if (mFlag_140 == 0 && mFlag_13d == 0) {
        mFlags_198 |= 2;
        mFloat_90 = f + mFloat_90;
    }
}

// ===========================================================================
// @ 0x010171b0
// ===========================================================================
void cSPCameraControllerSolarSystem::FUN_010171b0(float f)
{
    if (mFlag_140 == 0 && mFlag_13d == 0) {
        mFlags_198 |= 1;
        mVec_74.y = f + mVec_74.y;
    }
}

// ===========================================================================
// @ 0x01017200
// ===========================================================================
void cSPCameraControllerSolarSystem::FUN_01017200(void* out)
{
    *(Blk64*)out = mBlk_f8;
}

// ===========================================================================
// @ 0x01017270
// ===========================================================================
void cSPCameraControllerSolarSystem::FUN_01017270(char b)
{
    mFlag_13c = b;
    if (b == 0)
        mFlags_198 |= 2;
}

// ===========================================================================
// @ 0x01017290
// ===========================================================================
void cSPCameraControllerSolarSystem::Write(void* stream)
{
    void* p = (void*)(**(int(__thiscall**)(void*))(vpt(stream) + 0x20))(stream);
    u32 tag = 0x303154cc;
    void* io = (void*)(**(int(__thiscall**)(void*))(vpt(p) + 0x18))(p);
    EA_IO_WriteUint32(io, &tag, 1, 0);
    cVarListSerializer buf;
    buf.Ctor(this, (void*)0x15b6e28, 0x1a80d26);
    buf.Serialize(stream);
}

// ===========================================================================
// @ 0x01017300
// ===========================================================================
u8 cSPCameraControllerSolarSystem::Read(void* stream)
{
    cVarListSerializer buf;
    u32 tmp;
    void* p = (void*)(**(int(__thiscall**)(void*))(vpt(stream) + 0x20))(stream);
    void* io = (void*)(**(int(__thiscall**)(void*))(vpt(p) + 0x18))(p);
    EA_IO_ReadInt32(io, &tmp, 1, 0);
    buf.Ctor(this, (void*)0x15b6e28, 0x1a80d26);
    u8 ok = buf.Read(stream);
    if ((**(u32(__thiscall**)(void*))(vpt(stream) + 0x3c))(stream) < 0x220001) {
        mVec_74 = mVec_68;
    }
    return ok;
}

// ===========================================================================
// @ 0x01017410
// ===========================================================================
float cSPCameraControllerSolarSystem::FUN_01017410(int a)
{
    float f0 = g_1485720;      // property 0x195e020
    void* prop = mpProperty_84;
    if (prop != 0) {
        Property* out;
        if ((**(u8(__thiscall**)(void*, u32, Property**))(*(void***)prop + 9))(prop, 0x195e020, &out) &&
            out->mType_12 == 0xd)
            f0 = *out->GetFloat();
    }
    float f1 = g_13ec4d0;      // property 0x195e021
    prop = mpProperty_84;
    if (prop != 0) {
        Property* out;
        if ((**(u8(__thiscall**)(void*, u32, Property**))(*(void***)prop + 9))(prop, 0x195e021, &out) &&
            out->mType_12 == 0xd)
            f1 = *out->GetFloat();
    }
    float f2 = g_1485720;      // property 0x195e022
    prop = mpProperty_84;
    if (prop != 0) {
        Property* out;
        if ((**(u8(__thiscall**)(void*, u32, Property**))(*(void***)prop + 9))(prop, 0x195e022, &out) &&
            out->mType_12 == 0xd)
            f2 = *out->GetFloat();
    }
    float f3 = g_1485720;      // property 0x195e023
    prop = mpProperty_84;
    if (prop != 0) {
        Property* out;
        if ((**(u8(__thiscall**)(void*, u32, Property**))(*(void***)prop + 9))(prop, 0x195e023, &out) &&
            out->mType_12 == 0xd)
            f3 = *out->GetFloat();
    }
    float r = FUN_01041cd0(f0, f1, a);
    if (r <= 0.0f)
        r = 0.0f;
    if (1.0f <= r)
        r = 1.0f;
    return ((f3 - f2) * r + f2) * g_13ebca0;
}

// ===========================================================================
// @ 0x01016540
// ===========================================================================
void cSPSimulatorWalkAround::RemoveHighLODPlant(void* plant, char flag)
{
    void** begin = mHighLODPlantsBegin;
    void** end   = mHighLODPlantsEnd;
    void** obst  = mHighLODObstaclesBegin;
    if (plant != 0)
        (**(void(__thiscall**)(void*))(*(void***)plant + 0))(plant);
    ((cGameNounManager*)SP_NounManager((int)plant))->RemoveNoun(plant);
    void** p = begin;
    void** o = obst;
    for (;;) {
        if (p == end)
            goto cleanup;
        if (*p == plant) {
            void** e = mHighLODPlantsEnd;
            if ((char*)p + 4 < (char*)e)
                copy_impl((char*)p + 4, e, p);
            mHighLODPlantsEnd = (void**)((char*)mHighLODPlantsEnd - 4);
            void* last = *(void**)((char*)mHighLODPlantsEnd);
            if (last != 0)
                (**(void(__thiscall**)(void*))(*(void***)last + 1))(last);
            ObstacleData* ob = (ObstacleData*)*o;
            if (!(**(u8(__thiscall**)(void*))(*(void***)ob + 0xb))(ob) && ob->mFlag_54 != 0) {
                ob->FUN_00b73de0(flag == 0);
                if (flag == 0)
                    ob->mFlags_34 |= 2;
                else
                    ob->mFlags_34 &= 0xfffffffd;
            }
            void** e2 = mHighLODObstaclesEnd;
            if ((char*)o + 4 < (char*)e2)
                copy_impl((char*)o + 4, e2, o);
            mHighLODObstaclesEnd = (void**)((char*)mHighLODObstaclesEnd - 4);
            void* last2 = *(void**)((char*)mHighLODObstaclesEnd);
            if (last2 != 0)
                (**(void(__thiscall**)(void*))(*(void***)last2 + 1))(last2);
            goto cleanup;
        }
        ++p;
        ++o;
    }
cleanup:
    if (plant != 0)
        (**(void(__thiscall**)(void*))(*(void***)plant + 1))(plant);
}

// ===========================================================================
// @ 0x01016630
// ===========================================================================
u8 cSPSimulatorWalkAround::ClearOldestPlant()
{
    void** e = mHighLODPlantsBegin;
    if (e == mHighLODPlantsEnd)
        return 0;
    if (mHighLODObstaclesBegin == mHighLODObstaclesEnd)
        return 0;
    void* plant = *e;
    ((cGameNounManager*)SP_NounManager((int)plant))->RemoveNoun(plant);
    void** p5 = mHighLODPlantsBegin;
    void** p6 = mHighLODPlantsEnd;
    if ((char*)p5 + 4 < (char*)p6)
        copy_impl((char*)p5 + 4, p6, p5);
    mHighLODPlantsEnd = (void**)((char*)mHighLODPlantsEnd - 4);
    void* q = *(void**)mHighLODPlantsEnd;
    if (q != 0)
        (**(void(__thiscall**)(void*))(*(void***)q + 1))(q);
    void** r5 = mHighLODObstaclesBegin;
    void** r6 = mHighLODObstaclesEnd;
    if ((char*)r5 + 4 < (char*)r6)
        copy_impl((char*)r5 + 4, r6, r5);
    mHighLODObstaclesEnd = (void**)((char*)mHighLODObstaclesEnd - 4);
    void* s = *(void**)mHighLODObstaclesEnd;
    if (s != 0)
        (**(void(__thiscall**)(void*))(*(void***)s + 1))(s);
    return 1;
}

// ===========================================================================
// @ 0x010166c0
// ===========================================================================
void cSPSimulatorWalkAround::SetHighLODPlant(void* plant)
{
    Plant* pa = (Plant*)plant;
    if (pa == 0)
        return;
    if ((u32)((char*)mHighLODPlantsEnd - (char*)mHighLODPlantsBegin) / 4 == 8)
        ClearOldestPlant();

    PlantDesc desc;
    PlantDesc* d = (PlantDesc*)pa->GetDesc();
    desc.a = d->a;
    desc.b = d->b;
    desc.x = d->x;
    desc.y = d->y;
    desc.z = d->z;
    desc.w = d->w;
    desc.m.Assign(&d->m);

    if ((pa->mFlags_34 >> 2 & 1) != 0) {
        SpeciesProfile* sp =
            ((PlantSpeciesManager*)FUN_00b3d420_p())->GetSpeciesFromID(&pa->mpKey_7c);
        desc.w = desc.w / sp->mField_90;
        desc.b = (u16)(desc.b + 1);
    }
    pa->FUN_00b73de0(1);

    SpeciesProfile* profile =
        ((EditorSpeciesManager*)FUN_00401090_p())->GetPlantProfile(&pa->mpKey_7c);
    if (profile == 0)
        return;

    Vec3 v = { desc.x, desc.y, desc.z };
    SpeciesMgr* mgr = (SpeciesMgr*)FUN_00b3d3b0();
    NewPlant* np = (NewPlant*)mgr->FUN_00b2b430(v, 0, profile, &pa->mpKey_7c, &desc);
    np->FUN_00c3e270(pa->mFloat_44);

    ObstacleData* data = &np->mData_34;
    void* r1 = (**(void*(__thiscall**)(ObstacleData*))(*(void***)data + 0x2c))(data);
    void* r2 = (**(void*(__thiscall**)(ObstacleData*, int))(*(void***)data + 0x2b))(data, 1);
    (**(void(__thiscall**)(void*, void*))(*(void***)r1 + 0x2d))(r1, r2);

    if (mHighLODPlantsEnd < mHighLODPlantsCap) {
        *mHighLODPlantsEnd = np;
        mHighLODPlantsEnd = mHighLODPlantsEnd + 1;
        (**(void(__thiscall**)(void*))(*(void***)np + 0))(np);
    } else {
        FUN_00aea5d0(mHighLODPlantsEnd, np);
    }
    (**(void(__thiscall**)(void*))(*(void***)np + 1))(np);

    if (mHighLODObstaclesEnd < mHighLODObstaclesCap) {
        *mHighLODObstaclesEnd = pa;
        mHighLODObstaclesEnd = mHighLODObstaclesEnd + 1;
        (**(void(__thiscall**)(void*))(*(void***)pa + 0))(pa);
    } else {
        FUN_00aea5d0(mHighLODObstaclesEnd, pa);
    }
    (**(void(__thiscall**)(void*))(*(void***)pa + 1))(pa);
}

// ===========================================================================
// @ 0x010168c0
// ===========================================================================
void cSPSimulatorWalkAround::ShutdownForGame()
{
    void* ticker = SP_SimTicker();
    (**(void(__thiscall**)(void*, void*))(*(void***)ticker + 0x15))(ticker, this);
    while (ClearOldestPlant())
        ;
    void* p = mpX_44;
    if (p != 0) {
        FUN_00572020(p, 1);
        mpX_44 = 0;
    }
    void* a = mpAvatar;
    if (a != 0) {
        (**(void(__thiscall**)(void*, int))(*(void***)a + 0x32))(a, 1);
        a = mpAvatar;
        if (a != 0) {
            mpAvatar = 0;
            (**(void(__thiscall**)(void*))(*(void***)a + 1))(a);
        }
    }
    void* b = mpStrategy;
    if (b != 0) {
        (**(void(__thiscall**)(void*))(*(void***)b + 3))(b);
        void* c = mpStrategy;
        if (c != 0) {
            void* sub = (char*)c + 0x3c;
            mpStrategy = 0;
            (**(void(__thiscall**)(void*))(*(void***)sub + 2))(sub);
        }
    }
}

// ===========================================================================
// @ 0x01016950
// ===========================================================================
void cSPSimulatorWalkAround::FUN_01016950()
{
    void* p0 = mpX_44;
    if (p0 != 0)
        FUN_00572020(p0, 1);
    if (mpAvatar != 0) {
        if (FUN_00b3d3c0() != 0) {
            void* a = ((void*(__stdcall*)(int))FUN_00b3d3c0)(0x1654c05);
            (**(void(__thiscall**)(void*))(*(void***)a + 0))(a);
        }
    }
    if (mpAvatar != 0) {
        if (FUN_00c0ee60_dummy() != 0) {
            void* av = mpAvatar;
            (**(void(__thiscall**)(void*, int, int, int))(*(void***)av + 0x21))(av, 0, 0, 0);
        }
    }
    void* hints = FUN_0067cac0(1, 1);
    (**(void(__thiscall**)(void*, int, int))(*(void***)hints + 0))(hints, 1, 1);
    ((GameMgr*)FUN_00b3d310())->mField_20 = 2;
    while (ClearOldestPlant())
        ;
    void* ui = FUN_010666a0();
    if (ui != 0)
        (**(void(__thiscall**)(void*, int))(*(void***)ui + 0))(ui, 1);
    void* b = FUN_00b3d230(0x1103193);
    (**(void(__thiscall**)(void*))(*(void***)b + 0))(b);
    void* app = SP_App();
    void* av1 = (**(void*(__thiscall**)(void*))(*(void***)app + 0x14))(app);
    void* av2 = (**(void*(__thiscall**)(void*))(*(void***)av1 + 0xe))(av1);
    if (av2 != 0)
        (**(void(__thiscall**)(void*, int))(*(void***)av2 + 3))(av2, 0x303154cd);
    mIsWalkingAround = false;
    if (((void*)FUN_00fd9c60()) != 0) {
        void* cm = SP_ConfigManager();
        void* v = (**(void*(__thiscall**)(void*, int))(*(void***)cm + 0xc))(cm, 0x679b880);
        void* x = ((void*(__stdcall*)(void*))FUN_00fd9c60)(v);
        (**(void(__thiscall**)(void*))(*(void***)x + 0))(x);
    }
    mBeamingState = 0;
    mBeamingTimer.Stop();
    (**(void(__thiscall**)(void*))(*(void***)((char*)FUN_00b3d3c0())))(FUN_00b3d3c0());
    void* em = SP_EffectsManager();
    (**(void(__thiscall**)(void*, int, int))(*(void***)em + 0x26))(em, 0x11, 0);
    void* em2 = SP_EffectsManager();
    (**(void(__thiscall**)(void*, int, int))(*(void***)em2 + 0x26))(em2, 0x14, 1);
    void* sim = SP_GetUFOSimulator();
    UFOInv* inv = (UFOInv*)((void*(__thiscall*)(void*))(*(void***)sim + 0x10))(sim);
    if (inv->mCollisionTimer_540 <= 0.0f)
        inv->StartPlayerDeathSequence();
    void* r = FUN_010408b0();
    (**(void(__thiscall**)(void*))(*(void***)r + 0))(r);
    void* sg = SP_SpaceGameGet(0xe);
    (**(void(__thiscall**)(void*))(*(void***)sg + 0))(sg);
}

// ===========================================================================
// @ 0x01016e50
// ===========================================================================
void cSPSimulatorWalkAround::FUN_01016e50(void* param_2)
{
    if (mBeamingState != 0)
        FUN_01016ad0();
    if (mIsWalkingAround && mpStrategy != 0) {
        void* o = mpStrategy;
        (**(void(__thiscall**)(void*, void*))(*(void***)o + 4))(o, param_2);
    }
    if (mpAvatar != 0) {
        if (g_169e381 == 0 || g_169e380 == 0) {
            g_169e384 = 0.0f;
        } else {
            void* o = (char*)mpAvatar + 0xc0;
            g_169e384 = (**(float(__thiscall**)(void*))(*(void***)o + 0x32))(o);
        }
    }
    if (mpAvatar != 0) {
        if (FUN_00b3d3c0() != 0) {
            int st = ((TriggerMgr*)FUN_00b3d4d0())->mState_2c;
            if (st != 1 && st != 2) {
                void* o = (char*)mpAvatar + 0xc0;
                float tmp[6];
                float* pf = (**(float*(__thiscall**)(void*, void*))(*(void***)o + 0x1b))(o, tmp);
                float f1 = pf[0], f2 = pf[4], f3 = pf[5];
                float f4 = pf[3], f5 = pf[1], f6 = pf[2];
                float r = (**(float(__thiscall**)(void*, int, int, int))(*(void***)o + 0x1c))(o, 7, 1, 0);
                FUN_00b76d20(tmp, r, 7, 1, 0);
                if (mpX_44 != 0) {
                    AudioSetListener3(mpX_44,
                                      (f1 + f4) * g_1471064,
                                      (f2 + f5) * g_1471064,
                                      (f3 + f6) * g_1471064);
                }
            }
        }
    }
}

// ===========================================================================
// @ 0x01016ad0
// ===========================================================================
void cSPSimulatorWalkAround::FUN_01016ad0()
{
    int state = mBeamingState;
    SimTimer* tm = &mBeamingTimer;
    if (state == 1) {
        if (!tm->IsRunning()) {
            tm->Restart();
            return;
        }
        long long e = (long long)tm->GetElapsed();
        if (e < 0) e = -e;
        if ((float)e > mRescueDelay * 1000.0f) {
            tm->Stop();
            mBeamingState = 2;
            if (mpAvatar != 0 && SP_GetUFOSimulator() != 0) {
                void* o = (char*)mpAvatar + 0xc0;
                (**(void(__thiscall**)(void*))(*(void***)o + 0xb))(o);
                void* res = (**(void*(__thiscall**)(void*, int, int, int, int))(*(void***)o + 0xb))(o, 0, 1, 0, 0);
                ((UFOInv*)((void*(__thiscall*)(void*))(*(void***)SP_GetUFOSimulator() + 0x10))(SP_GetUFOSimulator()))->SetPlanetDestination(res);
            }
        }
    } else if (state == 2) {
        if (!tm->IsRunning()) {
            void* ufo = SP_GetUFOSimulator();
            UFOInv* inv = ufo ? (UFOInv*)((void*(__thiscall*)(void*))(*(void***)ufo + 0x10))(ufo) : 0;
            if (inv != 0) {
                if (inv->mFlag_74c == 0) {
                    if (mpAvatar != 0) {
                        void* o = (char*)mpAvatar + 0xc0;
                        (**(void(__thiscall**)(void*))(*(void***)o + 0xb))(o);
                        void* res = (**(void*(__thiscall**)(void*, int, int, int, int))(*(void***)o + 0xb))(o, 0, 1, 0, 0);
                        inv->SetPlanetDestination(res);
                    }
                } else {
                    tm->Restart();
                    if (mpAvatar != 0) {
                        void* o = (char*)mpAvatar + 0xc0;
                        (**(void(__thiscall**)(void*, int))(*(void***)o + 0x27))(o, 3);
                    }
                }
            }
        } else {
            if (mpAvatar != 0) {
                void* o = (char*)mpAvatar + 0xc0;
                if ((**(u8(__thiscall**)(void*))(*(void***)o + 0x2b))(o)) {
                    long long e = (long long)tm->GetElapsed();
                    if (e < 0) e = -e;
                    if ((float)e < 2000.0f) {
                        void* m = ((AvatarFields*)mpAvatar)->mpHandle_b54;
                        long long e2 = (long long)tm->GetElapsed();
                        if (e2 < 0) e2 = -e2;
                        ((AvatarHandle*)m)->mFloat_80 = (float)((2.0 - (double)e2 * 0.001) * 0.5);
                    } else {
                        (**(void(__thiscall**)(void*, int))(*(void***)o + 0x27))(o, 0);
                        if (FUN_00b3d3c0() != 0) {
                            void* a = ((void*(__stdcall*)(int))FUN_00b3d3c0)(0x1654c05);
                            (**(void(__thiscall**)(void*))(*(void***)a + 0))(a);
                        }
                        void* u = FUN_00c04590();
                        void* u2 = SP_NounManager((int)u);
                        FUN_00b22930(u2);
                        void* pi = mpAvatar;
                        if (pi != 0) {
                            mpAvatar = 0;
                            (**(void(__thiscall**)(void*))(*(void***)pi + 1))(pi);
                        }
                        mIsWalkingAround = false;
                        void* o18 = mpStrategy;
                        (**(void(__thiscall**)(void*))(*(void***)o18 + 3))(o18);
                        void* o18b = mpStrategy;
                        if (o18b != 0) {
                            mpStrategy = 0;
                            void* sub = (char*)o18b + 0x3c;
                            (**(void(__thiscall**)(void*))(*(void***)sub + 2))(sub);
                        }
                    }
                }
            }
            long long e = (long long)tm->GetElapsed();
            if (e < 0) e = -e;
            if ((float)e >= 4000.0f) {
                FUN_01016950();
                return;
            }
        }
    } else if (state == 3) {
        if (!tm->IsRunning()) {
            tm->Restart();
            void* o = (char*)mpAvatar + 0xc0;
            (**(void(__thiscall**)(void*, int))(*(void***)o + 0x27))(o, 2);
            return;
        }
        long long e = (long long)tm->GetElapsed();
        if (e < 0) e = -e;
        if ((float)e >= 4000.0f) {
            mBeamingState = 0;
            tm->Stop();
            void* o = (char*)mpAvatar + 0xc0;
            (**(void(__thiscall**)(void*, int))(*(void***)o + 0x27))(o, 0);
            return;
        }
    }
}
