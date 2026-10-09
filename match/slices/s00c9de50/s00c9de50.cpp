// Slice s00c9de50: SP::cTribeTool::LoadTribeToolData() (0x00c9de50, 1759 bytes).
// One-time load of the tribe tool tuning: creates the 12 cTribeToolData records, lists every property
// list of group 0x04292f52, and for each list with a tool type in 1..11 fills the record from its
// properties (keys, tuning numbers, display text) and, when the list names an ability list, reads
// that into a cCreatureAbility. Class and field names are coined from usage.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

// ------------------------------------------------------------------ keys
struct ResourceKey {
    uint32_t instance, type, group;
    ResourceKey() {}
    ResourceKey(uint32_t i, uint32_t t, uint32_t g) : instance(i), type(t), group(g) {}
};

// ------------------------------------------------------------------ properties
extern const int      kDefaultInt32Value;   // 015d1160
extern const uint32_t kDefaultUInt32Value;  // 015d1164

struct Property {
    void*    mpData;       // +0x00 (external data, or the inline value itself)
    uint32_t pad04[3];
    uint16_t mnFlags;      // +0x10 (0x30 = external data)
    uint16_t mnType;       // +0x12

    void* GetValuePtr()
    {
        if (mnFlags & 0x30)
            return mpData;
        else if (mnType != 0)
            return this;
        return 0;
    }
    const int* GetValueInt32()
    {
        if (mnType == 9 || mnType == 0x10)
            return (const int*)GetValuePtr();
        return &kDefaultInt32Value;
    }
    const uint32_t* GetValueUInt32()
    {
        if (mnType == 10 || mnType == 0x10)
            return (const uint32_t*)GetValuePtr();
        return &kDefaultUInt32Value;
    }
    const ResourceKey* GetValueKey();               // inline body below
    const ResourceKey* GetKeyTPTR();                // 00454b10 VariantTypeTraits<Key>::GetTPTR
    const float* GetFloat();                        // 0041ea70
};

const ResourceKey* DefaultResourceKey();            // 006bb640

inline const ResourceKey* Property::GetValueKey()
{
    if (mnType == 0x20 || mnType == 0x10)
        return (const ResourceKey*)GetValuePtr();
    return DefaultResourceKey();
}

struct PropertyList {
    virtual int AddRef();                           // +0x00
    virtual int Release();                          // +0x04
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
    virtual bool HasProperty(uint32_t id);          // +0x1c
    virtual void v8(); virtual void v9();
    virtual Property* GetProperty(uint32_t id);     // +0x28
    int         mRefCount;                          // +0x04 (shared with the vptr slot view)
    ResourceKey mKey;                               // +0x08
};

// eastl::intrusive_ptr<PropertyList>
struct PropertyListPtr {
    PropertyList* mpObject;
    PropertyListPtr() { mpObject = 0; }
    ~PropertyListPtr() { if (mpObject) mpObject->Release(); }
    PropertyList** AsParam()
    {
        PropertyList* p = mpObject;
        if (p) {
            mpObject = 0;
            p->Release();
        }
        return &mpObject;
    }
};

struct UIntVector;
struct IPropManager {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyList** ppOut);  // +0x2c
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17();
    virtual bool GetPropertyListIDs(uint32_t groupID, UIntVector& result);                      // +0x48
};

void __cdecl EASTL_allocator_deallocate(void* p); // 0x00f47380   // 00f47380

struct UIntVector {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    UIntVector() { mpBegin = 0; mpEnd = 0; mpCapacity = 0; }
    ~UIntVector()
    {
        uint32_t* p = mpBegin;
        if (p) {
            if (((uint32_t*)p)[-1]) { void* q = p; EASTL_allocator_deallocate(q); }
        }
    }
};

// ------------------------------------------------------------------ strings, abilities
struct cString {                                     // retail SP::cString (0x14 bytes)
    uint32_t d[5];
    cString();                                       // 006b5060
    cString(const cString& o);                       // 006b56f0
    ~cString();                                      // 006b5240
};

struct DefaultRefCounted;
struct DefaultRefCountedPtr {                        // eastl::intrusive_ptr<DefaultRefCounted>
    DefaultRefCounted* mpObject;
    DefaultRefCountedPtr() : mpObject(0) {}
    DefaultRefCountedPtr& operator=(const DefaultRefCountedPtr& o);   // 004e4350
};

struct cCreatureAbility {
    virtual ~cCreatureAbility();
    int mnRefCount;                                  // +0x04
    uint32_t pad08[(0x13c - 0x08) / 4];
    cCreatureAbility();                              // 004d3760
};

struct AbilityRef {
    cCreatureAbility* mpObject;
    AbilityRef(cCreatureAbility* p) { mpObject = p; if (mpObject) mpObject->mnRefCount++; }
    ~AbilityRef()
    {
        if (mpObject) {
            int n = mpObject->mnRefCount - 1;
            mpObject->mnRefCount = mpObject->mnRefCount - 1;
            if (n == 0) {
                mpObject->mnRefCount = 1;
                delete mpObject;
            }
        }
    }
};

void* operator new(unsigned int size, const char* name, int flags, unsigned int align,
                   const char* file, int line);      // 00f473a0

struct cTribeToolData {
    ResourceKey mListKey;       // +0x00 key of the property list
    uint32_t mTypeIndex;        // +0x0c
    uint32_t mSubIndex;         // +0x10
    ResourceKey mKey;           // +0x14
    uint32_t m20;               // +0x20
    DefaultRefCountedPtr mAbility;   // +0x24
    uint32_t m28, m2c;          // +0x28
    uint32_t m30, m34;          // +0x30
    int      m38, m3c;          // +0x38
    float    mFloat40;          // +0x40
    ResourceKey mKey1, mKey2, mKey3;   // +0x44
    cString  mText;             // +0x68

    cTribeToolData(const cString& s);
};

__forceinline cTribeToolData::cTribeToolData(const cString& s)
    : mListKey(0, 0, 0), mTypeIndex(0), mSubIndex(0), mKey(0, 0, 0), m20(0), mAbility(), m28(0x2481de5), m2c(0x2481de5),
      m30(0), m34(0), m38(0), m3c(2), mKey1(0, 0, 0), mKey2(0, 0, 0), mKey3(0, 0, 0), mText(s)
{
}

// ------------------------------------------------------------------ externals
namespace SP {
IPropManager* PropertyManager();                                              // 0067de30
bool GetPropertyAsText(PropertyList* p, uint32_t id, cString* pOut);           // 006a1360
bool ReadAbilityData(cCreatureAbility* pAbility, PropertyList* pList);         // 004d92b0
}
uint32_t TribeToolIntProperty(PropertyList* p, uint32_t id, int zero);        // 00ac8fa0

extern cTribeToolData* gTribeTools[12];     // 01699a14
extern bool gTribeToolsLoaded;              // 01699a44

extern const uint32_t kPropTypeIndex;       // 0157c578
extern const uint32_t kPropSubIndex;        // 0157c57c
extern const uint32_t kPropKey;             // 0157c580
extern const uint32_t kPropField20;         // 0157c584
extern const uint32_t kPropM28;             // 0157c588
extern const uint32_t kPropM2c;             // 0157c58c
extern const uint32_t kPropM38;             // 0157c590
extern const uint32_t kPropKey1;            // 0157c594
extern const uint32_t kPropKey2;            // 0157c598
extern const uint32_t kPropKey3;            // 0157c59c
extern const uint32_t kPropFloat40;         // 0157c5a0
extern const uint32_t kPropText;            // 0157c5a4
extern const uint32_t kPropAbilityList;     // 0157c5a8
extern const uint32_t kPropM30;             // 0157c5ac
extern const uint32_t kPropM34;             // 0157c5b0
extern const uint32_t kPropM3c;             // 0157c5b4

namespace SP {
struct cTribeTool {
    static bool LoadTribeToolData();
};

// @ 0x00c9de50
bool cTribeTool::LoadTribeToolData()
{
    PropertyListPtr pList;
    if (!gTribeToolsLoaded) {
        IPropManager* pPropManager = PropertyManager();
        for (unsigned i = 0; i < 12; i++) {
            gTribeTools[i] = new("Simulator/cTribeToolData", 0, 0, 0, 0) cTribeToolData(cString());
        }
        UIntVector ids;
        PropertyManager()->GetPropertyListIDs(0x04292f52, ids);
        uint32_t* it = ids.mpBegin;
        uint32_t* end = ids.mpEnd;
        if (it == end)
            return false;
        for (; it != end; ++it) {
            uint32_t id = *it;
            if (!pPropManager->GetPropertyList(id, 0x04292f52, pList.AsParam()))
                return false;
            if (pList.mpObject->HasProperty(kPropTypeIndex) && pList.mpObject->HasProperty(kPropSubIndex)) {
                uint32_t typeIndex = *pList.mpObject->GetProperty(kPropTypeIndex)->GetValueUInt32();
                uint32_t subIndex = *pList.mpObject->GetProperty(kPropSubIndex)->GetValueUInt32();
                if (typeIndex - 1 <= 10) {
                    cTribeToolData* t = gTribeTools[typeIndex];
                    t->mListKey = pList.mpObject->mKey;
                    t->mTypeIndex = typeIndex;
                    t->mSubIndex = subIndex;
                    if (pList.mpObject->HasProperty(kPropKey))
                        t->mKey = *pList.mpObject->GetProperty(kPropKey)->GetKeyTPTR();
                    t->mKey.type = 0xb1b104;
                    t->mKey1 = t->mKey2 = t->mKey3 = t->mKey;
                    if (pList.mpObject->HasProperty(kPropKey1))
                        t->mKey1 = *pList.mpObject->GetProperty(kPropKey1)->GetKeyTPTR();
                    t->mKey1.type = 0xb1b104;
                    if (pList.mpObject->HasProperty(kPropKey2))
                        t->mKey2 = *pList.mpObject->GetProperty(kPropKey2)->GetKeyTPTR();
                    t->mKey2.type = 0xb1b104;
                    if (pList.mpObject->HasProperty(kPropKey3))
                        t->mKey3 = *pList.mpObject->GetProperty(kPropKey3)->GetKeyTPTR();
                    t->mKey3.type = 0xb1b104;
                    if (pList.mpObject->HasProperty(kPropFloat40))
                        t->mFloat40 = *pList.mpObject->GetProperty(kPropFloat40)->GetFloat();
                    t->m20 = TribeToolIntProperty(pList.mpObject, kPropField20, 0);
                    t->m28 = *pList.mpObject->GetProperty(kPropM28)->GetValueUInt32();
                    t->m2c = *pList.mpObject->GetProperty(kPropM2c)->GetValueUInt32();
                    t->m30 = *pList.mpObject->GetProperty(kPropM30)->GetValueUInt32();
                    t->m34 = *pList.mpObject->GetProperty(kPropM34)->GetValueUInt32();
                    t->m38 = *pList.mpObject->GetProperty(kPropM38)->GetValueInt32();
                    t->m3c = *pList.mpObject->GetProperty(kPropM3c)->GetValueInt32();
                    GetPropertyAsText(pList.mpObject, kPropText, &t->mText);
                    ResourceKey abilityKey = *pList.mpObject->GetProperty(kPropAbilityList)->GetValueKey();
                    PropertyListPtr pAbilityList;
                    if (pPropManager->GetPropertyList(abilityKey.instance, abilityKey.group, &pAbilityList.mpObject)) {
                        AbilityRef ability(new("Simulator/cCreatureAbility", 0, 0, 0, 0) cCreatureAbility());
                        ReadAbilityData(ability.mpObject, pAbilityList.mpObject);
                        t->mAbility = *(DefaultRefCountedPtr*)&ability;
                    }
                }
            }
        }
    }
    gTribeToolsLoaded = true;
    return true;
}
}
