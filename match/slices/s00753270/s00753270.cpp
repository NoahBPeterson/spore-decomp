// slice s00753270 -- SP::cModelWorld / cMWGroupInternal / cLoadQueue helpers.
//
// Region: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE2 (EH prologue, no stack cookie).
// Byte-exact: FUN_00753dc0, FUN_00754110, FUN_007542b0.  The rest are best-effort
// translations or compiling skeletons (see nonmatching.txt / partial.txt).

#include "types.h"

// ---------------------------------------------------------------------------
// Callees (masked relocations in the original): only signature/convention matter.
// ---------------------------------------------------------------------------
void FUN_007387f0(void*);
void FUN_007389c0(void*, int);
void FUN_00738900(void*);
void FUN_006b4b60(void*, void*, int, int);
char FUN_0071ded0(int, int, void*, void*, void*, void*, int);
void FUN_00738610(int, int, void*);
void* RBTreeIncrement(void*);
void FUN_0074fea0(void*);
void FUN_0093dd80_754250(int, int, int, int, int);
void __cdecl operator_delete__(void* p);   // 0x00f47380 (CRT operator delete)
struct cSPTransform { uint32_t m[12]; cSPTransform& operator=(const cSPTransform& o); };
namespace SP { struct MWGroupDtorStub { void F(); }; }   // 0x00751d00 `MWGroupDtorStub::F`
extern void* g_mwFreeList_162ed38;      // 0x0162ed38 (clip-map node free list)
extern void* g_mwFreeList_162ed18;      // 0x0162ed18 (model free list)
struct FixedAllocatorBase_00926650 { bool AddCore(void* core, unsigned n); };   // 0x00926650
extern FixedAllocatorBase_00926650 g_fixedAlloc_162ed28;                        // 0x0162ed28
void* __cdecl operator_new_753d10(unsigned size, const char* name, int, int, int, int); // 0x00f473a0
struct CompactMap_74f200 { void** Subscript(const uint32_t& key); };            // 0x0074f200
struct Ctor753900 { void* ctor(void* a, void* b); };                            // 0x00753900

// @ 0x00753270  (708 bytes) large cModelWorld helper; skeleton
void FUN_00753270(void* self) { (void)self; }

// @ 0x00753540  (62 bytes) tree foreach
struct TreeNode_00753540 {
  char pad_0[0x14];
  void* mObject;  // +0x14
};
struct TreeWalker_00753540 {
  char pad_0[0x10];
  void* mEnd;   // +0x10
  void* mRoot;  // +0x14
  void ForEach(float a, float b);
};
struct NodeRunThunk {
  void Run(float a, float b);
};
void TreeWalker_00753540::ForEach(float a, float b) {
  void* n = mRoot;
  void* end = (char*)this + 0x10;
  while (n != end) {
    ((NodeRunThunk*)((TreeNode_00753540*)n)->mObject)->Run(a, b);
    n = RBTreeIncrement(n);
  }
}

// @ 0x00753580  (79 bytes) cMWGroupInternal teardown: run the group dtor stub, free the pool
struct cMWGroupInternal_00753580 {
  char pad_0[0x4c];
  void* m4c;                             // +0x4c
  char pad_50[0xc];
  void* m5c;                             // +0x5c
  __declspec(noinline) ~cMWGroupInternal_00753580();
};
cMWGroupInternal_00753580::~cMWGroupInternal_00753580() {
  ((SP::MWGroupDtorStub*)this)->F();
  void* p = m4c;
  if (p != 0 && p != m5c)
    operator_delete__(p);
}

// @ 0x00753630  (316 bytes) job queue lookup; skeleton
void FUN_00753630(void* self, int* p) { (void)self; (void)p; }

// @ 0x00753770  (126 bytes) model-info element constructor (inlined cSPTransform/Matrix ctor)
struct Matrix3_41cb40 { float m[9]; void Assign(const void* src); };   // 0x0041cb40
struct ArrayHolder_7535d0 { void* mArray; void Init(int count); };     // 0x007535d0
extern float g_f162eb0c, g_f162eb10, g_f162eb14, g_f1485720;
extern char  g_m162ec4c[];
struct CspElem_753770 {
  void*        mpObject;    // +0x00
  uint32_t     mFlags;      // +0x04
  uint16_t     m8;          // +0x08
  uint16_t     ma;          // +0x0a
  float        m0c;         // +0x0c
  float        m10;         // +0x10
  float        m14;         // +0x14
  float        m18;         // +0x18
  Matrix3_41cb40 m1c;       // +0x1c
  uint32_t     m40;         // +0x40
  ArrayHolder_7535d0 m44;   // +0x44
  void* Init(void* p0, void* p1);
};
void* CspElem_753770::Init(void* p0, void* p1) {
  mpObject = p0;
  mFlags = 0;
  m8 = 0;
  ma = 0;
  m0c = g_f162eb0c;
  m10 = g_f162eb10;
  m14 = g_f162eb14;
  m18 = g_f1485720;
  m1c.Assign(&g_m162ec4c);
  m40 = 0;
  m44.Init((int)p1);
  mFlags |= 0x80000000u;
  return this;
}

// @ 0x00753810  (108 bytes) vector-of-model-info constructor
struct CspVec_753810 {
  uint32_t       m0;      // +0x00
  uint32_t       m4;      // +0x04
  CspElem_753770 m8;      // +0x08
  void* Init(void* p0, int count, void** arr);
};
void* CspVec_753810::Init(void* p0, int count, void** arr) {
  m4 = 0;
  m0 = 0;
  m8.Init(p0, (void*)count);
  for (int i = 0; i < count; i++) {
    void* p = arr[i];
    *(void**)((char*)m8.m44.mArray + i * 0x3c) = p;
    if (p != 0) {
      *(cSPTransform*)((char*)m8.m44.mArray + i * 0x3c + 4) = *(cSPTransform*)((char*)p + 8);
      ++*(int*)((char*)p + 0x40);
    }
  }
  return this;
}

// @ 0x00753880  (127 bytes) cLoadQueue constructor: EH-vector-construct 8 cLoadingModel entries, init deque
struct CLoadingModel_73880 { uint8_t m[0x50]; CLoadingModel_73880(); ~CLoadingModel_73880(); };
struct Deque_7458d0 { uint32_t m[10]; void Init(int n); };   // 0x007458d0
struct cLoadQueue_00753880 {
  uint32_t           m0;       // +0x000
  CLoadingModel_73880 mArr[8]; // +0x004 (8 x cLoadingModel; compiler emits the EH vector ctor)
  Deque_7458d0       mDeque;   // +0x284
  uint32_t           m2ac;     // +0x2ac
  uint32_t           m2b0;     // +0x2b0
  cLoadQueue_00753880();
};
cLoadQueue_00753880::cLoadQueue_00753880() : m0(0) {
  mDeque.m[0] = 0; mDeque.m[1] = 0; mDeque.m[2] = 0; mDeque.m[3] = 0; mDeque.m[4] = 0;
  mDeque.m[5] = 0; mDeque.m[6] = 0; mDeque.m[7] = 0; mDeque.m[8] = 0; mDeque.m[9] = 0;
  mDeque.Init(0);
  m2b0 = 0;
}

// @ 0x00753900  (678 bytes) cModelWorld constructor (EH); skeleton
void cModelWorld_ctor_00753900(void* self) { (void)self; }

// @ 0x00753bb0  (155 bytes) fixed-allocator node acquire + intrusive circular-list push
struct MwOwner_753bb0 {
  char  pad_0[0x1ac];
  void* m1ac;   // +0x1ac (list head.prev / sentinel)
  void* m1b0;   // +0x1b0 (list head.next)
  void* Register(void* a, void* b);
};
void* MwOwner_753bb0::Register(void* a, void* b) {
  CspVec_753810* node;
  for (;;) {
    node = (CspVec_753810*)g_mwFreeList_162ed38;
    if (node != 0) {
      g_mwFreeList_162ed38 = *(void**)node;
      break;
    }
    if (!g_fixedAlloc_162ed28.AddCore(0, 0))
      break;
  }
  CspVec_753810* obj;
  if (node != 0)
    obj = (CspVec_753810*)node->Init(this, (int)a, (void**)b);
  else
    obj = 0;
  void* next = *(void**)((char*)this + 0x1b0);
  *(void**)((char*)obj + 0) = (char*)this + 0x1ac;
  *(void**)((char*)obj + 4) = next;
  *(void**)((char*)this + 0x1b0) = obj;
  *(void**)next = obj;
  return (char*)obj + 8;
}

// @ 0x00753c50  (187 bytes) SP::cModelWorld::FinalRelease
struct List_753c50 { void erase(void* key); };            // 0x0074be40
struct MwNode_753c50 { MwNode_753c50* mpPrev; MwNode_753c50* mpNext; };
struct NodeFc_753c50 { void F746fc0(); };                 // 0x00746fc0
struct cModelWorld_753c50 {
  virtual void cv0();
  virtual void cv1();
  char     pad_4[0x1c - 4];
  uint8_t  m1c;                       // +0x1c mWorldType
  char     pad_1d[0x314 - 0x1d];
  List_753c50 mList;                  // +0x314
  char     pad_318[0x894 - 0x318];
  uint32_t m894;                      // +0x894
  uint32_t m898;                      // +0x898
  void FinalRelease(void** p2, char p3);
  void ShutdownModel753c50(void* p);
};
void cModelWorld_753c50::FinalRelease(void** p2, char p3) {
  *p2 = 0;
  MwNode_753c50* node = (MwNode_753c50*)((char*)p2 - 8);
  if (p3 != 0) {
    if (m1c != 0) {
      MwNode_753c50* mpN = node->mpNext;
      MwNode_753c50* mpP = node->mpPrev;
      mpN->mpPrev = mpP;
      mpP->mpNext = mpN;
      node->mpPrev = 0;
      node->mpNext = 0;
    } else {
      cv1();
    }
    ((cMWGroupInternal_00753580*)node)->~cMWGroupInternal_00753580();
    node->mpPrev = (MwNode_753c50*)g_mwFreeList_162ed38;
    g_mwFreeList_162ed38 = node;
    return;
  }
  if (m1c != 0) {
    MwNode_753c50* mpN = node->mpNext;
    MwNode_753c50* mpP = node->mpPrev;
    mpN->mpPrev = mpP;
    mpP->mpNext = mpN;
    node->mpPrev = 0;
    node->mpNext = 0;
    void* tmp = (char*)node + 8;
    mList.erase(&tmp);
    ShutdownModel753c50(node);
    m894 += 0xffffffffu;
    if ((*(uint32_t*)((char*)node + 0x138) & 0x80000010u) == 0)
      m898 += 0xffffffffu;
  } else {
    cv1();
  }
  ((NodeFc_753c50*)node)->F746fc0();
  node->mpPrev = (MwNode_753c50*)g_mwFreeList_162ed18;
  g_mwFreeList_162ed18 = node;
}

// @ 0x00753d10  (174 bytes) operator new + cModelWorld ctor + CompactMap insert
struct IEventObject_753d10 { virtual void ev0(); virtual void ev1(); };
struct MwOwner_753d10 {
  virtual void ov0();
  char              pad_4[0xc - 4];
  CompactMap_74f200 mMap;         // +0x0c
  void* Create(uint32_t key, void* unused, void* a2);
};
void* MwOwner_753d10::Create(uint32_t key, void* unused, void* a2) {
  (void)unused;
  void* mem = operator_new_753d10(0x8b8, "Graphics", 0, 0, 0, 0);
  IEventObject_753d10* obj = 0;
  if (mem != 0)
    obj = (IEventObject_753d10*)((Ctor753900*)mem)->ctor(this, a2);
  typedef void (__thiscall *Fn174)(void*);
  (*(Fn174*)((char*)(*(void***)obj) + 0x174))(obj);
  void** slot = mMap.Subscript(key);
  IEventObject_753d10* old = (IEventObject_753d10*)*slot;
  if (obj != old) {
    obj->ev0();
    *slot = obj;
    if (old != 0)
      old->ev1();
  }
  return obj;
}

// @ 0x00753dc0  (59 bytes)
void FUN_00753dc0(int param_1, unsigned char param_2) {
  if ((param_2 & 2) != 0) {
    FUN_007387f0((void*)param_1);
  } else if ((param_2 & 4) != 0) {
    FUN_007389c0((void*)param_1, 1);
  }
  if ((param_2 & 8) != 0) {
    FUN_00738900((void*)param_1);
  }
}

// @ 0x00753e00  (383 bytes) skeleton
void FUN_00753e00(void* self) { (void)self; }

// @ 0x00753fc0  (31 bytes) callback refcount release; register allocation differs
struct RC_00753fc0 {
  void* p;
  volatile int n;
};
void FUN_00753fc0(RC_00753fc0* param_1) {
  int n = (param_1->n += -1);
  if (n == 0) {
    param_1->n = 1;
    // vtable slot 0 (deleting dtor) called thiscall on the record itself: the original's `ecx`
    // at the call is `this`, not a register-allocation choice (hybrid 2026-10-12).
    typedef void(__thiscall *Fn)(RC_00753fc0*, int);
    Fn fn = *(Fn*)param_1->p;
    fn(param_1, 1);
  }
}

// @ 0x00753fe0  (301 bytes) KDTree asset build (EH); skeleton
void FUN_00753fe0(void* self, void* a) { (void)self; (void)a; }

// @ 0x00754110  (25 bytes)
class Stub_754110 {
 public:
  char pad_0[0x64];
  void* m064;
  void* m068;
  bool FUN_00754110(int arg);
};
bool Stub_754110::FUN_00754110(int arg) {
  FUN_006b4b60(m068, m064, 0, 0);
  return true;
}

// @ 0x007541b0  (158 bytes) find-or-insert into a 0x20-stride table
void FUN_007541b0(int param_1, int param_2, int param_3) {
  int found[2] = { -1, -1 };
  int limits[2] = { 2, 2 };
  int keys[2] = { param_2, param_3 };
  int span[2] = { 8, 8 };
  char c = (char)FUN_0071ded0(param_1, 2, found, span, keys, limits, 0);
  if (c != 0) {
    *(int*)(found[1] * 0x20 + 4 + *(int*)(param_1 + 8)) = param_2;
    FUN_00738610(param_1, 1, found);
    return;
  }
  if (found[1] >= 0) {
    *(int*)(found[1] * 0x20 + 4 + *(int*)(param_1 + 8)) = param_2;
  }
}

// @ 0x00754250  (94 bytes) two-short init + thunk ctor (EH)
struct S_754250 {
  char pad_0[0x10];
  uint16_t m10;
  uint16_t m12;
  S_754250* FUN_00754250(int param_2);
};
typedef void (__thiscall* ConstructVariantFn)(void* self, int, int, int, int, int);
S_754250* S_754250::FUN_00754250(int param_2) {
  m10 = 2;
  m12 = 0x39;
  ((ConstructVariantFn)FUN_0093dd80_754250)(this, 0x39, 0, param_2, 0x18, 1);
  return this;
}

// @ 0x007542b0  (79 bytes)
bool FUN_007542b0(int param_1, int param_2) {
  if (param_2 != 0) {
    ++*(int*)(param_2 + 4);
    void* fn = *(void**)(param_1 + 0x24);
    void* a = *(void**)(param_1 + 0x20);
    *(int*)(param_1 + 0x20) = param_2;
    *(void**)(param_1 + 0x24) = (void*)&FUN_00753fc0;
    if (fn != 0) {
      ((void(__cdecl*)(void*))fn)(a);
    }
  } else {
    void* fn = *(void**)(param_1 + 0x24);
    void* a = *(void**)(param_1 + 0x20);
    *(void**)(param_1 + 0x20) = 0;
    *(void**)(param_1 + 0x24) = 0;
    if (fn != 0) {
      ((void(__cdecl*)(void*))fn)(a);
      return true;
    }
  }
  return true;
}
