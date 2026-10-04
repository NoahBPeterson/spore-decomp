// SP::cSPPaletteCategoryUI (Spore editor paint palette category UI), part 2, plus the
// EASTL copy helpers instantiated for its vectors.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include <new>
#include <string.h>
#include "types.h"

extern "C" void EASTL_allocator_deallocate(void* p);
extern "C" void* EASTL_memmove(void* dst, const void* src, unsigned int n);  // 0x011e0744 (static memmove)

#define PV(n) virtual void pv##n();

extern "C" long __cdecl _InterlockedExchange(long volatile* target, long value);
#pragma intrinsic(_InterlockedExchange)

namespace EA {
template <typename T>
class AutoRefCount {
 public:
  T* mpObject;
  AutoRefCount() : mpObject(0) {}
  AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
  AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
  ~AutoRefCount() { if (mpObject) mpObject->Release(); }
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

template <typename T>
class RefCountVTemplate {
 public:
  RefCountVTemplate() : mRefCount(0) {}
  virtual ~RefCountVTemplate() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};

namespace COM {
class IUnknown32 {
 public:
  ~IUnknown32() {}
  virtual int AddRef();
  virtual int Release();
};
}

namespace ResourceMan {
struct Key {
  unsigned int mInstance, mType, mGroup;
  Key() {}
  Key(unsigned int i, unsigned int t, unsigned int g) : mInstance(i), mType(t), mGroup(g) {}
};
}

struct RectT {
  float left, top, right, bottom;
  RectT() {}
  RectT(const RectT& r) : left(r.left), top(r.top), right(r.right), bottom(r.bottom) {}
  float Width() const { return right - left; }
  float Height() const { return bottom - top; }
};

namespace UTFWin {
class IWindow {
 public:
  PV(0) PV(1) PV(2) PV(3)
  virtual IWindow* GetParent();                     // +0x10
  PV(5) PV(6) PV(7) PV(8) PV(9)
  virtual uint32_t GetFlags();                      // +0x28
  PV(11) PV(12)
  virtual const RectT& GetRealArea();               // +0x34
  virtual const RectT& GetArea();                   // +0x38
  PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23)
  virtual void SetArea(const RectT& area);          // +0x60
  PV(25) PV(26)
  virtual void SetLayoutArea(const RectT& area);   // +0x6c
  PV(28) PV(29) PV(30)
  virtual void SetFlag(int flag, bool value);       // +0x7c
};
}  // namespace UTFWin
}  // namespace EA

using EA::UTFWin::IWindow;

namespace eastl {
template <typename T>
struct copy_impl_do {
  static T* do_copy(T* first, T* last, T* result);  // copy_impl<0,random_access>::do_copy
};

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

template <typename T>
inline T* copy(T* first, T* last, T* result) {
  return copy_impl_do<T>::do_copy(first, last, result);
}

template <typename T>
inline void destruct(T* first, T* last) {
  for (; first < last; ++first)
    first->~T();
}

template <typename T>
class sp_ref_vector : public sp_vector<EA::AutoRefCount<T> > {
 public:
  typedef EA::AutoRefCount<T> value_type;
  ~sp_ref_vector();  // FUN_005c7f10 (out of line)
  value_type* erase(value_type* first, value_type* last);
  void clear() { erase(this->mpBegin, this->mpEnd); }
};

template <typename InputIterator, typename T>
inline InputIterator find(InputIterator first, InputIterator last, const T& value) {
  while ((first != last) && !(*first == value))
    ++first;
  return first;
}
}  // namespace eastl

struct Property {
  char pad[0x12];
  unsigned short mType;  // +0x12
  bool* GetBool();       // 0x0041e920
  uint32_t* GetUInt();   // 0x0041ea00
  float* GetFloat();     // 0x0041ea70
};

namespace SP {
class cString {
 public:
  cString();
  ~cString();
  const wchar_t* GetText();  // 0x006b55c0
  char pad[0x14];
};

class cPropertyList {
 public:
  virtual int AddRef();
  virtual int Release();
  PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
  virtual bool GetProperty(uint32_t id, Property*& result);  // +0x24
};
class IPropertyManager {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, cPropertyList*& result);  // +0x2c
};
IPropertyManager* PropertyManager();
bool GetPropertyAsKeyInstance(cPropertyList* list, uint32_t id, uint32_t* result);
bool GetPropertyAsKey(cPropertyList* list, uint32_t id, EA::ResourceMan::Key* result);
bool GetPropertyKeys(cPropertyList* list, uint32_t id, int* count, EA::ResourceMan::Key** keys);
bool GetPropertyAsText(cPropertyList* list, uint32_t id, cString* result);
extern uint32_t kDefaultPaletteGroup;  // 0x01514dd0

class cSPPalettePage {
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
  eastl::sp_vector<class cSPPaletteItem*> mItems;  // +0x70
  cSPPaletteItem* GetItem(int index);             // FUN_005c7f00
};

struct PackInfo {
  uint32_t mPackID;   // +0x0
  int mPriority;      // +0x4
};
struct PackDescription {
  uint32_t mData[6];           // +0x0
  EA::ResourceMan::Key mKey;   // +0x18
  cString mName;               // +0x24
};
class cPackageManager {
 public:
  PackInfo* GetPackInfo(uint32_t packID);               // FUN_007db5e0
  PackDescription* GetPackDescription(int index);       // FUN_007db620
  eastl::sp_vector<PackInfo*>& GetPacks();              // FUN_00572590
};
cPackageManager* PackageManager();  // FUN_0067dea0
bool KeysEqual(const EA::ResourceMan::Key* a, const EA::ResourceMan::Key* b);  // FUN_004eb930

class cSPPaletteCategory : public EA::RefCountVTemplate<int>, public EA::COM::IUnknown32 {
 public:
  eastl::sp_ref_vector<cSPPalettePage> mPages;                  // +0xc
  eastl::sp_vector<unsigned int> mPacks;                         // +0x20
  eastl::sp_ref_vector<cSPPaletteCategory> mSubCategories;       // +0x34
  unsigned int mLayoutInstanceID;                                // +0x48
  unsigned int mSequenceNumber;                                  // +0x4c
  bool mPaintByNumber;                                           // +0x50
  unsigned int mRegionFilter;                                    // +0x54
  unsigned int mSkinPaintIndex;                                  // +0x58
  cString mCategoryName;                                         // +0x5c
  bool mHasMultiImageButton;                                     // +0x70
  unsigned int mCategoryId;                                      // +0x74
  unsigned int mParentCategory;                                  // +0x78
  EA::ResourceMan::Key mButtonImageKey;                          // +0x7c
  EA::ResourceMan::Key* mpButtonImageKeys;                       // +0x88
  bool mIsSubCategory;                                           // +0x8c

  cSPPaletteCategory();
  ~cSPPaletteCategory();
  virtual int AddRef();
  virtual int Release();
  cSPPaletteCategory* FindSubCategory(uint32_t categoryID);
  bool Init(const EA::ResourceMan::Key& key, unsigned int layoutInstanceID);
  void Shutdown();
  void AddSubCategory(cSPPaletteCategory* category);
  void AddPage(cSPPalettePage* page);
  unsigned int GetNumPages() { return mPages.size(); }
  cSPPalettePage* GetPage(int index);           // FUN_005c1ce0
  int CountPagesInCategory(uint32_t packID);    // FUN_005c1d10
};

// RGB color; the user copy ctor copies per float (movss), assignment stays implicit (dwords).
struct cSPColorRGB {
  float r, g, b;
  cSPColorRGB() {}
  cSPColorRGB(const cSPColorRGB& c) : r(c.r), g(c.g), b(c.b) {}
  bool operator!=(const cSPColorRGB& c) const { return r != c.r || g != c.g || b != c.b; }
};
extern cSPColorRGB kDefaultPaintColor;  // 0x015150b0
extern cSPColorRGB kWhiteColor;         // 0x015ebbf8 (guessed)

struct tSPEditorPaint {
  unsigned int mPaint;   // +0x0
  cSPColorRGB mColor1;   // +0x4
  cSPColorRGB mColor2;   // +0x10
};

bool GetPropertyAsColorRGB(cPropertyList* list, uint32_t id, cSPColorRGB* result);                // 0x006a11b0
bool GetPropertyColors(cPropertyList* list, uint32_t id, int* count, cSPColorRGB** colors);      // 0x006a0a70
extern uint32_t kPaintPropertyGroup;  // 0x01515094

inline bool GetPropFloat(cPropertyList* list, uint32_t id, float& value) {
  Property* prop;
  if (list && list->GetProperty(id, prop) && prop->mType == 13) {
    value = *prop->GetFloat();
    return true;
  }
  return false;
}

class cSPPaletteItem {
 public:
  char pad[0xc];
  uint32_t mItemID;    // +0xc
  char pad10[0x24 - 0x10];
  uint32_t mItemType;  // +0x24
};

class cSPUILayout {
 public:
  IWindow* FindWindowByID(uint32_t id, bool recursive);
};

class cSPEditorColorPicker {
 public:
  bool IsEnabled();                         // FUN_005a41e0
  void SetAlphaEnabled(bool enabled);       // FUN_005a4200
  void SetArea(EA::RectT area);             // FUN_005a4800
  void SetPaletteColor(const cSPColorRGB& color);  // FUN_005a4920
  void SetColor(const cSPColorRGB& color);  // FUN_005a4e20
  void SetDefault();                        // FUN_005a4fb0
};

class cSPPalettePageUI {
 public:
  virtual int AddRef();
  virtual int Release();
  void SetVisible(bool visible);  // FUN_005c8bf0
  uint32_t GetPackID();           // FUN_005c8fc0
};

class cSPPaletteSubCategoryUI {
 public:
  class cSPPaletteCategoryUI* GetParentUI();  // FUN_005c9830
};

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
extern cSPColorRGB kSwatchColor;  // 0x01514eb8
struct cSwatchMaterialSlot;
cSwatchMaterialSlot* AddBoundingBox(cSwatchMaterial* material, int index);  // 0x0067cad0
class cSwatchMaterialSlot { public: void* GetModel(); /* FUN_006c10e0 */ };
namespace EditorUtils {
void CreateAndSetPaintMaterial(tSPEditorPaint paint, void* model);  // 0x004b8180
}

class cSPSwatch {
 public:
  char pad[0x118];
  cSwatchMaterial* mpMaterial;  // +0x118
};

class cAppPropertiesData { public: char pad[0x118]; int mbExpansionPacksOnly; };
class cAppProperties { public: char pad[0x3c]; cAppPropertiesData* mpData; };
extern cAppProperties* sAppProperties;  // 0x015fd918

class cSPEditorPaintLikeThisBase { public: virtual void v0(); int mA, mB; };
class cSPEditorPaintLikeThisRef {
 public:
  virtual int AddRef();
  virtual int Release();
};
class cSPEditorPaintLikeThis : public cSPEditorPaintLikeThisBase, public cSPEditorPaintLikeThisRef {};

}  // namespace SP

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
IAudioSystem* GetSystemAT();
}

namespace Messaging {
union Data {
  uint32_t mUint32;
  uint64_t mUint64;
};
class IMessageRC {
 public:
  virtual int AddRef();
};
class BehaviorMessage : public IMessageRC {
 public:
  BehaviorMessage(uint32_t id) {
    mID = id;
    _InterlockedExchange(&mRefCount, 0);
  }
  long mRefCount;    // +0x4
  Data mData[5];     // +0x8
  uint32_t mID;      // +0x30
  uint32_t pad34;
};
class MessageBasicRC5 : public BehaviorMessage {
 public:
  MessageBasicRC5(uint32_t id) : BehaviorMessage(id), mResult(0) {}
  ~MessageBasicRC5();  // SlotMessage::Destruct (0x00421cf0)
  virtual int AddRef();
  uint32_t mResult;  // +0x38
};
class IMessageServer {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4)
  virtual bool MessageSend(uint32_t id, IMessageRC* msg, void* handler);  // +0x14
};
}  // namespace Messaging
}  // namespace EA

namespace SP {
EA::Messaging::IMessageServer* MessageServer();

struct PageUIEntry {
  EA::AutoRefPtr<cSPPalettePageUI> mpPageUI;  // +0x0
  bool mVisible;                              // +0x4
  bool mShown;                                // +0x5
  bool mDisabled;                             // +0x6
};

typedef EA::AutoRefPtr<cSPEditorPaintLikeThis> PaintLikeThisRef;

// @ 0x005C2EF0  eastl::uninitialized_copy_ptr<PageUIEntry>
PageUIEntry* uninitialized_copy_ptr(PageUIEntry* first, PageUIEntry* last, PageUIEntry* result) {
  for (; first != last; ++first, ++result)
    ::new (result) PageUIEntry(*first);
  return result;
}

// @ 0x005C2F40  eastl::copy_impl<...>::do_copy<AutoRefCount<cSPEditorPaintLikeThis>*>
PaintLikeThisRef* copy(PaintLikeThisRef* first, PaintLikeThisRef* last, PaintLikeThisRef* result) {
  for (; first != last; ++result, ++first)
    *result = *first;
  return result;
}

// @ 0x005C2FA0  eastl::copy_backward_impl<...>::do_copy<AutoRefCount<cSPEditorPaintLikeThis>*>
PaintLikeThisRef* copy_backward(PaintLikeThisRef* first, PaintLikeThisRef* last, PaintLikeThisRef* resultEnd) {
  while (last != first)
    *--resultEnd = *--last;
  return resultEnd;
}

// @ 0x005C3610  eastl::copy_impl<...>::do_copy<PageUIEntry*>
PageUIEntry* copy(PageUIEntry* first, PageUIEntry* last, PageUIEntry* result) {
  for (; first != last; ++result, ++first)
    *result = *first;
  return result;
}

// @ 0x005C3680  eastl::copy_backward_impl<...>::do_copy<PageUIEntry*>
PageUIEntry* copy_backward(PageUIEntry* first, PageUIEntry* last, PageUIEntry* resultEnd) {
  while (last != first)
    *--resultEnd = *--last;
  return resultEnd;
}

struct PageUIEntryAssign : PageUIEntry {
  PageUIEntryAssign& operator=(const PageUIEntryAssign& x);
};

// @ 0x005C35C0  PageUIEntry::operator=
PageUIEntryAssign& PageUIEntryAssign::operator=(const PageUIEntryAssign& x) {
  mpPageUI = x.mpPageUI;
  mVisible = x.mVisible;
  mShown = x.mShown;
  mDisabled = x.mDisabled;
  return *this;
}

class cSPPaletteCategoryUI {
 public:
  char pad00[0x10];
  cSPUILayout* mLayout;                          // +0x10
  cSPUILayout* mExpansionPackLayout;             // +0x14
  IWindow* mWinCategory;                         // +0x18
  IWindow* mWinPageButtons;                      // +0x1c
  IWindow* mWinEPUIHolder;                       // +0x20
  IWindow* mWinColorPickerHolder;                // +0x24
  IWindow* mWinPalettePage;                      // +0x28
  IWindow* mWinFullPalettePage;                  // +0x2c
  cSPEditorColorPicker* mColorPicker1;           // +0x30
  cSPEditorColorPicker* mColorPicker2;           // +0x34
  EA::RectT mOriginalColorPickerArea1;           // +0x38
  EA::RectT mOriginalColorPickerArea2;           // +0x48
  EA::RectT mOriginalColorPickerAreaUnion;       // +0x58
  cSPSwatch* mPreviewSwatch;                     // +0x68
  cSPPaletteCategory* mData;                     // +0x6c
  void* mPageControls;                           // +0x70
  eastl::sp_vector<void*> mPackButtons;          // +0x74
  eastl::sp_vector<PageUIEntry> mPageUIs;        // +0x88
  cSPPaletteSubCategoryUI* mSubCategoryUI;       // +0x9c
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
  tSPEditorPaint GetSelectedPaint();
  uint32_t GetSkinPaintIndex();
  bool IsColor1Default();
  void SetPackPaneVisible(bool visible);
  void SetWindowPositions();
  void UpdatePreviewSwatch();
  void SetSelectedPaint(const tSPEditorPaint& paint);
  bool HandleMessage(uint32_t messageID, void* message);
  void OnPageChanged(int oldIndex, int newIndex);
  bool SetPageIndex(int index);
  bool CyclePage(int direction);
  void SetSelectedPack(uint32_t packID);  // FUN_005c3cb0
  cSPPaletteCategory* GetPaletteCategoryData() { return mData; }
  cSPPaletteSubCategoryUI* GetSubCategoryUI() { return mSubCategoryUI; }
  cSPPalettePageUI* GetPageUI(int index) {
    if (index >= 0 && index < (int)mPageUIs.size())
      return mPageUIs[index].mpPageUI.mpObject;
    return 0;
  }
};

// @ 0x005C2D30
tSPEditorPaint cSPPaletteCategoryUI::GetSelectedPaint() {
  if (GetSubCategoryUI() && GetSubCategoryUI()->GetParentUI())
    return GetSubCategoryUI()->GetParentUI()->GetSelectedPaint();
  tSPEditorPaint paint;
  paint.mPaint = mSelectedItemID;
  paint.mColor1 = mSelectedColor1;
  paint.mColor2 = mSelectedColor2;
  return paint;
}

// @ 0x005C2E00
uint32_t cSPPaletteCategoryUI::GetSkinPaintIndex() {
  cSPPaletteCategoryUI* ui = this;
  while (ui->mData) {
    if (!ui->mSubCategoryUI || !ui->mSubCategoryUI->GetParentUI())
      return ui->mData->mSkinPaintIndex;
    ui = ui->mSubCategoryUI->GetParentUI();
  }
  return 0;
}

// @ 0x005C2E80
bool cSPPaletteCategoryUI::IsColor1Default() {
  if (mSubCategoryUI && mSubCategoryUI->GetParentUI())
    return mSubCategoryUI->GetParentUI()->IsColor1Default();
  return mIsColor1Default;
}

// @ 0x005C2EC0
void cSPPaletteCategoryUI::SetPackPaneVisible(bool visible) {
  IWindow* window = mLayout->FindWindowByID(0x65badef, true);
  if (window)
    window->SetFlag(1, visible);
}

// @ 0x005C3000
void cSPPaletteCategoryUI::SetWindowPositions() {
  bool showPackButtons = (mPackButtons.mpEnd - mPackButtons.mpBegin) >= 1;
  bool hasColorPickers = mLayout->FindWindowByID(0x5d3f56b, true) != 0;
  bool showPageButtons = (int)mData->mPages.size() > 1 || mData->mHasMultiImageButton;
  if (sAppProperties->mpData->mbExpansionPacksOnly && GetNumUniquePacks() < 1)
    showPackButtons = false;
  float y = 5.0f;
  if (showPackButtons) {
    IWindow* epHolder = mWinEPUIHolder;
    if (epHolder)
      y = epHolder->GetArea().bottom + 5.0f;
  }
  if (hasColorPickers) {
    IWindow* pickerHolder = mWinColorPickerHolder;
    if (pickerHolder) {
      EA::RectT area = pickerHolder->GetArea();
      float height = area.Height();
      area.top = y;
      area.bottom = height + y;
      mWinColorPickerHolder->SetLayoutArea(area);
      y = area.bottom + 5.0f;
    }
  }
  IWindow* palettePage = mWinPalettePage;
  if (palettePage) {
    EA::RectT area = palettePage->GetArea();
    area.top = y;
    IWindow* pageButtons;
    if (showPageButtons && (pageButtons = mWinPageButtons) != 0) {
      area.bottom = pageButtons->GetArea().top - 5.0f;
    } else {
      IWindow* fullPage = mWinFullPalettePage;
      if (fullPage)
        area.bottom = fullPage->GetArea().Height() - 5.0f;
    }
    mWinPalettePage->SetLayoutArea(area);
  }
}

// @ 0x005C31C0
void cSPPaletteCategoryUI::UpdatePreviewSwatch() {
  float alpha1 = 1.0f;
  float alpha2 = 1.0f;
  EA::AutoRefCount<cPropertyList> list;
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
      cSPEditorColorPicker* picker2 = mColorPicker2;
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
    tSPEditorPaint paint;
    paint.mPaint = mSelectedItemID;
    paint.mColor1 = mSelectedColor1;
    paint.mColor2 = mSelectedColor2;
    material->SetColor(kSwatchColor);
    material->SetAlpha(1.0f);
    material->mLayer = 7;
    EditorUtils::CreateAndSetPaintMaterial(paint, AddBoundingBox(material, -1)->GetModel());
  }
}

// @ 0x005C34E0
void cSPPaletteCategoryUI::SetSelectedPaint(const tSPEditorPaint& paint) {
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

struct cItemSelectedMessage {
  char pad[0x20];
  struct ISource {
    PV(0) PV(1) PV(2)
    virtual cSPPaletteItem* Cast(uint32_t typeID);  // +0xc
  }* mpSource;  // +0x20
};
struct cColorPickerSourceBase { char pad[8]; };
struct cColorPickerMessage {
  char pad[8];
  uint32_t mColorID;   // +0x8
  char padc[4];
  struct Source : cColorPickerSourceBase {}* mpSource;  // +0x10 (points 8 bytes into the picker)
  char pad14[0x20 - 0x14];
  int mIsDefault;      // +0x20
};
cSPColorRGB ColorFromID(uint32_t colorID);  // 0x00576ab0

// @ 0x005C36F0
bool cSPPaletteCategoryUI::HandleMessage(uint32_t messageID, void* message) {
  if (message) {
  switch (messageID) {
    case 0xb2e18705: {
      cItemSelectedMessage* msg = (cItemSelectedMessage*)message;
      cItemSelectedMessage::ISource* source = msg->mpSource;
      cSPPaletteItem* item = source ? source->Cast(0x72d44e3a) : 0;
      int numPages = (int)mData->mPages.size();
      for (int i = 0; i < numPages; i++) {
        cSPPalettePage* page = GetPaletteCategoryData()->GetPage(i);
        int numItems = (int)page->mItems.size();
        for (int j = 0; j < numItems; j++) {
          if (page->GetItem(j) == item) {
            mSelectedItemID = item->mItemID;
            EA::AutoRefCount<cPropertyList> list;
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
        cSPEditorColorPicker* picker = (cSPEditorColorPicker*)((char*)msg->mpSource - 8);
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

// @ 0x005C3A50
void cSPPaletteCategoryUI::OnPageChanged(int oldIndex, int newIndex) {
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

// @ 0x005C3BD0
bool cSPPaletteCategoryUI::SetPageIndex(int index) {
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

// @ 0x005C3C20
bool cSPPaletteCategoryUI::CyclePage(int direction) {
  int oldIndex = mCurrentPageIndex;
  int numPages = (int)mPageUIs.size();
  if (numPages >= 2) {
    do {
      mCurrentPageIndex = (numPages + direction + mCurrentPageIndex) % numPages;
      PageUIEntry& entry = mPageUIs[mCurrentPageIndex];
      cSPPalettePageUI* pageUI = entry.mpPageUI.mpObject;
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
