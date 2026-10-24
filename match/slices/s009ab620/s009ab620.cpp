// nSPCreatureAnim baked-animation helpers and the baked_anim_manager event maps.
// Flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

extern "C" float sqrtf(float);

// Global color scale used to pack/unpack 10:11:11 vertex attributes.
extern float g_colorScale;      // 0x0166c0d8
// Baked-animation id generator.
extern uint32_t g_bakedAnimIdCounter;   // 0x0166c0c8
// Non-zero selects the random frame-sampling eviction cursor (see FUN_009abbb0).
extern int g_bakedAnimEvictSampling;    // 0x01550a98

namespace nSPCreatureAnim {

struct baked_animation_data;

struct baked_animation {
  baked_animation_data* mpData;   // +0x00
  uint32_t field_04;              // +0x04
  uint32_t mID;                   // +0x08
  char mName[0x104];              // +0x0c
  int field_110;                  // +0x110

  void Init(bool bReset);
  float GetScale() const;
  void* GetFrame(int index) const;
};

struct baked_animation_data {
  char pad_00[0xc];
  uint32_t mCount;      // +0x0c
  char pad_10[4];
  float mScale;         // +0x14
  char pad_18[0x20];
  // frames begin at +0x38
};

}  // namespace nSPCreatureAnim

extern "C" void EASTL_allocator_deallocate(void* p);   // 0x00f47380

// @ 0x009AC250
void nSPCreatureAnim::baked_animation::Init(bool bReset) {
  if (bReset) {
    mpData = 0;
    field_110 = 0;
  }
  EASTL_allocator_deallocate(mpData);
  mpData = 0;
  field_04 = 0;
  mID = g_bakedAnimIdCounter;
  g_bakedAnimIdCounter++;
  mName[0] = 0;
}

// @ 0x009AC2B0
__declspec(noinline) float nSPCreatureAnim::baked_animation::GetScale() const {
  return mpData ? mpData->mScale : 0.0f;
}

// @ 0x009AC2E0
void* nSPCreatureAnim::baked_animation::GetFrame(int index) const {
  uint32_t count = mpData->mCount;
  return (char*)mpData + 0x38 + (count * 8 + 0x54) * index;
}

// ---------------------------------------------------------------------------------------------
// Color (10:11:11) pack/unpack helpers.

// @ 0x009AC300  (unpack packed RGB into 3 floats scaled by g_colorScale)
void __cdecl UnpackColor(uint32_t packed, float* out) {
  out[0] = ((float)(packed >> 0x15) * 0.00048875855f - 0.5f) * g_colorScale;
  out[1] = ((float)((packed >> 0xa) & 0x7ff) * 0.00048875855f - 0.5f) * g_colorScale;
  out[2] = ((float)(packed & 0x3ff) * 0.0009784736f - 0.5f) * g_colorScale;
}

// @ 0x009AC390  (pack 3 floats to a 10:11:11 value)
void __cdecl PackColor(const float* in, uint32_t* out) {
  float t = in[0] / g_colorScale + 0.5f;
  if (t > 0.0f) {
    if (t > 1.0f)
      t = 1.0f;
  } else {
    t = 0.0f;
  }
  *out = (uint32_t)(int)(t * 2046.0f) << 0x15;

  t = in[1] / g_colorScale + 0.5f;
  if (t > 0.0f) {
    if (t > 1.0f)
      t = 1.0f;
  } else {
    t = 0.0f;
  }
  *out |= (uint32_t)(int)(t * 2046.0f) << 0xa;

  t = in[2] / g_colorScale + 0.5f;
  if (t > 0.0f) {
    if (t > 1.0f)
      t = 1.0f;
  } else {
    t = 0.0f;
  }
  *out |= (uint32_t)(int)(t * 1022.0f);
}

// @ 0x009AC460  (unpack 3 bytes to floats, then derive the 4th component)
void __cdecl UnpackBytes(const uint8_t* in, float* out) {
  out[0] = ((float)in[0] * 0.0039370079f - 0.5f) * 2.0f;
  out[1] = ((float)in[1] * 0.0039370079f - 0.5f) * 2.0f;
  out[2] = ((float)in[2] * 0.0039370079f - 0.5f) * 2.0f;

  float q = 1.0f - out[0] * out[0] - out[1] * out[1] - out[2] * out[2];
  if (q > 0.0f) {
    if (q > 1.0f)
      q = 1.0f;
  } else {
    q = 0.0f;
  }
  out[3] = sqrtf(q);
}

// =============================================================================================
// nSPCreatureAnim::baked_anim_manager
//
// Layout recovered from the disassembly (retail differs from the 2008 dev PDB):
//   +0x00  uint32 mBakedAnimCacheSize
//   +0x04  eastl::map<baked_anim_cache_key, baked_anim_cache_value>  mBakedAnimCache
//   +0x20  eastl::map<creature_static_data const*, creature_instance_data*> mSpeciesInstances
//   +0x3c  baked_anim_cache_key mLastUpdatedKey
// Each eastl::map is 0x1c bytes: mCompare(+0), anchor(right,left,parent,color)(+4),
// mnSize(+0x14), allocator(+0x18).  Node base is 0x10 bytes (3 pointers + color), then the pair.

namespace nSPCreatureAnim {

struct creature_static_data;
struct creature_instance_data;
struct animation_instance_data;

struct rbtree_node_base {
  rbtree_node_base* mpNodeRight;
  rbtree_node_base* mpNodeLeft;
  rbtree_node_base* mpNodeParent;
  char mColor;
  char mPad[3];
};

struct baked_anim_cache_key {
  void* mSpecies;      // +0x0  AutoRefCount<creature_static_data const>
  uint32_t mAnimKey;   // +0x4
  uint32_t mPad;       // +0x8
  uint32_t mAnimID;    // +0xc
};

struct baked_anim_cache_value {
  void* mpAnimation;   // +0x0  AutoRefCount<animation_instance_data>
  void* mpBaked;       // +0x4  AutoRefCount<baked_animation>
  uint32_t mField8;    // +0x8
};

struct baked_cache_node {
  rbtree_node_base base;       // +0x00
  baked_anim_cache_key key;    // +0x10
  baked_anim_cache_value val;  // +0x20
};

struct species_node {
  rbtree_node_base base;   // +0x00
  void* mSpecies;          // +0x10
  void* mInstance;         // +0x14
};

struct rbtree_layout {
  int mCompare;              // +0x00
  rbtree_node_base mAnchor;  // +0x04
  uint32_t mnSize;           // +0x14
  void* mAllocator;          // +0x18
};

struct baked_anim_manager {
  uint32_t mBakedAnimCacheSize;      // +0x00
  rbtree_layout mBakedAnimCache;     // +0x04
  rbtree_layout mSpeciesInstances;   // +0x20
  baked_anim_cache_key mLastUpdatedKey;  // +0x3c
};

}  // namespace nSPCreatureAnim

// --- out-of-line helpers (masked relocations; signatures inferred from the calls) ---
extern "C" void __fastcall FUN_009c26a0(void* p);   // release creature_static_data auto-ref
extern "C" void __fastcall FUN_009a3630(void* p);   // release animation_instance_data
extern "C" void __fastcall FUN_009ae1c0(void* p);   // release baked_animation
extern "C" void __fastcall FUN_009c4cc0(void* p);   // creature_instance_data::Release
extern "C" void __fastcall FUN_009c4d10(void* p);   // creature_instance_data::Clear-ish
extern "C" void __fastcall FUN_009a3080(void* p);   // animation_instance_data teardown
extern "C" void* RBTreeIncrement(const nSPCreatureAnim::rbtree_node_base* pNode);   // 0x00921580
extern "C" void RBTreeErase(nSPCreatureAnim::rbtree_node_base* pNode,
                            nSPCreatureAnim::rbtree_node_base* pAnchor);
struct MgrHelper {
  void RemoveNode(void** pNode);        // 0x009ab4a0
  void NukeSpeciesTree(void* node);     // 0x009aaed0
  void NukeBakedTree(void* node);       // 0x009aae10
};
struct AnimInstanceHelper { void Detach(); };  // 0x0099c970

// @ 0x009AB620
void __fastcall ClearBakedAnimManager(nSPCreatureAnim::baked_anim_manager* self) {
  using namespace nSPCreatureAnim;
  if (self->mLastUpdatedKey.mSpecies) {
    void* p = self->mLastUpdatedKey.mSpecies;
    self->mLastUpdatedKey.mSpecies = 0;
    FUN_009c26a0(p);
  }
  self->mLastUpdatedKey.mAnimKey = 0;
  self->mLastUpdatedKey.mPad = 0;
  self->mLastUpdatedKey.mAnimID = 0;

  baked_cache_node* anchor = (baked_cache_node*)&self->mBakedAnimCache.mAnchor;
  baked_cache_node* node = (baked_cache_node*)self->mBakedAnimCache.mAnchor.mpNodeLeft;
  if (node != anchor) {
    do {
      baked_cache_node* cur = node;
      ((MgrHelper*)self)->RemoveNode((void**)&cur);
      self->mBakedAnimCache.mnSize--;
      baked_cache_node* next = (baked_cache_node*)RBTreeIncrement(&cur->base);
      RBTreeErase(&cur->base, &self->mBakedAnimCache.mAnchor);
      if (cur->val.mpBaked)
        FUN_009ae1c0(cur->val.mpBaked);
      if (cur->val.mpAnimation)
        FUN_009a3630(cur->val.mpAnimation);
      if (cur->key.mSpecies)
        FUN_009c26a0(cur->key.mSpecies);
      EASTL_allocator_deallocate(cur);
      node = next;
    } while (node != anchor);
  }

  species_node* anchor2 = (species_node*)&self->mSpeciesInstances.mAnchor;
  species_node* node2 = (species_node*)self->mSpeciesInstances.mAnchor.mpNodeLeft;
  if (node2 != anchor2) {
    do {
      species_node* cur = node2;
      FUN_009c4d10(cur->mInstance);
      self->mSpeciesInstances.mnSize--;
      species_node* next = (species_node*)RBTreeIncrement(&cur->base);
      RBTreeErase(&cur->base, &self->mSpeciesInstances.mAnchor);
      if (cur->mInstance)
        FUN_009c4cc0(cur->mInstance);
      if (cur->mSpecies)
        FUN_009c26a0(cur->mSpecies);
      EASTL_allocator_deallocate(cur);
      node2 = next;
    } while (node2 != anchor2);
  }
}

// @ 0x009ABCE0  (destructor: Clear + member destructors, reverse declaration order)
void __fastcall DestroyBakedAnimManager(nSPCreatureAnim::baked_anim_manager* self) {
  ClearBakedAnimManager(self);
  if (self->mLastUpdatedKey.mSpecies) {
    void* p = self->mLastUpdatedKey.mSpecies;
    self->mLastUpdatedKey.mSpecies = 0;
    FUN_009c26a0(p);
  }
  ((MgrHelper*)&self->mSpeciesInstances)
      ->NukeSpeciesTree(self->mSpeciesInstances.mAnchor.mpNodeParent);
  ((MgrHelper*)&self->mBakedAnimCache)
      ->NukeBakedTree(self->mBakedAnimCache.mAnchor.mpNodeParent);
}

// ---------------------------------------------------------------------------------------------
// The remaining baked_anim_manager methods below are reconstructed skeletons: their control
// flow and callees are described, but the deep inlined EASTL/timer passes are not reproduced.

// @ 0x009AB710  PARTIAL
// Removes one entry from mSpeciesInstances keyed by the node inside *param_2, and (when the
// per-species instance list becomes empty) drops the species' baked-animation cache entries.
// __thiscall (ecx = the manager) with two stack arguments, callee-clean (ret 8): modelled as
// __fastcall with an unused EDX filler.  Its eax is whatever the body last computed, so callers
// that leak eax hand it through.
void* __fastcall RemoveSpeciesEntry(void* self, void* edxUnused, void* ppNode, uint32_t id);

__declspec(noinline) void* __fastcall RemoveSpeciesEntry(void* self, void* edxUnused, void* ppNode, uint32_t id) {
  (void)self; (void)edxUnused; (void)ppNode; (void)id;
  return 0;
}

// @ 0x009AB7C0  PARTIAL
// Inserts a baked_anim_cache entry (lower_bound + DoInsertValueImpl) and returns the node.
void* __fastcall InsertBakedCacheEntry(void* self, void* key) {
  (void)self; (void)key;
  return 0;
}

// @ 0x009AB890  PARTIAL
// Maintains mBakedAnimCacheSize: repeatedly evicts least-recently-used baked cache nodes until
// the size drops to (int)(DAT_01550b80 * 0.6), then resets mLastUpdatedKey.
void __fastcall TrimBakedAnimCache(void* self) {
  (void)self;
}

// @ 0x009ABA80  PARTIAL
// RemoveAllEventsOfSameType: finds all mSpeciesInstances sharing an animation id and detaches
// up to `count` of them.
uint32_t __fastcall FUN_009aba80(void* self, void* key, uint32_t count) {
  (void)self; (void)key; (void)count;
  return 0;
}

// @ 0x009ABBB0
// Eviction-cursor advance for one mBakedAnimCache node.  Retail first bails out when the node's
// animation is already at the sampled end (val.mpBaked->field_04 == mpData->field_10).  With the
// sampling global off it simply bumps the node cursor (wrapping at the frame range) and hands the
// cursor value to RemoveSpeciesEntry; with it on it derives a frame index from a van-der-Corput
// style radical inverse of the cursor, scaled to [0, frameRange-1], then retries while the picked
// frame's first byte has bit 0 set.  __thiscall with one stack argument (ret 4); eax is left at
// whatever the last step produced, so the routine is declared to return it.
void* __fastcall FUN_009abbb0(void* self, void* edxUnused, void** ppNode) {
    using namespace nSPCreatureAnim;
    baked_cache_node* node = (baked_cache_node*)*ppNode;
    baked_animation* anim = (baked_animation*)node->val.mpBaked;
    uint32_t end = anim->mpData ? *(uint32_t*)((char*)anim->mpData + 0x10) : 0;
    if (anim->field_04 == end)
        return *ppNode;
    if (g_bakedAnimEvictSampling == 0) {
        uint32_t cur = node->val.mField8;
        node->val.mField8 = cur + 1;
        uint32_t e = anim->mpData ? *(uint32_t*)((char*)anim->mpData + 0x10) : 0;
        if (node->val.mField8 >= e)
            node->val.mField8 = 0;
        return RemoveSpeciesEntry(self, 0, ppNode, cur);
    }
    for (;;) {
        node = (baked_cache_node*)*ppNode;
        uint32_t cur = node->val.mField8;
        int bits = 0;
        for (uint32_t x = cur; x != 0; x >>= 1)
            bits++;
        uint32_t rem = cur % (1u << ((bits - 1) & 31));
        anim = (baked_animation*)node->val.mpBaked;
        uint32_t cnt = anim->mpData ? *(uint32_t*)((char*)anim->mpData + 0x10) : 0;
        long double v = (long double)(uint32_t)(2 * rem + 1) / (long double)(int)(1u << (bits & 31));
        v = v * (long double)(uint32_t)(cnt - 1) + 0.5L;
        float f = (float)v;
        // Retail takes (int)floor(f), compiled inline as cvtss2si + "if (f < (float)r) r--";
        // values >= 2^31 keep cvtss2si's 0x80000000 result (MSVC's x87 __ftol2 helper would
        // instead return the low dword of a 64-bit result).
        int idx;
        if (f >= 2147483648.0f) {
            idx = (int)0x80000000u;
        } else {
            idx = (int)f;
            if ((float)idx > f)
                idx--;
        }
        node->val.mField8 = node->val.mField8 + 1;
        void* frame = anim->GetFrame(idx);
        if ((*(unsigned char*)frame & 1) == 0)
            return RemoveSpeciesEntry(self, 0, ppNode, (uint32_t)idx);
    }
}

// @ 0x009ABD10  PARTIAL
// Creates (or fetches) the creature_instance_data (0x1930 bytes, "Anim/bam/new_cid") for the
// species, initialises it and inserts it into mSpeciesInstances.
void* __fastcall CreateCreatureInstance(void* self, void* key, uint32_t existing) {
  (void)self; (void)key; (void)existing;
  return 0;
}

// @ 0x009ABE90  PARTIAL
// Higher-level "get/create creature for species and build its animation instance" entry point.
void __fastcall FUN_009abe90(void* self, void* key, void* p3, void* p4, void* p5) {
  (void)self; (void)key; (void)p3; (void)p4; (void)p5;
}

// --- EA::LimitStopwatch and the eastl map key helpers used by RestartTimer ---
namespace EA {
struct Stopwatch {
  int64_t mnStartTime;      // +0x00
  int64_t mnElapsedTime;    // +0x08
  int32_t mnUnits;          // +0x10
  float mfUnitsToSeconds;   // +0x14
};
struct LimitStopwatch : Stopwatch {
  int64_t mnEndTime;        // +0x18  QPC tick deadline
};
}  // namespace EA

union LARGE_INTEGER_ {
  struct { uint32_t LowPart; int32_t HighPart; };
  int64_t QuadPart;
};
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(LARGE_INTEGER_* t);

// EA::Stopwatch::Stopwatch(int units, bool start) - __thiscall (ecx = this, ret 8).
extern "C" void __fastcall FUN_0093a560(void* self, void* edxUnused, int units, int start);
// EA::LimitStopwatch::SetTimeLimit(unsigned limit, bool restart) - __thiscall (ret 8).
extern "C" void __fastcall FUN_0093a480(void* self, void* edxUnused, uint32_t limit, int restart);
// eastl::map::lower_bound(key): writes the first node >= key into *out (ecx = map, ret 8).
extern "C" void __fastcall FUN_009aa500(void* map, void* edxUnused, void** out, const void* key);
// baked_anim_cache_key::operator=(const key&) (ecx = destination, ret 4).
extern "C" void __fastcall FUN_009aa770(void* lhs, void* edxUnused, const void* rhs);

// @ 0x009AC130
// RestartTimer: walks mBakedAnimCache from mLastUpdatedKey under an EA::LimitStopwatch,
// advancing each entry's eviction cursor (FUN_009abbb0) until the time budget expires or a
// full pass makes no change.  __thiscall with one float stack argument (ret 4): modelled as
// __fastcall with an unused EDX filler.
bool __fastcall RestartTimer(void* self, void* edxUnused, float seconds) {
  (void)edxUnused;
  using namespace nSPCreatureAnim;
  baked_anim_manager* mgr = (baked_anim_manager*)self;

  // The budget is rounded (fistp, round-half-to-even) to whole microseconds; SetTimeLimit only
  // keeps the low 32 bits.
  // EA's budget conversion: the microsecond count is rounded (fistp, round-half-to-even) to an
  // int64; SetTimeLimit only keeps the low 32 bits.  A C cast would go through __ftol2, which
  // truncates, so the conversion is written out.
  float usec = seconds * 1000000.0;
  int64_t ticks;
  __asm {
    fld dword ptr [usec]
    fistp qword ptr [ticks]
  }

  EA::LimitStopwatch sw;
  FUN_0093a560(&sw, 0, 3, 0);
  FUN_0093a480(&sw, 0, (uint32_t)ticks, 1);

  void* it;
  FUN_009aa500(&mgr->mBakedAnimCache, 0, &it, &mgr->mLastUpdatedKey);
  baked_cache_node* end = (baked_cache_node*)&mgr->mBakedAnimCache.mAnchor;
  if (it == end)
    it = mgr->mBakedAnimCache.mAnchor.mpNodeLeft;

  char flag = 0;
  void* first = it;
  bool updated = false;
  for (;;) {
    if (it == end) {
      flag = 1;
      break;
    }
    baked_cache_node* node = (baked_cache_node*)it;
    baked_animation* anim = (baked_animation*)node->val.mpBaked;
    uint32_t endFrame = anim->mpData ? *(uint32_t*)((char*)anim->mpData + 0x10) : 0;
    if (anim->field_04 != endFrame) {
      FUN_009abbb0(self, 0, &it);
      updated = true;
    }
    it = RBTreeIncrement((rbtree_node_base*)it);
    if (it == end)
      it = mgr->mBakedAnimCache.mAnchor.mpNodeLeft;
    if (it == first && !updated) {
      flag = 0;
      break;
    }
    LARGE_INTEGER_ now;
    QueryPerformanceCounter(&now);
    updated = false;
    int64_t left = sw.mnEndTime - now.QuadPart;
    if (left < 0) {
      flag = 1;
      break;
    }
  }
  if (it != end)
    FUN_009aa770(&mgr->mLastUpdatedKey, 0, (char*)it + 0x10);
  return flag != 0;
}
