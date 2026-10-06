// Slice s00e12f80 (batch bfs0, slice 31). Region 0xe12f80-0xe13b49.
// SP::cUICard / SP::cUIMissionCard UI helpers: vtable-forwarding wrappers, Toggle,
// animation tick, message handling, destructor and the large InitForCreature.
// Optimised: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"

static inline void** Vt(void* p) { return *(void***)p; }

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
  void*    p24;     // +0x24
  void*    p28;     // +0x28 cSPUIAnimator*
  void*    p2c;     // +0x2c
  void*    p30;     // +0x30
  void*    p34;     // +0x34
  void*    p38;     // +0x38
  void*    p3c;     // +0x3c
  void*    p40;     // +0x40
  void*    p44;     // +0x44

  void Toggle();                     // 0xe12fe0
  void Release2();                   // 0xe13210 (destructor)
  void Teardown();                   // 0xe132c0
  void SetVisible(int);              // 0xe13360
  void DoVcallF0(int);               // 0xe13390
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
void cUICard::DoVcallF0(int v) {
  ((void(__thiscall*)(void*, int, int))Vt(p24)[0xf0 / 4])(p24, v, 1);
}

// @ 0x00e133b0  SP::cUIMissionCard::InitForCreature -- partial (see partial.txt)
struct cUIMissionCard {
  void InitForCreature(int a, int b);
  void Expand(int a);
};

void cUIMissionCard::InitForCreature(int a, int b) {
  char* self = (char*)this;
  int r = ((int(__thiscall*)(void*))Vt(self)[0x38 / 4])(self);
  void* card = ((void*(__thiscall*)(void*, int, int))Vt(*(void**)(self + 0x24))[0xf0 / 4])
                   (*(void**)(self + 0x24), r, 1);
  void* old = *(void**)(self + 0x40);
  if (old && old != card) ((void(__thiscall*)(void*, int, int))Vt(old)[0x7c / 4])(old, 1, 0);
  old = *(void**)(self + 0x40);
  if (card != old) {
    if (card) ((void(__thiscall*)(void*))Vt(card)[0])(card);
    *(void**)(self + 0x40) = card;
    if (old) ((void(__thiscall*)(void*))Vt(old)[4 / 4])(old);
  }
  if (!*(void**)(self + 0x30) || !*(void**)(self + 0x38) || !*(void**)(self + 0x3c) ||
      !*(void**)(self + 0x44) || !card)
    return;
  // remainder (layout/animation/text sizing) approximated; see partial.txt
  (void)a; (void)b;
}

// @ 0x00e13b30
void cUIMissionCard::Expand(int a) {
  InitForCreature(a, 0);
  ((void(__thiscall*)(void*))Vt(this)[0x30 / 4])(this);
}
