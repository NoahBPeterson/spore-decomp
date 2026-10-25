// Slice s005e6b40: SP::cSPEditorVerbIconTray.  CheckMessage, Update and SetBaseStat are
// reconstructed; the large DoMessage/SetLevelText/Shutdown and the EASTL vector helpers are
// stubbed (see partial.txt).  Layout follows the retail binary (see Update/SetBaseStat).
#include <string.h>
#include "types.h"

#define PV(n) virtual void _pv##n();

// Float constants in the original's .rdata.
extern const float gSecondsScale;   // 0x013f9428 (0.001f)
extern const float gDampenLimit;    // 0x013eb95c (3.0f)
extern const float gDampenMax;      // 0x013f9624 (0.7f)
extern const float gDampenScale;    // 0x013f967c (0.15555555f)
extern const float gDampenBias;     // 0x013f9678 (0.23333333f)

// Editor debug allocator: operator new(size, name, flags, debugFlags, file, line) at 0x00f473a0.
void* operator new(unsigned int size, const char* name, int flags, int debugFlags,
                   const char* file, int line);
extern "C" void operator_delete_editor(void* p);        // 0x00f47380
extern unsigned char kEditorAllocName[];                 // 0x013eb430 ("Editor")
extern unsigned char kEditorAllocFile[];                 // 0x013ebb38 (".../EASTL/allocator.h")

// The tray's level-text routine is still a skeleton in this slice; Update/SetBaseStat call the
// original through a proxy with the same thiscall signature (this in ECX, float on the stack,
// callee pops it -> ret 4). A __fastcall stub would clobber EDX, which the original leaves alone.
class cTrayLevelTextCall {
 public:
  void SetLevelText(float level);  // 0x005e7030
};

namespace Math {
struct Rectangle {
  float x1, y1, x2, y2;
  float Width() const { return x2 - x1; }
  float Height() const { return y2 - y1; }
};
}  // namespace Math

namespace EA {
namespace UTFWin {
class IWinProc;

class IWindow {
 public:
  virtual int AddRef();   // +0x00
  virtual int Release();  // +0x04
  PV(2) PV(3) PV(4)
  PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13)
  virtual const Math::Rectangle& GetArea();  // +0x38
  PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23)
  virtual void SetArea(const Math::Rectangle& area);  // +0x60
  PV(25) PV(26) PV(27) PV(28) PV(29) PV(30) PV(31) PV(32) PV(33)
  virtual void AddWindow(IWindow* w);     // +0xd8
  virtual void RemoveWindow(IWindow* w);  // +0xdc
};

class IWinProc {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
};
}  // namespace UTFWin
}  // namespace EA

using EA::UTFWin::IWindow;
using EA::UTFWin::IWinProc;

namespace SP {
class cSPEditorVerbIconTray;

// eastl::basic_string<wchar_t> sub-object (four words: begin, end, cap, allocator).
class cEAWString16 {
 public:
  void* mpBegin;       // +0x00
  void* mpEnd;         // +0x04
  void* mpCap;         // +0x08
  void* mpAllocator;   // +0x0c
  void range_initialize(const wchar_t* s);   // 0x00579a90
};

// An object that owns a window/image group used while laying out the rollover.
class cSPVerbIconRollover {
 public:
  PV(0)
  virtual int Release();  // +0x04
  PV(2) PV(3) PV(4) PV(5) PV(6) PV(7)
  virtual void v20();  // +0x20
  PV(9)
  virtual void v24();  // +0x24
  void MarkDirty();
};

// The tray's icon-key / property holder (+0x40) and its data holder (+0x20).
class cSPVerbIconKey {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6)
  virtual bool HasProperty(int key);         // +0x1c
};

class cSPVerbIconData20 {
 public:
  char   pad00[0x18];
  float  mScaledLevel;     // +0x18
  char   pad1c[0x04];
  float  mBaseLevel;       // +0x20
  char   pad24[0x9c];
  void*  mpExtra;          // +0xc0
};

class cSPEditorVerbIconData {
 public:
  PV(0) PV(1) PV(2)
  virtual void* GetProperty(uint32_t id);  // +0x0c
};

class cSPEditorVerbIcon {
 public:
  virtual int AddRef();                     // +0x00
  virtual int Release();                    // +0x04
  PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
  virtual void LayoutShutdown();            // +0x28
  virtual bool SetAnimationTime(float t);   // +0x2c
  void* GetData();                          // 0x005e2d00
  float GetLevel(bool scaled);              // 0x005e2860
  int GetState();                           // 0x005e1fc0
  IWindow* GetWindow();                     // 0x007f54d0
  void UpdateRollover(IWindow* parent);
  void RefreshLevel();
};

// Generic object with the vtable slots the tray's level/teardown code touches.
struct IRefObj28 {
  PV(0)
  virtual void Rel();         // +0x04
  virtual void v8();          // +0x08
  PV(3) PV(4)
  virtual void v14();         // +0x14
  PV(6)
  virtual bool v1c(int key);  // +0x1c
  PV(8)
  virtual void v24();         // +0x24
  virtual void v28();         // +0x28
  PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
  PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30)
  virtual void SetFlag(int flag, bool value);  // +0x7c
  virtual void v80(void* text);                // +0x80
};

class cSPUILayout : public IRefObj28 {
 public:
  void Shutdown(unsigned flags);   // 0x00811ad0
};

// The tray's mVerbIcons vector (element = cSPEditorVerbIcon*).
class cVerbIconVector {
 public:
  cSPEditorVerbIcon** mpBegin;  // +0x00
  cSPEditorVerbIcon** mpEnd;    // +0x04
  cSPEditorVerbIcon** mpCap;    // +0x08

  void** DoAllocate(unsigned count, const unsigned char* value,
                    unsigned allocHint);                            // 0x005e7390
  void DoInsert(cSPEditorVerbIcon** pos, unsigned n,
                cSPEditorVerbIcon** value);                       // 0x005e7400
  void Resize(unsigned count);                                    // 0x005e77e0
  void Erase(cSPEditorVerbIcon** first, cSPEditorVerbIcon** last);  // 0x00e25bd0
};

// EASTL helpers referenced by the vector routines (addresses masked at match time).
extern "C" void FUN_00829110(...);
extern "C" void FUN_00ac97a0(...);
extern "C" void FUN_00ea0350(...);
extern "C" void FUN_00b2ac90(...);
extern "C" void FUN_006b54b0(...);   // cString::Load
extern "C" void FUN_006b55c0(...);   // cString::GetText
extern "C" void FUN_006a1360(...);   // SP::GetPropertyAsText
extern "C" void FUN_0041e050(...);   // eastl::wstring::sprintf (WStr_Format)
extern "C" void FUN_007f54d0(...);   // cSPEditorVerbIcon::GetWindow
extern "C" void FUN_00828c30(...);   // cSPVerbIconRollover::SetProperty
extern "C" void FUN_006052c0(...);   // cSPVerbIconRollover::SetVisibility
extern "C" void FUN_006052f0(...);   // cSPVerbIconRollover::SetPositionFromIcon
extern "C" void FUN_008283a0(...);   // cSPUIPropertyLayout::SetPositionAndOffset
extern "C" void FUN_00579a90(...);   // eastl::wstring::range_initialize
extern "C" void FUN_0093dd80(...);   // EA::Variant::Construct
extern "C" void FUN_0093db80(...);   // EA::Variant::Destruct

// Locale scratch object (DAT_015ee298) and shared empty-string data.
extern char   g_015ee298[];          // EA::Locale singleton
extern wchar_t g_01667bac[];
extern wchar_t g_01667bae[];
extern const wchar_t g_013f01bc[];   // L"%d"-style level format string

// DoMessage helpers: tray name/description getters, Variant plumbing, window manager.
extern "C" void FUN_005e6a60(...);   // GetTrayName
extern "C" void FUN_005e6ae0(...);   // GetTrayDescription
extern "C" void FUN_006b5060(...);   // cString::cString
extern "C" void FUN_006052d0(...);   // SP_cSPVerbIconRollover_Layout
extern "C" void FUN_006052e0(...);   // rollover vtable +0x20
extern "C" void* FUN_00605300(...);  // mWinIcon vtable +0x38 (group part)
extern "C" void FUN_00605310(...);   // group part vtable +0xc0 (GetRect)
extern "C" void* FUN_00605320(...);  // window manager vtable +0x04 (screen)
extern "C" Math::Rectangle& FUN_00605330(...);  // screen vtable +0x34 (GetArea)
extern "C" void* FUN_0067caa0(...);  // SP::WindowManager
extern "C" void PublishVariant(...); // eastl::wstring -> EA::Variant property
extern "C" void VariantCleanup(...);
extern "C" int atexit(void (*)());

// Lazily-built shared "unset level" string (initialized in DoMessage).
extern unsigned int g_015f03fc;
extern cEAWString16 g_015f03ec;
extern void g_013bd680();

// The property object's "set the level text" call (vtable +0x80).
extern "C" void IRefObj_v80(IRefObj28* self, void* text);

class cSPEditorVerbIconTray : public IWinProc {
 public:
  struct cVerbIconInterpolationValue {
    float mTargetValue;   // +0x00
    float mCurrentValue;  // +0x04
    float mRate;          // +0x08
    float mZero0c;        // +0x0c
    float mZero10;        // +0x10
    float mZero14;        // +0x14
    float mZero18;        // +0x18
    void Init(float a, float b, float c, float d, float e);  // 0x005e1c80
    int IsAtTarget();                                        // 0x005e1cd0
    void Advance(float dt);                                  // 0x005e1d00
  };

  // vtable slots 9.. (after the IWinProc slots)
  PV(9) PV(10) PV(11) PV(12) PV(13) PV(14)
  virtual void LayoutTray();  // +0x3c

  char pad00[0x08];                       // +0x04 vptr/pad
  cSPEditorVerbIcon** mpVerbIconBegin;  // +0x0c
  cSPEditorVerbIcon** mpVerbIconEnd;    // +0x10
  char pad14[0x0c];                     // +0x14
  cSPVerbIconData20* mpProp20;          // +0x20
  cSPEditorVerbIcon* mpOwner;  // +0x24
  IRefObj28* mpLayout28;                // +0x28
  IRefObj28* mpProp2c;                  // +0x2c
  IWindow* mWinIconPanel;  // +0x30
  IRefObj28* mpProp34;                  // +0x34
  IWindow* mWinIcon;  // +0x38
  char pad3c[0x04];                     // +0x3c
  cSPVerbIconKey* mpProp40;             // +0x40
  char pad44[0x2d];                     // +0x44
  bool mAnimateIcons;  // +0x71
  char pad72[0x16];                     // +0x72
  float mLevelTotal;                    // +0x88
  char pad8c[0x04];                     // +0x8c
  bool mShowLevel;                      // +0x90
  bool mFlag91;                         // +0x91
  bool mFlag92;                         // +0x92
  bool mFlag93;                         // +0x93
  char pad94[0x08];                     // +0x94
  float mDisplayedLevel;                // +0x9c
  char padA0[0x39];                     // +0xa0
  bool mOverrideAggregate;  // +0xd9
  char padDa[0x16];
  cVerbIconInterpolationValue mBaseStat;  // +0xf0
  bool mShowRollover;                     // +0x10c
  char pad10d[0x03];
  cSPVerbIconRollover* mRollover;  // +0x110
  void* mpProp114;                       // +0x114

  bool CheckMessage(IWindow* w, void* msg);
  void DoMessage(IWindow* w);
  void SetLevelText(float level);
  bool Update(float dt);
  void SetBaseStat(float value);
  void Shutdown();
};

// @ 0x005e6fb0
bool cSPEditorVerbIconTray::CheckMessage(IWindow* w, void* msg) {
  if (*(int*)((char*)msg + 8) == 10 && *(int*)((char*)msg + 0xc) == 1) {
    IWindow* target = *(IWindow**)((char*)msg + 0x18);
    if (target == mWinIcon) {
      if (mShowRollover && mRollover) {
        if (mpOwner) {
          mpOwner->UpdateRollover(w);
          return false;
        } else {
          DoMessage(w);
          return false;
        }
      }
    } else {
      if (mRollover)
        mRollover->MarkDirty();
      if (mpOwner)
        mpOwner->RefreshLevel();
    }
  }
  return false;
}

// @ 0x005e6b40
void cSPEditorVerbIconTray::DoMessage(IWindow* w) {
  (void)w;
  // The tray name comes back as an eastl::wstring, then becomes a Variant property.
  cEAWString16 name;
  FUN_005e6a60(this, &name, 0);  // GetTrayName(0)

  // Publish property 0x331cc0e = tray name.
  void* propVar = 0;
  PublishVariant(propVar, &name, 0, 1);
  FUN_00828c30(0x331cc0e, &propVar, 1, 0);
  VariantCleanup(&propVar);
  if (((int)((char*)name.mpCap - (char*)name.mpBegin) & ~1) > 2 && name.mpBegin) {
    operator_delete_editor(name.mpBegin);
  }

  cEAWString16 text;
  FUN_006b5060(&text);  // cString::cString (placeholder text)

  if (!mFlag91) {
    // Cold path: lazily build the shared "unset" level string once.
    if ((g_015f03fc & 1) == 0) {
      g_015f03fc |= 1;
      g_015f03ec.mpBegin = (void*)g_01667bac;
      g_015f03ec.mpEnd = (void*)g_01667bac;
      g_015f03ec.mpCap = (void*)g_01667bae;
      atexit((void (*)())g_013bd680);
    }
    void* v2 = 0;
    PublishVariant(v2, &g_015f03ec, 0, 1);
    FUN_00828c30(0x4d97708, &v2, 1, 0);
    VariantCleanup(&v2);
  } else {
    int rounded;
    if (!mFlag93 || mpLayout28 == 0) {
      if (!mFlag92 || mpLayout28 == 0) {
        rounded = (int)mLevelTotal;
      } else {
        rounded = (int)*(float*)(g_015ee298 + 0x20);
        *(int*)(g_015ee298 + 0x58) = rounded;
      }
    } else {
      rounded = (int)*(float*)((char*)mpLayout28 + 0x20);
      *(int*)(g_015ee298 + 0x58) = rounded;
    }

    if (mpProp40->HasProperty(0x62d00e8)) {
      FUN_006a1360(mpProp40, 0x62d00e8, &text);
    } else if (mpProp20 != 0 && mpProp20->mpExtra != 0) {
      FUN_006a1360(mpProp20->mpExtra, 0x62d00e8, &text);
    }

    cEAWString16 desc;
    FUN_005e6ae0(this, &desc, &text);  // GetTrayDescription(text)
    void* v3 = 0;
    PublishVariant(v3, &desc, 0, 1);
    FUN_00828c30(0x4d97708, &v3, 1, 0);
    VariantCleanup(&v3);
    if (((int)((char*)desc.mpCap - (char*)desc.mpBegin) & ~1) > 2 && desc.mpBegin) {
      operator_delete_editor(desc.mpBegin);
    }
  }

  if (mpProp40->HasProperty(0x4acedf9)) {
    cEAWString16 d2;
    FUN_005e6ae0(this, &d2, &text);
    void* v4 = 0;
    PublishVariant(v4, &d2, 0, 1);
    FUN_00828c30(0x331cc0f, &v4, 1, 0);
    VariantCleanup(&v4);
    if (((int)((char*)d2.mpCap - (char*)d2.mpBegin) & ~1) > 2 && d2.mpBegin) {
      operator_delete_editor(d2.mpBegin);
    }
  }

  // Position the rollover over the tray's icon group.
  FUN_006052c0(mRollover, 0x4d97710, 0);
  FUN_006052e0(mRollover, 0x20);  // rollover vtable +0x20
  FUN_006052d0(mRollover);        // SP_cSPVerbIconRollover_Layout

  const Math::Rectangle& iconArea = mWinIcon->GetArea();
  void* groupPart = FUN_00605300(mWinIcon);  // mWinIcon vtable +0x38
  Math::Rectangle tmp;
  FUN_00605310(groupPart, &tmp, (iconArea.x2 + iconArea.x1) * 0.5f,
               (iconArea.y2 + iconArea.y1) * 0.5f);  // groupPart vtable +0xc0

  void* wm = FUN_0067caa0();                    // SP::WindowManager
  void* screen = FUN_00605320(wm);              // wm vtable +0x04
  const Math::Rectangle& scr = FUN_00605330(screen);  // screen vtable +0x34
  float sx = scr.x1, sy = scr.y1, sx2 = scr.x2, sy2 = scr.y2;
  FUN_006052f0(mRollover);
  FUN_008283a0(mRollover, (int)sx2, (int)sy2, (sx2 - sx) * 0.025f, (sy2 - sy) * 0.033333335f);
}

// @ 0x005e7030
void cSPEditorVerbIconTray::SetLevelText(float level) {
  if (mpProp34 == 0) return;
  if (level == mDisplayedLevel) return;

  cEAWString16 text;
  if (mFlag92 != 0) {
    // Non-default style: build the localized level string.
    FUN_006b5060(&text);  // cString::cString
    int rounded = (int)level;
    *(int*)(g_015ee298 + 0x58) = rounded;
    FUN_006b54b0(&text, 0x7153bbb1, 0x642c770, 0);
  } else {
    if (mpProp40->HasProperty(0x64927c9)) {
      FUN_006b5060(&text);
      int rounded = (int)level;
      *(int*)(g_015ee298 + 0x58) = rounded;
      FUN_006a1360(mpProp40, 0x64927c9, &text);
    } else {
      text.mpBegin = (void*)g_01667bac;
      text.mpEnd = (void*)g_01667bac;
      text.mpAllocator = 0;
      text.mpCap = (void*)g_01667bae;
      FUN_0041e050(&text, g_013f01bc, (int)level);
      ((IRefObj28*)mpProp34)->v80(text.mpBegin);
      text.mpBegin = (void*)g_01667bac;
      text.mpEnd = (void*)g_01667bac;
      text.mpCap = (void*)g_01667bae;
    }
  }
  // Hand the assembled text to the property list's window (+0x80).
  ((IRefObj28*)mpProp34)->v80(mpProp34);
  if (((int)((char*)text.mpCap - (char*)text.mpBegin) & ~1) > 2 && text.mpBegin) {
    operator_delete_editor(text.mpBegin);
  }
  mDisplayedLevel = level;
  ((IRefObj28*)mpProp34)->SetFlag(1, mShowLevel);
}

// @ 0x005e71d0
bool cSPEditorVerbIconTray::Update(float dt) {
  float fdt = (float)*(uint32_t*)&dt * gSecondsScale;
  bool changed = false;
  float level = 0.0f;
  int count = (int)(mpVerbIconEnd - mpVerbIconBegin);
  for (int i = 0; i < count; ++i) {
    cSPEditorVerbIcon* icon = mpVerbIconBegin[i];
    if (icon) {
      bool flag = icon->SetAnimationTime(dt);
      cSPEditorVerbIconData* data = (cSPEditorVerbIconData*)icon->GetData();
      void* prop = 0;
      if (data) prop = data->GetProperty(0x4ac90b5);
      void* holder = 0;
      if (prop) holder = *(void**)((char*)prop + 0xc4);
      float v;
      if (holder) {
        v = icon->GetLevel(true) * *(float*)((char*)holder + 0x110);
      } else {
        v = icon->GetLevel(true);
      }
      level = level + v;
      changed = changed || flag;
      if (icon->GetState() == 1) {
        mWinIconPanel->RemoveWindow(icon->GetWindow());
        icon->LayoutShutdown();
        if (icon) {
          mpVerbIconBegin[i] = 0;
          icon->Release();
        }
        changed = true;
      }
    }
  }
  if (mOverrideAggregate) {
    if (mAnimateIcons) {
      if (!mBaseStat.IsAtTarget()) mBaseStat.Advance(fdt);
    }
    level = mBaseStat.mCurrentValue;
  }
  ((cTrayLevelTextCall*)this)->SetLevelText(level);
  if (changed) LayoutTray();
  return changed;
}

// @ 0x005e75c0
void cSPEditorVerbIconTray::SetBaseStat(float value) {
  bool animate = mAnimateIcons;
  mOverrideAggregate = true;
  if (!animate) {
    mBaseStat.Init(value, value, 0.0f, 0.0f, 0.0f);
    ((cTrayLevelTextCall*)this)->SetLevelText(value);
    return;
  }
  float cur = mBaseStat.mCurrentValue;
  double d = (double)value - (double)cur;
  if (d < 0.0) d = -d;
  float diff = (float)d;
  float rate;
  if ((double)gDampenLimit > d) {
    rate = diff * gDampenScale + gDampenBias;
  } else {
    rate = gDampenMax;
  }
  if (value != mBaseStat.mTargetValue) {
    mBaseStat.Init(cur, value, rate, 0.0f, 0.0f);
    ((cTrayLevelTextCall*)this)->SetLevelText(mBaseStat.mCurrentValue);
  }
}

// @ 0x005e76b0
void cSPEditorVerbIconTray::Shutdown() {
  // Detach the shared ability array (release under +0x110).
  if (mRollover != 0) {
    mRollover->v24();
    if (mRollover != 0) {
      cSPVerbIconRollover* p = mRollover;
      mRollover = 0;
      p->Release();
    }
  }
  // Tear down the level layout (+0x28), then release it.
  if (mpLayout28 != 0) {
    ((cSPUILayout*)mpLayout28)->Shutdown(1);
    if (mpLayout28 != 0) {
      IRefObj28* p = mpLayout28;
      mpLayout28 = 0;
      p->v8();
    }
  }
  // Release each verb icon.
  unsigned int n = (unsigned int)(mpVerbIconEnd - mpVerbIconBegin) >> 2;
  for (unsigned int i = 0; i < n; ++i) {
    cSPEditorVerbIcon* icon = mpVerbIconBegin[i];
    if (icon != 0) icon->LayoutShutdown();
  }
  // Release the tray properties (+0x20), then free the raw representative blob (+0x114).
  if (mpProp20 != 0) {
    ((IRefObj28*)mpProp20)->v14();
    if (mpProp20 != 0) {
      IRefObj28* p = (IRefObj28*)mpProp20;
      mpProp20 = 0;
      p->Rel();
    }
  }
  if (mpProp114 != 0) {
    operator_delete_editor(mpProp114);
    mpProp114 = 0;
  }
  // Reset the icon vector.
  cVerbIconVector* vec = (cVerbIconVector*)&mpVerbIconBegin;
  vec->Erase(vec->mpBegin, vec->mpEnd);
  if (mpProp2c != 0) {
    IRefObj28* p = mpProp2c;
    mpProp2c = 0;
    p->Rel();
  }
  if (mpProp34 != 0) {
    IRefObj28* p = mpProp34;
    mpProp34 = 0;
    p->Rel();
  }
  if (mWinIcon != 0) {
    IRefObj28* p = (IRefObj28*)mWinIcon;
    mWinIcon = 0;
    p->Rel();
  }
  if (mWinIconPanel != 0) {
    IRefObj28* p = (IRefObj28*)mWinIconPanel;
    mWinIconPanel = 0;
    p->Rel();
  }
  if (mpProp40 != 0) {
    IRefObj28* p = (IRefObj28*)mpProp40;
    mpProp40 = 0;
    p->Rel();
  }
}

// @ 0x005e7390
void** cVerbIconVector::DoAllocate(unsigned int count, const unsigned char* value,
                                   unsigned int allocHint) {
  (void)allocHint;
  char* p;
  if (count) {
    p = (char*)operator new(count, (const char*)kEditorAllocName, 0, 0,
                           (const char*)kEditorAllocFile, 0xd1);
  } else {
    p = 0;
  }
  const unsigned char* v = value;
  mpBegin = (cSPEditorVerbIcon**)p;
  mpEnd = (cSPEditorVerbIcon**)p;
  mpCap = (cSPEditorVerbIcon**)(p + count);
  if (count > 0u) {
    unsigned char fill = *v;
    memset(p, fill, count);
  }
  mpEnd = (cSPEditorVerbIcon**)((char*)mpBegin + count);
  return (void**)this;
}

// @ 0x005e7400
void cVerbIconVector::DoInsert(cSPEditorVerbIcon** pos, unsigned int n,
                               cSPEditorVerbIcon** value) {
  unsigned int freeTail = (unsigned int)(mpCap - mpEnd) >> 2;
  if (n > freeTail) {
    // Grow: allocate a new block, copy head, fill interior, copy tail.
    unsigned int cur = (unsigned int)(mpEnd - mpBegin) >> 2;
    unsigned int want = cur + n;
    unsigned int grown = (cur << 1) | 1u;
    if (want < grown) want = grown;
    cSPEditorVerbIcon** fresh;
    if (want == 0) {
      fresh = 0;
    } else {
      fresh = (cSPEditorVerbIcon**)operator new(want * 4, (const char*)kEditorAllocName, 0, 0,
                                                (const char*)kEditorAllocFile, 0xd1);
    }
    unsigned char* head = (unsigned char*)fresh;
    unsigned int headBytes = (unsigned int)((unsigned char*)pos - (unsigned char*)mpBegin);
    FUN_00b2ac90(head, (unsigned char*)mpBegin, headBytes);          // move head (uninit copy)
    unsigned char* fillAt = head + headBytes;
    unsigned int i = 0;
    for (; i < n; ++i) {
      cSPEditorVerbIcon* v = *value;
      *(cSPEditorVerbIcon**)(fillAt + i * 4) = v;
      if (v) v->AddRef();
    }
    unsigned char* tailAt = fillAt + n * 4;
    unsigned int tailBytes = (unsigned int)((unsigned char*)mpEnd - (unsigned char*)pos);
    FUN_00ac97a0(tailAt, (unsigned char*)pos, tailBytes);            // move tail (uninit copy)
    if (mpBegin && *(int*)((char*)mpBegin - 4) != 0) {
      operator_delete_editor(mpBegin);
    }
    mpBegin = fresh;
    mpCap = (cSPEditorVerbIcon**)((char*)fresh + want * 4);
    mpEnd = (cSPEditorVerbIcon**)((char*)fresh + headBytes + n * 4 + tailBytes);
    return;
  }
  if (n == 0) return;

  cSPEditorVerbIcon* v = *value;
  if (v) v->AddRef();

  unsigned int after = (unsigned int)(mpEnd - pos) >> 2;
  if (n < after) {
    cSPEditorVerbIcon** oldEnd = mpEnd;
    unsigned int tailElems = after - n;
    // Move the trailing elements one n-slot block to the right.
    FUN_00829110(mpEnd, mpEnd - n, tailElems);                        // shift back (overlap)
    mpEnd += n;
    FUN_00ea0350(pos + n, pos, oldEnd);                               // copy old [pos,oldEnd) to +n
    FUN_00ea0350(pos, pos, (cSPEditorVerbIcon**)((char*)pos + n * 4));  // fill the gap with v
    return;
  }

  // Fill the free tail, shift the tail, then fill the gap.
  unsigned int grownElems = n - after;
  cSPEditorVerbIcon** w = mpEnd;
  for (unsigned int i = 0; i < grownElems; ++i) {
    cSPEditorVerbIcon* vv = *value;
    *w++ = vv;
    if (vv) vv->AddRef();
  }
  mpEnd = w;
  FUN_00ea0350(pos + n, pos, mpEnd);                                  // copy [pos,mpEnd) to +n
  mpEnd += after;
  FUN_00ea0350(pos, pos, mpEnd);
}

// @ 0x005e77e0
void cVerbIconVector::Resize(unsigned int count) {
  cSPEditorVerbIcon** begin = mpBegin;
  cSPEditorVerbIcon** end = mpEnd;
  int cur = (int)((char*)end - (char*)begin) >> 2;
  if (count > (unsigned int)cur) {
    cSPEditorVerbIcon* fill = 0;
    DoInsert(end, count - (unsigned int)cur, &fill);
  } else {
    Erase(begin + count, end);
  }
}

}  // namespace SP
