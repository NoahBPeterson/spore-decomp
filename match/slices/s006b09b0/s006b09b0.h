#pragma once
// Shared stub declarations for slice s006b09b0 (App::LRUCache subsystem).
#include "types.h"

// 12-byte cache key.
struct Key12 { uint32_t a, b, c; };
// 16-byte cache entry: key + score.
struct Entry { uint32_t a, b, c, score; };

// Wrapper struct passed to the +0x60 member's update method (0x6b09b0).
struct Key20 { uint32_t mode, a, b, c, value; };

// --- vtable placeholder bases (slot N is virtual N) ---
struct Vt2  { virtual void v0(); virtual void v1(); };
struct Vt3  : Vt2  { virtual void v2(); };
struct Vt5  : Vt3  { virtual void v3(); virtual void v4(); };
struct Vt7  : Vt5  { virtual void v5(); virtual void v6(); };
struct Vt13 : Vt7  { virtual void v7(); virtual void v8(); virtual void v9();
                      virtual void v10(); virtual void v11(); virtual void v12(); };
struct Vt14 : Vt13 { virtual void v13(); };
struct Vt15 : Vt14 { virtual void v14(); };
struct Vt16 : Vt15 { virtual void v15(); };

// SP::PropertyManager object (slots 0x3c,0x40,0x44).
struct PropertyMgr : Vt15 {
  virtual void Call3c(int, void*);
  virtual void Call40(void*);
  virtual bool Call44(int, void*);
};
extern PropertyMgr* SP_PropertyManager();        // 0x0067de30

// Resource manager object (slot 0x14).
struct ResourceMgr : Vt5 {
  virtual bool Call14(void*, int);
};
extern ResourceMgr* ResourceMan_GetManager();    // 0x0067dcd0

// Callback with slot 0x40 (0x6b1000) / 0x38 (0x6b10a0), stream slots.
struct Callback40 : Vt16 { virtual void Call40(void*); };
struct Callback38 : Vt14 { virtual bool Call38(void*); };

// I/O stream (slots 0x1c,0x28,0x2c).
struct Stream : Vt7 {
  virtual uint32_t GetSize();                    // 0x1c
  virtual void s8(); virtual void s9();
  virtual bool SetPosition(int64_t, int);        // 0x28
  virtual uint32_t Get2();                       // 0x2c
};

// Reference-counted object (AddRef slot 1, Release slot 2, plus slots 0x18/0x24/0x34).
struct RefObj {
  virtual void v0();                    // 0x00
  virtual void AddRef();                // 0x04
  virtual void Release();               // 0x08
  virtual void v3(); virtual void v4(); virtual void v5();
  virtual void Call18();                // 0x18
  virtual void v7(); virtual void v8();
  virtual void Call24();                // 0x24
  virtual void v10(); virtual void v11(); virtual void v12();
  virtual bool Call34(int, void*, int, int, int);  // 0x34
};

// MemoryStream object used via AutoRefCount at +0x54.
struct MemStream {
  virtual void v0();
  virtual void AddRef();                // 0x04
  virtual void Release();               // 0x08
  void Ctor(const char* name);          // 0x0093bd50 (thiscall)
};

// Worker job object at +0x58 (direct thiscall methods).
struct Job {
  void m0(void*);                       // 0x692400
  void GetStatus();                     // 0x690120
};

// Allocator / free helpers (masked relocations).
extern void*  EAlloc(uint32_t, const char*, int, int, const char*, int);   // 0x00f473a0
extern void   EFree(void*);                                              // 0x00f47380
extern void   DoInsertValue(void*, Entry*, const Entry*);                // 0x007efb70 (thiscall)
extern void   Vec12DoInsertValue(void*, void*, void*);                   // 0x00425d30
extern bool   IO_ReadInt32(Stream*, void*, int, int);                    // 0x0093a780
extern bool   IO_ReadBytes(Stream*, void*, int, int);                    // 0x0093a800
extern void   MemStreamCtor(MemStream*, const char*);                    // 0x0093bd50
extern void   SetSomething(int, float);                                  // 0x0093bb40

// EASTL rbtree / intrusive-list helpers (masked).
struct Map {
  uint32_t r[7];
  void DoNukeSubtree(uint32_t);                     // 0x009a9600
  void Find(uint32_t* out, Key12* key);             // 0x00a05730
  void Insert(void* key, void* val, int tag);       // 0x006b0670
};
extern void  RBTreeIncrement(void*);                // 0x00921580
extern void  RBTreeErase(void*, void*);             // 0x00921880
extern void  ListRemove(void* node);                // 0x006afe40

// The +0x60 member of Cache (methods 0x6b0900 ctor, 0x6b09b0 update).
struct CacheSub60 {
  uint32_t pad[6];                                  // size 0x18
  void Init();                                      // 0x006b0900
  void Update(Key20*);                              // 0x006b09b0
};

// Vector-of-Entry subobject (lives at +0x10 of CacheList).
struct VectorBase {
  Entry* begin;   // 0x10
  Entry* end;     // 0x14
  Entry* cap;     // 0x18
  void DoInsertValue(Entry* pos, const Entry& val); // 0x007efb70
};

// Per-world cache node (class D) - `this` for 0x6b0b80/0f40/1000/10a0/1200.
struct CacheList {
  uint32_t m00;          // 0x00
  uint32_t m04;          // 0x04
  int64_t  total;        // 0x08
  VectorBase vec;        // 0x10..0x1b

  void AddOrUpdate(const Key12& k, uint32_t score);  // 0x6b0f40
  uint64_t Remove(const Key12& k);                   // 0x6b0b80
  uint64_t Flush(Callback40* cb);                    // 0x6b1000
  bool Load(Callback38* cb);                         // 0x6b10a0
  bool Read(Stream* s, uint32_t* p, uint64_t* q);    // 0x6b1200
  bool Read2(Stream* s);                             // 0x6b1200 helper
};

// The manager object (class C) - `this` for the remaining functions.
struct Cache {
  uint32_t vt0;          // 0x00
  uint32_t vt1;          // 0x04
  uint32_t refcnt;       // 0x08
  uint32_t m0c;          // 0x0c
  uint32_t m10;          // 0x10
  uint32_t m14;          // 0x14 (bytes m14,m15)
  uint32_t m18;          // 0x18
  uint32_t m1c, m20, m24, m28, m2c, m30;  // map 0x1c..0x33
  uint32_t nodeNext;     // 0x34
  uint32_t nodePrev;     // 0x38
  uint32_t m3c;          // 0x3c
  uint64_t m40;          // 0x40
  uint32_t m48, m4c;     // 0x48
  uint32_t capacity;     // 0x50
  RefObj*  stream;       // 0x54
  Job*     job;          // 0x58
  uint32_t m5c;          // 0x5c
  CacheSub60 sub;        // 0x60..0x77

  Cache(int a, int b);                               // 0x6b0c00
  void  A(Key12* e, int v);                          // 0x6b0ce0
  void  B(Key12* e);                                 // 0x6b0d20
  void  C(Key12* e);                                 // 0x6b0d60
  void** Insert(void** out, uint32_t key, uint64_t val); // 0x6b0da0
  void  Clear();                                     // 0x6b0e40
  void  Load();                                      // 0x6b14f0
  void  Refresh();                                   // 0x6b15b0
  bool  ReadStream(Stream* s);                       // 0x6b13b0
  void  Init();                                      // 0x6b17a0
  void  Shutdown();                                  // 0x6b1860
  uint32_t helper08a0(uint32_t, uint32_t);
  void  helper0670(void*, void*, int);
  void  helper0720(void*, uint32_t);
  void  helperafc40(uint32_t, uint32_t, uint32_t);
  void  helperafdd0();
  void  helperafe80();
};

extern Cache* Cache_Create(uint32_t a, uint32_t b);  // 0x6b0ed0

// EA tagged placement new used by the LRUCache factories.
void* operator new(uint32_t size, const char* name, int a, int b, int c, int d);
void  operator delete(void* p, const char* name, int a, int b, int c, int d);

