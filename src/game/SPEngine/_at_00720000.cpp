// src/game/SPEngine/_at_00720000.cpp -- migrated from slice(s) s0072f830, s0072d5a0, s0072b630, s0071f410 by tools/migrate/rewrite.py
// Object file: SPEngine/_at_00720000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <string.h>
#include <intrin.h>
#include "rw/graphics/IndexBuffer.h"
#include "rw/graphics/VertexBuffer.h"
#include "rw/graphics/VertexDescriptor.h"
#include <new>
#include "rw/core/arena/Arena.h"
#include <xmmintrin.h>
#pragma intrinsic(_InterlockedExchange)

// ---- items of slice s0071f410 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vertex3D {
    uint32_t m[6];
};
// ---- items of slice s0071f410 end

// ---- items of slice s0072b630 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void FUN_0011e0744(void* a, void* b, int c);
struct FixedBoolVector {
    char* mpBegin;                       // +0x00
    char* mpEnd;                         // +0x04
    char* mpCapacity;                    // +0x08
    int   mOverflow;                     // +0x0c
    char* mpPoolBegin;                   // +0x10
    int   mPad;                          // +0x14
    char  mBuffer[16];                   // +0x18

    void insert(char* position, int count, int value);      // 0x004c6560 vector<bool>::insert(pos,count,value)
    __declspec(noinline) FixedBoolVector* FUN_0072c1e0(unsigned count, int value);
};
// ---- items of slice s0072b630 end

// ---- items of slice s0072d5a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedIncrement, _InterlockedDecrement, _InterlockedExchange)
#pragma pack(push, 1)
#pragma pack(pop)
typedef unsigned int u32;
typedef unsigned short u16;
void* operator new(size_t size, const char* name, int a, int b, int c, int d);  // 0x00f473a0
void operator delete[](void* p);  // 0x00f47380
struct IRC {
    virtual int AddRef() = 0;
    virtual int Release() = 0;
};
template <typename T>
struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    AutoRefCount& operator=(const AutoRefCount& x)
    {
        T* const pObject = x.mpObject;
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject) pObject->AddRef();
            mpObject = pObject;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
    AutoRefCount& operator=(T* pObject)
    {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject) pObject->AddRef();
            mpObject = pObject;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
};
struct VBView {
    u32 mGroup;
    u32 mOffset;
    u16 mSize;
    u16 mStride;
    AutoRefCount<IRC> mVB;
    VBView() : mGroup(0), mOffset(0), mSize(0), mStride(0) {}
    VBView(u32 g, u32 o, u16 s, u16 st, const AutoRefCount<IRC>& vb)
        : mGroup(g), mOffset(o), mSize(s), mStride(st), mVB(vb) {}
};
struct Elem32 {
    u32 mType;
    u32 mUsage;
    u32 mFormat;
    u32 mCategory;
    VBView mView;
    Elem32() {}
    Elem32(u32 a, u32 b, u32 c, u32 d, const VBView& v) : mType(a), mUsage(b), mFormat(c), mCategory(d), mView(v) {}
};
struct Elem20 {
    u32 mKind;
    u32 mSection;
    u32 mStart;
    u32 mEnd;
    u32 mIndex;
};
struct Elem32Vec {
    Elem32* mpBegin;
    Elem32* mpEnd;
    Elem32* mpCapacity;
    u32 mAlloc[2];
    Elem32Vec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    void Resize(u32 n);              // 0x00475260
    void PushBack(const Elem32& e);  // 0x0041f7d0
};
struct Elem20Vec {
    Elem20* mpBegin;
    Elem20* mpEnd;
    Elem20* mpCapacity;
    u32 mAlloc[2];
    Elem20Vec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    void DoInsertValue(Elem20* pos, const Elem20& v);  // 0x00428900
    void push_back(const Elem20& v)
    {
        if (mpEnd < mpCapacity) {
            ::new ((void*)mpEnd) Elem20(v);
            ++mpEnd;
        } else
            DoInsertValue(mpEnd, v);
    }
};
struct U32Vec {
    u32* mpBegin;
    u32* mpEnd;
    u32* mpCapacity;
    u32 mAlloc[2];
    U32Vec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    void Insert(u32* pos, u32 n, const u32& v);  // 0x0071e870
};
struct Section {
    VBView mIB;       // +0x00
    u32 mGroupId;     // +0x10
    U32Vec mV;        // +0x14
    u32 pad28[(0x8c - 0x28) / 4];
};
struct SectionVec {
    Section* mpBegin;
    Section* mpEnd;
    Section* mpCapacity;
    u32 mAlloc[2];
    SectionVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    void PushDefault();  // 0x00475430
};
struct GmeRefCount {
    virtual ~GmeRefCount() {}
    volatile long mRef;
    GmeRefCount() { _InterlockedExchange(&mRef, 0); }
};
struct GmeModel : GmeRefCount {
    Elem32Vec mElems;      // +0x08
    SectionVec mSections;  // +0x1c
    Elem20Vec mRanges;     // +0x30
    U32Vec mSpare;         // +0x44
    void AddRef() { _InterlockedExchangeAdd(&mRef, 1); }
    void Release()
    {
        if (_InterlockedDecrement(&mRef) == 0) {
            _InterlockedExchange(&mRef, 1);
            delete this;
        }
    }
};
struct GmePtr {
    GmeModel* mp;
    GmePtr(GmeModel* p) : mp(p) { if (mp) mp->AddRef(); }
    GmePtr(const GmePtr& x) : mp(x.mp) { if (mp) mp->AddRef(); }
    ~GmePtr() { if (mp) mp->Release(); }
};
struct GmePtrVec {
    GmePtr* mpBegin;
    GmePtr* mpEnd;
    GmePtr* mpCapacity;
    GmePtrVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~GmePtrVec();                                      // 0x0041eb80
    void DoInsertValue(GmePtr* pos, const GmePtr& v);  // 0x00424430
    void push_back(const GmePtr& v)
    {
        if (mpEnd < mpCapacity) {
            ::new ((void*)mpEnd) GmePtr(v);
            ++mpEnd;
        } else
            DoInsertValue(mpEnd, v);
    }
};
int FUN_0072c270(GmePtrVec* meshes, void* extent, void* arr, void* leaf, void* kd);
// ---- items of slice s0072d5a0 end

// ---- items of slice s0072f830 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
struct MaterialManagerStub {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
    virtual void MakeMesh(unsigned count, void* aux, void* meshes);  // +0x38 vtable slot 14 (ret 0xc)
    virtual void v3c();
    virtual void* MakeEntry(void* obj, void* a5);                    // +0x40 vtable slot 16 (ret 8)
};
MaterialManagerStub* __cdecl SP_MaterialManager();                            // 0x0067dd70
void __cdecl FUN_0072d6a0(unsigned count, void* first, void* array, void* a4, void* a5); // 0x0072d6a0
void __cdecl FUN_0072f9b0(void* resource, void* outMeshes);                   // 0x0072f9b0
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags,
                   const char* file, int line);                                 // 0x00f473a0
namespace palette {
typedef unsigned int u32_s0072_f830;
}
namespace palette {
typedef unsigned short u16_s0072_f830;
}
namespace palette {
void* __cdecl memmove(void* d, const void* s, unsigned n);                       // 0x011e0744
}
namespace palette {
template<class T> struct intrusive_ptr {
    T* mpObject;
    intrusive_ptr() : mpObject(0) {}
    intrusive_ptr(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    intrusive_ptr(const intrusive_ptr& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~intrusive_ptr() { if (mpObject) mpObject->Release(); }
    T* get() const { return mpObject; }
    T* operator->() const { return mpObject; }
};
}
namespace palette {
struct IObject {
    virtual int AddRef() = 0;
    virtual int Release() = 0;
};
}
namespace palette {
struct BufferRef {
    int  mCount;
    int  mpData;
    u16_s0072_f830  mSize0;
    u16_s0072_f830  mSize1;
    intrusive_ptr<IObject> mpOwner;
    BufferRef(int count, int data, u16_s0072_f830 s0, u16_s0072_f830 s1, IObject* owner)
        : mCount(count), mpData(data), mSize0(s0), mSize1(s1), mpOwner(owner) {}
};
}
namespace palette {
struct StreamElem {
    int mUsage, mIndex, mFormat, mFlags;
    BufferRef mBuffer;
    StreamElem(int usage, int index, int format, int flags, const BufferRef& buffer)
        : mUsage(usage), mIndex(index), mFormat(format), mFlags(flags), mBuffer(buffer) {}
};
}
namespace palette {
template<class T> struct vector {
    T*  mpBegin;
    T*  mpEnd;
    T*  mpCapacity;
    u32_s0072_f830 mAllocator[2];
    void DoInsertValue(T* pos, const T& value);              // 0x00424cf0, out of line, thiscall ret 8
    void push_back(const T& value)
    {
        if (mpEnd < mpCapacity)
            ::new((void*)mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
};
}
namespace palette {
struct RefCounted {
    virtual ~RefCounted();
    volatile long mnRefCount;
    void AddRef();
    void Release();
};
}
namespace palette {
struct Mesh : RefCounted {                       // 0x58 bytes
    vector<StreamElem> mStreams;                 // +0x08
};
}
namespace palette {
struct PtrVector {
    void** mpBegin;
    void** mpEnd;
    void** mpCapacity;
    u32_s0072_f830 mAllocator[2];                           // allocator payload (never initialised)
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
}
namespace palette {
struct ArenaPair {
    int a, b;
    ArenaPair();             // 0x006c0fa0
    ~ArenaPair();            // 0x00c2e4e0
};
}
namespace palette {
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
}
namespace palette {
struct Arena {
    int  GetNumExportedObjects();                                   // 0x011e23a0
    void GetExportedObjectByIndex(int index, ArenaExportInfo* out); // 0x011e28e0
};
}
namespace palette {
struct RWResource : IObject {
    u32_s0072_f830 pad04[5];
    Arena* mpArena;                                                 // +0x18
};
}
namespace palette {
struct SkinMatrices {
    struct Matrix44* mpData;
    int mCount;
};
}
namespace palette {
struct SkinObject {
    u32_s0072_f830 pad[4];
    SkinMatrices* mpMatrices;
};
}
namespace palette {
struct Matrix44 {
    __m128 row[4];
    Matrix44() {}
    Matrix44(const Matrix44& o) { row[3] = o.row[3]; row[2] = o.row[2]; row[1] = o.row[1]; row[0] = o.row[0]; }
};
}
namespace palette {
inline void StoreColumn(const Matrix44& source, int c, float* out)
{
    Matrix44 m(source);
    out[0] = m.row[0].m128_f32[c];
    out[1] = m.row[1].m128_f32[c];
    out[2] = m.row[2].m128_f32[c];
    out[3] = m.row[3].m128_f32[c];
}
}
namespace palette {
struct MatrixPalette : IObject {
    u32_s0072_f830 mVtbl2;                                  // +0x04 second base vtable
    u32_s0072_f830 mRefCount;                               // +0x08
    float* mpData;                               // +0x0c
    u32_s0072_f830 pad[5];
    virtual int AddRef();
    virtual int Release();
    MatrixPalette(int count);                    // 0x0072ac60, thiscall ret 4
    BufferRef GetBufferRef();                    // 0x0072a130, thiscall ret 4
};
}
namespace palette {
void __cdecl FUN_0072e010(RWResource& resource, vector<intrusive_ptr<Mesh> >& outMeshes);   // 0x0072e010
}
namespace resfac {
typedef unsigned int u32_s0072_f830;
}
namespace resfac {
struct Key {
    u32_s0072_f830 mInstance; u32_s0072_f830 mType; u32_s0072_f830 mGroup;
    Key(u32_s0072_f830 instance, u32_s0072_f830 type, u32_s0072_f830 group) : mInstance(instance), mType(type), mGroup(group) {}
};
}
namespace resfac {
struct IRefObj {
    virtual int AddRef();    // +0x00
    virtual int Release();   // +0x04
};
}
namespace resfac {
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
}
namespace resfac {
struct ResDesc {
    u32_s0072_f830 pad00;       // +0x00
    u32_s0072_f830 pad04;       // +0x04
    u32_s0072_f830 mInstance;   // +0x08
    u32_s0072_f830 mType;       // +0x0c
    u32_s0072_f830 mGroup;      // +0x10
};
}
namespace resfac {
struct PartHolder : IRefObj {
    uint32_t mData[21];                      // +0x04  opaque holder state (0x58 total)
    PartHolder(const palette::Mesh* part);   // 0x0040f070, thiscall ret 4
};
}
namespace resfac {
template<class T> struct RV {
    T* mpBegin; T* mpEnd; T* mpCapacity; u32_s0072_f830 mAlloc[2];
    void DoInsertValue(T* pos, const T& value);   // 0x00424430, thiscall ret 8
    void push_back(const T& value)
    {
        if (mpEnd < mpCapacity)
            ::new((void*)mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
};
}
namespace resfac {
struct CEditorRes : IRefObj {
    u32_s0072_f830 pad04[5];
    RV<palette::intrusive_ptr<palette::Mesh> > mParts;   // +0x18
    CEditorRes();                                        // 0x00763100
};
}
namespace resfac {
struct ResourceManager {
virtual void r00();
virtual void r04();
virtual void r08();
virtual void r0c();
virtual void r10();
    virtual bool GetResource(const Key& key, void* outRef);   // +0x14
};
}
namespace resfac {
ResourceManager* __cdecl GetManager();       // 0x0067dcd0
}
namespace resfac {
bool __cdecl FUN_006acfe0(void* key, void* desc);   // 0x006acfe0
}
namespace resfac {
bool __cdecl SetCachingType(int type, void* desc);  // 0x006ac040
}
// ---- items of slice s0072f830 end

// @ 0x00720200
void Obj15_20200(Vertex3D* first, Vertex3D* last, Vertex3D* dest)
{
    if (first == last)
        return;
    do {
        if (dest)
            *dest = *first;
        ++first;
        ++dest;
    } while (first != last);
}

// @ 0x0072c1e0
FixedBoolVector* FixedBoolVector::FUN_0072c1e0(unsigned count, int value)
{
    char* buf = mBuffer;

    mpBegin = buf;
    mpEnd = buf;
    mpCapacity = buf + 16;
    mpPoolBegin = buf;
    if (count > 0) {
        insert(mpEnd, count, value);
        return this;
    }
    // count == 0: the inlined tail of vector<bool>::insert is the empty range copy of the elements
    // after the insertion point (always empty here, the point is the end) plus the end adjustment.
    char* src = mpEnd;
    char* dst = src + count;
    FUN_0011e0744(dst, src, src - dst + count);
    mpEnd = mpEnd + count;
    return this;
}

// @ 0x0072d5a0
extern "C" int __cdecl FUN_0072d5a0(GmeModel* obj, void* extent, void* arr, void* leaf, void* kd)
{
    GmePtrVec meshes;
    meshes.push_back(GmePtr(obj));
    return FUN_0072c270(&meshes, extent, arr, leaf, kd);
}

// @ 0x0072f830
void __cdecl FUN_0072f830(unsigned count, void* first, void* aux, void* a3, void* a4)
{
    MaterialManagerStub* mgr = SP_MaterialManager();
    SmallVec local(count);
    mgr->MakeMesh(count, aux, local.mpBegin);
    FUN_0072d6a0(count, first, local.mpBegin, a3, a4);
}

// @ 0x0072f8d0
namespace palette {
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
}  // namespace palette

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

// @ 0x0072fff0
void __cdecl FUN_0072fff0(resfac::ResDesc* desc, resfac::RV<palette::intrusive_ptr<resfac::PartHolder> >* out)
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
