// Slice s00ef9e40 -- Simulator::cScenarioTutorials methods: rebuild of the step hashtables,
// message registration, app-preference read, and per-category / per-entry update helpers.
// Region flags: /O2 /MD /Gy /TP
#include "types.h"

// ---------------------------------------------------------------------------
// external helpers (masked relocations); thiscall callees modelled as stub members
// ---------------------------------------------------------------------------
extern "C" void* __cdecl SP_MessageServer();       // 0x0067dcc0
extern "C" void* __cdecl FUN_0067cac0();           // 0x0067cac0
#define SP_GetSomeMgr FUN_0067cac0
extern "C" void  __cdecl operator_delete_(void*);  // 0x00f47380

struct HashClear { void clear(void*, void*); };          // 0x0068fb70, ret 8
struct HashCtor  { void* ctor(int, int); };              // 0x00ef9950, ret 8
struct HashErase { void erase(void*, void*, void*, void*); }; // 0x00ef9a20, ret 0x10
struct CatUpdate { void f(int); };                       // 0x00ef7ec0, ret 4
struct EntryUpdate { void f(int); };                     // 0x00ef9af0, ret 4
struct InputFwd  { void f(int); };                       // 0x00ef8a10, ret 4
struct CatState  { unsigned f(int); };               // 0x00ef7330, ret 4
struct CatValid  { bool f(int); };                   // 0x00ef72d0, ret 4
struct Stopwatch { void SetTimeLimit(int, int); };       // 0x0093a480, ret 8
struct HashInsert { void insert(void*, void*); };        // 0x00ef8cc0, ret 8
struct HashFind  { void find(void*, void*); };           // 0x00a23ef0, ret 8
struct RefreshUI { void Refresh(); };                    // 0x00efbce0, ret 0
struct Mgr830    { void f(int); };                       // 0x0067c830, ret 4
extern "C" void __cdecl RefreshChecklist();              // 0x00efbce0 (call with this already in ecx)

// ---------------------------------------------------------------------------
// globals
// ---------------------------------------------------------------------------
extern void*    g_AppPreferences;      // 0x015fd91c
extern uint32_t g_msgNames[11];        // 0x0148b5d8
extern int      g_catTableA[];         // 0x0148b450 {lo,hi,hash,flag} x 0x10
extern int      g_catTableB[];         // 0x0148b510
extern uint8_t  g_16c7b50[2];          // 0x016c7b50

// ---------------------------------------------------------------------------
// eastl hash_set pieces used by the two completed-group sets.
// ---------------------------------------------------------------------------
struct PrimeRehashPolicyData {
    float mfMaxLoadFactor;   // +0
    float mfGrowthFactor;    // +4
    uint32_t mnNextResize;   // +8
};

struct HashLink { HashLink* mpNext; };

struct FixedPoolBase {
    HashLink* mpHead;        // +0
    HashLink* mpNext;        // +4
    void init(void* memory, uint32_t size, uint32_t nodeSize, uint32_t align, uint32_t offset); // 0x00921260
};

struct FixedPool : FixedPoolBase {
    void* mpPoolBegin;       // +8
    void* mpPoolEnd;         // +0c
    uint32_t mnNodeSize;     // +10
    void deallocate(void* p)
    {
        if ((p >= mpPoolBegin) && (p < mpPoolEnd)) {
            ((HashLink*)p)->mpNext = mpHead;
            mpHead = (HashLink*)p;
        } else {
            delete[] (char*)p;
        }
    }
};

struct FixedHashtableAllocator {
    FixedPool mPool;          // +0
    void* mpBucketBuffer;     // +14
};

struct StepNode {
    int mKey;                 // +0
    StepNode* mpNext;         // +4
};

struct StepIterator {
    StepNode* mpNode;
    StepNode** mpBucket;
    StepIterator(StepNode* node, StepNode** bucket) : mpNode(node), mpBucket(bucket) {}
};

struct StepInsertResult {
    StepNode* mpNode;
    StepNode** mpBucket;
    bool second;
};

struct HashFn {};
struct EqFn {};
struct true_type {};

// hash_set<int> with the small fixed allocator used by each completed-group set.
struct StepSetSmall {
    uint32_t mHashCodeBase;                 // +00
    StepNode** mpBucketArray;               // +04
    uint32_t mnBucketCount;                 // +08
    uint32_t mnElementCount;                // +0c
    PrimeRehashPolicyData mRehashPolicy;    // +10
    FixedHashtableAllocator mAllocator;     // +1c
    StepNode* mBuckets[0x48 / 4];           // +34
    char mNodes[0x80];                      // +7c

    StepSetSmall(const HashFn& h = HashFn(), const EqFn& e = EqFn()); // 0x00ef9950

    void DoFreeNodes(StepNode** buckets, uint32_t count);              // 0x0068fb70
    void DoInsertRange(StepNode* first, StepNode** firstBucket,
                       StepNode* last, StepNode** lastBucket);         // 0x00ef9a20
    StepInsertResult DoInsertValue(const int& key, true_type);         // 0x00ef8cc0

    StepIterator begin() const
    {
        StepNode** bucket = mpBucketArray;
        StepNode* node = *bucket;
        while (node == 0)
            node = *++bucket;
        return StepIterator(node, bucket);
    }
    StepIterator end() const
    {
        StepNode** bucket = mpBucketArray + mnBucketCount;
        return StepIterator(*bucket, bucket);
    }
    void DoFreeBuckets(StepNode** buckets, uint32_t count)
    {
        if (count > 1 && buckets != mAllocator.mpBucketBuffer)
            mAllocator.mPool.deallocate(buckets);
    }
    StepSetSmall& operator=(const StepSetSmall& other)
    {
        if (this != &other) {
            DoFreeNodes(mpBucketArray, mnBucketCount);
            mnElementCount = 0;
            StepIterator first = other.begin();
            StepIterator last = other.end();
            DoInsertRange(first.mpNode, first.mpBucket, last.mpNode, last.mpBucket);
        }
        return *this;
    }
    ~StepSetSmall()
    {
        DoFreeNodes(mpBucketArray, mnBucketCount);
        mnElementCount = 0;
        DoFreeBuckets(mpBucketArray, mnBucketCount);
    }
};

struct StepGroup {
    StepSetSmall mSet;         // +000
    uint32_t mUnknown[0x50 / 4]; // +0fc
};

// EA::Variant / property list access used for the saved completion counts.
struct EA_Variant {
    char mValue[0x10];         // +00
    uint16_t mFlags;           // +10
    uint16_t mTypeId;          // +12
};

struct IPropertyList {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20();
    virtual bool GetProperty(uint32_t id, EA_Variant** out); // +0x24
};

struct MessageServer {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20();
    virtual void Register(void* owner, uint32_t name); // +0x24
};

struct MessageHandlerRef {
    void* mpServer;            // +00
    void* mpOwner;             // +04
    uint32_t* mpNames;         // +08
    int mnCount;               // +0c
    int mField10;              // +10
};

// ---------------------------------------------------------------------------
// cScenarioTutorials -- base at +0 is cContentValidationSummarizer.
// ---------------------------------------------------------------------------
struct cScenarioTutorials {
    char pad0[0x10];
    char mTimer[0x20];         // +10
    int mCurStep;              // +30
    int mCurLesson;            // +34
    uint8_t mCurrentBits[3];   // +38
    uint8_t mFlag3b;           // +3b
    char pad3c[4];             // +3c
    uint8_t mFlag40;           // +40
    char pad41[7];             // +41
    MessageHandlerRef mHandler; // +48
    char mSeenSteps[0x4a8 - 0x5c];
    StepGroup mGroups[2];      // +4a8, +5f4

    char* self() { return (char*)this; }
    void Reset();                              // 0x00ef9e40
    void UpdateAll();                          // 0x00efa040
    void SetCategoryState(int category, char flag);   // 0x00efa0b0
    void HandleCategoryMessage(int category, int arg); // 0x00efa110
};

// @ 0x00ef9e40
void cScenarioTutorials::Reset()
{
    *(uint16_t*)&mCurrentBits[0] = 0;
    mCurrentBits[2] = 0;

    StepGroup* group = mGroups;
    int n = 2;
    do {
        StepGroup temp;
        group->mSet = temp.mSet;
        group = (StepGroup*)((char*)group + 0x14c);
    } while (--n != 0);

    void* ms = SP_MessageServer();
    mHandler.mpServer = ms;
    mHandler.mpOwner = this;
    mHandler.mpNames = g_msgNames;
    mHandler.mnCount = 0xb;
    mHandler.mField10 = 0;
    if (ms != 0 && this != 0) {
        for (uint32_t i = 0; i < 0xb; ++i)
            ((MessageServer*)ms)->Register(this, g_msgNames[i]);
    }

    int counts[2] = { 0, 0 };
    IPropertyList* prefs = (IPropertyList*)g_AppPreferences;
    if (prefs != 0) {
        EA_Variant* value;
        if (prefs->GetProperty(0x7abf095, &value) && value->mTypeId == 10) {
            if (value->mFlags & 0x30)
                value = *(EA_Variant**)value;
            counts[0] = *(int*)value;
        }
        if (prefs->GetProperty(0x7abf09d, &value) && value->mTypeId == 10) {
            if (value->mFlags & 0x30)
                value = *(EA_Variant**)value;
            counts[1] = *(int*)value;
        }
    }

    group = mGroups;
    int i = 0;
    do {
        int count = counts[i];
        g_16c7b50[i] = (count != 0);
        if (count > 0) {
            int k = 0;
            do {
                group->mSet.DoInsertValue(k, true_type());
                k += 1;
            } while (k < count);
        }
        i += 1;
        group = (StepGroup*)((char*)group + 0x14c);
    } while (i < 2);
}

// @ 0x00efa040
void cScenarioTutorials::UpdateAll()
{
    char* self = (char*)this;
    int idx = *(int*)(self + 0x30);
    if (idx == -1)
        return;
    int sel = *(int*)(self + 0x34);
    int* p;
    if (sel == 0) {
        p = (int*)((char*)g_catTableA + idx * 0x10);
    } else if (sel == 1) {
        p = (int*)((char*)g_catTableB + idx * 0x10);
    }
    int i = 0;
    do {
        ((CatUpdate*)self)->f(i);
        i++;
    } while (i != 0xad);
    int e = p[0];
    if (e <= p[1]) {
        do {
            ((EntryUpdate*)self)->f(e);
            e++;
        } while (e <= p[1]);
    }
}

// @ 0x00efa0b0
void cScenarioTutorials::SetCategoryState(int category, char flag)
{
    char* self = (char*)this;
    ((InputFwd*)self)->f(category);
    ((CatUpdate*)self)->f(category);
    unsigned state = ((CatState*)self)->f(category);
    if (state > 0) {
        ((Stopwatch*)(self + 0x10))->SetTimeLimit(state, 1);
        *(uint8_t*)(self + 0x3b) = 1;
    }
    ((EntryUpdate*)self)->f(category);
    if (((CatValid*)self)->f(category) && *(int*)(self + 0x30) != -1 && flag != 0) {
        RefreshChecklist();
    }
}

// @ 0x00efa110
void cScenarioTutorials::HandleCategoryMessage(int category, int arg)
{
    char* self = (char*)this;
    int local;
    int k = category;
    ((HashFind*)(self + 0x5c))->find(&local, &k);
    if (local == *(int*)(*(int*)(self + 0x60) + *(int*)(self + 0x64) * 4)) {
        ((InputFwd*)self)->f(category);
        ((CatUpdate*)self)->f(category);
        unsigned state = ((CatState*)self)->f(category);
        if (state > 0) {
            ((Stopwatch*)(self + 0x10))->SetTimeLimit(state, 1);
            *(uint8_t*)(self + 0x3b) = 1;
        }
        ((EntryUpdate*)self)->f(category);
    }
    if (*(uint8_t*)(self + 0x40) == 0) {
        ((Mgr830*)SP_GetSomeMgr())->f(arg);
    }
}
