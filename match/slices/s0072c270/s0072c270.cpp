// Slice s0072c270 — SP::MakeKDTree (0x0072c270, 4902 bytes, 16-byte aligned frame).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /GS-  (no cookie in the original)
//
// Builds an rw::collision::TriangleKDTreeProcedural from a list of cMeshData:
//   1. counts the vertices (position element arrays) and triangle-list triangles of every mesh;
//   2. computes one AABB per triangle (both for directly indexed sections and for sections whose
//      position stream goes through a per-element index array);
//   3. sorts the triangles into a KD tree with the pool-allocated cKDBuildNode builder;
//   4. creates the procedural, copies the vertices (as Vector3 with w = x) and the triangles
//      (remapped to their KD-tree order), and fills the optional cTriToRegionMap with the
//      material's 0x20f shader-data region id per primitive.
// Retail layouts: eastl vectors are 0x14 bytes (8-byte allocator), cMDSection is 0x8c.

#include <string.h>
#include <xmmintrin.h>
#include "types.h"

void operator delete[](void* p);  // 0x00f47380

namespace EA { namespace COM {
class IRefCount {
public:
    virtual int AddRef() = 0;
    virtual int Release() = 0;
};
} }

namespace EA {
template <typename T>
class AutoRefCount {
public:
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    AutoRefCount& operator=(const AutoRefCount& x)
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

namespace rw { namespace graphics {
class EmbeddedState {
public:
    uint32_t pad0[2];
    uint8_t m_softStateDirty;  // +0x8
    const int* D3D9GetShaderData(int type);  // 0x011edcf0
};
} }

namespace rw { namespace math { namespace vpu {
struct Vector3 {
    __m128 v;
};
} } }

namespace rw { namespace collision {
class KDTree;
class Aggregate;
struct AggregateVTable {
    int m_type;
    void* m_GetSize;
    unsigned int m_alignment;
    unsigned int m_isProcedural;
    void (Aggregate::*m_Update)();  // +0x10
    void* m_LineIntersectionQuery;
    void* m_BBoxOverlapQuery;
};
class Aggregate {
public:
    uint32_t m_AABB[8];
    AggregateVTable* m_vTable;  // +0x20
    unsigned int m_numTagBits;
    unsigned int m_numVolumes;
    void Update() { (this->*(m_vTable->m_Update))(); }
};
class TriangleKDTreeProcedural : public Aggregate {
public:
    struct Triangle {
        unsigned int indices[3];
        unsigned int id;
    };
    unsigned int m_numVerts;        // +0x30
    Triangle* m_tris;               // +0x34
    rw::math::vpu::Vector3* m_verts;  // +0x38
    KDTree* m_map;                  // +0x3c
    unsigned int* m_flags;          // +0x40
};
} }

namespace SP {

struct cSPVector3 {
    float x, y, z;
    cSPVector3() {}
    cSPVector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
};

template <typename T> inline const T& Min(const T& a, const T& b) { return (b < a) ? b : a; }
template <typename T> inline const T& Max(const T& a, const T& b) { return (a < b) ? b : a; }

inline cSPVector3 Min(const cSPVector3& a, const cSPVector3& b)
{
    return cSPVector3(Min(a.x, b.x), Min(a.y, b.y), Min(a.z, b.z));
}
inline cSPVector3 Max(const cSPVector3& a, const cSPVector3& b)
{
    return cSPVector3(Max(a.x, b.x), Max(a.y, b.y), Max(a.z, b.z));
}

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

// Memory from the "App" array allocator carries its element count just before the data.
inline void FreeArray(void* p)
{
    if (p && ((int*)p)[-1] != 0)
        operator delete[](p);
}

struct cAppAllocTag {};

struct cAABBoxVector {
    cAABBox* mpBegin;
    cAABBox* mpEnd;
    cAABBox* mpCapacity;
    uint32_t mAllocator[2];
    cAABBoxVector(int n, const cAppAllocTag& tag);  // 0x006a4770 (filled with an empty box)
    ~cAABBoxVector() { FreeArray(mpBegin); }
    cAABBox& operator[](int i) { return mpBegin[i]; }
};

struct cIntVector {
    int* mpBegin;
    int* mpEnd;
    int* mpCapacity;
    uint32_t mAllocator;
    cIntVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~cIntVector() { FreeArray(mpBegin); }
    int size() const { return (int)(mpEnd - mpBegin); }
};

template <typename T, int N>
struct fixed_vector {
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
    fixed_vector()
    {
        mpPoolBegin = mBuffer;
        mpBegin = mpEnd = mBuffer;
        mpCapacity = mBuffer + N;
    }
    ~fixed_vector()
    {
        if (mpBegin && mpBegin != mpPoolBegin)
            operator delete[](mpBegin);
    }
    T& operator[](int i) { return mpBegin[i]; }
};

struct cEltArrayRef {
    int mNumElts;              // +0x0
    unsigned char* mData;      // +0x4
    unsigned short mEltSize;   // +0x8
    unsigned short mEltStride; // +0xa
    EA::AutoRefCount<EA::COM::IRefCount> mDataRC;  // +0xc
    cEltArrayRef() : mNumElts(0), mData(0), mEltSize(sizeof(uint32_t)), mEltStride(sizeof(uint32_t)) {}
};

extern const uint32_t kIndexMasks[];  // 0x0140d15c, by element size: 0xff, 0xffff, 0xffffff, 0xffffffff

struct cIndexArrayRef : public cEltArrayRef {
    uint32_t Get(int i) const { return *(const uint32_t*)(mData + mEltStride * i) & kIndexMasks[mEltSize]; }
};

inline const cSPVector3& GetVertex(const cEltArrayRef& a, uint32_t i)
{
    return *(const cSPVector3*)(a.mData + a.mEltStride * i);
}

struct cMDElementArray {
    int mSemantic;
    int mNumber;
    int mType;
    int mClass;
    cEltArrayRef mArray;  // +0x10
};

struct cMDFormatEntry {
    short mElts;
    short mIndices;
};

struct cMDSection {
    cIndexArrayRef mVertIndices;                    // +0x00
    int mNumVertices;                               // +0x10
    fixed_vector<cMDFormatEntry, 6> mFormat;        // +0x14
    fixed_vector<cIndexArrayRef, 3> mEltIndices;    // +0x44
};

enum tMDPrimType { kMDTriangleList = 4, kMDPolygon = 9, kMaxMDPrimTypes = 10 };

struct cMDPrimitive {
    int mPrimType;
    int mSection;
    int mStart;
    int mEnd;
    int mSubset;
};

extern const signed char kPrimCountBias[];     // 0x0140cf84
extern const signed char kPrimCountDivisor[];  // 0x0140cf90

inline int GetPrimitiveCount(const cMDPrimitive& prim)
{
    int type = prim.mPrimType;
    if (type <= 0 || type >= kMaxMDPrimTypes)
        return 0;
    if (type == kMDPolygon)
        return 1;
    return (kPrimCountBias[type] + (prim.mEnd - prim.mStart)) / kPrimCountDivisor[type];
}

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

struct cMeshData {
    uint32_t mRefCount[2];
    sp_vector<cMDElementArray> mEltArrays;  // +0x08
    sp_vector<cMDSection> mSections;        // +0x1c
    sp_vector<cMDPrimitive> mPrimitives;    // +0x30
};

int FindElementArray(cMeshData* pMesh, int semantic, int number, int type, int eltClass);  // 0x0071ddc0
int FindFormatEntry(cMeshData* pMesh, int section, int eltArray);                          // 0x0071e040
void FindPrimitives(cMeshData* pMesh, cIntVector& prims, int section, int primType, int subset);  // 0x0071ee10

struct cTriToRegionMap {
    struct cTriToRegionMapEntry {
        int mRegionId;
        int mBegin;
        int mEnd;
    };
    sp_vector<cTriToRegionMapEntry> mRegions;
    void AddRegion(int begin, int end, int regionId);  // 0x0072b560
};

struct Material {
    uint32_t pad0;
    rw::graphics::EmbeddedState* mpState;  // +0x4
};

class cMaterialManager {
public:
#define PV(n) virtual void pv##n();
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    virtual Material* GetMaterialInstance(uint32_t materialID);  // +0x28
};
cMaterialManager* MaterialManager();  // 0x0067dd70

// KD-tree build node (0x34 bytes); children come from a free-list pool.
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

void WriteKDTree(cKDBuildNode* pRoot, rw::collision::KDTree* pTree);  // 0x00729990

struct __declspec(align(16)) cAABBox4 {
    rw::math::vpu::Vector3 mMin;
    rw::math::vpu::Vector3 mMax;
    cAABBox4()
    {
        uint32_t* p = (uint32_t*)this;
        p[0] = 0; p[1] = 0; p[2] = 0; p[3] = 0;
        p[4] = 0; p[5] = 0; p[6] = 0; p[7] = 0;
    }
};

inline __m128 MakeVector3(float x, float y, float z)
{
    return _mm_set_ps(x, z, y, x);
}

rw::collision::TriangleKDTreeProcedural* CreateTriangleKDTreeProcedural(
    int numVerts, uint32_t numTris, uint32_t numBranchNodes, const cAABBox4* pBBox, void* pArena);  // 0x00761500

// @ 0x0072c270
rw::collision::TriangleKDTreeProcedural* MakeKDTree(sp_vector<cMeshData*>& meshes, cAABBox* pBBoxOut,
                                                    cTriToRegionMap* pRegionMap, int maxLeafSize, void* pArena)
{
    int numMeshes = meshes.size();
    uint32_t numTris = 0;
    int numVerts = 0;

    for (int m = 0; m < numMeshes; m++) {
        cIntVector prims;
        cMeshData* pMesh = meshes[m];
        int posIdx = FindElementArray(pMesh, 1, -1, 3, 0xe);
        if (posIdx >= 0) {
            numVerts += pMesh->mEltArrays[posIdx].mArray.mNumElts;
            FindPrimitives(pMesh, prims, -1, kMDTriangleList, -1);
            int numPrims = prims.size();
            for (int i = 0; i < numPrims; i++)
                numTris += GetPrimitiveCount(pMesh->mPrimitives[prims.mpBegin[i]]);
        }
    }

    cAABBoxVector boxes(numTris, cAppAllocTag());
    int boxIndex = 0;
    for (int m = 0; m < numMeshes; m++) {
        cMeshData* pMesh = meshes[m];
        int posIdx = FindElementArray(pMesh, 1, -1, 3, 0xe);
        if (posIdx < 0)
            continue;
        const cEltArrayRef& positions = pMesh->mEltArrays[posIdx].mArray;
        int numSections = pMesh->mSections.size();
        for (int s = 0; s < numSections; s++) {
            cMDSection& section = pMesh->mSections[s];
            int fmt = FindFormatEntry(pMesh, s, posIdx);
            if (fmt < 0)
                continue;
            cIntVector prims;
            FindPrimitives(pMesh, prims, s, kMDTriangleList, -1);
            int numPrims = prims.size();
            for (int i = 0; i < numPrims; i++) {
                const cMDPrimitive& prim = pMesh->mPrimitives[prims.mpBegin[i]];
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
                    const cIndexArrayRef& eltIndices = section.mEltIndices[section.mFormat[fmt].mIndices];
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

    fixed_vector<uint32_t, 512> order;
    order.resize_inline(numTris, 0);
    fixed_vector<int, 512> remap;
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
    rw::collision::TriangleKDTreeProcedural* pTree =
        CreateTriangleKDTreeProcedural(numVerts, numTris, (numNodes - 1) / 2, &box4, pArena);

    rw::math::vpu::Vector3* pVerts = pTree->m_verts;
    int vertIndex = 0;
    for (int m = 0; m < numMeshes; m++) {
        cMeshData* pMesh = meshes[m];
        int posIdx = FindElementArray(pMesh, 1, -1, 3, 0xe);
        if (posIdx >= 0) {
            const cEltArrayRef& positions = pMesh->mEltArrays[posIdx].mArray;
            int n = positions.mNumElts;
            for (int i = 0; i < n; i++) {
                const cSPVector3& v = GetVertex(positions, i);
                pVerts[vertIndex++].v = MakeVector3(v.x, v.y, v.z);
            }
        }
    }

    WriteKDTree(&root, pTree->m_map);
    pTree->Update();
    rw::collision::TriangleKDTreeProcedural::Triangle* pTris = pTree->m_tris;

    if (pRegionMap)
        pRegionMap->mRegions.clear();

    cMaterialManager* pMatMgr = MaterialManager();
    uint32_t triIndex = 0;
    for (int m = 0; m < numMeshes; m++) {
        cMeshData* pMesh = meshes[m];
        cEltArrayRef materialIds;
        int matIdx = FindElementArray(pMesh, 0x15, 0, 6, 0xe);
        if (matIdx >= 0)
            materialIds = pMesh->mEltArrays[matIdx].mArray;
        int posIdx = FindElementArray(pMesh, 1, -1, 3, 0xe);
        if (posIdx < 0)
            continue;
        int numSections = pMesh->mSections.size();
        for (int s = 0; s < numSections; s++) {
            cMDSection& section = pMesh->mSections[s];
            int fmt = FindFormatEntry(pMesh, s, posIdx);
            if (fmt < 0)
                continue;
            cIntVector prims;
            FindPrimitives(pMesh, prims, s, kMDTriangleList, -1);
            int numPrims = prims.size();
            for (int i = 0; i < numPrims; i++) {
                const cMDPrimitive& prim = pMesh->mPrimitives[prims.mpBegin[i]];
                int count = GetPrimitiveCount(prim);
                int vtx = prim.mStart;

                int regionId = -1;
                if (materialIds.mData) {
                    uint32_t materialId = *(const uint32_t*)(materialIds.mData + materialIds.mEltStride * prim.mSubset);
                    rw::graphics::EmbeddedState* pState = pMatMgr->GetMaterialInstance(materialId)->mpState;
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
                            rw::collision::TriangleKDTreeProcedural::Triangle& tri = pTris[remap[triIndex]];
                            tri.indices[0] = section.mVertIndices.Get(vtx++);
                            tri.indices[1] = section.mVertIndices.Get(vtx++);
                            tri.indices[2] = section.mVertIndices.Get(vtx++);
                            tri.id = triIndex;
                        }
                        triIndex++;
                    }
                } else {
                    const cIndexArrayRef& eltIndices = section.mEltIndices[section.mFormat[fmt].mIndices];
                    for (int t = 0; t < count; t++) {
                        if ((uint32_t)remap[triIndex] < numTris) {
                            rw::collision::TriangleKDTreeProcedural::Triangle& tri = pTris[remap[triIndex]];
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
