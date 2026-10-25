// Slice s009a9600: cSPUILayoutManager / rbtree helpers.
// Reconstructed from the annotated disassembly; real name for the EASTL DoNukeSubtree.
#include "types.h"

// ---------------------------------------------------------------------------
// stubs
// ---------------------------------------------------------------------------
extern void FUN_f47380(void*);              // operator delete(void*) cdecl
struct S9a3630b { int f(); };               // refcount-descend (slice 33)
struct S9ac2a0 { void f(); };
struct S9ae1c0 { void f(); };
struct S99c970 { void f(); };
struct S9ac2b0 { float f(); };

extern "C" __declspec(dllimport) unsigned long __stdcall
GetFullPathNameA(const char*, unsigned long, char*, char**);

struct S9a9600 { void f(void*); };
struct S9a9640 { void f(); };
struct S9a9b90 { S9a9b90* f(int); };
struct S9aa4c0 { S9aa4c0* f(int*); };
struct S9aa500 { int* f(int*, unsigned*); };

// ---------------------------------------------------------------------------
// @ 0x009a9600  eastl::rbtree<...>::DoNukeSubtree
// ---------------------------------------------------------------------------
void S9a9600::f(void* node_) {
  char* node = (char*)node_;
  while (node) {
    ((S9a9600*)this)->f(*(void**)node);
    char* next = *(char**)(node + 4);
    FUN_f47380(node);
    node = next;
  }
}

// ---------------------------------------------------------------------------
// @ 0x009a9640
// ---------------------------------------------------------------------------
void S9a9640::f() {
  char* self = (char*)this;
  int* end = *(int**)(self + 4);
  for (int* p = *(int**)self; p < end; p++) {
    if (*p) ((S9a3630b*)(size_t)*p)->f();
  }
  int v = *(int*)self;
  if (v && *(int*)(v - 4)) FUN_f47380((void*)v);
}

// ---------------------------------------------------------------------------
// EASTL containers owned by cSPUILayoutManager: rbtree (0x1c) and vector (0x14).
// ---------------------------------------------------------------------------
struct RbNodeBase {
  RbNodeBase* mpNodeRight;              // +0x00
  RbNodeBase* mpNodeLeft;               // +0x04
  RbNodeBase* mpNodeParent;             // +0x08
  char        mColor;                   // +0x0c
};
template<class V> struct RbNode : RbNodeBase { V mValue; };
struct EmptyLess {};
struct EmptyAlloc {};

template<class V>
struct RbTree {                         // 0x1c bytes
  EmptyLess  mCompare;                  // +0x00
  RbNodeBase mAnchor;                   // +0x04
  unsigned   mnSize;                    // +0x14
  EmptyAlloc mAllocator;                // +0x18
  RbTree() : mAnchor() {
    mAnchor.mpNodeRight = &mAnchor;
    mAnchor.mpNodeLeft = &mAnchor;
    mAnchor.mpNodeParent = 0;
    mAnchor.mColor = 0;
    mnSize = 0;
  }
};

template<class T>
struct SpVector {                       // 0x14 bytes
  T*       mpBegin;                     // +0x00
  T*       mpEnd;                       // +0x04
  T*       mpCapacity;                  // +0x08
  unsigned mAllocator[2];               // +0x0c (empty named allocator)
  SpVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
};

// Node values: a key at +0x10 followed by one pointer payload at +0x14.
struct PayloadPtr { unsigned mKey; void* mpValue; };
struct PayloadVec { unsigned mKey; SpVector<int>* mpValue; };

// Element of mpVec2: a string with a one-byte inline buffer (0x14 bytes).
struct AnimString {
  char*    mpBegin;                     // +0x00
  char*    mpEnd;                       // +0x04
  char*    mpCapacity;                  // +0x08
  unsigned mAllocator[2];               // +0x0c
};

extern void* __cdecl FUN_f473a0(unsigned size, const char* name, int flags, unsigned debugFlags,
                                const char* file, int line);
inline void* operator new(unsigned size, const char* pName, int flags, unsigned debugFlags,
                          const char* file, int line) {
  return FUN_f473a0(size, pName, flags, debugFlags, file, line);
}

extern void __cdecl FUN_9cabb0(void* p);        // delete element (dtor + free)
extern bool __cdecl FUN_9feb30();
void* __cdecl FUN_921580(void* node);           // eastl::RBTreeIncrement

struct S9a3c40 { void f(void* node); };         // rbtree<...cWorld>::DoNukeSubtree
struct S9a3c80 { void f(void* node); };         // second rbtree instantiation
struct S9e1710 { void f(); };                   // node payload destructor
struct S5d9320 { void FUN_5d9320(void* node); };
struct S9ab880 { void FUN_9ab880(); };          // baked_anim_manager::Reset (jmp thunk)
struct S9abce0 { void FUN_9abce0(); };          // baked_anim_manager destructor
struct Sc2e4e0 { void f(); };
struct S9ab430 { void* f(); };                  // baked_anim_manager constructor (returns this)

struct cSPUILayoutManager {
  RbTree<int>*         mpTree0;         // +0x00  rbtree<unsigned, pair<const unsigned, cWorld>>
  RbTree<int>*         mpTree1;         // +0x04  second rbtree instantiation
  int                  mn08;            // +0x08
  SpVector<char*>*     mpVec0;          // +0x0c
  SpVector<char*>*     mpVec1;          // +0x10
  RbTree<PayloadPtr>*  mpTree2;         // +0x14
  SpVector<AnimString>* mpVec2;         // +0x18
  RbTree<int>*         mpTree3;         // +0x1c
  RbTree<PayloadVec>*  mpTree4;         // +0x20
  SpVector<int>*       mpVec3;          // +0x24
  RbTree<int>*         mpTree5;         // +0x28
  void*                mpMgr;           // +0x2c  baked_anim_manager
  bool                 mbInitialized;   // +0x30
  bool Init();
  void Shutdown();
};

// ---------------------------------------------------------------------------
// @ 0x009a9680  cSPUILayoutManager::Shutdown
// ---------------------------------------------------------------------------
void cSPUILayoutManager::Shutdown() {
  if (!mbInitialized) return;
  if (mpTree0) {
    ((S9a3c40*)mpTree0)->f(mpTree0->mAnchor.mpNodeParent);
    FUN_f47380(mpTree0);
  }
  mpTree0 = 0;
  if (mpTree1) {
    ((S9a3c80*)mpTree1)->f(mpTree1->mAnchor.mpNodeParent);
    FUN_f47380(mpTree1);
  }
  mpTree1 = 0;
  if (mpVec0) {
    ((S9a9640*)mpVec0)->f();
    FUN_f47380(mpVec0);
  }
  mpVec0 = 0;
  for (unsigned i = 0; i < mpVec1->size(); ++i) FUN_9cabb0(mpVec1->mpBegin[i]);
  if (mpVec1) {
    if (mpVec1->mpBegin && ((int*)mpVec1->mpBegin)[-1]) FUN_f47380(mpVec1->mpBegin);
    FUN_f47380(mpVec1);
  }
  mpVec1 = 0;
  {
    RbTree<PayloadPtr>* t = mpTree2;
    RbNodeBase* end = &t->mAnchor;
    for (RbNodeBase* n = t->mAnchor.mpNodeLeft; n != end; n = (RbNodeBase*)FUN_921580(n)) {
      void* p = ((RbNode<PayloadPtr>*)n)->mValue.mpValue;
      if (p) {
        ((S9e1710*)p)->f();
        FUN_f47380(p);
      }
    }
    if (t) {
      RbNode<PayloadPtr>* q = (RbNode<PayloadPtr>*)t->mAnchor.mpNodeParent;
      while (q) {
        ((S9a9600*)t)->f(q->mpNodeRight);
        RbNode<PayloadPtr>* next = (RbNode<PayloadPtr>*)q->mpNodeLeft;
        FUN_f47380(q);
        q = next;
      }
      FUN_f47380(t);
    }
  }
  mpTree2 = 0;
  {
    SpVector<AnimString>* v = mpVec2;
    if (v) {
      AnimString* const end = v->mpEnd;
      for (AnimString* p = v->mpBegin; p < end; ++p)
        if (p->mpCapacity - p->mpBegin > 1 && p->mpBegin) FUN_f47380(p->mpBegin);
      if (v->mpBegin && ((int*)v->mpBegin)[-1]) FUN_f47380(v->mpBegin);
      FUN_f47380(v);
    }
  }
  mpVec2 = 0;
  {
    RbTree<int>* t = mpTree3;
    if (t) {
      RbNode<int>* q = (RbNode<int>*)t->mAnchor.mpNodeParent;
      while (q) {
        ((S9a9600*)t)->f(q->mpNodeRight);
        RbNode<int>* next = (RbNode<int>*)q->mpNodeLeft;
        FUN_f47380(q);
        q = next;
      }
      FUN_f47380(t);
    }
  }
  mpTree3 = 0;
  {
    RbTree<PayloadVec>* t = mpTree4;
    RbNodeBase* end = &t->mAnchor;
    for (RbNodeBase* n = t->mAnchor.mpNodeLeft; n != end; n = (RbNodeBase*)FUN_921580(n)) {
      SpVector<int>* p = ((RbNode<PayloadVec>*)n)->mValue.mpValue;
      if (p) {
        if (p->mpBegin && ((int*)p->mpBegin)[-1]) FUN_f47380(p->mpBegin);
        FUN_f47380(p);
      }
    }
    if (t) {
      RbNode<PayloadVec>* q = (RbNode<PayloadVec>*)t->mAnchor.mpNodeParent;
      while (q) {
        ((S9a9600*)t)->f(q->mpNodeRight);
        RbNode<PayloadVec>* next = (RbNode<PayloadVec>*)q->mpNodeLeft;
        FUN_f47380(q);
        q = next;
      }
      FUN_f47380(t);
    }
  }
  mpTree4 = 0;
  {
    SpVector<int>* v = mpVec3;
    if (v) {
      if (v->mpBegin && ((int*)v->mpBegin)[-1]) FUN_f47380(v->mpBegin);
      FUN_f47380(v);
    }
  }
  mpVec3 = 0;
  {
    RbTree<int>* t = mpTree5;
    if (t) {
      ((S5d9320*)t)->FUN_5d9320(t->mAnchor.mpNodeParent);
      FUN_f47380(t);
    }
  }
  mpTree5 = 0;
  ((S9ab880*)mpMgr)->FUN_9ab880();
  if (mpMgr) {
    ((S9abce0*)mpMgr)->FUN_9abce0();
    FUN_f47380(mpMgr);
  }
  mpMgr = 0;
  mbInitialized = false;
}

// ---------------------------------------------------------------------------
// @ 0x009a9920  cSPUILayoutManager::Init
// ---------------------------------------------------------------------------
bool cSPUILayoutManager::Init() {
  if (mbInitialized) return true;
  mpTree0 = new ("Anim/globals", 0, 0, 0, 0) RbTree<int>();
  mn08 = 0;
  mpTree1 = new ("Anim/globals", 0, 0, 0, 0) RbTree<int>();
  mpVec0 = new ("Anim/globals", 0, 0, 0, 0) SpVector<char*>();
  mpVec1 = new ("Anim/globals", 0, 0, 0, 0) SpVector<char*>();
  mpTree2 = new ("Anim/globals", 0, 0, 0, 0) RbTree<PayloadPtr>();
  mpVec2 = new ("Anim/globals", 0, 0, 0, 0) SpVector<AnimString>();
  mpTree3 = new ("Anim/globals", 0, 0, 0, 0) RbTree<int>();
  mpTree4 = new ("Anim/globals", 0, 0, 0, 0) RbTree<PayloadVec>();
  mpVec3 = new ("Anim/globals", 0, 0, 0, 0) SpVector<int>();
  mpTree5 = new ("Anim/globals", 0, 0, 0, 0) RbTree<int>();
  S9ab430* mgr = (S9ab430*)FUN_f473a0(0x4c, "Anim/globals", 0, 0, 0, 0);
  mpMgr = mgr ? mgr->f() : 0;
  ((Sc2e4e0*)mpMgr)->f();
  mbInitialized = true;
  if (!FUN_9feb30()) {
    Shutdown();
    return false;
  }
  return true;
}

// ---------------------------------------------------------------------------
// @ 0x009a9b70  GetFullPathNameA wrapper
// ---------------------------------------------------------------------------
unsigned long __cdecl FUN_009a9b70(const char* a, unsigned long b, char* c, char** d) {
  return GetFullPathNameA(a, b, c, d);
}

// ---------------------------------------------------------------------------
// @ 0x009a9b90
// ---------------------------------------------------------------------------
S9a9b90* S9a9b90::f(int p2) {
  int old = *(int*)this;
  if (p2 != old) {
    if (p2) ((S9ac2a0*)(size_t)p2)->f();
    *(int*)this = p2;
    if (old) ((S9ae1c0*)(size_t)old)->f();
  }
  return this;
}

// ---------------------------------------------------------------------------
// @ 0x009a9bc0  three-field strict-less comparator
// ---------------------------------------------------------------------------
bool __stdcall FUN_009a9bc0(unsigned* a, unsigned* b) {
  if (a[0] < b[0]) return true;
  if (a[0] == b[0]) {
    if (a[1] < b[1]) return true;
    if (a[1] == b[1]) return a[3] < b[3];
  }
  return false;
}

// ---------------------------------------------------------------------------
// @ 0x009a9c00  (1949 bytes; skeleton)
// ---------------------------------------------------------------------------
struct Vec4A { float x, y, z, w; };
struct AnimDesc {                       // *(anim+0) : creature animation descriptor
  uint32_t pad0[0x43];
  float scaleX, scaleY, scaleZ;         // 0x10c..0x114
  Vec4A tint;                           // 0x118: x unused here, y(0x11c) = speed
  uint32_t pad128[10];
  uint32_t flags;                       // 0x150
};
struct AnimInfo { uint32_t pad[4]; uint32_t flags; };   // *(anim+8): flags at +0x10
struct AnimBlock {                      // 9 floats; normalized by FUN_0099ce40
  float pos[4];                         // +0x00
  float rot[5];                         // +0x10 (quaternion) .. +0x20
  void Normalize();                     // 0x0099ce40, thiscall
};
struct AnimState {
  AnimDesc* desc;                       // 0x00
  uint32_t pad04;
  AnimInfo* info;                       // 0x08
  uint32_t pad0c[8];                    // 0x0c..0x2b
  AnimBlock blockA;                     // 0x2c
  AnimBlock blockB;                     // 0x50 (0x2c + 0x24)
};
struct BoneSlot {                       // 700 bytes
  AnimDesc* desc;                       // 0x00
  uint32_t pad04[0x18];
  float f64;
  uint32_t pad68[4];
  float f78;
  float f7c, f80, f84;
  float f88;
  Vec4A v8c;                            // 0x8c..0x98
  float f9c;
  uint32_t padA0[0x2bc / 4 - 0x28];
};
struct CreatureDesc { uint32_t pad[0xfd]; uint8_t pad3f4; uint8_t flag3f5; };
struct CreatureAnim {
  CreatureDesc* desc;                   // 0x00
  uint32_t pad04[5];
  float outPos[3];                      // 0x18
  uint32_t pad24[6];
  float outRot[4];                      // 0x3c
  uint32_t pad4c[9];
  float timeScale;                      // 0x70
  uint32_t pad74[(0x2e4 - 0x74) / 4];
  BoneSlot* slotsBegin;                 // 0x2e4
  BoneSlot* slotsEnd;                   // 0x2e8
  uint32_t pad2ec[(0x168c - 0x2ec) / 4];
  uint8_t flag168c;
  void RefreshDirty(float);             // 0x009b8f40 thiscall
  void FUN_009c0680();                  // thiscall
};
extern int g_015509f0, g_015509dc;
extern float __cdecl FUN_009a1d90(AnimState*, float, int, int);
extern void __cdecl FUN_009be260(CreatureAnim*);
extern void __cdecl FUN_009bd340(CreatureAnim*);
extern void __cdecl FUN_009b3bc0(CreatureAnim*);
extern void __cdecl FUN_0099e110(float, CreatureAnim*, AnimState*, int, int, int);
extern float* __cdecl QuaternionVectorTransform(float* out, const float* q, const float* v);
extern void __cdecl FUN_009bc580(CreatureAnim*, float);
extern void __cdecl FUN_0099d460(float, CreatureAnim*, AnimState*, float);
extern void __cdecl FUN_009f9b40(CreatureAnim*);
extern void __cdecl FUN_009bd550(float, float, CreatureAnim*, int);

static inline void ClearBlock(AnimBlock* b) {
  b->pos[0] = 0.0f; b->pos[1] = 0.0f; b->pos[2] = 0.0f; b->pos[3] = 0.0f;
  b->rot[0] = 0.0f; b->rot[1] = 0.0f; b->rot[2] = 0.0f; b->rot[3] = 0.0f; b->rot[4] = 0.0f;
}
static __forceinline void InitSlot(CreatureAnim* c, BoneSlot* s) {
  if ((s->desc->flags & 4) && s->f64 == 0.0f && s->f78 == 0.0f && s->f88 == 0.0f && s->f9c == 0.0f) {
    float t = c->timeScale;
    s->f7c = t * s->desc->scaleX;
    s->f80 = s->desc->scaleY * t;
    s->f84 = s->desc->scaleZ * t;
    s->f88 = 1.0f;
    s->v8c = s->desc->tint;
    s->f9c = 1.0f;
  }
}

// @ 0x009a9c00
void FUN_009a9c00(CreatureAnim* c, AnimState* a, float t) {
  float speed = a->desc->tint.y;
  FUN_009a1d90(a, t, 1, 0);
  if ((a->info->flags & 1) && (a->info->flags & 2)) FUN_009be260(c);
  FUN_009bd340(c);
  FUN_009b3bc0(c);
  ClearBlock(&a->blockA);
  ClearBlock(&a->blockB);
  FUN_0099e110(1.0f, c, a, 0, 1, 1);
  a->blockA.Normalize();
  a->blockB.Normalize();
  float tmp[3];
  const float* r = QuaternionVectorTransform(tmp, a->blockB.rot, a->blockA.pos);
  c->outPos[0] = r[0] + a->blockB.pos[0];
  c->outPos[1] = r[1] + a->blockB.pos[1];
  c->outPos[2] = r[2] + a->blockB.pos[2];
  c->outRot[0] = ((a->blockA.rot[0] * a->blockB.rot[3] + a->blockB.rot[0] * a->blockA.rot[3]) - a->blockA.rot[1] * a->blockB.rot[2]) + a->blockA.rot[2] * a->blockB.rot[1];
  c->outRot[1] = ((a->blockB.rot[2] * a->blockA.rot[0] + a->blockA.rot[1] * a->blockB.rot[3]) + a->blockB.rot[1] * a->blockA.rot[3]) - a->blockA.rot[2] * a->blockB.rot[0];
  c->outRot[2] = ((a->blockB.rot[2] * a->blockA.rot[3] - a->blockB.rot[1] * a->blockA.rot[0]) + a->blockA.rot[2] * a->blockB.rot[3]) + a->blockA.rot[1] * a->blockB.rot[0];
  c->outRot[3] = ((a->blockB.rot[3] * a->blockA.rot[3] - a->blockA.rot[0] * a->blockB.rot[0]) - a->blockB.rot[1] * a->blockA.rot[1]) - a->blockA.rot[2] * a->blockB.rot[2];
  FUN_009bc580(c, speed);
  FUN_0099d460(1.0f, c, a, 1.0f);
  int n = (int)(c->slotsEnd - c->slotsBegin);
  for (int i = 0; i < n; i++) InitSlot(c, &c->slotsBegin[i]);
  if (g_015509f0 && !c->desc->flag3f5 && c->flag168c) c->FUN_009c0680();
  if (!c->desc->flag3f5) c->RefreshDirty(1.0f);
  if (g_015509dc) FUN_009f9b40(c);
  FUN_009bd550(speed, 0.0f, c, 0);
}

// ---------------------------------------------------------------------------
// @ 0x009aa3a0  seek a baked animation to frame `n` (normalized time)
// ---------------------------------------------------------------------------
namespace nSPCreatureAnim {
struct baked_animation_data {
  char     pad_00[0x0c];
  uint32_t mElementCount;               // +0x0c  entries per frame
  uint32_t mFrameCount;                 // +0x10
  float    mScale;                      // +0x14
  char     pad_18[0x20];
};
struct baked_animation {
  baked_animation_data* mpData;         // +0x00
  uint32_t field_04;                    // +0x04
  uint32_t mID;                         // +0x08
  char     mName[0x104];                // +0x0c
  int      field_110;                   // +0x110
  float GetScale() const;               // 0x009AC2B0
};
}  // namespace nSPCreatureAnim

struct S9ae350 { void f(int n, float t, void* o, void* p2); };   // 0x009AE350

void __cdecl F9aa3a0(void* o, void* p2, nSPCreatureAnim::baked_animation* b, unsigned n) {
  unsigned count = b->mpData ? b->mpData->mFrameCount : 0;
  float scale = b->GetScale();
  float frac;
  if (count <= 1) frac = 0.0f;
  else frac = (float)n * scale / (float)(count - 1);
  FUN_009a9c00((CreatureAnim*)o, (AnimState*)p2, frac);
  ((S9ae350*)b)->f((int)n, frac, o, p2);
}

// ---------------------------------------------------------------------------
// @ 0x009aa440
// ---------------------------------------------------------------------------
bool FUN_009aa440(int param_1, int* param_2) {
  bool bVar3;
  if (((*(unsigned char*)((char*)param_2 + 0x1ac) & 7) == 4) && param_2[0x8e] == 0)
    bVar3 = false;
  else
    bVar3 = true;
  int iVar1 = *param_2;
  int iVar5 = *(int*)(param_1 + 0x2e8) - *(int*)(param_1 + 0x2e4);
  unsigned uVar2 = *(unsigned*)(iVar1 + 0x440);
  bool al = uVar2 < (unsigned)(iVar5 / 700);
  if (bVar3 && !al) return 1;
  if (!bVar3 && !al) {
    if (*(int*)(iVar1 + 0x1f8) == 0) return 1;
    return 0;
  }
  if (*(unsigned*)(iVar1 + 0x1f8) == uVar2) return 1;
  if (*(int*)(iVar1 + 0x1f8) == 0) return 1;
  return 0;
}

// ---------------------------------------------------------------------------
// @ 0x009aa4c0
// ---------------------------------------------------------------------------
S9aa4c0* S9aa4c0::f(int* p) {
  int n = *p;
  int old = *(int*)this;
  if (n != old) {
    if (n) ((S99c970*)(size_t)n)->f();
    *(int*)this = n;
    if (old) ((S9a3630b*)(size_t)old)->f();
  }
  return this;
}

// ---------------------------------------------------------------------------
// @ 0x009aa500  rbtree three-field lower_bound
// ---------------------------------------------------------------------------
int* S9aa500::f(int* out, unsigned* key) {
  char* head = (char*)this + 4;
  char* parent = head;
  char* node = *(char**)((char*)this + 0xc);
  while (node) {
    unsigned n0 = *(unsigned*)(node + 0x10);
    unsigned n1 = *(unsigned*)(node + 0x14);
    unsigned n3 = *(unsigned*)(node + 0x1c);
    if (n0 < key[0] || (n0 == key[0] && (n1 < key[1] || (n1 == key[1] && n3 < key[3]))))
      node = *(char**)node;
    else { parent = node; node = *(char**)(node + 4); }
  }
  if (parent != head && *(unsigned*)(parent + 0x10) <= key[0] &&
      (key[0] != *(unsigned*)(parent + 0x10) ||
       (*(unsigned*)(parent + 0x14) <= key[1] &&
        (key[1] != *(unsigned*)(parent + 0x14) || *(unsigned*)(parent + 0x1c) <= key[3])))) {
    *out = (int)(size_t)parent;
    return out;
  }
  *out = (int)(size_t)head;
  return out;
}
