// Slice s005e6b40: SP::cSPEditorVerbIconTray.  CheckMessage, Update and SetBaseStat are
// reconstructed; the large DoMessage/SetLevelText/Shutdown and the EASTL vector helpers are
// stubbed (see partial.txt).  Layout follows the retail binary (see Update/SetBaseStat).
#include "types.h"

#define PV(n) virtual void _pv##n();

// Float constants in the original's .rdata.
extern const float gSecondsScale;   // 0x013f9428 (0.001f)
extern const float gDampenLimit;    // 0x013eb95c (3.0f)
extern const float gDampenMax;      // 0x013f9624 (0.7f)
extern const float gDampenScale;    // 0x013f967c (0.15555555f)
extern const float gDampenBias;     // 0x013f9678 (0.23333333f)

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

class cSPVerbIconRollover {
 public:
  PV(0)
  virtual int Release();  // +0x04
  void MarkDirty();
};

class cSPEditorVerbIconData {
 public:
  PV(0) PV(1) PV(2)
  virtual void* GetProperty(uint32_t id);  // +0x0c
};

class cSPEditorVerbIcon {
 public:
  PV(0)
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

  char pad00[0x08];
  cSPEditorVerbIcon** mpVerbIconBegin;  // +0x0c
  cSPEditorVerbIcon** mpVerbIconEnd;    // +0x10
  char pad14[0x10];
  cSPEditorVerbIcon* mpOwner;  // +0x24
  char pad28[0x08];
  IWindow* mWinIconPanel;  // +0x30
  char pad34[0x04];
  IWindow* mWinIcon;  // +0x38
  char pad3c[0x35];
  bool mAnimateIcons;  // +0x71
  char pad72[0x67];
  bool mOverrideAggregate;  // +0xd9
  char padDa[0x16];
  cVerbIconInterpolationValue mBaseStat;  // +0xf0
  bool mShowRollover;                     // +0x10c
  char pad10d[3];
  cSPVerbIconRollover* mRollover;  // +0x110

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
void cSPEditorVerbIconTray::DoMessage(IWindow* w) { (void)w; }

// @ 0x005e7030
void cSPEditorVerbIconTray::SetLevelText(float level) { (void)level; }

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
void cSPEditorVerbIconTray::Shutdown() {}

// The three routines at 005e7390/005e7400/005e77e0 are EASTL vector helpers; stubbed here.
// @ 0x005e7390
void* VectorDoAllocate(void* dst, unsigned int count, const unsigned char* value) {
  (void)dst;
  (void)count;
  (void)value;
  return 0;
}

// @ 0x005e7400
void VectorDoInsert(void* out, unsigned int count, void* value) {
  (void)out;
  (void)count;
  (void)value;
}

// @ 0x005e77e0
void VectorResize(void* self, unsigned int count) {
  (void)self;
  (void)count;
}
}  // namespace SP
