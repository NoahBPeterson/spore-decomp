// src/game/SPEditors/SPPlayModeAnimation.cpp -- migrated from slice(s) s0062e7e0, s0062da00 by tools/migrate/rewrite.py
// Object file: SPEditors/SPPlayModeAnimation.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPPlayModeAnimation.h"
#include "SP/cSPPlayModeUI.h"
#include "SP/cString.h"
#include "SP/cILightingWorld.h"
#include "SP/cSPPlayModeAnimLoadInfo.h"
#include "SP/cSPPlayModeAnimPanelInfo.h"
#include "SP/cSPPlayModeBGMgr.h"

// unnamed retail callees and globals (address in the comment)
extern const uint32_t kAnimButtonMap[24];  // 0x013fe288
extern const char kTooltipExtra[];         // 0x013fe27c (object, passed by address)
extern const float gTooltipX;              // 0x1486110
extern const float gTooltipY;              // 0x13f6ad8

// ---- items of slice s0062da00_ui begin (TODO(rewrite): local stubs, replace by canonical classes)
class cString {
 public:
  uint32_t mData[5];
  cString();
  ~cString();
  void Load(uint32_t table, uint32_t group, const wchar_t* def);
  const wchar_t* c_str();
};
struct AnimLoadInfo {
  uint32_t pad[2];
  uint32_t mAnimID;        // +0x08
  uint32_t mAnimBabyID;    // +0x0c
  float mAnimBabySpeed;    // +0x10
  float mAnimBabyDelay;    // +0x14
};
struct LoadInfoVector {
  AnimLoadInfo** mpBegin;
  AnimLoadInfo** mpEnd;
  AnimLoadInfo** mpCapacity;
  uint32_t mAllocator;
  uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
};
struct AnimPanelInfo {
  uint32_t pad[5];
  LoadInfoVector mAnimLoadInfo;     // +0x14
};
struct PanelVector {
  AnimPanelInfo** mpBegin;
  AnimPanelInfo** mpEnd;
  AnimPanelInfo** mpCapacity;
  uint32_t mAllocator;
  uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
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
  virtual void v33(); virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37();
  virtual void v38(); virtual void v39(); virtual void v40(); virtual void v41(); virtual void v42();
  virtual void v43(); virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
  virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51(); virtual void v52();
  virtual void v53(); virtual void v54(); virtual void v55(); virtual void v56(); virtual void v57();
  virtual void v58(); virtual void v59(); virtual void v60(); virtual void v61(); virtual void v62();
  virtual void v63(); virtual void v64();
  virtual void SetWinProc(void* proc);                 // +0x104
};
struct cSPPlayModeUI {
  IWindow* FindPlayModeUIWindow(uint32_t id);
  void SetUIGroupVisible(uint32_t group, bool visible);
};
struct UITooltip {
  virtual void AddRef();
  virtual void Release();
  uint32_t pad[25];
  UITooltip(const wchar_t* name, uint32_t id, const wchar_t* text, const float* pos, int a,
            const void* b, int c);
};
void* operator new(unsigned int size, int align, const char* name, void* alloc);
void* GetAllocator();   // FUN_009512c0
extern const uint32_t kAnimButtonMap[24];  // 0x013fe288
extern const char kTooltipExtra[];         // 0x013fe27c (object, passed by address)
extern const float gTooltipX;              // 0x1486110
extern const float gTooltipY;              // 0x13f6ad8
struct GlobalPageInfo { uint32_t pad[10]; uint32_t pageCount; uint32_t field; };  // +0x28, +0x2c
extern GlobalPageInfo* gPageInfo;          // 0x015f7cf4
struct AnimController;   // object at creature+0x184
struct AnimatingCreature {
  virtual void v0(); virtual void v1();
  virtual uint32_t CreateAnim(uint32_t anim, int a);     // +0x08
  virtual void SetAnimParam(uint32_t h, uint32_t v);     // +0x0c
  virtual void v4(); virtual void v5();
  virtual void Start(uint32_t h);                        // +0x18
  virtual void v7();
  virtual void SetLooping(uint32_t h, int v);            // +0x20
  virtual void SetBlend(uint32_t h, float v);            // +0x24
  virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
  virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
  virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
  virtual float GetAnimLength(uint32_t anim);            // +0x60
  uint32_t pad[(0x184 - 4) / 4];
  AnimController* mController;      // +0x184
  uint32_t mFadeOutHandle;          // +0x188
  uint32_t mCurHandle;              // +0x18c
  bool IsMoveIdleAnim(uint32_t anim);
  bool FUN_00a02800(uint32_t anim);
};
struct AnimController {
  void FUN_00a00f90(void* slot, int v);
  void FUN_00a01f10(uint32_t handle, int v);
};
struct CreatureStructure {
  uint32_t pad[2];
  AnimatingCreature* mCreature;   // +0x08
  void FUN_007cd950(uint32_t anim);
};
struct EditorBase { uint32_t pad[0x360 / 4]; struct AnimMgr* mgr; };
struct AnimMgr { CreatureStructure* GetCreatureStructure(uint32_t id); };
class cSPPlayModeAnimation {
 public:
  void* vftable;
  EditorBase* mEditorBase;       // +0x04
  uint32_t mCurrAnimID;          // +0x08
  PanelVector mAnimPanelInfo;    // +0x0c
  uint32_t pad1c;                // +0x1c
  uint32_t mPageCount;           // +0x20
  uint32_t mViewMode;            // +0x24
  cSPPlayModeUI* mUI;            // +0x28
  UITooltip* pTooltip[24];       // +0x2c

  __declspec(noinline) int GetAnimCount();
  bool GetExpansionAnimInfo(int buttonId, uint32_t* id, uint32_t* babyId, float* speed, float* delay);
  bool IsExtraAnims();
  void UpdatePageCount();
  void Activate();
  void ResetCurAnimWindow();
  float StartNewAnimation(uint32_t creatureId, uint32_t anim, bool flag, uint32_t param, uint32_t* outHandle);
};
// ---- items of slice s0062da00_ui end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern GlobalPageInfo* gPageInfo;          // 0x015f7cf4

// ---- items of slice s0062e7e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t gAnimResourceGroup;       // 0x01522dac
extern const float gOneF;                 // 0x01485720
extern const uint32_t kAnimPanelIconMap[4];        // 0x013fe2e8
extern const uint32_t kAnimPanelIconShadowMap[4];  // 0x013fe2f8
struct ResourceKey;
struct RefCountVTemplate {
  int mRefCount;
  RefCountVTemplate() : mRefCount(0) {}
  virtual ~RefCountVTemplate() {}
  virtual int AddRef() { return ++mRefCount; }
  virtual int Release();
};
struct IWindow_s0062_e7e0 {
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
struct UITooltip_s0062_e7e0 {
  void SetText(const wchar_t* text, int a, int b);    // cSPUITooltipWinProc::SetText
};
struct cSPPlayModeUI_s0062_e7e0 {
  IWindow_s0062_e7e0* FindPlayModeUIWindow(uint32_t id);  // 0x00634dc0 (cSPPlayModeUI::FindPlayModeUIWindow)
  void SetUIGroupVisible(uint32_t group, bool visible);  // 0x00635760 (cSPPlayModeUI::SetUIGroupVisible)
  bool IsUIGroupEnabled(uint32_t group);  // 0x00635890 (cSPPlayModeUI::IsUIGroupEnabled)
  void SetAnimButtonsEnabled(bool enabled);  // 0x00635f00 (cSPPlayModeUI::SetAnimButtonsEnabled)
  void SetExpansionAnimButtonsEnabled(bool enabled);  // 0x00635ff0 (cSPPlayModeUI::SetExpansionAnimButtonsEnabled)
};
class cSPPlayModeAnimLoadInfo;
struct LoadInfoVector_s0062_e7e0 {
  cSPPlayModeAnimLoadInfo** mpBegin;
  cSPPlayModeAnimLoadInfo** mpEnd;
  cSPPlayModeAnimLoadInfo** mpCapacity;
  uint32_t mAllocator;
  LoadInfoVector_s0062_e7e0() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~LoadInfoVector_s0062_e7e0();     // out of line (0x005c7f10)
  void DoInsertValue(cSPPlayModeAnimLoadInfo** pos, cSPPlayModeAnimLoadInfo* const& v);   // 0x005c8480
};
class cSPPlayModeAnimPanelInfo : public RefCountVTemplate {
 public:
  uint32_t mOrder;                  // +0x08
  uint32_t mIconID;                 // +0x0c
  uint32_t mIconShadowID;           // +0x10
  LoadInfoVector_s0062_e7e0 mAnimLoadInfo;     // +0x14
  uint32_t mPad24;                  // +0x24
  virtual ~cSPPlayModeAnimPanelInfo();
};
struct PanelVector_s0062_e7e0 {
  cSPPlayModeAnimPanelInfo** mpBegin;
  cSPPlayModeAnimPanelInfo** mpEnd;
  cSPPlayModeAnimPanelInfo** mpCapacity;
  uint32_t mAllocator;
  void DoInsertValue(cSPPlayModeAnimPanelInfo** pos, cSPPlayModeAnimPanelInfo* const& v);   // 0x005c8480
  void Insert(cSPPlayModeAnimPanelInfo** pos, cSPPlayModeAnimPanelInfo* const& v);          // 0x005c21d0
};
class cSPPlayModeAnimation_s0062_e7e0 {
 public:
  void* vftable;
  void* mEditorBase;             // +0x04
  uint32_t mCurrAnimID;          // +0x08
  PanelVector_s0062_e7e0 mAnimPanelInfo;    // +0x0c
  uint32_t pad1c;                // +0x1c
  uint32_t mPageCount;           // +0x20
  uint32_t mNumPages;            // +0x24
  cSPPlayModeUI_s0062_e7e0* mUI;            // +0x28
  UITooltip_s0062_e7e0* pTooltip[24];       // +0x2c

  int GetAnimCount();  // 0x0062e4b0 (cSPPlayModeAnimation::GetAnimCount)
  void UpdateButtonImages();  // 0x0062e7e0 (cSPPlayModeAnimation::UpdateButtonImages)
  void UpdatePageCount();  // 0x0062e600 (cSPPlayModeAnimation::UpdatePageCount)
  void NextAnimWindowSet();
  void PreviousAnimWindowSet();
  void LoadAllAnimInfo();
  void LoadPanelInfo(const ResourceKey& key);  // 0x0062efb0 (cSPPlayModeAnimation::LoadPanelInfo)
  void LoadAnimInfo(cSPPlayModeAnimPanelInfo* panel, ResourceKey* key);  // 0x0062ec90 (cSPPlayModeAnimation::LoadAnimInfo)
  void Init(void* editorBase, cSPPlayModeUI_s0062_e7e0* ui);  // 0x0062f2a0 (cSPPlayModeAnimation::Init)
};
struct ResourceKey { uint32_t instanceID, typeID, groupID; };
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
void FUN_008068d0(IWindow_s0062_e7e0* w, RefObj* image, int index);
void FUN_00806aa0(IWindow_s0062_e7e0* w, RefObj* image, int v);
void FUN_00806b20(IWindow_s0062_e7e0* w, const void* data, int n);
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
// ---- items of slice s0062e7e0 end

// @ 0x0062e4b0
int cSPPlayModeAnimation::GetAnimCount()
{
  int count = 0;
  uint32_t i = 0;
  if (mAnimPanelInfo.size() > 0) {
    AnimPanelInfo** p = mAnimPanelInfo.mpBegin;
    do {
      i++;
      count += (int)(*p)->mAnimLoadInfo.size();
      p++;
    } while (i < mAnimPanelInfo.size());
  }
  return count;
}

// @ 0x0062e4f0
bool cSPPlayModeAnimation::GetExpansionAnimInfo(int buttonId, uint32_t* id, uint32_t* babyId, float* speed, float* delay)
{
  uint32_t page = mPageCount;
  int base = page * 4 - 4;
  uint32_t k = 0;
  int local = 0;
  for (;;) {
    if ((uint32_t)(mAnimPanelInfo.mpEnd - mAnimPanelInfo.mpBegin) <= (uint32_t)(local + base)) return false;
    AnimPanelInfo* panel = mAnimPanelInfo.mpBegin[local + base];
    uint32_t n = (uint32_t)(panel->mAnimLoadInfo.mpEnd - panel->mAnimLoadInfo.mpBegin);
    uint32_t j = 0;
    if (n != 0) {
      do {
        if (5 < j) break;
        if (buttonId == (int)kAnimButtonMap[k + j]) {
          uint32_t cnt = (uint32_t)GetAnimCount();
          if (cnt <= k + j + (page * 3 - 3) * 8) return false;
          AnimLoadInfo* info = mAnimPanelInfo.mpBegin[local + base]->mAnimLoadInfo.mpBegin[j];
          *id = info->mAnimID;
          *babyId = info->mAnimBabyID;
          *speed = info->mAnimBabySpeed;
          *delay = info->mAnimBabyDelay;
          return true;
        }
        j++;
      } while (j < n);
    }
    local++;
    k += 6;
    if (0x17 < k) return false;
  }
}

// @ 0x0062e5f0
bool SP::cSPPlayModeAnimation::IsExtraAnims()
{
  bool r = GetAnimCount() != 0;
  return r;
}

// @ 0x0062e600
void cSPPlayModeAnimation::UpdatePageCount()
{
  cString text;
  IWindow* w1 = mUI->FindPlayModeUIWindow(0x5c2a0e8);
  IWindow* w2 = mUI->FindPlayModeUIWindow(0x5fb7ee0);
  if (w1 != 0 && w2 != 0) {
    if (mViewMode == 1) {
      w1->SetFlag(1, false);
      w2->SetFlag(1, false);
    } else {
      w1->SetFlag(1, true);
      w2->SetFlag(1, true);
    }
    text.Load(0x7518573e, 0x5c2b47b, L"Anim Page Count (PLACEHOLDER)");
    gPageInfo->pageCount = mPageCount + 1;
    gPageInfo->field = mViewMode;
    w1->SetCaption(text.c_str());
  }
}

// @ 0x0062e6c0
void cSPPlayModeAnimation::Activate()
{
  float pos[2];
  pos[0] = gTooltipX;
  pos[1] = gTooltipY;
  UITooltip** slot = &pTooltip[0];
  for (uint32_t off = 0; off < 0x60; off += 4, slot++) {
    UITooltip* t = new (4, "UI/Tooltip", GetAllocator())
        UITooltip(L"Tooltips", 0x3754e6c, L"***PLACEHOLDER***", pos, 0, kTooltipExtra, 0);
    UITooltip* old = *slot;
    if (t != old) {
      if (t) t->AddRef();
      *slot = t;
      if (old) old->Release();
    }
    IWindow* w = mUI->FindPlayModeUIWindow(*(uint32_t*)((char*)kAnimButtonMap + off));
    w->SetWinProc(*slot);
  }
  UpdatePageCount();
}

// @ 0x0062e7a0
void SP::cSPPlayModeAnimation::ResetCurAnimWindow()
{
  mUI->SetUIGroupVisible(0x4864e80, false);
  if (GetAnimCount() != 0) mUI->SetUIGroupVisible(0x4864e88, true);
  mCurrAnimWindowSet = 0;
}

// @ 0x0062e7e0
void cSPPlayModeAnimation_s0062_e7e0::UpdateButtonImages()
{
  mUI->SetUIGroupVisible(0x4864e88, mPageCount * 0x18 < (uint32_t)GetAnimCount());
  const uint32_t* btn = kAnimButtonMap;
  for (uint32_t i = 0; i < 4; i++) {
    FUN_008068d0(mUI->FindPlayModeUIWindow(kAnimPanelIconMap[i]), 0, 0);
    FUN_008068d0(mUI->FindPlayModeUIWindow(kAnimPanelIconShadowMap[i]), 0, 0);
    for (int b = 0; b < 6; b++, btn++) {
      IWindow_s0062_e7e0* w = mUI->FindPlayModeUIWindow(*btn);
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
      IWindow_s0062_e7e0* w = mUI->FindPlayModeUIWindow(kAnimPanelIconMap[panelIdx]);
      if (image != 0) { RefObj* o = image; image = 0; o->AddRef(); }
      FUN_00807840(0x2f7d0004, 0x100d977c, panel->mIconID, &image, 0, -1, -1);
      FUN_008068d0(w, image, 0);
      if (image != 0) image->AddRef();
    }
    panel = *(cSPPlayModeAnimPanelInfo**)((char*)mAnimPanelInfo.mpBegin + off);
    if (panel->mIconShadowID != 0) {
      RefObj* image = 0;
      IWindow_s0062_e7e0* w = mUI->FindPlayModeUIWindow(kAnimPanelIconShadowMap[cur]);
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
        IWindow_s0062_e7e0* w = mUI->FindPlayModeUIWindow(kAnimButtonMap[bi]);
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

// @ 0x0062ebb0
cSPPlayModeAnimPanelInfo::~cSPPlayModeAnimPanelInfo()
{}

// @ 0x0062ebe0
void SP::cSPPlayModeAnimation::NextAnimWindowSet()
{
  uint32_t* pc = &mCurrAnimWindowSet;
  *pc = *pc + 1;
  if (*pc != 0) mUI->SetUIGroupVisible(0x4864e80, true);
  mUI->SetAnimButtonsEnabled(false);
  if (!mUI->IsUIGroupEnabled(0x48666b8)) mUI->SetExpansionAnimButtonsEnabled(true);
  UpdateButtonImages();
  UpdatePageCount();
}

// @ 0x0062ec30
void SP::cSPPlayModeAnimation::PreviousAnimWindowSet()
{
  uint32_t* pc = &mCurrAnimWindowSet;
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

// @ 0x0062ec90
void cSPPlayModeAnimation_s0062_e7e0::LoadAnimInfo(cSPPlayModeAnimPanelInfo* panel, ResourceKey* key)
{
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
      LoadInfoVector_s0062_e7e0& v = panel->mAnimLoadInfo;
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

// @ 0x0062efb0
void cSPPlayModeAnimation_s0062_e7e0::LoadPanelInfo(const ResourceKey& key)
{
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
