// Slice s00e12f80 (batch bfs0, slice 31). Region 0xe12f80-0xe13b49.
// SP::cUICard / SP::cUIMissionCard UI helpers: vtable-forwarding wrappers, Toggle,
// animation tick, message handling, destructor and the large InitForCreature.
// Optimised: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"
#include <math.h>

static inline void** Vt(void* p) { return *(void***)p; }

struct Rect { float left, top, right, bottom; };
// EA::UTFWin::IWindow (retail vtable; unused slots are placeholders)
struct IWindow {
  virtual void AddRef();                              // 0x00
  virtual void Release();                             // 0x04
  virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14();
  virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
  virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34();
  virtual const Rect& GetArea();                      // 0x38
  virtual const void* GetCaption();                   // 0x3c
  virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
  virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
  virtual void v60(); virtual void v64();
  virtual void SetSize(float w, float h);             // 0x68
  virtual void v6c();
  virtual void SetLayoutLocation(float x, float y);   // 0x70
  virtual void v74(); virtual void v78();
  virtual void SetFlag(int flag, bool v);             // 0x7c
  virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
  virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
  virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac();
  virtual void vb0(); virtual void vb4(); virtual void vb8(); virtual void vbc();
  virtual void vc0(); virtual void vc4(); virtual void vc8(); virtual void vcc();
  virtual void vd0(); virtual void vd4(); virtual void vd8(); virtual void vdc();
  virtual void ve0(); virtual void ve4(); virtual void ve8(); virtual void vec();
  virtual IWindow* FindWindowByID(uint32_t id, bool recursive);  // 0xf0
};
// interface obtained from an AutoRefCount<IWindow> (0x5e1fd0): slot 0x14 takes a bool
struct IWinExt {
  virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
  virtual void SetOption(bool v);                     // 0x14
};
// EA::UTFWinControls::IWinButton (0x5ca960): slot 0x28 takes (int, int)
struct IWinButton {
  virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
  virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
  virtual int Command(int a, int b);                 // 0x28
};
struct cSPUIAnimator {
  void CancelAll();                                   // 0x7f8f00
  void AddAnimation(const struct AnimTmp& anim, IWindow* w, int flags);   // 0x7f8d10
};
struct AnimTmp { uint32_t d[0x1f]; ~AnimTmp(); };     // dtor body 0x59a1e0
struct Vec2 { float x, y; Vec2(float a, float b) : x(a), y(b) {} };

// ---- external callees (masked relocations) ----
extern "C" float __cdecl SPUIHelpers_GetElapsedSeconds();     // 0x805080
extern "C" bool  __fastcall cSPUIAnimator_Empty(void* self);  // 0x7f6340
extern "C" void  __fastcall cSPUIAnimator_Update(void* self); // 0x7f63b0
struct cSPUILayout {
  void Shutdown(int);          // 0x811ad0
  void SetVisibility(int);     // 0x810590
};
extern "C" void  __cdecl FUN_00e2ed40();                      // 0xe2ed40
extern "C" void* __cdecl FUN_00b3d3f0(int a, void* b);        // 0xb3d3f0
extern "C" void  __fastcall FUN_00e18dd0(void* self);         // 0xe18dd0
extern "C" void* __cdecl SP_GetCurrentGameMode();             // 0xb5b800
extern "C" void* __cdecl SPUIHelpers_AutoSizeWindowForText(void* w, int a, int b); // 0x806e40
extern "C" void  __fastcall FUN_007f8f00(void* self);         // 0x7f8f00

// ---------------------------------------------------------------------------------------
// SP::cUICard (offsets taken from the destructor and accessors)
// ---------------------------------------------------------------------------------------
struct cUICard {
  void*    vtbl;    // +0x00
  void*    vtbl4;   // +0x04
  uint32_t pad8;    // +0x08
  void*    p0c;     // +0x0c cSPUILayout*
  uint8_t  b10;     // +0x10
  uint8_t  b11;     // +0x11
  uint8_t  pad12[0x0a];
  void*    p1c;     // +0x1c cSPUILayout*
  void*    p20;     // +0x20
  IWindow* p24;     // +0x24
  cSPUIAnimator* p28;     // +0x28
  IWindow* p2c;     // +0x2c
  IWindow* p30;     // +0x30
  IWindow* p34;     // +0x34
  IWindow* p38;     // +0x38
  IWindow* p3c;     // +0x3c
  IWindow* p40;     // +0x40
  IWindow* p44;     // +0x44

  void Toggle();                     // 0xe12fe0
  void Release2();                   // 0xe13210 (destructor)
  void Teardown();                   // 0xe132c0
  void SetVisible(int);              // 0xe13360
  IWindow* DoVcallF0(int);               // 0xe13390
  bool HandleMessage(void* msg, int);  // 0xe130b0
};

// @ 0x00e12f80
void FUN_00e12f80(void* p, int v) {
  if (p) ((void(__thiscall*)(void*, int, int))Vt(p)[0x7c / 4])(p, 1, v);
}

// @ 0x00e12fa0
void FUN_00e12fa0(void* p, int v) {
  if (p) ((void(__thiscall*)(void*, int, int))Vt(p)[0x7c / 4])(p, 2, v);
}

// @ 0x00e12fc0
void FUN_00e12fc0(void* p, int v) {
  if (p) ((void(__thiscall*)(void*, int))Vt(p)[0x80 / 4])(p, v);
}

// @ 0x00e12fe0
void cUICard::Toggle() {
  if (b10) ((void(__thiscall*)(void*, int))Vt(this)[0x2c / 4])(this, 1);
  else     ((void(__thiscall*)(void*, int))Vt(this)[0x28 / 4])(this, 1);
}

// @ 0x00e13000
void __fastcall FUN_00e13000(void* self) {
  SPUIHelpers_GetElapsedSeconds();
  if (*(void**)((char*)self + 0x28)) {
    if (!cSPUIAnimator_Empty(*(void**)((char*)self + 0x28))) {
      *(uint8_t*)((char*)self + 0x11) = 1;
      cSPUIAnimator_Update(*(void**)((char*)self + 0x28));
      return;
    }
  }
}

// @ 0x00e130b0
bool cUICard::HandleMessage(void* msg, int) {
  if (*(int*)((char*)msg + 8) == 0xc)
    ((void(__thiscall*)(void*))Vt(this)[0x24 / 4])(this);
  int kind = *(int*)((char*)msg + 0xc);
  if (kind == 0x5235138) {
    if (*(int*)((char*)msg + 8) == 0x287259f6) {
      void* r = FUN_00b3d3f0(-0xc, this);
      FUN_00e18dd0(r);
    }
    return true;
  } else if (kind == 0x5235aa8) {
    if (*(int*)((char*)msg + 8) == 0x287259f6)
      ((void(__thiscall*)(void*))Vt(this)[0x20 / 4])(this);
    return true;
  }
  return false;
}

// @ 0x00e13160
int __stdcall FUN_00e13160(void* a, void* b) {
  void* x;
  if (a) x = (void*)((int(__thiscall*)(void*, int))Vt(a)[0xc / 4])(a, 0x334c6eec);
  else x = 0;
  void* y;
  if (b) y = (void*)((int(__thiscall*)(void*, int))Vt(b)[0xc / 4])(b, 0x334c6eec);
  else y = 0;
  if (a) ((void(__thiscall*)(void*, int))Vt(a)[0xc / 4])(a, 0x334c6eef);
  void* z;
  if (b) z = (void*)((int(__thiscall*)(void*, int))Vt(b)[0xc / 4])(b, 0x334c6eef);
  else z = 0;
  if (x) {
    if (y) return *(float*)((char*)x + 0x98) > *(float*)((char*)y + 0x98);
    if (z) return 1;
  }
  return 0;
}

// @ 0x00e13210
void cUICard::Release2() {
  void* q;
  q = p44; if (q) ((void(__thiscall*)(void*))Vt(q)[4 / 4])(q);
  q = p40; if (q) ((void(__thiscall*)(void*))Vt(q)[4 / 4])(q);
  q = p3c; if (q) ((void(__thiscall*)(void*))Vt(q)[4 / 4])(q);
  q = p38; if (q) ((void(__thiscall*)(void*))Vt(q)[4 / 4])(q);
  q = p34; if (q) ((void(__thiscall*)(void*))Vt(q)[4 / 4])(q);
  q = p30; if (q) ((void(__thiscall*)(void*))Vt(q)[4 / 4])(q);
  q = p2c; if (q) ((void(__thiscall*)(void*))Vt(q)[4 / 4])(q);
  q = p24; if (q) ((void(__thiscall*)(void*))Vt(q)[4 / 4])(q);
  q = p20; if (q) ((void(__thiscall*)(void*))Vt(q)[8 / 4])(q);
  q = p1c; if (q) ((void(__thiscall*)(void*))Vt(q)[8 / 4])(q);
  q = p0c; if (q) ((void(__thiscall*)(void*))Vt(q)[8 / 4])(q);
  *(void**)((char*)this + 4) = (void*)0x13ec458;
  *(void**)this = (void*)0x13eb938;
}

// @ 0x00e132c0
void cUICard::Teardown() {
  void* q = p24;
  ((void(__thiscall*)(void*, void*))Vt(q)[0x108 / 4])(q, this);
  q = p24;
  if (q) { p24 = 0; ((void(__thiscall*)(void*))Vt(q)[4 / 4])(q); }
  q = p1c;
  ((cSPUILayout*)q)->Shutdown(1);
  q = p1c;
  if (q) { p1c = 0; ((void(__thiscall*)(void*))Vt(q)[8 / 4])(q); }
  q = p28;
  if (q) { ((void(__thiscall*)(void*, int))Vt(q)[0 / 4])(q, 1); p28 = 0; }
  q = p0c;
  if (q) {
    ((cSPUILayout*)q)->Shutdown(1);
    q = p0c;
    if (q) { p0c = 0; ((void(__thiscall*)(void*))Vt(q)[8 / 4])(q); }
  }
  q = p20;
  if (q) FUN_00e2ed40();
  q = p20;
  if (q) { p20 = 0; ((void(__thiscall*)(void*))Vt(q)[8 / 4])(q); }
}

// @ 0x00e13360
void cUICard::SetVisible(int v) {
  if (p1c) {
    ((cSPUILayout*)p1c)->SetVisibility(v);
    void* q = p24;
    if (q) ((void(__thiscall*)(void*, int, int))Vt(q)[0x7c / 4])(q, 1, v);
  }
}

// @ 0x00e13390
IWindow* cUICard::DoVcallF0(int v) {
  return p24->FindWindowByID(v, true);
}

// @ 0x00e133b0  SP::cUIMissionCard::InitForCreature
extern "C" void __cdecl AutoSizeWindowForText(IWindow* w, int a, int b);   // 0x806e40
IWinExt*   __cdecl QueryWinExt(IWindow** ref);                              // 0x5e1fd0
IWinButton* __cdecl CastWinButton(IWindow* w);                              // 0x5ca960
AnimTmp __cdecl SPUICreateWindowAnimationTargetSize(IWindow* win, const Vec2& size,
                                                    float duration, float from, int type);   // 0x7f8230

struct cUIMissionCard : cUICard {
  char  pad48[0x68 - 0x48];
  float f68, f6c, f70, f74;     // +0x68 rect
  float f78, f7c, f80, f84;     // +0x78 rect
  float f88, f8c, f90, f94;     // +0x88 rect
  __declspec(noinline) void InitForCreature(bool animate, int kind);
  void Expand(bool a);
};

static inline float Height(const Rect& r) { return r.bottom - r.top; }

void cUIMissionCard::InitForCreature(bool animate, int kind) {
  IWindow* card = DoVcallF0(((int(__thiscall*)(void*))Vt(this)[0x38 / 4])(this));
  IWindow* old = p40;
  if (old && old != card) old->SetFlag(1, false);
  old = p40;
  if (card != old) {
    if (card) card->AddRef();
    p40 = card;
    if (old) old->Release();
  }
  if (!p30 || !p38 || !p3c || !p44 || !card) return;
  float t = SPUIHelpers_GetElapsedSeconds();
  p28->CancelAll();
  const Rect& compArea = p38->GetArea();
  const Rect& area3c = p3c->GetArea();
  const Rect& cardArea = card->GetArea();
  const Rect& area44 = p44->GetArea();
  AutoSizeWindowForText(p30, 0, 1);
  const Rect& bgArea = p30->GetArea();
  float top0 = bgArea.top;
  float bottom0 = bgArea.bottom;
  if (SP_GetCurrentGameMode() == (void*)0x1654c10) {
    IWindow* a = DoVcallF0(0x7f453b8);
    IWindow* b = DoVcallF0(0x7f5abd0);
    b->GetArea();
    float h1 = Height(p30->GetArea());
    float h2 = Height(a->GetArea());
    bool big = h1 > h2;
    FUN_00e12f80(a, big);
    FUN_00e12f80(p30, !big);
    if (big) {
      const Rect& r = a->GetArea();
      top0 = r.top;
      bottom0 = r.bottom;
    }
  }
  float y = (bottom0 - top0) + top0;
  if (p2c && p2c->GetCaption()) {
    IWindow* dw = p2c;
    dw->SetLayoutLocation(dw->GetArea().left, y);
    QueryWinExt(&p2c)->SetOption(true);
    const Rect& d = p2c->GetArea();
    y = (d.bottom - d.top) + y;
  }
  IWindow* cw = p34;
  cw->SetLayoutLocation(cw->GetArea().left, y);
  bool notMode = SP_GetCurrentGameMode() != (void*)0x1654c10;
  IWinExt* ext = QueryWinExt(&p34);
  if (notMode) ext->SetOption(true);
  const Rect& c = p34->GetArea();
  float y2 = (c.bottom - c.top) + c.top;
  card->SetLayoutLocation(cardArea.left, y2);
  card->SetFlag(1, true);
  float y3 = (cardArea.bottom - cardArea.top) + y2;
  IWindow* w;
  switch (kind) {
  case 1: w = DoVcallF0(0x574efda); break;
  case 2: w = DoVcallF0(0xf5a74bec); break;
  default: goto skip;
  }
  if (w) {
    const Rect& r = w->GetArea();
    float hh = r.bottom - r.top;
    float yy = y3 - top0;
    if (hh > yy) y3 = (hh - yy) + y3;
    w->SetLayoutLocation(r.left, (((y3 - top0) * 0.5f) + top0) - hh * 0.5f);
  }
skip:
  Rect ra, rb, rc;
  ra.left = f68;
  ra.top = f6c;
  ra.right = (f70 - f68) + f68;
  ra.bottom = (f6c + (float)fabs(y3 - f6c)) + 8.0f;
  rb.left = f78;
  rb.top = f7c;
  rb.right = (f80 - f78) + f78;
  rb.bottom = (f7c + (float)fabs(y3 - f7c)) + 8.0f;
  rc.left = f88;
  rc.top = f8c;
  rc.right = (f90 - f88) + f88;
  rc.bottom = ((ra.bottom - f74) + (f94 - f8c)) + f8c;
  IWindow* w35 = DoVcallF0(0x35b08191);
  float wA = ra.bottom - ra.top;
  if (animate) {
    p28->AddAnimation(SPUICreateWindowAnimationTargetSize(p38, Vec2(ra.right - ra.left, wA), t,
        (float)fabs(wA - Height(compArea)) * 0.002f, 1), p38, 0);
    if (notMode) {
      float wB = rb.bottom - rb.top;
      p28->AddAnimation(SPUICreateWindowAnimationTargetSize(p3c, Vec2(rb.right - rb.left, wB), t,
          (float)fabs(wB - Height(area3c)) * 0.002f, 1), p3c, 0);
    }
    float wC = rc.bottom - rc.top;
    p28->AddAnimation(SPUICreateWindowAnimationTargetSize(p44, Vec2(rc.right - rc.left, wC), t,
        (float)fabs(wC - Height(area44)) * 0.002f, 1), p44, 0);
    if (w35) {
      p28->AddAnimation(SPUICreateWindowAnimationTargetSize(w35, Vec2(rc.right - rc.left, wC), t,
          (float)fabs(wC - Height(area44)) * 0.002f, 1), w35, 0);
    }
  } else {
    p38->SetSize(ra.right - ra.left, wA);
    if (notMode) p3c->SetSize(rb.right - rb.left, rb.bottom - rb.top);
    p44->SetSize(rc.right - rc.left, rc.bottom - rc.top);
    if (w35) w35->SetSize(rc.right - rc.left, rc.bottom - rc.top);
  }
  IWindow* bw = DoVcallF0(0x5397388);
  if (bw) {
    IWinButton* btn = CastWinButton(bw);
    if (btn) btn->Command(4, 1);
  }
}

// @ 0x00e13b30
void cUIMissionCard::Expand(bool a) {
  InitForCreature(a, 0);
  ((void(__thiscall*)(void*))Vt(this)[0x30 / 4])(this);
}
