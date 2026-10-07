// Slice s00fdeac0: SP::cAppModeSpace::TransitionFromSolarToPlanet (0x00fdeac0).
// Flags: /O2 /MD /Gy /EHsc /TP (default).
//
// Runs when the player drops from the solar system onto a planet: reloads the plant models of the
// active planet record, swaps the bake tag, queues the bakes the planet needs (city/UFO models of
// every planet item, kept in mNeedsBakingForTransition), records the render-layer states, sets
// the planet model, posts the transition message and the "visited planet type" feedback event.
//
// Member names come from the dev PDB (cAppModeSpace, offsets shifted by +0x5c in retail);
// IBakeManager slots and BakeParameters from Spore-ModAPI Editors/BakeManager.h.
// Callees that only have FUN_ names are named after their use here (descriptive, not PDB).
#include "types.h"

typedef unsigned int size_t_;

void* operator new[](size_t_ n, const char* pName, int flags, unsigned debugFlags, const char* file, int line);  // 0x00f473a0
void operator delete[](void* p);                                                                               // 0x00f47380
inline void* operator new(size_t_, void* p) { return p; }

#define EASTL_ALLOCATOR_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

struct ResourceKey {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
    bool operator==(const ResourceKey& b) const
    {
        return instanceID == b.instanceID && typeID == b.typeID && groupID == b.groupID;
    }
    bool operator!=(const ResourceKey& b) const { return !(*this == b); }
};

namespace eastl {

struct allocator {
    void* allocate(size_t_ n) { return operator new[](n, "Simulator", 0, 0, EASTL_ALLOCATOR_FILE, 0xd1); }
    void deallocate(void* p) { operator delete[](p); }
};

struct ListNodeBase {
    ListNodeBase* mpNext;
    ListNodeBase* mpPrev;
    void insert(ListNodeBase* pNext)
    {
        mpNext = pNext;
        mpPrev = pNext->mpPrev;
        pNext->mpPrev->mpNext = this;
        pNext->mpPrev = this;
    }
};

template <typename T>
struct ListNode : public ListNodeBase {
    T mValue;
};

template <typename T>
struct ListIterator {
    ListNode<T>* mpNode;
    ListIterator(ListNode<T>* p) : mpNode(p) {}
    T& operator*() const { return mpNode->mValue; }
    ListIterator& operator++() { mpNode = (ListNode<T>*)mpNode->mpNext; return *this; }
    bool operator==(const ListIterator& b) const { return mpNode == b.mpNode; }
    bool operator!=(const ListIterator& b) const { return mpNode != b.mpNode; }
};

template <typename T>
class list {
public:
    typedef ListNode<T> node_type;
    typedef ListIterator<T> iterator;
    ListNodeBase mNode;
    allocator mAllocator;

    iterator begin() { return iterator((node_type*)mNode.mpNext); }
    iterator end() { return iterator((node_type*)&mNode); }

    void push_back(const T& value)
    {
        node_type* const pNode = DoCreateNode(value);
        pNode->insert(&mNode);
    }
    void clear()
    {
        DoClear();
        mNode.mpNext = &mNode;
        mNode.mpPrev = &mNode;
    }

    node_type* DoCreateNode(const T& value)
    {
        node_type* const pNode = (node_type*)mAllocator.allocate(sizeof(node_type));
        ::new(&pNode->mValue) T(value);
        return pNode;
    }
    void DoClear()
    {
        node_type* p = (node_type*)mNode.mpNext;
        while (p != (node_type*)&mNode) {
            node_type* const pTemp = p;
            p = (node_type*)p->mpNext;
            mAllocator.deallocate(pTemp);
        }
    }
};

template <typename InputIterator, typename T>
inline InputIterator find(InputIterator first, InputIterator last, const T& value)
{
    while ((first != last) && !(*first == value))
        ++first;
    return first;
}

// rbtree node layout used by the key maps below.
struct rbtree_node_base {
    rbtree_node_base* mpNodeRight;
    rbtree_node_base* mpNodeLeft;
    rbtree_node_base* mpNodeParent;
    char mColor;
};

} // namespace eastl

// A map keyed by uint32 (size 0x18: compare, anchor at +4, size at +0x14). The value type is not
// recovered; the bake code only builds and forwards it.
struct cKeyMap {
    uint32_t mCompare;
    eastl::rbtree_node_base mAnchor;            // +0x04
    uint32_t mnSize;                            // +0x14
    cKeyMap();                                  // 0x00bf2c60
    ~cKeyMap() { DoNukeSubtree(mAnchor.mpNodeParent); }
    void DoNukeSubtree(eastl::rbtree_node_base* pNode)   // out of line at 0x009a9600
    {
        while (pNode) {
            DoNukeSubtree(pNode->mpNodeRight);
            eastl::rbtree_node_base* const pNodeLeft = pNode->mpNodeLeft;
            operator delete[](pNode);
            pNode = pNodeLeft;
        }
    }
    uint32_t Find(uint32_t key);                // 0x00bf9700
    void Insert(uint32_t key, uint32_t value);  // 0x00bf4a60
};

// ---- Gonzago models ----
struct cMWModel;
struct IModelWorldOwner {
    virtual void v000(); virtual void v004(); virtual void v008(); virtual void v00c();
    virtual void v010(); virtual void v014(); virtual void v018(); virtual void v01c();
    virtual void v020(); virtual void v024(); virtual void v028(); virtual void v02c();
    virtual void v030(); virtual void v034(); virtual void v038(); virtual void v03c();
    virtual void v040(); virtual void v044(); virtual void v048(); virtual void v04c();
    virtual void v050(); virtual void v054(); virtual void v058(); virtual void v05c();
    virtual void v060(); virtual void v064(); virtual void v068(); virtual void v06c();
    virtual void v070(); virtual void v074(); virtual void v078(); virtual void v07c();
    virtual void v080(); virtual void v084(); virtual void v088(); virtual void v08c();
    virtual void v090(); virtual void v094(); virtual void v098(); virtual void v09c();
    virtual void v0a0(); virtual void v0a4(); virtual void v0a8(); virtual void v0ac();
    virtual void v0b0(); virtual void v0b4(); virtual void v0b8(); virtual void v0bc();
    virtual void v0c0(); virtual void v0c4(); virtual void v0c8(); virtual void v0cc();
    virtual void v0d0(); virtual void v0d4(); virtual void v0d8(); virtual void v0dc();
    virtual void v0e0(); virtual void v0e4(); virtual void v0e8(); virtual void v0ec();
    virtual void v0f0(); virtual void v0f4(); virtual void v0f8(); virtual void v0fc();
    virtual void v100(); virtual void v104(); virtual void v108(); virtual void v10c();
    virtual void v110(); virtual void v114(); virtual void v118(); virtual void v11c();
    virtual void v120(); virtual void v124(); virtual void v128(); virtual void v12c();
    virtual void v130(); virtual void v134(); virtual void v138(); virtual void v13c();
    virtual void v140(); virtual void v144(); virtual void v148(); virtual void v14c();
    virtual void v150(); virtual void v154(); virtual void v158(); virtual void v15c();
    virtual void v160(); virtual void v164(); virtual void v168();
    virtual void SetModelVisible(cMWModel* model, bool visible);   // +0x16c
    virtual void DestroyModel(cMWModel* model, bool owned);        // +0x170
};

struct cMWModel {
    IModelWorldOwner* mpWorld;                  // +0x00
    uint32_t mFlagBits : 31;                    // +0x04
    uint32_t mbOwned : 1;
    uint32_t pad08[14];
    int mnRefCount;                             // +0x40
    void AddRef() { mnRefCount++; }
    void Release()
    {
        if (mnRefCount > 1)
            --mnRefCount;
        else
            mpWorld->DestroyModel(this, mbOwned);
    }
};

template <class T>
struct AutoRefCount {
    T* mpObject;
    AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};

typedef AutoRefCount<cMWModel> ModelPtr;

struct copy_impl_ModelPtr {
    static ModelPtr* do_copy(ModelPtr* first, ModelPtr* last, ModelPtr* result);   // 0x005f4e10
};

struct ModelVector {
    ModelPtr* mpBegin;
    ModelPtr* mpEnd;
    ModelPtr* mpCapacity;
    uint32_t mAllocator;

    void DoDestroyValues(ModelPtr* first, ModelPtr* last);       // 0x005f3680
    void DoInsertValue(ModelPtr* position, const ModelPtr& value);   // 0x00423c40

    ModelPtr* erase(ModelPtr* first, ModelPtr* last)
    {
        ModelPtr* const position = copy_impl_ModelPtr::do_copy(last, mpEnd, first);
        DoDestroyValues(position, mpEnd);
        mpEnd -= (last - first);
        return first;
    }
    void clear() { erase(mpBegin, mpEnd); }
    void push_back(const ModelPtr& value)
    {
        if (mpEnd < mpCapacity)
            ::new(mpEnd++) ModelPtr(value);
        else
            DoInsertValue(mpEnd, value);
    }
};

struct IModelWorld {
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual cMWModel* LoadModel(uint32_t instanceID, uint32_t groupID, int flags);   // +0x0c
};
IModelWorld* GonzagoModelWorld();               // 0x00b3d520

struct cPlantSpecies {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14();
    virtual const ResourceKey* GetModelKey();   // +0x18
};
struct cPlantSpeciesManager {
    cPlantSpecies* GetSpeciesFromID(const ResourceKey& id);   // 0x00b90410
};
cPlantSpeciesManager* PlantSpeciesManager();    // 0x00b3d420

// ---- bake manager (Spore-ModAPI Editors::IBakeManager) ----
struct BakeParameters {
    uint32_t mTag;
    int16_t mFlag;
    int16_t mPriority;
    BakeParameters(int16_t flag, int16_t priority, uint32_t tag)
    {
        mFlag = flag;
        mPriority = priority;
        mTag = tag;
    }
};
struct IBakeManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18();
    virtual bool IsBaked(const ResourceKey& nameKey, bool param);          // +0x1c
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual bool Cancel(uint32_t tag);                                      // +0x40
    virtual void v44(); virtual void v48();
    virtual bool BakeModel(const ResourceKey& nameKey, const BakeParameters& params);   // +0x4c
};
IBakeManager* BakeManager();                    // 0x00401010

// ---- universe / planet ----
struct cPlanetRecord {
    uint32_t pad00[0xbc / 4];
    ResourceKey* mPlantsBegin;                  // +0xbc  vector<ResourceKey>
    ResourceKey* mPlantsEnd;                    // +0xc0
    uint32_t size() const { return (uint32_t)(mPlantsEnd - mPlantsBegin); }
};

struct cBioProtector { const ResourceKey* GetKey(); };   // 0x00bb9b80
struct cStarRecordRef {
    uint32_t GetCommContext();                  // 0x00ce6950
    cBioProtector* GetBioProtector();           // 0x00b8de30
};

struct cKeyMapSource;
struct cPlanetItem {
    ResourceKey* mKeysBegin;                    // +0x00 vector<ResourceKey>
    ResourceKey* mKeysEnd;                      // +0x04
    int GetOwnerID();                           // 0x00ff0420
    void ApplyKeyMap(const cKeyMap& map);       // 0x00ff3190
};
struct PlanetItemVector {
    cPlanetItem** mpBegin;
    cPlanetItem** mpEnd;
    bool empty() const { return mpBegin == mpEnd; }
    int size() const { return (int)(mpEnd - mpBegin); }
};

struct cPlanet {
    uint32_t pad00[0x13c / 4];
    cStarRecordRef* mpStarRecord;               // +0x13c
    int GetPlanetType();                        // 0x00c70e00
    PlanetItemVector& GetItems();               // 0x00c71000
    cPlanetItem* GetItem(int index);            // 0x00c71030
    const ResourceKey* GetPlanetKey();          // 0x00c713e0
    void SetPlanetKey(const ResourceKey* key);  // 0x00c713c0
    bool IsHomePlanet();                        // 0x00c73250
};

namespace cSPLivingUniverse {
cPlanet* GetActivePlanet();                     // 0x01021260
cPlanetRecord* GetActivePlanetRecord();         // 0x010212a0
}
void UniverseUpdateActive();                    // 0x01021230

struct cMission {
    cPlanetRecord* GetTargetRecord(int which);  // 0x00bbaa60
    int GetState();                             // 0x00bb9ae0
    uint32_t GetEmpireID();                     // 0x00b1fdb0
};
cMission* ActiveMission();                      // 0x01021240

struct cEmpire {
    cKeyMap GetKeyMap();                        // 0x00c352f0
    const ResourceKey* GetUFOKey();             // 0x00c326b0
};
struct cStarManager {
    cMission* GetCurrentMission();              // 0x00ba70a0
    cEmpire* GetEmpireByID(uint32_t id);        // 0x00ba9370
};
cStarManager* StarManager();                    // 0x00b3d2a0

struct cGameNounManager { int GetPlayerEmpireID(); };   // 0x00b1f9d0
cGameNounManager* NounManager();                // 0x00b3d300

struct AchievementsCtl { void AutoTest(uint32_t id, int value); };   // 0x00676e90
AchievementsCtl* AchievementsController();      // 0x00675250

struct cSPSimulatorSpaceGame { void FillKeyMap(cKeyMap& map); };   // 0x0102f5a0

struct cSPUISpace { void ShowBakeTimeSplash(); };   // 0x01065ab0
struct cSpaceUI {
    uint32_t pad00[5];
    cSPUISpace* mpUISpace;                      // +0x14
    uint32_t pad18[14];
    uint32_t mFlags;                            // +0x50
};

struct cPropertyList {
    virtual void v00();
    virtual void Release();                     // +0x04
    bool GetBool(uint32_t id);                  // 0x006a25a0
};
extern cPropertyList* sAppProperties;           // 0x015fd918
bool GetPropertyAsKey(cPropertyList* list, uint32_t id, ResourceKey* dst);   // 0x006a1250

struct PropertyListPtr {
    cPropertyList* mpObject;
    PropertyListPtr() : mpObject(0) {}
    ~PropertyListPtr() { if (mpObject) mpObject->Release(); }
    // COM-style out-parameter access: releases the current object first.
    cPropertyList** operator&()
    {
        if (mpObject) {
            cPropertyList* const p = mpObject;
            mpObject = 0;
            p->Release();
        }
        return &mpObject;
    }
    operator cPropertyList*() const { return mpObject; }
};
struct IPropertyManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, cPropertyList** dst);   // +0x2c
};
IPropertyManager* PropertyManager();            // 0x0067de30

struct cPlanetModel {
    uint32_t pad00[9];
    void* mpISphere;                            // +0x24
    void Generate(const ResourceKey* key, int flags);   // 0x00b8d750
    const ResourceKey* GetPlanetKey();          // 0x00b7e380
};
cPlanetModel* PlanetModel();                    // 0x00b3d350

struct IMessageServer {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void PostMSG(uint32_t id, void* data, void* sender);   // +0x14
};
IMessageServer* MessageServer();                // 0x0067dcc0

struct cPlanetVisits {
    int GetVisitCount(const ResourceKey* key);  // 0x0103ac40
    void SetVisitCount(const ResourceKey* key, int count);   // 0x0103fba0
};
cPlanetVisits* PlanetVisits();                  // 0x00b3d3d0

struct cSPUIEventLog {
    void PostFeedbackEvent(uint32_t a, uint32_t b, int c, int d, int e, int f);   // 0x00dd8640
};
cSPUIEventLog* EventLog();                      // 0x00b3d3e0

struct cGameTimeManager { void IncPauseGate(uint32_t id); };   // 0x00b32220
cGameTimeManager* GameTimeManager();            // 0x00b3d380

struct cSPUILayoutCollection { void Show(); };  // 0x00801360
cSPUILayoutCollection* LayoutCollection();      // 0x0067cab0

struct cGameInputManager { uint32_t pad[0x110 / 4]; int mInputLock; };   // +0x110
cGameInputManager* GameInputManager();          // 0x00b3d250

struct cTribeTool { void Refresh(uint32_t a, int b); };   // 0x00fe5430
struct cSpaceGameData { cTribeTool* GetTool(); };   // 0x00bfc5f0
cSpaceGameData* SpaceGameGet();                 // 0x01002bd0

struct cGonzagoTransition { void Begin(); };    // 0x00b7dec0
cGonzagoTransition* GonzagoTransition();        // 0x00b3d360

struct IRenderer {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual bool IsLayerEnabled(int layer, bool flag);   // +0x60
};
IRenderer* Renderer();                          // 0x0067dd50

extern const ResourceKey kDefaultKey;           // 0x016d9950

namespace SP {

struct cAppModeSpace {
    uint32_t pad000[0x144 / 4];
    ModelVector mPlantModels;                   // +0x144
    uint32_t pad154[2];
    cSpaceUI* mpSpaceUI;                        // +0x15c
    cSPSimulatorSpaceGame* mSimulatorSpaceGame; // +0x160
    uint32_t mElapsedBakeTimeForTransitionMS;   // +0x164
    bool mBackgroundMapGenerationEnded;         // +0x168
    bool mBakingForPlanetEntryEnded;            // +0x169
    bool mDisabledRenderLayersForBaking;        // +0x16a
    uint32_t mLastBakedTag;                     // +0x16c
    eastl::list<ResourceKey> mNeedsBakingForTransition;   // +0x170
    eastl::list<bool> mOldRenderLayerStates;    // +0x17c

    void TransitionFromSolarToPlanet();
};

// @ 0x00fdeac0
void cAppModeSpace::TransitionFromSolarToPlanet()
{
    cPlanet* planet = cSPLivingUniverse::GetActivePlanet();
    cPlanetRecord* record = cSPLivingUniverse::GetActivePlanetRecord();
    GonzagoTransition()->Begin();
    mDisabledRenderLayersForBaking = true;
    mBakingForPlanetEntryEnded = false;
    mElapsedBakeTimeForTransitionMS = 0;

    mPlantModels.clear();
    for (uint32_t i = 0; i < record->size(); i++) {
        cPlantSpecies* species = PlantSpeciesManager()->GetSpeciesFromID(record->mPlantsBegin[i]);
        IModelWorld* world = GonzagoModelWorld();
        ModelPtr model = world->LoadModel(species->GetModelKey()->instanceID,
                                          (species->GetModelKey()->groupID & 0xffff62ff) | 0x6200, 0);
        if (model) {
            mPlantModels.push_back(model);
            model->mpWorld->SetModelVisible(model, false);
        }
    }

    uint32_t tag = planet->mpStarRecord->GetCommContext();
    if (tag != mLastBakedTag)
        BakeManager()->Cancel(mLastBakedTag);
    BakeManager()->Cancel(0x609b763);
    if (planet->GetPlanetType() > 1) {
        const ResourceKey* key = planet->mpStarRecord->GetBioProtector()->GetKey();
        if (!BakeManager()->IsBaked(*key, false)) {
            BakeParameters params(0, 4, tag);
            BakeManager()->BakeModel(*key, params);
        }
    }
    mLastBakedTag = tag;

    if (ActiveMission() == StarManager()->GetCurrentMission()) {
        if (ActiveMission()->GetTargetRecord(0) == cSPLivingUniverse::GetActivePlanetRecord())
            AchievementsController()->AutoTest(0x7d4eb7d3, 1);
    }

    {
    cKeyMap keyMap;
    cPlanet* activePlanet = cSPLivingUniverse::GetActivePlanet();
    if (activePlanet && !activePlanet->GetItems().empty()) {
        int count = activePlanet->GetItems().size();
        for (int i = 0; i < count; i++) {
            cPlanetItem* item = activePlanet->GetItem(i);
            int ownerID = item->GetOwnerID();
            if (ownerID < 0 && ownerID != NounManager()->GetPlayerEmpireID())
                item->ApplyKeyMap(StarManager()->GetEmpireByID(ownerID)->GetKeyMap());

            if (item->mKeysBegin[0].instanceID == 0 || item->mKeysBegin[0].instanceID == 0xffffffff) {
                mSimulatorSpaceGame->FillKeyMap(keyMap);
                if (activePlanet->GetPlanetType() == 4) {
                    uint32_t v = keyMap.Find(0x2090a11b);
                    keyMap.Insert(0x441cd3e6, v);
                    keyMap.Insert(0x449c040f, v);
                    keyMap.Insert(0x1a4e0708, v);
                    v = keyMap.Find(0xbc1041e6);
                    keyMap.Insert(0x7d433fad, v);
                    keyMap.Insert(0x9ad7d4aa, v);
                    keyMap.Insert(0xf670aa43, v);
                    v = keyMap.Find(0xc15695da);
                    keyMap.Insert(0x8f963dcb, v);
                    keyMap.Insert(0x1f2a25b6, v);
                    keyMap.Insert(0x2a5147a9, v);
                }
                for (int j = 0; j < count; j++)
                    activePlanet->GetItem(j)->ApplyKeyMap(keyMap);
            }

            BakeParameters params(0, 1, tag);
            if (ActiveMission()->GetState() == 5) {
                const ResourceKey* ufoKey = StarManager()->GetEmpireByID(ActiveMission()->GetEmpireID())->GetUFOKey();
                if (!BakeManager()->IsBaked(*ufoKey, false)) {
                    mNeedsBakingForTransition.push_back(*ufoKey);
                    BakeManager()->BakeModel(*ufoKey, params);
                }
            }

            params.mPriority = 2;
            int numKeys = (int)(item->mKeysEnd - item->mKeysBegin);
            for (int k = 0; k < numKeys; k++) {
                const ResourceKey& key = item->mKeysBegin[k];
                if (key.instanceID != 0 && key.instanceID != 0xffffffff) {
                    if (!BakeManager()->IsBaked(key, false)) {
                        if (eastl::find(mNeedsBakingForTransition.begin(), mNeedsBakingForTransition.end(), key) ==
                            mNeedsBakingForTransition.end()) {
                            mNeedsBakingForTransition.push_back(key);
                            mDisabledRenderLayersForBaking = false;
                            BakeManager()->BakeModel(key, params);
                        }
                    }
                }
            }
        }
    }

    if (!sAppProperties->GetBool(0x7ae23adf)) {
        mNeedsBakingForTransition.clear();
        mDisabledRenderLayersForBaking = true;
    } else if (!mDisabledRenderLayersForBaking) {
        if (mpSpaceUI->mpUISpace)
            mpSpaceUI->mpUISpace->ShowBakeTimeSplash();
        for (int layer = 0; layer < 28; layer++)
            mOldRenderLayerStates.push_back(Renderer()->IsLayerEnabled(layer, true));
        mBakingForPlanetEntryEnded = true;
    }
    }

    cPlanet* targetPlanet = cSPLivingUniverse::GetActivePlanet();
    UniverseUpdateActive();
    cPlanetModel* planetModel = PlanetModel();
    if (planetModel->mpISphere == 0)
        planetModel->Generate(targetPlanet->GetPlanetKey(), 0);
    else
        targetPlanet->SetPlanetKey(planetModel->GetPlanetKey());
    MessageServer()->PostMSG(0x279a5da, 0, 0);
    mpSpaceUI->mFlags |= 2;

    cPlanetVisits* visits = PlanetVisits();
    ResourceKey visitKey = kDefaultKey;
    PropertyListPtr propList;
    ResourceKey planetType = {0, 0, 0};
    PropertyManager()->GetPropertyList(planet->GetPlanetKey()->instanceID, planet->GetPlanetKey()->groupID, &propList);
    if (propList)
        GetPropertyAsKey(propList, 0xb2cccb, &planetType);
    switch (planetType.instanceID) {
    case 0x0d019b5b: case 0x5c80e783: case 0xa1867950: case 0xaa61bc5b:
        visitKey.instanceID = 0xae15a0ca; break;
    case 0x1e5569aa: case 0x80f548aa:
        visitKey.instanceID = 0xdb0c25ed; break;
    case 0x34bf26cf: case 0x1c901fcf: case 0x2f88ce28: case 0x332eab13: case 0x4c0e0747:
        visitKey.instanceID = 0xae15a0cc; break;
    case 0x51f60469: case 0x60e56c7a: case 0xf1c64be5: case 0xff0cf57a:
        visitKey.instanceID = 0xae15a0cb; break;
    case 0x06be74d1: case 0xa4e5fdd1:
        visitKey.instanceID = 0xae15a0c7; break;
    case 0x329977f9: case 0x49668fda: case 0x98eeb4f9: case 0xafbbccda:
        visitKey.instanceID = 0xae15a0c8; break;
    case 0x3c5bdade: case 0x73f48a76: case 0xead9ff1a:
        visitKey.instanceID = 0xae15a0cd; break;
    case 0x655cf1e1: case 0xbdf0e303: case 0x7d8bf8e1: case 0xd61fea03:
        visitKey.instanceID = 0xae15a0cf; break;
    case 0x2f860299: case 0xcce62399:
        visitKey.instanceID = 0xae15a0c9; break;
    case 0x532534be: case 0xf08555be: case 0xfbec2af8:
        visitKey.instanceID = 0xae15a0c6; break;
    }
    if (visitKey != kDefaultKey) {
        if (!planet->IsHomePlanet())
            SpaceGameGet()->GetTool()->Refresh(0x18, 1);
        if (visits->GetVisitCount(&visitKey) != 1) {
            visits->SetVisitCount(&visitKey, 1);
            EventLog()->PostFeedbackEvent(0xd7775835, 0x131a9f54, 0, 0, 1, 0);
        }
    }

    GameTimeManager()->IncPauseGate(0x4bf38a7);
    LayoutCollection()->Show();
    GameInputManager()->mInputLock++;
}

} // namespace SP
