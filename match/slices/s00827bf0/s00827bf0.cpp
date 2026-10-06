// Slice s00827bf0 -- SP::cSPUIPropertyLayout methods + vector_map element helpers.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

struct Key { unsigned int a, b, c; };
void SPKeyFromName(Key* out, const wchar_t* name, unsigned int ns, int id);

// ---- layout / window helpers --------------------------------------------
struct cSPUILayout {
  virtual int AddRef();       // slot 0
  virtual int Release();      // slot 4
  int mRefCount;              // +0x4
  void* mpObject;             // +0x8
  void* FindWindowByID(int id, int flag);   // __thiscall (callee pops)
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

// ===========================================================================
// retail cSPUIPropertyLayout (offsets confirmed from disassembly)
// ===========================================================================
struct CPL {
  virtual unsigned int GetEventMask();
  virtual bool DoMessage(int, void*);
  char pad0[8];               // +0x4 .. +0xb
  cSPUILayout mLayout;        // +0xc
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

// ===========================================================================
// 00827fc0
// ===========================================================================
void CPL::SetKey(const wchar_t* name, int uid) {
  if (name) {
    Key k = {0, 0, 0};
    SPKeyFromName(&k, name, 0x510a95b, uid);
    mKey28 = uid;
    mKey24 = (int)k.a;
  }
}

// ===========================================================================
// 00828020
// ===========================================================================
void CPL::SetFlag(bool b) {
  if (b != mbFlag) {
    mbFlag = b;
    IWindow* w = (IWindow*)mLayout.FindWindowByID(mRootWinId, 1);
    if (w) {
      ((void(__thiscall*)(void*, void*))(*(void***)w)[0x104 / 4])(w, this);
      ((void(__thiscall*)(void*, int, int))(*(void***)w)[0x7c / 4])(w, 1, mbFlag);
    }
  }
}

// ===========================================================================
// 00828070  cSPUIPropertyLayout::GetEventMask
// ===========================================================================
unsigned int CPL::GetEventMask() {
  return mbFlag ? 2 : 0;
}

// ===========================================================================
// 00828080  cSPUIPropertyLayout::DoMessage
// ===========================================================================
bool CPL::DoMessage(int a, void* b) {
  if (*(int*)((char*)b + 8) == 0xc) {
    if (mTime > mInterval) {
      ((void(__thiscall*)(void*))(*(void***)this)[0x20 / 4])(this);
    }
    Stopwatch& sw = mStopwatch;
    mTime = (float)sw.GetElapsedTime() * sw.mUnitsPerSecond;
  }
  return false;
}

// ===========================================================================
// 00828100  cSPUIPropertyLayout::GetRootWindow
// ===========================================================================
void* CPL::GetRootWindow() {
  return mLayout.FindWindowByID(mRootWinId, 1);
}

// ===========================================================================
// 008283a0  cSPUIPropertyLayout::SetPositionAndOffset
// ===========================================================================
void CPL::SetPositionAndOffset(float x, float y, float offX, float offY) {
  mOffsetX = offX;
  mOffsetY = offY;
  IWindow* w = (IWindow*)mLayout.FindWindowByID(mRootWinId, 1);
  if (w) {
    ((void(__thiscall*)(void*, float, float))(*(void***)w)[0x70 / 4])(w, x + offX, y + offY);
    ForceVisibleLocation();
  }
}

// ===========================================================================
// vector_map element helpers (eastl::pair<unsigned int, cProperty>, 0x20 bytes)
// These are complete but not byte-exact (instruction scheduling of the inlined
// Variant reset differs); see nonmatching.txt.
// ===========================================================================
struct Elem {
  unsigned int first;      // +0x00
  void* mpObject;          // +0x04
  Variant mVariant;        // +0x08
  int mLast;               // +0x1c
  Elem(const Elem& o);
  Elem& operator=(const Elem& o);
};

// 00828450 pair element copy-ctor
Elem::Elem(const Elem& o) : first(o.first), mpObject(o.mpObject) {
  if (mpObject) ((IRefThing*)mpObject)->AddRef();
  mVariant = o.mVariant;
  mLast = o.mLast;
}

// 008284a0 pair element operator=
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

// 00828410 vector::DoDestroyValues
void __stdcall ElemDoDestroyValues(Elem* first, Elem* last) {
  for (; first < last; ++first) {
    Variant* v = &first->mVariant;
    if (first->mVariant.mFlags & 4) v->Destruct(0);
    IRefThing* p = (IRefThing*)first->mpObject;
    if (p) p->Release();
  }
}

// 00828350 destroy-source / advance-dest range helper
Elem* ElemDestroyRange(Elem* first, Elem* last, Elem* dst) {
  while (first != last) {
    Variant* v = &first->mVariant;
    if (first->mVariant.mFlags & 4) v->Destruct(0);
    IRefThing* p = (IRefThing*)first->mpObject;
    if (p) p->Release();
    ++first;
    ++dst;
  }
  return dst;
}
