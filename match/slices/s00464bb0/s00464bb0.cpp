// Slice s00464bb0: (anonymous namespace)::cBlockGeometryExporter::Export
// (SPBake/SPEditorExportUtilities.cpp; dev-PDB name
//  ?Export@cBlockGeometryExporter@?A0x0560a4a0@@QAEXAAVcExportHelper@nSPSkinner@@PAVcSPEditorBlock@SP@@AAV?$RectT@M@EA@@I_N@Z).
// Unoptimized editor module: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
//
// Clears the exporter's six geometry vectors, asks the block's model for its meshes and, for each
// mesh, appends its position / normal / texcoord streams (texcoords fall back to the positions'
// x/y when the mesh has none) and its first section's 16-bit indices (rebased); then maps every
// texcoord into the given UV rect and hands the arrays to cExportHelper::ExportMeshAdd.
// If the model has no meshes the block's bounding box is exported instead.
//
// The loop-body local names were chosen to reproduce the original /Od stack-slot order (cl 15.00
// orders a scope's locals by a 16-bucket name hash, later declarations first within a bucket).
#include "types.h"

// Reserves N dwords of /Od frame, standing in for the frame of an inline callee cl declined.
template <int N> inline void ScratchSlots() { uint32_t s[N]; }

namespace EA {
template<class T> struct RectT {
    T left, top, right, bottom;
};
}

struct cSPVector3 {
    float x, y, z;
    cSPVector3() {}
    cSPVector3(const cSPVector3& v) { x = v.x; y = v.y; z = v.z; }
};
struct cSPVector2 {
    float x, y;
    cSPVector2() {}
    cSPVector2(const cSPVector2& v) { x = v.x; y = v.y; }
    float& operator[](int i) { return (&x)[i]; }
};
struct cSPVector4 { float x, y, z, w; };
namespace SP { struct tMDUByte4 { uint8_t v[4]; }; }

namespace eastl {
struct sp_vector_allocator { uint32_t mData[2]; };
struct allocator_tag { allocator_tag() {} };   // empty argument of the RefVector ctor
template<class T, class A> class vector {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    A mAllocator;
    T* erase(T* first, T* last);
    void resize(unsigned int n);
    void clear() { erase(mpBegin, mpEnd); }
    unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
    T& operator[](unsigned int i) { return *(mpBegin + i); }
};
template<class T1, class T2> struct pair {
    T1 first;
    T2 second;
    pair(const T1& a, const T2& b) : first(a), second(b) {}
};
}

// One vertex stream of a model mesh (0x10 bytes): element count, data, format, byte stride.
struct cMDStream {
    unsigned int mCount;           // +0x0
    void* mpData;                  // +0x4
    uint16_t mFormat;              // +0x8
    uint16_t mStride;              // +0xa
    uint32_t mPadC;
};
struct cMDElement {                // 0x20 bytes
    uint32_t mPad0[4];
    cMDStream mStream;             // +0x10
};
struct cMDSection {                // 0x8c bytes
    unsigned int mIndexCount;      // +0x0
    uint16_t* mpIndices;           // +0x4
    uint32_t mPad8[(0x8c - 8) / 4];
};
struct cMDSectionArray {
    cMDSection* mpBegin;
    cMDSection& operator[](unsigned int i) { return *(mpBegin + i); }
    cMDSection& at(unsigned int i) { cMDSection* p = mpBegin + i; return *p; }
};
struct cMeshData {
    uint32_t mPad0[2];
    cMDElement* mpElements;        // +0x8
    uint32_t mPadC[4];
    cMDSectionArray mSections;     // +0x1c
};

// Finds the elements with the given usages; fills elementIndices[]. (0x0071ded0)
bool FindVertexElements(cMeshData* mesh, int numUsages, int* elementIndices, const int* usages,
                        int a4, const int* componentCounts, int a6);

struct MeshRef { cMeshData* mpObject; };
struct MeshRefVector {
    MeshRef* mpBegin;
    MeshRef* mpEnd;
    MeshRef* mpCapacity;
    uint32_t mAllocator[2];
    MeshRefVector(const eastl::allocator_tag& a);     // 0x00540470
    ~MeshRefVector();                                       // 0x0041eb80
    unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
    MeshRef& operator[](unsigned int i) { MeshRef* p = mpBegin + i; return *p; }
};

class cSPModel {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
    virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
    virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
    virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
    virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51();
    virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55();
    virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
    virtual void v60();
    virtual bool GetMeshes(uint32_t modelId, MeshRefVector& meshes);   // slot 61 (+0xf4)
};

namespace SP {
class cSPEditorBlock {
public:
    uint32_t mPad0[4];
    uint32_t mModelId;             // +0x10
    uint32_t mPad14;
    cSPModel* mpModel;             // +0x18
    uint32_t GetModelIdRaw() { return mModelId; }
    cSPModel* GetModelRaw() { return mpModel; }
    uint32_t GetModelId() { uint32_t id = GetModelIdRaw(); return id; }
    cSPModel* GetModel() { cSPModel* m = GetModelRaw(); return m; }
};
}

namespace nSPSkinner {
class cExportHelper {
public:
    void ExportMeshAdd(eastl::pair<unsigned int, unsigned int> id, const cSPVector3* positions,
                       const cSPVector3* normals, const cSPVector2* texcoords,
                       const unsigned int* indices, unsigned int numVertices,
                       unsigned int numTriangles, unsigned int positionStride,
                       unsigned int normalStride, unsigned int texcoordStride);   // 0x00500ef0
};
}

namespace {

struct cBlockGeometryExporter {
    eastl::vector<unsigned int, eastl::sp_vector_allocator> mTriangleIndices;   // +0x00
    eastl::vector<cSPVector3, eastl::sp_vector_allocator> mPositions;           // +0x14
    eastl::vector<cSPVector3, eastl::sp_vector_allocator> mNormals;             // +0x28
    eastl::vector<cSPVector2, eastl::sp_vector_allocator> mTextureCoordinates;  // +0x3c
    eastl::vector<cSPVector4, eastl::sp_vector_allocator> mBoneWeights;         // +0x50
    eastl::vector<SP::tMDUByte4, eastl::sp_vector_allocator> mBoneIndices;      // +0x64

    void BuildBoundingBoxGeometry(SP::cSPEditorBlock* block);                   // 0x004655e0
    void Export(nSPSkinner::cExportHelper& helper, SP::cSPEditorBlock* block,
                EA::RectT<float>& uvRect, unsigned int id, bool flag);
};

// @ 0x00464bb0
void cBlockGeometryExporter::Export(nSPSkinner::cExportHelper& helper, SP::cSPEditorBlock* block,
                                    EA::RectT<float>& uvRect, unsigned int id, bool flag)
{
    mTriangleIndices.clear();
    mPositions.clear();
    mNormals.clear();
    mTextureCoordinates.clear();
    mBoneWeights.clear();
    mBoneIndices.clear();

    MeshRefVector meshes = MeshRefVector(eastl::allocator_tag());
    uint32_t modelId = block->GetModelId();
    cSPModel* pModel = block->GetModel();
    if (pModel->GetMeshes(modelId, meshes)) {
        unsigned int vertexBase = 0;
        unsigned int indexBase = 0;
        for (unsigned int i = 0, numMeshes = meshes.size(); i < numMeshes; i++) {
            cMeshData* meshObj = meshes[i].mpObject;

            const char* srcPositions = 0;
            const char* normIter = 0;
            const char* uvData = 0;
            unsigned int nVerts = 0xffffffff;
            unsigned int posStride = 0xffffffff;
            unsigned int srcNormCount = 0xffffffff;
            unsigned int nrmStride = 0xffffffff;
            unsigned int numUV = 0xffffffff;
            unsigned int uvSrcStride = 0xffffffff;
            int streamUsages[3] = { 1, 2, 8 };
            int compCount[3] = { 3, 3, 2 };
            bool hasUVs = true;
            int elementIndices[3];

            if (!FindVertexElements(meshObj, 3, elementIndices, streamUsages, 0, compCount, 0)) {
                hasUVs = false;
                if (!FindVertexElements(meshObj, 2, elementIndices, streamUsages, 0, compCount, 0))
                    continue;
            }

            cMDStream* positionStreamDesc = &meshObj->mpElements[elementIndices[0]].mStream;
            cMDStream* normalDesc = &meshObj->mpElements[elementIndices[1]].mStream;
            srcPositions = (const char*)positionStreamDesc->mpData;
            posStride = positionStreamDesc->mStride;
            nVerts = positionStreamDesc->mCount;
            normIter = (const char*)normalDesc->mpData;
            nrmStride = normalDesc->mStride;
            srcNormCount = normalDesc->mCount;
            if (hasUVs) {
                cMDStream* uvStream = &meshObj->mpElements[elementIndices[2]].mStream;
                uvData = (const char*)uvStream->mpData;
                uvSrcStride = uvStream->mStride;
                numUV = uvStream->mCount;
            }

            mPositions.resize(mPositions.size() + nVerts);
            ScratchSlots<5>();
            cSPVector3* positionDst = &mPositions[vertexBase];
            for (unsigned int j = 0, n = nVerts; j < n; j++) {
                cSPVector3 v(*(const cSPVector3*)srcPositions);
                *positionDst = v;
                positionDst++;
                srcPositions += posStride;
            }

            mNormals.resize(mNormals.size() + srcNormCount);
            ScratchSlots<5>();
            cSPVector3* normalDst = &mNormals[vertexBase];
            for (unsigned int j = 0, n = srcNormCount; j < n; j++) {
                cSPVector3 v(*(const cSPVector3*)normIter);
                *normalDst = v;
                normalDst++;
                normIter += nrmStride;
            }

            if (hasUVs) {
                mTextureCoordinates.resize(mTextureCoordinates.size() + numUV);
                ScratchSlots<4>();
                cSPVector2* uvOut = &mTextureCoordinates[vertexBase];
                for (unsigned int j = 0, n = numUV; j < n; j++) {
                    cSPVector2 v(*(const cSPVector2*)uvData);
                    *uvOut = v;
                    uvOut++;
                    uvData += uvSrcStride;
                }
            } else {
                mTextureCoordinates.resize(mTextureCoordinates.size() + nVerts);
                ScratchSlots<4>();
                for (unsigned int j = 0, n = nVerts; j < n; j++) {
                    mTextureCoordinates[vertexBase + j] = *(cSPVector2*)&mPositions[vertexBase + j];
                }
            }

            const uint16_t* indexData = meshObj->mSections.at(0).mpIndices;
            unsigned int numIdx = meshObj->mSections[0].mIndexCount;
            mTriangleIndices.resize(mTriangleIndices.size() + numIdx);
            ScratchSlots<3>();
            unsigned int* pIndexDst = &mTriangleIndices[indexBase];
            for (unsigned int j = 0, n = numIdx; j < n; j++) {
                *pIndexDst = *indexData + vertexBase;
                pIndexDst++;
                indexData++;
            }

            vertexBase += nVerts;
            indexBase += numIdx;
        }

        for (int k = 0, n = mTextureCoordinates.size(); k < n; k++) {
            cSPVector2& uv = mTextureCoordinates[k];
            if (uv[1] < 0.0f)
                uv[1] += 1.0f;
            uv[0] *= uvRect.right - uvRect.left;
            uv[1] *= uvRect.bottom - uvRect.top;
            uv[0] += uvRect.left;
            uv[1] += uvRect.top;
        }
    } else {
        BuildBoundingBoxGeometry(block);
    }

    helper.ExportMeshAdd(eastl::pair<unsigned int, unsigned int>(id, 0xffffffff),
                         &mPositions[0], &mNormals[0], &mTextureCoordinates[0],
                         &mTriangleIndices[0], mPositions.size(), mTriangleIndices.size() / 3,
                         12, 12, 8);
    ScratchSlots<8>();
}

}  // namespace
