// Slice s00f16580 -- adventure (scenario) completion: player statistics, achievements and
// Pollinator telemetry (0x00f16580, 2628 bytes).
//
// cScenarioResultsRecorder::RecordResults(bool finished)   (thiscall, ret 4; class and method
// names Claude-coined; the owner keeps the player's property list at +0xb8, the play mode at
// +0x10 and the player/collectables holder at +0x24).
//
//   * optionally (finished && play mode state 5) records the adventure in the player list;
//   * converts the earned points (+0xc8) to a level (FindFirstGE), stores points and level in
//     the property list and awards the "max level" achievement when the level reaches 10;
//   * adds every play-summary counter to the player's lifetime totals (AddToIntProperty) and
//     collects the new totals in a fixed_vector<int64_t, 32>;
//   * drops the holder's pending object, refreshes the collectables, saves them and the property
//     list, and sends the totals, the adventure name and the unlocked-item list to the Pollinator.
//
// Collaborators are declared from their own slices: AddToIntProperty / SaveCollectableItems /
// SaveEditorPropertyList (s005beaf0), cPollinator (s0060d860), EA::Variant (s005beaf0),
// cScenarioPlaySummary layout (ModAPI cScenarioPlayMode.h), cCollectableItems::mUnlockedItems
// at +0x6d80 (ModAPI cCollectableItems.h).
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (same module as s00f1c690; no /EHsc).
#include "types.h"

typedef long long int64_t;

extern "C" void operator_delete_array(void* p);       // 0x00f47380 (operator delete[])

inline void* operator new(unsigned int, void* p) { return p; }

namespace eastl {

struct allocator { allocator() {} };
struct bidirectional_iterator_tag { bidirectional_iterator_tag() {} };

// eastl::basic_string<wchar_t, eastl::allocator>
extern wchar_t gEmptyString16[2];                     // 0x01667bac
struct string16
{
    wchar_t*  mpBegin;
    wchar_t*  mpEnd;
    wchar_t*  mpCapacity;
    allocator mAllocator;

    string16()
    {
        mpBegin = gEmptyString16;
        mpEnd = gEmptyString16;
        mpCapacity = gEmptyString16 + 1;
    }
    ~string16() { DeallocateSelf(); }
    void DeallocateSelf()
    {
        if ((mpCapacity - mpBegin) > 1 && mpBegin)
            operator_delete_array(mpBegin);
    }
};

template <typename T>
struct ListNode
{
    ListNode* mpNext;
    ListNode* mpPrev;
    T         mValue;
};

template <typename T>
struct list_iterator
{
    ListNode<T>* mpNode;
    list_iterator(ListNode<T>* p) : mpNode(p) {}
};

template <typename T>
struct list
{
    ListNode<T>* mpNext;    // anchor
    ListNode<T>* mpPrev;
    unsigned int mSize;
    list_iterator<T> begin() { return list_iterator<T>(mpNext); }
    list_iterator<T> end() { return list_iterator<T>((ListNode<T>*)this); }
};

template <unsigned int size, unsigned int alignment>
struct aligned_buffer { __declspec(align(8)) char buffer[size]; };

// eastl::fixed_vector<int64_t, 32, true>
struct fixed_vector_allocator
{
    allocator mOverflowAllocator;
    void*     mpPoolBegin;
};

struct fixed_vector_int64_32
{
    int64_t*               mpBegin;
    int64_t*               mpEnd;
    int64_t*               mpCapacity;
    fixed_vector_allocator mAllocator;
    aligned_buffer<32 * sizeof(int64_t), 8> mBuffer;

    fixed_vector_int64_32()
    {
        mpBegin = (int64_t*)mBuffer.buffer;
        mpEnd = mpBegin;
        mpCapacity = mpBegin + 32;
        mAllocator.mpPoolBegin = mpBegin;
    }
    ~fixed_vector_int64_32()
    {
        if (mpBegin && mpBegin != mAllocator.mpPoolBegin)
            operator_delete_array(mpBegin);
    }

    int64_t* data() { return mpBegin; }
    unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }

    void push_back(const int64_t& value)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) int64_t(value);
        else
            DoInsertValue(mpEnd, value);
    }

    template <typename T>
    void assign(list_iterator<T> first, list_iterator<T> last)
    {
        DoAssignFromIterator(first, last, bidirectional_iterator_tag());
    }

    void DoInsertValue(int64_t* position, const int64_t& value);   // 0x00f14140
    void DoAssignFromIterator(list_iterator<int64_t> first, list_iterator<int64_t> last,
                              bidirectional_iterator_tag);        // 0x00f16280
};

template <typename T>
struct intrusive_ptr
{
    T* mpObject;
    intrusive_ptr() : mpObject(0) {}
    ~intrusive_ptr()
    {
        if (mpObject)
            mpObject->Release();
    }
    T* get() const { return mpObject; }
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
};

}  // namespace eastl

namespace EA {
// EA::Variant (size 0x14)
struct Variant
{
    uint32_t       mData[4];
    unsigned short mFlags;   // +0x10
    unsigned short mTypeId;  // +0x12
    Variant() : mFlags(0), mTypeId(0) {}
    ~Variant()
    {
        if (mFlags & 4)
            Destruct(0);
    }
    void Destruct(int);                                                   // EA::Variant::Destruct 0x0093db80
    Variant& operator=(const int& v);                                     // EA::Variant::operator=<int> 0x00422eb0
    void Set(int type, int flags, const void* data, int elemSize, int count);  // EA::Variant::Set 0x0093dd80
};
}  // namespace EA

struct ResourceKey { uint32_t mInstance, mType, mGroup; };

struct Property
{
    uint32_t       pad_00[0x12 / 4];
    unsigned short pad_10;
    unsigned short mType;    // +0x12
    int* GetInt();           // Property::GetInt 0x0041e990
};

namespace App {
class PropertyList
{
public:
    virtual void AddRef();
    virtual void Release();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void SetProperty(uint32_t id, const EA::Variant& value);   // +0x14
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual bool GetProperty(uint32_t id, Property*& result);         // +0x24
};

class IMessageManager
{
public:
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void PostMSG(uint32_t messageID, void* pMessage, void* pListener);   // +0x14
};
IMessageManager* MessageServer();                                   // SP::MessageServer 0x0067dcc0
}  // namespace App

namespace SP {
namespace Achievements {
class Controller
{
public:
    void AwardAchievement(uint32_t id);                             // 0x00676710
};
}
Achievements::Controller* AchievementsController();                // 0x00675250

struct cPollinator
{
    void UpdateProperty2(uint32_t id, const ResourceKey* key, EA::Variant* v);                 // 0x0060d920
    void UpdatePropertyInt(uint32_t id, const ResourceKey* key, uint32_t a, uint32_t b);       // 0x0060e600
};
cPollinator* GetPollinator();                                       // 0x0067cb30
}  // namespace SP

namespace Simulator {
struct cScenarioPlaySummary
{
    int   mNumCreaturesKilled;        // +0x00
    int   mNumBuildingsDestroyed;     // +0x04
    int   mNumVehiclesDestroyed;      // +0x08
    int   mNumCastMembersDefended;    // +0x0c
    int   mNumCreaturesBefriended;    // +0x10
    int   mNumObjectsCollected;       // +0x14
    int   field_18;                   // +0x18
    int   mNumGoalsCompleted;         // +0x1c
    int   mNumDeaths;                 // +0x20
    int   mNumPosseMembersLost;       // +0x24
    int   mAmountDamageDealt;         // +0x28
    int   mNumTimesUsedJetPack;       // +0x2c
    int   mNumTimesUsedSprint;        // +0x30
    int   mNumBarrelsDestroyed;       // +0x34
    int   mNumCastMembersTalkedTo;    // +0x38
    float mAmountHealthRegained;      // +0x3c
    float mAmountDamageReceived;      // +0x40
    float mAmountEnergyUsed;          // +0x44
};

struct cScenarioPlayMode
{
    uint32_t pad_000[0x90 / 4];
    int      mCurrentPlayModeState;   // +0x90

    cScenarioPlaySummary* GetSummary();   // 0x008dc790 (lea eax,[ecx+0xc]; COMDAT-folded)
    int GetElapsedTimeMS();               // 0x00f19190 (name guessed)
};

struct cCollectableItems
{
    virtual void v00();
    virtual void Release();               // +0x04 (as released by the conditional temporary)
    void AddRef();
    void Refresh(int flags);                          // 0x005970d0 (name guessed)
    eastl::list<int64_t>& GetUnlockedItems();          // 0x005939a0 (lea eax,[ecx+0x6d80])
};

struct cPlayerData                        // what the holder points to at +0x14 (name guessed)
{
    uint32_t pad_000[0x10 / 4];
    eastl::intrusive_ptr<cCollectableItems> mpCollectableItems;  // +0x10
};

struct cPendingObject
{
    virtual void v00();
    virtual void v04();
    virtual void Release();               // +0x08
    void AddRef();
};

struct cCollectablesHolder                // the object at owner+0x24 (name guessed)
{
    uint32_t     pad_000[0x14 / 4];
    cPlayerData* mpPlayerData;                                     // +0x14
    uint32_t     pad_018[(0x20 - 0x18) / 4];
    eastl::intrusive_ptr<cPendingObject> mpPending;                // +0x20
    void Update();                        // 0x00f12340 (name guessed)
};
}  // namespace Simulator

struct cScenarioData                      // g_ScenarioManager->+0x74 (name guessed)
{
    uint32_t pad_000[0x10 / 4];
    struct cScenarioResource* mpResource;      // +0x10
    const ResourceKey* GetKey();               // 0x00f3bcb0 (return &mpResource->+0x130)
};
struct cScenarioResource { uint32_t pad_000[2]; uint32_t mHeader[1]; };   // +0x08 passed below
struct cScenarioManager { uint32_t pad_000[0x74 / 4]; cScenarioData* mpData; };
extern cScenarioManager* g_ScenarioManager;   // 0x016c7aa4

void RecordPlayedAdventure(App::PropertyList* list, const uint32_t* header);   // 0x00eef330 (name guessed)
int  FindFirstGE(int points);                                                  // 0x00eec540
int  AddToIntProperty(App::PropertyList* list, uint32_t id, int delta);        // 0x005bf470
void SaveCollectableItems(App::PropertyList* list, Simulator::cCollectableItems* items);    // 0x005bf610
bool SaveEditorPropertyList(const ResourceKey* key, App::PropertyList* list, int flags, void* db);  // 0x005bf120
void GetAdventureName(const ResourceKey* key, eastl::string16* out);           // 0x00eed920

// int property value, or 0 when it is missing or not an int
inline int GetIntProperty(App::PropertyList* list, uint32_t id)
{
    int value = 0;
    Property* prop;
    if (list && list->GetProperty(id, prop) && prop->mType == 9)
        value = *prop->GetInt();
    return value;
}

class cScenarioResultsRecorder
{
public:
    uint32_t                        pad_000[0x10 / 4];
    Simulator::cScenarioPlayMode*   mpPlayMode;    // +0x10
    uint32_t                        pad_014[(0x24 - 0x14) / 4];
    Simulator::cCollectablesHolder* mpHolder;      // +0x24
    uint32_t                        pad_028[(0xb8 - 0x28) / 4];
    App::PropertyList*              mpPlayerProps; // +0xb8
    uint32_t                        pad_0bc[(0xc8 - 0xbc) / 4];
    float                           mPoints;       // +0xc8

    void RecordResults(bool finished);
};

// @ 0x00f16580
void cScenarioResultsRecorder::RecordResults(bool finished)
{
    if (mpPlayerProps == 0)
        return;

    if (finished && mpPlayMode->mCurrentPlayModeState == 5)
        RecordPlayedAdventure(mpPlayerProps, g_ScenarioManager->mpData->mpResource->mHeader);

    const int oldLevel = FindFirstGE(GetIntProperty(mpPlayerProps, 0xcf837237));

    int points = (int)mPoints;
    {
        EA::Variant v;
        v = points;
        mpPlayerProps->SetProperty(0xcf837237, v);
    }
    int level = FindFirstGE(points);
    {
        EA::Variant v;
        v = level;
        mpPlayerProps->SetProperty(0x5888ef41, v);
    }

    if (oldLevel != 10 && level == 10) {
        SP::AchievementsController()->AwardAchievement(0x8b16db09);
        App::MessageServer()->PostMSG(0x7ca274b, 0, 0);
    }

    eastl::fixed_vector_int64_32 stats;
    stats.push_back(points);
    stats.push_back(level);

    Simulator::cScenarioPlaySummary* s = mpPlayMode->GetSummary();
    stats.push_back(AddToIntProperty(mpPlayerProps, 0x5ff28470, s->mNumGoalsCompleted));
    stats.push_back(AddToIntProperty(mpPlayerProps, 0xfbec5f0c, s->mNumCreaturesKilled));
    stats.push_back(AddToIntProperty(mpPlayerProps, 0x02e88517, s->mNumBuildingsDestroyed));
    stats.push_back(AddToIntProperty(mpPlayerProps, 0xb77e5335, s->mNumVehiclesDestroyed));
    stats.push_back(AddToIntProperty(mpPlayerProps, 0xf27fefd1, s->mNumBarrelsDestroyed));
    stats.push_back(AddToIntProperty(mpPlayerProps, 0x76134ba7, s->mNumCreaturesBefriended));
    stats.push_back(AddToIntProperty(mpPlayerProps, 0xa55c05aa, s->mNumObjectsCollected));
    stats.push_back(AddToIntProperty(mpPlayerProps, 0x547fecc1, s->mNumCastMembersTalkedTo));
    stats.push_back(AddToIntProperty(mpPlayerProps, 0x9d8493b2, s->mNumCastMembersDefended));
    stats.push_back(AddToIntProperty(mpPlayerProps, 0xdbcffa7d, s->mNumDeaths));
    stats.push_back(AddToIntProperty(mpPlayerProps, 0x384fb43e, s->mNumPosseMembersLost));
    stats.push_back(AddToIntProperty(mpPlayerProps, 0xf469cdc3, s->mAmountDamageDealt));
    stats.push_back(AddToIntProperty(mpPlayerProps, 0xad4e4ce0, (int)s->mAmountDamageReceived));
    stats.push_back(AddToIntProperty(mpPlayerProps, 0xceb2889b, s->mNumTimesUsedJetPack));
    stats.push_back(AddToIntProperty(mpPlayerProps, 0xc5ff81b3, s->mNumTimesUsedSprint));
    stats.push_back(AddToIntProperty(mpPlayerProps, 0xebed2519, (int)s->mAmountHealthRegained));
    stats.push_back(AddToIntProperty(mpPlayerProps, 0x42abfeab, (int)s->mAmountEnergyUsed));
    stats.push_back(AddToIntProperty(mpPlayerProps, 0x99a62668, 1));
    stats.push_back(AddToIntProperty(mpPlayerProps, 0x0db76cb8, mpPlayMode->mCurrentPlayModeState == 5));
    stats.push_back(AddToIntProperty(mpPlayerProps, 0x59df6558, mpPlayMode->mCurrentPlayModeState == 6));
    stats.push_back(AddToIntProperty(mpPlayerProps, 0x86a6dced, mpPlayMode->GetElapsedTimeMS() / 1000));

    Simulator::cCollectablesHolder* holder = mpHolder;
    holder->mpPending = 0;
    holder->mpPlayerData->mpCollectableItems.get()->Refresh(0);
    holder->Update();

    Simulator::cCollectableItems* items =
        (mpHolder->mpPlayerData ? mpHolder->mpPlayerData->mpCollectableItems
                                : eastl::intrusive_ptr<Simulator::cCollectableItems>()).get();
    SaveCollectableItems(mpPlayerProps, items);

    const ResourceKey* key = g_ScenarioManager->mpData->GetKey();
    SaveEditorPropertyList(key, mpPlayerProps, 0, 0);
    SP::GetPollinator()->UpdatePropertyInt(0xd9d7edf2, key, (uint32_t)stats.data(), stats.size());

    eastl::string16 name;
    GetAdventureName(key, &name);
    {
        EA::Variant v;
        v.Set(0x13, 9, &name, 0x10, 1);
        SP::GetPollinator()->UpdateProperty2(0xa31b4d50, key, &v);
    }

    Simulator::cCollectableItems* items2 =
        (mpHolder->mpPlayerData ? mpHolder->mpPlayerData->mpCollectableItems
                                : eastl::intrusive_ptr<Simulator::cCollectableItems>()).get();
    eastl::list<int64_t>& unlocked = items2->GetUnlockedItems();
    stats.assign(unlocked.begin(), unlocked.end());
    SP::GetPollinator()->UpdatePropertyInt(0x0fdb0e00, key, (uint32_t)stats.data(), stats.size());
}
