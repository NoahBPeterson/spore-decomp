// src/game/SPGonzago/SPSpaceTuning.cpp
//
// Space-stage tuning values, read from the game's property-list store.

#include "game/types.h"
#include "SP/cCity.h"
#include "SP/cPropertyManager.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void _ReadWriteBarrier(void);
extern "C" void* __stdcall FUN_00b3d2a0(void* a);                  // 0x00b3d2a0 SP::StarManager
extern "C" float __cdecl FUN_010307a0(void* p, int a, int b);      // 0x010307a0
extern "C" void  __cdecl FUN_00571db0(void* server, void* handler, void* ids, int count, int prio); // 0x00571db0 EA::Messaging::RemoveHandler
extern float     gMillisecondsPerSecond;     // 0x013ec5b4 1000.0f
extern float     gSecondsPerTick;            // 0x013eb960 0.01f
#pragma intrinsic(_ReadWriteBarrier)

// Reads a virtual function pointer from an object's vtable slot.
#define VFN(obj, off) (*(void**)((char*)(*(void**)obj) + (off)))

class tHost {
public:
    void* __thiscall FUN_00baf700();                         // 0x00baf700
};

// Space-tuning object; only the three members the exported helpers read are named.
class cSpaceTuning {
public:
    uint8_t m00[0x50];           // +0x00  unknown head, +0x50 float parameter lives in another view
    float   m50;                 // +0x50
    uint8_t m54[0x40];           // +0x54  unknown tail up to +0x94
    int     m94;                 // +0x94
    uint8_t m98[4];              // +0x98
    float   m9c;                 // +0x9c

    int   __thiscall FUN_010407d0(void* param);
    float __thiscall FUN_01040820(float param);
    uint32_t __thiscall FUN_01040870();
};

// Stand-in base for a reference-counted object: slot 0 is the destructor,
// slot 1 (the address VFN(obj, 4) reads) is Release().
class PaintSystem {
public:
    virtual ~PaintSystem() {}
    virtual void _v01();
};

// Same object as SP::cSpaceRelationshipTuning_s0104_09b0, seen from its vtable slice.
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

extern uint32_t gSpaceRelationshipMessageIds[];   // 0x01499ca8

// Property / message ids (names guessed from the call sites).
static const uint32_t kPropListGroupInstance = 0x86017d53;  // relationship tuning group
static const uint32_t kPropListGroupKind     = 0x02ae0c7e;
static const uint32_t kUIPropListInstance    = 0x5c770db7;  // relationship UI tuning group
static const uint32_t kTuningChangedMessage  = 0x00f62def;

#define PV(n) virtual void _pv##n();

namespace App {
enum PropertyType { kPropBool = 1, kPropInt32 = 9, kPropFloat = 13 };

// A single value inside a PropertyList; only mnType and the Get* accessors are used.
class Property {
 public:
  char mPad00[0x10];  // size, payload pointer, item count, flags
  uint16_t mnFlags;   // +0x10
  uint16_t mnType;    // +0x12
  bool* GetBool();    // 0x0041e920
  int* GetInt();      // 0x0041e990
  float* GetFloat();  // 0x0041ea70
};

class PropertyList {
 public:
  virtual int AddRef();
  virtual int Release();
  PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
  virtual bool GetProperty(uint32_t id, Property** ppOut);   // +0x24
};

// Owns a reference to a PropertyList, releasing it when Reset() or the owner dies.
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

class IPropManager {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  virtual bool GetPropertyList(uint32_t instance, uint32_t group, AutoRefCount<PropertyList>* pOut);   // +0x2c
  virtual bool GetPropertyList2(uint32_t instance, AutoRefCount<PropertyList>* pOut);                  // +0x30
};
}  // namespace App

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

// The space-relationship tuning object, seen from its message-handling slice:
// mpVTable/mpServer/mpHandler/mpIdArray/mnIdCount/mnPriority then the property lists
// and every tuning value it reads out of them.
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

// One row of a tuning set, with the retail defaults baked into its constructor.
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

// Base of every message handler: the server, the handler id and its priority.
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

class cTuningEntrySet : public CMessageHandlerBase {
 public:
  cTuningEntryVector mEntries;   // +0x18

  void Release();                                     // 0x01041480
  void* ScalarDeletingDestructor(unsigned char nFlags);   // 0x01041110
};

static inline bool GetPropFloat(App::PropertyList* pList, uint32_t id, float& dst)
{
  App::Property* p;
  if (pList && pList->GetProperty(id, &p) && p->mnType == App::kPropFloat) {
    dst = *p->GetFloat();
    return true;
  }
  return false;
}

static inline bool GetPropInt(App::PropertyList* pList, uint32_t id, int& dst)
{
  App::Property* p;
  if (pList && pList->GetProperty(id, &p) && p->mnType == App::kPropInt32) {
    dst = *p->GetInt();
    return true;
  }
  return false;
}

static inline bool GetPropBool(App::PropertyList* pList, uint32_t id, bool& dst)
{
  App::Property* p;
  if (pList && pList->GetProperty(id, &p) && p->mnType == App::kPropBool) {
    dst = *p->GetBool();
    return true;
  }
  return false;
}

}  // namespace SP

// ---------------------------------------------------------------------------
// Function bodies
// ---------------------------------------------------------------------------

// Property ids read from the star object (the names are guesses from the call site).
static const int kStarPropTravelTimeLow  = 0x068d6965;
static const int kStarPropTravelTimeHigh = 0x068d696b;
// Travel time is scaled to hundredths before being returned.
static const int kTravelTimePercentScale = 100;

// ---- items of slice s010414c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct ShaderMsgHandler {
    uint32_t mPad00;               // +0x00
    void*    mHandler;             // +0x04
    void*    mSelf;                // +0x08
    void*    mCallback;            // +0x0c
    uint32_t mMsg;                 // +0x10
    uint32_t mUserData;            // +0x14
    uint8_t  mPad18[0x18];         // +0x18 mInfos (owned by RegisterShaderDataInfo)

    bool OnMessage(int msg, void* obj);   // 0x01041b90
};
// ---- items of slice s010414c0 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void __fastcall RegisterShaderDataInfo(void* mgr);  // 0x010414c0 (stays in the slice: not this object's)

// @ 0x010407d0
int __thiscall cSpaceTuning::FUN_010407d0(void* param)
{
    void* star = FUN_00b3d2a0(param);
    void* host = ((tHost*)star)->FUN_00baf700();
    float travelTime = FUN_010307a0(host, kStarPropTravelTimeLow, kStarPropTravelTimeHigh);
    float scaled = (float)m94 * travelTime;
    return (int)(scaled * gSecondsPerTick) * kTravelTimePercentScale;
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
    return (uint32_t)(m9c * gMillisecondsPerSecond);
}

// @ 0x010408f0
// Releases both property lists and unregisters the message handler.
// (Called by the destructor path; the two lists are read through slot 1 = Release.)
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
// The barrier keeps the volatile reads of the list pointers from being reordered
// ahead of the store to mpServer in the release above.
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
    pm->GetPropertyList(kPropListGroupInstance, kPropListGroupKind, &mPropList);
  }
  if (!mUIPropList.mpObject) {
    App::IPropManager* pm = PropertyManager();
    mUIPropList.Reset();
    pm->GetPropertyList2(kUIPropListInstance, &mUIPropList);
  }
  // Relationship thresholds come from the UI tuning list.
  GetPropFloat(mUIPropList.mpObject, 0x01d37a06, mFriendThreshold);
  GetPropFloat(mUIPropList.mpObject, 0x01d37a0c, mGoodFriendThreshold);
  GetPropFloat(mUIPropList.mpObject, 0x01d37be0, mEnemyThreshold);
  GetPropFloat(mUIPropList.mpObject, 0x01d379fa, mBadEnemyThreshold);
  // War and alliance thresholds; break-alliance starts from the good-friend value.
  GetPropFloat(mPropList.mpObject, 0x05b7e4f5, mEscortThreshold);
  GetPropFloat(mPropList.mpObject, 0x05b7e516, mHostileThreshold);
  GetPropFloat(mPropList.mpObject, 0x02fc233b, mWarThreshold);
  GetPropFloat(mPropList.mpObject, 0x04233ced, mWarEndThreshold);
  GetPropFloat(mPropList.mpObject, 0x02fc2520, mChanceOfWar);
  mBreakAllianceThreshold = mGoodFriendThreshold;
  GetPropFloat(mPropList.mpObject, 0x041a06f8, mBreakAllianceThreshold);
  GetPropFloat(mPropList.mpObject, 0x041a06fa, mGrobInitialRelationship);
  // Empire size ratio caps fall back to the retail defaults when absent.
  mEmpireSizeRatioMinCap = 3.0f;
  GetPropFloat(mPropList.mpObject, 0x065266c0, mEmpireSizeRatioMinCap);
  mEmpireSizeRatioMaxCap = 0.0f;
  GetPropFloat(mPropList.mpObject, 0x065266cd, mEmpireSizeRatioMaxCap);
  GetPropFloat(mPropList.mpObject, 0x0295c001, mEmpireSizeRatioFactor);
  GetPropFloat(mPropList.mpObject, 0x0295c002, mCurRelationshipFactor);
  GetPropFloat(mPropList.mpObject, 0x0295c003, mMissionThreshold);
  // Gift and tribute amounts.
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
  // Tribe feedback distances and flags.
  GetPropFloat(mPropList.mpObject, 0x04d80588, mTribeFeedbackActivationDistance);
  GetPropFloat(mPropList.mpObject, 0x04d8076d, mTribeFeedbackDeactivationDistance);
  GetPropBool(mPropList.mpObject, 0x04d805be, mTribeGameBehaviorsActivated);
  GetPropFloat(mPropList.mpObject, 0x04d805bf, mSmallGiftAmount);
  GetPropFloat(mPropList.mpObject, 0x0580dfe7, mField9c);
}

// @ 0x01041090
void cSpaceRelationshipTuning_s0104_09b0::Init()
{  struct LocalAutoHandler {
    IMessageServer* mpServer;
    void* mpHandler;
    uint32_t* mpIdArray;
    int mnIdCount;
    int mnPriority;
    void AddHandler(IMessageServer* server, void* handler, uint32_t* ids) {
      mpServer = server;
      mpHandler = handler;
      mpIdArray = ids;
      mnIdCount = 1;
      mnPriority = 0;
      if (mpServer != 0 && mpHandler != 0)
        mpServer->AddHandler(mpHandler, 0xf62def);
    }
  };
  ((LocalAutoHandler*)&mpServer)->AddHandler(MessageManager(), this, gSpaceRelationshipMessageIds);
  ReloadTuning();}

// @ 0x010410e0
bool cSpaceRelationshipTuning_s0104_09b0::HandleMessage(int nMessageId, CMessage* pMessage)
{
  if (nMessageId == kTuningChangedMessage &&
      (pMessage->mnType == kPropListGroupInstance || pMessage->mnType == kUIPropListInstance))
    ReloadTuning();
  return false;
}

// @ 0x01041110
// Destroys the entry vector and base, unregisters from the message server,
// and frees the object itself when bit 0 of nFlags is set.
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

// @ 0x01041b90
bool ShaderMsgHandler::OnMessage(int msg, void* obj)
{
    if (msg == 0xf62def) {
        uint32_t group = *(uint32_t*)((uint8_t*)obj + 0x10);
        if (group == 0xf0bf332c || group == 0x073a7400)
            RegisterShaderDataInfo((void*)this);
    }
    return false;
}
