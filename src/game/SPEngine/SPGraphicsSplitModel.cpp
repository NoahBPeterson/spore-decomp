// src/game/SPEngine/SPGraphicsSplitModel.cpp -- migrated from slice(s) s007a3260, s007a26e0, s007a1740, s007a07b0, s0079f8d0, s0079e950, s0079b020, s00798d30 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsSplitModel.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern void __cdecl FUN_00436ce0(...);
#include <intrin.h>
#include <math.h>
#include "SPGraphicsSplitModel/refvec_fwd.h"
#include "SP/cModelInstance.h"
#include <new>

// ---- items of slice s00798d30 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void __cdecl FUN_00436ce0(...);
struct Vec2 { float x, y; };
struct Vec4 { float x, y, z, w; };
struct Vec3 { float x, y, z; };
// ---- items of slice s00798d30 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void FUN_00799320(float *param_1, float *param_2);  // 0x00799320 (stays in the slice: not this object's)

// ---- items of slice s0079b020 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void  __cdecl EASTL_free(void* p);                                                                       // 0x00f47380
extern "C" void* __cdecl memcpy(void*, const void*, size_t);
static inline void DoFree(void* p)
{
    if (p && ((int*)p)[-1] != 0) EASTL_free(p);
}
struct UShortVecBase {
    uint16_t* mpBegin;
    uint16_t* mpEnd;
    uint16_t* mpCapacity;
    UShortVecBase() {}
    ~UShortVecBase() { DoFree(mpBegin); }
};
struct UShortVec : UShortVecBase {

    uint16_t* DoRealloc(int n, const uint16_t* first, const uint16_t* last);   // 0x0079ae60
    void DoInsertValue(uint16_t* pos, const uint16_t& v);                      // 0x006f5bc0
    UShortVec& CopyFrom(const UShortVec& x);   // 0x0079b360 operator= (named so the checker can find our symbol)
    void push_back(const uint16_t& v)
    {
        if (mpEnd < mpCapacity) {
            uint16_t* p = mpEnd;
            mpEnd = p + 1;
            if (p) *p = v;
        } else
            DoInsertValue(mpEnd, v);
    }
};
// ---- items of slice s0079b020 end

// ---- items of slice s0079e950 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void operator_delete__(void* p);
typedef unsigned int uint;
struct RefCounted { int vtbl; int refCount; };
struct RefElem {                                        // 8 bytes
    RefCounted* p;
    int x;
    void CopyFrom(const RefElem& o) {                   // copy-construct with addref
        p = o.p;
        if (p)
            _InterlockedExchangeAdd((long*)&p->refCount, 1);
        x = o.x;
    }
    RefElem& Assign(const RefElem& o);                  // 0x8dee30
};
void ReleaseAndClear(RefVec* v);  // 0x0079f7b0 (defined below; used by a stub's inline body)
struct RefVec {
    RefElem* mpBegin; RefElem* mpEnd; RefElem* mpCap;
    void DoInsertValue(RefElem* pos, const RefElem& val);   // 0x79f4e0
    RefVec& Assign(const RefVec& rhs);                      // 0x79f640
    void ReleaseAndClear();                                 // 0x79f7b0 (free function form below)
    RefElem* DoAllocateCopy(uint n, RefElem* first, RefElem* last);   // 0x799d60
    void DestroyRange(RefElem* first, RefElem* last);       // 0x8dede0
};
extern "C" RefElem* FUN_008defe0(RefElem* first, RefElem* last, RefElem* dst); // copy
extern "C" void FUN_00799290(RefElem** out, RefElem* a, RefElem* b, RefElem* c, const RefVec* hint);
// ---- items of slice s0079e950 end

// ---- items of slice s0079f8d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* operator_new(unsigned int size, const char* area, int a, int b,
                              const char* allocatorPath, int line);   // 0x00f473a0
extern "C" void  operator_delete(void* p);                            // 0x00f47380
extern "C" const char g_allocatorFile[];                              // 0x013ebb38
struct Elem20 {
  uint32_t m00, m04, m08, m0c, m10, m14;   // +0x00
  uint16_t m18, m1a;                        // +0x18
  void*    m1c;                             // +0x1c
  Elem20() {
    m00 = 0; m04 = 0; m08 = 0; m0c = 0xe; m10 = 0; m14 = 0; m18 = 0; m1a = 0; m1c = 0;
  }
  ~Elem20() {
    if (m1c != 0) (*(void(__thiscall*)(void*, int))*(void**)m1c)(m1c, 1);
  }
};
struct Elem78 {
  int      mKey;                      // +0x00
  uint32_t mBody[0x1d];               // +0x04 .. +0x77
};
struct Elem14 {
  uint32_t m00, m04, m08, m0c, m10;   // +0x00 .. +0x13
};
struct VecBase {
  void* mpBegin;                      // +0x00
  void* mpEnd;                        // +0x04
  void* mpCapacity;                   // +0x08
  void* mAllocator;                   // +0x0c
};
struct RefIndexPair {
  void* mPtr;                         // +0x00
  int   mIndex;                       // +0x04
};
struct cSplitInstanceList {
  int      mNextFree;                 // +0x00
  VecBase  mDataArray;                // +0x04 .. +0x13
  unsigned int mSize;                 // +0x14
  unsigned int mInsertCount;          // +0x18
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
void  FUN_0079a800(int a, int b, int c, int d, int e);
void  FUN_0079a8f0(int a, int b, int c);
void  FUN_0079aaa0(int a, int b, int c);
int   FUN_0079ab00(int a, int b, int c);
void  FUN_0079ab40(int a, int b, int c);
void  FUN_0079b190(int a, int b, int c);
void  FUN_0079b1c0(int a, int b, int c, int d, int e);
void  FUN_0079b2a0(int a, int b, int c, int d);
void  FUN_0079b470(int a, int b, int c);
void  FUN_0079f770(int a, int b, int c);
void  FUN_0079fcc0(int a, int b, int c);
void  FUN_0799dc0(int a, int b, int c);
void* FUN_011e0744(void* dst, const void* src, unsigned int n);       // 0x011e0744 byte-range copy
void __fastcall FUN_0079fef0(void* self);
void FUN_0079f7b0(void* elem);
void FUN_0079b6b0(int elem, int sub);
static inline int count14(void* beg, void* end) {
  return (int)((char*)end - (char*)beg) / 0x14;   // signed /20, matches 0x66666667 reciprocal
}
static inline int count8(void* beg, void* end) {
  return (int)((char*)end - (char*)beg) >> 3;
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
static __forceinline void PushBackSlowElem78(VecBase* v) {
  Elem78 tmp;
  tmp.mKey = -2;
  ((Tc*)(&tmp.mBody))->m_07993a0();
  ((Tc*)v)->m_0079f8d0((int)v->mpEnd, (int)&tmp);
}
// ---- items of slice s0079f8d0 end

// ---- items of slice s007a07b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* memmove_thunk_11e0744(void* dst, const void* src, unsigned n);  // memmove
extern unsigned g_sizeMask[];           // 0x140f544 (per-component masks)
extern int g_streamTable[];             // 0x153b208
#pragma intrinsic(_InterlockedExchange, _InterlockedIncrement, _InterlockedDecrement)
void* operator new(unsigned int, const char*, int, unsigned int, const char*, int);
void operator delete[](void*) throw();
#define MOVE(d, s, n) memmove_thunk_11e0744((d), (s), (n))
struct V20 {                       // value with copy-ctor 0x79a4a0, dtor 0x432e80
    int* b; int* e; int* c; int x; int y;
    V20() : b(0), e(0), c(0) {}
    V20(const V20&);               // 0x79a4a0
    ~V20();                        // 0x432e80
};
V20* UninitMove(V20** out, V20* first, V20* last, V20* dest, V20* pos);  // 0x79a710
V20* MoveBackward(V20* first, V20* last, V20* destEnd);                   // 0x79f770
V20* FillRange(V20* first, V20* last, const V20* val);                    // 0x79fcf0
V20* UninitFillN(V20* dest, unsigned n, const V20* val);       // 0x79a9d0
struct VecV20 {
    V20* mpBegin; V20* mpEnd; V20* mpCapacity;
    void Insert(V20* pos, unsigned n, const V20* val);
    void InsertC(V20* pos, unsigned n, const V20& val);   // same routine, by-reference spelling   // 0x7a07b0
    void Resize(unsigned n);                              // 0x7a1100
    V20* EraseTail(V20* first, V20* last);                // 0x7a05b0
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
struct IModelSplitter {
    virtual void v0();
    virtual void Notify(V12* out);          // vtbl+4
    void Process(int a, V12* vec);          // 0x7a0ee0
    void Split(int meshes, V12* out);       // 0x7a0f90
};
V20* FindErase(V20* a, V20* b, V20* c);     // 0x79f730 (cdecl, 3 args)
V20Tmp MakeTmp(int a);                      // 0x79fd20 (cdecl, hidden return slot)
struct CompiledElem { int mesh; int material; };
struct ElemList { CompiledElem* b; CompiledElem* e; CompiledElem* c; int p3, p4; };   // 20 bytes
struct StreamDesc {                     // 0x8c bytes
    int w0; char* data; unsigned short maskIdx; unsigned short stride; char pad[0x8c - 12];
};
struct FixedIdVec6 {
    void Assign(const void* src);   // 0x719170 FixedIdVector6::operator=
};
struct StreamIdVec {
    void Resize(int n);             // 0x71f7e0
};
struct ElemVec {
    void Resize(int n);             // 0x475320
    void Grow();                    // 0x79fe20
};
struct IObjRelease { virtual void v0(); virtual void Release(); };
struct RangeInfo {
    int count; unsigned short* ptr; unsigned short w1, w2; IObjRelease* r;
    RangeInfo(int c, unsigned short* p) : count(c), ptr(p), w1(2), w2(2), r(0) {}
    ~RangeInfo() { if (r) r->Release(); }
};
void BuildStream(RangeInfo* r, void* dst);              // 0x7201d0 (cdecl)
void BuildObj(int count, unsigned short w, void* dst);  // 0x720190 (cdecl)
void HandleAssign(void* dst, const void* src);          // 0x424f70 (thiscall Handle_Assign)
void BlendCopy(int a, int b, float f, int v1, int v2, void* out);  // 0x799e70 (cdecl)
struct PairElem { int a, b, c; float f; };              // 16 bytes
struct CompiledStreamElem {                             // 0x20 bytes
    int k0, k1, k2, k3;
    char* data; int base; unsigned short w; unsigned short stride; int pad;
};
struct ModelDst {                                       // the object pointed to by *this
    char pad[8]; char* elems;                           // +8 ElemVec begin..: used via methods
    int e0c;                                            // +0xc: end of ElemVec
    char pad2[0x1c - 0x10];
    char* streams;                                      // +0x1c: StreamIdVec begin
};
struct ModelSrc {
    char pad[8]; CompiledStreamElem* sb; CompiledStreamElem* se;   // +8/+0xc
    char pad2[0x1c - 0x10];
    StreamDesc* streamBegin; StreamDesc* streamEnd;                // +0x1c/+0x20
};
struct GeomBuilder {
    ModelDst* mDst;                  // +0
    PairElem* mpB; PairElem* mpE;    // +4/+8
    int pad[3];
    ElemList* mListsB; ElemList* mListsE;  // +0x18/+0x1c (20-byte lists)
    ModelDst* Build(ModelSrc* src);  // 0x7a1400
};
// ---- items of slice s007a07b0 end

// ---- items of slice s007a1740 begin (TODO(rewrite): local stubs, replace by canonical classes)
void operator delete(void* p);  // 0x00f47380 (EASTL_allocator_deallocate)
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
struct Arg23c0;
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
struct Builder {
  void Cb1(A* src, Prim* pr, Vec16* iv, C* ctx);   // 0x0079b7b0
  void Cb2(A* src, Prim* pr, Vec16* iv, C* ctx);   // 0x0079bfa0
  void Cb3(A* src, Prim* pr, Vec16* iv, C* ctx);   // 0x0079c960
  void Cb4(A* src, Prim* pr, Vec16* ivA, Vec16* ivB, C* ctxA, C* ctxB);  // 0x0079d190
  void Cb5(A* src, Prim* pr, Vec16* ivA, Vec16* ivB, C* ctxA, C* ctxB);  // 0x0079dce0
  void Cb6(A* src, Prim* pr, Vec16* ivA, Vec16* ivB, C* ctxA, C* ctxB);  // 0x0079e950
  __declspec(noinline) void F1940(A* src, B* dst);
  __declspec(noinline) void F1a80(A* src, B* dst);
  __declspec(noinline) void F1bc0(A* src, B* dst);
  __declspec(noinline) void F1d00(A* src, B* d1, B* d2);
  __declspec(noinline) void F1f40(A* src, B* d1, B* d2);
  __declspec(noinline) void F2180(A* src, B* d1, B* d2);
  void F23c0(Arg23c0* arg);
};
struct PairRc {
  A* a;
  int v;
};
struct SrcRange {  // 0x14 bytes; list of (A*, int)
  PairRc* b;
  PairRc* e;
  uint32_t pad[3];
};
struct OutPair {
  RcBase* p;
  int v;
  OutPair(RcBase* x, int n) : p(x), v(n) { if (p) p->AddRef(); }
  OutPair(const OutPair& o) : p(o.p), v(o.v) { if (p) p->AddRef(); }
  ~OutPair() { if (p) p->Release(); }
};
struct OutVec {  // vector of OutPair
  OutPair* b;
  OutPair* e;
  OutPair* cap;
  uint32_t pad[2];
  void Resize(uint32_t n);                          // 0x0079af80
  void Grow(OutPair* at, const OutPair& v);         // 0x0079f4e0
  void push_back(const OutPair& v) {
    if (e < cap) {
      OutPair* at = e++;
      if (at) new (at) OutPair(v);
    } else {
      Grow(e, v);
    }
  }
};
struct Arg23c0 {  // object whose [0] is an array of OutVec
  OutVec* vecs;
  void Resize(uint32_t n);                          // 0x007a1100
};
struct SrcVec {  // local vector of SrcRange
  SrcRange* b;
  SrcRange* e;
  SrcRange* cap;
  void Fill(Arg23c0* a);                            // 0x007a0b90
  void Destroy(SrcRange* f, SrcRange* l);           // 0x0079b0d0
  ~SrcVec() {
    Destroy(b, e);
    if (b && ((int*)b)[-1]) operator delete(b);
  }
};
// ---- items of slice s007a1740 end

// ---- items of slice s007a26e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void __fastcall FUN_007a0b90(void* self, int, void* other);
extern "C" void __fastcall FUN_007a1100(void* self, int, int count);
extern "C" void __fastcall FUN_0079af80(void* self, int, int count);
extern "C" void __fastcall FUN_0079f4e0(void* self, int, void* pos, void* value);
extern "C" void __fastcall FUN_0079aeb0(void* self);
extern "C" void __fastcall FUN_0060d210(void** slot);
extern "C" void __fastcall FUN_007a1a80(void* self, int, void* source, void* out);
extern "C" void __fastcall FUN_007a1bc0(void* self, int, void* source, void* out);
extern "C" void __fastcall FUN_007a1d00(void* self, int, void* source, void* outA, void* outB);
extern "C" void __fastcall FUN_0079b0d0(void* self, int, void* begin, void* end);  // destroy range of Group
extern "C" void __cdecl FUN_f47380(void* block);                   // operator delete
struct Pair {
    void* object;   // +0x00  refcounted pointer (refcount at object + 4)
    int   tag;      // +0x04
};
struct Group {                 // eastl::vector<Pair, sp_vector_allocator>
    Pair* begin;               // +0x00
    Pair* end;                 // +0x04
    Pair* cap;                 // +0x08
    int   alloc0;              // +0x0c
    int   alloc1;              // +0x10
};
struct Group2 {
    Group a;                   // +0x00
    Group b;                   // +0x14
};
struct GroupVec {              // vector of 20-byte groups
    Group* begin;
    Group* end;
    Group* cap;
};
struct Group2Vec {             // vector of 40-byte group pairs
    Group2* begin;
    Group2* end;
    Group2* cap;
};
struct OutRecord {             // 0x70-byte per-object conversion result
    void* sp0;                 // +0x00  shared pointer
    void* sp1;                 // +0x04  shared pointer
    void* u08;                 // +0x08
    void* u0c;                 // +0x0c
    void* u10;                 // +0x10
    void* u14;                 // +0x14
    int   u18;                 // +0x18
    int   u1c;                 // +0x1c
    void* arr20;               // +0x20  array begin
    void* u24;                 // +0x24
    void* u28;                 // +0x28
    int   u2c;                 // +0x2c
    int   u30;                 // +0x30
    int   v34;                 // +0x34  initialised to 4 by the type
    int   v38;                 // +0x38
    int   v3c;                 // +0x3c
    int   v40;                 // +0x40
    int   v44;                 // +0x44
    void* arr48;               // +0x48  array begin
    void* arr4c;               // +0x4c
    void* arr50;               // +0x50
    int   u54;                 // +0x54
    int   u58;                 // +0x58
    int   v5c;                 // +0x5c  initialised to 4 by the type
    int   v60;                 // +0x60
    int   v64;                 // +0x64
    int   v68;                 // +0x68
    int   v6c;                 // +0x6c
};
struct Converter {
    void ConvertPairs1(GroupVec* dest);
    void ConvertPairs2(GroupVec* dest);
    void ConvertPairPairs(Group2Vec* dest);
};
static void InitOut(OutRecord& o)
{
    o.sp0 = 0;
    o.sp1 = 0;
    o.u08 = 0;
    o.u0c = 0;
    o.u10 = 0;
    o.u14 = 0;
    o.u18 = 0;
    o.u1c = 0;
    o.arr20 = 0;
    o.u24 = 0;
    o.u28 = 0;
    o.u2c = 0;
    o.u30 = 0;
    o.v34 = 4;
    o.v38 = 0;
    o.v3c = 0;
    o.v40 = 0;
    o.v44 = 0;
    o.arr48 = 0;
    o.arr4c = 0;
    o.arr50 = 0;
    o.u54 = 0;
    o.u58 = 0;
    o.v5c = 4;
    o.v60 = 0;
    o.v64 = 0;
    o.v68 = 0;
    o.v6c = 0;
}
static inline void RetainObject(void* object)
{
    _InterlockedIncrement((volatile long*)object + 1);
}
static void PushPair(Group* group, void* object, int tag)
{
    Pair temp;
    temp.object = object;
    temp.tag = tag;
    RetainObject(object);
    if (group->end < group->cap) {
        Pair* slot = group->end;
        group->end = slot + 1;
        if (slot != 0) {
            slot->object = object;
            RetainObject(object);
            slot->tag = tag;
        }
    } else {
        FUN_0079f4e0(group, 0, group->end, &temp);
    }
    FUN_0060d210(&temp.object);
}
static void DestroyGroupVector(GroupVec* v)
{
    FUN_0079b0d0(v, 0, v->begin, v->end);
    if (v->begin != 0 && ((int*)v->begin)[-1] != 0)
        FUN_f47380(v->begin);
}
// ---- items of slice s007a26e0 end

// ---- items of slice s007a3260 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedExchange)
struct RefObj {
    virtual void Destroy(int flags);
    int mnRefCount;
};
static inline void AddRef(RefObj* p) { _InterlockedExchangeAdd((volatile long*)&p->mnRefCount, 1); }
static inline void ReleaseRefObj(RefObj* p) {
    if (p) {
        int n = _InterlockedExchangeAdd((volatile long*)&p->mnRefCount, -1);
        if (n - 1 == 0) {
            _InterlockedExchange((volatile long*)&p->mnRefCount, 1);
            if (p)
                p->Destroy(1);
        }
    }
}
struct RefPtr {
    RefObj* mp;
    RefPtr() : mp(0) {}
    RefPtr(RefObj* p) : mp(p) { if (mp) AddRef(mp); }
    RefPtr(const RefPtr& o) : mp(o.mp) { if (mp) AddRef(mp); }
    ~RefPtr() { ReleaseRefObj(mp); }
};
struct Entry {
    RefPtr ref;
    int mTag;
    Entry(const RefPtr& r, int t) : ref(r), mTag(t) {}
};
struct KeyTag {
    int mKey;
    int mTag;
};
struct EntryVec;
struct EntryVec {
    Entry* mpBegin;
    Entry* mpEnd;
    Entry* mpCapacity;
    int mAllocator[2];
    void reserve(int n);                                 // 0x0079af80
    void DoInsertValue(Entry* pos, const Entry& v);      // 0x0079f4e0
    void push_back(const Entry& v) {
        if (mpEnd < mpCapacity) {
            Entry* p = mpEnd++;
            if (p)
                new (p) Entry(v);
        } else {
            DoInsertValue(mpEnd, v);
        }
    }
};
struct KeyTagVec {
    KeyTag* mpBegin;
    KeyTag* mpEnd;
    KeyTag* mpCapacity;
    int mAllocator[2];
};
struct KeyTagVecVec {
    KeyTagVec* mpBegin;
    KeyTagVec* mpEnd;
    KeyTagVec* mpCapacity;
    void Fill(void* src);                                // 0x007a0b90
    void DestroyRange(KeyTagVec* b, KeyTagVec* e);       // 0x0079b0d0
    ~KeyTagVecVec() {
        DestroyRange(mpBegin, mpEnd);
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            operator_delete__(mpBegin);
    }
};
struct EntryVecVec {
    EntryVec* mpBegin;
    void resize(int n);                                  // 0x007a1100
};
struct GatherResult {
    RefPtr a;            // +0
    RefPtr b;            // +4
    int w[4];            // +8
    int _pad18[2];
    int x[3];            // +0x20
    int _pad2c[2];
    int c34;             // +0x34
    int y[4];            // +0x38
    int z[3];            // +0x48
    int _pad54[2];
    int c5c;             // +0x5c
    int t[4];            // +0x60
    __forceinline GatherResult() {
        a.mp = 0; b.mp = 0;
        w[0] = w[1] = w[2] = w[3] = 0;
        x[0] = x[1] = x[2] = 0;
        c34 = 4;
        y[0] = y[1] = y[2] = y[3] = 0;
        z[0] = z[1] = z[2] = 0;
        c5c = 4;
        t[0] = t[1] = t[2] = t[3] = 0;
    }
    ~GatherResult();                                     // 0x0079aeb0
};
struct MeshBuilder {
    void GatherA(int key, GatherResult* r1, GatherResult* r2);   // 0x007a1f40
    void GatherB(int key, GatherResult* r1, GatherResult* r2);   // 0x007a2180

    template <void (MeshBuilder::*Gather)(int, GatherResult*, GatherResult*)>
    __forceinline void Build(EntryVecVec* out) {
        KeyTagVecVec src;
        src.mpBegin = src.mpEnd = src.mpCapacity = 0;
        src.Fill(out);
        GatherResult r1;
        GatherResult r2;
        int n = (int)(src.mpEnd - src.mpBegin);
        out->resize(n * 2);
        KeyTagVec* sv = src.mpBegin;
        int off = 0;
        for (int i = 0; i < n; ++i, ++sv, off += 2) {
            EntryVec* v0 = out->mpBegin + off;
            EntryVec* v1 = v0 + 1;
            int count = (int)(sv->mpEnd - sv->mpBegin);
            v0->reserve(count);
            v1->reserve(count);
            for (int j = 0; j < (int)(sv->mpEnd - sv->mpBegin); ++j) {
                KeyTag* e = &sv->mpBegin[j];
                (this->*Gather)(e->mKey, &r1, &r2);
                if (r1.a.mp) { Entry t(r1.a, e->mTag); v0->push_back(t); }
                if (r1.b.mp) { Entry t(r1.b, e->mTag); v0->push_back(t); }
                if (r2.a.mp) { Entry t(r2.a, e->mTag); v1->push_back(t); }
                if (r2.b.mp) { Entry t(r2.b, e->mTag); v1->push_back(t); }
            }
        }
    }

    void BuildPairListsA(EntryVecVec* out);
    void BuildPairListsB(EntryVecVec* out);
};
// ---- items of slice s007a3260 end

// @ 0x00798e40
void FUN_00798e40(int param_1, float param_2, float *param_3, float *param_4, float *param_5)
{
    switch (param_1) {
    case 1:
        *param_5 = (1.0f - param_2) * *param_3 + *param_4 * param_2;
        return;
    case 3:
        if (param_2 > 0.5f) { *param_5 = *param_4; return; }
        *param_5 = *param_3;
        return;
    case 4:
        *param_5 = *param_3;
        return;
    case 5:
        *param_5 = *param_4;
        return;
    }
}

// @ 0x00798ed0
void FUN_00798ed0(int param_1, float param_2, unsigned int *param_3, unsigned int *param_4, unsigned int *param_5)
{
    float fVar1;
    float fVar2;
    unsigned int local_8;

    switch (param_1) {
    case 1:
        fVar1 = (float)*param_3;
        if (*param_3 < 0) {
            fVar1 = fVar1 + 4.2949673e+09f;
        }
        fVar2 = (float)*param_4;
        if (*param_4 < 0) {
            fVar2 = fVar2 + 4.2949673e+09f;
        }
        local_8 = (unsigned int)(fVar2 * param_2 + fVar1 * (1.0f - param_2));
        *param_5 = local_8;
        return;
    case 3:
        if (param_2 > 0.5f) { *param_5 = *param_4; return; }
        *param_5 = *param_3;
        return;
    case 4:
        *param_5 = *param_3;
        return;
    case 5:
        *param_5 = *param_4;
        return;
    }}

// @ 0x00798fb0
void FUN_00798fb0(int param_1, float param_2, int *param_3, int *param_4, int *param_5)
{
    switch (param_1) {
    case 1:
        *param_5 = (int)((1.0f - param_2) * (float)*param_3 + (float)*param_4 * param_2);
        return;
    case 3:
        if (param_2 > 0.5f) { *param_5 = *param_4; return; }
        *param_5 = *param_3;
        return;
    case 4:
        *param_5 = *param_3;
        return;
    case 5:
        *param_5 = *param_4;
        return;
    }
}

// @ 0x00799050
void FUN_00799050(int param_1, float param_2, int *param_3, int *param_4, int *param_5)
{
    switch (param_1) {
    case 3:
        if (param_2 > 0.5f) { *param_5 = *param_4; return; }
        *param_5 = *param_3;
        return;
    case 4:
        *param_5 = *param_3;
        return;
    case 5:
        *param_5 = *param_4;
        return;
    }
}

// @ 0x00799090
void FUN_00799090(int param_1, float param_2, int *param_3, int *param_4, int *param_5)
{
    switch (param_1) {
    case 3:
        if (param_2 > 0.5f) { *param_5 = *param_4; param_5[1] = param_4[1]; return; }
        *param_5 = *param_3;
        param_5[1] = param_3[1];
        return;
    case 4:
        *param_5 = *param_3;
        param_5[1] = param_3[1];
        return;
    case 5:
        *param_5 = *param_4;
        param_5[1] = param_4[1];
        return;
    }
}

// @ 0x00799110
void FUN_00799110(int param_1, float param_2, float *param_3, float *param_4, float *param_5)
{
    switch (param_1) {
    case 1: {
        float fVar4 = 1.0f - param_2;
        float fVar0 = *param_3 * fVar4;
        float fVar5 = param_3[1] * fVar4;
        float fVar1 = param_3[2] * fVar4;
        *param_5 = *param_4 * param_2 + fVar0;
        param_5[1] = param_4[1] * param_2 + fVar5;
        param_5[2] = param_4[2] * param_2 + fVar1;
        return;
    }
    case 2: {
        float fVar5 = 1.0f - param_2;
        float blended[3];
        blended[0] = *param_4 * param_2 + *param_3 * fVar5;
        blended[1] = param_4[1] * param_2 + param_3[1] * fVar5;
        blended[2] = param_4[2] * param_2 + param_3[2] * fVar5;
        float normalized[3];
        FUN_00436ce0(normalized, blended);
        param_4 = normalized;
        break;
    }
    case 3:
        if (param_2 <= 0.5f) { *(Vec3 *)param_5 = *(Vec3 *)param_3; return; }
        *(Vec3 *)param_5 = *(Vec3 *)param_4;
        return;
    case 4:
        param_4 = param_3;
        break;
    case 5:
        break;
    default:
        return;
    }
    *(Vec3 *)param_5 = *(Vec3 *)param_4;
    return;
}

// @ 0x00799290
int **FUN_00799290(int **param_1, int *param_2, int *param_3, int *param_4)
{
    int *piVar1;
    int iVar2;

    *param_1 = param_4;
    for (; param_2 != param_3; param_2 = param_2 + 2) {
        piVar1 = *param_1;
        if (piVar1 != (int *)0x0) {
            iVar2 = *param_2;
            *piVar1 = iVar2;
            if (iVar2 != 0) {
                _InterlockedIncrement((volatile long *)(iVar2 + 4));
            }
            piVar1[1] = param_2[1];
        }
        *param_1 = (int *)((char *)*param_1 + 8);
    }
    return param_1;
}

// @ 0x007992e0
int* FUN_007992e0(int *param_1, int *param_2, int *param_3)
{
    int iVar1;

    for (; param_1 != param_2; param_1 = param_1 + 2) {
        if (param_3 != (int *)0x0) {
            iVar1 = *param_1;
            *param_3 = iVar1;
            if (iVar1 != 0) {
                _InterlockedIncrement((volatile long *)(iVar1 + 4));
            }
            param_3[1] = param_1[1];
        }
        param_3 = param_3 + 2;
    }
    return param_3;
}

// @ 0x007994d0
void FUN_007994d0(int param_1, float param_2, float *param_3, float *param_4, float *param_5)
{
    switch (param_1) {
    case 1: {
        float fVar4 = 1.0f - param_2;
        float fVar0 = *param_3 * fVar4;
        float fVar1 = param_3[1] * fVar4;
        *param_5 = *param_4 * param_2 + fVar0;
        param_5[1] = param_4[1] * param_2 + fVar1;
        return;
    }
    case 2: {
        float fVar4 = 1.0f - param_2;
        float fVar2 = param_4[1] * param_2 + param_3[1] * fVar4;
        float fVar1 = *param_4 * param_2 + *param_3 * fVar4;
        float fVar3 = 1.0f / (float)sqrt((double)fVar1 * fVar1 + (double)fVar2 * fVar2);
        *param_5 = fVar3 * fVar1;
        param_5[1] = fVar3 * fVar2;
        return;
    }
    case 3:
        if (param_2 <= 0.5f) { *(Vec2 *)param_5 = *(Vec2 *)param_3; return; }
        *(Vec2 *)param_5 = *(Vec2 *)param_4;
        return;
    case 4:
        *(Vec2 *)param_5 = *(Vec2 *)param_3;
        return;
    case 5:
        *(Vec2 *)param_5 = *(Vec2 *)param_4;
        return;
    default:
        return;
    }
}

// @ 0x00799640
void FUN_00799640(int param_1, float param_2, float *param_3, float *param_4, float *param_5)
{
    switch (param_1) {
    case 1: {
        float fVar7 = param_3[1];
        float fVar1 = param_3[2];
        float fVar2 = param_3[3];
        float fVar3 = param_4[2];
        float fVar4 = param_4[3];
        float fVar6 = 1.0f - param_2;
        float fVar5 = param_4[1];
        *param_5 = *param_4 * param_2 + *param_3 * fVar6;
        param_5[1] = fVar5 * param_2 + fVar7 * fVar6;
        param_5[2] = fVar3 * param_2 + fVar1 * fVar6;
        param_5[3] = fVar4 * param_2 + fVar2 * fVar6;
        return;
    }
    case 2: {
        float fVar7 = 1.0f - param_2;
        float blended[4];
        blended[0] = *param_4 * param_2 + *param_3 * fVar7;
        blended[1] = param_4[1] * param_2 + param_3[1] * fVar7;
        blended[2] = param_4[2] * param_2 + param_3[2] * fVar7;
        blended[3] = param_4[3] * param_2 + param_3[3] * fVar7;
        float normalized[4];
        FUN_00799320(normalized, blended);
        param_3 = normalized;
        break;
    }
    case 3:
        if (0.5f < param_2) { param_3 = param_4; }
        break;
    case 4:
        break;
    case 5:
        param_3 = param_4;
        break;
    default:
        return;
    }
    *(Vec4 *)param_5 = *(Vec4 *)param_3;
    return;
}

// @ 0x0079b360
UShortVec& UShortVec::CopyFrom(const UShortVec& x)
{
    if (&x != this) {
        const uint16_t* const pFirst = x.mpBegin;
        const uint16_t* const pLast = x.mpEnd;
        const unsigned n = (unsigned)(pLast - pFirst);
        if (n > (unsigned)(mpCapacity - mpBegin)) {
            uint16_t* const pNewData = DoRealloc(n, pFirst, pLast);
            DoFree(mpBegin);
            mpBegin = pNewData;
            mpCapacity = pNewData + n;
            mpEnd = pNewData + n;
        } else if (n > (unsigned)(mpEnd - mpBegin)) {
            const unsigned sz = (unsigned)(mpEnd - mpBegin);
            memcpy(mpBegin, pFirst, sz * 2);
            const uint16_t* pMid = x.mpBegin + (mpEnd - mpBegin);
            memcpy(mpEnd, pMid, (char*)x.mpEnd - (char*)pMid);
            mpEnd = mpBegin + n;
        } else {
            memcpy(mpBegin, pFirst, (char*)pLast - (char*)pFirst);
            mpEnd = mpBegin + n;
        }
    }
    return *this;
}

// @ 0x0079f640
RefVec& RefVec::Assign(const RefVec& rhs)
{
    if (&rhs != this) {
        RefElem* rb = rhs.mpBegin;
        RefElem* re = rhs.mpEnd;
        uint n = (uint)(re - rb);
        if (n > (uint)(mpCap - mpBegin)) {
            RefElem* np = DoAllocateCopy(n, rb, re);
            DestroyRange(mpBegin, mpEnd);
            if (mpBegin && ((int*)mpBegin)[-1])
                operator_delete__(mpBegin);
            mpCap = np + n;
            mpEnd = np + n;
            mpBegin = np;
            return *this;
        }
        uint size = (uint)(mpEnd - mpBegin);
        if (n > size) {
            FUN_008defe0(rb, rb + size, mpBegin);
            RefElem* out;
            FUN_00799290(&out, rhs.mpBegin + (mpEnd - mpBegin), rhs.mpEnd, mpEnd, &rhs);
            mpEnd = mpBegin + n;
            return *this;
        }
        RefElem* p = FUN_008defe0(rb, re, mpBegin);
        DestroyRange(p, mpEnd);
        mpEnd = mpBegin + n;
    }
    return *this;
}

// @ 0x0079f8d0
void Tc::m_0079f8d0(int firstArg, int lastArg)
{
  VecBase* v = (VecBase*)this;
  char* first = (char*)firstArg;
  char* last  = (char*)lastArg;
  char* end   = (char*)v->mpEnd;
  if (end == v->mpCapacity) {
    int units = (int)(end - (char*)v->mpBegin) / 0x78;
    int cap;
    if (units == 0) { cap = 1; }
    else { cap = units * 2; if (cap == 0) cap = 0; }
    char* nb;
    if (cap == 0) nb = 0;
    else nb = (char*)operator_new(cap * 0x78, "Graphics", 0, 0, g_allocatorFile, 0xd1);
    FUN_0799dc0((int)v->mpBegin, (int)first, (int)nb);   // uninitialized_move [begin,first)
    char* p = first;
    if (p != nb) { /* (only used for its side effect) */ }
    // the destination of the moved prefix is nb; the new element goes after it
    char* dst = nb + ((char*)first - (char*)v->mpBegin);
    if (dst != 0) {
      *(int*)dst = *(int*)last;
      ((Tc*)(dst + 4))->m_0799450(last + 4);                     // cSplitInstance copy ctor
    }
    char* moved = dst + 0x78;
    FUN_0799dc0((int)first, (int)v->mpEnd, (int)moved);  // uninitialized_move [first,end)
    if (spNeedsDelete(v->mpBegin)) operator_delete(v->mpBegin);
    v->mpEnd = moved + ((char*)v->mpEnd - first);
    v->mpBegin = nb;
    v->mpCapacity = nb + cap * 0x78;
    return;
  }
  if (last >= first && last < end) last += 0x78;
  if (end != 0) {
    *(int*)end = *(int*)(end - 0x78);
    ((Tc*)(end + 4))->m_0799450(end - 0x74);
  }
  FUN_0079aaa0((int)first, (int)v->mpEnd + -0x78, (int)v->mpEnd);
  *(int*)first = *(int*)last;
  first[4] = last[4];
  ((Tc*)(first + 8))->m_0537dc0(last + 8);
  ((Tc*)(first + 0x40))->m_0537dc0(last + 0x40);
  v->mpEnd = (char*)v->mpEnd + 0x78;
}

// @ 0x0079fa70
void Tc::m_0079fa70(int pos, int n, int value)
{
  VecBase* v = (VecBase*)this;
  char* p = (char*)pos;
  if ((uint)count14(v->mpEnd, v->mpCapacity) < (uint)n) {
    int size = count14(v->mpBegin, v->mpEnd);
    uint cap = (uint)size * 2;
    if (size == 0) cap = 1;
    uint grow = (uint)size + (uint)n;
    uint newCap = grow > cap ? grow : cap;
    if (newCap == 0) newCap = (grow != 0) ? grow : 1;
    if (newCap == 0) newCap = 1;
    char* nb = 0;
    if (newCap != 0)
      nb = (char*)operator_new(newCap * 0x14, "Graphics", 0, 0, g_allocatorFile, 0xd1);
    char* begin = (char*)v->mpBegin;
    int   pre   = count14(begin, p);
    FUN_0799dc0((int)begin, (int)p, (int)nb);
    char* dst = nb + pre * 0x14;
    FUN_0079a8f0(n, value, (int)p);                      // fill n value-ish elements
    FUN_0799dc0((int)p, (int)v->mpEnd, (int)(dst + n * 0x14));
    if (spNeedsDelete(begin)) operator_delete(begin);
    v->mpBegin = nb;
    v->mpEnd = dst + n * 0x14 + count14(p, v->mpEnd) * 0x14;
    v->mpCapacity = nb + newCap * 0x14;
  } else if (n != 0) {
    Elem14 tmp;
    ((Tc*)&tmp)->m_0079a6c0(value);
    char* end = (char*)v->mpEnd;
    uint tail = (uint)count14(p, end);
    uint num = (uint)n;
    if (num < tail) {
      char* hole = end - num * 0x14;
      FUN_0079a800((int)&value, (int)hole, (int)end, (int)end, (int)p);
      v->mpEnd = (char*)v->mpEnd + num * 0x14;
      FUN_0079ab40((int)p, (int)hole, (int)end);
      FUN_0079b190((int)p, (int)(p + num * 0x14), (int)&tmp);
    } else {
      FUN_0079a8f0((int)end, (int)(num - tail), (int)&tmp);
      v->mpEnd = (char*)v->mpEnd + (num - tail) * 0x14;
      FUN_0079a800((int)&p, (int)p, (int)end, (int)v->mpEnd, (int)p);
      v->mpEnd = (char*)v->mpEnd + tail * 0x14;
      FUN_0079b190((int)p, (int)end, (int)&tmp);
    }
  }
}

// @ 0x0079fd20
void FUN_0079fd20(void* out, void* pvec)
{
  VecBase* v = (VecBase*)out;
  VecBase* src = (VecBase*)pvec;
  v->mpBegin = 0; v->mpEnd = 0; v->mpCapacity = 0;
  uint n = (uint)((char*)src->mpEnd - (char*)src->mpBegin) >> 2;
  for (uint i = 0; i < n; i++) {
    void* p = ((void**)src->mpBegin)[i];
    if (p != 0) ((volatile int*)p)[1] = ((volatile int*)p)[1] + 1;
    RefIndexPair* end = (RefIndexPair*)v->mpEnd;
    if (end < (RefIndexPair*)v->mpCapacity) {
      v->mpEnd = end + 1;
      if (end != 0) {
        end->mPtr = p;
        if (p != 0) ((volatile int*)p)[1] = ((volatile int*)p)[1] + 1;
        end->mIndex = (int)i;
      }
    } else {
      ((Tc*)0)->m_0079f4e0((int)v->mpEnd, (int)&p);
    }
    if (p != 0) {
      volatile int* rc = (volatile int*)p + 1;
      int old = *rc;
      *rc = old - 1;
      if (old == 1) {
        *rc = 1;
        (*(void(__thiscall*)(void*, int))*(void**)p)(p, 1);
      }
    }
  }
}

// @ 0x0079fe20
void __fastcall FUN_0079fe20(void* self)
{
  VecBase* v = (VecBase*)self;
  char* end = (char*)v->mpEnd;
  if (end < (char*)v->mpCapacity) {
    v->mpEnd = end + 0x20;
    if (end != 0) {
      *(int*)(end + 0x00) = 0;
      *(int*)(end + 0x04) = 0;
      *(int*)(end + 0x08) = 0;
      *(int*)(end + 0x0c) = 0xe;
      *(int*)(end + 0x10) = 0;
      *(int*)(end + 0x14) = 0;
      *(unsigned short*)(end + 0x18) = 0;
      *(unsigned short*)(end + 0x1a) = 0;
      *(int*)(end + 0x1c) = 0;
      return;
    }
  } else {
    Elem20 tmp;
    ((Tc*)self)->m_00424cf0((int)v->mpEnd, (int)&tmp);   // append empty string element
  }
}

// @ 0x0079fef0
void __fastcall FUN_0079fef0(void* self)
{
  VecBase* v = (VecBase*)self;
  char* end = (char*)v->mpEnd;
  if (end < (char*)v->mpCapacity) {
    v->mpEnd = end + 0x78;
    if (end != 0) {
      ((Elem78*)end)->mKey = -2;                // kKeyDataValid
      ((Tc*)(end + 4))->m_07993a0();     // cSplitInstance() -- tail call
    }
    return;
  }
  PushBackSlowElem78(v);
}

// @ 0x0079ff40
int Tc::m_0079ff40(void* src)
{
  cSplitInstanceList* list = (cSplitInstanceList*)this;
  int idx = list->mNextFree;
  if (idx < 1) {
    char* beg = (char*)list->mDataArray.mpBegin;
    char* end = (char*)list->mDataArray.mpEnd;
    idx = (int)(end - beg) / 0x78;
    FUN_0079fef0(&list->mDataArray);
  } else {
    char* slot = (char*)list->mDataArray.mpBegin + idx * 0x78;
    list->mNextFree = *(int*)slot;
    *(int*)slot = -2;
  }
  // Two out-of-line cSplitInstance copies (locals kept POD to avoid a /GS cookie).
  Elem78 a;
  ((Tc*)(&a.mBody))->m_0799450(src);         // cSplitInstance(copy) from src
  Elem78 b;
  b.mKey = -2;
  ((Tc*)(&b.mBody))->m_0799450(&a.mBody);    // cSplitInstance(copy) from a
  char* slot = (char*)list->mDataArray.mpBegin + idx * 0x78;
  *(int*)slot = b.mKey;                      // 0xfffffffe
  slot[4] = ((unsigned char*)&b.mBody)[0];   // b.mFlags
  ((Tc*)(slot + 8))->m_0537dc0((char*)&b.mBody + 4);
  ((Tc*)(slot + 0x40))->m_0537dc0((char*)&b.mBody + 0x3c);
  list->mInsertCount++;
  return idx;
}

// @ 0x007a0010
void Tc::m_007a0010(int n)
{
  VecBase* v = (VecBase*)this;
  int size = count14(v->mpBegin, v->mpEnd);
  if ((uint)size < (uint)n) {
    Elem14 tmp;
    tmp.m00 = 0; tmp.m04 = 0; tmp.m08 = 0;   // only the first 3 words are cleared
    ((Tc*)this)->m_0079fa70((int)v->mpEnd, n - size, (int)&tmp);
  } else {
    ((Tc*)this)->m_0079fa20((int)v->mpBegin + n * 0x14, (int)v->mpEnd);
  }
}

// @ 0x007a0110
void Tc::m_007a0110(void* pos, int n, void* value)
{
  VecBase* v = (VecBase*)this;
  char* p = (char*)pos;
  if ((uint)count14(v->mpEnd, v->mpCapacity) < (uint)n) {
    int size = count14(v->mpBegin, v->mpEnd);
    uint cap = (uint)size * 2;
    if (size == 0) cap = 1;
    uint grow = (uint)size + (uint)n;
    uint newCap = grow < cap ? cap : grow;
    char* nb = 0;
    if (newCap != 0)
      nb = (char*)operator_new(newCap * 0x14, "Graphics", 0, 0, g_allocatorFile, 0xd1);
    char* begin = (char*)v->mpBegin;
    uint preBytes = (uint)(p - begin);
    char* dst = (char*)FUN_011e0744(nb, begin, preBytes);                // move prefix
    dst = dst + (preBytes / 0x14) * 0x14;
    FUN_0079b2a0((int)dst, (int)n, (int)value, (int)p);
    uint tailBytes = (uint)((char*)v->mpEnd - p);
    char* moved = (char*)FUN_011e0744(dst + n * 0x14, p, tailBytes);      // move suffix
    if (spNeedsDelete(begin)) operator_delete(begin);
    v->mpBegin = nb;
    v->mpEnd = moved + (tailBytes / 0x14) * 0x14;
    v->mpCapacity = nb + newCap * 0x14;
  } else if (n != 0) {
    Elem14 tmp;
    ((Tc*)&tmp)->m_0079b150((int)value);
    char* end = (char*)v->mpEnd;
    uint tail = (uint)count14(p, end);
    uint num = (uint)n;
    if (num < tail) {
      char* hole = end - num * 0x14;
      FUN_0079b1c0((int)&value, (int)hole, (int)end, (int)end, (int)p);
      v->mpEnd = (char*)v->mpEnd + num * 0x14;
      FUN_0079b470((int)p, (int)hole, (int)end);
      FUN_0079fcc0((int)p, (int)(p + num * 0x14), (int)&tmp);
    } else {
      FUN_0079b2a0((int)end, (int)(num - tail), (int)&tmp, (int)p);
      v->mpEnd = (char*)v->mpEnd + (num - tail) * 0x14;
      FUN_0079b1c0((int)&p, (int)p, (int)end, (int)v->mpEnd, (int)p);
      v->mpEnd = (char*)v->mpEnd + tail * 0x14;
      FUN_0079fcc0((int)p, (int)end, (int)&tmp);
    }
  }
}

// @ 0x007a0360
void FUN_007a0360(void* p1, void* p2)
{
  VecBase* v1 = (VecBase*)p1;
  VecBase* v2 = (VecBase*)p2;
  int local_4 = count14(v1->mpBegin, v1->mpEnd);
  ((Tc*)v2)->m_007a0010(local_4);
  local_4 = count14(v1->mpBegin, v1->mpEnd);
  if (local_4 > 0) {
    int local_8 = 0;
    do {
      char* trans = (char*)v2->mpBegin + local_8;
      char* elem  = (char*)v1->mpBegin + local_8;
      FUN_0079f7b0(trans);
      int c = count8(*(void**)(elem + 0), *(void**)(elem + 4));
      for (int j = 0; j < c; j++)
        FUN_0079b6b0((int)trans, (int)(*(char**)(elem + 0) + j * 8));
      local_8 += 0x14;
      local_4--;
    } while (local_4 != 0);
  }
}

// @ 0x007a0410
void FUN_007a0410(void* self)
{
  VecBase* v = (VecBase*)self;
  int n = count14(v->mpBegin, v->mpEnd);
  for (int i = 0; i < n; i++)
    FUN_0079f7b0((void*)((char*)v->mpBegin + i * 0x14));
  ((Tc*)self)->m_007a0010(0);
}

// @ 0x007a0600
void Tc::m_007a0600(void* pos, void* value)
{
  VecBase* v = (VecBase*)this;
  char* p = (char*)pos;
  char* end = (char*)v->mpEnd;
  if (end != (char*)v->mpCapacity) {
    if (p <= (char*)value && (char*)value < end) value = (char*)value + 0x14;
    if (end != 0) ((Tc*)end)->m_0079a4a0((int)end - 0x14);
    FUN_0079f770((int)p, (int)v->mpEnd + -0x14, (int)v->mpEnd);
    ((Tc*)p)->m_0079f640((int)value);
    v->mpEnd = (char*)v->mpEnd + 0x14;
    return;
  }
  int units = (int)(end - (char*)v->mpBegin) / 0x14;
  int cap;
  if (units == 0) cap = 1;
  else { cap = units * 2; if (cap == 0) cap = 0; }
  char* nb = 0;
  if (cap != 0) nb = (char*)operator_new(cap * 0x14, "Graphics", 0, 0, g_allocatorFile, 0xd1);
  char* begin = (char*)v->mpBegin;
  uint preBytes = (uint)(p - begin);
  char* dst = (char*)FUN_011e0744(nb, begin, preBytes);                  // move prefix
  dst = dst + (preBytes / 0x14) * 0x14;
  if (dst != 0) ((Tc*)dst)->m_0079a4a0((int)value);
  uint tailBytes = (uint)((char*)v->mpEnd - p);
  char* moved = (char*)FUN_011e0744(dst + 0x14, p, tailBytes);            // move suffix
  if (spNeedsDelete(begin)) operator_delete(begin);
  v->mpEnd = moved + (tailBytes / 0x14) * 0x14;
  v->mpBegin = nb;
  v->mpCapacity = nb + cap * 0x14;
}

// @ 0x007a07b0
void VecV20::Insert(V20* position, unsigned n, const V20* pValue)
{
    if (n <= (unsigned)(mpCapacity - mpEnd)) {
        if (n > 0) {
            const V20 temp(*pValue);
            const unsigned nExtra = (unsigned)(mpEnd - position);
            V20* pOldEnd = mpEnd;
            if (n < nExtra) {
                UninitMove((V20**)&pValue, pOldEnd - n, pOldEnd, pOldEnd, position);
                mpEnd += n;
                MoveBackward(position, pOldEnd - n, pOldEnd);
                FillRange(position, position + n, &temp);
            } else {
                UninitFillN(pOldEnd, n - nExtra, &temp);
                mpEnd += n - nExtra;
                UninitMove(&position, position, pOldEnd, mpEnd, position);
                mpEnd += nExtra;
                FillRange(position, pOldEnd, &temp);
            }
        }
    } else {
        const unsigned nPrevSize = (unsigned)(mpEnd - mpBegin);
        unsigned nNewCap = nPrevSize ? nPrevSize * 2 : 1;
        if (nNewCap < nPrevSize + n) nNewCap = nPrevSize + n;
        V20* pNewData = 0;
        if (nNewCap)
            pNewData = (V20*)operator new(nNewCap * sizeof(V20), "Graphics", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
        unsigned nHead = (unsigned)((char*)position - (char*)mpBegin);
        V20* pNew = (V20*)MOVE(pNewData, mpBegin, nHead);
        V20* pFill = pNew + nHead / sizeof(V20);
        UninitFillN(pFill, n, pValue);
        unsigned nTail = (unsigned)((char*)mpEnd - (char*)position);
        V20* pTail = (V20*)MOVE(pFill + n, position, nTail);
        V20* pEnd = pTail + nTail / sizeof(V20);
        if (mpBegin && ((int*)mpBegin)[-1])
            operator delete[](mpBegin);
        mpBegin = pNewData;
        mpEnd = pEnd;
        mpCapacity = pNewData + nNewCap;
    }
}

// @ 0x007a0ee0
void IModelSplitter::Process(int a, V12* vec)
{
    V20* b0 = vec->b;
    V20* e0 = vec->e;
    V20* r = FindErase(e0, e0, b0);
    vec->Free(r, vec->e);
    vec->e += -(e0 - b0);
    vec->Add(MakeTmp(a));
    Notify(vec);
}

// @ 0x007a1400
ModelDst* GeomBuilder::Build(ModelSrc* src)
{
    if (mpB == mpE) return 0;
    ((StreamIdVec*)((char*)mDst + 0x1c))->Resize((int)(src->streamEnd - src->streamBegin));
    int nLists = (int)(mListsE - mListsB);
    for (int i = 0; i < nLists; ++i) {
        char* t1 = *(char**)((char*)mDst + 0x1c) + i * 0x8c;
        *(int*)(t1 + 0x10) = (int)(mpE - mpB);
        ((FixedIdVec6*)(t1 + 0x14))->Assign((char*)src->streamBegin + i * 0x8c + 0x14);
        ElemList* el = mListsB + i;
        RangeInfo ri((int)(((char*)el->e - (char*)el->b) >> 1), (unsigned short*)el->b);
        BuildStream(&ri, t1);
    }
    ((ElemVec*)((char*)mDst + 8))->Resize((int)(src->se - src->sb));
    unsigned nSrc = (unsigned)(src->se - src->sb);
    for (unsigned k = 0; k < nSrc; ++k) {
        CompiledStreamElem* e = src->sb + k;
        if (g_streamTable[e->k0] == 0) continue;
        ((ElemVec*)((char*)mDst + 8))->Grow();
        CompiledStreamElem* d = (CompiledStreamElem*)(*(char**)((char*)mDst + 0xc)) - 1;
        d->k3 = e->k3; d->k1 = e->k1; d->k0 = e->k0; d->k2 = e->k2;
        int kind = e->k3;
        if (kind < 0) continue;
        if (kind <= 2) {
            char* obj = (char*)d + 0x10;
            unsigned cnt = (unsigned)(mpE - mpB);
            BuildObj((int)cnt, e->w, obj);
            cnt = (unsigned)(mpE - mpB);
            for (unsigned j = 0; j < cnt; ++j) {
                PairElem* p = mpB + j;
                StreamDesc* sd = src->streamBegin + p->a;
                char* out = *(char**)(obj + 4) + (*(unsigned short*)(obj + 0xa)) * j;
                if (p->f != 0.0f) {
                    unsigned v2 = *(unsigned*)(sd->data + sd->stride * p->c) & g_sizeMask[sd->maskIdx];
                    unsigned v1 = *(unsigned*)(sd->data + sd->stride * p->b) & g_sizeMask[sd->maskIdx];
                    BlendCopy(d->k0, d->k2, p->f, (int)(v1 * e->stride + e->base),
                              (int)(v2 * e->stride + e->base), out);
                } else {
                    unsigned v1 = *(unsigned*)(sd->data + sd->stride * p->b) & g_sizeMask[sd->maskIdx];
                    MOVE(out, (void*)(v1 * e->stride + e->base), e->w);
                }
            }
        } else if (kind == 8) {
            HandleAssign((char*)d + 0x10, (char*)e + 0x10);
        }
    }
    return mDst;
}

// @ 0x007a23c0
void Builder::F23c0(Arg23c0* arg)
{
  SrcVec v = {0, 0, 0};
  v.Fill(arg);
  uint32_t n = v.e - v.b;
  arg->Resize(n);
  B tmp;
  if (n != 0) {
    SrcRange* sr = v.b;
    int off = 0;
    do {
      OutVec* ov = (OutVec*)((char*)arg->vecs + off);
      ov->Resize(sr->e - sr->b);
      uint32_t cnt = sr->e - sr->b;
      for (uint32_t j = 0; j < cnt; ++j) {
        PairRc* pr = &sr->b[j];
        F1940(pr->a, &tmp);
        if (tmp.p) ov->push_back(OutPair(tmp.p, pr->v));
        if (tmp.q) ov->push_back(OutPair(tmp.q, pr->v));
      }
      off += 0x14;
      ++sr;
    } while (--n != 0);
  }
}

// @ 0x007a26e0
void Converter::ConvertPairs1(GroupVec* dest)
{
    GroupVec source;
    source.begin = 0;
    source.end = 0;
    source.cap = 0;
    FUN_007a0b90(&source, 0, dest);

    int groupCount = (int)(source.end - source.begin);
    FUN_007a1100(dest, 0, groupCount);

    OutRecord out;
    InitOut(out);

    for (int i = 0; i < groupCount; ++i) {
        Group* target = dest->begin + i;
        Group* group = source.begin + i;
        int pairCount = (int)(group->end - group->begin);
        FUN_0079af80(target, 0, pairCount);
        for (int j = 0; j < pairCount; ++j) {
            Pair* pair = group->begin + j;
            FUN_007a1a80(this, 0, pair->object, &out);
            if (out.sp0 != 0)
                PushPair(target, out.sp0, pair->tag);
            if (out.sp1 != 0)
                PushPair(target, out.sp1, pair->tag);
        }
    }

    FUN_0079aeb0(&out);
    DestroyGroupVector(&source);
}

// @ 0x007a2a00
void Converter::ConvertPairs2(GroupVec* dest)
{
    GroupVec source;
    source.begin = 0;
    source.end = 0;
    source.cap = 0;
    FUN_007a0b90(&source, 0, dest);

    int groupCount = (int)(source.end - source.begin);
    FUN_007a1100(dest, 0, groupCount);

    OutRecord out;
    InitOut(out);

    for (int i = 0; i < groupCount; ++i) {
        Group* target = dest->begin + i;
        Group* group = source.begin + i;
        int pairCount = (int)(group->end - group->begin);
        FUN_0079af80(target, 0, pairCount);
        for (int j = 0; j < pairCount; ++j) {
            Pair* pair = group->begin + j;
            FUN_007a1bc0(this, 0, pair->object, &out);
            if (out.sp0 != 0)
                PushPair(target, out.sp0, pair->tag);
            if (out.sp1 != 0)
                PushPair(target, out.sp1, pair->tag);
        }
    }

    FUN_0079aeb0(&out);
    DestroyGroupVector(&source);
}

// @ 0x007a2d20
void Converter::ConvertPairPairs(Group2Vec* dest)
{
    GroupVec source;
    source.begin = 0;
    source.end = 0;
    source.cap = 0;
    FUN_007a0b90(&source, 0, dest);

    int groupCount = (int)(source.end - source.begin);
    FUN_007a1100(dest, 0, groupCount * 2);

    OutRecord outA;
    InitOut(outA);
    OutRecord outB;
    InitOut(outB);

    for (int i = 0; i < groupCount; ++i) {
        Group2* target = dest->begin + i;
        Group* group = source.begin + i;
        int pairCount = (int)(group->end - group->begin);
        FUN_0079af80(&target->a, 0, pairCount);
        FUN_0079af80(&target->b, 0, pairCount);
        for (int j = 0; j < pairCount; ++j) {
            Pair* pair = group->begin + j;
            FUN_007a1d00(this, 0, pair->object, &outA, &outB);
            if (outA.sp0 != 0)
                PushPair(&target->a, outA.sp0, pair->tag);
            if (outA.sp1 != 0)
                PushPair(&target->a, outA.sp1, pair->tag);
            if (outB.sp0 != 0)
                PushPair(&target->b, outB.sp0, pair->tag);
            if (outB.sp1 != 0)
                PushPair(&target->b, outB.sp1, pair->tag);
        }
    }

    FUN_0079aeb0(&outB);
    FUN_0079aeb0(&outA);
    DestroyGroupVector(&source);
}

// @ 0x007a3260
void MeshBuilder::BuildPairListsA(EntryVecVec* out)
{ Build<&MeshBuilder::GatherA>(out); }

// @ 0x007a37a0
void MeshBuilder::BuildPairListsB(EntryVecVec* out)
{ Build<&MeshBuilder::GatherB>(out); }
