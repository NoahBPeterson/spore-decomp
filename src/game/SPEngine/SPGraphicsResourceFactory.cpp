// src/game/SPEngine/SPGraphicsResourceFactory.cpp -- migrated from slice(s) s00769f20, s00769310, s007689a0, s00767ee0, s00766fa0, s00765f80, s00764df0, s00763cb0, s00762d70, s00682f40 by tools/migrate/rewrite.py
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
extern "C" void* __cdecl GetGlobal67de80();                                                   // 0x067de80
extern "C" void* __cdecl CreateRasterFn(int w, int h, int a, int b, int c);                   // 0x0761420
extern unsigned char g_flags1630180;   // 0x01630180
extern int g_word160077c;              // 0x0160077c
struct RefVec {
    void* b; void* e; void* c;
    RefVec() { b = 0; e = 0; c = 0; }
    ~RefVec() { destroy(); }
    void destroy();   // 0x0041eb80
};
struct Raster { void D3D9GetStreamedMipLevelSize(unsigned char*, int); }; // 0x011f0270
struct IObj { virtual void s0(); virtual void s1(); virtual void s2(int); };
namespace SP {
struct cRasterFromGimexLoadState_s0076_2d70 {
    uint32_t mFormat; uint32_t mWidth; uint32_t mHeight;
    uint32_t mBpp; uint32_t mPitch; uint32_t mSize; unsigned char* mData;
};
}
using SP::cRasterFromGimexLoadState_s0076_2d70;
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
struct OutRaster { char pad[0x18]; void* mData; };
struct V3 { int x, y, z; };
extern "C" void  __cdecl RemoveRegistrationCallback(int id, void* cb);                        // 0x06ad070
// ---- items of slice s00762d70 end

// ---- items of slice s00763cb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct RasterCtx { char Create(void* a, void* b, void* c); };
struct Ctx63620 { char Load(void* a, void* b, void* c); };
struct Ctx63770 { char Fill(void* a, void* b, void* c); };
struct RefObj { virtual void s0(); virtual void s1(); virtual void s2(); };
struct AutoRef { RefObj* p; ~AutoRef() { if (p) p->s1(); } };
struct D7642c0 {
    char pad4[4];
    AutoRef a;                 // +4
    AutoRef b;                 // +8
    ~D7642c0();
};
struct Loader {
    char pad0[0xc];
    void* pC;                  // +0xc
    char pad10[4];
    void* p14;                 // +0x14
    char pad18[0x10];
    void* p28;                 // +0x28
    char p2c[0x308];           // +0x2c
    unsigned char b334;        // +0x334
    void Wrap670(int);
    void Wrap6a0(int);
    void Wrap6c0(int);
};
void Loader::Wrap6c0(int) {
    if (((Ctx63770*)pC)->Fill(p2c, p28, p14))
        b334 = 1;
}
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
struct Resource_s0076_4df0 : IUnknown32 {
    AtomicInt mRefCount; int k0, k1, k2;
    Resource_s0076_4df0() { mRefCount = 0; k0 = 0; k1 = 0; k2 = 0; }
};
struct cResourceBase : Resource_s0076_4df0 { int* cb; cResourceBase() { cb = 0; } };
struct D765f10 : cResourceBase {
    int f18;
    void* f1c;
    D765f10(void* arg);
};
// ---- items of slice s00764df0 end

// ---- items of slice s00765f80 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void __cdecl sub_87cf40(void* p);
extern "C" void __cdecl sub_87cf60(void* p, int v);
extern "C" bool __cdecl sub_87d2a0(void* p, int a, int b);
extern "C" bool __cdecl sub_87d030(void* p, void* a, int n);
extern "C" void __cdecl sub_87cff0(void* p);
extern "C" void __cdecl sub_87d260(void* p);
extern "C" void* __cdecl Ctor765f10(void* p);   // 0x765f10
extern "C" void* __cdecl Ctor763100(void* p);   // 0x763100
extern "C" void* __cdecl Ctor7004d0(void* p);   // 0x7004d0
extern "C" void __cdecl sub_4e0880(void* vec, uint32_t n);
extern "C" void* __cdecl EA_Alloc6(uint32_t size, const char* name, int a, int b, const char* file, int line);
extern "C" void* __cdecl EA_Alloc8(uint32_t size, int align, int a, const char* name, int b, int c, const char* file, int line);
extern "C" void  __cdecl EA_Dealloc(void* p);
extern "C" void* __cdecl memcpy_t(void* dst, const void* src, uint32_t n);
extern "C" void  __cdecl sub_6c20b0(void* p);
extern "C" void  __cdecl sub_6c2060(void* p, int a, int b);
extern "C" void  __cdecl sub_6c20e0(void* p);
extern "C" void* __cdecl MessageServer();
extern "C" void* __cdecl Manager67dcd0();
extern "C" bool  __cdecl ReadInt32(void* stream, void* dst, int count, int flags);
extern "C" void  __cdecl sub_4b54b0(void* p);
extern "C" void  __cdecl sub_6ac0a0(int a, void* b);
extern "C" void  __cdecl sub_11eff60(void* p);
extern "C" void  __cdecl cLocalLightInfo_dtor(void* alloc, void* obj);
extern "C" char* __cdecl BigMoveBack(char* dst, char* first, char* last, char* src);   // 0x764720
extern "C" char* __cdecl BigMove(char* dst, char* first, char* last);                  // 0x763f10
extern "C" char* __cdecl BigUninitFill(char* dst, uint32_t n, char* value);            // 0x765200
extern "C" void __cdecl VecReserve41e4d0(void* vec, int n);               // 0x41e4d0
extern "C" void __cdecl PushDeclareParam(void* vec, int* v);              // 0x4e19a0
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
};
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
    BaseP() { (void)_InterlockedExchange((volatile long*)&mRef, 0); k8 = 0; kc = 0; k10 = 0; k14 = 0; x18 = 0; }
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
struct Elem8 {
    void* p;
    int   x;
    Elem8() : p(0), x(0) {}
    ~Elem8() {}
};
struct ResD {
virtual void d0();
virtual void d1();
virtual void d2();
virtual void d3();
    virtual ~ResD();
    int mRef;                 // +0x4
    int m08, m0c, m10, m14;   // +0x8..+0x14
    void* mArena;             // +0x18
    Elem8* mpBegin;           // +0x20
    Elem8* mpEnd;             // +0x24
    Elem8* mpCap;             // +0x28
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
void* InitResE(void* p) { return new (p) ResE(); }
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
struct IPngArg {
virtual void a0();
virtual void a1();
virtual void a2();
virtual void a3();
virtual void a4();
virtual void a5();
virtual void a6();
virtual void a7();
    char pad[0x18];
    void* mMgr;               // +0x1c (approx)
};
struct PngArg {
    char pad[0x8];
    IPngArg* p08;             // +0x8
};
void* InitResE(void* p);
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
struct IResMgr {
virtual void m0();
virtual void m1();
virtual void m2();
virtual void m3();
    virtual bool m4(void* key, void** outA, void** outB, int, int, int, int, int);
};
struct ResHandle { virtual void h0(); virtual void h1(); virtual void h2(); virtual void h3(); };
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
struct Reader { IStream* mStream; int mField2c; };
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
extern "C" void  __cdecl FUN_00763f50(void* a, void* b, void* c);
extern "C" void* __cdecl FUN_00764320(void* a, void* b, void* c);
extern "C" void  __cdecl FUN_00765ac0(void* p);
extern "C" void  __cdecl VBigInsert(void* vec, void* pos, uint32_t n, void* value);    // 0x7662d0
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
};
struct PaintHolder {
    char pad[0x20];
    bool FUN_00767170(void* a, void* b, void* c);
};
struct VBig2 { char* b; char* e; char* c; void Resize(int, uint32_t n); };
// ---- items of slice s00766fa0 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
bool __stdcall ReadPaintStuff(PaintObj* obj, void* stream, void* p3);  // 0x00766fa0 (stays in the slice: not this object's)

// ---- items of slice s00767ee0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  __fastcall FUN_007642c0(void* self);                                // 0x7642c0 (thiscall)
extern "C" void  __cdecl FUN_00764760(void* self, int v);                              // 0x764760 (thiscall)
extern "C" void  __cdecl FUN_0041f2d0(void* p);                                        // 0x41f2d0
extern "C" void  __cdecl FUN_00700670(void* a, void* b);                               // 0x700670
extern "C" void  __cdecl FUN_00767350(void* self, void* pos, uint32_t n, void* value); // 0x767350
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
struct V7cB {
    char* b; char* e; char* c;
    void Resize(uint32_t n);
};
struct C68370 {
    void* m0; void* m4; void* m8; void* mc; void* m10; void* m14;
    int   m18; int m1c; int m20; int m24; void* m28;
    char pad2c[0xd0];
    int   mFC; int m100; void* m104; void* m108; void* m10c; void* m118;
    void* m19c; void* m1a0; void* m1a4; void* m1b0; char m334;
    C68370(void* a, int* b, void* c, int* d, void* e);
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
extern "C" void* __cdecl Alloc6(uint32_t size, const char* name, int a, int b, const char* file, int line); // 0xf473a0
extern "C" void  __cdecl FUN_007006d0(void* p);                                        // 0x7006d0
extern "C" char  __cdecl FUN_007638a0(void* a, void* b, void* c, void* d);             // 0x7638a0
extern "C" char  __cdecl FUN_00767170(void* a, void* b, void* c);                      // 0x767170
extern "C" char  __cdecl ReadMaterialList(void* a, void* b, void* c);                  // 0x767c80
extern "C" char  __cdecl FUN_00764ce0(void* a, void* b, void* c);                      // 0x764ce0
extern "C" char  __cdecl FUN_007637d0(void* a, void* b, int c, void* d);               // 0x7637d0
extern "C" char  __cdecl ReadResourcePCAWeights(void* a, void* b, void* c);            // 0x763950
extern "C" char  __cdecl FUN_00769cf0(void* a, void* b, void* c);                      // 0x769cf0
extern "C" char  __cdecl FUN_00769310b(void* a, void* b, void* c, void* d);            // 0x769310
extern "C" void* __cdecl FUN_0093b530(int a, int b, void* c);                          // 0x93b530
// ---- items of slice s00769310 end

// ---- items of slice s00769f20 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl Node8F4d0(void);                                             // 0x68f4d0
extern "C" void* __cdecl FUN_0067de70();                                              // 0x67de70
extern "C" void* __cdecl FUN_00768370v(void* a, void* b, void* c, void* d, void* e);  // 0x768370
extern "C" char  __cdecl FUN_007666a0v(void* a, void* b, void* c);                    // 0x7666a0
extern "C" char  __cdecl FUN_00769d80v(void* a, void* b, void* c, void* d);           // 0x769d80
extern "C" char  __cdecl FUN_00765b30v(void* a, void* b);                             // 0x765b30
extern "C" char  __cdecl FUN_00765d30v(void* a, void* b);                             // 0x765d30
extern "C" char  __cdecl FUN_007652c0v(void* a, void* b);                             // 0x7652c0
extern "C" char  __cdecl FUN_007655f0b(void* a, void* b, void* c);   // 0x7655f0
extern "C" bool  __fastcall ArmDecodeB(void* self, int, int);         // 0x7677c0
extern "C" char  __cdecl FUN_0076a940v(void* a, void* b, void* c, void* d, void* e);   // 0x76a940
struct C69a9 { char pad0[0x10]; void* m10; char pad14[4]; int m18; char pad1c[0x18]; };
// ---- items of slice s00769f20 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
bool __fastcall SetupJobChain(void* self, int, int unused);  // 0x00769f20 (stays in the slice: not this object's)
bool __fastcall CreateRequestJob(void* self, int, void* out);  // 0x0076a400 (stays in the slice: not this object's)
bool __fastcall TryLockChain(void* self, int, int unused);  // 0x0076a4d0 (stays in the slice: not this object's)

// @ 0x00683f10
int RefCounted::AddRef()
{
    return (int)((_InterlockedExchangeAdd((volatile long*)&mRef, 2) + 2) >> 1);
}

// @ 0x00763100
CEditorRes::CEditorRes()
{}

// @ 0x00763250
int __fastcall Release763250(void* self)
{
    volatile int* rc = (volatile int*)((char*)self + 4);
    int n = _InterlockedExchangeAdd((volatile long*)rc, -2) - 2;
    if (n == 0) {
        _InterlockedExchange((volatile long*)rc, 2);
        if (g_flags1630180 != 0 || g_word160077c != *(int*)__readfsdword(0x18)) {
            void* o = GetGlobal67de80();
            (void)o; (void)self;
        } else if (self != 0) {
            ((IObj*)self)->s2(1);
        }
    } else if (n == 3) {
        void* p = *(void**)((char*)self + 0x14);
        if (p != 0)
            (*(void(__thiscall**)(void*, void*))p)(*(void**)p, self);
    }
    return n;
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
bool __cdecl LoadRasterHeader(cRasterFromGimexLoadState_s0076_2d70* s, const char* name, void* unused)
{
    (void)s; (void)name; (void)unused; return false;
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
bool __stdcall LoadAndCreateRaster(cRasterFromGimexLoadState_s0076_2d70* src, int a, int b, int* out3)
{
    (void)src; (void)a; (void)b; (void)out3; return false;
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
bool SP::cGraphicsResourceFactory::ReadResourcePCAWeights(EA::IO::IStream * a, EA::ResourceMan::Resource * b, EA::ResourceMan::Key const & a3)
{
    (void)a; (void)b; return false;
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

// @ 0x007642c0
D7642c0::~D7642c0()
{}

// @ 0x00764670
void Loader::Wrap670(int)
{
    RasterCtx* ctx = (RasterCtx*)pC;
    char ok = ctx->Create(p2c, p28, p14);
    if (ok)
        b334 = 1;
}

// @ 0x007646a0
void Loader::Wrap6a0(int)
{
    ((Ctx63620*)pC)->Load(p2c, p28, p14);
}

// @ 0x007650d0
void Loader29::WrapA50(int)
{
    ((Ctx764a50*)pC)->ReadArena(p2c, p28, p14);
}

// @ 0x00765150
void Loader29::WrapDf0(int)
{
    Ctx764df0* ctx = (Ctx764df0*)pC;
    char ok = ctx->CreateRaster(p2c, p28, p14);
    if (ok)
        b334 = 1;
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

// @ 0x00765f10
D765f10::D765f10(void* arg)
{
    f18 = 0;
    f1c = arg;
    if (arg)
        ((IUnknown32*)arg)->u0();
    f18 = 0;
}

// @ 0x00765f80
IResEd::~IResEd()
{ if (m1c) m1c->Release(); }

// @ 0x00765fe0
ResB::ResB()
: a20(0), a24(0), a28(0), a2c(0) {}

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
: mRef(0), m08(0), m0c(0), m10(0), m14(0), mArena(0),
               mpBegin(0), mpEnd(0), mpCap(0) {
    Elem8 tmp[4];
    (void)tmp;
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
    unsigned char* buf = (unsigned char*)_alloca(0x2a70);
    (void)buf;
    IPngArg* a = arg->p08;
    void* inner = *(void**)((char*)a + 0xc);
    int c1c = *(int*)((char*)inner + 0x1c);
    void* c20 = *(void**)((char*)inner + 0x20);
    void* ctx = 0;
    (void)c1c; (void)c20;
    if (*(char*)((char*)a + 0x18)) {
        // formatted debug string path (stubbed)
    }
    sub_87cf40(&ctx);
    void* m = *(void**)((char*)a + 0x10);
    int v = ((int(__thiscall**)(void*))VP(m))[0x18 / 4](m);
    sub_87cf60(&ctx, v);
    bool ok = sub_87d2a0(&ctx, 1, 4);
    if (ok) {
        ok = sub_87d030(&ctx, *(void**)((char*)inner + 0x28), *(int*)((char*)arg + 0x44) * 4) != 0;
        sub_87cff0(&ctx);
        m = *(void**)((char*)a + 0x10);
        ((void(__thiscall**)(void*))VP(m))[0x24 / 4](m);
        void* srv = MessageServer();
        if (srv && *(void**)((char*)a + 0x14))
            ((void(__thiscall**)(void*, void*, int, int, int))VP(srv))[0x18 / 4](
                srv, *(void**)((char*)a + 0x14), 0, 0, 0);
    }
    sub_87d260(&ctx);
    return ok;
}

// @ 0x007666a0
bool __stdcall CreateByType(void** out, uint32_t type, int sub)
{
    void* obj = 0;
    if (type < 0x2cb4f30) {
        if (type == 0x2f4e681b) {
            void* p = EA_Alloc6(0x3fe4, "RenderAsset", 0, 0, 0, 0);
            if (p) {
                // cPropertyList base ctor + derived vtable
                *(void**)p = (void*)0x13ebcdc;
                _InterlockedExchange((volatile long*)((char*)p + 4), 0);
                *(int*)((char*)p + 8) = 0;
                *(int*)((char*)p + 0xc) = 0;
                *(int*)((char*)p + 0x10) = 0;
                *(int*)((char*)p + 0x14) = 0;
                // (large body stubbed)
                obj = p;
            }
        } else if (type == 0x2cb4f2f) {
            void* p = EA_Alloc6(0x140, "RenderAsset", 0, 0, 0, 0);
            if (p) obj = Ctor7004d0(p);
        } else if (type == 0x1c135da) {
            void* p = EA_Alloc6(0x2c, "RenderAsset", 0, 0, 0, 0);
            if (p) obj = Ctor763100(p);
        }
    } else if (type == 0x2f4e681b) {
        // unreachable by ordering
    } else if (type == 0x2f4e681c) {
        if (sub == 0x2f4e681b) {
            void* p = EA_Alloc6(0x20, "RenderAsset", 0, 0, 0, 0);
            if (p) obj = Ctor765f10(p);
        } else {
            void* p = EA_Alloc6(0x1c, "RenderAsset", 0, 0, 0, 0);
            if (p) obj = InitResE(p);
        }
    }
    if (obj) {
        *out = obj;
        ((void(__thiscall**)(void*))VP(obj))[0](obj);   // AddRef
        ((void(__thiscall**)(void*))VP(obj))[1](obj);   // Release
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
        uint32_t* nb = need ? (uint32_t*)EA_Alloc6(need * 4, "Graphics", 0, 0, g_allocFile_s0076_5f80, 0xd1) : 0;
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
bool RequestPaintDecalsFromModels(void* self, void* job)
{
    char* s = (char*)self;
    // reserve
    sub_4e0880(s + 0x104, (uint32_t)((*(int*)(s + 0x1a0) - *(int*)(s + 0x19c)) / 0xc));
    uint32_t have = (uint32_t)((*(int*)(s + 0x108) - *(int*)(s + 0x104)) >> 2);
    uint32_t want = (uint32_t)((*(int*)(s + 0x1a0) - *(int*)(s + 0x19c)) / 0xc);
    while (have < want) {
        if (*(void**)(s + 0x100) == 0) {
            IResMgr* mgr = (IResMgr*)Manager67dcd0();
            ResHandle* hA = 0;
            ResHandle* hB = 0;
            bool ok = ((IResMgr*)mgr)->m4(s + 0x19c + have * 0xc, (void**)&hA, (void**)&hB, 0, 0, 0, 0, 0);
            if (!ok) {
                if (hA) { hA->h1(); hA = 0; }
                if (hB) { hB->h1(); hB = 0; }
            }
            ResHandle* got = hA ? (ResHandle*)((int(__thiscall**)(ResHandle*, int))VP(hA))[0xc / 4](hA, 0x3a212ac) : 0;
            ResHandle* old = *(ResHandle**)(s + 0x100);
            if (got != old) {
                if (got) got->h0();
                *(ResHandle**)(s + 0x100) = got;
                if (old) old->h1();
            }
            if (hB == 0 && *(void**)(s + 0x100) != 0) {
                // continuation
                sub_4b54b0(&hB);
                if (hB) sub_6ac0a0(2, hB);
                if (hB) hB->h1();
                if (hA) hA->h1();
                return true;
            }
            sub_4b54b0(&hB);
            if (hB) sub_6ac0a0(2, hB);
            if (hA) hA->h1();
        } else {
            ResHandle* local = 0;
            ((void(__thiscall**)(ResHandle*, ResHandle**))VP(*(void**)(s + 0x100)))[0x14 / 4](
                *(ResHandle**)(s + 0x100), &local);
            ResHandle* old = *(ResHandle**)(s + 0x100);
            if (old) { *(void**)(s + 0x100) = 0; old->h1(); }
            sub_4b54b0(&local);
            if (local) sub_6ac0a0(2, local);
            if (local) local->h1();
        }
        have = (uint32_t)((*(int*)(s + 0x108) - *(int*)(s + 0x104)) >> 2);
    }
    return true;
}

// @ 0x00766e10
bool __fastcall ReadDecalBlock(Reader* r)
{
    int n = r->mStream->sC(&r->mField2c, 4);
    if (n != 4)
        return false;
    int count = r->mField2c;
    if (count < 8 || count > 9)
        return false;
    int num = 0;
    if (!ReadInt32(r->mStream, &num, 1, 0))
        return false;
    VecReserve41e4d0((char*)r + 0x19c, num);
    for (int i = 0; i < num; i++) {
        int v[3] = {0, 0, 0};
        if (!ReadTriplet763340(r->mStream, v, 0))
            return false;
        PushDeclareParam((char*)r + 0x19c, v);
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

// @ 0x00767170
bool PaintHolder::FUN_00767170(void* a, void* b, void* c)
{
    char* stackObj = (char*)this;
    char tmp[0xd0];
    (void)tmp;
    if (ReadPaintStuff((PaintObj*)stackObj, a, b)) {
        if (FUN_00764320(stackObj, a, b)) {
            uint32_t* s = (uint32_t*)c;
            char* d = (char*)b;
            *(uint32_t*)(d + 8) = s[0];
            *(uint32_t*)(d + 0xc) = s[1];
            *(uint32_t*)(d + 0x10) = s[2];
            FUN_00765ac0(stackObj);
            return true;
        }
    }
    FUN_00765ac0(stackObj);
    return false;
}

// @ 0x00767290
void VBig2::Resize(int, uint32_t n)
{
    uint32_t size = (uint32_t)((e - b) / 0xa0);
    if (size < n) {
        VBigInsert(this, e, n - size, 0);
        return;
    }
    char* dst = b + n * 0xa0;
    FUN_00763f50(e, e, dst);
    e = e + (uint32_t)((e - dst) / 0xa0) * 0xa0;
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

// @ 0x007682a0
void V7cB::Resize(uint32_t n)
{
    uint32_t count = (uint32_t)((e - b) / 0x7c);
    if (count < n) {
        char tmp[0x7c];
        FUN_00764760(&tmp, 0);
        FUN_00767350(this, e, n - count, tmp);
        FUN_0041f2d0(&tmp);
    } else {
        FUN_00700670(b + n * 0x7c, e);
    }
}

// @ 0x00768370
C68370::C68370(void* a, int* b, void* c, int* d, void* e)
{
    m0 = (void*)0;            // vtable (masked)
    m4 = (void*)0;
    _InterlockedExchange((volatile long*)&m8, 0);
    m0 = (void*)0;
    m4 = (void*)0;
    mc = b;
    if (b) ((void(__thiscall**)(void*))*(void***)b)[1](b);
    m10 = e;
    if (e) ((void(__thiscall**)(void*))*(void***)e)[1](e);
    m14 = a;
    if (a) ((void(__thiscall**)(void*))*(void***)a)[0](a);
    m18 = 0; // param_6 (int) - approximated
    m1c = d[0];
    m20 = d[1];
    m24 = d[2];
    m28 = 0;
    mFC = 0; m100 = 0;
    m104 = (char*)this + 0x11c;
    m108 = (char*)this + 0x11c;
    m10c = (char*)this + 0x19c;
    m118 = 0;
    m19c = (char*)this + 0x1b4;
    m1a0 = (char*)this + 0x1b4;
    m1a4 = (char*)this + 0x334;
    m1b0 = 0;
    m334 = 0;
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
char __fastcall ReadResourceFromStream(void* self, int, int* obj1, int* obj2, void* a4)
{
    (void)self;
    int* holder = 0;
    int local = 0;
    (void)holder; (void)local;
    if (obj1 && ((int(__thiscall**)(int*))*(void***)obj1)[3](obj1) == 0x34722300) {
        void* p = Alloc6(0x34, "Graphics", 0, 0, 0, 0);
        if (p)
            p = FUN_0093b530(0x2000, 0, obj1);
        if (p) {
            ((void(__thiscall**)(void*))*(void***)p)[1](p);
            holder = (int*)p;
        }
    }
    uint32_t type = *(uint32_t*)((char*)obj2 + 4);
    char r = 0;
    bool handled = true;
    if (type < 0x2cb4f30) {
        if (type == 0x2cb4f2f)
            r = ReadResourcePCAWeights(holder, obj2, obj1);
        else if (type == 0xe6bce5)
            r = FUN_00769cf0(holder, obj2, obj1);
        else if (type == 0x1c135da)
            r = ReadMaterialList(holder, obj2, obj1);
        else
            handled = false;
    } else if (type == 0x2f4e681b) {
        r = FUN_00764ce0(holder, obj2, obj1);
    } else if (type == 0x2f4e681c && (uint32_t)(size_t)a4 <= 0x2f7d0004) {
        if ((size_t)a4 == 0x2f7d0004)
            r = FUN_007637d0(holder, obj2, 4, obj1);
        else if ((size_t)a4 != 0x2f4e681b && (size_t)a4 == 0x2f4e681c)
            r = FUN_00767170(holder, obj2, obj1);
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

// @ 0x0076a720
bool __fastcall CanConvert(void* self, int, void* out)
{
    C69a9* s = (C69a9*)self;
    void* a = Node8F4d0();
    ((void(__thiscall**)(void*))*(void***)a)[8](a);
    int holder = 0;
    int type = s->m18;
    char r;
    if (type < 0x2f4e681c) {
        if (type == 0x2f4e681b) r = FUN_00765b30v(self, &holder);
        else if (type == 0xe6bce5) r = SetupJobChain(self, 0, 0);
        else if (type == 0x1c135da) r = TryLockChain(self, 0, 0);
        else r = CreateRequestJob(self, 0, &holder);
    } else if (type == 0x2f4e681c) {
        void* p = (void*)((int(__thiscall**)(void*))*(void***)s->m10)[4](s->m10);
        uint32_t sub = *(uint32_t*)((char*)p + 4);
        if (sub < 0x2f7d0005) {
            if (sub == 0x2f7d0004) r = FUN_007652c0v(self, &holder);
            else if (sub == 0x2f4e681b) r = FUN_00765d30v(self, &holder);
            else if (sub == 0x2f4e681c) r = ArmDecodeB(self, 0, 0);
            else return false;
        } else if (sub == 0x2f7d0007) r = FUN_007652c0v(self, &holder);
        else return false;
    } else {
        r = CreateRequestJob(self, 0, &holder);
    }
    if (!r)
        return false;
    *(void**)out = (void*)holder;
    return true;
}

// @ 0x0076a940
bool __cdecl CreateConvertedResourceAsync(void* a, void* b, void* c, int* d, void* e)
{
    if (!FUN_0067de70())
        return false;
    void* res = 0;
    int t = ((int(__thiscall**)(int*))*(void***)d)[4](d);
    if (!FUN_007666a0v(&res, e, *(void**)((char*)t + 4)))
        return false;
    void* job = Alloc6(0x338, "Graphics", 0, 0, 0, 0);
    if (job)
        job = FUN_00768370v(res, b, c, d, e);
    if (job)
        ((void(__thiscall**)(void*))*(void***)job)[0](job);
    ((void(__thiscall**)(int*))*(void***)d)[8](d);
    return true;
}

// @ 0x0076ac30
bool __fastcall CreateResourceAsync(void* self, int, void* out, int* param_4, void* p5, void* p6, int p7)
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
    return true;
}
