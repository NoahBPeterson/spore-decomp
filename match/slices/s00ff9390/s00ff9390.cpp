// Slice s00ff9390 -- FUN_00ff9800 (0x00ff9800, 2746 bytes), a cSPSimPlanetHighLOD member (this in ecx,
// `ret 4`) that runs when the high-LOD planet simulation starts on `planet` (fields at the retail
// cSPSimPlanetHighLOD offsets used by sibling slice s00ff7530 and ModAPI cSimPlanetHighLOD:
// mSimulationStepTime +0x20, field_1B0 (intrusive ptr) +0x1b0, field_1B4 +0x1b4, field_1B8 +0x1b8).
//
// What it does, in order:
//  - hands every id queued in the planet record's +0x148 vector to PlanetModel()->m24 (vslot 0x58) and
//    clears the vector;
//  - if the planet is not yet set up (0x00c73250 false) it refreshes the planet updater and the planet
//    (0x00c74650), and remembers that in `firstVisit`;
//  - notifies the player empire about a foreign owner, sets the 2 s simulation step, gets/activates
//    the low-LOD planet sim (returns early when there is none);
//  - names an unnamed owner after its species, runs the per-planet population setup, recomputes
//    +0x1b8, advances the owner's UFO spawn timer (record +0x124/+0x128/+0x12c, tuning properties
//    0x5c2cbc5 / 0x5c2cbd6, default 30 s) and spawns its UFOs;
//  - walks the record's 0x2c-byte tool/marker entries (+0x134) and places, re-adds, marks, creates or
//    expires each one;
//  - with 2% chance re-adds a random saved key (+0xd0) at a PlanetModel position;
//  - recomputes relationships with the planet's tribes/cities, refreshes a few singletons,
//    creates (and leaks) a cCommandTerraform, posts message 0x490d429, and makes sure the +0x1b0
//    helper object exists before updating it.
// Callee names are descriptive except where the PDB name map gives one (see comments).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (sibling s00ff7530).
#include "types.h"
#include <string.h>

#pragma warning(disable : 4035)

typedef unsigned int size_t_;

void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file, int line);
void operator delete[](void* p);                                   // 0x00f47380

// float -> int rounding down (the module's asm helper; cvtss2si + cmovb)
__forceinline int FloorToInt(float f)
{
    __asm {
        movss    xmm0, f
        cvtss2si eax, xmm0
        cvtsi2ss xmm1, eax
        mov      ecx, eax
        sub      ecx, 1
        ucomiss  xmm0, xmm1
        cmovb    eax, ecx
    }
}

struct Vector3 {
    float x, y, z;
    bool operator!=(const Vector3& b) const { return x != b.x || y != b.y || z != b.z; }
};
struct Quaternion { float x, y, z, w; };

struct ResourceKey {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
};
inline bool operator==(const ResourceKey& a, const ResourceKey& b)
{
    return a.instanceID == b.instanceID && a.typeID == b.typeID && a.groupID == b.groupID;
}

template <typename T> inline T* find(T* first, T* last, const T& value)
{
    while ((first != last) && !(*first == value))
        ++first;
    return first;
}

template <typename T>
struct PtrVector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    int size() const { return (int)(mpEnd - mpBegin); }
    T& operator[](int i) { return mpBegin[i]; }
    T* erase(T* first, T* last)
    {
        memcpy(first, last, (char*)mpEnd - (char*)last);
        mpEnd -= (last - first);
        return first;
    }
    T* erase(T* position)
    {
        if ((position + 1) < mpEnd) {
            T* d = position;
            for (T* s = position + 1; s != mpEnd; ++s, ++d)
                *d = *s;
        }
        --mpEnd;
        return position;
    }
    void clear() { erase(mpBegin, mpEnd); }
};

// eastl::string16 (begin/end/capacity + allocator), only what this function needs.
extern uint16_t gEmptyString[];                                    // 0x01667bac
struct string16 {
    uint16_t* mpBegin;
    uint16_t* mpEnd;
    uint16_t* mpCapacity;
    uint32_t mAllocator;
    string16() : mpBegin(gEmptyString), mpEnd(gEmptyString), mpCapacity(gEmptyString + 1) {}
    ~string16()
    {
        if ((mpCapacity - mpBegin) > 1 && mpBegin)
            operator delete[](mpBegin);
    }
};

// ---- App::Property ----
struct Property {
    uint32_t mData[4];
    uint8_t mFlags;                                                // +0x10
    uint8_t mPad11;
    uint16_t mType;                                                // +0x12
    float* GetValueFloat() { return (mFlags & 0x30) ? *(float**)this : (float*)this; }
};
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8
struct PropertyList {
    PV8 PV
    virtual bool GetProperty(uint32_t id, Property*& result);      // +0x24
};
struct PropertyListPtr {
    PropertyList* mpObject;
    PropertyList* get() const { return mpObject; }
};
inline bool GetFloat(const PropertyListPtr& listPtr, uint32_t id, float& value)
{
    PropertyList* list = listPtr.get();
    Property* prop;
    if (list && list->GetProperty(id, prop) && prop->mType == 0xd) {
        value = *prop->GetValueFloat();
        return true;
    }
    return false;
}
struct cSpaceCombatTuning {
    uint32_t mPad[2];
    PropertyListPtr mpPropList;                                    // +0x08
};
cSpaceCombatTuning* GetSpaceCombatTuning();                        // 0x01029940 SP::GetSpaceCombatTuning

// ---- singletons / helpers ----
struct cPlanetModelHelper {
    PV16 PV4 PV2
    virtual void Release(uint32_t id, int flag);                   // +0x58
};
struct cPlanetModel {
    uint32_t mPad[9];
    cPlanetModelHelper* mpHelper;                                  // +0x24
    cPlanetModelHelper* GetHelper() { return mpHelper; }
    void GetRandomPosition(Vector3* out);                          // 0x00b84730
    Quaternion BuildSurfaceOrientation(const Vector3& pos);        // 0x00b7f190
    void AddResourceNodes();                                       // 0x00b8bba0
};
cPlanetModel* PlanetModel();                                       // 0x00b3d350

struct cPlanetUpdater { void RefreshUpdater(int flags); };         // 0x00b2bf10
cPlanetUpdater* PlanetUpdater();                                   // 0x00b3d3b0

struct cBackgroundSim { bool IsBusy(); };                          // 0x00c8b560
cBackgroundSim* GetBackgroundSim();                                // 0x01021230

struct cGameTimeManager { uint64_t GetGameTime(); };               // 0x00b316c0
cGameTimeManager* GameTimeManager();                               // 0x00b3d380

struct cRelationshipManager {
    float ApplyRelationship(int politicalA, int politicalB, int flag);   // 0x00d00a10
};
cRelationshipManager* RelationshipManager();                       // 0x00b3d2c0

struct cMarkerManager {                                            // 0x00b3d480
    void RefreshMarkers(uint32_t id);                                   // 0x00ad2560
    void RefreshAll() { RefreshMarkers(0x1654c05); }
    void AddMarker(const void* key, const void* data);             // 0x00acf3e0
};
cMarkerManager* MarkerManager();                                   // 0x00b3d480

struct cGameNoun {
    PV16 PV2 PV
    virtual int GetPoliticalID();                                  // +0x4c
    void* GetCityTarget();                                         // 0x00c8e7e0
    void* GetTribe();                                              // 0x00bef8e0
};
inline void* CityOf(cGameNoun* p) { return p ? p->GetCityTarget() : 0; }
struct cRelationshipTarget { void UpdateTarget(int flag); };             // 0x01062e60
struct cGameDataVector {
    uint32_t mPad;
    PtrVector<cGameNoun*> mData;                                   // +0x04
};
typedef void (*GameDataFn)();
void GameData_cd7d10();                                            // 0x00cd7d10
void GameData_d3d420();                                            // 0x00d3d420
void GameData_acdff0();                                            // 0x00acdff0
void GameData_accbb0();                                            // 0x00accbb0
void GameData_b1e500();                                            // 0x00b1e500
void GameData_b21080();                                            // 0x00b21080
void GameData_b236c0();                                            // 0x00b236c0

struct ILocatable {
    PV8 PV4 PV2
    virtual void SetPosition(const void* pos);                     // +0x38
    virtual void SetOrientation(const Quaternion& q);              // +0x3c
};
struct cSpatialNoun {
    uint32_t mPad[0x70 / 4];
    ILocatable mLocatable;                                         // +0x70
    void SetModel(uint32_t instance, int group, uint32_t type);    // 0x00c6f770
};
struct cGameNounManager {
    int GetPlayerEmpireOrMinus1();                                 // 0x00b1f9d0
    cGameDataVector* GetGameDataVector(GameDataFn a, GameDataFn b, GameDataFn c, GameDataFn d, uint32_t type);  // 0x00b21340
    cSpatialNoun* CreateNoun(uint32_t type);                       // 0x00b20c60
};
cGameNounManager* NounManager();                                   // 0x00b3d300

struct cSimSingleton {
    uint32_t mData[0x58 / 4];
    cSimSingleton();                                               // 0x00dc7d70
    void ResetSim();                                             // 0x00dced90
    static cSimSingleton* sInstance;                               // 0x01699ab8
    static cSimSingleton* Get()
    {
        if (!sInstance)
            sInstance = new ("Simulator/SimSingleton", 0, 0, 0, 0) cSimSingleton();
        return sInstance;
    }
};
struct cSimTicker {
    PV16 PV4
    virtual void SetSingleton(cSimSingleton* s);                   // +0x50
};
cSimTicker* SimTicker();                                           // 0x00b3d330

struct cCommandBase {
    cCommandBase();                                                // 0x0083c800
    virtual void ParseLine(void* line);
    uint32_t mField4;
    uint32_t mField8;
};
struct cCommandTerraform : cCommandBase {
    uint32_t mFieldC;
    cCommandTerraform() {}
    virtual void ParseLine(void* line);
};
struct cCheatManager;
cCheatManager* CheatManager();                                     // 0x0067de20
struct IMessageManager {
    PV4 PV2
    virtual bool PostMSG(uint32_t id, void* data, void* p2, void* p3);   // +0x18
};
IMessageManager* MessageServer();                                  // 0x0067dcc0

struct cEffectRegistry { void RefreshEffects(); };                        // 0x01041bc0
cEffectRegistry* EffectRegistry();                                 // 0x010408b0

struct cPlanetHelper68 {                                           // 0x68 bytes, "Simulator"
    virtual void Dispose();
    virtual int AddRef();
    virtual int Release();
    uint32_t mData[0x64 / 4];
    cPlanetHelper68();                                             // 0x00ebc120
    void UpdateHelper();                                           // 0x00ebd220
};

struct RandomLCG {
    double RandomDoubleUniform();                                  // 0x009360d0
    uint32_t RandomUint32Uniform(uint32_t n);                      // 0x00a68fb0
};
extern RandomLCG gRandom;                                          // 0x01601760
extern const Vector3 kZeroVector;                                  // 0x016db418
extern uint32_t k_placeuberturret;                                 // 0x016db6f0

// ---- empire / species ----
struct rbtree_node_base { rbtree_node_base* mpNodeRight; rbtree_node_base* mpNodeLeft; rbtree_node_base* mpNodeParent; char mColor; };
struct rbtree_iterator {
    rbtree_node_base* mpNode;
    rbtree_iterator() {}
    rbtree_iterator(rbtree_node_base* p) : mpNode(p) {}
    rbtree_iterator(const rbtree_iterator& x) : mpNode(x.mpNode) {}
    bool operator==(const rbtree_iterator& x) const { return mpNode == x.mpNode; }
};
struct IDNameMap {
    uint32_t mCompare;
    rbtree_node_base mAnchor;                                      // +0x04
    rbtree_iterator find(const uint32_t& key);                     // 0x00e5c780
    rbtree_iterator end() { return rbtree_iterator(&mAnchor); }
};
struct cIdentity {
    uint32_t mPad[2];
    IDNameMap mIDNameMap;                                          // +0x08
    void SetName(const string16& name);                            // 0x00b6f380
};
struct cEmpire {
    uint32_t mPad[3];
    cIdentity mIdentity;                                           // +0x0c
    uint32_t mPad2[(0x84 - 0x0c - 0x8 - 0x14) / 4];
    uint32_t mHomeStar;                                            // +0x84
    uint32_t GetUFOKey();                                          // 0x00c326b0 SP::cEmpire::GetUFOKey
    void OnForeignPlanetVisited(cEmpire* owner);                   // 0x010829f0
};
cEmpire* GetPlayerEmpire();                                        // 0x01021300 SP::cSPLivingUniverse::GetPlayerEmpire
void CreateUFO(int kind, uint32_t* star, uint32_t key);            // 0x0102acb0 SP::CreateUFO

struct cSpeciesProfile {
    void GetUiName(string16& out);                                 // 0x004da330 SP::cSpeciesProfile::GetUiName
};

// ---- planet ----
struct cToolData {                                                 // entry + 4
    Vector3 mPos;                                                  // +0x00
    uint8_t mPad0c[2];
    uint8_t mKind;                                                 // +0x0e
    uint8_t mPad0f;
    float mScale;                                                  // +0x10
    uint32_t mTime;                                                // +0x14
    ResourceKey mKey;                                              // +0x18
    uint8_t mFlags;                                                // +0x24
    uint8_t mPad25[3];
};
struct cToolEntry {                                                // 0x2c bytes
    uint32_t mType;
    cToolData mData;
};
struct cPlanetRecordData {
    uint32_t mPad[0xd0 / 4];
    PtrVector<ResourceKey> mSavedKeys;                             // +0xd0
    uint32_t mPadDC[(0x124 - 0xdc) / 4];
    int mUFOCount;                                                 // +0x124
    float mUFOTime;                                                // +0x128
    float mInterceptTime;                                          // +0x12c
    uint32_t mPad130;
    PtrVector<cToolEntry> mToolEntries;                            // +0x134
    uint32_t mPad140[2];
    PtrVector<uint32_t> mPendingIDs;                               // +0x148
};
struct cPlanet {
    uint32_t mPad[0x130 / 4];
    int mPopulation;                                               // +0x130
    uint32_t mPad134[2];
    cPlanetRecordData* mpRecord;                                   // +0x13c
    bool IsInitialized();                                          // 0x00c73250
    int GetPendingCount();                                         // 0x00c70fb0
    void Initialize();                                             // 0x00c74650
    cEmpire* GetOwner();                                           // 0x00c71e30
    void* GetSimPlanetLowLOD();                                    // 0x008414c0
    bool IsSimActive();                                            // 0x00c70c00
    void* PlanetSimActivate();                                     // 0x00c71e70 SP::cPlanet::PlanetSimActivate
    void SetDirty(int flag);                                       // 0x00c70bf0
    bool IsDirty();                                                // 0x00c70be0
    cSpeciesProfile* GetSpecies();                                 // 0x00c70860
    bool HasCivilization();                                        // 0x00c6ffb0
    void SetEmpty(int flag);                                       // 0x00c6ffc0
    int GetCityCount();                                            // 0x00c710c0
    void* GetCity(int i);                                          // 0x00c71030
    int GetTechLevel();                                            // 0x00c70e00
    PtrVector<void*>* GetTribes();                                 // 0x00c71010
    int GetUFOCount();                                             // 0x00c70ba0
};
void RefreshPlanet(cPlanet* planet);                               // 0x00ba1ce0
void SetupTribe(void* tribe, cSpeciesProfile* species);            // 0x00c932a0
int CountPlanetUFOs(cPlanetRecordData* rec);                       // 0x00ff5930
void CreateToolObject(uint32_t type, cToolData* data, float scale);   // 0x00ff8560
void CreateUberTurret(uint32_t type, cToolData* data);             // 0x0102b780
void SetZooMarker(cPlanetRecordData* rec, ResourceKey* key, cToolData* data, int flag);   // 0x01043fd0 SP::SetZooMarker

class cSPSimPlanetHighLOD {
public:
    uint32_t mPad00[0x20 / 4];
    uint32_t mSimulationStepTime;                                  // +0x20
    uint32_t mPad24[(0x1b0 - 0x24) / 4];
    cPlanetHelper68* mpHelper;                                     // +0x1b0
    bool mbInitialized;                                            // +0x1b4
    int mUFOCount;                                                 // +0x1b8

    void SetupCity(void* city, cSpeciesProfile* species);          // 0x00ff6a50
    static void SetupResourceNodes();                              // 0x00ff95a0
    void UpdateInterceptorUFO();                                   // 0x00ff8ad0
    void SpawnUFOs();                                              // 0x00ff9070
    void SpawnArtifact(cToolEntry* entry);                         // 0x00ff5d20 SP::cSPSimPlanetHighLOD::SpawnArtifact
    void UpdatePopulation();                                       // 0x00ff9390
    void ActivatePlanet(cPlanet* planet);
};

// @ 0x00ff9800
void cSPSimPlanetHighLOD::ActivatePlanet(cPlanet* planet)
{
    PtrVector<uint32_t>& pending = planet->mpRecord->mPendingIDs;
    for (int i = 0; i < pending.size(); i++)
        PlanetModel()->GetHelper()->Release(pending[i], 1);
    pending.clear();

    if (!planet->IsInitialized() && planet->GetPendingCount() > 0)
        PlanetUpdater()->RefreshUpdater(0);

    bool firstVisit = false;
    if (!planet->IsInitialized()) {
        firstVisit = true;
        mbInitialized = true;
        planet->Initialize();
    }

    cEmpire* owner = planet->GetOwner();
    if (owner && owner != GetPlayerEmpire())
        GetPlayerEmpire()->OnForeignPlanetVisited(owner);

    mSimulationStepTime = 2000;
    void* lowLOD = planet->GetSimPlanetLowLOD();
    if (!planet->IsSimActive())
        lowLOD = planet->PlanetSimActivate();
    if (!lowLOD)
        return;

    cBackgroundSim* bg = GetBackgroundSim();
    if (bg && bg->IsBusy())
        planet->SetDirty(0);
    if (planet->IsDirty()) {
        RefreshPlanet(planet);
        planet->SetDirty(0);
    }

    cGameNounManager* nouns = NounManager();
    nouns->GetPlayerEmpireOrMinus1();
    cSpeciesProfile* species = planet->GetSpecies();

    if (owner) {
        cIdentity& identity = owner->mIdentity;
        if (identity.mIDNameMap.find(0) == identity.mIDNameMap.end()) {
            string16 name;
            species->GetUiName(name);
            identity.SetName(name);
        }
    }

    if (planet->HasCivilization()) {
        for (int i = 0, cityCount = planet->GetCityCount(); i < cityCount; i++)
            SetupCity(planet->GetCity(i), species);
        if (planet->GetTechLevel() == 4)
            SetupResourceNodes();
        PtrVector<void*>* tribes = planet->GetTribes();
        int tribeCount = tribes->size();
        for (int i = 0; i < tribeCount; i++)
            SetupTribe((*tribes)[i], species);

        cPlanetRecordData* rec = planet->mpRecord;
        mUFOCount = CountPlanetUFOs(rec);
        if (owner && owner != GetPlayerEmpire()) {
            int missing = mUFOCount - planet->GetUFOCount();
            if (missing > 0) {
                float now = (float)GameTimeManager()->GetGameTime() * 0.001f;
                if (rec->mUFOTime == 0.0f) {
                    rec->mUFOTime = now;
                    rec->mUFOCount = mUFOCount;
                } else {
                    float interval = 30.0f;
                    GetFloat(GetSpaceCombatTuning()->mpPropList, 0x5c2cbc5, interval);
                    float elapsed = now - rec->mUFOTime;
                    if (elapsed > (float)missing * interval) {
                        rec->mUFOTime = now;
                        rec->mUFOCount = mUFOCount;
                    } else {
                        int n = FloorToInt(elapsed / interval);
                        rec->mUFOCount += n;
                        rec->mUFOTime = (float)n * interval + rec->mUFOTime;
                    }
                }
                if (rec->mInterceptTime > 0.0f) {
                    float delay = 30.0f;
                    GetFloat(GetSpaceCombatTuning()->mpPropList, 0x5c2cbd6, delay);
                    if (now - rec->mInterceptTime > delay) {
                        rec->mInterceptTime = -rec->mInterceptTime;
                        UpdateInterceptorUFO();
                    }
                }
            }
            uint32_t key = owner->GetUFOKey();
            for (int i = 0; i < planet->GetUFOCount(); i++) {
                uint32_t star = owner->mHomeStar;
                CreateUFO(6, &star, key);
            }
        }
        SpawnUFOs();
    } else {
        planet->SetEmpty(1);
    }

    MarkerManager()->RefreshAll();

    cPlanetRecordData* rec = planet->mpRecord;
    for (cToolEntry* it = rec->mToolEntries.mpBegin; it != rec->mToolEntries.mpEnd;) {
        cToolData* data = &it->mData;
        if (data->mFlags & 1) {
            if (it->mType == k_placeuberturret)
                CreateUberTurret(it->mType, data);
            else
                CreateToolObject(it->mType, data, data->mScale);
        } else if (data->mFlags & 4) {
            ResourceKey* last = rec->mSavedKeys.mpEnd;
            if (find(rec->mSavedKeys.mpBegin, last, data->mKey) != last)
                MarkerManager()->AddMarker(&data->mKey, data);
        } else if (data->mFlags & 0x40) {
            SetZooMarker(rec, &data->mKey, data, 0);
        } else if (data->mFlags & 0x80) {
            cSpatialNoun* noun = NounManager()->CreateNoun(0x18c88e4);
            if (noun) {
                noun->SetModel(0x345bd5d, -1, 0x1a4f418e);
                ILocatable* loc = &noun->mLocatable;
                loc->SetPosition(data);
                loc->SetOrientation(PlanetModel()->BuildSurfaceOrientation(data->mPos));
            }
        } else {
            uint32_t seconds = (uint32_t)(GameTimeManager()->GetGameTime() / 1000);
            if ((data->mFlags & 8) && data->mKind == 7 && data->mTime < seconds && seconds - data->mTime > 300) {
                it = rec->mToolEntries.erase(it);
                continue;
            }
            SpawnArtifact(it);
        }
        ++it;
    }

    if (gRandom.RandomDoubleUniform() < 0.02f && rec->mSavedKeys.mpBegin != rec->mSavedKeys.mpEnd) {
        uint32_t index = gRandom.RandomUint32Uniform(rec->mSavedKeys.size());
        Vector3 pos;
        PlanetModel()->GetRandomPosition(&pos);
        if (pos != kZeroVector)
            MarkerManager()->AddMarker(&rec->mSavedKeys[index], &pos);
    }

    cRelationshipManager* relations = RelationshipManager();
    PtrVector<cGameNoun*>& cities = nouns->GetGameDataVector(GameData_cd7d10, GameData_d3d420, GameData_acdff0,
                                                               GameData_b1e500, 0x18c43e8)->mData;
    PtrVector<cGameNoun*>& tribes = nouns->GetGameDataVector(GameData_cd7d10, GameData_d3d420, GameData_accbb0,
                                                               GameData_b1e500, 0x18c6d19)->mData;
    int tribeCount = tribes.size();
    for (int i = 0; i < tribeCount; i++) {
        cGameNoun* tribe = tribes[i];
        relations->ApplyRelationship(tribe->GetPoliticalID(), NounManager()->GetPlayerEmpireOrMinus1(), 0);
        cRelationshipTarget* target = (cRelationshipTarget*)CityOf(tribes[i]);
        if (target)
            target->UpdateTarget(0);
    }
    PtrVector<cGameNoun*>& others = nouns->GetGameDataVector(GameData_b21080, GameData_d3d420, GameData_b236c0,
                                                               GameData_b1e500, 0x18c816a)->mData;
    int otherCount = others.size();
    for (int i = 0; i < otherCount; i++) {
        cGameNoun* noun = others[i];
        if (noun->GetPoliticalID() != nouns->GetPlayerEmpireOrMinus1()) {
            relations->ApplyRelationship(noun->GetPoliticalID(), nouns->GetPlayerEmpireOrMinus1(), 0);
            cRelationshipTarget* target = (cRelationshipTarget*)noun->GetTribe();
            if (target)
                target->UpdateTarget(0);
        }
    }

    UpdatePopulation();
    if (firstVisit) {
        planet->mPopulation = 0;
        int cityCount = cities.size();
        for (int i = 0; i < cityCount; i++) {
            uint32_t* c = (uint32_t*)cities[i];
            PtrVector<void*>& a = *(PtrVector<void*>*)(c + 0x340 / 4);
            PtrVector<void*>& b = *(PtrVector<void*>*)(c + 0x354 / 4);
            planet->mPopulation += a.size() + b.size();
        }
    }

    cSimSingleton::Get()->ResetSim();
    SimTicker()->SetSingleton(cSimSingleton::Get());
    new ("App/cCommandTerraform", 0, 0, 0, 0) cCommandTerraform();
    CheatManager();
    MessageServer()->PostMSG(0x490d429, 0, 0, 0);
    if (planet->GetTechLevel() == 4)
        PlanetModel()->AddResourceNodes();

    if (!mpHelper) {
        EffectRegistry()->RefreshEffects();
        cPlanetHelper68* p = new ("Simulator", 0, 0, 0, 0) cPlanetHelper68();
        if (p != mpHelper) {
            cPlanetHelper68* old = mpHelper;
            if (p)
                p->AddRef();
            mpHelper = p;
            if (old)
                old->Release();
        }
    }
    mpHelper->UpdateHelper();
}
