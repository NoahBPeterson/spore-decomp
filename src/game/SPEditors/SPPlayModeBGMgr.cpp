// src/game/SPEditors/SPPlayModeBGMgr.cpp -- migrated from slice(s) s00b1d870, s0062f6e0, s0062e7e0 by tools/migrate/rewrite.py
// Object file: SPEditors/SPPlayModeBGMgr.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPPlayModeBGMgr.h"
#include "SP/cILightingWorld.h"
#include "SP/cSPPlayModeAnimLoadInfo.h"
#include "SP/cSPPlayModeAnimPanelInfo.h"
#include "SP/cSPPlayModeAnimation.h"
#include "SP/cSPPlayModeUI.h"
#include "SP/cString.h"
#include "SP/cJob.h"
#include "SP/cPlayModePhoto.h"
#include "SP/cSPPlayModeBGInfo.h"
#include "SP/cSPPlayModePhotoBrowser.h"
#include <intrin.h>

// ---- items of slice s0062e7e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
class cString {
 public:
  uint32_t mData[5];
  cString();
  ~cString();
  void Load(uint32_t table, uint32_t group, const wchar_t* def);
  const wchar_t* c_str();
};
struct IWindow {
virtual void v0();
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
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
virtual void v27();
virtual void v28();
virtual void v29();
  virtual void v30();
  virtual void SetFlag(int flag, bool value);          // +0x7c
  virtual void SetCaption(const wchar_t* text);        // +0x80
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
struct BGInfoVector { void** mpBegin; void** mpEnd; void** mpCapacity; uint32_t mAllocator; };
struct BGInfo { uint32_t pad[2]; uint32_t mEffectID; uint32_t pad2; uint32_t mType; uint32_t mLightID; };   // +8, +0x10, +0x14
struct FxObj {
  int FUN_0045b210();
  void FUN_0045b150();
  void FUN_0045ae10(int v);
};
FxObj* __stdcall FUN_00401050(uint32_t id);
struct ILightingWorld {
virtual void v0();
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
virtual void v11();
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
void cSPPlayModeBGMgr::FUN_0062f5c0() {
  if (mLastBkgEffectID != 0 && mbChangeInitiated) {
    mChangingEnvironment = true;
    mLightingWorld->SetLighting(((BGInfo*)mBackGroundInfo.mpBegin[mCurrThumbnailNum])->mLightID);
    FUN_00401050(mLastBkgEffectID)->FUN_0045ae10(1);
    mbChangeInitiated = false;
  }
}
// ---- items of slice s0062e7e0 end

// unnamed retail callees and globals that name local stubs (address in the comment)

// ---- items of slice s0062f6e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedDecrement, _rotl)
void* operator new(size_t, const char*, int, int, int, int);
inline void* operator new(size_t, void* p) { return p; }
struct IRefCount {
    virtual int AddRef();
    virtual int Release();
};
template <class T> struct AutoRef {
    T* mpObject;
    AutoRef() : mpObject(0) {}
    AutoRef(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    AutoRef(const AutoRef& o) : mpObject(o.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRef() { if (mpObject) mpObject->Release(); }
};
template <class T> struct SPVec {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    SPVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~SPVec();
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    T* erase(T* first, T* last);
    T* insert(T* pos, const T& v);
    void DoInsertValueEnd(T* pos, const T& v);
};
struct cSPPlayModeUI_s0062_f6e0 {
    void* FindPlayModeUIWindow(uint32_t id);  // 0x00634dc0 (cSPPlayModeUI::FindPlayModeUIWindow)
    void* FindEditorUIWindow(uint32_t id);  // 0x00634e40 (cSPPlayModeUI::FindEditorUIWindow)
    void SetUIGroupVisible(uint32_t id, bool v);  // 0x00635760 (cSPPlayModeUI::SetUIGroupVisible)
    void SetEditorUIGroupVisible(uint32_t id, bool v);  // 0x00635790 (cSPPlayModeUI::SetEditorUIGroupVisible)
    void SetEditorUIEnabled(uint32_t id, bool v);  // 0x00634f20 (cSPPlayModeUI::SetEditorUIEnabled)
    void SetEnabled(uint32_t id, bool v);  // 0x00634ef0 (cSPPlayModeUI::SetEnabled)
    void ToggleUIGroup(uint32_t id, bool v);  // 0x006357c0 (cSPPlayModeUI::ToggleUIGroup)
};
struct RefCountVBase {
    virtual void Dtor_();
    virtual int AddRef();
    virtual int Release();
    int mRefCount;
    RefCountVBase() : mRefCount(0) {}
};
struct cSPPlayModeBGInfo : RefCountVBase {
    uint32_t mEntryEffectID;
    uint32_t mThumbNailID;
    uint32_t mOrderNumber;
    uint32_t mLightingID;
    cSPPlayModeBGInfo() {}
};
struct UIWindow {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
    virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
    virtual bool v0A();
    virtual void v0B(); virtual void v0C(); virtual void v0D(); virtual void v0E(); virtual void v0F();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v1A(); virtual void v1B(); virtual void v1C(); virtual void v1D(); virtual void v1E();
    virtual void SetVisible(bool visible, bool animate);
};
struct Effect {
    int f0045b210();
    void f0045b150();
    void f0045ae10(int);
};
Effect* __stdcall GetEffect(uint32_t id);   // FUN_00401050
struct ResourceKey { uint32_t instance, type, group; };
struct PropertyList;
struct Property {
    uint16_t pad[9];
    uint16_t type;   // +0x12
    int* GetInt();
};
struct PropertyList : IRefCount {
    virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6();
    virtual void s7(); virtual void s8();
    virtual bool GetProperty(uint32_t id, Property** out);   // vtbl +0x24
};
struct PropertyManager_ {
    virtual int a0(); virtual int a1(); virtual int a2(); virtual int a3(); virtual int a4();
    virtual int a5(); virtual int a6(); virtual int a7();
    virtual void GetPropertyList(uint32_t instance, uint32_t group, AutoRef<PropertyList>* out); // +0x20 (unused here)
    virtual void a9(); virtual void a10();
    virtual void GetPropertyListEx(uint32_t instance, uint32_t group, AutoRef<PropertyList>* out); // +0x2c
};
PropertyManager_* PropertyManager();   // 0x0067de30
void GetPropertyAsKeyInstance(PropertyList* props, uint32_t id, uint32_t* out);  // cdecl
struct KeyFilterBase {
    virtual void v0();
    int a;
    uint32_t b;
    uint32_t c;
    int d;
    KeyFilterBase() {}
    ~KeyFilterBase() {}
};
struct KeyFilter : KeyFilterBase {
    KeyFilter(uint32_t group) { a = -1; b = group | 0x40607000; c = 0xb1b104; d = -1; }
};
struct KeyArray {
    ResourceKey* mpBegin;
    ResourceKey* mpEnd;
    ResourceKey* mpCap;
    uint32_t mAlloc[2];
    KeyArray() : mpBegin(0), mpEnd(0), mpCap(0) {}
    ~KeyArray() {
        if (mpBegin && ((int*)mpBegin)[-1] != 0) EASTL_allocator_deallocate(mpBegin);
    }
    static void EASTL_allocator_deallocate(void*);
};
struct ResourceManager_ {
    virtual int a0(); virtual int a1(); virtual int a2(); virtual int a3(); virtual int a4();
    virtual int a5(); virtual int a6(); virtual int a7(); virtual int a8(); virtual int a9();
    virtual int a10(); virtual int a11(); virtual int a12(); virtual int a13();
    virtual void GetKeys(KeyArray* out, KeyFilterBase* filter, int flag);   // +0x38
};
ResourceManager_* GetResourceManager();   // 0x008de1a0
struct cSPPlayModeBGMgr_s0062_f6e0 {
    virtual void v0();
    SPVec<AutoRef<cSPPlayModeBGInfo> > mBG;      // +0x04
    uint32_t pad0[2];                             // +0x10
    uint32_t mCurrThumbnailNum;                   // +0x18
    uint32_t mCurrBkgEffectID;                    // +0x1c
    uint32_t mLastBkgEffectID;                    // +0x20
    uint32_t pad1;                                // +0x24
    uint32_t mEntryEffectID;                      // +0x28
    uint32_t mChanging;                           // +0x2c
    uint8_t  mUI;                                 // +0x30
    cSPPlayModeUI_s0062_f6e0* mUIPtr;                        // +0x34
    uint32_t mPageCount;                          // +0x38
    uint32_t mLightingWorld;                      // +0x3c
    uint32_t mbChangeInitiated;                   // +0x40
    uint8_t  mb44;                                // +0x44

    __declspec(noinline) void ShowBGThumbnails();  // 0x0062f6e0 (cSPPlayModeBGMgr::ShowBGThumbnails)
    bool HandleButton(uint32_t id);
    void Shutdown();  // 0x0062f920 (cSPPlayModeBGMgr::Shutdown)
    __declspec(noinline) void LoadBackground(const ResourceKey* key);  // 0x0062f9f0 (cSPPlayModeBGMgr::LoadBackground)
    void LoadAllBGInfoFromGroup(uint8_t group);
    void Init(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint8_t e);  // 0x0062fc90 (cSPPlayModeBGMgr::Init)
    void SetBGHilite(uint32_t id);  // 0x0062f340 (cSPPlayModeBGMgr::SetBGHilite)
    void UpdateBGCountText();  // 0x0062f540 (cSPPlayModeBGMgr::UpdateBGCountText)
    void UpdateBGHilite();  // 0x0062f480 (cSPPlayModeBGMgr::UpdateBGHilite)
    void FUN_0062f610();  // 0x0062f610 (cSPPlayModeBGMgr::FUN_0062f610)
};
void FUN_008068d0(void* win, void* image, int z);
void FUN_00807840(uint32_t a, uint32_t b, uint32_t c, AutoRef<IRefCount>* out, int d, int e, int f);
struct SharedLibList {
    virtual void v0();
    SPVec<AutoRef<IRefCount> > mLibs;
    SharedLibList();
    ~SharedLibList();
};
// ---- items of slice s0062f6e0 end

// @ 0x0062f340
void SP::cSPPlayModeBGMgr::SetBGHilite(unsigned int id)
{
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
void SP::cSPPlayModeBGMgr::UpdateBGHilite()
{
  uint32_t effect = mCurrThumbnailNum;
  bool onPage = false;
  if ((effect >> 2) == mCurrentPage) onPage = true;
  mUI->SetUIGroupVisible(0x459b0f0, false);
  mUI->SetUIGroupVisible(0x459b298, false);
  mUI->SetUIGroupVisible(0x459b2d8, false);
  mUI->SetUIGroupVisible(0x459b348, false);
  if (onPage) {
    switch (mCurrThumbnailNum & 3) {
      case 0: mUI->SetUIGroupVisible(0x459b0f0, true); return;
      case 1: mUI->SetUIGroupVisible(0x459b298, true); return;
      case 2: mUI->SetUIGroupVisible(0x459b2d8, true); return;
      case 3: mUI->SetUIGroupVisible(0x459b348, true);
    }
  }
}

// @ 0x0062f540
void cSPPlayModeBGMgr::UpdateBGCountText()
{
  cString text;
  IWindow* w = mUI->FindPlayModeUIWindow(0x47ed688);
  if (w != 0) {
    text.Load(0x7518573e, 0x47ed777, L"*BG Page Count*");
    gPageInfo->page = mPageCount + 1;
    gPageInfo->pageCount = mCurrentPage + 1;
    w->SetCaption(text.c_str());
  }
}

// @ 0x0062f610
void cSPPlayModeBGMgr::FUN_0062f610()
{
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
bool cSPPlayModeBGMgr::FUN_0062f6c0()
{
  BGInfo* info = (BGInfo*)mBackGroundInfo.mpBegin[mCurrThumbnailNum];
  if (info != 0 && info->mType != 4) return true;
  return false;
}

// @ 0x0062f6e0
void SP::cSPPlayModeBGMgr::ShowBGThumbnails()
{
    uint32_t ids[4] = { 0x445b018, 0x445b318, 0x445b340, 0x445b388 };
    uint32_t i = 0;
    do {
        if (i >= mBackGroundInfo.size())
            break;
        uint32_t idx = i + mCurrentPage * 4;
        void* win = mUI->FindPlayModeUIWindow(ids[i]);
        if (idx >= mBackGroundInfo.size()) {
            FUN_008068d0(win, 0, 0);
        } else {
            AutoRef<IRefCount> img;
            FUN_00807840(0x2f7d0004, 0x100d977c, mBackGroundInfo.mpBegin[idx].mpObject->mThumbNailID, &img, 0, -1, -1);
            FUN_008068d0(win, img.mpObject, 0);
        }
        ++i;
    } while (i < 4);
    for (i = mBackGroundInfo.size(); i < 4; ++i) {
        UIWindow* w = (UIWindow*)mUI->FindPlayModeUIWindow(ids[i]);
        if (w)
            w->SetVisible(true, false);
    }
}

// @ 0x0062f7f0
bool cSPPlayModeBGMgr_s0062_f6e0::HandleButton(uint32_t id)
{
    bool result = false;
    uint32_t base = mPageCount * 4;
    uint32_t target;
    switch (id) {
    case 0x445b018:
        if (mCurrBkgEffectID == base)
            return result;
        if (mBG.size() <= base)
            return result;
        mCurrBkgEffectID = base;
        goto hilite;
    case 0x445b318: target = base + 1; break;
    case 0x445b340: target = base + 2; break;
    case 0x445b388: target = base + 3; break;
    case 0x47ed5b8:
        if (mPageCount > 0) {
            mPageCount = mPageCount - 1;
            UpdateBGCountText();
            ShowBGThumbnails();
            UpdateBGHilite();
            result = true;
        }
        return result;
    case 0x47ed640:
        if (mPageCount < mLightingWorld) {
            mPageCount = mPageCount + 1;
            UpdateBGCountText();
            ShowBGThumbnails();
            UpdateBGHilite();
            result = true;
        }
        return result;
    default:
        return result;
    }
    if (mCurrBkgEffectID == target)
        return result;
    if (mBG.size() <= target)
        return result;
    mCurrBkgEffectID = target;
hilite:
    result = true;
    SetBGHilite(id);
    FUN_0062f610();
    return result;
}

// @ 0x0062f8c0
SharedLibList::SharedLibList()
{}

// @ 0x0062f8e0
SharedLibList::~SharedLibList()
{}

// @ 0x0062f920
void cSPPlayModeBGMgr_s0062_f6e0::Shutdown()
{
    if (mBG.size() != 0) {
        uint32_t last = mLastBkgEffectID;
        cSPPlayModeBGInfo* info = mBG.mpBegin[0].mpObject;
        if (GetEffect(last)->f0045b210())
            GetEffect(mLastBkgEffectID)->f0045b150();
        if (!GetEffect(info->mEntryEffectID)->f0045b210()) {
            if (GetEffect(info->mEntryEffectID)->f0045b210())
                GetEffect(info->mEntryEffectID)->f0045ae10(1);
        }
        mLastBkgEffectID = info->mEntryEffectID;
        for (uint32_t i = 0; i < mBG.size(); ++i) {
            AutoRef<cSPPlayModeBGInfo>* slot = &mBG.mpBegin[i];
            cSPPlayModeBGInfo* p = slot->mpObject;
            if (p) {
                slot->mpObject = 0;
                p->Release();
            }
        }
        mBG.erase(mBG.mpBegin, mBG.mpEnd);
    }
}

// @ 0x0062f9f0
void cSPPlayModeBGMgr_s0062_f6e0::LoadBackground(const ResourceKey* key)
{
    AutoRef<PropertyList> props;
    uint32_t entry = 0, thumb = 0, lighting = 0;
    Property* prop;
    uint32_t order = (uint32_t)-1;
    PropertyManager_* mgr = PropertyManager();
    if (props.mpObject) {
        PropertyList* t = props.mpObject;
        props.mpObject = 0;
        t->Release();
    }
    mgr->GetPropertyListEx(key->instance, key->group, &props);
    if (props.mpObject) {
        cSPPlayModeBGInfo* info = new ("Editor", 0, 0, 0, 0) cSPPlayModeBGInfo();
        AutoRef<cSPPlayModeBGInfo> ref(info);
        GetPropertyAsKeyInstance(props.mpObject, 0x3fd7424, &entry);
        GetPropertyAsKeyInstance(props.mpObject, 0x3febc27, &thumb);
        GetPropertyAsKeyInstance(props.mpObject, 0x56bf5d7, &lighting);
        if (props.mpObject && props.mpObject->GetProperty(0x40e7f66, &prop) && prop->type == 9)
            order = *prop->GetInt();
        info->mOrderNumber = order;
        info->mEntryEffectID = entry;
        info->mThumbNailID = thumb;
        info->mLightingID = lighting;
        SPVec<AutoRef<cSPPlayModeBGInfo> >* pv = &mBG;
        AutoRef<cSPPlayModeBGInfo>* end = pv->mpEnd;
        AutoRef<cSPPlayModeBGInfo>* it = pv->mpBegin;
        for (; it != end; ++it) {
            AutoRef<cSPPlayModeBGInfo> cur(*it);
            if (info->mOrderNumber < cur.mpObject->mOrderNumber) {
                pv->insert(it, ref);
                return;
            }
        }
        if (pv->mpEnd < pv->mpCapacity) {
            AutoRef<cSPPlayModeBGInfo>* slot = pv->mpEnd++;
            if (slot)
                new (slot) AutoRef<cSPPlayModeBGInfo>(ref);
        } else {
            pv->DoInsertValueEnd(pv->mpEnd, ref);
        }
    }
}

// @ 0x0062fbc0
void cSPPlayModeBGMgr_s0062_f6e0::LoadAllBGInfoFromGroup(uint8_t group)
{
    ResourceManager_* rm = GetResourceManager();
    KeyArray keys;
    KeyFilter filter(group);
    ResourceKey copy;
    rm->GetKeys(&keys, &filter, 0);
    ResourceKey* end = keys.mpEnd;
    for (ResourceKey* k = keys.mpBegin; k != end; ++k) {
        copy = *k;
        LoadBackground(&copy);
    }
}

// @ 0x0062fc90
void cSPPlayModeBGMgr_s0062_f6e0::Init(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint8_t e)
{
    mUIPtr = (cSPPlayModeUI_s0062_f6e0*)a;
    mChanging = b;
    mLastBkgEffectID = b;
    mEntryEffectID = c;
    mCurrThumbnailNum = 0;
    mCurrBkgEffectID = 0;
    mUI = 0;
    mbChangeInitiated = d;
    LoadAllBGInfoFromGroup(e);
    mPageCount = 0;
    mLightingWorld = 0;
    if (mBG.size() > 0)
        mLightingWorld = (mBG.size() - 1) >> 2;
    if (mLightingWorld > 0)
        mUIPtr->SetUIGroupVisible(0x47ed4c0, true);
    else
        mUIPtr->SetUIGroupVisible(0x47ed4c0, false);
    UpdateBGCountText();
    ShowBGThumbnails();
    mUIPtr->SetUIGroupVisible(0x459b0f0, true);
    mUIPtr->SetUIGroupVisible(0x459b298, false);
    mUIPtr->SetUIGroupVisible(0x459b2d8, false);
    mUIPtr->SetUIGroupVisible(0x459b348, false);
    mb44 = 0;
}

// @ 0x00b1e0c0
int FUN_b1e0c0()
{ return 0; }
