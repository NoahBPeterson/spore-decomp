// src/game/SPEngine/_at_00790000.cpp -- migrated from slice(s) s0079dce0, s0079d190, s0079c960, s0079bfa0, s0079b020, s00798d30, s00797a20, s00796ed0, s00796910, s00795ec0 by tools/migrate/rewrite.py
// Object file: SPEngine/_at_00790000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern float DAT_016342f0[16];
extern float DAT_01634330[16];
extern unsigned char DAT_01634384;
extern void *operator_new__(void *, int, unsigned int);
#include <math.h>
#include <string.h>
#include <intrin.h>
#define __PLACEMENT_NEW_INLINE   // the slices' own placement new/delete win over <new>'s (rewrite.py)
#include <new>
inline void operator delete(void*, void*) {}   // placement delete (<new>'s is skipped, rewrite.py)

// ---- items of slice s00795ec0 begin (TODO(rewrite): local stubs, replace by canonical classes)
int DAT_01634370;
int DAT_01634374;
int DAT_01634378;
int DAT_0163437c;
int DAT_01634380;
extern float DAT_016342f0[16];
extern float DAT_01634330[16];
extern unsigned char DAT_01634384;
extern void *operator_new__(void *, int, unsigned int);
struct StubHandle {
    int __thiscall Method(int *);
};
// ---- items of slice s00795ec0 end

// ---- items of slice s00796910 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int DAT_0163437c;
extern int DAT_01634380;
extern int FUN_011fda50(...);
extern int (*DAT_01634378_s0079_6910)(...);
typedef float* (__thiscall* FrameAtProc)(void*, unsigned int);
// ---- items of slice s00796910 end

// ---- items of slice s00796ed0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int (*DAT_01634378_s0079_6ed0)(...);
// ---- items of slice s00796ed0 end

// ---- items of slice s00797a20 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int (*DAT_01634378_s0079_7a20)(...);
// ---- items of slice s00797a20 end

// ---- items of slice s00798d30 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int DAT_01634370;
extern int DAT_01634374;
extern void __cdecl FUN_00796910(int *, int *, int, int, float *, char *);
extern void __cdecl FUN_00796ed0();
extern void __cdecl FUN_00797a20(int *, int *, int, int, float *, char *, int, int);
extern int V_13ebc60;
extern int V_140f558;
extern int V_140f560;
extern int V_140f568;
extern int V_140f570;
extern int V_140f578;
extern int __cdecl FUN_00f473a0(...);
extern void __cdecl FUN_00c2e4e0();   // 0x00c2e4e0 default transform-notify callback
#define ABS(x) fabs(x)
extern int (*DAT_01634378_s0079_8d30)(...);
struct VObj { virtual void f0(); virtual void f1(int); };
struct AllocThing { int *alloc(int n, int extra); };
struct Mgr { void Notify(int param); };
struct VCtor { VCtor *c0(int *); VCtor *c1(int *); VCtor *c2(int *); VCtor *c3(int *); VCtor *c4(int *); };
struct PlaneQ { float x, y, z, d; long double IntersectRay(float *param_2, float *param_3); };
struct CylinderQ { float ox, oy, oz, dx, dy, dz, radiusSq; long double Intersect(float *param_2, float *param_3); };
struct RayQ { float ox, oy, oz, radiusSq; long double IntersectRay(float *param_2, float *param_3); };
// ---- items of slice s00798d30 end

// ---- items of slice s0079b020 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void  __cdecl EASTL_free(void* p);                                                                       // 0x00f47380
extern uint32_t g_IndexMask[];          // 0x0140f544: mask per index-format code
extern "C" void* __cdecl memcpy(void*, const void*, size_t);
extern void* __cdecl EASTL_allocate(size_t size, const char* name, int a, int b, const char* file, int line);  // 0x00f473a0
#define EASTL_ALLOC_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
static inline void* DoAlloc(size_t n)
{
    return EASTL_allocate(n, "Graphics", 0, 0, EASTL_ALLOC_FILE, 0xd1);
}
static inline void DoFree(void* p)
{
    if (p && ((int*)p)[-1] != 0) EASTL_free(p);
}
inline void* operator new(size_t, void* p) { return p; }
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
struct UShortVecRec : UShortVec {
    int       mExtra0;
    int       mExtra1;

    UShortVecRec(const UShortVecRec& x)
    {
        int n = (int)(x.mpEnd - x.mpBegin);
        uint16_t* p = n ? (uint16_t*)DoAlloc(n * 2) : 0;
        mpBegin = p;
        mpEnd = p;
        mpCapacity = p + n;
        int bytes = (int)((char*)x.mpEnd - (char*)x.mpBegin);
        mpEnd = (uint16_t*)memcpy(p, x.mpBegin, bytes) + (bytes >> 1);
    }
    void DestructRange(uint16_t* first, uint16_t* last);   // 0x008dede0
    __forceinline ~UShortVecRec()
    {
        DestructRange(mpBegin, mpEnd);
    }
};
struct UShortVecSrc : UShortVec {
    int mAllocState;    // +0xc
};
struct UShortVecDst : UShortVec {
    void DoCreate(int n, void* alloc);    // 0x00799840
    UShortVecDst* Assign(const UShortVecSrc& x);   // 0x0079b150
};
extern void __cdecl UninitCopyRecs(UShortVecRec** out, UShortVecRec* first, UShortVecRec* last, UShortVecRec* dest, const void* extra);   // 0x0079a710
struct RecVecBase {
    UShortVecRec* mpBegin;
    UShortVecRec* mpEnd;
    UShortVecRec* mpCapacity;
    RecVecBase() {}
    ~RecVecBase() { DoFree(mpBegin); }
};
struct RecVec : RecVecBase {
    RecVec(const RecVec& x);
    ~RecVec();
};
void __stdcall DestroyRecs(UShortVecRec* first, UShortVecRec* last);
RecVec::~RecVec() { DestroyRecs(mpBegin, mpEnd); }
struct Rec16 {          // vertex/edge origin record
    int   mSub;
    int   mA;
    int   mB;
    float mT;
    Rec16(int sub, int a, int b, float t) : mSub(sub), mA(a), mB(b), mT(t) {}
};
struct Rec20 {          // 5-word group record
    int mA, mIdx, mLimit, mSize, mExtra;
};
struct Rec16Vec {
    Rec16* mpBegin;
    Rec16* mpEnd;
    Rec16* mpCapacity;
    void DoInsertValue(Rec16* pos, const Rec16& v);       // 0x0079ace0
    void push_back(const Rec16& v)
    {
        if (mpEnd < mpCapacity) {
            Rec16* p = mpEnd;
            mpEnd = p + 1;
            if (p) *p = v;
        } else
            DoInsertValue(mpEnd, v);
    }
};
struct Rec20Vec {
    Rec20* mpBegin;
    Rec20* mpEnd;
    Rec20* mpCapacity;
    void DoInsertValue(Rec20* pos, const Rec20& v);       // 0x00428900
    void push_back(const Rec20& v)
    {
        if (mpEnd < mpCapacity) {
            Rec20* p = mpEnd;
            mpEnd = p + 1;
            if (p) *p = v;
        } else
            DoInsertValue(mpEnd, v);
    }
};
struct SplitParent {
    char     pad[0x30];
    Rec20Vec mGroups;
};
struct SplitCtx {
    SplitParent*  mpParent;     // +0
    Rec16Vec      mVerts;       // +4
    char          pad10[8];
    UShortVecRec* mpIndexSets;  // +0x18
    char          pad1c[0x10];
    Rec20         mCur;         // +0x2c (mCur.mIdx at +0x30 is the current index set)
    void AddVertex(int sub, int i);                       // 0x0079b4b0
    void AddEdge(int sub, int i, int j, float t);         // 0x0079b520
    void AddIndex(uint16_t v);                            // 0x0079b590
    void FinishGroup();                                   // 0x0079b5d0
};
struct SplitOuter {
    SplitParent*  mpParent;     // +0
    int           mPad4;
    SplitCtx      mCtx;         // +8
    UShortVecRec* mpSets;       // +0x48
    char          pad4c[0x10];
    Rec20         mCur;         // +0x5c
    void Flush(int a, int idx, int unused0, int unused1, int extra);   // 0x0079b630
};
struct SubmeshRef {
    void* mpModel;
    int   mVal;
};
struct ModelHdr {
    char     pad[0x30];
    struct Vec20 {                      // vector of 0x14-byte records at +0x30
        char* mpBegin;
        char* mpEnd;
        int size() const { return (int)((mpEnd - mpBegin) / 0x14); }
    } mRecords;
};
struct PairRec { void* mA; int mB; };
struct PairVec {
    PairRec* mpBegin;
    PairRec* mpEnd;
    PairRec* mpCapacity;
    void DoInsertValue(PairRec* pos, const PairRec& v);   // 0x006ec390
};
struct PtrVec {
    void** mpBegin;
    void** mpEnd;
    void** mpCapacity;
    void reserve(int n);                                   // 0x007658f0
    ~PtrVec() { DoFree(mpBegin); }
};
extern void __cdecl CompileToRwMeshes(void* model, int, PtrVec* out, int, int, int, int, int, int);   // 0x0072b630
struct Remap {                          // 0x10-byte index remap table
    int      pad0;
    char*    mpData;                    // +4
    uint16_t mFormat;                   // +8
    uint16_t mStride;                   // +0xa
    int      pad[1];
};
struct IndexBuf {                       // 0x8c-byte index buffer description
    int      pad0;
    char*    mpData;                    // +4
    uint16_t mFormat;                   // +8
    uint16_t mStride;                   // +0xa
    int      pad[2];
    char*    mpRemapSel;                // +0x14
    char     pad18[0x2c];
    Remap*   mpRemapBegin;              // +0x44
    Remap*   mpRemapEnd;                // +0x48
    char     pad4c[0x8c - 0x4c];
};
struct VertStream {                     // 0x20-byte vertex stream description
    int      pad0;
    char*    mpData;                    // +4
    uint16_t mFormat;                   // +8
    uint16_t mStride;                   // +0xa
    char     pad[0x20 - 0xc];
};
struct SplitModel {
    char        pad[8];
    VertStream* mpStreams;              // +8
    char        pad0c[0x10];
    IndexBuf*   mpIndexBufs;            // +0x1c
};
struct SplitRange {
    int pad0;
    int mSub;       // +4
    int mStart;     // +8
    int mEnd;       // +0xc
};
extern int __cdecl FindStream(SplitModel* model, int a, int b, int c, int d);    // 0x0071ddc0
struct PlaneEq {
    float x, y, z, d;
    float Intersect(const float* a, const float* b);      // 0x007998a0
};
struct SplitPlane {
    int     pad0[2];
    int     mMode;          // +8
    PlaneEq mEq;            // +0xc
    int     mSide;          // +0x1c
    void SplitTriangles(SplitModel* model, SplitRange* rng, UShortVec* out, SplitCtx* ctx);   // 0x0079b7b0
};
static inline uint16_t FetchIndex16(const IndexBuf* ib, int i)
{
    return *(uint16_t*)(ib->mStride * i + ib->mpData) & (uint16_t)g_IndexMask[ib->mFormat];
}
// ---- items of slice s0079b020 end

// ---- items of slice s0079bfa0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint;
typedef unsigned short ushort;
struct UShortVec_s0079_bfa0 {
    ushort* mpBegin; ushort* mpEnd; ushort* mpCap;
    void DoInsert(ushort* pos, const ushort* val);      // 0x6f5bc0
    void PushBackOOL(const ushort* val);                // 0x6f66a0 (cVecU16::push_back)
    void push_back(ushort v) {
        ushort tmp = v;
        if (mpEnd < mpCap) {
            ushort* p = mpEnd++;
            if (p)
                *p = v;
        } else {
            DoInsert(mpEnd, &tmp);
        }
    }
};
extern const uint g_formatMask[];                       // 0x140f544
struct Stream {                                         // vertex / index stream view
    uint  pad0;
    char* data;                                         // +4
    ushort fmt;                                         // +8
    ushort stride;                                      // +0xa
    uint  Read(uint i) const { return *(uint*)(data + stride * i) & g_formatMask[fmt]; }
    ushort ReadU16(uint i) const { return (ushort)(*(ushort*)(data + stride * i) & (ushort)g_formatMask[fmt]); }
};
struct IndexStream : Stream {                           // 0x8c bytes
    char pad1[0x14 - 0xc];
    char* table;                                        // +0x14: 4-byte entries, short at +2
    char pad2[0x44 - 0x18];
    Stream* remapBegin;                                 // +0x44 (0x10-byte records)
    Stream* remapEnd;                                   // +0x48
};
struct Mesh {
    char pad0[8];
    char* streams;                                      // +8: 0x20-byte stream descriptors, view at +0x10
    char pad1[0x1c - 0xc];
    char* indexStreams;                                 // +0x1c
};
extern "C" int FUN_0071ddc0(Mesh* m, int a, int b, int c, int d);   // find vertex stream (position)
struct VertRecord { uint v[4]; };                       // 16-byte output vertex record
struct Out {                                            // clip output builder
    char pad0[4];
    VertRecord* f4;                                     // +4: vertex records begin
    VertRecord* f8;                                     // +8: vertex records end
    char pad1[0x18 - 0xc];
    char* vecs;                                         // +0x18: 0x14-byte ushort vectors
    char pad2[0x30 - 0x1c];
    int  cur;                                           // +0x30
    void AddVert(int stream, int idx);                  // 0x79b4b0
    void AddLerp(int stream, int i, int j, float t);    // 0x79b520
    UShortVec_s0079_bfa0* IdxVec() { return (UShortVec_s0079_bfa0*)(vecs + cur * 0x14); }
};
struct Job {
    char pad0[4];
    int  stream;                                        // +4: index stream number (0x8c stride)
    int  start;                                         // +8
    int  end;                                           // +0xc
};
struct Cylinder {                                       // lives at CylinderClipper+0xc (esi = this+0xc at the calls)
    float cx, cy, cz;                                   // +0x0: a point on the axis
    float ax, ay, az;                                   // +0xc: unit axis direction
    float radiusSq;                                     // +0x18
    float Intersect(const float* a, const float* b);    // 0x7999a0 (x87 return): crossing parameter on a->b

    // 1 when the point's side matches keep: outside (squared distance from the axis > radius^2)
    // XOR keep == 0.
    __forceinline int Bit(const float* p, unsigned int keep) const
    {
        float dx = p[0] - cx;
        float dy = p[1] - cy;
        float dz = p[2] - cz;
        float t = (az * dz + ay * dy) + ax * dx;
        float rx = ax * t - dx;
        float ry = ay * t - dy;
        float rz = az * t - dz;
        float d2 = (rz * rz + ry * ry) + rx * rx;
        return ((radiusSq <= d2 && d2 != radiusSq) == keep) ? 1 : 0;
    }
};
struct CylinderClipper {
    char pad0[8];
    int      mode;                                      // +8
    Cylinder cyl;                                       // +0xc
    unsigned int keep;                                  // +0x28: which side the bit marks
    void Run(Mesh* mesh, Job* job, UShortVec_s0079_bfa0* out, Out* clip);
};
static __forceinline void PushRaw3(UShortVec_s0079_bfa0* v, const IndexStream* ib, uint i)
{
    v->push_back(ib->ReadU16(i));
    v->push_back(ib->ReadU16(i + 1));
    v->push_back(ib->ReadU16(i + 2));
}
// ---- items of slice s0079bfa0 end

// ---- items of slice s0079c960 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const uint32_t g_bitMask[];   // 0x0140f544: low-bit masks, indexed by bit count
struct Packed {
  int unk0;
  char* data;
  uint16_t bits;
  uint16_t stride;
  int pad;
};
struct VertexElement {     // 0x20 bytes
  int a, b, c, d;
  Packed packed;
};
struct RemapEntry { short a; short packedIndex; };
struct Stream_s0079_c960 {            // 0x8c bytes
  int pad0;
  char* data;              // +4
  uint16_t bits;           // +8
  uint16_t stride;         // +0xa
  int pad0c, pad10;
  const RemapEntry* remapTab; // +0x14: 4-byte entries, short at +2 selects a Packed in remapBegin
  uint32_t pad18[11];
  Packed* remapBegin;      // +0x44
  Packed* remapEnd;        // +0x48
  uint32_t pad4c[0x10];
};
struct Mesh_s0079_c960 {
  int pad0, pad4;
  VertexElement* elemBegin;  // +8
  VertexElement* elemEnd;    // +0xc
  int pad10, pad14, pad18;
  Stream_s0079_c960* streams;           // +0x1c
};
struct TriRange {
  int pad0;
  int stream;                // +4
  int start;                 // +8
  int end;                   // +0xc
};
struct UShortVec_s0079_c960 {
  uint16_t* mpBegin;
  uint16_t* mpEnd;
  uint16_t* mpCapacity;
  int pad[2];
  void __thiscall DoInsertValue(uint16_t* pos, const uint16_t& v);   // 0x006f5bc0
  inline void push_back(uint16_t value) {
    if (mpEnd < mpCapacity)
      ::new ((void*)mpEnd++) uint16_t(value);
    else
      DoInsertValue(mpEnd, value);
  }
};
struct NewVertex {
  int a, b, c;
  float t;
};
struct ClipOut {
  int pad0;
  NewVertex* vBegin;         // +4
  NewVertex* vEnd;           // +8
  NewVertex* vCap;           // +0xc
  int pad10, pad14;
  UShortVec_s0079_c960* indexSets;      // +0x18, stride 0x14
  int pad1c[4];
  int pad2c;
  int curSet;                // +0x30
  void __thiscall Pass(int stream, int v);                          // 0x0079b4b0
  void __thiscall Edge(int stream, int a, int b, float t);          // 0x0079b520
};
struct Sphere {
  float c[3];
  float r2;
  float __thiscall RayHit(const float* a, const float* b);          // 0x00799b50
};
int FindElement(Mesh_s0079_c960* m, int a, int b, int c, int d);                // 0x0071ddc0 (cdecl)
struct Clipper {
  int pad0, pad4;
  int mode;                  // +8
  Sphere sphere;             // +0xc
  int keepOutside;           // +0x1c
  void __thiscall Run(Mesh_s0079_c960* mesh, TriRange* range, UShortVec_s0079_c960* out, ClipOut* co);
};
static inline int Far(const Sphere& s, const float* p) {
  float dx = p[0] - s.c[0];
  float dy = p[1] - s.c[1];
  float dz = p[2] - s.c[2];
  return ((dz * dz + dy * dy) + dx * dx) > s.r2;
}
static inline uint32_t Fetch(const Packed* p, uint32_t i) {
  return *(uint32_t*)(p->data + p->stride * i) & g_bitMask[p->bits];
}
static inline uint16_t Fetch16(const Stream_s0079_c960* s, int i) {
  return *(uint16_t*)(s->data + s->stride * i) & (uint16_t)g_bitMask[s->bits];
}
// ---- items of slice s0079c960 end

// ---- items of slice s0079d190 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct UShortVec_s0079_d190 {
    uint16_t* mpBegin;
    uint16_t* mpEnd;
    uint16_t* mpCapacity;
    int       mAllocator;
    void DoInsertValue(uint16_t* pos, const uint16_t& v);       // 0x006f5bc0
    void push_back_call(const uint16_t& v);                     // 0x006f66a0 (out-of-line push_back)
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
struct UShortVecRec_s0079_d190 : UShortVec_s0079_d190 {
    int mExtra;
};
struct Rec16_s0079_d190 {          // vertex/edge origin record
    int   mSub;
    int   mA;
    int   mB;
    float mT;
};
struct Rec16Vec_s0079_d190 {
    Rec16_s0079_d190* mpBegin;
    Rec16_s0079_d190* mpEnd;
    Rec16_s0079_d190* mpCapacity;
};
struct SplitCtx_s0079_d190 {
    void*         mpParent;     // +0
    Rec16Vec_s0079_d190      mVerts;       // +4
    int           pad10[2];
    UShortVecRec_s0079_d190* mpIndexSets;  // +0x18
    int           pad1c[5];
    int           mCurIdx;      // +0x30 current index set
    void AddVertex(int sub, int i);                       // 0x0079b4b0
    void AddEdge(int sub, int i, int j, float t);         // 0x0079b520
    void AddIndex(uint16_t v);                            // 0x0079b590
    int VertexCount() const { return (int)(mVerts.mpEnd - mVerts.mpBegin); }
    void AddIndexInline(uint16_t v) { mpIndexSets[mCurIdx].push_back(v); }
};
struct IndexBuf_s0079_d190 {                       // 0x8c-byte index buffer description
    int      pad0;
    char*    mpData;                    // +4
    uint16_t mFormat;                   // +8
    uint16_t mStride;                   // +0xa
    int      pad[2];
    char*    mpRemapSel;                // +0x14
    int      pad18[11];
    Remap*   mpRemapBegin;              // +0x44
    Remap*   mpRemapEnd;                // +0x48
    int      pad4c[(0x8c - 0x4c) / 4];
};
struct VertStream_s0079_d190 {                     // 0x20-byte vertex stream description
    int      pad0;
    char*    mpData;                    // +4
    uint16_t mFormat;                   // +8
    uint16_t mStride;                   // +0xa
    int      pad[5];
};
struct SplitModel_s0079_d190 {
    int         pad[2];
    VertStream_s0079_d190* mpStreams;              // +8
    int         pad0c[4];
    IndexBuf_s0079_d190*   mpIndexBufs;            // +0x1c
};
extern int __cdecl FindStream(SplitModel_s0079_d190* model, int a, int b, int c, int d);    // 0x0071ddc0
static inline uint16_t FetchIndex16_s0079_d190(const IndexBuf_s0079_d190* ib, int i)
{
    return *(uint16_t*)(ib->mStride * i + ib->mpData) & (uint16_t)g_IndexMask[ib->mFormat];
}
struct SplitPlane2 {
    int     pad0[2];
    int     mMode;          // +8: 0 keep straddlers above, 1 below, 2 by majority, 3 cut
    PlaneEq mEq;            // +0xc
    void SplitTriangles(SplitModel_s0079_d190* model, SplitRange* rng, UShortVec_s0079_d190* above, UShortVec_s0079_d190* below,
                        SplitCtx_s0079_d190* ctxAbove, SplitCtx_s0079_d190* ctxBelow);
};
// ---- items of slice s0079d190 end

// ---- items of slice s0079dce0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct UShortVec_s0079_dce0 {
    ushort* mpBegin; ushort* mpEnd; ushort* mpCap;
    void DoInsert(ushort* pos, const ushort* val);      // 0x6f5bc0
    void PushBackOOL(const ushort* val);                // 0x6f66a0 (cVecU16::push_back)
    void push_back(ushort v) {
        ushort tmp = v;
        if (mpEnd < mpCap) {
            ushort* p = mpEnd++;
            if (p)
                *p = v;
        } else {
            DoInsert(mpEnd, &tmp);
        }
    }
};
struct Out_s0079_dce0 {                                            // clip output builder
    char pad0[4];
    VertRecord* f4;                                     // +4: vertex records begin
    VertRecord* f8;                                     // +8: vertex records end
    char pad1[0x18 - 0xc];
    char* vecs;                                         // +0x18: 0x14-byte ushort vectors
    char pad2[0x30 - 0x1c];
    int  cur;                                           // +0x30
    void AddVert(void* src, int idx);                   // 0x79b4b0
    void AddLerp(void* src, int i, int j, float t);     // 0x79b520
    void AddTri(int idx);                               // 0x79b590
    UShortVec_s0079_dce0* IdxVec() { return (UShortVec_s0079_dce0*)(vecs + cur * 0x14); }
};
struct Job_s0079_dce0 {
    char pad0[4];
    void* src;                                          // +4
    int  start;                                         // +8
    int  end;                                           // +0xc
};
struct Cylinder_s0079_dce0 {
    float cx, cy, cz;                                   // +0x0: a point on the axis
    float ax, ay, az;                                   // +0xc: unit axis direction
    float radiusSq;                                     // +0x18
    float Intersect(const float* a, const float* b);    // 0x7999a0 (x87 return): crossing parameter on a->b

    // Squared distance of p from the axis, compared with the radius.
    bool IsOutside(const float* p) const
    {
        float dx = p[0] - cx;
        float dy = p[1] - cy;
        float dz = p[2] - cz;
        float t = (az * dz + ay * dy) + ax * dx;
        float rx = ax * t - dx;
        float ry = ay * t - dy;
        float rz = az * t - dz;
        return (rz * rz + ry * ry) + rx * rx > radiusSq;
    }
};
struct CylinderSlicer {
    char pad0[8];
    int      mode;                                      // +8
    Cylinder_s0079_dce0 cyl;                                       // +0xc
    void Run(Mesh* mesh, Job_s0079_dce0* job, UShortVec_s0079_dce0* vecAllOut, UShortVec_s0079_dce0* vecAllIn, Out_s0079_dce0* out6, Out_s0079_dce0* out7);
};
// ---- items of slice s0079dce0 end

// @ 0x007965c0
int *__fastcall FUN_007965c0(int *param_1)
{
    float *p = (float *)param_1;
    int i;
    for (i = 0; i < 32; ++i) {
        p[i] = 0.0f;
    }
    p[0] = 1.0f;
    p[5] = 1.0f;
    p[10] = 1.0f;
    p[16] = 1.0f;
    p[21] = 1.0f;
    p[26] = 1.0f;
    param_1[0x20] = 0;
    param_1[0x21] = 0;
    param_1[0x22] = 0xc2e4e0;
    param_1[0x23] = 0;
    param_1[0x24] = 0;
    *(char *)(param_1 + 0x25) = 0;
    return param_1;
}

// @ 0x00796650
void FUN_00796650(StubHandle *param_1)
{
    if (param_1 != 0) {
        DAT_01634370 = param_1->Method(&DAT_01634374);
        return;
    }
    DAT_01634370 = 0;
    return;
}

// @ 0x00796680
void FUN_00796680(int param_1, int param_2, int param_3)
{
    DAT_01634378 = param_1;
    DAT_0163437c = param_2;
    DAT_01634380 = param_3;
    return;
}

// @ 0x007966a0
void __fastcall FUN_007966a0(int param_1)
{
    float *pDst;
    int iVar1;

    iVar1 = *(int *)(*(int *)(param_1 + 0xc) + 0xc);
    pDst = *(float **)(*(int *)(param_1 + 8));
    operator_new__(pDst, 0, iVar1 * 0x30);
    if (0 < iVar1) {
        do {
            pDst[0] = 1.0f;
            pDst[5] = 1.0f;
            pDst[10] = 1.0f;
            pDst = pDst + 12;
            iVar1 = iVar1 - 1;
        } while (iVar1 != 0);
    }
    return;
}

// @ 0x007966f0
void FUN_007966f0(int param_1)
{
    float s = *(float *)(param_1 + 0x10);
    float *m = (float *)param_1;
    DAT_016342f0[0] = m[5] * s;
    DAT_016342f0[4] = m[8] * s;
    DAT_016342f0[8] = m[11] * s;
    DAT_016342f0[1] = m[6] * s;
    DAT_016342f0[2] = m[7] * s;
    DAT_016342f0[3] = DAT_016342f0[0];
    DAT_016342f0[5] = m[9] * s;
    DAT_016342f0[6] = m[10] * s;
    DAT_016342f0[7] = DAT_016342f0[4];
    DAT_016342f0[9] = m[12] * s;
    DAT_016342f0[10] = m[13] * s;
    DAT_016342f0[11] = DAT_016342f0[8];
    DAT_016342f0[12] = m[1];
    DAT_016342f0[13] = m[2];
    DAT_016342f0[14] = m[3];
    DAT_016342f0[15] = m[1];
    return;
}

// @ 0x00796800
void FUN_00796800(int param_1)
{
    float s = *(float *)(param_1 + 0x10);
    float *m = (float *)param_1;
    DAT_01634330[0] = m[5] * s;
    DAT_01634330[4] = m[8] * s;
    DAT_01634330[8] = m[11] * s;
    DAT_01634330[1] = m[6] * s;
    DAT_01634330[2] = m[7] * s;
    DAT_01634330[3] = DAT_01634330[0];
    DAT_01634384 = 1;
    DAT_01634330[5] = m[9] * s;
    DAT_01634330[6] = m[10] * s;
    DAT_01634330[7] = DAT_01634330[4];
    DAT_01634330[9] = m[12] * s;
    DAT_01634330[10] = m[13] * s;
    DAT_01634330[11] = DAT_01634330[8];
    DAT_01634330[12] = m[1];
    DAT_01634330[13] = m[2];
    DAT_01634330[14] = m[3];
    DAT_01634330[15] = m[1];
    return;
}

// @ 0x00796910
int FUN_00796910(int *param_1,int *param_2,int param_3,int *param_4,float *param_5,float *param_6)
{
  unsigned int uVar1;
  int iVar2;
  float fVar3;
  float *pfVar4;
  unsigned int uVar5;
  float *pfVar6;
  float *pfVar7;
  unsigned int uVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  int local_11e8;
  float local_11e0;
  float fStack_11dc;
  float fStack_11d8;
  float fStack_11d4;
  float local_11d0;
  float fStack_11cc;
  float fStack_11c8;
  float fStack_11c4;
  float local_11c0;
  float fStack_11bc;
  float fStack_11b8;
  float fStack_11b4;
  float local_11b0;
  float fStack_11ac;
  float fStack_11a8;
  float fStack_11a4;
  float local_11a0;
  float fStack_119c;
  float fStack_1198;
  float fStack_1194;
  float local_1190;
  float fStack_118c;
  float fStack_1188;
  float fStack_1184;
  float local_1180;
  float fStack_117c;
  float fStack_1178;
  float fStack_1174;
  float local_1170;
  float fStack_116c;
  float fStack_1168;
  float fStack_1164;
  float fStack_1160;
  float fStack_115c;
  float fStack_1158;
  float fStack_1154;
  float local_1150;
  float fStack_114c;
  float fStack_1148;
  float fStack_1144;
  float fStack_1140;
  float fStack_113c;
  float fStack_1138;
  float fStack_1134;
  float fStack_1130;
  float fStack_112c;
  float fStack_1128;
  float fStack_1124;
  float fStack_1120;
  float fStack_111c;
  float fStack_1118;
  float fStack_1114;
  float fStack_1110;
  float fStack_110c;
  float fStack_1108;
  float fStack_1104;
  float fStack_1100;
  float fStack_10fc;
  float fStack_10f8;
  float fStack_10f4;
  float fStack_10f0;
  float fStack_10ec;
  float fStack_10e8;
  float fStack_10e4;
  float fStack_10e0;
  float fStack_10dc;
  float fStack_10d8;
  float fStack_10d4;
  float fStack_10d0;
  float fStack_10cc;
  float fStack_10c8;
  float fStack_10c4;
  float fStack_10c0;
  float fStack_10bc;
  float fStack_10b8;
  float fStack_10b4;
  float fStack_10b0;
  float fStack_10ac;
  float fStack_10a8;
  float fStack_10a4;
  float local_10a0;
  float fStack_109c;
  float fStack_1098;
  int uStack_1094;
  float local_1090;
  float fStack_108c;
  float fStack_1088;
  float fStack_1084;
  float local_1080;
  float fStack_107c;
  float fStack_1078;
  int uStack_1074;
  float fStack_1070;
  float fStack_106c;
  float fStack_1068;
  float fStack_1064;
  float fStack_1060;
  float fStack_105c;
  float fStack_1058;
  float fStack_1054;
  float fStack_1030;
  float fStack_102c;
  float fStack_1028;
  float fStack_1024;
  float local_fd0 [1007];
  int uStack_14;
  
  uStack_14 = 0x796920;
  pfVar7 = (float *)*param_4;
  local_11e0 = *param_5;
  fStack_11dc = param_5[1];
  fStack_11d8 = param_5[2];
  fStack_11d4 = param_5[3];
  local_11d0 = param_5[4];
  fStack_11cc = param_5[5];
  fStack_11c8 = param_5[6];
  fStack_11c4 = param_5[7];
  local_11c0 = param_5[8];
  fStack_11bc = param_5[9];
  fStack_11b8 = param_5[10];
  fStack_11b4 = param_5[0xb];
  local_11b0 = param_5[0xc];
  fStack_11ac = param_5[0xd];
  fStack_11a8 = param_5[0xe];
  fStack_11a4 = param_5[0xf];
  uVar1 = *(unsigned int *)(param_3 + 0x14);
  uVar8 = 0;
  if (uVar1 != 0) {
    local_1090 = 1.4142135;
    fStack_108c = 1.4142135;
    fStack_1088 = 1.4142135;
    fStack_1084 = 1.4142135;
    local_10a0 = 0.0;
    fStack_109c = 0.0;
    fStack_1098 = 0.0;
    uStack_1094 = 0;
    local_1080 = 0.5;
    fStack_107c = 0.5;
    fStack_1078 = 0.5;
    uStack_1074 = 0x3f000000;
    local_1150 = 1.0;
    fStack_114c = 1.0;
    fStack_1148 = 1.0;
    fStack_1144 = 1.0;
    local_11e8 = 0;
    pfVar6 = local_fd0 + 75;
    do {
      pfVar4 = ((FrameAtProc)FUN_011fda50)((void*)param_3, uVar8);
      fVar9 = local_1090 * *pfVar4;
      fVar10 = fStack_108c * pfVar4[1];
      fVar11 = fStack_1088 * pfVar4[2];
      fVar12 = fStack_1084 * pfVar4[3];
      fVar13 = (local_10a0 - fVar9) * fVar9 + local_1080;
      fVar14 = (fStack_109c - fVar10) * fVar10 + fStack_107c;
      fVar15 = (fStack_1098 - fVar11) * fVar11 + fStack_1078;
      fVar16 = fVar12 * fVar11 + fVar10 * fVar9;
      fVar18 = fVar12 * fVar9 + fVar11 * fVar10;
      fVar20 = fVar12 * fVar10 + fVar9 * fVar11;
      fVar22 = fVar10 * fVar9 - fVar12 * fVar11;
      fVar23 = fVar11 * fVar10 - fVar12 * fVar9;
      fVar12 = fVar9 * fVar11 - fVar12 * fVar10;
      fVar24 = fVar14 + fVar13;
      fVar14 = fVar15 + fVar14;
      fVar13 = fVar13 + fVar15;
      fVar9 = pfVar4[4];
      fVar10 = pfVar4[5];
      fVar11 = pfVar4[6];
      local_11a0 = (fVar16 * local_11d0 + fVar14 * local_11e0) + fVar12 * local_11c0;
      fStack_119c = (fVar16 * fStack_11cc + fVar14 * fStack_11dc) + fVar12 * fStack_11bc;
      fStack_1198 = (fVar16 * fStack_11c8 + fVar14 * fStack_11d8) + fVar12 * fStack_11b8;
      fStack_1194 = (fVar16 * fStack_11c4 + fVar14 * fStack_11d4) + fVar12 * fStack_11b4;
      local_1190 = (fVar13 * local_11d0 + fVar22 * local_11e0) + fVar18 * local_11c0;
      fStack_118c = (fVar13 * fStack_11cc + fVar22 * fStack_11dc) + fVar18 * fStack_11bc;
      fStack_1188 = (fVar13 * fStack_11c8 + fVar22 * fStack_11d8) + fVar18 * fStack_11b8;
      fStack_1184 = (fVar13 * fStack_11c4 + fVar22 * fStack_11d4) + fVar18 * fStack_11b4;
      local_1180 = (fVar23 * local_11d0 + fVar20 * local_11e0) + fVar24 * local_11c0;
      fStack_117c = (fVar23 * fStack_11cc + fVar20 * fStack_11dc) + fVar24 * fStack_11bc;
      fStack_1178 = (fVar23 * fStack_11c8 + fVar20 * fStack_11d8) + fVar24 * fStack_11b8;
      fStack_1174 = (fVar23 * fStack_11c4 + fVar20 * fStack_11d4) + fVar24 * fStack_11b4;
      local_1170 = ((fVar10 * local_11d0 + fVar9 * local_11e0) + fVar11 * local_11c0) +
                   local_11b0 * local_1150;
      fStack_116c = ((fVar10 * fStack_11cc + fVar9 * fStack_11dc) + fVar11 * fStack_11bc) +
                    fStack_11ac * fStack_114c;
      fStack_1168 = ((fVar10 * fStack_11c8 + fVar9 * fStack_11d8) + fVar11 * fStack_11b8) +
                    fStack_11a8 * fStack_1148;
      fStack_1164 = ((fVar10 * fStack_11c4 + fVar9 * fStack_11d4) + fVar11 * fStack_11b4) +
                    fStack_11a4 * fStack_1144;
      iVar2 = *(int *)(param_2[2] + uVar8 * 4);
      if ((DAT_01634380 == -1) || (DAT_01634380 == iVar2)) {
        (*DAT_01634378_s0079_6910)(iVar2,&local_11a0,0,DAT_0163437c);
      }
      pfVar4 = (float *)(*param_1 + local_11e8);
      fVar9 = *pfVar4;
      fVar10 = pfVar4[1];
      fVar11 = pfVar4[2];
      fVar12 = pfVar4[6];
      fVar13 = pfVar4[4];
      fVar14 = (fVar9 * local_11a0 + fVar10 * local_1190) + fVar11 * local_1180;
      fVar15 = (fVar9 * fStack_119c + fVar10 * fStack_118c) + fVar11 * fStack_117c;
      fVar16 = (fVar9 * fStack_1198 + fVar10 * fStack_1188) + fVar11 * fStack_1178;
      fVar18 = (fVar9 * fStack_1194 + fVar10 * fStack_1184) + fVar11 * fStack_1174;
      fVar9 = pfVar4[5];
      fVar10 = pfVar4[9];
      fVar11 = pfVar4[10];
      fVar20 = (fVar13 * local_11a0 + fVar9 * local_1190) + fVar12 * local_1180;
      fVar22 = (fVar13 * fStack_119c + fVar9 * fStack_118c) + fVar12 * fStack_117c;
      fVar23 = (fVar13 * fStack_1198 + fVar9 * fStack_1188) + fVar12 * fStack_1178;
      fVar24 = (fVar13 * fStack_1194 + fVar9 * fStack_1184) + fVar12 * fStack_1174;
      fVar9 = pfVar4[8];
      fVar12 = pfVar4[0xc];
      fVar13 = pfVar4[0xd];
      fVar17 = (fVar9 * local_11a0 + fVar10 * local_1190) + fVar11 * local_1180;
      fVar19 = (fVar9 * fStack_119c + fVar10 * fStack_118c) + fVar11 * fStack_117c;
      fVar21 = (fVar9 * fStack_1198 + fVar10 * fStack_1188) + fVar11 * fStack_1178;
      fVar10 = (fVar9 * fStack_1194 + fVar10 * fStack_1184) + fVar11 * fStack_1174;
      fVar9 = pfVar4[0xe];
      fStack_1100 = ((fVar12 * local_11a0 + fVar13 * local_1190) + fVar9 * local_1180) +
                    local_1170 * local_1150;
      fStack_10fc = ((fVar12 * fStack_119c + fVar13 * fStack_118c) + fVar9 * fStack_117c) +
                    fStack_116c * fStack_114c;
      fStack_10f8 = ((fVar12 * fStack_1198 + fVar13 * fStack_1188) + fVar9 * fStack_1178) +
                    fStack_1168 * fStack_1148;
      fStack_10f4 = ((fVar12 * fStack_1194 + fVar13 * fStack_1184) + fVar9 * fStack_1174) +
                    fStack_1164 * fStack_1144;
      fStack_1110 = fVar14;
      fStack_110c = fVar15;
      fStack_1108 = fVar16;
      fStack_1104 = fVar18;
      fStack_1140 = fVar20;
      fStack_113c = fVar22;
      fStack_1138 = fVar23;
      fStack_1134 = fVar24;
      fStack_1130 = fVar17;
      fStack_112c = fVar19;
      fStack_1128 = fVar21;
      fStack_1124 = fVar10;
      if (param_6 != (float *)0x0) {
        fVar9 = *param_6;
        fVar11 = param_6[1];
        fVar12 = param_6[2];
        fVar13 = param_6[4];
        fVar3 = param_6[6];
        fStack_1110 = (fVar11 * fVar20 + fVar9 * fVar14) + fVar12 * fVar17;
        fStack_110c = (fVar11 * fVar22 + fVar9 * fVar15) + fVar12 * fVar19;
        fStack_1108 = (fVar11 * fVar23 + fVar9 * fVar16) + fVar12 * fVar21;
        fStack_1104 = (fVar11 * fVar24 + fVar9 * fVar18) + fVar12 * fVar10;
        fVar9 = param_6[5];
        fVar11 = param_6[9];
        fVar12 = param_6[8];
        fStack_1140 = (fVar9 * fVar20 + fVar13 * fVar14) + fVar3 * fVar17;
        fStack_113c = (fVar9 * fVar22 + fVar13 * fVar15) + fVar3 * fVar19;
        fStack_1138 = (fVar9 * fVar23 + fVar13 * fVar16) + fVar3 * fVar21;
        fStack_1134 = (fVar9 * fVar24 + fVar13 * fVar18) + fVar3 * fVar10;
        fStack_1160 = fVar11 * fVar20 + fVar12 * fVar14;
        fStack_115c = fVar11 * fVar22 + fVar12 * fVar15;
        fStack_1158 = fVar11 * fVar23 + fVar12 * fVar16;
        fStack_1154 = fVar11 * fVar24 + fVar12 * fVar18;
        fVar9 = param_6[10];
        fStack_1130 = fStack_1160 + fVar9 * fVar17;
        fStack_112c = fStack_115c + fVar9 * fVar19;
        fStack_1128 = fStack_1158 + fVar9 * fVar21;
        fStack_1124 = fStack_1154 + fVar9 * fVar10;
        fVar9 = param_6[0xd];
        fVar11 = param_6[0xc];
        fVar12 = param_6[0xe];
        fStack_1100 = ((fVar9 * fVar20 + fVar11 * fVar14) + fVar12 * fVar17) +
                      fStack_1100 * local_1150;
        fStack_10fc = ((fVar9 * fVar22 + fVar11 * fVar15) + fVar12 * fVar19) +
                      fStack_10fc * fStack_114c;
        fStack_10f8 = ((fVar9 * fVar23 + fVar11 * fVar16) + fVar12 * fVar21) +
                      fStack_10f8 * fStack_1148;
        fStack_10f4 = ((fVar9 * fVar24 + fVar11 * fVar18) + fVar12 * fVar10) +
                      fStack_10f4 * fStack_1144;
        fStack_1030 = fStack_1130;
        fStack_102c = fStack_112c;
        fStack_1028 = fStack_1128;
        fStack_1024 = fStack_1124;
      }
      iVar2 = *param_2;
      pfVar7[8] = fStack_1108;
      pfVar7[1] = fStack_1140;
      pfVar7[5] = fStack_113c;
      pfVar7[9] = fStack_1138;
      pfVar7[2] = fStack_1130;
      pfVar7[6] = fStack_112c;
      pfVar7[10] = fStack_1128;
      pfVar7[3] = fStack_1100;
      *pfVar7 = fStack_1110;
      pfVar7[7] = fStack_10fc;
      pfVar7[4] = fStack_110c;
      pfVar7[0xb] = fStack_10f8;
      uVar5 = *(unsigned int *)(iVar2 + uVar8 * 4) & 3;
      pfVar4 = pfVar6;
      if (uVar5 == 0) {
LAB_00796e53:
        local_11e0 = local_11a0;
        fStack_11dc = fStack_119c;
        fStack_11d8 = fStack_1198;
        fStack_11d4 = fStack_1194;
        local_11d0 = local_1190;
        fStack_11cc = fStack_118c;
        fStack_11c8 = fStack_1188;
        fStack_11c4 = fStack_1184;
        local_11c0 = local_1180;
        fStack_11bc = fStack_117c;
        fStack_11b8 = fStack_1178;
        fStack_11b4 = fStack_1174;
        local_11b0 = local_1170;
        fStack_11ac = fStack_116c;
        fStack_11a8 = fStack_1168;
        fStack_11a4 = fStack_1164;
      }
      else if (uVar5 == 1) {
        local_11e0 = pfVar6[-0x10];
        fStack_11dc = pfVar6[-0xf];
        fStack_11d8 = pfVar6[-0xe];
        fStack_11d4 = pfVar6[-0xd];
        pfVar4 = pfVar6 + -0x10;
        local_11d0 = pfVar6[-0xc];
        fStack_11cc = pfVar6[-0xb];
        fStack_11c8 = pfVar6[-10];
        fStack_11c4 = pfVar6[-9];
        local_11c0 = pfVar6[-8];
        fStack_11bc = pfVar6[-7];
        fStack_11b8 = pfVar6[-6];
        fStack_11b4 = pfVar6[-5];
        local_11b0 = pfVar6[-4];
        fStack_11ac = pfVar6[-3];
        fStack_11a8 = pfVar6[-2];
        fStack_11a4 = pfVar6[-1];
      }
      else if (uVar5 == 2) {
        *pfVar6 = local_11e0;
        pfVar6[1] = fStack_11dc;
        pfVar6[2] = fStack_11d8;
        pfVar6[3] = fStack_11d4;
        pfVar6[4] = local_11d0;
        pfVar6[5] = fStack_11cc;
        pfVar6[6] = fStack_11c8;
        pfVar6[7] = fStack_11c4;
        pfVar6[8] = local_11c0;
        pfVar6[9] = fStack_11bc;
        pfVar6[10] = fStack_11b8;
        pfVar6[0xb] = fStack_11b4;
        pfVar4 = pfVar6 + 0x10;
        pfVar6[0xc] = local_11b0;
        pfVar6[0xd] = fStack_11ac;
        pfVar6[0xe] = fStack_11a8;
        pfVar6[0xf] = fStack_11a4;
        goto LAB_00796e53;
      }
      local_11e8 = local_11e8 + 0x40;
      uVar8 = uVar8 + 1;
      pfVar7 = pfVar7 + 0xc;
      pfVar6 = pfVar4;
      fStack_1120 = fStack_1130;
      fStack_111c = fStack_112c;
      fStack_1118 = fStack_1128;
      fStack_1114 = fStack_1124;
      fStack_10f0 = fStack_1140;
      fStack_10ec = fStack_113c;
      fStack_10e8 = fStack_1138;
      fStack_10e4 = fStack_1134;
      fStack_10e0 = fStack_1100;
      fStack_10dc = fStack_10fc;
      fStack_10d8 = fStack_10f8;
      fStack_10d4 = fStack_10f4;
      fStack_10d0 = fStack_1140;
      fStack_10cc = fStack_113c;
      fStack_10c8 = fStack_1138;
      fStack_10c4 = fStack_1134;
      fStack_10c0 = fStack_1100;
      fStack_10bc = fStack_10fc;
      fStack_10b8 = fStack_10f8;
      fStack_10b4 = fStack_10f4;
      fStack_10b0 = fStack_1110;
      fStack_10ac = fStack_110c;
      fStack_10a8 = fStack_1108;
      fStack_10a4 = fStack_1104;
      fStack_1070 = fStack_1110;
      fStack_106c = fStack_110c;
      fStack_1068 = fStack_1108;
      fStack_1064 = fStack_1104;
      fStack_1060 = fStack_1130;
      fStack_105c = fStack_112c;
      fStack_1058 = fStack_1128;
      fStack_1054 = fStack_1124;
    } while (uVar8 < uVar1);
  }
  return 1;
}

// @ 0x00796ed0
int FUN_00796ed0(int *param_1,int *param_2,int param_3,int *param_4,float *param_5,float *param_6)
{
  int iVar1;
  float *pfVar2;
  unsigned int uVar3;
  float *pfVar4;
  float *pfVar5;
  unsigned int uVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  float *local_1734;
  int local_1730;
  float local_172c;
  float local_1728;
  float local_1724;
  float local_1720;
  float fStack_171c;
  float fStack_1718;
  float fStack_1714;
  unsigned int local_1704;
  float local_1700;
  float fStack_16fc;
  float fStack_16f8;
  float fStack_16f4;
  float local_16f0;
  float fStack_16ec;
  float fStack_16e8;
  float fStack_16e4;
  float local_16e0;
  float fStack_16dc;
  float fStack_16d8;
  float fStack_16d4;
  float local_16d0;
  float fStack_16cc;
  float fStack_16c8;
  float fStack_16c4;
  float local_16c0;
  float fStack_16bc;
  float fStack_16b8;
  float fStack_16b4;
  float local_16b0;
  float fStack_16ac;
  float fStack_16a8;
  float fStack_16a4;
  float local_16a0;
  float fStack_169c;
  float fStack_1698;
  float fStack_1694;
  float local_1690;
  float fStack_168c;
  float fStack_1688;
  float fStack_1684;
  float local_1680;
  float fStack_167c;
  float fStack_1678;
  float fStack_1674;
  float local_1670;
  float fStack_166c;
  float fStack_1668;
  float fStack_1664;
  float fStack_1660;
  float fStack_165c;
  float fStack_1658;
  float fStack_1654;
  float fStack_1650;
  float fStack_164c;
  float fStack_1648;
  float fStack_1644;
  float fStack_1640;
  float fStack_163c;
  float fStack_1638;
  float fStack_1634;
  float fStack_1630;
  float fStack_162c;
  float fStack_1628;
  float fStack_1624;
  float fStack_1620;
  float fStack_161c;
  float fStack_1618;
  float fStack_1614;
  float fStack_1610;
  float fStack_160c;
  float fStack_1608;
  float fStack_1604;
  float fStack_1600;
  float fStack_15fc;
  float fStack_15f8;
  float fStack_15f4;
  float fStack_15f0;
  float fStack_15ec;
  float fStack_15e8;
  float fStack_15e4;
  float fStack_15e0;
  float fStack_15dc;
  float fStack_15d8;
  float fStack_15d4;
  float local_15d0;
  float fStack_15cc;
  float fStack_15c8;
  float fStack_15c4;
  float fStack_15c0;
  float fStack_15bc;
  float fStack_15b8;
  float fStack_15b4;
  float fStack_15b0;
  float fStack_15ac;
  float fStack_15a8;
  float fStack_15a4;
  float local_15a0;
  float fStack_159c;
  float fStack_1598;
  float fStack_1594;
  float fStack_1590;
  float fStack_158c;
  float fStack_1588;
  float fStack_1584;
  float local_1580;
  float fStack_157c;
  float fStack_1578;
  int uStack_1574;
  float fStack_1570;
  float fStack_156c;
  float fStack_1568;
  float fStack_1564;
  float fStack_1560;
  float fStack_155c;
  float fStack_1558;
  float fStack_1554;
  float fStack_1550;
  float fStack_154c;
  float fStack_1548;
  float fStack_1544;
  float fStack_1540;
  float fStack_153c;
  float fStack_1538;
  float fStack_1534;
  float fStack_1530;
  float fStack_152c;
  float fStack_1528;
  float fStack_1524;
  float fStack_1520;
  float fStack_151c;
  float fStack_1518;
  float fStack_1514;
  float local_1500;
  float fStack_14fc;
  float fStack_14f8;
  float fStack_14f4;
  float local_14f0;
  float fStack_14ec;
  float fStack_14e8;
  float fStack_14e4;
  float fStack_14d0;
  float fStack_14cc;
  float fStack_14c8;
  float fStack_14c4;
  float fStack_14c0;
  float fStack_14bc;
  float fStack_14b8;
  float fStack_14b4;
  float fStack_14b0;
  float fStack_14ac;
  float fStack_14a8;
  float fStack_14a4;
  float fStack_1480;
  float fStack_147c;
  float fStack_1478;
  float fStack_1474;
  float fStack_1470;
  float fStack_146c;
  float fStack_1468;
  float fStack_1464;
  float local_1430;
  float fStack_142c;
  float fStack_1428;
  float fStack_1424;
  struct CacheInverse {
    float guard[32];
    float data[268];
  } cacheInverse;
  struct CacheMatrix {
    float guard[128];
    float data[1007];
  } cacheMatrix;
  int uStack_14;
  
  uStack_14 = 0x796ee0;
  pfVar5 = (float *)*param_4;
  local_16b0 = *param_5;
  fStack_16ac = param_5[1];
  fStack_16a8 = param_5[2];
  fStack_16a4 = param_5[3];
  local_16a0 = param_5[4];
  fStack_169c = param_5[5];
  fStack_1698 = param_5[6];
  fStack_1694 = param_5[7];
  local_1690 = param_5[8];
  fStack_168c = param_5[9];
  fStack_1688 = param_5[10];
  fStack_1684 = param_5[0xb];
  local_1680 = param_5[0xc];
  fStack_167c = param_5[0xd];
  fStack_1678 = param_5[0xe];
  fStack_1674 = param_5[0xf];
  local_1704 = *(unsigned int *)(param_3 + 0x14);
  uVar6 = 0;
  {
    unsigned int fill = 0xCCCCCCCCu;
    for (int i = 0; i < 32; i++) ((unsigned int *)cacheInverse.guard)[i] = fill;
    for (int i = 0; i < 128; i++) ((unsigned int *)cacheMatrix.guard)[i] = fill;
  }
  local_1734 = cacheInverse.data;
  local_1670 = 1.0;
  fStack_166c = 1.0;
  fStack_1668 = 1.0;
  fStack_1664 = 1.0;
  if (local_1704 != 0) {
    local_15a0 = 1.4142135;
    fStack_159c = 1.4142135;
    fStack_1598 = 1.4142135;
    fStack_1594 = 1.4142135;
    local_1580 = 0.5;
    fStack_157c = 0.5;
    fStack_1578 = 0.5;
    uStack_1574 = 0x3f000000;
    local_15d0 = 0.0;
    fStack_15cc = 0.0;
    fStack_15c8 = 0.0;
    fStack_15c4 = 0.0;
    local_1720 = 1.0;
    fStack_171c = 1.0;
    fStack_1718 = 1.0;
    fStack_1714 = 1.0;
    local_1730 = 0;
    pfVar4 = cacheMatrix.data;
    do {
      typedef float *(__thiscall *FrameAtFn)(void *, unsigned int);
      pfVar2 = ((FrameAtFn)FUN_011fda50)((void *)param_3, uVar6);
      local_172c = pfVar2[7];
      local_1728 = pfVar2[8];
      local_1724 = pfVar2[9];
      fVar7 = local_15a0 * *pfVar2;
      fVar8 = fStack_159c * pfVar2[1];
      fVar9 = fStack_1598 * pfVar2[2];
      fVar10 = fStack_1594 * pfVar2[3];
      fStack_14fc = (local_15d0 - fVar7) * fVar7 + local_1580;
      fVar16 = (fStack_15cc - fVar8) * fVar8 + fStack_157c;
      fVar18 = (fStack_15c8 - fVar9) * fVar9 + fStack_1578;
      fStack_14f4 = fVar10 * fVar9 + fVar8 * fVar7;
      fStack_14f8 = fVar10 * fVar7 + fVar9 * fVar8;
      local_14f0 = fVar10 * fVar8 + fVar7 * fVar9;
      local_1500 = fVar8 * fVar7 - fVar10 * fVar9;
      fStack_14ec = fVar9 * fVar8 - fVar10 * fVar7;
      fVar22 = fVar7 * fVar9 - fVar10 * fVar8;
      fStack_14e8 = fVar16 + fStack_14fc;
      fVar16 = fVar18 + fVar16;
      fStack_14fc = fStack_14fc + fVar18;
      fVar7 = (local_172c * fVar16 + fStack_15cc * local_1500) + fStack_15c8 * local_14f0;
      fVar8 = (local_172c * fStack_14f4 + fStack_15cc * fStack_14fc) + fStack_15c8 * fStack_14ec;
      fVar9 = (local_172c * fVar22 + fStack_15cc * fStack_14f8) + fStack_15c8 * fStack_14e8;
      fVar15 = (local_15d0 * fVar16 + local_1728 * local_1500) + fStack_15c8 * local_14f0;
      fVar17 = (local_15d0 * fStack_14f4 + local_1728 * fStack_14fc) + fStack_15c8 * fStack_14ec;
      fVar19 = (local_15d0 * fVar22 + local_1728 * fStack_14f8) + fStack_15c8 * fStack_14e8;
      fVar20 = (local_15d0 * fVar16 + fStack_15cc * local_1500) + local_1724 * local_14f0;
      fVar21 = (local_15d0 * fStack_14f4 + fStack_15cc * fStack_14fc) + local_1724 * fStack_14ec;
      fVar23 = (local_15d0 * fVar22 + fStack_15cc * fStack_14f8) + local_1724 * fStack_14e8;
      fVar10 = ((local_15d0 * fVar16 + fStack_15cc * local_1500) + fStack_15c8 * local_14f0) +
               local_1720 * local_15d0;
      fVar16 = ((local_15d0 * fStack_14f4 + fStack_15cc * fStack_14fc) + fStack_15c8 * fStack_14ec)
               + fStack_171c * fStack_15cc;
      fVar18 = ((local_15d0 * fVar22 + fStack_15cc * fStack_14f8) + fStack_15c8 * fStack_14e8) +
               fStack_1718 * fStack_15c8;
      fVar22 = (fVar8 * local_15d0 + fVar7 * local_1670) + fVar9 * local_15d0;
      fVar11 = (fVar8 * fStack_166c + fVar7 * fStack_15cc) + fVar9 * fStack_15cc;
      fVar12 = (fVar8 * fStack_15c8 + fVar7 * fStack_15c8) + fVar9 * fStack_1668;
      fVar13 = (fVar17 * local_15d0 + fVar15 * local_1670) + fVar19 * local_15d0;
      fVar14 = (fVar17 * fStack_166c + fVar15 * fStack_15cc) + fVar19 * fStack_15cc;
      fVar15 = (fVar17 * fStack_15c8 + fVar15 * fStack_15c8) + fVar19 * fStack_1668;
      local_1430 = (fVar21 * local_15d0 + fVar20 * local_1670) + fVar23 * local_15d0;
      fStack_142c = (fVar21 * fStack_166c + fVar20 * fStack_15cc) + fVar23 * fStack_15cc;
      fStack_1428 = (fVar21 * fStack_15c8 + fVar20 * fStack_15c8) + fVar23 * fStack_1668;
      fStack_1424 = (fVar21 * fStack_15c4 + fVar20 * fStack_15c4) + fVar23 * fStack_15c4;
      fVar7 = ((fVar16 * local_15d0 + fVar10 * local_1670) + fVar18 * local_15d0) +
              local_1720 * local_15d0;
      fVar8 = ((fVar16 * fStack_166c + fVar10 * fStack_15cc) + fVar18 * fStack_15cc) +
              fStack_171c * fStack_15cc;
      fVar9 = ((fVar16 * fStack_15c8 + fVar10 * fStack_15c8) + fVar18 * fStack_1668) +
              fStack_1718 * fStack_15c8;
      fStack_16b4 = pfVar2[4];
      local_16c0 = pfVar2[4];
      fStack_16bc = pfVar2[5];
      fStack_16b8 = pfVar2[6];
      fVar17 = (fVar11 * local_15d0 + fVar22 * local_1720) + fVar12 * local_15d0;
      fVar19 = (fVar11 * fStack_171c + fVar22 * fStack_15cc) + fVar12 * fStack_15cc;
      fVar20 = (fVar11 * fStack_15c8 + fVar22 * fStack_15c8) + fVar12 * fStack_1718;
      fVar18 = (fVar14 * local_15d0 + fVar13 * local_1720) + fVar15 * local_15d0;
      fVar22 = (fVar14 * fStack_171c + fVar13 * fStack_15cc) + fVar15 * fStack_15cc;
      fVar11 = (fVar14 * fStack_15c8 + fVar13 * fStack_15c8) + fVar15 * fStack_1718;
      fVar12 = (fStack_142c * local_15d0 + local_1430 * local_1720) + fStack_1428 * local_15d0;
      fVar13 = (fStack_142c * fStack_171c + local_1430 * fStack_15cc) + fStack_1428 * fStack_15cc;
      fVar14 = (fStack_142c * fStack_15c8 + local_1430 * fStack_15c8) + fStack_1428 * fStack_1718;
      fVar10 = ((fVar8 * local_15d0 + fVar7 * local_1720) + fVar9 * local_15d0) +
               local_1720 * local_16c0;
      fVar16 = ((fVar8 * fStack_171c + fVar7 * fStack_15cc) + fVar9 * fStack_15cc) +
               fStack_171c * fStack_16bc;
      fVar7 = ((fVar8 * fStack_15c8 + fVar7 * fStack_15c8) + fVar9 * fStack_1718) +
              fStack_1718 * fStack_16b8;
      local_1700 = (fVar19 * local_16a0 + fVar17 * local_16b0) + fVar20 * local_1690;
      fStack_16fc = (fVar19 * fStack_169c + fVar17 * fStack_16ac) + fVar20 * fStack_168c;
      fStack_16f8 = (fVar19 * fStack_1698 + fVar17 * fStack_16a8) + fVar20 * fStack_1688;
      fStack_16f4 = (fVar19 * fStack_1694 + fVar17 * fStack_16a4) + fVar20 * fStack_1684;
      local_16f0 = (fVar22 * local_16a0 + fVar18 * local_16b0) + fVar11 * local_1690;
      fStack_16ec = (fVar22 * fStack_169c + fVar18 * fStack_16ac) + fVar11 * fStack_168c;
      fStack_16e8 = (fVar22 * fStack_1698 + fVar18 * fStack_16a8) + fVar11 * fStack_1688;
      fStack_16e4 = (fVar22 * fStack_1694 + fVar18 * fStack_16a4) + fVar11 * fStack_1684;
      local_16e0 = (fVar13 * local_16a0 + fVar12 * local_16b0) + fVar14 * local_1690;
      fStack_16dc = (fVar13 * fStack_169c + fVar12 * fStack_16ac) + fVar14 * fStack_168c;
      fStack_16d8 = (fVar13 * fStack_1698 + fVar12 * fStack_16a8) + fVar14 * fStack_1688;
      fStack_16d4 = (fVar13 * fStack_1694 + fVar12 * fStack_16a4) + fVar14 * fStack_1684;
      local_16d0 = ((fVar16 * local_16a0 + fVar10 * local_16b0) + fVar7 * local_1690) +
                   local_1720 * local_1680;
      fStack_16cc = ((fVar16 * fStack_169c + fVar10 * fStack_16ac) + fVar7 * fStack_168c) +
                    fStack_171c * fStack_167c;
      fStack_16c8 = ((fVar16 * fStack_1698 + fVar10 * fStack_16a8) + fVar7 * fStack_1688) +
                    fStack_1718 * fStack_1678;
      fStack_16c4 = ((fVar16 * fStack_1694 + fVar10 * fStack_16a4) + fVar7 * fStack_1684) +
                    fStack_1714 * fStack_1674;
      iVar1 = *(int *)(param_2[2] + uVar6 * 4);
      fStack_14e4 = fStack_14e8;
      if ((DAT_01634380 == -1) || (DAT_01634380 == iVar1)) {
        (*DAT_01634378_s0079_6ed0)(iVar1,&local_1700,&local_172c,DAT_0163437c);
      }
      pfVar2 = (float *)(*param_1 + local_1730);
      fVar7 = *pfVar2;
      fVar8 = pfVar2[1];
      fVar9 = pfVar2[2];
      fVar10 = pfVar2[5];
      fStack_1630 = (fVar8 * local_16f0 + fVar7 * local_1700) + fVar9 * local_16e0;
      fStack_162c = (fVar8 * fStack_16ec + fVar7 * fStack_16fc) + fVar9 * fStack_16dc;
      fStack_1628 = (fVar8 * fStack_16e8 + fVar7 * fStack_16f8) + fVar9 * fStack_16d8;
      fStack_1624 = (fVar8 * fStack_16e4 + fVar7 * fStack_16f4) + fVar9 * fStack_16d4;
      fVar7 = pfVar2[4];
      fVar8 = pfVar2[6];
      fVar9 = pfVar2[8];
      fStack_1480 = (fVar10 * local_16f0 + fVar7 * local_1700) + fVar8 * local_16e0;
      fStack_147c = (fVar10 * fStack_16ec + fVar7 * fStack_16fc) + fVar8 * fStack_16dc;
      fStack_1478 = (fVar10 * fStack_16e8 + fVar7 * fStack_16f8) + fVar8 * fStack_16d8;
      fStack_1474 = (fVar10 * fStack_16e4 + fVar7 * fStack_16f4) + fVar8 * fStack_16d4;
      fVar7 = pfVar2[9];
      fVar8 = pfVar2[10];
      fVar10 = pfVar2[0xc];
      fStack_1470 = (fVar7 * local_16f0 + fVar9 * local_1700) + fVar8 * local_16e0;
      fStack_146c = (fVar7 * fStack_16ec + fVar9 * fStack_16fc) + fVar8 * fStack_16dc;
      fStack_1468 = (fVar7 * fStack_16e8 + fVar9 * fStack_16f8) + fVar8 * fStack_16d8;
      fStack_1464 = (fVar7 * fStack_16e4 + fVar9 * fStack_16f4) + fVar8 * fStack_16d4;
      fVar7 = pfVar2[0xd];
      fVar8 = pfVar2[0xe];
      fStack_15b0 = ((fVar7 * local_16f0 + fVar10 * local_1700) + fVar8 * local_16e0) +
                    local_1720 * local_16d0;
      fStack_15ac = ((fVar7 * fStack_16ec + fVar10 * fStack_16fc) + fVar8 * fStack_16dc) +
                    fStack_171c * fStack_16cc;
      fStack_15a8 = ((fVar7 * fStack_16e8 + fVar10 * fStack_16f8) + fVar8 * fStack_16d8) +
                    fStack_1718 * fStack_16c8;
      fStack_15a4 = ((fVar7 * fStack_16e4 + fVar10 * fStack_16f4) + fVar8 * fStack_16d4) +
                    fStack_1714 * fStack_16c4;
      fStack_1610 = fStack_1480;
      fStack_160c = fStack_147c;
      fStack_1608 = fStack_1478;
      fStack_1604 = fStack_1474;
      fStack_1660 = fStack_1470;
      fStack_165c = fStack_146c;
      fStack_1658 = fStack_1468;
      fStack_1654 = fStack_1464;
      if (param_6 != (float *)0x0) {
        fVar7 = *param_6;
        fVar8 = param_6[1];
        fVar9 = param_6[2];
        fStack_14d0 = (fVar8 * fStack_1480 + fVar7 * fStack_1630) + fVar9 * fStack_1470;
        fStack_14cc = (fVar8 * fStack_147c + fVar7 * fStack_162c) + fVar9 * fStack_146c;
        fStack_14c8 = (fVar8 * fStack_1478 + fVar7 * fStack_1628) + fVar9 * fStack_1468;
        fStack_14c4 = (fVar8 * fStack_1474 + fVar7 * fStack_1624) + fVar9 * fStack_1464;
        fVar7 = param_6[5];
        fVar8 = param_6[4];
        fVar9 = param_6[6];
        fStack_14c0 = (fVar7 * fStack_1480 + fVar8 * fStack_1630) + fVar9 * fStack_1470;
        fStack_14bc = (fVar7 * fStack_147c + fVar8 * fStack_162c) + fVar9 * fStack_146c;
        fStack_14b8 = (fVar7 * fStack_1478 + fVar8 * fStack_1628) + fVar9 * fStack_1468;
        fStack_14b4 = (fVar7 * fStack_1474 + fVar8 * fStack_1624) + fVar9 * fStack_1464;
        fVar7 = param_6[9];
        fVar8 = param_6[8];
        fVar9 = param_6[10];
        fStack_14b0 = (fVar7 * fStack_1480 + fVar8 * fStack_1630) + fVar9 * fStack_1470;
        fStack_14ac = (fVar7 * fStack_147c + fVar8 * fStack_162c) + fVar9 * fStack_146c;
        fStack_14a8 = (fVar7 * fStack_1478 + fVar8 * fStack_1628) + fVar9 * fStack_1468;
        fStack_14a4 = (fVar7 * fStack_1474 + fVar8 * fStack_1624) + fVar9 * fStack_1464;
        fVar7 = param_6[0xd];
        fVar8 = param_6[0xc];
        fVar9 = param_6[0xe];
        fStack_15b0 = ((fVar7 * fStack_1480 + fVar8 * fStack_1630) + fVar9 * fStack_1470) +
                      local_1720 * fStack_15b0;
        fStack_15ac = ((fVar7 * fStack_147c + fVar8 * fStack_162c) + fVar9 * fStack_146c) +
                      fStack_171c * fStack_15ac;
        fStack_15a8 = ((fVar7 * fStack_1478 + fVar8 * fStack_1628) + fVar9 * fStack_1468) +
                      fStack_1718 * fStack_15a8;
        fStack_15a4 = ((fVar7 * fStack_1474 + fVar8 * fStack_1624) + fVar9 * fStack_1464) +
                      fStack_1714 * fStack_15a4;
        fStack_1630 = fStack_14d0;
        fStack_162c = fStack_14cc;
        fStack_1628 = fStack_14c8;
        fStack_1624 = fStack_14c4;
        fStack_1610 = fStack_14c0;
        fStack_160c = fStack_14bc;
        fStack_1608 = fStack_14b8;
        fStack_1604 = fStack_14b4;
        fStack_1660 = fStack_14b0;
        fStack_165c = fStack_14ac;
        fStack_1658 = fStack_14a8;
        fStack_1654 = fStack_14a4;
      }
      iVar1 = *param_2;
      pfVar5[8] = fStack_1628;
      pfVar5[1] = fStack_1610;
      pfVar5[5] = fStack_160c;
      pfVar5[9] = fStack_1608;
      pfVar5[2] = fStack_1660;
      pfVar5[6] = fStack_165c;
      pfVar5[10] = fStack_1658;
      pfVar5[3] = fStack_15b0;
      *pfVar5 = fStack_1630;
      pfVar5[7] = fStack_15ac;
      pfVar5[4] = fStack_162c;
      pfVar5[0xb] = fStack_15a8;
      uVar3 = *(unsigned int *)(iVar1 + uVar6 * 4) & 3;
      if (uVar3 == 0) {
        fStack_15c0 = local_172c;
        fStack_15bc = local_1728;
        fStack_15b8 = local_1724;
        fStack_15b4 = local_172c;
        fStack_15e0 = local_172c;
        fStack_15dc = local_1728;
        fStack_15d8 = local_1724;
        fStack_15d4 = local_172c;
        fStack_1600 = local_172c;
        fStack_15fc = local_1728;
        fStack_15f8 = local_1724;
        fStack_15f4 = local_172c;
LAB_007979e3:
        fStack_1674 = fStack_16c4;
        fStack_1678 = fStack_16c8;
        fStack_167c = fStack_16cc;
        local_1680 = local_16d0;
        fStack_1684 = fStack_16d4;
        fStack_1688 = fStack_16d8;
        fStack_168c = fStack_16dc;
        local_1690 = local_16e0;
        fStack_1694 = fStack_16e4;
        fStack_1698 = fStack_16e8;
        fStack_169c = fStack_16ec;
        local_16a0 = local_16f0;
        fStack_16a4 = fStack_16f4;
        fStack_16a8 = fStack_16f8;
        fStack_16ac = fStack_16fc;
        local_16b0 = local_1700;
        fStack_166c = 1.0 / local_1728;
        local_1670 = 1.0 / local_172c;
        fStack_1668 = 1.0 / local_1724;
        pfVar2 = pfVar4;
        fStack_1664 = fStack_1668;
      }
      else if (uVar3 == 1) {
        local_16b0 = pfVar4[-0x10];
        fStack_16ac = pfVar4[-0xf];
        fStack_16a8 = pfVar4[-0xe];
        fStack_16a4 = pfVar4[-0xd];
        pfVar2 = pfVar4 + -0x10;
        local_16a0 = pfVar4[-0xc];
        fStack_169c = pfVar4[-0xb];
        fStack_1698 = pfVar4[-10];
        fStack_1694 = pfVar4[-9];
        local_1690 = pfVar4[-8];
        fStack_168c = pfVar4[-7];
        fStack_1688 = pfVar4[-6];
        fStack_1684 = pfVar4[-5];
        local_1680 = pfVar4[-4];
        fStack_167c = pfVar4[-3];
        fStack_1678 = pfVar4[-2];
        fStack_1674 = pfVar4[-1];
        local_1670 = local_1734[-4];
        fStack_166c = local_1734[-3];
        fStack_1668 = local_1734[-2];
        fStack_1664 = local_1734[-1];
        local_1734 = local_1734 + -4;
      }
      else {
        pfVar2 = pfVar4;
        if (uVar3 == 2) {
          pfVar4[8] = local_1690;
          pfVar4[9] = fStack_168c;
          pfVar4[10] = fStack_1688;
          pfVar4[0xb] = fStack_1684;
          pfVar4[0xc] = local_1680;
          pfVar4[0xd] = fStack_167c;
          pfVar4[0xe] = fStack_1678;
          pfVar4[0xf] = fStack_1674;
          *pfVar4 = local_16b0;
          pfVar4[1] = fStack_16ac;
          pfVar4[2] = fStack_16a8;
          pfVar4[3] = fStack_16a4;
          pfVar4[4] = local_16a0;
          pfVar4[5] = fStack_169c;
          pfVar4[6] = fStack_1698;
          pfVar4[7] = fStack_1694;
          *local_1734 = local_1670;
          local_1734[1] = fStack_166c;
          local_1734[2] = fStack_1668;
          local_1734[3] = fStack_1664;
          pfVar4 = pfVar4 + 0x10;
          local_1734 = local_1734 + 4;
          fStack_1620 = local_172c;
          fStack_161c = local_1728;
          fStack_1618 = local_1724;
          fStack_1614 = local_172c;
          fStack_1640 = local_172c;
          fStack_163c = local_1728;
          fStack_1638 = local_1724;
          fStack_1634 = local_172c;
          fStack_1650 = local_172c;
          fStack_164c = local_1728;
          fStack_1648 = local_1724;
          fStack_1644 = local_172c;
          goto LAB_007979e3;
        }
      }
      local_1730 = local_1730 + 0x40;
      uVar6 = uVar6 + 1;
      pfVar5 = pfVar5 + 0xc;
      pfVar4 = pfVar2;
      fStack_15f0 = fStack_1610;
      fStack_15ec = fStack_160c;
      fStack_15e8 = fStack_1608;
      fStack_15e4 = fStack_1604;
      fStack_1590 = fStack_15b0;
      fStack_158c = fStack_15ac;
      fStack_1588 = fStack_15a8;
      fStack_1584 = fStack_15a4;
      fStack_1570 = fStack_1630;
      fStack_156c = fStack_162c;
      fStack_1568 = fStack_1628;
      fStack_1564 = fStack_1624;
      fStack_1560 = fStack_15b0;
      fStack_155c = fStack_15ac;
      fStack_1558 = fStack_15a8;
      fStack_1554 = fStack_15a4;
      fStack_1550 = fStack_1660;
      fStack_154c = fStack_165c;
      fStack_1548 = fStack_1658;
      fStack_1544 = fStack_1654;
      fStack_1540 = fStack_1630;
      fStack_153c = fStack_162c;
      fStack_1538 = fStack_1628;
      fStack_1534 = fStack_1624;
      fStack_1530 = fStack_1660;
      fStack_152c = fStack_165c;
      fStack_1528 = fStack_1658;
      fStack_1524 = fStack_1654;
      fStack_1520 = fStack_1610;
      fStack_151c = fStack_160c;
      fStack_1518 = fStack_1608;
      fStack_1514 = fStack_1604;
    } while (uVar6 < local_1704);
  }
  return 1;
}

// @ 0x00797a20
int FUN_00797a20(int *param_1,int *param_2,int param_3,int *param_4,float *param_5,float *param_6, int param_7)
{
  int iVar1;
  float fVar2;
  float fVar3;
  float *pfVar4;
  unsigned int uVar5;
  float *pfVar6;
  float *pfVar7;
  float *pfVar8;
  float *pfVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  float local_1830;
  float local_182c;
  float local_1828;
  int local_1824;
  float *local_17f0;
  int local_17e0;
  float local_17c0;
  float local_17bc;
  float local_17b8;
  float local_17b4;
  float local_17b0;
  float local_17ac;
  float local_17a8;
  float local_17a4;
  float local_1798;
  float local_1794;
  float local_1790;
  int uStack_178c;
  int uStack_1788;
  int uStack_1784;
  float fStack_1780;
  float fStack_177c;
  float fStack_1778;
  int local_1774;
  float local_1770;
  float fStack_176c;
  float fStack_1768;
  float fStack_1764;
  float local_1760;
  float fStack_175c;
  float fStack_1758;
  float fStack_1754;
  float local_1750;
  float fStack_174c;
  float fStack_1748;
  float fStack_1744;
  float local_1740;
  float fStack_173c;
  float fStack_1738;
  float fStack_1734;
  float local_1730;
  float fStack_172c;
  float fStack_1728;
  float fStack_1724;
  float local_1720;
  float fStack_171c;
  float fStack_1718;
  float fStack_1714;
  float local_1710;
  float fStack_170c;
  float fStack_1708;
  float fStack_1704;
  float local_1700;
  float fStack_16fc;
  float fStack_16f8;
  float fStack_16f4;
  float local_16f0;
  float fStack_16ec;
  float fStack_16e8;
  float fStack_16e4;
  float local_16e0;
  float fStack_16dc;
  float fStack_16d8;
  float fStack_16d4;
  float local_16d0;
  float fStack_16cc;
  float fStack_16c8;
  float fStack_16c4;
  float local_16b0;
  float fStack_16ac;
  float fStack_16a8;
  float fStack_16a4;
  float local_16a0;
  float fStack_169c;
  float fStack_1698;
  float fStack_1694;
  float fStack_1680;
  float fStack_167c;
  float fStack_1678;
  float fStack_1674;
  float fStack_1670;
  float fStack_166c;
  float fStack_1668;
  float fStack_1664;
  float local_1660;
  float fStack_165c;
  float fStack_1658;
  float fStack_1654;
  float local_1650;
  float fStack_164c;
  float fStack_1648;
  float fStack_1644;
  float fStack_1640;
  float fStack_163c;
  float fStack_1638;
  float fStack_1634;
  float local_1630;
  float fStack_162c;
  float fStack_1628;
  float fStack_1624;
  float fStack_1620;
  float fStack_161c;
  float fStack_1618;
  float fStack_1614;
  float local_1610;
  float fStack_160c;
  float fStack_1608;
  int uStack_1604;
  float fStack_1600;
  float fStack_15fc;
  float fStack_15f8;
  float fStack_15f4;
  float fStack_15f0;
  float fStack_15ec;
  float fStack_15e8;
  float fStack_15e4;
  float fStack_15e0;
  float fStack_15dc;
  float fStack_15d8;
  float fStack_15d4;
  float fStack_15d0;
  float fStack_15cc;
  float fStack_15c8;
  float fStack_15c4;
  float fStack_15c0;
  float fStack_15bc;
  float fStack_15b8;
  float fStack_15b4;
  float fStack_15b0;
  float fStack_15ac;
  float fStack_15a8;
  float fStack_15a4;
  float fStack_15a0;
  float fStack_159c;
  float fStack_1598;
  float fStack_1594;
  float fStack_1590;
  float fStack_158c;
  float fStack_1588;
  float fStack_1584;
  float fStack_1580;
  float fStack_157c;
  float fStack_1578;
  float fStack_1574;
  float fStack_1570;
  float fStack_156c;
  float fStack_1568;
  float fStack_1564;
  float fStack_1560;
  float fStack_155c;
  float fStack_1558;
  float fStack_1554;
  float local_1540;
  float fStack_153c;
  float fStack_1538;
  float fStack_1534;
  float local_1530;
  float fStack_152c;
  float fStack_1528;
  float fStack_1524;
  float local_1500;
  float fStack_14fc;
  float fStack_14f8;
  float fStack_14f4;
  float local_14f0;
  float fStack_14ec;
  float fStack_14e8;
  float fStack_14e4;
  float local_14c0;
  float fStack_14bc;
  float fStack_14b8;
  float fStack_14b4;
  float local_14b0;
  float fStack_14ac;
  float fStack_14a8;
  float fStack_14a4;
  float local_1480;
  float fStack_147c;
  float fStack_1478;
  float fStack_1474;
  float local_1470;
  float fStack_146c;
  float fStack_1468;
  float fStack_1464;
  float local_1440;
  float fStack_143c;
  float fStack_1438;
  float fStack_1434;
  float local_1430;
  float fStack_142c;
  float fStack_1428;
  float fStack_1424;
  float local_1400;
  float fStack_13fc;
  float fStack_13f8;
  float fStack_13f4;
  float local_13f0;
  float fStack_13ec;
  float fStack_13e8;
  float fStack_13e4;
  float fStack_13c0;
  float fStack_13bc;
  float fStack_13b8;
  float fStack_13b4;
  float fStack_13b0;
  float fStack_13ac;
  float fStack_13a8;
  float fStack_13a4;
  float local_1370;
  float fStack_136c;
  float fStack_1368;
  float fStack_1364;
  float local_1330;
  float fStack_132c;
  float fStack_1328;
  float fStack_1324;
  float local_1304 [205];
  float local_fd0 [1007];
  int uStack_14;
  
  uStack_14 = 0x797a30;
  local_1770 = *param_5;
  fStack_176c = param_5[1];
  fStack_1768 = param_5[2];
  fStack_1764 = param_5[3];
  local_1774 = *(int *)(param_3 + 0x14);
  local_1760 = param_5[4];
  fStack_175c = param_5[5];
  fStack_1758 = param_5[6];
  fStack_1754 = param_5[7];
  local_1750 = param_5[8];
  fStack_174c = param_5[9];
  fStack_1748 = param_5[10];
  fStack_1744 = param_5[0xb];
  local_1740 = param_5[0xc];
  fStack_173c = param_5[0xd];
  fStack_1738 = param_5[0xe];
  fStack_1734 = param_5[0xf];
  local_1830 = 1.0;
  local_182c = 1.0;
  local_1828 = 1.0;
  local_1824 = 0;
  if (0 < local_1774) {
    local_1630 = 1.4142135;
    fStack_162c = 1.4142135;
    fStack_1628 = 1.4142135;
    fStack_1624 = 1.4142135;
    pfVar7 = (float *)(*param_4 + 8);
    local_1610 = 0.5;
    fStack_160c = 0.5;
    fStack_1608 = 0.5;
    uStack_1604 = 0x3f000000;
    local_17f0 = (float *)(param_7 + 0x24);
    local_1650 = 0.0;
    fStack_164c = 0.0;
    fStack_1648 = 0.0;
    fStack_1644 = 0.0;
    local_16d0 = 1.0;
    fStack_16cc = 1.0;
    fStack_16c8 = 1.0;
    fStack_16c4 = 1.0;
    local_17e0 = 0;
    pfVar6 = local_1304;
    pfVar8 = local_fd0;
    do {
      if (*(int *)(param_3 + 0x10) == 0x30) {
        pfVar4 = (float *)FUN_011fda50(local_1824);
        fVar11 = *pfVar4;
        fVar13 = pfVar4[1];
        fVar15 = pfVar4[2];
        fVar16 = pfVar4[3];
        local_17c0 = pfVar4[4];
        local_17bc = pfVar4[5];
        local_17b8 = pfVar4[6];
        local_17b4 = pfVar4[7];
        local_17b0 = pfVar4[8];
        local_17ac = pfVar4[9];
        local_17a8 = pfVar4[10];
        local_17a4 = pfVar4[0xb];
      }
      else {
        pfVar4 = (float *)FUN_011fda50(local_1824);
        fVar11 = *pfVar4;
        fVar13 = pfVar4[1];
        fVar15 = pfVar4[2];
        fVar16 = pfVar4[3];
        local_17c0 = pfVar4[4];
        local_17bc = pfVar4[5];
        local_17b8 = pfVar4[6];
        fStack_1664 = pfVar4[7];
        uStack_178c = 0x3f800000;
        uStack_1788 = 0x3f800000;
        uStack_1784 = 0x3f800000;
        local_17b4 = 1.0;
        local_17b0 = 1.0;
        local_17ac = 1.0;
        fStack_1780 = local_17c0;
        fStack_177c = local_17bc;
        fStack_1778 = local_17b8;
        fStack_1670 = local_17c0;
        fStack_166c = local_17bc;
        fStack_1668 = local_17b8;
        fStack_15c0 = local_17c0;
        fStack_15bc = local_17bc;
        fStack_15b8 = local_17b8;
        fStack_15b4 = fStack_1664;
        fStack_15a0 = local_17c0;
        fStack_159c = local_17bc;
        fStack_1598 = local_17b8;
        fStack_1594 = fStack_1664;
      }
      fVar17 = local_17f0[-5];
      fVar18 = local_17f0[-4];
      fVar19 = local_17f0[-3];
      fVar10 = local_17f0[-2];
      local_16e0 = (fVar19 * fVar13 - fVar18 * fVar15) + (fVar10 * fVar11 + fVar16 * fVar17);
      fStack_16dc = (fVar17 * fVar15 - fVar19 * fVar11) + (fVar10 * fVar13 + fVar16 * fVar18);
      fStack_16d8 = (fVar18 * fVar11 - fVar17 * fVar13) + (fVar10 * fVar15 + fVar16 * fVar19);
      fStack_16d4 = (fVar17 * fVar11 - fVar17 * fVar11) + (fVar10 * fVar11 + fVar16 * fVar17);
      local_17ac = local_17f0[1] * local_17ac;
      local_17b4 = local_17f0[-1] * local_17b4;
      local_17b0 = local_17b0 * *local_17f0;
      fVar10 = local_1630 * local_16e0;
      fVar12 = fStack_162c * fStack_16dc;
      fVar14 = fStack_1628 * fStack_16d8;
      fVar15 = fStack_1624 *
               (fVar16 * local_17f0[-2] - ((fVar19 * fVar15 + fVar18 * fVar13) + fVar17 * fVar11));
      fVar16 = (local_1650 - fVar10) * fVar10 + local_1610;
      fVar17 = (fStack_164c - fVar12) * fVar12 + fStack_160c;
      fVar18 = (fStack_1648 - fVar14) * fVar14 + fStack_1608;
      fVar11 = fVar15 * fVar14 + fVar12 * fVar10;
      fVar13 = fVar15 * fVar10 + fVar14 * fVar12;
      local_1370 = fVar15 * fVar12 + fVar10 * fVar14;
      fVar20 = fVar12 * fVar10 - fVar15 * fVar14;
      fStack_136c = fVar14 * fVar12 - fVar15 * fVar10;
      fVar12 = fVar10 * fVar14 - fVar15 * fVar12;
      fStack_1368 = fVar17 + fVar16;
      fVar17 = fVar18 + fVar17;
      fVar16 = fVar16 + fVar18;
      fVar10 = (local_17b4 * fVar17 + fStack_164c * fVar20) + fStack_1648 * local_1370;
      fVar18 = (local_17b4 * fVar11 + fStack_164c * fVar16) + fStack_1648 * fStack_136c;
      fVar19 = (local_17b4 * fVar12 + fStack_164c * fVar13) + fStack_1648 * fStack_1368;
      local_16b0 = (local_1650 * fVar17 + local_17b0 * fVar20) + fStack_1648 * local_1370;
      fStack_16ac = (local_1650 * fVar11 + local_17b0 * fVar16) + fStack_1648 * fStack_136c;
      fStack_16a8 = (local_1650 * fVar12 + local_17b0 * fVar13) + fStack_1648 * fStack_1368;
      fStack_16a4 = (local_1650 * fVar20 + local_17b0 * fVar11) + fStack_1648 * fStack_1368;
      local_16a0 = (local_1650 * fVar17 + fStack_164c * fVar20) + local_17ac * local_1370;
      fStack_169c = (local_1650 * fVar11 + fStack_164c * fVar16) + local_17ac * fStack_136c;
      fStack_1698 = (local_1650 * fVar12 + fStack_164c * fVar13) + local_17ac * fStack_1368;
      fStack_1694 = (local_1650 * fVar20 + fStack_164c * fVar11) + local_17ac * fStack_1368;
      fVar15 = ((fStack_164c * fVar20 + local_1650 * fVar17) + fStack_1648 * local_1370) +
               local_1650 * local_16d0;
      fVar11 = ((fStack_164c * fVar16 + local_1650 * fVar11) + fStack_1648 * fStack_136c) +
               fStack_164c * fStack_16cc;
      fVar13 = ((fStack_164c * fVar13 + local_1650 * fVar12) + fStack_1648 * fStack_1368) +
               fStack_1648 * fStack_16c8;
      if (*(char *)(local_17f0 + 5) == '\0') {
        fVar16 = (fVar18 * local_1650 + fVar10 * local_1830) + fVar19 * local_1650;
        fVar17 = (fVar18 * local_182c + fVar10 * fStack_164c) + fVar19 * fStack_164c;
        fVar10 = (fVar18 * fStack_1648 + fVar10 * fStack_1648) + fVar19 * local_1828;
        local_1480 = (fStack_16ac * local_1650 + local_16b0 * local_1830) + fStack_16a8 * local_1650
        ;
        fStack_147c = (fStack_16ac * local_182c + local_16b0 * fStack_164c) +
                      fStack_16a8 * fStack_164c;
        fStack_1478 = (fStack_16ac * fStack_1648 + local_16b0 * fStack_1648) +
                      fStack_16a8 * local_1828;
        fStack_1474 = (fStack_16ac * fStack_1644 + local_16b0 * fStack_1644) +
                      fStack_16a8 * fStack_1644;
        local_1470 = (fStack_169c * local_1650 + local_16a0 * local_1830) + fStack_1698 * local_1650
        ;
        fStack_146c = (fStack_169c * local_182c + local_16a0 * fStack_164c) +
                      fStack_1698 * fStack_164c;
        fStack_1468 = (fStack_169c * fStack_1648 + local_16a0 * fStack_1648) +
                      fStack_1698 * local_1828;
        fStack_1464 = (fStack_169c * fStack_1644 + local_16a0 * fStack_1644) +
                      fStack_1698 * fStack_1644;
        fVar12 = ((fVar11 * local_1650 + fVar15 * local_1830) + fVar13 * local_1650) +
                 local_1650 * local_16d0;
        fVar14 = ((fVar11 * local_182c + fVar15 * fStack_164c) + fVar13 * fStack_164c) +
                 fStack_164c * fStack_16cc;
        fVar20 = ((fVar11 * fStack_1648 + fVar15 * fStack_1648) + fVar13 * local_1828) +
                 fStack_1648 * fStack_16c8;
        fVar22 = (fVar17 * local_1650 + fVar16 * local_16d0) + fVar10 * local_1650;
        fVar23 = (fVar17 * fStack_16cc + fVar16 * fStack_164c) + fVar10 * fStack_164c;
        fVar24 = (fVar17 * fStack_1648 + fVar16 * fStack_1648) + fVar10 * fStack_16c8;
        fVar11 = (fStack_147c * local_1650 + local_1480 * local_16d0) + fStack_1478 * local_1650;
        fVar13 = (fStack_147c * fStack_16cc + local_1480 * fStack_164c) + fStack_1478 * fStack_164c;
        fVar15 = (fStack_147c * fStack_1648 + local_1480 * fStack_1648) + fStack_1478 * fStack_16c8;
        fStack_1434 = (fStack_147c * fStack_1644 + local_1480 * fStack_1644) +
                      fStack_1478 * fStack_1644;
        fVar16 = (fStack_146c * local_1650 + local_1470 * local_16d0) + fStack_1468 * local_1650;
        fVar17 = (fStack_146c * fStack_16cc + local_1470 * fStack_164c) + fStack_1468 * fStack_164c;
        fVar19 = (fStack_146c * fStack_1648 + local_1470 * fStack_1648) + fStack_1468 * fStack_16c8;
        fStack_1424 = (fStack_146c * fStack_1644 + local_1470 * fStack_1644) +
                      fStack_1468 * fStack_1644;
        fVar10 = ((fVar14 * local_1650 + fVar12 * local_16d0) + fVar20 * local_1650) +
                 (local_17f0[2] * (local_17f0[-9] + local_17c0)) * local_16d0;
        fVar18 = ((fVar14 * fStack_16cc + fVar12 * fStack_164c) + fVar20 * fStack_164c) +
                 (local_17f0[3] * (local_17f0[-8] + local_17bc)) * fStack_16cc;
        fVar12 = ((fVar14 * fStack_1648 + fVar12 * fStack_1648) + fVar20 * fStack_16c8) +
                 (local_17f0[4] * (local_17f0[-7] + local_17b8)) * fStack_16c8;
        local_1440 = fVar11;
        fStack_143c = fVar13;
        fStack_1438 = fVar15;
        local_1430 = fVar16;
        fStack_142c = fVar17;
        fStack_1428 = fVar19;
      }
      else {
        fVar16 = local_17f0[0x1b];
        fVar17 = local_17f0[0x1d];
        fVar12 = local_17f0[0x1c];
        fVar14 = (fVar18 * local_1650 + fVar10 * fVar16) + fVar19 * local_1650;
        fVar20 = (fVar18 * fVar12 + fVar10 * fStack_164c) + fVar19 * fStack_164c;
        fVar10 = (fVar18 * fStack_1648 + fVar10 * fStack_1648) + fVar19 * fVar17;
        local_1540 = (fStack_16ac * local_1650 + local_16b0 * fVar16) + fStack_16a8 * local_1650;
        fStack_153c = (fStack_16ac * fVar12 + local_16b0 * fStack_164c) + fStack_16a8 * fStack_164c;
        fStack_1538 = (fStack_16ac * fStack_1648 + local_16b0 * fStack_1648) + fStack_16a8 * fVar17;
        fStack_1534 = (fStack_16ac * fStack_1644 + local_16b0 * fStack_1644) +
                      fStack_16a8 * fStack_1644;
        local_1530 = (fStack_169c * local_1650 + local_16a0 * fVar16) + fStack_1698 * local_1650;
        fStack_152c = (fStack_169c * fVar12 + local_16a0 * fStack_164c) + fStack_1698 * fStack_164c;
        fStack_1528 = (fStack_169c * fStack_1648 + local_16a0 * fStack_1648) + fStack_1698 * fVar17;
        fStack_1524 = (fStack_169c * fStack_1644 + local_16a0 * fStack_1644) +
                      fStack_1698 * fStack_1644;
        fVar18 = ((fVar11 * local_1650 + fVar15 * fVar16) + fVar13 * local_1650) +
                 local_1650 * local_16d0;
        fVar19 = ((fVar11 * fVar12 + fVar15 * fStack_164c) + fVar13 * fStack_164c) +
                 fStack_164c * fStack_16cc;
        fVar17 = ((fVar11 * fStack_1648 + fVar15 * fStack_1648) + fVar13 * fVar17) +
                 fStack_1648 * fStack_16c8;
        fVar22 = (fVar20 * local_1650 + fVar14 * local_16d0) + fVar10 * local_1650;
        fVar23 = (fVar20 * fStack_16cc + fVar14 * fStack_164c) + fVar10 * fStack_164c;
        local_16f0 = (fVar20 * fStack_1648 + fVar14 * fStack_1648) + fVar10 * fStack_16c8;
        fVar12 = (fStack_153c * local_1650 + local_1540 * local_16d0) + fStack_1538 * local_1650;
        fVar14 = (fStack_153c * fStack_16cc + local_1540 * fStack_164c) + fStack_1538 * fStack_164c;
        fVar20 = (fStack_153c * fStack_1648 + local_1540 * fStack_1648) + fStack_1538 * fStack_16c8;
        local_1660 = local_1650;
        fStack_165c = fStack_164c;
        fStack_1658 = fStack_16c8;
        fStack_1654 = fStack_1644;
        local_1330 = (fStack_152c * local_1650 + local_1530 * local_16d0) + fStack_1528 * local_1650
        ;
        fStack_132c = (fStack_152c * fStack_16cc + local_1530 * fStack_164c) +
                      fStack_1528 * fStack_164c;
        fStack_1328 = (fStack_152c * fStack_1648 + local_1530 * fStack_1648) +
                      fStack_1528 * fStack_16c8;
        fStack_1324 = (fStack_152c * fStack_1644 + local_1530 * fStack_1644) +
                      fStack_1528 * fStack_1644;
        fVar11 = local_17f0[0xf];
        fVar13 = local_17f0[0x10];
        fVar15 = local_17f0[0x11];
        fVar16 = ((fVar19 * local_1650 + fVar18 * local_16d0) + fVar17 * local_1650) +
                 (local_17f0[-9] + local_17c0) * local_16d0;
        fVar10 = ((fVar19 * fStack_16cc + fVar18 * fStack_164c) + fVar17 * fStack_164c) +
                 (local_17f0[-8] + local_17bc) * fStack_16cc;
        fVar17 = ((fVar19 * fStack_1648 + fVar18 * fStack_1648) + fVar17 * fStack_16c8) +
                 (local_17f0[-7] + local_17b8) * fStack_16c8;
        fVar18 = (fVar22 * local_17f0[0xb] + fVar23 * fVar11) + local_16f0 * local_17f0[0x13];
        fVar19 = (fVar22 * local_17f0[0xc] + fVar23 * fVar13) + local_16f0 * local_17f0[0x14];
        fVar22 = (fVar22 * local_17f0[0xd] + fVar23 * fVar15) + local_16f0 * local_17f0[0x15];
        local_14c0 = (fVar12 * local_17f0[0xb] + fVar14 * fVar11) + fVar20 * local_17f0[0x13];
        fStack_14bc = (fVar12 * local_17f0[0xc] + fVar14 * fVar13) + fVar20 * local_17f0[0x14];
        fStack_14b8 = (fVar12 * local_17f0[0xd] + fVar14 * fVar15) + fVar20 * local_17f0[0x15];
        fStack_14b4 = (fVar12 * local_17f0[0xe] + fVar14 * local_17f0[0x12]) +
                      fVar20 * local_17f0[0x16];
        local_14b0 = (local_1330 * local_17f0[0xb] + fStack_132c * fVar11) +
                     fStack_1328 * local_17f0[0x13];
        fStack_14ac = (local_1330 * local_17f0[0xc] + fStack_132c * fVar13) +
                      fStack_1328 * local_17f0[0x14];
        fStack_14a8 = (local_1330 * local_17f0[0xd] + fStack_132c * fVar15) +
                      fStack_1328 * local_17f0[0x15];
        fStack_14a4 = (local_1330 * local_17f0[0xe] + fStack_132c * local_17f0[0x12]) +
                      fStack_1328 * local_17f0[0x16];
        fVar11 = ((fVar16 * local_17f0[0xb] + fVar10 * fVar11) + fVar17 * local_17f0[0x13]) +
                 local_17f0[0x17] * local_16d0;
        fVar13 = ((fVar16 * local_17f0[0xc] + fVar10 * fVar13) + fVar17 * local_17f0[0x14]) +
                 local_17f0[0x18] * fStack_16cc;
        fVar15 = ((fVar16 * local_17f0[0xd] + fVar10 * fVar15) + fVar17 * local_17f0[0x15]) +
                 local_17f0[0x19] * fStack_16c8;
        fVar16 = (fVar19 * local_1650 + fVar18 * local_1830) + fVar22 * local_1650;
        fVar10 = (fVar19 * local_182c + fVar18 * fStack_164c) + fVar22 * fStack_164c;
        fVar17 = (fVar19 * fStack_1648 + fVar18 * fStack_1648) + fVar22 * local_1828;
        local_1500 = (fStack_14bc * local_1650 + local_14c0 * local_1830) + fStack_14b8 * local_1650
        ;
        fStack_14fc = (fStack_14bc * local_182c + local_14c0 * fStack_164c) +
                      fStack_14b8 * fStack_164c;
        fStack_14f8 = (fStack_14bc * fStack_1648 + local_14c0 * fStack_1648) +
                      fStack_14b8 * local_1828;
        fStack_14f4 = (fStack_14bc * fStack_1644 + local_14c0 * fStack_1644) +
                      fStack_14b8 * fStack_1644;
        local_14f0 = (fStack_14ac * local_1650 + local_14b0 * local_1830) + fStack_14a8 * local_1650
        ;
        fStack_14ec = (fStack_14ac * local_182c + local_14b0 * fStack_164c) +
                      fStack_14a8 * fStack_164c;
        fStack_14e8 = (fStack_14ac * fStack_1648 + local_14b0 * fStack_1648) +
                      fStack_14a8 * local_1828;
        fStack_14e4 = (fStack_14ac * fStack_1644 + local_14b0 * fStack_1644) +
                      fStack_14a8 * fStack_1644;
        fVar12 = ((fVar13 * local_1650 + fVar11 * local_1830) + fVar15 * local_1650) +
                 local_1650 * local_16d0;
        fVar14 = ((fVar13 * local_182c + fVar11 * fStack_164c) + fVar15 * fStack_164c) +
                 fStack_164c * fStack_16cc;
        fVar20 = ((fVar13 * fStack_1648 + fVar11 * fStack_1648) + fVar15 * local_1828) +
                 fStack_1648 * fStack_16c8;
        fVar22 = (fVar10 * local_1650 + fVar16 * local_16d0) + fVar17 * local_1650;
        fVar23 = (fVar10 * fStack_16cc + fVar16 * fStack_164c) + fVar17 * fStack_164c;
        fVar24 = (fVar10 * fStack_1648 + fVar16 * fStack_1648) + fVar17 * fStack_16c8;
        fVar11 = (fStack_14fc * local_1650 + local_1500 * local_16d0) + fStack_14f8 * local_1650;
        fVar13 = (fStack_14fc * fStack_16cc + local_1500 * fStack_164c) + fStack_14f8 * fStack_164c;
        fVar15 = (fStack_14fc * fStack_1648 + local_1500 * fStack_1648) + fStack_14f8 * fStack_16c8;
        fStack_13f4 = (fStack_14fc * fStack_1644 + local_1500 * fStack_1644) +
                      fStack_14f8 * fStack_1644;
        fVar16 = (fStack_14ec * local_1650 + local_14f0 * local_16d0) + fStack_14e8 * local_1650;
        fVar17 = (fStack_14ec * fStack_16cc + local_14f0 * fStack_164c) + fStack_14e8 * fStack_164c;
        fVar19 = (fStack_14ec * fStack_1648 + local_14f0 * fStack_1648) + fStack_14e8 * fStack_16c8;
        fStack_13e4 = (fStack_14ec * fStack_1644 + local_14f0 * fStack_1644) +
                      fStack_14e8 * fStack_1644;
        fVar10 = ((fVar14 * local_1650 + fVar12 * local_16d0) + fVar20 * local_1650) +
                 local_17f0[6] * local_16d0;
        fVar18 = ((fVar14 * fStack_16cc + fVar12 * fStack_164c) + fVar20 * fStack_164c) +
                 local_17f0[7] * fStack_16cc;
        fVar12 = ((fVar14 * fStack_1648 + fVar12 * fStack_1648) + fVar20 * fStack_16c8) +
                 local_17f0[8] * fStack_16c8;
        fStack_16ec = local_16f0;
        fStack_16e8 = local_16f0;
        fStack_16e4 = local_16f0;
        local_1400 = fVar11;
        fStack_13fc = fVar13;
        fStack_13f8 = fVar15;
        local_13f0 = fVar16;
        fStack_13ec = fVar17;
        fStack_13e8 = fVar19;
      }
      local_1730 = (fVar23 * local_1760 + fVar22 * local_1770) + fVar24 * local_1750;
      fStack_172c = (fVar23 * fStack_175c + fVar22 * fStack_176c) + fVar24 * fStack_174c;
      fStack_1728 = (fVar23 * fStack_1758 + fVar22 * fStack_1768) + fVar24 * fStack_1748;
      fStack_1724 = (fVar23 * fStack_1754 + fVar22 * fStack_1764) + fVar24 * fStack_1744;
      local_1720 = (fVar13 * local_1760 + fVar11 * local_1770) + fVar15 * local_1750;
      fStack_171c = (fVar13 * fStack_175c + fVar11 * fStack_176c) + fVar15 * fStack_174c;
      fStack_1718 = (fVar13 * fStack_1758 + fVar11 * fStack_1768) + fVar15 * fStack_1748;
      fStack_1714 = (fVar13 * fStack_1754 + fVar11 * fStack_1764) + fVar15 * fStack_1744;
      local_1710 = (fVar17 * local_1760 + fVar16 * local_1770) + fVar19 * local_1750;
      fStack_170c = (fVar17 * fStack_175c + fVar16 * fStack_176c) + fVar19 * fStack_174c;
      fStack_1708 = (fVar17 * fStack_1758 + fVar16 * fStack_1768) + fVar19 * fStack_1748;
      fStack_1704 = (fVar17 * fStack_1754 + fVar16 * fStack_1764) + fVar19 * fStack_1744;
      local_1700 = ((fVar18 * local_1760 + fVar10 * local_1770) + fVar12 * local_1750) +
                   local_1740 * local_16d0;
      fStack_16fc = ((fVar18 * fStack_175c + fVar10 * fStack_176c) + fVar12 * fStack_174c) +
                    fStack_173c * fStack_16cc;
      fStack_16f8 = ((fVar18 * fStack_1758 + fVar10 * fStack_1768) + fVar12 * fStack_1748) +
                    fStack_1738 * fStack_16c8;
      fStack_16f4 = ((fVar18 * fStack_1754 + fVar10 * fStack_1764) + fVar12 * fStack_1744) +
                    fStack_1734 * fStack_16c4;
      iVar1 = *(int *)(param_2[2] + local_1824 * 4);
      local_1798 = local_17b4;
      local_1794 = local_17b0;
      local_1790 = local_17ac;
      fStack_1364 = fStack_1368;
      if ((DAT_01634380 == -1) || (DAT_01634380 == iVar1)) {
        (*DAT_01634378_s0079_7a20)(iVar1,&local_1730,&local_17b4,DAT_0163437c);
      }
      pfVar4 = (float *)(*param_1 + local_17e0);
      fVar11 = pfVar4[6];
      fVar13 = *pfVar4;
      fVar15 = pfVar4[1];
      fVar16 = pfVar4[2];
      fVar10 = pfVar4[4];
      fVar17 = (fVar15 * local_1720 + fVar13 * local_1730) + fVar16 * local_1710;
      fVar18 = (fVar15 * fStack_171c + fVar13 * fStack_172c) + fVar16 * fStack_170c;
      fVar19 = (fVar15 * fStack_1718 + fVar13 * fStack_1728) + fVar16 * fStack_1708;
      fVar12 = (fVar15 * fStack_1714 + fVar13 * fStack_1724) + fVar16 * fStack_1704;
      fVar13 = pfVar4[5];
      fVar15 = pfVar4[9];
      fVar14 = (fVar13 * local_1720 + fVar10 * local_1730) + fVar11 * local_1710;
      fVar20 = (fVar13 * fStack_171c + fVar10 * fStack_172c) + fVar11 * fStack_170c;
      fVar22 = (fVar13 * fStack_1718 + fVar10 * fStack_1728) + fVar11 * fStack_1708;
      fVar10 = (fVar13 * fStack_1714 + fVar10 * fStack_1724) + fVar11 * fStack_1704;
      fVar11 = pfVar4[8];
      fVar13 = pfVar4[10];
      fVar16 = pfVar4[0xd];
      fVar23 = (fVar15 * local_1720 + fVar11 * local_1730) + fVar13 * local_1710;
      fVar24 = (fVar15 * fStack_171c + fVar11 * fStack_172c) + fVar13 * fStack_170c;
      fVar21 = (fVar15 * fStack_1718 + fVar11 * fStack_1728) + fVar13 * fStack_1708;
      fVar15 = (fVar15 * fStack_1714 + fVar11 * fStack_1724) + fVar13 * fStack_1704;
      fVar11 = pfVar4[0xc];
      fVar13 = pfVar4[0xe];
      fStack_15e0 = ((fVar16 * local_1720 + fVar11 * local_1730) + fVar13 * local_1710) +
                    local_1700 * local_16d0;
      fStack_15dc = ((fVar16 * fStack_171c + fVar11 * fStack_172c) + fVar13 * fStack_170c) +
                    fStack_16fc * fStack_16cc;
      fStack_15d8 = ((fVar16 * fStack_1718 + fVar11 * fStack_1728) + fVar13 * fStack_1708) +
                    fStack_16f8 * fStack_16c8;
      fStack_15d4 = ((fVar16 * fStack_1714 + fVar11 * fStack_1724) + fVar13 * fStack_1704) +
                    fStack_16f4 * fStack_16c4;
      fStack_1640 = fVar17;
      fStack_163c = fVar18;
      fStack_1638 = fVar19;
      fStack_1634 = fVar12;
      fStack_1680 = fVar14;
      fStack_167c = fVar20;
      fStack_1678 = fVar22;
      fStack_1674 = fVar10;
      fStack_1620 = fVar23;
      fStack_161c = fVar24;
      fStack_1618 = fVar21;
      fStack_1614 = fVar15;
      if (param_6 != (float *)0x0) {
        fVar11 = *param_6;
        fVar13 = param_6[1];
        fVar16 = param_6[2];
        fVar2 = param_6[4];
        fVar3 = param_6[5];
        fStack_1640 = (fVar11 * fVar17 + fVar13 * fVar14) + fVar16 * fVar23;
        fStack_163c = (fVar11 * fVar18 + fVar13 * fVar20) + fVar16 * fVar24;
        fStack_1638 = (fVar11 * fVar19 + fVar13 * fVar22) + fVar16 * fVar21;
        fStack_1634 = (fVar11 * fVar12 + fVar13 * fVar10) + fVar16 * fVar15;
        fVar11 = param_6[6];
        fStack_1680 = (fVar2 * fVar17 + fVar3 * fVar14) + fVar11 * fVar23;
        fStack_167c = (fVar2 * fVar18 + fVar3 * fVar20) + fVar11 * fVar24;
        fStack_1678 = (fVar2 * fVar19 + fVar3 * fVar22) + fVar11 * fVar21;
        fStack_1674 = (fVar2 * fVar12 + fVar3 * fVar10) + fVar11 * fVar15;
        fVar11 = param_6[8];
        fVar13 = param_6[9];
        fVar16 = param_6[10];
        fStack_1620 = (fVar11 * fVar17 + fVar13 * fVar14) + fVar16 * fVar23;
        fStack_161c = (fVar11 * fVar18 + fVar13 * fVar20) + fVar16 * fVar24;
        fStack_1618 = (fVar11 * fVar19 + fVar13 * fVar22) + fVar16 * fVar21;
        fStack_1614 = (fVar11 * fVar12 + fVar13 * fVar10) + fVar16 * fVar15;
        fVar11 = param_6[0xc];
        fVar13 = param_6[0xd];
        fVar16 = param_6[0xe];
        fStack_15e0 = ((fVar11 * fVar17 + fVar13 * fVar14) + fVar16 * fVar23) +
                      fStack_15e0 * local_16d0;
        fStack_15dc = ((fVar11 * fVar18 + fVar13 * fVar20) + fVar16 * fVar24) +
                      fStack_15dc * fStack_16cc;
        fStack_15d8 = ((fVar11 * fVar19 + fVar13 * fVar22) + fVar16 * fVar21) +
                      fStack_15d8 * fStack_16c8;
        fStack_15d4 = ((fVar11 * fVar12 + fVar13 * fVar10) + fVar16 * fVar15) +
                      fStack_15d4 * fStack_16c4;
        fStack_13c0 = fStack_1680;
        fStack_13bc = fStack_167c;
        fStack_13b8 = fStack_1678;
        fStack_13b4 = fStack_1674;
        fStack_13b0 = fStack_1620;
        fStack_13ac = fStack_161c;
        fStack_13a8 = fStack_1618;
        fStack_13a4 = fStack_1614;
      }
      iVar1 = *param_2;
      pfVar7[-2] = fStack_1640;
      pfVar7[-1] = fStack_1680;
      *pfVar7 = fStack_1620;
      pfVar7[1] = fStack_15e0;
      pfVar7[2] = fStack_163c;
      pfVar7[3] = fStack_167c;
      pfVar7[4] = fStack_161c;
      pfVar7[5] = fStack_15dc;
      pfVar7[6] = fStack_1638;
      pfVar7[7] = fStack_1678;
      pfVar7[8] = fStack_1618;
      pfVar7[9] = fStack_15d8;
      uVar5 = *(unsigned int *)(iVar1 + local_1824 * 4) & 3;
      if (uVar5 == 0) {
LAB_00798c60:
        local_1770 = local_1730;
        fStack_176c = fStack_172c;
        fStack_1768 = fStack_1728;
        fStack_1764 = fStack_1724;
        local_1760 = local_1720;
        fStack_175c = fStack_171c;
        fStack_1758 = fStack_1718;
        fStack_1754 = fStack_1714;
        local_1750 = local_1710;
        fStack_174c = fStack_170c;
        fStack_1748 = fStack_1708;
        fStack_1744 = fStack_1704;
        pfVar4 = pfVar6;
        pfVar9 = pfVar8;
        local_1830 = 1.0 / local_17b4;
        local_182c = 1.0 / local_17b0;
        local_1828 = 1.0 / local_17ac;
        local_1740 = local_1700;
        fStack_173c = fStack_16fc;
        fStack_1738 = fStack_16f8;
        fStack_1734 = fStack_16f4;
      }
      else if (uVar5 == 1) {
        local_1770 = pfVar8[-0x10];
        fStack_176c = pfVar8[-0xf];
        fStack_1768 = pfVar8[-0xe];
        fStack_1764 = pfVar8[-0xd];
        local_1830 = pfVar6[-3];
        pfVar9 = pfVar8 + -0x10;
        pfVar4 = pfVar6 + -3;
        local_1760 = pfVar8[-0xc];
        fStack_175c = pfVar8[-0xb];
        fStack_1758 = pfVar8[-10];
        fStack_1754 = pfVar8[-9];
        local_182c = pfVar6[-2];
        local_1750 = pfVar8[-8];
        fStack_174c = pfVar8[-7];
        fStack_1748 = pfVar8[-6];
        fStack_1744 = pfVar8[-5];
        local_1740 = pfVar8[-4];
        fStack_173c = pfVar8[-3];
        fStack_1738 = pfVar8[-2];
        fStack_1734 = pfVar8[-1];
        local_1828 = pfVar6[-1];
      }
      else {
        pfVar4 = pfVar6;
        pfVar9 = pfVar8;
        if (uVar5 == 2) {
          *pfVar8 = local_1770;
          pfVar8[1] = fStack_176c;
          pfVar8[2] = fStack_1768;
          pfVar8[3] = fStack_1764;
          *pfVar6 = local_1830;
          pfVar8[4] = local_1760;
          pfVar8[5] = fStack_175c;
          pfVar8[6] = fStack_1758;
          pfVar8[7] = fStack_1754;
          pfVar6[1] = local_182c;
          pfVar8[8] = local_1750;
          pfVar8[9] = fStack_174c;
          pfVar8[10] = fStack_1748;
          pfVar8[0xb] = fStack_1744;
          pfVar8[0xc] = local_1740;
          pfVar8[0xd] = fStack_173c;
          pfVar8[0xe] = fStack_1738;
          pfVar8[0xf] = fStack_1734;
          pfVar6[2] = local_1828;
          pfVar8 = pfVar8 + 0x10;
          pfVar6 = pfVar6 + 3;
          goto LAB_00798c60;
        }
      }
      local_17e0 = local_17e0 + 0x40;
      local_1824 = local_1824 + 1;
      local_17f0 = local_17f0 + 0x28;
      pfVar7 = pfVar7 + 0xc;
      pfVar6 = pfVar4;
      pfVar8 = pfVar9;
      fStack_1600 = fStack_1640;
      fStack_15fc = fStack_163c;
      fStack_15f8 = fStack_1638;
      fStack_15f4 = fStack_1634;
      fStack_15f0 = fStack_1620;
      fStack_15ec = fStack_161c;
      fStack_15e8 = fStack_1618;
      fStack_15e4 = fStack_1614;
      fStack_15d0 = fStack_15e0;
      fStack_15cc = fStack_15dc;
      fStack_15c8 = fStack_15d8;
      fStack_15c4 = fStack_15d4;
      fStack_15b0 = fStack_1680;
      fStack_15ac = fStack_167c;
      fStack_15a8 = fStack_1678;
      fStack_15a4 = fStack_1674;
      fStack_1590 = fStack_1640;
      fStack_158c = fStack_163c;
      fStack_1588 = fStack_1638;
      fStack_1584 = fStack_1634;
      fStack_1580 = fStack_15e0;
      fStack_157c = fStack_15dc;
      fStack_1578 = fStack_15d8;
      fStack_1574 = fStack_15d4;
      fStack_1570 = fStack_1620;
      fStack_156c = fStack_161c;
      fStack_1568 = fStack_1618;
      fStack_1564 = fStack_1614;
      fStack_1560 = fStack_1680;
      fStack_155c = fStack_167c;
      fStack_1558 = fStack_1678;
      fStack_1554 = fStack_1674;
    } while (local_1824 < local_1774);
  }
  return 1;
}

// @ 0x00798d30
void FUN_00798d30(int param_1, int *param_2)
{
    int iVar1;
    char *puVar2;

    if (param_1 == 0) {
        param_1 = param_2[2];
    }
    puVar2 = (char *)0x0;
    if (DAT_01634384 != 0) {
        puVar2 = (char *)DAT_01634330;
    }
    iVar1 = *param_2;
    if (DAT_01634370 == 0) {
        if (*(int *)(iVar1 + 0x10) == 0x30) {
            FUN_00796ed0();
        } else {
            FUN_00796910((int *)param_2[4], (int *)param_2[3], iVar1, param_1,
                         DAT_016342f0, puVar2);
        }
    } else {
        FUN_00797a20((int *)param_2[4], (int *)param_2[3], iVar1, param_1,
                     DAT_016342f0, puVar2, DAT_01634370, DAT_01634374);
    }
    DAT_01634384 = 0;
    DAT_01634370 = 0;
    DAT_01634374 = 0;
    DAT_0163437c = 0;
    DAT_01634380 = 0;
    DAT_016342f0[0] = 1.0f;
    DAT_016342f0[1] = 0.0f;
    DAT_016342f0[2] = 0.0f;
    DAT_016342f0[3] = 0.0f;
    DAT_016342f0[4] = 0.0f;
    DAT_016342f0[5] = 1.0f;
    DAT_016342f0[6] = 0.0f;
    DAT_016342f0[7] = 0.0f;
    DAT_016342f0[8] = 0.0f;
    DAT_016342f0[9] = 0.0f;
    DAT_016342f0[10] = 1.0f;
    DAT_016342f0[11] = 0.0f;
    DAT_016342f0[12] = 0.0f;
    DAT_016342f0[13] = 0.0f;
    DAT_016342f0[14] = 0.0f;
    DAT_016342f0[15] = 0.0f;
    DAT_01634378_s0079_8d30 = (int (*)(...)) & FUN_00c2e4e0;
    return;
}

// @ 0x007990e0
void Mgr::Notify(int param)
{
    VObj **puVar1;

    puVar1 = *(VObj ***)((char *)this + 0xc);
    if (puVar1 != *(VObj ***)((char *)this + 0x10)) {
        do {
            (*puVar1)->f1(param);
            puVar1 = puVar1 + 1;
        } while (puVar1 != *(VObj ***)((char *)this + 0x10));
    }
    return;
}

// @ 0x00799320
void FUN_00799320(float *param_1, float *param_2)
{
    float fVar5 = (float)(1.0 / sqrt(((double)param_2[0] * param_2[0] + (double)param_2[1] * param_2[1]) +
                                     ((double)param_2[2] * param_2[2] + (double)param_2[3] * param_2[3])));
    *param_1 = param_2[0] * fVar5;
    param_1[1] = param_2[1] * fVar5;
    param_1[2] = fVar5 * param_2[2];
    param_1[3] = fVar5 * param_2[3];
    return;
}

// @ 0x007997f0
VCtor *VCtor::c0(int *param_2)
{
    int *param_1 = (int *)this;
    param_1[0] = (int)&V_13ebc60;
    param_1[1] = 0;
    param_1[2] = 4;
    *(float *)(param_1 + 3) = *(float *)param_2;
    *(float *)(param_1 + 4) = *(float *)(param_2 + 1);
    *(float *)(param_1 + 5) = *(float *)(param_2 + 2);
    *(float *)(param_1 + 6) = *(float *)(param_2 + 3);
    _ReadWriteBarrier();
    param_1[0] = (int)&V_140f558;
    param_1[7] = 1;
    return this;
}

// @ 0x00799840
int *AllocThing::alloc(int param_2, int param_3)
{
    int *param_1 = (int *)this;
    int iVar1;
    (void)param_3;
    if (param_2 != 0) {
        iVar1 = FUN_00f473a0(param_2 * 2, "Graphics", 0, 0,
                             "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                             0xd1);
        param_1[0] = iVar1;
        param_1[1] = iVar1;
        param_1[2] = iVar1 + param_2 * 2;
        return param_1;
    }
    param_1[0] = 0;
    param_1[1] = 0;
    param_1[2] = 0;
    return param_1;
}

// @ 0x007998a0
long double PlaneQ::IntersectRay(float *param_2, float *param_3)
{
    return ((long double)d -
            ((long double)x * (long double)*param_2 +
            ((long double)y * (long double)param_2[1] + (long double)z * (long double)param_2[2]))) /
            ((long double)z * (long double)(param_3[2] - param_2[2]) +
            ((long double)y * (long double)(param_3[1] - param_2[1]) +
            (long double)x * (long double)(*param_3 - *param_2)));
}

// @ 0x00799940
VCtor *VCtor::c1(int *param_2)
{
    int *param_1 = (int *)this;
    param_1[0] = (int)&V_13ebc60;
    param_1[1] = 0;
    param_1[2] = 4;
    *(float *)(param_1 + 3) = *(float *)param_2;
    *(float *)(param_1 + 4) = *(float *)(param_2 + 1);
    *(float *)(param_1 + 5) = *(float *)(param_2 + 2);
    *(float *)(param_1 + 6) = *(float *)(param_2 + 3);
    *(float *)(param_1 + 7) = *(float *)(param_2 + 4);
    *(float *)(param_1 + 8) = *(float *)(param_2 + 5);
    *(float *)(param_1 + 9) = *(float *)(param_2 + 6);
    _ReadWriteBarrier();
    param_1[0] = (int)&V_140f560;
    param_1[10] = 1;
    return this;
}

// @ 0x007999a0
long double CylinderQ::Intersect(float *param_2, float *param_3)
{
    float fVar7 = *param_2 - ox;
    float fVar8 = param_2[1] - oy;
    float fVar9 = param_2[2] - oz;
    float fVar10 = *param_3 - ox;
    float fVar11 = param_3[1] - oy;
    float fVar12 = param_3[2] - oz;
    float fVar5 = (dz * fVar9 + dy * fVar8) + dx * fVar7;
    float fVar6 = (dz * fVar12 + dy * fVar11) + dx * fVar10;
    float fVar1 = (fVar9 - dz * fVar5);
    float fVar2 = (fVar8 - dy * fVar5);
    float fVar3 = (fVar7 - dx * fVar5);
    double dVar1 = ABS(sqrt((double)fVar3 * fVar3 + (double)fVar2 * fVar2 + (double)fVar1 * fVar1) -
                       sqrt((double)radiusSq));
    float fVar4 = (fVar12 - dz * fVar6);
    float fVar13 = (fVar11 - dy * fVar6);
    float fVar14 = (fVar10 - fVar6 * dx);
    return (long double)dVar1 /
           (ABS(sqrt((double)fVar4 * fVar4 + (double)fVar13 * fVar13 + (double)fVar14 * fVar14) -
                sqrt((double)radiusSq)) + (double)dVar1);
}

// @ 0x00799b00
VCtor *VCtor::c2(int *param_2)
{
    int *param_1 = (int *)this;
    param_1[0] = (int)&V_13ebc60;
    param_1[1] = 0;
    param_1[2] = 4;
    *(float *)(param_1 + 3) = *(float *)param_2;
    *(float *)(param_1 + 4) = *(float *)(param_2 + 1);
    *(float *)(param_1 + 5) = *(float *)(param_2 + 2);
    *(float *)(param_1 + 6) = *(float *)(param_2 + 3);
    _ReadWriteBarrier();
    param_1[0] = (int)&V_140f568;
    param_1[7] = 1;
    return this;
}

// @ 0x00799b50
long double RayQ::IntersectRay(float *param_2, float *param_3)
{
    float fVar11 = param_3[2] - param_2[2];
    float fVar9 = *param_3 - *param_2;
    float fVar10 = param_3[1] - param_2[1];
    float fVar6 = param_2[2] - oz;
    float fVar7 = *param_2 - ox;
    float fVar8 = param_2[1] - oy;
    long double fVar5 = (long double)1 / sqrt((long double)((long double)fVar10 * fVar10 +
                          ((long double)fVar9 * fVar9 + (long double)fVar11 * fVar11)));
    long double fVar1 = (long double)(((fVar6 * fVar11 + fVar7 * fVar9) + fVar8 * fVar10) * (float)fVar5);
    return (-fVar1 - sqrt(fVar1 * fVar1 -
                         (((long double)fVar7 * fVar7 + ((long double)fVar8 * fVar8 +
                         (long double)fVar6 * fVar6)) - (long double)radiusSq))) * fVar5;
}

// @ 0x00799c30
VCtor *VCtor::c3(int *param_2)
{
    int *param_1 = (int *)this;
    param_1[0] = (int)&V_13ebc60;
    param_1[1] = 0;
    param_1[2] = 4;
    *(float *)(param_1 + 3) = *(float *)param_2;
    *(float *)(param_1 + 4) = *(float *)(param_2 + 1);
    *(float *)(param_1 + 5) = *(float *)(param_2 + 2);
    *(float *)(param_1 + 6) = *(float *)(param_2 + 3);
    _ReadWriteBarrier();
    param_1[0] = (int)&V_140f570;
    return this;
}

// @ 0x00799c70
VCtor *VCtor::c4(int *param_2)
{
    int *param_1 = (int *)this;
    param_1[0] = (int)&V_13ebc60;
    param_1[1] = 0;
    param_1[2] = 4;
    *(float *)(param_1 + 3) = *(float *)param_2;
    *(float *)(param_1 + 4) = *(float *)(param_2 + 1);
    *(float *)(param_1 + 5) = *(float *)(param_2 + 2);
    *(float *)(param_1 + 6) = *(float *)(param_2 + 3);
    *(float *)(param_1 + 7) = *(float *)(param_2 + 4);
    *(float *)(param_1 + 8) = *(float *)(param_2 + 5);
    *(float *)(param_1 + 9) = *(float *)(param_2 + 6);
    _ReadWriteBarrier();
    param_1[0] = (int)&V_140f578;
    return this;
}

// @ 0x0079b020
RecVec::RecVec(const RecVec& x)
{
    int n = (int)(x.mpEnd - x.mpBegin);
    UShortVecRec* p = n ? (UShortVecRec*)DoAlloc(n * 0x14) : 0;
    mpBegin = p;
    mpEnd = p;
    mpCapacity = p + n;
    UShortVecRec* res = 0;
    UninitCopyRecs(&res, x.mpBegin, x.mpEnd, p, &x);
    mpEnd = res;
}

// @ 0x0079b0d0
void __stdcall DestroyRecs(UShortVecRec* first, UShortVecRec* last)
{
    for (; first < last; ++first)
        first->~UShortVecRec();
}

// @ 0x0079b150
UShortVecDst* UShortVecDst::Assign(const UShortVecSrc& x)
{
    DoCreate((int)(x.mpEnd - x.mpBegin), (void*)&x.mAllocState);
    int bytes = (int)((char*)x.mpEnd - (char*)x.mpBegin);
    mpEnd = (uint16_t*)memcpy(mpBegin, x.mpBegin, bytes) + (bytes >> 1);
    return this;
}

// @ 0x0079b1c0
UShortVecRec** __cdecl UninitCopyRecs2(UShortVecRec** out, UShortVecRec* first, UShortVecRec* last, UShortVecRec* dest)
{
    *out = dest;
    for (; first != last; ++first) {
        UShortVecRec* cur = *out;
        if (cur)
            new (cur) UShortVecRec(*first);
        *out = *out + 1;
    }
    return out;
}

// @ 0x0079b2a0
void __cdecl UninitFillRecs(UShortVecRec* dest, unsigned n, const UShortVecRec& x)
{
    for (; n > 0; --n, ++dest) {
        if (dest)
            new (dest) UShortVecRec(x);
    }
}

// @ 0x0079b4b0
void SplitCtx::AddVertex(int sub, int i)
{
    mVerts.push_back(Rec16(sub, i, 0, 0.0f));
}

// @ 0x0079b520
void SplitCtx::AddEdge(int sub, int i, int j, float t)
{
    mVerts.push_back(Rec16(sub, i, j, t));
}

// @ 0x0079b590
void SplitCtx::AddIndex(uint16_t v)
{
    mpIndexSets[mCur.mIdx].push_back(v);
}

// @ 0x0079b5d0
void SplitCtx::FinishGroup()
{
    UShortVec& set = mpIndexSets[mCur.mIdx];
    mCur.mSize = (int)(set.mpEnd - set.mpBegin);
    if (mCur.mLimit < mCur.mSize)
        mpParent->mGroups.push_back(mCur);
}

// @ 0x0079b630
void SplitOuter::Flush(int a, int idx, int unused0, int unused1, int extra)
{
    mCtx.FinishGroup();
    UShortVec& set = mpSets[idx];
    mCur.mSize = (int)(set.mpEnd - set.mpBegin);
    if (mCur.mLimit < mCur.mSize) {
        mCur.mA = a;
        mCur.mIdx = idx;
        mCur.mExtra = extra;
        mpParent->mGroups.push_back(mCur);
    }
}

// @ 0x0079b6b0
void __cdecl CompileSplitModelElement(PairVec* out, SubmeshRef* ref)
{
    PtrVec meshes;
    meshes.mpBegin = 0;
    meshes.mpEnd = 0;
    meshes.mpCapacity = 0;
    meshes.reserve(((ModelHdr*)ref->mpModel)->mRecords.size());
    CompileToRwMeshes(ref->mpModel, 0, &meshes, 0, 0, 0, 0, 0, -1);
    int count = (int)(meshes.mpEnd - meshes.mpBegin);
    for (int i = 0; i < count; ++i) {
        PairRec r;
        r.mA = meshes.mpBegin[i];
        r.mB = ref->mVal;
        if (out->mpEnd < out->mpCapacity) {
            PairRec* p = out->mpEnd;
            out->mpEnd = p + 1;
            if (p) *p = r;
        } else
            out->DoInsertValue(out->mpEnd, r);
    }
}

// @ 0x0079b7b0
void SplitPlane::SplitTriangles(SplitModel* model, SplitRange* rng, UShortVec* out, SplitCtx* ctx)
{
    int streamSel = FindStream(model, 1, 0, 3, 0xe);
    VertStream* vs = (VertStream*)((char*)model->mpStreams + streamSel * 0x20 + 0x10);
    IndexBuf* ib = model->mpIndexBufs + rng->mSub;
    int i = rng->mStart;
    if (i >= rng->mEnd)
        return;
    do {
        uint32_t i0, i1, i2;
        if (ib->mpRemapBegin == ib->mpRemapEnd) {
            uint32_t mask = g_IndexMask[ib->mFormat];
            uint32_t stride = ib->mStride;
            i0 = *(uint32_t*)(stride * i + ib->mpData) & mask;
            i1 = *(uint32_t*)(stride * (i + 1) + ib->mpData) & mask;
            i2 = *(uint32_t*)(stride * (i + 2) + ib->mpData) & mask;
        } else {
            uint32_t mask = g_IndexMask[ib->mFormat];
            const Remap* r = (const Remap*)((char*)ib->mpRemapBegin + *(int16_t*)(ib->mpRemapSel + 2 + streamSel * 4) * 0x10);
            uint32_t stride = ib->mStride;
            i0 = *(uint32_t*)((*(uint32_t*)(stride * i + ib->mpData) & mask) * r->mStride + r->mpData) & g_IndexMask[r->mFormat];
            i1 = *(uint32_t*)((*(uint32_t*)(stride * (i + 1) + ib->mpData) & mask) * r->mStride + r->mpData) & g_IndexMask[r->mFormat];
            i2 = *(uint32_t*)((*(uint32_t*)(stride * (i + 2) + ib->mpData) & mask) * r->mStride + r->mpData) & g_IndexMask[r->mFormat];
        }
        const float* v0 = (const float*)(vs->mStride * i0 + vs->mpData);
        const float* v1 = (const float*)(vs->mStride * i1 + vs->mpData);
        const float* v2 = (const float*)(vs->mStride * i2 + vs->mpData);
        int s0 = ((mEq.z * v0[2] + mEq.y * v0[1] + mEq.x * v0[0]) > mEq.d) == mSide;
        int s1 = ((mEq.z * v1[2] + mEq.y * v1[1] + mEq.x * v1[0]) > mEq.d) == mSide;
        int s2 = ((mEq.z * v2[2] + mEq.y * v2[1] + mEq.x * v2[0]) > mEq.d) == mSide;
        int sum = s1 + s2 + s0;
        uint16_t first;
        if (sum % 3 == 0) {
            if (s0 == sum % 3)
                goto next;
            first = FetchIndex16(ib, i);
            goto emit;
        }
        switch (mMode) {
        case 0:
            first = FetchIndex16(ib, i);
            goto emit;
        case 2:
            if (sum > 1) {
                first = FetchIndex16(ib, i);
                goto emit;
            }
            goto next;
        case 3: {
            int sub = rng->mSub;
            uint32_t base = (uint32_t)(ctx->mVerts.mpEnd - ctx->mVerts.mpBegin);
            uint16_t b16 = (uint16_t)base;
            if (s0 == 0) {
                if (s1 == 0) {
                    ctx->AddEdge(sub, i + 2, i, mEq.Intersect(v2, v0));
                    ctx->AddEdge(sub, i + 2, i + 1, mEq.Intersect(v2, v1));
                    ctx->AddVertex(sub, i + 2);
                } else {
                    ctx->AddEdge(sub, i + 1, i, mEq.Intersect(v1, v0));
                    ctx->AddVertex(sub, i + 1);
                    if (s2 == 0) {
                        ctx->AddEdge(sub, i + 1, i + 2, mEq.Intersect(v1, v2));
                    } else {
                        ctx->AddVertex(sub, i + 2);
                        ctx->AddEdge(sub, i + 2, i, mEq.Intersect(v2, v0));
                    }
                }
            } else {
                ctx->AddVertex(sub, i);
                if (s1 == 0) {
                    ctx->AddEdge(sub, i, i + 1, mEq.Intersect(v0, v1));
                    if (s2 != 0) {
                        ctx->AddEdge(sub, i + 2, i + 1, mEq.Intersect(v2, v1));
                        ctx->AddVertex(sub, i + 2);
                    } else {
                        ctx->AddEdge(sub, i, i + 2, mEq.Intersect(v0, v2));
                    }
                } else {
                    ctx->AddVertex(sub, i + 1);
                    ctx->AddEdge(sub, i + 1, i + 2, mEq.Intersect(v1, v2));
                    ctx->AddEdge(sub, i, i + 2, mEq.Intersect(v0, v2));
                }
            }
            ctx->AddIndex(b16);
            ctx->AddIndex((uint16_t)(base + 1));
            ctx->AddIndex((uint16_t)(base + 2));
            if (sum > 1) {
                ctx->AddIndex(b16);
                ctx->AddIndex((uint16_t)(base + 2));
                ctx->AddIndex((uint16_t)(base + 3));
            }
            goto next;
        }
        default:
            goto next;
        }
    emit:
        out->push_back(first);
        out->push_back(FetchIndex16(ib, i + 1));
        out->push_back(FetchIndex16(ib, i + 2));
    next:
        i += 3;
    } while (i < rng->mEnd);
}

// @ 0x0079bfa0
void CylinderClipper::Run(Mesh* mesh, Job* job, UShortVec_s0079_bfa0* out, Out* clip)
{
    int sidx = FUN_0071ddc0(mesh, 1, 0, 3, 0xe);
    IndexStream* ib = (IndexStream*)(mesh->indexStreams + job->stream * 0x8c);
    Stream* vs = (Stream*)(mesh->streams + sidx * 0x20 + 0x10);
    int sIdx = job->stream;

    if (job->start < job->end) {
        int a = job->start;
        do {
            int b = a + 1;
            int c = a + 2;
            uint ia, ib_, ic;
            if (ib->remapBegin == ib->remapEnd) {
                ia = ib->Read(a);
                ib_ = ib->Read(b);
                ic = ib->Read(c);
            } else {
                Stream* rm = (Stream*)((char*)ib->remapBegin + *(short*)(ib->table + sidx * 4 + 2) * 0x10);
                ia = rm->Read(ib->Read(a));
                ib_ = rm->Read(ib->Read(b));
                ic = rm->Read(ib->Read(c));
            }
            const float* pA = (const float*)(vs->data + vs->stride * ia);
            const float* pB = (const float*)(vs->data + vs->stride * ib_);
            const float* pC = (const float*)(vs->data + vs->stride * ic);
            int bA = cyl.Bit(pA, keep);
            int bB = cyl.Bit(pB, keep);
            int bC = cyl.Bit(pC, keep);
            int sum = bA + bB + bC;

            if (sum == (sum / 3) * 3) {
                // all bits clear (0) or all set (3): only the all-set triangles are copied
                if (bA != sum % 3)
                    PushRaw3(out, ib, a);
            } else {
                switch (mode) {
                case 0:
                    PushRaw3(out, ib, a);
                    break;
                case 1:
                    break;
                case 2:
                    if (sum > 1)
                        PushRaw3(out, ib, a);
                    break;
                case 3: {
                    uint n = (uint)(clip->f8 - clip->f4) & 0xffff;
                    if (bA == 0) {
                        if (bB == 0) {
                            clip->AddLerp(sIdx, c, a, cyl.Intersect(pC, pA));
                            clip->AddLerp(sIdx, c, b, cyl.Intersect(pC, pB));
                            clip->AddVert(sIdx, c);
                        } else {
                            clip->AddLerp(sIdx, b, a, cyl.Intersect(pB, pA));
                            clip->AddVert(sIdx, b);
                            if (bC == 0) {
                                clip->AddLerp(sIdx, b, c, cyl.Intersect(pB, pC));
                            } else {
                                clip->AddVert(sIdx, c);
                                clip->AddLerp(sIdx, c, a, cyl.Intersect(pC, pA));
                            }
                        }
                    } else {
                        clip->AddVert(sIdx, a);
                        if (bB == 0) {
                            clip->AddLerp(sIdx, a, b, cyl.Intersect(pA, pB));
                            if (bC != 0) {
                                clip->AddLerp(sIdx, c, b, cyl.Intersect(pC, pB));
                                clip->AddVert(sIdx, c);
                            } else {
                                clip->AddLerp(sIdx, a, c, cyl.Intersect(pA, pC));
                            }
                        } else {
                            clip->AddVert(sIdx, b);
                            clip->AddLerp(sIdx, b, c, cyl.Intersect(pB, pC));
                            clip->AddLerp(sIdx, a, c, cyl.Intersect(pA, pC));
                        }
                    }
                    UShortVec_s0079_bfa0* iv = clip->IdxVec();
                    iv->push_back((ushort)n);
                    iv->push_back((ushort)(n + 1));
                    iv->push_back((ushort)(n + 2));
                    if (sum > 1) {
                        iv = clip->IdxVec();
                        iv->push_back((ushort)n);
                        iv->push_back((ushort)(n + 2));
                        iv->push_back((ushort)(n + 3));
                    }
                    break;
                }
                }
            }
            a += 3;
        } while (a < job->end);
    }
}

// @ 0x0079c960
void __thiscall Clipper::Run(Mesh_s0079_c960* mesh, TriRange* range, UShortVec_s0079_c960* out, ClipOut* co)
{
  int e = FindElement(mesh, 1, 0, 3, 14);
  Packed* pos = &mesh->elemBegin[e].packed;
  Stream_s0079_c960* s = &mesh->streams[range->stream];
  for (int i = range->start; i < range->end; i += 3) {
    uint32_t i0, i1, i2;
    if (s->remapBegin == s->remapEnd) {
      uint32_t m = g_bitMask[s->bits];
      i0 = *(uint32_t*)(s->data + s->stride * i) & m;
      i1 = *(uint32_t*)(s->data + s->stride * (i + 1)) & m;
      i2 = *(uint32_t*)(s->data + s->stride * (i + 2)) & m;
    } else {
      uint32_t m = g_bitMask[s->bits];
      const Packed* r = &s->remapBegin[s->remapTab[e].packedIndex];
      i0 = Fetch(r, *(uint32_t*)(s->data + s->stride * i) & m);
      i1 = Fetch(r, *(uint32_t*)(s->data + s->stride * (i + 1)) & m);
      i2 = Fetch(r, *(uint32_t*)(s->data + s->stride * (i + 2)) & m);
    }
    const float* p0 = (const float*)(pos->data + pos->stride * i0);
    const float* p1 = (const float*)(pos->data + pos->stride * i1);
    const float* p2 = (const float*)(pos->data + pos->stride * i2);
    int n0 = Far(sphere, p0) == keepOutside;
    int n1 = Far(sphere, p1) == keepOutside;
    int n2 = Far(sphere, p2) == keepOutside;
    int sum = n1 + n2 + n0;
    bool emit;
    if (sum == (sum / 3) * 3) {
      if (n0 == sum % 3) continue;
      emit = true;
    } else if (mode == 0) {
      emit = true;
    } else if (mode == 2) {
      if (!(sum > 1)) continue;
      emit = true;
    } else if (mode == 3) {
      int count = (int)(co->vEnd - co->vBegin);
      uint16_t base = (uint16_t)count;
      int st = range->stream;
      if (n0 == 0) {
        if (n1 == 0) {
          co->Edge(st, i + 2, i, sphere.RayHit(p2, p0));
          co->Edge(st, i + 2, i + 1, sphere.RayHit(p2, p1));
          co->Pass(st, i + 2);
        } else {
          co->Edge(st, i + 1, i, sphere.RayHit(p1, p0));
          co->Pass(st, i + 1);
          if (n2 == 0) {
            co->Edge(st, i + 1, i + 2, sphere.RayHit(p1, p2));
          } else {
            co->Pass(st, i + 2);
            co->Edge(st, i + 2, i, sphere.RayHit(p2, p0));
          }
        }
      } else {
        co->Pass(st, i);
        if (n1 == 0) {
          co->Edge(st, i, i + 1, sphere.RayHit(p0, p1));
          if (n2 != 0) {
            co->Edge(st, i + 2, i + 1, sphere.RayHit(p2, p1));
            co->Pass(st, i + 2);
          } else {
            co->Edge(st, i, i + 2, sphere.RayHit(p0, p2));
          }
        } else {
          co->Pass(st, i + 1);
          co->Edge(st, i + 1, i + 2, sphere.RayHit(p1, p2));
          co->Edge(st, i, i + 2, sphere.RayHit(p0, p2));
        }
      }
      UShortVec_s0079_c960* v = &co->indexSets[co->curSet];
      uint16_t a = base;
      v->push_back(a);
      uint16_t b = (uint16_t)(count + 1);
      co->indexSets[co->curSet].push_back(b);
      uint16_t c = (uint16_t)(count + 2);
      co->indexSets[co->curSet].push_back(c);
      if (sum > 1) {
        co->indexSets[co->curSet].push_back(a);
        co->indexSets[co->curSet].push_back(c);
        uint16_t d = (uint16_t)(count + 3);
        co->indexSets[co->curSet].push_back(d);
      }
      continue;
    } else {
      continue;
    }
    if (emit) {
      uint16_t v0 = Fetch16(s, i);
      out->push_back(v0);
      uint16_t v1 = Fetch16(s, i + 1);
      out->push_back(v1);
      uint16_t v2 = Fetch16(s, i + 2);
      out->push_back(v2);
    }
  }
}

// @ 0x0079d190
void SplitPlane2::SplitTriangles(SplitModel_s0079_d190* model, SplitRange* rng, UShortVec_s0079_d190* above, UShortVec_s0079_d190* below, SplitCtx_s0079_d190* ctxAbove, SplitCtx_s0079_d190* ctxBelow)
{
    int streamSel = FindStream(model, 1, 0, 3, 0xe);
    IndexBuf_s0079_d190* ib = model->mpIndexBufs + rng->mSub;
    VertStream_s0079_d190* vs = (VertStream_s0079_d190*)((char*)model->mpStreams + streamSel * 0x20 + 0x10);
    for (int i = rng->mStart; i < rng->mEnd; i += 3) {
        uint32_t i0, i1, i2;
        if (ib->mpRemapBegin == ib->mpRemapEnd) {
            uint32_t mask = g_IndexMask[ib->mFormat];
            uint32_t stride = ib->mStride;
            i0 = *(uint32_t*)(stride * i + ib->mpData) & mask;
            i1 = *(uint32_t*)(stride * (i + 1) + ib->mpData) & mask;
            i2 = *(uint32_t*)(stride * (i + 2) + ib->mpData) & mask;
        } else {
            const Remap* r = (const Remap*)((char*)ib->mpRemapBegin + *(int16_t*)(ib->mpRemapSel + 2 + streamSel * 4) * 0x10);
            uint32_t stride = ib->mStride;
            uint32_t mask = g_IndexMask[ib->mFormat];
            i0 = *(uint32_t*)((*(uint32_t*)(stride * i + ib->mpData) & mask) * r->mStride + r->mpData) & g_IndexMask[r->mFormat];
            i1 = *(uint32_t*)((*(uint32_t*)(stride * (i + 1) + ib->mpData) & mask) * r->mStride + r->mpData) & g_IndexMask[r->mFormat];
            i2 = *(uint32_t*)((*(uint32_t*)(stride * (i + 2) + ib->mpData) & mask) * r->mStride + r->mpData) & g_IndexMask[r->mFormat];
        }
        const float* v0 = (const float*)(vs->mStride * i0 + vs->mpData);
        const float* v1 = (const float*)(vs->mStride * i1 + vs->mpData);
        const float* v2 = (const float*)(vs->mStride * i2 + vs->mpData);
        int s0 = (mEq.z * v0[2] + mEq.y * v0[1] + mEq.x * v0[0]) > mEq.d;
        int s1 = (mEq.z * v1[2] + mEq.y * v1[1] + mEq.x * v1[0]) > mEq.d;
        int s2 = (mEq.z * v2[2] + mEq.y * v2[1] + mEq.x * v2[0]) > mEq.d;
        int sum = s2 + s1 + s0;
        if (sum % 3 == 0) {
            // whole triangle on one side
            if (s0 == sum % 3)
                goto emitBelow;
            goto emitAbove;
        }
        switch (mMode) {
        case 0:
            goto emitAbove;
        case 1:
            goto emitBelow;
        case 2: {
            UShortVec_s0079_d190* dst = sum > 1 ? above : below;
            dst->push_back_call(FetchIndex16_s0079_d190(ib, i));
            dst->push_back_call(FetchIndex16_s0079_d190(ib, i + 1));
            dst->push_back_call(FetchIndex16_s0079_d190(ib, i + 2));
            continue;
        }
        case 3: {
            int baseA = ctxAbove->VertexCount();
            int baseB = ctxBelow->VertexCount();
            if (s0 != 0) {
                ctxAbove->AddVertex(rng->mSub, i);
                if (s1 != 0) {
                    float t12 = mEq.Intersect(v1, v2);
                    float t02 = mEq.Intersect(v0, v2);
                    ctxAbove->AddVertex(rng->mSub, i + 1);
                    ctxAbove->AddEdge(rng->mSub, i + 1, i + 2, t12);
                    ctxAbove->AddEdge(rng->mSub, i, i + 2, t02);
                    ctxBelow->AddEdge(rng->mSub, i + 2, i, 1.0f - t02);
                    ctxBelow->AddEdge(rng->mSub, i + 2, i + 1, 1.0f - t12);
                    ctxBelow->AddVertex(rng->mSub, i + 2);
                } else {
                    float t01 = mEq.Intersect(v0, v1);
                    ctxAbove->AddEdge(rng->mSub, i, i + 1, t01);
                    ctxBelow->AddEdge(rng->mSub, i + 1, i, 1.0f - t01);
                    ctxBelow->AddVertex(rng->mSub, i + 1);
                    if (s2 != 0) {
                        float t21 = mEq.Intersect(v2, v1);
                        ctxAbove->AddEdge(rng->mSub, i + 2, i + 1, t21);
                        ctxAbove->AddVertex(rng->mSub, i + 2);
                        ctxBelow->AddEdge(rng->mSub, i + 1, i + 2, 1.0f - t21);
                    } else {
                        float t02 = mEq.Intersect(v0, v2);
                        ctxAbove->AddEdge(rng->mSub, i, i + 2, t02);
                        ctxBelow->AddVertex(rng->mSub, i + 2);
                        ctxBelow->AddEdge(rng->mSub, i + 2, i, 1.0f - t02);
                    }
                }
            } else {
                ctxBelow->AddVertex(rng->mSub, i);
                if (s1 != 0) {
                    float t10 = mEq.Intersect(v1, v0);
                    ctxAbove->AddEdge(rng->mSub, i + 1, i, t10);
                    ctxAbove->AddVertex(rng->mSub, i + 1);
                    ctxBelow->AddEdge(rng->mSub, i, i + 1, 1.0f - t10);
                    if (s2 != 0) {
                        float t20 = mEq.Intersect(v2, v0);
                        ctxAbove->AddVertex(rng->mSub, i + 2);
                        ctxAbove->AddEdge(rng->mSub, i + 2, i, t20);
                        ctxBelow->AddEdge(rng->mSub, i, i + 2, 1.0f - t20);
                    } else {
                        float t12 = mEq.Intersect(v1, v2);
                        ctxAbove->AddEdge(rng->mSub, i + 1, i + 2, t12);
                        ctxBelow->AddEdge(rng->mSub, i + 2, i + 1, 1.0f - t12);
                        ctxBelow->AddVertex(rng->mSub, i + 2);
                    }
                } else {
                    float t20 = mEq.Intersect(v2, v0);
                    float t21 = mEq.Intersect(v2, v1);
                    ctxAbove->AddEdge(rng->mSub, i + 2, i, t20);
                    ctxAbove->AddEdge(rng->mSub, i + 2, i + 1, t21);
                    ctxAbove->AddVertex(rng->mSub, i + 2);
                    ctxBelow->AddVertex(rng->mSub, i + 1);
                    ctxBelow->AddEdge(rng->mSub, i + 1, i + 2, 1.0f - t21);
                    ctxBelow->AddEdge(rng->mSub, i, i + 2, 1.0f - t20);
                }
            }
            ctxAbove->AddIndexInline((uint16_t)baseA);
            ctxAbove->AddIndexInline((uint16_t)(baseA + 1));
            ctxAbove->AddIndexInline((uint16_t)(baseA + 2));
            ctxBelow->AddIndexInline((uint16_t)baseB);
            ctxBelow->AddIndexInline((uint16_t)(baseB + 1));
            ctxBelow->AddIndexInline((uint16_t)(baseB + 2));
            // the side holding two original vertices is a quad: add its second triangle
            SplitCtx_s0079_d190* quad = ctxBelow;
            int base = baseB;
            if (sum > 1) {
                base = baseA;
                quad = ctxAbove;
            }
            quad->AddIndex((uint16_t)base);
            quad->AddIndex((uint16_t)(base + 2));
            quad->AddIndex((uint16_t)(base + 3));
            continue;
        }
        default:
            continue;
        }
    emitAbove:
        above->push_back(FetchIndex16_s0079_d190(ib, i));
        above->push_back(FetchIndex16_s0079_d190(ib, i + 1));
        above->push_back(FetchIndex16_s0079_d190(ib, i + 2));
        continue;
    emitBelow:
        below->push_back(FetchIndex16_s0079_d190(ib, i));
        below->push_back(FetchIndex16_s0079_d190(ib, i + 1));
        below->push_back(FetchIndex16_s0079_d190(ib, i + 2));
    }
}

// @ 0x0079dce0
void CylinderSlicer::Run(Mesh* mesh, Job_s0079_dce0* job, UShortVec_s0079_dce0* vecAllOut, UShortVec_s0079_dce0* vecAllIn, Out_s0079_dce0* out6, Out_s0079_dce0* out7)
{
    int sidx = FUN_0071ddc0(mesh, 1, 0, 3, 0xe);
    IndexStream* ib = (IndexStream*)(mesh->indexStreams + *(int*)((char*)job + 4) * 0x8c);
    Stream* vs = (Stream*)(mesh->streams + sidx * 0x20 + 0x10);

    for (int a = job->start; a < job->end; a += 3) {
        int b = a + 1;
        int c = a + 2;
        uint ia, ib_, ic;
        if (ib->remapBegin != ib->remapEnd) {
            Stream* rm = (Stream*)((char*)ib->remapBegin + *(short*)(ib->table + sidx * 4 + 2) * 0x10);
            ia = rm->Read(ib->Read(a));
            ib_ = rm->Read(ib->Read(b));
            ic = rm->Read(ib->Read(c));
        } else {
            ia = ib->Read(a);
            ib_ = ib->Read(b);
            ic = ib->Read(c);
        }
        const float* pA = (const float*)(vs->data + vs->stride * ia);
        const float* pB = (const float*)(vs->data + vs->stride * ib_);
        const float* pC = (const float*)(vs->data + vs->stride * ic);
        int fA = cyl.IsOutside(pA) ? 1 : 0;
        int fB = cyl.IsOutside(pB) ? 1 : 0;
        int fC = cyl.IsOutside(pC) ? 1 : 0;
        int sum = fC + fB + fA;

        if (sum == (sum / 3) * 3) {
            // all inside (0) or all outside (3): copy the triangle's indices
            UShortVec_s0079_dce0* v = (fA == sum % 3) ? vecAllIn : vecAllOut;
            v->push_back(ib->ReadU16(a));
            v->push_back(ib->ReadU16(b));
            v->push_back(ib->ReadU16(c));
        } else {
            switch (mode) {
            case 0:
                vecAllOut->push_back(ib->ReadU16(a));
                vecAllOut->push_back(ib->ReadU16(b));
                vecAllOut->push_back(ib->ReadU16(c));
                break;
            case 1:
                vecAllIn->push_back(ib->ReadU16(a));
                vecAllIn->push_back(ib->ReadU16(b));
                vecAllIn->push_back(ib->ReadU16(c));
                break;
            case 2: {
                ushort va = ib->ReadU16(a);
                UShortVec_s0079_dce0* v;
                if (sum > 1) {
                    vecAllOut->PushBackOOL(&va);
                    v = vecAllOut;
                } else {
                    vecAllIn->PushBackOOL(&va);
                    v = vecAllIn;
                }
                ushort vb = ib->ReadU16(b);
                v->PushBackOOL(&vb);
                ushort vc = ib->ReadU16(c);
                v->PushBackOOL(&vc);
                break;
            }
            case 3: {
                int n6 = out6->f8 - out6->f4;
                int n7 = out7->f8 - out7->f4;
                if (fA != 0) {
                    out6->AddVert(job->src, a);
                    if (fB != 0) {
                        float t1 = cyl.Intersect(pB, pC);
                        float t2 = cyl.Intersect(pA, pC);
                        out6->AddVert(job->src, b);
                        out6->AddLerp(job->src, b, c, t1);
                        out6->AddLerp(job->src, a, c, t2);
                        out7->AddLerp(job->src, c, a, 1.0f - t2);
                        out7->AddLerp(job->src, c, b, 1.0f - t1);
                        out7->AddVert(job->src, c);
                    } else {
                        float t = cyl.Intersect(pA, pB);
                        out6->AddLerp(job->src, a, b, t);
                        out7->AddLerp(job->src, b, a, 1.0f - t);
                        out7->AddVert(job->src, b);
                        if (fC != 0) {
                            float tt = cyl.Intersect(pC, pB);
                            out6->AddLerp(job->src, c, b, tt);
                            out6->AddVert(job->src, c);
                            out7->AddLerp(job->src, b, c, 1.0f - tt);
                        } else {
                            float tt = cyl.Intersect(pA, pC);
                            out6->AddLerp(job->src, a, c, tt);
                            out7->AddVert(job->src, c);
                            out7->AddLerp(job->src, c, a, 1.0f - tt);
                        }
                    }
                } else {
                    out7->AddVert(job->src, a);
                    if (fB != 0) {
                        float u = cyl.Intersect(pB, pA);
                        out6->AddLerp(job->src, b, a, u);
                        out6->AddVert(job->src, b);
                        out7->AddLerp(job->src, a, b, 1.0f - u);
                        if (fC != 0) {
                            float w = cyl.Intersect(pC, pA);
                            out6->AddVert(job->src, c);
                            out6->AddLerp(job->src, c, a, w);
                            out7->AddLerp(job->src, a, c, 1.0f - w);
                        } else {
                            float z = cyl.Intersect(pB, pC);
                            out6->AddLerp(job->src, b, c, z);
                            out7->AddLerp(job->src, c, b, 1.0f - z);
                            out7->AddVert(job->src, c);
                        }
                    } else {
                        float p = cyl.Intersect(pC, pA);
                        float q = cyl.Intersect(pC, pB);
                        out6->AddLerp(job->src, c, a, p);
                        out6->AddLerp(job->src, c, b, q);
                        out6->AddVert(job->src, c);
                        out7->AddVert(job->src, b);
                        out7->AddLerp(job->src, b, c, 1.0f - q);
                        out7->AddLerp(job->src, a, c, 1.0f - p);
                    }
                }
                UShortVec_s0079_dce0* i6 = out6->IdxVec();
                i6->push_back((ushort)n6);
                i6 = out6->IdxVec();
                i6->push_back((ushort)(n6 + 1));
                i6 = out6->IdxVec();
                i6->push_back((ushort)(n6 + 2));
                UShortVec_s0079_dce0* i7 = out7->IdxVec();
                i7->push_back((ushort)n7);
                i7 = out7->IdxVec();
                i7->push_back((ushort)(n7 + 1));
                i7 = out7->IdxVec();
                i7->push_back((ushort)(n7 + 2));
                Out_s0079_dce0* t = out7;
                int base = n7;
                if (sum > 1) {
                    base = n6;
                    t = out6;
                }
                t->AddTri(base);
                t->AddTri(base + 2);
                t->AddTri(base + 3);
                break;
            }
            }
        }
    }
}
