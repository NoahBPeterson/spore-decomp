// Slice s0072e010 — RenderWare arena -> graphics mesh builder (single 6.2 KB /O2 function).
//
// FUN_0072e010 walks the exported objects of an RW4 arena, sorts them by type into three
// fixed_vectors (0x200af vertex/skin data, 0x20007 index buffers, 0x2001a mesh sections),
// then builds one refcounted Mesh per vertex/index-buffer pair: vertex streams (positions,
// normals, tangents, texcoords, blend indices/weights, morph deltas), an index remap table,
// a primitive list (one entry per section that uses that index buffer) and a material list,
// and appends the mesh to the output vector.
//
// Names are role-based guesses; all callees are masked relocations.
// Flags: /O2 /MD /Gy /EHsc /TP /GS-  (original has an EH frame but no security cookie).
#include "types.h"

typedef unsigned int   u32;
typedef unsigned short u16;

extern "C" long __cdecl _InterlockedExchange(volatile long* target, long value);
extern "C" long __cdecl _InterlockedIncrement(volatile long* target);
extern "C" long __cdecl _InterlockedDecrement(volatile long* target);
#pragma intrinsic(_InterlockedExchange, _InterlockedIncrement, _InterlockedDecrement)

inline void* operator new(unsigned int, void* p) throw() { return p; }
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags,
                   const char* file, int line);                         // 0x00f473a0
void operator delete[](void* p);                                         // 0x00f47380

// ---------------------------------------------------------------------------
// Minimal EASTL-shaped containers
// ---------------------------------------------------------------------------
template<class T> struct intrusive_ptr {
    T* mpObject;
    intrusive_ptr() : mpObject(0) {}
    intrusive_ptr(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    intrusive_ptr(const intrusive_ptr& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~intrusive_ptr() { if (mpObject) mpObject->Release(); }
    intrusive_ptr& operator=(const intrusive_ptr& x)
    {
        T* p = x.mpObject;
        if (p != mpObject) {
            T* pTemp = mpObject;
            if (p) p->AddRef();
            mpObject = p;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
    T* get() const { return mpObject; }
    T* operator->() const { return mpObject; }
};

template<class T> struct vector {
    T*  mpBegin;
    T*  mpEnd;
    T*  mpCapacity;
    u32 mAllocator[2];

    vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    int  size() const { return (int)(mpEnd - mpBegin); }
    bool empty() const { return mpBegin == mpEnd; }
    T&   operator[](int i) { return mpBegin[i]; }

    void DoInsertValue(T* pos, const T& value);                    // out of line
    void DoInsertValues(T* pos, unsigned n, const T& value);       // out of line

    void push_back(const T& value)
    {
        if (mpEnd < mpCapacity)
            ::new((void*)mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
    T* erase(T* first, T* last)
    {
        T* d = first;
        for (T* s = last; s != mpEnd; ++s, ++d)
            *d = *s;
        mpEnd -= (last - first);
        return first;
    }
    void resize(unsigned n)
    {
        if (n > (unsigned)(mpEnd - mpBegin))
            DoInsertValues(mpEnd, n - (unsigned)(mpEnd - mpBegin), T());
        else
            erase(mpBegin + n, mpEnd);
    }
};

// eastl::fixed_vector<void*, 8> (0x38 bytes); overflow insert is 0x006c1570.
struct fixed_ptr_vector {
    void** mpBegin;      // +0x00
    void** mpEnd;        // +0x04
    void** mpCapacity;   // +0x08
    u32    mAlloc0;      // +0x0c
    void** mpPoolBegin;  // +0x10
    u32    mAlloc1;      // +0x14
    void*  mBuffer[8];   // +0x18

    fixed_ptr_vector()
    {
        mpPoolBegin = mBuffer;
        mpBegin = mpEnd = mpPoolBegin;
        mpCapacity = mBuffer + 8;
    }
    ~fixed_ptr_vector()
    {
        if (mpBegin && mpBegin != mpPoolBegin)
            operator delete[](mpBegin);
    }
    int   size() const { return (int)(mpEnd - mpBegin); }
    void* operator[](int i) const { return mpBegin[i]; }

    void DoInsertValue(void** pos, void* const& value);           // 0x006c1570
    void push_back(void* const& value)
    {
        if (mpEnd < mpCapacity)
            ::new((void*)mpEnd++) (void*)(value);
        else
            DoInsertValue(mpEnd, value);
    }
};

// ---------------------------------------------------------------------------
// Graphics types
// ---------------------------------------------------------------------------
struct IObject {
    virtual int AddRef() = 0;
    virtual int Release() = 0;
};

// Refcounted base with non-virtual atomic AddRef/Release (vtbl 0x013ef094).
struct RefCounted {
    RefCounted() { _InterlockedExchange(&mnRefCount, 0); }
    virtual ~RefCounted();
    void AddRef() { _InterlockedIncrement(&mnRefCount); }
    void Release()
    {
        if (_InterlockedDecrement(&mnRefCount) == 0) {
            _InterlockedExchange(&mnRefCount, 1);
            delete this;
        }
    }
    volatile long mnRefCount;
};

// A view on a buffer: element count, data pointer, two element sizes, owning object.
struct BufferRef {
    int  mCount;                      // +0x00
    int  mpData;                      // +0x04
    u16  mSize0;                      // +0x08
    u16  mSize1;                      // +0x0a
    intrusive_ptr<IObject> mpOwner;   // +0x0c

    BufferRef(int count, int data, u16 s0, u16 s1, IObject* owner)
        : mCount(count), mpData(data), mSize0(s0), mSize1(s1), mpOwner(owner) {}
};

// One vertex stream of a mesh (0x20 bytes); vector overflow insert is 0x00424cf0.
struct StreamElem {
    int mUsage;       // 1 pos, 2 normal, 3 tangent, 8 texcoord, 9 blend idx, 0xa blend wt, 0xb-0xe morph, 0x15 material
    int mIndex;
    int mFormat;
    int mFlags;
    BufferRef mBuffer;

    StreamElem(int usage, int index, int format, int flags, const BufferRef& buffer)
        : mUsage(usage), mIndex(index), mFormat(format), mFlags(flags), mBuffer(buffer) {}
};

struct RemapEntry {
    u16 mFrom;
    u16 mTo;
    RemapEntry() : mFrom(0), mTo(0) {}
    RemapEntry(u16 from, u16 to) : mFrom(from), mTo(to) {}
};

struct IndexData {
    BufferRef          mBuffer;       // +0x00
    int                mVertexCount;  // +0x10
    vector<RemapEntry> mRemap;        // +0x14  (DoInsertValues = 0x0071e870)
};
template<> void vector<IndexData>::resize(unsigned n);                 // 0x0071f7e0

// Primitive range (0x14 bytes); vector overflow insert is 0x00428900.
struct PrimRange {
    int mType;
    int mFlags;
    int mStart;
    int mEnd;
    int mIndex;
};

struct Mesh : RefCounted {                           // 0x58 bytes, vtbl 0x013eb8d0
    vector<StreamElem> mStreams;   // +0x08
    vector<IndexData>  mIndices;   // +0x1c
    vector<PrimRange>  mPrims;     // +0x30
    vector<u32>        mExtra;     // +0x44
    virtual ~Mesh();
};

struct MaterialList : IObject, RefCounted {          // 0x24 bytes, vtbls 0x013ef09c/0x013ef098
    vector<u32> mMaterials;        // +0x0c  (DoInsertValue = 0x004558a0)
    int         mField20;          // +0x20
    MaterialList() : mField20(0) {}
    virtual int AddRef();
    virtual int Release();
    virtual ~MaterialList();
    BufferRef GetBufferRef();                       // 0x004728e0
};

// Vertex data block (arena type 0x200af); all accessors are tiny out-of-line getters.
struct VertexData {
    int  GetVertexCount();          // 0x008e7f80  [+0x34]
    int  GetMorphCount();           // 0x005aacf0  [+0x30]
    int  GetPositions();            // 0x00fcc210  [+0x04]
    int  GetNormals();              // 0x0093b6c0  [+0x08]
    int  GetTangents();             // 0x00fc7e50  [+0x0c]
    int  GetTexCoords();            // 0x007f54d0  [+0x10]
    bool HasNormals();              // 0x006c10f0
    bool HasTangents();             // 0x006c1100
    bool HasTexCoords();            // 0x006c1110
    bool HasBlendData();            // 0x006c1140
    bool HasDeltaData();            // 0x006c1120
    int  GetBonesPerVertex();       // 0x006c10e0  [+0x3c]
    int  GetPaddedBones();          // 0x006c0fc0
    int  GetBlendIndices(int n);    // 0x006c1160
    int  GetBlendWeights(int n);    // 0x006c0fd0
    int  GetDeltaCount();           // 0x00a1ad10  [+0x38]
    int  GetDeltaIndices(int n);    // 0x006c0ff0
    int  GetDeltaPositions(int n);  // 0x006c1020
    int  GetDeltaNormals(int n);    // 0x006c1040
    int  GetDeltaTangents(int n);   // 0x006c1060
    int  GetMorphPositions(int n);  // 0x006c1080
    int  GetMorphNormals(int n);    // 0x006c10a0
    int  GetMorphTangents(int n);   // 0x006c10c0
};

// Index buffer (arena type 0x20007).
struct IndexBuffer {
    u32 pad0[2];
    int mIndexCount;   // +0x08
    u32 pad0c[2];
    int mPrimType;     // +0x14
};

struct SectionRange {
    u32 pad0[2];
    IndexBuffer* mpIndexBuffer;  // +0x08
    u32 pad0c[2];
    int mStart;                  // +0x14
    int mCount;                  // +0x18
};

// Mesh section (arena type 0x2001a).
struct MeshSection {
    SectionRange* mpRange;   // +0x00
    u32 pad04;
    void* mpMaterial;        // +0x08
};

namespace rw { namespace core { namespace arena {
struct ArenaPair {
    int a, b;
    ArenaPair();             // 0x006c0fa0
    ~ArenaPair();            // 0x00c2e4e0
};
struct ArenaExportInfo {     // 0x38 bytes
    int   mTypeId;
    void* mpObject;
    int   f08, f0c, f10, f14;
    ArenaPair mPairs[4];
    ArenaExportInfo() : mTypeId(0), mpObject(0), f08(0), f0c(0), f10(0), f14(0)
    {
        mPairs[0].a = 0;
        mPairs[0].b = 1;
    }
};
struct Arena {
    int  GetNumExportedObjects();                                   // 0x011e23a0
    void GetExportedObjectByIndex(int index, ArenaExportInfo* out); // 0x011e28e0
};
}}}

struct RWResource : IObject {
    u32 pad04[5];
    rw::core::arena::Arena* mpArena;   // +0x18
};

struct IMaterialManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual u32  GetMaterial(void* material, RWResource* owner);    // +0x40
};
namespace SP { IMaterialManager* MaterialManager(); }                // 0x0067dd70

int GetIndexBufferData(IndexBuffer* ib, RWResource* owner, intrusive_ptr<IObject>* outOwner); // 0x00729bd0

// ---------------------------------------------------------------------------
// @ 0x0072e010
// ---------------------------------------------------------------------------
void FUN_0072e010(RWResource& resource, vector< intrusive_ptr<Mesh> >& outMeshes)
{
    using namespace rw::core::arena;

    Arena* arena = resource.mpArena;
    int numObjects = arena->GetNumExportedObjects();
    IMaterialManager* materialMgr = SP::MaterialManager();

    fixed_ptr_vector vertexDatas;    // 0x200af
    fixed_ptr_vector indexBuffers;   // 0x20007
    fixed_ptr_vector sections;       // 0x2001a

    for (int i = 0; i < numObjects; ++i) {
        ArenaExportInfo info;
        arena->GetExportedObjectByIndex(i, &info);
        switch (info.mTypeId) {
        case 0x20007: indexBuffers.push_back(info.mpObject); break;
        case 0x2001a: sections.push_back(info.mpObject); break;
        case 0x200af: vertexDatas.push_back(info.mpObject); break;
        }
    }

    int primIndex = 0;
    int numMeshes = vertexDatas.size();
    for (int meshIndex = 0; meshIndex < numMeshes; ++meshIndex) {
        IndexBuffer* ib = (IndexBuffer*)indexBuffers[meshIndex];
        VertexData*  vd = (VertexData*)vertexDatas[meshIndex];
        bool streamsBuilt = false;

        Mesh* mesh = new("Graphics", 0, 0, 0, 0) Mesh;
        intrusive_ptr<Mesh> meshPtr(mesh);
        intrusive_ptr<MaterialList> materials(new("Graphics", 0, 0, 0, 0) MaterialList);

        int numSections = sections.size();
        for (int s = 0; s < numSections; ++s) {
            MeshSection* section = (MeshSection*)sections[s];
            SectionRange* range = section->mpRange;
            void* material = section->mpMaterial;
            if (range->mpIndexBuffer != ib)
                continue;

            if (!streamsBuilt) {
                streamsBuilt = true;
                int vertexCount = vd->GetVertexCount();
                int morphCount = vd->GetMorphCount();

                mesh->mStreams.push_back(StreamElem(1, meshIndex, 3, 0,
                    BufferRef(vertexCount, vd->GetPositions(), 0xc, 0x10, &resource)));
                if (vd->HasNormals())
                    mesh->mStreams.push_back(StreamElem(2, meshIndex, 3, 1,
                        BufferRef(vertexCount, vd->GetNormals(), 0xc, 0x10, &resource)));
                if (vd->HasTangents())
                    mesh->mStreams.push_back(StreamElem(3, meshIndex, 3, 1,
                        BufferRef(vertexCount, vd->GetTangents(), 0xc, 0x10, &resource)));
                if (vd->HasTexCoords())
                    mesh->mStreams.push_back(StreamElem(8, meshIndex, 2, 2,
                        BufferRef(vertexCount, vd->GetTexCoords(), 8, 0x10, &resource)));

                if (vd->HasBlendData()) {
                    int indexFormat;
                    int indexSize0, indexSize1;
                    switch (vd->GetBonesPerVertex()) {
                    case 0:
                        indexFormat = 0;
                        indexSize1 = 0;
                        indexSize0 = 0;
                        break;
                    case 1:
                    case 2:
                        indexFormat = 8;
                        indexSize1 = indexSize0 = vd->GetPaddedBones() * 2;
                        break;
                    default:
                        indexFormat = 9;
                        indexSize0 = 8;
                        indexSize1 = vd->GetPaddedBones() * 2;
                        break;
                    }

                    int weightFormat;
                    int weightSize0, weightSize1;
                    switch (vd->GetBonesPerVertex()) {
                    case 0:  weightFormat = 0; weightSize1 = 0;   weightSize0 = 0;   break;
                    case 1:  weightSize1 = 4;   weightFormat = 1; weightSize0 = 4;   break;
                    case 2:  weightSize1 = 8;   weightFormat = 2; weightSize0 = 8;   break;
                    case 3:  weightSize1 = 0xc; weightFormat = 3; weightSize0 = 0xc; break;
                    default:
                        weightFormat = 4;
                        weightSize0 = 0x10;
                        weightSize1 = vd->GetBonesPerVertex() * 4;
                        break;
                    }

                    mesh->mStreams.push_back(StreamElem(9, meshIndex, indexFormat, 0,
                        BufferRef(vertexCount, vd->GetBlendIndices(0),
                                  (u16)indexSize0, (u16)indexSize1, 0)));
                    mesh->mStreams.push_back(StreamElem(0xa, meshIndex, weightFormat, 0,
                        BufferRef(vertexCount, vd->GetBlendWeights(0),
                                  (u16)weightSize0, (u16)weightSize1, 0)));
                }

                if (vd->HasDeltaData()) {
                    int n = vd->GetDeltaCount();
                    for (int k = 0; k < n; ++k)
                        mesh->mStreams.push_back(StreamElem(0xb, k, 6, 0,
                            BufferRef(vertexCount, vd->GetDeltaIndices(k), 4, 4, 0)));
                    n = vd->GetDeltaCount();
                    for (int k = 0; k < n; ++k)
                        mesh->mStreams.push_back(StreamElem(0xc, k, 3, 0,
                            BufferRef(vertexCount, vd->GetDeltaPositions(k), 0xc, 0x10, 0)));
                    if (vd->HasNormals()) {
                        n = vd->GetDeltaCount();
                        for (int k = 0; k < n; ++k)
                            mesh->mStreams.push_back(StreamElem(0xd, k, 3, 0,
                                BufferRef(vertexCount, vd->GetDeltaNormals(k), 0xc, 0x10, 0)));
                    }
                    if (vd->HasTangents()) {
                        n = vd->GetDeltaCount();
                        for (int k = 0; k < n; ++k)
                            mesh->mStreams.push_back(StreamElem(0xe, k, 3, 0,
                                BufferRef(vertexCount, vd->GetDeltaTangents(k), 0xc, 0x10, 0)));
                    }
                } else {
                    for (int k = 0; k < morphCount; ++k)
                        mesh->mStreams.push_back(StreamElem(0xc, k, 3, 0,
                            BufferRef(vertexCount, vd->GetMorphPositions(k), 0xc, 0x10, 0)));
                    if (vd->HasNormals())
                        for (int k = 0; k < morphCount; ++k)
                            mesh->mStreams.push_back(StreamElem(0xd, k, 3, 0,
                                BufferRef(vertexCount, vd->GetMorphNormals(k), 0xc, 0x10, 0)));
                    if (vd->HasTangents())
                        for (int k = 0; k < morphCount; ++k)
                            mesh->mStreams.push_back(StreamElem(0xe, k, 3, 0,
                                BufferRef(vertexCount, vd->GetMorphTangents(k), 0xc, 0x10, 0)));
                }

                // Index buffer + identity vertex remap (one entry per stream).
                int indexCount = ib->mIndexCount;
                intrusive_ptr<IObject> ibOwner;
                int ibData = GetIndexBufferData(ib, &resource, &ibOwner);
                mesh->mIndices.resize(1);
                int numStreams = mesh->mStreams.size();
                mesh->mIndices[0].mRemap.resize(numStreams);
                for (int k = 0; k < numStreams; ++k)
                    mesh->mIndices[0].mRemap[k] = RemapEntry((u16)k, 0xffff);
                mesh->mIndices[0].mVertexCount = vertexCount;
                mesh->mIndices[0].mBuffer = BufferRef(indexCount, ibData, 2, 2, ibOwner.get());
            }

            int primType;
            switch (ib->mPrimType) {
            case 1:  primType = 1; break;
            case 2:  primType = 2; break;
            case 3:  primType = 3; break;
            case 5:  primType = 5; break;
            case 6:  primType = 6; break;
            default: primType = 4; break;
            }
            PrimRange prim;
            prim.mType = primType;
            prim.mFlags = 0;
            prim.mStart = range->mStart;
            prim.mEnd = range->mStart + range->mCount;
            prim.mIndex = primIndex++;
            mesh->mPrims.push_back(prim);

            u32 mat = materialMgr->GetMaterial(material, &resource);
            materials->mMaterials.push_back(mat);
        }

        if (!mesh->mPrims.empty()) {
            mesh->mStreams.push_back(StreamElem(0x15, 0, 6, 8, materials->GetBufferRef()));
            outMeshes.push_back(meshPtr);
        }
    }
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct URemapEntry {
    void DoInsertValues(void*, unsigned int, int&); // 0x004cea40
};
}
