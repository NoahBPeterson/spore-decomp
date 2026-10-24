// Slice s00d091c0 -- SP::cCommunityEditor helpers and small accessors.
//
//  0x00d091c0  FUN_00d091c0                 model-type dispatch -> cCity::FUN_00bddda0
//  0x00d09560  SetKeyForModelType
//  0x00d09600  GetKeyForModelType
//  0x00d09670  FUN_00d09670                 palette-category index
//  0x00d096b0/00d096e0/00d09710/00d09740    "is in vector" helpers
//  0x00d09770  FUN_00d09770                 recompute anchor direction + quaternion
//  0x00d098b0  GetCameraZoomProgramID
//  0x00d09960  GetCommunityCenter
//  0x00d099c0  CameraTrackMouse
//  0x00d09ad0  SetObjectSpecificData
//  0x00d09d30  RemoveObjectFromCommunity
//  0x00d09f00  SnapPointToPlanetIfNecessary
//  0x00d09f60  SetManipulatedObject
//  0x00d0a040  ComputeMouseOffset
//
// Field offsets are the RETAIL ones (the 2008 PDB layout of cCommunityEditor is
// 0x294 bytes; retail is larger and offsets shift). Callees are masked
// relocations, so the stub classes below only need the right calling convention
// and vtable slots.
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <stddef.h>
#include <math.h>

struct ResourceKey {                                      // EA::ResourceMan::Key
    uint32_t instanceID, typeID, groupID;
};
struct Vector3 { float x, y, z; };
struct Quaternion { float x, y, z, w; };

extern Vector3 g_Vector3Zero;                             // 0x0169d58c

// ---- minimal EASTL-shaped vector -----------------------------------------
template <class T> struct sp_vector {                     // vector<T, sp_vector_allocator>
    T* mpBegin; T* mpEnd; T* mpCapacity; const char* mAllocName;
    int size() const { return (int)(mpEnd - mpBegin); }
};

// ---- external callees -----------------------------------------------------
uint32_t GetCurrentGameMode();                            // 0x00b5b800
enum { kGameModeCiv = 0x1654c04, kGameModeSpace = 0x1654c05 };

struct cTerrainSphere;
class cNounManager;
struct cSPLivingUniverse;
struct cGameNounManager;
struct cSPSimulatorSpaceGame;
struct cSPGameDataUFO;
struct cEmpire;

cNounManager*       NounManager();                        // 0x00b3d300
class cNounManager { public:
    cTerrainSphere* GetCurrentTerrainSphere();             // 0x00f67d90 (cTerrainEditor)
};
void                FUN_00c77bf0(cTerrainSphere*);        // 0x00c77bf0
cEmpire*            GetPlayerEmpire_01021300();           // 0x01021300
cSPLivingUniverse*  GetActivePlanetOwner_01021260();      // 0x01021260
void*               App_0067dd10();                       // 0x0067dd10
void*               MessageServer_0067dcc0();             // 0x0067dcc0
void*               SpaceGameGet_01002bd0(int, int);      // 0x01002bd0
cSPSimulatorSpaceGame* GetUFOSimulator_00ffbe50();        // 0x00ffbe50
void*               NounHost_00b3d240();                  // 0x00b3d240
void*               CameraCtl_00b3d280();                 // 0x00b3d280
void                CameraCtl_SetDir_00b13bb0(void*, const Vector3*, int);   // 0x00b13bb0
bool                RayHitsObject_00b35bf0(void*, const Vector3*, class cSpatialObject*); // 0x00b35bf0
void                FUN_007c4900(Vector3*, Vector3*);     // 0x007c4900
class cPlanetModel { public:
    void DirectionToSurface(Vector3* out, const Vector3* dir);        // 0x00b815a0
};
cPlanetModel*       PlanetModel_00b3d350(void*, const Vector3*);      // 0x00b3d350
void                FUN_00fe5430(void*, int);             // 0x00fe5430
void                FUN_00c8f470(void*, void*, int, int, float, int);  // 0x00c8f470 (cTribe::SetStimuli)

// FUN_00d09ad0 / FUN_00d09d30 anchors
int  FUN_00bd7f60();                                      // 0x00bd7f60
int  FUN_00bd7f40();                                      // 0x00bd7f40
int  FUN_00bd7f50();                                      // 0x00bd7f50
void FUN_00be2070(void*, int);                            // 0x00be2070
void FUN_00be33e0(void*);                                 // 0x00be33e0
void FUN_00be34a0(void*, int);                            // 0x00be34a0

// ---- vtable-only interfaces ----------------------------------------------
struct INameable {
    virtual void v0(); virtual const wchar_t* GetName(); virtual const Vector3* GetPosition();
};

class cCommunity;   // fwd

enum { TYPE_cCity = 0xee9b2232, TYPE_cTribe = 0x4f396a66 };

class cSpatialObject {
public:
    virtual void v00(); virtual void Release(); virtual void v02();       // 0x00..0x08
    virtual void* Cast0C(uint32_t typeID);                                // 0x0c
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();  // 0x10..0x1c
    virtual void v08(); virtual void v09(); virtual void v10();           // 0x20..0x28
    virtual const Vector3* GetPosition();                                 // 0x2c
    virtual const Quaternion* GetOrientation();                           // 0x30
    virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16();  // 0x34..0x40
    virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20();  // 0x44..0x50
    virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();  // 0x54..0x60
    virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28();  // 0x64..0x70
    virtual void v29(); virtual void v30(); virtual void v31(); virtual void v32();  // 0x74..0x80
    virtual void v33(); virtual void v34(); virtual void v35(); virtual void v36();  // 0x84..0x90
    virtual void v37(); virtual void v38(); virtual void v39(); virtual void v40();  // 0x94..0xa0
    virtual void v41(); virtual void v42(); virtual void v43(); virtual void v44();  // 0xa4..0xb0
    virtual void v45();                                                   // 0xb4
    virtual void* Cast(uint32_t typeID);                                  // 0xb8
    virtual void v67();                                                   // 0xbc
    virtual void v68();                                                   // 0xc0
    uint8_t pad04[0x72 - 4];
    uint8_t mFlag72;                                                      // +0x72
};

// The community-object base used by the editor (Cast slot 0x0c, GetPosition 0x64,
// GetMode 0x6c).
class cCommunity {
public:
    virtual void AddRef();                                // 0x00
    virtual void Release();                               // 0x04
    virtual void v02();
    virtual void* Cast(uint32_t typeID);                  // 0x0c
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24();
    virtual const Vector3* GetPosition();                 // 0x64
    virtual void v26();
    virtual void* GetMode();                              // 0x6c
};

class cCivilization {
public:
    uint8_t   pad00[0x34];
    INameable mNameable;                                  // +0x34
    uint8_t   pad38[0x40 - 0x38];
    int       mPoliticalID;                               // +0x40
    const ResourceKey* GetModelTypeKey(uint32_t modelType);                       // 0x00bf9770
    void CreateVehicleFromModelType(uint32_t modelType, const ResourceKey* key);  // 0x00bf4b10
};

struct cHallNoun { uint8_t pad[0x34]; INameable mSpatial; };   // +0x34 spatial

class cCity : public cCommunity {
public:
    cCivilization* GetCivilization();                     // 0x00bd9bf0
    cHallNoun*     GetCityHall();                         // 0x00bd9b40
    void* FUN_00bddda0(int a, int b, uint32_t kx, uint32_t ky, uint32_t kz, int space); // ret 0x18
    uint8_t pad04[0x298 - 4];
    cSpatialObject* mpSpecific_298;                       // +0x298
};

class cSPPaletteUI {
public:
    virtual void AddRef(); virtual void Release();
    uint32_t data[(0x6c - 4) / 4];
    int GetCurrentCategoryIndex();                        // 0x005ca9c0
};

// ---- external engine classes (vtable-only stubs) -------------------------
class cEmpire {
public:
    void SetUFOKey(const ResourceKey*);                   // 0x00c35740
    const ResourceKey* GetUFOKey();                       // 0x00c326b0
};
class cSPGameDataUFO {
public:
    void SetDesiredModel(const ResourceKey*, int);        // 0x00c37180
};
class cSPSimulatorSpaceGame {
public:
    cSPGameDataUFO* GetPlayerInventory();                 // 0x00a1ad60
};
class cSPLivingUniverse {
public:
    bool FUN_00c70b50();                                  // 0x00c70b50
};
class cGameNounManager {
public:
    void* GetPlayerTribe();                               // (0x00bfc5f0 path)
};

// ---- cCommunityEditor (retail layout) ------------------------------------
class cCommunityEditor {
public:
    virtual void HandleMessage();                         // IHandlerRC primary base (vptr +0)

    uint32_t pad04[4];
    uint8_t  mActiveAutoHandler[0x14];                    // +0x14
    uint8_t  mPassiveAutoHandler[0x14];                   // +0x28
    void*    mConfigProps;                                // +0x3c
    cCommunity* mpCommunity;                              // +0x40
    uint32_t mSelectedCategoryID;                         // +0x44
    uint32_t mShoppingModelType;                          // +0x48
    uint32_t mLastShoppingModelType;                      // +0x4c
    uint32_t mRecentlyEditedModelKey[3];                  // +0x50
    bool     mbFromShopping;                              // +0x5c
    uint8_t  pad5d[3];
    uint8_t  pad60[0x88 - 0x60];
    uint8_t  mEditorUI;                                   // +0x88 (cSPUILayout head, opaque)
    uint8_t  pad89[0xb4 - 0x89];
    cSPPaletteUI*  mpPaletteUI;                           // +0xb4
    uint32_t padb8;
    cSpatialObject* mpAnchorRing;                         // +0xbc
    cSpatialObject* mpManipulatedObject;                  // +0xc0
    cSpatialObject* mpSelectedObject;                     // +0xc4
    uint32_t padc8;
    Vector3  mAnchorDir_cc;                               // +0xcc
    Quaternion mAnchorQuat;                               // +0xd8
    Vector3  mSnapPoint;                                  // +0xe8
    int      mLastSwapPointIndex;                         // +0xf4
    uint8_t  padf8[0x114 - 0xf8];
    uint8_t  mAnimatedObjectMap[0x1c];                    // +0x114 (eastl::map)
    sp_vector<void*> mPreExistingBuildings;               // +0x130
    uint32_t pad140;
    sp_vector<void*> mPreExistingNouns;                   // +0x144
    uint8_t  pad154[0x1dc - 0x154];
    sp_vector<void*> mPreExistingTurrets;                 // +0x1dc
    uint32_t pad1ec;
    sp_vector<void*> mPreExistingTools;                   // +0x1f0
    uint8_t  pad200[0x278 - 0x200];
    cSpatialObject* mpManipulatedObject_278;              // +0x278
    uint32_t mSpecificA_27c;                              // +0x27c
    uint32_t mSpecificB_280;                              // +0x280
    uint32_t mSpecificC_284;                              // +0x284
    uint32_t mSpecificD_288;                              // +0x288
    uint32_t mSpecificE_28c;                              // +0x28c
    uint32_t mSpecificF_290;                              // +0x290
    uint32_t mSpecificG_294;                              // +0x294
    void*    mpCaptureWindow;                             // +0x298

    void   FUN_00d091c0(uint32_t modelType);                                  // 0x00d091c0
    void   SetKeyForModelType(uint32_t modelType, const ResourceKey* key);    // 0x00d09560
    const ResourceKey* GetKeyForModelType(uint32_t modelType);               // 0x00d09600
    int    FUN_00d09670();                                                    // 0x00d09670
    bool   FUN_00d096b0(void* obj);                                           // 0x00d096b0
    bool   FUN_00d096e0(void* obj);                                           // 0x00d096e0
    bool   FUN_00d09710(void* obj);                                           // 0x00d09710
    bool   FUN_00d09740(void* obj);                                           // 0x00d09740
    void*  FUN_00d09770(int, int);                                            // 0x00d09770
    uint32_t GetCameraZoomProgramID();                                        // 0x00d098b0
    const Vector3* GetCommunityCenter();                                      // 0x00d09960
    void   CameraTrackMouse(cSpatialObject* obj);                             // 0x00d099c0
    void   SetObjectSpecificData();                                           // 0x00d09ad0
    void   RemoveObjectFromCommunity(cSpatialObject* obj);                    // 0x00d09d30
    Vector3* SnapPointToPlanetIfNecessary(Vector3* out, float x, float y, float z, cSpatialObject* obj); // 0x00d09f00
    void   SetManipulatedObject(cSpatialObject* obj);                         // 0x00d09f60
    void   ComputeMouseOffset(cSpatialObject* obj);                           // 0x00d0a040
};

#define OFFSET_CHECK(T, m, n) typedef char off_check_##T##_##m[(offsetof(T, m) == (n)) ? 1 : -1]
OFFSET_CHECK(cCommunityEditor, mpCommunity, 0x40);
OFFSET_CHECK(cCommunityEditor, mpPaletteUI, 0xb4);
OFFSET_CHECK(cCommunityEditor, mpAnchorRing, 0xbc);
OFFSET_CHECK(cCommunityEditor, mpManipulatedObject, 0xc0);
OFFSET_CHECK(cCommunityEditor, mpSelectedObject, 0xc4);
OFFSET_CHECK(cCommunityEditor, mAnchorDir_cc, 0xcc);
OFFSET_CHECK(cCommunityEditor, mAnchorQuat, 0xd8);
OFFSET_CHECK(cCommunityEditor, mSnapPoint, 0xe8);
OFFSET_CHECK(cCommunityEditor, mLastSwapPointIndex, 0xf4);
OFFSET_CHECK(cCommunityEditor, mAnimatedObjectMap, 0x114);
OFFSET_CHECK(cCommunityEditor, mPreExistingBuildings, 0x130);
OFFSET_CHECK(cCommunityEditor, mPreExistingNouns, 0x144);
OFFSET_CHECK(cCommunityEditor, mPreExistingTurrets, 0x1dc);
OFFSET_CHECK(cCommunityEditor, mPreExistingTools, 0x1f0);
OFFSET_CHECK(cCommunityEditor, mpManipulatedObject_278, 0x278);
OFFSET_CHECK(cCommunityEditor, mSpecificA_27c, 0x27c);
OFFSET_CHECK(cCommunityEditor, mpCaptureWindow, 0x298);

// helper: the community editor's objects are found via Cast(slot 0x0c)
static inline void* CastTo(cCommunity* c, uint32_t typeID)
{
    return c ? c->Cast(typeID) : 0;
}
static inline cCity* AsCity(cCommunity* c)
{
    return (cCity*)CastTo(c, TYPE_cCity);
}

// ==========================================================================
// @ 0x00d091c0
// ==========================================================================
void cCommunityEditor::FUN_00d091c0(uint32_t modelType)
{
    if (!mpCommunity) return;
    cCity* city = AsCity(mpCommunity);
    if (!city) return;

    bool inSpace = (GetCurrentGameMode() == kGameModeSpace);

    if (GetCurrentGameMode() == kGameModeCiv &&
        (modelType == 0x441cd3e6 || modelType == 0x449c040f || modelType == 0x1a4e0708)) {
        cTerrainSphere* ts = NounManager()->GetCurrentTerrainSphere();
        FUN_00c77bf0(ts);
    }

    int a = -1, b = -1;
    switch (modelType) {
    case 0x1a4e0708: a = 2; b = 1; break;
    case 0xbc1041e6: a = 2; b = 2; break;
    case 0x9ad7d4aa: a = 1; b = 0; break;
    case 0x8f963dcb: a = 0; b = 1; break;
    case 0xc0b74287: a = 2; b = 2; break;
    case 0xf670aa43: a = 2; b = 2; break;
    case 0xc15695da: a = 2; b = 1; break;
    case 0x2a5147a9: a = 1; b = 1; break;
    case 0x2090a11b: a = 2; b = 2; break;
    case 0x1f2a25b6: a = 1; b = 1; break;
    case 0x441cd3e6: a = 0; b = 2; break;
    case 0x449c040f: a = 1; b = 2; break;
    case 0x7d433fad: a = 0; b = 0; break;
    default: return;
    }
    cCivilization* civ = city->GetCivilization();
    const ResourceKey* key = civ->GetModelTypeKey(modelType);
    city->FUN_00bddda0(a, b, key->instanceID, key->typeID, key->groupID, inSpace ? 1 : 0);
}

// ==========================================================================
// @ 0x00d09560  SetKeyForModelType
// ==========================================================================
void cCommunityEditor::SetKeyForModelType(uint32_t modelType, const ResourceKey* key)
{
    if (modelType == 0x98e03c0d) {
        GetPlayerEmpire_01021300()->SetUFOKey(key);
        cSPSimulatorSpaceGame* sim = GetUFOSimulator_00ffbe50();
        cSPGameDataUFO* inv = sim->GetPlayerInventory();
        if (inv) { inv->SetDesiredModel(key, 1); return; }
        return;
    }
    cCommunity* comm = mpCommunity;
    cCity* city = comm ? (cCity*)comm->Cast(TYPE_cCity) : 0;
    city->GetCivilization()->CreateVehicleFromModelType(modelType, key);
    if (modelType == 0x99e92f05) {
        cTerrainSphere* ts = NounManager()->GetCurrentTerrainSphere();
        *(uint32_t*)((char*)ts + 0x1150) = key->instanceID;
        *(uint32_t*)((char*)ts + 0x1154) = key->typeID;
        *(uint32_t*)((char*)ts + 0x1158) = key->groupID;
    }
}

// ==========================================================================
// @ 0x00d09600  GetKeyForModelType
// ==========================================================================
const ResourceKey* cCommunityEditor::GetKeyForModelType(uint32_t modelType)
{
    if (modelType == 0x98e03c0d) {
        cEmpire* empire = GetPlayerEmpire_01021300();
        return empire->GetUFOKey();
    }
    cCommunity* comm = mpCommunity;
    cCity* city = comm ? (cCity*)comm->Cast(TYPE_cCity) : 0;
    return city->GetCivilization()->GetModelTypeKey(modelType);
}

// ==========================================================================
// @ 0x00d09670
// ==========================================================================
int cCommunityEditor::FUN_00d09670()
{
    if (mpPaletteUI) return mpPaletteUI->GetCurrentCategoryIndex();
    return -1;
}

// ==========================================================================
// @ 0x00d096b0
// ==========================================================================
bool cCommunityEditor::FUN_00d096b0(void* obj)
{
    void** end = mPreExistingBuildings.mpEnd;
    void** it  = mPreExistingBuildings.mpBegin;
    if (it != end) {
        do { if (*it == obj) break; ++it; } while (it != end);
    }
    return (it == end) ? false : true;
}

// @ 0x00d096e0
bool cCommunityEditor::FUN_00d096e0(void* obj)
{
    void** end = mPreExistingNouns.mpEnd;
    void** it  = mPreExistingNouns.mpBegin;
    if (it != end) {
        do { if (*it == obj) break; ++it; } while (it != end);
    }
    return (it == end) ? false : true;
}

// @ 0x00d09710
bool cCommunityEditor::FUN_00d09710(void* obj)
{
    void** end = mPreExistingTurrets.mpEnd;
    void** it  = mPreExistingTurrets.mpBegin;
    if (it != end) {
        do { if (*it == obj) break; ++it; } while (it != end);
    }
    return (it == end) ? false : true;
}

// @ 0x00d09740
bool cCommunityEditor::FUN_00d09740(void* obj)
{
    void** end = mPreExistingTools.mpEnd;
    void** it  = mPreExistingTools.mpBegin;
    if (it != end) {
        do { if (*it == obj) break; ++it; } while (it != end);
    }
    return (it == end) ? false : true;
}

// ==========================================================================
// @ 0x00d09770
// ==========================================================================
struct cCamHost {                                          // FUN_00b3d240 result vtbl
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();  // 0x00..0x0c
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();  // 0x10..0x1c
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();  // 0x20..0x2c
    virtual void v12(); virtual void v13();                                           // 0x30..0x34
    virtual const Vector3* GetCamPos(Vector3* out, int flag);      // 0x38
    virtual void           GetCamPos3C(Vector3* out, int flag);    // 0x3c
};

void* cCommunityEditor::FUN_00d09770(int, int)
{
    if (mpSelectedObject) {
        cCamHost* host = (cCamHost*)NounHost_00b3d240();
        const Vector3* objPos = mpSelectedObject->GetPosition();
        Vector3 camBuf = g_Vector3Zero;
        const Vector3* camPos = host->GetCamPos(&camBuf, 0);
        float dx = camPos->x - objPos->x;
        float dy = camPos->y - objPos->y;
        float dz = camPos->z - objPos->z;
        float inv = 1.0f / (float)sqrt(dx*dx + dy*dy + dz*dz);
        mAnchorDir_cc.x = inv * dx;
        mAnchorDir_cc.y = inv * dy;
        mAnchorDir_cc.z = inv * dz;
        const Quaternion* q = mpSelectedObject->GetOrientation();
        mAnchorQuat.x = q->x;
        mAnchorQuat.y = q->y;
        mAnchorQuat.z = q->z;
        mAnchorQuat.w = q->w;
    }
    return 0;
}

// ==========================================================================
// @ 0x00d098b0  GetCameraZoomProgramID
// ==========================================================================
struct cCommunityMode {                                   // community GetMode() result
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26();
    virtual void* FUN_00bec860();                         // 0x6c
};

uint32_t cCommunityEditor::GetCameraZoomProgramID()
{
    const uint32_t kDefault = 0x225d13ad;
    if (!mpCommunity) return kDefault;

    cCommunity* a = mpCommunity ? (cCommunity*)mpCommunity->Cast(TYPE_cCity) : 0;
    cCommunity* b = mpCommunity ? (cCommunity*)mpCommunity->Cast(TYPE_cTribe) : 0;

    if (a == 0) {
        if (b != 0) return 0x5b2dd8b4;
    } else {
        if (a->GetMode() != 0) {
            cCommunity* m2 = (cCommunity*)a->GetMode();
            if (m2->GetMode() != 0) {
                cCommunity* m3 = (cCommunity*)a->GetMode();
                if (m3->GetMode() != (void*)2)
                    return 0x0c24c2b5;
            }
        }
    }
    return kDefault;
}

// ==========================================================================
// @ 0x00d09960  GetCommunityCenter
// ==========================================================================
const Vector3* cCommunityEditor::GetCommunityCenter()
{
    if (!mpCommunity) return &g_Vector3Zero;
    if (GetCurrentGameMode() == kGameModeSpace && mpCommunity) {
        cCommunity* comm = mpCommunity;
        cCity* city = comm ? (cCity*)comm->Cast(TYPE_cCity) : 0;
        if (city) {
            if (city->GetCityHall()) {
                cSpatialObject* sp = (cSpatialObject*)((char*)city->GetCityHall() + 0x34);
                return sp->GetPosition();
            }
        }
    }
    return mpCommunity->GetPosition();
}

// ==========================================================================
// @ 0x00d099c0  CameraTrackMouse
// ==========================================================================
void cCommunityEditor::CameraTrackMouse(cSpatialObject* obj)
{
    cCamHost* host = (cCamHost*)NounHost_00b3d240();
    Vector3 buf;
    host->GetCamPos3C(&buf, 1);
    if (obj) {
        cSpatialObject* r = (cSpatialObject*)obj->Cast0C(0x01186577);
        if (r) {
            const Vector3* p = r->GetPosition();
            buf.x = p->x; buf.y = p->y; buf.z = p->z;
        }
    }
    const Vector3* center = GetCommunityCenter();
    float len = (float)sqrt(center->x*center->x + center->y*center->y + center->z*center->z);
    float inv = 1.0f / (float)sqrt(buf.x*buf.x + buf.y*buf.y + buf.z*buf.z);
    Vector3 dir;
    dir.x = (inv * buf.x) * len;
    dir.y = (inv * buf.y) * len;
    dir.z = (inv * buf.z) * len;
    if (CameraCtl_00b3d280()) {
        CameraCtl_SetDir_00b13bb0(CameraCtl_00b3d280(), &dir, 0);
    }
}

// ==========================================================================
// @ 0x00d09ad0  SetObjectSpecificData
// ==========================================================================
void cCommunityEditor::SetObjectSpecificData()
{
    if (!mpManipulatedObject) return;
    cCommunity* a = (cCommunity*)CastTo(mpCommunity, TYPE_cCity);
    cCommunity* b = (cCommunity*)CastTo(mpCommunity, TYPE_cTribe);
    cSpatialObject* obj = mpManipulatedObject;
    void* f1 = obj->Cast(0x0436f315);
    void* f2 = obj->Cast(0x0e9cb8ba);
    void* f3 = obj->Cast(0x0116d858);
    void* f4 = obj->Cast(0x0175cdc9);

    if (f1 && a) {
        mSpecificA_27c = 0xf089377b; mSpecificB_280 = 0x1641ae13;
        mSpecificC_284 = 0xde3f8c28; mSpecificD_288 = 0x414c841f;
        mSpecificE_28c = 0x97b71138; mSpecificF_290 = 0x869764ee;
        mSpecificG_294 = 0xefca2d60;
        mLastSwapPointIndex = FUN_00bd7f60();
        return;
    }
    if (f2 && a) {
        mSpecificA_27c = 0x9fdf8751; mSpecificB_280 = 0x7fa0a9e9;
        mSpecificC_284 = 0xa94b3e0e; mSpecificD_288 = 0x7f232c6d;
        mSpecificE_28c = 0xd393ef5e; mSpecificF_290 = 0xdffee948;
        mSpecificG_294 = 0x215d6086;
        mLastSwapPointIndex = FUN_00bd7f40();
        return;
    }
    if (f3 && b) {
        mSpecificA_27c = 0xeeef054f; mSpecificB_280 = 0xbc866537;
        mSpecificC_284 = 0x9e017694; mSpecificD_288 = 0x98ff936a;
        mSpecificE_28c = 0x5546e1e4; mSpecificF_290 = 0xbb2a2e9a;
        mSpecificG_294 = 0xd9c01f7c;
        mLastSwapPointIndex = (int)b + 0x3b4;
        return;
    }
    if (f4 && a) {
        mSpecificA_27c = 0xf081d484; mSpecificB_280 = 0x769de34c;
        mSpecificC_284 = 0x63614239; mSpecificD_288 = 0x0ff4d3c0;
        mSpecificE_28c = 0x86c46889; mSpecificF_290 = 0xfd7cf077;
        mSpecificG_294 = 0x0d05b881;
        mLastSwapPointIndex = FUN_00bd7f50();
    }
}

// ==========================================================================
// @ 0x00d09d30  RemoveObjectFromCommunity
// ==========================================================================
struct cModelStimuli { virtual void v(int); };

void cCommunityEditor::RemoveObjectFromCommunity(cSpatialObject* obj)
{
    if (!mpCommunity) return;
    cCity* city = AsCity(mpCommunity);
    cCommunity* comm = (cCommunity*)CastTo(mpCommunity, TYPE_cTribe);
    if (!obj) return;

    void* f1 = obj->Cast(0x0436f315);
    void* f2 = obj->Cast(0x0e9cb8ba);
    void* f3 = obj->Cast(0x0116d858);
    void* f4 = obj->Cast(0x0175cdc9);

    if (f1 && city) { FUN_00be2070(f1, 0); return; }
    if (f2 && city) {
        FUN_00be33e0(f2);
        if (GetCurrentGameMode() == kGameModeSpace) {
            cSPLivingUniverse* lu = GetActivePlanetOwner_01021260();
            if (!lu->FUN_00c70b50()) {
                cGameNounManager* sg = (cGameNounManager*)SpaceGameGet_01002bd0(0, -1);
                void* tribe = sg->GetPlayerTribe();
                FUN_00fe5430(tribe, -1);
                return;
            }
        }
        return;
    }
    if (f3 && comm) {
        FUN_00c8f470(comm, f3, 0, 0x800000, *(float*)0x14791d8, 0);
        return;
    }
    if (f4 && comm) { FUN_00be34a0(f4, 0); }
}

// ==========================================================================
// @ 0x00d09f00  SnapPointToPlanetIfNecessary
// ==========================================================================
Vector3* cCommunityEditor::SnapPointToPlanetIfNecessary(Vector3* out, float x, float y, float z,
                                                        cSpatialObject* obj)
{
    if (obj && obj->Cast(0x0436f315)) {
        out->x = x; out->y = y; out->z = z;
        return out;
    }
    PlanetModel_00b3d350(out, (Vector3*)&x)->DirectionToSurface(out, (Vector3*)&x);
    return out;
}

// ==========================================================================
// @ 0x00d09f60  SetManipulatedObject
// ==========================================================================
class cGameDataHolder;
void FUN_00c88530(void*);                                 // 0x00c88530 (cCity-specific, unused)

void cCommunityEditor::SetManipulatedObject(cSpatialObject* obj)
{
    if (mpManipulatedObject_278 && mpManipulatedObject != obj) {
        mpManipulatedObject_278->Cast0C(1);
        if (mpManipulatedObject_278) {
            cSpatialObject* p = mpManipulatedObject_278;
            mpManipulatedObject_278 = 0;
            p->Release();
        }
    }
    if (mpManipulatedObject) mpManipulatedObject->mFlag72 = 0;
    mpManipulatedObject = obj;
    if (obj) obj->mFlag72 = 1;

    mSnapPoint = g_Vector3Zero;
    cCommunity* comm = mpCommunity;

    if (comm) {
        cCity* city = (cCity*)comm->Cast(TYPE_cCity);
        if (city) {
            cSpatialObject* cur  = mpManipulatedObject;
            cSpatialObject* prev = city->mpSpecific_298;
            if (cur != prev) {
                if (cur) cur->v67();
                city->mpSpecific_298 = cur;
                if (prev) prev->v68();
            }
        }
    }
}

// ==========================================================================
// @ 0x00d0a040  ComputeMouseOffset
// ==========================================================================
class cDisplay {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06();
    virtual void GetMousePos(Vector3* a, Vector3* b);     // 0x1c
};
struct cApp {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void* GetDisplay();                           // 0x50
};

void cCommunityEditor::ComputeMouseOffset(cSpatialObject* obj)
{
    if (!obj) return;
    mSnapPoint.x = g_Vector3Zero.x;
    mSnapPoint.y = g_Vector3Zero.y;
    mSnapPoint.z = g_Vector3Zero.z;

    cApp* app = (cApp*)App_0067dd10();
    cDisplay* display = (cDisplay*)app->GetDisplay();
    Vector3 a = { 0, 0, 0 };
    Vector3 b = { 0, 0, 0 };
    display->GetMousePos(&a, &b);
    FUN_007c4900(&a, &b);
    float scale = *(float*)0x13ec5b4;
    Vector3 target;
    target.x = a.x + b.x * scale;
    target.y = a.y + b.y * scale;
    target.z = a.z + b.z * scale;
    if (RayHitsObject_00b35bf0(NounHost_00b3d240(), &target, obj)) {
        const Vector3* p = obj->GetPosition();
        mSnapPoint.x = p->x - target.x;
        mSnapPoint.y = p->y - target.y;
        mSnapPoint.z = p->z - target.z;
    }
}
