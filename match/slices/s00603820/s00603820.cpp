// Slice s00603820 - cGraphicsTab / cSPUISettings settings persistence + message handling.
// Flags: /O2 /MD /Gy /TP /arch:SSE
#include "../s005fa8d0/s005fa8d0.h"

struct ConfigManagerStub14 {
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14)
  virtual void vt3c();                     // +0x3c
};
ConfigManagerStub14* ConfigManager();      // 0x0067dd30

struct Sub10c { void Save(); };            // 0x00603de0
struct cSPUISettings14 {
  char pad0[0x10c];
  Sub10c mSub;                             // +0x10c
  void SaveOnlineSettings();               // 0x005ff850
  void SaveAllSettings();                  // 0x00604860
};

// @ 0x00604860
void cSPUISettings14::SaveAllSettings()
{
  mSub.Save();
  SaveOnlineSettings();
  if (ConfigManager())
    ConfigManager()->vt3c();
}

// ---- 006041f0: cSPUISettings::HandleMessage --------------------------------------------
struct SubFC { char pad[4]; void A(); };    // 0x00603fe0
struct Sub1A0 { char pad[4]; void B(); };   // 0x00600180
struct SettingsForHandler {
  char pad0[0x14];
  void* mpLayout;                          // +0x14
  char pad18[0x10c - 0x18];
  SubFC mFC;                               // +0x10c
  char pad110[0x1b0 - 0x110];
  Sub1A0 m1A0;                             // +0x1b0 (settings-relative)
  bool Shutdown();                         // 0x00601e60
};
void EndModal(void* w, int a, int b);      // 0x00809c50
struct LayoutModal { void* FindWindowByID(uint32_t id, int rec); };
struct Handler14 {
  char pad0[4];
  void* mpLayout;                          // +0x4
  bool HandleMessage(uint32_t msg, void* unused);
};

// @ 0x006041f0
bool Handler14::HandleMessage(uint32_t msg, void* unused)
{
  if (msg == 0x238de9c) {
    if (mpLayout) {
      EndModal(((LayoutModal*)mpLayout)->FindWindowByID(0x43c8b98, 1), 0, 0);
    }
    ((SettingsForHandler*)((char*)this - 0x10))->Shutdown();
    return true;
  }
  if (msg == 0x62752d3) {
    ((SettingsForHandler*)((char*)this - 0x10))->mFC.A();
    ((SettingsForHandler*)((char*)this - 0x10))->m1A0.B();
    return true;
  }
  return false;
}

// ---- 00603f10 / 00603fe0: cGraphicsTab checkbox<->canvas sync ---------------------------
struct WinA14 {
  PV(0) PV(1) PV(2)
  virtual void* vt0c(uint32_t id);                       // +0x0c
  PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15)
  PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27)
  PV(28) PV(29) PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39)
  PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46) PV(47) PV(48) PV(49) PV(50) PV(51)
  PV(52) PV(53) PV(54) PV(55) PV(56) PV(57) PV(58) PV(59)
  virtual void* vtf0(uint32_t id, int b);                // +0xf0
};
struct Obj14 {
  virtual void vt0();                                    // +0x00
  virtual void vt04();                                   // +0x04
  PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
  virtual void vt28(int a, bool b);                      // +0x28
};
struct Canvas14 { PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20)
  virtual bool vt54(); };
Canvas14* GetCanvas();                                   // 0x0067dcf0
struct Config14 { PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  virtual void vt2c(uint32_t a, uint32_t b); };
Config14* GetConfig14();                                 // 0x0067dd30
struct VecMap14 { uint32_t& operator[](const uint32_t& k); };   // 0x00564a10
struct LayoutFind14 { char pad[0x18]; void* FindWindowByID(uint32_t id, int rec); };
struct GraphicsTabF10 {
  char pad0[8];
  LayoutFind14 mLayout;      // +0x08
  uint32_t mId;              // +0x20
  VecMap14 mData;            // +0x24
  void F10();                // 0x00603f10
  void FE0();                // 0x00603fe0
};

// @ 0x00603f10
void GraphicsTabF10::F10()
{
  WinA14* w = (WinA14*)mLayout.FindWindowByID(mId, 1);
  WinA14* w2 = (WinA14*)w->vtf0(0x5b591c0, 1);
  if (w2) {
    Obj14* o = (Obj14*)w2->vt0c(0x8ed27e7a);
    if (o) {
      o->vt0();
      const uint32_t key = 0x46170a2;
      uint32_t v = (GetCanvas()->vt54() != 0);
      mData[key] = v;
      uint32_t v2 = mData[key];
      o->vt28(4, v2 != 0);
      GetConfig14()->vt2c(key, v2);
      o->vt04();
    }
  }
}

// @ 0x00603fe0
void GraphicsTabF10::FE0()
{
  WinA14* w = (WinA14*)mLayout.FindWindowByID(mId, 1);
  WinA14* w2 = (WinA14*)w->vtf0(0x5b591c0, 1);
  if (w2) {
    Obj14* o = (Obj14*)w2->vt0c(0x8ed27e7a);
    if (o) {
      o->vt0();
      const uint32_t key = 0x46170a2;
      uint32_t v = (GetCanvas()->vt54() == 0);
      mData[key] = v;
      uint32_t v2 = mData[key];
      o->vt28(4, v2 != 0);
      GetConfig14()->vt2c(key, v2);
      o->vt04();
    }
  }
}

// ---- stubs -----------------------------------------------------------------------------
void FUN_00603820() {}
void FUN_00603920() {}
void FUN_00603a10() {}
void FUN_00603de0() {}
void FUN_00603f10() {}
void FUN_00603fe0() {}
void FUN_00604260() {}
void FUN_006044b0() {}
void FUN_00604520() {}
void FUN_006045c0() {}
