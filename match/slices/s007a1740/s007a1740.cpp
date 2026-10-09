// slice s007a1740
// Mesh/index-range copy helpers (cl 15.00 /O2 /MD /Gy /EHsc /TP). Class names are
// descriptive placeholders (A = source mesh, B = destination builder); offsets from disassembly.
#include "types.h"
#include <intrin.h>
#include <new>
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

// @ 0x007a1740
void B::CopyFrom(A* src) {
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

#define ONE_DST(NAME, CB)                                                  \
  __declspec(noinline) void Builder::NAME(A* src, B* dst) {                \
    dst->Resize(src->pe - src->pb, src->ve - src->vb);                     \
    int n = src->pe - src->pb;                                             \
    if (n != 0) {                                                          \
      C* c = &dst->c;                                                      \
      int off = 0;                                                         \
      int k = n;                                                           \
      do {                                                                 \
        Prim* pr = (Prim*)((char*)src->pb + off);                          \
        Prim p = *pr;                                                      \
        Vec16* iv = &dst->idx[p.b];                                        \
        dst->f64 = iv->e - iv->b;                                          \
        c->f2c = p.a;                                                      \
        c->f30 = p.b;                                                      \
        c->f3c = p.e;                                                      \
        Vec16* rv = &c->v18[p.b];                                          \
        c->f34 = rv->e - rv->b;                                            \
        CB(src, pr, &dst->idx[pr->b], c);                                  \
        dst->Emit(*pr);                                                    \
        off += 0x14;                                                       \
      } while (--k != 0);                                                  \
    }                                                                      \
    dst->CopyFrom(src);                                                    \
  }

// @ 0x007a1940
ONE_DST(F1940, Cb1)
// @ 0x007a1a80
ONE_DST(F1a80, Cb2)
// @ 0x007a1bc0
ONE_DST(F1bc0, Cb3)

#define TWO_DST(NAME, CB)                                                  \
  __declspec(noinline) void Builder::NAME(A* src, B* d1, B* d2) {          \
    d1->Resize(src->pe - src->pb, src->ve - src->vb);                      \
    d2->Resize(src->pe - src->pb, src->ve - src->vb);                      \
    int n = src->pe - src->pb;                                             \
    if (n != 0) {                                                          \
      C* c2 = &d2->c;                                                      \
      C* c1 = &d1->c;                                                      \
      int off = 0;                                                         \
      int k = n;                                                           \
      do {                                                                 \
        Prim* pr = (Prim*)((char*)src->pb + off);                          \
        Prim p = *pr;                                                      \
        Vec16* iv1 = &d1->idx[p.b];                                        \
        d1->f64 = iv1->e - iv1->b;                                         \
        c1->f30 = p.b;                                                     \
        c1->f2c = p.a;                                                     \
        c1->f3c = p.e;                                                     \
        Vec16* rv1 = &c1->v18[p.b];                                        \
        c1->f34 = rv1->e - rv1->b;                                         \
        Prim q = *pr;                                                      \
        Vec16* iv2 = &d2->idx[q.b];                                        \
        d2->f64 = iv2->e - iv2->b;                                         \
        c2->f30 = q.b;                                                     \
        c2->f2c = q.a;                                                     \
        c2->f3c = q.e;                                                     \
        Vec16* rv2 = &c2->v18[q.b];                                        \
        c2->f34 = rv2->e - rv2->b;                                         \
        CB(src, pr, &d1->idx[pr->b], &d2->idx[pr->b], c1, c2);             \
        d1->Emit(*pr);                                                     \
        d2->Emit(*pr);                                                     \
        off += 0x14;                                                       \
      } while (--k != 0);                                                  \
    }                                                                      \
    d1->CopyFrom(src);                                                     \
    d2->CopyFrom(src);                                                     \
  }

// @ 0x007a1d00
TWO_DST(F1d00, Cb4)
// @ 0x007a1f40
TWO_DST(F1f40, Cb5)
// @ 0x007a2180
TWO_DST(F2180, Cb6)

// ---- 0x007a23c0 ----
struct PairRc {
  A* a;
  int v;
};

struct SrcRange {  // 0x14 bytes; list of (A*, int)
  PairRc* b;
  PairRc* e;
  uint32_t pad[3];
};

struct RcOwner {
  RcBase* p;
  RcOwner(RcBase* x) : p(x) { if (p) p->AddRef(); }
  RcOwner(const RcOwner& o) : p(o.p) { if (p) p->AddRef(); }
  ~RcOwner() { if (p) p->Release(); }
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

// @ 0x007a23c0
void Builder::F23c0(Arg23c0* arg) {
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
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct B {
    ~B(); // 0x0079aeb0
};
struct SrcVec {
    void Fill(void*); // 0x007a0b90
};
struct Arg23c0 {
    void Resize(unsigned int); // 0x007a1100
};
struct OutVec {
    void Resize(unsigned int); // 0x0079af80
    void Grow(void*, int&); // 0x0079f4e0
};
}
