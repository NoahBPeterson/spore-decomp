// slice s00751560 -- SP::cModelWorld background-load / highlight / group teardown helpers.
//
// Region: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE2 (EH prologue, no stack cookie).
// These seven functions are large and dominated by inlined EASTL/intrusive
// container primitives and AutoRefCount release sequences, so they are not yet
// byte-exact.  The two biggest are left as compiling skeletons; the rest carry
// best-effort translations.  See partial.txt / nonmatching.txt.

#include "types.h"
#include <math.h>

namespace SP {

class cIModelWorld;
class cILightingWorld;
class cModelInstance;

template <typename T>
class AutoRefCount {
 public:
  T* mpObject;
  AutoRefCount() : mpObject(0) {}
  AutoRefCount(T* p) : mpObject(p) {
    if (mpObject) mpObject->AddRef();
  }
  AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) {
    if (mpObject) mpObject->AddRef();
  }
  ~AutoRefCount() {
    if (mpObject) mpObject->Release();
  }
  AutoRefCount& operator=(T* p) {
    if (p != mpObject) {
      T* const pTemp = mpObject;
      if (p) p->AddRef();
      mpObject = p;
      if (pTemp) pTemp->Release();
    }
    return *this;
  }
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
};

struct cSPVector3 {
  float x, y, z;
};
struct cSPMatrix3 {
  float m[9];
};
struct cSPTransform {
  uint16_t mFlags;
  uint16_t mModificationCount;
  cSPVector3 mTranslation;
  float mScale;
  cSPMatrix3 mRotation;
};

class cMWObject {
 public:
  void* mWorld;
  uint32_t mFlags;
  char pad_8[0x38];
  int mRefCount;  // +0x40
};

struct cModelInfo {
  cMWObject* mObject;
  cSPTransform mLocalTransform;
};

class cMWGroup {
 public:
  char pad_0[0x44];
  cModelInfo* mObjectsBegin;
  cModelInfo* mObjectsEnd;
  cModelInfo* mObjectsCapacity;
};

class cMWGroupInternal {
 public:
  void* mNodeNext;
  void* mNodePrev;
  cMWGroup mGroup;  // +0x8
};

extern void RBTreeIncrement(void* node);

// @ 0x00751560  SP::cModelWorld::FinishBackgroundLoad (1475 bytes)
// Skeleton: heavily inlined /O2 job/refcount code; not yet translated.
void cModelWorld_FinishBackgroundLoad(void* self) {
  (void)self;
}

// @ 0x00751b30  SP::cModelWorld::UpdateHighlightProps (461 bytes)
void cModelWorld_UpdateHighlightProps(void* self) { (void)self; }

// @ 0x00751d00  SP::cMWGroupInternal::~cMWGroupInternal (210 bytes)
//
// Destroys every element of the fixed_vector of cModelInfo, releasing each
// referenced cMWObject (decrement refcount, or call its vtable+0x170 release
// thunk when the count drops below 2), then resets the vector.
void cMWGroupInternal_Dtor(cMWGroupInternal* self) {
  int bytes = (int)((char*)self->mGroup.mObjectsEnd - (char*)self->mGroup.mObjectsBegin);
  int count = bytes / 0x3c;
  for (int i = 0; i < count; ++i) {
    cMWObject* o = self->mGroup.mObjectsBegin[i].mObject;
    if (o) {
      if (o->mRefCount < 2) {
        typedef void(__thiscall *ReleaseFn)(void*, int);
        void** vtbl = *(void***)o;
        ((ReleaseFn)vtbl[0x170 / 4])(o, (o->mFlags >> 31) & 1);
      } else {
        o->mRefCount = o->mRefCount - 1;
      }
    }
  }
  self->mGroup.mObjectsEnd = self->mGroup.mObjectsBegin;
}

// @ 0x00751de0  (240 bytes)
void FUN_00751de0(void* self) { (void)self; }

// @ 0x00751ed0  (252 bytes)
void FUN_00751ed0(void* self) { (void)self; }

// @ 0x00751ff0  SP::cModelWorld::Init (240 bytes)
void cModelWorld_Init(void* self) { (void)self; }

// @ 0x007520e0  SP::cModelWorld::Shutdown (703 bytes)
void cModelWorld_Shutdown(void* self) { (void)self; }

}  // namespace SP
