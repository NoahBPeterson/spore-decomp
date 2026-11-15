// Slice s0062e7e0: SP::cSPPlayModeAnimation (panel/anim info loading, page navigation) and
// SP::cSPPlayModeBGMgr (background hilite). Retail layouts, raw offsets where the PDB differs.
#include "types.h"

struct ResourceKey;

class cString {
 public:
  uint32_t mData[5];
  cString();
  ~cString();
  void Load(uint32_t table, uint32_t group, const wchar_t* def);
  const wchar_t* c_str();
};

struct RefCountVTemplate {
  int mRefCount;
  RefCountVTemplate() : mRefCount(0) {}
  virtual ~RefCountVTemplate() {}
  virtual int AddRef() { return ++mRefCount; }
  virtual int Release();
};

struct IWindow {
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
  virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
  virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
  virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
  virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
  virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
  virtual void v30();
  virtual void SetFlag(int flag, bool value);          // +0x7c
  virtual void SetCaption(const wchar_t* text);        // +0x80
};

struct RefObj {                       // generic intrusive refcounted object (AddRef +4, Release +8)
  virtual void v0();
  virtual void AddRef();
  virtual void Release();
};

struct UITooltip {
  void SetText(const wchar_t* text, int a, int b);    // cSPUITooltipWinProc::SetText
};

struct cSPPlayModeUI {
  IWindow* FindPlayModeUIWindow(uint32_t id);
  void SetUIGroupVisible(uint32_t group, bool visible);
  bool IsUIGroupEnabled(uint32_t group);
  void SetAnimButtonsEnabled(bool enabled);
  void SetExpansionAnimButtonsEnabled(bool enabled);
};

struct GlobalPageInfo { uint32_t pad[8]; uint32_t page; uint32_t pageCount; };  // +0x20, +0x24
extern GlobalPageInfo* gPageInfo;          // 0x015f7cf4

// ---------------------------------------------------------------------------------------------
// cSPPlayModeAnimPanelInfo (vtable 0x013fe378): refcounted, owns a vector of load infos at +0x14
class cSPPlayModeAnimLoadInfo;
struct LoadInfoVector {
  cSPPlayModeAnimLoadInfo** mpBegin;
  cSPPlayModeAnimLoadInfo** mpEnd;
  cSPPlayModeAnimLoadInfo** mpCapacity;
  uint32_t mAllocator;
  LoadInfoVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~LoadInfoVector();     // out of line (0x005c7f10)
  void DoInsertValue(cSPPlayModeAnimLoadInfo** pos, cSPPlayModeAnimLoadInfo* const& v);   // 0x005c8480
};

class cSPPlayModeAnimPanelInfo : public RefCountVTemplate {
 public:
  uint32_t mOrder;                  // +0x08
  uint32_t mIconID;                 // +0x0c
  uint32_t mIconShadowID;           // +0x10
  LoadInfoVector mAnimLoadInfo;     // +0x14
  uint32_t mPad24;                  // +0x24
  virtual ~cSPPlayModeAnimPanelInfo();
};

// @ 0x0062ebb0
cSPPlayModeAnimPanelInfo::~cSPPlayModeAnimPanelInfo() {}

// ---------------------------------------------------------------------------------------------
struct PanelVector {
  cSPPlayModeAnimPanelInfo** mpBegin;
  cSPPlayModeAnimPanelInfo** mpEnd;
  cSPPlayModeAnimPanelInfo** mpCapacity;
  uint32_t mAllocator;
  void DoInsertValue(cSPPlayModeAnimPanelInfo** pos, cSPPlayModeAnimPanelInfo* const& v);   // 0x005c8480
  void Insert(cSPPlayModeAnimPanelInfo** pos, cSPPlayModeAnimPanelInfo* const& v);          // 0x005c21d0
};

class cSPPlayModeAnimation {
 public:
  void* vftable;
  void* mEditorBase;             // +0x04
  uint32_t mCurrAnimID;          // +0x08
  PanelVector mAnimPanelInfo;    // +0x0c
  uint32_t pad1c;                // +0x1c
  uint32_t mPageCount;           // +0x20
  uint32_t mNumPages;            // +0x24
  cSPPlayModeUI* mUI;            // +0x28
  UITooltip* pTooltip[24];       // +0x2c

  int GetAnimCount();
  void UpdateButtonImages();
  void UpdatePageCount();
  void NextAnimWindowSet();
  void PreviousAnimWindowSet();
  void LoadAllAnimInfo();
  void LoadPanelInfo(const ResourceKey& key);
  void LoadAnimInfo(cSPPlayModeAnimPanelInfo* panel, ResourceKey* key);
  void Init(void* editorBase, cSPPlayModeUI* ui);
};

// ---- resource manager access for LoadAllAnimInfo ----
struct ResourceKey { uint32_t instanceID, typeID, groupID; };
struct KeyVector {
  ResourceKey* mpBegin;
  ResourceKey* mpEnd;
  ResourceKey* mpCapacity;
  ~KeyVector() { if (mpBegin && ((int*)mpBegin)[-1] != 0) operator delete(mpBegin); }
};
struct KeyFilter {
  virtual void v0();
  int a, b, c, d;
  KeyFilter() {}
};
struct IResourceManager {
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
  virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
  virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
  virtual int GetKeys(KeyVector* out, KeyFilter* filter, int flags);   // +0x38
};
IResourceManager* GetResourceManager();      // 0x008de1a0
extern int gResourceTypeFilter;              // 0x01522db0
void operator delete(void* p);


// @ 0x0062f1e0 (PDB candidate LoadAllAnimInfoFromGroup)
void cSPPlayModeAnimation::LoadAllAnimInfo() {
  IResourceManager* rm = GetResourceManager();
  KeyVector keys;
  keys.mpBegin = 0;
  keys.mpEnd = 0;
  keys.mpCapacity = 0;
  KeyFilter filter;
  filter.a = -1;
  filter.b = gResourceTypeFilter;
  filter.c = 0xb1b104;
  filter.d = -1;
  rm->GetKeys(&keys, &filter, 0);
  for (ResourceKey* k = keys.mpBegin; k != keys.mpEnd; k++) {
    ResourceKey key = *k;
    LoadPanelInfo(key);
  }
}

// @ 0x0062f2a0 (PDB candidate Init)
void cSPPlayModeAnimation::Init(void* editorBase, cSPPlayModeUI* ui) {
  mUI = ui;
  mEditorBase = editorBase;
  mCurrAnimID = 0xffffffff;
  LoadAllAnimInfo();
  uint32_t n = (uint32_t)(mAnimPanelInfo.mpEnd - mAnimPanelInfo.mpBegin) >> 2;
  uint32_t pages = n + 1;
  mNumPages = pages;
  if (((char*)mAnimPanelInfo.mpEnd - (char*)mAnimPanelInfo.mpBegin) & 0xc) {
    pages++;
    mNumPages = pages;
  }
}

// @ 0x0062ebe0
void cSPPlayModeAnimation::NextAnimWindowSet() {
  uint32_t* pc = &mPageCount;
  *pc = *pc + 1;
  if (*pc != 0) mUI->SetUIGroupVisible(0x4864e80, true);
  mUI->SetAnimButtonsEnabled(false);
  if (!mUI->IsUIGroupEnabled(0x48666b8)) mUI->SetExpansionAnimButtonsEnabled(true);
  UpdateButtonImages();
  UpdatePageCount();
}

// @ 0x0062ec30
void cSPPlayModeAnimation::PreviousAnimWindowSet() {
  uint32_t* pc = &mPageCount;
  *pc = *pc - 1;
  if (*pc == 0) {
    if (GetAnimCount() != 0) {
      mUI->SetUIGroupVisible(0x4864e80, false);
      mUI->SetUIGroupVisible(0x4864e88, true);
      mUI->SetAnimButtonsEnabled(true);
      mUI->SetExpansionAnimButtonsEnabled(false);
    }
  }
  UpdateButtonImages();
  UpdatePageCount();
}

// ---------------------------------------------------------------------------------------------
// cSPPlayModeBGMgr (retail layout: mUI moved to +0x34)
struct BGInfoVector { void** mpBegin; void** mpEnd; void** mpCapacity; uint32_t mAllocator; };
struct BGInfo { uint32_t pad[2]; uint32_t mEffectID; uint32_t pad2; uint32_t mType; uint32_t mLightID; };   // +8, +0x10, +0x14

struct FxObj {
  int FUN_0045b210();
  void FUN_0045b150();
  void FUN_0045ae10(int v);
};
FxObj* __stdcall FUN_00401050(uint32_t id);
struct ILightingWorld {
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
  virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
  virtual void v10(); virtual void v11();
  virtual void SetLighting(uint32_t id);      // +0x30
};

class cSPPlayModeBGMgr {
 public:
  void* vftable;                   // +0x00
  BGInfoVector mBackGroundInfo;    // +0x04
  uint32_t pad14;                  // +0x14
  uint32_t mCurrThumbnailNum;      // +0x18
  uint32_t mCurrBkgEffectID;       // +0x1c
  uint32_t mLastBkgEffectID;       // +0x20
  uint32_t mCrossFadeEffectID;     // +0x24
  uint32_t mEntryEffectID;         // +0x28
  uint32_t pad2c;                  // +0x2c
  bool mChangingEnvironment;       // +0x30
  uint8_t pad31[3];
  cSPPlayModeUI* mUI;              // +0x34
  uint32_t mPageCount;             // +0x38
  uint32_t mCurrentPage;           // +0x3c
  ILightingWorld* mLightingWorld;  // +0x40
  bool mbChangeInitiated;          // +0x44

  void SetBGHilite(uint32_t id);
  void UpdateBGHilite();
  void UpdateBGCountText();
  void FUN_0062f2f0();
  void FUN_0062f5c0();
  void FUN_0062f610();
  bool FUN_0062f6c0();
};

// @ 0x0062f340
void cSPPlayModeBGMgr::SetBGHilite(uint32_t id) {
  switch (id) {
    case 0x445b018:
      mUI->SetUIGroupVisible(0x459b0f0, true);
      mUI->SetUIGroupVisible(0x459b298, false);
      mUI->SetUIGroupVisible(0x459b2d8, false);
      mUI->SetUIGroupVisible(0x459b348, false);
      break;
    case 0x445b318:
      mUI->SetUIGroupVisible(0x459b0f0, false);
      mUI->SetUIGroupVisible(0x459b298, true);
      mUI->SetUIGroupVisible(0x459b2d8, false);
      mUI->SetUIGroupVisible(0x459b348, false);
      break;
    case 0x445b340:
      mUI->SetUIGroupVisible(0x459b0f0, false);
      mUI->SetUIGroupVisible(0x459b298, false);
      mUI->SetUIGroupVisible(0x459b2d8, true);
      mUI->SetUIGroupVisible(0x459b348, false);
      break;
    case 0x445b388:
      mUI->SetUIGroupVisible(0x459b0f0, false);
      mUI->SetUIGroupVisible(0x459b298, false);
      mUI->SetUIGroupVisible(0x459b2d8, false);
      mUI->SetUIGroupVisible(0x459b348, true);
      break;
  }
}

// @ 0x0062f480
void cSPPlayModeBGMgr::UpdateBGHilite() {
  uint32_t effect = mCurrBkgEffectID;
  bool onPage = false;
  if ((effect >> 2) == mPageCount) onPage = true;
  mUI->SetUIGroupVisible(0x459b0f0, false);
  mUI->SetUIGroupVisible(0x459b298, false);
  mUI->SetUIGroupVisible(0x459b2d8, false);
  mUI->SetUIGroupVisible(0x459b348, false);
  if (onPage) {
    switch (mCurrBkgEffectID & 3) {
      case 0: mUI->SetUIGroupVisible(0x459b0f0, true); return;
      case 1: mUI->SetUIGroupVisible(0x459b298, true); return;
      case 2: mUI->SetUIGroupVisible(0x459b2d8, true); return;
      case 3: mUI->SetUIGroupVisible(0x459b348, true);
    }
  }
}

// @ 0x0062f540
void cSPPlayModeBGMgr::UpdateBGCountText() {
  cString text;
  IWindow* w = mUI->FindPlayModeUIWindow(0x47ed688);
  if (w != 0) {
    text.Load(0x7518573e, 0x47ed777, L"*BG Page Count*");
    gPageInfo->page = mPageCount + 1;
    gPageInfo->pageCount = mCurrentPage + 1;
    w->SetCaption(text.c_str());
  }
}

// @ 0x0062f2f0
void cSPPlayModeBGMgr::FUN_0062f2f0() {
  if (mChangingEnvironment) {
    if (FUN_00401050(mLastBkgEffectID)->FUN_0045b210()) {
      uint32_t id = mCrossFadeEffectID;
      mChangingEnvironment = false;
      if (FUN_00401050(id)->FUN_0045b210()) {
        FUN_00401050(mCrossFadeEffectID)->FUN_0045b150();
      }
    }
  }
}

// @ 0x0062f340 is above; 0x0062f5c0:
void cSPPlayModeBGMgr::FUN_0062f5c0() {
  if (mLastBkgEffectID != 0 && mbChangeInitiated) {
    mChangingEnvironment = true;
    mLightingWorld->SetLighting(((BGInfo*)mBackGroundInfo.mpBegin[mCurrThumbnailNum])->mLightID);
    FUN_00401050(mLastBkgEffectID)->FUN_0045ae10(1);
    mbChangeInitiated = false;
  }
}

// @ 0x0062f610
void cSPPlayModeBGMgr::FUN_0062f610() {
  if (!mbChangeInitiated && !mChangingEnvironment &&
      ((uint32_t)((char*)mBackGroundInfo.mpEnd - (char*)mBackGroundInfo.mpBegin) & 0xfffffffcu) != 0) {
    uint32_t next = mCurrBkgEffectID;
    if (mCurrThumbnailNum != next) {
      mCurrThumbnailNum = next;
      if (next < (uint32_t)(mBackGroundInfo.mpEnd - mBackGroundInfo.mpBegin)) {
        BGInfo* info = (BGInfo*)mBackGroundInfo.mpBegin[next];
        if (info != 0) {
          if (info->mType == 4) {
            FUN_00401050(mLastBkgEffectID)->FUN_0045b150();
            mCrossFadeEffectID = mLastBkgEffectID;
            mLastBkgEffectID = 0;
            mLightingWorld->SetLighting(0xf1fac055);
            return;
          }
          uint32_t prev = mLastBkgEffectID;
          mCrossFadeEffectID = prev;
          mLastBkgEffectID = info->mEffectID;
          if (mLastBkgEffectID != prev) FUN_00401050(mEntryEffectID)->FUN_0045ae10(1);
          mbChangeInitiated = true;
        }
      }
    }
  }
}

// @ 0x0062f6c0
bool cSPPlayModeBGMgr::FUN_0062f6c0() {
  BGInfo* info = (BGInfo*)mBackGroundInfo.mpBegin[mCurrThumbnailNum];
  if (info != 0 && info->mType != 4) return true;
  return false;
}


// =============================================================================================
// Property / image loading helpers (opaque externals)
struct Property {
  uint32_t pad[4];
  uint16_t pad2;
  uint16_t mType;                          // +0x12
  uint32_t* GetUInt();                     // 0x0041ea00
  int* GetInt();                           // 0x0041e990
  float* GetFloat();                       // 0x0041ea70
};
struct IPropertyList {
  virtual void v0(); virtual void AddRef(); virtual void Release();
  virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
  virtual void v8();
  virtual bool GetProperty(uint32_t id, Property** out);     // +0x24
};
struct IPropertyManager {
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
  virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
  virtual void v10();
  virtual void GetPropertyList(uint32_t instance, uint32_t group, IPropertyList** out);  // +0x2c
};
IPropertyManager* PropertyManager();                                    // 0x0067de30
bool GetPropertyAsKeyInstance(IPropertyList* l, uint32_t id, uint32_t* out);   // 0x006a12a0
bool GetPropertyAsText(IPropertyList* l, uint32_t id, cString* out);           // 0x006a1360
bool GetPropertyAsKeys(IPropertyList* l, uint32_t id, ResourceKey** keys, int* count);  // 0x006a0ae0
void* operator new(unsigned int size, const char* name, int a, int b, int c, int d);   // EA allocator
extern uint32_t gAnimResourceGroup;       // 0x01522dac
extern const float gOneF;                 // 0x01485720
extern const uint32_t kAnimPanelIconMap[4];        // 0x013fe2e8
extern const uint32_t kAnimPanelIconShadowMap[4];  // 0x013fe2f8
extern const uint32_t kAnimButtonMap[24];          // 0x013fe288
void FUN_008068d0(IWindow* w, RefObj* image, int index);
void FUN_00806aa0(IWindow* w, RefObj* image, int v);
void FUN_00806b20(IWindow* w, const void* data, int n);
void FUN_00807840(uint32_t type, uint32_t group, uint32_t instance, RefObj** out, int a, int b, int c);

class cSPPlayModeAnimLoadInfo : public RefCountVTemplate {
 public:
  uint32_t mAnimID;           // +0x08
  uint32_t mAnimBabyID;       // +0x0c
  float mAnimBabySpeed;       // +0x10
  float mAnimBabyDelay;       // +0x14
  uint32_t mImage[4];         // +0x18
  uint32_t mIconID;           // +0x28
  uint32_t mProp[4];          // +0x2c (loaded from 0x703212d, 0x70338db, 0x70338e4, 0x70338e9)
  cString mName;              // +0x3c
  virtual ~cSPPlayModeAnimLoadInfo();
  cSPPlayModeAnimLoadInfo() {}
};

// @ 0x0062ec90 (PDB name LoadAnimInfo)
void cSPPlayModeAnimation::LoadAnimInfo(cSPPlayModeAnimPanelInfo* panel, ResourceKey* key) {
  cSPPlayModeAnimLoadInfo* ref;
  IPropertyList* list = 0;
  Property* prop;
  IPropertyManager* pm = PropertyManager();
  if (list != 0) {
    IPropertyList* old = list;
    list = 0;
    old->AddRef();
  }
  pm->GetPropertyList(key->instanceID, key->groupID, &list);
  if (list != 0) {
    cSPPlayModeAnimLoadInfo* info = new ("Editor", 0, 0, 0, 0) cSPPlayModeAnimLoadInfo();
    ref = info;
    if (info != 0) info->AddRef();
    uint32_t* animId = &info->mAnimID;
    if (!GetPropertyAsKeyInstance(list, 0x486039f, animId)) *animId = 0xffffffff;
    GetPropertyAsKeyInstance(list, 0x4864a96, &info->mImage[0]);
    GetPropertyAsKeyInstance(list, 0x4864a97, &info->mImage[1]);
    GetPropertyAsKeyInstance(list, 0x4864a98, &info->mImage[2]);
    GetPropertyAsKeyInstance(list, 0x4864a99, &info->mImage[3]);
    GetPropertyAsKeyInstance(list, 0x70204d2, &info->mIconID);
    if (list != 0) {
      if (list->GetProperty(0x703212d, &prop) && prop->mType == 10) info->mProp[0] = *prop->GetUInt();
      if (list != 0) {
        if (list->GetProperty(0x70338db, &prop) && prop->mType == 10) info->mProp[1] = *prop->GetUInt();
        if (list != 0) {
          if (list->GetProperty(0x70338e4, &prop) && prop->mType == 10) info->mProp[2] = *prop->GetUInt();
          if (list != 0 && list->GetProperty(0x70338e9, &prop) && prop->mType == 10) info->mProp[3] = *prop->GetUInt();
        }
      }
    }
    if (!GetPropertyAsKeyInstance(list, 0x4879ca4, &info->mAnimBabyID)) info->mAnimBabyID = *animId;
    if (list == 0 || !list->GetProperty(0x4879ca6, &prop) || prop->mType != 0xd) {
      info->mAnimBabyDelay = 0.0f;
    } else {
      info->mAnimBabyDelay = *prop->GetFloat();
    }
    if (list == 0 || !list->GetProperty(0x4879ca5, &prop) || prop->mType != 0xd) {
      info->mAnimBabySpeed = gOneF;
    } else {
      info->mAnimBabySpeed = *prop->GetFloat();
    }
    if (!GetPropertyAsText(list, 0x5c3eb47, &info->mName)) {
      info->mName.Load(0x7518573e, 0x5c3efcd, L"animation (PLACEHOLDER)");
    }
    if (*animId != 0xffffffff) {
      LoadInfoVector& v = panel->mAnimLoadInfo;
      if (v.mpEnd < v.mpCapacity) {
        cSPPlayModeAnimLoadInfo** slot = v.mpEnd++;
        if (slot != 0) {
          *slot = info;
          info->AddRef();
        }
      } else {
        v.DoInsertValue(v.mpEnd, ref);
      }
    }
    if (ref != 0) ref->Release();
    if (list != 0) list->AddRef();
  }
}

// @ 0x0062efb0 (PDB name LoadPanelInfo)
void cSPPlayModeAnimation::LoadPanelInfo(const ResourceKey& key) {
  IPropertyList* list = 0;
  IPropertyManager* pm = PropertyManager();
  if (list != 0) {
    IPropertyList* old = list;
    list = 0;
    old->AddRef();
  }
  pm->GetPropertyList(key.instanceID, key.groupID, &list);
  if (list != 0) {
    cSPPlayModeAnimPanelInfo* panel = new ("Editor", 0, 0, 0, 0) cSPPlayModeAnimPanelInfo();
    cSPPlayModeAnimPanelInfo* ref = panel;
    if (panel != 0) panel->AddRef();
    Property* prop;
    if (list == 0 || !list->GetProperty(0x5c43a40, &prop) || prop->mType != 9) {
      panel->mOrder = 0;
    } else {
      panel->mOrder = *prop->GetInt();
    }
    if (!GetPropertyAsKeyInstance(list, 0x5c54e7e, &panel->mIconID)) panel->mIconID = 0;
    if (!GetPropertyAsKeyInstance(list, 0x5c54e7f, &panel->mIconShadowID)) panel->mIconShadowID = 0;
    ResourceKey* keys;
    int count;
    if (!GetPropertyAsKeys(list, 0x48676c2, &keys, &count)) count = 0;
    for (int i = 0; i < count; i++) {
      keys[i].groupID = gAnimResourceGroup;
      keys[i].typeID = 0xb1b104;
      LoadAnimInfo(panel, &keys[i]);
    }
    if (count != 0) {
      cSPPlayModeAnimPanelInfo** it = mAnimPanelInfo.mpBegin;
      cSPPlayModeAnimPanelInfo** end = mAnimPanelInfo.mpEnd;
      bool inserted = false;
      for (; it != end; it++) {
        cSPPlayModeAnimPanelInfo* other = *it;
        if (other != 0) other->AddRef();
        if ((int)panel->mOrder < (int)other->mOrder) {
          mAnimPanelInfo.Insert(it, ref);
          other->Release();
          inserted = true;
          break;
        }
        other->Release();
      }
      if (!inserted) {
        if (mAnimPanelInfo.mpEnd < mAnimPanelInfo.mpCapacity) {
          cSPPlayModeAnimPanelInfo** slot = mAnimPanelInfo.mpEnd++;
          if (slot != 0) {
            *slot = panel;
            panel->AddRef();
          }
        } else {
          mAnimPanelInfo.DoInsertValue(mAnimPanelInfo.mpEnd, ref);
        }
      }
    }
    if (ref != 0) ref->Release();
    if (list != 0) list->AddRef();
  }
}

// @ 0x0062e7e0 (PDB name UpdateButtonImages)
void cSPPlayModeAnimation::UpdateButtonImages() {
  mUI->SetUIGroupVisible(0x4864e88, mPageCount * 0x18 < (uint32_t)GetAnimCount());
  const uint32_t* btn = kAnimButtonMap;
  for (uint32_t i = 0; i < 4; i++) {
    FUN_008068d0(mUI->FindPlayModeUIWindow(kAnimPanelIconMap[i]), 0, 0);
    FUN_008068d0(mUI->FindPlayModeUIWindow(kAnimPanelIconShadowMap[i]), 0, 0);
    for (int b = 0; b < 6; b++, btn++) {
      IWindow* w = mUI->FindPlayModeUIWindow(*btn);
      w->SetFlag(2, false);
      w->SetFlag(1, false);
      for (int k = 0; k < 4; k++) FUN_008068d0(w, 0, k);
    }
  }
  int pageBase = (mPageCount * 3 - 3) * 8;
  int panelBase = mPageCount * 4 - 4;
  int off = panelBase * 4;
  uint32_t panelIdx = 0;
  int btnBase = 0;
  uint32_t j = 0;
  do {
    uint32_t cur = panelIdx;
    if ((uint32_t)(mAnimPanelInfo.mpEnd - mAnimPanelInfo.mpBegin) <= (uint32_t)(panelBase + panelIdx)) return;
    cSPPlayModeAnimPanelInfo* panel = *(cSPPlayModeAnimPanelInfo**)((char*)mAnimPanelInfo.mpBegin + off);
    if (panel->mIconID != 0) {
      RefObj* image = 0;
      IWindow* w = mUI->FindPlayModeUIWindow(kAnimPanelIconMap[panelIdx]);
      if (image != 0) { RefObj* o = image; image = 0; o->AddRef(); }
      FUN_00807840(0x2f7d0004, 0x100d977c, panel->mIconID, &image, 0, -1, -1);
      FUN_008068d0(w, image, 0);
      if (image != 0) image->AddRef();
    }
    panel = *(cSPPlayModeAnimPanelInfo**)((char*)mAnimPanelInfo.mpBegin + off);
    if (panel->mIconShadowID != 0) {
      RefObj* image = 0;
      IWindow* w = mUI->FindPlayModeUIWindow(kAnimPanelIconShadowMap[cur]);
      if (image != 0) { RefObj* o = image; image = 0; o->AddRef(); }
      FUN_00807840(0x2f7d0004, 0x100d977c, panel->mIconShadowID, &image, 0, -1, -1);
      FUN_008068d0(w, image, 0);
      if (image != 0) image->AddRef();
    }
    panel = *(cSPPlayModeAnimPanelInfo**)((char*)mAnimPanelInfo.mpBegin + off);
    uint32_t n = (uint32_t)(panel->mAnimLoadInfo.mpEnd - panel->mAnimLoadInfo.mpBegin);
    j = 0;
    if (n != 0) {
      do {
        uint32_t cj = j;
        if (5 < j) break;
        int bi = btnBase + j;
        IWindow* w = mUI->FindPlayModeUIWindow(kAnimButtonMap[bi]);
        if ((uint32_t)GetAnimCount() <= (uint32_t)(bi + pageBase)) break;
        cSPPlayModeAnimLoadInfo* info = (*(cSPPlayModeAnimPanelInfo**)((char*)mAnimPanelInfo.mpBegin + off))->mAnimLoadInfo.mpBegin[cj];
        uint32_t* img = &info->mImage[0];
        for (int k = 0; k < 4; k++, img++) {
          RefObj* image = 0;
          FUN_00807840(0x2f7d0004, 0x100d977c, *img, &image, 0, -1, -1);
          FUN_008068d0(w, image, k);
          if (image != 0) image->AddRef();
        }
        RefObj* icon = 0;
        FUN_00807840(0x2f7d0004, 0x100d977c, info->mIconID, &icon, 0, -1, -1);
        FUN_00806aa0(w, icon, 0);
        FUN_00806b20(w, &info->mProp[0], 4);
        w->SetFlag(2, true);
        w->SetFlag(1, true);
        pTooltip[bi]->SetText(info->mName.c_str(), -1, 1);
        if (icon != 0) icon->AddRef();
        j++;
      } while (j < n);
    }
    off += 4;
    btnBase += 6;
    panelIdx++;
  } while (panelIdx < 4);
}
