// Slice s00600e80 - cOnlineTab/cSPUISettings helpers.
// Flags: /O2 /MD /Gy /TP /arch=SSE
#include "../s005fa8d0/s005fa8d0.h"

// ---- 00601c50: copy assignment of a settings record -----------------------------------
struct IRefCounted2 { virtual int AddRef(); virtual int Release(); };
struct IntrusivePtr2 {
  IRefCounted2* mpObject;
  IntrusivePtr2& operator=(const IntrusivePtr2& x) {
    IRefCounted2* const p = x.mpObject;
    IRefCounted2* const pOld = mpObject;
    if (p != pOld) {
      if (p) p->AddRef();
      mpObject = p;
      if (pOld) pOld->Release();
    }
    return *this;
  }
};
struct SubObj14 {
  uint32_t pad[5];
  SubObj14& operator=(const SubObj14&);
};
struct SettingsRecord {
  IntrusivePtr2 m0;          // +0x00
  uint32_t f4, f8;           // +0x04, +0x08
  eastl::string16 mName;     // +0x0c
  uint32_t f1c, f20, f24, f28, f2c, f30, f34, f38;   // +0x1c..+0x38
  SubObj14 m3c;              // +0x3c
  uint32_t f50, f54;         // +0x50, +0x54
  SettingsRecord& operator=(const SettingsRecord& o);
};

// @ 0x00601c50
SettingsRecord& SettingsRecord::operator=(const SettingsRecord& o)
{
  m0 = o.m0;
  f4 = o.f4;
  f8 = o.f8;
  mName = o.mName;
  f1c = o.f1c; f20 = o.f20; f24 = o.f24; f28 = o.f28;
  f2c = o.f2c; f30 = o.f30; f34 = o.f34; f38 = o.f38;
  m3c = o.m3c;
  f50 = o.f50;
  f54 = o.f54;
  return *this;
}

// ---- 00601e60: cSPUISettings::Shutdown -------------------------------------------------
struct LayoutShutdown { void Shutdown(int a); };   // 0x00811ad0
void RemoveTabHelper(void* self, uint32_t id);

struct SPUISettingsStub {
  char pad0[0x10];
  char mHandler[4];        // +0x10 (IHandler subobject passed to MessageServer)
  void* mpLayout;          // +0x14
  char pad18[0x20c - 0x18];
  uint32_t* mTabBegin;     // +0x20c
  uint32_t* mTabEnd;       // +0x210
  void RemoveTab(uint32_t id);   // 0x00601da0
  bool Shutdown();               // 0x00601e60
};

// @ 0x00601e60
bool SPUISettingsStub::Shutdown()
{
  while ((mTabEnd - mTabBegin) != 0)
    RemoveTab(mTabBegin[(mTabEnd - mTabBegin) - 1]);
  if (mpLayout)
    ((LayoutShutdown*)mpLayout)->Shutdown(1);
  void* handler = (char*)this + 0x10;
  SP::Thumbnail::GetMessageServer()->vt2c(handler, 0x238de9c, 0xffffd8f1);
  SP::Thumbnail::GetMessageServer()->vt2c(handler, 0x62752d3, 0xffffd8f1);
  return true;
}

// ---- stubs -----------------------------------------------------------------------------
void FUN_00600e80() {}
void FUN_006012e0() {}
void FUN_00601930() {}
void FUN_00601a70() {}
void FUN_006016c0() {}
void FUN_00601730() {}
void FUN_00601790() {}
void FUN_00601f00() {}
