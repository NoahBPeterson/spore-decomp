// Slice s00c6f6e0: Simulator planet/ornament/civ helpers (retail 0x00c6f6e0..).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
//
// The generated SP::cPlanet.h / SP::cOrnament.h disagree with retail for the "Simulator" flavour
// of these classes (cOrnament here puts cSpatialObject at +0x70, cCombatant at +0x148 and
// cInteractionTarget at +0x210; cPlanet's record pointer lives at +0x13c and the tech level at
// +0x194).  Touched sub-objects are declared as local stubs with the retail offsets read off the
// disassembly and named by role.  SP::cPlanetRecord's field offsets DO match the retail
// disassembly (type 0x28, orbit 0x30, rotationIsNull 0x98, rotationAxis 0x9c, rotationPeriod 0xa8,
// ringType 0xac) and are named accordingly.
#include <string.h>

typedef unsigned int   uint;
typedef unsigned char  uchar;
typedef unsigned short ushort;

struct WorldObject;

// ---------------------------------------------------------------------------
// External callees (retail VAs in comments).  Declared only so MSVC emits a
// real `call rel32` and cannot fold the calls away.
// ---------------------------------------------------------------------------
void* __cdecl FUN_00c884f0(void* id);                 // 0xc884f0  Simulator::cSpatialObject::Cast
void* __cdecl FUN_00bfc380(void* id);                 // 0xbfc380
void* __cdecl FUN_00b18460(void* id);                 // 0xb18460  (class-id dispatch)
void* __cdecl FUN_00c751c0(void* id);                 // 0xc751c0
void* __cdecl FUN_00b18660();                         // 0xb18660  SP::cGameData::cGameData
void* __cdecl FUN_00c89630();                         // 0xc89630  SP::cSpatialObject::cSpatialObject
void* __cdecl FUN_00bfd4e0();                         // 0xbfd4e0  SP::cCombatant::cCombatant
void* __cdecl FUN_00ac03d0();                         // 0xac03d0  SP::cInteractionTarget::cInteractionTarget
void* __cdecl FUN_00b3d350(void* pId);               // 0xb3d350  SP::PlanetModel
void  __cdecl FUN_00b83c40(void* model, float a, int b, int c); // 0xb83c40  SP::cPlanetModel::FUN_00b83c40
void* __cdecl FUN_00b21340(void* mgr, void* a, void* b, void* c, void* d, void* e); // 0xb21340 GetGameDataVector
void* __cdecl FUN_00ac9310(void* a, void* b, void* c); // 0xac9310
void* __cdecl FUN_00bd9710(void* a);                  // 0xbd9710
void* __cdecl FUN_00b18530(void* pSelf);              // 0xb18530  SP::cGameData
void* __cdecl FUN_00b18590(void* a, void* b);         // 0xb18590  SP::cGameData::Write
void* __cdecl FUN_00c88a90(void* a, void* b);         // 0xc88a90  Simulator::cSpatialObject::Write
void* __cdecl FUN_00b18600(void* a, void* b);         // 0xb18600  SP::cGameData::Read
void* __cdecl FUN_00c88b00(void* a, void* b);         // 0xc88b00  Simulator::cSpatialObject::Read
void* __cdecl FUN_00692f90(void* a, void* b, void* c, void* d); // 0x692f90 cVarListSerializer::cVarListSerializer
void* __cdecl FUN_00692900(void* a, void* b);         // 0x692900 cVarListSerializer::Serialize
void* __cdecl FUN_00693e10(void* a, void* b);         // 0x693e10 cVarListSerializer::Read
void* __cdecl FUN_0093aa70(void* a, void* b, void* c, void* d); // 0x93aa70 EA::IO::WriteUint32
void* __cdecl FUN_00ac0450(void* self);               // 0xac0450
void* __cdecl FUN_00c8b2e0(void* self);                // 0xc8b2e0  Simulator::cSpatialObject
void* __cdecl FUN_00c8a550(void* a, void* b);         // 0xc8a550  Simulator::cSpatialObject::LoadModel
void* __cdecl FUN_00c884f0(void* self, unsigned type); // 0xc884f0  Simulator::cSpatialObject::Cast
void* __cdecl FUN_00bfc380(void* self, unsigned type); // 0xbfc380  cCombatant::Cast
void* __cdecl FUN_00b18460(void* self, unsigned type); // 0xb18460  cGameData::Cast
void* __cdecl FUN_00c751c0(void* self, unsigned type); // 0xc751c0  cast at +0x144
void* __cdecl FUN_00b3d300();                         // 0xb3d300  SP::NounManager
int   __cdecl FUN_00b1f9d0(void* mgr);                // 0xb1f9d0  GetPlayerEmpireOrMinus1 (this=mgr)
WorldObject* __cdecl FUN_00b8de30(void* a);           // 0xb8de30 (free form used by Func6fe50)
void* __cdecl FUN_00b8de60(void* a);                  // 0xb8de60
void* __cdecl FUN_00b8df20(void* a);                  // 0xb8df20
void* __cdecl FUN_00bba500();                         // 0xbba500
void* __cdecl FUN_00bb9ae0(void* a);                  // 0xbb9ae0
void* __cdecl FUN_00bb9b90(void* a);                  // 0xbb9b90
void* __cdecl FUN_00b1fdb0(void* a);                  // 0xb1fdb0  cGameNounManager::GetAvatar
void* __cdecl FUN_00b3d2a0(void* a);                  // 0xb3d2a0  SP::StarManager
void* __cdecl FUN_00ba9370(void* a);                  // 0xba9370  cStarManager::GetEmpireByID
void* __cdecl FUN_00c31730(void* a);                  // 0xc31730  cEmpire::GetHomePlanet
void* __cdecl FUN_00c35810(void* a, void* b);         // 0xc35810
void* __cdecl FUN_00ce6950(void* a);                  // 0xce6950  cStarRecordRef::GetCommContext
void* __cdecl FUN_00b3d4a0(void* a);                  // 0xb3d4a0  CommManager
void* __cdecl FUN_00aeab40(void* a, void* b);         // 0xaeab40  SpaceTool::RemoveByKey
void* __cdecl FUN_00aea720(void* a, void* b, void* c); // 0xaea720 SpaceTool::RemoveMatching
void* __cdecl FUN_00b5b800();                         // 0xb5b800  SP::GetCurrentGameMode
void* __cdecl FUN_0067dcc0();                         // 0x67dcc0  MessageServer
void* __cdecl FUN_00c8b5e0(void* a);                  // 0xc8b5e0
void* __cdecl FUN_00f473a0(int a, const char* tag, int b, int c, int d, int e); // 0xf473a0 operator new
void* __cdecl FUN_00ae5c30(void* a);                  // 0xae5c30  SimSingleton::SimSingleton
void* __cdecl FUN_00ae3740(void* a);                  // 0xae3740
void* __cdecl FUN_01021300();                         // 0x1021300  cSPLivingUniverse (ptr)
void* __cdecl FUN_01021090();                         // 0x1021090  GetPlayerEmpireID
void* __cdecl FUN_01021260();                         // 0x1021260  cSPLivingUniverse::GetActivePlanet
void* __cdecl FUN_01021080();                         // 0x1021080  cSPLivingUniverse::GetUniverseContext
void* __cdecl FUN_00fe8450(void* a);                  // 0xfe8450

extern int    DAT_01578698;
extern int    DAT_01578890;
extern int    DAT_01578ba0;
extern float  DAT_01485378;                            // _HK_REAL_ZERO
extern float  DAT_01485720;                            // _HK_REAL_ONE
extern float  DAT_013f4fd0;                            // 4294967296.0f (uint->float bias)
extern void*  DAT_01654c05;                            // a game-mode singleton
extern void*  DAT_0167a60c;                            // SimSingleton singleton
extern void*  DAT_016c7aa4;                            // 0x016c7aa4  globals
extern void*  DAT_0167a60c;                            // SimSingleton singleton
extern void*  DAT_015b4500;                            // default cEllipticalOrbit
extern void*  DAT_01578750;                            // name table row base
extern void*  DAT_01578754;                            // name table row base +4
extern void*  DAT_01578758;                            // name table row base +8
extern void*  DAT_015787f0;                            // default rotation axis
extern void*  PTR_FUN_0146c56c;
extern void*  PTR_FUN_01466c14;
extern void*  vtbl_Simulator_cOrnament;
extern void*  PTR_AddRef_01472180;
extern void*  PTR_FUN_0147216c;
extern void*  PTR_FUN_01472160;
extern void*  PTR_FUN_0147213c;
extern void*  PTR_FUN_01472120;
extern void*  PTR_FUN_014720b8;
extern void*  PTR_AddRef_014722d8;
extern void*  PTR_FUN_014722c4;
extern void*  vtbl_cPlaceholderColonyEditorCursorAttachment;
extern void*  FUN_00b1e500;
extern void*  FUN_00acdff0;
extern void*  FUN_00d3d420;
extern void*  FUN_00cd7d10;
extern void*  DAT_018c43e8;

struct Vec3 { float x, y, z; };
struct Orbit { uint w[0x1a]; void Recalc(); };   // cEllipticalOrbit, 0x68 bytes
struct WorldObj { void Func70860(); };           // the b8de30 result
struct NameRow { void* col0; void* col1; void* col2; };
extern NameRow g_NameRows[];                     // 0x01578750 (0xc-byte rows)

// helper: virtual function pointer at vtable byte offset
static void* vc(void* obj, int off) { return ((void**)*(void**)obj)[off / 4]; }

// ---------------------------------------------------------------------------
// SP::cPlanetRecord (retail field subset -- offsets verified against disassembly)
// ---------------------------------------------------------------------------
struct PlanetRecord {
    uchar   pad_000[0x18];
    void*   mName_18;          // 0x18  (eastl::wstring begin)
    uchar   pad_01c[0x0c];
    int     mType_28;          // 0x28  ePlanetType
    int     mFlags_2c;         // 0x2c
    Orbit   mOrbit_30;         // 0x30  cEllipticalOrbit
    bool    mRotationIsNull_98; // 0x98
    uchar   pad_099[0x3];
    Vec3    mRotationAxis_9c;  // 0x9c
    float   mRotationPeriod_a8; // 0xa8
    char    mRingType_ac;      // 0xac

    WorldObj* GetWorld();      // 0x00b8de30 (thiscall; retail returns the owning WorldObj)
};

// ---------------------------------------------------------------------------
// Simulator "cPlanet": cPlanetRecord pointer at +0x13c, tech level at +0x194.
// ---------------------------------------------------------------------------
struct SimPlanet {
    uchar        pad_000[0x13c];
    PlanetRecord* mRecord_13c;   // 0x13c
    uchar        pad_140[0x54];
    int          mTechLevel_194; // 0x194

    int   GetPlanetType() const;                 // 0x00c70880
    void* GetOrbit() const;                      // 0x00c708a0
    void  SetOrbit(void* pOrbit);                // 0x00c708c0
    bool  IsRotationNull() const;                // 0x00c708f0
    void  SetRotationNull(bool val);             // 0x00c70910
    void* GetRotationAxis() const;               // 0x00c70930
    void  SetRotationAxis(Vec3* axis);           // 0x00c70950
    float GetRotationPeriod() const;             // 0x00c70980
    void  SetRotationPeriod(float v);            // 0x00c709b0

    void* GetNameRow(bool wantCol0) const;       // 0x00c707f0
    void  Func70860();                           // 0x00c70860
};

// ---------------------------------------------------------------------------
// Simulator "cOrnament": cGameData at 0, cSpatialObject at 0x70,
// cCombatant at 0x148 (vtable slot 0x144), cInteractionTarget at 0x210.
// ---------------------------------------------------------------------------
struct SimOrnament {
    uchar pad_000[0x2c];
    void* mpRefCount_2c;       // 0x2c  refcounted object released in Destroy
    uchar pad_030[0x4];
    void* mpVftbl_34;          // 0x34
    int   mPowerupType_38;     // 0x38
    int   mInstanceID_3c;      // 0x3c
    int   mTypeID_40;          // 0x40
    int   mGroupID_44;         // 0x44
    bool  mbField_48;          // 0x48
    void* mpPropList_4c;       // 0x4c
    void* mpField20_50;        // 0x50
    void* mpField1c_54;        // 0x54
    uchar pad_058[0x0c];
    bool  mbHasBeenThrown_64;  // 0x64
    float mTimeInFlight_68;    // 0x68
    void* mpThrowObjective_6c; // 0x6c
    uchar mSpatial_70[0xa6];   // 0x70..0x116  cSpatialObject sub-object (part)
    bool  mbField_116;         // 0x116
    uchar mSpatial_b_117[0x2d];// 0x117..0x144 cSpatialObject sub-object (rest)
    void* mpVftbl_144;         // 0x144
    uchar mCombatant_148[0xc8];// 0x148..0x210  cCombatant sub-object
    uchar mIntTarget_210[0x18];// 0x210..0x228  cInteractionTarget sub-object
    int   mStyle_228;          // 0x228
    int   mModelID_22c;        // 0x22c
    bool  mbVisible_230;       // 0x230

    void* Cast(unsigned type);                       // 0x00c6f6e0
    void  SetStyleModel(int style, void* a, int model); // 0x00c6f770
    bool  IsPlayerOwned();                           // 0x00c6f7b0
    SimOrnament();                                   // 0x00c6f7f0
    bool  Write(void* pArchive);                     // 0x00c6f990
    void  Destroy();                                 // 0x00c6fac0
};

// ---------------------------------------------------------------------------
// Simulator "cPlaceholderColonyEditorCursorAttachment": cGameData at 0,
// cSpatialObject at 0x34.
// ---------------------------------------------------------------------------
struct SimCursorAttachment {
    uchar mGameData_000[0x2c]; // 0x00..0x2c cGameData
    void* mpRefCount_2c;       // 0x2c  AutoRefCount target
    uchar pad_030[0x4];
    uchar mSpatial_34[0x2c];   // 0x34..0x60 cSpatialObject

    SimCursorAttachment();                           // 0x00c6fcd0
    void* Cast(unsigned type);                       // 0x00c6fd20
    void  Destroy();                                 // 0x00c6fdc0
};

// ---------------------------------------------------------------------------
// The Simulator cSpatialObject sub-object as embedded in cOrnament at +0x70;
// `this` is that sub-object and the enclosing ornament sits at this - 0x70.
// ---------------------------------------------------------------------------
struct SimSpatial {
    uchar      pad_000[0x1b8];
    int        mStyle_1b8;          // 0x1b8  (== ornament +0x228)
    uchar      pad_1bc[0x3c];

    bool IsPlayerOwnedOrnament();                    // 0x00c6f7b0
    bool LoadModelOrnament(void* pModel);            // 0x00c6fb80
};

// ---------------------------------------------------------------------------
// The object the civ/planet helper functions operate on: a cCivData* vector at
// +0x15c..+0x160 plus fields used by the tech-level / city queries.
// ---------------------------------------------------------------------------
struct CivData;
struct CityData;
struct WorldObject {                    // the `b8de30`/`b8dab0`/`b8dad0` result
    uchar      pad_000[0x3c];
    void**     mpVec3c_3c;              // 0x3c  vector<X*>::begin
    void**     mpVec3c_40;              // 0x40  vector<X*>::end
    uchar      pad_044[0x40];
    int        mPlayerID_84;            // 0x84
    void  Func70860();                  // 0xb8de30 -> later vtable call
    int   GetType();                    // 0xbb9ae0
    void  SetSomething(void* a);        // 0xbb9b90
};
// cCivData: owns a vector<CityData*> at +0x00 (begin/end).
struct CivData {
    CityData** mpCities_00;             // 0x00 begin
    CityData** mpCities_04;             // 0x04 end
    uchar      pad_008[0x84 - 8];
    int        mOwner_84;               // 0x84

    CityData** GetCities() const;            // 0x5c65e0
    int        GetOwnerMaybe() const;        // 0xff0420
};
// cCityData: the per-city helpers.
struct CityData {
    int  GetNumBuildings() const;            // 0xff0870
    int  GetNumTurrets() const;              // 0xff0760
    float GetValue() const;                  // 0xfd9410
    void AddValue(float v) const;            // 0xff0350
    int  GetPercent() const;                 // 0xff0400
};

struct SimCivObject {
    uchar        pad_000[0x15c];
    CivData**    mpCivBegin_15c;        // 0x15c  eastl vector<cCivData*>::begin
    CivData**    mpCivEnd_160;          // 0x160  eastl vector<cCivData*>::end
    uchar        pad_164[0x30];
    int          mTechLevel_194;        // 0x194

    int        GetRecordType();                              // 0xb8dab0
    void*      GetKeyMaybe();                                // 0xb8dad0 (int[3] key)
    void*      GetSubObject(int index);                      // 0xb8dec0
    WorldObject* GetWorldObj();                              // 0xb8de30
    void       RebuildCivs();                                // 0xb8de60
    void       RebuildCivs2();                               // 0xb8df20

    bool  IsHomePlanetOfPlayer(WorldObject* pObj);           // 0x00c70150
    bool  AnyCityHasBuildings();                             // 0x00c70260
    int   CountBuildings();                                  // 0x00c702f0
    void  GetTurretAndBuildingCounts(int* pBuildings, int* pTurrets); // 0x00c70380
    int   CountCities();                                     // 0x00c70420
    int   GetPercentMaybe();                                 // 0x00c70470
    bool  Func704a0(int a, int b, int c, float amount);      // 0x00c704a0
    int   Func705c0(int amount);                             // 0x00c705c0
    void  SetPlanetTechLevel(int level);                     // 0x00c706d0
};

#define CHECK_OFF(t, m, o) char check_##t##_##m[(size_t)&((t*)0)->m == (o) ? 1 : -1]
CHECK_OFF(PlanetRecord, mType_28, 0x28);
CHECK_OFF(PlanetRecord, mOrbit_30, 0x30);
CHECK_OFF(PlanetRecord, mRotationIsNull_98, 0x98);
CHECK_OFF(PlanetRecord, mRotationAxis_9c, 0x9c);
CHECK_OFF(PlanetRecord, mRotationPeriod_a8, 0xa8);
CHECK_OFF(PlanetRecord, mRingType_ac, 0xac);
CHECK_OFF(SimPlanet, mRecord_13c, 0x13c);
CHECK_OFF(SimPlanet, mTechLevel_194, 0x194);
CHECK_OFF(SimOrnament, mpRefCount_2c, 0x2c);
CHECK_OFF(SimOrnament, mpVftbl_34, 0x34);
CHECK_OFF(SimOrnament, mpVftbl_144, 0x144);
CHECK_OFF(SimOrnament, mCombatant_148, 0x148);
CHECK_OFF(SimOrnament, mIntTarget_210, 0x210);
CHECK_OFF(SimOrnament, mStyle_228, 0x228);
CHECK_OFF(SimOrnament, mModelID_22c, 0x22c);
CHECK_OFF(SimOrnament, mbVisible_230, 0x230);
CHECK_OFF(SimOrnament, mbField_116, 0x116);
CHECK_OFF(SimCursorAttachment, mpRefCount_2c, 0x2c);
CHECK_OFF(SimCursorAttachment, mSpatial_34, 0x34);

// ---------------------------------------------------------------------------
// Function definitions.  One `// @ 0x<va>` marker per function.
// ---------------------------------------------------------------------------

// cVarListSerializer: a 0xa14-byte stack-local serializer object.
struct VarListSerializer { uchar mData_000[0xa14]; };

// ---- SimPlanet record accessors (member functions -> __thiscall) ----
// @ 0x00c70880
int SimPlanet::GetPlanetType() const {
    return mRecord_13c ? mRecord_13c->mType_28 : 2;
}
// @ 0x00c708a0
void* SimPlanet::GetOrbit() const {
    if (mRecord_13c) return (uchar*)mRecord_13c + 0x30;
    return &DAT_015b4500;
}
// @ 0x00c708c0
void SimPlanet::SetOrbit(void* pOrbit) {
    if (!mRecord_13c) return;
    mRecord_13c->mOrbit_30 = *(Orbit*)pOrbit;
    mRecord_13c->mOrbit_30.Recalc();
}
// @ 0x00c708f0
bool SimPlanet::IsRotationNull() const {
    return mRecord_13c ? mRecord_13c->mRotationIsNull_98 : true;
}
// @ 0x00c70910
void SimPlanet::SetRotationNull(bool val) {
    if (mRecord_13c) mRecord_13c->mRotationIsNull_98 = val;
}
// @ 0x00c70930
void* SimPlanet::GetRotationAxis() const {
    if (mRecord_13c) return (uchar*)mRecord_13c + 0x9c;
    return &DAT_015787f0;
}
// @ 0x00c70950
void SimPlanet::SetRotationAxis(Vec3* axis) {
    if (!mRecord_13c) return;
    mRecord_13c->mRotationAxis_9c = *axis;
}
// @ 0x00c70980
float SimPlanet::GetRotationPeriod() const {
    return mRecord_13c ? mRecord_13c->mRotationPeriod_a8 : 1.0f;
}
// @ 0x00c709b0
void SimPlanet::SetRotationPeriod(float v) {
    if (mRecord_13c) mRecord_13c->mRotationPeriod_a8 = v;
}
// @ 0x00c707f0
void* SimPlanet::GetNameRow(bool wantCol0) const {
    PlanetRecord* r = mRecord_13c;
    if (!r) return wantCol0 ? g_NameRows[0].col0 : g_NameRows[0].col1;
    char t = r->mRingType_ac;
    if (t < 0) return 0;
    int i = (int)t;
    if (r->mType_28 == 1) return g_NameRows[i].col2;
    return wantCol0 ? g_NameRows[i].col0 : g_NameRows[i].col1;
}
// @ 0x00c70860
void SimPlanet::Func70860() {
    mRecord_13c->GetWorld()->Func70860();
}

// ===========================================================================
// Civ/city helper functions.  `this` is the object carrying the cCivData*
// vector at +0x15c..+0x160.
// ===========================================================================

// @ 0x00c70150
bool SimCivObject::IsHomePlanetOfPlayer(WorldObject* pObj) {
    if (GetRecordType() != 5) return false;
    int n = (int)(mpCivEnd_160 - mpCivBegin_15c);
    for (int i = 0; i < n; ++i) {
        CivData* pCiv = mpCivBegin_15c[i];
        int owner = pObj->mPlayerID_84;
        if (pCiv->GetOwnerMaybe() == owner) {
            CityData** pCities = pCiv->GetCities();
            int nCities = (int)(pCities[1] - pCities[0]);
            for (int j = 0; j < nCities; ++j) {
                CityData* pCity = pCities[0] + j;
                if (pCity->GetNumBuildings() > 1) return true;
            }
        }
    }
    return true;
}

// @ 0x00c70260
bool SimCivObject::AnyCityHasBuildings() {
    int n = (int)(mpCivEnd_160 - mpCivBegin_15c);
    if (n <= 0) return false;
    for (int i = 0; i < n; ++i) {
        WorldObject* pObj = (WorldObject*)GetSubObject(i);
        int m = (int)(pObj->mpVec3c_40 - pObj->mpVec3c_3c);
        for (int j = 0; j < m; ++j) {
            if (((CityData*)pObj->mpVec3c_3c[j])->GetValue() >= 1.0f) return true;
        }
    }
    return false;
}
// @ 0x00c702f0
int SimCivObject::CountBuildings() {
    int total = 0;
    int n = (int)(mpCivEnd_160 - mpCivBegin_15c);
    for (int i = 0; i < n; ++i) {
        CityData** pCities = mpCivBegin_15c[i]->GetCities();
        int m = (int)(pCities[1] - pCities[0]);
        for (int j = 0; j < m; ++j) total += (pCities[0] + j)->GetNumBuildings();
    }
    return total;
}
// @ 0x00c70380
void SimCivObject::GetTurretAndBuildingCounts(int* pBuildings, int* pTurrets) {
    int n = (int)(mpCivEnd_160 - mpCivBegin_15c);
    for (int i = 0; i < n; ++i) {
        CityData** pCities = mpCivBegin_15c[i]->GetCities();
        int m = (int)(pCities[1] - pCities[0]);
        for (int j = 0; j < m; ++j) {
            *pBuildings += (pCities[0] + j)->GetNumBuildings();
            *pTurrets   += (pCities[0] + j)->GetNumTurrets();
        }
    }
}
// @ 0x00c70420
int SimCivObject::CountCities() {
    int total = 0;
    int n = (int)(mpCivEnd_160 - mpCivBegin_15c);
    for (int i = 0; i < n; ++i) {
        CityData** pCities = mpCivBegin_15c[i]->GetCities();
        total += (int)(pCities[1] - pCities[0]);
    }
    return total;
}
// @ 0x00c70470
int SimCivObject::GetPercentMaybe() {
    unsigned n = (unsigned)(mpCivEnd_160 - mpCivBegin_15c);
    if (n < 2 && n != 0) return mpCivBegin_15c[0]->GetCities()[0][0].GetPercent();
    return 0;
}
// @ 0x00c704a0
bool SimCivObject::Func704a0(int a, int b, int c, float amount) {
    int* pKey = (int*)GetKeyMaybe();
    if (a == pKey[0] && b == pKey[1] && c == pKey[2]) {
        int n = (int)(mpCivEnd_160 - mpCivBegin_15c);
        for (int i = 0; i < n; ++i) {
            WorldObject* pObj = (WorldObject*)GetSubObject(i);
            int m = (int)(pObj->mpVec3c_40 - pObj->mpVec3c_3c);
            for (int j = 0; j < m; ++j) {
                CityData* pCity = (CityData*)pObj->mpVec3c_3c[j];
                if (amount > 0.0f) {
                    float v = pCity->GetValue();
                    float take = v;
                    if (amount < v) take = amount;
                    pCity->AddValue(-take);
                    amount -= take;
                }
            }
        }
    }
    return true;
}
// @ 0x00c705c0
int SimCivObject::Func705c0(int amount) {
    if (FUN_01021300() == 0) return 0;
    FUN_01021090();
    float budget = (float)amount;
    if (amount < 0) budget += DAT_013f4fd0;
    float spent = 0.0f;
    int n = (int)(mpCivEnd_160 - mpCivBegin_15c);
    for (int i = 0; i < n; ++i) {
        WorldObject* pObj = (WorldObject*)GetSubObject(i);
        int m = (int)(pObj->mpVec3c_40 - pObj->mpVec3c_3c);
        for (int j = 0; j < m; ++j) {
            CityData* pCity = (CityData*)pObj->mpVec3c_3c[j];
            float v = pCity->GetValue();
            spent += v;
            if (budget > 0.0f) {
                if (v > budget) v = budget;
                pCity->AddValue(-v);
                budget -= v;
            }
        }
    }
    return (int)spent;
}
// @ 0x00c706d0
void SimCivObject::SetPlanetTechLevel(int level) {
    WorldObject* pWorld = GetWorldObj();
    SimPlanet* pActive = (SimPlanet*)FUN_01021260();
    if (pActive != 0 && pActive->mRecord_13c != (PlanetRecord*)this) pActive = 0;

    if (mTechLevel_194 == 5 && level != 5) {
        void* pAvatar = FUN_00b1fdb0(pWorld);
        void* pEmpire = FUN_00ba9370(FUN_00b3d2a0(pAvatar));
        if (pEmpire != 0) FUN_00c35810(pEmpire, this);
        void* pCtx1 = FUN_00ce6950(this);
        FUN_00aeab40(FUN_00b3d4a0(pCtx1), pCtx1);
        void* pCtx2 = FUN_00ce6950(this);
        FUN_00aea720(FUN_00b3d4a0(pAvatar), pCtx2, 0);
    }
    mTechLevel_194 = level;
    if (level == 1 || level == 0) {
        RebuildCivs();
        RebuildCivs2();
    }
    if (pActive != 0) {
        if (FUN_00b5b800() == &DAT_01654c05) {
            void* pMsg = FUN_0067dcc0();
            ((void (__thiscall*)(void*, int, int, int, int))vc(pMsg, 0x18))(pMsg, 0x490d429, 0, 0, 0);
        }
    }
    FUN_00c8b5e0(pWorld);
    if (pWorld->GetType() < 2) {
        int x[3] = { 0, 0, 0 };
        FUN_00bb9b90(x);
    }
}

// ===========================================================================
// Simulator cOrnament
// ===========================================================================

// base sub-object stubs whose only observable behaviour here is their ctor
struct GameDataBase { void ctor(); };              // 0xb18660
struct SpatialBase  { void ctor(); };              // 0xc89630
struct CombatantBase{ void ctor(); };              // 0xbfd4e0
struct IntTargetBase{ void ctor(); };              // 0xac03d0

// @ 0x00c6f7f0
SimOrnament::SimOrnament() {
    ((GameDataBase*)this)->ctor();
    mpVftbl_34 = &PTR_FUN_0146c56c;
    mPowerupType_38 = 0;
    mInstanceID_3c  = 0;
    mTypeID_40      = 0;
    mGroupID_44     = 0;
    mbField_48      = false;
    mpPropList_4c   = 0;
    mpField20_50    = 0;
    mpField1c_54    = 0;
    mbHasBeenThrown_64 = false;
    mTimeInFlight_68   = 0.0f;
    mpThrowObjective_6c = 0;
    ((SpatialBase*)mSpatial_70)->ctor();
    mpVftbl_144 = &PTR_FUN_01466c14;
    ((CombatantBase*)mCombatant_148)->ctor();
    ((IntTargetBase*)mIntTarget_210)->ctor();
    *(void**)mSpatial_70 = &vtbl_Simulator_cOrnament;
    mStyle_228   = 0;
    mModelID_22c = 0;
    *(void**)this   = &PTR_AddRef_01472180;
    *(void**)((uchar*)this + 4)       = &PTR_FUN_0147216c;
    mpVftbl_34      = &PTR_FUN_01472160;
    mpVftbl_144     = &PTR_FUN_0147213c;
    *(void**)mIntTarget_210 = &PTR_FUN_01472120;
    mbVisible_230   = true;
    *(void**)mCombatant_148 = &PTR_FUN_014720b8;
}

// @ 0x00c6f6e0
void* SimOrnament::Cast(unsigned type) {
    if (type == 0x175cdc9) return this;
    if (type == 0x102a041a) return this ? (uchar*)this + 0x210 : 0;
    if (type == 0x8367427)  return this ? (uchar*)this + 0x34 : 0;
    void* r = ((void* (__thiscall*)(void*, unsigned))FUN_00c884f0)(mSpatial_70, type);
    if (r) return r;
    r = ((void* (__thiscall*)(void*, unsigned))FUN_00bfc380)(mCombatant_148, type);
    if (r) return r;
    r = ((void* (__thiscall*)(void*, unsigned))FUN_00b18460)(this, type);
    if (r) return r;
    return ((void* (__thiscall*)(void*, unsigned))FUN_00c751c0)(&mpVftbl_144, type);
}

// @ 0x00c6f770
void SimOrnament::SetStyleModel(int style, void* a, int model) {
    mStyle_228   = style;
    mModelID_22c = model;
    ((void (__thiscall*)(SimOrnament*, void*))vc(this, 0x48))(this, a);
    if (mStyle_228 == 0x65658d2) mbField_116 = false;
}

// @ 0x00c6f7b0
bool SimSpatial::IsPlayerOwnedOrnament() {
    SimOrnament* p = (SimOrnament*)((uchar*)this - 0x70);
    void* pMgr = FUN_00b3d300();
    int id = ((int (__thiscall*)(void*))FUN_00b1f9d0)(pMgr);
    int mine = ((int (__thiscall*)(SimOrnament*))vc(p, 0x4c))(p);
    return mine == id;
}

// @ 0x00c6f990
bool SimOrnament::Write(void* pArchive) {
    void* p1 = ((void* (__thiscall*)(void*))vc(pArchive, 0x20))(pArchive);
    unsigned id = 0x175cdc9;
    unsigned handle = ((unsigned (__thiscall*)(void*))vc(p1, 0x18))(p1);
    FUN_0093aa70((void*)handle, &id, (void*)1, 0);
    bool b = ((bool (__thiscall*)(void*, void*))FUN_00b18590)(this, pArchive);
    if (b) {
        b = ((bool (__thiscall*)(void*, void*))FUN_00c88a90)(mSpatial_70, pArchive);
    }
    VarListSerializer ser;
    FUN_00692f90(&ser, this, &DAT_01578698, (void*)0x1a80d26);
    if (b) {
        if (FUN_00692900(&ser, pArchive)) return true;
    }
    return false;
}

// @ 0x00c6fac0
void SimOrnament::Destroy() {
    void* p = mpRefCount_2c;
    if (p) {
        mpRefCount_2c = 0;
        ((void (__thiscall*)(void*))vc(p, 4))(p);
    }
    ((void (__thiscall*)(void*))FUN_00ac0450)(mIntTarget_210);
    ((void (__thiscall*)(void*))FUN_00c8b2e0)(mSpatial_70);
}

// ===========================================================================
// The "visible planet" object: cSpatialObject at 0, cGameData at +0xd4.
// ===========================================================================
void* __cdecl FUN_00c8b5e0(void* a);                  // 0xc8b5e0

struct VisiblePlanet {
    uchar mSpatial_000[0xd4];   // 0x00..0xd4 cSpatialObject
    uchar mGameData_d4[0x44];   // 0xd4..    cGameData

    void* Cast(unsigned type);                       // 0x00c6fec0
    bool  Write(void* pArchive);                     // 0x00c6ff00
    void* Cast2(unsigned type);                      // 0x00c6ffd0
    bool  Write2(void* pArchive);                    // 0x00c70010
    bool  Read(void* pArchive);                      // 0x00c70090
};

// @ 0x00c6fcd0
SimCursorAttachment::SimCursorAttachment() {
    ((GameDataBase*)this)->ctor();
    ((SpatialBase*)mSpatial_34)->ctor();
    *(void**)mSpatial_34 = &vtbl_cPlaceholderColonyEditorCursorAttachment;
    *(void**)this       = &PTR_AddRef_014722d8;
    *(void**)((uchar*)this + 4) = &PTR_FUN_014722c4;
}

// @ 0x00c6fd20
void* SimCursorAttachment::Cast(unsigned type) {
    if (type == 0x2c5c935) return this;
    void* r = ((void* (__thiscall*)(void*, unsigned))FUN_00b18460)(this, type);
    if (!r) r = ((void* (__thiscall*)(void*, unsigned))FUN_00c884f0)(mSpatial_34, type);
    return r;
}

// @ 0x00c6fdc0
void SimCursorAttachment::Destroy() {
    void* p = mpRefCount_2c;
    if (p) {
        mpRefCount_2c = 0;
        ((void (__thiscall*)(void*))vc(p, 4))(p);
    }
    ((void (__thiscall*)(void*))FUN_00c8b2e0)(mSpatial_34);
}

// @ 0x00c6fec0
void* VisiblePlanet::Cast(unsigned type) {
    if (type != 0x3275872) {
        void* r = ((void* (__thiscall*)(void*, unsigned))FUN_00b18460)((uchar*)this + 0xd4, type);
        if (r == 0) return ((void* (__thiscall*)(void*, unsigned))FUN_00c884f0)(this, type);
        return r;
    }
    return this;
}

// @ 0x00c6ff00
bool VisiblePlanet::Write(void* pArchive) {
    bool b = ((bool (__thiscall*)(void*, void*))FUN_00b18590)((uchar*)this + 0xd4, pArchive);
    if (b) b = ((bool (__thiscall*)(void*, void*))FUN_00c88a90)(this, pArchive);
    VarListSerializer ser;
    FUN_00692f90(&ser, this, &DAT_01578890, (void*)0x1a80d26);
    if (b) {
        if (FUN_00692900(&ser, pArchive)) return true;
    }
    return false;
}

// @ 0x00c6ffd0
void* VisiblePlanet::Cast2(unsigned type) {
    if (type != 0x44462a6) {
        void* r = ((void* (__thiscall*)(void*, unsigned))FUN_00b18460)((uchar*)this + 0xd4, type);
        if (r == 0) return ((void* (__thiscall*)(void*, unsigned))FUN_00c884f0)(this, type);
        return r;
    }
    return this;
}

// @ 0x00c70010
bool VisiblePlanet::Write2(void* pArchive) {
    bool b = ((bool (__thiscall*)(void*, void*))FUN_00b18590)((uchar*)this + 0xd4, pArchive);
    if (b) b = ((bool (__thiscall*)(void*, void*))FUN_00c88a90)(this, pArchive);
    VarListSerializer ser;
    FUN_00692f90(&ser, this, &DAT_01578ba0, (void*)0x1a80d26);
    if (b) {
        if (FUN_00692900(&ser, pArchive)) return true;
    }
    return false;
}

// @ 0x00c70090
bool VisiblePlanet::Read(void* pArchive) {
    bool b = ((bool (__thiscall*)(void*, void*))FUN_00b18600)((uchar*)this + 0xd4, pArchive);
    if (b) b = ((bool (__thiscall*)(void*, void*))FUN_00c88b00)(this, pArchive);
    VarListSerializer ser;
    FUN_00692f90(&ser, this, &DAT_01578ba0, (void*)0x1a80d26);
    if (b) {
        if (FUN_00693e10(&ser, pArchive)) return true;
    }
    return false;
}

// ===========================================================================
// Free functions that take their argument on the stack (no `this`).
// ===========================================================================

// @ 0x00c6fe00
int Func6fe00(int type) {
    switch (type) {
    case 4: case 10: case 11: return 1;
    case 5: case 7: case 8: case 9: return 2;
    case 6: case 12: return 0;
    default: return 0;
    }
}

// @ 0x00c6fe50
bool Func6fe50(WorldObject* pObj) {
    WorldObject* pType = (WorldObject*)FUN_00b8de30(pObj);
    if (pType->GetType() != 5) return false;
    void* pAvatar = FUN_00b1fdb0(pType);
    void* pEmpire = FUN_00ba9370(FUN_00b3d2a0(pAvatar));
    return FUN_00c31730(pEmpire) == pObj;
}

// ===========================================================================
// 0x00c6fb80: the Simulator cOrnament's spatial sub-object LoadModel override.
// ===========================================================================
// @ 0x00c6fb80
bool SimSpatial::LoadModelOrnament(void* pModel) {
    bool ok = ((bool (__thiscall*)(void*, void*))FUN_00c8a550)(this, pModel);
    if (ok) {
        if (mStyle_1b8 == 0x65658d2) {
            SimOrnament* pOrn = (SimOrnament*)((uchar*)this - 0x70);
            void* pv = ((void* (__thiscall*)(void*))vc(this, 0x68))(this);
            float a = *(float*)((uchar*)pv + 0x10);
            if (a < 0) a = -a;
            void* pv2 = ((void* (__thiscall*)(void*))vc(this, 0x68))(this);
            float b = *(float*)((uchar*)pv2 + 4);
            if (b < 0) b = -b;
            float m = a > b ? a : b;
            void* pPlanetModel = ((void* (__thiscall*)(void*, float, int, int))vc(this, 0x2c))(this, m, 0x10000000, 0);
            FUN_00b83c40(FUN_00b3d350(pPlanetModel), m, 0x10000000, 0);
            void* pVec = FUN_00b21340(FUN_00b3d300(), (void*)FUN_00cd7d10, (void*)FUN_00d3d420, (void*)FUN_00acdff0, (void*)FUN_00b1e500, &DAT_018c43e8);
            void* pk = ((void* (__thiscall*)(void*))vc(this, 0x2c))(this);
            void* found = FUN_00ac9310((uchar*)pVec + 4, pk, 0);
            if (found) FUN_00bd9710(found);
        } else if (mStyle_1b8 == 1) {
            int tg = *(int*)((uchar*)this - 0x38);
            if (tg == 0xb || (tg == 0xe && *(int*)((uchar*)DAT_016c7aa4 + 0xcc) == 1)) {
                void* pGd = FUN_00b18530((uchar*)this - 0x70);
                int r = ((int (__thiscall*)(void*))vc(this, 0xac))(this);
                if (r != 0 && (pGd == 0 || *(int*)((uchar*)pGd + 0x24) != 2)) {
                    *(unsigned*)((uchar*)r + 4) |= 0x100;
                    *(uchar*)((uchar*)r + 0x5d) = 1;
                }
            }
        }
    }
    return ok;
}

