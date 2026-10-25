// slice s005c9230 -- cUIMissionCard-ish page/feed UI object: SetWindowFlag / GetCurrent /
// ctor / dtor / DoMessage, plus cSPPalettePageUI::Init and a big subcategory updater.
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
  ~AutoRefCount() { if (mpObject) mpObject->Release(); }
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
};
}  // namespace EA
using EA::AutoRefCount;

namespace EA {
namespace UTFWin {
class IUnknown32 {
 public:
  virtual int AddRef();   // +0
  virtual int Release();  // +4
};
class IWindow : public IUnknown32 {
 public:
  PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12)
  PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24)
  PV(25) PV(26) PV(27) PV(28) PV(29) PV(30)
  virtual void SetFlag(int flag, int value);  // +0x7c
};
}  // namespace UTFWin
}  // namespace EA
using EA::UTFWin::IWindow;

namespace eastl {
// Vector whose element dtor is trivial: dtor inlines to a single allocator free.
template <typename T>
class sp_trivial_vector {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  int mAllocator[2];
  sp_trivial_vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~sp_trivial_vector() {
    if (mpBegin && ((int*)mpBegin)[-1] != 0)
      EASTL_allocator_deallocate(mpBegin);
  }
};

// Vector of refcounted elements: out-of-line destructor (call target 0x005c9c30).
class cCategory;
template <typename T>
class sp_ref_vector {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  int mAllocator[2];
  sp_ref_vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~sp_ref_vector();
  unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
  T& operator[](unsigned int i) { return mpBegin[i]; }
};

}  // namespace eastl

// Read a virtual-method pointer out of an object's vtable at byte offset n.
template <typename Fn>
static Fn vslot(void* object, unsigned int n) {
  return (Fn)(*(void**)((char*)(*(void**)object) + n));
}

// ---------------------------------------------------------------------------------------------
// Three no-data polymorphic bases (vtables at +0, +4, +8).
class cB0 { public: virtual ~cB0() {} PV(1) PV(2) };
class cB1 { public: virtual ~cB1() {} PV(1) PV(2) };
class cB2 {
 public:
  cB2() : mFieldc(0) {}
  virtual ~cB2() {}
  PV(1) PV(2)
  int mFieldc;
};

// The descriptor reached through cFeedCategory::mpFeedData.
struct FeedDescriptor {
  char pad0[0x74];
  int mFeedId;      // +0x74
};

class cFeedCategory {
 public:
  char pad0[0x6c];
  FeedDescriptor* mpFeedData;  // +0x6c  points at the feed descriptor
};

// The shared 1.0f constant the compiler materialises with movss.
extern const float kRealOne;   // 0x01485720  _HK_REAL_ONE

// KillSeti / editor event helpers used by the feed-selection message.
void __cdecl KillSeti(int hash);                                          // 0x004a88d0
void __cdecl RecordEvent4(unsigned int a, unsigned int b, float c, unsigned int d);  // 0x00435f40

class cUIMissionCard : public cB0, public cB1, public cB2 {
 public:
  cUIMissionCard();
  virtual ~cUIMissionCard();

  AutoRefCount<IWindow> mWindow;            // +0x10
  int mSelectedIndex;                       // +0x14
  float mFloat18;                           // +0x18
  float mFloat1c;                           // +0x1c
  char pad20[0x10];                         // +0x20
  eastl::sp_trivial_vector<int> mVec30;     // +0x30  item UI objects (void*)
  eastl::sp_trivial_vector<int> mVec44;     // +0x44
  eastl::sp_trivial_vector<int> mVec58;     // +0x58
  eastl::sp_ref_vector<AutoRefCount<cFeedCategory> > mVec6c;  // +0x6c
  eastl::sp_trivial_vector<int> mVec80;     // +0x80  per-entry fade weights (float)

  void SetWindowFlag(int value);   // 0x005c9810
  cFeedCategory* GetCurrent();     // 0x005c9830
  bool DoMessage(int messageType, void* message);   // 0x005c9dd0
};

// @ 0x005C9810
void cUIMissionCard::SetWindowFlag(int value) {
  if (mWindow)
    mWindow->SetFlag(1, value);
}

// @ 0x005C9830
cFeedCategory* cUIMissionCard::GetCurrent() {
  int index = mSelectedIndex;
  if (index >= 0 && index < (int)mVec6c.size())
    return mVec6c[index];
  return 0;
}

// @ 0x005C9C70
cUIMissionCard::cUIMissionCard()
    : mSelectedIndex(0), mFloat18(0.0f), mFloat1c(0.0f) {}

// @ 0x005C9D10
cUIMissionCard::~cUIMissionCard() {}

// ---------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------
// cSPPalettePage: the palette model whose item vector drives the page UI.
class cSPPaletteItem;
class cSPPalettePage {
 public:
  char pad0[0x10];
  void* mp0x10;                 // +0x10  (unused here)
  char pad14[0x5c];
  int mCategoryKey;             // +0x60  instance key used for one-click paint items
  char pad64[0x0c];
  float mItemHeight;            // +0x74  (0.0 disables the old item UI path)
  eastl::sp_trivial_vector<void*> mItems;   // +0x70  AutoRefCount<cSPPaletteItem>*
};

// One palette item's data (only the fields these functions touch).
class cSPPaletteItem {
 public:
  char pad0[0x0c];
  void* mpModel;                // +0x0c
  void* mpProperties;           // +0x14
  char pad18[0x0c];
  int   mClassId;               // +0x24  hash-tagged UI class id
};

// Helpers used by the page/feed UI.
void* __cdecl WindowManager();                                 // 0x0067caa0
void* __cdecl PropertyManager();                               // 0x0067de30
unsigned int __cdecl FNVHash(const char* name, unsigned int seed, int len);  // 0x00932e80
int* __cdecl Property_GetUInt();                               // 0x0041ea00
cSPPaletteItem* __cdecl cSPPalettePage_GetItem(cSPPalettePage* self, int index);  // 0x005c7f00
void* __cdecl FUN_00806370(void* window);                      // 0x00806370
void __cdecl SetWindowAreaToParent(void* window);              // 0x00806bf0

void* __cdecl cConnectionDialog_ctor(void* self);              // 0x00810000
extern char gEmptyString16[];                                  // 0x01667bac

// Ref-counted page UI: mData (+0x14), mLayout (+0xc), mWinPage (+0x10),
// mScaleX/mScaleY (+0x18/+0x1c), mOldItemUIs (+0x20), mItemUIs (+0x34).
class cSPPalettePageUI {
 public:
  char pad0[0xc];
  void* mLayout;                // +0x0c
  void* mWinPage;               // +0x10
  void* mData;                  // +0x14
  float mScaleX;                // +0x18
  float mScaleY;                // +0x1c
  eastl::sp_trivial_vector<void*> mOldItemUIs;   // +0x20
  eastl::sp_trivial_vector<void*> mItemUIs;      // +0x34

  bool Init(cSPPalettePage* page, void* parent, int flag, float* rect);
};

// Layout/window helpers.
bool __cdecl cSPUILayout_Init(void* layout, const void* key, bool a, int flags);       // 0x008120d0
bool __cdecl cSPUILayout_SetParentWin(void* layout, void* parent, bool a, int flags);  // 0x008121b0
void* __cdecl cSPUILayout_FindWindowByID(void* layout, int id, int a);                  // 0x008105b0
int __cdecl String_sprintf(void* s, const char* fmt, ...);                              // 0x00472fe0

// Item UI constructors / helpers.
void* __cdecl cSPPaletteItemRollover_ctor();                   // 0x005c7010
void* __cdecl cSPPaletteItemUIPlannerEdit_ctor();              // 0x005ef6b0
void* __cdecl cSPPaletteItemUIDrag_ctor();                     // 0x005ee540
void* __cdecl cSPSwatchPlanner_ctor();                         // 0x005f0d80
void* __cdecl cSPPaletteItemUIOneClickPaint_ctor(unsigned int key);  // 0x005ee7b0
void* __cdecl FUN_00920090(void* prop, void* p1, int a, int b);      // 0x00920090
void* __cdecl cSPOLDPaletteItemUI_Init(void* self, void* item, void* winPage,
                                       int id, int flag);       // 0x005c7500
void* __cdecl cPagePartBig(void* out, int index);               // 0x005c8d70
void* __cdecl FUN_005c8480(void* pos, void* value);             // 0x005c8480
void* __cdecl FUN_005c8c10(void* value);                        // 0x005c8c10
void* __cdecl FUN_005c8c50(void* a, void* b, void* c, void* d); // 0x005c8c50
void* __cdecl cVectorInsertBig(void* pos, void* first, void* last);  // 0x005c90d0

extern int gPaletteClassIds[16];    // 0x0081c74dbc .. table of hash-tagged class ids
extern float kScaleX;               // 0x013f6adc   0.00125f
extern float kScaleY;               // 0x013f8370   0.0016666667f
extern float gPaletteZero;          // 0x013eb1bc

// @ 0x005C9230
// Build the palette page: bind the model, size the layout, then instantiate one
// item UI per model item, dispatching on each item's hash-tagged class id.
bool cSPPalettePageUI::Init(cSPPalettePage* page, void* parent, int flag, float* rect) {
  // Bind the page model (ref-counted assign).
  if (page != (cSPPalettePage*)mData) {
    if (page != 0)
      vslot<void (__thiscall*)(void*)>(page, 4)(page);
    mData = page;
  }

  // Layout scale: explicit rect if given, otherwise derived from the client area.
  if (rect == 0 || rect[10] == -1.0f) {
    void* wm = WindowManager();
    void* inner = vslot<void* (__thiscall*)(void*)>(wm, 4)(wm);
    float* area = (float*)vslot<void* (__thiscall*)(void*)>(inner, 0x34)(inner);
    mScaleX = (area[2] - area[0]) * kScaleX;
    mScaleY = (area[3] - area[1]) * kScaleY;
  } else {
    mScaleX = rect[9];
    mScaleY = rect[10];
  }

  // Fresh layout object, ref-counted into mLayout.
  {
    void* layout = operator new(0x18, "Editor", 0, 0, 0, 0);
    if (layout == 0)
      layout = 0;
    else
      layout = cConnectionDialog_ctor(layout);
    if (layout != mLayout) {
      if (layout != 0)
        vslot<void (__thiscall*)(void*)>(layout, 4)(layout);
      mLayout = layout;
    }
  }

  // The layout key is {instance id, 0x510a95b, 0x40464100}.
  struct LayoutKey {
    int instance;
    int tag1;      // 0x0510a95b
    int tag2;      // 0x40464100
  } key;
  key.instance = (int)page;
  key.tag1 = 0x0510a95b;
  key.tag2 = 0x40464100;

  if (!cSPUILayout_Init(mLayout, &key, true, 0x05b598fa)) {
    // Failure: format a diagnostic into an eastl string and tear it down.
    char* str = gEmptyString16;
    char* end = str;
    String_sprintf(&str, "Failed to initialize palette layout page %x\n", (int)page);
    if (end - str > 1 && str != 0)
      operator delete(str);
    return false;
  }

  cSPUILayout_SetParentWin(mLayout, parent, true, 0x05b598fa);
  void* win = cSPUILayout_FindWindowByID(mLayout, -1, 1);
  if (win != 0)
    SetWindowAreaToParent(win);
  mWinPage = cSPUILayout_FindWindowByID(mLayout, 0x12df7465, 1);

  cSPPalettePage* const model = (cSPPalettePage*)mData;
  const int itemCount = (int)(model->mItems.mpEnd - model->mItems.mpBegin);

  for (int i = 0; i < itemCount; ++i) {
    cSPPaletteItem* const item = cSPPalettePage_GetItem(model, i);
    if (item == 0)
      continue;

    // Look the item's UI class id up through the property manager.
    int* prop = 0;
    {
      void* pm = PropertyManager();
      vslot<void (__thiscall*)(void*, void*, void*, int**)>(pm, 0x2c)(
          pm, item->mpModel, item->mpProperties, &prop);
    }

    float itemHeight = model->mItemHeight;
    if (prop != 0 && itemHeight == 0.0f) {
      unsigned int hash = FNVHash("paletteItemUIClassId", 0x811c9dc5, 1);
      int out = 0;
      if (vslot<bool (__thiscall*)(void*, int, int*)>(prop, 0x24)(prop, hash, &out) &&
          *(uint16_t*)((char*)out + 0x12) == 10) {
        itemHeight = *(float*)Property_GetUInt();
      }
    }

    int classId = item->mClassId;
    unsigned int wantId = 0xffffffff;
    unsigned int paintKey = 0xffffffff;
    // Decode the hash-tagged class id into the constructor selector.
    if (classId == 0x17d37d90 || classId == 0xdee3d8a8) {
      paintKey = model->mCategoryKey;
      wantId = 0xeccc3657;
    } else if (classId == 0x81c74dbc || classId == 0x142462a || classId == 0x8bfac054) {
      wantId = 0x87e8a1af;
    } else if (classId == 0x2b885df4 || classId == 0xfcafd26 || classId == 0x4d863c8b ||
               classId == 0xc9db779b || classId == 0xa2e50993 || classId == 0xe73759f3) {
      wantId = 0;
    } else if (classId == 0x42bf8c1d) {
      wantId = 0xb4e4f69b;
    } else if (classId == 0xbd110a25) {
      paintKey = model->mCategoryKey;
      wantId = 0xeccc3657;
    }

    if (itemHeight == 0.0f && wantId == 0) {
      // Old-style item UI.
      void* ui = operator new(0x20, "Editor", 0, 0, 0, 0);
      if (ui != 0)
        ui = cSPPaletteItemRollover_ctor();
      if (ui != 0)
        vslot<void (__thiscall*)(void*)>(ui, 4)(ui);

      int partId = (int)cPagePartBig(0, i);
      cSPOLDPaletteItemUI_Init(ui, item, mWinPage, partId, (int)rect);

      if (mOldItemUIs.mpEnd < mOldItemUIs.mpCapacity) {
        void** slot = mOldItemUIs.mpEnd++;
        if (slot != 0) {
          *slot = ui;
          if (ui != 0)
            vslot<void (__thiscall*)(void*)>(ui, 4)(ui);
        }
      } else {
        FUN_005c8480(mOldItemUIs.mpEnd, &ui);
      }
      if (ui != 0)
        vslot<void (__thiscall*)(void*)>(ui, 8)(ui);
    } else {
      // Typed item UI.
      void* ui = 0;
      if (itemHeight == 0.0f) {
        if (wantId == 0xb4e4f69b) {
          ui = operator new(0x74, "Editor", 0, 0, 0, 0);
          if (ui != 0)
            ui = cSPPaletteItemUIPlannerEdit_ctor();
        } else if (wantId == 0x71fa7d3f) {
          ui = operator new(0x24, "Editor", 0, 0, 0, 0);
          if (ui != 0)
            ui = cSPPaletteItemUIDrag_ctor();
        } else if (wantId == 0x87e8a1af) {
          ui = operator new(0x6c, "Editor", 0, 0, 0, 0);
          if (ui != 0)
            ui = cSPSwatchPlanner_ctor();
        } else if (wantId == 0xeccc3657) {
          ui = operator new(0x78, "Editor", 0, 0, 0, 0);
          if (ui != 0)
            ui = cSPPaletteItemUIOneClickPaint_ctor(paintKey);
        } else {
          continue;
        }
        FUN_005c8c10(ui);
      } else {
        int propRef = 0;
        FUN_00920090((void*)(int)itemHeight, &propRef, 0, 0);
        FUN_005c8c50((void*)(int)itemHeight, &propRef, 0, 0);
      }
    }
  }

  if (mWinPage != 0)
    vslot<void (__thiscall*)(void*, int, int)>(mWinPage, 0x7c)(mWinPage, 1, 0);

  return true;
}

namespace eastl {
}  // namespace eastl

// ---------------------------------------------------------------------------------------------
// cSPPaletteSubCategoryUI: the scrolling category strip updater.
// Parallel per-entry arrays: item UIs (+0x30), icon handles (+0x44), windows
// (+0x58), category UI objects (+0x6c) and fade weights (+0x80).
class cSPPaletteCategoryUI;
class cSPPaletteSubCategoryUI {
 public:
  char pad0[0x14];
  int   mSelectedIndex;         // +0x14   index of the highlighted entry
  float mStep;                  // +0x18   per-slot offset step
  float mClipHeight;            // +0x1c   denominator for the scroll ratio
  float mTopHidden;             // +0x20
  float mTopVisible;            // +0x24
  float mBottomVisible;         // +0x28
  float mBottomHidden;          // +0x2c
  eastl::sp_trivial_vector<void*> mVec30;    // +0x30  item UI objects
  eastl::sp_trivial_vector<void*> mVec44;    // +0x44  icon handles
  eastl::sp_trivial_vector<void*> mVec58;    // +0x58  window objects
  eastl::sp_trivial_vector<void*> mVec6c;    // +0x6c
  eastl::sp_trivial_vector<float> mVec80;    // +0x80  fade weights

  void Update(unsigned int deltaMs);
};

// Helpers used by the scroll updater.
void FUN_00806c60(float* out, void* frame);                            // 0x00806c60
void FUN_00806ca0(void* window, float x, float y);                     // 0x00806ca0
void FUN_00808190(void* window, float a, float b);                     // 0x00808190
float __cdecl GetAlpha(void* window);                                  // 0x00805040
void __cdecl SetWindowAlpha(void* window, float alpha);                // 0x00804fc0
void __cdecl SetWindowImage(void* window, void* image, int flags);     // 0x00807bb0
void cSPPaletteCategoryUI_Update(cSPPaletteCategoryUI* self, unsigned int dt);  // 0x005c28b0
void cSPPaletteCategoryUI_SetVisibility(cSPPaletteCategoryUI* self, bool visible); // 0x005c2960

extern float kRealZero;   // 0x01485378
extern const float kScrollRate;   // 0x013eb960
extern float kMinRatio;           // 0x013f9428
extern float kHalf;               // 0x01471064
extern void* gPaletteImages[6];   // 0x01516838 .. 0x0151688c

// @ 0x005C98A0
// Per-frame scroll animation: blends each entry toward its target offset and
// fades the strip, then refreshes the per-entry icon.
void cSPPaletteSubCategoryUI::Update(unsigned int deltaMs) {
  // delta = clamp((float)deltaMs * 0.01f, 0.0f, 1.0f)
  float delta = (float)(int)deltaMs * kScrollRate;
  if (delta < 0.0f)
    delta = 0.0f;
  if (delta > kRealOne)
    delta = kRealOne;

  if ((((char*)mVec58.mpEnd - (char*)mVec58.mpBegin) ^
       ((char*)mVec30.mpEnd - (char*)mVec30.mpBegin)) & ~3u) {
    // Array sizes disagree: nothing to animate.
  } else {
    // Pass 1: slide each entry toward its slot, then move it to the lerped point.
    const int count = (int)(mVec30.mpEnd - mVec30.mpBegin);
    for (int i = 0; i < count; ++i) {
      float target;
      if (mSelectedIndex < i)
        target = (mBottomHidden - mTopVisible) - (float)(count - i) * mStep;
      else
        target = (float)i * mStep;

      void* const item = mVec30.mpBegin[i];
      typedef void* (__thiscall *GetObjFn)(void*);
      void* const obj = vslot<GetObjFn>(item, 0x10)(item);

      float point[2];
      FUN_00806c60(point, obj);
      const float x = point[0] - point[0] * delta;
      const float y = point[1] + (target - point[1]) * delta;

      void* const obj2 = vslot<GetObjFn>(item, 0x10)(item);
      typedef void (__thiscall *SetPosFn)(void*, float, float);
      vslot<SetPosFn>(obj2, 0x64)(obj2, x, y);
    }

    // Pass 2: stretch each window between the current and next entry, then fade it.
    const int wcount = (int)(mVec58.mpEnd - mVec58.mpBegin);
    for (int i = 0; i < wcount; ++i) {
      typedef void* (__thiscall *GetObjFn)(void*);
      typedef void* (__thiscall *GetBoxFn)(void*);
      void* const item = mVec30.mpBegin[i];
      void* const obj = vslot<GetObjFn>(item, 0x10)(item);
      const float top = *(float*)((char*)vslot<GetBoxFn>(obj, 0x38)(obj) + 0xc);
      const float mid = mBottomVisible - mTopHidden;

      float bottom;
      if (i == (int)(mVec30.mpEnd - mVec30.mpBegin) - 1) {
        bottom = mBottomHidden - mTopVisible;
      } else {
        void* const nitem = mVec30.mpBegin[i + 1];
        void* const nobj = vslot<GetObjFn>(nitem, 0x10)(nitem);
        bottom = *(float*)((char*)vslot<GetBoxFn>(nobj, 0x38)(nobj) + 4);
      }

      void* const window = mVec58.mpBegin[i];
      FUN_00806ca0(window, mid * kHalf, (bottom + top) * kHalf);

      float ratio = (bottom - top) / mClipHeight;
      if (ratio == 0.0f)
        ratio = kMinRatio;
      FUN_00808190(window, kRealOne, ratio);

      float alpha = GetAlpha(window);
      float weight = mVec80.mpBegin[i];
      if (weight != kRealOne)
        weight = (weight - alpha) * delta * kHalf + alpha;
      SetWindowAlpha(window, weight);
      cSPPaletteCategoryUI_SetVisibility((cSPPaletteCategoryUI*)mVec6c.mpBegin[i],
                                         ratio > kScrollRate);
    }
  }

  // Refresh every category UI.
  const int ccount = (int)(mVec6c.mpEnd - mVec6c.mpBegin);
  for (int i = 0; i < ccount; ++i)
    cSPPaletteCategoryUI_Update((cSPPaletteCategoryUI*)mVec6c.mpBegin[i], deltaMs);

  // Pick each entry's icon from its state flags and push it to the window.
  const int icount = (int)(mVec30.mpEnd - mVec30.mpBegin);
  for (int i = 0; i < icount; ++i) {
    void* const item = mVec30.mpBegin[i];
    typedef unsigned (__thiscall *GetFlagsFn)(void*);
    const unsigned flags = vslot<GetFlagsFn>(item, 0x20)(item);
    void* image;
    if (flags & 4) {
      if (flags & 2)
        image = gPaletteImages[4];
      else if (flags & 8)
        image = gPaletteImages[3];
      else
        image = gPaletteImages[2];
    } else {
      if (flags & 2)
        image = gPaletteImages[1];
      else if (flags & 8)
        image = gPaletteImages[0];
      else
        image = gPaletteImages[2];
    }
    SetWindowImage(mVec44.mpBegin[i], image, -1);
  }
}

// @ 0x005C9DD0
// Message 0x287259f6 carries the feed index to select. Everything else is a no-op.
void* __cdecl MessageServer();                                       // 0x0067dcc0
void __cdecl SlotMessage_Destruct(void* p);                          // 0x00421cf0

// Stack-allocated override-message envelope: a vtable pointer, an id word and a
// payload word; the server dispatches it then the envelope is torn down.
struct MessageBasicRC5 {
  void* mpVftable;      // +0x00   0x013eb844
  void* mpVftable2;     // +0x04   0x013eb90c (transient)
  int   mPayload;       // +0x08
  int   pad0c;          // +0x0c
  int   mId;            // +0x10   0x07956d8a
};

bool cUIMissionCard::DoMessage(int messageType, void* message) {
  (void)messageType;
  const int* const msg = (const int*)message;
  if (msg[2] != 0x287259f6)
    return false;

  const int index = msg[3];
  if (index < 0 || index >= (int)(mVec30.mpEnd - mVec30.mpBegin))
    return false;

  // Move the highlight: clear the old entry's fade weight and set the new one to 1.
  const int prevIndex = mSelectedIndex;
  mSelectedIndex = index;
  ((float*)mVec80.mpBegin)[prevIndex] = 0.0f;
  ((float*)mVec80.mpBegin)[mSelectedIndex] = kRealOne;

  KillSeti(0x38eb66f8);
  RecordEvent4(0x1d6253c0, 0x3597e2da, (float)(index + 100), 0);

  const int count = (int)(mVec30.mpEnd - mVec30.mpBegin);
  for (int i = 0; i < count; ++i) {
    void* const item = (void*)mVec30.mpBegin[i];
    typedef void (__thiscall *SetSelFn)(void*, int, int);
    vslot<SetSelFn>(item, 0x28)(item, 4, mSelectedIndex == i ? 1 : 0);
  }

  MessageBasicRC5 envelope;
  envelope.mpVftable2 = (void*)0x013eb90c;   // RefBaseA22 vtable
  envelope.mPayload = 0;
  envelope.mpVftable = (void*)0x013eb844;    // PTR_FUN_013eb844
  envelope.pad0c = 0;
  envelope.mId = 0x07956d8a;

  cFeedCategory* category;
  if (mSelectedIndex < 0 || (int)(mVec6c.mpEnd - mVec6c.mpBegin) <= mSelectedIndex)
    category = 0;
  else
    category = mVec6c.mpBegin[mSelectedIndex];

  envelope.mPayload = category->mpFeedData->mFeedId;

  void** const server = (void**)MessageServer();
  typedef void (__thiscall *DispatchFn)(void*, int, void*);
  (*(DispatchFn*)(server[0x14 / 4]))(server, 0x07956d8a, &envelope);
  SlotMessage_Destruct(&envelope.mpVftable);

  return false;
}
