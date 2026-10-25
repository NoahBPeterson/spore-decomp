// Slice s005bc0f0 -- SP::cSPEditorManipulationStacking / ...Simple (Spore creature editor)
// Flags for this region: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include <new>
#include <math.h>
#include <string.h>
#include "types.h"

void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file, int line);
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
void* EASTL_allocator_allocate(unsigned int n, const char* name, int flags, int debugFlags, const char* file, int line); // 0x00f473a0
extern const char kEditorAllocName[]; // 0x013eb430 ("Editor")

struct cSPVector3 {
  float x, y, z;
  cSPVector3() {}
  cSPVector3(float a, float b, float c) : x(a), y(b), z(c) {}
  cSPVector3(const cSPVector3& v) : x(v.x), y(v.y), z(v.z) {}
};

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
// 8-byte vector allocator (EASTL sp_vector_allocator), keeps the 0x14-byte vector layout.
struct sp_vector_allocator {
  int mAllocId;
  int mAllocPad;
};

template <typename T, typename Alloc>
class vector {
 public:
  T* mpBegin;      // +0x0
  T* mpEnd;        // +0x4
  T* mpCapacity;   // +0x8
  Alloc mAllocator;

  ~vector() { if (mpBegin && ((int*)mpBegin)[-1] != 0) EASTL_allocator_deallocate(mpBegin); }
  int size() const { return (int)(mpEnd - mpBegin); }
  T& operator[](int i) { return mpBegin[i]; }
  T* erase(T* first, T* last);                                  // 0x00454280
  void* Grow(unsigned int n, const T* first, const T* last);    // 0x005bc8e0
  vector& operator=(const vector& x);
};
}

namespace SP {

class cSPEditorBlock;
class cSPEditorModel;
class cSPEditorPhysicsWorld;

struct cSPMatrix3 {
  float m[9];
  cSPMatrix3() {}
  cSPMatrix3(const cSPMatrix3& o);              // 0x0041cb40
  void Assign(const cSPMatrix3& o);             // 0x0041cb40
};

// EA::RefCountTemplate<int> sub-object of cSPEditorModel (vptr at +4, count at +8).
struct ModelRefCount {
  virtual void Destroy(int flag);   // slot 0: scalar deleting destructor
  int mnRefCount;                   // +0x8 in cSPEditorModel
  void AddRef() { ++mnRefCount; }
  __forceinline int Release() {
    int n = --mnRefCount;
    if (n == 0) {
      mnRefCount = 1;
      Destroy(1);
    }
    return n;
  }
};

class cSPEditorPhysicsWorld {
 public:
  char pad00[0xc];
  void* mpFloorBody;                // +0xc
};

class cSPEditorModel {
 public:
  virtual void v0();                            // +0x0 vtable
  ModelRefCount rc;                             // +0x4
  void AddRef() { rc.AddRef(); }
  int Release() { return rc.Release(); }
  cSPEditorPhysicsWorld* GetPhysicsWorld();     // 0x004ad450
  float GetScale();                             // 0x004adaa0
  bool UsingSymmetry() const;                   // 0x004adc40
};
}

namespace EA { namespace Swarm {
class cIVisualEffect {
 public:
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void Update(int mode);    // +0xc
};
}}

namespace SP {

class cSPEditorBlock {
 public:
  virtual void v0();
  virtual int AddRef();
  virtual int Release();

  char pad04[0x28 - 4];
  cSPEditorModel* mpModel;                      // +0x28
  char pad2c[0x48 - 0x2c];
  cSPVector3 mPosition;                         // +0x48
  char pad54[0x60 - 0x54];
  cSPMatrix3 mOrientation;                      // +0x60
  char pad84[0xa8 - 0x84];
  cSPMatrix3 mBaseOrientation;                  // +0xa8
  char padcc[0x33c - 0xcc];
  cSPEditorBlock* mpParent;                     // +0x33c
  char pad340[0x3c9 - 0x340];
  char mbOnFloor;                               // +0x3c9
  char pad3ca[0x3e0 - 0x3ca];
  cSPEditorBlock* mpSymmetric;                  // +0x3e0
  char pad3e4[0xdc8 - 0x3e4];
  unsigned int mFlagsA;                         // +0xdc8
  unsigned int mFlagsB;                         // +0xdcc

  void SetPosition(const cSPVector3& pos, bool notify);   // 0x00448e90
  void SetIsOnGround(bool onGround);                      // 0x0049c0f0
  bool Unk43bbc0(int a);                                  // 0x0043bbc0
  bool NeedPostUpdate();                                  // 0x00435c80
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

typedef eastl::vector<EA::AutoRefCount<cSPEditorBlock>, eastl::sp_vector_allocator> BlockRefVector;
typedef eastl::vector<EA::Swarm::cIVisualEffect*, eastl::sp_vector_allocator> EffectVector;
typedef EA::AutoRefCount<cSPEditorBlock> BlockRef;

class cSPEditorManipulationStacking : public cSPEditorManipulationObject, public EA::RefCountVTemplate<int> {
 public:
  char pad1c[0x24 - 0x1c];
  cSPEditorBlock* mpBlock;                      // +0x24
  BlockRefVector mPileList;                     // +0x28
  cSPVector3 mMouseOffset;                      // +0x3c
  cSPVector3 mStartPos;                         // +0x48
  float mLastX;                                 // +0x54
  float mLastY;                                 // +0x58
  int mLastFlags;                               // +0x5c
  cSPVector3 mPosition;                         // +0x60
  char pad6c[0x8a - 0x6c];
  bool mAlignmentState;                         // +0x8a

  int MoveBlockStacking(cSPEditorBlock* block, BlockRefVector* pile, cSPVector3 rayOrigin,
                        cSPVector3 rayDirection);                             // 0x005bb5a0
  virtual bool DoOnMouseMove(float x, float y, int flags);
};

class cSPEditorManipulationStackingSimple : public cSPEditorManipulationObject, public EA::RefCountVTemplate<int> {
 public:
  EA::AutoRefCount<cSPEditorBlock> mBlock;      // +0x1c
  bool mNewAttachment;                          // +0x20
  char pad21[0x24 - 0x21];
  cSPEditorBlock* mOriginalParent;              // +0x24
  BlockRefVector mPileList;                     // +0x28
  EffectVector mEffectList;                     // +0x3c
  cSPVector3 mMouseOffset;                      // +0x50
  float mX;                                     // +0x5c
  float mY;                                     // +0x60
  cSPVector3 mOriginalMouseOffset;              // +0x64
  bool mUnk70;                                  // +0x70

  cSPEditorManipulationStackingSimple();
  ~cSPEditorManipulationStackingSimple();
  void Init(cSPEditorBlock** block, cSPVector3 offset);
  virtual bool OnMouseUp(unsigned int button, float x, float y, unsigned int flags);
  virtual bool DoOnMouseDown(unsigned int button, float x, float y, unsigned int flags);
};

class cSPEditorAnimatedEventInfo {
 public:
  cSPEditorAnimatedEventInfo();                 // 0x0059d960
  virtual void v0();
  virtual int AddRef();                         // +0x4
  virtual int Release();                        // +0x8
  void MessagePost(uint32_t id, cSPEditorBlock* block, cSPEditorModel* model, unsigned int a,
                   bool b, float c, int d, int e, float f);   // 0x0059d840
};

struct cViewer {
  void GetWorldRayFromScreenCoords(float x, float y, cSPVector3* origin, cSPVector3* dir);  // 0x007c4730
};

struct cAppSystem {
  virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
  virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
  virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
  virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
  virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
  virtual void v20(); virtual void v21();
  virtual cViewer* GetViewer();                 // +0x58
};
cAppSystem* App();                              // 0x0067dd10

struct cReporter {
  void Report(const char* message);             // 0x0067c830
};

}  // namespace SP

// ---- free helpers (retail order of calls preserved) ---------------------------------
namespace SP {

extern const float g_defaultBlockScale;         // 0x014853e0 (4.0f)
extern const float g_stackScaleFactor;          // 0x013f5698 (0.667f)
extern const float g_alignmentEpsilon;          // 0x013eb960 (0.01f)
extern const float g_minusOne;                  // 0x013eb1bc (-1.0f)
extern int g_killSetAlignmentOff;               // 0x015ea600
extern int g_killSetAlignmentOn;                // 0x015ea668

void KillSeti(int id);                                                          // 0x004a88d0
cSPEditorBlock* FUN_004a3dc0(cSPEditorBlock* block, void* pile, cSPVector3 origin,
                             cSPVector3 dir, cSPVector3* outPosition);          // 0x004a3dc0
void FUN_004a1070(cSPEditorBlock* block);                                       // 0x004a1070
bool FUN_004982b0(cSPEditorBlock* block, char unk0, float scale, char unk1);    // 0x004982b0
void FUN_00496300(cSPEditorBlock* block, void* pile, cSPVector3 origin, cSPVector3 dir,
                  cSPVector3 startPos, int unk);                                // 0x00496300
void FUN_004a6d20(cSPEditorBlock* block, void* pile, int flag, int a, int b, int c,
                  int d, int e);                                                // 0x004a6d20
void SnapBlockToSocket(cSPEditorBlock* block, void* pile, cSPEditorBlock* socket); // 0x004a29a0
void SetSymmetricBlocksUIState(cSPEditorBlock* block, void* pile, int state);   // 0x004a7f30
void BuildPileList(cSPEditorBlock* block, void* pile, int depth);               // 0x0048c790
void RecordBlockAndPileHistory(cSPEditorBlock* block, void* pile);              // 0x004961d0
void ReleaseRefs(cSPEditorBlock* block, void* pile);                            // 0x004a8860
void DeleteInvalidBlocks(cSPEditorBlock* block, void* pile);                    // 0x004a6f10
void FUN_0049cfd0(cSPEditorBlock* block);                                       // 0x0049cfd0
BlockRef* RemoveCopyBlocks(BlockRef* first, BlockRef* last, BlockRef* result,
                           const BlockRef* value);                              // 0x005aa740
EffectVector FUN_004a37f0(cSPEditorModel* model, unsigned int effectId);        // 0x004a37f0
void* FUN_0067cac0();                                                           // 0x0067cac0
float GetAlignmentPosition(cSPEditorBlock* block, void* pile, cSPVector3 pos, cSPMatrix3 m2,
                           cSPVector3* outPos, cSPMatrix3* outRot, bool* flag, int mode,
                           cSPMatrix3 m1);                                      // 0x00490a70
}

namespace SP {

volatile int g_s59_sink;
__declspec(noinline) cSPEditorManipulationObject::cSPEditorManipulationObject() { g_s59_sink = 1; }

// @ 0x005bc7f0
void cSPEditorManipulationStackingSimple::Init(cSPEditorBlock** block, cSPVector3 offset) {
  mBlock = *block;
  mMouseOffset = offset;
  mOriginalMouseOffset = offset;
  if (mBlock)
    mOriginalParent = (cSPEditorBlock*)mBlock->mpParent;
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

// @ 0x005bc0f0
bool cSPEditorManipulationStacking::DoOnMouseMove(float x, float y, int flags) {
  cSPEditorBlock* block = mpBlock;
  if (!block)
    return false;

  if ((mLastX != x || mLastY != y) && !mChangedObject)
    mChangedObject = true;
  mLastX = x;
  mLastY = y;
  mLastFlags = flags;

  cSPVector3 startPos = block->mPosition;
  cSPEditorModel* model = block->mpModel;

  cSPVector3 origin, dir;
  App()->GetViewer()->GetWorldRayFromScreenCoords(x, y, &origin, &dir);

  origin.x = origin.x + mMouseOffset.x;
  origin.y = origin.y + mMouseOffset.y;
  origin.z = origin.z + mMouseOffset.z;

  cSPVector3 snapped;
  cSPEditorBlock* hit = FUN_004a3dc0(block, &mPileList, origin, dir, &snapped);
  if (hit) {
    if (hit == block->mpParent)
      return true;

    mPosition = snapped;
    cSPVector3 delta;
    delta.x = startPos.x - snapped.x;
    delta.y = startPos.y - snapped.y;
    delta.z = startPos.z - snapped.z;

    SnapBlockToSocket(block, &mPileList, hit);

    mMouseOffset.x = mMouseOffset.x + delta.x;
    mMouseOffset.y = mMouseOffset.y + delta.y;
    mMouseOffset.z = mMouseOffset.z + delta.z;

    SetSymmetricBlocksUIState(block, &mPileList, 0);
    FUN_004a6d20(block, &mPileList, 1, 0, 0, 0, 1, 1);
  } else {
    if ((block->mFlagsA >> 12) & 1)
      FUN_004a1070(block);

    int socket = MoveBlockStacking(block, &mPileList, origin, dir);
    if (model) {
      if (socket == 0 || model->GetPhysicsWorld()->mpFloorBody != (void*)socket) {
        block->SetIsOnGround(false);
      } else {
        block->mbOnFloor = 1;
        if (block->mpSymmetric)
          block->mpSymmetric->mbOnFloor = 1;
      }
    }

    float scale = g_defaultBlockScale;
    if (block->mpModel)
      scale = block->mpModel->GetScale() * g_stackScaleFactor;
    bool positioned = FUN_004982b0(block, 0, scale, 1);

    mPosition = block->mPosition;

    if (!positioned) {
      bool flagC = block->Unk43bbc0(0);
      cSPMatrix3 outRot;
      float score = GetAlignmentPosition(block, &mPileList, startPos, block->mBaseOrientation,
                                        &mPosition, &outRot, &flagC, 1, block->mBaseOrientation);
      if (score == g_minusOne) {
        if (mAlignmentState) {
          KillSeti(g_killSetAlignmentOff);
          mAlignmentState = false;
        }
      } else if (!mAlignmentState) {
        KillSeti(g_killSetAlignmentOn);
        mAlignmentState = true;
      }

      if (score == g_minusOne || score <= g_alignmentEpsilon) {
        block->SetPosition(startPos, true);
      } else {
        block->SetPosition(mPosition, true);
        block->SetIsOnGround(flagC);
      }
    }

    FUN_00496300(block, &mPileList, origin, dir, startPos, 0);
    SetSymmetricBlocksUIState(block, &mPileList, 0);
    FUN_004a6d20(block, &mPileList, 1, 0, 0, 0, 1, 1);

    if ((block->mFlagsA >> 15) & 1)
      SetSymmetricBlocksUIState(block, &mPileList, 0);
  }
  return true;
}

// @ 0x005bc630
bool cSPEditorManipulationStackingSimple::OnMouseUp(unsigned int button, float x, float y,
                                                    unsigned int flags) {
  (void)button; (void)x; (void)y; (void)flags;
  if (mChangedObject) {
    cSPEditorBlock* block = mBlock.mpObject;
    unsigned int id = 0;
    bool post = false;
    if (mOriginalParent) {
      if (block->mpParent) { id = 0xda95baa5u; post = true; }
      else { id = 0x0428e920u; post = true; }
    } else if (block->mpParent) {
      id = 0x8e04ce1au;
      post = true;
    }
    if (post) {
      void* raw = EASTL_allocator_allocate(0x30, kEditorAllocName, 0, 0, 0, 0);
      cSPEditorAnimatedEventInfo* ev = raw ? new (raw) cSPEditorAnimatedEventInfo() : 0;
      if (ev)
        ev->AddRef();
      cSPEditorModel* model = block ? block->mpModel : 0;
      ev->MessagePost(id, block, model, 0, false, 0.0f, 0, -1, 1.0f);
      if (ev)
        ev->Release();
    }
  }

  int count = (int)(mEffectList.mpEnd - mEffectList.mpBegin);
  for (int i = 0; i < count; ++i)
    mEffectList.mpBegin[i]->Update(0);

  DeleteInvalidBlocks(mBlock.mpObject, &mPileList);
  if (mBlock.mpObject->NeedPostUpdate())
    FUN_0049cfd0(mBlock.mpObject);
  return true;
}

// @ 0x005bcaa0
bool cSPEditorManipulationStackingSimple::DoOnMouseDown(unsigned int button, float x, float y,
                                                        unsigned int flags) {
  (void)button; (void)flags;
  cSPEditorBlock* block = mBlock.mpObject;
  cSPEditorModel* model = block->mpModel;
  if (model)
    model->AddRef();

  mPileList.erase(mPileList.mpBegin, mPileList.mpEnd);
  BuildPileList(block, &mPileList, 0);

  BlockRef* first = mPileList.mpBegin;
  BlockRef* last = mPileList.mpEnd;
  while (first != last && first->mpObject != block)
    ++first;
  if (first != last)
    first = RemoveCopyBlocks(first + 1, last, first, &mBlock);
  mPileList.erase(first, last);

  RecordBlockAndPileHistory(block, &mPileList);
  if (!model->UsingSymmetry())
    ReleaseRefs(block, &mPileList);

  if (!((block->mFlagsA >> 12) & 1)) {
    if (((block->mFlagsB >> 12) & 1) || ((block->mFlagsB >> 13) & 1)) {
      mEffectList = FUN_004a37f0(block->mpModel, 0x6027fb5a);
    }
    if (mEffectList.size() == 0) {
      ((cReporter*)FUN_0067cac0())->Report((const char*)0x0f49e842);
    }
  }

  SetSymmetricBlocksUIState(block, &mPileList, 0);
  mX = x;
  mY = y;

  cSPVector3 alignedPos = block->mPosition;
  cSPMatrix3 localRot(block->mOrientation);
  bool flagC = block->Unk43bbc0(0);
  float score = GetAlignmentPosition(block, &mPileList, block->mPosition,
                                     cSPMatrix3(block->mBaseOrientation),
                                     &alignedPos, &localRot, &flagC, 1,
                                     cSPMatrix3(block->mBaseOrientation));
  if (score > g_minusOne)
    mUnk70 = true;

  if (model)
    model->Release();
  return true;
}

}  // namespace SP

namespace eastl {
// @ 0x005bc9b0
template <typename T, typename Alloc>
vector<T, Alloc>& vector<T, Alloc>::operator=(const vector<T, Alloc>& x) {
  if (this != &x) {
    unsigned int n = (unsigned int)(x.mpEnd - x.mpBegin);          // src element count
    if (n > (unsigned int)(mpCapacity - mpBegin)) {                // no room: reallocate
      T* p = (T*)Grow(n, x.mpBegin, x.mpEnd);
      if (mpBegin && ((int*)mpBegin)[-1] != 0)
        EASTL_allocator_deallocate(mpBegin);
      mpBegin = p;
      mpCapacity = p + n;
      mpEnd = p + n;
      return *this;
    }
    unsigned int cur = (unsigned int)(mpEnd - mpBegin);            // this element count
    if (n > cur) {
      memcpy(mpBegin, x.mpBegin, cur * sizeof(T));
      memcpy(mpEnd, x.mpBegin + cur, (const char*)x.mpEnd - (const char*)(x.mpBegin + cur));
      mpEnd = mpBegin + n;
      return *this;
    }
    memcpy(mpBegin, x.mpBegin, (const char*)x.mpEnd - (const char*)x.mpBegin);
    mpEnd = mpBegin + n;
  }
  return *this;
}

// Instantiated so the operator= above is emitted with the retail symbol name.
template class vector<EA::Swarm::cIVisualEffect*, sp_vector_allocator>;
}  // namespace eastl
