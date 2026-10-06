// Slice s004629e0: SP::EditorUtils::ExportToXMFAndBlocks (0x004629e0, 6430 bytes, /Od).
// Builds a Collada (.dae) export of an editor creature: copies the baked skin mesh, the bone
// skeleton and then appends every rigid block model (positions, UVs remapped into the block's
// texture rect, tangent frames, blend indices/weights, triangle indices and bone matrices).
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast /GS-  (no /EHsc: no EH frame although RAII locals).
#include "types.h"

extern "C" long __cdecl _InterlockedExchangeAdd(long volatile* p, long v);
#pragma intrinsic(_InterlockedExchangeAdd)

// ---------------------------------------------------------------------------------------------
// math
// ---------------------------------------------------------------------------------------------
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

// Transform (0x38): flags, change counter, offset, scale, rotation.
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

// ---------------------------------------------------------------------------------------------
// containers (EASTL vector with sp_vector_allocator: 0x14 bytes)
// ---------------------------------------------------------------------------------------------
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

// eastl::fixed_vector<T,64> (begin/end/cap + pool allocator header 0x18, then the buffer).
// The sized ctor is out of line (0x41d510 Matrix43, 0x41d0c0 int).
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

// eastl::basic_string<wchar_t>
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

namespace EA { namespace IO {
bool SplitPath(const wchar_t* pPath, wchar_t* pDrive, wchar_t* pDirectory, wchar_t* pFileName,
               wchar_t* pExtension, int nCapacity);    // 0x930180
class FileStream {
public:
    FileStream(const wchar_t* pPath);                     // 0x931e10
    ~FileStream();                                         // 0x931e70
    bool Open(int nAccessFlags, int nCreationDisposition, int nSharing, int nUsageHints); // 0x9318f0
    bool Close();                                          // 0x931a70
    char mData[0x230];
};
} }

// ---------------------------------------------------------------------------------------------
// export data
// ---------------------------------------------------------------------------------------------
// Unidentified exporter helpers; only constructed/destroyed here.
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

// The Collada mesh/skin being written (0x150).
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
    bool Write(EA::IO::FileStream* stream); // 0x45c350
};

// Source creature data.
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

// Model manager interface (vtable slots by byte offset).
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

// Baked render model (0x58) with vertex streams and index buffers.
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

// ---------------------------------------------------------------------------------------------
// @ 0x004629e0
// ---------------------------------------------------------------------------------------------
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

    EA::IO::FileStream stream(path.c_str());
    stream.Open(2, 2, 1, 0);
    dae.Write(&stream);
    stream.Close();
    return true;
}

} }
