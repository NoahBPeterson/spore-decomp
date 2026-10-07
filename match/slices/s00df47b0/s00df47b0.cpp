// Slice s00df47b0 -- cGalaxyGameEntryUIStateMachine::SetupForGame (0x00df47b0, 2944 bytes).
//
// Points the galaxy game-entry UI at a cGameInfo and resets it: clears the game's name, and when a
// game is given, rebuilds the new-game flow order (the panel IDs listed in the "new game flow
// layout" property, resolved through a local name -> panel-ID hash_map), resets the game's keys and
// star, and centers a dialog in the client area. Then it resets the state machine, restarts the
// zoom stopwatch and refreshes several windows (including the four level buttons).
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc: the string/hash_map locals get no EH frame).
// The retail class is larger than the 2008 PDB layout (mpGameInfo at +0x628), so fields are named
// by role at their retail offsets.
#include "types.h"
#include <new>
#include <string.h>

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8

extern "C" unsigned __int64 __rdtsc(void);
#pragma intrinsic(__rdtsc)
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(int64_t* pCount);

// ---- EASTL (the parts this function inlines; out-of-line members are declared only) ----
namespace eastl {

struct allocator {
    allocator() {}
};

template <bool B> struct integral_constant { };
typedef integral_constant<true> true_type;

template <typename T> struct basic_string {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    allocator mAllocator;

    basic_string(const T* p) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(p); }
    ~basic_string() { DeallocateSelf(); }

    void RangeInitialize(const T* pBegin);   // 0x00579a90
    void DoFree(T* p, size_t n)
    {
        if (p)
            delete[] (char*)p;
    }
    void DeallocateSelf()
    {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin, mpCapacity - mpBegin);
    }
    void clear()
    {
        if (mpBegin != mpEnd) {
            *mpBegin = 0;
            mpEnd = mpBegin;
        }
    }
};
typedef basic_string<wchar_t> string16;

template <typename T> struct vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    allocator mAllocator;

    void DoInsertValue(T* position, const T& value);   // 0x00b96600
    T* erase(T* first, T* last)
    {
        memcpy(first, last, (size_t)((char*)mpEnd - (char*)last));
        mpEnd -= (last - first);
        return first;
    }
    void clear() { erase(mpBegin, mpEnd); }
    void push_back(const T& value)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
};

template <typename T1, typename T2> struct pair {
    T1 first;
    T2 second;
    pair(const T1& a, const T2& b);   // 0x008d6580 for <const string16, uint32_t>
};

// hash_map<string16, uint32_t>
struct hash_node {
    pair<const string16, uint32_t> mValue;
    hash_node* mpNext;
};

extern void* gpEmptyBucketArray[2];   // 0x0154df28

struct hash_iterator {
    hash_node* mpNode;
    hash_node** mpBucket;
    hash_iterator(hash_node** pBucket) : mpNode(*pBucket), mpBucket(pBucket) {}
    hash_iterator(const hash_iterator& x) : mpNode(x.mpNode), mpBucket(x.mpBucket) {}
    pair<const string16, uint32_t>* operator->() const { return &mpNode->mValue; }
    bool operator!=(const hash_iterator& x) const { return mpNode != x.mpNode; }
};

struct prime_rehash_policy {
    float mfMaxLoadFactor;
    float mfGrowthFactor;
    uint32_t mnNextResize;
    prime_rehash_policy(float fMaxLoadFactor = 1.0f)
        : mfMaxLoadFactor(fMaxLoadFactor), mfGrowthFactor(2.0f), mnNextResize(0) {}
};

struct hash_map_string16_uint {
    typedef pair<const string16, uint32_t> value_type;
    struct insert_return_type {
        hash_iterator first;
        bool second;
    };

    uint32_t mEmptyBases;   // the empty hash/equal functor bases occupy 4 bytes under MSVC
    hash_node** mpBucketArray;
    uint32_t mnBucketCount;
    uint32_t mnElementCount;
    prime_rehash_policy mRehashPolicy;
    allocator mAllocator;

    hash_map_string16_uint() : mnBucketCount(0), mnElementCount(0), mRehashPolicy() { reset(); }
    ~hash_map_string16_uint()
    {
        clear();
        DoFreeBuckets(mpBucketArray, mnBucketCount);
    }
    void reset()
    {
        mnElementCount = 0;
        mnBucketCount = 1;
        mpBucketArray = (hash_node**)&gpEmptyBucketArray[0];
        mRehashPolicy.mnNextResize = 0;
    }
    void DoFreeNodes(hash_node** pBucketArray, uint32_t n);   // 0x007c7050
    void DoFreeBuckets(hash_node** pBucketArray, uint32_t n)
    {
        if (n > 1)
            delete[] (char*)pBucketArray;
    }
    void clear()
    {
        DoFreeNodes(mpBucketArray, mnBucketCount);
        mnElementCount = 0;
    }
    hash_iterator end() { return hash_iterator(mpBucketArray + mnBucketCount); }
    hash_iterator find(const string16& k);                                     // 0x00def5f0
    insert_return_type DoInsertValue(const value_type& value, true_type);     // 0x00df0ad0
    insert_return_type insert(const value_type& value) { return DoInsertValue(value, true_type()); }
};

}  // namespace eastl

using eastl::string16;

// ---- game types ----
struct ResourceKey {
    uint32_t instanceID, typeID, groupID;
    ResourceKey(uint32_t i, uint32_t t, uint32_t g) : instanceID(i), typeID(t), groupID(g) {}
};

struct cRefCounted {
    virtual int AddRef();
    virtual int Release();
};

template <typename T> struct intrusive_ptr {
    T* mpObject;
    intrusive_ptr() : mpObject(0) {}
    ~intrusive_ptr()
    {
        if (mpObject)
            mpObject->Release();
    }
    intrusive_ptr& operator=(T* p)
    {
        if (p != mpObject) {
            T* const pTemp = mpObject;
            if (p)
                p->AddRef();
            mpObject = p;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
    T* get() const { return mpObject; }
};

struct cPropList : cRefCounted { };
typedef intrusive_ptr<cPropList> PropListPtr;

struct cPropManager {
    PV8 PV2 PV
    virtual bool GetPropertyListImpl(uint32_t instanceID, uint32_t groupID, PropListPtr& dst);   // +0x2c
    bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropListPtr& dst)
    {
        dst = 0;
        return GetPropertyListImpl(instanceID, groupID, dst);
    }
};
cPropManager* PropertyManager();                                                                  // 0x0067de30
bool GetPropertyAsString16Array(const cPropList* list, uint32_t id, int& count, string16*& dst);  // 0x006a0bc0
uint32_t FNV1_String16(const wchar_t* s, uint32_t seed, bool lowercase);                         // 0x00932f30

struct Rect {
    float left, top, right, bottom;
    Rect(const Rect& r) : left(r.left), top(r.top), right(r.right), bottom(r.bottom) {}
};
struct IntRect { int left, top, right, bottom; };

struct IWindow {
    PV2 PV
    virtual IWindow* FindWindowByID(uint32_t id);   // +0x0c
    PV8 PV2
    virtual const Rect& GetArea();                  // +0x38
    PV8 PV2
    virtual void SetLocation(float x, float y);     // +0x64
    PV4 PV
    virtual void SetFlag(int flag, bool value);     // +0x7c
};

struct cSPUILayout {
    uint32_t pad[3];
    IWindow* FindWindowByID(uint32_t id, bool recursive);   // 0x008105b0
};

struct cAppWindow {
    void GetClientRect(IntRect* rect);   // 0x007c4010
};
struct cApp {
    PV16 PV4 PV2
    virtual cAppWindow* GetMainWindow();   // +0x58
};
cApp* App();   // 0x0067dd10

struct cAppSystem {
    PV16 PV4 PV
    virtual bool IsFeatureEnabled();   // +0x54
};
cAppSystem* AppSystem();   // 0x0067dd00

struct cStarRecord {
    uint32_t pad[0x16];
    uint32_t m58;
    uint32_t Get58();                  // 0x00989360 (returns m58)
    void Reset(int flags);             // 0x00bbaa80
};
struct cStarManager {
    void SetActiveStar(cStarRecord* star);   // 0x00bb7510
};
cStarManager* StarManager();   // 0x00b3d2a0

struct cGameInfo {
    uint32_t pad00[8];
    string16 mName;          // +0x20
    uint32_t pad30[7];
    ResourceKey mKey4C;      // +0x4c
    uint32_t pad58[3];
    ResourceKey mKey64;      // +0x64
    ResourceKey mKey70;      // +0x70
    uint32_t mStarID;        // +0x7c
    uint32_t pad80[5];
    ResourceKey mKey94;      // +0x94
    int mA0;                 // +0xa0
    int mA4;                 // +0xa4
    int mA8;                 // +0xa8
    uint32_t padac;
    int mB0;                 // +0xb0
    cStarRecord* GetStarRecord();   // 0x00de4610
};

const ResourceKey& GetKeyForID(uint32_t id);   // 0x00b6f0c0

struct cGGEGlobal {
    uint8_t pad[0x1f5];
    bool mbAllLevelsUnlocked;              // +0x1f5
    bool IsLevelUnlocked(uint32_t level);  // 0x00de5cb0
};
extern cGGEGlobal* gpGGEGlobal;   // 0x016a1344

extern uint32_t gNewGameFlowPropListID;   // 0x015a2df8
extern const wchar_t* sNewGameFlowLayout; // 0x016a0cf8
extern bool gbFlag16a0ee8;                // 0x016a0ee8
extern bool gbFlag16a0d60;                // 0x016a0d60
extern const uint32_t kLevelIDs[4];       // 0x0147e800
extern const uint32_t kLevelButtonIDs[4]; // 0x0147e810

struct Stopwatch {
    uint64_t mnStartTime;      // +0x00
    uint64_t mnTotalElapsed;   // +0x08
    int mnUnits;               // +0x10 (1 = CPU cycles)
    float mfCyclesToUnits;     // +0x14
    uint64_t GetStopwatchCycle()
    {
        if (mnUnits == 1)
            return __rdtsc();
        int64_t t;
        QueryPerformanceCounter(&t);
        return (uint64_t)t;
    }
    void Restart()
    {
        mnStartTime = GetStopwatchCycle();
        mnTotalElapsed = 0;
    }
};

struct cGalaxyGameEntryUIStateMachine {
    uint32_t pad00[0xa];
    cSPUILayout mLayout;                       // +0x28
    uint32_t pad34[0xa];
    eastl::vector<uint32_t> mNewGameFlow;      // +0x5c
    uint32_t pad6c;
    bool mb70;                                 // +0x70
    uint8_t pad71[0x4a3];
    ResourceKey mKey514;                       // +0x514
    uint32_t pad520[0x34];
    Stopwatch mZoomTimer;                      // +0x5f0
    uint32_t pad608[8];
    cGameInfo* mpGameInfo;                     // +0x628

    void ResetGameUI();                                  // 0x00dec460
    void MakeRandomName();                               // 0x00defc80
    void SetupPanelA(uint32_t id);                       // 0x00df2920
    void SetupPanelB(uint32_t id);                       // 0x00df2770
    void SetCurrentState(int state);                     // 0x00df0670
    void RefreshUI();                                    // 0x00ded7d0
    void FillStarterWorldCombo(IWindow* combo);          // 0x00df1ba0
    void SelectStarterWorld(IWindow* combo, uint32_t v); // 0x00decf20
    void UpdateNavigationControls();                     // 0x00def8c0

    void SetupForGame(cGameInfo* gameInfo);
};

// @ 0x00df47b0
void cGalaxyGameEntryUIStateMachine::SetupForGame(cGameInfo* gameInfo)
{
    mpGameInfo = gameInfo;
    gameInfo->mB0 = 0;
    mb70 = false;
    mpGameInfo->mName.clear();
    ResetGameUI();

    if (mpGameInfo) {
        IWindow* window = mLayout.FindWindowByID(0x5944089, true);
        if (window)
            window->SetFlag(1, true);
        MakeRandomName();

        PropListPtr propList;
        cPropManager* propManager = PropertyManager();
        propList = 0;
        if (propManager->GetPropertyListImpl(gNewGameFlowPropListID, 0, propList)) {
            mNewGameFlow.clear();

            eastl::hash_map_string16_uint panels;
            typedef eastl::hash_map_string16_uint::value_type value_type;
            panels.insert(value_type(string16(L"level"), 1));
            panels.insert(value_type(string16(L"diet"), 2));
            panels.insert(value_type(string16(L"creature"), 3));
            panels.insert(value_type(string16(L"name"), 4));
            panels.insert(value_type(string16(L"difficulty"), 5));
            panels.insert(value_type(string16(L"theme"), 6));
            panels.insert(value_type(string16(L"specialty"), 7));
            panels.insert(value_type(string16(L"assets"), 8));
            panels.insert(value_type(string16(L"assets and creature"), 9));
            panels.insert(value_type(string16(L"captain name"), 10));
            panels.insert(value_type(string16(L"start"), 11));

            int count;
            string16* names;
            uint32_t layoutID = FNV1_String16(sNewGameFlowLayout, 0x811c9dc5, true);
            if (GetPropertyAsString16Array(propList.get(), layoutID, count, names)) {
                for (int i = 0; i < count; i++) {
                    eastl::hash_iterator it = panels.find(names[i]);
                    if (it != panels.end())
                        mNewGameFlow.push_back(it->second);
                }
            }
        }

        SetupPanelA(0x6149007);
        SetupPanelB(0x614c680);
        StarManager()->SetActiveStar(mpGameInfo->GetStarRecord());
        mpGameInfo->GetStarRecord()->Reset(0);
        mpGameInfo->mKey70 = ResourceKey(0, 0, 0);
        mpGameInfo->mKey4C = mpGameInfo->mKey70;
        mpGameInfo->mKey64 = mpGameInfo->mKey4C;
        mKey514 = mpGameInfo->mKey64;
        mpGameInfo->mA8 = 6;
        mpGameInfo->mA4 = 6;
        mpGameInfo->mA0 = 0;

        IntRect client;
        App()->GetMainWindow()->GetClientRect(&client);
        float cx = (float)((client.right - client.left) / 2);
        float cy = (float)((client.bottom - client.top) / 2);
        window = mLayout.FindWindowByID(0x5384881, true);
        if (window) {
            Rect area = window->GetArea();
            window->SetLocation(cx - (area.right - area.left) * 0.5f, cy - (area.bottom - area.top) * 0.5f);
        }
        mpGameInfo->mKey94 = GetKeyForID(0x53dbcf5);
    }

    SetCurrentState(0);
    SetCurrentState(0xc);
    mpGameInfo = gameInfo;
    RefreshUI();
    mZoomTimer.Restart();
    mpGameInfo->mB0 = 0;

    IWindow* window = mLayout.FindWindowByID(0x657ce07, true);
    if (window)
        window->SetFlag(1, gbFlag16a0ee8);
    window = mLayout.FindWindowByID(0x5b744bc, true);
    if (window)
        window->SetFlag(1, !gbFlag16a0ee8);
    window = mLayout.FindWindowByID(0x4ec1b8d8, true);
    if (window) {
        if (!AppSystem()->IsFeatureEnabled())
            window->SetFlag(1, false);
        else
            window->SetFlag(1, gbFlag16a0d60);
    }
    window = mLayout.FindWindowByID(0x588ab05, true);
    if (window) {
        IWindow* combo = window->FindWindowByID(0x2f5528d9);
        if (combo) {
            FillStarterWorldCombo(combo);
            if (mpGameInfo && mpGameInfo->GetStarRecord())
                SelectStarterWorld(combo, mpGameInfo->GetStarRecord()->Get58());
        }
    }

    bool allUnlocked = gpGGEGlobal->mbAllLevelsUnlocked || AppSystem()->IsFeatureEnabled();
    for (uint32_t i = 0; i < 4; i++) {
        window = mLayout.FindWindowByID(kLevelButtonIDs[i], true);
        if (window)
            window->SetFlag(2, allUnlocked || gpGGEGlobal->IsLevelUnlocked(kLevelIDs[i]));
    }
    UpdateNavigationControls();
}
