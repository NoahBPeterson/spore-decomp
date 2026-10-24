// s0046d660 -- /arch:SSE region of SPBake/SPEditorExportUtilities.obj (editor model / skin export).
//
// 0x0046d660  quaternion-from-matrix wrapper around rw::math::fpu::QuaternionFromMatrix33<float,0>
// 0x0046d6c0  min-z comparison between flagged and plain blocks of a block array
// 0x0046d840  loads an editor model from a resource and updates the target skin object
// 0x0046dad0  rebuilds the skin's creature material info and per-block material objects
// 0x0046de70  fills the export buffers (positions/uvs/colors/weights) from the model's block list
//
// The retail objects are all /Od with a frame pointer, so every row compiles with /Oy-.

#include <intrin.h>

typedef unsigned int uint32_t;

// ---- shared views ---------------------------------------------------------

struct Vector3T {                                                        // rw::math::fpu::Vector3Template<float,0>
    float x, y, z;
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};
struct cSPVector3 : Vector3T {
    cSPVector3() {}
    cSPVector3(const Vector3T& v) { x = v.x; y = v.y; z = v.z; }
    cSPVector3& operator=(const Vector3T& v) { x = v.x; y = v.y; z = v.z; return *this; }
};
struct cSPBoundingBox {
    cSPVector3 mMin;
    cSPVector3 mMax;
};
struct Vector2T {
    float x, y;
};
struct cSPMatrix4 {                                                      // 4x4 transform (0x40)
    float mValue[16];
};
struct cSPTransform {                                                    // 0x80 build transform copied into the target
    float mValue[32];
};

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
    cSPVector3 mPosition;                                                // +0x48
    char pad54[0xdc8 - 0x54];
    bitset<60> mFlags;                                                   // +0xdc8
    cSPBoundingBox GetBBox(int type, bool a, bool b);                    // 0x0044ae00
};

// ---- small refcounted helpers --------------------------------------------

extern const float kFltMax;                                              // 0x013eec70
extern const float kSymmetryTolerance;                                   // 0x013ec480 (0.2f)
extern const float kMaterialDepth;                                       // 0x013ebc4c (60.0f)
extern const char kEditorAllocName[];                                    // 0x013eb430 "Editor"

// 0x00472b80 rw::math::fpu::QuaternionFromMatrix33<float,0>
extern "C" float* QuaternionFromMatrix33(float* out, const float* m, float v);

// EAAllocate/operator new(size, name, ...) used by every `new ("Editor") T`.
void* operator new(unsigned int size, const char* name, int a, int b, int c, int d);
void* operator new(unsigned int size);

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
bool F_0046d6c0(cSPEditorBlock** ppBlocks, int nBlocks)
{
    float t32 = kSymmetryTolerance;                                      // tolerance
    float p32 = kFltMax;                                                 // min of the unflagged blocks
    float n10 = kFltMax;                                                 // min of the flagged blocks
    for (int n37 = 0; n37 < nBlocks; n37++) {
        cSPEditorBlock* owner = ppBlocks[n37];
        cSPBoundingBox n2 = owner->GetBBox(0, true, false);
        if (owner->mFlags.test(7) || owner->mFlags.test(0x2d)) {
            if (n10 > n2.mMin[2])
                n10 = n2.mMin[2];
        } else {
            if (p32 > n2.mMin[2])
                p32 = n2.mMin[2];
        }
    }
    if (n10 - p32 > t32) {
        return true;
    } else {
        return false;
    }
}

// ---- refcounted objects ---------------------------------------------------

struct DefaultRefCounted {                                               // counter subobject at object+4
    void* mpVtbl;                                                        // +0x00
    int mCount;                                                          // +0x04
    void AddRef() { int c = mCount + 1; mCount = mCount + 1; (void)c; }
    void Release();                                                      // 0x00453540
};

struct Releasable {                                                      // handle target with virtual AddRef/Release
    virtual void AddRef();                                               // +0x00
    virtual void Release();                                              // +0x04
};

struct cSPEditorModel {                                                  // 0xe0 bytes, ctor 0x004ab690
    void* mpVtbl;                                                        // +0x00
    DefaultRefCounted mRef;                                              // +0x04
    char pad0C[0x18 - 0x0c];
    cSPEditorBlock** mpBlocks;                                           // +0x18
    char pad1C[0xe0 - 0x1c];
    cSPEditorModel();                                                    // 0x004ab690
    void AddRef() { mRef.AddRef(); }
    void Release() { mRef.Release(); }
    cSPEditorBlock** GetBlocks() const { return mpBlocks; }
    bool LoadResource(const void* resource);                             // 0x004ae3b0
    bool FUN_004ae260(Releasable* world);                                // 0x004ae260
    unsigned GetBlockCount() const;                                      // 0x004accf0
    void FUN_004ad330();                                                 // 0x004ad330
};

// EA::AutoRefCount<SP::cSPEditorModel> -- the assignment is an out-of-line call
struct ModelRef {
    cSPEditorModel* mpPtr;
    ModelRef(cSPEditorModel* p = 0) { mpPtr = p; if (mpPtr) mpPtr->mRef.AddRef(); }
    ~ModelRef() { if (mpPtr) mpPtr->mRef.Release(); }
    ModelRef& operator=(cSPEditorModel* p);                              // 0x0041d980
    cSPEditorModel* operator->() const { return mpPtr; }
    operator cSPEditorModel*() const { return mpPtr; }
};

template <class T>
struct AutoRefCount {                                                    // handle whose assignment is inlined
    T* mpPtr;
    AutoRefCount() { mpPtr = 0; }
    AutoRefCount(T* p) { mpPtr = p; if (mpPtr) mpPtr->AddRef(); }
    ~AutoRefCount() { if (mpPtr) mpPtr->Release(); }
    AutoRefCount& operator=(T* p)
    {
        if (p != mpPtr) {
            T* old = mpPtr;
            if (p)
                p->AddRef();
            mpPtr = p;
            if (old)
                old->Release();
        }
        return *this;
    }
    T* operator->() const { return mpPtr; }
};

// intrusive store into a pointer member: callers pass the member address, so the /Od temp holds it
template <class T>
inline void IntrusiveAssign(T** slot, T* p)
{
    if (p != *slot) {
        T* old = *slot;
        if (p)
            p->AddRef();
        *slot = p;
        if (old)
            old->Release();
    }
}

template <class T>
struct SpVector {                                                        // eastl vector with the SP allocator (0x14 bytes)
    T* mpBegin;                                                          // +0x00
    T* mpEnd;                                                            // +0x04
    T* mpCapacity;                                                       // +0x08
    char mAllocator[8];                                                  // +0x0c
    void reserve(unsigned n);
    void push_back(const T& value);
};

template <class T>
struct PtrVector {                                                       // eastl vector of pointers (0x0c bytes)
    T* mpBegin;                                                          // +0x00
    T* mpEnd;                                                            // +0x04
    T* mpCapacity;                                                       // +0x08
    int size() const { return (int)(mpEnd - mpBegin); }
    void resize(unsigned n);                                             // 0x0041ee90
    void erase(T* first, T* last);                                       // 0x00426280
};

struct IntVector {                                                       // SimpleVector<int>
    int* mpBegin;                                                        // +0x00
    int* mpEnd;                                                          // +0x04
    int* mpCapacity;                                                     // +0x08
    void resize(unsigned n);                                             // 0x004cd3c0
};

// ---- editor export material chain -----------------------------------------

struct cBakeSprite {                                                     // 0x1c bytes, ctor 0x00472a00
    char pad0[0x0c];
    float mWidth;                                                        // +0x0c
    float mHeight;                                                       // +0x10
    float mOffsetX;                                                      // +0x14
    float mOffsetY;                                                      // +0x18
    cBakeSprite();                                                       // 0x00472a00
};

struct cBakeMaterial {                                                   // 0x1c bytes, ctor 0x0077d1d0
    void* mpVtbl;                                                        // +0x00
    int mRefCount;                                                       // +0x04
    char pad08[0x1c - 0x0c];
    cBakeMaterial();                                                     // 0x0077d1d0
    void AddRef() { _InterlockedIncrement((long*)&mRefCount); }
    void Release();                                                      // 0x00404f90
    void PushBack(cBakeSprite* sprite);                                  // 0x0077d970
};

struct cBakeSeg {                                                        // 16-byte uv rectangle of a block
    float mX0;                                                           // +0x00
    float mY0;                                                           // +0x04
    float mX1;                                                           // +0x08
    float mY1;                                                           // +0x0c
};

struct cSkinObject {                                                     // 0xbc bytes, ctor 0x004c6ba0
    void* mpVtbl;                                                        // +0x00
    int mRefCount;                                                       // +0x04
    Releasable* mpSource;                                                // +0x08
    char pad0C[0x18 - 0x0c];
    cSPMatrix4 mTransform;                                               // +0x18
    char pad58[0xbc - 0x58];
    cSkinObject();                                                       // 0x004c6ba0
    void AddRef() { _InterlockedIncrement((long*)&mRefCount); }
    void Release();                                                      // 0x00404f90
    bool UpdateBlocks(cSPEditorBlock** blocks, unsigned count, int flags); // 0x004c73f0
    void SetSource(Releasable* p) { IntrusiveAssign(&mpSource, p); }
};

struct cBakeSkin {                                                       // skin the export is built on
    void* mpVtbl;                                                        // +0x00
    int mRefCount;                                                       // +0x04
    char pad08[0x90 - 0x08];
    cBakeSeg* mpSegs;                                                    // +0x90
    char pad94[0xb8 - 0x94];
    cBakeMaterial* mpMaterial;                                           // +0xb8
    char padBC[0xc0 - 0xbc];
    PtrVector<cSPEditorBlock*> mBlocks;                                  // +0xc0
    char padCC[0xe4 - 0xcc];
    PtrVector<cBakeMaterial*> mMaterials;                                // +0xe4
    void AddRef() { _InterlockedIncrement((long*)&mRefCount); }
    void Release();                                                      // 0x00404f90
    void SetMaterial(cBakeMaterial* p) { IntrusiveAssign(&mpMaterial, p); }
    void SetMaterialRef(int index, cBakeMaterial* p) { IntrusiveAssign(&mMaterials.mpBegin[index], p); }
};

struct cSkinBuildInfo {                                                  // resource handed to the editor model
    char pad0[0x18];
    cSPTransform mTransform;                                             // +0x18
};

struct cSkinBuildTarget : Releasable {                                   // object the built skin is written back into
    char pad04[0x18 - 0x04];
    cSPTransform mTransform;                                             // +0x18
};

// 0x00401010 singleton; slot +0x60 hands out the world the model is attached to
struct Universe {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual Releasable* GetWorld(int a, int b, int c);                   // +0x60
};
extern Universe* FUN_00401010();                                         // 0x00401010

extern Vector3T* FUN_0046bfd0(Vector3T* out, cSPEditorModel* model);    // 0x0046bfd0 (returns out)
extern void FUN_004934d0(cSPEditorModel* model, cSPVector3 position, int flags); // 0x004934d0

// @ 0x0046d840
bool F_0046d840(const cSkinBuildInfo* info, cSkinBuildTarget* target)
{
    ModelRef model = new (kEditorAllocName, 0, 0, 0, 0) cSPEditorModel;
    if (!model->LoadResource(info) ||
        !model->FUN_004ae260(FUN_00401010()->GetWorld(0, 0, 0)))
        return false;
    cSPVector3 center;
    FUN_0046bfd0((Vector3T*)&center, model);
    FUN_004934d0(model.operator->(), center, 0);
    AutoRefCount<cSkinObject> skin = new (kEditorAllocName, 0, 0, 0, 0) cSkinObject;
    IntrusiveAssign((Releasable**)&skin.mpPtr->mpSource, (Releasable*)target);
    bool built = skin->UpdateBlocks(model->GetBlocks(), model->GetBlockCount(), 0);
    skin = 0;
    model->FUN_004ad330();
    model = 0;
    target->mTransform = info->mTransform;
    return built;
}

// 0x004604f0 (the depth is pushed as a float, the callee reads the bits as its `unused` argument)
extern void BuildCreatureMaterialInfo(cBakeMaterial* out, unsigned id, int tex0, int tex1, float unused,
                                      char skipLookup);

// @ 0x0046dad0
void F_0046dad0(cBakeSkin* skin, unsigned id, int tex0, int tex1)
{
    float depth = kMaterialDepth;
    cBakeMaterial* material = new (kEditorAllocName, 0, 0, 0, 0) cBakeMaterial;
    skin->SetMaterial(material);
    BuildCreatureMaterialInfo(skin->mpMaterial, id, tex0, tex1, depth, 1);
    skin->mMaterials.erase(skin->mMaterials.mpBegin, skin->mMaterials.mpEnd);
    skin->mMaterials.resize(skin->mBlocks.size());
    for (int i = 0, n = skin->mBlocks.size(); i < n; i++) {
        cSPEditorBlock* block = skin->mBlocks.mpBegin[i];
        if (!block)
            continue;
        if (block->mFlags.test(0x0a))
            continue;
        cBakeSeg* seg = &skin->mpSegs[i];
        AutoRefCount<cBakeMaterial> mat = new (kEditorAllocName, 0, 0, 0, 0) cBakeMaterial;
        BuildCreatureMaterialInfo(mat.mpPtr, id, tex0, tex1, depth, 1);
        cBakeSprite* sprite = new (kEditorAllocName, 0, 0, 0, 0) cBakeSprite;
        float height = seg->mY1 - seg->mY0;
        float width = seg->mX1 - seg->mX0;
        float x = seg->mX0;
        float y = seg->mY0;
        sprite->mWidth = width;
        sprite->mHeight = height;
        sprite->mOffsetX = x;
        sprite->mOffsetY = y;
        mat->PushBack(sprite);
        skin->SetMaterialRef(i, mat.mpPtr);
    }
}

// ---- export buffers --------------------------------------------------------

struct cVertexRec {                                                      // 0x14: four bone indices plus four weights
    unsigned char mIndex[4];                                             // +0x00
    float mWeight[4];                                                    // +0x04
};
struct cTriIndex {                                                       // 0x0c
    int mPosition;                                                       // +0x00
    int mNormal;                                                         // +0x04
    int mUv;                                                             // +0x08
};
struct cTangentFrame {                                                   // 0x18 (indexed by the uv index)
    float mValue[6];
};
struct Weights4 {
    float mWeight[4];
};
struct Color4U16 {
    unsigned short mIndex[4];
};

struct cExportMaterial {
    char pad0[0x6c];
    int* mpIndexBegin;                                                   // +0x6c
    int* mpIndexEnd;                                                     // +0x70
    char pad74[0x80 - 0x74];
    cTriIndex* mpTriBegin;                                               // +0x80
    cTriIndex* mpTriEnd;                                                 // +0x84
};

struct cBakeSource {                                                     // object reached through cExportRequest::mpSource
    char pad0[8];
    SpVector<Vector3T> mPositions;                                       // +0x08
    SpVector<Vector3T> mNormals;                                         // +0x1c
    SpVector<Vector2T> mUvs;                                             // +0x30
    SpVector<cTangentFrame> mTangents;                                   // +0x44
    char pad58[0xe4 - 0x58];
    cExportMaterial** mpMaterials;                                       // +0xe4
    cExportMaterial** mpMaterialsEnd;                                    // +0xe8
};

struct cMaterialTypeEntry {                                              // 0x8c
    char pad0[8];
    unsigned short mFlags;                                               // +0x08
    char padA[1];
    unsigned char mType;                                                 // +0x0b
    char padC[0x80];
};

struct cExportConfig {
    char pad0[0x98];
    cMaterialTypeEntry* mpEntries;                                       // +0x98
    cMaterialTypeEntry* mpEntriesEnd;                                    // +0x9c
};

struct cExportRequest {
    char pad0[8];
    cExportConfig* mpConfig;                                             // +0x08
    char pad0C[0x34 - 0x0c];
    cBakeSource* mpSource;                                               // +0x34
    char pad38[0x7c - 0x38];
    cVertexRec* mpVertices;                                              // +0x7c
    cVertexRec* mpVerticesEnd;                                           // +0x80
};

struct cExportBuffers {
    char pad0[0x0c];
    SpVector<unsigned> mIndices;                                         // +0x0c
    SpVector<Vector3T> mPositions;                                       // +0x20
    SpVector<Vector3T> mNormals;                                         // +0x34
    SpVector<Vector3T> mTangents;                                        // +0x48
    SpVector<Vector2T> mUvs;                                             // +0x5c
    SpVector<Color4U16> mColors;                                         // +0x70
    SpVector<Weights4> mWeights;                                         // +0x84
    IntVector mMaterialTypes;                                            // +0x98
};

// @ 0x0046de70
bool F_0046de70(cExportRequest* request, cExportBuffers* out)
{
    cBakeSource* source = request->mpSource;
    if (!source)
        return false;
    int vertexCount = (int)((const char*)request->mpVerticesEnd - (const char*)request->mpVertices) / 0x14;
    if (vertexCount != (int)((const char*)source->mPositions.mpEnd - (const char*)source->mPositions.mpBegin) / 0x0c)
        return false;
    unsigned triCount = 0;
    unsigned indexCount = 0;
    int materialCount = (int)(source->mpMaterialsEnd - source->mpMaterials);
    for (int i = 0; i < materialCount; i++) {
        cExportMaterial* material = source->mpMaterials[i];
        triCount += (unsigned)((const char*)material->mpTriEnd - (const char*)material->mpTriBegin) / 0x0c;
        indexCount += (unsigned)(material->mpIndexEnd - material->mpIndexBegin);
    }
    out->mIndices.reserve(indexCount);
    out->mPositions.reserve(triCount);
    out->mNormals.reserve(triCount);
    out->mUvs.reserve(triCount);
    out->mTangents.reserve(triCount);
    out->mColors.reserve(triCount);
    out->mWeights.reserve(triCount);
    const Vector3T* positions = source->mPositions.mpBegin;
    const Vector3T* normals = source->mNormals.mpBegin;
    const Vector2T* uvs = source->mUvs.mpBegin;
    const cTangentFrame* tangents = source->mTangents.mpBegin;
    const cVertexRec* vertices = request->mpVertices;
    int entryCount =
        (int)((const char*)request->mpConfig->mpEntriesEnd - (const char*)request->mpConfig->mpEntries) / 0x8c;
    const cMaterialTypeEntry* entries = request->mpConfig->mpEntries;
    for (int i = 0, n = (int)(source->mpMaterialsEnd - source->mpMaterials); i < n; i++) {
        cExportMaterial* material = source->mpMaterials[i];
        const cTriIndex* tri = material->mpTriBegin;
        const int* index = material->mpIndexBegin;
        int baseIndex =
            (int)((const char*)out->mPositions.mpEnd - (const char*)out->mPositions.mpBegin) / 0x0c;
        for (int t = (int)((const char*)material->mpTriEnd - (const char*)material->mpTriBegin) / 0x0c; t > 0; t--) {
            out->mPositions.push_back(*(const Vector3T*)((const char*)positions + tri->mPosition * 0x0c));
            out->mNormals.push_back(*(const Vector3T*)((const char*)normals + tri->mNormal * 0x0c));
            out->mUvs.push_back(*(const Vector2T*)((const char*)uvs + tri->mUv * 0x08));
            out->mTangents.push_back(*(const Vector3T*)((const char*)tangents + tri->mUv * 0x18));
            const cVertexRec* vertex = &vertices[tri->mPosition];
            Color4U16 color;
            color.mIndex[0] = (unsigned short)(vertex->mIndex[0] * 3);
            color.mIndex[1] = (unsigned short)(vertex->mIndex[1] * 3);
            color.mIndex[2] = (unsigned short)(vertex->mIndex[2] * 3);
            color.mIndex[3] = (unsigned short)(vertex->mIndex[3] * 3);
            out->mColors.push_back(color);
            out->mWeights.push_back(*(const Weights4*)vertex->mWeight);
            tri++;
        }
        for (int t = (int)(material->mpIndexEnd - material->mpIndexBegin); t > 0; t--) {
            unsigned value = (unsigned)(baseIndex + *index);
            out->mIndices.push_back(value);
            index++;
        }
    }
    out->mMaterialTypes.resize(entryCount);
    for (int i = 0; i < entryCount; i++) {
        const cMaterialTypeEntry* entry = &entries[i];
        if (entry->mType == 5) {
            out->mMaterialTypes.mpBegin[i] = 1;
        } else if (entry->mType == 3 && (entry->mFlags & 1)) {
            out->mMaterialTypes.mpBegin[i] = 2;
        } else if (entry->mType == 3 && !(entry->mFlags & 1)) {
            out->mMaterialTypes.mpBegin[i] = 3;
        } else if (entry->mType == 4) {
            out->mMaterialTypes.mpBegin[i] = 3;
        } else if (!(entry->mFlags & 8)) {
            out->mMaterialTypes.mpBegin[i] = 4;
        } else {
            out->mMaterialTypes.mpBegin[i] = 5;
        }
    }
    return true;
}
