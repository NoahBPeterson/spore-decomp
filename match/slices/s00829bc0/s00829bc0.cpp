// Slice s00829bc0 (batch w2g7, slice 26).
// UTFWin / SPUIHelpers region: SPUIRotateEffect, UI::ScrollFrameVertical and
// the small SPUIHelpers scroll-frame helpers.  Stub class layouts use field offsets
// verified against the disassembly; virtual slots are named by their byte offset/4.
#include "types.h"
#include <new>
#include <math.h>
#include <string.h>
#include <intrin.h>

extern char g_sfvVtbl0;        // 0x141a0f4
extern char g_sfvVtbl1;        // 0x141a0e4
extern char g_sfvBase0Vtbl;    // 0x13eb938
extern char g_sfvBase1Vtbl;    // 0x13ec458

struct Rect { float left, top, right, bottom; };

// Generic COM-ish object: m0 = AddRef (+0x00), m1 = Release (+0x04).
// Slot N lives at vtable offset N*4; only the slots this slice reaches are typed.
struct ObjT1 {
  virtual void m0(); virtual void m1(); virtual void m2(); virtual void* m3(unsigned id); virtual ObjT1* m4(); virtual void m5(); virtual void m6(); virtual void m7();
  virtual void m8(); virtual void m9(); virtual int m10(); virtual void m11(); virtual void m12(); virtual void m13(); virtual Rect* m14(); virtual void m15();
  virtual void m16(); virtual void m17(); virtual void m18(); virtual void m19(); virtual void m20(); virtual void m21(); virtual void m22(); virtual void m23();
  virtual void m24(); virtual void m25(); virtual void m26(); virtual void m27(Rect* area); virtual void m28(); virtual void m29(); virtual void m30(); virtual void m31(int a, int b);
  virtual void m32(); virtual void m33(); virtual void m34(); virtual void m35(); virtual void m36(); virtual void m37(); virtual void m38(); virtual void m39();
  virtual void m40(); virtual void m41(); virtual void m42(); virtual void m43(int a); virtual void m44(); virtual void m45(); virtual void m46(); virtual void m47();
  virtual void m48(); virtual void m49(); virtual void m50(); virtual void m51(); virtual void m52(); virtual void m53(); virtual void m54(ObjT1*); virtual void m55(ObjT1*);
  virtual void m56(); virtual void m57(); virtual void m58(); virtual void m59(); virtual void m60(); virtual void m61(); virtual void m62(); virtual void m63();
  virtual void m64(); virtual void m65(void* p); virtual void m66(void* p); virtual void m67();
};

// Asset/com interface whose AddRef is at +0x04 and Release at +0x08.
struct ObjT2 {
  virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3(); virtual ObjT1* m4(); virtual void m5(); virtual void m6(); virtual void m7();
  virtual void m8(); virtual void m9(); virtual void m10(); virtual void m11(); virtual void m12(); virtual void m13(); virtual Rect* m14(); virtual void m15();
  virtual void m16(); virtual void m17(); virtual void m18(); virtual void m19(); virtual void m20(); virtual void m21(); virtual void m22(); virtual void m23();
  virtual void m24(); virtual void m25(); virtual void m26(); virtual void m27(); virtual void m28(); virtual void m29(); virtual void m30(); virtual void m31();
  virtual void m32(); virtual void m33(); virtual void m34(); virtual void m35(); virtual void m36(); virtual void m37(); virtual void m38(); virtual void m39();
  virtual void m40(); virtual void m41(); virtual void m42(); virtual void m43(); virtual void m44(); virtual void m45(); virtual void m46(); virtual void m47();
  virtual void m48(); virtual void m49(); virtual void m50(); virtual void m51(); virtual void m52(); virtual void m53(); virtual void m54(ObjT1*); virtual void m55(ObjT1*);
  virtual void m56(); virtual void m57(); virtual void m58(); virtual void m59(); virtual void m60(); virtual void m61(); virtual void m62(); virtual void m63();
  virtual void m64(); virtual void m65(); virtual void m66(); virtual void m67();
};

// EA::UTFWinControls::IWinScrollbar, acquired through IWindow::AsInterface(0x2ef0c885).
// Slot numbering follows the vtable byte offset / 4 (m0 = AddRef, m1 = Release, ...).
struct ScrollBar {
  virtual void m0(); virtual void m1(); virtual void m2(); virtual void* m3(unsigned id);
  virtual void m4(); virtual void m5(); virtual void m6(); virtual void m7();
  virtual void m8(); virtual void m9(int value, int notify); virtual int m10(); virtual void m11(int value, int notify);
  virtual int m12(); virtual void m13(int value, int notify); virtual int m14(); virtual void m15(int value, int notify);
  virtual void m16(); virtual void m17(); virtual void m18(); virtual void m19(); virtual int m20();
  virtual void m21(); virtual void m22(); virtual void m23(); virtual void m24();
};

// Handler interface stored at SFV::m24; slot 0 rescales a scroll extent.
struct ScrollHost { virtual float m0(float value); };

// EA::UTFWin::Message (0x1c bytes); mArgs union starts at +0x0c.
struct Msg {
  ObjT1* mSrc;       // +0x00
  ObjT1* mDst;       // +0x04
  unsigned mType;    // +0x08
  int mArg1;         // +0x0c
  int mArg2;         // +0x10
  int mArg3;         // +0x14
  union { int mArg4; ObjT1* mArg4p; };   // +0x18
};

// ---- UTFWinControls effect hierarchy (from the 2008 dev-build PDB) ----
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

extern const float kRotEps;    // 0x1419f4c
extern const float kDeg2Rad;   // 0x1419f1c
struct cSPUIRotateEffect_ : RotateEffect_ {
  float mRotStartAngle;        // +0x78
  cSPUIRotateEffect_();
  virtual ~cSPUIRotateEffect_();
  void UpdateTransform(Mat* pMat, int defaultAxis, float t);
};

// @ 0x00829DD0
cSPUIRotateEffect_::cSPUIRotateEffect_() : mRotStartAngle(0.0f) {
}

// @ 0x00829F30
void cSPUIRotateEffect_::UpdateTransform(Mat* pMat, int defaultAxis, float t) {
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

// Ref-counting smart pointer (4 bytes).  Adds a reference before dropping the old one.
template<class T>
struct AutoRef {
  T* mpObject;
  AutoRef() {}
  T* operator->() const { return mpObject; }
  AutoRef(T* p) { mpObject = p; if (p) p->m0(); }
  AutoRef(const AutoRef<T>& o) { mpObject = o.mpObject; if (mpObject) mpObject->m0(); }
  ~AutoRef() { if (mpObject) mpObject->m1(); }
  AutoRef<T>& operator=(T* p) {
    T* pOld = mpObject;
    if (p != pOld) {
      if (p) p->m0();
      mpObject = p;
      if (pOld) pOld->m1();
    }
    return *this;
  }
};

// EASTL-like vector of ref-counted pointers.
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

// Handler class owning the ref-counted members and the vector (functions 0x829bc0..0x829d30).
struct Handler {
  char pad0[0x10];
  uint32_t m10;                       // +0x10
  Vec<AutoRef<ObjT1> > mVec;          // +0x14
  char pad20[0x8];                    // +0x20
  AutoRef<ObjT1> mPtr28;              // +0x28
  AutoRef<ObjT1> mPtr2c;              // +0x2c
  AutoRef<ObjT1> mPtr30;              // +0x30
  void Func1(ObjT1* a, uint32_t b, ObjT1* c, uint32_t d);
  void Func2(ObjT1* a, ObjT1* b, ObjT1* c, uint32_t d);
  void Reset();
};

// @ 0x00829BC0
void Handler::Func1(ObjT1* a, uint32_t b, ObjT1* c, uint32_t d) {
  mPtr28 = a;
  mVec.Fun(b);
  mPtr2c = c;
  m10 = d;
}

// @ 0x00829C50
void Handler::Func2(ObjT1* a, ObjT1* b, ObjT1* c, uint32_t d) {
  mPtr28 = a;
  mVec.erase(mVec.mpBegin, mVec.mpEnd);
  mVec.push_back(b);
  mPtr2c = c;
  m10 = d;
}

// @ 0x00829D30
void Handler::Reset() {
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

// ---------------------------------------------------------------------------

// Small vector adapter used by SPUIHelpers scroll-frame helpers (0x82aa50..0x82abd0).
struct Node { Node* pNext; uint32_t e; uint32_t f; };
struct Cursor {
  char pad0[4];
  uint32_t mLo;    // +4
  uint32_t mHi;    // +8
  uint32_t mA;     // +0xc
  uint32_t mB;     // +0x10
  char pad14[0xc];
  Node* mpNode;    // +0x20
  void Other(uint32_t v);
  void Set(uint32_t v);
  void Next();
};
struct CursorRef {
  Cursor* mpCursor;   // +0
  void Next();
};

// @ 0x0082AA50
void Cursor::Set(uint32_t v) {
  if (v > mLo && v < mHi) { mA = v; mB = v; return; }
  Other(v);
}

// @ 0x0082AA70
void Cursor::Next() {
  Node* p = mpNode;
  if (!p) return;
  uint32_t e = p->e, f = p->f;
  mpNode = p->pNext;
  if (e > mLo && e < mHi) { mB = e; mB = f; mA = e; return; }
  Other(e);
  mB = f;
}

// @ 0x0082AAC0
void CursorRef::Next() {
  Cursor* s = mpCursor;
  Node* p = s->mpNode;
  if (!p) return;
  uint32_t e = p->e, f = p->f;
  s->mpNode = p->pNext;
  if (e > s->mLo && e < s->mHi) { s->mB = e; s->mB = f; s->mA = e; return; }
  s->Other(e);
  s->mB = f;
}

// @ 0x0082AB00
int RangeCheck(int a, int b) {
  while (a > b) { int t = a; a = b; b = t; }
  if ((unsigned)(a - 3) <= 3 && b - a == 4) return 1;
  return 0;
}

// ---- token table lookup (0x82ab40) ----
struct TableEntry { const unsigned short* mpName; uint32_t mValue; };
struct Table {
  char pad0[4];
  int m4;              // +4
  char pad8[0xc];
  TableEntry* mEntries;  // +0x14
  int mCount;            // +0x18
};
static int CmpStr16(const unsigned short* a, const unsigned short* b) {
  while (*a == *b) { if (!*a) return 0; ++a; ++b; }
  return *a < *b ? -1 : 1;
}

// @ 0x0082AB40
uint32_t __stdcall TableLookup(Table* t, const unsigned short* key) {
  if (t->m4 != 1) return 0;
  for (int i = 0; i < t->mCount; ++i) {
    if (CmpStr16(t->mEntries[i].mpName, key) == 0) return t->mEntries[i].mValue;
  }
  return 0;
}

// ---- byte allocator (0x82abd0) ----
struct Blk {
  Blk* pNext;         // +0x00
  uint32_t mTag;      // +0x04
  uint32_t mPad8;     // +0x08
  const void* mData;  // +0x0c
  uint32_t mPad10;    // +0x10
  uint32_t mCount;    // +0x14
};
struct StackAllocator {
  char pad0[0x08];
  uint32_t mCap;    // +0x08
  uint32_t mBase;   // +0x0c
  uint32_t mCur;    // +0x10
  bool AllocateNewBlock(unsigned size);   // 0x928ba0
};
struct Alloc {
  char pad0[0x10];
  StackAllocator mAlloc;   // +0x10
  uint32_t AddBlock(Blk* b);
};
extern unsigned short g_abWord;   // 0x141a154

// @ 0x0082ABD0
uint32_t Alloc::AddBlock(Blk* b) {
  if (!b->pNext || b->pNext->mTag != 4) return (uint32_t)b->mData;
  // Access mAlloc through `this` (retail rebuilds &mAlloc after the loop and spills the
  // incoming ecx to a home slot; cl keeps `this` in esi instead).
  while (b) {
    if (b->mTag != 4) break;
    unsigned n = b->mCount * 2;
    if (mAlloc.mCur + n <= mAlloc.mCap || mAlloc.AllocateNewBlock(n)) {
      memcpy((void*)mAlloc.mCur, b->mData, n);
      mAlloc.mCur += n;
    }
    b = b->pNext;
  }
  if (mAlloc.mCur != mAlloc.mBase) {
    uint32_t old = mAlloc.mBase;
    if (mAlloc.mCur + 2 <= mAlloc.mCap || mAlloc.AllocateNewBlock(2)) {
      *(unsigned short*)mAlloc.mCur = g_abWord;
      mAlloc.mCur += 2;
    }
    unsigned aligned = (mAlloc.mCur + 7) & ~7u;
    mAlloc.mCur = aligned;
    if (aligned > mAlloc.mCap) mAlloc.mCur = mAlloc.mCap;
    mAlloc.mBase = mAlloc.mCur;
    return old;
  }
  return 0;
}

// ---------------------------------------------------------------------------

unsigned FNV1_String16(const unsigned short* s, unsigned seed, int mode);

// Resource key handed to the layout loader (12 bytes).
struct Key { int mId; uint32_t mType; uint32_t mGroup; };

// UI layout object; AddRef at +0x04, Release at +0x08.
struct SPUILayout : ObjT2 {
  uint32_t mRefCount;          // +0x04
  uint32_t mResourceKey[3];    // +0x08
  void* mpObjectCollection;    // +0x14
  SPUILayout();                               // 0x00810000
  bool Init(const Key* key, bool a, int b);
  ObjT1* FindWindowByID(unsigned id, bool a);
  bool SetParentWin(ObjT1* parent, bool a, unsigned id);
  void Shutdown(int a);
};

void* operator new(unsigned int size, const char* name, int a, int b, int c, int d);
Rect* AccumulateBounds(Rect* out, ObjT1* node, bool a, bool b);   // 0x00e36670

// A window/UI element (AddRef @0, Release @4, many virtuals covered by ObjT1).
typedef ObjT1 Win;

struct SFV {
  volatile ObjT1* vtbl0;      // +0x00
  volatile ObjT1* vtbl1;      // +0x04
  uint32_t m8;       // +0x08
  SPUILayout* mLayout;  // +0x0c
  AutoRef<ObjT1> m10;   // +0x10
  AutoRef<ObjT1> m14;   // +0x14
  AutoRef<ObjT1> m18;   // +0x18
  AutoRef<ObjT1> m1c;   // +0x1c
  AutoRef<ScrollBar> m20;   // +0x20
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

// @ 0x0082A4E0
float SFV::GetScrollOffset() {
  Rect* r = m1c->m14();
  return (r->right - r->left) + m38;
}

// @ 0x0082AA20
bool SFV::CreateFromName(const unsigned short* name, bool a, bool b) {
  unsigned h = FNV1_String16(name, 0x811c9dc5, 1);
  return Create((int)h, a, b);
}

// @ 0x0082A040  (constructor)
SFV::SFV() {
  vtbl1 = (ObjT1*)&g_sfvBase1Vtbl;
  m8 = 0;
  _ReadWriteBarrier();
  vtbl0 = (ObjT1*)&g_sfvVtbl0;
  vtbl1 = (ObjT1*)&g_sfvVtbl1;
  mLayout = 0;
  m10.mpObject = 0;
  m14.mpObject = 0;
  m18.mpObject = 0;
  m1c.mpObject = 0;
  m20.mpObject = 0;
  SPUILayout* pNew = new ("UI", 0, 0, 0, 0) SPUILayout();
  SPUILayout* pOld = mLayout;
  if (pNew != pOld) {
    if (pNew) ((ObjT2*)pNew)->m1();
    mLayout = pNew;
    if (pOld) ((ObjT2*)pOld)->m2();
  }
}

// @ 0x0082A0D0  (destructor body)
void SFV::Destroy() {
  if (m20.mpObject) m20.mpObject->m1();
  if (m1c.mpObject) m1c.mpObject->m1();
  if (m18.mpObject) m18.mpObject->m1();
  if (m14.mpObject) m14.mpObject->m1();
  if (m10.mpObject) m10.mpObject->m1();
  if (mLayout) ((ObjT2*)mLayout)->m2();
  vtbl1 = (ObjT1*)&g_sfvBase1Vtbl;
  vtbl0 = (ObjT1*)&g_sfvBase0Vtbl;
}

// @ 0x0082A450
void SFV::Shutdown() {
  if (m10.mpObject) {
    ObjT1* pObj = m10.mpObject->m4();
    if (pObj) pObj->m55(m10.mpObject);
  }
  m10 = (ObjT1*)0;
  m14 = (ObjT1*)0;
  m18 = (ObjT1*)0;
  m1c = (ObjT1*)0;
  m20 = (ScrollBar*)0;
  mLayout->Shutdown(1);
}

// @ 0x0082A140
bool SFV::Create(int a, bool b, unsigned c) {
  Key key;
  key.mId = a;
  key.mType = 0x510a95b;
  key.mGroup = 0x40464100;
  if (!mLayout->Init(&key, true, 0)) return b;

  m10 = mLayout->FindWindowByID(0x4ab5e60, false);
  m14 = mLayout->FindWindowByID(0x4ab5e50, true);
  m18 = mLayout->FindWindowByID(0x580a910, true);
  m1c = mLayout->FindWindowByID(0x4ab5e70, true);
  m20 = m1c.mpObject ? (ScrollBar*)m1c.mpObject->m3(0x2ef0c885) : 0;

  if (!m10.mpObject || !m14.mpObject || !m18.mpObject || !m1c.mpObject || !m20.mpObject) {
    mLayout->Shutdown(1);
    return b;
  }

  m20.mpObject->m9(0, 0);

  Rect* p14 = m14.mpObject->m14();
  Rect client;
  client.left = p14->left;
  client.top = p14->top;
  client.right = p14->right;
  client.bottom = p14->bottom;

  Rect view;
  view.left = 0.0f;
  view.top = 0.0f;
  view.right = client.right - client.left;
  view.bottom = client.bottom - client.top;
  m18.mpObject->m27(&view);

  Rect* p1c = m1c.mpObject->m14();

  m28 = client.left;
  m2c = client.top;

  Rect* p10 = m10.mpObject->m14();
  m34 = (p10->bottom - p10->top) - client.bottom;
  p10 = m10.mpObject->m14();
  m30 = (p10->right - p10->left) - p1c->right;
  m38 = p1c->left - client.right;
  m3c = 0;
  m40 = 0;

  m10.mpObject->m43(0);
  m14.mpObject->m43(0);
  m18.mpObject->m43(0);

  mLayout->SetParentWin(0, false, 0x5b598fa);
  m44 = b ? 0xc1 : 0x80;
  m10.mpObject->m65(this);
  m24 = (ScrollHost*)c;
  return true;
}

// @ 0x0082A500
void SFV::Update(bool force) {
  Rect* p10 = m10.mpObject->m14();
  Rect rView;
  rView.left = m28;
  rView.top = m2c;
  rView.right = (p10->right - p10->left) - m30;
  rView.bottom = (p10->bottom - p10->top) - m34;

  Rect rClip = rView;
  Rect* p1c = m1c.mpObject->m14();
  rClip.right = rClip.right - (p1c->right - p1c->left);
  m1c.mpObject->m27(&rClip);

  float viewH = rView.bottom - rView.top;
  float content;
  float best;
  // Retail keeps the accumulation target 16-byte aligned (prologue does and esp,-16).
  __declspec(align(16)) Rect area;
  if (m24) {
    content = m24->m0(rView.right - rView.left);
    best = m24->m0((rView.right - rView.left) - (rClip.right - rClip.left) - m38);
  } else {
    AccumulateBounds(&area, m18.mpObject, true, true);
    if (area.left == area.right || area.top == area.bottom) {
      content = rView.bottom - rView.top;
    } else {
      content = area.bottom - area.top;
    }
    best = content;
  }

  bool scroll = false;
  float page = content;
  if (content > viewH) {
    rView.right = rView.right - ((rClip.right - rClip.left) + m38);
    scroll = true;
    page = best;
  }

  ScrollBar* bar = m1c.mpObject ? (ScrollBar*)m1c.mpObject->m3(0x2ef0c885) : 0;
  int range = (int)page;
  int visible = (int)(rView.bottom - rView.top);
  int oldVal = m1c.mpObject->m10();
  m1c.mpObject->m31(1, scroll);
  m14.mpObject->m27(&rView);
  m14.mpObject->m31(0x400, scroll);

  Rect* p18 = m18.mpObject->m14();
  area.left = p18->left;
  area.top = p18->top;
  area.right = p18->left + (rView.right - rView.left);
  area.bottom = p18->top + page;
  m18.mpObject->m27(&area);

  if (scroll) {
    if ((oldVal & 1) && m3c == (uint32_t)range && m40 == (uint32_t)visible) {
      if (force) bar->m9(bar->m12(), 1);
    } else {
      bar->m11(0, 1);
      m3c = range;
      bar->m13(range, 1);
      m40 = visible;
      bar->m15(visible, 1);
      int val = bar->m10();
      if (force || val < bar->m12() || val > bar->m14()) val = bar->m12();
      bar->m9(val, 1);
    }
  } else {
    if (oldVal & 1) bar->m9(bar->m12(), 1);
  }
  if (!scroll) {
    bar->m11(0, 1);
    bar->m15(0, 1);
  }
  m1c.mpObject->m36();
}

// @ 0x0082A8A0
bool SFV::OnMessage(Win* pSender, Msg* pMsg) {
  bool handled = false;
  switch (pMsg->mType) {
    case 0x1c:
      if (pSender == m10.mpObject && pMsg->mArg4p != m10.mpObject) {
        pMsg->mArg4p->m66(this);
      }
      break;
    case 9: {
      int step = pMsg->mArg4 / -120;
      ScrollBar* bar = m20.mpObject;
      int inc = bar->m20();
      int val = bar->m10();
      bar->m9(val + inc * step * 2, 1);
      handled = true;
      break;
    }
    case 0x1b:
      if (pSender == m10.mpObject && pMsg->mArg4p != m10.mpObject) {
        pMsg->mArg4p->m65(this);
      }
      break;
    case 0x8ef0c8dd:
      if (pSender == m10.mpObject && pMsg->mSrc == m1c.mpObject) {
        Rect* r = m18.mpObject->m14();
        Rect area;
        area.left = r->left;
        area.top = r->top;
        area.right = r->right;
        area.bottom = r->bottom;
        float delta = -(float)pMsg->mArg3 - area.top;
        area.top = area.top + delta;
        area.bottom = area.bottom + delta;
        m18.mpObject->m27(&area);
      }
      break;
  }
  return handled;
}
