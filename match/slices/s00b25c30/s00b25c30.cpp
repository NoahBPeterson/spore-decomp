// Slice s00b25c30: cGameNounManager noun-registry/reset helpers, the UI timeline objects
// (cSPUITimeline) and the cSPUIGlobalUIRootWinProc helpers that share the same translation unit.
// /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc: none of these bodies installs an EH frame).
// Out-of-line callees are only declared; their original addresses are in the trailing comments.
#include "types.h"

typedef unsigned int size_t;

// ---------------------------------------------------------------------------------------------
// data globals touched by this slice
// ---------------------------------------------------------------------------------------------
extern const wchar_t g_emptyString16[];        // 0x01667bac (eastl::gEmptyString16)
extern uint32_t g_uiModeToken;                 // 0x0167e04c (set to 6 when a UI mode is entered)
extern char     g_uiModeByte;                  // 0x0167e068
extern int32_t  g_modeArg;                     // 0x0167dfa8 (passed by address to the mode switch)
extern uint32_t g_timeSource;                  // 0x0167df98 (1 = rdtsc, otherwise QueryPerformanceCounter)
extern uint32_t g_timerStartLow;               // 0x0167df88
extern uint32_t g_timerStartHigh;              // 0x0167df8c
extern uint32_t g_timerElapsedLow;             // 0x0167df90
extern uint32_t g_timerElapsedHigh;            // 0x0167df94
extern const wchar_t g_leaveGameMessage[];     // 0x01568a7c
extern const wchar_t g_leaveGameTitle[];       // 0x01568a70
extern const char g_serializedFieldName[];     // 0x01568a8c
extern const char g_eastlAllocatorFile[];      // 0x013ebb38
extern const char g_quitCommand[];             // 0x014137f8 ("quit")
extern const char g_herdEffectsFactoryName[];  // 0x0145fa6c
extern const uint32_t g_timelineEvents[];      // 0x0145f82c (three registered event ids)
extern uint32_t g_classRegistryGuard;          // 0x0167c3c0 (one bit per lazily built registry)

// ---------------------------------------------------------------------------------------------
// small engine types
// ---------------------------------------------------------------------------------------------
struct cSPVector3 {
    float x, y, z;
};

void* __cdecl FUN_00f473a0(size_t size, const char* pName, int flags, int debugFlags,
                           const char* pFile, int line);         // 0x00f473a0 EA operator new
void  __cdecl FUN_00f47380(void* pBlock);                        // 0x00f47380 operator delete[]
int   __cdecl FUN_011e07ef(void (__cdecl* pfn)(void));           // 0x011e07ef lib_crt::atexit
void* __cdecl EA_Messaging_GetServer();                          // 0x00883860
void  __cdecl EA_Messaging_RemoveHandler(void* pHandler, void* p1, void* p2, void* p3,
                                         void* p4);              // 0x00571db0

class cGameData;

struct tGameDataVector {
    uint32_t    mPad00;                 // +0x00
    cGameData** mpBegin;                // +0x04
    cGameData** mpEnd;                  // +0x08
    uint32_t    mPad0c;                 // +0x0c
};

typedef tGameDataVector* (__cdecl* tVectorCreateFn)(void);
typedef void (__cdecl* tVectorClearFn)(tGameDataVector*);
typedef void (__cdecl* tVectorAddFn)(tGameDataVector*, cGameData*);
typedef bool (__cdecl* tVectorMatchFn)(cGameData*, uint32_t);

// polymorphic transform sub-object embedded in every noun (vptr at its own +0x00)
class cLocatable {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a();
    virtual const cSPVector3* GetPosition();                     // +0x2c
    virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15();
    virtual bool IsActive();                                     // +0x58
};

// one game noun (SP::cGameData as reached through tGameDataVector)
class cGameData {
public:
    virtual void v00();
    virtual void Release();                                      // +0x04
    virtual void v02();  virtual void v03();  virtual void v04();
    virtual void v05();  virtual void v06();  virtual void v07();
    virtual void v08();  virtual void v09();  virtual void v0a(); virtual void v0b();
    virtual void v0c();  virtual void v0d();  virtual void v0e(); virtual void v0f();
    virtual void v10();  virtual void v11();  virtual void v12();
    virtual uint32_t GetPoliticalID();                           // +0x4c
    virtual void v14();  virtual void v15();  virtual void v16(); virtual void v17();
    virtual void v18();  virtual void v19();  virtual void v1a(); virtual void v1b();
    virtual void v1c();  virtual void v1d();  virtual void v1e(); virtual void v1f();
    virtual void v20();  virtual void v21();  virtual void v22(); virtual void v23();
    virtual void v24();  virtual void v25();  virtual void v26(); virtual void v27();
    virtual void v28();  virtual void v29();  virtual void v2a(); virtual void v2b();
    virtual void v2c();  virtual void v2d();
    virtual cGameData* Cast(uint32_t typeID);                    // +0xb8
    uint32_t pad04[(0x120 - 0x04) / 4];                          // +0x04
    cLocatable mLocation;                                        // +0x120
    uint32_t pad124[(0x714 - 0x124) / 4];                        // +0x124
    int32_t  mObjectState;                                       // +0x714
    uint32_t pad718[(0xb58 - 0x718) / 4];                        // +0x718
    uint32_t mFlagsB58;                                          // +0xb58 (0x100 = in a posse)
    void ClearPosseMemberFlag()                                  // inline in the original
    {
        mFlagsB58 &= ~0x100u;
    }
};

// player empire (only the civilization id this slice reads)
class cEmpire {
public:
    uint32_t mPad00[0x84 / 4];                                   // +0x00
    uint32_t mCivilizationID;                                    // +0x84
};

cEmpire* GetPlayerEmpire();                                      // 0x01021300

// Reference-counted EA object; slots 0x08/0x0c are the modal-window activate/dismiss entries.
class cRefCounted {
public:
    virtual void AddRef();                                       // +0x00
    virtual void Release();                                      // +0x04
    virtual void Activate(int a);                                // +0x08
    virtual void Dismiss(int a);                                 // +0x0c
};

struct tAutoRefCount {
    cRefCounted* mpObject;                                       // +0x00
    ~tAutoRefCount()                                             // inline in the original
    {
        if (mpObject != 0)
            mpObject->Release();
    }
    void Reset()                                                 // inline in the original
    {
        if (mpObject != 0) {
            cRefCounted* pOld = mpObject;
            mpObject = 0;
            pOld->Release();
        }
    }
};

// eastl::vector<T*> view: begin/end/capacity + inline allocator (0x14 bytes)
struct tNounVector {
    cGameData** mpBegin;                // +0x00
    cGameData** mpEnd;                  // +0x04
    cGameData** mpCapacity;             // +0x08
    uint32_t    mPad0c;                 // +0x0c
    uint32_t    mPad10;                 // +0x10
};

struct tRBNode {
    tRBNode* mpLeft;                    // +0x00
    tRBNode* mpRight;                   // +0x04
    tRBNode* mpParent;                  // +0x08
    uint8_t  mColor;                    // +0x0c
    uint8_t  mPad0d[3];                 // +0x0d
};

struct tRBTree {
    uint32_t mPad00;                    // +0x00
    tRBNode  mAnchor;                   // +0x04
    uint32_t mnSize;                    // +0x14
    void FUN_00d0c930(tRBNode* pRoot);  // 0x00d0c930 (destroy the subtree below pRoot)
    void swap(tRBTree& other);          // 0x00b21da0
    void clear()                        // inline: retail inlines it at both call sites
    {
        FUN_00d0c930(mAnchor.mpParent);
        mAnchor.mpLeft = &mAnchor;
        mAnchor.mpRight = &mAnchor;
        mAnchor.mpParent = 0;
        mAnchor.mColor = 0;
        mnSize = 0;
    }
};

// eastl::map<unsigned, X>: 0x1c bytes (allocator + red-black tree)
struct tNounMap {
    uint32_t mPad00;                    // +0x00
    tRBTree  mTree;                     // +0x04
};

// EA::Messaging::AutoHandler as used by cGameNounManager (0x14 bytes)
struct tNounManagerHandler {
    void*    mpServer;                  // +0x00
    void*    mpOwner;                   // +0x04
    const uint32_t* mpEventNames;       // +0x08
    uint32_t mEventCount;               // +0x0c
    uint32_t mPad10;                    // +0x10
};

// EA::Messaging::AutoHandler as used by cSPUITimeline (0x14 bytes)
struct tUIHandler {
    void* mpHandler;                    // +0x00
    void* mSub04;                       // +0x04
    void* mSub08;                       // +0x08
    void* mSub0c;                       // +0x0c
    void* mSub10;                       // +0x10
    tUIHandler()                        // inline in the original
    {
        mpHandler = 0;
        mSub04 = 0;
        mSub08 = 0;
        mSub0c = 0;
        mSub10 = 0;
    }
    ~tUIHandler()                       // inline in the original
    {
        if (mpHandler != 0) {
            void* pHandler = mpHandler;
            mpHandler = 0;
            EA_Messaging_RemoveHandler(pHandler, mSub04, mSub08, mSub0c, mSub10);
        }
    }
};

// eastl::basic_string<wchar_t>: 0x10 bytes
struct cWString {
    const wchar_t* mpBegin;             // +0x00
    const wchar_t* mpEnd;               // +0x04
    const wchar_t* mpCapacity;          // +0x08
    uint32_t       mPad0c;              // +0x0c
    cWString()
    {
        mpCapacity = g_emptyString16 + 1;
        mpBegin = g_emptyString16;
        mpEnd = g_emptyString16;
    }
    ~cWString()                          // inline in the original
    {
        if ((int)(((uint32_t)mpCapacity - (uint32_t)mpBegin) & 0xfffffffeU) > 2 && mpBegin != 0)
            FUN_00f47380((void*)mpBegin);
    }
};

// ---------------------------------------------------------------------------------------------
// cGameNounManager (SPGonzago/SPGameNounManager.obj)
// ---------------------------------------------------------------------------------------------
class cGameNounManager;

class cNounManagerMessaging;                                     // sub-object at cGameNounManager+0x04

class cGameNounManager {
public:
    uint32_t mPad00[0x40 / 4];                   // +0x00 (vptr, definition map)
    tNounManagerHandler mAutoHandler;           // +0x40
    tAutoRefCount mAvatar;                      // +0x54
    tAutoRefCount mAvatarHerd;                  // +0x58
    tNounVector   mPosseMembers;                // +0x5c
    tAutoRefCount mPlayerTribe;                 // +0x70
    tAutoRefCount mpPlayer;                     // +0x74
    void*         mNounListNext;                // +0x78 (intrusive list anchor)
    void*         mNounListPrev;                // +0x7c
    tNounVector   mTempNouns;                   // +0x80
    tNounMap      mGameDataVectorMap;           // +0x94
    tNounMap      mGameDataVectorMapDeleted;    // +0xb0
    tNounMap      mPoliticalMap;                // +0xcc
    tNounMap      mPlanetaryContextPoliticalMap; // +0xe8
    uint32_t      mLastPoliticalID;             // +0x104
    uint32_t      mPad108[(0x118 - 0x108) / 4]; // +0x108 (pending list, damage display)

    tGameDataVector* GetGameDataVector(tVectorCreateFn fnCreate, tVectorClearFn fnClear,
                                       tVectorAddFn fnAdd, tVectorMatchFn fnMatch,
                                       uint32_t classID);        // 0x00b21340
    void FUN_00b21410(cGameData* pNoun);                         // 0x00b21410
    void FUN_00b215a0();                                         // 0x00b215a0
    void RegisterNounClasses();                                  // 0x00b24740
    void FUN_00692850();                                         // 0x00692850
    bool IsRegistered();                                         // 0x00ab30c0
    void RemoveNoun(cGameData* pNoun);                           // 0x00b225d0
    void RemoveNounsOfType(uint32_t classID);                    // 0x00b22650
    void ProcessPending();                                       // 0x00b22960
    void ValidateClassSets();                                    // 0x00b222a0
    void Flush();                                                // 0x00b206d0
    void ClearPosseMembers();                                    // 0x00b234c0
    cGameData* FindNounByEmpireID(uint32_t civID);               // 0x00b25f40
    class cCivilization* GetPlayerCivilization();                // 0x00b25fb0
    class cCity* GetPlayerCityAtPosition(const cSPVector3& position); // 0x00b262c0
    cGameData* FUN_00b25c30();
    void FUN_00b25ee0();
    void FUN_00b25fe0();
    void FUN_00b26320();
    void FUN_00b26600();
};

cGameNounManager* GetStaticObj();                                // 0x00b22210
void RegisterDramaEventsFactories();                             // 0x00d4b5a0
void FUN_00b23c60(uint32_t classID, const char* pClassName);     // 0x00b23c60
void FUN_00b25cd0();                                             // 0x00b25cd0
void FUN_0102c340(cGameData* pNoun, int a);                      // 0x0102c340
void __cdecl FUN_013c2030(void);                                 // 0x013c2030 (registry destructors)
void __cdecl FUN_013c2020(void);                                 // 0x013c2020
void __cdecl FUN_013c2010(void);                                 // 0x013c2010
void __cdecl FUN_013c2000(void);                                 // 0x013c2000

// one lazily built noun class-set registry (0x0167c3ac / 0x0167c398 / 0x0167c384 / 0x0167c370)
class cRegNode {
public:
    cRegNode* Construct(void* pArg);                             // 0x00692f60
    bool IsRegistered();                                         // 0x00ab30c0
    void Build();                                                // 0x00692850
    uint32_t mVtbl;                                              // +0x00
};

extern cRegNode g_classRegistry0;                                // 0x0167c3ac
extern cRegNode g_classRegistry1;                                // 0x0167c398
extern cRegNode g_classRegistry2;                                // 0x0167c384
extern cRegNode g_classRegistry3;                                // 0x0167c370

// Inline one-time construction of a registry node (retail inlines all four blocks).
inline void InitClassRegistry(cRegNode* pNode, uint32_t maskBit, uint32_t vtable,
                              void (__cdecl* pDestructor)())
{
    if ((g_classRegistryGuard & maskBit) == 0) {
        g_classRegistryGuard |= maskBit;
        pNode->Construct(0);
        pNode->mVtbl = vtable;
        FUN_011e07ef(pDestructor);
    }
    if (!pNode->IsRegistered())
        pNode->Build();
}

// ---------------------------------------------------------------------------------------------
// @ 0x00b25c30  first noun whose locatable reports itself active
// ---------------------------------------------------------------------------------------------
cGameData* cGameNounManager::FUN_00b25c30()
{
    tGameDataVector* pVector = GetGameDataVector((tVectorCreateFn)0x00cd7d10, (tVectorClearFn)0x00d3d420,
                                                 (tVectorAddFn)0x00acdff0, (tVectorMatchFn)0x00b1e500,
                                                 0x018c43e8);
    uint32_t count = (uint32_t)(pVector->mpEnd - pVector->mpBegin);
    for (uint32_t i = 0; i < count; ++i) {
        if (pVector->mpBegin[i]->mLocation.IsActive())
            return pVector->mpBegin[i];
    }
    return 0;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00b25cd0  one-time registration of the noun classes and their class-set registries
// ---------------------------------------------------------------------------------------------
void FUN_00b25cd0()
{
    GetStaticObj()->RegisterNounClasses();
    GetStaticObj()->FUN_00692850();
    RegisterDramaEventsFactories();
    InitClassRegistry(&g_classRegistry0, 1, 0x0145ea00, FUN_013c2030);
    FUN_00b23c60(0x01186577, "cSpatialObject");
    FUN_00b23c60(0xef3da0d7, "cCreatureTribeMember");
    FUN_00b23c60(0x0e9cb8ba, "cBuilding");
    FUN_00b23c60(0xce9f6639, "cCreatureBase");
    FUN_00b23c60(0x013f94d4, "cCombatant");
    InitClassRegistry(&g_classRegistry1, 2, 0x0145ea48, FUN_013c2020);
    InitClassRegistry(&g_classRegistry2, 4, 0x0145ea80, FUN_013c2010);
    InitClassRegistry(&g_classRegistry3, 8, 0x0145eac8, FUN_013c2000);
}

// ---------------------------------------------------------------------------------------------
// @ 0x00b25e80  constructor of the messaging sub-object embedded at cGameNounManager+0x04
// ---------------------------------------------------------------------------------------------
class cMessagingListener {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08();
    virtual void AddHandler(void* pOwner, uint32_t eventID);     // +0x24
};

class cNounManagerMessaging {
public:
    cGameNounManager* Owner()
    {
        return (cGameNounManager*)((char*)this - 4);
    }
    void FUN_00b25e80();
    uint32_t mPad00[(0x3c - 0x00) / 4];  // +0x00
    void*    mpMessageServer;            // +0x3c
    void*    mpOwner;                    // +0x40
    const uint32_t* mpEventNames;        // +0x44 (0x0145f82c, three ids)
    uint32_t mEventCount;                // +0x48
    uint32_t mPad4c;                     // +0x4c
};

void cNounManagerMessaging::FUN_00b25e80()
{
    FUN_00b25cd0();
    Owner()->FUN_00b215a0();
    mpMessageServer = EA_Messaging_GetServer();
    mpOwner = Owner();
    mpEventNames = g_timelineEvents;
    mEventCount = 3;
    mPad4c = 0;
    if (mpMessageServer != 0 && mpOwner != 0) {
        for (uint32_t i = 0; i < 3; ++i)
            ((cMessagingListener*)mpMessageServer)->AddHandler(mpOwner, mpEventNames[i]);
    }
}

// ---------------------------------------------------------------------------------------------
// @ 0x00b25ee0  force-release every noun of one key set (their storage is reclaimed elsewhere)
// ---------------------------------------------------------------------------------------------
void cGameNounManager::FUN_00b25ee0()
{
    tGameDataVector* pVector = GetGameDataVector((tVectorCreateFn)0x00b21080, (tVectorClearFn)0x00d3d420,
                                                 (tVectorAddFn)0x00b236c0, (tVectorMatchFn)0x00b1e500,
                                                 0x018c816a);
    int count = (int)(pVector->mpEnd - pVector->mpBegin);
    for (int i = 0; i < count; ++i) {
        FUN_00b21410(pVector->mpBegin[i]);
        RemoveNoun(pVector->mpBegin[i]);
    }
}

// ---------------------------------------------------------------------------------------------
// @ 0x00b25f40  noun owning a political id (cities and civilizations both answer this)
// ---------------------------------------------------------------------------------------------
cGameData* cGameNounManager::FindNounByEmpireID(uint32_t civID)
{
    tGameDataVector* pVector = GetGameDataVector((tVectorCreateFn)0x00b21080, (tVectorClearFn)0x00d3d420,
                                                 (tVectorAddFn)0x00b236c0, (tVectorMatchFn)0x00b1e500,
                                                 0x018c816a);
    int count = (int)(pVector->mpEnd - pVector->mpBegin);
    for (int i = 0; i < count; ++i) {
        cGameData* pNoun = pVector->mpBegin[i];
        if (pNoun->GetPoliticalID() == civID)
            return pVector->mpBegin[i];
    }
    return 0;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00b25fb0  civilization of the local player, `this` when there is no player empire yet
// ---------------------------------------------------------------------------------------------
class cCivilization;
class cCity;

class cCivilizationBase {
public:
    int    GetCityCount();                                       // 0x00bf01e0
    cCity* GetCityNearestTo(const cSPVector3& position, int a);  // 0x00befee0
};

class cCivilization : public cCivilizationBase {
public:
    bool CanReach(const cSPVector3& position);                   // 0x00bd9c00
};

class cCity {
public:
    bool CanReach(const cSPVector3& position);                   // 0x00bd9c00
};

cCivilization* cGameNounManager::GetPlayerCivilization()
{
    cCivilization* pCiv = (cCivilization*)this;
    cEmpire* pEmpire = GetPlayerEmpire();
    if (pEmpire != 0)
        return (cCivilization*)FindNounByEmpireID(pEmpire->mCivilizationID);
    return pCiv;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00b25fe0  tear down the planetary-context nouns that are not in a playable state
// ---------------------------------------------------------------------------------------------
class cGroundEditor {
public:
    void* GetContainer();                                        // 0x00ac79d0
    void  DrainNouns(void* pContainer);                          // 0x00ac7a40
};

class cGroundEditorSource {
public:
    cGroundEditor* GetEditor();                                  // 0x00b3d2b0
};

cGroundEditorSource* FUN_00b3d2b0();                             // 0x00b3d2b0

void cGameNounManager::FUN_00b25fe0()
{
    ProcessPending();
    RemoveNounsOfType(0x018eb45e);
    RemoveNounsOfType(0x2c9cc91);
    RemoveNounsOfType(0x2e96892);
    RemoveNounsOfType(0x018c84a9);
    RemoveNounsOfType(0x1be418e);
    mAvatarHerd.Reset();
    RemoveNounsOfType(0x2a8fb3f);
    RemoveNounsOfType(0x2a034cd);
    RemoveNounsOfType(0x018c6de8);
    RemoveNounsOfType(0x018c88e4);
    RemoveNounsOfType(0x3a2511e);
    RemoveNounsOfType(0x403df5c);
    RemoveNounsOfType(0x61494be);
    RemoveNounsOfType(0x629bafe);
    FUN_00b3d2b0()->GetEditor()->DrainNouns(FUN_00b3d2b0()->GetEditor()->GetContainer());

    tGameDataVector* pVector = GetGameDataVector((tVectorCreateFn)0x00cd7d10, (tVectorClearFn)0x00d3d420,
                                                 (tVectorAddFn)0x00ad48b0, (tVectorMatchFn)0x00b1e500,
                                                 0x018ebadc);
    tNounVector local;
    local.mpBegin = pVector->mpBegin;
    local.mpEnd = pVector->mpEnd;
    local.mpCapacity = pVector->mpEnd;
    local.mPad0c = 0;
    local.mPad10 = 0;
    for (cGameData** pp = local.mpBegin; pp != local.mpEnd; ++pp) {
        int32_t state = (*pp)->mObjectState;
        if (state != 0 && state != 8 && state != 3)
            FUN_0102c340(*pp, 0);
    }
    RemoveNounsOfType(0x2dd8c42);
    RemoveNounsOfType(0x4e3fab5);
    RemoveNounsOfType(0x018c6d19);
    RemoveNounsOfType(0x24270c9);
    RemoveNounsOfType(0x018c43e8);
    RemoveNounsOfType(0x018eb4b7);
    FUN_00b25ee0();
}

// ---------------------------------------------------------------------------------------------
// @ 0x00b262c0  player city nearest to a position, if it can reach it
// ---------------------------------------------------------------------------------------------
cCity* cGameNounManager::GetPlayerCityAtPosition(const cSPVector3& position)
{
    // the inlined GetPlayerCivilization body; with no player empire yet the position argument's
    // slot is what the standalone function returns as `this`, and that is what the original keeps
    cCivilization* pCiv;
    cEmpire* pEmpire = GetPlayerEmpire();
    if (pEmpire != 0)
        pCiv = (cCivilization*)FindNounByEmpireID(pEmpire->mCivilizationID);
    else
        pCiv = (cCivilization*)&position;
    if (pCiv != 0) {
        if (pCiv->GetCityCount() > 0) {
            cCity* pCity = pCiv->GetCityNearestTo(position, 0);
            if (pCity != 0) {
                if (pCity->CanReach(position))
                    return pCity;
            }
        }
    }
    return 0;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00b26320  full reset of the manager (leaving the game)
// ---------------------------------------------------------------------------------------------
class cMessageServer {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04();
    virtual void Send(uint32_t eventID, void* pMessage, int a);  // +0x14
};

class cMessageServer4 {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05();
    virtual void Send(uint32_t eventID, void* pMessage, int a, int b); // +0x18
};

cMessageServer* MessageServer();                                 // 0x0067dcc0
cMessageServer4* MessageServer4();                               // 0x0067dcc0

void cGameNounManager::FUN_00b26320()
{
    if (mpPlayer.mpObject != 0) {
        RemoveNoun((cGameData*)mpPlayer.mpObject);
        ProcessPending();
        mpPlayer.Reset();
    }
    FUN_00b25fe0();
    Flush();
    mGameDataVectorMap.mTree.swap(mGameDataVectorMapDeleted.mTree);
    ValidateClassSets();
    mPlanetaryContextPoliticalMap.mTree.clear();
    mAvatar.Reset();
    mAvatarHerd.Reset();
    for (cGameData** pp = mPosseMembers.mpBegin; pp != mPosseMembers.mpEnd; ++pp)
        (*pp)->ClearPosseMemberFlag();                       // clears bit 0x100 at +0xb58
    mPosseMembers.mpEnd = mPosseMembers.mpBegin;
    mPlayerTribe.Reset();
    mpPlayer.Reset();
    Flush();
    mGameDataVectorMap.mTree.swap(mGameDataVectorMapDeleted.mTree);
    Flush();
    mGameDataVectorMap.mTree.swap(mGameDataVectorMapDeleted.mTree);
}

// ---------------------------------------------------------------------------------------------
// @ 0x00b26600  clear the player-facing noun slots and both game-data vector maps
// ---------------------------------------------------------------------------------------------
void cGameNounManager::FUN_00b26600()
{
    FUN_00b25fe0();
    if (mpPlayer.mpObject != 0) {
        RemoveNoun((cGameData*)mpPlayer.mpObject);
        ProcessPending();
        if (mpPlayer.mpObject != 0) {
            cRefCounted* pOld = mpPlayer.mpObject;
            mpPlayer.mpObject = 0;
            pOld->Release();
        }
    }
    mPlanetaryContextPoliticalMap.mTree.clear();
    mAvatar.Reset();
    mAvatarHerd.Reset();
    ClearPosseMembers();
    mPlayerTribe.Reset();
    mpPlayer.Reset();
    Flush();
    mGameDataVectorMap.mTree.swap(mGameDataVectorMapDeleted.mTree);
    Flush();
    mGameDataVectorMap.mTree.swap(mGameDataVectorMapDeleted.mTree);
    RemoveNounsOfType(0x3ed8573);
    RemoveNounsOfType(0x2e72cae);
    RemoveNounsOfType(0x32f9778);
}

// ---------------------------------------------------------------------------------------------
// cSPUITimeline (the story/timeline subsystem object)
// ---------------------------------------------------------------------------------------------
class cListenerBase {
public:
    virtual ~cListenerBase() {}
};

class cIGonzagoSubsystem {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
    virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
    virtual void v10(); virtual void v11(); virtual void v12();
};

class cRefCountTemplate {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
};

class cGonzagoSubsystem : public cIGonzagoSubsystem, public cRefCountTemplate {
public:
    cGonzagoSubsystem();                                         // 0x00b5b960
    ~cGonzagoSubsystem();                                        // 0x00b5b9a0
    uint32_t mPad0c[5];                                          // +0x0c
};

class cSPUITimeline : public cListenerBase, public cGonzagoSubsystem {
public:
    cSPUITimeline();                                             // 0x00b26e10
    ~cSPUITimeline();                                            // 0x00b26ec0
    void FUN_00b26790();                                         // 0x00b26790
    void leave_game(int a, int b);                               // 0x00b26af0
    void OnModalWindowStart(int a);                              // 0x00b26c90
    tUIHandler mHandler;                                         // +0x20
    cWString   mTimeline;                                        // +0x34
    bool       mFlag44;                                          // +0x44
    bool       mFlag45;                                          // +0x45
    bool       mQuitWhenLeaving;                                 // +0x46
    bool       mFlag47;                                          // +0x47
    tAutoRefCount mModalWindow;                                  // +0x48
};

class cStarManager {
public:
    bool CanLeaveTimeline();                                     // 0x00baad00
};

cStarManager* StarManager();                                     // 0x00b3d2a0
void __cdecl UI_CalloutMessageBox(const wchar_t* pTitle, const wchar_t* pMessage); // 0x00809db0

// ---------------------------------------------------------------------------------------------
// @ 0x00b26710  enter the timeline mode and switch the app mode argument
// ---------------------------------------------------------------------------------------------
class cModeOwner {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void SetModeArgument(void* pArgument);                // +0x10
};

class cTimelineModeStarter {
public:
    cModeOwner* mpModeOwner;                                     // +0x00
    void FUN_00b26710();
};

void cTimelineModeStarter::FUN_00b26710()
{
    mpModeOwner->SetModeArgument(&g_modeArg);
    g_uiModeToken = 6;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00b26790  warn the player when the timeline cannot be left yet
// ---------------------------------------------------------------------------------------------
void cSPUITimeline::FUN_00b26790()
{
    if (!StarManager()->CanLeaveTimeline()) {
        mQuitWhenLeaving = true;
        UI_CalloutMessageBox(g_leaveGameTitle, g_leaveGameMessage);
    }
}

// ---------------------------------------------------------------------------------------------
// @ 0x00b269d0  copy the current UI mode byte into a writable string object
// ---------------------------------------------------------------------------------------------
struct cUIString {
    void* apSlots[8];                                            // +0x00 .. +0x1c
    char* (__cdecl* mpGetBuffer)(void* pSelf);                    // +0x20
};

void FUN_00b269d0(cUIString* pString)
{
    *pString->mpGetBuffer(pString) = g_uiModeByte;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00b269f0  forward a one-argument request to the active viewer, if any
// ---------------------------------------------------------------------------------------------
class cViewerRequest {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04();
    virtual void Request(int a);                                 // +0x14
};

cViewerRequest* FUN_00b3d340();                                  // 0x00b3d340

void __stdcall FUN_00b269f0(int a)
{
    cViewerRequest* pViewer = FUN_00b3d340();
    if (pViewer != 0)
        return pViewer->Request(a);
}

// ---------------------------------------------------------------------------------------------
// @ 0x00b26a10  start/stop the frame timer around a mode change
// ---------------------------------------------------------------------------------------------
class cTimerViewer {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05();
    virtual void SetPaused(int a, int b);                        // +0x18
};

class cFrameTimerOwner {
public:
    uint32_t mPad00;                                             // +0x00 (vptr)
    bool     mTimingEnabled;                                     // +0x04
    void FUN_00b26a10(int a, int b);
};

extern "C" unsigned __int64 __rdtsc(void);
#pragma intrinsic(__rdtsc)

extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(__int64* pCounter); // 0x13cc2b8

void cFrameTimerOwner::FUN_00b26a10(int a, int b)
{
    cTimerViewer* pViewer = (cTimerViewer*)FUN_00b3d340();
    if (pViewer != 0)
        pViewer->SetPaused(a, b);
    if (mTimingEnabled) {
        uint64_t now;
        if (g_timeSource == 1)
            now = __rdtsc();
        else
            QueryPerformanceCounter((__int64*)&now);
        g_timerStartLow = (uint32_t)now;
        g_timerStartHigh = (uint32_t)(now >> 32);
        g_timerElapsedLow = 0;
        g_timerElapsedHigh = 0;
        MessageServer4()->Send(0x685dbfa, 0, 0, 0);
    }
}

// ---------------------------------------------------------------------------------------------
// @ 0x00b26af0  leave the timeline: drop the modal window, resume time, quit if requested
// ---------------------------------------------------------------------------------------------
class cGameTimeManager {
public:
    void DecPauseGate(uint32_t gate);                            // 0x00b32250
    void IncPauseGate(uint32_t gate);                            // 0x00b32220
};

cGameTimeManager* GameTimeManager();                             // 0x00b3d380

class cCheatManager {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void Execute(const char* pCommand);                  // +0x20
};

cCheatManager* CheatManager();                                   // 0x0067de20

void cSPUITimeline::leave_game(int a, int b)
{
    if (mModalWindow.mpObject != 0) {
        mModalWindow.mpObject->Dismiss(0);
        if (mModalWindow.mpObject != 0) {
            cRefCounted* pOld = mModalWindow.mpObject;
            mModalWindow.mpObject = 0;
            pOld->Release();
        }
    }
    GameTimeManager()->DecPauseGate(0x4bf38a9);
    MessageServer()->Send(0x67df712, 0, 0);
    if (mQuitWhenLeaving)
        CheatManager()->Execute(g_quitCommand);
}

// ---------------------------------------------------------------------------------------------
// @ 0x00b26c20  serialize the timeline field block
// ---------------------------------------------------------------------------------------------
class cOutStream {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void* GetObject();                                   // +0x20
};

class cIOStream {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05();
    virtual cIOStream* GetWriteStream();                         // +0x18
};

extern "C" bool __cdecl EA_IO_WriteUint32(cIOStream* pStream, const uint32_t* pValue, int count,
                                          int a);                                        // 0x0093aa70

class cVarListSerializer {
public:
    cVarListSerializer(void* pOwner, const char* pFieldName, int line);  // 0x00692f90
    bool Serialize(cOutStream* pStream);                                 // 0x00692900
    uint32_t mPad00[(0xa14 - 0x00) / 4];                                 // +0x00
};

class cTimelineSerializer {
public:
    void FUN_00b26c20(cOutStream* pStream);
};

void cTimelineSerializer::FUN_00b26c20(cOutStream* pStream)
{
    uint32_t version = 0x12326f66;
    cIOStream* pWriteStream = ((cIOStream*)pStream->GetObject())->GetWriteStream();
    EA_IO_WriteUint32(pWriteStream, &version, 1, 0);
    cVarListSerializer serializer((char*)this - 8, g_serializedFieldName, 0x1a80d26);
    serializer.Serialize(pStream);
}

// ---------------------------------------------------------------------------------------------
// @ 0x00b26c90  pause the game while a modal window owns the timeline
// ---------------------------------------------------------------------------------------------
class cEffectCallback {
public:
    virtual void v00(); virtual void v01();
    virtual bool Bind(uint32_t id, int a, tAutoRefCount* pOut);   // +0x08
};

class cEffectsManager {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
    virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14();
    virtual cEffectCallback* GetEffect(uint32_t effectID);        // +0x54
};

cEffectsManager* EffectsManagerPtr();                            // 0x0067ddd0

void cSPUITimeline::OnModalWindowStart(int a)
{
    cEffectCallback* pEffect = EffectsManagerPtr()->GetEffect(0xeb9968);
    if (pEffect != 0) {
        mModalWindow.Reset();
        if (pEffect->Bind(0x4c4ba0a9, 0, &mModalWindow))
            mModalWindow.mpObject->Activate(0);
    }
    GameTimeManager()->IncPauseGate(0x4bf38a9);
}

// ---------------------------------------------------------------------------------------------
// @ 0x00b26d00  constructor of the three-string UI configuration block
// ---------------------------------------------------------------------------------------------
class cSPUIStringConfig {
public:
    cSPUIStringConfig();
    ~cSPUIStringConfig();                                        // 0x00b26db0
    cWString mStr00;                                            // +0x00
    cWString mStr10;                                            // +0x10
    cWString mStr20;                                            // +0x20
    uint32_t mZero30[20];                                       // +0x30 (fields cleared to zero)
    uint32_t mPad80[3];                                         // +0x80
    uint32_t mAllocatorType;                                    // +0x8c (= 4)
    uint32_t mZero90;                                           // +0x90
    uint32_t mPad94[3];                                         // +0x94
    uint32_t mZeroA0;                                           // +0xa0
    uint32_t mZeroA4;                                           // +0xa4
    uint32_t mZeroA8;                                           // +0xa8
    uint8_t  mFlagAc;                                           // +0xac
    uint8_t  mFlagAd;                                           // +0xad
    uint8_t  mPadAe[2];                                         // +0xae
    uint32_t mZeroB0;                                           // +0xb0
    uint32_t mZeroB4;                                           // +0xb4
    uint32_t mZeroB8;                                           // +0xb8
};

cSPUIStringConfig::cSPUIStringConfig()
{
    for (int i = 0; i < 20; ++i)
        mZero30[i] = 0;
    mAllocatorType = 4;
    mZero90 = 0;
    mZeroA0 = 0;
    mZeroA4 = 0;
    mZeroA8 = 0;
    mFlagAc = 0;
    mFlagAd = 0;
    mZeroB0 = 0;
    mZeroB4 = 0;
    mZeroB8 = 0;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00b26db0  destructor of the three-string UI configuration block
// ---------------------------------------------------------------------------------------------
cSPUIStringConfig::~cSPUIStringConfig()
{
}

// ---------------------------------------------------------------------------------------------
// @ 0x00b26e10  cSPUITimeline constructor
// ---------------------------------------------------------------------------------------------
cSPUITimeline::cSPUITimeline()
    : mFlag44(false), mFlag45(false), mQuitWhenLeaving(false), mFlag47(false)
{
    mModalWindow.mpObject = 0;
    g_uiModeToken = 6;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00b26ec0  cSPUITimeline destructor
// ---------------------------------------------------------------------------------------------
cSPUITimeline::~cSPUITimeline()
{
}

// ---------------------------------------------------------------------------------------------
// @ 0x00b26f40  COM factory for the deprecated herd-effects simulator
// ---------------------------------------------------------------------------------------------
class cISerializableObject {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    uint32_t mPad04;                                             // +0x04
};

class cGonzagoSimulator {
public:
    cGonzagoSimulator();                                         // 0x00b5b6c0
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    uint32_t mPad04;                                             // +0x04
};

class cHerdEffects : public cGonzagoSimulator {
public:
    cISerializableObject mSerializable;                          // +0x08
};

inline void* operator new(size_t size, const char* pName, int flags, int debugFlags,
                          const char* pFile, int line)
{
    return FUN_00f473a0(size, pName, flags, debugFlags, pFile, line);
}

cISerializableObject* __stdcall FUN_00b26f40(int a, int b)
{
    cHerdEffects* pHerd = new (g_herdEffectsFactoryName, 0, 0, 0, 0) cHerdEffects;
    if (pHerd != 0)
        return &pHerd->mSerializable;
    return 0;
}
