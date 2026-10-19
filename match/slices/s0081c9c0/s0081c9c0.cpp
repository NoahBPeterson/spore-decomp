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
// @ 0x0081d7a0
Variant* Variant::Reset(int v) {
  if (flags & 4) Destruct(1);
  unsigned short f = flags & 2;
  if (f && typeId != 1) { Call5(1, 0x20, v, 1, 1); return this; }
  flags = f | 0x20; typeId = 1;
  f0 = v; f4 = 1; f8 = 1;
  return this;
}
// @ 0x0081da30
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
// @ 0x0081cce0
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
// @ 0x0081ddd0
D3* D3::Init(int arg) { w10 = 2; w12 = 0x33; Call5(0x33, 0, arg, 0x10, 1); return this; }
// @ 0x0081de30
D3* D3::Init2(int arg) { w10 = 2; w12 = 0x34; Call5(0x34, 0, arg, 0x10, 1); return this; }

// ===========================================================================
// cSPUIPopupMenuWin / scroll button methods (retail offsets)
// ===========================================================================
#include <wchar.h>
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(long long*);
extern unsigned int g_164dd9c;
struct PMLink { void Update(void*); };
struct CopyHelper { void DoCopy(void*); };
extern CopyHelper g_1546030;
extern void* PropertyManager();
extern void EndModal(void*, int, int);
extern void UpdateMouseFocus(int);
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
// @ 0x0081c9c0
void PMW::OnAttach() {
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
void PMW::OnMouseUp(float x, float y, int c, int d) {
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
void PMW::OnChar(int a, unsigned b) {
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
void PMW::OnScrollButtonClicked(char down, int p3) {
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
// @ 0x0081cdb0
void PMW::OnMouseWheel(float a, float b, int c, int delta) {
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

struct PSB {
  char pad00[0x8a0];
  long long limit;         // +0x8a0
  unsigned char active;    // +0x8a8 (byte at +0x8a9 tested below)
  unsigned char flag;      // +0x8a9
  void ScrollButtonSelected(int);
  unsigned char BaseOnTick();   // 0x009645a0
  unsigned char OnTick();
};
// @ 0x0081ce80
unsigned char PSB::OnTick() {
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

// ===========================================================================
// 0081df10  SP::cPropertyUI::FindPropertyUIWindow
// ===========================================================================
struct UObj {
  virtual void AddRef();                   // slot 0
  virtual void Release();                  // slot 1
  virtual void v2();
  virtual UObj* Cast(unsigned id);         // slot 3
};
struct UWin : UObj {
  char pad[0x1c / 4 * 4 - 16 - 4 + 4];
};
struct UVec { UObj** begin; UObj** end; };
struct UiLayout { UVec* GetObjects(); };   // 0x008100c0
struct PUI {
  char pad00[0x44];
  UiLayout layout;     // +0x44
  void** FindPropertyUIWindow(void** out, int id);
};
// @ 0x0081df10
void** PUI::FindPropertyUIWindow(void** out, int id) {
  UVec* v = layout.GetObjects();
  int n = v->end - v->begin;
  for (int i = 0; i < n; i++) {
    {
      UObj* obj = v->begin[i];
      UObj* w;
      if (obj != 0) {
        obj->AddRef();
        w = obj->Cast(0xeeee8218);
      } else {
        w = 0;
      }
      UObj* res = w;
      if (res != 0) {
        w->AddRef();
        int wid = ((int (__thiscall*)(void*))VTSLOT(w, 0x1c))(w);
        if (wid == id) {
          *out = w;
          w->AddRef();
          w->Release();
          if (obj != 0) obj->Release();
          return out;
        }
        UObj* r = ((UObj* (__thiscall*)(void*, int, int))VTSLOT(w, 0xf0))(w, id, 1);
        if (r != w) {
          if (r != 0) r->AddRef();
          w->Release();
          res = r;
        }
        if (res != 0) {
          *out = res;
          res->AddRef();
          res->Release();
          if (obj != 0) obj->Release();
          return out;
        }
      }
      if (obj != 0) obj->Release();
    }
  }
  *out = 0;
  return out;
}

// ===========================================================================
// Not reconstructed -- see partial.txt
// 0081c9c0, 0081ca60, 0081cbe0, 0081cc60, 0081cdb0, 0081ce80,
// 0081cf50, 0081d020, 0081d0f0, 0081d480, 0081d510, 0081d5e0, 0081df10
// ===========================================================================
