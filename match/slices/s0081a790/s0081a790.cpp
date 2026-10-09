// Slice s0081a790 -- Spore UI: cSPUIPieMenu / cSPUIPopupMenuWin family (UTFWin).
// Reconstructed from annotated disassembly + Ghidra typed decompile.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

extern "C" double ceil(double);

extern int g_1440aec;   // offset-pool base used by UI object iterators
extern int g_164dd8c;   // default scroll-button time limit

#define VTSLOT(p, off) ((*(void***)(p))[(off) / 4])

extern void Mark1();
extern void Mark2();
extern void Mark3();

struct LimitStopwatch { void SetTimeLimit(int, int); };

// ===========================================================================
// cSPUIPieMenuItem / cSPUIPieMenu
// ===========================================================================
struct cSPUIPieMenuItem {
  char pad00[0x38];
  float mf0;    // +0x38
  float mf1;    // +0x3c
  float mf2;    // +0x40
  float mf3;    // +0x44
  char pad01[0x4];
  void SetId(int);
  void SetText(int, int);
  void SetTextColor(int);
  void SetIcon(void*);
};

struct cSPUIPieMenu {
  char pad00[0xc];
  cSPUIPieMenuItem* mpBegin;   // +0x0c
  cSPUIPieMenuItem* mpEnd;     // +0x10
  cSPUIPieMenuItem* mpCap;     // +0x14
  char pad01[0x8];             // +0x18..0x1f
  int mCount;                  // +0x20
  int mItem;                   // +0x24
  void** mpListBegin;          // +0x28
  void** mpListEnd;            // +0x2c
  char pad02[0x2c];            // +0x30..0x5b
  char mChanged;               // +0x5c

  cSPUIPieMenuItem* get_unused_item();
  int AddItem(int a, int b, int c, int d);
};

extern void FUN_00817fa0(void*, int);

// @ 0x0081A790  cSPUIPieMenu::get_unused_item  (incomplete -- see partial.txt)
cSPUIPieMenuItem* cSPUIPieMenu::get_unused_item() {
  return 0;
}

// @ 0x0081A940  cSPUIPieMenu::AddItem
int cSPUIPieMenu::AddItem(int a, int b, int c, int d) {
  cSPUIPieMenuItem* item = get_unused_item();
  if (item == 0) return 0;
  item->mf0 = 0.f; item->mf1 = 0.f; item->mf2 = 0.f; item->mf3 = 0.f;
  item->SetId(a);
  item->SetText(b, 1);
  item->SetTextColor(c);
  FUN_00817fa0(item, d);
  uint32_t n = (uint32_t)(mpListEnd - mpListBegin);
  if (n != 0) {
    uint32_t i = 0;
    for (;;) {
      void* p = mpListBegin[i];
      int id = ((int (__thiscall*)(void*))VTSLOT(p, 0x1c))(p);
      if (id == a) { item->SetIcon(p); break; }
      i++;
      if (i >= (uint32_t)(mpListEnd - mpListBegin)) break;
    }
  }
  mCount++;
  mChanged = 1;
  return 1;
}

// ===========================================================================
// cSPUIPopupMenuItemWin
// ===========================================================================
struct cSPUIPopupMenuItemWin {
  char pad00[0x888];
  int mChildIndex;               // +0x888
  void SomeFunc();               // 0081ae40
  __declspec(noinline) void OnAttach();   // 0081ad50
};

// @ 0x0081AE40
void cSPUIPopupMenuItemWin::SomeFunc() {
  void* self = (char*)this + 4;
  void* vt = *(void**)self;
  ((void (__thiscall*)(void*, int, int))((void**)vt)[0x7c / 4])(self, 1, 0);
  OnAttach();
}

// @ 0x0081AD50  cSPUIPopupMenuItemWin::OnAttach (complete behaviour best-effort)
extern float FUN_0083ce70(float);
void cSPUIPopupMenuItemWin::OnAttach() {
  void* self = (char*)this + 4;
  void* p = ((void* (__thiscall*)(void*))VTSLOT(self, 0x10))(self);
  if (mChildIndex != -1 || p == 0) return;
  void* q = ((void* (__thiscall*)(void*, int))VTSLOT(p, 0xc))(p, 0x4c058d5);
  if (q == 0) return;
  mChildIndex = *(int*)((char*)q + 0x8a8);
  (*(int*)((char*)q + 0x8a8))++;
  void* rect = ((void* (__thiscall*)(void*))VTSLOT(self, 0x38))(self);
  if (*(char*)((char*)q + 0x8c5) != 0) {
    ((void (__thiscall*)(void*))VTSLOT((char*)this + 0x20c, 0x14))((char*)this + 0x20c);
    float w = *(float*)((char*)rect + 8) - *(float*)rect;
    if (*(float*)((char*)q + 0x8bc) < w) {
      *(float*)((char*)q + 0x8bc) = FUN_0083ce70(w);
      *(char*)((char*)q + 0x8c4) = 1;
    }
  }
  float h = *(float*)((char*)rect + 0xc) - *(float*)((char*)rect + 4);
  if (*(float*)((char*)q + 0x8b8) < h) {
    *(float*)((char*)q + 0x8b8) = (float)ceil((double)h);
  }
}

// ===========================================================================
// cSPUIPopupMenuScrollButton
// ===========================================================================
struct cSPUIPopupMenuScrollButton {
  char pad00[0x888];
  LimitStopwatch timer;          // +0x888
  char pad01[0x8a8 - 0x888 - sizeof(LimitStopwatch)];
  bool mbF0;                     // +0x8a8
  bool mbF1;                     // +0x8a9

  void OnFocusLost(int a, int b);
  void OnFocusLostBase(int a, int b);
  void OnFocusAcquired(int a, int b);
  void OnFocusAcquiredBase(int a, int b);
  void OnMouseWheel(float a1, float a2, int a3, int a4);
  void OnMouseWheelBase(float a1, float a2, int a3, int a4);
};

// @ 0x0081AA80
void cSPUIPopupMenuScrollButton::OnFocusLost(int a, int b) {
  if (a == 1) mbF1 = false;
  OnFocusLostBase(a, b);
}

// @ 0x0081AF30
void cSPUIPopupMenuScrollButton::OnMouseWheel(float a1, float a2, int a3, int a4) {
  void* self = (char*)this + 4;
  void* p = ((void* (__thiscall*)(void*))VTSLOT(self, 0x10))(self);
  if (p != 0) {
    void* q = ((void* (__thiscall*)(void*, int))VTSLOT(p, 0xc))(p, 0x4c058d5);
    if (q != 0) {
      ((void (__thiscall*)(void*, float, float, int, int))VTSLOT(q, 0x48))(q, a1, a2, a3, a4);
      return;
    }
  }
  OnMouseWheelBase(a1, a2, a3, a4);
}

// @ 0x0081AFB0
void cSPUIPopupMenuScrollButton::OnFocusAcquired(int a, int b) {
  if (a == 1) {
    mbF1 = true;
    timer.SetTimeLimit(g_164dd8c, a);
  }
  OnFocusAcquiredBase(a, b);
}

// ===========================================================================
// cSPUIPopupMenuWin
// ===========================================================================
struct cSPUIPopupMenuWin {
  char pad00[0x8a8];
  int mNumItemChildren;          // +0x8a8
  int mSelectedItemIndex;        // +0x8ac
  int mCenteredItemIndex;        // +0x8b0
  char pad01[0x8c0 - 0x8b4];     // +0x8b4..0x8bf
  bool mbF0;                     // +0x8c0
  bool mbF1;                     // +0x8c1
  bool mbF2;                     // +0x8c2
  bool mbF3;                     // +0x8c3

  void Reset();
  void* FindChild(int idx);
  void RemoveChild(int idx);
  void HideMenuItems(bool a, bool b);
  void AddMenuItem2(cSPUIPopupMenuItemWin* item, bool attach);
};

// @ 0x0081AAD0
void cSPUIPopupMenuWin::Reset() {
  mbF0 = 0; mbF1 = 0; mbF2 = 0; mbF3 = 0;
  mCenteredItemIndex = mSelectedItemIndex;
}

// @ 0x0081B750
void* cSPUIPopupMenuWin::FindChild(int idx) {
  void* self = (char*)this + 4;
  void* it;
  void* end;
  ((void (__thiscall*)(void*, void*))VTSLOT(self, 0xcc))(self, &it);
  ((void (__thiscall*)(void*, void*))VTSLOT(self, 0xd0))(self, &end);
  while (it != end) {
    void* obj = (void*)(g_1440aec + (int)it);
    if (obj != 0) {
      void* q = ((void* (__thiscall*)(void*, int))VTSLOT(obj, 0xc))(obj, 0x4c058cf);
      if (q != 0 && *(int*)((char*)q + 0x888) == idx) return q;
    }
    it = *(void**)it;
  }
  return 0;
}

// @ 0x0081B7D0
void cSPUIPopupMenuWin::RemoveChild(int idx) {
  void* self = (char*)this + 4;
  void* it;
  void* end;
  ((void (__thiscall*)(void*, void*))VTSLOT(self, 0xcc))(self, &it);
  ((void (__thiscall*)(void*, void*))VTSLOT(self, 0xd0))(self, &end);
  void* found = 0;
  while (it != end) {
    void* obj = (void*)(g_1440aec + (int)it);
    if (obj != 0) {
      void* q = ((void* (__thiscall*)(void*, int))VTSLOT(obj, 0xc))(obj, 0x4c058cf);
      if (q != 0) {
        if (*(int*)((char*)q + 0x888) == idx) {
          *(int*)((char*)q + 0x888) = -1;
          found = obj;
        }
        if (*(int*)((char*)q + 0x888) > idx)
          *(int*)((char*)q + 0x888) = *(int*)((char*)q + 0x888) - 1;
      }
    }
    it = *(void**)it;
  }
  if (found != 0) {
    ((void (__thiscall*)(void*, void*))VTSLOT(self, 0xdc))(self, found);
    if (mSelectedItemIndex == idx) {
      mSelectedItemIndex = 0;
      mCenteredItemIndex = 0;
    }
    mNumItemChildren--;
  }
}

// @ 0x0081B8B0
void cSPUIPopupMenuWin::HideMenuItems(bool a, bool b) {
  void* self = (char*)this + 4;
  void* it;
  void* end;
  ((void (__thiscall*)(void*, void*))VTSLOT(self, 0xcc))(self, &it);
  ((void (__thiscall*)(void*, void*))VTSLOT(self, 0xd0))(self, &end);
  if (it == end) return;
  while (it != end) {
    void* obj = (void*)(g_1440aec + (int)it);
    bool doHide = true;
    if (obj != 0) {
      void* s = ((void* (__thiscall*)(void*, int))VTSLOT(obj, 0xc))(obj, 0x4c6ec97);
      if (s != 0 && !b) doHide = false;
    }
    if (doHide) {
      ((void (__thiscall*)(void*, int, int))VTSLOT(obj, 0x7c))(obj, 1, 0);
    }
    if (a) {
      void* q = ((void* (__thiscall*)(void*, int))VTSLOT(obj, 0xc))(obj, 0x4c058cf);
      if (q != 0) {
        void* b2 = (char*)q + 0x20c;
        ((void (__thiscall*)(void*, int, int))VTSLOT(b2, 0x28))(b2, 4, 0);
      }
    }
    void* m = ((void* (__thiscall*)(void*, int))VTSLOT(obj, 0xc))(obj, 0x4c058d5);
    if (m != 0) {
      ((cSPUIPopupMenuWin*)m)->HideMenuItems(false, true);
    }
    it = *(void**)it;
  }
}

// @ 0x0081B650  cSPUIPopupMenuWin::AddMenuItem (two-byte near miss)
void cSPUIPopupMenuWin::AddMenuItem2(cSPUIPopupMenuItemWin* item, bool attach) {
  void* iself = (char*)item + 4;
  void* vt = *(void**)iself;
  void* r = ((void* (__thiscall*)(void*))((void**)vt)[0x10 / 4])(iself);
  if (r != 0) {
    void* rvt = *(void**)r;
    ((void (__thiscall*)(void*, void*))((void**)rvt)[0xdc / 4])(r, iself);
  }
  void* mself = (char*)this + 4;
  void* mvt = *(void**)mself;
  ((void (__thiscall*)(void*, void*))((void**)mvt)[0xd8 / 4])(mself, iself);
  if (attach) item->OnAttach();
}

// ===========================================================================
// Remaining constructors / dtor / detach / layout helper -- complete, not exact
// ===========================================================================

// @ 0x0081AA00  ctor cSPUIPopupMenuItemWin (not byte-exact)
struct ItemWinCtor {
  char pad[0x888];
  int mChildIndex;
  void Ctor();
};
void ItemWinCtor::Ctor() {
  *(void**)this = (void*)&Mark1;
  *(void**)((char*)this + 4) = (void*)&Mark2;
  *(void**)((char*)this + 0x20c) = (void*)&Mark3;
  mChildIndex = -1;
}

// @ 0x0081AE90  ctor cSPUIPopupMenuScrollButton (not byte-exact)
struct ScrollBtnCtor {
  char pad[0x888];
  LimitStopwatch timer;
  char pad2[0x8a8 - 0x888 - sizeof(LimitStopwatch)];
  bool b0;
  bool b1;
  void Ctor();
  void StopwatchCtor(int, int);
};
void ScrollBtnCtor::Ctor() {
  *(void**)this = (void*)&Mark1;
  *(void**)((char*)this + 4) = (void*)&Mark2;
  *(void**)((char*)this + 0x20c) = (void*)&Mark3;
  StopwatchCtor(4, 0);
  timer.SetTimeLimit(g_164dd8c, 0);
  b0 = 0;
  b1 = 0;
}

// @ 0x0081B000  ctor cSPUIPopupMenuWin (not byte-exact)
struct PopupWinCtor {
  char pad[0x888];
  int z[12];     // 0x888..0x8b7
  float f0, f1;  // 0x8b8,0x8bc
  char b0, b1, b2, b3, b4, b5;
  char pad2[2];
  int d0;        // 0x8c8
  void Ctor();
};
void PopupWinCtor::Ctor() {
  *(void**)this = (void*)&Mark1;
  *(void**)((char*)this + 4) = (void*)&Mark2;
  *(void**)((char*)this + 0x20c) = (void*)&Mark3;
  for (int i = 0; i < 12; i++) z[i] = 0;
  f0 = 0.f; f1 = 0.f;
  b0 = b1 = b2 = b3 = b4 = b5 = 0;
  d0 = 0;
}

// @ 0x0081B100  dtor cSPUIPopupMenuWin (not byte-exact)
static void ReleaseRef(void* p) {
  ((void (__thiscall*)(void*))((void**)*(void**)p)[1])(p);
}
struct PopupWinDtor {
  char pad[0x888];
  void* p[15];    // 0x888..0x8c4 region
  void Dtor();
  void BaseDtor();
};
void PopupWinDtor::Dtor() {
  void** m = (void**)((char*)this + 0x888);
  for (int i = 0; i < 7; i++) { if (m[i]) { void* q = m[i]; m[i] = 0; ReleaseRef(q); } }
  if (m[6]) ReleaseRef(m[6]);
  if (m[5]) ReleaseRef(m[5]);
  BaseDtor();
}

// @ 0x0081B510  OnDetach (not byte-exact)
struct PopupWinDetach {
  char pad00[0x894];
  void* m0;     // 0x894
  void* m1;     // 0x898
  void* m2;     // 0x89c
  void* m3;     // 0x8a0
  void* m4;     // 0x8a4
  void OnDetach();
  void EndModal(void*, int, int);
};
void PopupWinDetach::OnDetach() {
  void* self = (char*)this + 4;
  if (((void* (__thiscall*)(void*))VTSLOT(self, 0x14))(self) != 0) {
    void* p = ((void* (__thiscall*)(void*))VTSLOT(self, 0x14))(self);
    if (((char (__thiscall*)(void*, void*))VTSLOT(p, 0x80))(p, self))
      EndModal(self, 0, 0);
  }
  if (m0) { ((void (__thiscall*)(void*, void*))VTSLOT(self, 0xdc))(self, m0); void* q = m0; m0 = 0; ReleaseRef(q); }
  if (m1) {
    void* q = ((void* (__thiscall*)(void*))VTSLOT((char*)m1 + 0x20c, 0x10))((char*)m1 + 0x20c);
    ((void (__thiscall*)(void*, void*))VTSLOT(self, 0xdc))(self, q);
    q = m1; m1 = 0; ReleaseRef(q);
  }
  if (m2) {
    void* q = ((void* (__thiscall*)(void*))VTSLOT((char*)m2 + 0x20c, 0x10))((char*)m2 + 0x20c);
    ((void (__thiscall*)(void*, void*))VTSLOT(self, 0xdc))(self, q);
    q = m2; m2 = 0; ReleaseRef(q);
  }
  if (m3) {
    ((void (__thiscall*)(void*, void*))VTSLOT(self, 0x108))(self, m3);
    if (m3) { void* q = m3; m3 = 0; ReleaseRef(q); }
  }
  if (m4) { void* q = m4; m4 = 0; ReleaseRef(q); }
}

// @ 0x0081B6A0  AddMenuItem (not byte-exact)
extern void cSPUILayout_Ctor(void*);
extern char cSPUILayout_Init(void*, int, int, int);
extern void* cSPUILayout_FindWindowByID(void*, int, int);
extern void cSPUILayout_Shutdown(void*, int); // 0x00811ad0
extern void cSPUILayout_Dtor(void*);
struct cSPUIPopupMenuWin2 {
  char pad00[0x8a8];
  void* AddMenuItem3(int id, int styleId, int parent, bool attach);
};
void* cSPUIPopupMenuWin2::AddMenuItem3(int id, int styleId, int parent, bool attach) {
  char local[0x18];
  cSPUILayout_Ctor(local);
  void* result = 0;
  if (cSPUILayout_Init(local, id, 0, 0x5b598fa) != 0) {
    void* w = cSPUILayout_FindWindowByID(local, styleId, 1);
    if (w) ((void (__thiscall*)(void*))VTSLOT(w, 0))(w);
    cSPUILayout_Shutdown(local, 1); // 0x00811ad0
    if (w) {
      void* item = ((void* (__thiscall*)(void*, int))VTSLOT(w, 0xc))(w, 0x4c058cf);
      result = item;
      if (item) {
        if (parent)
          ((void (__thiscall*)(void*, int))VTSLOT((char*)item + 4, 0x80))((char*)item + 4, parent);
        ((cSPUIPopupMenuWin*)this)->AddMenuItem2((cSPUIPopupMenuItemWin*)item, attach);
      }
      ((void (__thiscall*)(void*))VTSLOT(w, 4))(w);
    }
  }
  cSPUILayout_Dtor(local);
  return result;
}

// @ 0x0081B240  cSPUIPopupMenuWin::MeasureItemHeight  (incomplete -- see partial.txt)
// @ 0x0081A790  cSPUIPieMenu::get_unused_item        (incomplete -- see partial.txt)
// --- equivalence checker address annotations
    void cSPUILayout_Shutdown(...); // 0x00811ad0

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct LimitStopwatch {
    void SetTimeLimit(int, int); // 0x0093a480
};
}
