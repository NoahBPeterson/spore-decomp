// slice s010409b0 -- SP::cSpaceRelationshipTuning::ReloadTuning (1714 B).
// Flags: /O2 /MD /Gy /TP /arch:SSE
// Retail layout (size 0xa0) differs from the 2008 PDB: several gift fields are floats/ints at other offsets.
#include "types.h"

#define PV(n) virtual void _pv##n();

namespace App {
enum PropertyType { kPropBool = 1, kPropInt32 = 9, kPropFloat = 13 };

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

class PropertyList {
 public:
  virtual int AddRef();
  virtual int Release();
  PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
  virtual bool GetProperty(uint32_t id, Property** ppOut);   // +0x24
};

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

using namespace App;

inline void* operator new(unsigned int, void* pPlace) { return pPlace; }

// Everything posted to a message handler carries the message type at +0x18.
class CMessage {
 public:
  char mPad00[0x18];
  uint32_t mnType;   // +0x18
};

// The server side of the messaging framework (0x0067dcc0 hands out the singleton).
class IMessageServer {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
  virtual void AddHandler(void* pHandler, uint32_t nMessageId);   // +0x24
};

IMessageServer* MessageManager();   // 0x0067dcc0
void RemoveHandler(void* pServer, void* pHandler, uint32_t* pIdArray, int nIdCount,
                   int nPriority);   // 0x00571db0

// EASTL's allocator entry points: the size of the block is stored just below the payload.
void* EastlAllocate(int nBytes, const char* pName, int nHint, int nFlags, void* pAllocator,
                    int nLine);              // 0x00f473a0
void EastlDeallocate(void* pBlock);          // 0x00f47380
extern char gEastlAllocator;                 // 0x013ebb38

// The one message id the tuning objects listen to.
extern uint32_t gSpaceRelationshipMessageIds[];   // 0x01499ca8

namespace SP {

class cSpaceRelationshipTuning {
 public:
  void* mpVTable;                           // +0x00
  IMessageServer* mpServer;                 // +0x04
  void* mpHandler;                          // +0x08
  uint32_t* mpIdArray;                      // +0x0c
  int mnIdCount;                            // +0x10
  int mnPriority;                           // +0x14
  AutoRefCount<PropertyList> mPropList;     // +0x18
  AutoRefCount<PropertyList> mUIPropList;   // +0x1c
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

// ---------------------------------------------------------------------------
// Growable array of 0x54-byte tuning entries (an eastl::vector instance), owned by the
// message handler class below.  Only the fields the slice touches are named.
// ---------------------------------------------------------------------------
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

// Copies [pFirst, pLast) to pDest and returns the first slot past the copies (0x010408c0).
cTuningEntry* CopyEntries(cTuningEntry* pFirst, cTuningEntry* pLast, cTuningEntry* pDest);

// Base of every object that registers itself with the message server.
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

// Owner of the tuning entries: unregisters on release and drops every record.  The class itself
// adds no virtuals, so its destructor only restores the base vtable.
class cTuningEntrySet : public CMessageHandlerBase {
 public:
  cTuningEntryVector mEntries;   // +0x18

  void Release();                                     // 0x01041480
  void* ScalarDeletingDestructor(unsigned char nFlags);   // 0x01041110
};

static inline bool GetPropFloat(PropertyList* pList, uint32_t id, float& dst)
{
  Property* p;
  if (pList && pList->GetProperty(id, &p) && p->mnType == kPropFloat) {
    dst = *p->GetFloat();
    return true;
  }
  return false;
}
static inline bool GetPropInt(PropertyList* pList, uint32_t id, int& dst)
{
  Property* p;
  if (pList && pList->GetProperty(id, &p) && p->mnType == kPropInt32) {
    dst = *p->GetInt();
    return true;
  }
  return false;
}
static inline bool GetPropBool(PropertyList* pList, uint32_t id, bool& dst)
{
  Property* p;
  if (pList && pList->GetProperty(id, &p) && p->mnType == kPropBool) {
    dst = *p->GetBool();
    return true;
  }
  return false;
}

// @ 0x010409b0
void cSpaceRelationshipTuning::ReloadTuning()
{
  if (!mPropList.mpObject) {
    IPropManager* pm = PropertyManager();
    mPropList.Reset();
    pm->GetPropertyList(0x86017d53, 0x02ae0c7e, &mPropList);
  }
  if (!mUIPropList.mpObject) {
    IPropManager* pm = PropertyManager();
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

// @ 0x01041090
// Registers for the space-relationship message and pulls the tuning values from the property
// database.
void cSpaceRelationshipTuning::Init()
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

// @ 0x010410e0
// Tunings are re-read whenever either of the two relationship property lists is reloaded.
bool cSpaceRelationshipTuning::HandleMessage(int nMessageId, CMessage* pMessage)
{
  if (nMessageId == 0xf62def &&
      (pMessage->mnType == 0x86017d53 || pMessage->mnType == 0x5c770db7))
    ReloadTuning();
  return false;
}

// @ 0x01041110
// Deleting destructor: drops the record array, unregisters from the message server and releases
// the object itself when the low flag bit is set.
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

// @ 0x01041220
// Drops [pFirst, pLast): the tail moves down over the hole and the end pointer shrinks by the
// size of the dropped range.
cTuningEntry* cTuningEntryVector::EraseRange(cTuningEntry* pFirst, cTuningEntry* pLast)
{
  cTuningEntry* pEnd = mpEnd;   // the copies may alias the vector object, so cache the end
  cTuningEntry* p = pFirst;
  for (cTuningEntry* q = pLast; q != pEnd; ++q, ++p)
    *p = *q;
  mpEnd -= pLast - pFirst;
  return pFirst;
}

// @ 0x01041280
// Inserts one record in front of pPos, growing the buffer to twice its element count when it is
// full (0x54 bytes each, allocated through the "Simulator" allocator).
void cTuningEntryVector::Insert(cTuningEntry* pPos, const cTuningEntry& value)
{
  if (mpEnd != mpCap) {
    const cTuningEntry* pValue = &value;
    // A record that is already stored at or after the insertion point moves up with the tail.
    if (pValue >= pPos && pValue < mpEnd)
      ++pValue;
    // The shift is a move_backward with its first copy peeled off.
    if (mpEnd != 0)
      *mpEnd = mpEnd[-1];
    cTuningEntry* pSrc = mpEnd - 1;
    cTuningEntry* pDst = mpEnd;
    while (pSrc != pPos) {
      --pSrc;
      --pDst;
      *pDst = *pSrc;
    }
    *pPos = *pValue;
    ++mpEnd;
    return;
  }

  int nCount = (int)(mpEnd - mpBegin);
  int nNewCap = (nCount != 0) ? (nCount * 2) : 1;
  cTuningEntry* pNew = (nNewCap != 0)
                           ? (cTuningEntry*)EastlAllocate(nNewCap * (int)sizeof(cTuningEntry),
                                                          "Simulator", 0, 0, &gEastlAllocator, 0xd1)
                           : 0;
  cTuningEntry* pNewEnd = CopyEntries(mpBegin, pPos, pNew);
  if (pNewEnd != 0)
    *pNewEnd = value;
  pNewEnd = CopyEntries(pPos, mpEnd, pNewEnd + 1);
  if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0)
    EastlDeallocate(mpBegin);
  mpEnd = pNewEnd;
  mpBegin = pNew;
  mpCap = pNew + nNewCap;
}

// @ 0x010413b0
// Appends a record holding the default tuning values.
void cTuningEntryVector::PushDefault()
{
  if (mpEnd < mpCap) {
    cTuningEntry* p = mpEnd++;
    if (p != 0)
      new (p) cTuningEntry();
  } else {
    cTuningEntry entry;
    Insert(mpEnd, entry);
  }
}

// @ 0x01041480
// Unregisters the handler and empties the record array (the buffer itself is kept).
void cTuningEntrySet::Release()
{
  if (mpServer != 0) {
    IMessageServer* pServer = mpServer;
    mpServer = 0;
    RemoveHandler(pServer, mpHandler, mpIdArray, mnIdCount, mnPriority);
  }
  mEntries.EraseRange(mEntries.mpBegin, mEntries.mpEnd);
}

// Defined out of line on purpose: the retail build keeps this a real call (0x010408c0).
__declspec(noinline) cTuningEntry* CopyEntries(cTuningEntry* pFirst, cTuningEntry* pLast,
                                               cTuningEntry* pDest)
{
  while (pFirst != pLast)
    *pDest++ = *pFirst++;
  return pDest;
}

}  // namespace SP
