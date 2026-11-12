// src/game/SPEngine/SPGraphicsResourceFactory.cpp -- migrated from slice(s) s00761dc0, s00769f20, s00769310, s007689a0, s00767ee0, s00766fa0, s00765f80, s00764df0, s00763cb0, s00762d70, s00682f40 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsResourceFactory.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <intrin.h>
#include "SP/cGraphicsResourceFactory.h"
#include "SP/cResourceBase.h"
#include <string.h>
#include "rw/core/arena/Arena.h"
#include "EA/Audio/IPrimitive.h"
#include <malloc.h>
#include <new>
#include "rw/graphics/IndexBuffer.h"
#include "rw/graphics/VertexBuffer.h"
#include "SP/cJob.h"
#include "rw/graphics/EmbeddedState.h"
#include <xmmintrin.h>
#include "SP/cJobLock.h"

// ---- items of slice s00682f40 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct RefCounted {
    void* vtbl;                         // +0x00
    volatile int mRef;                  // +0x04
    int AddRef();
    int Release();
};
// ---- items of slice s00682f40 end

// ---- items of slice s00762d70 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  __cdecl EA_Delete(void* p);                                                  // 0x0f47380
extern "C" bool  __cdecl EA_IO_ReadInt32(void* stream, void* dst, int count, int flags);      // 0x093a780
extern "C" void* __cdecl GetGlobal67dd60();                                                   // 0x067dd60
extern "C" void* __cdecl GetGlobal67de80();                                                   // 0x067de80
extern "C" void* __cdecl MaterialManager();                                                   // 0x067dd70
extern "C" void* __cdecl CreateRasterFn(int w, int h, int a, int b, int c);                   // 0x0761420
extern unsigned char g_flags1630180;   // 0x01630180
extern void* g_sAppProperties;         // 0x015fd918
extern void* g_arena16303f0;           // 0x016303f0
extern void* g_arena16303f4;           // 0x016303f4
extern int g_word160077c;              // 0x0160077c
extern char g_140e00c[];               // 0x0140e00c
extern "C" void* __fastcall F_68c140(const void* key8);                       // 0x0068c140 AtomicRead64
extern "C" void  __fastcall F_68c1b0(const void* key8, unsigned __int64 val); // 0x0068c1b0 AtomicExchange64
extern "C" void  __cdecl F_87cde0(void* stream);                                  // 0x0087cde0 stream ctor
extern "C" bool  __cdecl F_87ce00(void* stream, const char* name);                // 0x0087ce00 open
extern "C" bool  __cdecl F_87d0b0(void* stream, void* a, void* b);                // 0x0087d0b0 read header
extern "C" void* __cdecl F_87ced0(void* stream, int flags);                       // 0x0087ced0 get record
extern "C" bool  __cdecl F_87cf00(void* stream, void* rec, void* dst, int size);  // 0x0087cf00 decompress
extern "C" void  __cdecl F_87cef0(void* stream, void* rec);                       // 0x0087cef0 release record
extern "C" void  __cdecl F_87ce90(void* stream);                                  // 0x0087ce90
extern "C" void  __cdecl F_87d070(void* stream);                                  // 0x0087d070 dtor/closer
extern "C" void* __cdecl F_11e2fe0(void* scope);                       // 0x011e2fe0 scope ctor
extern "C" bool  __cdecl F_11e3350(void* stream, void* out, int flags);// 0x011e3350 begin
extern "C" bool  __cdecl F_11e34d0(void* scope);                       // 0x011e34d0 advance
extern "C" bool  __cdecl F_11e3c50(void* scope, void* cb);             // 0x011e3c50 set callback
extern "C" bool  __cdecl F_11e3940(void* scope);                       // 0x011e3940 advance
extern "C" void  __cdecl F_11e2690(void* scope);                       // 0x011e2690 scope dtor
extern "C" void* __cdecl F_11e0744(void* dst, void* src, int n);       // 0x011e0744 memcpy-ish
extern void* g_dev16f89d0;                                            // 0x016f89d0 device singleton
extern "C" void* __cdecl EA_New_s0076_2d70(uint32_t size, const char* file, int a, int b, int c, int d); // 0x0f473a0
struct RefVec {
    void* b; void* e; void* c;
    RefVec() { b = 0; e = 0; c = 0; }
    ~RefVec() { destroy(); }
    void destroy();   // 0x0041eb80
};
struct Raster { void D3D9GetStreamedMipLevelSize(unsigned char*, int); }; // 0x011f0270
struct Arena_s0076_2d70 { unsigned char f(void* addr, unsigned n); };           // vtbl +0x38 call
struct IObj { virtual void s0(); virtual void s1(); virtual void s2(int); };
struct Color3 { int r, g, b; };
struct KeyDef { int a, b; int key; };
extern Color3 g_colors[];              // 0x016304bc
namespace SP {
struct cRasterFromGimexLoadState_s0076_2d70 {
    uint32_t mFormat; uint32_t mWidth; uint32_t mHeight;
    uint32_t mBpp; uint32_t mPitch; uint32_t mSize; unsigned char* mData;
};
}
using SP::cRasterFromGimexLoadState_s0076_2d70;
struct Map762fa0 {
    int field0; int field4; int field8; int fieldC;
    void* Insert(void* out, const void* key);   // 0x00762fa0
    void  Append(const void* key);              // 0x00763130
};
struct IUnknown32 {
virtual void u0();
virtual void u1();
virtual void u2();
};
struct AtomicInt {
    int v;
    int operator=(int x) { return _InterlockedExchange((volatile long*)&v, x); }
};
struct Resource : IUnknown32 {
    AtomicInt mRefCount;      // +0x4
    int mKey0, mKey1, mKey2;  // +0x8
    Resource() { mRefCount = 0; mKey0 = 0; mKey1 = 0; mKey2 = 0; }
};
struct cResourceBase_s0076_2d70 : Resource {
    int* mReleaseCallback;    // +0x14
    cResourceBase_s0076_2d70() { mReleaseCallback = 0; }
};
struct CEditorRes : cResourceBase_s0076_2d70 {
    RefVec mRefs;             // +0x18
    CEditorRes();
    ~CEditorRes() {}
};
struct EhItem { void* p; int x; ~EhItem(); };
struct EhHolder { char pad[0x44]; EhItem a[4]; EhItem b[4]; ~EhHolder(); };
struct GimexRecord { char pad[0x10]; int mWidth; int mHeight; int mBpp; };
struct StreamObj { char pad[0x20]; };
struct OutRaster { char pad[0x18]; void* mData; };
struct RasterFactory {
    bool LoadAndCreateRaster(cRasterFromGimexLoadState_s0076_2d70* state, int a, int b, void* out3);
};
struct V3 { int x, y, z; };
struct UniqVec {
    char pad[0x134];
    int mCount;
    int mArr[16];
    void AddUnique(int v);
};
extern "C" void  __cdecl RemoveRegistrationCallback(int id, void* cb);                        // 0x06ad070
// ---- items of slice s00762d70 end

// ---- items of slice s00763cb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
__declspec(noinline) bool __cdecl FUN_763fd0(void* arena) { (void)arena; return false; }       // 00763fd0
bool __cdecl FUN_763fd0(void* arena);           // 0x00763fd0
extern "C" int   __cdecl FUN_011f06c0(void* a, void* b);               // 0x011f06c0
extern float g_one_01485720;    // 0x01485720
extern void*    g_texStageRaster0;                   // 0x016303f8
extern void*    g_texStageRaster1;                   // 0x016303fc
extern uint32_t g_texStageCreate[3];                 // 0x016304d4 / d8 / dc
extern uint32_t g_texStageRasterType[3];             // 0x016304c8 / cc / d0
#pragma pack(push, 1)
#pragma pack(pop)
struct RasterCtx { char Create(void* a, void* b, void* c); };
struct Ctx63620 { char Load(void* a, void* b, void* c); };
struct Ctx63770 { char Fill(void* a, void* b, void* c); };
struct V3u { uint32_t x, y, z; };
struct IfA {
    virtual void AddRef();
    virtual void Release();
    uint32_t pad04;
    V3u v08;                   // +8
    uint32_t pad14;
    void* f18;                 // +0x18
};
struct Z4 { uint32_t a, b, c, d; };
struct BRD {                                            // rw::BaseResourceDescriptor
    uint32_t size, align;
    BRD();      // 0x006c0fa0
    ~BRD();     // 0x00c2e4e0
};
struct BRDs { BRD d[4]; };                              // rw::BaseResourceDescriptors<4>
struct RDesc : BRDs { RDesc() { d[0].size = 0; d[0].align = 1; } };   // rw::ResourceDescriptor
struct IfB {
    virtual void AddRef();
    virtual void Release();
    virtual void v2();
    virtual void v3();
    virtual void Alloc(const RDesc* rd, int z);   // slot 4
    virtual void Done();                          // slot 5
    virtual void Reset(Z4* z);                    // slot 6
    virtual char** Blocks();                      // slot 7
};
struct Registry { virtual void v0(); virtual void v1(); virtual void v2(); virtual void* Query(uint32_t id); };   // slot 3
struct Stm7 {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
    virtual uint32_t Size();                       // slot 7
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
    virtual uint32_t Read(void* p, uint32_t n);    // slot 12
};
template <class T> struct AutoRefT { T* p; ~AutoRefT() { if (p) p->Release(); } };
struct D7642c0 {                    // SP::cGraphicsResourceFactory::cArenaLoadState
    uint32_t size;                 // +0 mRecordSize
    AutoRefT<IfA> a;               // +4 mArenaResource
    AutoRefT<IfB> b;               // +8 mRwAllocator
    D7642c0() { a.p = 0; b.p = 0; }
    __declspec(noinline) ~D7642c0();
};
struct TR { uint32_t a, b, c, d; TR() { a = 0; b = 0; c = 0; d = 0; } };   // rw::TargetResource
struct Arena98 {
    uint32_t hdr[0x44 / 4];
    RDesc a;                       // +0x44 m_resourceDescriptor
    RDesc b;                       // +0x64 m_resourcesUsed
    TR r;                          // +0x84 m_resource
    uint32_t grp;                  // +0x94 m_arenaGroup
    __declspec(noinline) Arena98();   // 0x00764220
    ~Arena98();                       // 0x007635b0
};
void* __cdecl SP_CreateRaster(int, int, int, int, int);   // 0x00761420
void __cdecl FreeMem(void* p);                             // 0x00f47380
struct RasterObj { char pad[0x12]; uint8_t face; void SetMipLevelData(void* data, uint32_t level); };   // 0x011f0270
struct RasterLoadState {
    uint32_t pad0[1];
    int w, h, nml, tp, fm;     // +4
    uint8_t isCube; uint8_t pad19[3];
    uint32_t numFaces;         // +0x1c
    uint32_t pad20[0x58 / 4];
    void** pix;                // +0x78
};
struct OutRec { char pad[0x18]; void* raster; };
struct T3 { uint32_t x, y, z; T3(uint32_t a, uint32_t b, uint32_t c) : x(a), y(b), z(c) {} };
struct WStream {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
    virtual uint32_t Write(const void* p, uint32_t n);   // slot 14 (+0x38)
};
struct Cell { void* GetChildID(uint32_t* count); };   // 0x00700360 thiscall (ret 4)
struct P74 { char pad[8]; T3 v; };
struct Rec7c { char a[0x38]; char b[0x38]; uint32_t f70; P74* p74; Cell* p78; };
struct RecSrc { char pad[0x108]; char* begin; char* end; };
struct Matrix3 { float m[9]; Matrix3& Assign(const Matrix3& o); };   // 0x0041cb40 thiscall
struct V3g { float x, y, z; };
extern V3g g_v3_01630408;       // 0x01630408
extern Matrix3 g_mat_01630560;  // 0x01630560
struct Blk {
    uint16_t a, b;       // +0
    V3g pos;             // +4
    float w;             // +0x10
    Matrix3 m;           // +0x14
};
struct Ctor764760 {
    Blk blk0;            // +0
    Blk blk1;            // +0x38
    uint32_t p70, p74, p78;
    Ctor764760* Init(uint32_t v);
};
static void InitBlk(Blk* b) {
    b->a = 0; b->b = 0;
    b->pos.x = g_v3_01630408.x; b->pos.y = g_v3_01630408.y; b->pos.z = g_v3_01630408.z;
    b->w = g_one_01485720;
    b->m.Assign(g_mat_01630560);
}
struct Slot9 { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
               virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); };
struct cSPMemPool { void* LockedAlloc(uint32_t size, int a, int b, int c, int d, int e); };   // 0x009289f0 (ret 0x18)
extern cSPMemPool* g_pSPMemPool;                                                              // 0x016c8b44
void* __cdecl ZoneObject_new(int size, const char* name, int a, int b, int c, int d);         // 0x00926020
void* __cdecl TaggedNew(uint32_t size, const char* name, int a, int b, int c, int d);         // 0x00f473a0
struct Rc { virtual void Del(int); long rc; };
struct SharedBuf {                       // EA::IO::SharedPointer-like buffer holder, 0x18 bytes
    void* vptr0; Rc rcb; void* pad0c; void* data; int pad14;
    SharedBuf(void* a, void* b, uint8_t c);   // 0x0093bc40
    static void* operator new(size_t n, const char* name, int a, int b, int c, int d) { return ZoneObject_new((int)n, name, a, b, c, d); }
    static void operator delete(void*, const char*, int, int, int, int) {}
    static void operator delete(void*) {}
};
struct SBHandle {
    SharedBuf* p;
    SBHandle(SharedBuf* q) : p(q) { if (p) _InterlockedIncrement(&p->rcb.rc); }
    ~SBHandle() {
        Rc* r = &p->rcb;
        long n = _InterlockedDecrement(&r->rc);
        if (n == 0) {
            _InterlockedExchange(&r->rc, 1);
            if (r) r->Del(1);
        }
    }
};
struct Stm {                                  // memory stream held at Loader::p28
virtual void v0();
virtual void AddRef();
virtual void Release();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
    virtual int GetSize();                    // slot 11
    virtual int Read(void* p, uint32_t n);    // slot 12
};
struct AsyncReq : Stm {                       // Graphics::GraphicsFactoryAsyncRequest, 0x24 bytes
    char pad[0x24 - 4];
    AsyncReq(SharedBuf* sp, uint32_t size, const char* name);   // 0x0093c270
    static void* operator new(size_t n, const char* name, int a, int b, int c, int d) { return TaggedNew((uint32_t)n, name, a, b, c, d); }
    static void operator delete(void*, const char*, int, int, int, int) {}
    static void operator delete(void*) {}
};
struct AsyncMgr { void RequestComplete(void* req, void* arg); };   // 0x006ae880 thiscall (ret 8)
AsyncMgr* __cdecl GetAsyncMgr();                                    // 0x0067de70
bool __cdecl FUN_6ae2f0(char* a, void* b);                          // 0x006ae2f0 cdecl
struct Loader {
    char pad0[0xc];
    void* pC;                  // +0xc
    Slot9* p10;                // +0x10
    void* p14;                 // +0x14
    char pad18[4];
    char r1c[0xc];             // +0x1c
    Stm* p28;                  // +0x28
    char p2c[0x308];           // +0x2c
    unsigned char b334;        // +0x334
    void Wrap670(int);
    void Wrap6a0(int);
    void Wrap6c0(int);
    bool Load820(int);         // 0x764820
    bool Complete(char* a);    // 0x7649f0
};
void Loader::Wrap670(int) {
    RasterCtx* ctx = (RasterCtx*)pC;
    char ok = ctx->Create(p2c, p28, p14);
    if (ok)
        b334 = 1;
}
void Loader::Wrap6c0(int) {
    if (((Ctx63770*)pC)->Fill(p2c, p28, p14))
        b334 = 1;
}
struct ArenaOwner { void* arena; };
struct ArenaIter { char pad[0x134]; uint32_t f134; char pad2[0x40];
void Init();
void Done();
    ArenaIter() { Init(); f134 = 0; } ~ArenaIter() { Done(); } };
int __cdecl ArenaStart(void* arena, ArenaIter* it, void* owner, int* flag);   // 0x011e3c70
unsigned int __cdecl FixupNext(ArenaIter*);     // 0x011e39e0 rw::core::arena::Arena::FixupNext
unsigned int __cdecl DestructNext(ArenaIter*);  // 0x011e2330 rw::core::arena::Arena::DestructNext
namespace SP {
class cGraphicsResourceFactory_s0076_3cb0 {
public:
    bool Init();                                            // 007641c0 0x007641c0
    bool FixupArena(ArenaOwner* p);                         // 00764580 0x00764580
    bool ReadResourceArena(D7642c0* st, Stm7* s, Registry* reg);   // 00764a50 0x00764a50
    bool BuildArena(Stm7* s, Registry* reg, const V3u* pv); // 00764ce0 0x00764ce0
};
}
struct EmbeddedState {
    char     pad0[0x10];
    uint32_t dirtyBits;                              // +0x10
    unsigned int GetTextureStageState(int stage);    // 0x011ee870
    void         SetRaster(int stage, void* raster); // 0x011ee6b0
};
struct RasterThing {
    void FUN_00763c60(unsigned state);               // 0x00763c60
};
struct Managed { void* value; uint8_t flags; };      // +0 flags bit0
void* __cdecl GetRasterMgr();                        // 0x0067dd60
uint32_t __cdecl FUN_011ed690(void* hard, void* raster);   // 0x011ed690
extern "C" void* __cdecl AddRegistrationCallback(int id, void* cb);   // 0x06adfe0
extern "C" void* __cdecl ArenaTypeRegGetType(int t);                   // 0x011e22c0
extern "C" void* __cdecl GetManager();                                 // 0x067dcd0
extern char  kRasterRecordTypes[];                          // 0x0140e000
// ---- items of slice s00763cb0 end

// ---- items of slice s00764df0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl EA_New(uint32_t size, const char* f, int a, int b, const char* g, int line); // 0x0f473a0
extern "C" void  __cdecl DoFreeNodes(void* b, void* e, void* n);                                      // 0x04554f0
extern const char g_allocFile[];   // 0x13ebb38
struct Ctx764df0 { char CreateRaster(void* a, void* b, void* c); };   // 0x764df0 thiscall, 3 args
struct Ctx764a50 { char ReadArena(void* a, void* b, void* c); };      // 0x764a50 thiscall, 3 args
struct Loader29 {
    char pad0[0xc];
    void* pC;                  // +0xc
    char pad10[4];
    void* p14;                 // +0x14
    char pad18[0x10];
    void* p28;                 // +0x28
    char p2c[0x308];           // +0x2c
    unsigned char b334;
    void WrapDf0(int);
    void WrapA50(int);
};
struct Node8 { int x, y; };
struct HVec { Node8* b; Node8* e; Node8* cap; void grow(unsigned n); };
struct Vec { void** b; void** e; void** cap; int alloc; void** inlinebuf; };
struct D765ac0 {
    char pad[0x20];
    Vec v20;                 // +0x20
    char padX[0x78 - 0x34];
    Vec v78;                 // +0x78
    ~D765ac0();
};
struct IUnknown32_s0076_4df0 {
    virtual void u0();
    virtual void u1();
    virtual void u2();
};
struct AtomicInt_s0076_4df0 { int v; int operator=(int x) { return _InterlockedExchange((volatile long*)&v, x); } };
struct Resource_s0076_4df0 : IUnknown32_s0076_4df0 {
    AtomicInt_s0076_4df0 mRefCount; int k0, k1, k2;
    Resource_s0076_4df0() { mRefCount = 0; k0 = 0; k1 = 0; k2 = 0; }
};
struct cResourceBase_s0076_4df0 : Resource_s0076_4df0 { int* cb; cResourceBase_s0076_4df0() { cb = 0; } };
struct D765f10 : cResourceBase_s0076_4df0 {
    int f18;
    void* f1c;
    D765f10(void* arg);
};
struct RefIface { virtual void AddRef(); virtual void Release(); };
struct ArenaHolder : RefIface { char pad[0x14]; void* arenaPtr; };   // +0x18 arena (rw::core::arena::Arena*)
struct Elem { uint32_t a, b; Elem(); ~Elem(); };               // 0x006c0fa0 / 0x00c2e4e0
struct Res16 { void* m[4]; Res16() { for (int i = 0; i < 4; i++) m[i] = 0; } };
struct RDesc2 { Elem d[4]; RDesc2() { d[0].a = 0; d[0].b = 1; } };
__declspec(noinline) Elem::Elem() { a = 0; b = 1; }     // 0x006c0fa0
__declspec(noinline) Elem::~Elem() {}                    // 0x00c2e4e0
struct ExpObj { uint32_t type; void* obj; Res16 res; RDesc2 rd;
    ExpObj() : type(0), obj(0) {}
};
struct Arena_s0076_4df0 {
    int GetNumExportedObjects();                           // 0x011e23a0
    void GetExportedObjectByIndex(int idx, ExpObj* out);   // 0x011e28e0
};
bool __cdecl SetCachingType(int type, void* obj);          // 0x006ac040
struct RefObj2 { virtual void s0(); virtual void s1(); virtual void s2(); };
struct D7643d0 {                  // two refcounted handles (release = slot 1)
    RefObj2* a;                   // +0
    RefObj2* b;                   // +4
    D7643d0() { a = 0; b = 0; }
    ~D7643d0();                   // 0x007643d0
    RefObj2** ResetB() { if (b) { RefObj2* t = b; b = 0; t->s1(); } return &b; }
};
struct ArenaSrc { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
                  virtual void Get(RefIface** out); };      // slot 5
struct CreateRasterIn { ArenaSrc* loader; ArenaHolder* res; };
struct CreateRasterOut { char pad[0x18]; void* cell; RefIface* ref; };     // +0x18, +0x1c
namespace SP {
class cGraphicsResourceFactory_s0076_4df0 {
public:
    bool CreateRasterFromArena(CreateRasterIn* in, void* z, CreateRasterOut* out);   // 00764df0 0x00764df0
    bool Fn7655f0(void* a, void* b, void* c);                                        // 007655f0 0x007655f0
};
}
struct ResMgr { virtual void v0(); virtual void v1(); virtual void v2();
                virtual char Get(void* a, RefObj2** out, int z, void* b, void* self, void* c); };   // slot 3, ret 0x18
struct Obj34 { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
               virtual void Fn5(); virtual void v6(); virtual ArenaOwner* Fn7(); };
struct Rec30 { char pad[0x18]; void* f18; };
namespace SP {
 class cGraphicsResourceFactory2 { public: bool FixupArena(ArenaOwner* p); };   // 0x00764580
}
struct LoaderF0 {
    char pad0[0xc];
    SP::cGraphicsResourceFactory2* pC;    // +0xc
    char pad10[0x20];
    Rec30* p30;                           // +0x30
    Obj34* p34;                           // +0x34
    char pad38[0x334 - 0x38];
    unsigned char b334;
    bool Fn7650f0(int);
};
struct IStream_;
struct Mesh764 { char pad[8]; char* recs; };               // +8 record array (0x20 stride)
struct GameMeshes { char pad[8]; char f8[0x10]; Mesh764** begin; Mesh764** end; };   // +8 object, +0x18/+0x1c vector
bool __cdecl WriteUint32(IStream_* s, const uint32_t* p, uint32_t n, int endian);       // 0x0093aa70
bool __cdecl WriteMesh(IStream_* s, Mesh764* m);                                        // 0x0071e390
int  __cdecl FUN_71ddc0(Mesh764* m, int a, int b, int c, int d);                        // 0x0071ddc0
struct MatRec { uint32_t a, b; uint16_t c, d; RefIface* e;
    MatRec(const MatRec& o) : a(o.a), b(o.b), c(o.c), d(o.d), e(o.e) { if (e) e->AddRef(); }
    ~MatRec() { if (e) e->Release(); } };
struct MaterialMgr { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
    virtual void Fn17(uint32_t a, uint32_t b, IStream_* s, void* c); };            // slot 0x44
MaterialMgr* __cdecl GetMaterialManager();                                              // 0x0067dd70
static __forceinline void W32(IStream_* s, uint32_t x) { WriteUint32(s, &x, 1, 0); }
struct AtomicL {
    volatile long v;
    __forceinline long Increment() { return _InterlockedExchangeAdd(&v, 1) + 1; }
    __forceinline long Decrement() { return _InterlockedExchangeAdd(&v, -1) - 1; }
    __forceinline long GetValue() { return _InterlockedExchangeAdd(&v, 0); }
};
struct RcObj { uint32_t p0, p4; AtomicL rc; };
static __forceinline void RcAddRef(RcObj* p) { p->rc.Increment(); }
static __forceinline void RcRelease(RcObj* p) {
    p->rc.Decrement();
    if (p->rc.GetValue() < 1)
        p->rc.Increment();
    else
        p->rc.GetValue();
}
struct RcRef {
    RcObj* p;
    RcRef(RcObj* q) : p(q) { if (p) RcAddRef(p); }
    ~RcRef() { if (p) RcRelease(p); }
    void Reset() { if (p) { RcObj* t = p; p = 0; RcRelease(t); } }
    void Assign(RcObj* q) {
        RcObj* old = p;
        if (q != old) {
            if (q) RcAddRef(q);
            p = q;
            if (old) RcRelease(old);
        }
    }
};
struct SlotEnt { uint32_t a; RcObj* ref; uint32_t c, d; };
struct MeshS { char pad4[4]; uint16_t w4; uint16_t w6; void* p8; uint32_t cnt; SlotEnt ents[1]; };   // ents at +0x10
struct MeshVec { char pad[8]; MeshS** begin; MeshS** end; };
struct WStream7 {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
    virtual uint32_t Write(const void* p, uint32_t n);   // slot 14 (+0x38)
};
struct KeyOut { uint32_t instance, type, group; };
struct KeyMgr { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
    virtual void GetKey(KeyOut* out, RcObj* h); };      // slot 11 (+0x2c)
KeyMgr* __cdecl FUN_67dd60();                           // 0x0067dd60
uint32_t __cdecl FUN_778050(uint32_t t);                // 0x00778050
struct cJob_s0076_4df0 {
    void* mpCallback;           // +0
    void* mpCallbackData;       // +4
    char pad08[0x10];
    uint32_t mFlags;            // +0x18
    void SetCallback(void* f, void* d) { mpCallback = f; mpCallbackData = d; }
    int  Release();                       // 0x00690120
    void Queue();                         // 0x006909b0
    void SetOwner(void* o);               // 0x0068f9b0 (AddRefs the owner into mpExtraObject)
    void AddDependency(cJob_s0076_4df0* other);      // 0x00691380
};
struct JobRefL {
    cJob_s0076_4df0* p;
    JobRefL() : p(0) {}
    ~JobRefL() { if (p) p->Release(); }
    void Reset() { if (p) { cJob_s0076_4df0* t = p; p = 0; t->Release(); } }
};
struct IJobMgr {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
    virtual bool CreateJob(JobRefL* out);     // slot 4 (+0x10)
virtual void v5();
virtual void v6();
virtual void v7();
    virtual void Lock();                      // slot 8 (+0x20)
    virtual void Unlock();                    // slot 9 (+0x24)
};
IJobMgr* __cdecl GetJobManager();             // 0x0068f4d0
struct JobLockL {
    IJobMgr* m;
    JobLockL(IJobMgr* x) : m(x) { m->Lock(); }
    ~JobLockL() { m->Unlock(); }
};
void __cdecl Job7651a0(void*);                // 0x007651a0
void __cdecl Job7651b0(void*);                // 0x007651b0
void __cdecl Job7651c0(void*);                // 0x007651c0
struct IRef2 { virtual void v0(); virtual void Release(); virtual void v2(); virtual void* Query(uint32_t id); };   // slot 3 = Query
struct ReqState {
    IRef2* a;                   // +0
    IRef2* b;                   // +4
    uint32_t c;                 // +8
    char padc[0xd0 - 0xc];
    uint32_t state;             // +0xd0
    __forceinline IRef2** Init() { state = 2; a = 0; IRef2** pb = &b; *pb = 0; return pb; }
};
struct AsyncReqB {
    char pad0[0x18];
    uint32_t id18;              // +0x18
    char pad1c[0x10];
    ReqState st;                // +0x2c
    bool Start(JobRefL* out);
};
struct DomNode { cJob_s0076_4df0* Type(); };                                      // 0x00fc7e50
struct RecInfo { uint32_t f0, f4; };
struct IKeyObj {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
    virtual RecInfo* Info();                 // slot 4 (+0x10)
virtual void v5();
virtual void v6();
    virtual void* Aux();                     // slot 7 (+0x1c)
};
struct IMgr8 {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
    virtual bool Get(RecInfo* a, IRef2** r1, IRef2** r2, int z0, int z1, void* aux, uint32_t v, int z2);   // slot 4, ret 0x20
};
struct AsyncReqC {
    char pad0[0xc];
    uint32_t f0c;               // +0xc
    IKeyObj* obj;               // +0x10
    char pad14[4];
    uint32_t id18;              // +0x18
    char pad1c[0x10];
    ReqState st;                // +0x2c
    bool Start(JobRefL* out);
};
struct Rec7c_s0076_4df0 {  // 0x00422fd0 thiscall, ret 4
    char raw[0x7c];
    Rec7c_s0076_4df0(const Rec7c_s0076_4df0& o);
    void Assign(const Rec7c_s0076_4df0& o);
};
void __cdecl FUN_764700(void*);
void __cdecl FUN_764710(void*);
struct AsyncReqA {
    char pad0[0x10];
    IKeyObj* obj;               // +0x10
    void* f14;                  // +0x14
    uint32_t id18;              // +0x18
    char pad1c[0x10];
    uint32_t f2c;               // +0x2c
    char pad30[0x14];
    void* f44;                  // +0x44
    char pad48[0xb4];
    uint32_t state;             // +0xfc
    bool Start(JobRefL* out);
};
namespace EA {
struct AtomicInt_s0076_4df0 { long mValue; long operator++(int) { volatile long* r = &mValue; _ReadWriteBarrier(); return _InterlockedExchangeAdd(r, 1); } };
}
namespace EA {
class RefCountTemplate_s0076_4df0 { public:
    RefCountTemplate_s0076_4df0() { volatile long* r = &mnRefCount.mValue; _InterlockedExchange(r, 0); }
    virtual ~RefCountTemplate_s0076_4df0() {}
    int AddRef() { return mnRefCount++ + 1; }
    int Release();
    AtomicInt_s0076_4df0 mnRefCount;               // +4
};
}
namespace EA {
template<class T> struct AutoRefCountX {
    T* mpObject;
    AutoRefCountX() : mpObject(0) {}
    AutoRefCountX(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCountX() { if (mpObject) mpObject->Release(); }
};
}
namespace EA {
namespace ResourceMan {
class Factory_s0076_4df0 : public EA::RefCountTemplate_s0076_4df0 { public:};
}
}
struct cJobLock_s0076_4df0 : EA::RefCountTemplate_s0076_4df0 {          // size 0x40
    char pad8[0x38];
    cJobLock_s0076_4df0();                                   // 0x0068eff0
};
void* operator new(size_t, const char*, int, int, int, int);
void operator delete(void*, const char*, int, int, int, int);
struct GrfCtor : EA::ResourceMan::Factory_s0076_4df0 {
    EA::AutoRefCountX<cJobLock_s0076_4df0> mPrestreamMemoryBufferLock;   // +8
    GrfCtor();
};
// ---- items of slice s00764df0 end

// ---- items of slice s00765f80 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl sub_f473a0(uint32_t size, const char* name, int a, int b, const char* file, int line);
extern "C" void* __cdecl EA_Alloc8(uint32_t size, int align, int a, const char* name, int b, int c, const char* file, int line);
extern "C" void  __cdecl EA_Dealloc(void* p);
extern "C" void* __cdecl memcpy_t(void* dst, const void* src, uint32_t n);
extern "C" void  __cdecl sub_6c20b0(void* p);
extern "C" void  __cdecl sub_6c2060(void* p, int a, int b);
extern "C" void  __cdecl sub_6c20e0(void* p);
extern "C" void  __cdecl sub_6ac040(int a, void* b);
extern "C" void* __cdecl MessageServer();
extern "C" void* __cdecl Manager67dcd0();
extern "C" bool  __cdecl ReadInt32(void* stream, void* dst, int count, int flags);
extern "C" void  __cdecl sub_6ac0a0(int a, void* b);
extern "C" void  __cdecl sub_11eff60(void* p);
extern "C" void  __cdecl cLocalLightInfo_dtor(void* alloc, void* obj);
extern "C" char* __cdecl BigMoveBack(char* dst, char* first, char* last, char* src);   // 0x764720
extern "C" char* __cdecl BigMove(char* dst, char* first, char* last);                  // 0x763f10
extern "C" char* __cdecl BigUninitFill(char* dst, uint32_t n, char* value);            // 0x765200
extern "C" extern char g_allocFile_s0076_5f80[];
static inline void* VP(void* p) { return *(void**)p; }
struct IRef {
    virtual void AddRef();   // +0
    virtual void Release();  // +4
    virtual void m2();       // +8
    virtual void m3();       // +0xc
    virtual void m4();       // +0x10
    virtual void m5();       // +0x14
    virtual void m6();       // +0x18
    virtual void m7();       // +0x1c
};
struct Arena {
    void Release();          // 0x11e40a0
};
struct IResEd {
virtual void e0();
virtual void e1();
virtual void e2();
virtual void e3();
virtual void e4();
virtual void e5();
virtual void e6();
virtual void e7();
virtual void e8();
virtual void e9();
virtual void eA();
virtual void eB();
    virtual ~IResEd();
    int mRef;                 // +0x4
    int m08, m0c, m10, m14;   // +0x8..+0x14
    int m18;                  // +0x18
    IRef* m1c;                // +0x1c
    void* Delete(unsigned flags);   // 0x00765f80 (scalar deleting destructor)
};
IResEd::~IResEd() { if (m1c) m1c->Release(); }
struct BaseP {
virtual void p0();
virtual void p1();
virtual void p2();
virtual void p3();
virtual void p4();
virtual void p5();
virtual void p6();
virtual void p7();
virtual void p8();
virtual void p9();
virtual void pA();
virtual void pB();
virtual void pC();
virtual void pD();
virtual void pE();
virtual void pF();
    int mRef;                 // +0x4
    int k8, kc, k10, k14;     // +0x8..+0x14
    int x18;                  // +0x18
    BaseP() { (void)_InterlockedExchange((volatile long*)&mRef, 0); k8 = 0; kc = 0; k10 = 0; k14 = 0; }
};
struct SecP {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
    SecP() {}
};
struct ResB : BaseP, SecP {
    int a20, a24, a28, a2c;   // +0x20..+0x2c
    ResB();
    void* AsInterface(int type);      // 0x766030
    void MoveOut(void* out);          // 0x766100
    void Method66070(int a, int b);   // (secondary slot, 0x766070)
    void Method660b0();               // (secondary slot, 0x7660b0)
};
struct RawRes {
    void* AsInterface(int type);
};
struct AllocDesc {
    uint32_t size;            // +0
    uint32_t type;            // +4
    AllocDesc();              // 0x6c0fa0
    ~AllocDesc();             // 0xc2e4e0
};
void __cdecl FreePtrs4(void* p);                                  // 0x6c20b0
void __cdecl AllocFromDesc(void* dst, const void* desc, int n);   // 0x6c2060
struct ResD {
    char pad0[0x18];
    void* mArena;             // +0x18
    void* m20;                // +0x20
    void* m24;                // +0x24
    void* m28;                // +0x28
    void* m2c;                // +0x2c
    ResD();
};
struct BaseE {
virtual void e0();
virtual void e1();
virtual void e2();
virtual void e3();
virtual void e4();
virtual void e5();
virtual void e6();
virtual void e7();
virtual void e8();
virtual void e9();
virtual void eA();
virtual void eB();
    int mRef;                 // +0x4
    int k8, kc, k10, k14;     // +0x8..+0x14
    BaseE() { (void)_InterlockedExchange((volatile long*)&mRef, 0); k8 = 0; kc = 0; k10 = 0; k14 = 0; }
};
struct ResE : BaseE {
    int a18;                  // +0x18
    ResE();
    ~ResE();
};
ResE::~ResE() {
    if (a18) {
        sub_11eff60((void*)a18);
        cLocalLightInfo_dtor(*(void**)0x016c8b44, (void*)a18);
    }
}
struct VBig {
    char* mpBegin;            // +0
    char* mpEnd;              // +4
    char* mpCap;              // +8
    void _insert(char* position, uint32_t n, char* value);
};
struct PngInner {
    char pad0[0x1c];
    int      c1c;      // +0x1c
    void*    c20;      // +0x20
    void*    c24;      // +0x24
    void*    c28;      // +0x28
    uint32_t c2c;      // +0x2c
    uint32_t c30;      // +0x30
    char     c34;      // +0x34
};
struct PngObj10 {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
    virtual int  v6();      // +0x18
virtual void v7();
virtual void v8();
    virtual void v9();      // +0x24
};
struct PngArg2 {
    char pad0[0xc];
    PngInner* inner;        // +0xc
    PngObj10* obj10;        // +0x10
    void*     p14;          // +0x14
    unsigned char flag18;   // +0x18
};
struct PngArg {
    char pad[0x8];
    PngArg2* p08;           // +0x8
};
struct PngCtx {
    char pad[0x10];
    void ctor87cf40();                          // 0x87cf40 (thiscall)
    void m87cf60(int v);                        // 0x87cf60
    bool m87d2a0(int a, int b);                 // 0x87d2a0
    bool m87d030(void* dst, void* src, int n);  // 0x87d030
    void m87cff0();                             // 0x87cff0
    void m87d260();                             // 0x87d260
};
struct MsgSrv {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
    virtual int  s6(void* a, int, int, int);    // +0x18
};
void __cdecl EA_Free(void* p);                                    // 0xf47380
struct PngStr {
    const char* mpBegin;    // +0
    const char* mpEnd;      // +4
    const char* mpCap;      // +8
    ~PngStr() {
        if ((int)(mpCap - mpBegin) > 1 && mpBegin != 0)
            EA_Free((void*)mpBegin);
    }
};
void __cdecl EAString_sprintf(PngStr* s, const char* fmt, ...);   // 0x472fe0
void __cdecl MsvcrSprintf(char* dst, const char* fmt, ...);       // 0x13cc4a0
struct CEditorRes_s0076_5f80 { CEditorRes_s0076_5f80(); };       // 0x763100 (thiscall, no args)
struct D7004d0    { D7004d0(); };          // 0x7004d0
struct D765f10_s0076_5f80    { D765f10_s0076_5f80(void*); };     // 0x765f10 (thiscall, one arg)
struct AutoRef {
    void* p;                               // +0
    AutoRef& operator=(void* q);           // 0xb5f950 (thiscall, one arg)
};
struct CUnionTarget { void m(); };
struct VPtr {
    uint32_t* mpBegin;   // +0
    uint32_t* mpEnd;     // +4
    uint32_t* mpCap;     // +8
    void push_back(const uint32_t& v);
    void DoInsertValue(uint32_t* pos, const uint32_t& v);  // 0x6c1570
};
struct V4 {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCap;
    uint32_t* mpAlloc;   // +0x10
    void insert(uint32_t* position, uint32_t n, const uint32_t& value);
};
struct RefObj {
    virtual void AddRef();                    // +0x00
    virtual void Release();                   // +0x04
    virtual void r2();                        // +0x08
    virtual RefObj* GetCached(int key);       // +0x0c
    virtual void r4();                        // +0x10
    virtual void GetOut(RefObj** out);        // +0x14
};
struct AutoRefCount {
    RefObj* p;
    AutoRefCount() : p(0) {}
    ~AutoRefCount() { if (p) p->Release(); }
    AutoRefCount& operator=(RefObj* q) {
        RefObj* old = p;
        p = q;
        if (old) old->Release();
        return *this;
    }
};
struct RefVec_s0076_5f80 {
    void* mpBegin;             // +0
    void* mpEnd;               // +4
    void* mpCap;               // +8
    void reserve(uint32_t n);              // 0x4e0880 (thiscall)
    void push_back(const AutoRefCount& v);      // 0x4b54b0 (thiscall)
};
struct IResMgr {
virtual void m0();
virtual void m1();
virtual void m2();
virtual void m3();
    virtual bool m4(void* key, AutoRefCount* hA, AutoRefCount* hB, int, int, int, int, int);
};
struct NodeFC { int Type(); };                     // 0xfc7e50 (thiscall)
struct JobC {
    void AddWeakDependency(int t);                 // 0x6913c0 (thiscall)
    bool Continuation(void* fn, void* ctx);        // 0x68f9f0 (thiscall)
};
struct TerrainSphere {
    char pad0[0x100];
    RefObj* handle;            // +0x100
    RefVec_s0076_5f80 vec;                // +0x104
    char pad1[0x19c - 0x110];
    bool RequestPaintDecalsFromModels(void* job);
};
struct IStream {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
virtual void s8();
virtual void s9();
virtual void sA();
virtual void sB();
    virtual int  sC(void* dst, int n);          // slot 0xc
};
struct Vec3Vec {
    void reserve(uint32_t n);          // 0x41e4d0 (thiscall)
    void push_back(const int* v);      // 0x4e19a0 (thiscall)
};
struct Reader {
    char pad0[0x28];
    IStream* mStream;         // +0x28
    int mField2c;             // +0x2c
    char pad1[0x19c - 0x30];
    Vec3Vec vec;              // +0x19c
    bool ReadDecalBlock(int unused);
};
extern "C" bool __cdecl ReadTriplet763340(IStream* s, int* p, int io);   // 0x763340
struct IFactorySrc {
virtual void f0();
virtual void f1();
virtual void f2();
virtual void f3();
    virtual void* f4();   // +0x10
};
struct Factory {
    char pad[0x8];
virtual void g0();
virtual void g1();
virtual void g2();
virtual void g3();
virtual void g4();
virtual void g5();
virtual void g6();
virtual void g7();
virtual void g8();
virtual void g9();
    virtual bool g9call(int* src, void* res, int a, int b);   // +0x24
    bool CreateResource(int* src, void** out, int a, int b);
};
// ---- items of slice s00765f80 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
bool __stdcall CreateByType(void** out, uint32_t type, int sub);  // 0x007666a0 (stays in the slice: not this object's)

// ---- items of slice s00766fa0 begin (TODO(rewrite): local stubs, replace by canonical classes)
bool __stdcall FUN_00764320(void* a, void* b, void* c);
struct PaintHolder {
    char pad[0x20];
    bool FUN_00767170(void* a, void* b, void* c);
};
extern char g_file[];
extern "C" bool __cdecl ReadValue(void* stream, void* dst, int n);                     // 0x93a6c0
extern "C" bool __cdecl WriteValue(void* stream, const void* src, int n);              // 0x93a890
extern "C" bool __cdecl ReadTripletG(void* stream, void* dst, int n);                  // 0x692740
extern "C" void* __cdecl Alloc6(uint32_t size, const char* name, int a, int b, const char* file, int line); // 0xf473a0
extern "C" void  __cdecl Dealloc(void* p);                                             // 0xf47380
extern "C" void  __cdecl FUN_005965b0(void* out);
extern "C" void  __cdecl FUN_00764ff0(void* a, void* b, void* c, void* d);
extern "C" void  __cdecl FUN_00757fb0(void* a, void* b, void* c);
extern "C" void  __cdecl FUN_007664b0(void* a, void* b, void* c);
extern "C" void* __cdecl FUN_00765230(void* a, void* b, void* c, void* d);
extern "C" void* __cdecl FUN_00757ee0(void* a, void* b, void* c);
extern "C" void* __cdecl FUN_00757f70(void* a, void* b, void* c);
extern "C" void  __cdecl FUN_00763f50(void* a, void* b, void* c);
extern "C" void  __cdecl FUN_0068f9b0(void* p);
extern "C" void  __cdecl FUN_006909b0(void* p);
extern "C" void* __cdecl FUN_0067dd60(void);                                           // 0x67dd60
extern "C" bool  __cdecl FUN_0071f8f0(void* stream, void* out);
extern "C" int   __cdecl FUN_0071ddc0(void* obj, int a, int b, int c, int d);
extern "C" void  __cdecl Reserve765a10(void* vec, uint32_t n);                         // 0x765a10
extern "C" void  __cdecl VPtrPush(void* vec, const void* v);                           // 0x766910
extern "C" void* __cdecl Fake78050(int v);                                             // 0x778050 table lookup
extern "C" void* __cdecl ResolveColorSlot(void* a, void* b);                           // 0x7633a0
extern "C" void* __cdecl FUN_007640c0(void* p);      // 0x7640c0
int   __fastcall JobRelease(void* self, int);                    // 0x690120
void  __fastcall JobInit(void* self, int, void* arg);            // 0x68f9b0
void  __fastcall JobAddDep(void* self, int, void* dep);          // 0x691380
void  __fastcall JobGetStatus(void* self, int);                  // 0x6909b0
void  __fastcall CtorEditor(void* self, int);                    // 0x40d010
void  __fastcall VecResizeInt(void* self, int, int count, void* value);  // 0x767700
void* __stdcall LockedAlloc(int size, int, int, int, int, int); // 0x9289f0
void  __fastcall GetImageResource2(void* self, int, int img);    // 0x576650
void  __fastcall RefVecPush2(void* self, int, void** p);         // 0x41ef20
void  __fastcall RemoveRC2(void* self, int, void* p);            // 0x714050
bool  __cdecl HasRoom(void* stream, int a, int b);               // 0x93a890
struct PaintObj {
    uint32_t mVersion;        // +0
    uint32_t mA;              // +4
    uint32_t mB;              // +8
    uint32_t mC;              // +0xc
    uint32_t mFlags;          // +0x10
    uint32_t mD;              // +0x14
    unsigned char mByte18;    // +0x18
    uint32_t mCount;          // +0x1c
    char mVec0[0x58];         // +0x20
    char mVec1[0x24];         // +0x78
    void Destroy();           // 0x765ac0
};
struct PaintReaderFactory { bool ReadPaintStuff(PaintObj*, void*, void*); }; // 0x00766fa0
struct F67270 {
    char pad0[0xc];
    int mC;                   // +0xc
    char pad10[4];
    int m14;                  // +0x14
    char pad18[0x10];
    void* m28;                // +0x28
    char m2c[8];              // +0x2c
    void Method(int);
};
struct VBig2 {
    char* b;
    char* e;
    char* c;
    void Resize(uint32_t n);
    void InsertGrow(char* pos, uint32_t n, void* value);  // 0x7662d0
};
struct V7c { char* b; char* e; char* c; void Insert(int, char*, uint32_t, char*); };
struct JobOwner {
    char pad[4];
    bool BuildJob(int* a, int* b, unsigned char c);
};
// ---- items of slice s00766fa0 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
bool __stdcall ReadPaintStuff(PaintObj* obj, void* stream, void* p3);  // 0x00766fa0 (stays in the slice: not this object's)

// ---- items of slice s00767ee0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  __cdecl FUN_0041f2d0(void* p);                                        // 0x41f2d0
void __cdecl UnionDestroy(void* p, int type);          // 0x7668c0
void __fastcall FUN_007642c0(void* self);              // 0x7642c0
struct Raster_s0076_7ee0 {
    char pad0[4];
    int mFlags;               // +0x4
    char pad8[4];
    unsigned short mWidth;    // +0xc
    unsigned short mHeight;   // +0xe
    unsigned char mLevels;    // +0x11
    unsigned char mFace;      // +0x12
};
struct C68200 {
    char pad[0xd0];
    int mD0;                  // +0xd0
    void Release();
};
struct C68240 {
    void* m0;                 // +0x00
    void* m4;                 // +0x04
    void* m8;                 // +0x08
    int   mc;                 // +0x0c
    void* m10;                // +0x10
    int   m14;                // +0x14
    char  m18[0x7c];          // +0x18 inline storage
    C68240(void* arg);
    // 0x00767760 takes this in ecx (0x767762 mov %ecx,%edi; reads 0x0/0x4(%edi)) and the count as
    // its single stack argument, so it must be called as a member, not as a cdecl free function.
    void RegisterJob(void* arg);                               // 0x00767760
};
struct Tmp7c {
    char raw[0x7c];
    void Init(int v);          // 0x00764760
    void Destroy();            // 0x0041F2D0
};
struct V7cB {
    char* b; char* e; char* c;
    void Resize(uint32_t n);
    // Both helpers take the vector in ecx and all their arguments on the stack:
    // 0x7682ea pushes value (the stack temp), count and e, then sets %ecx before calling 0x767350.
    void InsertFill(char* pos, uint32_t n, void* value);       // 0x00767350
    void DestroyRange(char* first, char* last);                // 0x00700670
};
struct AtomicInt_s0076_7ee0 {
    volatile long mValue;
    AtomicInt_s0076_7ee0(long n = 0) { _InterlockedExchange(&mValue, n); }
};
struct BakeIRef {
    virtual int AddRef() = 0;
    virtual int Release() = 0;
    virtual ~BakeIRef() {}
};
struct BakeLayer : BakeIRef {
    virtual void DrawLayer() = 0;
};
struct BakeRef {
    virtual ~BakeRef() {}
    AtomicInt_s0076_7ee0 mRefCount;
};
struct IObj_s0076_7ee0 {
    virtual void v0();
    virtual int  AddRef();
    virtual int  Release();
    virtual int  GetKind();
    virtual void v4();
    virtual void v5();
    virtual IObj_s0076_7ee0* GetChild();
};
struct IRefB {
    virtual int AddRef() = 0;
    virtual int Release() = 0;
};
template <class T>
struct AutoRef_s0076_7ee0 {
    T* mpObject;
    AutoRef_s0076_7ee0() : mpObject(0) {}
    AutoRef_s0076_7ee0(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRef_s0076_7ee0() { if (mpObject) mpObject->Release(); }
    AutoRef_s0076_7ee0& operator=(T* p) {
        if (p != mpObject) {
            T* old = mpObject;
            if (p) p->AddRef();
            mpObject = p;
            if (old) old->Release();
        }
        return *this;
    }
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
};
struct UnionState {
    char mBytes[0xd0];
    int  mType;
    UnionState() : mType(0) {}
    ~UnionState();
};
UnionState::~UnionState()
{
    if (mType) {
        if (mType == 5) FUN_007642c0(mBytes);
        else            UnionDestroy(mBytes, mType);
        mType = 0;
    }
}
struct VecA {
    IRefB** mpBegin;                    // +0x00
    IRefB** mpEnd;                      // +0x04
    IRefB** mpCapacity;                 // +0x08
    uint32_t mAllocator[2];             // +0x0c
    uint32_t mFlag;                     // +0x14
    void*   mStorage[0x80 / 4];         // +0x18
    VecA()
    {
        mpBegin = (IRefB**)mStorage;
        mpEnd   = mpBegin;
        mFlag = 0;
        mpCapacity = (IRefB**)((char*)mpBegin + 0x80);
    }
    ~VecA();                            // 0x4b5440
};
struct VecB {
    void** mpBegin;                     // +0x00
    void** mpEnd;                       // +0x04
    void** mpCapacity;                  // +0x08
    uint32_t mAllocator[2];             // +0x0c
    uint32_t mFlag;                     // +0x14
    void*  mStorage[0x180 / 4];         // +0x18
    VecB()
    {
        mpBegin = mStorage;
        mpEnd   = mpBegin;
        mFlag = 0;
        mpCapacity = (void**)((char*)mpBegin + 0x180);
    }
    ~VecB()
    {
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            Dealloc(mpBegin);
    }
};
void* operator new(unsigned size, const char* name, int, int, int, int);
struct Child : IObj_s0076_7ee0 {
    Child(int, int, IObj_s0076_7ee0*);             // 0x93b530
    char mPad[0x30];                    // sizeof == 0x34
};
class C68370 : public BakeLayer, public BakeRef {
public:
    virtual int  AddRef();
    virtual int  Release();
    virtual void DrawLayer();

    C68370(IRefB* a, IObj_s0076_7ee0* b, int* c, IObj_s0076_7ee0* d, int e);
    ~C68370();

    AutoRef_s0076_7ee0<IObj_s0076_7ee0> m_pC;                 // +0x0c
    AutoRef_s0076_7ee0<IObj_s0076_7ee0> m_pE;                 // +0x10
    AutoRef_s0076_7ee0<IRefB> m_pA;                // +0x14
    int   m_v18;                        // +0x18
    int   m_v1c;                        // +0x1c
    int   m_v20;                        // +0x20
    int   m_v24;                        // +0x24
    AutoRef_s0076_7ee0<IObj_s0076_7ee0> m_p28;                // +0x28
    UnionState m_state;                 // +0x2c
    AutoRef_s0076_7ee0<IRefB> m_100;               // +0x100
    VecA  m_vecA;                       // +0x104
    VecB  m_vecB;                       // +0x19c
    char  m334;                         // +0x334
};
// ---- items of slice s00767ee0 end

// ---- items of slice s007689a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint;
struct Key { uint a, b, c; };       // 12-byte resource key (read from owner+8)
struct Stream {                     // EA::IO::IStream; Write is slot 0x38
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
    virtual void s20(); virtual void s24(); virtual void s28(); virtual void s2c();
    virtual void s30(); virtual void s34();
    virtual bool Write(const void* p, uint n);                  // +0x38
};
struct LockedRegion { void* data; uint a, b; };
struct VDesc {                      // rw::graphics::VertexDescriptor
    char p0[0xc];
    uint16_t numElements;           // +0xc
    uint8_t lockFlags;              // +0xe
    uint8_t stride;                 // +0xf
    char p1[8];
    char elements[1];               // +0x18, 12 bytes each
    uint8_t GetStride() const { return stride; }
    void Finish();                  // 0x011f3220
};
struct VBuf {                       // rw::graphics::VertexBuffer
    VDesc* desc;
    uint p4, base, numVertices;
    uint Bytes(uint n) const { return desc->GetStride() * n; }
    void* Lock(uint flags, uint off, uint size);               // 0x011f3620 (ret 0xc)
    void Unlock();                                             // 0x011f36a0
};
struct IBuf {                       // rw::graphics::IndexBuffer
    uint p0, p4, numIndices, pc, p10, primType;
    uint GetDepth();                                           // 0x011f4fb0
    IBuf* Lock(uint flags, LockedRegion* r);                   // 0x011f4f20 (ret 8)
    void Unlock(LockedRegion* r);                              // 0x011f4fd0 (ret 4)
};
struct MeshEntry {                  // element of Model+0x18
    char p0[8];
    IBuf* ib;                       // +0x08
    char p1[0x18];
    VBuf* vb;                       // +0x24
};
struct KeyOwner { char p0[8]; Key key; };   // Key at +8
struct SubObj { char p0[0x74]; KeyOwner* owner; char p1[0x7c - 0x78]; };   // 0x7c bytes
struct Pair8 { uint a, b; };
struct sp_alloc { uint d[2]; };
template<class T> struct PVec {
    T* b; T* e; T* cap; sp_alloc a;      // 0x14 bytes
    T& operator[](uint i) { return b[i]; }
    uint size() const { return (uint)(e - b); }
};
struct Model {
    char p0[8];
    char ctx[0x10];                 // +0x08 (passed to the material manager)
    PVec<MeshEntry*> meshes;        // +0x18
    char q0[0x40 - 0x2c];
    PVec<IBuf*> ibs;                // +0x40
    char q1[0x68 - 0x54];
    PVec<VBuf*> vbs;                // +0x68
    char q2[0x90 - 0x7c];
    PVec<VDesc*> descs;             // +0x90
    char q3[0xb8 - 0xa4];
    PVec<void*> mats;               // +0xb8
    char q4[0xe0 - 0xcc];
    PVec<Pair8> pairs;              // +0xe0 (8-byte elements)
    PVec<void*> bvhs;               // +0xf4
    PVec<SubObj> subs;              // +0x108 (0x7c-byte elements)
    char block18[0x18];             // +0x11c
    char pad134[4];                 // +0x134
    char pad138[4];
    KeyOwner* extra;                // +0x13c
};
namespace SP {
struct cGraphicsResourceFactory_s0076_89a0 {
    bool WriteResourceGameModel(Model* m, Stream* s);           // 0x007689a0 (ret 8)
    bool WriteResourceGameMeshes(void* obj, Stream* s);         // 0x00764f60
    bool WriteResourceRaster(void* obj, Stream* s);             // 0x00767ee0
    bool WriteResourceRasterArena(void* obj, Stream* s);        // 0x00763a80
    bool BuildJob(void* obj, void* a, uint flag);               // 0x00767590
    void WriteMaterialRef(Stream* s, void* p);                  // 0x007656c0 (ret 8)
    void WriteTail(Stream* s, Model* m);                        // 0x00764430 (ret 8)
    bool WriteResource(void* obj, void* src, void* u3, void* u4);   // 0x00769200 (ret 0x10)
};
}
typedef SP::cGraphicsResourceFactory_s0076_89a0 Factory_s0076_89a0;
struct IFactorySrc_s0076_89a0 {
    virtual void f0(); virtual void f1(); virtual void f2(); virtual void f3();
    virtual void f4(); virtual void f5(); virtual Stream* GetStream();   // +0x18
};
struct IRefObj {                                   // slots +4 AddRef, +8 Release
    virtual void v0(); virtual void AddRef(); virtual void Release();
};
struct StreamRef {                                 // EA::AutoRefCount<Stream>
    Stream* p;
    StreamRef(Stream* x) : p(x) { if (p) ((IRefObj*)p)->AddRef(); }
    ~StreamRef() { if (p) ((IRefObj*)p)->Release(); }
};
// ---- items of slice s007689a0 end

// ---- items of slice s00769310 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" char  __cdecl FUN_00767170(void* a, void* b, void* c);                      // 0x767170
extern "C" char  __cdecl ReadMaterialList(void* a, void* b, void* c);                  // 0x767c80
extern "C" void  __cdecl FUN_007006d0(void* p);                                        // 0x7006d0
extern "C" char  __cdecl FUN_007638a0(void* a, void* b, void* c, void* d);             // 0x7638a0
extern "C" char  __cdecl FUN_00769310b(void* a, void* b, void* c, void* d);            // 0x769310
extern "C" void* __cdecl FUN_0093b530(int a, int b, void* c);                          // 0x93b530
struct M69310 { char Meth(int a, int b, int c); };
struct cGraphicsResourceFactory {
    char ReadResourceFromStream(int* src, void* a2, int* obj, uint32_t kind);

    char ReadPCAWeights(void* holder, void* a2, void* obj);            // 0x763950
    char ReadVia69cf0(void* holder, void* a2, void* obj);              // 0x769cf0
    char ReadMaterialList_(void* holder, void* a2, void* obj);         // 0x767c80
    char ReadVia64ce0(void* holder, void* a2, void* obj);              // 0x764ce0
    char ReadVia637d0(void* holder, void* a2, int four, void* obj);    // 0x7637d0
    char ReadVia67170(void* holder, void* a2, void* obj);              // 0x767170
};
// ---- items of slice s00769310 end

// ---- items of slice s00769f20 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl Node8F4d0(void);                                             // 0x68f4d0
extern "C" void* __cdecl FUN_0067de70();                                              // 0x67de70
extern "C" char  __cdecl FUN_00769d80v(void* a, void* b, void* c, void* d);           // 0x769d80
extern "C" char  __cdecl FUN_007655f0b(void* a, void* b, void* c);   // 0x7655f0
extern "C" bool  __fastcall ArmDecodeB(void* self, int, int);         // 0x7677c0
extern "C" char  __cdecl FUN_0076a940v(void* a, void* b, void* c, void* d, void* e);   // 0x76a940
struct M69d80 { char Meth(int a, int b, int c); };
struct cJob;
struct JobRefL_s0076_9f20;
struct cJob {
    void* mpCallback;              // +0x00
    void* mpCallbackData;          // +0x04
    char pad08[0x10];
    uint32_t mFlags;               // +0x18
    void SetCallback(void* f, void* d) { mpCallback = f; mpCallbackData = d; }
    int  AddRef();                 // 0x0068f950
    int  Release();                // 0x00690120
    void SetExtra(void* owner);    // 0x0068f9b0
    void Submit();                 // 0x006909b0
    void AddDependency(cJob* other);       // 0x00691380
    void AddWeakDependency(cJob* other);   // 0x006913c0
};
struct JobRefL_s0076_9f20 {
    cJob* p;
    JobRefL_s0076_9f20() : p(0) {}
    ~JobRefL_s0076_9f20() { Reset(); }
    void Reset() { if (p) { cJob* t = p; p = 0; t->Release(); } }
};
struct IJobMgr_s0076_9f20 {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
    virtual bool CreateJob(JobRefL_s0076_9f20* out);     // slot 4 (+0x10)
virtual void v5();
virtual void v6();
virtual void v7();
    virtual void Lock();                      // slot 8 (+0x20)
    virtual void Unlock();                    // slot 9 (+0x24)
};
struct JobLockTable {
    bool TryLockJobs(JobRefL_s0076_9f20* a, JobRefL_s0076_9f20* b); // 0x0068f350
};
struct IConvCtx {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
    virtual RecInfo* Info();          // slot 4 (+0x10)
virtual void v5();
virtual void v6();
virtual void v7();
    virtual void Begin();             // slot 8 (+0x20)
    virtual void End();               // slot 9 (+0x24)
};
struct IRefObj_s0076_9f20 {
    virtual void AddRef();
    virtual void Release();
};
struct Grf {
    char pad0[0xc];
    void* pC;                      // +0x0c
    IConvCtx* p10;                 // +0x10
    char pad14[4];
    uint32_t type18;               // +0x18
    char pad1c[0xe0];
    uint32_t stateFC;              // +0xfc
};
struct ConvObj { void* Init(void* res, void* a, void* b, void* c, void* d); }; // 0x00768370
struct AsyncResMgr { bool AllocateRequest(void* type, IRefObj_s0076_9f20** req, JobRefL_s0076_9f20* job); }; // 0x006af150
char __fastcall StartReqA(void* self, int, void** out);   // 0x007652c0
char __fastcall StartReqB(void* self, int, void** out);   // 0x00765b30
char __fastcall StartReqC(void* self, int, void** out);   // 0x00765d30
char __fastcall CreateByType(void* self, int, void** out, void* p5, uint32_t type); // 0x007666a0
static __forceinline IJobMgr_s0076_9f20* GetJobManager_s0076_9f20() { return (IJobMgr_s0076_9f20*)Node8F4d0(); }
static __forceinline bool CreateJobInto(IJobMgr_s0076_9f20* jm, JobRefL_s0076_9f20& r) {
    r.Reset();
    return jm->CreateJob(&r);
}
static __forceinline JobLockTable* LockTable(void* self) {
    return *(JobLockTable**)((char*)*(void**)((char*)self + 0xc) + 8);
}
// ---- items of slice s00769f20 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
bool __fastcall SetupJobChain(void* self, int, int unused);  // 0x00769f20 (stays in the slice: not this object's)
bool __fastcall CreateRequestJob(void* self, int, void* out);  // 0x0076a400 (stays in the slice: not this object's)
bool __fastcall TryLockChain(void* self, int, int unused);  // 0x0076a4d0 (stays in the slice: not this object's)

// ---- items of slice s00761dc0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  __cdecl operator_delete_(void* p);
extern "C" void* __cdecl FUN_00928a30(void* a, void* b, int c, int d, int e, int f, int g, int h);
extern "C" void* __cdecl FUN_011f51d0(void* p, ...);
extern "C" void* __cdecl FUN_011f36d0(void* p, int a, int b, int c);
extern "C" void* __cdecl FUN_011f5010(void* p, int a, int b, int c, int d, int e);
void __fastcall FUN_011f3580(void* p);  // 0x011f3580
void __fastcall FUN_011f4e90(void* p);  // 0x011f4e90
namespace SP {
struct Alloc16c8b44 {
    void  Free(void* p);
    void* allocate(int a, int b, int c, int d, int e, int f, int g, int h);
};
}
extern SP::Alloc16c8b44* g_alloc;
struct Map262890 {
    char pad0[4];
    void* buckets;               // +0x4
    unsigned int bucketCount;    // +0x8
    unsigned int count;          // +0xc
    int erase(unsigned int* key);   // @ 0x762890
};
extern Map262890 g_map1538ff0;
extern Map262890 g_map1539010;
struct Iter { void* node; void* bucket; unsigned char inserted; char pad[3]; };   // eastl hashtable iterator
struct Hash262b00 {
    char pad0[4];
    void* buckets;               // +0x04
    unsigned int bucketCount;    // +0x08
    void find(Iter* out, const void* key);   // 0x00db4780
    int findInsert(unsigned int* key);       // @ 0x762b00
};
// ---- items of slice s00761dc0 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void* __stdcall MakeObj762f30(const int* src);  // 0x00762f30 (stays in the slice: not this object's)

// @ 0x00683f10
int RefCounted::AddRef()
{
    return (int)((_InterlockedExchangeAdd((volatile long*)&mRef, 2) + 2) >> 1);
}

// @ 0x00762890
int Map262890::erase(unsigned int* key)
{
    unsigned int before = count;
    unsigned int b = *key % bucketCount;
    unsigned int* slot = (unsigned int*)((char*)buckets + b * 4);
    if (*slot != 0) {
        unsigned int* e;
        do {
            e = (unsigned int*)*slot;
            if (*key == *e) break;
            slot = e + 4;
        } while (e[4] != 0);
        while (*slot != 0 && *key == **(unsigned int**)slot) {
            unsigned int* cur = (unsigned int*)*slot;
            *slot = cur[4];
            operator_delete_(cur);
            count--;
        }
    }
    return (int)(before - count);
}

// @ 0x00762a00
void __cdecl FUN_00762a00(void* p)
{
    unsigned int key = (unsigned int)p;
    g_map1538ff0.erase(&key);
    FUN_011f3580(p);
    g_alloc->Free(p);
}

// @ 0x00762a30
void __cdecl FUN_00762a30(void* p)
{
    unsigned int key = (unsigned int)p;
    g_map1539010.erase(&key);
    FUN_011f4e90(p);
    g_alloc->Free(p);
}

// @ 0x00762b70
void* __cdecl FUN_00762b70(int a, int b, int c, void* out)
{
    int desc[8];
    FUN_011f51d0(desc, a, b, c);
    int local[4];
    local[0] = (int)FUN_00928a30((void*)desc[0], (void*)desc[4], 0, 0, 0, 0, 0, 0);
    local[1] = 0; local[2] = 0; local[3] = 0;
    void* r = FUN_011f36d0(local, a, b, c);
    int zeroKey[3] = { 0, 0, 0 };
    int* src = out ? (int*)out : zeroKey;
    Hash262b00* h = (Hash262b00*)0x1538ff0;
    int* slot = (int*)h->findInsert((unsigned int*)&r);
    slot[0] = src[0];
    slot[1] = src[1];
    slot[2] = src[2];
    return r;
}

// @ 0x00762c60
void* __cdecl FUN_00762c60(int a, int b, int c, int d, int e, void* out)
{
    int desc[8];
    FUN_011f51d0(desc, a, b, c, d, e);
    int local[4];
    local[0] = (int)FUN_00928a30((void*)desc[0], (void*)desc[4], 0, 0, 0, 0, 0, 0);
    local[1] = 0; local[2] = 0; local[3] = 0;
    void* r = FUN_011f5010(local, a, b, c, d, e);
    int zeroKey[3] = { 0, 0, 0 };
    int* src = out ? (int*)out : zeroKey;
    Hash262b00* h = (Hash262b00*)0x1539010;
    int* slot = (int*)h->findInsert((unsigned int*)&r);
    slot[0] = src[0];
    slot[1] = src[1];
    slot[2] = src[2];
    return r;
}

// @ 0x00762fa0
void* Map762fa0::Insert(void* out, const void* key)
{
    unsigned __int64 node8 = *(const unsigned __int64*)((char*)this + 0);
    void* slot = F_68c140(&node8);
    if (slot == 0) {
        void* obj = MakeObj762f30((const int*)key);
        F_68c1b0(out, (unsigned __int64)(size_t)obj);
        return out;
    }
    for (;;) {
        void* e = F_68c140(&node8);
        unsigned __int64 inner = *(unsigned __int64*)((char*)e + 8);
        void* cur = F_68c140(&inner);
        unsigned __int64 oldv = *(unsigned __int64*)&node8;
        (void)cur; (void)oldv;
        unsigned __int64 nw = node8 + 1;
        unsigned __int64 prev = *(volatile unsigned __int64*)((char*)this + 0);
        if (_InterlockedCompareExchange64((volatile __int64*)((char*)this + 0),
                (__int64)nw, (__int64)prev) == (__int64)prev) {
            unsigned __int64 z = 0;
            F_68c1b0(&z, 0);
            void* e3 = F_68c140(&node8);
            *(int*)((char*)e3 + 8)  = (int)(nw & 0xffffffffu);
            *(int*)((char*)e3 + 0xc) = (int)(nw >> 32);
            if (key) {
                *(int*)((char*)e3 + 0) = *(const int*)key;
                *(int*)((char*)e3 + 4) = *((const int*)key + 1);
            }
            *(unsigned __int64*)out = node8;
            return out;
        }
    }
}

// @ 0x00763100
CEditorRes::CEditorRes()
{}

// @ 0x00763130
void Map762fa0::Append(const void* key)
{
    int out[2];
    Insert(out, key);
    const int* k = (const int*)key;
    unsigned __int64 node8 = *(const unsigned __int64*)k;
    for (;;) {
        void* e = F_68c140(&node8);
        unsigned __int64 inner = *(unsigned __int64*)((char*)e + 8);
        void* e2 = F_68c140(&inner);
        *(int*)((char*)e2 + 8) = k[0];
        *(int*)((char*)e2 + 0xc) = k[1];
        unsigned __int64 nw = node8 + 1;
        unsigned __int64 prev = *(volatile unsigned __int64*)((char*)this + 8);
        if (_InterlockedCompareExchange64((volatile __int64*)((char*)this + 8),
                (__int64)nw, (__int64)prev) == (__int64)prev)
            return;
    }
}

// @ 0x00763250
int __fastcall Release763250(void* self)
{
    void* p = self;
    volatile int* rc = (volatile int*)((char*)p + 4);
    int n = _InterlockedExchangeAdd((volatile long*)rc, -2) - 2;
    if (n == 0) {
        _InterlockedExchange((volatile long*)rc, 2);
        int tid = (int)__readfsdword(0x18);
        if (g_flags1630180 != 0 || g_word160077c != tid) {
            Map762fa0* map = (Map762fa0*)GetGlobal67de80();
            int key[2];
            key[0] = (int)p;
            key[1] = 0x762f10;
            map->Append(key);
        } else if (p != 0) {
            ((IObj*)p)->s2(1);
        }
    } else if (n == 3) {
        char* slot = (char*)p + 0x14;
        if (*(void**)slot != 0) {
            _ReadWriteBarrier();
            void* cb = *(void**)slot;
            void* fn = *(void**)*(void**)cb;
            ((void(__thiscall*)(void*, void*))fn)(cb, p);
        }
    }
    return n;
}

// @ 0x007632f0
void __cdecl SwapRasterMode(char sel, int v)
{
    if (GetGlobal67dd60() != 0) {
        void* o = GetGlobal67dd60();
        void** vt = *(void***)o;
        if (sel) {
            void* fn = vt[0x6c / 4];
            ((void(__thiscall*)(void*, int))fn)(o, v);
            void* mm = MaterialManager();
            void** mvt = *(void***)mm;
            void* mfn = mvt[0x50 / 4];
            ((void(__thiscall*)(void*, int))mfn)(mm, v);
        } else {
            void* fn = vt[0x70 / 4];
            ((void(__thiscall*)(void*, int))fn)(o, v);
            void* mm = MaterialManager();
            void** mvt = *(void***)mm;
            void* mfn = mvt[0x54 / 4];
            ((void(__thiscall*)(void*, int))mfn)(mm, v);
        }
    }
}

// @ 0x00763340
bool __cdecl ReadRasterTriplet(void* stream, int* p, int io)
{
    return EA_IO_ReadInt32(stream, p, 1, io)
        && EA_IO_ReadInt32(stream, p + 2, 1, io)
        && EA_IO_ReadInt32(stream, p + 1, 1, io);
}

// @ 0x007633a0
void __cdecl ResolveColor(Color3* out, KeyDef* def)
{
    void* p = g_sAppProperties;
    if (*(int*)((char*)(*(int*)((char*)p + 0x3c)) + 0x130) != 0) {
        int key = def->key;
        if ((key & 0xc0000000u) == 0x40000000u
            && (key & 0xff00u) == 0x2900u
            && (key & 0xffu) != 0
            && (unsigned)((((unsigned)key >> 16) & 0xff) - 0x61) <= 5u) {
            switch (((unsigned)key >> 16) & 0xff) {
            case 0x61: case 0x62: case 0x66:
                *out = g_colors[2];
                return;
            case 0x63: case 0x64: case 0x65:
                *out = g_colors[key & 0xff];
                return;
            }
        }
    }
    *out = *(Color3*)def;
}

// @ 0x00763490
unsigned char __cdecl ArenaWrite(void* buf, int n, unsigned total)
{
    unsigned char ok = 1;
    if (g_arena16303f0 == 0)
        return 0;
    if (g_arena16303f4 != 0)
        *(int*)g_arena16303f4 += n + total;
    if (total != 0) {
        while (total != 0) {
            unsigned chunk = total;
            if (total > 0x20)
                chunk = 0x20;
            ok = ((Arena_s0076_2d70*)g_arena16303f0)->f(g_140e00c, chunk);
            total -= chunk;
            if (!ok)
                return 0;
        }
        if (!ok)
            return 0;
    }
    if (n != 0)
        ok = ((Arena_s0076_2d70*)g_arena16303f0)->f(buf, n);
    return ok;
}

// @ 0x00763520
bool SP::cGraphicsResourceFactory::Shutdown()
{
    RemoveRegistrationCallback(0x2f4e681b, (void*)0x7632f0);
    return true;
}

// @ 0x00763550
unsigned int SP::cGraphicsResourceFactory::GetSupportedTypes(unsigned int * types, unsigned int n)
{
    unsigned int count = 8;
    if (types != 0) {
        if (n >= count) {
            memcpy(types, (void*)0x140dfe0, 32);
        } else {
            return 0;
        }
    }
    return count;
}

// @ 0x00763580
bool __stdcall IsRegType(unsigned a, int b)
{
    if (b == 0x2f4e681c && a >= 0x2f4e681b) {
        if (a <= 0x2f4e681c || a == 0x2f7d0004)
            return true;
    }
    return false;
}

// @ 0x007635b0
EhHolder::~EhHolder()
{}

// @ 0x00763620
bool __stdcall LoadRasterHeader(cRasterFromGimexLoadState_s0076_2d70* s, const char* name, void* unused)
{
    StreamObj stream;
    F_87cde0(&stream);
    if (!F_87ce00(&stream, name)) {
        F_87d070(&stream);
        return false;
    }
    char inner[4];
    if (!F_87d0b0(&stream, (void*)name, inner)) {
        F_87d070(&stream);
        return false;
    }
    GimexRecord* rec = (GimexRecord*)F_87ced0(&stream, 0);
    bool ok = false;
    if (rec != 0 && rec->mBpp == 0x20) {
        s->mWidth  = rec->mWidth;
        s->mHeight = rec->mHeight;
        s->mBpp    = 0x20;
        s->mPitch  = rec->mWidth * 4;
        s->mSize   = s->mPitch * s->mHeight;
        s->mData   = (unsigned char*)EA_New_s0076_2d70(s->mSize, (const char*)0x140e02c, 0, 0, 0, 0);
        ok = F_87cf00(&stream, rec, s->mData, s->mSize);
        F_87cef0(&stream, rec);
    }
    F_87ce90(&stream);
    F_87d070(&stream);
    (void)unused;
    return ok;
}

// @ 0x00763770
bool __stdcall CreateRasterFromState(cRasterFromGimexLoadState_s0076_2d70* s, int unused, OutRaster* out)
{
    if (s->mBpp == 0x20 && s->mData != 0) {
        void* r = CreateRasterFn(s->mWidth, s->mHeight, 1, 8, 0x15);
        ((Raster*)r)->D3D9GetStreamedMipLevelSize(s->mData, 0);
        EA_Delete(s->mData);
        s->mData = 0;
        out->mData = r;
        return true;
    }
    return false;
}

// @ 0x007637d0
bool RasterFactory::LoadAndCreateRaster(cRasterFromGimexLoadState_s0076_2d70* state, int a, int b, void* out3)
{
    char  buf[0x1c];
    *(int*)(buf + 0x10) = 0;
    if (!LoadRasterHeader((cRasterFromGimexLoadState_s0076_2d70*)buf, 0, 0))
        return false;
    // NB: the original allocates a small scratch vector at [esp+0x24] here
    if (!CreateRasterFromState((cRasterFromGimexLoadState_s0076_2d70*)buf, 0, 0))
        return false;
    int* src = (int*)out3;
    ((int*)b)[2] = src[0];
    ((int*)b)[3] = src[1];
    ((int*)b)[4] = src[2];
    (void)state; (void)a;
    return true;
}

// @ 0x007638a0
bool __stdcall ReadTriplets(void* stream, int, int, int)
{
    int count;
    if (!EA_IO_ReadInt32(stream, &count, 1, 0))
        return false;
    V3 v;
    v.x = 0; v.y = 0; v.z = 0;
    for (unsigned int i = 0; i < (unsigned)count; i++) {
        if (!EA_IO_ReadInt32(stream, &v.x, 1, 0))
            return false;
        if (!EA_IO_ReadInt32(stream, &v.z, 1, 0))
            return false;
        if (!EA_IO_ReadInt32(stream, &v.y, 1, 0))
            return false;
    }
    return true;
}

// @ 0x00763950
bool SP::cGraphicsResourceFactory::ReadResourcePCAWeights(EA::IO::IStream * stream, EA::ResourceMan::Resource * resource, EA::ResourceMan::Key const & key)
{
    (void)key;
    char* res = (char*)resource;
    int   hdr[6];
    int   flag = 0;
    int   tag;
    if (!EA_IO_ReadInt32(stream, &tag, 1, flag))
        return false;
    if (tag == (int)0xeeffeeff)      flag = 1;
    else if (tag == (int)0xffeeffee) flag = 0;
    else return false;
    if (!EA_IO_ReadInt32(stream, &hdr[1], 1, flag)) return false;
    if (hdr[1] != 2) return false;
    if (!EA_IO_ReadInt32(stream, &hdr[0], 1, flag)) return false;
    if (hdr[0] > 4) return false;
    int* pGroup = (int*)(res + 0x18);
    if (!EA_IO_ReadInt32(stream, pGroup, 1, flag)) return false;
    if (*pGroup > 0x3c) return false;
    if (!EA_IO_ReadInt32(stream, &hdr[2], 1, flag)) return false;
    if (hdr[2] != 0x10) return false;
    if (!EA_IO_ReadInt32(stream, &hdr[3], 1, flag)) return false;
    if (hdr[3] != 2) return false;
    int count = (*pGroup * 0x110) >> 2;
    if (!EA_IO_ReadInt32(stream, res + 0x24, count, flag)) return false;
    *(float*)(res + 4) = *(float*)0x14853e0;
    *(unsigned char*)(res + 8) = 1;
    return true;
}

// @ 0x00763a80
bool __stdcall WriteResourceArena(int* res, int flags)
{
    void* stream = *(void**)((char*)res + 0x18);
    char  scope[0x130];
    F_11e2fe0(scope);
    void* arena = 0;
    if (!F_11e3350(stream, &arena, 0)) {
        F_11e2690(scope);
        return false;
    }
    while (F_11e34d0(scope)) { }
    g_arena16303f0 = arena;
    if (!F_11e3c50(scope, (void*)0x763490)) {
        F_11e2690(scope);
        return false;
    }
    while (F_11e3940(scope)) { }
    g_arena16303f0 = 0;
    F_11e2690(scope);
    (void)flags;
    return true;
}

// @ 0x00763b80
bool __cdecl DrawRaster(void* a, int b, int c, unsigned char d)
{
    char* p = (char*)a;
    void* tex = *(void**)(p + 8);
    int   v0  = 0;
    ((void(__thiscall*)(void*, int, int, int))((*(void***)tex)[0x48 / 4]))(
        tex, *(unsigned char*)(p + 0x12), (int)d, (int)&v0);
    void* obj = (void*)v0;
    int   width  = *(unsigned short*)(p + 0xc);
    int   height = *(unsigned short*)(p + 0xe);
    char  local[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    ((void(__thiscall*)(void*, void*))((*(void***)obj)[0x30 / 4]))(obj, local);
    void* dev = *(void**)g_dev16f89d0;
    ((void(__thiscall*)(void*, int, int, int, int, int))((*(void***)dev)[0x90 / 4]))(
        dev, width, height, *(int*)local, 2, (int)local);
    ((void(__thiscall*)(void*, int))((*(void***)dev)[0x80 / 4]))(dev, v0);
    ((void(__thiscall*)(void*, void*, int, int))((*(void***)obj)[0x34 / 4]))(obj, local, 0, 0x10);
    F_11e0744((void*)b, (void*)*(int*)(local + 4), *(int*)local * height);
    ((void(__thiscall*)(void*))((*(void***)obj)[0x38 / 4]))(obj);
    ((void(__thiscall*)(void*))((*(void***)obj)[8 / 4]))((void*)v0);
    ((void(__thiscall*)(void*))((*(void***)tex)[8 / 4]))(tex);
    (void)c;
    return true;
}

// @ 0x00763c60
void UniqVec::AddUnique(int v)
{
    int n = mCount;
    if (n >= 16)
        return;
    for (int i = 0; i < n; i++) {
        if (v == mArr[i])
            return;
    }
    mArr[n] = v;
    mCount++;
}

// @ 0x00763cb0
uint32_t __cdecl FUN_763cb0(EmbeddedState* hard, RasterThing* raster)
{
    if (g_texStageRaster0 == 0) {
        typedef void* (__thiscall *FnCreate)(void*, V3u, int);
        typedef void  (__thiscall *FnRelease)(void*, void*);
        void* mgr = GetRasterMgr();
        Managed* m = (Managed*)((FnCreate)((*(void***)mgr)[0x1c / 4]))(mgr, *(const V3u*)g_texStageCreate, 0);
        if ((m->flags & 1) == 0) {
            void* mgr2 = GetRasterMgr();
            ((FnRelease)((*(void***)mgr2)[0x34 / 4]))(mgr2, m);
        }
        g_texStageRaster0 = m->value;

        mgr = GetRasterMgr();
        Managed* m2 = (Managed*)((FnCreate)((*(void***)mgr)[0x1c / 4]))(mgr, *(const V3u*)g_texStageRasterType, 0);
        if ((m2->flags & 1) == 0) {
            void* mgr2 = GetRasterMgr();
            ((FnRelease)((*(void***)mgr2)[0x34 / 4]))(mgr2, m2);
        }
        g_texStageRaster1 = m2->value;
    }

    uint32_t result = FUN_011ed690(hard, raster);

    void* props = g_sAppProperties;
    if (*(uint32_t*)((char*)(*(uint32_t*)((char*)props + 0x3c)) + 0x130) != 0) {
        uint32_t bit = 1;
        for (int stage = 0; stage < 4; ++stage, bit = _rotl(bit, 1)) {
            if ((hard->dirtyBits & bit) == 0)
                return result;
            if (stage > 0) {
                raster->FUN_00763c60(hard->GetTextureStageState(stage));
                void* r;
                if (stage == 1)
                    r = g_texStageRaster0;
                else if (stage == 2)
                    r = g_texStageRaster1;
                else
                    r = 0;
                hard->SetRaster(stage, r);
            }
        }
    }
    return result;
}

// @ 0x00763df0
int __cdecl FUN_763df0(void* a, void* b)
{
    void* p = g_sAppProperties;
    int c = *(int*)((char*)p + 0x3c);
    if (*(int*)((char*)c + 0x130) != 0) {
        int n = *(int*)((char*)b + 0x134);
        int i = 0;
        if (n > 0) {
            int* arr = (int*)((char*)b + 0x138);
            do {
                if (a == (void*)*arr) {
                    *(int*)((char*)a + 8) = 0;
                    return 1;
                }
                i++;
                arr++;
            } while (i < n);
        }
    }
    return FUN_011f06c0(a, b);
}

// @ 0x007640c0
void* __fastcall FUN_7640c0(void* self)
{
    uint32_t* p = (uint32_t*)self;
    p[0] = 0x013f1ab0;                 // first vtable (primary base)
    p[1] = 0x013ef094;                 // second vtable (secondary base)
    _InterlockedExchange((volatile long*)(p + 2), 0);   // atomic refcount init at +8
    p[0] = 0x0140e044;                 // final first vtable
    p[1] = 0x0140e040;                 // final second vtable
    p[3] = 0;                          // +0x0c
    p[4] = 0;                          // +0x10
    *((uint8_t*)p + 0x18) = 1;         // +0x18
    return self;
}

// @ 0x007641c0
bool SP::cGraphicsResourceFactory::Init()
{
    AddRegistrationCallback(0x2f4e681b, (void*)0x7632f0);
    void* t = ArenaTypeRegGetType(0x20003);
    *(void**)((char*)t + 0xc) = (void*)0x763df0;
    t = ArenaTypeRegGetType(0x2000b);
    *(void**)((char*)t + 0xc) = (void*)0x763cb0;
    void* m = GetManager();
    ((void(__thiscall*)(void*, int, void*, int))(*(void***)m)[0x24 / 4])(m, 0x2f4e681c, kRasterRecordTypes, 3);
    return true;
}

// @ 0x00764220
Arena98::Arena98()
{}

// @ 0x007642c0
D7642c0::~D7642c0()
{}

// @ 0x00764320
unsigned char __stdcall FUN_764320(RasterLoadState* s, void* unused, OutRec* out)
{
    RasterObj* r = (RasterObj*)SP_CreateRaster(s->w, s->h, s->nml, s->tp, s->fm);
    uint32_t idx = 0;
    for (uint32_t j = 0; j < (uint32_t)s->nml; j++) {
        for (uint32_t i = 0; i < s->numFaces; i++) {
            if (s->isCube) r->face = (uint8_t)i;
            r->SetMipLevelData(s->pix[idx], j);
            FreeMem(s->pix[idx]);
            s->pix[idx] = 0;
            idx++;
        }
    }
    if (s->isCube) r->face = 0;
    out->raster = r;
    return 1;
}

// @ 0x00764430
unsigned char __stdcall FUN_764430(WStream* s, RecSrc* o)
{
    uint32_t count = (int)(o->end - o->begin) / 0x7c;
    s->Write(&count, 4);
    uint32_t off = 0;
    for (uint32_t i = 0; i < count; i++) {
        Rec7c* r = (Rec7c*)(o->begin + off);
        s->Write(r, 0x38);
        s->Write(r->b, 0x38);
        s->Write(&r->f70, 4);
        P74* q = r->p74;
        if (q) {
            volatile V3u t;
            t.x = ((volatile T3*)&q->v)->x;
            t.y = ((volatile T3*)&q->v)->y;
            t.z = ((volatile T3*)&q->v)->z;
            s->Write((const void*)&t, 0xc);
        } else {
            T3 u(0xffffffff, 0xffffffff, 0xffffffff);
            s->Write(&u, 0xc);
        }
        uint32_t flag = r->p78 != 0;
        s->Write(&flag, 4);
        if (r->p78) {
            uint32_t n;
            void* d = r->p78->GetChildID(&n);
            s->Write(&n, 4);
            s->Write(d, n * 0xa0);
        }
        off += 0x7c;
    }
    return 1;
}

// @ 0x00764580
bool SP::cGraphicsResourceFactory_s0076_3cb0::FixupArena(ArenaOwner* p)
{
    ArenaIter it;
    void* a = p->arena;
    int flag = 1;
    if (ArenaStart(a, &it, p, &flag)) {
        while (FixupNext(&it)) {}
        if (flag) return true;
        while (DestructNext(&it)) {}
    }
    return false;
}

// @ 0x00764670
static __forceinline void* PoolAlloc(uint32_t n)
{ return g_pSPMemPool->LockedAlloc(n, 0, 0, 0, 0, 0); }

// @ 0x007646a0
void Loader::Wrap6a0(int)
{
    void* resource = p14;
    Ctx63620* factory = (Ctx63620*)pC;
    _ReadWriteBarrier();
    Stm* stream = p28;
    _ReadWriteBarrier();
    factory->Load(p2c, stream, resource);
}

// @ 0x00764760
Ctor764760* Ctor764760::Init(uint32_t v)
{
    InitBlk(&blk0);
    InitBlk(&blk1);
    p70 = v;
    memset(&p74, 0, 8);
    return this;
}

// @ 0x00764820
bool Loader::Load820(int)
{
    uint32_t size = p28->GetSize();
    if (size == (uint32_t)-1) return false;
    SharedBuf* sb = new ("Graphics", 0, 0, 0, 0) SharedBuf(PoolAlloc(size), (void*)1, 0);
    SBHandle h(sb);
    char* dst = (char*)sb->data;
    uint32_t left = size;
    while (left > 0) {
        int n = p28->Read(dst, left);
        if (n == -1) break;
        left -= n;
        dst += n;
    }
    if (left != 0) return false;
    AsyncReq* req = new ("Graphics/GraphicsFactoryAsyncRequest", 0, 0, 0, 0) AsyncReq(sb, size, "UTF/MemoryStream");
    Stm* old = p28;
    if (req != old) {
        if (req) req->AddRef();
        p28 = req;
        if (old) old->Release();
    }
    return true;
}

// @ 0x007649f0
bool Loader::Complete(char* a)
{
    p10->v9();
    if (!b334) {
        GetAsyncMgr()->RequestComplete(r1c, 0);
        return false;
    }
    void* q = p14;
    GetAsyncMgr()->RequestComplete(r1c, q);
    q = p14;
    return FUN_6ae2f0(a, q);
}

// @ 0x00764a50
bool SP::cGraphicsResourceFactory_s0076_3cb0::ReadResourceArena(D7642c0* st, Stm7* s, Registry* reg)
{
    st->size = s->Size();
    {
        IfA* nw = reg ? (IfA*)reg->Query(0x2f4e681b) : 0;
        IfA* old = st->a.p;
        if (nw != old) { if (nw) nw->AddRef(); st->a.p = nw; if (old) old->Release(); }
    }
    {
        IfB* nw = reg ? (IfB*)reg->Query(0x034c84e9) : 0;
        IfB* old = st->b.p;
        if (nw != old) { if (nw) nw->AddRef(); st->b.p = nw; if (old) old->Release(); }
    }
    if (st->a.p && st->b.p) {
        if (st->a.p->f18) {
            Z4 z; z.b = 0; z.c = 0; z.d = 0; z.a = 0;
            st->b.p->Reset(&z);
            IfA* q = st->a.p;
            q->f18 = 0;
        }
        Arena98 holder;
        if (st->size < 0x98) return false;
        if (s->Read(&holder, 0x98) != 0x98) return false;
        st->size -= 0x98;
        RDesc rd = holder.a;
        if (holder.a.d[0].size < 0x98) return false;
        st->b.p->Alloc(&rd, 0);
        char** blocks = st->b.p->Blocks();
        *(Arena98*)blocks[0] = holder;
        for (uint32_t i = 0; i < 4; i++) {
            uint32_t n = rd.d[i].size;
            char* p = blocks[i];
            if (i == 0) { n -= 0x98; p += 0x98; }
            if (st->size < n) return false;
            if (n > 0) {
                if (s->Read(p, n) != n) return false;
                st->size -= n;
            }
        }
        if (st->size != 0) return false;
        return true;
    }
    return false;
}

// @ 0x00764ce0
bool SP::cGraphicsResourceFactory_s0076_3cb0::BuildArena(Stm7* s, Registry* reg, const V3u* pv)
{
    D7642c0 st;
    if (!ReadResourceArena(&st, s, reg)) return false;
    char** blocks = st.b.p->Blocks();
    char* first = blocks[0];
    if (FixupArena((ArenaOwner*)blocks)) {
        if (FUN_763fd0(first)) st.b.p->Done();
        st.a.p->f18 = first;
        st.a.p->v08 = *pv;
        return true;
    }
    return false;
}

// @ 0x00764df0
bool SP::cGraphicsResourceFactory_s0076_4df0::CreateRasterFromArena(CreateRasterIn* in, void* z, CreateRasterOut* out)
{
    ArenaSrc* ld = in->loader;
    if (ld) {
        ArenaHolder* old = in->res;
        if (old) { in->res = 0; old->Release(); }
        ld->Get((RefIface**)&in->res);
    }
    ArenaHolder* res = in->res;
    if (res) {
        Arena_s0076_4df0* arena = (Arena_s0076_4df0*)res->arenaPtr;
        SetCachingType(2, res);
        uint32_t n = arena->GetNumExportedObjects();
        for (uint32_t i = 0; i < n; i++) {
            void* cell;
            {
                ExpObj e;
                arena->GetExportedObjectByIndex(i, &e);
                if (e.type != 0x20003) continue;
                cell = e.obj;
            }
            if (!cell) break;
            out->cell = cell;
            RefIface* old = out->ref;
            if ((RefIface*)res != old) {
                res->AddRef();
                out->ref = res;
                if (old) old->Release();
            }
            return true;
        }
    }
    return false;
}

// @ 0x00764f60
bool __stdcall FUN_764f60(GameMeshes* g, IStream_* s)
{
    int n = (int)(g->end - g->begin);
    W32(s, 1);
    W32(s, n);
    for (int i = 0; i < n; i++) {
        Mesh764** pp = g->begin + i;
        if (!WriteMesh(s, *pp))
            return false;
    }
    for (int i = 0; i < n; i++) {
        Mesh764* m = g->begin[i];
        int idx = FUN_71ddc0(m, 0x15, 0, 6, 8);
        if (idx >= 0) {
            MatRec* r = (MatRec*)(m->recs + idx * 0x20 + 0x10);
            MatRec copy(*r);
            GetMaterialManager()->Fn17(copy.a, copy.b, s, g->f8);
        }
    }
    return true;
}

// @ 0x007650d0
void Loader29::WrapA50(int)
{
    void* resource = p14;
    Ctx764a50* factory = (Ctx764a50*)pC;
    _ReadWriteBarrier();
    void* stream = p28;
    _ReadWriteBarrier();
    factory->ReadArena(p2c, stream, resource);
}

// @ 0x007650f0
bool LoaderF0::Fn7650f0(int)
{
    SP::cGraphicsResourceFactory2* f = pC;
    ArenaOwner* o = p34->Fn7();
    void* arena = o->arena;
    if (!f->FixupArena(o))
        return false;
    if (FUN_763fd0(arena))
        p34->Fn5();
    p30->f18 = arena;
    b334 = 1;
    return true;
}

// @ 0x00765150
void Loader29::WrapDf0(int)
{
    Ctx764df0* ctx = (Ctx764df0*)pC;
    char ok = ctx->CreateRaster(p2c, p28, p14);
    if (ok)
        b334 = 1;
}

// @ 0x00765230
void __cdecl FUN_765230(Rec7c_s0076_4df0* p, unsigned count, const Rec7c_s0076_4df0& value)
{
    for (unsigned i = count; i > 0; --i) {
        if (p)
            new ((void*)p) Rec7c_s0076_4df0(value);
        p = (Rec7c_s0076_4df0*)((char*)p + 0x7c);
    }
}

// @ 0x007652c0
bool AsyncReqA::Start(JobRefL* out)
{
    if (id18 != 0x2f4e681c)
        return false;
    state = 1;
    _ReadWriteBarrier();
    f44 = 0;
    _ReadWriteBarrier();
    if (obj->Info()->f4 != 0x2f7d0004)
        return false;
    f2c = 4;
    JobLockL lock(GetJobManager());
    JobRefL a;
    {
        IJobMgr* m = GetJobManager();
        a.Reset();
        if (!m->CreateJob(&a))
            return false;
    }
    JobRefL b;
    {
        IJobMgr* m = GetJobManager();
        b.Reset();
        if (!m->CreateJob(&b))
            return false;
    }
    a.p->SetCallback((void*)FUN_764700, this);
    a.p->mFlags = 4;
    a.p->SetOwner(this);
    a.p->Queue();
    b.p->SetCallback((void*)FUN_764710, this);
    b.p->mFlags = 1;
    b.p->SetOwner(this);
    b.p->AddDependency(a.p);
    b.p->Queue();
    out->p = b.p;
    b.p = 0;
    return true;
}

// @ 0x007654f0
GrfCtor::GrfCtor()
: mPrestreamMemoryBufferLock(new ("Graphics", 0, 0, 0, 0) cJobLock_s0076_4df0()) {}

// @ 0x007655f0
bool SP::cGraphicsResourceFactory_s0076_4df0::Fn7655f0(void* a, void* b, void* c)
{
    D7643d0 d;
    ResMgr* mgr = (ResMgr*)GetManager();
    if (mgr->Get(c, d.ResetB(), 0, a, this, c))
        return CreateRasterFromArena((CreateRasterIn*)&d, 0, (CreateRasterOut*)b);
    return 0;
}

// @ 0x007656c0
bool __stdcall FUN_7656c0(WStream7* s, MeshVec* o)
{
    uint32_t count = (uint32_t)(o->end - o->begin);
    s->Write(&count, 4);
    for (uint32_t i = 0; i < count; i++) {
        uint32_t t = (*(o->begin + i))->w4;
        s->Write(&t, 4);
        if (t != 0x20d) {
            MeshS** pp = o->begin + i;
            s->Write((*pp)->p8, FUN_778050(t));
        } else {
            MeshS* m = o->begin[i];
            uint32_t n = m->cnt;
            s->Write(&n, 4);
            for (uint32_t j = 0; j < n; j++) {
                SlotEnt* e = &m->ents[j];
                RcRef h(e->ref);
                RcRef* er = (RcRef*)&e->ref;
                er->Reset();
                s->Write(e, 0x10);
                KeyOut k;
                FUN_67dd60()->GetKey(&k, h.p);
                s->Write(&k.instance, 4);
                s->Write(&k.group, 4);
                er->Assign(h.p);
            }
        }
    }
    return true;
}

// @ 0x00765980
void HVec::grow(unsigned n)
{
    if (n > (unsigned)(cap - b)) {
        Node8* newp = n ? (Node8*)EA_New(n * 8, "Graphics", 0, 0, g_allocFile, 0xd1) : 0;
        DoFreeNodes(b, e, newp);
        if (b && *(int*)((char*)b - 4) != 0)
            EA_Delete(b);
        Node8* oldb = b;
        size_t count = e - oldb;
        b = newp;
        e = newp + count;
        cap = newp + n;
    }
}

// @ 0x00765ac0
D765ac0::~D765ac0()
{
    int n = (int)(v78.e - v78.b);
    for (int i = 0; i < n; i++) {
        if (v78.b[i])
            EA_Delete(v78.b[i]);
    }
    if (v78.b && v78.b != v78.inlinebuf)
        EA_Delete(v78.b);
    if (v20.b && v20.b != v20.inlinebuf)
        EA_Delete(v20.b);
}

// @ 0x00765b30
bool AsyncReqB::Start(JobRefL* out)
{
    if (id18 != 0x2f4e681b)
        return false;
    st.state = 5;
    st.b = 0;
    st.c = 0;
    JobLockL lock(GetJobManager());
    JobRefL a;
    {
        IJobMgr* m = GetJobManager();
        a.Reset();
        if (!m->CreateJob(&a))
            return false;
    }
    JobRefL b;
    {
        IJobMgr* m = GetJobManager();
        b.Reset();
        if (!m->CreateJob(&b))
            return false;
    }
    a.p->SetCallback((void*)Job7651a0, this);
    a.p->mFlags = 4;
    a.p->SetOwner(this);
    a.p->Queue();
    b.p->SetCallback((void*)Job7651b0, this);
    b.p->mFlags = 1;
    b.p->SetOwner(this);
    b.p->AddDependency(a.p);
    b.p->Queue();
    out->p = b.p;
    b.p = 0;
    return true;
}

// @ 0x00765d30
bool AsyncReqC::Start(JobRefL* out)
{
    if (id18 != 0x2f4e681c)
        return false;
    if (obj->Info()->f4 != 0x2f4e681b)
        return false;
    IRef2** pb = st.Init();
    IKeyObj* o = obj;
    IMgr8* mgr = (IMgr8*)GetManager();
    uint32_t v = f0c;
    if (*pb) { IRef2* t = *pb; *pb = 0; t->Release(); }
    if (st.a) { IRef2* t = st.a; st.a = 0; t->Release(); }
    if (!mgr->Get(o->Info(), &st.a, pb, 0, 0, o->Aux(), v, 0))
        return false;
    JobRefL job;
    IJobMgr* jm = GetJobManager();
    job.Reset();
    if (!jm->CreateJob(&job))
        return false;
    if (st.a) {
        void* x = st.a->Query(0x3a212ac);
        if (x) {
            cJob_s0076_4df0* jp = job.p;
            jp->AddDependency(((DomNode*)x)->Type());
        }
    }
    job.p->SetCallback((void*)Job7651c0, this);
    job.p->mFlags = 1;
    job.p->SetOwner(this);
    job.p->Queue();
    out->p = job.p;
    job.p = 0;
    return true;
}

// @ 0x00765f10
D765f10::D765f10(void* arg)
{
    f18 = 0;
    f1c = arg;
    if (arg)
        ((IUnknown32_s0076_4df0*)arg)->u0();
    f18 = 0;
}

// @ 0x00765f80
void* IResEd::Delete(unsigned flags)
{
    if (m1c)
        m1c->Release();
    *(void**)this = (void*)0x13eb938;
    if (flags & 1)
        EA_Dealloc(this);
    return this;
}

// @ 0x00765fe0
ResB::ResB()
: a24(0), a28(0), a2c(0) { a20 = 0; x18 = 0; }

// @ 0x00766030
void* __fastcall AsInterfaceFC(void* self, int, int type)
{
    if (type == 0x34c84e9) {
        if (self)
            return (char*)self + 0x1c;
        return 0;
    }
    if (type == 0x2f4e681b)
        return self;
    return ((RawRes*)self)->AsInterface(type);
}

// @ 0x00766070
void ResB::Method66070(int a, int b)
{
    Arena* arena = *(Arena**)((char*)this - 4);
    if (arena)
        arena->Release();
    *(void**)((char*)this - 4) = 0;
    void* p = (char*)this + 4;
    sub_6c20b0(p);
    sub_6c2060(p, a, b);
}

// @ 0x007660b0
void ResB::Method660b0()
{
    sub_6c20e0((char*)this + 4);
}

// @ 0x00766100
void ResB::MoveOut(void* out)
{
    int* o = (int*)out;
    char* self = (char*)this;
    o[0] = *(int*)(self + 4);
    o[1] = *(int*)(self + 8);
    o[2] = *(int*)(self + 0xc);
    o[3] = *(int*)(self + 0x10);
    *(int*)(self + 4) = 0;
    *(int*)(self + 8) = 0;
    *(int*)(self + 0xc) = 0;
    *(int*)(self + 0x10) = 0;
}

// @ 0x00766140
ResD::ResD()
{
    *(void**)this = (void*)0x140e118;
    *(void**)((char*)this + 0x1c) = (void*)0x140e0f8;
    AllocDesc desc[4];
    desc[0].size = 0;
    desc[0].type = 1;
    if (mArena)
        ((Arena*)mArena)->Release();
    mArena = 0;
    FreePtrs4((char*)this + 0x20);
    AllocFromDesc((char*)this + 0x20, desc, 0);
    *(void**)((char*)this + 0x1c) = (void*)0x13eb938;
    *(void**)this = (void*)0x13eb938;
}

// @ 0x00766220
ResE::ResE()
: a18(0) {}

// @ 0x007662d0
void VBig::_insert(char* position, uint32_t n, char* value)
{
    uint32_t size = (uint32_t)((mpEnd - mpBegin) / 0xa0);
    if (size < n) {
        uint32_t cap = size * 2;
        if (size == 0)
            cap = 1;
        uint32_t need = size + n;
        if (need < cap)
            need = cap;
        char* nb = need ? (char*)EA_Alloc8(need * 0xa0, 0x10, 0, "Graphics", 0, 0, g_allocFile_s0076_5f80, 0xe5) : 0;
        char* p = BigMove(nb, mpBegin, position);
        BigUninitFill(p, n, value);
        char* ne = BigMove(position, mpEnd, p + n * 0xa0);
        if (mpBegin && mpBegin != *(char**)((char*)this + 0x10))
            EA_Dealloc(mpBegin);
        mpBegin = nb;
        mpEnd = ne;
        mpCap = nb + need * 0xa0;
    } else if (n) {
        char* end = mpEnd;
        uint32_t right = (uint32_t)((end - position) / 0xa0);
        if (n < right) {
            char* edge = end - n * 0xa0;
            BigMoveBack(edge, end, position, end);
            mpEnd = end + n * 0xa0;
            BigMoveBack(position + n * 0xa0, edge, end, position);
            BigUninitFill(position, n, value);
        } else {
            BigUninitFill(end, n - right, value);
            mpEnd = end + (n - right) * 0xa0;
            BigMove(position, end, mpEnd);
            mpEnd += right * 0xa0;
            BigUninitFill(position, right, value);
        }
    }
}

// @ 0x007664e0
bool __stdcall PNGWriteCallback(PngArg* arg)
{
    unsigned char buf[0x2a70];
    memset(buf, 0, 0x2a70);
    PngArg2* a = arg->p08;
    PngInner* inner = a->inner;
    int c1c = inner->c1c;
    void* c20 = inner->c20;
    *(int*)(buf + 0x10) = c1c;
    *(void**)(buf + 0x14) = c20;
    *(int*)(buf + 0x18) = 0x20;
    *(int*)(buf + 0x438) = (a->flag18 != 0) ? 8 : 0;
    if (inner->c34 != 0) {
        PngStr s;
        s.mpBegin = (const char*)0x1667bac;
        s.mpEnd   = (const char*)0x1667bac;
        s.mpCap   = (const char*)0x1667bad;
        EAString_sprintf(&s, "0x%08x:0x%08x", inner->c2c, inner->c30);
        MsvcrSprintf((char*)buf + 0x65c, s.mpBegin);
    }
    PngCtx ctx;
    ctx.ctor87cf40();
    int v = a->obj10->v6();
    ctx.m87cf60(v);
    bool ok = ctx.m87d2a0(4, 1);
    if (!ok) {
        ctx.m87d260();
        return false;
    }
    bool wrote = ctx.m87d030(buf, inner->c28, c1c * 4);
    ctx.m87cff0();
    a->obj10->v9();
    MsgSrv* srv = (MsgSrv*)MessageServer();
    if (srv && a->p14)
        srv->s6(a->p14, 0, 0, 0);
    ctx.m87d260();
    return wrote;
}

// @ 0x007666a0
bool __stdcall CreateByType(void** out, uint32_t type, int sub)
{
    AutoRef ref;
    ref.p = 0;
    if (type < 0x2cb4f30) {
        if (type == 0x2cb4f2f) {
            void* p = sub_f473a0(0x3fe4, "RenderAsset", 0, 0, 0, 0);
            if (p) {
                *(void**)p = (void*)0x13ebcdc;
                _InterlockedExchange((volatile long*)((char*)p + 4), 0);
                *(int*)((char*)p + 8) = 0;
                *(int*)((char*)p + 0xc) = 0;
                *(int*)((char*)p + 0x10) = 0;
                *(int*)((char*)p + 0x14) = 0;
                *(void**)p = (void*)0x140e0d0;
                ref.p = p;
                ((IRef*)p)->AddRef();
            }
        } else if (type == 0xe6bce5) {
            void* p = sub_f473a0(0x140, "RenderAsset", 0, 0, 0, 0);
            ref = p ? (void*)new (p) D7004d0() : 0;
            sub_6ac040(4, ref.p);
        } else if (type == 0x1c135da) {
            void* p = sub_f473a0(0x2c, "RenderAsset", 0, 0, 0, 0);
            ref = p ? (void*)new (p) CEditorRes_s0076_5f80() : 0;
            sub_6ac040(4, ref.p);
        } else {
            return false;
        }
    } else if (type == 0x2f4e681b) {
        void* p = sub_f473a0(0x30, "RenderAsset", 0, 0, 0, 0);
        if (!p)
            return false;
        void* q = (void*)new (p) ResB();
        if (!q)
            return false;
        ref.p = q;
        ((IRef*)q)->AddRef();
    } else if (type == 0x2f4e681c) {
        if (sub == 0x2f4e681b) {
            void* p = sub_f473a0(0x20, "RenderAsset", 0, 0, 0, 0);
            ref = p ? (void*)new (p) D765f10_s0076_5f80(0) : 0;
        } else {
            void* p = sub_f473a0(0x1c, "RenderAsset", 0, 0, 0, 0);
            ref = p ? (void*)new (p) ResE() : 0;
        }
    } else {
        return false;
    }
    if (ref.p) {
        *out = ref.p;
        ((IRef*)ref.p)->AddRef();
        ((IRef*)ref.p)->Release();
        return true;
    }
    return false;
}

// @ 0x007668c0
void __cdecl UnionDestroy(void* p, int type)
{
    if (type == 4) {
        ((CUnionTarget*)p)->m();
        return;
    }
    if (type == 3)
        return;
    if (type == 2) {
        ((CUnionTarget*)p)->m();
        return;
    }
    if (type == 1) {
        void* v = *(void**)((char*)p + 0x18);
        if (v)
            EA_Dealloc(v);
        *(void**)((char*)p + 0x18) = 0;
    }
}

// @ 0x00766910
void VPtr::push_back(const uint32_t& v)
{
    uint32_t* e = mpEnd;
    if (e < mpCap) {
        mpEnd = e + 1;
        if (e)
            *e = v;
        return;
    }
    DoInsertValue(e, v);
}

// @ 0x00766950
void V4::insert(uint32_t* position, uint32_t n, const uint32_t& value)
{
    if ((uint32_t)(mpCap - mpEnd) < n) {
        uint32_t size = (uint32_t)(mpEnd - mpBegin);
        uint32_t cap = size * 2;
        if (size == 0)
            cap = 1;
        uint32_t need = size + n;
        if (need < cap)
            need = cap;
        uint32_t* nb = need ? (uint32_t*)sub_f473a0(need * 4, "Graphics", 0, 0, g_allocFile_s0076_5f80, 0xd1) : 0;
        uint32_t* p = (uint32_t*)memcpy_t(nb, mpBegin, (uint32_t)((char*)position - (char*)mpBegin));
        p = (uint32_t*)((char*)p + ((char*)position - (char*)mpBegin));
        for (uint32_t i = 0; i < n; i++)
            p[i] = value;
        uint32_t* r = (uint32_t*)memcpy_t(p + n, position, (uint32_t)((char*)mpEnd - (char*)position));
        uint32_t* ne = (uint32_t*)((char*)r + ((char*)mpEnd - (char*)position));
        if (mpBegin && mpBegin != mpAlloc)
            EA_Dealloc(mpBegin);
        mpBegin = nb;
        mpEnd = ne;
        mpCap = nb + need;
    } else if (n) {
        uint32_t v = value;
        uint32_t* end = mpEnd;
        uint32_t right = (uint32_t)(end - position);
        if (n < right) {
            uint32_t* edge = end - n;
            memcpy_t(end, edge, n * 4);
            mpEnd = end + n;
            memmove(end - (edge - position), position, (uint32_t)((char*)edge - (char*)position));
            for (uint32_t* p = position; p != position + n; ++p)
                *p = v;
        } else {
            for (uint32_t* p = end; p != end + (n - right); ++p)
                *p = v;
            mpEnd = end + (n - right);
            memcpy_t(mpEnd, position, (uint32_t)((char*)end - (char*)position));
            mpEnd += right;
            for (uint32_t* p = position; p != end; ++p)
                *p = v;
        }
    }
}

// @ 0x00766b30
bool TerrainSphere::RequestPaintDecalsFromModels(void* job)
{
    char* s = (char*)this;
    vec.reserve((uint32_t)((*(int*)(s + 0x1a0) - *(int*)(s + 0x19c)) / 0xc));
    uint32_t have = (uint32_t)(((char*)vec.mpEnd - (char*)vec.mpBegin) >> 2);
    while (have < (uint32_t)((*(int*)(s + 0x1a0) - *(int*)(s + 0x19c)) / 0xc)) {
        if (handle != 0) {
            AutoRefCount local;
            handle->GetOut(&local.p);
            RefObj* old = handle;
            if (old) { handle = 0; old->Release(); }
            vec.push_back(local);
            if (local.p) sub_6ac0a0(2, local.p);
        } else {
            AutoRefCount hA;
            AutoRefCount hB;
            IResMgr* mgr = (IResMgr*)Manager67dcd0();
            bool ok = mgr->m4(s + 0x19c + have * 0xc, &hA, &hB, 0, 0, 0, 0, 0);
            if (!ok) {
                hA = (RefObj*)0;
                hB = (RefObj*)0;
            }
            RefObj* got = hA.p ? hA.p->GetCached(0x3a212ac) : 0;
            RefObj* old = handle;
            if (got != old) {
                if (got) got->AddRef();
                handle = got;
                if (old) old->Release();
            }
            if (hB.p == 0 && handle != 0) {
                int t = ((NodeFC*)handle)->Type();
                ((JobC*)job)->AddWeakDependency(t);
                return ((JobC*)job)->Continuation((void*)0x767340, this);
            }
            vec.push_back(hB);
            if (hB.p) sub_6ac0a0(2, hB.p);
        }
        have = (uint32_t)(((char*)vec.mpEnd - (char*)vec.mpBegin) >> 2);
    }
    return true;
}

// @ 0x00766e10
bool Reader::ReadDecalBlock(int /*unused*/)
{
    if (mStream->sC(&mField2c, 4) != 4)
        return false;
    uint32_t count = (uint32_t)mField2c;
    if (count < 8)
        return false;
    if (count > 9)
        return false;
    uint32_t num;
    IStream* stream = mStream;
    if (!ReadInt32(stream, &num, 1, 0))
        return false;
    vec.reserve(num);
    for (uint32_t i = 0; i < num; i++) {
        int v[3] = {0, 0, 0};
        IStream* s2 = mStream;
        if (!ReadTriplet763340(s2, v, 0))
            return false;
        vec.push_back(v);
    }
    return true;
}

// @ 0x00766ed0
bool Factory::CreateResource(int* src, void** out, int a, int b)
{
    void* local = 0;
    int* tmp = (int*)((IFactorySrc*)src)->f4();
    CreateByType(&local, (uint32_t)b, *(int*)((char*)tmp + 4));
    if (local) {
        if (this->g9call(src, local, a, b)) {
            *out = local;
            ((void(__thiscall**)(void*))VP(local))[0](local);
            ((void(__thiscall**)(void*))VP(local))[1](local);
            return true;
        }
    }
    if (local)
        ((void(__thiscall**)(void*))VP(local))[1](local);
    return false;
}

// @ 0x00766fa0
bool __stdcall ReadPaintStuff(PaintObj* obj, void* stream, void* p3)
{
    (void)p3;
    if (!ReadInt32(stream, &obj->mVersion, 1, 1))
        return false;
    if (obj->mVersion > 1)
        return false;
    if (!ReadInt32(stream, &obj->mA, 1, 1))
        return false;
    if (!ReadInt32(stream, &obj->mB, 1, 1))
        return false;
    if (!ReadTripletG(stream, &obj->mC, 1))
        return false;
    if (!ReadTripletG(stream, &obj->mFlags, 1))
        return false;
    if (!ReadTripletG(stream, &obj->mD, 1))
        return false;
    if (obj->mVersion == 0) {
        obj->mByte18 = 0;
        obj->mCount = 1;
    } else {
        obj->mByte18 = (unsigned char)((obj->mFlags >> 0xc) & 1);
        obj->mCount = obj->mByte18 ? 6u : 1u;
    }
    if (!WriteValue(stream, &obj->mC, 4))
        return false;
    Reserve765a10(&obj->mVec0, obj->mC);
    Reserve765a10(obj->mVec1, obj->mCount * obj->mB);
    if (obj->mB != 0) {
        uint32_t i = 0;
        do {
            uint32_t n;
            if (!ReadInt32(stream, &n, 1, 1))
                return false;
            FUN_005965b0(&n);
            if (obj->mCount != 0) {
                uint32_t j = 0;
                do {
                    if (!WriteValue(stream, &n, 1))
                        return false;
                    void* p = Alloc6(n, "Graphics", 0, 0, 0, 0);
                    VPtrPush(&obj->mVec1, &p);
                } while (++j < obj->mCount);
            }
        } while (++i < obj->mB);
    }
    return true;
}

// @ 0x00767170
bool PaintHolder::FUN_00767170(void* a, void* b, void* c)
{
    PaintObj stackObj;
    if (ReadPaintStuff(&stackObj, a, b)) {
        if (FUN_00764320(&stackObj, a, b)) {
            uint32_t* s = (uint32_t*)c;
            char* d = (char*)b;
            *(uint32_t*)(d + 8) = s[0];
            *(uint32_t*)(d + 0xc) = s[1];
            *(uint32_t*)(d + 0x10) = s[2];
            stackObj.Destroy();
            return true;
        }
    }
    stackObj.Destroy();
    return false;
}

// @ 0x00767270
void F67270::Method(int)
{
    void* resource = (void*)m14;
    PaintReaderFactory* factory = (PaintReaderFactory*)mC;
    _ReadWriteBarrier();
    void* stream = m28;
    _ReadWriteBarrier();
    factory->ReadPaintStuff((PaintObj*)m2c, stream, resource);
}

// @ 0x00767290
void VBig2::Resize(uint32_t n)
{
    uint32_t size = (uint32_t)((e - b) / 0xa0);
    if (size < n) {
        char temp[0xa0];
        InsertGrow(e, n - size, temp);
        return;
    }
    char* dst = b + n * 0xa0;
    char* oldEnd = e;
    FUN_00763f50(oldEnd, oldEnd, dst);
    uint32_t count = (uint32_t)((oldEnd - dst) / 0xa0);
    e = e - count * 0xa0;
}

// @ 0x00767350
void V7c::Insert(int, char* pos, uint32_t n, char* value)
{
    uint32_t size = (uint32_t)((e - b) / 0x7c);
    if (size < n) {
        uint32_t cap = size * 2;
        if (size == 0) cap = 1;
        uint32_t need = size + n;
        if (need < cap) need = cap;
        char* nb = need ? (char*)Alloc6(need * 0x7c, "Graphics", 0, 0, g_file, 0xd1) : 0;
        char* p = (char*)FUN_00757ee0(b, pos, nb);
        FUN_00757f70(b, pos, nb);
        FUN_00765230(p, (void*)(size_t)n, value, b);
        char* ne = (char*)FUN_00757ee0(pos, e, p + n * 0x7c);
        FUN_00757f70(pos, e, p + n * 0x7c);
        if (b && *(int*)(b - 4) != 0)
            Dealloc(b);
        e = ne;
        b = nb;
        c = nb + need * 0x7c;
    } else if (n) {
        char* end = e;
        uint32_t right = (uint32_t)((end - pos) / 0x7c);
        if (n < right) {
            char* edge = end - n * 0x7c;
            char tmp[0x7c];
            FUN_00764ff0(&tmp, edge, end, end);
            e = end + n * 0x7c;
            FUN_00757fb0(pos, edge, end);
            FUN_007664b0(pos, n * 0x7c + pos, tmp);
            FUN_0041f2d0(&tmp);
        } else {
            char tmp[0x7c];
            FUN_00765230(end, (void*)(size_t)(n - right), tmp, 0);
            e = end + (n - right) * 0x7c;
            FUN_00764ff0(&tmp, pos, end, e);
            e = e + right * 0x7c;
            FUN_007664b0(pos, end, tmp);
            FUN_0041f2d0(&tmp);
        }
    }
}

// @ 0x00767590
bool JobOwner::BuildJob(int* a, int* b, unsigned char c)
{
    int* h = (int*)Alloc6(0x1c, "Graphics", 0, 0, 0, 0);
    if (h)
        h = (int*)FUN_007640c0(h);
    if (!h)
        return false;
    if (a != (int*)h[3]) {
        if (a) ((void(__thiscall**)(void*))*(void***)a)[0](a);
        h[3] = (int)a;
    }
    if (b != (int*)h[4]) {
        if (b) ((void(__thiscall**)(void*))*(void***)b)[1](b);
        h[4] = (int)b;
    }
    h[5] = 0x4755bcf;
    *(unsigned char*)(h + 6) = c;
    if (b) ((void(__thiscall**)(void*))*(void***)b)[8](b);
    void* node = Node8F4d0();
    int local = 0;
    ((void(__thiscall**)(void*, int*))*(void***)node)[4](node, &local);
    FUN_0068f9b0(h);
    FUN_006909b0((void*)local);
    if (h) ((void(__thiscall**)(void*))*(void***)h)[1](h);
    return true;
}

// @ 0x007677c0
bool __fastcall ArmDecode(void* self, int, int outPtr)
{
    char* s = (char*)self;
    if (*(int*)(s + 0x18) != 0x2f4e681c)
        return false;
    *(int*)(s + 0xfc) = 4;
    char* e = s + 0x64;
    *(char**)(s + 0x5c) = e;
    *(char**)(s + 0x50) = e;
    *(char**)(s + 0x4c) = e;
    *(char**)(s + 0x54) = e + 0x40;
    char* f = s + 0xbc;
    *(char**)(s + 0xb4) = f;
    *(char**)(s + 0xa8) = f;
    *(char**)(s + 0xa4) = f;
    *(char**)(s + 0xac) = f + 0x40;

    void* a = Node8F4d0();
    ((void(__thiscall*)(void*))(*(void***)a)[8])(a);

    void* local = 0;
    void* b = Node8F4d0();
    if (!((bool(__thiscall*)(void*, void**))(*(void***)b)[4])(b, &local)) {
        if (local) JobRelease(local, 0);
        ((void(__thiscall*)(void*))(*(void***)a)[9])(a);
        return false;
    }

    void* local2 = 0;
    void* c = Node8F4d0();
    if (!((bool(__thiscall*)(void*, void**))(*(void***)c)[4])(c, &local2)) {
        if (local2) JobRelease(local2, 0);
        if (local) JobRelease(local, 0);
        ((void(__thiscall*)(void*))(*(void***)a)[9])(a);
        return false;
    }

    *(int*)local = 0x767320;
    *(void**)((char*)local + 4) = s;
    *(int*)((char*)local + 0x18) = 4;
    JobInit(local, 0, s);
    JobGetStatus(local, 0);

    *(int*)local2 = 0x7646f0;
    *(void**)((char*)local2 + 4) = s;
    *(int*)((char*)local2 + 0x18) = 1;
    JobInit(local2, 0, s);
    JobAddDep(local2, 0, local);
    JobGetStatus(local2, 0);
    *(void**)outPtr = local2;

    if (local) JobRelease(local, 0);
    ((void(__thiscall*)(void*))(*(void***)a)[9])(a);
    return true;
}

// @ 0x007679f0
bool __stdcall ReadAbilityList(void* stream, char* obj, void* key)
{
    (void)key;
    uint32_t count = 0;
    if (!ReadValue(stream, &count, 4))
        return false;
    if (!HasRoom(stream, 4, (int)count))
        return false;
    uint32_t zero = 0;
    VecResizeInt(obj + 8, 0, (int)count, &zero);
    for (uint32_t i = 0; i < count; i++) {
        uint32_t kind;
        if (!ReadValue(stream, &kind, 4))
            return false;
        void* p;
        if (kind == 0x20d) {
            p = Alloc6(0x70, "Editor", 0, 0, 0, 0);
            if (p) CtorEditor(p, 0);
            uint32_t n;
            if (!ReadValue(stream, &n, 4) || n > 6)
                return false;
            *(uint32_t*)((char*)p + 0xc) = n;
            char* item = (char*)p + 0x10;
            for (uint32_t j = 0; j < n; j++, item += 0x10) {
                if (!ReadValue(stream, item, 0x10))
                    return false;
                int in[3] = {0, 0, 0};
                int out[3];
                if (!ReadValue(stream, &in[0], 4) || !ReadValue(stream, &in[2], 4))
                    return false;
                int* r = (int*)ResolveColorSlot(out, in);
                in[0] = r[0];
                in[1] = r[1];
                in[2] = r[2];
                void* mm = FUN_0067dd60();
                int img = ((int(__thiscall*)(void*, int, int, int))(*(void***)mm)[8])(mm, in[0], in[2], 4);
                GetImageResource2(item + 4, 0, img);
            }
        } else {
            int size = (int)(size_t)Fake78050((int)kind);
            p = LockedAlloc(size + 0xc, 0, 0, 0, 0, 0);
            if (p) {
                *(short*)((char*)p + 4) = (short)kind;
                *(void**)p = (void*)0x13ef094;
                *(unsigned short*)((char*)p + 6) = (unsigned short)size;
                *(void**)((char*)p + 8) = (char*)p + 0xc;
            }
            if (!ReadValue(stream, *(void**)((char*)p + 8), size)) {
                ((void(__thiscall*)(void*, int))(*(void***)p)[0])(p, 1);
                return false;
            }
        }
        *(void**)(*(int*)(obj + 8) + i * 4) = p;
    }
    return true;
}

// @ 0x00767c80
bool __stdcall ReadMaterialList(void* stream, char* obj, uint32_t* key3)
{
    *(uint32_t*)(obj + 8) = key3[0];
    *(uint32_t*)(obj + 0xc) = key3[1];
    *(uint32_t*)(obj + 0x10) = key3[2];
    int one;
    if (!ReadInt32(stream, &one, 1, 0) || one != 1)
        return false;
    int count;
    if (!ReadInt32(stream, &count, 1, 0))
        return false;
    for (int i = 0; i < count; i++) {
        void* p = 0;
        if (!FUN_0071f8f0(stream, &p)) {
            if (p) {
                volatile int* rc = (volatile int*)((char*)p + 4);
                if (_InterlockedExchangeAdd((volatile long*)rc, -1) - 1 == 0) {
                    _InterlockedExchange((volatile long*)rc, 1);
                    ((void(__thiscall*)(void*, int))(*(void***)p)[0])(p, 1);
                }
            }
            return false;
        }
        RefVecPush2(obj + 0x18, 0, &p);
        if (p) {
            volatile int* rc = (volatile int*)((char*)p + 4);
            if (_InterlockedExchangeAdd((volatile long*)rc, -1) - 1 == 0) {
                _InterlockedExchange((volatile long*)rc, 1);
                ((void(__thiscall*)(void*, int))(*(void***)p)[0])(p, 1);
            }
        }
    }
    for (int i = 0; i < count; i++) {
        int e = *(int*)(*(int*)(obj + 0x18) + i * 4);
        int idx = FUN_0071ddc0((void*)e, 0x15, 0, 6, 8);
        if (idx >= 0) {
            char* slot = (char*)(idx * 0x20 + 0x10 + *(int*)(e + 8));
            void* local = 0;
            void* mm = MaterialManager();
            int r = ((int(__thiscall*)(void*, void*, void*, void*, void*, void*))(*(void***)mm)[0x48 / 4])(
                mm, stream, *(void**)slot, *((void**)slot + 1), &local, key3);
            if (r < 0) {
                if (local) ((void(__thiscall*)(void*))(*(void***)local)[1])(local);
                return false;
            }
            if (local) {
                RemoveRC2(local, 0, *((void**)slot + 3));
                void* old = *((void**)slot + 3);
                if (local != old) {
                    ((void(__thiscall*)(void*))(*(void***)local)[0])(local);
                    *((void**)slot + 3) = local;
                    if (old) ((void(__thiscall*)(void*))(*(void***)old)[1])(old);
                }
            }
            if (local) ((void(__thiscall*)(void*))(*(void***)local)[1])(local);
        }
    }
    return true;
}

// @ 0x00767ee0
int __stdcall WriteResourceRaster(void* arg, int* stream)
{
    Raster_s0076_7ee0* r = *(Raster_s0076_7ee0**)((char*)arg + 0x18);
    (void)r; (void)stream;
    // full writer is a register-heavy event loop over mip levels/faces;
    // modelled only structurally here.
    return 1;
}

// @ 0x00768200
void C68200::Release()
{
    int v = mD0;
    if (v) {
        if (v == 5) {
            FUN_007642c0(this);
        } else {
            UnionDestroy(this, v);
        }
        mD0 = 0;
    }
}

// @ 0x00768240
C68240::C68240(void* arg)
{
    char* base = m18;
    m10 = base;
    m4 = base;
    m0 = base;
    m8 = base + 0x80;
    RegisterJob(arg);
}

// @ 0x007682a0
void V7cB::Resize(uint32_t n)
{
    uint32_t count = (uint32_t)((e - b) / 0x7c);
    if (count < n) {
        Tmp7c tmp;
        tmp.Init(0);
        InsertFill(e, n - count, &tmp);
        tmp.Destroy();
    } else {
        DestroyRange(b + n * 0x7c, e);
    }
}

// @ 0x00768370
C68370::C68370(IRefB* a, IObj_s0076_7ee0* b, int* c, IObj_s0076_7ee0* d, int e)
: m_pC(b), m_pE(d), m_pA(a), m_v18(e), m_v1c(c[0]), m_v20(c[1]), m_v24(c[2])
{
    m334 = 0;
    IObj_s0076_7ee0* p = m_pE->GetChild();
    if (p) {
        if (p->GetKind() == 0x34722300)
            p = new ("Graphics", 0, 0, 0, 0) Child(0x2000, 0, p);
        m_p28 = p;
    }
}

// @ 0x00769200
bool Factory_s0076_89a0::WriteResource(void* obj, void* src, void* u3, void* u4)
{
    (void)u3; (void)u4;
    StreamRef st(((IFactorySrc_s0076_89a0*)src)->GetStream());
    bool r;
    if (st.p) {
        uint32_t type = *(uint32_t*)((char*)obj + 0xc);
        switch (type) {
        case 0x46194d0:
            r = BuildJob(obj, src, 1);
            break;
        case 0x1c135da:
            r = WriteResourceGameMeshes(obj, st.p);
            break;
        case 0xe6bce5:
            r = WriteResourceGameModel((Model*)obj, st.p);
            break;
        case 0x65ea4ec:
            r = BuildJob(obj, src, 0);
            break;
        case 0x2f4e681b:
            r = WriteResourceRasterArena(obj, st.p);
            break;
        case 0x2f4e681c:
            r = WriteResourceRaster(obj, st.p);
            break;
        default:
            return false;
        }
        return r;
    }
    return false;
}

// @ 0x00769cb0
char __fastcall Func69cb0(void* self, int, int unused)
{
    (void)unused;
    char* s = (char*)self;
    void* obj = *(void**)(s + 0x10);
    int uVar5 = *(int*)(s + 0x2c);
    int a14 = *(int*)(s + 0x14);
    int a28 = *(int*)(s + 0x28);
    int ebp = *(int*)(s + 0xc);
    int v = ((int(__thiscall**)(void*, int))*(void***)obj)[4](obj, uVar5);
    char c = ((M69310*)ebp)->Meth(a28, a14, v);
    if (c)
        *(char*)(s + 0x334) = 1;
    return c;
}

// @ 0x00769cf0
char __fastcall Func69cf0(void* self, int, void* stream, void* a2, void* a3)
{
    (void)self;
    int local;
    if (((int(__thiscall**)(void*, int*, int))*(void***)stream)[12](stream, &local, 4) != 4)
        return 0;
    if ((uint32_t)(local - 8) > 1)
        return 0;
    FUN_007006d0(a2);
    if (!FUN_007638a0(stream, a3, a2, (void*)local))
        return 0;
    return FUN_00769310b(stream, a3, a2, (void*)local);
}

// @ 0x00769d80
char cGraphicsResourceFactory::ReadResourceFromStream(int* src, void* a2, int* obj, uint32_t kind)
{
    int* holder = 0;
    int* arg = src;
    if (src && ((int(__thiscall**)(int*))*(void***)src)[3](src) == 0x34722300) {
        void* p = Alloc6(0x34, "Graphics", 0, 0, 0, 0);
        if (p)
            p = FUN_0093b530(0x2000, 0, src);
        if (p) {
            ((void(__thiscall**)(void*))*(void***)p)[1](p);
            holder = (int*)p;
        }
        arg = holder;
    }
    uint32_t type = *(uint32_t*)((char*)obj + 4);
    char r = 0;
    bool handled = true;
    if (type <= 0x2cb4f2f) {
        if (type == 0x2cb4f2f)
            r = ReadPCAWeights(arg, a2, obj);
        else if (type == 0xe6bce5)
            r = ReadVia69cf0(arg, a2, obj);
        else if (type == 0x1c135da)
            r = ReadMaterialList_(arg, a2, obj);
        else
            handled = false;
    } else if (type == 0x2f4e681b) {
        r = ReadVia64ce0(arg, a2, obj);
    } else if (type == 0x2f4e681c && kind <= 0x2f7d0004) {
        if (kind == 0x2f7d0004)
            r = ReadVia637d0(arg, a2, 4, obj);
        else if (kind != 0x2f4e681b && kind == 0x2f4e681c)
            r = ReadVia67170(arg, a2, obj);
        else
            handled = false;
    } else {
        handled = false;
    }
    if (!handled) {
        if (holder)
            ((void(__thiscall**)(int*))*(void***)holder)[2](holder);
        return 0;
    }
    if (holder)
        ((void(__thiscall**)(int*))*(void***)holder)[2](holder);
    return r;
}

// @ 0x00769f20
bool __fastcall SetupJobChain(void* self, int, void** out)
{
    Grf* s = (Grf*)self;
    s->stateFC = 3;
    IJobMgr_s0076_9f20* jm = GetJobManager_s0076_9f20();
    jm->Lock();

    JobRefL_s0076_9f20 j1, j2, j3, j4;
    if (!CreateJobInto(GetJobManager_s0076_9f20(), j1)) { jm->Unlock(); return false; }
    if (!CreateJobInto(GetJobManager_s0076_9f20(), j2)) { j1.Reset(); jm->Unlock(); return false; }
    if (!CreateJobInto(GetJobManager_s0076_9f20(), j3)) { j2.Reset(); j1.Reset(); jm->Unlock(); return false; }
    if (!CreateJobInto(GetJobManager_s0076_9f20(), j4)) { j3.Reset(); j2.Reset(); j1.Reset(); jm->Unlock(); return false; }

    JobRefL_s0076_9f20 l1, l2;
    if (!LockTable(self)->TryLockJobs(&l1, &l2)) {
        l2.Reset(); l1.Reset();
        j4.Reset(); j3.Reset(); j2.Reset(); j1.Reset();
        jm->Unlock();
        return false;
    }

    j1.p->SetCallback((void*)0x767330, self);
    j1.p->mFlags = 4;
    j1.p->SetExtra(self);
    j1.p->Submit();

    j2.p->SetCallback((void*)0x767340, self);
    j2.p->mFlags = 0x80000000;
    j2.p->SetExtra(self);
    j2.p->AddDependency(j1.p);
    j2.p->Submit();

    l1.p->AddDependency(j2.p);
    l1.p->Submit();

    j3.p->SetCallback((void*)0x765190, self);
    j3.p->mFlags = 4;
    j3.p->SetExtra(self);
    j3.p->AddDependency(l1.p);
    j3.p->Submit();

    j4.p->SetCallback((void*)0x769d70, self);
    j4.p->mFlags = 1;
    j4.p->SetExtra(self);
    j4.p->AddDependency(j3.p);
    j4.p->Submit();

    l2.p->AddDependency(j4.p);
    l2.p->Submit();

    *out = j4.p;
    j4.p = 0;

    l2.Reset(); l1.Reset();
    j4.Reset(); j3.Reset(); j2.Reset(); j1.Reset();
    jm->Unlock();
    return true;
}

// @ 0x0076a300
char __fastcall Func76a300(void* self, int, int unused)
{
    (void)unused;
    char* s = (char*)self;
    void* obj = *(void**)(s + 0x10);
    int uVar5 = *(int*)(s + 0x18);
    int a14 = *(int*)(s + 0x14);
    int a28 = *(int*)(s + 0x28);
    int ebp = *(int*)(s + 0xc);
    int v = ((int(__thiscall**)(void*, int))*(void***)obj)[4](obj, uVar5);
    char c = ((M69d80*)ebp)->Meth(a28, a14, v);
    if (c)
        *(char*)(s + 0x334) = 1;
    return c;
}

// @ 0x0076a340
char __fastcall ReadResource(void* self, int, void* a1, void* a2, void* a3)
{
    char* o = (char*)a1;
    void* p = (void*)((int(__thiscall**)(void*))*(void***)self)[4](self);
    // triplet copy
    int t0 = *(int*)p, t1 = *(int*)((char*)p + 4), t2 = *(int*)((char*)p + 8);
    *(int*)(o + 8) = t0;
    *(int*)(o + 0xc) = (int)(size_t)a3;
    *(int*)(o + 0x10) = t2;
    if ((size_t)a3 == 0x2f4e681c) {
        void* q = (void*)((int(__thiscall**)(void*))*(void***)self)[4](self);
        if (*(int*)((char*)q + 4) == 0x2f4e681b) {
            void* r = (void*)((int(__thiscall**)(void*))*(void***)self)[4](self);
            void* u = (void*)((int(__thiscall**)(void*, void*, void*))*(void***)self)[7](self, a1, r);
            return FUN_007655f0b(u, a1, r);
        }
    }
    void* q = (void*)((int(__thiscall**)(void*))*(void***)self)[4](self);
    void* t = *(void**)((char*)q + 4);
    void* u = (void*)((int(__thiscall**)(void*, void*, void**, void*))*(void***)self)[6](self, a1, &t, t);
    return FUN_00769d80v(u, a1, &t, t);
}

// @ 0x0076a400
bool __fastcall CreateRequestJob(void* self, int, void* out)
{
    void* n = Node8F4d0();
    int local = 0;
    (void)local;
    if (!((bool(__thiscall**)(void*, int*))*(void***)n)[4](n, &local))
        return false;
    char* lp = (char*)local;
    *(void**)(lp) = (void*)0;          // callback
    *(void**)(lp + 4) = self;
    *(int*)(lp + 0x18) = 1;
    FUN_0068f9b0(self);
    FUN_006909b0(lp);
    *(void**)out = lp;
    return true;
}

// @ 0x0076a4d0
bool __fastcall TryLockChain(void* self, int, void** out)
{
    IJobMgr_s0076_9f20* jm = GetJobManager_s0076_9f20();
    jm->Lock();

    JobRefL_s0076_9f20 j1, j2;
    if (!CreateJobInto(GetJobManager_s0076_9f20(), j1)) { jm->Unlock(); return false; }
    if (!CreateJobInto(GetJobManager_s0076_9f20(), j2)) { j1.Reset(); jm->Unlock(); return false; }

    JobRefL_s0076_9f20 a, b;
    if (!LockTable(self)->TryLockJobs(&a, &b)) {
        b.Reset(); a.Reset();
        j2.Reset(); j1.Reset();
        jm->Unlock();
        return false;
    }

    a.p->Submit();

    j1.p->SetCallback((void*)0x765190, self);
    j1.p->mFlags = 4;
    j1.p->SetExtra(self);
    j1.p->AddDependency(a.p);
    j1.p->Submit();

    j2.p->SetCallback((void*)0x76a3f0, self);
    j2.p->mFlags = 1;
    j2.p->SetExtra(self);
    j2.p->AddDependency(j1.p);
    j2.p->Submit();

    b.p->AddDependency(j2.p);
    b.p->Submit();

    *out = j2.p;
    j2.p = 0;

    b.Reset(); a.Reset();
    j2.Reset(); j1.Reset();
    jm->Unlock();
    return true;
}

// @ 0x0076a720
bool __fastcall CanConvert(void* self, int, void** out)
{
    Grf* s = (Grf*)self;
    IJobMgr_s0076_9f20* jm = GetJobManager_s0076_9f20();
    jm->Lock();

    JobRefL_s0076_9f20 job;
    uint32_t type = s->type18;
    char ok;
    if (type <= 0x2f4e681b) {
        if (type == 0x2f4e681b)
            ok = StartReqB(self, 0, (void**)&job.p);
        else if (type == 0xe6bce5)
            ok = SetupJobChain(self, 0, (void**)&job.p);
        else if (type == 0x1c135da)
            ok = TryLockChain(self, 0, (void**)&job.p);
        else
            ok = CreateRequestJob(self, 0, &job.p);
    } else if (type == 0x2f4e681c) {
        RecInfo* info = s->p10->Info();
        uint32_t sub = info->f4;
        if (sub <= 0x2f7d0004) {
            if (sub == 0x2f7d0004)
                ok = StartReqA(self, 0, (void**)&job.p);
            else if (sub == 0x2f4e681b)
                ok = StartReqC(self, 0, (void**)&job.p);
            else if (sub == 0x2f4e681c)
                ok = ArmDecodeB(self, 0, (int)(size_t)&job.p);
            else {
                jm->Unlock();
                return false;
            }
        } else if (sub == 0x2f7d0007) {
            ok = StartReqA(self, 0, (void**)&job.p);
        } else {
            jm->Unlock();
            return false;
        }
    } else {
        ok = CreateRequestJob(self, 0, &job.p);
    }

    if (!ok) {
        job.Reset();
        jm->Unlock();
        return false;
    }

    JobRefL_s0076_9f20 j2;
    if (!CreateJobInto(GetJobManager_s0076_9f20(), j2)) {
        j2.Reset();
        job.Reset();
        jm->Unlock();
        return false;
    }

    j2.p->SetCallback((void*)0x765180, self);
    j2.p->SetExtra(self);
    j2.p->AddWeakDependency(job.p);

    *out = j2.p;
    j2.p = 0;

    job.Reset();
    jm->Unlock();
    return true;
}

// @ 0x0076a940
bool __cdecl CreateConvertedResourceAsync(void* out, void* a, void* b, IConvCtx* c, void* d)
{
    void* mgr = FUN_0067de70();
    if (!mgr)
        return false;

    IRefObj_s0076_9f20* res = 0;
    RecInfo* info = c->Info();
    if (!CreateByType(a, 0, (void**)&res, d, info->f4)) {
        if (res)
            res->Release();
        return false;
    }

    void* mem = Alloc6(0x338, "Graphics", 0, 0, 0, 0);
    ConvObj* conv = mem ? (ConvObj*)((ConvObj*)mem)->Init(res, a, b, c, d) : 0;
    if (conv)
        ((IRefObj_s0076_9f20*)conv)->AddRef();

    c->Begin();

    IJobMgr_s0076_9f20* jm = GetJobManager_s0076_9f20();
    jm->Lock();

    JobRefL_s0076_9f20 job;
    if (!CanConvert(conv, 0, (void**)&job.p)) {
        c->End();
        job.Reset();
        jm->Unlock();
        if (conv)
            ((IRefObj_s0076_9f20*)conv)->Release();
        if (res)
            res->Release();
        return false;
    }

    JobRefL_s0076_9f20 jobcopy;
    jobcopy.p = job.p;
    if (jobcopy.p)
        jobcopy.p->AddRef();

    IRefObj_s0076_9f20* req = 0;
    bool ok = ((AsyncResMgr*)mgr)->AllocateRequest(b, &req, &jobcopy);
    job.p->Submit();

    if (!ok) {
        if (req)
            req->Release();
        jobcopy.Reset();
        job.Reset();
        jm->Unlock();
        if (conv)
            ((IRefObj_s0076_9f20*)conv)->Release();
        if (res)
            res->Release();
        return false;
    }

    *(void**)out = req;

    jobcopy.Reset();
    job.Reset();
    jm->Unlock();
    if (conv)
        ((IRefObj_s0076_9f20*)conv)->Release();
    if (res)
        res->Release();
    return true;
}

// @ 0x0076ac30
bool __fastcall CreateResourceAsync(void* self, int, void* out, void* unused2, int* param_4, void* p5, void* p6, int p7)
{
    int* local = 0;
    if (p7 == 0)
        p7 = ((int(__thiscall**)(int*))*(void***)param_4)[4](param_4);
    char r = FUN_0076a940v(&local, self, (void*)p7, param_4, p6);
    if (!r) {
        if (local)
            ((void(__thiscall**)(int*))*(void***)local)[1](local);
        return false;
    }
    *(int**)out = local;
    (void)p5;
    (void)unused2;
    return true;
}
