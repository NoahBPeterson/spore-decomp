// Slice s00fe0570: cAppModeSpace init for the space game (0x00fe0570, 1773 bytes).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (same module as s00fe0f40).
//
// Registers the planet/terrain resource keys with the object-template DB, queues every model
// key of the player's home planet entities for baking, runs the start-up sequence selected by
// the "game start" app property (new game / continue / interstellar-drive tutorial), refreshes
// the active planet, and (when baking is not already done) pre-pushes 28 simulator input flags.
#include "types.h"
#include <intrin.h>
#include <new>

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4

struct Vector3 {
    float x, y, z;
};

struct ResourceKey {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
};
struct ZeroKey : public ResourceKey {
    ZeroKey() { instanceID = 0; typeID = 0; groupID = 0; }
};

void* operator new[](unsigned int n, const char* pName, int flags, unsigned int debugFlags, const char* pFile, int line);  // 0x00f473a0
void operator delete[](void* p);                                                                                           // 0x00f47380

namespace eastl {
struct ListNodeBase {
    ListNodeBase* mpNext;
    ListNodeBase* mpPrev;
};
template <typename T>
struct ListNode : public ListNodeBase {
    T mValue;
};
template <typename T>
struct list {
    typedef ListNode<T> node_type;
    ListNodeBase mNode;
    uint32_t mAllocator;

    void push_back(const T& value)
    {
        node_type* pNode = (node_type*)(new ("Simulator", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 209) char[sizeof(node_type)]);
        ::new ((void*)&pNode->mValue) T(value);
        pNode->mpNext = &mNode;
        pNode->mpPrev = mNode.mpPrev;
        mNode.mpPrev->mpNext = pNode;
        mNode.mpPrev = pNode;
    }
};
}  // namespace eastl

// ------------------------------------------------------------------ map<uint32, ResourceKey>
struct KeyNode {
    KeyNode* mpRight;
    KeyNode* mpLeft;
    KeyNode* mpParent;
    uint32_t mColor;
    uint32_t mKey;
    ResourceKey mValue;
};
struct KeyMap {
    uint32_t mAllocator;     // +0x00
    KeyNode* mpAnchorRight;  // +0x04
    KeyNode* mpAnchorLeft;   // +0x08
    KeyNode* mpRoot;         // +0x0c
    uint8_t mColor;          // +0x10
    uint32_t mnSize;         // +0x14

    KeyMap();                                               // 0x00bf2c60
    void Set(uint32_t key, const ResourceKey& value);       // 0x00bf4a60  map[key] = value
    void Insert(uint32_t key);                              // 0x00bf9300  default-insert
    ResourceKey* Get(uint32_t key);                         // 0x00bf9700  find-or-insert, returns &value

    void DoNukeSubtree(KeyNode* pNode)
    {
        while (pNode) {
            DoNukeSubtree(pNode->mpRight);
            KeyNode* pLeft = pNode->mpLeft;
            operator delete[](pNode);
            pNode = pLeft;
        }
    }
    ~KeyMap() { DoNukeSubtree(mpRoot); }
};

// ------------------------------------------------------------------ singletons and stubs
struct cObjectTemplateDB {
    PV8 PV8 PV4 PV2
    virtual void Register(const ResourceKey* key, int flag);  // +0x58
};
cObjectTemplateDB* ObjectTemplateDB();                        // 0x0067cb40

struct cTerrainSphere {
    uint32_t pad00[0x1150 / 4];
    ResourceKey mKey1150;                                     // +0x1150
    uint32_t pad115c[3];
    ResourceKey mKey1168;                                     // +0x1168
};
struct cGameNounManager {
    cTerrainSphere* GetCurrentTerrainSphere();                // 0x00f67d90
    void ProcessPending();                                    // 0x00b22960
};
cGameNounManager* NounManager();                              // 0x00b3d300

struct cModelEntity {
    void StoreModelKeys(const KeyMap* keys);                  // 0x00ff3190
};
struct cPlanetRecord {
    uint32_t pad00[0x15c / 4];
    cModelEntity** mpEntitiesBegin;                           // +0x15c
    cModelEntity** mpEntitiesEnd;                             // +0x160
    uint32_t GetCommContext();                                // 0x00ce6950
    int GetEntry();                                           // 0x00b8dab0
    cModelEntity* GetEntity(int index);                       // 0x00b8dec0
};
cPlanetRecord* GetPlayerHomePlanet();                         // 0x01021370
void RegisterHomePlanet(cPlanetRecord* home, int entry);      // 0x00b96f40 (cdecl)

struct cEmpire {
    char* GetData();                                          // 0x00c30c80
};
cEmpire* GetPlayerEmpire();                                   // 0x01021300
void* Unused_b3d460();                                        // 0x00b3d460

struct IBox {
    PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV4
    virtual void SetWorldBounds(const Vector3* box, float a, float b);  // +0x150
};
IBox* GonzagoModelWorld();                                    // 0x00b3d520

struct BakeParam {
    uint32_t mContext;
    uint16_t mA;
    uint16_t mB;
};

struct cPropertyList {
    int GetIntProperty(uint32_t id);                          // 0x006a2660
};
extern cPropertyList* sAppProperties;                         // 0x015fd918

struct cPlanetModel {
    float GetMinAltitude();                                   // 0x00b7e4d0
};
cPlanetModel* PlanetModel();                                  // 0x00b3d350

struct cCameraSettings {
    float GetRadiusFactor();                                  // 0x00a0ab60
};
cCameraSettings* CameraSettings();                            // 0x00c37360

struct cTimeOfDay {
    void GetSunPosition(Vector3* out);                        // 0x00bc2c00
};
cTimeOfDay* TimeOfDayInstance();                              // 0x00bc30b0

struct cPlayerUFO {
    void SetAltitude(float altitude);                         // 0x00c3daa0
    void PopToDestination();                                  // 0x00c37e60
    float GetFloat();                                         // 0x00c3ae70
    void ApplyKey(const ResourceKey* key);                    // 0x00c381e0
};

struct cSimThing {
    void Notify(uint32_t id);                                 // 0x00b5cde0
};
cSimThing* SimSystem();                                       // 0x00b3d230

struct cSPUISpace {
    void ShowBakeTimeSplash();                                // 0x01065ab0
};
struct cSpaceSub {
    uint32_t pad00[0x40 / 4];
    void* mpField40;                                          // +0x40 (stub: see SetName)
};
struct cNamed40 {
    void SetName(const void* name);                           // 0x00ff4840
};
struct cSPSimulatorSpaceGame {
    uint32_t pad00[0x14 / 4];
    cSPUISpace* mpUI;                                         // +0x14
    uint32_t pad18[(0x40 - 0x18) / 4];
    cNamed40* mpField40;                                      // +0x40
    uint32_t pad44[(0x50 - 0x44) / 4];
    uint32_t mFlags;                                          // +0x50
    void StepA();                                             // 0x01003490
    void StepB();                                             // 0x01003a50
    void StepC();                                             // 0x01003690
};
struct cSPSimulatorPlayerUFO {
    cPlayerUFO* GetPlayerUFO();                               // 0x00a1ad60
    void InitForPlanet();                                     // 0x00ffd390
    void SetPlanetDestination(Vector3* pos, bool a, bool b, bool c, bool d);  // 0x00ffc350
};
cSPSimulatorPlayerUFO* SpaceGame();                           // 0x00ffbe50

struct cPlanet {
    void Refresh1();    // 0x00c73ff0
    void Refresh2();    // 0x00c74280
    void Refresh3(int a);  // 0x00c73cf0
    void Restart();     // 0x00c6ffa0
};
cPlanet* GetActivePlanet();                                   // 0x01021260

extern void* g_slotMsgVtbl0;                                  // 0x013eb90c
extern void* g_slotMsgVtbl1;                                  // 0x013eb844
struct SlotMessage {
    void* vptr;           // +0x00
    long mRef;            // +0x04
    uint32_t pad08[2];
    uint32_t mTarget;     // +0x10
    uint32_t pad14[7];
    uint32_t mData30;     // +0x30
    uint32_t pad34;
    uint32_t mData38;     // +0x38
    uint32_t pad3c;

    SlotMessage()
    {
        mData30 = 0;
        vptr = &g_slotMsgVtbl0;
        _InterlockedExchange(&mRef, 0);
        vptr = &g_slotMsgVtbl1;
        mData38 = 0;
    }
    void Destruct();                                          // 0x00421cf0
    ~SlotMessage() { Destruct(); }
};
struct IMessageServer {
    PV4 PV
    virtual void Post(uint32_t id, SlotMessage* msg, int flag);  // +0x14
};
IMessageServer* MessageServer();                              // 0x0067dcc0

struct IInputManager {
    PV8 PV8 PV8
    virtual bool IsControlActive(int control, int flag);      // +0x60
};
IInputManager* InputManager();                                // 0x0067dd50

struct cGameTimeManager {
    void IncPauseGate(uint32_t id);                           // 0x00b32220
};
cGameTimeManager* GameTimeManager();                          // 0x00b3d380

struct MissionHelper {};
int MissionIndexFromFloat(float f);                           // 0x01021240 (cdecl)
void MakeKeyFromIndex(ResourceKey* out, int index);           // 0x0105c5d0 (cdecl)
extern char kInterstellarDrive[];                             // 0x016d99a0

class cAppModeSpace {
public:
    uint32_t pad000[0x7c / 4];
    ResourceKey mUFOKey;                                      // +0x7c
    uint32_t pad88[(0x15c - 0x88) / 4];
    cSPSimulatorSpaceGame* mpSimulatorSpaceGame;              // +0x15c
    uint32_t pad160;
    uint32_t mElapsedBakeTimeForTransitionMS;                 // +0x164
    uint8_t pad168;
    bool mbBakeStarted;                                       // +0x169
    bool mBakingForPlanetEntryEnded;                          // +0x16a
    uint8_t pad16b;
    uint32_t mCommContext;                                    // +0x16c
    eastl::list<ResourceKey> mNeedsBakingForTransition;       // +0x170
    eastl::list<bool> mInputFlags;                            // +0x17c
    uint8_t pad188[0x18e - 0x188];
    bool mbTutorial;                                          // +0x18e

    void LoadNewGamePlanet();                                 // 0x00fdc240
    void AddBakeKey(const BakeParam* p, const ResourceKey* key);  // 0x00fdd320
    void SetPlanetTimeOnFirstEntry();                         // 0x00fda530
    void Func_fda750();                                       // 0x00fda750
    void Func_fdf9f0();                                       // 0x00fdf9f0

    void InitSpaceMode();
};

// @ 0x00fe0570
void cAppModeSpace::InitSpaceMode()
{
    cObjectTemplateDB* db = ObjectTemplateDB();
    cTerrainSphere* s1 = NounManager()->GetCurrentTerrainSphere();
    db->Register(&s1->mKey1168, 1);
    db = ObjectTemplateDB();
    cTerrainSphere* s2 = NounManager()->GetCurrentTerrainSphere();
    db->Register(&s2->mKey1150, 1);

    cPlanetRecord* home = GetPlayerHomePlanet();
    mBakingForPlanetEntryEnded = true;
    mbBakeStarted = false;
    mElapsedBakeTimeForTransitionMS = 0;
    uint32_t context = home->GetCommContext();
    mCommContext = context;
    RegisterHomePlanet(home, home->GetEntry());

    KeyMap keys;
    keys.Set(0x99e92f05, NounManager()->GetCurrentTerrainSphere()->mKey1150);
    keys.Insert(0x4e3f7777);
    keys.Insert(0x47c10953);
    keys.Insert(0x72c49181);
    keys.Insert(0x2090a11b);
    keys.Insert(0xbc1041e6);
    keys.Insert(0xc15695da);
    keys.Set(0x7d433fad, ZeroKey());
    keys.Set(0xf670aa43, ZeroKey());
    keys.Set(0x9ad7d4aa, ZeroKey());
    keys.Set(0x8f963dcb, ZeroKey());
    keys.Set(0x2a5147a9, ZeroKey());
    keys.Set(0x1f2a25b6, ZeroKey());
    keys.Set(0x441cd3e6, ZeroKey());
    keys.Set(0x1a4e0708, ZeroKey());
    keys.Set(0x449c040f, ZeroKey());

    if (home && home->mpEntitiesBegin != home->mpEntitiesEnd) {
        int n = (int)(home->mpEntitiesEnd - home->mpEntitiesBegin);
        for (int i = 0; i < n; i++) {
            cModelEntity* entity = home->GetEntity(i);
            entity->StoreModelKeys(&keys);
        }
    }

    BakeParam param;
    param.mA = 0;
    param.mB = 2;
    param.mContext = context;
    AddBakeKey(&param, keys.Get(0x99e92f05));
    AddBakeKey(&param, keys.Get(0x4e3f7777));
    AddBakeKey(&param, keys.Get(0x47c10953));
    AddBakeKey(&param, keys.Get(0x72c49181));
    AddBakeKey(&param, keys.Get(0x2090a11b));
    AddBakeKey(&param, keys.Get(0xbc1041e6));
    AddBakeKey(&param, keys.Get(0xc15695da));
    AddBakeKey(&param, &NounManager()->GetCurrentTerrainSphere()->mKey1168);
    Unused_b3d460();
    AddBakeKey(&param, (const ResourceKey*)(GetPlayerEmpire()->GetData() + 0x504));

    Vector3 box[2];
    box[0].x = -1500.0f;
    box[0].y = -1500.0f;
    box[0].z = -500.0f;
    box[1].x = 1500.0f;
    box[1].y = 1500.0f;
    box[1].z = 500.0f;
    GonzagoModelWorld()->SetWorldBounds(box, 0.0f, 1.0e10f);

    cTerrainSphere* sphere = NounManager()->GetCurrentTerrainSphere();
    const ResourceKey* ufoKey = &sphere->mKey1168;
    mUFOKey.instanceID = ufoKey->instanceID;
    mUFOKey.typeID = ufoKey->typeID;
    mUFOKey.groupID = ufoKey->groupID;
    Func_fda750();

    int startMode = sAppProperties->GetIntProperty(0x1c29572);
    cPlayerUFO* ufo = SpaceGame()->GetPlayerUFO();
    switch (startMode) {
    case 0: {
        LoadNewGamePlanet();
        MessageServer()->Post(0x279a5da, 0, 0);
        mpSimulatorSpaceGame->StepC();
        cSPSimulatorPlayerUFO* game = SpaceGame();
        game->InitForPlanet();
        ufo = game->GetPlayerUFO();
        float half = CameraSettings()->GetRadiusFactor() * 0.5f;
        ufo->SetAltitude(PlanetModel()->GetMinAltitude() + half);
        Vector3 pos;
        TimeOfDayInstance()->GetSunPosition(&pos);
        game->SetPlanetDestination(&pos, false, true, false, false);
        game->GetPlayerUFO()->PopToDestination();
        SetPlanetTimeOnFirstEntry();
        Func_fdf9f0();
        SlotMessage msg;
        msg.mTarget = (uint32_t)GetActivePlanet();
        MessageServer()->Post(0x248975f, &msg, 0);
        break;
    }
    case 1:
        SimSystem()->Notify(0x1103192);
        mpSimulatorSpaceGame->StepB();
        break;
    case 2: {
        mpSimulatorSpaceGame->mpField40->SetName(kInterstellarDrive);
        SimSystem()->Notify(0x1103192);
        mpSimulatorSpaceGame->StepA();
        ResourceKey key;
        MakeKeyFromIndex(&key, MissionIndexFromFloat(ufo->GetFloat()));
        ufo->ApplyKey(&key);
        break;
    }
    }

    NounManager()->ProcessPending();
    cPlanet* planet = GetActivePlanet();
    planet->Refresh1();
    planet->Refresh2();
    planet->Refresh3(0);
    planet->Restart();

    if (!mBakingForPlanetEntryEnded) {
        if (!mbTutorial && mpSimulatorSpaceGame->mpUI)
            mpSimulatorSpaceGame->mpUI->ShowBakeTimeSplash();
        GameTimeManager()->IncPauseGate(0x4bf38a7);
        for (int i = 0; i <= 0x1b; i++) {
            bool value = InputManager()->IsControlActive(i, 1) & 1;
            mInputFlags.push_back(value);
        }
        mbBakeStarted = true;
    }
    mpSimulatorSpaceGame->mFlags |= 0x10;
}
