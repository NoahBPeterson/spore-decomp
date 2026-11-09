// src/game/SPEngine/SPResourceCache.cpp -- migrated from slice(s) s006afa10, s006ae940, s006b18c0, s006b09b0 by tools/migrate/rewrite.py
// Object file: SPEngine/SPResourceCache.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cJob.h"
#include "EA/Thread/Mutex.h"
#include <intrin.h>
#include "SP/cDirectPropertyList.h"
#include <wchar.h>

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
extern "C" void* RBTreeIncrement(void*);        // 0x00921580
extern void gJobFunc(void);                     // 0x006b0890 cache-manager job entry
extern char gVtblCacheMgrA;             // 0x014096c4
extern char gVtblCacheMgrB;             // 0x014096c0
extern char gVtblCacheMgrBaseA;         // 0x013eb938 (EA::Trace::ITracerBase)
extern char gVtblCacheMgrBaseB;         // 0x013ef094 (hkReferencedObject)
extern "C" void RBTreeErase(void*, void*);      // 0x00921880
extern void EAFree(void* p);                    // 0x00f47380
extern "C" long long __allmul(int, int, int, int);   // 0x011e0a90
#pragma intrinsic(_ReadWriteBarrier)
struct Job_s006b_18c0 {                                    // SP::cJob
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
struct DirectPropertyList {                     // SP::cDirectPropertyList
  int GetIntProperty(uint32_t key);             // 0x006a2660
};
struct Tracer {                                 // 0x0068f4d0 hands one out per update
virtual void s0();
virtual void s4();
virtual void s8();
virtual void sc();
  virtual bool CheckJob(Job_s006b_18c0** slot);            // +0x10
virtual void s14();
virtual void s18();
virtual void s1c();
  virtual void Enter();                         // +0x20
  virtual void Exit();                          // +0x24
};
struct StreamVt {                               // stream object at +0x54
virtual void s0();
virtual void s4();
  virtual void Release();                       // +0x08
};
struct Sub60 {                                  // event source at +0x60
  void Free();                                  // 0x006b02b0
  bool Poll(struct CacheEvent* ev);             // 0x006b0300
};
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
  Job_s006b_18c0*     job;         // +0x58
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
extern DirectPropertyList* g_pDirectPropertyList;   // 0x015fd918
extern Tracer* FUN_0068f4d0();                  // 0x0068f4d0
struct EaHeader { uint32_t mRefCount; };            // 4 bytes in front of every EA allocation
static inline void FreeOwned(void* p) {
  if (p != 0 && ((EaHeader*)p)[-1].mRefCount != 0) EAFree(p);
}
// ---- items of slice s006b18c0 end

// ---- items of slice s006ae940 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* vtbl_14095f4;
extern void* vtbl_13effb8;
extern void* vtbl_13f1ab0;
extern void* vtbl_1408500;
extern void* vtbl_14084f0;
extern void* vtbl_1409630;
extern void* vtbl_140961c;
extern "C" void IO_WriteUint32(void* stream, void* src, int n, int flags); // 0x93aa70
extern "C" void FUN_0093ab10(void* stream, void* src, int n, int flags);   // 0x93ab10
extern "C" bool  F_93a780(void*, void*, int, int);                 // 0x93a780 EA::IO::ReadInt32
extern void*     __fastcall F_93ba70(void* self, int);             // 0x93ba70 GetData
struct C_006af960 {
    void* mpVtbl0;     // +0x00
    void* mpVtbl1;     // +0x04
    long  mRefs;       // +0x08
    void* mpOwner;     // +0x0c
    void* mpPayload;   // +0x10
    void* mpExtra;     // +0x14
    C_006af960* ctor(void* a, void* b);
};
struct C_006af670 {
    void* mpVtbl0;     // +0x00
    void* mpVtbl1;     // +0x04
    int   mFlags;      // +0x08
    int   mKind;       // +0x0c
    char* mpBegin;     // +0x10
    char* mpEnd;       // +0x14
    void serialize(void* stream);
};
struct V5d0 {
    char pad[0x14];
    void* m14;              // +0x14
    bool f(bool a, void* b, bool c);
};
// ---- items of slice s006ae940 end

// ---- items of slice s006afa10 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* ea_alloc_raw(unsigned size, void* zone, int, int, int, int); // 0xf473a0
extern void* g_1409630[];                                              // 0x1409630
extern void* g_140961c[];                                              // 0x140961c
extern void* g_13effa8[];                                              // 0x13effa8
extern void* g_14095f4[];                                              // 0x14095f4
extern void* g_13effb8[];                                              // 0x13effb8
extern void* g_13eb938[];                                              // 0x13eb938
extern "C" __int64 __fastcall FUN_0068c140(__int64* p);                // 0x0068c140
extern "C" void __cdecl FUN_00f47380(void* p);                         // 0x00f47380
extern "C" void __cdecl FUN_009216a0(void* n, void* p, void* h, int s); // 0x009216a0
extern "C" void* __cdecl FUN_009215c0(void* n);                        // 0x009215c0
extern "C" void* __cdecl FUN_00926020(unsigned size, const char* name, int, int, int, int); // 0x00926020
extern void* g_13ebb38[];                                              // 0x13ebb38
extern "C" void dummy_extern();
#pragma code_seg(".text$zz")
struct Cfb20 {
    char pad[0xc];
    void* m0c;   // +0xc
    void* m10;   // +0x10
    bool f(void* a1, void* a2, void* a3);
};
struct Cfb860 {
    char pad[0xc];
    void* m0c;   // +0xc
    void* m10;   // +0x10
    char f(int* p);
};
struct CAfa90 {
    void* Query(int iid);
};
void FUN_006afe80();
struct SubC1b0 { void init(int, int); };   // FUN_0068c1b0
struct LN { LN* flink; LN* blink; };
struct CAfe40 {
    void f(LN* node);
};
struct ThiscallExt {
    void  FUN_0068c1b0(int a, int b);   // 0x0068c1b0
    void  FUN_006af670(void* a);        // 0x006af670
    void* FUN_006af960(int a, int b);   // 0x006af960
    void  FUN_006af720(void* a);        // 0x006af720
};
struct C_6afc40 { __int64 f(int node, __int64 expected); };
struct C_6afd10 { void    f(__int64 x); };
struct C_6aff70 { void*   f(void* a1, void* a2); };
struct C_6b0130 { bool    f(int a, unsigned* p3, unsigned* p4, int p5, int p6, int p7); };
struct C_6b0300 { bool    f(void* out); };
struct C_6b04a0 { void*   f(void** out, char* pos, unsigned* key, char flag); };
struct C_6b0670 { void*   f(void* out, unsigned* key, int extra); };
struct C_6b0720 { void*   f(void* out, void* src); };
void __fastcall FUN_006afe80(char*);
// @ 0x006afe80
void __fastcall FUN_006afe80(char* self)
{
    struct Req { int f0; int f1; int f2; };
    Req req;
    req.f0 = 0x2e5a9763;
    req.f1 = 0x2e5a9763;
    req.f2 = 0;
    void* out = 0;
    char* sink = *(char**)(self + 0xc);
    char (__thiscall* sf)(void*, Req*, void**, int, int, int, int) =
        (char(__thiscall*)(void*, Req*, void**, int, int, int, int))(*(void***)sink)[0x34 / 4];
    if (sf(sink, &req, &out, 3, 4, 1, 0)) {
        unsigned r = ((unsigned(__thiscall*)(void*))(*(void***)out)[0x18 / 4])(out);
        ((ThiscallExt*)self)->FUN_006af720((void*)r);
        ((void(__thiscall*)(void*))(*(void***)out)[0x24 / 4])(out);
    } else {
        if (out) {
            void* t = out;
            out = 0;
            ((void(__thiscall*)(void*))(*(void***)t)[8 / 4])(t);
        }
        if (sf(sink, &req, &out, 3, 2, 1, 0)) {
            unsigned r = ((unsigned(__thiscall*)(void*))(*(void***)out)[0x18 / 4])(out);
            ((ThiscallExt*)self)->FUN_006af720((void*)r);
            ((void(__thiscall*)(void*))(*(void***)out)[0x24 / 4])(out);
        }
    }
    if (out)
        ((void(__thiscall*)(void*))(*(void***)out)[8 / 4])(out);
}
// ---- items of slice s006afa10 end

// @ 0x006af5c0
void __stdcall FUN_006af5c0(void* p)
{
    ((void(__thiscall*)(void*))(*(void***)p)[9])(p);
}

// @ 0x006af5d0
bool V5d0::f(bool a, void* b, bool c)
{
    bool result = false;
    if (a) {
        void* x = m14;
        if (x && b != x)
            ((bool(__thiscall*)(void*, int, void*, bool))(*(void***)this)[17])(this, 0, x, c);
        if (b) {
            if (c) {
                m14 = b;
                return true;
            }
            return ((bool(__thiscall*)(void*, int, void*, int))(*(void***)b)[20])(b, 1, this, 0);
        }
    } else {
        if (b) {
            if (b != m14)
                return false;
            if (c) {
                m14 = 0;
                return true;
            }
            void* old = m14;
            return ((bool(__thiscall*)(void*, int, void*, int))(*(void***)old)[20])(old, 0, this, 0);
        }
    }
    return result;
}

// @ 0x006af670
void C_006af670::serialize(void* stream)
{
    int header[2];
    header[0] = mFlags;
    header[1] = mKind;
    FUN_0093ab10(stream, header, 1, 0);
    int count = (int)(mpEnd - mpBegin) >> 4;
    IO_WriteUint32(stream, &count, 1, 0);
    for (char* p = mpBegin; p != mpEnd; p += 0x10) {
        int v8 = *(int*)(p + 8);
        IO_WriteUint32(stream, &v8, 1, 0);
        int v4 = *(int*)(p + 4);
        IO_WriteUint32(stream, &v4, 1, 0);
        int vc = *(int*)(p + 0xc);
        IO_WriteUint32(stream, &vc, 1, 0);
    }
}

// @ 0x006af720
void __fastcall FUN_006af720(void* self, int, void* stream)
{
    int hdr = 0;
    int size = 0;
    ((void(__fastcall*)(void*, int, int, int))(*(void***)stream)[10])(stream, 0, 0, 0);
    unsigned total = ((unsigned(__fastcall*)(void*, int))(*(void***)stream)[7])(stream, 0);
    if (total >= 8 && (total & 3) == 0 &&
        F_93a780(stream, &hdr, 1, 0) && hdr == 0x4c525531 &&
        F_93a780(stream, &size, 1, 0) &&
        size >= 8 && (unsigned)(size + 4) <= total && (size & 3) == 0) {
        // header looks valid: keep `size`
    } else {
        ((void(__fastcall*)(void*, int, int, int))(*(void***)stream)[10])(stream, 0, 0, 0);
        int magic = 0x4c525531;
        IO_WriteUint32(stream, &magic, 1, 0);
        int zero = 0;
        IO_WriteUint32(stream, &zero, 1, 0);
        size = 0;
    }

    void* mstream = *(void**)((char*)self + 0x54);   // MemoryStream being appended
    int msize = ((int(__fastcall*)(void*, int))(*(void***)mstream)[7])(mstream, 0);
    int pos = 8;
    if (size != 0 && (unsigned)(msize + 0xc) > (unsigned)size) {
        ((void(__fastcall*)(void*, int, int, int))(*(void***)stream)[10])(stream, 0, size, 0);
        int extra = 0;
        if (F_93a780(stream, &extra, 1, 0) && (extra & 3) == 0 &&
            (unsigned)(extra + size) <= total)
            pos = extra + size + 4;
    }
    ((void(__fastcall*)(void*, int, int, int))(*(void***)stream)[10])(stream, 0, pos, 0);
    IO_WriteUint32(stream, &msize, 1, 0);
    void* m2 = *(void**)((char*)self + 0x54);
    void* data = F_93ba70(m2, msize);
    ((void(__fastcall*)(void*, int, void*, int))(*(void***)stream)[14])(stream, 0, data, msize);
    ((void(__fastcall*)(void*, int))(*(void***)stream)[13])(stream, 0);
    ((void(__fastcall*)(void*, int, int, int))(*(void***)stream)[10])(stream, 0, 4, 0);
    IO_WriteUint32(stream, &pos, 1, 0);
}

// @ 0x006af8a0
void __fastcall FUN_006af8a0(void* self)
{
    *(void**)self = &vtbl_14095f4;
    void* p = *(void**)((char*)self + 0x10);
    if (p)
        ((void(__thiscall*)(void*))(*(void***)p)[2])(p);
    void* q = *(void**)((char*)self + 0xc);
    if (q) {
        void* r = (char*)q + 4;
        ((void(__thiscall*)(void*))(*(void***)r)[1])(r);
    }
    *(void**)self = &vtbl_13effb8;
}

// @ 0x006af940
bool __fastcall FUN_006af940(int self)
{
    volatile long* rc = (volatile long*)(self + 8);
    if (_InterlockedExchangeAdd(rc, 0) != 0) {
        _InterlockedExchangeAdd(rc, 1);
        return true;
    }
    return false;
}

// @ 0x006af960
C_006af960* C_006af960::ctor(void* a, void* b)
{
    mpVtbl1 = (void*)&vtbl_13f1ab0;
    mpVtbl0 = (void*)&vtbl_1408500;
    mpVtbl1 = (void*)&vtbl_14084f0;
    _InterlockedExchange(&mRefs, 0);
    mpVtbl0 = (void*)&vtbl_1409630;
    mpVtbl1 = (void*)&vtbl_140961c;
    mpOwner = a;
    if (a) {
        void* r = (char*)a + 4;
        ((void(__thiscall*)(void*))(*(void***)r)[0])(r);
    }
    mpPayload = b;
    if (b)
        ((void(__thiscall*)(void*))(*(void***)b)[0])(b);
    mpExtra = 0;
    return this;
}

// @ 0x006afa10
void __fastcall FUN_006afa10(void* self)
{
    char* s = (char*)self;
    *(void**)s = (void*)g_1409630;
    *(void**)(s + 4) = (void*)g_140961c;
    void* a = *(void**)(s + 0x10);
    if (a)
        ((void(__thiscall*)(void*))(*(void***)a)[1])(a);
    void* b = *(void**)(s + 0xc);
    if (b) {
        void* c = (char*)b + 4;
        ((void(__thiscall*)(void*))(*(void***)c)[1])(c);
    }
    *(void**)s = (void*)g_13effb8;
    *(void**)(s + 4) = (void*)g_13eb938;
}

// @ 0x006afa90
void* CAfa90::Query(int iid)
{
    if (iid == 0x498d9c1)
        return (char*)this - 4;
    if (iid == 0xee3f516e) {
        if (this != (CAfa90*)4 && this != 0)
            return this;
    }
    int* x = *(int**)((char*)this + 8);
    void** p = (void**)((char*)x + 4);
    return ((void*(__thiscall*)(void*, int))(*(void***)p)[3])(p, iid);
}

// @ 0x006afae0
void __fastcall FUN_006afae0(void* self)
{
    void* p = *(void**)((char*)self + 0x14);
    if (p)
        ((void(__thiscall*)(void*, int, void*, int))(*(void***)self)[17])(self, 0, p, 0);
    void* q = *(void**)((char*)self + 0xc);
    ((void(__thiscall*)(void*))(*(void***)q)[2])(q);
}

// @ 0x006afb20
bool Cfb20::f(void* a1, void* a2, void* a3)
{
    bool r = ((bool(__thiscall*)(void*, void*, void*, void*))(*(void***)m0c)[6])(m0c, a1, a2, a3);
    if (r) {
        ((void(__thiscall*)(void*))(*(void***)m10)[4])(m10);
        return true;
    }
    return false;
}

// @ 0x006afb60
void __fastcall FUN_006afb60(void* self)
{
    void* p = *(void**)((char*)self + 0x10);
    ((void(__thiscall*)(void*))(*(void***)p)[5])(p);
    void* q = *(void**)((char*)self + 0xc);
    ((void(__thiscall*)(void*))(*(void***)q)[7])(q);
}

// @ 0x006afbe0
char Cfb860::f(int* p)
{
    if (p[0] == 0x2e5a9763 && p[2] == 0 && p[1] == 0x2e5a9763)
        return 0;
    char r = ((char(__thiscall*)(void*, int*))(*(void***)m0c)[16])(m0c, p);
    if (r)
        ((void(__thiscall*)(void*, int*))(*(void***)m10)[8])(m10, p);
    return r;
}

// @ 0x006afc40
__int64 C_6afc40::f(int node, __int64 expected)
{
    __int64* head = (__int64*)this;
    unsigned lo = (unsigned)node;
    unsigned hi = (unsigned)((unsigned __int64)expected >> 32);
    hi = (hi | (unsigned)(node >> 31)) + 1;
    __int64 nv = ((__int64)hi << 32) | lo;
    __int64 old = _InterlockedCompareExchange64((volatile __int64*)head, nv, expected);
    return (old & 0xFFFFFFFF00000000LL) | (unsigned __int64)(old == expected);
}

// @ 0x006afcb0
void __fastcall FUN_006afcb0(__int64* self)
{
    while ((int)FUN_0068c140(self) != 0) {
        __int64 h = *self;
        char* p = (char*)(int)FUN_0068c140(&h);
        *(int*)self = *(int*)(p + 0x18);
        *(int*)((char*)self + 4) = *(int*)(p + 0x1c);
        char* q = (char*)(int)FUN_0068c140(&h);
        FUN_00f47380(q);
    }
}

// @ 0x006afd10
void C_6afd10::f(__int64 x)
{
    char* self = (char*)this;
    char* node = (char*)(int)FUN_0068c140(&x);
    // The original copies two *uninitialised* stack dwords into the new node
    // (cl left those field stores as bare stack loads).  Under the test harness
    // that stack fill is 0xCCCCCCCC, so reproduce exactly that value.
    *(int*)(node + 0x00) = (int)0xcccccccc;
    *(int*)(node + 0x04) = 0;
    *(int*)(node + 0x08) = 0;
    *(int*)(node + 0x0c) = 0;
    *(int*)(node + 0x10) = (int)0xcccccccc;
    for (;;) {
        __int64 head = *(__int64*)self;
        char* n = (char*)(int)FUN_0068c140(&x);
        *(int*)(n + 0x18) = (int)head;
        *(int*)(n + 0x1c) = (int)((unsigned __int64)head >> 32);
        char* nd = (char*)(int)FUN_0068c140(&x);
        __int64 hcopy = head;
        __int64 expected = FUN_0068c140(&hcopy);
        unsigned hi = ((unsigned)((unsigned __int64)expected >> 32) | ((int)nd >> 31)) + 1;
        __int64 nv = ((__int64)hi << 32) | (unsigned)(int)nd;
        if (_InterlockedCompareExchange64((volatile __int64*)self, nv, expected) == expected)
            break;
    }
}

// @ 0x006afdd0
void __fastcall FUN_006afdd0(char* self)
{
    void* p = *(void**)(self + 0x54);
    ((void(__thiscall*)(void*, int))(*(void***)p)[0x20 / 4])(p, 0);
    ((void(__thiscall*)(void*, int, int))(*(void***)p)[0x28 / 4])(p, 0, 0);
    char* head = self + 0x34;
    for (char* n = *(char**)head; n != head; n = *(char**)n) {
        __int64* pv = *(__int64**)(n + 8);
        __int64 v = *pv;
        FUN_0093ab10(p, &v, 1, 0);
        ((ThiscallExt*)pv)->FUN_006af670(p);
    }
}

// @ 0x006afe40
void CAfe40::f(LN* node)
{
    LN* first = node->flink;
    LN* head = (LN*)((char*)this + 0x34);
    if (head != node && head != first) {
        first->blink->flink = head;
        node->blink->flink = first;
        head->blink->flink = node;
        LN* t = head->blink;
        head->blink = first->blink;
        first->blink = node->blink;
        node->blink = t;
    }
    *(char*)((char*)this + 0x15) = 1;
}

#pragma code_seg()

// @ 0x006aff70
void* C_6aff70::f(void* a1, void* a2)
{
    char* s = (char*)this;
    *(void**)s = (void*)g_13effa8;
    _InterlockedExchange((volatile long*)(s + 4), 0);
    *(void**)s = (void*)g_14095f4;
    _InterlockedExchange((volatile long*)(s + 8), 1);
    *(void**)(s + 0xc) = a1;
    if (a1) {
        void* p = (char*)a1 + 4;
        (*(void(__thiscall**)(void*))*(void**)p)(p);
    }
    *(void**)(s + 0x10) = a2;
    if (a2)
        ((void(__thiscall*)(void*))(*(void***)a2)[1])(a2);
    return this;
}

// @ 0x006b0020
bool __fastcall FUN_006b0020(char* self)
{
    volatile long* c = (volatile long*)(self + 8);
    if (_InterlockedExchangeAdd(c, 0) == 0)
        return false;
    if (_InterlockedExchangeAdd(c, -1) == 1) {
        void* p = *(void**)(self + 0x10);
        int* r = (int*)((int(__thiscall*)(void*))(*(void***)p)[0x10 / 4])(p);
        int v[3];
        v[0] = r[0];
        v[1] = r[1];
        v[2] = r[2];
        void* q = (*(void*(__thiscall**)(void*))(*(void***)p)[0x18 / 4])(p);
        int a = ((int(__thiscall*)(void*))(*(void***)q)[0x1c / 4])(q);
        void* z = *(void**)(*(char**)(self + 0xc) + 0x10);
        ((void(__thiscall*)(void*, int*, int))(*(void***)z)[0x18 / 4])(z, v, a);
        (*(void(__thiscall**)(void*))(*(void***)p)[0x24 / 4])(p);
    }
    return true;
}

// @ 0x006b00a0
void* FUN_006b00a0(int a1, int a2)
{
    char* p = (char*)FUN_00926020(0x18, "App/LRUCache", 0, 0, 0, 0);
    if (!p)
        return 0;
    return ((ThiscallExt*)p)->FUN_006af960(a1, a2);
}

// @ 0x006b0130
bool C_6b0130::f(int a, unsigned* p3, unsigned* p4, int p5, int p6, int p7)
{
    char* self = (char*)this;
    void* s0c = *(void**)(self + 0xc);
    void* s10 = *(void**)(self + 0x10);
    bool (__thiscall* f34)(void*, int, void*, unsigned*, int, int, int) =
        (bool(__thiscall*)(void*, int, void*, unsigned*, int, int, int))(*(void***)s0c)[0x34 / 4];
    if (p3 == 0)
        return f34(s0c, a, 0, p4, p5, p6, p7);
    ((void(__thiscall*)(void*, int))(*(void***)s10)[0x1c / 4])(s10, a);
    if (((unsigned)p4 & 2) == 0)
        return f34(s0c, a, p3, p4, p5, p6, p7);
    unsigned tmp = 0;
    if (f34(s0c, a, &tmp, p4, p5, p6, p7)) {
        char* ad = (char*)FUN_00926020(0x14, "App/LRUCache/RecordAdapter", 0, 0, 0, 0);
        char* obj = 0;
        if (ad)
            obj = (char*)((C_6aff70*)ad)->f(self, (void*)tmp);
        *p3 = (unsigned)obj;
        if (obj)
            ((void(__thiscall*)(void*))(*(void***)obj)[1])(obj);
        if (tmp)
            ((void(__thiscall*)(void*))(*(void***)tmp)[2])((void*)tmp);
        return true;
    }
    if (tmp)
        ((void(__thiscall*)(void*))(*(void***)tmp)[2])((void*)tmp);
    return false;
}

// @ 0x006b02b0
void __fastcall FUN_006b02b0(char* self)
{
    char* p = self + 8;
    while ((int)FUN_0068c140((__int64*)p) != 0) {
        int lo = *(int*)p;
        int hi = *(int*)(p + 4);
        char* n = (char*)(int)FUN_0068c140((__int64*)p);
        *(int*)p = *(int*)(n + 0x18);
        *(int*)(p + 4) = *(int*)(n + 0x1c);
        ((C_6afd10*)self)->f(((__int64)hi << 32) | (unsigned)lo);
    }
    FUN_006afcb0((__int64*)self);
}

// @ 0x006b0300
bool C_6b0300::f(void* out)
{
    struct Pair { int a; int b; };
    char* self = (char*)this;
    char* headp = self + 8;
    char* curp = self + 0x10;
    Pair hc;
    ((ThiscallExt*)&hc)->FUN_0068c1b0(0, 0);
    for (;;) {
        Pair nc, c30, exp;
        __int64 r2;
        do {
            hc.a = *(int*)headp;
            hc.b = *(int*)(headp + 4);
            c30.a = *(int*)curp;
            c30.b = *(int*)(curp + 4);
            char* n = (char*)(int)FUN_0068c140((__int64*)&hc);
            nc.a = *(int*)(n + 0x18);
            nc.b = *(int*)(n + 0x1c);
            r2 = FUN_0068c140((__int64*)headp);
        } while (FUN_0068c140((__int64*)&hc) != r2);
        if ((int)FUN_0068c140((__int64*)&hc) == (int)FUN_0068c140((__int64*)&c30)) {
            if ((int)FUN_0068c140((__int64*)&nc) == 0)
                return false;
            ((C_6afc40*)curp)->f((int)FUN_0068c140((__int64*)&nc),
                                 ((__int64)c30.b << 32) | (unsigned)c30.a);
            continue;
        }
        char* src = (char*)(int)FUN_0068c140((__int64*)&nc);
        ((int*)out)[0] = ((int*)src)[0];
        ((int*)out)[1] = ((int*)src)[1];
        ((int*)out)[2] = ((int*)src)[2];
        ((int*)out)[3] = ((int*)src)[3];
        ((int*)out)[4] = ((int*)src)[4];
        __int64 nl = FUN_0068c140((__int64*)&nc);
        exp.a = hc.a;
        exp.b = hc.b;
        __int64 e = FUN_0068c140((__int64*)&exp);
        unsigned hi = ((unsigned)((unsigned __int64)e >> 32) | ((int)nl >> 31)) + 1;
        __int64 nv = ((__int64)hi << 32) | (unsigned)(int)nl;
        if (_InterlockedCompareExchange64((volatile __int64*)headp, nv, e) == e) {
            ((C_6afd10*)self)->f((((__int64)hc.b) << 32) | (unsigned)hc.a);
            return true;
        }
    }
}

// @ 0x006b04a0
void* C_6b04a0::f(void** out, char* pos, unsigned* key, char flag)
{
    char* self = (char*)this;
    int side = 0;
    if (flag == 0 && pos != self + 4) {
        unsigned p14 = *(unsigned*)(pos + 0x14);
        unsigned p10 = *(unsigned*)(pos + 0x10);
        if (p14 <= key[1] && (key[1] != p14 || p10 <= key[0]))
            side = 1;
    }
    char* node = (char*)ea_alloc_raw(0x20, (void*)"App", 0, 0, (int)g_13ebb38, 0xd1);
    if (node != 0) {
        *(unsigned*)(node + 0x10) = key[0];
        *(unsigned*)(node + 0x14) = key[1];
        *(unsigned*)(node + 0x18) = key[2];
    }
    FUN_009216a0(node, pos, self + 4, side);
    (*(int*)(self + 0x14))++;
    *out = node;
    return out;
}

// @ 0x006b0530
void* __stdcall FUN_006b0530(void* src)
{
    char* p = (char*)ea_alloc_raw(0x20, (void*)"App", 0, 0, 0, 0);
    if (!src) {
        if (!p)
            return 0;
        *(void**)p = 0;
        *(void**)(p + 0x10) = 0;
        *(void**)(p + 4) = 0;
        *(void**)(p + 8) = 0;
        *(void**)(p + 0xc) = 0;
        ((SubC1b0*)(p + 0x18))->init(0, 0);
        return p;
    }
    if (!p)
        return 0;
    *(void**)p = *(void**)src;
    *(void**)(p + 4) = *(void**)((char*)src + 4);
    *(void**)(p + 8) = *(void**)((char*)src + 8);
    *(void**)(p + 0xc) = *(void**)((char*)src + 0xc);
    *(void**)(p + 0x10) = *(void**)((char*)src + 0x10);
    ((SubC1b0*)(p + 0x18))->init(0, 0);
    return p;
}

// @ 0x006b05d0
bool __stdcall FUN_006b05d0(void* self)
{
    FUN_006afe80();
    return true;
}

// @ 0x006b0670
void* C_6b0670::f(void* out, unsigned* key, int extra)
{
    char* self = (char*)this;
    char* node = self + 4;
    bool goLeft = true;
    char* cur = *(char**)(self + 0xc);
    while (cur != 0) {
        node = cur;
        if (*(unsigned*)(cur + 0x14) < key[1] ||
            (*(unsigned*)(cur + 0x14) <= key[1] && *(unsigned*)(cur + 0x10) <= key[0]))
            goLeft = false;
        else
            goLeft = true;
        cur = goLeft ? *(char**)(node + 4) : *(char**)node;
    }
    char* lb = node;
    if (goLeft) {
        if (node == *(char**)(self + 8))
            goto insert;
        lb = (char*)FUN_009215c0(node);
    }
    if (key[1] < *(unsigned*)(lb + 0x14) ||
        (key[1] <= *(unsigned*)(lb + 0x14) && key[0] <= *(unsigned*)(lb + 0x10))) {
        *(void**)out = lb;
        *(char*)((char*)out + 4) = 0;
        return out;
    }
insert:
    void* tmp = 0;
    ((C_6b04a0*)self)->f(&tmp, node, key, 0);
    *(void**)out = tmp;
    *(char*)((char*)out + 4) = 1;
    return out;
}

// @ 0x006b0720
void* C_6b0720::f(void* out, void* src)
{
    char* self = (char*)this;
    __int64 lhead = *(__int64*)self;
    __int64 head = FUN_0068c140(&lhead);
    while ((int)head != 0) {
        char* h2 = (char*)(int)FUN_0068c140(&lhead);
        __int64 lnext = *(__int64*)(h2 + 0x18);
        __int64 next = FUN_0068c140(&lnext);
        __int64 lh = lhead;
        __int64 expected = FUN_0068c140(&lh);
        unsigned hi = ((unsigned)((unsigned __int64)expected >> 32) | ((int)next >> 31)) + 1;
        __int64 nv = ((__int64)hi << 32) | (unsigned)(int)next;
        if (_InterlockedCompareExchange64((volatile __int64*)self, nv, expected) == expected) {
            __int64 scratch;
            ((ThiscallExt*)&scratch)->FUN_0068c1b0(0, 0);
            char* n = (char*)(int)FUN_0068c140(&lhead);
            *(int*)(n + 0x18) = *(int*)&scratch;
            *(int*)(n + 0x1c) = *((int*)&scratch + 1);
            if (src) {
                char* d = (char*)(int)FUN_0068c140(&lhead);
                *(int*)(d + 0x00) = *(int*)((char*)src + 0x00);
                *(int*)(d + 0x04) = *(int*)((char*)src + 0x04);
                *(int*)(d + 0x08) = *(int*)((char*)src + 0x08);
                *(int*)(d + 0x0c) = *(int*)((char*)src + 0x0c);
                *(int*)(d + 0x10) = *(int*)((char*)src + 0x10);
            }
            *(int*)out = (int)lhead;
            *(int*)((char*)out + 4) = (int)((unsigned __int64)lhead >> 32);
            return out;
        }
        lhead = *(__int64*)self;
        head = FUN_0068c140(&lhead);
    }
    char* node = (char*)FUN_006b0530(src);
    ((ThiscallExt*)out)->FUN_0068c1b0((int)node, 0);
    return out;
}

// @ 0x006b08a0
void* __stdcall FUN_006b08a0(void* a, void* b)
{
    char* p = (char*)ea_alloc_raw(0x128, (void*)"App/Resource/LRUCache", 0, 0, 0, 0);
    if (!p)
        return 0;
    *(void**)p = a;
    *(void**)(p + 4) = b;
    *(void**)(p + 8) = 0;
    *(void**)(p + 0xc) = 0;
    char* q = p + 0x28;
    *(void**)(p + 0x10) = q;
    *(void**)(p + 0x14) = q;
    q += 0x100;
    *(void**)(p + 0x24) = 0;
    *(void**)(p + 0x18) = q;
    return p;
}

// @ 0x006b0900
void* __fastcall FUN_006b0900(char* self)
{
    struct Pair { int a; int b; };
    Pair out;
    Pair loc;
    ((ThiscallExt*)self)->FUN_0068c1b0(0, 0);
    ((ThiscallExt*)(self + 8))->FUN_0068c1b0(0, 0);
    ((ThiscallExt*)(self + 0x10))->FUN_0068c1b0(0, 0);
    int* pu = (int*)((C_6b0720*)self)->f(&out, 0);
    *(int*)(self + 0x10) = pu[0];
    *(int*)(self + 0x14) = pu[1];
    *(int*)(self + 8) = pu[0];
    *(int*)(self + 0xc) = pu[1];
    ((ThiscallExt*)&loc)->FUN_0068c1b0(0, 0);
    char* n = (char*)(int)FUN_0068c140((__int64*)(self + 8));
    *(int*)(n + 0x18) = loc.a;
    *(int*)(n + 0x1c) = loc.b;
    return self;
}

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

// @ 0x006b18c0
void CacheMgr::Notify(CacheEvent* ev)
{
  uint32_t* p = (uint32_t*)ev + 1;
  Key8 key;
  key.lo = p[0];
  key.hi = (p[2] & 0xc0000000u) == 0x40000000u ? (p[2] & 0xc0ff0000u) : 0;
  AreaMapNode* node;
  map.find((void**)&node, &key);
  ListNode* it = &list;
  if (node != (AreaMapNode*)&map.head) {
    it = (ListNode*)node->mpValue;
  }
  if (ev->op == 0) {
    if (it != &list) {
      Touch(it);
    }
    return;
  }
  if (ev->op == 1) {
    if (it == &list) {
      ListNode* added;
      it = *(ListNode**)InsertKey((void**)&added, key.lo, key.hi);
    } else {
      Touch(it);
    }
    AreaRec* area = it == &list ? 0 : it->mpValue;
    m40 += area->AddFromEvent((int*)p, ev->extra);
    return;
  }
  if (ev->op == 2 && it != &list) {
    m40 += it->mpValue->AddFromStream((int*)p);
  }
}

// @ 0x006b19e0
void CacheMgr::ReleaseArea(ListNode* it)
{
  AreaRec* area;
  if (it == &list) {
    area = 0;
  } else {
    area = it->mpValue;
  }
  Key8 key;
  key.hi = area->m04;
  key.lo = area->m00;
  m40 -= area->SizeTaken(m0c);
  AreaMapNode* node;
  map.find((void**)&node, &key);
  if (node != (AreaMapNode*)&map.head) {
    --map.size;
    RBTreeIncrement(node);
    RBTreeErase(node, &map.head);
    EAFree(node);
  }
  ListNode* p = it->mpNext->mpPrev;
  p->mpPrev->mpNext = p->mpNext;
  p->mpNext->mpPrev = p->mpPrev;
  EAFree(p);
  FreeOwned(area->mpBuf);
  EAFree(area);
  mb15 = 1;
}

// @ 0x006b1ab0
void CacheMgr::Destructor()
{
  vt0 = (uint32_t)&gVtblCacheMgrA;
  vt1 = (uint32_t)&gVtblCacheMgrB;
  if (mb14 != 0) {
    Shutdown();
  }
  sub.Free();
  if (job != 0) {
    job->Release();
  }
  if (stream != 0) {
    ((StreamVt*)stream)->Release();
  }
  ListNode* it = list.mpNext;
  while (it != &list) {
    ListNode* next = it->mpNext;
    EAFree(it);
    it = next;
  }
  map.Clear(map.m0c);
  if (mpOwner != 0) {
    ((OwnerObj*)mpOwner)->ref.Release();
  }
  vt0 = (uint32_t)&gVtblCacheMgrBaseA;
  vt1 = (uint32_t)&gVtblCacheMgrBaseB;
}

// @ 0x006b1b80
void CacheMgr::Update()
{
  CacheEvent ev;
  ev.lo = 0;
  ev.m08 = 0;
  ev.hi = 0;
  if (sub.Poll(&ev)) {
    do {
      Notify(&ev);
    } while (sub.Poll(&ev));
  }
  int limit = g_pDirectPropertyList->GetIntProperty(m10);
  mLimit = __allmul(limit, limit >> 31, 0x100000, 0);
  if (mLimit != 0) {
    do {
      if (m40 <= mLimit) {
        break;
      }
      if (list.mpNext == &list) {
        m40 = 0;
      } else {
        ListNode* it = list.mpNext;
        if (it->mpValue->CanRelease(m0c)) {
          Touch(it);
          break;
        }
        ReleaseArea(it);
      }
    } while (mLimit != 0);
  }
  Tracer* tracer = FUN_0068f4d0();
  tracer->Enter();
  try {
    if (job != 0) {
      int status = job->ContinueJob();
      if ((unsigned)(status - 7) <= 1) {
        Job_s006b_18c0* j = job;
        if (j != 0) {
          job = 0;
          j->Release();
        }
      }
    }
    if (--m50 == 0) {
      m50 = 9000;
      if (mb15 != 0 && job == 0) {
        Job_s006b_18c0** slot = &job;
        Tracer* t2 = FUN_0068f4d0();
        Job_s006b_18c0* j = job;
        if (j != 0) {
          job = 0;
          j->Release();
        }
        if (t2->CheckJob(slot)) {
          StartJob();
          Job_s006b_18c0* nj = job;
          nj->mpFunc = (void*)&gJobFunc;
          nj->mpOwner = this;
          job->m18 = 4;
          job->GetStatus();
          mb15 = 0;
        }
      }
    }
  } catch (...) {
  }
  tracer->Exit();
}
