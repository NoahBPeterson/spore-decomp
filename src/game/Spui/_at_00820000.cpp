// src/game/Spui/_at_00820000.cpp -- migrated from slice(s) s0082dc00, s0082cd30, s00829bc0, s00828c30, s00827bf0 by tools/migrate/rewrite.py
// Object file: Spui/_at_00820000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cString.h"
#include "EA/Stopwatch.h"
#include "EA/Variant.h"
#include <new>
#include <intrin.h>
#include "EA/UTFWin/RenderContext.h"
#include <math.h>
#include <string.h>
#include "EA/ResourceMan/Manager.h"
#include "EA/Allocator/StackAllocator.h"

// ---- items of slice s00827bf0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Key { unsigned int a, b, c; };
void SPKeyFromName(Key* out, const wchar_t* name, unsigned int ns, int id);
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
  virtual bool func24h();  // +0x24
};
typedef UIObj IWindow;
class cSPUILayout_s0082_7bf0 { public:
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
extern void (*g_TimerFunc)(unsigned __int64*);   // 0x013cc2b8 (QueryPerformanceCounter)
struct Stopwatch {
  unsigned mStartLo;          // +0x0
  unsigned mStartHi;          // +0x4
  unsigned mAccLo;            // +0x8
  unsigned mAccHi;            // +0xc
  int mMode;                  // +0x10 (1 == rdtsc)
  float mUnitsPerSecond;      // +0x14
  Stopwatch(int units, bool b);    // 0x0093a560 (callee pops)
  __int64 GetElapsedTime();        // 0x0093a3a0
  void Reset();
};
inline void Stopwatch::Reset() {
  unsigned __int64 t;
  if (mMode == 1) t = __rdtsc();
  else g_TimerFunc(&t);
  mStartLo = (unsigned)t;
  mStartHi = (unsigned)(t >> 32);
  mAccLo = 0;
  mAccHi = 0;
}
struct Variant {
  union {
    void* mpValue;
    unsigned uValue;
    float fValue;
    char raw[0x10];
  };
  unsigned short mFlags;      // +0x10
  unsigned short mTypeId;     // +0x12
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
  void clear();
  Elem* insert(Elem* position, const Elem& value);
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
  virtual void func20h();
  virtual bool func24h();
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
Elem* ElemCopy(Elem* first, Elem* last, Elem* dst);  // 0x00828560 (defined below; used by a stub's inline body)
void ElemVec::clear() {
  Elem* first = mpBegin;
  Elem* last = mpEnd;
  Elem* newEnd = ElemCopy(last, last, first);
  DoDestroyValues(newEnd, mpEnd);
  mpEnd -= (last - first);
}
// ---- items of slice s00827bf0 end

// ---- items of slice s00828c30 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char g_wrapAllocName[];   // 0x013f6b3c
extern void __cdecl OperatorDeleteRaw(void* p);                                        // 0x00f47380
struct C25c {
  char pad0[0x10];
  void* m10;          // +0x10
  char pad14[0x14];   // +0x14 .. +0x27
  void* m28;          // +0x28
  void Do(int arg);
};
struct IThing {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void v4();
virtual void v5(int, int);
virtual void v6();
};
struct C25b {
  char pad0[0xc];
  IThing* mObj;       // +0xc
  int m10;            // +0x10
  void Do(int arg);
};
struct Pt {
  float x, y;
  Pt() {}
  Pt(float a, float b) : x(a), y(b) {}
  Pt(const Pt& o) : x(o.x), y(o.y) {}
};
struct Rect {
  float l, t, r, b;
  Rect() {}
  Rect(float a, float b_, float c, float d) : l(a), t(b_), r(c), b(d) {}
  Rect(const Rect& o) : l(o.l), t(o.t), r(o.r), b(o.b) {}
  Rect& operator=(const Rect& o) { l = o.l; t = o.t; r = o.r; b = o.b; return *this; }
};
#define TL(rc) (*(Pt*)&(rc).l)
class IWin;
class IRef {
public:
    virtual void AddRef();  // slot 0 +0x0
    virtual void Release();  // slot 1 +0x4
};
class IProv {
public:
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
    virtual IWin* GetWindow();  // slot 19 +0x4c
};
class IText {
public:
    virtual void AddRef();  // slot 0 +0x0
    virtual void Release();  // slot 1 +0x4
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void Measure(Rect* out, int a, int b);  // slot 8 +0x20
};
class IParent {
public:
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
    virtual void Place(int a, IWin* w);  // slot 19 +0x4c
};
class IWin {
public:
    virtual void AddRef();  // slot 0 +0x0
    virtual void Release();  // slot 1 +0x4
    virtual void s2();
    virtual IText* QueryText(unsigned id);  // slot 3 +0xc
    virtual IWin* GetParent();  // slot 4 +0x10
    virtual IParent* GetContainer();  // slot 5 +0x14
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual unsigned GetFlags();  // slot 10 +0x28
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual Rect* GetArea();  // slot 14 +0x38
    virtual void s15();
    virtual int GetStyleId();  // slot 16 +0x40
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
    virtual void SetArea(const Rect* r);  // slot 27 +0x6c
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
    virtual Pt* ToScreen(Pt* out, Pt p);  // slot 48 +0xc0
    virtual Pt* ToLocal(Pt* out, Pt p);  // slot 49 +0xc4
    virtual void s50();
    virtual void s51();
    virtual void s52();
    virtual void s53();
    virtual void Detach(IWin* w);  // slot 54 +0xd8
    virtual void Attach(IWin* w);  // slot 55 +0xdc
};
class IRectCb {
public:
    virtual bool IsDragging();  // slot 0 +0x0
    virtual void GetRect(Rect* out);  // slot 1 +0x4
    virtual void SetRect(const Rect* r);  // slot 2 +0x8
};
template <class T> class AutoRef {
 public:
  T* p;
  AutoRef() : p(0) {}
  AutoRef(T* n) : p(n) { if (n) n->AddRef(); }
  ~AutoRef() { if (p) p->Release(); }
  AutoRef& operator=(T* n) {
    T* old = p;
    if (n != old) {
      if (n) n->AddRef();
      p = n;
      if (old) old->Release();
    }
    return *this;
  }
};
class AutoRefWin {
 public:
  IWin* p;
  AutoRefWin() : p(0) {}
  ~AutoRefWin();
  AutoRefWin& operator=(IWin* n);
};
inline AutoRefWin::~AutoRefWin() {
  if (p) ((IRef*)p)->Release();
}
class IResBase {
 public:
  virtual ~IResBase() {}
  virtual void rb1();
};
class IRC {
 public:
  IRC() : mnRefCount(0) {}
  virtual ~IRC() {}
  virtual void rc1();
  int mnRefCount;
};
class cRender2D {
 public:
  IRef* F9557c0();   // 0x009557c0
};
class RenderContext {
 public:
  void End2D();                 // 0x0095bb20
  cRender2D* Begin2D(IText* r);  // 0x0095bc10
};
IWin* F951d50();   // 0x00951d50
class cWrap : public IResBase, public IRC {
 public:
  AutoRef<IText> mC;     // +0xc
  AutoRef<IRef> m10;     // +0x10
  cRender2D* m14;        // +0x14
  cWrap(IProv* prov, IRef* ref);
  static void operator delete(void* p);
  void* operator new(unsigned sz, const void* name, int a, int b, int c, int d);
};
class RefVec {
 public:
  IRef** mpBegin;
  IRef** mpEnd;
  IRef** mpCap;
  RefVec() : mpBegin(0), mpEnd(0), mpCap(0) {}
  ~RefVec();                                              // 0x004b5440
  IRef** DoAllocateAndCopy(unsigned n, IRef** f, IRef** l);   // 0x00829a10
  void DoDestroy(IRef** f, IRef** l);                     // 0x00b007f0
  RefVec& operator=(const RefVec& x);
};
class cLayoutBase {
 public:
  cLayoutBase() : m4(0) {}
  virtual ~cLayoutBase() {}
  int m4;
};
class cPropLayout : public cLayoutBase {
 public:
  bool mBusy;          // +8
  bool mMoved;         // +9
  bool mPending;       // +0xa
  float mOffset;       // +0xc
  IRectCb* m10;        // +0x10
  RefVec mKids;        // +0x14
  char pad20[0x28 - 0x20];
  AutoRef<IWin> m28;   // +0x28
  AutoRef<IWin> m2c;   // +0x2c
  AutoRefWin m30;      // +0x30
  cPropLayout();
  static void operator delete(void* p);
  float MeasureOverflow();
  Rect* GetRect(Rect* out);
  Rect* GetRectLocal(Rect* out);
  void SetRect2(const Rect* in, bool flag);
  void ApplyRect(const Rect* r);   // 0x008290e0
  void UpdateLayout(bool active);
  void Tick();
};
IRef** __cdecl CopyRefsRange(IRef** first, IRef** last, IRef** dest);                  // 0x006782c0
IRef*** __cdecl UninitCopyRefs5(IRef*** res, IRef** first, IRef** last, IRef** dest, const RefVec* junk);   // 0x00829110
// ---- items of slice s00828c30 end

// ---- items of slice s00829bc0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char g_sfvBase0Vtbl;    // 0x13eb938
extern char g_sfvBase1Vtbl;    // 0x13ec458
extern const float kRotEps;    // 0x1419f4c
extern const float kDeg2Rad;   // 0x1419f1c
struct Rect_s0082_9bc0 { float left, top, right, bottom; };
struct ObjT1 {
virtual void m0();
virtual void m1();
virtual void m2();
virtual void* m3(unsigned id);
virtual ObjT1* m4();
virtual void m5();
virtual void m6();
virtual void m7();
virtual void m8();
virtual void m9();
virtual int m10();
virtual void m11();
virtual void m12();
virtual void m13();
virtual Rect_s0082_9bc0* m14();
virtual void m15();
virtual void m16();
virtual void m17();
virtual void m18();
virtual void m19();
virtual void m20();
virtual void m21();
virtual void m22();
virtual void m23();
virtual void m24();
virtual void m25();
virtual void m26();
virtual void m27(Rect_s0082_9bc0* area);
virtual void m28();
virtual void m29();
virtual void m30();
virtual void m31(int a, int b);
virtual void m32();
virtual void m33();
virtual void m34();
virtual void m35();
virtual void m36();
virtual void m37();
virtual void m38();
virtual void m39();
virtual void m40();
virtual void m41();
virtual void m42();
virtual void m43(int a);
virtual void m44();
virtual void m45();
virtual void m46();
virtual void m47();
virtual void m48();
virtual void m49();
virtual void m50();
virtual void m51();
virtual void m52();
virtual void m53();
virtual void m54(ObjT1*);
virtual void m55(ObjT1*);
virtual void m56();
virtual void m57();
virtual void m58();
virtual void m59();
virtual void m60();
virtual void m61();
virtual void m62();
virtual void m63();
virtual void m64();
virtual void m65(void* p);
virtual void m66(void* p);
virtual void m67();
};
struct ObjT2 {
virtual void m0();
virtual void m1();
virtual void m2();
virtual void m3();
virtual ObjT1* m4();
virtual void m5();
virtual void m6();
virtual void m7();
virtual void m8();
virtual void m9();
virtual void m10();
virtual void m11();
virtual void m12();
virtual void m13();
virtual Rect_s0082_9bc0* m14();
virtual void m15();
virtual void m16();
virtual void m17();
virtual void m18();
virtual void m19();
virtual void m20();
virtual void m21();
virtual void m22();
virtual void m23();
virtual void m24();
virtual void m25();
virtual void m26();
virtual void m27();
virtual void m28();
virtual void m29();
virtual void m30();
virtual void m31();
virtual void m32();
virtual void m33();
virtual void m34();
virtual void m35();
virtual void m36();
virtual void m37();
virtual void m38();
virtual void m39();
virtual void m40();
virtual void m41();
virtual void m42();
virtual void m43();
virtual void m44();
virtual void m45();
virtual void m46();
virtual void m47();
virtual void m48();
virtual void m49();
virtual void m50();
virtual void m51();
virtual void m52();
virtual void m53();
virtual void m54(ObjT1*);
virtual void m55(ObjT1*);
virtual void m56();
virtual void m57();
virtual void m58();
virtual void m59();
virtual void m60();
virtual void m61();
virtual void m62();
virtual void m63();
virtual void m64();
virtual void m65();
virtual void m66();
virtual void m67();
};
struct ScrollBar {
virtual void m0();
virtual void m1();
virtual void m2();
virtual void* m3(unsigned id);
virtual void m4();
virtual void m5();
virtual void m6();
virtual void m7();
virtual void m8();
virtual void m9(int value, int notify);
virtual int m10();
virtual void m11(int value, int notify);
virtual int m12();
virtual void m13(int value, int notify);
virtual int m14();
virtual void m15(int value, int notify);
virtual void m16();
virtual void m17();
virtual void m18();
virtual void m19();
virtual int m20();
virtual void m21();
virtual void m22();
virtual void m23();
virtual void m24();
};
struct ScrollHost { virtual float m0(float value); };
struct Msg {
  ObjT1* mSrc;       // +0x00
  ObjT1* mDst;       // +0x04
  unsigned mType;    // +0x08
  int mArg1;         // +0x0c
  int mArg2;         // +0x10
  int mArg3;         // +0x14
  union { int mArg4; ObjT1* mArg4p; };   // +0x18
};
struct IWinProc_ { virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); };
struct ISerializable_ { virtual void s0(); virtual void s1(); };
struct MultiHeapObject_ { };   // non-polymorphic base
struct CustomWinProc_ : IWinProc_, ISerializable_, MultiHeapObject_ {
  int mRefCount;               // +0x08
  CustomWinProc_();
  virtual ~CustomWinProc_();
};
struct IBiStateEffect_ { virtual void q0(); virtual void q1(); };
struct BiStateEffect_ : CustomWinProc_, IBiStateEffect_ {
  char pad10[0x50];            // +0x10 .. +0x5f
  BiStateEffect_();
  virtual ~BiStateEffect_();
};
struct IRotateEffect_ { virtual void r0(); virtual void r1(); };
struct V3 { float x, y, z; };
struct Mat {
  void RotateX(float a);
  void RotateY(float a);
  void RotateZ(float a);
  void RotateAxis(const V3& axis, float a);
};
struct RotateEffect_ : BiStateEffect_, IRotateEffect_ {
  float mRotAxisX, mRotAxisY, mRotAxisZ;   // +0x64 .. +0x6f
  float mRotAngle;                          // +0x70
  float mPad74;                             // +0x74
  RotateEffect_();
  virtual ~RotateEffect_();
};
struct cSPUIRotateEffect_ : RotateEffect_ {
  float mRotStartAngle;        // +0x78
  cSPUIRotateEffect_();
  virtual ~cSPUIRotateEffect_();
  void UpdateTransform(Mat* pMat, int defaultAxis, float t);
};
template<class T>
struct AutoRef_s0082_9bc0 {
  T* mpObject;
  AutoRef_s0082_9bc0() {}
  T* operator->() const { return mpObject; }
  AutoRef_s0082_9bc0(T* p) { mpObject = p; if (p) p->m0(); }
  AutoRef_s0082_9bc0(const AutoRef_s0082_9bc0<T>& o) { mpObject = o.mpObject; if (mpObject) mpObject->m0(); }
  ~AutoRef_s0082_9bc0() { if (mpObject) mpObject->m1(); }
  AutoRef_s0082_9bc0<T>& operator=(T* p) {
    T* pOld = mpObject;
    if (p != pOld) {
      if (p) p->m0();
      mpObject = p;
      if (pOld) pOld->m1();
    }
    return *this;
  }
};
template<class E>
struct Vec {
  E* mpBegin;    // +0x00
  E* mpEnd;      // +0x04
  E* mpEndCap;   // +0x08
  void Fun(uint32_t v);
  void erase(E* first, E* last);
  void DoInsertValue(E* pos, const E& value);
  void push_back(const E& value) {
    if (mpEnd < mpEndCap) {
      ::new ((void*)mpEnd) E(value);
      ++mpEnd;
    } else {
      DoInsertValue(mpEnd, value);
    }
  }
};
struct Handler {
  char pad0[0x10];
  uint32_t m10;                       // +0x10
  Vec<AutoRef_s0082_9bc0<ObjT1> > mVec;          // +0x14
  char pad20[0x8];                    // +0x20
  AutoRef_s0082_9bc0<ObjT1> mPtr28;              // +0x28
  AutoRef_s0082_9bc0<ObjT1> mPtr2c;              // +0x2c
  AutoRef_s0082_9bc0<ObjT1> mPtr30;              // +0x30
  void Func1(ObjT1* a, uint32_t b, ObjT1* c, uint32_t d);
  void Func2(ObjT1* a, ObjT1* b, ObjT1* c, uint32_t d);
  void Reset();
};
struct Key_s0082_9bc0 { int mId; uint32_t mType; uint32_t mGroup; };
struct SPUILayout : ObjT2 {
  uint32_t mRefCount;          // +0x04
  uint32_t mResourceKey[3];    // +0x08
  void* mpObjectCollection;    // +0x14
  SPUILayout();                               // 0x00810000
  bool Init(const Key_s0082_9bc0* key, bool a, int b);
  ObjT1* FindWindowByID(unsigned id, bool a);
  bool SetParentWin(ObjT1* parent, bool a, unsigned id);
  void Shutdown(int a);
};
void* operator new(unsigned int size, const char* name, int a, int b, int c, int d);
typedef ObjT1 Win;
struct SFV {
  volatile ObjT1* vtbl0;      // +0x00
  volatile ObjT1* vtbl1;      // +0x04
  uint32_t m8;       // +0x08
  SPUILayout* mLayout;  // +0x0c
  AutoRef_s0082_9bc0<ObjT1> m10;   // +0x10
  AutoRef_s0082_9bc0<ObjT1> m14;   // +0x14
  AutoRef_s0082_9bc0<ObjT1> m18;   // +0x18
  AutoRef_s0082_9bc0<ObjT1> m1c;   // +0x1c
  AutoRef_s0082_9bc0<ScrollBar> m20;   // +0x20
  ScrollHost* m24;   // +0x24
  float m28;         // +0x28
  float m2c;         // +0x2c
  float m30;         // +0x30
  float m34;         // +0x34
  float m38;         // +0x38
  uint32_t m3c;      // +0x3c
  uint32_t m40;      // +0x40
  uint32_t m44;      // +0x44

  SFV();
  __declspec(noinline) bool Create(int a, bool b, unsigned c);
  void Destroy();
  float GetScrollOffset();
  bool CreateFromName(const unsigned short* name, bool a, bool b);
  void Shutdown();
  void Update(bool force);
  bool OnMessage(Win* pSender, Msg* pMsg);
};
// ---- items of slice s00829bc0 end

// ---- items of slice s0082cd30 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int __cdecl wcscmp(const wchar_t*, const wchar_t*);
#pragma intrinsic(wcscmp)
struct RbNodeBase {
    RbNodeBase* mpNodeRight;    // +0x00
    RbNodeBase* mpNodeLeft;     // +0x04
    RbNodeBase* mpNodeParent;   // +0x08
    uint32_t mColor;            // +0x0c
};
template<class K, class V> struct RbNode : RbNodeBase {
    K first;                    // +0x10
    V second;                   // +0x14
};
template<class K, class V> struct RbPair {
    K first; V second;
    RbPair(const K& k, const V& v) : first(k), second() { (void)v; }
};
struct RbIterBase {
    RbNodeBase* mpNode;
    RbIterBase() : mpNode(0) {}
    RbIterBase(RbNodeBase* n) : mpNode(n) {}
    RbIterBase(const RbIterBase& o) : mpNode(o.mpNode) {}
};
struct ForceTag {
    bool mValue;
    ForceTag(bool v) : mValue(v) {}
};
template<class K, class V, class D> struct RbTreeMap {
    typedef RbNode<K, V> node_type;
    typedef RbPair<K, V> value_type;
    uint32_t mAllocator;        // +0x00
    RbNodeBase mAnchor;         // +0x04 (header node; root is mAnchor.mpNodeParent)
    uint32_t mnSize;            // +0x14
    uint32_t mCompare;          // +0x18

    RbIterBase lower_bound(const K& key)
    {
        node_type* pCurrent = static_cast<node_type*>(mAnchor.mpNodeParent);
        node_type* pRangeEnd = static_cast<node_type*>(&mAnchor);
        while (pCurrent) {
            if (!(pCurrent->first < key)) {
                pRangeEnd = pCurrent;
                pCurrent = static_cast<node_type*>(pCurrent->mpNodeLeft);
            } else {
                pCurrent = static_cast<node_type*>(pCurrent->mpNodeRight);
            }
        }
        return RbIterBase(pRangeEnd);
    }

    RbIterBase end() { return RbIterBase(&mAnchor); }

    RbIterBase insert(RbIterBase position, const value_type& value)
    {
        return static_cast<D*>(this)->DoInsertValue(position, value, ForceTag(false));
    }

    __forceinline V& operator[](const K& key)     // inlined into the Index wrappers below
    {
        RbIterBase itLower(lower_bound(key));
        if (itLower.mpNode == end().mpNode || key < static_cast<node_type*>(itLower.mpNode)->first) {
            itLower = insert(itLower, value_type(key, V()));
        }
        return static_cast<node_type*>(itLower.mpNode)->second;
    }
};
struct SerObject;
struct Slot16 {
    uint32_t a, b, c, d;
    Slot16() : a(0), b(0), c(0), d(0) {}
};
struct XmlIdMap : RbTreeMap<uint32_t, Slot16, XmlIdMap> {               // mXMLIDToObject
    // eastl::rbtree::DoInsertValue (thiscall, hidden return slot, iterator by value)
    RbIterBase DoInsertValue(RbIterBase position, const value_type& value, ForceTag bForceToLeft); // 0x0082CAC0
    Slot16& Index(const uint32_t& key);                                                            // 0x0082DAE0
};
struct ObjectBindingMap : RbTreeMap<SerObject*, int, ObjectBindingMap> { // mObjectBindings
    RbIterBase DoInsertValue(RbIterBase position, const value_type& value, ForceTag bForceToLeft); // 0x0082CB90
    int& Index(SerObject* const& key);                                                             // 0x0082DB80
};
struct Prop;
struct SerObject {              // Pool12 record
    const wchar_t* mpClassId;   // +0x00 "clsid"
    const wchar_t* mpAttr2;     // +0x04
    Prop* mpProps;              // +0x08
};
struct Value {                  // 0x20 bytes, allocated as an array by NewValues
    char mData[0x18];
    Prop* mpStruct;             // +0x18 (nested "struct": property list)
    SerObject* mpObject;        // +0x1c (nested "object")
};
struct Prop {                   // Pool16 record
    uint32_t mId;               // +0x00 "propid"
    uint16_t mType;             // +0x04
    uint16_t mCount;            // +0x06
    Value* mpValues;            // +0x08
    Prop* mpNext;               // +0x0c
};
// ---- items of slice s0082cd30 end

// ---- items of slice s0082dc00 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_d3d;            // 0x16f89d0
extern void* g_counter;        // 0x16f6e78
struct ImgHolder { int mDummy; void GetImageResource(void* r); };
struct LayerWinProc {
  char pad0[0x178];
  int mLayer;        // +0x178
  int mRefCount;     // +0x17c
  ImgHolder mImg[2]; // +0x180 (two 4-byte image-holder slots)
  float mFloats[0x10];  // +0x188
  bool SetLayer(int v);
  int ReleaseRef();
  void SetImage(unsigned i, void* r);
  float* FloatAt(int i);
  float GetFloat(unsigned i);
  void SetFloat(float v, unsigned i);
  void* AsInterface(int id);
  void CopyFloats(float* src, int start, int count);
  void SetImage2(unsigned* p, unsigned unused);
};
struct Stream {
  virtual void s0();
  virtual void AddRef();
  virtual void Release();
  Stream* Ctor(void*, void*, void*);          // 0x93c270
  void Set(int, float);                       // 0x93bb40
};
struct DispObj { void Dispose(); };           // 0x903120
struct Q4 { int a, b, c, d; };
struct LayoutMgr {
  Q4 q0, q1, q2, q3, q4, q5, q6, q7, q8, q9, q10, q11, q12, q13, q14, q15;
  int extra;
  void Ctor(void*, void*);                    // 0x82c810
  void Dtor();                                // 0x82c5a0
  bool ProcessTokens();                       // 0x82dc00
};
void* __cdecl NewMem(unsigned, void*, int, int, int, int);   // 0xf473a0
void __cdecl DeleteMem(void*);                                // 0xf47380
typedef void (__stdcall *DrawProc)(void*, void*, int*, int);
// ---- items of slice s0082dc00 end

// @ 0x00827fc0
void CPL::SetKey(const wchar_t* name, int uid)
{
  if (name) {
    Key k = {0, 0, 0};
    SPKeyFromName(&k, name, 0x510a95b, uid);
    mKey28 = uid;
    mKey24 = (int)k.a;
  }
}

// @ 0x00828020
void CPL::SetFlag(bool b)
{
  if (b != mbFlag) {
    mbFlag = b;
    IWindow* w = (IWindow*)mLayout.FindWindowByID(mRootWinId, 1);
    if (w) {
      ((void(__thiscall*)(void*, void*))(*(void***)w)[0x104 / 4])(w, this);
      ((void(__thiscall*)(void*, int, int))(*(void***)w)[0x7c / 4])(w, 1, mbFlag);
    }
  }
}

// @ 0x00828d40
cWrap::cWrap(IProv* prov, IRef* ref)
: m10(ref) {
  m14 = 0;
  IWin* w = prov->GetWindow();
  if (!w) w = F951d50();
  IText* t;
  if (w) t = w->QueryText(0x5234b49);
  else t = 0;
  mC = t;
}

// @ 0x00828df0
void C25b::Do(int arg)
{
  if (m10 && mObj) {
    mObj->v4();
    mObj->v5(arg, m10);
    mObj->v6();
  }
}

// @ 0x00828e30
cRender2D* __cdecl BeginRender(RenderContext* ctx, IProv* prov, cWrap** out)
{
  ctx->End2D();
  cWrap* w = new (g_wrapAllocName, 0, 0, 0, 0) cWrap(prov, 0);
  *out = w;
  ((IRef*)(*out))->AddRef();
  (*out)->m14 = ctx->Begin2D((*out)->mC.p);
  return (*out)->m14;
}

// @ 0x00828ef0
void __cdecl EndRender(RenderContext* ctx, cWrap* w)
{
  if (w && w->m14) {
    IRef* r = w->m14->F9557c0();
    w->m10 = r;
    w->m14 = 0;
  }
  ctx->End2D();
}

// @ 0x00829080
Rect* cPropLayout::GetRect(Rect* out)
{
  Rect tmp;
  Rect* p;
  if (m10) {
    m10->GetRect(out);
    return out;
  }
  IWin* w = m28.p;
  if (w) p = w->GetArea();
  else p = &tmp;
  *out = *p;
  return out;
}

// @ 0x008290e0
void C25c::Do(int arg)
{
  if (m10) {
    ((void(__thiscall*)(void*, int))(*(void***)m10)[2])(m10, arg);
  } else {
    void* o = m28;
    if (o) ((void(__thiscall*)(void*, int))(*(void***)o)[0x6c / 4])(o, arg);
  }
}

// @ 0x00829110
IRef*** __cdecl UninitCopyRefs(IRef*** res, IRef** first, IRef** last, IRef** dest)
{
  *res = dest;
  for (; first != last; ++first) {
    if (*res) {
      IRef* p = *first;
      **res = p;
      if (p) p->AddRef();
    }
    ++*res;
  }
  return res;
}

// @ 0x008294c0
void cPropLayout::SetRect2(const Rect* in, bool flag)
{
  Rect R;
  if (m30.p) {
    Pt o1;
    m30.p->ToScreen(&o1, *(const Pt*)&in->l);
    Pt o2;
    m28.p->GetParent()->ToLocal(&o2, o1);
    if (flag) {
      GetRect(&R);
      R = Rect(o2.x, o2.y, (R.r - R.l) + o2.x, (in->b - in->t) + o2.y);
    } else {
      R = Rect(o2.x, o2.y, (in->r - in->l) + o2.x, (in->b - in->t) + o2.y);
    }
  } else {
    if (!flag) {
      if (m10) {
        m10->SetRect(in);
        return;
      }
      if (m28.p) m28.p->SetArea(in);
      return;
    }
    GetRect(&R);
    R = Rect(in->l, in->t, (R.r - R.l) + in->l, in->b);
  }
  if (m10) {
    m10->SetRect(&R);
    return;
  }
  if (m28.p) m28.p->SetArea(&R);
}

// @ 0x00829690
Rect* cPropLayout::GetRectLocal(Rect* out)
{
  if (m30.p) {
    Rect r;
    GetRect(&r);
    Pt o1;
    m28.p->GetParent()->ToScreen(&o1, TL(r));
    Pt o2;
    IWin* w30 = m30.p;
    w30->ToLocal(&o2, o1);
    out->l = o2.x;
    out->t = o2.y;
    out->r = (r.r - r.l) + o2.x;
    out->b = (r.b - r.t) + o2.y;
    return out;
  }
  GetRect(out);
  return out;
}

// @ 0x00829770
cPropLayout::cPropLayout()
: mBusy(false), mMoved(false), mPending(false), mOffset(0.0f), m10(0) {}

// @ 0x00829ad0
RefVec& RefVec::operator=(const RefVec& x)
{
  if (&x != this) {
    const unsigned n = (unsigned)(x.mpEnd - x.mpBegin);
    if (n > (unsigned)(mpCap - mpBegin)) {
      IRef** pNew = DoAllocateAndCopy(n, x.mpBegin, x.mpEnd);
      DoDestroy(mpBegin, mpEnd);
      if (mpBegin && ((int*)mpBegin)[-1] != 0) OperatorDeleteRaw(mpBegin);
      mpCap = pNew + n;
      mpEnd = pNew + n;
      mpBegin = pNew;
      return *this;
    }
    unsigned sz = (unsigned)(mpEnd - mpBegin);
    if (n > sz) {
      CopyRefsRange(x.mpBegin, x.mpBegin + sz, mpBegin);
      IRef** res;
      UninitCopyRefs5(&res, x.mpBegin + (mpEnd - mpBegin), x.mpEnd, mpEnd, &x);
      mpEnd = mpBegin + n;
      return *this;
    }
    IRef** p = CopyRefsRange(x.mpBegin, x.mpEnd, mpBegin);
    DoDestroy(p, mpEnd);
    mpEnd = mpBegin + n;
  }
  return *this;
}

// @ 0x00829bc0
void Handler::Func1(ObjT1* a, uint32_t b, ObjT1* c, uint32_t d)
{
  mPtr28 = a;
  mVec.Fun(b);
  mPtr2c = c;
  m10 = d;
}

// @ 0x00829c50
void Handler::Func2(ObjT1* a, ObjT1* b, ObjT1* c, uint32_t d)
{
  mPtr28 = a;
  mVec.erase(mVec.mpBegin, mVec.mpEnd);
  mVec.push_back(b);
  mPtr2c = c;
  m10 = d;
}

// @ 0x00829d30
void Handler::Reset()
{
  if (mPtr30.mpObject) {
    ObjT1* pObj = (ObjT1*)mPtr28.mpObject->m4();
    if (pObj != mPtr30.mpObject) {
      pObj->m55(mPtr28.mpObject);
      mPtr30.mpObject->m54(mPtr28.mpObject);
      mPtr30 = (ObjT1*)0;
    }
  }
  m10 = 0;
  mPtr28 = (ObjT1*)0;
  mVec.erase(mVec.mpBegin, mVec.mpEnd);
  mPtr2c = (ObjT1*)0;
  mPtr30 = (ObjT1*)0;
}

// @ 0x00829dd0
cSPUIRotateEffect_::cSPUIRotateEffect_()
: mRotStartAngle(0.0f) {
}

// @ 0x00829f30
void cSPUIRotateEffect_::UpdateTransform(Mat* pMat, int defaultAxis, float t)
{
  int n = 0;
  int axis = defaultAxis;
  if (fabs(mRotAxisX) > kRotEps) { axis = 0; n = 1; }
  if (fabs(mRotAxisY) > kRotEps) { axis = 1; ++n; }
  if (fabs(mRotAxisZ) > kRotEps) { axis = 2; ++n; }
  if (n > 1) axis = 3;
  if (n <= 0) return;
  float a = (mRotAngle * t + mRotStartAngle) * kDeg2Rad;
  switch (axis) {
    case 0: pMat->RotateX(a); return;
    case 1: pMat->RotateY(a); return;
    case 2: pMat->RotateZ(a); return;
    case 3: pMat->RotateAxis(*(V3*)&mRotAxisX, a); return;
  }
}

// @ 0x0082a0d0
void SFV::Destroy()
{
  if (m20.mpObject) m20.mpObject->m1();
  if (m1c.mpObject) m1c.mpObject->m1();
  if (m18.mpObject) m18.mpObject->m1();
  if (m14.mpObject) m14.mpObject->m1();
  if (m10.mpObject) m10.mpObject->m1();
  if (mLayout) ((ObjT2*)mLayout)->m2();
  vtbl1 = (ObjT1*)&g_sfvBase1Vtbl;
  vtbl0 = (ObjT1*)&g_sfvBase0Vtbl;
}

// @ 0x0082dae0
Slot16& XmlIdMap::Index(const uint32_t& key)
{ return (*this)[key]; }

// @ 0x0082db80
int& ObjectBindingMap::Index(SerObject* const& key)
{ return (*this)[key]; }

// @ 0x0082dc00
void LayerWinProcInit()
{
}

// @ 0x0082e1d0
bool __cdecl LayerProc1(char* p)
{
  if (*(void**)(p + 0x1c)) {
    void* m = NewMem(0x24, (void*)0x13f6b3c, 0, 0, 0, 0);
    Stream* s = m ? ((Stream*)m)->Ctor(0, 0, (void*)0x13ebacc) : 0;
    if (s) s->AddRef();
    s->Set(1, 1.0f);
    LayoutMgr mgr;
    mgr.Ctor(s, *(void**)(p + 0x1c));
    if (!mgr.ProcessTokens()) {
      mgr.Dtor();
      if (s) s->Release();
      return false;
    }
    s->Set(1, 0.0f);
    mgr.Dtor();
    Stream* old = *(Stream**)(p + 0x18);
    if (s != old) {
      if (s) s->AddRef();
      *(Stream**)(p + 0x18) = s;
      if (old) old->Release();
    }
    DispObj* q = *(DispObj**)(p + 0x20);
    *(void**)(p + 0x1c) = 0;
    if (q) {
      q->Dispose();
      DeleteMem(q);
    }
    *(void**)(p + 0x20) = 0;
    if (s) s->Release();
    return true;
  }
  return false;
}

// @ 0x0082e300
void LayerProcDraw(void* a1, void* a2, int a3)
{
  (void)a2;
  int* c = (int*)g_counter;
  void** vt = *(void***)g_d3d;
  if (a3)
    ((DrawProc)vt[0x178 / 4])(g_d3d, a1, c + 1, c[0] * 6);
  else
    ((DrawProc)vt[0x1b4 / 4])(g_d3d, a1, c + 1, c[0] * 6);
}

// @ 0x0082e340
void LayerWinProc::SetFloat(float v, unsigned i)
{
  if (i < 0x10) mFloats[i] = v;
}

// @ 0x0082e360
float LayerWinProc::GetFloat(unsigned i)
{
  if (i < 0x10) return mFloats[i];
  return 0.0f;
}

// @ 0x0082e3f0
float* LayerWinProc::FloatAt(int i)
{
  return &mFloats[i];
}
