// Slice s00afab70 -- SP::cActionCircle slot queries, slot-vector cleanup, planet projection,
// a small eastl hash-table erase, node copy, and the distance-sorting / heap / median helpers
// used by the slot packers.  Reconstructed from the retail disassembly.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"
#include <math.h>

typedef unsigned int u32;

// ---------------------------------------------------------------------------
// external globals (values live in the retail image; symbol identity matters)
// ---------------------------------------------------------------------------
extern float g_fFLTMax;        // 0x145c45c = FLT_MAX
extern float g_fEps;           // 0x13ec4b8 = 1e-8f
extern float g_fNegOne;        // 0x13eb1bc = -1.0f
extern float g_defCenter[3];   // 0x167aec4
extern float g_quatIdent[4];   // 0x156737c = {0,0,0,1}

// eastl allocation plumbing
void* operator_new(unsigned int size, const char* name, int a, int b,
                   const char* file, int line);                 // 0xf473a0
void operator_delete_array(void* p);                            // 0xf47380

namespace EA {

class IRefCounted {
 public:
  virtual int AddRef();
  virtual int Release();
};

template <class T>
class AutoRefCount {
 public:
  T* mpObject;
  AutoRefCount() : mpObject(0) {}
  AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
  AutoRefCount(const AutoRefCount& o) : mpObject(o.mpObject) { if (mpObject) mpObject->AddRef(); }
  ~AutoRefCount() { if (mpObject) mpObject->Release(); }
  AutoRefCount& operator=(T* p) {
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
}  // namespace EA

namespace SP {

struct cSPVector3 { float mX, mY, mZ; };
struct cSPQuaternion { float x, y, z, w; };

class cGameData : public EA::IRefCounted {};
class cInteractionAgent : public EA::IRefCounted {};

class cActionCircle {
 public:
  class tSlot {
   public:
    bool mOccupied;                                 // +0x0
    char _pad0[3];
    EA::AutoRefCount<cGameData> mpReservingNoun;    // +0x4
    unsigned int mReservingId;                      // +0x8
    cSPVector3 mPos;                                // +0xc

    void Clear() {
      *(volatile bool*)&mOccupied = false;
      *(volatile unsigned int*)&mReservingId = 0;
      cGameData* old = *(cGameData* volatile*)&mpReservingNoun.mpObject;
      mpReservingNoun.mpObject = (cGameData*)0;
      if (old) old->Release();
    }
  };

  struct AgentVector {
    EA::AutoRefCount<cInteractionAgent>* mpBegin;   // +0x0
    EA::AutoRefCount<cInteractionAgent>* mpEnd;     // +0x4
    EA::AutoRefCount<cInteractionAgent>* mpCapacity;// +0x8
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

  cSPVector3 mFacing;                               // +0x00
  float mRadius;                                    // +0x0c
  float mSlotRadius;                                // +0x10
  cSPVector3 mCenter;                               // +0x14
  float mAltitude;                                  // +0x20
  int mPacking;                                     // +0x24
  bool mbRelative;                                  // +0x28
  char _pad28[3];
  cSPQuaternion mOrientation;                       // +0x2c
  AgentVector mAgents;                              // +0x3c
  SlotVector mSlots;                                // +0x50

  cActionCircle();
  ~cActionCircle();

  int StartSnapAttractorEffects(const cSPVector3* p);   // 0xafab70
  int FindSlotByAgent(cGameData* agent);                // 0xafad30
  tSlot* FindClosestFreeSlotPtr(const cSPVector3* p);   // 0xafad70
  void RemoveAgent(cGameData* agent);                   // 0xafae50
  void ProjectSlotsOntoPlanet();                        // 0xafaec0
  void ClearSlots();                                    // 0xafafd0
  void RemoveSlotsByReservingId(unsigned int id);       // 0xafb020
  int FindClosestFreeSlot(const cSPVector3* p);         // 0xafa5d0
};

class cPlanetModel {
 public:
  float GetRadiusAt(const cSPVector3* p);               // 0xb7ef70
};

cPlanetModel* PlanetModel();                            // 0xb3d350

}  // namespace SP

using SP::cSPVector3;
using SP::cActionCircle;
using SP::cGameData;

// Distance context passed by value to the comparator: the query point followed by the circle.
struct DistCtx {
  cSPVector3 mP;                 // +0x0
  cActionCircle* mCircle;        // +0xc

  bool IsCloser(int a, int b) const;   // 0xafadb0
};

// eastl hash node / table (erase-by-key and node copy helpers below).
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

// Node payload copied by FUN_00afb1d0: an int tag followed by seven float slots.
struct AllocNode {
  u32 mTag;                      // +0x0
  float m4, m8, mC, m10, m14, m18, m1C;
  AllocNode* mpNext;             // +0x20
};

void __stdcall CopyAllocNode(const AllocNode* src);   // 0xafb1d0

// Distance between a query point and one slot (used by the sorter/heap helpers).
static float SlotDist2(const cSPVector3& p, const cSPVector3& s) {
  float dx = p.mX - s.mX;
  float dy = p.mY - s.mY;
  float dz = p.mZ - s.mZ;
  return (dz * dz + dy * dy) + dx * dx;
}

static float SlotDist2XYZ(const cActionCircle::tSlot* s, float x, float y, float z) {
  float dx = x - s->mPos.mX;
  float dy = y - s->mPos.mY;
  float dz = z - s->mPos.mZ;
  return (dz * dz + dy * dy) + dx * dx;
}

void SortSlotsByDistanceA(int* begin, int* end, float x, float y, float z,
                          cActionCircle* circle);                 // 0xafb230
void SortSlotsByDistanceB(int* begin, int* end, float x, float y, float z,
                          cActionCircle* circle);                 // 0xafb340
int* MedianOfThree(int* a, int* b, int* c, DistCtx ctx);          // 0xafb430
void PartitionSlots(int* begin, int* end, int pivotIndex, DistCtx ctx); // 0xafb540
void HeapSiftUp(int* heap, int start, int pos, int value, DistCtx ctx); // 0xafb6a0
void ShuffleSlots(int* begin, int* end, void* rng);               // 0xafb8a0
void HeapSiftDown(int* heap, int start, int size, int hole, int value, DistCtx ctx); // 0xafb8f0

// RandomLinearCongruential::RandomUint32Uniform(unsigned)
struct RandomLinearCongruential {
  u32 RandomUint32Uniform(u32 n);                                 // 0xa68fb0
};

// ===========================================================================
// @ 0xafab70
// ===========================================================================
int SP::cActionCircle::StartSnapAttractorEffects(const cSPVector3* p) {
  int n = (int)(mSlots.mpEnd - mSlots.mpBegin);
  float best = g_fFLTMax;
  int i = 0;
  int found = -1;
  if (3 < n) {
    float px = p->mX;
    float py = p->mY;
    float pz = p->mZ;
    tSlot* s = mSlots.mpBegin;
    do {
      {
        float dx = px - s[0].mPos.mX, dy = py - s[0].mPos.mY, dz = pz - s[0].mPos.mZ;
        float dist = (dx * dx + dy * dy) + dz * dz;
        if (dist < best) { found = i; best = dist; }
      }
      {
        float dx = px - s[1].mPos.mX, dy = py - s[1].mPos.mY, dz = pz - s[1].mPos.mZ;
        float dist = (dx * dx + dy * dy) + dz * dz;
        if (dist < best) { found = i + 1; best = dist; }
      }
      {
        float dx = px - s[2].mPos.mX, dy = py - s[2].mPos.mY, dz = pz - s[2].mPos.mZ;
        float dist = (dx * dx + dy * dy) + dz * dz;
        if (dist < best) { found = i + 2; best = dist; }
      }
      {
        float dx = px - s[3].mPos.mX, dy = py - s[3].mPos.mY, dz = pz - s[3].mPos.mZ;
        float dist = (dx * dx + dy * dy) + dz * dz;
        if (dist < best) { found = i + 3; best = dist; }
      }
      i += 4;
      s += 4;
    } while (i < n - 3);
  }
  for (; i < n; i++) {
    tSlot* s = mSlots.mpBegin + i;
    float dx = p->mX - s->mPos.mX, dy = p->mY - s->mPos.mY, dz = p->mZ - s->mPos.mZ;
    float dist = (dx * dx + dy * dy) + dz * dz;
    if (dist < best) { found = i; best = dist; }
  }
  return found;
}

// ===========================================================================
// @ 0xafad30
// ===========================================================================
int SP::cActionCircle::FindSlotByAgent(cGameData* agent) {
  int n = mSlots.GetSize();
  int i = 0;
  if (0 < n) {
    tSlot* s = mSlots.mpBegin;
    do {
      if (s->mpReservingNoun.mpObject == agent) return i;
      i++;
      s++;
    } while (i < n);
  }
  return -1;
}

// ===========================================================================
// @ 0xafad70
// ===========================================================================
SP::cActionCircle::tSlot* SP::cActionCircle::FindClosestFreeSlotPtr(const cSPVector3* p) {
  int index = FindClosestFreeSlot(p);
  if ((unsigned int)index >= (unsigned int)mSlots.GetSize()) return 0;
  return &mSlots.mpBegin[index];
}

// ===========================================================================
// @ 0xafadb0
// ===========================================================================
bool DistCtx::IsCloser(int a, int b) const {
  const cActionCircle::tSlot* sa = mCircle->mSlots.mpBegin + a;
  const cActionCircle::tSlot* sb = mCircle->mSlots.mpBegin + b;
  float da = SlotDist2(mP, sa->mPos);
  float db = SlotDist2(mP, sb->mPos);
  return da < db;
}

// ===========================================================================
// @ 0xafae50
// ===========================================================================
void SP::cActionCircle::RemoveAgent(cGameData* agent) {
  int n = (int)(mSlots.mpEnd - mSlots.mpBegin);
  for (int i = 0; i < n; i++) {
    tSlot* s = mSlots.mpBegin + i;
    if (s->mpReservingNoun.mpObject == agent) s->Clear();
  }
}

// ===========================================================================
// @ 0xafaec0
// ===========================================================================
void SP::cActionCircle::ProjectSlotsOntoPlanet() {
  cPlanetModel* model = SP::PlanetModel();
  if (model) {
    int n = (int)(mSlots.mpEnd - mSlots.mpBegin);
    if (0 < n) {
      for (int i = 0; i < n; i++) {
        tSlot* s = mSlots.mpBegin + i;
        float x = s->mPos.mX;
        float y = s->mPos.mY;
        float z = s->mPos.mZ;
        float inv = 1.0f / (float)sqrt((double)((x * x + y * y) + z * z) + g_fEps);
        cSPVector3 local;
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

// ===========================================================================
// @ 0xafafd0
// ===========================================================================
void SP::cActionCircle::ClearSlots() {
  int n = (int)(mSlots.mpEnd - mSlots.mpBegin);
  for (int i = 0; i < n; i++) {
    mSlots.mpBegin[i].Clear();
  }
}

// ===========================================================================
// @ 0xafb020
// ===========================================================================
void SP::cActionCircle::RemoveSlotsByReservingId(unsigned int id) {
  int n = (int)(mSlots.mpEnd - mSlots.mpBegin);
  for (int i = 0; i < n; i++) {
    tSlot* s = mSlots.mpBegin + i;
    if (s->mReservingId == id) s->Clear();
  }
}

// ===========================================================================
// @ 0xafb130
// ===========================================================================
int HashTable::erase(const u32& key) {
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

// ===========================================================================
// @ 0xafb1d0
// ===========================================================================
void __stdcall CopyAllocNode(const AllocNode* src) {
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

// ===========================================================================
// @ 0xafb230
// ===========================================================================
void SortSlotsByDistanceA(int* begin, int* end, float x, float y, float z,
                          cActionCircle* circle) {
  if (begin == end) return;
  for (int* it = begin + 1; it != end; ++it) {
    int value = *it;
    int* hole = it;
    while (hole != begin) {
      int prev = hole[-1];
      const cActionCircle::tSlot* cur = &circle->mSlots.mpBegin[value];
      float dz = z - cur->mPos.mZ;
      float dy = y - cur->mPos.mY;
      float dx = x - cur->mPos.mX;
      float dcur = (dz * dz + dy * dy) + dx * dx;
      const cActionCircle::tSlot* pv = &circle->mSlots.mpBegin[prev];
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

// ===========================================================================
// @ 0xafb340
// ===========================================================================
void SortSlotsByDistanceB(int* begin, int* end, float x, float y, float z,
                          cActionCircle* circle) {
  for (; begin != end; ++begin) {
    int value = *begin;
    int* hole = begin;
    int* prevp = begin;
    while (true) {
      --prevp;
      int prev = *prevp;
      const cActionCircle::tSlot* cur = &circle->mSlots.mpBegin[value];
      float dz = z - cur->mPos.mZ;
      float dy = y - cur->mPos.mY;
      float dx = x - cur->mPos.mX;
      float dcur = (dz * dz + dy * dy) + dx * dx;
      const cActionCircle::tSlot* pv = &circle->mSlots.mpBegin[prev];
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

// ===========================================================================
// @ 0xafb430
// ===========================================================================
int* MedianOfThree(int* a, int* b, int* c, DistCtx ctx) {
  const cActionCircle::tSlot* sa = &ctx.mCircle->mSlots.mpBegin[*a];
  float dza = ctx.mP.mZ - sa->mPos.mZ;
  float dya = ctx.mP.mY - sa->mPos.mY;
  float dxa = ctx.mP.mX - sa->mPos.mX;
  float da = (dza * dza + dya * dya) + dxa * dxa;
  const cActionCircle::tSlot* sb = &ctx.mCircle->mSlots.mpBegin[*b];
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

// ===========================================================================
// @ 0xafb540
// ===========================================================================
void PartitionSlots(int* begin, int* end, int pivotIndex, DistCtx ctx) {
  const cActionCircle::tSlot* pivot = &ctx.mCircle->mSlots.mpBegin[pivotIndex];
  while (true) {
    while (true) {
      const cActionCircle::tSlot* cur = &ctx.mCircle->mSlots.mpBegin[*begin];
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
      const cActionCircle::tSlot* cand = &ctx.mCircle->mSlots.mpBegin[*end];
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

// ===========================================================================
// @ 0xafb6a0
// ===========================================================================
void HeapSiftUp(int* heap, int start, int pos, int value, DistCtx ctx) {
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

// ===========================================================================
// @ 0xafb8a0
// ===========================================================================
void ShuffleSlots(int* begin, int* end, void* rng) {
  RandomLinearCongruential* random = (RandomLinearCongruential*)rng;
  for (int* it = begin + 1; it < end; ++it) {
    u32 idx = random->RandomUint32Uniform((u32)(it - begin) + 1);
    int* p = &begin[idx];
    int tmp = *it;
    *it = *p;
    *p = tmp;
  }
}

// ===========================================================================
// @ 0xafb8f0
// ===========================================================================
void HeapSiftDown(int* heap, int start, int size, int hole, int value, DistCtx ctx) {
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

// ===========================================================================
// @ 0xafba10
// ===========================================================================
SP::cActionCircle::cActionCircle() {
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

// ===========================================================================
// @ 0xafbad0
// ===========================================================================
SP::cActionCircle::~cActionCircle() {
  mSlots.Destroy();
  mAgents.Destroy();
}
