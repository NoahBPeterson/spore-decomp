// src/game/SPGonzago/SPFormationUtilities.cpp -- migrated from slice(s) s00afbaf0, s00afab70 by tools/migrate/rewrite.py
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

// ---- items of slice s00afbaf0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float    g_f2f1c;            // 0x01470f1c
extern float    g_f8a0;             // 0x013eb8a0
extern float    g_fSpace;           // 0x0167aec4
extern float    g_fSpaceB;          // 0x0167aec8
extern float    g_fSpaceC;          // 0x0167aecc
extern float    g_fVec7c;           // 0x0156737c
extern float    g_fVec80;           // 0x01567380
extern float    g_fVec84;           // 0x01567384
extern float    g_fVec88;           // 0x01567388
extern float    g_f8c5448;          // 0x01485548
extern float    g_f3eb1bc;          // 0x013eb1bc
extern int32_t  g_nSlots;           // 0x0156734c
extern void*    g_pSlotVtable;      // 0x0154df28
extern float    g_f1_48;            // 0x01485720  (1.0f)
struct tFloat4 {
    float       x;
    float       y;
    float       z;
    void*       pCtx;

    tFloat4() {}
    tFloat4(const tFloat4& o) { x = o.x; y = o.y; z = o.z; pCtx = o.pCtx; }
    ~tFloat4() {}
};
void    __stdcall FUN_00afb0d0(void* pOut, const void* pKey);                   // 0x00afb0d0
void    __cdecl FUN_00afb8f0(int32_t* pBase, int32_t nFirst, int32_t nCount, int32_t nRoot,
                             int32_t nKey, tFloat4 v);                          // 0x00afb8f0
void    __cdecl FUN_00afbf40(int32_t* pBase, int32_t* pLast, tFloat4 v);        // 0x00afbf40
void    __cdecl FUN_00afbfb0(int32_t* pBase, int32_t* pLast, tFloat4 v);        // 0x00afbfb0
class tSlot {
public:
    virtual void    v00();
    virtual void    v04();                          // +0x04 destructor slot
    void*           mpOwned;                        // +0x04  (owned sub-object pointer)
    uint8_t         mPad08[0x18 - 0x08];

    void        CopyConstruct(const tSlot& src);    // 0x00afa110 (thiscall)
    void        Assign(const tSlot& src);           // 0x00afa230 (thiscall)
};
class cSlotVec {
public:
    tSlot*  mpBegin;                                // +0x00
    tSlot*  mpEnd;                                  // +0x04
    tSlot*  mpCap;                                  // +0x08

    tSlot*      EraseRange(tSlot* pFirst, tSlot* pLast);        // 0x00afc0d0
    void        InsertOne(tSlot* pPos, tSlot* pValue);          // 0x00afc150
};
class cActionCircle {
public:
    cSlotVec    mSlots;                             // +0x000  (slot vector: begin/end/cap)
    int32_t     mnField0c;                          // +0x00c
    int32_t     mnField10;                          // +0x010
    int32_t     mnField14;                          // +0x014
    float       mf18;                               // +0x018 (inline slot buffer x)
    float       mf1c;                               // +0x01c
    float       mf20;                               // +0x020
    float       mf24;                               // +0x024
    int32_t     mnField28;                          // +0x028
    int32_t     mnField2c;                          // +0x02c
    int32_t     mnField30;                          // +0x030
    int32_t     mnField34;                          // +0x034
    int32_t     mnField38;                          // +0x038
    void*       mpField3c;                          // +0x03c
    int32_t     mnField40;                          // +0x040
    int32_t     mnField44;                          // +0x044
    float       mfField48;                          // +0x048
    float       mfField4c;                          // +0x04c
    cSlotVec    mSlots2;                            // +0x050  (second slot vector)
    float       mf5c;                               // +0x05c
    int32_t     mn60;                               // +0x060
    float       mf64;                               // +0x064
    float       mf68;                               // +0x068
    float       mf6c;                               // +0x06c
    float       mf70;                               // +0x070
    float       mf74;                               // +0x074
    float       mf78;                               // +0x078
    float       mf7c;                               // +0x07c
    float       mf80;                               // +0x080
    float       mf84;                               // +0x084
    float       mf88;                               // +0x088
    float       mf8c;                               // +0x08c
    float       mf90;                               // +0x090
    float       mf94;                               // +0x094
    uint8_t     mb98;                               // +0x098
    uint8_t     mPad99[3];                          // +0x099
    float       mf9c;                               // +0x09c
    float       mfa0;                               // +0x0a0
    float       mfa4;                               // +0x0a4
    float       mfa8;                               // +0x0a8
    float       mfac;                               // +0x0ac
    float       mfb0;                               // +0x0b0
    float       mfb4;                               // +0x0b4
    float       mfb8;                               // +0x0b8
    float       mfbc;                               // +0x0bc
    float       mfc0;                               // +0x0c0
    float       mfc4;                               // +0x0c4 (unwritten in ctor)
    uint8_t     mbc8;                               // +0x0c8
    uint8_t     mPadc9[3];                          // +0x0c9
    float       mfcc;                               // +0x0cc
    float       mfd0;                               // +0x0d0
    float       mfd4;                               // +0x0d4
    float       mfd8;                               // +0x0d8
    int32_t     mdc;                                // +0x0dc
    int32_t     me0;                                // +0x0e0
    int32_t     me4;                                // +0x0e4
    int32_t     me8;                                // +0x0e8 (unwritten in ctor)
    int32_t     mec;                                // +0x0ec (unwritten in ctor)
    int32_t     mf0;                                // +0x0f0
    int32_t     mf4;                                // +0x0f4
    int32_t     mf8;                                // +0x0f8
    float       mffc;                               // +0x0fc (unwritten in ctor)
    float       mf100;                              // +0x100 (unwritten in ctor)
    float       mf104;                              // +0x104
    float       mf108;                              // +0x108
    float       mf10c;                              // +0x10c
    float       mf110;                              // +0x110
    float       mf114;                              // +0x114
    float       mf118;                              // +0x118
    float       mf11c;                              // +0x11c
    float       mf120;                              // +0x120
    float       mf124;                              // +0x124
    float       mf128;                              // +0x128 (unwritten in ctor)
    uint8_t     mbc12c;                             // +0x12c
    uint8_t     mPad12d[3];                         // +0x12d
    float       mf130;                              // +0x130
    float       mf134;                              // +0x134
    float       mf138;                              // +0x138
    float       mf13c;                              // +0x13c
    int32_t     m140;                               // +0x140
    int32_t     m144;                               // +0x144
    int32_t     m148;                               // +0x148
    int32_t     m14c;                               // +0x14c (unwritten in ctor)
    int32_t     m150;                               // +0x150 (unwritten in ctor)
    int32_t     m154;                               // +0x154
    int32_t     m158;                               // +0x158
    int32_t     m15c;                               // +0x15c
    int32_t     m160;                               // +0x160 (unwritten in ctor)
    int32_t     m164;                               // +0x164 (unwritten in ctor)
    int32_t     m168;                               // +0x168
    int32_t     m16c;                               // +0x16c
    int32_t     m170;                               // +0x170
    int32_t     mnField174;                         // +0x174

    cActionCircle();                                // 0x00afbaf0
    bool        EraseOne(tSlot* pPos);              // 0x00afc410
};
struct tInsertArgs {
    int32_t     nKey;                               // +0x00
    float       f0;                                 // +0x04
    float       f1;                                 // +0x08
    float       f2;                                 // +0x0c
    float       f3;                                 // +0x10
    float       f4;                                 // +0x14
    float       f5;                                 // +0x18
    float       f6;                                 // +0x1c
};
struct cSearchHost {
    int32_t     mnField00;                          // +0x00
    int32_t*    mpTable;                            // +0x04
    int32_t     mnIndex;                            // +0x08

    int32_t*    FindAndInsert(const void* pKey);    // 0x00afc030
    struct tHint { char c; };
    void        FUN_00afb7e0(void* pA, void* pB, tHint hint); // 0x00afb7e0
};
// ---- items of slice s00afbaf0 end

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
    do {
      HashNode* node = *link;
      if (key == node->mKey) break;
      link = &node->mpNext;
    } while (*link);
    while (*link) {
      HashNode* del = *link;
      if (key != del->mKey) break;
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

// @ 0x00afbaf0
cActionCircle::cActionCircle()
{
    mnField14 = 0;
    mSlots.mpBegin = (tSlot*)((char*)this + 0x18);
    mSlots.mpEnd = (tSlot*)((char*)this + 0x18);
    mSlots.mpCap = (tSlot*)((char*)this + 0x38);
    mfField4c = g_f2f1c;
    mfField48 = g_f1_48;
    mnField40 = 1;
    mpField3c = &g_pSlotVtable;
    mnField44 = 0;
    mSlots2.mpBegin = 0;
    mSlots2.mpCap = 0;
    mf5c = 0.0f;
    mn60 = 0;
    mf64 = g_fSpace;
    mf68 = g_fSpaceB;
    mf6c = g_fSpaceC;
    mf70 = g_fSpace;
    mf74 = g_fSpaceB;
    mf78 = g_fSpaceC;
    mf7c = 0.0f;
    mf80 = 0.0f;
    mf84 = g_f1_48;
    mf88 = g_f1_48;
    mf8c = g_f8c5448;
    mf90 = g_f3eb1bc;
    mf94 = g_f8a0;
    mb98 = 0;
    mf9c = g_f1_48;
    mfa0 = g_fSpace;
    mfa4 = g_fSpaceB;
    mfa8 = g_fSpaceC;
    mfac = g_f3eb1bc;
    mfb0 = g_f3eb1bc;
    mfb4 = g_fSpace;
    mfb8 = g_fSpaceB;
    mfbc = g_fSpaceC;
    mfc0 = 0.0f;
    mbc8 = 0;
    mfcc = g_fVec7c;
    mfd0 = g_fVec80;
    mfd4 = g_fVec84;
    mfd8 = g_fVec88;
    mdc = 0;
    me0 = 0;
    me4 = 0;
    mf0 = 0;
    mf4 = 0;
    mf8 = 0;
    mf104 = g_fSpace;
    mf108 = g_fSpaceB;
    mf10c = g_fSpaceC;
    mf110 = g_f3eb1bc;
    mf114 = g_f3eb1bc;
    mf118 = g_fSpace;
    mf11c = g_fSpaceB;
    mf120 = g_fSpaceC;
    mbc12c = 0;
    mf124 = 0.0f;
    mf130 = g_fVec7c;
    mf134 = g_fVec80;
    mf138 = g_fVec84;
    mf13c = g_fVec88;
    m140 = 0;
    m144 = 0;
    m148 = 0;
    m154 = 0;
    m158 = 0;
    m15c = 0;
    m168 = 0;
    m16c = 0;
    m170 = 0;
    mnField174 = g_nSlots++;
}

// @ 0x00afbf40
void __cdecl FUN_00afbf40(int32_t* pBase, int32_t* pLast, tFloat4 v)
{
    int32_t nCount = (int32_t)(pLast - pBase);
    if (nCount >= 2) {
        int32_t i = ((nCount - 2) >> 1) + 1;
        do {
            i = i - 1;
            FUN_00afb8f0(pBase, i, nCount, i, pBase[i], v);
        } while (i != 0);
    }
}

// @ 0x00afbfb0
void __cdecl FUN_00afbfb0(int32_t* pBase, int32_t* pLast, tFloat4 v)
{
    int32_t nCount = (int32_t)((char*)pLast - (char*)pBase) >> 2;
    if (nCount > 1) {
        int32_t* p = pLast - 1;
        do {
            int32_t nKey = *p;
            *p = *pBase;
            FUN_00afb8f0(pBase, 0, nCount - 1, 0, nKey, v);
            p = p - 1;
            nCount = (int32_t)(p + 1 - pBase);
        } while (nCount > 1);
    }
}

// @ 0x00afc030
int32_t* cSearchHost::FindAndInsert(const void* pKey)
{
    int32_t aSlot[3];
    FUN_00afb0d0(aSlot, pKey);
    if (aSlot[0] == mpTable[mnIndex]) {
        tInsertArgs aValue;
        aValue.nKey = *(int32_t*)pKey;
        aValue.f0 = 0.0f;
        aValue.f1 = g_fSpace;
        aValue.f2 = g_fSpaceB;
        aValue.f3 = g_fSpaceC;
        aValue.f4 = g_fSpace;
        aValue.f5 = g_fSpaceB;
        aValue.f6 = g_fSpaceC;
        tHint hint;
        hint.c = 0;
        FUN_00afb7e0(aSlot, &aValue, hint);
    }
    return (int32_t*)(aSlot[0] + 4);
}
