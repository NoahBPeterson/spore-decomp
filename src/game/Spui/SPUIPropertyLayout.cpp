// src/game/Spui/SPUIPropertyLayout.cpp -- migrated from slice(s) s00828c30, s00827bf0 by tools/migrate/rewrite.py
// Object file: Spui/SPUIPropertyLayout.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "cSPUIPropertyLayout.h"
#include "SP/cString.h"
#include "EA/Stopwatch.h"
#include "EA/Variant.h"

// unnamed retail callees and globals (address in the comment)
extern float g_PropDefaultValue;                 // 0x015d1168 (default "value" variant)
extern unsigned* GetDefaultPropValue();                          // 0x0068a2e0
extern void FormatFloat(double v, char* dst, unsigned size, const wchar_t* fmt); // 0x00881ea0
#include <new>
#include <intrin.h>
#include "cSPUILayout.h"
#include "EA/UTFWin/RenderContext.h"

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
  virtual bool func24h();  // +0x24
};
WinMgr* WindowManager();                         // 0x0067caa0
Rect2* FUN_00808370(Rect2* out, UIObj* w, int flag);   // 0x00808370 (cdecl)
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
extern float g_PropDefaultValue;                 // 0x015d1168 (default "value" variant)
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
static void* VarData(const Variant* v) {
  if (v->mFlags & 0x30) return *(void**)(void*)v;
  return v->mTypeId ? (void*)v : 0;
}
struct EStringView { const char* mpBegin; const char* mpEnd; };
struct EString {
  void* mpBegin;   // +0x0
  void* mpEnd;     // +0x4
  void* mpCap;     // +0x8
  EString();                       // 0x006b5060
  ~EString();                      // 0x006b5240
  const char* c_str();             // 0x006b55c0
};
extern void StringAssign(const EStringView* src, EString* dst);  // 0x006b56d0
extern const EStringView* GetEmptyStringView();                  // 0x006bb660
extern unsigned* GetDefaultPropValue();                          // 0x0068a2e0
extern void FormatFloat(double v, char* dst, unsigned size, const wchar_t* fmt); // 0x00881ea0
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

// unnamed retail callees and globals that name local stubs (address in the comment)
extern void StringAssign(const EStringView* src, EString* dst);  // 0x006b56d0
extern const EStringView* GetEmptyStringView();                  // 0x006bb660

// callees this slice defines outside this object (rewrite.py held_callee_protos)
Elem* ElemDestroyRange(Elem* first, Elem* last, Elem* dst);  // 0x00828350 (stays in the slice: not this object's)

// ---- items of slice s00828c30 begin (TODO(rewrite): local stubs, replace by canonical classes)
class IRef {
public:
    virtual void AddRef();  // slot 0 +0x0
    virtual void Release();  // slot 1 +0x4
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
struct Variant_s0082_8c30 {
  char data[0x10];
  unsigned short mFlags;
  unsigned short mTypeId;
  Variant_s0082_8c30() : mFlags(0) {}               // the original leaves mTypeId unset
  ~Variant_s0082_8c30() { if (mFlags & 4) Destruct(0); }
  Variant_s0082_8c30& operator=(const Variant_s0082_8c30& o);   // 0x00542b80
  void Destruct(int);                     // 0x0093db80
};
struct VarSlot {
  AutoRef<IRef> p;
  Variant_s0082_8c30 v;
  union {
    unsigned extra;
    struct { unsigned short extraLo, extraHi; };
  };
  VarSlot() { extraHi = 0; }             // only the high half is cleared
};
struct MapNode {
  unsigned key;
  IRef* p;
  Variant_s0082_8c30 v;
  unsigned flags;
};
struct MapPair {      // value_type passed to Insert (copied into the vector)
  unsigned key;
  VarSlot s;
};
struct MapVec {       // sorted vector of MapNode values
  MapNode* mBegin;    // +0x2c
  MapNode* mEnd;      // +0x30
  MapNode* Insert(MapNode* pos, const MapPair* value);   // 0x00828b80
};
class cEntryMap {
 public:
  char pad0[0x2c];
  MapVec mVec;        // +0x2c
  char pad34[0x40 - 0x34];
  bool mFlag;         // +0x40
  bool Set(unsigned key, const Variant_s0082_8c30* value, unsigned flags, IRef* ref);
};
MapNode* LowerBound(MapNode* first, MapNode* last, unsigned* key, bool flag);   // 0x00d01210
// ---- items of slice s00828c30 end

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

// @ 0x00828740
void CPL::func20h()
{
  for (Elem* it = mProperties.mpBegin; it != mProperties.mpEnd; ++it) {
    if ((it->mLast & 5) == 0) continue;
    it->mLast &= ~4;
    Variant tmp;
    Variant* src = &it->mVariant;
    if (it->mVariant.mTypeId == 0x1d00) {
      void* obj = VarData(&it->mVariant);
      bool (*fn)(Variant*, void*) = obj ? *(bool (**)(Variant*, void*))obj : 0;
      if (!fn) continue;
      if (!fn(&tmp, *(void**)((char*)obj + 4))) continue;
      src = &tmp;
    }
    IWindow* w = (IWindow*)mLayout.FindWindowByID((int)it->first, 1);
    if (!w) continue;
    if (src->mTypeId > 5 && src->mTypeId < 0xf) {
      Variant conv;
      conv.mFlags = 2;
      conv.mTypeId = 0xd;
      conv = *src;
      const void* pv = (conv.mTypeId == 0xd || conv.mTypeId == 0x10)
                           ? VarData(&conv)
                           : (const void*)&g_PropDefaultValue;
      float val = *(const float*)pv;
      if (conv.mFlags & 4) conv.Destruct(0);
      IWindow* bar = (IWindow*)w->Cast(0x10edf11);
      if ((it->mLast & 2) && bar) {
        float c = val;
        if (c > 100.0f) c = 100.0f;
        else if (c < 0.0f) c = 0.0f;
        ((void(__thiscall*)(IWindow*, float))((*(void***)bar)[1]))(bar, c);
      } else {
        char buf[0x20];
        FormatFloat((double)val, buf, 0x20, L"%-F%-p");
        w->Set80((unsigned)(size_t)buf);
      }
    } else if (src->mTypeId == 0x22) {
      EString s;
      const void* pv = (src->mTypeId == 0x22 || src->mTypeId == 0x10)
                           ? VarData(src)
                           : (const void*)GetEmptyStringView();
      StringAssign((const EStringView*)pv, &s);
      w->Set80((unsigned)(size_t)s.c_str());
      s.~EString();
    } else {
      const void* pv = (src->mTypeId == 0x13 || src->mTypeId == 0x10)
                           ? VarData(src)
                           : (const void*)GetDefaultPropValue();
      w->Set80(*(const unsigned*)pv);
    }
  }
  Stopwatch& sw = mStopwatch;
  sw.Reset();
  mTime = (float)sw.GetElapsedTime() * sw.mUnitsPerSecond;
}

// @ 0x00828a50
Elem* ElemVec::insert(Elem* position, const Elem& value)
{
  if (mpEnd != mpCapacity) {
    Elem* pv = (Elem*)&value;
    if (pv >= position && pv < mpEnd) pv = pv + 1;
    if (mpEnd) ::new ((void*)mpEnd) Elem(*(mpEnd - 1));
    ElemCopyBackward(position, mpEnd - 1, mpEnd);
    *position = *pv;
    ++mpEnd;
  } else {
    unsigned n = (unsigned)(mpEnd - mpBegin);
    unsigned newCap = (n == 0) ? 1u : n * 2;
    Elem* pNew = 0;
    if (newCap) {
      pNew = (Elem*)((void* (*)(unsigned, void*, int, int, void*, int))0xf473a0)(
          newCap * 0x20, (void*)0x13f6b3c, 0, 0, (void*)0x13ebb38, 0xd1);
    }
    Elem* pEnd = ElemMoveStart(mpBegin, position, pNew);
    ElemDestroyRange(mpBegin, position, pNew);
    if (pEnd) ::new ((void*)pEnd) Elem(value);
    Elem* q = ElemMoveStart(position, mpEnd, pEnd + 1);
    ElemDestroyRange(position, mpEnd, pEnd + 1);
    if (mpBegin) ((void (*)(void*))0xf47380)(mpBegin);
    mpBegin = pNew;
    mpEnd = q;
    mpCapacity = pNew + newCap;
  }
  return position;
}

// @ 0x00828be0
bool CPL::func24h()
{
  if (mbInitialized) {
    mLayout.Shutdown(1);
    mProperties.clear();
  }
  mbInitialized = false;
  return true;
}

// @ 0x00828c30
bool cEntryMap::Set(unsigned key, const Variant_s0082_8c30* value, unsigned flags, IRef* ref)
{
  MapNode* it;
  {
    VarSlot a;
    MapPair b;
    b.key = key;
    b.s.v = a.v;
    b.s.extra = a.extra;
    MapVec& vec = mVec;
    MapNode* end = vec.mEnd;
    it = LowerBound(vec.mBegin, end, &b.key, mFlag);
    if (it == end || b.key < it->key)
      it = vec.Insert(it, &b);
  }
  MapNode* n = it;
  n->v = *value;
  n->flags = flags | 4;
  IRef* old = n->p;
  if (ref != old) {
    if (ref) ref->AddRef();
    n->p = ref;
    if (old) old->Release();
  }
  return true;
}
