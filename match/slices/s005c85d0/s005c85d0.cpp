// slice s005c85d0 -- SP::cSPPalettePage::CommonInit / Init and the page-UI helper methods
// (page-part iteration, refcounted-vector teardown, page-UI ctor/dtor). Flags as the module:
// /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include <new>
#include "types.h"

extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
void* operator new(unsigned int n, const char* name, int flags, unsigned int debugFlags,
                   const char* file, int line);

#define PV(n) virtual void pv##n();

namespace EA {
template <typename T>
class AutoRefCount {
 public:
  T* mpObject;
  AutoRefCount() : mpObject(0) {}
  AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
  ~AutoRefCount() { if (mpObject) mpObject->Release(); }
  AutoRefCount& operator=(T* p) {
    if (p != mpObject) {
      T* const pTemp = mpObject;
      if (p)
        p->AddRef();
      mpObject = p;
      if (pTemp)
        pTemp->Release();
    }
    return *this;
  }
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
};
}  // namespace EA

using EA::AutoRefCount;

namespace eastl {
template <typename T>
class sp_vector {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  int mAllocator[2];
  sp_vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~sp_vector();
  T* begin() { return mpBegin; }
  T* end() { return mpEnd; }
};
}  // namespace eastl

// Refcount interface reached through a secondary base at +0xc (AddRef slot0 / Release slot1).
class IRefCount {
 public:
  virtual int AddRef();
  virtual int Release();
};

// First polymorphic base of 0xc bytes, so IRefCount of cRefObj lands at +0xc.
class cBase1 {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5)
  int mPad4, mPad8;
};

class cRefObj : public cBase1, public IRefCount {
 public:
  virtual void Accept(int value);  // +0x18
  void Shutdown();                 // 0x005c7320
};

// Page-part element in the +0x34 refcounted vector.
class cRefNode : public cBase1, public IRefCount {
 public:
  virtual void Accept(int value);  // +0x18
  void Shutdown();                 // 0x005c7320
};

// UI layout: Release at vtable +0x8.
class cSPUILayout {
 public:
  PV(0) PV(1)
  virtual void Release();       // +0x8
  int AddRef();                 // non-virtual, only to satisfy AutoRefCount
  void Shutdown(bool destroy);  // 0x00811ad0
};

namespace EA {
namespace UTFWin {
class IWindow {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12)
  PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24)
  PV(25) PV(26) PV(27) PV(28) PV(29) PV(30)
  virtual void SetFlag(int flag, int value);  // +0x7c
};
}  // namespace UTFWin
}  // namespace EA
using EA::UTFWin::IWindow;

// +0x34 vector: raw pointer array with Release/free (dtor @005c8fd0).
class cRefVector {
 public:
  cRefNode** mpBegin;
  cRefNode** mpEnd;
  cRefNode** mpCapacity;
  int mAllocator[2];
  cRefVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~cRefVector();
};

// Two no-data polymorphic bases; the first has a virtual dtor so the derived dtor and GetRef
// land at slots 0 and 8 (+0x20) exactly.
class cUIVtblA {
 public:
  virtual ~cUIVtblA() {}
  PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7)
};
class cUIVtblB {
 public:
  virtual ~cUIVtblB() {}
  PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7)
};

class cSPPalettePageUI : public cUIVtblA, public cUIVtblB {
 public:
  cSPPalettePageUI();
  virtual ~cSPPalettePageUI() {}
  virtual cRefObj* GetRef(int a, int b, int c, int d);  // +0x20

  int mField8;                            // +0x8
  AutoRefCount<cSPUILayout> mLayout;      // +0xc
  IWindow* mSwatch;                       // +0x10
  AutoRefCount<cRefObj> mField14;         // +0x14
  float mFloat18;                         // +0x18
  float mFloat1c;                         // +0x1c
  eastl::sp_vector<cRefNode*> mNodes20;   // +0x20
  cRefVector mRefs34;                     // +0x34

  void SetSwatchFlag(int value);  // 0x005c8bf0
  void Shutdown();                // 0x005c8cc0
  void Accept(int value);         // 0x005c8d30
  cRefObj* GetAndAssign(int a1, AutoRefCount<cRefObj>* out, int a3, int a4);  // 0x005c8c50
};

// @ 0x005C8BF0
void cSPPalettePageUI::SetSwatchFlag(int value) {
  if (mSwatch)
    mSwatch->SetFlag(1, value);
}

// @ 0x005C8D30
void cSPPalettePageUI::Accept(int value) {
  int count = (int)(mRefs34.mpEnd - mRefs34.mpBegin);
  for (int i = 0; i < count; i++)
    mRefs34.mpBegin[i]->Accept(value);
}

// @ 0x005C8CC0
void cSPPalettePageUI::Shutdown() {
  int count = (int)(mNodes20.mpEnd - mNodes20.mpBegin);
  for (int i = 0; i < count; i++)
    mNodes20.mpBegin[i]->Shutdown();
  int count2 = (int)(mRefs34.mpEnd - mRefs34.mpBegin);
  for (int i = 0; i < count2; i++)
    mRefs34.mpBegin[i]->pv2();
  if (mLayout) {
    mLayout->Shutdown(true);
    mLayout = 0;
  }
}

// @ 0x005C8C50
cRefObj* cSPPalettePageUI::GetAndAssign(int a1, AutoRefCount<cRefObj>* out, int a3, int a4) {
  cRefObj* p = GetRef(a1, 0x4785a3d, a3, a4);
  *out = p;
  return *out;
}

// @ 0x005C8FD0
cRefVector::~cRefVector() {
  cRefNode** end = mpEnd;
  for (cRefNode** p = mpBegin; p < end; ++p) {
    if (*p)
      (*p)->Release();
  }
  if (mpBegin && ((int*)mpBegin)[-1] != 0)
    EASTL_allocator_deallocate(mpBegin);
}

extern float g_one;  // 0x01485720

// @ 0x005C9010
cSPPalettePageUI::cSPPalettePageUI()
    : mField8(0), mLayout(0), mSwatch(0), mField14(0), mFloat18(g_one), mFloat1c(g_one),
      mNodes20(), mRefs34() {}

// @ 0x005C9070
// (deleting destructor ??_G is generated from the inline ~cSPPalettePageUI)

// ---------------------------------------------------------------------------------------------
// Large functions: signature-only stubs (partial).

class cSPPalettePage {
 public:
  bool CommonInit(int a, int b);
  bool Init(int a, int b, int c, int d, float e);
  void ProcessPagePart(int a, void* b, int c);
};

// @ 0x005C85D0
bool cSPPalettePage::CommonInit(int a, int b) {
  (void)a;
  (void)b;
  return false;
}

// @ 0x005C8AD0
bool cSPPalettePage::Init(int a, int b, int c, int d, float e) {
  (void)a;
  (void)b;
  (void)c;
  (void)d;
  (void)e;
  return false;
}

// @ 0x005C8D70
void cPagePartBig(int a, int b, int c) {
  (void)a;
  (void)b;
  (void)c;
}

// @ 0x005C90D0
void cVectorInsertBig(void* a, void* b) {
  (void)a;
  (void)b;
}
