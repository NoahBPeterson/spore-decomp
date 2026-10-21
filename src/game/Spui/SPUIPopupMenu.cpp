// src/game/Spui/SPUIPopupMenu.cpp -- migrated from slice(s) s012f64e0, s0081c9c0, s0081b990, s0081a790 by tools/migrate/rewrite.py
// Object file: Spui/SPUIPopupMenu.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <wchar.h>
#include "EA/Text/LineLayout.h"
#include "EA/Text/Typesetter.h"

// unnamed retail callees and globals (address in the comment)
extern "C" double ceil(double);
extern int g_1440aec;   // offset-pool base used by UI object iterators
extern int g_164dd8c;   // default scroll-button time limit
extern void Mark1();
extern void Mark2();
extern void Mark3();
extern float FUN_0083ce70(float);
extern void cSPUILayout_Ctor(void*);
extern char cSPUILayout_Init(void*, int, int, int);
extern void* cSPUILayout_FindWindowByID(void*, int, int);
extern void cSPUILayout_Shutdown(void*, int); // 0x00811ad0
extern void cSPUILayout_Dtor(void*);   // 0x00811fe0 (equiv t3)

// ---- items of slice s0081a790 begin (TODO(rewrite): local stubs, replace by canonical classes)
    void cSPUILayout_Shutdown(...); // 0x00811ad0
extern "C" unsigned wcslen(const wchar_t*);
#pragma intrinsic(wcslen)
#define VTSLOT(p, off) ((*(void***)(p))[(off) / 4])
struct LimitStopwatch { void SetTimeLimit(int, int); };
class cSPUIPopupMenuItemWin { public:
  char pad00[0x888];
  int mChildIndex;               // +0x888
  void SomeFunc();               // 0081ae40
  __declspec(noinline) void OnAttach();   // 0081ad50
};
class cSPUIPopupMenuScrollButton { public:
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
class cSPUIPopupMenuWin { public:
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
  bool MeasureItemHeight(int skip, float* out);
  void AddMenuItem2(cSPUIPopupMenuItemWin* item, bool attach);
};
struct ScrollBtnCtor {
  char pad[0x888];
  LimitStopwatch timer;
  char pad2[0x8a8 - 0x888 - sizeof(LimitStopwatch)];
  bool b0;
  bool b1;
  void Ctor();
  void StopwatchCtor(int, int);
};
struct PopupWinCtor {
  char pad[0x888];
  int z[12];     // 0x888..0x8b7
  float f0, f1;  // 0x8b8,0x8bc
  char b0, b1, b2, b3, b4, b5;
  char pad2[2];
  int d0;        // 0x8c8
  void Ctor();
};
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
struct cSPUIPopupMenuWin2 {
  char pad00[0x8a8];
  void* AddMenuItem3(int id, int styleId, int parent, bool attach);
};
namespace EAT {
struct TextStyle;
}
namespace EAT {
struct LineLayout {
  char pad00[0x98];
  float mX;      // +0x98
  char pad01[4];
  float mTop;    // +0xa0
  float mBot;    // +0xa4
  void Clear(int);                                   // 0x0089cbc0
};
}
namespace EAT {
struct StyleManager {
  TextStyle* GetStyle(unsigned id, TextStyle* def);  // 0x00894670
};
}
namespace EAT {
struct Typesetter {
  LineLayout* GetLineLayout();                       // 0x008976a0
  int LayoutLine(const wchar_t* text, unsigned len, float x, float y, const TextStyle* st); // 0x0089db20
};
}
extern EAT::StyleManager* __cdecl EAGetStyleManager(bool create);  // 0x00885bd0
static __forceinline const float& MaxRef(const float& a, const float& b) { return a < b ? b : a; }
// ---- items of slice s0081a790 end

// ---- items of slice s0081b990 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern unsigned int g_164dc58;
extern void EndModal(void*, int, int);
struct Menu { void HideMenuItems(bool, bool); };
struct cAutoPropertyBaseLink {
  char pad00[4];
  void* mList;                 // +4
  void Update(void* except);   // 0081bfb0
};
struct C1 {
  char pad00[4];
  int mField4;                 // +4
  char pad01[4];
  unsigned int mFieldC;        // +0xc
  bool Method(int* arg);
};
struct Evt { char pad00[8]; int type; int a; int b; int c; };
struct C2 {
  char pad00[0xc];
  void* mFieldC;              // +0xc
  bool Method2(int unused, Evt* e);
};
struct Menu2 {
  void HideMenuItems(bool, bool);
  void OnMenuItemSelected(Menu2* b, Menu2* a);
};
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
// ---- items of slice s0081b990 end

// ---- items of slice s0081c9c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int g_13ec468;
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(long long*);
extern unsigned int g_164dd9c;
extern void* PropertyManager();
extern void UpdateMouseFocus(int);
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
struct ScrollBtn2 {
  char pad[0x8a9 - 0];
  void ScrollButtonSelected(int);
  void OnButtonClicked(int);
  void OnButtonClicked2(int arg);
};
struct MB {
  char pad00[0x3c];
  int* head;      // +0x3c
  char pad01[0x8a8 - 0x40];
  int f8a8;       // +0x8a8
  int f8ac;       // +0x8ac
  void Do030();
  void Reset();
};
struct PMLink { void Update(void*); };
struct CopyHelper { void DoCopy(void*); };
extern CopyHelper g_1546030;
struct VO2 { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
             virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual unsigned char Flags(); };
struct VO { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual VO2* Get(); };
struct PBtn { char pad[0x20c]; VO sub; };
struct PMW {
  char pad00[0x898];
  char* upBtn;             // +0x898
  char* downBtn;           // +0x89c
  char pad01[0x8a4 - 0x8a0];
  void* f8a4;              // +0x8a4
  int bgImage;             // +0x8a8
  int upDrawable;          // +0x8ac
  int curIndex;            // +0x8b0
  int f8b4;                // +0x8b4
  char pad02[0x8c0 - 0x8b8];
  unsigned char b8c0, b8c1, b8c2, b8c3;
  void Do030();
  void SelectItem(int);                  // 0x0081c370
  void HideMenuItems(int, int);          // 0x0081b8b0
  int GetItemIndexFromChar(unsigned);    // 0x0081bbe0
  void BaseOnMouseUp(float, float, int, int);   // 0x00964450
  void BaseOnMouseWheel(float, float, int, int);  // 0x006f2f20
  void BaseOnChar(int, unsigned);               // 0x00950ea0
  void OnAttach();
  void OnMouseUp(float, float, int, int);
  void OnChar(int, unsigned);
  void OnScrollButtonClicked(char, int);
  void OnMouseWheel(float, float, int, int);
};
struct PSB {
  char pad00[0x8a0];
  long long limit;         // +0x8a0
  unsigned char active;    // +0x8a8 (byte at +0x8a9 tested below)
  unsigned char flag;      // +0x8a9
  void ScrollButtonSelected(int);
  unsigned char BaseOnTick();   // 0x009645a0
  unsigned char OnTick();
};
// ---- items of slice s0081c9c0 end

// @ 0x0081aa80
void cSPUIPopupMenuScrollButton::OnFocusLost(int a, int b)
{
  if (a == 1) mbF1 = false;
  OnFocusLostBase(a, b);
}

// @ 0x0081aad0
void cSPUIPopupMenuWin::Reset()
{
  mbF0 = 0; mbF1 = 0; mbF2 = 0; mbF3 = 0;
  mCenteredItemIndex = mSelectedItemIndex;
}

// @ 0x0081ad50
void cSPUIPopupMenuItemWin::OnAttach()
{
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

// @ 0x0081ae40
void cSPUIPopupMenuItemWin::SomeFunc()
{
  void* self = (char*)this + 4;
  void* vt = *(void**)self;
  ((void (__thiscall*)(void*, int, int))((void**)vt)[0x7c / 4])(self, 1, 0);
  OnAttach();
}

// @ 0x0081ae90
void ScrollBtnCtor::Ctor()
{
  *(void**)this = (void*)&Mark1;
  *(void**)((char*)this + 4) = (void*)&Mark2;
  *(void**)((char*)this + 0x20c) = (void*)&Mark3;
  StopwatchCtor(4, 0);
  timer.SetTimeLimit(g_164dd8c, 0);
  b0 = 0;
  b1 = 0;
}

// @ 0x0081af30
void cSPUIPopupMenuScrollButton::OnMouseWheel(float a1, float a2, int a3, int a4)
{
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

// @ 0x0081afb0
void cSPUIPopupMenuScrollButton::OnFocusAcquired(int a, int b)
{
  if (a == 1) {
    mbF1 = true;
    timer.SetTimeLimit(g_164dd8c, a);
  }
  OnFocusAcquiredBase(a, b);
}

// @ 0x0081b000
void PopupWinCtor::Ctor()
{
  *(void**)this = (void*)&Mark1;
  *(void**)((char*)this + 4) = (void*)&Mark2;
  *(void**)((char*)this + 0x20c) = (void*)&Mark3;
  for (int i = 0; i < 12; i++) z[i] = 0;
  f0 = 0.f; f1 = 0.f;
  b0 = b1 = b2 = b3 = b4 = b5 = 0;
  d0 = 0;
}

// @ 0x0081b100
static void ReleaseRef(void* p)
{
  ((void (__thiscall*)(void*))((void**)*(void**)p)[1])(p);
}

// @ 0x0081b240
bool cSPUIPopupMenuWin::MeasureItemHeight(int skip, float* out)
{
  if (skip != 0) return false;
  void* self = (char*)this + 4;
  struct __declspec(align(64)) Al { int v; };
  Al dummy_; dummy_.v = 0;
  float cur[2];
  cur[0] = 0.f; cur[1] = 0.f;
  float maxW = 0.f, maxH = 0.f;
  void* it;
  void* end;
  ((void (__thiscall*)(void*, void*))VTSLOT(self, 0xcc))(self, &it);
  ((void (__thiscall*)(void*, void*))VTSLOT(self, 0xd0))(self, &end);
  while (it != end) {
    void* w;
    if ((void*)(g_1440aec + (int)it) == 0 ||
        (w = ((void* (__thiscall*)(void*, int))VTSLOT((void*)(g_1440aec + (int)it), 0xc))((void*)(g_1440aec + (int)it), 0x4c058cf)) == 0) {
      void* obj = (void*)(g_1440aec + (int)it);
      if (obj != 0) {
        void* m = ((void* (__thiscall*)(void*, int))VTSLOT(obj, 0xc))(obj, 0x4c058d5);
        if (m != 0)
          ((void (__thiscall*)(void*, int, float*))VTSLOT(m, 0xa4))(m, 0, cur);
      }
    } else {
      void* wself = (char*)w + 4;
      const wchar_t* text = ((const wchar_t* (__thiscall*)(void*))VTSLOT(wself, 0x3c))(wself);
      unsigned len = (unsigned)wcslen(text);
      if (text != 0 && len > 0u) {
        EAT::StyleManager* sm = EAGetStyleManager(true);
        if (sm != 0) {
          EAT::TextStyle* st = sm->GetStyle(((unsigned (__thiscall*)(void*))VTSLOT(wself, 0x40))(wself), 0);
          if (st != 0) {
            EAT::Typesetter* ts = (EAT::Typesetter*)((char*)this + 0x280);
            EAT::LineLayout* ll = ts->GetLineLayout();
            ll->Clear(1);
            ts->LayoutLine(text, len, 0.f, 0.f, st);
            cur[0] = ll->mX;
            cur[1] = ll->mTop - ll->mBot;
          }
        }
      }
    }
    maxW = MaxRef(maxW, cur[0]);
    float c = (float)ceil((double)cur[1]);
    maxH = MaxRef(maxH, c);
    it = *(void**)it;
  }
  out[0] = *(float*)((char*)this + 0x250) + *(float*)((char*)this + 0x248) + maxW;
  out[1] = *(float*)((char*)this + 0x254) + *(float*)((char*)this + 0x24c) + maxH;
  float tmp[2];
  tmp[0] = 0.f; tmp[1] = 0.f;
  void* sub = *(void**)((char*)this + 0x1e0);
  if (sub != 0)
    ((void (__thiscall*)(void*, float*, int, int))VTSLOT(sub, 0x18))(sub, tmp, 0, 0);
  out[0] = MaxRef(out[0], tmp[0]);
  out[1] = MaxRef(out[1], tmp[1]);
  float k = 14.0f;
  out[0] = MaxRef(out[0], k);
  out[1] = MaxRef(out[1], k);
  return true;
}

// @ 0x0081b510
void PopupWinDetach::OnDetach()
{
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

// @ 0x0081b650
void cSPUIPopupMenuWin::AddMenuItem2(cSPUIPopupMenuItemWin* item, bool attach)
{
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

// @ 0x0081b6a0
void* cSPUIPopupMenuWin2::AddMenuItem3(int id, int styleId, int parent, bool attach)
{
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

// @ 0x0081b750
void* cSPUIPopupMenuWin::FindChild(int idx)
{
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

// @ 0x0081b7d0
void cSPUIPopupMenuWin::RemoveChild(int idx)
{
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

// @ 0x0081b8b0
void cSPUIPopupMenuWin::HideMenuItems(bool a, bool b)
{
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

// @ 0x0081bce0
bool C1::Method(int* arg)
{
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

// @ 0x0081bd50
bool C2::Method2(int unused, Evt* e)
{
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

// @ 0x0081bef0
void Menu2::OnMenuItemSelected(Menu2* b, Menu2* a)
{
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

// @ 0x0081bfb0
void cAutoPropertyBaseLink::Update(void* except)
{
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

// @ 0x0081c900
char ItemMouseUp::OnMouseUp(float a1, float a2, int a3, int a4)
{
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

// @ 0x0081c9c0
void PMW::OnAttach()
{
  Do030();
  void* self = (char*)this + 4;
  void* o = ((void* (__thiscall*)(void*))VTSLOT(self, 0x10))(self);
  if (o != 0) {
    char* q = (char*)((void* (__thiscall*)(void*, int))VTSLOT(o, 0xc))(o, 0x4c058d5);
    if (q != 0) {
      ((void (__thiscall*)(void*, int, int))VTSLOT(self, 0x7c))(self, 1, 0);
      f8b4 = *(int*)(q + 0x8a8);
      (*(int*)(q + 0x8a8))++;
    }
  }
  void* pm = PropertyManager();
  void* old = f8a4;
  if (old != 0) {
    f8a4 = 0;
    ((void (__thiscall*)(void*))VTSLOT(old, 4))(old);
  }
  if (((char (__thiscall*)(void*, int, void*))VTSLOT(pm, 0x30))(pm, 0x5c770db7, &f8a4))
    g_1546030.DoCopy(f8a4);
}

// @ 0x0081ca60
void PMW::OnMouseUp(float x, float y, int c, int d)
{
  if (bgImage != 0) {
    void* self = (char*)this + 4;
    float* r = ((float* (__thiscall*)(void*))VTSLOT(self, 0x38))(self);
    bool inside = true;
    if (x < 0.0f || y < 0.0f || r[2] - r[0] < x || r[3] - r[1] < y) inside = false;
    void* o = ((void* (__thiscall*)(void*))VTSLOT(self, 0x10))(self);
    if (o != 0) {
      curIndex = upDrawable;
      b8c0 = 0; b8c1 = 0; b8c2 = 0; b8c3 = 0;
      PMLink* l = ((PMLink* (__thiscall*)(void*, int))VTSLOT(o, 0xc))(o, 0x4c058d5);
      if (inside) {
        if (l != 0) l->Update(this);
        SelectItem(1);
      } else {
        HideMenuItems(0, 1);
        EndModal(self, 0, 0);
        if (l != 0)
          ((void (__thiscall*)(void*, float, float, int, int))VTSLOT(l, 0x40))(l, -1.0f, -1.0f, c, d);
      }
    }
  } else {
    void* o = ((void* (__thiscall*)(void*))VTSLOT((char*)this + 4, 0x10))((char*)this + 4);
    if (o != 0) {
      curIndex = upDrawable;
      b8c0 = 0; b8c1 = 0; b8c2 = 0; b8c3 = 0;
      PMLink* l = ((PMLink* (__thiscall*)(void*, int))VTSLOT(o, 0xc))(o, 0x4c058d5);
      if (l != 0) l->Update(this);
    }
  }
  BaseOnMouseUp(x, y, c, d);
}

// @ 0x0081cbe0
void PMW::OnChar(int a, unsigned b)
{
  int idx;
  if ((unsigned short)(b - 0x30) <= 9) {
    idx = GetItemIndexFromChar(b);
  } else {
    unsigned w = (wint_t)towlower((wint_t)b);
    if ((unsigned short)(w - 0x61) > 0x19) goto done;
    idx = GetItemIndexFromChar(w);
  }
  if (idx >= 0 && idx != curIndex) {
    b8c2 = 0; b8c3 = 0; b8c0 = 0; b8c1 = 0;
    curIndex = idx;
    SelectItem(0);
  }
done:
  BaseOnChar(a, b);
}

// @ 0x0081cc60
void PMW::OnScrollButtonClicked(char down, int p3)
{
  char** pb = &upBtn;
  if (!down) pb = &downBtn;
  PBtn* bt = (PBtn*)*pb;
  unsigned char f = bt->sub.Get()->Flags();
  if ((f & 1) && (f & 2)) {
    HideMenuItems(0, p3);
    if (down) {
      curIndex--;
      b8c3 = 0;
      SelectItem(0);
      return;
    }
    curIndex++;
    b8c2 = 0;
    SelectItem(0);
  }
}

// @ 0x0081cce0
void MB::Reset()
{
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

// @ 0x0081cd50
void SB::ScrollButtonSelected(int arg)
{
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

// @ 0x0081cdb0
void PMW::OnMouseWheel(float a, float b, int c, int delta)
{
  bool up = delta > 0;
  char** pb = &upBtn;
  if (!up) pb = &downBtn;
  PBtn* btn = (PBtn*)*pb;
  unsigned i = 0;
  if (g_164dd9c > 0) {
    do {
      unsigned char f = btn->sub.Get()->Flags();
      if (!(f & 1) || !(f & 2)) break;
      OnScrollButtonClicked(up, 0);
      i++;
    } while (i < g_164dd9c);
  }
  UpdateMouseFocus(1);
  BaseOnMouseWheel(a, b, c, delta);
}

// @ 0x0081ce60
void ScrollBtn2::OnButtonClicked2(int arg)
{
  ScrollButtonSelected(1);
  OnButtonClicked(arg);
}

// @ 0x0081ce80
unsigned char PSB::OnTick()
{
  if (flag) {
    long long now;
    QueryPerformanceCounter(&now);
    if (limit - now < 0) ScrollButtonSelected(0);
  }
  unsigned char r = BaseOnTick();
  void* self = (char*)this + 4;
  ((void (__thiscall*)(void*, int, int))VTSLOT(self, 0x7c))(self, 8, 1);
  return r;
}

// @ 0x012fc2b0
void init_1546064()
{
    *(int*)0x1546064 = 1;
    *(int*)0x1546068 = 0;
    *(void**)0x154606c = (void*)0x1418fd8; *(int*)0x1546070 = 0x4c9a86d; *(short*)0x1546074 = 0x13; *(int*)0x1546078 = 0x88c; *(int*)0x154607c = 1; *(int*)0x1546080 = 0;
    *(void**)0x1546084 = (void*)0x1418fd8; *(int*)0x1546088 = 0x4c9a86e; *(short*)0x154608c = 0x13; *(int*)0x1546090 = 0x890; *(int*)0x1546094 = 1;
}
