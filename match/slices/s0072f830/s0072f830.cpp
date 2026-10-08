// Slice s0072f830 — mesh materialisation entry points.
//   00730210 is reconstructed; the others are partial.
#include "types.h"
#include <xmmintrin.h>

// @ 0x0072f830  (PARTIAL — skeleton; opaque sink so callers are not collapsed)
volatile int g_sink_72f830;
__declspec(noinline)
void FUN_0072f830(int count, int base, int b8, int a4, int a5)
{
    g_sink_72f830 = count + base + b8 + a4 + a5;
}

// @ 0x00730210
void FUN_00730210(int* p, int param_2)
{
    int  b8    = *(int*)((char*)p + 0xb8);
    int  base  = p[6];
    int  count = (p[7] - base) >> 2;
    FUN_0072f830(count, base, b8, param_2, (int)p);
}

// @ 0x0072f8d0  (PARTIAL)
void FUN_0072f8d0(void* a, void* b, void* c, void* d)
{
    (void)a; (void)b; (void)c; (void)d;
}

// @ 0x0072f9b0  build the per-mesh bone-matrix palette stream
// (flags /O2 /MD /Gy /EHsc /TP /arch:SSE /GS-)
//   1. walk the arena's exported objects: 0x2001a mesh sections (collected), 0x200af vertex data
//      (hands the whole arena to FUN_0072e010, which builds the meshes);
//   2. no vertex data but sections: build models from the sections (FUN_0072f8d0), then clear them;
//   3. for a 0x7000c skin object: convert its 4x4 matrices to 3x4 (transposed) rows in a new matrix
//      palette and attach its buffer as stream 0x12 to every built mesh.
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags,
                   const char* file, int line);                                 // 0x00f473a0
void operator delete[](void* p) throw();                                        // 0x00f47380
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
void __cdecl Fn0072f8d0(PtrVector* sections, PtrVector* ranges, void* meshes, void* resource); // 0x0072f8d0
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
        Fn0072f8d0(&sectionObjs, &sectionRanges, meshes, resource);
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

// @ 0x0072fff0  (PARTIAL)
void FUN_0072fff0(void* a)
{
    (void)a;
}
