// Slice s00723140: model-chart build helpers (vertex remap of cModelResource-like meshes) and
// small EASTL vector helpers for Vertex3D (0x18), cSPTransform (0x38) and a 0x68-byte record.
#include "types.h"

extern "C" {
void* __cdecl memcpy(void*, const void*, size_t);
void* __cdecl memset(void*, int, size_t);
long __cdecl _InterlockedExchange(long volatile*, long);
}
#pragma intrinsic(_InterlockedExchange)

void* __cdecl operator_new(size_t, const char*, int, int, const char*, int);
void __cdecl operator_delete__(void* p);  // 0xf47380
extern const char kEastlAllocFile[];  // 0x13ebb38 ".../EASTL/allocator.h"

extern uint32_t gBitMask[];  // 0x140d0ac: per-format value masks, indexed by BufView::maskIdx

// ---- ref-counted object (AutoRefCount target): vtbl[0]=AddRef, vtbl[1]=Release ----
struct RefObj { virtual int AddRef(); virtual int Release(); };

// ---- typed memory view (element data + stride + mask selector) ----
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

// ======================================================================
// Small vector helper types
// ======================================================================
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
struct RandomAccessTag {};
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

struct Vec8 {  // eastl::vector<8-byte element>
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    void* mAllocator;
    int mPad;
    void Alloc(uint32_t n, const void* srcAlloc);  // 0x6a40a0
    Vec8& assign(const Vec8& o);                    // 0x473b00
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

// ======================================================================
// @ 0x00723680 / 0x00723720: ref-counted int-vector object (two vptrs, refcount at +8)
// ======================================================================
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

// @ 0x00723680
IntVecObj::IntVecObj(int n) {
    mVec.Alloc(n, &n);
    int* p = mVec.mpBegin;
    if ((uint32_t)n > 0) {
        for (int i = n; i != 0; --i) *p++ = 0;
    }
    mVec.mpEnd = mVec.mpBegin + n;
    mField20 = 0;
}

// @ 0x00723720
IntVecObj::IntVecObj(int n, const int* v) {
    mVec.Fill(n, *v);
    mField20 = 0;
}

// @ 0x007237a0  (vector<Vertex3D>::resize(n))
void Vec24::resize(uint32_t n) {
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

// @ 0x007238b0  (vector<Vertex3D>::resize(n, value))
void Vec24::resize(uint32_t n, const Vertex3D* val) {
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

// ======================================================================
// 0x68-byte chart record: copy ctor (0x723930) and operator= (0x723a70)
// ======================================================================
struct ChartRec {
    int   i0;          // +0
    float f4;          // +4
    float f8;          // +8
    int   iC;          // +0xc
    int   i10;         // +0x10
    Vec8  v14;         // +0x14 (alloc at +0x20)
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

// @ 0x00723930
ChartRec::ChartRec(const ChartRec& o) {
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
ChartRec& ChartRec::operator=(const ChartRec& o) {
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

// @ 0x00723af0  (eastl::vector<cSPTransform>::DoAssign(first, last, random_access_iterator_tag))
void Vec56::DoAssign(const Xform56* first, const Xform56* last, int tag) {
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

// ======================================================================
// Mesh data model used by the chart builder
// ======================================================================
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

// @ 0x00723140  (compact the vertex index space chunk by chunk)
void MeshBuild::Build() {
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

// ======================================================================
// Per-submesh element list ("pairs" vector of 8-byte items + Vertex3D vector)
// ======================================================================
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

// @ 0x00723cf0
void PairVec::Reset(uint32_t nVerts, uint32_t nPairs, int a, int b, uint8_t flag) {
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

// @ 0x00723d60  (per-submesh index-remap export: build a 32-bit lookup and store it into the mesh)
void __cdecl ExportSubMeshRemap(MeshData* mesh) {
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
