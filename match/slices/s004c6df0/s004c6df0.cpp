// Slice s004c6df0: SP::cSkinObject constructor / destructor (/Od).
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast (no /EHsc).
#include "types.h"
#pragma pack(push, 4)

extern "C" long __cdecl _InterlockedExchange(volatile long*, long);
#pragma intrinsic(_InterlockedExchange)

struct AllocTag { AllocTag() {} };

// 4-byte refcount at +4 of the polymorphic base.
struct Cnt {
    volatile long n;
    Cnt() { _InterlockedExchange(&n, 0); }
};

// cRuntimeCreatureResource (only the pieces this ctor touches).
class IRefCounted {
public:
    virtual int AddRef();
    virtual int Release();
};

struct CBlock {                     // 0x8c cRuntimeCreatureBlock
    char pad0[8];
    uint16_t flags;                 // +0x08
    char padA[0x84 - 0x0a];
    uint32_t group;                 // +0x84
    uint32_t instance;              // +0x88
    char pad8c[0x8c - 0x8c];
};

struct BlockArray {
    CBlock* mpBegin;
    CBlock* mpEnd;
    char pad[0xc];
    int size() { return (int)(mpEnd - mpBegin); }
};

struct Res : IRefCounted {
    char pad04[0x98 - 4];
    BlockArray mBlocks;             // +0x98
};

template <class T> struct AutoRef {
    T* mp;
    AutoRef(T* p = 0) : mp(p)
    {
        if (mp)
            mp->AddRef();
    }
    ~AutoRef()
    {
        if (mp)
            mp->Release();
    }
    T* get() const { return mp; }
    T* operator->() const { return mp; }
    operator T*() const { return mp; }
};

class PropertyList {
public:
    virtual int AddRef();
    virtual int Release();
};

struct PropRef {                    // AutoRefCount<PropertyList>: one pointer
    PropertyList* mp;
    void** AsPPVoidParam();         // 0x0041D870
};

class PropertyManager {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool GetPropertyList(uint32_t instance, uint32_t group, void* out); // 0x2c
};
PropertyManager* GetPropertyManager();  // 0x0067DE30

extern uint32_t gPropGroup;          // 0x015D91BC

// Allocator subobject stored at +0xc of the inline EASTL vectors; its ctor is
// out of line (0x00429360), which is what leaves the one-byte default-arg temp.
struct VecAlloc {
    uint32_t a, b;
    VecAlloc(const AllocTag& tag = AllocTag());   // 0x00429360
};

// First two vectors: the whole ctor is out of line (0x00540470).
struct BlockVec {
    PropRef* mpBegin;
    PropRef* mpEnd;
    PropRef* mpCapacity;
    VecAlloc alloc;
    BlockVec(const AllocTag& tag = AllocTag());   // 0x00540470
    ~BlockVec();                                   // 0x004B5440
    void resize(unsigned n);                       // 0x00421BF0
    PropRef& operator[](int i) { return mpBegin[i]; }
};

struct NodeVec {
    uint8_t* mpBegin;
    uint8_t* mpEnd;
    uint8_t* mpCapacity;
    VecAlloc alloc;
    NodeVec(const AllocTag& tag = AllocTag());    // 0x00540470
    ~NodeVec();                                    // 0x0041E5D0
    void resize(unsigned n);                       // 0x004C0410
    uint8_t& operator[](int i) { return mpBegin[i]; }
};

class cTribePlanner {
public:
    void Destroy();                                // 0x00453540
};

// Plain owning pointer whose dtor calls the pointee's destructor.
struct PlannerPtr {
    cTribePlanner* mp;
    PlannerPtr() : mp(0) {}
    ~PlannerPtr()
    {
        cTribePlanner** self = &mp;
        {
            uint32_t dead[3];      // inline-expansion frame of the retail dtor
        }
        if (*self)
            (*self)->Destroy();
    }
};

// Inline-constructed EASTL vectors (zero header, allocator subobject at +0xc).
// The six plain vectors hold different element types, so each destructor is a
// distinct out-of-line function.
struct Vec40 {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    VecAlloc alloc;
    Vec40() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~Vec40();                                      // 0x004CD530
};
struct Vec54 {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    VecAlloc alloc;
    Vec54() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~Vec54();                                      // 0x004CDDD0
};
struct Vec68 {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    VecAlloc alloc;
    Vec68() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~Vec68();                                      // 0x0041E090
};
struct Vec7c {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    VecAlloc alloc;
    Vec7c() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~Vec7c();                                      // 0x00454970
};
struct VecA4 {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    VecAlloc alloc;
    VecA4() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~VecA4();                                      // 0x0041EB80
};

struct ThreadedObj {
    void Release();                                // 0x00404F90
};
struct ThreadedPtr {
    ThreadedObj* mp;
    ThreadedPtr() : mp(0) {}
    ~ThreadedPtr()
    {
        ThreadedObj** self = &mp;
        {
            uint32_t dead[11];     // inline-expansion frame of the retail dtor
        }
        if (*self)
            (*self)->Release();
    }
};

struct RectF {
    float left, top, right, bottom;
    RectF(float l, float t, float r, float b) : left(l), top(t), right(r), bottom(b) {}
};
struct RectVec {
    RectF* mpBegin;
    RectF* mpEnd;
    RectF* mpCapacity;
    VecAlloc alloc;
    RectVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~RectVec();                                    // 0x004748C0
    void resize(unsigned n, const RectF& value);   // 0x004CD710
};

// Refcounted base at +0: vptr 0x13EF094, refcount at +4.
struct RefBase {
    void* mVtbl;                      // +0x00
    Cnt cnt;                          // +0x04
    RefBase() : mVtbl((void*)0x13EF094u) {}
    ~RefBase() { mVtbl = (void*)0x13EF094u; }
};

// Intermediate base so the derived vtable pointer is installed before the
// members are constructed, exactly like the compiler-generated vptr store.
struct SkinVtblBase : RefBase {
    SkinVtblBase() { mVtbl = (void*)0x13F05A8u; }
};

struct SkinObj : SkinVtblBase {
    AutoRef<Res> mResource;           // +0x08
    BlockVec mBlockProps;             // +0x0c
    NodeVec mNodeBlockMap;            // +0x20
    PlannerPtr mPlannerA;             // +0x34
    PlannerPtr mPlannerB;             // +0x38
    float mFloat;                     // +0x3c
    Vec40 mNodes;                     // +0x40
    Vec54 mBones;                     // +0x54
    Vec68 mBoneTransforms;            // +0x68
    Vec7c mVertexWeights;             // +0x7c
    RectVec mTextureSubRects;         // +0x90
    VecA4 mExtra;                     // +0xa4
    ThreadedPtr mThreaded;            // +0xb8

    SkinObj(Res* pResource);
    ~SkinObj();
};

// @ 0x004c6df0
SkinObj::SkinObj(Res* pResource) : mResource(pResource), mFloat(0.0f)
{
    CBlock* blocks = pResource->mBlocks.mpBegin;
    int nBlocks = pResource->mBlocks.size();
    mBlockProps.resize(nBlocks);
    for (int i = 0; i < nBlocks; i++) {
        PropertyManager* pm = GetPropertyManager();
        void* pv = mBlockProps[i].AsPPVoidParam();
        if (!pm->GetPropertyList(blocks[i].instance, blocks[i].group, pv)) {
            PropertyManager* pm2 = GetPropertyManager();
            PropRef* slot = &mBlockProps[i];
            if (slot->mp) {
                PropertyList* old = slot->mp;
                slot->mp = 0;
                old->Release();
            }
            pm2->GetPropertyList(0x4f5f8ce, gPropGroup, slot);
        }
    }

    int nodeCount = 0;
    for (int j = 0; j < nBlocks; j++)
        nodeCount += 1 + ((blocks[j].flags & 2) != 0);
    mNodeBlockMap.resize(nodeCount);

    int node = 0;
    for (int k = 0; k < nBlocks; k++) {
        if (blocks[k].flags & 2) {
            mNodeBlockMap[node] = (uint8_t)k;
            node++;
        }
        mNodeBlockMap[node] = (uint8_t)k;
        node++;
    }

    float bottom = 1.0f;
    float right = 1.0f;
    float top = 0.0f;
    float left = 0.0f;
    RectF rect(left, top, right, bottom);
    mTextureSubRects.resize(nBlocks, rect);
}

// @ 0x004c72f0
SkinObj::~SkinObj()
{
    *(void**)this = (void*)0x13F05A8u;
}

#pragma pack(pop)
