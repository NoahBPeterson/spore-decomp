// slice s005c7500 -- SP palette-item cursor (ctor / SetPalette / Advance / Current / Next /
// Reset / Shutdown), cSPPalettePage (ctor + deleting dtor) and two large UI functions
// (cSPOLDPaletteItemUI::Init, cSPPalettePage::ProcessPagePart).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include <new>
#include "types.h"

extern "C" void EASTL_allocator_deallocate(void* p);
void* operator new(unsigned int n, const char* name, int flags, unsigned int debugFlags,
                   const char* file, int line);

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
  AutoRefCount& operator=(T* p) {
    if (p != mpObject) {
      T* const pTemp = mpObject;
      if (p)
        p->AddRef();
      mpObject = p;
      if (pTemp)
        pTemp->Release();
    }
    return *this;
  }
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
}  // namespace COM

namespace ResourceMan {
struct Key {
  unsigned int mInstance, mType, mGroup;
  Key() {}
  Key(unsigned int i, unsigned int t, unsigned int g) : mInstance(i), mType(t), mGroup(g) {}
};
}  // namespace ResourceMan
}  // namespace EA

namespace eastl {
template <typename T>
class sp_vector {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  int mAllocator[2];
  sp_vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~sp_vector() {}
  T* begin() { return mpBegin; }
  T* end() { return mpEnd; }
};

// 3-pointer vector with an out-of-line destructor (cSPPalettePage::mItems at +0x70 -> 0x5c7f10)
template <typename T>
class sp_vector0 {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  sp_vector0() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~sp_vector0();
  T* begin() { return mpBegin; }
  T* end() { return mpEnd; }
};
}  // namespace eastl

using EA::AutoRefCount;

namespace SP {
class cSPPalettePage;
class cSPPaletteItem;
class cSPSwatch;
class cPlanetModel;

class cSPPaletteCategory {
 public:
  PV(0)
  virtual int AddRef();
  virtual int Release();
  char pad04[8];                                            // +4
  eastl::sp_vector<AutoRefCount<cSPPalettePage> > mPages;   // +0xc
  eastl::sp_vector<unsigned int> mPacks;                    // +0x20
  eastl::sp_vector<AutoRefCount<cSPPaletteCategory> > mSubCategories;  // +0x34
  cSPPaletteCategory* GetSubCategory(int index);  // 0x005cae30
  cSPPalettePage* GetPage(int index);             // 0x005c1ce0
};

class cSPPalette {
 public:
  PV(0)
  virtual int AddRef();
  virtual int Release();
  char pad04[8];                                             // +4
  eastl::sp_vector<AutoRefCount<cSPPaletteCategory> > mCategories;  // +0xc
  cSPPaletteCategory* GetCategory(int index);  // 0x005c5de0
};

class cSPPaletteItem : public EA::RefCountVTemplate<int>, public EA::COM::IUnknown32 {
 public:
  enum eItemType {
    kItemTypeUnknown = -1,
    kBlock = 0xa2e50993,
    kBakedModel = 0x674ab27,
    kSwatch = 0x2c7c0887,
  };
  EA::ResourceMan::Key mItemKey;          // +0xc
  EA::ResourceMan::Key mThumbnailKey;     // +0x18
  eItemType mItemType;                    // +0x24
  int mPriority;                          // +0x28
  EA::ResourceMan::Key mSwatchKey;        // +0x2c
  uint32_t mSwatchColor;                  // +0x38
  EA::ResourceMan::Key mSwatchKey2;       // +0x3c
  int mIndex;                             // +0x48
  bool mbHidden;                          // +0x4c
  AutoRefCount<EA::COM::IUnknown32> mpData;  // +0x50
  void Shutdown();                        // 0x005c6710
};

class cSPPalettePage : public EA::RefCountVTemplate<int>, public EA::COM::IUnknown32 {
 public:
  cSPPalettePage();
  virtual ~cSPPalettePage();
  void Shutdown();  // 0x005c7ed0
  int GetItemIndex(int itemIndex);  // 0x005c7f00
  void ProcessPagePart(int a, void* b, int c);  // 0x005c7ff0

  uint32_t mLayoutInstanceID;  // +0xc
  int mField10;                // +0x10
  float mFloat14;              // +0x14
  float mFloat18;              // +0x18
  float mFloat1c;              // +0x1c
  float mFloat20;              // +0x20
  float mFloat24;              // +0x24
  float mFloat28;              // +0x28
  bool mBool2c;                // +0x2c
  bool mBool2d;                // +0x2d
  char pad2e[0x48 - 0x2e];
  bool mBool48;  // +0x48
  bool mBool49;  // +0x49
  bool mBool4a;  // +0x4a
  char pad4b;
  float mFloat4c;              // +0x4c
  int mField50;                // +0x50
  int mField54;                // +0x54
  uint32_t mField58;           // +0x58
  int mField5c;                // +0x5c
  int mCategoryKey0;           // +0x60
  int mCategoryKey1;           // +0x64
  int mCategoryKey2;           // +0x68
  int mField6c;                // +0x6c
  eastl::sp_vector0<AutoRefCount<cSPPaletteItem> > mItems;  // +0x70
};

// The palette cursor over cSPPalette -> category -> subcategory -> page -> item.
class cSPPaletteCursor : public EA::RefCountVTemplate<int>, public EA::COM::IUnknown32 {
 public:
  cSPPaletteCursor();
  void SetPalette(cSPPalette* palette);
  bool Advance();
  int Current(void* out1, int* out2, int* out3, int* out4);
  int Next(void* a, int* b, int* c, int* d);
  int Reset(void* a, int* b, int* c, int* d);

  AutoRefCount<cSPPalette> mPalette;  // +0xc
  int mCategoryIndex;                 // +0x10
  int mSubCategoryIndex;              // +0x14
  int mPageIndex;                     // +0x18
  int mItemIndex;                     // +0x1c
};

// @ 0x005C7B80
cSPPaletteCursor::cSPPaletteCursor()
    : mPalette(0), mCategoryIndex(0), mSubCategoryIndex(0), mPageIndex(0), mItemIndex(0) {}

// @ 0x005C7BC0
void cSPPaletteCursor::SetPalette(cSPPalette* palette) {
  mPalette = palette;
  mCategoryIndex = 0;
  mSubCategoryIndex = 0;
  mPageIndex = 0;
  mItemIndex = 0;
}

// @ 0x005C7C10
bool cSPPaletteCursor::Advance() {
  cSPPaletteCategory* category;
  if (mCategoryIndex >= (int)(mPalette->mCategories.mpEnd - mPalette->mCategories.mpBegin)) {
    return false;
  }
  do {
    category = mPalette->GetCategory(mCategoryIndex);
    if (mSubCategoryIndex <
        (int)(category->mSubCategories.mpEnd - category->mSubCategories.mpBegin)) {
      do {
        cSPPaletteCategory* sub = category->GetSubCategory(mSubCategoryIndex);
        if (mPageIndex < (int)(sub->mPages.mpEnd - sub->mPages.mpBegin)) {
          do {
            cSPPalettePage* page = sub->GetPage(mPageIndex);
            if (mItemIndex < (int)(page->mItems.mpEnd - page->mItems.mpBegin))
              return true;
            mPageIndex++;
            mItemIndex = 0;
          } while (mPageIndex < (int)(sub->mPages.mpEnd - sub->mPages.mpBegin));
        }
        mSubCategoryIndex++;
        mPageIndex = 0;
      } while (mSubCategoryIndex <
               (int)(category->mSubCategories.mpEnd - category->mSubCategories.mpBegin));
    }
    mSubCategoryIndex = 0;
    if (mPageIndex < (int)(category->mPages.mpEnd - category->mPages.mpBegin)) {
      do {
        cSPPalettePage* page = category->GetPage(mPageIndex);
        if (mItemIndex < (int)(page->mItems.mpEnd - page->mItems.mpBegin))
          return true;
        mPageIndex++;
        mItemIndex = 0;
      } while (mPageIndex < (int)(category->mPages.mpEnd - category->mPages.mpBegin));
    }
    mCategoryIndex++;
    mItemIndex = 0;
  } while (mCategoryIndex < (int)(mPalette->mCategories.mpEnd - mPalette->mCategories.mpBegin));
  return false;
}

// @ 0x005C7D30
int cSPPaletteCursor::Current(void* out1, int* out2, int* out3, int* out4) {
  cSPPaletteCategory* category = mPalette->GetCategory(mCategoryIndex);
  if (category) {
    if (0 < (int)(category->mSubCategories.mpEnd - category->mSubCategories.mpBegin))
      category = category->GetSubCategory(mSubCategoryIndex);
    if (out1)
      *(int*)out1 = *(int*)((char*)category + 0x74);
    cSPPalettePage* page = category->GetPage(mPageIndex);
    if (page) {
      int count = page->mField50;
      if (out2)
        *out2 = mItemIndex % count;
      if (out3)
        *out3 = mItemIndex / count;
      if (out4)
        *(int*)out4 = mPageIndex;
      return page->GetItemIndex(mItemIndex);
    }
  }
  return 0;
}

// @ 0x005C7E20
int cSPPaletteCursor::Next(void* a, int* b, int* c, int* d) {
  int result = 0;
  if (!Advance())
    return result;
  do {
    result = Current(a, b, c, d);
    mItemIndex++;
    if (result)
      break;
  } while (Advance());
  return result;
}

// @ 0x005C7E80
int cSPPaletteCursor::Reset(void* a, int* b, int* c, int* d) {
  mCategoryIndex = 0;
  mSubCategoryIndex = 0;
  mPageIndex = 0;
  mItemIndex = 0;
  return Next(a, b, c, d);
}

// @ 0x005C7ED0
void cSPPalettePage::Shutdown() {
  int count = (int)(mItems.mpEnd - mItems.mpBegin);
  for (int i = 0; i < count; i++) {
    cSPPaletteItem* item = mItems.mpBegin[i];
    if (item)
      item->Shutdown();
  }
}

extern float g_one;  // 0x01485720

// @ 0x005C7F50
cSPPalettePage::cSPPalettePage()
    : mLayoutInstanceID(0xd8006607),
      mField10(0),
      mFloat14(0.0f),
      mFloat18(0.0f),
      mFloat1c(0.0f),
      mFloat20(0.0f),
      mFloat24(0.0f),
      mFloat28(0.0f),
      mBool2c(false),
      mBool2d(false),
      mBool48(false),
      mBool49(false),
      mBool4a(false),
      mFloat4c(g_one),
      mField50(0),
      mField54(0),
      mField58(0),
      mField5c(0),
      mCategoryKey0(-1),
      mCategoryKey1(0),
      mCategoryKey2(0),
      mField6c(0) {}

// @ 0x005C8440
cSPPalettePage::~cSPPalettePage() {}

// ---------------------------------------------------------------------------------------------
// Large UI functions: signatures preserved, bodies not reconstructed (partial).
class cSPSwatch : public EA::RefCountVTemplate<int>, public EA::COM::IUnknown32 {
 public:
  char pad0c[0x140 - 0x0c];
};

class cSPOLDPaletteItemUI : public EA::COM::IUnknown32, public EA::RefCountVTemplate<int> {
 public:
  AutoRefCount<cSPPaletteItem> mData;  // +0xc
  AutoRefCount<cSPSwatch> mSwatch;     // +0x10
  void Init(cPlanetModel* model, int a, int b, cSPSwatch* swatch);
};

// @ 0x005C7500
void cSPOLDPaletteItemUI::Init(cPlanetModel* model, int a, int b, cSPSwatch* swatch) {
  // Partial: full body (1606 bytes) not reconstructed.
  (void)model;
  (void)a;
  (void)b;
  (void)swatch;
}

// @ 0x005C7FF0
void cSPPalettePage::ProcessPagePart(int a, void* b, int c) {
  // Partial: full body (1104 bytes) not reconstructed.
  (void)a;
  (void)b;
  (void)c;
}
}  // namespace SP
