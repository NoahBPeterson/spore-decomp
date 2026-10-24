// Slice s0081b990 -- Spore UI: cSPUIPopupMenuWin / SPUIHelpers (UTFWin).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"
#include <xmmintrin.h>
#include <wchar.h>

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
// @ 0x0081bce0
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
// @ 0x0081bd50
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
extern void EndModal(void*, int, int);   // 0x00809c50 SPUIHelpers::EndModal
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
struct OnMouseUpArg {
  int pad00;   // +0x00
  int pad04;   // +0x04
  int f08;     // +0x08
  int f0c;     // +0x0c
  int f10;     // +0x10
  int pad14;   // +0x14
  int pad18;   // +0x18
};

extern "C" void FUN_0081bef0(void);   // Menu2::OnMenuItemSelected (__thiscall, 2 args)
extern "C" char FUN_00964450(void);   // WB::OnMouseUp (__thiscall, 4 args)

// @ 0x0081c900  cSPUIPopupMenuItemWin::OnMouseUp
struct ItemMouseUp {
  char pad00[0x80];
  int f80;                     // +0x80
  int f84;                     // +0x84
  char pad01[0x888 - 0x88];
  int f888;                    // +0x888
  char OnMouseUp(float a1, float a2, int a3, int a4);
};
char ItemMouseUp::OnMouseUp(float a1, float a2, int a3, int a4) {
  ((void (__thiscall*)(void*, int, int))VTSLOT((char*)this + 0x20c, 0x28))((char*)this + 0x20c, 4, 1);
  OnMouseUpArg args;
  args.f08 = 0x4cab02d;
  args.f0c = f84 != 0 ? f84 : f80;
  args.f10 = f888;
  void* self = (char*)this + 4;
  void* p = ((void* (__thiscall*)(void*))VTSLOT(self, 0x10))(self);
  if (p != 0) {
    void* q = ((void* (__thiscall*)(void*, int))VTSLOT(p, 0xc))(p, 0x4c058d5);
    if (q != 0) ((void (__thiscall*)(void*, int, void*))FUN_0081bef0)(q, 0, this);
  }
  char r = ((char (__thiscall*)(void*, float, float, int, int))FUN_00964450)(this, a1, a2, a3, a4);
  ((void (__thiscall*)(void*, void*))VTSLOT(self, 0x114))(self, &args);
  return r;
}

// ===========================================================================
// cSPUIPopupMenuWin (retail layout) -- shared stub for the five big routines
// ===========================================================================
__forceinline int FloorToInt(float f) {
  __asm {
    movss    xmm0, f
    cvtss2si eax, xmm0
    cvtsi2ss xmm1, eax
    mov      ecx, eax
    sub      ecx, 1
    ucomiss  xmm0, xmm1
    cmovb    eax, ecx
  }
}
struct Rect4 {
  float l, t, r, b;
  Rect4() {}
  Rect4(float a, float b_, float c, float d) : l(a), t(b_), r(c), b(d) {}
};
Rect4* GetWinRect(Rect4* out, void* win);      // 0x00805fe0 cdecl
Rect4* GetMainWindowArea(Rect4* out);          // 0x00805ea0 cdecl
void BeginModal(void*, int, int);              // 0x008099a0 cdecl
void UpdateMouseFocus(int);                    // 0x00804f50 cdecl

struct PMBase0 { virtual void pmb0(); };
struct PMWin {                 // IWindow subobject at +4
  virtual void pmw0();
  uint32_t winPad[0x880 / 4];
};
struct PopupMenu : PMBase0, PMWin {
  int mItemId;                 // +0x888
  void* mUpDrawable;           // +0x88c
  void* mDownDrawable;         // +0x890
  void* mBgWin;                // +0x894
  void* mUpBtn;                // +0x898
  void* mDownBtn;              // +0x89c
  void* mWinProc;              // +0x8a0
  char pad8a4[4];
  int mCount;                  // +0x8a8
  int mSelected;               // +0x8ac
  int mScroll;                 // +0x8b0
  int mSubSel;                 // +0x8b4
  float mItemH;                // +0x8b8
  float mWidth;                // +0x8bc
  bool mUpForce;               // +0x8c0
  bool mDownForce;             // +0x8c1
  bool mUpUnneeded;            // +0x8c2
  bool mDownUnneeded;          // +0x8c3
  bool mFlag8c4;               // +0x8c4
  bool mFlag8c5;               // +0x8c5
  char pad8c6[2];
  int mCentered;               // +0x8c8
  int GetVisibleIndex(bool up);
  int GetItemIndexFromChar(wchar_t ch);
  bool OnKeyDown(int a, int b, int c);
  void Reset();                // 0x0081aad0
  void HideMenuItems(bool, bool);   // 0x0081b8b0
  bool BaseOnKeyDown(int, int, int);   // 0x009642d0 WinButton::OnKeyDown
  void CreateChildren();
  void DisplayMenuItems(bool);
};

// @ 0x0081b990
int PopupMenu::GetVisibleIndex(bool up) {
  int idx = up ? 0 : *(int*)((char*)this + 0x8a8) - 1;
  void* self = this ? (char*)this + 4 : 0;
  Rect4 win;
  Rect4 area;
  GetWinRect(&win, self);
  GetMainWindowArea(&area);
  if (mCentered != 0) {
    void* c = ((void* (__thiscall*)(void*))VTSLOT((char*)this + 4, 0x10))((char*)this + 4);
    for (; c != 0; c = ((void* (__thiscall*)(void*))VTSLOT(c, 0x10))(c)) {
      int id = ((int (__thiscall*)(void*))VTSLOT(c, 0x1c))(c);
      if (id == mCentered) {
        Rect4 tmp;
        Rect4* rp = GetWinRect(&tmp, c);
        area.l = rp->l;
        area.t = rp->t;
        area.r = rp->r;
        area.b = rp->b;
        break;
      }
    }
  }
  if (up) {
    if (area.t > win.t - (float)mScroll * mItemH) {
      void* b = *(void**)((char*)this + 0x898);
      Rect4* r = ((Rect4* (__thiscall*)(void*))VTSLOT((char*)b + 4, 0x38))((char*)b + 4);
      float v = ((win.t - area.t) - (r->b - r->t)) / mItemH;
      int iv = FloorToInt(v);
      idx = mScroll - iv;
    }
    if (mUpForce && !mUpUnneeded && !idx) {
      return mUpUnneeded = true;
    }
  } else {
    float top = mItemH + win.b;
    float yb = area.b;
    if (yb < (float)(mCount - mScroll - 1) * mItemH + top) {
      void* b = *(void**)((char*)this + 0x89c);
      Rect4* r = ((Rect4* (__thiscall*)(void*))VTSLOT((char*)b + 4, 0x38))((char*)b + 4);
      float v = ((yb - top) - (r->b - r->t)) / mItemH;
      int iv = FloorToInt(v);
      idx = mScroll + iv;
    }
    if (mDownForce && !mDownUnneeded && idx == mCount - 1) {
      mDownUnneeded = true;
      idx = idx - 1;
    }
  }
  return idx;
}

// @ 0x0081bbe0
int PopupMenu::GetItemIndexFromChar(wchar_t ch) {
  void* self = (char*)this + 4;
  int last = -1;
  int best = last;
  void* it;
  void* end;
  ((void (__thiscall*)(void*, void*))VTSLOT(self, 0xcc))(self, &it);
  ((void (__thiscall*)(void*, void*))VTSLOT(self, 0xd0))(self, &end);
  while (it != end) {
    void* obj = (void*)(g_1440aec + (int)it);
    if (obj != 0) {
      PopupMenu* q = ((PopupMenu* (__thiscall*)(void*, int))VTSLOT(obj, 0xc))(obj, 0x4c058cf);
      if (q != 0) {
        wchar_t* s = ((wchar_t* (__thiscall*)(void*))VTSLOT((char*)q + 4, 0x3c))((char*)q + 4);
        if (s != 0 && towlower(*s) == ch) {
          last = q->mItemId;
          if (best == -1) best = last;
          if (last > mScroll) break;
        }
      }
    }
    it = *(void**)it;
  }
  if (last != mScroll && (best == -1 || mScroll <= last)) return last;
  return best;
}

// @ 0x0081be20
bool PopupMenu::OnKeyDown(int a, int b, int c) {
  if (a == 0 && b == 0x1b && c == 0) {
    void* self = (char*)this + 4;
    void* w;
    if (this) w = self; else w = 0;
    void* mgr = ((void* (__thiscall*)(void*))VTSLOT(self, 0x14))(self);
    if (((bool (__thiscall*)(void*, void*))VTSLOT(mgr, 0x80))(mgr, w)) {
      Reset();
      HideMenuItems(false, true);
      EndModal(self, 0, 0);
      void* p = ((void* (__thiscall*)(void*))VTSLOT(self, 0x10))(self);
      if (p != 0) {
        void* q = ((void* (__thiscall*)(void*, int))VTSLOT(p, 0xc))(p, 0x4c058d5);
        if (q != 0)
          ((void (__thiscall*)(void*, int, int, int))VTSLOT(q, 0x30))(q, 0, 0x1b, 0);
      }
      UpdateMouseFocus(1);
      return true;
    }
  }
  return BaseOnKeyDown(a, b, c);
}

// ===========================================================================
// 0081c030  CreateChildren (background window, two scroll buttons, key winproc)
// ===========================================================================
struct IRef {
  virtual void AddRef();
  virtual void Release();
};
static inline void AssignRef(void*& slot, void* np) {
  IRef* old = (IRef*)slot;
  if ((IRef*)np != old) {
    if (np) ((IRef*)np)->AddRef();
    slot = np;
    if (old) old->Release();
  }
}
void* GetUIAllocator();                                                   // 0x009512c0 cdecl
void* AllocAligned(unsigned size, unsigned align, const char* name, void* a);  // 0x009512d0 cdecl
struct NewWindow : PMBase0, PMWin { NewWindow* Ctor(); };                 // 0x00962a10 Window::Window
struct ScrollBtnNew { ScrollBtnNew* Ctor(); char pad[0x8a8]; bool mIsUp; };  // 0x0081ae90
struct KeysWP0 { virtual void kw0(); };
struct KeysRC { virtual void kr0(); int ref; KeysRC() : ref(0) {} };
struct KeysWinProc : KeysWP0, KeysRC {                                   // "UI/cHandleKeysWinProc"
  void* owner;
  KeysWinProc(void* o) : owner(o) { ((void (__thiscall*)(void*))VTSLOT(o, 0))(o); }
  static void* operator new(size_t sz, unsigned al, const char* nm, void* a) { return AllocAligned(sz, al, nm, a); }
  virtual void kw0();
  virtual void kr0();
};
inline void* operator new(size_t, void* p) throw() { return p; }
struct ScrollPt { float x, y; };

// @ 0x0081c030
void PopupMenu::CreateChildren() {
  void* mem = AllocAligned(0x20c, 4, "UI/Window", GetUIAllocator());
  PMWin* win;
  if (mem) {
    NewWindow* r = ((NewWindow*)mem)->Ctor();
    win = r ? (PMWin*)r : 0;
  } else {
    win = 0;
  }
  AssignRef((void*&)mBgWin, win);
  ((void (__thiscall*)(void*, int, int))VTSLOT(mBgWin, 0x7c))(mBgWin, 1, 0);
  ((void (__thiscall*)(void*, int, int))VTSLOT(mBgWin, 0x7c))(mBgWin, 0x10, 1);
  ((void (__thiscall*)(void*, int))VTSLOT(mBgWin, 0xb0))(mBgWin, mItemId);
  ((void (__thiscall*)(void*, void*))VTSLOT((char*)this + 4, 0xd8))((char*)this + 4, mBgWin);

  mem = AllocAligned(0x8b0, 8, "UI/cSPUIPopupMenuScrollButton", GetUIAllocator());
  ScrollBtnNew* sb = mem ? ((ScrollBtnNew*)mem)->Ctor() : 0;
  AssignRef(mUpBtn, sb);
  ((ScrollBtnNew*)mUpBtn)->mIsUp = true;
  if (mUpDrawable) {
    ((void (__thiscall*)(void*, void*))VTSLOT((char*)mUpBtn + 4, 0xb0))((char*)mUpBtn + 4, mUpDrawable);
    ScrollPt pt;
    pt.x = 0.0f;
    pt.y = 0.0f;
    ((void (__thiscall*)(void*, ScrollPt*, int, int))VTSLOT(mUpDrawable, 0x18))(mUpDrawable, &pt, 0, 0);
    ((void (__thiscall*)(void*, float, float))VTSLOT((char*)mUpBtn + 4, 0x68))((char*)mUpBtn + 4, pt.x, pt.y);
  }
  void* p = ((void* (__thiscall*)(void*))VTSLOT((char*)mUpBtn + 0x20c, 0x10))((char*)mUpBtn + 0x20c);
  ((void (__thiscall*)(void*, int, int))VTSLOT(p, 0x7c))(p, 1, 0);
  ((void (__thiscall*)(void*, void*))VTSLOT((char*)this + 4, 0xd8))((char*)this + 4, p);

  mem = AllocAligned(0x8b0, 8, "UI/cSPUIPopupMenuScrollButton", GetUIAllocator());
  sb = mem ? ((ScrollBtnNew*)mem)->Ctor() : 0;
  AssignRef(mDownBtn, sb);
  ((ScrollBtnNew*)mDownBtn)->mIsUp = false;
  if (mDownDrawable) {
    ((void (__thiscall*)(void*, void*))VTSLOT((char*)mDownBtn + 4, 0xb0))((char*)mDownBtn + 4, mDownDrawable);
    ScrollPt pt;
    pt.x = 0.0f;
    pt.y = 0.0f;
    ((void (__thiscall*)(void*, ScrollPt*, int, int))VTSLOT(mDownDrawable, 0x18))(mDownDrawable, &pt, 0, 0);
    ((void (__thiscall*)(void*, float, float))VTSLOT((char*)mDownBtn + 4, 0x68))((char*)mDownBtn + 4, pt.x, pt.y);
  }
  p = ((void* (__thiscall*)(void*))VTSLOT((char*)mDownBtn + 0x20c, 0x10))((char*)mDownBtn + 0x20c);
  ((void (__thiscall*)(void*, int, int))VTSLOT(p, 0x7c))(p, 1, 0);
  ((void (__thiscall*)(void*, void*))VTSLOT((char*)this + 4, 0xd8))((char*)this + 4, p);

  if (mWinProc == 0) {
    KeysWinProc* kp = new (4, "UI/cHandleKeysWinProc", GetUIAllocator()) KeysWinProc(this);
    AssignRef(mWinProc, kp);
    ((void (__thiscall*)(void*, void*))VTSLOT((char*)this + 4, 0x104))((char*)this + 4, mWinProc);
  }
}

// ===========================================================================
// 0081c370  DisplayMenuItems(bool recurse)
// ===========================================================================
struct ItemWin { char pad[0x888]; int mItemId; };
struct Point2 { float x, y; Point2() {} Point2(float a, float b) : x(a), y(b) {} Point2(const Point2& o) : x(o.x), y(o.y) {} };
struct WinSlots {                // IWindow vtable stub: slot 48 (0xc0) = Point2 transform
  virtual void s0();
  virtual void s1();
  virtual void s2();
  virtual void s3();
  virtual void s4();
  virtual void s5();
  virtual void s6();
  virtual void s7();
  virtual void s8();
  virtual void s9();
  virtual void s10();
  virtual void s11();
  virtual void s12();
  virtual void s13();
  virtual void s14();
  virtual void s15();
  virtual void s16();
  virtual void s17();
  virtual void s18();
  virtual void s19();
  virtual void s20();
  virtual void s21();
  virtual void s22();
  virtual void s23();
  virtual void s24();
  virtual void s25();
  virtual void s26();
  virtual void s27();
  virtual void s28();
  virtual void s29();
  virtual void s30();
  virtual void s31();
  virtual void s32();
  virtual void s33();
  virtual void s34();
  virtual void s35();
  virtual void s36();
  virtual void s37();
  virtual void s38();
  virtual void s39();
  virtual void s40();
  virtual void s41();
  virtual void s42();
  virtual void s43();
  virtual void s44();
  virtual void s45();
  virtual void s46();
  virtual void s47();
  virtual Point2 s48(Point2);
};
static __forceinline void SetItemRect(void* obj, const Rect4& r) {
  ((void (__thiscall*)(void*, const Rect4*))VTSLOT(obj, 0x6c))(obj, &r);
}
static __forceinline bool IsPopupMenuWin(void* p) {
  bool r = false;
  if (p) {
    void* q = ((void* (__thiscall*)(void*, int))VTSLOT(p, 0xc))(p, 0x4c058d5);
    r = (q != 0);
  }
  return r;
}
struct ShowMsg { uint32_t w0, w1; int id; int val; uint32_t w4, w5, w6; };
extern float g_164dd7c;      // 0x0164dd7c popup border margin

// @ 0x0081c370
void PopupMenu::DisplayMenuItems(bool recurse) {
  void* self = (char*)this + 4;
  float h;
  void* par = ((void* (__thiscall*)(void*))VTSLOT(self, 0x10))(self);
  if (IsPopupMenuWin(par)) {
    void* par2 = ((void* (__thiscall*)(void*))VTSLOT(self, 0x10))(self);
    Rect4* pr = ((Rect4* (__thiscall*)(void*))VTSLOT(par2, 0x38))(par2);
    h = pr->r - pr->l;
  } else {
    h = 0.0f;
  }
  if (!mFlag8c5 && !mFlag8c4) {
    Rect4* wr = ((Rect4* (__thiscall*)(void*))VTSLOT(self, 0x38))(self);
    mWidth = wr->r - wr->l;
  }
  float left = ((WinSlots*)self)->s48(Point2(0.0f, 0.0f)).x;
  Rect4 rB;
  Rect4* area = GetMainWindowArea(&rB);
  float aw = area->r - area->l;
  if (left + mWidth > aw) h = h - ((left + mWidth) - aw);

  int lo = GetVisibleIndex(true);
  int hi = GetVisibleIndex(false);
  void* it;
  void* end;
  ((void (__thiscall*)(void*, void*))VTSLOT(self, 0xcc))(self, &it);
  ((void (__thiscall*)(void*, void*))VTSLOT(self, 0xd0))(self, &end);
  while (it != end) {
    void* obj = (void*)(g_1440aec + (int)it);
    ((void (__thiscall*)(void*, int, int))VTSLOT(obj, 0x7c))(obj, 1, 1);
    ItemWin* a = ((ItemWin* (__thiscall*)(void*, int))VTSLOT(obj, 0xc))(obj, 0x4c058cf);
    PopupMenu* b = ((PopupMenu* (__thiscall*)(void*, int))VTSLOT(obj, 0xc))(obj, 0x4c058d5);
    if (a != 0 || b != 0) {
      ((void* (__thiscall*)(void*))VTSLOT(obj, 0x38))(obj);
      int idx;
      if (a != 0)
        idx = a->mItemId;
      else
        idx = b->mSubSel;
      if (idx >= lo && idx <= hi) {
        float ih = mItemH;
        float top = (float)(idx - mScroll) * ih;
        rB.l = h;
        rB.t = top;
        rB.r = h + mWidth;
        rB.b = ih + top;
        ((void (__thiscall*)(void*, Rect4*))VTSLOT(obj, 0x6c))(obj, &rB);
      } else {
        ((void (__thiscall*)(void*, int, int))VTSLOT(obj, 0x7c))(obj, 1, 0);
      }
      if (b != 0 && recurse && idx == mSelected) {
        int sel = b->mSelected;
        b->mUpForce = false;
        b->mDownForce = false;
        b->mUpUnneeded = false;
        b->mDownUnneeded = false;
        b->mScroll = sel;
        b->DisplayMenuItems(true);
      }
    }
    it = *(void**)it;
  }

  if (mUpBtn != 0) {
    void* p = ((void* (__thiscall*)(void*))VTSLOT((char*)mUpBtn + 0x20c, 0x10))((char*)mUpBtn + 0x20c);
    if (!mUpForce && lo == 0) {
      ((void (__thiscall*)(void*, int, int))VTSLOT(p, 0x7c))(p, 1, 0);
    } else {
      float t = (float)(mScroll - lo + 1) * mItemH * -1.0f;
      Rect4* pr = ((Rect4* (__thiscall*)(void*))VTSLOT(p, 0x38))(p);
      float w2 = pr->r - pr->l;
      ((void (__thiscall*)(void*, float, float))VTSLOT(p, 0x64))(p, (mWidth - w2) * 0.5f + h, t);
      ((void (__thiscall*)(void*, int, bool))VTSLOT(p, 0x7c))(p, 2, !(mUpUnneeded && lo == 0));
    }
  }
  if (mDownBtn != 0) {
    void* p = ((void* (__thiscall*)(void*))VTSLOT((char*)mDownBtn + 0x20c, 0x10))((char*)mDownBtn + 0x20c);
    if (!mDownForce && hi == mCount - 1) {
      ((void (__thiscall*)(void*, int, int))VTSLOT(p, 0x7c))(p, 1, 0);
    } else {
      Rect4* pr = ((Rect4* (__thiscall*)(void*))VTSLOT(p, 0x38))(p);
      float w2 = pr->r - pr->l;
      ((void (__thiscall*)(void*, float, float))VTSLOT(p, 0x64))(p, (mWidth - w2) * 0.5f + h, (float)(hi - mScroll + 1) * mItemH);
      ((void (__thiscall*)(void*, int, bool))VTSLOT(p, 0x7c))(p, 2, !(mDownUnneeded && hi == mCount - 1));
    }
  }
  if (mBgWin != 0) {
    float y1 = (float)(lo - mScroll) * mItemH - g_164dd7c;
    float y2 = (float)(hi - lo + 1) * mItemH + g_164dd7c * 2.0f;
    if (((unsigned char (__thiscall*)(void*))VTSLOT((char*)mUpBtn + 4, 0x28))((char*)mUpBtn + 4) & 1) {
      y1 = y1 - mItemH;
      y2 = mItemH + y2;
    }
    if (((unsigned char (__thiscall*)(void*))VTSLOT((char*)mDownBtn + 4, 0x28))((char*)mDownBtn + 4) & 1) {
      y2 = mItemH + y2;
    }
    ((void (__thiscall*)(void*, float, float))VTSLOT(mBgWin, 0x68))(mBgWin, mWidth, y2);
    ((void (__thiscall*)(void*, float, float))VTSLOT(mBgWin, 0x64))(mBgWin, h, y1);
    ((void (__thiscall*)(void*, void*))VTSLOT(self, 0xec))(self, mBgWin);
  }
  void* mgr = ((void* (__thiscall*)(void*))VTSLOT(self, 0x14))(self);
  if (!((bool (__thiscall*)(void*, void*))VTSLOT(mgr, 0x80))(mgr, self)) {
    void* q = ((void* (__thiscall*)(void*))VTSLOT(self, 0x10))(self);
    if (!IsPopupMenuWin(q))
      BeginModal(self, 0, 0);
  }
  ShowMsg msg;
  msg.id = 0x685a2b9;
  int cv = *(int*)((char*)this + 0x84);
  msg.val = cv ? cv : *(int*)((char*)this + 0x80);
  ((void (__thiscall*)(void*, ShowMsg*))VTSLOT(self, 0x114))(self, &msg);
  UpdateMouseFocus(1);
}
