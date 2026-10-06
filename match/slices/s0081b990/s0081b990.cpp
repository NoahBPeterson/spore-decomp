// Slice s0081b990 -- Spore UI: cSPUIPopupMenuWin / SPUIHelpers (UTFWin).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

extern int g_1440aec;
extern unsigned int g_164dc58;

#define VTSLOT(p, off) ((*(void***)(p))[(off) / 4])

// ===========================================================================
// 0081bfb0  SPUIHelpers::cAutoPropertyBaseLink::Update  (MATCH)
// ===========================================================================
struct Menu { void HideMenuItems(bool, bool); };

struct cAutoPropertyBaseLink {
  char pad00[4];
  void* mList;                 // +4
  void Update(void* except);   // 0081bfb0
};
void cAutoPropertyBaseLink::Update(void* except) {
  void* self = (char*)this + 4;
  void* it;
  void* end;
  ((void (__thiscall*)(void*, void*))VTSLOT(self, 0xcc))(self, &it);
  ((void (__thiscall*)(void*, void*))VTSLOT(self, 0xd0))(self, &end);
  while (it != end) {
    void* obj = (void*)(g_1440aec + (int)it);
    if (obj != 0) {
      void* q = ((void* (__thiscall*)(void*, int))VTSLOT(obj, 0xc))(obj, 0x4c058d5);
      if (q != 0 && except != q) {
        ((Menu*)q)->HideMenuItems(false, true);
      }
    }
    it = *(void**)it;
  }
}

// ===========================================================================
// 0081bce0  (complete, 43-byte diff)
// ===========================================================================
struct C1 {
  char pad00[4];
  int mField4;                 // +4
  char pad01[4];
  unsigned int mFieldC;        // +0xc
  bool Method(int* arg);
};
bool C1::Method(int* arg) {
  bool ok = ((bool (__thiscall*)(int*, int, int**))VTSLOT(arg, 0x24))(arg, mField4, &arg);
  if (!ok) return false;
  unsigned short key = *(unsigned short*)((char*)arg + 0x12);
  unsigned int v;
  if (key == 0xa || key == 0x10) {
    if (*(unsigned char*)((char*)arg + 0x10) & 0x30)
      v = **(unsigned int**)arg;
    else
      v = *(unsigned int*)arg;
  } else {
    v = g_164dc58;
  }
  if (mFieldC != v) { mFieldC = v; return true; }
  return false;
}

// ===========================================================================
// 0081bd50  (complete, 76-byte diff)
// ===========================================================================
struct Evt { char pad00[8]; int type; int a; int b; int c; };
struct C2 {
  char pad00[0xc];
  void* mFieldC;              // +0xc
  bool Method2(int unused, Evt* e);
};
bool C2::Method2(int unused, Evt* e) {
  int t = e->type;
  if (t == 1) {
    if (mFieldC != 0)
      return ((bool (__thiscall*)(void*, int, int, int))VTSLOT(mFieldC, 0x30))(mFieldC, e->a, e->b, e->c);
  } else if (t != 5) {
    return false;
  }
  if (mFieldC == 0) return false;
  return ((bool (__thiscall*)(void*, int, int))VTSLOT(mFieldC, 0x38))(mFieldC, e->a, *(unsigned short*)&e->b);
}

// ===========================================================================
// 0081bef0  cSPUIPopupMenuWin::OnMenuItemSelected  (complete, 29-byte diff)
// ===========================================================================
extern void EndModal(void*, int, int);
struct Menu2 {
  void HideMenuItems(bool, bool);
  void OnMenuItemSelected(Menu2* b, Menu2* a);
};
void Menu2::OnMenuItemSelected(Menu2* b, Menu2* a) {
  Menu2* cur = this;
  for (;;) {
    cur->HideMenuItems(true, true);
    if (a != 0) {
      void* q = (char*)a + 0x20c;
      ((void (__thiscall*)(void*, int, int))VTSLOT(q, 0x28))(q, 4, 1);
    }
    if (b != 0)
      *(int*)((char*)cur + 0x8ac) = *(int*)((char*)b + 0x8b4);
    else
      *(int*)((char*)cur + 0x8ac) = *(int*)((char*)a + 0x888);
    *(int*)((char*)cur + 0x8b0) = *(int*)((char*)cur + 0x8ac);
    void* self = (char*)cur + 4;
    EndModal(self, 0, 0);
    void* p = ((void* (__thiscall*)(void*))VTSLOT(self, 0x10))(self);
    if (p == 0) return;
    void* n = ((void* (__thiscall*)(void*, int))VTSLOT(p, 0xc))(p, 0x4c058d5);
    if (n == 0) {
      void* w = (char*)cur + 4;
      void** vt = *(void***)w;
      void** slot = (void**)((char*)vt + 0x80);
      void* r = ((void* (__thiscall*)(void*))VTSLOT((char*)a + 4, 0x3c))((char*)a + 4);
      ((void (__thiscall*)(void*, void*))*slot)(w, r);
      return;
    }
    b = cur;
    cur = (Menu2*)n;
  }
}

// ===========================================================================
// 0081c900  cSPUIPopupMenuItemWin::OnMouseUp  (complete, approx)
// ===========================================================================
struct OnMouseUpArg { char pad00[0x14]; int d14; int d18; int d1c; };
struct ItemMouseUp {
  char pad00[0x80];
  int f80;                     // +0x80
  int f84;                     // +0x84
  char pad01[0x888 - 0x88];
  int f888;                    // +0x888
  char OnMouseUp(float a1, float a2, int a3, int a4);
  char WinButtonOnMouseUp(float, float, int, int);
  void OnMenuItemSelected2(int, void*);
  void Call114(void*);
};
char ItemMouseUp::OnMouseUp(float a1, float a2, int a3, int a4) {
  ((void (__thiscall*)(void*, int, int))VTSLOT((char*)this + 0x20c, 0x28))((char*)this + 0x20c, 4, 1);
  int v = f84 != 0 ? f84 : f80;
  OnMouseUpArg args;
  args.d14 = 0x4cab02d;
  args.d18 = v;
  args.d1c = f888;
  void* self = (char*)this + 4;
  void* p = ((void* (__thiscall*)(void*))VTSLOT(self, 0x10))(self);
  if (p != 0) {
    void* q = ((void* (__thiscall*)(void*, int))VTSLOT(p, 0xc))(p, 0x4c058d5);
    if (q != 0) ((ItemMouseUp*)q)->OnMenuItemSelected2(0, this);
  }
  char r = WinButtonOnMouseUp(a1, a2, a3, a4);
  Call114(&args);
  return r;
}

// ===========================================================================
// 0081b990 GetVisibleIndex / 0081c030 / 0081c370 / 0081be20 / 0081bbe0
//   -- incomplete, see partial.txt (large float/list routines not reconstructed)
// ===========================================================================
