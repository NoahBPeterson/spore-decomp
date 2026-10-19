// src/game/SPEditors/SPEditorPaletteCategory.cpp -- migrated from slice(s) s005c1d70 by tools/migrate/rewrite.py
// Object file: SPEditors/SPEditorPaletteCategory.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPPaletteCategory.h"
#include "SP/cSPPaletteCategoryUI.h"
#include "EA/UTFWin/IWindow.h"
#include "EA/Variant.h"
#include "SP/cPropertyList.h"
#include "SP/cSPEditorColorPicker.h"
#include "SP/cSPEditorPageControls.h"
#include "SP/cSPPalettePage.h"
#include "SP/cSPPalettePageUI.h"
#include "SP/cSPPaletteSubCategoryUI.h"
#include "SP/cSPSwatch.h"
#include "SP/cString.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" void* EASTL_memmove(void* dst, const void* src, unsigned int n);  // 0x011e0744 (static memmove)
#include <new>
#include <string.h>

// ---- items of slice s005c1d70 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" void* EASTL_memmove(void* dst, const void* src, unsigned int n);  // 0x011e0744 (static memmove)
#define PV(n) virtual void pv##n();
namespace EA {
template <typename T>
class AutoRefCount_s005c_1d70 {
 public:
  T* mpObject;
  AutoRefCount_s005c_1d70() : mpObject(0) {}
  AutoRefCount_s005c_1d70(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
  AutoRefCount_s005c_1d70(const AutoRefCount_s005c_1d70& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
  ~AutoRefCount_s005c_1d70() { if (mpObject) mpObject->Release(); }
  T*& AsOutParam() {
    if (mpObject) {
      T* const p = mpObject;
      mpObject = 0;
      p->Release();
    }
    return mpObject;
  }
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
};
}
namespace EA {
template <typename T>
class RefCountVTemplate_s005c_1d70 {
 public:
  RefCountVTemplate_s005c_1d70() : mRefCount(0) {}
  virtual ~RefCountVTemplate_s005c_1d70() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
}
namespace EA {
namespace COM {
class IUnknown32_s005c_1d70 {
 public:
  ~IUnknown32_s005c_1d70() {}
  virtual int AddRef();
  virtual int Release();
};
}
}
namespace EA {
namespace ResourceMan {
struct Key_s005c_1d70 {
  unsigned int mInstance, mType, mGroup;
  Key_s005c_1d70() {}
  Key_s005c_1d70(unsigned int i, unsigned int t, unsigned int g) : mInstance(i), mType(t), mGroup(g) {}
};
}
}
namespace eastl {
template <typename T>
class sp_vector {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  int mAllocator[2];
  sp_vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~sp_vector() {
    if (mpBegin && ((int*)mpBegin)[-1] != 0)
      EASTL_allocator_deallocate(mpBegin);
  }
  unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
  T* begin() { return mpBegin; }
  T* end() { return mpEnd; }
  T& operator[](unsigned int i) { return mpBegin[i]; }
  T* DoInsertValue(T* position, const T& value);
  void push_back(const T& value) {
    if (mpEnd < mpCapacity)
      ::new (mpEnd++) T(value);
    else
      DoInsertValue(mpEnd, value);
  }
  T* insert(T* position, const T& value);
  T* erase(T* first, T* last) {  // trivially copyable T
    EASTL_memmove(first, last, (unsigned int)((char*)mpEnd - (char*)last));
    mpEnd -= (last - first);
    return first;
  }
  void clear() { erase(mpBegin, mpEnd); }
};
}
namespace eastl {
template <typename T>
class sp_ref_vector : public sp_vector<EA::AutoRefCount_s005c_1d70<T> > {
 public:
  typedef EA::AutoRefCount_s005c_1d70<T> value_type;
  ~sp_ref_vector();  // FUN_005c7f10 (out of line)
  value_type* erase(value_type* first, value_type* last);
  void clear() { erase(this->mpBegin, this->mpEnd); }
};
}
struct Property {
  char pad[0x12];
  unsigned short mType;  // +0x12
  bool* GetBool();       // 0x0041e920
  uint32_t* GetUInt();   // 0x0041ea00
};
namespace SP {
class cString_s005c_1d70 {
 public:
  cString_s005c_1d70();
  ~cString_s005c_1d70();
  const wchar_t* GetText();  // 0x006b55c0
  char pad[0x14];
};
}
namespace SP {
class cPropertyList_s005c_1d70 {
 public:
  virtual int AddRef();
  virtual int Release();
  PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
  virtual bool GetProperty(uint32_t id, Property*& result);  // +0x24
};
}
namespace SP {
class IPropertyManager {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, cPropertyList_s005c_1d70*& result);  // +0x2c
};
}
namespace SP {
IPropertyManager* PropertyManager();
}
namespace SP {
bool GetPropertyAsKeyInstance(cPropertyList_s005c_1d70* list, uint32_t id, uint32_t* result);
}
namespace SP {
bool GetPropertyAsKey(cPropertyList_s005c_1d70* list, uint32_t id, EA::ResourceMan::Key_s005c_1d70* result);
}
namespace SP {
bool GetPropertyKeys(cPropertyList_s005c_1d70* list, uint32_t id, int* count, EA::ResourceMan::Key_s005c_1d70** keys);
}
namespace SP {
bool GetPropertyAsText(cPropertyList_s005c_1d70* list, uint32_t id, cString_s005c_1d70* result);
}
namespace SP {
extern uint32_t kDefaultPaletteGroup;  // 0x01514dd0
}
namespace SP {
class cSPPalettePage_s005c_1d70 {
 public:
  PV(0)
  virtual int AddRef();
  virtual int Release();
  void Shutdown();  // FUN_005c7ed0
  char pad04[0x58 - 4];
  uint32_t mSequenceNumber;  // +0x58
  uint32_t mPackID;          // +0x5c
  uint32_t mRegionFilter;    // +0x60
};
}
namespace SP {
class cSPPaletteCategory_s005c_1d70 : public EA::RefCountVTemplate_s005c_1d70<int>, public EA::COM::IUnknown32_s005c_1d70 {
 public:
  eastl::sp_ref_vector<cSPPalettePage_s005c_1d70> mPages;                  // +0xc
  eastl::sp_vector<unsigned int> mPacks;                         // +0x20
  eastl::sp_ref_vector<cSPPaletteCategory_s005c_1d70> mSubCategories;       // +0x34
  unsigned int mLayoutInstanceID;                                // +0x48
  unsigned int mSequenceNumber;                                  // +0x4c
  bool mPaintByNumber;                                           // +0x50
  unsigned int mRegionFilter;                                    // +0x54
  unsigned int mSkinPaintIndex;                                  // +0x58
  cString_s005c_1d70 mCategoryName;                                         // +0x5c
  bool mHasMultiImageButton;                                     // +0x70
  unsigned int mCategoryId;                                      // +0x74
  unsigned int mParentCategory;                                  // +0x78
  EA::ResourceMan::Key_s005c_1d70 mButtonImageKey;                          // +0x7c
  EA::ResourceMan::Key_s005c_1d70* mpButtonImageKeys;                       // +0x88
  bool mIsSubCategory;                                           // +0x8c

  cSPPaletteCategory_s005c_1d70();
  ~cSPPaletteCategory_s005c_1d70();
  virtual int AddRef();
  virtual int Release();
  cSPPaletteCategory_s005c_1d70* FindSubCategory(uint32_t categoryID);
  bool Init(const EA::ResourceMan::Key_s005c_1d70& key, unsigned int layoutInstanceID);  // 0x005c1e20 (SP::cSPPaletteCategory::Init)
  void Shutdown();
  void AddSubCategory(cSPPaletteCategory_s005c_1d70* category);
  void AddPage(cSPPalettePage_s005c_1d70* page);
  unsigned int GetNumPages() { return mPages.size(); }
  cSPPalettePage_s005c_1d70* GetPage(int index);           // FUN_005c1ce0
  int CountPagesInCategory(uint32_t packID);    // FUN_005c1d10
};
}
namespace SP {
inline bool GetPropBool(cPropertyList_s005c_1d70* list, uint32_t id, bool& value) {
  Property* prop;
  if (list && list->GetProperty(id, prop) && prop->mType == 1) {
    value = *prop->GetBool();
    return true;
  }
  return false;
}
}
namespace SP {
inline bool GetPropUInt(cPropertyList_s005c_1d70* list, uint32_t id, uint32_t& value) {
  Property* prop;
  if (list && list->GetProperty(id, prop) && prop->mType == 10) {
    value = *prop->GetUInt();
    return true;
  }
  return false;
}
}
// ---- items of slice s005c1d70 end

// @ 0x005c1e20
namespace SP {
bool cSPPaletteCategory_s005c_1d70::Init(const EA::ResourceMan::Key_s005c_1d70& key, unsigned int layoutInstanceID)
{
  EA::AutoRefCount_s005c_1d70<cPropertyList_s005c_1d70> list;
  uint32_t group = key.mGroup;
  if (!group)
    group = kDefaultPaletteGroup;
  IPropertyManager* pm = PropertyManager();
  pm->GetPropertyList(key.mInstance, group, list.AsOutParam());
  if (list) {
  mCategoryId = key.mInstance;
  GetPropBool(list, 0x337bf31, mPaintByNumber);
  GetPropBool(list, 0x88025f5, mHasMultiImageButton);
  GetPropertyAsKeyInstance(list, 0xd20d4636, &mRegionFilter);
  GetPropUInt(list, 0x3e0a564, mSkinPaintIndex);
  EA::ResourceMan::Key_s005c_1d70 parentKey(0, 0, 0);
  GetPropertyAsKey(list, 0xb35d7835, &parentKey);
  mParentCategory = parentKey.mInstance;
  GetPropertyAsKey(list, 0xe6a31466, &mButtonImageKey);
  int numKeys = 0;
  GetPropertyKeys(list, 0x44f6c09, &numKeys, &mpButtonImageKeys);
  GetPropUInt(list, 0x35eeb8b5, mSequenceNumber);
  if (layoutInstanceID)
    mLayoutInstanceID = layoutInstanceID;
  else
    GetPropertyAsKeyInstance(list, 0x9a6aaae5, &mLayoutInstanceID);
  GetPropertyAsText(list, 0x2e1942a8, &mCategoryName);
    return true;
  }
  return false;
}
}  // namespace SP

// @ 0x005c2020
namespace SP {
cSPPaletteCategory_s005c_1d70::cSPPaletteCategory_s005c_1d70()
: mLayoutInstanceID(0x89845152), mSequenceNumber(0), mPaintByNumber(false), mRegionFilter(0xffffffff),
      mSkinPaintIndex(0xffffffff), mHasMultiImageButton(false), mCategoryId(0), mParentCategory(0),
      mButtonImageKey(0, 0, 0), mpButtonImageKeys(0), mIsSubCategory(false) {}
}  // namespace SP
