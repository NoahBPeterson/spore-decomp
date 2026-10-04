// Slice s0062da00 (UI part): SP::cSPPlayModeAnimation and a RefCountVTemplate-derived class with a cString.
// Compiled without /arch:SSE (x87 float copies) and without /EHsc.
#include "types.h"

namespace EA { }
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
};

// ---- cString-owning refcounted class (vtable 0x013fe308) ----
class cNamedRefCount : public RefCountVTemplate {
 public:
  uint32_t pad[13];
  cString mName;      // +0x3c
  virtual ~cNamedRefCount();
};

// @ 0x0062e2b0
cNamedRefCount::~cNamedRefCount() {}

// ---- animation panel ----
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
extern const wchar_t kTooltipsName[];      // 0x13f6a90
struct GlobalPageInfo { uint32_t pad[10]; uint32_t pageCount; uint32_t field; };  // +0x28, +0x2c
extern GlobalPageInfo* gPageInfo;          // 0x015f7cf4

struct AnimController;   // object at creature+0x184
struct AnimSlot;
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
struct AnimSlot { uint32_t pad[0x36]; uint32_t mAnimID; };   // +0xd8
void* FUN_009ff6f0(AnimController* ctl, uint32_t handle);
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

// @ 0x0062e4b0
int cSPPlayModeAnimation::GetAnimCount() {
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
bool cSPPlayModeAnimation::GetExpansionAnimInfo(int buttonId, uint32_t* id, uint32_t* babyId,
                                                float* speed, float* delay) {
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
bool cSPPlayModeAnimation::IsExtraAnims() {
  bool r = GetAnimCount() != 0;
  return r;
}

// @ 0x0062e600
void cSPPlayModeAnimation::UpdatePageCount() {
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
void cSPPlayModeAnimation::Activate() {
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
void cSPPlayModeAnimation::ResetCurAnimWindow() {
  mUI->SetUIGroupVisible(0x4864e80, false);
  if (GetAnimCount() != 0) mUI->SetUIGroupVisible(0x4864e88, true);
  mPageCount = 0;
}

// @ 0x0062e2e0
float cSPPlayModeAnimation::StartNewAnimation(uint32_t creatureId, uint32_t anim, bool flag,
                                              uint32_t param, uint32_t* outHandle) {
  EditorBase* eb = mEditorBase;
  uint32_t cid = creatureId;
  CreatureStructure* cs = eb->mgr->GetCreatureStructure(cid);
  if (cs != 0) {
    AnimatingCreature* c = cs->mCreature;
    if (c != 0) {
      if (c->IsMoveIdleAnim(anim)) {
        AnimSlot* slot = (AnimSlot*)FUN_009ff6f0(c->mController, c->mCurHandle);
        if (slot == 0 || slot->mAnimID != anim) {
          uint32_t h = c->CreateAnim(anim, 0);
          c->mCurHandle = h;
          c->SetAnimParam(h, param);
          c->Start(c->mCurHandle);
        }
        if (slot != 0 && slot->mAnimID != anim) c->mController->FUN_00a00f90(slot, 0);
        if (flag) {
          c->SetLooping(c->mCurHandle, 1);
          c->SetBlend(c->mCurHandle, -1.0f);
        }
        if (outHandle != 0) *outHandle = c->mCurHandle;
      } else {
        uint32_t h = c->CreateAnim(anim, 0);
        c->SetAnimParam(h, param);
        c->Start(h);
        if (flag) {
          c->SetLooping(h, 1);
          c->SetBlend(h, -1.0f);
        }
        if (outHandle != 0) *outHandle = h;
        if (!c->FUN_00a02800(anim)) {
          c->mController->FUN_00a01f10(c->mFadeOutHandle, 0);
          c->mController->FUN_00a01f10(c->mCurHandle, 0);
        }
        cs->FUN_007cd950(anim);
      }
      mCurrAnimID = anim;
      return cs->mCreature->GetAnimLength(anim);
    }
  }
  if (outHandle != 0) *outHandle = 0;
  return -1.0f;
}
