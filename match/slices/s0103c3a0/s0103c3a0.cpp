// Slice 34: named float-vector serializer wrapper (0x0103c3a0).
// Builds a wide name string (or "list" when there is none), opens it on the archive
// (vtable slot 0), serializes each float through FUN_00acabe0, closes it (slot 1).
#include "types.h"

// eastl::basic_string<wchar_t> layout as used here: {begin, end, capacity}, no allocator bytes.
struct WStrObj {
    wchar_t* b;
    wchar_t* e;
    wchar_t* c;
    WStrObj() {}
    WStrObj(const WStrObj& o);             // 0x0056e2d0 (thiscall, ret 4)
    void RangeInitialize(const wchar_t* p); // 0x00579a90 (thiscall, ret 4)
};

struct E4 { char d[4]; };
struct FloatVec { E4* b; E4* e; };

extern "C" {
void __cdecl FUN_00f47380(void* p);                                     // 0x00f47380 operator delete
WStrObj* __cdecl FUN_0093c5a0(WStrObj* out, const char* s, int n);      // 0x0093c5a0 EA::ConvertToString16
bool __cdecl FUN_00acabe0(void* ar, int z, E4* e, const wchar_t* tn);   // 0x00acabe0 element serializer
}

typedef void (__thiscall *ArStrFn)(void* self, const wchar_t* s);

static inline void ArCall(void* ar, int slot, const wchar_t* s)
{
    void** vt = *(void***)ar;
    ((ArStrFn)vt[slot])(ar, s);
}

// Heap-owned buffer check used by the inline string teardown: (cap - begin) & ~1 > 2 and begin != 0.
static inline void StrFree(const WStrObj& s)
{
    int n = (int)((char*)s.c - (char*)s.b) & ~1;
    if (n > 2 && s.b) FUN_00f47380(s.b);
}

// @ 0x0103c3a0
bool FUN_0103c3a0(void* ar, const char* name, FloatVec* v)
{
    bool ok = true;
    if (v->b != v->e) {
        WStrObj tmp;
        WStrObj w;
        WStrObj* piVar5;
        if (name == 0) {
            tmp.b = 0;
            tmp.e = 0;
            tmp.c = 0;
            tmp.RangeInitialize(0);
            piVar5 = &tmp;
        } else {
            piVar5 = FUN_0093c5a0(&w, name, -1);
        }
        WStrObj D(*piVar5);
        if (name == 0)
            StrFree(tmp);
        else
            StrFree(w);

        wchar_t* pwVar2 = D.b;
        ArCall(ar, 0, pwVar2 == D.e ? L"list" : pwVar2);

        E4* end = v->e;
        for (E4* p = v->b; p != end; p = p + 1)
            ok = ok && FUN_00acabe0(ar, 0, p, L"float");

        ArCall(ar, 1, pwVar2 == D.e ? L"list" : pwVar2);
        StrFree(D);
    }
    return ok;
}

// =====================================================================================
// gold7 s0103c3a0: SP::cSPSpaceTrading food/spice commodity setup
// (BuildSpiceCommodities / RefreshNPCSpiceCosts / ChooseNPCSpices / ConsiderBuyingRare)
// plus the EASTL container helpers those calls expand into
// (rbtree hint-insert, intro-sort, vector erase/insert/range copy).
//
// Object layouts follow the retail SP::cSPSpaceTrading / Simulator::cNPCStore pair used
// by the sibling slice at 0x0103e8e0 (CreateNPCInventory):
//   cSPSpaceTrading: mFoodCommodities +0x20, mCommodities +0x34, mNPCStore +0x48,
//                    mLastNPCStoreIndex +0x9c, rare-request list +0xe4
//   cNPCStore:       0xc0 bytes, IRefCount sub-object at +8, planet key +0x0c,
//                    timer +0x10, inventory +0x34, ages +0x48, reset flag +0x5c,
//                    mSpiceID (+0x60) and mSpiceCost (+0x9c) inline-buffered vectors.
// =====================================================================================

struct ResourceKey {
    uint32_t instance;      // +0x00
    uint32_t type;          // +0x04
    uint32_t group;         // +0x08
};

// eastl::less<ResourceKey> in the retail build compares instance, then group, then type.
inline bool operator<(const ResourceKey& a, const ResourceKey& b)
{
    if (a.instance != b.instance)
        return a.instance < b.instance;
    if (a.group != b.group)
        return a.group < b.group;
    return a.type < b.type;
}
inline bool operator==(const ResourceKey& a, const ResourceKey& b)
{
    return a.instance == b.instance && a.type == b.type && a.group == b.group;
}
inline bool operator!=(const ResourceKey& a, const ResourceKey& b) { return !(a == b); }

extern const ResourceKey kNoKey;      // 0x016df56c: the empty EA::ResourceMan::Key

// ---- App::Property / App::PropertyList / App::PropertyManager ----------------------

struct Property {
    union Value {
        void* mpData;       // +0x00 pointer form (used when mFlags has 0x30)
        float mFloat;       // +0x00 inline float form
        uint32_t mUInt;     // +0x00 inline integer form
    } mValue;
    uint32_t mPad04[(0x10 - 4) / 4];    // +0x04
    uint8_t mFlags;                     // +0x10 (0x30 = value is heap/offset pointer)
    uint8_t mPad11;                     // +0x11
    uint16_t mType;                     // +0x12 (0x0a = uint, 0x0d = float)

    float* GetFloatPtr();               // 0x0041ea70
    uint32_t* GetUIntPtr();             // 0x0041ea00
};

struct PropertyList {
    virtual int AddRef();                                   // +0x00
    virtual void Release();                                 // +0x04
    virtual void _v2();                                     // +0x08
    virtual void _v3();                                     // +0x0c
    virtual void _v4();                                     // +0x10
    virtual void _v5();                                     // +0x14
    virtual void _v6();                                     // +0x18
    virtual void _v7();                                     // +0x1c
    virtual void _v8();                                     // +0x20
    virtual bool GetProperty(uint32_t id, Property** ppProp);   // +0x24
};

struct PropertyManager {
    virtual void _v0(); virtual void _v1(); virtual void _v2(); virtual void _v3();
    virtual void _v4(); virtual void _v5(); virtual void _v6(); virtual void _v7();
    virtual void _v8(); virtual void _v9(); virtual void _v10();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyList** ppList);   // +0x2c
};

PropertyManager* PropertyManager_Get();                                   // 0x0067de30
bool GetPropertyAsKey(PropertyList* pList, uint32_t id, ResourceKey* pKey);   // 0x006a1250
void GetPropertyT_int(PropertyList* pList, uint32_t id, int* pOut);          // 0x0040cf10

// ---- reference counted pointers ----------------------------------------------------

// The COM-style reference count of a game object; it is a sub-object at object+0x08.
struct IRefCount {
    virtual int AddRef();                // +0x00
    virtual void Release();              // +0x04
};

inline int RefAddRef(PropertyList* p) { return p->AddRef(); }
inline void RefRelease(PropertyList* p) { p->Release(); }
template <class T> inline int RefAddRef(T* p) { return p->mRefCount.AddRef(); }
template <class T> inline void RefRelease(T* p) { p->mRefCount.Release(); }

// Simulator::cSpaceInventoryItem (ref count lives in the IRefCount sub-object at +8).
class cSpaceInventoryItem {
public:
    uint32_t mPad00[2];                  // +0x00
    IRefCount mRefCount;                 // +0x08
    uint32_t mItemCount;                 // +0x10
    uint32_t mItemType;                  // +0x14
    uint32_t mItemCost;                  // +0x18
    uint32_t mPad1c[5];                  // +0x1c
    PropertyList* mpPropList;            // +0x30
};

template <class T> class AutoRefCount {
public:
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(T* p) : mpObject(p) { if (mpObject) RefAddRef(mpObject); }
    AutoRefCount(const AutoRefCount& o) : mpObject(o.mpObject) { if (mpObject) RefAddRef(mpObject); }
    ~AutoRefCount() { if (mpObject) RefRelease(mpObject); }
    T** AsOutParam()
    {
        if (mpObject) { T* pOld = mpObject; mpObject = 0; RefRelease(pOld); }
        return &mpObject;
    }
    AutoRefCount& operator=(const AutoRefCount& o) { return operator=(o.mpObject); }
    AutoRefCount& operator=(T* p)
    {
        T* const pOld = mpObject;
        if (p != pOld) {
            if (p)
                RefAddRef(p);
            mpObject = p;
            if (pOld)
                RefRelease(pOld);
        }
        return *this;
    }
    T* get() const { return mpObject; }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};

typedef AutoRefCount<cSpaceInventoryItem> ItemPtr;

// ---- eastl::vector<T, sp_vector_allocator> (3 pointers + 8-byte allocator) ---------

extern void* memcpy(void*, const void*, unsigned int);
inline void* operator new(size_t, void* p) { return p; }

template <class T> struct Vec {
    T* mpBegin;              // +0x00
    T* mpEnd;                // +0x04
    T* mpCapacity;           // +0x08
    const char* mpName;      // +0x0c (eastl allocator name)
    void* mpPoolBegin;       // +0x10 (inline buffer address of the fixed variants)
    Vec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    int size() const { return (int)(mpEnd - mpBegin); }
    bool empty() const { return mpBegin == mpEnd; }
    T& operator[](int i) { return mpBegin[i]; }
    ~Vec();
    void push_back(const T& value)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
    void DoInsertValue(T* position, const T& value);
};

// Intrusive-pointer range assignment helpers used by the vector element moves.
template <class T> T* MoveItemRange(T* first, T* last, T* out);           // 0x00ad73a0
template <class T> T* MoveItemRangeBackward(T* first, T* last, T* out);   // 0x00ad7400

// eastl::vector<AutoRefCount<cSpaceInventoryItem> > (inventory of a planet/NPC store).
class ItemVec : public Vec<ItemPtr> {
public:
    void erase(ItemPtr* first, ItemPtr* last);
    ~ItemVec();                          // 0x005c7f10
};

// ---- Simulator::cNPCStore ----------------------------------------------------------

class cGonzagoTimer {
public:
    cGonzagoTimer();                     // 0x00b63890
    ~cGonzagoTimer();                    // 0x00b638b0
    uint32_t mData[8];                   // +0x00 (0x20 bytes)
};

// Easter egg ages of a store's stock: eastl::vector with an out-of-line destructor.
struct InventoryAges {
    void* mpBegin;                       // +0x00
    void* mpEnd;                         // +0x04
    void* mpCapacity;                    // +0x08
    const char* mpName;                  // +0x0c
    void* mpPoolBegin;                   // +0x10
    ~InventoryAges();                    // 0x00bf1b60
};

// eastl::fixed_vector<ResourceKey, 3>: header + inline 3-key buffer.
struct KeyVec3 {
    ResourceKey* mpBegin;                // +0x00
    ResourceKey* mpEnd;                  // +0x04
    ResourceKey* mpCapacity;             // +0x08
    uint32_t mAllocator;                 // +0x0c
    ResourceKey* mpPoolBegin;            // +0x10 (mBuffer, never freed)
    uint32_t mAllocatorEx;               // +0x14
    ResourceKey mBuffer[3];              // +0x18
    void Init() { mpPoolBegin = mBuffer; mpEnd = mBuffer; mpBegin = mBuffer; mpCapacity = mBuffer + 3; }
    void push_back(const ResourceKey& value)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) ResourceKey(value);
        else
            DoInsertValue(mpEnd, value);
    }
    void DoInsertValue(ResourceKey* position, const ResourceKey& value);      // 0x004e3e10
    void erase(ResourceKey* first, ResourceKey* last);                        // 0x009e0480
    void Clear() { erase(mpBegin, mpEnd); }
};

// eastl::fixed_vector<float, 3>.
struct FloatVec3 {
    float* mpBegin;                      // +0x00
    float* mpEnd;                        // +0x04
    float* mpCapacity;                   // +0x08
    uint32_t mAllocator;                 // +0x0c
    float* mpPoolBegin;                  // +0x10 (mBuffer, never freed)
    uint32_t mAllocatorEx;               // +0x14
    float mBuffer[3];                    // +0x18
    void Init() { mpPoolBegin = mBuffer; mpEnd = mBuffer; mpBegin = mBuffer; mpCapacity = mBuffer + 3; }
    void push_back(float value)
    {
        if (mpEnd < mpCapacity)
            *mpEnd++ = value;
        else
            DoInsertValue(mpEnd, value);
    }
    void DoInsertValue(float* position, const float& value);                  // 0x00cc4160
    void Clear()
    {
        // The retail build empties the vector by copying the (empty) tail range back over the head.
        float* pEnd = mpEnd;
        float* pBegin = mpBegin;
        memcpy(pBegin, pEnd, (unsigned int)((char*)pEnd - (char*)pEnd));
        mpEnd += pBegin - pEnd;
    }
};

// Common reference-counted base: vtable at +0x00, count at +0x04.
struct cNPCStoreBase {
    virtual int AddRef();                // +0x00
    virtual void Release();              // +0x04
    ~cNPCStoreBase();
    uint32_t mnRefCount;                 // +0x04
};

// Simulator::cNPCStore: one planet's shop. Reference count sub-object at +0x08.
class cNPCStore : public cNPCStoreBase, public IRefCount {
public:
    uint32_t mPlanetKey;                 // +0x0c
    cGonzagoTimer mTimer;                // +0x10
    uint32_t mPad30;                     // +0x30
    ItemVec mNPCInventory;               // +0x34
    InventoryAges mInventoryAges;        // +0x48
    uint8_t mbNeedsReset;                // +0x5c
    uint8_t mPad5d[3];                   // +0x5d
    KeyVec3 mSpiceID;                    // +0x60
    FloatVec3 mSpiceCost;                // +0x9c
public:
    cNPCStore();
    ~cNPCStore();
};

// cNPCStore keeps its reference count in the IRefCount sub-object at +0x08.
inline int RefAddRef(cNPCStore* p) { return static_cast<IRefCount*>(p)->AddRef(); }
inline void RefRelease(cNPCStore* p) { static_cast<IRefCount*>(p)->Release(); }

typedef AutoRefCount<cNPCStore> NPCStorePtr;

// eastl::fixed_vector<NPCStorePtr, 5> used for cSPSpaceTrading::mNPCStore.
class StoreVec {
public:
    NPCStorePtr* mpBegin;                // +0x00
    NPCStorePtr* mpEnd;                  // +0x04
    NPCStorePtr* mpCapacity;             // +0x08
    const char* mpName;                  // +0x0c
    NPCStorePtr* mpPoolBegin;            // +0x10 (inline buffer, never freed)
    StoreVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    int size() const { return (int)(mpEnd - mpBegin); }
    NPCStorePtr& operator[](int i) { return mpBegin[i]; }
    void DoInsertValue(NPCStorePtr* position, const NPCStorePtr& value);
    void push_back(const NPCStorePtr& value)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) NPCStorePtr(value);
        else
            DoInsertValue(mpEnd, value);
    }
};

// ---- random / game access ----------------------------------------------------------

namespace EA { namespace Random {
struct RandomLinearCongruential {
    double RandomDouble();                       // 0x009360d0
    uint32_t RandomUint32Uniform(uint32_t n);    // 0x00a68fb0
};
} }
extern EA::Random::RandomLinearCongruential gRandom;    // 0x01601760
void RandomShuffle(ResourceKey* first, ResourceKey* last, void* pRandom);   // 0x0103b3e0

class cTerrainSphere {
public:
    double Measure();                    // 0x00c75c30
};
class cNounManager {
public:
    cTerrainSphere* GetCurrentTerrainSphere();   // 0x00f67d90
};
cNounManager* NounManager(uint32_t id);          // 0x00b3d300

// The planet being traded with: holds its own inventory, flags and spice key.
class cPlanetRef {
public:
    ResourceKey* GetSpiceKey();          // 0x00b8dad0 (this+0x198)
    void SetSpiceKey(const ResourceKey& key);    // 0x00b8dae0
    int GetSpiceSituation();             // 0x00801920
    uint32_t mPad00[(0x2c) / 4];         // +0x00
    uint32_t mFlags;                     // +0x2c (0x3000 = planet has a trade post?)
};

class cEmpire {
public:
    bool IsCommodityKnown();             // 0x00fe4180
};
class cGameData {
public:
    cEmpire* GetPlayerEmpire();          // 0x00bfc5f0
};
cGameData* SpaceGameGet(uint32_t planetKey);   // 0x01002bd0

// ---- rbtree / sort primitives ------------------------------------------------------

typedef bool (__cdecl *ItemCompare)(const ItemPtr&, const ItemPtr&);

struct RBNode {
    RBNode* mpNodeRight;                 // +0x00
    RBNode* mpNodeLeft;                  // +0x04
    RBNode* mpNodeParent;                // +0x08
    char mColor;                         // +0x0c
    char mPad0d[3];                      // +0x0d
    ResourceKey mValue;                  // +0x10
};
RBNode* RBTreeIncrement(RBNode* pNode);                     // 0x00921580
void RBTreeInsert(RBNode* pNode, RBNode* pParent, RBNode* pAnchor, int eSide);   // 0x009216a0

// eastl::rbtree<ResourceKey, ResourceKey, less, use_self> sub-object (mAnchor at +4).
class RBTree {
public:
    uint8_t mCompare;                    // +0x00 (eastl::less, empty)
    uint8_t mPad01[3];
    RBNode* mpAnchorRight;               // +0x04 (rightmost node / &mAnchor when empty)
    RBNode* mpAnchorLeft;                // +0x08 (leftmost node / &mAnchor when empty)
    RBNode* mpAnchorParent;              // +0x0c (root)
    char mAnchorColor;                   // +0x10
    uint8_t mPad11[3];
    uint32_t mnSize;                     // +0x14
    void* mAllocator;                    // +0x18
public:
    bool Less(const ResourceKey& a, const ResourceKey& b) { return a < b; }
    RBNode* DoInsertValueImpl(RBNode* pParent, const ResourceKey& value, bool bForceToLeft);   // 0x0103b590
    RBNode* DoInsertUnique(const ResourceKey& value);                                          // 0x0103bc40
    RBNode* insert(RBNode* position, const ResourceKey& value);
};

void* MedianOfThree(ItemPtr* first, ItemPtr* mid, ItemPtr* last, ItemCompare cmp, ItemCompare cmp2);   // 0x01021180
ItemPtr* PartitionRange(ItemPtr* first, ItemPtr* last);                        // 0x0103bd10
void UnguardedInsertionSort(ItemPtr* first, ItemPtr* last, ItemPtr* end, ItemCompare cmp);  // 0x0103bd90
void QuickSortImpl(ItemPtr* first, ItemPtr* last, int depth, ItemCompare cmp);  // 0x0103c800

// ---- SP::cSPSpaceTrading -----------------------------------------------------------

namespace SP {
class cSPSpaceTrading {
public:
    uint32_t mPad00[0x20 / 4];           // +0x00
    Vec<ResourceKey> mFoodCommodities;   // +0x20
    Vec<ResourceKey> mCommodities;       // +0x34
    StoreVec mNPCStore;                  // +0x48
    uint32_t mPad5c[(0x9c - 0x5c) / 4];  // +0x5c (rare-map state)
    int mLastNPCStoreIndex;              // +0x9c
    uint32_t mPad0a0[(0xe4 - 0xa0) / 4]; // +0xa0
    Vec<ResourceKey> mRareRequests;      // +0xe4

    void BuildSpiceCommodities();
    void RefreshNPCSpiceCosts(cPlanetRef* planet);
    void ChooseNPCSpices(cPlanetRef* planet, bool bForce);
    void ConsiderBuyingRare(uint32_t planetKey, Vec<ResourceKey>* pOut);
    void ConsiderRareGroupRequest(uint32_t planetKey);
};
}
using SP::cSPSpaceTrading;

// 0x0103c4f0: eastl::vector<ItemPtr>::erase(first, last).
// @ 0x0103c4f0
void ItemVec::erase(ItemPtr* first, ItemPtr* last)
{
    ItemPtr* p = MoveItemRange(last, mpEnd, first);
    for (ItemPtr* pEnd = mpEnd; p < pEnd; ++p)
        p->~ItemPtr();
    mpEnd -= last - first;
}

extern const char kEastlAllocatorName[];     // 0x013f09b4 "Simulator"
extern const int kEastlAllocatorDesc;        // 0x013ebb38 eastl allocator description
void* operator new(size_t n, const char* pName, int nFlags, int nAlignment, const void* pAllocator, int nLine);   // 0x00f473a0

// 0x0103c550: eastl::fixed_vector<NPCStorePtr,5>::DoInsertValue (one element at position).
// @ 0x0103c550
void StoreVec::DoInsertValue(NPCStorePtr* position, const NPCStorePtr& value)
{
    if (mpEnd != mpCapacity) {
        const NPCStorePtr* pValue = &value;
        if ((pValue >= position) && (pValue < mpEnd))
            ++pValue;
        ::new (mpEnd) NPCStorePtr(*(mpEnd - 1));
        MoveItemRangeBackward(position, mpEnd - 1, mpEnd);
        *position = *pValue;
        ++mpEnd;
        return;
    }

    uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
    uint32_t nNewSize = nPrevSize * 2;
    if ((int)nPrevSize <= 0)
        nNewSize = 1;
    NPCStorePtr* pNewData = 0;
    if (nNewSize)
        pNewData = (NPCStorePtr*)::operator new(nNewSize * sizeof(NPCStorePtr), kEastlAllocatorName,
                                                0, 0, &kEastlAllocatorDesc, 0xd1);

    // Elements are relocatable pointers, so the old range is block-copied around the new slot.
    memcpy(pNewData, mpBegin, (char*)position - (char*)mpBegin);
    NPCStorePtr* pNewEnd = (NPCStorePtr*)((char*)pNewData + ((char*)position - (char*)mpBegin));
    if (pNewEnd)
        ::new (pNewEnd) NPCStorePtr(value);
    memcpy(pNewEnd + 1, position, (char*)mpEnd - (char*)position);
    pNewEnd = pNewEnd + 1 + (mpEnd - position);

    if (mpBegin && mpBegin != mpPoolBegin)
        operator delete(mpBegin);
    mpBegin = pNewData;
    mpEnd = pNewEnd;
    mpCapacity = pNewData + nNewSize;
}

// 0x0103c6b0: eastl::rbtree hint insert (insert(position, value)).
// @ 0x0103c6b0
RBNode* RBTree::insert(RBNode* position, const ResourceKey& value)
{
    if (position == (RBNode*)&mpAnchorRight) {
        // Hint is end(): append after the rightmost node when the value is larger.
        if (mnSize != 0 && Less(mpAnchorRight->mValue, value))
            return DoInsertValueImpl(mpAnchorRight, value, false);
    } else {
        RBNode* pNext = RBTreeIncrement(position);
        if (Less(position->mValue, value) && Less(value, pNext->mValue))
            return DoInsertValueImpl(pNext, value, position->mpNodeRight == 0);
    }
    return DoInsertUnique(value);
}

// 0x0103c800: eastl::quick_sort recursion (introsort depth guard).
// @ 0x0103c800
void QuickSortImpl(ItemPtr* first, ItemPtr* last, int depth, ItemCompare cmp)
{
    for (;;) {
        int nBytes = (int)((char*)last - (char*)first) & ~3;
        if (!(nBytes > 0x70 && depth > 0)) {
            if (depth == 0)
                UnguardedInsertionSort(first, last, last, cmp);
            return;
        }
        ItemPtr* pPivot = (ItemPtr*)MedianOfThree(first, first + (last - first) / 2, last - 1, cmp, cmp);
        ItemPtr pivot = *pPivot;
        pivot.~ItemPtr();
        ItemPtr* pMid = PartitionRange(first, last);
        --depth;
        QuickSortImpl(pMid, last, depth, cmp);
        last = pMid;
    }
}

// Small owned key buffer (0x14 bytes) whose assignment is out of line.
struct KeyVec {
    uint32_t mData[5];                   // +0x00
    KeyVec& operator=(const KeyVec& other);   // 0x006609a0
};

// 0x24-byte map entry: four key words followed by their own key buffer.
struct KeyVecEntry {
    uint32_t mData[4];                   // +0x00
    KeyVec mKeys;                        // +0x10
};

// 0x0103c8a0: eastl::copy of 0x24-byte KeyVec elements (key + its own vector).
// @ 0x0103c8a0
KeyVecEntry* CopyKeyVecRange(KeyVecEntry* first, KeyVecEntry* last, KeyVecEntry* out)
{
    while (first != last) {
        *out = *first;
        ++first;
        ++out;
    }
    return out;
}

// 0x0103c8f0: eastl::copy_backward of 0x24-byte KeyVec elements.
// @ 0x0103c8f0
KeyVecEntry* CopyKeyVecRangeBackward(KeyVecEntry* first, KeyVecEntry* last, KeyVecEntry* out)
{
    while (last != first) {
        --last;
        --out;
        *out = *last;
    }
    return out;
}

// 0x0103c940: collect the commodity keys whose "food" property marks them as spice.
// @ 0x0103c940
void cSPSpaceTrading::BuildSpiceCommodities()
{
    if (!mFoodCommodities.empty())
        return;

    int nCommodities = (int)(mCommodities.mpEnd - mCommodities.mpBegin);
    AutoRefCount<PropertyList> props;
    ResourceKey kind = {0, 0, 0};
    ResourceKey* pKey = mCommodities.mpBegin;
    for (; nCommodities != 0; --nCommodities, ++pKey) {
        PropertyManager_Get()->GetPropertyList(pKey->instance, 0x34d97fa, props.AsOutParam());
        GetPropertyAsKey(props.get(), 0x34f1a4f, &kind);
        if (kind.instance == 0x82af541)
            mFoodCommodities.push_back(*pKey);
    }
}

// 0x0103ca40: pick the NPC store's spice list (situational) and mark its spice key.
// @ 0x0103ca40
void cSPSpaceTrading::ChooseNPCSpices(cPlanetRef* planet, bool bForce)
{
    if (*planet->GetSpiceKey() != kNoKey && !bForce)
        return;

    BuildSpiceCommodities();
    int situation = planet->GetSpiceSituation() - 4;    // 4..11 -> 0..7
    bool bTradePost = (planet->mFlags & 0x3000) != 0;
    int nCommodities = (int)(mCommodities.mpEnd - mCommodities.mpBegin);
    if (nCommodities <= 0)
        return;

    float fLimit = (float)gRandom.RandomDouble();
    float fSum = 0.0f;
    ResourceKey* pKey = mCommodities.mpBegin;
    for (int i = 0; i < nCommodities; ++i, ++pKey) {
        AutoRefCount<PropertyList> props;
        PropertyManager_Get()->GetPropertyList(pKey->instance, 0x34d97fa, props.AsOutParam());

        union { int mInt; float mFloat; } value;
        value.mInt = 0;
        switch (situation) {
        case 0:
        case 5:
        case 6:
        case 7:
            if (bTradePost)
                GetPropertyT_int(props.get(), 0x68b657e, &value.mInt);
            else
                GetPropertyT_int(props.get(), 0x68b657d, &value.mInt);
            break;
        case 1:
        case 3:
        case 4:
            if (bTradePost)
                GetPropertyT_int(props.get(), 0x68b657a, &value.mInt);
            else
                GetPropertyT_int(props.get(), 0x68b6579, &value.mInt);
            break;
        default: {
            Property* pProp = 0;
            if (props.get() != 0) {
                if (bTradePost) {
                    if (props->GetProperty(0x68b657c, &pProp) && pProp->mType == 0x0d)
                        value.mFloat = *pProp->GetFloatPtr();
                } else {
                    if (props->GetProperty(0x68b657b, &pProp) && pProp->mType == 0x0d)
                        value.mFloat = *pProp->GetFloatPtr();
                }
            }
            break;
        }
        }

        fSum += value.mFloat;
        bool bTake;
        if (!bForce) {
            bTake = (fSum >= fLimit);
        } else {
            uint32_t rareTag = 0;
            Property* pProp = 0;
            if (props.get() != 0 && props->GetProperty(0x58cbb75, &pProp) && pProp->mType == 0x0a)
                rareTag = *pProp->GetUIntPtr();
            bTake = (rareTag == 0xcd3700);
        }
        if (bTake) {
            planet->SetSpiceKey(*pKey);
            return;
        }
    }
}

// 0x0103cd00: rebuild the three spice keys/costs of this planet's NPC store.
// @ 0x0103cd00
void cSPSpaceTrading::RefreshNPCSpiceCosts(cPlanetRef* planet)
{
    static const float kSpiceCostScale[10] = {
        0.6f, 0.75f, 0.85f, 1.0f, 1.2f, 1.4f, 1.65f, 2.0f, 2.5f, 3.0f
    };

    BuildSpiceCommodities();
    if ((int)(mFoodCommodities.mpEnd - mFoodCommodities.mpBegin) <= 0)
        return;

    RandomShuffle(mFoodCommodities.mpBegin, mFoodCommodities.mpEnd, &gRandom);

    cNPCStore* pStore = mNPCStore[mLastNPCStoreIndex];
    const ResourceKey& ownSpice = *planet->GetSpiceKey();
    int nKey = 0;                        // next commodity to price
    for (int slot = 0; slot < 3; ++slot) {
        // Never price the planet's own spice; step over it.
        if (mFoodCommodities[nKey] == ownSpice)
            ++nKey;

        const ResourceKey& commodity = mFoodCommodities[nKey];
        AutoRefCount<PropertyList> props;
        PropertyManager_Get()->GetPropertyList(commodity.instance, 0x34d97fa, props.AsOutParam());

        float fBase = 0.0f;
        Property* pProp = 0;
        if (props.get() != 0 && props->GetProperty(0x34f1a4a, &pProp) && pProp->mType == 0x0d)
            fBase = (pProp->mFlags & 0x30) ? *(float*)pProp->mValue.mpData : pProp->mValue.mFloat;

        float fCost = (float)(NounManager(0x1c2e590d)->GetCurrentTerrainSphere()->Measure() * fBase);

        pStore->mSpiceID.mpBegin[slot] = commodity;
        uint32_t nScale = gRandom.RandomUint32Uniform(10);
        pStore->mSpiceCost.mpBegin[slot] = kSpiceCostScale[nScale] * fCost;

        ++nKey;
    }
}

// 0x0103cf20: Simulator::cNPCStore::cNPCStore.
// @ 0x0103cf20
cNPCStore::cNPCStore()
{
    mnRefCount = 0;
    mNPCInventory.mpBegin = 0;
    mNPCInventory.mpEnd = 0;
    mNPCInventory.mpCapacity = 0;
    mInventoryAges.mpBegin = 0;
    mInventoryAges.mpEnd = 0;
    mInventoryAges.mpCapacity = 0;

    mSpiceID.Init();
    mSpiceCost.Init();
    mPlanetKey = 0xffffffff;

    // The two inline vectors start out empty.
    mSpiceCost.Clear();
    mSpiceID.Clear();

    mbNeedsReset = 0;
    for (int i = 0; i < 3; ++i) {
        mSpiceCost.push_back(0.0f);
        ResourceKey noKey = {0, 0, 0};
        mSpiceID.push_back(noKey);
    }
}

// 0x0103d090: Simulator::cNPCStore::~cNPCStore.
// @ 0x0103d090
cNPCStore::~cNPCStore()
{
    if (mSpiceCost.mpBegin && mSpiceCost.mpBegin != mSpiceCost.mpPoolBegin)
        operator delete(mSpiceCost.mpBegin);
    if (mSpiceID.mpBegin && mSpiceID.mpBegin != mSpiceID.mpPoolBegin)
        operator delete(mSpiceID.mpBegin);
    mInventoryAges.~InventoryAges();
    mNPCInventory.~ItemVec();
    mTimer.~cGonzagoTimer();
}

// 0x0103d110: queue this planet's request for any rare commodity the player can use.
// @ 0x0103d110
void cSPSpaceTrading::ConsiderBuyingRare(uint32_t planetKey, Vec<ResourceKey>* pOut)
{
    int nCommodities = (int)(mCommodities.mpEnd - mCommodities.mpBegin);
    AutoRefCount<PropertyList> props;
    ResourceKey key1 = {0, 0, 0};
    ResourceKey key2 = {0, 0, 0};
    ResourceKey key3 = {0, 0, 0};
    if (nCommodities <= 0)
        return;

    ResourceKey* pKey = mCommodities.mpBegin;
    do {
        PropertyManager_Get()->GetPropertyList(pKey->instance, 0x34d97fa, props.AsOutParam());
        if (GetPropertyAsKey(props.get(), 0x5107709, &key1)) {
            GetPropertyAsKey(props.get(), 0x510770a, &key2);
            GetPropertyAsKey(props.get(), 0x510770b, &key3);

            bool bKnown1 = true;
            bool bKnown2 = true;
            bool bKnown3 = false;
            if (key1 != kNoKey)
                bKnown1 = SpaceGameGet(key1.instance)->GetPlayerEmpire()->IsCommodityKnown();
            if (key2 != kNoKey)
                bKnown2 = SpaceGameGet(key2.instance)->GetPlayerEmpire()->IsCommodityKnown();
            if (key3 != kNoKey)
                bKnown3 = SpaceGameGet(key3.instance)->GetPlayerEmpire()->IsCommodityKnown();

            if ((!bKnown1 || !bKnown2) && !bKnown3) {
                if (!bKnown1)
                    bKnown1 = (key1.instance == planetKey);
                if (!bKnown2)
                    bKnown2 = (key2.instance == planetKey);
                if ((bKnown1 && bKnown2) || key3.instance == planetKey)
                    pOut->push_back(*pKey);
            }
        }
        ++pKey;
    } while (--nCommodities != 0);
}

// 0x0103d360: rare-group request entry point (planet key -> mRareRequests).
// @ 0x0103d360
void cSPSpaceTrading::ConsiderRareGroupRequest(uint32_t planetKey)
{
    ConsiderBuyingRare(planetKey, &mRareRequests);
}
