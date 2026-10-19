// src/game/Spui/SPUIPropertyLayout.cpp -- migrated from slice(s) s00827bf0 by tools/migrate/rewrite.py
// Object file: Spui/SPUIPropertyLayout.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "cSPUIPropertyLayout.h"
#include "EA/Stopwatch.h"
#include "EA/Variant.h"
#include "cSPUILayout.h"

// ---- items of slice s00827bf0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cSPUILayout_s0082_7bf0 {
  virtual int AddRef();       // slot 0
  virtual int Release();      // slot 4
  int mRefCount;              // +0x4
  void* mpObject;             // +0x8
  void* FindWindowByID(int id, int flag);   // __thiscall (callee pops) 0x008105b0
};
struct Stopwatch {
  char pad0[0x14];            // +0x0
  float mUnitsPerSecond;      // +0x14
  __int64 GetElapsedTime();
};
struct IWindow;
struct IRefThing { virtual int AddRef(); virtual int Release(); };
struct Variant {
  char pad[0x10];
  unsigned short mFlags;
  unsigned short mTypeId;
  Variant() { mFlags = 0; mTypeId = 0; }
  Variant& operator=(const Variant&);
  void Destruct(int);
};
struct CPL {
  virtual unsigned int GetEventMask();
  virtual bool DoMessage(int, void*);
  char pad0[8];               // +0x4 .. +0xb
  cSPUILayout_s0082_7bf0 mLayout;        // +0xc
  char pad18[0xc];            // +0x18 .. +0x23
  int mKey24;                 // +0x24
  int mKey28;                 // +0x28
  char pad2c[0x1c];           // +0x2c .. +0x47
  int mRootWinId;             // +0x48
  float mInterval;            // +0x4c
  Stopwatch mStopwatch;       // +0x50
  float mTime;                // +0x68
  float mOffsetX;             // +0x6c
  float mOffsetY;             // +0x70
  bool mbFlag;                // +0x74

  void SetKey(const wchar_t* name, int uid);
  void SetFlag(bool b);
  void* GetRootWindow();
  void SetPositionAndOffset(float x, float y, float offX, float offY);
  void ForceVisibleLocation();
};
struct Elem {
  unsigned int first;      // +0x00
  void* mpObject;          // +0x04
  Variant mVariant;        // +0x08
  int mLast;               // +0x1c
  Elem(const Elem& o);
  Elem& operator=(const Elem& o);
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
void* CPL::GetRootWindow()
{
  return mLayout.FindWindowByID(mRootWinId, 1);
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
void __stdcall ElemDoDestroyValues(Elem* first, Elem* last)
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
