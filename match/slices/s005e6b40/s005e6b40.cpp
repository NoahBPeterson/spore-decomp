// Slice s005e6b40: SP::cSPEditorVerbIconTray.  Only the message handler is fully
// reconstructed; the large DoMessage/Update/SetLevelText/Shutdown and the EASTL vector
// helpers are stubbed (see partial.txt).  Layout from match/slices/s005e5d40.
#include "types.h"

#define PV(n) virtual void _pv##n();

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

class cSPEditorVerbIcon {
 public:
  PV(0)
  virtual int Release();
  void UpdateRollover(IWindow* parent);
  void RefreshLevel();
};

class cSPEditorVerbIconTray : public IWinProc {
 public:
  char pad00[0x20];
  cSPEditorVerbIcon* mpOwner;  // +0x24
  char pad28[0x10];
  IWindow* mWinIcon;            // +0x38
  char pad3c[0xd0];
  bool mShowRollover;           // +0x10c
  char pad10d[3];
  cSPVerbIconRollover* mRollover;  // +0x110

  bool CheckMessage(IWindow* w, void* msg);
  void DoMessage(IWindow* w);
  void SetLevelText(float level);
  void Update(float dt);
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
void cSPEditorVerbIconTray::Update(float dt) { (void)dt; }

// @ 0x005e75c0
void cSPEditorVerbIconTray::SetBaseStat(float value) { (void)value; }

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
