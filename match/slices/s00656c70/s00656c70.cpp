#include "types.h"

struct IWindow {
  virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
  virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
  virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
  virtual void v0c(); virtual void v0d();
  virtual int GetControlID();            // 0x38
  virtual void v0f(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
  virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
  virtual void v18(); virtual void v19(); virtual void v1a();
  virtual void SetControlID(int id);     // 0x6c
  virtual void v1c(); virtual void v1d(); virtual void v1e();
  virtual void SetFlag(int flag, bool value); // 0x7c
};

struct ResKey { int a; uint32_t typeID; };
struct IItem {
  virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
  virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
  virtual void v08();
  virtual int Get24();                    // 0x24
  virtual void v0a(); virtual void v0b(); virtual void v0c(); virtual void v0d();
  virtual void v0e(); virtual void v0f();
  virtual ResKey* GetKey();               // 0x40
  virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
  virtual void v15(); virtual void v16(); virtual void v17();
  virtual bool Is60();                    // 0x60
  virtual void v19();
  virtual bool Is68();                    // 0x68
  virtual void v1b();
  virtual bool Is70();                    // 0x70
  virtual void v1d(); virtual void v1e();
  virtual bool Is7c();                    // 0x7c
  virtual bool Is80();                    // 0x80
};

struct ItemVec { IItem** mpBegin; IItem** mpEnd; IItem** mpCap; int mAllocator[2];
  uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
  bool empty() const { return mpBegin == mpEnd; }
  void insert(IItem** pos, IItem* const& v);
};

struct Params { uint32_t id; bool f0, f1, f2; int index; bool f3;
  Params() : id(0), f0(false), f1(false), f2(false), index(1), f3(false) {} };

struct WindowMgr { IWindow* FindWindowByID(uint32_t id, bool recursive); };
struct Game { int Get645d90(); int Get6447b0(); bool Is6448e0(); };
Game* GetGame();
bool FUN_004bbe20(uint32_t type, int);
int FUN_00432f10(int);
void FUN_00806bf0(int);
void EASTL_allocator_deallocate(void* p);
extern uint32_t g_ControlIDs[6];

struct Panel {
  char pad0[0x10];
  bool m10;
  char pad11[3];
  WindowMgr* m14;
  char pad18[4];
  IWindow* m1c;
  char pad20[4];
  IWindow* m24;
  char pad28[4];
  IWindow* m2c;
  int m30;
  void FUN_00656510(Params* p);
  void FUN_00656770(Params* p);
  void FUN_00656830(int i);
  __forceinline void ShowPair(uint32_t a, uint32_t b) {
    IWindow* w1 = m14->FindWindowByID(a, true);
    IWindow* w2 = m14->FindWindowByID(b, true);
    if (w1) w1->SetFlag(1, true);
    if (w2) w2->SetFlag(0x10, true);
  }
  inline void Link(bool v) {
    IWindow* w1 = m14->FindWindowByID(0x668ad90, true);
    IWindow* w2 = m14->FindWindowByID(0x668ada0, true);
    if (w1 && w2) {
      w1->SetFlag(1, !v);
      w2->SetControlID(w1->GetControlID());
      w2->SetFlag(1, v);
    }
  }
  void Update(bool show, const Params* p, ItemVec* items);
  void Update(bool show, const Params* p, IItem* item);
};

// @ 0x00656c70
void Panel::Update(bool show, const Params* p, ItemVec* items) {
  Params s;
  if (p) s = *p;
  uint32_t id = s.id;
  bool f1 = s.f1;
  m10 = show;
  if (m1c) {
    m1c->SetFlag(1, show);
    FUN_00806bf0(m30);
  }
  FUN_00656510(&s);
  FUN_00656770(&s);
  if (m24 && m2c && s.f0) {
    m24->SetFlag(1, true);
    m2c->SetFlag(1, true);
  }
  if (show && !items->empty()) {
    int idx = 6;
    if (id) {
      for (int i = 0; i < 6; i++) {
        if (g_ControlIDs[i] == id) {
          idx = i;
          FUN_00656830(i);
        }
      }
    }
    bool all68 = true, all70 = true, all7c = true, all80 = true;
    bool e = false, g = false;
    for (uint32_t i = 0; i < items->size(); i++) {
      IItem* it = items->mpBegin[i];
      if (it->Is68()) {
        if (!it->Is70()) all70 = false;
      } else {
        all68 = false;
      }
      if (!it->Is7c()) all7c = false;
      if (!it->Is80()) all80 = false;
    }
    if (items->size() == 1) {
      IItem* it = items->mpBegin[0];
      e = f1 && it->Is60();
      if (FUN_004bbe20(it->GetKey()->typeID, 0)) {
        int x = GetGame()->Get645d90();
        int y = GetGame()->Get6447b0();
        if (x == -1) x = FUN_00432f10(it->Get24());
        g = s.f3 && x != y && it->Is60() && it->GetKey()->typeID == 0x2b978c46;
      }
    } else if (!all70) {
      goto other;
    }
    if (all68) {
      if (all70) {
        Link(true);
      } else {
        ShowPair(0x54acb9f5, 0x668ad90);
        Link(false);
      }
    } else {
    other:
      Link(false);
    }
    if (all7c && GetGame() && !GetGame()->Is6448e0()) ShowPair(0x54acb9f6, 0x667d118);
    if (all80) ShowPair(0x54acb9e0, 0x668adb0);
    if (e) ShowPair(0x54acb9f1, 0x667d120);
    if (g) ShowPair(0x54acb9f2, 0x7a43648);
    if (s.index >= 0 && items->size() > (uint32_t)s.index && idx != 6)
    {
      WindowMgr* m = m14;
      m->FindWindowByID(g_ControlIDs[idx], true)->SetFlag(1, false);
    }
  }
}

// @ 0x006571e0
void Panel::Update(bool show, const Params* p, IItem* item) {
  IItem** b = 0;
  ItemVec v;
  v.mpBegin = b;
  v.mpEnd = b;
  v.mpCap = b;
  if (item) {
    v.insert(v.mpEnd, item);
    b = v.mpBegin;
  }
  Update(show, p, &v);
  if (b && ((int*)b)[-1]) EASTL_allocator_deallocate(b);
}

struct ITelemetry {
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
  virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
  virtual int GetValue();                                // 0x20
  virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
  virtual void BeginEvent(uint32_t id);                  // 0x38
  virtual void v15();
  virtual void AddUInt32(uint32_t key, uint32_t value);  // 0x40
  virtual void v17(); virtual void v18(); virtual void v19();
  virtual void AddUInt32b(uint32_t key, uint32_t value); // 0x50
  virtual void v21();
  virtual void EndEvent();                               // 0x58
};
ITelemetry* GetTelemetry();  // FUN_00a206f0

// @ 0x00657240
void LogEvent_3475331(uint32_t a, uint32_t b, uint32_t c) {
  ITelemetry* t = GetTelemetry();
  if (t) {
    t->BeginEvent(0x3475331);
    t->AddUInt32(0x3475381, a);
    t->AddUInt32(0x3475385, b);
    if (c) t->AddUInt32b(0x39e41ea, c);
    t->EndEvent();
  }
}

// @ 0x006572b0
void LogEvent_3475365(uint32_t a) {
  ITelemetry* t = GetTelemetry();
  if (t) {
    t->BeginEvent(0x3475365);
    t->AddUInt32(0x3475385, a);
    t->EndEvent();
  }
}

// @ 0x006572f0
void LogEvent_673a567(uint32_t a, uint32_t b) {
  ITelemetry* t = GetTelemetry();
  if (t) {
    t->BeginEvent(0x673a567);
    t->AddUInt32(0x4362049, a);
    t->AddUInt32(0x3475385, b);
    t->EndEvent();
  }
}

struct CastCls { void* Cast(uint32_t id); };

// @ 0x00657340
void* CastCls::Cast(uint32_t id) {
  if (id == 0xee3f516e) return this;
  if (id == 0x2f009dd0) return this;
  if (id == 0x73cc339e) return this;
  return 0;
}

// @ 0x00657370
bool LogEvent_4e79d7d1() {
  ITelemetry* t0 = GetTelemetry();
  int v = t0 ? t0->GetValue() : 0;
  ITelemetry* t = GetTelemetry();
  if (t) {
    t->BeginEvent(0x3475365);
    t->AddUInt32(0x3475381, 0x4e79d7d1);
    t->AddUInt32(0x3475385, v);
    t->EndEvent();
  }
  return false;
}

extern int g_15f9f40;

// @ 0x006573e0
int GetGlobal_15f9f40() { return g_15f9f40; }

struct Vec3 { float x, y, z; };
extern Vec3 g_1526560;
struct Vec3Holder { Vec3 Get(); };

// @ 0x006573f0
Vec3 Vec3Holder::Get() { return g_1526560; }

struct VObj {
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
  virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
  virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
  virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
  virtual void Enable(); virtual void Disable();
};

// @ 0x00657420
void SetEnabled(VObj* o, int, bool b) {
  if (!b) o->Disable();
  else o->Enable();
}

struct ISub { virtual void a(); virtual void b(); virtual void c(); virtual void* Cast(uint32_t); };
struct Outer { char pad[0x10]; ISub sub; };

// @ 0x00657440
void* CastSub(Outer** p) {
  if (*p) return (*p)->sub.Cast(0x13d55dc8);
  return 0;
}
