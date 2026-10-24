// src/game/SPBake/SPEditorExportUtilities.cpp -- migrated from slice(s) s00467a20, s00464300, s00461680, s004614b0, s004604f0, s00471b50, s00470bd0, s0046ff00, s0046f2a0, s0046e450, s0046d660, s0046c900, s0046c000, s0046b8e0, s0046aac0, s00469bb0, s00469500, s004680c0, s00466e20, s00466320, s004655e0, s00464bb0, s004629e0 by tools/migrate/rewrite.py
// Object file: SPBake/SPEditorExportUtilities.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPEditorSkinPart.h"
#include "SP/cRuntimeCreatureResource.h"
#include "EA/IO/FileStream.h"
#include "nSPSkinner/cMesh.h"
#include "SP/cSPEditorBlock.h"
#include "SP/cModelInstance.h"
#include "EA/ResourceMan/Key.h"
#include "nSPSkinner/cExportHelper.h"
#include "SP/cJob.h"
#include "SP/cPropertyManager.h"
#include "cSPMatrix3.h"
#include "cSPVector3.h"
#include "cSPTransform.h"
#include "cSPBoundingBox.h"
#include "SP/cModelWorld.h"
#include "EA/Variant.h"
#include "SP/cPropertyList.h"
#include "SP/cSPEditorModel.h"
#include "SP/cEditorResource.h"
#include "SP/cDirectPropertyList.h"
#include "SP/cEditorExportCreatureBlock.h"
#include "SP/cSPEditorExportCreatureModel.h"
#include "SP/cMWModel.h"
#include <stdio.h>
#include <stddef.h>

// unnamed retail callees and globals (address in the comment)
extern "C" long __cdecl _InterlockedExchangeAdd(long volatile* p, long v);
extern const char* kBoneTypeNames[];      // 0x150c4ac
extern const uint32_t kIndexMask[];       // 0x13eec84
#pragma intrinsic(_InterlockedExchangeAdd)

// ---- items of slice s004629e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" long __cdecl _InterlockedExchangeAdd(long volatile* p, long v);
struct Vector2 {
    float x, y;
    float& operator[](int i) { return (&x)[i]; }
};
struct Vector3 {
    float x, y, z;
};
struct Vector4f {            // blend weights
    float w[4];
};
struct BoneIdx4 {            // blend indices
    uint16_t b[4];
};
struct Matrix3 {
    Vector3 m[3];
    Matrix3();                                           // 0x402ab0 (empty ctor)
    Vector3& operator[](int i) { return m[i]; }
};
struct Matrix4 {
    float m[4][4];
    Matrix4();                                           // 0x402ab0 (same empty ctor, ICF-folded)
};
struct Matrix43 {            // 0x30-byte bone matrix as returned by the model manager
    float m[4][3];
};
Matrix4 operator*(const Matrix4& a, const Matrix4& b);   // 0x45daa0 (cdecl, sret)
Vector3 Cross(const Vector3& a, const Vector3& b);       // 0x44e460 (cdecl, sret)
void Orthonormalize(Matrix3* m);                         // 0x698650
void Matrix43ToMatrix4(const Matrix43* src, Matrix4* dst); // 0x732eb0
struct Transform {
    uint16_t mFlags;         // +0x00
    uint16_t mnChanges;      // +0x02
    Vector3  mOffset;        // +0x04
    float    mScale;         // +0x10
    Matrix3  mRotation;      // +0x14
    Transform();                                         // 0x409930
    Matrix4 ToMatrix4() const;                           // 0x6b9440
    void SetScale(float s) { mScale = s; mnChanges++; }
    void SetRotation(const Matrix3& r) { mRotation = r; mFlags |= 2; mnChanges++; }
    void SetOffset(const Vector3& v) { mOffset = v; mFlags |= 4; mnChanges++; }
};
struct sp_vector_allocator {
    const char* mpName;
    int         mFlags;
};
struct AllocTag { AllocTag() {} };
template <class T>
struct vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator mAllocator;

    vector();
    explicit vector(const AllocTag& a);                    // 0x540470 for vector<uint32_t>
    ~vector();                                             // 0x41eb80 for vector<uint32_t>
    vector& operator=(const vector& x);
    unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
    T* begin() { return mpBegin; }
    T* end() { return mpEnd; }
    T& operator[](unsigned int n) { return mpBegin[n]; }
    bool empty() const;                                    // 0x526430 (out of line)
    void resize(unsigned int n);
    void resize(unsigned int n, const T& value);
    void reserve(unsigned int n);
    void push_back(const T& value);
    T* erase(T* first, T* last);
    void clear() { erase(mpBegin, mpEnd); }
};
struct fixed_vector_Matrix43 {
    Matrix43* mpBegin;
    Matrix43* mpEnd;
    Matrix43* mpCapacity;
    int       mAllocator[3];
    Matrix43  mBuffer[64];
    explicit fixed_vector_Matrix43(unsigned int n);        // 0x41d510
    void DoFree();                                         // 0x428130
    ~fixed_vector_Matrix43() {
        for (Matrix43* p = mpBegin; p < mpEnd; ++p) {
        }
        DoFree();
    }
    Matrix43& operator[](int n) { return mpBegin[n]; }
};
struct fixed_vector_int {
    int* mpBegin;
    int* mpEnd;
    int* mpCapacity;
    int  mAllocator[3];
    int  mBuffer[64];
    explicit fixed_vector_int(unsigned int n);             // 0x41d0c0
    ~fixed_vector_int();                                   // 0x4209b0
    int& operator[](int n) { return mpBegin[n]; }
};
struct CtorSprintf {};
struct wstring {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    int      mAllocator;
    wstring(CtorSprintf tag, const wchar_t* fmt, ...);     // 0x473020
    ~wstring() { DeallocateSelf(); }
    void DeallocateSelf();                                 // 0x4237d0
    wstring& assign(const wchar_t* first, const wchar_t* last);   // 0x423650
    wstring& assign(const wchar_t* p) { return assign(p, p + CharStrlen(p)); }
    static unsigned int CharStrlen(const wchar_t* p) {
        const wchar_t* pCurrent = p;
        while (*pCurrent) ++pCurrent;
        return (unsigned int)(pCurrent - p);
    }
    const wchar_t* c_str() const { return mpBegin; }
};
namespace EA {
namespace IO {
bool SplitPath(const wchar_t* pPath, wchar_t* pDrive, wchar_t* pDirectory, wchar_t* pFileName,
               wchar_t* pExtension, int nCapacity);    // 0x930180
}
}
namespace EA {
namespace IO {
class FileStream_s0046_29e0 {
public:
    FileStream_s0046_29e0(const wchar_t* pPath);                     // 0x931e10
    ~FileStream_s0046_29e0();                                         // 0x931e70
    bool Open(int nAccessFlags, int nCreationDisposition, int nSharing, int nUsageHints); // 0x9318f0
    bool Close();                                          // 0x931a70
    char mData[0x230];
};
}
}
struct ExportHelperA {             // 0xa8
    char mData[0xa8];
    ExportHelperA();               // 0x464300
    ~ExportHelperA();              // 0x464480
};
struct ExportHelperB {             // 0x78
    char mData[0x78];
    ExportHelperB();               // 0x464580
    ~ExportHelperB();              // 0x464680
};
struct ColladaExport {
    wstring              mName;          // +0x00
    vector<Vector3>      mPositions;     // +0x10
    vector<Vector3>      mNormals;       // +0x24
    vector<Vector2>      mUVs;           // +0x38
    vector<Vector3>      mTangents;      // +0x4c
    vector<Vector3>      mBinormals;     // +0x60
    vector<BoneIdx4>     mBoneIndices;   // +0x74
    vector<Vector4f>     mBoneWeights;   // +0x88
    vector<uint32_t>     mPosIndices;    // +0x9c
    vector<uint32_t>     mNormalIndices; // +0xb0
    vector<uint32_t>     mUVIndices;     // +0xc4
    vector<const char*>  mBoneNames;     // +0xd8
    vector<int>          mBoneParents;   // +0xec
    vector<Matrix4>      mBindMatrices;  // +0x100
    char                 mPad114[0x14];  // +0x114
    vector<Matrix4>      mBoneMatrices;  // +0x128
    char                 mPad13c[0x14];  // +0x13c
    ColladaExport();                     // 0x45b7c0
    ~ColladaExport();                    // 0x45b9a0
    void SetRootBoneCount(int n);        // 0x45bc20
    void Finalize0();                    // 0x45c0f0
    void Finalize1();                    // 0x45bc80
    bool Write(EA::IO::FileStream_s0046_29e0* stream); // 0x45c350
};
struct EditorBone {                       // 0x8c
    char     pad00[4];
    int16_t  mParent;                     // +0x04
    char     pad06[4];
    uint8_t  mHasModel;                   // +0x0a
    uint8_t  mType;                       // +0x0b  (5 = root-chain bone)
    char     pad0c[0x20];
    float    mScale;                      // +0x2c
    Matrix3  mRotation;                   // +0x30
    Vector3  mPosition;                   // +0x54
    char     pad60[0x2c];
};
struct EditorSkeleton {
    char                pad[0x98];
    vector<EditorBone>  mBones;           // +0x98
};
struct TangentFrame {                     // 0x18
    Vector3 mTangent;
    Vector3 mBinormal;
};
struct SkinMesh {
    char                   pad[8];
    vector<Vector3>        mPositions;    // +0x08
    vector<Vector3>        mNormals;      // +0x1c
    vector<Vector2>        mUVs;          // +0x30
    vector<TangentFrame>   mFrames;       // +0x44
    vector<uint32_t>       mPosIndices;   // +0x58
    vector<uint32_t>       mNormalIndices;// +0x6c
    vector<uint32_t>       mUVIndices;    // +0x80
};
struct SkinVertexWeights {                // 0x14
    uint8_t mIndex[4];
    Vector4f mWeight;
};
struct UVRect {
    float x0, y0, x1, y1;
};
struct IModelManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80();
    virtual int  GetBoneCount(uint32_t id);                               // +0x84
    virtual void GetBoneMatrices(uint32_t id, Matrix43* out, int flags);  // +0x88
    virtual void GetBindMatrices(uint32_t id, Matrix43* out);             // +0x8c
    virtual void v90();
    virtual void GetBoneParents(uint32_t id, int* out);                   // +0x94
    virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac();
    virtual void vb0(); virtual void vb4(); virtual void vb8(); virtual void vbc();
    virtual void vc0(); virtual void vc4(); virtual void vc8(); virtual void vcc();
    virtual void vd0(); virtual void vd4(); virtual void vd8(); virtual void vdc();
    virtual void ve0(); virtual void ve4(); virtual void ve8(); virtual void vec();
    virtual void vf0(); virtual void vf4();
    virtual bool GetModelInfo(uint32_t id, vector<uint32_t>* models, Transform* xf); // +0xf8
};
struct EditorBlock {
    char           pad[0x10];
    uint32_t       mModelID;              // +0x10
    char           pad14[4];
    IModelManager* mpModelManager;        // +0x18
    void InitNonDeformAnimations();       // 0x448b10
    uint32_t GetModelID() { return mModelID; }
    IModelManager* GetModelManager() { return mpModelManager; }
};
struct EditorCreatureData {
    char                       pad00[8];
    EditorSkeleton*            mpSkeleton;    // +0x08
    char                       pad0c[0x28];
    SkinMesh*                  mpSkinMesh;    // +0x34
    char                       pad38[0x30];
    vector<Transform>          mBindPose;     // +0x68
    vector<SkinVertexWeights>  mSkinWeights;  // +0x7c
    vector<UVRect>             mUVRects;      // +0x90
    char                       padA4[0x1c];
    EditorBlock**              mpBlocks;      // +0xc0
    EditorSkeleton* GetSkeleton() { return mpSkeleton; }
    SkinMesh* GetSkinMesh() { return mpSkinMesh; }
};
struct EditorModel {
    const wchar_t* GetFileName();             // 0x4ae000 (returns +0x7c)
};
struct VertexStreamData {
    int      mCount;                          // +0x00
    char*    mpData;                          // +0x04
    uint16_t mFormat;                         // +0x08
    uint16_t mStride;                         // +0x0a
};
struct VertexStream {                         // 0x20
    char             pad[8];
    int              mType;                   // +0x08 (7 = ubyte4; component count for floats)
    char             pad0c[4];
    VertexStreamData mData;                   // +0x10
    char             pad1c[4];
};
struct IndexBuffer {                          // 0x8c
    int      mCount;
    char*    mpData;
    uint16_t mFormat;
    uint16_t mStride;
    char     pad[0x80];
};
struct BakedModel {
    char          pad00[4];
    int           mnRefCount;                 // +0x04
    VertexStream* mpStreams;                  // +0x08
    char          pad0c[0x10];
    IndexBuffer*  mpIndexBuffers;             // +0x1c
    char          pad20[0x38];
    BakedModel(uint32_t key);                 // 0x40f070
    void AddRef() { _InterlockedExchangeAdd((long*)&mnRefCount, 1); }
    void Release();                           // 0x404f90
};
void* operator new(unsigned int size, const char* pName, int flags, unsigned int debugFlags,
                   const char* pFile, int line);   // 0xf473a0
struct BakedModelRef {
    BakedModel* mpObject;
    BakedModelRef(BakedModel* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~BakedModelRef() { if (mpObject) mpObject->Release(); }
    BakedModel* get() const { return mpObject; }
};
void ApplyModelTransform(Transform* xf, BakedModel* model);      // 0x734d00
void PrepareModel(BakedModel* model);                            // 0x733ed0
bool FindVertexStreams(BakedModel* model, int n, int* outIndices, const int* usages,
                       int p4, const int* formats, int p6);      // 0x71ded0
int FindVertexStream(BakedModel* model, int usage, int usageIndex, int p3, int format); // 0x71ddc0
extern const char* kBoneTypeNames[];      // 0x150c4ac
extern const uint32_t kIndexMask[];       // 0x13eec84
// ---- items of slice s004629e0 end

// ---- items of slice s00464bb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
template <int N> inline void ScratchSlots() { uint32_t s[N]; }
namespace EA {
template<class T> struct RectT_s0046_4bb0 {
    T left, top, right, bottom;
};
}
struct cSPVector3_s0046_4bb0 {
    float x, y, z;
    cSPVector3_s0046_4bb0() {}
    cSPVector3_s0046_4bb0(const cSPVector3_s0046_4bb0& v) { x = v.x; y = v.y; z = v.z; }
};
struct cSPVector2_s0046_4bb0 {
    float x, y;
    cSPVector2_s0046_4bb0() {}
    cSPVector2_s0046_4bb0(const cSPVector2_s0046_4bb0& v) { x = v.x; y = v.y; }
    float& operator[](int i) { return (&x)[i]; }
};
struct cSPVector4_s0046_4bb0 { float x, y, z, w; };
namespace SP {
 struct tMDUByte4_s0046_4bb0 { uint8_t v[4]; }; 
}
namespace eastl {
struct sp_vector_allocator_s0046_4bb0 { uint32_t mData[2]; };
}
namespace eastl {
struct allocator_tag { allocator_tag() {} };   // empty argument of the RefVector ctor
}
namespace eastl {
template<class T, class A> class vector_s0046_4bb0 {
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
}
namespace eastl {
template<class T1, class T2> struct pair_s0046_4bb0 {
    T1 first;
    T2 second;
    pair_s0046_4bb0(const T1& a, const T2& b) : first(a), second(b) {}
};
}
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
class cSPEditorBlock_s0046_4bb0 {
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
class cExportHelper_s0046_4bb0 {
public:
    void ExportMeshAdd(eastl::pair_s0046_4bb0<unsigned int, unsigned int> id, const cSPVector3_s0046_4bb0* positions,
                       const cSPVector3_s0046_4bb0* normals, const cSPVector2_s0046_4bb0* texcoords,
                       const unsigned int* indices, unsigned int numVertices,
                       unsigned int numTriangles, unsigned int positionStride,
                       unsigned int normalStride, unsigned int texcoordStride);   // 0x00500ef0
};
}
namespace {

struct cBlockGeometryExporter {
    eastl::vector_s0046_4bb0<unsigned int, eastl::sp_vector_allocator_s0046_4bb0> mTriangleIndices;   // +0x00
    eastl::vector_s0046_4bb0<cSPVector3_s0046_4bb0, eastl::sp_vector_allocator_s0046_4bb0> mPositions;           // +0x14
    eastl::vector_s0046_4bb0<cSPVector3_s0046_4bb0, eastl::sp_vector_allocator_s0046_4bb0> mNormals;             // +0x28
    eastl::vector_s0046_4bb0<cSPVector2_s0046_4bb0, eastl::sp_vector_allocator_s0046_4bb0> mTextureCoordinates;  // +0x3c
    eastl::vector_s0046_4bb0<cSPVector4_s0046_4bb0, eastl::sp_vector_allocator_s0046_4bb0> mBoneWeights;         // +0x50
    eastl::vector_s0046_4bb0<SP::tMDUByte4_s0046_4bb0, eastl::sp_vector_allocator_s0046_4bb0> mBoneIndices;      // +0x64

    void BuildBoundingBoxGeometry(SP::cSPEditorBlock_s0046_4bb0* block);                   // 0x004655e0
    void Export(nSPSkinner::cExportHelper_s0046_4bb0& helper, SP::cSPEditorBlock_s0046_4bb0* block,
                EA::RectT_s0046_4bb0<float>& uvRect, unsigned int id, bool flag);
};

}  // namespace
// ---- items of slice s00464bb0 end

// ---- items of slice s004655e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace rw {
namespace math {
namespace fpu {
template<class T, int N> struct Vector3Template_s0046_55e0 {
    T x, y, z;
    Vector3Template_s0046_55e0() {}
    Vector3Template_s0046_55e0(const Vector3Template_s0046_55e0& v);                               // 0x004098a0
    // The original's inlined expansion of the copy constructor (cl /Ob1 expanded it at the first
    // five sites of this function and called it out of line at the other seven).
    void CopyConstructInline(const Vector3Template_s0046_55e0& v) { x = v.x; y = v.y; z = v.z; }
};
}
}
}
namespace rw {
namespace math {
namespace fpu {
template<class T, int N> struct Matrix33Template_s0046_55e0 {
    T m[9];
};
}
}
}
typedef rw::math::fpu::Vector3Template_s0046_55e0<float, 0> Vector3f;
struct cSPVector3_s0046_55e0 : Vector3f {
    cSPVector3_s0046_55e0() {}
    cSPVector3_s0046_55e0(const Vector3f& v) : Vector3f(v) {}
};
struct cSPVector2_s0046_55e0 {
    float x, y;
    static const cSPVector2_s0046_55e0 ZERO;                                        // 0x015d4104
};
struct cSPMatrix3_s0046_55e0 : rw::math::fpu::Matrix33Template_s0046_55e0<float, 0> {};
Vector3f operator-(const Vector3f& a, const Vector3f& b);                // 0x0041db10
Vector3f Cross(const Vector3f& a, const Vector3f& b);                    // 0x0044e460
cSPVector3_s0046_55e0 Normalize(const Vector3f& v);                                 // 0x00436ce0
struct cSPBoundingBox_s0046_55e0 {
    cSPVector3_s0046_55e0 mMin;
    cSPVector3_s0046_55e0 mMax;
    void GetCorners(cSPVector3_s0046_55e0* corners) const;                          // 0x00466320
};
struct cSPTransform_s0046_55e0 {
    uint16_t mFlags;                          // +0x00
    uint16_t mChangeCount;                    // +0x02
    cSPVector3_s0046_55e0 mPosition;                     // +0x04
    float mScale;                             // +0x10
    cSPMatrix3_s0046_55e0 mRotation;                     // +0x14
    cSPTransform_s0046_55e0();                                                      // 0x00409930
    void SetPosition(const cSPVector3_s0046_55e0& p) { mPosition = p; mFlags |= 4; mChangeCount++; }
    void SetRotation(const cSPMatrix3_s0046_55e0& m) { mRotation = m; mFlags |= 2; mChangeCount++; }
    void ApplyToPoint(cSPVector3_s0046_55e0& p) const;                              // 0x0044d4f0
};
namespace SP {
class cSPEditorBlock_s0046_55e0 {
public:
    enum eBBoxType { kBBoxType0 = 0, kBBoxType1 = 1 };
    cSPBoundingBox_s0046_55e0 GetBBox(eBBoxType type, bool a, bool b);              // 0x0044ae00
    uint8_t mPad[0x48];
    cSPVector3_s0046_55e0 mPosition;                     // +0x48
    uint8_t mPad1[0x60 - 0x54];
    cSPMatrix3_s0046_55e0 mOrientation;                  // +0x60
};
}
namespace eastl {
struct sp_vector_allocator_s0046_55e0 { uint32_t mData[2]; };
}
namespace eastl {
template<class T, class A> class vector_s0046_55e0 {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    A mAllocator;
    void push_back(const T& value);
};
}
namespace {

struct cBlockGeometryExporter_s0046_55e0 {
    eastl::vector_s0046_55e0<unsigned int, eastl::sp_vector_allocator_s0046_55e0> mTriangleIndices;   // +0x00 (push_back 0x00454860)
    eastl::vector_s0046_55e0<cSPVector3_s0046_55e0, eastl::sp_vector_allocator_s0046_55e0> mPositions;           // +0x14 (push_back 0x004739d0)
    eastl::vector_s0046_55e0<cSPVector3_s0046_55e0, eastl::sp_vector_allocator_s0046_55e0> mNormals;             // +0x28
    eastl::vector_s0046_55e0<cSPVector2_s0046_55e0, eastl::sp_vector_allocator_s0046_55e0> mTextureCoordinates;  // +0x3c (push_back 0x00473f30)

    void BuildBoundingBoxGeometry(SP::cSPEditorBlock_s0046_55e0* block);
};

} // anonymous namespace
// ---- items of slice s004655e0 end

// ---- items of slice s00466320 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct wstring_s0046_6320 {                                           // eastl::basic_string<wchar_t>
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    int      mAllocator;
    wstring_s0046_6320(CtorSprintf tag, const wchar_t* fmt, ...);     // 0x473020
    ~wstring_s0046_6320() { DeallocateSelf(); }
    void DeallocateSelf();                                 // 0x4237d0
};
struct cstring {                                           // eastl::basic_string<char>
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    int   mAllocator;
    cstring(CtorSprintf tag, const char* fmt, ...);        // 0x472f50
    ~cstring();                                            // 0x530670
};
struct ModelPtr {                                          // intrusive_ptr element
    unsigned int mpObject;
};
struct ModelVec {                                          // vector<intrusive_ptr<..>> (RefVector), 0x14 bytes
    ModelPtr* mpBegin;
    ModelPtr* mpEnd;
    ModelPtr* mpCapacity;
    int mAllocator[2];
    explicit ModelVec(const AllocTag& a);                  // 0x540470
    ~ModelVec();                                           // 0x41eb80
    ModelPtr* end() const { ModelPtr* e = mpEnd; return e; }
};
struct ResourceKey {
    unsigned int instanceID;                               // +0
    unsigned int typeID;                                   // +4
    unsigned int groupID;                                  // +8
};
struct Transform_s0046_6320 {                                         // 0x38 bytes
    char mData[0x38];
    Transform_s0046_6320();                                           // 0x409930
};
struct MeshAccum;                                          // ExportHelperB (0x78 bytes)
struct cExportHelper {                                     // ExportHelperA (0xa8 bytes)
    char mData[0xa8];
    cExportHelper();                                       // 0x464300
    ~cExportHelper();                                      // 0x464480
    void SetName(const wchar_t* path);                     // 0x4fe860
    void ExportDummyStaticSkeleton();                      // 0x5001c0
    void ExportMeshBegin(unsigned int numSubmeshes, bool ascii);   // 0x500880
    void ExportMeshEnd();                                  // 0x501200
};
struct MeshAccum {
    char mData[0x78];
    MeshAccum();                                           // 0x464580
    ~MeshAccum();                                          // 0x464680
    void Export(cExportHelper* helper, const ModelVec& models);    // 0x466e20
};
struct ModelInst;
struct ModelRoot {                                         // 0x100 bytes, ctor 0x740e90
    void* vt;
    int   mnRefCount;
    char  pad8[0x100 - 8];
    ModelRoot();                                           // 0x740e90
    int AddRef() { int n = mnRefCount + 1; mnRefCount = mnRefCount + 1; return n; }
    void Release();                                        // EA::RefCountTemplate<int>::Release 0x453540
    void Init(struct IResource* res);                      // 0x742b30
    void SetInstance(struct ModelInst* inst);              // 0x73ab40
    void Collect(Transform_s0046_6320* xf, ModelVec* out);            // 0x743270
};
struct ModelInst {                                         // cModelInstance, 0xa0 bytes, ctor 0x7400f0
    void* vt;
    int   mRefCount;
    char  pad8[0xa0 - 8];
    ModelInst();                                           // 0x7400f0
    int AddRef() { return mRefCount++ + 1; }
    void Release();                                        // 0x453540
    void SetFlags(bool a, bool b);                         // 0x73a800
    void ConstructFromGameModelResource(struct IResource* res);    // 0x742db0
};
template <class T>
struct RefPtr {                                            // eastl::intrusive_ptr
    T* mpObject;
    RefPtr(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~RefPtr() { if (mpObject) mpObject->Release(); }
};
void PrepareModelImpl(unsigned int model);                 // 0x733ed0 (cdecl)
inline void PrepareModel_s0046_6320(unsigned int model) { PrepareModelImpl(model); }
ResourceKey* DefaultModelKey();                            // 0x6bb640 (returns the address 0x1531cdc)
struct Property {
    char pad0[0x10];
    unsigned short mFlags;                                 // +0x10
    unsigned short mType;                                  // +0x12
    ResourceKey* AsKey();                                  // 0x446ff0 (thiscall)
};
inline ResourceKey* ModelKeyOf(Property* p)
{
    if (p->mType == 0x20 || p->mType == 0x10)
        return p->AsKey();
    return DefaultModelKey();
}
struct IRefCounted {
    virtual void AddRef();
    virtual void Release();                                // +4
};
struct IPropList : IRefCounted {
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8();
    virtual bool GetProperty(unsigned int id, Property** out);     // +0x24
};
struct IResource : IRefCounted {};
template <class T>
struct AutoRefCount {
    T* mp;
    ~AutoRefCount() { if (mp) mp->Release(); }
    void** AsPPVoidParam();                                // 0x41d870
    void** operator&() { return AsPPVoidParam(); }
    T* operator->() const { return mp; }
};
struct PropMgr {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10();
    virtual bool GetPropList(unsigned int type, unsigned int group, void** out);   // +0x2c
};
PropMgr* GetPropMgr();                                     // 0x67de30
struct ResourceMan {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual bool GetResource(ResourceKey* key, void** out, int a, int b, int c, int d);   // +0xc
};
ResourceMan* GetManager();                                 // 0x67dcd0
struct TexData { int format; };
struct Tex {
    TexData* mpData; unsigned char mFlags;
};
struct TexMgr {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12();
    virtual void Load(Tex* t);                             // +0x34
};
TexMgr* GetTexMgr();                                       // 0x67dd60
struct TexId { int lo; int hi; };
struct TexIdMgr {                                          // 0x67dd40
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04(); virtual void v05();
    virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
    virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual void v18(); virtual void v19(); virtual void v1a(); virtual void v1b(); virtual void v1c(); virtual void v1d();
    virtual void v1e(); virtual void v1f(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
    virtual void v2a(); virtual void v2b(); virtual void v2c();
    virtual void GetBakeInfoId(TexId* out);                // +0xb4
    virtual void GetNormalId(TexId* out);                  // +0xb8
    virtual void GetDiffuseId(TexId* out);                 // +0xbc
};
TexIdMgr* GetTexIdMgr();                                   // 0x67dd40
struct TexLookup {                                         // 0x67dda0
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6();
    virtual Tex* GetTexture(int lo, int hi);               // +0x1c
};
TexLookup* GetTexLookup();                                 // 0x67dda0
void SaveTga7b2380(const char* name, TexData* data);       // 0x7b2380 (cdecl)
inline TexData* DataOf(Tex* t)
{
    if (!(t->mFlags & 1)) GetTexMgr()->Load(t);
    return t->mpData;
}
// ---- items of slice s00466320 end

// ---- items of slice s00466e20 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern unsigned int maskTable[];   // 0x013eec84 index-format masks
extern char tableA[];              // 0x0140cf84
extern char tableB[];              // 0x0140cf90
struct ArrF {
    int pad0;                      // +0 element count
    char* data;                    // +4
    unsigned short maskIdx;        // +8
    unsigned short stride;         // +0xa
    unsigned int padc;             // +0xc
    unsigned int get(int i);       // 0x00467980
    char* at(unsigned int i);      // 0x00472640  return data + stride * i  (out of line)
    // inline twins of get()/at() (expanded in place in FUN_00466e20)
    unsigned int getI(unsigned int i) { return *(unsigned int*)(data + stride * i) & maskTable[maskIdx]; }
    char* atI(unsigned int i) { return data + stride * i; }
};
struct ArrG {
    int idx;
    int pad1;
    int b;
    int a;
    int pad10;
    int f();
};
struct Vec3 { float x, y, z; };
struct Vec2 {
    float x, y;
    float& operator[](int i) { return (&x)[i]; }
};
struct sp_vector_allocator_s0046_6e20 { sp_vector_allocator_s0046_6e20() {} };
struct VecU32 {
    unsigned int* mpBegin; unsigned int* mpEnd; unsigned int* mpCapacity; unsigned int mAlloc[2];
    unsigned int* erase(unsigned int* first, unsigned int* last);   // 0x004769b0
    unsigned int size();                                            // 0x004746a0
    void push_back(const unsigned int& v);                          // 0x00454860
    void clear() { erase(mpBegin, mpEnd); }
    unsigned int& operator[](unsigned int i) { unsigned int* p = mpBegin + i; return *p; }
};
struct VecV3 {
    Vec3* mpBegin; Vec3* mpEnd; Vec3* mpCapacity; unsigned int mAlloc[2];
    Vec3* erase(Vec3* first, Vec3* last);                           // 0x0050f740
    unsigned int size();                                            // 0x004737f0
    void push_back(const Vec3& v);                                  // 0x004739d0
    void clear() { erase(mpBegin, mpEnd); }
    Vec3& operator[](unsigned int i) { Vec3* p = mpBegin + i; return *p; }
};
struct VecV2 {
    Vec2* mpBegin; Vec2* mpEnd; Vec2* mpCapacity; unsigned int mAlloc[2];
    Vec2* erase(Vec2* first, Vec2* last);                           // 0x00530c80
    unsigned int size();                                            // 0x00474050
    void push_back(const Vec2& v);                                  // 0x00473f30
    void clear() { erase(mpBegin, mpEnd); }
    Vec2& operator[](unsigned int i) { Vec2* p = mpBegin + i; return *p; }
};
struct VecInt {
    int* mpBegin; int* mpEnd; int* mpCapacity; unsigned int mAlloc;
    VecInt(const sp_vector_allocator_s0046_6e20& a);                           // 0x00540470
    ~VecInt();                                                      // 0x004e1bf0
    unsigned int size() { return mpEnd - mpBegin; }
    int& operator[](unsigned int i) { int* p = mpBegin + i; return *p; }
};
struct FormatEntry { short elts; short stream; };
struct FormatVec {
    FormatEntry* mpBegin; FormatEntry* mpEnd;
    FormatEntry& operator[](unsigned int i) { FormatEntry* p = mpBegin + i; return *p; }
};
struct StreamVec {
    ArrF* mpBegin; ArrF* mpEnd;
    bool empty();                                                   // 0x00526430
};
struct Section {                  // 0x8c bytes
    ArrF indices;                 // +0x00
    unsigned int pad10;
    FormatVec mFormat;            // +0x14
    unsigned int pad1c[(0x44 - 0x1c) / 4];
    StreamVec mStreams;           // +0x44
    unsigned int pad4c[(0x8c - 0x4c) / 4];
    bool HasStreams() { return !mStreams.empty(); }
};
struct SectionVec {
    Section* mpBegin; Section* mpEnd;
    int size();                                                     // 0x00475410
};
struct MeshEntry {                // 0x20 bytes
    unsigned int pad0[4];
    ArrF stream;                  // +0x10
};
struct Model {
    unsigned int pad0[2];
    MeshEntry* entries;           // +0x08
    unsigned int pad0c[4];
    SectionVec mSections;         // +0x1c
    unsigned int pad24[3];
    ArrG* mPrims;                 // +0x30
};
struct ModelVec_s0046_6e20 {
    Model** mpBegin; Model** mpEnd;
    unsigned int size() const { return mpEnd - mpBegin; }
    Model*& operator[](unsigned int i) const { Model** p = mpBegin + i; return *p; }
};
bool __cdecl FUN_0071ded0(Model* m, int n, int* idx, int* fmts, int a, int* counts, int b);
int __cdecl FindFormatEntry(Model* m, int section, int elts);          // 0x0071e040
void __cdecl FindPrimitives(Model* m, VecInt* out, int section, int type, int aux);  // 0x0071ee10
struct NodeBone {
    int nidx; int bidx;
    NodeBone(int n, int b) : nidx(n), bidx(b) {}
};
struct cExportHelper_s0046_6e20 {
    void ExportMeshAdd(NodeBone nb, float* pos, float* normals, float* uvs, unsigned int* indices,
                       unsigned int numVerts, unsigned int numFaces, int posStride, int normStride,
                       int uvStride);                              // 0x00500ef0
};
struct MeshAccum_s0046_6e20 {
    VecU32 mIndices;              // +0x00
    VecV3 mPositions;             // +0x14
    VecV3 mNormals;               // +0x28
    VecV2 mUVs;                   // +0x3c
    void Export(cExportHelper_s0046_6e20* helper, const ModelVec_s0046_6e20& models);
};
// ---- items of slice s00466e20 end

// ---- items of slice s004680c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" long __cdecl _InterlockedIncrement(volatile long*);
extern bool g_bUseAltModelKey;            // 0x015d3c30
#pragma intrinsic(_InterlockedIncrement)
inline void* operator new(unsigned int, void* p) { return p; }
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file, int line);
struct IObject {
    virtual int AddRef() = 0;
    virtual int Release() = 0;
};
struct ObjectRef {
    IObject* p;
    ObjectRef() : p(0) {}
    ObjectRef(IObject* o);                // 0x0041cc20
    ~ObjectRef();                         // 0x004a9b10
    ObjectRef& Reset();                   // 0x0041d870
    IObject* get() const { return p; }
    operator IObject**() { return &p; }
};
struct OwnerRef {
    IObject* p;
    OwnerRef(IObject* o);                 // 0x0041cc20
    ~OwnerRef()
    {
        if (p)
            p->Release();
    }
};
struct Vector3_s0046_80c0 {
    float x, y, z;
    Vector3_s0046_80c0(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    Vector3_s0046_80c0(const Vector3_s0046_80c0& o);            // 0x004098a0
};
struct Vector2_s0046_80c0 {
    float x, y;
    Vector2_s0046_80c0(float x_, float y_) : x(x_), y(y_) {}
};
Vector3_s0046_80c0* __cdecl Vector3_Add(Vector3_s0046_80c0* a, const Vector3_s0046_80c0* b);   // 0x0041ddb0 (a += b)
struct cJob {
    int Release();                        // 0x00690120
    void Queue();                         // 0x006909b0
    void AddDependency(cJob* other);      // 0x00691380
    void Wait();                          // 0x006926b0
};
struct JobRef {
    cJob* p;
    JobRef() : p(0) {}
    ~JobRef()
    {
        if (p)
            p->Release();
    }
    JobRef& Reset();                      // 0x0041d940 (drop + return the holder as out-param)
    JobRef& operator=(cJob* j);           // 0x0041cd10
    cJob* get() const { return p; }
    cJob* operator->() const { return p; }
    operator cJob**() { return &p; }
};
template <class T, int N>
struct Vec {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[2];               // sp_vector_allocator
    int size() const { return (int)(mpEnd - mpBegin); }
    T* data() const { return mpBegin; }
    T* begin() const { return mpBegin; }
    T* end() const { return mpEnd; }

    // EASTL vector::push_back. /Ob1 declines to inline these; each call site keeps the callee's
    // reserved frame as a hole in this function's /Od frame.
    void DoInsertValue(T* position, const T& value);
    void DoInsertValueEnd();
    void push_back(const T& value)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
    // The same push_back instance, called after cl had used up this caller's /Ob1 inline budget:
    // no inline attempt, so no reserved frame (from the 6th stream on).
    void push_back_no_inline(const T& value);
    void push_back()
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T();
        else
            DoInsertValue(mpEnd, T());
    }
};
struct PairIF { int i; float f; };
struct Elem16 { uint32_t v[4]; };
struct Elem18 { uint32_t v[6]; };
struct Elem8c { uint32_t v[0x8c / 4]; };
struct Vec12 : Vec<Vector3_s0046_80c0, 0> {
    int count() const;                    // 0x004737f0; push_back 0x004739d0
};
struct VecPairIF : Vec<PairIF, 0> {
    int count() const;                    // 0x00474050
    void erase(PairIF* first, PairIF* last);   // 0x00530c80
    void clear() { erase(mpBegin, mpEnd); }
};
struct VecPairFF : Vec<Vector2_s0046_80c0, 0> {
    int count() const;                    // 0x00474050; push_back 0x00473f30
};
struct Vec16 : Vec<Elem16, 0> {
    int count() const;                    // 0x004743b0
    void erase(Elem16* first, Elem16* last);   // 0x00548690
    void clear() { erase(mpBegin, mpEnd); }
};
struct VecU32_s0046_80c0 : Vec<uint32_t, 0> {
    int count() const;                    // 0x004746a0
    void insert(uint32_t* position, uint32_t n, const uint32_t& value);
    void erase(uint32_t* first, uint32_t* last);
    void resize(uint32_t n, const uint32_t& value)  // 0x004746c0
    {
        if (n > (uint32_t)(mpEnd - mpBegin))
            insert(mpEnd, n - (uint32_t)(mpEnd - mpBegin), value);
        else
            erase(mpBegin + n, mpEnd);
    }
    uint32_t& operator[](int i) { return mpBegin[i]; }
};
struct Vec18 : Vec<Elem18, 0> {};
struct ModelMesh : IObject {
    uint32_t pad04[2];
    VecU32_s0046_80c0 mIndices;                      // +0x0c
    Vec12 mPositions;                     // +0x20
    Vec12 mNormals;                       // +0x34
    Vec12 mTangents;                      // +0x48
    VecPairFF mTexCoords;                 // +0x5c
    VecPairIF mBoneWeights;               // +0x70 (resource type checked)
    Vec16 mBoneIndices;                   // +0x84
    Vec18 mExtra;                         // +0x98
    uint8_t mBonePalette[4];              // +0xac
};
struct EmptyCheck {                       // any EASTL vector seen through its empty() (0x00526430)
    bool empty();
};
struct StreamDesc {
    int mCount;
    void* mpData;
    uint16_t mStride;
    uint16_t mStride2;
    OwnerRef mOwner;

    template <class V>
    StreamDesc(V& v, IObject* owner, int stride)
        : mCount(v.count()), mpData(v.data()), mStride((uint16_t)stride), mStride2((uint16_t)stride),
          mOwner(owner)
    {
    }
    StreamDesc(int count, void* data, IObject* owner, int);      // 0x0046f140
    StreamDesc(Vec18* v, IObject* owner, int);                   // 0x004755a0
    StreamDesc(const StreamDesc& o);                             // 0x00401b80
};
struct StreamElem {
    int mUsage;
    int mIndex;
    int mType;
    int mSlot;
    StreamDesc mDesc;
    StreamElem(int usage, int index, int type, int slot, const StreamDesc& d)
        : mUsage(usage), mIndex(index), mType(type), mSlot(slot), mDesc(d)
    {
    }
};
struct StreamElemC : StreamElem {
    StreamElemC(int usage, int index, int type, int slot, const StreamDesc& d);   // 0x00469500
};
struct StreamVec_s0046_80c0 : Vec<StreamElem, 0> {    // push_back 0x0041f7d0
    void reserve(int n);                  // 0x00475320
    int count() const;                    // 0x00475240
};
struct StreamIndex {
    int16_t mStream;
    int16_t mSub;
    StreamIndex(int s, int sub) : mStream((int16_t)s), mSub((int16_t)sub) {}
};
struct IndexVec : Vec<StreamIndex, 0> {   // push_back 0x00475130
    void reserve(int n);                  // 0x00475040
};
struct IndexRange {                       // 0x14 bytes
    IndexRange(int type, int a, uint32_t first, uint32_t last, int b);   // 0x00469550
    uint32_t v[5];
};
struct IndexRangeVec {
    void push_back(const IndexRange& r);  // 0x004227f0
};
struct Batch {                            // 0x8c bytes
    Batch();
    Batch(const Batch& o);
    void SetIndices(const StreamDesc& d); // 0x004694e0
    uint32_t pad00[4];
    int mVertexCount;                     // +0x10
    IndexVec mStreamIndices;              // +0x14
    uint32_t rest[(0x8c - 0x28) / 4];
};
struct BatchVec : Vec<Batch, 0> {        // push_back() 0x00475430
    Batch& back() { return *(mpEnd - 1); }
};
struct MeshGroup {                        // 0x58 bytes, ThreadedObject refcount at +4
    MeshGroup();                          // 0x0040d160
    uint32_t vt;
    volatile long mnRefCount;             // +0x04
    void AddRef() { _InterlockedIncrement(&mnRefCount); }
    StreamVec_s0046_80c0 mStreams;                   // +0x08
    BatchVec mBatches;                    // +0x1c
    IndexRangeVec mRanges;                // +0x30
    uint32_t pad34[(0x58 - 0x34) / 4];
};
struct MeshGroupRef {
    MeshGroup* p;
    MeshGroupRef(MeshGroup* g) : p(g)
    {
        if (p)
            p->AddRef();
    }
    ~MeshGroupRef();                      // 0x00472520
    MeshGroup* operator->() const { return p; }
};
struct MeshGroupList {                    // RefVector, 0x1c bytes
    MeshGroupList(int n, const MeshGroupRef& r);   // 0x00472990
    ~MeshGroupList();                     // 0x0041eb80
    uint32_t v[7];
};
struct BonePalette : IObject {            // 0x24 bytes
    BonePalette();                        // 0x00472860
    int AddRef();
    int Release();
    StreamDesc GetDesc();                 // 0x004728e0
    uint32_t pad04[2];
    struct Vec : ::Vec<uint32_t, 0> {
        void assign(uint32_t* first, uint32_t* last);   // 0x00475620
    } mBones;                             // +0x0c
    uint32_t pad20;
};
struct PaletteRef {
    BonePalette* p;
    PaletteRef(BonePalette* o);           // 0x0041cc20
    ~PaletteRef();                        // 0x004a9b10
    BonePalette* operator->() const { return p; }
};
struct IJobManager {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void AddJob(cJob** job);      // +0x10
    virtual void v5(); virtual void v6(); virtual void v7();
    virtual void Lock();                  // +0x20
    virtual void Unlock();                // +0x24
};
IJobManager* GetJobManager();             // 0x0068f4d0
struct JobLock {
    IJobManager* p;
    JobLock(IJobManager* m) : p(m) { p->Lock(); }
    ~JobLock() { p->Unlock(); }
};
struct cPropertyManager {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, IObject** dst);   // +0x2c
};
cPropertyManager* PropertyManager();      // 0x0067de30
struct InstanceID {
    uint32_t value;
};
struct ResourceKey_s0046_80c0 {
    InstanceID instanceID;
    uint32_t typeID;
    uint32_t groupID;
    ResourceKey_s0046_80c0() : instanceID(), typeID(0), groupID(0) {}
};
struct TypeIDBits {
    uint32_t lo : 8;
    uint32_t variant : 8;
    uint32_t hi : 14;
    uint32_t kind : 2;
};
inline uint32_t WithVariant(uint32_t typeID, int variant)
{
    ((TypeIDBits*)&typeID)->variant = variant;
    return typeID;
}
inline bool IsKind1(uint32_t typeID) { return ((TypeIDBits*)&typeID)->kind == 1; }
struct TypeID {
    uint32_t value;
    TypeID(uint32_t v) : value(v) {}
    uint32_t Variant() const { return (value >> 8) & 0xff; }
};
void __cdecl LoadPropertyListJob(cJob** job, IObject* propList, MeshGroupList* meshes, uint32_t instanceID,
                                 uint32_t key, uint32_t c8, cJob* after);          // 0x00460d40
bool __cdecl GetModelAsGameMeshes(cJob** job, MeshGroupList* meshes, uint32_t instanceID, uint32_t typeID,
                                  uint32_t c8, int, int, void* out1b4, void* out15c, int,
                                  ResourceKey_s0046_80c0* altKey, cJob* after);               // 0x007573a0
struct SizedSpan {
    int mCount;
    void* mpData;
    SizedSpan(int count, void* data) : mCount(count), mpData(data) {}
};
struct SpanVec : Vec<SizedSpan, 0> {};     // push_back 0x005402c0
struct Holder10 {
    uint32_t pad[0x98 / 4];
    Vec<Elem8c, 0> mElems;                // +0x98
};
class MeshUploadJob {
public:
    bool Run(cJob* pDependency);

    uint32_t pad00[3];
    ModelMesh* mpMesh;                    // +0x0c
    Holder10* mpHolder;                   // +0x10
    Holder10* GetHolder() { return mpHolder; }
    uint32_t pad14[(0xc8 - 0x14) / 4];
    uint32_t mC8;                         // +0xc8
    uint32_t GetC8() const { return mC8; }
    Vector3_s0046_80c0 mOffset;                      // +0xcc
    uint32_t mInstanceID;                 // +0xd8
    uint32_t mTypeID;                     // +0xdc
    uint32_t GetTypeID() const { return mTypeID; }
    JobRef mJob;                          // +0xe0
    cJob* GetJob() const { return mJob.get(); }
    uint8_t* mBytesBegin;                 // +0xe4
    uint8_t* mBytesEnd;                   // +0xe8
    VecU32_s0046_80c0 mPartRanges;                   // +0xec
    uint32_t padfc[(0x124 - 0x100) / 4];
    VecU32_s0046_80c0 mVertexCounts;                 // +0x124 (only begin/end used)
    uint32_t pad138[(0x15c - 0x138) / 4];
    SpanVec mSpans;                       // +0x15c
    uint32_t pad170[(0x1b4 - 0x170) / 4];
    uint32_t mOut1b4;                     // +0x1b4
};
#define ADD_STREAM(VEC, STRIDE, USAGE, IDX, TYPE, SLOT)                                         \
    mAllocator->push_back(StreamIndex(mPositions->size(), -1));                                     \
    mPositions->push_back(StreamElem(USAGE, IDX, TYPE, SLOT, StreamDesc(VEC, mNormals, STRIDE)));
// ---- items of slice s004680c0 end

// ---- items of slice s00469500 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct S45sub {
    // 4-byte subobject constructed by FUN_00401b80(caller this+0x10, arg)
    S45sub(int);
};
struct S45a {
    int a, b, c, d;
    S45sub sub;
    S45a(int, int, int, int, int);
};
struct S45b {
    int a, b, c, d, e;
    S45b* init(int, int, int, int, int);
};
struct M45 {
    char pad[0x14];
    M45& operator=(const M45&);
};
struct S45c {
    M45 m0, m1, m2, m3, m4, m5, m6;
    S45c& operator=(const S45c&);
};
// ---- items of slice s00469500 end

// ---- items of slice s00469bb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const char kBuildTag[];            // 0x015d4034
extern float gMatParam;                   // 0x013eeda0
template <int N> inline void ScratchSlots_s0046_9bb0()
{
    uint32_t s[N];
    (void)s;
}
struct V3 {
    float x, y, z;
    V3(const V3& o) { x = o.x; y = o.y; z = o.z; }
};
struct Vec3i {
    int x, y, z;
};
struct Tail {
    char b[0x3c];
};
struct M18real {
    int a, b;
    Vec3i i8, i14;
    V3 arr[3];
    Tail tail;
};
struct M18 {
    char pad[0x80];
    M18(const M18&);
};
struct B750 {
    virtual void bv();
    uint32_t key[3];              // +8 resource key (instance, type, group)
    char pad[8];
    B750(const B750&);
};
struct T50 {
    char pad[0x14];
    T50(const T50&);
};
struct T31 {
    char pad[0x14];
    T31(const T31&);
};
struct T31b {
    char pad[0x14];
    T31b(const T31b&);
};
struct Mat9 {
    float m[9];
};
struct Vec3f {
    float x, y, z;
};
struct CPart {                    // 0x8c-byte creature part (see 0x00469bb0)
    char pad0[0x2c];
    float scale;                  // +0x2c
    Mat9 rot;                     // +0x30
    Vec3f pos;                    // +0x54
    char pad60[0x8c - 0x60];
};
struct M98 {
    CPart* mpBegin;               // parts vector (begin/end/capacity + allocator)
    CPart* mpEnd;
    char pad[0xc];
    int size() const { return (int)(mpEnd - mpBegin); }
    M98(const M98&);
};
struct S630 : B750 {
    virtual void v();
    M18 m18;
    M98 m98;
    T50 mAc;
    T31 mC0;
    T50 mD4;
    T50 mE8;
    T50 mFc;
    int f110;
    T31b m114;
    S630(const S630&);
};
struct IRefCounted_s0046_9bb0 {
    virtual int AddRef();
    virtual int Release();
};
template <class T>
struct IPtr {
    T* mp;
    IPtr() : mp(0) {}
    IPtr(T* p) : mp(p)
    {
        if (mp)
            ((IRefCounted_s0046_9bb0*)mp)->AddRef();
    }
    ~IPtr()
    {
        if (mp)
            ((IRefCounted_s0046_9bb0*)mp)->Release();
    }
    IPtr& operator=(T* p)
    {
        if (p != mp) {
            T* old = mp;
            if (p)
                ((IRefCounted_s0046_9bb0*)p)->AddRef();
            mp = p;
            if (old)
                ((IRefCounted_s0046_9bb0*)old)->Release();
        }
        return *this;
    }
    T* get() const { return mp; }
    T* operator->() const { return mp; }
    operator T*() const { return mp; }
};
struct EBuildObj : IRefCounted_s0046_9bb0 {          // 0x004610c0, 0xb0 bytes
    char pad4[0xac - 4];
    uint32_t mId;                         // +0xac
    EBuildObj();
};
struct EBuildObj2 : IRefCounted_s0046_9bb0 {         // 0x0046a510, 0xb0 bytes (built from the first object)
    char pad4[0xac];
    EBuildObj2(EBuildObj* src);
};
bool PrepareBuild(void* ed, EBuildObj* obj);                         // 0x0046de70 (cdecl)
void MakeBabyRuntimeCreature(S630* c);                               // 0x0046a8a0 (cdecl)
struct ThreadedObj {                      // 0x1c bytes, ctor 0x0077d1d0, refcount at +4
    char pad0[4];
    volatile long mnRefCount;
    char pad8[0x1c - 8];
    ThreadedObj();
    void AddRef() { _InterlockedIncrement(&mnRefCount); }
    void Release();                       // 0x00404f90 (Resource::ThreadedObject::Release)
};
struct ThreadedPtr {
    ThreadedObj* mp;
    ThreadedPtr(ThreadedObj* p) : mp(p)
    {
        if (mp)
            mp->AddRef();
    }
    ~ThreadedPtr()
    {
        if (mp)
            mp->Release();
    }
    ThreadedObj* get() const { return mp; }
};
struct JobSlotB8 {
    void Set(ThreadedObj* j);             // 0x0041d8b0
};
struct AtomicObj {
    void Release();                       // 0x00402420 (AtomicRefCounted::Release)
};
struct AtomicPtr {
    AtomicObj* mp;
    AtomicPtr() : mp(0) {}
    ~AtomicPtr()
    {
        if (mp)
            mp->Release();
    }
    AtomicObj** Reset();                  // 0x00472b00
    AtomicObj** operator&() { return Reset(); }
    AtomicObj* get() const { return mp; }
    operator AtomicObj*() const { return mp; }
};
struct CJob {                             // job object (secondary base, this-8 is the owner)
    void Flush();                         // 0x006909b0
    int Release();                        // 0x00690120
};
struct JobPtr {
    CJob* mp;
    JobPtr() : mp(0) {}
    CJob** Reset();                       // 0x0041d940
    CJob** operator&() { return Reset(); }
    CJob* get() const { return mp; }
};
struct EdCtx {
    char pad0[8];
    S630* mpCreature;                     // +8 source creature
    S630* Creature() { return mpCreature; }
    char padc[0xb8 - 0xc];
    JobSlotB8 jobSlot;                    // +0xb8
};
struct KeyArg {
    uint32_t instance;                    // +0
    uint32_t id;                          // +4
    uint32_t flags;                       // +8
};
union KeyBits {
    uint32_t raw;
    struct {
        uint32_t lo : 16;
        uint32_t kind : 8;                // 0x62 = baby-capable
        uint32_t cls : 5;
        uint32_t hi : 3;
    } f;
};
inline uint32_t KindOf(uint32_t v)
{
    KeyBits k;
    k.raw = v;
    return k.f.kind;
}
inline uint32_t WithClass(uint32_t v, uint32_t c)
{
    KeyBits k;
    k.raw = v;
    k.f.cls = c;
    return k.raw;
}
struct XformVec {                         // inline-storage vector of 0x38-byte cSPTransform (0xe18 bytes)
    char* mpBegin;
    char buf[0xe18 - 4];
    struct Tag {};
    XformVec(const Tag&);                 // 0x00540470
    void Init();                          // 0x00472b40
    void resize(int n);                   // 0x0041e3b0
    void Free();                          // 0x0041e090
};
struct XformTmp {                         // 0x38-byte transform builder (BBoxTransform)
    uint16_t flags;
    uint16_t count;
    Vec3f pos;
    float scale;
    Mat9 rot;
    XformTmp();                           // 0x00409930
    void Invert();                        // 0x0040efa0
    void ScaleBy(float s);                // 0x00409b30
    void ApplyRot(const Mat9* m);         // 0x006ba870
    void SetScale(float s)
    {
        scale = s;
        count++;
    }
    void SetRotation(const Mat9& m)
    {
        rot = m;
        flags |= 2;
        count++;
    }
    void SetPosition(const Vec3f& p)
    {
        pos = p;
        flags |= 4;
        count++;
    }
    void MarkPos()
    {
        flags |= 4;
        count++;
    }
    void Assign(void* dst);               // 0x00537dc0 (cSPTransform::operator=, on dst)
};
void AddPos(Vec3f* a, const Vec3f* b);    // 0x0041ddb0 (cdecl)
void RegisterModels(uint32_t instance, uint32_t flags, AtomicObj** a, AtomicObj** b, void* c);   // 0x004615e0 (cdecl)
void BuildMaterialInfo(ThreadedObj* job, uint32_t id, AtomicObj* a, AtomicObj* b, float f, char c);   // 0x004604f0 (cdecl)
void BuildModel(uint32_t instance, uint32_t flags, void* a, void* b, int p5, ThreadedObj* job, const void* tag,
                int mode, void* xforms, CJob** outJob, CJob* inJob);                                  // 0x00467a20 (cdecl)
// ---- items of slice s00469bb0 end

// ---- items of slice s0046aac0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Tag {
    Tag() {}
};
struct IObject_s0046_aac0 {
    virtual int AddRef();
    virtual int Release();
};
struct Vector3_s0046_aac0 {
    float x, y, z;
    Vector3_s0046_aac0() {}
    Vector3_s0046_aac0(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
};
struct Matrix3_s0046_aac0 {
    float m[9];
};
struct ResKey {
    uint32_t a, b, c;
};
struct Variant {
    char data[0x10];
    uint16_t mFlags;
    uint16_t mTypeId;
    Variant() : mFlags(0), mTypeId(0) {}
    void SetVec12(const ResKey* k);       // 0x00422f40
    void SetChar(const bool* v);          // 0x00422e20
    void Destruct(int);                   // 0x0093db80 (EA::Variant::Destruct)
    Variant(const ResKey& k) : mFlags(0), mTypeId(0)
    {
        mTypeId = 0x20;
        mFlags = 2;
        SetVec12(&k);
    }
    Variant(const bool& v) : mFlags(0), mTypeId(0)
    {
        mTypeId = 1;
        mFlags = 2;
        SetChar(&v);
    }
    ~Variant()
    {
        if (mFlags & 4)
            Destruct(0);
    }
};
struct IPropertyList : IObject_s0046_aac0 {
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void SetProperty(unsigned id, const Variant& v);   // slot 5
};
struct Model_s0046_aac0;
struct IModelOwner {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual Model_s0046_aac0* CreateModel(uint32_t a, uint32_t b, int mode);                        // slot 3
#define P4(n) virtual void p##n##a(); virtual void p##n##b(); virtual void p##n##c(); virtual void p##n##d();
    P4(0) P4(1) P4(2) P4(3) P4(4) P4(5) P4(6) P4(7) P4(8) P4(9) P4(10) P4(11) P4(12) P4(13) P4(14)
    virtual void s64();
    virtual int LoadModel(Model_s0046_aac0* m, IObject_s0046_aac0** outList, ResKey* key);                     // slot 65
};
struct SPTransform {
    char data[0x38];
    SPTransform& operator=(const SPTransform&);   // 0x00537dc0 (cSPTransform::operator=)
};
struct Model_s0046_aac0 {
    IModelOwner* pOwner;              // +0
    char pad4[4];
    SPTransform transform;            // +8
    int mnRefCount;                   // +0x40 (SPTransform ends at 0x40)
    struct Extra { uint32_t a, b; } extra;   // +0x44, +0x48
    char pad4c[0x90 - 0x4c];
    IObject_s0046_aac0* pParent;                 // +0x90
    IObject_s0046_aac0* GetParent() { return pParent; }
    void AddRef() { mnRefCount++; }
    void Release();                   // 0x0040f360 (Counted::Release)
};
template <class T>
struct AutoRef {
    T* mp;
    AutoRef() : mp(0) {}
    AutoRef(T* p) : mp(p) { if (mp) mp->AddRef(); }
    AutoRef(const AutoRef& o) : mp(o.mp) { if (mp) mp->AddRef(); }
    ~AutoRef() { if (mp) mp->Release(); }
    AutoRef& operator=(T* p)
    {
        if (p != mp) {
            T* old = mp;
            if (p)
                p->AddRef();
            mp = p;
            if (old)
                old->Release();
        }
        return *this;
    }
    T* operator->() const { return mp; }
    T* get() const { return mp; }
    AutoRef& operator=(const AutoRef& o) { return operator=(o.mp); }
    operator T*() const { return mp; }
};
struct cPropertyList : IPropertyList {
    char pad[0x38 - 4];
    cPropertyList();                           // 0x006a1c40 (Editor::cPropertyList::cPropertyList)
    void SetParent(IObject_s0046_aac0* parent);           // 0x006a1710 (SP::cPropertyList::SetParent)
};
struct IPropertyManager {
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3();
    virtual void m4(); virtual void m5(); virtual void m6(); virtual void m7();
    virtual void m8(); virtual void m9(); virtual void m10();
    virtual void LoadProperties(uint32_t a, uint32_t c, IObject_s0046_aac0** outList);   // slot 11 (0x2c)
    virtual void m12();
    virtual void RegisterList(IPropertyList* list, uint32_t a, uint32_t c);   // slot 13 (0x34)
};
IPropertyManager* PropertyManager_s0046_aac0();           // 0x0067de30 (SP::PropertyManager)
struct Block {
    char pad0[0x10];
    Model_s0046_aac0* pModel;                    // +0x10
    char pad14[0x33c - 0x14];
    Block* pParent;                   // +0x33c
    char pad340[0xdc8 - 0x340];
    uint32_t flags[2];                // +0xdc8
    void GetBBox(struct BBox* out, int a, int b, int c);   // 0x0044ae00 (SP::cSPEditorBlock::GetBBox)
    Block* GetParent() const { return pParent; }
    bool IsSet(unsigned bit) const
    {
        uint32_t w;
        bool r;
        if (bit < 0x3c) {
            w = flags[bit >> 5];
            r = (w & (1u << (bit % 32))) != 0;
        } else {
            r = false;
        }
        return r;
    }
};
struct IHolder {
    IObject_s0046_aac0* p;
    IHolder() : p(0) {}
    ~IHolder() { if (p) p->Release(); }
    IHolder& Reset();                 // 0x0041d870
    operator IObject_s0046_aac0**() { return &p; }
};
struct ModelVec_s0046_aac0 {
    AutoRef<Model_s0046_aac0>* mpBegin;
    AutoRef<Model_s0046_aac0>* mpEnd;
    int size() const { return mpEnd - mpBegin; }
    AutoRef<Model_s0046_aac0>& operator[](int i) { return mpBegin[i]; }
};
struct ModelListObj {
    char pad0[0xc];
    ModelVec_s0046_aac0 models;
};
void BuildKeyHelper(ResKey* key, IObject_s0046_aac0* holder);   // 0x006acfe0
struct BBox {
    float v[6];
    void TransformBy(const struct BBoxTransform* t);   // 0x00409dd0
};
struct BBoxTransform {
    uint16_t flags;
    uint16_t count;
    Vector3_s0046_aac0 pos;
    float scale;
    Matrix3_s0046_aac0 rot;
    BBoxTransform();                  // 0x00409930
    void SetScale(float s) { scale = s; count++; }
    void SetRotation(const Matrix3_s0046_aac0& m) { rot = m; flags |= 2; count++; }
    void SetPosition(const Vector3_s0046_aac0& p) { pos = p; flags |= 4; count++; }
};
struct BBoxVec {
    char buf[1560];
    BBoxVec(const Tag&);              // 0x00540470
    void Init();                      // 0x0041da70
    void reserve(int n);              // 0x0041e770
    void push_back(const BBox& b);    // 0x0041e8b0
    ~BBoxVec();                       // 0x0041e730
};
struct CreaturePart {
    char pad0[0x2c];
    float scale;                      // +0x2c
    Matrix3_s0046_aac0 rot;                      // +0x30
    Vector3_s0046_aac0 pos;                      // +0x54
    char pad60[0x8c - 0x60];
};
struct PartVec {
    CreaturePart* mpBegin;
    CreaturePart* mpEnd;
};
struct Creature : IObject_s0046_aac0 {
    Creature(void* ctx);              // 0x0046a630
    char pad4[4];
    Vector3_s0046_aac0 pos;                      // +8
    char pad14[0x98 - 0x14];
    PartVec parts;                    // +0x98
    char padA0[0x128 - 0xa0];
};
struct AssetView;
struct EditorCtx {
    char pad0[0x18];
    AssetView* pAssetView;            // +0x18
};
struct ThreadedObject {
    ThreadedObject();                 // 0x0077d1d0
    char pad0[4];
    volatile long mnRefCount;         // +4
    void AddRef() { _InterlockedIncrement(&mnRefCount); }
    void Release();                   // 0x00404f90 (Resource::ThreadedObject::Release)
};
struct JobRef_s0046_aac0 {
    ThreadedObject* mp;
    JobRef_s0046_aac0() : mp(0) {}
    ~JobRef_s0046_aac0();                        // 0x00472520
    JobRef_s0046_aac0& operator=(ThreadedObject* p)
    {
        if (p != mp) {
            ThreadedObject* old = mp;
            if (p)
                p->AddRef();
            mp = p;
            if (old)
                old->Release();
        }
        return *this;
    }
};
struct BuildObject : IObject_s0046_aac0 {
    BuildObject();                    // 0x004610c0
    char pad4[0xac - 4];
    uint32_t mId;                     // +0xac
};
struct BuildRef {
    BuildObject* mp;
    BuildRef() : mp(0) {}
    ~BuildRef();                      // 0x004a9b10
};
struct Editor {
    char pad0[8];
    EditorCtx* ctx;                   // +8
    char padc[0xc0 - 0xc];
    Block** blocks;                   // +0xc0
};
struct JobSlot {
    void Set(ThreadedObject* j);      // 0x0041d8b0
};
struct IModelHost {
    virtual void h0(); virtual void h1(); virtual void h2();
    virtual Model_s0046_aac0* GetModel(uint32_t a, uint32_t c, int flags);                   // slot 3
};
struct ICreator {
#define Q4(n) virtual void q##n##a(); virtual void q##n##b(); virtual void q##n##c(); virtual void q##n##d();
    Q4(0) Q4(1) Q4(2) Q4(3) Q4(4) Q4(5)
    virtual IModelHost* GetHost();                                                // slot 24 (0x60)
};
ICreator* GetCreator();                                                           // 0x00401010
struct IIdGenerator {
    virtual void i0();
    virtual void Generate(ResKey* key, uint32_t type, int a, int b, int c, int d);   // slot 1
};
IIdGenerator* IDGenerator();                                                      // 0x0067de60
struct IModelNotify {
    virtual void n0();
#define N4(n) virtual void vn##n##a(); virtual void vn##n##b(); virtual void vn##n##c(); virtual void vn##n##d();
    N4(1) N4(2) N4(3) N4(4) N4(5) N4(6) N4(7) N4(8) N4(9) N4(10) N4(11) N4(12) N4(13) N4(14) N4(15)
    N4(16) N4(17) N4(18) N4(19) N4(20) N4(21) N4(22)
    virtual void v89(); virtual void v90();
    virtual void Notify(Model_s0046_aac0* m, int flag);                                    // slot 91 (0x16c)
};
struct CreatureRef {
    Creature* mp;
    Creature* operator->() const { return mp; }
    operator Creature*() const { return mp; }
};
struct MakeOutput {
    CreatureRef creature;             // +0
    Model_s0046_aac0* model;                     // +4
    JobSlot job;                      // +8 (empty, member functions only)
    char pad9[3];
    Model_s0046_aac0** modelsBegin;              // +0xc
    char pad10[0x20 - 0x10];
    char refVec[1];                   // +0x20
    char pad21[0x34 - 0x21];
    bool bIsVerbCollection;           // +0x34
};
void MakeBabyRuntimeCreature(Creature* c);                                         // 0x0046a8a0
void GetTranslationOffset(Vector3_s0046_aac0* out, BBoxVec* boxes, int unused, Creature* c);  // 0x0046c000
unsigned InitVerbCollection(AssetView* v);                                         // 0x004bb860
void PartPosAdd(Vector3_s0046_aac0* p, const Vector3_s0046_aac0* d);                                     // 0x0041ddb0
bool PrepareBuild(Editor* ed, BuildObject* obj);                                   // 0x0046de70
void LoadKeyDefault(uint32_t a, uint32_t c, int z);                                // 0x00469920
void BuildModelResource(uint32_t a, uint32_t c, EditorCtx* ctx, BuildObject* obj, int z0, ThreadedObject* job,
                        Vector3_s0046_aac0* off, int a1, int a2, int a3, int a4);             // 0x00467a20
void ReserveModels(void* vec, int n);                                              // 0x00473270 (thiscall)
void ResizeRefVec(void* vec, int n);                                               // 0x0041ee90 (thiscall)
// ---- items of slice s0046aac0 end

// ---- items of slice s0046b8e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double __cdecl fabs(double);
extern const float kFltMax;                                              // 0x013eec70
extern const float kZero;                                                // 0x01485378
extern const float kOne;                                                 // 0x01485720
#pragma intrinsic(fabs)
inline float Fabs(float x) { return (float)fabs(x); }
inline float Abs(float x) { return Fabs(x); }
struct Vector3T {                                                        // rw::math::fpu::Vector3Template<float,0>
    float x, y, z;
    float& operator[](int i) { return (&x)[i]; }
};
struct cSPVector3_s0046_b8e0 : Vector3T {
    cSPVector3_s0046_b8e0() {}
    cSPVector3_s0046_b8e0(const Vector3T& v) { x = v.x; y = v.y; z = v.z; }
    cSPVector3_s0046_b8e0(const cSPVector3_s0046_b8e0& o);                                     // 0x004098a0
};
struct cSPBoundingBox_s0046_b8e0 {
    cSPVector3_s0046_b8e0 mMin;
    cSPVector3_s0046_b8e0 mMax;
    Vector3T* GetCenter(Vector3T* out) const;                            // 0x00409b90 (thiscall, returns out)
};
Vector3T* Vector3_Add(Vector3T* a, const Vector3T* b);                   // 0x0041ddb0 (a += b)
Vector3T* Vector3_Negate(Vector3T* out, const Vector3T* v);              // 0x00422020
Vector3T* Vector3_Div(Vector3T* out, const Vector3T* v, const float* s); // 0x00453880
Vector3T* Vector3_Scale(Vector3T* out, const Vector3T* a, const float* s); // 0x0041dca0
extern const cSPVector3_s0046_b8e0 kZeroPos;                                        // 0x015d4034
template <unsigned N>
struct bitset {
    uint32_t mWord[(N + 31) / 32];
    bool test(unsigned i) const
    {
        uint32_t w;
        bool r;
        if (i < N) {
            w = mWord[i >> 5];
            r = (w & (1u << (i % 32))) != 0;
        } else {
            r = false;
        }
        return r;
    }
};
struct cSPEditorBlock {
    char pad0[0x48];
    cSPVector3_s0046_b8e0 mPosition;                                                // +0x48
    char pad54[0xdc8 - 0x54];
    bitset<60> mFlags;                                                   // +0xdc8
    cSPBoundingBox_s0046_b8e0 GetBBox(int type, bool a, bool b);                    // 0x0044ae00
};
bool BlockOrAncestorHasFlag(cSPEditorBlock* b);                          // 0x0046b7b0 (cdecl)
struct cSPEditorModel {
    char pad0[0x18];
    cSPEditorBlock** mpBegin;                                            // +0x18
    cSPEditorBlock** mpEnd;
    int GetCount();                                                      // 0x004accf0
    cSPEditorBlock* GetBlock(int i);                                     // 0x004accb0
};
struct Tbfd {
    int m();
};
// ---- items of slice s0046b8e0 end

// ---- items of slice s0046c000 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const uint32_t kPropGroup;                                    // 0x015d3eb4
inline float Abs_s0046_c000(float x) { return (float)fabs(x); }
struct Vec3Data {
    float x, y, z;
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};
struct Vector3_s0046_c000 : Vec3Data {
    Vector3_s0046_c000() {}
    Vector3_s0046_c000(const Vec3Data& o) { x = o.x; y = o.y; z = o.z; }
    Vector3_s0046_c000(const Vector3_s0046_c000& o) { x = o.x; y = o.y; z = o.z; }
};
struct Vector3Copyable : Vec3Data {
    Vector3Copyable() {}
    Vector3Copyable(const Vector3Copyable& o);   // 0x004098a0
    Vector3Copyable(const Vec3Data& o) { x = o.x; y = o.y; z = o.z; }
};
Vec3Data& operator+=(Vec3Data& a, const Vec3Data& b);                // 0x0041ddb0
Vector3_s0046_c000 operator-(const Vec3Data& v);                                // 0x00422020
Vector3_s0046_c000 operator/(const Vec3Data& v, const float& s);                // 0x00453880
Vector3_s0046_c000 operator*(const Vec3Data& a, const float& s);                // 0x0041dca0
extern const Vector3Copyable kZeroPos_s0046_c000;                               // 0x015d4034
struct BoundingBox {
    Vector3Copyable min;
    Vector3Copyable max;
    BoundingBox(const BoundingBox& o) : min(o.min), max(o.max) {}
    Vector3_s0046_c000& GetCenter(Vector3_s0046_c000& out) const;                          // 0x00409b90
};
struct Property_s0046_c000 {
    bool* GetBool();                                                 // 0x0041e920
    uint32_t* GetUInt();                                             // 0x0041ea00
    char pad[0x12];
    uint16_t type;                                                   // +0x12
};
struct PropertyList {
    virtual int AddRef();                                            // +0x00
    virtual int Release();                                           // +0x04
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
    virtual bool HasProperty(uint32_t id);                           // +0x1c
    virtual void v8();
    virtual bool GetProperty(uint32_t id, Property_s0046_c000** out);           // +0x24
};
template <class T>
struct AutoRefCount_s0046_c000 {
    T* mp;
    AutoRefCount_s0046_c000() : mp(0) {}
    ~AutoRefCount_s0046_c000() { if (mp) mp->Release(); }
    T** AsPPVoidParam();                                             // 0x0041d870
    T* operator->() const { return mp; }
    operator T*() const { return mp; }
};
struct PropertyManager_ {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10();
    virtual void GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyList** out);  // +0x2c
};
PropertyManager_* PropertyManager_s0046_c000();                                 // 0x0067de30
bool GetBoolProperty(PropertyList* list, uint32_t id, bool* out);    // 0x00407190
uint32_t RemapTypeId(uint32_t id);                                   // 0x00432f10
inline void GetUIntProp(PropertyList* l, uint32_t id, uint32_t& out) {
    Property_s0046_c000* p;
    if (l && l->GetProperty(id, &p) && p->type == 10) out = *p->GetUInt();
}
inline void GetBoolProp(PropertyList* l, uint32_t id, bool& out) {
    Property_s0046_c000* p;
    if (l && l->GetProperty(id, &p) && p->type == 1) out = *p->GetBool();
}
struct ResKey_s0046_c000 { uint32_t instanceID, typeID, groupID; };
struct ModelPart {                    // 0x1d8 bytes
    uint32_t groupID;                 // +0
    uint32_t instanceID;              // +4
    char pad8[0xc];
    Vector3Copyable pos;              // +0x14
    char pad20[0x1d8 - 0x20];
};
struct CreaturePart_s0046_c000 {                 // 0x8c bytes
    char pad0[0x54];
    Vector3Copyable pos;              // +0x54
    char pad60[0x84 - 0x60];
    uint32_t groupID;                 // +0x84
    uint32_t instanceID;              // +0x88
};
template <class T>
struct PartVec_s0046_c000 {
    T* mpBegin;
    T* mpEnd;
    int size() const { return (int)(mpEnd - mpBegin); }
};
struct EditorModel_s0046_c000 {
    char pad0[0x18];
    uint32_t typeID;                  // +0x18
    char pad1c[0x98 - 0x1c];
    PartVec_s0046_c000<ModelPart> parts;         // +0x98
};
struct Creature_s0046_c000 {
    char pad0[0x18];
    uint32_t typeID;                  // +0x18
    char pad1c[0x98 - 0x1c];
    PartVec_s0046_c000<CreaturePart_s0046_c000> parts;      // +0x98
};
struct BoxVec {
    BoundingBox* mpBegin;
};
// ---- items of slice s0046c000 end

// ---- items of slice s0046c900 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern wchar_t gEmptyString16;                                 // 0x01667bac
struct Vec3f_s0046_c900 {
    float x, y, z;
    Vec3f_s0046_c900(const Vec3f_s0046_c900& o) : x(o.x), y(o.y), z(o.z) {}
};
struct Vector3_s0046_c900 {
    float x, y, z;
    Vector3_s0046_c900(const Vector3_s0046_c900& o) : x(o.x), y(o.y), z(o.z) {}
    Vector3_s0046_c900(const Vec3f_s0046_c900& o) : x(o.x), y(o.y), z(o.z) {}
    Vector3_s0046_c900& operator=(const Vec3f_s0046_c900& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
struct Quaternion { float x, y, z, w; };
struct QuatResult : Quaternion {
    QuatResult(const Quaternion& o) { x = o.x; y = o.y; z = o.z; w = o.w; }
};
struct Matrix33 { float m[9]; };
namespace rw {
namespace math {
namespace fpu {
    Quaternion& QuaternionFromMatrix33(Quaternion& out, const Matrix33& m, float tolerance);   // 0x00472b80
}
}
}
Vec3f_s0046_c900 operator+(const Vector3_s0046_c900& a, const Vector3_s0046_c900& b);           // 0x0041dc10
Vec3f_s0046_c900 operator*(const float& s, const Vec3f_s0046_c900& v);               // 0x0041de40
Vec3f_s0046_c900 RotateVector(const Vector3_s0046_c900& v, const Vector3_s0046_c900& frame);     // 0x0041dca0
extern const Vector3_s0046_c900 kZeroVector;                              // 0x015d4034
void operator delete[](void* p);
struct allocator {
    void deallocate(void* p, uint32_t) { delete[] (char*)p; }
};
struct string16 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    allocator mAllocator;

    string16() : mpBegin(0), mpEnd(0), mpCapacity(0) { AllocateSelf(); }
    ~string16() { DeallocateSelf(); }
    void AllocateSelf() { mpBegin = &gEmptyString16; mpEnd = mpBegin; mpCapacity = mpBegin + 1; }
    // 0x004237d0 (cl declines to inline it here)
    void DeallocateSelf()
    {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
    }
    void DoFree(wchar_t* p, uint32_t n)
    {
        if (p)
            mAllocator.deallocate(p, n * sizeof(wchar_t));
    }
    void reserve(uint32_t n);                                  // 0x0042e610
    string16& assign(const wchar_t* pBegin, const wchar_t* pEnd);  // 0x00423650
    string16& assign(const wchar_t* p) { return assign(p, p + CharStrlen(p)); }
    const wchar_t* c_str() const { return mpBegin; }
    static uint32_t CharStrlen(const wchar_t* pString)
    {
        const wchar_t* pCurrent = pString;
        while (*pCurrent)
            ++pCurrent;
        return (uint32_t)(pCurrent - pString);
    }
};
namespace EA {
namespace StdC {
    wchar_t* Strncpy(wchar_t* pDest, const wchar_t* pSource, uint32_t n);   // 0x0092cb90
}
}
int Snprintf8(char* pBuffer, uint32_t n, const char* pFormat, ...);       // 0x009384e0
template <int N> struct Bitset {
    uint32_t mWord[(N + 31) / 32];
    uint32_t GetWord(uint32_t i) const { return mWord[i >> 5]; }
    bool test(uint32_t i) const
    {
        if (i < N)
            return (GetWord(i) & (1 << (i % 32))) != 0;
        return false;
    }
};
struct SkinBone {                       // 0x8c bytes
    int16_t mBlockIndex;                // +0x00
    int16_t mNodeIndex;                 // +0x02
    int16_t mParent;                    // +0x04
    int16_t mSymmetric;                 // +0x06
    uint16_t mFlags;                    // +0x08
    uint8_t mPartIndex;                 // +0x0a
    uint8_t mType;                      // +0x0b
    uint32_t pad0c[2];
    Vector3_s0046_c900 mStart;                     // +0x14
    Vector3_s0046_c900 mEnd;                       // +0x20
    Vector3_s0046_c900 mFrame;                     // +0x2c (its x is also exported as a float)
    uint32_t pad38[(0x60 - 0x38) / 4];
    Vector3_s0046_c900 mOffset;                    // +0x60
    float mRadius;                      // +0x6c
    uint32_t pad70[(0x8c - 0x70) / 4];
};
struct SkinBoneVector {
    SkinBone* mpBegin;
    SkinBone* mpEnd;
    int size() const { return (int)(mpEnd - mpBegin); }
};
struct SkinData {
    uint32_t pad0[0x98 / 4];
    SkinBoneVector mBones;              // +0x98
};
struct ResourceKey_s0046_c900 { uint32_t instance, type, group; };
struct BlockResource { uint32_t pad0[2]; ResourceKey_s0046_c900 mKey; };   // key at +0x08
class cMWModel;
class cModelWorld {
public:
    virtual void v000(); virtual void v004(); virtual void v008(); virtual void v00c();
    virtual void v010(); virtual void v014(); virtual void v018(); virtual void v01c();
    virtual void v020(); virtual void v024(); virtual void v028(); virtual void v02c();
    virtual void v030(); virtual void v034(); virtual void v038(); virtual void v03c();
    virtual void v040(); virtual void v044(); virtual void v048(); virtual void v04c();
    virtual void v050(); virtual void v054(); virtual void v058(); virtual void v05c();
    virtual void v060(); virtual void v064(); virtual void v068(); virtual void v06c();
    virtual void v070(); virtual void v074(); virtual void v078(); virtual void v07c();
    virtual void v080(); virtual void v084(); virtual void v088(); virtual void v08c();
    virtual void v090(); virtual void v094(); virtual void v098(); virtual void v09c();
    virtual void v0a0(); virtual void v0a4(); virtual void v0a8(); virtual void v0ac();
    virtual void v0b0(); virtual void v0b4(); virtual void v0b8(); virtual void v0bc();
    virtual void v0c0(); virtual void v0c4(); virtual void v0c8(); virtual void v0cc();
    virtual void v0d0(); virtual void v0d4(); virtual void v0d8(); virtual void v0dc();
    virtual void v0e0(); virtual void v0e4(); virtual void v0e8(); virtual void v0ec();
    virtual void v0f0(); virtual void v0f4(); virtual void v0f8(); virtual void v0fc();
    virtual void v100(); virtual void v104(); virtual void v108(); virtual void v10c();
    virtual void v110(); virtual void v114(); virtual void v118(); virtual void v11c();
    virtual void v120(); virtual void v124(); virtual void v128(); virtual void v12c();
    virtual void v130(); virtual void v134(); virtual void v138(); virtual void v13c();
    virtual void v140(); virtual void v144(); virtual void v148(); virtual void v14c();
    virtual void v150(); virtual void v154(); virtual void v158(); virtual void v15c();
    virtual void v160(); virtual void v164(); virtual void v168(); virtual void v16c();
    virtual void ReleaseModel(cMWModel* pModel, bool flag);     // +0x170
};
class cMWModel {
public:
    int AddRef() { return ++mnRefCount; }
    int Release()
    {
        if (mnRefCount > 1)
            return --mnRefCount;
        mpWorld->ReleaseModel(this, mFlags.test(31));
        return 0;
    }
    cModelWorld* mpWorld;               // +0x00
    Bitset<32> mFlags;                  // +0x04
    uint32_t pad08[(0x40 - 0x08) / 4];
    int mnRefCount;                     // +0x40
};
namespace EA {
template <class T> class AutoRefCount_s0046_c900 {
public:
    T* mpObject;
    ~AutoRefCount_s0046_c900()
    {
        if (mpObject)
            mpObject->Release();
    }
    AutoRefCount_s0046_c900& operator=(T* pObject)
    {
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
struct BlockAttachment {                // 0x14 bytes
    uint32_t mPart;
    uint32_t pad04[2];
    uint32_t mSlot;                     // +0x0c
    uint32_t pad10;
    uint32_t GetPart() const { return mPart; }
    uint32_t GetSlot() const { return mSlot; }
};
struct BlockAttachmentVector {
    BlockAttachment* mpBegin;
    BlockAttachment* mpEnd;
    int size() const { return (int)(mpEnd - mpBegin); }
};
struct PartModel {
    uint32_t pad0[0x8c / 4];
    uint32_t mModelID;                  // +0x8c
    uint32_t pad90[(0x180 - 0x90) / 4];
    float mScale;                       // +0x180
};
class cBlock {
public:
    int GetPartModelCount();                    // 0x0043c040
    PartModel* GetPartModel(int index);         // 0x0043c270
    uint32_t GetPropertyValue(uint32_t id);     // 0x00435c20

    BlockResource* GetResource() { return mpResource; }
    cMWModel* GetModel() { return mpModel.mpObject; }
    uint32_t GetModelIDA() { return mIDA; }
    uint32_t GetModelIDB() { return mIDB; }
    cBlock* GetParent() { return mpParent; }

    uint32_t pad0[3];
    BlockResource* mpResource;          // +0x0c
    EA::AutoRefCount_s0046_c900<cMWModel> mpModel; // +0x10
    uint32_t pad14[2];
    uint32_t mIDA;                      // +0x1c
    uint32_t mIDB;                      // +0x20
    uint32_t pad24[(0x48 - 0x24) / 4];
    Vector3_s0046_c900 mPosition;                  // +0x48
    uint32_t pad54[(0x60 - 0x54) / 4];
    Matrix33 mOrientation;              // +0x60
    uint32_t pad84[(0x33c - 0x84) / 4];
    cBlock* mpParent;                   // +0x33c
    uint32_t pad340[(0xc0c - 0x340) / 4];
    BlockAttachmentVector mAttachments; // +0xc0c
    uint32_t padc14[(0xdb4 - 0xc14) / 4];
    uint32_t mPropertyA;                // +0xdb4
    uint32_t mPropertyB;                // +0xdb8
    uint32_t mPropertyC;                // +0xdbc
    uint32_t paddc0[2];
    Bitset<60> mFlags;                  // +0xdc8
};
inline QuatResult GetBlockRotation(const Matrix33& m)
{
    Quaternion q;
    return QuatResult(rw::math::fpu::QuaternionFromMatrix33(q, m, 0.0f));
}
uint32_t GetPartID(uint32_t part);                  // 0x00461520
struct cSkin {
    SkinData* GetSkinData() { return mpSkinData; }
    uint32_t pad0[2];
    SkinData* mpSkinData;               // +0x08
    uint32_t pad0c[(0xc0 - 0x0c) / 4];
    cBlock** mpBlocks;                  // +0xc0
};
struct IntVector {
    int* mpBegin;
    int* mpEnd;
    int& operator[](int i) { return mpBegin[i]; }
    int size() const { return (int)(mpEnd - mpBegin); }
};
struct HelperNodeGroup {                // 0x48 bytes
    uint32_t pad0[3];
    IntVector mBlocks;                  // +0x0c
    uint32_t pad14[(0x44 - 0x14) / 4];
    int mNode;                          // +0x44
};
struct HelperBone {                     // 0x54 bytes
    uint32_t pad0[0x38 / 4];
    Vector3_s0046_c900 mPosition;                  // +0x38
    bool mbConnected;                   // +0x44
    uint8_t pad45[3];
    uint32_t pad48[3];
};
struct HelperNode {                     // 0xd8 bytes
    uint32_t pad0[2];
    int mBone;                          // +0x08
    int mType;                          // +0x0c
    uint32_t pad10[(0xd8 - 0x10) / 4];
};
struct SkeletonHelper {
    HelperNodeGroup& GetGroup(int i) { return mpGroups[i]; }
    uint32_t pad0[4];
    HelperNodeGroup* mpGroups;          // +0x10
    uint32_t pad14[4];
    HelperBone* mpBones;                // +0x24
    uint32_t pad28[4];
    int mRootGroup;                     // +0x38
    uint32_t pad3c[6];
    HelperNode* mpNodes;                // +0x54
};
Vec3f_s0046_c900 TransformToGroup(const HelperNodeGroup& group, const Vector3_s0046_c900& pos);   // 0x0041db10
struct ExportPart { uint32_t mPart; uint32_t mSlot; };
struct ExportPartModel { uint32_t mModelID; float mScale; };
class IExportMesh {
public:
    virtual void AddRef();
    virtual void Release();
};
class IExportFactory {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual IExportMesh* CreateMesh();          // +0x60
};
IExportFactory* GetExportFactory();             // 0x00401010
template <class T> struct MeshPtr {
    T* mpObject;
    T* get() const { return mpObject; }
    MeshPtr& operator=(T* pObject)
    {
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
struct ExportJoint {                    // 0x29c bytes
    ExportJoint();                      // 0x00475880
    int mVersion;                       // +0x000
    wchar_t mFileName[0x50];            // +0x004
    char mJointName[0x28];              // +0x0a4
    uint32_t mModelIDB;                 // +0x0cc
    uint32_t mModelIDA;                 // +0x0d0
    int mBlockIndex;                    // +0x0d4
    int mParent;                        // +0x0d8
    int mSymmetric;                     // +0x0dc
    Vector3_s0046_c900 mCenter;                    // +0x0e0
    int mPartIndex;                     // +0x0ec
    Vector3_s0046_c900 mBonePosition;              // +0x0f0
    Vector3_s0046_c900 mOffset;                    // +0x0fc
    Vector3_s0046_c900 mPosition;                  // +0x108
    Quaternion mOrientation;            // +0x114
    Vector3_s0046_c900 mStart;                     // +0x124
    Vector3_s0046_c900 mEnd;                       // +0x130
    float mFrameX;                      // +0x13c
    float mRadius;                      // +0x140
    uint32_t mProperties[3];            // +0x144
    int mNumParts;                      // +0x150
    int mNumPartModels;                 // +0x154
    ExportPart mParts[32];              // +0x158
    ExportPartModel mPartModels[8];     // +0x258
    EA::AutoRefCount_s0046_c900<cMWModel> mpModel; // +0x298
};
struct ExportJointVector {
    ExportJoint* mpBegin;
    ExportJoint* mpEnd;
    ExportJoint* mpCapacity;
    uint32_t mAllocator;
    ExportJoint& operator[](int i) { return mpBegin[i]; }
    void erase(ExportJoint* first, ExportJoint* last);     // 0x00475da0
    void clear() { erase(mpBegin, mpEnd); }
    // 0x00473370 (cl declines to inline it here)
    void resize(uint32_t n)
    {
        if (n > (uint32_t)(mpEnd - mpBegin))
            DoInsertValues(mpEnd, n - (uint32_t)(mpEnd - mpBegin), ExportJoint());
        else
            erase(mpBegin + n, mpEnd);
    }
    void insert(ExportJoint* position, uint32_t n, const ExportJoint& value) { DoInsertValues(position, n, value); }
    void DoInsertValues(ExportJoint* position, uint32_t n, const ExportJoint& value);   // 0x00478e00
};
struct ExportModel {
    int mVersion;                       // +0x00
    string16 mModelPath;                // +0x04
    uint32_t pad14[3];
    bool mbRootFirst;                   // +0x20
    uint8_t pad21[3];
    int mRootIndex;                     // +0x24
    ExportJointVector mJoints;          // +0x28
    uint32_t pad38[2];
    MeshPtr<IExportMesh> mpMesh;        // +0x40
};
namespace EA {
namespace ResourceMan {
    class IResourceManager {
    public:
        virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
        virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
        virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
        virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
        virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
        virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
        virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
        virtual void v70(); virtual void v74(); virtual void v78();
        virtual bool GetFileName(const ResourceKey_s0046_c900& key, string16& name);   // +0x7c
    };
}
}
namespace EA {
namespace ResourceMan {
    IResourceManager* GetManager();     // 0x0067dcd0
}
}
// ---- items of slice s0046c900 end

// ---- items of slice s0046d660 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" float* QuaternionFromMatrix33(float* out, const float* m, float v);
// ---- items of slice s0046d660 end

// ---- items of slice s0046e450 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Mgr {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13(void*);
};
extern "C" Mgr* FUN_0067dd60();
struct Sf260 {
    int field0;
    unsigned char flags;
};
struct BaseDesc {
    virtual void v0();
};
struct Desc {
    int a, b;
    unsigned short c, d;
    BaseDesc* ref;
    Desc* init(int, int, BaseDesc*, int);
    Desc* init0();
};
struct EAString8 {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    unsigned int alloc;
    struct Tag {};
    EAString8(Tag, const char* fmt, ...);
    ~EAString8();
    const char* c_str() const { return mpBegin; }
};
struct cPropertyList_s0046_e450 {
    virtual int AddRef();
    virtual int Release();
};
struct IPropertyManager_s0046_e450 {
virtual void pv0();
virtual void pv1();
virtual void pv2();
virtual void pv3();
virtual void pv4();
virtual void pv5();
virtual void pv6();
virtual void pv7();
virtual void pv8();
virtual void pv9();
    virtual void pv10();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, cPropertyList_s0046_e450*& result);
};
IPropertyManager_s0046_e450* PropertyManager_s0046_e450();
bool GetPropertyAsKeyInstance(cPropertyList_s0046_e450* list, uint32_t id, void* result);
template <typename T>
struct AutoRefCount_s0046_e450 {
    T* mpObject;
    AutoRefCount_s0046_e450() : mpObject(0) {}
    ~AutoRefCount_s0046_e450() { if (mpObject) mpObject->Release(); }
    operator T*() const { return mpObject; }
    T*& AsOutParam() {
        if (mpObject) {
            T* const p = mpObject;
            mpObject = 0;
            p->Release();
        }
        return mpObject;
    }
};
struct Vec3_s0046_e450 {
    float v[3];
    float& operator[](int i) { return v[i]; }
};
struct CapEntry { const char* name; int value; };
struct DeformEntry { uint32_t id; float value; };
struct Block_s0046_e450 {
    int version;           // +0x00
    wchar_t name[80];      // +0x04
    char boneName[40];     // +0xa4
    uint32_t keyGroup;     // +0xcc
    uint32_t instanceId;   // +0xd0
    int blockIndex;        // +0xd4
    int parentIndex;       // +0xd8
    int symmetricIndex;    // +0xdc
    Vec3_s0046_e450 jointPosition;    // +0xe0
    int submeshIndex;      // +0xec
    Vec3_s0046_e450 cal3DOrigin;      // +0xf0
    Vec3_s0046_e450 effectsOrigin;    // +0xfc
    Vec3_s0046_e450 position;         // +0x108
    float orientX, orientY, orientZ, orientW;  // +0x114
    Vec3_s0046_e450 bBoxMin;          // +0x124
    Vec3_s0046_e450 bBoxMax;          // +0x130
    float scale;           // +0x13c
    uint32_t pad140;
    uint32_t soundIDFoot;  // +0x144
    uint32_t soundIDMouth; // +0x148
    uint32_t soundIDWeapon;// +0x14c
    int numCaps;           // +0x150
    int numDeform;         // +0x154
    CapEntry caps[32];     // +0x158
    DeformEntry deform[8]; // +0x258
    uint32_t pad298;
};
struct BlockVec {
    Block_s0046_e450* mpBegin;
    Block_s0046_e450* mpEnd;
    Block_s0046_e450* mpCapacity;
    int size() const { return (int)(mpEnd - mpBegin); }
    Block_s0046_e450& operator[](int i) { return mpBegin[i]; }
};
struct CreatureBlocks {
    int version;               // +0
    const wchar_t* mpName;     // +4
    uint32_t pad[6];
    unsigned char isPlant;     // +0x20
    int cal3DRootBlockIndex;   // +0x24
    BlockVec blocks;           // +0x28
    const wchar_t* GetName() const { return mpName; }
};
struct StreamDesc_s0046_e450 {                       // 0x10 bytes
    int mCount;
    void* mpData;
    uint16_t mStride;
    uint16_t mStride2;
    OwnerRef mOwner;
    StreamDesc_s0046_e450(int count, void* data, int stride, IObject* owner)
        : mCount(count), mpData(data), mStride((uint16_t)stride), mStride2((uint16_t)stride), mOwner(owner)
    {
    }
    StreamDesc_s0046_e450(int count, void* data, IObject* owner, int);   // 0x0046f140
    StreamDesc_s0046_e450(const StreamDesc_s0046_e450& o);                          // 0x00401b80
    StreamDesc_s0046_e450& operator=(const StreamDesc_s0046_e450& o);               // 0x004694e0 (via 0x00424f70)
};
struct StreamElem_s0046_e450 {                       // 0x20 bytes
    int mUsage;
    int mIndex;
    int mType;
    int mSlot;
    StreamDesc_s0046_e450 mDesc;
    StreamElem_s0046_e450(int usage, int index, int type, int slot, const StreamDesc_s0046_e450& d)
        : mUsage(usage), mIndex(index), mType(type), mSlot(slot), mDesc(d)
    {
    }
    StreamElem_s0046_e450& operator=(const StreamElem_s0046_e450& o);               // 0x00424f10
};
struct StreamVec_s0046_e450 {
    StreamElem_s0046_e450* mpBegin;
    StreamElem_s0046_e450* mpEnd;
    StreamElem_s0046_e450* mpCapacity;
    uint32_t mAllocator[2];
    void resize(unsigned n);                                  // 0x00475260
    StreamElem_s0046_e450& operator[](int i) { return mpBegin[i]; }
};
struct DescVec {
    StreamDesc_s0046_e450* mpBegin;
    StreamDesc_s0046_e450* mpEnd;
    StreamDesc_s0046_e450* mpCapacity;
    uint32_t mAllocator[2];
    DescVec();                                                // 0x004725d0 (fixed_vector ctor)
    void resize(unsigned n);                                  // 0x004751a0
    StreamDesc_s0046_e450& operator[](int i) { return mpBegin[i]; }
};
struct IndexVec_s0046_e450 {
    StreamIndex* mpBegin;
    StreamIndex* mpEnd;
    StreamIndex* mpCapacity;
    uint32_t mAllocator[2];
    IndexVec_s0046_e450();                                               // 0x00472560 (fixed_vector ctor)
    void push_back(const StreamIndex& v);                     // 0x00475130
};
struct DescInit : Desc {
    DescInit() { init0(); }
};
struct __declspec(align(4)) Batch_s0046_e450 {                            // 0x8c bytes
    Batch_s0046_e450();                              // 0x0046f1b0
    ~Batch_s0046_e450();                             // 0x0041f940
    DescInit mDesc;                       // +0x00 (StreamDesc, zeroed by Desc::init0)
    int mVertexCount;                     // +0x10
    IndexVec_s0046_e450 mStreamIndices;              // +0x14
    uint32_t pad28[(0x44 - 0x28) / 4];
    DescVec mIndexDescs;                  // +0x44
    uint32_t pad58[(0x8c - 0x58) / 4];
};
struct BatchVec_s0046_e450 {
    Batch_s0046_e450* mpBegin;
    Batch_s0046_e450* mpEnd;
    Batch_s0046_e450* mpCapacity;
    uint32_t mAllocator[2];
    void push_back(const Batch_s0046_e450& b);                           // 0x004754e0
    Batch_s0046_e450& back() { return *(mpEnd - 1); }
};
struct MeshGroup_s0046_e450 {                        // 0x58 bytes
    MeshGroup_s0046_e450();                          // 0x0040d160
    uint32_t vt;
    volatile long mnRefCount;             // +0x04
    void AddRef() { _InterlockedIncrement(&mnRefCount); }
    StreamVec_s0046_e450 mStreams;                   // +0x08
    BatchVec_s0046_e450 mBatches;                    // +0x1c
    IndexRangeVec mRanges;                // +0x30
    uint32_t pad34[(0x58 - 0x34) / 4];
};
struct MeshGroupRef_s0046_e450 {
    MeshGroup_s0046_e450* p;
    MeshGroupRef_s0046_e450(MeshGroup_s0046_e450* g) : p(g)
    {
        if (p)
            p->AddRef();
    }
    ~MeshGroupRef_s0046_e450();                      // 0x00472520
    MeshGroup_s0046_e450* operator->() const { return p; }
};
struct DefaultRefCounted {
    void* vtbl;
    int mnRefCount;
    void Release();                       // 0x00453540
};
template <typename T>
struct Vec_s0046_e450 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[2];
    int size() const { return (int)(mpEnd - mpBegin); }
    T* begin() const { return mpBegin; }
};
struct Vec2f { float x, y; };
struct cMesh : DefaultRefCounted {
    Vec_s0046_e450<Vec3f> mVertices;                 // +0x08
    uint32_t pad1c[(0x30 - 0x1c) / 4];
    Vec_s0046_e450<Vec2f> mTextureCoordinates;       // +0x30
    uint32_t pad44[5];
    Vec_s0046_e450<uint32_t> mVertexIndices_TV;      // +0x58
    uint32_t pad6c[5];
    Vec_s0046_e450<uint32_t> mTextureIndices_TV;     // +0x80
};
struct MeshRef_s0046_e450 {
    cMesh* p;
    MeshRef_s0046_e450() : p(0) {}
    ~MeshRef_s0046_e450();                           // 0x00472540
    MeshRef_s0046_e450& Reset();                     // 0x0041d900
    operator cMesh**() { return &p; }
    cMesh* operator->() const { return p; }
};
struct EditorModelSource {
    uint32_t pad00[0xfc / 4];
    Sf260* mpTexture;                     // +0xfc
    Sf260* GetTexture() { return mpTexture; }
};
struct cPaintSystem {
    void BuildMeshes(EditorModelSource* src, cMesh** ppMesh);   // 0x00525360
};
cPaintSystem* GetPaintSystem();           // 0x00401080
struct RefVector {                        // 0x14 bytes
    MeshGroup_s0046_e450** mpBegin;
    MeshGroup_s0046_e450** mpEnd;
    MeshGroup_s0046_e450** mpCapacity;
    uint32_t mAllocator[2];
    RefVector(const AllocTag&);           // 0x00540470
    RefVector(const RefVector& o);        // 0x0041eae0
    ~RefVector();                         // 0x0041eb80
    void push_back(const MeshGroupRef_s0046_e450& r);  // 0x0041ef20
};
bool DumpZPR(RefVector models, int tex, const wchar_t* name);   // 0x0046f2a0
// ---- items of slice s0046e450 end

// forward declarations: helpers defined later in VA order (rewrite.py forward_protos)
int __fastcall FUN_0046f260(Sf260* p);   // defined at 0x0046f260, called earlier in the TU

// ---- items of slice s0046f2a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char gEmptyStr8[];                               // 0x01667bac
extern "C" size_t __cdecl strlen(const char*);
#pragma intrinsic(strlen)
void* operator new[](unsigned, const char*, int, int, int, int);   // 0x00f473a0
struct Stream {                 // vertex/index stream
    int count;                  // +0x00
    char* data;                 // +0x04
    uint16_t format;            // +0x08
    uint16_t stride;            // +0x0A
    int unk0c;                  // +0x0C
};
struct ModelStreamEntry {
    uint32_t pad[4];
    Stream stream;              // +0x10
};
struct StreamRef {
    short stream;
    short remap;
};
struct StreamVector {           // eastl::vector<Stream>, 0x10 bytes
    Stream* mpBegin;
    Stream* mpEnd;
    Stream* mpCapacity;
    int mAllocator;
    bool empty() const;                                 // 0x00526430 (out of line)
    Stream& operator[](int i) { return mpBegin[i]; }
};
struct Mesh {                   // 0x8C bytes
    Stream mIndices;            // +0x00
    uint32_t pad10;             // +0x10
    StreamRef* mStreamMap;      // +0x14
    uint32_t pad18[(0x44 - 0x18) / 4];
    StreamVector mRemaps;       // +0x44
    uint32_t pad54[(0x8c - 0x54) / 4];
};
struct MeshVector {
    Mesh* mpBegin;
    Mesh* mpEnd;
    Mesh* mpCapacity;
    int mAllocator;
    int size() const { return mpEnd - mpBegin; }
    Mesh& operator[](int i) { return mpBegin[i]; }
};
struct Model_s0046_f2a0 {
    uint32_t pad00[2];
    ModelStreamEntry* mStreams; // +0x08
    uint32_t pad0c[(0x1c - 0xc) / 4];
    MeshVector mMeshes;         // +0x1C
};
void __cdecl FUN_00733ed0(Model_s0046_f2a0* m);                                   // 0x00733ed0
void __cdecl CreateClustersAndEdges(Model_s0046_f2a0* m, int flag);               // 0x00735470 (cMeshClusterer::CreateClustersAndEdges)
Stream* __cdecl FUN_0071de40(Model_s0046_f2a0* m, int a, int b, int c, int d);    // 0x0071de40 (returns the model's vertex-position stream)
bool __cdecl FindMeshStreams(Model_s0046_f2a0* model, int meshIndex, int count, int* semantics, int* usageIndex,
                             int* formats, int* outIdx);               // 0x0071e110
struct RefVector_s0046_f2a0 {
    Model_s0046_f2a0** mpBegin;
    Model_s0046_f2a0** mpEnd;
    Model_s0046_f2a0** mpCapacity;
    int d3, d4;
    RefVector_s0046_f2a0(const RefVector_s0046_f2a0& o);                      // 0x0041eae0
    ~RefVector_s0046_f2a0();                                       // 0x0041eb80
    Model_s0046_f2a0*& operator[](int i) { return mpBegin[i]; }
};
template <typename T> struct VectorBase {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    ~VectorBase();                                      // 0x004c0b80
};
struct __declspec(align(4)) IntVector_s0046_f2a0 : VectorBase<int> {
    int mAllocFlags;
    int* mpBuf;
    int mAllocPad;
    int mBuffer[16];
    IntVector_s0046_f2a0();                                        // 0x0041cfe0
    ~IntVector_s0046_f2a0() { for (int* p = mpBegin; p < mpEnd; ++p) {} }
    void push_back(const int& v);                       // 0x00422380
};
struct EStr {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    int mAllocator;
    EStr() : mpBegin(0), mpEnd(0), mpCapacity(0) { mpBegin = gEmptyStr8; mpEnd = mpBegin; mpCapacity = mpBegin + 1; }
    const char* c_str() const { return mpBegin; }
    ~EStr();                                            // 0x00530670
    int sprintf(const char* fmt, ...);                  // 0x00472fe0 (cdecl, this pushed first)
};
struct SpriteTexture {
    char pad0[0xc];
    uint16_t mWidth;            // +0x0C
    uint16_t mHeight;           // +0x0E
    uint8_t mBitsPerPixel;      // +0x10
    char pad11[0x13 - 0x11];
    uint16_t GetWidth() const { return mWidth; }
    uint16_t GetHeight() const { return mHeight; }
    uint8_t GetBitsPerPixel() const { return mBitsPerPixel; }
    int __thiscall FillSpriteTexture(void* pixels, unsigned int bytes, int zero);   // 0x011f0440
};
void ExportModelTriangles(FILE* file, RefVector_s0046_f2a0 models, const int& triangleCount,
                          const IntVector_s0046_f2a0& vertexBase, const IntVector_s0046_f2a0& triangleBase, bool perModelID);  // 0x0046ff00
void DumpZPR_M0(FILE* file, RefVector_s0046_f2a0 models, int& triangleCount, IntVector_s0046_f2a0& vertexBase,
                IntVector_s0046_f2a0& triangleBase);                                                        // 0x0046f8a0
namespace __equiv_ann1 {
struct IntVector_s0046_f2a0 {
    IntVector_s0046_f2a0();   // 0x0041cfe0 (equiv t3)
};
}
// ---- items of slice s0046f2a0 end

// ---- items of slice s0046ff00 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t gIndexMask[];   // 0x013EEC84: per-stream-format index mask (0xff, 0xffff, ...)
struct Model_s0046_ff00 {
    uint32_t pad00[2];
    ModelStreamEntry* mStreams; // +0x08
    uint32_t pad0c[(0x1c - 0xc) / 4];
    MeshVector mMeshes;         // +0x1C
};
bool FindMeshStreams(Model_s0046_ff00* model, int meshIndex, int count, int* semantics, int* usageIndex,
                     int* formats, int* outIdx);
struct ModelRefVector {  // eastl::vector<intrusive_ptr<Model>>, passed by value
    Model_s0046_ff00** mpBegin;
    Model_s0046_ff00** mpEnd;
    Model_s0046_ff00** mpCapacity;
    int mAllocator;
    ~ModelRefVector();                                   // 0x0041EB80 (RefVector::~RefVector)
    int size() const { return mpEnd - mpBegin; }
    Model_s0046_ff00*& operator[](int i) { return mpBegin[i]; }
};
struct IntVector_s0046_ff00 {       // eastl::vector<int>
    int* mpBegin;
    int* mpEnd;
    int* mpCapacity;
    int mAllocator;
};
struct Vector2_s0046_ff00 {
    float x, y;
    Vector2_s0046_ff00(const Vector2_s0046_ff00& o) { x = o.x; y = o.y; }
};
static inline uint32_t ReadIndex(Stream* s, uint32_t i)
{
    return *(uint32_t*)(s->data + s->stride * i) & gIndexMask[s->format];
}
// ---- items of slice s0046ff00 end

// ---- items of slice s00470bd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_DefaultX;     // 0x15d4104
extern float g_DefaultY;     // 0x15d4108
extern float g_Epsilon;      // 0x13ec478 (0.05)
extern float g_Zero;         // 0x1485378
extern float g_Third;        // 0x13eb8c8 (0.3)
extern float g_BoxFallbackRadius;                           // 0x1488874
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned long long u64;
struct Vec3_s0047_0bd0 {
    float v[3];
    float& operator[](int i) { return v[i]; }
};
struct Vec2_s0047_0bd0 {
    union { float v[2]; struct { float x, y; }; };
    float& operator[](int i) { return v[i]; }
};
struct Vec4 {
    float v[4];
    Vec4(float a, float b, float c, float d) { v[0] = a; v[1] = b; v[2] = c; v[3] = d; }
    float& operator[](int i) { return v[i]; }
};
struct Box {                 // 0x18 bytes: min then max
    Vec3_s0047_0bd0 mMin;
    Vec3_s0047_0bd0 mMax;
    void Reset();                                  // 0x409c00
    void AddPoint(const Box* b);                   // 0x43f050 (extends by another box)
    void SetCenterRadius(const Vec3_s0047_0bd0* c, float r);  // 0x409ce0
};
struct Transform_s0047_0bd0 {
    u16 mFlags; u16 mCount;
    Vec3_s0047_0bd0 mPos;
    float mScale;
    Mat9 mRot;
    Transform_s0047_0bd0();                                   // 0x409930
    void SetScale(float s) { mScale = s; mCount++; }
    void SetRotation(const Mat9& r) { mRot = r; mFlags |= 2; mCount++; }
    void SetPosition(const Vec3_s0047_0bd0& p) { mPos = p; mFlags |= 4; mCount++; }
};
extern Vec3_s0047_0bd0 g_Vec3Zero;      // 0x15d4034
inline float Max2(Vec4* p, int i, int j)
{
    float r;
    if ((*p)[i] >= (*p)[j]) r = (*p)[i]; else r = (*p)[j];
    return r;
}
inline float MaxF(const float& a, const float& b)
{
    float r;
    if (a >= b) r = a; else r = b;
    return r;
}
struct Range { Box* mp; int mCount; float mBest; };
struct Variant_s0047_0bd0 {
    unsigned int mData[4];
    u16 mFlags;
    u16 mTypeId;
    Variant_s0047_0bd0() : mFlags(0), mTypeId(0) {}
    ~Variant_s0047_0bd0() { if (mFlags & 4) Destruct(false); }
    // operator=<float> / operator=<Box> instantiations; named apart so each annotation is unique
    Variant_s0047_0bd0& SetFloat(const float& x);                          // 0x428060
    Variant_s0047_0bd0& SetBox(const Box& x);                              // 0x478300
    void Destruct(bool bReconstruct);                           // 0x93db80
};
struct Property_s0047_0bd0 {
    char pad[0x12];
    u16 mType;                       // +0x12
    bool* GetBool();                 // 0x41e920
    int*  GetInt();                  // 0x41e990
};
struct IPropList_s0047_0bd0 {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void Set(u32 id, const Variant_s0047_0bd0* v);                 // slot 5 (+0x14)
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual bool Get(u32 id, Property_s0047_0bd0** out);                   // slot 9 (+0x24)
};
struct IObject_s0047_0bd0 {
    virtual void s0();
    virtual void Release();                                     // slot 1 (+4)
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual bool Get(u32 id, Property_s0047_0bd0** out);                   // slot 9 (+0x24)
};
struct IPropManager {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10();
    virtual bool GetObject(u32 a, u32 b, IObject_s0047_0bd0** out);        // slot 11 (+0x2c)
};
struct ObjPtr { IObject_s0047_0bd0* mp; };
struct RefState { bool b; int z0; int z1; int z2; };
struct VecBox {
    Box* mpBegin; Box* mpEnd; Box* mpCap; int mAlloc;
    char buf[0x608];
    VecBox(bool* a);                                // 0x540470
    void Init();                                    // 0x41da70
    void push_back(const Box* b);                   // 0x41e8b0
    void reserve(int n);                            // 0x41e770
    void Free();                                    // 0x4fd940
};
struct VecV2_s0047_0bd0 {
    Vec2_s0047_0bd0* mpBegin; Vec2_s0047_0bd0* mpEnd; Vec2_s0047_0bd0* mpCap; int mAlloc;
    char buf[72];
    void Init();                                    // 0x41cfe0
    void push_back(const Vec2_s0047_0bd0* v);                  // 0x475670
    void Free();                                    // 0x526a40
};
IPropManager* __cdecl PropertyManager_s0047_0bd0();                              // 0x67de30
IObject_s0047_0bd0** __fastcall PropObjOut(ObjPtr* p);                           // 0x41d870
Vec3_s0047_0bd0* __cdecl Vector3_Negate(Vec3_s0047_0bd0* out, const Vec3_s0047_0bd0* in);              // 0x422020
Vec3_s0047_0bd0* __cdecl Vector3_MaxVec(Vec3_s0047_0bd0* out, const Vec3_s0047_0bd0* a, const Vec3_s0047_0bd0* b); // 0x41bfb0
float __cdecl VectorLength(const Vec3_s0047_0bd0* v);                            // 0x40ae50
bool  __cdecl GetPropertyAsFloatArray(IPropList_s0047_0bd0* pl, u32 id, int* count, float** arr); // 0x6a08b0
void  __cdecl SortV2(Vec2_s0047_0bd0* b, Vec2_s0047_0bd0* e, bool flag);                    // 0x478620
struct Item {                // 0x8c bytes
    char pad0[0x14];
    Vec3_s0047_0bd0 mBoxMin;            // +0x14
    Vec3_s0047_0bd0 mBoxMax;            // +0x20
    float mScale;            // +0x2c
    Mat9 mRot;               // +0x30
    Vec3_s0047_0bd0 mPos;               // +0x54
    char pad1[0x84 - 0x60];
    u32 mIdHi;               // +0x84
    u32 mIdLo;               // +0x88
};
struct ItemVec { char* mpBegin; char* mpEnd; };
struct Editor_s0047_0bd0 {
    char pad0[0x18];
    int f18;
    char pad1[0x98 - 0x1c];
    ItemVec mItems;
};
struct Vec3C {                                              // Vector3 with a copy ctor at 0x4098a0
    float x, y, z;
    Vec3C(const Vec3_s0047_0bd0& o);                                  // 0x004098a0
};
struct BoxC {
    Vec3C mMin; Vec3C mMax;
    BoxC(const Vec3_s0047_0bd0& a, const Vec3_s0047_0bd0& b) : mMin(a), mMax(b) {}
    void SetCenterRadius(const Vec3_s0047_0bd0* c, float r);          // 0x409ce0
    void TransformBy(const Transform_s0047_0bd0* t);                  // 0x409dd0
};
struct VecBoxC {
    Box* mpBegin; Box* mpEnd; Box* mpCap; int mAlloc;
    char buf[0x608];
    VecBoxC(bool* a);                                       // 0x540470
    void Init();                                            // 0x41da70
    void push_back(const BoxC* b);                          // 0x41e8b0
    void reserve(int n);                                    // 0x41e770
    void Free();                                            // 0x4fd940
};
struct VecIds {
    u64* mpBegin; u64* mpEnd; u64* mpCap; int mAlloc;
    char buf[72];
    VecIds(bool* a);                                        // 0x540470
    void Init();                                            // 0x4c5e30
    void push_back(const u64* v);                           // 0x475800
    void reserve(int n);                                    // 0x4756f0
    void Free();                                            // 0x4cddd0
};
// ---- items of slice s00470bd0 end

// forward declarations: helpers defined later in VA order (rewrite.py forward_protos)
float FUN_00470f20(Vec4* p);   // defined at 0x00470f20, called earlier in the TU

// ---- items of slice s00471b50 begin (TODO(rewrite): local stubs, replace by canonical classes)
template <int N> inline void ScratchSlots_s0047_1b50()
{
    uint32_t s[N];
    (void)s;
}
class DefaultRefCounted_s0047_1b50 {
public:
    void Release();
};
struct RefHolderB {
    DefaultRefCounted_s0047_1b50* p;
    ~RefHolderB();
};
// ---- items of slice s00471b50 end

// ---- items of slice s004604f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" long __cdecl _InterlockedExchange(volatile long*, long);
extern char g_sentinel2;   // 0x01667bac
extern void __cdecl GetFloatProperty(int owner, int key, float* out);     // 0x40cf10
extern float g_const_1486114;       // 0x1486114
extern int   g_3e8c[3];             // 0x15d3e8c
    extern float g_f1485720; // 0x01485720
    extern float g_f13eecd8; // 0x013eecd8
    extern float g_f13ec480; // 0x013ec480
    extern float g_f1471064; // 0x01471064
#pragma intrinsic(_InterlockedExchange)
struct RefCounted {
    char         pad[8];
    volatile long mnRefCount;
    int AddRef();
};
struct Sub {
    void* b;
    void* e;
    void* c;
};
struct C461400 {
    char  pad0[4];
    Sub   sub1;       // +0x04
    char  pad1[0x18];
    Sub   sub2;       // +0x28
    char  pad2[8];
    void* p3c;        // +0x3c
    void* p40;        // +0x40
    C461400* Ctor();
};
struct Vec3_s0046_04f0 { float x, y, z; Vec3_s0046_04f0() {} Vec3_s0046_04f0(const Vec3_s0046_04f0& o) { x = o.x; y = o.y; z = o.z; } };
extern Vec3_s0046_04f0* __cdecl Vector3_Add(Vec3_s0046_04f0* a, const Vec3_s0046_04f0* b);                           // 0x41ddb0
extern Vec3_s0046_04f0* __cdecl Vector3_Sub(Vec3_s0046_04f0* out, const Vec3_s0046_04f0* a, const Vec3_s0046_04f0* b);          // 0x41db10
extern Vec3_s0046_04f0* __cdecl Vector3_Scale(Vec3_s0046_04f0* out, const Vec3_s0046_04f0* a, const float* s);       // 0x41dca0
struct Bone {
    char  pad0[4];
    short parent;      // +4
    char  pad1[0x26];
    float weight;      // +0x2c
    char  pad2[0x24];
    Vec3_s0046_04f0  pos;         // +0x54
    char  pad3[0x8c - 0x60];
};
template<int N> inline void ScratchSlots_s0046_04f0() { unsigned int s[N]; }
struct EmptyAlloc { EmptyAlloc() {} };
struct Alloc {
    int a, b;
    Alloc() {}
    Alloc* __thiscall Copy(const EmptyAlloc& o);   // 0x429360 (copy ctor)
};
template <class T> struct Vec_s0046_04f0 {         // vector with a real allocator sub-object (0x14 bytes)
    T* b; T* e; T* c;
    Alloc al;
    void Init(const EmptyAlloc& a) { b = 0; e = 0; c = 0; al.Copy(a); }
};
template <class T> struct VecPlain {    // vector with an empty allocator (0x14 bytes)
    T* b; T* e; T* c;
    int pad[2];
    void Init() { b = 0; e = 0; c = 0; }
};
void* operator new(unsigned n, const char* name, int, int, int, int);   // 0xf473a0
struct C460f80 {
    Vec_s0046_04f0<int>       v0;      // 0x00
    Vec_s0046_04f0<int>       v1;      // 0x14
    Vec_s0046_04f0<int>       v2;      // 0x28
    VecPlain<int>  v3;      // 0x3c
    VecPlain<int>  v4;      // 0x50
    VecPlain<int>  v5;      // 0x64
    VecPlain<int>  v6;      // 0x78
    C460f80* __thiscall Ctor();
};
struct Piece { int a, b; };
struct PieceVec {                       // 0x14: vector<Piece>
    Piece* b; Piece* e; Piece* c; Alloc al;
    unsigned size() { return e - b; }
    Piece* data() { return b; }
};
struct PieceVecList {                   // vector<PieceVec>
    PieceVec* b; PieceVec* e; PieceVec* c; Alloc al;
    PieceVecList(const EmptyAlloc& a = EmptyAlloc()) { b = 0; e = 0; c = 0; al.Copy(a); }
    ~PieceVecList();                    // 0x432de0
    PieceVec* at(unsigned i) { return b + i; }
    unsigned size() { return e - b; }
};
struct RefObj {
    void* vt;
    int   mnRefCount;      // +4
    int AddRef() { return mnRefCount++ + 1; }
    void __thiscall Release();                               // 0x453540
    void __thiscall GetPieces(int src, PieceVecList* out);   // 0x7a0ee0
};
struct AutoRef_s0046_04f0 {
    RefObj* p;
    AutoRef_s0046_04f0(RefObj* x) { p = x; if (p) p->AddRef(); }
    ~AutoRef_s0046_04f0() { if (p) p->Release(); }
};
struct EditorPropList {
    char pad[0x38];
    EditorPropList();                              // 0x6a1c40
    void __thiscall SetParent(int parent);         // 0x6a1710
};
struct PropMgr2 {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
virtual void v12();
    virtual void SetPropList(EditorPropList* pl, int a, int b);     // +0x34
};
extern PropMgr2* __cdecl GetPropertyManager();                            // 0x67de30
extern RefObj* __cdecl FUN_0079ab90(int a, int b, void* data, int n);
struct RefVec {
    Piece** b; Piece** e; Piece** c; Alloc al;
    RefVec(const EmptyAlloc& a = EmptyAlloc()) { b = 0; e = 0; c = 0; al.Copy(a); }
    ~RefVec();                                 // 0x41eb80
    void __thiscall PushBack(Piece* p);        // 0x41ef20
    char __thiscall IsResourceType();          // 0x526430 (SP::GetResourceTypeFromModelType)
};
extern void __cdecl GetModelAsGameMeshes(int a, RefVec* v, int b, int c, int d, int e, EditorPropList* pl,
                                         int f, int g, int h, int i, int j);   // 0x7573a0
struct MatInfo {
    char  pad[0xc];
    char  kind;       // +0xc
    char  pad1[3];
    float f10, f14, f18, f1c;
    MatInfo();        // 0x432cf0
};
struct IRef { virtual void v0(); virtual void Release(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
              virtual bool GetProperty(unsigned key, struct Property_s0046_04f0** out); };
struct Property_s0046_04f0 {
    char pad[0x12];
    unsigned short type;
    int* __thiscall GetInt();  // 0x0041e990 (Property::GetInt)
};
struct PropMgr3 {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
    virtual bool GetPropertyList(unsigned id, unsigned group, IRef** out);   // +0x2c
};
struct ShaderRes {
    char pad[0x70];
    ShaderRes();                                       // 0x40d010
    void __thiscall InsertResource(int slot, int res); // 0x77cb10
    void __thiscall setSlotU0(int slot, int v);        // 0x777a60
    void __thiscall setSlotU1(int slot, int v);        // 0x777a80
    void __thiscall setSlotV0(int slot, int v);        // 0x777aa0
    void __thiscall setSlotV1(int slot, int v);        // 0x777ac0
};
struct ResMgr { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
                virtual int GetResource(unsigned key, int a, int b); };   // +0x20
extern PropMgr3* __cdecl GetPropertyManager3();   // 0x67de30
extern ResMgr* __cdecl GetResMgr();               // 0x67dd60
struct PtrVector { void __thiscall PushBack(void* p); };   // 0x77d970
struct C472660 { char pad[0xc]; C472660(); };   // 0x472660
struct C4726d0 { char pad[0xc]; C4726d0(); };   // 0x4726d0
// ---- items of slice s004604f0 end

// ---- items of slice s004614b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern unsigned char g_byte_15d3c30;
extern "C" void  FUN_009fc0f0(void* p);               // 0x9fc0f0
extern "C" void  FUN_0052a400(int a, unsigned int b, unsigned int c, int d, int e, int f); // 0x52a400
extern "C" void  FUN_00473300(void* p);               // 0x473300
extern "C" void  WString_FreeBuffer(void* p);         // 0x4237d0
extern "C" void  Counted_Release(void* p);            // 0x40f360
extern "C" void* LowerBound12(void* start, void* end, const void* key, int flag); // 0x422430
extern char g_table_150c050;
extern int  g_count_13ec430;
struct TableEntry {
    unsigned    key;
    const char* name;
    char        pad[4];
};
// the image's "unknown" literal (returned when the key is absent)
extern const char g_strUnknown_13eecec[];
struct IRefObj {
    virtual void v0();
    virtual void Release();   // +0x04
};
// Raw thiscall helpers used by the destructor (ecx carries the argument).
struct CountedObject {
    void Release();      // 0x0040f360 (thiscall, ret 0)
};
struct SubObject {
    void Destroy();      // 0x00473300 (thiscall, ret 0)
};
struct WStringBuffer {
    void Free();         // 0x004237d0 (thiscall, ret 0)
};
struct Holder {
    char  pad0[4];
    char  str[0x24];     // +0x04  (string buffer)
    char  sub[0x14];     // +0x28
    void* p3c;           // +0x3c
    IRefObj* p44;        // +0x40
    void Dtor();
};
union Bits {
    unsigned int raw;
    struct {
        unsigned int lo : 8;
        unsigned int mid : 8;
        unsigned int hi : 16;
    } f;
};
// ---- items of slice s004614b0 end

// forward declarations: helpers defined later in VA order (rewrite.py forward_protos)
namespace SP { namespace EditorUtils { void AddInitialBoundInfo(SP::cEditorResource * a1, SP::cPropertyList * a2); } }   // defined at 0x00471b50, called earlier in the TU

// @ 0x004604f0
void BuildCreatureMaterialInfo(PtrVector* out, unsigned id, int tex0, int tex1, int unused, char skipLookup)
{
    MatInfo* mi = new ("Editor", 0, 0, 0, 0) MatInfo();
    mi->f18 = g_f1485720;
    mi->f10 = g_f13eecd8;
    mi->f14 = g_f13ec480;
    mi->f1c = g_f1471064;
    if (id == 0x3d97a8e4) {
        mi->kind = 4;
    } else if (id == 0x438f6347) {
        mi->kind = 5;
    } else {
        int level = 2;
        if (!skipLookup) {
            unsigned key = 0x4529f96f;
            unsigned group = 0x40626200;
            IRef* list = 0;
            PropMgr3* pm = GetPropertyManager3();
            if (list) {
                IRef* t = list;
                list = 0;
                t->Release();
            }
            if (pm->GetPropertyList(key, group, &list)) {
                IRef* l = list;
                if (l) {
                    Property_s0046_04f0* prop;
                    if (l->GetProperty(0x4c6ba3c, &prop)) {
                        if (prop->type == 9) level = *prop->GetInt();
                    }
                }
            }
            if (list) list->Release();
        }
        if (level >= 2) mi->kind = 7; else mi->kind = 6;
    }
    out->PushBack(mi);
    int flag = tex0 != 0;
    if (mi->kind == 4) {
        ShaderRes* sr = new ("Editor", 0, 0, 0, 0) ShaderRes();
        int r2 = GetResMgr()->GetResource(0x552a5077, 0, 0);
        sr->InsertResource(0, tex0);
        sr->setSlotU0(0, 3); sr->setSlotU1(0, 2); sr->setSlotV0(0, 2); sr->setSlotV1(0, flag);
        sr->InsertResource(1, tex1);
        sr->setSlotU0(1, 3); sr->setSlotU1(1, 2); sr->setSlotV0(1, 2); sr->setSlotV1(1, flag);
        sr->InsertResource(2, r2);
        sr->setSlotU0(2, 3); sr->setSlotU1(2, 2); sr->setSlotV0(2, 2); sr->setSlotV1(2, flag);
        out->PushBack(sr);
    } else if (mi->kind == 7 || mi->kind == 5) {
        ShaderRes* sr = new ("Editor", 0, 0, 0, 0) ShaderRes();
        sr->InsertResource(0, tex0);
        sr->setSlotU0(0, 1); sr->setSlotU1(0, 2); sr->setSlotV0(0, 2); sr->setSlotV1(0, flag);
        sr->InsertResource(1, tex1);
        sr->setSlotU0(1, 3); sr->setSlotU1(1, 2); sr->setSlotV0(1, 2); sr->setSlotV1(1, flag);
        out->PushBack(sr);
    } else if (mi->kind == 6) {
        ShaderRes* sr = new ("Editor", 0, 0, 0, 0) ShaderRes();
        sr->InsertResource(0, tex0);
        sr->setSlotU0(0, 1); sr->setSlotU1(0, 2); sr->setSlotV0(0, 2); sr->setSlotV1(0, flag);
        out->PushBack(sr);
    }
    if (id == 0x2b978c46) {
        out->PushBack(new ("Editor", 0, 0, 0, 0) C472660());
    } else if (id == 0x3d97a8e4) {
        out->PushBack(new ("Editor", 0, 0, 0, 0) C4726d0());
    }
}

// @ 0x00460a80
int FUN_00460a80(int verts, int target, int* ids, int count)
{
    int out = 0;
    int i = 0;
    while (i < count) {
        if (target == *(short*)(verts + ids[i] * 4)) {
            int id = ids[i];
            ids[i] = ids[out];
            ids[out] = id;
            out = out + 1;
            int n = FUN_00460a80(verts, id, ids + out, count - out);
            out = n + out;
        }
        int nxt = i + 1;
        int* chosen;
        if (nxt < out) {
            chosen = &out;
        } else {
            chosen = &nxt;
        }
        i = *chosen;
    }
    return out;
}

// @ 0x00460b50
void FUN_00460b50(Bone* bones, int count, int root, Vec3_s0046_04f0 offs)
{
    for (int i = root + 1; i < count; i++) {
        if (bones[i].parent == root) {
            Vector3_Add(&bones[i].pos, &offs);
            FUN_00460b50(bones, count, i, offs);
        }
    }
}

// @ 0x00460bf0
void FUN_00460bf0(Bone* bones, int count, int root, float t)
{
    bones[root].weight = bones[root].weight * t;
    for (int i = root + 1; i < count; i++) {
        if (bones[i].parent == root) {
            Vec3_s0046_04f0 n28;
            int v2;
            Vec3_s0046_04f0* hi = Vector3_Sub(&n28, &bones[root].pos, &bones[i].pos);
            Vec3_s0046_04f0 p30;
            p30.x = hi->x; p30.y = hi->y; p30.z = hi->z;
            float key = 1.0f - t;
            Vec3_s0046_04f0 v9;
            Vector3_Add(&bones[i].pos, Vector3_Scale(&v9, &p30, &key));
            FUN_00460b50(bones, count, i, p30);
        }
    }
}

// @ 0x00460d40
void FUN_00460d40(int p1, int p2, int p3, int p4, int p5, int p6, int p7)
{
    int   t24[3];
    float u;
    t24[0] = g_3e8c[0];
    t24[1] = g_3e8c[1];
    t24[2] = g_3e8c[2];
    u = g_const_1486114;
    GetFloatProperty(p2, 0x67ef6b0, &u);
    AutoRef_s0046_04f0 v33(FUN_0079ab90(1, 0, t24, 4));

    PieceVecList p30;
    v33.p->GetPieces(p3, &p30);

    RefVec v28;
    unsigned obj = p30.size();
    for (unsigned i = 0; i < obj; i++) {
        unsigned j = 0;
        unsigned n = p30.at(i)->size();
        for (; j < n; j++) {
            v28.PushBack(p30.at(i)->data() + j);
        }
    }

    EditorPropList* n37 = new ("Graphics", 0, 0, 0, 0) EditorPropList();
    n37->SetParent(p2);
    GetPropertyManager()->SetPropList(n37, p4, p5);
    if (!v28.IsResourceType()) {
        GetModelAsGameMeshes(p1, &v28, p4, p5, p6, 0, n37, 0, 0, 0, 0, p7);
    }
}

// @ 0x00460f80
C460f80* C460f80::Ctor()
{
    char t2, t1, t0;
    ScratchSlots_s0046_04f0<1>();
    v0.Init(*(const EmptyAlloc*)&t2);
    v1.Init(*(const EmptyAlloc*)&t1);
    v2.Init(*(const EmptyAlloc*)&t0);
    v3.Init();
    v4.Init();
    v5.Init();
    v6.Init();
    return this;
}

// @ 0x00461290
int RefCounted::AddRef()
{
    return _InterlockedIncrement(&mnRefCount);
}

// @ 0x00461400
C461400* C461400::Ctor()
{
    Sub* s1 = &sub1;
    s1->b = 0;
    s1->e = 0;
    s1->c = 0;
    s1->b = &g_sentinel2;
    s1->e = s1->b;
    s1->c = (char*)s1->b + 2;
    Sub* s2 = &sub2;
    s2->b = 0;
    s2->e = 0;
    s2->c = 0;
    void** p3 = &p3c;
    *p3 = 0;
    void** p4 = &p40;
    *p4 = 0;
    return this;
}

// @ 0x004614b0
void Holder::Dtor()
{
    if (p44 != 0) {
        p44->Release();
    }
    if (p3c != 0) {
        ((CountedObject*)p3c)->Release();
    }
    ((SubObject*)sub)->Destroy();
    ((WStringBuffer*)str)->Free();
    return;
}

// @ 0x00461510
unsigned char GetGlobalFlag()
{
    return g_byte_15d3c30;
}

// @ 0x00461520
const char* LookupName(int key)
{
    TableEntry* start = (TableEntry*)&g_table_150c050;
    TableEntry* end = (TableEntry*)((char*)&g_table_150c050 + g_count_13ec430 * 0xc);
    TableEntry* it = (TableEntry*)LowerBound12(start, end, &key, 0);
    TableEntry* found = end;
    if (it != end && !((unsigned)key < it->key)) {
        found = it;
    }
    if (found == end) {
        return g_strUnknown_13eecec;
    }
    return found->name;
}

// @ 0x004615b0
void UseName(int key)
{
    void* p = (void*)LookupName(key);
    FUN_009fc0f0(p);
    return;
}

// @ 0x004615e0
void RegisterCreatureModels(int a, unsigned int flags, int c, int d, int e)
{
    Bits x;
    x.raw = flags;
    x.f.mid = 0x29;
    x.f.lo = 1;
    Bits y;
    y.raw = flags;
    y.f.mid = 0x29;
    y.f.lo = 0;
    FUN_0052a400(a, y.raw, x.raw, c, d, e);
    return;
}

// @ 0x004629e0
namespace SP { namespace EditorUtils {
bool ExportToXMFAndBlocks(EditorModel* model, EditorCreatureData* data, const wchar_t* dir)
{
    if (!model || !data || !data->GetSkeleton() || !dir)
        return false;

    EditorBone* bones = data->GetSkeleton()->mBones.mpBegin;
    int nBones = 0;
    if (bones)
        nBones = data->GetSkeleton()->mBones.size();
    if (nBones <= 0 || !bones)
        return false;

    wchar_t name[260];
    EA::IO::SplitPath(model->GetFileName(), 0, 0, name, 0, 4);
    wstring path(CtorSprintf(), L"%ls/%ls.dae", dir, name);

    ExportHelperA helperA;
    ExportHelperB helperB;
    ColladaExport dae;

    dae.mName.assign(name);

    // skin mesh
    dae.mPositions = data->GetSkinMesh()->mPositions;
    dae.mNormals = data->GetSkinMesh()->mNormals;
    dae.mUVs = data->GetSkinMesh()->mUVs;
    for (unsigned int k = 0, n = dae.mUVs.size(); k < n; k++)
        dae.mUVs[k][1] = 1.0f - dae.mUVs[k][1];

    dae.mTangents.resize(data->GetSkinMesh()->mFrames.size());
    dae.mBinormals.resize(data->GetSkinMesh()->mFrames.size());
    for (unsigned int k = 0, n = data->GetSkinMesh()->mFrames.size(); k < n; k++) {
        dae.mTangents[k] = data->GetSkinMesh()->mFrames[k].mTangent;
        dae.mBinormals[k] = data->GetSkinMesh()->mFrames[k].mBinormal;
    }

    dae.mPosIndices = data->GetSkinMesh()->mPosIndices;
    dae.mNormalIndices = data->GetSkinMesh()->mNormalIndices;
    dae.mUVIndices = data->GetSkinMesh()->mUVIndices;

    // skin weights
    dae.mBoneWeights.resize(data->mSkinWeights.size());
    dae.mBoneIndices.resize(data->mSkinWeights.size());
    SkinVertexWeights* skin = data->mSkinWeights.mpBegin;
    for (unsigned int k = 0, n = data->mSkinWeights.size(); k < n; k++) {
        dae.mBoneIndices[k].b[0] = skin[k].mIndex[0];
        dae.mBoneIndices[k].b[1] = skin[k].mIndex[1];
        dae.mBoneIndices[k].b[2] = skin[k].mIndex[2];
        dae.mBoneIndices[k].b[3] = skin[k].mIndex[3];
        dae.mBoneWeights[k] = skin[k].mWeight;
    }

    // skeleton
    dae.mBoneParents.resize(nBones);
    dae.mBoneNames.resize(nBones);
    for (int k = 0; k < nBones; k++) {
        dae.mBoneParents[k] = bones[k].mParent;
        dae.mBoneNames[k] = kBoneTypeNames[bones[k].mType];
    }

    dae.mBindMatrices.clear();
    for (unsigned int k = 0; k < data->mBindPose.size(); k++) {
        dae.mBindMatrices.push_back(data->mBindPose[k].ToMatrix4());
        dae.mBoneMatrices.push_back(data->mBindPose[k].ToMatrix4());
    }
    dae.mBindMatrices.reserve(nBones);
    dae.mBoneMatrices.reserve(nBones);

    if (nBones > 0 && bones[0].mParent == -1) {
        int nRoot = 0;
        while (nRoot < nBones && bones[nRoot].mType == 5)
            nRoot++;
        if (nRoot > 1)
            dae.SetRootBoneCount(nRoot / 2);
    }

    // rigid block models
    for (int i = 0; i < nBones; i++) {
        if (bones[i].mHasModel > 0) {
            EditorBlock* block = data->mpBlocks[i];
            IModelManager* mgr = block->GetModelManager();
            uint32_t id = block->GetModelID();
            bool bSkinned = false;
            int posBase = dae.mPositions.size();
            int normalBase = dae.mNormals.size();
            int uvBase = dae.mUVs.size();
            int boneBase = dae.mBoneParents.size();

            block->InitNonDeformAnimations();
            vector<uint32_t> models((AllocTag()));
            Transform xf;

            if (mgr->GetModelInfo(id, &models, &xf) && !models.empty()) {
                uint32_t key = models[0];
                BakedModelRef baked(new ("Editor", 0, 0, 0, 0) BakedModel(key));
                ApplyModelTransform(&xf, baked.get());
                PrepareModel(baked.get());

                int unused0 = 0;
                int unused1 = 0;
                int usage4 = 0;
                int unusedM0 = -1;
                int unusedM1 = -1;
                int unusedM2 = -1;
                int unusedM3 = -1;
                int unusedM4 = -1;
                int unusedM5 = -1;
                int usages[4];
                usages[0] = 1;   // position
                usages[1] = 2;   // normal
                usages[2] = 8;   // texcoord
                usages[3] = 3;   // tangent
                int formats[4];
                formats[0] = 3;
                formats[1] = 3;
                formats[2] = 2;
                formats[3] = 3;
                int streamIdx[4];
                (void)unused0; (void)unused1; (void)usage4; (void)unusedM0; (void)unusedM1;
                (void)unusedM2; (void)unusedM3; (void)unusedM4; (void)unusedM5;

                if (FindVertexStreams(baked.get(), 4, streamIdx, usages, 0, formats, 0)) {
                    VertexStreamData* pos = &baked.get()->mpStreams[streamIdx[0]].mData;
                    VertexStreamData* nrm = &baked.get()->mpStreams[streamIdx[1]].mData;
                    VertexStreamData* tex = &baked.get()->mpStreams[streamIdx[2]].mData;
                    VertexStreamData* tan = &baked.get()->mpStreams[streamIdx[3]].mData;

                    Matrix3 frame;
                    for (int v = 0; v < pos->mCount; v++) {
                        dae.mPositions.push_back(*(Vector3*)(pos->mpData + pos->mStride * v));

                        Vector2 uv = *(Vector2*)(tex->mpData + tex->mStride * v);
                        if (uv[1] <= 0.0f)
                            uv[1] += 1.0f;
                        uv[0] *= data->mUVRects[i].x1 - data->mUVRects[i].x0;
                        uv[1] *= data->mUVRects[i].y1 - data->mUVRects[i].y0;
                        uv[0] += data->mUVRects[i].x0;
                        uv[1] += data->mUVRects[i].y0;
                        uv[1] = 1.0f - uv[1];
                        dae.mUVs.push_back(uv);

                        frame[1] = *(Vector3*)(nrm->mpData + nrm->mStride * v);
                        frame[2] = *(Vector3*)(tan->mpData + tan->mStride * v);
                        frame[0] = Cross(*(Vector3*)(nrm->mpData + nrm->mStride * v),
                                         *(Vector3*)(tan->mpData + tan->mStride * v));
                        Orthonormalize(&frame);
                        dae.mNormals.push_back(frame[1]);
                        dae.mTangents.push_back(frame[2]);
                        dae.mBinormals.push_back(frame[0]);
                    }

                    int blendIdx = FindVertexStream(baked.get(), 9, -1, 0, 0xe);
                    int blendWgt = FindVertexStream(baked.get(), 10, -1, 0, 0xe);
                    if (blendIdx >= 0 && blendWgt >= 0 && mgr->GetBoneCount(id) > 1) {
                        VertexStream* idxStream = &baked.get()->mpStreams[blendIdx];
                        VertexStream* wgtStream = &baked.get()->mpStreams[blendWgt];
                        Vector4f w;
                        w.w[0] = 1.0f;
                        w.w[1] = 0.0f;
                        w.w[2] = 0.0f;
                        w.w[3] = 0.0f;
                        BoneIdx4 b;
                        b.b[0] = (uint16_t)i;
                        b.b[1] = (uint16_t)i;
                        b.b[2] = (uint16_t)i;
                        b.b[3] = (uint16_t)i;
                        int nInfluences = wgtStream->mType;
                        for (int v = 0; v < pos->mCount; v++) {
                            for (int k = 0; k < nInfluences; k++) {
                                if (idxStream->mType == 7) {
                                    VertexStreamData* d = &idxStream->mData;
                                    b.b[k] = (uint16_t)((int)((uint8_t*)(d->mpData + d->mStride * v))[k] / 3 + boneBase);
                                } else {
                                    VertexStreamData* d = &idxStream->mData;
                                    b.b[k] = (uint16_t)((int)((uint16_t*)(d->mpData + d->mStride * v))[k] / 3 + boneBase);
                                }
                                VertexStreamData* d = &wgtStream->mData;
                                float* wv = (float*)(d->mpData + d->mStride * v);
                                w.w[k] = wv[k];
                            }
                            dae.mBoneIndices.push_back(b);
                            dae.mBoneWeights.push_back(w);
                        }
                        bSkinned = true;
                    } else {
                        BoneIdx4 b;
                        b.b[0] = (uint16_t)i;
                        b.b[1] = (uint16_t)i;
                        b.b[2] = (uint16_t)i;
                        b.b[3] = (uint16_t)i;
                        Vector4f w;
                        w.w[0] = 1.0f;
                        w.w[1] = 0.0f;
                        w.w[2] = 0.0f;
                        w.w[3] = 0.0f;
                        dae.mBoneIndices.resize(dae.mBoneIndices.size() + pos->mCount, b);
                        dae.mBoneWeights.resize(dae.mBoneWeights.size() + pos->mCount, w);
                    }

                    IndexBuffer* ib = &baked.get()->mpIndexBuffers[0];
                    for (int t = 0; t < ib->mCount; t++) {
                        dae.mPosIndices.push_back(
                            (*(uint32_t*)(ib->mpData + ib->mStride * t) & kIndexMask[ib->mFormat]) + posBase);
                        dae.mNormalIndices.push_back(
                            (*(uint32_t*)(ib->mpData + ib->mStride * t) & kIndexMask[ib->mFormat]) + normalBase);
                        dae.mUVIndices.push_back(
                            (*(uint32_t*)(ib->mpData + ib->mStride * t) & kIndexMask[ib->mFormat]) + uvBase);
                    }
                }
            }

            if (bSkinned) {
                Transform boneXf;
                boneXf.SetScale(bones[i].mScale);
                boneXf.SetRotation(bones[i].mRotation);
                boneXf.SetOffset(bones[i].mPosition);

                int nModelBones = mgr->GetBoneCount(id);
                fixed_vector_Matrix43 boneMats(nModelBones);
                fixed_vector_Matrix43 bindMats(nModelBones);
                fixed_vector_int parents(nModelBones);
                mgr->GetBoneMatrices(id, boneMats.mpBegin, 0);
                mgr->GetBindMatrices(id, bindMats.mpBegin);
                mgr->GetBoneParents(id, parents.mpBegin);

                Matrix4 m;
                Matrix4 bind;
                for (int j = 0; j < nModelBones; j++) {
                    Matrix43ToMatrix4(&boneMats[j], &m);
                    Matrix43ToMatrix4(&bindMats[j], &bind);
                    bind = (m * bind) * xf.ToMatrix4();
                    m = m * xf.ToMatrix4();
                    dae.mBindMatrices.push_back(m);
                    dae.mBoneMatrices.push_back(bind);
                    dae.mBoneParents.push_back(parents[j] != -1 ? parents[j] + boneBase : i);
                }
            }
        }
    }

    dae.mBoneNames.resize(dae.mBindMatrices.size(), "internal");
    dae.Finalize0();
    dae.Finalize1();

    EA::IO::FileStream_s0046_29e0 stream(path.c_str());
    stream.Open(2, 2, 1, 0);
    dae.Write(&stream);
    stream.Close();
    return true;
}
}}  // namespace SP::EditorUtils

// @ 0x00464300
void F_00464300()
{}

// @ 0x00464480
void F_00464480()
{}

// @ 0x00464580
void F_00464580()
{}

// @ 0x00464680
void F_00464680()
{}

// @ 0x004647b0
void F_004647b0()
{}

// @ 0x00464bb0
void cBlockGeometryExporter::Export(nSPSkinner::cExportHelper_s0046_4bb0& helper, SP::cSPEditorBlock_s0046_4bb0* block, EA::RectT_s0046_4bb0<float>& uvRect, unsigned int id, bool flag)
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
            cSPVector3_s0046_4bb0* positionDst = &mPositions[vertexBase];
            for (unsigned int j = 0, n = nVerts; j < n; j++) {
                cSPVector3_s0046_4bb0 v(*(const cSPVector3_s0046_4bb0*)srcPositions);
                *positionDst = v;
                positionDst++;
                srcPositions += posStride;
            }

            mNormals.resize(mNormals.size() + srcNormCount);
            ScratchSlots<5>();
            cSPVector3_s0046_4bb0* normalDst = &mNormals[vertexBase];
            for (unsigned int j = 0, n = srcNormCount; j < n; j++) {
                cSPVector3_s0046_4bb0 v(*(const cSPVector3_s0046_4bb0*)normIter);
                *normalDst = v;
                normalDst++;
                normIter += nrmStride;
            }

            if (hasUVs) {
                mTextureCoordinates.resize(mTextureCoordinates.size() + numUV);
                ScratchSlots<4>();
                cSPVector2_s0046_4bb0* uvOut = &mTextureCoordinates[vertexBase];
                for (unsigned int j = 0, n = numUV; j < n; j++) {
                    cSPVector2_s0046_4bb0 v(*(const cSPVector2_s0046_4bb0*)uvData);
                    *uvOut = v;
                    uvOut++;
                    uvData += uvSrcStride;
                }
            } else {
                mTextureCoordinates.resize(mTextureCoordinates.size() + nVerts);
                ScratchSlots<4>();
                for (unsigned int j = 0, n = nVerts; j < n; j++) {
                    mTextureCoordinates[vertexBase + j] = *(cSPVector2_s0046_4bb0*)&mPositions[vertexBase + j];
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
            cSPVector2_s0046_4bb0& uv = mTextureCoordinates[k];
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

    helper.ExportMeshAdd(eastl::pair_s0046_4bb0<unsigned int, unsigned int>(id, 0xffffffff),
                         &mPositions[0], &mNormals[0], &mTextureCoordinates[0],
                         &mTriangleIndices[0], mPositions.size(), mTriangleIndices.size() / 3,
                         12, 12, 8);
    ScratchSlots<8>();
}

// @ 0x004655e0
void cBlockGeometryExporter_s0046_55e0::BuildBoundingBoxGeometry(SP::cSPEditorBlock_s0046_55e0* block)
{
    cSPVector3_s0046_55e0 corners[8];
    block->GetBBox(SP::cSPEditorBlock_s0046_55e0::kBBoxType1, false, false).GetCorners(corners);

    cSPTransform_s0046_55e0 transform;
    transform.SetPosition(block->mPosition);
    transform.SetRotation(block->mOrientation);
    for (int i = 0; i < 8; i++) {
        transform.ApplyToPoint(corners[i]);
    }
    for (int j = 0; j < 24; j++) {
        mTextureCoordinates.push_back(cSPVector2_s0046_55e0::ZERO);
    }

    unsigned int baseIndex = 0;
    cSPVector3_s0046_55e0 normal;

    {
    // face 0-1-2-3
    mPositions.push_back(corners[0]);
    mPositions.push_back(corners[1]);
    mPositions.push_back(corners[2]);
    mPositions.push_back(corners[3]);
    cSPVector3_s0046_55e0 edgeA0;
    edgeA0.CopyConstructInline(corners[3] - corners[1]);
    cSPVector3_s0046_55e0 edgeB0;
    edgeB0.CopyConstructInline(corners[0] - corners[1]);
    normal = Normalize(Cross(edgeB0, edgeA0));
    mNormals.push_back(normal);
    mNormals.push_back(normal);
    mNormals.push_back(normal);
    mNormals.push_back(normal);
    mTriangleIndices.push_back(baseIndex + 2);
    mTriangleIndices.push_back(baseIndex + 1);
    mTriangleIndices.push_back(baseIndex);
    mTriangleIndices.push_back(baseIndex + 1);
    mTriangleIndices.push_back(baseIndex + 2);
    mTriangleIndices.push_back(baseIndex + 3);
    baseIndex += 4;
    }

    {
    // face 1-5-3-7
    mPositions.push_back(corners[1]);
    mPositions.push_back(corners[5]);
    mPositions.push_back(corners[3]);
    mPositions.push_back(corners[7]);
    cSPVector3_s0046_55e0 edgeA1;
    edgeA1.CopyConstructInline(corners[7] - corners[5]);
    cSPVector3_s0046_55e0 edgeB1;
    edgeB1.CopyConstructInline(corners[1] - corners[5]);
    normal = Normalize(Cross(edgeB1, edgeA1));
    mNormals.push_back(normal);
    mNormals.push_back(normal);
    mNormals.push_back(normal);
    mNormals.push_back(normal);
    mTriangleIndices.push_back(baseIndex + 2);
    mTriangleIndices.push_back(baseIndex + 1);
    mTriangleIndices.push_back(baseIndex);
    mTriangleIndices.push_back(baseIndex + 1);
    mTriangleIndices.push_back(baseIndex + 2);
    mTriangleIndices.push_back(baseIndex + 3);
    baseIndex += 4;
    }

    {
    // face 5-4-7-6
    mPositions.push_back(corners[5]);
    mPositions.push_back(corners[4]);
    mPositions.push_back(corners[7]);
    mPositions.push_back(corners[6]);
    cSPVector3_s0046_55e0 edgeA2;
    edgeA2.CopyConstructInline(corners[6] - corners[4]);
    cSPVector3_s0046_55e0 edgeB2 = corners[5] - corners[4];
    normal = Normalize(Cross(edgeB2, edgeA2));
    mNormals.push_back(normal);
    mNormals.push_back(normal);
    mNormals.push_back(normal);
    mNormals.push_back(normal);
    mTriangleIndices.push_back(baseIndex + 2);
    mTriangleIndices.push_back(baseIndex + 1);
    mTriangleIndices.push_back(baseIndex);
    mTriangleIndices.push_back(baseIndex + 1);
    mTriangleIndices.push_back(baseIndex + 2);
    mTriangleIndices.push_back(baseIndex + 3);
    baseIndex += 4;
    }

    {
    // face 3-7-2-6
    mPositions.push_back(corners[3]);
    mPositions.push_back(corners[7]);
    mPositions.push_back(corners[2]);
    mPositions.push_back(corners[6]);
    cSPVector3_s0046_55e0 edgeA3 = corners[6] - corners[7];
    cSPVector3_s0046_55e0 edgeB3 = corners[3] - corners[7];
    normal = Normalize(Cross(edgeB3, edgeA3));
    mNormals.push_back(normal);
    mNormals.push_back(normal);
    mNormals.push_back(normal);
    mNormals.push_back(normal);
    mTriangleIndices.push_back(baseIndex + 2);
    mTriangleIndices.push_back(baseIndex + 1);
    mTriangleIndices.push_back(baseIndex);
    mTriangleIndices.push_back(baseIndex + 1);
    mTriangleIndices.push_back(baseIndex + 2);
    mTriangleIndices.push_back(baseIndex + 3);
    baseIndex += 4;
    }

    {
    // face 4-0-6-2
    mPositions.push_back(corners[4]);
    mPositions.push_back(corners[0]);
    mPositions.push_back(corners[6]);
    mPositions.push_back(corners[2]);
    cSPVector3_s0046_55e0 edgeA4 = corners[2] - corners[0];
    cSPVector3_s0046_55e0 edgeB4 = corners[4] - corners[0];
    normal = Normalize(Cross(edgeB4, edgeA4));
    mNormals.push_back(normal);
    mNormals.push_back(normal);
    mNormals.push_back(normal);
    mNormals.push_back(normal);
    mTriangleIndices.push_back(baseIndex + 2);
    mTriangleIndices.push_back(baseIndex + 1);
    mTriangleIndices.push_back(baseIndex);
    mTriangleIndices.push_back(baseIndex + 1);
    mTriangleIndices.push_back(baseIndex + 2);
    mTriangleIndices.push_back(baseIndex + 3);
    baseIndex += 4;
    }

    {
    // face 0-4-1-5
    mPositions.push_back(corners[0]);
    mPositions.push_back(corners[4]);
    mPositions.push_back(corners[1]);
    mPositions.push_back(corners[5]);
    cSPVector3_s0046_55e0 edgeA5 = corners[5] - corners[4];
    cSPVector3_s0046_55e0 edgeB5 = corners[0] - corners[4];
    normal = Normalize(Cross(edgeB5, edgeA5));
    mNormals.push_back(normal);
    mNormals.push_back(normal);
    mNormals.push_back(normal);
    mNormals.push_back(normal);
    mTriangleIndices.push_back(baseIndex + 2);
    mTriangleIndices.push_back(baseIndex + 1);
    mTriangleIndices.push_back(baseIndex);
    mTriangleIndices.push_back(baseIndex + 1);
    mTriangleIndices.push_back(baseIndex + 2);
    mTriangleIndices.push_back(baseIndex + 3);
    baseIndex += 4;
    }
}

// @ 0x00466690
namespace SP { namespace EditorUtils {
void ExportBakedModelToXMF(EditorModel* model, const wchar_t* dir, ResourceKey* key)
{
    wchar_t nameTmp[260];
    EA::IO::SplitPath(model->GetFileName(), 0, 0, nameTmp, 0, 4);
    wstring_s0046_6320 fullPath(CtorSprintf(), L"%ls/%ls", dir, nameTmp);

    cExportHelper helperObj;
    MeshAccum accumA;
    helperObj.SetName(fullPath.mpBegin);
    helperObj.ExportDummyStaticSkeleton();

    AutoRefCount<IPropList> propsX;
    propsX.mp = 0;
    if (GetPropMgr()->GetPropList(key->instanceID, key->groupID, &propsX)) {
        unsigned int propIdOld = 0xf9efbb;
        Property* propOld = 0;
        if (propsX->GetProperty(propIdOld, &propOld)) {
            ResourceKey* resKeyY = ModelKeyOf(propOld);
            AutoRefCount<IResource> resC;
            resC.mp = 0;
            if (GetManager()->GetResource(resKeyY, &resC, 0, 0, 0, 0)) {
                Transform_s0046_6320 xfD;
                ModelVec modelsC((AllocTag()));
                IResource* rA = resC.mp;

                RefPtr<ModelRoot> rootTmp(new ("Graphics", 0, 0, 0, 0) ModelRoot());
                RefPtr<ModelInst> instC(new ("Graphics", 0, 0, 0, 0) ModelInst());
                rootTmp.mpObject->Init(rA);
                instC.mpObject->SetFlags(false, false);
                instC.mpObject->ConstructFromGameModelResource(rA);
                ModelInst* instArg = instC.mpObject;
                rootTmp.mpObject->SetInstance(instArg);
                rootTmp.mpObject->Collect(&xfD, &modelsC);
                for (ModelPtr* itObj = modelsC.mpBegin; itObj != modelsC.end(); ++itObj)
                    PrepareModel_s0046_6320(itObj->mpObject);

                helperObj.ExportMeshBegin(1, false);
                accumA.Export(&helperObj, modelsC);
                helperObj.ExportMeshEnd();

                TexId diffuseIdCur; diffuseIdCur.lo = -1; diffuseIdCur.hi = -1;
                TexId normalId2;  normalId2.lo = -1;  normalId2.hi = -1;
                TexId bakeNew;    bakeNew.lo = -1;    bakeNew.hi = -1;
                GetTexIdMgr()->GetDiffuseId(&diffuseIdCur);
                Tex* tex = GetTexLookup()->GetTexture(diffuseIdCur.lo, diffuseIdCur.hi);
                GetTexIdMgr()->GetNormalId(&normalId2);
                Tex* imgTmp = GetTexLookup()->GetTexture(normalId2.lo, normalId2.hi);
                GetTexIdMgr()->GetBakeInfoId(&bakeNew);
                Tex* bakeTmp = GetTexLookup()->GetTexture(bakeNew.lo, bakeNew.hi);

                cstring diffuseNameD(CtorSprintf(), "%ls/%ls_Diffuse.tga", dir, nameTmp);
                SaveTga7b2380(diffuseNameD.mpBegin, DataOf(tex));
                cstring normalName2(CtorSprintf(), "%ls/%ls_NormalMap.tga", dir, nameTmp);
                SaveTga7b2380(normalName2.mpBegin, DataOf(imgTmp));
                cstring bakeNameX(CtorSprintf(), "%ls/%ls_BakeInfoMap.tga", dir, nameTmp);
                SaveTga7b2380(bakeNameX.mpBegin, DataOf(bakeTmp));
            }
        }
    }
}
}}  // namespace SP::EditorUtils

// @ 0x00466e20
void MeshAccum_s0046_6e20::Export(cExportHelper_s0046_6e20* helper, const ModelVec_s0046_6e20& models)
{
    mIndices.clear();
    mPositions.clear();
    mNormals.clear();
    mUVs.clear();
    int total = 0;
    int vert = 0;
    for (unsigned int i = 0, n = models.size(); i < n; i++) {
        int count = 0;
        Model* model = models[i];
        int fmts[4] = { 1, 2, 8, 8 };
        int counts[4] = { 3, 3, 2, 2 };
        int idx[4];
        FUN_0071ded0(model, 4, idx, fmts, 0, counts, 0);
        ArrF* sPos = &model->entries[idx[0]].stream;
        ArrF* sNrm = &model->entries[idx[1]].stream;
        ArrF* sTan = &model->entries[idx[2]].stream;
        ArrF* sUV = &model->entries[idx[3]].stream;
        for (int j = 0, nSec = model->mSections.size(); j < nSec; j++) {
            Section* sec = &model->mSections.mpBegin[j];
            int fPos = FindFormatEntry(model, j, idx[0]);
            int fNrm = FindFormatEntry(model, j, idx[1]);
            int fTan = FindFormatEntry(model, j, idx[2]);
            int fUV = FindFormatEntry(model, j, idx[3]);
            VecInt prims((sp_vector_allocator_s0046_6e20()));
            FindPrimitives(model, &prims, j, 4, -1);
            for (int k = 0, nPrims = prims.size(); k < nPrims; k++) {
                ArrG* prim = &model->mPrims[prims[k]];
                int nTri = prim->f();
                int start = prim->b;
                if (!sec->HasStreams()) {
                    for (int t = 0; t < nTri; t++) {
                        unsigned int i0 = sec->indices.getI(start++);
                        unsigned int i1 = sec->indices.getI(start++);
                        unsigned int i2 = sec->indices.getI(start++);
                        mPositions.push_back(*(Vec3*)sPos->atI(i0));
                        mPositions.push_back(*(Vec3*)sPos->atI(i1));
                        mPositions.push_back(*(Vec3*)sPos->atI(i2));
                        mNormals.push_back(*(Vec3*)sNrm->atI(i0));
                        mNormals.push_back(*(Vec3*)sNrm->atI(i1));
                        mNormals.push_back(*(Vec3*)sNrm->atI(i2));
                        mUVs.push_back(*(Vec2*)sUV->atI(i0));
                        mUVs.push_back(*(Vec2*)sUV->atI(i1));
                        mUVs.push_back(*(Vec2*)sUV->atI(i2));
                        mIndices.push_back(vert++);
                        mIndices.push_back(vert++);
                        mIndices.push_back(vert++);
                        count += 3;
                    }
                } else {
                    ArrF* tPos = &sec->mStreams.mpBegin[sec->mFormat[fPos].stream];
                    ArrF* tNrm = &sec->mStreams.mpBegin[sec->mFormat[fNrm].stream];
                    ArrF* tUV = &sec->mStreams.mpBegin[sec->mFormat[fUV].stream];
                    for (int t = 0; t < nTri; t++) {
                        unsigned int i0 = sec->indices.get(start++);
                        unsigned int i1 = sec->indices.get(start++);
                        unsigned int i2 = sec->indices.get(start++);
                        unsigned int p0 = tPos->get(i0);
                        unsigned int p1 = tPos->get(i1);
                        unsigned int p2 = tPos->get(i2);
                        unsigned int n0 = tNrm->get(i0);
                        unsigned int n1 = tNrm->get(i1);
                        unsigned int n2 = tNrm->get(i2);
                        unsigned int u0 = tUV->get(i0);
                        unsigned int u1 = tUV->get(i1);
                        unsigned int u2 = tUV->get(i2);
                        mPositions.push_back(*(Vec3*)sPos->atI(p0));
                        mPositions.push_back(*(Vec3*)sPos->at(p1));
                        mPositions.push_back(*(Vec3*)sPos->at(p2));
                        mNormals.push_back(*(Vec3*)sNrm->at(n0));
                        mNormals.push_back(*(Vec3*)sNrm->at(n1));
                        mNormals.push_back(*(Vec3*)sNrm->at(n2));
                        mUVs.push_back(*(Vec2*)sUV->at(u0));
                        mUVs.push_back(*(Vec2*)sUV->at(u1));
                        mUVs.push_back(*(Vec2*)sUV->at(u2));
                        mIndices.push_back(vert++);
                        mIndices.push_back(vert++);
                        mIndices.push_back(vert++);
                        count += 3;
                    }
                }
            }
        }
        total += count;
    }
    for (int u = 0, nUV = mUVs.size(); u < nUV; u++) {
        Vec2& uv = mUVs.mpBegin[u];
        if (uv[1] <= 0.0f)
            uv[1] += 1.0f;
    }
    int bidx = -1;
    int nidx = 0;
    helper->ExportMeshAdd(NodeBone(nidx, bidx), &mPositions[0].x, &mNormals[0].x, &mUVs[0].x, &mIndices[0],
                          mPositions.size(), mIndices.size() / 3, 0xc, 0xc, 8);
}

// @ 0x00467980
unsigned int ArrF::get(int i)
{
    return *(unsigned int*)(data + stride * i) & maskTable[maskIdx];
}

// @ 0x004679b0
int ArrG::f()
{
    if (idx <= 0 || idx >= 10)
        return 0;
    if (idx == 9)
        return 1;
    int v9 = a - b;
    int t10 = tableA[idx];
    int cap = tableB[idx];
    return (v9 + t10) / cap;
}

// @ 0x00467a20
void F_00467a20()
{}

// @ 0x00467ef0
void F_00467ef0()
{}

// @ 0x004680c0
bool MeshUploadJob::Run(cJob* pDependency)
{
    ModelMesh* mNormals = mpMesh;
    Elem8c* rest = GetHolder()->mElems.mpBegin;
    int kind = GetHolder()->mElems.size();

    mSpans.push_back(SizedSpan(mBytesEnd - mBytesBegin, mBytesBegin));

    Vector3_s0046_80c0 mBoneWeights(mOffset);
    Vector3_s0046_80c0* mStride = mNormals->mPositions.mpBegin;
    for (int i = 0, n = mNormals->mPositions.size(); i < n; i++)
        Vector3_Add(&mStride[i], &mBoneWeights);

    ScratchSlots<2>();
    if (((EmptyCheck*)&mNormals->mIndices)->empty()) {
        // empty mesh: one degenerate triangle
        mNormals->mIndices.resize(3, 0);
        mNormals->mPositions.push_back(Vector3_s0046_80c0(0.0f, 0.0f, 0.0f));
        mNormals->mNormals.push_back(Vector3_s0046_80c0(0.0f, 0.0f, 1.0f));
        mNormals->mTangents.push_back(Vector3_s0046_80c0(0.0f, 1.0f, 0.0f));
        mNormals->mTexCoords.push_back(Vector2_s0046_80c0(0.0f, 0.0f));
        mNormals->mBoneWeights.clear();
        mNormals->mBoneIndices.clear();
    }

    mVertexCounts.push_back(mNormals->mPositions.size());
    mPartRanges.push_back(mNormals->mIndices.size());

    bool mTexCoords = false;
    ScratchSlots<2>();
    MeshGroupRef mSlot(new ("Editor", 0, 0, 0, 0) MeshGroup());
    mSlot->mBatches.push_back();
    Batch* mUsage = &mSlot->mBatches.back();
    IndexVec* mAllocator = &mUsage->mStreamIndices;
    StreamVec_s0046_80c0* mPositions = &mSlot->mStreams;
    mAllocator->reserve(8);
    mPositions->reserve(8);

    ADD_STREAM(mNormals->mPositions, 0xc, 1, 0, 3, 0)
    ADD_STREAM(mNormals->mNormals, 0xc, 2, 0, 3, 1)
    ADD_STREAM(mNormals->mTexCoords, 8, 8, 0, 2, 2)
    ADD_STREAM(mNormals->mTangents, 0xc, 3, 0, 3, 2)

    if (!((EmptyCheck*)&mNormals->mBoneWeights)->empty()) {
        ADD_STREAM(mNormals->mBoneWeights, 8, 9, 0, 9, 0)
        mAllocator->push_back(StreamIndex(mPositions->size(), -1));
        mPositions->push_back_no_inline(StreamElem(10, 0, 4, 0, StreamDesc(mNormals->mBoneIndices, mNormals, 0x10)));
        if (!((EmptyCheck*)&mNormals->mExtra)->empty()) {
            mAllocator->push_back_no_inline(StreamIndex(mPositions->size(), -1));
            mPositions->push_back_no_inline(StreamElemC(0x18, 0, 6, 5, StreamDesc(&mNormals->mExtra, mNormals, 0)));
        }
        PaletteRef palette(new ("Editor", 0, 0, 0, 0) BonePalette());
        palette->mBones.assign(mVertexCounts.begin(), mVertexCounts.end());
        mAllocator->push_back_no_inline(StreamIndex(mPositions->count(), -1));
        mPositions->push_back_no_inline(StreamElemC(0x19, 0, 6, 0xb, palette->GetDesc()));
    }

    int owner = mNormals->mIndices.count();
    mUsage->mVertexCount = mNormals->mPositions.count();
    mUsage->SetIndices(StreamDesc(owner, mNormals->mIndices.data(), mNormals, 0));
    mPositions->push_back_no_inline(StreamElemC(0x15, 0, 6, 8, StreamDesc(1, mNormals->mBonePalette, mNormals, 0)));

    for (int i = 1, n = mPartRanges.count(); i < n; i++)
        mSlot->mRanges.push_back(IndexRange(4, 0, mPartRanges[i - 1], mPartRanges[i], 0));

    MeshGroupList mDesc(1, mSlot);
    JobLock mVertexCount(GetJobManager());

    if (pDependency == 0) {
        GetJobManager()->AddJob(mJob.Reset());
        GetJob();
    }

    uint32_t hi = WithVariant(mTypeID, 0xe3);
    JobRef mnRefCount;
    ObjectRef mBatches;
    if (PropertyManager()->GetPropertyList(0x4529f96f, hi, mBatches.Reset()))
        LoadPropertyListJob(mnRefCount.Reset(), mBatches.get(), &mDesc, mInstanceID, hi, GetC8(), mJob.get());

    ResourceKey_s0046_80c0 mType;
    if (g_bUseAltModelKey && IsKind1(GetTypeID())) {
        if (TypeID(GetTypeID()).Variant() == 0x62) {
            mType.instanceID.value = mInstanceID;
            mType.groupID = WithVariant(mTypeID, 0x71);
            mType.typeID = 0xffffffff;
        }
    }

    JobRef mpBegin;
    if (!GetModelAsGameMeshes(mpBegin.Reset(), &mDesc, mInstanceID, mTypeID, GetC8(), 0, 0, &mOut1b4, &mSpans,
                              0, mType.instanceID.value ? &mType : 0,
                              (mnRefCount.p ? mnRefCount : mJob).get())) {
        return false;
    }

    if (mnRefCount.p)
        mnRefCount->Queue();
    if (pDependency == 0) {
        mpBegin->Queue();
        mJob->Queue();
        mJob->Wait();
        mJob = 0;
    } else {
        mpBegin->AddDependency(pDependency);
        mpBegin->Queue();
    }
    return true;
}

// @ 0x00469500
S45a::S45a(int a_, int b_, int c_, int d_, int e_)
: a(a_), b(b_), c(c_), d(d_), sub(e_)
{
    int hole_;
    (void)hole_;
}

// @ 0x00469550
S45b* S45b::init(int a_, int b_, int c_, int d_, int e_)
{
    a = a_;
    b = b_;
    c = c_;
    d = d_;
    e = e_;
    return this;
}

// @ 0x00469590
void F_00469590()
{}

// @ 0x004696d0
S45c& S45c::operator=(const S45c& o)
{
    m0 = o.m0;
    m1 = o.m1;
    m2 = o.m2;
    m3 = o.m3;
    m4 = o.m4;
    m5 = o.m5;
    m6 = o.m6;
    return *this;
}

// @ 0x00469790
void F_00469790()
{}

// @ 0x00469920
void F_00469920()
{}

// @ 0x00469bb0
void BuildEditorCreature(EdCtx* ed, KeyArg* key, int p3, uint32_t p4, uint32_t p5, CJob* p6)
{
    bool isBaby = false;
    if (p4 != 0 && p5 != 0 && KindOf(p5) == 0x62)
        isBaby = true;
    CPart* srcParts = ed->Creature()->m98.mpBegin;
    int nParts = ed->Creature()->m98.size();
    IPtr<EBuildObj> pMain(new ("Editor", 0, 0, 0, 0) EBuildObj());
    if (!PrepareBuild(ed, pMain))
        return;
    pMain.mp->mId = 0xd7be35f9;
    IPtr<EBuildObj2> pAux;
    if (p4 != 0)
        pAux = new ("Editor", 0, 0, 0, 0) EBuildObj2(pMain);
    ThreadedPtr job(new ("Editor", 0, 0, 0, 0) ThreadedObj());
    AtomicPtr ref1;
    AtomicPtr ref2;
    RegisterModels(key->instance, key->flags, &ref2, &ref1, (char*)ed->mpCreature + 0x38);
    BuildMaterialInfo(job.mp, key->id, ref1, ref2, gMatParam, 0);
    ed->jobSlot.Set(job.mp);
    JobPtr job3;
    JobPtr job2;
    JobPtr job1;
    if (isBaby) {
        uint32_t flags = WithClass(p5, 1);
        IPtr<S630> pBaby(new ("Editor", 0, 0, 0, 0) S630(*ed->mpCreature));
        IPtr<EBuildObj2> pBabyAux(new ("Editor", 0, 0, 0, 0) EBuildObj2(pMain));
        uint64_t inst = key->instance;
        pBaby.mp->key[0] = (uint32_t)inst;
        pBaby.mp->key[1] = 0x2b978c46;
        pBaby.mp->key[2] = flags;
        MakeBabyRuntimeCreature(pBaby);
        XformVec::Tag tag;
        XformVec xf(tag);
        xf.Init();
        xf.resize(nParts);
        for (int i = 0; i < nParts; i++) {
            XformTmp t;
            t.SetScale(srcParts[i].scale);
            t.SetRotation(srcParts[i].rot);
            t.SetPosition(srcParts[i].pos);
            t.Invert();
            t.ScaleBy(pBaby->m98.mpBegin[i].scale);
            t.ApplyRot(&pBaby->m98.mpBegin[i].rot);
            AddPos(&t.pos, &pBaby->m98.mpBegin[i].pos);
            t.MarkPos();
            t.Assign(xf.mpBegin + i * 0x38);
        }
        BuildModel(key->instance, flags, pBaby, pBabyAux, p3, job.get(), kBuildTag, 1, xf.mpBegin, &job1, p6);
        p6 = job1.mp;
        xf.Free();
    }
    if (p4 != 0)
        BuildModel(key->instance, p4, ed->mpCreature, pAux, p3, job.get(), kBuildTag, 0, 0, &job2, p6);
    BuildModel(key->instance, p5, ed->mpCreature, pMain, p3, job.get(), kBuildTag, 1, 0, &job3, job2.mp);
    if (job1.mp)
        job1.mp->Flush();
    if (job2.mp)
        job2.mp->Flush();
    if (job3.mp)
        job3.mp->Flush();
    if (job1.mp)
        job1.mp->Release();
    if (job2.mp)
        job2.mp->Release();
    if (job3.mp)
        job3.mp->Release();
}

// @ 0x0046a510
void F_0046a510()
{}

// @ 0x0046a630
S630::S630(const S630& o)
: B750(o), m18(o.m18), m98(o.m98), mAc(o.mAc), mC0(o.mC0), mD4(o.mD4), mE8(o.mE8),
      mFc(o.mFc), f110(o.f110), m114(o.m114)
{
    ScratchSlots_s0046_9bb0<4>();
}

// @ 0x0046a750
void F_0046a750()
{}

// @ 0x0046a7c0
// M18real copy constructor (implicit): the forcing function below makes the compiler emit it out of line
#pragma auto_inline(off)
void rwForceEmit_M18real_copy(const M18real& s)
{
    M18real c(s);
}
#pragma auto_inline(on)

// @ 0x0046a8a0
namespace SP {
namespace EditorUtils {
void MakeBabyRuntimeCreature(SP::cRuntimeCreatureResource * a1)
{}
}
}  // namespace SP::EditorUtils

// @ 0x0046aac0
void BuildRuntimeCreature(Editor* ed, MakeOutput* out, bool baby, ThreadedObject** pJob)
{
    Creature* pCreature = new ("Editor", 0, 0, 0, 0) Creature(ed->ctx);
    if (pCreature != out->creature.mp) {
        Creature* old = out->creature.mp;
        if (pCreature)
            pCreature->AddRef();
        out->creature.mp = pCreature;
        if (old)
            old->Release();
    }
    Vector3_s0046_aac0 zero;
    zero.x = 0;
    zero.y = 0;
    zero.z = 0;
    out->creature->pos = zero;
    if (baby)
        MakeBabyRuntimeCreature(out->creature);

    CreaturePart* parts = out->creature->parts.mpBegin;
    int n = (int)((char*)out->creature->parts.mpEnd - (char*)out->creature->parts.mpBegin) / 0x8c;
    Tag tag;
    BBoxVec boxes(tag);
    boxes.Init();
    boxes.reserve(n);
    for (int i = 0; i < n; i++) {
        BBox bb;
        ed->blocks[i]->GetBBox(&bb, 2, 1, 0);
        BBoxTransform xf;
        xf.SetScale(parts[i].scale);
        xf.SetRotation(parts[i].rot);
        xf.SetPosition(parts[i].pos);
        bb.TransformBy(&xf);
        boxes.push_back(bb);
    }
    Vector3_s0046_aac0 offset(0, 0, 0);
    GetTranslationOffset(&offset, &boxes, 0, out->creature);

    ResKey key;
    key.a = 0;
    key.b = 0;
    key.c = 0;
    IDGenerator()->Generate(&key, 0xb1b104, 0x62, 0, 0x72, 0);

    JobRef_s0046_aac0 job;
    if (pJob) {
        job = new ("Editor", 0, 0, 0, 0) ThreadedObject();
    }
    BuildRef obj;
    obj.mp = new ("Editor", 0, 0, 0, 0) BuildObject();
    if (obj.mp)
        obj.mp->AddRef();
    if (!PrepareBuild(ed, obj.mp)) {
        return;
    }
    obj.mp->mId = 0xd7be35f9;
    IHolder list;
    LoadKeyDefault(key.a, key.c, 0);
    PropertyManager_s0046_aac0()->LoadProperties(key.a, key.c, list.Reset());
    BuildModelResource(key.a, key.c, ed->ctx, obj.mp, 0, job.mp, &offset, 0, 0, 0, 0);
    {
        IPropertyList* props = (IPropertyList*)list.p;
        bool t = true;
        props->SetProperty(0x3704e55, Variant(t));
    }
    Model_s0046_aac0* m = GetCreator()->GetHost()->GetModel(key.a, key.c, 0);
    {
        Model_s0046_aac0** slot = &out->model;
        if (m != *slot) {
            Model_s0046_aac0* old = *slot;
            if (m)
                m->AddRef();
            *slot = m;
            if (old)
                old->Release();
        }
    }
    ((IModelNotify*)out->model->pOwner)->Notify(out->model, 0);
    out->job.Set(job.mp);

    int j = 0;
    int pn = (int)((char*)out->creature->parts.mpEnd - (char*)out->creature->parts.mpBegin) / 0x8c;
    for (; j < pn; j++)
        PartPosAdd(&out->creature->parts.mpBegin[j].pos, &offset);

    if (pJob) {
        ThreadedObject* t = job.mp;
        job.mp = 0;
        *pJob = t;
    }
    ReserveModels((void*)&out->modelsBegin, n);
    ResizeRefVec(out->refVec, n);
    for (int k = 0; k < n; k++) {
        if (!ed->blocks[k]->IsSet(10)) {
            Model_s0046_aac0* bm = ed->blocks[k]->pModel;
            Model_s0046_aac0** slot = &out->modelsBegin[k];
            if (bm != *slot) {
                Model_s0046_aac0* old = *slot;
                if (bm)
                    bm->AddRef();
                *slot = bm;
                if (old)
                    old->Release();
            }
        }
    }
    bool isVerb = InitVerbCollection(ed->ctx->pAssetView) == 0x3d97a8e4;
    out->bIsVerbCollection = isVerb;
}

// @ 0x0046b460
void ReplaceModelsWithCopies(ModelListObj* self)
{
    int count = 1;
    int p24 = 0;
    int cap = self->models.size();
    for (; p24 < cap; p24++) {
        AutoRef<Model_s0046_aac0> pModel(self->models[p24]);
        if (pModel) {
            ResKey v33;
            IModelOwner* n40 = pModel->pOwner;
            v33.a = 0xffffffff;
            v33.b = 0xffffffff;
            v33.c = 0xffffffff;
            IHolder len;
            if (!n40->LoadModel(self->models[p24].get(), len.Reset(), &v33)) {
                ResKey t38;
                t38.a = count;
                t38.b = 0xe6bce5;
                t38.c = 0x5ef992e;
                count++;
                BuildKeyHelper(&t38, len.p);
                AutoRef<cPropertyList> n21(new ("Editor", 0, 0, 0, 0) cPropertyList());
                n21->SetParent(pModel->GetParent());
                n21->SetProperty(0xf9efbb, Variant(t38));
                PropertyManager_s0046_aac0()->RegisterList(n21, t38.a, t38.c);
                AutoRef<Model_s0046_aac0> n12(n40->CreateModel(t38.a, t38.c, 2));
                if (n12) {
                    n12->transform = pModel->transform;
                    n12->extra = pModel->extra;
                    self->models[p24] = n12;
                }
                ScratchSlots<4>();
            }
        }
    }
}

// @ 0x0046b7b0
bool BlockOrAncestorHasFlag(Block* b)
{
    if (!b)
        return false;
    if (b->IsSet(7) || b->IsSet(8) || b->IsSet(0x23))
        return true;
    else
        return BlockOrAncestorHasFlag(b->GetParent());
}

// @ 0x0046b8e0
extern "C" Vector3T* FUN_0046b8e0(Vector3T* out, cSPEditorModel* model, int flags)
{
    float vSum = kZero;
    cSPVector3_s0046_b8e0 sumC(kZeroPos);
    float best = kFltMax;
    float lowZ = kFltMax;
    bool useAlt = false;
    float bottom2 = lowZ;
    for (int i = 0, num = model->GetCount(); i < num; i++) {
        cSPEditorBlock* block = model->GetBlock(i);
        if (BlockOrAncestorHasFlag(block)) {
            cSPBoundingBox_s0046_b8e0 bb = block->GetBBox(0, true, false);
            bool isD = block->mFlags.test(7);
            bool isE = block->mFlags.test(8);
            bool f0 = block->mFlags.test(0);
            bool f23 = block->mFlags.test(0x23);
            bool a = block->mFlags.test(0x2d);
            useAlt = useAlt || a;
            bool add = false;
            if (flags & 0x10) {
                if (isD) {
                    float y = block->mPosition[1];
                    if (best > y) {
                        best = y;
                        sumC = block->mPosition;
                        vSum = kOne;
                    }
                }
            } else if (flags & 0x20) {
                if (isD || isE || f23)
                    add = true;
            } else {
                add = true;
            }
            if (add) {
                float sx = Abs(bb.mMax[0] - bb.mMin[0]);
                float ly = Abs(bb.mMax[1] - bb.mMin[1]);
                float lz = Abs(bb.mMax[2] - bb.mMin[2]);
                float v = sx * ly * lz;
                vSum += v;
                                Vector3T t1, t2;
                Vector3_Add(&sumC, Vector3_Scale(&t2, bb.GetCenter(&t1), &v));
            }
            if (lowZ > bb.mMin[2])
                lowZ = bb.mMin[2];
            if (a) {
                if (bottom2 > bb.mMin[2])
                    bottom2 = bb.mMin[2];
            }
        }
    }
    cSPVector3_s0046_b8e0 result((const Vector3T&)kZeroPos);
    if (vSum > kZero) {
                Vector3T t3, t4;
        cSPVector3_s0046_b8e0 center(*Vector3_Div(&t3, &sumC, &vSum));
        cSPVector3_s0046_b8e0 off(*Vector3_Negate(&t4, &center));
        float lift = -(useAlt ? bottom2 : lowZ);
        if ((flags & 1) && kZero >= lift)
            result[2] += lift;
        if (flags & 2)
            result[0] += off[0];
        if (flags & 4)
            result[1] += off[1];
        if (flags & 8)
            result[2] += off[2];
        if (flags & 0x10) {
            result = off;
        }
    }
    out->x = result.x;
    out->y = result.y;
    out->z = result.z;
    return out;
}

// @ 0x0046bfd0
int FUN_0046bfd0(int a, int b)
{
    FUN_0046b8e0((Vector3T*)a, (cSPEditorModel*)b, ((Tbfd*)b)->m());
    return a;
}

// @ 0x0046c000
Vector3Copyable GetTranslationOffset(BoxVec* boxes, EditorModel_s0046_c000* model, Creature_s0046_c000* creature)
{
    float volumeSum = kZero;
    Vector3Copyable weighted(kZeroPos_s0046_c000);
    float minHistY = kFltMax;
    float minZ = kFltMax;
    bool anyFlag = false;
    float minZFlag = minZ;
    uint32_t typeId = model ? model->typeID : creature->typeID;
    uint32_t remapped = RemapTypeId(typeId);
    if (remapped == 0xffffffff)
        return kZeroPos_s0046_c000;

    AutoRefCount_s0046_c000<PropertyList> modeList;
    PropertyManager_s0046_c000()->GetPropertyList(remapped, kPropGroup, modeList.AsPPVoidParam());
    uint32_t flags = 0;
    GetUIntProp(modeList, 0x51ce36a, flags);

    int count = model ? model->parts.size() : creature->parts.size();

    for (int i = 0; i < count; i++) {
        Vector3Copyable offset(kZeroPos_s0046_c000);
        ResKey_s0046_c000 key;
        if (model) {
            key.instanceID = model->parts.mpBegin[i].instanceID;
            key.groupID = model->parts.mpBegin[i].groupID;
            offset = model->parts.mpBegin[i].pos;
        } else {
            key.instanceID = creature->parts.mpBegin[i].instanceID;
            key.groupID = creature->parts.mpBegin[i].groupID;
            offset = creature->parts.mpBegin[i].pos;
        }
        BoundingBox box(boxes->mpBegin[i]);

        AutoRefCount_s0046_c000<PropertyList> partList;
        PropertyManager_s0046_c000()->GetPropertyList(key.instanceID, key.groupID, partList.AsPPVoidParam());
        const uint32_t kPropHasFlag = 0xafff3a14;
        const uint32_t kPropBoolA = 0xd8800eb;
        const uint32_t kPropBoolB = 0x8e31d974;
        const uint32_t kPropBoolC = 0x4a33896;
        bool hasFlag = partList->HasProperty(kPropHasFlag);
        bool boolA = false;
        GetBoolProp(partList, kPropBoolA, boolA);
        bool boolB = false;
        GetBoolProperty(partList, kPropBoolB, &boolB);
        bool boolC = false;
        GetBoolProperty(partList, kPropBoolC, &boolC);
        anyFlag = (anyFlag || boolC) ? true : false;

        bool accumulate = false;
        if (flags & 0x10) {
            if (hasFlag) {
                float yHist = offset[1];
                if (minHistY > yHist) {
                    minHistY = yHist;
                    weighted = offset;
                    volumeSum = kOne;
                }
            }
        } else if (flags & 0x20) {
            if (hasFlag || boolA || boolB)
                accumulate = true;
        } else {
            accumulate = true;
        }
        if (accumulate) {
            float sx = Abs_s0046_c000(box.max[0] - box.min[0]);
            float sy = Abs_s0046_c000(box.max[1] - box.min[1]);
            float sz = Abs_s0046_c000(box.max[2] - box.min[2]);
            float vol = sx * sy * sz;
            volumeSum += vol;
            Vector3_s0046_c000 center;
            weighted += box.GetCenter(center) * vol;
        }
        if (minZ > box.min[2])
            minZ = box.min[2];
        if (boolC) {
            if (minZFlag > box.min[2])
                minZFlag = box.min[2];
        }
    }

    Vector3_s0046_c000 result(kZeroPos_s0046_c000);
    if (volumeSum > kZero) {
        Vector3_s0046_c000 c = weighted / volumeSum;
        Vector3_s0046_c000 neg = -c;
        float zoff = -(anyFlag ? minZFlag : minZ);
        if ((flags & 1) && kZero >= zoff)
            result[2] += zoff;
        if (flags & 2)
            result[0] += neg[0];
        if (flags & 4)
            result[1] += neg[1];
        if (flags & 8)
            result[2] += neg[2];
        if (flags & 0x10) {
            result.x = neg.x;
            result.y = neg.y;
            result.z = neg.z;
        }
    }
    return result;
}

// @ 0x0046c900
namespace SP { namespace EditorUtils {
void CreateExportCreatureModel(cSkin* pSkin, const wchar_t* modelpath, ExportModel* pExportModel, SkeletonHelper* helper, bool ignorePartModels)
{
    string16 tempString;
    tempString.reserve(0x100);

    SkinBone* blocks = pSkin->GetSkinData()->mBones.mpBegin;
    int numBlocks = pSkin->GetSkinData()->mBones.size();
    cBlock** pBlocks = pSkin->mpBlocks;
    ExportModel* pModel = pExportModel;

    pModel->mVersion = 5;
    pModel->mModelPath.assign(modelpath);
    pModel->mJoints.clear();
    if (!pModel->mpMesh.get())
        pModel->mpMesh = GetExportFactory()->CreateMesh();
    pModel->mbRootFirst = false;
    pModel->mRootIndex = 0;

    int idxPlantRoot = -1;
    if (numBlocks > 0 && blocks[0].mParent != -1) {
        idxPlantRoot = blocks[0].mParent;
        if ((uint32_t)idxPlantRoot >= (uint32_t)numBlocks || blocks[idxPlantRoot].mType != 4)
            idxPlantRoot = -1;
        else
            pModel->mRootIndex = idxPlantRoot;
    }

    if (helper) {
        int rootGroup = helper->mRootGroup;
        pModel->mRootIndex = helper->GetGroup(rootGroup).mBlocks[0];
        for (int ii = 0, numInGroup = helper->GetGroup(rootGroup).mBlocks.size(); ii < numInGroup; ++ii) {
            int index = helper->GetGroup(rootGroup).mBlocks[ii];
            if (index < numBlocks && pBlocks[index]->mFlags.test(7)) {
                pModel->mRootIndex = index;
                break;
            }
        }
    }

    pModel->mJoints.resize(numBlocks);
    for (int i = 0; i < numBlocks; ++i) {
        ExportJoint* joint = &pModel->mJoints.mpBegin[i];
        joint->mVersion = 5;

        int blockindex = i;
        if (idxPlantRoot != -1) {
            if (i == 0) {
                blockindex = idxPlantRoot;
                pModel->mbRootFirst = true;
            } else if (i <= idxPlantRoot) {
                blockindex = i - 1;
            }
        }

        cBlock* pBlock = pBlocks[blockindex];
        SkinBone* pBlockData = &pSkin->GetSkinData()->mBones.mpBegin[blockindex];

        string16 resName;
        EA::ResourceMan::GetManager()->GetFileName(pBlock->GetResource()->mKey, resName);
        EA::StdC::Strncpy(joint->mFileName, resName.mpBegin, 0x50);

        joint->mModelIDA = pBlock->GetModelIDA();
        joint->mModelIDB = pBlock->GetModelIDB();
        joint->mBlockIndex = pBlockData->mBlockIndex;
        joint->mParent = pBlockData->mParent;
        if (pBlockData->mFlags & 0x1000)
            joint->mSymmetric = -1;
        else
            joint->mSymmetric = pBlockData->mSymmetric;
        joint->mPartIndex = pBlockData->mPartIndex == 0 ? -1 : pBlockData->mPartIndex;

        if (pBlock->mFlags.test(7) && pBlock->GetParent() != 0)
            joint->mCenter = 0.5f * (pBlock->mPosition + pBlock->GetParent()->mPosition);
        else
            joint->mCenter = pBlock->mPosition;

        Snprintf8(joint->mJointName, 0x28, "joint_b%d_n%d", pBlockData->mBlockIndex, pBlockData->mNodeIndex);
        joint->mBonePosition = kZeroVector;
        joint->mOffset = pBlockData->mOffset;

        if (helper) {
            if (joint->mPartIndex == -1) {
                Snprintf8(joint->mJointName, 0x28, "joint_bone_%d", blockindex);
                joint->mBonePosition = helper->mpBones[blockindex].mPosition;
            } else {
                int nodeIndex = pBlockData->mNodeIndex;
                int nodeIdx = helper->mpGroups[nodeIndex].mNode;
                HelperNode* pN = &helper->mpNodes[nodeIdx];
                switch (pN->mType) {
                case 3:
                    Snprintf8(joint->mJointName, 0x28, "joint_eenode_%d", nodeIndex);
                    break;
                case 2:
                    Snprintf8(joint->mJointName, 0x28, "joint_fakenode_%d", nodeIndex);
                    break;
                case 0:
                    Snprintf8(joint->mJointName, 0x28, "joint_rootnode_%d", nodeIndex);
                    break;
                case 1:
                    if (!helper->mpBones[pN->mBone].mbConnected)
                        Snprintf8(joint->mJointName, 0x28, "joint_bone_%d", pN->mBone);
                    else
                        Snprintf8(joint->mJointName, 0x28, "joint_connbone_%d", pN->mBone);
                    break;
                }
                Vector3_s0046_c900 np = TransformToGroup(helper->GetGroup(nodeIndex), pBlock->mPosition);
                joint->mBonePosition = np;
            }
        }

        Vector3_s0046_c900 p = pBlock->mPosition;
        joint->mPosition = p;
        Quaternion ori = GetBlockRotation(pBlock->mOrientation);
        joint->mOrientation = ori;
        Vector3_s0046_c900 mn = RotateVector(pBlockData->mStart, pBlockData->mFrame);
        Vector3_s0046_c900 mx = RotateVector(pBlockData->mEnd, pBlockData->mFrame);
        joint->mStart = mn;
        joint->mEnd = mx;
        joint->mFrameX = pBlockData->mFrame.x;
        joint->mRadius = pBlockData->mRadius;

        joint->mNumParts = pBlock->mAttachments.size();
        for (int k = 0; k < joint->mNumParts; ++k) {
            joint->mParts[k].mPart = GetPartID(pBlock->mAttachments.mpBegin[k].GetPart());
            joint->mParts[k].mSlot = pBlock->mAttachments.mpBegin[k].GetSlot();
        }

        joint->mNumPartModels = 0;
        if (!ignorePartModels && joint->mPartIndex != -1) {
            joint->mNumPartModels = pBlock->GetPartModelCount();
            for (int m = 0; m < joint->mNumPartModels; ++m) {
                PartModel* pPart = pBlock->GetPartModel(m);
                if (pPart) {
                    joint->mPartModels[m].mModelID = pPart->mModelID;
                    joint->mPartModels[m].mScale = pPart->mScale;
                }
            }
            joint->mpModel = pBlock->GetModel();
        }
        {
            int unused;   // an unused local of the original: it only reserves a stack slot at /Od
        }

        joint->mProperties[0] = pBlock->GetPropertyValue(0xdd94fb65);
        joint->mProperties[1] = pBlock->GetPropertyValue(0x0e40c402);
        joint->mProperties[2] = pBlock->GetPropertyValue(0x2dc2a89d);
    }
}
}}  // namespace SP::EditorUtils

// @ 0x0046d660
float* FUN_0046d660(float* out, const float* m)
{
    float tmp[4];
    float* q = QuaternionFromMatrix33(tmp, m, 0.0f);
    out[0] = q[0];
    out[1] = q[1];
    out[2] = q[2];
    out[3] = q[3];
    return out;
}

// @ 0x0046d6c0
void F_0046d6c0()
{}

// @ 0x0046d840
void F_0046d840()
{}

// @ 0x0046dad0
void F_0046dad0()
{}

// @ 0x0046de70
void F_0046de70()
{}

// @ 0x0046e450
namespace SP { namespace EditorUtils {
void ExportCreatureBlocksFile(const wchar_t* baseName, CreatureBlocks* data)
{
    EAString8 value(EAString8::Tag(), "%ls.blocks", baseName);
    FILE* it = fopen(value.c_str(), "w");
    fprintf(it, "version %d\n", data->version);
    fprintf(it, "name \"%S\"\n", data->GetName());
    fprintf(it, "isPlant %d\n", data->isPlant != 0);
    fprintf(it, "cal3DRootBlockIndex %d\n", data->cal3DRootBlockIndex);
    fprintf(it, "numBlocks %d\n\n", data->blocks.size());
    for (int x = 0, n = data->blocks.size(); x < n; ++x) {
        Block_s0046_e450* base = &data->blocks[x];
        fprintf(it, "block %d\n", base->blockIndex);
        fprintf(it, "\tversion %d\n", base->version);
        fprintf(it, "\tname %S\n", base->name);
        fprintf(it, "\tinstanceId %d\n", base->instanceId);
        fprintf(it, "\tparentIndex %d\n", base->parentIndex);
        fprintf(it, "\tsymmetricIndex %d\n", base->symmetricIndex);
        fprintf(it, "\tjointPosition %f %f %f\n", base->jointPosition[0], base->jointPosition[1], base->jointPosition[2]);
        fprintf(it, "\tsubmeshIndex %d\n", base->submeshIndex);
        bool ptr = false;
        {
        AutoRefCount_s0046_e450<cPropertyList_s0046_e450> tmp;
        if (PropertyManager_s0046_e450()->GetPropertyList(base->instanceId, base->keyGroup, tmp.AsOutParam())) {
            uint32_t other = 0;
            const uint32_t len = 0xf48eb09;
            if (GetPropertyAsKeyInstance(tmp, len, &other)) {
                if (other == base->instanceId)
                    ptr = true;
            }
        }
        }
        ScratchSlots<3>();
        fprintf(it, "\tleftHanded %d\n", ptr);
        fprintf(it, "\tcal3DBoneName %s\n", base->boneName);
        fprintf(it, "\tcal3DOrigin %f %f %f\n", base->cal3DOrigin[0], base->cal3DOrigin[1], base->cal3DOrigin[2]);
        fprintf(it, "\teffectsOrigin %f %f %f\n", base->effectsOrigin[0], base->effectsOrigin[1], base->effectsOrigin[2]);
        fprintf(it, "\tposition %f %f %f\n", base->position[0], base->position[1], base->position[2]);
        fprintf(it, "\torientation %f %f %f %f\n", base->orientX, base->orientY, base->orientZ, base->orientW);
        fprintf(it, "\tbBoxMin %f %f %f\n", base->bBoxMin[0], base->bBoxMin[1], base->bBoxMin[2]);
        fprintf(it, "\tbBoxMax %f %f %f\n", base->bBoxMax[0], base->bBoxMax[1], base->bBoxMax[2]);
        fprintf(it, "\tscale %f\n", base->scale);
        fprintf(it, "\tsoundIDFoot 0x%8.8x\n", base->soundIDFoot);
        fprintf(it, "\tsoundIDMouth 0x%8.8x\n", base->soundIDMouth);
        fprintf(it, "\tsoundIDWeapon 0x%8.8x\n", base->soundIDWeapon);
        for (int g = 0, buf = base->numCaps; g < buf; ++g)
            fprintf(it, "\tcap %s %d\n", base->caps[g].name, base->caps[g].value);
        for (int hi = 0, z = base->numDeform; hi < z; ++hi)
            fprintf(it, "\tdeformChannel 0x%8.8x %f\n", base->deform[hi].id, base->deform[hi].value);
        fprintf(it, "end\n\n");
    }
    fclose(it);
}
}}  // namespace SP::EditorUtils

// @ 0x0046eae0
namespace SP { namespace EditorUtils {
void DumpEditorModelZPR(EditorModelSource* src, const wchar_t* name)
{
    MeshRef_s0046_e450 offset;
    GetPaintSystem()->BuildMeshes(src, offset.Reset());
    ScratchSlots<2>();
    MeshGroupRef_s0046_e450 hi(new ("App", 0, 0, 0, 0) MeshGroup_s0046_e450());
    hi->mBatches.push_back(Batch_s0046_e450());
    ScratchSlots<3>();
    Batch_s0046_e450* val = &hi->mBatches.back();
    ScratchSlots<12>();
    hi.p->mStreams.resize(2);
    hi->mStreams[0] = StreamElem_s0046_e450(1, 0, 3, 0, StreamDesc_s0046_e450(offset->mVertices.size(), offset->mVertices.begin(), 12, 0));
    hi->mStreams[1] = StreamElem_s0046_e450(8, 0, 2, 2, StreamDesc_s0046_e450(offset->mTextureCoordinates.size(), offset->mTextureCoordinates.begin(), 8, 0));
    int owner = offset->mVertexIndices_TV.size();
    val->mVertexCount = offset->mVertices.size();
    ScratchSlots<8>();
    val->mIndexDescs.resize(2);
    val->mIndexDescs[0] = StreamDesc_s0046_e450(owner, offset->mVertexIndices_TV.begin(), (IObject*)0, 0);
    val->mIndexDescs[1] = StreamDesc_s0046_e450(owner, offset->mTextureIndices_TV.begin(), (IObject*)0, 0);
    val->mStreamIndices.push_back(StreamIndex(0, 0));
    val->mStreamIndices.push_back(StreamIndex(1, 1));
    hi->mRanges.push_back(IndexRange(4, 0, 0, owner, 0));
    RefVector g((AllocTag()));
    g.push_back(hi);
    DumpZPR(g, FUN_0046f260(src->GetTexture()), name);
}
}}  // namespace SP::EditorUtils

// @ 0x0046f140
Desc* Desc::init(int a_, int b_, BaseDesc* r_, int)
{
    a = a_;
    b = b_;
    c = 4;
    d = 4;
    BaseDesc** local = &ref;
    *local = r_;
    if (*local)
        (*local)->v0();
    return this;
}

// @ 0x0046f1b0
Batch_s0046_e450::Batch_s0046_e450()
: mVertexCount(0)
{
    ScratchSlots<7>();
}

// @ 0x0046f1f0
Desc* Desc::init0()
{
    a = 0;
    b = 0;
    c = 0;
    d = 0;
    BaseDesc** local = &ref;
    *local = 0;
    if (*local)
        (*local)->v0();
    return this;
}

// @ 0x0046f260
int __fastcall FUN_0046f260(Sf260* p)
{
    if (!(p->flags & 1))
        FUN_0067dd60()->v13(p);
    return p->field0;
}

// @ 0x0046f2a0
bool DumpZPR(RefVector_s0046_f2a0 meshesIn, SpriteTexture* tex, const wchar_t* fullPath)
{
    const char* kZPRTextureName = "Spore Baked Texture";
    unsigned int textureNameLen = strlen(kZPRTextureName);
    char kZPRTextureMapsBlockType = 0x1e;
    int numPrimTris = 0;
    int blockSize;
    IntVector_s0046_f2a0 vertOffsets;
    IntVector_s0046_f2a0 primOffsets;
    EStr fullPath8;
    fullPath8.sprintf("%ls", fullPath);
    FILE* f = fopen(fullPath8.c_str(), "wb");
    if (f) {
        DumpZPR_M0(f, meshesIn, numPrimTris, vertOffsets, primOffsets);
        if (tex) {
            int height = tex->GetHeight();
            int width = tex->GetWidth();
            char kZPRRepeatFlag = 1;
            int numTextures = 1;
            blockSize = (textureNameLen + width * 3 * height + 0xe) * numTextures + 9;
            fwrite(&kZPRTextureMapsBlockType, 1, 1, f);
            fwrite(&blockSize, 1, 4, f);
            fwrite(&numTextures, 1, 4, f);
            fwrite(&textureNameLen, 1, 4, f);
            fwrite(kZPRTextureName, textureNameLen, 1, f);
            fwrite(&width, 1, 4, f);
            fwrite(&height, 1, 4, f);
            fwrite(&kZPRRepeatFlag, 1, 1, f);
            fwrite(&kZPRRepeatFlag, 1, 1, f);
            int bytes = width * height * tex->GetBitsPerPixel() / 8;
            unsigned char* pixels = new("Editor", 0, 0, 0, 0) unsigned char[bytes];
            if (pixels) {
                if (tex->FillSpriteTexture(pixels, bytes, 0)) {
                    FILE* f2 = fopen("sporelicious.f2", "wb");
                    if (f2) {
                        for (int y = 0; y < height; y++) {
                            for (int x = 0; x < width; x++) {
                                unsigned char* px = pixels + (y * width + x) * 4;
                                unsigned char r = px[0];
                                unsigned char g = px[1];
                                unsigned char cb = px[2];
                                fwrite(&cb, 1, 1, f2);
                                fwrite(&g, 1, 1, f2);
                                fwrite(&r, 1, 1, f2);
                            }
                        }
                        fclose(f2);
                    }
                    for (int y = 0; y < height; y++) {
                        for (int x = 0; x < width; x++) {
                            unsigned char* px = pixels + (y * width + x) * 4;
                            unsigned char r = px[0];
                            unsigned char g = px[1];
                            unsigned char cb = px[2];
                            fwrite(&cb, 1, 1, f);
                            fwrite(&g, 1, 1, f);
                            fwrite(&r, 1, 1, f);
                        }
                    }
                }
            }
            if (pixels) {
                delete[] pixels;
            }
        }
        ExportModelTriangles(f, meshesIn, numPrimTris, vertOffsets, primOffsets, false);
    }
    return true;
}

// @ 0x0046f8a0
void DumpZPR_M0(FILE* f, RefVector_s0046_f2a0 meshesIn, int& numPrimTris, IntVector_s0046_f2a0& vertOffsets, IntVector_s0046_f2a0& primOffsets)
{
    int ptSemantics[2] = { 1, 8 };
    int ptTypes[2] = { 3, 2 };
    int ptNumbers[2] = { 0, 0 };
    char kZPRFormat = (char)0xaa;
    char kZPRVersion = 1;
    const char* kZPRComment = "Created by Spore Editor";
    char kZPRColorMode = 2;
    char kZPRTextureMode = 2;
    char kZPRScaleBlockType = 0x3c;
    char kZPRVerticesBlockType = 0xa;
    float kZPRDefaultScale = 1.0f;
    char kZPRNullColor = 0;
    char kZPRFF = (char)0xff;
    int kZPRNullTexIndex = -1;
    unsigned int commentLen = strlen(kZPRComment);
    fwrite(&kZPRFormat, 1, 1, f);
    fwrite(&kZPRVersion, 1, 1, f);
    fwrite(&commentLen, 1, 4, f);
    fwrite(kZPRComment, commentLen, 1, f);
    fwrite(&kZPRColorMode, 1, 1, f);
    fwrite(&kZPRTextureMode, 1, 1, f);
    fwrite(&kZPRScaleBlockType, 1, 1, f);
    int blockSize = 9;
    fwrite(&blockSize, 1, 4, f);
    fwrite(&kZPRDefaultScale, 1, 4, f);
    int numVerts = 0;
    for (int i = 0, numMeshes = meshesIn.mpEnd - meshesIn.mpBegin; i < numMeshes; i++) {
        Model_s0046_f2a0* mesh = meshesIn[i];
        FUN_00733ed0(mesh);
        CreateClustersAndEdges(mesh, 1);
        vertOffsets.push_back(numVerts);
        Stream* positions = FUN_0071de40(mesh, 1, 0, 3, 0xe);
        numVerts += positions->count;
        primOffsets.push_back(numPrimTris);
        for (int s = 0, ns = mesh->mMeshes.size(); s < ns; s++) {
            int formatIndices[2];
            if (FindMeshStreams(mesh, s, 2, ptSemantics, ptNumbers, ptTypes, formatIndices)) {
                Stream* pos = &mesh->mStreams[mesh->mMeshes[s].mStreamMap[formatIndices[0]].stream].stream;
                Stream* uv = &mesh->mStreams[mesh->mMeshes[s].mStreamMap[formatIndices[1]].stream].stream;
                Stream* posRemap = !mesh->mMeshes[s].mRemaps.empty()
                    ? &mesh->mMeshes[s].mRemaps[mesh->mMeshes[s].mStreamMap[formatIndices[0]].remap] : NULL;
                Stream* uvRemap = !mesh->mMeshes[s].mRemaps.empty()
                    ? &mesh->mMeshes[s].mRemaps[mesh->mMeshes[s].mStreamMap[formatIndices[1]].remap] : NULL;
                Stream* indices = mesh->mMeshes[s].mIndices.data == NULL ? NULL : &mesh->mMeshes[s].mIndices;
                numPrimTris += (indices ? indices->count : pos->count) / 3;
                (void)uv;
                (void)posRemap;
                (void)uvRemap;
            }
        }
    }
    blockSize = numVerts * 0x13 + 5;
    fwrite(&kZPRVerticesBlockType, 1, 1, f);
    fwrite(&blockSize, 1, 4, f);
    for (int i = 0, numMeshes = meshesIn.mpEnd - meshesIn.mpBegin; i < numMeshes; i++) {
        Model_s0046_f2a0* mesh = meshesIn[i];
        Stream* positions = FUN_0071de40(mesh, 1, 0, 3, 0xe);
        int n = positions->count;
        for (int v = 0; v < n; v++) {
            fwrite(positions->data + positions->stride * v, 1, 0xc, f);
            fwrite(&kZPRNullColor, 1, 1, f);
            fwrite(&kZPRNullColor, 1, 1, f);
            fwrite(&kZPRNullColor, 1, 1, f);
            fwrite(&kZPRNullTexIndex, 1, 4, f);
        }
    }
    (void)kZPRFF;
}

// @ 0x0046ff00
void ExportModelTriangles(FILE* file, ModelRefVector models, int unused, const int& triangleCount, const IntVector_s0046_ff00& vertexBase, const IntVector_s0046_ff00& triangleBase, bool perModelID)
{
    int semantics[2] = { 1, 8 };
    int formats[2] = { 3, 2 };
    int usage[2] = { 0, 0 };
    char chunkTris = 0x14;
    char zero = 0;
    char chunkEnd = 0x28;
    char chunkUVs = 0x32;
    int modelID = 0;

    int chunkSize = triangleCount * 0x13 + 5;
    fwrite(&chunkTris, 1, 1, file);
    fwrite(&chunkSize, 1, 4, file);

    for (int m = 0, nModels = models.size(); m < nModels; m++) {
        Model_s0046_ff00* model = models[m];
        for (int i = 0, nMeshes = model->mMeshes.size(); i < nMeshes; i++) {
            int idx[2];
            if (FindMeshStreams(model, i, 2, semantics, usage, formats, idx)) {
                Stream* pos = &model->mStreams[model->mMeshes[i].mStreamMap[idx[0]].stream].stream;
                Stream* uv = &model->mStreams[model->mMeshes[i].mStreamMap[idx[1]].stream].stream;
                Stream* posRemap = !model->mMeshes[i].mRemaps.empty()
                    ? &model->mMeshes[i].mRemaps[model->mMeshes[i].mStreamMap[idx[0]].remap] : NULL;
                Stream* uvRemap = !model->mMeshes[i].mRemaps.empty()
                    ? &model->mMeshes[i].mRemaps[model->mMeshes[i].mStreamMap[idx[1]].remap] : NULL;
                Stream* indices = model->mMeshes[i].mIndices.data == NULL ? NULL : &model->mMeshes[i].mIndices;
                int nTris = (indices ? indices->count : pos->count) / 3;
                uint32_t next = 0;
                for (int t = 0; t < nTris; t++) {
                    uint32_t a = next++;
                    uint32_t b = next++;
                    uint32_t c = next++;
                    if (indices) {
                        a = ReadIndex(indices, a);
                        b = ReadIndex(indices, b);
                        c = ReadIndex(indices, c);
                    }
                    if (posRemap) {
                        a = ReadIndex(posRemap, a);
                        b = ReadIndex(posRemap, b);
                        c = ReadIndex(posRemap, c);
                    }
                    a += vertexBase.mpBegin[m];
                    b += vertexBase.mpBegin[m];
                    c += vertexBase.mpBegin[m];
                    int tri = t + triangleBase.mpBegin[m];
                    fwrite(&a, 1, 4, file);
                    fwrite(&b, 1, 4, file);
                    fwrite(&c, 1, 4, file);
                    fwrite(&zero, 1, 1, file);
                    fwrite(&zero, 1, 1, file);
                    fwrite(&zero, 1, 1, file);
                    fwrite(&tri, 1, 4, file);
                }
                (void)uv;
                (void)uvRemap;
            }
        }
    }

    chunkSize = 5;
    fwrite(&chunkEnd, 1, 1, file);
    fwrite(&chunkSize, 1, 4, file);

    chunkSize = triangleCount * 0x1c + 5;
    fwrite(&chunkUVs, 1, 1, file);
    fwrite(&chunkSize, 1, 4, file);

    for (int m = 0, nModels = models.size(); m < nModels; m++) {
        Model_s0046_ff00* model = models[m];
        if (perModelID)
            modelID = m;
        for (int i = 0, nMeshes = model->mMeshes.size(); i < nMeshes; i++) {
            int idx[2];
            if (FindMeshStreams(model, i, 2, semantics, usage, formats, idx)) {
                Stream* pos = &model->mStreams[model->mMeshes[i].mStreamMap[idx[0]].stream].stream;
                Stream* uv = &model->mStreams[model->mMeshes[i].mStreamMap[idx[1]].stream].stream;
                Stream* posRemap = !model->mMeshes[i].mRemaps.empty()
                    ? &model->mMeshes[i].mRemaps[model->mMeshes[i].mStreamMap[idx[0]].remap] : NULL;
                Stream* uvRemap = !model->mMeshes[i].mRemaps.empty()
                    ? &model->mMeshes[i].mRemaps[model->mMeshes[i].mStreamMap[idx[1]].remap] : NULL;
                Stream* indices = model->mMeshes[i].mIndices.data == NULL ? NULL : &model->mMeshes[i].mIndices;
                int nTris = (indices ? indices->count : uv->count) / 3;
                uint32_t next = 0;
                for (int t = 0; t < nTris; t++) {
                    uint32_t a = next++;
                    uint32_t b = next++;
                    uint32_t c = next++;
                    if (indices) {
                        a = ReadIndex(indices, a);
                        b = ReadIndex(indices, b);
                        c = ReadIndex(indices, c);
                    }
                    if (uvRemap) {
                        a = ReadIndex(uvRemap, a);
                        b = ReadIndex(uvRemap, b);
                        c = ReadIndex(uvRemap, c);
                    }
                    Vector2_s0046_ff00 uvA = *(Vector2_s0046_ff00*)(uv->data + uv->stride * a);
                    Vector2_s0046_ff00 uvB = *(Vector2_s0046_ff00*)(uv->data + uv->stride * b);
                    Vector2_s0046_ff00 uvC = *(Vector2_s0046_ff00*)(uv->data + uv->stride * c);
                    fwrite(&modelID, 1, 4, file);
                    fwrite(&uvA.x, 1, 4, file);
                    fwrite(&uvB.x, 1, 4, file);
                    fwrite(&uvC.x, 1, 4, file);
                    fwrite(&uvA.y, 1, 4, file);
                    fwrite(&uvB.y, 1, 4, file);
                    fwrite(&uvC.y, 1, 4, file);
                }
                (void)pos;
                (void)posRemap;
            }
        }
    }

    fclose(file);
}

// @ 0x00470bd0
Vec2_s0047_0bd0* FUN_00470bd0(Vec2_s0047_0bd0* out, Box* a, int na, Box* b, int nb, float z)
{
    if (a == 0 || b == 0) {
        out->x = g_DefaultX;
        out->y = g_DefaultY;
        return out;
    }
    Vec2_s0047_0bd0 result;
    result.x = g_DefaultX;
    result.y = g_DefaultY;
    float eps = g_Epsilon;

    Range ra; ra.mp = a; ra.mCount = na; ra.mBest = g_Zero;
    for (int i = 0; i < ra.mCount; i++) {
        if (ra.mp[i].mMax[2] > g_Zero) {
            Vec4 v(ra.mp[i].mMax[0], ra.mp[i].mMax[1], -ra.mp[i].mMin[0], -ra.mp[i].mMin[1]);
            float m = FUN_00470f20(&v);
            if (z - eps >= ra.mp[i].mMin[2] && ra.mp[i].mMax[2] >= z + eps && m > ra.mBest)
                ra.mBest = m;
        }
    }
    result[0] = ra.mBest;

    Range rb; rb.mp = b; rb.mCount = nb; rb.mBest = g_Zero;
    for (int j = 0; j < rb.mCount; j++) {
        if (rb.mp[j].mMax[2] > g_Zero) {
            Vec4 v(rb.mp[j].mMax[0], rb.mp[j].mMax[1], -rb.mp[j].mMin[0], -rb.mp[j].mMin[1]);
            float m = FUN_00470f20(&v);
            if (rb.mp[j].mMax[2] >= z && m > rb.mBest)
                rb.mBest = m;
        }
    }
    result[1] = rb.mBest;
    out->x = result.x;
    out->y = result.y;
    return out;
}

// @ 0x00470f20
float FUN_00470f20(Vec4* p)
{
    float l = Max2(p, 0, 1);
    float r = Max2(p, 2, 3);
    return MaxF(l, r);
}

// @ 0x00471000
namespace SP { namespace EditorUtils {
void AddInitialBoundInfo(u64* ids, Box* boxes, int count, int unused, IPropList_s0047_0bd0* pl)
{
    if (boxes == 0 || pl == 0)
        return;

    Box bound;
    bound.Reset();
    for (int i = 0; i < count; i++)
        bound.AddPoint(&boxes[i]);

    {
        Variant_s0047_0bd0 v;
        v.SetBox(bound);
        pl->Set(0xf9efba, &v);
    }
    Vec3_s0047_0bd0 neg;
    Vec3_s0047_0bd0* pn = Vector3_Negate(&neg, &bound.mMin);
    Vec3_s0047_0bd0 negCopy;
    negCopy[0] = (*pn)[0]; negCopy[1] = (*pn)[1]; negCopy[2] = (*pn)[2];
    Vec3_s0047_0bd0 mx;
    float radius = VectorLength(Vector3_MaxVec(&mx, &negCopy, &bound.mMax));
    {
        Variant_s0047_0bd0 v;
        v.SetFloat(radius);
        pl->Set(0xf9efb9, &v);
    }
    {
        Variant_s0047_0bd0 v;
        v.SetFloat(bound.mMax[2]);
        pl->Set(0x254cf97, &v);
    }

    bool allocFlag;
    VecBox vbox(&allocFlag);
    vbox.Init();
    for (int i = 0; i < count && ids != 0; i++) {
        u32 lo = (u32)(ids[i] & 0xffffffff);
        u32 hi = (u32)(ids[i] >> 32);
        ObjPtr obj; obj.mp = 0;
        if (lo != 0 && hi != 0) {
            IPropManager* pm = PropertyManager_s0047_0bd0();
            if (pm->GetObject(lo, hi, PropObjOut(&obj))) {
                RefState st; st.b = true; st.z0 = 0; st.z1 = 0; st.z2 = 0;
                IObject_s0047_0bd0* o = obj.mp;
                Property_s0047_0bd0* prop;
                if (o != 0 && o->Get(0x4bf2278, &prop) && prop->mType == 1)
                    st.b = *prop->GetBool();
                if (st.b)
                    vbox.push_back(&boxes[i]);
            }
        }
        if (obj.mp != 0)
            obj.mp->Release();
    }

    float f624 = g_Zero;
    float f4 = g_Zero;
    int nArr = 0;
    float* arr = 0;
    if (!GetPropertyAsFloatArray(pl, 0x4c6df19, &nArr, &arr)) {
        f624 = radius;
        f4 = radius;
    }
    VecV2_s0047_0bd0 v2;
    v2.Init();
    for (int k = 0; k < nArr; k++) {
        float z = arr[k] * bound.mMax[2];
        int nb = (int)(vbox.mpEnd - vbox.mpBegin);
        Vec2_s0047_0bd0 r;
        FUN_00470bd0(&r, vbox.mpBegin, nb, boxes, count, z);
        if (r[0] > g_Zero)
            v2.push_back(&r);
        f4 = r[1];
    }
    if ((unsigned)(v2.mpEnd - v2.mpBegin) != 0) {
        int n = 1;
        Property_s0047_0bd0* prop;
        if (pl != 0 && pl->Get(0x52d8d4a, &prop) && prop->mType == 9)
            n = *prop->GetInt();
        SortV2(v2.mpBegin, v2.mpEnd, allocFlag);
        f624 = g_Zero;
        int cnt = 0;
        int size = (int)(v2.mpEnd - v2.mpBegin);
        int lim = 0;
        int m = (size < n) ? size : n;
        for (; lim < m; lim++) {
            Vec2_s0047_0bd0* e = v2.mpBegin + lim;
            f624 = f624 + (*e)[0];
            cnt++;
        }
        int one = 1;
        const int* pd = (cnt < one) ? &one : &cnt;
        f624 = f624 / (float)*pd;
    }
    if (f624 == 0.0f)
        f624 = g_Third;
    {
        Variant_s0047_0bd0 v;
        v.SetFloat(f624);
        pl->Set(0x254cf89, &v);
    }
    {
        Variant_s0047_0bd0 v;
        v.SetFloat(f4);
        pl->Set(0x254cf8f, &v);
    }
    for (char* p = (char*)v2.mpBegin; p < (char*)v2.mpEnd; p += 8) {}
    v2.Free();
    for (char* p = (char*)vbox.mpBegin; p < (char*)vbox.mpEnd; p += 0x18) {}
    vbox.Free();
}
}}  // namespace SP::EditorUtils

// @ 0x00471830
void FUN_00471830(Editor_s0047_0bd0* self, IPropList_s0047_0bd0* pl)
{
    if (self == 0)
        return;
    Item* data = (Item*)self->mItems.mpBegin;
    ItemVec* vp = &self->mItems;
    int n = (int)(vp->mpEnd - vp->mpBegin) / 0x8c;

    bool a1;
    VecBoxC boxes(&a1);
    boxes.Init();
    bool a2;
    VecIds ids(&a2);
    ids.Init();
    boxes.reserve(n);
    ids.reserve(n);

    for (int i = 0; i < n; i++) {
        Transform_s0047_0bd0 t;
        t.SetScale(data[i].mScale);
        t.SetRotation(data[i].mRot);
        t.SetPosition(data[i].mPos);
        BoxC box(data[i].mBoxMin, data[i].mBoxMax);
        bool bad = box.mMin.x > box.mMax.x ? true : false;   // inverted (empty) box test
        if (bad)
            box.SetCenterRadius(&g_Vec3Zero, g_BoxFallbackRadius);
        box.TransformBy(&t);
        boxes.push_back(&box);
        u64 id = ((u64)data[i].mIdHi << 32) | data[i].mIdLo;
        ids.push_back(&id);
    }
    Box* bb = boxes.mpBegin;
    SP::EditorUtils::AddInitialBoundInfo(ids.mpBegin, bb, n, self->f18, pl);
    ids.Free();
    for (char* p = (char*)boxes.mpBegin; p < (char*)boxes.mpEnd; p += 0x18) {}
    boxes.Free();
}

// @ 0x00471b50
namespace SP {
namespace EditorUtils {
void AddInitialBoundInfo(SP::cEditorResource * a1, SP::cPropertyList * a2)
{}
}
}  // namespace SP::EditorUtils

// @ 0x00472540
RefHolderB::~RefHolderB()
{
    ScratchSlots_s0047_1b50<3>();
    if (p)
        p->Release();
}
