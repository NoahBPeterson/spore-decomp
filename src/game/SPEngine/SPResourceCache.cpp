// src/game/SPEngine/SPResourceCache.cpp -- migrated from slice(s) s006b18c0, s006b09b0 by tools/migrate/rewrite.py
// Object file: SPEngine/SPResourceCache.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cJob.h"

// unnamed retail callees and globals (address in the comment)
extern void*  EAlloc(uint32_t, const char*, int, int, const char*, int);   // 0x00f473a0
extern void   SetSomething(int, float);                                  // 0x0093bb40

// ---- items of slice s006b09b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Key12 { uint32_t a, b, c; };
struct Key20 { uint32_t mode, a, b, c, value; };
struct Vt2  { virtual void v0(); virtual void v1(); };
struct Vt3  : Vt2  { virtual void v2(); };
struct Vt5  : Vt3  { virtual void v3(); virtual void v4(); };
struct Vt7  : Vt5  { virtual void v5(); virtual void v6(); };
struct Stream : Vt7 {
  virtual uint32_t GetSize();                    // 0x1c
  virtual void s8(); virtual void s9();
  virtual bool SetPosition(int64_t, int);        // 0x28
  virtual uint32_t Get2();                       // 0x2c
};
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
struct MemStream {
  virtual void v0();
  virtual void AddRef();                // 0x04
  virtual void Release();               // 0x08
  void Ctor(const char* name);          // 0x0093bd50 (thiscall)
};
struct Job {
  void m0(void*);                       // 0x692400
  void GetStatus();                     // 0x690120
};
extern void*  EAlloc(uint32_t, const char*, int, int, const char*, int);   // 0x00f473a0
extern void   SetSomething(int, float);                                  // 0x0093bb40
struct CacheSub60 {
  uint32_t pad[6];                                  // size 0x18
  void Init();                                      // 0x006b0900
  void Update(Key20*);                              // 0x006b09b0
};
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
// ---- items of slice s006b09b0 end

// ---- items of slice s006b18c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
// ---- items of slice s006b18c0 end

// @ 0x006b0ce0
void Cache::A(Key12* e, int v)
{
  Key20 t;
  t.a = e->a;
  t.b = e->b;
  t.c = e->c;
  t.mode = 1;
  t.value = v;
  sub.Update(&t);
}

// @ 0x006b0d20
void Cache::B(Key12* e)
{
  Key20 t;
  t.mode = 0;
  t.a = e->a;
  t.b = e->b;
  t.c = e->c;
  t.value = 0;
  sub.Update(&t);
}

// @ 0x006b0d60
void Cache::C(Key12* e)
{
  Key20 t;
  t.mode = 2;
  t.a = e->a;
  t.b = e->b;
  t.c = e->c;
  t.value = 0;
  sub.Update(&t);
}

// @ 0x006b17a0
void Cache::Init()
{
  MemStream* s = (MemStream*)EAlloc(0x24, "App/LRUCache/MemoryStream", 0, 0, 0, 0);
  if (s != 0) {
    s->Ctor("LRUCache/MemoryStream");
  } else {
    s = 0;
  }
  if (s != (MemStream*)stream) {
    if (s != 0) {
      s->AddRef();
    }
    MemStream* old = (MemStream*)stream;
    stream = (RefObj*)s;
    if (old != 0) {
      old->Release();
    }
  }
  SetSomething(1, 1.0f);
  Load();
  Refresh();
  helperafdd0();
  ((uint8_t*)this)[0x14] = 1;
  ((uint8_t*)this)[0x15] = 0;
}

// @ 0x006b1860
void Cache::Shutdown()
{
  ((uint8_t*)this)[0x14] = 0;
  if (job != 0) {
    job->m0((void*)1);
    if (job != 0) {
      Job* j = job;
      job = 0;
      j->GetStatus();
    }
    ((uint8_t*)this)[0x15] = 1;
  }
  if (((uint8_t*)this)[0x15] != 0) {
    helperafdd0();
    helperafe80();
  }
  Clear();
  RefObj* s = stream;
  if (s != 0) {
    stream = 0;
    s->Release();
  }
}

// @ 0x006b1b80
void CacheMgr::Update()
{}
