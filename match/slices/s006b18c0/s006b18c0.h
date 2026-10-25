#pragma once
// Stub declarations for slice s006b18c0 (SP save-area subsystem).
#include "types.h"

// ---- global eastl rbtree of save areas (base 0x0152fdc4) ----
struct SaveAreaMap {
  uint32_t  f0;       // +0x00
  uint32_t  head;     // +0x04  (sentinel address 0x0152fdc8)
  uint32_t* root;     // +0x08  (0x0152fdcc)
  uint32_t  f3;       // +0x0c
  void find(void** out, const uint32_t* key);   // 0x00e5c780 (thiscall)
};
extern SaveAreaMap g_saveAreas;                 // 0x0152fdc4
extern "C" void* RBTreeIncrement(void*);        // 0x00921580

// ---- vtable stubs ----
struct PropertyMgr4 {
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
  virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
  virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
  virtual void v12();
  virtual void Call34(void*, void*, void*);     // slot 13 (0x34)
};
extern PropertyMgr4* SP_PropertyManager();      // 0x0067de30

struct ResourceMgr4 {
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
  virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
  virtual uint32_t Call20(void*, void*, void*, void*, void*);  // slot 8 (0x20)
  virtual void v9(); virtual void v10(); virtual void v11();
  virtual int Call30(void*, void*, void*);      // slot 12 (0x30)
  virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16();
  virtual void v17(); virtual void v18(); virtual void v19();
  virtual bool Call50(int a, void* p, int b);   // slot 20 (0x50)
};
extern ResourceMgr4* ResourceMan_GetManager();  // 0x0067dcd0

struct SaveObj {
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
  virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
  virtual void v8();
  virtual void Call24();                        // slot 9 (0x24)
  virtual void v10(); virtual void v11(); virtual void v12();
  virtual bool Call34(void*, void*, void*, void*, void*, void*); // slot 13
};

// ---- free helpers (masked) ----
extern void  FUN_006acfe0(void*, void*);        // 0x006acfe0
extern uint32_t FUN_006b4b60(void*, void*, int, int);  // 0x006b4b60
extern uint8_t g_16046d8;

// ---- manager object (App::LRUCache) used by 0x6b18c0..0x6b1b80 ----
struct Key12 { uint32_t a, b, c; };
struct Entry { uint32_t a, b, c, score; };
struct ListVec {
  Entry* begin;   // +0x10
  Entry* end;     // +0x14
  Entry* cap;     // +0x18
  void DoInsertValue(Entry*, const Entry&);
};
struct Job {                                    // SP::cJob
  void*    mpFunc;      // +0x00
  void*    mpOwner;     // +0x04
  uint32_t m08;         // +0x08
  uint32_t m0c;         // +0x0c
  uint32_t m10;         // +0x10
  uint32_t m14;         // +0x14
  uint32_t m18;         // +0x18 job kind
  int  ContinueJob();                           // 0x0068f970
  void Release();                               // 0x00690120
  int  GetStatus();                             // 0x006909b0
};
extern void gJobFunc(void);                     // 0x006b0890 cache-manager job entry
struct DirectPropertyList {                     // SP::cDirectPropertyList
  int GetIntProperty(uint32_t key);             // 0x006a2660
};
struct Tracer {                                 // 0x0068f4d0 hands one out per update
  virtual void s0(); virtual void s4(); virtual void s8(); virtual void sc();
  virtual bool CheckJob(Job** slot);            // +0x10
  virtual void s14(); virtual void s18(); virtual void s1c();
  virtual void Enter();                         // +0x20
  virtual void Exit();                          // +0x24
};
struct StreamVt {                               // stream object at +0x54
  virtual void s0(); virtual void s4();
  virtual void Release();                       // +0x08
};
struct Sub60 {                                  // event source at +0x60
  void Free();                                  // 0x006b02b0
  bool Poll(struct CacheEvent* ev);             // 0x006b0300
};

// ---- per-key resource record reached through the list node's payload ----
struct AreaRec;
struct ListNode {                               // intrusive list node (sentinel at CacheMgr+0x34)
  ListNode* mpNext;                             // +0x00
  ListNode* mpPrev;                             // +0x04
  AreaRec*  mpValue;                            // +0x08
};
struct AreaRec {
  uint32_t m00;         // +0x00 key low
  uint32_t m04;         // +0x04 key high
  uint32_t m08;         // +0x08
  uint32_t m0c;         // +0x0c
  void*    mpBuf;       // +0x10 owned buffer
  void*    mpStream;    // +0x14
  uint64_t SizeTaken(void* owner);              // 0x006b1000
  uint64_t AddFromStream(int* ev);              // 0x006b0b80
  uint64_t AddFromEvent(int* ev, uint32_t v);   // 0x006b0f40
  bool     CanRelease(void* owner);             // 0x006b10a0
};
struct AreaMapNode {                            // map node holding the ListNode*
  uint32_t m00, m04, m08, m0c, m10, m14;
  void*    mpValue;                             // +0x18
};
struct Key8 { uint32_t lo; uint32_t hi; };
struct AreaMap {                                // eastl::map<Key8, ListNode*> at CacheMgr+0x18
  uint32_t m00;         // +0x00
  uint32_t head;        // +0x04 sentinel node base
  uint32_t m08;         // +0x08
  uint32_t m0c;         // +0x0c
  uint32_t m10;         // +0x10
  uint32_t size;        // +0x14 element count
  void find(void** out, const Key8* key);       // 0x00a05730
  void Clear(uint32_t node);                    // 0x009a9600 eastl rbtree DoNukeSubtree
};
struct CacheEvent {
  uint32_t op;          // +0x00 0 = touch, 1 = event value, 2 = stream value
  uint32_t lo;          // +0x04 key low
  uint32_t m08;         // +0x08 unused by the dispatch
  uint32_t hi;          // +0x0c key high (flags word, masked into the key)
  uint32_t extra;       // +0x10 value handed to the area helper
};
struct OwnerRef { virtual void AddRef(); virtual void Release(); };   // refcount subobject at owner+4
struct OwnerObj { uint32_t pad0; OwnerRef ref; };

struct CacheMgr {
  uint32_t vt0;         // +0x00
  uint32_t vt1;         // +0x04
  void*    mpOwner;     // +0x08 refcounted owner (Release through +0x0c)
  void*    m0c;         // +0x0c owner handle handed to the area helpers
  uint32_t m10;         // +0x10 property key
  uint8_t  mb14;        // +0x14 started
  uint8_t  mb15;        // +0x15 needs a job
  uint16_t mb16;        // +0x16
  AreaMap  map;         // +0x18 .. +0x2f
  uint32_t m30;         // +0x30
  ListNode list;        // +0x34 sentinel
  uint64_t m40;         // +0x40 bytes held
  uint64_t mLimit;      // +0x48 byte budget
  uint32_t m50;         // +0x50 countdown (9000)
  void*    stream;      // +0x54
  Job*     job;         // +0x58
  Sub60    sub;         // +0x60

  void Shutdown();                      // 0x006b1860
  void Touch(ListNode* it);             // 0x006afe40
  void StartJob();                      // 0x006afdd0
  void* InsertKey(void** out, uint32_t lo, uint32_t hi);  // 0x006b0da0
  void Notify(CacheEvent* ev);          // 0x6b18c0
  void ReleaseArea(ListNode* it);       // 0x6b19e0
  void Destructor();                    // 0x6b1ab0
  void Update();                        // 0x6b1b80
};
extern char gVtblCacheMgrA;             // 0x014096c4
extern char gVtblCacheMgrB;             // 0x014096c0
extern char gVtblCacheMgrBaseA;         // 0x013eb938 (EA::Trace::ITracerBase)
extern char gVtblCacheMgrBaseB;         // 0x013ef094 (hkReferencedObject)
extern DirectPropertyList* g_pDirectPropertyList;   // 0x015fd918
extern "C" void RBTreeErase(void*, void*);      // 0x00921880
extern void EAFree(void* p);                    // 0x00f47380
extern Tracer* FUN_0068f4d0();                  // 0x0068f4d0
extern "C" long long __allmul(int, int, int, int);   // 0x011e0a90

// ---- AutoRefCount pair used at 0x6b1dc0..0x6b1ef0 ----
struct RefVt { virtual void AddRef(); virtual void Release(); };
struct RefA { uint32_t pad0; RefVt ref; };       // polymorphic subobject at +0x4
struct RefB { virtual void AddRef(); virtual void Release(); };
struct RefPair {
  RefA* a;
  RefB* b;
  RefPair* Ctor(RefA* x, RefB* y);               // 0x6b1dc0
  void     Dtor();                               // 0x6b1e20
  RefPair* CtorCopy(const RefPair* o);           // 0x6b1e90
  RefPair* Assign(const RefPair* o);             // 0x6b1ef0
};
