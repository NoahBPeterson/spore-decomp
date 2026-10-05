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
extern SaveAreaMap g_saveAreas;
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
struct Sub60 { void Init(); void Update(void*); };
struct CacheMgr {
  uint32_t vt0, vt1;
  uint32_t refcnt;
  uint32_t m0c;
  uint32_t m10;
  uint32_t m14;
  uint32_t m18, m1c, m20, m24, m28, m2c, m30;
  uint32_t nodeNext, nodePrev, m3c;
  uint64_t m40;
  uint32_t m48, m4c;
  uint32_t capacity;
  void*    stream;
  void*    job;
  uint32_t m5c;
  Sub60    sub;

  void Notify(void* ev);                    // 0x6b18c0
  void ReleaseArea(void* node);             // 0x6b19e0
  void Destructor();                        // 0x6b1ab0
  void Update();                            // 0x6b1b80
};
extern uint32_t FUN_006b0300(void*, void*);     // 0x006b0300
extern void  FUN_006b10a0c(void*, void*);
extern void  FUN_006afe40c(void*, void*);

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
