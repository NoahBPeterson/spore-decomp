// Slice s00e3cf60: the single function in this slice is
//   0x00E3CF60  cSPUITradeItemInfo::Populate  (2687 bytes, __thiscall, 1 arg, ret 4, returns bool)
//   (all names Claude-coined; the class is a space-stage UI panel that shows one tradable/collectible
//    item: 7 ResourceKeys at +0x580 and 17 string16 fields at +0x5d4.)
//
// What it does: given the source object (arg), takes its item (arg+0xa8) and the item's record,
//   1. looks up the record's category (property 0x91ad064 of list (kind, 0xe1d7164f));
//   2. formats three numbers into strings 15, 16 and 14, and fills strings 0/4 from keys 4/5;
//   3. per category (0xad56080c, 0x2db6dad3, 0xbeb528cb, 0xf71fa311) fills further text strings and
//      keys from property lists, the empire's name, the badge manager, etc.;
//   4. finally fills string 9 / string 8 and keys 1/0 from the record's two description keys.
//
// Flags: /O2 /MD /Gy /TP /GS- (no /EHsc: cString locals but no EH frame; no float code).
#include "types.h"

typedef unsigned int size_t;

// ---------------------------------------------------------------------------------------
struct ResourceKey {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
    __forceinline ResourceKey() {}
    __forceinline ResourceKey(uint32_t i, uint32_t t, uint32_t g) : instanceID(i), typeID(t), groupID(g) {}
};

template <class T> struct intrusive_ptr {
    T* mpObject;
    __forceinline intrusive_ptr() : mpObject(0) {}
    __forceinline ~intrusive_ptr() { if (mpObject) mpObject->Release(); }
    __forceinline T* get() const { return mpObject; }
    __forceinline intrusive_ptr& operator=(T* pObject)
    {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject) pObject->AddRef();
            mpObject = pObject;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
    T** AsPPTypeParam();                                                 // 0x00a16f40
};

class PropertyList {
public:
    virtual void AddRef();
    virtual void Release();
};
typedef intrusive_ptr<PropertyList> PropertyListPtr;

__forceinline PropertyListPtr& ResetForOutput(PropertyListPtr& p) { p = 0; return p; }

class IPropManager {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyListPtr& dst);   // 0x2c
    virtual bool GetGlobalPropertyList(uint32_t id, PropertyList** dst);                         // 0x30
    // AutoRefCount::AsPPTypeParam() (release + &mpObject); the original inlines it at some call
    // sites and calls the out-of-line copy (0x00a16f40) at others.
    __forceinline bool GetPropertyListPP(uint32_t instanceID, uint32_t groupID, PropertyListPtr& dst)
    {
        return GetPropertyList(instanceID, groupID, *(PropertyListPtr*)dst.AsPPTypeParam());
    }
    __forceinline bool GetGlobalPropertyListPP(uint32_t id, PropertyListPtr& dst)
    {
        return GetGlobalPropertyList(id, dst.AsPPTypeParam());
    }
};
IPropManager* PropertyManager();                                         // 0x0067de30
#define PropManager (*PropertyManager())

class IResourceManager {
public:
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual bool FindRecord(const ResourceKey& key, int a, int b, int c, int d, int e);   // 0x0c
};
IResourceManager* GetResourceManager();                                  // 0x0067dcd0

bool GetPropertyAsKeyInstance(const PropertyList* prop, uint32_t id, uint32_t* dst);   // 0x006a12a0
bool GetPropertyAsKey(const PropertyList* prop, uint32_t id, ResourceKey* dst);        // 0x006a1250

class cString {
public:
    cString();                                                           // 0x006b5060
    ~cString();                                                          // 0x006b5240
    const wchar_t* GetText();                                            // 0x006b55c0
    uint32_t data[0x14 / 4];
};
bool GetPropertyAsText(const PropertyList* prop, uint32_t id, cString& dst);           // 0x006a1360

void SetNumberString(__int64 value, wchar_t* buffer, int bufferSize);    // 0x00881ae0

// eastl::basic_string<wchar_t>
struct string16 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAllocator;

    string16& AssignRange(const wchar_t* first, const wchar_t* last);    // 0x00423650
    string16& AssignCStr(const wchar_t* p);                              // 0x005c3d90
    string16& operator=(const string16& x);                              // 0x0057cb60
    __forceinline string16& assign_inline(const wchar_t* p)
    {
        const wchar_t* pCurrent = p;
        while (*pCurrent)
            ++pCurrent;
        return AssignRange(p, p + (size_t)(pCurrent - p));
    }
};

// ---------------------------------------------------------------------------------------
// The item record: keys stored as (type, instance, group).
struct RecordKey {
    uint32_t typeID;
    uint32_t instanceID;
    uint32_t groupID;
};

struct cItemRecord {
    uint32_t mKind;                                                      // +0x00
    uint32_t pad04[2];
    RecordKey mKey3;                                                     // +0x0c (index 3)
    RecordKey mKey6;                                                     // +0x18 (index 6)
    uint32_t mEmpireID;                                                  // +0x24
    uint32_t pad28;
    uint32_t mValue2C;                                                   // +0x2c
    uint32_t mValue30;                                                   // +0x30
    RecordKey mKeyD;                                                     // +0x34 (index 0xd)
    RecordKey mKey10;                                                    // +0x40 (index 0x10)
    RecordKey mKey13;                                                    // +0x4c
    RecordKey mKey16;                                                    // +0x58
    uint32_t mPlanetID;                                                  // +0x64
    uint32_t mValue68;                                                   // +0x68
};

struct cTradeItem {
    uint32_t pad0[3];
    cItemRecord* mpRecord;                                               // +0x0c
};

// 0x00e39420 (out of line), inlined at some call sites
void GetItemKey(cTradeItem* item, int index, ResourceKey* dst);
__forceinline void GetItemKeyInline(cTradeItem* item, int index, ResourceKey* dst)
{
    if (item) {
        dst->typeID = ((uint32_t*)item->mpRecord)[index];
        dst->instanceID = ((uint32_t*)item->mpRecord)[index + 1];
        dst->groupID = ((uint32_t*)item->mpRecord)[index + 2];
    }
}

struct cTradeSource {
    uint32_t pad0[0xa8 / 4];
    cTradeItem* mpItem;                                                  // +0xa8
    uint32_t padac[(0xd4 - 0xac) / 4];
    int mCount;                                                          // +0xd4
    int mCountD8;                                                        // +0xd8
    cTradeItem* GetItem();                                               // 0x0098f940
};

void FormatItemText(string16* src, uint32_t value, int mode, cString& dst);   // 0x00b6ec50

class cEmpire { public: string16* GetEmpireName(); };                          // 0x005c65e0
class cPlanetRecord {
public:
    string16* GetPlanetName();                                           // 0x00ecdba0
    ResourceKey* GetImageKey();                                          // 0x00b8d8e0
};
class cStarManager {
public:
    cEmpire* GetEmpireByID(uint32_t id);                                 // 0x00ba9370
    cPlanetRecord* GetPlanetRecord(uint32_t id);                         // 0x00ba6dc0
};
cStarManager* StarManager();                                             // 0x00b3d2a0

class cBadgeManager { public: ResourceKey GetBadgeImageKey(uint32_t badge); };   // 0x00fe5520
class cSpaceGame { public: cBadgeManager* GetBadgeManager(); };          // 0x00bfc5f0
cSpaceGame* SpaceGameGet();                                              // 0x01002bd0

struct cTradeTarget {
    uint32_t pad0[0x14 / 4];
    ResourceKey mKey;                                                    // +0x14
    uint32_t mValue;                                                     // +0x20
};
struct cTradeTargetHolder {
    uint32_t pad0[0x7c / 4];
    cTradeTarget* mpTarget;                                              // +0x7c
};
extern cTradeTargetHolder* g_TradeTargetHolder;                          // 0x016c7aa4
extern uint32_t g_PlanetImageGroup;                                      // 0x015a5938

class cSPUITradeItemInfo {
public:
    bool Populate(cTradeSource* source);
    void SetKeyString(ResourceKey* key, string16* str, int index);       // 0x00e3ce60
    int GetPrice(cTradeSource* source);                                  // 0x00e37780

    uint32_t pad0[0x580 / 4];
    ResourceKey mKeys[7];                                                // +0x580
    string16 mStrings[17];                                               // +0x5d4
};

// ---------------------------------------------------------------------------------------
// 0x00E3CF60
bool cSPUITradeItemInfo::Populate(cTradeSource* source)
{
    if (!source || !source->GetItem())
        return false;

    cTradeItem* item = source->GetItem();
    uint32_t kind = item->mpRecord->mKind;
    uint32_t category = 0;
    PropertyListPtr propList;
    if (PropManager.GetPropertyList(kind, 0xe1d7164f, ResetForOutput(propList)))
        GetPropertyAsKeyInstance(propList.get(), 0x91ad064, &category);

    ResourceKey key3, key6, keyD, key10;
    GetItemKeyInline(item, 3, &key3);
    GetItemKeyInline(item, 6, &key6);
    GetItemKeyInline(item, 0x10, &key10);
    GetItemKeyInline(item, 0xd, &keyD);

    wchar_t countText[64];
    SetNumberString(source->mCount, countText, 64);
    mStrings[15].assign_inline(countText);
    wchar_t priceText[64];
    SetNumberString(GetPrice(source), priceText, 64);
    mStrings[16].assign_inline(priceText);
    wchar_t countD8Text[64];
    SetNumberString(source->mCountD8, countD8Text, 64);
    mStrings[14].assign_inline(countD8Text);

    SetKeyString(&key3, &mStrings[0], 4);
    SetKeyString(&key6, &mStrings[4], 5);

    switch (category) {
    case 0xad56080c:
        if (kind == 0x246ba26c || kind == 0x278e6ca8) {
            PropertyListPtr textProp;
            if (PropManager.GetPropertyListPP(key10.instanceID, key10.groupID, textProp)) {
                cString text;
                GetPropertyAsText(textProp.get(), 0x1b7c544, text);
                mStrings[9].AssignCStr(text.GetText());
                mKeys[1] = ResourceKey(0, 0, 0);
                key10.instanceID = 0;
            }
        }
        break;

    case 0x2db6dad3: {
        cEmpire* empire = StarManager()->GetEmpireByID(item->mpRecord->mEmpireID);
        if (empire)
            mStrings[3] = *empire->GetEmpireName();
        cString text;
        FormatItemText(&mStrings[4], item->mpRecord->mValue30, 2, text);
        mStrings[7].AssignCStr(text.GetText());

        uint32_t planetID = item->mpRecord->mPlanetID;
        if (planetID) {
            ResourceKey imageKey;
            bool haveImage = true;
            if (kind == 0x1af2f7b7) {
                ResourceKey key(planetID, 0x366a930d, g_PlanetImageGroup);
                SetKeyString(&key, &mStrings[11], 6);
                imageKey.instanceID = planetID;
                imageKey.typeID = 0x366a930d;
                imageKey.groupID = key.groupID;
            } else {
                cPlanetRecord* planet = StarManager()->GetPlanetRecord(planetID);
                if (!planet) {
                    haveImage = false;
                } else {
                    mStrings[11] = *planet->GetPlanetName();
                    ResourceKey* k = planet->GetImageKey();
                    imageKey.instanceID = k->instanceID;
                    imageKey.typeID = k->typeID;
                    imageKey.groupID = (k->groupID & 0xffffff01) | 1;
                }
            }
            if (haveImage) {
                imageKey.typeID = 0x2f7d0004;
                if (!GetResourceManager()->FindRecord(imageKey, 0, 0, 0, 0, 0)) {
                    PropertyListPtr fallback;
                    PropManager.GetGlobalPropertyListPP(0x120b89ce, fallback);
                    GetPropertyAsKey(fallback.get(), 0x287652b, &imageKey);
                }
                mKeys[6] = imageKey;
            }
        }

        ResourceKey key16;
        key16.instanceID = 0;
        GetItemKey(item, 0x16, &key16);
        if (key16.instanceID) {
            PropertyListPtr prop;
            if (PropManager.GetPropertyListPP(key16.instanceID, 0x34d97fa, prop)) {
                cString name;
                GetPropertyAsText(prop.get(), 0x3068d95d, name);
                mStrings[12].AssignCStr(name.GetText());
                GetPropertyAsKey(prop.get(), 0x653a6cf, &mKeys[3]);
            }
        }

        uint32_t value68 = item->mpRecord->mValue68;
        if (value68) {
            wchar_t valueText[64];
            SetNumberString(value68, valueText, 64);
            mStrings[13].AssignCStr(valueText);
        }

        switch (kind) {
        case 0xbbc2a4ef: {
            cTradeTarget* target = g_TradeTargetHolder->mpTarget;
            target->mKey = key3;
            target->mValue = 0xffffffff;
            g_TradeTargetHolder->mpTarget->mValue = item->mpRecord->mValue68;
            break;
        }
        case 0x687b36a1: {
            uint32_t badge = item->mpRecord->mValue68;
            if (!badge)
                badge = 0xa9e986a3;
            ResourceKey badgeKey(0xd22db80a, 0x2f7d0004, 0x542e15d);
            cSpaceGame* game = SpaceGameGet();
            if (game)
                badgeKey = game->GetBadgeManager()->GetBadgeImageKey(badge);
            mKeys[5] = badgeKey;
            break;
        }
        }
        break;
    }

    case 0xbeb528cb: {
        cString text1;
        FormatItemText(&mStrings[0], item->mpRecord->mValue2C, 0xd, text1);
        mStrings[2].AssignCStr(text1.GetText());
        cString text2;
        FormatItemText(&mStrings[4], item->mpRecord->mValue30, 1, text2);
        mStrings[6].AssignCStr(text2.GetText());

        ResourceKey key13;
        key13.instanceID = 0;
        key13.groupID = 0;
        GetItemKey(item, 0x13, &key13);
        if (key13.instanceID) {
            PropertyListPtr prop;
            if (PropManager.GetPropertyListPP(key13.instanceID, key13.groupID, prop)) {
                cString name;
                GetPropertyAsText(prop.get(), 0xd4d959e0, name);
                mStrings[10].AssignCStr(name.GetText());
                GetPropertyAsKey(prop.get(), 0xd4d959e2, &mKeys[2]);
            }
        }
        break;
    }

    case 0xf71fa311: {
        cString text1;
        FormatItemText(&mStrings[0], item->mpRecord->mValue2C, 0xe, text1);
        mStrings[1].AssignCStr(text1.GetText());
        cString text2;
        FormatItemText(&mStrings[4], item->mpRecord->mValue30, 0, text2);
        mStrings[5].AssignCStr(text2.GetText());

        uint32_t value68 = item->mpRecord->mValue68;
        if (value68) {
            wchar_t valueText[64];
            SetNumberString(value68, valueText, 64);
            mStrings[13].AssignCStr(valueText);
        }

        if (kind == 0x25c8b21a) {
            PropertyListPtr prop;
            if (PropManager.GetPropertyListPP(key10.instanceID, key10.groupID, prop)) {
                cString text;
                GetPropertyAsText(prop.get(), 0x8f6fc401, text);
                mStrings[9].AssignCStr(text.GetText());
                mKeys[1] = ResourceKey(key10.instanceID, 0x2f7d0004, 0x65928944);
                key10.instanceID = 0;
            }
        }
        break;
    }
    }

    if (key10.instanceID) {
        PropertyListPtr prop;
        if (PropManager.GetPropertyList(key10.instanceID, key10.groupID, ResetForOutput(prop))) {
            cString text;
            GetPropertyAsText(prop.get(), 0x1b7c544, text);
            mStrings[9].AssignCStr(text.GetText());
        }
    }

    if (keyD.instanceID) {
        PropertyListPtr prop;
        if (PropManager.GetPropertyList(keyD.instanceID, keyD.groupID, ResetForOutput(prop))) {
            cString text;
            GetPropertyAsText(prop.get(), 0x8f6fc401, text);
            mStrings[8].AssignCStr(text.GetText());
            uint32_t group = 0x2231c8b;
            if (category == 0xa426730b)
                group = 0xb1b0f42e;
            else if (kind == 0x88558da4)
                group = 0x91b125e5;
            mKeys[0] = ResourceKey(keyD.instanceID, 0x2f7d0004, group);
        }
    }

    return true;
}
