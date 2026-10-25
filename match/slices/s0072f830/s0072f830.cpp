// Slice s0072f830 — mesh materialisation entry points.
//   00730210 is reconstructed; the others are partial.
#include "types.h"
#include <xmmintrin.h>

// ---- external helpers the three entry points call ----
// Local small-vector (0x58 bytes, 0x40-byte inline buffer at +0x18); constructed with a count hint.
void operator delete[](void* p) throw();                                        // 0x00f47380
struct SmallVec {
    void* mpBegin;      // +0x00
    void* mpEnd;        // +0x04
    void* mpCapacity;   // +0x08
    void* pad0;         // +0x0c
    void* mpInline;     // +0x10  points at +0x18 (the inline buffer)
    void* pad1;         // +0x14
    void* mBuffer[16];  // +0x18  0x40-byte inline storage
    SmallVec(unsigned count);                   // 0x0072c180, thiscall ret 4
    ~SmallVec() { if (mpBegin && mpBegin != mpInline) operator delete[](mpBegin); }
};
// The global material manager singleton and the resource manager singleton.
struct MaterialManagerStub {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34();
    virtual void MakeMesh(unsigned count, void* aux, void* meshes);  // +0x38 vtable slot 14 (ret 0xc)
    virtual void v3c();
    virtual void* MakeEntry(void* obj, void* a5);                    // +0x40 vtable slot 16 (ret 8)
};
MaterialManagerStub* __cdecl SP_MaterialManager();                            // 0x0067dd70

void __cdecl FUN_0072d6a0(unsigned count, void* first, void* array, void* a4, void* a5); // 0x0072d6a0
void __cdecl FUN_0072f9b0(void* resource, void* outMeshes);                   // 0x0072f9b0
void __cdecl MergeMeshesIntoModels(unsigned count, void* first, void* array, void* a4, void* a5);

// @ 0x0072f830  (local mesh-list builder: size a local vector, make the mesh, merge into models)
// 5 cdecl args: count / first / aux([p+0xb8]) / a3 / a4 (see FUN_00730210).
void __cdecl FUN_0072f830(unsigned count, void* first, void* aux, void* a3, void* a4)
{
    MaterialManagerStub* mgr = SP_MaterialManager();
    SmallVec local(count);
    mgr->MakeMesh(count, aux, local.mpBegin);
    FUN_0072d6a0(count, first, local.mpBegin, a3, a4);
}

// @ 0x00730210
void FUN_00730210(int* p, int param_2)
{
    int  b8    = *(int*)((char*)p + 0xb8);
    int  base  = p[6];
    int  count = (p[7] - base) >> 2;
    FUN_0072f830(count, (void*)base, (void*)b8, (void*)param_2, (void*)p);
}

// mesh materialisation (0072f9b0): build the per-mesh bone-matrix palette stream
// (flags /O2 /MD /Gy /EHsc /TP /arch:SSE /GS-)
//   1. walk the arena's exported objects: 0x2001a mesh sections (collected), 0x200af vertex data
//      (hands the whole arena to FUN_0072e010, which builds the meshes);
//   2. no vertex data but sections: build models from the sections (FUN_0072f8d0), then clear them;
//   3. for a 0x7000c skin object: convert its 4x4 matrices to 3x4 (transposed) rows in a new matrix
//      palette and attach its buffer as stream 0x12 to every built mesh.
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags,
                   const char* file, int line);                                 // 0x00f473a0
inline void* operator new(unsigned int, void* p) throw() { return p; }

namespace palette {

typedef unsigned int u32;
typedef unsigned short u16;

void* __cdecl memmove(void* d, const void* s, unsigned n);                       // 0x011e0744

template<class T> struct intrusive_ptr {
    T* mpObject;
    intrusive_ptr() : mpObject(0) {}
    intrusive_ptr(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    intrusive_ptr(const intrusive_ptr& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~intrusive_ptr() { if (mpObject) mpObject->Release(); }
    T* get() const { return mpObject; }
    T* operator->() const { return mpObject; }
};

struct IObject {
    virtual int AddRef() = 0;
    virtual int Release() = 0;
};

// A view on a buffer: element count, data pointer, two element sizes, owning object.
struct BufferRef {
    int  mCount;
    int  mpData;
    u16  mSize0;
    u16  mSize1;
    intrusive_ptr<IObject> mpOwner;
    BufferRef(int count, int data, u16 s0, u16 s1, IObject* owner)
        : mCount(count), mpData(data), mSize0(s0), mSize1(s1), mpOwner(owner) {}
};

// One vertex stream of a mesh (0x20 bytes); vector overflow insert is 0x00424cf0.
struct StreamElem {
    int mUsage, mIndex, mFormat, mFlags;
    BufferRef mBuffer;
    StreamElem(int usage, int index, int format, int flags, const BufferRef& buffer)
        : mUsage(usage), mIndex(index), mFormat(format), mFlags(flags), mBuffer(buffer) {}
};

template<class T> struct vector {
    T*  mpBegin;
    T*  mpEnd;
    T*  mpCapacity;
    u32 mAllocator[2];
    void DoInsertValue(T* pos, const T& value);              // 0x00424cf0, out of line, thiscall ret 8
    void push_back(const T& value)
    {
        if (mpEnd < mpCapacity)
            ::new((void*)mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
};

struct RefCounted {
    virtual ~RefCounted();
    volatile long mnRefCount;
    void AddRef();
    void Release();
};
struct Mesh : RefCounted {                       // 0x58 bytes
    vector<StreamElem> mStreams;                 // +0x08
};

// Plain pointer vector (no allocator payload): begin / end / capacity, grown by 0x006ec4a0.
struct PtrVector {
    void** mpBegin;
    void** mpEnd;
    void** mpCapacity;
    u32 mAllocator[2];                           // allocator payload (never initialised)
    int size() const { return (int)(mpEnd - mpBegin); }
    PtrVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~PtrVector() { if (mpBegin && ((int*)mpBegin)[-1]) operator delete[](mpBegin); }
    void DoInsertValue(void** pos, void* const& value);      // 0x006ec4a0, thiscall ret 8
    void push_back(void* const& value)
    {
        if (mpEnd < mpCapacity)
            ::new((void*)mpEnd++) (void*)(value);
        else
            DoInsertValue(mpEnd, value);
    }
    void clear()
    {
        void** first = mpBegin;
        void** last = mpEnd;
        memmove(first, last, (unsigned)((mpEnd - last) * sizeof(void*)));
        mpEnd = mpEnd - (last - first);
    }
};

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
struct RWResource : IObject {
    u32 pad04[5];
    Arena* mpArena;                                                 // +0x18
};

// Skin object (arena type 0x7000c): +0x10 points at {matrices, count}.
struct SkinMatrices {
    struct Matrix44* mpData;
    int mCount;
};
struct SkinObject {
    u32 pad[4];
    SkinMatrices* mpMatrices;
};

struct Matrix44 {
    __m128 row[4];
    Matrix44() {}
    Matrix44(const Matrix44& o) { row[3] = o.row[3]; row[2] = o.row[2]; row[1] = o.row[1]; row[0] = o.row[0]; }
};
// Writes column c of the matrix (rows 0..3) to out[0..3].
inline void StoreColumn(const Matrix44& source, int c, float* out)
{
    Matrix44 m(source);
    out[0] = m.row[0].m128_f32[c];
    out[1] = m.row[1].m128_f32[c];
    out[2] = m.row[2].m128_f32[c];
    out[3] = m.row[3].m128_f32[c];
}

// Palette of 3x4 matrices (0x24 bytes, 0x30 bytes per entry); constructed by 0x0072ac60.
struct MatrixPalette : IObject {
    u32 mVtbl2;                                  // +0x04 second base vtable
    u32 mRefCount;                               // +0x08
    float* mpData;                               // +0x0c
    u32 pad[5];
    virtual int AddRef();
    virtual int Release();
    MatrixPalette(int count);                    // 0x0072ac60, thiscall ret 4
    BufferRef GetBufferRef();                    // 0x0072a130, thiscall ret 4
};

} // namespace palette

namespace palette {
void __cdecl FUN_0072e010(RWResource& resource, vector<intrusive_ptr<Mesh> >& outMeshes);   // 0x0072e010

// @ 0x0072f8d0  (build one output mesh per source range: MakeEntry for each range element,
//                then merge the model array into the meshes)
// 4 cdecl args: modelVec / srcVec / meshes / resource.
void __cdecl Fn0072f8d0_impl(PtrVector* modelVec, PtrVector* srcVec, void* meshes, void* resource)
{
    MaterialManagerStub* mgr = SP_MaterialManager();

    SmallVec local((unsigned)srcVec->size());
    int n = srcVec->size();

    for (int i = 0; i < n; ++i)
        ((void**)local.mpBegin)[i] = mgr->MakeEntry(srcVec->mpBegin[i], resource);

    FUN_0072d6a0(modelVec->size(), modelVec->mpBegin,
                 local.mpBegin, meshes, resource);
}
}

// @ 0x0072f9b0
void FUN_0072f9b0(palette::RWResource* resource, palette::vector<palette::intrusive_ptr<palette::Mesh> >* meshes)
{
    using namespace palette;
    Arena* arena = resource->mpArena;
    int numObjects = arena->GetNumExportedObjects();

    PtrVector sectionObjs;
    PtrVector sectionRanges;
    bool builtFromVertexData = false;

    for (int i = 0; i < numObjects; ++i) {
        ArenaExportInfo info;
        arena->GetExportedObjectByIndex(i, &info);
        switch (info.mTypeId) {
        case 0x2001a: {
            void* a = ((void**)info.mpObject)[0];
            void* b = ((void**)info.mpObject)[2];
            if (a && b) {
                sectionObjs.push_back(a);
                sectionRanges.push_back(b);
            }
            break;
        }
        case 0x200af:
            FUN_0072e010(*resource, *meshes);
            builtFromVertexData = true;
            break;
        }
    }
    if (!builtFromVertexData && sectionObjs.mpBegin != sectionObjs.mpEnd) {
        Fn0072f8d0_impl(&sectionObjs, &sectionRanges, meshes, resource);
        sectionObjs.clear();
        sectionRanges.clear();
    }

    for (int i = 0; i < numObjects; ++i) {
        ArenaExportInfo info;
        arena->GetExportedObjectByIndex(i, &info);
        if (info.mTypeId == 0x7000c) {
            SkinMatrices* skin = ((SkinObject*)info.mpObject)->mpMatrices;
            if (meshes->mpBegin != meshes->mpEnd) {
                MatrixPalette* palette = new("Graphics", 0, 0, 0, 0) MatrixPalette(skin->mCount);
                for (int m = 0; m < skin->mCount; ++m) {
                    float* dst = palette->mpData + m * 12;
                    StoreColumn(skin->mpData[m], 0, dst);
                    StoreColumn(skin->mpData[m], 1, dst + 4);
                    StoreColumn(skin->mpData[m], 2, dst + 8);
                }
                for (unsigned k = 0; k < (unsigned)(meshes->mpEnd - meshes->mpBegin); ++k)
                    meshes->mpBegin[k]->mStreams.push_back(StreamElem(0x12, 0, 0xe, 5, palette->GetBufferRef()));
            }
        }
    }
}

namespace resfac {

typedef unsigned int u32;

// EA::ResourceMan::Key: three dwords (instance, type, group).
struct Key {
    u32 mInstance; u32 mType; u32 mGroup;
    Key(u32 instance, u32 type, u32 group) : mInstance(instance), mType(type), mGroup(group) {}
};

// Refcounted base: vtable slot 0 = AddRef, slot 1 = Release.
struct IRefObj {
    virtual int AddRef();    // +0x00
    virtual int Release();   // +0x04
};

// EA::AutoRefCount<T>: one pointer, AddRef on copy/assign, Release on destruction.
template<class T> struct RefPtr {
    T* mpObject;
    RefPtr() : mpObject(0) {}
    RefPtr(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    RefPtr(const RefPtr& o) : mpObject(o.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~RefPtr() { if (mpObject) mpObject->Release(); }
    RefPtr& operator=(T* p)
    {
        if (p != mpObject) {
            if (p) p->AddRef();
            T* old = mpObject;
            mpObject = p;
            if (old) old->Release();
        }
        return *this;
    }
    T* get() const { return mpObject; }
    T* operator->() const { return mpObject; }
};

// Descriptor passed in by the caller: the same Key triple lives at +0x08.
struct ResDesc {
    u32 pad00;       // +0x00
    u32 pad04;       // +0x04
    u32 mInstance;   // +0x08
    u32 mType;       // +0x0c
    u32 mGroup;      // +0x10
};

// PartHolder (0x58 bytes): refcounted wrapper around a mesh/part.
struct PartHolder : IRefObj {
    uint32_t mData[21];                      // +0x04  opaque holder state (0x58 total)
    PartHolder(const palette::Mesh* part);   // 0x0040f070, thiscall ret 4
};

// Ref-vector (begin / end / capacity + allocator payload), grown out of line.
template<class T> struct RV {
    T* mpBegin; T* mpEnd; T* mpCapacity; u32 mAlloc[2];
    void DoInsertValue(T* pos, const T& value);   // 0x00424430, thiscall ret 8
    void push_back(const T& value)
    {
        if (mpEnd < mpCapacity)
            ::new((void*)mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
};

// Resource entry created when the resource is not cached (0x2c bytes).
struct CEditorRes : IRefObj {
    u32 pad04[5];
    RV<palette::intrusive_ptr<palette::Mesh> > mParts;   // +0x18
    CEditorRes();                                        // 0x00763100
};

// Resource manager: vtable slot 5 (0x14) looks a resource up by key.
struct ResourceManager {
    virtual void r00(); virtual void r04(); virtual void r08(); virtual void r0c(); virtual void r10();
    virtual bool GetResource(const Key& key, void* outRef);   // +0x14
};
ResourceManager* __cdecl GetManager();       // 0x0067dcd0

bool __cdecl FUN_006acfe0(void* key, void* desc);   // 0x006acfe0
bool __cdecl SetCachingType(int type, void* desc);  // 0x006ac040

} // namespace resfac

// @ 0x0072fff0  build/lookup the cached editor resource then fill the output part vector
//   1. build the resource key from the descriptor, look it up in the resource manager;
//   2. on a miss, create a CEditorRes, build its meshes (FUN_0072f9b0) and register it;
//   3. wrap every mesh of the resource in a PartHolder and append it to the output vector.
void __cdecl FUN_0072fff0(resfac::ResDesc* desc,
                          resfac::RV<palette::intrusive_ptr<resfac::PartHolder> >* out)
{
    using namespace resfac;

    Key key(desc->mInstance, 0x1c135da, desc->mGroup);
    RefPtr<CEditorRes> resource;

    if (!GetManager()->GetResource(key, &resource)) {
        resource = new("Graphics", 0, 0, 0, 0) CEditorRes();
        FUN_0072f9b0(desc, &resource->mParts);
        desc->mInstance = key.mInstance;
        desc->mType     = key.mType;
        desc->mGroup    = key.mGroup;
        FUN_006acfe0(&key, desc);
        SetCachingType(4, desc);
    }

    int count = (int)(resource->mParts.mpEnd - resource->mParts.mpBegin);
    for (int i = 0; i < count; ++i) {
        PartHolder* holder = new("Graphics", 0, 0, 0, 0) PartHolder(resource->mParts.mpBegin[i].get());
        out->push_back(palette::intrusive_ptr<PartHolder>(holder));
    }
}
