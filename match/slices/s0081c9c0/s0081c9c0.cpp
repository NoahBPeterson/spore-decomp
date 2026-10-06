// Slice s0081c9c0 -- Spore UI: cSPUIPopupMenuWin scroll buttons / Variant / PropertyEditor.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

extern int g_164dd8c;
extern int g_13ec468;

#define VTSLOT(p, off) ((*(void***)(p))[(off) / 4])

// ===========================================================================
// 0081cd50  cSPUIPopupMenuScrollButton::ScrollButtonSelected  (MATCH)
// ===========================================================================
struct LimitStopwatch2 { void SetTimeLimit(int, int); };
struct SB {
  char pad00[0x888];
  LimitStopwatch2 timer;   // +0x888
  char pad01[0x8a8 - 0x888 - sizeof(LimitStopwatch2)];
  unsigned char mbS;       // +0x8a8
  unsigned char mbF;       // +0x8a9
  void OnScrollButtonClicked(unsigned char, int);
  void ScrollButtonSelected(int arg);
};
void SB::ScrollButtonSelected(int arg) {
  void* self = (char*)this + 4;
  unsigned char r = ((unsigned char (__thiscall*)(void*))VTSLOT(self, 0x28))(self);
  if (!(r & 2)) return;
  void* p = ((void* (__thiscall*)(void*))VTSLOT(self, 0x10))(self);
  if (p == 0) return;
  void* q = ((void* (__thiscall*)(void*, int))VTSLOT(p, 0xc))(p, 0x4c058d5);
  if (q == 0) return;
  ((SB*)q)->OnScrollButtonClicked(mbS, arg);
  timer.SetTimeLimit(g_164dd8c, 1);
}

// ===========================================================================
// 0081ce60  cSPUIPopupMenuScrollButton::OnButtonClicked  (MATCH)
// ===========================================================================
struct ScrollBtn2 {
  char pad[0x8a9 - 0];
  void ScrollButtonSelected(int);
  void OnButtonClicked(int);
  void OnButtonClicked2(int arg);
};
void ScrollBtn2::OnButtonClicked2(int arg) {
  ScrollButtonSelected(1);
  OnButtonClicked(arg);
}

// ===========================================================================
// 0081dce0  SP::cSPUIPropertyEditor::Shutdown  (MATCH)
// ===========================================================================
struct Layout { void Shutdown(int); };
extern void* MessageServer();
extern int g_15bbbf3;
extern int g_16af8d8;
struct cSPUIPropertyEditor {
  char pad00[0xc];
  void* mPropUI;               // +0xc
  void Shutdown();
};
void cSPUIPropertyEditor::Shutdown() {
  void* p = mPropUI;
  if (p != 0) {
    ((Layout*)((char*)p + 0x44))->Shutdown(1);
    p = mPropUI;
    if (p != 0) {
      mPropUI = 0;
      ((void (__thiscall*)(void*))VTSLOT(p, 4))(p);
    }
  }
  void* s = MessageServer();
  if (s != 0) {
    ((void (__thiscall*)(void*, void*, void*, int))VTSLOT(s, 0x2c))(s, this, &g_15bbbf3, 0xffffd8f1);
    ((void (__thiscall*)(void*, void*, void*, int))VTSLOT(s, 0x2c))(s, this, &g_16af8d8, 0xffffd8f1);
  }
}

// ===========================================================================
// 0081d7a0 / 0081da30  EA::Variant setters  (complete, not exact)
// ===========================================================================
struct Variant {
  int f0; int f4; int f8;
  char pad00[4];
  unsigned short flags;   // +0x10
  unsigned short typeId;  // +0x12
  void Destruct(int);
  void Call5(int, int, int, int, int);
  Variant* Reset(int v);
  Variant* Set20(int v);
};
Variant* Variant::Reset(int v) {
  if (flags & 4) Destruct(1);
  unsigned short f = flags & 2;
  if (f && typeId != 1) { Call5(1, 0x20, v, 1, 1); return this; }
  flags = f | 0x20; typeId = 1;
  f0 = v; f4 = 1; f8 = 1;
  return this;
}
Variant* Variant::Set20(int v) {
  if (flags & 4) Destruct(1);
  unsigned short f = flags & 2;
  if (f && typeId != 0x20) { Call5(0x20, 0x20, v, 0xc, 1); return this; }
  flags = f | 0x20; typeId = 0x20;
  f0 = v; f4 = 0xc; f8 = 1;
  return this;
}

// ===========================================================================
// 0081cce0  list reset  (complete, 27-byte diff)
// ===========================================================================
struct MB {
  char pad00[0x3c];
  int* head;      // +0x3c
  char pad01[0x8a8 - 0x40];
  int f8a8;       // +0x8a8
  int f8ac;       // +0x8ac
  void Do030();
  void Reset();
};
void MB::Reset() {
  int* h = (int*)((char*)this + 0x3c);
  if (*(int**)((char*)this + 0x40) != h) {
    do {
      int v = *h;
      if (v == 0 || v == 8) v = 0; else v = v - 4;
      ((void (__thiscall*)(void*, int))VTSLOT((char*)this + 4, 0xdc))((char*)this + 4, v);
    } while (*(int**)((char*)this + 0x40) != h);
  }
  ((void (__thiscall*)(void*, void*))VTSLOT((char*)this + 4, 0x80))((char*)this + 4, (void*)&g_13ec468);
  Do030();
  f8a8 = 0;
  f8ac = 0;
}

// ===========================================================================
// 0081ddd0 / 0081de30  (complete, 9-byte diff)
// ===========================================================================
struct D3 {
  char pad[0x10];
  short w10;   // +0x10
  short w12;   // +0x12
  void Call5(int, int, int, int, int);
  D3* Init(int arg);
  D3* Init2(int arg);
};
D3* D3::Init(int arg) { w10 = 2; w12 = 0x33; Call5(0x33, 0, arg, 0x10, 1); return this; }
D3* D3::Init2(int arg) { w10 = 2; w12 = 0x34; Call5(0x34, 0, arg, 0x10, 1); return this; }

// ===========================================================================
// Not reconstructed -- see partial.txt
// 0081c9c0, 0081ca60, 0081cbe0, 0081cc60, 0081cdb0, 0081ce80,
// 0081cf50, 0081d020, 0081d0f0, 0081d480, 0081d510, 0081d5e0, 0081df10
// ===========================================================================
