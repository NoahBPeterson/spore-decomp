// Slice s00600260 - cOnlineTab / cGraphicsTab ctor+dtor / cSPUISettings helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE
#include "../s005fa8d0/s005fa8d0.h"

struct ConfigManagerStub {
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  virtual void vt2c(uint32_t id, uint8_t v);       // +0x2c
  virtual uint8_t vt30(uint32_t id);               // +0x30
};
ConfigManagerStub* ConfigManager();   // 0x0067dd30

struct LayoutStub {
  char pad[0x41];
  void* FindWindowByID(uint32_t id, int recurse);  // 0x008105b0
};

struct WinWithIDStub {
  PV(0) PV(1) PV(2)
  virtual void* vt0c(uint32_t id);                 // +0x0c
  PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
  virtual void vt28(int a, bool b);                // +0x28
};

struct OnlineTabStub {
  char pad0[8];
  LayoutStub mLayout;       // +0x8 (0x41 bytes)
  uint8_t mbFlag;           // +0x49
  void DoMessageTab();      // 0x00600260
};

// @ 0x00600260
void OnlineTabStub::DoMessageTab()
{
  ConfigManager()->vt2c(0x5de7b4a, mbFlag);
  mbFlag = ConfigManager()->vt30(0x5de7b4a);
  WinWithIDStub* w = (WinWithIDStub*)mLayout.FindWindowByID(0x5b1cc48, 1);
  if (w) {
    WinWithIDStub* p = (WinWithIDStub*)w->vt0c(0x8ed27e7a);
    if (p) p->vt28(4, mbFlag == 1);
  }
}

// --- skeletons ------------------------------------------------------------------------
void FUN_006002d0() {}
void FUN_006008c0() {}
void FUN_00600ab0() {}
void FUN_00600c00() {}
void FUN_00600da0() {}
void FUN_00600df0() {}
