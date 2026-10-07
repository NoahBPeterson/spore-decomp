// Slice s005c53c0 -- SP::cSPPalette / SP::cSPPaletteCategoryUI methods (Spore UI)
// Flags for this region: /O2 /MD /Gy /TP (no /arch:SSE; floats copy via fld/fstp)
#include "types.h"

void* operator new(unsigned int size, const char* name, int, int, int, int);
void EAFreeArray(void* p);  // operator delete[] (0x00f47380), cdecl

namespace SP {

// Ref-counted objects: the COM-like IUnknown32 subobject has AddRef at vtable+4, Release at vtable+8.
class cSPPaletteCategory;
class cSPPalettePage;
class cSPPaletteItem;

struct Key {
  uint32_t mInstance;
  uint32_t mType;
  uint32_t mGroup;
};

// Property object released through vtable slot 1.
struct IProp {
  virtual void v0();
  virtual int Release();
};

struct IPropertyManager {
  virtual void v0();  // slots 0..10
  virtual void v1();
  virtual void v2();
  virtual void v3();
  virtual void v4();
  virtual void v5();
  virtual void v6();
  virtual void v7();
  virtual void v8();
  virtual void v9();
  virtual void v10();
  virtual bool GetProperty(uint32_t inst, uint32_t group, IProp** out);  // slot 11 (+0x2c)
};

IPropertyManager* PropertyManager();                                           // 0x0067de30
bool GetPropertyArray(IProp* prop, uint32_t id, int* count, Key** data);       // 0x006a0ae0 (cdecl)
void GetPropertyAsKey(IProp* prop, uint32_t id, Key* out);                     // 0x006a1250 (cdecl)

class cSPPaletteItem {
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
  cSPPaletteItem();  // 0x005c66a0
  void Init(Key* key, int region, uint32_t thumbGroup);  // 0x005c6810
};

class cSPPalettePage {
 public:
  virtual void v0();
  virtual int AddRef();
  virtual int Release();
  char pad4[0x58];
  int m5c;       // +0x5c
  uint32_t m60;  // +0x60
  Key mCategoryKey;  // +0x64
  cSPPaletteItem** mItemsBegin;  // +0x70
  cSPPaletteItem** mItemsEnd;    // +0x74
  char pad78[0xc];
  cSPPalettePage();  // 0x005c7f50
  bool Init(Key* key, uint32_t a, uint32_t b, uint32_t c, uint32_t d);  // 0x005c8ad0
  cSPPaletteItem* GetItem(int i);                                        // 0x005c7f00
};

class cSPPaletteCategory {
 public:
  virtual void v0();
  virtual int AddRef();
  virtual int Release();
  char pad4[0x8];
  cSPPalettePage** mPagesBegin;  // +0xc
  cSPPalettePage** mPagesEnd;    // +0x10
  char pad14[0x20];
  cSPPaletteCategory** mSubBegin;  // +0x34
  cSPPaletteCategory** mSubEnd;    // +0x38
  char pad3c[0xc];
  uint32_t mRegionFilter;  // +0x48
  uint32_t mSortKey;       // +0x4c
  char pad50[4];
  uint32_t mNameLocal;  // +0x54
  uint32_t mNameSrc;    // +0x58
  char pad5c[0x18];
  int mId;  // +0x74
  char pad78[0x18];
  cSPPaletteCategory();                                       // 0x005c2020
  void Init(Key* key, uint32_t group);                        // 0x005c1e20
  void Shutdown();                                            // 0x005c2230
  cSPPaletteCategory* FindSubCategory(int id);                // 0x005c1d70
  bool HasSubCategory(cSPPaletteCategory* c);                 // 0x005c1d40
  void AddSubCategory(cSPPaletteCategory* c);                 // 0x005c22b0
  void AddPage(cSPPalettePage* p);                            // 0x005c2390
  cSPPalettePage* GetPage(int i);                             // 0x005c1ce0
};

struct AppGlobals3 {
  char pad[0x118];
  int mFlag;
};
struct AppGlobals {
  char pad[0x3c];
  AppGlobals3* mSub;
};
extern AppGlobals* gApp;  // 0x015fd918

template <class T>
struct RCRef {
  T* p;
  RCRef(T* q) : p(q) { if (p) p->AddRef(); }
  ~RCRef() { if (p) p->Release(); }
};

struct IRC {
  virtual void v0();
  virtual int AddRef();
  virtual int Release();
};

// EA::RefCountVTemplate<int>, vtable 0x013ec458: dtor, AddRef, Release, GetReferenceCount.
class RefCountVTemplate {
 public:
  RefCountVTemplate() { mRefCount = 0; }
  virtual ~RefCountVTemplate() {}
  virtual int AddRef();             // 0x005454f0
  virtual int Release();            // 0x00453540
  virtual int GetReferenceCount();  // 0x004535b0
  int mRefCount;
};
// Interface base at +8, vtable 0x013eb938: AddRef = 0, Release = 0, dtor.
class IUnknown32 {
 public:
  virtual int AddRef() = 0;
  virtual int Release() = 0;
  virtual ~IUnknown32() {}
};

struct CatVector {
  cSPPaletteCategory** mBegin;
  cSPPaletteCategory** mEnd;
  cSPPaletteCategory** mCap;
  CatVector() : mBegin(0), mEnd(0), mCap(0) {}
  ~CatVector();  // 0x005c7f10, out of line
  void InsertAux(cSPPaletteCategory** pos, cSPPaletteCategory** val);  // 0x005c8480
};

class cSPPalette : public RefCountVTemplate, public IUnknown32 {
 public:
  CatVector mCats;  // +0xc, eastl::vector<AutoRefCount<cSPPaletteCategory>>
  char pad18[8];
  uint32_t m20;  // +0x20
  uint32_t m24;  // +0x24
  uint32_t m28;  // +0x28
  uint32_t m2c;  // +0x2c
  uint32_t m30;  // +0x30
  uint32_t m34;  // +0x34
  int m38;       // +0x38
  int m3c;       // +0x3c

  cSPPalette();
  ~cSPPalette();
  virtual int AddRef();   // 0x00804910
  virtual int Release();  // 0x00834200
  void ShutdownChildren();                                   // 0x005c5c20
  __declspec(noinline) int CountItems(cSPPalettePage* page, int* pOut);           // 0x005c5c50
  __declspec(noinline) bool AllItemsListed(cSPPalettePage* page, cSPPaletteCategory* cat);  // 0x005c5cc0
  __declspec(noinline) cSPPaletteCategory* FindCategory(int id);                  // 0x005c5df0
  __declspec(noinline) void AddCategory(cSPPaletteCategory* cat);                 // 0x005c5f00
  void LoadDefinitionPart(Key* key);                         // 0x005c6010
};

// @ 0x005c5c20
void cSPPalette::ShutdownChildren() {
  int count = (int)(mCats.mEnd - mCats.mBegin);
  for (int i = 0; i < count; i++)
    mCats.mBegin[i]->Shutdown();
}

// @ 0x005c5c50
int cSPPalette::CountItems(cSPPalettePage* page, int* pOut) {
  int n = (int)(page->mItemsEnd - page->mItemsBegin);
  int total = 0;
  int unassigned = 0;
  for (int i = 0; i < n; i++) {
    cSPPaletteItem* item = page->GetItem(i);
    if (item) {
      total++;
      if (item->mRegion == -1)
        unassigned++;
      else
        total++;
    }
  }
  *pOut = unassigned;
  return total;
}

// @ 0x005c5cc0
bool cSPPalette::AllItemsListed(cSPPalettePage* page, cSPPaletteCategory* cat) {
  int nItems = (int)(page->mItemsEnd - page->mItemsBegin);
  int nPages = (int)(cat->mPagesEnd - cat->mPagesBegin);
  int seen = 0;
  int fixed = 0;
  for (int i = 0; i < nItems; i++) {
    cSPPaletteItem* item = page->GetItem(i);
    if (!item)
      continue;
    seen++;
    Key* ik = &item->mItemKey;
    for (int j = 0; j < nPages; j++) {
      cSPPalettePage* other = cat->GetPage(j);
      if (other->m5c == 1) {
        int nOther = (int)(other->mItemsEnd - other->mItemsBegin);
        for (int k = 0; k < nOther; k++) {
          cSPPaletteItem* o = other->GetItem(k);
          if (o && o->mItemKey.mInstance == ik->mInstance &&
              o->mItemKey.mType == ik->mType &&
              o->mItemKey.mGroup == ik->mGroup) {
            item->Init(ik, -1, item->mThumbKey_Group);
            fixed++;
            goto nextItem;
          }
        }
      }
    }
  nextItem:;
  }
  return fixed == seen;
}

// @ 0x005c5df0
cSPPaletteCategory* cSPPalette::FindCategory(int id) {
  cSPPaletteCategory** end = mCats.mEnd;
  for (cSPPaletteCategory** it = mCats.mBegin; it != end; ++it) {
    cSPPaletteCategory* c = *it;
    if (c->mId == id)
      return c;
    cSPPaletteCategory* r = c->FindSubCategory(id);
    if (r)
      return r;
  }
  return 0;
}

// @ 0x005c5e30
cSPPalette::cSPPalette() {
  m24 = 0;
  m28 = 0;
  m2c = 0;
  m30 = 0;
  m34 = 0;
  m20 = 0x8511b8a;
  m38 = -1;
  m3c = -1;
}

// @ 0x005c5e90
cSPPalette::~cSPPalette() {
  ShutdownChildren();
}

// @ 0x005c5f00
void cSPPalette::AddCategory(cSPPaletteCategory* cat) {
  if (!cat)
    return;
  uint32_t key = cat->mSortKey;
  cSPPaletteCategory** end = mCats.mEnd;
  for (cSPPaletteCategory** it = mCats.mBegin; it != end; ++it) {
    cSPPaletteCategory* cur = *it;
    if (cur)
      cur->AddRef();
    if (cur->mSortKey > key) {
      cSPPaletteCategory* tmp = cat;
      cat->AddRef();
      CatVector* v = &mCats;
      if (it == v->mEnd && v->mEnd != v->mCap) {
        cSPPaletteCategory** slot = v->mEnd++;
        if (slot) {
          *slot = cat;
          cat->AddRef();
        }
      } else {
        v->InsertAux(it, &tmp);
      }
      if (tmp)
        tmp->Release();
      cur->Release();
      return;
    }
    cur->Release();
  }
  CatVector* v = &mCats;
  cSPPaletteCategory* tmp = cat;
  cat->AddRef();
  if (v->mEnd < v->mCap) {
    cSPPaletteCategory** slot = v->mEnd++;
    if (slot) {
      *slot = cat;
      cat->AddRef();
    }
  } else {
    v->InsertAux(v->mEnd, &tmp);
    cat = tmp;
  }
  if (cat)
    cat->Release();
}

// @ 0x005c6010
void cSPPalette::LoadDefinitionPart(Key* defKey) {
  IProp* prop = 0;
  IPropertyManager* pm = PropertyManager();
  if (prop) {
    IProp* t = prop;
    prop = 0;
    t->Release();
  }
  pm->GetProperty(defKey->mInstance, defKey->mGroup, &prop);
  if (!prop)
    return;

  int count = 0;
  Key* data;
  GetPropertyArray(prop, 0xf21e733c, &count, &data);
  for (int i = 0; i < count; i++) {
    Key* k = data + i;
    cSPPalettePage* page;
    page = new ("Editor", 0, 0, 0, 0) cSPPalettePage();
    if (page)
      page->AddRef();
    if (!page->Init(k, m30, m34, m28, m2c)) {
      if (page)
        page->Release();
      continue;
    }
    Key catKey = page->mCategoryKey;
    Key parentKey = {0, 0, 0};
    IProp* p2 = 0;
    pm = PropertyManager();
    if (p2) {
      IProp* t = p2;
      p2 = 0;
      t->Release();
    }
    if (pm->GetProperty(catKey.mInstance, catKey.mGroup, &p2))
      GetPropertyAsKey(p2, 0xb35d7835, &parentKey);

    cSPPaletteCategory* parent = 0;
    cSPPaletteCategory* cat = 0;
    cSPPaletteCategory* f = FindCategory(catKey.mInstance);
    if (f) {
      f->AddRef();
      cat = f;
    }
    if (parentKey.mInstance) {
      cSPPaletteCategory* pf = FindCategory(parentKey.mInstance);
      if (pf) {
        pf->AddRef();
        parent = pf;
      } else {
        cSPPaletteCategory* n = new ("Editor", 0, 0, 0, 0) cSPPaletteCategory();
        if (n) {
          n->AddRef();
          parent = n;
          n->Init(&parentKey, m24);
          AddCategory(n);
        }
      }
    }
    if (!cat) {
      cSPPaletteCategory* n = new ("Editor", 0, 0, 0, 0) cSPPaletteCategory();
      if (n) {
        n->AddRef();
        n->Init(&catKey, m24);
        cat = n;
        if (!parent)
          AddCategory(n);
      }
    }
    if (parent) {
      if (!parent->HasSubCategory(cat))
        parent->AddSubCategory(cat);
    }
    if (cat) {
      bool skip = false;
      if (gApp->mSub->mFlag != 0 && (((char*)cat->mPagesEnd - (char*)cat->mPagesBegin) & ~3) != 0 &&
          AllItemsListed(page, cat)) {
        int n;
        int c = CountItems(page, &n);
        if (c == n)
          skip = true;
      }
      if (!skip)
        cat->AddPage((cSPPalettePage*)page);
    }
    if (parent)
      parent->Release();
    if (cat)
      cat->Release();
    if (p2)
      p2->Release();
    page->Release();
  }
  if (prop)
    prop->Release();
}

// ---- cSPPaletteCategoryUI::Init -------------------------------------------------------------
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

struct cSPUILayout {
  virtual void v0();
  virtual int AddRef();
  virtual int Release();
  char pad4[0x14];
  cSPUILayout();                                                       // 0x00810000
  bool Init(Key* key, int a, uint32_t b);                              // 0x008120d0
  void SetParentWin(IWindow* parent, int a, uint32_t b);               // 0x008121b0
  IWindow* FindWindowByID(uint32_t id, int a);                         // 0x008105b0
};

struct cSPEditorPageControls {
  virtual int AddRef();
  virtual int Release();
  char pad8[0x20];
  cSPEditorPageControls();                  // 0x005c0770
  void Init(IWindow* w, void* owner);       // 0x005c0840
  void SetFlag(int f);                      // 0x00ed0260
};

struct cSPEditorColorPicker {
  virtual void v0();
  virtual int AddRef();
  virtual int Release();
  char pad4[0x4c];
  cSPEditorColorPicker();                                                  // 0x005a5a50
  void Init(IWindow* w, uint32_t id, uint32_t nameKey, int z);             // 0x005a5ec0
  void SetFlag(int f);                                                     // 0x005a4200
};

struct RCSub {
  virtual int AddRef();
  virtual int Release();
};

struct cSPEditorPaintLikeThis {
  virtual void v0();
  virtual void Init(cSPPaletteItem* item, IWindow* w, int z, uint32_t arg);
  char pad8[4];
  RCSub sub;  // +0xc
  char pad10[0xd8];
  cSPEditorPaintLikeThis(uint32_t v);  // 0x005c0f40
};

struct cSPSwatch {
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
struct cSPSwatchManager {
  cSPSwatch* CreateSwatch();  // 0x005f0ca0
};
cSPSwatchManager* __stdcall GetSwatchManager(int a);  // 0x00401020

struct cSPPaletteSubCategoryUI {
  virtual int AddRef();
  virtual int Release();
  char pad8[0x8c];
  cSPPaletteSubCategoryUI();                                                 // 0x005c9c70
  void Init(IWindow* w, cSPPaletteCategory* cat, uint32_t arg);              // 0x005ca070
  void SetWindowFlag(int f);                                                 // 0x005c9810
};

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

struct PackButton {
  void* mButton;
  bool mEnabled;
  char pad[3];
};

struct PLTVec {
  cSPEditorPaintLikeThis** mBegin;
  cSPEditorPaintLikeThis** mEnd;
  cSPEditorPaintLikeThis** mCap;
  void InsertAux(cSPEditorPaintLikeThis** pos, cSPEditorPaintLikeThis** val);  // 0x005c90d0
};

struct AutoHandler {
  IMessageServer* mServer;  // +0xb4
  void* mHandler;           // +0xb8
  const uint32_t* mIds;     // +0xbc
  int mCount;               // +0xc0
  int mPriority;            // +0xc4
};

extern const uint32_t gPaletteMsgIds[2];  // 0x013f7f6c
IMessageServer* MessageServer();          // 0x0067dcc0
void SetWindowAreaToParent(IWindow* w);  // 0x00806bf0, cdecl
extern uint32_t gSwatchDefault;           // 0x015150a4

class cSPPaletteCategoryUI {
 public:
  char pad0[0x10];
  ARC<cSPUILayout> mLayout;                // +0x10
  char pad14[4];
  ARC<IWindow> mWinCategory;               // +0x18
  ARC<IWindow> mWinPageButtons;            // +0x1c
  ARC<IWindow> mWinEPUIHolder;             // +0x20
  ARC<IWindow> mWinColorPickerHolder;      // +0x24
  ARC<IWindow> mWinPalettePage;            // +0x28
  ARC<IWindow> mWinFullPalettePage;        // +0x2c
  ARC<cSPEditorColorPicker> mColorPicker1; // +0x30
  ARC<cSPEditorColorPicker> mColorPicker2; // +0x34
  float mArea1[4];                         // +0x38
  float mArea2[4];                         // +0x48
  float mAreaUnion[4];                     // +0x58
  ARC<cSPSwatch> mPreviewSwatch;           // +0x68
  cSPPaletteCategory* mData;               // +0x6c
  ARC<cSPEditorPageControls> mPageControls;  // +0x70
  char pad74[0x14];
  PackButton* mPackBegin;                  // +0x88
  PackButton* mPackEnd;                    // +0x8c
  char pad90[0xc];
  ARC<cSPPaletteSubCategoryUI> mSubCategoryUI;  // +0x9c
  int mExpansionPackChunkIndex;            // +0xa0
  char pada4[0xc];  // +0xa4
  int mExpansionPacksPerPage;              // +0xb0
  AutoHandler mAutoMsgHandler;             // +0xb4
  char padc8[0x20];
  PLTVec mPaintLike;                       // +0xe8

  void Init(cSPPaletteCategory* data, IWindow* parent, uint32_t arg3);   // 0x005c53c0
  void SetData(cSPPaletteCategory* data, uint32_t arg3);                 // 0x005c51e0
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

// @ 0x005c53c0
void cSPPaletteCategoryUI::Init(cSPPaletteCategory* data, IWindow* parent, uint32_t arg3) {
  mLayout = new ("Editor", 0, 0, 0, 0) cSPUILayout();
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
      mPageControls = new ("Editor", 0, 0, 0, 0) cSPEditorPageControls();
      mPageControls.mp->Init(pageButtons, this);
      mPageControls.mp->SetFlag(1);
    }
    IWindow* picker1 = mLayout.mp->FindWindowByID(0x3304221b, 1);
    if (picker1) {
      uint32_t nameKey = mData->mNameLocal;
      if (nameKey == 0xffffffff)
        nameKey = mData->mNameSrc;
      mColorPicker1 = new ("Editor", 0, 0, 0, 0) cSPEditorColorPicker();
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
      mColorPicker2 = new ("Editor", 0, 0, 0, 0) cSPEditorColorPicker();
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
      cSPEditorPaintLikeThis* plt = new ("Editor", 0, 0, 0, 0) cSPEditorPaintLikeThis(v);
      cSPEditorPaintLikeThis* tmp = plt;
      if (plt)
        plt->sub.AddRef();
      cSPPaletteItem* item = new ("Editor", 0, 0, 0, 0) cSPPaletteItem();
      if (item)
        item->AddRef();
      Key itemKey;
      itemKey.mInstance = 0x32f652ad;
      itemKey.mType = 0;
      itemKey.mGroup = 0x406a0200;
      item->Init(&itemKey, 0, 0);
      plt->Init(item, w, 0, arg3);
      if (mPaintLike.mEnd < mPaintLike.mCap) {
        cSPEditorPaintLikeThis** slot = mPaintLike.mEnd++;
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

    IMessageServer* server = MessageServer();
    mAutoMsgHandler.mServer = server;
    mAutoMsgHandler.mHandler = this;
    mAutoMsgHandler.mIds = gPaletteMsgIds;
    mAutoMsgHandler.mCount = 2;
    mAutoMsgHandler.mPriority = 0;
    if (server) {
      for (int i = 0; i < 2; i++)
        server->AddHandler(this, gPaletteMsgIds[i]);
    }

    IWindow* subWin = mLayout.mp->FindWindowByID(0x1357f0c2, 1);
    if (subWin && (((char*)mData->mSubEnd - (char*)mData->mSubBegin) & ~3) != 0) {
      mSubCategoryUI = new ("Editor", 0, 0, 0, 0) cSPPaletteSubCategoryUI();
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

void EmitDtor(cSPPalette* p) { p->~cSPPalette(); }

}  // namespace SP
