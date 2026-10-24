// Slice s00cc4fa0: feedback-event timer map (eastl rbtree of cGonzagoTimer
// values), its node destructor helpers, the tribe controller singleton that
// owns one of those maps and the UI layout reset pass.
//
//  - 00cc4fa0  cFeedbackTimerList::Broadcast
//  - 00cc5010  ForEach (visits every timer node)
//  - 00cc5070  cFeedbackTimerMap::GetRemainingTime
//  - 00cc5100  cFeedbackTimerMap::GetElapsedRatio
//  - 00cc5170  cFeedbackTimerMap::RunEvent
//  - 00cc5230  cEventTimerValue::cEventTimerValue (copy)
//  - 00cc5290  cWorldMapReset
//  - 00cc5340  cTimerMap::Erase
//  - 00cc5390  cTimerMap::NukeSubtree
//  - 00cc53e0  cEventTimerValue::cEventTimerValue (converting)
//  - 00cc54f0  SerializeTimerMap
//  - 00cc5610  SP::cNpcTribeController::~cNpcTribeController
//  - 00cc5700  SP::cNpcTribeController::PurgeTimersAndSerialize
//  - 00cc5850  SP::ValidateHerdLocationsForTribe
//  - 00cc5a70  SP::cNpcTribeController::cNpcTribeController
//  - 00cc5b50  SP::cNpcTribeController::Reset
//  - 00cc5bc0  SP::cNpcTribeController::CollectResourceKeys
//  - 00cc5d40  cCreatureTimerMap::Read
//  - 00cc5ee0  cCreatureTimerMap::operator[]
//  - 00cc5f80  ValidateAllTribes
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"

// ---------------------------------------------------------------------------
// refcounted bases
// ---------------------------------------------------------------------------
class cIRefCounted
{
public:
    virtual int AddRef();                 // +0x00
    virtual int Release();                // +0x04
};

class cFeedbackEvent : public cIRefCounted
{
public:
    virtual void e08();                   // +0x08
    virtual uint32_t GetResourceID(uint32_t nHash);   // +0x0c
    virtual void e10();                   // +0x10
    virtual void e14();                   // +0x14
    virtual void e18();                   // +0x18
    virtual void Activate(void* pArg);    // +0x1c
    virtual void e20();                   // +0x20
    virtual void e24();                   // +0x24
    virtual void e28();                   // +0x28
    virtual bool IsDone();                // +0x2c

    uint8_t  mPad04[0x131];               // +0x04
    uint8_t  mbField135;                  // +0x135
};

// ---------------------------------------------------------------------------
// SP::cSPTimer / SP::cGonzagoTimer
// ---------------------------------------------------------------------------
// 64-bit tick count stored as two words (keeps the class 4-byte aligned, so the
// vfptr stays a single dword and mRefCount lands at +0x04)
struct cTimeValue
{
    uint32_t mLow;                        // +0x00
    uint32_t mHigh;                       // +0x04
};

class cSPTimer
{
public:
    virtual void st00();                  // +0x00
    virtual void st04();                  // +0x04
    uint32_t mRefCount;                   // +0x04
    cTimeValue mElapsedTime;              // +0x08
    cTimeValue mBaseTime;                 // +0x10
    uint8_t  mRunning;                    // +0x18
    uint8_t  mPad19[3];                   // +0x19
    void*    mpfnGetMillisecondTime;      // +0x1c

    cSPTimer();                                          // 0x00bc31c0
    ~cSPTimer();                                         // 0x005725a0
    cSPTimer(const cSPTimer& x)
    {
        mRefCount = 0;
        mElapsedTime = x.mElapsedTime;
        mBaseTime = x.mBaseTime;
        mRunning = x.mRunning;
        mpfnGetMillisecondTime = x.mpfnGetMillisecondTime;
    }
    int64_t GetElapsedTime();                            // 0x00bc3190
};

class cGonzagoTimer : public cSPTimer
{
public:
    cGonzagoTimer();                                     // 0x00b63890
    cGonzagoTimer(const cGonzagoTimer& x) : cSPTimer(x) {}
    ~cGonzagoTimer();                                    // 0x00b638b0
    void Destroy();                                      // 0x00b638b0
    void AddTime(int nDelta);                            // 0x00b638c0
    void Write(void* pSerializer);                       // 0x00b638d0
    void Read(void* pSerializer);                        // 0x00b63930
};

void* RBTreeIncrement(void* pNode);                      // 0x00921580
void  RBTreeErase(void* pNode, void* pAnchor);           // 0x00921880
void  operator_delete_array(void* pMem);                 // 0x00f47380
void* operator_new(uint32_t nSize, const char* pName,
                   int a, int b, int c, int d);          // 0x00f473a0
void* memcpy(void* pDst, const void* pSrc, uint32_t nSize);   // 0x011e0744

// ---------------------------------------------------------------------------
// eastl red/black tree
// ---------------------------------------------------------------------------
struct cTreeNode
{
    cTreeNode* mpNodeRight;               // +0x00
    cTreeNode* mpNodeLeft;                // +0x04
    cTreeNode* mpNodeParent;              // +0x08
    uint8_t    mColor;                    // +0x0c
    uint8_t    mPad0d[3];                 // +0x0d
};

class cKeyRef
{
public:
    cIRefCounted* mpRef;                  // +0x00
    cKeyRef() : mpRef(0) {}
    cKeyRef(cIRefCounted* p) : mpRef(p) { if (mpRef) mpRef->AddRef(); }
    cKeyRef(const cKeyRef& x) : mpRef(x.mpRef) { if (mpRef) mpRef->AddRef(); }
};

// value stored in a timer map node (node + 0x10)
struct cEventTimerValue
{
    cKeyRef       mKey;                   // +0x00
    uint32_t      mPad04;                 // +0x04
    cGonzagoTimer mTimer;                 // +0x08

    cEventTimerValue(const cEventTimerValue& x);
    cEventTimerValue(cIRefCounted** ppKey, const cGonzagoTimer& timer);
    cEventTimerValue& operator=(const cEventTimerValue& x)
    {
        mKey = x.mKey;
        mTimer = x.mTimer;
        return *this;
    }

    cFeedbackEvent* Event() { return (cFeedbackEvent*)mKey.mpRef; }
};

struct cTimerNode : public cTreeNode
{
    cEventTimerValue mValue;              // +0x10
};

class cTimerMap
{
public:
    uint32_t    mCompare;                 // +0x00
    cTreeNode*  mpNodeLeft;               // +0x04  (anchor)
    cTreeNode*  mpNodeRight;              // +0x08
    cTreeNode*  mpNodeParent;             // +0x0c
    uint8_t     mColor;                   // +0x10
    int32_t     mnSize;                   // +0x14

    cTimerNode* begin() { return (cTimerNode*)mpNodeRight; }
    cTimerNode* end() { return (cTimerNode*)&mpNodeLeft; }
    int32_t size() const { return mnSize; }

    void DoNukeSubtree(cTreeNode* pNode);                  // 0x009a9600
    void NukeSubtree(cTimerNode* pNode);                   // 0x00cc5390
    void Erase(cTimerNode** ppNext, cTimerNode* pNode);    // 0x00cc5340
    void find(cTimerNode** ppOut, cFeedbackEvent** ppKey); // 0x00e5c780
    void InsertNode(cTreeNode** ppOut, int nZero,
                    cEventTimerValue* pValue, int nFlag);  // 0x00cc5c70
    void reset();
    ~cTimerMap() { NukeSubtree((cTimerNode*)mpNodeParent); }
};

// node of the global UI world map (keyed by layout id)
struct cWorldNode
{
    cWorldNode* mpNodeRight;              // +0x00
    cWorldNode* mpNodeLeft;               // +0x04
    cWorldNode* mpNodeParent;             // +0x08
    uint8_t     mColor;                   // +0x0c
    uint8_t     mPad0d[3];                // +0x0d
    uint32_t    mID;                      // +0x10
};

class cWorldMap
{
public:
    uint32_t     mCompare;                // +0x00
    cWorldNode*  mpNodeLeft;              // +0x04  (anchor)
    cWorldNode*  mpNodeRight;             // +0x08
    cWorldNode*  mpNodeParent;            // +0x0c
    uint8_t      mColor;                  // +0x10
    int32_t      mnSize;                  // +0x14
    void DoNukeSubtree(cWorldNode* pNode);                    // 0x009a9600
    void reset();
};

extern cWorldMap gWorldMap;               // 0x0157ea18
extern int64_t  gTimeLimit;               // 0x015812c0
extern int      gTimeBonus;               // 0x015812c8
extern wchar_t  gEmptyString16[];         // 0x01667bac

// ---------------------------------------------------------------------------
// planet model / UI layout manager
// ---------------------------------------------------------------------------
class cVector3
{
public:
    float x, y, z;
};

class cPlanetModel;
cPlanetModel* PlanetModel();                                  // 0x00b3d350

class cWorldOwner
{
public:
    virtual void w00(); virtual void w01(); virtual void w02(); virtual void w03();
    virtual void w04(); virtual void w05(); virtual void w06(); virtual void w07();
    virtual void w08(); virtual void w09(); virtual void w10(); virtual void w11();
    virtual void w12(); virtual void w13(); virtual void w14(); virtual void w15();
    virtual void w16(); virtual void w17(); virtual void w18(); virtual void w19();
    virtual void w20(); virtual void w21(); virtual void w22(); virtual void w23();
    virtual void w24(); virtual void w25(); virtual void w26(); virtual void w27();
    virtual void w28(); virtual void w29(); virtual void w30(); virtual void w31();
    virtual void w32(); virtual void w33(); virtual void w34(); virtual void w35();
    virtual void w36(); virtual void w37(); virtual void w38(); virtual void w39();
    virtual void w40(); virtual void w41(); virtual void w42(); virtual void w43();
    virtual void w44(); virtual void w45(); virtual void w46(); virtual void w47();
    virtual void NotifyWorldRemoved(uint32_t nID);            // +0xc0
};

class cPlanetModel
{
public:
    uint32_t pad00[(0x24) / 4];
    cWorldOwner* mpWorldOwner;            // +0x24
};

// ---------------------------------------------------------------------------
// resource manager (broadcast target)
// ---------------------------------------------------------------------------
struct cResourceKey8
{
    uint32_t mPad;                        // +0x00
    uint32_t mCount;                      // +0x04
    uint32_t mID;                         // +0x08  (kept last: written after the others)
    cResourceKey8(uint32_t nID) : mPad(0), mCount(4), mID(nID) {}
};

class cResourceManager
{
public:
    virtual void r00(); virtual void r01(); virtual void r02(); virtual void r03();
    virtual void r04(); virtual void r05(); virtual void r06(); virtual void r07();
    virtual void r08(); virtual void r09(); virtual void r10(); virtual void r11();
    virtual void r12(); virtual void r13(); virtual void r14(); virtual void r15();
    virtual void r16(); virtual void r17(); virtual void r18();
    virtual void RegisterObject(void* pObject, cResourceKey8 key);   // +0x4c
};

cResourceManager* GetResourceManager();                       // 0x00401010

// ---------------------------------------------------------------------------
// serializer plumbing used by the map read/write helpers
// ---------------------------------------------------------------------------
namespace EA { namespace IO { class IStream; } }

class cStreamOwner
{
public:
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10(); virtual void s14();
    virtual EA::IO::IStream* GetStream();                 // +0x18
};

class cSerializer
{
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18();
    virtual void BeginEntry();                            // +0x1c
    virtual cStreamOwner* GetOwner();                     // +0x20
    virtual void v24();                                   // +0x24
    virtual void ReadObject(uint32_t nID, cFeedbackEvent** ppEvent, int nFlags);  // +0x28
    virtual void WriteValue(uint32_t nValue);             // +0x2c
};

bool EA_IO_WriteUint32(EA::IO::IStream* pStream, const uint32_t* pValue,
                       uint32_t nCount, int nFlags);      // 0x0093aa70
bool EA_IO_ReadInt32(EA::IO::IStream* pStream, uint32_t* pValue,
                     uint32_t nCount, int nFlags);        // 0x0093a780

class cVarListSerializer
{
public:
    uint8_t mData[0xa14];
    cVarListSerializer(void* pOwner, void* pVarList, const char* pszName);  // 0x00692f90
    bool Serialize(void* pStream);                                          // 0x00692900
};

// ---------------------------------------------------------------------------
// eastl-like containers with the SP allocation header
// ---------------------------------------------------------------------------
template <class T>
class cSpVector
{
public:
    T* mpBegin;                           // +0x00
    T* mpEnd;                             // +0x04
    T* mpCapacity;                        // +0x08
    void clear() { mpEnd = mpBegin; }
    ~cSpVector()
    {
        if (mpBegin && *(int*)((char*)mpBegin - 4) != 0)
            operator_delete_array(mpBegin);
    }
};

class cShortString16
{
public:
    wchar_t* mpBegin;                     // +0x00
    wchar_t* mpEnd;                       // +0x04
    wchar_t* mpCapacity;                  // +0x08
    ~cShortString16()
    {
        if (((uint32_t)(mpCapacity - mpBegin) << 1) > 2 && mpBegin)
            operator_delete_array(mpBegin);
    }
};

struct cResourceKey
{
    uint32_t mID;                         // +0x00
    uint32_t mPad;                        // +0x04
    uint32_t mCount;                      // +0x08
};

// ===========================================================================
// cFeedbackTimerList
// ===========================================================================
class cFeedbackTimerList
{
public:
    void Broadcast();
    uint32_t pad00[(0xd0) / 4];
    void**   mppObjects;                  // +0xd0
    void**   mppEnd;                      // +0xd4
};

// ===========================================================================
// @ 0x00cc4fa0
// ===========================================================================
void __declspec(noinline) cFeedbackTimerList::Broadcast()
{
    uint32_t nCount = (uint32_t)(mppEnd - mppObjects);
    for (uint32_t i = 0; i < nCount; ++i)
    {
        void* pObject = mppObjects[i];
        if (pObject)
        {
            cResourceManager* pManager = GetResourceManager();
            cResourceKey8 key(0x609b763);
            pManager->RegisterObject((char*)pObject + 0x504, key);
        }
    }
}

class cTimerFactory
{
public:
    void InitTimer(cGonzagoTimer* pTimer, void* pConfig,
                   const wchar_t* pszName);                    // 0x00695b40
};

// ===========================================================================
// @ 0x00cc5010
// ===========================================================================
bool __declspec(noinline) ForEach(cTimerFactory* pFactory, cTimerMap* pMap)
{
    cTimerNode* pEnd = pMap->end();
    cTimerNode* pNode = pMap->begin();
    while (pNode != pEnd)
    {
        cFeedbackEvent* pEvent = pNode->mValue.Event();
        if (pEvent)
            pEvent->Activate(pFactory);
        cGonzagoTimer* pTimer = &pNode->mValue.mTimer;
        if (pTimer)
            pFactory->InitTimer(pTimer, (void*)0x145b9a0, (const wchar_t*)0x156ad88);
        pNode = (cTimerNode*)RBTreeIncrement(pNode);
    }
    return true;
}

// ===========================================================================
// cFeedbackTimerMap
// ===========================================================================
class cFeedbackTimerMap
{
public:
    int64_t GetRemainingTime(cFeedbackEvent* pEvent);
    long double GetElapsedRatio(cFeedbackEvent* pEvent);
    void    RunEvent(cFeedbackEvent* pEvent);

    uint32_t pad00[(0x60) / 4];
    cTimerMap mTimers;                    // +0x60
};

// ===========================================================================
// @ 0x00cc5070
// ===========================================================================
int64_t __declspec(noinline) cFeedbackTimerMap::GetRemainingTime(cFeedbackEvent* pEvent)
{
    if (pEvent)
        pEvent->AddRef();

    cTimerNode* pNode;
    mTimers.find(&pNode, &pEvent);

    if (pEvent)
        pEvent->Release();

    if (pNode == mTimers.end())
        return 0;

    int nRemaining = (int)gTimeLimit - (int)pNode->mValue.mTimer.GetElapsedTime();
    return (int64_t)((nRemaining > 0) ? nRemaining : 0);
}

// ===========================================================================
// @ 0x00cc5100
// ===========================================================================
long double __declspec(noinline) cFeedbackTimerMap::GetElapsedRatio(cFeedbackEvent* pEvent)
{
    long double nRemaining = (long double)GetRemainingTime(pEvent);
    return 1.0L - nRemaining / (long double)gTimeLimit;
}

// ===========================================================================
// @ 0x00cc5170
// ===========================================================================
void __declspec(noinline) cFeedbackTimerMap::RunEvent(cFeedbackEvent* pEvent)
{
    if (pEvent)
        pEvent->AddRef();

    cTimerNode* pNode;
    mTimers.find(&pNode, &pEvent);

    if (pEvent)
        pEvent->Release();

    if (pNode != mTimers.end())
        pNode->mValue.mTimer.AddTime(gTimeBonus);
}

// ===========================================================================
// @ 0x00cc5230
// ===========================================================================
cEventTimerValue::cEventTimerValue(const cEventTimerValue& x)
    : mKey(x.mKey), mTimer(x.mTimer)
{
}

// ===========================================================================
// cWorldMapReset
// ===========================================================================
void cWorldMap::reset()
{
    mpNodeLeft = (cWorldNode*)&mpNodeLeft;
    mpNodeRight = (cWorldNode*)&mpNodeLeft;
    mpNodeParent = 0;
    mColor = 0;
    mnSize = 0;
}

// ===========================================================================
// @ 0x00cc5290
// ===========================================================================
void __declspec(noinline) cWorldMapReset()
{
    cPlanetModel* pModel = PlanetModel();
    if (pModel)
    {
        cWorldOwner* pOwner = PlanetModel()->mpWorldOwner;
        if (pOwner)
        {
            for (cWorldNode* pNode = gWorldMap.mpNodeRight;
                 pNode != (cWorldNode*)&gWorldMap.mpNodeLeft;
                 pNode = (cWorldNode*)RBTreeIncrement(pNode))
            {
                if (pNode->mID != 0xffffffff)
                    pOwner->NotifyWorldRemoved(pNode->mID);
            }
        }
    }

    cWorldNode* pNode = gWorldMap.mpNodeParent;
    while (pNode)
    {
        gWorldMap.DoNukeSubtree(pNode->mpNodeRight);
        cWorldNode* pNext = pNode->mpNodeLeft;
        operator_delete_array(pNode);
        pNode = pNext;
    }

    gWorldMap.reset();
}

// ===========================================================================
// @ 0x00cc5340
// ===========================================================================
void __declspec(noinline) cTimerMap::Erase(cTimerNode** ppNext, cTimerNode* pNode)
{
    --mnSize;
    cTreeNode* pNext = (cTreeNode*)RBTreeIncrement(pNode);
    RBTreeErase(pNode, &mpNodeLeft);
    pNode->mValue.mTimer.Destroy();
    if (pNode->mValue.Event())
        pNode->mValue.Event()->Release();
    operator_delete_array(pNode);
    *ppNext = (cTimerNode*)pNext;
}

// ===========================================================================
// @ 0x00cc5390
// ===========================================================================
void __declspec(noinline) cTimerMap::NukeSubtree(cTimerNode* pNode)
{
    while (pNode)
    {
        NukeSubtree((cTimerNode*)pNode->mpNodeRight);
        cTimerNode* pNext = (cTimerNode*)pNode->mpNodeLeft;
        pNode->mValue.mTimer.Destroy();
        if (pNode->mValue.Event())
            pNode->mValue.Event()->Release();
        operator_delete_array(pNode);
        pNode = pNext;
    }
}

void cTimerMap::reset()
{
    mpNodeLeft = (cTreeNode*)&mpNodeLeft;
    mpNodeRight = (cTreeNode*)&mpNodeLeft;
    mpNodeParent = 0;
    mColor = 0;
    mnSize = 0;
}

// ===========================================================================
// @ 0x00cc53e0
// ===========================================================================
cEventTimerValue::cEventTimerValue(cIRefCounted** ppKey, const cGonzagoTimer& timer)
    : mKey(*ppKey), mTimer(timer)
{
}

// ===========================================================================
// @ 0x00cc54f0
// ===========================================================================
void __declspec(noinline) SerializeTimerMap(cSerializer* pSerializer, cTimerMap* pMap)
{
    EA::IO::IStream* pStream = pSerializer->GetOwner()->GetStream();
    uint32_t nSize = (uint32_t)pMap->mnSize;
    EA_IO_WriteUint32(pStream, &nSize, 1, 0);

    for (cTimerNode* pNode = pMap->begin(); pNode != pMap->end();
         pNode = (cTimerNode*)RBTreeIncrement(pNode))
    {
        uint32_t nID = 0;
        cFeedbackEvent* pEvent = pNode->mValue.Event();
        if (pEvent)
            nID = pEvent->GetResourceID(0x179c807);
        pSerializer->WriteValue(nID);
        pSerializer->BeginEntry();
        pNode->mValue.mTimer.Write(pSerializer);
        pSerializer->BeginEntry();
    }
    pSerializer->BeginEntry();
}

// ===========================================================================
// terrain sphere handle embedded in the tribe controller
// ===========================================================================
class cITerrainSphereRef
{
public:
    virtual void i00(); virtual void i04(); virtual void i08(); virtual void i0c();
    virtual void i10(); virtual void i14(); virtual void i18(); virtual void i1c();
    virtual void i20(); virtual void i24(); virtual void i28(); virtual void i2c();
    virtual void i30(); virtual void i34(); virtual void i38(); virtual void i3c();
    virtual void i40(); virtual void i44(); virtual void i48(); virtual void i4c();
    virtual void i50(); virtual void i54();
    virtual bool IsTracking();                            // +0x58
    virtual void i5c(); virtual void i60(); virtual void i64(); virtual void i68();
    virtual void i6c(); virtual void i70(); virtual void i74(); virtual void i78();
    virtual void i7c(); virtual void i80(); virtual void i84(); virtual void i88();
    virtual void i8c(); virtual void i90(); virtual void i94(); virtual void i98();
    virtual void i9c(); virtual void ia0(); virtual void ia4(); virtual void ia8();
    virtual void iac(); virtual void ib0(); virtual void ib4();
    virtual uint32_t AddVertexObject(void* pVec);         // +0xb8
    uint32_t mPad04;                                      // +0x04
};

// ===========================================================================
// SP::cNpcTribeController
// ===========================================================================
class cRefCountBase
{
public:
    virtual void r00(); virtual void r04(); virtual void r08(); virtual void r0c();
    virtual void r10(); virtual void r14(); virtual void r18(); virtual void r1c();
    virtual void r20(); virtual void r24(); virtual void r28();
    virtual cVector3* GetHerdPosition();                  // +0x2c
    virtual void r30(); virtual void r34(); virtual void r38(); virtual void r3c();
    virtual void r40(); virtual void r44(); virtual void r48(); virtual void r4c();
    virtual void r50(); virtual void r54(); virtual void r58(); virtual void r5c();
    virtual long double GetHerdRadius();                  // +0x60
    virtual ~cRefCountBase();                             // 0x00b5b690
};

class cIUnknown32
{
public:
    virtual void u00(); virtual void u04(); virtual void u08(); virtual void u0c();
    virtual ~cIUnknown32();
    uint32_t mPad04;                      // +0x04
};

class cSimSingletonBase : public cRefCountBase, public cIUnknown32
{
public:
    cSimSingletonBase();                                  // 0x00b5b6f0
    virtual ~cSimSingletonBase();
};

class cTribeModeStrategy
{
public:
    static cTribeModeStrategy* Instance();                // 0x00cd40b0
    uint32_t pad00[(0x2c) / 4];
    uint8_t* mpHerdSets;                  // +0x2c
    uint8_t* mpHerdSetsEnd;               // +0x30
};

class cVertex3DVec;

class cNpcTribeController;
class cSPVectorKeys;

extern cNpcTribeController* gNpcTribeSingleton;           // 0x0169b054

class cNpcTribeController : public cSimSingletonBase
{
public:
    ~cNpcTribeController();                               // 0x00cc5610
    cNpcTribeController();                                // 0x00cc5a70
    void PurgeTimersAndSerialize(void* pStream);          // 0x00cc5700
    void Reset();                                         // 0x00cc5b50
    void CollectResourceKeys(cSPVectorKeys* pOut);        // 0x00cc5bc0

    cGonzagoTimer        mGrowthUpdateTimer;   // +0x10
    cGonzagoTimer        mGrowthEventTimer;    // +0x30
    cShortString16       mStatusString;        // +0x50
    cTimerMap            mBabyGrowthTimers;    // +0x60
    cSpVector<cVector3>  mHerdPoints;          // +0x7c
    uint32_t             mField88;             // +0x88
    uint32_t             mField8C;             // +0x8c
    uint32_t             mField90;             // +0x90
    uint8_t              mHerdInline[0x3c];    // +0x94
    cSpVector<void*>     mResourceObjects;     // +0xd0
    uint32_t             mPadDC[2];            // +0xdc
    uint32_t             mFieldE4;             // +0xe4
    uint8_t              mResourceInline[0x14];// +0xe8
    uint32_t             mFieldFC;             // +0xfc
    uint8_t              mPad100[0x20];        // +0x100
    cITerrainSphereRef   mHerdSphere;          // +0x120
};

// ===========================================================================
// @ 0x00cc5610
// ===========================================================================
cNpcTribeController::~cNpcTribeController()
{
}

// ===========================================================================
// @ 0x00cc5700
// ===========================================================================
void __declspec(noinline) cNpcTribeController::PurgeTimersAndSerialize(void* pStream)
{
    cTimerMap* pMap = &mBabyGrowthTimers;
    cTimerNode* pNode = pMap->begin();
    while (pNode != pMap->end())
    {
        cFeedbackEvent* pEvent = pNode->mValue.Event();
        if (pEvent && !pEvent->IsDone() && pEvent->mbField135)
        {
            pNode = (cTimerNode*)RBTreeIncrement(pNode);
            continue;
        }
        cTimerNode* pNext;
        pMap->Erase(&pNext, pNode);
        pNode = pNext;
    }

    cVarListSerializer serializer(this, (void*)0x157ea38, (const char*)0x1a80d26);
    serializer.Serialize(pStream);
}

// ===========================================================================
// SP::ValidateHerdLocationsForTribe
// ===========================================================================
struct cVertexDesc
{
    uint32_t mID;                         // +0x00
    uint32_t mPad04;                      // +0x04
    uint32_t mPad08;                      // +0x08
    uint32_t mPad0c;                      // +0x0c
    float    mx;                          // +0x10
    float    my;                          // +0x14
    float    mz;                          // +0x18
    uint32_t mType;                       // +0x1c
    uint32_t mField20;                    // +0x20
    uint32_t mScale;                      // +0x24
    uint32_t mField28;                    // +0x28
};

class cVertex3DVec
{
public:
    cVertexDesc* mpBegin;                 // +0x00
    cVertexDesc* mpEnd;                   // +0x04
    cVertexDesc* mpCapacity;              // +0x08
    void Reserve(uint32_t nCount);                               // 0x00cc5440
    void push_back(const cVertexDesc& value);                    // 0x00b85db0
};

class cPlanetSphere
{
public:
    void DirectionToSurfacePosition(cVector3* pOut, const cVector3* pDir);  // 0x00b815a0
};

class cRBT
{
public:
    void Insert(void* pEntry, void* pKey, uint8_t nFlags);       // 0x007d0850
};

extern cRBT gWorldRBT;                    // 0x0157ea18

void ValidateHerdLocationsForTribe(cNpcTribeController* pTribe);   // 0x00cc5850

// ===========================================================================
// @ 0x00cc5850
// ===========================================================================
void __declspec(noinline) ValidateHerdLocationsForTribe(cNpcTribeController* pTribe)
{
    if (pTribe->mHerdSphere.IsTracking())
        return;

    cPlanetModel* pModel = PlanetModel();
    cWorldOwner* pOwner = pModel->mpWorldOwner;
    if (!pOwner)
        return;

    cTribeModeStrategy* pStrategy = cTribeModeStrategy::Instance();
    if (pStrategy->mpHerdSets == pStrategy->mpHerdSetsEnd)
        return;

    long double dRadius = pTribe->GetHerdRadius();
    int nSets = (int)((pStrategy->mpHerdSetsEnd - pStrategy->mpHerdSets) / 0x14);
    if (!nSets)
        return;

    for (int i = 0; i < nSets; ++i)
    {
        cVertex3DVec* pPoints = (cVertex3DVec*)(pStrategy->mpHerdSets + i * 0x14);
        if (pPoints->mpBegin == pPoints->mpEnd)
            continue;

        cVector3* pHerd = pTribe->GetHerdPosition();
        float dy = pPoints->mpEnd[-1].my - pHerd->y;
        float dx = pPoints->mpEnd[-1].mx - pHerd->x;
        float dz = pPoints->mpEnd[-1].mz - pHerd->z;
        if (dx * dx + dy * dy + dz * dz > (float)(dRadius * dRadius))
            continue;

        cVertex3DVec* pVec = (cVertex3DVec*)operator_new(0x18, "Simulator", 0, 0, 0, 0);
        if (pVec)
        {
            pVec->mpBegin = 0;
            pVec->mpEnd = 0;
            pVec->mpCapacity = 0;
        }
        pVec->Reserve((uint32_t)(pPoints->mpEnd - pPoints->mpBegin));

        cVertexDesc* pEnd = pPoints->mpEnd;
        for (cVertexDesc* pPoint = pPoints->mpBegin; pPoint != pEnd; ++pPoint)
        {
            cVector3 pos;
            ((cPlanetSphere*)pModel)->DirectionToSurfacePosition(&pos, (const cVector3*)pPoint);
            cVertexDesc desc;
            desc.mID = 0x53496b14;
            desc.mPad04 = 0xffffffff;
            desc.mPad08 = 0;
            desc.mPad0c = 0;
            desc.mx = pos.x;
            desc.my = pos.y;
            desc.mz = pos.z;
            desc.mType = 0x3f800000;
            desc.mField20 = 0x3f0b8b8c;
            desc.mScale = 0x3e8a8a8b;
            desc.mField28 = 0x3d989899;
            pVec->push_back(desc);
        }

        uint32_t nID = pTribe->mHerdSphere.AddVertexObject(pVec);
        gWorldRBT.Insert(&nID, (void*)0, 0);
    }
}

// ===========================================================================
// @ 0x00cc5a70
// ===========================================================================
cNpcTribeController::cNpcTribeController()
{
    gNpcTribeSingleton = this;

    mStatusString.mpCapacity = gEmptyString16 + 1;
    mStatusString.mpBegin = gEmptyString16;
    mStatusString.mpEnd = gEmptyString16;

    mBabyGrowthTimers.mpNodeLeft = 0;
    mBabyGrowthTimers.mpNodeRight = 0;
    mBabyGrowthTimers.mpNodeParent = 0;
    mBabyGrowthTimers.mpNodeLeft = (cTreeNode*)&mBabyGrowthTimers.mpNodeLeft;
    mBabyGrowthTimers.mpNodeRight = (cTreeNode*)&mBabyGrowthTimers.mpNodeLeft;
    mBabyGrowthTimers.mpNodeParent = 0;
    mBabyGrowthTimers.mColor = 0;
    mBabyGrowthTimers.mnSize = 0;

    mHerdPoints.mpBegin = (cVector3*)mHerdInline;
    mHerdPoints.mpEnd = (cVector3*)mHerdInline;
    mHerdPoints.mpCapacity = (cVector3*)(mHerdInline + 0x3c);
    mField90 = 0;

    mResourceObjects.mpBegin = (void**)mResourceInline;
    mResourceObjects.mpEnd = (void**)mResourceInline;
    mResourceObjects.mpCapacity = (void**)&mFieldFC;
    mFieldE4 = 0;
    mFieldFC = 0;
}

// ===========================================================================
// @ 0x00cc5b50
// ===========================================================================
void __declspec(noinline) cNpcTribeController::Reset()
{
    mBabyGrowthTimers.NukeSubtree((cTimerNode*)mBabyGrowthTimers.mpNodeParent);
    mBabyGrowthTimers.reset();
    cWorldMapReset();
    mHerdPoints.mpEnd = mHerdPoints.mpBegin;
    mResourceObjects.clear();
}

// ===========================================================================
// CollectResourceKeys helpers
// ===========================================================================
class cSPEditorSpeciesManager
{
public:
    static cSPEditorSpeciesManager* Get();                // 0x00401090
    void* GetAvatarProfile();                             // 0x004df420
};

class cSPVectorKeys
{
public:
    cResourceKey* mpBegin;                // +0x00
    cResourceKey* mpEnd;                  // +0x04
    cResourceKey* mpCapacity;             // +0x08
    void Reserve(uint32_t nCount);                                        // 0x0041e4d0
    void DoInsertKey(cResourceKey* pWhere, const cResourceKey& key);      // 0x004e3e10
};

class cGameObject
{
public:
    uint8_t pad00[0x504];
    cResourceKey mKey;                    // +0x504
};

// ===========================================================================
// @ 0x00cc5bc0
// ===========================================================================
void __declspec(noinline) cNpcTribeController::CollectResourceKeys(cSPVectorKeys* pOut)
{
    cSPEditorSpeciesManager* pManager = cSPEditorSpeciesManager::Get();
    void* pAvatarProfile = pManager->GetAvatarProfile();

    uint32_t nCount = (uint32_t)(pOut->mpEnd - pOut->mpBegin)
                    + (uint32_t)(mResourceObjects.mpEnd - mResourceObjects.mpBegin);
    pOut->Reserve(nCount);

    for (void** ppObject = mResourceObjects.mpBegin;
         ppObject != mResourceObjects.mpEnd; ++ppObject)
    {
        cGameObject* pObject = (cGameObject*)*ppObject;
        if (!pObject || pObject == pAvatarProfile)
            continue;

        if (pOut->mpEnd < pOut->mpCapacity)
        {
            cResourceKey* pKey = pOut->mpEnd;
            pOut->mpEnd = pKey + 1;
            if (pKey)
                *pKey = pObject->mKey;
        }
        else
        {
            pOut->DoInsertKey(pOut->mpEnd, pObject->mKey);
        }
    }
}

// ===========================================================================
// cCreatureTimerMap (same node/value shape as cTimerMap)
// ===========================================================================
class cCreatureTimerMap : public cTimerMap
{
public:
    void Read(cSerializer* pSerializer);                     // 0x00cc5d40
    cGonzagoTimer& operator[](cIRefCounted** ppKey);         // 0x00cc5ee0
};

// ===========================================================================
// @ 0x00cc5d40
// ===========================================================================
void __declspec(noinline) cCreatureTimerMap::Read(cSerializer* pSerializer)
{
    NukeSubtree((cTimerNode*)mpNodeParent);
    reset();

    EA::IO::IStream* pStream = pSerializer->GetOwner()->GetStream();
    uint32_t nCount = 0;
    EA_IO_ReadInt32(pStream, &nCount, 1, 0);

    for (uint32_t i = 0; i < nCount; ++i)
    {
        cGonzagoTimer timer;
        cFeedbackEvent* pEvent = 0;
        pSerializer->ReadObject(0xce9f6639, &pEvent, 0);
        pSerializer->BeginEntry();
        timer.Read(pSerializer);
        pSerializer->BeginEntry();

        cKeyRef key(pEvent);
        cEventTimerValue value(&key.mpRef, timer);
        cTimerNode* pNode = 0;
        InsertNode((cTreeNode**)&pNode, 0, &value, 0);
        if (pNode)
            pNode->mValue.mTimer = timer;
        if (pEvent)
            pEvent->Release();
    }
    pSerializer->BeginEntry();
}

// ===========================================================================
// @ 0x00cc5ee0
// ===========================================================================
__declspec(noinline) cGonzagoTimer& cCreatureTimerMap::operator[](cIRefCounted** ppKey)
{
    cTreeNode* pAnchor = (cTreeNode*)&mpNodeLeft;
    cTreeNode* pNode = mpNodeParent;
    cTreeNode* pParent = pAnchor;
    while (pNode)
    {
        cTimerNode* pTimerNode = (cTimerNode*)pNode;
        if ((uint32_t)pTimerNode->mValue.mKey.mpRef < (uint32_t)*ppKey)
        {
            pNode = pNode->mpNodeRight;
        }
        else
        {
            pParent = pNode;
            pNode = pNode->mpNodeLeft;
        }
    }

    if (pParent == pAnchor
        || (uint32_t)*ppKey < (uint32_t)((cTimerNode*)pParent)->mValue.mKey.mpRef)
    {
        cGonzagoTimer timer;
        cEventTimerValue value(ppKey, timer);
        cTreeNode* pResult = 0;
        InsertNode(&pResult, 0, &value, 0);
        pParent = pResult;
    }
    return *(cGonzagoTimer*)((char*)pParent + 0x18);
}

// ===========================================================================
// ValidateAllTribes
// ===========================================================================
class cGameDataVector
{
public:
    uint32_t* mpBegin;                    // +0x00
    uint32_t* mpEnd;                      // +0x04
    uint32_t* mpCapacity;                 // +0x08
};

class cGameNounManager
{
public:
    void SetGameDataOwner2();                             // 0x00bfc5f0
    cGameDataVector* GetGameDataVector(void* a, void* b, void* c, void* d,
                                       const char* pszName);   // 0x00b21340
};

cGameNounManager* NounManager();                          // 0x00b3d300

// ===========================================================================
// @ 0x00cc5f80
// ===========================================================================
void __declspec(noinline) ValidateAllTribes()
{
    NounManager()->SetGameDataOwner2();

    cGameDataVector* pVector = NounManager()->GetGameDataVector(
        (void*)0x00cd7d10, (void*)0x00d3d420, (void*)0x00accbb0,
        (void*)0x00b1e500, (const char*)0x018c6d19);

    uint32_t* pBegin = pVector->mpBegin;
    uint32_t nCount = (uint32_t)(pVector->mpEnd - pBegin);
    for (uint32_t i = 0; i < nCount; ++i)
        ValidateHerdLocationsForTribe((cNpcTribeController*)pBegin[i]);
}
