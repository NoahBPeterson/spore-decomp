// 0x00b8bb70..0x00b8c0f0 -- SP::cPlanetModel (PDB: cCityDisplayStrategy for the
// resource pass) water probe, resource-node rebuild and minimap teardown.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE.

#include "types.h"
#include <math.h>

extern "C" long __cdecl _InterlockedExchangeAdd(volatile long*, long);
extern "C" long __cdecl _InterlockedExchange(volatile long*, long);
extern "C" long __cdecl _InterlockedDecrement(volatile long*);
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedExchange, _InterlockedDecrement)

struct SVector3 {
    float x, y, z;
};

// 0x00f473a0: EA debug operator new (size, tag, flags, debugFlags, file, line).
void* operator new(size_t size, const char* pName, int nFlags, unsigned nDebugFlags,
                   const char* pFile, int nLine);

// ---------------------------------------------------------------------------
// Graph / minimap objects
// ---------------------------------------------------------------------------
class RCSub {
public:
    virtual void Del(int);
    volatile long mnRefCount;                  // +0x04
    long Release()
    {
        long n = _InterlockedDecrement(&mnRefCount);
        if (n == 0) {
            _InterlockedExchange(&mnRefCount, 1);
            if (this)
                Del(1);
        }
        return n;
    }
};

class cMinimapGfx {
public:
    char     pad00[0x0c];
    bool     mbDirty;                          // +0x0c
    char     pad0d[0x24 - 0x0d];
    RCSub*   mpRefObject;                      // +0x24
    bool     mbActive;                         // +0x28
};

class cPlanet {
public:
    void SetRampEnabled(bool bEnabled);        // 0x00fbd6b0
};

class cTerrainEditor {
public:
    void SetActiveObject(void* pObject);       // 0x00f67a60
};

class cInputManager {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void SetMode(int nMode);           // +0x50
};

class cMessageServer {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual void Post(void* pSender, uint32_t nMessage, int nFlags);   // +0x2c
};

class cEffectsManager {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void SetTime(int nA, int nB);      // +0x20
};

class cRenderer {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38();
    virtual void SetFlag(int nValue);          // +0x3c
};

class IWorldEditor {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual cPlanet* v10();                    // +0x10
    virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void vA0(); virtual void vA4(); virtual void vA8(); virtual void vAC();
    virtual void vB0(); virtual void vB4(); virtual void vB8(); virtual void vBC();
    virtual void vC0(); virtual void vC4(); virtual void vC8(); virtual void vCC();
    virtual void vD0(); virtual void vD4(); virtual void vD8(); virtual void vDC();
    virtual void vE0(); virtual void vE4(); virtual void vE8(); virtual void vEC();
    virtual void vF0(); virtual void vF4(); virtual void vF8(); virtual void vFC();
    virtual void v100(); virtual void v104(); virtual void v108(); virtual void v10C();
    virtual void ShutdownScene();              // +0x110
};

class IPlanetSphere {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void SetInputManager(void* pManager);        // +0x90
    virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void vA0();
    virtual void vA4();                        // +0xa4
    virtual void vA8();
    virtual void vAC();                        // +0xac
    virtual void vB0(); virtual void vB4(); virtual void vB8(); virtual void vBC();
    virtual void vC0(); virtual void vC4(); virtual void vC8(); virtual void vCC();
    virtual void vD0(); virtual void vD4(); virtual void vD8(); virtual void vDC();
    virtual void vE0(); virtual void vE4(); virtual void vE8();
    virtual void vEC();                        // +0xec
    virtual void vF0(); virtual void vF4();
    virtual void vF8();                        // +0xf8
};

struct CityPair {
    void* mpFirst;
    void* mpSecond;
};
struct LandRoute {
    uint8_t mData[0x1c];
};

class CityPairVector {
public:
    CityPair* mpBegin;                         // +0x00
    CityPair* mpEnd;                           // +0x04
    CityPair* mpCapacity;                      // +0x08
    uint32_t  mAllocator;                      // +0x0c
    void EraseRange(CityPair* pFirst, CityPair* pLast);        // 0x00d018d0
    void Clear() { EraseRange(mpBegin, mpEnd); }
};

class LandRouteVector {
public:
    LandRoute* mpBegin;                        // +0x00
    LandRoute* mpEnd;                          // +0x04
    LandRoute* mpCapacity;                     // +0x08
    uint32_t   mAllocator;                     // +0x0c
    void EraseRange(LandRoute* pFirst, LandRoute* pLast);      // 0x00b897d0
    void Clear() { EraseRange(mpBegin, mpEnd); }
};

// ---------------------------------------------------------------------------
// City / resource-node records
// ---------------------------------------------------------------------------
class cCivilization {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48();
    virtual int GetID();                       // +0x4c
};

// Embedded object with a vtable at +0x00 whose slot +0x2c returns the three
// coordinates used to place a graph node.
class IPositionSource {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual const SVector3* GetPosition();     // +0x2c
};

class cCity {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48();
    virtual int GetOwnerID(bool bPrimary);     // +0x4c
    char              pad04[0x34 - 0x04];
    IPositionSource   mNodeValue;              // +0x34
    char              pad38[0x120 - 0x38];
    IPositionSource   mPosition;               // +0x120
    cCivilization*    GetCivilization();       // 0x00bd9bf0
};

class cPlaceholder {
public:
    char              pad00[0x34];
    IPositionSource   mNodeValue;              // +0x34
};

struct GraphNodeValue {
    uint32_t mValue[3];
};
struct GraphNode {
    int32_t         mnID;                      // +0x00
    GraphNodeValue  mValue;                    // +0x04
    bool            mbResourceNode;            // +0x10
    bool            mbDirty;                   // +0x11
    uint16_t        pad12;
    cCity*          mpCity;                    // +0x14
};
class GraphNodeVector {
public:
    GraphNode* mpBegin;                        // +0x00
    GraphNode* mpEnd;                          // +0x04
    GraphNode* mpCapacity;                     // +0x08
    uint32_t   mAllocator;                     // +0x0c
};

template <class T>
struct SpVector {
    T*       mpBegin;                          // +0x00
    T*       mpEnd;                            // +0x04
    T*       mpCapacity;                       // +0x08
    uint32_t mAllocator;                       // +0x0c
};

struct tGameDataVector {
    uint32_t            pad00;
    SpVector<cCity*>    mData;                 // +0x04
};

class cGameNounManager {
public:
    tGameDataVector* GetGameDataVector(void* pfnA, void* pfnB, void* pfnC,
                                       void* pfnD, void* pFilter);      // 0x00b21340
};

class cEffMgr {
public:
    char pad00[0xac];
    int  mnSlotCount;                          // +0xac
};

namespace Simulator {
struct SimSlot {
    uint32_t mnNounID;                         // +0x00
    char     pad04[0x2c];
    bool     mbInactive;                       // +0x30
    char     pad31[0x64 - 0x31];
};
struct SimSlotVector {
    SimSlot* mpBegin;                          // +0x00
    SimSlot* mpEnd;                            // +0x04
    SimSlot* mpCapacity;                       // +0x08
    uint32_t mAllocator;                       // +0x0c
};
class SimSingleton {
public:
    char          pad00[0x14];
    SimSlotVector mVec;                        // +0x14
    char          pad24[0xc8 - 0x24];
    SimSingleton();                            // 0x00ae5c30
    static SimSingleton* sInstance;            // 0x0167a60c
};
}

struct IVec3U {
    uint32_t mX, mY, mZ;
    IVec3U() {}
    IVec3U(uint32_t x, uint32_t y, uint32_t z) : mX(x), mY(y), mZ(z) {}
};

// ---------------------------------------------------------------------------
// cPlanetModel
// ---------------------------------------------------------------------------
class cPlanetModel {
public:
    char            pad00[0x20];
    IWorldEditor*   mpWorldEditor;             // +0x20
    IPlanetSphere*  mpISphere;                 // +0x24
    char            pad28[0x2c - 0x28];
    IVec3U          mField2C;                  // +0x2c
    uint16_t*       mpIndexBegin;              // +0x38
    uint16_t*       mpIndexEnd;                // +0x3c
    char            pad40[0x48 - 0x40];
    bool            mbRegistered;              // +0x48
    char            pad49[0x4c - 0x49];
    uint32_t*       mContinentMap;             // +0x4c
    char            pad50[0x64 - 0x50];
    uint8_t*        mContinentAboveWater;      // +0x64
    char            pad68[0x7c - 0x68];
    uint32_t*       mpCellNibbles;             // +0x7c
    GraphNodeVector mNodes;                    // +0x80
    char            pad90[0x94 - 0x90];
    uint8_t*        mpZoneMap;                 // +0x94
    uint8_t*        mpZoneMapEnd;              // +0x98
    char            pad9c[0xa8 - 0x9c];
    cMinimapGfx*    mpMinimapGfx;              // +0xa8
    CityPairVector  mSeaTradeRoutes;           // +0xac
    char            padBC[0xc0 - 0xbc];
    CityPairVector  mLandTradeRoutes;          // +0xc0
    char            padD0[0xd4 - 0xd0];
    LandRouteVector mPathRoutes;               // +0xd4
    char            padE4[0xe8 - 0xe4];
    bool            mbSeaRoutesDirty;          // +0xe8
    bool            mbLandRoutesDirty;         // +0xe9
    bool            mbPathRoutesDirty;         // +0xea

    bool RayCast(const SVector3* pOrigin, float fDirection, SVector3* pOut,
                 float fRadius, bool bLayer, uint32_t nMask);          // 0x00b88770
    bool FindClosestWater(const SVector3* pOrigin, float fDirection,
                          SVector3* pOut);                             // 0x00b8bb70
    void Reset();                                                      // 0x00b87bb0
    int  AddNode(const SVector3* pValue, bool bResourceNode);          // 0x00b86500
    void SetNodeFlag(int nIndex, bool bValue);                         // 0x00b7ea30
    void SetNodeID(int nIndex, int nValue);                            // 0x00b841a0
    int  GetContinent(const SVector3* pPosition);                      // 0x00b88590
    void BuildPoliticalZoneMap();                                      // 0x00b8aea0
    void Shutdown();                                                   // 0x00b8c0f0
    void AddResourceNodes();                                           // 0x00b8bba0
};

extern cInputManager* InputManager();          // 0x0067dd50
extern cMessageServer* MessageServer();        // 0x0067dcc0
extern cEffectsManager* EffectsManagerPtr();   // 0x0067ddd0
extern cRenderer* g_Renderer;                  // 0x0167ea54
extern "C" uint32_t* __cdecl Memset32(uint32_t* pDst, uint32_t nValue, int nCount);  // 0x0092cb00
extern "C" cTerrainEditor* __cdecl TerrainEditor();                    // 0x00f48a70
extern "C" void __cdecl FUN_00f48af0(int nValue);                      // 0x00f48af0
extern "C" cGameNounManager* __cdecl NounManager();                    // 0x00b3d300
extern "C" cEffMgr* __cdecl GetEffMgr();                               // 0x00b26930
extern "C" cPlaceholder* __cdecl FindPlaceholder(int nID);             // 0x00b993c0
extern "C" void* __cdecl GetCurrentGameMode();                         // 0x00b5b800

// ---------------------------------------------------------------------------
// 0x00b8bb70: SP::cPlanetModel::FindClosestWater -- unit-radius downward ray.
// ---------------------------------------------------------------------------
// @ 0x00b8bb70
bool cPlanetModel::FindClosestWater(const SVector3* pOrigin, float fDirection,
                                    SVector3* pOut)
{
    return RayCast(pOrigin, fDirection, pOut, 1.0f, true, 0);
}

// ---------------------------------------------------------------------------
// 0x00b8c0f0: cPlanetModel::Shutdown -- release the minimap, tear down the
// rendered planet and clear the graph bookkeeping.
// ---------------------------------------------------------------------------
// @ 0x00b8c0f0
void cPlanetModel::Shutdown()
{
    cMinimapGfx* gfx = mpMinimapGfx;
    RCSub** ppRef = &gfx->mpRefObject;
    if (RCSub* pRef = *ppRef) {
        *ppRef = 0;
        pRef->Release();
    }

    cMinimapGfx* gfx2 = mpMinimapGfx;
    if (gfx2->mbActive) {
        InputManager()->SetMode(9);
        InputManager()->SetMode(0x19);
    }
    gfx2->mbActive = false;

    mSeaTradeRoutes.Clear();
    mLandTradeRoutes.Clear();
    mPathRoutes.Clear();
    mbSeaRoutesDirty = true;
    mbPathRoutesDirty = true;
    mbLandRoutesDirty = true;

    if (mbRegistered) {
        mbRegistered = false;
        MessageServer()->Post(this, 0x1b537e5, 0xffffd8f1);
        MessageServer()->Post(this, 0x182c582, 0xffffd8f1);
        MessageServer()->Post(this, 0x44448ed, 0xffffd8f1);
        MessageServer()->Post(this, 0x45fe992, 0xffffd8f1);
    }

    EffectsManagerPtr()->SetTime(0, -1);
    TerrainEditor()->SetActiveObject(0);
    FUN_00f48af0(0);

    if (mpISphere != 0) {
        cPlanet* pPlanet = mpWorldEditor->v10();
        pPlanet->SetRampEnabled(false);
        mpISphere->SetInputManager(InputManager());
        mpISphere->vAC();
        g_Renderer->SetFlag(0);
        mpISphere->vA4();
        mpISphere->vEC();
        mpISphere->vF8();
        mpWorldEditor->ShutdownScene();
        if (mpWorldEditor != 0) {
            IWorldEditor* pOld = mpWorldEditor;
            mpWorldEditor = 0;
            pOld->v04();
        }
        mpISphere = 0;
    }

    Memset32(mpCellNibbles, 0, 0x3000);

    uint32_t* pCells = mContinentMap;
    for (int i = 0; i < 0x18000; ++i)
        pCells[i] &= 0xc3ffffff;

    Reset();

    if (mpIndexBegin != mpIndexEnd) {
        *mpIndexBegin = 0;
        mpIndexEnd = mpIndexBegin;
    }

    mField2C = IVec3U(0, 0, 0);
}

// ---------------------------------------------------------------------------
// 0x00b8bba0: cPlanetModel::AddResourceNodes -- rebuild the graph nodes for
// cities / resource placeholders and hook each to its political zone.
// ---------------------------------------------------------------------------
// @ 0x00b8bba0
void cPlanetModel::AddResourceNodes()
{
    if (mpISphere == 0)
        return;

    Reset();

    if (GetCurrentGameMode() != (void*)0x1654c04)
        return;

    int nSlots = GetEffMgr()->mnSlotCount;
    for (int i = 0; i < nSlots; ++i) {
        Simulator::SimSingleton* pSim = Simulator::SimSingleton::sInstance;
        if (pSim == 0)
            pSim = Simulator::SimSingleton::sInstance =
                new ("Simulator/SimSingleton", 0, 0, 0, 0) Simulator::SimSingleton();

        Simulator::SimSlot* pSlot = &pSim->mVec.mpBegin[i];
        if (pSlot->mbInactive == false) {
            cPlaceholder* pPlaceholder = FindPlaceholder(pSlot->mnNounID);
            if (pPlaceholder != 0) {
                int nIndex = AddNode(pPlaceholder->mNodeValue.GetPosition(), true);
                SetNodeFlag(nIndex, true);
            }
        }
    }

    SpVector<cCity*>& cityList = NounManager()->GetGameDataVector(
        (void*)0xcd7d10, (void*)0xd3d420, (void*)0xacdff0, (void*)0xb1e500,
        (void*)0x18c43e8)->mData;
    int nCities = (int)(cityList.mpEnd - cityList.mpBegin);
    for (int i = 0; i < nCities; ++i) {
        int nIndex = AddNode(cityList.mpBegin[i]->mPosition.GetPosition(), true);
        if (nIndex > 0 && nIndex < (uint32_t)(mNodes.mpEnd - mNodes.mpBegin) &&
            mNodes.mpBegin[nIndex].mbDirty != true) {
            mNodes.mpBegin[nIndex].mbDirty = true;
            mpMinimapGfx->mbDirty = true;
        }
    }

    SpVector<cCity*>& resourceList = NounManager()->GetGameDataVector(
        (void*)0xcd7d10, (void*)0xd3d420, (void*)0xae5ea0, (void*)0xb1e500,
        (void*)0x403df5c)->mData;
    int nResources = (int)(resourceList.mpEnd - resourceList.mpBegin);
    for (int i = 0; i < nResources; ++i) {
        cCity* pEntity = resourceList.mpBegin[i];
        int nContinent = GetContinent(pEntity->mNodeValue.GetPosition());
        if (mContinentAboveWater[nContinent]) {
            int nIndex = AddNode(pEntity->mNodeValue.GetPosition(), false);
            SetNodeID(nIndex, pEntity->GetOwnerID(false));
            if (nIndex > 0 && nIndex < (uint32_t)(mNodes.mpEnd - mNodes.mpBegin) &&
                mNodes.mpBegin[nIndex].mbDirty != true) {
                mNodes.mpBegin[nIndex].mbDirty = true;
                mpMinimapGfx->mbDirty = true;
            }
        }
    }

    BuildPoliticalZoneMap();

    int nNodeCount = (int)(mNodes.mpEnd - mNodes.mpBegin);
    for (int i = 1; i < nNodeCount; ++i)
        mNodes.mpBegin[i].mpCity = 0;

    for (int i = 0; i < nCities; ++i) {
        cCity* pCity = cityList.mpBegin[i];
        if (pCity != 0 && pCity->GetCivilization() != 0) {
            const SVector3* pPos = pCity->mPosition.GetPosition();
            float ax = fabsf(pPos->x);
            float ay = fabsf(pPos->y);
            float az = fabsf(pPos->z);
            int nFirst;
            int nSecond;
            int nFace;
            if (az < ax || az < ay) {
                if (ay < ax) {
                    nFirst  = (int)((pPos->y / pPos->x + 1.0f) * 32.0f);
                    nSecond = (int)((pPos->z / ax + 1.0f) * 32.0f);
                    nFace   = (pPos->x < 0.0f) ? 3 : 2;
                } else {
                    nFirst  = (int)((pPos->z / pPos->y + 1.0f) * 32.0f);
                    nSecond = (int)((pPos->x / ay + 1.0f) * 32.0f);
                    nFace   = (pPos->y < 0.0f) ? 5 : 4;
                }
            } else {
                nFirst  = (int)((pPos->x / pPos->z + 1.0f) * 32.0f);
                nSecond = (int)((pPos->y / az + 1.0f) * 32.0f);
                nFace   = (pPos->z < 0.0f) ? 1 : 0;
            }
            if (nFirst == 0x40)
                nFirst = 0x3f;
            if (nSecond == 0x40)
                nSecond = 0x3f;
            int nZone = mpZoneMap[(nFace * 0x40 + nSecond) * 0x40 + nFirst];
            if (nZone > 0 && mNodes.mpBegin[nZone].mbResourceNode)
                mNodes.mpBegin[nZone].mpCity = pCity;
        }
    }

    nNodeCount = (int)(mNodes.mpEnd - mNodes.mpBegin);
    for (int i = 1; i < nNodeCount; ++i) {
        GraphNode& node = mNodes.mpBegin[i];
        if (node.mbResourceNode) {
            int nCiv = -1;
            if (node.mpCity != 0)
                nCiv = node.mpCity->GetCivilization()->GetID();
            if (node.mnID != nCiv) {
                mpMinimapGfx->mbDirty = true;
                node.mnID = nCiv;
                node.mbDirty = true;
            }
        }
    }
}
