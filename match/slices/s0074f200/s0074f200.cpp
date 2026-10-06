// Slice s0074f200: SP::cModelWorld helpers (~0x0074f200-0x00750030).
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE2 (same region as the neighbouring s00754310).
//
//  0x0074f200  map<uint,uint>-style find-or-insert (operator[]) on the tree at this+4
//  0x0074f3a0  eastl::quick_sort<cOccluder*, bool(*)(const cOccluder&, const cOccluder&)>
//  0x0074f420  eastl::vector<Elem1C>::DoInsertValue (fixed-buffer allocator, "Graphics" heap)
//  0x0074f5d0  eastl::vector<cMWGroup::cModelInfo>::DoInsertValues
//  0x0074f800  SP::cModelWorld::DrawLayer (draw a sorted list of cDrawModelInfo with shader-state caching)
//  0x0074fd90  constructor (two rb-trees + counters)
//  0x0074fe10  event-id slot allocator (find in event map, else hand out next of 64 ids)
//  0x0074fea0  start of the two feedback jobs (lock, create 2 jobs, link, queue)
//  0x00750030  spstl::slot_vector_base<cOccluderInfo>::create
#include "types.h"

inline void* operator new(unsigned int, void* p) { return p; }
inline void operator delete(void*, void*) {}
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file, int line);
void operator delete[](void* p);

// ===========================================================================
// 0x0074f200: tree lookup / insert with a uint key (EASTL rbtree node: right, left, parent, color, key, value)
// ===========================================================================
struct cFeedbackEvent;
struct RbNodeU {
    RbNodeU* mpNodeRight;     // +0
    RbNodeU* mpNodeLeft;      // +4
    RbNodeU* mpNodeParent;    // +8
    uint32_t mColor;          // +0xc
    uint32_t mKey;            // +0x10
    cFeedbackEvent* mValue;   // +0x14
};

struct cFeedbackEvent {
    void Release();    // ref-counted event
};
struct PairUU {
    uint32_t first;
    cFeedbackEvent* second;
    PairUU(uint32_t k) : first(k), second(0) {}
    ~PairUU()
    {
        if (second)
            second->Release();
    }
};

struct CompactMapUU {
    char pad0[4];
    RbNodeU mAnchor;          // +4 (right/left/parent/color)
    uint32_t mKeyDummy;
    uint32_t mnSize;
    RbNodeU* Insert(RbNodeU** result, RbNodeU* pos, const PairUU* value, bool bForceToLeft);   // 0x0074c170
    cFeedbackEvent*& operator[](const uint32_t& key);                                           // 0x0074f200
};

// @ 0x0074f200
cFeedbackEvent*& CompactMapUU::operator[](const uint32_t& key)
{
    RbNodeU* const pEnd = &mAnchor;
    RbNodeU* pCurrent = mAnchor.mpNodeParent;
    RbNodeU* pRangeEnd = pEnd;
    while (pCurrent) {
        if (!(pCurrent->mKey < key)) {
            pRangeEnd = pCurrent;
            pCurrent = pCurrent->mpNodeLeft;
        } else {
            pCurrent = pCurrent->mpNodeRight;
        }
    }
    RbNodeU* itLowerBound = pRangeEnd;
    if ((itLowerBound == pEnd) || (key < itLowerBound->mKey)) {
        PairUU value(key);
        bool bForceToLeft = false;
        Insert(&itLowerBound, itLowerBound, &value, bForceToLeft);
    }
    return itLowerBound->mValue;
}

// ===========================================================================
// 0x0074f3a0: quick_sort of 24-byte cOccluder records
// ===========================================================================
struct cOccluder {
    uint32_t v[6];
};
typedef bool(__cdecl* OccluderCompare)(const cOccluder&, const cOccluder&);

void quick_sort_impl(cOccluder* first, cOccluder* last, int kDepthLimit, OccluderCompare compare);   // 0x0074d190
void insertion_sort(cOccluder* first, cOccluder* last, OccluderCompare compare);                       // 0x007459c0
void insertion_sort_unguarded(cOccluder* first, cOccluder* last, OccluderCompare compare);             // 0x00745ac0

template <typename Size>
inline Size Log2(Size n)
{
    int i;
    for (i = 0; n; ++i)
        n >>= 1;
    return (Size)(i - 1);
}

// @ 0x0074f3a0
void quick_sort(cOccluder* first, cOccluder* last, OccluderCompare compare)
{
    if (first != last) {
        quick_sort_impl(first, last, 2 * Log2(last - first), compare);
        if ((last - first) > 28) {
            insertion_sort(first, first + 28, compare);
            insertion_sort_unguarded(first + 28, last, compare);
        } else {
            insertion_sort(first, last, compare);
        }
    }
}

// ===========================================================================
// 0x0074f420: vector<Elem1C>::DoInsertValue
// ===========================================================================
struct Elem1C {
    uint32_t v[7];
    Elem1C(const Elem1C& o);                 // 0x00743b60
    Elem1C& operator=(const Elem1C& o);      // 0x00747190
};

Elem1C* ext_copy_range(Elem1C* first, Elem1C* last, Elem1C* dest);        // 0x00743d90 (returns end of dest)
void ext_copy_range_tail(Elem1C* first, Elem1C* last, Elem1C* dest);      // 0x00745f00
Elem1C* ext_copy_backward(Elem1C* first, Elem1C* last, Elem1C* dest);     // 0x00748470

struct VecElem1C {
    Elem1C* mpBegin;
    Elem1C* mpEnd;
    Elem1C* mpCapacity;
    uint32_t mAllocator;
    Elem1C* mpPoolBegin;    // +0x10 (fixed buffer; never freed)
    void DoInsertValue(Elem1C* position, const Elem1C& value);
};

static const char kEastlAllocFile[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";

// @ 0x0074f420
void VecElem1C::DoInsertValue(Elem1C* position, const Elem1C& value)
{
    if (mpEnd != mpCapacity) {
        const Elem1C* pValue = &value;
        if ((pValue >= position) && (pValue < mpEnd))
            ++pValue;
        ::new (mpEnd) Elem1C(*(mpEnd - 1));
        ext_copy_backward(position, mpEnd - 1, mpEnd);
        *position = *pValue;
        ++mpEnd;
    } else {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        const uint32_t nNewSize = nPrevSize ? 2 * nPrevSize : 1;
        Elem1C* const pNewData = nNewSize ? (Elem1C*)operator new(nNewSize * sizeof(Elem1C), "Graphics", 0, 0, kEastlAllocFile, 0xd1) : 0;
        Elem1C* pNewEnd = ext_copy_range(mpBegin, position, pNewData);
        ext_copy_range_tail(mpBegin, position, pNewData);
        ::new (pNewEnd) Elem1C(value);
        ++pNewEnd;
        pNewEnd = ext_copy_range(position, mpEnd, pNewEnd);
        ext_copy_range_tail(position, mpEnd, pNewEnd);
        if (mpBegin && mpBegin != mpPoolBegin)
            operator delete[](mpBegin);
        mpEnd = pNewEnd;
        mpBegin = pNewData;
        mpCapacity = pNewData + nNewSize;
    }
}

// ===========================================================================
// 0x0074f5d0: vector<cModelInfo>::DoInsertValues
// ===========================================================================
struct SPTransform {
    char data[0x38];
    SPTransform& operator=(const SPTransform& o);   // 0x00537dc0
};
struct ModelInfo {
    uint32_t mId;
    SPTransform mTransform;
    ModelInfo(const ModelInfo& o);                  // 0x00747ac0
    ModelInfo& operator=(const ModelInfo& o)
    {
        mId = o.mId;
        mTransform = o.mTransform;
        return *this;
    }
};

ModelInfo* ext_mi_copy(ModelInfo* first, ModelInfo* last, ModelInfo* dest);                                              // 0x00748170
void ext_mi_fill_n(ModelInfo* dest, uint32_t n, const ModelInfo* value, uint32_t nAgain);                                // 0x00747c90
void ext_mi_copy_ex(ModelInfo** pResult, ModelInfo* first, ModelInfo* last, ModelInfo* dest, ModelInfo* firstAgain);     // 0x00747b70
ModelInfo* ext_mi_copy_backward(ModelInfo* first, ModelInfo* last, ModelInfo* dest);                                     // 0x007484f0

struct VecModelInfo {
    ModelInfo* mpBegin;
    ModelInfo* mpEnd;
    ModelInfo* mpCapacity;
    uint32_t mAllocator;
    ModelInfo* mpPoolBegin;
    void DoInsertValues(ModelInfo* position, uint32_t n, const ModelInfo& value);
};

// @ 0x0074f5d0
void VecModelInfo::DoInsertValues(ModelInfo* position, uint32_t n, const ModelInfo& value)
{
    if (n <= (uint32_t)(mpCapacity - mpEnd)) {
        if (n > 0) {
            const ModelInfo temp = value;
            const uint32_t nExtra = (uint32_t)(mpEnd - position);
            if (n < nExtra) {
                ModelInfo* pDummy;
                ext_mi_copy_ex(&pDummy, mpEnd - n, mpEnd, mpEnd, mpEnd - n);
                ModelInfo* const pOldEnd = mpEnd;
                mpEnd += n;
                ext_mi_copy_backward(position, pOldEnd - n, pOldEnd);
                for (ModelInfo* p = position; p != position + n; ++p)
                    *p = temp;
            } else {
                ModelInfo* pDummy;
                ext_mi_fill_n(mpEnd, n - nExtra, &temp, n - nExtra);
                mpEnd += n - nExtra;
                ext_mi_copy_ex(&pDummy, position, mpEnd - (n - nExtra), mpEnd, (ModelInfo*)(n - nExtra));
                mpEnd += nExtra;
                for (ModelInfo* p = position; p != mpEnd - n; ++p)
                    *p = temp;
            }
        }
    } else {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        const uint32_t nGrowSize = nPrevSize ? 2 * nPrevSize : 1;
        uint32_t nNewSize = nPrevSize + n;
        if (nGrowSize > nNewSize)
            nNewSize = nGrowSize;
        ModelInfo* const pNewData = nNewSize ? (ModelInfo*)operator new(nNewSize * sizeof(ModelInfo), "Graphics", 0, 0, kEastlAllocFile, 0xd1) : 0;
        ModelInfo* pNewEnd = ext_mi_copy(mpBegin, position, pNewData);
        ext_mi_fill_n(pNewEnd, n, &value, nNewSize);
        pNewEnd = ext_mi_copy(position, mpEnd, pNewEnd + n);
        if (mpBegin && mpBegin != mpPoolBegin)
            operator delete[](mpBegin);
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

// ===========================================================================
// 0x0074f800: SP::cModelWorld::DrawLayer
// ===========================================================================
struct IShaderRef {
    virtual void* v0();
};
struct ShaderRef {              // intrusive ref (refcount at +4, deleting dtor in slot 0)
    void* vtbl;
    int mnRefCount;
    int DrawBatch(void* arg, uint32_t drawArg);   // 0x0073fd20
};
struct ShaderRefPtr {
    ShaderRef* mp;
    ShaderRefPtr() : mp(0) {}
    ~ShaderRefPtr()
    {
        if (mp && --mp->mnRefCount == 0) {
            mp->mnRefCount = 1;
            ((void(__thiscall*)(ShaderRef*, int))(*(void***)mp)[0])(mp, 1);
        }
    }
};

struct cDrawModelInfo {
    char pad0[0xc];
    uint32_t mFlags;                  // +0xc
    char pad10[0x54 - 0x10];
    float mColor[4];                  // +0x54
    char pad64[0x9c - 0x64];
    ShaderRefPtr mShaders[4];         // +0x9c (indexed by mLayerType)
    char padac[0xb0 - 0xac];
    ShaderRef* mpAltShader;           // +0xb0
    char padb4[0xd8 - 0xb4];
    uint32_t mDrawArg;                // +0xd8
    char padDC[0x128 - 0xdc];
    uint8_t mLayerType;               // +0x128
    char pad129[0x134 - 0x129];
    void** mpExtra;                   // +0x134
};
// The +0x64 byte (shader variant selector) lives inside pad10..; read through this helper.
static inline uint8_t VariantByte(const cDrawModelInfo* i) { return *((const uint8_t*)i + 0x64); }

struct DrawEntry {
    cDrawModelInfo* pInfo;
    float fDistance;
};
struct DrawList {
    DrawEntry* mpBegin;
    DrawEntry* mpEnd;
};

struct Float4 {
    float x, y, z, w;
    Float4() {}
    Float4& operator=(const Float4& o)
    {
        x = o.x;
        y = o.y;
        z = o.z;
        w = o.w;
        return *this;
    }
};

struct AlphaSortCompare {};

struct Camera {
    void GetFrustumPlanes(Float4* out);                                     // 0x007c44e0
};
void SortDrawList(DrawEntry* first, DrawEntry* last, AlphaSortCompare c);   // 0x0074d000 (eastl::quick_sort)
void SortDrawListOpaque(DrawEntry* first, DrawEntry* last, AlphaSortCompare c);   // 0x0074cf80
void PushShaderDataNull();                                                  // 0x00777bf0
void SetShaderConstant(int id, const void* data, bool bChanged);            // 0x00777ae0
void PopShaderData();                                                       // 0x00777c10
void SetBlendMode(uint32_t mode);                                           // 0x011f1340 (rw::graphics::GlobalState::SetBlendMode)
extern uint32_t g_renderStateDirty;                                         // 0x016fa38c
extern uint32_t g_016f9244;
extern uint32_t g_016f921c;

struct cModelWorld {
    char pad0[0x8a4];
    int mnDrawnOpaque;       // +0x8a4
    int mnDrawnAlpha;        // +0x8a8
    int mnDrawnTotal;        // +0x8ac
    void SetViewport(uint8_t* pVariant);       // 0x00745140 (thiscall on the world)
    void DrawLayer(bool bAlpha, DrawList* pList, uint32_t flags, void* pArg, Camera* pCamera);
};

static inline bool Differs(const Float4& a, const Float4& b)
{
    return a.x != b.x || a.y != b.y || a.z != b.z || a.w != b.w;
}
static inline uint32_t SignBit(float f) { return (*(uint32_t*)&f) >> 31; }

// @ 0x0074f800
void cModelWorld::DrawLayer(bool bAlpha, DrawList* pList, uint32_t flags, void* pArg, Camera* pCamera)
{
    uint32_t tempGuard = 0;
    Float4 planes;
    pCamera->GetFrustumPlanes(&planes);

    Float4 color;
    color.x = 0.0f;
    color.y = 0.0f;
    color.z = 0.0f;
    color.w = 0.0f;
    uint32_t lastVariant = 0;
    int8_t lastSignCount = -1;
    Float4 cacheA;           // last value sent as constant 0x20c
    Float4 cacheB;           // last value sent as constant 0x22e
    uint8_t dirtyB = 0;
    uint8_t zeroByte;
    (void)tempGuard;
    (void)zeroByte;

    if (!bAlpha)
        mnDrawnOpaque = 0;
    else
        mnDrawnAlpha = 0;

    if (flags & 0x800) {
        SetBlendMode(bAlpha ? 0x60005 : 0x10002);
        g_renderStateDirty |= 0x40100;
        g_016f9244 = 8;
        g_016f921c = 0;
    }

    if (!(flags & 0x8000)) {
        AlphaSortCompare cmp;
        if (!bAlpha)
            SortDrawList(pList->mpBegin, pList->mpEnd, cmp);
        else
            SortDrawListOpaque(pList->mpBegin, pList->mpEnd, cmp);
    }

    const int nCount = (int)(pList->mpEnd - pList->mpBegin);
    for (int i = 0; i < nCount; ++i) {
        cDrawModelInfo* pInfo = pList->mpBegin[i].pInfo;
        const float fDistance = pList->mpBegin[i].fDistance;

        ShaderRef* pShader;
        {
            ShaderRefPtr nullRef;
            const ShaderRefPtr& src = (pInfo->mLayerType < 4) ? pInfo->mShaders[pInfo->mLayerType] : nullRef;
            pShader = src.mp;
        }
        if (pInfo->mLayerType == 0 && ((pInfo->mFlags >> 13) & 1) && pInfo->mpAltShader)
            pShader = pInfo->mpAltShader;

        PushShaderDataNull();

        if ((pInfo->mFlags >> 3) & 1) {
            const uint8_t variant = VariantByte(pInfo);
            const bool bChanged = lastVariant != variant;
            lastVariant = variant;
            SetViewport((uint8_t*)&lastVariant);
            SetShaderConstant(0x202, &lastVariant, bChanged);
        }

        const uint32_t f = pInfo->mFlags;
        color.x = pInfo->mColor[0];
        color.y = pInfo->mColor[1];
        color.z = pInfo->mColor[2];
        color.w = pInfo->mColor[3];

        if ((f >> 2) & 1) {
            if ((f >> 11) & 1)
                color.w = 0.5f;
            else if ((f >> 10) & 1)
                color.w = 0.0f;
            else
                color.w = 1.0f;
            dirtyB = Differs(cacheB, color) ? 1 : 0;
            cacheB = color;
            SetShaderConstant(0x218, &zeroByte, false);
            SetShaderConstant(0x22e, &cacheB, dirtyB != 0);
            if (bAlpha) {
                Float4 one;
                one.x = 1.0f;
                one.y = 1.0f;
                one.z = 1.0f;
                one.w = pInfo->mColor[3];
                const bool bChanged = Differs(cacheA, one);
                cacheA = one;
                color = cacheA;
                SetShaderConstant(0x20c, &cacheA, bChanged);
            }
        } else if ((f >> 1) & 1) {
            const bool bChanged = Differs(cacheA, color);
            cacheA = color;
            color = cacheA;
            SetShaderConstant(0x20c, &cacheA, bChanged);
        }

        Float4 d;
        d.x = planes.x - fDistance;
        d.y = planes.y - fDistance;
        d.z = planes.z - fDistance;
        d.w = planes.w - fDistance;
        const int8_t nSigns = (int8_t)(SignBit(d.x) + SignBit(d.y) + SignBit(d.z) + SignBit(d.w));
        const bool bSignChanged = lastSignCount != nSigns;
        lastSignCount = nSigns;
        SetShaderConstant(0x237, &lastSignCount, bSignChanged);

        if (pInfo->mpExtra)
            SetShaderConstant(0x219, *pInfo->mpExtra, false);

        const int nDrawn = pShader->DrawBatch(pArg, pInfo->mDrawArg);
        PopShaderData();
        mnDrawnTotal += nDrawn;
        if (!bAlpha)
            ++mnDrawnOpaque;
        else
            ++mnDrawnAlpha;
    }
}

// ===========================================================================
// 0x0074fd90 / 0x0074fe10 / 0x0074fea0: feedback-event manager object
// ===========================================================================
struct RbAnchorBase {
    RbAnchorBase* mpNodeRight;
    RbAnchorBase* mpNodeLeft;
    RbAnchorBase* mpNodeParent;
    uint32_t mColor;
    RbAnchorBase() : mpNodeLeft(0), mpNodeParent(0), mColor(0) {}
};
struct RbTreeHeader {
    RbAnchorBase mAnchor;
    uint32_t mnSize;
    RbTreeHeader()
    {
        mAnchor.mpNodeRight = &mAnchor;
        mAnchor.mpNodeLeft = &mAnchor;
        mAnchor.mpNodeParent = 0;
        *(uint8_t*)&mAnchor.mColor = 0;
        mnSize = 0;
    }
};

struct FeedbackBaseA {
    virtual void a0();
};
struct FeedbackBaseB {
    uint32_t mRefCount;
    virtual void b0();
    FeedbackBaseB() : mRefCount(0) {}
};

struct cFeedbackMgr : FeedbackBaseA, FeedbackBaseB {
    uint32_t mpad0c;
    RbTreeHeader mTreeA;          // +0x10 .. +0x20
    uint32_t mpad24, mpad28;
    RbTreeHeader mTreeB;          // +0x2c .. +0x3c
    uint32_t mpad40;
    uint32_t mn44, mn48, mn4c, mn50, mn54;
    cFeedbackMgr();
    int AllocSlot(uint32_t key, uint32_t unused);   // 0x0074fe10
    bool StartJobs(void** pSource);                 // 0x0074fea0
    virtual void a0();
    virtual void b0();
};

// @ 0x0074fd90
cFeedbackMgr::cFeedbackMgr()
{
    mn44 = 0;
    mn48 = 0;
    mn4c = 0;
    mn50 = 0;
    mn54 = 0;
}

// -- 0x0074fe10
struct SlotTree {
    uint32_t mpad;
    void find(RbNodeU** pResult, const uint32_t* key);              // 0x00e5c780 (rbtree<uint, pair<const uint, AutoRef<cFeedbackEvent>>>::find)
};
struct SlotIndexTree {
    uint32_t mpad;
    uint32_t& operator[](const uint32_t& key);                       // 0x00643a40 (map<uint,uint>::operator[])
};

struct SlotAllocator {
    char pad0[0x28];
    SlotTree mTree;                                                 // +0x28 (shared tree object; anchor at +0x2c)
    char mAnchor[0x18];                                             // +0x2c (tree anchor / end node)
    int mnNextSlot;                                                 // +0x44
    int Allocate(uint32_t key, uint32_t unused);
};

// @ 0x0074fe10
int SlotAllocator::Allocate(uint32_t key, uint32_t unused)
{
    RbNodeU* pFound;
    mTree.find(&pFound, &key);
    if (pFound != (RbNodeU*)mAnchor)
        return (int)(uint32_t)pFound->mValue;
    const int nSlot = mnNextSlot;
    if (nSlot < 0x40) {
        (*(SlotIndexTree*)&mTree)[key] = nSlot;
        ++mnNextSlot;
        return nSlot;
    }
    return -1;
}

// -- 0x0074fea0
struct IJobManager {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual bool CreateJob(struct cJobRef* pRef);      // slot 4 (0x10)
    virtual void v5(); virtual void v6(); virtual void v7();
    virtual void Lock();                               // slot 8 (0x20)
    virtual void Unlock();                             // slot 9 (0x24)
};
IJobManager* GetJobManager();                          // 0x0068f4d0

struct cJob {
    char pad0[0x18];
    uint32_t mFlags;                                   // +0x18
    void SetDependency(cJob* pOther);                  // 0x00691380 (this = dependent)
    void Start();                                      // 0x006909b0
    void Release();                                    // 0x00690120
};
struct cJobRef {
    cJob* mp;
};
struct JobLock {
    IJobManager* m;
    JobLock(IJobManager* mgr) : m(mgr) { m->Lock(); }
    ~JobLock() { m->Unlock(); }
};

struct cFeedbackJobs {
    char pad0[0x1c];
    uint8_t mbStarted;                                 // +0x1c
    char pad1d[3];
    cJobRef mJobA;                                     // +0x20
    cJobRef mJobB;                                     // +0x24
    char pad28[4];
    uint32_t mnState;                                  // +0x2c
    cJobRef mJobC;                                     // +0x30
    char pad34[0x4c - 0x34];
    uint32_t mbActive;                                 // +0x4c
    void Assign(void** pSource);                       // 0x00747190
    void ResetTree(uint32_t first);                    // 0x00478db0 (thiscall on this+0x28)
    bool Start(void** pSource);
};
void JobCallback(void*);                               // 0x0074d080

// @ 0x0074fea0
bool cFeedbackJobs::Start(void** pSource)
{
    if (*pSource == 0)
        return false;
    ResetTree((uint32_t)*pSource);
    Assign(pSource);
    mbActive = 1;
    mnState = 6;
    if (mJobC.mp) {
        cJob* pOld = mJobC.mp;
        mJobC.mp = 0;
        pOld->Release();
    }
    JobLock lock(GetJobManager());
    {
        if (mJobA.mp) {
            cJob* pOld = mJobA.mp;
            mJobA.mp = 0;
            pOld->Release();
        }
        if (!GetJobManager()->CreateJob(&mJobA))
            return false;
    }
    {
        if (mJobB.mp) {
            cJob* pOld = mJobB.mp;
            mJobB.mp = 0;
            pOld->Release();
        }
        if (!GetJobManager()->CreateJob(&mJobB))
            return false;
    }
    mJobA.mp->mFlags = 0x80000000;
    *(void**)mJobA.mp = (void*)JobCallback;
    ((void**)mJobA.mp)[1] = this;
    mJobB.mp->SetDependency(mJobA.mp);
    mJobB.mp->Start();
    mbStarted = 1;
    mJobA.mp->Start();
    return true;
}

// ===========================================================================
// 0x00750030: slot_vector_base<cOccluderInfo>::create
// ===========================================================================
struct cOccluderInfo {
    float v[4];
    cOccluderInfo() {}
    cOccluderInfo(const cOccluderInfo& o)
    {
        v[0] = o.v[0];
        v[1] = o.v[1];
        v[2] = o.v[2];
        v[3] = o.v[3];
    }
};

struct SlotEntry {
    uint32_t mFlags;            // bit31 free, bit30 last, low 30 bits next-free link
    cOccluderInfo mItem;
};

struct SlotVectorOccluder {
    SlotEntry* mpBegin;
    SlotEntry* mpEnd;
    SlotEntry* mpCapacity;
    uint32_t mAllocator;
    uint32_t mUnused10;
    uint32_t mMinFree;          // +0x14
    uint32_t mFreeHead;         // +0x18
    void DoInsertEntry(SlotEntry* position, const SlotEntry& value);   // 0x0074ce20
    uint32_t create(const cOccluderInfo& item);
};

// @ 0x00750030
uint32_t SlotVectorOccluder::create(const cOccluderInfo& item)
{
    uint32_t nIndex = mFreeHead;
    if (nIndex != 0x3fffffff) {
        mFreeHead = mpBegin[nIndex].mFlags & 0x3fffffff;
        mpBegin[nIndex].mFlags &= 0x7fffffff;
        cOccluderInfo* pItem = &mpBegin[nIndex].mItem;
        if (pItem)
            ::new (pItem) cOccluderInfo(item);
    } else {
        const cOccluderInfo temp(item);
        nIndex = (uint32_t)(mpEnd - mpBegin);
        if (mpEnd < mpCapacity) {
            SlotEntry* pEnd = mpEnd;
            mpEnd = pEnd + 1;
            if (pEnd)
                pEnd->mFlags = 0x80000000;
        } else {
            SlotEntry entry;
            entry.mFlags = 0x80000000;
            DoInsertEntry(mpEnd, entry);
        }
        if (nIndex != 0)
            mpBegin[nIndex - 1].mFlags &= 0xbfffffff;
        {
            SlotEntry* e = mpBegin + nIndex;
            e->mFlags |= 0x40000000;
        }
        {
            SlotEntry* e = mpBegin + nIndex;
            e->mFlags &= 0x7fffffff;
        }
        cOccluderInfo* pItem = &mpBegin[nIndex].mItem;
        if (pItem)
            ::new (pItem) cOccluderInfo(temp);
    }
    if (mMinFree > nIndex)
        mMinFree = nIndex;
    return nIndex;
}
