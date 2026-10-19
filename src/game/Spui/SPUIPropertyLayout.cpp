// src/game/Spui/SPUIPropertyLayout.cpp -- migrated from slice(s) s00827bf0 by tools/migrate/rewrite.py
// Object file: Spui/SPUIPropertyLayout.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "cSPUIPropertyLayout.h"
#include "EA/Stopwatch.h"
#include "EA/Variant.h"
#include "SP/cPropertyUI.h"
#include "cSPUILayout.h"
#include <new>

// ---- items of slice s00827bf0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Key { unsigned int a, b, c; };
struct RectF { float x0, y0, x1, y1; };
struct Pt { float x, y; Pt() {} Pt(const Pt& o) : x(o.x), y(o.y) {} };
struct Rect2 { Pt a, b; };
struct UIObj {
virtual void s0();
virtual void s1();
virtual void s2();
  virtual void* Cast(unsigned id);  // +0xc
  virtual UIObj* Get10();  // +0x10
virtual void s5();
virtual void s6();
  virtual unsigned GetId();  // +0x1c
virtual void s8();
virtual void s9();
  virtual int Get28();  // +0x28
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
  virtual void SetPos64(float x, float y);  // +0x64
virtual void s26();
virtual void s27();
  virtual void SetPos(float x, float y);  // +0x70
virtual void s29();
virtual void s30();
  virtual void Set7c(int a, int b);  // +0x7c
  virtual void Set80(unsigned a);  // +0x80
virtual void s33();
virtual void s34();
virtual void s35();
  virtual void Fn90();  // +0x90
virtual void s37();
virtual void s38();
virtual void s39();
virtual void s40();
  virtual bool Fa4(unsigned* a, unsigned* b);  // +0xa4
virtual void s42();
virtual void s43();
virtual void s44();
virtual void s45();
virtual void s46();
virtual void s47();
virtual void s48();
virtual void s49();
virtual void s50();
virtual void s51();
virtual void s52();
virtual void s53();
virtual void s54();
virtual void s55();
virtual void s56();
virtual void s57();
virtual void s58();
virtual void s59();
virtual void s60();
virtual void s61();
virtual void s62();
virtual void s63();
virtual void s64();
  virtual void Attach(void* p);  // +0x104
virtual void s66();
virtual void s67();
virtual void s68();
virtual void s69();
virtual void s70();
virtual void s71();
virtual void s72();
virtual void s73();
virtual void s74();
virtual void s75();
virtual void s76();
virtual void s77();
virtual void s78();
virtual void s79();
virtual void s80();
virtual void s81();
virtual void s82();
virtual void s83();
virtual void s84();
virtual void s85();
virtual void s86();
virtual void s87();
virtual void s88();
virtual void s89();
virtual void s90();
virtual void s91();
virtual void s92();
virtual void s93();
virtual void s94();
virtual void s95();
virtual void s96();
virtual void s97();
virtual void s98();
virtual void s99();
virtual void s100();
virtual void s101();
virtual void s102();
virtual void s103();
  virtual void F1a0(unsigned a, unsigned b, unsigned* c);  // +0x1a0
virtual void s105();
virtual void s106();
virtual void s107();
virtual void s108();
virtual void s109();
virtual void s110();
virtual void s111();
virtual void s112();
  virtual unsigned F1c4(unsigned a, unsigned b);  // +0x1c4
};
struct QObj {
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
  virtual RectF* GetRect();  // +0x38
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
virtual void s48();
  virtual Pt* FindPos(Pt* out, Pt p);  // +0xc4
};
struct WinMgr {
  virtual void s0(); 
  virtual QObj* GetMain();  // +0x4
};
struct WinProcBase {
  WinProcBase() {}
  ~WinProcBase() {}
  virtual int AddRef();  // +0x0
  virtual int Release();  // +0x4
  virtual void s2(); 
  virtual void* Cast(unsigned id);  // +0xc
  virtual void s4(); 
  virtual unsigned GetEventMask();  // +0x14
  virtual bool DoMessage(int, void*);  // +0x18
  virtual bool Init();  // +0x1c
  virtual void func20h();  // +0x20
  virtual void func24h();  // +0x24
};
WinMgr* WindowManager();                         // 0x0067caa0
Rect2* FUN_00808370(Rect2* out, UIObj* w, int flag);   // 0x00808370 (cdecl)
typedef UIObj IWindow;
struct cSPUILayout_s0082_7bf0 {
  cSPUILayout_s0082_7bf0();                              // 0x00810000
  ~cSPUILayout_s0082_7bf0();                             // 0x00811fe0
  void Shutdown(int);                         // 0x00811ad0 (callee pops)
  bool IsVisible() const;                     // 0x00810070
  bool Init(const Key* k, bool b, unsigned u);   // 0x008120d0
  void* FindWindowByID(int id, int flag);     // 0x008105b0 __thiscall (callee pops)
  struct ObjVec { UIObj** mpBegin; UIObj** mpEnd; };
  ObjVec* GetObjects();                       // 0x008100c0
  void* mpVtbl;               // +0x0
  int mRefCount;              // +0x4
  void* mpObject;             // +0x8
};
struct Stopwatch {
  char pad0[0x14];            // +0x0
  float mUnitsPerSecond;      // +0x14
  Stopwatch(int units, bool b);    // 0x0093a560 (callee pops)
  __int64 GetElapsedTime();
};
struct Variant {
  char pad[0x10];
  unsigned short mFlags;
  unsigned short mTypeId;
  Variant() { mFlags = 0; mTypeId = 0; }
  Variant& operator=(const Variant&);   // 0x00542b80
  void Destruct(int);
};
struct IRefThing { virtual int AddRef(); virtual int Release(); };
struct Elem {
  unsigned int first;      // +0x00
  void* mpObject;          // +0x04
  Variant mVariant;        // +0x08
  int mLast;               // +0x1c
  Elem(const Elem& o);
  Elem& operator=(const Elem& o);
};
struct ElemVec {
  Elem* mpBegin;
  Elem* mpEnd;
  Elem* mpCapacity;
  ElemVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~ElemVec() {
    DoDestroyValues(mpBegin, mpEnd);
    if (mpBegin) operator delete(mpBegin);
  }
  void DoDestroyValues(Elem* first, Elem* last);
};
struct RefCountBase {
  RefCountBase() : mRefCount(0) {}
  ~RefCountBase() {}
virtual int rc0();
virtual int rc1();
virtual int rc2();
virtual int rc3();
  int mRefCount;              // +0x8
};
struct CPL : WinProcBase, RefCountBase {
  cSPUILayout_s0082_7bf0 mLayout;        // +0xc
  char pad18[0xc];            // +0x18 .. +0x23
  int mKey24;                 // +0x24
  int mKey28;                 // +0x28
  ElemVec mProperties;        // +0x2c
  char pad38[0xc];            // +0x38 .. +0x43
  bool mbInitialized;         // +0x44
  int mRootWinId;             // +0x48
  float mInterval;            // +0x4c
  Stopwatch mStopwatch;       // +0x50
  float mTime;                // +0x68
  float mOffsetX;             // +0x6c
  float mOffsetY;             // +0x70
  bool mbFlag;                // +0x74

  CPL();
  ~CPL();
  virtual unsigned GetEventMask();
  virtual bool DoMessage(int, void*);
  virtual bool Init();
  void SetKey(const wchar_t* name, int uid);
  void SetFlag(bool b);
  void* GetRootWindow();
  void SetPositionAndOffset(float x, float y, float offX, float offY);
  void ForceVisibleLocation();
};
Elem& Elem::operator=(const Elem& o) {
  first = o.first;
  void* old = mpObject;
  void* nw = o.mpObject;
  if (nw != old) {
    if (nw) ((IRefThing*)nw)->AddRef();
    mpObject = nw;
    if (old) ((IRefThing*)old)->Release();
  }
  mVariant = o.mVariant;
  mLast = o.mLast;
  return *this;
}
// ---- items of slice s00827bf0 end

// @ 0x00828070
unsigned int CPL::GetEventMask()
{
  return mbFlag ? 2 : 0;
}

// @ 0x00828080
bool CPL::DoMessage(int a, void* b)
{
  if (*(int*)((char*)b + 8) == 0xc) {
    if (mTime > mInterval) {
      ((void(__thiscall*)(void*))(*(void***)this)[0x20 / 4])(this);
    }
    Stopwatch& sw = mStopwatch;
    mTime = (float)sw.GetElapsedTime() * sw.mUnitsPerSecond;
  }
  return false;
}

// @ 0x00828100
EA::UTFWin::IWindow * cSPUIPropertyLayout::GetRootWindow()
{
  return mLayout.FindWindowByID(mRootWinId, 1);
}

// @ 0x00828110
void CPL::ForceVisibleLocation()
{
  IWindow* w = (IWindow*)mLayout.FindWindowByID(mRootWinId, 1);
  if (w) {
    if (w->Get10()) {
      if (WindowManager()->GetMain()) {
        QObj* q = WindowManager()->GetMain();
        RectF* r = q->GetRect();
        Rect2 R;
        Pt P;
        FUN_00808370(&R, w, 1);
        Pt pf = *q->FindPos(&P, R.b);
        float x = P.x;
        float y = P.y;
        if (pf.x > r->x1) x = (P.x - mOffsetX * 2.0f) - (R.a.x - P.x);
        if (pf.y > r->y1) y = (P.y - mOffsetY * 2.0f) - (R.a.y - P.y);
        w->SetPos(x, y);
      }
    }
  }
}

// @ 0x00828250
bool CPL::Init()
{
  if (!mbInitialized) {
    mTime = 1.0e30f;
    Key k = {(unsigned)mKey24, 0x510a95b, (unsigned)mKey28};
    mbInitialized = mLayout.Init(&k, false, 0x5b598fa);
    if (mbInitialized) {
      IWindow* w = (IWindow*)mLayout.FindWindowByID(mRootWinId, 1);
      if (!w) {
        cSPUILayout_s0082_7bf0::ObjVec* objs = mLayout.GetObjects();
        int n = (int)(objs->mpEnd - objs->mpBegin);
        for (int i = 0; i < n; ++i) {
          IWindow* c = (IWindow*)objs->mpBegin[i]->Cast(0xeeee8218);
          if (c) {
            mRootWinId = c->GetId();
            w = c;
            break;
          }
        }
      }
      mbInitialized = (w != 0);
      if (w) w->Attach(this);
    }
  }
  return mbInitialized;
}

// @ 0x008283a0
void CPL::SetPositionAndOffset(float x, float y, float offX, float offY)
{
  mOffsetX = offX;
  mOffsetY = offY;
  IWindow* w = (IWindow*)mLayout.FindWindowByID(mRootWinId, 1);
  if (w) {
    ((void(__thiscall*)(void*, float, float))(*(void***)w)[0x70 / 4])(w, x + offX, y + offY);
    ForceVisibleLocation();
  }
}

// @ 0x00828410
void ElemVec::DoDestroyValues(Elem* first, Elem* last)
{
  for (; first < last; ++first) {
    Variant* v = &first->mVariant;
    if (first->mVariant.mFlags & 4) v->Destruct(0);
    IRefThing* p = (IRefThing*)first->mpObject;
    if (p) p->Release();
  }
}

// @ 0x00828450
Elem::Elem(const Elem& o)
: first(o.first), mpObject(o.mpObject) {
  if (mpObject) ((IRefThing*)mpObject)->AddRef();
  mVariant = o.mVariant;
  mLast = o.mLast;
}

// @ 0x008284f0
Elem* ElemMoveStart(Elem* first, Elem* last, Elem* dst)
{
  for (; first != last; ++first, ++dst) {
    if (dst) ::new ((void*)dst) Elem(*first);
  }
  return dst;
}

// @ 0x00828560
Elem* ElemCopy(Elem* first, Elem* last, Elem* dst)
{
  for (; first != last; ++first, ++dst) *dst = *first;
  return dst;
}

// @ 0x008285e0
Elem* ElemCopyBackward(Elem* first, Elem* last, Elem* dst)
{
  while (last != first) {
    --last;
    --dst;
    *dst = *last;
  }
  return dst;
}

// @ 0x00828670
CPL::~CPL()
{
  mLayout.Shutdown(1);
}

// @ 0x008286d0
CPL::CPL()
: mKey24(-1), mKey28(-1), mbInitialized(false), mRootWinId(0), mInterval(1.0f), mStopwatch(5, false) {
  mTime = 1.0e30f;
  mbFlag = true;
}
