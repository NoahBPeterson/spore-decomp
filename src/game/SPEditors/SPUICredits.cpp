// src/game/SPEditors/SPUICredits.cpp -- migrated from slice(s) s005fe1d0 by tools/migrate/rewrite.py
// Object file: SPEditors/SPUICredits.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPUICredits.h"
#include "EA/LimitStopwatch.h"
#include "EA/Variant.h"
#include "EA/Stopwatch.h"
#include "eastl/allocator.h"
#include "SP/cPropertyList.h"
#include "SP/cPropertyManager.h"
#include "cSPUILayout.h"
#include "cSPUILayoutManager.h"
#include "SP/cString.h"
#include <string.h>
#include <intrin.h>

// ---- items of slice s005fe1d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV(n) virtual void _pv##n();
#define PV10(n) PV(n##0) PV(n##1) PV(n##2) PV(n##3) PV(n##4) PV(n##5) PV(n##6) PV(n##7) PV(n##8) PV(n##9)
void operator delete[](void* p);
namespace EA {
namespace ResourceMan {
struct Key_s005f_e1d0 {
  uint32_t instanceID;
  uint32_t typeID;
  uint32_t groupID;
  Key_s005f_e1d0() : instanceID(0), typeID(0), groupID(0) {}
  Key_s005f_e1d0(uint32_t i, uint32_t t, uint32_t g) : instanceID(i), typeID(t), groupID(g) {}
};  // namespace ResourceMan
}
}
namespace EA {
template <typename T>
class AutoRefCount_s005f_e1d0 {
 public:
  T* mpObject;
  AutoRefCount_s005f_e1d0() : mpObject(0) {}
  ~AutoRefCount_s005f_e1d0() {
    if (mpObject) mpObject->Release();
  }
  AutoRefCount_s005f_e1d0& operator=(T* pObject) {
    if (pObject != mpObject) {
      T* const pTemp = mpObject;
      if (pObject) pObject->AddRef();
      mpObject = pObject;
      if (pTemp) pTemp->Release();
    }
    return *this;
  }
  // @ 0x005fe320 (AutoRefCount<cPropertyList>::Reset, emitted out of line)
  void Reset() {
    if (mpObject) {
      T* const pTemp = mpObject;
      mpObject = 0;
      pTemp->Release();
    }
  }
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
};
}
using EA::ResourceMan::Key_s005f_e1d0;
namespace eastl {
extern wchar_t gEmptyString16[2];
}
namespace eastl {
struct allocator_s005f_e1d0 {};
}
namespace eastl {
class string16_s005f_e1d0 {
 public:
  wchar_t* mpBegin;
  wchar_t* mpEnd;
  wchar_t* mpCapacity;
  allocator_s005f_e1d0 mAllocator;
  string16_s005f_e1d0() {
    mpBegin = gEmptyString16;
    mpEnd = mpBegin;
    mpCapacity = mpBegin + 1;
  }
  ~string16_s005f_e1d0() {
    if ((mpCapacity - mpBegin) > 1 && mpBegin) operator delete[](mpBegin);
  }
  const wchar_t* c_str() const { return mpBegin; }
  string16_s005f_e1d0& operator=(const wchar_t* p);                  // 0x005c3d90
  string16_s005f_e1d0& assign(const wchar_t* pBegin, const wchar_t* pEnd);  // 0x00423650
  string16_s005f_e1d0& assign(const wchar_t* p) { return assign(p, p + CharStrlen(p)); }
  int sprintf(const wchar_t* pFormat, ...);               // 0x0041e050
  static size_t CharStrlen(const wchar_t* p) {
    const wchar_t* pCurrent = p;
    while (*pCurrent) ++pCurrent;
    return (size_t)(pCurrent - p);
  }
};
}
namespace SP {
class cString_s005f_e1d0 {  // localized string
 public:
  cString_s005f_e1d0();                                                // 0x006b5060
  ~cString_s005f_e1d0();                                               // 0x006b5240
  void SetText(uint32_t tableID, uint32_t instanceID, int a);  // 0x006b54b0
  const wchar_t* GetText();                                 // 0x006b55c0
  uint32_t mData[5];
};
}
namespace SP {
struct cLocalizedEntry {  // 12-byte localized string reference
  uint32_t mInstanceID;
  uint32_t mUnknown04;
  uint32_t mTableID;
};
}
namespace SP {
struct Property {
  uint32_t pad00[4];
  uint16_t pad10;
  int16_t mnType;  // +0x12
  uint32_t* GetValueUInt32();  // 0x0041ea00
};
}
namespace SP {
class cPropertyList_s005f_e1d0 {
 public:
  PV(0)
  virtual int Release();  // +0x04
  PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
  virtual bool GetProperty(uint32_t id, Property*& pOut);  // +0x24
  int AddRef();
};
}
namespace SP {
class cPropertyManager_s005f_e1d0 {
 public:
  PV10(0) PV(10)
  virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, EA::AutoRefCount_s005f_e1d0<cPropertyList_s005f_e1d0>& pOut);  // +0x2c
};
}
namespace SP {
cPropertyManager_s005f_e1d0* PropertyManager();  // 0x0067de30
}
namespace SP {
bool GetPropertyAsKey(cPropertyList_s005f_e1d0* list, uint32_t id, Key_s005f_e1d0* pOut);                  // 0x006a1250
}
namespace SP {
bool GetPropertyAsText(cPropertyList_s005f_e1d0* list, uint32_t id, cString_s005f_e1d0* pOut);             // 0x006a1360
}
namespace SP {
bool GetPropertyArrayText(cPropertyList_s005f_e1d0* list, uint32_t id, int* pCount, cLocalizedEntry** pArray);  // 0x006a0ae0
}
namespace SP {
inline bool GetPropertyUInt32(cPropertyList_s005f_e1d0* list, uint32_t id, uint32_t& value) {
  Property* prop;
  if (list && list->GetProperty(id, prop) && prop->mnType == 10) {
    value = *prop->GetValueUInt32();
    return true;
  }
  return false;
}
}
namespace SP {
class cSPUICredits_s005f_e1d0 {
 public:
  EA::AutoRefCount_s005f_e1d0<cPropertyList_s005f_e1d0> mCreditNamesProperties;  // +0x00
  int mNumCreditNames;                                     // +0x04
  cLocalizedEntry* mCreditNames;                           // +0x08
  eastl::string16_s005f_e1d0 mReturnString;                           // +0x0c
  uint32_t mScrollSpeed;                                   // +0x1c
  uint32_t mPropertyID;                                    // +0x20
  Key_s005f_e1d0 mBackgroundKey;                                      // +0x24
  Key_s005f_e1d0 mMusicKey;                                           // +0x30
  cString_s005f_e1d0 mTitle;                                          // +0x3c
  uint32_t mLineSpacing;                                   // +0x50
  uint32_t mFadeTime;                                      // +0x54

  cSPUICredits_s005f_e1d0();
  ~cSPUICredits_s005f_e1d0();
  void LoadNamesFromProp();  // 0x005fe340 (SP::cSPUICredits::LoadNamesFromProp)
  void SetPropertyID(uint32_t id);
  uint32_t GetCreditNameTable(uint16_t index);
  const wchar_t* GetCreditName(uint16_t index);
};
}
// ---- items of slice s005fe1d0 end

// @ 0x005fe340
namespace SP {
void cSPUICredits_s005f_e1d0::LoadNamesFromProp()
{
  mCreditNamesProperties.Reset();
  mCreditNames = 0;
  cPropertyManager_s005f_e1d0* pm = PropertyManager();
  mCreditNamesProperties.Reset();
  pm->GetPropertyList(mPropertyID, 0x9a76ea1a, mCreditNamesProperties);
  GetPropertyUInt32(mCreditNamesProperties, 0x77384c4, mScrollSpeed);
  GetPropertyUInt32(mCreditNamesProperties, 0x7bfe364, mLineSpacing);
  GetPropertyUInt32(mCreditNamesProperties, 0x7bfe376, mFadeTime);
  GetPropertyAsKey(mCreditNamesProperties, 0x774b42e, &mBackgroundKey);
  GetPropertyAsKey(mCreditNamesProperties, 0x7a2cc3d, &mMusicKey);
  GetPropertyAsText(mCreditNamesProperties, 0x7a55691, &mTitle);
  GetPropertyArrayText(mCreditNamesProperties, 0x463d294, &mNumCreditNames, &mCreditNames);
}
}  // namespace SP
