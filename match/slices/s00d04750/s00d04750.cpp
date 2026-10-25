// Decompiled slice s00d04750 -- SP UI-layout / relationship objects.
// Reconstructed from the shipped binary; helper addresses noted per call.
#include "types.h"

void operator_delete_array(void* p);                     // 0x00f47380

// ---------------------------------------------------------------------------
// shared shapes
// ---------------------------------------------------------------------------
struct Sub04 {
  uint8_t mData[0x0c];                                   // +0x04 .. +0x0f
  void FUN_00d03b10(void* arg);                          // 0x00d03b10 (ecx=this, stack arg)
  void FUN_00d048a0(void* src);                          // 0x00d048a0 (ecx=this, stack arg)
  void FUN_00d049d0(void* src);                          // 0x00d049d0 (ecx=this, stack arg)
};

struct Elem20 {                                          // 0x20-byte vector element
  int      mKey;        // +0x00
  Sub04    mSub;        // +0x04
  void*    mField10;    // +0x10
  uint8_t  mTail[0x0c]; // +0x14 .. +0x1f
};

struct Pair { uint32_t mKey; };                          // key/value pair passed to vec ops

Elem20* FUN_00d04f90(void* a, Elem20* end, void* b);      // 0x00d04f90 (cdecl)
Elem20* FUN_00d01210(Elem20* begin, Elem20* end, Pair* key, uint8_t flag); // 0x00d01210 (cdecl)
Elem20* FUN_00d04cd0(Elem20* begin, Elem20* end, Elem20* dst);        // 0x00d04cd0 (cdecl)
Elem20* FUN_00d041d0(Elem20* begin, Elem20* end, Elem20* dst);        // 0x00d041d0 (cdecl)
Elem20* FUN_00d04fd0(Elem20* begin, Elem20* end, Elem20* dst);        // 0x00d04fd0 (cdecl)

struct Vec20 {
  Elem20*  mpBegin;     // +0x00
  Elem20*  mpEnd;       // +0x04
  Elem20*  mpCap;       // +0x08
  uint32_t mField0c;    // +0x0c
  uint32_t mField10;    // +0x10
  uint8_t  mField14;    // +0x14

  int   FUN_00d051e0(void* a1, void* a2);                // 0x00d051e0
  void  FUN_00d05140(uint32_t n);                        // 0x00d05140
  void  FUN_00d05240(Elem20* pos, Pair* value);          // 0x00d05240
  Elem20* FUN_00d05380(Elem20* pos, Pair* value);        // 0x00d05380
  int   FUN_00d05560(Pair* key);                         // 0x00d05560
  void* FUN_00d055d0(Pair* key);                         // 0x00d055d0 (returns the element's tree)
};

// ---------------------------------------------------------------------------
// world-map rbtree (eastl), shared by cSPUILayoutManager and its vectors
// ---------------------------------------------------------------------------
struct WorldNodeBase {
  WorldNodeBase* mpRight;    // node +0x00
  WorldNodeBase* mpLeft;     // node +0x04
  WorldNodeBase* mpParent;   // node +0x08  (root when this is the anchor)
  uint8_t        mColor;     // node +0x0c
  uint8_t        mPad0d[3];
};

struct Key8 {                                           // node +0x10
  uint32_t mFirst;                                      // node +0x10
  uint32_t mSecond;                                     // node +0x14
};

struct RTree {                                          // 0x18 bytes
  uint32_t      mPad;                                   // +0x00
  WorldNodeBase mAnchor;                                // +0x04  {right,left,root,color}
  uint32_t      mnSize;                                 // +0x14

  void DoNukeSubtreeWorld(WorldNodeBase* n);            // 0x00d03b10
  void DoNukeSubtreeSub(void* n);                       // 0x009a9600
};

struct WorldNode;

struct cWorld {                                         // node +0x18, 0x20 bytes
  float   mFloat;                                       // +0x00
  uint32_t mField;                                      // +0x04
  RTree   mTree;                                        // +0x08  nested map
};

struct WorldNode {                                      // 0x3c bytes
  WorldNodeBase mBase;                                  // +0x00
  Key8          mKey;                                   // +0x10
  cWorld        mWorld;                                 // +0x18
  uint8_t       mPad38[4];
};

struct WorldTree {                                      // 0x18 bytes
  uint32_t      mPad;                                   // +0x00
  WorldNodeBase mAnchor;                                // +0x04
  uint32_t      mnSize;                                 // +0x14

  void      reset();
  WorldNode* findOrInsert(const Key8* key);             // 0x00d04e90
  void      DoNukeSubtree(WorldNodeBase* n);            // 0x00d03b10
};

// a vector element seen as {key, nested world tree}
struct ElemTree {                                       // 0x1c bytes (stride 0x20)
  uint32_t mKey;                                        // +0x00
  WorldTree mTree;                                      // +0x04
};

// helpers on the world tree --------------------------------------------------
struct WorldValue {                                     // insert-source temp, 0x28
  Key8  mKey;                                           // +0x00
  cWorld mWorld;                                        // +0x08
};

// ecx-based helpers: the first parameter is the incoming ecx value, the
// explicit `scratch` occupies edx (unused by the callee), further parameters
// are pushed right-to-left exactly like the shipped thiscall functions.
void __fastcall      FUN_00d03b10(WorldTree* self, uint32_t scratch, WorldNodeBase* node); // 0x00d03b10
void __fastcall      FUN_009a9600(WorldTree* self, uint32_t scratch, WorldNodeBase* node); // 0x009a9600
WorldNode* __fastcall FUN_00d03e90(WorldTree* self, uint32_t scratch, const WorldValue* v); // 0x00d03e90
void __fastcall      FUN_00d03ef0(WorldTree* self, uint32_t scratch, void** out,
                       WorldNode* hint, const WorldValue* v, uint32_t flag);  // 0x00d03ef0
void __fastcall      FUN_00d040a0(WorldTree* self, uint32_t scratch, void** out,
                       const WorldValue* v, uint32_t flag);                   // 0x00d040a0
WorldNodeBase* RBTreeIncrement(WorldNodeBase* n);       // 0x00921580 (cdecl)
void RBTreeInsert(WorldNode* n, WorldNodeBase* parent, WorldNodeBase* anchor,
                  int insertRight);                     // 0x009216a0 (cdecl)
void __fastcall FUN_00d01a40(RTree* dst, uint32_t scratch, const RTree* src);  // copy-ctor
void __fastcall FUN_00d02250(RTree* dst, uint32_t scratch, const RTree* src);  // assign
void __fastcall FUN_00d049d0(RTree* dst, uint32_t scratch, const RTree* src);  // assign
WorldTree* __fastcall FUN_00d01ab0(void* self, uint32_t scratch, uint32_t a, uint32_t b); // 0x00d01ab0
cWorld* __fastcall   FUN_00d01410(void* self, uint32_t scratch, WorldTree* tree,
                       uint32_t a, uint32_t b);                            // 0x00d01410
void __fastcall FUN_00d056c0(void* self, uint32_t scratch, void* src); // 0x00d056c0
cWorld* __fastcall FUN_00d05730(void* self, uint32_t scratch, WorldTree* tree,
                                uint32_t a, uint32_t b); // 0x00d05730
void __fastcall FUN_00d05830(void* self, uint32_t scratch, uint32_t a, uint32_t b); // 0x00d05830

// ---------------------------------------------------------------------------
// cSPUILayoutManager
// ---------------------------------------------------------------------------
struct StreamVtbl;
struct StreamObj { StreamVtbl* mpVtbl; };
struct MgrVtbl;

typedef void* (__fastcall *MgrSlot20)(void* self);
typedef void  (__fastcall *MgrSlot1C)(void* self);
typedef void* (__fastcall *StreamSlot18)(void* self);

struct StreamVtbl {
  void* v00; void* v04; void* v08; void* v0c; void* v10; void* v14;
  StreamSlot18 v18;
};

struct MgrVtbl {
  void* v00; void* v04; void* v08; void* v0c; void* v10; void* v14;
  void* v18;
  MgrSlot1C v1c;
  MgrSlot20 v20;
};

struct cSPUILayoutManager {
  MgrVtbl*  mpVtbl;          // +0x00
  void*     mpVt04;          // +0x04
  void*     mpVt08;          // +0x08
  void*     mpVt0C;          // +0x0c
  float     mF10;            // +0x10
  float     mF14;            // +0x14
  float     mF18;            // +0x18
  float     mF1C;            // +0x1c
  uint8_t   mFlag20;         // +0x20
  uint8_t   mPad21[3];       // +0x21
  WorldTree mWorlds;         // +0x24
  uint8_t   mPad3C[4];       // +0x3c
  void*     mpCurrent;       // +0x40
  void*     mp44;            // +0x44
  uint32_t* mpBits48;        // +0x48
  uint32_t* mpBits4C;        // +0x4c
  uint32_t* mpBits50;        // +0x50
  uint8_t   mPad54[0x0c];    // +0x54
  uint32_t* mpBits60;        // +0x60
  uint32_t* mpBits64;        // +0x64
  void*     mp68;            // +0x68
  uint8_t   mPad6C[0x0c];    // +0x6c
  void*     mp78;            // +0x78
  uint8_t   mPad7C[4];       // +0x7c
  void*     mp80;            // +0x80
  void*     mp84;            // +0x84
  int       mHandler;        // +0x88
  void*     mpHandlerArg0;   // +0x8c
  void*     mpHandlerArg1;   // +0x90
  void*     mpHandlerArg2;   // +0x94
  void*     mpHandlerArg3;   // +0x98
  Vec20     mEmbassies;      // +0x9c  (its mField14 doubles as the +0xb0 flag)
  void*     mpVecB4;         // +0xb4
  void*     mpVecB8;         // +0xb8
  void*     mpVecBC;         // +0xbc
  uint8_t   mPadC0[0x0c];    // +0xc0
  void*     mpVecCC;         // +0xcc
  void*     mpVecD0;         // +0xd0
  void*     mpVecD4;         // +0xd4
  uint8_t   mPadD8[0x0c];    // +0xd8
  RTree     mClassTree;      // +0xe4

  StreamObj* stream() { return (StreamObj*)mpVtbl->v20(this); }   // 0x20 -> 0x18
  void  endScope()    { mpVtbl->v1c(this); }                      // vtable 0x1c
};

// ---------------------------------------------------------------------------
// leaf helpers
// ---------------------------------------------------------------------------
struct MsgVtbl {
  void* v00; void* v04; void* v08; void* v0c; void* v10; void* v14;
  void* v18; void* v1c; void* v20; void* v24; void* v28; void* v2c;
  void* v30; void* v34; void* v38; void* v3c; void* v40; void* v44;
  void* v48;
  uint32_t (__fastcall *v4c)(void* self);
};
struct MsgObject { MsgVtbl* mpVtbl; };
struct MsgPayload {
  uint32_t   m0;             // +0x00
  uint32_t   m4;             // +0x04
  MsgObject* mpObject;       // +0x08
  uint32_t   m0c;            // +0x0c
  uint32_t   mId;            // +0x10
};
struct cRelationshipManager;

char __fastcall FUN_00d04910(uint8_t* self, uint32_t scratch, uint32_t msg,
                             MsgPayload* p);               // 0x00d04910
void __fastcall FUN_00d04290(cRelationshipManager* m, uint32_t scratch, uint32_t id); // 0x00d04290
void __fastcall FUN_00d03c40(cRelationshipManager* m, uint32_t scratch);  // 0x00d03c40
void FUN_00b3d2a0(void);                                                  // 0x00b3d2a0
char FUN_00ba6650(uint32_t id);                                           // 0x00ba6650
void FUN_00d04aa0(cSPUILayoutManager* self, WorldTree* tree);             // 0x00d04aa0 (cdecl)
void __fastcall FUN_00d04d10(cSPUILayoutManager* self);                   // 0x00d04d10
cSPUILayoutManager* __fastcall FUN_00d05010(cSPUILayoutManager* self);    // 0x00d05010
void __fastcall FUN_00d053e0(cSPUILayoutManager* self);                   // 0x00d053e0

void* FUN_00f473a0(uint32_t size, const char* name, int a, int b,
                   const char* file, int line);          // 0x00f473a0 operator_new
uint32_t* __fastcall FUN_00f41aa0(void* map, uint32_t scratch, uint32_t* key); // 0x00f41aa0
void  RemoveHandler(int h, void* a, void* b, void* c, void* d); // 0x00571db0
void  FUN_0011e0744(void* begin, void* end, int val);    // 0x0011e0744
void __fastcall FUN_00d018d0(void* self, uint32_t scratch, void* begin, void* end); // 0x00d018d0
void __fastcall FUN_00530c80(void* self, uint32_t scratch, void* begin, void* end); // 0x00530c80
void __fastcall FUN_00d0c930(RTree* self, uint32_t scratch, WorldNodeBase* root);   // 0x00d0c930
void* FUN_010212a0(void);                                // 0x010212a0 GetActivePlanetRecord
uint32_t __fastcall FUN_00ce6950(void* planetRecord, uint32_t scratch); // 0x00ce6950 embassy id
void  FUN_00d009a0(uint32_t* a, uint32_t* b);            // 0x00d009a0
// stream read / var-list serializer
void  FUN_0093a780(void* reader, uint32_t* dst, int count, int zero); // 0x0093a780
void __fastcall FUN_00692f90(void* ser, uint32_t scratch, cWorld* value, void* globals, int tag); // 0x00692f90
void __fastcall FUN_00693e10(void* ser, uint32_t scratch, void* obj);           // 0x00693e10

// global class tree and bit vector (see 0x01581f30 / 0x0169d410)
RTree* const     gpClassTree    = (RTree*)0x01581f30;
uint32_t* const  gpBitVecBegin  = (uint32_t*)0x0169d410;
uint32_t* const  gpBitVecEnd    = (uint32_t*)0x0169d414;
void* const      kpVarList      = (void*)0x01582008;

// ---------------------------------------------------------------------------
// @ 0x00d04e60
// AddRef: increments the intrusive reference count stored immediately before
// the object pointer (the object base sits 4 bytes past the count).
struct RefCountHeader { int mCount; };                   // mCount at -4 from the object

int __fastcall AddRef(RefCountHeader* p)
{
  int n = (p - 1)->mCount;
  ++n;
  (p - 1)->mCount = n;
  return n;
}

// @ 0x00d04a60
// Destroys a vector of 0x20-byte elements (destroying each element's +0x04
// sub-object) and frees the backing array.
void __fastcall FUN_00d04a60(Vec20* v)
{
  Elem20* end = v->mpEnd;
  for (Elem20* p = v->mpBegin; p < end; ++p)
    p->mSub.FUN_00d03b10(p->mField10);
  if (v->mpBegin)
    operator_delete_array(v->mpBegin);
}

// @ 0x00d051e0
// Destroys every element from the position returned by FUN_00d04f90 up to the
// vector end and shrinks the end pointer by the erased range.
int Vec20::FUN_00d051e0(void* a1, void* a2)
{
  Elem20* e = FUN_00d04f90(a2, mpEnd, a1);
  if (e < mpEnd) {
    unsigned n = (((unsigned)((char*)mpEnd - (char*)e)) - 1 >> 5) + 1;
    Elem20* p = e;
    do {
      p->mSub.FUN_00d03b10(p->mField10);
      ++p;
    } while (--n);
  }
  int d = (int)a2 - (int)a1;
  d >>= 5;
  d = -d;
  d <<= 5;
  mpEnd = (Elem20*)((char*)mpEnd + d);
  return (int)a1;
}

// @ 0x00d05380
// Inserts value before pos, appending in place when pos is the end and the
// capacity allows; otherwise forwards to FUN_00d05240.
Elem20* Vec20::FUN_00d05380(Elem20* pos, Pair* value)
{
  Elem20* end = mpEnd;
  int idx = (int)((char*)pos - (char*)mpBegin) >> 5;
  if (pos == end && end != mpCap) {
    mpEnd = end + 1;
    if (end != 0) {
      end->mKey = value->mKey;
      end->mSub.FUN_00d048a0(value + 1);
      return mpBegin + idx;
    }
  } else {
    FUN_00d05240(pos, value);
  }
  return mpBegin + idx;
}

// @ 0x00d05560
// Erases the element matching key (found through FUN_00d01210) and destroys it.
int Vec20::FUN_00d05560(Pair* key)
{
  Elem20* end = mpEnd;
  Elem20* p = FUN_00d01210(mpBegin, end, key, mField14);
  if (p == end || key->mKey < p->mKey || p == p + 1)
    p = end;
  if (p != end) {
    if (p + 1 < end)
      FUN_00d04f90(p + 1, end, p);
    mpEnd = mpEnd - 1;
    Elem20* q = mpEnd;
    q->mSub.FUN_00d03b10(q->mField10);
    return 1;
  }
  return 0;
}
// ---------------------------------------------------------------------------
// world-tree helpers
// ---------------------------------------------------------------------------
WorldNode* __fastcall FUN_00d04750(WorldTree* self, uint32_t scratch,
                                   void** out, WorldNode* pos,
                                   const WorldValue* value, uint32_t flag);

static const float kFloatMax = 3.402823466e+38F;   // 0x7f7fffff
static const char* const kAllocFile =
  "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";

static bool key_lt(const Key8& a, const Key8& b)
{
  return a.mFirst < b.mFirst || (a.mFirst == b.mFirst && a.mSecond < b.mSecond);
}

static void wt_reset(WorldTree* t)
{
  WorldNodeBase* a = &t->mAnchor;
  a->mpRight  = a;
  a->mpLeft   = a;
  a->mpParent = 0;
  a->mColor   = 0;
  t->mnSize   = 0;
}

static void wt_clear_outer(WorldTree* t)
{
  FUN_00d03b10(t, 0, t->mAnchor.mpParent);
  wt_reset(t);
}

static void wt_clear_nested(WorldTree* t)
{
  FUN_009a9600(t, 0, t->mAnchor.mpParent);
  wt_reset(t);
}

// The shipped clear helper rounds the element count down to whole dwords and
// leaves the residual bytes on the end pointer.
static uint32_t* trim_word_end(uint32_t* begin, uint32_t* end)
{
  int32_t bytes = (int32_t)((uint8_t*)end - (uint8_t*)begin);
  return (uint32_t*)((uint8_t*)end - ((bytes >> 2) << 2));
}

// lower_bound over the world map, returns the anchor when no such key
static WorldNodeBase* lb_node(WorldTree* t, const Key8* key)
{
  WorldNodeBase* n = t->mAnchor.mpParent;
  WorldNodeBase* best = &t->mAnchor;
  while (n) {
    WorldNode* w = (WorldNode*)n;
    if (!key_lt(w->mKey, *key)) {
      best = n;
      n = n->mpLeft;
    } else {
      n = n->mpRight;
    }
  }
  return best;
}

// ---------------------------------------------------------------------------
// @ 0x00d04750
// Tree insert with a position hint: append past the rightmost node, insert
// between two neighbours when the hint allows it, otherwise fall back to the
// plain "insert unique" helper.
// ---------------------------------------------------------------------------
WorldNode* __fastcall FUN_00d04750(WorldTree* self, uint32_t scratch,
                                   void** out, WorldNode* pos,
                                   const WorldValue* value, uint32_t flag)
{
  WorldNodeBase* rightmost = self->mAnchor.mpRight;
  WorldNodeBase* anchor = &self->mAnchor;

  if (pos == (WorldNode*)rightmost || pos == (WorldNode*)anchor) {
    if (self->mnSize != 0) {
      const Key8& rk = ((WorldNode*)rightmost)->mKey;
      if (key_lt(rk, value->mKey)) {
        uint32_t right;
        if (pos == (WorldNode*)anchor || key_lt(value->mKey, rk))
          right = 0;
        else
          right = 1;
        WorldNode* n = FUN_00d03e90(self, 0, value);
        RBTreeInsert(n, rightmost, anchor, (int)right);
        ++self->mnSize;
        *out = n;
        return (WorldNode*)out;
      }
    }
  } else {
    WorldNode* next = (WorldNode*)RBTreeIncrement((WorldNodeBase*)pos);
    if (key_lt(pos->mKey, value->mKey) && key_lt(value->mKey, next->mKey)) {
      if (pos->mBase.mpRight != 0) {
        WorldNode* n = FUN_00d03e90(self, 0, value);
        RBTreeInsert(n, (WorldNodeBase*)next, anchor, 0);
        ++self->mnSize;
        *out = n;
        return (WorldNode*)out;
      }
      FUN_00d03ef0(self, 0, out, pos, value, 0);
      return (WorldNode*)out;
    }
  }
  void* where = 0;
  FUN_00d040a0(self, 0, &where, value, (uint32_t)value & 0xffffff00u);
  *out = where;
  return (WorldNode*)out;
}

// ---------------------------------------------------------------------------
// @ 0x00d04910
// SP::cRelationshipManager::HandleMessage: dispatch the four simulator
// relationship messages, forwarding the sender id to the manager.
// ---------------------------------------------------------------------------
char __fastcall FUN_00d04910(uint8_t* self, uint32_t scratch, uint32_t msg,
                             MsgPayload* p)
{
  cRelationshipManager* mgr = (cRelationshipManager*)(self - 8);

  if (msg == 0x4b33710) {
    MsgObject* o = p->mpObject;
    FUN_00b3d2a0();
    uint32_t id = o->mpVtbl->v4c(o);
    if (!FUN_00ba6650(id)) {
      id = o->mpVtbl->v4c(o);
      FUN_00d04290(mgr, 0, id);
    }
    return 1;
  }
  if (msg == 0xf62def) {
    if (p->mId != 0x568de14)
      return 1;
    FUN_00d03c40(mgr, 0);
    return 1;
  }
  if (msg == 0x4b3370f) {
    MsgObject* o = p->mpObject;
    FUN_00d04290(mgr, 0, o->mpVtbl->v4c(o));
    return 1;
  }
  if (msg == 0x4b33711) {
    FUN_00d04290(mgr, 0, *(uint32_t*)((uint8_t*)p->mpObject + 0x84));
    return 1;
  }
  return 0;
}

// ---------------------------------------------------------------------------
// @ 0x00d04aa0
// Deserialize a world map: read the entry count, then per entry the key and
// the cWorld payload (through cVarListSerializer), inserting each entry.
// ---------------------------------------------------------------------------
void FUN_00d04aa0(cSPUILayoutManager* self, WorldTree* tree)
{
  wt_clear_outer(tree);

  int32_t count = 0;
  StreamObj* s = self->stream();
  void* reader = s->mpVtbl->v18(s);
  FUN_0093a780(reader, (uint32_t*)&count, 1, 0);

  for (int32_t i = 0; i < count; ++i) {
    WorldValue v;
    v.mKey.mFirst = 0;
    v.mKey.mSecond = 0;
    v.mWorld.mFloat = kFloatMax;
    v.mWorld.mField = 0;
    wt_reset((WorldTree*)&v.mWorld.mTree);

    s = self->stream();
    reader = s->mpVtbl->v18(s);
    FUN_0093a780(reader, &v.mKey.mFirst, 1, 0);

    s = self->stream();
    reader = s->mpVtbl->v18(s);
    FUN_0093a780(reader, &v.mKey.mSecond, 1, 0);

    self->endScope();
    uint8_t ser[0x40];
    FUN_00692f90(ser, 0, &v.mWorld, kpVarList, 0x1a80d26);
    FUN_00693e10(ser, 0, self);
    self->endScope();

    WorldValue copy;
    copy.mKey = v.mKey;
    copy.mWorld.mFloat = v.mWorld.mFloat;
    copy.mWorld.mField = v.mWorld.mField;
    FUN_00d01a40(&copy.mWorld.mTree, 0, &v.mWorld.mTree);

    void* where = 0;
    FUN_00d040a0(tree, 0, &where, &copy, 0);
    wt_clear_nested((WorldTree*)&copy.mWorld.mTree);
    wt_clear_nested((WorldTree*)&v.mWorld.mTree);
  }
  self->endScope();
}

// ---------------------------------------------------------------------------
// @ 0x00d04d10
// cSPUILayoutManager destructor: clear the embedded maps, free the vectors,
// unregister the message handler, then install the base-class vtables.
// ---------------------------------------------------------------------------
void __fastcall FUN_00d04d10(cSPUILayoutManager* self)
{
  self->mpVtbl = (MgrVtbl*)0x1478e4c;
  self->mpVt08 = (void*)0x1478e3c;
  self->mpVt0C = (void*)0x1478e18;

  wt_clear_outer(&self->mWorlds);
  FUN_009a9600((WorldTree*)&self->mClassTree, 0,
               self->mClassTree.mAnchor.mpParent);

  if (self->mpVecCC)
    operator_delete_array(self->mpVecCC);
  if (self->mpVecB4)
    operator_delete_array(self->mpVecB4);
  FUN_00d04a60(&self->mEmbassies);

  int h = self->mHandler;
  if (h != 0) {
    self->mHandler = 0;
    RemoveHandler(h, self->mpHandlerArg0, self->mpHandlerArg1,
                  self->mpHandlerArg2, self->mpHandlerArg3);
  }
  if (self->mpBits60)
    operator_delete_array(self->mpBits60);
  if (self->mpBits48)
    operator_delete_array(self->mpBits48);

  FUN_00d03b10(&self->mWorlds, 0, self->mWorlds.mAnchor.mpParent);

  self->mpVt0C = (void*)0x13eb938;
  self->mpVt08 = (void*)0x13eb394;
  self->mpVtbl = (MgrVtbl*)0x13ef094;
}

// ---------------------------------------------------------------------------
// @ 0x00d04e90
// Find the cWorld for a key, inserting a default (FLT_MAX) entry when the key
// is not present.  Returns the cWorld inside the node.
// ---------------------------------------------------------------------------
cWorld* __fastcall FUN_00d04e90(WorldTree* self, uint32_t scratch,
                                const Key8* key)
{
  WorldNode* n = (WorldNode*)lb_node(self, key);
  if (n != (WorldNode*)&self->mAnchor && !key_lt(*key, n->mKey))
    return &n->mWorld;

  WorldTree empty;
  wt_reset(&empty);

  WorldValue v;
  v.mKey = *key;
  v.mWorld.mFloat = kFloatMax;
  v.mWorld.mField = 0;
  FUN_00d01a40((RTree*)&v.mWorld.mTree, 0, (const RTree*)&empty);

  void* where = 0;
  FUN_00d04750(self, 0, &where, n, &v, (uint32_t)n & 0xffffff00u);
  wt_clear_nested((WorldTree*)&v.mWorld.mTree);
  wt_clear_nested(&empty);
  return &((WorldNode*)where)->mWorld;
}

// ---------------------------------------------------------------------------
// @ 0x00d05010
// cSPUILayoutManager constructor: install the vtables and zero every embedded
// container / scalar, initialising the two map anchors.
// ---------------------------------------------------------------------------
cSPUILayoutManager* __fastcall FUN_00d05010(cSPUILayoutManager* self)
{
  self->mpVt04 = 0;
  self->mpVt08 = (void*)0x13eb384;
  self->mpVt0C = (void*)0x1444434;
  self->mpVtbl = (MgrVtbl*)0x1478e4c;
  self->mpVt08 = (void*)0x1478e3c;
  self->mpVt0C = (void*)0x1478e18;

  self->mFlag20 = 0;
  self->mF10 = 0.0f;
  self->mF14 = 0.0f;
  self->mF18 = 0.0f;
  self->mF1C = 0.0f;

  wt_reset(&self->mWorlds);
  self->mWorlds.mAnchor.mColor = 0;
  self->mWorlds.mAnchor.mPad0d[0] = 0;
  self->mWorlds.mAnchor.mPad0d[1] = 0;
  self->mWorlds.mAnchor.mPad0d[2] = 0;
  self->mpCurrent = 0;
  self->mp44 = 0;
  self->mpBits48 = 0;
  self->mpBits4C = 0;
  self->mpBits50 = 0;
  self->mpBits60 = 0;
  self->mpBits64 = 0;
  self->mp68 = 0;
  self->mp78 = 0;
  self->mp80 = 0;
  self->mp84 = 0;
  self->mHandler = 0;
  self->mpHandlerArg0 = 0;
  self->mpHandlerArg1 = 0;
  self->mpHandlerArg2 = 0;
  self->mpHandlerArg3 = 0;
  self->mEmbassies.mpBegin = 0;
  self->mEmbassies.mpEnd = 0;
  self->mEmbassies.mpCap = 0;
  self->mpVecB4 = 0;
  self->mpVecB8 = 0;
  self->mpVecBC = 0;
  self->mpVecCC = 0;
  self->mpVecD0 = 0;
  self->mpVecD4 = 0;

  wt_reset((WorldTree*)&self->mClassTree);
  self->mClassTree.mAnchor.mColor = 0;
  self->mClassTree.mAnchor.mPad0d[0] = 0;
  self->mClassTree.mAnchor.mPad0d[1] = 0;
  self->mClassTree.mAnchor.mPad0d[2] = 0;
  return self;
}

// ---------------------------------------------------------------------------
// @ 0x00d05140
// Reserve room for at least n elements: deep-copy the live range into a new
// block, destroy the old range and free the old block.
// ---------------------------------------------------------------------------
void Vec20::FUN_00d05140(uint32_t n)
{
  if (n <= (uint32_t)(mpCap - mpBegin))
    return;

  Elem20* fresh = 0;
  if (n != 0)
    fresh = (Elem20*)FUN_00f473a0(n << 5, "Simulator", 0, 0, kAllocFile, 0xd1);

  Elem20* oldBegin = mpBegin;
  Elem20* oldEnd = mpEnd;
  Elem20* dst = FUN_00d04cd0(oldBegin, oldEnd, fresh);
  FUN_00d041d0(oldBegin, oldEnd, dst);
  if (oldBegin)
    operator_delete_array(oldBegin);

  uint32_t count = (uint32_t)(oldEnd - oldBegin);
  mpBegin = fresh;
  mpEnd = fresh + count;
  mpCap = (Elem20*)((char*)fresh + (n << 5));
}

// ---------------------------------------------------------------------------
// @ 0x00d05240
// Insert value before pos, either by shifting the tail in place or by growing
// the backing block.
// ---------------------------------------------------------------------------
void Vec20::FUN_00d05240(Elem20* pos, Pair* value)
{
  Elem20* end = mpEnd;
  Elem20* src = (Elem20*)value;

  if (end != mpCap) {
    if (pos <= src && src < end)
      src = (Elem20*)((char*)src + 0x20);
    if (end != 0) {
      end->mKey = end[-1].mKey;
      end->mSub.FUN_00d048a0(&end[-1].mSub);
    }
    FUN_00d04fd0(pos, end - 1, end);
    pos->mKey = src->mKey;
    pos->mSub.FUN_00d049d0(&src->mSub);
    mpEnd = end + 1;
    return;
  }

  int32_t cap = (int32_t)(end - mpBegin);
  if (cap == 0)
    cap = 1;
  else
    cap <<= 1;

  Elem20* fresh = 0;
  if (cap != 0)
    fresh = (Elem20*)FUN_00f473a0((uint32_t)cap << 5, "Simulator", 0, 0,
                                  kAllocFile, 0xd1);

  Elem20* dst = FUN_00d04cd0(mpBegin, pos, fresh);
  FUN_00d041d0(mpBegin, pos, dst);
  if (dst != 0) {
    dst->mKey = src->mKey;
    dst->mSub.FUN_00d048a0(&src->mSub);
  }
  Elem20* newEnd = FUN_00d04cd0(pos, mpEnd, dst + 1);
  FUN_00d041d0(pos, mpEnd, newEnd);
  if (mpBegin)
    operator_delete_array(mpBegin);

  mpBegin = fresh;
  mpEnd = newEnd;
  mpCap = fresh + cap;
}

// ---------------------------------------------------------------------------
// @ 0x00d053e0
// Reset the manager to its empty state, clearing every embedded container.
// ---------------------------------------------------------------------------
void __fastcall FUN_00d053e0(cSPUILayoutManager* self)
{
  wt_clear_outer(&self->mWorlds);
  self->mpCurrent = self->mWorlds.mAnchor.mpLeft;

  self->mEmbassies.FUN_00d051e0(self->mEmbassies.mpBegin,
                                self->mEmbassies.mpEnd);
  FUN_00d018d0(&self->mpVecB4, 0, self->mpVecB4, self->mpVecB8);
  FUN_00530c80(&self->mpVecCC, 0, self->mpVecCC, self->mpVecD0);

  FUN_0011e0744(self->mpBits48, self->mpBits4C, 0);
  self->mpBits4C = trim_word_end(self->mpBits48, self->mpBits4C);

  FUN_0011e0744(self->mpBits60, self->mpBits64, 0);
  self->mpBits64 = trim_word_end(self->mpBits60, self->mpBits64);

  self->mp78 = self->mWorlds.mAnchor.mpLeft;

  wt_clear_nested((WorldTree*)&self->mClassTree);

  FUN_00d0c930(gpClassTree, 0, gpClassTree->mAnchor.mpParent);
  wt_reset((WorldTree*)gpClassTree);

  uint32_t* bvBegin = *(uint32_t**)0x0169d410;
  uint32_t* bvEnd   = *(uint32_t**)0x0169d414;
  FUN_0011e0744(bvBegin, bvEnd, 0);
  *(uint32_t**)0x0169d414 = trim_word_end(bvBegin, bvEnd);

  if (self->mHandler != 0) {
    int h = self->mHandler;
    self->mHandler = 0;
    RemoveHandler(h, self->mpHandlerArg0, self->mpHandlerArg1,
                  self->mpHandlerArg2, self->mpHandlerArg3);
  }
  self->mFlag20 = 0;
}

// ---------------------------------------------------------------------------
// @ 0x00d055d0
// Find the vector element for a key, appending a fresh (empty tree) element
// when absent.  Returns the address of the element's embedded tree.
// ---------------------------------------------------------------------------
void* Vec20::FUN_00d055d0(Pair* key)
{
  Elem20* end = mpEnd;
  Elem20* p = FUN_00d01210(mpBegin, end, key, mField14);

  if (p == end || key->mKey < p->mKey) {
    Elem20 tmp;
    tmp.mKey = key->mKey;
    wt_reset((WorldTree*)&tmp.mSub);

    uint32_t k = tmp.mKey;
    Elem20* lo;
    Elem20* hi;
    if (p == end || p->mKey <= k) {
      lo = p;
      hi = end;
    } else {
      lo = mpBegin;
      hi = p;
    }
    Elem20* q = FUN_00d01210(lo, hi, (Pair*)&tmp, mField14);
    if (q == mpEnd || k < q->mKey)
      q = FUN_00d05380(q, (Pair*)&tmp);

    wt_clear_nested((WorldTree*)&tmp.mSub);
    return (void*)((char*)q + 4);
  }
  return (void*)((char*)p + 4);
}

// ---------------------------------------------------------------------------
// @ 0x00d056c0
// Copy the tree at src+0x24 into the embassy entry of the active planet's
// embassy id, then expose that map's leftmost node in the +0xb4 map.
// ---------------------------------------------------------------------------
void __fastcall FUN_00d056c0(void* self, uint32_t scratch, void* src)
{
  void* rec = FUN_010212a0();
  uint32_t id = FUN_00ce6950(rec, 0);

  Vec20* vec = (Vec20*)((char*)self + 0x9c);
  vec->FUN_00d05560((Pair*)&id);
  void* tree = vec->FUN_00d055d0((Pair*)&id);
  FUN_00d049d0((RTree*)tree, 0, (const RTree*)((char*)src + 0x24));

  tree = vec->FUN_00d055d0((Pair*)&id);
  uint32_t left = *(uint32_t*)((char*)tree + 8);
  uint32_t* slot = FUN_00f41aa0((char*)self + 0xb4, 0, &id);
  *slot = left;
}

// ---------------------------------------------------------------------------
// @ 0x00d05730
// Map a pair of ids to a cWorld.  When both ids belong to the active planet's
// embassy, use the embassy entry; otherwise use the manager's own world map.
// ---------------------------------------------------------------------------
cWorld* __fastcall FUN_00d05730(void* self, uint32_t scratch, WorldTree* tree,
                                uint32_t a, uint32_t b)
{
  FUN_00d009a0(&a, &b);

  Key8 key;
  key.mFirst = a;
  key.mSecond = b;
  uint32_t ida = a;
  uint32_t idb = b;

  void* rec = FUN_010212a0();
  if (rec != 0) {
    if (!(FUN_00ba6650(ida) && FUN_00ba6650(idb))) {
      uint32_t emb = FUN_00ce6950(rec, 0);

      Vec20* vec = (Vec20*)((char*)self + 0x9c);
      Elem20* end = vec->mpEnd;
      Elem20* p = FUN_00d01210(vec->mpBegin, end, (Pair*)&emb,
                               vec->mField14);
      if (p == end || emb < p->mKey)
        p = end;

      if (p != vec->mpEnd) {
        cWorld* w = FUN_00d04e90((WorldTree*)((char*)p + 4), 0, &key);
        void* t = vec->FUN_00d055d0((Pair*)&emb);
        uint32_t left = *(uint32_t*)((char*)t + 8);
        uint32_t* slot = FUN_00f41aa0((char*)self + 0xb4, 0, &emb);
        *slot = left;
        return w;
      }
    }
  }

  cWorld* w = FUN_00d04e90((WorldTree*)((char*)self + 0x24), 0, &key);
  *(uint32_t*)((char*)self + 0x40) = *(uint32_t*)((char*)self + 0x2c);
  return w;
}

// ---------------------------------------------------------------------------
// @ 0x00d05830
// Clear the world record for an id pair: locate (or create) the cWorld and
// empty its nested map.
// ---------------------------------------------------------------------------
void __fastcall FUN_00d05830(void* self, uint32_t scratch, uint32_t a,
                             uint32_t b)
{
  FUN_00d009a0(&a, &b);

  WorldTree* tree = FUN_00d01ab0(self, 0, a, b);
  cWorld* w = FUN_00d01410(self, 0, tree, a, b);
  if (w == 0)
    w = FUN_00d05730(self, 0, tree, a, b);

  WorldTree* inner = (WorldTree*)((char*)w + 8);
  wt_clear_nested(inner);
}
