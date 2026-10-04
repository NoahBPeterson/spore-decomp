// SP::cSPPaletteCategory (palette category data) and parts of SP::cSPPaletteCategoryUI.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include <new>
#include <string.h>
#include "types.h"

extern "C" void EASTL_allocator_deallocate(void* p);
extern "C" void* EASTL_memmove(void* dst, const void* src, unsigned int n);  // 0x011e0744 (static memmove)

#define PV(n) virtual void pv##n();

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
  PV(25) PV(26) PV(27) PV(28) PV(29) PV(30)
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

// @ 0x005C2120  vector<unsigned int, sp_vector_allocator>::insert
// @ 0x005C21D0  vector<AutoRefCount<T>, sp_vector_allocator>::insert
template <typename T>
__declspec(noinline) T* sp_vector<T>::insert(T* position, const T& value) {
  const int n = (int)(position - mpBegin);
  if ((position == mpEnd) && (mpEnd != mpCapacity))
    ::new (mpEnd++) T(value);
  else
    DoInsertValue(position, value);
  return mpBegin + n;
}

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

// @ 0x005C2170  vector<AutoRefCount<T>, sp_vector_allocator>::erase
template <typename T>
EA::AutoRefCount<T>* sp_ref_vector<T>::erase(value_type* first, value_type* last) {
  value_type* const position = eastl::copy(last, this->mpEnd, first);
  destruct(position, this->mpEnd);
  this->mpEnd -= (last - first);
  return first;
}

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

// @ 0x005C1D70
cSPPaletteCategory* cSPPaletteCategory::FindSubCategory(uint32_t categoryID) {
  for (unsigned int i = 0; i < mSubCategories.size(); i++) {
    EA::AutoRefCount<cSPPaletteCategory>& sub = mSubCategories[i];
    if (sub->mCategoryId == categoryID)
      return sub;
    cSPPaletteCategory* found = sub->FindSubCategory(categoryID);
    if (found)
      return found;
  }
  return 0;
}


inline bool GetPropBool(cPropertyList* list, uint32_t id, bool& value) {
  Property* prop;
  if (list && list->GetProperty(id, prop) && prop->mType == 1) {
    value = *prop->GetBool();
    return true;
  }
  return false;
}
inline bool GetPropUInt(cPropertyList* list, uint32_t id, uint32_t& value) {
  Property* prop;
  if (list && list->GetProperty(id, prop) && prop->mType == 10) {
    value = *prop->GetUInt();
    return true;
  }
  return false;
}

// @ 0x005C1E20
bool cSPPaletteCategory::Init(const EA::ResourceMan::Key& key, unsigned int layoutInstanceID) {
  EA::AutoRefCount<cPropertyList> list;
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
  EA::ResourceMan::Key parentKey(0, 0, 0);
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

// @ 0x005C2020
cSPPaletteCategory::cSPPaletteCategory()
    : mLayoutInstanceID(0x89845152), mSequenceNumber(0), mPaintByNumber(false), mRegionFilter(0xffffffff),
      mSkinPaintIndex(0xffffffff), mHasMultiImageButton(false), mCategoryId(0), mParentCategory(0),
      mButtonImageKey(0, 0, 0), mpButtonImageKeys(0), mIsSubCategory(false) {}

// @ 0x005C20B0
cSPPaletteCategory::~cSPPaletteCategory() {}

// @ 0x005C2230
void cSPPaletteCategory::Shutdown() {
  int numPages = (int)mPages.size();
  for (int i = 0; i < numPages; i++)
    mPages[i]->Shutdown();
  mPages.clear();
  mPacks.clear();
  mSubCategories.clear();
}

// @ 0x005C22B0
void cSPPaletteCategory::AddSubCategory(cSPPaletteCategory* category) {
  unsigned int sequence = category->mSequenceNumber;
  category->mIsSubCategory = true;
  EA::AutoRefCount<cSPPaletteCategory>* end = mSubCategories.end();
  for (EA::AutoRefCount<cSPPaletteCategory>* it = mSubCategories.begin(); it != end; ++it) {
    EA::AutoRefCount<cSPPaletteCategory> current(*it);
    if (current->mSequenceNumber > sequence) {
      mSubCategories.insert(it, EA::AutoRefCount<cSPPaletteCategory>(category));
      return;
    }
  }
  mSubCategories.push_back(EA::AutoRefCount<cSPPaletteCategory>(category));
}

// @ 0x005C2390
void cSPPaletteCategory::AddPage(cSPPalettePage* page) {
  unsigned int sequence = page->mSequenceNumber;
  EA::AutoRefCount<cSPPalettePage>* end = mPages.end();
  EA::AutoRefCount<cSPPalettePage>* it;
  for (it = mPages.begin(); it != end; ++it) {
    EA::AutoRefCount<cSPPalettePage> current(*it);
    if (current->mSequenceNumber > sequence) {
      mPages.insert(it, EA::AutoRefCount<cSPPalettePage>(page));
      goto addPack;
    }
  }
  mPages.push_back(EA::AutoRefCount<cSPPalettePage>(page));
addPack:
  unsigned int packID = page->mPackID;
  if (eastl::find(mPacks.mpBegin, mPacks.mpEnd, packID) == mPacks.mpEnd) {
    unsigned int* p = mPacks.mpBegin;
    unsigned int* packsEnd = mPacks.mpEnd;
    PackInfo* info = PackageManager()->GetPackInfo(packID);
    if (info) {
      int priority = info->mPriority;
      for (; p != packsEnd; ++p) {
        if (PackageManager()->GetPackInfo(*p)->mPriority > priority) {
          mPacks.insert(p, packID);
          goto done;
        }
      }
      mPacks.push_back(packID);
    }
  }
done:
  page->mRegionFilter = (mRegionFilter != 0xffffffff) ? mRegionFilter : mSkinPaintIndex;
}

// ---------------------------------------------------------------- cSPPaletteCategoryUI
class cSPUILayout {
 public:
  IWindow* FindWindowByID(uint32_t id, bool recursive);
};
class cSPEditorColorPicker { public: void Update(int deltaTime); /* FUN_005a6db0 */ };
class cSPEditorPageControls { public: void Update(int deltaTime); };
class cSPPaletteSubCategoryUI {
 public:
  void Update(int deltaTime);                    // FUN_005c98a0
  class cSPPaletteCategoryUI* GetParentUI();  // FUN_005c9830
};
class cSPPalettePageUI { public: void Update(int deltaTime); /* FUN_005c8d30 */ };
class cSPSwatch {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  virtual void SetVisible(bool visible);  // +0x2c
};
class IWinButton {
 public:
  PV(0) PV(1) PV(2) PV(3)
  virtual IWindow* ToWindow();  // +0x10
};
struct PageUIEntry {
  cSPPalettePageUI* mpPageUI;  // +0x0
  bool mVisible;               // +0x4
  bool pad5;
  bool mDisabled;              // +0x6
  bool pad7;
};

class cSPPaletteCategoryUI {
 public:
  char pad00[0x10];
  cSPUILayout* mLayout;                        // +0x10
  char pad14[4];
  IWindow* mWinCategory;                       // +0x18
  char pad1c[4];
  IWindow* mWinEPUIHolder;                     // +0x20
  char pad24[0x30 - 0x24];
  cSPEditorColorPicker* mColorPicker1;         // +0x30
  cSPEditorColorPicker* mColorPicker2;         // +0x34
  char pad38[0x68 - 0x38];
  cSPSwatch* mPreviewSwatch;                   // +0x68
  cSPPaletteCategory* mData;                   // +0x6c
  cSPEditorPageControls* mPageControls;        // +0x70
  eastl::sp_vector<IWinButton*> mPackButtons;  // +0x74
  eastl::sp_vector<PageUIEntry> mPageUIs;      // +0x88
  cSPPaletteSubCategoryUI* mSubCategoryUI;     // +0x9c
  int mCurrentPageIndex;                       // +0xa0
  int mFilterSetId;                            // +0xa4
  int mExpansionPackChunkIndex;                // +0xa8
  unsigned int mCurrentPackID;                 // +0xac
  int mExpansionPacksPerPage;                  // +0xb0

  void SetVisibleChunk(int chunkIndex);
  void SetButtonPositions();
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

// @ 0x005C2590
void cSPPaletteCategoryUI::SetVisibleChunk(int chunkIndex) {
  mExpansionPackChunkIndex = chunkIndex;
  int numChunks = (int)((mPackButtons.size() + mExpansionPacksPerPage - 1) / mExpansionPacksPerPage);
  IWindow* window = mLayout->FindWindowByID(0x5d1ad44, true);
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

// @ 0x005C2660
void cSPPaletteCategoryUI::SetButtonPositions() {
  if (mWinEPUIHolder && mPackButtons.mpBegin != mPackButtons.mpEnd) {
    IWindow* area = mLayout->FindWindowByID(0x5d1ad4a, true);
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
      IWindow* window = mPackButtons[i]->ToWindow();
      window->GetParent();
      window->GetFlags();
      window->GetRealArea();
      unsigned int column = (unsigned int)i % (unsigned int)count;
      EA::RectT r;
      r.left = (float)(int)(column + 1) * spacing + (float)(int)column * buttonWidth;
      r.top = top;
      r.right = r.left + buttonWidth;
      r.bottom = top + buttonHeight;
      window->SetArea(r);
    }
  }
}

// @ 0x005C28B0
void cSPPaletteCategoryUI::Update(int deltaTime) {
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

// @ 0x005C2940
bool cSPPaletteCategoryUI::IsVisible() {
  IWindow* window = mWinCategory;
  if (window)
    return window->GetFlags() & 1;
  return false;
}


// @ 0x005C2960
void cSPPaletteCategoryUI::SetVisibility(bool visible) {
  IWindow* window = mWinCategory;
  if (window)
    window->SetFlag(1, visible);
  cSPSwatch* swatch = mPreviewSwatch;
  if (swatch)
    swatch->SetVisible(visible);
  IWindow* holder = mWinEPUIHolder;
  if (holder)
    holder->SetFlag(1, visible);
}

// @ 0x005C29A0
void cSPPaletteCategoryUI::SetPageVisible(int index, bool visible) {
  mPageUIs[index].mVisible = visible;
}

// @ 0x005C29C0
bool cSPPaletteCategoryUI::IsPageVisible(int index) {
  return mPageUIs[index].mVisible;
}

// @ 0x005C29E0
int cSPPaletteCategoryUI::GetPageIndexForPackID(uint32_t packID) {
  int numPages = (int)mData->GetNumPages();
  for (int i = 0; i < numPages; i++) {
    if (mData->GetPage(i)->mPackID == packID)
      return i;
  }
  return -1;
}

// @ 0x005C2A30
int cSPPaletteCategoryUI::GetChunkIndexForPackID(uint32_t packID) {
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

static inline bool SameDescription(const PackDescription* a, const PackDescription* b) {
  return a->mData[0] == b->mData[0] && a->mData[1] == b->mData[1] && a->mData[2] == b->mData[2] &&
         a->mData[3] == b->mData[3] && a->mData[4] == b->mData[4] && a->mData[5] == b->mData[5];
}

// @ 0x005C2AA0
int cSPPaletteCategoryUI::GetNumUniquePacks() {
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

// @ 0x005C2BC0
bool cSPPaletteCategoryUI::IsPackUnique(int index) {
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

// @ 0x005C2CD0
bool cSPPaletteCategoryUI::IsPaintByNumber() {
  if (mData)
    return mData->mPaintByNumber;
  return false;
}

// @ 0x005C2CE0
uint32_t cSPPaletteCategoryUI::GetRegionFilterID() {
  cSPPaletteCategoryUI* ui = this;
  while (ui->mData) {
    if (!ui->mSubCategoryUI || !ui->mSubCategoryUI->GetParentUI())
      return ui->mData->mRegionFilter;
    ui = ui->mSubCategoryUI->GetParentUI();
  }
  return 0;
}
}  // namespace SP
