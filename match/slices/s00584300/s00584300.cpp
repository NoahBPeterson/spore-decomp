// slice s00584300: SP::cAppModeEditorBase::Init (0x00584300, 4134 bytes).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-   (no EH frame, movss float store).
// Retail layout differs from the 2008 PDB (retail is ~0x5d4 bytes); offsets below come from the asm.
#include "types.h"

#define PV(n) virtual void _pv##n();
#define PV4(n) PV(n##0) PV(n##1) PV(n##2) PV(n##3)
#define PV16(n) PV4(n##0) PV4(n##1) PV4(n##2) PV4(n##3)

// EA operator new (name, flags, debugFlags, file, line); no matching delete, so no EH.
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);   // 0x00f473a0

// ---------------------------------------------------------------------------------------------
// Smart pointers / containers

template <class T>
struct AutoRefCount {
    T* mpObject;
    AutoRefCount& operator=(T* p)
    {
        if (p != mpObject) {
            T* const pTemp = mpObject;
            if (p)
                p->AddRef();
            mpObject = p;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};

// EA::RefCountTemplate-style object: non-virtual refcount at +4, deleting dtor in vtable slot 0.
struct cRefCounted {
    cRefCounted() : mnRefCount(0) {}
    virtual ~cRefCounted();
    int mnRefCount;
    int AddRef() { return ++mnRefCount; }
    int Release()
    {
        int n = mnRefCount - 1;
        mnRefCount = n;
        if (n == 0) {
            mnRefCount = 1;
            delete this;
        }
        return n;
    }
};

template <int N>
struct bitset {
    uint32_t mWord[(N + 31) / 32];
    bitset() { reset(); }
    void reset()
    {
        for (int i = 0; i < (N + 31) / 32; ++i)
            mWord[i] = 0;
    }
    void set(uint32_t i)
    {
        if (i < (uint32_t)N)
            mWord[i >> 5] |= ((uint32_t)1 << (i & 31));
    }
};

struct rbtree_node_base {
    rbtree_node_base* mpNodeRight;
    rbtree_node_base* mpNodeLeft;
    rbtree_node_base* mpNodeParent;
    char mColor;
};

// eastl::rbtree<unsigned, pair<const unsigned, cSPUILayoutManager::cWorld>, ...>
struct cWorldMap {
    uint32_t mCompare;
    rbtree_node_base mAnchor;
    uint32_t mnSize;
    uint32_t mAllocator;
    void DoNukeSubtree(rbtree_node_base* pNode);   // 0x009a9600
    void reset()
    {
        mAnchor.mpNodeRight = &mAnchor;
        mAnchor.mpNodeLeft = &mAnchor;
        mAnchor.mpNodeParent = 0;
        mAnchor.mColor = 0;
        mnSize = 0;
    }
    void clear()
    {
        DoNukeSubtree(mAnchor.mpNodeParent);
        reset();
    }
};

// eastl::map<unsigned int, unsigned int>
struct cUIntMap {
    uint32_t mData[7];
    uint32_t& operator[](const uint32_t& key);       // 0x00643a40
};

// ---------------------------------------------------------------------------------------------
// Interfaces (only the vtable slots used here)

typedef void* (*FactoryFn)();
void* FUN_005a4150();                                // 0x005a4150
void* CreateCreatureCameraBase();                    // SP::CreateCreatureCameraBase 0x00627c70

struct cICameraManager {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7)
    virtual void RegisterFactory(uint32_t id, FactoryFn fn);   // +0x20
};

struct cIApp {
    PV16(0) PV(10) PV(11) PV(12) PV(13)
    virtual cICameraManager* GetCameraManager();     // +0x50
};

struct IHandler;

struct IMessageServer {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7)
    virtual void AddListener(IHandler* h, uint32_t id);        // +0x20
    virtual void AddRegistration(IHandler* h, uint32_t id);    // +0x24
};

struct cIVirtualRC {                                 // AddRef/Release in slots 1/2
    PV(0)
    virtual int AddRef();
    virtual int Release();
};

struct cEditorsTokenTranslator : cIVirtualRC {
    cEditorsTokenTranslator();                       // 0x005d5e40
    uint32_t mData[15];
};

struct cSPEditorPhysicsWorld : cRefCounted {
    cSPEditorPhysicsWorld();                         // 0x004b8af0
    void Init();                                     // 0x004b8c10
    uint32_t mData[10];
};

struct cSPEditorAppEconomy : cRefCounted {
    cSPEditorAppEconomy()
        : field_8(0), field_C(0), field_10(0), field_1C(0), field_20(0), field_24(0)
    {
    }
    virtual void _e1(); virtual void _e2(); virtual void _e3(); virtual void _e4(); virtual void _e5();
    virtual void SetFunds(int a, int b);             // +0x18
    void Init(int n);                                // 0x0059ec80
    int field_8;
    int field_C;
    int field_10;
    int field_14;
    int field_18;
    int field_1C;
    int field_20;
    int field_24;
    int field_28;
    int field_2C;
};

struct cILightingWorld {
    virtual int AddRef();
    virtual int Release();
};

struct cILightingManager {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5)
    virtual cILightingWorld* CreateWorld(uint32_t id, int a, int b);   // +0x18
};

struct cIModelWorld {
    virtual int AddRef();
    virtual int Release();
    PV16(0) PV16(1) PV16(2) PV16(3)                  // slots 2..65
    PV4(40) PV(410)                                  // slots 66..70
    virtual void SetGroupInclusion(bitset<64>* render, bitset<64>* shadow, int layer);   // +0x11c
    PV4(44) PV4(45)                                  // slots 72..79
    virtual void AddLightingWorld(cILightingWorld* w, int index, int flag);              // +0x140
};

struct cIModelManager {
    PV(0) PV(1) PV(2) PV(3) PV(4)
    virtual cIModelWorld* CreateWorld(uint32_t id, int a, int b);   // +0x14
    PV(6) PV(7) PV(8) PV(9)
    virtual uint32_t GetGroupIndex(uint32_t id, int a);             // +0x28
};

struct cIEffectsWorld {
    virtual int AddRef();
    virtual int Release();
    PV(2)
    virtual void SetState(int s);                    // +0x0c
};

struct cIEffectsManager {
    PV16(0) PV(10) PV(11) PV(12)
    virtual cIEffectsWorld* CreateWorld(uint32_t id, int a);   // +0x4c
};

struct cZoneObject : cIVirtualRC {                   // 0xc-byte object, ctor 0x00998820
    static void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags,
                              const char* file, int line);    // 0x00926020
    cZoneObject();
    uint32_t mData[2];
};

struct cIZoneOwner {                                 // returned by 0x008de1a0
    PV16(0) PV(10)
    virtual void Attach(int a, cZoneObject* obj, int b);   // +0x44
};

struct cViewer {
    cViewer();                                       // 0x007c3f70
    void Init(int a);                                // 0x007c4dd0
    uint32_t mData[0x174 / 4];
};

struct IStream {
    PV4(0) PV4(1) PV4(2)
    virtual int Read(void* p, int n);                // +0x30
};

struct IRecord {
    PV(0) PV(1)
    virtual int Release();                           // +0x08
    PV(3) PV(4) PV(5)
    virtual IStream* GetStream();                    // +0x18
    PV(7) PV(8)
    virtual void Close();                            // +0x24
};

struct RecordPtr {                                   // EA::AutoRefCount<EA::ResourceMan::Record>
    IRecord* mpObject;
    RecordPtr() : mpObject(0) {}
    ~RecordPtr()
    {
        if (mpObject)
            mpObject->Release();
    }
    IRecord* operator->() const { return mpObject; }
};

struct ISaveArea {
    PV4(0) PV4(1) PV4(2) PV(3)
    virtual bool OpenRecord(const void* key, RecordPtr* ppRecord, int a, int b, int c, int d);   // +0x34
};

struct cDirectPropertyList {
    void SetBoolProperty(uint32_t id, bool value);   // 0x006a17e0
    uint32_t pad[15];
    struct Inner { uint32_t pad[0x118 / 4]; int field_118; }* mpInner;   // +0x3c
};

struct ICheatManager {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5)
    virtual void AddCheat(const char* name, void* cheat, bool b);   // +0x18
};

class cAppModeEditorBase;

// ArgScript::ICommand base (ctor 0x0083c800); editor cheats keep the editor at +0x10.
struct ICommand {
    ICommand();                                      // 0x0083c800
    virtual void _c0(); virtual void _c1(); virtual void _c2();
    virtual void _c3(); virtual void _c4(); virtual void _c5();
    uint32_t mData[3];
};

#define EDITOR_CHEAT(Name)                                                        \
    struct Name : ICommand {                                                      \
        Name(cAppModeEditorBase* p) : mpEditor(p) {}                              \
        virtual void _c0(); virtual void _c1(); virtual void _c2();               \
        virtual void _c3(); virtual void _c4(); virtual void _c5();               \
        cAppModeEditorBase* mpEditor;                                             \
    };
EDITOR_CHEAT(cAddDNACheat)
EDITOR_CHEAT(cFreedomCheat)
EDITOR_CHEAT(cToggleEditorBackgroundCheat)
EDITOR_CHEAT(cColladaExportCheat)

IMessageServer* MessageServer();                    // 0x0067dcc0
cIModelManager* ModelManager();                     // 0x0067dd80
cILightingManager* LightingManager();               // 0x0067dd90
cIEffectsManager* EffectsManager();                 // 0x0067ddd0
ICheatManager* CheatManager();                      // 0x0067de20
cIZoneOwner* GetZoneOwner();                        // 0x008de1a0
ISaveArea* GetSaveArea(uint32_t id);                // 0x006b1f90
void FUN_005a9b60();                                 // 0x005a9b60
void FUN_00563de0();                                 // 0x00563de0

extern cDirectPropertyList* g_AppProperties;        // 0x015fd918
extern AutoRefCount<cEditorsTokenTranslator> g_TokenTranslator;   // 0x015eebec
extern const char g_EditorKey[];                     // 0x0150cfa0

static const uint32_t kEditorMessageIds[1] = { 0xb03bc30c };   // 0x013f5c9c

struct cMessageRegistration {
    IMessageServer* mpServer;
    IHandler* mpHandler;
    const uint32_t* mpIds;
    int mnIds;
    int mnFlags;
    void Init(IMessageServer* server, IHandler* handler, const uint32_t* ids, int n)
    {
        mpServer = server;
        mpHandler = handler;
        mpIds = ids;
        mnIds = n;
        mnFlags = 0;
        if (mpHandler)
            for (int i = 0; i < n; ++i)
                mpServer->AddRegistration(mpHandler, ids[i]);
    }
};

// ---------------------------------------------------------------------------------------------

#pragma pack(push, 2)
struct cIntShort { int a; short b; };
#pragma pack(pop)

#pragma pack(push, 4)
class cAppModeEditorBase {
public:
    PV16(0) PV(10) PV(11) PV(12) PV(13)
    virtual void OnInitDone();                       // +0x50
    bool Init(cIApp* app);
    void FUN_00584070();                             // 0x00584070

    uint32_t _p004[3];
    uint32_t mHandlerBase[4];                        // +0x10 IHandlerRC subobject
    cIApp* mApp;                                     // +0x20
    uint32_t _p024[(0x6c - 0x24) / 4];
    float field_6C;                                  // +0x6c
    uint32_t _p070[4];
    AutoRefCount<cILightingWorld> mLightingWorld;    // +0x80
    AutoRefCount<cIModelWorld> mModelWorld;          // +0x84
    AutoRefCount<cIModelWorld> mModelWorld88;        // +0x88
    AutoRefCount<cIModelWorld> mModelWorld8C;        // +0x8c
    AutoRefCount<cSPEditorPhysicsWorld> mPhysicsWorld;   // +0x90
    AutoRefCount<cIEffectsWorld> mEffectsWorld;      // +0x94
    uint32_t _p098[(0x15c - 0x98) / 4];
    AutoRefCount<cZoneObject> mZoneObject;           // +0x15c
    uint32_t _p160[(0x1b0 - 0x160) / 4];
    cUIntMap mResourceToConfigMap;                   // +0x1b0
    uint32_t _p1cc[(0x220 - 0x1cc) / 4];
    bitset<64> mPartsModeRenderInclude;              // +0x220
    bitset<64> mPartsModeShadowInclude;              // +0x228
    bitset<64> mPaintModeRenderInclude;              // +0x230
    bitset<64> mPaintModeShadowInclude;              // +0x238
    bitset<64> mAnimCreatureRenderInclude;           // +0x240
    bitset<64> mAnimCreatureShadowInclude;           // +0x248
    bitset<64> mPartsModeEnvironmentInclude;         // +0x250
    bitset<64> mPaintModeEnvironmentInclude;         // +0x258
    uint32_t _p260[(0x3cc - 0x260) / 4];
    cViewer* mViewer3CC;                             // +0x3cc
    cViewer* mViewer3D0;
    cViewer* mViewer3D4;
    cViewer* mViewer3D8;
    cViewer* mViewer3DC;
    uint32_t _p3e0[(0x434 - 0x3e0) / 4];
    AutoRefCount<cSPEditorAppEconomy> mEconomy;      // +0x434
    uint32_t _p438[4];
    uint64_t mStoredTime;                            // +0x448
    uint32_t _p450;
    cWorldMap mWorlds;                               // +0x454
    uint32_t _p470[(0x580 - 0x470) / 4];
    union {
        struct { int field_580; short field_584; };
        cIntShort mPair580;                          // +0x580
    };
    uint32_t _p588[(0x5c0 - 0x588) / 4];
    cMessageRegistration mRegistration;              // +0x5c0

    IHandler* AsHandler() { return (IHandler*)mHandlerBase; }
};
#pragma pack(pop)

// @ 0x00584300  SP::cAppModeEditorBase::Init
bool cAppModeEditorBase::Init(cIApp* app)
{
    mWorlds.clear();
    mApp = app;
    mApp->GetCameraManager()->RegisterFactory(0xfcc521, FUN_005a4150);
    mApp->GetCameraManager()->RegisterFactory(0x3d437e3, CreateCreatureCameraBase);

    {
        uint32_t key;
        key = 0x3d97a8e4; mResourceToConfigMap[key] = 0x3615a30b;
        key = 0x2b978c46; mResourceToConfigMap[key] = 0x465c50ba;
        key = 0x2399be55; mResourceToConfigMap[key] = 0xd817cd63;
        key = 0x24682294; mResourceToConfigMap[key] = 0x99f87089;
        key = 0x476a98c7; mResourceToConfigMap[key] = 0x96b24187;
        key = 0x438f6347; mResourceToConfigMap[key] = 0x1c7eca95;
    }

    FUN_005a9b60();

    IMessageServer* pServer = MessageServer();
    if (pServer) {
        mRegistration.Init(pServer, AsHandler(), kEditorMessageIds, 1);
        pServer->AddListener(AsHandler(), 0x29d57f4);
        pServer->AddListener(AsHandler(), 0x3fc3f13);
        pServer->AddListener(AsHandler(), 0x62628f0);
    }

    g_AppProperties->SetBoolProperty(0x43, false);

    g_TokenTranslator = new ("Editor", 0, 0, 0, 0) cEditorsTokenTranslator();

    mPhysicsWorld = new ("Editor", 0, 0, 0, 0) cSPEditorPhysicsWorld();
    mPhysicsWorld->Init();

    mEconomy = new ("Editor", 0, 0, 0, 0) cSPEditorAppEconomy();
    mEconomy->Init(6);
    if (g_AppProperties->mpInner->field_118)
        mEconomy->SetFunds(0, 9999);

    cIModelManager* pModelManager = ModelManager();
    if (pModelManager) {
        mLightingWorld = LightingManager()->CreateWorld(0xe4c6e4, 0, 0);
        mModelWorld = pModelManager->CreateWorld(0xe4c6e4, 0, 0);
        mModelWorld8C = pModelManager->CreateWorld(0x21b37d6, 0, 0);
        mModelWorld88 = pModelManager->CreateWorld(0x5557b15, 0, 0);

        mModelWorld->AddLightingWorld(mLightingWorld, 0, 1);
        mModelWorld->AddLightingWorld(mLightingWorld, 2, 0);
        mModelWorld->AddLightingWorld(mLightingWorld, 3, 0);
        mModelWorld->AddLightingWorld(mLightingWorld, 7, 0);
        mModelWorld8C->AddLightingWorld(mLightingWorld, 0, 0);
        mModelWorld88->AddLightingWorld(mLightingWorld, 0, 1);

        mPartsModeEnvironmentInclude.set(pModelManager->GetGroupIndex(0xfe39de0, 0));
        mPaintModeEnvironmentInclude.set(pModelManager->GetGroupIndex(0xfe39de0, 0));

        mPartsModeRenderInclude.set(pModelManager->GetGroupIndex(0x9138fd8d, 0));
        mPartsModeRenderInclude.set(pModelManager->GetGroupIndex(0x4fe3913, 0));
        mPartsModeRenderInclude.set(pModelManager->GetGroupIndex(0xfeb8df2, 0));
        mPartsModeRenderInclude.set(pModelManager->GetGroupIndex(0x900c6cdd, 0));
        mPartsModeRenderInclude.set(pModelManager->GetGroupIndex(0x31390733, 0));
        mPartsModeRenderInclude.set(pModelManager->GetGroupIndex(0x31390732, 0));
        mPartsModeRenderInclude.set(pModelManager->GetGroupIndex(0x1ba53ea, 0));
        mPartsModeRenderInclude.set(pModelManager->GetGroupIndex(0x31390734, 0));

        mPartsModeShadowInclude.set(pModelManager->GetGroupIndex(0x9138fd8d, 0));
        mPartsModeShadowInclude.set(pModelManager->GetGroupIndex(0x4fe3913, 0));
        mPartsModeShadowInclude.set(pModelManager->GetGroupIndex(0xfeb8df2, 0));

        mPaintModeRenderInclude.set(pModelManager->GetGroupIndex(0x9138fd8d, 0));
        mPaintModeRenderInclude.set(pModelManager->GetGroupIndex(0x4fe3913, 0));
        mPaintModeRenderInclude.set(pModelManager->GetGroupIndex(0xfeb8df2, 0));

        mPaintModeShadowInclude.set(pModelManager->GetGroupIndex(0x9138fd8d, 0));
        mPaintModeShadowInclude.set(pModelManager->GetGroupIndex(0x4fe3913, 0));
        mPaintModeShadowInclude.set(pModelManager->GetGroupIndex(0xfeb8df2, 0));

        mAnimCreatureRenderInclude.set(pModelManager->GetGroupIndex(0x509991e6, 0));
        mAnimCreatureShadowInclude.set(pModelManager->GetGroupIndex(0x509991e6, 0));
    }

    if (mModelWorld) {
        bitset<64> includeGroup;
        bitset<64> excludeGroup;
        cIModelManager* pMM = ModelManager();

        includeGroup.set(pMM->GetGroupIndex(0x9138fd8d, 0));
        includeGroup.set(pMM->GetGroupIndex(0x4fe3913, 0));
        includeGroup.set(pMM->GetGroupIndex(0xfe39de0, 0));
        includeGroup.set(pMM->GetGroupIndex(0xfeb8df2, 0));
        includeGroup.set(pMM->GetGroupIndex(0x509991e6, 0));
        mModelWorld->SetGroupInclusion(&includeGroup, &excludeGroup, 1);

        includeGroup.reset();
        excludeGroup.reset();
        includeGroup.set(pMM->GetGroupIndex(0x22fff11, 0));
        mModelWorld->SetGroupInclusion(&includeGroup, &excludeGroup, 2);

        includeGroup.reset();
        excludeGroup.reset();
        includeGroup.set(pMM->GetGroupIndex(0x23008d4, 0));
        mModelWorld->SetGroupInclusion(&includeGroup, &excludeGroup, 3);

        includeGroup.reset();
        excludeGroup.reset();
        includeGroup.set(pMM->GetGroupIndex(0x9138fd8d, 0));
        mModelWorld->SetGroupInclusion(&includeGroup, &excludeGroup, 7);

        includeGroup.reset();
        excludeGroup.reset();
        includeGroup.set(pMM->GetGroupIndex(0x9138fd8d, 0));
        includeGroup.set(pMM->GetGroupIndex(0x4fe3913, 0));
        includeGroup.set(pMM->GetGroupIndex(0xfeb8df2, 0));
        includeGroup.set(pMM->GetGroupIndex(0xfe39de0, 0));
        includeGroup.set(pMM->GetGroupIndex(0x900c6cdd, 0));
        includeGroup.set(pMM->GetGroupIndex(0x31390733, 0));
        includeGroup.set(pMM->GetGroupIndex(0x31390732, 0));
        includeGroup.set(pMM->GetGroupIndex(0x1ba53ea, 0));
        includeGroup.set(pMM->GetGroupIndex(0x31390734, 0));
        mModelWorld->SetGroupInclusion(&includeGroup, &excludeGroup, 0);

        includeGroup.reset();
        excludeGroup.reset();
        includeGroup.set(pMM->GetGroupIndex(0x509991e6, 0));
        mModelWorld->SetGroupInclusion(&includeGroup, &excludeGroup, 5);
    }

    mEffectsWorld = EffectsManager()->CreateWorld(0xe4c6e4, 0);
    mEffectsWorld->SetState(2);

    cIZoneOwner* pOwner = GetZoneOwner();
    if (!pOwner)
        return false;

    mZoneObject = new ("Editor", 0, 0, 0, 0) cZoneObject();
    pOwner->Attach(1, mZoneObject, 0);

    FUN_00563de0();
    FUN_00563de0();

    mViewer3D0 = new ("Editor", 0, 0, 0, 0) cViewer();
    mViewer3D0->Init(0);
    mViewer3D4 = new ("Editor", 0, 0, 0, 0) cViewer();
    mViewer3D4->Init(0);
    mViewer3CC = new ("Editor", 0, 0, 0, 0) cViewer();
    mViewer3CC->Init(0);
    mViewer3D8 = new ("Editor", 0, 0, 0, 0) cViewer();
    mViewer3D8->Init(0);
    mViewer3DC = new ("Editor", 0, 0, 0, 0) cViewer();
    mViewer3DC->Init(0);

    FUN_00584070();

    ISaveArea* pSaveArea = GetSaveArea(0x11ac19c);
    if (pSaveArea) {
        RecordPtr pRecord;
        if (pSaveArea->OpenRecord(g_EditorKey, &pRecord, 1, 3, 1, 0)) {
            uint64_t n64StoredTime;
            if (pRecord->GetStream()->Read(&n64StoredTime, 8) == 8)
                mStoredTime = n64StoredTime;
            pRecord->Close();
        }
    }

    field_6C = 500.0f;
    OnInitDone();

    mPair580 = cIntShort();

    CheatManager()->AddCheat("addDNA", new ("Editor", 0, 0, 0, 0) cAddDNACheat(this), true);
    CheatManager()->AddCheat("freedom", new ("Editor", 0, 0, 0, 0) cFreedomCheat(this), true);
    CheatManager()->AddCheat("toggleeditorbackground",
                             new ("Editor", 0, 0, 0, 0) cToggleEditorBackgroundCheat(this), true);
    CheatManager()->AddCheat("colladaexport", new ("Editor", 0, 0, 0, 0) cColladaExportCheat(this), true);
    return true;
}
