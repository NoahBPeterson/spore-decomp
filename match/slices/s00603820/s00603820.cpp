// Slice s00603820 - cGraphicsTab / cSPUISettings settings persistence + message handling.
// Flags: /O2 /MD /Gy /TP /arch:SSE
#include "../s005fa8d0/s005fa8d0.h"

struct ConfigManagerStub14 {
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  virtual void SetValue(uint32_t id, uint32_t value);   // +0x2c
  virtual uint32_t GetValue(uint32_t id);       // +0x30
  virtual uint32_t vt34(uint32_t id);           // +0x34
  virtual void vt38(void* out);                 // +0x38
  virtual void vt3c();                          // +0x3c
  PV(16)                                        // +0x40
  virtual int vt44();                           // +0x44
  virtual bool vt48(int i, uint32_t* a, uint32_t* b, uint32_t* c);  // +0x48
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
struct Pair8 { uint32_t first; uint32_t second; };
struct VecMap14 {
  Pair8* mpBegin;                                // +0x00
  Pair8* mpEnd;                                  // +0x04
  Pair8* mpCapacity;                             // +0x08
  uint8_t pad0c[8];                              // +0x0c
  uint8_t mCompare;                              // +0x14
  uint8_t pad15[3];
  uint32_t& operator[](const uint32_t& key);     // 0x00564a10
  Pair8* find(const uint32_t& key);              // 0x00ea9bb0
};
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

// ---- cGraphicsTab (retail layout 0x58) reconstruction -----------------------------------
void FUN_00603f10();
void FUN_00603fe0();

struct Node14 { Node14* mpNext; };
struct ProfPair14 { uint32_t mListId; uint32_t mNameId; };

struct Variant14 {
  union { void* mpValue; uint32_t mValue; };
  uint8_t pad04[0x0c];
  uint8_t mFlags;                                // +0x10
  uint8_t pad11;
  uint16_t mType;                                // +0x12
  template <typename T> Variant14& operator=(const T&);
  void Destruct(bool b);                         // 0x0093db80
};

struct IWindow14;
struct IButton14;

struct IWindow14 {
  virtual int AddRef();                                   // 0   +0x00
  virtual int Release();                                  // 1   +0x04
  PV(2)                                                   //     +0x08
  virtual void* Cast(uint32_t type);                      // 3   +0x0c
  virtual void* vt10();                                   // 4   +0x10
  PV(5)                                                   //     +0x14
  PV(6)                                                   //     +0x18
  virtual uint32_t GetControlID();                        // 7   +0x1c
  virtual uint32_t GetID();                               // 8   +0x20
  PV(9)                                                   //     +0x24
  virtual void SetState(int a, int b);                    // 10  +0x28
  PV(11) PV(12) PV(13) PV(14) PV(15)                      //     +0x2c..+0x3c
  virtual uint32_t vt40();                                // 16  +0x40
  PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26)
  PV(27) PV(28) PV(29) PV(30)
  virtual void SetFlag(int flag, bool on);                // 31  +0x7c
  virtual void SetCaption(const wchar_t* text);           // 32  +0x80
  PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42)
  PV(43) PV(44) PV(45) PV(46) PV(47) PV(48) PV(49) PV(50)
  virtual void vtcc(Node14** out);                        // 51  +0xcc
  virtual Node14** vtd0(Node14** out);                    // 52  +0xd0
  PV(53) PV(54) PV(55) PV(56) PV(57) PV(58) PV(59)
  virtual IWindow14* vtf0(uint32_t id, int b);            // 60  +0xf0
  PV(61) PV(62) PV(63) PV(64)
  virtual void AddWinProc(void* proc);                    // 65  +0x104
  virtual void RemoveWinProc(void* proc);                 // 66  +0x108
  virtual IWindow14* GetNextChild(IWindow14* prev);       // 67  +0x10c
};

struct IButton14 {
  virtual int AddRef();                                   // 0   +0x00
  virtual int Release();                                  // 1   +0x04
  PV(2) PV(3)                                             //     +0x08 +0x0c
  virtual IWindow14* ToWindow();                          // 4   +0x10
  virtual void vt14(int v, int b);                        // 5   +0x14
  virtual int vt18();                                     // 6   +0x18
  PV(7) PV(8) PV(9)                                       //     +0x1c..+0x24
  virtual void SetButtonStateFlag(int flag, bool on);     // 10  +0x28
  PV(11) PV(12) PV(13) PV(14) PV(15)
  virtual uint32_t vt40();                                // 16  +0x40
};

struct ISettingsObj14 {
  PV(0) PV(1) PV(2) PV(3)
  virtual IWindow14* ToWindow();                          // 4   +0x10
  virtual void vt14(int v);                               // 5   +0x14
};

struct IRect14 {
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  PV(11) PV(12) PV(13)
  virtual float* vt38();                                  // 14  +0x38
};

Pair8* LowerBoundPair(Pair8* begin, Pair8* end, const uint32_t* key, uint8_t cmp);   // 0x005701b0

struct cProfVec14 {
  ProfPair14* mpBegin;                           // +0x00
  ProfPair14* mpEnd;                             // +0x04
  ProfPair14* mpCapacity;                        // +0x08
};

struct cSPUILayout14 {
  PV(0)
  virtual int AddRef();                                     // +0x04
  virtual int Release();                                    // +0x08
  bool Init(const Key& key, bool b, uint32_t group);        // 0x008120d0
  void GetObjects();                                        // 0x008100c0
  IWindow14* FindWindowByID(uint32_t id, int recursive);    // 0x008105b0
  uint8_t pad[0x18 - 4];
};

struct cPropertyList14 {
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
  virtual bool GetProperty(uint32_t id, Variant14** out);   // +0x24
};

struct IRefObj14 { virtual int AddRef(); virtual int Release(); };
struct IPropMgr14 {
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  virtual bool GetPropertyList(uint32_t id, uint32_t group, IRefObj14** out);   // +0x2c
};
IPropMgr14* PropertyManager14();                 // 0x0067de30

struct AppSystem14 {
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12)
  PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24)
  virtual void vt64();                                     // +0x64
};
AppSystem14* AppSystem();                        // 0x0067dd00

struct AppPrefs14 {
  PV(0) PV(1) PV(2) PV(3) PV(4)
  virtual void vt14(uint32_t hash, Variant14* var);        // +0x14
};
extern AppPrefs14* gAppPreferences14;            // 0x015fd91c

struct AppProps14 { bool GetDescription(uint32_t id); };    // 0x006a25a0
extern AppProps14* gAppProperties14;             // 0x015fd918

struct MB14 {
  void Reset();                                  // 0x0081cce0
  void* AddMenuItem3(void* key, int a, const wchar_t* text, bool b);   // 0x0081b6a0
  void OnMenuItemSelected(void* item, void* b);  // 0x0081bef0
};

struct Msg14 {
  void* mpSource;                                // +0x00
  uint32_t m04;                                  // +0x04
  uint32_t mType;                                // +0x08
  uint32_t m0c;                                  // +0x0c
  uint32_t m10;                                  // +0x10
  int m14;                                       // +0x14
};

extern uint32_t gOptionKeys14[];                 // 0x0151d5b4
extern uint32_t gWindowNodeOffset14;             // 0x01440aec

extern wchar_t gEmptyString16[];
struct WStr16 {
  wchar_t* b;
  wchar_t* e;
  wchar_t* c;
  WStr16() { b = gEmptyString16; e = gEmptyString16; c = gEmptyString16 + 1; }
  ~WStr16() { if ((((char*)c - (char*)b) & ~1) > 2 && b) operator delete[](b); }
};
void __cdecl WStr_Format(void* out, const wchar_t* fmt, ...);          // 0x0041e050
uint32_t __cdecl FNVHash(const wchar_t* s, uint32_t seed, int lower);  // 0x00932e80
void __cdecl Pollinator(void* w, float* rect);                         // 0x00806d10

struct cGraphicsTab14 {
  uint8_t pad0[0x04];
  void* mWinProc;                                // +0x04
  cSPUILayout14 mLayout;                         // +0x08
  uint32_t mId;                                  // +0x20
  VecMap14 mData;                                // +0x24
  uint8_t mbOnDataChaged;                        // +0x3c
  uint8_t pad3d[3];
  cProfVec14 mProfileData;                       // +0x40
  uint8_t pad4c[0x54 - 0x4c];
  uint8_t mbRestartRequired;                     // +0x54
  uint8_t pad55[3];

  void Init(const Key& key, void* winProc, uint32_t id);   // 0x00604260
  void init_lmh_control(uint32_t id);                      // 0x00603920
  void on_data_changed();                                  // 0x00603a10
  void load_list_options(cPropertyList14* list);           // 0x006044b0
  void set_profile(uint32_t profile);                      // 0x00604520
  bool DoMessageTab(IWindow14* window, Msg14* msg);        // 0x006045c0
  void FUN_00603820(bool a, bool b);                       // 0x00603820
  void SaveSettings();                                     // 0x00603de0
  void init_profile_data();                                // 0x00603650
};

// @ 0x006044b0
void cGraphicsTab14::load_list_options(cPropertyList14* list)
{
  for (uint32_t* p = gOptionKeys14; *p; ++p) {
    if (list) {
      Variant14* v;
      if (list->GetProperty(*p, &v) && v->mType == 0xa) {
        uint32_t* src = (v->mFlags & 0x30) ? *(uint32_t**)v : (uint32_t*)v;
        mData[*p] = *src;
      }
    }
  }
  FUN_00603820(0, 0);
}

// @ 0x00604520
void cGraphicsTab14::set_profile(uint32_t profile)
{
  if (mbOnDataChaged == true) return;
  if (profile >= (uint32_t)(mProfileData.mpEnd - mProfileData.mpBegin)) return;
  if (profile > 0) {
    IRefObj14* list = 0;
    IPropMgr14* pm = PropertyManager14();
    if (list) { IRefObj14* t = list; list = 0; t->Release(); }
    pm->GetPropertyList(mProfileData.mpBegin[profile].mListId, 0, &list);
    load_list_options((cPropertyList14*)list);
    if (list) list->Release();
  }
  mData[0x472a9c4] = profile;
}

// @ 0x00603920
void cGraphicsTab14::init_lmh_control(uint32_t id)
{
  uint32_t value = mData[id];
  IWindow14* w = mLayout.FindWindowByID(mId, 1);
  IWindow14* w2 = w->vtf0(id, 1);
  if (w2) {
    w2->AddRef();
    Node14* cur;
    Node14* end;
    w2->vtcc(&cur);
    while (cur != *w2->vtd0(&end)) {
      IWindow14* obj = (IWindow14*)((char*)cur + gWindowNodeOffset14);
      if (obj->GetID() == value) {
        if (obj) {
          IButton14* b = (IButton14*)obj->Cast(0x8ed27e7a);
          if (b) b->SetButtonStateFlag(4, true);
        }
      }
      cur = cur->mpNext;
    }
    w2->Release();
  }
}

// @ 0x00603820
void cGraphicsTab14::FUN_00603820(bool a, bool b)
{
  struct Cfg14 { uint32_t* mpBegin; uint32_t* mpEnd; void* mpRef; };
  VecMap14& data = mData;
  Cfg14 cfg = { 0, 0, 0 };
  ConfigManager()->vt38(&cfg);
  for (uint32_t* p = gOptionKeys14; *p; ++p) {
    if (a == 0) {
      Pair8* it = LowerBoundPair(data.mpBegin, data.mpEnd, p, data.mCompare);
      if (it == data.mpEnd || *p < it->first)
        it = data.mpEnd;
      else if (it == it + 1)
        it = data.mpEnd;
      if (it->second == 0xffffffff)
        continue;
    }
    uint32_t value;
    if (b == 0) {
      uint32_t* q = cfg.mpBegin;
      uint32_t* e = cfg.mpEnd;
      while (q != e && *q != *p) ++q;
      value = (q != e) ? ConfigManager()->GetValue(*p) : ConfigManager()->vt34(*p);
    } else {
      value = ConfigManager()->vt34(*p);
    }
    data[*p] = value;
  }
  if (cfg.mpBegin && ((int*)cfg.mpBegin)[-1])
    operator delete(cfg.mpBegin);
}

// @ 0x00604260
void cGraphicsTab14::Init(const Key& key, void* winProc, uint32_t id)
{
  mId = id;
  mWinProc = winProc;
  mLayout.Init(key, 0, 0x5b598fa);
  mLayout.GetObjects();
  mLayout.FindWindowByID(mId, 1)->AddWinProc(mWinProc);
  if (&mLayout) {
    IWindow14* w = mLayout.FindWindowByID(0x5caca50, 1);
    if (w) {
      ISettingsObj14* o = (ISettingsObj14*)w->Cast(0x8ed27e7a);
      if (o) {
        o->vt14(0);
        IRect14* r = (IRect14*)w->vt10();
        if (r) {
          float* p = r->vt38();
          float rect[4];
          rect[0] = p[0] - p[0];
          rect[1] = p[1] - p[1];
          rect[2] = p[2] - p[0];
          rect[3] = p[3] - p[1];
          Pollinator(w, rect);
        }
      }
    }
  }
  for (uint32_t* p = gOptionKeys14; *p; ++p)
    mData[*p] = 0xffffffff;
  init_profile_data();
  FUN_00603820(1, 0);
  on_data_changed();
  if (gAppProperties14->GetDescription(0x5dd4647)) {
    IWindow14* w = mLayout.FindWindowByID(mId, 1);
    IWindow14* w2 = w->vtf0(0x61c90b8, 1);
    bool desc = gAppProperties14->GetDescription(0x61b67b6);
    IWindow14* w3 = w2->vtf0(0x695b460, 1);
    if (w3) w3->SetFlag(1, desc);
    if (desc) {
      IWindow14* w4 = w2->vtf0(0x695b438, 1);
      if (w4) w4->SetFlag(1, 0);
      IWindow14* w5 = w2->vtf0(0x5b591c0, 1);
      if (w5) w5->SetFlag(1, 0);
    } else {
      w2->SetFlag(1, 0);
      w2->SetFlag(2, 0);
    }
  }
  FUN_00603f10();
}

// @ 0x00603de0
void cGraphicsTab14::SaveSettings()
{
  uint32_t key = 0x46170a2;
  if (ConfigManager()->GetValue(key) != mData[key])
    AppSystem()->vt64();
  uint32_t* it = gOptionKeys14;
  while (*it != 0x46170a3) {
    if (++it == gOptionKeys14 + 0xd) break;
  }
  uint32_t idx = (uint32_t)(it - gOptionKeys14);
  if (idx < 0xd && ConfigManager()->GetValue(0x46170a3) != gOptionKeys14[idx]) {
    Variant14 var;
    var = 1;
    gAppPreferences14->vt14(FNVHash((const wchar_t*)0x13fa4fc, 0x811c9dc5, 1), &var);
    if (var.mFlags & 4) var.Destruct(false);
  }
  for (uint32_t* p = gOptionKeys14; *p; ++p)
    ConfigManager()->SetValue(*p, mData[*p]);
}

// @ 0x00603a10
void cGraphicsTab14::on_data_changed()
{
  mbOnDataChaged = 1;
  init_lmh_control(0x461709e);
  init_lmh_control(0x461709f);
  init_lmh_control(0x46170a0);
  init_lmh_control(0x46170a3);
  init_lmh_control(0x46170a6);
  init_lmh_control(0x46170a7);
  init_lmh_control(0x4c0dd839);

  IButton14* temp = 0;
  {
    IWindow14* w = mLayout.FindWindowByID(mId, 1);
    IWindow14* w2 = w->vtf0(0x46170a4, 1);
    if (w2) {
      IButton14* b = (IButton14*)w2->Cast(0xaf062e1d);
      temp = b;
      if (b) {
        b->AddRef();
        WStr16 str;
        WStr_Format(&str, (const wchar_t*)0x13fa490, mData[0x46170a4] << 8);
        IWindow14* w3 = mLayout.FindWindowByID(mId, 1)->vtf0(0x4728b30, 0);
        w3->SetCaption(str.b);
      }
    }
  }

  {
    IWindow14* w = mLayout.FindWindowByID(mId, 1)->vtf0(0x46170a1, 1);
    MB14* menu = w ? (MB14*)w->Cast(0x4c058d5) : 0;
    if (menu) {
      int count = ConfigManager()->vt44();
      menu->Reset();
      for (int i = 0; i < count; ++i) {
        uint32_t a, b, c;
        if (!ConfigManager()->vt48(i, &a, &b, &c)) break;
        WStr16 str;
        WStr_Format(&str, L"%4u x %4u @ %3uHz", a, b, c);
        Key mkey = { 0xa10d844a, 0x510a95b, 0x40464100 };
        void* item = menu->AddMenuItem3(&mkey, 0, str.b, true);
        if (i == mData[0x46170a1]) menu->OnMenuItemSelected(item, 0);
      }
    }
  }

  IButton14* btn = 0;
  {
    IWindow14* w = mLayout.FindWindowByID(mId, 1)->vtf0(0x5b591c0, 1);
    if (w) {
      IButton14* b = (IButton14*)w->Cast(0x8ed27e7a);
      if (b) {
        b->AddRef();
        if (mData[0x46170a2] != 0) b->SetButtonStateFlag(4, true);
        else b->SetButtonStateFlag(4, false);
        btn = b;
      }
    }
    IWindow14* w2 = mLayout.FindWindowByID(mId, 1)->vtf0(0x6f20fb8, 1);
    IButton14* b2 = w2 ? (IButton14*)w2->Cast(0x8ed27e7a) : 0;
    if (b2 != btn) {
      IButton14* old = btn;
      if (b2) b2->AddRef();
      btn = b2;
      if (old) old->Release();
    }
  }
  if (btn)
    btn->SetButtonStateFlag(4, mData[0x46170a5] != 0);
  mbOnDataChaged = 0;
  if (btn) btn->Release();
  if (temp) temp->Release();
}

// @ 0x006045c0
bool cGraphicsTab14::DoMessageTab(IWindow14* window, Msg14* msg)
{
  if (mbOnDataChaged) return false;
  if (msg->mType == 0x18) {
    IWindow14* src = (IWindow14*)msg->mpSource;
    if (src) {
      IButton14* b = (IButton14*)src->Cast(0x8ed27e7a);
      if (b) {
        uint32_t key;
        if (b->ToWindow()->GetControlID() == 0x5b591c0) {
          key = 0x46170a2;
        } else if (b->ToWindow()->GetControlID() == 0x6f20fb8) {
          key = 0x46170a5;
        } else {
          if (msg->m14 == 0) return false;
          if (b->vt18() != 3) return false;
          Pair8* it = mData.find(b->vt40());
          if (it == mData.mpEnd) return false;
          it->second = ((IWindow14*)msg->mpSource)->GetID();
          set_profile(0);
          on_data_changed();
          return true;
        }
        mData[key] = msg->m14;
        if (mbOnDataChaged != 1 && (uint32_t)(mProfileData.mpEnd - mProfileData.mpBegin) > 0)
          mData[0x472a9c4] = 0;
        on_data_changed();
        return true;
      }
    }
    return false;
  }
  if (msg->mType == 0xaf0b6441) {
    if (((IWindow14*)msg->mpSource)->GetID() == 0x46170a4) {
      uint32_t v = msg->m14;
      WStr16 str;
      WStr_Format(&str, (const wchar_t*)0x13fa490, v);
      mData[0x46170a4] = v >> 8;
      if (mbOnDataChaged != 1 && (uint32_t)(mProfileData.mpEnd - mProfileData.mpBegin) > 0)
        mData[0x472a9c4] = 0;
      on_data_changed();
      return true;
    }
    return false;
  }
  if (msg->mType == 0x17 && msg->m0c == 0x472a5c0) {
    if (mbOnDataChaged != 1 && (uint32_t)(mProfileData.mpEnd - mProfileData.mpBegin) > 0)
      mData[0x472a9c4] = 0;
    FUN_00603820(1, 1);
    on_data_changed();
    return true;
  }
  if (msg->mType == 0x4cab02d) {
    mData[0x46170a1] = msg->m10;
    return true;
  }
  return false;
}

// ---- leftover free stubs (nonmatching rows 00603f10/00603fe0 map to GraphicsTabF10) ------
void FUN_00603f10() {}
void FUN_00603fe0() {}
