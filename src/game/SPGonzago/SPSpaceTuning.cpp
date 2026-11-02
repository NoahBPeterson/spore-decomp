// src/game/SPGonzago/SPSpaceTuning.cpp -- migrated from slice(s) s010409b0, s0103fe90 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPSpaceTuning.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void _ReadWriteBarrier(void);
extern "C" void* __stdcall FUN_00b3d2a0(void* a);                  // 0x00b3d2a0 SP::StarManager
extern "C" float __cdecl FUN_010307a0(void* p, int a, int b);      // 0x010307a0
extern "C" void  __cdecl FUN_00571db0(void* server, void* handler, void* ids, int count, int prio); // 0x00571db0 EA::Messaging::RemoveHandler
extern float     DAT_013ec5b4;               // 0x013ec5b4 1000.0f
extern float     DAT_013eb960;               // 0x013eb960 0.01f
#pragma intrinsic(_ReadWriteBarrier)

// ---- items of slice s0103fe90 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define VFN(obj, off) (*(void**)((char*)(*(void**)obj) + (off)))
extern "C" void _ReadWriteBarrier(void);
extern "C" void* __stdcall FUN_00b3d2a0(void* a);                  // 0x00b3d2a0 SP::StarManager
extern "C" float __cdecl FUN_010307a0(void* p, int a, int b);      // 0x010307a0
extern "C" void  __cdecl FUN_00571db0(void* server, void* handler, void* ids, int count, int prio); // 0x00571db0 EA::Messaging::RemoveHandler
extern float     DAT_013ec5b4;               // 0x013ec5b4 1000.0f
extern float     DAT_013eb960;               // 0x013eb960 0.01f
class tHost {
public:
    void  __thiscall FUN_00692f60(int a);                    // 0x00692f60 cRegNode::Construct
    char  __thiscall FUN_00ab30c0();                         // 0x00ab30c0
    void  __thiscall FUN_00692850();                         // 0x00692850
    void* __thiscall FUN_00baf700();                         // 0x00baf700
    void  __thiscall FUN_00733030(void* a, void* b);         // 0x00733030
    void* __thiscall FUN_00c71e30();                         // 0x00c71e30
    void* __thiscall FUN_00f67d90();                         // 0x00f67d90 GetCurrentTerrainSphere
    char  __thiscall FUN_00c75650();                         // 0x00c75650 cTerrainSphere::Check
    void  __thiscall FUN_00bdbf10();                         // 0x00bdbf10
    void  __thiscall FUN_00ff0350(float f);                  // 0x00ff0350 cCityData::AddValue
    void  __thiscall FUN_00fffdd0(int a, int b);             // 0x00fffdd0
    void* __thiscall FUN_00d06240(void* a);                  // 0x00d06240 cRelationshipManager::RecordEvent
    void  __thiscall FUN_00dd8640(int a, int b, int c, int d, int e, int f); // 0x00dd8640 PostFeedbackEvent
    void  __thiscall FUN_00676e90(int a, int b);             // 0x00676e90 Achievements::AutoTest
    void* __thiscall FUN_00b21340(void* a, void* b, void* c, void* d, void* e); // 0x00b21340 GetGameDataVector
};
class cSpaceTuning {
public:
    uint8_t m00[0x50];           // +0x50 float parameter lives in another view; pad 0x00..0x50
    float   m50;                 // +0x50
    uint8_t m54[0x40];           // +0x54 -> +0x94
    int     m94;                 // +0x94
    uint8_t m98[4];              // +0x98
    float   m9c;                 // +0x9c

    int   __thiscall FUN_010407d0(void* param);
    float __thiscall FUN_01040820(float param);
    uint32_t __thiscall FUN_01040870();
};
class PaintSystem {
public:
    virtual ~PaintSystem() {}
    virtual void _v01();
};
class cSpaceRelationshipTuning : public PaintSystem {
public:
    void* mpServer;              // +0x04
    void* mpHandler;             // +0x08
    void* mpIdArray;             // +0x0c
    int   mnIdArrayCount;        // +0x10
    int   mnPriority;            // +0x14
    void* mPropList;             // +0x18
    void* mUIPropList;           // +0x1c

    void __thiscall FUN_010408f0();
    virtual ~cSpaceRelationshipTuning();
};
// ---- items of slice s0103fe90 end

// ---- items of slice s010409b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t gSpaceRelationshipMessageIds[];   // 0x01499ca8
#define PV(n) virtual void _pv##n();
namespace App {
enum PropertyType { kPropBool = 1, kPropInt32 = 9, kPropFloat = 13 };
}
namespace App {
class Property {
 public:
  void* mpData;
  uint32_t field_4;
  uint32_t mnItemCount;
  uint32_t field_C;
  uint16_t mnFlags;   // +0x10
  uint16_t mnType;    // +0x12
  bool* GetBool();    // 0x0041e920
  int* GetInt();      // 0x0041e990
  float* GetFloat();  // 0x0041ea70
};
}
namespace App {
class PropertyList {
 public:
  virtual int AddRef();
  virtual int Release();
  PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
  virtual bool GetProperty(uint32_t id, Property** ppOut);   // +0x24
};
}
namespace App {
template <class T>
struct AutoRefCount {
  T* mpObject;
  void Reset() {
    if (mpObject) {
      T* t = mpObject;
      mpObject = 0;
      t->Release();
    }
  }
};
}
namespace App {
class IPropManager {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  virtual bool GetPropertyList(uint32_t instance, uint32_t group, AutoRefCount<PropertyList>* pOut);   // +0x2c
  virtual bool GetPropertyList2(uint32_t instance, AutoRefCount<PropertyList>* pOut);                  // +0x30
};
}
App::IPropManager* PropertyManager();   // 0x0067de30
class CMessage {
 public:
  char mPad00[0x18];
  uint32_t mnType;   // +0x18
};
class IMessageServer {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
  virtual void AddHandler(void* pHandler, uint32_t nMessageId);   // +0x24
};
IMessageServer* MessageManager();   // 0x0067dcc0
void RemoveHandler(void* pServer, void* pHandler, uint32_t* pIdArray, int nIdCount,
                   int nPriority);   // 0x00571db0
void EastlDeallocate(void* pBlock);          // 0x00f47380
namespace SP {
class cSpaceRelationshipTuning_s0104_09b0 {
 public:
  void* mpVTable;                           // +0x00
  IMessageServer* mpServer;                 // +0x04
  void* mpHandler;                          // +0x08
  uint32_t* mpIdArray;                      // +0x0c
  int mnIdCount;                            // +0x10
  int mnPriority;                           // +0x14
  App::AutoRefCount<App::PropertyList> mPropList;     // +0x18
  App::AutoRefCount<App::PropertyList> mUIPropList;   // +0x1c
  float mFriendThreshold;                   // +0x20
  float mGoodFriendThreshold;               // +0x24
  float mEnemyThreshold;                    // +0x28
  float mBadEnemyThreshold;                 // +0x2c
  float mEscortThreshold;                   // +0x30
  float mHostileThreshold;                  // +0x34
  float mWarThreshold;                      // +0x38
  float mWarEndThreshold;                   // +0x3c
  float mChanceOfWar;                       // +0x40
  float mTribeFeedbackActivationDistance;   // +0x44
  float mTribeFeedbackDeactivationDistance; // +0x48
  bool mTribeGameBehaviorsActivated;        // +0x4c
  float mBreakAllianceThreshold;            // +0x50
  float mGrobInitialRelationship;           // +0x54
  float mEmpireSizeRatioMinCap;             // +0x58
  float mEmpireSizeRatioMaxCap;             // +0x5c
  float mEmpireSizeRatioFactor;             // +0x60
  float mCurRelationshipFactor;             // +0x64
  float mMissionThreshold;                  // +0x68
  float mLargeGiftAmount;                   // +0x6c
  float mMediumGiftAmount;                  // +0x70
  float mSmallGiftAmount;                   // +0x74
  int mLargeGiftRelMultiplier;              // +0x78
  int mMediumGiftRelMultiplier;             // +0x7c
  int mSmallGiftRelMultiplier;              // +0x80
  float mNPCGiftAmount;                     // +0x84
  float mNPCTributeAmount;                  // +0x88
  float mNPCTributeTimeLimit;               // +0x8c
  int mEmbassyUpdateRate;                   // +0x90
  int mField94;                             // +0x94
  float mField98;                           // +0x98
  float mField9c;                           // +0x9c

  void ReloadTuning();                      // 0x010409b0
  void Init();                              // 0x01041090
  bool HandleMessage(int nMessageId, CMessage* pMessage);   // 0x010410e0
};
}
namespace SP {
struct cTuningEntry {
  int mn00, mn04, mn08, mn0c, mn10;     // +0x00  zeroed
  int mn14;                            // +0x14  1
  float mf18, mf1c, mf20;              // +0x18  relationship band, default 1.0
  float mf24;                          // +0x24  30.0
  float mf28;                          // +0x28  1.0
  float mf2c;                          // +0x2c  10.0
  float mf30, mf34;                    // +0x30  1.0
  float mf38;                          // +0x38  0.0
  bool mb3c, mb3d;                     // +0x3c  flags, false
  char mPad3e[2];
  float mf40, mf44;                    // +0x40  1.0
  float mf48, mf4c;                    // +0x48  0.0
  bool mb50, mb51, mb52;               // +0x50  flags, false
  char mPad53;

  cTuningEntry()
      : mn00(0), mn04(0), mn08(0), mn0c(0), mn10(0), mn14(1), mf18(1.0f),
        mf1c(1.0f), mf20(1.0f), mf24(30.0f), mf28(1.0f), mf2c(10.0f), mf30(1.0f), mf34(1.0f),
        mf38(0.0f), mb3c(false), mb3d(false), mf40(1.0f), mf44(1.0f), mf48(0.0f), mf4c(0.0f),
        mb50(false), mb51(false), mb52(false) {}
};
}
namespace SP {
class cTuningEntryVector {
 public:
  cTuningEntry* mpBegin;   // +0x00
  cTuningEntry* mpEnd;     // +0x04
  cTuningEntry* mpCap;     // +0x08

  cTuningEntry* EraseRange(cTuningEntry* pFirst, cTuningEntry* pLast);   // 0x01041220
  void Insert(cTuningEntry* pPos, const cTuningEntry& value);           // 0x01041280
  void PushDefault();                                                  // 0x010413b0

  ~cTuningEntryVector() { FreeBuffer(); }
  void FreeBuffer() {
    if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0)
      EastlDeallocate(mpBegin);
  }
};
}
namespace SP {
class CMessageHandlerBase {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
  virtual ~CMessageHandlerBase() {}   // restores the base vtable

  IMessageServer* mpServer;   // +0x04
  void* mpHandler;            // +0x08
  uint32_t* mpIdArray;        // +0x0c
  int mnIdCount;              // +0x10
  int mnPriority;             // +0x14
};
}
namespace SP {
class cTuningEntrySet : public CMessageHandlerBase {
 public:
  cTuningEntryVector mEntries;   // +0x18

  void Release();                                     // 0x01041480
  void* ScalarDeletingDestructor(unsigned char nFlags);   // 0x01041110
};
}
namespace SP {
static inline bool GetPropFloat(App::PropertyList* pList, uint32_t id, float& dst)
{
  App::Property* p;
  if (pList && pList->GetProperty(id, &p) && p->mnType == App::kPropFloat) {
    dst = *p->GetFloat();
    return true;
  }
  return false;
}
}
namespace SP {
static inline bool GetPropInt(App::PropertyList* pList, uint32_t id, int& dst)
{
  App::Property* p;
  if (pList && pList->GetProperty(id, &p) && p->mnType == App::kPropInt32) {
    dst = *p->GetInt();
    return true;
  }
  return false;
}
}
namespace SP {
static inline bool GetPropBool(App::PropertyList* pList, uint32_t id, bool& dst)
{
  App::Property* p;
  if (pList && pList->GetProperty(id, &p) && p->mnType == App::kPropBool) {
    dst = *p->GetBool();
    return true;
  }
  return false;
}
}
// ---- items of slice s010409b0 end

// @ 0x010407d0
int __thiscall cSpaceTuning::FUN_010407d0(void* param)
{
    void* p = FUN_00b3d2a0(param);
    void* q = ((tHost*)p)->FUN_00baf700();
    float r = FUN_010307a0(q, 0x68d6965, 0x68d696b);
    float f = (float)m94 * r;
    return (int)(f * DAT_013eb960) * 100;
}

// @ 0x01040820
float __thiscall cSpaceTuning::FUN_01040820(float param)
{
    if (m50 > param) {
        return 0.0f;
    }
    return 1.0f;
}

// @ 0x01040870
uint32_t __thiscall cSpaceTuning::FUN_01040870()
{
    return (uint32_t)(m9c * DAT_013ec5b4);
}

// @ 0x010408f0
void __thiscall cSpaceRelationshipTuning::FUN_010408f0()
{
    if (mPropList != 0) {
        void* p = mPropList;
        mPropList = 0;
        ((void(__thiscall*)(void*))VFN(p, 4))(p);
    }
    if (mUIPropList != 0) {
        void* p = mUIPropList;
        mUIPropList = 0;
        ((void(__thiscall*)(void*))VFN(p, 4))(p);
    }
    if (mpServer != 0) {
        void* s = mpServer;
        mpServer = 0;
        FUN_00571db0(s, mpHandler, mpIdArray, mnIdArrayCount, mnPriority);
    }
}

// @ 0x01040950
cSpaceRelationshipTuning::~cSpaceRelationshipTuning()
{
    _ReadWriteBarrier();
    void* ui = *(void* volatile*)&mUIPropList;
    if (ui != 0) {
        ((void(__thiscall*)(void*))VFN(ui, 4))(ui);
    }
    void* pl = *(void* volatile*)&mPropList;
    if (pl != 0) {
        ((void(__thiscall*)(void*))VFN(pl, 4))(pl);
    }
    if (mpServer != 0) {
        void* s = mpServer;
        mpServer = 0;
        FUN_00571db0(s, mpHandler, mpIdArray, mnIdArrayCount, mnPriority);
    }
}

// @ 0x010409b0
namespace SP {
void cSpaceRelationshipTuning_s0104_09b0::ReloadTuning()
{
  if (!mPropList.mpObject) {
    App::IPropManager* pm = PropertyManager();
    mPropList.Reset();
    pm->GetPropertyList(0x86017d53, 0x02ae0c7e, &mPropList);
  }
  if (!mUIPropList.mpObject) {
    App::IPropManager* pm = PropertyManager();
    mUIPropList.Reset();
    pm->GetPropertyList2(0x5c770db7, &mUIPropList);
  }
  GetPropFloat(mUIPropList.mpObject, 0x01d37a06, mFriendThreshold);
  GetPropFloat(mUIPropList.mpObject, 0x01d37a0c, mGoodFriendThreshold);
  GetPropFloat(mUIPropList.mpObject, 0x01d37be0, mEnemyThreshold);
  GetPropFloat(mUIPropList.mpObject, 0x01d379fa, mBadEnemyThreshold);
  GetPropFloat(mPropList.mpObject, 0x05b7e4f5, mEscortThreshold);
  GetPropFloat(mPropList.mpObject, 0x05b7e516, mHostileThreshold);
  GetPropFloat(mPropList.mpObject, 0x02fc233b, mWarThreshold);
  GetPropFloat(mPropList.mpObject, 0x04233ced, mWarEndThreshold);
  GetPropFloat(mPropList.mpObject, 0x02fc2520, mChanceOfWar);
  mBreakAllianceThreshold = mGoodFriendThreshold;
  GetPropFloat(mPropList.mpObject, 0x041a06f8, mBreakAllianceThreshold);
  GetPropFloat(mPropList.mpObject, 0x041a06fa, mGrobInitialRelationship);
  mEmpireSizeRatioMinCap = 3.0f;
  GetPropFloat(mPropList.mpObject, 0x065266c0, mEmpireSizeRatioMinCap);
  mEmpireSizeRatioMaxCap = 0.0f;
  GetPropFloat(mPropList.mpObject, 0x065266cd, mEmpireSizeRatioMaxCap);
  GetPropFloat(mPropList.mpObject, 0x0295c001, mEmpireSizeRatioFactor);
  GetPropFloat(mPropList.mpObject, 0x0295c002, mCurRelationshipFactor);
  GetPropFloat(mPropList.mpObject, 0x0295c003, mMissionThreshold);
  GetPropFloat(mPropList.mpObject, 0x041a05e5, mLargeGiftAmount);
  GetPropFloat(mPropList.mpObject, 0x041a05e6, mMediumGiftAmount);
  GetPropInt(mPropList.mpObject, 0x041a05f5, mLargeGiftRelMultiplier);
  GetPropInt(mPropList.mpObject, 0x041a05f6, mMediumGiftRelMultiplier);
  GetPropInt(mPropList.mpObject, 0x041a05f7, mSmallGiftRelMultiplier);
  GetPropInt(mPropList.mpObject, 0x0594a718, mEmbassyUpdateRate);
  GetPropInt(mPropList.mpObject, 0x0594a71c, mField94);
  GetPropFloat(mPropList.mpObject, 0x0595d661, mField98);
  GetPropFloat(mPropList.mpObject, 0x041a05f8, mNPCGiftAmount);
  GetPropFloat(mPropList.mpObject, 0x041a05f9, mNPCTributeAmount);
  GetPropFloat(mPropList.mpObject, 0x041a05fa, mNPCTributeTimeLimit);
  GetPropFloat(mPropList.mpObject, 0x04d80588, mTribeFeedbackActivationDistance);
  GetPropFloat(mPropList.mpObject, 0x04d8076d, mTribeFeedbackDeactivationDistance);
  GetPropBool(mPropList.mpObject, 0x04d805be, mTribeGameBehaviorsActivated);
  GetPropFloat(mPropList.mpObject, 0x04d805bf, mSmallGiftAmount);
  GetPropFloat(mPropList.mpObject, 0x0580dfe7, mField9c);
}
}  // namespace SP

// @ 0x01041090
namespace SP {
void cSpaceRelationshipTuning_s0104_09b0::Init()
{
  mpServer = MessageManager();
  mpHandler = this;
  mpIdArray = gSpaceRelationshipMessageIds;
  mnIdCount = 1;
  mnPriority = 0;
  if (mpServer != 0 && mpHandler != 0)
    mpServer->AddHandler(mpHandler, 0xf62def);
  ReloadTuning();
}
}  // namespace SP

// @ 0x010410e0
namespace SP {
bool cSpaceRelationshipTuning_s0104_09b0::HandleMessage(int nMessageId, CMessage* pMessage)
{
  if (nMessageId == 0xf62def &&
      (pMessage->mnType == 0x86017d53 || pMessage->mnType == 0x5c770db7))
    ReloadTuning();
  return false;
}
}  // namespace SP

// @ 0x01041110
namespace SP {
void* cTuningEntrySet::ScalarDeletingDestructor(unsigned char nFlags)
{
  mEntries.~cTuningEntryVector();
  if (mpServer != 0) {
    IMessageServer* pServer = mpServer;
    mpServer = 0;
    RemoveHandler(pServer, mpHandler, mpIdArray, mnIdCount, mnPriority);
  }
  CMessageHandlerBase::~CMessageHandlerBase();
  if (nFlags & 1)
    EastlDeallocate(this);
  return this;
}
}  // namespace SP
