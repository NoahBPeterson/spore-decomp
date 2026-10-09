// Slice s0055ec70: SP::cSPObjectTemplateDB save/restore of asset timestamps, group records
// and the PaintSystem block. Unoptimized module: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast.
#include "../s0055ce80/s0055ce80.h"

extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
typedef void (__thiscall *Vfn8)(void*, void*, void**, int, int, int, int, int);
typedef void (__thiscall *Vfn2)(void*, int);
namespace EA { namespace XHTML { namespace DOM { struct Node { static int Type(void* p); }; } } }
unsigned DateTime_Set(int a);

namespace SP {

// Helpers (call targets are relocated, so signatures only fix the stack shape).
void FUN_00563e10(void* self);
void FUN_00561850(int index);
void FUN_00561970(int index);
void FUN_005631e0(void* self, void* out);
void* FUN_00566c50(void* node);
void* FUN_00564f50(void* it);
void* FUN_00564ea0(void* p);
int  FUN_00564f90(void* self);
void FUN_00555980(void* out, void* key);
void FUN_0048c720(void* it);
void FUN_00422c50(void* node);
void FUN_00564fb0(void* self);
void FUN_006926b0(void* obj);
void FUN_006913c0(int type);
void* FUN_00554020(void* out, void* val);
void FUN_00566d20(void* out, void* val, char flag);
void RBTreeErase(void* node, void* anchor);


// @ 0x0055f7a0
unsigned char FUN_0055f7a0(void* this_) {
    if (*(int*)((char*)this_ + 0x5c) == 0) {
        FUN_00563e10(this_);
        *(unsigned char*)((char*)this_ + 0x40) = 1;
        return 1;
    }
    FUN_00566c50(*(void**)((char*)this_ + 0x50));
    void* key = FUN_00564f50(*(void**)((char*)this_ + 0x50));
    void* local_c = 0;
    void* local_8 = 0;
    void* mgr = EA::ResourceMan::GetManager();
    if (local_8) {
        void* p = local_8; local_8 = 0;
        (*(void(__thiscall**)(void*))((*(void***)p)[1]))(p);
    }
    if (local_c) {
        void* p = local_c; local_c = 0;
        (*(void(__thiscall**)(void*))((*(void***)p)[1]))(p);
    }
    ((Vfn8)(*(void***)mgr)[0x10 / 4])(mgr, key, &local_c, 0, 0, 0, 0, 0);
    void* node = FUN_00564ea0(local_c);
    if (node)
        FUN_006913c0(EA::XHTML::DOM::Node::Type(node));
    unsigned char r = (unsigned char)FUN_00564f90(this_);
    if (local_8) {
        void* p = local_8;
        (*(void(__thiscall**)(void*))((*(void***)p)[1]))(p);
    }
    if (local_c) {
        void* p = local_c;
        (*(void(__thiscall**)(void*))((*(void***)p)[1]))(p);
    }
    return r;
}

// @ 0x0055f8e0
unsigned char FUN_0055f8e0(void* this_) {
    if (*(int*)((char*)this_ + 0x5c) == 0) {
        FUN_00563e10(this_);
        *(unsigned char*)((char*)this_ + 0x40) = 1;
        return 1;
    }
    void* p = (void*)0x1;
    (void)p;
    FUN_00566c50(*(void**)((char*)this_ + 0x50));
    int value = (int)FUN_00564f50(*(void**)((char*)this_ + 0x50));
    ((Vfn2)(*(void***)this_)[0x70 / 4])(this_, value);
    FUN_00566c50(*(void**)((char*)this_ + 0x50));
    *(int*)((char*)this_ + 0x5c) -= 1;
    void* node = (void*)value;
    FUN_00422c50(&node);
    void* anchor = (char*)this_ + 0x48;
    RBTreeErase(node, anchor);
    EASTL_allocator_deallocate(node);
    return 1;
}

// @ 0x0055f9e0
void FUN_0055f9e0(void* this_) {
    if (*(char*)((char*)this_ + 0x40) == 0) {
        void* obj = *(void**)((char*)this_ + 0x44);
        if (obj != 0)
            FUN_006926b0(obj);
    }
}

// @ 0x0055fa20
unsigned char FUN_0055fa20(void* this_, void* key, char flag) {
    int index = 0;
    FUN_005631e0(this_, &index);
    ((int*)this_)[0] = 0;   // placeholder to keep `index` live
    if (index == -1)
        return 0;
    if (flag != 0) {
        char tmp[8];
        void* p = FUN_00554020(tmp, &index);
        if (*(char*)((char*)p + 4) != 0) {
            FUN_00561970(index);
            *(unsigned char*)((char*)this_ + 0x1d0) = 1;
        }
        unsigned a = DateTime_Set(1);
        (void)a;
        int base = index * 0x50 + *(int*)((char*)this_ + 0x14);
        (void)base;
    } else {
        void* itpair[2];
        FUN_00555980(itpair, &index);
        void* it = (itpair[0] != itpair[1]) ? itpair[0] : *(void**)((char*)this_ + 0x68);
        if (it != *(void**)((char*)this_ + 0x68)) {
            FUN_0048c720(it);
            FUN_00561850(index);
        }
    }
    return 1;
}

// @ 0x0055fb30
unsigned char FUN_0055fb30(void* this_, void* key) {
    int index = 0;
    FUN_005631e0(this_, &index);
    if (index != -1) {
        void* itpair[2];
        FUN_00555980(itpair, &index);
        void* it = (itpair[0] != itpair[1]) ? itpair[0] : *(void**)((char*)this_ + 0x68);
        if (it != *(void**)((char*)this_ + 0x68))
            return 1;
    }
    return 0;
}

// @ 0x0055fbb0
unsigned char FUN_0055fbb0(void* this_, void* key) {
    int index = 0;
    FUN_005631e0(this_, &index);
    if (index == -1)
        return 0;
    unsigned a = DateTime_Set(1);
    (void)a;
    int base = index * 0x50 + *(int*)((char*)this_ + 0x14);
    (void)base;
    return 1;
}

}

// ---------------------------------------------------------------------------------------------
// 0x0055ec70: cSPObjectTemplateDB asset-index rebuild driver (2855 bytes, /Od).
// Rebuilds the set of group IDs used by the classifier/summarizer tables, collects the keys of
// resources in those groups into the pending set, rescans the asset list from the type-0x2d5c9af
// keys of the save DB, then indexes pending keys (time-limited unless bForce), and when work is
// left over hands itself to a job. Out-of-line helpers are declared only (calls are relocated).
// ---------------------------------------------------------------------------------------------
union LargeInteger { struct { uint32_t LowPart; int32_t HighPart; } u; int64_t QuadPart; };
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(LargeInteger* p);

namespace EA {
class Stopwatch {
public:
    Stopwatch(int units, bool bStartImmediately);                  // 0x0093a560
    uint64_t mnStartTime;
    uint64_t mnTotalElapsedTime;
    int mnUnits;
    float mfStopwatchCyclesToUnitsCoefficient;
    static uint64_t GetStopwatchCycle() {
        LargeInteger li;
        QueryPerformanceCounter(&li);
        return (uint64_t)li.QuadPart;
    }
};
class LimitStopwatch : public Stopwatch {
public:
    LimitStopwatch(int units) : Stopwatch(units, false) {}
    void SetTimeLimit(uint32_t nLimit, bool bStartImmediately);    // 0x0093a480
    bool IsTimeUp() const { return (int64_t)(mnEndTime - GetStopwatchCycle()) < 0; }
    uint64_t mnEndTime;
};
}

namespace idx {

struct input_iterator_tag {};
struct true_type {};

template<typename Container>
struct insert_iterator {
    Container* container;
    typename Container::iterator it;
    insert_iterator(Container& x, typename Container::iterator i) : container(&x), it(i) {}
    insert_iterator& operator=(const typename Container::value_type& value);   // 0x00565a80
    insert_iterator& operator*() { return *this; }
    insert_iterator& operator++(int) { return *this; }
};
template<typename Container>
inline insert_iterator<Container> inserter(Container& x, typename Container::iterator i) {
    return insert_iterator<Container>(x, i);
}
template<typename In, typename Out>
inline Out copy(In first, In last, Out result, input_iterator_tag) {
    for (; first != last; ++first)
        *result++ = *first;
    return result;
}

// rbtree<ResourceKey> (eastl::set); the iterator helpers are shared COMDAT-folded instances.
template<typename V>
struct rbtree_iterator {
    eastl::rbtree_node_base* mpNode;
    rbtree_iterator(const eastl::rbtree_node_base* pNode);         // 0x00566c50
    rbtree_iterator(const rbtree_iterator& x) : mpNode(x.mpNode) {}
    V& operator*() const;                                          // 0x00564f50
    rbtree_iterator& operator++();                                 // 0x00422c50
    bool operator!=(const rbtree_iterator& x) const { return mpNode != x.mpNode; }
};
struct KeySet {
    typedef rbtree_iterator<ResourceKey> iterator;
    typedef eastl::rbtree_node_base node_type;
    uint32_t mCompare;
    eastl::rbtree_node_base mAnchor;
    size_t mnSize;
    uint32_t mAllocator;
    iterator begin() { return iterator(mAnchor.mpNodeLeft); }
    bool empty() const { return mnSize == 0; }
    size_t size() const { return mnSize; }
    void DoNuke(node_type* pNode);                                 // 0x004e8a30
    void reset();                                                  // 0x004b5a20
    void clear() { DoNuke((node_type*)mAnchor.mpNodeParent); reset(); }
    eastl::pair<iterator, bool> DoInsertValue(const ResourceKey& value, true_type);   // 0x004290c0
    eastl::pair<iterator, bool> insert(const ResourceKey& value) { return DoInsertValue(value, true_type()); }
    size_t erase(const ResourceKey& key);                          // 0x005648c0
    iterator erase(iterator position);                             // 0x00566510
};
// map<uint32_t, ValueMap<T>> parameter tables: only clear() is used here.
struct ParamMap {
    typedef eastl::rbtree_node_base node_type;
    uint32_t mCompare;
    eastl::rbtree_node_base mAnchor;
    size_t mnSize;
    uint32_t mAllocator;
    void DoNuke(node_type* pNode);                                 // 0x00566ad0
    void reset();                                                  // 0x004b5a20
    void clear() { DoNuke((node_type*)mAnchor.mpNodeParent); reset(); }
};
// map<uint32_t, AutoRefCount<...>> classifier/summarizer tables: key iteration only.
struct IDMap {
    typedef rbtree_iterator<const uint32_t> key_iterator;
    uint32_t mCompare;
    eastl::rbtree_node_base mAnchor;
    size_t mnSize;
    uint32_t mAllocator;
    key_iterator key_begin() { return key_iterator(mAnchor.mpNodeLeft); }
    key_iterator key_end() { return key_iterator(&mAnchor); }
};

// Resource filter on a sorted list of group IDs (Skinner-labelled ctor at 0x0055eae0).
struct GroupIDList {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    uint32_t mAllocator;
    uint32_t mCompare;
    ~GroupIDList();                                                // 0x004e1bf0
};
struct GroupFilter : public IResourceFilter {
    GroupIDList mGroupIDs;
    GroupFilter(const uint32_t* pGroupIDs, size_t count);          // 0x0055eae0
    virtual bool IsValid(const ResourceKey& key);
};
// Resource filter on one type ID.
struct TypeFilter : public IResourceFilter {
    uint32_t mTypeID;
    TypeFilter(uint32_t typeID) : mTypeID(typeID) {}
    virtual bool IsValid(const ResourceKey& key);
};

// Key list whose allocator ctor is out of line (0x00540470); shares the KeyVectorBase dtor.
struct KeyList : public eastl::KeyVectorBase<ResourceKey> {
    KeyList(const eastl::allocator& a = eastl::allocator());       // 0x00540470
    ~KeyList() { eastl::destruct(mpBegin, mpEnd); }
    ResourceKey* begin() { return mpBegin; }
    ResourceKey* end() { return mpEnd; }
};

struct IKeyLister {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
    virtual void v0c(); virtual void v0d();
    virtual int GetResourceKeyList(eastl::KeyVectorBase<ResourceKey>& keys, IResourceFilter* pFilter, void* pDBs);  // +0x38
};
extern IKeyLister* gSaveDatabase;                                  // 0x015e3f00

struct cJob {
    uint32_t pad00[0x18 / 4];
    int mnState;                                                   // +0x18
    void Release();                                                // 0x00690120
    void SetOwner(void* pOwner);                                   // 0x00564f70
    void Start();                                                  // 0x006909b0
};
struct cJobManager {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual bool CreateJob(cJob** ppJob);                          // +0x10
};
cJobManager* JobManager();                                         // 0x0068f4d0

}

namespace eastl { void sort(ResourceKey* first, ResourceKey* last); }   // 0x004f6b70

namespace SP {

inline uint32_t ModelTypeFromGroupID(uint32_t groupID) { return (groupID >> 16) & 0xff; }

class cSPObjectTemplateDBIndex {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
    virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual void v18(); virtual void v19(); virtual void v1a(); virtual void v1b();
    virtual bool IndexAsset(const ResourceKey& key);               // +0x70

    uint32_t pad04[(0x14 - 0x04) / 4];
    eastl::vector<cSPObjectTemplateDB::AssetInfo, eastl::sp_vector_allocator> mAssetList;  // +0x14
    uint32_t pad28[(0x40 - 0x28) / 4];
    bool mbIndexComplete;                                          // +0x40
    IntrusivePtr<idx::cJob> mpIndexJob;                            // +0x44
    idx::KeySet mPendingKeys;                                      // +0x48
    uint32_t pad64[(0xf4 - 0x64) / 4];
    idx::ParamMap mIntParameters;                                  // +0xf4
    idx::ParamMap mFloatParameters;                                // +0x110
    uint32_t pad12c[(0x1ec - 0x12c) / 4];
    idx::IDMap mClassifierTable;                                   // +0x1ec
    idx::IDMap mSummarizerTable;                                   // +0x208
    uint32_t pad224;
    eastl::vector_set<uint32_t> mIndexGroupIDs;                    // +0x228

    bool GroupsChanged();                                          // 0x0055dfe0
    bool IsKeyIncluded(const ResourceKey& key);                    // 0x0055cff0
    void OnIndexComplete();                                        // 0x00563e10
    bool RebuildIndex(bool bForce, bool bAddMissing);
};

// @ 0x0055ec70
bool cSPObjectTemplateDBIndex::RebuildIndex(bool bForce, bool bAddMissing) {
    bool result = true;
    EA::LimitStopwatch stopwatch(5);
    stopwatch.SetTimeLimit(5, true);

    if (GroupsChanged() || bForce) {
        idx::copy(mClassifierTable.key_begin(), mClassifierTable.key_end(),
                  idx::inserter(mIndexGroupIDs, mIndexGroupIDs.begin()), idx::input_iterator_tag());
        idx::copy(mSummarizerTable.key_begin(), mSummarizerTable.key_end(),
                  idx::inserter(mIndexGroupIDs, mIndexGroupIDs.begin()), idx::input_iterator_tag());
    }
    mPendingKeys.clear();

    if (!mIndexGroupIDs.empty() && !bAddMissing) {
        idx::KeyList keys;
        idx::GroupFilter filter(mIndexGroupIDs.begin(), mIndexGroupIDs.size());
        ((idx::IKeyLister*)EA::ResourceMan::GetManager())->GetResourceKeyList(keys, &filter, 0);
        eastl::sort(keys.begin(), keys.end());
        ResourceKey lastKey;
        lastKey.mInstanceID = 0;
        lastKey.mTypeID = 0;
        lastKey.mGroupID = 0;
        for (ResourceKey* it = keys.mpBegin, *itEnd = keys.mpEnd; it != itEnd; ++it) {
            if (it->mGroupID == 0)
                continue;
            if (it->mGroupID == lastKey.mGroupID && it->mInstanceID == lastKey.mInstanceID)
                continue;
            lastKey = *it;
            lastKey.mTypeID = SP::EditorEntityToResourceType(ModelTypeFromGroupID(it->mGroupID), 1);
            mPendingKeys.insert(lastKey);
        }
    }

    mAssetList.clear();
    mIntParameters.clear();
    mFloatParameters.clear();

    eastl::key_vector<ResourceKey> savedKeys;
    idx::TypeFilter typeFilter(0x2d5c9af);
    if (idx::gSaveDatabase && idx::gSaveDatabase->GetResourceKeyList(savedKeys, &typeFilter, 0)) {
        size_t pendingCount = mPendingKeys.size();
        size_t savedCount = savedKeys.size();
        size_t reserveCount = (savedCount < pendingCount) ? pendingCount : savedCount;
        reserveCount = (reserveCount >> 3) + reserveCount;
        mAssetList.reserve(reserveCount);
        for (ResourceKey* it = savedKeys.mpBegin, *itEnd = savedKeys.mpEnd; it != itEnd; ++it) {
            const ResourceKey& savedKey = *it;
            ResourceKey key;
            key.mInstanceID = 0;
            key.mTypeID = 0;
            key.mGroupID = 0;
            key = savedKey;
            key.mTypeID = SP::EditorEntityToResourceType(ModelTypeFromGroupID(savedKey.mGroupID), 1);
            bool bIncluded = true;
            if (mIndexGroupIDs.find(key.mTypeID) == mIndexGroupIDs.end()) {
                mPendingKeys.erase(key);
                bIncluded = IsKeyIncluded(savedKey);
            } else if (bAddMissing) {
                mPendingKeys.insert(key);
            }
            result = result && bIncluded;
        }
    }

    while (!mPendingKeys.empty()) {
        if (!bForce && stopwatch.IsTimeUp())
            break;
        const ResourceKey& key = *mPendingKeys.begin();
        result = IndexAsset(key) && result;
        mPendingKeys.erase(mPendingKeys.begin());
    }

    if (!mPendingKeys.empty()) {
        idx::cJobManager* pJobManager = idx::JobManager();
        if (!pJobManager->CreateJob(&mpIndexJob))
            return false;
        mpIndexJob.mpObject->mnState = 1;
        mpIndexJob.mpObject->SetOwner(this);
        mpIndexJob.mpObject->Start();
        return false;
    }

    if (!mIndexGroupIDs.empty()) {
        mIndexGroupIDs.clear();
        OnIndexComplete();
    }
    mbIndexComplete = true;
    return result;
}

}

// Layout checks for the index view of cSPObjectTemplateDB.
#define IDX_OFFSETOF(T, m) ((size_t)&reinterpret_cast<const volatile char&>(((T*)0)->m))
typedef char kCheckAssetList[(sizeof(eastl::vector<SP::cSPObjectTemplateDB::AssetInfo, eastl::sp_vector_allocator>) == 0x14) ? 1 : -1];
typedef char kCheckJob[(IDX_OFFSETOF(SP::cSPObjectTemplateDBIndex, mpIndexJob) == 0x44) ? 1 : -1];
typedef char kCheckPending[(IDX_OFFSETOF(SP::cSPObjectTemplateDBIndex, mPendingKeys) == 0x48) ? 1 : -1];
typedef char kCheckInt[(IDX_OFFSETOF(SP::cSPObjectTemplateDBIndex, mIntParameters) == 0xf4) ? 1 : -1];
typedef char kCheckFloat[(IDX_OFFSETOF(SP::cSPObjectTemplateDBIndex, mFloatParameters) == 0x110) ? 1 : -1];
typedef char kCheckClassifier[(IDX_OFFSETOF(SP::cSPObjectTemplateDBIndex, mClassifierTable) == 0x1ec) ? 1 : -1];
typedef char kCheckSummarizer[(IDX_OFFSETOF(SP::cSPObjectTemplateDBIndex, mSummarizerTable) == 0x208) ? 1 : -1];
typedef char kCheckGroups[(IDX_OFFSETOF(SP::cSPObjectTemplateDBIndex, mIndexGroupIDs) == 0x228) ? 1 : -1];
typedef char kCheckGroupFilter[(sizeof(idx::GroupFilter) == 0x18) ? 1 : -1];
typedef char kCheckTypeFilter[(sizeof(idx::TypeFilter) == 0x8) ? 1 : -1];
typedef char kCheckStopwatch[(sizeof(EA::LimitStopwatch) == 0x20) ? 1 : -1];
