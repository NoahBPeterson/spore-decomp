// src/game/SPEngine/_at_007a0000.cpp -- migrated from slice(s) s007a7d50, s007a41c0, s007a3260, s007a1740, s007a07b0, s0079f8d0 by tools/migrate/rewrite.py
// Object file: SPEngine/_at_007a0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cModelInstance.h"
#include <intrin.h>
#include <new>
#include "SP/cDebugDraw.h"
#include "SP/cGraphicsSystem.h"
#include "SP/cIRTTManager.h"
#include "SP/cIRenderer.h"
#include "SP/cPropertyList.h"
#include "SP/cStaticBuffer.h"
#include "SP/cStaticBufferDraw.h"
#include "SP/cViewer.h"
#include <math.h>
#include <stdlib.h>
#include "SP/cEffectsRenderer.h"
#include "SP/cEffectsResources.h"
#include "SP/cFilterChain.h"
#include "SP/cShadowWorld.h"
#include "SP/cTextRenderer.h"
#include <xmmintrin.h>

// unnamed retail callees and globals (address in the comment)
extern "C" void  operator_delete(void* p);                            // 0x00f47380

// ---- items of slice s0079f8d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint;
struct VecBase {
  void* mpBegin;                      // +0x00
  void* mpEnd;                        // +0x04
  void* mpCapacity;                   // +0x08
  void* mAllocator;                   // +0x0c
};
struct Tc {
  // --- 0x14-byte-element vector helpers: original __thiscall (receiver in ecx) ---
  void  m_0079a4a0(int a);                       // move-construct into this (1 stack arg)
  void  m_0079a6c0(int a);                       // shallow-copy-construct into this (1 stack arg)
  void  m_0079f640(int a);                       // copy-assign into this (1 stack arg)
  void  m_0079f4e0(int a, int b);                // push_back (2 stack args)
  int   m_0079ae00(int n, int a, int b);         // allocate n (3 stack args, ret 0xc)
  void  m_0079b0d0(int a, int b);                // destroy range (2 stack args)
  void  m_0079b150(int a);                       // construct a vector temp into this (1 stack arg, ret 4)
  void  m_01023030(int a, int b);                // destroy [a,b) 0x14-elements (2 stack args)
  int   m_00424cf0(int src, int nbytes);         // DoInsertValue: move nbytes to `this`
  // --- direct thiscall helpers on the target objects ---
  void  m_0537dc0(void* a);                 // cSPTransform::operator= (1 stack arg)
  void  m_07993a0();                        // cSplitInstance() (0 stack args)
  void  m_0799450(void* a);                 // cSplitInstance(copy) (1 stack arg)
  // --- sibling target functions (called as thiscall members / defined below) ---
  void  m_0079f8d0(int first, int last);         // ret 8
  void  m_0079fa20(int first, int last);
  void  m_0079fa70(int pos, int n, int value);
  __declspec(noinline) void m_007a0010(int n);
  void  m_007a0110(void* pos, int n, void* value);
  void* m_007a0460(void* other);
  void  m_007a0600(void* pos, void* value);
  int   m_0079ff40(void* src);
};
void  FUN_0079a710(int a, int b, int c, int d, int e);
int   FUN_0079ab00(int a, int b, int c);
int   FUN_0079f730(int a, int b, int c);         // returns dst
extern "C" void  operator_delete(void* p);                            // 0x00f47380
static inline int count14(void* beg, void* end) {
  return (int)((char*)end - (char*)beg) / 0x14;   // signed /20, matches 0x66666667 reciprocal
}
static inline bool spNeedsDelete(void* p) {
  return p != 0 && *((int*)p - 1) != 0;
}
void Tc::m_0079fa20(int first, int last) {
  VecBase* v = (VecBase*)this;
  char* res = (char*)FUN_0079ab00(last, (int)v->mpEnd, first);  // relink tail
  ((Tc*)this)->m_01023030((int)res, (int)v->mpEnd);                     // destroy range
  v->mpEnd = (char*)v->mpEnd + ((last - first) / 0x14) * 0x14;
}
// ---- items of slice s0079f8d0 end

// ---- items of slice s007a07b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* memmove_thunk_11e0744(void* dst, const void* src, unsigned n);  // memmove
extern "C" long _InterlockedExchange(long volatile*, long);
extern "C" long _InterlockedIncrement(long volatile*);
extern "C" long _InterlockedDecrement(long volatile*);
extern unsigned g_renderStateDirty;     // 0x16fa38c
extern int g_drawFlag;                  // 0x16f9238
#pragma intrinsic(_InterlockedExchange, _InterlockedIncrement, _InterlockedDecrement)
void* operator new(unsigned int, const char*, int, unsigned int, const char*, int);
void operator delete[](void*) throw();
static __forceinline unsigned ByteDiff(const void* last, const void* first) { return (unsigned)((const char*)last - (const char*)first); }
#define MOVE(d, s, n) memmove_thunk_11e0744((d), (s), (n))
struct V20 {                       // value with copy-ctor 0x79a4a0, dtor 0x432e80
    int* b; int* e; int* c; int x; int y;
    V20() : b(0), e(0), c(0) {}
    V20(const V20&);               // 0x79a4a0
    ~V20();                        // 0x432e80
};
struct V20Pod {                    // same shape, trivially destructible (vector<cSplitInstanceList>)
    int* b; int* e; int* c; int x; int y;
    V20Pod() : b(0), e(0), c(0) {}
    ~V20Pod() { b = 0; }
};
struct VecV20 {
    V20* mpBegin; V20* mpEnd; V20* mpCapacity;
    void Insert(V20* pos, unsigned n, const V20* val);
    void InsertC(V20* pos, unsigned n, const V20& val);   // same routine, by-reference spelling   // 0x7a07b0
    void Resize(unsigned n);                              // 0x7a1100
    V20* EraseTail(V20* first, V20* last);                // 0x7a05b0
};
struct VecPod20 {
    V20Pod* mpBegin; V20Pod* mpEnd; V20Pod* mpCapacity;
    void Resize(unsigned n);
    void UninitInsertN(V20Pod* pos, unsigned n, const V20Pod& val);   // 0x7a0110
    V20Pod* DestroyRangeP(V20Pod* first, V20Pod* last);              // 0x7a00c0
};
struct RefBase {
    virtual ~RefBase() {}
    volatile long mnRefCount;
    RefBase() { _InterlockedExchange(&mnRefCount, 0); }
    __forceinline void AddRef() { _InterlockedIncrement(&mnRefCount); }
    __forceinline int Release() {
        long n = _InterlockedDecrement(&mnRefCount);
        if (n == 0) { _InterlockedExchange(&mnRefCount, 1); delete this; }
        return (int)n;
    }
};
struct Transform0x30 { void Reset(int arg); };       // 0x79a3f0 (thiscall)
struct V16 { int a, b, c, d; };
V16* CopyV16(V16* first, V16* last, V16* dest);        // 0x705250 (cdecl)
struct SplitMgr : RefBase {
    int a8[3]; int pad14, pad18; int a1c[3]; int pad28, pad2c; Transform0x30 t30; int a30tail[2];
    int pad3c, pad40; int a44[3]; int pad50, pad54;
    SplitMgr() {
        int* w = (int*)this;
        w[2] = 0; w[3] = 0; w[4] = 0;
        w[7] = 0; w[8] = 0; w[9] = 0;
        w[0xc] = 0; w[0xd] = 0; w[0xe] = 0;
        w[0x11] = 0; w[0x12] = 0; w[0x13] = 0;
    }
};
template <class T> struct AutoRef {
    T* mp;
    __forceinline AutoRef& operator=(T* p) {
        T* old = mp;
        if (p != old) {
            if (p) p->AddRef();
            mp = p;
            if (old) old->Release();
        }
        return *this;
    }
};
struct U16Vec { unsigned short* b; unsigned short* e; unsigned short* c; int x, y; };
struct SplitState {
    AutoRef<SplitMgr> mMgr;       // +0
    V16* mpBegin; V16* mpEnd;     // +4/+8 (vector of 16-byte elements)
    int pad[3];
    VecPod20 mLists;              // +0x18
    // 0x7a0cd0
    void Reset(int a, int b);
};
struct SplitState2 {
    AutoRef<SplitMgr> mMgr;       // +0
    int pad4;
    SplitState mSub;              // +8 (size 0x24)
    char pad48[0x48 - 0x8 - sizeof(SplitState)];
    VecPod20 mLists48;            // +0x48
    void Reset(int a, int b);     // 0x7a0de0
};
struct IntVecVec { int* mpBegin; int* mpEnd; int* mpCap; };
void ClearVecVec(IntVecVec* v);                            // 0x7a0410
struct BaseA {
    virtual void vA();      // 0x51e340
    virtual void vA1();     // 0x51e380
    virtual void vA2();     // 0x402ab0
    virtual void vA3();     // 0x7a11c0
};
struct GmeRefCount {        // RefCountTemplate<int> base; vtable 0x13ef094
    virtual ~GmeRefCount() {}   // slot 0 (in SplitDrawBase: this-4 thunk 0x79ab80 -> deleting dtor 0x7a0ac0)
};
struct PlainRc {
    virtual ~PlainRc() {}
    int mnRefCount;
    __forceinline int Release() {
        int n = mnRefCount + -1;
        mnRefCount = n;
        if (n == 0) { mnRefCount = 1; delete this; }
        return n;
    }
};
template <class T> struct RcPtr {
    T* mp;
    ~RcPtr() { if (mp) mp->Release(); }
};
struct CIntVec {
    int* mpBegin; int* mpEnd; int* mpCap;
    void DestroyRange(int* first, int* last) throw();   // 0x1023030 (thiscall)
    ~CIntVec() {
        // element destruction through 0x1023030, then buffer release
        DestroyRange(mpBegin, mpEnd);
        if (mpBegin && ((int*)mpBegin)[-1]) operator delete[](mpBegin);
    }
};
struct SplitDrawBase : BaseA, GmeRefCount {
    int pad8;
    RcPtr<PlainRc> mA;            // +0xc
    CIntVec mVec;                 // +0x10
    int pad1c, pad20;
    RcPtr<PlainRc> mC;            // +0x24
    ~SplitDrawBase();             // 0x7a09f0
};
struct V20Tmp { int w[5]; ~V20Tmp(); };     // 0x432e80 dtor
struct V12 {
    V20* b; V20* e; V20* c; int x; int y;
    V12() : b(0), e(0), c(0) {}
    V12(const V12&);                       // 0x79b020
    V12& Assign(const V12&);               // 0x7a0460 (operator=, thiscall)
    ~V12();                                // 0x432de0
    void Swap(V12& other);                 // 0x7a0b90
    void Free(V20* first, V20* last);      // 0x79b0d0 (thiscall)
    void Add(const V20Tmp& v);             // 0x7a0c50 (thiscall)
};
static __forceinline void SwapPtr(V20*& a, V20*& b) { V20* t = a; a = b; b = t; }
struct MeshList {                           // 12-byte RefVector
    int* b; int* e; int* c;
    MeshList() : b(0), e(0), c(0) {}
    ~MeshList();                            // 0x41eb80 (RefVector::~RefVector)
};
struct IModelSplitter {
    virtual void v0();
    virtual void Notify(V12* out);          // vtbl+4
    void Process(int a, V12* vec);          // 0x7a0ee0
    void Split(int meshes, V12* out);       // 0x7a0f90
};
void CompileSplitModels(V12* models, V12* out);        // 0x7a0360 (cdecl)
struct MapNode { MapNode* a; MapNode* b; int pad[2]; int key; };
struct V12Src {                          // vector built from the host's manager; inline dtor
    V20* b; V20* e; V20* c; int x; int y;
    V12Src(int arg) : b(0), e(0), c(0) { Init(arg); }
    void Init(int arg);                  // 0x79a4f0 (thiscall)
    ~V12Src() {
        ((V12*)this)->Free(b, e);
        if (b && ((int*)b)[-1]) operator delete[](b);
    }
    void Swap(V12& other) { ((V12*)this)->Swap(other); }
};
struct ApplyHost {
    int pad[4];
    int pad10, pad14;       // +0x10: map header node
    MapNode* mRoot;         // +0x18
    int pad1c;
    int mArg;               // +0x20
    void Apply(V12* target);
};
struct CompiledElem { int mesh; int material; };
struct ElemList { CompiledElem* b; CompiledElem* e; CompiledElem* c; int p3, p4; };   // 20 bytes
struct SplitInstEntry { int key; char pad[0x3c]; char xform[0x38]; };                 // 0x78 bytes
struct SplitInstList { int nextFree; SplitInstEntry* b; SplitInstEntry* e; int pad[4]; };  // 0x1c bytes
struct SplitMgrData { char pad[0x40]; SplitInstList* mb; SplitInstList* me; };
struct ModelInstance {
    void GetMeshes(MeshList* out);                                   // 0x73eb90
    void SetTransform(const void* xf, int a);                        // 0x73eca0
    void DrawMesh(int mesh, int material, int b, int a);             // 0x73ede0
};
struct SplitDrawImpl {
    int pad0[3];
    IModelSplitter* mSplitter;          // +0xc
    ElemList* mpBegin;                  // +0x10
    ElemList* mpEnd;                    // +0x14
    int pad18[3];
    SplitMgrData* mMgr;                 // +0x24
    void Dispatch(ModelInstance* model, int a, int b);
};
// ---- items of slice s007a07b0 end

// ---- items of slice s007a1740 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct RcBase {
  virtual void Destroy(int flag) = 0;  // slot 0: deleting destructor
  long rc;                             // +4
  void AddRef() { _InterlockedIncrement(&rc); }
  void Release() {
    long r = _InterlockedDecrement(&rc);
    if (r == 0) {
      _InterlockedExchange(&rc, 1);
      Destroy(1);
    }
  }
};
struct PolyObj {  // virtual slot 1 releases it
  virtual void Slot0();
  virtual void Free();
};
struct Range {  // 0x10-byte range descriptor passed by pointer to Obj15
  int count;
  uint16_t* first;
  short a, b;
  PolyObj* poly;
  Range(int n, uint16_t* f) : count(n), first(f), a(2), b(2), poly(0) {}
  ~Range() { if (poly) poly->Free(); }
};
struct Vec16 {  // 0x14 bytes: a list of 16-bit indices
  uint16_t* b;
  uint16_t* e;
  uint32_t pad[3];
};
struct IdVec6 { void operator=(const IdVec6&);  // 0x00719170
  uint32_t d[12]; };  // FixedIdVector6, 0x30 bytes
struct EntVec3 {  // FixedEntryVector3 (begin/end at +0/+4)
  uint32_t* b;
  uint32_t* e;
  void Erase(uint32_t* f, uint32_t* l);  // 0x004772a0
  void DoAssign(uint32_t* f, uint32_t* l, void* tag);  // 0x0042d020
  uint32_t pad[1];
};
struct Vert {  // 0x8c bytes
  uint32_t pad0[4];
  int f10;
  IdVec6 f14;
  EntVec3 f44;
  uint32_t pad1[0x8c / 4 - 0x44 / 4 - 3];
};
struct Prim { int a, b, c, d, e; };  // 0x14 bytes
struct Inline8 { void Assign(const Inline8&);  // 0x00735dd0
  uint32_t d[5]; };
struct VertVec {  // vector<Vert> at A+0x1c
  Vert* b;
  Vert* e;
  void resize(int n);  // 0x0071f7e0
};
struct A : RcBase {  // source mesh (also the payload of B)
  Inline8 inl;       // +8
  Vert* vb;          // +0x1c
  Vert* ve;          // +0x20
  uint32_t pad24[3];
  Prim* pb;          // +0x30
  Prim* pe;          // +0x34
  void ResizeVerts(int n) { ((VertVec*)&vb)->resize(n); }  // the vertex vector at +0x1c resizes itself
};
struct B;
struct C {  // sub-object at B+8
  uint32_t pad0[6];
  Vec16* v18;  // +0x18
  uint32_t pad1[4];
  int f2c;
  int f30;
  int f34;
  uint32_t pad38;
  int f3c;
  RcBase* Build(A* src);  // 0x007a1400 (called on the sub-object at B+8)
};
struct B {  // builder / destination
  A* p;               // +0
  RcBase* q;          // +4
  C c;                // +8
  Vec16* idx;         // +0x48
  uint32_t pad4c[0x64 / 4 - 0x4c / 4];
  int f64;
  uint32_t pad68[2];
  void Resize(int nPrims, int nVerts);                // 0x007a0de0
  void Emit(Prim pr);                                 // 0x0079b630 (ret 0x14)
  __declspec(noinline) void CopyFrom(A* src);         // 0x007a1740
  B() {
    uint32_t* w = (uint32_t*)this;
    w[0] = 0; w[1] = 0; w[2] = 0; w[3] = 0; w[4] = 0; w[5] = 0;
    w[8] = 0; w[9] = 0; w[10] = 0;
    w[13] = 4;
    w[14] = 0; w[15] = 0; w[16] = 0; w[17] = 0; w[18] = 0; w[19] = 0; w[20] = 0;
    w[23] = 4;
    w[24] = 0; w[25] = 0; w[26] = 0; w[27] = 0;
  }
  ~B();                                               // 0x0079aeb0
};
// ---- items of slice s007a1740 end

// ---- items of slice s007a3260 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void __cdecl operator_delete__(void* p);   // 0x00f47380 (array delete)
extern "C" void __cdecl pushShaderDataNull();                 // 0x00777bf0
extern "C" void __cdecl pushShaderDataPop();                  // 0x00777c10
extern "C" void __cdecl D3D9Sync();                           // 0x011f21a0
extern "C" int __cdecl VertexDescriptorAreEqual(int a, int b);// 0x011f2e70
extern "C" void __fastcall FUN_011f2bc0(int desc);            // applies the vertex descriptor
extern int gCurVertexDesc;          // 0x016f65a0
extern unsigned gDirtyFlags;        // 0x016f9110
extern int gCurIndexBuffer;         // 0x016f8afc
extern int gRendererArg;            // 0x016079a0
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedExchange)
struct cStaticBufferDraw;
extern cStaticBufferDraw* gStaticBufferDraw;                  // 0x015ddc84
void __fastcall FUN_006de2a0(void* self);          // base-class setup (SingletonBase)
struct SingletonBaseStub {
    SingletonBaseStub(cStaticBufferDraw* p) { gStaticBufferDraw = p; }
    ~SingletonBaseStub();
};
struct cStaticBufferDraw : SingletonBaseStub {
    int mStaticBuffer;       // +0x00
    int mField04;
    int mField08;
    int mField0c;
    int mField10;
    int mField14;
    int mField18;
    int mField1c;
    char mField20;
    char _pad21[3];
    int mField24;
    int mField28;
    int mField2c;
    int mField30;
    char _pad34[12];
    char mField40;
    char _pad41[3];
    int mVertexDesc;         // +0x44

    cStaticBufferDraw();
    void SetVertexFormat(int fmt);
    static void sInstanceReset();
};
cStaticBufferDraw* gStaticBufferDraw;
struct ShaderData;
extern "C" void __cdecl SetShaderData(ShaderData* sd);        // 0x00777b50
struct CompiledState { void Dispatch(); };                    // 0x011ee580 (rw::graphics::CompiledState)
struct D3DDevice { void** vt; };
typedef long (__stdcall* DrawPrimFn)(D3DDevice*, int type, int start, int count);
typedef long (__stdcall* DrawIdxFn)(D3DDevice*, int type, int baseVertex, int minIndex, int numVerts, int startIndex, int primCount);
typedef long (__stdcall* SetStreamFn)(D3DDevice*, int stream, int vb, int offset, int stride);
typedef long (__stdcall* SetIndicesFn)(D3DDevice*, int ib);
struct Stream { int vb; int offset; int stride; };
struct DrawStats { char _pad[0x20]; int mVerts; int mTris; int mBatches; };
struct RendererFns { char _pad[0x14]; int (__cdecl* IsReady)(int); };
struct StaticBatch {          // 24-byte draw record
    int mBuffer;              // +0x00 index into mpBuffers
    int mStart;               // +0x04
    int mCount;               // +0x08
    int mIndexSet;            // +0x0c (<0 = none)
    int mIndexOffset;         // +0x10
    int mIndexCount;          // +0x14
};
struct BufferInfo { char* mpDesc; int mVB; int mOffset; };   // mpDesc+0x0f = stride
struct IndexInfo { int mIB; int mBase; };
struct cStaticBuffer {
    char _pad0[8];
    BufferInfo** mpBuffers;       // +0x08
    char _pad0c[0x10];
    IndexInfo** mpIndexSets;      // +0x1c
    char _pad20[0x10];
    StaticBatch* mpBatchBegin;    // +0x30
    StaticBatch* mpBatchEnd;      // +0x34
    char _pad38[0x10];
    int mPrimType;                // +0x48
    void Dispatch(DrawStats* stats, ShaderData* sd);
};
extern Stream gStreams[3];          // 0x016f9144 (streams 1..3)
extern Stream gStream0;             // 0x016f9138
extern RendererFns* gRendererFns;   // 0x016f6568
extern IndexInfo* gDefaultIndexSet; // 0x016079a4
extern D3DDevice* gDevice;          // 0x016f89d0
// ---- items of slice s007a3260 end

// ---- items of slice s007a41c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* EXT_7a3df0(...);
extern "C" void* EXT_f473a0(...);
typedef unsigned int   u32;
struct MeshElement {
  u32 v0;  // +0x00
  u32 v1;  // +0x04
  u32 v2;  // +0x08
  u32 v3;  // +0x0c
  u32 v4;  // +0x10
  u32 v5;  // +0x14
};
struct MeshVector {
  MeshElement* mpBegin;     // +0x00
  MeshElement* mpEnd;       // +0x04
  MeshElement* mpCapacity;  // +0x08

  void grow(MeshElement* at, MeshElement* src);  // 0x007a44b0
  void push_back(MeshElement* src);              // 0x007a4600
};
struct cStaticBuffer_s007a_41c0 {
  virtual void sb00();  // +0x00
  virtual void sb01();  // +0x04  scalar deleting destructor

  u32         mUnk04;             // +0x04
  u32         mUnk08;             // +0x08  element count of vector A
  u32         mUnk0c;             // +0x0c  vector A data pointer
  u32         mUnk10;             // +0x10  pending cursor
  u32         mUnk14;             // +0x14
  u32         mUnk18;             // +0x18
  MeshVector  mVertexBuffers;     // +0x1c .. +0x24
  u32         mUnk28;             // +0x28
  u32         mUnk2c;             // +0x2c  vector B data pointer
  MeshVector  mDrawVector;        // +0x30 .. +0x38
  u32         mUnk3c;             // +0x3c
  u32         mUnk40;             // +0x40  pending-cursor flag byte
  u32         mUnk44;             // +0x44
  u32         mUnk48;             // +0x48

  cStaticBuffer_s007a_41c0* Ctor(u32 param_1, u32 param_2);   // 0x007a4380
  ~cStaticBuffer_s007a_41c0();                                // 0x007a4220
  void Flush();                                    // 0x007a4710
  u32  GetVertexBuffer(u32 numVertices, u32* outCount, u32* outStride);  // 0x007a47c0
  void SnapshotPending();                          // 0x007a4650
};
struct cStaticBufferDraw_s007a_41c0 {
  cStaticBuffer_s007a_41c0 buffer;  // +0x00  (0x4c bytes; the ctor sets +0x48)

  void Ctor(u32 param_1, u32 param_2, u32 param_3, u32 count);  // 0x007a4420
};
// ---- items of slice s007a41c0 end

// ---- items of slice s007a7d50 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* EASTL_allocator_allocate(unsigned int n, const char* name, int flags,
                                          unsigned debugFlags, const char* file, int line); // 0x00f473a0
extern "C" void  EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" void  FUN_00c50ad0(void*, void*, void*);
extern "C" void* FUN_00951bb0(unsigned int, unsigned int, void*);
#pragma intrinsic(_InterlockedExchangeAdd)
struct Layout; struct TextStyle; struct TextRenderWare;
struct PtrPair {                                // 0x190/0x194 pair owner (eastl vector-like)
    void free_0070f520(void* begin, void* end);
};
struct GlyphCacheObj {                          // the 0x1a8-byte object the factory allocates
    void init_0088ae10(void* arg);
    void dtor_0088b450();
};
struct TextRenderWare {
    char pad000[0xa384];
    void* ScalarDelete(unsigned char flags); // 007a88b0
};
struct GlyphVec {
    void* begin;    // +0
    void* end;      // +4
    void* cap;      // +8
    void* InsertAt(void* position, void* value);
};
// ---- items of slice s007a7d50 end

// @ 0x007a0460
void* Tc::m_007a0460(void* other_)
{
  VecBase* self = (VecBase*)this;
  VecBase* other = (VecBase*)other_;
  if (other == self) return self;
  char* oBegin = (char*)other->mpBegin;
  char* oEnd   = (char*)other->mpEnd;
  uint uVar2 = (uint)count14(oBegin, oEnd);
  if ((uint)count14(self->mpBegin, self->mpCapacity) < uVar2) {
    char* nb = (char*)((Tc*)self)->m_0079ae00((int)uVar2, (int)oBegin, (int)oEnd);
    ((Tc*)self)->m_0079b0d0((int)self->mpBegin, (int)self->mpEnd);
    if (spNeedsDelete(self->mpBegin)) operator_delete(self->mpBegin);
    self->mpCapacity = nb + uVar2 * 0x14;
    self->mpBegin = nb;
    self->mpEnd = nb + uVar2 * 0x14;
    return self;
  }
  uint uVar3 = (uint)count14(self->mpBegin, self->mpEnd);
  if (uVar3 < uVar2) {
    FUN_0079f730((int)oBegin, (int)(oBegin + uVar3 * 0x14), (int)self->mpBegin);
    char* p = (char*)other->mpEnd;
    FUN_0079a710((int)&p,
                         (int)(oBegin + count14(self->mpBegin, self->mpEnd) * 0x14),
                         (int)p, (int)self->mpEnd, (int)p);
    self->mpEnd = (char*)self->mpBegin + uVar2 * 0x14;
    return self;
  }
  char* dst = (char*)FUN_0079f730((int)oBegin, (int)oEnd, (int)self->mpBegin);
  ((Tc*)self)->m_0079b0d0((int)dst, (int)self->mpEnd);
  self->mpEnd = (char*)self->mpBegin + uVar2 * 0x14;
  return self;
}

// @ 0x007a09f0
SplitDrawBase::~SplitDrawBase()
{
    ClearVecVec((IntVecVec*)&mVec);
}

// @ 0x007a0ae0
void VecPod20::Resize(unsigned n)
{
    if (n > (unsigned)(mpEnd - mpBegin))
        UninitInsertN(mpEnd, n - (unsigned)(mpEnd - mpBegin), V20Pod());
    else
        DestroyRangeP(mpBegin + n, mpEnd);
}

// @ 0x007a0b90
void V12::Swap(V12& other)
{
    V20* x = b;
    if ((x == 0 || ((int*)x)[-1] != 0)) {
        V20* y = other.b;
        if (y == 0 || ((int*)y)[-1] != 0) {
            b = y; other.b = x;
            SwapPtr(e, other.e);
            SwapPtr(c, other.c);
            return;
        }
    }
    V12 tmp(*this);
    Assign(other);
    other.Assign(tmp);
}

// @ 0x007a0cd0
void SplitState::Reset(int a, int b)
{
    mMgr = new ("Graphics", 0, 0, 0, 0) SplitMgr();
    ((SplitMgr*)mMgr.mp)->t30.Reset(a);
    V16* first = mpBegin;
    V16* last = mpEnd;
    CopyV16(last, last, first);
    mpEnd += -(last - first);
    mLists.Resize(b);
    U16Vec* it = (U16Vec*)mLists.mpBegin;
    if (it != (U16Vec*)mLists.mpEnd) {
        do {
            unsigned short* eb = it->b;
            unsigned short* ee = it->e;
            MOVE(eb, ee, ByteDiff(it->e, ee));
            it->e += -(ee - eb);
            it = (U16Vec*)((char*)it + 0x14);
        } while (it != (U16Vec*)mLists.mpEnd);
    }
}

// @ 0x007a0de0
void SplitState2::Reset(int a, int b)
{
    mMgr = new ("Graphics", 0, 0, 0, 0) SplitMgr();
    mSub.Reset(a, b);
    mLists48.Resize(b);
    U16Vec* it = (U16Vec*)mLists48.mpBegin;
    if (it != (U16Vec*)mLists48.mpEnd) {
        do {
            unsigned short* eb = it->b;
            unsigned short* ee = it->e;
            MOVE(eb, ee, ByteDiff(it->e, ee));
            it->e += -(ee - eb);
            it = (U16Vec*)((char*)it + 0x14);
        } while (it != (U16Vec*)mLists48.mpEnd);
    }
    ((SplitMgr*)mMgr.mp)->t30.Reset(a);
}

// @ 0x007a0f90
void IModelSplitter::Split(int meshes, V12* out)
{
    V12 tmp;
    Process(meshes, &tmp);
    CompileSplitModels(&tmp, out);
}

// @ 0x007a1000
void ApplyHost::Apply(V12* target)
{
    V12Src tmp(mArg);
    tmp.Swap(*target);
    unsigned count = (unsigned)(tmp.e - tmp.b);
    V20* p = tmp.b;
    MapNode* head = (MapNode*)((char*)this + 0x10);
    for (unsigned i = 0; i < count; ++i, ++p) {
        MapNode* r = head;
        MapNode* n = mRoot;
        while (n) {
            if (n->key < (int)i) n = n->a;
            else { r = n; n = n->b; }
        }
        if (r != head && (int)i < r->key) r = head;
        if (r != head)
            target->Add(*(const V20Tmp*)p);
    }
}

// @ 0x007a1100
void VecV20::Resize(unsigned n)
{
    if (n > (unsigned)(mpEnd - mpBegin))
        InsertC(mpEnd, n - (unsigned)(mpEnd - mpBegin), V20());
    else
        EraseTail(mpBegin + n, mpEnd);
}

// @ 0x007a11c0
void SplitDrawImpl::Dispatch(ModelInstance* model, int a, int b)
{
    ElemList** pVec = &mpBegin;
    if (pVec[0] == pVec[1]) {
        MeshList meshes;
        model->GetMeshes(&meshes);
        mSplitter->Split((int)&meshes, (V12*)pVec);
    }
    g_renderStateDirty |= 0x8000;
    g_drawFlag = 1;
    if (mMgr == 0) {
        int n = (int)(pVec[1] - pVec[0]);
        if (n != 0) {
            int off = 0;
            do {
                ElemList* el = (ElemList*)((char*)*pVec + off);
                unsigned cnt = (unsigned)(el->e - el->b);
                for (unsigned j = 0; j < cnt; ++j)
                    model->DrawMesh(el->b[j].mesh, el->b[j].material, b, a);
                off += 0x14;
                --n;
            } while (n != 0);
        }
    } else {
        int n = (int)(mMgr->me - mMgr->mb);
        if (n != 0) {
            int off1 = 0;
            int off2 = 0;
            do {
                SplitInstList* inst = (SplitInstList*)((char*)mMgr->mb + off1);
                ElemList* el = (ElemList*)((char*)*pVec + off2);
                SplitInstEntry* last = inst->e;
                SplitInstEntry* it = inst->b;
                for (; it != last && it->key != -2; ++it) {}
                if (it != last) {
                    do {
                        model->SetTransform(it->xform, a);
                        unsigned cnt = (unsigned)(el->e - el->b);
                        for (unsigned j = 0; j < cnt; ++j)
                            model->DrawMesh(el->b[j].mesh, el->b[j].material, b, a);
                        do {
                            ++it;
                        } while (it != last && it->key != -2);
                    } while (it != last);
                }
                off2 += 0x14;
                off1 += 0x1c;
                --n;
            } while (n != 0);
        }
    }
}

// @ 0x007a1740
void B::CopyFrom(A* src)
{
  A* pp = p;
  if (pp->pe - pp->pb > 0) {
    p->inl.Assign(src->inl);
    p->ResizeVerts(src->ve - src->vb);
    int n = src->ve - src->vb;
    for (int i = 0; i < n; ++i) {
      Vert* d = &p->vb[i];
      Vert* s = &src->vb[i];
      Vec16* iv = &idx[i];
      d->f10 = s->f10;
      d->f14 = s->f14;
      EntVec3* sp = &s->f44;
      EntVec3* dp = &d->f44;
      if (dp != sp) {
        dp->Erase(dp->b, dp->e);
        dp->DoAssign(sp->b, sp->e, src);
      }
      int cnt = iv->e - iv->b;
      if (cnt != 0) {
        Range r(cnt, iv->b);
        extern void Obj15(Range*, Vert*);  // 0x007201d0
        Obj15(&r, d);
      }
    }
  } else {
    if (pp) {
      p = 0;
      pp->Release();
    }
  }
  RcBase* np = c.Build(src);
  RcBase* old = q;
  if (np != old) {
    if (np) np->AddRef();
    q = np;
    if (old) old->Release();
  }
}

// @ 0x007a3de0
void cStaticBufferDraw::sInstanceReset()
{ gStaticBufferDraw = 0; }

// @ 0x007a3df0
cStaticBufferDraw::cStaticBufferDraw()
: SingletonBaseStub(this) {
    mStaticBuffer = 0;
    mField04 = 0;
    mField08 = 0;
    mField0c = 0;
    mField10 = 0;
    mField14 = 0;
    mField18 = 0;
    mField1c = 0;
    mField20 = 0;
    mField24 = 0;
    mField28 = 0;
    mField2c = 0;
    mField30 = 0;
    mField40 = 0;
    FUN_006de2a0(this);
}

// @ 0x007a3e60
void cStaticBuffer::Dispatch(DrawStats* stats, ShaderData* sd)
{
    if (sd) {
        pushShaderDataNull();
        SetShaderData(sd);
        ((CompiledState*)sd)->Dispatch();
        D3D9Sync();
    }
    int desc = *(int*)((char*)this + 0x44);
    if (!gCurVertexDesc || !VertexDescriptorAreEqual(gCurVertexDesc, desc))
        gDirtyFlags |= 0x100000;
    gCurVertexDesc = desc;
    FUN_011f2bc0(desc);
    int (__cdecl* isReady)(int) = gRendererFns->IsReady;
    if (!isReady(gRendererArg))
        return;

    D3DDevice* dev = gDevice;
    gDirtyFlags = 0;
    for (int stream = 1; stream < 4; ++stream) {
        Stream* s = &gStreams[stream - 1];
        if (s->vb) {
            ((SetStreamFn)dev->vt[0x190 / 4])(dev, stream, 0, 0, 0);
            s->vb = 0;
            s->offset = 0;
            s->stride = 0;
        }
    }

    if ((int)(mpBatchEnd - mpBatchBegin) > 0) {
        int count = (int)(mpBatchEnd - mpBatchBegin);
        int off = 0;
        for (; count; --count, off += sizeof(StaticBatch)) {
            StaticBatch* b = (StaticBatch*)((char*)mpBatchBegin + off);
            BufferInfo* buf = mpBuffers[b->mBuffer];
            int baseVertex = buf->mOffset;
            IndexInfo* idx = 0;
            if (b->mIndexSet >= 0)
                idx = mpIndexSets[b->mIndexSet];
            int vb = buf->mVB;
            int stride = (unsigned char)buf->mpDesc[0xf];
            if (gStream0.vb != vb || gStream0.offset != 0 || gStream0.stride != stride) {
                ((SetStreamFn)dev->vt[0x190 / 4])(dev, 0, vb, 0, stride);
                gStream0.vb = vb;
                gStream0.offset = 0;
                gStream0.stride = stride;
            }
            int ib = 0;
            int startIndex = 0;
            if (mPrimType == 3) {
                IndexInfo* d = gDefaultIndexSet;
                ib = d->mIB;
                startIndex = d->mBase;
            } else if (idx) {
                ib = idx->mIB;
                startIndex = idx->mBase + b->mIndexOffset;
            }
            if (gCurIndexBuffer != ib) {
                ((SetIndicesFn)dev->vt[0x1a0 / 4])(dev, ib);
                gCurIndexBuffer = ib;
            }
            int start = b->mStart + baseVertex;
            switch (mPrimType) {
            case 0:
                ((DrawPrimFn)dev->vt[0x144 / 4])(dev, 1, start, b->mCount);
                break;
            case 1:
                ((DrawPrimFn)dev->vt[0x144 / 4])(dev, 2, start, b->mCount / 2);
                break;
            case 2:
                if (ib)
                    ((DrawIdxFn)dev->vt[0x148 / 4])(dev, 4, start, 0, b->mCount, startIndex, b->mIndexCount / 3);
                else
                    ((DrawPrimFn)dev->vt[0x144 / 4])(dev, 4, start, b->mCount / 3);
                break;
            case 3:
                ((DrawIdxFn)dev->vt[0x148 / 4])(dev, 4, start, 0, b->mCount, startIndex, b->mCount / 2);
                stats->mTris += (b->mCount * 3) / 2;
                break;
            case 4:
                if (ib)
                    ((DrawIdxFn)dev->vt[0x148 / 4])(dev, 5, start, 0, b->mCount, startIndex, b->mIndexCount - 2);
                else
                    ((DrawPrimFn)dev->vt[0x144 / 4])(dev, 5, start, b->mCount - 2);
                break;
            }
            stats->mVerts += b->mCount;
            stats->mTris += b->mIndexCount;
            stats->mBatches += 1;
        }
    }
    if (sd)
        pushShaderDataPop();
}

// @ 0x007a41a0
void __fastcall FreeArrayBlock(void** pp)
{
    void* p = *pp;
    if (p && ((int*)p)[-1] != 0)
        operator_delete__(p);
}

// @ 0x007a41c0
void* __cdecl FUN_007a41c0(void* param_1)
{
  cStaticBufferDraw_s007a_41c0* p =
      (cStaticBufferDraw_s007a_41c0*)EXT_f473a0(0x44, "Graphics/StaticBufferDraw",
                                     0, 0, 0, 0, (const char*)param_1);
  if (p != 0) {
    EXT_7a3df0(p);
  }
  return p;
}

// @ 0x007a88b0
void* TextRenderWare::ScalarDelete(unsigned char flags)
{
    TextRenderWare* self = this;
    PtrPair* pair = (PtrPair*)((char*)self + 0x190);
    pair->free_0070f520(*(void**)((char*)self + 0x190), *(void**)((char*)self + 0x194));
    void* p = *(void**)((char*)self + 0x190);
    if (p && *(int*)((char*)p - 4) != 0)
        EASTL_allocator_deallocate(p);
    ((GlyphCacheObj*)self)->dtor_0088b450();
    if (flags & 1)
        EASTL_allocator_deallocate(self);
    return self;
}

// @ 0x007a8910
extern "C" void* FUN_007a8910(GlyphVec* self, void* position, void* value)
{
    if (self->end != self->cap) {
        if (position <= value && value < self->end)
            value = (char*)value + 0x14;
        void* end = self->end;
        if (end) {
            *(uint32_t*)((char*)end + 0x00) = *(uint32_t*)((char*)end - 0x14);
            *(uint32_t*)((char*)end + 0x04) = *(uint32_t*)((char*)end - 0x10);
            *(uint32_t*)((char*)end + 0x08) = *(uint32_t*)((char*)end - 0x0c);
            *(uint32_t*)((char*)end + 0x0c) = *(uint32_t*)((char*)end - 0x08);
            *(uint32_t*)((char*)end + 0x10) = *(uint32_t*)((char*)end - 0x04);
        }
        FUN_00c50ad0((char*)self->end - 0x14, position, self->end);
        *(uint32_t*)((char*)position + 0x00) = *(uint32_t*)((char*)value + 0x00);
        *(uint32_t*)((char*)position + 0x04) = *(uint32_t*)((char*)value + 0x04);
        *(uint32_t*)((char*)position + 0x08) = *(uint32_t*)((char*)value + 0x08);
        *(uint32_t*)((char*)position + 0x0c) = *(uint32_t*)((char*)value + 0x0c);
        *(uint32_t*)((char*)position + 0x10) = *(uint32_t*)((char*)value + 0x10);
        self->end = (char*)self->end + 0x14;
        return 0;
    }

    int count = (int)((char*)self->end - (char*)self->begin) / 0x14;
    int newCap;
    void* newBegin;
    if (count == 0) {
        newCap = 1;
        newBegin = EASTL_allocator_allocate((unsigned)(newCap * 0x14 * 4), "Graphics", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1);
    }
    else {
        newCap = count * 2;
        if (newCap != 0) {
            newBegin = EASTL_allocator_allocate((unsigned)(newCap * 0x14 * 4), "Graphics", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                0xd1);
        } else {
            newBegin = 0;
        }
    }
    void* newEnd = (void*)FUN_00951bb0((unsigned)newBegin, (unsigned)self->begin,
                                       (void*)((char*)position - (char*)self->begin));
    if (newEnd) {
        *(uint32_t*)((char*)newEnd + 0x00) = *(uint32_t*)((char*)value + 0x00);
        *(uint32_t*)((char*)newEnd + 0x04) = *(uint32_t*)((char*)value + 0x04);
        *(uint32_t*)((char*)newEnd + 0x08) = *(uint32_t*)((char*)value + 0x08);
        *(uint32_t*)((char*)newEnd + 0x0c) = *(uint32_t*)((char*)value + 0x0c);
        *(uint32_t*)((char*)newEnd + 0x10) = *(uint32_t*)((char*)value + 0x10);
    }
    void* r = FUN_00951bb0((unsigned)((char*)newEnd + 0x14), (unsigned)position,
                           (void*)((char*)self->end - (char*)position));
    if (self->begin && *(int*)((char*)self->begin - 4) != 0)
        EASTL_allocator_deallocate(self->begin);
    self->begin = newBegin;
    self->end = r;
    self->cap = (char*)newBegin + newCap * 0x14;
    return self->begin;
}
