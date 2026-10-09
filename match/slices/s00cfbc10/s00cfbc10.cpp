// Slice s00cfbc10: SP::cCivModeStrategy::ContinueLoading (0x00cfbc10, 5644 bytes).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc: no EH frame despite RAII locals;
// /fp:fast for the inline fsin/fcos).
//
// One step of the Civilization-mode loading state machine (cLoadingState at +0xb4:
// mState, mPreviousMode, mCurrentMode, mFrames). Each call advances at most one state:
//   0  orient the planet, bring up the city/tribe hand-off, terrain/model world, input configs
//   1  per-mode setup (tribe->civ effect, load-game civ names, time of day, texture preload,
//      sim singleton counters, camera reset, editor-return path)
//   2  wait for the texture preload; editor return / load-game follow-up
//   3  wait for the planet model, add resource nodes
//   4  re-collect the mandatory baked items and request the missing ones
//   5  wait until resources and the model world are ready
//   6  after 1 s: event log, city-hall camera/sound/messages, then tutorial (8) or 7
//   7  civ-start tutorial message, then done (10)
//   8/9 wait for the tutorial system
// After the switch the loading UI is ticked (FUN_00b3d230()->Update(param)).
//
// Game mode IDs are the CommonIDs.h values (kGameTribe 0x1654C02, kGameCiv 0x1654C04,
// kGameEditMode 0x1654C06, kLoadGameMode 0x1654C08, kEditorMode 0xDBDBA1, kGGEMode 0x2CCD1D2).
// Most callees are only known by address; receivers are modelled as small stub classes with
// the vtable slots the original uses. Retail field offsets of cCivModeStrategy differ from the
// dev PDB, so its fields are named by role.
#include "types.h"

#pragma intrinsic(sin, cos)
extern "C" double sin(double);
extern "C" double cos(double);

// ---------------------------------------------------------------- ids
enum {
    kGameTribe = 0x1654C02,
    kGameCiv = 0x1654C04,
    kGameEditMode = 0x1654C06,
    kLoadGameMode = 0x1654C08,
    kEditorMode = 0x00DBDBA1,
    kGGEMode = 0x2CCD1D2,
    kNoMode = -1
};

// ---------------------------------------------------------------- math
struct Vector3 {
    float x, y, z;
};
struct Quaternion {
    float x, y, z, w;
};
struct Matrix3 {
    float m[9];
};
struct ResourceKey {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
};

Quaternion QuaternionFromDirections(const Vector3& from, const Vector3& to);   // 0x00698180
Quaternion operator*(const Quaternion& a, const Quaternion& b);                 // 0x007dcb00
Matrix3 Transposed(const Matrix3& m);                                           // 0x004a9b40
Quaternion QuaternionFromMatrix33(const Matrix3& m, float tolerance);           // 0x00472b80
uint32_t FNV1_String8(const char* s, uint32_t seed, int caseMode);              // 0x00932e80

extern const Vector3 kPlanetUp;            // 0x015819a8
extern const uint32_t kCivTextures[12];    // 0x01581be0
extern float kCivTimeScale[4];             // 0x0169cb88
extern float kCivCameraAngles[3];          // 0x0169ca60

// ---------------------------------------------------------------- ref counting
struct IRefCounted {
    virtual int AddRef();
    virtual int Release();
};

struct PropertyList : IRefCounted {};
struct PropertyListPtr {
    PropertyList* mpObject;
    PropertyListPtr() : mpObject(0) {}
    ~PropertyListPtr() { if (mpObject) mpObject->Release(); }
    PropertyList** AsPPTypeParam();        // 0x00a16f40
    PropertyList* get() const { return mpObject; }
};
bool GetFloatProperty(PropertyList* list, uint32_t id, float& out);   // 0x0040cf10

struct cPropertyManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyList** dst);   // +0x2c
};
cPropertyManager* PropertyManager();       // 0x0067de30

// eastl::basic_string<wchar_t> (only construction/destruction is inlined here).
extern wchar_t gEmptyString[];             // 0x01667bac
void operator_delete_array(void* p);       // 0x00f47380 (operator delete[])
struct string16 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAllocator;
    string16() : mpBegin(gEmptyString), mpEnd(gEmptyString), mpCapacity(gEmptyString + 1) {}
    ~string16()
    {
        if ((mpCapacity - mpBegin) > 1 && mpBegin)
            operator_delete_array(mpBegin);
    }
};
struct wstring_ref;
bool operator==(const wstring_ref& a, const wchar_t* b);   // 0x006ab760

// ---------------------------------------------------------------- spatial objects
struct ISpatialObject {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual const Vector3& GetPosition();                       // +0x2c
    virtual const Matrix3& GetOrientationMatrix();              // +0x30
    virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8();
    virtual void* GetModel();                                   // +0xac
};

struct cCityHall {
    uint32_t pad0[13];
    ISpatialObject mSpatial;               // +0x34
};
struct cCityTerritory {
    uint32_t pad0[13];
    ISpatialObject mSpatial;               // +0x34
};
struct cCity {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48();
    virtual void* GetFocus(const Vector3& pos, const Matrix3& orientation);   // +0x4c
    uint32_t pad04[0x120 / 4 - 1];
    ISpatialObject mSpatial;               // +0x120
    uint32_t pad124[(0x324 - 0x124) / 4];
    cCityTerritory* mpTerritory;           // +0x324
    cCityHall* GetCityHall();              // 0x00bd9b40
    void GetCameraSetup(Vector3& pos, float& distance);   // 0x00bd7f70
};

struct cGameData {
    uint32_t pad0[0x120 / 4];
    ISpatialObject mSpatial;               // +0x120
};
struct cTribeData {
    uint32_t pad0[13];
    ISpatialObject mSpatial;               // +0x34
};
cTribeData* GetTribeByIndex(int index);    // 0x00b993c0

// ---------------------------------------------------------------- planet / terrain
struct cPlanetRecordMap {
    void* FindRecord();                    // 0x00ce6950
};
struct cTerrainSphere {
    uint32_t pad0[0x1150 / 4];
    ResourceKey mSpeciesKey;               // +0x1150
    uint32_t pad115c[(0x128c - 0x115c) / 4];
    int mPendingEdits;                     // +0x128c
    struct cRecord* GetPlanetRecord(void* found);         // 0x00c73cb0
    struct cRecord* GetPlanetRecord2(void* found);        // 0x00c73cd0
};
struct cRecord {
    bool& SpeciesFlag(const ResourceKey& key);            // 0x00ba4520
    bool& EmpireFlag(const uint32_t& empire);             // 0x00c735e0
};
void SetSpeciesScanned(const ResourceKey& key, int flag); // 0x00ba57f0
void SetEmpireRelation(void* empire, int relation);       // 0x00ba5a60

struct cPlanet {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual const Quaternion& GetOrientation();                 // +0x30
    virtual void v34(); virtual void v38();
    virtual void SetOrientation(const Quaternion& q);           // +0x3c
    uint32_t pad04[0x13c / 4 - 1];
    cPlanetRecordMap* mpRecords;           // +0x13c
    bool HasFixedAxis();                   // 0x00c708f0
    const Vector3* GetAxis();              // 0x00c70930
    bool IsSpeciesScanned(const ResourceKey& key);        // 0x00c73f10
};
cPlanet* GetActivePlanet();                // 0x01021260 cSPLivingUniverse::GetActivePlanet
uint32_t GetPlayerEmpireID();              // 0x01021090 cSPLivingUniverse::GetPlayerEmpireID

struct cPlanetModelChild {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual bool IsReady();                                     // +0x50
};
struct cPlanetModel {
    uint32_t pad0[9];
    cPlanetModelChild* mpChild;            // +0x24
    void InitMinimap(int param, int a, int b);            // 0x00b8c330 sInitMinimap
    void Activate();                       // 0x00b87dc0
    void AddResourceNodes();               // 0x00b8bba0
};
cPlanetModel* PlanetModel();               // 0x00b3d350

// ---------------------------------------------------------------- nouns / civs
struct cSpeciesProfile {
    void GetUiName(string16& out);         // 0x004da330
};
struct cCivNameList {
    void SetName(const string16& name);    // 0x00b6f380
};
struct cIntMapNode {
    uint32_t pad0[5];
    int mValue;                            // +0x14
};
struct cIntMapIterator {
    cIntMapNode* mpNode;
};
struct cIntMap {
    cIntMapIterator* find(cIntMapIterator* out, const int& key);   // 0x00e5c780 (by value)
};
struct IColorTarget {
    virtual void SetColorIndex(int index);                      // +0x00
};
struct cCivilization {
    uint32_t pad0[13];
    IColorTarget mColor;                   // +0x34
    uint32_t pad38;
    cCivNameList mNames;                   // +0x3c
    int mEffectOwner;                      // +0x40
    cIntMap mColorMap;                     // +0x44
    uint32_t pad48[(0x89 - 0x48) / 4];
    uint8_t pad88;
    bool mHasBanner;                       // +0x89
    uint8_t pad8a[0x298 - 0x8a];
    int mStage;                            // +0x298
    bool IsAtLeastStage4() const { return mStage >= 4 ? true : false; }
    cSpeciesProfile* GetProfile();         // 0x00bef950 (+0x504 = effect anchor)
    void SetSpecies(const ResourceKey& key);             // 0x00bebdd0
    struct cTribeList* GetTribes();        // 0x00bef6c0
    int GetCursorTarget();                 // 0x00b2fa60
};
void RefreshBanner(int owner);             // 0x00b6e1f0

struct cCivPtrVector {
    cCivilization** mpBegin;
    cCivilization** mpEnd;
};
struct cTribeList {
    int* mpBegin;
    int* mpEnd;
};
struct cDataPtrVector {
    void** mpBegin;
    void** mpEnd;
    void** mpCapacity;
    uint32_t mAllocator[2];
    cDataPtrVector(const cDataPtrVector& o);   // 0x00ba95a0
    ~cDataPtrVector();                     // 0x00ae6970
};
struct cGameDataResult {
    uint32_t pad0;
    void** mpBegin;                        // +0x04
    void** mpEnd;                          // +0x08
};

struct cSkinManagerPtr {                   // AutoRefCount<T>
    IRefCounted* mpObject;
    cSkinManagerPtr(IRefCounted* p);       // 0x00572660
    ~cSkinManagerPtr() { if (mpObject) mpObject->Release(); }
};

void* FUN_00cd7d10();
void* FUN_00d3d420();
void* FUN_00accbb0();
void* FUN_00b1e500();

struct cGameNounManager {
    void* GetTerrainEditorTarget();        // 0x00b93960
    uint32_t GetPlayerEmpireOrMinus1();    // 0x00b1f9d0
    cTerrainSphere* GetCurrentTerrainSphere();            // 0x00f67d90
    void* GetEmpireData(uint32_t empire);  // 0x00b25f40
    void DestroyNoun(uint32_t type);       // 0x00b22650
    IRefCounted* GetPlayerData();          // 0x00bfc5f0
    const cDataPtrVector& GetNounList();   // 0x00acd9d0
    void RemoveNoun(void* noun);           // 0x00b225d0
    cCity* GetPlayerCity();                // 0x00b25c30
    cCivilization* GetPlayerCivilization();               // 0x00b25fb0
    cCivPtrVector* GetCivilizations();     // 0x00b25ca0
    cGameDataResult* GetGameDataVector(void* (*a)(), void* (*b)(), void* (*c)(), void* (*d)(),
                                       uint32_t typeID);  // 0x00b21340
};
cGameNounManager* NounManager();           // 0x00b3d300

struct cTerrainEditorTarget {
    void Setup(uint32_t empire, int a, uint32_t id, int b);   // 0x00bf8170
};
void PrepareTerrainEditor();               // 0x00bf55d0

struct cTribe {
    void UpdateRoboTribeness();            // 0x00c8fbb0
    void SetSpeciesProfile(cSpeciesProfile* profile, int flag);   // 0x00c8e830
};
typedef void (cTribe::*TribeMemFn)();
struct cTribeMemFun {   // mem_fun-style functor (non-POD: returned through a hidden pointer)
    TribeMemFn mpFn;
    int mAdjust;
    cTribeMemFun() {}
};
cTribeMemFun ForEachTribe(void** first, void** last, cTribeMemFun fn);   // 0x00cf94e0

// ---------------------------------------------------------------- other managers
struct cGameModeManagerInternal {
    void Reset();                          // 0x00ae3300
    void ExitEditor();                     // 0x00ae3d70
    void SetFocus(void* p);                // 0x00ae46f0
    struct cModeData* mpData_pad[5];
};
struct cModeData {
    int mTribeIndex;
};
struct cGameModeManager {
    uint32_t pad0[5];
    cModeData* mpModeData;                 // +0x14
    void Reset();                          // 0x00ae3300
    void ExitEditor();                     // 0x00ae3d70
    void SetFocus(void* p);                // 0x00ae46f0
};
cGameModeManager* GameModeManager();       // 0x00b26930
void ResetCivUI();                         // 0x00cfea20
void ResetTerrainEditor();                 // 0x00b969e0
void StartNewCiv(uint32_t newMode);        // 0x00ba1c60

struct cTerraformingManager {
    void Activate(int flag);               // 0x00bc08d0
};
cTerraformingManager* TerraformingManager();   // 0x00b3d430

struct cControllerSet {
    void Controller(uint32_t id, int a, int b);   // 0x00676ed0
};
cControllerSet* ControllerSet();           // 0x00675250

struct cNamedObject {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void SetName(uint32_t hash);                        // +0x30
};
extern cNamedObject* gCivPlanetObject;     // 0x0167ea54

struct cModelWorldSetup {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void SetOwner(void* owner);                         // +0x10
    virtual void v14();
    virtual void AddWorld(void* world, int priority);           // +0x18
    virtual void SetLayer(void* layer, uint32_t flags);         // +0x1c
    virtual void v20(); virtual void v24();
    virtual void SetEnabled(int enabled);                       // +0x28
    virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38();
    virtual void v3c(); virtual void v40(); virtual void v44();
    virtual void SetEffect(uint32_t id);                        // +0x48
};
cModelWorldSetup* ModelWorldSetup();       // 0x0067ddc0
void* RenderLayer();                       // 0x0067de00

struct cModelManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18();
    virtual void* GetWorld(uint32_t id);                        // +0x1c
};
cModelManager* ModelManager();             // 0x0067dd80

struct cGonzagoModelWorld {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void Update();                                      // +0x10
    virtual void v14(); virtual void v18();
    virtual bool IsReady(int what);                             // +0x1c
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac();
    virtual void vb0();
    virtual void SetModelVisible(void* model, int visible);     // +0xb4
    virtual void SetModelLOD(void* model, float distance);      // +0xb8
    virtual void vbc(); virtual void vc0(); virtual void vc4();
    virtual void SetModelEffect(void* model, uint32_t id, float* value, int a, int b);   // +0xc8
};
cGonzagoModelWorld* GonzagoModelWorld();   // 0x00b3d520

struct cCameraManager {
    uint8_t pad0[0x364];
    bool mbLocked;                         // +0x364
    void SetTarget(const Vector3& pos, const Quaternion* q, int snap);   // 0x00b12dd0
    void Commit();                         // 0x00b13b50
    void SetTargetPosition(const Vector3* pos, int a, int b);           // 0x00b146a0
};
cCameraManager* CameraManager();           // 0x00b3d280

struct cGameInputManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void LoadTriggerConfig(const char* name, int a, int b);   // +0x10
    uint8_t pad04[0x110 - 4];
    int mLockCount;                        // +0x110
};
cGameInputManager* GameInputManager();     // 0x00b3d250

struct cLocaleInfo {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10();
    virtual const wstring_ref& GetLanguage();                   // +0x14
};
cLocaleInfo* LocaleInfo();                 // 0x0067de40

struct cTerrainCursor {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54();
    virtual void SetTarget(int target);                         // +0x58
};
cTerrainCursor* GetGameTerrainCursor();    // 0x00b30d70

void SpawnEffect(uint32_t id, void* anchor, Vector3* pos, Vector3* dir, int owner, int a,
                 int b);                   // 0x00e3c7c0

struct cGameTimeManager {
    void SetTimeScale(float a, float b, float c, float d);       // 0x00b316d0
    void Pause(uint32_t reason);           // 0x00b32250
};
cGameTimeManager* GameTimeManager();       // 0x00b3d380

struct cBehaviorManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void Reset();                                       // +0x30
};
cBehaviorManager* BehaviorManager();       // 0x00b3d260

struct cEmpire {
    struct cEmpireRecord* GetRecord();     // 0x00c30c60
};
struct cEmpireRecord {
    cSpeciesProfile* GetProfile();         // 0x00bba500
    const ResourceKey& GetSpeciesKey();    // 0x00bb9b80
};
struct cStarManager {
    cEmpire* GetEmpireByID(uint32_t id);   // 0x00ba9370
};
cStarManager* StarManager();               // 0x00b3d2a0

struct cTexturePreload {
    cTexturePreload(int priority);         // 0x007b07e0
    void PreloadTextureList(const ResourceKey& key);   // 0x007b1e90
    bool IsDone();                         // 0x007b19c0
};
struct cTexturePreloadPtr {
    cTexturePreload* mpObject;
    cTexturePreloadPtr& operator=(cTexturePreload* p);  // 0x00b5f950
};
void* operator new(unsigned int size, const char* name, int a, int b, int c, int d);   // 0x00f473a0

struct cSimSingleton {
    cSimSingleton();                       // 0x00ae5c30
    void GetSavedCounts(int& a, int& b, int& c);   // 0x00ae3750
};
extern cSimSingleton* gSimSingleton;       // 0x0167a60c

struct cCounterSet {
    void SetCount(int kind, int count);    // 0x00ae9150
};
cCounterSet* CounterSet();                 // 0x00b3d4a0

struct cCameraController {
    void GetAnglesA(float& a, float& b, float& c);       // 0x00b0f210
    void SetMode(uint32_t id);             // 0x00b11870
    void SetAngles(float a, float b, float c);           // 0x00b10340
    void ResetInterpolation(float a, float b, float c);  // 0x00b10760
    const Vector3* GetFocus(Vector3* out); // 0x00b137d0
};
struct cCameraSet {
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual cCameraController* GetCamera(uint32_t id);          // +0x0c
};
struct cCameraSystem {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual cCameraSet* GetCameraSet(uint32_t id);              // +0x40
};
struct cApp {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual cCameraSystem* GetCameraSystem();                   // +0x50
};
cApp* App();                               // 0x0067dd10

struct cTimeOfDay {
    uint32_t pad0[9];
    float mHours;                          // +0x24
    void SetTime(float t, const Vector3* focus);   // 0x00bc2f00
    static cTimeOfDay* Instance();         // 0x00bc30b0
};

struct cSpeciesManager {
    void SetAvatarSpecies(const ResourceKey& key);        // 0x004df310
    cSpeciesProfile* GetProfile(const ResourceKey& key);  // 0x004df550
    cSpeciesProfile* GetAvatarProfile();   // 0x004df420
};
cSpeciesManager* SpeciesManager();         // 0x00401090

struct cPreloadParams {
    uint32_t mTypeID;
    uint16_t mPriority;
    uint16_t mFlags;
};
struct cResourceManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14();
    virtual bool IsLoaded(const ResourceKey* key);               // +0x18
    virtual bool IsCached(const ResourceKey* key, int flags);    // +0x1c
    virtual void v20(); virtual void v24();
    virtual void Flush();                                        // +0x28
    virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38();
    virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48();
    virtual void Preload(const ResourceKey* key, const cPreloadParams* params);   // +0x4c
};
cResourceManager* ResourceManager();       // 0x00401010

struct cKeyVector {                        // eastl::vector<ResourceKey, sp_vector_allocator>
    ResourceKey* mpBegin;
    ResourceKey* mpEnd;
    ResourceKey* mpCapacity;
    uint32_t mAllocator[2];
    int size() const { return (int)(mpEnd - mpBegin); }
    ResourceKey* erase(ResourceKey* first, ResourceKey* last);   // 0x0050f740
    void clear() { erase(mpBegin, mpEnd); }
    void push_back(const ResourceKey& key);                // 0x004e19a0
};

struct cUIStateObject {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual void SetState(uint32_t id, int a);                  // +0x2c
};
cUIStateObject* UIStateObject();           // 0x0067cb20

struct cLoadingScreen {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual void SetProgressA(int param);                       // +0x2c
    virtual void SetProgressB(int param);                       // +0x30
    void Update(int param);                // 0x00b5e9a0
};
cLoadingScreen* LoadingScreen();           // 0x00b3d230

struct cRenderSettings {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58();
    virtual void PushState(int a, int b);                       // +0x5c
    virtual void PopState(int a, int b);                        // +0x60
};
cRenderSettings* RenderSettings();         // 0x0067dd50

struct cAppSystem {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void SetLoadingVisible(bool visible);               // +0x40
    virtual bool IsLoadingVisible();                            // +0x44
};
cAppSystem* AppSystem();                   // 0x0067dd00

struct cEA_Stopwatch {
    uint64_t GetElapsedTime() const;       // 0x0093a5e0
};

struct cEventLog {
    void SetVisibility(int visible);       // 0x00dd8da0
};
cEventLog* EventLog();                     // 0x00b3d3e0

struct cMessageManager {
    void PostMessage(uint32_t id, void* msg, int a);     // 0x00ae09b0
    void PostString(const char* name, int a, int b, int c, int d, int e);   // 0x00ae0930
    void SetFlag(int f);                   // 0x00adf390
};
cMessageManager* MessageManager();         // 0x00b3d4d0

// 0x50-byte message/locator object (ctor 0x00ad7a30 / 0x00ad79d0, dtor 0x00ad7ad0).
struct cCameraMessage {
    uint32_t data[8];
    float mDistance;                       // +0x20
    uint32_t pad24[11];
    cCameraMessage(void* target);          // 0x00ad7a30
    cCameraMessage(const Vector3& pos, void* from);   // 0x00ad79d0
    ~cCameraMessage();                     // 0x00ad7ad0
    const float* GetPosition();            // 0x00ad7b50
    void* GetTarget();                     // 0x00ad7b70
};
void* MakeCameraTarget(void* p);           // 0x00b18e00
void* AudioListener();                     // 0x00435e90
void Start3dSoundByName(uint32_t id, void* listener, float x, float y, float z);   // 0x00571f80

struct cUIHints {
    void SetEnabled(int a, int b);         // 0x0067c420
};
cUIHints* UIHints();                       // 0x0067cac0

struct cConfigManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void* GetConfig(uint32_t id);                       // +0x30
};
cConfigManager* ConfigManager();           // 0x0067dd30

struct cMissionHooks {
    void Update();                         // 0x00b2a100
};
cMissionHooks* MissionHooks();             // 0x00b3d340

struct cTutorialSystem {
    bool IsEnabled();                      // 0x00e36fa0
    void StartCivTutorial();               // 0x00e36de0
    void StartModeTutorial(int a, uint32_t mode, int b);  // 0x00e3e350
    bool IsReadyA();                       // 0x00e36dd0
    void Advance();                        // 0x00e3b1f0
    bool IsReadyB();                       // 0x00e36e10
};
cTutorialSystem* TutorialSystem();         // 0x00b3d410

struct cSporepediaList {
    uint32_t pad0[0x70 / 4];
    void* mpListHead;                      // +0x70 (intrusive list anchor)
    bool empty() const { return mpListHead == (void*)&mpListHead; }
};
extern cSporepediaList* gSporepedia;       // 0x015fd928

struct cTribeTools {
    void ResetTools(void* tribeID, int flag);   // 0x00ac8cd0
    void Reset();                          // 0x00acd790
};
cTribeTools* TribeTools();                 // 0x00b3d480
void ResetCityLayers();                    // 0x00bed460

// ---------------------------------------------------------------- the strategy
struct cEditorResult {
    virtual void v00(); virtual void v04();
    virtual void Release();                                     // +0x08
    uint32_t pad04[5];
    ResourceKey mSpeciesKey;               // +0x18 (typeID at +0x1c)
};
struct cCityInputStrategy {
    void SetMode(int a, int b);            // 0x00cf0f80
    void SetActive(int active);            // 0x00cf1500
    void RestoreCommunityEditorOrShopping(int category);   // 0x00cf1f50
    void ReturnFromEditor(const ResourceKey& key);        // 0x00cf44c0
};
struct cCivUIPanel {
    void SetVisible(int visible);          // 0x00e042d0
};
struct cCityDisplayStrategy {
    uint32_t pad0[25];
    cCivUIPanel* mpPanel;                  // +0x64
    void ShowLoadGame(int a);              // 0x00ce96a0
    void Refresh();                        // 0x00cec6d0
};
struct cMissionManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void Start();                                       // +0x20
};
struct cMissionManagerPtr {
    cMissionManager* mpObject;
    cMissionManagerPtr& operator=(cMissionManager* p);  // 0x00572620
};
extern cMissionManager* gCivMissionManager;   // 0x0169d3cc

namespace SP {

struct cCivModeStrategy {
    void* vftable;
    uint32_t pad04[9];
    bool mbReturningFromEditor;            // +0x28
    uint8_t pad29[3];
    uint32_t pad2c[5];
    cKeyVector mMandatoryBakedItems;       // +0x40
    cKeyVector mOptionalBakedItems;        // +0x54
    uint32_t pad68[19];
    uint32_t mState;                       // +0xb4 cLoadingState
    uint32_t mPreviousMode;                // +0xb8
    uint32_t mCurrentMode;                 // +0xbc
    uint32_t mFrames;                      // +0xc0
    uint32_t padc4;
    cEA_Stopwatch mLoadTimer;              // +0xc8
    uint32_t padcc[5];
    bool mbInUFOEditorDuringTransitionFlow;   // +0xe0
    uint8_t pade1[3];
    uint32_t pade4;
    cCityInputStrategy* mpInputStrategy;   // +0xe8
    cCityDisplayStrategy* mpDisplayStrategy;  // +0xec
    uint32_t padf0[2];
    int mLastCommunityPlannerActiveCategory;  // +0xf8
    uint32_t padfc;
    cEditorResult* mEditorResult;          // +0x100
    uint32_t pad104;
    cMissionManagerPtr mCivMissionManager; // +0x108
    cTexturePreloadPtr mTexturePreload;    // +0x10c
    uint32_t pad110[4];
    bool mbTutorialPending;                // +0x120

    void PrepareForMode(uint32_t mode);    // 0x00cf71d0
    void ResetFromPreviousMode();          // 0x00cf8560
    void InitCityCivModeFromLaunchScreen();   // 0x00cfa410
    void StartCivDay();                    // 0x00cf8fd0
    void CollectBakedItems();              // 0x00cfb890
    void RequestBakedItems();              // 0x00cfb0b0
    void SetupCityUI();                    // 0x00cf9190
    bool AreSimulatorsReady();             // 0x00cf7880
    void RegisterSimulators();             // 0x00cfb040
    void* GetCameraTarget(int a);          // 0x00cf7d40
    void ShowIntro();                      // 0x00cf7ad0
    void ContinueLoading(int param);
};
void CloseLoadingPanels();                 // 0x00cf7150

// @ 0x00cfbc10 ?ContinueLoading@cCivModeStrategy@SP@@
void cCivModeStrategy::ContinueLoading(int param)
{
    uint32_t prevMode = mPreviousMode;
    uint32_t curMode = mCurrentMode;

    if (PlanetModel())
        PlanetModel()->InitMinimap(param, 0, 0);

    switch (mState) {
    case 0: {
        mState = 1;
        PrepareForMode(prevMode);
        if (prevMode != kGameEditMode && prevMode != kGameCiv && prevMode != kEditorMode &&
            prevMode != kLoadGameMode)
            ResetFromPreviousMode();
        if (prevMode == kLoadGameMode)
            mbInUFOEditorDuringTransitionFlow = true;
        if (prevMode != kEditorMode) {
            GameModeManager()->Reset();
            ResetCivUI();
        }

        // Orient the planet: base axis, then the configured rotation about it.
        cPlanet* planet = GetActivePlanet();
        PropertyListPtr propList;
        PropertyManager()->GetPropertyList(0x1106d054, 0x2ae0c7e, propList.AsPPTypeParam());
        float angle = 0.0f;
        GetFloatProperty(propList.get(), 0x195e030, angle);
        angle = angle * 0.017453292f;
        const Vector3* axis;
        if (planet->HasFixedAxis())
            axis = &kPlanetUp;
        else
            axis = planet->GetAxis();
        planet->SetOrientation(QuaternionFromDirections(kPlanetUp, *axis));
        float half = angle * 0.5f;
        float s = (float)sin(half);
        Quaternion spin;
        spin.x = s * axis->x;
        spin.y = axis->y * s;
        spin.z = axis->z * s;
        spin.w = (float)cos(half);
        Quaternion orientation = planet->GetOrientation() * spin;
        planet->SetOrientation(orientation);

        uint32_t mode = prevMode;
        if (mode == kGGEMode || mode == kGameTribe) {
            PrepareTerrainEditor();
            cTerrainEditorTarget* target =
                (cTerrainEditorTarget*)NounManager()->GetTerrainEditorTarget();
            target->Setup(NounManager()->GetPlayerEmpireOrMinus1(), 1, 0x53dbcf2, 0);
        }
        ResourceKey speciesKey = NounManager()->GetCurrentTerrainSphere()->mSpeciesKey;
        if (!planet->IsSpeciesScanned(speciesKey)) {
            NounManager()->GetCurrentTerrainSphere()
                ->GetPlanetRecord(planet->mpRecords->FindRecord())
                ->SpeciesFlag(speciesKey) = true;
            SetSpeciesScanned(speciesKey, 1);
        }
        uint32_t empire = NounManager()->GetPlayerEmpireOrMinus1();
        if (mode == kGGEMode || mode == kGameTribe) {
            SetEmpireRelation(NounManager()->GetEmpireData(empire), 7);
            NounManager()->GetCurrentTerrainSphere()
                ->GetPlanetRecord2(planet->mpRecords->FindRecord())
                ->EmpireFlag(empire) = true;
        }

        if (mode == kGGEMode || mode == (uint32_t)kNoMode || mode == kGameTribe) {
            if (mode == kGameTribe) {
                // Tribe -> civ: drop the tribe-stage nouns except the player's.
                NounManager()->DestroyNoun(0x1be418e);
                NounManager()->DestroyNoun(0x3a2511e);
                cSkinManagerPtr player(NounManager()->GetPlayerData());
                {
                    cDataPtrVector nouns(NounManager()->GetNounList());
                    for (void** it = nouns.mpBegin; it != nouns.mpEnd; ++it) {
                        if (*it != player.mpObject)
                            NounManager()->RemoveNoun(*it);
                    }
                }
            } else {
                InitCityCivModeFromLaunchScreen();
            }
            ControllerSet()->Controller(0xd082675a, 8, 1);
            NounManager()->GetCurrentTerrainSphere()->mPendingEdits = 0;
        } else if (mode == kLoadGameMode) {
            ResetTerrainEditor();
            GameModeManager()->ExitEditor();
        }

        gCivPlanetObject->SetName(FNV1_String8("Planet_Civ", 0x811c9dc5, 1));
        cModelWorldSetup* setup = ModelWorldSetup();
        if (setup) {
            setup->SetOwner(gCivPlanetObject);
            setup->AddWorld(GonzagoModelWorld(), 3);
            void* world = ModelManager()->GetWorld(0x3fbae24);
            if (world)
                setup->AddWorld(world, 0);
            setup->SetLayer(RenderLayer(), 0x20007);
            setup->SetEffect(0x5e51b92);
            setup->SetEnabled(1);
        }
        TerraformingManager()->Activate(0);
        PlanetModel()->Activate();

        if (mode != kEditorMode) {
            Vector3 focus;
            if (mode == kGameTribe) {
                IRefCounted* player = NounManager()->GetPlayerData();
                if (player)
                    focus = ((cGameData*)player)->mSpatial.GetPosition();
            } else {
                ISpatialObject* spatial;
                int tribe = GameModeManager()->mpModeData->mTribeIndex;
                if (tribe == -1) {
                    cGameData* data = (cGameData*)NounManager()->GetPlayerData();
                    if (data)
                        spatial = &data->mSpatial;
                    else
                        spatial = &((cGameData*)NounManager()->GetPlayerCity())->mSpatial;
                } else {
                    spatial = &GetTribeByIndex(tribe)->mSpatial;
                }
                focus = spatial->GetPosition();
            }
            if (CameraManager()) {
                cCity* city = NounManager()->GetPlayerCity();
                if (city) {
                    cCityHall* hall = city->GetCityHall();
                    if (hall) {
                        ISpatialObject* hallSpatial = &hall->mSpatial;
                        Matrix3 m = Transposed(hallSpatial->GetOrientationMatrix());
                        m.m[0] = -m.m[0];
                        m.m[1] = -m.m[1];
                        m.m[2] = -m.m[2];
                        m.m[3] = -m.m[3];
                        m.m[4] = -m.m[4];
                        m.m[5] = -m.m[5];
                        Quaternion q = QuaternionFromMatrix33(m, 0.0f);
                        CameraManager()->SetTarget(hallSpatial->GetPosition(), &q, 1);
                        CameraManager()->Commit();
                    }
                } else {
                    CameraManager()->SetTargetPosition(&focus, 1, 1);
                }
            }
        }

        GameInputManager()->LoadTriggerConfig("TriggerConfigTribeGame", 0, 1);
        const char* wasd = "TriggerConfigWASD";
        if (LocaleInfo()->GetLanguage() == L"fr-fr")
            wasd = "TriggerConfigWASD_fr-fr";
        GameInputManager()->LoadTriggerConfig(wasd, 0, 0);
        break;
    }

    case 1: {
        mState = 2;
        mFrames = 0;
        cCivilization* civ = NounManager()->GetPlayerCivilization();
        if (civ != 0) {
            cTerrainCursor* cursor = GetGameTerrainCursor();
            cursor->SetTarget(civ->GetCursorTarget());
        }
        if (prevMode == kGameTribe)
            StartNewCiv(kGameCiv);
        if (prevMode == kGameTribe || prevMode == kGGEMode || prevMode == (uint32_t)kNoMode) {
            Vector3 dir;
            Vector3 pos;
            int owner = NounManager()->GetPlayerCivilization()->mEffectOwner;
            pos.x = 0; pos.y = 0; pos.z = 0;
            dir.x = 0; dir.y = 0; dir.z = 0;
            SpawnEffect(0x3b38f92a,
                        (char*)NounManager()->GetPlayerCivilization()->GetProfile() + 0x504,
                        &dir, &pos, owner, 0, 0);
        }
        if (prevMode == kLoadGameMode) {
            // Loaded game: rename every civilization after the player species.
            string16 name;
            cSpeciesProfile* profile = civ->GetProfile();
            if (!profile) {
                cEmpireRecord* record =
                    StarManager()->GetEmpireByID(GetPlayerEmpireID())->GetRecord();
                profile = record->GetProfile();
                ResourceKey key = record->GetSpeciesKey();
                cCivPtrVector* civs = NounManager()->GetCivilizations();
                for (cCivilization** it = civs->mpBegin; it != civs->mpEnd; ++it)
                    (*it)->SetSpecies(key);
            }
            profile->GetUiName(name);
            cCivPtrVector* civs = NounManager()->GetCivilizations();
            cCivilization** end = civs->mpEnd;
            for (cCivilization** it = civs->mpBegin; it != end; ++it) {
                (*it)->mNames.SetName(name);
                cCivilization* c = *it;
                int colorKey = (c == civ) ? 13 : 1;
                cIntMapIterator found;
                IColorTarget* color = &c->mColor;
                color->SetColorIndex(c->mColorMap.find(&found, colorKey)->mpNode->mValue);
                if ((*it)->mHasBanner)
                    RefreshBanner((*it)->mEffectOwner);
            }
        }
        GameTimeManager()->SetTimeScale(kCivTimeScale[0], kCivTimeScale[1], kCivTimeScale[2],
                                        kCivTimeScale[3]);
        uint32_t mode = prevMode;
        if (mode != kEditorMode && mode != kLoadGameMode)
            BehaviorManager()->Reset();
        cGameDataResult* tribes = NounManager()->GetGameDataVector(
            FUN_00cd7d10, FUN_00d3d420, FUN_00accbb0, FUN_00b1e500, 0x18c6d19);
        cTribeMemFun fn;
        fn.mpFn = &cTribe::UpdateRoboTribeness;
        fn.mAdjust = 0;
        ForEachTribe(tribes->mpBegin, tribes->mpEnd, fn);

        if (mode != kEditorMode) {
            mpInputStrategy->SetMode(0, 0);
            if (!gSporepedia || gSporepedia->empty() || mode != kLoadGameMode) {
                mTexturePreload = new ("Simulator", 0, 0, 0, 0) cTexturePreload(-1);
                ResourceKey key;
                key.typeID = 0xefbda3ff;
                key.groupID = 0x40464100;
                for (int i = 0; i < 12; i++) {
                    key.instanceID = kCivTextures[i];
                    mTexturePreload.mpObject->PreloadTextureList(key);
                }
            }
            if (!gSimSingleton)
                gSimSingleton = new ("Simulator/SimSingleton", 0, 0, 0, 0) cSimSingleton();
            int counts[3];
            gSimSingleton->GetSavedCounts(counts[0], counts[1], counts[2]);
            if (counts[0] > 0)
                CounterSet()->SetCount(0, counts[0]);
            if (counts[1] > 0)
                CounterSet()->SetCount(1, counts[1]);
            if (counts[2] > 0)
                CounterSet()->SetCount(2, counts[2]);
        }
        if (mode == kLoadGameMode) {
            mpDisplayStrategy->ShowLoadGame(0);
            cCivilization* player = NounManager()->GetPlayerCivilization();
            if (player && player->IsAtLeastStage4())
                mpDisplayStrategy->mpPanel->SetVisible(1);
        }

        cCameraController* camera = 0;
        cCameraSet* cameras = App()->GetCameraSystem()->GetCameraSet(0xe3057616);
        if (cameras) {
            camera = cameras->GetCamera(0x11966ed);
            if (camera) {
                float a, b, c;
                camera->GetAnglesA(a, b, c);
                camera->SetMode(0xf31f49a1);
                camera->SetAngles(a, b, c);
                camera->ResetInterpolation(kCivCameraAngles[0], kCivCameraAngles[1],
                                           kCivCameraAngles[2]);
            }
        }

        if (mode == kEditorMode) {
            if (!mbReturningFromEditor) {
                mpInputStrategy->RestoreCommunityEditorOrShopping(
                    mLastCommunityPlannerActiveCategory);
                cEditorResult* result = mEditorResult;
                mLastCommunityPlannerActiveCategory = -1;
                if (result && result->mSpeciesKey.typeID == 0x2b978c46) {
                    // Came back from the creature editor: apply the new species everywhere.
                    SpeciesManager()->SetAvatarSpecies(result->mSpeciesKey);
                    cCivPtrVector* civs = NounManager()->GetCivilizations();
                    int count = (int)(civs->mpEnd - civs->mpBegin);
                    for (int i = 0; i < count; i++) {
                        cCivilization* c = civs->mpBegin[i];
                        c->SetSpecies(mEditorResult->mSpeciesKey);
                        c->GetTribes();
                        cTribeList* list = c->GetTribes();
                        for (int* t = list->mpBegin; t != list->mpEnd; ++t)
                            TribeTools()->ResetTools((void*)*t, 0);
                    }
                    cGameDataResult* all = NounManager()->GetGameDataVector(
                        FUN_00cd7d10, FUN_00d3d420, FUN_00accbb0, FUN_00b1e500, 0x18c6d19);
                    int n = (int)(all->mpEnd - all->mpBegin);
                    for (int i = 0; i < n; i++)
                        ((cTribe*)all->mpBegin[i])
                            ->SetSpeciesProfile(
                                SpeciesManager()->GetProfile(mEditorResult->mSpeciesKey), 0);
                    if (mEditorResult) {
                        cEditorResult* old = mEditorResult;
                        mEditorResult = 0;
                        old->Release();
                    }
                }
            } else if (mEditorResult == 0) {
                mbReturningFromEditor = false;
                GameTimeManager()->Pause(0x4bf38a6);
                GameInputManager()->mLockCount--;
                cCameraManager* cam = CameraManager();
                if (cam)
                    cam->mbLocked = true;
                mpInputStrategy->SetActive(1);
                mpDisplayStrategy->mpPanel->SetVisible(1);
                mState = 10;
            }
        } else if (mode == kGGEMode || mode == (uint32_t)kNoMode || mode == kGameTribe) {
            cTimeOfDay* tod = cTimeOfDay::Instance();
            if (tod) {
                float t = tod->mHours * 0.41666666f;
                if (!(t > 0.0f))
                    t = 36000.0f;
                Vector3 focus;
                tod->SetTime(t, camera->GetFocus(&focus));
            }
            StartCivDay();
        }
        break;
    }

    case 2:
        if (mTexturePreload.mpObject != 0 && !mTexturePreload.mpObject->IsDone())
            break;
        mState = 3;
        mFrames = 0;
        if (prevMode == kEditorMode) {
            if (mbReturningFromEditor == true) {
                cEditorResult* result = mEditorResult;
                mbReturningFromEditor = false;
                if (result != 0) {
                    mpInputStrategy->ReturnFromEditor(result->mSpeciesKey);
                    mState = 10;
                }
            }
        } else if (prevMode == kLoadGameMode) {
            mCivMissionManager = gCivMissionManager;
            mCivMissionManager.mpObject->Start();
        }
        break;

    case 3:
        if (mFrames > 0 && PlanetModel()->mpChild->IsReady()) {
            PlanetModel()->AddResourceNodes();
            mState = 4;
            mFrames = 0;
        }
        break;

    case 4:
        if (mFrames > 4) {
            mState = 5;
            mMandatoryBakedItems.clear();
            mOptionalBakedItems.clear();
            if (prevMode != kEditorMode) {
                mpDisplayStrategy->Refresh();
                CollectBakedItems();
            } else if (mEditorResult) {
                mMandatoryBakedItems.push_back(mEditorResult->mSpeciesKey);
            }
            for (int i = 0; i < mMandatoryBakedItems.size(); i++) {
                ResourceKey key = mMandatoryBakedItems.mpBegin[i];
                if (key.instanceID != 0 && !ResourceManager()->IsLoaded(&key)) {
                    cPreloadParams params;
                    params.mTypeID = 0x2ea8fb98;
                    params.mPriority = 0;
                    params.mFlags = 1;
                    ResourceManager()->Preload(&key, &params);
                }
            }
            RequestBakedItems();
            if (prevMode != kEditorMode) {
                ResetCityLayers();
                SetupCityUI();
                TribeTools()->Reset();
                UIStateObject()->SetState(0x8bff672a, 0);
            }
        }
        LoadingScreen()->SetProgressA(param);
        LoadingScreen()->SetProgressB(param);
        break;

    case 5: {
        RenderSettings()->PushState(0x16, 2);
        ResourceManager()->Flush();
        GonzagoModelWorld()->Update();
        SpeciesManager()->GetAvatarProfile();
        bool pending = false;
        for (int i = 0; i < mMandatoryBakedItems.size(); i++) {
            if (!ResourceManager()->IsCached(&mMandatoryBakedItems.mpBegin[i], 0) &&
                ResourceManager()->IsLoaded(&mMandatoryBakedItems.mpBegin[i])) {
                pending = true;
                break;
            }
        }
        if (!GonzagoModelWorld()->IsReady(2))
            pending = true;
        if (!AreSimulatorsReady() || pending) {
            if (!AppSystem()->IsLoadingVisible())
                AppSystem()->SetLoadingVisible(true);
            break;
        }
        if (AppSystem()->IsLoadingVisible() == true)
            AppSystem()->SetLoadingVisible(false);
        RenderSettings()->PopState(0x16, 2);
        RegisterSimulators();
        mState = 6;
        break;
    }

    case 6:
        if (mLoadTimer.GetElapsedTime() <= 1000)
            break;
        if (prevMode != kEditorMode && prevMode != kLoadGameMode) {
            EventLog()->SetVisibility(1);
            if (!gSporepedia || gSporepedia->empty()) {
                cCity* city = NounManager()->GetPlayerCity();
                CloseLoadingPanels();
                cCameraMessage cityTarget(MakeCameraTarget(GetCameraTarget(0)));
                MessageManager()->PostMessage(0x9e430ff6, &cityTarget, 0);
                cCityHall* hall = city->GetCityHall();
                cCameraMessage hallTarget(hall ? (void*)&hall->mSpatial : 0);
                ISpatialObject* territory = &city->mpTerritory->mSpatial;
                GameModeManager()->SetFocus(city->GetFocus(territory->GetPosition(),
                                                           territory->GetOrientationMatrix()));
                const float* p = hallTarget.GetPosition();
                Start3dSoundByName(0xc697a2e5, AudioListener(), p[0], p[1], p[1]);
                MessageManager()->SetFlag(1);
                UIHints()->SetEnabled(1, 1);
                if (!ConfigManager()->GetConfig(0x4ea96cb))
                    ShowIntro();
                MessageManager()->PostMessage(0xc7c230ca, &hallTarget, 0);
                Vector3 camPos;
                float camDistance;
                city->GetCameraSetup(camPos, camDistance);
                cCameraMessage cameraMsg(camPos, hallTarget.GetTarget());
                cameraMsg.mDistance = camDistance;
                MessageManager()->PostMessage(0xb3393b83, &cameraMsg, 0);
                cGonzagoModelWorld* world = GonzagoModelWorld();
                ISpatialObject* hallSpatial = &hall->mSpatial;
                world->SetModelVisible(hallSpatial->GetModel(), 0);
                world->SetModelLOD(hallSpatial->GetModel(), 3.402823466e+38F);
                float zero = 0.0f;
                world->SetModelEffect(hallSpatial->GetModel(), 0x13, &zero, 1, 0);
                MessageManager()->PostString("TRG2CVG_CivStart", 1, 0, 0, 0, 0);
                MissionHooks()->Update();
            }
        }
        if (mbTutorialPending && prevMode != kEditorMode && TutorialSystem()->IsEnabled() &&
            (!gSporepedia || gSporepedia->empty())) {
            TutorialSystem()->StartCivTutorial();
            mState = 8;
        } else {
            mState = 7;
        }
        break;

    case 7:
        if ((!gSporepedia || gSporepedia->empty()) && curMode == kGameCiv &&
            prevMode != kEditorMode) {
            if (TutorialSystem()->IsEnabled())
                TutorialSystem()->StartModeTutorial(0, curMode, 1);
            else
                GameTimeManager()->Pause(0x4bf38a7);
        }
        mState = 10;
        break;

    case 8:
        if (TutorialSystem()->IsReadyA()) {
            TutorialSystem()->Advance();
            mState = 9;
        }
        break;

    case 9:
        if (TutorialSystem()->IsReadyB())
            mState = 7;
        break;

    default:
        mState = 10;
        break;
    }

    LoadingScreen()->Update(param);
}

}  // namespace SP
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct cGameNounManager {
    void GetGameDataVector(int, int, int, int, unsigned int); // 0x00b21340
};
}
