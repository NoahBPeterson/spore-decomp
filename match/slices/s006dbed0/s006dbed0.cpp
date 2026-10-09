// Slice s006dbed0: mesh texture-coordinate bake driver (0x006dbed0, 4,988 bytes).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /GS-
//
// For a reference-counted mesh it
//   1. looks up three vertex elements (0x15, 0x14 and the position element 1),
//   2. creates a new float2 vertex buffer object and appends a new element record
//      (type 8, usage param_3, 2 components) to the mesh's element table,
//   3. adds a zeroed 16-bit index stream to every geometry that uses the position element,
//   4. for every material (element 0x15 entry) collects the primitives of geometry 0,
//      builds de-duplicated vertex records and either hands them to one of eight
//      shader-specific bake functions (selected by the material's shader-data byte) or,
//      when there is no shader data / the bake fails, copies the source uvs through an
//      int->int remap table,
//   5. stores the vertex buffer handle into the new element and finalises the mesh.
#include "types.h"
#include <string.h>
#include <new>

extern "C" long __cdecl _InterlockedExchangeAdd(long volatile* addend, long value);
extern "C" long __cdecl _InterlockedExchange(long volatile* target, long value);
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedExchange)

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);
void operator delete[](void* p);

// 0x0140a644: value mask per element component size (1 -> 0xff, 2 -> 0xffff, 4 -> 0xffffffff)
extern const uint32_t kElementMask[];   // 0x140a644

// ---------------------------------------------------------------------------------------------
// Shared types
// ---------------------------------------------------------------------------------------------
struct IRefObject
{
    virtual void AddRef();     // slot 0
    virtual void Release();    // slot 1
};

// 0x10-byte stream handle: element count, data pointer, component size, stride, owner.
struct Handle
{
    uint32_t    mCount;     // +0
    char*       mpData;     // +4
    uint16_t    mSize;      // +8
    uint16_t    mStride;    // +a
    IRefObject* mpOwner;    // +c

    Handle() : mCount(0), mpData(0), mSize(0), mStride(0), mpOwner(0) {}

    Handle(uint32_t count, char* pData, uint16_t size, uint16_t stride, IRefObject* pOwner)
        : mCount(count), mpData(pData), mSize(size), mStride(stride), mpOwner(pOwner)
    {
        if (mpOwner)
            mpOwner->AddRef();
    }

    Handle(const Handle& x);   // 0x006c2ad0

    ~Handle()
    {
        if (mpOwner)
            mpOwner->Release();
    }

    Handle& operator=(const Handle& x)
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

// 0x20-byte vertex element record (mesh +0x08 table)
struct Element
{
    uint32_t mType;     // +0
    uint32_t mUsage;    // +4
    uint32_t mCount;    // +8
    uint32_t mIndex;    // +c
    Handle   mHandle;   // +10

    Element(uint32_t type, uint32_t usage, uint32_t count, uint32_t index)
        : mType(type), mUsage(usage), mCount(count), mIndex(index), mHandle() {}

    Element(uint32_t type, uint32_t usage, uint32_t count, uint32_t index, const Handle& h)
        : mType(type), mUsage(usage), mCount(count), mIndex(index),
          mHandle(h.mCount, h.mpData, h.mSize, h.mStride, h.mpOwner) {}
};

// geometry stream table entry: element index (lo) / stream index (hi)
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

// 0x18-byte bake record
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

// allocator whose blocks carry a count word in front (0 = not heap allocated)
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

// vector<StreamRef> at geometry +0x14
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

// vector<Handle> at geometry +0x44
struct HandleVector : SimpleVector<Handle>
{
    void push_back(const Handle& value);   // 0x006da2e0
};

// vector<Element> at mesh +0x08
struct ElementVector : SimpleVector<Element>
{
    uint32_t mAllocator[2];
    void push_back(const Element& value);  // 0x0041f7d0
};

// vector<Vector2> inside the vertex buffer object
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

// vector<BakeVertex> (local)
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

// fixed_vector<int, 24> (local, buffer preceded by a zero count word)
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

// eastl::map<int, int> (local remap table)
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

// 0x8c-byte geometry
struct Geometry
{
    Handle          mIndices;   // +00 (index remap stream)
    uint32_t        mField10;   // +10
    StreamRefVector mStreamRefs;// +14
    uint32_t        mPad20[9];  // +20
    HandleVector    mStreams;   // +44
    uint32_t        mPad50[15]; // +50
};

// 0x14-byte primitive
struct Primitive
{
    int mType;      // +0
    int mGeometry;  // +4
    int mStart;     // +8
    int mEnd;       // +c
    int mMaterial;  // +10
};

struct Mesh
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

// 0x24-byte float2 vertex buffer created here (ctor 0x006c3510)
struct UVBuffer : public IRefObject
{
    void*         mpSecondVtbl; // +04
    long          mRefCount;    // +08
    Vector2Vector mVertices;    // +0c
    uint32_t      mAllocator;   // +18
    uint32_t      mField1C;     // +1c
    uint32_t      mField20;     // +20

    UVBuffer();                 // 0x006c3510
    Handle GetHandle();         // 0x006c32f0
};

namespace rw { namespace graphics {
    struct EmbeddedState
    {
        uint32_t mPad[2];
        uint8_t  m_softStateDirty;   // +8
        const char* D3D9GetShaderData(uint32_t id);   // 0x011edcf0
    };
}}

struct Material
{
    uint32_t                        mPad0;
    rw::graphics::EmbeddedState*    mpState;   // +4
};

struct IMaterialManager
{
    virtual void f00(); virtual void f04(); virtual void f08(); virtual void f0c();
    virtual void f10(); virtual void f14(); virtual void f18(); virtual void f1c();
    virtual void f20(); virtual void f24();
    virtual Material* GetMaterial(uint32_t id);   // +0x28
};

namespace SP
{
    IMaterialManager* MaterialManager();                                             // 0x0067dd70
    void FindPrimitives(Mesh* mesh, PrimIndexVector* out, int geometry, int type, int material); // 0x0071ee10
}

int  FindElement(Mesh* mesh, int usage, int index, int type, int count);            // 0x0071ddc0
int  FindStream(Mesh* mesh, int geometry, int usage, int index, int type);          // 0x0071e090
void PrepareGeometry(Geometry* geometry);                                           // 0x007368a0
void AllocateStream(Handle* stream);                                                // 0x00720070
void SortBakeVertices(BakeVertex* first, BakeVertex* last);                         // 0x006c4c20
void FinishMesh(Mesh* mesh);                                                        // 0x00735a90

typedef bool (*BakeFunction)(Vector2* out, int count, Mesh* mesh, BakeVertex* vertices,
                             Handle* positions, const char* params, int param);
bool BakeType0(Vector2*, int, Mesh*, BakeVertex*, Handle*, const char*, int);   // 0x006dacf0
bool BakeType1(Vector2*, int, Mesh*, BakeVertex*, Handle*, const char*, int);   // 0x006db1d0
bool BakeType2(Vector2*, int, Mesh*, BakeVertex*, Handle*, const char*, int);   // 0x006db6b0
bool BakeType3(Vector2*, int, Mesh*, BakeVertex*, Handle*, const char*, int);   // 0x006c3080
bool BakeType4(Vector2*, int, Mesh*, BakeVertex*, Handle*, const char*, int);   // 0x006da9c0
bool BakeType5(Vector2*, int, Mesh*, BakeVertex*, Handle*, const char*, int);   // 0x006dbba0
bool BakeType6(Vector2*, int, Mesh*, BakeVertex*, Handle*, const char*, int);   // 0x006da360
bool BakeType7(Vector2*, int, Mesh*, BakeVertex*, Handle*, const char*, int);   // 0x006da690

static void StoreIndex(const Handle& h, uint32_t row, uint32_t value)
{
    switch (h.mSize)
    {
        case 1: *(uint8_t*)(h.mpData + h.mStride * row)  = (uint8_t)value;  break;
        case 2: *(uint16_t*)(h.mpData + h.mStride * row) = (uint16_t)value; break;
        case 4: *(uint32_t*)(h.mpData + h.mStride * row) = value;           break;
    }
}

// @ 0x006dbed0
void BakeMeshTexCoords(Mesh* pMesh, int param, uint32_t usage)
{
    AutoRefCount<Mesh> mesh(pMesh);

    const int iMaterialElement = FindElement(pMesh, 0x15, 0, 6, 8);
    const int iElement14       = FindElement(pMesh, 0x14, 0, 6, 8);
    int       iPosElement      = FindElement(pMesh, 1, 0, 3, 0xe);

    if (iMaterialElement < 0 || iElement14 < 0 || iPosElement < 0 ||
        pMesh->mGeometries.mpBegin == pMesh->mGeometries.mpEnd)
        return;

    Handle hMaterials(pMesh->mElements.mpBegin[iMaterialElement].mHandle);
    Handle hElement14(pMesh->mElements.mpBegin[iElement14].mHandle);
    Handle hPositions(pMesh->mElements.mpBegin[iPosElement].mHandle);

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
            Handle stream(count, 0, 2, 2, 0);
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
                Handle hPos;
                Handle hA;
                Handle hB;
                Handle hC;

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
        rw::graphics::EmbeddedState* const state = material->mpState;
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
            const Handle& src = geometry0->mStreams.mpBegin[geometry0->mStreamRefs.mpBegin[iIndexRef].mStream];
            Handle hIndex(src.mCount, src.mpData, src.mSize, src.mStride, src.mpOwner);

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
                    const Handle* const srcIndex = &geometry->mStreams.mpBegin[refs[iSrcRef].mStream];
                    const Handle* const dstIndex = &geometry->mStreams.mpBegin[refs[iDstRef].mStream];
                    const Handle& srcUV = pMesh->mElements.mpBegin[refs[iSrcRef].mElement].mHandle;
                    Handle hUV(srcUV.mCount, srcUV.mpData, srcUV.mSize, srcUV.mStride, srcUV.mpOwner);

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
        Handle hBuffer = buffer->GetHandle();
        Element element(8, usage, 2, 0, hBuffer);
        pMesh->mElements.mpBegin[iNewElement] = element;
    }

    FinishMesh(pMesh);
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
