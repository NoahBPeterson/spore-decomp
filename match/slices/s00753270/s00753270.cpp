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

// Drain one pending background load of a cModelWorld.
//
// Runs under an SEH scope.  Takes a load-queue entry by value-pointer: it
// AddRefs the entry's model and job, waits for the job, then walks the five
// intrusive model-owner lists collected in the entry, sorting each and
// dispatching every node through its vtable slot +0x34.
struct MwModel_mw {
  virtual void mv0();
  virtual void mv1();
  uint32_t  m4;          // +0x04 (high bit used as a flag)
  char      pad08[0x38]; // +0x08
  int       m40;         // +0x40 refcount
  void      AddRefOrDestroy();
};
struct cJob_mw {
  void AddRef();     // 0x0068f950
  void Wait();       // 0x006926b0
  void GetStatus();  // 0x00690120 (Release is used here in practice)
  void Release();    // 0x00690120
};
struct LoadEntry_mw {
  MwModel_mw* mpModel;   // +0x00
  char      pad04[0x18];     // +0x04
  uint8_t   m1c;             // +0x1c
  char      pad1d[3];        // +0x1d
  cJob_mw* mpJob;        // +0x20
  char      pad24[0x10];     // +0x24
  void*     mpLists[5];      // +0x34  five intrusive model-owner lists
};

struct VecBase_mw { void* begin; void* end; void* cap; void* pad0c; void* pad10; };

extern "C" void* eastl_copydispatch_copy_intrusive(void*, void*, void*);  // 0x006f43e0
extern "C" void  DestroyRange_mw(void* a, void* b);                   // 0x0070f520
extern "C" void  SortWithCmp_mw(void* range, void* cmp);              // 0x0073bd60
extern "C" int   Cmp_mw(void* a, void* b);                            // 0x00743910
extern "C" void* AllocIntro_mw();                                     // 0x0067dd60
extern "C" void  FinishBackgroundLoad_mw(void* self, void* entry);    // 0x00751560

static void CModelWorld_ReleaseModel753270(MwModel_mw* m)
{
  if (m == 0)
    return;
  const int n = m->m40;
  if (n < 2)
    (*(void(__thiscall**)(MwModel_mw*, unsigned))(*(void***)m)[0x170 / 4])(m, m->m4 >> 0x1f);
  else
    m->m40 = n - 1;
}

// @ 0x00753270  (708 bytes)
void FUN_00753270(void* self, LoadEntry_mw* entry)
{
  MwModel_mw* model = entry->mpModel;
  if (model != 0)
    ++model->m40;

  cJob_mw* job = entry->mpJob;
  if (job != 0)
    job->AddRef();
  entry->mpJob->Wait();

  if (entry->m1c != 0 && entry->mpJob == job) {
    char* obj = (char*)AllocIntro_mw();

    // Local growable vector<P> scratch (begin/end/cap + allocator).
    void* vec[2] = { 0, 0 };
    void* scratch[2] = { 0, 0 };
    char* work = (char*)vec;  // work area reused for the temporary block

    for (int i = 0; i < 5; ++i) {
      void** list = (void**)((char*)entry + 0x34 + i * 4);
      if (*list == 0)
        continue;

      void* endRec = eastl_copydispatch_copy_intrusive(scratch, scratch, vec);
      DestroyRange_mw(endRec, scratch);
      // Sorting the collected range with the model comparator.
      SortWithCmp_mw(&scratch[0], (void*)Cmp_mw);

      void** p   = (void**)scratch[0];
      void** end = (void**)scratch[1];
      while (p != end) {
        (*(void(__thiscall**)(void*))(*(void***)obj + 0x34))(*p);

        if (entry->m1c == 0 || entry->mpJob != job) {
          DestroyRange_mw(scratch[0], scratch[1]);
          if (scratch[0] != 0 && ((int*)scratch[0])[-1] != 0)
            operator_delete__(scratch[0]);
          if (job != 0)
            job->Release();
          CModelWorld_ReleaseModel753270(model);
          return;
        }
        ++p;
      }
    }

    FinishBackgroundLoad_mw(self, entry);
    DestroyRange_mw(scratch[0], scratch[1]);
    if (scratch[0] != 0 && ((int*)scratch[0])[-1] != 0)
      operator_delete__(scratch[0]);
    if (job != 0)
      job->Release();
    CModelWorld_ReleaseModel753270(model);
    return;
  }

  if (job != 0)
    job->Release();
  if (model != 0) {
    if (model->m40 < 2)
      (*(void(__thiscall**)(MwModel_mw*, unsigned))(*(void***)model)[0x170 / 4])(model, model->m4 >> 0x1f);
    else
      --model->m40;
  }
}

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

// @ 0x00753630  (316 bytes) cLoadQueue lookup/start for a job's model chunks.
//
// Scans the queue's 8 fixed slots (0x50 stride at self+4) for a free one, or
// reuses the slot already bound to the incoming job, then dispatches any ready
// chunk range to the feedback-job starter and drains it with FUN_00753270.
struct QueueSlot_lq {
  void*   mpJob;    // +0x00
  char    pad04[0x18];
  uint8_t m1c;      // +0x1c occupied flag
};

struct ChunkRange_lq { int m[4]; };

extern "C" int  ChunkFind_lq(void* p, void* a, void* b);              // 0x00745560
extern "C" void StartFeedbackJobs_lq(void* self, void** range);       // 0x0074fea0
extern "C" void helper_50180_lq(void* dst, void* a);                  // 0x00750180

void FUN_00753630(void* self, void* param)
{
  char* base = (char*)self;
  for (;;) {
    // Phase 1: look for a free / matching slot among the 8 fixed ones.
    QueueSlot_lq* found = 0;
    do {
      void* job = *(void**)param;
      if (((*(uint32_t*)((char*)job + 4) >> 0xe) & 1) != 0 || found != 0) {
        // A job with the busy bit (or we already found a slot): try to start.
        if (((*(uint32_t*)((char*)job + 4) >> 0xe) & 1) == 0) {
          int range[4];
          int rc = ChunkFind_lq(&range[0], *(void**)(base + 0x28c),
                                    *(void**)(base + 0x29c));
          (void)rc;
          if (range[0] != *(int*)(base + 0x29c)) {
            StartFeedbackJobs_lq(found, (void**)range[0]);
            helper_50180_lq((char*)base + 0x284, &range[0]);
            FUN_00753270(*(void**)base, (LoadEntry_mw*)found);
          }
        }
        return;
      }

      QueueSlot_lq* slot = (QueueSlot_lq*)(base + 4);
      found = 0;
      for (unsigned i = 0; i < 8; ++i) {
        if (slot->m1c != 0 && slot->mpJob == job) {
          found = slot;
          break;
        }
        slot = (QueueSlot_lq*)((char*)slot + 0x50);
      }

      if (found == 0) {
        uint32_t n = *(uint32_t*)(base + 0x2b0);
        found = (QueueSlot_lq*)(base + 4 + n * 0x50);
        ++n;
        *(uint32_t*)(base + 0x2b0) = n;
        if (n >= 8)
          *(uint32_t*)(base + 0x2b0) = 0;
      }

      if (found->m1c == 0)
        break;
      FUN_00753270(*(void**)base, (LoadEntry_mw*)found);
      if (found->m1c == 0)
        break;
    } while (true);
  }
}

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

// @ 0x00753900  (678 bytes) SP::cModelWorld::cModelWorld (EH).
//
// Sets the multi-vtable header, constructs the cHierGrid at +0x118, three
// self-referential list heads at +0x19c/+0x1a4/+0x1ac, three EH vector blocks,
// the cLoadQueue at +0x314, and initialises the tuning scalars.
class cModelWorld_00753900 {
 public:
  cModelWorld_00753900(unsigned arg0, unsigned char arg1);

  char     pad00[0x04];     // +0x000
  void*    mvptr04;         // +0x004
  void*    mvptr08;         // +0x008
  void*    mvptr0c;         // +0x00c
  void*    mvptr10;         // +0x010
  uint32_t m14;             // +0x014
  uint32_t m18;             // +0x018
  uint8_t  m1c;             // +0x01c
  uint8_t  m1d;             // +0x01d
  uint8_t  m1e;             // +0x01e
  char     pad1f[0x01];     // +0x01f
  void*    m20;             // +0x020
  uint8_t  m24;             // +0x024
  char     pad25[0x118 - 0x25]; // +0x025
  char     m118[0x84];      // +0x118 cHierGrid (ends at +0x19c)
  // list heads
  void*    m19c_prev;       // +0x19c
  void*    m1a0_next;       // +0x1a0
  void*    m1a4_prev;       // +0x1a4
  void*    m1a8_next;       // +0x1a8
  void*    m1ac_prev;       // +0x1ac
  void*    m1b0_next;       // +0x1b0
  char     m1b4[8 * 0x20];  // +0x1b4 (8 x 0x20)
  float    m2b4;            // +0x2b4
  float    m2b8;            // +0x2b8
  uint32_t m2bc;            // +0x2bc
  uint32_t m2c0;            // +0x2c0
  uint32_t m2c4;            // +0x2c4
  char     pad2c8[0x2d0 - 0x2c8];
  uint32_t m2d0;            // +0x2d0
  uint32_t m2d4;            // +0x2d4
  uint32_t m2d8;            // +0x2d8
  uint32_t m2dc;            // +0x2dc
  uint32_t m2e0;            // +0x2e0
  char     pad2e4[0x2ec - 0x2e4];
  uint32_t m2ec;            // +0x2ec
  uint32_t m2f0;            // +0x2f0
  uint32_t m2f4;            // +0x2f4
  char     pad2f8[0x300 - 0x2f8];
  uint32_t m300;            // +0x300
  uint32_t m304;            // +0x304
  uint32_t m308;            // +0x308
  cLoadQueue_00753880 m314; // +0x314
  uint32_t m5c8;            // +0x5c8
  uint8_t  m5cc;            // +0x5cc
  char     m5d0[16 * 0x14]; // +0x5d0
  char     m710[16 * 0x14]; // +0x710
  float    m850;            // +0x850
  float    m854;            // +0x854
  float    m858;            // +0x858
  float    m85c;            // +0x85c
  float    m860;            // +0x860
  uint32_t m864;            // +0x864
  uint32_t m868;            // +0x868
  uint32_t m86c;            // +0x86c
  char     pad870[0x878 - 0x870];
  float    m878;            // +0x878
  float    m87c;            // +0x87c
  uint32_t m880;            // +0x880
  uint32_t m884;            // +0x884
  float    m888;            // +0x888
  float    m88c;            // +0x88c
  float    m890;            // +0x890
  uint32_t m894;            // +0x894
  uint32_t m898;            // +0x898
  uint32_t m89c;            // +0x89c
  uint32_t m8a0;            // +0x8a0
  uint32_t m8a4;            // +0x8a4
  uint32_t m8a8;            // +0x8a8
  uint32_t m8ac;            // +0x8ac
  uint8_t  m8b0;            // +0x8b0
  uint32_t m8b4;            // +0x8b4
};

extern "C" void cHierGrid_ctor_cw(void* p);                            // 0x00703ce0
extern "C" void __stdcall eh_vec_ctor_cw(void* p, unsigned sz, int n,
                                   void* ctor, void* dtor);                // 0x011e0b85
extern "C" void Small7_Init_cw(void* p);                               // 0x007453a0
extern "C" void Small7_Dtor_cw(void* p);                               // 0x007445a0
extern "C" void IPtrVec_Ctor_cw(void* p);                              // 0x006e5790
extern "C" void IPtrVec_Dtor_cw(void* p);                              // 0x0041e640
extern "C" void cLoadQueue_ctor_cw(void* p);                           // 0x00753880

extern float g_f1485720;   // 0x01485720 = 1.0
extern float g_f1470f1c;   // 0x01470f1c = 2.0
extern float g_f1473c70;   // 0x01473c70
extern float g_f1471064;   // 0x01471064 = 0.5
extern float g_f1486110;   // 0x01486110
extern float g_f1537b10, g_f1537b14, g_f1537b18, g_f1537b1c;

cModelWorld_00753900::cModelWorld_00753900(unsigned arg0, unsigned char arg1)
{
  mvptr04 = (void*)0x013f1ab0;   // cILayer vtable
  mvptr08 = (void*)0x013eb384;   // cListenerBase vtable
  mvptr0c = (void*)0x013f1ab0;
  mvptr10 = (void*)0x013ef094;   // hkReferencedObject vtable
  m14     = 0;
  m1e     = arg1;

  // Final vtables / model-world header.
  *(void**)this      = (void*)0x0140d790;
  mvptr04            = (void*)0x0140d780;
  mvptr08            = (void*)0x0140d770;
  mvptr0c            = (void*)0x0140d760;
  mvptr10            = (void*)0x0140d75c;
  m18                = arg0;
  m1c                = 0;
  m1d                = 0;
  m20                = 0;
  m24                = 1;

  cHierGrid_ctor_cw(m118);

  m19c_prev = &m19c_prev;  m1a0_next = &m19c_prev;
  m1a4_prev = &m1a4_prev;  m1a8_next = &m1a4_prev;
  m1ac_prev = &m1ac_prev;  m1b0_next = &m1ac_prev;

  eh_vec_ctor_cw(m1b4, 0x20, 8, (void*)Small7_Init_cw, (void*)Small7_Dtor_cw);

  m2b4 = 0.0f;
  m2b8 = g_f1485720;
  m2bc = 0;
  m2c0 = 0;
  m2c4 = 0;
  m2d0 = 0x3fffffff;
  m2d4 = 0x3fffffff;
  m2d8 = 0;
  m2dc = 0;
  m2e0 = 0;
  m2ec = 0;
  m2f0 = 0;
  m2f4 = 0;
  m300 = 0;
  m304 = 0;
  m308 = 0;

  cLoadQueue_ctor_cw(&m314);

  m5c8 = 0;
  m5cc = 0;
  eh_vec_ctor_cw(m5d0, 0x14, 0x10, (void*)IPtrVec_Ctor_cw, (void*)IPtrVec_Dtor_cw);
  eh_vec_ctor_cw(m710, 0x14, 0x10, (void*)IPtrVec_Ctor_cw, (void*)IPtrVec_Dtor_cw);

  m850 = g_f1537b10;
  m854 = g_f1537b14;
  m858 = g_f1537b18;
  m85c = g_f1537b1c;
  m860 = 0.0f;
  m864 = 0;
  m868 = 0;
  m86c = 0;
  m878 = g_f1470f1c;
  m87c = g_f1485720;
  m880 = 0;
  m888 = g_f1473c70;
  m88c = g_f1471064;
  m890 = g_f1486110;
  m894 = 0;
  m898 = 0;
  m89c = 0;
  m8a0 = 0;
  m8a4 = 0;
  m8a8 = 0;
  m8ac = 0;
  m8b0 = 0;
  m8b4 = 0;
  m884 = 0xc8;
}

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

// @ 0x00753e00  (383 bytes) load vertex attribute arrays from a property set.
//
// Three property arrays keyed 0x61b99cd/0x61b99ce/0x61b99cf are copied into a
// record array at stride 8: float at +0 (clamped/filled), byte at +5, and a
// split 3/3-bit pair at +4 (>>3) and +6 (&7).
struct ARec_ar {
  float  f0;    // +0x00
  uint8_t m4;   // +0x04
  uint8_t m5;   // +0x05
  uint8_t m6;   // +0x06
  char   pad7;  // +0x07
};

extern "C" char GetPropertyAsFloatArray_ar(void* obj, int key, int* count, float** out); // 0x006a08b0
extern "C" char GetPropertyAsIntArray_ar(void* obj, int key, int* count, void** out);    // 0x006a07d0

void FUN_00753e00(void* propSet, ARec_ar* dst, int n)
{
  {
    int    count;
    float* src;
    if (GetPropertyAsFloatArray_ar(propSet, 0x61b99cd, &count, &src)) {
      if (n < count)
        count = n;
      for (int i = 0; i < count; ++i)
        dst[i].f0 = src[i];
      for (int i = count; i < n; ++i)   // fill remainder from src[0]
        dst[i].f0 = src[0];
    }
  }
  {
    int    count;
    void*  src;
    if (GetPropertyAsIntArray_ar(propSet, 0x61b99ce, &count, &src)) {
      if (n < count)
        count = n;
      for (int i = 0; i < count; ++i)
        dst[i].m5 = *(uint8_t*)((char*)src + i * 4);
      for (int i = count; i < n; ++i)
        dst[i].m5 = *(uint8_t*)src;
    }
  }
  {
    int    count;
    void*  src;
    if (GetPropertyAsIntArray_ar(propSet, 0x61b99cf, &count, &src)) {
      if (n < count)
        count = n;
      for (int i = 0; i < count; ++i) {
        const int v = *(int*)((char*)src + i * 4);
        dst[i].m4 = (uint8_t)(v >> 3);
        dst[i].m6 = (uint8_t)(v & 7);
      }
      for (int i = count; i < n; ++i) {
        const int v = *(int*)src;
        dst[i].m4 = (uint8_t)(v >> 3);
        dst[i].m6 = (uint8_t)(v & 7);
      }
    }
  }
}

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

// @ 0x00753fe0  (301 bytes) build the RenderAsset/KDTree resource (EH).
//
// Local 4-element pointer array is EH-constructed; a resource of type 0x10 is
// created from the argument, then a KDTree object is allocated and handed to
// FUN_006c24b0, and its caching type is set to 2.
typedef void* (__thiscall* Fn762250_kd)(void* self, void* arg0);        // 0x00762250
extern "C" void* FUN_0072d5a0(void* a, int b, int c, int d, void* e);       // 0x0072d5a0
extern "C" void* FUN_00762250(void* a, void* b);                            // 0x00762250
extern "C" unsigned FUN_006c24b0_kd(void* a, void* b, void* c, int d,
                                        void* e, int f, const char* g);     // 0x006c24b0
extern "C" char SetCachingType_kd(int a, void* b);                      // 0x006ac040
extern "C" void __stdcall eh_vec_ctor_kd(void* p, unsigned sz, int n, void* ctor, void* dtor); // 0x011e0b85
extern "C" void __stdcall eh_vec_dtor_kd(void* p, unsigned sz, int n, void* dtor);             // 0x011e0b22
extern "C" void  BaseResourceDescriptor_ctor_kd(void* p);               // 0x006c0fa0
extern "C" void  ReadText_dtor_kd(void* p);                             // 0x00c2e4e0

struct KDTreeForeign_kd {
  virtual void kv0();
  virtual void kv1();
};

void FUN_00753fe0(void* param_1, void* param_2)
{
  // The original zeroes the first six dwords with individual stores; MSVC folds
  // any zero-init here into a memset whose stack cleanup it then mis-emits, so
  // leave the scratch block uninitialised and let the EH vector ctor below fill
  // the descriptor array at +0x18.
  char local[0x44];
  void* const arg_dst = param_1;   // snapshot args before any frame-shifting call
  void* const arg_src = param_2;

  eh_vec_ctor_kd((char*)local + 0x18, 8, 4, (void*)BaseResourceDescriptor_ctor_kd,
                     (void*)ReadText_dtor_kd);

  char* loc = (char*)local;
  void* res = (void*)FUN_0072d5a0(arg_src, 0, 0, 0x10, loc);
  if (res != 0) {
    void* mem = operator_new_753d10(0x4c, "Graphics", 0, 0, 0, 0);
    KDTreeForeign_kd* kd = 0;
    if (mem != 0)
      kd = (KDTreeForeign_kd*)((Fn762250_kd)FUN_00762250)((void*)mem, loc);
    if (kd != 0)
      (*(void(__thiscall**)(KDTreeForeign_kd*))(*(void***)kd)[0])(kd);

    FUN_006c24b0_kd(arg_dst, kd, loc, 1, loc, 1, "RenderAsset/KDTree");
    SetCachingType_kd(2, *(void**)arg_dst);
    if (kd != 0)
      (*(void(__thiscall**)(KDTreeForeign_kd*))(*(void***)kd)[1])(kd);
  }

  eh_vec_dtor_kd(loc + 0x18, 8, 4, (void*)ReadText_dtor_kd);
}

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
