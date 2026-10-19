// Slice s00600e80 - cOnlineTab/cSPUISettings helpers.
// Flags: /O2 /MD /Gy /TP /arch=SSE
#include "../s005fa8d0/s005fa8d0.h"
#include <intrin.h>

// ---- address-annotated data symbols ----------------------------------------------------
extern int vt_13fa3ec;        // 0x013fa3ec
extern int vt_13fa364;        // 0x013fa364
extern int vt_13fa378;        // 0x013fa378
extern int vt_13fa38c;        // 0x013fa38c
extern int vt_13fa3a0;        // 0x013fa3a0
extern int vt_13fa434;        // 0x013fa434
extern int vt_13fa42c;        // 0x013fa42c
extern int vt_13fa448;        // 0x013fa448
extern int vt_13fa450;        // 0x013fa450
extern int vt_13fa460;        // 0x013fa460
extern int vt_13fa46c;        // 0x013fa46c
extern int vt_13eb394;        // 0x013eb394
extern int vt_13eb938;        // 0x013eb938
extern int vt_13ec458;        // 0x013ec458
extern char gEmpty_1667bac;   // 0x01667bac
extern char gEmpty_1667bad;   // 0x01667bad
extern wchar_t gW_13ec468[];  // 0x013ec468
extern float gF13fa35c;       // 0x013fa35c
extern float gF13fa360;       // 0x013fa360
extern float gF13fa354;       // 0x013fa354
extern float gF13eb960;       // 0x013eb960
extern float gF1471064;       // 0x01471064
extern float gF1488874;       // 0x01488874
extern float gF13f6a30;       // 0x013f6a30
extern float gF1486374;       // 0x01486374

extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(void* lp);

// ---- shared interfaces -----------------------------------------------------------------
struct cUILayoutS {
  void* FindWindowByID(uint32_t id, bool recursive) const;   // 0x008105b0
  void Ctor();                                               // 0x00810000
  void Dtor();                                               // 0x00811fe0
};
struct cOnlineTabD { void Dtor(); };   // 0x00601730

// A retro-fitted window vtable: only the slots this slice touches are named.
struct IW {
  virtual void f0();                      // +0x00
  virtual void f1();                      // +0x04
  virtual void f2();
  virtual void f3();
  virtual void* f4();                     // +0x10
  virtual void f5();                      // +0x14
  virtual void f6();
  virtual void f7();
  virtual void f8();
  virtual void f9(int, int);              // +0x24
  virtual int  f10();                     // +0x28
  virtual void f11();
  virtual void f12();
  virtual void f13();
  virtual void* f14();                    // +0x38
  virtual void f15();
  virtual int  f16();                     // +0x40
  virtual void f17();
  virtual void f18();
  virtual void f19(int);                  // +0x4c
  virtual void f20();
  virtual void f21();
  virtual void f22();
  virtual void f23();
  virtual void f24();
  virtual void f25(float, float);         // +0x64
  virtual void f26(float, float);         // +0x68
  virtual void f27(void*);                // +0x6c
  virtual void f28();
  virtual void f29();
  virtual void f30();
  virtual void f31(int, int);             // +0x7c
  virtual void f32(const wchar_t*);       // +0x80
  virtual void f33(); virtual void f34(); virtual void f35(); virtual void f36(); virtual void f37();
  virtual void f38(); virtual void f39(); virtual void f40(); virtual void f41(); virtual void f42();
  virtual void f43(); virtual void f44(); virtual void f45(); virtual void f46(); virtual void f47();
  virtual void f48(); virtual void f49(); virtual void f50(); virtual void f51(); virtual void f52();
  virtual void f53();
  virtual void f54(void*);                // +0xd8
  virtual void f55(void*);                // +0xdc
  virtual void f56();
  virtual void f57();                     // +0xe4
  virtual void f58(); virtual void f59(); virtual void f60(); virtual void f61();
  virtual void f62(); virtual void f63(); virtual void f64(); virtual void f65();
  virtual void f66(void*);                // +0x108
};

struct ILang5 {
  virtual void l0(); virtual void l1(); virtual void l2(); virtual void l3(); virtual void l4();
  virtual const wchar_t* l5();
};
struct IVec5 {
  virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3(); virtual void m4();
  virtual void m5(int);
};
struct IMsgSrv5 {
  virtual void n0(); virtual void n1(); virtual void n2(); virtual void n3(); virtual void n4();
  virtual void n5(uint32_t, int, int);
};

struct IDirectPropList { bool GetDescription(uint32_t id); };   // 0x006a25a0
extern IDirectPropList* g_sAppProperties;                       // 0x015fd918

struct cSPUICreditsX {
  int FUN_005fe300(uint32_t i);                  // 0x005fe300
  const wchar_t* GetCreditName(uint32_t i);      // 0x005fe500
};
struct WinTextX { WinTextX* Ctor(); };           // 0x00989000

void* __cdecl FUN_009512c0();                                     // 0x009512c0
void* __cdecl FUN_009512d0(uint32_t t, int a, const char* n, void* m);  // 0x009512d0
IW* __cdecl FUN_0067de40();                                       // 0x0067de40
bool __cdecl FUN_006ab760(const void* p, const wchar_t* s);       // 0x006ab760
char __cdecl FUN_00807690(void* a, int b);                        // 0x00807690
float __cdecl Clamp01(float v);                                   // 0x005a6e00

struct MsgX {
  char pad0[4];
  void* f4;        // +0x04
  uint32_t id;     // +0x08
  void* f0c;       // +0x0c
  char pad10[8];
  int f18;         // +0x18
};

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

// ---- 00601a70: SettingsRecord copy constructor ----------------------------------------
struct RefPtr2 {
  IRefCounted2* p;
  RefPtr2() : p(0) {}
  RefPtr2(const RefPtr2& o) : p(o.p) { if (p) p->AddRef(); }
  RefPtr2& operator=(const RefPtr2& o);
};
struct cStringRec {
  cStringRec(const cStringRec&);   // 0x006b56f0
  uint32_t pad[5];
};
struct SettingsRecordCopy {
  RefPtr2 m0;                // +0x00
  uint32_t f4, f8;           // +0x04, +0x08
  eastl::string16 mName;     // +0x0c
  uint32_t f1c, f20, f24, f28, f2c, f30, f34, f38;   // +0x1c..+0x38
  cStringRec m3c;            // +0x3c
  uint32_t f50, f54;         // +0x50, +0x54
  SettingsRecordCopy(const SettingsRecordCopy& o);
};

// @ 0x00601a70
SettingsRecordCopy::SettingsRecordCopy(const SettingsRecordCopy& o)
  : m0(o.m0), f4(o.f4), f8(o.f8), mName(o.mName),
    f1c(o.f1c), f20(o.f20), f24(o.f24), f28(o.f28),
    f2c(o.f2c), f30(o.f30), f34(o.f34), f38(o.f38),
    m3c(o.m3c), f50(o.f50), f54(o.f54)
{
}

// ---- 00601e60 family -------------------------------------------------------------------
struct LayoutShutdown { void Shutdown(int a); };   // 0x00811ad0
void RemoveTabHelper(void* self, uint32_t id);

// A settings tab: refcounted object that embeds a layout at +8 and keeps its root window id at +0x20.
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
  SPUISettingsStub* Ctor();      // 0x00601790
  void Dtor();                   // 0x00601930
  void CloseWindow();            // 0x00601f00
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

// ---- 00601790: cSPUISettings constructor ----------------------------------------------
struct CreditsTabCtor { void Construct(); void Destroy(); };   // 0x00600da0 / 0x00600df0
struct EAStopwatchX {
  void Ctor(int units, bool a);         // 0x0093a560
  void SetTimeLimit(uint32_t, bool);    // 0x0093a480
  __int64 GetElapsedTime();             // 0x0093a5e0
  __int64 GetElapsedTimeInt();          // 0x0093a3a0
  void Restart();                       // 0x00571e80
};

// @ 0x00601790
SPUISettingsStub* SPUISettingsStub::Ctor()
{
  char* p = (char*)this;
  *(void* volatile*)(p + 8) = &vt_13ec458;
  *(void* volatile*)(p + 0xc) = 0;
  *(void* volatile*)(p + 0x10) = &vt_13eb394;
  *(void* volatile*)(p + 0x0) = &vt_13fa46c;
  *(void* volatile*)(p + 0x4) = &vt_13fa460;
  *(void* volatile*)(p + 8) = &vt_13fa450;
  *(void* volatile*)(p + 0x10) = &vt_13fa448;
  *(void* volatile*)(p + 0x14) = 0;
  *(uint8_t volatile*)(p + 0x18) = 0;
  ((CreditsTabCtor*)(p + 0x20))->Construct();
  *(void* volatile*)(p + 0xc0) = &vt_13fa364;
  ((cUILayoutS*)(p + 0xc8))->Ctor();
  *(void* volatile*)(p + 0xc0) = &vt_13fa378;
  *(void* volatile*)(p + 0xe4) = 0;
  *(void* volatile*)(p + 0x10c) = &vt_13fa364;
  ((cUILayoutS*)(p + 0x114))->Ctor();
  *(void* volatile*)(p + 0x10c) = &vt_13fa3ec;
  *(void* volatile*)(p + 0x130) = 0;
  *(void* volatile*)(p + 0x134) = 0;
  *(void* volatile*)(p + 0x138) = 0;
  *(void* volatile*)(p + 0x14c) = 0;
  *(void* volatile*)(p + 0x150) = 0;
  *(void* volatile*)(p + 0x154) = 0;
  *(void* volatile*)(p + 0x160) = &vt_13fa364;
  ((cUILayoutS*)(p + 0x168))->Ctor();
  *(void* volatile*)(p + 0x184) = &vt_13eb394;
  *(void* volatile*)(p + 0x160) = &vt_13fa434;
  *(void* volatile*)(p + 0x184) = &vt_13fa42c;
  void* e0 = &gEmpty_1667bac;
  void* e1 = &gEmpty_1667bad;
  *(void* volatile*)(p + 0x188) = e0;
  *(void* volatile*)(p + 0x18c) = e0;
  *(void* volatile*)(p + 0x190) = e1;
  *(void* volatile*)(p + 0x1a0) = e1;
  *(void* volatile*)(p + 0x198) = e0;
  *(void* volatile*)(p + 0x19c) = e0;
  *(void* volatile*)(p + 0x1b0) = &vt_13fa364;
  ((cUILayoutS*)(p + 0x1b8))->Ctor();
  *(void* volatile*)(p + 0x1b0) = &vt_13fa38c;
  *(void* volatile*)(p + 0x1dc) = &vt_13fa364;
  ((cUILayoutS*)(p + 0x1e4))->Ctor();
  *(void* volatile*)(p + 0x1dc) = &vt_13fa3a0;
  *(void* volatile*)(p + 0x20c) = 0;
  *(void* volatile*)(p + 0x210) = 0;
  *(void* volatile*)(p + 0x214) = 0;
  *(void* volatile*)(p + 0x220) = 0;
  EAStopwatchX* sw = (EAStopwatchX*)(p + 0x228);
  sw->Ctor(4, false);
  sw->SetTimeLimit(0, false);
  return this;
}

// @ 0x00601930
void SPUISettingsStub::Dtor()
{
  char* p = (char*)this;
  *(void* volatile*)(p + 0x0) = &vt_13fa46c;
  *(void* volatile*)(p + 0x4) = &vt_13fa460;
  *(void* volatile*)(p + 8) = &vt_13fa450;
  *(void* volatile*)(p + 0x10) = &vt_13fa448;
  {
    IW* o = *(IW* volatile*)(p + 0x220);
    if (o) o->f1();
  }
  {
    void* m = *(void* volatile*)(p + 0x20c);
    if (m && ((int*)m)[-1]) operator delete(m);
  }
  *(void* volatile*)(p + 0x1dc) = &vt_13fa364;
  ((cUILayoutS*)(p + 0x1e4))->Dtor();
  *(void* volatile*)(p + 0x1b0) = &vt_13fa364;
  ((cUILayoutS*)(p + 0x1b8))->Dtor();
  ((cOnlineTabD*)(p + 0x160))->Dtor();
  *(void* volatile*)(p + 0x10c) = &vt_13fa3ec;
  {
    void* m = *(void* volatile*)(p + 0x14c);
    if (m && ((int*)m)[-1]) operator delete(m);
  }
  {
    void* m = *(void* volatile*)(p + 0x130);
    if (m) operator delete(m);
  }
  *(void* volatile*)(p + 0x10c) = &vt_13fa364;
  ((cUILayoutS*)(p + 0x114))->Dtor();
  *(void* volatile*)(p + 0xc0) = &vt_13fa364;
  ((cUILayoutS*)(p + 0xc8))->Dtor();
  ((CreditsTabCtor*)(p + 0x20))->Destroy();
  {
    IW* o = *(IW* volatile*)(p + 0x14);
    if (o) o->f2();
  }
  *(void* volatile*)(p + 0x10) = &vt_13eb394;
  *(void* volatile*)(p + 8) = &vt_13ec458;
  *(void* volatile*)(p + 0x0) = &vt_13eb938;
}

// @ 0x00601f00
void SPUISettingsStub::CloseWindow()
{
  if (this) ((IW*)this)->f0();
  ((IW*)mpLayout->FindWindowByID(0x43c8b98, true))->f66(this);
  ((IW*)mpLayout->FindWindowByID(0xaded51d5, true))->f66(this);
  ((IW*)mpLayout->FindWindowByID(0x8bdd39ec, true))->f66(this);
  ((IW*)mpLayout->FindWindowByID(0x3af239c4, true))->f66(this);
  ((IW*)mpLayout->FindWindowByID(0x9a0474a, true))->f66(this);
  ((IMsgSrv5*)SP::Thumbnail::GetMessageServer())->n5(0x4519b5f, 0, 0);
  Shutdown();
  ((IW*)this)->f1();
}

// ---- 006016c0: cGraphicsTab scalar deleting destructor --------------------------------
struct cGraphicsTabD { void* ScalarDtor(uint8_t flags); };

// @ 0x006016c0
void* cGraphicsTabD::ScalarDtor(uint8_t flags)
{
  char* p = (char*)this;
  *(void* volatile*)(p + 0) = &vt_13fa3ec;
  {
    void* m = *(void* volatile*)(p + 0x40);
    if (m && ((int*)m)[-1]) operator delete(m);
  }
  {
    void* m = *(void* volatile*)(p + 0x24);
    if (m) operator delete(m);
  }
  *(void* volatile*)(p + 0) = &vt_13fa364;
  ((cUILayoutS*)(p + 8))->Dtor();
  if (flags & 1) operator delete(this);
  return this;
}

// ---- 00601730: cOnlineTab destructor --------------------------------------------------

// @ 0x00601730
void cOnlineTabD::Dtor()
{
  char* p = (char*)this;
  *(void* volatile*)(p + 0) = &vt_13fa434;
  *(void* volatile*)(p + 0x24) = &vt_13fa42c;
  {
    char* s = *(char* volatile*)(p + 0x38);
    if (*(char* volatile*)(p + 0x40) - s > 1 && s) operator delete(s);
  }
  {
    char* s = *(char* volatile*)(p + 0x28);
    if (*(char* volatile*)(p + 0x30) - s > 1 && s) operator delete(s);
  }
  *(void* volatile*)(p + 0x24) = &vt_13eb394;
  *(void* volatile*)(p + 0) = &vt_13fa364;
  ((cUILayoutS*)(p + 8))->Dtor();
}

// ---- 00600e80 / 006012e0: cCreditsTab ------------------------------------------------
struct cCreditsTabX {
  void UpdateCredits(int index);              // 0x00600e80
  bool DoMessage(void* ctx, MsgX* msg);       // 0x006012e0
  void RestartTimer();                        // 0x005ff230
};

// @ 0x00600e80
void cCreditsTabX::UpdateCredits(int index)
{
  char* p = (char*)this;
  if (*(void**)(p + 0x24) == *(void**)(p + 0x28)) return;
  IW* win44 = *(IW**)(p + 0x44);
  if (win44) win44->f57();
  IW* win = (IW*)((cUILayoutS*)(p + 8))->FindWindowByID(0x6036e80, true);
  float* pf = (float*)win->f14();
  int off = index * 0x58;
  float h = pf[2] - pf[0];
  float saved = h * gF1471064;
  float xmm2 = gF13fa35c;
  float sub2 = saved - gF13fa360;
  int i = 0;
  char* cred = (char*)*(void**)(p + 0x24) + off;
  if (*(uint16_t*)(cred + 4) == 0) goto Lend;
  do {
    cSPUICreditsX* cp = (cSPUICreditsX*)((char*)*(void**)(p + 0x24) + off);
    int first = cp->FUN_005fe300(i);
    bool isLast = cp->FUN_005fe300(i + 1) == 1;
    bool desc = g_sAppProperties->GetDescription(0x61b67b6);
    bool skip;
    if (!desc && first == *(int*)(cred + 0x54)) {
      skip = true;
    } else {
      const wchar_t* lang = ((ILang5*)FUN_0067de40())->l5();
      skip = (!FUN_006ab760(lang, L"en-us") && first == *(int*)(cred + 0x50));
    }
    if (!skip) {
      WinTextX* w1 = (WinTextX*)FUN_009512d0(0x834, 4, "UTFWinControls/WinText", FUN_009512c0());
      if (w1) {
        w1 = w1->Ctor();
        if (w1) ((IW*)w1)->f0();
      }
      WinTextX* w2 = (WinTextX*)FUN_009512d0(0x834, 4, "UTFWinControls/WinText", FUN_009512c0());
      if (w2) {
        w2 = w2->Ctor();
        if (w2) ((IW*)w2)->f0();
      }
      IW* p1 = (IW*)((char*)w1 + 4);
      p1->f32(cp->GetCreditName(i));
      p1->f26(isLast ? (h - gF13fa360) : sub2, gF13fa360);
      if (*cp->GetCreditName(i)) ((IVec5*)((char*)w1 + 0x20c))->m5(1);
      win44->f54(p1);
      p1->f31(0x10, 1);
      p1->f25(gF13fa354, xmm2);
      float f = ((float*)p1->f14())[3];
      IW* p2 = (IW*)((char*)w2 + 4);
      if (isLast) {
        p2->f32(gW_13ec468);
      } else {
        p2->f32(cp->GetCreditName(i + 1));
        p2->f26(sub2, gF13fa360);
        p2->f31(0x10, 1);
        if (*cp->GetCreditName(i + 1)) ((IVec5*)((char*)w2 + 0x20c))->m5(1);
        win44->f54(p2);
        p2->f25(saved + gF13fa354, xmm2);
      }
      float f2 = ((float*)p2->f14())[3];
      xmm2 = (f2 > f ? f2 : f) + gF13fa35c;
      i += 2;
      ((IW*)w2)->f1();
      ((IW*)w1)->f1();
    } else {
      i += 2;
    }
    cred = (char*)*(void**)(p + 0x24) + off;
  } while (i < (int)(uint16_t)*(uint16_t*)(cred + 4));
Lend:
  *(float*)(p + 0x38) = 0.0f;
  *(float*)(p + 0x3c) = gF13eb960;
  *(uint32_t*)(p + 0x60) = 0;
  *(uint32_t*)(p + 0x64) = 0;
  *(uint32_t*)(p + 0x68) = 0;
  *(uint32_t*)(p + 0x6c) = 0;
  *(uint32_t*)(p + 0x80) = 0;
  *(uint32_t*)(p + 0x84) = 0;
  *(uint32_t*)(p + 0x88) = 0;
  *(uint32_t*)(p + 0x8c) = 0;
  if (*(int*)(p + 0x90) == 1) {
    unsigned __int64 t = __rdtsc();
    *(uint32_t*)(p + 0x80) = (uint32_t)t;
    *(uint32_t*)(p + 0x84) = (uint32_t)(t >> 32);
    *(uint8_t*)(p + 0x98) = 0;
    return;
  }
  __int64 q;
  QueryPerformanceCounter(&q);
  *(uint32_t*)(p + 0x80) = (uint32_t)q;
  *(uint32_t*)(p + 0x84) = (uint32_t)(q >> 32);
  *(uint8_t*)(p + 0x98) = 0;
}

// @ 0x006012e0
bool cCreditsTabX::DoMessage(void* ctx, MsgX* msg)
{
  char* p = (char*)this;
  uint32_t m = msg->id;
  if (m > 0x287259f6) {
    if (m == 0x8ef0c8dd && msg->f4 == *(void**)(p + 0x48) && *(void**)(p + 0x50)) {
      IW* w50 = *(IW**)(p + 0x50);
      float old = *(float*)(p + 0x3c);
      *(float*)(p + 0x3c) = (float)w50->f10();
      float v = (float)w50->f10();
      *(float*)(p + 0x38) = v;
      float d = v - old;
      if (d < 0.0f) d = -d;
      if (d > gF13fa354) RestartTimer();
    }
    return false;
  }
  if (m == 0x287259f6) {
    if (msg->f0c) {
      int n = (int)((*(char**)(p + 0x28) - *(char**)(p + 0x24)) / 0x58);
      int k = 0;
      if (n > 0) {
        char* e = *(char**)(p + 0x24) + 0x20;
        do {
          if (*(void**)e == msg->f0c) {
            *(int*)(p + 0x9c) = k;
            UpdateCredits(k);
            return true;
          }
          ++k;
          e += 0x58;
        } while (k < n);
        return false;
      }
    }
    return false;
  }
  if (m == 9) {
    if (msg->f4 == *(void**)(p + 0x44) || msg->f4 == *(void**)(p + 0x4c)) {
      float v = *(float*)(p + 0x38) - (float)msg->f18 * gF1486374;
      *(float*)(p + 0x38) = v;
      if (v < 0.0f) v = 0.0f;
      if (*(float*)(p + 0x40) <= v) v = *(float*)(p + 0x40);
      *(float*)(p + 0x38) = v;
      *(uint8_t*)(p + 0x54) = 1;
      RestartTimer();
      return true;
    }
  } else if (m != 0xc) {
    return false;
  }
  if (*(uint8_t*)(p + 0x98) == 0) {
    __int64 t = ((EAStopwatchX*)(p + 0x80))->GetElapsedTime();
    if ((t >> 32) != 0 || (uint32_t)t > 3) *(uint8_t*)(p + 0x98) = 1;
  }
  IW* win = (IW*)((cUILayoutS*)(p + 8))->FindWindowByID(0x463f008, true);
  EAStopwatchX* sw = (EAStopwatchX*)(p + 0x60);
  __int64 e = sw->GetElapsedTimeInt();
  float dt = (float)e * *(float*)(p + 0x74);
  *(uint32_t*)(p + 0x60) = 0;
  *(uint32_t*)(p + 0x64) = 0;
  *(uint32_t*)(p + 0x68) = 0;
  *(uint32_t*)(p + 0x6c) = 0;
  sw->Restart();
  if (*(uint8_t*)(p + 0x98) != 0) {
    if (win->f10() & 1) *(float*)(p + 0x38) = *(float*)(p + 0x38) + gF1488874;
  }
  if (*(void**)(p + 0x44) != 0 && *(float*)(p + 0x38) != *(float*)(p + 0x3c)) {
    float k = Clamp01(dt * gF13f6a30);
    float v = (*(float*)(p + 0x38) - *(float*)(p + 0x3c)) * k + *(float*)(p + 0x3c);
    *(float*)(p + 0x3c) = v;
    if (*(void**)(p + 0x50)) ((IW*)*(void**)(p + 0x50))->f9((int)v, 1);
    float d = *(float*)(p + 0x3c) - *(float*)(p + 0x38);
    if (d < 0.0f) d = -d;
    if (d < gF1471064) *(float*)(p + 0x3c) = *(float*)(p + 0x38);
  }
  if (*(float*)(p + 0x3c) == *(float*)(p + 0x38)) *(uint8_t*)(p + 0x54) = 0;
  if (*(void**)(p + 0x48) && *(void**)(p + 0x50) && *(void**)(p + 0x4c) && *(void**)(p + 0x44)) {
    if (win->f10() & 1) {
      IW* w4c = *(IW**)(p + 0x4c);
      float* r4c = (float*)w4c->f14();
      if (*(float*)(p + 0x58) != r4c[3]) {
        IW* w44 = *(IW**)(p + 0x44);
        float* r44 = (float*)w44->f14();
        float rc[4];
        rc[0] = r44[0];
        rc[1] = r44[1];
        rc[2] = r44[2];
        rc[3] = r44[3];
        w44->f27(rc);
        FUN_00807690(*(void**)(p + 0x48), 0);
        IW* w50 = *(IW**)(p + 0x50);
        int top = w50->f16();
        int bot = (int)w50->f14();
        *(float*)(p + 0x40) = (float)(bot - top);
        IW* w4c2 = *(IW**)(p + 0x4c);
        float* r = (float*)w4c2->f14();
        *(float*)(p + 0x58) = r[3];
        float right = r[2];
        rc[2] = (right - r[0]) + r[0];
        IW* w44b = *(IW**)(p + 0x44);
        w44b->f27(rc);
        IW* w50b = *(IW**)(p + 0x50);
        w50b->f19(1000);
        return false;
      }
    }
  }
  return false;
}
