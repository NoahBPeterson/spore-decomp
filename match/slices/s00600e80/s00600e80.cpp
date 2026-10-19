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

// A settings tab: refcounted object that embeds a layout at +8 and keeps its root window id at +0x20.
struct cUILayoutS {
  void* FindWindowByID(uint32_t id, bool recursive) const;   // 0x008105b0 (thiscall, ret 8)
};
struct cUITab {
  virtual int AddRef();     // +0
  virtual int Release();    // +4
  char pad08[0x28 - 0x08];
};

#define SLOTS8(n) virtual void s##n##a(); virtual void s##n##b(); virtual void s##n##c(); virtual void s##n##d(); \
                  virtual void s##n##e(); virtual void s##n##f(); virtual void s##n##g(); virtual void s##n##h();
struct IWindowS {          // only slots +0x10 and +0xdc are used here
  virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
  virtual void* Slot4();                             // +0x10
  virtual void v14(); virtual void v18(); virtual void v1c();
  SLOTS8(1) SLOTS8(2) SLOTS8(3) SLOTS8(4) SLOTS8(5)             // +0x20 .. +0xc7
  virtual void s6a(); virtual void s6b(); virtual void s6c(); virtual void s6d();
  virtual void s6e(); virtual void s6f(); virtual void s6g();                         // .. +0xdb
  virtual void Slot55(void* arg);                    // +0xdc
};

struct SPUISettingsStub {
  char pad0[0x10];
  char mHandler[4];        // +0x10 (IHandler subobject passed to MessageServer)
  cUILayoutS* mpLayout;    // +0x14
  char pad18[0x20c - 0x18];
  cUITab** mTabBegin;      // +0x20c
  cUITab** mTabEnd;        // +0x210
  void RemoveTab(cUITab* tab);   // 0x00601da0
  bool Shutdown();               // 0x00601e60
};
void* __cdecl Memmove_11e0744(void* dst, const void* src, uint32_t n);   // 0x011e0744 (static CRT)

// @ 0x00601da0
void SPUISettingsStub::RemoveTab(cUITab* tab)
{
  cUITab** end = mTabEnd;
  cUITab** p = mTabBegin;
  while (p != end && *p != tab)
    ++p;
  cUITab** next = p + 1;
  if (next < end)
    Memmove_11e0744(p, next, (char*)end - (char*)next);
  mTabEnd -= 1;
  if (mpLayout) {
    IWindowS* win = (IWindowS*)mpLayout->FindWindowByID(0x46967c0, true);
    if (win && tab) {
      cUILayoutS* sub = (cUILayoutS*)((char*)tab + 8);
      if (sub->FindWindowByID(*(uint32_t*)((char*)tab + 0x20), true)) {
        IWindowS* w2 = (IWindowS*)sub->FindWindowByID(*(uint32_t*)((char*)tab + 0x20), true);
        if (w2->Slot4()) {
          void* arg = sub->FindWindowByID(*(uint32_t*)((char*)tab + 0x20), true);
          win->Slot55(arg);
        }
      }
      tab->Release();
    }
  }
}

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
