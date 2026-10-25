// src/game/SPGonzago/SPSpaceTradeRouteManager.cpp -- migrated from slice(s) s010377f0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPSpaceTradeRouteManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSpaceTradeRouteManager.h"
#include "SP/cCivData.h"
#include "SP/cGonzagoSubsystem.h"
#include "SP/cStarManager.h"
#include "SP/cTerrainSphere.h"
#include "SP/cTradeRouteData.h"
#include "SP/cVarListSerializer.h"

// unnamed retail callees and globals (address in the comment)
extern float gCityRadius;               // 0x015b7d08
extern float gMinusOne;                 // 0x013eb1bc
extern float gFullProgress;             // 0x013ec4d0

// ---- items of slice s010377f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vec3 {
    float mX;
    float mY;
    float mZ;
};
inline void* operator new(size_t, void* pMemory) {
    return pMemory;
}
class cCivData {
public:
    const Vec3* GetCities();                                    // 0x005c65e0
};
class cStarManager {
public:
    cCivData* GetCivData();                                     // 0x00ba6d80
};
class cTradeRouteData;
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
class cVarListSerializer {
public:
    cVarListSerializer(const void* pObject, const void* pList, int nVersion);   // 0x00692f90
    bool SerializeOut(cStreamHandle* pStream);                  // 0x00692900
    bool SerializeIn(cStreamHandle* pStream);                   // 0x00693e10

    void* mpVtable;                                             // 0x000
    uint8_t mPad004[0xa10];                                     // 0x004
};
uint32_t cSPLivingUniverse_GetPlayerEmpireID();                 // 0x01021090
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
extern float gCityRadius;               // 0x015b7d08
extern float gMinusOne;                 // 0x013eb1bc
extern float gFullProgress;             // 0x013ec4d0
extern cSerializerList gTradeRouteSerializerList;       // 0x015b7dc0
extern cSerializerList gRouteManagerSerializerList;     // 0x015b7fe0
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
class cTradeRoutePair {
public:
    cTradeRoutePair(const cTradeRoutePair& src);                // 0x01037a60

    uint32_t mnKeyA;                    // 0x00
    uint32_t mnKeyB;                    // 0x04
    cTradeRouteData mData;              // 0x08
};
struct cRBNodeBase {
    cRBNodeBase* mpNodeRight;           // 0x00
    cRBNodeBase* mpNodeLeft;            // 0x04
    cRBNodeBase* mpNodeParent;          // 0x08
    uint8_t mColor;                     // 0x0c
    uint8_t mPad00d[0x03];              // 0x0d
};
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
// ---- items of slice s010377f0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern cSerializerList gTradeRouteSerializerList;       // 0x015b7dc0
extern cSerializerList gRouteManagerSerializerList;     // 0x015b7fe0

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

// @ 0x01037ae0
bool cTradeRouteData::Write(cStreamHandle* pStream)
{
    void* pRaw = ((cStreamInterface*)pStream->GetStreamInterface())->GetRawStream();
    uint32_t nVersion = 0x5527100;
    EA_IO_WriteUint32(pRaw, &nVersion, 1, 0);
    cVarListSerializer serializer(this, &gTradeRouteSerializerList, 0x1a80d26);
    return serializer.SerializeOut(pStream);
}

// @ 0x01037b50
bool cTradeRouteData::Read(cStreamHandle* pStream)
{
    void* pRaw = ((cStreamInterface*)pStream->GetStreamInterface())->GetRawStream();
    uint32_t nVersion;
    EA_IO_ReadInt32(pRaw, &nVersion, 1, 0);
    cVarListSerializer serializer(this, &gTradeRouteSerializerList, 0x1a80d26);
    return serializer.SerializeIn(pStream);
}

// @ 0x01037bc0
bool cSpaceTradeRouteManager::Write(cStreamHandle* pStream)
{
    void* pRaw = ((cStreamInterface*)pStream->GetStreamInterface())->GetRawStream();
    uint32_t nVersion = 0x5526a59;
    EA_IO_WriteUint32(pRaw, &nVersion, 1, 0);
    cVarListSerializer serializer(this, &gRouteManagerSerializerList, 0x1a80d26);
    return serializer.SerializeOut(pStream);
}

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

// @ 0x01037eb0
void cSpaceTradeRouteManager::ResetPlayerProgressOnTradeRoute(uint32_t nSystem, uint32_t nEmpire, float fProgress)
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

// @ 0x010380f0
void cTradeRouteTree::InsertNode(cRouteNode** ppOut, cRBNodeBase* pParent, const cTradeRoutePair* pValue, uint8_t bSide)
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

// @ 0x01038180
cRouteNode** cTradeRouteTree::DoInsertValue(cRouteNode** ppOut, const cTradeRoutePair* pValue, int nUnused)
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
