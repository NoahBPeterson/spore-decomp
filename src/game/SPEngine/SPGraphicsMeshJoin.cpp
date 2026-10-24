// src/game/SPEngine/SPGraphicsMeshJoin.cpp -- migrated from slice(s) s0071e390, s00728020, s007249f0, s0073a110, s007361e0, s00735350, s00728c90, s00726c20, s00725e40, s00725130, s00724100, s00723140, s00722410, s00721240, s00720290, s0071f410 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsMeshJoin.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cHeap.h"
#include "cSPVector3.h"
#include "SP/cDualEdge.h"
#include "SP/cFaceCluster.h"
#include "SP/cHeapEntry.h"
#include "SP/cMeshClusterer.h"
#include <math.h>
#include <string.h>
#include <new>
#include <float.h>
#include <xmmintrin.h>
#include "SP/cClusterInfo.h"
#include "cSPVector2.h"
#include <intrin.h>

// ---- items of slice s0071f410 begin (TODO(rewrite): local stubs, replace by canonical classes)
void Obj15_Init(void* p);                                  // 0x00720070
void Obj15_Assign(void* src, void* dst, int flag);         // 0x0071fce0
struct Obj15 {
    uint32_t m0;        // +0x0
    uint32_t m4;        // +0x4
    uint16_t m8;        // +0x8
};
// ---- items of slice s0071f410 end

// ---- items of slice s00720290 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  __cdecl EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" void* __cdecl EASTL_allocator_allocate(uint32_t size, const char* name, int a, int b,
                                                  const char* file, int line); // 0x00f473a0
extern "C" void* __cdecl operator_new(uint32_t size, const char* name, int a, int b,
                                      const char* file, int line);
extern "C" void  __cdecl op_new_array(void* dst, int zero, uint32_t size);
extern "C" float __cdecl sqrtf(float x);
struct Vec3 { float x, y, z; };
struct cFaceCluster {
    Vec3 mSumAreaPoint;      // +0x00
    Vec3 mSumAreaNormal;     // +0x0c
    float mArea;             // +0x18
    int mFirstEdge;          // +0x1c
    int mParentCluster;      // +0x20
    void* mPreviousDE;       // +0x24
};                           // 0x28
struct cHeapEntry { float mCost; int mHeapIndex; };
struct cDualEdge {
    float mCost;             // +0x00
    int mHeapIndex;          // +0x04
    int mClusters[2];        // +0x08
    int mNextEdges[2];       // +0x10
};                           // 0x18
struct FaceVec { cFaceCluster* mpBegin; cFaceCluster* mpEnd; cFaceCluster* mpCap; int pad[2]; };
struct DualVec { cDualEdge* mpBegin; cDualEdge* mpEnd; cDualEdge* mpCap; int pad[2]; };
struct HeapVec { cHeapEntry** mpBegin; cHeapEntry** mpEnd; cHeapEntry** mpCap; int pad[2]; };
struct cHeap {
    HeapVec mHeapEntries;    // +0x00
    void HeapifyDown(int i);
    void HeapifyUp(int i);
};
struct cMeshClusterer {
    char pad_00[0x48];
    FaceVec mFaceClusters;   // +0x48
    DualVec mDualEdges;      // +0x5c
    cHeap mEdgeHeap;         // +0x70
    float mMaxError;         // +0x84
    int mNumClusters;        // +0x88
    int mCostType;           // +0x8c
    void CalcError(cFaceCluster* a, cFaceCluster* b, float* out);
    void MergeEdgeLists(int param_2, int param_3);
};
struct Pair16 { int first, second; };
struct Rec18 {
    int*   f0;   // +0x00  int array (in)
    Pair16* f1;  // +0x04  pair array
    int*   f2;   // +0x08  int array
    int    f3;   // +0x0c
    int    f4;   // +0x10
    int    f5;   // +0x14  group modulus
};
struct MeshAdj {
    Pair16* mPairs;      // +0x00
    char    pad04[0x10];
    Rec18*  mRecords;    // +0x14
    char    pad18[0x10];
    int     mCount;      // +0x28
    int     mCounter;    // +0x2c
    char    pad30[4];
    bool (__cdecl *mCb)(Rec18*, int*, int*, void*);  // +0x34
    void*   mCbArg;      // +0x38
    bool    mFlag;       // +0x3c
    void AddTri(int a, int n, int c, int* in, Pair16* out, int d);
    void LinkRec(int node, int pos, int val);
    void Build();
};
struct HashTable {
    char     pad00[4];
    void**   mBuckets;   // +0x04
    uint32_t mCount;     // +0x08
    void Grow(uint32_t newSize);
};
struct Element68 {
    char  pad00[0x14];
    void* v14;           // +0x14
    char  pad18[0x1c];
    void* v34;           // +0x34
    char  pad38[0x10];
    void* v48;           // +0x48
    char  pad4c[0x1c];
    void Dtor();
};
// ---- items of slice s00720290 end

// ---- items of slice s00721240 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  __cdecl qsort(void* base, uint32_t n, uint32_t sz, int (__cdecl* cmp)(const void*, const void*));
extern "C" int   __cdecl ComparePairs(const void* a, const void* b);
extern float g_chartMinX, g_chartMinY;
struct FChartNode { float kx, ky, kz; int f0c; FChartNode* next; };  // 0x14
struct IChartNode { int k0, k1, k2; int f0c; IChartNode* next; };    // 0x14
struct HashFind { void* pNode; void* pSlot; };                       // out pair written by Find*
struct ChartHash {
    char      pad00[4];
    void**    mBuckets;   // +0x04
    uint32_t  mCapacity;  // +0x08
    uint32_t  mCount;     // +0x0c
    char      state[0x30];
    void GrowF(uint32_t newSize);
    void FindF(int* out, float* key);
    void InsertF(int* out, float* key);
    void FindI(int* out, int* key);
    void InsertI(int* out, int* key);
};
struct Chart68 {
    char  p0[0x14];
    void* v14;   // +0x14
    char  p1[0x1c];
    void* v34;   // +0x34
    char  p2[0x10];
    void* v48;   // +0x48
    char  p3[0x1c];
};
struct TwoVtbl { void* vt0; void* vt1; char pad[4]; void* p0c; };
struct ChartRef;
struct ChartVec { char pad[0xc]; void** begin; void** end; ChartRef* MakeChartRef(ChartRef* out); };
struct ChartRef {
    int  mNumElts;             // +0x00
    void* mData;               // +0x04
    unsigned short mEltSize;   // +0x08
    unsigned short mEltStride; // +0x0a
    void* mOwner;              // +0x0c
};
struct HeapVec2 { void* mpBegin; void* mpEnd; void* mpCap; int pad[2]; };
struct cHeap2 { HeapVec2 mHeapEntries; void HeapifyDown(int i); };
struct FaceVec2 { void* mpBegin; void* mpEnd; void* mpCap; int pad[2]; };
struct CMeshClusterer2 {
    char pad_00[0x48];
    FaceVec2 mFaceClusters;  // +0x48
    char pad_5c[0x14];
    cHeap2 mEdgeHeap;        // +0x70
    float mMaxError;         // +0x84
    int mNumClusters;        // +0x88
    int mCostType;           // +0x8c
    void CollapseEdges();
    void MergeEdgeLists(int a, int b);
};
// ---- items of slice s00721240 end

// ---- items of slice s00722410 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct VecAppend8 {                                 // thiscall target: vector in ECX, ret 8 (cleans e,val)
    void Append(void* e, void* val);                // 0x00722410
};
struct Vec8 { float x, y; };
struct VecAny { int* begin; int* end; int* cap; void Assign(int n, int value, int dummy); void Push8(Vec8* val); };
// ---- items of slice s00722410 end

// ---- items of slice s00723140 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl memcpy(void*, const void*, size_t);
extern "C" void* __cdecl memset(void*, int, size_t);
extern const char kEastlAllocFile[];  // 0x13ebb38 ".../EASTL/allocator.h"
extern uint32_t gBitMask[];  // 0x140d0ac: per-format value masks, indexed by BufView::maskIdx
#pragma intrinsic(_InterlockedExchange)
void __cdecl operator_delete__(void* p);  // 0xf47380
struct RefObj { virtual int AddRef(); virtual int Release(); };
struct BufView {
    int      count;     // +0
    char*    data;      // +4
    uint16_t maskIdx;   // +8
    uint16_t stride;    // +0xa
    RefObj*  ref;       // +0xc
};
void __cdecl AllocView(BufView* v);  // 0x720070: allocate v->data for count/stride, set ref
static inline void ReleaseRef(RefObj* r) { if (r) r->Release(); }
static inline uint32_t ViewU32(const BufView& v, int i) {
    return *(uint32_t*)(v.data + (uint32_t)v.stride * i) & gBitMask[v.maskIdx];
}
struct Vertex3D {  // EA::Text::Vertex3D, 0x18 bytes; ctor zeroes 5 of the 6 words
    uint32_t w[6];
    Vertex3D() { w[0] = 0; w[1] = 0; w[2] = 0; w[4] = 0; w[5] = 0; }
};
Vertex3D* __cdecl CopyVertex3D(Vertex3D* first, Vertex3D* last, Vertex3D* dest);  // 0x720250 (do_copy)
struct Vec24 {  // eastl::vector<Vertex3D>
    Vertex3D* mpBegin;
    Vertex3D* mpEnd;
    void Insert(Vertex3D* pos, uint32_t n, const Vertex3D* val);  // 0x722580
    void resize(uint32_t n);                                // 0x7237a0
    void resize(uint32_t n, const Vertex3D* val);           // 0x7238b0
};
struct Xform56 { uint32_t w[14]; };  // cSPTransform, 0x38 bytes
Xform56* __cdecl CopyXform(const Xform56* first, const Xform56* last, Xform56* dest);        // 0xf339d0
void __cdecl UninitCopyXform(Xform56** out, const Xform56* first, const Xform56* last, Xform56* dest, int tag);  // 0xf337a0
struct Vec56 {  // eastl::vector<cSPTransform>
    Xform56* mpBegin;
    Xform56* mpEnd;
    Xform56* mpCapacity;
    Xform56* AllocCopy(uint32_t n, const Xform56* first, const Xform56* last);  // 0x722990
    void DoAssign(const Xform56* first, const Xform56* last, int tag);  // 0x723af0
};
struct VecInt {  // eastl::vector<int>
    int* mpBegin;
    int* mpEnd;
    int* mpCapacity;
    void* mAllocator;
    int mPad;
    void Alloc(uint32_t n, const void* tag);  // 0x4aa350
    void Fill(uint32_t n, int val);           // 0x722ca0
};
struct Vec8_s0072_3140 {  // eastl::vector<8-byte element>
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    void* mAllocator;
    int mPad;
    void Alloc(uint32_t n, const void* srcAlloc);  // 0x6a40a0
    Vec8_s0072_3140& assign(const Vec8_s0072_3140& o);                    // 0x473b00
};
void __cdecl UninitCopy8(void** outEnd, const void* first, const void* last, void* dest, const void* tag);  // 0x479c00
struct VecFloat {  // eastl::vector<float, sp_vector_allocator>
    float* mpBegin;
    float* mpEnd;
    float* mpCapacity;
    void* mAllocator;
    int mPad;
    void Alloc(uint32_t n, const void* srcAlloc);   // 0x4aa350
    VecFloat& operator=(const VecFloat& o);          // 0x50d4e0
};
struct ObjBase {           // Object: vtable 0x13eb938 {AddRef, Release, dtor}
    virtual int AddRef() = 0;
    virtual int Release() = 0;
    virtual ~ObjBase();    // 0x517400
};
struct AtomicInt {         // EA::Thread::AtomicInt32: the ctor stores with xchg
    volatile long mValue;
    AtomicInt(long v) { _InterlockedExchange(&mValue, v); }
};
struct RefCounted {        // vtable 0x13ef094 {dtor}; refcount at +4 of this base
    virtual ~RefCounted(); // 0x41d780
    AtomicInt mRefCount;   // +8 in IntVecObj
    RefCounted() : mRefCount(0) {}
};
struct IntVecObj : ObjBase, RefCounted {   // vtables 0x13ef09c / 0x13ef098
    VecInt mVec;           // +0xc
    int mField20;          // +0x20
    IntVecObj(int n);                // 0x723680
    IntVecObj(int n, const int* v);  // 0x723720
    int AddRef();                    // 0x461290
    int Release();                   // 0x472970
    ~IntVecObj();                    // 0x472a70
};
struct ChartRec {
    int   i0;          // +0
    float f4;          // +4
    float f8;          // +8
    int   iC;          // +0xc
    int   i10;         // +0x10
    Vec8_s0072_3140  v14;         // +0x14 (alloc at +0x20)
    int   f28;         // +0x28
    int   f2C;         // +0x2c
    uint8_t b30;       // +0x30
    VecFloat v34;      // +0x34 (alloc at +0x40)
    VecFloat v48;      // +0x48 (alloc at +0x54)
    int i5C;           // +0x5c
    int i60;           // +0x60
    int i64;           // +0x64
    ChartRec(const ChartRec& o);       // 0x723930
    ChartRec& operator=(const ChartRec& o);  // 0x723a70
};
struct ViewEntry {          // 0x20 bytes; BufView at +0x10
    char hdr[0x10];
    BufView view;
};
struct SubMesh {            // 0x8c bytes
    BufView idx;            // +0   (count, data, maskIdx, stride, ref)
    int     field10;        // +0x10
    int16_t* pairs;         // +0x14 (pairs of int16: view slot, index-view slot)
    char    pad18[0x44 - 0x18];
    BufView* views;         // +0x44 begin
    BufView* viewsEnd;      // +0x48
    char    pad4c[0x8c - 0x4c];
};
struct MeshData {
    char       pad0[8];
    ViewEntry* entries;     // +8
    char       padc[0x1c - 0xc];
    SubMesh*   items;       // +0x1c
    SubMesh*   itemsEnd;    // +0x20
};
int  __cdecl FindElement(MeshData* m, int a, int b, int c, int d);          // 0x71e090
int  __cdecl FindViewSlot(MeshData* m, int a, int b);                       // 0x71e040
int  __cdecl LookupView(MeshData* m, int a, int b, int c, int d);           // 0x71ddc0
void __cdecl PrepareSubMesh(SubMesh* s);                                    // 0x7368a0
void __cdecl StoreView(MeshData* m, int a, int b, int c, int d, BufView* v);  // 0x71f0f0
struct Chunk {              // 0x64 bytes
    char pad0[0x38];
    int  triBegin;          // +0x38
    int  triEnd;            // +0x3c
    int  vtxBase;           // +0x40
    int  vtxEnd;            // +0x44
    int  vtxBase2;          // +0x48
    int  vtxMid;            // +0x4c
    char pad50[0x64 - 0x50];
};
struct Edge { char pad[0x20]; int chunk; char pad24[4]; };  // 0x28 bytes
static inline void TakeIndex(uint32_t* map, uint32_t v, int& counter) {
    if ((int)map[v] < 0) map[v] = counter++;
}
struct MeshBuild {
    char      pad0[8];
    MeshData* mMesh;        // +8
    Chunk*    mChunks;      // +0xc
    char      pad10[0x20 - 0x10];
    BufView   mOut;         // +0x20 (remapped index view)
    int       mTotal;       // +0x30
    BufView   mTri;         // +0x34 (triangle order view)
    int       mMeshIdx;     // +0x44
    Edge*     mEdges;       // +0x48
    Edge*     mEdgesEnd;    // +0x4c
    char      pad50[0x88 - 0x50];
    int       mChunkCount;  // +0x88
    void Build();           // 0x723140
};
struct PairVec {  // eastl::vector<pair<fn, void*>> plus Vertex3D vector and bookkeeping
    char*  mpBegin;       // +0
    char*  mpEnd;         // +4
    char*  mpCapacity;    // +8
    char   padc[0x14 - 0xc];
    Vec24  mVerts;        // +0x14
    char   pad1c[0x28 - 0x1c];
    int    mCount;        // +0x28
    int    mField2C;      // +0x2c
    char   pad30[0x34 - 0x30];
    int    mField34;      // +0x34
    int    mField38;      // +0x38
    uint8_t mFlag3C;      // +0x3c
    void Insert(char* pos, uint32_t n, const void* val);  // 0x740b00
    void Erase(char* first, char* last);                  // 0xd018d0
    void Fill(int a, int count, int type, uint32_t* idx, void* data, int z);  // 0x720290
    void Clear2();                                        // 0x7204c0
    void Reset(uint32_t nVerts, uint32_t nPairs, int a, int b, uint8_t flag);  // 0x723cf0
};
    void operator_delete__(...); // 0x00f47380
// ---- items of slice s00723140 end

// ---- items of slice s00724100 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t gTypeMask[];             // 0x0140d0ac
struct IRefCount {
    virtual int AddRef();
    virtual int Release();
};
struct EltRef {
    int mCount;           // +0x00
    char* mpData;         // +0x04
    uint16_t mType;       // +0x08
    uint16_t mStride;     // +0x0a
    IRefCount* mpOwner;   // +0x0c
    EltRef() {}
    EltRef(const EltRef& o)
        : mCount(o.mCount), mpData(o.mpData), mType(o.mType), mStride(o.mStride), mpOwner(o.mpOwner) {
        if (mpOwner)
            mpOwner->AddRef();
    }
    ~EltRef() {
        if (mpOwner)
            mpOwner->Release();
    }
};
struct MeshElt {          // 0x20 bytes
    char pad[0x10];
    EltRef mRef;          // +0x10
};
struct SectionFmt { int16_t mElt; int16_t mIndex; };
struct MeshSection {      // 0x8c bytes
    EltRef mVertIndices;      // +0x00
    int mNumVertices;         // +0x10
    SectionFmt* mFmtBegin;    // +0x14
    SectionFmt* mFmtEnd;      // +0x18
    char pad1c[0x28];
    EltRef* mpIndexArrays;    // +0x44
    char pad48[0x44];
};
struct MeshData_s0072_4100 {
    char pad00[8];
    MeshElt* mpElts;          // +0x08
    char pad0c[0x10];
    MeshSection* mpSections;  // +0x1c
};
struct cFaceCluster_s0072_4100 {         // 0x28
    float mSumAreaPoint[3];   // +0x00
    float mSumAreaNormal[3];  // +0x0c
    float mArea;              // +0x18
    int mFirstEdge;           // +0x1c
    int mParentCluster;       // +0x20
    void* mPreviousDE;        // +0x24
};
struct FaceVec_s0072_4100 {
    cFaceCluster_s0072_4100* mpBegin;
    cFaceCluster_s0072_4100* mpEnd;
    cFaceCluster_s0072_4100* mpCap;
    int pad[2];
    void resize(uint32_t n);             // 0x00723840
};
struct DualVec_s0072_4100 {
    cDualEdge* mpBegin;
    cDualEdge* mpEnd;
    cDualEdge* mpCap;
    int pad[2];
    void resize(uint32_t n, const cDualEdge* v);  // 0x007238b0
};
struct HeapVec_s0072_4100 {
    cDualEdge** mpBegin;
    cDualEdge** mpEnd;
    cDualEdge** mpCap;
    int pad[2];
    void DoInsertValue(cDualEdge** pos, cDualEdge* const* v);  // 0x006ec4a0
};
struct cHeap_s0072_4100 {
    HeapVec_s0072_4100 mHeapEntries;
    void HeapifyUp(int i);               // 0x007206b0
};
int __cdecl FindElement(MeshData_s0072_4100* m, int section, int a, int b, int c);  // 0x0071e090
int __cdecl FindStream(MeshData_s0072_4100* m, int a, int b, int c, int d);         // 0x0071ddc0
static inline uint32_t ReadIndex(const EltRef* r, int i) {
    return *(uint32_t*)(r->mpData + i * r->mStride) & gTypeMask[r->mType];
}
struct cMeshClusterer_s0072_4100 {
    char pad00[8];
    MeshData_s0072_4100* mpMesh;        // +0x08
    char pad0c[0x38];
    int mSection;            // +0x44
    FaceVec_s0072_4100 mFaceClusters;   // +0x48
    DualVec_s0072_4100 mDualEdges;      // +0x5c
    cHeap_s0072_4100 mEdgeHeap;         // +0x70
    char pad84[4];
    int mNumClusters;        // +0x88
    void CalcError(cFaceCluster_s0072_4100* a, cFaceCluster_s0072_4100* b, float* out);  // 0x00720700
    void Setup();  // 0x00724100 (cMeshClusterer::Setup)
};
// ---- items of slice s00724100 end

// ---- items of slice s00725130 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define EASTL_ALLOCATOR_FILE \
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
void* operator new[](unsigned int n, const char* name, int flags, unsigned int debugFlags,
                     const char* file, int line);                    // 0x00f473a0
void operator delete[](void* p, const char* name, int flags, unsigned int debugFlags,
                       const char* file, int line);
namespace EA {
namespace Thread {
 void ThreadSleep(const int& relativeTime);   // 0x00921df0
}
}
namespace EA {
namespace COM {
struct IRefCount_s0072_5130 {
    virtual int AddRef() = 0;
    virtual int Release() = 0;
};
}
}
namespace EA {
template <typename T>
class AutoRefCount_s0072_5130 {
public:
    T* mpObject;
    AutoRefCount_s0072_5130() : mpObject(0) {}
    AutoRefCount_s0072_5130(const AutoRefCount_s0072_5130& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount_s0072_5130() { if (mpObject) mpObject->Release(); }
    AutoRefCount_s0072_5130& operator=(const AutoRefCount_s0072_5130& x) { return operator=(x.mpObject); }
    AutoRefCount_s0072_5130& operator=(T* p)
    {
        if (p != mpObject) {
            T* const pTemp = mpObject;
            if (p)
                p->AddRef();
            mpObject = p;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
};
}
namespace eastl {
struct sp_vector_allocator_s0072_5130 {
    void* allocate(unsigned int n)
    {
        return operator new[](n, "Graphics", 0, 0, EASTL_ALLOCATOR_FILE, 0xd1);
    }
    void deallocate(void* p)
    {
        if (p && ((int*)p)[-1])
            operator delete[](p);
    }
};
}
namespace eastl {
template <typename T>
class vector_s0072_5130 {
public:
    typedef unsigned int size_type;
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator_s0072_5130 mAllocator;

    vector_s0072_5130() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    __forceinline explicit vector_s0072_5130(size_type n)
    {
        mpBegin = DoAllocate(n);
        mpCapacity = mpBegin + n;
        mpEnd = mpBegin;
        for (size_type i = n; i; --i)
            *mpEnd++ = T();
        mpEnd = mpCapacity;
    }
    ~vector_s0072_5130()
    {
        mAllocator.deallocate(mpBegin);
    }

    size_type size() const { return (size_type)(mpEnd - mpBegin); }
    T& operator[](size_type i) { return mpBegin[i]; }
    T* data() { return mpBegin; }

    T* DoAllocate(size_type n) { return n ? (T*)mAllocator.allocate(n * sizeof(T)) : 0; }

    void resize(size_type n);                                    // 0x004cd3c0 (out of line)
    void DoInsertValues(T* position, size_type n, const T& value);  // 0x004cea40
    void DoInsertValue(T* position, const T& value);             // 0x004558a0

    T* erase(T* first, T* last)
    {
        memcpy(first, last, (char*)mpEnd - (char*)last);
        mpEnd -= (last - first);
        return first;
    }
    void resize_inline(size_type n)
    {
        if (n > (size_type)(mpEnd - mpBegin))
            DoInsertValues(mpEnd, n - (size_type)(mpEnd - mpBegin), T());
        else
            erase(mpBegin + n, mpEnd);
    }
    void push_back(const T& value)
    {
        if (mpEnd < mpCapacity) {
            T* p = mpEnd++;
            if (p)
                *p = value;
        } else
            DoInsertValue(mpEnd, value);
    }
};
}
namespace SP {
extern const uint32_t kEltSizeMask[];      // 0x0140d0ac: {0, 0xff, 0xffff, 0xffffff, 0xffffffff}
}
namespace SP {
struct cEltArrayRef_s0072_5130 {
    int mNumElts;
    unsigned char* mData;
    unsigned short mEltSize;
    unsigned short mEltStride;
    EA::AutoRefCount_s0072_5130<EA::COM::IRefCount_s0072_5130> mDataRC;

    uint32_t GetIndex(uint32_t i) const { return *(uint32_t*)(mData + mEltStride * i) & kEltSizeMask[mEltSize]; }
    int& Int(uint32_t i) { return *(int*)(mData + mEltStride * i); }
};
}
namespace SP {
struct cIndexArrayRef_s0072_5130 : cEltArrayRef_s0072_5130 {
    cIndexArrayRef_s0072_5130()
    {
        mNumElts = 0;
        mData = 0;
        mEltSize = 0;
        mEltStride = 0;
    }
};
}
namespace SP {
void AllocateEltArray(cEltArrayRef_s0072_5130* p);                                  // 0x00720070
}
namespace SP {
void MakeEltArrayUnique(cEltArrayRef_s0072_5130* p);                                // 0x007200f0
}
namespace SP {
void CopyEltArray(const cEltArrayRef_s0072_5130* src, cEltArrayRef_s0072_5130* dst);          // 0x007201d0
}
namespace SP {
struct cMDFormatEntry_s0072_5130 {
    short mElts;
    short mIndices;
};
}
namespace SP {
struct cMDSection_s0072_5130 {                     // retail stride 0x8c
    cIndexArrayRef_s0072_5130 mVertIndices;        // +0x00
    int mNumVertices;                   // +0x10
    cMDFormatEntry_s0072_5130* mFormat;            // +0x14 fixed_vector begin
    uint32_t pad18[0xb];
    cIndexArrayRef_s0072_5130* mEltIndices;        // +0x44 fixed_vector begin
    uint32_t pad48[0x11];
};
}
namespace SP {
struct cMDElementArray_s0072_5130 {                // 0x20
    int mSemantic;
    int mNumber;
    int mType;
    int mClass;
    cEltArrayRef_s0072_5130 mArray;                // +0x10
};
}
namespace SP {
struct cMDPrimitive_s0072_5130 {                   // 0x14
    int mPrimType;
    int mSection;
    int mStart;                         // +0x08
    int mEnd;                           // +0x0c
    int mSubset;
};
}
namespace SP {
template <typename T>
struct SPVector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[2];
};
}
namespace SP {
struct cMeshData_s0072_5130 {
    uint32_t mRefCountVtbl[2];
    SPVector<cMDElementArray_s0072_5130> mEltArrays;   // +0x08
    SPVector<cMDSection_s0072_5130> mSections;         // +0x1c
    SPVector<cMDPrimitive_s0072_5130> mPrimitives;     // +0x30
};
}
namespace SP {
int FindElementArray(cMeshData_s0072_5130* mesh, int semantic, int number, int type, int elementClass);  // 0x0071ddc0
}
namespace SP {
int FindFormatEntry(cMeshData_s0072_5130* mesh, int section, int eltArray);                           // 0x0071e040
}
namespace SP {
void FindPrimitives(cMeshData_s0072_5130* mesh, eastl::vector_s0072_5130<int>* out, int section, int a, int b);  // 0x0071ee10
}
namespace SP {
void BuildConnectivity(cMeshData_s0072_5130* mesh);                                                   // 0x007249f0
}
namespace SP {
void FinishEdges(cMeshData_s0072_5130* mesh);                                                         // 0x0073a4b0
}
namespace SP {
void Memset32(void* p, uint32_t value, int count);                                        // 0x0092cb00
}
namespace SP {
__forceinline void MergeEdgeRings(cEltArrayRef_s0072_5130& edgeMap, uint32_t e0, uint32_t e1)
{
    int& n0 = edgeMap.Int(e0);
    if (n0 < 0) {
        int n1 = edgeMap.Int(e1);
        n0 = (n1 >= 0) ? n1 : (int)e1;
        edgeMap.Int(e1) = e0;
    } else {
        int& n1 = edgeMap.Int(e1);
        if (n1 < 0) {
            n1 = n0;
            edgeMap.Int(e0) = e1;
        } else {
            int k = n1;
            while (k != (int)e0 && k != (int)e1)
                k = edgeMap.Int(k);
            if (k != (int)e0) {
                int t = n0;
                n0 = n1;
                n1 = t;
            }
        }
    }
}
}
namespace SP {
template <typename T>
__forceinline void CompactTriangles(const cEltArrayRef_s0072_5130& posIdx, cEltArrayRef_s0072_5130& adjIdx, cEltArrayRef_s0072_5130& edgeMap,
                             eastl::vector_s0072_5130<int>& corners, eastl::vector_s0072_5130<int>& remap, int nTris,
                             int& numOut)
{
    for (int i = 0; i < nTris; i++) {
        int i3 = i * 3;
        T p0 = *(T*)(posIdx.mData + posIdx.mEltStride * corners[i3]);
        T p1 = *(T*)(posIdx.mData + posIdx.mEltStride * corners[i3 + 1]);
        int degenerate = 0;
        if (p0 == p1)
            degenerate = 1;
        T p2 = *(T*)(posIdx.mData + posIdx.mEltStride * corners[i3 + 2]);
        if (p1 == p2)
            degenerate += 2;
        if (p2 == p0)
            degenerate += 3;
        remap[i3] = numOut;
        if (degenerate == 0) {
            corners[numOut] = corners[i3];
            remap[i3 + 1] = ++numOut;
            corners[numOut] = corners[i3 + 1];
            remap[i3 + 2] = ++numOut;
            corners[numOut] = corners[i3 + 2];
            ++numOut;
        } else {
            remap[i3 + 1] = numOut;
            remap[i3 + 2] = numOut;
            if (adjIdx.mData && degenerate < 4) {
                uint32_t e0 = adjIdx.GetIndex(corners[i3 + degenerate - 1]);
                uint32_t e1 = adjIdx.GetIndex(corners[i3 + degenerate % 3]);
                MergeEdgeRings(edgeMap, e0, e1);
            }
        }
    }
}
}
// ---- items of slice s00725130 end

// ---- items of slice s00725e40 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* FUN_00f473a0(unsigned n, const char* name, int f, int df, const char* file, int line);
extern "C" void  FUN_00f47380(void* p);
extern "C" int   FUN_00721f50(int src, int srcEnd, int dst);
extern "C" void  FUN_00720e60(int src, int srcEnd, int dst);
extern "C" void  FUN_00721ed0(int dst, unsigned n, int value, int dst2);
extern "C" void  FUN_00721d80(int value);
extern "C" void  FUN_00721e50(void* p, ...);
extern "C" void  FUN_00722ac0(int src, int srcEnd, int dst);
extern "C" void  FUN_00723bf0(int first, int last, int tmp);
namespace SP {
struct cSPVector2 {
    float x, y;
    cSPVector2() {}
    cSPVector2(float ax, float ay) : x(ax), y(ay) {}
    cSPVector2& operator-=(const cSPVector2& o) { float nx = x - o.x; float ny = y - o.y; x = nx; y = ny; return *this; }
    cSPVector2& operator*=(float s) { float nx = x * s; float ny = y * s; x = nx; y = ny; return *this; }
};
}
namespace SP {
inline cSPVector2 operator-(const cSPVector2& a, const cSPVector2& b) { return cSPVector2(a.x - b.x, a.y - b.y); }
}
namespace SP {
struct cSPVector3 {
    float x, y, z;
    cSPVector3() {}
    cSPVector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    cSPVector3(const cSPVector3& o) : x(o.x), y(o.y), z(o.z) {}
    cSPVector3& operator=(const cSPVector3& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
}
namespace SP {
inline cSPVector3 operator-(const cSPVector3& a, const cSPVector3& b) { return cSPVector3(a.x - b.x, a.y - b.y, a.z - b.z); }
}
namespace SP {
inline cSPVector3 operator+(const cSPVector3& a, const cSPVector3& b) { return cSPVector3(a.x + b.x, a.y + b.y, a.z + b.z); }
}
namespace SP {
inline cSPVector3 operator*(const cSPVector3& a, float s) { return cSPVector3(a.x * s, a.y * s, a.z * s); }
}
namespace SP {
inline float Dot(const cSPVector3& a, const cSPVector3& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
}
namespace SP {
inline cSPVector3 Cross(const cSPVector3& a, const cSPVector3& b)
{
    return cSPVector3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}
}
namespace SP {
inline cSPVector3 Normalize(const cSPVector3& v)
{
    float len = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
    float inv = 1.0f / len;
    return cSPVector3(v.x * inv, v.y * inv, v.z * inv);
}
}
namespace SP {
cSPVector3 OrthogonalVector(const cSPVector3& v);  // 0x006985b0
}
namespace SP {
extern const uint32_t kEltMasks[];  // 0x0140d0ac: value mask per element size (index = byte count)
}
namespace SP {
struct IRefCounted { virtual int AddRef(); virtual int Release(); };
}
namespace SP {
struct cEltArrayRef_s0072_5e40 {
    int          mNumElts;    // +0
    uint8_t*     mData;       // +4
    uint16_t     mEltSize;    // +8
    uint16_t     mEltStride;  // +a
    IRefCounted* mDataRC;     // +c

    cEltArrayRef_s0072_5e40(int n, int eltSize)
        : mNumElts(n), mData(0), mEltSize((uint16_t)eltSize), mEltStride((uint16_t)eltSize), mDataRC(0) {}
    ~cEltArrayRef_s0072_5e40() { if (mDataRC) mDataRC->Release(); }

    template<class T> T& At(int i) const { return *(T*)(mData + mEltStride * i); }
};
}
namespace SP {
struct cIndexArrayRef_s0072_5e40 : cEltArrayRef_s0072_5e40 {
    uint32_t Index(int i) const { return *(uint32_t*)(mData + mEltStride * i) & kEltMasks[mEltSize]; }
};
}
namespace SP {
void AllocateEltArray(cEltArrayRef_s0072_5e40& a);  // 0x00720070
}
namespace SP {
struct cMDElementArray_s0072_5e40 {       // 0x20
    int mSemantic, mNumber, mType, mClass;
    cEltArrayRef_s0072_5e40 mArray;       // +0x10
};
}
namespace SP {
struct cMDFormatEntry_s0072_5e40 { short mElts; short mIndices; };
}
namespace SP {
struct cMDSection_s0072_5e40 {            // 0x8c (retail)
    uint32_t pad0[5];
    cMDFormatEntry_s0072_5e40* mFormat;   // +0x14 (fixed_vector mpBegin)
    uint32_t pad18[11];
    cIndexArrayRef_s0072_5e40* mEltIndices;  // +0x44 (fixed_vector mpBegin)
    uint32_t pad48[17];
};
}
namespace SP {
struct cMeshData_s0072_5e40 {
    uint32_t pad0[2];
    cMDElementArray_s0072_5e40* mEltArrays;  // +0x08
    uint32_t padc[4];
    cMDSection_s0072_5e40* mSections;        // +0x1c
};
}
namespace SP {
int  FindFormatEntry(cMeshData_s0072_5e40* mesh, int section, int semantic, int number, int flags);   // 0x0071e090
}
namespace SP {
int  AddEltArray(cMeshData_s0072_5e40* mesh, int semantic, int number, int type, int cls, const cEltArrayRef_s0072_5e40& a);  // 0x0071f0f0
}
namespace SP {
void AddSectionElement(cMeshData_s0072_5e40* mesh, int section, int eltArray, const cIndexArrayRef_s0072_5e40& idx);      // 0x0071f040
}
namespace SP {
inline void* SpAllocate(uint32_t n)
{
    return FUN_00f473a0(n, "Graphics", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
}
}
namespace SP {
inline void SpFree(void* p)
{
    if (p && ((int*)p)[-1] != 0)
        FUN_00f47380(p);
}
}
namespace SP {
struct UIntVector {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    uint32_t  mAllocator[2];

    __forceinline explicit UIntVector(uint32_t n)
    {
        mpBegin = n ? (uint32_t*)SpAllocate(n * sizeof(uint32_t)) : 0;
        mpCapacity = mpBegin + n;
        uint32_t* cur = mpBegin;
        for (uint32_t k = n; k > 0; --k)
            *cur++ = 0;
        mpEnd = mpBegin + n;
    }
    ~UIntVector() { SpFree(mpBegin); }
    uint32_t& operator[](int i) { return mpBegin[i]; }
};
}
namespace SP {
struct forward_iterator_tag { forward_iterator_tag() {} };
}
namespace SP {
inline cSPVector2* CopyV2(cSPVector2* first, cSPVector2* last, cSPVector2* dest)
{
    for (; first != last; ++first, ++dest)
        *dest = *first;
    return dest;
}
}
namespace SP {
struct Vector2Vector {
    cSPVector2* mpBegin;
    cSPVector2* mpEnd;
    cSPVector2* mpCapacity;
    uint32_t    mAllocator[2];

    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    void DoInsertValues(cSPVector2* position, uint32_t n, const cSPVector2& value);       // 0x00479830
    void DoInsertFromIterator(cSPVector2* position, const cSPVector2* first, const cSPVector2* last,
                              forward_iterator_tag);                                       // 0x005107d0
    cSPVector2* erase(cSPVector2* first, cSPVector2* last)
    {
        CopyV2(last, mpEnd, first);
        mpEnd -= (last - first);
        return first;
    }
    void resize(uint32_t n)
    {
        if (n > size())
            DoInsertValues(mpEnd, n - size(), cSPVector2());
        else
            erase(mpBegin + n, mpEnd);
    }
    void insert(cSPVector2* position, const cSPVector2* first, const cSPVector2* last)
    {
        DoInsertFromIterator(position, first, last, forward_iterator_tag());
    }
};
}
namespace SP {
void RemoveDuplicatePoints(Vector2Vector* v);                                     // 0x00721240
}
namespace SP {
void FindConvexHull(const cSPVector2* pts, int n, Vector2Vector* out);            // 0x007247c0
}
namespace SP {
void ComputeBounds(Vector2Vector* v, cSPVector2* bmin, cSPVector2* bmax);         // 0x00720920
}
namespace SP {
void FindBestRectAxis(const cSPVector2* pts, int n, cSPVector2* bmin, cSPVector2* bmax,
                      cSPVector2* axis);                                           // 0x00721340
}
namespace SP {
struct cClusterInfo_s0072_5e40 {
    int        mNumFaces;          // +0x00
    cSPVector3 mNormal;            // +0x04
    cSPVector3 mCentre;            // +0x10
    float      mArea;              // +0x1c
    float      mProjArea;          // +0x20
    float      mTexArea;           // +0x24
    cSPVector2 mMinUV;             // +0x28
    cSPVector2 mMaxUV;             // +0x30
    int        mFacesStart;        // +0x38
    int        mFacesEnd;          // +0x3c
    int        mIndicesStart;      // +0x40
    int        mIndicesEnd;        // +0x44
    int        mBorderIndicesStart;// +0x48
    int        mBorderIndicesEnd;  // +0x4c
    Vector2Vector mBoundaryCoords; // +0x50
};
}
namespace SP {
template<class T> inline const T& Max(const T& a, const T& b) { return (a < b) ? b : a; }
}
namespace SP {
struct cMeshClusterer_s0072_5e40 {
    void*         vfptr;               // +0x00
    int           mRefCount;           // +0x04
    cMeshData_s0072_5e40*    mMeshData;           // +0x08
    cClusterInfo_s0072_5e40* mClusterInfo;        // +0x0c (vector mpBegin)
    uint32_t      pad10[4];
    cEltArrayRef_s0072_5e40  mClusterIndices;     // +0x20 (cEltArrayRefT<unsigned int>)
    int           mNumClusterElements; // +0x30
    cEltArrayRef_s0072_5e40  mClusterFaces;       // +0x34 (cEltArrayRefT<unsigned int>)
    int           mSection;            // +0x44
    uint32_t      pad48[16];
    int           mNumClusters;        // +0x88

    void Prepare();                    // 0x00723140
    void AssignCharts(int texCoordSet, bool normalize, bool alignToBoundary);
};
}
// ---- items of slice s00725e40 end

// ---- items of slice s00728c90 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace UV {
struct Vec2 { float x, y; };                       // POD: copies go through integer registers
}
namespace UV {
extern Vec2 g_Vec2Zero;                            // 0x0162ae9c
}
namespace UV {
struct Vec2Vec {                                   // eastl::vector<cSPVector2, sp_vector_allocator> (0x14)
    Vec2* mpBegin;
    Vec2* mpEnd;
    Vec2* mpCapacity;
    int   alloc[2];
    void Assign(const Vec2Vec& o);                                 // 0x00722ba0 (ret 4)
    void DoInsertValues(Vec2* pos, unsigned n, const Vec2& v);     // 0x00479830 (ret 0xc)
    inline void erase(Vec2* first, Vec2* last)
    {
        Vec2* dst = first;
        for (Vec2* src = last; src != mpEnd; ++src, ++dst)
            *dst = *src;
        mpEnd -= (last - first);
    }
    inline void clear() { erase(mpBegin, mpEnd); }
    inline void resize(unsigned n, const Vec2& v)
    {
        unsigned cur = (unsigned)(mpEnd - mpBegin);
        if (n > cur) DoInsertValues(mpEnd, n - cur, v);
        else         erase(mpBegin + n, mpEnd);
    }
};
}
namespace UV {
struct ClusterInfo {                               // 0x64
    int   numFaces;                                // +0
    float nx, ny, nz;                              // +4 +8 +0xc
    float cx, cy, cz;                              // +0x10
    float area;                                    // +0x1c
    float projArea;                                // +0x20
    float texArea;                                 // +0x24
    Vec2  minUV;                                   // +0x28
    Vec2  maxUV;                                   // +0x30
    int   pad38[2];
    int   indicesStart, indicesEnd;                // +0x40 +0x44
    int   pad48[2];
    Vec2Vec boundary;                              // +0x50
};
}
namespace UV {
struct Chart {                                     // SP::cTextureChart, 0x68
    int     meshIndex;                             // +0
    float   texArea;                               // +4
    float   primArea;                              // +8
    int     texStart, texEnd;                      // +0xc +0x10
    Vec2Vec boundaries;                            // +0x14
    Vec2    texBound;                              // +0x28
    char    flag;                                  // +0x30
    char    pad31[3];
    int     rest[13];                              // +0x34 horizons etc.
};
}
namespace UV {
void __stdcall DestroyChartRange(Chart* first, Chart* last);       // 0x00721910
}
namespace UV {
struct ChartVec_s0072_8c90 {
    Chart* mpBegin; Chart* mpEnd; Chart* mpCapacity; int alloc[2];
    ChartVec_s0072_8c90() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~ChartVec_s0072_8c90()
    {
        DestroyChartRange(mpBegin, mpEnd);
        if (mpBegin && ((int*)mpBegin)[-1]) operator_delete__(mpBegin);
    }
    void reserve(unsigned n);                      // 0x00728270 (ret 4)
    void push_back0();                             // 0x007289a0 (default-construct one at the end)
};
}
namespace UV {
struct ChartRect {                                 // 0x34, element of the rect-pack list
    int   a, b;
    float prim;
    int   mesh;
    Vec2  minUV, maxUV;
    float w, h;
    float g0; int g1; float g2;                    // never written before the copy
    ChartRect() {}
    ChartRect(int ia, int ib, float p, int m, Vec2 mn, Vec2 mx, float ww, float hh)
        : a(ia), b(ib), prim(p), mesh(m), minUV(mn), maxUV(mx), w(ww), h(hh) {}
    ChartRect(const ChartRect& o)
        : a(o.a), b(o.b), prim(o.prim), mesh(o.mesh), minUV(o.minUV), maxUV(o.maxUV),
          w(o.w), h(o.h), g0(o.g0), g1(o.g1), g2(o.g2) {}
};
}
namespace UV {
struct RectVec {
    ChartRect* mpBegin; ChartRect* mpEnd; ChartRect* mpCapacity; int alloc[2];
    RectVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~RectVec() { if (mpBegin && ((int*)mpBegin)[-1]) operator_delete__(mpBegin); }
    void DoInsertValue(ChartRect* pos, const ChartRect& v);        // 0x007222f0 (ret 8)
    inline void push_back(const ChartRect& v)
    {
        if (mpEnd < mpCapacity) { ::new (mpEnd++) ChartRect(v); }
        else DoInsertValue(mpEnd, v);
    }
};
}
namespace UV {
struct MeshClusterer {                             // 0x90 (retail)
    MeshClusterer();                               // 0x00722010
    virtual ~MeshClusterer();                      // 0x007220c0
    int          rc;
    void*        meshData;
    ClusterInfo* cBegin;                           // +0xc
    ClusterInfo* cEnd;                             // +0x10
    ClusterInfo* cCap;
    uint32_t     pad[30];
    void Cluster(void* mesh, float f);             // 0x00728af0 (ret 8)
    void AssignCharts(int a, int b, int c);        // 0x00725e40 (ret 0xc)
};
}
namespace UV {
struct PtrVec { void** mpBegin; void** mpEnd; };
}
namespace UV {
struct ClusterMap {                                // 0x264
    ClusterMap();                                  // 0x006dffc0
    ~ClusterMap();                                 // 0x00724700
    char pad[0x274];
    void Build(PtrVec* meshes);                    // 0x006e0ea0 (ret 4)
    void AddCluster(Chart* c);                     // 0x006dfc30 (ret 4)
    void Pack(int mode);                           // 0x006e04d0 (ret 4)
};
}
namespace UV {
struct MeshXform {                                 // per-mesh transform info, 0x38
    unsigned flags;                                // +0
    char  pad4[0xc];
    float scale;                                   // +0x10
    char  pad14[8];
    float vx;                                      // +0x1c
    char  pad20[8];
    float vy;                                      // +0x28
    char  pad2c[8];
    float vz;                                      // +0x34
};
}
namespace UV {
struct PropList { int GetIntProperty(unsigned id); };              // 0x006a2660 (ret 4)
}
namespace UV {
extern PropList* g_AppProps;                                       // 0x015fd918
}
namespace UV {
void __cdecl ThreadSleep(const unsigned& t);                       // 0x00921df0
}
namespace UV {
void __cdecl RectPackCharts(PtrVec* meshes, RectVec* rects, float total, int size);   // 0x006e09d0
}
namespace UV {
void __cdecl FinishMesh(void* mesh);                               // 0x00735a90
}
// ---- items of slice s00728c90 end

// ---- items of slice s007249f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int   FUN_0071ddc0(void* p, int a, int b, int c, int d);   // 0x71ddc0
extern "C" int   FUN_0071e040(void* p, int idx, int id);              // 0x71e040
extern "C" void  FUN_004cd3c0(void* vec, int n);                      // 0x4cd3c0 (vector<int>::resize)
extern "C" void  FUN_004cea40(void* end, int n, void* tag);           // vector<int>::DoInsertValues
extern "C" void  FUN_007201d0(void* desc, void* mesh);
extern "C" void  FUN_004558a0(void* vec, void* pos, void* val);      // vector<unsigned>::DoInsertValue
extern "C" void  FUN_0071ee10(void* p, void* out, int idx, int a, int b); // SP::FindPrimitives
extern "C" void  FUN_00921df0(void* ms);                              // EA::Thread::ThreadSleep
extern "C" void  FUN_0011e0744(void* pos, int n, int val);            // vector<bool>::DoInsertValue
extern "C" void  FUN_0073a4b0(void* p);                               // vector<cQuadric>::resize
struct RefObj_s0072_49f0 {
    virtual void AddRef();
    virtual void Release();
};
struct VertEntry {
    int      x;    // +0
    int      y;    // +4
    int16_t  fmt;  // +8   (4 = int region data, 2 = ushort region data)
    uint16_t stride;// +0xa (bytes between region entries)
    RefObj_s0072_49f0*  ref;  // +0xc
};
struct MeshRec {
    uint32_t  count0;    // +0x00
    uint16_t* pData;     // +0x04
    int16_t   fmt;       // +0x08
    uint16_t  stride;    // +0x0a
    RefObj_s0072_49f0*   ref1;      // +0x0c
    uint32_t  count1;    // +0x10
    int*      pIdxTable; // +0x14
    char      pad_18[0x2c];
    void*     pVertBase; // +0x44
    char      pad_48[0x44];
};
struct MeshContext {
    char      pad0[8];
    char*     pNodeArray;   // +0x08 (stride 0x20)
    char      pad_c[0x10];
    char*     pMeshes;      // +0x1c
    char*     pMeshesEnd;   // +0x20
    char      pad_24[0xc];
    char*     pPrims;       // +0x30 (stride 0x14)
};
struct IntVec { int* mpBegin; int* mpEnd; int* mpCap; };
// ---- items of slice s007249f0 end

// ---- items of slice s00728020 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void FUN_00726c20(void* p, float f, int one, void* p4);   // 0x726c20
extern "C" void FUN_00725130(void* p);                               // 0x725130
extern "C" void FUN_00735a90(void* p);                               // 0x735a90
extern "C" void FUN_00737ef0(void* p);                               // 0x737ef0
struct MeshRec_s0072_8020 { char pad[0x8c]; };
struct MeshCtx {
    char     pad0[0x1c];
    MeshRec_s0072_8020* begin;   // +0x1c
    MeshRec_s0072_8020* end;     // +0x20
};
// ---- items of slice s00728020 end

// ---- items of slice s00726c20 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file, int line); // 0x00f473a0
struct cSPVector3_s0072_6c20 {
  float x, y, z;
  cSPVector3_s0072_6c20() {}
  cSPVector3_s0072_6c20(const cSPVector3_s0072_6c20& v) : x(v.x), y(v.y), z(v.z) {}
};
__forceinline int RoundToInt(float f) { __asm cvtss2si eax, f }
namespace EA {
namespace COM {
class IRefCount_s0072_6c20 {
 public:
  virtual int AddRef();
  virtual int Release();
};  // namespace COM
}
}
namespace EA {
template <typename T>
class AutoRefCount_s0072_6c20 {
 public:
  T* mpObject;
  AutoRefCount_s0072_6c20() : mpObject(0) {}
  AutoRefCount_s0072_6c20(const AutoRefCount_s0072_6c20& x) : mpObject(x.mpObject) {
    if (mpObject)
      mpObject->AddRef();
  }
  ~AutoRefCount_s0072_6c20() {
    if (mpObject)
      mpObject->Release();
  }
  AutoRefCount_s0072_6c20& operator=(T* pObject) {
    if (pObject != mpObject) {
      T* const pTemp = mpObject;
      if (pObject)
        pObject->AddRef();
      mpObject = pObject;
      if (pTemp)
        pTemp->Release();
    }
    return *this;
  }
  AutoRefCount_s0072_6c20& operator=(const AutoRefCount_s0072_6c20& x) { return operator=(x.mpObject); }
};
}
namespace EA {
namespace Thread {
typedef unsigned int ThreadTime;
}
}
namespace EA {
namespace Thread {
void ThreadSleep(const ThreadTime& timeRelative);  // 0x00921df0
}
}
namespace eastl {
struct sp_vector_allocator_s0072_6c20 {
  uint32_t mName[2];
  sp_vector_allocator_s0072_6c20() {}
};
}
namespace eastl {
template <typename T>
class vector_s0072_6c20 {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  sp_vector_allocator_s0072_6c20 mAllocator;
  int size() const { return (int)(mpEnd - mpBegin); }
  T& operator[](int i) { return mpBegin[i]; }
  void DoInsertValue(T* position, const T& value);
  void push_back(const T& value) {
    if (mpEnd < mpCapacity)
      ::new (mpEnd++) T(value);
    else
      DoInsertValue(mpEnd, value);
  }
};
}
namespace eastl {
template <typename T, int N>
class fixed_vector_s0072_6c20 {
 public:
  T* mpBegin;          // +0x00
  T* mpEnd;            // +0x04
  T* mpCapacity;       // +0x08
  uint32_t mOverflow;  // +0x0c
  T* mpPoolBegin;      // +0x10
  uint32_t mPad;       // +0x14
  uint32_t mBuffer[N * sizeof(T) / 4];  // +0x18 (aligned_buffer)

  fixed_vector_s0072_6c20() {
    mpPoolBegin = (T*)mBuffer;
    mpBegin = mpEnd = (T*)mBuffer;
    mpCapacity = (T*)mBuffer + N;
  }
  explicit fixed_vector_s0072_6c20(int n);  // fixed_vector<int,256>: 0x00726900
  ~fixed_vector_s0072_6c20() {
    if (mpBegin && mpBegin != mpPoolBegin)
      operator delete[](mpBegin);
  }
  int size() const { return (int)(mpEnd - mpBegin); }
  T& operator[](int i) { return mpBegin[i]; }
  void DoInsertValue(T* position, const T& value);
  void push_back(const T& value) {
    if (mpEnd < mpCapacity)
      ::new (mpEnd++) T(value);
    else
      DoInsertValue(mpEnd, value);
  }
};
}
namespace eastl {
struct true_type {};
}
namespace eastl {
template <typename K, typename V>
struct pair_s0072_6c20 {
  K first;
  V second;
  pair_s0072_6c20(const K& k, const V& v) : first(k), second(v) {}
};
}
namespace eastl {
template <typename K, typename V>
class hash_map_s0072_6c20 {
 public:
  typedef pair_s0072_6c20<const K, V> value_type;
  struct node_type {
    value_type mValue;
    node_type* mpNext;
  };
  struct iterator {
    node_type* mpNode;
    node_type** mpBucket;
    iterator() {}
    iterator(node_type** pBucket) : mpNode(*pBucket), mpBucket(pBucket) {}
    iterator(const iterator& x) : mpNode(x.mpNode), mpBucket(x.mpBucket) {}
    bool operator!=(const iterator& x) const { return mpNode != x.mpNode; }
    value_type* operator->() const { return &mpNode->mValue; }
  };
  struct insert_return_type {
    iterator first;
    bool second;
  };

  node_type** mpBucketArray;   // +0x00
  uint32_t mnBucketCount;      // +0x04
  uint32_t mnElementCount;     // +0x08
  float mfMaxLoadFactor;       // +0x0c
  float mfGrowthFactor;        // +0x10
  uint32_t mnNextResize;       // +0x14

  hash_map_s0072_6c20() {
    mfMaxLoadFactor = 1.0f;
    mfGrowthFactor = 2.0f;
    mnBucketCount = 1;
    mpBucketArray = (node_type**)&gpEmptyBucketArray[0];
    mnElementCount = 0;
    mnNextResize = 0;
  }
  ~hash_map_s0072_6c20() {
    DoFreeNodes(mpBucketArray, mnBucketCount);
    mnElementCount = 0;
    if (mnBucketCount > 1)
      operator delete[](mpBucketArray);
  }
  iterator end() { return iterator(mpBucketArray + mnBucketCount); }
  iterator find(const K& k);                                                   // 0x00721bb0
  insert_return_type DoInsertValue(const value_type& value, true_type tag);  // 0x00721c30
  void DoFreeNodes(node_type** pBucketArray, uint32_t n);                    // 0x007611f0
  V& operator[](const K& k) {
    iterator it = find(k);
    if (it != end())
      return it->second;
    return DoInsertValue(value_type(k, V()), true_type()).first->second;
  }
  static void* gpEmptyBucketArray[2];  // 0x0154df28
};
}
namespace SP {
enum tQuantizeType { kQuantizePositionOnly = 0, kQuantizePositionClasses = 1, kQuantizeAll = 2 };
}
namespace SP {
struct tMDShort4_s0072_6c20 { short m0, m1, m2, m3; };
}
namespace SP {
struct tMDUByte4_s0072_6c20 { uint8_t m0, m1, m2, m3; };
}
namespace SP {
struct cEltArrayRef_s0072_6c20 {
  int mNumElts;                                  // +0x0
  uint8_t* mData;                                // +0x4
  uint16_t mEltSize;                             // +0x8
  uint16_t mEltStride;                           // +0xa
  EA::AutoRefCount_s0072_6c20<EA::COM::IRefCount_s0072_6c20> mDataRC;  // +0xc
  cEltArrayRef_s0072_6c20(int eltSize) : mNumElts(0), mData(0), mEltSize((uint16_t)eltSize), mEltStride((uint16_t)eltSize) {}
  int size() const { return mNumElts; }
};
}
namespace SP {
template <typename T>
struct cEltArrayRefT_s0072_6c20 : public cEltArrayRef_s0072_6c20 {
  cEltArrayRefT_s0072_6c20() : cEltArrayRef_s0072_6c20(sizeof(T)) {}
  cEltArrayRefT_s0072_6c20(const cEltArrayRef_s0072_6c20& r) : cEltArrayRef_s0072_6c20(r) {}
  cEltArrayRefT_s0072_6c20& operator=(const cEltArrayRef_s0072_6c20& r) {
    cEltArrayRef_s0072_6c20::operator=(r);
    return *this;
  }
  T& operator[](int i) { return *(T*)(mData + i * mEltStride); }
};
}
namespace SP {
template <>
struct cEltArrayRefT_s0072_6c20<int> : public cEltArrayRef_s0072_6c20 {
  cEltArrayRefT_s0072_6c20(const cEltArrayRef_s0072_6c20& r);
  int& operator[](int i) { return *(int*)(mData + i * mEltStride); }
};
}
namespace SP {
struct cIndexArrayRef_s0072_6c20 : public cEltArrayRef_s0072_6c20 {
  cIndexArrayRef_s0072_6c20() : cEltArrayRef_s0072_6c20(0) {}
  int& Int(int i) { return *(int*)(mData + i * mEltStride); }
  uint16_t& UShort(int i) { return *(uint16_t*)(mData + i * mEltStride); }
};
}
namespace SP {
template <typename T>
struct cEltArrayT : public EA::COM::IRefCount_s0072_6c20 { private:
 public:
  void* mpInterfaceVtbl;                 // +0x04
  int mRefCount;                         // +0x08
  eastl::vector_s0072_6c20<T> mEltData;             // +0x0c
  uint32_t mField20;                     // +0x20
  cEltArrayT();                          // 0x006c3510
  cEltArrayRefT_s0072_6c20<T> AsRef();              // 0x007217c0
};
}
namespace SP {
struct cMDElementArray_s0072_6c20 {
  int mSemantic;        // +0x00
  int mNumber;          // +0x04
  int mType;            // +0x08
  int mClass;           // +0x0c
  cEltArrayRef_s0072_6c20 mArray;  // +0x10
};
}
namespace SP {
struct cMDFormatEntry_s0072_6c20 {
  short mElts;     // +0x0
  short mIndices;  // +0x2
};
}
namespace SP {
struct cMDSection_s0072_6c20 {
  cIndexArrayRef_s0072_6c20 mVertIndices;                       // +0x00
  int mNumVertices;                                  // +0x10
  eastl::fixed_vector_s0072_6c20<cMDFormatEntry_s0072_6c20, 6> mFormat;    // +0x14
  eastl::fixed_vector_s0072_6c20<cIndexArrayRef_s0072_6c20, 3> mEltIndices;  // +0x44
};
}
namespace SP {
class cMeshData_s0072_6c20 {
 public:
  void* mpVtbl;                                // +0x00
  int mRefCount;                               // +0x04
  eastl::vector_s0072_6c20<cMDElementArray_s0072_6c20> mEltArrays;   // +0x08
  eastl::vector_s0072_6c20<cMDSection_s0072_6c20> mSections;         // +0x1c
};
}
namespace SP {
struct cQuantizeClass {
  float mScale;        // +0x0
  bool mUseBoneClass;  // +0x4
  uint8_t mFlagB;      // +0x5
  uint8_t mNormalMask; // +0x6
  uint8_t mPad;
  cQuantizeClass() : mScale(1.0f), mUseBoneClass(true), mFlagB(0), mNormalMask(0) {}
};
}
namespace SP {
struct cDecCellID {
  int m[3];
  cDecCellID(int x, int y, int z) {
    m[0] = x;
    m[1] = y;
    m[2] = z;
  }
};
}
namespace SP {
void PushIndices(cMeshData_s0072_6c20* meshData);                                                  // 0x007366e0
}
namespace SP {
int FindEltArrayIndex(cMeshData_s0072_6c20* meshData, int semantic, int number, int type, int classes);  // 0x0071ddc0
}
namespace SP {
int FindSectionEltIndex(cMeshData_s0072_6c20* meshData, int section, int eltArrayIndex);           // 0x0071e040
}
namespace SP {
void CreateArray(const cIndexArrayRef_s0072_6c20& src, cIndexArrayRef_s0072_6c20& dst);                       // 0x007201b0
}
    void* operator new(unsigned int, char*, int, unsigned int, char*, int); // 0x00f473a0
// ---- items of slice s00726c20 end

// ---- items of slice s0071e390 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedExchange)
struct IRef {                       // virtual AddRef/Release (+0, +4)
    virtual int AddRef();
    virtual int Release();
};
struct Handle {                     // 16-byte handle member of a vertex record
    int mF0, mF4;                   // +0x00, +0x04
    short mS8, mSA;                 // +0x08, +0x0a
    IRef* mpRef;                    // +0x0c (refcounted)
    void Assign(const Handle* src);                                          // 0x00424f70
};
struct Vertex20 {                   // 0x20 bytes
    unsigned mA, mB, mC, mD;        // +0x00 .. +0x0c
    Handle mHandle;                 // +0x10
};
struct KeyPair {
    short mKey;
    short mVal;
};
struct VecKeyPair {
    KeyPair* mpBegin; KeyPair* mpEnd; KeyPair* mpCapacity;
    void DoInsertValue(KeyPair* position, const KeyPair& v);    // 0x00476fe0
    void push_back(const KeyPair& v)
    {
        if (mpEnd < mpCapacity) {
            KeyPair* p = mpEnd++;
            if (p)
                *p = v;
        } else {
            DoInsertValue(mpEnd, v);
        }
    }
};
struct cFaceCluster_s0071_e390 {               // 0x14 bytes
    int mKind;                      // 4 by default
    int m1, m2, m3, m4;
    cFaceCluster_s0071_e390() : mKind(4), m1(0), m2(0), m3(0), m4(0) {}
};
cFaceCluster_s0071_e390* CopyFC(cFaceCluster_s0071_e390* first, cFaceCluster_s0071_e390* last, cFaceCluster_s0071_e390* dest);       // 0x00951bf0
struct VecFC {
    cFaceCluster_s0071_e390* mpBegin; cFaceCluster_s0071_e390* mpEnd; cFaceCluster_s0071_e390* mpCapacity;
    void DoInsertValues(cFaceCluster_s0071_e390* position, unsigned n, const cFaceCluster_s0071_e390* value);   // 0x0071ea40
    void resize(unsigned n);                                                              // 0x0071efa0
};
struct V16 {                        // vector of 16-byte records (begin, end, ...)
    char* mpBegin;
    char* mpEnd;
    void Notify(int arg);           // 0x006da2e0
    int size() const { return (int)(mpEnd - mpBegin) >> 4; }
};
struct EntryFor70 {                 // 0x8c bytes
    char pad_00[0x14];
    VecKeyPair mPairs;              // +0x14
    char pad_20[0x44 - 0x20];
    V16 mRecs;                      // +0x44
    char pad_4c[0x8c - 0x4c];
};
struct MeshEntries {
    char pad_00[0x1c];
    EntryFor70* mpEntries;          // +0x1c
};
int FindPairIndex(MeshEntries* m, int entry, int key);              // 0x0071e040
struct VertexKey {                  // temporary built by FUN_00469500 (5 args)
    unsigned mA, mB, mC, mD;
    Handle mHandle;
    VertexKey(unsigned a, unsigned b, unsigned c, unsigned d, unsigned e);   // 0x00469500
    ~VertexKey() { if (mHandle.mpRef) mHandle.mpRef->Release(); }
};
struct VertexVec {
    char* mpBegin;
    char* mpEnd;
    void push_back(const VertexKey& v);                                      // 0x0041f7d0
};
struct VertexMesh {
    char pad_00[8];
    VertexVec mVerts;               // +0x08
};
int FindVertexIndex(VertexMesh* m, unsigned a, unsigned b, unsigned c, int d);   // 0x0071ddc0
inline void CopyVertex(Vertex20* dst, const VertexKey& src)
{
    dst->mA = src.mA;
    dst->mB = src.mB;
    dst->mC = src.mC;
    dst->mD = src.mD;
    dst->mHandle.Assign(&src.mHandle);
}
// ---- items of slice s0071e390 end

// @ 0x0071efa0
void VecFC::resize(unsigned n)
{
    if (n > (unsigned)(mpEnd - mpBegin)) {
        cFaceCluster_s0071_e390 v;
        DoInsertValues(mpEnd, n - (unsigned)(mpEnd - mpBegin), &v);
    } else {
        cFaceCluster_s0071_e390* first = mpBegin + n;
        cFaceCluster_s0071_e390* last = mpEnd;
        CopyFC(last, mpEnd, first);
        mpEnd -= (last - first);
    }
}

// @ 0x0071f040
void SetEntryKey(MeshEntries* m, int entry, int key, int arg)
{
    EntryFor70* e = &m->mpEntries[entry];
    int idx = FindPairIndex(m, entry, key);
    V16& recs = e->mRecs;
    if (idx >= 0) {
        e->mPairs.mpBegin[idx].mVal = (short)recs.size();
        recs.Notify(arg);
        return;
    }
    KeyPair v;
    v.mKey = (short)key;
    v.mVal = (short)recs.size();
    e->mPairs.push_back(v);
    recs.Notify(arg);
}

// @ 0x0071f0f0
int AddVertex(VertexMesh* mesh, unsigned a, unsigned b, unsigned c, unsigned d, unsigned e)
{
    int idx = FindVertexIndex(mesh, a, b, c, 0xe);
    if (idx < 0) {
        idx = (int)(mesh->mVerts.mpEnd - mesh->mVerts.mpBegin) >> 5;
        mesh->mVerts.push_back(VertexKey(a, b, c, d, e));
    } else {
        CopyVertex((Vertex20*)(mesh->mVerts.mpBegin + idx * 0x20), VertexKey(a, b, c, d, e));
    }
    return idx;
}

// @ 0x00720070
void Obj15_20070(void* a)
{ (void)a; }

// @ 0x007200f0
void Obj15_200f0(void* a, void* b, void* c)
{ (void)a; (void)b; (void)c; }

// @ 0x007201b0
void Obj15_copy(const Obj15* src, Obj15* dst)
{
    dst->m0 = src->m0;
    dst->m8 = src->m8;
    Obj15_Init(dst);
}

// @ 0x007201d0
void Obj15_copyAssign(const Obj15* src, Obj15* dst)
{
    dst->m0 = src->m0;
    dst->m8 = src->m8;
    Obj15_Init(dst);
    Obj15_Assign((void*)src, dst, 0);
}

// @ 0x00720290
void MeshAdj::AddTri(int a, int n, int c, int* in, Pair16* out, int d)
{
    Rec18* rec = &mRecords[a];
    rec->f0 = in;
    rec->f1 = out;
    rec->f2 = 0;
    rec->f3 = d;
    rec->f4 = n;
    rec->f5 = c;

    int counter = 0;
    int i6 = 0;
    if (n > 0) {
        do {
            int mod = rec->f5;
            i6 = counter + 1;
            int i7 = i6;
            if (i6 % mod == 0)
                i7 = i6 - mod;

            int idx = in[counter];
            out->first = -1;
            out->second = -1;

            Pair16* p = &mPairs[idx];
            int node = p->first;
            int lnk = p->second;

            bool inserted = false;
            while (node >= 0) {
                Rec18* q = &mRecords[node];
                if (q->f0[lnk] == in[i7] && (mFlag || a == node)) {
                    bool ok = true;
                    if (mCb != 0) {
                        int a2 = a;
                        int i72 = i7;
                        ok = mCb(mRecords, &node, &a2, mCbArg);
                    }
                    if (ok) {
                        int p0 = q->f1[lnk].first;
                        int p1 = q->f1[lnk].second;
                        p->first  = p0;
                        p->second = p1;
                        out->first = node;
                        out->second = lnk;
                        q->f1[lnk].first  = a;
                        q->f1[lnk].second = counter;
                        inserted = true;
                        break;
                    }
                }
                p = &q->f1[lnk];
                node = p->first;
                lnk  = p->second;
            }
            if (!inserted) {
                int idx2 = in[i7];
                out->first  = mPairs[idx2].first;
                out->second = mPairs[idx2].second;
                mPairs[idx2].first  = a;
                mPairs[idx2].second = counter;
            }
            out++;
            counter = i6;
        } while (i6 < c);
    }
}

// @ 0x00720590
uint32_t __stdcall HashVec(const float* v)
{
    int key[3];
    float f0 = *(float*)v + 192.0f;
    float f1 = *(float*)((const char*)v + 4) + 192.0f;
    float f2 = *(float*)((const char*)v + 8) + 192.0f;
    key[0] = (*(int*)&f0) + (int)0xBCC00000;
    key[1] = (*(int*)&f1) + (int)0xBCC00000;
    key[2] = (*(int*)&f2) + (int)0xBCC00000;
    uint32_t h = 0x811C9DC5;
    unsigned char* q = (unsigned char*)key;
    unsigned char* e = (unsigned char*)(key + 3);
    do {
        h *= 0x1000193;
        h ^= *q;
        q++;
    } while (q < e);
    return h;
}

// @ 0x00720620
void SP::cHeap::HeapifyDown(int i)
{
    SP::cHeapEntry** begin = mHeapEntries.mpBegin;
    int count = (int)(mHeapEntries.mpEnd - mHeapEntries.mpBegin);
    int child = i * 2 + 1;
    if (child < count) {
        do {
            int right = child + 1;
            if (right < count) {
                SP::cHeapEntry* l = begin[child];
                SP::cHeapEntry* r = begin[right];
                if (l->mCost > r->mCost)
                    child = right;
            }
            SP::cHeapEntry* e = begin[child];
            SP::cHeapEntry* p = begin[i];
            if (p->mCost <= e->mCost)
                return;
            int t = e->mHeapIndex;
            e->mHeapIndex = p->mHeapIndex;
            p->mHeapIndex = t;
            begin = mHeapEntries.mpBegin;
            SP::cHeapEntry* t2 = begin[child];
            begin[child] = begin[i];
            begin[i] = t2;
            i = child;
            child = i * 2 + 1;
            count = (int)(mHeapEntries.mpEnd - mHeapEntries.mpBegin);
        } while (child < count);
    }
}

// @ 0x007206b0
void SP::cHeap::HeapifyUp(int i)
{
    int parent = (i - 1) >> 1;
    if (parent < 0)
        return;
    do {
        SP::cHeapEntry* e = mHeapEntries.mpBegin[parent];
        SP::cHeapEntry* p = mHeapEntries.mpBegin[i];
        if (e->mCost <= p->mCost)
            return;
        int t = p->mHeapIndex;
        p->mHeapIndex = e->mHeapIndex;
        e->mHeapIndex = t;
        SP::cHeapEntry* t2 = mHeapEntries.mpBegin[i];
        mHeapEntries.mpBegin[i] = mHeapEntries.mpBegin[parent];
        mHeapEntries.mpBegin[parent] = t2;
        i = parent;
        parent = (i - 1) >> 1;
    } while (parent >= 0);
}

// @ 0x00720700
void cMeshClusterer::CalcError(cFaceCluster* a, cFaceCluster* b, float* out)
{
    float sumNx = a->mSumAreaNormal.x + b->mSumAreaNormal.x;
    float sumNy = a->mSumAreaNormal.y + b->mSumAreaNormal.y;
    float sumNz = a->mSumAreaNormal.z + b->mSumAreaNormal.z;
    float sumArea = a->mArea + b->mArea;
    float nsum = sumNx * sumNx + sumNy * sumNy + sumNz * sumNz;
    float la = sqrtf(a->mSumAreaNormal.x * a->mSumAreaNormal.x
                   + a->mSumAreaNormal.y * a->mSumAreaNormal.y
                   + a->mSumAreaNormal.z * a->mSumAreaNormal.z);
    float lb = sqrtf(b->mSumAreaNormal.x * b->mSumAreaNormal.x
                   + b->mSumAreaNormal.y * b->mSumAreaNormal.y
                   + b->mSumAreaNormal.z * b->mSumAreaNormal.z);
    float ls = sqrtf(nsum);
    if (ls < 1e-08f) {
        *out = 1000.0f;
        return;
    }
    if (la < 1e-08f || lb < 1e-08f) {
        *out = 0.0f;
        return;
    }
    float dot_ab = a->mSumAreaNormal.x * b->mSumAreaNormal.x
                 + a->mSumAreaNormal.y * b->mSumAreaNormal.y
                 + a->mSumAreaNormal.z * b->mSumAreaNormal.z;
    if (mCostType == 1) {
        *out = 1.0f - dot_ab / (lb * la);
        return;
    }
    if (mCostType != 2) {
        float da = (a->mSumAreaNormal.x * sumNx + a->mSumAreaNormal.y * sumNy
                  + a->mSumAreaNormal.z * sumNz) / (la * ls);
        float db = (b->mSumAreaNormal.x * sumNx + b->mSumAreaNormal.y * sumNy
                  + b->mSumAreaNormal.z * sumNz) / (lb * ls);
        *out = (((2.0f - da) - db) / ls) * sumArea;
        return;
    }
    {
        float r = dot_ab / (lb * la);
        *out = r;
        if (sumArea < 0.1f)
            *out = (r / 0.1f) * sumArea;
    }
}

// @ 0x00720920
void __cdecl MinMaxIndices(const float* const* v, int* minOut, int* maxOut)
{
    *maxOut = 0; maxOut[1] = 0;
    *minOut = 0; minOut[1] = 0;
    const float* p = v[0];
    int n = (int)((const char*)v[1] - (const char*)p) >> 3;
    float minX = p[0], minY = p[1];
    float maxX = minX, maxY = minY;
    for (int i = 1; i < n; i++) {
        float x = p[i * 2];
        float y = p[i * 2 + 1];
        if (x < minX) { minX = x; minOut[0] = i; }
        else if (x > maxX) { maxX = x; maxOut[0] = i; }
        if (y < minY) { minY = y; minOut[1] = i; }
        else if (y > maxY) { maxY = y; maxOut[1] = i; }
    }
}

// @ 0x00720b10
void Element68::Dtor()
{
    if (v48 != 0 && ((int*)v48)[-1] != 0)
        EASTL_allocator_deallocate(v48);
    if (v34 != 0 && ((int*)v34)[-1] != 0)
        EASTL_allocator_deallocate(v34);
    if (v14 != 0 && ((int*)v14)[-1] != 0)
        EASTL_allocator_deallocate(v14);
}

// @ 0x00720b60
void HashTable::Grow(uint32_t newSize)
{
    uint32_t size = newSize * 4;
    if (size == -4 && 0) {}
    char* dst = (char*)EASTL_allocator_allocate(size + 4, "Graphics", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    op_new_array(dst, 0, size);
    *(int*)(size + (int)dst) = -1;
    uint32_t i = 0;
    if (mCount != 0) {
        do {
            void* p = mBuckets[i];
            while (p != 0) {
                int* node = (int*)p;
                uint32_t h = (node[2] ^ node[1] ^ node[0]) % newSize;
                mBuckets[i] = (void*)node[4];
                node[4] = *(int*)(dst + h * 4);
                *(int**)(dst + h * 4) = node;
                p = mBuckets[i];
            }
            i++;
        } while (i < mCount);
    }
    if (mCount > 1)
        EASTL_allocator_deallocate(mBuckets);
    mBuckets = (void**)dst;
    mCount = newSize;
}

// @ 0x00720c20
Element68* __cdecl DestroyRange68(Element68* first, Element68* last, Element68* dst)
{
    if (first == last)
        return dst;
    do {
        if (first->v48 != 0 && ((int*)first->v48)[-1] != 0)
            EASTL_allocator_deallocate(first->v48);
        if (first->v34 != 0 && ((int*)first->v34)[-1] != 0)
            EASTL_allocator_deallocate(first->v34);
        if (first->v14 != 0 && ((int*)first->v14)[-1] != 0)
            EASTL_allocator_deallocate(first->v14);
        first += 1;
        dst += 1;
    } while (first != last);
    return dst;
}

// @ 0x00720c90
void __cdecl UninitCopyFace28(cFaceCluster** out, const cFaceCluster* first, const cFaceCluster* last, cFaceCluster* dst)
{
    *out = dst;
    while (first != last) {
        if (dst != 0) {
            dst->mSumAreaPoint.x = first->mSumAreaPoint.x;
            dst->mSumAreaPoint.y = first->mSumAreaPoint.y;
            dst->mSumAreaPoint.z = first->mSumAreaPoint.z;
            dst->mSumAreaNormal.x = first->mSumAreaNormal.x;
            dst->mSumAreaNormal.y = first->mSumAreaNormal.y;
            dst->mSumAreaNormal.z = first->mSumAreaNormal.z;
            dst->mFirstEdge = first->mFirstEdge;
            dst->mParentCluster = first->mParentCluster;
            dst->mPreviousDE = first->mPreviousDE;
        }
        first++;
        dst++;
    }
    *out = dst;
}

// @ 0x00720d10
void __cdecl FillFace28(cFaceCluster* dst, uint32_t n, const cFaceCluster* src)
{
    if (n == 0)
        return;
    do {
        if (dst != 0) {
            dst->mSumAreaPoint.x = src->mSumAreaPoint.x;
            dst->mSumAreaPoint.y = src->mSumAreaPoint.y;
            dst->mSumAreaPoint.z = src->mSumAreaPoint.z;
            dst->mSumAreaNormal.x = src->mSumAreaNormal.x;
            dst->mSumAreaNormal.y = src->mSumAreaNormal.y;
            dst->mSumAreaNormal.z = src->mSumAreaNormal.z;
            dst->mArea = src->mArea;
            dst->mFirstEdge = src->mFirstEdge;
            dst->mParentCluster = src->mParentCluster;
            dst->mPreviousDE = src->mPreviousDE;
        }
        n--;
        dst++;
    } while (n != 0);
}

// @ 0x00720d70
void __cdecl UninitCopyDual18(cDualEdge** out, const cDualEdge* first, const cDualEdge* last, cDualEdge* dst)
{
    *out = dst;
    while (first != last) {
        if (dst != 0)
            *dst = *first;
        first++;
        dst++;
    }
    *out = dst;
}

// @ 0x00720dd0
void* __cdecl MoveCopy34(void* first, void* last, void* dst)
{
    if (first == last)
        return dst;
    do {
        unsigned char* s = (unsigned char*)first;
        unsigned char* d = (unsigned char*)dst;
        if (dst != 0) {
            *(int*)(d + 0x00) = *(int*)(s + 0x00);
            *(int*)(d + 0x04) = *(int*)(s + 0x04);
            *(float*)(d + 0x08) = *(float*)(s + 0x08);
            *(int*)(d + 0x0c) = *(int*)(s + 0x0c);
            *(float*)(d + 0x10) = *(float*)(s + 0x10);
            *(float*)(d + 0x14) = *(float*)(s + 0x14);
            *(float*)(d + 0x18) = *(float*)(s + 0x18);
            *(float*)(d + 0x1c) = *(float*)(s + 0x1c);
            *(float*)(d + 0x20) = *(float*)(s + 0x20);
            *(float*)(d + 0x24) = *(float*)(s + 0x24);
            *(float*)(d + 0x28) = *(float*)(s + 0x28);
            *(int*)(d + 0x2c) = *(int*)(s + 0x2c);
            *(float*)(d + 0x30) = *(float*)(s + 0x30);
        }
        first = (unsigned char*)first + 0x34;
        dst = (unsigned char*)dst + 0x34;
    } while (first != last);
    return dst;
}

// @ 0x00720ea0
void* __cdecl CopyFace28(void* first, void* last, void* dst)
{
    if (first == last)
        return dst;
    do {
        unsigned char* s = (unsigned char*)first;
        unsigned char* d = (unsigned char*)dst;
        if (dst != 0) {
            *(float*)(d + 0x00) = *(float*)(s + 0x00);
            *(float*)(d + 0x04) = *(float*)(s + 0x04);
            *(float*)(d + 0x08) = *(float*)(s + 0x08);
            *(float*)(d + 0x0c) = *(float*)(s + 0x0c);
            *(float*)(d + 0x10) = *(float*)(s + 0x10);
            *(float*)(d + 0x14) = *(float*)(s + 0x14);
            *(float*)(d + 0x18) = *(float*)(s + 0x18);
            *(int*)(d + 0x1c) = *(int*)(s + 0x1c);
            *(int*)(d + 0x20) = *(int*)(s + 0x20);
            *(int*)(d + 0x24) = *(int*)(s + 0x24);
        }
        first = (unsigned char*)first + 0x28;
        dst = (unsigned char*)dst + 0x28;
    } while (first != last);
    return dst;
}

// @ 0x00720f40
void cMeshClusterer::MergeEdgeLists(int param_2, int param_3)
{
    cFaceCluster* faceBase = mFaceClusters.mpBegin;
    cFaceCluster* fa = &faceBase[param_2];
    cFaceCluster* fb = &faceBase[param_3];

    int e = fb->mFirstEdge;
    while (e >= 0) {
        int count = (int)(mDualEdges.mpEnd - mDualEdges.mpBegin);
        int q = e / count;
        int r = e % count;
        cDualEdge* de = &mDualEdges.mpBegin[r];
        int nxt = de->mNextEdges[q];
        faceBase[de->mClusters[q ^ 1]].mPreviousDE = 0;
        e = nxt;
    }

    int* plink = &fa->mFirstEdge;
    e = *plink;
    while (e >= 0) {
        int count = (int)(mDualEdges.mpEnd - mDualEdges.mpBegin);
        int q = e / count;
        int r = e % count;
        cDualEdge* de = &mDualEdges.mpBegin[r];
        e = de->mNextEdges[q];
        if (de->mHeapIndex < 0) {
            *plink = e;
        } else {
            int other = de->mClusters[q ^ 1];
            faceBase[other].mPreviousDE = de;
            CalcError(fa, &faceBase[other], (float*)de);
            int hi = de->mHeapIndex;
            plink = &de->mNextEdges[q];
            if (hi >= 1) {
                cHeapEntry* par = mEdgeHeap.mHeapEntries.mpBegin[(hi - 1) >> 1];
                if (par->mCost > de->mCost)
                    mEdgeHeap.HeapifyUp(hi);
                else
                    mEdgeHeap.HeapifyDown(hi);
            } else {
                mEdgeHeap.HeapifyDown(hi);
            }
        }
    }

    e = fb->mFirstEdge;
    *plink = e;
    int* plink2 = plink;
    while (e >= 0) {
        int count = (int)(mDualEdges.mpEnd - mDualEdges.mpBegin);
        int q = e / count;
        int r = e % count;
        cDualEdge* de = &mDualEdges.mpBegin[r];
        int hi = de->mHeapIndex;
        e = de->mNextEdges[q];
        int* pe = &de->mNextEdges[q];
        if (hi < 0) {
            *plink = e;
        } else if (faceBase[de->mClusters[q ^ 1]].mPreviousDE == 0) {
            de->mClusters[q] = param_2;
            CalcError(fa, &faceBase[de->mClusters[q ^ 1]], (float*)de);
            hi = de->mHeapIndex;
            plink = pe;
            plink2 = pe;
            if (hi >= 1) {
                cHeapEntry* par = mEdgeHeap.mHeapEntries.mpBegin[(hi - 1) >> 1];
                if (par->mCost > de->mCost)
                    mEdgeHeap.HeapifyUp(hi);
                else
                    mEdgeHeap.HeapifyDown(hi);
            } else {
                mEdgeHeap.HeapifyDown(hi);
            }
        } else {
            cHeapEntry** arr = mEdgeHeap.mHeapEntries.mpBegin;
            arr[hi] = arr[(int)(mEdgeHeap.mHeapEntries.mpEnd - arr) - 1];
            int hi2 = de->mHeapIndex;
            arr[hi2]->mHeapIndex = hi2;
            mEdgeHeap.mHeapEntries.mpEnd = (cHeapEntry**)((char*)mEdgeHeap.mHeapEntries.mpEnd - 4);
            mEdgeHeap.HeapifyDown(hi);
            de->mHeapIndex = -1;
            *plink2 = e;
            plink = plink2;
        }
    }
    *plink = -1;
}

// @ 0x00721240
void __cdecl SortFloatsByDist(void* v)
{
    float* p = *(float**)v;
    int n = (((int*)v)[1] - (int)p) >> 3;
    int minIdx = 0;
    float minv = *p;
    if (1 < n) {
        int i = 1;
        if (3 < n - 1) {
            float* q = p + 6;
            do {
                if (q[-4] < minv) { minIdx = i; minv = q[-4]; }
                if (q[-2] < minv) { minIdx = i + 1; minv = q[-2]; }
                if (*q < minv) { minIdx = i + 2; minv = *q; }
                if (q[2] < minv) { minIdx = i + 3; minv = q[2]; }
                i += 4;
                q += 8;
            } while (i < n - 3);
        }
        if (i < n) {
            float* q = p + i * 2;
            do {
                if (*q < minv) { minIdx = i; minv = *q; }
                i++;
                q += 2;
            } while (i < n);
        }
    }
    float tmp0 = p[0];
    float tmp1 = p[1];
    p[0] = p[minIdx * 2];
    p[1] = p[minIdx * 2 + 1];
    p[minIdx * 2] = tmp0;
    p[minIdx * 2 + 1] = tmp1;
    g_chartMinX = (*(float**)v)[0];
    g_chartMinY = (*(float**)v)[1];
    qsort((char*)*(float**)v + 8, n - 1, 8, ComparePairs);
}

// @ 0x00721340
void __cdecl ChartSolve(int verts, int n, int* a, int* b, float* out)
{
    float* v = (float*)verts;
    out[0] = 1.0f;
    out[1] = 0.0f;
    int idx[4];
    float d[8];
    idx[0] = a[0];
    idx[1] = b[0];
    idx[2] = a[1];
    idx[3] = b[1];
    for (int k = 0; k < 4; k++) {
        int j = (idx[k] + 1) % n;
        d[k * 2]     = v[j * 2]     - v[idx[k] * 2];
        d[k * 2 + 1] = v[j * 2 + 1] - v[idx[k] * 2 + 1];
    }
    float ax = 0.0f, ay = 1.0f;
    float bx = 1.0f, by = 0.0f;
    float best = 3.4028234663852886e+38f;
    float dy23 = v[idx[3] * 2 + 1] - v[idx[2] * 2 + 1];
    float dx01 = v[idx[1] * 2]     - v[idx[0] * 2];
    float maxd = dy23 > dx01 ? dy23 : dx01;
    for (;;) {
        if (!(ay > 0.0f)) {
            int* volatile keep = &idx[0];
            (void)keep;
            return;
        }
        int i;
        for (i = 0; i < 4; i++) {
            double len = sqrt((double)d[i * 2] * d[i * 2] + (double)d[i * 2 + 1] * d[i * 2 + 1]);
            if (len <= maxd * 0.0001)
                break;
            volatile float flen = (float)len;
            float finv;
            _mm_store_ss(&finv, _mm_div_ss(_mm_set_ss(1.0f), _mm_load_ss((const float*)&flen)));
            float inv = finv;
            d[i * 2]     *= inv;
            d[i * 2 + 1] *= inv;
        }
        if (i == 4) {
            float v0 = -(d[0] * ax + d[1] * ay);
            float v1 =   d[2] * ax + d[3] * ay;
            float v2 =   d[4] * bx + d[5] * by;
            float v3 = -(d[6] * bx + d[7] * by);
            int m;
            if (v0 > v1) {
                if (v0 > v2)
                    m = (v0 > v3) ? 0 : 3;
                else
                    m = (v2 > v3) ? 2 : 3;
            } else {
                if (v1 > v2)
                    m = (v1 > v3) ? 1 : 3;
                else
                    m = (v2 > v3) ? 2 : 3;
            }
            switch (m) {
            case 0:
                ax = -d[0]; ay = -d[1];
                bx = -d[1]; by =  d[0];
                break;
            case 1:
                ax =  d[2]; ay =  d[3];
                bx =  d[3]; by = -d[2];
                break;
            case 2:
                ax = -d[5]; ay =  d[4];
                bx =  d[4]; by =  d[5];
                break;
            default:
                ax =  d[7]; ay = -d[6];
                bx = -d[6]; by = -d[7];
                break;
            }
            float p1 = (v[idx[1] * 2] - v[idx[0] * 2]) * bx
                     + (v[idx[1] * 2 + 1] - v[idx[0] * 2 + 1]) * by;
            float p2 = (v[idx[3] * 2] - v[idx[2] * 2]) * ax
                     + (v[idx[3] * 2 + 1] - v[idx[2] * 2 + 1]) * ay;
            float prod = p1 * p2;
            if (prod < best) {
                best = prod;
                if (p1 < p2) {
                    out[0] = bx; out[1] = by;
                } else {
                    out[0] = ax; out[1] = ay;
                }
            }
            i = m;
        }
        int j = (idx[i] + 1) % n;
        int j2 = (j + 1) % n;
        d[i * 2]     = v[j2 * 2]     - v[j * 2];
        d[i * 2 + 1] = v[j2 * 2 + 1] - v[j * 2 + 1];
        idx[i] = j;
        if (!(bx > 0.0f)) {
            int* volatile keep = &idx[i];
            (void)keep;
            return;
        }
    }
}

// @ 0x007217c0
ChartRef* ChartVec::MakeChartRef(ChartRef* out)
{
    ChartVec* this_ = this;
    void** begin = this_->begin;
    out->mNumElts = (int)((char*)this_->end - (char*)begin) / 0xc;
    out->mEltStride = 0xc;
    out->mData = begin;
    out->mEltSize = 0xc;
    out->mOwner = this_;
    return out;
}

// @ 0x00721850
void ChartHash::GrowF(uint32_t newSize)
{
    uint32_t size = newSize * 4;
    char* dst = (char*)EASTL_allocator_allocate(size + 4, "Graphics", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    op_new_array(dst, 0, size);
    *(int*)(size + (int)dst) = -1;
    uint32_t i = 0;
    if (mCapacity != 0) {
        do {
            FChartNode* n = (FChartNode*)mBuckets[i];
            while (n != 0) {
                uint32_t h = HashVec(&n->kx) % newSize;
                mBuckets[i] = n->next;
                n->next = *(FChartNode**)(dst + h * 4);
                *(FChartNode**)(dst + h * 4) = n;
                n = (FChartNode*)mBuckets[i];
            }
            i++;
        } while (i < mCapacity);
    }
    if (mCapacity > 1)
        EASTL_allocator_deallocate(mBuckets);
    mBuckets = (void**)dst;
    mCapacity = newSize;
}

// @ 0x00721910
void __stdcall DestroyChartRange(Chart68* first, Chart68* last)
{
    for (; first < last; first++) {
        if (first->v48 != 0 && ((int*)first->v48)[-1] != 0)
            EASTL_allocator_deallocate(first->v48);
        if (first->v34 != 0 && ((int*)first->v34)[-1] != 0)
            EASTL_allocator_deallocate(first->v34);
        if (first->v14 != 0 && ((int*)first->v14)[-1] != 0)
            EASTL_allocator_deallocate(first->v14);
    }
}

// @ 0x00721980
void* __cdecl DeleteTwoVtbl(TwoVtbl* this_, uint32_t flags)
{
    if (this_->p0c != 0 && ((int*)this_->p0c)[-1] != 0)
        EASTL_allocator_deallocate(this_->p0c);
    if (flags & 1)
        EASTL_allocator_deallocate(this_);
    return this_;
}

// @ 0x007219f0
void ChartHash::FindF(int* out, float* key)
{
    uint32_t h = HashVec(key) % mCapacity;
    FChartNode** slot = (FChartNode**)&mBuckets[h];
    FChartNode* n = *slot;
    if (n != 0) {
        do {
            if (key[0] == n->kx && key[1] == n->ky && key[2] == n->kz)
                goto found;
            n = n->next;
        } while (n != 0);
    }
    slot = (FChartNode**)&mBuckets[mCapacity];
    n = *slot;
found:
    HashFind r;
    r.pNode = n;
    r.pSlot = slot;
    *(HashFind*)out = r;
}

// @ 0x00721a80
void ChartHash::InsertF(int* out, float* key)
{
    uint32_t h = HashVec(key);
    uint32_t cap = mCapacity;
    uint32_t b = h % cap;
    FChartNode** slot = (FChartNode**)&mBuckets[b];
    FChartNode* n = *slot;
    while (n != 0) {
        if (key[0] == n->kx && key[1] == n->ky && key[2] == n->kz) {
            out[0] = (int)n;
            *((unsigned char*)out + 8) = 0;
            out[1] = (int)slot;
            return;
        }
        n = n->next;
    }
    FChartNode* nn = (FChartNode*)EASTL_allocator_allocate(0x14, "Graphics", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    if (nn != 0) {
        nn->kx = key[0]; nn->ky = key[1]; nn->kz = key[2]; nn->f0c = *(int*)((char*)key + 0xc);
    }
    nn->next = 0;
    b = h % mCapacity;
    slot = (FChartNode**)&mBuckets[b];
    nn->next = *slot;
    *slot = nn;
    mCount++;
    out[0] = (int)nn;
    *((unsigned char*)out + 8) = 1;
    out[1] = (int)slot;
}

// @ 0x00721bb0
void ChartHash::FindI(int* out, int* key)
{
    uint32_t h = (uint32_t)(key[0] ^ key[1] ^ key[2]) % mCapacity;
    IChartNode** slot = (IChartNode**)&mBuckets[h];
    IChartNode* n = *slot;
    while (n != 0) {
        if (n->k0 == key[0] && n->k1 == key[1] && n->k2 == key[2])
            goto found;
        n = n->next;
    }
    slot = (IChartNode**)&mBuckets[mCapacity];
    n = *slot;
found:
    HashFind r;
    r.pNode = n;
    r.pSlot = slot;
    void* volatile keep = memcpy(out, &r, sizeof(r));   // pair copy; keeps memcpy's destination (out) in eax
    (void)keep;
}

// @ 0x00721c30
void ChartHash::InsertI(int* out, int* key)
{
    uint32_t h = (uint32_t)(key[0] ^ key[1] ^ key[2]);
    uint32_t cap = mCapacity;
    uint32_t b = h % cap;
    IChartNode** slot = (IChartNode**)&mBuckets[b];
    IChartNode* n = *slot;
    while (n != 0) {
        if (n->k0 == key[0] && n->k1 == key[1] && n->k2 == key[2]) {
            out[0] = (int)n;
            *((unsigned char*)out + 8) = 0;
            out[1] = (int)slot;
            return;
        }
        n = n->next;
    }
    IChartNode* nn = (IChartNode*)EASTL_allocator_allocate(0x14, "Graphics", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    if (nn != 0) {
        nn->k0 = key[0]; nn->k1 = key[1]; nn->k2 = key[2]; nn->f0c = key[3];
    }
    nn->next = 0;
    b = h % mCapacity;
    slot = (IChartNode**)&mBuckets[b];
    nn->next = *slot;
    *slot = nn;
    mCount++;
    out[0] = (int)nn;
    *((unsigned char*)out + 8) = 1;
    out[1] = (int)slot;
}

// @ 0x00721d80
void* __cdecl CopyChart68(void* dst, void* src)
{
    unsigned char* d = (unsigned char*)dst;
    unsigned char* s = (unsigned char*)src;
    for (int i = 0; i < 0x50; i += 4)
        *(int*)(d + i) = *(int*)(s + i);
    return dst;
}

// @ 0x00722010
void __cdecl InitChartHash(ChartHash* this_)
{
    this_->mBuckets = 0;
    this_->mCapacity = 0;
    this_->mCount = 0;
}

// @ 0x007220c0
void __cdecl FreeChartThing(ChartHash* this_)
{
    if (this_->mBuckets != 0 && ((int*)this_->mBuckets)[-1] != 0)
        EASTL_allocator_deallocate(this_->mBuckets);
}

// @ 0x007221c0
void CMeshClusterer2::CollapseEdges()
{
    while (((char*)mEdgeHeap.mHeapEntries.mpEnd - (char*)mEdgeHeap.mHeapEntries.mpBegin) > 0) {
        float me = mMaxError;
        void* top = mEdgeHeap.mHeapEntries.mpBegin ? *(void**)mEdgeHeap.mHeapEntries.mpBegin : 0;
        if (!(me < 0.0f) && top && *(float*)top <= me && me != *(float*)top)
            break;
        void* e = 0;
        if (mEdgeHeap.mHeapEntries.mpEnd != mEdgeHeap.mHeapEntries.mpBegin) {
            e = *(void**)mEdgeHeap.mHeapEntries.mpBegin;
            *(int*)((char*)e + 4) = -1;
            *(void**)mEdgeHeap.mHeapEntries.mpBegin = *(void**)((char*)mEdgeHeap.mHeapEntries.mpEnd - 4);
            *(int*)(*(int*)mEdgeHeap.mHeapEntries.mpBegin + 4) = 0;
            mEdgeHeap.mHeapEntries.mpEnd = (char*)mEdgeHeap.mHeapEntries.mpEnd - 4;
            mEdgeHeap.HeapifyDown(0);
        }
        int i9 = *(int*)((char*)e + 8);
        int i12 = *(int*)((char*)e + 0xc);
        if (i9 != i12) {
            char* fc = (char*)mFaceClusters.mpBegin;
            char* a = fc + i9 * 0x28;
            char* b = fc + i12 * 0x28;
            for (int k = 0; k < 3; k++) {
                *(float*)(a + k * 4 + 0xc) += *(float*)(b + k * 4 + 0xc);
                *(float*)(a + k * 4) += *(float*)(b + k * 4);
            }
            *(float*)(a + 0x18) += *(float*)(b + 0x18);
            MergeEdgeLists(i9, i12);
            *(int*)(b + 0x20) = i9;
            mNumClusters--;
        }
    }
}

// @ 0x007222f0
void* __cdecl Insert34Vec(void* v, void* pos, void* val)
{
    (void)v; (void)pos; (void)val;
    return 0;
}

// @ 0x00722410
void __cdecl VectorAppend8Impl(void* dstEnd, void* val)
{
    (void)dstEnd; (void)val;
}

// @ 0x00722520
void __thiscall VecAny::Assign(int n, int value, int dummy)
{
    int* p;
    if (n != 0)
        p = (int*)EASTL_allocator_allocate(n * 4, "Graphics", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    else
        p = 0;
    this->begin = p;
    this->cap = p + n;
    this->end = p + n;
    if (n > 0) {
        for (; n != 0; n--)
            *p++ = value;
    }
    (void)dummy;
}

// @ 0x00722580
void __cdecl VecInsert18(int* v, void* pos, uint32_t n, void* val)
{
    (void)v; (void)pos; (void)n; (void)val;
}

// @ 0x00722770
void __cdecl VecInsert28(int* v, void* pos, uint32_t n, void* val)
{
    (void)v; (void)pos; (void)n; (void)val;
}

// @ 0x00722990
void* __cdecl AllocConstruct38(int n, const void* a, const void* b)
{
    void* p;
    if (n == 0)
        p = 0;
    else
        p = EASTL_allocator_allocate(n * 0x38, "Graphics", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    (void)a; (void)b;
    return p;
}

// @ 0x007229f0
void* __cdecl CopyChartRecord(void* dst, void* src)
{
    unsigned char* d = (unsigned char*)dst;
    unsigned char* s = (unsigned char*)src;
    for (int i = 0; i < 0x50; i += 4)
        *(int*)(d + i) = *(int*)(s + i);
    return dst;
}

// @ 0x00722b20
int __cdecl FindOrInsertF(void* hash, float* key)
{
    (void)hash;
    int* p = (int*)((char*)key + 0xc);
    return *p;
}

// @ 0x00722ba0
void __cdecl SwapVecIfOwned(int* a, int* b)
{
    int* t0 = (int*)a[0]; int* t1 = (int*)a[1]; int* t2 = (int*)a[2];
    a[0] = b[0]; a[1] = b[1]; a[2] = b[2];
    b[0] = (int)t0; b[1] = (int)t1; b[2] = (int)t2;
}

// @ 0x00722c60
void __thiscall VecAny::Push8(Vec8* val)
{
    Vec8* e = (Vec8*)this->end;
    if (e < (Vec8*)this->cap) {
        this->end = (int*)(e + 1);
        if (e != 0) {
            e->x = val->x;
            e->y = val->y;
            return;
        }
    } else {
        ((VecAppend8*)this)->Append(e, val);
    }
}

// @ 0x00722ca0
int* __cdecl ConstructIntVec(int* v, int n, int val)
{
    v[0] = 0; v[1] = 0; v[2] = 0;
    ((VecAny*)v)->Assign(n, val, 0);
    return v;
}

// @ 0x00722d00
void __cdecl BuildTextureChart(int param_1)
{
    (void)param_1;
}

// @ 0x00723140
void MeshBuild::Build()
{
    if (mTotal != 0) return;
    int j = FindElement(mMesh, mMeshIdx, 1, 0, 0);
    if (j < 0) return;
    PrepareSubMesh((SubMesh*)((char*)mMesh->items + mMeshIdx * 0x8c));
    int slot = LookupView(mMesh, 0x16, mMeshIdx, 0xf, 0xe);
    BufView adj = mMesh->entries[slot].view;  // copy; AddRef the ref
    if (adj.ref) adj.ref->AddRef();

    SubMesh* item = (SubMesh*)((char*)mMesh->items + mMeshIdx * 0x8c);
    int vertCount = mMesh->entries[item->pairs[j * 2]].view.count;
    BufView* idxView = &item->views[item->pairs[j * 2 + 1]];

    BufView out;
    out.count = idxView->count;
    out.data = 0;
    out.maskIdx = 4;
    out.stride = 4;
    out.ref = 0;
    AllocView(&out);

    uint32_t* map = 0;
    if (vertCount) map = (uint32_t*)operator_new(vertCount * 4, "Graphics", 0, 0, kEastlAllocFile, 0xd1);
    for (int i = vertCount; i != 0; --i) map[vertCount - i] = 0;  // zero fill

    int chunkId = (int)(mEdgesEnd - mEdges);
    int counter = 0;
    for (int k = 0; k < mChunkCount; ++k) {
        memset(map, 0xff, vertCount * 4);
        Chunk* c = (Chunk*)((char*)mChunks + k * 0x64);
        int t = c->triBegin;
        c->vtxBase = counter;
        c->vtxBase2 = counter;
        for (; t < c->triEnd; ++t) {
            int base = *(int*)(mTri.data + (uint32_t)mTri.stride * t) * 3;
            uint32_t v0 = ViewU32(*idxView, base);
            uint32_t v1 = ViewU32(*idxView, base + 1);
            uint32_t v2 = ViewU32(*idxView, base + 2);
            int n0 = *(int*)(adj.data + (uint32_t)adj.stride * base + 4);
            int n1 = *(int*)(adj.data + (uint32_t)adj.stride * (base + 1) + 4);
            int n2 = *(int*)(adj.data + (uint32_t)adj.stride * (base + 2) + 4);
            bool f0 = (n0 < 0) || mEdges[n0 / 3].chunk != chunkId;
            bool f1 = (n1 < 0) || mEdges[n1 / 3].chunk != chunkId;
            bool f2 = (n2 < 0) || mEdges[n2 / 3].chunk != chunkId;
            if (f0 || f2) TakeIndex(map, v0, counter);
            if (f0 || f1) TakeIndex(map, v1, counter);
            if (f1 || f2) TakeIndex(map, v2, counter);
        }
        c->vtxMid = counter;
        for (t = c->triBegin; t < c->triEnd; ++t) {
            int base = *(int*)(mTri.data + (uint32_t)mTri.stride * t) * 3;
            uint32_t v0 = ViewU32(*idxView, base);
            uint32_t v1 = ViewU32(*idxView, base + 1);
            uint32_t v2 = ViewU32(*idxView, base + 2);
            TakeIndex(map, v0, counter);
            TakeIndex(map, v1, counter);
            TakeIndex(map, v2, counter);
            *(uint32_t*)(out.data + (uint32_t)out.stride * base) = map[v0];
            *(uint32_t*)(out.data + (uint32_t)out.stride * (base + 1)) = map[v1];
            *(uint32_t*)(out.data + (uint32_t)out.stride * (base + 2)) = map[v2];
        }
        ++chunkId;
        c->vtxEnd = counter;
    }

    mOut.count = out.count;
    mOut.data = out.data;
    mOut.maskIdx = out.maskIdx;
    mOut.stride = out.stride;
    RefObj* oldRef = mOut.ref;
    if (out.ref != oldRef) {
        if (out.ref) out.ref->AddRef();
        mOut.ref = out.ref;
        ReleaseRef(oldRef);
    }
    mTotal = counter;
    if (map && ((int*)map)[-1] != 0) operator_delete__(map);
    ReleaseRef(out.ref);
    ReleaseRef(adj.ref);
}

// @ 0x00723680
IntVecObj::IntVecObj(int n)
{
    mVec.Alloc(n, &n);
    int* p = mVec.mpBegin;
    if ((uint32_t)n > 0) {
        for (int i = n; i != 0; --i) *p++ = 0;
    }
    mVec.mpEnd = mVec.mpBegin + n;
    mField20 = 0;
}

// @ 0x00723720
IntVecObj::IntVecObj(int n, const int* v)
{
    mVec.Fill(n, *v);
    mField20 = 0;
}

// @ 0x007237a0
void Vec24::resize(uint32_t n)
{
    Vertex3D* pEnd = mpEnd;
    uint32_t size = (uint32_t)(pEnd - mpBegin);
    if (n > size) {
        Vertex3D v;
        Insert(pEnd, n - size, &v);
        return;
    }
    Vertex3D* pNewEnd = mpBegin + n;
    CopyVertex3D(pEnd, pEnd, pNewEnd);
    mpEnd = mpEnd - (pEnd - pNewEnd);
}

// @ 0x007238b0
void Vec24::resize(uint32_t n, const Vertex3D* val)
{
    Vertex3D* pEnd = mpEnd;
    uint32_t size = (uint32_t)(pEnd - mpBegin);
    if (n > size) {
        Insert(pEnd, n - size, val);
        return;
    }
    Vertex3D* pNewEnd = mpBegin + n;
    CopyVertex3D(pEnd, pEnd, pNewEnd);
    mpEnd = mpEnd - (pEnd - pNewEnd);
}

// @ 0x00723930
ChartRec::ChartRec(const ChartRec& o)
{
    i0 = o.i0;
    f4 = o.f4;
    f8 = o.f8;
    iC = o.iC;
    i10 = o.i10;
    v14.Alloc((uint32_t)(o.v14.mpEnd - o.v14.mpBegin) >> 3, &o.v14.mAllocator);
    void* outEnd;
    UninitCopy8(&outEnd, o.v14.mpBegin, o.v14.mpEnd, v14.mpBegin, &o);
    v14.mpEnd = (char*)outEnd;
    f28 = o.f28;
    f2C = o.f2C;
    b30 = o.b30;
    v34.Alloc((uint32_t)((char*)o.v34.mpEnd - (char*)o.v34.mpBegin) >> 2, &o.v34.mAllocator);
    {
        char* src = (char*)o.v34.mpBegin;
        int bytes = (char*)o.v34.mpEnd - src;
        char* r = (char*)memcpy(v34.mpBegin, src, bytes);
        v34.mpEnd = (float*)(r + (bytes >> 2) * 4);
    }
    v48.Alloc((uint32_t)((char*)o.v48.mpEnd - (char*)o.v48.mpBegin) >> 2, &o.v48.mAllocator);
    {
        char* src = (char*)o.v48.mpBegin;
        int bytes = (char*)o.v48.mpEnd - src;
        char* r = (char*)memcpy(v48.mpBegin, src, bytes);
        v48.mpEnd = (float*)(r + (bytes >> 2) * 4);
    }
    i5C = o.i5C;
    i60 = o.i60;
    i64 = o.i64;
}

// @ 0x00723a70
ChartRec& ChartRec::operator=(const ChartRec& o)
{
    i0 = o.i0;
    f4 = o.f4;
    f8 = o.f8;
    iC = o.iC;
    i10 = o.i10;
    v14.assign(o.v14);
    f28 = o.f28;
    f2C = o.f2C;
    b30 = o.b30;
    v34 = o.v34;
    v48 = o.v48;
    i5C = o.i5C;
    i60 = o.i60;
    i64 = o.i64;
    return *this;
}

// @ 0x00723af0
void Vec56::DoAssign(const Xform56* first, const Xform56* last, int tag)
{
    uint32_t n = (uint32_t)(last - first);
    if (n > (uint32_t)(mpCapacity - mpBegin)) {
        Xform56* pNew = AllocCopy(n, first, last);
        if (mpBegin && ((int*)mpBegin)[-1] != 0) operator_delete__(mpBegin);
        mpBegin = pNew;
        Xform56* pNewEnd = pNew + n;
        mpEnd = pNewEnd;
        mpCapacity = mpEnd;
        return;
    }
    uint32_t size = (uint32_t)(mpEnd - mpBegin);
    if (n <= size) {
        mpEnd = CopyXform(first, last, mpBegin);
        return;
    }
    const Xform56* pMid = first + size;
    CopyXform(first, pMid, mpBegin);
    Xform56* out;
    UninitCopyXform(&out, pMid, last, mpEnd, tag);
    mpEnd = out;
}

// @ 0x00723cf0
void PairVec::Reset(uint32_t nVerts, uint32_t nPairs, int a, int b, uint8_t flag)
{
    char* pEnd = mpEnd;
    struct Pair8 { int first, second; };
    uint32_t size = (uint32_t)((Pair8*)pEnd - (Pair8*)mpBegin);  // signed ptrdiff (sar), then unsigned compare
    if (nPairs > size) {
        char tmp[8];
        Insert(pEnd, nPairs - size, tmp);
    } else {
        Erase(mpBegin + nPairs * 8, pEnd);
    }
    mVerts.resize(nVerts);
    mCount = nPairs;
    mField2C = 0;
    mField34 = a;
    mField38 = b;
    mFlag3C = flag;
}

// @ 0x00723d60
void __cdecl ExportSubMeshRemap(MeshData* mesh)
{
    char alloc[0x40];  // PairVec storage (constructed with zeroed vectors)
    (void)alloc;
    PairVec pv;
    pv.mpBegin = pv.mpEnd = pv.mpCapacity = 0;
    pv.mVerts.mpBegin = pv.mVerts.mpEnd = 0;
    pv.mCount = 0;
    pv.mField2C = 0;
    pv.mField34 = 0;
    pv.mField38 = 0;
    pv.mFlag3C = 1;

    int key = LookupView(mesh, 1, 0, 0, 0xe);
    if (key >= 0) {
        int nItems = (int)(mesh->itemsEnd - mesh->items);
        for (int i = 0; i < nItems; ++i) {
            int j = FindViewSlot(mesh, i, key);
            if (j < 0) continue;
            SubMesh* item = &mesh->items[i];
            int count = item->idx.count;
            if (count <= 0) continue;

            BufView src;
            src.count = 0;
            src.data = 0;
            src.maskIdx = 0;
            src.stride = 0;
            src.ref = 0;
            if (item->views != item->viewsEnd) {
                BufView* e = &item->views[item->pairs[j * 2 + 1]];
                src.count = e->count;
                src.data = e->data;
                src.maskIdx = e->maskIdx;
                src.stride = e->stride;
                RefObj* r = e->ref;
                if (r) {
                    r->AddRef();
                    src.ref = r;
                }
            }

            pv.Reset(1, item->field10, 0, 0, 0);
            for (int p = 0; p < pv.mCount; ++p) {
                ((int*)pv.mpBegin)[p * 2] = -1;
                ((int*)pv.mpBegin)[p * 2 + 1] = -1;
            }

            BufView tmp;
            tmp.count = item->idx.count;
            tmp.data = 0;
            tmp.maskIdx = 8;
            tmp.stride = 8;
            tmp.ref = 0;
            AllocView(&tmp);

            int n = item->idx.count;
            uint32_t* map = 0;
            if (n) map = (uint32_t*)operator_new(n * 4, "Graphics", 0, 0, kEastlAllocFile, 0xd1);
            for (int z = n; z != 0; --z) map[n - z] = 0;

            if (src.data) {
                for (int q = 0; q < n; ++q) {
                    uint32_t a = ViewU32(item->idx, q);
                    map[q] = ViewU32(src, a);
                }
            } else {
                for (int q = 0; q < n; ++q) map[q] = ViewU32(item->idx, q);
            }

            pv.Fill(0, count, 3, map, tmp.data, 0);
            pv.Clear2();
            pv.mpEnd = pv.mpBegin + 0;  // end = begin: pair list cleared
            StoreView(mesh, 0x16, i, 0xf, 7, &tmp);

            if (map && ((int*)map)[-1] != 0) operator_delete__(map);
            ReleaseRef(tmp.ref);
            ReleaseRef(src.ref);
        }
    }
    if (pv.mVerts.mpBegin && ((int*)pv.mVerts.mpBegin)[-1] != 0) operator_delete__(pv.mVerts.mpBegin);
    if (pv.mpBegin && ((int*)pv.mpBegin)[-1] != 0) operator_delete__(pv.mpBegin);
}

// @ 0x00724100
void cMeshClusterer_s0072_4100::Setup()
{
    int ix = FindElement(mpMesh, mSection, 1, 0, 0);
    if (ix < 0)
        return;

    MeshData_s0072_4100* mesh = mpMesh;
    MeshSection* sec = &mesh->mpSections[mSection];
    const SectionFmt& fmt = sec->mFmtBegin[ix];
    EltRef* pos = &mpMesh->mpElts[fmt.mElt].mRef;
    EltRef* idx = &sec->mpIndexArrays[fmt.mIndex];
    int a = FindStream(mesh, 0x16, 0, 0xf, 0xe);
    EltRef adj = mpMesh->mpElts[a].mRef;

    if (idx->mpData == 0)
        return;

    int n = sec->mVertIndices.mCount;
    int tris = n / 3;
    mFaceClusters.resize(tris);
    int j = 2;
    int off = 0;
    for (int t = tris; t > 0; --t) {
        uint32_t s0 = ReadIndex(&sec->mVertIndices, j - 2);
        uint32_t s1 = ReadIndex(&sec->mVertIndices, j - 1);
        uint32_t s2 = ReadIndex(&sec->mVertIndices, j);
        uint32_t i0 = ReadIndex(idx, s0);
        uint32_t i1 = ReadIndex(idx, s1);
        uint32_t i2 = ReadIndex(idx, s2);
        float* p0 = (float*)(pos->mpData + pos->mStride * i0);
        float* p2 = (float*)(pos->mpData + pos->mStride * i2);
        float* p1 = (float*)(pos->mpData + pos->mStride * i1);
        float x0 = p0[0], y0 = p0[1], z0 = p0[2];
        float x1 = p1[0], y1 = p1[1], z1 = p1[2];
        float x2 = p2[0], y2 = p2[1], z2 = p2[2];
        float* f = (float*)((char*)mFaceClusters.mpBegin + off);
        float z10 = z1 + z0;
        f[3] = ((z2 + z1) * (y1 - y2) + (z2 + z0) * (y2 - y0) + (y0 - y1) * z10) * 0.5f;
        f[4] = ((z1 - z2) * (x2 + x1) + (z2 - z0) * (x2 + x0) + (z0 - z1) * (x1 + x0)) * 0.5f;
        float nz = ((y2 + y1) * (x1 - x2) + (y2 + y0) * (x2 - x0) + (x0 - x1) * (y1 + y0)) * 0.5f;
        f[5] = nz;
        f[6] = sqrtf(f[4] * f[4] + nz * nz + f[3] * f[3]);
        float area = f[6];
        f[0] = (area * ((x1 + x0) + x2)) * (1.0f / 3.0f);
        f[1] = (area * (y2 + (y1 + y0))) * (1.0f / 3.0f);
        f[2] = (area * (z2 + z10)) * (1.0f / 3.0f);
        ((int*)f)[7] = -1;
        ((int*)f)[8] = -1;
        ((int*)f)[9] = 0;
        off += 0x28;
        j += 3;
    }

    mNumClusters = (int)(mFaceClusters.mpEnd - mFaceClusters.mpBegin);

    int numEdges = 0;
    {
        const char* p = adj.mpData + 4;
        for (int i = 0; i < n; ++i) {
            int nb = *(const int*)p;
            if (nb >= 0 && nb > i)
                ++numEdges;
            p += adj.mStride;
        }
    }

    cDualEdge zero;
    zero.mCost = 0;
    zero.mHeapIndex = 0;
    zero.mClusters[0] = zero.mClusters[1] = 0;
    zero.mNextEdges[0] = zero.mNextEdges[1] = 0;
    mDualEdges.resize(numEdges, &zero);

    int e = 0;
    int eoff = 0;
    for (int i = 0; i < n; ++i) {
        int nb = *(const int*)(adj.mpData + 4 + i * adj.mStride);
        if (nb >= 0 && nb > i) {
            cDualEdge* edge = (cDualEdge*)((char*)mDualEdges.mpBegin + eoff);
            int c0 = i / 3;
            int c1 = nb / 3;
            edge->mClusters[0] = c0;
            edge->mClusters[1] = c1;
            cFaceCluster_s0072_4100* f0 = &mFaceClusters.mpBegin[c0];
            edge->mNextEdges[0] = f0->mFirstEdge;
            f0->mFirstEdge = e;
            cFaceCluster_s0072_4100* f1 = &mFaceClusters.mpBegin[c1];
            edge->mNextEdges[1] = f1->mFirstEdge;
            f1->mFirstEdge = e + numEdges;
            CalcError(f0, f1, (float*)edge);
            HeapVec_s0072_4100& h = mEdgeHeap.mHeapEntries;
            if (h.mpEnd < h.mpCap) {
                cDualEdge** q = h.mpEnd;
                h.mpEnd = q + 1;
                if (q)
                    *q = edge;
            } else {
                h.DoInsertValue(h.mpEnd, &edge);
            }
            edge->mHeapIndex = (int)(h.mpEnd - h.mpBegin) - 1;
            mEdgeHeap.HeapifyUp((int)(h.mpEnd - h.mpBegin) - 1);
            ++e;
            eoff += 0x18;
        }
    }
}

// @ 0x00724700
void __cdecl FUN_00724700(void* this_)
{ (void)this_; }

// @ 0x007247c0
void __cdecl FUN_007247c0()
{}

// @ 0x007249f0
void FUN_007249f0(MeshContext* ctx)
{
    char* p = (char*)ctx;
    int job = FUN_0071ddc0(p, 1, 0, 3, 0xe);
    if (job < 0)
        return;
    if (*(int*)(ctx->pNodeArray + job * 0x20 + 0xc) != 0)
        return;

    int meshCount = (int)(ctx->pMeshesEnd - ctx->pMeshes) / 0x8c;
    for (int mi = 0; mi < meshCount; ++mi) {
        int tri = FUN_0071e040(p, mi, job);
        if (tri < 0)
            continue;

        int    recOff = mi * 0x8c;
        char*  rec    = ctx->pMeshes + recOff;
        MeshRec* mr   = (MeshRec*)rec;

        // 16-byte wedge entry for triangle `tri`.
        int16_t    sub = *(int16_t*)((char*)mr->pIdxTable + tri * 4 + 2);
        VertEntry* src = (VertEntry*)((char*)mr->pVertBase + (int)sub * 0x10);
        VertEntry  ve  = *src;
        if (ve.ref)
            ve.ref->AddRef();

        uint32_t  count0 = mr->count0;
        uint16_t* data   = mr->pData;
        int16_t   fmt    = mr->fmt;
        uint16_t  stride = mr->stride;
        RefObj_s0072_49f0*   ref1   = mr->ref1;
        if (ref1)
            ref1->AddRef();

        IntVec idx;
        idx.mpBegin = idx.mpEnd = idx.mpCap = 0;
        uint32_t count = count0;
        uint32_t origCount = 0;

        if (data == 0) {
            count = mr->count1;
            origCount = count;
            FUN_004cd3c0(&idx, (int)count);
            for (uint32_t i = 0; i < count; ++i)
                idx.mpBegin[i] = (int)i;
        } else if (fmt == 4) {
            origCount = count;
            FUN_004cd3c0(&idx, (int)count);
            for (uint32_t i = 0; i < count; ++i)
                idx.mpBegin[i] = *(int*)((char*)data + i * stride);
        } else if (fmt == 2) {
            origCount = count;
            FUN_004cd3c0(&idx, (int)count);
            for (uint32_t i = 0; i < count; ++i)
                idx.mpBegin[i] = *(uint16_t*)((char*)data + i * stride);
        }

        // Compacted output index table, `count` uints (zeroed).
        uint32_t* out = 0;
        if (count != 0) {
            out = (uint32_t*)FUN_00f473a0(count * 4, "Graphics", 0, 0,
                    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                    0xd1);
        }
        uint32_t* outEnd = out + count;
        for (uint32_t i = 0; i < count; ++i)
            out[i] = 0;

        int nTri = (int)count / 3;
        uint32_t written = 0;
        int triIdx = 0;

        if (ve.fmt == 4) {
            int*      pIdx = idx.mpBegin;
            uint32_t* pOut = out + 2;
            for (int t = 0; t < nTri; ++t) {
                // region ids of the three wedge vertices
                int r0 = *(int*)((char*)ve.y + (int)ve.stride * pIdx[0]);
                int r1 = *(int*)((char*)ve.y + (int)ve.stride * pIdx[1]);
                int r2 = *(int*)((char*)ve.y + (int)ve.stride * pIdx[2]);
                if (r0 == r1 || r1 == r2 || r2 == r0) {
                    pOut[-2] = written;
                    pOut[-1] = written;
                    pOut[0]  = written;
                } else {
                    pOut[-2] = written;
                    idx.mpBegin[triIdx] = pIdx[0];
                    pOut[-1] = written + 1;
                    idx.mpBegin[triIdx + 1] = pIdx[1];
                    pOut[0] = written + 2;
                    idx.mpBegin[triIdx + 2] = pIdx[2];
                    written += 3;
                    triIdx += 3;
                }
                if ((t & 0xfff) == 0) {
                    int zero = 0;
                    FUN_00921df0(&zero);
                }
                pIdx += 3;
                pOut += 3;
            }
        } else if (ve.fmt == 2) {
            int*      pIdx = idx.mpBegin;
            uint32_t* pOut = out + 2;
            for (int t = 0; t < nTri; ++t) {
                uint16_t r0 = *(uint16_t*)((char*)ve.y + (int)ve.stride * pIdx[0]);
                uint16_t r1 = *(uint16_t*)((char*)ve.y + (int)ve.stride * pIdx[1]);
                uint16_t r2 = *(uint16_t*)((char*)ve.y + (int)ve.stride * pIdx[2]);
                if (r0 == r1 || r1 == r2 || r2 == r0) {
                    pOut[-2] = written;
                    pOut[-1] = written;
                    pOut[0]  = written;
                } else {
                    pOut[-2] = written;
                    idx.mpBegin[triIdx] = pIdx[0];
                    pOut[-1] = written + 1;
                    idx.mpBegin[triIdx + 1] = pIdx[1];
                    pOut[0] = written + 2;
                    idx.mpBegin[triIdx + 2] = pIdx[2];
                    written += 3;
                    triIdx += 3;
                }
                if ((t & 0xfff) == 0) {
                    int zero = 0;
                    FUN_00921df0(&zero);
                }
                pIdx += 3;
                pOut += 3;
            }
        }

        if (written == origCount) {
            if (out && *(int*)((char*)out - 4) != 0)
                FUN_00f47380(out);
            if (idx.mpBegin && *(int*)((char*)idx.mpBegin - 4) != 0)
                FUN_00f47380(idx.mpBegin);
        } else {
            int have = (int)((char*)idx.mpEnd - (char*)idx.mpBegin) >> 2;
            if ((int)written > have) {
                int zero = 0;
                FUN_004cea40(idx.mpEnd, (int)written - have, &zero);
            } else {
                int* here = idx.mpBegin + written;
                FUN_0011e0744(here, (int)idx.mpEnd, 0);
                idx.mpEnd = (int*)((char*)idx.mpEnd + (((char*)idx.mpEnd - (char*)here) >> 2) * -4);
            }
            struct { int n; int16_t a, b; RefObj_s0072_49f0* r; } desc;
            desc.n = (int)((char*)idx.mpEnd - (char*)idx.mpBegin) >> 2;
            desc.a = 4; desc.b = 4; desc.r = 0;
            FUN_007201d0(&desc, ctx->pMeshes + recOff);

            // append `written` to a uint vector
            if (outEnd < outEnd) {
                // (empty else-branch as in original)
            } else {
                FUN_004558a0(outEnd, &written, 0);
            }

            int* prims = 0; int* primsEnd = 0; int pad = 0;
            FUN_0071ee10(p, &prims, mi, 0, -1);
            int np = (int)((char*)primsEnd - (char*)prims) >> 2;
            for (int i = 0; i < np; ++i) {
                char* prim = ctx->pPrims + prims[i] * 0x14;
                *(int*)(prim + 8)  = (int)out[*(int*)(prim + 8)];
                *(int*)(prim + 0xc) = (int)out[*(int*)(prim + 0xc)];
            }
            int zero = 0;
            FUN_00921df0(&zero);
            if (prims && *(int*)((char*)prims - 4) != 0)
                FUN_00f47380(prims);
            if (desc.r)
                desc.r->Release();
            if (out && *(int*)((char*)out - 4) != 0)
                FUN_00f47380(out);
            if (idx.mpBegin && *(int*)((char*)idx.mpBegin - 4) != 0)
                FUN_00f47380(idx.mpBegin);
        }

        if (ref1)
            ref1->Release();
        if (ve.ref)
            ve.ref->Release();
    }

    FUN_0073a4b0(p);
}

// @ 0x00725130
namespace SP {
void CreateEdges(cMeshData_s0072_5130* mesh)
{
    int posArray = FindElementArray(mesh, 1, 0, 3, 0xe);
    if (posArray < 0)
        return;

    int adjArray = FindElementArray(mesh, 8, 0, 0, 0xe);
    if (adjArray < 0) {
        adjArray = FindElementArray(mesh, 0, 0, 0, 2);
        if (adjArray < 0) {
            adjArray = FindElementArray(mesh, 2, 0, 0, 0xe);
            if (adjArray < 0) {
                adjArray = FindElementArray(mesh, 0, 0, 0, 1);
                if (adjArray < 0) {
                    BuildConnectivity(mesh);
                    return;
                }
            }
        }
    }

    cEltArrayRef_s0072_5130 edgeMap;
    edgeMap.mNumElts = mesh->mEltArrays.mpBegin[adjArray].mArray.mNumElts;
    edgeMap.mData = 0;
    edgeMap.mEltSize = 4;
    edgeMap.mEltStride = 4;
    AllocateEltArray(&edgeMap);
    Memset32(edgeMap.mData, 0xffffffff, (int)(edgeMap.mEltSize * edgeMap.mNumElts) / 4);

    int numSections = (int)(mesh->mSections.mpEnd - mesh->mSections.mpBegin);
    for (int s = 0; s < numSections; s++) {
        int posFmt = FindFormatEntry(mesh, s, posArray);
        if (posFmt < 0)
            continue;

        cIndexArrayRef_s0072_5130 adjIdx;
        int adjFmt = FindFormatEntry(mesh, s, adjArray);
        if (adjFmt >= 0) {
            cMDSection_s0072_5130& sec = mesh->mSections.mpBegin[s];
            adjIdx = sec.mEltIndices[sec.mFormat[adjFmt].mIndices];
        }
        cMDSection_s0072_5130* section = &mesh->mSections.mpBegin[s];
        cEltArrayRef_s0072_5130 posIdx = section->mEltIndices[section->mFormat[posFmt].mIndices];
        section = &mesh->mSections.mpBegin[s];
        cEltArrayRef_s0072_5130 vertIdx = section->mVertIndices;

        eastl::vector_s0072_5130<int> corners;
        int n = 0;
        if (vertIdx.mData) {
            if (vertIdx.mEltSize == 4) {
                n = vertIdx.mNumElts;
                corners.resize(n);
                const unsigned char* p = vertIdx.mData;
                for (int i = 0; i < n; i++) {
                    corners[i] = *(const uint32_t*)p;
                    p += vertIdx.mEltStride;
                }
            } else if (vertIdx.mEltSize == 2) {
                n = vertIdx.mNumElts;
                corners.resize(n);
                const unsigned char* p = vertIdx.mData;
                for (int i = 0; i < n; i++) {
                    corners[i] = *(const unsigned short*)p;
                    p += vertIdx.mEltStride;
                }
            }
        } else {
            n = mesh->mSections.mpBegin[s].mNumVertices;
            corners.resize(n);
            for (int i = 0; i < n; i++)
                corners[i] = i;
        }

        eastl::vector_s0072_5130<int> remap(n);
        int nTris = n / 3;
        int numOut = 0;
        if (posIdx.mEltSize == 4)
            CompactTriangles<uint32_t>(posIdx, adjIdx, edgeMap, corners, remap, nTris, numOut);
        else if (posIdx.mEltSize == 2)
            CompactTriangles<unsigned short>(posIdx, adjIdx, edgeMap, corners, remap, nTris, numOut);

        EA::Thread::ThreadSleep(0);
        if (numOut == n)
            continue;

        corners.resize_inline(numOut);
        cEltArrayRef_s0072_5130 newIndices;
        newIndices.mNumElts = corners.size();
        newIndices.mData = (unsigned char*)corners.data();
        newIndices.mEltSize = 4;
        newIndices.mEltStride = 4;
        CopyEltArray(&newIndices, &mesh->mSections.mpBegin[s].mVertIndices);
        remap.push_back(numOut);

        eastl::vector_s0072_5130<int> prims;
        FindPrimitives(mesh, &prims, s, 0, -1);
        for (int i = 0; i < (int)prims.size(); i++) {
            cMDPrimitive_s0072_5130& prim = mesh->mPrimitives.mpBegin[prims[i]];
            prim.mStart = remap[prim.mStart];
            prim.mEnd = remap[prim.mEnd];
        }

        if (adjIdx.mData) {
            MakeEltArrayUnique(&adjIdx);
            // collapse every ring to one representative (stored as -2 - rep)
            for (int i = 0; i < section->mVertIndices.mNumElts; i++) {
                uint32_t e = adjIdx.GetIndex(section->mVertIndices.GetIndex(i));
                if (edgeMap.Int(e) >= 0) {
                    int k = edgeMap.Int(e);
                    edgeMap.Int(e) = -2 - (int)e;
                    while (k != (int)e && k >= 0) {
                        int& next = edgeMap.Int(k);
                        k = next;
                        next = -2 - (int)e;
                    }
                }
                int rep = edgeMap.Int(e);
                if (rep < -1) {
                    rep = -2 - rep;
                    uint32_t v = section->mVertIndices.GetIndex(i);
                    switch (adjIdx.mEltSize) {
                    case 1:
                        *(unsigned char*)(adjIdx.mData + adjIdx.mEltStride * v) = (unsigned char)rep;
                        break;
                    case 2:
                        *(unsigned short*)(adjIdx.mData + adjIdx.mEltStride * v) = (unsigned short)rep;
                        break;
                    case 4:
                        *(int*)(adjIdx.mData + adjIdx.mEltStride * v) = rep;
                        break;
                    }
                }
            }
            cMDSection_s0072_5130& sec = mesh->mSections.mpBegin[s];
            sec.mEltIndices[sec.mFormat[adjFmt].mIndices] = adjIdx;
        }
        EA::Thread::ThreadSleep(0);
    }
    FinishEdges(mesh);
}
}  // namespace SP

// @ 0x00725e40
namespace SP {
void cMeshClusterer_s0072_5e40::AssignCharts(int texCoordSet, bool normalize, bool alignToBoundary)
{
    Prepare();

    int fmtIndex = FindFormatEntry(mMeshData, mSection, 1 /*kMDPosition*/, 0, 0);
    const cEltArrayRef_s0072_5e40& positions =
        mMeshData->mEltArrays[mMeshData->mSections[mSection].mFormat[fmtIndex].mElts].mArray;
    const cIndexArrayRef_s0072_5e40& posIndices =
        mMeshData->mSections[mSection].mEltIndices[mMeshData->mSections[mSection].mFormat[fmtIndex].mIndices];

    // cluster element -> vertex index
    UIntVector vertIndex(mNumClusterElements);
    for (int i = 0; i < mNumClusters; ++i) {
        const cClusterInfo_s0072_5e40& ci = mClusterInfo[i];
        for (int f = ci.mFacesStart; f < ci.mFacesEnd; ++f) {
            int e = mClusterFaces.At<int>(f) * 3;
            vertIndex[mClusterIndices.At<int>(e)]     = posIndices.Index(e);
            vertIndex[mClusterIndices.At<int>(e + 1)] = posIndices.Index(e + 1);
            vertIndex[mClusterIndices.At<int>(e + 2)] = posIndices.Index(e + 2);
        }
    }

    cEltArrayRef_s0072_5e40 uvs(mNumClusterElements, sizeof(cSPVector2));
    AllocateEltArray(uvs);

    for (int i = 0; i < mNumClusters; ++i) {
        cClusterInfo_s0072_5e40& ci = mClusterInfo[i];

        cSPVector3 u = Normalize(OrthogonalVector(ci.mNormal));
        cSPVector3 v = Cross(ci.mNormal, u);
        int numBorder = ci.mBorderIndicesEnd - ci.mBorderIndicesStart;
        cSPVector3 a = u;
        cSPVector3 b = v;

        if (alignToBoundary && numBorder > 4) {
            ci.mBoundaryCoords.resize(numBorder);
            for (int k = ci.mBorderIndicesStart; k < ci.mBorderIndicesEnd; ++k) {
                cSPVector3 d = positions.At<cSPVector3>(vertIndex[k]) - ci.mCentre;
                ci.mBoundaryCoords.mpBegin[k - ci.mBorderIndicesStart] = cSPVector2(Dot(d, u), Dot(d, v));
            }
            RemoveDuplicatePoints(&ci.mBoundaryCoords);
            FindConvexHull(ci.mBoundaryCoords.mpBegin, ci.mBoundaryCoords.size(), &ci.mBoundaryCoords);
            cSPVector2 bmin, bmax, axis;
            ComputeBounds(&ci.mBoundaryCoords, &bmin, &bmax);
            FindBestRectAxis(ci.mBoundaryCoords.mpBegin, ci.mBoundaryCoords.size(), &bmin, &bmax, &axis);
            a = u * axis.x + v * axis.y;
            b = u * -axis.y + v * axis.x;
        }

        ci.mMinUV = cSPVector2(FLT_MAX, FLT_MAX);
        ci.mMaxUV = cSPVector2(-FLT_MAX, -FLT_MAX);
        for (int k = ci.mIndicesStart; k < ci.mIndicesEnd; ++k) {
            cSPVector3 d = positions.At<cSPVector3>(vertIndex[k]) - ci.mCentre;
            cSPVector2 uv(Dot(d, a), -Dot(d, b));
            uvs.At<cSPVector2>(k) = uv;
            if (uv.x < ci.mMinUV.x) ci.mMinUV.x = uv.x;
            if (uv.x > ci.mMaxUV.x) ci.mMaxUV.x = uv.x;
            if (uv.y < ci.mMinUV.y) ci.mMinUV.y = uv.y;
            if (uv.y > ci.mMaxUV.y) ci.mMaxUV.y = uv.y;
        }

        if (normalize) {
            cSPVector2 ext = ci.mMaxUV - ci.mMinUV;
            const float& m = Max(ext.x, ext.y);
            float scale = 1.0f;
            if (m > 0.0001f)
                scale = 1.0f / m;
            for (int k = ci.mIndicesStart; k < ci.mIndicesEnd; ++k) {
                uvs.At<cSPVector2>(k) -= ci.mMinUV;
                uvs.At<cSPVector2>(k) *= scale;
            }
            ci.mMaxUV -= ci.mMinUV;
            ci.mMinUV -= ci.mMinUV;
            ci.mMinUV *= scale;
            ci.mMaxUV *= scale;
        }

        ci.mBoundaryCoords.resize(0);
        if (numBorder != 0) {
            const cSPVector2* uvData = (const cSPVector2*)uvs.mData;
            ci.mBoundaryCoords.insert(ci.mBoundaryCoords.mpBegin,
                                      uvData + ci.mBorderIndicesStart, uvData + ci.mBorderIndicesEnd);
            RemoveDuplicatePoints(&ci.mBoundaryCoords);
            FindConvexHull(ci.mBoundaryCoords.mpBegin, ci.mBoundaryCoords.size(), &ci.mBoundaryCoords);
        }

        // UV-space area: Newell normal of the triangle lifted to 3D (the z coordinates are
        // never set in the original, only the x/y components of the normal are used).
        ci.mTexArea = 0.0f;
        for (int f = ci.mFacesStart; f < ci.mFacesEnd; ++f) {
            int e = mClusterFaces.At<int>(f) * 3;
            const cSPVector2& t0 = uvs.At<cSPVector2>(mClusterIndices.At<int>(e));
            const cSPVector2& t1 = uvs.At<cSPVector2>(mClusterIndices.At<int>(e + 1));
            const cSPVector2& t2 = uvs.At<cSPVector2>(mClusterIndices.At<int>(e + 2));
            cSPVector3 p0, p1, p2;
            p0.x = t0.x; p0.y = t0.y;
            p1.x = t1.x; p1.y = t1.y;
            p2.x = t2.x; p2.y = t2.y;
            float nx = (p0.y - p1.y) * (p0.z + p1.z) + (p1.y - p2.y) * (p1.z + p2.z) + (p2.y - p0.y) * (p2.z + p0.z);
            float ny = (p0.z - p1.z) * (p0.x + p1.x) + (p1.z - p2.z) * (p1.x + p2.x) + (p2.z - p0.z) * (p2.x + p0.x);
            nx *= 0.5f;
            ny *= 0.5f;
            ci.mTexArea += sqrtf(nx * nx + ny * ny);
        }
    }

    AddSectionElement(mMeshData, mSection,
                      AddEltArray(mMeshData, 8 /*kMDTexCoord*/, texCoordSet, 2, 2, uvs),
                      *(const cIndexArrayRef_s0072_5e40*)&mClusterIndices);
}
}  // namespace SP

// @ 0x007269b0
void FUN_007269b0(int* param_1, int param_2, unsigned param_3, int param_4)
{
    if ((unsigned)((param_1[2] - param_1[1]) / 100) < param_3) {
        int   count = (param_1[1] - *param_1) / 100;   // current size
        unsigned cap = count * 2;
        if (count == 0)
            cap = 1;
        unsigned need = count + param_3;
        if (need < cap)
            need = cap;
        int newBuf;
        if (need == 0)
            newBuf = 0;
        else
            newBuf = (int)FUN_00f473a0(need * 100, "Graphics", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                0xd1);
        int oldEnd = param_1[1];
        int oldBeg = *param_1;
        int mid = FUN_00721f50(oldBeg, param_2, newBuf);
        FUN_00720e60(oldBeg, param_2, newBuf);
        FUN_00721ed0(mid, param_3, param_4, mid);      // fill n values
        int afterFill = param_3 * 100 + mid;
        int pos = param_1[1];
        FUN_00721f50(pos, oldEnd, afterFill);          // relocate [pos,end)
        FUN_00720e60(pos, oldEnd, afterFill);
        (void)oldEnd;
        if (oldBeg && *(int*)(oldBeg - 4) != 0)
            FUN_00f47380((void*)oldBeg);
        param_1[1] = afterFill;
        *param_1 = newBuf;
        param_1[2] = need * 100 + newBuf;
    } else if (param_3 != 0) {
        FUN_00721d80(param_4);
        int   end  = param_1[1];
        unsigned old = (unsigned)((param_1[1] - param_2) / 100);
        if (param_3 < old) {
            int cut = end + param_3 * -100;
            FUN_00721e50(&param_4, cut, end, end);
            int oldPos = param_2;
            param_1[1] = param_1[1] + param_3 * 100;
            FUN_00722ac0(param_2, cut, end);
            FUN_00723bf0(oldPos, param_3 * 100 + oldPos, 0);
        } else {
            FUN_00721ed0(end, param_3 - old, 0, param_2);
            int oldPos = param_2;
            param_1[1] = param_1[1] + (param_3 - old) * 100;
            FUN_00721e50(&param_2, param_2, end, param_1[1], param_2);
            param_1[1] = param_1[1] + old * 100;
            FUN_00723bf0(oldPos, end, 0);
        }
    }
}

// @ 0x00726c20
namespace SP {
void QuantizeVertices(cMeshData_s0072_6c20* meshData, float granularity, tQuantizeType quantizeType, const cQuantizeClass* classes)
{
  PushIndices(meshData);
  int pointArrayIndex = FindEltArrayIndex(meshData, 1, 0, 3, 0xe);
  if (pointArrayIndex < 0 || meshData->mEltArrays[pointArrayIndex].mClass != 0)
    return;

  cEltArrayRefT_s0072_6c20<cSPVector3_s0072_6c20> points(meshData->mEltArrays[pointArrayIndex].mArray);
  eastl::hash_map_s0072_6c20<cDecCellID, int> pointMap;
  eastl::fixed_vector_s0072_6c20<int, 256> indicesRemap(points.mNumElts);
  eastl::fixed_vector_s0072_6c20<int, 256> anchorIndices;
  eastl::fixed_vector_s0072_6c20<float, 256> weights;
  cEltArrayT<cSPVector3_s0072_6c20>* newPoints = new ("Graphics", 0, 0, 0, 0) cEltArrayT<cSPVector3_s0072_6c20>;
  int newIndex = 0;

  int index = FindEltArrayIndex(meshData, 9, 0, 9, 0xe);
  cEltArrayRefT_s0072_6c20<tMDShort4_s0072_6c20> boneIndices;
  cEltArrayRefT_s0072_6c20<tMDUByte4_s0072_6c20> boneIndicesB;
  if (index >= 0) {
    boneIndices = meshData->mEltArrays[index].mArray;
    if (boneIndices.mNumElts != points.mNumElts)
      boneIndices = cEltArrayRefT_s0072_6c20<tMDShort4_s0072_6c20>();
  } else {
    index = FindEltArrayIndex(meshData, 9, 0, 7, 0xe);
    if (index >= 0) {
      boneIndicesB = meshData->mEltArrays[index].mArray;
      if (boneIndicesB.mNumElts != points.mNumElts)
        boneIndicesB = cEltArrayRefT_s0072_6c20<tMDUByte4_s0072_6c20>();
    }
  }

  cEltArrayRefT_s0072_6c20<long> classIndices;
  cQuantizeClass defaultClass;
  if (classes) {
    defaultClass = classes[0];
    index = FindEltArrayIndex(meshData, 0x18, 0, 6, 0xe);
    if (index >= 0)
      classIndices = meshData->mEltArrays[index].mArray;
  }

  index = FindEltArrayIndex(meshData, 2, 0, 3, 0xe);
  cEltArrayRefT_s0072_6c20<cSPVector3_s0072_6c20> normals;
  if (index >= 0) {
    normals = meshData->mEltArrays[index].mArray;
    if (normals.mNumElts != points.mNumElts)
      normals = cEltArrayRefT_s0072_6c20<cSPVector3_s0072_6c20>();
  }

  index = FindEltArrayIndex(meshData, 2, 0, 7, 0xe);
  cEltArrayRefT_s0072_6c20<uint32_t> packedNormals;
  if (index >= 0) {
    packedNormals = meshData->mEltArrays[index].mArray;
    if (packedNormals.mNumElts != points.mNumElts)
      packedNormals = cEltArrayRefT_s0072_6c20<uint32_t>();
  }

  eastl::fixed_vector_s0072_6c20<int, 8> sectionStarts;
  index = FindEltArrayIndex(meshData, 0x19, 0, 6, 0xe);
  if (index >= 0) {
    cEltArrayRefT_s0072_6c20<int> starts(meshData->mEltArrays[index].mArray);
    const uint8_t* p = starts.mData;
    for (int j = 0; j < starts.mNumElts; j++) {
      sectionStarts.push_back(*(const int*)p);
      p += starts.mEltStride;
    }
  } else {
    sectionStarts.push_back(0);
    sectionStarts.push_back(points.size());
  }

  int ns = sectionStarts.size() - 1;
  for (int is = 0; is < ns; is++) {
    for (int i = sectionStarts[is]; i < sectionStarts[is + 1]; i++) {
      int classIdx = 0;
      const cQuantizeClass* info = &defaultClass;
      if (boneIndices.mData) {
        classIdx = boneIndices[i].m0 / 3;
        if (classIndices.mData)
          info = &classes[classIndices[classIdx]];
      } else if (boneIndicesB.mData) {
        classIdx = boneIndicesB[i].m0 / 3;
        if (classIndices.mData)
          info = &classes[classIndices[classIdx]];
      }

      float scale = info->mScale * granularity;
      cSPVector3_s0072_6c20 v(points[i]);
      cDecCellID cellID(RoundToInt(v.x * scale), RoundToInt(v.y * scale), RoundToInt(v.z * scale));
      cellID.m[0] ^= -(int)info->mUseBoneClass & (classIdx << 24);
      cellID.m[1] ^= info->mFlagB << 24;
      cellID.m[2] ^= is << 27;
      if (normals.mData) {
        cSPVector3_s0072_6c20 n(normals[i]);
        uint32_t nx = *(uint32_t*)&n.x;
        uint32_t ny = *(uint32_t*)&n.y;
        uint32_t nz = *(uint32_t*)&n.z;
        cellID.m[2] ^= ((((nz >> 29) & 4) + ((ny >> 30) & 2) + (nx >> 31)) & info->mNormalMask) << 24;
      }
      if (packedNormals.mData) {
        uint32_t p = packedNormals[i];
        cellID.m[2] ^= (((((p >> 16) & 0xff) >> 5 & 4) + (((p >> 8) & 0xff) >> 6 & 2) + ((p & 0xff) >> 7)) &
                        info->mNormalMask)
                       << 24;
      }

      eastl::hash_map_s0072_6c20<cDecCellID, int>::iterator it = pointMap.find(cellID);
      if (it != pointMap.end()) {
        indicesRemap[i] = it->second;
        cSPVector3_s0072_6c20& p = newPoints->mEltData[it->second];
        p.x = v.x + p.x;
        p.y = p.y + v.y;
        p.z = p.z + v.z;
        weights[it->second] += 1.0f;
      } else {
        indicesRemap[i] = newIndex;
        pointMap[cellID] = newIndex;
        newIndex++;
        newPoints->mEltData.push_back(v);
        weights.push_back(1.0f);
        if (quantizeType)
          anchorIndices.push_back(i);
      }

      if ((i & 0xfff) == 0)
        EA::Thread::ThreadSleep(0);
    }
  }
  EA::Thread::ThreadSleep(0);

  for (int i = 0; i < newIndex; i++) {
    float inv = 1.0f / weights[i];
    cSPVector3_s0072_6c20& p = newPoints->mEltData[i];
    p.x = inv * p.x;
    p.y = inv * p.y;
    p.z = p.z * inv;
  }

  meshData->mEltArrays[pointArrayIndex].mArray = newPoints->AsRef();

  int numSections = meshData->mSections.size();
  for (int is = 0; is < numSections; is++) {
    int oldEltIndicesIndex = FindSectionEltIndex(meshData, is, pointArrayIndex);
    if (oldEltIndicesIndex < 0)
      continue;
    cIndexArrayRef_s0072_6c20 srcEltIndices(
        meshData->mSections[is].mEltIndices[meshData->mSections[is].mFormat[oldEltIndicesIndex].mIndices]);
    cIndexArrayRef_s0072_6c20 dstEltIndices;
    CreateArray(srcEltIndices, dstEltIndices);
    cIndexArrayRef_s0072_6c20 dstEltIndicesPC;
    if (quantizeType)
      CreateArray(srcEltIndices, dstEltIndicesPC);

    if (srcEltIndices.mEltSize == 4) {
      if (quantizeType) {
        for (int i = 0; i < srcEltIndices.mNumElts; i++) {
          dstEltIndices.Int(i) = indicesRemap[srcEltIndices.Int(i)];
          dstEltIndicesPC.Int(i) = anchorIndices[dstEltIndices.Int(i)];
        }
      } else {
        for (int i = 0; i < srcEltIndices.mNumElts; i++)
          dstEltIndices.Int(i) = indicesRemap[srcEltIndices.Int(i)];
      }
    } else if (srcEltIndices.mEltSize == 2) {
      if (quantizeType) {
        for (int i = 0; i < srcEltIndices.mNumElts; i++) {
          dstEltIndices.UShort(i) = (uint16_t)indicesRemap[srcEltIndices.UShort(i)];
          dstEltIndicesPC.UShort(i) = (uint16_t)anchorIndices[dstEltIndices.UShort(i)];
        }
      } else {
        for (int i = 0; i < srcEltIndices.mNumElts; i++)
          dstEltIndices.UShort(i) = (uint16_t)indicesRemap[srcEltIndices.UShort(i)];
      }
    }

    cMDSection_s0072_6c20& section = meshData->mSections[is];
    int newEltIndicesIndex = section.mEltIndices.size();
    section.mEltIndices.push_back(dstEltIndices);
    short& formatIndices = section.mFormat[oldEltIndicesIndex].mIndices;
    oldEltIndicesIndex = formatIndices;
    formatIndices = (short)newEltIndicesIndex;
    if (quantizeType) {
      int newEltIndicesPCIndex = section.mEltIndices.size();
      section.mEltIndices.push_back(dstEltIndicesPC);
      for (int f = 0; f < section.mFormat.size(); f++) {
        if (section.mFormat[f].mIndices == oldEltIndicesIndex &&
            (quantizeType == kQuantizeAll ||
             meshData->mEltArrays[section.mFormat[f].mElts].mClass == 0))
          section.mFormat[f].mIndices = (short)newEltIndicesPCIndex;
      }
    }
    EA::Thread::ThreadSleep(0);
  }
}
}  // namespace SP

// @ 0x00728020
void FUN_00728020(MeshCtx* ctx, float f, int mode, void* p4)
{
    if (ctx->end - ctx->begin != 0) {
        FUN_00726c20(ctx, f, 1, p4);
        int z = 0;
        FUN_00921df0(&z);
        FUN_00725130(ctx);
        z = 0;
        FUN_00921df0(&z);
        FUN_00735a90(ctx);
        z = 0;
        FUN_00921df0(&z);
        FUN_00737ef0(ctx);
        z = 0;
        FUN_00921df0(&z);
    }
}

// @ 0x007280b0
void FUN_007280b0(void* self, void* param_2, int param_3, int param_4, int param_5)
{
    (void)self; (void)param_2; (void)param_3; (void)param_4; (void)param_5;
}

// @ 0x007281d0
void FUN_007281d0(void* self)
{
    (void)self;
}

// @ 0x00728330
void FUN_00728330(void* self, unsigned n)
{
    (void)self; (void)n;
}

// @ 0x00728400
void FUN_00728400(void* self, unsigned a, unsigned b)
{
    (void)self; (void)a; (void)b;
}

// @ 0x007285a0
void FUN_007285a0(void* self)
{
    (void)self;
}

// @ 0x007289a0
void FUN_007289a0(void* self)
{
    (void)self;
}

// @ 0x00728af0
void FUN_00728af0(void* self, void* meshData, int n)
{
    (void)self; (void)meshData; (void)n;
}

// @ 0x00728c90
void __cdecl FUN_00728c90(UV::PtrVec* meshes, float clusterParam, const float* scales, const UV::MeshXform* info)
{
    using namespace UV;
    ChartVec_s0072_8c90 charts;
    RectVec  rects;
    charts.reserve(0x20);
    int prop = g_AppProps->GetIntProperty(0x04474195);
    int nMeshes = (int)(meshes->mpEnd - meshes->mpBegin);
    float totalTexArea = 0.0f;

    for (int i = 0; i < nMeshes; ++i) {
        MeshClusterer mc;
        mc.Cluster(meshes->mpBegin[i], clusterParam);
        ThreadSleep(0);
        mc.AssignCharts(1, 1, 1);
        ThreadSleep(0);
        int nClusters = (int)(mc.cEnd - mc.cBegin);
        for (int j = 0; j < nClusters; ++j) {
            ClusterInfo& c = mc.cBegin[j];
            if (info) {
                float sc = info[i].scale;
                float a = c.area * sc;
                c.area = a * sc;
            }
            if (prop == 2) {
                float tex = c.texArea;
                ChartRect r(c.indicesStart, c.indicesEnd, c.area * tex, i, c.minUV, c.maxUV,
                            c.maxUV.x - c.minUV.x, c.maxUV.y - c.minUV.y);
                if (scales) r.prim = scales[i] * r.prim;
                totalTexArea = tex + totalTexArea;
                rects.push_back(r);
            } else {
                charts.push_back0();
                Chart& ch = charts.mpEnd[-1];
                ch.meshIndex = i;
                ch.texArea = c.texArea;
                ch.primArea = c.area;
                ch.texStart = c.indicesStart;
                ch.texEnd = c.indicesEnd;
                ch.boundaries.Assign(c.boundary);
                ch.texBound.x = c.maxUV.x - c.minUV.x;
                ch.texBound.y = c.maxUV.y - c.minUV.y;
                float dot = c.nz;
                if (info && (info[i].flags & 2))
                    dot = (info[i].vy * c.ny + info[i].vx * c.nx) + c.nz * info[i].vz;
                if (dot < -0.95f && c.area > 30.0f) {
                    ch.primArea = 1.0e-4f;
                    ch.boundaries.clear();
                    ch.boundaries.resize((unsigned)(c.boundary.mpEnd - c.boundary.mpBegin), g_Vec2Zero);
                    ch.texBound.x = ch.texBound.x * 1.0e-5f;
                    ch.texBound.y = ch.texBound.y * 1.0e-5f;
                    ch.flag = 1;
                }
                if (scales)
                    ch.primArea = scales[i] * ch.primArea;
            }
        }
        ThreadSleep(0);
    }

    if (prop == 2) {
        RectPackCharts(meshes, &rects, totalTexArea, 0x200);
    } else {
        ClusterMap cm;
        cm.Build(meshes);
        int nCharts = (int)(charts.mpEnd - charts.mpBegin);
        for (int k = 0; k < nCharts; ++k)
            cm.AddCluster(charts.mpBegin + k);
        ThreadSleep(0);
        cm.Pack(prop);
    }

    int n2 = (int)(meshes->mpEnd - meshes->mpBegin);
    for (int k = 0; k < n2; ++k) {
        FinishMesh(meshes->mpBegin[k]);
        ThreadSleep(0);
    }
}

// @ 0x00729290
int FUN_00729290(void* self)
{
    (void)self;
    return 1;
}

// @ 0x00735470
void FUN_00735470(void)
{
    // PARTIAL: ~1.2 KB container routine; skeleton only.
}

// @ 0x00735960
void FUN_00735960(int* param_1, int* param_2)
{
    // PARTIAL: refcounted element list builder with EH; skeleton only.
    (void)param_1; (void)param_2;
}

// @ 0x007366e0
void FUN_007366e0(int param_1)
{
    // PARTIAL: rebuild per-cluster index arrays (0x8c-byte records, refcounted); skeleton only.
    (void)param_1;
}

// @ 0x007368a0
void FUN_007368a0(int* param_1)
{
    // PARTIAL: rebuild reverse index streams with refcounted EltArrays; skeleton only.
    (void)param_1;
}

// @ 0x0073a4b0
void QuadricVectorResize(void* self, uint32_t n)
{
    (void)self; (void)n;
}
