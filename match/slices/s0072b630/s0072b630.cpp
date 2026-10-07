// Slice s0072b630 — mesh -> Rw compilation dispatch helpers.
// The three small dispatchers are reconstructed; the big compiler and the fixed-vector
// ctor are partial.
#include "types.h"
#include <intrin.h>

__declspec(noinline) void FUN_0072b630(void* mesh, void* a, void* b, void* c, void* d, void* e, void* f, void* g, void* h);
extern "C" {
    void FUN_00729c60(void* p, float* a, float* b);
    void FUN_004c6560(void* dst, void* src, void* n);
    void FUN_0011e0744(void* a, void* b, int c);
}

// @ 0x0072c040
void FUN_0072c040(int* vec, void* a2, void* a3, void* a4, void* a5, void* a6, void* a7, void* a8, void* a9)
{
    int n = (vec[1] - vec[0]) >> 2;
    for (int i = 0; i < n; ++i)
        FUN_0072b630((void*)((int*)vec[0])[i], a2, a3, a4, a5, a6, a7, a8, a9);
}

// @ 0x0072c0a0
void FUN_0072c0a0(void* a, char* b, void* p3, void* p4)
{
    FUN_0072b630(a, p4, b + 0x18, b + 0xb8, b + 0xf4, b + 0x68, b + 0x90, b + 0x40, p3);
    FUN_00729c60(a, (float*)(b + 0x11c), (float*)(b + 0x134));
}

// @ 0x0072c100
void FUN_0072c100(int* vec, int base, void* p3, void* p4)
{
    char* b = (char*)base;
    FUN_0072c040(vec, p4, b + 0x18, b + 0xb8, b + 0xf4, b + 0x68, b + 0x90, b + 0x40, p3);
    int n = (vec[1] - vec[0]) >> 2;
    for (int i = 0; i < n; ++i)
        FUN_00729c60((void*)((int*)vec[0])[i], (float*)(b + 0x11c), (float*)(b + 0x134));
}

// @ 0x0072b630  SP::CompileToRwMeshes
// Converts one source mesh (vertex elements, sub-meshes, primitive groups) into
// RenderWare vertex descriptors, vertex buffers, index buffers and meshes, plus the
// per-primitive materials and textures.

struct IRefObject {                       // virtual AddRef/Release (slots 0/1)
    virtual int AddRef();
    virtual int Release();
};

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
struct vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator;
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
    T& operator[](unsigned i) { return mpBegin[i]; }
    void DoInsertValue(T* position, const T& value);
    void push_back(const T& value) {
        if (mpEnd < mpCapacity)
            ::new(mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
};

inline void* operator new(unsigned, void* p) { return p; }

void operator_delete__(void* p) throw();  // 0x00f47380

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

// Strided view onto a typed source array (shared by elements, indices, ids).
extern const uint32_t kIndexMasks[];     // 0x0140d15c
struct DataAccessor {
    int         mCount;                  // +0x0
    char*       mpData;                  // +0x4
    uint16_t    mFormat;                 // +0x8
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
    template <typename T> T* At(int i) const { return (T*)(mpData + mStride * i); }
    template <typename T> T Index(int i) const { return *At<T>(i) & (T)kIndexMasks[mFormat]; }
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

// RenderWare objects.
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
struct IMaterialManager {
    virtual void f00(); virtual void f04(); virtual void f08(); virtual void f0c();
    virtual void f10(); virtual void f14(); virtual void f18(); virtual void f1c();
    virtual void f20(); virtual void f24();
    virtual Material* GetMaterial(uint32_t id);          // +0x28
};
typedef intrusive_ptr<RefCounted> TexturePtr;

extern int  FindElement(SourceMesh* mesh, int semantic, int index, int a, int b);  // 0x0071ddc0
extern VertexDescription* CreateVertexDescriptor(int n);                          // 0x00761650
extern VertexBuffer* CreateVertexBuffer(VertexDescription* d, int n, int a, int b); // 0x00762b70
extern IndexBuffer* CreateIndexBuffer(const void* fmt, int a, int n, int b, int primType, int c); // 0x00762c60
extern RwMesh* CreateMesh(int n);                                                 // 0x00761840
extern IMaterialManager* MaterialManager();                                       // 0x0067dd70
extern void CopyElement(VertexStream* dst, const DataAccessor* src, int n);       // 0x007296e0
extern void CopyElementIndexed(VertexStream* dst, const DataAccessor* src, const DataAccessor* idx, int n); // 0x00729760
extern const int kRwPrimTypes[];         // 0x01536f0c
extern const char kIndexFormat32[8];     // 0x015d07b8
extern const char kIndexFormat16[8];     // 0x015d07b0

// @ 0x00729560
int ToD3DDeclType(int type)
{
    switch (type) {
    case 1: return 0;
    case 2: return 1;
    case 3: return 2;
    case 4: return 3;
    case 5: return 4;
    case 7: return 5;
    case 10: return 8;
    case 8: return 6;
    case 9: return 7;
    case 11: return 9;
    case 12: return 10;
    }
    return -1;
}

// @ 0x007295f0
int ToRwDecl(int semantic, int index)
{
    switch (semantic) {
    case 1: if (index == 0) return 0; break;
    case 2: if (index == 0) return 2; break;
    case 8: if (index < 8) return index + 6; break;
    case 3: if (index == 0) return 0x13; break;
    case 5:
    case 7:
        if (index == 0) return 3;
        if (index == 1) return 5;
        break;
    case 6: if (index == 0) return 4; break;
    case 9: if (index == 0) return 0xe; break;
    case 10: if (index == 0) return 0xf; break;
    case 11: return 0x16;
    case 12: if (index == 0) return 0x11; break;
    case 13: if (index == 0) return 0x12; break;
    }
    return -1;
}

template <typename T>
inline void PushOutput(vector<T>* v, T x)
{
    v->push_back(x);
}

template <typename T>
inline void AddOutput(vector<T>* v, T x)
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

__declspec(noinline)
void FUN_0072b630(void* pMesh, void* pTextures, void* pMeshes, void* pMaterials, void* pTexturesOut,
                  void* pVertexBuffers, void* pVertexDescs, void* pIndexBuffers, void* pSemanticIndex)
{
    SourceMesh* mesh = (SourceMesh*)pMesh;
    vector<TexturePtr>* textures = (vector<TexturePtr>*)pTextures;
    vector<RwMesh*>* outMeshes = (vector<RwMesh*>*)pMeshes;
    vector<Material*>* outMaterials = (vector<Material*>*)pMaterials;
    vector<TexturePtr>* outTextures = (vector<TexturePtr>*)pTexturesOut;
    vector<VertexBuffer*>* outVertexBuffers = (vector<VertexBuffer*>*)pVertexBuffers;
    vector<VertexDescription*>* outVertexDescs = (vector<VertexDescription*>*)pVertexDescs;
    vector<IndexBuffer*>* outIndexBuffers = (vector<IndexBuffer*>*)pIndexBuffers;
    int semanticIndex = (int)pSemanticIndex;

    DataAccessor materialIds;
    if (outMaterials) {
        int idx = FindElement(mesh, 0x15, 0, 6, 0xe);
        if (idx >= 0)
            materialIds = mesh->mpElements[idx].mData;
    }

    DataAccessor textureIds;
    if (outTextures && textures) {
        int idx = FindElement(mesh, 0x14, 0, 6, 0xe);
        if (idx >= 0)
            textureIds = mesh->mpElements[idx].mData;
    }

    int nSubMeshes = (int)mesh->mSubMeshes.size();
    for (int i = 0; i < nSubMeshes; ++i) {
        const SubMesh& sm = mesh->mSubMeshes[i];
        fixed_vector<uint32_t, 16> rwDecls;
        fixed_vector<int, 16> elementIndices;
        fixed_vector<uint32_t, 16> declTypes;

        int nElements = (int)mesh->mSubMeshes[i].mElements.size();
        for (int j = 0; j < nElements; ++j) {
            const MeshElement& e = mesh->mpElements[mesh->mSubMeshes[i].mElements[j].mElement];
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
            const DataAccessor* src =
                &mesh->mpElements[mesh->mSubMeshes[i].mElements[j].mElement].mData;
            lock.GetElementStream(&stream, k);
            const SubMesh& cur = mesh->mSubMeshes[i];
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

// @ 0x0072c1e0  (PARTIAL: eastl fixed_vector ctor with EH)
void* FUN_0072c1e0(void* self, int n, void* a)
{
    (void)self; (void)n; (void)a;
    return self;
}
