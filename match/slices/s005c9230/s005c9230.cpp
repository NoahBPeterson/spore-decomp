// slice s005c9230 -- cUIMissionCard-ish page/feed UI object: SetWindowFlag / GetCurrent /
// ctor / dtor / DoMessage, plus cSPPalettePageUI::Init and a big subcategory updater.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include <new>
#include "types.h"

extern "C" void EASTL_allocator_deallocate(void* p);
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
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
};
}  // namespace EA
using EA::AutoRefCount;

namespace EA {
namespace UTFWin {
class IUnknown32 {
 public:
  virtual int AddRef();   // +0
  virtual int Release();  // +4
};
class IWindow : public IUnknown32 {
 public:
  PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12)
  PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24)
  PV(25) PV(26) PV(27) PV(28) PV(29) PV(30)
  virtual void SetFlag(int flag, int value);  // +0x7c
};
}  // namespace UTFWin
}  // namespace EA
using EA::UTFWin::IWindow;

namespace eastl {
// Vector whose element dtor is trivial: dtor inlines to a single allocator free.
template <typename T>
class sp_trivial_vector {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  int mAllocator[2];
  sp_trivial_vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~sp_trivial_vector() {
    if (mpBegin && ((int*)mpBegin)[-1] != 0)
      EASTL_allocator_deallocate(mpBegin);
  }
};

// Vector of refcounted elements: out-of-line destructor (call target 0x005c9c30).
class cCategory;
template <typename T>
class sp_ref_vector {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  int mAllocator[2];
  sp_ref_vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~sp_ref_vector();
  unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
  T& operator[](unsigned int i) { return mpBegin[i]; }
};
}  // namespace eastl

// ---------------------------------------------------------------------------------------------
// Three no-data polymorphic bases (vtables at +0, +4, +8).
class cB0 { public: virtual ~cB0() {} PV(1) PV(2) };
class cB1 { public: virtual ~cB1() {} PV(1) PV(2) };
class cB2 {
 public:
  cB2() : mFieldc(0) {}
  virtual ~cB2() {}
  PV(1) PV(2)
  int mFieldc;
};

class cFeedCategory {
 public:
  char pad0[0x6c];
  int mId;  // +0x6c
};

class cUIMissionCard : public cB0, public cB1, public cB2 {
 public:
  cUIMissionCard();
  virtual ~cUIMissionCard();

  AutoRefCount<IWindow> mWindow;            // +0x10
  int mSelectedIndex;                       // +0x14
  float mFloat18;                           // +0x18
  float mFloat1c;                           // +0x1c
  char pad20[0x10];                         // +0x20
  eastl::sp_trivial_vector<int> mVec30;     // +0x30
  eastl::sp_trivial_vector<int> mVec44;     // +0x44
  eastl::sp_trivial_vector<int> mVec58;     // +0x58
  eastl::sp_ref_vector<AutoRefCount<cFeedCategory> > mVec6c;  // +0x6c
  eastl::sp_trivial_vector<int> mVec80;     // +0x80

  void SetWindowFlag(int value);   // 0x005c9810
  cFeedCategory* GetCurrent();     // 0x005c9830
};

// @ 0x005C9810
void cUIMissionCard::SetWindowFlag(int value) {
  if (mWindow)
    mWindow->SetFlag(1, value);
}

// @ 0x005C9830
cFeedCategory* cUIMissionCard::GetCurrent() {
  int index = mSelectedIndex;
  if (index >= 0 && index < (int)mVec6c.size())
    return mVec6c[index];
  return 0;
}

// @ 0x005C9C70
cUIMissionCard::cUIMissionCard()
    : mSelectedIndex(0), mFloat18(0.0f), mFloat1c(0.0f) {}

// @ 0x005C9D10
cUIMissionCard::~cUIMissionCard() {}

// ---------------------------------------------------------------------------------------------
// Large functions: signature-only stubs (partial).

class cSPPalettePageUI {
 public:
  bool Init(int a, int b, int c, int d);
};

// @ 0x005C9230
bool cSPPalettePageUI::Init(int a, int b, int c, int d) {
  (void)a;
  (void)b;
  (void)c;
  (void)d;
  return false;
}

// @ 0x005C98A0
void cSubCategoryUpdate(int deltaTime) {
  (void)deltaTime;
}

// @ 0x005C9DD0
bool cUIMissionCardDoMessageStub(int param_2, void* message) {
  (void)param_2;
  (void)message;
  return false;
}
