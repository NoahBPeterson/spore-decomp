// slice s01045200 -- SP::cStarMap visual bookkeeping (17 functions).
// Flags: /O2 /MD /Gy /TP /arch:SSE
#include "types.h"

typedef unsigned char byte;

struct Vector3 { float x, y, z; };

// ---------------------------------------------------------------------------
// vtable interfaces used by the visual effects
// ---------------------------------------------------------------------------
class VEffect {
 public:
  virtual void v00();
  virtual void Release();                     // +0x04
  virtual void SetVisible(bool);              // +0x08
  virtual void Destroy(bool);                 // +0x0c
  virtual void v10();                         // +0x10
  virtual void SetTransform(void*);           // +0x14
  virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28();
  virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c(); virtual void v40();
  virtual void SetParam(int, void*, int);     // +0x44
  virtual void v48(); virtual void v4c(); virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
  virtual int64_t GetKey();                   // +0x60
  virtual void v64(); virtual void v68(); virtual void v6c(); virtual void v70(); virtual void v74(); virtual void v78();
  virtual void v7c(); virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c(); virtual void v90();
  virtual void v94(); virtual void v98(); virtual void v9c(); virtual void vA0(); virtual void vA4(); virtual void vA8();
  virtual void vAc(); virtual void vB0(); virtual void vB4(); virtual void vB8(); virtual void vBc();
  virtual void Detach();                      // +0xc0
};

class EffectsMgr {
 public:
  virtual void t00(); virtual void t04(); virtual void t08(); virtual void t0c(); virtual void t10();
  virtual void t14(); virtual void t18(); virtual void t1c(); virtual void t20(); virtual void t24(); virtual void t28();
  virtual bool Create(uint32_t id, int a, VEffect** out);      // +0x2c
};

// serializer / reader used by ReadSTLSequenceT
class SeqStream {
 public:
  virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c(); virtual void s10(); virtual void s14();
  virtual void* Handle();                     // +0x18
};

class SeqReader {
 public:
  virtual void q00(); virtual void q04(); virtual void q08(); virtual void q0c(); virtual void q10(); virtual void q14();
  virtual void q18();
  virtual void End();                         // +0x1c
  virtual SeqStream* Stream();                // +0x20
  virtual void* ReadItem();                   // +0x28
};

// ---------------------------------------------------------------------------
// containers (eastl layouts, see src/game/include/eastl/deque.h)
// ---------------------------------------------------------------------------
class cStarRecord;

template <typename T>
struct DequeIter {
  T* mpCurrent;
  T* mpBegin;
  T* mpEnd;
  T** mpCurrentArrayPtr;
};

template <typename T>
struct Deque64 {
  T** mpPtrArray;              // +0x00
  uint32_t mnPtrArraySize;     // +0x04
  DequeIter<T> mItBegin;       // +0x08
  DequeIter<T> mItEnd;         // +0x18
  uint32_t mAllocator;         // +0x28
  uint32_t mPad2c;             // +0x2c

  void clear();                // eastl::deque<T>::clear (thiscall)
};

class cStarRecord {
 public:
  virtual void r00();          // +0x00
  virtual void Release();      // +0x04
  uint8_t mPad08[0x6c];        // +0x04 .. +0x6f
  void* mpInstance;            // +0x70
};

struct PtrVector {
  void** mpBegin;
  void** mpEnd;
  void** mpCap;
};

struct StarMapVisual {
  VEffect* mpObject;           // +0x14 in the node
  uint32_t mKey;               // +0x18
  uint32_t mGroup;             // +0x1c
  uint32_t mFlags;             // +0x20
};

struct RBNode {
  RBNode* mpLeft;
  RBNode* mpRight;
  RBNode* mpParent;
  uint32_t mColor;
  void* mpKey;                 // +0x10
  StarMapVisual mValue;        // +0x14
};

struct NodeRange {
  RBNode* mpFirst;
  RBNode* mpSecond;
};

struct RBTree {
  uint32_t mAlloc;             // +0x00
  RBNode* mpAnchorLeft;        // +0x04
  RBNode* mpAnchorRight;       // +0x08
  RBNode* mpRoot;              // +0x0c
  uint32_t mField10;           // +0x10
  uint32_t mnSize;             // +0x14
  uint32_t mPad18;             // +0x18

  void equal_range(NodeRange* out, const uint32_t* key);   // 0x00d4b450
};

struct VisualCtx;

class cStarMap {
 public:
  uint8_t mPad00[0x20];
  Deque64<cStarRecord*> mTravelTrail;   // 0x20
  float mTravelTrailLength;            // 0x50
  VEffect* mRelationshipScreenEffect;  // 0x54
  RBTree mObjectVisuals;               // 0x58
  uint32_t mVisualCount;               // 0x74

  VEffect* CreateVisual(cStarRecord* rec, int kind, int key, int group,
                        bool flagA, bool flagB);
  VEffect* CreateStarRecordVisual(cStarRecord* rec, int key, int group);
  VEffect* CreatePlanetRecordVisual(cStarRecord* rec, int key, int group,
                                    bool flagA, bool flagB);
  void RemoveVisual(VEffect* object, bool destroy);
  void RemoveVisual(uint32_t mapKey, uint32_t keyLo, uint32_t keyHi, bool destroy);
  void RemoveVisualGroup(int group, bool destroy);
  void ResetTravelTrail();
  void FilterHelperRemove(int filter);
  void FilterHelperTravelTrail(int filter);
  void FilterHelperVisited(uint32_t filter);
  void SetInitialVisuals();
  void BuildVisual(VisualCtx* ctx, void* object);
  void Init();                 // SP::cStarMap::Init
};

// ---------------------------------------------------------------------------
// external helpers (defined in other translation units)
// ---------------------------------------------------------------------------
extern const char kAllocatorFile[];                       // 0x013f09b4 "…/EASTL/allocator.h"

void*  StarManager(cStarRecord* rec);                     // 0x00b3d2a0
void   FUN_00b3d2a0(PtrVector* vec);                      // 0x00b3d2a0
int    FUN_00baf460(PtrVector* vec);                      // 0x00baf460
void*  FUN_00ba6dc0(void* mgr, cStarRecord* rec);         // 0x00ba6dc0
void*  FUN_00ba6d80(void* mgr, cStarRecord* rec);         // 0x00ba6d80
void*  cCivData_GetCities(void* civ);                     // 0x005c65e0
void*  cCivData_GetCitiesOverload(void* civ, float r, void* out); // 0x00b8de30
char   FUN_00fe3b30(void* x);                             // 0x00fe3b30
int    cSPLivingUniverse_GetUniverseContext();            // 0x01021080
void*  cStarManager_GetOrActivatePlanet(void* mgr, cStarRecord* rec); // 0x00bb59b0
void*  FUN_00b8de30(void* x);                             // 0x00b8de30
void*  BioProtectorSort_op(void* x);                      // 0x00b8de30
void   Matrix3_Assign(void* dst, const void* src);        // 0x0041cb40
void   FUN_01044f80(Deque64<cStarRecord*>* d, int a, int b);// 0x01044f80
void*  operator_new(uint32_t size, const char* name, int a, int b,
                    const char* file, int line);          // 0x00f473a0
void   operator_delete__(void* p);                        // 0x00f47380
// eastl::deque<T>::clear is a thiscall member (see Deque64::clear).
int32_t EA_IO_ReadInt32(void* stream, void* dst, int a, int b); // 0x0093a780
void   RBTreeInsert(void* node, RBNode* parent, RBNode** anchor, int side); // 0x009216a0
RBNode* RBTreeIncrement(RBNode* node);                    // 0x00921580
void   RBTreeErase(RBNode* node, RBNode** anchor);        // 0x00921880
RBNode* FUN_010450b0(void* key);                          // 0x010450b0
EffectsMgr* EffectsManagerPtr();                          // 0x0067ddd0
void*  cStarRecordRef_GetCommContext(void* ref);          // 0x00ce6950
char   FUN_01044bf0(cStarMap* self, cStarRecord* rec);    // 0x01044bf0
void*  FUN_01045120(cStarMap* self, void* key, uint32_t id); // 0x01045120
void   FUN_01043d10(void* x);                             // 0x01043d10
void*  cSPLivingUniverse_GetPlayerEmpire();               // 0x01021300
class EmpireContext {
 public:
  void* GetSelectedRecord();                              // 0x00c30c60
};

extern float gMatrixDefault;        // 0x016e0690
extern float gVisualPosX;           // 0x016e06b4
extern float gVisualPosY;           // 0x016e06b8
extern float gVisualPosZ;           // 0x016e06bc
extern const float kRealOne;        // 0x01485720
extern const float kTrailBias;      // 0x01499db0
extern const float kHalf;           // 0x01471064
extern const float kOneTenth;       // 0x01488874

// ---------------------------------------------------------------------------
// helpers
// ---------------------------------------------------------------------------
static cStarRecord** DequeAllocBlock()
{
  return (cStarRecord**)operator_new(0x100, "Simulator", 0, 0, kAllocatorFile, 0xd1);
}

static void DequeClear(Deque64<cStarRecord*>* d)
{
  d->clear();
}

static void VisualDestroy(VEffect* obj, bool a)
{
  if (obj != 0)
    obj->Destroy(a);
}

static void VisualRelease(VEffect** pobj)
{
  VEffect* obj = *pobj;
  if (obj != 0) {
    *pobj = 0;
    obj->Release();
  }
}

// ===========================================================================
// 0x01045200 -- build the render/transform block for one visual
// ===========================================================================
struct VisualCtx {
  VEffect* mpEffect;
  uint32_t mPad04;
  uint32_t mPad08;
  uint32_t mKind;
};

// @ 0x01045200
void cStarMap::BuildVisual(VisualCtx* ctx, void* object)
{
  cStarRecord* rec = (cStarRecord*)object;
  float x, y, z;

  if (ctx->mKind == 0) {
    void* mgr = StarManager(rec);
    void* civ = FUN_00ba6dc0(mgr, rec);
    if (FUN_00fe3b30(civ) != 0 &&
        cSPLivingUniverse_GetUniverseContext() == 1) {
      void* planet = cStarManager_GetOrActivatePlanet(FUN_00ba6dc0(mgr, rec), rec);
      VEffect* vis = (VEffect*)planet;
      const Vector3* p = (const Vector3*)vis;
      x = p->x; y = p->y; z = p->z;
      if (vis != 0)
        vis->Detach();
    } else {
      void* civ2 = BioProtectorSort_op(civ);
      const Vector3* p = (const Vector3*)cCivData_GetCities(civ2);
      x = p->x; y = p->y; z = p->z;
    }
  } else if (ctx->mKind == 1) {
    void* mgr = StarManager(rec);
    void* civ = FUN_00ba6d80(mgr, rec);
    const Vector3* p = (const Vector3*)cCivData_GetCities(civ);
    x = p->x; y = p->y; z = p->z;
  } else {
    x = y = z = 0.0f;
  }

  struct RenderBlock {
    uint16_t mFlags;
    int16_t  mCount;
    float    mPosX, mPosY, mPosZ;
    float    mScale;
    float    mMatrix[9];
  } block;

  block.mPosX = gVisualPosX;
  block.mPosY = gVisualPosY;
  block.mPosZ = gVisualPosZ;
  block.mCount = 0;
  block.mFlags = 0;
  block.mScale = kRealOne;
  Matrix3_Assign(&block.mMatrix[0], &gMatrixDefault);
  block.mFlags |= 4;
  block.mCount = (int16_t)(block.mCount + 1);

  if (ctx->mpEffect != 0) {
    block.mPosX = x;
    block.mPosY = y;
    block.mPosZ = z;
    ctx->mpEffect->SetTransform(&block);
  }
}

// ===========================================================================
// 0x01045370 -- grow the deque block map and append one element
// ===========================================================================
// @ 0x01045370
void FUN_01045370(Deque64<cStarRecord*>* d, cStarRecord** value)
{
  cStarRecord* v = *value;
  if ((int)(((char*)d->mItEnd.mpCurrentArrayPtr - (char*)d->mpPtrArray) >> 2) + 1
      >= (int)d->mnPtrArraySize)
    FUN_01044f80(d, 1, 1);

  cStarRecord** block = DequeAllocBlock();
  d->mItEnd.mpCurrentArrayPtr[1] = block;
  if (d->mItEnd.mpCurrent != 0)
    *d->mItEnd.mpCurrent = v;

  cStarRecord*** cur = d->mItEnd.mpCurrentArrayPtr;
  d->mItEnd.mpCurrentArrayPtr = cur + 1;
  block = cur[1];
  d->mItEnd.mpBegin = block;
  d->mItEnd.mpEnd = block + 0x40;
  d->mItEnd.mpCurrent = d->mItEnd.mpBegin;
}

// ===========================================================================
// 0x010453f0 -- ReadSTLSequenceT<eastl::deque<cStarRecord*, ...> >
// ===========================================================================
// @ 0x010453f0
void FUN_010453f0(SeqReader* reader, Deque64<cStarRecord*>* d)
{
  DequeClear(d);

  uint32_t count = 0;
  SeqStream* stream = reader->Stream();
  EA_IO_ReadInt32(stream->Handle(), &count, 1, 0);

  for (uint32_t i = 0; i < count; ++i) {
    cStarRecord* rec = (cStarRecord*)reader->ReadItem();
    if (d->mItEnd.mpCurrent + 1 == d->mItEnd.mpEnd) {
      FUN_01045370(d, &rec);
    } else {
      cStarRecord** slot = d->mItEnd.mpCurrent;
      d->mItEnd.mpCurrent = slot + 1;
      if (slot != 0)
        *slot = rec;
    }
  }
  reader->End();
}

// ===========================================================================
// 0x01045490 -- eastl::rbtree<void const*, StarMapVisual>::DoInsertValueImpl
// ===========================================================================
// @ 0x01045490
void DoInsertValueImpl(RBTree* tree, const void* key, const void* value, uint32_t force)
{
  RBNode* parent = (RBNode*)&tree->mpAnchorLeft;
  if (tree->mpRoot != 0) {
    RBNode* node = tree->mpRoot;
    do {
      parent = node;
      if ((uint32_t)key < (uint32_t)node->mpKey)
        node = node->mpRight;
      else
        node = node->mpLeft;
    } while (node != 0);
  }

  bool left = ((parent == (RBNode*)&tree->mpAnchorLeft) ||
               ((uint32_t)key < (uint32_t)parent->mpKey));

  RBNode* fresh = FUN_010450b0((void*)key);
  RBTreeInsert(fresh, parent, (RBNode**)&tree->mpAnchorLeft, left ? 0 : 1);
  tree->mnSize = tree->mnSize + 1;
  (void)value;
  (void)force;
}

// ===========================================================================
// 0x01045500 -- rebuild the map for a freshly loaded star record set
// ===========================================================================
// @ 0x01045500
void cStarMap::SetInitialVisuals()
{
  int i = 0;
  do {
    uint32_t* p = (uint32_t*)((uint8_t*)this + 4 + i * 4);
    if ((i == 0) || (i > 4 && i <= 6))
      *p = 1;
    else
      *p = 0;
    ++i;
  } while (i < 7);

  Deque64<cStarRecord*>* dq = &mTravelTrail;
  if (dq->mItBegin.mpCurrent == dq->mItEnd.mpCurrent) {
    void* empire = cSPLivingUniverse_GetPlayerEmpire();
    if (empire != 0) {
      cStarRecord* rec = (cStarRecord*)((EmpireContext*)empire)->GetSelectedRecord();
      if (rec != 0) {
        if (dq->mItEnd.mpCurrent + 1 != dq->mItEnd.mpEnd) {
          cStarRecord** slot = dq->mItEnd.mpCurrent;
          dq->mItEnd.mpCurrent = slot + 1;
          if (slot != 0)
            *slot = rec;
        } else {
          FUN_01045370(dq, &rec);
        }
      }
    }
  }
  Init();
}

// ===========================================================================
// 0x01045590 -- eastl::multimap<void const*, StarMapVisual>::erase
// ===========================================================================
// @ 0x01045590
void MultiMapErase(RBTree* tree, RBNode** out, RBNode* node)
{
  tree->mnSize = tree->mnSize - 1;
  RBNode* next = RBTreeIncrement(node);
  RBTreeErase(node, (RBNode**)&tree->mpAnchorLeft);
  VEffect* obj = node->mValue.mpObject;
  if (obj != 0)
    obj->Release();
  operator_delete__(node);
  *out = next;
}

// ===========================================================================
// 0x010455e0 -- debug/list dump helper
// ===========================================================================
class DebugWriter {
 public:
  virtual void Begin(const uint16_t* name);   // +0x00
  virtual void End(const uint16_t* name);     // +0x04
};

bool FUN_00ac8050(DebugWriter* writer, int zero, cStarRecord* rec); // 0x00ac8050

// @ 0x010455e0
byte FUN_010455e0(DebugWriter* writer, const char* label, Deque64<cStarRecord*>* dq)
{
  byte ok = 1;
  if (dq->mItBegin.mpCurrent == dq->mItEnd.mpCurrent)
    return ok;

  const uint16_t* name = (label != 0) ? (const uint16_t*)label
                                      : (const uint16_t*)L"list";
  writer->Begin(name);

  cStarRecord** it = dq->mItBegin.mpCurrent;
  cStarRecord** blockEnd = dq->mItBegin.mpEnd;
  cStarRecord*** blockPtr = dq->mItBegin.mpCurrentArrayPtr;
  cStarRecord** end = dq->mItEnd.mpCurrent;

  while (it != end) {
    if (ok)
      ok = FUN_00ac8050(writer, 0, *it) ? 1 : 0;
    else
      ok = 0;

    ++it;
    if (it == blockEnd) {
      it = blockPtr[1];
      ++blockPtr;
      blockEnd = it + 0x40;
    }
  }
  writer->End(name);
  return ok;
}

// ===========================================================================
// 0x01045740 -- SP::cStarMap::CreateVisual
// ===========================================================================
// @ 0x01045740
VEffect* cStarMap::CreateVisual(cStarRecord* rec, int kind, int key, int group,
                                bool flagA, bool flagB)
{
  uint32_t id = this->mVisualCount;
  this->mVisualCount = id + 1;

  void* commCtx = 0;
  if (rec == 0) {
    commCtx = rec ? (void*)rec->mpInstance : 0;
  } else {
    commCtx = cStarRecordRef_GetCommContext(rec);
  }

  if (rec != 0 &&
      key != 0x166521a5 && key != 0x70930c64 &&
      key != (int)0xc3f6ca28 &&
      group != 0x7c2917e7 && group != 0x41bc3bc4 &&
      FUN_01044bf0(this, rec) == 0) {
    return 0;
  }

  VisualCtx ctx;
  ctx.mpEffect = 0;
  ctx.mPad04 = 0;
  ctx.mPad08 = 0;
  ctx.mKind = kind;
  (void)commCtx;

  if (flagA) ctx.mPad04 |= 1;
  if (flagB) ctx.mPad04 |= 2;

  EffectsMgr* mgr = EffectsManagerPtr();
  VEffect* eff = 0;
  if (!mgr->Create((uint32_t)group, 0, &eff))
    return 0;

  eff->SetVisible(false);
  BuildVisual(&ctx, rec);

  // store into the map keyed by the object pointer
  RBNode node;
  node.mpKey = (void*)id;
  node.mValue.mpObject = eff;
  node.mValue.mGroup = (uint32_t)group;
  node.mValue.mFlags = 0;
  DoInsertValueImpl(&this->mObjectVisuals, (const void*)id, &node.mValue, 0);

  return eff;
}

// ===========================================================================
// 0x010458f0 -- SP::cStarMap::CreateStarRecordVisual
// ===========================================================================
// @ 0x010458f0
VEffect* cStarMap::CreateStarRecordVisual(cStarRecord* rec, int key, int group)
{
  return CreateVisual(rec, 0, key, group, false, true);
}

// ===========================================================================
// 0x01045910 -- SP::cStarMap::CreatePlanetRecordVisual
// ===========================================================================
// @ 0x01045910
VEffect* cStarMap::CreatePlanetRecordVisual(cStarRecord* rec, int key, int group,
                                            bool flagA, bool flagB)
{
  uint32_t id = this->mVisualCount;
  this->mVisualCount = id + 1;

  void* instance = (rec != 0) ? rec->mpInstance : 0;

  VisualCtx ctx;
  ctx.mpEffect = 0;
  ctx.mPad04 = 0;
  ctx.mPad08 = 0;
  ctx.mKind = 0;
  if (flagA) ctx.mPad04 |= 1;
  if (flagB) ctx.mPad04 |= 2;

  EffectsMgr* mgr = EffectsManagerPtr();
  VEffect* eff = 0;
  if (!mgr->Create((uint32_t)group, 0, &eff))
    return 0;

  eff->SetVisible(false);
  BuildVisual(&ctx, rec);
  (void)instance;

  RBNode node;
  node.mpKey = (void*)id;
  node.mValue.mpObject = eff;
  node.mValue.mGroup = (uint32_t)group;
  node.mValue.mFlags = 0;
  DoInsertValueImpl(&this->mObjectVisuals, (const void*)id, &node.mValue, 0);
  return eff;
}

// ===========================================================================
// 0x01045a60 -- SP::cStarMap::RemoveVisual (by object pointer)
// ===========================================================================
// @ 0x01045a60
void cStarMap::RemoveVisual(VEffect* object, bool destroy)
{
  RBNode* anchor = (RBNode*)&this->mObjectVisuals.mpAnchorLeft;
  RBNode* node = this->mObjectVisuals.mpAnchorRight;
  while (node != anchor) {
    if (object == node->mValue.mpObject) {
      VisualDestroy(node->mValue.mpObject, destroy);
      this->mObjectVisuals.mnSize = this->mObjectVisuals.mnSize - 1;
      RBNode* next = RBTreeIncrement(node);
      RBTreeErase(node, (RBNode**)&this->mObjectVisuals.mpAnchorLeft);
      if (node->mValue.mpObject != 0)
        node->mValue.mpObject->Release();
      operator_delete__(node);
      node = next;
    } else {
      node = RBTreeIncrement(node);
    }
  }
}

// ===========================================================================
// 0x01045ae0 -- SP::cStarMap::RemoveVisual (by 64-bit key)
// ===========================================================================
// @ 0x01045ae0
void cStarMap::RemoveVisual(uint32_t mapKey, uint32_t keyLo, uint32_t keyHi,
                            bool destroy)
{
  NodeRange range;
  this->mObjectVisuals.equal_range(&range, &mapKey);
  RBNode* node = range.mpFirst;
  while (node != range.mpSecond) {
    if (node->mValue.mpObject == 0) {
      // fall through to erase
    } else {
      int64_t k = node->mValue.mpObject->GetKey();
      int64_t want = ((int64_t)keyHi << 32) | keyLo;
      if (k != want) {
        node = RBTreeIncrement(node);
        continue;
      }
      node->mValue.mpObject->Destroy(destroy);
    }
    this->mObjectVisuals.mnSize = this->mObjectVisuals.mnSize - 1;
    RBNode* next = RBTreeIncrement(node);
    RBTreeErase(node, (RBNode**)&this->mObjectVisuals.mpAnchorLeft);
    if (node->mValue.mpObject != 0)
      node->mValue.mpObject->Release();
    operator_delete__(node);
    node = next;
  }
}

// ===========================================================================
// 0x01045b90 -- SP::cStarMap::RemoveVisualGroup
// ===========================================================================
// @ 0x01045b90
void cStarMap::RemoveVisualGroup(int group, bool destroy)
{
  RBNode* node = this->mObjectVisuals.mpAnchorRight;
  while (node != (RBNode*)&this->mObjectVisuals.mpAnchorLeft) {
    if ((uint32_t)group == node->mValue.mGroup) {
      VEffect* obj = node->mValue.mpObject;
      if (obj != 0)
        obj->Destroy(destroy);
      this->mObjectVisuals.mnSize = this->mObjectVisuals.mnSize - 1;
      RBNode* next = RBTreeIncrement(node);
      RBTreeErase(node, (RBNode**)&this->mObjectVisuals.mpAnchorLeft);
      if (node->mValue.mpObject != 0)
        node->mValue.mpObject->Release();
      operator_delete__(node);
      node = next;
    } else {
      node = RBTreeIncrement(node);
    }
  }
}

// ===========================================================================
// 0x01045c10 -- SP::cStarMap::ResetTravelTrail
// ===========================================================================
// @ 0x01045c10
void cStarMap::ResetTravelTrail()
{
  RemoveVisualGroup(4, false);
  DequeClear(&this->mTravelTrail);
}

// ===========================================================================
// 0x01045c30 -- SP::cStarMap::FilterHelperRemove
// ===========================================================================
// @ 0x01045c30
void cStarMap::FilterHelperRemove(int filter)
{
  RemoveVisualGroup(filter, false);
  if (filter != 0 && filter != 1 && filter == 2 &&
      this->mRelationshipScreenEffect != 0) {
    VEffect* eff = this->mRelationshipScreenEffect;
    eff->Destroy(false);
    eff = this->mRelationshipScreenEffect;
    if (eff != 0) {
      this->mRelationshipScreenEffect = 0;
      eff->Release();
    }
  }
}

// ===========================================================================
// 0x01045c80 -- SP::cStarMap::FilterHelperTravelTrail
// ===========================================================================
// @ 0x01045c80
void cStarMap::FilterHelperTravelTrail(int filter)
{
  Deque64<cStarRecord*>& q = this->mTravelTrail;
  uint32_t count = (uint32_t)(((q.mItEnd.mpCurrentArrayPtr - q.mItBegin.mpCurrentArrayPtr) >> 2) - 1) * 0x40
                 + (uint32_t)((q.mItEnd.mpCurrent - q.mItEnd.mpBegin) >> 2)
                 + (uint32_t)((q.mItBegin.mpEnd - q.mItBegin.mpCurrent) >> 2);
  if (count <= 1)
    return;

  cStarRecord** it = q.mItEnd.mpCurrent;
  cStarRecord** beginBlock = q.mItEnd.mpBegin;
  cStarRecord** endBlock = q.mItEnd.mpEnd;
  cStarRecord*** blockPtr = q.mItEnd.mpCurrentArrayPtr;
  cStarRecord* prev = 0;
  int index = 0;

  while (it != q.mItBegin.mpCurrent) {
    cStarRecord** cur = it;
    if (it == beginBlock) {
      cur = blockPtr[-1] + 0x40;
    }
    cStarRecord* rec = cur[-1];
    if (it == beginBlock) {
      beginBlock = blockPtr[-1];
      blockPtr = blockPtr - 1;
      it = beginBlock + 0x40;
      endBlock = it;
    }
    it = it - 1;
    if (it == q.mItBegin.mpCurrent)
      break;

    cur = it;
    if (it == beginBlock)
      cur = blockPtr[-1] + 0x40;
    cStarRecord* next = cur[-1];
    if (rec != next) {
      uint32_t id = this->mVisualCount;
      this->mVisualCount = id + 1;

      VEffect* eff = 0;
      if (filter == 0x166521a5 || filter == 0x70930c64 ||
          filter == (int)0xc3f6ca28 || FUN_01044bf0(this, rec) != 0) {
        EffectsMgr* mgr = EffectsManagerPtr();
        if (mgr->Create(0x3ab4709, 0, &eff)) {
          eff->SetVisible(false);
          VisualCtx ctx;
          ctx.mpEffect = 0;
          ctx.mPad04 = 0;
          ctx.mPad08 = 0;
          ctx.mKind = 0;
          BuildVisual(&ctx, rec);

          RBNode node;
          node.mpKey = (void*)id;
          node.mValue.mpObject = eff;
          node.mValue.mGroup = 0;
          node.mValue.mFlags = 0;
          DoInsertValueImpl(&this->mObjectVisuals, (const void*)id, &node.mValue, 0);

          if (id != 0) {
            VEffect* obj = (VEffect*)FUN_01045120(this, rec->mpInstance, id);
            if (obj != 0) {
              float f = ((float)index / this->mTravelTrailLength) * -0.45f + 0.5f;
              obj->SetParam(4, &f, 1);
              void* cities = 0;
              cCivData_GetCitiesOverload((void*)rec, 0.1f, &cities);
              FUN_01043d10(cities);
              obj->SetParam(0xd, cities, 0);
            }
          }
        }
      }
      ++index;
    }
  }
}

// ===========================================================================
// 0x01045f90 -- SP::cStarMap::FilterHelperVisited
// ===========================================================================
// @ 0x01045f90
void cStarMap::FilterHelperVisited(uint32_t filter)
{
  PtrVector visited;
  visited.mpBegin = 0;
  visited.mpEnd = 0;
  visited.mpCap = 0;

  FUN_00b3d2a0(&visited);
  if (FUN_00baf460(&visited) != 0) {
    for (void** p = visited.mpBegin; p != visited.mpEnd; ++p) {
      cStarRecord* rec = (cStarRecord*)*p;
      uint32_t id = this->mVisualCount;
      this->mVisualCount = id + 1;
      void* instance = rec->mpInstance;

      VEffect* eff = 0;
      if (filter == 0x166521a5 || filter == 0x70930c64 ||
          filter == (uint32_t)0xc3f6ca28 || FUN_01044bf0(this, rec) != 0) {
        EffectsMgr* mgr = EffectsManagerPtr();
        if (eff != 0) {
          eff->Release();
          eff = 0;
        }
        if (mgr->Create(0xbfdea3f7, 0, &eff)) {
          eff->SetVisible(false);
          VisualCtx ctx;
          ctx.mpEffect = eff;
          ctx.mPad04 = 0;
          ctx.mPad08 = 0;
          ctx.mKind = 0;
          BuildVisual(&ctx, instance);

          RBNode node;
          node.mpKey = instance;
          node.mValue.mpObject = eff;
          node.mValue.mGroup = filter;
          node.mValue.mFlags = 0;
          if (eff != 0)
            eff->v00();                 // AddRef before publishing
          DoInsertValueImpl(&this->mObjectVisuals, instance, &node.mValue, 0);
          if (eff != 0)
            eff->Release();
        }
      }
      if (eff != 0)
        eff->Release();
    }
  }

  for (void** p = visited.mpBegin; p != visited.mpEnd; ++p) {
    cStarRecord* rec = (cStarRecord*)*p;
    if (rec != 0)
      rec->Release();
  }
  if (visited.mpBegin != 0 && ((uint32_t*)visited.mpBegin)[-1] != 0)
    operator_delete__(visited.mpBegin);
}
