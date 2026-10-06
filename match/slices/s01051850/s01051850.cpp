// Slice s01051850 — 0x01051850, 3987 bytes.
//
// Simulator::cToolManager::HandleMessage(uint32_t messageID, void* pMessage)
// (App::IUnmanagedMessageListener override; the listener base sits at +0x1c of cToolManager,
// so `this` is the listener subobject and every field offset below is relative to the full
// object: +0x20 ResourceKey, +0x2c Vector3, +0x290 Vector3).  Identification: the vftable at
// 0x0149add0 is { deleting-dtor thunk (sub ecx,0x1c), this function } and is stored at +0x1c by
// the ctor 0x0104f960 / dtor 0x0104f740, which also own the tool-strategy hash_map (+0x38) and
// the 26 tool-fail LocalizedStrings (+0x74) of ModAPI's cToolManager (size 0x29c).
//
// The message payload carries a uint32 at +0, another at +8 and a Transform* at +0x28.
// Message IDs handled: 0x05e667a2, 0x04a32d09, 0x044f1189, 0x0611691f, 0x06116922,
// 0x06117665, 0x0612d770, 0x06255124, 0x0643d5cb, 0x0643d5cc, 0x0653a95b, 0x06565534,
// 0x066605a6, 0x0668af00; anything else returns false.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no EH frame although locals have dtors; scalar SSE float math).
//
// @ 0x01051850

typedef unsigned int size_t;
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;

inline void* operator new(size_t, void* p) throw() { return p; }
inline void  operator delete(void*, void*) throw() {}
void EASTL_allocator_deallocate(void* p);   // 0x00f47380 (operator delete[])

// ---------------------------------------------------------------------------------------
// Math
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
    bool operator!=(const Vector3& b) const { return x != b.x || y != b.y || z != b.z; }
};
struct Quaternion {
    float x, y, z, w;
    Quaternion() {}
    Quaternion(const Quaternion& o) : x(o.x), y(o.y), z(o.z), w(o.w) {}
};
struct Matrix3 { float m[9]; };

// rw::math::fpu::QuaternionFromMatrix33<float,0> (cdecl, result by value)
Quaternion QuaternionFromMatrix33(const Matrix3& m, float tolerance);   // 0x00472b80
Matrix3 Matrix3FromQuaternion(const Quaternion& q);   // 0x0059c190 (cdecl, result by value)

extern Vector3 kInvalidPosition;   // 0x016e12cc (runtime-initialized copy)

struct ResourceKey {
    uint32_t instanceID, typeID, groupID;
};
struct ResourceKeyZ {   // default-constructed key (zeroed)
    uint32_t instanceID, typeID, groupID;
    ResourceKeyZ() : instanceID(0), typeID(0), groupID(0) {}
    ResourceKeyZ& operator=(const ResourceKey& o) {
        instanceID = o.instanceID; typeID = o.typeID; groupID = o.groupID; return *this;
    }
};

// Transform (ctor 0x00409930): flags +0, revision +2, offset +4, scale +0x10, rotation +0x14
struct Transform {
    uint16_t mFlags;
    uint16_t mnRevision;
    Vector3 mOffset;
    float mfScale;
    Matrix3 mRotation;

    Transform();                                            // 0x00409930
    Vector3 GetOffset() const { return mOffset; }
    void SetOffset(const Vector3& v) { mFlags |= 4; mOffset = v; mnRevision++; }
    void SetRotation(const Matrix3& m) { mRotation = m; mnRevision++; mFlags |= 2; }
    void SetScale(float s) { mnRevision++; mfScale = s; }
};

// Same layout, other TU (ctor 0x00434040, SetOffset out of line at 0x00571d40)
struct EffectTransform {
    uint16_t mFlags;
    uint16_t mnRevision;
    Vector3 mOffset;
    float mfScale;
    Matrix3 mRotation;

    EffectTransform();                                      // 0x00434040
    void SetOffset(const Vector3& v);                       // 0x00571d40
    void SetRotation(const Matrix3& m) { mRotation = m; mFlags |= 2; mnRevision++; }
};

// ---------------------------------------------------------------------------------------
// EASTL-ish containers
template <typename T>
struct sp_vector {   // 0x14 bytes, storage carries a header dword before the data
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[2];

    void DoInsertValue(T* position, const T& value);   // 0x004e3e10
    void push_back(const T& value)                          // inline; out-of-line copy 0x004e19a0
    {
        if (mpEnd < mpCapacity)
            ::new(mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
    T& back() { return *(mpEnd - 1); }
};

struct cPlantProfile;
struct PlantProfileArray {   // 0x418 bytes: fixed_vector<cPlantProfile*, 256>
    cPlantProfile** mpBegin;
    cPlantProfile** mpEnd;
    cPlantProfile** mpCapacity;
    uint32_t mAllocator[2];
    uint32_t mHeader;            // +0x14 (zero = inline buffer)
    cPlantProfile* mBuffer[256]; // +0x18

    PlantProfileArray(int n, cPlantProfile* const& value);   // 0x00ac1060
    ~PlantProfileArray()
    {
        if (mpBegin && ((int*)mpBegin)[-1])
            EASTL_allocator_deallocate(mpBegin);
    }
};

// ---------------------------------------------------------------------------------------
// Simulator types (only what is used here)
struct IVisualEffect {
    virtual int AddRef();
    virtual int Release();
    virtual void Start(int flags);                          // +0x08
    virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void SetTransform(const EffectTransform& t);    // +0x18
};
struct IVisualEffectPtr {
    IVisualEffect* mpObject;
    IVisualEffectPtr() : mpObject(0) {}
    ~IVisualEffectPtr() { if (mpObject) mpObject->Release(); }
    IVisualEffect** AsPPTypeParam();                        // 0x00a16f40
    IVisualEffect* get() const { return mpObject; }
    IVisualEffect* operator->() const { return mpObject; }
};

struct IEffectsManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool CreateVisualEffect(uint32_t instanceID, uint32_t groupID, IVisualEffect** dst); // +0x2c
};
IEffectsManager* EffectsManager();          // 0x0067ddd0
IEffectsManager* EffectsManager2();         // 0x0067de30

struct IMessageManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14();
    virtual void PostMSG(uint32_t messageID, void* pData, void* p2, int p3);  // +0x18
};
IMessageManager* MessageManager();          // 0x0067dcc0

struct cSpatialObjectI {   // cSpatialObject vtable view
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual const Vector3& GetPosition();                   // +0x2c
    virtual const Quaternion& GetOrientation();             // +0x30
    virtual void v34();
    virtual void SetPosition(const Vector3& v);             // +0x38
    virtual void SetOrientation(const Quaternion& q);       // +0x3c
};

struct cToolEffectHolder {
    uint32_t pad[0x38 / 4];
    int mEffectHandle;                                      // +0x38
};
struct cToolEffectHost {
    cToolEffectHolder* Add(const Vector3& pos, float radius);   // 0x00ae41b0
};
cToolEffectHost* ToolEffectHost();          // 0x00b26930

struct IPlanetEffects {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50();
    virtual int AttachEffect(const Transform& t, IVisualEffect* effect);    // +0x54
    virtual void v58(); virtual void v5c(); virtual void v60();
    virtual void PlaceAt(const Transform& t, uint32_t id, int flags);       // +0x64
};
struct cPlanetModel {
    uint32_t pad[0x24 / 4];
    IPlanetEffects* mpEffects;                              // +0x24
    Quaternion BuildSurfaceOrientation(const Vector3& pos); // 0x00b7f190
};
cPlanetModel* PlanetModel();                // 0x00b3d350

struct cSimulationEvent {   // 0x30 bytes; ctor 0x00ad79d0, dtor 0x00ad7ad0
    uint32_t pad[0x30 / 4];
    cSimulationEvent(const Vector3& pos, const Quaternion& orientation);   // 0x00ad79d0
    ~cSimulationEvent();                                    // 0x00ad7ad0
};
struct cGameModeState {
    uint32_t GetModeID(const char* name);                   // 0x00ad7db0
    bool IsInEditor();                                      // 0x00ac80f0
    void Trigger(uint32_t id, cSimulationEvent* evt, int flags);   // 0x00ae09b0
    void Announce(const char* name, int a, int b, int c, int d, int e);  // 0x00ae0930
};
cGameModeState* GameModeState();            // 0x00b3d4d0

void TriggerAdventureEvent(const char* name, uint32_t id, int flag);   // 0x01041c50 (cdecl)

struct cPlanetObjectData {   // 0x2c bytes
    uint32_t pad[0x2c / 4];
    cPlanetObjectData(int type, const Vector3& pos);       // 0x0104e290
};
struct PlanetObjectVector {
    cPlanetObjectData* mpBegin;
    cPlanetObjectData* mpEnd;
    cPlanetObjectData* mpCapacity;
    uint32_t mAllocator[2];
    void push_back_planetobj(const cPlanetObjectData& v);   // 0x00acbbe0 (vector::push_back)
};

struct cPlantProfile {
    uint32_t pad[0x504 / 4];
    ResourceKey mKey;                                       // +0x504
    uint32_t pad2[(0x57c - 0x510) / 4];
    uint32_t mPlantType;                                    // +0x57c
};

struct cPlanetRecord;
struct cStarRecordView {
    void SetSpeciesKey(const ResourceKey& key);             // 0x00bb9b90
};
struct cPlanetRecord {
    uint32_t pad[0xbc / 4];
    sp_vector<ResourceKey> mPlantSpecies;                   // +0xbc
    sp_vector<ResourceKey> mAnimalSpecies;                  // +0xd0
    uint32_t pad2[(0x134 - 0xe4) / 4];
    PlanetObjectVector mPlanetObjects;                      // +0x134
    uint32_t GetID();                                       // 0x00ce6950
    cStarRecordView* GetStarView();                         // 0x00b8de30
};

struct PlantSwapData {   // 0x50 bytes; ctor 0x0104ef00, dtor 0x0104e6f0
    sp_vector<ResourceKey> mOldPlants;                      // +0x00
    sp_vector<ResourceKey> mNewPlants;                      // +0x14
    sp_vector<ResourceKey> mOldAnimals;                     // +0x28
    sp_vector<ResourceKey> mNewAnimals;                     // +0x3c
    PlantSwapData();                                        // 0x0104ef00
    ~PlantSwapData();                                       // 0x0104e6f0
};
struct cPlanetSim {
    void ApplySwap(PlantSwapData& data);                    // 0x00c80780
};
struct cPlanet {
    uint32_t pad[0x13c / 4];
    cPlanetRecord* mpPlanetRecord;                          // +0x13c
    void ReplaceSpecies(const ResourceKey& key, int a, int b);   // 0x00c74690
    cPlanetSim* GetPlanetSim();                             // 0x008414c0
    int GetTechLevel();                                     // 0x00c70e00
};
cPlanet* GetActivePlanet();                 // 0x01021260
cPlanetRecord* GetActivePlanetRecord();     // 0x010212a0
cPlanetRecord* GetPlayerHomePlanet();       // 0x01021370

struct cSpeciesManager {
    void GetMatchingPlantProfiles(PlantProfileArray& dst, int count, uint32_t type);  // 0x004dfd50
    cPlantProfile* GetPlantProfile(const ResourceKey& key);     // 0x004df440
    cPlantProfile* GetProfile(const ResourceKey& key);          // 0x004df550
};
cSpeciesManager* SpeciesManager();          // 0x00401090

uint32_t GetReplacementSpecies(cPlantProfile* profile);     // 0x01041d30 (cdecl)
struct cSpeciesPool {
    cPlantProfile* Pick(uint32_t id);                       // 0x00ac10a0
};
cSpeciesPool* SpeciesPool();                // 0x00b3d450

struct cTerraformingManager {
    int GetTerraformLevel(cPlanetRecord* rec);                          // 0x00bbc670
    ResourceKey GetPlantKey(int level, uint32_t type, cPlanetRecord* rec);      // 0x00bbc870
    ResourceKey GetAnimalKey(int level, int kind, cPlanetRecord* rec);          // 0x00bbc950
    ResourceKey GetCreatureKey(int level, cPlanetRecord* rec);                  // 0x00bbca30
};
cTerraformingManager* TerraformingManager();    // 0x00b3d430

struct cTerrainObjectList {
    void Clear();                                           // 0x00c53a90
};
struct cTerrainObjectEntry {
    uint32_t pad[2];
    cTerrainObjectList mList;                               // +0x08
};
struct cTerrainObjectMap {
    cTerrainObjectEntry& operator[](const uint32_t& key);   // 0x00ba4e60
};
struct cTerrainSphere {
    uint32_t pad[0x11c0 / 4];
    cTerrainObjectMap mObjects;                             // +0x11c0
};

struct cCreatureAnimal {
    uint32_t pad[0xc0 / 4];
    cSpatialObjectI mSpatial;                               // +0xc0
    uint32_t pad2[(0x135 - 0xc4) / 4];
    uint8_t pad3;
    bool mbAlive;                                           // +0x135
    uint8_t pad4[0xb5e - 0x136];
    bool mbIsPlayer;                                        // +0xb5e
    bool IsInTribe();                                       // 0x00c0c0e0
    const ResourceKey& GetSpeciesKey();                     // 0x00c0bc00
};
struct CreatureVector {
    cCreatureAnimal** mpBegin;
    cCreatureAnimal** mpEnd;
};

struct cOrnament {
    void SetModelKey(uint32_t instance, int type, uint32_t group);  // 0x00c6f770
    uint32_t pad[0x70 / 4];
    cSpatialObjectI mSpatial;                               // +0x70
};
struct cTerrainEditorView {
    cTerrainSphere* GetCurrentTerrainSphere();              // 0x00f67d90
};
struct cGameNounManager {
    cOrnament* CreateNoun(uint32_t nounID);                 // 0x00b20c60
    const CreatureVector& GetCreatures();                   // 0x00ace2f0
    cTerrainSphere* GetCurrentTerrainSphere();              // 0x00f67d90
};
cGameNounManager* NounManager();            // 0x00b3d300

struct cPositionTracker {
    void Update(const ResourceKey& key, const Vector3& pos);    // 0x00acf3e0
};
cPositionTracker* PositionTracker();        // 0x00b3d480

struct cUFO {
    void SetToolActive(bool b);                             // 0x00c37130
    void PopToDestination();                                // 0x00c37e60
    void SetDestination(const Vector3& pos);                // 0x00c3bfe0
    void SetDestinationStar(uint32_t star);                 // 0x00c3c190
    uint32_t pad[0x34 / 4];
    cSpatialObjectI mSpatial;                               // +0x34
    uint32_t pad2[(0x75c - 0x38) / 4];
    uint32_t mDestinationStar;                              // +0x75c
};
struct cUFOSimulator {
    cUFO* GetPlayerUFO();                                   // 0x00a1ad60
    void PopState();                                        // 0x00ffc0b0
    void ClearPending();                                    // 0x00ffc0d0
    uint32_t pad[0x18 / 4];
    bool mb18;                                              // +0x18
    uint8_t pad19[7];
    bool mb20;                                              // +0x20
};
cUFOSimulator* UFOSimulator();              // 0x00ffbe50

struct cSpaceInventory {
    virtual void v00();
    // slot 0x8c
    virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20();
    virtual void v24(); virtual void v28(); virtual void v2c(); virtual void v30();
    virtual void v34(); virtual void v38(); virtual void v3c(); virtual void v40();
    virtual void v44(); virtual void v48(); virtual void v4c(); virtual void v50();
    virtual void v54(); virtual void v58(); virtual void v5c(); virtual void v60();
    virtual void v64(); virtual void v68(); virtual void v6c(); virtual void v70();
    virtual void v74(); virtual void v78(); virtual void v7c(); virtual void v80();
    virtual void v84(); virtual void v88();
    virtual int GetCapacity();                              // +0x8c
};
void AddPlantItem(cSpaceInventory* inv, const ResourceKeyZ& key, int& capacity, int count);   // 0x0104e620
void AddAnimalItem(cSpaceInventory* inv, const ResourceKeyZ& key, int& capacity, int count);  // 0x0104e570

struct cAvatar {
    void Abduct();                                          // 0x00ffb030
    void Release();                                         // 0x00ffb180
};
struct cSpaceGame {
    cSpaceInventory* GetPlayerInventory();                  // 0x00a1ad60
    cAvatar* GetAvatar();                                   // 0x00b1fdb0
    void OnPlanetUplifted(cPlanet* planet);                 // 0x0100aec0
};
cSpaceGame* SpaceGame();                    // 0x01002bd0

struct cAppModeSpace {
    void SetMode(int mode);                                 // 0x00fde3e0
    void TransitionFromPlanetToSolar(cStarRecordView* star, int flag);   // 0x00fdd390
};
cAppModeSpace* AppModeSpace();              // 0x00fd9c60

struct cMission {
    cPlanet* GetTargetPlanet();                             // 0x00970b30
};
struct cMissionManager {
    cMission* GetMissionByID(uint32_t id);                  // 0x00fee480
};
cMissionManager* MissionManager();          // 0x00feb9f0

struct cAchievements {
    void AutoTest(uint32_t id, int flag);                   // 0x00676e90
};
cAchievements* AchievementsController();    // 0x00675250

// ---------------------------------------------------------------------------------------
struct ToolMessage {
    uint32_t mID;                                           // +0x00
    uint32_t mField4;
    uint32_t mValue;                                        // +0x08
    uint32_t pad[7];
    Transform* mpTransform;                                 // +0x28
};

struct ISimulatorStrategy { virtual void s0(); };
struct DefaultRefCounted { virtual void r0(); int mnRefCount; };
struct cStrategy : ISimulatorStrategy, DefaultRefCounted { uint32_t mStrategy[4]; };   // 0x1c
struct IUnmanagedMessageListener {
    virtual ~IUnmanagedMessageListener();
    virtual bool HandleMessage(uint32_t messageID, void* pMessage);
};

struct LocalizedString { uint32_t data[5]; };

class cToolManager : public cStrategy, public IUnmanagedMessageListener {
public:
    virtual ~cToolManager();
    virtual bool HandleMessage(uint32_t messageID, void* pMessage);

    ResourceKey field_20;                                   // +0x20
    Vector3 field_2C;                                       // +0x2c
    uint32_t mStrategies[8];                                // +0x38
    uint32_t field_58[7];                                   // +0x58
    LocalizedString mToolFailTexts[26];                     // +0x74
    uint32_t field_27C[5];                                  // +0x27c
    Vector3 field_290;                                      // +0x290
};

// 0x01051850
bool cToolManager::HandleMessage(uint32_t messageID, void* pMessage)
{
    ToolMessage* msg = (ToolMessage*)pMessage;
    switch (messageID)
    {
    case 0x05e667a2:
    {
        Transform* xf = msg->mpTransform;
        uint32_t effectID = msg->mID;
        Vector3 position = xf->GetOffset();
        cToolEffectHolder* holder = ToolEffectHost()->Add(position, 5.0f);
        Transform transform;
        transform.SetOffset(xf->GetOffset());
        transform.SetRotation(xf->mRotation);
        transform.SetScale(xf->mfScale);
        IVisualEffectPtr effect;
        if (EffectsManager2()->CreateVisualEffect(effectID, 0x40828100, effect.AsPPTypeParam())) {
            int handle = PlanetModel()->mpEffects->AttachEffect(transform, effect.get());
            if (holder)
                holder->mEffectHandle = handle;
        }
        return true;
    }

    case 0x04a32d09:
        if (PlanetModel() && PlanetModel()->mpEffects) {
            uint32_t id = msg->mID;
            Transform* xf = msg->mpTransform;
            PlanetModel()->mpEffects->PlaceAt(*xf, id, 0);
            return true;
        }
        return true;

    case 0x044f1189:
    {
        uint32_t value = msg->mValue;
        if (value == GameModeState()->GetModeID("SPG_CreatureTribeUplift")) {
            cOrnament* ornament = NounManager()->CreateNoun(0x018c88e4);
            if (ornament) {
                ornament->SetModelKey(0x0345bd5d, -1, 0x1a4f418e);
                ornament->mSpatial.SetPosition(field_290);
                ornament->mSpatial.SetOrientation(PlanetModel()->BuildSurfaceOrientation(field_290));
                cPlanetObjectData data(7, field_290);
                GetActivePlanet()->mpPlanetRecord->mPlanetObjects.push_back_planetobj(data);
            }
            field_290 = kInvalidPosition;
            return true;
        }
        return true;
    }

    case 0x0611691f:
        UFOSimulator()->GetPlayerUFO()->SetToolActive(false);
        return true;

    case 0x06116922:
    {
        cPlanetRecord* record = GetActivePlanetRecord();
        cPlanet* planet = GetActivePlanet();
        int level = TerraformingManager()->GetTerraformLevel(record);
        PlantProfileArray smallPlants(level, 0);
        PlantProfileArray mediumPlants(level, 0);
        PlantProfileArray largePlants(level, 0);
        cSpeciesManager* species = SpeciesManager();
        species->GetMatchingPlantProfiles(smallPlants, level, 0x37148141);
        species->GetMatchingPlantProfiles(mediumPlants, level, 0xb8669ec9);
        species->GetMatchingPlantProfiles(largePlants, level, 0xbcd73e89);

        PlantSwapData swap;
        NounManager()->GetCurrentTerrainSphere()->mObjects[record->GetID()].mList.Clear();

        int numPlants = (int)(record->mPlantSpecies.mpEnd - record->mPlantSpecies.mpBegin);
        int iSmall = 0, iMedium = 0, iLarge = 0;
        {
            for (int i = 0; i < numPlants; i++) {
                cPlantProfile* profile = species->GetPlantProfile(record->mPlantSpecies.mpBegin[i]);
                swap.mOldPlants.push_back(profile->mKey);
                switch (profile->mPlantType) {
                case 0xb8669ec9:
                    swap.mNewPlants.push_back(mediumPlants.mpBegin[iMedium++]->mKey);
                    break;
                case 0xbcd73e89:
                    swap.mNewPlants.push_back(largePlants.mpBegin[iLarge++]->mKey);
                    break;
                case 0x37148141:
                    swap.mNewPlants.push_back(smallPlants.mpBegin[iSmall++]->mKey);
                    break;
                }
                record->mPlantSpecies.mpBegin[i] = swap.mNewPlants.back();
                planet->ReplaceSpecies(swap.mNewPlants.back(), 1, 0);
            }
        }

        int numAnimals = (int)(record->mAnimalSpecies.mpEnd - record->mAnimalSpecies.mpBegin);
        {
            for (int i = 0; i < numAnimals; i++) {
                cPlantProfile* profile = species->GetProfile(record->mAnimalSpecies.mpBegin[i]);
                swap.mOldAnimals.push_back(profile->mKey);
                cPlantProfile* replacement = SpeciesPool()->Pick(GetReplacementSpecies(profile));
                swap.mNewAnimals.push_back(replacement->mKey);
                record->mAnimalSpecies.mpBegin[i] = swap.mNewAnimals.back();
                planet->ReplaceSpecies(swap.mNewAnimals.back(), 1, 0);
            }
        }

        planet->GetPlanetSim()->ApplySwap(swap);
        return true;
    }

    case 0x06117665:
    {
        if (GameModeState()->IsInEditor()) {
            MessageManager()->PostMSG(0x06117665, 0, 0, 0);
            return true;
        }
        AppModeSpace()->SetMode(0);
        AppModeSpace()->TransitionFromPlanetToSolar(GetPlayerHomePlanet()->GetStarView(), 1);
        IVisualEffectPtr effect;
        if (EffectsManager()->CreateVisualEffect(0x719a262a, 0, effect.AsPPTypeParam())) {
            cUFO* ufo = UFOSimulator()->GetPlayerUFO();
            ufo->PopToDestination();
            EffectTransform transform;
            transform.SetOffset(ufo->mSpatial.GetPosition());
            transform.SetRotation(Matrix3FromQuaternion(ufo->mSpatial.GetOrientation()));
            effect->SetTransform(transform);
            effect->Start(0);
        }
        return true;
    }

    case 0x0612d770:
    {
        cPlanetRecord* record = GetActivePlanetRecord();
        cSpaceInventory* inventory = SpaceGame()->GetPlayerInventory();
        int capacity = inventory->GetCapacity();
        cTerraformingManager* terraform = TerraformingManager();
        int level = terraform->GetTerraformLevel(record);
        for (int i = 1; i <= level; i++) {
            ResourceKeyZ key;
            key = terraform->GetPlantKey(i, 0x3a8be428, record);
            AddPlantItem(inventory, key, capacity, 2);
            key = terraform->GetPlantKey(i, 0x029c388a, record);
            AddPlantItem(inventory, key, capacity, 2);
            key = terraform->GetPlantKey(i, 0x6d60a1cc, record);
            AddPlantItem(inventory, key, capacity, 2);
            key = terraform->GetAnimalKey(i, 0, record);
            AddAnimalItem(inventory, key, capacity, 2);
            key = terraform->GetAnimalKey(i, 1, record);
            AddAnimalItem(inventory, key, capacity, 2);
            key = terraform->GetCreatureKey(i, record);
            AddAnimalItem(inventory, key, capacity, 2);
        }
        return true;
    }

    case 0x06255124:
    {
        Transform* xf = msg->mpTransform;
        cUFO* ufo = UFOSimulator()->GetPlayerUFO();
        uint32_t star = ufo->mDestinationStar;
        Vector3 destination = xf->GetOffset();
        ufo->SetDestination(destination);
        ufo->PopToDestination();
        ufo->SetDestinationStar(star);
        ufo->SetToolActive(true);
        UFOSimulator()->mb18 = false;
        UFOSimulator()->PopState();
        UFOSimulator()->mb20 = false;
        return true;
    }

    case 0x0643d5cb:
    {
        Transform* xf = msg->mpTransform;
        Vector3 position = xf->GetOffset();
        Quaternion orientation = Quaternion(QuaternionFromMatrix33(xf->mRotation, 0.0f));
        cSimulationEvent evt(position, orientation);
        GameModeState()->Trigger(0x5dce504a, &evt, 0);
        TriggerAdventureEvent("SPG_ZooCreated", 0x05482570, 0);
        return true;
    }

    case 0x0643d5cc:
    {
        Transform* xf = msg->mpTransform;
        Vector3 position = xf->GetOffset();
        Quaternion orientation = Quaternion(QuaternionFromMatrix33(xf->mRotation, 0.0f));
        cSimulationEvent evt(position, orientation);
        GameModeState()->Trigger(0x14a7d231, &evt, 0);
        field_290 = position;
        GameModeState()->Announce("SPG_CreatureTribeUplift", 1, 0, 0, 0, 0);
        cPlanet* planet = GetActivePlanet();
        cPlanetRecord* record = planet->mpPlanetRecord;
        SpaceGame()->OnPlanetUplifted(planet);
        if (planet->GetTechLevel() == 2)
            AchievementsController()->AutoTest(0x313be103, 1);
        if (planet->GetTechLevel() == 1) {
            cCreatureAnimal* closest = 0;
            float closestDist = 3.402823466e+38F;
            const CreatureVector& creatures = NounManager()->GetCreatures();
            for (cCreatureAnimal** it = creatures.mpBegin; it != creatures.mpEnd; ++it) {
                cCreatureAnimal* creature = *it;
                if (creature && creature->mbAlive && !creature->mbIsPlayer && !creature->IsInTribe()) {
                    const Vector3& pos = creature->mSpatial.GetPosition();
                    float dy = field_290.y - pos.y;
                    float dx = field_290.x - pos.x;
                    float dz = field_290.z - pos.z;
                    float dist = dz * dz + dy * dy + dx * dx;
                    if (closestDist > dist) {
                        closest = creature;
                        closestDist = dist;
                    }
                }
            }
            record->GetStarView()->SetSpeciesKey(
                closest ? closest->GetSpeciesKey() : record->mAnimalSpecies.mpBegin[0]);
        }
        return true;
    }

    case 0x0653a95b:
    {
        cMission* mission = MissionManager()->GetMissionByID(0x398aca5e);
        if (!mission)
            return true;
        if (mission->GetTargetPlanet() != GetActivePlanet())
            return true;
        Transform* xf = msg->mpTransform;
        Vector3 position = xf->GetOffset();
        Quaternion orientation = Quaternion(QuaternionFromMatrix33(xf->mRotation, 0.0f));
        cSimulationEvent evt(position, orientation);
        GameModeState()->Trigger(0x5dce504a, &evt, 0);
        TriggerAdventureEvent("SPG_ColonizeMissionComplete", 0x09f3a466, 1);
        return true;
    }

    case 0x06565534:
        if (field_2C != kInvalidPosition) {
            PositionTracker()->Update(field_20, field_2C);
            field_2C = kInvalidPosition;
        }
        return true;

    case 0x066605a6:
    {
        cAvatar* avatar = SpaceGame()->GetAvatar();
        if (avatar) {
            avatar->Release();
            UFOSimulator()->mb18 = false;
            UFOSimulator()->PopState();
            UFOSimulator()->ClearPending();
        }
        return true;
    }

    case 0x0668af00:
    {
        cAvatar* avatar = SpaceGame()->GetAvatar();
        if (avatar)
            avatar->Abduct();
        return true;
    }
    }
    return false;
}
