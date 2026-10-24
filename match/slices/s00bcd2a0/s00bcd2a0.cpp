// Slice s00bcd2a0 -- UpdateFromSubobject (0x00bcdd00, 177 bytes, ret 8).
//
// Takes the sub-object's offset vector (vslot 0x5c, out parameter) and its position (vslot 0x2c),
// scales the offset by (vslot 0x70 + 10.0f), writes pos + offset * scale to the first output and
// 10.0f to the second output.
#include "types.h"

struct Vector3 {
    float x, y, z;
};

class cSubObject {
public:
    virtual void VS00();
    virtual void VS04();
    virtual void VS08();
    virtual void VS0c();
    virtual void VS10();
    virtual void VS14();
    virtual void VS18();
    virtual void VS1c();
    virtual void VS20();
    virtual void VS24();
    virtual void VS28();
    virtual Vector3* GetPosition();                 // +0x2c
    virtual void VS30();
    virtual void VS34();
    virtual void VS38();
    virtual void VS3c();
    virtual void VS40();
    virtual void VS44();
    virtual void VS48();
    virtual void VS4c();
    virtual void VS50();
    virtual void VS54();
    virtual void VS58();
    virtual void ComputeOffset(Vector3* pOut);      // +0x5c
    virtual void VS60();
    virtual void VS64();
    virtual void VS68();
    virtual void VS6c();
    virtual float GetScale();                       // +0x70
};

class cUpdater {
public:
    char pad00[0x34];
    cSubObject mSub;           // +0x34

    void UpdateFromSubobject(Vector3* pOut, float* pScaleOut);   // 0x00bcdd00 (thiscall, ret 8)
};

void cUpdater::UpdateFromSubobject(Vector3* pOut, float* pScaleOut) {
    Vector3 local;
    mSub.ComputeOffset(&local);
    Vector3* pPos = mSub.GetPosition();
    float px = pPos->x;
    float py = pPos->y;
    float pz = pPos->z;
    float k = mSub.GetScale() + 10.0f;
    *pScaleOut = 10.0f;
    pOut->x = local.x * k + px;
    pOut->y = local.y * k + py;
    pOut->z = local.z * k + pz;
}

// ===========================================================================
// Slice s00bcd2a0 -- Spore "Simulator" cGameData / cBuilding / cTurret region
// (retail 0x00bcd2a0..0x00bce0a0).  Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
//
// The generated SP::cGameData.h flavour disagrees with retail for these
// objects; the touched sub-objects are declared as local stubs whose offsets
// are read off the disassembly and named by role.  `vc()` fetches a virtual
// slot by byte offset so the retail `mov edx,[vtbl+off]; call edx` shape is
// preserved.
// ===========================================================================
#include <math.h>

typedef unsigned int   u32;
typedef unsigned char  u8;
typedef unsigned short u16;

struct Vec3 { float x, y, z, w; };

// helper: virtual function pointer at vtable byte offset
static void* vc(void* obj, int off) { return ((void**)*(void**)obj)[off / 4]; }

// ---------------------------------------------------------------------------
// External callees (retail VAs in comments).  Declared only so MSVC emits a
// real `call rel32` and cannot fold the calls away.
// ---------------------------------------------------------------------------
void*  __cdecl FUN_0093aa70(void* a, void* b, void* c, void* d); // 0x93aa70 EA::IO::WriteUint32
void*  __cdecl FUN_0093a780(void* a, void* b, void* c, void* d); // 0x93a780 EA::IO::ReadInt32
void*  __cdecl FUN_00692f90(void* a, void* b, void* c, void* d); // 0x692f90 cVarListSerializer ctor
void*  __cdecl FUN_00692900(void* a, void* b);                   // 0x692900 cVarListSerializer::Serialize
void*  __cdecl FUN_00693e10(void* a, void* b);                   // 0x693e10 cVarListSerializer::Read
void*  __cdecl FUN_00bcc350(void* a);                            // 0xbcc350 ISimulatorSerializable Write helper
void*  __cdecl FUN_00bcc400(void* a);                            // 0xbcc400 ISimulatorSerializable Read helper
// Simulator::cCommunity::func5Ch -- __thiscall, takes a float on the stack.
struct cCommunityBase { void func5Ch(float v); };
void*  __cdecl FUN_00695b40(void* a, void* b, void* c);          // 0x695b40 set-class helper
void*  __cdecl FUN_00b5b800();                                   // 0xb5b800 SP::GetCurrentGameMode
void*  __cdecl FUN_01021090();                                   // 0x1021090 GetPlayerEmpireID
void*  __cdecl FUN_01021260();                                   // 0x1021260 cSPLivingUniverse::GetActivePlanet
void*  __cdecl FUN_01021370();                                   // 0x1021370 cSPLivingUniverse::GetPlayerHomePlanet
void*  __cdecl FUN_0102f810();                                   // 0x102f810 economy tuning singleton
void*  __cdecl FUN_0102fb70(void* a);                            // 0x102fb70 GetHomeWorldBuildingMultiplier
void*  __cdecl FUN_00c88810(void* a, void* b);                   // 0xc88810 Simulator::cSpatialObject::SetModelKey
void*  __cdecl FUN_00bd9e50(void* a);                            // 0xbd9e50 model-key refresh
void*  __cdecl FUN_00b18550(void* a, void* b);                   // 0xb18550 SP::cGameData::SetGameDataOwner2
void*  __cdecl FUN_00bfc720(void* a);                            // 0xbfc720
void*  __cdecl FUN_00ac0450(void* a);                            // 0xac0450
void*  __cdecl FUN_00c8b2e0(void* a);                            // 0xc8b2e0 Simulator::cSpatialObject
void*  __cdecl FUN_00bd9bf0(void* a);                            // 0xbd9bf0 SP::cCity::GetCivilization
void*  __cdecl FUN_00b3d300();                                   // 0xb3d300 SP::NounManager
void*  __cdecl FUN_00b25f40(void* a, void* b);                   // 0xb25f40 cGameNounManager lookup
double __cdecl FUN_0059da80(float a);                            // 0x59da80 RandomRange
void*  __cdecl FUN_00a68fb0(void* a, u32 b);                     // 0xa68fb0 RandomUint32Uniform
void*  __cdecl FUN_00b3d480(float a, float b, float c, float d, float e, float f); // 0xb3d480
void*  __cdecl FUN_00d5cfd0(void* a, void* b, void* c, void* d, void* e, void* f); // 0xd5cfd0
void*  __cdecl FUN_00b3d350(void* a);                            // 0xb3d350 SP::PlanetModel
void*  __cdecl FUN_00b8bb70(void* a, void* b, void* c);          // 0xb8bb70 cPlanetModel::FindClosestWater
void*  __cdecl FUN_0108db30(void* a);                            // 0x108db30 water-body list
void*  __cdecl FUN_00b81470(void* a, void* b, void* c);          // 0xb81470 cPlanetModel::DistanceBetweenPoints
void*  __cdecl FUN_00c00b00(void* a, void* b, void* c);          // 0xc00b00
void*  __cdecl FUN_00bf02b0(void* a, void* b);                   // 0xbf02b0 city_flags_update
void*  __cdecl FUN_00c6f660(void* a);                            // 0xc6f660
void*  __cdecl FUN_00b3d310(void* a, void* b, void* c);          // 0xb3d310
void*  __cdecl FUN_00b452f0(void* a, void* b, void* c);          // 0xb452f0
void*  __cdecl FUN_00b4c600(void* a, void* b, void* c);          // 0xb4c600
void*  __cdecl FUN_00b225d0(void* a, void* b);                   // 0xb225d0 cGameNounManager::RemoveNoun
void*  __cdecl FUN_00b18660(void* a);                            // 0xb18660 SP::cGameData::cGameData
void*  __cdecl FUN_00b184c0(void* a);                            // 0xb184c0 SP::cGameData::~cGameData
void*  __cdecl FUN_00c43860(void* a);                            // 0xc43860
void*  __cdecl FUN_00c432e0(void* a);                            // 0xc432e0
void*  __cdecl FUN_00ac03d0(void* a);                            // 0xac03d0 SP::cInteractionTarget ctor
void*  __cdecl FUN_00ac0520(void* a);                            // 0xac0520 SP::cInteractionTarget dtor
void*  __cdecl FUN_00abfe50(void* a);                            // 0xabfe50
void*  __cdecl FUN_00abfec0(void* a);                            // 0xabfec0
void*  __cdecl FUN_00bfd4e0(void* a);                            // 0xbfd4e0 SP::cCombatant::cCombatant
void*  __cdecl FUN_00bfcd00(void* a);                            // 0xbfcd00 SP::cCombatant::~cCombatant
void*  __cdecl FUN_00b63890(void* a);                            // 0xb63890 SP::cGonzagoTimer ctor
void*  __cdecl FUN_00b638b0(void* a);                            // 0xb638b0 SP::cGonzagoTimer dtor

// ---------------------------------------------------------------------------
// Read-only globals referenced by these functions.
// ---------------------------------------------------------------------------
extern void*  PTR_s_field_name_0156deb4;   // 0x156deb4  serializer field-name row
extern void*  DAT_01570858;                // 0x1570858  set-class payload
extern void*  DAT_01601760;                // 0x1601760  cRandomGlobal
extern void*  DAT_01186577;                // 0x1186577  lookup key
extern void*  DAT_018c43e8;                // 0x18c43e8  city cast tag
extern void*  DAT_01654c05;                // 0x1654c05  SPACE game-mode tag
extern float  DAT_0168b66c, DAT_0168b670, DAT_0168b674;  // default offset triplet
extern float  DAT_0169c0fc, DAT_0169c100;  // wrapper constants (a)
extern float  DAT_0169c07c, DAT_0169c080;  // wrapper constants (b)
extern float  DAT_0169c0a8, DAT_0169c0ac;  // wrapper constants (c)
extern float  DAT_0156def0;                // model direction scale
extern void*  PTR_FUN_01466c14;
extern void*  vtbl_Simulator_cTurret;      // 0x1466e90
extern void*  PTR_FUN_01466e7c;            // 0x1466e7c
extern void*  PTR_FUN_01466d80;            // 0x1466d80
extern void*  PTR_FUN_01466d74;            // 0x1466d74
extern void*  PTR_FUN_01466d58;            // 0x1466d58
extern void*  PTR_FUN_01466cf0;            // 0x1466cf0
extern void*  PTR_FUN_01466c88;            // 0x1466c88
extern void*  PTR_FUN_01466c60;            // 0x1466c60

// cVarListSerializer: a 0xa14-byte stack-local serializer object.
struct VarListSerializer { u8 mData_000[0xa14]; };

// ---------------------------------------------------------------------------
// Simulator::cGameData -- the shared base.  Only the slots touched here are
// named; everything else is padding.  +0x34 opens the embedded cSpatialObject,
// +0x1f0 holds the owned "game data" pointer (city / planet object).
// ---------------------------------------------------------------------------
struct cGameData {
    u8   pad_000[0x34];
    u8   pad_034[0xd4];        // 0x34..0x108  embedded cSpatialObject
    void* mpVftbl_108;         // 0x108
    u8   pad_10c[0x14];        // 0x10c..0x120
    void* mpField_120;         // 0x120
    u8   pad_124[0xc8];        // 0x124..0x1ec
    void* mpField_1ec;         // 0x1ec  sub-container
    void* mpOwner_1f0;         // 0x1f0  owned object (city)
    u8   pad_1f4[0x8];         // 0x1f4..0x1fc
    u8   mbField_1fc;          // 0x1fc

    bool Write(void* pArchive);            // 0x00bcd2a0
    bool Read(void* pArchive);             // 0x00bcd340
};

// ---------------------------------------------------------------------------
// cCommunity-flavoured object touched by 00bcd3f0.
// ---------------------------------------------------------------------------
struct cCommunityT {
    u8    pad_000[0x64];
    float mField_64;           // 0x64  compared against the incoming float
    u8    pad_068[0x2a4];      // 0x68..0x30c
    u8    mbField_30c;         // 0x30c  set to 1 after func5Ch

    void SetFloat(float v);    // 0x00bcd3f0
};

// ---------------------------------------------------------------------------
// The building/city object whose owner pointer sits at +0x1f0.
// +0x224 holds its current model key, +0x230 the boolean it caches.
// ---------------------------------------------------------------------------
struct cOwnerT {
    u8    pad_000[0x34];       // 0x00..0x34 cGameData
    u8    pad_034[0xd4];       // 0x34..0x108
    void* mpVftbl_108;         // 0x108
    u8    pad_10c[0x14];       // 0x10c..0x120
    void* mpField_120;         // 0x120
    u8    pad_124[0xc8];       // 0x124..0x1ec
    void* mpField_1ec;         // 0x1ec
    void* mpOwner_1f0;         // 0x1f0  owned object (city)
    u8    pad_1f4[0x8];        // 0x1f4..0x1fc
    u8    mbField_1fc;         // 0x1fc
    u8    pad_1fd[0x27];       // 0x1fd..0x224
    u8    mModelKey_224[0xc];  // 0x224..0x230 model key (12 bytes)
    u8    mbFlag_230;          // 0x230

    void  SetOwnerCity2(void* pCity);    // 0x00bcd5b0
    void  RemoveOwner();                 // 0x00bcd5f0
    void  RemoveOwnerFull();             // 0x00bcddc0
    void  SetFlag(char on);              // 0x00bcd550
    void  SetModelKey2(void* pKey);      // 0x00bcd4e0
    void* GetOwnerCivilization();        // 0x00bcd630
    void  UpdateCityFlags(void* pObj);   // 0x00bcd890
    bool  func7Ch(void* pPlanet, void* pPoint, float threshold); // 0x00bcda00
    void  RefreshModelKeys();            // 0x00bcda90
    void  GetNextWanderNode(char mode, int count); // 0x00bcd690
};

// ---------------------------------------------------------------------------
// Simulator::cTurret -- the widest object in the slice.
// ---------------------------------------------------------------------------
struct cTurret {
    u8 mBase_000[0x7a0];
    cTurret();                 // 0x00bcded0
    ~cTurret();                // 0x00bce0a0
};

// ---------------------------------------------------------------------------
// 00bcd2a0 -- Simulator::ISimulatorSerializable::Write
// ---------------------------------------------------------------------------
// @ 0x00bcd2a0
bool cGameData::Write(void* pArchive) {
    void* v1 = ((void* (__thiscall*)(void*))vc(pArchive, 0x20))(pArchive);
    u32 id = 0x70704db;
    u32 handle = ((u32 (__thiscall*)(void*))vc(v1, 0x18))(v1);
    FUN_0093aa70((void*)handle, &id, (void*)1, 0);

    bool b = ((bool (__thiscall*)(void*))FUN_00bcc350)(pArchive) != 0;
    if (b) {
        b = ((bool (__thiscall*)(void*))FUN_00bcc350)(pArchive) != 0;
    }
    VarListSerializer ser;
    FUN_00692f90(&ser, this, &PTR_s_field_name_0156deb4, (void*)0x1a80d26);
    if (b) {
        if (FUN_00692900(&ser, pArchive)) return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// 00bcd340 -- Simulator::ISimulatorSerializable::Read
// ---------------------------------------------------------------------------
// @ 0x00bcd340
bool cGameData::Read(void* pArchive) {
    void* v1 = ((void* (__thiscall*)(void*))vc(pArchive, 0x20))(pArchive);
    u32 id;
    u32 handle = ((u32 (__thiscall*)(void*))vc(v1, 0x18))(v1);
    FUN_0093a780((void*)handle, &id, (void*)1, 0);

    bool b = ((bool (__thiscall*)(void*))FUN_00bcc400)(pArchive) != 0;
    if (b) {
        b = ((bool (__thiscall*)(void*))FUN_00bcc400)(pArchive) != 0;
    }
    VarListSerializer ser;
    FUN_00692f90(&ser, this, &PTR_s_field_name_0156deb4, (void*)0x1a80d26);
    if (b) {
        if (FUN_00693e10(&ser, pArchive)) return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// 00bcd3f0 -- cCommunity float setter.
// ---------------------------------------------------------------------------
// @ 0x00bcd3f0
void cCommunityT::SetFloat(float v) {
    if (v != mField_64) {
        ((cCommunityBase*)this)->func5Ch(v);
        mbField_30c = 1;
    }
}

// ---------------------------------------------------------------------------
// 00bcd450 -- attach the "cCombatant" class tag to a non-null object.
// ---------------------------------------------------------------------------
// @ 0x00bcd450
bool __cdecl FUN_00bcd450(u32 param_1, u32* param_2) {
    if (*param_2 != 0) {
        ((void (__thiscall*)(void*, void*, void*, void*))FUN_00695b40)(
            (void*)param_1, (void*)*param_2, &DAT_01570858, (void*)L"cCombatant");
    }
    return true;
}

// ---------------------------------------------------------------------------
// 00bcd480 -- home-world building multiplier divisor (x87 return).
// ---------------------------------------------------------------------------
// @ 0x00bcd480
float __cdecl FUN_00bcd480_(int empireID, float fallback, float value) {
    if (FUN_00b5b800() == (void*)&DAT_01654c05) {
        if (empireID == (int)FUN_01021090()) {
            int divisor = 1;
            int activePlanet = *(int*)((u8*)FUN_01021260() + 0x13c);
            if ((int)FUN_01021370() == activePlanet) {
                divisor = ((int (__thiscall*)(void*))FUN_0102fb70)(FUN_0102f810());
            }
            return value / (float)divisor;
        }
    }
    return fallback;
}

// ---------------------------------------------------------------------------
// 00bcd4e0 -- model-key compare / cache / tail-call SetModelKey.
// ---------------------------------------------------------------------------
// @ 0x00bcd4e0
void cOwnerT::SetModelKey2(void* pKey) {
    u32* k = (u32*)pKey;
    (void)k;
    if (((u32*)pKey)[0] != *(u32*)((u8*)this + 0x90) ||
        ((u32*)pKey)[1] != *(u32*)((u8*)this + 0x94) ||
        ((u32*)pKey)[2] != *(u32*)((u8*)this + 0x98)) {
        if ((((u32*)pKey)[2] & 0xff00) != 0x7e00) {
            *(u32*)((u8*)this + 0x1f0) = ((u32*)pKey)[0];
            *(u32*)((u8*)this + 0x1f4) = ((u32*)pKey)[1];
            *(u32*)((u8*)this + 0x1f8) = ((u32*)pKey)[2];
        }
        if (*(u8*)((u8*)this + 0x1fc) == 0) {
            return ((void (__thiscall*)(void*, void*))FUN_00c88810)(this, pKey);
        }
    }
}

// ---------------------------------------------------------------------------
// 00bcd550 -- model-key / visibility toggle.
// ---------------------------------------------------------------------------
// @ 0x00bcd550
void cOwnerT::SetFlag(char on) {
    if (on != (char)mbFlag_230) {
        void* pKey;
        u32 key[3];
        if (on != 0) {
            key[1] = 0;
            key[2] = 0;
            pKey = key;
            key[0] = 0xd1bf030c;
        } else {
            pKey = (u8*)this + 0x224;
        }
        ((void (__thiscall*)(void*, void*))FUN_00c88810)((u8*)this + 0x34, pKey);
        void* owner = mpOwner_1f0;
        mbFlag_230 = (u8)on;
        if (owner != 0) {
            ((void (__thiscall*)(void*))FUN_00bd9e50)(owner);
        }
    }
}

// ---------------------------------------------------------------------------
// 00bcd5b0 -- Simulator::cBuilding::SetOwnerCity2 (refcounted owner swap).
// ---------------------------------------------------------------------------
// @ 0x00bcd5b0
void cOwnerT::SetOwnerCity2(void* pCity) {
    ((void (__thiscall*)(void*, void*))FUN_00b18550)(this, pCity);
    void* prev = mpOwner_1f0;
    if (pCity != prev) {
        if (pCity != 0) {
            ((void (__thiscall*)(void*))vc(pCity, 0))(pCity);   // AddRef
        }
        mpOwner_1f0 = pCity;
        if (prev != 0) {
            ((void (__thiscall*)(void*))vc(prev, 4))(prev);     // Release
        }
    }
}

// ---------------------------------------------------------------------------
// 00bcd5f0 -- Simulator::cGameData::RemoveOwner (compact variant).
// ---------------------------------------------------------------------------
// @ 0x00bcd5f0
void cOwnerT::RemoveOwner() {
    ((void (__thiscall*)(void*))FUN_00bfc720)((u8*)this + 0x120);
    ((void (__thiscall*)(void*))FUN_00ac0450)((u8*)this + 0x108);
    ((void (__thiscall*)(void*))FUN_00c8b2e0)((u8*)this + 0x34);
    void* p = mpOwner_1f0;
    if (p != 0) {
        mpOwner_1f0 = 0;
        ((void (__thiscall*)(void*))vc(p, 4))(p);
    }
}

// ---------------------------------------------------------------------------
// 00bcd630 -- resolve the owner city's civilization.
// ---------------------------------------------------------------------------
// @ 0x00bcd630
void* cOwnerT::GetOwnerCivilization() {
    if (mpOwner_1f0 == 0) return 0;
    void* pCity = ((void* (__thiscall*)(void*))vc(this, 0x30))(this);
    if (pCity != 0) {
        void* type = ((void* (__thiscall*)(void*))vc(pCity, 0x20))(pCity);
        if (type != (void*)&DAT_018c43e8) pCity = 0;
    } else {
        pCity = 0;
    }
    int id = ((int (__thiscall*)(void*))vc(this, 0x4c))(this);
    if (id == -1) {
        return ((void* (__thiscall*)(void*))FUN_00bd9bf0)(pCity);
    }
    int id2 = ((int (__thiscall*)(void*))vc(this, 0x4c))(this);
    return ((void* (__thiscall*)(void*, void*))FUN_00b25f40)(FUN_00b3d300(), (void*)id2);
}

// ---------------------------------------------------------------------------
// 00bcd690 -- wander-node spawn (PDB candidate SP::CitizenTree::GetNextWanderNode).
// ---------------------------------------------------------------------------
// @ 0x00bcd690
void cOwnerT::GetNextWanderNode(char mode, int count) {
    if (!((bool (__thiscall*)(void*))vc((u8*)this + 0x34, 0x48))((u8*)this + 0x34))
        return;

    u32 kind;
    if (mode == 0) {
        if (count != 0) return;
        if ((float)FUN_0059da80(1.0f) >= 0.33f) return;
        kind = 1;
        count = 2;
    } else {
        kind = 2;
        count = 5;
    }

    float ox = DAT_0168b66c;
    float oy = DAT_0168b670;
    float oz = DAT_0168b674;
    float px = ox, py = oy, pz = oz;

    if (mode != 1 && *(u32*)((u8*)this + 0x308) != *(u32*)((u8*)this + 0x30c)) {
        u32 span = *(u32*)((u8*)this + 0x30c) - *(u32*)((u8*)this + 0x308);
        u32 i = (u32)FUN_00a68fb0(&DAT_01601760, span / 0x38);
        u8* e = (u8*)(*(u32*)((u8*)this + 0x308) + i * 0x38);
        px = *(float*)(e + 4);
        py = *(float*)(e + 8);
        pz = *(float*)(e + 0xc);
        float s = (float)FUN_0059da80(5.0f) + 4.0f;
        ox = *(float*)(e + 0x20) * s;
        oy = *(float*)(e + 0x24) * s;
        oz = *(float*)(e + 0x28) * s;
    } else {
        Vec3 tmp;
        float* r = (float*)((void* (__thiscall*)(void*, Vec3*))vc((u8*)this + 0x120, 0x20))(
            (u8*)this + 0x120, &tmp);
        float* q = (float*)((void* (__thiscall*)(void*))vc((u8*)this + 0x34, 0x2c))((u8*)this + 0x34);
        px = r[0] + q[0];
        py = r[1] + q[1];
        pz = r[2] + q[2];
    }

    void* eff = FUN_00b3d480(px, py, pz, ox, oy, oz);
    u32 id = ((u32 (__thiscall*)(void*))vc(this, 0x4c))(this);
    FUN_00d5cfd0((void*)kind, (void*)count, (void*)id, &eff, &eff, &eff);
}

// ---------------------------------------------------------------------------
// 00bcd890 -- update the owner city flag/civilization state.
// ---------------------------------------------------------------------------
// @ 0x00bcd890
void cOwnerT::UpdateCityFlags(void* pObj) {
    u8 found = 0;
    void* value = (void*)0xffffffff;
    if (pObj == 0) return;

    void* a = ((void* (__thiscall*)(void*, void*))vc(pObj, 0x5c))(pObj, (void*)0x137e8e0);
    if (a != 0 && *(int*)((u8*)a + 0xb20) == 0) {
        found = 1;
        value = ((void* (__thiscall*)(void*))vc((u8*)a + 0x508, 0x10))((u8*)a + 0x508);
    }
    void* b = ((void* (__thiscall*)(void*, void*))vc(pObj, 0x5c))(pObj, (void*)0xb033b403);
    if (b != 0) {
        found = 1;
        value = ((void* (__thiscall*)(void*))vc(b, 0x4c))(b);
    }
    void* c = ((void* (__thiscall*)(void*, void*))vc(pObj, 0x5c))(pObj, (void*)0xd0036e08);
    if (c == 0) {
        if (!found) return;
    } else {
        value = ((void* (__thiscall*)(void*))vc(c, 0x4c))(c);
    }
    if (*(int*)((u8*)this + 0xd0) == 0) return;

    void* s = ((void* (__thiscall*)(void*))vc(pObj, 8))(pObj);
    float* pos = (float*)((void* (__thiscall*)(void*))vc(s, 0x2c))(s);
    Vec3 v;
    v.x = pos[0]; v.y = pos[1]; v.z = pos[2]; v.w = pos[3];
    void* civ = FUN_00bd9bf0(*(void**)((u8*)this + 0xd0));
    FUN_00bf02b0(civ, value);
    FUN_00c00b00((void*)0, value, &v);
}

// ---------------------------------------------------------------------------
// 00bcd970 -- water-distance check for a planet point.
// ---------------------------------------------------------------------------
// @ 0x00bcd970
bool __cdecl FUN_00bcd970(void* pPlanet, float dist, void* pPoint) {
    if (pPoint == 0) return false;
    dist = dist + 2.0f;
    Vec3 tmp;
    void* model = FUN_00b3d350(pPlanet);
    u8 ok = (u8)(((char (__thiscall*)(void*, float, Vec3*))FUN_00b8bb70)(model, dist, &tmp) != 0);
    if (ok != 0) return false;

    u32* p = (u32*)FUN_0108db30(pPoint);
    u32 cur = p[0];
    if (cur == p[1]) return true;
    do {
        Vec3 d;
        void* m = FUN_00b3d350(pPlanet);
        ((void (__thiscall*)(void*, void*, Vec3*))FUN_00b81470)(m, (void*)cur, &d);
        if (d.x > *(float*)(cur + 0xc)) {
            cur += 0x14;
        } else {
            return false;
        }
    } while (cur != p[1]);
    return true;
}

// ---------------------------------------------------------------------------
// 00bcda00 -- Simulator::cBuilding::func7Ch (distance gate).
// ---------------------------------------------------------------------------
// @ 0x00bcda00
bool cOwnerT::func7Ch(void* pPlanet, void* pPoint, float threshold) {
    if (mpOwner_1f0 == 0) return false;
    Vec3 key;
    ((void (__thiscall*)(void*, Vec3*))vc(mpOwner_1f0, 0x5c))(mpOwner_1f0, &key);
    void* model = FUN_00b3d350(pPlanet);
    float dist;
    ((void (__thiscall*)(void*, void*, void*, float*))FUN_00b81470)(model, &key, pPoint, &dist);
    float radius = ((float (__thiscall*)(void*))vc(mpOwner_1f0, 0x60))(mpOwner_1f0);
    if (threshold < radius) {
        return FUN_00bcd970(pPlanet, dist, pPoint);
    }
    return false;
}

// ---------------------------------------------------------------------------
// 00bcda90 -- building model-key refresh over the +0x1ec container.
// ---------------------------------------------------------------------------
// @ 0x00bcda90
void cOwnerT::RefreshModelKeys() {
    if (mpField_1ec == 0) return;
    for (;;) {
        int idx = ((int (__thiscall*)(void*, int, int))vc(mpField_1ec, 0x6c))(mpField_1ec, 0, 8);
        if (idx == -1) break;
        void* entry = ((void* (__thiscall*)(void*, int))vc(mpField_1ec, 0x60))(mpField_1ec, idx);
        if (entry == 0) continue;
        void* obj = ((void* (__thiscall*)(void*, void*))vc(*(void**)((u8*)entry + 0xc), 0xc))(
            *(void**)((u8*)entry + 0xc), (void*)0x73905ae);
        if (obj == 0) continue;
        ((void (__thiscall*)(void*))vc(obj, 4))(obj);
        ((void (__thiscall*)(void*, void*))vc(mpField_1ec, 0x78))(mpField_1ec, obj);
        void* a = FUN_00c6f660(obj);
        if (a == 0) {
            ((void (__thiscall*)(void*))vc(obj, 8))(obj);
            continue;
        }
        void* t = ((void* (__thiscall*)(void*, void*))vc(a, 0xc))(a, &DAT_01186577);
        if (t == 0) {
            ((void (__thiscall*)(void*))vc(obj, 8))(obj);
            continue;
        }
        u8* self34 = (u8*)this + 0x34;
        ((void (__thiscall*)(void*, void*))vc(t, 0x38))(t,
            ((void* (__thiscall*)(void*))vc(self34, 0x2c))(self34));
        ((void (__thiscall*)(void*, void*))vc(t, 0x3c))(t,
            ((void* (__thiscall*)(void*))vc(self34, 0x30))(self34));
        *(u8*)((u8*)t + 0x71) = 0;
        float* v = (float*)((void* (__thiscall*)(void*))vc(self34, 0x2c))(self34);
        float inv = 1.0f / (float)sqrt((double)(v[0] * v[0] + v[1] * v[1] + v[2] * v[2] + 1e-8f));
        Vec3 n;
        ((void (__thiscall*)(void*, Vec3*))vc(self34, 0x5c))(self34, &n);
        Vec3 n2;
        ((void (__thiscall*)(void*, Vec3*))vc(self34, 0x5c))(self34, &n2);
        float ax = n2.x + n.x;
        float ay = n2.y + n.y;
        float az = n2.z + n.z;
        float inv2 = 1.0f / (float)sqrt((double)(ax * ax + ay * ay + az * az + 1e-8f));
        Vec3 dir;
        dir.x = (ax * inv2) * DAT_0156def0;
        dir.y = (ay * inv2) * DAT_0156def0;
        dir.z = (az * inv2) * DAT_0156def0;
        dir.w = 0.0f;
        FUN_00b3d310(t, &dir, 0);
        FUN_00b452f0(t, &dir, 0);
        FUN_00b3d310(self34, t, (void*)0x40000000);
        FUN_00b4c600(self34, t, (void*)0x40000000);
        (void)inv;
        ((void (__thiscall*)(void*))vc(obj, 8))(obj);
    }
}

// ---------------------------------------------------------------------------
// 00bcddc0 -- Simulator::cGameData::RemoveOwner (full variant).
// ---------------------------------------------------------------------------
// @ 0x00bcddc0
void cOwnerT::RemoveOwnerFull() {
    if (*(void**)((u8*)this + 0x344) != 0) {
        ((void (__thiscall*)(void*, void*))FUN_00b225d0)(FUN_00b3d300(), *(void**)((u8*)this + 0x344));
        void* n2 = *(void**)((u8*)this + 0x344);
        *(void**)((u8*)this + 0x344) = 0;
        if (n2 != 0) {
            ((void (__thiscall*)(void*))vc(n2, 4))(n2);
        }
    }
    ((void (__thiscall*)(void*))FUN_00bfc720)((u8*)this + 0x120);
    ((void (__thiscall*)(void*))FUN_00ac0450)((u8*)this + 0x108);
    ((void (__thiscall*)(void*))FUN_00c8b2e0)((u8*)this + 0x34);
    void* p = *(void**)((u8*)this + 0x1f0);
    if (p != 0) {
        *(void**)((u8*)this + 0x1f0) = 0;
        return ((void (__thiscall*)(void*))vc(p, 4))(p);
    }
}

// ---------------------------------------------------------------------------
// 00bcde40 / 00bcde70 / 00bcdea0 -- wrappers over FUN_00bcd480.
// ---------------------------------------------------------------------------
// @ 0x00bcde40
float __cdecl FUN_00bcde40(u32 param_1) {
    return FUN_00bcd480_(param_1, DAT_0169c0fc, DAT_0169c100);
}

// @ 0x00bcde70
float __cdecl FUN_00bcde70(u32 param_1) {
    return FUN_00bcd480_(param_1, DAT_0169c07c, DAT_0169c080);
}

// @ 0x00bcdea0
float __cdecl FUN_00bcdea0(u32 param_1) {
    return FUN_00bcd480_(param_1, DAT_0169c0a8, DAT_0169c0ac);
}

// ---------------------------------------------------------------------------
// 00bcded0 -- Simulator::cTurret::cTurret.
// ---------------------------------------------------------------------------
// @ 0x00bcded0
cTurret::cTurret() {
    u8* self = (u8*)this;
    ((void (__thiscall*)(void*))FUN_00b18660)(self);
    ((void (__thiscall*)(void*))FUN_00c43860)(self + 0x34);
    ((void (__thiscall*)(void*))FUN_00ac03d0)(self + 0x504);
    ((void (__thiscall*)(void*))FUN_00abfe50)(self + 0x51c);
    ((void (__thiscall*)(void*))FUN_00bfd4e0)(self + 0x588);
    *(void**)(self + 0x650) = &PTR_FUN_01466c14;
    ((void (__thiscall*)(void*))FUN_00b63890)(self + 0x660);
    *(void**)(self)         = &vtbl_Simulator_cTurret;
    *(void**)(self + 4)     = &PTR_FUN_01466e7c;
    *(void**)(self + 0x34)  = &PTR_FUN_01466d80;
    *(void**)(self + 0x108) = &PTR_FUN_01466d74;
    *(void**)(self + 0x504) = &PTR_FUN_01466d58;
    *(void**)(self + 0x51c) = &PTR_FUN_01466cf0;
    *(void**)(self + 0x588) = &PTR_FUN_01466c88;
    *(void**)(self + 0x650) = &PTR_FUN_01466c60;
    *(u32*)(self + 0x680) = 0;
    *(u32*)(self + 0x684) = 0;
    *(u32*)(self + 0x688) = 0;
    *(u32*)(self + 0x68c) = 0;
    *(u32*)(self + 0x690) = 0;
    *(u32*)(self + 0x694) = 0;
    *(u32*)(self + 0x698) = 0;
    *(u32*)(self + 0x69c) = 0;
    *(u32*)(self + 0x6a0) = 0;
    *(u32*)(self + 0x6a4) = 0;
    *(u32*)(self + 0x6a8) = 0xffffffff;
    ((void (__thiscall*)(void*))FUN_00b63890)(self + 0x6b0);
}

// ---------------------------------------------------------------------------
// 00bce0a0 -- Simulator::cTurret::~cTurret.
// ---------------------------------------------------------------------------
// @ 0x00bce0a0
cTurret::~cTurret() {
    u8* self = (u8*)this;
    *(void**)(self)         = &vtbl_Simulator_cTurret;
    *(void**)(self + 4)     = &PTR_FUN_01466e7c;
    *(void**)(self + 0x34)  = &PTR_FUN_01466d80;
    *(void**)(self + 0x108) = &PTR_FUN_01466d74;
    *(void**)(self + 0x504) = &PTR_FUN_01466d58;
    *(void**)(self + 0x51c) = &PTR_FUN_01466cf0;
    *(void**)(self + 0x588) = &PTR_FUN_01466c88;
    *(void**)(self + 0x650) = &PTR_FUN_01466c60;
    ((void (__thiscall*)(void*))FUN_00b638b0)(self + 0x6b0);
    void* p1 = *(void**)(self + 0x6a4);
    if (p1 != 0) ((void (__thiscall*)(void*))vc(p1, 0x64))(p1);
    void* p2 = *(void**)(self + 0x6a0);
    if (p2 != 0) ((void (__thiscall*)(void*))vc(p2, 4))(p2);
    void* p3 = *(void**)(self + 0x69c);
    if (p3 != 0) ((void (__thiscall*)(void*))vc(p3, 8))(p3);
    void* p4 = *(void**)(self + 0x698);
    if (p4 != 0) ((void (__thiscall*)(void*))vc(p4, 8))(p4);
    void* p5 = *(void**)(self + 0x694);
    if (p5 != 0) ((void (__thiscall*)(void*))vc(p5, 8))(p5);
    void* p6 = *(void**)(self + 0x690);
    if (p6 != 0) ((void (__thiscall*)(void*))vc(p6, 8))(p6);
    void* p7 = *(void**)(self + 0x68c);
    if (p7 != 0) ((void (__thiscall*)(void*))vc(p7, 8))(p7);
    void* p8 = *(void**)(self + 0x688);
    if (p8 != 0) ((void (__thiscall*)(void*))vc(p8, 4))(p8);
    void* p9 = *(void**)(self + 0x680);
    if (p9 != 0) ((void (__thiscall*)(void*))vc(p9, 4))(p9);
    ((void (__thiscall*)(void*))FUN_00b638b0)(self + 0x660);
    *(void**)(self + 0x650) = &PTR_FUN_01466c14;
    ((void (__thiscall*)(void*))FUN_00bfcd00)(self + 0x588);
    ((void (__thiscall*)(void*))FUN_00abfec0)(self + 0x51c);
    ((void (__thiscall*)(void*))FUN_00ac0520)(self + 0x504);
    ((void (__thiscall*)(void*))FUN_00c432e0)(self + 0x34);
    ((void (__thiscall*)(void*))FUN_00b184c0)(self);
}
