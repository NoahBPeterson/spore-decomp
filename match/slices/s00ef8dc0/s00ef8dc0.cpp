// Slice s00ef8dc0: Simulator::cScenarioTutorials (tutorial manager) and its UI page.
// The manager owns a "seen steps" hash_set<int> (+0x5c) and two "completed groups" hash_sets (+0x4a8, +0x5f4),
// all fixed_hashtable_allocator based.  A tutorial UI page (cTutorialPage) builds a scrolling list of lesson
// groups/steps from cSPUILayout resources.  /O2 /MD /Gy /EHsc /TP /arch:SSE region.
#include "types.h"

void* __cdecl operator new(unsigned size, const char* name, int flags, int debugFlags, int file, int line);   // 0x00f473a0

// ---------------------------------------------------------------------------------------------
// Common helper types
struct Rect {
    float left, top, right, bottom;
};

struct ResourceKey {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
};

class IReleasable {
public:
    virtual int AddRef();
    virtual int Release();
};

// ---------------------------------------------------------------------------------------------
// UI windows
class IWindow {
public:
    virtual int AddRef();                                           // +0x00
    virtual int Release();                                          // +0x04
    virtual void v08();
    virtual IWindow* GetComponent(uint32_t id);                     // +0x0c
    virtual IWindow* GetParent();                                   // +0x10
    virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24();
    virtual void SetStateFlag(int state, bool on);                  // +0x28
    virtual void v2c(); virtual void v30(); virtual void v34();
    virtual const Rect* GetArea();                                  // +0x38
    virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void SetControlID(int id);                              // +0x50
    virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68();
    virtual void SetArea(const Rect* area);                         // +0x6c
    virtual void v70();
    virtual void SetSize(float width, float height);                // +0x74
    virtual void v78();
    virtual void SetFlag(int flag, bool value);                     // +0x7c
    virtual void SetCaption(const wchar_t* text);                   // +0x80
    virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac();
    virtual void vb0(); virtual void vb4(); virtual void vb8(); virtual void vbc();
    virtual void vc0(); virtual void vc4(); virtual void vc8(); virtual void vcc();
    virtual void vd0(); virtual void vd4();
    virtual void AddWindow(IWindow* child);                         // +0xd8
    virtual void vdc(); virtual void ve0(); virtual void ve4(); virtual void ve8(); virtual void vec();
    virtual IWindow* GetChildByID(int id, bool recursive);          // +0xf0
    virtual void vf4(); virtual void vf8(); virtual void vfc(); virtual void v100();
    virtual void AddWinProc(void* proc);                            // +0x104
};

// Reference-counted window handle.
struct WindowRef {
    IWindow* mp;
    IWindow* operator->() const { return mp; }
    operator IWindow*() const { return mp; }
    ~WindowRef()
    {
        if (mp)
            mp->Release();
    }
    WindowRef& operator=(IWindow* p)
    {
        if (p != mp) {
            IWindow* const pTemp = mp;
            if (p)
                p->AddRef();
            mp = p;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
};

class cSPUILayout {
public:
    virtual void Destroy();
    virtual int AddRef();
    virtual int Release();
    char pad4[0x18 - 4];
    cSPUILayout();                                                  // 0x00810000
    ~cSPUILayout();                                                 // 0x00811fe0
    IWindow* FindWindowByID(uint32_t id, bool recursive);           // 0x008105b0
    bool Init(const ResourceKey& key, bool visible, uint32_t parentID);   // 0x008120d0
    void SetParentWin(IWindow* parent, bool b, uint32_t id);        // 0x008121b0
    void SetReloadCallback(void (*cb)(void*, int, char), void* user);    // 0x00810090
    void Shutdown(bool b);                                          // 0x00811ad0
};

// Localized string (resource id lookup).
class cString {
public:
    cString(uint32_t tableID, uint32_t instanceID, const wchar_t* defaultText);   // 0x006b5770
    ~cString();                                                     // 0x006b5240
    const wchar_t* c_str();                                         // 0x006b55c0
    uint32_t pad[5];
};

// ---------------------------------------------------------------------------------------------
// EA::Variant (dev PDB: size 0x14; mFlags +0x10, mTypeId +0x12)
struct Variant {
    char mValue[0x10];
    uint16_t mFlags;
    uint16_t mTypeId;
    Variant() { mTypeId = 10; mFlags = 2; }
    Variant& operator=(const int& v);                               // 0x00427fd0
    void Destruct(int flags);                                       // 0x0093db80
    ~Variant()
    {
        if (mFlags & 4)
            Destruct(0);
    }
};

class IPropertyList {
public:
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c(); virtual void s10();
    virtual void SetProperty(uint32_t id, const Variant* value);    // +0x14
};
extern IPropertyList* gAppPreferences;                              // 0x015fd91c

struct cSaveArea;
cSaveArea* __cdecl GetSaveArea(uint32_t id);                        // 0x006b1f90 (SP::GetSaveArea)
void __cdecl SaveResource(void* props, cSaveArea* area, int flags); // 0x006b1d50 (SP::SaveResource)
void __cdecl RemoveHandler(int handler, int a, int b, int c, int d);// 0x00571db0 (EA::Messaging::RemoveHandler)

// Wide-string number formatting (EA::Locale::SetNumberString)
int __cdecl SetNumberString(int64_t value, wchar_t* buffer, int bufferSize);   // 0x00881ae0

// ---------------------------------------------------------------------------------------------
// eastl pieces (hash_set<int> over fixed_hashtable_allocator)
namespace eastl {

struct true_type {};

struct prime_rehash_policy_data {
    float mfMaxLoadFactor;
    float mfGrowthFactor;
    uint32_t mnNextResize;
};
struct prime_rehash_policy : prime_rehash_policy_data {
    prime_rehash_policy(float fMaxLoadFactor = 1.f)
    {
        mfMaxLoadFactor = fMaxLoadFactor;
        mfGrowthFactor = 2.f;
        mnNextResize = 0;
    }
    uint32_t GetBucketCount(uint32_t nElementCount) const;          // 0x009213c0
};
uint32_t __cdecl GetPrevBucketCountOnly(uint32_t n);                // 0x00921340

struct Link { Link* mpNext; };

struct fixed_pool_base {
    Link* mpHead;
    Link* mpNext;
    fixed_pool_base() {}
    void init(void* pMemory, uint32_t memorySize, uint32_t nodeSize, uint32_t alignment, uint32_t alignmentOffset);   // 0x00921260
};

struct fixed_pool_with_overflow : fixed_pool_base {
    void* mpPoolBegin;     // +8
    void* mpPoolEnd;       // +0xc
    uint32_t mnNodeSize;   // +0x10
    fixed_pool_with_overflow() {}
    void deallocate(void* p)
    {
        if ((p >= mpPoolBegin) && (p < mpPoolEnd)) {
            ((Link*)p)->mpNext = mpHead;
            mpHead = ((Link*)p);
        } else
            delete[] (char*)p;
    }
};

struct fixed_hashtable_allocator {
    fixed_pool_with_overflow mPool;   // +0
    void* mpBucketBuffer;             // +0x14
    fixed_hashtable_allocator() {}
};

}  // namespace eastl
using namespace eastl;

struct StepNode {
    int mKey;
    StepNode* mpNext;
};

struct StepInsertResult {
    StepNode* mpNode;
    StepNode** mpBucket;
    bool second;
    StepInsertResult() : mpNode(0), mpBucket(0), second(false) {}
};

struct StepIterator {
    StepNode* mpNode;
    StepNode** mpBucket;
    StepIterator(StepNode* n, StepNode** b) : mpNode(n), mpBucket(b) {}
    explicit StepIterator(StepNode** b) : mpNode(*b), mpBucket(b) {}
    StepIterator(const StepIterator& x) : mpNode(x.mpNode), mpBucket(x.mpBucket) {}
    bool operator==(const StepIterator& x) const { return mpNode == x.mpNode; }
};

struct HashFn { HashFn() {} };
struct EqFn { EqFn() {} };
struct ModRangeHashing {};
struct RangedHash {};
struct UseSelf {};

// hash_set<int, ..., fixed_hashtable_allocator>: 0x34 bytes of table state
struct StepSet {
    uint32_t mHashCodeBase;                  // +0
    StepNode** mpBucketArray;                // +4
    uint32_t mnBucketCount;                  // +8
    uint32_t mnElementCount;                 // +0xc
    prime_rehash_policy_data mRehashPolicy;  // +0x10
    fixed_hashtable_allocator mAllocator;    // +0x1c

    void DoRehash(uint32_t nNewBucketCount);                              // 0x00ef7c00
    void DoFreeNodes(StepNode** pNodeArray, uint32_t n);                  // 0x0068fb70
    StepInsertResult DoInsertValue(const int& key, true_type);            // 0x00ef8cc0

    void set_max_load_factor(float f)
    {
        prime_rehash_policy rp(f);
        mRehashPolicy = rp;
        const uint32_t nBuckets = rp.GetBucketCount(mnElementCount);
        if (nBuckets > mnBucketCount)
            DoRehash(nBuckets);
    }
    StepIterator end() { return StepIterator(mpBucketArray + mnBucketCount); }
    static StepNode* DoFindNode(StepNode* pNode, const int& k, uint32_t)
    {
        for (; pNode; pNode = pNode->mpNext)
            if (k == pNode->mKey)
                return pNode;
        return 0;
    }
    StepIterator find(const int& k)
    {
        const uint32_t c = (uint32_t)k;
        const uint32_t n = c % mnBucketCount;
        StepNode* const pNode = DoFindNode(mpBucketArray[n], k, c);
        return pNode ? StepIterator(pNode, mpBucketArray + n) : StepIterator(mpBucketArray + mnBucketCount);
    }
    void DoFreeBuckets(StepNode** pBucketArray, uint32_t n)
    {
        if (n > 1 && (void*)pBucketArray != mAllocator.mpBucketBuffer)
            mAllocator.mPool.deallocate(pBucketArray);
    }
    ~StepSet()
    {
        DoFreeNodes(mpBucketArray, mnBucketCount);
        mnElementCount = 0;
        DoFreeBuckets(mpBucketArray, mnBucketCount);
    }
};

// Base-table constructors (hashtable::hashtable with all functor args), one per instantiation.
struct StepSetBig;
struct StepSetSmall;

struct StepSetBig : StepSet {                // 0x33c bytes: 0x34 table + 0x108 buckets + 0x200 nodes
    StepNode* mBuckets[0x108 / 4];
    char mNodes[0x200];
    void Construct(uint32_t n, const HashFn& h, const EqFn& e0, const EqFn& e1, const HashFn& h2, const EqFn& e2,
                   const fixed_hashtable_allocator& a);                  // 0x00ef86c0
    StepSetBig(const HashFn& h = HashFn(), const EqFn& e = EqFn());                                        // 0x00ef9880
    ~StepSetBig() {}
};
struct StepSetSmall : StepSet {              // 0xfc bytes: 0x34 table + 0x48 buckets + 0x80 nodes
    StepNode* mBuckets[0x48 / 4];
    char mNodes[0x80];
    void Construct(uint32_t n, const HashFn& h, const EqFn& e0, const EqFn& e1, const HashFn& h2, const EqFn& e2,
                   const fixed_hashtable_allocator& a);                  // 0x00ef8770
    StepSetSmall(const HashFn& h = HashFn(), const EqFn& e = EqFn());                                      // 0x00ef9950
    ~StepSetSmall() {}
};

// @ 0x00ef9880
StepSetBig::StepSetBig(const HashFn& h, const EqFn& e)
{
    {
        fixed_hashtable_allocator a;
        a.mPool.mpHead = 0;
        a.mPool.init(mNodes, 0x200, 8, 4, 0);
        a.mPool.mpPoolBegin = mNodes;
        a.mPool.mpPoolEnd = mNodes + 0x200;
        a.mPool.mnNodeSize = 8;
        a.mpBucketBuffer = mBuckets;
        uint32_t nBuckets = GetPrevBucketCountOnly(0x41);
        Construct(nBuckets, h, e, e, h, e, a);
    }
    set_max_load_factor(10000.0f);
}

// @ 0x00ef9950
StepSetSmall::StepSetSmall(const HashFn& h, const EqFn& e)
{
    {
        fixed_hashtable_allocator a;
        a.mPool.mpHead = 0;
        a.mPool.init(mNodes, 0x80, 8, 4, 0);
        a.mPool.mpPoolBegin = mNodes;
        a.mPool.mpPoolEnd = mNodes + 0x80;
        a.mPool.mnNodeSize = 8;
        a.mpBucketBuffer = mBuckets;
        uint32_t nBuckets = GetPrevBucketCountOnly(0x11);
        Construct(nBuckets, h, e, e, h, e, a);
    }
    set_max_load_factor(10000.0f);
}

// ---------------------------------------------------------------------------------------------
// Static lesson tables (read-only data)
struct StepInfo {
    int lo;        // first step id of the group
    int hi;        // last step id of the group
    int strId;     // localized title
    int group;     // lesson group index
};
extern StepInfo gStepInfo0[12];       // 0x0148b450
extern StepInfo gStepInfo1[5];        // 0x0148b510
extern uint32_t gGroupTitles0[5];     // 0x0148b560
extern uint32_t gGroupTitles1[5];     // 0x0148b574
extern int gGroupCount[2];            // 0x0148b5d0

extern ResourceKey gKeyPage;          // 0x015ad268
extern ResourceKey gKeyGroup;         // 0x015ad274
extern ResourceKey gKeyStep;          // 0x015ad280
extern wchar_t gEmptyWStr[2];         // 0x01667bac

// ---------------------------------------------------------------------------------------------
// Minimal basic_string<wchar_t> (begin/end/capacity/allocator) and the string-argument record
struct WString {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    int mAllocator;
    WString() : mpBegin(gEmptyWStr), mpEnd(gEmptyWStr), mpCapacity(gEmptyWStr + 1) {}
    void assign(const wchar_t* first, const wchar_t* last);         // 0x00423650
    WString& operator=(const wchar_t* p)
    {
        const wchar_t* pEnd = p;
        while (*pEnd)
            ++pEnd;
        assign(p, p + (pEnd - p));
        return *this;
    }
    ~WString()
    {
        if ((mpCapacity - mpBegin) > 1 && mpBegin)
            delete[] mpBegin;
    }
};
struct StringArg {
    uint32_t mKey;
    WString mValue;
};

class ILocalizer {
public:
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c(); virtual void s20(); virtual void s24();
    virtual void s28(); virtual void s2c();
    virtual void FormatString(cString* str, StringArg* args, int count);   // +0x30
};
class ILocalizerHost {
public:
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
    virtual ILocalizer* GetLocalizer();                                   // +0x20
};
ILocalizerHost* FUN_0067de40();                                           // 0x0067de40

// ---------------------------------------------------------------------------------------------
// Tutorial manager and page
class cScenarioTutorials;
struct cTutorialPage;
struct StepGroup : StepSetSmall {   // 0x14c bytes: the set plus 0x50 bytes of unknown state
    char mUnknown[0x50];
};

class IConfigManager {
public:
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
    virtual void s20(); virtual void s24(); virtual void s28(); virtual void s2c();
    virtual int GetBool(uint32_t key);                                    // +0x30
};
IConfigManager* ConfigManager();                                          // 0x0067dd30 (SP::ConfigManager)

struct TutorialRoot {
    cTutorialPage* GetPage(int index);                                    // 0x00ed4b50
    int GetState();                                                       // 0x00985e40
};
struct TutorialApp {
    char pad[0x14];
    TutorialRoot* mpRoot;                 // +0x14
    char pad18[0xd4 - 0x18];
    cScenarioTutorials* mpTutorials;      // +0xd4
};
extern TutorialApp* gTutorialApp;         // 0x016c7aa4

struct cTutorialPage {
    char pad0[0xc];
    IWindow* mpParentWin;       // +0x0c
    cSPUILayout* mpLayout;      // +0x10
    WindowRef mpWindow;         // +0x14  (list root)
    WindowRef mpWindowD;        // +0x18  (caption)
    WindowRef mpWindowB;        // +0x1c
    WindowRef mpWindowC;        // +0x20
    bool mbBuilt;               // +0x24
    char pad25[3];
    int mMode;                  // +0x28
    int pad2c;
    int mStepCount;             // +0x30
    char pad34[0x44 - 0x34];

    void Rebuild();                         // 0x00ef9000 (refresh the progress labels)
    void BuildList();                       // 0x00ef9290
    void CreateLayout();                    // 0x00ef9d00
    void UpdateGroup(int group);            // 0x00ef8600
    void FUN_00ef7b40();                    // 0x00ef7b40
};
extern void FUN_00ef7a00(cTutorialPage* page);   // 0x00ef7a00 (thiscall on page)
void FUN_00ef8860();                              // 0x00ef8860

// EA::Stopwatch (0x18 bytes) / EA::LimitStopwatch (0x20 bytes)
struct Stopwatch {
    char data[0x18];
    Stopwatch(int units, bool start);                                     // 0x0093a560
};
struct LimitStopwatch : Stopwatch {
    uint64_t mnEndTime;
    void SetTimeLimit(uint64_t limit);                                    // 0x0093a480
    LimitStopwatch(int units, bool start) : Stopwatch(units, start) { SetTimeLimit(0); }
};

// Registered message handler: unregistered on destruction.
struct MessageHandlerRef {
    int mHandler;
    int mArgs[4];
    MessageHandlerRef() : mHandler(0)
    {
        mArgs[0] = 0;
        mArgs[1] = 0;
        mArgs[2] = 0;
        mArgs[3] = 0;
    }
    void Remove()
    {
        if (mHandler) {
            int h = mHandler;
            mHandler = 0;
            RemoveHandler(h, mArgs[0], mArgs[1], mArgs[2], mArgs[3]);
        }
    }
    ~MessageHandlerRef() { Remove(); }
};

// Base classes of the manager (vtable only / vtable + one field).
struct PaintSystem {
    virtual ~PaintSystem() {}                                             // vtbl 0x013eb394
};
struct ContentValidationSummarizer {
    virtual ~ContentValidationSummarizer() {}                             // vtbl 0x013ec458
    int mField8;
    int pad0c;
    ContentValidationSummarizer() : mField8(0) {}
};

class cScenarioTutorials : public PaintSystem, public ContentValidationSummarizer {
public:
    LimitStopwatch mTimer;     // +0x10
    int mCurStep;              // +0x30
    int mCurLesson;            // +0x34
    char pad38[3];
    char mFlag3b, mFlag3c, mFlag3d, mFlag3e, mFlag3f, mFlag40;
    char pad41[3];
    int mField44;
    MessageHandlerRef mHandler;   // +0x48 .. +0x5c
    StepSetBig mSeenSteps;     // +0x5c
    char padBig[0x4a8 - 0x5c - sizeof(StepSetBig)];
    StepGroup mGroups[2];      // +0x4a8, +0x5f4

    cScenarioTutorials();                                                 // 0x00ef9d90
    virtual ~cScenarioTutorials();                                        // 0x00ef9180
    int GetCompletedCount(int mode);                                      // 0x00ef8940
    void SavePrefs();                                                     // 0x00ef8dc0
    void OnStepDone(int step);                                            // 0x00ef9af0
};

// ---------------------------------------------------------------------------------------------
// @ 0x00ef9830 -- toggle: if on, tear down the attached window and clear flag.
struct Stub {
    void* FUN_00ef9290();
};

// @ 0x00ef9830
void FUN_00ef9830(void* param_1, int param_2, char param_3) {
    if (param_3 != 0) {
        ((Stub*)param_1)->FUN_00ef9290();
        return;
    }
    void* esi = param_1;
    if (*(char*)((char*)esi + 0x24) == 0)
        return;
    void* o = *(void**)((char*)esi + 0x14);
    if (o) {
        void* vt = *(void**)o;
        ((void(__thiscall*)(void*, void*)) * ((void**)vt + 0x42))(o, esi);
        o = *(void**)((char*)esi + 0x14);
        if (o) {
            *(void**)((char*)esi + 0x14) = 0;
            vt = *(void**)o;
            ((void(__thiscall*)(void*)) * ((void**)vt + 1))(o);
        }
    }
    *(char*)((char*)esi + 0x24) = 0;
}


// @ 0x00ef9d90
cScenarioTutorials::cScenarioTutorials()
    : mTimer(5, false),
      mCurStep(-1), mCurLesson(-1),
      mFlag3b(0), mFlag3c(0), mFlag3d(0), mFlag3e(0), mFlag3f(0), mFlag40(0),
      mField44(-1)
{
}

// @ 0x00ef9180
cScenarioTutorials::~cScenarioTutorials()
{
}

// @ 0x00ef8dc0
void cScenarioTutorials::SavePrefs()
{
    mHandler.Remove();
    IPropertyList* props = gAppPreferences;
    int a = GetCompletedCount(0);
    Variant v1;
    v1 = a;
    props->SetProperty(0x7abf095, &v1);
    int b = GetCompletedCount(1);
    Variant v2;
    v2 = b;
    props->SetProperty(0x7abf09d, &v2);
    props = gAppPreferences;
    SaveResource(props, GetSaveArea(0x11ac192), 0);
}

// @ 0x00ef8ed0
// Show/hide the tutorial pages when the tutorial mode is toggled.
void __stdcall FUN_00ef8ed0(bool enable)
{
    if (enable) {
        TutorialRoot* root = gTutorialApp->mpRoot;
        int state = root->GetState();
        if (state == 0) {
            cTutorialPage* page = gTutorialApp->mpRoot->GetPage(0);
            if (ConfigManager()->GetBool(0x4ea96cb) && page->mpWindow)
                page->mpWindow->SetFlag(1, true);
            cTutorialPage* page1 = gTutorialApp->mpRoot->GetPage(1);
            page1->FUN_00ef7b40();
            if (page1->mpWindow)
                page1->mpWindow->SetFlag(1, false);
        } else if (state == 2) {
            cTutorialPage* page = gTutorialApp->mpRoot->GetPage(0);
            page->FUN_00ef7b40();
            if (page->mpWindow)
                page->mpWindow->SetFlag(1, false);
            cTutorialPage* page1 = gTutorialApp->mpRoot->GetPage(1);
            if (ConfigManager()->GetBool(0x4ea96cb) && page1->mpWindow)
                page1->mpWindow->SetFlag(1, true);
        }
    } else {
        FUN_00ef8860();
        cTutorialPage* page = gTutorialApp->mpRoot->GetPage(0);
        page->FUN_00ef7b40();
        if (page->mpWindow)
            page->mpWindow->SetFlag(1, false);
        cTutorialPage* page1 = gTutorialApp->mpRoot->GetPage(1);
        page1->FUN_00ef7b40();
        if (page1->mpWindow)
            page1->mpWindow->SetFlag(1, false);
    }
}

// @ 0x00ef9000
// Refresh the "N of M" progress caption.
void cTutorialPage::Rebuild()
{
    wchar_t completed[64];
    wchar_t total[64];
    SetNumberString(gTutorialApp->mpTutorials->GetCompletedCount(mMode), completed, 64);
    SetNumberString(mStepCount, total, 64);
    StringArg args[2];
    args[0].mKey = 0x6c7cf9;
    args[0].mValue = completed;
    args[1].mKey = 0xac24c978;
    args[1].mValue = total;
    cString text(0xc49c0c72, 0x7735bdc, 0);
    FUN_0067de40()->GetLocalizer()->FormatString(&text, args, 2);
    mpWindowD->SetCaption(text.c_str());
}

// @ 0x00ef9af0
// A tutorial step was completed: record it, and if it finishes a whole group, mark the group done and refresh.
void cScenarioTutorials::OnStepDone(int step)
{
    int stepKey = step;
    mSeenSteps.DoInsertValue(stepKey, true_type());
    cTutorialPage* page = gTutorialApp->mpRoot->GetPage(mCurLesson);
    int count = 0;
    if (mCurLesson == 0)
        count = 12;
    else if (mCurLesson == 1)
        count = 5;
    for (int i = 0; i < count; ++i) {
        const StepInfo* info = 0;
        if (mCurLesson == 0)
            info = &gStepInfo0[i];
        else if (mCurLesson == 1)
            info = &gStepInfo1[i];
        int lo = info->lo;
        int hi = info->hi;
        if (step < lo || step > hi)
            continue;
        for (int k = lo; k <= hi; ++k) {
            if (mSeenSteps.find(k) == mSeenSteps.end())
                return;
        }
        int group = i;
        mGroups[mCurLesson].DoInsertValue(group, true_type());
        IWindow* row = page->mpLayout->FindWindowByID(0x3e8 + i, true);
        IWindow* mark = row ? row->GetComponent(0x8ed27e7a) : 0;
        mark->SetStateFlag(4, true);
        page->Rebuild();
        page->UpdateGroup(i);
        if (i + 1 < page->mStepCount)
            page->mpWindow->GetChildByID(i + 1 + 0x64, true)->SetFlag(1, false);
        page->mpWindowB->SetFlag(1, false);
        FUN_00ef7a00(page);
        mCurStep = -1;
        mCurLesson = -1;
        mField44 = -1;
        mFlag3b = 0;
        mFlag3d = 0;
        mFlag3e = 0;
        mFlag3f = 0;
        mFlag40 = 0;
        *(uint16_t*)&pad38[0] = 0;
        pad38[2] = 0;
        return;
    }
}

// @ 0x00ef9d00
void cTutorialPage::CreateLayout()
{
    cSPUILayout* layout = new ("UI", 0, 0, 0, 0) cSPUILayout();
    cSPUILayout* old = mpLayout;
    if (layout != old) {
        if (layout)
            layout->AddRef();
        mpLayout = layout;
        if (old)
            old->Release();
    }
    mpLayout->Init(gKeyPage, false, 0x5b598fa);
    mpLayout->SetParentWin(mpParentWin, true, 0x5b598fa);
    mpLayout->SetReloadCallback(FUN_00ef9830, this);
    BuildList();
}

// @ 0x00ef9290
// Build the scrolling list: one block per lesson group, each holding one row per step of that group.
void cTutorialPage::BuildList()
{
    if (mbBuilt)
        return;
    mpWindow = mpLayout->FindWindowByID(0x771f0a0, true);
    mpWindow->AddWinProc(this);
    mpWindowB = mpLayout->FindWindowByID(0x7a2a2d6, true);
    mpWindowB->SetFlag(1, false);
    IWindow* w = mpLayout->FindWindowByID(0x7732678, true);
    mpWindowC = w ? w->GetComponent(0x8ed27e7a) : 0;
    mpWindowD = mpLayout->FindWindowByID(0x771f2a8, true);
    Rebuild();

    IWindow* container = mpLayout->FindWindowByID(0x771f2c0, true);
    const Rect* cr = container->GetArea();
    float contW = cr->right - cr->left;
    float contH = cr->bottom - cr->top;
    float yAcc = 0.0f;
    for (int i = 0; i < gGroupCount[mMode]; ++i) {
        cSPUILayout groupLayout;
        groupLayout.Init(gKeyGroup, false, 0x5b598fa);
        WindowRef groupWin = {0};
        groupWin = groupLayout.FindWindowByID(0x7b54408, true);
        IWindow* stepList = groupLayout.FindWindowByID(0x7b54370, true);
        IWindow* titleWin = groupLayout.FindWindowByID(0x7a6cfd8, true);
        uint32_t titleId = 0;
        if (mMode == 0)
            titleId = gGroupTitles0[i];
        else if (mMode == 1)
            titleId = gGroupTitles1[i];
        cString title(0xc49c0c72, titleId, 0);
        titleWin->SetCaption(title.c_str());
        groupLayout.Shutdown(true);
        container->AddWindow(groupWin);
        {
            const Rect* r = groupWin->GetArea();
            groupWin->SetSize(contW, r->bottom - r->top);
        }
        const Rect* sr = stepList->GetArea();
        float subW = sr->right - sr->left;
        float subH = sr->bottom - sr->top;
        float yInner = 0.0f;
        for (int j = 0; j < mStepCount; ++j) {
            if (mMode == 0) {
                if (gStepInfo0[j].group != i)
                    continue;
            } else if (mMode == 1) {
                if (gStepInfo1[j].group != i)
                    continue;
            }
            cSPUILayout stepLayout;
            stepLayout.Init(gKeyStep, false, 0x5b598fa);
            WindowRef stepWin = {0};
            stepWin = stepLayout.FindWindowByID(0x7731950, true);
            stepLayout.FindWindowByID(0x7732df0, true)->SetControlID(j + 1);
            stepLayout.FindWindowByID(0x7aa9b70, true)->SetControlID(j + 0x64);
            stepLayout.FindWindowByID(0x7757900, true)->SetControlID(j + 0x3e8);
            IWindow* captionWin = stepLayout.FindWindowByID(0x7733e00, true);
            uint32_t stepId = 0;
            if (mMode == 0)
                stepId = gStepInfo0[j].strId;
            else if (mMode == 1)
                stepId = gStepInfo1[j].strId;
            cString stepText(0xc49c0c72, stepId, 0);
            captionWin->SetCaption(stepText.c_str());
            stepLayout.Shutdown(true);
            stepList->AddWindow(stepWin);
            const Rect* r = stepWin->GetArea();
            Rect rc;
            rc.left = 0.0f;
            rc.top = yInner;
            rc.right = subW;
            rc.bottom = (r->bottom - r->top) + yInner;
            stepWin->SetArea(&rc);
            yInner = rc.bottom;
        }
        const Rect* gr = groupWin->GetArea();
        Rect rc2;
        rc2.left = 0.0f;
        rc2.top = yAcc;
        rc2.right = contW;
        rc2.bottom = (((gr->bottom - gr->top) - subH) + yInner) + yAcc;
        groupWin->SetArea(&rc2);
        yAcc = rc2.bottom;
    }
    const Rect* lr = mpWindow->GetArea();
    float newH = ((lr->bottom - lr->top) - contH) + yAcc;
    mpWindow->SetSize(lr->right - lr->left, newH);
    mbBuilt = true;
}
