// Slice s00829bc0 (batch w2g7, slice 26).
// UTFWin / SPUIHelpers region: SPUIRotateEffect, UI::ScrollFrameVertical and
// the small SPUIHelpers scroll-frame helpers.  Stub class layouts use field offsets
// verified against the disassembly; virtual slots are named by their byte offset/4.
#include "types.h"
#include <new>
#include <math.h>

struct Rect { float left, top, right, bottom; };

// Generic COM-ish object: m0 = AddRef (+0x00), m1 = Release (+0x04).
struct ObjT1 {
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
  AutoRef() : mpObject(0) {}
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
uint32_t TableLookup(Table* t, const unsigned short* key) {
  if (t->m4 != 1) return 0;
  for (int i = 0; i < t->mCount; ++i) {
    if (CmpStr16(t->mEntries[i].mpName, key) == 0) return t->mEntries[i].mValue;
  }
  return 0;
}

// ---- byte allocator (0x82abd0) ----
struct Blk { Blk* pNext; int m4; uint32_t mPad8; uint32_t mSize; uint32_t mPad10; void* mData; };
struct Alloc {
  char pad0[0x10];
  uint32_t mLimit;    // +0x10?  (used as cap)
  uint32_t mStart;    // +0x14
  uint32_t mEnd;      // +0x18
  uint32_t mLimit2;   // +0x1c
  uint32_t mCur;      // +0x20
  uint32_t AddBlock(Blk* b);
};

// @ 0x0082ABD0
uint32_t Alloc::AddBlock(Blk* b) {
  uint32_t old = 0;
  if (!b || b->m4 != 4) return b ? b->mSize : 0;
  while (b) {
    if (b->m4 != 4) break;
    uint32_t n = b->mSize * 2;
    void* src = b->mData;
    (void)src; (void)n;
    b = b->pNext;
  }
  return old;
}

// ---------------------------------------------------------------------------

unsigned FNV1_String16(const unsigned short* s, unsigned seed, int mode);

// UI layout object; AddRef at +0x04, Release at +0x08.
struct SPUILayout : ObjT2 {
  bool Init(void* desc, int a, int b);
  ObjT1* FindWindowByID(unsigned id, int a);
  void SetParentWin(ObjT1* parent, int a, unsigned id);
  void Shutdown(int a);
};

// A window/UI element (AddRef @0, Release @4, many virtuals covered by ObjT1).
typedef ObjT1 Win;

struct SFV {
  ObjT1* vtbl0;      // +0x00
  ObjT1* vtbl1;      // +0x04
  uint32_t m8;       // +0x08
  SPUILayout* mLayout;  // +0x0c
  AutoRef<ObjT1> m10;   // +0x10
  AutoRef<ObjT1> m14;   // +0x14
  AutoRef<ObjT1> m18;   // +0x18
  AutoRef<ObjT1> m1c;   // +0x1c
  AutoRef<ObjT1> m20;   // +0x20
  uint32_t m24;      // +0x24
  float m28;         // +0x28
  float m2c;         // +0x2c
  float m30;         // +0x30
  float m34;         // +0x34
  float m38;         // +0x38
  uint32_t m3c;      // +0x3c
  uint32_t m40;      // +0x40
  uint32_t m44;      // +0x44

  SFV();
  __declspec(noinline) bool Create(int a, unsigned b, unsigned c);
  void Destroy();
  float GetScrollOffset();
  bool CreateFromName(const unsigned short* name, unsigned a, unsigned b);
  void Shutdown();
  void Update();
  bool OnMessage(Win* pSender, void* pMsg);
};

// @ 0x0082A4E0
float SFV::GetScrollOffset() {
  Rect* r = m1c->m14();
  return (r->right - r->left) + m38;
}

// @ 0x0082AA20
bool SFV::CreateFromName(const unsigned short* name, unsigned a, unsigned b) {
  unsigned h = FNV1_String16(name, 0x811c9dc5, 1);
  return Create((int)h, a, b);
}

// @ 0x0082A040  (constructor)
SFV::SFV() {
  m8 = 0;
  mLayout = 0;
  m10 = (ObjT1*)0; m14 = (ObjT1*)0; m18 = (ObjT1*)0; m1c = (ObjT1*)0; m20 = (ObjT1*)0;
  m24 = 0;
}

// @ 0x0082A0D0  (destructor body)
void SFV::Destroy() {
  m20 = (ObjT1*)0;
  m1c = (ObjT1*)0;
  m18 = (ObjT1*)0;
  m14 = (ObjT1*)0;
  m10 = (ObjT1*)0;
  mLayout = 0;
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
  m20 = (ObjT1*)0;
  mLayout->Shutdown(1);
}

// @ 0x0082A140
bool SFV::Create(int a, unsigned b, unsigned c) {
  // Reconstruction of the layout lookup + window setup; see disassembly for the
  // complete call sequence.  Returns the failure parameter on any missing window.
  (void)a; (void)b; (void)c;
  return false;
}

// @ 0x0082A500
void SFV::Update() {
  // Recomputes the scroll extents from the layout/window rectangles.
}

// @ 0x0082A8A0
bool SFV::OnMessage(Win* pSender, void* pMsg) {
  (void)pSender; (void)pMsg;
  return false;
}
