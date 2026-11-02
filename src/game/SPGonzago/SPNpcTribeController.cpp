// src/game/SPGonzago/SPNpcTribeController.cpp -- migrated from slice(s) s00cc5fe0, s0135d100, s00cc4fa0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPNpcTribeController.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cTerrainSphere.h"
#include "SP/cTribeTool.h"

// ---- items of slice s00cc4fa0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int64_t  gTimeLimit;               // 0x015812c0
extern int      gTimeBonus;               // 0x015812c8
extern wchar_t  gEmptyString16[];         // 0x01667bac
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
virtual void w00();
virtual void w01();
virtual void w02();
virtual void w03();
virtual void w04();
virtual void w05();
virtual void w06();
virtual void w07();
virtual void w08();
virtual void w09();
virtual void w10();
virtual void w11();
virtual void w12();
virtual void w13();
virtual void w14();
virtual void w15();
virtual void w16();
virtual void w17();
virtual void w18();
virtual void w19();
virtual void w20();
virtual void w21();
virtual void w22();
virtual void w23();
virtual void w24();
virtual void w25();
virtual void w26();
virtual void w27();
virtual void w28();
virtual void w29();
virtual void w30();
virtual void w31();
virtual void w32();
virtual void w33();
virtual void w34();
virtual void w35();
virtual void w36();
virtual void w37();
virtual void w38();
virtual void w39();
virtual void w40();
virtual void w41();
virtual void w42();
virtual void w43();
virtual void w44();
virtual void w45();
virtual void w46();
virtual void w47();
    virtual void NotifyWorldRemoved(uint32_t nID);            // +0xc0
};
class cPlanetModel
{
public:
    uint32_t pad00[(0x24) / 4];
    cWorldOwner* mpWorldOwner;            // +0x24
};
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
virtual void r00();
virtual void r01();
virtual void r02();
virtual void r03();
virtual void r04();
virtual void r05();
virtual void r06();
virtual void r07();
virtual void r08();
virtual void r09();
virtual void r10();
virtual void r11();
virtual void r12();
virtual void r13();
virtual void r14();
virtual void r15();
virtual void r16();
virtual void r17();
virtual void r18();
    virtual void RegisterObject(void* pObject, cResourceKey8 key);   // +0x4c
};
cResourceManager* GetResourceManager();                       // 0x00401010
namespace EA {
namespace IO {
 class IStream_s00cc_4fa0; 
}
}
class cStreamOwner
{
public:
virtual void s00();
virtual void s04();
virtual void s08();
virtual void s0c();
virtual void s10();
virtual void s14();
    virtual EA::IO::IStream_s00cc_4fa0* GetStream();                 // +0x18
};
class cSerializer
{
public:
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
    virtual void BeginEntry();                            // +0x1c
    virtual cStreamOwner* GetOwner();                     // +0x20
    virtual void v24();                                   // +0x24
    virtual void ReadObject(uint32_t nID, cFeedbackEvent** ppEvent, int nFlags);  // +0x28
    virtual void WriteValue(uint32_t nValue);             // +0x2c
};
bool EA_IO_WriteUint32(EA::IO::IStream_s00cc_4fa0* pStream, const uint32_t* pValue,
                       uint32_t nCount, int nFlags);      // 0x0093aa70
bool EA_IO_ReadInt32(EA::IO::IStream_s00cc_4fa0* pStream, uint32_t* pValue,
                     uint32_t nCount, int nFlags);        // 0x0093a780
class cVarListSerializer
{
public:
    uint8_t mData[0xa14];
    cVarListSerializer(void* pOwner, void* pVarList, const char* pszName);  // 0x00692f90
    bool Serialize(void* pStream);                                          // 0x00692900
};
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
class cFeedbackTimerList
{
public:
    void Broadcast();
    uint32_t pad00[(0xd0) / 4];
    void**   mppObjects;                  // +0xd0
    void**   mppEnd;                      // +0xd4
};
class cTimerFactory
{
public:
    void InitTimer(cGonzagoTimer* pTimer, void* pConfig,
                   const wchar_t* pszName);                    // 0x00695b40
};
class cFeedbackTimerMap
{
public:
    int64_t GetRemainingTime(cFeedbackEvent* pEvent);
    long double GetElapsedRatio(cFeedbackEvent* pEvent);
    void    RunEvent(cFeedbackEvent* pEvent);

    uint32_t pad00[(0x60) / 4];
    cTimerMap mTimers;                    // +0x60
};
void cWorldMap::reset()
{
    mpNodeLeft = (cWorldNode*)&mpNodeLeft;
    mpNodeRight = (cWorldNode*)&mpNodeLeft;
    mpNodeParent = 0;
    mColor = 0;
    mnSize = 0;
}
void cTimerMap::reset()
{
    mpNodeLeft = (cTreeNode*)&mpNodeLeft;
    mpNodeRight = (cTreeNode*)&mpNodeLeft;
    mpNodeParent = 0;
    mColor = 0;
    mnSize = 0;
}
class cITerrainSphereRef
{
public:
virtual void i00();
virtual void i04();
virtual void i08();
virtual void i0c();
virtual void i10();
virtual void i14();
virtual void i18();
virtual void i1c();
virtual void i20();
virtual void i24();
virtual void i28();
virtual void i2c();
virtual void i30();
virtual void i34();
virtual void i38();
virtual void i3c();
virtual void i40();
virtual void i44();
virtual void i48();
virtual void i4c();
virtual void i50();
virtual void i54();
    virtual bool IsTracking();                            // +0x58
virtual void i5c();
virtual void i60();
virtual void i64();
virtual void i68();
virtual void i6c();
virtual void i70();
virtual void i74();
virtual void i78();
virtual void i7c();
virtual void i80();
virtual void i84();
virtual void i88();
virtual void i8c();
virtual void i90();
virtual void i94();
virtual void i98();
virtual void i9c();
virtual void ia0();
virtual void ia4();
virtual void ia8();
virtual void iac();
virtual void ib0();
virtual void ib4();
    virtual uint32_t AddVertexObject(void* pVec);         // +0xb8
    uint32_t mPad04;                                      // +0x04
};
class cRefCountBase
{
public:
virtual void r00();
virtual void r04();
virtual void r08();
virtual void r0c();
virtual void r10();
virtual void r14();
virtual void r18();
virtual void r1c();
virtual void r20();
virtual void r24();
virtual void r28();
    virtual cVector3* GetHerdPosition();                  // +0x2c
virtual void r30();
virtual void r34();
virtual void r38();
virtual void r3c();
virtual void r40();
virtual void r44();
virtual void r48();
virtual void r4c();
virtual void r50();
virtual void r54();
virtual void r58();
virtual void r5c();
    virtual long double GetHerdRadius();                  // +0x60
    virtual ~cRefCountBase();                             // 0x00b5b690
};
class cIUnknown32
{
public:
virtual void u00();
virtual void u04();
virtual void u08();
virtual void u0c();
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
class cCreatureTimerMap : public cTimerMap
{
public:
    void Read(cSerializer* pSerializer);                     // 0x00cc5d40
    cGonzagoTimer& operator[](cIRefCounted** ppKey);         // 0x00cc5ee0
};
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
// ---- items of slice s00cc4fa0 end

// ---- items of slice s0135d100 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void fn_00692ca0();
extern "C" void fn_00ae3470();
extern "C" void fn_00ae3490();
extern "C" void fn_00ae3310();
extern "C" void fn_00ac8050();
extern "C" void fn_00572810();
extern "C" void fn_00572840();
extern "C" void fn_00693090();
extern "C" void fn_00694f00();
extern "C" void fn_00b1fbf0();
extern "C" void fn_00675ca0();
extern "C" void fn_00cc5d40();
extern "C" void fn_00cc54f0();
extern "C" void fn_00c2e4e0();
extern "C" void fn_00692fb0();
extern "C" void fn_00cc5010();
extern "C" void fn_00d022e0();
extern "C" void fn_00c95780();
extern "C" void fn_00c6adc0();
extern "C" void fn_00c6c4e0();
typedef void (__cdecl *fp)();
struct T {
    const char* name;
    unsigned hash;
    int off;
    int p3, p4, p5;
    int z0, z1;
    fp f[7];
    T() {}
    T(const char* n, unsigned h, int o, fp f0, fp f1, fp f2, fp f3,
      fp f4, fp f5, fp f6)
        : name(n), hash(h), z0(0), z1(0) {
        f[0] = f0; f[1] = f1; f[2] = f2; f[3] = f3;
        f[4] = f4; f[5] = f5; f[6] = f6;
        off = o;
    }
};
extern T g_0157ea38, g_0157ea74, g_0157eab0, g_0157eaec, g_0157eb28;
// ---- items of slice s0135d100 end

// ---- items of slice s00cc5fe0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_fTribeScale;     // 0x0157e940 (declared in the block above)
extern float    g_f158135c;     // 0x0158135c  relationship threshold (class 1)
extern float    g_f1581360;     // 0x01581360  relationship threshold (class 2)
extern float    g_f1581364;     // 0x01581364  relationship threshold (class 3)
extern float    g_f1581378;     // 0x01581378  relationship reset value
extern uint64_t g_t15812c0;     // 0x015812c0  elapsed-time threshold (64-bit)
extern void DoInsertKey4(void* v, uint32_t* where, const uint32_t& value);   // 0x00b96600
extern void FillEntryPushBack(void* v, const void* value);                   // 0x004e19a0
extern float g_f13f9428;        // 0x013f9428  seconds->milliseconds scale
extern float g_f13ebc5c;        // 0x013ebc5c  default timer property value
struct Vec3 { float x, y, z; };
class cSpatial
{
public:
virtual void s00();
virtual void s01();
virtual void s02();
virtual void s03();
virtual void s04();
virtual void s05();
virtual void s06();
virtual void s07();
virtual void s08();
virtual void s09();
virtual void s10();
    virtual const Vec3* GetPosition();          // +0x2c
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s20();
virtual void s21();
virtual void s22();
virtual void s23();
virtual void s24();
virtual void s25();
virtual void s26();
virtual void s27();
    virtual void s28();
    virtual float GetFloat74();                 // +0x74 (the 0x4000000 pushed before it is b81020's third arg)
};
class cSubObj
{
public:
    char pad0[0x34];
    cSpatial mSpatial;                          // +0x34
};
class cTribe
{
public:
virtual void t00();
virtual void t01();
virtual void t02();
virtual void t03();
virtual void t04();
virtual void t05();
virtual void t06();
virtual void t07();
virtual void t08();
virtual void t09();
virtual void t10();
virtual void t11();
virtual void t12();
virtual void t13();
virtual void t14();
virtual void t15();
virtual void t16();
virtual void t17();
virtual void t18();
virtual void t19();
virtual void t20();
virtual void t21();
virtual void t22();
virtual void t23();
    virtual float GetRadius();                  // +0x60
virtual void t25();
virtual void t26();
virtual void t27();
virtual void t28();
virtual void t29();
virtual void t30();
virtual void t31();
virtual void t32();
virtual void t33();
virtual void t34();
virtual void t35();
virtual void t36();
virtual void t37();
virtual void t38();
virtual void t39();
virtual void t40();
virtual void t41();
virtual void t42();
    virtual cSubObj* GetModel();                // +0xac

    char pad4[0x120 - 4];
    cSpatial mSpatial;                          // +0x120
    char pad124[0x260 - 0x124];
    cSubObj* mpLinked;                          // +0x260
    char pad264[0x2c4 - 0x264];
    float mGrowthParam;                         // +0x2c4

    void* GetToolOfType(int type);              // 0x00c8f6e0 (ret 4)
    uint32_t GetSlot0();                        // 0x00c8e820 (ret 4): [this + 0x18cc]
    bool FUN_00c8e850();                        // 0x00c8e850
    bool FUN_00c8e870();                        // 0x00c8e870
    void FUN_00c8e820(int x);                   // 0x00c8e820 (ret 4)
};
class cHerdNoun
{
public:
    char pad0[0x34];
    cSpatial mSpatial;                          // +0x34
    char pad38[0x108 - 0x38];
    uint32_t mKind;                             // +0x108
    char pad10c[0x11c - 0x10c];
    uint32_t mTerraformId;                      // +0x11c
};
class cNearNoun
{
public:
virtual void n00();
virtual void n01();
virtual void n02();
virtual void n03();
virtual void n04();
virtual void n05();
virtual void n06();
virtual void n07();
virtual void n08();
virtual void n09();
virtual void n10();
    virtual bool IsExcluded();                  // +0x2c
    const Vec3* GetPosition();                  // 0x00c6acc0
};
struct PtrVector
{
    void** mpBegin; void** mpEnd; void** mpCapacity;
    int size() const { return (int)(mpEnd - mpBegin); }
};
struct GameDataVector { uint32_t pad0; PtrVector mVector; };
void FUN_00cd7d10();
void FUN_00d3d420();
void FUN_00accbb0();
void FUN_00b1e500();
void FUN_00ace070();
void FUN_00accc30();
typedef void (*GameDataFn)();
struct cTerrainSphere;
class cGameNounManager_s00cc_5fe0
{
public:
    GameDataVector* GetGameDataVector(GameDataFn a, GameDataFn b, GameDataFn c, GameDataFn d,
                                      uint32_t type);   // 0x00b21340 (ret 0x14)
    cTribe* GetPlayerTribe();                           // 0x00bfc5f0
    void RemoveNoun(void* noun);                        // 0x00b225d0 (ret 4)
    cTerrainSphere* GetCurrentTerrainSphere();          // 0x00f67d90
};
cGameNounManager_s00cc_5fe0* NounManager_s00cc_5fe0();                        // 0x00b3d300
class cPropertyList;
bool GetPropertyAsUint32Array(cPropertyList* l, uint32_t id, int* pCount, uint32_t** ppData);  // 0x006a0840
float GetPropertyFloat(cPropertyList* l, uint32_t id, float def);   // 0x004e1c70 SP::GetPropertyT<float>
extern cPropertyList* g_pGameProps;                     // 0x01581288
struct cSettings { void* GetAvatarProfile(); };         // 0x004df420 (thiscall, no args)
cSettings* GetSetting9();                               // 0x00401090
struct cResourceDB
{
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
    virtual bool Has(void* res, int flag);              // +0x1c
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
    virtual bool IsPending(void* res);                  // +0x3c
virtual void v16();
virtual void v17();
virtual void v18();
    virtual void Request(void* res, const void* key);   // +0x4c
};
cResourceDB* FUN_00401010();
struct cObjectTemplateDB
{
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
    virtual void Release(void* res, int flag);          // +0x58
};
cObjectTemplateDB* ObjectTemplateDB();                  // 0x0067cb40
uint32_t* FUN_00c8ea70(uint32_t n);
struct cG1581208 { uint32_t GetDefault(); };
extern cG1581208 g_1581208;
cTribe* CreateTribe(const Vec3* pos, uint32_t a, uint32_t b, uint32_t c, uint32_t d, void* e);   // 0x00c93160
void ValidateHerdLocationsForTribe(cTribe* t);          // 0x00cc5850
void FUN_00cd4770(cNearNoun* n, cTribe* t);             // cdecl
struct cTribeModeStrategy_s00cc_5fe0
{
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
    virtual void v20();
    virtual void SetTribe(cTribe* t);                   // +0x54 (ret 4)
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
    virtual void v26();
    virtual struct cTribeUI* GetUI();                   // +0x6c
};
cTribeModeStrategy_s00cc_5fe0* TribeModeStrategyInstance();        // 0x00cd40b0
struct cTribeUI { void SetVisible(bool v); };           // 0x00cc93b0 (ret 4)
struct cEventLog
{
    void PostFeedbackEvent(uint32_t a, uint32_t b, const Vec3* pos, int c, int d, int e);   // 0x00dd8640 (ret 0x18)
};
cEventLog* EventLog();                                  // 0x00b3d3e0
struct ActionTargetArg
{
    uint32_t data[12];
    ActionTargetArg(void* obj);                           // 0x00ad7a30 (ret 4)
    ~ActionTargetArg();                                   // 0x00ad7ad0
};
struct cTriggerMgr
{
    void PostAction(uint32_t id, const ActionTargetArg& t, int flag);                       // 0x00ae09b0 (ret 0xc)
    void PostTrigger(const char* name, int a, int b, int c, int d, int e);                // 0x00ae0930 (ret 0x18)
};
cTriggerMgr* FUN_00b3d4d0();
struct cSList
{
    void SetField18(uint32_t v);                        // 0x00fcc200 (ret 4)
};
extern cSList* g_pSList;                                // 0x0169b41c
struct cTerraformingMgr { void Apply(uint32_t id); };   // 0x00bbec60 (ret 4)
cTerraformingMgr* TerraformingManager();                // 0x00b3d430
struct cPlanetModel_s00cc_5fe0
{
    void FUN_00b83c40(const Vec3* pos, float f, uint32_t flags, int z);   // ret 0x10
    void FUN_00b81020(const Vec3* pos, float f, uint32_t flags);          // ret 0xc
};
cPlanetModel_s00cc_5fe0* PlanetModel_s00cc_5fe0();                            // 0x00b3d350
struct ResKey { uint32_t id; uint16_t a; uint16_t b; };
template <class T> inline const T& min_ref(const T& a, const T& b) { return (b < a) ? b : a; }
class cNpcTribeController_s00cc_5fe0
{
public:
    char pad0[0xd0];
    char** mpTribeObjsBegin;                            // +0xd0
    char** mpTribeObjsEnd;                              // +0xd4
    char padd8[0xfc - 0xd8];
    uint32_t mTribePropId;                              // +0xfc

    void DoTribeGrowthSim(int unused);                  // 0x00cc62c0 (ret 4)
};
struct cSPTimer_s00cc_5fe0
{
    char mStorage[0x20];            // +0x00 real cSPTimer is 0x20 bytes
    bool     IsRunning();           // 0x00feba90 (ret 0)
    void     Restart();             // 0x00bc3130 (ret 0)
    void     Start();               // 0x00bc30f0 (ret 0)
    uint64_t GetElapsedTime();      // 0x00bc3190 (__int64 in edx:eax)
};
struct cTerrainSphere { char pad0[0x1100]; uint32_t mHandle; };
float  g_f13ebc5c;                              // 0x013ebc5c default timer value
uint32_t* operator_delete(void* p);             // 0x00f47380
struct cRelationshipManager
{
    float CalculateRelationshipAbsolute(int a, int b);          // 0x00d05a20 (ret 8)
    int   Classify(float f);                                    // 0x00d00780 (ret 4)
    void  RecordEvent(int a, int b, uint32_t id, float f);      // 0x00d06240 (ret 0x10)
};
cRelationshipManager* RelationshipManager();                    // 0x00b3d2c0
struct cGrowthRecord { char pad0[0x50]; uint32_t mField50; };
struct cSettingHost
{
    int GetArchetype(void* h, int b);       // 0x004e0050 (ret 8)
};
cSettingHost* FUN_00401090();   // 0x00401090 (ret 0)
struct cInlineVec5
{
    void*    m0;    // +0x00 inline buffer (or heap block)
    void*    m1;    // +0x04
    uint32_t m2;    // +0x08 capacity
    void Init(int n);                       // 0x004cd3c0 (ret 4)
    int  Run(void* obj, int a, int b, int c);   // 0x004dfff0 (ret 0x14)
};
void  memcpy_11e0744(void* dst, void* src, size_t n);   // 0x011e0744
struct UIntVector { uint32_t* mpBegin; uint32_t* mpEnd; uint32_t* mpCapacity; };
struct GonzagoNode
{
    GonzagoNode* mpLeft;    // +0x00
    GonzagoNode* mpRight;   // +0x04
    char         pad8[0x8];
    void*        mpKey;     // +0x10
};
struct cTimerMap_s00cc_5fe0
{
    char        pad0[0x4];
    GonzagoNode* mpEnd;     // +0x04
    char        pad8[0x4];
    GonzagoNode* mpRoot;    // +0x0c
    cSPTimer_s00cc_5fe0* operator[](void** key);   // 0x00cc5ee0
};
class cNpcTribeControllerW
{
public:
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
    virtual void v08();
    virtual void SetActiveMode(int x);          // +0x24 (ret 4)
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
virtual void v27();
virtual void v28();
virtual void v29();
virtual void v30();
virtual void v31();
virtual void v32();
virtual void v33();
virtual void v34();
virtual void v35();
    virtual void* GetChildList();               // +0x90 (ret 0) returns a vector ptr

    char     pad04[0x0c];                       // +0x04 (vptr occupies +0x00)
    cSPTimer_s00cc_5fe0 mTimer10;                          // +0x10
    cSPTimer_s00cc_5fe0 mTimer30;                          // +0x30
    char     pad50[0x10];                       // +0x50
    cTimerMap_s00cc_5fe0 mMap60;                           // +0x60 (map begin/end pair + root)
    char     pad70[0xc];                        // +0x70
    UIntVector mVec7c;                          // +0x7c
    char     pad88[0xd0 - 0x88];
    UIntVector mVecD0;                          // +0xd0
    char     padDc[0xfc - 0xdc];
    uint32_t mTribePropId;                      // +0xfc

    void FUN_00cc5f80();
    void FUN_00cc5fe0();
    void OnTick(uint64_t dt);
};
struct cModeStrategy
{
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
virtual void v27();
virtual void v28();
virtual void v29();
virtual void v30();
virtual void v31();
virtual void v32();
virtual void v33();
virtual void v34();
virtual void v35();
virtual void v36();
virtual void v37();
virtual void v38();
virtual void v39();
    virtual void v40();
    virtual int  GetToolPrice();                // +0xa4
};
struct cModeStrategyWide
{
    char pad0[0x40];
    int  mField40;                              // +0x40
    int  mField44;                              // +0x44
};
struct cConfigManager
{
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
virtual void v11();
    virtual int  GetFlag(uint32_t id);          // +0x30
};
cConfigManager* ConfigManager();                        // 0x0067dd30
bool  TerrainHasKey(uint32_t id);                       // 0x00cd4460 (ret 4), this=strategy
void* FUN_00cd3440();                                   // 0x00cd3440
void  FUN_00b706a0(uint32_t id);                        // 0x00b706a0 (ret 4)
int   GetTutorialToolPrice(cPropertyList* l, uint32_t id, int def);   // 0x004e1c30
int   GetPlayerEmpireOrMinus1();                        // 0x00b1f9d0
void* GameTimeManager();                                // 0x00b3d380
class cCreature
{
public:
    virtual void AddRef();                              // +0x00
    virtual void Release();                             // +0x04
virtual void c08();
virtual void c0c();
virtual void c10();
virtual void c14();
virtual void c18();
virtual void c1c();
virtual void c20();
virtual void c24();
virtual void c28();
virtual void c2c();
virtual void c30();
virtual void c34();
virtual void c38();
virtual void c3c();
virtual void c40();
virtual void c44();
    virtual void c48();
    virtual int  GetEmpire(int empire);                 // +0x4c
virtual void c50();
virtual void c54();
virtual void c58();
virtual void c5c();
virtual void c60();
virtual void c64();
virtual void c68();
virtual void c6c();
virtual void c70();
virtual void c74();
    virtual void OnDeath();                             // +0x78
virtual void c7c();
virtual void c80();
virtual void c84();
    virtual void Tick(float seconds);                   // +0x88
    virtual void* GetChildList();                       // +0x90

    char    pad04[0x2cc - 0x04];                        // +0x04
    float   mField2cc;                                  // +0x2cc
};
float FUN_00c8ead0_of(cCreature* c);                    // 0x00c8ead0
int   FUN_00c0b760_of(cCreature* c);                    // 0x00c0b760
void  MapTimerFind(void* out, void* key);               // 0x00e5c780
void  FUN_00cc5340(void* a, void* node);                // 0x00cc5340
void  SpVectorErase(void* begin, void* end);            // 0x0050f740
// ---- items of slice s00cc5fe0 end

// @ 0x00cc4fa0
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

// @ 0x00cc5010
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

// @ 0x00cc5070
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

// @ 0x00cc5100
long double __declspec(noinline) cFeedbackTimerMap::GetElapsedRatio(cFeedbackEvent* pEvent)
{
    long double nRemaining = (long double)GetRemainingTime(pEvent);
    return 1.0L - nRemaining / (long double)gTimeLimit;
}

// @ 0x00cc5170
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

// @ 0x00cc5230
cEventTimerValue::cEventTimerValue(const cEventTimerValue& x)
: mKey(x.mKey), mTimer(x.mTimer)
{
}

// @ 0x00cc5290
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

// @ 0x00cc5340
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

// @ 0x00cc5390
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

// @ 0x00cc53e0
cEventTimerValue::cEventTimerValue(cIRefCounted** ppKey, const cGonzagoTimer& timer)
: mKey(*ppKey), mTimer(timer)
{
}

// @ 0x00cc54f0
void __declspec(noinline) SerializeTimerMap(cSerializer* pSerializer, cTimerMap* pMap)
{
    EA::IO::IStream_s00cc_4fa0* pStream = pSerializer->GetOwner()->GetStream();
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

// @ 0x00cc5610
cNpcTribeController::~cNpcTribeController()
{
}

// @ 0x00cc5700
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

// @ 0x00cc5850
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

// @ 0x00cc5a70
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

// @ 0x00cc5b50
void __declspec(noinline) cNpcTribeController::Reset()
{
    mBabyGrowthTimers.NukeSubtree((cTimerNode*)mBabyGrowthTimers.mpNodeParent);
    mBabyGrowthTimers.reset();
    cWorldMapReset();
    mHerdPoints.mpEnd = mHerdPoints.mpBegin;
    mResourceObjects.clear();
}

// @ 0x00cc5bc0
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

// @ 0x00cc5d40
void __declspec(noinline) cCreatureTimerMap::Read(cSerializer* pSerializer)
{
    NukeSubtree((cTimerNode*)mpNodeParent);
    reset();

    EA::IO::IStream_s00cc_4fa0* pStream = pSerializer->GetOwner()->GetStream();
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

// @ 0x00cc5ee0
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

// @ 0x00cc5f80
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

// @ 0x00cc5fe0
void cNpcTribeControllerW::FUN_00cc5fe0()
{
    FUN_00cc5f80();

    if (mVec7c.mpBegin == mVec7c.mpEnd)
    {
        g_fTribeScale = 1.0f;
        SpVectorErase((void*)mVec7c.mpBegin, (void*)mVec7c.mpEnd);

        {
            uint32_t* src = mVecD0.mpEnd;
            uint32_t* dst = mVecD0.mpBegin;
            memcpy_11e0744(dst, src, (size_t)(src - src));
            mVecD0.mpEnd -= src - dst;
        }

        cTribe* tribe = NounManager_s00cc_5fe0()->GetPlayerTribe();
        (void)tribe;

        uint32_t k1;
        uint32_t k2;
        if (tribe->FUN_00c8e850())
        {
            if (tribe->FUN_00c8e870())
            {
                k1 = 0x5ece4770;
                k2 = 0xb9de15f2;
            }
            else
            {
                k1 = 0xa8ec6f99;
                k2 = 0xfd159d91;
            }
        }
        else
        {
            k1 = 0xcfb01b93;
            k2 = 0x17e5ef84;
        }

        tribe->FUN_00c8e820(0);
        cTerrainSphere* sphere = NounManager_s00cc_5fe0()->GetCurrentTerrainSphere();
        if (sphere->mHandle != 0)
            k2 = sphere->mHandle;

        mTribePropId = 0xf7426b5e;
        if (k1 == 0xa8ec6f99)
        {
            if (k2 == 0xb9de15f2)       mTribePropId = 0x4252b6ff;
            else if (k2 == 0xfd159d91)  mTribePropId = 0x1631b0c3;
            else if (k2 == 0x17e5ef84)  mTribePropId = 0xf7426b5e;
        }
        else if (k1 == 0xcfb01b93)
        {
            if (k2 == 0xb9de15f2)       mTribePropId = 0x8da58d04;
            else if (k2 == 0xfd159d91)  mTribePropId = 0x97a0e4c2;
            else if (k2 == 0x17e5ef84)  mTribePropId = 0xfb43c9a7;
        }
        else if (k1 == 0x5ece4770)
        {
            if (k2 == 0xb9de15f2)       mTribePropId = 0xdb6b9;
            else if (k2 == 0xfd159d91)  mTribePropId = 0xf18a299d;
            else if (k2 == 0x17e5ef84)  mTribePropId = 0x8b4bf474;
        }

        {
            int count = 0;
            uint32_t* data = 0;
            count = 0;
            data = 0;
            if (GetPropertyAsUint32Array(g_pGameProps, mTribePropId, &count, &data) && count > 0)
            {
                int n = count / 2;
                int i = 0;
                if (n != 0)
                {
                    do
                    {
                        cGrowthRecord* rec = (cGrowthRecord*)FUN_00c8ea70(data[i * 2]);
                        uint32_t h = rec->mField50;
                        void* obj = (void*)FUN_00401090()->GetArchetype((void*)h, 0);
                        if (obj)
                        {
                            cInlineVec5 vec;
                            vec.Init(1);
                            int r = vec.Run(obj, 1, 0, 0);
                            if (r > 0)
                            {
                                uint32_t val = *(uint32_t*)vec.m0;
                                if (mVecD0.mpEnd < mVecD0.mpCapacity)
                                {
                                    uint32_t* p = mVecD0.mpEnd;
                                    mVecD0.mpEnd = p + 1;
                                    *p = val;
                                }
                                else
                                {
                                    DoInsertKey4((void*)&mVecD0, mVecD0.mpEnd, val);
                                }
                                FillEntryPushBack((void*)(val + 0x504), (void*)vec.m0);
                            }
                            void* alloc = *(void**)vec.m0;
                            if (alloc != 0 && *(uint32_t*)((char*)alloc - 4) != 0)
                                operator_delete(alloc);
                        }
                        ++i;
                    } while (i < n);
                }
            }
        }
    }
}

// @ 0x00cc62c0
void cNpcTribeController_s00cc_5fe0::DoTribeGrowthSim(int)
{
    g_fTribeScale = 1.0f;
    cGameNounManager_s00cc_5fe0* nm0 = NounManager_s00cc_5fe0();
    GameDataVector* tribes = nm0->GetGameDataVector(
        FUN_00cd7d10, FUN_00d3d420, FUN_00accbb0, FUN_00b1e500, 0x18c6d19);
    PtrVector& tv = tribes->mVector;
    int nTribes = tv.size();
    int count = 0;
    uint32_t* table = 0;
    char* selected = 0;
    if (!GetPropertyAsUint32Array(g_pGameProps, mTribePropId, &count, &table) || count < nTribes * 2)
        return;

    GetSetting9()->GetAvatarProfile();
    cTribe* player = NounManager_s00cc_5fe0()->GetPlayerTribe();
    const Vec3* playerPos = player->mSpatial.GetPosition();

    int last = nTribes - 1;
    if (mpTribeObjsBegin != mpTribeObjsEnd)
    {
        int sz = (int)(mpTribeObjsEnd - mpTribeObjsBegin);
        selected = mpTribeObjsBegin[min_ref(last, sz)];
        if (selected)
        {
            cResourceDB* db = FUN_00401010();
            char* res = selected + 0x504;
            if (!db->Has(res, 0))
            {
                if (db->IsPending(res))
                    return;
                ResKey key;
                key.id = 0x609b763;
                key.a = 0;
                key.b = 4;
                db->Request(res, &key);
                return;
            }
            ObjectTemplateDB()->Release(res, 1);
            selected = 0;
        }
    }

    uint32_t sel2 = table[nTribes * 2 - 2];
    FUN_00c8ea70(sel2);
    uint32_t v0 = 5;
    uint32_t v1 = g_1581208.GetDefault();
    if (sel2 > 0)
    {
        uint32_t* rec = FUN_00c8ea70(sel2);
        if (rec[0] > 0)
            v0 = rec[0];
        v1 = rec[1];
    }

    cHerdNoun* best = 0;
    float bestDist = 3.4028234e38f;
    cGameNounManager_s00cc_5fe0* nm1 = NounManager_s00cc_5fe0();
    GameDataVector* herds = nm1->GetGameDataVector(
        FUN_00cd7d10, FUN_00d3d420, FUN_00ace070, FUN_00b1e500, 0x36be27e);
    PtrVector& hv = herds->mVector;
    void** it = hv.mpBegin;
    void** end = hv.mpEnd;
    for (; it != end; ++it)
    {
        cHerdNoun* h = (cHerdNoun*)*it;
        if (h->mKind == 0x57f09e5e)
        {
            const Vec3* p = h->mSpatial.GetPosition();
            float dy = playerPos->y - p->y;
            float dx = playerPos->x - p->x;
            float dz = playerPos->z - p->z;
            float d = dz * dz + dy * dy + dx * dx;
            if (bestDist > d)
            {
                best = h;
                bestDist = d;
            }
        }
    }
    if (!best)
        return;

    best->mSpatial.GetPosition();
    cTribe* tribe = CreateTribe(best->mSpatial.GetPosition(), sel2, v0, v1, 0, selected);
    ValidateHerdLocationsForTribe(tribe);
    tribe->mGrowthParam = (float)(int)table[nTribes * 2 - 1];
    TribeModeStrategyInstance()->SetTribe(tribe);
    if (TribeModeStrategyInstance())
    {
        if (TribeModeStrategyInstance()->GetUI())
        {
            EventLog()->PostFeedbackEvent(0xd82d8a26, 0x182cd6ce, tribe->mSpatial.GetPosition(), 0, 1, 0);
            if (nTribes == 1)
            {
                cSubObj* model = tribe->GetModel();
                void* tool = tribe->GetToolOfType(10);
                g_pSList->SetField18(tribe->GetSlot0());
                FUN_00b3d4d0()->PostAction(0xed4cefb6, ActionTargetArg(tool ? (char*)tool + 0x34 : 0), 0);
                FUN_00b3d4d0()->PostAction(0xd749c1, ActionTargetArg(model ? (char*)model + 0x34 : 0), 0);
                FUN_00b3d4d0()->PostAction(0xe44aea33, ActionTargetArg(&tribe->mSpatial), 0);
                TribeModeStrategyInstance()->GetUI()->SetVisible(false);
                FUN_00b3d4d0()->PostTrigger("TRG_PRE_FirstTribeAppears", 1, 0, 0, 0, 0);
            }
        }
    }

    TerraformingManager()->Apply(best->mTerraformId);
    const Vec3* tribePos = tribe->mSpatial.GetPosition();
    float radius = tribe->GetRadius();
    float pa = GetPropertyFloat(g_pGameProps, 0x80e984f, 1.0f);
    float pb = GetPropertyFloat(g_pGameProps, 0x22748972, 0.0f);
    float pc = GetPropertyFloat(g_pGameProps, 0xaf5e325, 10.0f);
    cPlanetModel_s00cc_5fe0* planet = PlanetModel_s00cc_5fe0();
    planet->FUN_00b83c40(tribePos, pa * radius, 0x4000000, 0);
    planet->FUN_00b81020(tribePos, pb * radius, 0x4000000);
    if (tribe->mpLinked)
        planet->FUN_00b81020(playerPos, tribe->mpLinked->mSpatial.GetFloat74(), 0x4000000);
    planet->FUN_00b83c40(tribe->GetModel()->mSpatial.GetPosition(), pc, 0x10000000, 0);

    cGameNounManager_s00cc_5fe0* nm = NounManager_s00cc_5fe0();
    nm->RemoveNoun(best);
    float radius2 = radius * radius;
    GameDataVector* nears = nm->GetGameDataVector(
        FUN_00cd7d10, FUN_00d3d420, FUN_00accc30, FUN_00b1e500, 0x1be418e);
    PtrVector& nv = nears->mVector;
    void** nit = nv.mpBegin;
    void** nend = nv.mpEnd;
    for (; nit != nend; ++nit)
    {
        cNearNoun* n = (cNearNoun*)*nit;
        if (!n->IsExcluded())
        {
            const Vec3* p = n->GetPosition();
            float dx = p->x - tribePos->x;
            float dy = p->y - tribePos->y;
            float dz = p->z - tribePos->z;
            float d = dz * dz + dy * dy + dx * dx;
            if (radius2 > d)
                nm->RemoveNoun(n);
            else
                FUN_00cd4770(n, tribe);
        }
    }
}

// @ 0x00cc6910
void cNpcTribeControllerW::OnTick(uint64_t dt)
{
    {
        cTriggerMgr* tm = FUN_00b3d4d0();
        int mode = *(int*)((char*)tm + 0x2c);
        if (mode == 1)
            return;
        if (mode == 2)
            return;
    }
    {
        char* gt = (char*)GameTimeManager();
        if ((*(unsigned char*)(gt + 0x48) & 1) != 0)
            return;
    }

    cTribe* trib = NounManager_s00cc_5fe0()->GetPlayerTribe();
    (void)trib;

    float scale = g_fTribeScale;
    float seconds = (float)(__int64)dt * g_f13f9428;
    scale = scale - seconds;
    g_fTribeScale = scale;

goTail:
    if (scale < 0.0f)
    {
        GameDataVector* tribes = NounManager_s00cc_5fe0()->GetGameDataVector(
            FUN_00cd7d10, FUN_00d3d420, FUN_00accbb0, FUN_00b1e500, 0x18c6d19);
        int n = (int)(tribes->mVector.mpEnd - tribes->mVector.mpBegin);
        int idx = n - 1;
        if ((unsigned)idx <= 4u)
        {
            switch (idx)
            {
            case 0:
            {
                int flag = ConfigManager()->GetFlag(0x4ea96cb);
                bool b3 = (flag == 0);
                bool b1 = TerrainHasKey(0x11ade9ce);
                if (b1 || b3)
                {
                    if (!mTimer10.IsRunning())
                        mTimer10.Restart();
                    float lim = GetPropertyFloat(g_pGameProps, 0x3d346a77, g_f13ebc5c);
                    uint64_t el = mTimer10.GetElapsedTime();
                    b1 = ((double)(unsigned __int64)el * 0.001 < (double)lim);
                }
                bool b2 = TerrainHasKey(0x14363974);
                if (b2 || b3)
                {
                    if (!mTimer30.IsRunning())
                        mTimer30.Restart();
                    float lim = GetPropertyFloat(g_pGameProps, 0x1a09d79e, g_f13ebc5c);
                    uint64_t el = mTimer30.GetElapsedTime();
                    b2 = ((double)lim < (double)(unsigned __int64)el * 0.001);
                }
                if (b1 || b2)
                {
                    SetActiveMode(0);
                    void* p = FUN_00cd3440();
                    if (p)
                        FUN_00b706a0(0xdcdf2f2f);
                }
                break;
            }
            case 1:
            {
                cModeStrategyWide* st = (cModeStrategyWide*)TribeModeStrategyInstance();
                if (st->mField40 == st->mField44)
                {
                    int price = GetTutorialToolPrice(g_pGameProps, 0x4c87e711, 100);
                    int have = ((cModeStrategy*)st)->GetToolPrice();
                    if (have <= price)
                        break;
                }
                SetActiveMode(0);
                break;
            }
            case 2:
            case 3:
                SetActiveMode(0);
                break;
            case 4:
            {
                cModeStrategyWide* st = (cModeStrategyWide*)TribeModeStrategyInstance();
                if ((unsigned)((st->mField44 - st->mField40) >> 4) < 3u)
                    break;
                SetActiveMode(0);
                break;
            }
            default:
                break;
            }
        }
    }

    {
        GameDataVector* tribes = NounManager_s00cc_5fe0()->GetGameDataVector(
            FUN_00cd7d10, FUN_00d3d420, FUN_00accbb0, FUN_00b1e500, 0x18c6d19);
        char** it = (char**)tribes->mVector.mpBegin;
        char** end = (char**)tribes->mVector.mpEnd;
        if (it != end)
        {
            do
            {
                cCreature* obj = (cCreature*)*it;
                if (obj->mField2cc > 0.0f)
                {
                    float v = obj->mField2cc - seconds;
                    obj->mField2cc = v;
                    if (!(v > 0.0f))
                    {
                        int emp = GetPlayerEmpireOrMinus1();
                        obj->GetEmpire(emp);
                        cRelationshipManager* rm = RelationshipManager();
                        float rel = rm->CalculateRelationshipAbsolute(0, 0);
                        (void)rel;
                        int cls = rm->Classify(rel);
                        if (cls == 4)
                        {
                            obj->mField2cc = 0.0f;
                        }
                        else
                        {
                            float self = FUN_00c8ead0_of(obj);
                            int cls2 = rm->Classify(self);
                            float delta = 0.0f;
                            if (cls == 1)      delta = g_f158135c - rel;
                            else if (cls == 2) delta = g_f1581360 - rel;
                            else if (cls == 3) delta = g_f1581364 - rel;
                            if (delta < 0.0f)
                            {
                                int emp2 = GetPlayerEmpireOrMinus1();
                                obj->GetEmpire(emp2);
                                RelationshipManager()->RecordEvent(0, 0, 0x530cf06, delta);
                            }
                            int emp3 = GetPlayerEmpireOrMinus1();
                            obj->GetEmpire(emp3);
                            float rel3 = RelationshipManager()->CalculateRelationshipAbsolute(0, 0);
                            int cls3 = RelationshipManager()->Classify(rel3);
                            obj->mField2cc = (cls3 > cls2) ? g_f1581378 : 0.0f;
                        }
                    }
                }

                {
                    void* childList = obj->GetChildList();
                    char** cit = (char**)childList;
                    char** cend = (char**)((char**)childList)[1];
                    char** cur = (char**)((char**)childList)[0];
                    if (cur != cend)
                    {
                        do
                        {
                            cCreature* child = (cCreature*)*cur;
                            if (FUN_00c0b760_of(child) == 0)
                            {
                                child->AddRef();
                                // lower_bound over mMap60
                                cTimerMap_s00cc_5fe0& map = mMap60;
                                GonzagoNode* node = map.mpRoot;
                                GonzagoNode* cand = map.mpEnd;
                                while (node)
                                {
                                    if ((unsigned int)node->mpKey < (unsigned int)child)
                                        node = node->mpLeft;
                                    else { cand = node; node = node->mpRight; }
                                }
                                if (cand != map.mpEnd && (unsigned int)child < (unsigned int)cand->mpKey)
                                    cand = map.mpEnd;
                                bool missing = (cand == map.mpEnd);
                                child->Release();
                                if (missing)
                                {
                                    child->AddRef();
                                    cSPTimer_s00cc_5fe0* t = mMap60[(void**)&child];
                                    t->Start();
                                    child->Release();
                                }
                                child->AddRef();
                                cSPTimer_s00cc_5fe0* t2 = mMap60[(void**)&child];
                                child->Release();
                                if (t2->IsRunning() && t2->GetElapsedTime() > g_t15812c0)
                                {
                                    child->OnDeath();
                                    child->AddRef();
                                    void* found = 0;
                                    MapTimerFind(&found, &child);
                                    if (found != mMap60.mpEnd)
                                        FUN_00cc5340(0, found);
                                    child->Release();
                                }
                            }
                            child->Tick(seconds);
                            ++cur;
                        } while (cur != cend);
                    }
                }
                ++it;
            } while (it != end);
        }
    }
}

// @ 0x0135d100
void FUN_0135d100()
{
    g_0157ea38 = T("mPostTutorialDelayTimer_Mating", 0x5ee5e11u, 0x10, fn_00692ca0, fn_00ae3470, fn_00ae3490, fn_00c2e4e0, fn_00692fb0, fn_00ae3310, fn_00ac8050);
    g_0157ea74 = T("mPostTutorialDelayTimer_Food", 0x66a2038u, 0x30, fn_00692ca0, fn_00ae3470, fn_00ae3490, fn_00c2e4e0, fn_00692fb0, fn_00ae3310, fn_00ac8050);
    g_0157eab0 = T("mTribeAppearanceProperty", 0x629a22du, 0xfc, fn_00692ca0, fn_00572810, fn_00572840, fn_00693090, fn_00694f00, fn_00b1fbf0, fn_00675ca0);
    g_0157eaec = T("mBabyGrowthTimers", 0x57a481eu, 0x60, fn_00692ca0, fn_00cc5d40, fn_00cc54f0, fn_00c2e4e0, fn_00692fb0, fn_00cc5010, fn_00d022e0);
    g_0157eb28 = T("mNPCTribeSpeciesKeys", 0x600dd49u, 0x7c, fn_00692ca0, fn_00c95780, fn_00c6adc0, fn_00c2e4e0, fn_00692fb0, fn_00b1fbf0, fn_00c6c4e0);
}
