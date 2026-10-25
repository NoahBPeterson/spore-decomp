// src/game/SPGonzago/SPFormationUtilities.cpp -- migrated from slice(s) s00afab70 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPFormationUtilities.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cActionCircle.h"
#include "EA/Random/RandomLinearCongruential.h"
#include "SP/cPlanetModel.h"

// unnamed retail callees and globals (address in the comment)
extern float g_fEps;           // 0x13ec4b8 = 1e-8f
extern float g_fNegOne;        // 0x13eb1bc = -1.0f
extern float g_defCenter[3];   // 0x167aec4
extern float g_quatIdent[4];   // 0x156737c = {0,0,0,1}
#include <math.h>

// ---- items of slice s00afab70 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int u32;
void* operator_new(unsigned int size, const char* name, int a, int b,
                   const char* file, int line);                 // 0xf473a0
void operator_delete_array(void* p);                            // 0xf47380
namespace EA {
class IRefCounted {
 public:
  virtual int AddRef();
  virtual int Release();
};
}
namespace EA {
template <class T>
class AutoRefCount_s00af_ab70 {
 public:
  T* mpObject;
  AutoRefCount_s00af_ab70() : mpObject(0) {}
  AutoRefCount_s00af_ab70(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
  AutoRefCount_s00af_ab70(const AutoRefCount_s00af_ab70& o) : mpObject(o.mpObject) { if (mpObject) mpObject->AddRef(); }
  ~AutoRefCount_s00af_ab70() { if (mpObject) mpObject->Release(); }
  AutoRefCount_s00af_ab70& operator=(T* p) {
    if (p != mpObject) {
      T* const old = mpObject;
      if (p) p->AddRef();
      mpObject = p;
      if (old) old->Release();
    }
    return *this;
  }
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
};
}
namespace SP {
struct cSPVector3_s00af_ab70 { float mX, mY, mZ; };
}
namespace SP {
struct cSPQuaternion { float x, y, z, w; };
}
namespace SP {
class cGameData_s00af_ab70 : public EA::IRefCounted {};
}
namespace SP {
class cInteractionAgent_s00af_ab70 : public EA::IRefCounted {};
}
namespace SP {
class cActionCircle_s00af_ab70 {
 public:
  class tSlot {
   public:
    bool mOccupied;                                 // +0x0
    char _pad0[3];
    EA::AutoRefCount_s00af_ab70<cGameData_s00af_ab70> mpReservingNoun;    // +0x4
    unsigned int mReservingId;                      // +0x8
    cSPVector3_s00af_ab70 mPos;                                // +0xc

    void Clear() {
      *(volatile bool*)&mOccupied = false;
      *(volatile unsigned int*)&mReservingId = 0;
      cGameData_s00af_ab70* old = *(cGameData_s00af_ab70* volatile*)&mpReservingNoun.mpObject;
      mpReservingNoun.mpObject = (cGameData_s00af_ab70*)0;
      if (old) old->Release();
    }
  };

  struct AgentVector {
    EA::AutoRefCount_s00af_ab70<cInteractionAgent_s00af_ab70>* mpBegin;   // +0x0
    EA::AutoRefCount_s00af_ab70<cInteractionAgent_s00af_ab70>* mpEnd;     // +0x4
    EA::AutoRefCount_s00af_ab70<cInteractionAgent_s00af_ab70>* mpCapacity;// +0x8
    int mAllocator[2];                              // +0xc
    void Destroy();                                 // 0xafb7a0
  };

  struct SlotVector {
    tSlot* mpBegin;                                 // +0x0
    tSlot* mpEnd;                                   // +0x4
    tSlot* mpCapacity;                              // +0x8
    int mAllocator[2];                              // +0xc
    int GetSize() const { return (int)(mpEnd - mpBegin); }
    void Destroy();                                 // 0xafb090
  };

  cSPVector3_s00af_ab70 mFacing;                               // +0x00
  float mRadius;                                    // +0x0c
  float mSlotRadius;                                // +0x10
  cSPVector3_s00af_ab70 mCenter;                               // +0x14
  float mAltitude;                                  // +0x20
  int mPacking;                                     // +0x24
  bool mbRelative;                                  // +0x28
  char _pad28[3];
  cSPQuaternion mOrientation;                       // +0x2c
  AgentVector mAgents;                              // +0x3c
  SlotVector mSlots;                                // +0x50

  cActionCircle_s00af_ab70();  // 0x00afba10 (SP::cActionCircle::cActionCircle_s00af_ab70)
  ~cActionCircle_s00af_ab70();  // 0x00afba10 (SP::cActionCircle::cActionCircle_s00af_ab70)

  int StartSnapAttractorEffects(const cSPVector3_s00af_ab70* p);   // 0xafab70
  int FindSlotByAgent(cGameData_s00af_ab70* agent);                // 0xafad30
  tSlot* FindClosestFreeSlotPtr(const cSPVector3_s00af_ab70* p);   // 0xafad70
  void RemoveAgent(cGameData_s00af_ab70* agent);                   // 0xafae50
  void ProjectSlotsOntoPlanet();                        // 0xafaec0
  void ClearSlots();                                    // 0xafafd0
  void RemoveSlotsByReservingId(unsigned int id);       // 0xafb020
  int FindClosestFreeSlot(const cSPVector3_s00af_ab70* p);         // 0xafa5d0
};
}
namespace SP {
class cPlanetModel_s00af_ab70 {
 public:
  float GetRadiusAt(const cSPVector3_s00af_ab70* p);               // 0xb7ef70
};
}
namespace SP {
cPlanetModel_s00af_ab70* PlanetModel();                            // 0xb3d350
}
using SP::cSPVector3_s00af_ab70;
using SP::cActionCircle_s00af_ab70;
using SP::cGameData_s00af_ab70;
struct DistCtx {
  cSPVector3_s00af_ab70 mP;                 // +0x0
  cActionCircle_s00af_ab70* mCircle;        // +0xc

  bool IsCloser(int a, int b) const;   // 0xafadb0
};
struct HashNode {
  u32 mKey;                      // +0x0
  unsigned char _pad4[0x1c];     // +0x4
  HashNode* mpNext;              // +0x20
};
struct HashTable {
  unsigned char _pad0[4];
  HashNode** mpBuckets;          // +0x4
  u32 mBucketCount;              // +0x8
  u32 mCount;                    // +0xc

  int erase(const u32& key);     // 0xafb130
};
struct AllocNode {
  u32 mTag;                      // +0x0
  float m4, m8, mC, m10, m14, m18, m1C;
  AllocNode* mpNext;             // +0x20
};
void __stdcall CopyAllocNode(const AllocNode* src);   // 0xafb1d0
static float SlotDist2(const cSPVector3_s00af_ab70& p, const cSPVector3_s00af_ab70& s) {
  float dx = p.mX - s.mX;
  float dy = p.mY - s.mY;
  float dz = p.mZ - s.mZ;
  return (dz * dz + dy * dy) + dx * dx;
}
void SortSlotsByDistanceA(int* begin, int* end, float x, float y, float z,
                          cActionCircle_s00af_ab70* circle);                 // 0xafb230
void SortSlotsByDistanceB(int* begin, int* end, float x, float y, float z,
                          cActionCircle_s00af_ab70* circle);                 // 0xafb340
int* MedianOfThree(int* a, int* b, int* c, DistCtx ctx);          // 0xafb430
void PartitionSlots(int* begin, int* end, int pivotIndex, DistCtx ctx); // 0xafb540
void HeapSiftUp(int* heap, int start, int pos, int value, DistCtx ctx); // 0xafb6a0
void ShuffleSlots(int* begin, int* end, void* rng);               // 0xafb8a0
void HeapSiftDown(int* heap, int start, int size, int hole, int value, DistCtx ctx); // 0xafb8f0
struct RandomLinearCongruential_s00af_ab70 {
  u32 RandomUint32Uniform(u32 n);                                 // 0xa68fb0
};
// ---- items of slice s00afab70 end

// @ 0x00afadb0
bool DistCtx::IsCloser(int a, int b) const
{
  const cActionCircle_s00af_ab70::tSlot* sa = mCircle->mSlots.mpBegin + a;
  const cActionCircle_s00af_ab70::tSlot* sb = mCircle->mSlots.mpBegin + b;
  float da = SlotDist2(mP, sa->mPos);
  float db = SlotDist2(mP, sb->mPos);
  return da < db;
}

// @ 0x00afaec0
void SP::cActionCircle_s00af_ab70::ProjectSlotsOntoPlanet()
{
  cPlanetModel_s00af_ab70* model = SP::PlanetModel();
  if (model) {
    int n = (int)(mSlots.mpEnd - mSlots.mpBegin);
    if (0 < n) {
      for (int i = 0; i < n; i++) {
        tSlot* s = mSlots.mpBegin + i;
        float x = s->mPos.mX;
        float y = s->mPos.mY;
        float z = s->mPos.mZ;
        float inv = 1.0f / (float)sqrt((double)((x * x + y * y) + z * z) + g_fEps);
        cSPVector3_s00af_ab70 local;
        local.mX = x * inv;
        local.mY = y * inv;
        local.mZ = z * inv;
        float radius = model->GetRadiusAt(&local) + mAltitude;
        s->mPos.mX = local.mX * radius;
        s->mPos.mY = local.mY * radius;
        s->mPos.mZ = local.mZ * radius;
      }
    }
  }
}

// @ 0x00afafd0
void SP::cActionCircle_s00af_ab70::ClearSlots()
{
  int n = (int)(mSlots.mpEnd - mSlots.mpBegin);
  for (int i = 0; i < n; i++) {
    mSlots.mpBegin[i].Clear();
  }
}

// @ 0x00afb130
int HashTable::erase(const u32& key)
{
  int oldCount = (int)mCount;
  u32 bucket = key % mBucketCount;
  HashNode** link = &mpBuckets[bucket];
  if (*link) {
    HashNode* node = *link;
    while (node->mKey != key) {
      link = &node->mpNext;
      node = node->mpNext;
      if (!node) break;
    }
    while (*link && (*link)->mKey == key) {
      HashNode* del = *link;
      *link = del->mpNext;
      operator_delete_array(del);
      mCount--;
    }
  }
  return oldCount - (int)mCount;
}

// @ 0x00afb1d0
void __stdcall CopyAllocNode(const AllocNode* src)
{
  AllocNode* node = (AllocNode*)operator_new(
      0x24, "Simulator", 0, 0,
      "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
      0xd1);
  if (node) {
    float f4 = *(volatile float*)&src->m4;
    u32 tag = src->mTag;
    node->m4 = f4;
    node->mTag = tag;
    node->m8 = src->m8;
    node->mC = src->mC;
    node->m10 = src->m10;
    node->m14 = src->m14;
    node->m18 = src->m18;
    node->m1C = src->m1C;
  }
  node->mpNext = 0;
}

// @ 0x00afb230
void SortSlotsByDistanceA(int* begin, int* end, float x, float y, float z, cActionCircle_s00af_ab70* circle)
{
  if (begin == end) return;
  for (int* it = begin + 1; it != end; ++it) {
    int value = *it;
    int* hole = it;
    while (hole != begin) {
      int prev = hole[-1];
      const cActionCircle_s00af_ab70::tSlot* cur = &circle->mSlots.mpBegin[value];
      float dz = z - cur->mPos.mZ;
      float dy = y - cur->mPos.mY;
      float dx = x - cur->mPos.mX;
      float dcur = (dz * dz + dy * dy) + dx * dx;
      const cActionCircle_s00af_ab70::tSlot* pv = &circle->mSlots.mpBegin[prev];
      float py = y - pv->mPos.mY;
      float px = x - pv->mPos.mX;
      float pz = z - pv->mPos.mZ;
      float dprev = (pz * pz + py * py) + px * px;
      if (dprev <= dcur) break;
      *hole = prev;
      --hole;
    }
    *hole = value;
  }
}

// @ 0x00afb340
void SortSlotsByDistanceB(int* begin, int* end, float x, float y, float z, cActionCircle_s00af_ab70* circle)
{
  for (; begin != end; ++begin) {
    int value = *begin;
    int* hole = begin;
    int* prevp = begin;
    while (true) {
      --prevp;
      int prev = *prevp;
      const cActionCircle_s00af_ab70::tSlot* cur = &circle->mSlots.mpBegin[value];
      float dz = z - cur->mPos.mZ;
      float dy = y - cur->mPos.mY;
      float dx = x - cur->mPos.mX;
      float dcur = (dz * dz + dy * dy) + dx * dx;
      const cActionCircle_s00af_ab70::tSlot* pv = &circle->mSlots.mpBegin[prev];
      float py = y - pv->mPos.mY;
      float px = x - pv->mPos.mX;
      float pz = z - pv->mPos.mZ;
      float dprev = (pz * pz + py * py) + px * px;
      if (dprev <= dcur) break;
      *hole = prev;
      --hole;
    }
    *hole = value;
  }
}

// @ 0x00afb430
int* MedianOfThree(int* a, int* b, int* c, DistCtx ctx)
{
  const cActionCircle_s00af_ab70::tSlot* sa = &ctx.mCircle->mSlots.mpBegin[*a];
  float dza = ctx.mP.mZ - sa->mPos.mZ;
  float dya = ctx.mP.mY - sa->mPos.mY;
  float dxa = ctx.mP.mX - sa->mPos.mX;
  float da = (dza * dza + dya * dya) + dxa * dxa;
  const cActionCircle_s00af_ab70::tSlot* sb = &ctx.mCircle->mSlots.mpBegin[*b];
  float dzb = ctx.mP.mZ - sb->mPos.mZ;
  float dyb = ctx.mP.mY - sb->mPos.mY;
  float dxb = ctx.mP.mX - sb->mPos.mX;
  float db = (dzb * dzb + dyb * dyb) + dxb * dxb;
  if (db <= da) {
    if (ctx.IsCloser(*a, *c)) return a;
    if (ctx.IsCloser(*b, *c)) return c;
    return b;
  }
  if (ctx.IsCloser(*b, *c)) return b;
  if (ctx.IsCloser(*a, *c)) return c;
  return a;
}

// @ 0x00afb540
void PartitionSlots(int* begin, int* end, int pivotIndex, DistCtx ctx)
{
  const cActionCircle_s00af_ab70::tSlot* pivot = &ctx.mCircle->mSlots.mpBegin[pivotIndex];
  while (true) {
    while (true) {
      const cActionCircle_s00af_ab70::tSlot* cur = &ctx.mCircle->mSlots.mpBegin[*begin];
      float pz = ctx.mP.mZ - pivot->mPos.mZ;
      float py = ctx.mP.mY - pivot->mPos.mY;
      float px = ctx.mP.mX - pivot->mPos.mX;
      float dp = (pz * pz + py * py) + px * px;
      float cz = ctx.mP.mZ - cur->mPos.mZ;
      float cy = ctx.mP.mY - cur->mPos.mY;
      float cx = ctx.mP.mX - cur->mPos.mX;
      float dc = (cz * cz + cy * cy) + cx * cx;
      if (dp <= dc) break;
      ++begin;
    }
    float pz = ctx.mP.mZ - pivot->mPos.mZ;
    float py = ctx.mP.mY - pivot->mPos.mY;
    float px = ctx.mP.mX - pivot->mPos.mX;
    float dp = (pz * pz + py * py) + px * px;
    while (true) {
      --end;
      const cActionCircle_s00af_ab70::tSlot* cand = &ctx.mCircle->mSlots.mpBegin[*end];
      float cz = ctx.mP.mZ - cand->mPos.mZ;
      float cy = ctx.mP.mY - cand->mPos.mY;
      float cx = ctx.mP.mX - cand->mPos.mX;
      float dc = (cz * cz + cy * cy) + cx * cx;
      if (dp >= dc) break;
    }
    if (begin >= end) return;
    int tmp = *begin;
    *begin = *end;
    *end = tmp;
    ++begin;
  }
}

// @ 0x00afb6a0
void HeapSiftUp(int* heap, int start, int pos, int value, DistCtx ctx)
{
  float x = ctx.mP.mX, y = ctx.mP.mY, z = ctx.mP.mZ;
  int parent = (pos - 1) >> 1;
  if (pos <= start) {
    heap[pos] = value;
    return;
  }
  do {
    int parentValue = heap[parent];
    float pz = z - ctx.mCircle->mSlots.mpBegin[parentValue].mPos.mZ;
    float py = y - ctx.mCircle->mSlots.mpBegin[parentValue].mPos.mY;
    float px = x - ctx.mCircle->mSlots.mpBegin[parentValue].mPos.mX;
    float dp = (pz * pz + py * py) + px * px;
    float vy = y - ctx.mCircle->mSlots.mpBegin[value].mPos.mY;
    float vx = x - ctx.mCircle->mSlots.mpBegin[value].mPos.mX;
    float vz = z - ctx.mCircle->mSlots.mpBegin[value].mPos.mZ;
    float dv = (vz * vz + vy * vy) + vx * vx;
    if (dv <= dp) {
      heap[pos] = value;
      return;
    }
    heap[pos] = parentValue;
    pos = parent;
    parent = (pos - 1) >> 1;
  } while (start < pos);
  heap[pos] = value;
}

// @ 0x00afb8a0
void ShuffleSlots(int* begin, int* end, void* rng)
{
  RandomLinearCongruential_s00af_ab70* random = (RandomLinearCongruential_s00af_ab70*)rng;
  for (int* it = begin + 1; it < end; ++it) {
    u32 idx = random->RandomUint32Uniform((u32)(it - begin) + 1);
    int* p = &begin[idx];
    int tmp = *it;
    *it = *p;
    *p = tmp;
  }
}

// @ 0x00afb8f0
void HeapSiftDown(int* heap, int start, int size, int hole, int value, DistCtx ctx)
{
  float x = ctx.mP.mX, y = ctx.mP.mY, z = ctx.mP.mZ;
  int right;
  while (true) {
    right = hole * 2 + 2;
    if (right >= size) break;
    int rightValue = heap[right];
    float ry = y - ctx.mCircle->mSlots.mpBegin[rightValue].mPos.mY;
    float rx = x - ctx.mCircle->mSlots.mpBegin[rightValue].mPos.mX;
    float rz = z - ctx.mCircle->mSlots.mpBegin[rightValue].mPos.mZ;
    float dr = (rz * rz + ry * ry) + rx * rx;
    int leftValue = heap[right - 1];
    float ly = y - ctx.mCircle->mSlots.mpBegin[leftValue].mPos.mY;
    float lx = x - ctx.mCircle->mSlots.mpBegin[leftValue].mPos.mX;
    float lz = z - ctx.mCircle->mSlots.mpBegin[leftValue].mPos.mZ;
    float dl = (lz * lz + ly * ly) + lx * lx;
    int child;
    if (dl <= dr) child = right;
    else child = right - 1;
    heap[hole] = heap[child];
    hole = child;
  }
  if (right == size) {
    heap[hole] = heap[size - 1];
    hole = right - 1;
  }
  HeapSiftUp(heap, start, hole, value, ctx);
}

// @ 0x00afba10
SP::cActionCircle_s00af_ab70::cActionCircle_s00af_ab70()
{
  mFacing.mX = g_defCenter[0];
  mFacing.mY = g_defCenter[1];
  mFacing.mZ = g_defCenter[2];
  float negOne = g_fNegOne;
  mRadius = negOne;
  mSlotRadius = negOne;
  mCenter.mX = g_defCenter[0];
  mCenter.mY = g_defCenter[1];
  mCenter.mZ = g_defCenter[2];
  mAltitude = 0.0f;
  mbRelative = false;
  mOrientation.x = g_quatIdent[0];
  mOrientation.y = g_quatIdent[1];
  mOrientation.z = g_quatIdent[2];
  float qw = g_quatIdent[3];
  mAgents.mpBegin = 0;
  mAgents.mpEnd = 0;
  mAgents.mpCapacity = 0;
  mOrientation.w = qw;
  mSlots.mpBegin = 0;
  mSlots.mpEnd = 0;
  mSlots.mpCapacity = 0;
}

// @ 0x00afbad0
SP::cActionCircle_s00af_ab70::~cActionCircle_s00af_ab70()
{
  mSlots.Destroy();
  mAgents.Destroy();
}
