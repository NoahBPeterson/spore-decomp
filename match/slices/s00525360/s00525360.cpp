// Skin-paint (nSPSkinner) helpers: mesh building, EASTL vector/deque instantiations and the
// paint-command registration table (unoptimized module: /Od /Ob1 /MD /Gy /TP /arch:SSE, no /EHsc).
// Inline helpers that cl declined to inline in the original are modelled as out-of-line calls
// preceded by ScratchSlots<N>() (the declined callee's frame, minus its `this`, stays reserved).
#include "types.h"

template <int N> inline void ScratchSlots() { uint32_t slots[N]; }
template <> inline void ScratchSlots<0>() {}
inline void* operator new(unsigned int, void* p) { return p; }
inline void operator delete(void*, void*) {}

extern "C" void EASTL_allocator_deallocate(void* p);                       // 0x00f47380
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags,
                   const char* file, int line);                            // 0x00f473a0

struct sp_vector_allocator {
    uint32_t mFlags[2];
    void* allocate(uint32_t n, uint32_t align, uint32_t ofs);
};
void* EASTL_Allocate(sp_vector_allocator* a, uint32_t n, uint32_t align, uint32_t ofs);  // 0x0042dee0

// ---------------------------------------------------------------- ref counting
struct IRefObj {
    virtual void AddRef();
    virtual void Release();
};
template <typename T> struct intrusive_ptr {
    T* mp;
    intrusive_ptr() : mp(0) {}
    ~intrusive_ptr() { if (mp) mp->Release(); }
};

// Objects recycled through a free list once their count (at +0x4c) drops to zero.
struct PoolNode {
    PoolNode* mpNext;
};
struct PooledObj {
    PoolNode* mpNext;
    uint32_t pad04[0x12];
    int mRefCount;                  // +0x4c
    static PoolNode* sFreeList;     // 0x015de2b0
    static void Free(void* p)
    {
        PoolNode* const node = (PoolNode*)p;
        node->mpNext = sFreeList;
        sFreeList = node;
    }
    void AddRef() { mRefCount++; }
    void Release()
    {
        if (--mRefCount > 0)
            return;
        Free(this);
    }
};
struct PoolPtr {
    PooledObj* mp;
    PoolPtr() : mp(0) {}
    ~PoolPtr();
    PoolPtr& operator=(PooledObj* p);
};

// @ 0x005266a0 ??1PoolPtr
PoolPtr::~PoolPtr()
{
    if (mp)
        mp->Release();
}

// @ 0x00525d90 ??4PoolPtr
PoolPtr& PoolPtr::operator=(PooledObj* p)
{
    if (p != mp) {
        PooledObj* const pTemp = mp;
        if (p)
            p->AddRef();
        mp = p;
        if (pTemp)
            pTemp->Release();
    }
    return *this;
}

// ---------------------------------------------------------------- 0x38-byte vector element
struct Elem38 {
    uint32_t data[11];
    intrusive_ptr<IRefObj> mpObj;   // +0x2c
    uint32_t m30;
    PoolPtr mpPooled;               // +0x34
    Elem38() {}
    ~Elem38();
};

// @ 0x00526660 ??1Elem38
Elem38::~Elem38()
{
    ScratchSlots<2>();
}

template <typename T> struct VectorBase {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator mAllocator;
    ~VectorBase();      // declined inline in the original
};

template <typename T> inline void destruct(T* first, T* last)
{
    for (; first < last; ++first) {
        ScratchSlots<3>();
        first->~T();
    }
}

struct VectorElem38 : VectorBase<Elem38> {
    typedef Elem38 value_type;
    typedef uint32_t size_type;
    ~VectorElem38();
    void resize(size_type n);
    void push_back();
    void DoInsertValues(Elem38* position, size_type n, const value_type& value);  // 0x00527570
    void DoInsertValue(Elem38* position, const value_type& value);              // 0x005267c0
    Elem38* erase(Elem38* first, Elem38* last);                                 // 0x005266f0
    void insert(Elem38* position, size_type n, const value_type& value)
    {
        DoInsertValues(position, n, value);
    }
};

// @ 0x00525e10 ??1VectorElem38
VectorElem38::~VectorElem38()
{
    destruct(mpBegin, mpEnd);
    ScratchSlots<3>();
}

// @ 0x00525e70 ?resize@VectorElem38
void VectorElem38::resize(size_type n)
{
    if (n > (size_type)(mpEnd - mpBegin)) {
        insert(mpEnd, n - (size_type)(mpEnd - mpBegin), value_type());
        ScratchSlots<3>();
    } else {
        ScratchSlots<15>();
        erase(mpBegin + n, mpEnd);
    }
}

// @ 0x00525f40 ?push_back@VectorElem38
void VectorElem38::push_back()
{
    if (mpEnd < mpCapacity)
        ::new (mpEnd++) value_type();
    else {
        DoInsertValue(mpEnd, value_type());
        ScratchSlots<3>();
    }
}

// ---------------------------------------------------------------- 8-byte element vector
struct cSPVector2 {
    float x, y;
    float& operator[](int i) { return (&x)[i]; }
};

struct VectorVec2 : VectorBase<cSPVector2> {
    void push_back(const cSPVector2& value);
    void DoInsertValue(cSPVector2* position, const cSPVector2& value);   // 0x00533960
};

// @ 0x00525ff0 ?push_back@VectorVec2
void VectorVec2::push_back(const cSPVector2& value)
{
    if (mpEnd < mpCapacity)
        ::new (mpEnd++) cSPVector2(value);
    else
        DoInsertValue(mpEnd, value);
}

// ---------------------------------------------------------------- deque of 0x48-byte elements
struct Elem48 {
    uint32_t data[0x12];
};
struct DequeIterator48 {
    Elem48* mpCurrent;
    Elem48* mpBegin;
    Elem48* mpEnd;
    Elem48** mpCurrentArrayPtr;
};
struct DequeElem48 {
    Elem48** mpPtrArray;
    uint32_t mnPtrArraySize;
    DequeIterator48 mItBegin;       // +0x08
    DequeIterator48 mItEnd;         // +0x18
    void pop_front();
    void DoPopFront();              // 0x00527110
    bool empty() const;             // 0x00425430
};

// @ 0x005263f0 ?pop_front@DequeElem48
void DequeElem48::pop_front()
{
    if ((mItBegin.mpCurrent + 1) != mItBegin.mpEnd)
        ++mItBegin.mpCurrent;
    else
        DoPopFront();
}

// ---------------------------------------------------------------- vector<uint32_t>
struct VectorU32 : VectorBase<uint32_t> {
    typedef uint32_t size_type;
    bool empty() const;
    size_type size() const { return (size_type)(mpEnd - mpBegin); }
    uint32_t* erase(uint32_t* first, uint32_t* last);     // 0x004769b0
    void clear() { erase(mpBegin, mpEnd); }
};

// @ 0x00526430 ?empty@VectorU32
bool VectorU32::empty() const
{
    return mpBegin == mpEnd;
}

// ---------------------------------------------------------------- 64-byte element vector
struct Elem40 {
    uint32_t data[0x10];
    Elem40() {}
};

struct VectorElem40 : VectorBase<Elem40> {
    typedef Elem40 value_type;
    typedef uint32_t size_type;
    VectorElem40(const VectorElem40& x);                                         // 0x00527150
    ~VectorElem40();                                                              // 0x0045d750
    void swap(VectorElem40& x);                                                   // 0x005271f0
    void resize(size_type n);
    void set_capacity(size_type n);
    void DoInsertValues(Elem40* position, size_type n, const value_type& value);  // 0x00527f30
    Elem40* erase(Elem40* first, Elem40* last);                                   // 0x00476a40
    void insert(Elem40* position, size_type n, const value_type& value)
    {
        DoInsertValues(position, n, value);
    }
    Elem40* DoAllocate(size_type n)
    {
        return n ? (Elem40*)EASTL_Allocate(&mAllocator, n * sizeof(Elem40), 4, 0) : 0;
    }
    void DoFree(Elem40* p, size_type n)
    {
        if (p && ((uint32_t*)p)[-1]) {
            void* q = p;
            EASTL_allocator_deallocate(q);
        }
    }
};
Elem40* uninitialized_copy_ptr(Elem40* first, Elem40* last, Elem40* result);   // 0x005273a0

// @ 0x00526450 ?resize@VectorElem40
void VectorElem40::resize(size_type n)
{
    if (n > (size_type)(mpEnd - mpBegin))
        insert(mpEnd, n - (size_type)(mpEnd - mpBegin), value_type());
    else {
        ScratchSlots<6>();
        erase(mpBegin + n, mpEnd);
    }
}

// @ 0x005264d0 ?set_capacity@VectorElem40
void VectorElem40::set_capacity(size_type n)
{
    if ((n == (size_type)-1) || (n <= (size_type)(mpEnd - mpBegin))) {
        if (n < (size_type)(mpEnd - mpBegin))
            resize(n);
        ScratchSlots<17>();
        VectorElem40 temp(*this);
        ScratchSlots<35>();
        swap(temp);
    } else {
        Elem40* const pNewData = DoAllocate(n);
        uninitialized_copy_ptr(mpBegin, mpEnd, pNewData);
        DoFree(mpBegin, (size_type)(mpCapacity - mpBegin));
        const int nPrevSize = (int)(mpEnd - mpBegin);
        mpBegin = pNewData;
        mpEnd = pNewData + nPrevSize;
        mpCapacity = mpBegin + n;
    }
}

// ---------------------------------------------------------------- AutoRefCount
struct DefaultRefCounted {
    void* vtbl;
    int mnRefCount;     // +0x4
    int AddRef() { return mnRefCount++ + 1; }
    int Release();      // 0x00453540
};
template <typename T> struct AutoRefCount {
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
    T* detach()
    {
        T* const p = mpObject;
        mpObject = 0;
        return p;
    }
};

template <typename T> struct vector : VectorBase<T> {
    typedef uint32_t size_type;
    size_type size() const { return (size_type)(mpEnd - mpBegin); }
    T* begin() { return mpBegin; }
    T& operator[](size_type i) { return mpBegin[i]; }
};

// ---------------------------------------------------------------- mesh building
namespace nSPSkinner {
struct cMesh : DefaultRefCounted {          // retail size 0x1d0
    uint32_t pad08[0xa];
    vector<cSPVector2> mTextureCoordinates;         // +0x30
    uint32_t pad44[5];
    VectorU32 mVertexIndices_TV;                    // +0x58
    uint32_t pad6c[5];
    VectorU32 mTextureIndices_TV;                   // +0x80
    uint32_t pad94[0x4f];
    cMesh();                        // 0x00507380
    void Prepare();                 // 0x00509450
    void Reset();                   // 0x00508400
    void ClearTextureIndices() { mTextureIndices_TV.clear(); }
};
}  // namespace nSPSkinner
using nSPSkinner::cMesh;

struct cSkinnerResult : DefaultRefCounted {
    void AddMesh(cMesh* mesh);      // 0x0050c6c0
    void Finish();                  // 0x0050c3b0
};
struct cSkinnerFactory : DefaultRefCounted {
    cSkinnerResult* Create();       // 0x00523570
    cSkinnerResult* NewResult()
    {
        ScratchSlots<1>();
        return Create();
    }
};
struct cMeshData : DefaultRefCounted {
};
struct cRigBlock {                  // 0x8c bytes
    uint32_t pad00[2];
    uint16_t mFlags;                // +0x08
    uint16_t pad0a;
    uint32_t pad0c[0x20];
};
struct cRigModel : DefaultRefCounted {
    uint32_t pad08[0x24];
    vector<cRigBlock> mBlocks;      // +0x98
};
struct cSPRect {
    float x0, y0, x1, y1;
};
struct cSkinnerSource {
    uint32_t pad00[2];
    AutoRefCount<cRigModel> mpModel;            // +0x08
    uint32_t pad0c[0xa];
    AutoRefCount<cSkinnerFactory> mpFactory;    // +0x34
    uint32_t pad38[0x16];
    vector<cSPRect> mTexRects;                  // +0x90
    vector<AutoRefCount<cMeshData> > mMeshData; // +0xa4
};

bool LoadSkinnerMesh(cMeshData* data, cMesh* mesh);                // 0x0052a700
void ReportBlockError(cRigBlock* block, const char* msg);          // 0x00563de0

inline float Lerp(float a, float b, float t)
{
    float r = b - a;
    r *= t;
    return a + r;
}

struct cSkinnerBuilder {
    void BuildMeshes(cSkinnerSource* src, cSkinnerResult** ppResult);
};

// Local names are chosen for their /Od slot order (cl 15.00 lays a scope's locals out by name hash):
// i = mesh, f = result, nSize = block count, data = block array, v7 = scan start, n8 = current block,
// n30 = blocks skipped so far, n25 = counter; pRB = current block, bBad = out-of-bounds texcoords,
// bShift = texcoords in [-1,0) that get shifted up by one.
// @ 0x00525360 ?BuildMeshes@cSkinnerBuilder
void cSkinnerBuilder::BuildMeshes(cSkinnerSource* src, cSkinnerResult** ppResult)
{
    AutoRefCount<cMesh> i(new ("Skinner", 0, 0, 0, 0) cMesh());
    AutoRefCount<cSkinnerResult> f(src->mpFactory->NewResult());
    cRigBlock* data = src->mpModel->mBlocks.begin();
    int nSize = (int)src->mpModel->mBlocks.size();
    int v7 = 0;
    int n8;
    int n30;
    int n25;
next:
    n8 = v7;
    while (n8 < nSize && (data[n8].mFlags & 1))
        n8++;
    n30 = 0;
    for (n25 = 0; n25 < n8; n25++)
        if (!(data[n25].mFlags & 1))
            n30++;
    while (n8 < nSize) {
        cRigBlock* pRB = &data[n8];
        if (!src->mMeshData[n8] || !LoadSkinnerMesh(src->mMeshData[n8], i))
            ReportBlockError(pRB, "contains an invalid mesh");
        i->Prepare();
        bool bBad = false;
        bool bShift = false;
        for (int t = 0, n = (int)i->mTextureCoordinates.size(); t < n; t++) {
            cSPVector2& uv = i->mTextureCoordinates[t];
            if (uv[0] < 0.0f || uv[0] > 1.0f || uv[1] < -1.0f || uv[1] > 1.0f)
                bBad = true;
            else if (uv[1] < 0.0f)
                bShift = true;
        }
        if (bShift && !bBad) {
            for (int t = 0, n = (int)i->mTextureCoordinates.size(); t < n; t++) {
                cSPVector2& uv = i->mTextureCoordinates[t];
                uv[1] += 1.0f;
                if (uv[1] < 0.0f || uv[1] > 1.0f)
                    bBad = true;
            }
        }
        if (bBad) {
            ReportBlockError(pRB, "contains out-of-bounds texture coordinates");
            i->mTextureIndices_TV.clear();
        } else {
            cSPRect& rect = src->mTexRects[n8];
            for (int t = 0, n = (int)i->mTextureCoordinates.size(); t < n; t++) {
                cSPVector2& uv = i->mTextureCoordinates[t];
                uv[0] = Lerp(rect.x0, rect.x1, uv[0]);
                uv[1] = Lerp(rect.y0, rect.y1, uv[1]);
            }
        }
        if (i->mVertexIndices_TV.empty())
            ReportBlockError(pRB, "is not in a recognized format -- please make sure the maya material exports tangents");
        else if (i->mTextureIndices_TV.empty())
            ReportBlockError(pRB, "does not have any texture coordinates");
        else if (i->mTextureIndices_TV.size() != i->mVertexIndices_TV.size())
            ReportBlockError(pRB, "does not have a texture coordinate at every vertex");
        else
            f->AddMesh(i);
        i->Reset();
        v7 = n8 + 1;
        goto next;
    }
    f->Finish();
    *ppResult = f.detach();
    ScratchSlots<6>();
}

// ---------------------------------------------------------------- 0x00525a40 / 0x00525aa0
struct cDequeHolder {
    uint32_t pad00[0xa];
    DequeElem48 mPending;           // +0x28
};
struct cPaintLayer {
    uint32_t pad00[2];
    cDequeHolder* mpQueue;          // +0x08
};
template <typename T> struct Ptr {
    T* mp;
    operator T*() const { return mp; }
    T* operator->() const { return mp; }
};
struct cPaintJob {
    uint32_t pad00[3];
    Ptr<cPaintLayer> mpLayer;       // +0x0c
    uint32_t pad10[0xb];
    VectorU32 mStrokes;             // +0x3c
    bool IsBusy();
};

// @ 0x00525a40 ?IsBusy@cPaintJob
bool cPaintJob::IsBusy()
{
    return !mStrokes.empty() || (mpLayer && !mpLayer->mpQueue->mPending.empty());
}

struct cTexture {
    uint32_t mHandle;
    uint8_t mFlags;                 // +0x04
    uint32_t GetHandle();
};
struct cTextureManager {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12();
    virtual void Load(cTexture* tex);           // +0x34
};
struct cRenderer {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21();
    virtual uint32_t GetDefaultTexture();       // +0x58
};
cTextureManager* TextureManager();  // 0x0067dd60
cRenderer* Renderer();              // 0x0067dd40

inline uint32_t cTexture::GetHandle()
{
    if (!(mFlags & 1))
        TextureManager()->Load(this);
    return mHandle;
}

struct cPaintSurface {
    uint8_t mbEnabled;              // used at +0x6a
};
struct cSkinPaintTarget {
    uint32_t pad00[7];
    Ptr<cPaintSurface> mpSurface;   // +0x1c  (bool at +0x6a)
    uint32_t pad20[0x38];
    Ptr<cTexture> mpTexture;        // +0x100
    uint32_t GetTextureHandle();
};

// @ 0x00525aa0 ?GetTextureHandle@cSkinPaintTarget
uint32_t cSkinPaintTarget::GetTextureHandle()
{
    if (mpSurface && ((uint8_t*)(cPaintSurface*)mpSurface)[0x6a] && mpTexture)
        return mpTexture->GetHandle();
    else
        return Renderer()->GetDefaultTexture();
}

// ---------------------------------------------------------------- paint command table
typedef void (*CommandFn)();
void SPSkinPaintCmdA1(); void SPSkinPaintCmdA2(); void SPSkinPaintCmdA3(); void SPSkinPaintCmdA4();
void SPSkinPaintCmdB1(); void SPSkinPaintCmdB2(); void SPSkinPaintCmdB3(); void SPSkinPaintCmdB4();
void SWARM_SPSkinPaintParticleAddCommands(); void SPSkinPaintCmdC2(); void SPSkinPaintCmdC3(); void SPSkinPaintCmdC4();
void SWARM_SPSkinPaintFloodAddCommands(); void SPSkinPaintCmdD2(); void SPSkinPaintCmdD3(); void SPSkinPaintCmdD4();

struct CommandKey {
    uint32_t mInstance, mType, mGroup;
};
extern CommandKey kSkinPaintKeyA, kSkinPaintKeyB, kSkinPaintKeyC, kSkinPaintKeyD;

struct CommandDesc {
    void* mpOwner;
    CommandFn mpAdd;
    CommandFn mpParse;
    CommandFn mpExecute;
    CommandFn mpDestroy;
    int mFlags;
    uint32_t mType;
    uint32_t mGroup;
    CommandDesc(void* owner, CommandFn add, CommandFn parse, CommandFn execute, CommandFn destroy,
                int flags, uint32_t type, uint32_t group)
        : mpOwner(owner), mpAdd(add), mpParse(parse), mpExecute(execute), mpDestroy(destroy),
          mFlags(flags), mType(type), mGroup(group)
    {
    }
};
extern CommandDesc gSkinPaintCmdA, gSkinPaintCmdB, gSkinPaintCmdC, gSkinPaintCmdD;

// @ 0x00525b40 ?RegisterSkinPaintCommands
void RegisterSkinPaintCommands()
{
    gSkinPaintCmdA = CommandDesc(0, SPSkinPaintCmdA1, SPSkinPaintCmdA2, SPSkinPaintCmdA3, SPSkinPaintCmdA4, 0,
                                 kSkinPaintKeyA.mType, kSkinPaintKeyA.mGroup);
    gSkinPaintCmdB = CommandDesc(0, SPSkinPaintCmdB1, SPSkinPaintCmdB2, SPSkinPaintCmdB3, SPSkinPaintCmdB4, 0,
                                 kSkinPaintKeyB.mType, kSkinPaintKeyB.mGroup);
    gSkinPaintCmdC = CommandDesc(0, SWARM_SPSkinPaintParticleAddCommands, SPSkinPaintCmdC2, SPSkinPaintCmdC3,
                                 SPSkinPaintCmdC4, 0, kSkinPaintKeyC.mType, kSkinPaintKeyC.mGroup);
    gSkinPaintCmdD = CommandDesc(0, SWARM_SPSkinPaintFloodAddCommands, SPSkinPaintCmdD2, SPSkinPaintCmdD3,
                                 SPSkinPaintCmdD4, 0, kSkinPaintKeyD.mType, kSkinPaintKeyD.mGroup);
}

// @ 0x00525ce0 ?InitSkinPaintCommands
void InitSkinPaintCommands()
{
    RegisterSkinPaintCommands();
}
