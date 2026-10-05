// Slice s005b94b0 -- SP::cSPEditorManipulation* (Spore creature editor)
// Flags for this region: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include <new>
#include <math.h>
#include "types.h"

void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file, int line);
extern "C" void EASTL_allocator_deallocate(void* p);
void* EASTL_allocator_allocate(unsigned int n, const char* name, int flags, int debugFlags, const char* file, int line);

struct cSPVector3 { float x, y, z; cSPVector3() {} cSPVector3(float a, float b, float c) : x(a), y(b), z(c) {} };

namespace EA {
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
};
}

namespace SP {
class cSPEditorBlock;

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

class cSPEditorManipulation56 : public cSPEditorManipulationObject, public EA::RefCountVTemplate<int> {
 public:
  void* m1c;                                  // +0x1c
  char pad20[0x24 - 0x20];
  cSPEditorBlock* mBlock;                     // +0x24
  eastl::sp_vector<cSPEditorBlock*> mVec;     // +0x28
  cSPVector3 mV3c;                            // +0x3c
  cSPVector3 mV48;                            // +0x48
  float m54;                                  // +0x54
  float m58;                                  // +0x58
  char pad5c[0x60 - 0x5c];
  cSPVector3 mV60;                            // +0x60
  cSPVector3 mV6c;                            // +0x6c
  cSPVector3 mV78;                            // +0x78
  cSPEditorBlock* m84;                        // +0x84
  char pad88[0x89 - 0x88];
  bool m89;                                   // +0x89
  bool m8a;                                   // +0x8a

  cSPEditorManipulation56();
  bool DoOnMouseDown();
  void Update(float dt);
  void SetBlock(cSPEditorBlock* b, int a, int c, int d, unsigned char e);
  void Other1();
  void* CopyOut(void* dst);
  void Other2();
};

volatile int g_s56_sink;
__declspec(noinline) cSPEditorManipulationObject::cSPEditorManipulationObject() { g_s56_sink = 1; }

// @ 0x005ba060
cSPEditorManipulation56::cSPEditorManipulation56() : m1c(0) {
  mBlock = 0;
  mVec.mpBegin = 0;
  mVec.mpEnd = 0;
  mVec.mpCapacity = 0;
  mV3c.x = 0.0f;
  mV3c.y = 0.0f;
  mV3c.z = 0.0f;
  m89 = false;
  m8a = false;
  mChangedObject = false;
}

// @ 0x005b94b0 -- PARTIAL
bool cSPEditorManipulation56::DoOnMouseDown() { return true; }
// @ 0x005b9660 -- PARTIAL
void cSPEditorManipulation56::Update(float dt) { (void)dt; }
// @ 0x005b9840 -- PARTIAL
void cSPEditorManipulation56::SetBlock(cSPEditorBlock* b, int a, int c, int d, unsigned char e) {
  (void)b; (void)a; (void)c; (void)d; (void)e;
}
// @ 0x005b9b40 -- PARTIAL
void cSPEditorManipulation56::Other1() {}
// @ 0x005ba0f0 -- PARTIAL
void* cSPEditorManipulation56::CopyOut(void* dst) { (void)dst; return this; }
// @ 0x005ba190 -- PARTIAL
void cSPEditorManipulation56::Other2() {}

}  // namespace SP
