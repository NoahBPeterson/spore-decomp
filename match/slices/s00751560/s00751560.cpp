// slice s00751560 -- SP::cModelWorld background-load / highlight / group teardown helpers.
//
// Region: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE2 (EH prologue, no stack cookie).
// These functions are dominated by inlined EASTL/intrusive container primitives
// and AutoRefCount release sequences, so they are not byte-exact.
// See partial.txt / nonmatching.txt.

#include "types.h"
#include <math.h>
#include <string.h>
#include <xmmintrin.h>

namespace SP {

// ---------------------------------------------------------------------------
// external callees (addresses are the original VAs)
// ---------------------------------------------------------------------------
extern "C" void* Fun_0067dcc0();                                    // 0x067dcc0  MessageServer
extern "C" void* Fun_0067de30();                                    // 0x067de30  PropertyManager
extern "C" bool  Fun_006a08b0(void*, uint32_t, uint32_t*, void**);  // 0x06a08b0  GetPropertyAsFloatArray
extern "C" void* Fun_011e0744(void*, const void*, unsigned);        // 0x011e0744  memcpy
extern "C" void  Fun_00f47380(void*);                               // 0x00f47380  operator delete
extern "C" void  Fun_005ae5d0(void*, void*, void*);                 // 0x005ae5d0  destroy range
extern "C" void* Fun_005f4e10(void*, void*, void*);                 // 0x005f4e10  eastl copy_impl
extern "C" void  Fun_00747340(void*);                               // 0x00747340  model factory reset
extern "C" void  Fun_007478b0(void*);                               // 0x007478b0  fixed-vector teardown

extern "C" float gSporeDefaultTranslation[3];                       // 0x0162eb0c
extern "C" float gSporeDefaultRotation[9];                          // 0x0162ec4c

struct cModelWorld;

inline uint32_t PtrBits(const void* p) {
  return static_cast<uint32_t>(reinterpret_cast<uintptr_t>(p));
}

inline float BitsToFloat(uint32_t b) {
  float f;
  memcpy(&f, &b, 4);
  return f;
}

inline uint32_t FloatToBits(float f) {
  uint32_t b;
  memcpy(&b, &f, 4);
  return b;
}

// ---------------------------------------------------------------------------
// small supporting types
// ---------------------------------------------------------------------------
struct Matrix3 {                                    // rw::math::fpu::Matrix33Template<float,0>
  float m[9];                                       // +0x00
  void Assign(const void* src);                     // 0x041cb40 (thiscall)
};

// intrusive reference-counted base: vtable at +0x00, count at +0x04
struct cRefCounted {
  void**   mpVtbl;                                  // +0x00
  uint32_t mRefCount;                               // +0x04
  void AddRef();                                    // vtable slot 0
  void Release();                                   // vtable slot 1
};

inline void DecRefInline(cRefCounted* p) {
  uint32_t c = p->mRefCount;
  p->mRefCount = c - 1;
  if (c - 1 == 0) {
    p->mRefCount = 1;
    reinterpret_cast<void(__thiscall*)(cRefCounted*, int)>(p->mpVtbl[0])(p, 1);
  }
}

// AutoRefCount<T>::operator= (inline add / release)
inline void AssignObj(cRefCounted** dst, cRefCounted* src) {
  if (src != *dst) {
    if (src) src->mRefCount = src->mRefCount + 1;
    cRefCounted* old = *dst;
    *dst = src;
    if (old) DecRefInline(old);
  }
}

struct cSPTransform {                             // 0x38 bytes (dev PDB)
  uint16_t mFlags;                                  // +0x00
  uint16_t mModificationCount;                      // +0x02
  float    mTranslation[3];                         // +0x04
  float    mScale;                                  // +0x10
  Matrix3  mRotation;                               // +0x14
  cSPTransform& operator=(const cSPTransform& o);   // 0x00537dc0
};

// SP::cMWGroup::cModelInfo (dev PDB, 0x3c bytes)
struct cModelInfo {
  void*        mObject;                             // +0x00 (SP::cMWObject*)
  cSPTransform mLocalTransform;                     // +0x04
};

// what cQueueElem::mpModel points at (= the model instance base + 8)
struct cJobTarget {
  void*    mpObj;                                   // +0x00 (polymorphic; vtable slot 0x170)
  uint32_t mFlags;                                  // +0x04
  uint8_t  mPad08[0x38];                            // +0x08
  int32_t  mRefCount;                               // +0x40
};

struct VecModelInfo {
  cModelInfo* mpBegin;                              // +0x00
  cModelInfo* mpEnd;                                // +0x04
  cModelInfo* mpCapacity;                           // +0x08
  void  resize(uint32_t n);                         // 0x00751ed0 (thiscall, ret 4)
  void  DoInsertValues(cModelInfo* at, uint32_t n, const cModelInfo* v);  // 0x0074f5d0
  // eastl::vector::erase(first, last): move the tail down, then drop (last - first) elements (trivial dtor)
  __forceinline cModelInfo* erase(cModelInfo* first, cModelInfo* last) {
    cModelInfo* const end = mpEnd;
    cModelInfo* d = first;
    for (cModelInfo* s = last; s != end; ++s, ++d)
      *d = *s;
    mpEnd -= (last - first);
    return first;
  }
};

// SpVector<float>
struct SpVectorFloat {
  float* mpBegin;                                   // +0x00
  float* mpEnd;                                     // +0x04
  float* mpCapacity;                                // +0x08
  void   resize(int n);                             // 0x04afc80 (thiscall, ret 4)
};

struct cProperty {                                  // EA::cProperty
  uint8_t   pad_0[0x12];                            // +0x00
  uint16_t  mType;                                  // +0x12
  uint32_t* GetUInt();                              // 0x041ea00 (thiscall)
  float*    GetFloat();                             // 0x041ea70 (thiscall)
};

struct cJobManager {
  int  ContinueJob();                               // 0x068f970 (thiscall)
  bool Cancel(bool b);                              // 0x0692400 (thiscall)
};

// a queued background job (0x1c bytes) -- also the head of a cLoadEntry
struct cQueueElem {
  void*         mpModel;                            // +0x00
  cRefCounted*  mpRef;                              // +0x04
  uint32_t      mF08;                               // +0x08
  uint32_t      mF0c;                               // +0x0c
  uint32_t      mF10;                               // +0x10
  void*         mpCb14;                             // +0x14
  void*         mpCbArg18;                          // +0x18
};

// one background-load / feedback-job slot (0x50 bytes)
struct cLoadEntry {
  cQueueElem     mElem;                             // +0x00 .. +0x1b
  uint8_t        mActive;                           // +0x1c
  uint8_t        mPad1d[0x03];                      // +0x1d
  cJobManager*   mpJob;                             // +0x20
  cJobManager*   mpJobMgr;                          // +0x24
  uint8_t        mPad28[0x0c];                      // +0x28
  cRefCounted*   mpRef34;                           // +0x34
  cRefCounted*   mF38[3];                           // +0x38
  cRefCounted*   mpF44;                             // +0x44
  cRefCounted*   mpF48;                             // +0x48
  uint8_t        mPad4c[0x04];                      // +0x4c

  bool Start(cQueueElem* job);                      // 0x074fea0  cFeedbackJobs::Start
  void QueueDone();                                 // 0x074b170  cloadqueue_b170
};

// the queue tail object living at cLoadQueue+0x284 (cModelWorld+0x598)
struct cQueueTail {
  uint8_t        mPad00[0x08];                      // +0x00 .. +0x07
  void TailDtor();                                  // 0x07477d0 (thiscall, ecx = this)
};

// the load queue sub-object living at cModelWorld+0x314
struct cLoadQueue {
  cModelWorld*   mBase;                             // +0x00
  cLoadEntry     mEntries[8];                       // +0x04  -> cModelWorld+0x318
  cQueueTail     mTail;                             // +0x284 -> cModelWorld+0x598
  cQueueElem*    mpCur;                             // +0x28c -> cModelWorld+0x5a0
  cQueueElem*    mpBuf;                             // +0x290 -> cModelWorld+0x5a4
  cQueueElem*    mpCurBufEnd;                       // +0x294 -> cModelWorld+0x5a8
  cQueueElem**   mpBufCursor;                       // +0x298 -> cModelWorld+0x5ac
  cQueueElem*    mpEnd;                             // +0x29c -> cModelWorld+0x5b0

  bool IsDone(void* arg);                           // 0x0747640
  void Update();                                    // 0x00751de0
};

// entry of the 8 x 0x20 load-queue initialised by cModelWorld::Init
struct cLoadEntry20 {
  uint32_t mF00;                                    // +0x00
  uint32_t mF04;                                    // +0x04
  uint32_t mF08;                                    // +0x08
  uint32_t mF0c;                                    // +0x0c
  void*    mF10;                                    // +0x10
  void*    mF14;                                    // +0x14
  void*    mpRef18;                                 // +0x18
  uint8_t  mF1c;                                    // +0x1c
  uint8_t  mPad1d[0x03];                            // +0x1d
};

struct cSPBoundingBox {
  uint32_t mMin[3];                                 // +0x00
  uint32_t mMax[3];                                 // +0x0c
  void TransformBy(void* xform);                    // 0x0409dd0 (thiscall)
};

// the model object a cLoadEntry carries; the entry's pointer aims 8 bytes in
struct cMWModel {
  uint32_t      mNode0;                             // +0x00
  uint32_t      mNode1;                             // +0x04
  void*         mF08;                               // +0x08
  uint32_t      mFlags;                             // +0x0c
  uint8_t       mPad10[0x30];                       // +0x10
  int32_t       mRefCount;                          // +0x40
  uint8_t       mPad44[0x2c];                       // +0x44
  uint16_t      mF70;                               // +0x70
  uint8_t       mPad72[0x02];                       // +0x72
  uint32_t      mF74;                               // +0x74
  cSPBoundingBox mBBox;                             // +0x78
  uint8_t       mPad90[0x0c];                       // +0x90
  cRefCounted*  mpSlots9c[6];                        // +0x9c .. +0xb3
  cRefCounted*  mpSlotsB4[6];                        // +0xb4 .. +0xcb
  uint8_t       mFlagsCC[6];                         // +0xcc .. +0xd1
  uint8_t       mPadD2[0x12];                       // +0xd2
  uint8_t       mXformE4[0x04];                      // +0xe4
  float         mFE8;                               // +0xe8
  float         mFEc;                               // +0xec
  float         mFF0;                               // +0xf0
  float         mFF4;                               // +0xf4
  uint8_t       mPadF8[0x40];                       // +0xf8
  uint32_t      mFlags138;                          // +0x138
};

// eastl::fixed_vector<cQueueElem, 32, ...> local view
struct cElemVec {
  cQueueElem* mpBegin;                              // +0x00
  cQueueElem* mpEnd;                                // +0x04
  cQueueElem* mpCapacity;                           // +0x08
  void*       mpPad0c;                              // +0x0c
  void*       mpInlineBuffer;                       // +0x10 (the fixed-vector inline storage == mpBegin)
  uint32_t    mPad14;                               // +0x14
  uint32_t    mPad18;                               // +0x18
  uint32_t    mPad1c;                               // +0x1c
  void DoInsertValue(cQueueElem* at, const cQueueElem* v);  // 0x074f420
  void Cleanup();                                   // 0x07478b0 (thiscall, ecx = this)
};

// SP::cIModelWorld: only slot 92 (+0x170) is called here
struct cMWObject;
struct cIModelWorld {
  virtual void v00();
  virtual void v01();
  virtual void v02();
  virtual void v03();
  virtual void v04();
  virtual void v05();
  virtual void v06();
  virtual void v07();
  virtual void v08();
  virtual void v09();
  virtual void v10();
  virtual void v11();
  virtual void v12();
  virtual void v13();
  virtual void v14();
  virtual void v15();
  virtual void v16();
  virtual void v17();
  virtual void v18();
  virtual void v19();
  virtual void v20();
  virtual void v21();
  virtual void v22();
  virtual void v23();
  virtual void v24();
  virtual void v25();
  virtual void v26();
  virtual void v27();
  virtual void v28();
  virtual void v29();
  virtual void v30();
  virtual void v31();
  virtual void v32();
  virtual void v33();
  virtual void v34();
  virtual void v35();
  virtual void v36();
  virtual void v37();
  virtual void v38();
  virtual void v39();
  virtual void v40();
  virtual void v41();
  virtual void v42();
  virtual void v43();
  virtual void v44();
  virtual void v45();
  virtual void v46();
  virtual void v47();
  virtual void v48();
  virtual void v49();
  virtual void v50();
  virtual void v51();
  virtual void v52();
  virtual void v53();
  virtual void v54();
  virtual void v55();
  virtual void v56();
  virtual void v57();
  virtual void v58();
  virtual void v59();
  virtual void v60();
  virtual void v61();
  virtual void v62();
  virtual void v63();
  virtual void v64();
  virtual void v65();
  virtual void v66();
  virtual void v67();
  virtual void v68();
  virtual void v69();
  virtual void v70();
  virtual void v71();
  virtual void v72();
  virtual void v73();
  virtual void v74();
  virtual void v75();
  virtual void v76();
  virtual void v77();
  virtual void v78();
  virtual void v79();
  virtual void v80();
  virtual void v81();
  virtual void v82();
  virtual void v83();
  virtual void v84();
  virtual void v85();
  virtual void v86();
  virtual void v87();
  virtual void v88();
  virtual void v89();
  virtual void v90();
  virtual void v91();
  virtual void DestroyModel(cMWObject* pModel, bool flag);   // +0x170
};

// SP::cMWObject (dev PDB, 0x44 bytes)
struct cMWObject {
  cIModelWorld* mWorld;                             // +0x00
  uint32_t      mFlags;                             // +0x04 (eastl::bitset<32>)
  cSPTransform  mTransform;                         // +0x08
  int           mRefCount;                          // +0x40
};

// SP::cMWGroupInternal (dev PDB): eastl::intrusive_list_node, then SP::cMWGroup (a cMWObject followed by
// eastl::fixed_vector<cModelInfo, 8> mObjects)
struct cMWGroupInternal {
  void*        mpNext;                              // +0x00
  void*        mpPrev;                              // +0x04
  cMWObject    mBase;                               // +0x08
  VecModelInfo mObjects;                            // +0x4c
  ~cMWGroupInternal();                              // 0x00751d00
};

// the model-reference vector eastl::vector<EA::AutoRefCount<cMWModel>, sp_vector_allocator>
// used at cModelWorld+0x5d0 / +0x710: slot stride 0x14, only begin/end are meaningful here
struct cAutorefVec {
  void** mpBegin;                                   // +0x00
  void** mpEnd;                                     // +0x04
  uint8_t mPad08[0x14 - 0x08];                      // +0x08
  void DestroyValues(void** first, void** last);    // 0x05f3680 (thiscall, ecx = this)
};

// intrusive list node / circular list whose anchor is the list object itself
struct cIntrusiveNode {
  cIntrusiveNode* mpNext;                           // +0x00
  cIntrusiveNode* mpPrev;                           // +0x04
};

struct cIntrusiveList {
  cIntrusiveNode mAnchor;                           // +0x00 (anchor.next, anchor.prev)
};

// the hier-grid helper at cModelWorld+0x118
struct cHierGrid {
  uint8_t mPad00[0x24];                             // +0x00
  void*   mpBegin;                                  // +0x24
  void*   mpEnd;                                    // +0x28
  uint8_t mPad2c[0x84 - 0x2c];                      // +0x2c
  bool Shutdown();                                  // 0x0704060 (thiscall, ecx = this)
};

struct cStub7470c0 {
  void F();                                         // 0x07470c0 (thiscall, ecx = this)
};

// ---------------------------------------------------------------------------
// SP::cModelWorld
// ---------------------------------------------------------------------------
class cModelWorld {
 public:
  void**       mpVtbl;                              // +0x000
  uint32_t     mF04;                                // +0x004
  uint8_t      mHandler[0x14];                      // +0x008 (handler passed to MessageServer)
  uint8_t      mInit;                               // +0x01c
  uint8_t      mPad1d[0x118 - 0x1d];                // +0x01d
  cHierGrid    mHierGrid;                           // +0x118 .. +0x19c
  cIntrusiveList mList19c;                          // +0x19c
  cIntrusiveList mList1a4;                          // +0x1a4
  cIntrusiveList mList1ac;                          // +0x1ac
  cLoadEntry20 mEntries20[8];                       // +0x1b4 .. +0x2b3
  uint8_t      mPad2b4[0x314 - 0x2b4];              // +0x2b4
  cLoadQueue   mQueue;                              // +0x314 .. +0x5b3
  uint8_t      mPad5b4[0x5cc - 0x5b4];              // +0x5b4
  uint8_t      mF5cc;                               // +0x5cc
  uint8_t      mPad5cd[0x5d0 - 0x5cd];              // +0x5cd
  cAutorefVec mGroupsA[16];                         // +0x5d0 (stride 0x14)
  cAutorefVec mGroupsB[16];                         // +0x710 (stride 0x14)
  uint8_t      mPad850[0x864 - 0x850];              // +0x850
  SpVectorFloat mVec864;                            // +0x864
  uint8_t      mPad870[0x878 - 0x870];              // +0x870
  float        mF878;                               // +0x878
  uint8_t      mPad87c[0x880 - 0x87c];              // +0x87c
  void*        mLighting;                           // +0x880
  uint32_t     mF884;                               // +0x884
  float        mF888;                               // +0x888
  float        mF88c;                               // +0x88c
  float        mF890;                               // +0x890
  uint32_t     mF894;                               // +0x894
  uint32_t     mF898;                               // +0x898

  bool Init();                                      // 0x00751ff0
  void UpdateHighlightProps();                      // 0x00751b30
  bool Shutdown();                                  // 0x007520e0
  void ShutdownModel(void* node);                   // 0x00746b90
  void FinishBackgroundLoad(cLoadEntry* e);         // 0x00751560
  void SubA920(cRefCounted* p, void* model, uint32_t v);  // 0x0074a920
};

// ---------------------------------------------------------------------------
// 00751ff0  cModelWorld::Init
// ---------------------------------------------------------------------------
// @ 0x00751ff0
bool cModelWorld::Init() {
  mInit = 1;
  mQueue.mBase = this;

  void* ms = Fun_0067dcc0();
  if (ms) {
    reinterpret_cast<void(__thiscall*)(void*, void*, uint32_t)>(
        (*(void***)ms)[0x20 / 4])(ms, mHandler, 0x00f62defu);
    reinterpret_cast<void(__thiscall*)(void*, void*, uint32_t)>(
        (*(void***)ms)[0x20 / 4])(ms, mHandler, 0x02495f34u);
  }

  for (int i = 0; i < 8; i++) {
    cLoadEntry20* e = &mEntries20[i];
    e->mF00 = 0xffffffffu;
    e->mF04 = 0;
    e->mF08 = 0;
    e->mF0c = 0;
    e->mF10 = 0;
    e->mF14 = 0;
    if (e->mpRef18) {
      void* o = e->mpRef18;
      e->mpRef18 = 0;
      reinterpret_cast<void(__thiscall*)(void*)>((*(void***)o)[1])(o);
    }
    e->mF1c = 1;
  }
  mEntries20[0].mF00 = 0;

  UpdateHighlightProps();
  return true;
}

// ---------------------------------------------------------------------------
// 00751ed0  VecModelInfo::resize
// ---------------------------------------------------------------------------
// @ 0x00751ed0
void VecModelInfo::resize(uint32_t n) {
  int32_t size = (int32_t)((char*)mpEnd - (char*)mpBegin) / 0x3c;
  if ((uint32_t)size < n) {
    cModelInfo def;
    def.mLocalTransform.mFlags = 0;
    def.mLocalTransform.mModificationCount = 0;
    def.mLocalTransform.mTranslation[0] = gSporeDefaultTranslation[0];
    def.mLocalTransform.mTranslation[1] = gSporeDefaultTranslation[1];
    def.mLocalTransform.mTranslation[2] = gSporeDefaultTranslation[2];
    def.mLocalTransform.mScale = 1.0f;
    def.mLocalTransform.mRotation.Assign(gSporeDefaultRotation);
    DoInsertValues(mpEnd, (uint32_t)((int32_t)n - size), &def);
  } else {
    cModelInfo* newEnd = mpBegin + n;
    Fun_005ae5d0(mpEnd, mpEnd, newEnd);
    int32_t diff = (int32_t)((char*)mpEnd - (char*)newEnd);
    int32_t q = diff / 0x3c;
    mpEnd = (cModelInfo*)((char*)mpEnd - q * 0x3c);
  }
}

// ---------------------------------------------------------------------------
// 00751de0  cLoadQueue::Update
// ---------------------------------------------------------------------------
// @ 0x00751de0
void cLoadQueue::Update() {
  for (int i = 0; i < 8; i++) {
    cLoadEntry* e = &mEntries[i];
    if (e->mActive) {
      int r = e->mpJobMgr->ContinueJob();
      if ((uint32_t)(r - 7) <= 1u) mBase->FinishBackgroundLoad(e);
      if (e->mActive) continue;
    }
    for (;;) {
      if (mpCur == mpEnd) break;
      e->Start(mpCur);
      cQueueElem* v = mpCur;
      if (v + 1 == mpCurBufEnd) {
        if (v->mpRef) reinterpret_cast<void(__thiscall*)(cRefCounted*)>(
            v->mpRef->mpVtbl[1])(v->mpRef);
        if (mpBuf) Fun_00f47380(mpBuf);
        mpBufCursor += 1;
        mpBuf = *mpBufCursor;
        mpCurBufEnd = mpBuf + 8;
        mpCur = mpBuf;
      } else {
        mpCur = v + 1;
        if (v->mpRef) reinterpret_cast<void(__thiscall*)(cRefCounted*)>(
            v->mpRef->mpVtbl[1])(v->mpRef);
      }
      if (e->mActive) break;
    }
  }
}

// ---------------------------------------------------------------------------
// 00751b30  cModelWorld::UpdateHighlightProps
// ---------------------------------------------------------------------------
// @ 0x00751b30
void cModelWorld::UpdateHighlightProps() {
  if (mLighting == 0) {
    void* pm = Fun_0067de30();
    if (mLighting) {
      void* o = mLighting;
      mLighting = 0;
      reinterpret_cast<void(__thiscall*)(void*)>((*(void***)o)[1])(o);
    }
    reinterpret_cast<void(__thiscall*)(void*, uint32_t, uint32_t, void*)>(
        (*(void***)pm)[0x2c / 4])(pm, 0x823d6818u, 0x40200100u, &mLighting);
  }
  if (mLighting) {
    cProperty* p = 0;
    void** vt = *(void***)mLighting;
    if (reinterpret_cast<bool(__thiscall*)(void*, uint32_t, cProperty**)>(
            vt[0x24 / 4])(mLighting, 0x40c44a05u, &p) && p->mType == 0xa)
      mF884 = *p->GetUInt();
  }
  if (mLighting) {
    cProperty* p = 0;
    void** vt = *(void***)mLighting;
    if (reinterpret_cast<bool(__thiscall*)(void*, uint32_t, cProperty**)>(
            vt[0x24 / 4])(mLighting, 0x298c3112u, &p) && p->mType == 0xd)
      mF888 = *p->GetFloat();
  }
  if (mLighting) {
    cProperty* p = 0;
    void** vt = *(void***)mLighting;
    if (reinterpret_cast<bool(__thiscall*)(void*, uint32_t, cProperty**)>(
            vt[0x24 / 4])(mLighting, 0x59d61047u, &p) && p->mType == 0xd)
      mF88c = *p->GetFloat();
  }
  if (mLighting) {
    cProperty* p = 0;
    void** vt = *(void***)mLighting;
    if (reinterpret_cast<bool(__thiscall*)(void*, uint32_t, cProperty**)>(
            vt[0x24 / 4])(mLighting, 0x8c0d0f88u, &p) && p->mType == 0xd)
      mF890 = *p->GetFloat();
  }

  uint32_t n    = 0;
  void*    data = 0;
  if (Fun_006a08b0(mLighting, 0x4c08536u, &n, &data)) {
    mVec864.resize((int)n);
    Fun_011e0744(mVec864.mpBegin, data, n * 4);
  } else {
    float* ep = mVec864.mpEnd;
    float* bp = mVec864.mpBegin;
    Fun_011e0744(bp, ep, 0);
    int32_t dropped = (int32_t)((char*)ep - (char*)bp) >> 2;
    mVec864.mpEnd = (float*)((char*)ep - dropped * 4);
  }

  if (mLighting) {
    cProperty* p = 0;
    void** vt = *(void***)mLighting;
    if (reinterpret_cast<bool(__thiscall*)(void*, uint32_t, cProperty**)>(
            vt[0x24 / 4])(mLighting, 0x4c08537u, &p) && p->mType == 0xd)
      mF878 = *p->GetFloat();
  }
}

// ---------------------------------------------------------------------------
// 007520e0  cModelWorld::Shutdown
// ---------------------------------------------------------------------------
// @ 0x007520e0
bool cModelWorld::Shutdown() {
  // empty both 16-entry model-reference vectors (erase(begin, end) on each)
  for (int i = 0; i < 16; i++) {
    cAutorefVec* a = &mGroupsA[i];
    void** ab = a->mpBegin;
    void** ae = a->mpEnd;
    a->DestroyValues(static_cast<void**>(Fun_005f4e10(ae, ae, ab)), ae);
    a->mpEnd = ab;

    cAutorefVec* b = &mGroupsB[i];
    void** bb = b->mpBegin;
    void** be = b->mpEnd;
    b->DestroyValues(static_cast<void**>(Fun_005f4e10(be, be, bb)), be);
    b->mpEnd = bb;
  }

  // unregister the message handlers
  void* ms = Fun_0067dcc0();
  if (ms) {
    reinterpret_cast<void(__thiscall*)(void*, void*, uint32_t, uint32_t)>(
        (*(void***)ms)[0x2c / 4])(ms, mHandler, 0x00f62defu, 0xffffd8f1u);
    reinterpret_cast<void(__thiscall*)(void*, void*, uint32_t, uint32_t)>(
        (*(void***)ms)[0x2c / 4])(ms, mHandler, 0x02495f34u, 0xffffd8f1u);
  }

  // cancel and drain the 8 load-queue entries
  for (int i = 0; i < 8; i++) {
    cLoadEntry* e = &mQueue.mEntries[i];
    if (e->mActive) {
      e->mpJob->Cancel(true);
      e->QueueDone();
    }
  }

  mQueue.mTail.TailDtor();

  // list A: destroy each group and drop the world reference
  {
    cIntrusiveList* list = &mList1ac;
    for (cIntrusiveNode* n = list->mAnchor.mpNext; n != &list->mAnchor; ) {
      cIntrusiveNode* prev = n->mpPrev;
      cIntrusiveNode* next = n->mpNext;
      prev->mpNext = next;
      next->mpPrev = prev;
      n->mpNext = 0;
      n->mpPrev = 0;
      reinterpret_cast<cMWGroupInternal*>(n)->~cMWGroupInternal();
      reinterpret_cast<void(__thiscall*)(void*)>(mpVtbl[0])(this);
      n = next;
    }
    for (cIntrusiveNode* m = list->mAnchor.mpNext; m != &list->mAnchor; ) {
      cIntrusiveNode* next = m->mpNext;
      m->mpPrev = 0;
      m->mpNext = 0;
      m = next;
    }
    list->mAnchor.mpPrev = &list->mAnchor;
    list->mAnchor.mpNext = &list->mAnchor;
  }

  // list B: shut down each model, destroy the stub, drop the world reference
  {
    cIntrusiveList* list = &mList19c;
    for (cIntrusiveNode* n = list->mAnchor.mpNext; n != &list->mAnchor; ) {
      cIntrusiveNode* prev = n->mpPrev;
      cIntrusiveNode* next = n->mpNext;
      prev->mpNext = next;
      next->mpPrev = prev;
      n->mpNext = 0;
      n->mpPrev = 0;
      ShutdownModel(n);
      reinterpret_cast<cStub7470c0*>(n)->F();
      reinterpret_cast<void(__thiscall*)(void*)>(mpVtbl[0])(this);
      n = next;
    }
    for (cIntrusiveNode* m = list->mAnchor.mpNext; m != &list->mAnchor; ) {
      cIntrusiveNode* next = m->mpNext;
      m->mpPrev = 0;
      m->mpNext = 0;
      m = next;
    }
    list->mAnchor.mpPrev = &list->mAnchor;
    list->mAnchor.mpNext = &list->mAnchor;
  }

  // list C: identical treatment
  {
    cIntrusiveList* list = &mList1a4;
    for (cIntrusiveNode* n = list->mAnchor.mpNext; n != &list->mAnchor; ) {
      cIntrusiveNode* prev = n->mpPrev;
      cIntrusiveNode* next = n->mpNext;
      prev->mpNext = next;
      next->mpPrev = prev;
      n->mpNext = 0;
      n->mpPrev = 0;
      ShutdownModel(n);
      reinterpret_cast<cStub7470c0*>(n)->F();
      reinterpret_cast<void(__thiscall*)(void*)>(mpVtbl[0])(this);
      n = next;
    }
    for (cIntrusiveNode* m = list->mAnchor.mpNext; m != &list->mAnchor; ) {
      cIntrusiveNode* next = m->mpNext;
      m->mpPrev = 0;
      m->mpNext = 0;
      m = next;
    }
    list->mAnchor.mpPrev = &list->mAnchor;
    list->mAnchor.mpNext = &list->mAnchor;
  }

  mF894 = 0;
  mF898 = 0;
  if (mHierGrid.mpBegin != mHierGrid.mpEnd)
    mHierGrid.Shutdown();
  mInit = 0;
  return true;
}

// ---------------------------------------------------------------------------
// 00751560  cModelWorld::FinishBackgroundLoad
// ---------------------------------------------------------------------------
// @ 0x00751560
void cModelWorld::FinishBackgroundLoad(cLoadEntry* e) {
  cMWModel* m = 0;
  if (e->mElem.mpModel)
    m = reinterpret_cast<cMWModel*>(static_cast<uint8_t*>(e->mElem.mpModel) - 8);

  if (m->mFlags138 & 0x80000000u) mF5cc = 1;

  for (int i = 0; i < 6; i++) {
    if (m->mpSlots9c[i]) {
      cRefCounted* p = m->mpSlots9c[i];
      m->mpSlots9c[i] = 0;
      DecRefInline(p);
    }
    if (m->mpSlotsB4[i]) {
      cRefCounted* p = m->mpSlotsB4[i];
      m->mpSlotsB4[i] = 0;
      DecRefInline(p);
    }
    m->mFlagsCC[i] = 0xff;
  }

  AssignObj(&m->mpSlots9c[0], e->mpRef34);
  AssignObj(&m->mpSlots9c[1], e->mF38[0]);
  AssignObj(&m->mpSlots9c[2], e->mF38[1]);
  AssignObj(&m->mpSlots9c[3], e->mF38[2]);
  AssignObj(&m->mpSlots9c[4], e->mpF48);
  if (m->mFlags138 & 0x20) AssignObj(&m->mpSlots9c[5], e->mpF44);

  Fun_00747340(m);

  cMWModel* mi = reinterpret_cast<cMWModel*>(m->mpSlots9c[0] ? m->mpSlots9c[0] : m->mpSlots9c[4]);
  if (mi) {
    if (!(m->mFlags & 0x10000u)) {
      m->mBBox.mMax[0] = PtrBits(mi->mpSlotsB4[0]);
      m->mBBox.mMax[1] = PtrBits(mi->mpSlotsB4[1]);
      m->mBBox.mMax[2] = PtrBits(mi->mpSlotsB4[2]);
      m->mBBox.mMin[0] = PtrBits(mi->mpSlots9c[3]);
      m->mBBox.mMin[1] = PtrBits(mi->mpSlots9c[4]);
      m->mBBox.mMin[2] = PtrBits(mi->mpSlots9c[5]);
      if (m->mFF4 != 1.0f || (m->mXformE4[0] & 6))
        m->mBBox.TransformBy(m->mXformE4);
    }
    if (!((m->mFlags >> 0x11) & 1u)) {
      m->mF74 = PtrBits(mi->mpSlotsB4[3]);
      if (m->mFF4 != 1.0f || (m->mXformE4[0] & 6)) {
        float s = BitsToFloat(m->mF74) * m->mFF4;
        m->mF74 = FloatToBits(s);
        float r = _mm_cvtss_f32(_mm_sqrt_ss(_mm_set_ss(
            m->mFE8 * m->mFE8 + m->mFEc * m->mFEc + m->mFF0 * m->mFF0)));
        m->mF74 = FloatToBits(r + s);
      }
    }
  }

  struct { void* mpModel; uint32_t mPad; } qarg;
  qarg.mpModel = &m->mF08;
  if (!mQueue.IsDone(&qarg)) {
    m->mFlags |= 0x4000u;
    if (e->mElem.mpCb14)
      reinterpret_cast<void(__cdecl*)(void*, void*)>(e->mElem.mpCb14)(
          &m->mF08, e->mElem.mpCbArg18);

    cQueueElem  buf[32];
    cElemVec    vec;
    vec.mpBegin    = buf;
    vec.mpEnd      = buf;
    vec.mpCapacity = buf + 32;
    vec.mpPad0c    = buf;
    vec.mpInlineBuffer = buf;
    vec.mPad14     = 0;
    vec.mPad18     = 0;
    vec.mPad1c     = 0;

    cQueueElem*  begin    = buf;
    cQueueElem*  cap      = buf + 32;
    cQueueElem*  jobEnd   = mQueue.mpCurBufEnd;
    cQueueElem** cursor   = mQueue.mpBufCursor;

    for (cQueueElem* job = mQueue.mpCur; job != mQueue.mpEnd; ) {
      if (job->mpRef == e->mElem.mpRef) {
        bool skip = false;
        for (int i = 0; i < 8; i++)
          if (mQueue.mEntries[i].mElem.mpModel == job->mpModel) { skip = true; break; }
        if (!skip &&
            ((e->mElem.mF10 & 0x20) || !(job->mF10 & 0x20))) {
          if (begin < cap) {
            cQueueElem* dst = begin;
            begin += 1;
            *dst = *job;
            if (dst->mpRef)
              reinterpret_cast<void(__thiscall*)(cRefCounted*)>(
                  dst->mpRef->mpVtbl[0])(dst->mpRef);
          } else {
            vec.DoInsertValue(begin, job);
          }
          job->mpModel = 0;
          if (job->mpRef) {
            cRefCounted* p = job->mpRef;
            job->mpRef = 0;
            reinterpret_cast<void(__thiscall*)(cRefCounted*)>(p->mpVtbl[1])(p);
          }
          job->mF08 = 0;
          job->mF0c = 0;
          job->mF10 = 0;
          job->mpCb14 = 0;
          job->mpCbArg18 = 0;
        }
      }
      job += 1;
      if (job == jobEnd) {
        cursor += 1;
        job = *cursor;
        jobEnd = job + 8;
      }
    }
    vec.mpEnd = begin;

    for (cQueueElem* it = buf; it != begin; it += 1) {
      cJobTarget*  tgt   = reinterpret_cast<cJobTarget*>(it->mpModel);
      cRefCounted* obj   = it->mpRef;
      void*        cb    = it->mpCb14;
      void*        cbArg = it->mpCbArg18;
      if (tgt) tgt->mRefCount = tgt->mRefCount + 1;
      if (obj) reinterpret_cast<void(__thiscall*)(cRefCounted*)>(
          obj->mpVtbl[0])(obj);
      SubA920(obj, tgt ? static_cast<void*>(reinterpret_cast<uint8_t*>(tgt) - 8)
                       : 0, it->mF10);
      if (cb) reinterpret_cast<void(__cdecl*)(void*, void*)>(cb)(tgt, cbArg);
      if (obj) reinterpret_cast<void(__thiscall*)(cRefCounted*)>(
          obj->mpVtbl[1])(obj);
      if (tgt) {
        if (tgt->mRefCount < 2) {
          uint32_t b = (tgt->mFlags >> 31) & 1u;
          void*    o = tgt->mpObj;
          reinterpret_cast<void(__thiscall*)(void*, uint32_t)>(
              (*(void***)o)[0x170 / 4])(o, b);
        } else {
          tgt->mRefCount = tgt->mRefCount - 1;
        }
      }
    }
    vec.Cleanup();
  }

  e->QueueDone();
  m->mF70 = (uint16_t)(m->mF70 + 1);
}

}  // namespace SP

// ---------------------------------------------------------------------------
// 00751d00  cMWGroupInternal::~cMWGroupInternal
// ---------------------------------------------------------------------------
namespace SP {
// @ 0x00751d00
cMWGroupInternal::~cMWGroupInternal() {
  int n = (int)(mObjects.mpEnd - mObjects.mpBegin);
  for (int i = 0; i < n; ++i) {
    cMWObject* o = (cMWObject*)mObjects.mpBegin[i].mObject;
    if (o) {
      if (o->mRefCount > 1)
        o->mRefCount--;
      else
        o->mWorld->DestroyModel(o, ((o->mFlags >> 31) & 1) != 0);   // mFlags.test(31)
    }
  }
  mObjects.erase(mObjects.mpBegin, mObjects.mpEnd);
}
}  // namespace SP
