// Slice s00602940 - cOnlineTab / cSPUISettings tab management.
// Flags: /O2 /MD /Gy /TP /arch:SSE
#include "../s005fa8d0/s005fa8d0.h"
#include <stdlib.h>
void* operator new(size_t, const char*, int, int, int, int);   // 0x00f473a0

#define CAT2(a, b) a##b
#define CAT(a, b) CAT2(a, b)
#define PV1 virtual void CAT(_pv, __COUNTER__)();
#define PV5 PV1 PV1 PV1 PV1 PV1
#define PV20 PV5 PV5 PV5 PV5

// ---- shared stub declarations (retail layouts from the disassembly) --------------------
void __cdecl WStr_Format(void*, const wchar_t*, ...);   // 0x0041e050
extern wchar_t gEmptyStr16[2];                          // 0x01667bac

// eastl::basic_string<wchar_t> shape (begin/end/capacity)
struct WStr {
  wchar_t* b; wchar_t* e; wchar_t* c;
  WStr() { b = gEmptyStr16; e = gEmptyStr16; c = gEmptyStr16 + 1; }
  ~WStr() { if ((((char*)c - (char*)b) & ~1) > 2 && b) operator delete[](b); }
};
WStr* __cdecl ConvertToString16(WStr* out, int v);       // 0x0093c6d0 EA::ConvertToString16

namespace SP {
class cString {
 public:
  cString();                                                    // 0x006b5060
  ~cString();                                                   // 0x006b5240
  void Load(uint32_t table, uint32_t inst, const wchar_t* def); // 0x006b54b0
  const wchar_t* GetText();                                     // 0x006b55c0
  uint32_t pad[5];
};
}

// UTFWin window: only the vtable slots this slice touches
struct IWin {
  virtual int AddRef();                                  // +0x00
  virtual int Release();                                 // +0x04
  PV1
  virtual IWin* QueryChild(uint32_t id);                 // +0x0c
  virtual IWin* GetSub();                                // +0x10
  virtual void SetValue(int v, int w);                   // +0x14
  PV1 PV1
  virtual int GetID(int a);                              // +0x20
  PV1
  virtual void SetState(int a, int b);                   // +0x28
  PV20                                                   // slots 11..30
  virtual void SetFlag(int flag, int on);                // +0x7c
  virtual void SetCaption(const wchar_t* text);          // +0x80
  PV20 PV1                                               // slots 33..53
  virtual void AddChildWin(IWin* child);                 // +0xd8
  PV5                                                    // slots 55..59
  virtual IWin* FindByID(uint32_t id, int recursive);    // +0xf0
  PV1 PV1 PV1 PV1                                        // slots 61..64
  virtual void SetWinProc(void* proc);                   // +0x104
};

struct IColorWin { PV5 PV5 virtual void SetColor(uint32_t c); };   // slot +0x28, one argument

// cSPUILayout: refcounted (vtable +4 AddRef, +8 Release); also used inline at tab+8 (0x18 bytes)
class cSPUILayout {
 public:
  virtual void pv0();
  virtual int AddRef();
  virtual int Release();
  cSPUILayout();                                                         // 0x00810000
  bool Init(const wchar_t* name, uint32_t key, int a, uint32_t b);       // 0x00812160
  void InitTab(const wchar_t* name, int a, uint32_t b);                  // 0x008120d0
  void GetObjects();                                                     // 0x008100c0
  IWin* FindWindowByID(uint32_t id, int recursive);                      // 0x008105b0
  uint32_t pad[4];
};

namespace SPUIHelpers {
void __cdecl SetWindowAreaToParent(IWin* w);                    // 0x00806bf0
void __cdecl AutoSizeWindowForText(IWin* w, int a, int b);      // 0x00806e40
void __cdecl ResetScrollFrameColor(IWin* w);                    // 0x00807040
void __cdecl SetRotation(IWin* w, const float* q);              // 0x00808230 UI::cWindowTransform::SetRotation
}
IWin* __stdcall GetLayoutManager(uint32_t id);          // 0x00805070 (SPUIHelpers::GetLayoutManager)
struct cSPUILayoutManager { IWin* GetWorldMainWindow(); };  // 0x00810620
const float* __cdecl FUN_00805260(IWin* w);             // 0x00805260 -> float[4]
extern float gF1485720;   // 0x01485720
extern float gF151d728;   // 0x0151d728

struct IMsgListener;
struct IMsgServer {
  PV5 PV1 PV1 PV1 PV1
  virtual void AddListener(IMsgListener* l, uint32_t id);   // +0x24
};
IMsgServer* __cdecl MessageServer();                    // 0x0067dcc0

struct IConfigMgr {
  PV5 PV5 PV1 PV1
  virtual int GetValue(uint32_t id);                         // +0x30
};
IConfigMgr* __cdecl ConfigManager();                         // 0x0067dd30

struct IUserName { PV5 PV5 PV1 PV1 PV1 virtual void SetName(const wchar_t* s, int a); };   // +0x34
struct IUserInfo { PV5 PV1 PV1 PV1 virtual IUserName* GetName(); };                        // +0x20
IUserInfo* __cdecl FUN_0067de40();                                                         // 0x0067de40

struct IAuth {   // SP::Pollen::AuthManager (0x00607a60)
  PV5 PV1 PV1 PV1 PV1
  virtual int IsGuest();            // +0x24
  PV1
  virtual int GetStatus();          // +0x2c
  PV1 PV1
  virtual int GetUserID();          // +0x38
  PV5 PV1 PV1
  virtual int IsLoggedIn();         // +0x58
};
IAuth* __cdecl AuthManager();                                 // 0x00607a60

// intrusive ref pointer to a window (AddRef on assign, Release on drop)
struct WinRef {
  IWin* p;
  WinRef(IWin* q) : p(q) { if (p) p->AddRef(); }
  ~WinRef() { if (p) p->Release(); }
  WinRef& operator=(IWin* q) {
    if (q != p) {
      if (q) q->AddRef();
      IWin* o = p;
      p = q;
      if (o) o->Release();
    }
    return *this;
  }
};

struct cGlobalA { char pad[0x3c]; struct { char pad[0x118]; int flag; }* sub; };
extern cGlobalA* g_015fd918;   // 0x015fd918

// settings tab base: vptr, winproc, inline layout at +8 (0x18), window id at +0x20
struct cSettingsTab {
  virtual void Init(const wchar_t* ui, void* winproc, uint32_t id);
  void* mWinProc;
  char mLayoutStorage[0x18];
  uint32_t mWinID;
  cSPUILayout* L() { return (cSPUILayout*)mLayoutStorage; }
};

// ---- cOnlineTab (retail layout): +0x24 IHandler subobject, flag bytes at +0x48.. --------
struct cOnlineTab : cSettingsTab {
  void* mHandlerVptr;                  // +0x24
  char pad28[0x48 - 0x28];
  uint8_t b48, b49, b4a, b4b, b4c, b4d, b4e, b4f;
  virtual void Init(const wchar_t* ui, void* winproc, uint32_t id);   // 0x00603780
  void InitUIState(uint8_t b);                                         // 0x00602940
};

// ---- 00603170: cOnlineTab::HandleMessage -----------------------------------------------
struct Handler13 {
  bool HandleMessage(uint32_t msg, int p3);
};

// @ 0x00603170
bool Handler13::HandleMessage(uint32_t msg, int p3)
{
  if (msg != 0x44db12e && msg != 0x5b96086 && msg != 0x5c5594a) return false;
  uint8_t b = 0;
  if (msg == 0x44db12e && p3 == 0) b = 1;
  ((cOnlineTab*)((char*)this - 0x24))->InitUIState(b);
  return true;
}

// ---- 00602940: cOnlineTab::InitUIState --------------------------------------------------
// @ 0x00602940
void cOnlineTab::InitUIState(uint8_t b)
{
  IAuth* auth = AuthManager();
  SP::cString sTitle, sMsg, sInfo;
  uint32_t color;
  if (auth->IsLoggedIn()) {
    if (!auth->IsGuest() && !b) {
      IUserName* un = FUN_0067de40()->GetName();
      WStr tmp;
      un->SetName(ConvertToString16(&tmp, auth->GetUserID())->b, 0);
      sTitle.Load(0xad7b2086, 0x56528a8, 0);
      sMsg.Load(0xad7b2086, 0x565289d, 0);
      sInfo.Load(0xad7b2086, 0x56528a9, 0);
      color = 0xff00ff00;
    } else {
      sTitle.Load(0xad7b2086, 0x56528a6, 0);
      sMsg.Load(0xad7b2086, 0x565289e, 0);
      sInfo.Load(0xad7b2086, 0x56528a7, 0);
      color = 0xffffff00;
    }
  } else {
    sTitle.Load(0xad7b2086, 0x56528a4, 0);
    sMsg.Load(0xad7b2086, 0x565289f, 0);
    sInfo.Load(0xad7b2086, 0x56528a5, 0);
    color = 0xffff0000;
  }

  cSPUILayout* lay = L();
  IWin* w = lay->FindWindowByID(0x46c1500, 1);
  if (w) {
    IWin* c = w->QueryChild(0xf15f4bd);
    if (c) {
      c->GetSub()->SetCaption(sTitle.GetText());
      ((IColorWin*)c)->SetColor(color);
    }
  }
  w = lay->FindWindowByID(0x5669738, 1);
  if (w) w->SetCaption(sMsg.GetText());
  w = lay->FindWindowByID(0x43b6178, 1);
  if (w) {
    w->SetCaption(sInfo.GetText());
    SPUIHelpers::AutoSizeWindowForText(w, 1, 0);
  }
  w = lay->FindWindowByID(0x43b6428, 1);
  if (w) {
    IWin* c = w->QueryChild(0x8ed27e7a);
    if (c) c->SetState(4, (uint8_t)auth->GetStatus());
  }

  if (g_015fd918->sub->flag == 0) {
    // desktop-only toggles
    w = lay->FindWindowByID(0x5b1cc48, 1);
    if (w) w->SetFlag(2, 0);
    w = lay->FindWindowByID(0x5b76718, 1);
    if (w) w->SetFlag(1, 0);
    b49 = (uint8_t)ConfigManager()->GetValue(0x5de7b4a);
  } else {
    uint8_t v;
    v = (uint8_t)ConfigManager()->GetValue(0x5de7b4a);
    bool on = (v == 1);
    b49 = v;
    w = lay->FindWindowByID(0x5b1cc48, 1);
    if (w) { IWin* c = w->QueryChild(0x8ed27e7a); if (c) c->SetState(4, on); }

    v = (uint8_t)ConfigManager()->GetValue(0x626f940);
    on = (v == 1);
    b4a = v;
    w = lay->FindWindowByID(0x626f940, 1);
    if (w) { IWin* c = w->QueryChild(0x8ed27e7a); if (c) c->SetState(4, on); }

    v = (uint8_t)ConfigManager()->GetValue(0x626f9c0);
    on = (v == 1);
    b4c = v;
    w = lay->FindWindowByID(0x626f9c0, 1);
    if (w) { IWin* c = w->QueryChild(0x8ed27e7a); if (c) c->SetState(4, on); }

    b4b = (uint8_t)ConfigManager()->GetValue(0x626f958);
    IWin* o = lay->FindWindowByID(mWinID, 1)->FindByID(0x626f958, 1);
    WinRef ref(o ? o->QueryChild(0xaf062e1d) : 0);
    if (ref.p) {
      ref.p->SetValue(b4b, 0);
      WStr s;
      WStr_Format(&s, (const wchar_t*)0x13fa490, (int)b4b);
      lay->FindWindowByID(mWinID, 1)->FindByID(0x626f959, 1)->SetCaption(s.b);
    }

    v = (uint8_t)ConfigManager()->GetValue(0x685a785);
    on = (v == 1);
    b4d = v;
    w = lay->FindWindowByID(0x685a785, 1);
    if (w) { IWin* c = w->QueryChild(0x8ed27e7a); if (c) c->SetState(4, on); }

    b4e = (uint8_t)ConfigManager()->GetValue(0x685a821);
    o = lay->FindWindowByID(mWinID, 1)->FindByID(0x685a821, 1);
    ref = o ? o->QueryChild(0xaf062e1d) : 0;
    if (ref.p) {
      ref.p->SetValue(b4e, 0);
      WStr s;
      WStr_Format(&s, (const wchar_t*)0x13fa490, (int)b4e);
      lay->FindWindowByID(mWinID, 1)->FindByID(0x685a822, 1)->SetCaption(s.b);
    }

    b4f = (uint8_t)ConfigManager()->GetValue(0x685a63c);
    o = lay->FindWindowByID(mWinID, 1)->FindByID(0x685a63c, 1);
    ref = o ? o->QueryChild(0xaf062e1d) : 0;
    if (ref.p) {
      ref.p->SetValue(b4f, 0);
      WStr s;
      WStr_Format(&s, (const wchar_t*)0x13fa490, (int)b4f << 8);
      lay->FindWindowByID(mWinID, 1)->FindByID(0x685a63d, 1)->SetCaption(s.b);
    }
  }

  b48 = ConfigManager()->GetValue(0x5664a8b) != 0;
  w = lay->FindWindowByID(0x56648f8, 1);
  if (w) {
    IWin* c = w->QueryChild(0x8ed27e7a);
    if (c) c->SetState(4, b48 != 0);
  }
  SP::cString sLabel;
  sLabel.Load(0xad7b2086, 0x5664d28, (const wchar_t*)0x13ec468);
  lay->FindWindowByID(0x56648e8, 1)->SetCaption(sLabel.GetText());
}

// ---- 00603780: cOnlineTab::Init ---------------------------------------------------------
// @ 0x00603780
void cOnlineTab::Init(const wchar_t* ui, void* winproc, uint32_t id)
{
  mWinID = id;
  mWinProc = winproc;
  cSPUILayout* lay = L();
  lay->InitTab(ui, 0, 0x5b598fa);
  lay->GetObjects();
  lay->FindWindowByID(mWinID, 1)->SetWinProc(mWinProc);
  InitUIState(0);
  IMsgListener* h = (IMsgListener*)((char*)this + 0x24);
  MessageServer()->AddListener(h, 0x44db12e);
  MessageServer()->AddListener(h, 0x5b96086);
  MessageServer()->AddListener(h, 0x5c5594a);
}

// ---- cSPUISettings (retail): +0x14 layout, tabs at +0x20.., tab vector at +0x20c -------
struct cTabVec {
  cSettingsTab** mpBegin; cSettingsTab** mpEnd; cSettingsTab** mpCapacity;
  void DoInsertValue(cSettingsTab** pos, cSettingsTab* const& v);   // 0x00630b30
  void push_back(cSettingsTab* const& v) {
    if (mpEnd < mpCapacity) {
      if (mpEnd) *mpEnd = v;
      ++mpEnd;
    } else {
      DoInsertValue(mpEnd, v);
    }
  }
};
struct cCreditsTab13 : cSettingsTab {
  char pad[0x9c - 0x24];
  int f9c;
  void FUN_00600c00();            // 0x00600c00
  void FUN_00600e80(int v);       // 0x00600e80
};
struct cSPUISettings {
  char pad0[0x14];
  cSPUILayout* mpLayout;                                // +0x14
  char pad18[0x20 - 0x18];
  char tabs[0x20c - 0x20];                              // tab objects (0x20, 0xc0, 0x10c, ...)
  cTabVec mTabs;                                        // +0x20c
  void AddTab(cSettingsTab* tab, const wchar_t* ui, uint32_t id);   // 0x006031c0
  bool Init(int a);                                     // 0x00603260
  bool OnModalWindowEnd(int a);                         // 0x006008c0 (on the tab at +0x1dc)
};

// ---- 006031c0: cSPUISettings::AddTab ----------------------------------------------------
// @ 0x006031c0
void cSPUISettings::AddTab(cSettingsTab* tab, const wchar_t* ui, uint32_t id)
{
  tab->Init(ui, this, id);
  IWin* host = mpLayout->FindWindowByID(0x46967c0, 1);
  cSPUILayout* tl = tab->L();
  host->AddChildWin(tl->FindWindowByID(tab->mWinID, 1));
  SPUIHelpers::SetWindowAreaToParent(tl->FindWindowByID(tab->mWinID, 1));
  mTabs.push_back(tab);
}

// ---- 00603260: cSPUISettings::Init ------------------------------------------------------
struct cLastTab { bool OnModalWindowEnd(int a); };   // 0x006008c0

// @ 0x00603260
bool cSPUISettings::Init(int a)
{
  bool rotated = false;
  cSPUILayout* p = new ((const char*)0x13f6b3c, 0, 0, 0, 0) cSPUILayout();
  if (p != mpLayout) {
    if (p) p->AddRef();
    cSPUILayout* old = mpLayout;
    mpLayout = p;
    if (old) old->Release();
  }
  if (!mpLayout->Init(L"GameSettings", 0x40464100, 1, 0x5b598f7)) {
    cSPUILayout* l = mpLayout;
    if (l) {
      mpLayout = 0;
      l->Release();
    }
    return false;
  }

  IWin* win = mpLayout->FindWindowByID(0x43c8b98, 1);
  IWin* main = ((cSPUILayoutManager*)GetLayoutManager(0x5b598f7))->GetWorldMainWindow();
  float rot[4];
  rot[0] = 0.0f; rot[1] = gF1485720; rot[2] = 0.0f; rot[3] = gF151d728;
  const float* cur = FUN_00805260(main);
  if (cur[0] != 0.0f || cur[1] != 0.0f || cur[2] != gF1485720 || cur[3] != 0.0f) {
    SPUIHelpers::SetRotation(win, rot);
    rotated = true;
  }

  cCreditsTab13* tab0 = (cCreditsTab13*)((char*)this + 0x20);
  AddTab(tab0, (const wchar_t*)0x151d960, 0x463f008);
  AddTab((cSettingsTab*)((char*)this + 0xc0), (const wchar_t*)0x151d96c, 0x437a960);
  AddTab((cSettingsTab*)((char*)this + 0x10c),
         g_015fd918->sub->flag ? (const wchar_t*)0x151d984 : (const wchar_t*)0x151d978, 0x437a968);
  AddTab((cSettingsTab*)((char*)this + 0x160), (const wchar_t*)0x151d990, 0x437a978);
  AddTab((cSettingsTab*)((char*)this + 0x1b0), (const wchar_t*)0x151d99c, 0x46c1800);
  cLastTab* last = (cLastTab*)((char*)this + 0x1dc);
  AddTab((cSettingsTab*)last, (const wchar_t*)0x151d9a8, 0x679e383);
  if (!last->OnModalWindowEnd(a)) {
    IWin* w = mpLayout->FindWindowByID(0x473ff98, 1);
    if (w) {
      w->SetFlag(2, 0);
      w->SetFlag(0x10, 1);
    }
  }
  tab0->FUN_00600c00();
  tab0->FUN_00600e80(tab0->f9c);
  if (rotated) SPUIHelpers::ResetScrollFrameColor(win);

  IWin* w = mpLayout->FindWindowByID(0x473ff78, 1);
  if (w) {
    w->QueryChild(0x8ed27e7a)->SetState(4, 1);
    IWin* x = mpLayout->FindWindowByID(w->GetID(1), 1);
    if (x) {
      x->SetFlag(2, 1);
      x->SetFlag(1, 1);
    }
  }
  if (g_015fd918->sub->flag) {
    w = mpLayout->FindWindowByID(0x473ff88, 1);
    if (w) {
      SP::cString s;
      s.Load(0xad7b2086, 0x473ef2e, L"*capture button*");
      w->SetCaption(s.GetText());
      win->SetFlag(1, 1);
    }
  }
  IMsgListener* h = (IMsgListener*)((char*)this + 0x10);
  MessageServer()->AddListener(h, 0x238de9c);
  MessageServer()->AddListener(h, 0x62752d3);
  return true;
}

// ---- 006035d0: ShowSettingsWindow ------------------------------------------------------
struct cSPUISettings13 {
  virtual int AddRef();
  virtual int Release();
  cSPUISettings13();              // 0x00601790
  bool Init(int a);               // 0x00603260
  bool Shutdown();                // 0x00601e60
  bool Apply();                   // 0x00600ab0
  char pad[0x248 - 4];
};

// @ 0x006035d0
bool ShowSettingsWindow(int param)
{
  cSPUISettings13* p = new ((const char*)0x13f6b3c, 0, 0, 0, 0) cSPUISettings13();
  if (p) p->AddRef();
  if (p->Init(param)) {
    if (p->Apply()) {
      if (p) p->Release();
      return true;
    }
    p->Shutdown();
  }
  if (p) p->Release();
  return false;
}

// ---- 00603650: cGraphicsTab::init_profile_data -----------------------------------------
struct IRefObj { virtual int AddRef(); virtual int Release(); };
struct IPropMgr {
  PV5 PV5 PV1
  virtual bool GetPropertyList(uint32_t id, uint32_t group, IRefObj** out);   // +0x2c
};
IPropMgr* __cdecl PropertyManager();                                          // 0x0067de30
struct Str16 { wchar_t* b; wchar_t* e; wchar_t* c; uint32_t alloc; };   // 16-byte eastl string
bool __cdecl GetPropertyAsString16Array(IRefObj* props, uint32_t id, int* count, Str16** data);  // 0x006a0bc0
uint32_t __cdecl FNV1_String16(const wchar_t* s, uint32_t start, int lower);  // 0x00932f30 EA::Hash::FNV1_String16

struct ProfPair { uint32_t hash, value; };
struct cProfVec {
  ProfPair* mpBegin; ProfPair* mpEnd; ProfPair* mpCapacity;
  void erase(ProfPair* a, ProfPair* b);                                       // 0x00d018d0
  void DoInsertValue(ProfPair* pos, const ProfPair& v);                       // 0x00601b40
};
struct cGraphicsTab {
  char pad[0x40];
  cProfVec mProfiles;                                                         // +0x40
  void init_profile_data();                                                   // 0x00603650
};

// @ 0x00603650
void cGraphicsTab::init_profile_data()
{
  IRefObj* props = 0;
  IPropMgr* pm = PropertyManager();
  if (props) {
    IRefObj* t = props;
    props = 0;
    t->Release();
  }
  pm->GetPropertyList(0xe280c622, 0, &props);
  if (props) {
    int count = 0;
    Str16* data = 0;
    if (GetPropertyAsString16Array(props, 0x9f9c97de, &count, &data) && count > 0) {
      mProfiles.erase(mProfiles.mpBegin, mProfiles.mpEnd);
      for (int i = 0; i < count; i += 2) {
        ProfPair pr;
        pr.hash = FNV1_String16(data[i].b, 0x811c9dc5, 1);
        pr.value = wcstoul(data[i + 1].b + 2, 0, 16);
        if (pr.hash && pr.value) {
          if (mProfiles.mpEnd < mProfiles.mpCapacity) {
            ProfPair* e = mProfiles.mpEnd;
            mProfiles.mpEnd = e + 1;
            if (e) *e = pr;
          } else {
            mProfiles.DoInsertValue(mProfiles.mpEnd, pr);
          }
        }
      }
    }
    if (props) props->Release();
  }
}
// --- equivalence checker address annotations
    void* operator new(unsigned int, char*, int, int, int, int); // 0x00f473a0
    extern float gF1485720; // 0x01485720
    extern float gF151d728; // 0x0151d728

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
