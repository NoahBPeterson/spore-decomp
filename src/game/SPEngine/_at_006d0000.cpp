// src/game/SPEngine/_at_006d0000.cpp -- migrated from slice(s) s006deee0, s006de020, s006dd250, s006dbed0, s006d8880, s006d35a0 by tools/migrate/rewrite.py
// Object file: SPEngine/_at_006d0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <xmmintrin.h>
#include <string.h>
#include <new>
#include "rw/graphics/VertexBuffer.h"

// ---- items of slice s006d35a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct RefObject
{
    virtual void AddRef();
    virtual void Release();
};
struct Handle
{
    uint32_t a;         // +0
    uint32_t b;         // +4  data base
    uint16_t c;         // +8
    uint16_t d;         // +a  stride
    RefObject* mpRef;   // +c

    Handle() : a(0), b(0), c(0), d(0), mpRef(0) {}
    Handle(const Handle& o) : a(o.a), b(o.b), c(o.c), d(o.d), mpRef(o.mpRef)
    {
        if (mpRef)
            mpRef->AddRef();
    }
    ~Handle()
    {
        if (mpRef)
            mpRef->Release();
    }
    Handle* Assign(const Handle* src);   // out of line: 0x00424f70
};
struct Elem32
{
    uint32_t w0, w1, w2, w3;
    Handle handle;
};
struct ElemTable
{
    uint32_t p0;
    uint32_t p4;
    Elem32* mBegin;
};
struct BakeEntry
{
    uint32_t f0;        // +0   index into the param_5 (position) stream
    uint32_t f4;        // +4
    uint32_t f8;        // +8   index into the handle's colour stream
    uint32_t fc;        // +c   index into the handle's uv stream
    uint32_t f10;       // +10
    uint32_t f14;       // +14
};
struct StreamDesc
{
    uint32_t p0;
    uint32_t base;
    uint16_t p8;
    uint16_t stride;
    uint32_t pc;
};
struct ScaleInfo
{
    char pad[0x10];
    float scale;
};
void FUN_006c4200(void* out0, void* out1, const void* pos3, const void* dir3,
                  const void* color, const void* uv, int param);
// ---- items of slice s006d35a0 end

// ---- items of slice s006d8880 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double __cdecl acos(double);
extern "C" double __cdecl sqrt(double);
#define BAKE_PROLOG()                                                                                 \
    Elem32* base = table->mBegin;                                                                     \
    Handle hA = base[index].handle;                                                                   \
    Handle hB;                                                                                        \
    if (handleIndex >= 0)                                                                             \
        hB.Assign(&base[handleIndex].handle);                                                         \
    if (count == 0)                                                                                   \
        return true;                                                                                  \
    {                                                                                                 \
        float axisDir[3] = { 1.0f, 0.0f, 0.0f };                                                      \
        float white[4] = { 1.0f, 0.0f, 0.0f, 0.0f };                                                  \
        float* o = out;                                                                               \
        BakeEntry* e = entries;                                                                       \
        int n = count;                                                                                \
        do                                                                                            \
        {                                                                                             \
            float color[4];                                                                           \
            float p3[3];                                                                              \
            float res[3];                                                                             \
            float scratch[3];                                                                         \
            (void)white;                                                                              \
            (void)color; (void)p3; (void)res; (void)scratch;
#define BAKE_EPILOG()                                                                                 \
            o += 2;                                                                                   \
            e += 1;                                                                                   \
        } while (--n);                                                                                \
    }                                                                                                 \
    return true;
#define BAKE_TAIL_ACOS()                                                                              \
            float scale = scaleInfo->scale;                                                           \
            float dx = res[0] - axis[2];                                                              \
            float dy = res[1] - axis[3];                                                              \
            float sq = dx * dx + dy * dy;                                                             \
            float len = (float)sqrt((double)sq);                                                      \
            float angle = (float)acos((double)(dx / len));                                            \
            o[0] = ((axis[0] * angle) * 1.2732406f) * scale;                                          \
            o[1] = (1.0f - axis[1] * len) * scale;
struct RBNode
{
    RBNode* mpLeft;     // +0
    RBNode* mpRight;    // +4
    RBNode* mpParent;   // +8
    uint32_t mColour;   // +c
    int mKey;           // +10   value follows at +14
};
struct RBTree
{
    uint32_t mPad;      // +0
    RBNode anchor;      // +4
    void* FindOrInsert(const int* pKey);   // 0x006d95e0
};
struct TrueTypeTag { bool b; };
struct MapEntry
{
    int mKey;       // stored at node +0x10
    int mMapped;    // stored at node +0x14
};
struct TreeInsert
{
    void* DoInsertValue(void** out, RBNode* position, const MapEntry* value, TrueTypeTag tag);
};
struct VecElem
{
    void Destroy(void* elem);   // out-of-line helper 0x006c2ad0
    void Assign(const void* src);   // Handle::Assign 0x00424f70
    void Shift(void* first, void* last);   // 0x006df340
};
void* __cdecl FUN_006c2b10(void* first, void* last, void* dst);
void __cdecl FUN_0047d3f0(void* first, void* last, void* dst);
void __cdecl eastl_allocator_deallocate(void* p);
void* __cdecl eastl_allocator_allocate(uint32_t size, const char* tag, int a, int b,
                                       const char* file, int line);
struct HandleVec
{
    uint32_t mWords[5];
    void Insert(uint32_t position, uint32_t value);
};
// ---- items of slice s006d8880 end

// ---- items of slice s006dbed0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" long __cdecl _InterlockedExchangeAdd(long volatile* addend, long value);
extern "C" long __cdecl _InterlockedExchange(long volatile* target, long value);
extern const uint32_t kElementMask[];   // 0x140a644
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedExchange)
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);
void operator delete[](void* p);
struct IRefObject
{
    virtual void AddRef();     // slot 0
    virtual void Release();    // slot 1
};
struct Handle_s006d_bed0
{
    uint32_t    mCount;     // +0
    char*       mpData;     // +4
    uint16_t    mSize;      // +8
    uint16_t    mStride;    // +a
    IRefObject* mpOwner;    // +c

    Handle_s006d_bed0() : mCount(0), mpData(0), mSize(0), mStride(0), mpOwner(0) {}

    Handle_s006d_bed0(uint32_t count, char* pData, uint16_t size, uint16_t stride, IRefObject* pOwner)
        : mCount(count), mpData(pData), mSize(size), mStride(stride), mpOwner(pOwner)
    {
        if (mpOwner)
            mpOwner->AddRef();
    }

    Handle_s006d_bed0(const Handle_s006d_bed0& x);   // 0x006c2ad0

    ~Handle_s006d_bed0()
    {
        if (mpOwner)
            mpOwner->Release();
    }

    Handle_s006d_bed0& operator=(const Handle_s006d_bed0& x)
    {
        mCount  = x.mCount;
        mpData  = x.mpData;
        mSize   = x.mSize;
        mStride = x.mStride;
        if (mpOwner != x.mpOwner)
        {
            if (x.mpOwner)
                x.mpOwner->AddRef();
            IRefObject* const pOld = mpOwner;
            mpOwner = x.mpOwner;
            if (pOld)
                pOld->Release();
        }
        return *this;
    }

    uint32_t Get(uint32_t i) const
    {
        return *(const uint32_t*)(mpData + mStride * i) & kElementMask[mSize];
    }
};
struct Element
{
    uint32_t mType;     // +0
    uint32_t mUsage;    // +4
    uint32_t mCount;    // +8
    uint32_t mIndex;    // +c
    Handle_s006d_bed0   mHandle;   // +10

    Element(uint32_t type, uint32_t usage, uint32_t count, uint32_t index)
        : mType(type), mUsage(usage), mCount(count), mIndex(index), mHandle() {}

    Element(uint32_t type, uint32_t usage, uint32_t count, uint32_t index, const Handle_s006d_bed0& h)
        : mType(type), mUsage(usage), mCount(count), mIndex(index),
          mHandle(h.mCount, h.mpData, h.mSize, h.mStride, h.mpOwner) {}
};
struct StreamRef
{
    int16_t mElement;
    int16_t mStream;
};
struct Vector2
{
    float x, y;

    Vector2() {}
    Vector2(float x_, float y_) : x(x_), y(y_) {}
};
struct BakeVertex
{
    int32_t  mPos;      // +0
    int32_t  mAttrA;    // +4
    int32_t  mAttrB;    // +8
    int32_t  mAttrC;    // +c
    uint16_t mVertex;   // +10
    uint16_t mPad;      // +12
    int32_t  mUnused;   // +14
};
BakeVertex* CopyBakeVertices(BakeVertex* first, BakeVertex* last, BakeVertex* dest);   // 0x00720250
struct PrefixAllocator
{
    void deallocate(void* p)
    {
        if (p && ((int*)p)[-1] != 0)
            operator delete[](p);
    }
};
template <typename T>
struct SimpleVector
{
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;

    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
};
struct StreamRefVector : SimpleVector<StreamRef>
{
    void DoInsertValue(StreamRef* position, const StreamRef& value);   // 0x00476fe0

    void push_back(const StreamRef& value)
    {
        if (mpEnd < mpCapacity)
            ::new(mpEnd++) StreamRef(value);
        else
            DoInsertValue(mpEnd, value);
    }
};
struct HandleVector : SimpleVector<Handle_s006d_bed0>
{
    void push_back(const Handle_s006d_bed0& value);   // 0x006da2e0
};
struct ElementVector : SimpleVector<Element>
{
    uint32_t mAllocator[2];
    void push_back(const Element& value);  // 0x0041f7d0
};
struct Vector2Vector : SimpleVector<Vector2>
{
    void push_back(const Vector2& value);                                       // 0x00473f30
    void reserve(unsigned n);                                                   // 0x00473e40
    void DoInsertValue(Vector2* position, const Vector2& value);               // 0x00476000
    void DoInsertValues(Vector2* position, unsigned n, const Vector2& value);  // 0x00479830

    void PushBack(const Vector2& value)
    {
        if (mpEnd < mpCapacity)
            ::new(mpEnd++) Vector2(value);
        else
            DoInsertValue(mpEnd, value);
    }

    void erase(Vector2* first, Vector2* last)
    {
        Vector2* d = first;
        for (Vector2* s = last; s != mpEnd; ++s, ++d)
            *d = *s;
        mpEnd = mpEnd - (last - first);
    }

    void resize(unsigned n)
    {
        if (n > size())
            DoInsertValues(mpEnd, n - size(), Vector2());
        else
            erase(mpBegin + n, mpEnd);
    }
};
struct BakeVertexVector : SimpleVector<BakeVertex>
{
    PrefixAllocator mAllocator;

    BakeVertexVector() { mpBegin = 0; mpEnd = 0; mpCapacity = 0; }
    ~BakeVertexVector() { mAllocator.deallocate(mpBegin); }

    void DoInsertValue(BakeVertex* position, const BakeVertex& value);   // 0x007a44b0

    void push_back(const BakeVertex& value)
    {
        if (mpEnd < mpCapacity)
            ::new(mpEnd++) BakeVertex(value);
        else
            DoInsertValue(mpEnd, value);
    }

    void erase(BakeVertex* first, BakeVertex* last)
    {
        CopyBakeVertices(last, mpEnd, first);
        mpEnd = mpEnd - (last - first);
    }

    void clear() { erase(mpBegin, mpEnd); }

    // erase(first, end()): the copy is a no-op
    void EraseToEnd(BakeVertex* first) { mpEnd = mpEnd - (mpEnd - first); }
};
struct PrimIndexVector : SimpleVector<int>
{
    uint32_t        mPoolInfo[2];
    int             mBufferHeader;  // count word (0) in front of the buffer
    int             mBuffer[24];
    PrefixAllocator mAllocator;

    PrimIndexVector()
    {
        mBufferHeader = 0;
        mpBegin    = mBuffer;
        mpEnd      = mBuffer;
        mpCapacity = mBuffer + 24;
    }
    ~PrimIndexVector() { mAllocator.deallocate(mpBegin); }

    void erase(int* first, int* last)
    {
        memcpy(first, last, (char*)mpEnd - (char*)last);
        mpEnd = mpEnd - (last - first);
    }

    void clear() { erase(mpBegin, mpEnd); }
};
struct IntMapNode
{
    IntMapNode* mpNodeRight;    // +0
    IntMapNode* mpNodeLeft;     // +4
    IntMapNode* mpNodeParent;   // +8
    char        mColor;         // +c
    int         mKey;           // +10
    int         mValue;         // +14
};
struct IntMapAnchor
{
    IntMapNode* mpNodeRight;
    IntMapNode* mpNodeLeft;
    IntMapNode* mpNodeParent;
    char        mColor;
};
struct IntMap
{
    uint32_t     mCompare;
    IntMapAnchor mAnchor;   // +4
    unsigned     mnSize;    // +14

    IntMap()
    {
        mAnchor.mpNodeRight  = 0;
        mAnchor.mpNodeLeft   = 0;
        mAnchor.mpNodeParent = 0;
        mAnchor.mColor       = 0;
        mAnchor.mpNodeRight  = (IntMapNode*)&mAnchor;
        mAnchor.mpNodeLeft   = (IntMapNode*)&mAnchor;
        mAnchor.mpNodeParent = 0;
        mAnchor.mColor       = 0;
        mnSize = 0;
    }

    ~IntMap()
    {
        IntMapNode* pNode = mAnchor.mpNodeParent;
        while (pNode)
        {
            DoNukeSubtree(pNode->mpNodeRight);
            IntMapNode* const pNodeLeft = pNode->mpNodeLeft;
            operator delete[](pNode);
            pNode = pNodeLeft;
        }
    }

    void DoNukeSubtree(IntMapNode* pNode);   // 0x009a9600
    int& operator[](const int& key);         // 0x006d95e0

    bool contains(int key) const
    {
        const IntMapNode* pRangeEnd = (const IntMapNode*)&mAnchor;
        const IntMapNode* pCurrent  = mAnchor.mpNodeParent;
        while (pCurrent)
        {
            if (pCurrent->mKey < key)
                pCurrent = pCurrent->mpNodeRight;
            else
            {
                pRangeEnd = pCurrent;
                pCurrent  = pCurrent->mpNodeLeft;
            }
        }
        return (pRangeEnd != (const IntMapNode*)&mAnchor) && !(key < pRangeEnd->mKey);
    }
};
struct Geometry
{
    Handle_s006d_bed0          mIndices;   // +00 (index remap stream)
    uint32_t        mField10;   // +10
    StreamRefVector mStreamRefs;// +14
    uint32_t        mPad20[9];  // +20
    HandleVector    mStreams;   // +44
    uint32_t        mPad50[15]; // +50
};
struct Primitive
{
    int mType;      // +0
    int mGeometry;  // +4
    int mStart;     // +8
    int mEnd;       // +c
    int mMaterial;  // +10
};
struct Mesh_s006d_bed0
{
    virtual void DeleteThis(int flags);   // slot 0

    long                   mRefCount;   // +04
    ElementVector          mElements;   // +08
    SimpleVector<Geometry> mGeometries; // +1c
    uint32_t               mPad28[2];   // +28
    Primitive*             mpPrimBegin; // +30
    Primitive*             mpPrimEnd;   // +34

    void AddRef() { _InterlockedExchangeAdd(&mRefCount, 1); }

    void Release()
    {
        if (_InterlockedExchangeAdd(&mRefCount, -1) - 1 == 0)
        {
            _InterlockedExchange(&mRefCount, 1);
            DeleteThis(1);
        }
    }
};
template <typename T>
struct AutoRefCount
{
    T* mpObject;

    AutoRefCount(T* p) : mpObject(p)
    {
        if (mpObject)
            mpObject->AddRef();
    }
    ~AutoRefCount()
    {
        if (mpObject)
            mpObject->Release();
    }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
struct UVBuffer : public IRefObject
{
    void*         mpSecondVtbl; // +04
    long          mRefCount;    // +08
    Vector2Vector mVertices;    // +0c
    uint32_t      mAllocator;   // +18
    uint32_t      mField1C;     // +1c
    uint32_t      mField20;     // +20

    UVBuffer();                 // 0x006c3510
    Handle_s006d_bed0 GetHandle();         // 0x006c32f0
};
namespace rw {
namespace graphics {
    class EmbeddedState_s006d_bed0
    { public:
        uint32_t mPad[2];
        uint8_t  m_softStateDirty;   // +8
        const char* D3D9GetShaderData(uint32_t id);   // 0x011edcf0
    };
}
}
struct Material
{
    uint32_t                        mPad0;
    rw::graphics::EmbeddedState_s006d_bed0*    mpState;   // +4
};
struct IMaterialManager
{
virtual void f00();
virtual void f04();
virtual void f08();
virtual void f0c();
virtual void f10();
virtual void f14();
virtual void f18();
virtual void f1c();
virtual void f20();
virtual void f24();
    virtual Material* GetMaterial(uint32_t id);   // +0x28
};
namespace SP
{
    IMaterialManager* MaterialManager();                                             // 0x0067dd70
    void FindPrimitives(Mesh_s006d_bed0* mesh, PrimIndexVector* out, int geometry, int type, int material); // 0x0071ee10
}
int  FindElement(Mesh_s006d_bed0* mesh, int usage, int index, int type, int count);            // 0x0071ddc0
int  FindStream(Mesh_s006d_bed0* mesh, int geometry, int usage, int index, int type);          // 0x0071e090
void PrepareGeometry(Geometry* geometry);                                           // 0x007368a0
void AllocateStream(Handle_s006d_bed0* stream);                                                // 0x00720070
void SortBakeVertices(BakeVertex* first, BakeVertex* last);                         // 0x006c4c20
void FinishMesh(Mesh_s006d_bed0* mesh);                                                        // 0x00735a90
bool BakeType0(Vector2*, int, Mesh_s006d_bed0*, BakeVertex*, Handle_s006d_bed0*, const char*, int);   // 0x006dacf0
bool BakeType1(Vector2*, int, Mesh_s006d_bed0*, BakeVertex*, Handle_s006d_bed0*, const char*, int);   // 0x006db1d0
bool BakeType2(Vector2*, int, Mesh_s006d_bed0*, BakeVertex*, Handle_s006d_bed0*, const char*, int);   // 0x006db6b0
bool BakeType3(Vector2*, int, Mesh_s006d_bed0*, BakeVertex*, Handle_s006d_bed0*, const char*, int);   // 0x006c3080
bool BakeType4(Vector2*, int, Mesh_s006d_bed0*, BakeVertex*, Handle_s006d_bed0*, const char*, int);   // 0x006da9c0
bool BakeType5(Vector2*, int, Mesh_s006d_bed0*, BakeVertex*, Handle_s006d_bed0*, const char*, int);   // 0x006dbba0
bool BakeType6(Vector2*, int, Mesh_s006d_bed0*, BakeVertex*, Handle_s006d_bed0*, const char*, int);   // 0x006da360
bool BakeType7(Vector2*, int, Mesh_s006d_bed0*, BakeVertex*, Handle_s006d_bed0*, const char*, int);   // 0x006da690
static void StoreIndex(const Handle_s006d_bed0& h, uint32_t row, uint32_t value)
{
    switch (h.mSize)
    {
        case 1: *(uint8_t*)(h.mpData + h.mStride * row)  = (uint8_t)value;  break;
        case 2: *(uint16_t*)(h.mpData + h.mStride * row) = (uint16_t)value; break;
        case 4: *(uint32_t*)(h.mpData + h.mStride * row) = value;           break;
    }
}
// ---- items of slice s006dbed0 end

// ---- items of slice s006dd250 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int*  DAT_01607728;           // cBufferDrawImpl singleton
void __fastcall CompiledState_Dispatch(void* cs);
void __cdecl GlobalState_D3D9Sync();
void __fastcall FUN_006dd8b0(void* self);
struct CBufferDraw { void IssueDraw(int param_2); int Lock(int count, void* out, uint32_t* stride, int flag); bool FUN_006ddb40(int param_2, void* param_3, uint32_t* param_4, int param_5, int* param_6, int param_7); };
// ---- items of slice s006dd250 end

// ---- items of slice s006de020 begin (TODO(rewrite): local stubs, replace by canonical classes)
int __cdecl FUN_00762a30(void* p);
void __cdecl FUN_00f47410(void* p);
void* DAT_016079a0 = 0;
void* DAT_016079a4 = 0;
int DAT_016079a8 = 0;
struct Rec13
{
    int a, b;               // +0, +4
    float c;                // +8
    int d;                  // +c
    float e, f, g, h, i, j, k;   // +10..+28
    int l;                  // +2c
    float m;                // +30
    Rec13& operator=(const Rec13& src);   // 0x006de7f0
};
Rec13& Rec13::operator=(const Rec13& src)   // @ 0x006de7f0
{
    a = src.a;
    b = src.b;
    c = src.c;
    d = src.d;
    e = src.e;
    f = src.f;
    g = src.g;
    h = src.h;
    i = src.i;
    j = src.j;
    k = src.k;
    l = src.l;
    m = src.m;
    return *this;
}
// ---- items of slice s006de020 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void FUN_006dea60(int param_1, int param_2, int param_3, int param_4, Rec13 record);  // 0x006dea60 (stays in the slice: not this object's)

// ---- items of slice s006deee0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" long _InterlockedIncrement(volatile long*);
extern "C" long _InterlockedDecrement(volatile long*);
extern "C" void  FreeMem(void* p);                                                  // 0xf47380
typedef unsigned int uint;
struct IRefObj {                        // vtable[0]=AddRef, vtable[1]=Release
    virtual void AddRef();
    virtual void Release();
};
struct IntrusiveRef {
    IRefObj* mpObject;                  // +0x0
    IntrusiveRef& operator=(const IntrusiveRef& x) {
        IRefObj* src = x.mpObject;
        IRefObj* old = mpObject;
        if (src != old) {
            if (src)
                src->AddRef();
            mpObject = src;
            if (old)
                old->Release();
        }
        return *this;
    }
};
struct Elem16 {
    uint32_t f0;      // +0x0
    uint32_t f4;      // +0x4
    uint16_t f8;      // +0x8
    uint16_t fa;      // +0xa
    IntrusiveRef ref; // +0xc
};
struct RefCountObj {
    virtual void Delete(int flags);
    int mnRefCount;                     // +0x4
};
struct RefPtr {
    RefCountObj* mpObject;              // +0x0
    RefPtr& AssignRefPtr(const RefPtr* x);
    RefPtr& operator=(const RefPtr& x) {
        RefCountObj* src = x.mpObject;
        RefCountObj* old = mpObject;
        if (src != old) {
            if (src)
                _InterlockedIncrement((volatile long*)&src->mnRefCount);
            mpObject = src;
            if (old) {
                volatile long* p = (volatile long*)&old->mnRefCount;
                long n = _InterlockedDecrement(p);
                if (n == 0) {
                    _InterlockedExchange(p, 1);
                    old->Delete(1);
                }
            }
        }
        return *this;
    }
};
struct Elem16Vector {
    Elem16* mpBegin;    // +0x00
    Elem16* mpEnd;      // +0x04
    Elem16* mpCapacity; // +0x08
    void*   mpPad;      // +0x0c
    void*   mpInline;   // +0x10
    void Destroy();
    int Elem16VecEraseRange(int dest, int from);
    void Elem16VecInsert(int position, uint n, Elem16* value);
};
// ---- items of slice s006deee0 end

// @ 0x006d35a0
bool Bake_6d35a0(float* out, int count, ElemTable* table, BakeEntry* entries, StreamDesc* pos, float* axis, ScaleInfo* scaleInfo, int index, int handleIndex, int param10)
{
    Elem32* base = table->mBegin;
    Handle hA = base[index].handle;
    Handle hB;
    if (handleIndex >= 0)
        hB.Assign(&base[handleIndex].handle);
    if (count != 0)
    {
        float axisDir[3] = { 1.0f, 0.0f, 0.0f };
        float white[4] = { 1.0f, 0.0f, 0.0f, 0.0f };
        float* o = out;
        BakeEntry* e = entries;        int n = count;
        do
        {
            uint32_t u[4];
            uint16_t* s = (uint16_t*)(hA.b + hA.d * e->fc);
            u[0] = s[0] / 3; u[1] = s[1] / 3; u[2] = s[2] / 3; u[3] = s[3] / 3;
            float color[4];
            float* c = (float*)(hB.b + hB.d * e->f8);
            color[0] = c[0]; color[1] = c[1]; color[2] = c[2]; color[3] = c[3];
            float* ps = (float*)(pos->base + pos->stride * e->f0);
            float p3[3];
            p3[0] = ps[0]; p3[1] = ps[1]; p3[2] = ps[2];
            float res[3];
            float scratch[3];
            FUN_006c4200(res, scratch, p3, axisDir, color, (void*)u, param10);
            float scale = scaleInfo->scale;
            o[0] = (res[0] * axis[0] + axis[2]) * scale;
            o[1] = (1.0f - (res[1] * axis[1] + axis[3])) * scale;
            o += 2;
            e += 1;
        } while (--n);
    }
    return true;
}

// @ 0x006d8880
bool Bake_6d8880(float* out, int count, ElemTable* table, BakeEntry* entries, StreamDesc* pos, float* axis, ScaleInfo* scaleInfo, int index, int handleIndex, int param10)
{
    BAKE_PROLOG()
    uint16_t* s = (uint16_t*)(hA.b + hA.d * e->fc);
    uint32_t uv[4];
    uv[0] = s[0] / 3; uv[1] = s[1] / 3; uv[2] = s[2] / 3; uv[3] = s[3] / 3;
    (void)uv;
    {
        uint8_t* c = (uint8_t*)(hB.b + hB.d * e->f8);
        color[0] = (float)c[0] * (1.0f / 255.0f); color[1] = (float)c[1] * (1.0f / 255.0f);
        color[2] = (float)c[2] * (1.0f / 255.0f); color[3] = (float)c[3] * (1.0f / 255.0f);
    }
    float* ps = (float*)(pos->base + pos->stride * e->f0);
    p3[0] = ps[0]; p3[1] = ps[1]; p3[2] = ps[2];
    FUN_006c4200(res, scratch, p3, axisDir, color, uv, param10);
    BAKE_TAIL_ACOS()
    BAKE_EPILOG()
}

// @ 0x006d8c00
bool Bake_6d8c00(float* out, int count, ElemTable* table, BakeEntry* entries, StreamDesc* pos, float* axis, ScaleInfo* scaleInfo, int index, int handleIndex, int param10)
{
    BAKE_PROLOG()
    uint8_t* s = (uint8_t*)(hA.b + hA.d * e->fc);
    uint32_t uv[4];
    uv[0] = s[0] / 3; uv[1] = s[1] / 3; uv[2] = s[2] / 3; uv[3] = s[3] / 3;
    (void)uv;
    {
        float* c = (float*)(hB.b + hB.d * e->f8);
        color[0] = c[0]; color[1] = c[1]; color[2] = c[2]; color[3] = c[3];
    }
    float* ps = (float*)(pos->base + pos->stride * e->f0);
    p3[0] = ps[0]; p3[1] = ps[1]; p3[2] = ps[2];
    FUN_006c4200(res, scratch, p3, axisDir, color, uv, param10);
    BAKE_TAIL_ACOS()
    BAKE_EPILOG()
}

// @ 0x006d8f60
bool Bake_6d8f60(float* out, int count, ElemTable* table, BakeEntry* entries, StreamDesc* pos, float* axis, ScaleInfo* scaleInfo, int index, int handleIndex, int param10)
{
    BAKE_PROLOG()
    uint16_t* s = (uint16_t*)(hA.b + hA.d * e->fc);
    uint32_t uv[4];
    uv[0] = s[0] / 3; uv[1] = s[1] / 3;
    uv[2] = 0; uv[3] = 0;
    (void)uv;
    {
        float* c = (float*)(hB.b + hB.d * e->f8);
        color[0] = c[0]; color[1] = c[1]; color[2] = c[2]; color[3] = c[3];
    }
    float* ps = (float*)(pos->base + pos->stride * e->f0);
    p3[0] = ps[0]; p3[1] = ps[1]; p3[2] = ps[2];
    FUN_006c4200(res, scratch, p3, axisDir, color, uv, param10);
    BAKE_TAIL_ACOS()
    BAKE_EPILOG()
}

// @ 0x006d9280
bool Bake_6d9280(float* out, int count, ElemTable* table, BakeEntry* entries, StreamDesc* pos, float* axis, ScaleInfo* scaleInfo, int index, int handleIndex, int param10)
{
    BAKE_PROLOG()
    uint16_t* s = (uint16_t*)(hA.b + hA.d * e->fc);
    uint32_t uv[4];
    uv[0] = s[0] / 3; uv[1] = s[1] / 3; uv[2] = s[2] / 3; uv[3] = s[3] / 3;
    (void)uv;
    {
        float* c = (float*)(hB.b + hB.d * e->f8);
        color[0] = c[0]; color[1] = c[1]; color[2] = c[2]; color[3] = c[3];
    }
    float* ps = (float*)(pos->base + pos->stride * e->f0);
    p3[0] = ps[0]; p3[1] = ps[1]; p3[2] = ps[2];
    FUN_006c4200(res, scratch, p3, axisDir, color, uv, param10);
    BAKE_TAIL_ACOS()
    BAKE_EPILOG()
}

// @ 0x006d95e0
void* RBTree::FindOrInsert(const int* pKey)
{
    RBNode* endNode = &this->anchor;
    RBNode* lower = endNode;
    RBNode* node = this->anchor.mpParent;    // root
    if (node != 0)
    {
        do
        {
            if (node->mKey < *pKey)
                node = node->mpLeft;
            else
            {
                lower = node;
                node = node->mpRight;
            }
        } while (node != 0);
    }
    if (lower == endNode || *pKey < lower->mKey)
    {
        MapEntry entry = { *pKey, 0 };
        void* result = 0;
        TrueTypeTag tag;
        tag.b = false;
        ((TreeInsert*)this)->DoInsertValue(&result, lower, &entry, tag);
        return (char*)result + 0x14;
    }
    return (char*)lower + 0x14;
}

// @ 0x006d9660
void HandleVec::Insert(uint32_t position, uint32_t value)
{
    uint32_t* self = mWords;
    uint32_t end = self[1];
    if (end != self[2])
    {
        if (position <= value && value < end)
            value += 0x10;
        if (end != 0)
            ((VecElem*)(uint32_t)end)->Destroy((void*)(end - 0x10));
        ((VecElem*)(uint32_t)position)->Shift((void*)(self[1] - 0x10), (void*)self[1]);
        ((VecElem*)(uint32_t)position)->Assign((const void*)value);
        self[1] = self[1] + 0x10;
        return;
    }

    int count = (int)(end - self[0]) >> 4;
    void* newBlock;
    if (count == 0)
    {
        count = 1;
    }
    else
    {
        count *= 2;
    }
    if (count == 0)
        newBlock = 0;
    else
        newBlock = eastl_allocator_allocate(count << 4, "Graphics", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);

    uint32_t begin = self[0];
    void* mid = FUN_006c2b10((void*)begin, (void*)position, newBlock);
    FUN_0047d3f0((void*)begin, (void*)position, newBlock);
    if (mid != 0)
        ((VecElem*)mid)->Destroy((void*)value);

    uint32_t oldEnd = self[1];
    void* newEnd = FUN_006c2b10((void*)position, (void*)oldEnd, (char*)mid + 0x10);
    FUN_0047d3f0((void*)position, (void*)oldEnd, (char*)mid + 0x10);

    uint32_t begin2 = self[0];
    if (begin2 != 0 && begin2 != self[4])
        eastl_allocator_deallocate((void*)begin2);
    self[0] = (uint32_t)newBlock;
    self[1] = (uint32_t)newEnd;
    self[2] = (uint32_t)newBlock + (count << 4);
}

// @ 0x006dbed0
void BakeMeshTexCoords(Mesh_s006d_bed0* pMesh, int param, uint32_t usage)
{
    AutoRefCount<Mesh_s006d_bed0> mesh(pMesh);

    const int iMaterialElement = FindElement(pMesh, 0x15, 0, 6, 8);
    const int iElement14       = FindElement(pMesh, 0x14, 0, 6, 8);
    int       iPosElement      = FindElement(pMesh, 1, 0, 3, 0xe);

    if (iMaterialElement < 0 || iElement14 < 0 || iPosElement < 0 ||
        pMesh->mGeometries.mpBegin == pMesh->mGeometries.mpEnd)
        return;

    Handle_s006d_bed0 hMaterials(pMesh->mElements.mpBegin[iMaterialElement].mHandle);
    Handle_s006d_bed0 hElement14(pMesh->mElements.mpBegin[iElement14].mHandle);
    Handle_s006d_bed0 hPositions(pMesh->mElements.mpBegin[iPosElement].mHandle);

    AutoRefCount<UVBuffer> pBuffer(new("Graphics", 0, 0, 0, 0) UVBuffer());
    UVBuffer* const buffer = pBuffer;

    buffer->mVertices.push_back(Vector2(0.0f, 0.0f));

    // append the new uv element
    const int iNewElement = (int)pMesh->mElements.size();
    pMesh->mElements.push_back(Element(8, usage, 2, 0));

    // give every geometry that uses the position element a zeroed 16-bit uv index stream
    const int nGeometries = (int)pMesh->mGeometries.size();
    for (int g = 0; g < nGeometries; ++g)
    {
        Geometry* const geometry = &pMesh->mGeometries.mpBegin[g];
        const int iRef = FindStream(pMesh, g, 1, -1, 0);

        if (iRef >= 0 && geometry->mStreamRefs.mpBegin[iRef].mElement == iPosElement)
        {
            PrepareGeometry(geometry);

            const int count = (int)geometry->mStreams.mpBegin[geometry->mStreamRefs.mpBegin[iRef].mStream].mCount;
            Handle_s006d_bed0 stream(count, 0, 2, 2, 0);
            AllocateStream(&stream);

            for (int i = 0; i < count; ++i)
                *(uint16_t*)(stream.mpData + stream.mStride * i) = 0;

            const int iStream = (int)geometry->mStreams.size();
            geometry->mStreams.push_back(stream);

            StreamRef ref;
            ref.mElement = (int16_t)iNewElement;
            ref.mStream  = (int16_t)iStream;
            geometry->mStreamRefs.push_back(ref);
        }
    }

    buffer->mVertices.reserve(hPositions.mCount);

    PrimIndexVector  prims;
    BakeVertexVector vertices;

    for (int iMaterial = 0; iMaterial < (int)hMaterials.mCount; ++iMaterial)
    {
        prims.clear();
        vertices.clear();

        SP::FindPrimitives(pMesh, &prims, 0, 0, iMaterial);

        const int iPosRef   = FindStream(pMesh, 0, 1,  -1, 0);
        const int iRefA     = FindStream(pMesh, 0, 2,  -1, 0);
        const int iRefB     = FindStream(pMesh, 0, 10, -1, 0);
        const int iRefC     = FindStream(pMesh, 0, 9,  -1, 0);
        const int iIndexRef = FindStream(pMesh, 0, 8, (int)usage, 0);

        // build the bake records
        const int nPrims = (int)prims.size();
        for (int p = 0; p < nPrims; ++p)
        {
            const Primitive* const prim = &pMesh->mpPrimBegin[prims.mpBegin[p]];
            const Geometry* const geometry = &pMesh->mGeometries.mpBegin[prim->mGeometry];

            if (prim->mGeometry == 0)
            {
                Handle_s006d_bed0 hPos;
                Handle_s006d_bed0 hA;
                Handle_s006d_bed0 hB;
                Handle_s006d_bed0 hC;

                if (iPosRef >= 0)
                    hPos = geometry->mStreams.mpBegin[geometry->mStreamRefs.mpBegin[iPosRef].mStream];
                if (iRefA >= 0)
                    hA = geometry->mStreams.mpBegin[geometry->mStreamRefs.mpBegin[iRefA].mStream];
                if (iRefB >= 0)
                    hB = geometry->mStreams.mpBegin[geometry->mStreamRefs.mpBegin[iRefB].mStream];
                if (iRefC >= 0)
                    hC = geometry->mStreams.mpBegin[geometry->mStreamRefs.mpBegin[iRefC].mStream];

                for (int k = prim->mStart; k < prim->mEnd; ++k)
                {
                    uint32_t v = (uint32_t)k;
                    if (geometry->mIndices.mpData)
                        v = geometry->mIndices.Get(k);

                    uint16_t a = 0xffff;
                    uint16_t b = 0xffff;
                    uint16_t c = 0xffff;
                    if (hA.mpData)
                        a = (uint16_t)hA.Get(v);
                    if (hB.mpData)
                        b = (uint16_t)hB.Get(v);
                    if (hC.mpData)
                        c = (uint16_t)hC.Get(v);

                    BakeVertex bv;
                    bv.mPos    = (int16_t)hPos.Get(v);
                    bv.mAttrA  = (int16_t)a;
                    bv.mAttrB  = (int16_t)b;
                    bv.mAttrC  = (int16_t)c;
                    bv.mVertex = (uint16_t)v;
                    vertices.push_back(bv);
                }
            }
        }

        // shader data of this material
        Material* const material =
            SP::MaterialManager()->GetMaterial(*(uint32_t*)(hMaterials.mpData + iMaterial * hMaterials.mStride));
        rw::graphics::EmbeddedState_s006d_bed0* const state = material->mpState;
        const char* shaderData;
        if (state && (state->m_softStateDirty & 8))
            shaderData = state->D3D9GetShaderData(0x211);
        else
            shaderData = 0;

        bool bBaked = false;

        if (shaderData)
        {
            if (*shaderData != 3)
            {
                for (int n = (int)vertices.size(), i = 0; i < n; ++i)
                    vertices.mpBegin[i].mAttrA = -1;
            }

            SortBakeVertices(vertices.mpBegin, vertices.mpEnd);

            const unsigned base = buffer->mVertices.size();

            Geometry* const geometry0 = pMesh->mGeometries.mpBegin;
            const Handle_s006d_bed0& src = geometry0->mStreams.mpBegin[geometry0->mStreamRefs.mpBegin[iIndexRef].mStream];
            Handle_s006d_bed0 hIndex(src.mCount, src.mpData, src.mSize, src.mStride, src.mpOwner);

            // collapse identical records, writing the new vertex index for every source vertex
            BakeVertex last;
            last.mPos   = -1;
            last.mAttrA = -1;
            last.mAttrB = -1;
            last.mAttrC = -1;

            int         nUnique = 0;
            uint32_t    index   = base - 1;
            BakeVertex* out     = vertices.mpBegin;
            BakeVertex* it      = vertices.mpBegin;

            for (int n = (int)vertices.size(); n > 0; --n, ++it)
            {
                if (it->mPos != last.mPos || it->mAttrA != last.mAttrA ||
                    it->mAttrB != last.mAttrB || it->mAttrC != last.mAttrC)
                {
                    last = *it;
                    *out = last;
                    ++nUnique;
                    ++out;
                    ++index;
                }
                StoreIndex(hIndex, it->mVertex, index);
            }

            vertices.EraseToEnd(vertices.mpBegin + nUnique);
            buffer->mVertices.resize(base + nUnique);

            Vector2* const pOut = buffer->mVertices.mpBegin + base;
            switch (*shaderData)
            {
                case 3: bBaked = BakeType3(pOut, nUnique, pMesh, vertices.mpBegin, &hPositions, shaderData + 4, param); break;
                case 6: bBaked = BakeType6(pOut, nUnique, pMesh, vertices.mpBegin, &hPositions, shaderData + 4, param); break;
                case 7: bBaked = BakeType7(pOut, nUnique, pMesh, vertices.mpBegin, &hPositions, shaderData + 4, param); break;
                case 4: bBaked = BakeType4(pOut, nUnique, pMesh, vertices.mpBegin, &hPositions, shaderData + 4, param); break;
                case 0: bBaked = BakeType0(pOut, nUnique, pMesh, vertices.mpBegin, &hPositions, shaderData + 4, param); break;
                case 1: bBaked = BakeType1(pOut, nUnique, pMesh, vertices.mpBegin, &hPositions, shaderData + 4, param); break;
                case 2: bBaked = BakeType2(pOut, nUnique, pMesh, vertices.mpBegin, &hPositions, shaderData + 4, param); break;
                case 5: bBaked = BakeType5(pOut, nUnique, pMesh, vertices.mpBegin, &hPositions, shaderData + 4, param); break;
            }

            if (!bBaked)
                buffer->mVertices.resize(base);
        }

        if (bBaked)
            continue;

        // fallback: copy the source uvs, de-duplicated through a remap table
        const int nPrims2 = (int)prims.size();
        for (int p = 0; p < nPrims2; ++p)
        {
            const Primitive* const prim = &pMesh->mpPrimBegin[prims.mpBegin[p]];
            Geometry* const geometry = &pMesh->mGeometries.mpBegin[prim->mGeometry];

            const int iSrcRef = FindStream(pMesh, prim->mGeometry, 8, 0, 2);
            const int iDstRef = FindStream(pMesh, prim->mGeometry, 8, 2, 2);

            if (iSrcRef >= 0 && iDstRef >= 0)
            {
                IntMap remap;

                if (geometry->mStreams.mpBegin != geometry->mStreams.mpEnd)
                {
                    const StreamRef* const refs = geometry->mStreamRefs.mpBegin;
                    const Handle_s006d_bed0* const srcIndex = &geometry->mStreams.mpBegin[refs[iSrcRef].mStream];
                    const Handle_s006d_bed0* const dstIndex = &geometry->mStreams.mpBegin[refs[iDstRef].mStream];
                    const Handle_s006d_bed0& srcUV = pMesh->mElements.mpBegin[refs[iSrcRef].mElement].mHandle;
                    Handle_s006d_bed0 hUV(srcUV.mCount, srcUV.mpData, srcUV.mSize, srcUV.mStride, srcUV.mpOwner);

                    for (int k = prim->mStart; k < prim->mEnd; ++k)
                    {
                        uint32_t v = (uint32_t)k;
                        if (geometry->mIndices.mpData)
                            v = geometry->mIndices.Get(k);

                        int key = (int)v;
                        if (srcIndex->mpData)
                            key = (int)srcIndex->Get(v);

                        if (!remap.contains(key))
                        {
                            const int n = (int)buffer->mVertices.size();
                            buffer->mVertices.PushBack(*(const Vector2*)(hUV.mpData + hUV.mStride * key));
                            remap[key] = n;
                        }

                        StoreIndex(*dstIndex, v, (uint32_t)remap[key]);
                    }
                }
            }
        }
    }

    // point the new element at the vertex buffer
    {
        Handle_s006d_bed0 hBuffer = buffer->GetHandle();
        Element element(8, usage, 2, 0, hBuffer);
        pMesh->mElements.mpBegin[iNewElement] = element;
    }

    FinishMesh(pMesh);
}

// @ 0x006ddcc0
bool FUN_006ddcc0(int param_1, int param_2, int param_3, int param_4) // @ 0x006ddcc0
{
    *(uint32_t*)((char*)DAT_01607728 + 0x1a0) = param_1;
    int iVar1 = ((CBufferDraw*)DAT_01607728)->Lock(param_2, (void*)param_3, (uint32_t*)param_4, 0);
    if (param_2 == iVar1)
        return true;
    FUN_006dd8b0(DAT_01607728);
    return false;
}

// @ 0x006ddde0
void FUN_006ddde0(int param_1, int param_2) // @ 0x006ddde0
{
    *(uint32_t*)((char*)DAT_01607728 + 0x1a4) = param_1;
    *(uint32_t*)((char*)DAT_01607728 + 0x1a0) = param_2;
    *(uint32_t*)((char*)DAT_01607728 + 0x1a8) = 0;
    *(uint32_t*)((char*)DAT_01607728 + 0x1ac) = 0;
    GlobalState_D3D9Sync();
    *(uint8_t*)((char*)DAT_01607728 + 0x1b0) = 1;
}

// @ 0x006dde30
void FUN_006dde30(int param_1, int param_2, int param_3) // @ 0x006dde30
{
    *(uint32_t*)((char*)DAT_01607728 + 0x1a4) = param_1;
    *(uint32_t*)((char*)DAT_01607728 + 0x1a0) = param_2;
    *(uint32_t*)((char*)DAT_01607728 + 0x1a8) = param_3;
    *(uint32_t*)((char*)DAT_01607728 + 0x1ac) = 0;
    CompiledState_Dispatch(*(void**)(param_3 + 4));
    GlobalState_D3D9Sync();
    *(uint8_t*)((char*)DAT_01607728 + 0x1b0) = 1;
}

// @ 0x006dde90
void FUN_006dde90(int param_1, int param_2, int param_3, int param_4) // @ 0x006dde90
{
    ((CBufferDraw*)DAT_01607728)->Lock(param_1, (void*)param_2, (uint32_t*)param_3, param_4);
}

// @ 0x006de350
void FUN_006de350(void) // @ 0x006de350
{
    DAT_016079a8 = DAT_016079a8 - 1;
    if (DAT_016079a8 == 0)
    {
        if (DAT_016079a4 != 0)
        {
            FUN_00762a30(DAT_016079a4);
            DAT_016079a4 = 0;
        }
        if (DAT_016079a0 != 0)
        {
            FUN_00f47410(DAT_016079a0);
            DAT_016079a0 = 0;
        }
    }
}

// @ 0x006de4e0
void FUN_006de4e0(int param_1, int param_2, int param_3, int param_4)
{
    if (param_3 <= param_2)
    {
        *(int*)(param_1 + param_3 * 4) = param_4;
        return;
    }
    int iVar2;
    do
    {
        iVar2 = (param_3 + -1) >> 1;
        int iVar1 = *(int*)(param_1 + iVar2 * 4);
        if (*(uint32_t*)(iVar1 + 4) <= *(uint32_t*)(param_4 + 4))
            break;
        *(int*)(param_1 + param_3 * 4) = iVar1;
        param_3 = iVar2;
    } while (param_2 < iVar2);
    *(int*)(param_1 + param_3 * 4) = param_4;
}

// @ 0x006de530
void FUN_006de530(int param_1, int param_2, int param_3, int param_4)
{
    if (param_3 <= param_2)
    {
        *(int*)(param_1 + param_3 * 4) = param_4;
        return;
    }
    int iVar2;
    do
    {
        iVar2 = (param_3 + -1) >> 1;
        int iVar1 = *(int*)(param_1 + iVar2 * 4);
        if (*(uint32_t*)(param_4 + 4) <= *(uint32_t*)(iVar1 + 4))
            break;
        *(int*)(param_1 + param_3 * 4) = iVar1;
        param_3 = iVar2;
    } while (param_2 < iVar2);
    *(int*)(param_1 + param_3 * 4) = param_4;
}

// @ 0x006de580
void FUN_006de580(int param_1, int param_2, int param_3, uint32_t param_4, ...)
{
    uint32_t* args = &param_4;
    while (param_2 < param_3)
    {
        int iVar1 = (param_3 + -1) >> 1;
        int iVar2 = iVar1 * 0x34;
        if (*(uint32_t*)(iVar2 + 8 + param_1) <= args[2])
            break;
        uint32_t* pu4 = (uint32_t*)(iVar2 + param_1);
        uint32_t* pu5 = (uint32_t*)(param_3 * 0x34 + param_1);
        for (int i = 0xd; param_3 = iVar1, i != 0; --i)
            *pu5++ = *pu4++;
    }
    uint32_t* pu4 = args;
    uint32_t* pu5 = (uint32_t*)(param_3 * 0x34 + param_1);
    for (int i = 0xd; i != 0; --i)
        *pu5++ = *pu4++;
}

// @ 0x006deb70
void FUN_006deb70(uint32_t* param_1, int param_2, uint32_t param_3) // @ 0x006deb70
{
    uint32_t* old = (uint32_t*)(param_2 - 0x34);
    Rec13 record;
    uint32_t* rd = (uint32_t*)&record;
    for (int i = 0xd; i != 0; --i)
        *rd++ = *old++;
    old = (uint32_t*)(param_2 - 0x34);
    uint32_t* pu15 = param_1;
    uint32_t* pu16 = old;
    for (int i = 0xd; i != 0; --i)
        *pu16++ = *pu15++;
    FUN_006dea60((int)param_1, 0, ((param_2 - (int)param_1) / 0x34) - 1, 0, record);
    (void)param_3;
}

// @ 0x006df280
RefPtr& RefPtr::AssignRefPtr(const RefPtr* x)
{
    return (*this = *x), *this;
}

// @ 0x006df3b0
void Elem16Vector::Destroy()
{
    for (Elem16* p = mpBegin; p < mpEnd; ++p) {
        if (p->ref.mpObject)
            p->ref.mpObject->Release();
    }
    if (mpBegin && mpBegin != (Elem16*)mpInline)
        FreeMem(mpBegin);
}
