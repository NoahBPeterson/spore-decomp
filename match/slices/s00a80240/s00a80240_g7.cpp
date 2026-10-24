// Slice s00a80240 (gold7) -- Swarm surface decals / particle-cell bookkeeping.
//
// NOTE: this slice id is shared with the older slice whose source is
// s00a80240.cpp (BillboardEffect::WriteQuads @ 0x00a80240).  That file and its
// nonmatching row are left untouched.  The gold7 batch adds the ten functions
// below, all in the same neighbourhood of the binary:
//
//   00a80920  Particle::Particle              (particle/decal node constructor)
//   00a809d0  SurfaceDecals::VisitParticles   (walk the +0xa4 node list)
//   00a80a40  SurfaceDecals::ClearParticles   (retire indices, release +0x14)
//   00a80ac0  SurfaceDecals::SurfaceDecals    (base constructor)
//   00a80b80  SurfaceDecals::Reset             (drain +0xac, clear +0xa4)
//   00a80c00  HashTable::Insert                (EASTL hash-map find-or-insert)
//   00a80d10  SurfaceDecals::~SurfaceDecals    (derived destructor)
//   00a80dd0  SimpleVector::DoInsertValue      (EASTL vector insert)
//   00a80ee0  SurfaceDecals::SurfaceDecalsEx   (derived constructor)
//   00a80fe0  SurfaceDecals::RemoveCell        (unlink a cell from +0xac)
//
// Flags: VS2008-era cl 15, /O2 /MD /Gy /TP /arch:SSE /fp:fast
// Class and member names are coined; the offsets come from the disassembly.

#include "types.h"
#include <string.h>

// ---------------------------------------------------------------------------
// External data / helpers
// ---------------------------------------------------------------------------

extern float g_167776c;          // 0x0167776c
extern float g_1677770;          // 0x01677770
extern float g_1677774;          // 0x01677774
extern float g_1564cc8;          // 0x01564cc8
extern float g_1457d54;          // 0x01457d54 (raw 0xce6e6b28, -1e9f)
extern float g_1470f1c;          // 0x01470f1c (raw 0x40000000, 2.0f)
extern const uint32_t g_negmask; // 0x013eb8b0 (0x80000000 x4)
extern void* g_staticBuckets;    // 0x0154df28 (one-element static bucket array)

extern void* g_vtblSurfaceDecals;      // 0x01457d58
extern void* g_vtblSurfaceDecalsEx;    // 0x01457d64
extern void* g_vtblSurfaceDecalsEx2;   // 0x01457d60
extern void* g_vtblIEventModifier;     // 0x013ef094

extern void* EAAllocate(size_t size, const char* name, int flags, int align,
                        const char* file, int line);   // 0x00f473a0
extern void  FreeMem(void* p);                            // 0x00f47380

struct Matrix33 {
  float m[9];
  void Assign(const Matrix33* src);                        // 0x0041cb40
};
extern Matrix33 g_identity33;                              // 0x01677818

struct IntrusiveList {
  IntrusiveList* mNext;   // +0x00
  IntrusiveList* mPrev;   // +0x04
  ~IntrusiveList();                                        // 0x00620230
};

// ---------------------------------------------------------------------------
// Particle -- layout produced by 00a80920
// ---------------------------------------------------------------------------
struct Particle {
  uint32_t m0;        // +0x00
  uint32_t m4;        // +0x04
  uint16_t m8;        // +0x08
  uint16_t mA;        // +0x0a
  float    mC;        // +0x0c
  float    m10;       // +0x10
  float    m14;       // +0x14
  float    m18;       // +0x18
  Matrix33 mMatrix;   // +0x1c
  float    m40, m44, m48, m4c;   // +0x40
  float    m50, m54, m58, m5c;   // +0x50
  float    m60, m64;             // +0x60
  uint32_t m68, m6c;             // +0x68

  Particle* Ctor();                                          // 0x00a80920
};

// ---------------------------------------------------------------------------
// Nodes and containers
// ---------------------------------------------------------------------------
struct SurfaceDecalState;

// Node of the +0xa4 list: link object at +0x04 ({next, prev}), data at +0x0c.
struct DecalNode {
  uint32_t mPad00;            // +0x00
  uint32_t mNext;             // +0x04 (link pointer to the next node's mNext)
  uint32_t mPrev;             // +0x08
  int32_t  mIndex;            // +0x0c
  uint8_t  mPad10[0x18];      // +0x10
  Particle mParticle;         // +0x28 .. +0x97
  SurfaceDecalState* mState;  // +0x98
};

// Node of the +0xac list: link object at +0x00 ({next, prev}), state ptr +0x98.
struct CellDataNode {
  CellDataNode* mNext;        // +0x00
  CellDataNode* mPrev;        // +0x04
  uint8_t mData[0x90];        // +0x08 .. +0x97
  SurfaceDecalState* mState;  // +0x98
};

struct SimpleVector {
  CellDataNode** mBegin;      // +0x00
  CellDataNode** mEnd;        // +0x04
  CellDataNode** mCap;        // +0x08

  void DoInsertValue(CellDataNode** pos, CellDataNode** value); // 0x00a80dd0
};

struct SurfaceDecalState {
  uint8_t mPad00[0x0c];       // +0x00
  int32_t mIndex;             // +0x0c
  uint8_t mPad10[0x04];       // +0x10
  SimpleVector mVector;       // +0x14 (begin +0, end +4, cap +8)
};

// EASTL hash table used by SurfaceDecals at +0x84.
struct HashNode {
  uint32_t mKey[4];           // +0x00
  HashNode* mNext;            // +0x10
};

struct RehashResult {
  uint8_t mFlag;              // +0x00
  uint8_t mPad[3];            // +0x01
  uint32_t mCount;            // +0x04
};

struct RehashPolicy {
  float mMaxLoad;             // +0x00
  float mGrowth;              // +0x04
  uint32_t mNextResize;       // +0x08

  bool NeedRehash(RehashResult* out, uint32_t bucketCount,
                  uint32_t elementCount, bool grow);        // 0x00921440
};

struct InsertResult {
  HashNode*  mNode;           // +0x00
  HashNode** mBucket;         // +0x04
  uint8_t    mFlag;           // +0x08
};

struct HashTable {
  uint32_t mUnused;           // +0x00
  HashNode** mBuckets;        // +0x04
  uint32_t mBucketCount;      // +0x08
  uint32_t mElementCount;     // +0x0c
  RehashPolicy mPolicy;       // +0x10

  void DoFreeNodes(HashNode** buckets, uint32_t count);     // 0x007611f0
  void Rehash(uint32_t newCount);                           // 0x00a7bd70
  InsertResult* Insert(InsertResult* out, const uint32_t* key,
                       uint32_t unused);                    // 0x00a80c00
};

// ---------------------------------------------------------------------------
// SurfaceDecals -- layout shared by the ctors / dtor / list walkers
// ---------------------------------------------------------------------------
struct SurfaceDecals {
  void*    mVtbl0;            // +0x00
  void*    mVtbl4;            // +0x04
  uint32_t m8;                // +0x08
  int32_t  mC;                // +0x0c
  void*    mObj10;            // +0x10
  void*    mObj14;            // +0x14
  uint32_t m18;               // +0x18
  uint32_t m1c;               // +0x1c
  int32_t  m20;               // +0x20
  int32_t  m24;               // +0x24
  float    m28, m2c, m30;     // +0x28
  float    m34, m38, m3c;     // +0x34
  float    m40, m44, m48, m4c;// +0x40
  int32_t  m50, m54;          // +0x50
  void*    mArray58;          // +0x58
  uint32_t m5c;               // +0x5c
  uint32_t m60;               // +0x60
  uint32_t m64;               // +0x64
  uint32_t m68;               // +0x68
  uint32_t m6c;               // +0x6c
  void*    mArray70;          // +0x70
  uint32_t m74;               // +0x74
  uint32_t m78;               // +0x78
  uint32_t m7c;               // +0x7c
  uint32_t m80;               // +0x80
  HashTable mHash;            // +0x84
  uint32_t mListA0;           // +0xa0
  IntrusiveList mListA4;      // +0xa4
  IntrusiveList mListAC;      // +0xac

  SurfaceDecals* BaseCtor();                                  // 0x00a80ac0
  SurfaceDecals* DerivedCtor();                               // 0x00a80ee0
  void Destroy();                                             // 0x00a80d10
  void VisitParticles();                                      // 0x00a809d0
  void ClearParticles();                                      // 0x00a80a40
  bool Reset();                                               // 0x00a80b80
  void RemoveCell(CellDataNode* cell);                        // 0x00a80fe0
};

typedef void (__thiscall* VtFn0)(void* self);
typedef void (__thiscall* VtFn1)(void* self, int a);
typedef void (__thiscall* VtFn3)(void* self, int a, void* b, float c);

static inline void* VtblOf(void* obj) {
  return *(void**)obj;
}

static inline void* VtSlot(void* vtable, uint32_t byteOffset) {
  return *(void**)((char*)vtable + byteOffset);
}

static inline void FreeArray(void* p) {
  if (p != 0 && ((int*)p)[-1] != 0)
    FreeMem(p);
}

// ---------------------------------------------------------------------------
// 0x00a80920 -- Particle constructor
// ---------------------------------------------------------------------------
// @ 0x00a80920
Particle* Particle::Ctor() {
  m4 = 0;
  m0 = 0;
  uint32_t zA = m0;
  uint32_t z8 = m0;
  mA = (uint16_t)zA;
  m8 = (uint16_t)z8;
  mC = g_167776c;
  m10 = g_1677770;
  m14 = g_1677774;
  m18 = 1.0f;
  mMatrix.Assign(&g_identity33);
  m40 = 1.0f;
  m44 = 1.0f;
  m48 = 1.0f;
  m4c = 1.0f;
  m50 = 1.0f;
  m54 = 1.0f;
  m58 = 1.0f;
  m5c = 1.0f;
  m60 = 0.0f;
  m64 = 0.0f;
  m68 = 0;
  m6c = 0;
  return this;
}

// ---------------------------------------------------------------------------
// 0x00a809d0 -- walk the +0xa4 particle-node list and notify the owner
// ---------------------------------------------------------------------------
// @ 0x00a809d0
void SurfaceDecals::VisitParticles() {
  DecalNode* node = mListA4.mNext
      ? (DecalNode*)((char*)mListA4.mNext - 4) : 0;
  DecalNode* end = (DecalNode*)((char*)&mListA4 - 4);
  while (node != end) {
    if (node->mIndex >= 0) {
      void* owner = mObj14;
      VtFn3 fn = (VtFn3)VtSlot(VtblOf(owner), 0x20);
      fn(owner, node->mIndex, &node->mParticle, 0.0f);
    }
    node = node->mNext
        ? (DecalNode*)((char*)node->mNext - 4) : 0;
  }
}

// ---------------------------------------------------------------------------
// 0x00a80a40 -- retire the index of every particle and release the owner
// ---------------------------------------------------------------------------
// @ 0x00a80a40
void SurfaceDecals::ClearParticles() {
  DecalNode* node = mListA4.mNext
      ? (DecalNode*)((char*)mListA4.mNext - 4) : 0;
  DecalNode* end = (DecalNode*)((char*)&mListA4 - 4);
  while (node != end) {
    if (node->mIndex >= 0) {
      void* owner = mObj14;
      VtFn1 fn = (VtFn1)VtSlot(VtblOf(owner), 0x1c);
      fn(owner, node->mIndex);
      node->mIndex = -1;
    }
    node = node->mNext
        ? (DecalNode*)((char*)node->mNext - 4) : 0;
  }
  void* owner = mObj14;
  if (owner != 0) {
    mObj14 = 0;
    VtFn0 fn = (VtFn0)VtSlot(VtblOf(owner), 0x04);
    fn(owner);
  }
}

// ---------------------------------------------------------------------------
// 0x00a80ac0 -- SurfaceDecals base constructor
// ---------------------------------------------------------------------------
// @ 0x00a80ac0
SurfaceDecals* SurfaceDecals::BaseCtor() {
  float v = g_1564cc8;
  m8 = 0;
  mVtbl4 = 0;
  mVtbl0 = &g_vtblSurfaceDecals;
  mC = -1;
  mObj14 = 0;
  m18 = 0;
  m1c = 0;
  m28 = v;
  m2c = v;
  m30 = v;
  float nv = -v;
  m34 = nv;
  m38 = nv;
  m3c = nv;
  return this;
}

// ---------------------------------------------------------------------------
// 0x00a80b80 -- reset: drain the +0xac cell list, clear the +0xa4 anchors
// ---------------------------------------------------------------------------
// @ 0x00a80b80
bool SurfaceDecals::Reset() {
  if (mObj14 != 0)
    ClearParticles();

  IntrusiveList* anchor = &mListAC;
  while (anchor->mPrev != anchor) {
    CellDataNode* first = (CellDataNode*)anchor->mNext;
    CellDataNode* next = first->mNext;
    next->mPrev = (CellDataNode*)anchor;
    anchor->mNext = (IntrusiveList*)next;
    if (first != (CellDataNode*)anchor) {
      first->mPrev = 0;
      first->mNext = 0;
    }
    if (first != 0)
      FreeMem(first);
  }

  IntrusiveList* anchorA4 = &mListA4;
  uint32_t* p = (uint32_t*)mListA4.mNext;
  if (p != (uint32_t*)anchorA4) {
    do {
      uint32_t next = *p;
      p[1] = 0;
      p[0] = 0;
      p = (uint32_t*)next;
    } while (p != (uint32_t*)anchorA4);
  }
  mListA4.mPrev = anchorA4;
  mListA4.mNext = anchorA4;
  return true;
}

// ---------------------------------------------------------------------------
// 0x00a80c00 -- EASTL hash-table find-or-insert
// ---------------------------------------------------------------------------
// @ 0x00a80c00
InsertResult* HashTable::Insert(InsertResult* out, const uint32_t* key,
                                uint32_t /*unused*/) {
  uint32_t h = key[0] % mBucketCount;
  HashNode** bucket = mBuckets + h;
  HashNode* node = *bucket;
  while (node != 0) {
    if (node->mKey[0] == key[0] && node->mKey[1] == key[1]) {
      out->mNode = node;
      out->mFlag = 0;
      out->mBucket = bucket;
      return out;
    }
    node = node->mNext;
  }

  RehashResult res;
  mPolicy.NeedRehash(&res, mBucketCount, mElementCount, true);
  HashNode* n = (HashNode*)EAAllocate(
      0x18, "EASTL", 0, 0,
      "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
      0xd1);
  if (n != 0) {
    n->mKey[0] = key[0];
    n->mKey[1] = key[1];
    n->mKey[2] = key[2];
    n->mKey[3] = key[3];
  }
  n->mNext = 0;
  if (res.mFlag != 0) {
    h = key[0] % res.mCount;
    Rehash(res.mCount);
  }
  n->mNext = mBuckets[h];
  mBuckets[h] = n;
  ++mElementCount;
  out->mNode = n;
  out->mFlag = 1;
  out->mBucket = mBuckets + h;
  return out;
}

// ---------------------------------------------------------------------------
// 0x00a80d10 -- derived destructor
// ---------------------------------------------------------------------------
// @ 0x00a80d10
void SurfaceDecals::Destroy() {
  mVtbl0 = &g_vtblSurfaceDecalsEx;
  mVtbl4 = &g_vtblSurfaceDecalsEx2;
  mListAC.~IntrusiveList();
  mListA4.~IntrusiveList();

  mHash.DoFreeNodes(mHash.mBuckets, mHash.mBucketCount);
  mHash.mElementCount = 0;
  if (mHash.mBucketCount > 1)
    FreeMem(mHash.mBuckets);

  FreeArray(mArray70);
  FreeArray(mArray58);

  if (mObj14 != 0) {
    void* owner = mObj14;
    VtFn0 fn = (VtFn0)VtSlot(VtblOf(owner), 0x04);
    fn(owner);
  }
  if (mObj10 != 0) {
    void* owner = mObj10;
    VtFn0 fn = (VtFn0)VtSlot(VtblOf(owner), 0x00);
    fn(owner);
  }
  mVtbl4 = &g_vtblIEventModifier;
}

// ---------------------------------------------------------------------------
// 0x00a80dd0 -- SimpleVector<CellData*>::DoInsertValue
// ---------------------------------------------------------------------------
// @ 0x00a80dd0
void SimpleVector::DoInsertValue(CellDataNode** pos, CellDataNode** value) {
  if (mEnd != mCap) {
    CellDataNode** v = value;
    if (v >= pos && v < mEnd)
      ++v;
    if (mEnd != 0)
      *mEnd = mEnd[-1];
    int bytes = (int)((char*)(mEnd - 1) - (char*)pos);
    int rounded = (bytes >> 2) << 2;
    memmove((char*)mEnd - rounded, pos, (size_t)bytes);
    *pos = *v;
    ++mEnd;
    return;
  }

  int n = (int)(mEnd - mBegin);
  CellDataNode** newBuf;
  if (n == 0) {
    n = 1;
    newBuf = 0;
  } else {
    n *= 2;
    if (n == 0) {
      newBuf = 0;
    } else {
      newBuf = (CellDataNode**)EAAllocate(
          n * 4, "EASTL", 0, 0,
          "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
          0xd1);
    }
  }
  int off = (int)((char*)pos - (char*)mBegin);
  char* base = (char*)memcpy(newBuf, mBegin, (size_t)off);
  char* p = base + ((off >> 2) << 2);
  if (p != 0)
    *(CellDataNode**)p = *value;
  int tail = (int)((char*)mEnd - (char*)pos);
  char* base2 = (char*)memcpy(p + 4, pos, (size_t)tail);
  char* newEnd = base2 + ((tail >> 2) << 2);
  FreeArray(mBegin);
  mBegin = newBuf;
  mEnd = (CellDataNode**)newEnd;
  mCap = (CellDataNode**)((char*)newBuf + n * 4);
}

// ---------------------------------------------------------------------------
// 0x00a80ee0 -- derived constructor
// ---------------------------------------------------------------------------
// @ 0x00a80ee0
SurfaceDecals* SurfaceDecals::DerivedCtor() {
  mVtbl4 = &g_vtblIEventModifier;
  m8 = 0;
  mVtbl0 = &g_vtblSurfaceDecalsEx;
  mVtbl4 = &g_vtblSurfaceDecalsEx2;
  mC = 0;
  mObj10 = 0;
  mObj14 = 0;
  m30 = 0.0f;
  m34 = 0.0f;
  m38 = 0.0f;
  m40 = 0.0f;
  m44 = 0.0f;
  m48 = 0.0f;
  m18 = 0;
  m4c = g_1457d54;
  m28 = 1.0f;
  m2c = 1.0f;
  m3c = 1.0f;
  m20 = -1;
  m24 = -1;
  m50 = -1;
  m54 = -1;
  mArray58 = 0;
  m5c = 0;
  m60 = 0;
  mArray70 = 0;
  m74 = 0;
  m78 = 0;
  mHash.mPolicy.mMaxLoad = 1.0f;
  mHash.mPolicy.mGrowth = g_1470f1c;
  mHash.mElementCount = 0;
  mHash.mPolicy.mNextResize = 0;
  mHash.mBucketCount = 1;
  mHash.mBuckets = (HashNode**)&g_staticBuckets;
  mListA4.mPrev = &mListA4;
  mListA4.mNext = &mListA4;
  mListAC.mPrev = &mListAC;
  mListAC.mNext = &mListAC;
  return this;
}

// ---------------------------------------------------------------------------
// 0x00a80fe0 -- remove a cell node from the +0xac list
// ---------------------------------------------------------------------------
// @ 0x00a80fe0
void SurfaceDecals::RemoveCell(CellDataNode* cell) {
  if (mListAC.mPrev == &mListAC)
    return;

  CellDataNode* node = (CellDataNode*)((char*)cell - 8);
  SurfaceDecalState* state = node->mState;
  CellDataNode** begin = state->mVector.mBegin;
  CellDataNode** end = state->mVector.mEnd;
  int count = (int)(end - begin);
  for (int i = 0; i < count; ++i) {
    if (begin[i] == node) {
      CellDataNode** dst = begin + i;
      CellDataNode** src = dst + 1;
      if (src < end)
        memcpy(dst, src, (char*)end - (char*)src);
      state->mVector.mEnd = end - 1;
      break;
    }
  }

  state = node->mState;
  if (state->mVector.mBegin == state->mVector.mEnd && state->mIndex >= 0) {
    void* owner = mObj14;
    VtFn1 fn = (VtFn1)VtSlot(VtblOf(owner), 0x1c);
    fn(owner, state->mIndex);
    state->mIndex = -1;
  }

  CellDataNode* next = node->mNext;
  CellDataNode* prev = node->mPrev;
  prev->mNext = next;
  next->mPrev = prev;
  node->mNext = 0;
  node->mPrev = 0;
  FreeMem(node);
}
