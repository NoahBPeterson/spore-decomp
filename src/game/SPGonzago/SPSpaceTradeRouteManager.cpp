// src/game/SPGonzago/SPSpaceTradeRouteManager.cpp -- migrated from slice(s) s013a55c0, s010393a0, s010377f0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPSpaceTradeRouteManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

// addresses retail relocates here, named so the build relocates them too
extern "C" char g_1499a30[];

#include "game/types.h"
#include "SP/cCivData.h"
#include "SP/cGonzagoSubsystem.h"
#include "SP/cSpaceTradeRouteManager.h"
#include "SP/cStarManager.h"
#include "SP/cTerrainSphere.h"
#include "SP/cTradeRouteData.h"
#include "SP/cVarListSerializer.h"
#include "EA/ResourceMan/Key.h"
#include "SP/cEmpire.h"
#include "SP/cGameNounManager.h"
#include "SP/cGonzagoTimer.h"
#include "SP/cPlanetRecord.h"
#include "SP/cPropertyManager.h"
#include "SP/cSPSpaceEconomyTuning.h"
#include "SP/cSPSpaceInventoryItem.h"
#include "SP/cStarRecord.h"
#include <math.h>
#include <intrin.h>

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
class cStreamInterface;
class cStreamHandle {
public:
    virtual void slot_0();
    virtual void slot_1();
    virtual void slot_2();
    virtual void slot_3();
    virtual void slot_4();
    virtual void slot_5();
    virtual void slot_6();
    virtual void slot_7();
    virtual cStreamInterface* GetStreamInterface();             // slot 8, +0x20
};
class cStreamInterface {
public:
    virtual void slot_0();
    virtual void slot_1();
    virtual void slot_2();
    virtual void slot_3();
    virtual void slot_4();
    virtual void slot_5();
    virtual void* GetRawStream();                              // slot 6, +0x18
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
void RBTreeEraseNode(void* pNode, void* pAnchor);               // 0x00921880
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
    void clear() {
        erase(mAnchor.mpNodeParent);
        mAnchor.mpNodeLeft = &mAnchor;
        mAnchor.mpNodeParent = 0;
        mAnchor.mColor = 0;
        mnSize = 0;
        mAnchor.mpNodeRight = &mAnchor;
    }
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

// ---- items of slice s010393a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define VSLOT(n) virtual void _v##n();
struct Vector3 {
    float x, y, z;
};
struct IMessageServer {
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4)
    virtual void SendMSG(uint32_t id, void* msg, void* target);              // +0x14
    VSLOT(6) VSLOT(7) VSLOT(8)
    virtual void AddHandler(void* pHandler, uint32_t msgID);                 // +0x24
};
IMessageServer* MessageServer();                                             // 0x0067dcc0
struct IRefSlot { VSLOT(0) virtual int Release(); };
struct MessageBase0 { virtual ~MessageBase0() {} };
struct MessageBase1 : MessageBase0 {
    volatile long mnRefCount;
    MessageBase1() { _InterlockedExchange((long*)&mnRefCount, 0); }
};
struct TradeMessage : MessageBase1 {
    struct Slot { IRefSlot* p; uint32_t pad; } mSlots[5];
    uint32_t mMessageID;                                                     // +0x30
    uint32_t pad34;
    uint32_t mRefMask;                                                       // +0x38
    TradeMessage(uint32_t id) { mMessageID = id; mRefMask = 0; }
    ~TradeMessage()
    {
        for (int i = 0; i < 32; ++i)
            if ((mRefMask & (1u << i)) && mSlots[i].p)
                mSlots[i].p->Release();
    }
    void SetValue(int i, uint32_t v) { *(uint32_t*)&mSlots[i].p = v; }
};
struct cSpatialEntity {
    const Vector3& GetPosition();                                            // 0x005c65e0
};
struct cStarRecord_s0103_93a0 : cSpatialEntity {
    uint32_t pad00[0x70 / 4];
    uint32_t mKey;                                                           // +0x70
};
namespace SP {
cSpatialEntity* GetActivePlanet();                                           // 0x01021230
}
struct cTradeRouteData_s0103_93a0 {
    virtual ~cTradeRouteData_s0103_93a0() {}
    virtual bool Write(void* stream);  // 0x01037ae0 (cTradeRouteData::Write)
    virtual bool Read(void* stream);  // 0x01037b50 (cTradeRouteData::Read)

    uint32_t mPoliticalID1;                                                  // +0x04
    uint32_t mPoliticalID2;                                                  // +0x08
    uint32_t mStarID1;                                                       // +0x0c
    uint32_t mStarID2;                                                       // +0x10
    float mTradeRouteProgress;                                               // +0x14
    bool mInDetectableRange;                                                 // +0x18
    uint32_t mTimeSinceLastUFOMS;                                            // +0x1c
    uint32_t mTimeSinceLastSimMS;                                            // +0x20
    float mRouteLength;                                                      // +0x24
    int mLastMerchantVoyage;                                                 // +0x28
};
struct TradeKey { uint32_t first, second; };
namespace eastl {
struct rbtree_node_base_s0103_93a0 {
    rbtree_node_base_s0103_93a0* mpNodeRight;
    rbtree_node_base_s0103_93a0* mpNodeLeft;
    rbtree_node_base_s0103_93a0* mpNodeParent;
    char mColor;
};
}
struct TradeRouteNode : eastl::rbtree_node_base_s0103_93a0 {
    TradeKey mKey;                                                           // +0x10
    cTradeRouteData_s0103_93a0 mValue;                                                  // +0x18
};
struct TradeRouteMap {
    uint32_t mCompare;                                                       // +0x04
    eastl::rbtree_node_base_s0103_93a0 mAnchor;                                         // +0x08
    uint32_t mnSize;                                                         // +0x18
    uint32_t mAllocator;                                                     // +0x1c

    TradeRouteNode* end() { return (TradeRouteNode*)&mAnchor; }
    void Find(TradeRouteNode** pOut, const TradeKey& key);                   // 0x00d00f80
    TradeRouteNode* Insert(const TradeKey& key);                             // 0x010392f0
};
struct cSpaceTradeRouteManager_s0103_93a0 {
    virtual ~cSpaceTradeRouteManager_s0103_93a0();
    TradeRouteMap mTradeRoutes;                                              // +0x04
    uint32_t mLastStarID;                                                    // +0x20

    void UpdateRouteLength(cTradeRouteData_s0103_93a0* route, Vector3 pos);             // 0x01037c30
    void AddTradeRoute(cStarRecord_s0103_93a0* pStar1, uint32_t politicalID1,
                       cStarRecord_s0103_93a0* pStar2, uint32_t politicalID2);
};
// ---- items of slice s010393a0 end

// ---- items of slice s013a55c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct AttrRec {
    const char* mpName;              // +0x00
    void*       mpField;             // +0x04
    int32_t     mFieldOfs;           // +0x08
    int32_t     mUnk0c;              // +0x0c  (left indeterminate, as in the original)
    int32_t     mUnk10;              // +0x10
    int32_t     mUnk14;              // +0x14
    int32_t     mZero18;             // +0x18
    int32_t     mZero1c;             // +0x1c
    void*       mpFn20;              // +0x20
    void*       mpFn24;              // +0x24
    void*       mpFn28;              // +0x28
    void*       mpFn2c;              // +0x2c
    void*       mpFn30;              // +0x30
    void*       mpFn34;              // +0x34
    void*       mpFn38;              // +0x38
};
char g_55271b4;  char g_55271ba;  char g_55271c0;  char g_55271c4;
char g_5540e28;  char g_5540e44;  char g_55271c7;  char g_55555c7;
char g_692ca0;   char g_572810;   char g_572840;   char g_693090;
char g_694f00;   char g_b1fbf0;   char g_675ca0;   char g_ac88f0;
AttrRec g_t15b7dc0[8];
// ---- items of slice s013a55c0 end

// @ 0x01037a60
cTradeRoutePair::cTradeRoutePair(const cTradeRoutePair& src)
{
    mnKeyA = src.mnKeyA;
    mnKeyB = src.mnKeyB;
    mData.mpVtable = (void*)g_1499a30;
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
    cStreamInterface* __restrict pInterface = pStream->GetStreamInterface();
    uint32_t nVersion = 0x5527100;
    void* pRaw = pInterface->GetRawStream();
    EA_IO_WriteUint32(pRaw, &nVersion, 1, 0);
    SP::cVarListSerializer serializer(this,
        reinterpret_cast<SP::cDataSerializerGeneric*>(&gTradeRouteSerializerList),
        SP::cVarListSerializer::kSignature);
    bool result = serializer.Serialize(*reinterpret_cast<SP::cIObjectDatabaseOStream*>(pStream)) ? true : false;
    return result;
}

// @ 0x01037b50
bool cTradeRouteData::Read(cStreamHandle* pStream)
{
    void* pRaw = ((cStreamInterface*)pStream->GetStreamInterface())->GetRawStream();
    uint32_t nVersion;
    EA_IO_ReadInt32(pRaw, &nVersion, 1, 0);
    cVarListSerializer serializer(this, &gTradeRouteSerializerList, 0x1a80d26);
    bool ok = serializer.SerializeIn(pStream) != 0;
    return ok;
}

// @ 0x01037bc0
bool cSpaceTradeRouteManager::Write(cStreamHandle* pStream)
{
    cStreamInterface* __restrict pInterface = pStream->GetStreamInterface();
    uint32_t nVersion = 0x5526a59;
    void* pRaw = pInterface->GetRawStream();
    EA_IO_WriteUint32(pRaw, &nVersion, 1, 0);
    SP::cVarListSerializer serializer(this,
        reinterpret_cast<SP::cDataSerializerGeneric*>(&gRouteManagerSerializerList),
        SP::cVarListSerializer::kSignature);
    bool result = serializer.Serialize(*reinterpret_cast<SP::cIObjectDatabaseOStream*>(pStream)) ? true : false;
    return result;
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
        ((cRouteNode*)pNode)->mData.mpVtable = (void*)g_1499a30;
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

// @ 0x01038250
void cSpaceTradeRouteManager::Destroy()
{
    mpVtable = (void*)0x1499a3c;
    cRBNodeBase* pRoot = mRoutes.mAnchor.mpNodeParent;
    mRoutes.erase(pRoot);
}

// @ 0x01038270
bool cSpaceTradeRouteManager::Read(cStreamHandle* pStream)
{
    mnLastStarID = 0;
    mRoutes.clear();

    cStreamInterface* __restrict pInterface = pStream->GetStreamInterface();
    uint32_t nVersion;
    void* pRaw = pInterface->GetRawStream();
    EA_IO_ReadInt32(pRaw, &nVersion, 1, 0);
    SP::cVarListSerializer serializer(this,
        reinterpret_cast<SP::cDataSerializerGeneric*>(&gRouteManagerSerializerList),
        SP::cVarListSerializer::kSignature);
    bool result = serializer.Serialize(*reinterpret_cast<SP::cIObjectDatabaseIStream*>(pStream)) ? true : false;
    return result;
}

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

// @ 0x010393a0
void cSpaceTradeRouteManager_s0103_93a0::AddTradeRoute(cStarRecord_s0103_93a0* pStar1, uint32_t politicalID1, cStarRecord_s0103_93a0* pStar2, uint32_t politicalID2)
{
    uint32_t star1 = pStar1->mKey;
    uint32_t star2 = pStar2->mKey;
    uint32_t keyStar1 = star1;
    uint32_t keyStar2 = star2;
    if (keyStar1 > keyStar2) {
        uint32_t swap = keyStar1;
        keyStar1 = keyStar2;
        keyStar2 = swap;
    }
    TradeKey key;
    key.first = keyStar1;
    key.second = keyStar2;
    TradeRouteNode* pFound;
    mTradeRoutes.Find(&pFound, key);
    if (pFound != mTradeRoutes.end())
        return;
    if (star1 > star2) {
        uint32_t swap = star1;
        star1 = star2;
        star2 = swap;
        swap = politicalID1;
        politicalID1 = politicalID2;
        politicalID2 = swap;
    }
    TradeRouteNode* pNode = mTradeRoutes.Insert(key);
    cTradeRouteData_s0103_93a0* pRoute = &pNode->mValue;
    pRoute->mPoliticalID1 = politicalID1;
    pRoute->mStarID1 = star1;
    pRoute->mStarID2 = star2;
    pRoute->mPoliticalID2 = politicalID2;
    pRoute->mTradeRouteProgress = 0.0f;
    pRoute->mTimeSinceLastUFOMS = 0;
    pRoute->mTimeSinceLastSimMS = 0;

    const Vector3& pos2 = pStar2->GetPosition();
    const Vector3& pos1 = pStar1->GetPosition();
    float dx = pos1.x - pos2.x;
    float dy = pos1.y - pos2.y;
    float dz = pos1.z - pos2.z;
    pRoute->mRouteLength = sqrtf(dx * dx + (dy * dy + dz * dz));

    Vector3 activePos = SP::GetActivePlanet()->GetPosition();
    UpdateRouteLength(pRoute, activePos);

    TradeMessage msg(0xf46092d1);
    msg.SetValue(0, star1);
    msg.SetValue(1, star2);
    msg.SetValue(2, politicalID1);
    msg.SetValue(3, politicalID2);
    MessageServer()->SendMSG(msg.mMessageID, &msg, 0);
}

// @ 0x013a5c20
void FUN_013a5c20(void)
{
    extern char g_55271b4; extern char g_55271ba; extern char g_55271c0; extern char g_55271c4; extern char g_55271c7; extern char g_5540e28; extern char g_5540e44; extern char g_55555c7; extern char g_572810; extern char g_572840; extern char g_675ca0; extern char g_692ca0; extern char g_693090; extern char g_6930b0; extern char g_694f00; extern char g_694fc0; extern char g_ac88f0; extern char g_acbb80; extern char g_b1fbf0;
    AttrRec rec;

    rec.mpName     = "mPoliticalID1";
    rec.mpField    = (void*)&g_55271b4;
    rec.mZero18    = 0;
    rec.mZero1c    = 0;
    rec.mpFn20     = (void*)&g_692ca0;
    rec.mpFn24     = (void*)&g_572810;
    rec.mpFn28     = (void*)&g_572840;
    rec.mpFn2c     = (void*)&g_693090;
    rec.mpFn30     = (void*)&g_694f00;
    rec.mpFn34     = (void*)&g_b1fbf0;
    rec.mpFn38     = (void*)&g_675ca0;
    rec.mFieldOfs  = 4;
    g_t15b7dc0[0] = rec;

    rec.mpName     = "mPoliticalID2";
    rec.mpField    = (void*)&g_55271ba;
    rec.mZero18    = 0;
    rec.mZero1c    = 0;
    rec.mpFn20     = (void*)&g_692ca0;
    rec.mpFn24     = (void*)&g_572810;
    rec.mpFn28     = (void*)&g_572840;
    rec.mpFn2c     = (void*)&g_693090;
    rec.mpFn30     = (void*)&g_694f00;
    rec.mpFn34     = (void*)&g_b1fbf0;
    rec.mpFn38     = (void*)&g_675ca0;
    rec.mFieldOfs  = 8;
    g_t15b7dc0[1] = rec;

    rec.mpName     = "mStarID1";
    rec.mpField    = (void*)&g_55271c0;
    rec.mZero18    = 0;
    rec.mZero1c    = 0;
    rec.mpFn20     = (void*)&g_692ca0;
    rec.mpFn24     = (void*)&g_572810;
    rec.mpFn28     = (void*)&g_572840;
    rec.mpFn2c     = (void*)&g_693090;
    rec.mpFn30     = (void*)&g_694f00;
    rec.mpFn34     = (void*)&g_b1fbf0;
    rec.mpFn38     = (void*)&g_675ca0;
    rec.mFieldOfs  = 0xc;
    g_t15b7dc0[2] = rec;

    rec.mpName     = "mStarID2";
    rec.mpField    = (void*)&g_55271c4;
    rec.mZero18    = 0;
    rec.mZero1c    = 0;
    rec.mpFn20     = (void*)&g_692ca0;
    rec.mpFn24     = (void*)&g_572810;
    rec.mpFn28     = (void*)&g_572840;
    rec.mpFn2c     = (void*)&g_693090;
    rec.mpFn30     = (void*)&g_694f00;
    rec.mpFn34     = (void*)&g_b1fbf0;
    rec.mpFn38     = (void*)&g_675ca0;
    rec.mFieldOfs  = 0x10;
    g_t15b7dc0[3] = rec;

    rec.mpName     = "mTimeSinceLastUFOMS";
    rec.mpField    = (void*)&g_5540e28;
    rec.mZero18    = 0;
    rec.mZero1c    = 0;
    rec.mpFn20     = (void*)&g_692ca0;
    rec.mpFn24     = (void*)&g_572810;
    rec.mpFn28     = (void*)&g_572840;
    rec.mpFn2c     = (void*)&g_693090;
    rec.mpFn30     = (void*)&g_694f00;
    rec.mpFn34     = (void*)&g_b1fbf0;
    rec.mpFn38     = (void*)&g_675ca0;
    rec.mFieldOfs  = 0x1c;
    g_t15b7dc0[4] = rec;

    rec.mpName     = "mTimeSinceLastSimMS";
    rec.mpField    = (void*)&g_5540e44;
    rec.mZero18    = 0;
    rec.mZero1c    = 0;
    rec.mpFn20     = (void*)&g_692ca0;
    rec.mpFn24     = (void*)&g_572810;
    rec.mpFn28     = (void*)&g_572840;
    rec.mpFn2c     = (void*)&g_693090;
    rec.mpFn30     = (void*)&g_694f00;
    rec.mpFn34     = (void*)&g_b1fbf0;
    rec.mpFn38     = (void*)&g_675ca0;
    rec.mFieldOfs  = 0x20;
    g_t15b7dc0[5] = rec;

    rec.mpName     = "mTradeRouteProgress";
    rec.mpField    = (void*)&g_55271c7;
    rec.mZero18    = 0;
    rec.mZero1c    = 0;
    rec.mpFn20     = (void*)&g_692ca0;
    rec.mpFn24     = (void*)&g_572810;
    rec.mpFn28     = (void*)&g_ac88f0;
    rec.mpFn2c     = (void*)&g_6930b0;
    rec.mpFn30     = (void*)&g_694fc0;
    rec.mpFn34     = (void*)&g_b1fbf0;
    rec.mpFn38     = (void*)&g_acbb80;
    rec.mFieldOfs  = 0x14;
    g_t15b7dc0[6] = rec;

    rec.mpName     = "mRouteLength";
    rec.mpField    = (void*)&g_55555c7;
    rec.mZero18    = 0;
    rec.mZero1c    = 0;
    rec.mpFn20     = (void*)&g_692ca0;
    rec.mpFn24     = (void*)&g_572810;
    rec.mpFn28     = (void*)&g_ac88f0;
    rec.mpFn2c     = (void*)&g_6930b0;
    rec.mpFn30     = (void*)&g_694fc0;
    rec.mpFn34     = (void*)&g_b1fbf0;
    rec.mpFn38     = (void*)&g_acbb80;
    rec.mFieldOfs  = 0x24;
    g_t15b7dc0[7] = rec;
}
