// Slice s005c4500 (this module) defines its own 2-argument placement `operator new`; <new> defines the same
// overload, so suppress the standard one (the slice's definition, emitted in the items section below, is used
// instead).  See report_s005c4500.md REQUESTS: rewrite.py should drop a slice's placement-new definition when
// the TU includes <new>.
#define __PLACEMENT_NEW_INLINE 1
// src/game/SPEditors/SPEditorPaletteCategoryUI.cpp -- migrated from slice(s) s005c2d30, s005c1d70 by tools/migrate/rewrite.py
// Object file: SPEditors/SPEditorPaletteCategoryUI.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPPaletteCategoryUI.h"
#include "EA/UTFWin/IWindow.h"
#include "EA/Variant.h"
#include "SP/cDirectPropertyList.h"
#include "SP/cSPEditorColorPicker.h"
#include "SP/cSPEditorPageControls.h"
#include "SP/cSPPaletteCategory.h"
#include "SP/cSPPalettePage.h"
#include "SP/cSPPalettePageUI.h"
#include "SP/cSPPaletteSubCategoryUI.h"
#include "SP/cSPSwatch.h"
#include "SP/cSPEditorVerbIconTray.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" void* EASTL_memmove(void* dst, const void* src, unsigned int n);  // 0x011e0744 (static memmove)
#include <new>
#include <string.h>
#include "cSPColorRGB.h"
#include "SP/cSPPaletteItem.h"
#include "cSPUILayout.h"
#include "SP/tSPEditorPaint.h"
// EA::Messaging::Server: retail MessageServer() (0x0067dcc0) returns it; the slice stubs (IMessageServer)
// are partial views.  See report_s005c53c0.md.
#include "EA/Messaging/AutoHandler.h"
#include "EA/Messaging/Server.h"
#include "EA/IO/FileStream.h"
#include "EA/ResourceMan/Key.h"
#include "SP/cTribePlanner.h"
#include "SP/cSPEditorPaintLikeThis.h"
#include "SP/cGonzagoSimulator.h"

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
namespace EA {
struct RectT_s005c_1d70 {
  float left, top, right, bottom;
  float Width() const { return right - left; }
  float Height() const { return bottom - top; }
};
}
namespace EA {
namespace UTFWin {
class IWindow_s005c_1d70 {
 public:
  PV(0) PV(1) PV(2) PV(3)
  virtual IWindow_s005c_1d70* GetParent();                     // +0x10
  PV(5) PV(6) PV(7) PV(8) PV(9)
  virtual uint32_t GetFlags();                      // +0x28
  PV(11) PV(12)
  virtual const RectT_s005c_1d70& GetRealArea();               // +0x34
  virtual const RectT_s005c_1d70& GetArea();                   // +0x38
  PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23)
  virtual void SetArea(const RectT_s005c_1d70& area);          // +0x60
  PV(25) PV(26) PV(27) PV(28) PV(29) PV(30)
  virtual void SetFlag(int flag, bool value);       // +0x7c
};  // namespace UTFWin
}
}
using EA::UTFWin::IWindow_s005c_1d70;
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
struct PackInfo {
  uint32_t mPackID;   // +0x0
  int mPriority;      // +0x4
};
}
namespace SP {
struct PackDescription {
  uint32_t mData[6];           // +0x0
  EA::ResourceMan::Key_s005c_1d70 mKey;   // +0x18
  cString_s005c_1d70 mName;               // +0x24
};
}
namespace SP {
class cPackageManager {
 public:
  PackInfo* GetPackInfo(uint32_t packID);               // FUN_007db5e0
  PackDescription* GetPackDescription(int index);       // FUN_007db620
  eastl::sp_vector<PackInfo*>& GetPacks();              // FUN_00572590
};
}
namespace SP {
cPackageManager* PackageManager();  // FUN_0067dea0
}
namespace SP {
bool KeysEqual(const EA::ResourceMan::Key_s005c_1d70* a, const EA::ResourceMan::Key_s005c_1d70* b);  // FUN_004eb930
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
class cSPUILayout {
 public:
  IWindow_s005c_1d70* FindWindowByID(uint32_t id, bool recursive);
};
}
namespace SP {
class cSPEditorColorPicker_s005c_1d70 { public: void Update(int deltaTime); /* FUN_005a6db0 */ };
}
namespace SP {
class cSPEditorPageControls_s005c_1d70 { public: void Update(int deltaTime); };
}
namespace SP {
class cSPPaletteSubCategoryUI_s005c_1d70 {
 public:
  void Update(int deltaTime);                    // FUN_005c98a0
  class cSPPaletteCategoryUI_s005c_1d70* GetParentUI();  // FUN_005c9830
};
}
namespace SP {
class cSPPalettePageUI_s005c_1d70 { public: void Update(int deltaTime); /* FUN_005c8d30 */ };
}
namespace SP {
class cSPSwatch_s005c_1d70 {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  virtual void SetVisible(bool visible);  // +0x2c
};
}
namespace SP {
class IWinButton {
 public:
  PV(0) PV(1) PV(2) PV(3)
  virtual IWindow_s005c_1d70* ToWindow();  // +0x10
};
}
namespace SP {
struct PageUIEntry {
  cSPPalettePageUI_s005c_1d70* mpPageUI;  // +0x0
  bool mVisible;               // +0x4
  bool pad5;
  bool mDisabled;              // +0x6
  bool pad7;
};
}
namespace SP {
class cSPPaletteCategoryUI_s005c_1d70 {
 public:
  char pad00[0x10];
  cSPUILayout* mLayout;                        // +0x10
  char pad14[4];
  IWindow_s005c_1d70* mWinCategory;                       // +0x18
  char pad1c[4];
  IWindow_s005c_1d70* mWinEPUIHolder;                     // +0x20
  char pad24[0x30 - 0x24];
  cSPEditorColorPicker_s005c_1d70* mColorPicker1;         // +0x30
  cSPEditorColorPicker_s005c_1d70* mColorPicker2;         // +0x34
  char pad38[0x68 - 0x38];
  cSPSwatch_s005c_1d70* mPreviewSwatch;                   // +0x68
  cSPPaletteCategory_s005c_1d70* mData;                   // +0x6c
  cSPEditorPageControls_s005c_1d70* mPageControls;        // +0x70
  eastl::sp_vector<IWinButton*> mPackButtons;  // +0x74
  eastl::sp_vector<PageUIEntry> mPageUIs;      // +0x88
  cSPPaletteSubCategoryUI_s005c_1d70* mSubCategoryUI;     // +0x9c
  int mCurrentPageIndex;                       // +0xa0
  int mFilterSetId;                            // +0xa4
  int mExpansionPackChunkIndex;                // +0xa8
  unsigned int mCurrentPackID;                 // +0xac
  int mExpansionPacksPerPage;                  // +0xb0

  void SetVisibleChunk(int chunkIndex);  // 0x005c2590 (SP::cSPPaletteCategoryUI::SetVisibleChunk)
  void SetButtonPositions();  // 0x005c2660 (SP::cSPPaletteCategoryUI::SetButtonPositions)
  void Update(int deltaTime);
  bool IsVisible();
  void SetVisibility(bool visible);
  void SetPageVisible(int index, bool visible);
  bool IsPageVisible(int index);
  int GetPageIndexForPackID(uint32_t packID);
  int GetChunkIndexForPackID(uint32_t packID);
  bool IsPaintByNumber();
  uint32_t GetRegionFilterID();
  bool IsPackUnique(int index);
  int GetNumUniquePacks();
};
}
namespace SP {
static inline bool SameDescription(const PackDescription* a, const PackDescription* b) {
  return a->mData[0] == b->mData[0] && a->mData[1] == b->mData[1] && a->mData[2] == b->mData[2] &&
         a->mData[3] == b->mData[3] && a->mData[4] == b->mData[4] && a->mData[5] == b->mData[5];
}
}
// ---- items of slice s005c1d70 end

// ---- items of slice s005c2d30 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" long __cdecl _InterlockedExchange(long volatile* target, long value);
#pragma intrinsic(_InterlockedExchange)
namespace EA {
template <typename T>
class AutoRefCount_s005c_2d30 {
 public:
  T* mpObject;
  AutoRefCount_s005c_2d30() : mpObject(0) {}
  AutoRefCount_s005c_2d30(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
  AutoRefCount_s005c_2d30(const AutoRefCount_s005c_2d30& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
  ~AutoRefCount_s005c_2d30() { if (mpObject) mpObject->Release(); }
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
class RefCountVTemplate_s005c_2d30 {
 public:
  RefCountVTemplate_s005c_2d30() : mRefCount(0) {}
  virtual ~RefCountVTemplate_s005c_2d30() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
}
namespace EA {
namespace COM {
class IUnknown32_s005c_2d30 {
 public:
  ~IUnknown32_s005c_2d30() {}
  virtual int AddRef();
  virtual int Release();
};
}
}
namespace EA {
namespace ResourceMan {
struct Key_s005c_2d30 {
  unsigned int mInstance, mType, mGroup;
  Key_s005c_2d30() {}
  Key_s005c_2d30(unsigned int i, unsigned int t, unsigned int g) : mInstance(i), mType(t), mGroup(g) {}
};
}
}
namespace EA {
struct RectT_s005c_2d30 {
  float left, top, right, bottom;
  RectT_s005c_2d30() {}
  RectT_s005c_2d30(const RectT_s005c_2d30& r) : left(r.left), top(r.top), right(r.right), bottom(r.bottom) {}
  float Width() const { return right - left; }
  float Height() const { return bottom - top; }
};
}
namespace EA {
namespace UTFWin {
class IWindow_s005c_2d30 {
 public:
  PV(0) PV(1) PV(2) PV(3)
  virtual IWindow_s005c_2d30* GetParent();                     // +0x10
  PV(5) PV(6) PV(7) PV(8) PV(9)
  virtual uint32_t GetFlags();                      // +0x28
  PV(11) PV(12)
  virtual const RectT_s005c_2d30& GetRealArea();               // +0x34
  virtual const RectT_s005c_2d30& GetArea();                   // +0x38
  PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23)
  virtual void SetArea(const RectT_s005c_2d30& area);          // +0x60
  PV(25) PV(26)
  virtual void SetLayoutArea(const RectT_s005c_2d30& area);   // +0x6c
  PV(28) PV(29) PV(30)
  virtual void SetFlag(int flag, bool value);       // +0x7c
};  // namespace UTFWin
}
}
using EA::UTFWin::IWindow_s005c_2d30;
namespace eastl {
template <typename T>
struct copy_impl_do {
  static T* do_copy(T* first, T* last, T* result);  // copy_impl<0,random_access>::do_copy
};
}
namespace eastl {
template <typename T>
inline T* copy(T* first, T* last, T* result) {
  return copy_impl_do<T>::do_copy(first, last, result);
}
}
namespace eastl {
template <typename T>
class sp_ref_vector_s005c_2d30 : public sp_vector<EA::AutoRefCount_s005c_2d30<T> > {
 public:
  typedef EA::AutoRefCount_s005c_2d30<T> value_type;
  ~sp_ref_vector_s005c_2d30();  // FUN_005c7f10 (out of line)
  value_type* erase(value_type* first, value_type* last);
  void clear() { erase(this->mpBegin, this->mpEnd); }
};
}
struct Property {
  char pad[0x12];
  unsigned short mType;  // +0x12
  bool* GetBool();       // 0x0041e920
  uint32_t* GetUInt();   // 0x0041ea00
  float* GetFloat();     // 0x0041ea70
};
namespace SP {
class cString_s005c_2d30 {
 public:
  cString_s005c_2d30();
  ~cString_s005c_2d30();
  const wchar_t* GetText();  // 0x006b55c0
  char pad[0x14];
};
}
namespace SP {
class cPropertyList_s005c_2d30 {
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
  virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, cPropertyList_s005c_2d30*& result);  // +0x2c
};
}
namespace SP {
IPropertyManager* PropertyManager();
}
namespace SP {
class cSPPalettePage_s005c_2d30 {
 public:
  PV(0)
  virtual int AddRef();
  virtual int Release();
  void Shutdown();  // FUN_005c7ed0
  char pad04[0x58 - 4];
  uint32_t mSequenceNumber;  // +0x58
  uint32_t mPackID;          // +0x5c
  uint32_t mRegionFilter;    // +0x60
  char pad64[0x70 - 0x64];
  eastl::sp_vector<class cSPPaletteItem_s005c_2d30*> mItems;  // +0x70
  cSPPaletteItem_s005c_2d30* GetItem(int index);             // FUN_005c7f00
};
}
namespace SP {
class cSPPaletteCategory_s005c_2d30 : public EA::RefCountVTemplate_s005c_2d30<int>, public EA::COM::IUnknown32_s005c_2d30 {
 public:
  eastl::sp_ref_vector_s005c_2d30<cSPPalettePage_s005c_2d30> mPages;                  // +0xc
  eastl::sp_vector<unsigned int> mPacks;                         // +0x20
  eastl::sp_ref_vector_s005c_2d30<cSPPaletteCategory_s005c_2d30> mSubCategories;       // +0x34
  unsigned int mLayoutInstanceID;                                // +0x48
  unsigned int mSequenceNumber;                                  // +0x4c
  bool mPaintByNumber;                                           // +0x50
  unsigned int mRegionFilter;                                    // +0x54
  unsigned int mSkinPaintIndex;                                  // +0x58
  cString_s005c_2d30 mCategoryName;                                         // +0x5c
  bool mHasMultiImageButton;                                     // +0x70
  unsigned int mCategoryId;                                      // +0x74
  unsigned int mParentCategory;                                  // +0x78
  EA::ResourceMan::Key_s005c_2d30 mButtonImageKey;                          // +0x7c
  EA::ResourceMan::Key_s005c_2d30* mpButtonImageKeys;                       // +0x88
  bool mIsSubCategory;                                           // +0x8c

  cSPPaletteCategory_s005c_2d30();
  ~cSPPaletteCategory_s005c_2d30();
  virtual int AddRef();
  virtual int Release();
  cSPPaletteCategory_s005c_2d30* FindSubCategory(uint32_t categoryID);
  bool Init(const EA::ResourceMan::Key_s005c_2d30& key, unsigned int layoutInstanceID);  // 0x005c1e20 (SP::cSPPaletteCategory::Init)
  void Shutdown();
  void AddSubCategory(cSPPaletteCategory_s005c_2d30* category);
  void AddPage(cSPPalettePage_s005c_2d30* page);
  unsigned int GetNumPages() { return mPages.size(); }
  cSPPalettePage_s005c_2d30* GetPage(int index);           // FUN_005c1ce0
  int CountPagesInCategory(uint32_t packID);    // FUN_005c1d10
};
}
namespace SP {
struct cSPColorRGB {
  float r, g, b;
  cSPColorRGB() {}
  cSPColorRGB(const cSPColorRGB& c) : r(c.r), g(c.g), b(c.b) {}
  bool operator!=(const cSPColorRGB& c) const { return r != c.r || g != c.g || b != c.b; }
};
}
namespace SP {
extern cSPColorRGB kDefaultPaintColor;  // 0x015150b0
}
namespace SP {
extern cSPColorRGB kWhiteColor;         // 0x015ebbf8 (guessed)
}
namespace SP {
struct tSPEditorPaint_s005c_2d30 {
  unsigned int mPaint;   // +0x0
  cSPColorRGB mColor1;   // +0x4
  cSPColorRGB mColor2;   // +0x10
};
}
namespace SP {
bool GetPropertyAsColorRGB(cPropertyList_s005c_2d30* list, uint32_t id, cSPColorRGB* result);                // 0x006a11b0
}
namespace SP {
bool GetPropertyColors(cPropertyList_s005c_2d30* list, uint32_t id, int* count, cSPColorRGB** colors);      // 0x006a0a70
}
namespace SP {
extern uint32_t kPaintPropertyGroup;  // 0x01515094
}
namespace SP {
inline bool GetPropFloat(cPropertyList_s005c_2d30* list, uint32_t id, float& value) {
  Property* prop;
  if (list && list->GetProperty(id, prop) && prop->mType == 13) {
    value = *prop->GetFloat();
    return true;
  }
  return false;
}
}
namespace SP {
class cSPPaletteItem_s005c_2d30 {
 public:
  char pad[0xc];
  uint32_t mItemID;    // +0xc
  char pad10[0x24 - 0x10];
  uint32_t mItemType;  // +0x24
};
}
namespace SP {
class cSPUILayout_s005c_2d30 {
 public:
  IWindow_s005c_2d30* FindWindowByID(uint32_t id, bool recursive);  // 0x008105b0 (SP::cSPUILayout::FindWindowByID)
};
}
namespace SP {
class cSPEditorColorPicker_s005c_2d30 {
 public:
  bool IsEnabled();                         // FUN_005a41e0
  void SetAlphaEnabled(bool enabled);       // FUN_005a4200
  void SetArea(EA::RectT_s005c_2d30 area);             // FUN_005a4800
  void SetPaletteColor(const cSPColorRGB& color);  // FUN_005a4920
  void SetColor(const cSPColorRGB& color);  // FUN_005a4e20
  void SetDefault();                        // FUN_005a4fb0
};
}
namespace SP {
class cSPPalettePageUI_s005c_2d30 {
 public:
  virtual int AddRef();
  virtual int Release();
  void SetVisible(bool visible);  // FUN_005c8bf0
  uint32_t GetPackID();           // FUN_005c8fc0
};
}
namespace SP {
class cSPPaletteSubCategoryUI_s005c_2d30 {
 public:
  class cSPPaletteCategoryUI_s005c_2d30* GetParentUI();  // FUN_005c9830
};
}
namespace SP {
class cSwatchMaterial {
 public:
  char pad[4];
  uint32_t mFlags;           // +0x4
  char pad8[0x4c - 8];
  cSPColorRGB mColor;        // +0x4c
  float mAlpha;              // +0x58
  char mLayer;               // +0x5c
  void SetColor(const cSPColorRGB& color) {
    mFlags |= 2;
    mColor = color;
  }
  void SetAlpha(float alpha) {
    mAlpha = alpha;
    mFlags |= 8;
  }
};
}
namespace SP {
extern cSPColorRGB kSwatchColor;  // 0x01514eb8
}
namespace SP {
struct cSwatchMaterialSlot;
}
namespace SP {
cSwatchMaterialSlot* AddBoundingBox(cSwatchMaterial* material, int index);  // 0x0067cad0
}
namespace SP {
class cSwatchMaterialSlot { public: void* GetModel(); /* FUN_006c10e0 */ };
}
namespace SP {
namespace EditorUtils {
void CreateAndSetPaintMaterial(tSPEditorPaint_s005c_2d30 paint, void* model);  // 0x004b8180
}
}
namespace SP {
class cSPSwatch_s005c_2d30 {
 public:
  char pad[0x118];
  cSwatchMaterial* mpMaterial;  // +0x118
};
}
namespace SP {
class cAppPropertiesData { public: char pad[0x118]; int mbExpansionPacksOnly; };
}
namespace SP {
class cAppProperties { public: char pad[0x3c]; cAppPropertiesData* mpData; };
}
namespace SP {
extern cAppProperties* sAppProperties;  // 0x015fd918
}
namespace SP {
class cSPEditorPaintLikeThisBase { public: virtual void v0(); int mA, mB; };
}
namespace SP {
class cSPEditorPaintLikeThisRef {
 public:
  virtual int AddRef();
  virtual int Release();
};
}
namespace SP {
class cSPEditorPaintLikeThis_s005c_2d30 : public cSPEditorPaintLikeThisBase, public cSPEditorPaintLikeThisRef {};
}
namespace EA {
template <typename T>
class AutoRefPtr {  // EA::AutoRefCount with operator=
 public:
  T* mpObject;
  AutoRefPtr(const AutoRefPtr& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
  ~AutoRefPtr() { if (mpObject) mpObject->Release(); }
  AutoRefPtr& operator=(const AutoRefPtr& x) { return operator=(x.mpObject); }
  AutoRefPtr& operator=(T* pObject) {
    if (pObject != mpObject) {
      T* const pTemp = mpObject;
      if (pObject)
        pObject->AddRef();
      mpObject = pObject;
      if (pTemp)
        pTemp->Release();
    }
    return *this;
  }
};
}
namespace EA {
namespace Audio {
class IAudioSystem {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7)
  virtual uint32_t GetState();                         // +0x20
  PV(9) PV(10) PV(11) PV(12) PV(13)
  virtual void Begin(uint32_t id);                     // +0x38
  PV(15)
  virtual void SetParam(uint32_t id, uint32_t value);  // +0x40
  PV(17) PV(18) PV(19) PV(20) PV(21)
  virtual void End();                                  // +0x58
};
}
}
namespace EA {
namespace Audio {
IAudioSystem* GetSystemAT();
}
}
namespace EA {
namespace Messaging {
union Data_s005c_2d30 {
  uint32_t mUint32;
  uint64_t mUint64;
};
}
}
namespace EA {
namespace Messaging {
class IMessageRC_s005c_2d30 {
 public:
  virtual int AddRef();
};
}
}
namespace EA {
namespace Messaging {
class BehaviorMessage : public IMessageRC_s005c_2d30 {
 public:
  BehaviorMessage(uint32_t id) {
    mID = id;
    _InterlockedExchange(&mRefCount, 0);
  }
  long mRefCount;    // +0x4
  Data_s005c_2d30 mData[5];     // +0x8
  uint32_t mID;      // +0x30
  uint32_t pad34;
};
}
}
namespace EA {
namespace Messaging {
class MessageBasicRC5 : public BehaviorMessage {
 public:
  MessageBasicRC5(uint32_t id) : BehaviorMessage(id), mResult(0) {}
  ~MessageBasicRC5();  // SlotMessage::Destruct (0x00421cf0)
  virtual int AddRef();
  uint32_t mResult;  // +0x38
};
}
}
namespace EA {
namespace Messaging {
class IMessageServer_s005c_2d30 {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4)
  virtual bool MessageSend(uint32_t id, IMessageRC_s005c_2d30* msg, void* handler);  // +0x14
};
}
}
namespace SP {
EA::Messaging::Server* MessageServer();
}
namespace SP {
struct PageUIEntry_s005c_2d30 {
  EA::AutoRefPtr<cSPPalettePageUI_s005c_2d30> mpPageUI;  // +0x0
  bool mVisible;                              // +0x4
  bool mShown;                                // +0x5
  bool mDisabled;                             // +0x6
};
}
namespace SP {
typedef EA::AutoRefPtr<cSPEditorPaintLikeThis_s005c_2d30> PaintLikeThisRef;
}
namespace SP {
struct PageUIEntryAssign : PageUIEntry_s005c_2d30 {
  PageUIEntryAssign& operator=(const PageUIEntryAssign& x);
};
}
namespace SP {
class cSPPaletteCategoryUI_s005c_2d30 {
 public:
  char pad00[0x10];
  cSPUILayout_s005c_2d30* mLayout;                          // +0x10
  cSPUILayout_s005c_2d30* mExpansionPackLayout;             // +0x14
  IWindow_s005c_2d30* mWinCategory;                         // +0x18
  IWindow_s005c_2d30* mWinPageButtons;                      // +0x1c
  IWindow_s005c_2d30* mWinEPUIHolder;                       // +0x20
  IWindow_s005c_2d30* mWinColorPickerHolder;                // +0x24
  IWindow_s005c_2d30* mWinPalettePage;                      // +0x28
  IWindow_s005c_2d30* mWinFullPalettePage;                  // +0x2c
  cSPEditorColorPicker_s005c_2d30* mColorPicker1;           // +0x30
  cSPEditorColorPicker_s005c_2d30* mColorPicker2;           // +0x34
  EA::RectT_s005c_2d30 mOriginalColorPickerArea1;           // +0x38
  EA::RectT_s005c_2d30 mOriginalColorPickerArea2;           // +0x48
  EA::RectT_s005c_2d30 mOriginalColorPickerAreaUnion;       // +0x58
  cSPSwatch_s005c_2d30* mPreviewSwatch;                     // +0x68
  cSPPaletteCategory_s005c_2d30* mData;                     // +0x6c
  void* mPageControls;                           // +0x70
  eastl::sp_vector<void*> mPackButtons;          // +0x74
  eastl::sp_vector<PageUIEntry_s005c_2d30> mPageUIs;        // +0x88
  cSPPaletteSubCategoryUI_s005c_2d30* mSubCategoryUI;       // +0x9c
  int mCurrentPageIndex;                         // +0xa0
  uint32_t mFilterSetId;                         // +0xa4
  int mExpansionPackChunkIndex;                  // +0xa8
  uint32_t mCurrentPackID;                       // +0xac
  int mExpansionPacksPerPage;                    // +0xb0
  char mAutoMsgHandler[0x14];                    // +0xb4
  uint32_t mSelectedItemID;                      // +0xc8
  cSPColorRGB mSelectedColor1;                   // +0xcc
  cSPColorRGB mSelectedColor2;                   // +0xd8
  bool mIsColor1Default;                         // +0xe4
  bool mIsColor2Default;                         // +0xe5

  int GetNumUniquePacks();  // 0x005c2aa0
  tSPEditorPaint_s005c_2d30 GetSelectedPaint();
  uint32_t GetSkinPaintIndex();
  bool IsColor1Default();
  void SetPackPaneVisible(bool visible);
  void SetWindowPositions();
  void UpdatePreviewSwatch();
  void SetSelectedPaint(const tSPEditorPaint_s005c_2d30& paint);
  bool HandleMessage(uint32_t messageID, void* message);
  void OnPageChanged(int oldIndex, int newIndex);
  bool SetPageIndex(int index);
  bool CyclePage(int direction);  // 0x005c3c20 (SP::cSPPaletteCategoryUI::CyclePage)
  void SetSelectedPack(uint32_t packID);  // FUN_005c3cb0
  cSPPaletteCategory_s005c_2d30* GetPaletteCategoryData() { return mData; }
  cSPPaletteSubCategoryUI_s005c_2d30* GetSubCategoryUI() { return mSubCategoryUI; }
  cSPPalettePageUI_s005c_2d30* GetPageUI(int index) {
    if (index >= 0 && index < (int)mPageUIs.size())
      return mPageUIs[index].mpPageUI.mpObject;
    return 0;
  }
};
}
namespace SP {
struct cItemSelectedMessage {
  char pad[0x20];
  struct ISource {
    PV(0) PV(1) PV(2)
    virtual cSPPaletteItem_s005c_2d30* Cast(uint32_t typeID);  // +0xc
  }* mpSource;  // +0x20
};
}
namespace SP {
struct cColorPickerSourceBase { char pad[8]; };
}
namespace SP {
struct cColorPickerMessage {
  char pad[8];
  uint32_t mColorID;   // +0x8
  char padc[4];
  struct Source : cColorPickerSourceBase {}* mpSource;  // +0x10 (points 8 bytes into the picker)
  char pad14[0x20 - 0x14];
  int mIsDefault;      // +0x20
};
}
namespace SP {
cSPColorRGB ColorFromID(uint32_t colorID);  // 0x00576ab0
}
// ---- items of slice s005c2d30 end

// ---- items of slice s005c4500 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern wchar_t g_EmptyString[2];  // 0x1667bac
extern float g_PackPaneGap;  // 0x1486110 (5.0f)
extern float g_TooltipOffsetY;  // 0x1473c70 (10.0f)
extern const char g_TooltipFlag[];  // 0x13f7f24
typedef int(__thiscall* VF0)(void*);
typedef int(__thiscall* VF1)(void*, int);
typedef int(__thiscall* VF2)(void*, int, int);
#define VSLOT(o, off) ((*(void***)(o))[(off) / 4])
static inline int vc0(void* o, int off) { return ((VF0)VSLOT(o, off))(o); }
static inline int vc1(void* o, int off, int a) { return ((VF1)VSLOT(o, off))(o, a); }
static inline int vc2(void* o, int off, int a, int b) { return ((VF2)VSLOT(o, off))(o, a, b); }
static inline void ResetRef(void** field, int off) {
  void* p = *field;
  if (p) {
    *field = 0;
    vc0(p, off);
  }
}
void* operator new(unsigned int, const char*, int, int, int, int);   // 0x00f473a0
void operator delete(void* p);   // 0x00f47380
inline void* operator new(unsigned int, void* p) { return p; }
struct Rect4 {
  float x1, y1, x2, y2;
};
struct Vec2 {
  float x, y;
};
struct TipString {
  wchar_t* mpBegin;
  wchar_t* mpEnd;
  wchar_t* mpCapacity;
  TipString() : mpBegin(g_EmptyString), mpEnd(g_EmptyString), mpCapacity(g_EmptyString + 1) {}
  ~TipString() {
    if ((((int)mpCapacity - (int)mpBegin) & ~1) > 2 && mpBegin)
      delete[] mpBegin;
  }
  void append(const wchar_t* s);  // lib_eatext basic_string::append (0x5c3d90)
};
struct cSPUILayout_s005c_4500 {
  char pad[0x18];
  cSPUILayout_s005c_4500();  // 0x810000
  ~cSPUILayout_s005c_4500();  // 0x811fe0
  bool Init(const uint32_t* key, int a, uint32_t b);  // 0x8120d0
  void SetParentWin(void* win, int a, uint32_t b);  // 0x8121b0
  void* FindWindowByID(uint32_t id, int recursive);  // 0x8105b0
  void Shutdown(int a);  // 0x811ad0
};
struct cString {
  const wchar_t* GetText();  // 0x6b55c0
};
struct PackInfo_s005c_4500 {
  int id;  // +0
  int pad4;
  uint32_t layoutInstance;  // +8
  char iconKey[0xc];  // +0xc image key (first word non-zero when present)
  char iconKey2[0xc];  // +0x18 second image key
  cString name;  // +0x24
};
struct PackVec {
  PackInfo_s005c_4500** mpBegin;
  PackInfo_s005c_4500** mpEnd;
};
struct cSPUIStdDrawable {
  void SetImageIcon(int a, void* image);  // 0x831760
};
struct cSPUITooltipWinProc_s005c_4500 {
  cSPUITooltipWinProc_s005c_4500(const wchar_t* name, uint32_t id, const wchar_t* text, const Vec2* offset, int a, const void* b,
                      int c);  // 0x835e30
};
struct ImageRef {
  void* mpObject;
  void** AsPPType() { return &mpObject; }  // 0xa16f40
};
namespace SPUIHelpers {
bool __cdecl CreateImageFromResource(const void* key, void** image, int a, int b, int c);  // 0x806230
}
namespace SPUIHelpers {
void __cdecl SetWindowAreaToParent(void* win);  // 0x806bf0
}
void* __cdecl TooltipAlloc(unsigned int size, int align, const char* name, void* heap);  // 0x9512d0
void* __cdecl TooltipHeap();  // 0x9512c0
struct AppProps {
  char pad[0x118];
  int mFlag118;
};
struct AppPropsHolder {
  char pad[0x3c];
  AppProps* mpProps;
};
extern AppPropsHolder* g_AppProps;  // 0x15fd918
struct SwatchHelper {
  void Release();  // 0x5f0a60
};
SwatchHelper* __stdcall SwatchOwner(void* swatch);  // 0x401020
namespace EA {
namespace Messaging {
void __cdecl RemoveHandler(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e);  // 0x571db0
}
}
namespace SP {
struct PaintLikeVec {
  void** mpBegin;
  void** mpEnd;
  void Erase(void** first, void** last);  // FUN_005c41b0 (vector erase, this = the vector at +0xe8)
};
}
namespace SP {
class cSPSubCategoryUI {
 public:
  void Shutdown();  // FUN_005ca7b0
};
}
namespace SP {
class cSPPalettePageUI_s005c_4500 {
 public:
  void Shutdown();  // 0x5c8cc0
  void Detach();  // 0x5c8cc0
  void SetSwatchFlag(int flag);  // 0x5c8bf0
  cSPPalettePageUI_s005c_4500();  // 0x5c9010
  void Init(void* page, void* win, int a2, int index, bool isSubCategory);  // 0x5c9230
  static void* operator new(unsigned int sz, const char* n, int a, int b, int c, int d) {
    return ::operator new(sz, n, a, b, c, d);
  }
};
}
namespace SP {
class cSPPalettePage_s005c_4500 {
 public:
  char pad[0x5c];
  uint32_t mPaintId;  // +0x5c
};
}
namespace SP {
class cSPPaletteCategory_s005c_4500 {
 public:
  char pad[0xc];
  cSPPalettePage_s005c_4500** mPagesBegin;  // +0xc
  cSPPalettePage_s005c_4500** mPagesEnd;  // +0x10
  char pad14[0x6c - 0x14];
  uint32_t mCategoryId;  // +0x6c
  char pad70[0x8c - 0x70];
  bool mIsSubCategory;  // +0x8c
  cSPPalettePage_s005c_4500* GetPage(int i);  // 0x5c1ce0
  int CountFor(int packId);  // 0x5c1d10
};
}
namespace SP {
class cSPEditorColorPicker_s005c_4500 {
 public:
  void Clear();  // 0x5a6390
};
}
namespace SP {
class cSPEditorPageControls_s005c_4500 {
 public:
  void Shutdown();  // 0x5c0990
};
}
namespace SP {
struct PaletteRef {
  cSPPalettePageUI_s005c_4500* p;
  bool a;
  bool b;
  bool c;
};
}
namespace SP {
struct PaletteVec {
  PaletteRef* mpBegin;
  PaletteRef* mpEnd;
  PaletteRef* mpCapacity;
  void erase(PaletteRef* first, PaletteRef* last);  // FUN_005c4330
  void DoPushBack(PaletteRef* where, PaletteRef* value);  // FUN_005c4390 (grow + insert)
};
}
namespace SP {
PaletteRef* __cdecl MoveRange(PaletteRef* last, PaletteRef* end, PaletteRef* first);  // FUN_005c3610
}
namespace SP {
struct ButtonVec {
  void push_back(void** value);  // FUN_005c42f0
};
}
namespace SP {
class cSPPaletteCategoryUI_s005c_4500 {
 public:
  char pad0[0x10];
  cSPUILayout_s005c_4500* mLayout;  // +0x10
  cSPUILayout_s005c_4500* mExpansionPackLayout;  // +0x14
  void* mWinCategory;  // +0x18
  void* mWinPageButtons;  // +0x1c
  void* mWinEPUIHolder;  // +0x20
  void* pad24;
  void* mWinPalettePage;  // +0x28
  void* pad2c;
  cSPEditorColorPicker_s005c_4500* mColorPicker1;  // +0x30
  cSPEditorColorPicker_s005c_4500* mColorPicker2;  // +0x34
  char pad38[0x68 - 0x38];
  void* mPreviewSwatch;  // +0x68
  cSPPaletteCategory_s005c_4500* mData;  // +0x6c
  cSPEditorPageControls_s005c_4500* mPageControls;  // +0x70
  ButtonVec mPackButtons;  // +0x74
  char pad78[0x88 - 0x78];
  PaletteVec mPalettes;  // +0x88
  char pad94[0x9c - 0x94];
  void* mSubCategoryUI;  // +0x9c
  int mUnkA0;  // +0xa0
  char pada4[0xac - 0xa4];
  uint32_t mCurrentPackId;  // +0xac
  int mExpansionPacksPerPage;  // +0xb0
  uint32_t mMsgIds;  // +0xb4
  uint32_t mMsgCount;  // +0xb8
  uint32_t mMsgPriority;  // +0xbc
  uint32_t mMsgC0;  // +0xc0
  uint32_t mMsgC4;  // +0xc4
  char padc8[0xe8 - 0xc8];
  void** mPaintLikeBegin;  // +0xe8
  void** mPaintLikeEnd;  // +0xec

  int GetPageCount();  // 0x5c2aa0
  bool IsPackVisible(int index);  // 0x5c2bc0
  void SetButtonPositions();  // 0x5c2660
  void SetWindowPositions();  // 0x5c3000
  void ShowPage(uint32_t paintId);  // 0x5c3cb0

  void PopulateExpansionPackPane(cSPPaletteCategory_s005c_4500* unused);  // 0x005c4500 (SP::cSPPaletteCategoryUI::PopulateExpansionPackPane)
  void ClearPalettes();
  void Shutdown();  // 0x005c4e40 (SP::cSPPaletteCategoryUI::Shutdown)
  bool SelectPalette(int index);
  void SetCategory(cSPPaletteCategory_s005c_4500* cat, int a2);
};
}
namespace SP {
struct PackMgr {
  PackVec* GetPacks();  // FUN_00572590
};
}
namespace SP {
PackMgr* __cdecl GetPackManager();  // FUN_0067dea0
}
namespace SP {
static inline void AssignLayout(cSPUILayout_s005c_4500** field, cSPUILayout_s005c_4500* nv) {
  cSPUILayout_s005c_4500* old = *field;
  if (nv != old) {
    if (nv) vc0(nv, 4);
    *field = nv;
    if (old) vc0(old, 8);
  }
}
}
namespace SP {
static void AddPackButton(cSPPaletteCategoryUI_s005c_4500* ui, void* container, PackInfo_s005c_4500* p) {
  void* btn = 0;
  {
    cSPUILayout_s005c_4500 lay;
    uint32_t key[3] = {p->layoutInstance, 0x510a95b, 0x40464100};
    lay.Init(key, 0, 0x5b598fa);
    void* w = lay.FindWindowByID(0x5dffa47, 1);
    if (w) {
      vc0(w, 0);
      btn = w;
    }
  }
  if (vc0(btn, 0x10)) {
    void* parent = (void*)vc0(btn, 0x10);
    vc1(parent, 0xdc, (int)btn);
  }
  vc1(container, 0xd8, (int)btn);
  void* a = btn ? (void*)vc1(btn, 0x0c, 0x8ed27e7a) : 0;
  void* b = (void*)vc0(btn, 0xa8);
  void* c = b ? (void*)vc1(b, 0x0c, 0x53eb526) : 0;
  if (a && c) {
    vc1(btn, 0x54, p->id);
    vc1((void*)vc0(a, 0x10), 0x104, (int)ui + 4);
    TipString str;
    str.append(p->name.GetText());
    cSPUITooltipWinProc_s005c_4500* tip = 0;
    void* mem = TooltipAlloc(0x68, 4, "UI/Tooltip", TooltipHeap());
    if (mem) {
      Vec2 off;
      off.x = 0.0f;
      off.y = g_TooltipOffsetY;
      tip = new (mem) cSPUITooltipWinProc_s005c_4500(L"Tooltips", 0x3754e6c, str.mpBegin, &off, 1, g_TooltipFlag, 0);
      if (tip) vc0(tip, 0);
    }
    vc1((void*)vc0(a, 0x10), 0x104, (int)tip);
    if (*(int*)p->iconKey) {
      ImageRef img;
      img.mpObject = 0;
      if (SPUIHelpers::CreateImageFromResource(p->iconKey, img.AsPPType(), 0, -1, -1))
        ((cSPUIStdDrawable*)c)->SetImageIcon(0, img.mpObject);
      if (img.mpObject) vc0(img.mpObject, 4);
    }
    if (*(int*)p->iconKey2) {
      ImageRef img;
      img.mpObject = 0;
      if (SPUIHelpers::CreateImageFromResource(p->iconKey2, img.AsPPType(), 0, -1, -1))
        vc2((char*)c + 0xc, 0x14, 0, (int)img.mpObject);
      if (img.mpObject) vc0(img.mpObject, 4);
    }
    vc0(btn, 0);
    void* ref = btn;
    ui->mPackButtons.push_back(&ref);
    if (ref) vc0(ref, 4);
    if (tip) vc0(tip, 4);
  }
  vc0(btn, 4);
}
}
    void* operator new(unsigned int, char*, int, int, int, int); // 0x00f473a0
    void operator delete(void*); // 0x00f47380
// ---- items of slice s005c4500 end

// ---- items of slice s005c53c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void EAFreeArray(void* p);  // operator delete[] (0x00f47380), cdecl
namespace SP {
class cSPPaletteCategory_s005c_53c0;
}
namespace SP {
class cSPPalettePage_s005c_53c0;
}
namespace SP {
class cSPPaletteItem_s005c_53c0;
}
namespace SP {
struct Key {
  uint32_t mInstance;
  uint32_t mType;
  uint32_t mGroup;
};
}
namespace SP {
class cSPPaletteItem_s005c_53c0 {
 public:
  virtual void v0();
  virtual int AddRef();
  virtual int Release();
  char pad4[8];
  Key mItemKey;  // +0xc
  uint32_t mThumbKey_Inst;   // +0x18
  uint32_t mThumbKey_Type;   // +0x1c
  uint32_t mThumbKey_Group;  // +0x20
  char pad24[0x24];
  int mRegion;  // +0x48
  char pad4c[8];
  cSPPaletteItem_s005c_53c0();  // 0x005c66a0
  void Init(Key* key, int region, uint32_t thumbGroup);  // 0x005c6810
};
}
namespace SP {
class cSPPalettePage_s005c_53c0 {
 public:
  virtual void v0();
  virtual int AddRef();
  virtual int Release();
  char pad4[0x58];
  int m5c;       // +0x5c
  uint32_t m60;  // +0x60
  Key mCategoryKey;  // +0x64
  cSPPaletteItem_s005c_53c0** mItemsBegin;  // +0x70
  cSPPaletteItem_s005c_53c0** mItemsEnd;    // +0x74
  char pad78[0xc];
  cSPPalettePage_s005c_53c0();  // 0x005c7f50
  bool Init(Key* key, uint32_t a, uint32_t b, uint32_t c, uint32_t d);  // 0x005c8ad0
  cSPPaletteItem_s005c_53c0* GetItem(int i);                                        // 0x005c7f00
};
}
namespace SP {
class cSPPaletteCategory_s005c_53c0 {
 public:
  virtual void v0();
  virtual int AddRef();
  virtual int Release();
  char pad4[0x8];
  cSPPalettePage_s005c_53c0** mPagesBegin;  // +0xc
  cSPPalettePage_s005c_53c0** mPagesEnd;    // +0x10
  char pad14[0x20];
  cSPPaletteCategory_s005c_53c0** mSubBegin;  // +0x34
  cSPPaletteCategory_s005c_53c0** mSubEnd;    // +0x38
  char pad3c[0xc];
  uint32_t mRegionFilter;  // +0x48
  uint32_t mSortKey;       // +0x4c
  char pad50[4];
  uint32_t mNameLocal;  // +0x54
  uint32_t mNameSrc;    // +0x58
  char pad5c[0x18];
  int mId;  // +0x74
  char pad78[0x18];
  cSPPaletteCategory_s005c_53c0();                                       // 0x005c2020
  void Init(Key* key, uint32_t group);                        // 0x005c1e20
  void Shutdown();                                            // 0x005c2230
  cSPPaletteCategory_s005c_53c0* FindSubCategory(int id);                // 0x005c1d70
  bool HasSubCategory(cSPPaletteCategory_s005c_53c0* c);                 // 0x005c1d40
  void AddSubCategory(cSPPaletteCategory_s005c_53c0* c);                 // 0x005c22b0
  void AddPage(cSPPalettePage_s005c_53c0* p);                            // 0x005c2390
  cSPPalettePage_s005c_53c0* GetPage(int i);                             // 0x005c1ce0
};
}
namespace SP {
struct IWindow {
  virtual int AddRef();
  virtual int Release();
  virtual void s2();
  virtual void s3();
  virtual void s4();
  virtual void s5();
  virtual void s6();
  virtual void s7();
  virtual void s8();
  virtual void s9();
  virtual void s10();
  virtual void s11();
  virtual void s12();
  virtual void s13();
  virtual float* GetArea();
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
  virtual void s29();
  virtual void s30();
  virtual void SetFlag(int a, int b);
};
}
namespace SP {
struct IMessageServer {
  virtual void s0();
  virtual void s1();
  virtual void s2();
  virtual void s3();
  virtual void s4();
  virtual void s5();
  virtual void s6();
  virtual void s7();
  virtual void s8();
  virtual void AddHandler(void* handler, uint32_t id);
};
}
namespace SP {
struct cSPUILayout_s005c_53c0 {
  virtual void v0();
  virtual int AddRef();
  virtual int Release();
  char pad4[0x14];
  cSPUILayout_s005c_53c0();                                                       // 0x00810000
  bool Init(Key* key, int a, uint32_t b);                              // 0x008120d0
  void SetParentWin(IWindow* parent, int a, uint32_t b);               // 0x008121b0
  IWindow* FindWindowByID(uint32_t id, int a);                         // 0x008105b0
};
}
namespace SP {
struct cSPEditorPageControls_s005c_53c0 {
  virtual int AddRef();
  virtual int Release();
  char pad8[0x20];
  cSPEditorPageControls_s005c_53c0();                  // 0x005c0770
  void Init(IWindow* w, void* owner);       // 0x005c0840
  void SetFlag(int f);                      // 0x00ed0260
};
}
namespace SP {
struct cSPEditorColorPicker_s005c_53c0 {
  virtual void v0();
  virtual int AddRef();
  virtual int Release();
  char pad4[0x4c];
  cSPEditorColorPicker_s005c_53c0();                                                  // 0x005a5a50
  void Init(IWindow* w, uint32_t id, uint32_t nameKey, int z);             // 0x005a5ec0
  void SetFlag(int f);                                                     // 0x005a4200
};
}
namespace SP {
struct RCSub {
  virtual int AddRef();
  virtual int Release();
};
}
namespace SP {
struct cSPEditorPaintLikeThis_s005c_53c0 {
  virtual void v0();
  virtual void Init(cSPPaletteItem_s005c_53c0* item, IWindow* w, int z, uint32_t arg);  // 0x005c1960 (SP::cSPEditorPaintLikeThis::Init)
  char pad8[4];
  RCSub sub;  // +0xc
  char pad10[0xd8];
  cSPEditorPaintLikeThis_s005c_53c0(uint32_t v);  // 0x005c0f40
};
}
namespace SP {
struct cSPSwatch_s005c_53c0 {
  virtual int AddRef();
  virtual int Release();
  virtual void s2();
  virtual void s3();
  virtual void s4();
  virtual void s5();
  virtual void s6();
  virtual void s7();
  virtual void s8();
  virtual void s9();
  virtual void s10();
  virtual void SetVisible(int v);
  char pad30[0x40];
  void Init(Key* key, IWindow* a, IWindow* b, int c, int d, int e, int f, int g);  // 0x005f5000
  void SetColorId(uint32_t id);                                                    // 0x005f2270
};
}
namespace SP {
struct cSPSwatchManager {
  cSPSwatch_s005c_53c0* CreateSwatch();  // 0x005f0ca0
};
}
namespace SP {
cSPSwatchManager* __stdcall GetSwatchManager(int a);  // 0x00401020
}
namespace SP {
struct cSPPaletteSubCategoryUI_s005c_53c0 {
  virtual int AddRef();
  virtual int Release();
  char pad8[0x8c];
  cSPPaletteSubCategoryUI_s005c_53c0();                                                 // 0x005c9c70
  void Init(IWindow* w, cSPPaletteCategory_s005c_53c0* cat, uint32_t arg);              // 0x005ca070
  void SetWindowFlag(int f);                                                 // 0x005c9810
};
}
namespace SP {
struct WinVec {
  IWindow** mBegin;
  IWindow** mEnd;
  IWindow** mCap;
  WinVec() : mBegin(0), mEnd(0), mCap(0) {}
  ~WinVec() {
    if (mBegin && ((int*)mBegin)[-1] != 0)
      EAFreeArray(mBegin);
  }
};
}
namespace SP {
template <class T>
struct ARC {
  T* mp;
  ARC& operator=(T* q) {
    T* old = mp;
    if (q != old) {
      if (q)
        q->AddRef();
      mp = q;
      if (old)
        old->Release();
    }
    return *this;
  }
};
}
namespace SP {
struct PackButton {
  void* mButton;
  bool mEnabled;
  char pad[3];
};
}
namespace SP {
struct PLTVec {
  cSPEditorPaintLikeThis_s005c_53c0** mBegin;
  cSPEditorPaintLikeThis_s005c_53c0** mEnd;
  cSPEditorPaintLikeThis_s005c_53c0** mCap;
  void InsertAux(cSPEditorPaintLikeThis_s005c_53c0** pos, cSPEditorPaintLikeThis_s005c_53c0** val);  // 0x005c90d0
};
}
namespace SP {
struct AutoHandler {
  IMessageServer* mServer;  // +0xb4
  void* mHandler;           // +0xb8
  const uint32_t* mIds;     // +0xbc
  int mCount;               // +0xc0
  int mPriority;            // +0xc4
};
}
namespace SP {
extern const uint32_t gPaletteMsgIds[2];  // 0x013f7f6c
}
namespace SP {
void SetWindowAreaToParent(IWindow* w);  // 0x00806bf0, cdecl
}
namespace SP {
extern uint32_t gSwatchDefault;           // 0x015150a4
}
namespace SP {
class cSPPaletteCategoryUI_s005c_53c0 {
 public:
  char pad0[0x10];
  ARC<cSPUILayout_s005c_53c0> mLayout;                // +0x10
  char pad14[4];
  ARC<IWindow> mWinCategory;               // +0x18
  ARC<IWindow> mWinPageButtons;            // +0x1c
  ARC<IWindow> mWinEPUIHolder;             // +0x20
  ARC<IWindow> mWinColorPickerHolder;      // +0x24
  ARC<IWindow> mWinPalettePage;            // +0x28
  ARC<IWindow> mWinFullPalettePage;        // +0x2c
  ARC<cSPEditorColorPicker_s005c_53c0> mColorPicker1; // +0x30
  ARC<cSPEditorColorPicker_s005c_53c0> mColorPicker2; // +0x34
  float mArea1[4];                         // +0x38
  float mArea2[4];                         // +0x48
  float mAreaUnion[4];                     // +0x58
  ARC<cSPSwatch_s005c_53c0> mPreviewSwatch;           // +0x68
  cSPPaletteCategory_s005c_53c0* mData;               // +0x6c
  ARC<cSPEditorPageControls_s005c_53c0> mPageControls;  // +0x70
  char pad74[0x14];
  PackButton* mPackBegin;                  // +0x88
  PackButton* mPackEnd;                    // +0x8c
  char pad90[0xc];
  ARC<cSPPaletteSubCategoryUI_s005c_53c0> mSubCategoryUI;  // +0x9c
  int mExpansionPackChunkIndex;            // +0xa0
  char pada4[0xc];  // +0xa4
  int mExpansionPacksPerPage;              // +0xb0
  AutoHandler mAutoMsgHandler;             // +0xb4
  char padc8[0x20];
  PLTVec mPaintLike;                       // +0xe8

  void Init(cSPPaletteCategory_s005c_53c0* data, IWindow* parent, uint32_t arg3);   // 0x005c53c0
  void SetData(cSPPaletteCategory_s005c_53c0* data, uint32_t arg3);                 // 0x005c51e0
  void GetWindowsWithMatchingID(IWindow* root, uint32_t id, WinVec* out);  // 0x005c4210
  void SetVisibleChunk(int chunk);                                       // 0x005c2590
  int FUN_005c2a30(void* btn);                                           // 0x005c2a30
  void OnChunkChanged(int oldIdx, int newIdx);                           // 0x005c3a50
  void SetChunkIndex(int idx) {
    int old = mExpansionPackChunkIndex;
    if (idx >= 0 && idx < (int)(mPackEnd - mPackBegin) && mPackBegin[idx].mEnabled) {
      mExpansionPackChunkIndex = idx;
      if (old != idx)
        OnChunkChanged(old, idx);
    }
  }
};
}
// ---- items of slice s005c53c0 end

// @ 0x005c2590
namespace SP {
void cSPPaletteCategoryUI_s005c_1d70::SetVisibleChunk(int chunkIndex)
{
  mExpansionPackChunkIndex = chunkIndex;
  int numChunks = (int)((mPackButtons.size() + mExpansionPacksPerPage - 1) / mExpansionPacksPerPage);
  IWindow_s005c_1d70* window = mLayout->FindWindowByID(0x5d1ad44, true);
  if (window)
    window->SetFlag(1, chunkIndex > 0);
  window = mLayout->FindWindowByID(0x5d1ad3f, true);
  if (window)
    window->SetFlag(1, chunkIndex + 1 < numChunks);
  for (unsigned int i = 0; i < mPackButtons.size(); i++) {
    if (i / mExpansionPacksPerPage != (unsigned int)mExpansionPackChunkIndex)
      mPackButtons[i]->ToWindow()->SetFlag(1, false);
    else
      mPackButtons[i]->ToWindow()->SetFlag(1, true);
  }
}
}  // namespace SP





// @ 0x005c2660
namespace SP {
void cSPPaletteCategoryUI_s005c_1d70::SetButtonPositions()
{
  if (mWinEPUIHolder && mPackButtons.mpBegin != mPackButtons.mpEnd) {
    IWindow_s005c_1d70* area = mLayout->FindWindowByID(0x5d1ad4a, true);
    float areaWidth = area->GetArea().Width();
    float areaHeight = area->GetArea().Height() - 8.0f;
    float buttonWidth = mPackButtons[0]->ToWindow()->GetRealArea().Width();
    float buttonHeight = mPackButtons[0]->ToWindow()->GetRealArea().Height();
    if (buttonHeight > areaHeight) {
      float aspect = buttonWidth / buttonHeight;
      buttonHeight = areaHeight;
      buttonWidth = aspect * areaHeight;
    }
    int count = (int)mPackButtons.size();
    mExpansionPacksPerPage = (int)((areaWidth - 3.0f) / (buttonWidth + 3.0f));
    if (mExpansionPacksPerPage < 4) {
      float aspect = buttonWidth / buttonHeight;
      mExpansionPacksPerPage = 4;
      buttonWidth = areaWidth * 0.25f;
      buttonHeight = buttonWidth / aspect;
    }
    if (count > mExpansionPacksPerPage)
      count = mExpansionPacksPerPage;
    float spacing = (areaWidth - (float)mExpansionPacksPerPage * buttonWidth) / (float)(mExpansionPacksPerPage + 1);
    float top = (area->GetArea().Height() - buttonHeight) * 0.5f;
    int numButtons = (int)mPackButtons.size();
    for (int i = 0; i < numButtons; i++) {
      IWindow_s005c_1d70* window = mPackButtons[i]->ToWindow();
      window->GetParent();
      window->GetFlags();
      window->GetRealArea();
      unsigned int column = (unsigned int)i % (unsigned int)count;
      EA::RectT_s005c_1d70 r;
      r.left = (float)(int)(column + 1) * spacing + (float)(int)column * buttonWidth;
      r.top = top;
      r.right = r.left + buttonWidth;
      r.bottom = top + buttonHeight;
      window->SetArea(r);
    }
  }
}
}  // namespace SP





// @ 0x005c28b0
namespace SP {
void cSPPaletteCategoryUI_s005c_1d70::Update(int deltaTime)
{
  if (mColorPicker1)
    mColorPicker1->Update(deltaTime);
  if (mColorPicker2)
    mColorPicker2->Update(deltaTime);
  if (mPageControls)
    mPageControls->Update(deltaTime);
  if (mSubCategoryUI)
    mSubCategoryUI->Update(deltaTime);
  int numPages = (int)mPageUIs.size();
  for (int i = 0; i < numPages; i++) {
    if (!mPageUIs[i].mDisabled)
      mPageUIs[i].mpPageUI->Update(deltaTime);
  }
}
}  // namespace SP





// @ 0x005c2940
namespace SP {
bool cSPPaletteCategoryUI_s005c_1d70::IsVisible()
{
  IWindow_s005c_1d70* window = mWinCategory;
  if (window)
    return window->GetFlags() & 1;
  return false;
}
}  // namespace SP





// @ 0x005c2960
namespace SP {
void cSPPaletteCategoryUI_s005c_1d70::SetVisibility(bool visible)
{
  IWindow_s005c_1d70* window = mWinCategory;
  if (window)
    window->SetFlag(1, visible);
  cSPSwatch_s005c_1d70* swatch = mPreviewSwatch;
  if (swatch)
    swatch->SetVisible(visible);
  IWindow_s005c_1d70* holder = mWinEPUIHolder;
  if (holder)
    holder->SetFlag(1, visible);
}
}  // namespace SP





// @ 0x005c29a0
namespace SP {
void cSPPaletteCategoryUI_s005c_1d70::SetPageVisible(int index, bool visible)
{
  mPageUIs[index].mVisible = visible;
}
}  // namespace SP





// @ 0x005c29c0
namespace SP {
bool cSPPaletteCategoryUI_s005c_1d70::IsPageVisible(int index)
{
  return mPageUIs[index].mVisible;
}
}  // namespace SP





// @ 0x005c29e0
namespace SP {
int cSPPaletteCategoryUI_s005c_1d70::GetPageIndexForPackID(uint32_t packID)
{
  int numPages = (int)mData->GetNumPages();
  for (int i = 0; i < numPages; i++) {
    if (mData->GetPage(i)->mPackID == packID)
      return i;
  }
  return -1;
}
}  // namespace SP





// @ 0x005c2a30
namespace SP {
int cSPPaletteCategoryUI_s005c_1d70::GetChunkIndexForPackID(uint32_t packID)
{
  int index = 0;
  int i = 0;
  eastl::sp_vector<PackInfo*>& packs = PackageManager()->GetPacks();
  int numPacks = (int)packs.size();
  for (; i < numPacks; i++) {
    if (packID == packs[i]->mPackID)
      return index;
    if (mData->CountPagesInCategory(packs[i]->mPackID) > 0)
      index++;
  }
  return -1;
}
}  // namespace SP





// @ 0x005c2aa0
int SP::cSPPaletteCategoryUI::GetNumPages()
{
  int numPacks = (int)PackageManager()->GetPacks().size();
  if (numPacks < 1)
    return numPacks;
  int numUnique = numPacks;
  for (int i = 0; i < numPacks; i++) {
    PackDescription* a = PackageManager()->GetPackDescription(i);
    for (int j = i + 1; j < numPacks; j++) {
      PackDescription* b = PackageManager()->GetPackDescription(j);
      if (SameDescription(a, b) && a->mKey.mInstance == b->mKey.mInstance && a->mKey.mType == b->mKey.mType &&
          a->mKey.mGroup == b->mKey.mGroup && wcscmp(a->mName.GetText(), b->mName.GetText()) == 0)
        numUnique--;
    }
  }
  return numUnique;
}





// @ 0x005c2bc0
namespace SP {
bool cSPPaletteCategoryUI_s005c_1d70::IsPackUnique(int index)
{
  if (index == 0)
    return true;
  if (index == (int)PackageManager()->GetPacks().size())
    return false;
  PackDescription* target = PackageManager()->GetPackDescription(index);
  for (int i = 0; i < index; i++) {
    PackDescription* p = PackageManager()->GetPackDescription(i);
    if (SameDescription(p, target) && KeysEqual(&p->mKey, &target->mKey) &&
        wcscmp(p->mName.GetText(), target->mName.GetText()) == 0)
      return false;
  }
  return true;
}
}  // namespace SP





// @ 0x005c2cd0
bool SP::cSPPaletteCategoryUI::IsPaintByNumber()
{
  if (mData.mpObject)
    return mData.mpObject->mPaintByNumber;
  return false;
}





// @ 0x005c2ce0
namespace SP {
uint32_t cSPPaletteCategoryUI_s005c_1d70::GetRegionFilterID()
{
  cSPPaletteCategoryUI_s005c_1d70* ui = this;
  while (ui->mData) {
    if (!ui->mSubCategoryUI || !ui->mSubCategoryUI->GetParentUI())
      return ui->mData->mRegionFilter;
    ui = ui->mSubCategoryUI->GetParentUI();
  }
  return 0;
}
}  // namespace SP




// @ 0x005c2d30
namespace SP {
tSPEditorPaint_s005c_2d30 cSPPaletteCategoryUI_s005c_2d30::GetSelectedPaint()
{
  if (GetSubCategoryUI() && GetSubCategoryUI()->GetParentUI())
    return GetSubCategoryUI()->GetParentUI()->GetSelectedPaint();
  tSPEditorPaint_s005c_2d30 paint;
  paint.mPaint = mSelectedItemID;
  paint.mColor1 = mSelectedColor1;
  paint.mColor2 = mSelectedColor2;
  return paint;
}
}  // namespace SP



// @ 0x005c2e00
namespace SP {
uint32_t cSPPaletteCategoryUI_s005c_2d30::GetSkinPaintIndex()
{
  cSPPaletteCategoryUI_s005c_2d30* ui = this;
  while (ui->mData) {
    if (!ui->mSubCategoryUI || !ui->mSubCategoryUI->GetParentUI())
      return ui->mData->mSkinPaintIndex;
    ui = ui->mSubCategoryUI->GetParentUI();
  }
  return 0;
}
}  // namespace SP



// @ 0x005c2e80
namespace SP {
bool cSPPaletteCategoryUI_s005c_2d30::IsColor1Default()
{
  if (mSubCategoryUI && mSubCategoryUI->GetParentUI())
    return mSubCategoryUI->GetParentUI()->IsColor1Default();
  return mIsColor1Default;
}
}  // namespace SP



// @ 0x005c2ec0
namespace SP {
void cSPPaletteCategoryUI_s005c_2d30::SetPackPaneVisible(bool visible)
{
  IWindow_s005c_2d30* window = mLayout->FindWindowByID(0x65badef, true);
  if (window)
    window->SetFlag(1, visible);
}
}  // namespace SP



// @ 0x005c2ef0
namespace SP {
PageUIEntry_s005c_2d30* uninitialized_copy_ptr(PageUIEntry_s005c_2d30* first, PageUIEntry_s005c_2d30* last, PageUIEntry_s005c_2d30* result)
{
  for (; first != last; ++first, ++result)
    ::new (result) PageUIEntry_s005c_2d30(*first);
  return result;
}
}  // namespace SP



// @ 0x005c2f40
namespace SP {
PaintLikeThisRef* copy(PaintLikeThisRef* first, PaintLikeThisRef* last, PaintLikeThisRef* result)
{
  for (; first != last; ++result, ++first)
    *result = *first;
  return result;
}
}  // namespace SP



// @ 0x005c2fa0
namespace SP {
PaintLikeThisRef* copy_backward(PaintLikeThisRef* first, PaintLikeThisRef* last, PaintLikeThisRef* resultEnd)
{
  while (last != first)
    *--resultEnd = *--last;
  return resultEnd;
}
}  // namespace SP



// @ 0x005c3000
namespace SP {
void cSPPaletteCategoryUI_s005c_2d30::SetWindowPositions()
{
  bool showPackButtons = (mPackButtons.mpEnd - mPackButtons.mpBegin) >= 1;
  bool hasColorPickers = mLayout->FindWindowByID(0x5d3f56b, true) != 0;
  bool showPageButtons = (int)mData->mPages.size() > 1 || mData->mHasMultiImageButton;
  if (sAppProperties->mpData->mbExpansionPacksOnly && GetNumUniquePacks() < 1)
    showPackButtons = false;
  float y = 5.0f;
  if (showPackButtons) {
    IWindow_s005c_2d30* epHolder = mWinEPUIHolder;
    if (epHolder)
      y = epHolder->GetArea().bottom + 5.0f;
  }
  if (hasColorPickers) {
    IWindow_s005c_2d30* pickerHolder = mWinColorPickerHolder;
    if (pickerHolder) {
      EA::RectT_s005c_2d30 area = pickerHolder->GetArea();
      float height = area.Height();
      area.top = y;
      area.bottom = height + y;
      mWinColorPickerHolder->SetLayoutArea(area);
      y = area.bottom + 5.0f;
    }
  }
  IWindow_s005c_2d30* palettePage = mWinPalettePage;
  if (palettePage) {
    EA::RectT_s005c_2d30 area = palettePage->GetArea();
    area.top = y;
    IWindow_s005c_2d30* pageButtons;
    if (showPageButtons && (pageButtons = mWinPageButtons) != 0) {
      area.bottom = pageButtons->GetArea().top - 5.0f;
    } else {
      IWindow_s005c_2d30* fullPage = mWinFullPalettePage;
      if (fullPage)
        area.bottom = fullPage->GetArea().Height() - 5.0f;
    }
    mWinPalettePage->SetLayoutArea(area);
  }
}
}  // namespace SP



// @ 0x005c31c0
namespace SP {
void cSPPaletteCategoryUI_s005c_2d30::UpdatePreviewSwatch()
{
  float alpha1 = 1.0f;
  float alpha2 = 1.0f;
  EA::AutoRefCount_s005c_2d30<cPropertyList_s005c_2d30> list;
  if (PropertyManager()->GetPropertyList(mSelectedItemID, kPaintPropertyGroup, list.AsOutParam()) && list) {
    GetPropFloat(list, 0x25e49bb, alpha1);
    GetPropFloat(list, 0x265fb07, alpha2);
  }
  if (mColorPicker1) {
    if (mIsColor1Default)
      mColorPicker1->SetDefault();
    else
      mColorPicker1->SetColor(mSelectedColor1);
    if (mColorPicker2) {
      mColorPicker1->SetAlphaEnabled(alpha1 > 0.0f);
      cSPEditorColorPicker_s005c_2d30* picker2 = mColorPicker2;
      if (mIsColor2Default)
        picker2->SetDefault();
      else
        picker2->SetColor(mSelectedColor2);
      mColorPicker2->SetAlphaEnabled(alpha2 > 0.0f);
      if (mColorPicker1->IsEnabled() && !mColorPicker2->IsEnabled()) {
        mColorPicker1->SetArea(mOriginalColorPickerAreaUnion);
      } else if (!mColorPicker1->IsEnabled() && mColorPicker2->IsEnabled()) {
        mColorPicker2->SetArea(mOriginalColorPickerAreaUnion);
      } else {
        mColorPicker1->SetArea(mOriginalColorPickerArea1);
        mColorPicker2->SetArea(mOriginalColorPickerArea2);
      }
    }
  }
  if (mPreviewSwatch && mPreviewSwatch->mpMaterial) {
    cSwatchMaterial* material = mPreviewSwatch->mpMaterial;
    tSPEditorPaint_s005c_2d30 paint;
    paint.mPaint = mSelectedItemID;
    paint.mColor1 = mSelectedColor1;
    paint.mColor2 = mSelectedColor2;
    material->SetColor(kSwatchColor);
    material->SetAlpha(1.0f);
    material->mLayer = 7;
    SP::EditorUtils::CreateAndSetPaintMaterial(paint, AddBoundingBox(material, -1)->GetModel());
  }
}
}  // namespace SP



// @ 0x005c34e0
namespace SP {
void cSPPaletteCategoryUI_s005c_2d30::SetSelectedPaint(const tSPEditorPaint_s005c_2d30& paint)
{
  if (paint.mPaint)
    mSelectedItemID = paint.mPaint;
  if (paint.mColor1 != kDefaultPaintColor) {
    mSelectedColor1 = paint.mColor1;
    if (mColorPicker1)
      mColorPicker1->SetColor(paint.mColor1);
  }
  if (paint.mColor2 != kDefaultPaintColor) {
    mSelectedColor2 = paint.mColor2;
    if (mColorPicker2)
      mColorPicker2->SetColor(paint.mColor1);  // sic: retail passes color 1
  }
  UpdatePreviewSwatch();
}
}  // namespace SP



// @ 0x005c35c0
namespace SP {
PageUIEntryAssign& PageUIEntryAssign::operator=(const PageUIEntryAssign& x)
{
  mpPageUI = x.mpPageUI;
  mVisible = x.mVisible;
  mShown = x.mShown;
  mDisabled = x.mDisabled;
  return *this;
}
}  // namespace SP



// @ 0x005c3610
namespace SP {
PageUIEntry_s005c_2d30* copy(PageUIEntry_s005c_2d30* first, PageUIEntry_s005c_2d30* last, PageUIEntry_s005c_2d30* result)
{
  for (; first != last; ++result, ++first)
    *result = *first;
  return result;
}
}  // namespace SP



// @ 0x005c3680
namespace SP {
PageUIEntry_s005c_2d30* copy_backward(PageUIEntry_s005c_2d30* first, PageUIEntry_s005c_2d30* last, PageUIEntry_s005c_2d30* resultEnd)
{
  while (last != first)
    *--resultEnd = *--last;
  return resultEnd;
}
}  // namespace SP



// @ 0x005c36f0
namespace SP {
bool cSPPaletteCategoryUI_s005c_2d30::HandleMessage(uint32_t messageID, void* message)
{
  if (message) {
  switch (messageID) {
    case 0xb2e18705: {
      cItemSelectedMessage* msg = (cItemSelectedMessage*)message;
      cItemSelectedMessage::ISource* source = msg->mpSource;
      cSPPaletteItem_s005c_2d30* item = source ? source->Cast(0x72d44e3a) : 0;
      int numPages = (int)mData->mPages.size();
      for (int i = 0; i < numPages; i++) {
        cSPPalettePage_s005c_2d30* page = GetPaletteCategoryData()->GetPage(i);
        int numItems = (int)page->mItems.size();
        for (int j = 0; j < numItems; j++) {
          if (page->GetItem(j) == item) {
            mSelectedItemID = item->mItemID;
            EA::AutoRefCount_s005c_2d30<cPropertyList_s005c_2d30> list;
            if (PropertyManager()->GetPropertyList(mSelectedItemID, kPaintPropertyGroup, list.AsOutParam())) {
              if (item->mItemType == 0xbd110a25) {
                cSPColorRGB color1, color2;
                GetPropertyAsColorRGB(list, 0x921a7b98, &color1);
                GetPropertyAsColorRGB(list, 0x921a7b99, &color2);
                if (mColorPicker1)
                  mColorPicker1->SetPaletteColor(color1);
                if (mColorPicker2)
                  mColorPicker2->SetPaletteColor(color2);
                if (mIsColor1Default)
                  mSelectedColor1 = color1;
                if (mIsColor2Default)
                  mSelectedColor2 = color2;
              } else if (item->mItemType == 0xdee3d8a8) {
                int count = 0;
                cSPColorRGB* colors;
                GetPropertyColors(list, 0xb0e066a8, &count, &colors);
                cSPColorRGB color;
                for (int k = 0; k < count; k++) {
                  if (colors[k] != kWhiteColor) {
                    color = colors[k];
                    break;
                  }
                }
                if (mColorPicker1)
                  mColorPicker1->SetPaletteColor(color);
                if (mIsColor1Default)
                  mSelectedColor1 = color;
              }
            }
            UpdatePreviewSwatch();
            return false;
          }
        }
      }
      break;
    }
    case 0x90e08f60: {
      cColorPickerMessage* msg = (cColorPickerMessage*)message;
      bool isDefault = msg->mIsDefault != 0;
      if (msg->mpSource) {
        cSPEditorColorPicker_s005c_2d30* picker = (cSPEditorColorPicker_s005c_2d30*)((char*)msg->mpSource - 8);
        if (picker == mColorPicker1) {
          mIsColor1Default = isDefault != 0;
          mSelectedColor1 = ColorFromID(msg->mColorID);
        } else if (picker == mColorPicker2) {
          mIsColor2Default = isDefault != 0;
          mSelectedColor2 = ColorFromID(msg->mColorID);
        } else {
          break;
        }
        UpdatePreviewSwatch();
      }
      break;
    }
  }
  }
  return false;
}
}  // namespace SP



// @ 0x005c3a50
namespace SP {
void cSPPaletteCategoryUI_s005c_2d30::OnPageChanged(int oldIndex, int newIndex)
{
  EA::Audio::IAudioSystem* audio = EA::Audio::GetSystemAT();
  uint32_t state = audio ? audio->GetState() : 0;
  audio = EA::Audio::GetSystemAT();
  if (audio) {
    audio->Begin(0x3475365);
    audio->SetParam(0x3475381, 0xeaf824a0);
    audio->SetParam(0x3475385, state);
    audio->End();
  }
  mPageUIs[oldIndex].mpPageUI.mpObject->SetVisible(false);
  mPageUIs[oldIndex].mShown = false;
  if (mPageUIs[newIndex].mVisible) {
    mPageUIs[newIndex].mpPageUI.mpObject->SetVisible(true);
    mPageUIs[newIndex].mShown = true;
  }
  mCurrentPageIndex = newIndex;
  if (GetPageUI(newIndex)->GetPackID() != mCurrentPackID)
    SetSelectedPack(GetPageUI(mCurrentPageIndex)->GetPackID());
  EA::Messaging::MessageBasicRC5 msg(0x8292e7f);
  msg.mData[0].mUint32 = (uint32_t)this;
  msg.mData[1].mUint32 = newIndex;
  msg.mData[2].mUint32 = oldIndex;
  MessageServer()->MessageSend(msg.mID, &msg, 0);
}
}  // namespace SP



// @ 0x005c3bd0
namespace SP {
bool cSPPaletteCategoryUI_s005c_2d30::SetPageIndex(int index)
{
  int oldIndex = mCurrentPageIndex;
  if (index >= 0 && index < (int)mPageUIs.size() && mPageUIs[index].mVisible) {
    mCurrentPageIndex = index;
    if (oldIndex != index) {
      OnPageChanged(oldIndex, index);
      return true;
    }
  }
  return false;
}
}  // namespace SP



// @ 0x005c3c20
namespace SP {
bool cSPPaletteCategoryUI_s005c_2d30::CyclePage(int direction)
{
  int oldIndex = mCurrentPageIndex;
  int numPages = (int)mPageUIs.size();
  if (numPages >= 2) {
    do {
      mCurrentPageIndex = (numPages + direction + mCurrentPageIndex) % numPages;
      PageUIEntry_s005c_2d30& entry = mPageUIs[mCurrentPageIndex];
      cSPPalettePageUI_s005c_2d30* pageUI = entry.mpPageUI.mpObject;
      if (entry.mVisible && (!mFilterSetId || pageUI->GetPackID() == mFilterSetId))
        break;
    } while (oldIndex != mCurrentPageIndex);
    if (oldIndex != mCurrentPageIndex) {
      OnPageChanged(oldIndex, mCurrentPageIndex);
      return true;
    }
  }
  return false;
}
}  // namespace SP


// @ 0x005c4500
namespace SP {
void cSPPaletteCategoryUI_s005c_4500::PopulateExpansionPackPane(cSPPaletteCategory_s005c_4500*)
{
  PackVec* packs = GetPackManager()->GetPacks();
  int n = (int)(packs->mpEnd - packs->mpBegin);
  bool noPacks = false;
  if (g_AppProps->mpProps->mFlag118 != 0 && GetPageCount() < 1) noPacks = true;
  bool any = false;
  for (int i = 0; i < n; i++) {
    PackInfo_s005c_4500* p = packs->mpBegin[i];
    if (IsPackVisible(i) && p->id != 1 && mData->CountFor(p->id) > 0) {
      any = !noPacks;
      break;
    }
  }
  if (!any) {
    if (mWinEPUIHolder) {
      if (mWinPalettePage) {
        Rect4 r = *(Rect4*)vc0(mWinPalettePage, 0x38);
        r.y1 = g_PackPaneGap;
        vc1(mWinPalettePage, 0x6c, (int)&r);
      }
      vc2(mWinEPUIHolder, 0x7c, 1, 0);
    }
    ResetRef((void**)&mExpansionPackLayout, 8);
    return;
  }
  if (!mWinEPUIHolder) return;
  if (mWinPalettePage) {
    Rect4 r = *(Rect4*)vc0(mWinPalettePage, 0x38);
    Rect4* hr = (Rect4*)vc0(mWinEPUIHolder, 0x38);
    r.y1 = hr->y2 + g_PackPaneGap;
    vc1(mWinPalettePage, 0x6c, (int)&r);
  }
  vc2(mWinEPUIHolder, 0x7c, 1, 1);
  AssignLayout(&mExpansionPackLayout, new ("Editor", 0, 0, 0, 0) cSPUILayout_s005c_4500());
  uint32_t layoutKey[3] = {0x9ec201c3, 0x510a95b, 0x40464100};
  if (mExpansionPackLayout->Init(layoutKey, 1, 0x5b598fa)) {
    mExpansionPackLayout->SetParentWin(mWinEPUIHolder, 1, 0x5b598fa);
    void* w = mExpansionPackLayout->FindWindowByID(0x5d29758, 1);
    if (w) SPUIHelpers::SetWindowAreaToParent(w);
  }
  void* container = mExpansionPackLayout->FindWindowByID(0x5d1ad4a, 1);
  if (!container) return;
  bool filtered = g_AppProps->mpProps->mFlag118 != 0;
  for (int i = 0; i < n; i++) {
    PackInfo_s005c_4500* p = packs->mpBegin[i];
    if (filtered && !IsPackVisible(i)) continue;
    if (mData->CountFor(p->id) > 0) AddPackButton(this, container, p);
  }
  SetButtonPositions();
  if (n <= mExpansionPacksPerPage) return;
  void* w1 = mExpansionPackLayout->FindWindowByID(0x5d1ad44, 1);
  void* w2 = mExpansionPackLayout->FindWindowByID(0x5d1ad3f, 1);
  if (w1) vc1(w1, 0x104, (int)this + 4);
  if (w2) vc1(w2, 0x104, (int)this + 4);
}
}  // namespace SP


// @ 0x005c4df0
namespace SP {
void cSPPaletteCategoryUI_s005c_4500::ClearPalettes()
{
  PaletteVec& v = mPalettes;
  int count = (int)(v.mpEnd - v.mpBegin);
  for (int i = 0; i < count; i++)
    v.mpBegin[i].p->Detach();
  v.erase(v.mpBegin, v.mpEnd);
  mUnkA0 = 0;
}
}  // namespace SP


// @ 0x005c4e40
namespace SP {
void cSPPaletteCategoryUI_s005c_4500::Shutdown()
{
  if (mMsgIds) {
    uint32_t ids = mMsgIds;
    mMsgIds = 0;
    EA::Messaging::RemoveHandler(ids, mMsgCount, mMsgPriority, mMsgC0, mMsgC4);
  }
  if (mColorPicker1) {
    mColorPicker1->Clear();
    cSPEditorColorPicker_s005c_4500* p = mColorPicker1;
    if (p) {
      mColorPicker1 = 0;
      vc0(p, 8);
    }
  }
  if (mColorPicker2) {
    mColorPicker2->Clear();
    cSPEditorColorPicker_s005c_4500* p = mColorPicker2;
    if (p) {
      mColorPicker2 = 0;
      vc0(p, 8);
    }
  }
  if (mPreviewSwatch) {
    SwatchOwner(mPreviewSwatch)->Release();
    ResetRef(&mPreviewSwatch, 4);
  }
  if (mWinPageButtons) ResetRef(&mWinPageButtons, 4);
  if (mPageControls) {
    mPageControls->Shutdown();
    ResetRef((void**)&mPageControls, 4);
  }
  int nw = (int)(mPaintLikeEnd - mPaintLikeBegin);
  for (int i = 0; i < nw; i++)
    vc0(mPaintLikeBegin[i], 8);
  ((PaintLikeVec*)&mPaintLikeBegin)->Erase(mPaintLikeBegin, mPaintLikeEnd);
  if (mSubCategoryUI) {
    ((cSPSubCategoryUI*)mSubCategoryUI)->Shutdown();
    ResetRef(&mSubCategoryUI, 4);
  }
  if (mLayout) {
    void* w1 = mLayout->FindWindowByID(0x5d1ad44, 1);
    void* w2 = mLayout->FindWindowByID(0x5d1ad3f, 1);
    if (w1) vc1(w1, 0x108, (int)this + 4);
    if (w2) vc1(w2, 0x108, (int)this + 4);
  }
  int np = (int)(mPalettes.mpEnd - mPalettes.mpBegin);
  for (int i = 0; i < np; i++)
    mPalettes.mpBegin[i].p->Shutdown();
  {
    PaletteRef* first = mPalettes.mpBegin;
    PaletteRef* last = mPalettes.mpEnd;
    PaletteRef* dest = MoveRange(last, last, first);
    for (PaletteRef* q = dest; q < mPalettes.mpEnd; q++)
      if (q->p) vc0(q->p, 4);
    mPalettes.mpEnd -= (last - first);
  }
  mUnkA0 = 0;
  if (mExpansionPackLayout) {
    mExpansionPackLayout->Shutdown(1);
    ResetRef((void**)&mExpansionPackLayout, 8);
  }
  if (mLayout) {
    mLayout->Shutdown(1);
    ResetRef((void**)&mLayout, 8);
  }
}
}  // namespace SP


// @ 0x005c50b0
namespace SP {
bool cSPPaletteCategoryUI_s005c_4500::SelectPalette(int index)
{
  PaletteVec& v = mPalettes;
  if ((int)(v.mpEnd - v.mpBegin) == 0) return false;
  if (index == -1) {
    int n = (int)(mData->mPagesEnd - mData->mPagesBegin);
    for (int i = 0; i < n; i++) {
      if (mData->GetPage(i)->mPaintId == mCurrentPackId) {
        index = i;
        break;
      }
    }
  }
  cSPPalettePageUI_s005c_4500* page = v.mpBegin[index].p;
  if (page) vc0(page, 0);
  PaletteRef e;
  e.p = page;
  e.a = true;
  e.b = true;
  e.c = true;
  if (v.mpEnd < v.mpCapacity) {
    PaletteRef* dst = v.mpEnd++;
    if (dst) {
      dst->p = page;
      if (page) vc0(page, 0);
      dst->a = true;
      dst->b = true;
      dst->c = true;
    }
  } else {
    v.DoPushBack(v.mpEnd, &e);
  }
  if (page) vc0(page, 4);
  if (mWinPageButtons && (int)(v.mpEnd - v.mpBegin) > 1 && !(vc0(mWinPageButtons, 0x28) & 1)) {
    vc2(mWinPageButtons, 0x7c, 1, 1);
    SetWindowPositions();
  }
  return true;
}
}  // namespace SP


// @ 0x005c51e0
namespace SP {
void cSPPaletteCategoryUI_s005c_4500::SetCategory(cSPPaletteCategory_s005c_4500* cat, int a2)
{
  ClearPalettes();
  cSPPaletteCategory_s005c_4500* old = mData;
  if (cat != old) {
    if (cat) vc0(cat, 4);
    mData = cat;
    if (old) vc0(old, 8);
  }
  PopulateExpansionPackPane(cat);
  SetWindowPositions();
  int n = (int)(mData->mPagesEnd - mData->mPagesBegin);
  for (int i = 0; i < n; i++) {
    cSPPalettePage_s005c_4500* page = mData->GetPage(i);
    cSPPalettePageUI_s005c_4500* ui = new ("Editor", 0, 0, 0, 0) cSPPalettePageUI_s005c_4500();
    if (ui) vc0(ui, 0);
    void** winp = mWinPalettePage ? &mWinPalettePage : &mWinCategory;
    ui->Init(page, *winp, a2, i, mData->mIsSubCategory);
    cSPPalettePageUI_s005c_4500* tmp = ui;
    if (tmp) vc0(tmp, 0);
    PaletteRef e;
    e.p = ui;
    e.a = true;
    e.b = true;
    e.c = false;
    if (mPalettes.mpEnd < mPalettes.mpCapacity) {
      PaletteRef* dst = mPalettes.mpEnd++;
      if (dst) {
        dst->p = ui;
        if (ui) vc0(ui, 0);
        dst->a = true;
        dst->b = true;
        dst->c = false;
      }
    } else {
      mPalettes.DoPushBack(mPalettes.mpEnd, &e);
    }
    if (tmp) vc0(tmp, 4);
    if (i == 0) {
      mPalettes.mpBegin->a = true;
      if (mPalettes.mpBegin->a) {
        mPalettes.mpBegin->p->SetSwatchFlag(1);
        mPalettes.mpBegin->b = true;
      }
    }
    ShowPage(page->mPaintId);
    if (ui) vc0(ui, 4);
  }
  if (mWinPageButtons) {
    int cnt = (int)(mData->mPagesEnd - mData->mPagesBegin);
    vc2(mWinPageButtons, 0x7c, 1, cnt > 1);
  }
}
}  // namespace SP

// @ 0x005c53c0
namespace SP {
void cSPPaletteCategoryUI_s005c_53c0::Init(cSPPaletteCategory_s005c_53c0* data, IWindow* parent, uint32_t arg3)
{
  mLayout = new ("Editor", 0, 0, 0, 0) cSPUILayout_s005c_53c0();
  Key layoutKey;
  layoutKey.mInstance = data->mRegionFilter;
  layoutKey.mType = 0x510a95b;
  layoutKey.mGroup = 0x40464100;
  if (mLayout.mp->Init(&layoutKey, 1, 0x5b598fa)) {
    mLayout.mp->SetParentWin(parent, 1, 0x5b598fa);
    IWindow* root = mLayout.mp->FindWindowByID(0xffffffff, 1);
    if (root)
      SetWindowAreaToParent(root);
    mWinCategory = mLayout.mp->FindWindowByID(0x52df67af, 1);
    mWinPageButtons = mLayout.mp->FindWindowByID(0x92df6fd8, 1);
    mWinEPUIHolder = mLayout.mp->FindWindowByID(0x5d122c0, 1);
    mWinPalettePage = mLayout.mp->FindWindowByID(0x5d1754b, 1);
    mWinFullPalettePage = mLayout.mp->FindWindowByID(0x5d17546, 1);
    mWinColorPickerHolder = mLayout.mp->FindWindowByID(0x5d3f56b, 1);
  }
  SetData(data, arg3);
  if (mLayout.mp) {
    IWindow* pageButtons = mLayout.mp->FindWindowByID(0x92df6fd8, 1);
    if (pageButtons) {
      mPageControls = new ("Editor", 0, 0, 0, 0) cSPEditorPageControls_s005c_53c0();
      mPageControls.mp->Init(pageButtons, this);
      mPageControls.mp->SetFlag(1);
    }
    IWindow* picker1 = mLayout.mp->FindWindowByID(0x3304221b, 1);
    if (picker1) {
      uint32_t nameKey = mData->mNameLocal;
      if (nameKey == 0xffffffff)
        nameKey = mData->mNameSrc;
      mColorPicker1 = new ("Editor", 0, 0, 0, 0) cSPEditorColorPicker_s005c_53c0();
      mColorPicker1.mp->Init(picker1, 0x2ab48add, nameKey, 0);
      mColorPicker1.mp->SetFlag(1);
      float* a = picker1->GetArea();
      mArea1[0] = a[0];
      mArea1[1] = a[1];
      mArea1[2] = a[2];
      mArea1[3] = a[3];
      mArea2[0] = mArea1[0];
      mArea2[1] = mArea1[1];
      mArea2[2] = mArea1[2];
      mArea2[3] = mArea1[3];
    }
    IWindow* picker2 = mLayout.mp->FindWindowByID(0x3304221c, 1);
    if (picker2) {
      uint32_t nameKey = mData->mNameLocal;
      if (nameKey == 0xffffffff)
        nameKey = mData->mNameSrc;
      mColorPicker2 = new ("Editor", 0, 0, 0, 0) cSPEditorColorPicker_s005c_53c0();
      mColorPicker2.mp->Init(picker2, 0x2ab48add, nameKey, 0);
      mColorPicker2.mp->SetFlag(1);
      float* a = picker2->GetArea();
      mArea2[0] = a[0];
      mArea2[1] = a[1];
      mArea2[2] = a[2];
      mArea2[3] = a[3];
    }
    mAreaUnion[0] = mArea1[0];
    mAreaUnion[1] = mArea1[1];
    mAreaUnion[2] = mArea1[2];
    mAreaUnion[3] = mArea1[3];
    mAreaUnion[3] = mArea2[3];

    WinVec wins;
    GetWindowsWithMatchingID(mLayout.mp->FindWindowByID(0xffffffff, 1), 0x577e1ae, &wins);
    int nWins = (int)(wins.mEnd - wins.mBegin);
    for (int i = 0; i < nWins; i++) {
      IWindow* w = wins.mBegin[i];
      uint32_t v = 0xffffffff;
      if (((int)((char*)data->mPagesEnd - (char*)data->mPagesBegin) & ~3) > 0)
        v = data->GetPage(0)->m60;
      cSPEditorPaintLikeThis_s005c_53c0* plt = new ("Editor", 0, 0, 0, 0) cSPEditorPaintLikeThis_s005c_53c0(v);
      cSPEditorPaintLikeThis_s005c_53c0* tmp = plt;
      if (plt)
        plt->sub.AddRef();
      cSPPaletteItem_s005c_53c0* item = new ("Editor", 0, 0, 0, 0) cSPPaletteItem_s005c_53c0();
      if (item)
        item->AddRef();
      Key itemKey;
      itemKey.mInstance = 0x32f652ad;
      itemKey.mType = 0;
      itemKey.mGroup = 0x406a0200;
      item->Init(&itemKey, 0, 0);
      plt->Init(item, w, 0, arg3);
      if (mPaintLike.mEnd < mPaintLike.mCap) {
        cSPEditorPaintLikeThis_s005c_53c0** slot = mPaintLike.mEnd++;
        if (slot) {
          *slot = plt;
          plt->sub.AddRef();
        }
      } else {
        mPaintLike.InsertAux(mPaintLike.mEnd, &tmp);
      }
      if (item)
        item->Release();
      if (tmp)
        tmp->sub.Release();
    }

    IWindow* swatchWin = mLayout.mp->FindWindowByID(0x530c27bc, 1);
    if (swatchWin) {
      mPreviewSwatch = GetSwatchManager(0)->CreateSwatch();
      if (mPreviewSwatch.mp) {
        Key swatchKey;
        swatchKey.mInstance = 0xef4519ff;
        swatchKey.mType = 0xb1b104;
        swatchKey.mGroup = gSwatchDefault;
        mPreviewSwatch.mp->Init(&swatchKey, swatchWin, swatchWin, 0, 0, 1, 0, -1);
        mPreviewSwatch.mp->SetColorId(0x2d03ced2);
        mPreviewSwatch.mp->SetVisible(0);
      }
    }

    EA::Messaging::Server* server = MessageServer();
    mAutoMsgHandler.mServer = (IMessageServer*)server;
    mAutoMsgHandler.mHandler = this;
    mAutoMsgHandler.mIds = gPaletteMsgIds;
    mAutoMsgHandler.mCount = 2;
    mAutoMsgHandler.mPriority = 0;
    if (server) {
      for (int i = 0; i < 2; i++)
        server->AddHandler((EA::Messaging::IHandler*)this, gPaletteMsgIds[i]);
    }

    IWindow* subWin = mLayout.mp->FindWindowByID(0x1357f0c2, 1);
    if (subWin && (((char*)mData->mSubEnd - (char*)mData->mSubBegin) & ~3) != 0) {
      mSubCategoryUI = new ("Editor", 0, 0, 0, 0) cSPPaletteSubCategoryUI_s005c_53c0();
      mSubCategoryUI.mp->Init(subWin, mData, arg3);
      mSubCategoryUI.mp->SetWindowFlag(1);
    }
  }
  if ((mPackEnd - mPackBegin) != 0) {
    void* btn = mPackBegin[mExpansionPackChunkIndex].mButton;
    SetVisibleChunk(FUN_005c2a30(btn) / mExpansionPacksPerPage);
    SetChunkIndex(mExpansionPackChunkIndex);
  }
  if (mWinCategory.mp)
    mWinCategory.mp->SetFlag(1, 0);
  if (mPreviewSwatch.mp)
    mPreviewSwatch.mp->SetVisible(0);
  if (mWinEPUIHolder.mp)
    mWinEPUIHolder.mp->SetFlag(1, 0);
}
}  // namespace SP
