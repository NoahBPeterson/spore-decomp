// Recovered from SporeApp.exe (retail).
// Batch gold6 / worker 36 / slice s010377f0.
//
// Space stage trade routes: the space-gfx update entry point, the trade route
// data blob with its serializer list, and cSpaceTradeRouteManager with its
// eastl::rbtree keyed by (system, system) and holding cTradeRouteData.
//
// The route tree lives at manager + 4; its anchor node sits at manager + 8 and
// its root at manager + 0x10. A tree node is a 0x10 byte rbtree base followed
// by the pair key at +0x10 and the route data at +0x18.

typedef unsigned int size_t;
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef int int32_t;

struct Vec3 {
    float mX;
    float mY;
    float mZ;
};

inline void* operator new(size_t, void* pMemory) {
    return pMemory;
}

// ---------------------------------------------------------------------------
// Foreign objects
// ---------------------------------------------------------------------------

class cTerrainSphere {
public:
    void* mpVtable;                                             // 0x00
    void Reset();                                               // slot 0x0c
    void GenerateImpostor(uint32_t nModelId);                   // 0x00fa1650
};

class cTerrainEditor {
public:
    cTerrainSphere* GetCurrentTerrainSphere();                  // 0x00f67d90
};

class cCivData {
public:
    const Vec3* GetCities();                                    // 0x005c65e0
};

class cStarManager {
public:
    cCivData* GetCivData();                                     // 0x00ba6d80
};

class cGonzagoSubsystem {
public:
    void Construct();                                           // 0x00b5b960
};

class cSpaceTimerOwner {
public:
    void AddTimer(const void* pTimerId, const void* pEventId,
                  float fDelay, int nFlags);                    // 0x00a6c9f0
};

class cPlanetSubsystem {
public:
    cSpaceTimerOwner* GetTimerOwner();                          // 0x008414c0
};

class cTradeRouteData;

class cTimerOwner {
public:
    void* Construct();                                          // 0x00af14b0
};

// The stream handle handed to Write / Read; slot 0x20 yields the interface
// whose slot 0x18 yields the raw EA::IO stream.
class cStreamHandle {
public:
    void* mpVtable;                                             // 0x00
    void* GetStreamInterface() {
        return ((void* (__thiscall*)(cStreamHandle*))((void**)mpVtable)[0x20 / 4])(this);
    }
};

class cStreamInterface {
public:
    void* mpVtable;                                             // 0x00
    void* GetRawStream() {
        return ((void* (__thiscall*)(cStreamInterface*))((void**)mpVtable)[0x18 / 4])(this);
    }
};

// The reflective serializer list walker (0xa14 bytes on the stack).
class cVarListSerializer {
public:
    cVarListSerializer(const void* pObject, const void* pList, int nVersion);   // 0x00692f90
    bool SerializeOut(cStreamHandle* pStream);                  // 0x00692900
    bool SerializeIn(cStreamHandle* pStream);                   // 0x00693e10

    void* mpVtable;                                             // 0x000
    uint8_t mPad004[0xa10];                                     // 0x004
};

// ---------------------------------------------------------------------------
// Foreign free functions and globals
// ---------------------------------------------------------------------------

int cSPLivingUniverse_GetUniverseContext();                     // 0x01021080
void* cSPLivingUniverse_GetActivePlanet();                      // 0x01021260
uint32_t cSPLivingUniverse_GetPlayerEmpireID();                 // 0x01021090
cTerrainEditor* SP_TerrainEditor();                             // 0x00f48a70
void SpaceGfx_UpdateAudio0();                                   // 0x00c2e4e0
void SpaceGfx_UpdateAudioN(int nMode, uint32_t nA, uint32_t nB); // 0x00c2e4e0
void SpaceGfx_UpdateGroup1();                                   // 0x01036af0
void SpaceGfx_UpdateGroup2();                                   // 0x01037760
void SpaceGfx_UpdateGroup3(void* pThis, int nArg);              // 0x01034d40

cStarManager* StarManager(uint32_t nSystem);                    // 0x00b3d2a0

void EA_IO_WriteUint32(void* pStream, const uint32_t* pValue,
                       int nCount, int nFlags);                 // 0x0093aa70
void EA_IO_ReadInt32(void* pStream, uint32_t* pValue,
                     int nCount, int nFlags);                   // 0x0093a780

struct cSerializerList {
    uint32_t mnVersion;                                         // 0x00
};

class cSerializerContext {
public:
    void Serialize(cTradeRouteData* pData, const cSerializerList* pList,
                   const wchar_t* pName);                       // 0x00695b40
};

void* cRouteNode_Alloc(size_t nSize, const char* pName, int nA, int nB,
                       const char* pFile, int nLine);           // 0x00f473a0
void cRouteNode_Free(void* pMemory);                            // 0x00f47380

void RBTreeInsertNode(void* pNew, void* pParent, void* pAnchor,
                      uint8_t bSide);                           // 0x009216a0
void RBTreeEraseNode(void* pNode, void* pAnchor);               // 0x00921880

extern float gSpaceFadeDelay;           // 0x0149996c
extern float gCityRadius;               // 0x015b7d08
extern float gMinusOne;                 // 0x013eb1bc
extern float gFullProgress;             // 0x013ec4d0
extern cSerializerList gTradeRouteSerializerList;       // 0x015b7dc0
extern cSerializerList gRouteManagerSerializerList;     // 0x015b7fe0
extern const void* gImpostorTimer;      // 0x015b77b4
extern const void* gSpaceGfxTimerId;    // 0x016df344
extern uint8_t gSpaceAudioEnabled0;     // 0x016e06de
extern uint8_t gSpaceAudioEnabled1;     // 0x016e06e1
extern uint8_t gSpaceAudioEnabled2;     // 0x016e06e2
extern uint8_t gSpaceAudioEnabled3;     // 0x016e06e3
extern uint32_t gSpaceAudioParam0;      // 0x016e06e4
extern uint32_t gSpaceAudioParam1;      // 0x016e06e8

// ---------------------------------------------------------------------------
// Trade route data
// ---------------------------------------------------------------------------

class cTradeRouteData {
public:
    bool Write(cStreamHandle* pStream);                         // 0x01037ae0
    bool Read(cStreamHandle* pStream);                          // 0x01037b50

    void* mpVtable;                     // 0x00
    uint32_t mnEmpireA;                 // 0x04
    uint32_t mnEmpireB;                 // 0x08
    uint32_t mnSystemA;                 // 0x0c
    uint32_t mnSystemB;                 // 0x10
    float mfProgress;                   // 0x14
    uint8_t mbReachable;                // 0x18
    uint8_t mPad019[0x03];              // 0x19
    uint32_t mnFlags1c;                 // 0x1c
    uint32_t mnFlags20;                 // 0x20
    float mfTiming24;                   // 0x24
    uint32_t mnUnk28;                   // 0x28
};

// The pair stored in each node: key at +0, data at +8.
class cTradeRoutePair {
public:
    cTradeRoutePair(const cTradeRoutePair& src);                // 0x01037a60

    uint32_t mnKeyA;                    // 0x00
    uint32_t mnKeyB;                    // 0x04
    cTradeRouteData mData;              // 0x08
};

// ---------------------------------------------------------------------------
// rbtree nodes
// ---------------------------------------------------------------------------

struct cRBNodeBase {
    cRBNodeBase* mpNodeRight;           // 0x00
    cRBNodeBase* mpNodeLeft;            // 0x04
    cRBNodeBase* mpNodeParent;          // 0x08
    uint8_t mColor;                     // 0x0c
    uint8_t mPad00d[0x03];              // 0x0d
};

// A node is an rbtree base followed by the stored pair (key at +0x10, data at
// +0x18); the pair base sits at node + 0x10.
struct cRouteNode : cRBNodeBase, cTradeRoutePair {
};

cRBNodeBase* eastl_RBTreeIncrement(cRBNodeBase* pNode);         // 0x00921580
cRBNodeBase* eastl_RBTreeDecrement(cRBNodeBase* pNode);         // 0x009215c0

class cTradeRouteTree {
public:
    void erase(cRBNodeBase* pNode);                             // 0x010380b0
    void InsertNode(cRouteNode** ppOut, cRBNodeBase* pParent,
                    const cTradeRoutePair* pValue, uint8_t bSide);   // 0x010380f0
    cRouteNode** DoInsertValue(cRouteNode** ppOut, const cTradeRoutePair* pValue,
                               int nUnused);                    // 0x01038180

    uint8_t mPad000[0x04];              // 0x00
    cRBNodeBase mAnchor;                // 0x04
    uint32_t mnSize;                    // 0x14
};

// The manager owning the route tree.
class cSpaceTradeRouteManager {
public:
    bool Write(cStreamHandle* pStream);                         // 0x01037bc0
    bool Read(cStreamHandle* pStream);                          // 0x01038270
    bool HasTradeRouteWithPlayer(uint32_t nSystem);             // 0x01037d90
    bool IsTradeRouteBetween(uint32_t nSystem, uint32_t nEmpire);   // 0x01037d30
    float SystemHasTradeRouteWithPlayer(uint32_t nSystem, uint32_t nEmpire);   // 0x01037dd0
    void GetPlayerProgressOnTradeRoute(uint32_t nSystem, uint32_t nEmpire);    // 0x01037e40
    void ResetPlayerProgressOnTradeRoute(uint32_t nSystem, uint32_t nEmpire,
                                         float fProgress);      // 0x01037eb0
    int GetNumberOfPlayerTradeRoutes();                         // 0x01037f20
    cCivData* GetPlayerTradeRouteTarget();                      // 0x01037f60
    int RemoveTradeRoute(void* pSystem);                        // 0x01038300
    bool RemoveAllTradeRoutesFromSystem(void* pSystem);         // 0x010383a0
    void Destroy();                                             // 0x01038250

    void* mpVtable;                     // 0x00
    cTradeRouteTree mRoutes;            // 0x04
    uint32_t mnUnk1c;                   // 0x1c
    uint32_t mnLastStarID;              // 0x20
};

// ---------------------------------------------------------------------------
// The space gfx object driving the per-frame update
// ---------------------------------------------------------------------------

struct cIntrusiveLink {
    void* mp0;                          // 0x00
    void* mp4;                          // 0x04
    void* mp8;                          // 0x08
    void* mpc;                          // 0x0c
};

class cSPSpaceGfx : public cGonzagoSubsystem {
public:
    cSPSpaceGfx();
    void UpdateForSpaceGame(int nArg);                          // 0x010377f0

    void* mpVtable;                     // 0x000
    void* mpVtable2;                    // 0x004
    uint8_t mPad008[0x14];              // 0x008
    uint32_t mUnk1c;                    // 0x01c
    uint32_t mUnk20;                    // 0x020
    uint32_t mUnk24;                    // 0x024
    uint32_t mUnk28;                    // 0x028
    uint32_t mUnk2c;                    // 0x02c
    uint32_t mUnk30;                    // 0x030
    uint32_t mUnk34;                    // 0x034
    uint32_t mUnk38;                    // 0x038
    uint8_t mPad03c[0x04];              // 0x03c
    cIntrusiveLink mUnk40;              // 0x040
    uint32_t mUnk50;                    // 0x050
    uint8_t mPad054[0x04];              // 0x054
    uint8_t mUnk58;                     // 0x058
    uint8_t mUnk59;                     // 0x059
    uint8_t mPad05a[0x02];              // 0x05a
    uint32_t mUnk5c;                    // 0x05c
    uint32_t mUnk60;                    // 0x060
    uint32_t mUnk64;                    // 0x064
    uint32_t mUnk68;                    // 0x068
    uint32_t mUnk6c;                    // 0x06c
    uint32_t mUnk70;                    // 0x070
    uint32_t mUnk74;                    // 0x074
    uint32_t mUnk78;                    // 0x078
    uint32_t mUnk7c;                    // 0x07c
    uint32_t mUnk80;                    // 0x080
    uint32_t mUnk84;                    // 0x084
    uint32_t mUnk88;                    // 0x088
    uint32_t mUnk8c;                    // 0x08c
    uint32_t mUnk90;                    // 0x090
    uint32_t mUnk94;                    // 0x094
    uint32_t mUnk98;                    // 0x098
    uint32_t mUnk9c;                    // 0x09c
    uint32_t mUnkA0;                    // 0x0a0
    uint32_t mUnkA4;                    // 0x0a4
    uint32_t mUnkA8;                    // 0x0a8
    uint32_t mUnkAc;                    // 0x0ac
    uint32_t mUnkB0;                    // 0x0b0
    uint32_t mUnkB4;                    // 0x0b4
    uint32_t mUnkB8;                    // 0x0b8
    uint32_t mUnkBC;                    // 0x0bc
    uint32_t mUnkC0;                    // 0x0c0
    uint32_t mUnkC4;                    // 0x0c4
    cTimerOwner mTimer;                 // 0x0c8
    uint8_t mUnk100;                    // 0x100
    uint8_t mPad101[0x3b];              // 0x101
    uint32_t mUnk13c;                   // 0x13c
};

// ---------------------------------------------------------------------------
// 0x010377f0  cSPSpaceGfx::UpdateForSpaceGame
// ---------------------------------------------------------------------------
// @ 0x010377f0
void cSPSpaceGfx::UpdateForSpaceGame(int nArg)
{
    int nContext = cSPLivingUniverse_GetUniverseContext();
    if (nContext == 1)
        SpaceGfx_UpdateGroup1();
    else if (nContext == 2) {
        SpaceGfx_UpdateGroup2();
        SpaceGfx_UpdateGroup3(this, nArg);
    }

    if (gSpaceAudioEnabled0 != 0) {
        if (cSPLivingUniverse_GetUniverseContext() == 0) {
            cPlanetSubsystem* pPlanet = (cPlanetSubsystem*)cSPLivingUniverse_GetActivePlanet();
            if (pPlanet == 0)
                return;
            cSpaceTimerOwner* pTimerOwner = pPlanet->GetTimerOwner();
            if (pTimerOwner == 0)
                return;
            pTimerOwner->AddTimer(gSpaceGfxTimerId, gImpostorTimer, gSpaceFadeDelay, 0);
        }
    }

    if (gSpaceAudioEnabled1 != 0) {
        if (cSPLivingUniverse_GetUniverseContext() == 0)
            SpaceGfx_UpdateAudio0();
    }
    if (gSpaceAudioEnabled2 != 0) {
        if (cSPLivingUniverse_GetUniverseContext() == 0)
            SpaceGfx_UpdateAudioN(1, gSpaceAudioParam0, gSpaceAudioParam1);
    }
    if (gSpaceAudioEnabled3 != 0) {
        if (cSPLivingUniverse_GetUniverseContext() == 0)
            SpaceGfx_UpdateAudioN(0, gSpaceAudioParam0, gSpaceAudioParam1);
    }

    ((void (__thiscall*)(void*, int))((void**)*(void**)((char*)&mTimer))[0x04 / 4])(&mTimer, 0);
}

// ---------------------------------------------------------------------------
// 0x010378f0  cSPSpaceGfx::cSPSpaceGfx
// ---------------------------------------------------------------------------
// @ 0x010378f0
cSPSpaceGfx::cSPSpaceGfx()
{
    Construct();

    mpVtable = (void*)0x1499908;
    mpVtable2 = (void*)0x1499900;

    mUnk1c = 0;
    mUnk20 = 0;
    mUnk24 = 0;
    mUnk28 = 0;
    mUnk2c = 0;
    mUnk30 = 0;
    mUnk34 = 0;
    mUnk38 = 0;

    mUnk40.mp4 = 0;
    mUnk40.mp8 = 0;
    mUnk40.mpc = 0;
    mUnk40.mp0 = &mUnk40;
    mUnk40.mp4 = &mUnk40;

    mUnk50 = 0;
    mUnk58 = 0;
    mUnk59 = 0;
    mUnk5c = 1;
    mUnk60 = 0;
    mUnk64 = 0;
    mUnk68 = 0;
    mUnk6c = 0;
    mUnk70 = 0;
    mUnk74 = 0;
    mUnk78 = 0;
    mUnk7c = 0;
    mUnk80 = 0;
    mUnk84 = 0;
    mUnk88 = 0;
    mUnk8c = 0;
    mUnk90 = 0;
    mUnk94 = 0;
    mUnk98 = 0;
    mUnk9c = 0;
    mUnkA0 = 0;
    mUnkA4 = 0;
    mUnkA8 = 0;
    mUnkAc = 0;
    mUnkB0 = 0;
    mUnkB4 = 0;
    mUnkB8 = 0;
    mUnkBC = 0;
    mUnkC0 = 0;
    mUnkC4 = 0;

    mTimer.Construct();

    mUnk100 = 0;
    mUnk13c = 0;
}

// ---------------------------------------------------------------------------
// 0x01037a20  SP::CaptureImposterModel
// ---------------------------------------------------------------------------
// @ 0x01037a20
void SP_CaptureImposterModel(void* pPlanet)
{
    if (pPlanet == 0)
        pPlanet = cSPLivingUniverse_GetActivePlanet();
    cTerrainSphere* pSphere = SP_TerrainEditor()->GetCurrentTerrainSphere();
    if (pPlanet != 0 && pSphere != 0) {
        ((void (__thiscall*)(cTerrainSphere*))((void**)pSphere->mpVtable)[0x0c / 4])(pSphere);
        pSphere->GenerateImpostor(0x29ffa8d);
    }
}

// ---------------------------------------------------------------------------
// 0x01037a60  cTradeRoutePair::cTradeRoutePair
// ---------------------------------------------------------------------------
// @ 0x01037a60
cTradeRoutePair::cTradeRoutePair(const cTradeRoutePair& src)
{
    mnKeyA = src.mnKeyA;
    mnKeyB = src.mnKeyB;
    mData.mpVtable = (void*)0x1499a30;
    mData.mnEmpireA = src.mData.mnEmpireA;
    mData.mnEmpireB = src.mData.mnEmpireB;
    mData.mnSystemA = src.mData.mnSystemA;
    mData.mnSystemB = src.mData.mnSystemB;
    mData.mfProgress = src.mData.mfProgress;
    mData.mbReachable = src.mData.mbReachable;
    mData.mnFlags1c = src.mData.mnFlags1c;
    mData.mnFlags20 = src.mData.mnFlags20;
    mData.mfTiming24 = src.mData.mfTiming24;
    mData.mnUnk28 = src.mData.mnUnk28;
}

// ---------------------------------------------------------------------------
// 0x01037ae0  cTradeRouteData::Write
// ---------------------------------------------------------------------------
// @ 0x01037ae0
bool cTradeRouteData::Write(cStreamHandle* pStream)
{
    void* pRaw = ((cStreamInterface*)pStream->GetStreamInterface())->GetRawStream();
    uint32_t nVersion = 0x5527100;
    EA_IO_WriteUint32(pRaw, &nVersion, 1, 0);
    cVarListSerializer serializer(this, &gTradeRouteSerializerList, 0x1a80d26);
    return serializer.SerializeOut(pStream);
}

// ---------------------------------------------------------------------------
// 0x01037b50  cTradeRouteData::Read
// ---------------------------------------------------------------------------
// @ 0x01037b50
bool cTradeRouteData::Read(cStreamHandle* pStream)
{
    void* pRaw = ((cStreamInterface*)pStream->GetStreamInterface())->GetRawStream();
    uint32_t nVersion;
    EA_IO_ReadInt32(pRaw, &nVersion, 1, 0);
    cVarListSerializer serializer(this, &gTradeRouteSerializerList, 0x1a80d26);
    return serializer.SerializeIn(pStream);
}

// ---------------------------------------------------------------------------
// 0x01037bc0  cSpaceTradeRouteManager::Write
// ---------------------------------------------------------------------------
// @ 0x01037bc0
bool cSpaceTradeRouteManager::Write(cStreamHandle* pStream)
{
    void* pRaw = ((cStreamInterface*)pStream->GetStreamInterface())->GetRawStream();
    uint32_t nVersion = 0x5526a59;
    EA_IO_WriteUint32(pRaw, &nVersion, 1, 0);
    cVarListSerializer serializer(this, &gRouteManagerSerializerList, 0x1a80d26);
    return serializer.SerializeOut(pStream);
}

// ---------------------------------------------------------------------------
// 0x01037c30  trade route proximity test
// ---------------------------------------------------------------------------
// @ 0x01037c30
bool __stdcall TradeRoute_UpdateProximity(cTradeRouteData* pRoute, float fX, float fY, float fZ)
{
    cCivData* pCiv = StarManager(pRoute->mnSystemA)->GetCivData();
    if (pCiv != 0) {
        const Vec3* pCity = pCiv->GetCities();
        float fDX = pCity->mX - fX;
        float fDY = pCity->mY - fY;
        float fDZ = pCity->mZ - fZ;
        float fDistance = fDX * fDX + fDY * fDY + fDZ * fDZ;
        if (fDistance <= gCityRadius) {
            pRoute->mbReachable = 1;
            return true;
        }
    }

    pCiv = StarManager(pRoute->mnSystemB)->GetCivData();
    if (pCiv != 0) {
        const Vec3* pCity = pCiv->GetCities();
        float fDX = pCity->mX - fX;
        float fDY = pCity->mY - fY;
        float fDZ = pCity->mZ - fZ;
        float fDistance = fDX * fDX + fDY * fDY + fDZ * fDZ;
        if (fDistance <= gCityRadius) {
            pRoute->mbReachable = 1;
            return true;
        }
    }

    pRoute->mbReachable = 0;
    return false;
}

// ---------------------------------------------------------------------------
// 0x01037ce0  serialize every route of a tree
// ---------------------------------------------------------------------------
// @ 0x01037ce0
bool SP_SerializeTradeRouteList(void* pSerializer, cTradeRouteTree* pRoutes)
{
    cRBNodeBase* pNode = pRoutes->mAnchor.mpNodeLeft;
    cRBNodeBase* pEnd = &pRoutes->mAnchor;
    while (pNode != pEnd) {
        cRouteNode* pRoute = (cRouteNode*)pNode;
        if (&pRoute->mData != 0)
            ((cSerializerContext*)pSerializer)->Serialize(&pRoute->mData,
                                                           &gTradeRouteSerializerList,
                                                           L"cTradeRouteData");
        pNode = eastl_RBTreeIncrement(pNode);
    }
    return 1;
}

// ---------------------------------------------------------------------------
// 0x01037d30  cSpaceTradeRouteManager::IsTradeRouteBetween
// ---------------------------------------------------------------------------
// @ 0x01037d30
bool cSpaceTradeRouteManager::IsTradeRouteBetween(uint32_t nSystem, uint32_t nEmpire)
{
    uint32_t nPlayer = cSPLivingUniverse_GetPlayerEmpireID();
    cRBNodeBase* pEnd = &mRoutes.mAnchor;
    for (cRBNodeBase* pNode = mRoutes.mAnchor.mpNodeLeft; pNode != pEnd;
         pNode = eastl_RBTreeIncrement(pNode)) {
        cRouteNode* pRoute = (cRouteNode*)pNode;
        if ((pRoute->mData.mnSystemA == nSystem || pRoute->mData.mnSystemB == nSystem)
            && ((pRoute->mData.mnEmpireA == nEmpire && pRoute->mData.mnEmpireB == nPlayer)
                || (pRoute->mData.mnEmpireB == nEmpire && pRoute->mData.mnEmpireA == nPlayer)))
            return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// 0x01037d90  cSpaceTradeRouteManager::HasTradeRouteWithPlayer
// ---------------------------------------------------------------------------
// @ 0x01037d90
bool cSpaceTradeRouteManager::HasTradeRouteWithPlayer(uint32_t nSystem)
{
    cRBNodeBase* pNode = mRoutes.mAnchor.mpNodeLeft;
    cRBNodeBase* pEnd = &mRoutes.mAnchor;
    while (pNode != pEnd) {
        cRouteNode* pRoute = (cRouteNode*)pNode;
        if (pRoute->mData.mnSystemA == nSystem || pRoute->mData.mnSystemB == nSystem)
            return true;
        pNode = eastl_RBTreeIncrement(pNode);
    }
    return false;
}

// ---------------------------------------------------------------------------
// 0x01037dd0  cSpaceTradeRouteManager::SystemHasTradeRouteWithPlayer
// ---------------------------------------------------------------------------
// @ 0x01037dd0
float cSpaceTradeRouteManager::SystemHasTradeRouteWithPlayer(uint32_t nSystem, uint32_t nEmpire)
{
    uint32_t nPlayer = cSPLivingUniverse_GetPlayerEmpireID();
    cRBNodeBase* pEnd = &mRoutes.mAnchor;
    for (cRBNodeBase* pNode = mRoutes.mAnchor.mpNodeLeft; pNode != pEnd;
         pNode = eastl_RBTreeIncrement(pNode)) {
        cRouteNode* pRoute = (cRouteNode*)pNode;
        if ((pRoute->mData.mnSystemA == nSystem || pRoute->mData.mnSystemB == nSystem)
            && ((pRoute->mData.mnEmpireA == nEmpire && pRoute->mData.mnEmpireB == nPlayer)
                || (pRoute->mData.mnEmpireB == nEmpire && pRoute->mData.mnEmpireA == nPlayer)))
            return pRoute->mData.mfProgress;
    }
    return gMinusOne;
}

// ---------------------------------------------------------------------------
// 0x01037e40  cSpaceTradeRouteManager::GetPlayerProgressOnTradeRoute
// ---------------------------------------------------------------------------
// @ 0x01037e40
void cSpaceTradeRouteManager::GetPlayerProgressOnTradeRoute(uint32_t nSystem, uint32_t nEmpire)
{
    uint32_t nPlayer = cSPLivingUniverse_GetPlayerEmpireID();
    cRBNodeBase* pNode = mRoutes.mAnchor.mpNodeLeft;
    cRBNodeBase* pEnd = &mRoutes.mAnchor;
    if (pNode == pEnd)
        return;
    do {
        cRouteNode* pRoute = (cRouteNode*)pNode;
        if ((pRoute->mData.mnSystemA == nSystem || pRoute->mData.mnSystemB == nSystem)
            && ((pRoute->mData.mnEmpireA == nEmpire && pRoute->mData.mnEmpireB == nPlayer)
                || (pRoute->mData.mnEmpireB == nEmpire && pRoute->mData.mnEmpireA == nPlayer))) {
            pRoute->mData.mfProgress = 0.0f;
            return;
        }
        pNode = eastl_RBTreeIncrement(pNode);
    } while (pNode != pEnd);
}

// ---------------------------------------------------------------------------
// 0x01037eb0  cSpaceTradeRouteManager::ResetPlayerProgressOnTradeRoute
// ---------------------------------------------------------------------------
// @ 0x01037eb0
void cSpaceTradeRouteManager::ResetPlayerProgressOnTradeRoute(uint32_t nSystem,
                                                              uint32_t nEmpire, float fProgress)
{
    uint32_t nPlayer = cSPLivingUniverse_GetPlayerEmpireID();
    cRBNodeBase* pNode = mRoutes.mAnchor.mpNodeLeft;
    cRBNodeBase* pEnd = &mRoutes.mAnchor;
    if (pNode == pEnd)
        return;
    do {
        cRouteNode* pRoute = (cRouteNode*)pNode;
        if ((pRoute->mData.mnSystemA == nSystem || pRoute->mData.mnSystemB == nSystem)
            && ((pRoute->mData.mnEmpireA == nEmpire && pRoute->mData.mnEmpireB == nPlayer)
                || (pRoute->mData.mnEmpireB == nEmpire && pRoute->mData.mnEmpireA == nPlayer))) {
            pRoute->mData.mfProgress = fProgress;
            return;
        }
        pNode = eastl_RBTreeIncrement(pNode);
    } while (pNode != pEnd);
}

// ---------------------------------------------------------------------------
// 0x01037f20  cSpaceTradeRouteManager::GetNumberOfPlayerTradeRoutes
// ---------------------------------------------------------------------------
// @ 0x01037f20
int cSpaceTradeRouteManager::GetNumberOfPlayerTradeRoutes()
{
    uint32_t nPlayer = cSPLivingUniverse_GetPlayerEmpireID();
    cRBNodeBase* pNode = mRoutes.mAnchor.mpNodeLeft;
    cRBNodeBase* pEnd = &mRoutes.mAnchor;
    int nCount = 0;
    while (pNode != pEnd) {
        cRouteNode* pRoute = (cRouteNode*)pNode;
        if (pRoute->mData.mnEmpireA == nPlayer || pRoute->mData.mnEmpireB == nPlayer)
            ++nCount;
        pNode = eastl_RBTreeIncrement(pNode);
    }
    return nCount;
}

// ---------------------------------------------------------------------------
// 0x01037f60  cSpaceTradeRouteManager::GetPlayerTradeRouteTarget
// ---------------------------------------------------------------------------
// @ 0x01037f60
cCivData* cSpaceTradeRouteManager::GetPlayerTradeRouteTarget()
{
    uint32_t nPlayer = cSPLivingUniverse_GetPlayerEmpireID();
    cRBNodeBase* pNode = mRoutes.mAnchor.mpNodeLeft;
    cRBNodeBase* pEnd = &mRoutes.mAnchor;
    while (pNode != pEnd) {
        cRouteNode* pRoute = (cRouteNode*)pNode;
        if (pRoute->mData.mfProgress >= gFullProgress) {
            if (pRoute->mData.mnEmpireA == nPlayer)
                return StarManager(pRoute->mData.mnSystemB)->GetCivData();
            if (pRoute->mData.mnEmpireB == nPlayer)
                return StarManager(pRoute->mData.mnSystemA)->GetCivData();
        }
        pNode = eastl_RBTreeIncrement(pNode);
    }
    return 0;
}

// ---------------------------------------------------------------------------
// 0x010380b0  cTradeRouteTree::erase
// ---------------------------------------------------------------------------
// @ 0x010380b0
void cTradeRouteTree::erase(cRBNodeBase* pNode)
{
    while (pNode != 0) {
        erase(pNode->mpNodeRight);
        cRBNodeBase* pNext = pNode->mpNodeLeft;
        ((cRouteNode*)pNode)->mData.mpVtable = (void*)0x1499a30;
        cRouteNode_Free(pNode);
        pNode = pNext;
    }
}

// ---------------------------------------------------------------------------
// 0x010380f0  cTradeRouteTree::InsertNode
// ---------------------------------------------------------------------------
// @ 0x010380f0
void cTradeRouteTree::InsertNode(cRouteNode** ppOut, cRBNodeBase* pParent,
                                 const cTradeRoutePair* pValue, uint8_t bSide)
{
    uint8_t bLeft = 0;
    if (bSide == 0 && pParent != &mAnchor) {
        if (((cRouteNode*)pParent)->mnKeyA <= pValue->mnKeyA) {
            if (((cRouteNode*)pParent)->mnKeyA < pValue->mnKeyA
                || ((cRouteNode*)pParent)->mnKeyB <= pValue->mnKeyB)
                bLeft = 1;
        }
    }

    cRouteNode* pNode = (cRouteNode*)cRouteNode_Alloc(sizeof(cRouteNode), "Simulator", 0, 0,
                                                      "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                                                      0xd1);
    cTradeRoutePair* pPair = pNode != 0 ? static_cast<cTradeRoutePair*>(pNode) : 0;
    if (pPair != 0)
        new (pPair) cTradeRoutePair(*pValue);

    RBTreeInsertNode(pNode, pParent, &mAnchor, bLeft);
    ++mnSize;
    *ppOut = pNode;
}

// ---------------------------------------------------------------------------
// 0x01038180  cTradeRouteTree::DoInsertValue
// ---------------------------------------------------------------------------
// @ 0x01038180
cRouteNode** cTradeRouteTree::DoInsertValue(cRouteNode** ppOut, const cTradeRoutePair* pValue,
                                            int nUnused)
{
    uint8_t bLeft = 1;
    cRBNodeBase* pParent = &mAnchor;
    cRBNodeBase* pNode = mAnchor.mpNodeParent;
    if (pNode != 0) {
        do {
            pParent = pNode;
            if (pValue->mnKeyA < ((cRouteNode*)pNode)->mnKeyA
                || (pValue->mnKeyA <= ((cRouteNode*)pNode)->mnKeyA
                    && pValue->mnKeyB < ((cRouteNode*)pNode)->mnKeyB))
                bLeft = 1;
            else
                bLeft = 0;
            if (bLeft)
                pNode = pNode->mpNodeRight;
            else
                pNode = pNode->mpNodeLeft;
        } while (pNode != 0);
    }

    cRBNodeBase* pInsert = pParent;
    if (bLeft) {
        if (pParent == mAnchor.mpNodeLeft) {
            InsertNode(ppOut, pParent, pValue, 0);
            return ppOut;
        }
        pInsert = eastl_RBTreeDecrement(pParent);
    }

    if (((cRouteNode*)pInsert)->mnKeyA <= pValue->mnKeyA
        && (((cRouteNode*)pInsert)->mnKeyA < pValue->mnKeyA
            || ((cRouteNode*)pInsert)->mnKeyB <= pValue->mnKeyB)) {
        *ppOut = (cRouteNode*)pInsert;
        return ppOut;
    }

    InsertNode(ppOut, pParent, pValue, 0);
    return ppOut;
}

// ---------------------------------------------------------------------------
// 0x01038250  cSpaceTradeRouteManager::Destroy
// ---------------------------------------------------------------------------
// @ 0x01038250
void cSpaceTradeRouteManager::Destroy()
{
    mpVtable = (void*)0x1499a3c;
    cRBNodeBase* pRoot = mRoutes.mAnchor.mpNodeParent;
    mRoutes.erase(pRoot);
}

// ---------------------------------------------------------------------------
// 0x01038270  cSpaceTradeRouteManager::Read
// ---------------------------------------------------------------------------
// @ 0x01038270
bool cSpaceTradeRouteManager::Read(cStreamHandle* pStream)
{
    mnLastStarID = 0;
    mRoutes.erase(mRoutes.mAnchor.mpNodeParent);
    mRoutes.mAnchor.mpNodeLeft = &mRoutes.mAnchor;
    mRoutes.mAnchor.mpNodeParent = 0;
    mRoutes.mAnchor.mColor = 0;
    mRoutes.mnSize = 0;
    mRoutes.mAnchor.mpNodeRight = &mRoutes.mAnchor;

    void* pRaw = ((cStreamInterface*)pStream->GetStreamInterface())->GetRawStream();
    uint32_t nVersion;
    EA_IO_ReadInt32(pRaw, &nVersion, 1, 0);
    cVarListSerializer serializer(this, &gRouteManagerSerializerList, 0x1a80d26);
    return serializer.SerializeIn(pStream);
}

// ---------------------------------------------------------------------------
// 0x01038300  cSpaceTradeRouteManager::RemoveTradeRoute
// ---------------------------------------------------------------------------
// @ 0x01038300
int cSpaceTradeRouteManager::RemoveTradeRoute(void* pSystem)
{
    uint32_t nPlayer = cSPLivingUniverse_GetPlayerEmpireID();
    uint32_t nSystem = *(uint32_t*)((char*)pSystem + 0x70);
    int nRemoved = 0;
    cRBNodeBase* pNode = mRoutes.mAnchor.mpNodeLeft;
    while (pNode != &mRoutes.mAnchor) {
        cRouteNode* pRoute = (cRouteNode*)pNode;
        if ((pRoute->mData.mnSystemA == nSystem && pRoute->mData.mnEmpireB == nPlayer)
            || (pRoute->mData.mnSystemB == nSystem && pRoute->mData.mnEmpireA == nPlayer)) {
            --mRoutes.mnSize;
            cRBNodeBase* pNext = eastl_RBTreeIncrement(pNode);
            RBTreeEraseNode(pNode, &mRoutes.mAnchor);
            pRoute->mData.mpVtable = (void*)0x1499a30;
            cRouteNode_Free(pNode);
            pNode = pNext;
            ++nRemoved;
        } else {
            pNode = eastl_RBTreeIncrement(pNode);
        }
    }
    return nRemoved;
}

// ---------------------------------------------------------------------------
// 0x010383a0  cSpaceTradeRouteManager::RemoveAllTradeRoutesFromSystem
// ---------------------------------------------------------------------------
// @ 0x010383a0
bool cSpaceTradeRouteManager::RemoveAllTradeRoutesFromSystem(void* pSystem)
{
    uint32_t nSystem = *(uint32_t*)((char*)pSystem + 0x70);
    bool bRemoved = false;
    cRBNodeBase* pNode = mRoutes.mAnchor.mpNodeLeft;
    while (pNode != &mRoutes.mAnchor) {
        cRouteNode* pRoute = (cRouteNode*)pNode;
        if (pRoute->mData.mnSystemA == nSystem || pRoute->mData.mnSystemB == nSystem) {
            --mRoutes.mnSize;
            cRBNodeBase* pNext = eastl_RBTreeIncrement(pNode);
            RBTreeEraseNode(pNode, &mRoutes.mAnchor);
            pRoute->mData.mpVtable = (void*)0x1499a30;
            cRouteNode_Free(pNode);
            pNode = pNext;
            bRemoved = true;
        } else {
            pNode = eastl_RBTreeIncrement(pNode);
        }
    }
    return bRemoved;
}
