// src/game/SPEditors/SPEditorPalettePageUI.cpp -- migrated from slice(s) s005c9230, s005c85d0 by tools/migrate/rewrite.py
// Object file: SPEditors/SPEditorPalettePageUI.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "cSPUILayout.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
extern float g_one;  // 0x01485720
#include <new>
#include "SP/cSPPalettePageUI.h"
#include "EA/UTFWin/IWindow.h"

// ---- items of slice s005c85d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
#define PV(n) virtual void pv##n();
namespace EA {
template <typename T>
class AutoRefCount_s005c_85d0 {
 public:
  T* mpObject;
  AutoRefCount_s005c_85d0() : mpObject(0) {}
  AutoRefCount_s005c_85d0(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
  ~AutoRefCount_s005c_85d0() { if (mpObject) mpObject->Release(); }
  AutoRefCount_s005c_85d0& operator=(T* p) {
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
};  // namespace EA
}
using EA::AutoRefCount_s005c_85d0;
namespace eastl {
template <typename T>
class sp_vector {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  int mAllocator[2];
  sp_vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~sp_vector();  // 0x005c7f10
  T* begin() { return mpBegin; }
  T* end() { return mpEnd; }
};  // namespace eastl
}
class IRefCount {
 public:
  virtual int AddRef();
  virtual int Release();
};
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
class cRefNode : public cBase1, public IRefCount {
 public:
  virtual void Accept(int value);  // +0x18
  void Shutdown();                 // 0x005c7320
};
class cSPUILayout_s005c_85d0 {
 public:
  PV(0) PV(1)
  virtual void Release();       // +0x8
  int AddRef();                 // non-virtual, only to satisfy AutoRefCount
  void Shutdown(bool destroy);  // 0x00811ad0
};
namespace EA {
namespace UTFWin {
class IWindow_s005c_85d0 {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12)
  PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24)
  PV(25) PV(26) PV(27) PV(28) PV(29) PV(30)
  virtual void SetFlag(int flag, int value);  // +0x7c
};  // namespace UTFWin
}  // namespace EA
}
using EA::UTFWin::IWindow_s005c_85d0;
class cRefVector {
 public:
  cRefNode** mpBegin;
  cRefNode** mpEnd;
  cRefNode** mpCapacity;
  int mAllocator[2];
  cRefVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~cRefVector();
};
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
  static void operator delete(void* p) { EASTL_allocator_deallocate(p); }
  virtual cRefObj* GetRef(int a, int b, int c, int d);  // +0x20

  int mField8;                            // +0x8
  AutoRefCount_s005c_85d0<cSPUILayout_s005c_85d0> mLayout;      // +0xc
  IWindow_s005c_85d0* mSwatch;                       // +0x10
  AutoRefCount_s005c_85d0<cRefObj> mField14;         // +0x14
  float mFloat18;                         // +0x18
  float mFloat1c;                         // +0x1c
  eastl::sp_vector<cRefNode*> mNodes20;   // +0x20
  cRefVector mRefs34;                     // +0x34

  void SetSwatchFlag(int value);  // 0x005c8bf0
  void Shutdown();                // 0x005c8cc0
  void Accept(int value);         // 0x005c8d30
  cRefObj* GetAndAssign(int a1, AutoRefCount_s005c_85d0<cRefObj>* out, int a3, int a4);  // 0x005c8c50
};
extern float g_one;  // 0x01485720
// ---- items of slice s005c85d0 end

// ---- items of slice s005c9230 begin (TODO(rewrite): local stubs, replace by canonical classes)
class cSPPalettePageUI_s005c_9230 {
 public:
  bool Init(int a, int b, int c, int d);  // 0x005c9230 (cSPPalettePageUI::Init)
};
// ---- items of slice s005c9230 end

// @ 0x005c8bf0
void cSPPalettePageUI::SetSwatchFlag(int value)
{
  if (mSwatch)
    mSwatch->SetFlag(1, value);
}

// @ 0x005c8c50
cRefObj* cSPPalettePageUI::GetAndAssign(int a1, AutoRefCount_s005c_85d0<cRefObj>* out, int a3, int a4)
{
  cRefObj* p = GetRef(a1, 0x4785a3d, a3, a4);
  *out = p;
  return *out;
}

// @ 0x005c8cc0
void cSPPalettePageUI::Shutdown()
{
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

// @ 0x005c8d30
void cSPPalettePageUI::Accept(int value)
{
  int count = (int)(mRefs34.mpEnd - mRefs34.mpBegin);
  for (int i = 0; i < count; i++)
    mRefs34.mpBegin[i]->Accept(value);
}

// @ 0x005c8d70
void cPagePartBig(int a, int b, int c)
{
  (void)a;
  (void)b;
  (void)c;
}

// @ 0x005c8fd0
cRefVector::~cRefVector()
{
  cRefNode** end = mpEnd;
  for (cRefNode** p = mpBegin; p < end; ++p) {
    if (*p)
      (*p)->Release();
  }
  if (mpBegin && ((int*)mpBegin)[-1] != 0)
    EASTL_allocator_deallocate(mpBegin);
}

// @ 0x005c9010
cSPPalettePageUI::cSPPalettePageUI()
: mField8(0), mLayout(0), mSwatch(0), mField14(0), mFloat18(g_one), mFloat1c(g_one),
      mNodes20(), mRefs34() {}

// @ 0x005c90d0
void cVectorInsertBig(void* a, void* b)
{
  (void)a;
  (void)b;
}

// @ 0x005c9230
bool cSPPalettePageUI_s005c_9230::Init(int a, int b, int c, int d)
{
  (void)a;
  (void)b;
  (void)c;
  (void)d;
  return false;
}
