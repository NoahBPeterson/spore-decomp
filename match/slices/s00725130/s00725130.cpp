// Slice s00725130 -- SP::cMeshSimplifier::CreateEdges (PDB candidate, caller-scored), 0x00725130.
//
// Welds the mesh's triangle soup before simplification. For every section that has a position index
// stream it:
//   * builds the section's corner list (from its vertex index buffer, or 0..n-1 when it has none),
//   * drops degenerate triangles (two corners on the same position) and records, for every old
//     corner, the new corner index (remap),
//   * for each collapsed edge of a dropped triangle, merges the two adjacency entries into one
//     ring of a global "edge map" (a circular linked list stored in an int element array),
//   * writes the compacted index buffer back, remaps the section's primitives' start/end, and
//     finally rewrites the adjacency stream so every ring points to a single representative.
// When the mesh has no adjacency/attribute stream at all it falls back to BuildConnectivity.
//
// Module flags: /O2 /MD /Gy /EHsc /TP (EH frame for the AutoRefCount/vector temporaries).
#include "types.h"
#include <string.h>
#include <new>

#define EASTL_ALLOCATOR_FILE \
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

void* operator new[](unsigned int n, const char* name, int flags, unsigned int debugFlags,
                     const char* file, int line);                    // 0x00f473a0
void operator delete[](void* p, const char* name, int flags, unsigned int debugFlags,
                       const char* file, int line);

namespace EA {
namespace Thread { void ThreadSleep(const int& relativeTime); }       // 0x00921df0

namespace COM {
struct IRefCount {
    virtual int AddRef() = 0;
    virtual int Release() = 0;
};
}

template <typename T>
class AutoRefCount {
public:
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    AutoRefCount& operator=(const AutoRefCount& x) { return operator=(x.mpObject); }
    AutoRefCount& operator=(T* p)
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

struct sp_vector_allocator {
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

template <typename T>
class vector {
public:
    typedef unsigned int size_type;
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator mAllocator;

    vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    __forceinline explicit vector(size_type n)
    {
        mpBegin = DoAllocate(n);
        mpCapacity = mpBegin + n;
        mpEnd = mpBegin;
        for (size_type i = n; i; --i)
            *mpEnd++ = T();
        mpEnd = mpCapacity;
    }
    ~vector()
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

// An element (or index) stream: mNumElts entries of mEltSize bytes, mEltStride apart.
struct cEltArrayRef {
    int mNumElts;
    unsigned char* mData;
    unsigned short mEltSize;
    unsigned short mEltStride;
    EA::AutoRefCount<EA::COM::IRefCount> mDataRC;

    uint32_t GetIndex(uint32_t i) const { return *(uint32_t*)(mData + mEltStride * i) & kEltSizeMask[mEltSize]; }
    int& Int(uint32_t i) { return *(int*)(mData + mEltStride * i); }
};

struct cIndexArrayRef : cEltArrayRef {
    cIndexArrayRef()
    {
        mNumElts = 0;
        mData = 0;
        mEltSize = 0;
        mEltStride = 0;
    }
};

void AllocateEltArray(cEltArrayRef* p);                                  // 0x00720070
void MakeEltArrayUnique(cEltArrayRef* p);                                // 0x007200f0
void CopyEltArray(const cEltArrayRef* src, cEltArrayRef* dst);          // 0x007201d0

struct cMDFormatEntry {
    short mElts;
    short mIndices;
};

struct cMDSection {                     // retail stride 0x8c
    cIndexArrayRef mVertIndices;        // +0x00
    int mNumVertices;                   // +0x10
    cMDFormatEntry* mFormat;            // +0x14 fixed_vector begin
    uint32_t pad18[0xb];
    cIndexArrayRef* mEltIndices;        // +0x44 fixed_vector begin
    uint32_t pad48[0x11];
};

struct cMDElementArray {                // 0x20
    int mSemantic;
    int mNumber;
    int mType;
    int mClass;
    cEltArrayRef mArray;                // +0x10
};

struct cMDPrimitive {                   // 0x14
    int mPrimType;
    int mSection;
    int mStart;                         // +0x08
    int mEnd;                           // +0x0c
    int mSubset;
};

template <typename T>
struct SPVector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[2];
};

struct cMeshData {
    uint32_t mRefCountVtbl[2];
    SPVector<cMDElementArray> mEltArrays;   // +0x08
    SPVector<cMDSection> mSections;         // +0x1c
    SPVector<cMDPrimitive> mPrimitives;     // +0x30
};

int FindElementArray(cMeshData* mesh, int semantic, int number, int type, int elementClass);  // 0x0071ddc0
int FindFormatEntry(cMeshData* mesh, int section, int eltArray);                           // 0x0071e040
void FindPrimitives(cMeshData* mesh, eastl::vector<int>* out, int section, int a, int b);  // 0x0071ee10
void BuildConnectivity(cMeshData* mesh);                                                   // 0x007249f0
void FinishEdges(cMeshData* mesh);                                                         // 0x0073a4b0
void Memset32(void* p, uint32_t value, int count);                                        // 0x0092cb00

// Links adjacency entries e0 and e1 into the same ring of the edge map (rings are circular lists,
// -1 = not linked).
__forceinline void MergeEdgeRings(cEltArrayRef& edgeMap, uint32_t e0, uint32_t e1)
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

// Drops degenerate triangles of the corner list (position indices of type T), building remap.
template <typename T>
__forceinline void CompactTriangles(const cEltArrayRef& posIdx, cEltArrayRef& adjIdx, cEltArrayRef& edgeMap,
                             eastl::vector<int>& corners, eastl::vector<int>& remap, int nTris,
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

// @ 0x00725130
void CreateEdges(cMeshData* mesh)
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

    cEltArrayRef edgeMap;
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

        cIndexArrayRef adjIdx;
        int adjFmt = FindFormatEntry(mesh, s, adjArray);
        if (adjFmt >= 0) {
            cMDSection& sec = mesh->mSections.mpBegin[s];
            adjIdx = sec.mEltIndices[sec.mFormat[adjFmt].mIndices];
        }
        cMDSection* section = &mesh->mSections.mpBegin[s];
        cEltArrayRef posIdx = section->mEltIndices[section->mFormat[posFmt].mIndices];
        section = &mesh->mSections.mpBegin[s];
        cEltArrayRef vertIdx = section->mVertIndices;

        eastl::vector<int> corners;
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

        eastl::vector<int> remap(n);
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
        cEltArrayRef newIndices;
        newIndices.mNumElts = corners.size();
        newIndices.mData = (unsigned char*)corners.data();
        newIndices.mEltSize = 4;
        newIndices.mEltStride = 4;
        CopyEltArray(&newIndices, &mesh->mSections.mpBegin[s].mVertIndices);
        remap.push_back(numOut);

        eastl::vector<int> prims;
        FindPrimitives(mesh, &prims, s, 0, -1);
        for (int i = 0; i < (int)prims.size(); i++) {
            cMDPrimitive& prim = mesh->mPrimitives.mpBegin[prims[i]];
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
            cMDSection& sec = mesh->mSections.mpBegin[s];
            sec.mEltIndices[sec.mFormat[adjFmt].mIndices] = adjIdx;
        }
        EA::Thread::ThreadSleep(0);
    }
    FinishEdges(mesh);
}

}
