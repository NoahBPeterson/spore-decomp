// Slice s0074d4b0: cModelWorld model creation/filter helpers.
// /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "../../include/types.h"
#include <math.h>
#include <string.h>

void* operator new(size_t, void* p) throw() { return p; }
void operator delete(void*, void*) throw() {}

// ---------------------------------------------------------------------------
// Stubs (offsets from the disassembly; retail layout)
// ---------------------------------------------------------------------------
struct IRefObj { virtual int AddRef(); virtual int Release(); };

// refcounted property list handle: AddRef vt+0, Release vt+4
struct PropRef {
  IRefObj* p;
  PropRef() : p(0) {}
  ~PropRef() { if (p) p->Release(); }
  void reset() {
    if (p) {
      IRefObj* t = p;
      p = 0;
      t->Release();
    }
  }
};

struct IPropMgr {
  virtual void pv0(); virtual void pv1(); virtual void pv2(); virtual void pv3();
  virtual void pv4(); virtual void pv5(); virtual void pv6(); virtual void pv7();
  virtual void pv8(); virtual void pv9(); virtual void pv10();
  virtual bool GetPropertyList(uint32_t id, uint32_t group, IRefObj** out);   // +0x2c
};
IPropMgr* __cdecl PropertyManager();                                          // 0x0067de30

// cCookie (SP::Pollen::cCookie): refcount at +4, deleting dtor at vtable +0
struct cCookie {
  virtual void* DeletingDtor(int flags);
  int mRefCount;
  char pad8[0xa8 - 8];
  float mV0[3];          // +0xa8
  float mV1[3];          // +0xb4
  float mScale;          // +0xc0
  char padc4[0xcc - 0xc4];
  uint8_t mFlagCC;       // +0xcc
  void FUN_0073ab40(uint32_t v);   // 0x0073ab40
};
struct CookieRef {
  cCookie* p;
  CookieRef() : p(0) {}
  ~CookieRef() {
    if (p) {
      int n = p->mRefCount - 1;
      p->mRefCount = n;
      if (n == 0) {
        p->mRefCount = 1;
        p->DeletingDtor(1);
      }
    }
  }
  CookieRef& operator=(const CookieRef& o);   // 0x00609ea0 AutoRefCount<cCookie>::operator=
};

struct cB4Obj {
  uint32_t first;
  char pad[0x18 - 4];
  void* FUN_007454f0();           // 0x007454f0
};

// model node: intrusive list links at +0/+4, the model object itself starts at +8
struct cModelWorld;
#pragma pack(push, 4)
struct cModelNode {
  cModelNode* mpNext;       // +0x00
  cModelNode* mpPrev;       // +0x04
  uint32_t obj8;            // +0x08 (model object starts here)
  uint32_t mFlags;          // +0x0c
  char mXform[0x38];        // +0x10 cSPTransform
  char pad48[4];
  uint64_t mMask;           // +0x4c (type mask)
  char pad54[0x65 - 0x54];
  uint8_t mLod;             // +0x65
  char pad66[0x74 - 0x66];
  float mRadius;            // +0x74
  float mBoxMin[3];         // +0x78
  float mBoxMax[3];         // +0x84
  char pad90[0x98 - 0x90];
  IRefObj* mProps;          // +0x98
  cCookie* mCookie;         // +0x9c
  char pada0[0xac - 0xa0];
  cCookie* mCookie2;        // +0xac
  char padb0[4];
  cB4Obj mB4;               // +0xb4
  uint8_t mFlagCC;          // +0xcc
  char padcd[0x12c - 0xcd];
  uint32_t mFlags12c;       // +0x12c
  char pad130[0x138 - 0x130];
  uint32_t mCreateFlags;    // +0x138
  cModelNode(cModelWorld* world);   // 0x00746e50
  void* Obj() { return (char*)this + 8; }
};
#pragma pack(pop)

struct cFixedAlloc {          // EA::Allocator fixed pool at 0x0162ed08
  char pad[0x10];
  void** mpFree;              // +0x10 (0x0162ed18) head of the free list
  bool AddCore(int a, int b); // 0x00926650
  void* Alloc();              // 0x004fde40
};
extern cFixedAlloc gModelNodeAlloc;

struct PtrVec {
  void** mpBegin; void** mpEnd; void** mpCapacity;
  void DoInsertValue(void** pos, void* const& v);       // 0x006c1570
  void push_back(void* const& v) {
    if (mpEnd < mpCapacity) {
      void** e = mpEnd;
      mpEnd = e + 1;
      if (e) *e = v;
    } else {
      DoInsertValue(mpEnd, v);
    }
  }
  void PushObj(void* obj) {     // push_back of a temporary: the value lives in a stack slot
    void** e = mpEnd;
    void* v = obj;
    if (e < mpCapacity) {
      mpEnd = e + 1;
      if (e) *e = v;
    } else {
      DoInsertValue(e, v);
    }
  }
  void clear() {
    void** first = mpBegin;
    void** last = mpEnd;
    memcpy(first, last, (size_t)((char*)mpEnd - (char*)last));
    mpEnd = (void**)((char*)mpEnd - ((char*)last - (char*)first));
  }
};

// query filter passed to the collectors
#pragma pack(push, 4)
struct cModelFilter {
  uint64_t incl;               // +0x00 required type bits (0 = any)
  uint64_t excl;               // +0x08 excluded type bits
  bool (__cdecl* pred)(void* obj);   // +0x10 optional predicate on the model object
  uint8_t lod;                 // +0x14 default detail level
  uint8_t fl;                  // +0x15 bit0: use per-node lod, bit1: force unit scale
  uint16_t pad;
};
#pragma pack(pop)

struct cSPTransform {          // size 0x38
  uint16_t mFlags;             // +0
  uint16_t mModCount;          // +2
  float mT[3];                 // +4
  float mScale;                // +0x10
  float mRot[9];               // +0x14
  cSPTransform& operator=(const cSPTransform& o);   // 0x00537dc0
};

struct cAppProps { char pad[0x2c]; int f2c; char pad30[0x94 - 0x30]; int f94; char pad98[0x118 - 0x98]; int f118; };
struct cGlobalA { char pad[0x3c]; cAppProps* sub; };
extern cGlobalA* g_015fd918;    // 0x015fd918 (SP::sAppProperties)

extern float gV3Init[3];        // 0x0162eb0c default translation
extern float gRotInit[9];       // 0x0162ec4c default rotation
extern float gOne;              // 0x01485720 1.0f
extern float gFltMax;           // 0x0140d674  3.4028235e38
extern float gNegFltMax;        // 0x013f51ac -3.4028235e38
extern float gEps;              // 0x013f1168 1e-10
bool __cdecl CreateModelInstance(uint32_t a, uint32_t b, CookieRef* out, uint32_t lod);   // 0x00754ba0 SP::CreateModelInstance
uint32_t __cdecl FUN_007453d0(void* a, cCookie* c, uint32_t flags);                        // 0x007453d0
const float* __cdecl FUN_0069b1c0(float* out, const float* dir, const float* up);          // 0x0069b1c0 builds a 3x3 basis
struct cBBox { float mn[3]; float mx[3]; };
struct cCapsule6 { float a[6]; };
bool __cdecl FUN_00748ad0(const float* p0, const float* p1, cSPTransform* xf, cBBox* box, const float* rot,
                          cModelNode* node, int kind, int zero, float radius);              // 0x00748ad0
bool __cdecl FUN_007442c0(const float* p0, const float* p1, cSPTransform* xf, cCapsule6 seg, int zero,
                          float radius);                                                    // 0x007442c0

struct cModelWorldQuery { int FUN_00702860(const float* p0, const float* p1, float radius, int max, cModelNode** out); };  // 0x00702860

struct cModelWorld {
  char pad0[0x1e];
  uint8_t mbFallback;                  // +0x1e
  char pad1f[0x118 - 0x1f];
  cModelWorldQuery mQuery;             // +0x118 (spatial index)
  char pad11c[0x13c - 0x11c];
  void* mpIndexBegin;                  // +0x13c
  void* mpIndexEnd;                    // +0x140
  char pad144[0x19c - 0x144];
  cModelNode* mListA_next;             // +0x19c sentinel of the active list
  cModelNode* mListA_prev;             // +0x1a0
  cModelNode* mListB_next;             // +0x1a4 sentinel of the secondary list
  cModelNode* mListB_prev;             // +0x1a8
  char pad1ac[0x894 - 0x1ac];
  int mCount894;                       // +0x894
  int mCount898;                       // +0x898

  void* CreateModel(uint32_t a, uint32_t b, uint32_t flags);       // 0x0074d4b0
  bool CollectModels(PtrVec* out, const cModelFilter* f);          // 0x0074d870
  bool CollectSweep(const float* p0, const float* p1, PtrVec* out, const cModelFilter* f, float radius);  // 0x0074d990
  void UpdateFromPropList(IRefObj* props, cModelNode* node, uint32_t flags, int z);   // 0x0074b760
  void ScheduleForLoad(cModelNode* node, IRefObj* props, uint32_t a, uint32_t b);     // 0x0074c910
  cModelNode* ListAEnd() { return (cModelNode*)&mListA_next; }
  cModelNode* ListBEnd() { return (cModelNode*)&mListB_next; }
};

// intrusive list push_back at sentinel s
static inline void ListPushBack(cModelNode* s, cModelNode* n) {
  n->mpPrev = s->mpPrev;
  n->mpNext = s;
  s->mpPrev = n;
  n->mpPrev->mpNext = n;
}

// ---------------------------------------------------------------------------
// @ 0x0074D4B0  SP::cModelWorld::CreateModel
// ---------------------------------------------------------------------------
void* cModelWorld::CreateModel(uint32_t a, uint32_t b, uint32_t flags)
{
  PropRef props;
  IPropMgr* pm = PropertyManager();
  props.reset();
  if (pm->GetPropertyList(a, b, &props.p)) {
    void* mem;
    for (;;) {
      if (gModelNodeAlloc.mpFree) {
        mem = gModelNodeAlloc.mpFree;
        gModelNodeAlloc.mpFree = (void**)*gModelNodeAlloc.mpFree;
        break;
      }
      if (!gModelNodeAlloc.AddCore(0, 0)) {
        mem = 0;
        break;
      }
    }
    cModelNode* n = mem ? new (mem) cModelNode(this) : 0;
    uint32_t secondary = flags & 0x80000000;
    if (!secondary) {
      ListPushBack(ListAEnd(), n);
      n->mFlags |= 0x8000;
    } else {
      ListPushBack(ListBEnd(), n);
      n->mFlags |= 1;
    }
    n->mCreateFlags = flags;
    // AutoRefCount assignment: n->mProps = props
    IRefObj* np = props.p;
    IRefObj* old = n->mProps;
    if (np != old) {
      if (np) np->AddRef();
      n->mProps = np;
      if (old) old->Release();
    }
    mCount894 += 1;
    if (flags & 0x10) {
      n->mFlags |= 0x4000;
      UpdateFromPropList(props.p, n, flags, 0);
    } else {
      if (!secondary) mCount898 += 1;
      ScheduleForLoad(n, props.p, a, b);
    }
    n->mFlags12c = n->mFlags;
    return n->Obj();
  }

  if (!mbFallback) return 0;

  CookieRef res;
  uint32_t lod = flags & 1;
  if (!CreateModelInstance(a, b, &res, lod)) {
    if (g_015fd918->sub->f94 == 0) return 0;
    if (!CreateModelInstance(0x1565205f, 0xd94352ed, &res, lod)) return 0;
  }
  void* mem = gModelNodeAlloc.Alloc();
  cModelNode* n = mem ? new (mem) cModelNode(this) : 0;
  ListPushBack(ListAEnd(), n);
  mCount894 += 1;
  mCount898 += 1;
  n->mFlags |= 1;
  n->mFlags |= 0x8000;
  n->mCreateFlags = flags;
  {
    // n->mCookie = res (AutoRefCount<cCookie>::operator=)
    ((CookieRef*)&n->mCookie)->operator=(res);
  }
  cCookie* ck = res.p;
  n->mRadius = ck->mScale;
  n->mBoxMax[0] = ck->mV1[0];
  n->mBoxMax[1] = ck->mV1[1];
  n->mBoxMax[2] = ck->mV1[2];
  n->mBoxMin[0] = ck->mV0[0];
  n->mBoxMin[1] = ck->mV0[1];
  n->mBoxMin[2] = ck->mV0[2];
  FUN_007453d0(n->mB4.FUN_007454f0(), n->mCookie, flags);
  uint32_t v = n->mB4.first;
  n->mCookie->FUN_0073ab40(v);
  n->mFlagCC = 0;
  n->mFlags |= 0x4000;
  n->mFlags12c = n->mFlags;
  return n->Obj();
}

// ---------------------------------------------------------------------------
// @ 0x0074D870  cModelWorld: collect active models matching a filter
// ---------------------------------------------------------------------------
bool cModelWorld::CollectModels(PtrVec* out, const cModelFilter* f)
{
  cModelNode* end = ListAEnd();
  if (f->pred == 0 && f->incl == 0 && f->excl == 0) {
    for (cModelNode* n = mListA_next; n != end; n = n->mpNext) {
      if (n->mFlags & 1) {
        out->PushObj(n->Obj());
      }
    }
    return out->mpBegin != out->mpEnd;
  }
  for (cModelNode* n = mListA_next; n != end; n = n->mpNext) {
    if (n->mFlags & 1) {
      if ((f->incl == 0 || (n->mMask & f->incl) != 0) &&
          (n->mMask & f->excl) == 0 &&
          (f->pred == 0 || f->pred(n->Obj()))) {
        out->PushObj(n->Obj());
      }
    }
  }
  return out->mpBegin != out->mpEnd;
}

// ---------------------------------------------------------------------------
// @ 0x0074D990  cModelWorld: sphere sweep (p0 -> p1, radius) over models, appends hits to out
// ---------------------------------------------------------------------------
static __forceinline void SweepNode(cModelNode* n, const float* p0, const float* p1, PtrVec* out,
                                    const cModelFilter* f, float radius, cSPTransform& xf, cBBox& box,
                                    const float* rot)
{
  if (!(n->mFlags & 1)) return;
  if (!(f->incl == 0 || (n->mMask & f->incl) != 0)) return;
  if ((n->mMask & f->excl) != 0) return;
  if (f->pred && !f->pred(n->Obj())) return;

  uint32_t lod;
  if ((f->fl & 1) && ((n->mFlags >> 8) & 1))
    lod = n->mLod;
  else
    lod = f->lod;
  xf = *(cSPTransform*)n->mXform;
  if (((n->mFlags >> 7) & 1) || (f->fl & 2)) {
    xf.mModCount = xf.mModCount + 1;
    xf.mScale = gOne;
  }
  float R = n->mRadius * xf.mScale + radius;
  float cx = p0[0] - xf.mT[0];
  float dx = p1[0] - p0[0];
  float dy = p1[1] - p0[1];
  float cy = p0[1] - xf.mT[1];
  float dz = p1[2] - p0[2];
  float cz = p0[2] - xf.mT[2];
  float b = (dx * cx + dy * cy) + dz * cz;
  float a = (dx * dx + dy * dy) + dz * dz;
  float disc = b * b - (((cx * cx + cy * cy) + cz * cz) - R * R) * a;
  if (!(0.0f <= disc)) return;
  float s = sqrtf(disc);
  float t0 = -b - s;
  if (!(0.0f <= s - b) || !(t0 <= a)) return;

  if (lod < 3 || !n->mCookie || !n->mCookie->mFlagCC) {
    if (lod > 1 && n->mCookie2 && n->mCookie2->mFlagCC) {
      if (!FUN_00748ad0(p0, p1, &xf, &box, rot, n, 4, 0, radius)) return;
    } else if (lod != 0 && n->mBoxMin[0] <= n->mBoxMax[0]) {
      cCapsule6 seg;
      seg.a[0] = n->mBoxMin[0]; seg.a[1] = n->mBoxMin[1]; seg.a[2] = n->mBoxMin[2];
      seg.a[3] = n->mBoxMax[0]; seg.a[4] = n->mBoxMax[1]; seg.a[5] = n->mBoxMax[2];
      if (!FUN_007442c0(p0, p1, &xf, seg, 0, radius)) return;
    }
  } else {
    if (!FUN_00748ad0(p0, p1, &xf, &box, rot, n, 0, 0, radius)) return;
  }
  out->PushObj(n->Obj());
}

bool cModelWorld::CollectSweep(const float* p0, const float* p1, PtrVec* out, const cModelFilter* f, float radius)
{
  out->clear();

  cSPTransform xf;
  xf.mFlags = 0;
  xf.mModCount = 0;
  xf.mT[0] = gV3Init[0]; xf.mT[1] = gV3Init[1]; xf.mT[2] = gV3Init[2];
  xf.mScale = gOne;
  for (int i = 0; i < 9; ++i) xf.mRot[i] = gRotInit[i];

  cBBox box;
  box.mn[0] = box.mn[1] = box.mn[2] = gFltMax;
  box.mx[0] = box.mx[1] = box.mx[2] = gNegFltMax;
  float rot[9];

  if (0.0f < radius) {
    float d[3];
    d[0] = p1[0] - p0[0];
    d[1] = p1[1] - p0[1];
    d[2] = p1[2] - p0[2];
    float len = sqrtf((d[0] * d[0] + d[1] * d[1]) + d[2] * d[2]);
    float up[3];
    up[0] = 0.0f; up[1] = 0.0f; up[2] = gOne;
    float inv = gOne / (len + gEps);
    float dir[3];
    dir[0] = inv * d[0];
    dir[1] = inv * d[1];
    dir[2] = inv * d[2];
    float tmp[9];
    const float* m = FUN_0069b1c0(tmp, dir, up);
    for (int i = 0; i < 9; ++i) rot[i] = m[i];
    box.mn[0] = box.mn[1] = box.mn[2] = -radius;
    box.mx[0] = radius;
    box.mx[1] = radius;
    box.mx[2] = len + radius;
  }

  if (mpIndexBegin == mpIndexEnd || g_015fd918->sub->f2c < 2) {
    cModelNode* end = ListAEnd();
    for (cModelNode* n = mListA_next; n != end; n = n->mpNext)
      SweepNode(n, p0, p1, out, f, radius, xf, box, rot);
  } else {
    cModelNode* hits[0x400];
    int count = mQuery.FUN_00702860(p0, p1, radius, 0x400, hits);
    for (int i = 0; i < count; ++i)
      SweepNode(hits[i], p0, p1, out, f, radius, xf, box, rot);
  }
  return out->mpBegin != out->mpEnd;
}
