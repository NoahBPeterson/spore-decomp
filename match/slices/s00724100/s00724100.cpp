// SP::cMeshClusterer: builds the per-triangle cluster records and the dual-edge heap from a mesh
// section (retail name in the PDB-guess is ConvertMeshToTriangleLists; the body is cMeshClusterer setup).
// Retail offset layout (derived from the disassembly):
//   +0x08 mesh, +0x44 section, +0x48 face clusters (0x28 each), +0x5c dual edges (0x18 each),
//   +0x70 heap of edge pointers, +0x88 cluster count.
#include <math.h>
#include "types.h"

extern "C" void __cdecl EASTL_allocator_deallocate(void* p);

struct IRefCount {
    virtual int AddRef();
    virtual int Release();
};

// 16-byte element-array view {count, data, type, stride, owner}.
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

struct MeshData {
    char pad00[8];
    MeshElt* mpElts;          // +0x08
    char pad0c[0x10];
    MeshSection* mpSections;  // +0x1c
};

struct cFaceCluster {         // 0x28
    float mSumAreaPoint[3];   // +0x00
    float mSumAreaNormal[3];  // +0x0c
    float mArea;              // +0x18
    int mFirstEdge;           // +0x1c
    int mParentCluster;       // +0x20
    void* mPreviousDE;        // +0x24
};

struct cDualEdge {            // 0x18
    float mCost;              // +0x00
    int mHeapIndex;           // +0x04
    int mClusters[2];         // +0x08
    int mNextEdges[2];        // +0x10
};

struct FaceVec {
    cFaceCluster* mpBegin;
    cFaceCluster* mpEnd;
    cFaceCluster* mpCap;
    int pad[2];
    void resize(uint32_t n);             // 0x00723840
};
struct DualVec {
    cDualEdge* mpBegin;
    cDualEdge* mpEnd;
    cDualEdge* mpCap;
    int pad[2];
    void resize(uint32_t n, const cDualEdge* v);  // 0x007238b0
};
struct HeapVec {
    cDualEdge** mpBegin;
    cDualEdge** mpEnd;
    cDualEdge** mpCap;
    int pad[2];
    void DoInsertValue(cDualEdge** pos, cDualEdge* const* v);  // 0x006ec4a0
};
struct cHeap {
    HeapVec mHeapEntries;
    void HeapifyUp(int i);               // 0x007206b0
};

extern uint32_t gTypeMask[];             // 0x0140d0ac

int __cdecl FindElement(MeshData* m, int section, int a, int b, int c);  // 0x0071e090
int __cdecl FindStream(MeshData* m, int a, int b, int c, int d);         // 0x0071ddc0

static inline uint32_t ReadIndex(const EltRef* r, int i) {
    return *(uint32_t*)(r->mpData + i * r->mStride) & gTypeMask[r->mType];
}

struct cMeshClusterer {
    char pad00[8];
    MeshData* mpMesh;        // +0x08
    char pad0c[0x38];
    int mSection;            // +0x44
    FaceVec mFaceClusters;   // +0x48
    DualVec mDualEdges;      // +0x5c
    cHeap mEdgeHeap;         // +0x70
    char pad84[4];
    int mNumClusters;        // +0x88
    void CalcError(cFaceCluster* a, cFaceCluster* b, float* out);  // 0x00720700
    void Setup();
};

// @ 0x00724100
void cMeshClusterer::Setup() {
    int ix = FindElement(mpMesh, mSection, 1, 0, 0);
    if (ix < 0)
        return;

    MeshData* mesh = mpMesh;
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
            cFaceCluster* f0 = &mFaceClusters.mpBegin[c0];
            edge->mNextEdges[0] = f0->mFirstEdge;
            f0->mFirstEdge = e;
            cFaceCluster* f1 = &mFaceClusters.mpBegin[c1];
            edge->mNextEdges[1] = f1->mFirstEdge;
            f1->mFirstEdge = e + numEdges;
            CalcError(f0, f1, (float*)edge);
            HeapVec& h = mEdgeHeap.mHeapEntries;
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
void __cdecl FUN_00724700(void* this_) { (void)this_; }

// @ 0x007247c0
void __cdecl FUN_007247c0() {}
