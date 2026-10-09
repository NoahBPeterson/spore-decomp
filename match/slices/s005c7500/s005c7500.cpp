// slice s005c7500 -- SP palette-item cursor (ctor / SetPalette / Advance / Current / Next /
// Reset / Shutdown), cSPPalettePage (ctor + deleting dtor) and two large UI functions
// (cSPOLDPaletteItemUI::Init, cSPPalettePage::ProcessPagePart).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include <new>
#include "types.h"

extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
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
  using EA::RefCountVTemplate<int>::AddRef;
  using EA::RefCountVTemplate<int>::Release;
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
  // Out-of-line trivial accessors / checks called by cSPOLDPaletteItemUI::Init.
  int GetPriority();                      // 0x00641770: return [this+0x28]
  EA::ResourceMan::Key* GetPlanetKey();   // 0x00b7e380: return &[this+0x2c]
  uint32_t GetSwatchColor();              // 0x00a1ad10: return [this+0x38]
  EA::ResourceMan::Key* GetCities();      // 0x005c65e0: return &[this+0x3c]
  bool IsHidden();                        // 0x005c6620: return mbHidden
  bool CheckInfo(struct SwatchInfo* info);  // 0x005c65f0, ret 4
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
// cSPOLDPaletteItemUI::Init and the UI stubs it needs.
class cSPSwatch : public EA::RefCountVTemplate<int>, public EA::COM::IUnknown32 {
 public:
  using EA::RefCountVTemplate<int>::AddRef;
  using EA::RefCountVTemplate<int>::Release;
  char pad0c[0x140 - 0x0c];
};

typedef EA::ResourceMan::Key ResKey;

// Window object: only the vtable slots Init uses (slot 0 AddRef, 1 Release).
struct Rect4 {
  float x0, y0, x1, y1;
};
class UIWindow {
 public:
  void** vptr;
  int AddRef() { return ((int(__thiscall*)(UIWindow*))vptr[0])(this); }
  int Release() { return ((int(__thiscall*)(UIWindow*))vptr[1])(this); }
  Rect4* GetArea() { return ((Rect4*(__thiscall*)(UIWindow*))vptr[0x38 / 4])(this); }
  UIWindow* FindWindowByID(uint32_t id, bool recurse) {
    return ((UIWindow*(__thiscall*)(UIWindow*, uint32_t, bool))vptr[0xf0 / 4])(this, id, recurse);
  }
  void SetField60(int v) { ((void(__thiscall*)(UIWindow*, int))vptr[0x60 / 4])(this, v); }
  void SetFlag(int mask, bool on) {
    ((void(__thiscall*)(UIWindow*, int, bool))vptr[0x7c / 4])(this, mask, on);
  }
  void AddChild(UIWindow* w) { ((void(__thiscall*)(UIWindow*, UIWindow*))vptr[0xd8 / 4])(this, w); }
  void AddWinProc(void* proc) { ((void(__thiscall*)(UIWindow*, void*))vptr[0x104 / 4])(this, proc); }
};

// Out-of-line AutoRefCount assignment (0x00b5f950) is kept for some sites via SetOol.
template <typename T>
class WinRef {
 public:
  T* mpObject;
  WinRef() : mpObject(0) {}
  ~WinRef() { if (mpObject) mpObject->Release(); }
  WinRef& operator=(T* p) {
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
  void SetOol(T* p);  // 0x00b5f950: AutoRefCount<T>::operator=(T*), not inlined
  operator T*() const { return mpObject; }
  T* operator->() const { return mpObject; }
};

struct SwatchInfo {
  bool Has(uint64_t key);  // 0x00595110, ret 8
};
class SwatchVerifier {
 public:
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void v3();
  virtual int Query(const ResKey* key, int arg);  // slot 4
};
// Retail layout of cSPSwatch as read by Init (the stub class above is only a size placeholder).
struct SwatchView {
  int pad0;
  int pad4;
  SwatchVerifier* mVerifier;  // +8
  int pad0c;
  SwatchInfo* mInfo;          // +0x10
};

class cSPUILayout {
 public:
  cSPUILayout();                                                // 0x00810000
  ~cSPUILayout();                                               // 0x00811fe0
  void Init(const ResKey* key, bool flag, uint32_t id);         // 0x008120d0
  UIWindow* FindWindowByID(uint32_t id, bool recurse);          // 0x008105b0
  int pad[3];
};

class cString {
 public:
  cString(uint32_t table, uint32_t instance, const wchar_t* def);  // 0x006b5770
  ~cString();                                                       // 0x006b5240
  const wchar_t* GetText();                                         // 0x006b55c0
  int pad[7];
};

struct Vec2 {
  float x, y;
};

class cSPUITooltipWinProc {
 public:
  cSPUITooltipWinProc(const wchar_t* name, uint32_t id, const wchar_t* text, const Vec2* pos,
                      int a, const void* b, int c);  // 0x00835e30, ret 0x1c
  static void* operator new(unsigned int size, unsigned int align, const char* name, void* alloc);  // 0x009512d0
  virtual int AddRef();
  virtual int Release();
  int pad[0x68 / 4 - 1];
};

class DragAndBuy {
 public:
  DragAndBuy();  // 0x005f7380
  virtual int AddRef();
  virtual int Release();
  void Init(const ResKey* key, UIWindow* win, UIWindow* parent, uint32_t msg, cSPPaletteItem* item,
            cSPSwatch* swatch, bool flag);  // 0x005f4310, ret 0x1c
  static void* operator new(unsigned int size, const char* name, int a, int b, int c, int d);  // 0x00f473a0
  int pad[0x1c8 / 4 - 1];
};
// AutoRefCount ctor (stores the pointer and AddRefs), not inlined here.
struct DragAndBuyRef {
  DragAndBuy* mpObject;
  DragAndBuyRef(DragAndBuy* p);  // 0x00572660
};
class cSPSwatchManager {
 public:
  DragAndBuy* CreateSwatch(DragAndBuy* existing);  // 0x005f0ca0, ret 4
};

cSPSwatchManager* GetSwatchManager();                                       // 0x00401020
uint64_t MakeKey64(uint32_t hi, uint32_t lo);                                // 0x00593980
void* GetUIAllocator();                                                     // 0x009512c0
UIWindow* CreateWindowFor(UIWindow* parent);                                // 0x00806370
UIWindow* CreateImageWindow(const ResKey* key, float x, float y, UIWindow* parent);  // 0x00807880
void SetImageIcon(UIWindow* w, void* image, int a);                         // 0x00806aa0
void CenterWindowInRect(UIWindow* w, Rect4* r);                             // 0x00806d10
void* GetImageFromLayout(uint32_t id);                                      // 0x00458de0
extern char* g_ptr15fd918;                                                  // 0x015fd918
extern int g_data13f80fc;                                                   // 0x013f80fc

inline bool EditorFlag() { return *(int*)(*(char**)(g_ptr15fd918 + 0x3c) + 0x118) != 0; }

class cSPOLDPaletteItemUI : public EA::COM::IUnknown32, public EA::RefCountVTemplate<int> {
 public:
  AutoRefCount<cSPPaletteItem> mData;  // +0xc
  AutoRefCount<cSPSwatch> mSwatch;     // +0x10
  WinRef<DragAndBuy> mDragAndBuy;      // +0x14
  AutoRefCount<UIWindow> mWindow;      // +0x18
  void Init(cSPPaletteItem* item, UIWindow* parent, int arg3, cSPSwatch* swatch);
};

// @ 0x005C7500
void cSPOLDPaletteItemUI::Init(cSPPaletteItem* item, UIWindow* parent, int arg3, cSPSwatch* swatch) {
  mData = item;
  mSwatch = swatch;
  bool isHidden = false;
  bool checkResult = true;
  bool hasImage = true;
  bool flagged = false;
  uint32_t type = mData->mItemType;
  if (type == 0x81c74dbc || type == 0x8bfac054 || type == 0xe1e54b3b)
    hasImage = false;
  WinRef<UIWindow> win;
  void* iconId = 0;
  uint32_t iconValue = 0;

  if (hasImage) {
    if (EditorFlag() && item)
      flagged = item->mIndex < 0;
    if (swatch) {
      SwatchInfo* info = ((SwatchView*)swatch)->mInfo;
      if (info) {
        uint64_t k = MakeKey64(item->mItemKey.mGroup, item->mItemKey.mInstance);
        isHidden = !info->Has(k);
        if (!isHidden && !flagged) {
          int r = 1;
          SwatchVerifier* v = ((SwatchView*)swatch)->mVerifier;
          if (v)
            r = v->Query(&item->mItemKey, 0);
          isHidden = r == 7;
        }
      }
    }
    if (item)
      checkResult = item->CheckInfo(((SwatchView*)swatch)->mInfo);

    if (isHidden) {
      ResKey key;
      key.mInstance = 0;
      key.mType = 0;
      key.mGroup = 0;
      if (!checkResult) {
        iconValue = item->GetSwatchColor();
        key = *item->GetCities();
      } else {
        iconValue = item->GetPriority();
        key = *item->GetPlanetKey();
      }
      if (key.mInstance != 0) {
        cSPUILayout layout;
        layout.Init(&key, true, 0x5b598fa);
        win.SetOol(layout.FindWindowByID(0x902d3163, true));
      }
      if (win && key.mInstance != 0) {
        parent->AddChild(win);
        Rect4 r = *win->GetArea();
        r.x1 = r.x1 - r.x0;
        r.y1 = r.y1 - r.y0;
        r.x0 = 0.0f;
        r.y0 = 0.0f;
        CenterWindowInRect(win, &r);
        UIWindow* child = win->FindWindowByID(0x4976e19, false);
        if (child && iconValue) {
          child->SetFlag(0x10, true);
          SetImageIcon(child, GetImageFromLayout(iconValue), 0);
        }
      } else {
        ResKey fallback(0x3cf13a01, 0x2f7d0004, 0x11c0bde);
        win.SetOol(CreateImageWindow(&fallback, 0.0f, 0.0f, parent));
      }
    } else if (EditorFlag() && flagged) {
      ResKey lockedKey(0x43c6e503, 0x2f7d0004, 0x11c0bde);
      win.SetOol(CreateImageWindow(&lockedKey, 0.0f, 0.0f, parent));
    } else {
      win = CreateImageWindow(&mData->mThumbnailKey, 0.0f, 0.0f, parent);
    }
  } else {
    win = CreateWindowFor(parent);
  }

  if (win) {
    win->SetField60(arg3);
    if (isHidden) {
      if (item && item->IsHidden()) {
        win->AddWinProc((char*)this + 8);
        win->SetFlag(0x10, false);
        win->SetFlag(2, true);
      } else {
        win->SetFlag(0x10, true);
        win->SetFlag(2, false);
      }
    } else if (EditorFlag() && flagged) {
      Vec2 pos;
      pos.x = 5.0f;
      pos.y = -15.0f;
      cString text(0x496bfb26, 0x538602b, 0);
      cSPUITooltipWinProc* tip = new (4, "UI/Tooltip", GetUIAllocator())
          cSPUITooltipWinProc(L"Tooltips", 0x3754e6c, text.GetText(), &pos, 0, &g_data13f80fc, 0);
      if (tip)
        tip->AddRef();
      win->AddWinProc(tip);
      if (tip)
        tip->Release();
    } else {
      DragAndBuy* obj;
      switch (mData->mItemType) {
        case 0x4d863c8b:
        case 0x0fcafd26:
        case 0x2b885df4:
        case 0xe73759f3:
          if (!swatch)
            goto done;
          obj = GetSwatchManager()->CreateSwatch(new ("Editor", 0, 0, 0, 0) DragAndBuy());
          if (obj)
            obj->AddRef();
          break;
        case 0xa2e50993:
        case 0xc9db779b: {
          if (!swatch)
            goto done;
          DragAndBuyRef r(
              GetSwatchManager()->CreateSwatch(new ("Editor", 0, 0, 0, 0) DragAndBuy()));
          obj = r.mpObject;
          break;
        }
        default:
          goto done;
      }
      obj->Init(&mData->mItemKey, win, parent, 0xb2e18705, mData, swatch, true);
      mDragAndBuy.SetOol(obj);
      if (obj)
        obj->Release();
    }
  }
done:
  mWindow = win;
}

// @ 0x005C7FF0
void cSPPalettePage::ProcessPagePart(int a, void* b, int c) {
  // Partial: full body (1104 bytes) not reconstructed.
  (void)a;
  (void)b;
  (void)c;
}
}  // namespace SP
