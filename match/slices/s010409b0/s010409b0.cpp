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

namespace SP {

class cSpaceRelationshipTuning {
 public:
  void* mpVTable;                           // +0x00
  char mAutoHandler[0x14];                  // +0x04
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

}  // namespace SP
