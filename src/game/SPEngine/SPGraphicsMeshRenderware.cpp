// src/game/SPEngine/SPGraphicsMeshRenderware.cpp -- migrated from slice(s) s0072c270, s0072b630, s00728c90, s0072aaf0, s00729bd0 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsMeshRenderware.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "rw/graphics/BuildState.h"
#include "rw/graphics/EmbeddedState.h"
#include "SP/cTriToRegionMap.h"
#include <intrin.h>
#include <string.h>
#include "SP/cClusterInfo.h"
#include "SP/cMeshClusterer.h"
#include "rw/graphics/VertexBuffer.h"
#include "cSPVector2.h"
#include "rw/graphics/IndexBuffer.h"
#include "rw/graphics/VertexDescriptor.h"
#include "SP/cEltArrayRef.h"
#include "SP/cIndexArrayRef.h"
#include "SP/cMDElementArray.h"
#include "SP/cMDFormatEntry.h"
#include "SP/cMDPrimitive.h"
#include "SP/cMDSection.h"
#include "SP/cMaterialManager.h"
#include "SP/cMeshData.h"
#include <xmmintrin.h>

// ---- items of slice s0072aaf0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* FUN_00f473a0(unsigned size, const char* name, int f, int df, const char* file, int line);
extern "C" void FUN_0072a1a0(void* self, int count, void* pool);  // 0x0072a1a0
extern "C" void* FUN_0072aa80(void* self, int a, int* b);         // 0x0072aa80
extern void* const vtbl_Init0;  // 0x013eb938  (??_7ITracerBase@Trace@EA@@6B@)
extern void* const vtbl_Init1;  // 0x013ef094  (??_7hkReferencedObject@@6B@)
extern void* const vtbl_Final0; // 0x0140a660  (AddRef thunk)
extern void* const vtbl_Final1; // 0x0140d178
extern const uint32_t kIndexMasks[];     // 0x0140d15c
extern int  ToD3DDeclType(int type);                                              // 0x00729560
extern int  ToRwDecl(int semantic, int index);                                    // 0x007295f0
extern void ReleaseObject(void* p);                                               // 0x00761170
extern void CompiledStateBegin(void* cs, void* unused);                           // 0x011fd7b0
extern void* LockIndexSpan(int n);                                                // 0x011fd7e0
extern void UnlockIndexSpan();                                                    // 0x011fd820
extern void IndexSpanEnd();                                                       // 0x011fd7d0
extern void PushShaderDataNull();                                                 // 0x00777bf0
extern void PopShaderData();                                                      // 0x00777c10
extern void D3D9Sync();                                                           // 0x011f21a0
extern const int kRwPrimTypes[];         // 0x01536f0c
extern int gActivePrimType;              // 0x016f85a8
extern unsigned gSoftStateUpdated;       // 0x016f9110
void operator_delete(void* p);   // 0x00f47380
const char kEastlAllocatorFile[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";
struct TriRegionEntry {
    int mRegionId;   // +0
    int mBegin;      // +4
    int mEnd;        // +8
};
struct TriRegionVec {
    TriRegionEntry* mpBegin;
    TriRegionEntry* mpEnd;
    TriRegionEntry* mpCap;
    // The grow path of AddRegion: the vector comes in ecx (0x0072b616 leaves this there, which is
    // the address of mRegions) and the callee pops both stack arguments (`ret $0x8`), so it is a
    // thiscall member, not a cdecl function.
    void insert(TriRegionEntry* pos, const TriRegionEntry& value);   // 0x007409d0
};
struct cTriToRegionMap_s0072_aaf0 {
    TriRegionVec mRegions;
    void AddRegion(int begin, int end, int id);  // 0x0072b560 (cTriToRegionMap::AddRegion)
};
struct Vec4 {
    int* mpBegin;      // +0x00
    int* mpEnd;        // +0x04
    int* mpCap;        // +0x08
    void* mpAlloc;     // +0x0c
    int* mpPool;       // +0x10  (inline buffer start)

    void DoInsertValue(int* pos, const int* value);   // 0x0072aaf0
};
struct SpanHolder {
    int* mpBegin;   // +0
    int* mpEnd;     // +4
    SpanHolder* Init(const int* span);   // 0x0072ac10
};
struct IntSpan {
    int* mpBegin;   // +0
    int* mpEnd;     // +4
    int  mpPad8;    // +8
    int* mpPool;    // +0xc
};
struct RefObj_s0072_aaf0 {
    void** mpVtbl0;      // +0x00  (ITracerBase then AddRef thunk vtable)
    void** mpVtbl1;      // +0x04
    volatile long mRef;  // +0x08
    char  mPayload[0x14];// +0x0c
    int   mField20;      // +0x20
    RefObj_s0072_aaf0* Ctor(int arg);   // 0x0072ac60
};
struct IRefObject {                       // virtual AddRef/Release (slots 0/1)
    virtual int AddRef();
    virtual int Release();
};
void operator_delete__(void* p) throw();  // 0x00f47380
template <typename T>
struct vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator;
    int size() const { return (int)(mpEnd - mpBegin); }
};
template <typename T, int N>
struct fixed_vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mOverflow;
    T* mpPoolBegin;
    uint32_t mPad;
    T mBuffer[N];

    fixed_vector() {
        mpBegin = mBuffer;
        mpEnd = mBuffer;
        mpCapacity = mBuffer + N;
        mpPoolBegin = mBuffer;
    }
    ~fixed_vector() {
        if (mpBegin && mpBegin != mpPoolBegin)
            operator_delete__(mpBegin);
    }
    int size() const { return (int)(mpEnd - mpBegin); }
    void DoInsertValue(T* position, const T& value);
    void push_back(const T& value) {
        if (mpEnd < mpCapacity) {
            T* p = mpEnd++;
            if (p) *p = value;
        } else
            DoInsertValue(mpEnd, value);
    }
};
struct DataAccessor {
    int         mCount;                  // +0x0
    char*       mpData;                  // +0x4
    uint16_t    mFormat;                 // +0x8  (element byte size / index width)
    uint16_t    mStride;                 // +0xa
    IRefObject* mpOwner;                 // +0xc

    DataAccessor() : mCount(0), mpData(0), mFormat(4), mStride(4), mpOwner(0) {}
    ~DataAccessor() { if (mpOwner) mpOwner->Release(); }
    __forceinline DataAccessor& operator=(const DataAccessor& x) {
        IRefObject* p = x.mpOwner;
        mCount = x.mCount;
        mpData = x.mpData;
        mFormat = x.mFormat;
        mStride = x.mStride;
        if (p != mpOwner) {
            if (p) p->AddRef();
            IRefObject* old = mpOwner;
            mpOwner = p;
            if (old) old->Release();
        }
        return *this;
    }
    uint32_t Index(int i) const { return *(uint32_t*)(mpData + mStride * i) & kIndexMasks[mFormat]; }
};
struct MeshElement {                     // 0x20
    int          mSemantic;              // +0x00
    int          mSemanticIndex;         // +0x04
    int          mDataType;              // +0x08
    int          mStream;                // +0x0c
    DataAccessor mData;                  // +0x10
};
struct ElementRef { int16_t mElement; int16_t mIndexTable; };
struct SubMesh {                         // 0x8c
    DataAccessor         mIndices;       // +0x00
    int                  mVertexCount;   // +0x10
    vector<ElementRef>   mElements;      // +0x14
    uint32_t             pad24[8];       // +0x24
    vector<DataAccessor> mIndexTables;   // +0x44
    uint32_t             pad54[14];      // +0x54
};
struct PrimitiveGroup {                  // 0x14
    int mPrimType;
    int mSubMesh;
    int mStart;
    int mEnd;
    int mMaterial;
};
struct SourceMesh {
    uint32_t                pad0[2];
    MeshElement*            mpElements;  // +0x08
    uint32_t                padC[4];
    vector<SubMesh>         mSubMeshes;  // +0x1c
    uint32_t                pad2C;
    vector<PrimitiveGroup>  mPrims;      // +0x30
};
struct VertexElement { uint16_t stream, offset; uint8_t type, method, usage, usageIndex; int rwDecl; };
struct VertexDescription {
    void*    pNextParent;
    void*    pNextSibling;
    void*    pDXDecl;
    uint16_t elementsCount;
    uint8_t  lockFlags;                  // +0x0e
    uint8_t  stride;                     // +0x0f
    int      elementsUsed;
    int      elementsHash;
    VertexElement elements[1];           // +0x18
    void Finalize();                     // 0x011f3220
};
struct BuildState {
    void SetField1230(int a, int b);                       // 0x011f9c10
    void D3D9SetVertexDescriptor(VertexDescription* d, int flags);   // 0x011f9e20
};
struct ShaderDataItem {
    char pad[8];
    void Push();                                           // 0x007789d0
};
struct EmbeddedState {
    char pad00[8];
    uint32_t mSoftStateDirty;                              // +0x08
    int* D3D9GetShaderData(int id);                        // 0x011edcf0
    void Dispatch();                                       // 0x011ee580
};
struct Material { int pad; EmbeddedState* mpState; };
struct IMaterialManager {
virtual void f00();
virtual void f04();
virtual void f08();
virtual void f0c();
virtual void f10();
virtual void f14();
virtual void f18();
virtual void f1c();
virtual void f20();
virtual void f24();
    virtual Material* GetMaterial(uint32_t id);            // +0x28
};
struct ShaderMapEntry { int key; ShaderDataItem* value; };
struct ShaderMap { ShaderMapEntry* mpBegin; ShaderMapEntry* mpEnd; };
struct DrawStats { char pad[0x20]; int mVerts; int pad24; int mBatches; };
extern int  FindElement(SourceMesh* mesh, int semantic, int index, int a, int b);  // 0x0071ddc0
extern VertexDescription* CreateVertexDescriptor(int n);                          // 0x00761650
extern BuildState* CreateVertexBuffer(unsigned flags, int b);                     // 0x007616f0
extern void* CreateCompiledState(BuildState* bs);                                 // 0x007617a0
extern IMaterialManager* MaterialManager();                                       // 0x0067dd70
extern void DestroyBuildState(BuildState* p);                                     // 0x00761150
extern void DestroyVertexDescriptor(VertexDescription* p);                        // 0x00761130
extern void SetShaderData(EmbeddedState* s);                                      // 0x00777b50
extern void SetVertexDescriptor(VertexDescription* d);                            // 0x007611a0
extern int  VertexDescriptorAreEqual(VertexDescription* a, VertexDescription* b); // 0x011f2e70
extern VertexDescription* gActiveVertexDesc;   // 0x016f65a0
struct VDescRefresh { void Refresh(); };  // 0x011f2bc0 (thiscall)
// ---- items of slice s0072aaf0 end

// ---- items of slice s00728c90 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* g_162b1f0;
extern const unsigned int DAT_0140d15c[];
struct C29820 {
    int   f0;
    int   f1;
    float f2, f3, f4, f5, f6, f7;
    int   f8, f9, f10, f11, f12;
    C29820* Init(int a, float* b, int c, int d);
};
struct C29ad0 {
    char* mpBegin;   // +0
    char* mpEnd;     // +4
    int   Find(int x);
};
struct C29a70 {
    char   pad[0x2c];
    C29a70* mp2c;   // +0x2c
    C29a70* mp30;   // +0x30
    void Free();
};
struct ChartNode {
    uint8_t  pad00[0x08];
    int      mSlotLo[3];                                       // +0x08  (read through mpB)
    int      mSlotHi[3];                                       // +0x14  (read through mpA)
    int      mA20;                                             // +0x20
    int      mA24;                                             // +0x24
    int      mIndex;                                           // +0x28
    ChartNode* mpA;                                            // +0x2c
    ChartNode* mpB;                                            // +0x30
};
struct OutRec {
    int mNode;                                                 // +0x00
    int mIndex;                                                // +0x04
    int mLoA;                                                  // +0x08
    int mLoB;                                                  // +0x0c
    int mMarkA;                                                // +0x10
    int mMarkB;                                                // +0x14
    int mValA;                                                 // +0x18
    int mValB;                                                 // +0x1c
};
struct OutBuf {
    OutRec* mpRec;                                             // +0x00
    int     mCount;                                            // +0x04
};
struct Win29990 {
    int        mParent;                                        // +0x00
    int        mFlag;                                          // +0x04
    ChartNode* mpDesc;                                         // +0x08
};
struct VDesc {
    uint8_t pad00[0x0f];
    uint8_t mStride;                                           // +0x0f
};
struct VBi {
    VDesc*   m_desc;                                           // +0x00
    uint8_t  pad04[4];
    int      m_base;                                           // +0x08
    int      m_numVertices;                                    // +0x0c
    uint8_t  pad10[8];
    void*    m_disposableBuffer;                               // +0x18

    unsigned Lock(unsigned char flag, unsigned start, unsigned count);   // 0x011f3620
    void*    Unlock();                                                   // 0x011f36a0
};
typedef void (__thiscall *VSlot0)(void*);
static inline void CallSlot0(void* p)
{
    VSlot0* vt = *(VSlot0**)p;
    vt[0](p);
}
void* __cdecl FUN_00720010(int size);                          // 0x00720010 AllocEltBuffer
void* __cdecl MemCopy(void* dst, const void* src, unsigned n); // 0x011e0744 memcpy
// ---- items of slice s00728c90 end

// ---- items of slice s00729bd0 begin (TODO(rewrite): local stubs, replace by canonical classes)

extern "C" void  FUN_0042f0a0(void* p, int n, void* local, int m);                 // 0x0042f0a0
extern "C" int   FUN_0071ddc0(void* p, int a, int b, int c, int d);                // 0x0071ddc0
extern "C" double sqrt(double x);                                                  // CRT: inlined as fsqrt
struct IBuf {
    uint8_t  pad00[8];                                                      // +0x00
    int      mCount;                                                        // +0x08
    uint8_t  pad0c[0x0c];                                                   // +0x0c .. +0x17
    void*    mpData;                                                        // +0x18

    unsigned Lock(unsigned n, void* pOut);                                  // 0x011f4f20
    void*    Unlock(void** pIn);                                            // 0x011f4fd0
};
struct Box { float mn[3]; float mx[3]; };
struct SplitNode {            // 0x40 bytes; also the scratch type FUN_0072a080 resets
    int      axis;            // +0
    float    pos;             // +4
    unsigned nLeft;           // +8
    unsigned nRight;          // +0xc
    Box      left;            // +0x10
    Box      right;           // +0x28
};
struct SpanIter {
    int   count;   // +0
    int   base;    // +4
    short a;       // +8
    short b;       // +0xa
    int*  owner;   // +0xc
};
struct SpanOwner {
    void*  vptr;   // +0
    char   pad4[8];
    int*   mpBegin;   // +0xc
    int*   mpEnd;     // +0x10
    SpanIter* MakeIter(SpanIter* out);
};
struct SpanAlloc {
    int* mpBegin;   // +0
    int* mpEnd;     // +4
    int* mpCap;     // +8
    int  pad0;      // +0xc
    int  stride;    // +0x10
    SpanAlloc* Init(int n, int* other);
};
struct LockHandle {
    void* mpPtr;                                                            // +0x00
    void* mpPad1;                                                           // +0x04
    void* mpPad2;                                                           // +0x08
};
struct RefObj {
    void** vptr;                                                            // +0x00

    void AddRef()  { ((void (__thiscall*)(RefObj*))vptr[0])(this); }
    void Release() { ((void (__thiscall*)(RefObj*))vptr[1])(this); }
};
struct MeshModel {
    uint8_t pad00[8];                                                       // +0x00 .. +0x07
    void*   mpStreams;                                                      // +0x08
};
struct MeshStream {
    int            nCount;                                                  // +0x10
    const float*   mpVerts;                                                 // +0x14
    uint16_t       mUnk18;                                                  // +0x18
    uint16_t       mStride;                                                 // +0x1a  byte stride between vertices
    RefObj*        mpOwner;                                                 // +0x1c
};
struct StreamRecord {
    uint8_t    pad00[0x10];                                                 // +0x00 .. +0x0f
    MeshStream entry;                                                       // +0x10
};
struct Vec3 { float x, y, z; };
struct Box6 {
    Vec3 mn;                                                                // +0x00
    Vec3 mx;                                                                // +0x0c
};
static inline void ExpandPoint(Box6& cur, const float* v)
{
    if (cur.mn.x > cur.mx.x) {
        cur.mn = *(const Vec3*)v;
        cur.mx = *(const Vec3*)v;
    } else {
        if (cur.mn.x > v[0]) cur.mn.x = v[0];
        else if (v[0] > cur.mx.x) cur.mx.x = v[0];
        if (cur.mn.y > v[1]) cur.mn.y = v[1];
        else if (v[1] > cur.mx.y) cur.mx.y = v[1];
        if (cur.mn.z > v[2]) cur.mn.z = v[2];
        else if (v[2] > cur.mx.z) cur.mx.z = v[2];
    }
}
static inline void ExpandBox(Box& cur, const Box& e)
{
    if (cur.mn[0] <= cur.mx[0]) {
        if (cur.mn[0] > e.mn[0]) cur.mn[0] = e.mn[0];
        if (e.mx[0] > cur.mx[0]) cur.mx[0] = e.mx[0];
        if (cur.mn[1] > e.mn[1]) cur.mn[1] = e.mn[1];
        if (e.mx[1] > cur.mx[1]) cur.mx[1] = e.mx[1];
        if (cur.mn[2] > e.mn[2]) cur.mn[2] = e.mn[2];
        if (e.mx[2] > cur.mx[2]) cur.mx[2] = e.mx[2];
    } else {
        cur = e;
    }
}
float FUN_007298b0(const Box* box, const SplitNode* node);
static inline float SurfaceArea(const Box& b)
{
    float dx = b.mx[0] - b.mn[0];
    float dy = b.mx[1] - b.mn[1];
    float dz = b.mx[2] - b.mn[2];
    return ((dz * dx) + (dy * dx) + (dz * dy)) * 2.0f;
}
struct Scratch48 {
    int w0, w1, w2, w3, w4, w5, w6, w7, w8, w9, w10, w11;
};
struct EAArray {
    void* mpBegin;                                                          // +0x00
    void* mpEnd;                                                            // +0x04
    void* mpCap;                                                            // +0x08

    EAArray* Init(int n, int reserved);
};
struct NodeAllocator {
    void* Malloc();                                                         // 0x004fde40
};
extern NodeAllocator gNodeAllocator;                                        // 0x0162b1e0
struct BspNode {
    void*    mpOwner;                                                       // +0x00  tree this node lives in
    int      mLevel;                                                        // +0x04  level in the tree (parent + 1)
    Box      mBox;                                                          // +0x08  bounds of this node's slice
    unsigned mFirst;                                                        // +0x20  offset of the slice's first index
    unsigned mCount;                                                        // +0x24  number of indices in the slice
    int      mAxis;                                                         // +0x28  axis the parent split on
    BspNode* mpLeft;                                                        // +0x2c  below-plane child (0 if unsplit)
    BspNode* mpRight;                                                       // +0x30  above-plane child (0 if unsplit)

    // 0x00729820
    BspNode* Init(void* owner, float* box, int first, int count);
    int      Build(Box* const* items, unsigned* idx, unsigned n, int depth);
};
// ---- items of slice s00729bd0 end

// ---- items of slice s0072b630 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const char kIndexFormat32[8];     // 0x015d07b8
extern const char kIndexFormat16[8];     // 0x015d07b0
void FUN_0072b630(void* mesh, void* a, void* b, void* c, void* d, void* e, void* f, void* g, void* h);
struct RefCounted {                       // EA-style intrusive refcount at +4
    virtual ~RefCounted();
    int mnRefCount;
    void AddRef() { _InterlockedIncrement((volatile long*)&mnRefCount); }
    void Release() {
        if (_InterlockedDecrement((volatile long*)&mnRefCount) == 0) {
            _InterlockedExchange((volatile long*)&mnRefCount, 1);
            delete this;
        }
    }
};
template <typename T>
struct intrusive_ptr {
    T* mpObject;
    intrusive_ptr() : mpObject(0) {}
    intrusive_ptr(const intrusive_ptr& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~intrusive_ptr() { if (mpObject) mpObject->Release(); }
};
template <typename T>
struct vector_s0072_b630 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator;
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
    T& operator[](unsigned i) { return mpBegin[i]; }
    void DoInsertValue(T* position, const T& value);  // 0x00621fc0 (vector::DoInsertValue)
    void push_back(const T& value) {
        if (mpEnd < mpCapacity)
            ::new(mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);  // 0x00621fc0 (vector::DoInsertValue)
    }
};
inline void* operator new(unsigned, void* p) { return p; }
template <typename T, int N>
struct fixed_vector_s0072_b630 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mOverflow;
    T* mpPoolBegin;
    uint32_t mPad;
    T mBuffer[N];

    fixed_vector_s0072_b630() {
        mpBegin = mBuffer;
        mpEnd = mBuffer;
        mpCapacity = mBuffer + N;
        mpPoolBegin = mBuffer;
    }
    ~fixed_vector_s0072_b630() {
        if (mpBegin && mpBegin != mpPoolBegin)
            operator_delete__(mpBegin);
    }
    bool empty() const { return mpBegin == mpEnd; }
    int size() const { return (int)(mpEnd - mpBegin); }
    T& operator[](int i) { return mpBegin[i]; }
    void DoInsertValue(T* position, const T& value);
    void push_back(const T& value) {
        if (mpEnd < mpCapacity)
            ::new(mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
};
struct DataAccessor_s0072_b630 {
    int         mCount;                  // +0x0
    char*       mpData;                  // +0x4
    uint16_t    mFormat;                 // +0x8
    uint16_t    mStride;                 // +0xa
    IRefObject* mpOwner;                 // +0xc

    DataAccessor_s0072_b630() : mCount(0), mpData(0), mFormat(4), mStride(4), mpOwner(0) {}
    ~DataAccessor_s0072_b630() { if (mpOwner) mpOwner->Release(); }
    __forceinline DataAccessor_s0072_b630& operator=(const DataAccessor_s0072_b630& x) {
        IRefObject* p = x.mpOwner;
        mCount = x.mCount;
        mpData = x.mpData;
        mFormat = x.mFormat;
        mStride = x.mStride;
        if (p != mpOwner) {
            if (p) p->AddRef();
            IRefObject* old = mpOwner;
            mpOwner = p;
            if (old) old->Release();
        }
        return *this;
    }
    template <typename T> T* At(int i) const { return (T*)(mpData + mStride * i); }
    template <typename T> T Index(int i) const { return *At<T>(i) & (T)kIndexMasks[mFormat]; }
};
struct MeshElement_s0072_b630 {                     // 0x20
    int          mSemantic;              // +0x00
    int          mSemanticIndex;         // +0x04
    int          mDataType;              // +0x08
    int          mStream;                // +0x0c
    DataAccessor_s0072_b630 mData;                  // +0x10
};
struct SubMesh_s0072_b630 {                         // 0x8c
    DataAccessor_s0072_b630         mIndices;       // +0x00
    int                  mVertexCount;   // +0x10
    vector_s0072_b630<ElementRef>   mElements;      // +0x14
    uint32_t             pad24[8];       // +0x24
    vector_s0072_b630<DataAccessor_s0072_b630> mIndexTables;   // +0x44
    uint32_t             pad54[14];      // +0x54
};
struct SourceMesh_s0072_b630 {
    uint32_t                pad0[2];
    MeshElement_s0072_b630*            mpElements;  // +0x08
    uint32_t                padC[4];
    vector_s0072_b630<SubMesh_s0072_b630>         mSubMeshes;  // +0x1c
    uint32_t                pad2C;
    vector_s0072_b630<PrimitiveGroup>  mPrims;      // +0x30
};
struct VertexBuffer {
    VertexDescription* mpDesc;
    uint32_t pad4;
    int      mBaseVertex;                // +0x08
    int      mNumVertices;               // +0x0c
    void* Lock(int flags, int offset, int size);   // 0x011f3620
    void  Unlock();                                 // 0x011f36a0
};
struct VertexStream { char* mpData; int mStride; };
struct VertexBufferLock {
    char*         mpData;
    VertexBuffer* mpBuffer;
    void GetElementStream(VertexStream* out, int element);   // 0x011f9ae0
};
struct IndexLock { void* mpData; uint32_t pad[2]; };
struct IndexBuffer {
    uint32_t pad0[2];
    int      mNumIndices;                // +0x08
    int  Lock(int flags, IndexLock* out); // 0x011f4f20
    void Unlock(IndexLock* lock);         // 0x011f4fd0
};
struct RwMesh {
    void SetVertexBuffer(int stream, VertexBuffer* vb);  // 0x011f9670
    void SetIndexBuffer(IndexBuffer* ib);                // 0x011f96e0
    void SetIndexCount(int n);                           // 0x011f96b0
};
struct Material;
typedef intrusive_ptr<RefCounted> TexturePtr;
extern int  FindElement(SourceMesh_s0072_b630* mesh, int semantic, int index, int a, int b);  // 0x0071ddc0
extern VertexBuffer* CreateVertexBuffer(VertexDescription* d, int n, int a, int b); // 0x00762b70
extern IndexBuffer* CreateIndexBuffer(const void* fmt, int a, int n, int b, int primType, int c); // 0x00762c60
extern RwMesh* CreateMesh(int n);                                                 // 0x00761840
extern void CopyElement(VertexStream* dst, const DataAccessor_s0072_b630* src, int n);       // 0x007296e0
extern void CopyElementIndexed(VertexStream* dst, const DataAccessor_s0072_b630* src, const DataAccessor_s0072_b630* idx, int n); // 0x00729760
template <typename T>
inline void PushOutput(vector_s0072_b630<T>* v, T x)
{
    v->push_back(x);
}
template <typename T>
inline void AddOutput(vector_s0072_b630<T>* v, T x)
{
    if (v)
        v->push_back(x);
}
inline VertexBuffer* LockVertexBuffer(VertexBuffer* vb, VertexBufferLock& lock)
{
    uint8_t stride = vb->mpDesc->stride;
    void* p = vb->Lock(2, stride * vb->mBaseVertex, stride * vb->mNumVertices);
    if (!p)
        return 0;
    lock.mpData = (char*)p;
    lock.mpBuffer = vb;
    return vb;
}
// ---- items of slice s0072b630 end

// forward declarations: helpers defined later in VA order (rewrite.py forward_protos)
void __declspec(noinline) FUN_0072b630(void* pMesh, void* pTextures, void* pMeshes, void* pMaterials, void* pTexturesOut, void* pVertexBuffers, void* pVertexDescs, void* pIndexBuffers, void* pSemanticIndex);   // defined at 0x0072b630, called earlier in the TU

// ---- items of slice s0072c270 begin (TODO(rewrite): local stubs, replace by canonical classes)
void operator delete[](void* p);  // 0x00f47380
namespace EA {
namespace COM {
class IRefCount_s0072_c270 {
public:
    virtual int AddRef() = 0;
    virtual int Release() = 0;
};
}
}
namespace EA {
template <typename T>
class AutoRefCount_s0072_c270 {
public:
    T* mpObject;
    AutoRefCount_s0072_c270() : mpObject(0) {}
    ~AutoRefCount_s0072_c270() { if (mpObject) mpObject->Release(); }
    AutoRefCount_s0072_c270& operator=(const AutoRefCount_s0072_c270& x)
    {
        T* const pObject = x.mpObject;
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
};
}
namespace rw {
namespace graphics {
class EmbeddedState_s0072_c270 {
public:
    uint32_t pad0[2];
    uint8_t m_softStateDirty;  // +0x8
    const int* D3D9GetShaderData(int type);  // 0x011edcf0
};
}
}
namespace rw {
namespace math {
namespace vpu {
class Vector3_s0072_c270 { public:
    __m128 v;
};
}
}
}
namespace rw {
namespace collision {
class KDTree_s0072_c270;
}
}
namespace rw {
namespace collision {
class Aggregate_s0072_c270;
}
}
namespace rw {
namespace collision {
struct AggregateVTable {
    int m_type;
    void* m_GetSize;
    unsigned int m_alignment;
    unsigned int m_isProcedural;
    void (Aggregate_s0072_c270::*m_Update)();  // +0x10
    void* m_LineIntersectionQuery;
    void* m_BBoxOverlapQuery;
};
}
}
namespace rw {
namespace collision {
class Aggregate_s0072_c270 {
public:
    uint32_t m_AABB[8];
    AggregateVTable* m_vTable;  // +0x20
    unsigned int m_numTagBits;
    unsigned int m_numVolumes;
    void Update() { (this->*(m_vTable->m_Update))(); }
};
}
}
namespace rw {
namespace collision {
class TriangleKDTreeProcedural_s0072_c270 : public Aggregate_s0072_c270 {
public:
    struct Triangle {
        unsigned int indices[3];
        unsigned int id;
    };
    unsigned int m_numVerts;        // +0x30
    Triangle* m_tris;               // +0x34
    rw::math::vpu::Vector3_s0072_c270* m_verts;  // +0x38
    KDTree_s0072_c270* m_map;                  // +0x3c
    unsigned int* m_flags;          // +0x40
};
}
}
namespace SP {
struct cSPVector3 {
    float x, y, z;
    cSPVector3() {}
    cSPVector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
};
}
namespace SP {
template <typename T> inline const T& Min(const T& a, const T& b) { return (b < a) ? b : a; }
}
namespace SP {
template <typename T> inline const T& Max(const T& a, const T& b) { return (a < b) ? b : a; }
}
namespace SP {
inline cSPVector3 Min(const cSPVector3& a, const cSPVector3& b)
{
    return cSPVector3(Min(a.x, b.x), Min(a.y, b.y), Min(a.z, b.z));
}
}
namespace SP {
inline cSPVector3 Max(const cSPVector3& a, const cSPVector3& b)
{
    return cSPVector3(Max(a.x, b.x), Max(a.y, b.y), Max(a.z, b.z));
}
}
namespace SP {
struct cAABBox {
    cSPVector3 mMin;
    cSPVector3 mMax;
    cAABBox() {}
    cAABBox(const cSPVector3& mn, const cSPVector3& mx) : mMin(mn), mMax(mx) {}
    __forceinline void Add(const cAABBox& b)
    {
        if (mMin.x > mMax.x) {
            *this = b;
        } else {
            if (b.mMin.x < mMin.x) mMin.x = b.mMin.x;
            if (b.mMax.x > mMax.x) mMax.x = b.mMax.x;
            if (b.mMin.y < mMin.y) mMin.y = b.mMin.y;
            if (b.mMax.y > mMax.y) mMax.y = b.mMax.y;
            if (b.mMin.z < mMin.z) mMin.z = b.mMin.z;
            if (b.mMax.z > mMax.z) mMax.z = b.mMax.z;
        }
    }
};
}
namespace SP {
inline void FreeArray(void* p)
{
    if (p && ((int*)p)[-1] != 0)
        operator delete[](p);
}
}
namespace SP {
struct cAppAllocTag {};
}
namespace SP {
struct cAABBoxVector {
    cAABBox* mpBegin;
    cAABBox* mpEnd;
    cAABBox* mpCapacity;
    uint32_t mAllocator[2];
    cAABBoxVector(int n, const cAppAllocTag& tag);  // 0x006a4770 (filled with an empty box)
    ~cAABBoxVector() { FreeArray(mpBegin); }
    cAABBox& operator[](int i) { return mpBegin[i]; }
};
}
namespace SP {
struct cIntVector {
    int* mpBegin;
    int* mpEnd;
    int* mpCapacity;
    uint32_t mAllocator;
    cIntVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~cIntVector() { FreeArray(mpBegin); }
    int size() const { return (int)(mpEnd - mpBegin); }
};
}
namespace SP {
template <typename T, int N>
struct fixed_vector_s0072_c270 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocName;
    T* mpPoolBegin;
    uint32_t mAllocPad;
    T mBuffer[N];

    void DoInsertValues(T* position, unsigned int n, const T& value);  // 0x00766950
    void resize(unsigned int n, const T& value);                       // 0x00736090
    void erase(T* first, T* last)
    {
        T* const position = (T*)memcpy(first, last, (size_t)((char*)mpEnd - (char*)last)) + (mpEnd - last);
        mpEnd = position;
    }
    void resize_inline(unsigned int n, const T& value)
    {
        if (n > (unsigned int)(mpEnd - mpBegin))
            DoInsertValues(mpEnd, n - (unsigned int)(mpEnd - mpBegin), value);
        else
            erase(mpBegin + n, mpEnd);
    }
    fixed_vector_s0072_c270()
    {
        mpPoolBegin = mBuffer;
        mpBegin = mpEnd = mBuffer;
        mpCapacity = mBuffer + N;
    }
    ~fixed_vector_s0072_c270()
    {
        if (mpBegin && mpBegin != mpPoolBegin)
            operator delete[](mpBegin);
    }
    T& operator[](int i) { return mpBegin[i]; }
};
}
namespace SP {
struct cEltArrayRef_s0072_c270 {
    int mNumElts;              // +0x0
    unsigned char* mData;      // +0x4
    unsigned short mEltSize;   // +0x8
    unsigned short mEltStride; // +0xa
    EA::AutoRefCount_s0072_c270<EA::COM::IRefCount_s0072_c270> mDataRC;  // +0xc
    cEltArrayRef_s0072_c270() : mNumElts(0), mData(0), mEltSize(sizeof(uint32_t)), mEltStride(sizeof(uint32_t)) {}
};
}
namespace SP {
extern const uint32_t kIndexMasks_s0072_c270[];  // 0x0140d15c, by element size: 0xff, 0xffff, 0xffffff, 0xffffffff
}
namespace SP {
struct cIndexArrayRef_s0072_c270 : public cEltArrayRef_s0072_c270 {
    uint32_t Get(int i) const { return *(const uint32_t*)(mData + mEltStride * i) & kIndexMasks_s0072_c270[mEltSize]; }
};
}
namespace SP {
inline const cSPVector3& GetVertex(const cEltArrayRef_s0072_c270& a, uint32_t i)
{
    return *(const cSPVector3*)(a.mData + a.mEltStride * i);
}
}
namespace SP {
struct cMDElementArray_s0072_c270 {
    int mSemantic;
    int mNumber;
    int mType;
    int mClass;
    cEltArrayRef_s0072_c270 mArray;  // +0x10
};
}
namespace SP {
struct cMDFormatEntry_s0072_c270 {
    short mElts;
    short mIndices;
};
}
namespace SP {
struct cMDSection_s0072_c270 {
    cIndexArrayRef_s0072_c270 mVertIndices;                    // +0x00
    int mNumVertices;                               // +0x10
    fixed_vector_s0072_c270<cMDFormatEntry_s0072_c270, 6> mFormat;        // +0x14
    fixed_vector_s0072_c270<cIndexArrayRef_s0072_c270, 3> mEltIndices;    // +0x44
};
}
namespace SP {
enum tMDPrimType_s0072_c270 { kMDTriangleList_s0072_c270 = 4, kMDPolygon_s0072_c270 = 9, kMaxMDPrimTypes_s0072_c270 = 10 };
}
namespace SP {
struct cMDPrimitive_s0072_c270 {
    int mPrimType;
    int mSection;
    int mStart;
    int mEnd;
    int mSubset;
};
}
namespace SP {
extern const signed char kPrimCountBias[];     // 0x0140cf84
}
namespace SP {
extern const signed char kPrimCountDivisor[];  // 0x0140cf90
}
namespace SP {
inline int GetPrimitiveCount(const cMDPrimitive_s0072_c270& prim)
{
    int type = prim.mPrimType;
    if (type <= 0 || type >= kMaxMDPrimTypes_s0072_c270)
        return 0;
    if (type == kMDPolygon_s0072_c270)
        return 1;
    return (kPrimCountBias[type] + (prim.mEnd - prim.mStart)) / kPrimCountDivisor[type];
}
}
namespace SP {
template <typename T>
struct sp_vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[2];
    int size() const { return (int)(mpEnd - mpBegin); }
    T& operator[](int i) { return mpBegin[i]; }
    void erase(T* first, T* last)
    {
        T* pDest = first;
        for (T* pSrc = last; pSrc != mpEnd; ++pSrc, ++pDest)
            *pDest = *pSrc;
        mpEnd -= (last - first);
    }
    void clear() { erase(mpBegin, mpEnd); }
};
}
namespace SP {
struct cMeshData_s0072_c270 {
    uint32_t mRefCount[2];
    sp_vector<cMDElementArray_s0072_c270> mEltArrays;  // +0x08
    sp_vector<cMDSection_s0072_c270> mSections;        // +0x1c
    sp_vector<cMDPrimitive_s0072_c270> mPrimitives;    // +0x30
};
}
namespace SP {
int FindElementArray(cMeshData_s0072_c270* pMesh, int semantic, int number, int type, int eltClass);  // 0x0071ddc0
}
namespace SP {
int FindFormatEntry(cMeshData_s0072_c270* pMesh, int section, int eltArray);                          // 0x0071e040
}
namespace SP {
void FindPrimitives(cMeshData_s0072_c270* pMesh, cIntVector& prims, int section, int primType, int subset);  // 0x0071ee10
}
namespace SP {
struct cTriToRegionMap_s0072_c270 {
    struct cTriToRegionMapEntry {
        int mRegionId;
        int mBegin;
        int mEnd;
    };
    sp_vector<cTriToRegionMapEntry> mRegions;
    void AddRegion(int begin, int end, int regionId);  // 0x0072b560
};
}
namespace SP {
struct Material_s0072_c270 {
    uint32_t pad0;
    rw::graphics::EmbeddedState_s0072_c270* mpState;  // +0x4
};
}
namespace SP {
class cMaterialManager_s0072_c270 {
public:
#define PV(n) virtual void pv##n();
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    virtual Material_s0072_c270* GetMaterialInstance(uint32_t materialID);  // +0x28 0x00712d60
};
}
namespace SP {
cMaterialManager_s0072_c270* MaterialManager_s0072_c270();  // 0x0067dd70
}
namespace SP {
struct cKDBuildNode {
    uint32_t mSplit[2];
    cAABBox mBBox;          // +0x08
    uint32_t mFirst;        // +0x20
    uint32_t mCount;        // +0x24
    uint32_t mAxis;         // +0x28
    cKDBuildNode* mpLeft;   // +0x2c
    cKDBuildNode* mpRight;  // +0x30

    static void* sFreeList;  // 0x0162b1f0
    static void operator delete(void* p)
    {
        *(void**)p = sFreeList;
        sFreeList = p;
    }

    cKDBuildNode(const cAABBox& bbox, uint32_t count)
    {
        mSplit[0] = 0;
        mSplit[1] = 0;
        mBBox = bbox;
        mFirst = 0;
        mCount = count;
        mAxis = 0;
        mpLeft = 0;
        mpRight = 0;
    }
    ~cKDBuildNode()  // 0x00729870
    {
        delete mpLeft;
        delete mpRight;
    }
    uint32_t Build(cAABBoxVector* pBoxes, uint32_t* pOrder, int maxLeafSize, int maxDepth);  // 0x0072a8c0
};
}
namespace SP {
void WriteKDTree(cKDBuildNode* pRoot, rw::collision::KDTree_s0072_c270* pTree);  // 0x00729990
}
namespace SP {
struct __declspec(align(16)) cAABBox4 {
    rw::math::vpu::Vector3_s0072_c270 mMin;
    rw::math::vpu::Vector3_s0072_c270 mMax;
    cAABBox4()
    {
        uint32_t* p = (uint32_t*)this;
        p[0] = 0; p[1] = 0; p[2] = 0; p[3] = 0;
        p[4] = 0; p[5] = 0; p[6] = 0; p[7] = 0;
    }
};
}
namespace SP {
inline __m128 MakeVector3(float x, float y, float z)
{
    return _mm_set_ps(x, z, y, x);
}
}
namespace SP {
rw::collision::TriangleKDTreeProcedural_s0072_c270* CreateTriangleKDTreeProcedural(
    int numVerts, uint32_t numTris, uint32_t numBranchNodes, const cAABBox4* pBBox, void* pArena);  // 0x00761500
}
// ---- items of slice s0072c270 end

// @ 0x00729430
int FUN_00729430(int a)
{
    switch (a) {
    case 2:
    case 0x12: return 2;
    case 3:
    case 5:  return 5;
    case 4:  return 6;
    case 6:
    case 7:
    case 8:
    case 9:
    case 0xa:
    case 0xb:
    case 0xc:
    case 0xd: return 8;
    case 0xe: return 9;
    case 0xf: return 10;
    case 0x13: return 3;
    case 0x14: return 4;
    case 0:  return 1;
    case 1:  return 1;
    case 0x10: return 1;
    case 0x11: return 1;
    case 0x15: return 1;
    default:  return 1;
    }
}

// @ 0x007294d0
int FUN_007294d0(int a)
{
    switch (a) {
    case 0:  return 1;
    case 1:  return 2;
    case 2:  return 3;
    case 3:  return 4;
    case 4:  return 5;
    case 5:  return 7;
    case 8:  return 0xa;
    case 6:  return 8;
    case 7:  return 9;
    case 9:  return 0xb;
    case 10: return 0xc;
    default: return 0;
    }
}

// @ 0x00729560
int FUN_00729560(int a)
{
    switch (a) {
    case 1:  return 0;
    case 2:  return 1;
    case 3:  return 2;
    case 4:  return 3;
    case 5:  return 4;
    default: return -1;
    case 7:  return 5;
    case 10: return 8;
    case 8:  return 6;
    case 9:  return 7;
    case 0xb: return 9;
    case 0xc: return 10;
    }
}

// @ 0x007295f0
int FUN_007295f0(int a, int b)
{
    switch (a) {
    case 1:
        if (b == 0) return 0;
        break;
    case 2:
        if (b == 0) return 2;
        break;
    case 8:
        if (b < 8) return b + 6;
        break;
    case 3:
        if (b == 0) return 0x13;
        break;
    case 5:
    case 7:
        if (b == 0) return 3;
        if (b == 1) return 5;
        break;
    case 6:
        if (b == 0) return 4;
        break;
    case 9:
        if (b == 0) return 0xe;
        break;
    case 10:
        if (b == 0) return 0xf;
        break;
    case 0xb:
        return 0x16;
    case 0xc:
        if (b == 0) return 0x11;
        break;
    case 0xd:
        if (b == 0) return 0x12;
    }
    return -1;
}

// @ 0x007296e0
int FUN_007296e0(int* dst, int* src, int rows)
{
    int      srcBase   = src[1];
    int*     d         = (int*)dst[0];
    unsigned dstStride = (unsigned)dst[1] & 0xfffffffc;
    unsigned wordStride = *(unsigned short*)((char*)src + 10) >> 2;
    unsigned count     = *(unsigned short*)((char*)src + 8) >> 2;
    int      last      = (int)wordStride;
    if (rows > 0)
        last = (int)(wordStride * 4);
    for (; rows > 0; --rows) {
        int*      s = (int*)srcBase;
        int*      p = d;
        if (count) {
            for (unsigned i = 0; i < count; ++i)
                p[i] = s[i];
            last = (int)(size_t)(p + count);
        }
        srcBase += (int)(wordStride * 4);
        d = (int*)((char*)d + dstStride);
    }
    return last;
}

// @ 0x00729760
void FUN_00729760(int* dst, int* src, int* sel, int rows)
{
    if (sel[1] == 0) {
        FUN_007296e0(dst, src, rows);
        return;
    }
    int      srcBase   = src[1];
    int*     d         = (int*)dst[0];
    unsigned dstStride = (unsigned)dst[1];
    unsigned srcStride = *(unsigned short*)((char*)src + 10);
    unsigned count     = *(unsigned short*)((char*)src + 8) >> 2;
    unsigned mask      = DAT_0140d15c[*(unsigned short*)((char*)sel + 8)];
    for (int row = 0; row < rows; ++row) {
        unsigned idx = *(unsigned int*)((char*)sel[1] + *(unsigned short*)((char*)sel + 10) * row);
        int* s = (int*)(srcBase + (int)((mask & idx) * (srcStride >> 2) * 4));
        for (unsigned i = 0; i < count; ++i)
            d[i] = s[i];
        d = (int*)((char*)d + (dstStride & 0xfffffffc));
    }
}

// @ 0x00729820
C29820* C29820::Init(int a, float* b, int c, int d)
{
    f0 = a;
    f1 = 0;
    f2 = b[0];
    f3 = b[1];
    f4 = b[2];
    f5 = b[3];
    f6 = b[4];
    f7 = b[5];
    f8 = c;
    f9 = d;
    f10 = 0;
    f11 = 0;
    f12 = 0;
    return this;
}

// @ 0x00729870
void C29a70::Free()
{
    if (mp2c) {
        mp2c->Free();
        C29a70* n = mp2c;
        *(void**)n = g_162b1f0;
        g_162b1f0 = n;
    }
    if (mp30) {
        mp30->Free();
        C29a70* n = mp30;
        *(void**)n = g_162b1f0;
        g_162b1f0 = n;
    }
}

// @ 0x007298b0
double FUN_007298b0(float* a, int b)
{
    float* p = (float*)b;
    float ux = p[7] - p[4], uy = p[8] - p[5], uz = p[9] - p[6];
    float vx = p[13] - p[10], vy = p[14] - p[11], vz = p[15] - p[12];
    float wx = a[3] - a[0], wy = a[4] - a[1], wz = a[5] - a[2];
    unsigned int t0 = *(unsigned int*)(p + 2);
    unsigned int t1 = *(unsigned int*)(p + 3);
    return ((vz * vy + vz * vx + vx * vy) * 2.0f * (float)t1 +
            (uz * uy + uz * ux + ux * uy) * 2.0f * (float)t0) /
           (2.0f * (wz * wy + wz * wx + wx * wy) * (float)(t0 + t1));
}

// @ 0x00729990
void __cdecl FUN_00729990(int root, OutBuf* buf)
{
    if (buf->mCount == 0)
        return;

    // One {parent, flag, descendant} frame; the walk keeps a single stack
    // pointer and moves all three fields together (retail increments the three
    // lockstep pointers once per descendant pushed).
    enum { kSlots = 32 };
    Win29990  win[kSlots];
    win[0].mParent = 0;                                        // sentinel frame
    win[0].mFlag   = 0;
    win[0].mpDesc  = (ChartNode*)root;

    Win29990* sp      = &win[1];
    unsigned  pending = 1;
    int       offset  = 0;
    int       i       = 0;

    do {
        --sp;                                                  // pop one frame
        int        node = sp->mParent;
        int        flag = sp->mFlag;
        ChartNode* desc = sp->mpDesc;
        --pending;

        if (i != 0)
            ((int*)buf->mpRec)[3 + (flag + node * 4) * 2] = i;

        OutRec* out = (OutRec*)((char*)buf->mpRec + offset);
        out->mNode  = node;
        int idx = desc->mIndex;
        out->mIndex = idx;
        out->mValA  = desc->mpA->mSlotHi[idx];
        out->mValB  = desc->mpB->mSlotLo[idx];

        ChartNode* eB = desc->mpB;
        if (eB->mpA == 0) {                                    // B is a leaf
            out->mMarkA = eB->mA24;
            out->mMarkB = eB->mA20;
        } else {                                               // descend into B
            sp->mpDesc  = eB;
            sp->mParent = i;
            sp->mFlag   = 1;
            ++pending;
            ++sp;
            out->mMarkA = -1;
            out->mMarkB = -1;
        }

        ChartNode* eA = desc->mpA;
        if (eA->mpA == 0) {                                    // A is a leaf
            out->mLoA = eA->mA24;
            out->mLoB = eA->mA20;
        } else {                                               // descend into A
            sp->mpDesc  = eA;
            sp->mParent = i;
            sp->mFlag   = 0;
            ++pending;
            ++sp;
            out->mLoA = -1;
            out->mLoB = -1;
        }

        offset += 0x20;
        ++i;
    } while (pending != 0);
}

// @ 0x00729ad0
int C29ad0::Find(int x)
{
    int* p = (int*)mpBegin;
    int  n = (int)(mpEnd - mpBegin) / 0xc;
    int  i = 0;
    if (0 < n) {
        do {
            if (p[1] <= x && x < p[2])
                return p[0];
            i++;
            p += 3;
        } while (i < n);
    }
    return -1;
}

// @ 0x00729b20
void* FUN_00729b20(VBi* p1, void* p2, void** p3)
{
    void* rb = p1->m_disposableBuffer;
    if (rb != 0) {
        if (p2 != 0) {
            *p3 = p2;
            CallSlot0(p2);
        }
        return rb;
    }

    VDesc* desc = p1->m_desc;
    void* locked = (void*)p1->Lock(1, desc->mStride * p1->m_base,
                                      desc->mStride * p1->m_numVertices);
    if (locked == 0)
        return rb;

    unsigned size = desc->mStride * p1->m_numVertices;
    void*    seg  = FUN_00720010((int)size);
    if (seg == 0) {
        p1->Unlock();
        return 0;
    }
    void* out = (char*)seg + 0xc;
    MemCopy(out, locked, size);
    *p3 = seg;
    CallSlot0(seg);
    p1->Unlock();
    return out;
}

// @ 0x00729bd0
void* FUN_00729bd0(IBuf* p1, void* p2, void** p3)
{
    void* rb = p1->mpData;
    if (rb != 0) {
        if (p2 != 0) {
            *p3 = p2;
            CallSlot0(p2);
        }
        return rb;
    }

    LockHandle lh;
    if (p1->Lock(1, &lh)) {
        int   size = p1->mCount * 2;
        void* seg  = FUN_00720010(size);
        if (seg != 0) {
            rb = (char*)seg + 0xc;
            MemCopy(rb, lh.mpPtr, (unsigned)size);
            *p3 = seg;
            CallSlot0(seg);
        }
        p1->Unlock(&lh.mpPtr);
    }
    return rb;
}

// @ 0x00729c60
void FUN_00729c60(MeshModel* model, Box6* box, float* radius)
{
    int idx = FUN_0071ddc0(model, 1, 0, 3, 0xe);
    if (idx < 0)
        return;

    StreamRecord* rec    = (StreamRecord*)((char*)model->mpStreams + (idx << 5));
    MeshStream*   entry  = &rec->entry;
    int           count  = entry->nCount;
    uint16_t      stride = entry->mStride;
    RefObj*       obj    = entry->mpOwner;
    const float*  v      = entry->mpVerts;

    if (obj != 0)
        obj->AddRef();

    float len2 = 0.0f;
    if (count > 0) {
        const float* p = v + 1;
        do {
            if (box != 0)
                ExpandPoint(*box, p - 1);
            float d = (p[-1] * p[-1] + p[1] * p[1]) + p[0] * p[0];
            if (len2 < d)
                len2 = d;
            p = (const float*)((const char*)p + stride);
            --count;
        } while (count != 0);
    }

    if (radius != 0) {
        double s = sqrt(len2);
        len2 = (float)s;
        const float* q = (s > *radius) ? &len2 : radius;
        *radius = *q;
    }

    if (obj != 0)
        obj->Release();
}

// @ 0x00729de0
__declspec(noinline) void FUN_00729de0(SplitNode* node, const Box* box, Box* const* items, unsigned* idx, int n)
{
    Box inv;
    inv.mx[0] = box->mx[0]; inv.mx[1] = box->mx[1]; inv.mx[2] = box->mx[2];
    inv.mn[0] = box->mn[0]; inv.mn[1] = box->mn[1]; inv.mn[2] = box->mn[2];
    node->right.mn[0] = inv.mx[0]; node->right.mn[1] = inv.mx[1]; node->right.mn[2] = inv.mx[2];
    node->right.mx[0] = inv.mn[0]; node->right.mx[1] = inv.mn[1]; node->right.mx[2] = inv.mn[2];
    node->left = node->right;

    // Retail reads `c[node->axis]` from the stack slot array before it has stored the
    // current element's box copy, so an out-of-range axis sees the *previous* iteration's
    // values (or the initial `<box>` copy on the first pass).  The /O2 schedule used to
    // store the copy first, which changed the partition for axis > 2.  Model those slots
    // explicitly: c[3..6] are the previous element's mn[0..2]/mx[0]; c[7..8] are the
    // current element's mx[1]/mx[2] (retail stores those two before the compare).
    float staleMn0 = box->mx[0];
    float staleMn1 = box->mx[1];
    float staleMn2 = box->mx[2];
    float staleMx0 = box->mn[0];

    int i = 0;
    int j = n - 1;
    if (j >= 0) {
        do {
            unsigned k = idx[i];
            const Box& src = (*items)[k];
            float c0 = (src.mx[0] + src.mn[0]) * 0.5f;
            float c1 = (src.mx[1] + src.mn[1]) * 0.5f;
            float c2 = (src.mx[2] + src.mn[2]) * 0.5f;

            int a = node->axis;
            float cv;
            if (a == 0)       cv = c0;
            else if (a == 1)  cv = c1;
            else if (a == 2)  cv = c2;
            else if (a == 3)  cv = staleMn0;
            else if (a == 4)  cv = staleMn1;
            else if (a == 5)  cv = staleMn2;
            else if (a == 6)  cv = staleMx0;
            else if (a == 7)  cv = src.mx[1];
            else if (a == 8)  cv = src.mx[2];
            else {
                // Retail computes `[esp + axis*4 + 0x10]` with 32-bit wrapping; with its
                // frame at E-0x34 at that point the effective address is E-0x24+axis*4
                // (E = entry ESP).  Reproduce the same wrapped read so huge / negative
                // axes observe the same pool or stack bytes instead of an arbitrary c0.
                unsigned int E = (unsigned int)(uintptr_t)_AddressOfReturnAddress();
                unsigned int addr = E - 0x24u + ((unsigned int)a << 2);
                cv = *(const float*)(uintptr_t)addr;
            }

            staleMn0 = src.mn[0]; staleMn1 = src.mn[1];
            staleMn2 = src.mn[2]; staleMx0 = src.mx[0];

            if (cv > node->pos) {
                idx[i] = idx[j];
                idx[j] = k;
                --j;
                ExpandBox(node->right, src);
            } else {
                ++i;
                ExpandBox(node->left, src);
            }
        } while (i <= j);
    }
    node->nLeft = (unsigned)i;
    node->nRight = (unsigned)(n - i);
}

// @ 0x0072a080
__declspec(noinline) SplitNode* __fastcall FUN_0072a080(SplitNode* self)
{
    const float kMax =  3.402823466e+38F;
    const float kMin = -3.402823466e+38F;
    self->left.mn[0] = kMax; self->left.mn[1] = kMax; self->left.mn[2] = kMax;
    self->left.mx[0] = kMin; self->left.mx[1] = kMin; self->left.mx[2] = kMin;
    self->right.mn[0] = kMax; self->right.mn[1] = kMax; self->right.mn[2] = kMax;
    self->right.mx[0] = kMin; self->right.mx[1] = kMin; self->right.mx[2] = kMin;
    return self;
}

// @ 0x0072a130
SpanIter* SpanOwner::MakeIter(SpanIter* out)
{
    int base = (int)mpBegin;
    out->count = ((int)mpEnd - base) / 0x30;
    *(short*)((char*)out + 0xa) = 0x30;
    out->base = base;
    *(short*)(out + 2) = 0x30;
    out->owner = (int*)this;
    (*(void(**)(void))vptr)();
    return out;
}

// @ 0x0072a180
void __fastcall FUN_0072a180(int* self)
{
    int* p = (int*)self[0];
    if (p != 0 && p != (int*)self[4])
        operator_delete(p);
}

// @ 0x0072a1a0
SpanAlloc* SpanAlloc::Init(int n, int* other)
{
    stride = other[1];
    if (n != 0) {
        int* p = (int*)FUN_00f473a0(n * 4, "Graphics", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1);
        mpBegin = p;
        mpEnd   = p;
        mpCap   = p + n;
        return this;
    }
    mpBegin = 0;
    mpEnd   = 0;
    mpCap   = mpBegin + n;
    return this;
}

// @ 0x0072a200
bool FUN_0072a200(SplitNode* out, const Box* box, Box* const* items, unsigned* idx, unsigned n)
{
    SplitNode best;
    FUN_0072a080(&best);

    Box b;
    {
        const Box& e0 = (*items)[idx[0]];
        b.mn[0] = e0.mn[0]; b.mn[1] = e0.mn[1]; b.mn[2] = e0.mn[2];
        b.mx[0] = e0.mx[0]; b.mx[1] = e0.mx[1]; b.mx[2] = e0.mx[2];
    }
    for (unsigned i = 1; i < n; ++i) {
        const Box& e = (*items)[idx[i]];
        if (!(b.mn[0] > b.mx[0])) {
            if (e.mn[0] < b.mn[0]) b.mn[0] = e.mn[0];
            if (b.mx[0] < e.mx[0]) b.mx[0] = e.mx[0];
            if (e.mn[1] < b.mn[1]) b.mn[1] = e.mn[1];
            if (b.mx[1] < e.mx[1]) b.mx[1] = e.mx[1];
            if (e.mn[2] < b.mn[2]) b.mn[2] = e.mn[2];
            if (b.mx[2] < e.mx[2]) b.mx[2] = e.mx[2];
        } else {
            b = e;
        }
    }

    float parentArea;
    {
        float dy = box->mx[1] - box->mn[1];
        float dz = box->mx[2] - box->mn[2];
        float dx = box->mx[0] - box->mn[0];
        parentArea = ((dz * dx) + (dy * dx) + (dz * dy)) * 2.0f;
    }
    float bestCost = parentArea;
    unsigned a = 0;
    do {
        Box c = *box;
        c.mx[a] = b.mx[a];
        float cost = SurfaceArea(c);
        if (cost < bestCost) {
            best.axis = (int)a;
            best.pos = b.mx[a];
            best.nLeft = n;
            best.nRight = 0;
            best.left = b;
            {
                Box inv;
                inv.mn[0] = box->mx[0]; inv.mn[1] = box->mx[1]; inv.mn[2] = box->mx[2];
                inv.mx[0] = box->mn[0]; inv.mx[1] = box->mn[1]; inv.mx[2] = box->mn[2];
                best.right = inv;
            }
            bestCost = cost;
        }
        c = *box;
        c.mn[a] = b.mn[a];
        cost = SurfaceArea(c);
        if (cost < bestCost) {
            best.axis = (int)a;
            best.pos = b.mn[a];
            best.nLeft = 0;
            best.nRight = n;
            {
                Box inv;
                inv.mn[0] = box->mx[0]; inv.mn[1] = box->mx[1]; inv.mn[2] = box->mx[2];
                inv.mx[0] = box->mn[0]; inv.mx[1] = box->mn[1]; inv.mx[2] = box->mn[2];
                best.left = inv;
            }
            best.right = b;
            bestCost = cost;
        }
        ++a;
    } while (a < 3);

    if (parentArea * 0.6f > bestCost) {
        *out = best;
        return true;
    }

    b.mn[0] = (b.mx[0] + b.mn[0]) * 0.5f;
    b.mn[1] = (b.mx[1] + b.mn[1]) * 0.5f;
    b.mn[2] = (b.mx[2] + b.mn[2]) * 0.5f;
    float bestSplit = 1.0f;
    for (unsigned a = 0; a < 3; ++a) {
        best.axis = (int)a;
        best.pos = b.mn[a];
        FUN_00729de0(&best, box, items, idx, (int)n);
        float cost = FUN_007298b0(box, &best);
        if (best.nLeft != 0 && best.nRight != 0 && cost < bestSplit) {
            *out = best;
            bestSplit = cost;
        }
    }
    if (!(bestSplit < 0.95f))
        return false;
    FUN_00729de0(out, box, items, idx, (int)n);
    return true;
}

// @ 0x0072a8c0
int BspNode::Build(Box* const* items, unsigned* idx, unsigned n, int depth)
{
    SplitNode split;
    FUN_0072a080(&split);

    if (depth != 0 && mCount > n) {
        if (FUN_0072a200(&split, &mBox, items, idx + mFirst, mCount)) {
            int axis = split.axis;
            mAxis = axis;

            Box left = mBox;
            left.mx[axis] = split.left.mx[axis];

            Box right = mBox;
            right.mn[axis] = split.right.mn[axis];

            BspNode* node = (BspNode*)gNodeAllocator.Malloc();
            node = (node != 0) ? node->Init(this, (float*)&left, (int)mFirst, (int)split.nLeft) : 0;
            mpLeft = node;

            node = (BspNode*)gNodeAllocator.Malloc();
            node = (node != 0) ? node->Init(this, (float*)&right, (int)(mFirst + split.nLeft), (int)split.nRight) : 0;
            mpRight = node;

            mpLeft->mLevel = mLevel + 1;
            int c1 = mpLeft->Build(items, idx, n, depth - 1);
            mpRight->mLevel = mpLeft->mLevel + c1 + 1;
            int c2 = mpRight->Build(items, idx, n, depth - 1);
            return c2 + c1 + 2;
        }
    }
    return 0;
}

// @ 0x0072aa80
EAArray* EAArray::Init(int n, int reserved)
{
    (void)reserved;
    Scratch48 local_30;
    void* buf;
    if (n != 0)
        buf = FUN_00f473a0(n * 0x30, "Graphics", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1);
    else
        buf = 0;
    mpBegin = buf;
    mpEnd   = buf;
    mpCap   = (char*)buf + n * 0x30;
    FUN_0042f0a0(buf, n, &local_30, n);
    mpEnd = (char*)mpBegin + n * 0x30;
    return this;
}

// @ 0x0072aaf0
void Vec4::DoInsertValue(int* pos, const int* value)
{
    if (mpEnd != mpCap) {
        // Room for one more: shift [pos, mpEnd) up by one dword, then store *value.
        int* insertAt = pos;
        if (pos >= value && value < mpEnd)
            insertAt = pos + 1;
        if (mpEnd)
            *mpEnd = mpEnd[-1];
        int* src = mpEnd;
        int* dst = src;
        while (dst - 1 != insertAt) {
            --dst;
            *dst = src[-2];
            --src;
        }
        *insertAt = *value;
        mpEnd = mpEnd + 1;
        return;
    }

    int count = (int)(mpEnd - mpBegin);
    int newCap;
    if (count == 0)
        newCap = 1;
    else
        newCap = count * 2;

    int* buf;
    if (newCap == 0)
        buf = 0;
    else
        buf = (int*)FUN_00f473a0((unsigned)(newCap * 4), "Graphics", 0, 0, kEastlAllocatorFile, 0xd1);

    // Copy [mpBegin, pos), then *value, then [pos, mpEnd).
    int* out = buf;
    for (int* p = mpBegin; p != pos; ++p) {
        if (out) *out = *p;
        ++out;
    }
    if (out) *out = *value;
    int* srcEnd = mpEnd;
    int* writePos = out + 1;
    if (pos != srcEnd) {
        int* rd = pos;
        int* wr = writePos;
        do {
            if (wr) *wr = *rd;
            ++rd;
            ++wr;
        } while (rd != srcEnd);
    }
    if (mpBegin && mpBegin != mpPool)
        operator_delete(mpBegin);
    mpBegin = buf;
    mpEnd = writePos;
    mpCap = buf + newCap;
}

// @ 0x0072ac10
SpanHolder* SpanHolder::Init(const int* sp)
{
    const IntSpan* span = (const IntSpan*)sp;
    FUN_0072a1a0(this, (int)(span->mpEnd - span->mpBegin), span->mpPool);
    int nbytes = (int)((char*)span->mpEnd - (char*)span->mpBegin);
    memcpy(mpBegin, span->mpBegin, (size_t)nbytes);
    mpEnd = (int*)((char*)mpBegin + (nbytes & ~3));
    return this;
}

// @ 0x0072ac60
RefObj_s0072_aaf0* RefObj_s0072_aaf0::Ctor(int arg)
{
    mpVtbl0 = (void**)&vtbl_Init0;
    mpVtbl1 = (void**)&vtbl_Init1;
    _InterlockedExchange(&mRef, 0);
    mpVtbl0 = (void**)&vtbl_Final0;
    mpVtbl1 = (void**)&vtbl_Final1;
    FUN_0072aa80(&mPayload[0], arg, &arg);
    mField20 = 0;
    return this;
}

// @ 0x0072ace0
namespace SP {
void StreamMeshToRw(SourceMesh* mesh, DrawStats* stats, ShaderDataItem* extraPush, ShaderMap* shaderMap, int materialId, EmbeddedState* state)
{
    DataAccessor materials;
    EmbeddedState* defaultState = 0;
    if (state) {
        defaultState = state;
    } else if (materialId) {
        defaultState = MaterialManager()->GetMaterial(materialId)->mpState;
    } else {
        bool lookup = true;
        int idx = FindElement(mesh, 0x15, 0, 6, 0xe);
        if (idx >= 0) {
            materials = mesh->mpElements[idx].mData;
            if (materials.mpData)
                lookup = false;
        }
        if (lookup)
            defaultState = MaterialManager()->GetMaterial((uint32_t)0x9f84a565)->mpState;
    }

    int numSubMeshes = mesh->mSubMeshes.size();
    for (int subIdx = 0; subIdx < numSubMeshes; ++subIdx) {
        SubMesh* sub = &mesh->mSubMeshes.mpBegin[subIdx];
        fixed_vector<int, 16> rwDecls;
        fixed_vector<int, 16> d3dTypes;
        fixed_vector<ElementRef, 16> refs;

        int numRefs = sub->mElements.size();
        for (int j = 0; j < numRefs; ++j) {
            MeshElement* e = &mesh->mpElements[mesh->mSubMeshes.mpBegin[subIdx].mElements.mpBegin[j].mElement];
            int d3d = ToD3DDeclType(e->mDataType);
            int rw = ToRwDecl(e->mSemantic, e->mSemanticIndex);
            if (rw != -1 && d3d != -1 && e->mStream < 4) {
                rwDecls.push_back(rw);
                d3dTypes.push_back(d3d);
                refs.push_back(sub->mElements.mpBegin[j]);
            }
        }
        if (rwDecls.mpBegin == rwDecls.mpEnd)
            continue;

        int numElems = rwDecls.size();
        VertexDescription* vd = CreateVertexDescriptor(numElems);
        vd->lockFlags |= 2;
        for (int k = 0; k < rwDecls.size(); ++k) {
            vd->elements[k].rwDecl = rwDecls.mpBegin[k];
            vd->elements[k].type = (uint8_t)d3dTypes.mpBegin[k];
        }
        vd->Finalize();
        BuildState* bs = CreateVertexBuffer(0x80000002, 0);
        bs->SetField1230(4, 0);
        bs->D3D9SetVertexDescriptor(vd, 0);
        void* compiled = CreateCompiledState(bs);
        DestroyBuildState(bs);

        int numPrims = mesh->mPrims.size();
        for (int pi = 0; pi < numPrims; ++pi) {
            PrimitiveGroup* prim = &mesh->mPrims.mpBegin[pi];
            if (prim->mSubMesh != subIdx)
                continue;
            EmbeddedState* mat = defaultState;
            if (materials.mpData)
                mat = MaterialManager()->GetMaterial(*(uint32_t*)(materials.mpData + materials.mStride * prim->mMaterial))->mpState;
            int primType = kRwPrimTypes[prim->mPrimType];
            int scratch;
            CompiledStateBegin(compiled, &scratch);
            PushShaderDataNull();
            SetShaderData(mat);
            mat->Dispatch();
            if (shaderMap && mat && (mat->mSoftStateDirty & 8)) {
                int* data = mat->D3D9GetShaderData(0x20f);
                if (data) {
                    ShaderMapEntry* first = shaderMap->mpBegin;
                    ShaderMapEntry* last = shaderMap->mpEnd;
                    int n = (int)(last - first);
                    while (n > 0) {
                        int half = n >> 1;
                        if (first[half].key < *data) {
                            first += half + 1;
                            n -= half + 1;
                        } else
                            n = half;
                    }
                    if (first == last || *data < first->key)
                        first = last;
                    else if (first == first + 1)
                        first = last;
                    if (first != last && first->value)
                        first->value->Push();
                }
            }
            if (extraPush)
                extraPush->Push();
            gActivePrimType = primType;
            if (!gActiveVertexDesc || !VertexDescriptorAreEqual(gActiveVertexDesc, vd))
                gSoftStateUpdated |= 0x100000;
            gActiveVertexDesc = vd;
            ((VDescRefresh*)vd)->Refresh();
            SetVertexDescriptor(vd);
            D3D9Sync();

            int maxChunk = 0x8000 / vd->stride;
            int remaining = prim->mEnd - prim->mStart;
            int cur = prim->mStart;
            while (remaining > 0) {
                int chunk = ((remaining < maxChunk ? remaining : maxChunk) / 3) * 3;
                char* dst = (char*)LockIndexSpan(chunk);
                if (dst) {
                    int end = cur + chunk;
                    if (sub->mIndexTables.mpBegin == sub->mIndexTables.mpEnd) {
                        for (int k = cur; k < end; ++k) {
                            uint32_t idx = sub->mIndices.Index(k);
                            int nref = refs.size();
                            for (int j = 0; j < nref; ++j) {
                                MeshElement* e = &mesh->mpElements[refs.mpBegin[j].mElement];
                                int size = e->mData.mFormat;
                                memcpy(dst, e->mData.mpData + e->mData.mStride * idx, size);
                                dst += size;
                            }
                        }
                    } else {
                        for (int k = cur; k < end; ++k) {
                            uint32_t idx = sub->mIndices.Index(k);
                            int nref = refs.size();
                            for (int j = 0; j < nref; ++j) {
                                MeshElement* e = &mesh->mpElements[refs.mpBegin[j].mElement];
                                uint32_t tidx = sub->mIndexTables.mpBegin[refs.mpBegin[j].mIndexTable].Index(idx);
                                int size = e->mData.mFormat;
                                memcpy(dst, e->mData.mpData + e->mData.mStride * tidx, size);
                                dst += size;
                            }
                        }
                    }
                    UnlockIndexSpan();
                }
                stats->mVerts += chunk;
                stats->mBatches++;
                remaining -= chunk;
                cur += chunk;
            }
            PopShaderData();
            IndexSpanEnd();
        }
        DestroyVertexDescriptor(vd);
        ReleaseObject(compiled);
    }
}
}  // namespace SP

// @ 0x0072b560
void cTriToRegionMap_s0072_aaf0::AddRegion(int param_2, int param_3, int param_4)
{
    if (param_4 != -1) {
    if (param_2 != param_3) {
        TriRegionEntry* const pBegin = mRegions.mpBegin;
        TriRegionEntry* const pEnd   = mRegions.mpEnd;
        const int n = (int)(pEnd - pBegin);
        for (int i = 0; i < n; ++i) {
            TriRegionEntry& e = pBegin[i];
            if (e.mRegionId == param_4) {
                if (e.mBegin == param_3) {
                    e.mBegin = param_2;
                    return;
                }
                if (e.mEnd == param_2) {
                    e.mEnd = param_3;
                    return;
                }
            }
        }

        TriRegionEntry tmp;
        tmp.mBegin = param_2;
        tmp.mEnd = param_3;
        tmp.mRegionId = param_4;
        if (pEnd < mRegions.mpCap) {
            mRegions.mpEnd = pEnd + 1;
            if (pEnd != 0) {
                pEnd->mRegionId = param_4;
                pEnd->mBegin = param_2;
                pEnd->mEnd = param_3;
                return;
            }
        } else {
            mRegions.insert(pEnd, tmp);
        }
    }
    }
}

// @ 0x0072b630
void __declspec(noinline) FUN_0072b630(void* pMesh, void* pTextures, void* pMeshes, void* pMaterials, void* pTexturesOut, void* pVertexBuffers, void* pVertexDescs, void* pIndexBuffers, void* pSemanticIndex)
{
    SourceMesh_s0072_b630* mesh = (SourceMesh_s0072_b630*)pMesh;
    vector_s0072_b630<TexturePtr>* textures = (vector_s0072_b630<TexturePtr>*)pTextures;
    vector_s0072_b630<RwMesh*>* outMeshes = (vector_s0072_b630<RwMesh*>*)pMeshes;
    vector_s0072_b630<Material*>* outMaterials = (vector_s0072_b630<Material*>*)pMaterials;
    vector_s0072_b630<TexturePtr>* outTextures = (vector_s0072_b630<TexturePtr>*)pTexturesOut;
    vector_s0072_b630<VertexBuffer*>* outVertexBuffers = (vector_s0072_b630<VertexBuffer*>*)pVertexBuffers;
    vector_s0072_b630<VertexDescription*>* outVertexDescs = (vector_s0072_b630<VertexDescription*>*)pVertexDescs;
    vector_s0072_b630<IndexBuffer*>* outIndexBuffers = (vector_s0072_b630<IndexBuffer*>*)pIndexBuffers;
    int semanticIndex = (int)pSemanticIndex;

    DataAccessor_s0072_b630 materialIds;
    if (outMaterials) {
        int idx = FindElement(mesh, 0x15, 0, 6, 0xe);
        if (idx >= 0)
            materialIds = mesh->mpElements[idx].mData;
    }

    DataAccessor_s0072_b630 textureIds;
    if (outTextures && textures) {
        int idx = FindElement(mesh, 0x14, 0, 6, 0xe);
        if (idx >= 0)
            textureIds = mesh->mpElements[idx].mData;
    }

    int nSubMeshes = (int)mesh->mSubMeshes.size();
    for (int i = 0; i < nSubMeshes; ++i) {
        const SubMesh_s0072_b630& sm = mesh->mSubMeshes[i];
        fixed_vector_s0072_b630<uint32_t, 16> rwDecls;
        fixed_vector_s0072_b630<int, 16> elementIndices;
        fixed_vector_s0072_b630<uint32_t, 16> declTypes;

        int nElements = (int)mesh->mSubMeshes[i].mElements.size();
        for (int j = 0; j < nElements; ++j) {
            const MeshElement_s0072_b630& e = mesh->mpElements[mesh->mSubMeshes[i].mElements[j].mElement];
            uint32_t declType = ToD3DDeclType(e.mDataType);
            uint32_t rwDecl;
            if (semanticIndex >= 0) {
                if (e.mSemanticIndex != semanticIndex)
                    continue;
                rwDecl = ToRwDecl(e.mSemantic, 0);
            } else {
                rwDecl = ToRwDecl(e.mSemantic, e.mSemanticIndex);
            }
            if (rwDecl != (uint32_t)-1 && declType != (uint32_t)-1 && e.mStream < 4) {
                rwDecls.push_back(rwDecl);
                declTypes.push_back(declType);
                elementIndices.push_back(j);
            }
        }
        if (rwDecls.empty())
            continue;

        VertexDescription* desc = CreateVertexDescriptor(rwDecls.size());
        AddOutput(outVertexDescs, desc);
        desc->lockFlags |= 2;
        int nDecls = rwDecls.size();
        for (int k = 0; k < nDecls; ++k) {
            desc->elements[k].rwDecl = rwDecls[k];
            desc->elements[k].type = (uint8_t)declTypes[k];
        }
        desc->Finalize();

        VertexBuffer* vb = CreateVertexBuffer(desc, sm.mVertexCount, 0, 0);
        AddOutput(outVertexBuffers, vb);
        VertexBufferLock lock;
        VertexBuffer* lockedVB = LockVertexBuffer(vb, lock);
        VertexStream stream;
        stream.mpData = lock.mpData;
        stream.mStride = lock.mpBuffer->mpDesc->stride;
        int nCopy = elementIndices.size();
        for (int k = 0; k < nCopy; ++k) {
            int j = elementIndices[k];
            const DataAccessor_s0072_b630* src =
                &mesh->mpElements[mesh->mSubMeshes[i].mElements[j].mElement].mData;
            lock.GetElementStream(&stream, k);
            const SubMesh_s0072_b630& cur = mesh->mSubMeshes[i];
            if (cur.mIndexTables.mpBegin != cur.mIndexTables.mpEnd)
                CopyElementIndexed(&stream, src,
                                   &cur.mIndexTables.mpBegin[cur.mElements.mpBegin[j].mIndexTable],
                                   sm.mVertexCount);
            else
                CopyElement(&stream, src, sm.mVertexCount);
        }
        lockedVB->Unlock();

        int nPrims = (int)mesh->mPrims.size();
        for (int p = 0; p < nPrims; ++p) {
            const PrimitiveGroup& prim = mesh->mPrims[p];
            if (prim.mSubMesh != i)
                continue;
            bool b32 = sm.mVertexCount > 0x10000;
            IndexBuffer* ib = CreateIndexBuffer(b32 ? kIndexFormat32 : kIndexFormat16, 1,
                                                prim.mEnd - prim.mStart, 8,
                                                kRwPrimTypes[prim.mPrimType], 0);
            IndexLock il;
            if (ib->Lock(2, &il)) {
                if (b32) {
                    uint32_t* out = (uint32_t*)il.mpData;
                    if (sm.mIndices.mpData == 0) {
                        for (int n = prim.mStart; n < prim.mEnd; ++n)
                            *out++ = n;
                    } else {
                        for (int n = prim.mStart; n < prim.mEnd; ++n)
                            *out++ = sm.mIndices.Index<uint32_t>(n);
                    }
                } else {
                    uint16_t* out = (uint16_t*)il.mpData;
                    if (sm.mIndices.mpData == 0) {
                        for (int n = prim.mStart; n < prim.mEnd; ++n)
                            *out++ = (uint16_t)n;
                    } else {
                        for (int n = prim.mStart; n < prim.mEnd; ++n)
                            *out++ = sm.mIndices.Index<uint16_t>(n);
                    }
                }
                ib->Unlock(&il);
            }

            RwMesh* rwMesh = CreateMesh(1);
            rwMesh->SetVertexBuffer(0, lockedVB);
            rwMesh->SetIndexBuffer(ib);
            rwMesh->SetIndexCount(ib->mNumIndices);
            PushOutput(outMeshes, rwMesh);
            AddOutput(outIndexBuffers, ib);

            if (outMaterials) {
                IMaterialManager* mm = MaterialManager();
                outMaterials->push_back(materialIds.mpData
                                            ? mm->GetMaterial(*materialIds.At<uint32_t>(prim.mMaterial))
                                            : mm->GetMaterial(0x9f84a565));
            }

            if (outTextures) {
                if (textures && textureIds.mpData) {
                    uint32_t t = *textureIds.At<uint32_t>(prim.mMaterial);
                    if (t < textures->size())
                        outTextures->push_back((*textures)[t]);
                    else
                        outTextures->push_back(TexturePtr());
                } else {
                    outTextures->push_back(TexturePtr());
                }
            }
        }
    }
}

// @ 0x0072c040
void FUN_0072c040(int* vec, void* a2, void* a3, void* a4, void* a5, void* a6, void* a7, void* a8, void* a9)
{
    int n = (vec[1] - vec[0]) >> 2;
    for (int i = 0; i < n; ++i)
        FUN_0072b630((void*)((int*)vec[0])[i], a2, a3, a4, a5, a6, a7, a8, a9);
}

// @ 0x0072c270
namespace SP {
rw::collision::TriangleKDTreeProcedural_s0072_c270* MakeKDTree(sp_vector<cMeshData_s0072_c270*>& meshes, cAABBox* pBBoxOut, cTriToRegionMap_s0072_c270* pRegionMap, int maxLeafSize, void* pArena)
{
    int numMeshes = meshes.size();
    uint32_t numTris = 0;
    int numVerts = 0;

    for (int m = 0; m < numMeshes; m++) {
        cIntVector prims;
        cMeshData_s0072_c270* pMesh = meshes[m];
        int posIdx = FindElementArray(pMesh, 1, -1, 3, 0xe);
        if (posIdx >= 0) {
            numVerts += pMesh->mEltArrays[posIdx].mArray.mNumElts;
            FindPrimitives(pMesh, prims, -1, kMDTriangleList_s0072_c270, -1);
            int numPrims = prims.size();
            for (int i = 0; i < numPrims; i++)
                numTris += GetPrimitiveCount(pMesh->mPrimitives[prims.mpBegin[i]]);
        }
    }

    cAABBoxVector boxes(numTris, cAppAllocTag());
    int boxIndex = 0;
    for (int m = 0; m < numMeshes; m++) {
        cMeshData_s0072_c270* pMesh = meshes[m];
        int posIdx = FindElementArray(pMesh, 1, -1, 3, 0xe);
        if (posIdx < 0)
            continue;
        const cEltArrayRef_s0072_c270& positions = pMesh->mEltArrays[posIdx].mArray;
        int numSections = pMesh->mSections.size();
        for (int s = 0; s < numSections; s++) {
            cMDSection_s0072_c270& section = pMesh->mSections[s];
            int fmt = FindFormatEntry(pMesh, s, posIdx);
            if (fmt < 0)
                continue;
            cIntVector prims;
            FindPrimitives(pMesh, prims, s, kMDTriangleList_s0072_c270, -1);
            int numPrims = prims.size();
            for (int i = 0; i < numPrims; i++) {
                const cMDPrimitive_s0072_c270& prim = pMesh->mPrimitives[prims.mpBegin[i]];
                int count = GetPrimitiveCount(prim);
                int vtx = prim.mStart;
                if (section.mEltIndices.mpBegin == section.mEltIndices.mpEnd) {
                    for (int t = 0; t < count; t++) {
                        uint32_t i0 = section.mVertIndices.Get(vtx);
                        uint32_t i1 = section.mVertIndices.Get(vtx + 1);
                        uint32_t i2 = section.mVertIndices.Get(vtx + 2);
                        vtx += 3;
                        const cSPVector3& v0 = GetVertex(positions, i0);
                        const cSPVector3& v1 = GetVertex(positions, i1);
                        const cSPVector3& v2 = GetVertex(positions, i2);
                        cAABBox box(Min(v0, Min(v1, v2)), Max(v0, Max(v1, v2)));
                        boxes[boxIndex++] = box;
                    }
                } else {
                    const cIndexArrayRef_s0072_c270& eltIndices = section.mEltIndices[section.mFormat[fmt].mIndices];
                    for (int t = 0; t < count; t++) {
                        uint32_t i0 = eltIndices.Get(section.mVertIndices.Get(vtx));
                        uint32_t i1 = eltIndices.Get(section.mVertIndices.Get(vtx + 1));
                        uint32_t i2 = eltIndices.Get(section.mVertIndices.Get(vtx + 2));
                        vtx += 3;
                        const cSPVector3& v0 = GetVertex(positions, i0);
                        const cSPVector3& v1 = GetVertex(positions, i1);
                        const cSPVector3& v2 = GetVertex(positions, i2);
                        cAABBox box(Min(v0, Min(v1, v2)), Max(v0, Max(v1, v2)));
                        boxes[boxIndex++] = box;
                    }
                }
            }
        }
    }

    if (numTris == 0)
        return 0;

    fixed_vector_s0072_c270<uint32_t, 512> order;
    order.resize_inline(numTris, 0);
    fixed_vector_s0072_c270<int, 512> remap;
    remap.resize(numTris, -1);

    for (int i = 0; i < (int)numTris; i++)
        order[i] = i;

    cAABBox bbox = boxes[0];
    for (int i = 1; i < (int)numTris; i++)
        bbox.Add(boxes[i]);
    if (pBBoxOut)
        *pBBoxOut = bbox;

    cKDBuildNode root(bbox, numTris);
    uint32_t numNodes = root.Build(&boxes, order.mpBegin, maxLeafSize, 0x20) + 1;
    for (int i = 0; i < (int)numTris; i++) {
        if (order[i] < numTris)
            remap[order[i]] = i;
    }

    cAABBox4 box4;
    box4.mMin.v = MakeVector3(bbox.mMin.x, bbox.mMin.y, bbox.mMin.z);
    box4.mMax.v = MakeVector3(bbox.mMax.x, bbox.mMax.y, bbox.mMax.z);
    rw::collision::TriangleKDTreeProcedural_s0072_c270* pTree =
        CreateTriangleKDTreeProcedural(numVerts, numTris, (numNodes - 1) / 2, &box4, pArena);

    rw::math::vpu::Vector3_s0072_c270* pVerts = pTree->m_verts;
    int vertIndex = 0;
    for (int m = 0; m < numMeshes; m++) {
        cMeshData_s0072_c270* pMesh = meshes[m];
        int posIdx = FindElementArray(pMesh, 1, -1, 3, 0xe);
        if (posIdx >= 0) {
            const cEltArrayRef_s0072_c270& positions = pMesh->mEltArrays[posIdx].mArray;
            int n = positions.mNumElts;
            for (int i = 0; i < n; i++) {
                const cSPVector3& v = GetVertex(positions, i);
                pVerts[vertIndex++].v = MakeVector3(v.x, v.y, v.z);
            }
        }
    }

    WriteKDTree(&root, pTree->m_map);
    pTree->Update();
    rw::collision::TriangleKDTreeProcedural_s0072_c270::Triangle* pTris = pTree->m_tris;

    if (pRegionMap)
        pRegionMap->mRegions.clear();

    cMaterialManager_s0072_c270* pMatMgr = MaterialManager_s0072_c270();
    uint32_t triIndex = 0;
    for (int m = 0; m < numMeshes; m++) {
        cMeshData_s0072_c270* pMesh = meshes[m];
        cEltArrayRef_s0072_c270 materialIds;
        int matIdx = FindElementArray(pMesh, 0x15, 0, 6, 0xe);
        if (matIdx >= 0)
            materialIds = pMesh->mEltArrays[matIdx].mArray;
        int posIdx = FindElementArray(pMesh, 1, -1, 3, 0xe);
        if (posIdx < 0)
            continue;
        int numSections = pMesh->mSections.size();
        for (int s = 0; s < numSections; s++) {
            cMDSection_s0072_c270& section = pMesh->mSections[s];
            int fmt = FindFormatEntry(pMesh, s, posIdx);
            if (fmt < 0)
                continue;
            cIntVector prims;
            FindPrimitives(pMesh, prims, s, kMDTriangleList_s0072_c270, -1);
            int numPrims = prims.size();
            for (int i = 0; i < numPrims; i++) {
                const cMDPrimitive_s0072_c270& prim = pMesh->mPrimitives[prims.mpBegin[i]];
                int count = GetPrimitiveCount(prim);
                int vtx = prim.mStart;

                int regionId = -1;
                if (materialIds.mData) {
                    uint32_t materialId = *(const uint32_t*)(materialIds.mData + materialIds.mEltStride * prim.mSubset);
                    rw::graphics::EmbeddedState_s0072_c270* pState = pMatMgr->GetMaterialInstance(materialId)->mpState;
                    if (pState && (pState->m_softStateDirty & 8)) {
                        const int* pData = pState->D3D9GetShaderData(0x20f);
                        if (pData)
                            regionId = *pData;
                    }
                }
                if (pRegionMap)
                    pRegionMap->AddRegion(triIndex, triIndex + count, regionId);

                if (section.mEltIndices.mpBegin == section.mEltIndices.mpEnd) {
                    for (int t = 0; t < count; t++) {
                        if ((uint32_t)remap[triIndex] < numTris) {
                            rw::collision::TriangleKDTreeProcedural_s0072_c270::Triangle& tri = pTris[remap[triIndex]];
                            tri.indices[0] = section.mVertIndices.Get(vtx++);
                            tri.indices[1] = section.mVertIndices.Get(vtx++);
                            tri.indices[2] = section.mVertIndices.Get(vtx++);
                            tri.id = triIndex;
                        }
                        triIndex++;
                    }
                } else {
                    const cIndexArrayRef_s0072_c270& eltIndices = section.mEltIndices[section.mFormat[fmt].mIndices];
                    for (int t = 0; t < count; t++) {
                        if ((uint32_t)remap[triIndex] < numTris) {
                            rw::collision::TriangleKDTreeProcedural_s0072_c270::Triangle& tri = pTris[remap[triIndex]];
                            tri.indices[0] = eltIndices.Get(section.mVertIndices.Get(vtx++));
                            tri.indices[1] = eltIndices.Get(section.mVertIndices.Get(vtx++));
                            tri.indices[2] = eltIndices.Get(section.mVertIndices.Get(vtx++));
                            tri.id = triIndex;
                        }
                        triIndex++;
                    }
                }
            }
        }
    }

    return pTree;
}
}  // namespace SP
