// Slice s005bc0f0 -- SP::cSPEditorManipulationStackingSimple (Spore creature editor)
// Flags for this region: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include <new>
#include <math.h>
#include "types.h"

void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file, int line);
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
void* EASTL_allocator_allocate(unsigned int n, const char* name, int flags, int debugFlags, const char* file, int line); // 0x00f473a0

struct cSPVector3 { float x, y, z; cSPVector3() {} cSPVector3(float a, float b, float c) : x(a), y(b), z(c) {} };

namespace EA {
template <typename T>
class AutoRefCount {
 public:
  T* mpObject;
  AutoRefCount() : mpObject(0) {}
  AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
  ~AutoRefCount() { if (mpObject) mpObject->Release(); }
  AutoRefCount& operator=(T* p) {
    if (p != mpObject) { T* t = mpObject; if (p) p->AddRef(); mpObject = p; if (t) t->Release(); }
    return *this;
  }
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
};
template <typename T>
class RefCountVTemplate {
 public:
  RefCountVTemplate() : mRefCount(0) {}
  virtual ~RefCountVTemplate() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
}
namespace eastl {
template <typename T>
class sp_vector {
 public:
  T* mpBegin; T* mpEnd; T* mpCapacity; int mAllocator[2];
  ~sp_vector() { if (mpBegin && ((int*)mpBegin)[-1] != 0) EASTL_allocator_deallocate(mpBegin); }
  int size() const { return (int)(mpEnd - mpBegin); }
  T& operator[](int i) { return mpBegin[i]; }
  sp_vector& operator=(const sp_vector& x);
};
}

namespace SP {

class cSPEditorBlock {
 public:
  virtual void v0();
  virtual void AddRef();
  virtual void Release();
  char pad04[0x33c - 4];
  void* m33c;                       // +0x33c
  cSPEditorBlock** mChildrenBegin;  // +0x340
  cSPEditorBlock** mChildrenEnd;    // +0x344
};

class cSPEditorManipulationObject {
 public:
  __declspec(noinline) cSPEditorManipulationObject();
  virtual ~cSPEditorManipulationObject() {}
  bool mChangedObject;         // +0x4
  bool mUseDeadZone;           // +0x5
  bool mMovedOutsideDeadZone;  // +0x6
  float mDeadZoneSize;         // +0x8
  float mInitialX;             // +0xc
  float mInitialY;             // +0x10
};

class cSPEditorManipulationStackingSimple : public cSPEditorManipulationObject, public EA::RefCountVTemplate<int> {
 public:
  EA::AutoRefCount<cSPEditorBlock> mBlock;                            // +0x1c
  bool mNewAttachment;                                                // +0x20
  char pad21[0x24 - 0x21];
  cSPEditorBlock* mOriginalParent;                                    // +0x24
  eastl::sp_vector<EA::AutoRefCount<cSPEditorBlock> > mPileList;      // +0x28
  eastl::sp_vector<void*> mEffectList;                                // +0x3c
  cSPVector3 mMouseOffset;                                            // +0x50
  float mX;                                                           // +0x5c
  float mY;                                                           // +0x60
  cSPVector3 mOriginalMouseOffset;                                    // +0x64
  bool mUnk70;                                                        // +0x70

  cSPEditorManipulationStackingSimple();
  ~cSPEditorManipulationStackingSimple();
  void Init(cSPEditorBlock** block, cSPVector3 offset);
  bool DoOnMouseDown();
  void Other1();
  void Other2();
};

volatile int g_s59_sink;
__declspec(noinline) cSPEditorManipulationObject::cSPEditorManipulationObject() { g_s59_sink = 1; }

// @ 0x005bc7f0
void cSPEditorManipulationStackingSimple::Init(cSPEditorBlock** block, cSPVector3 offset) {
  mBlock = *block;
  mMouseOffset = offset;
  mOriginalMouseOffset = offset;
  if (mBlock)
    mOriginalParent = (cSPEditorBlock*)mBlock->m33c;
  mNewAttachment = false;
}

// @ 0x005bc860
cSPEditorManipulationStackingSimple::cSPEditorManipulationStackingSimple() {
  mBlock = (cSPEditorBlock*)0;
  mPileList.mpBegin = 0;
  mPileList.mpEnd = 0;
  mPileList.mpCapacity = 0;
  mMouseOffset = cSPVector3(0.0f, 0.0f, 0.0f);
  mEffectList.mpBegin = 0;
  mEffectList.mpEnd = 0;
  mEffectList.mpCapacity = 0;
  mOriginalMouseOffset = cSPVector3(0.0f, 0.0f, 0.0f);
  mUnk70 = false;
  mChangedObject = false;
}

// @ 0x005bc930
cSPEditorManipulationStackingSimple::~cSPEditorManipulationStackingSimple() {}

// @ 0x005bc0f0 -- PARTIAL
void cSPEditorManipulationStackingSimple::Other1() {}
// @ 0x005bc630 -- PARTIAL
void cSPEditorManipulationStackingSimple::Other2() {}
// @ 0x005bcaa0 -- PARTIAL
bool cSPEditorManipulationStackingSimple::DoOnMouseDown() { return false; }

}  // namespace SP

namespace eastl {
// @ 0x005bc9b0 -- PARTIAL
template <typename T>
sp_vector<T>& sp_vector<T>::operator=(const sp_vector<T>& x) {
  if (this != &x) {
    mpBegin = x.mpBegin;
    mpEnd = x.mpEnd;
    mpCapacity = x.mpCapacity;
  }
  return *this;
}
}  // namespace eastl
