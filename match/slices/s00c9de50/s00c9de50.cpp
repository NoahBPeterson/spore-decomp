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
class cTribeTool { public:
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

// =============================================================================================
// Vehicle / game-data helpers that follow the tribe-tool loader (0x00c9e530 .. 0x00c9eef0).
// Every entry below is a small __thiscall member or a leaf helper; class and field names are coined
// from usage (the retail names for these symbols are not available, only their addresses).
// =============================================================================================

struct Float3 { float x, y, z; };

// vtable prefixes: the retail call sites index slots by byte offset, so each modelled class declares
// the unused leading slots in front of the one slot it actually calls.
struct Vt05 {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
};
struct Vt10 {
    virtual void w00(); virtual void w04(); virtual void w08(); virtual void w0c(); virtual void w10();
    virtual void w14(); virtual void w18(); virtual void w1c(); virtual void w20(); virtual void w24();
};
struct Vt21 {
    virtual void x00(); virtual void x04(); virtual void x08(); virtual void x0c(); virtual void x10();
    virtual void x14(); virtual void x18(); virtual void x1c(); virtual void x20(); virtual void x24();
    virtual void x28(); virtual void x2c(); virtual void x30(); virtual void x34(); virtual void x38();
    virtual void x3c(); virtual void x40(); virtual void x44(); virtual void x48(); virtual void x4c();
    virtual void x50();
};

struct cVehicle;

// Locomotive sub-object: the retail object lives at vehicle + 0x34.
struct cLoco : Vt10 {
    virtual void  v28();
    virtual int   Slot2c();                 // +0x2c
    virtual void  v30();
    virtual float Slot34();                 // +0x34
    virtual void  v38(); virtual void v3c(); virtual void v40(); virtual void v44();
    virtual void  v48(); virtual void v4c(); virtual void v50(); virtual void v54();
    virtual bool  Slot58();                 // +0x58

    void* Find(uint32_t id);                // 0x00c41d00
    bool  Write(void* ar);                  // 0x00c448a0
    void  SetValue(float v, int n);         // 0x00c9ece0
    void  SetProperty(float v, int n);      // 0x00c41d20
    void  FormatName(cString* out);         // 0x00c9e5a0
    bool  IsLocalPlayer();                  // 0x00c9e690
};

// Combat sub-object at vehicle + 0x508.
struct cCombatant : Vt21 {
    virtual float GetFraction();            // +0x58
    uint32_t pad04[(0x38 - 4) / 4];         // +0x04
    float    mValue;                        // +0x38

    void* Find(uint32_t id);                // 0x00bfc380
    bool  Write(void* ar);                  // 0x00bfc4a0
    float GetValue();                       // 0x00bfc490
};

struct cChild5d0 { uint32_t mWord; void* Find(uint32_t id); };   // 0x00abf740
struct cChild638 { uint32_t mWord; void* Find(uint32_t id); };   // 0x00ac0320
struct cChild650 { uint32_t mWord; void* Find(uint32_t id); };   // 0x00c7d050

// Attachment object reached through vehicle + 0xaf0; its child at +0x08 owns the flag word.
struct cAttachmentChild {
    uint32_t pad00[(0x5f4) / 4];            // +0x000
    uint32_t mFlags;                        // +0x5f4 (attachment + 0x5fc)
    void Func(int a, int b, float c, int d);    // 0x00bc97f0
};
// Overlay of the same +0x08 region as cAttachmentChild, with the flag word named at the attachment
// level (the flag accesses are folded to attachment + 0x5fc in the retail code).
struct cAttachmentFlags {
    uint32_t pad00[(0x5fc - 0x08) / 4];     // +0x008
    uint32_t mFlags;                        // +0x5fc
};
struct cAttachment {
    uint32_t pad00[2];                      // +0x00
    union {
        cAttachmentChild mChild;            // +0x08
        cAttachmentFlags mFlagsView;        // +0x08
    };
};

struct cGameDataInner {
    uint32_t pad00[(0x1c8) / 4];            // +0x000
    uint32_t mBits;                         // +0x1c8
};

struct cArchiveStream : Vt05 {
    virtual void z14();
    virtual uint32_t GetHandle();           // +0x18
};
struct cArchive : Vt05 {
    virtual void y14(); virtual void y18(); virtual void y1c();
    virtual cArchiveStream* Slot20();       // +0x20
};

struct cVarListSerializer {
    uint32_t mPad[(0xa14) / 4];             // +0x000 (retail object; contents not modelled)
    cVarListSerializer(void* owner, uint32_t key, const char* name);   // 0x00692f90
    bool Serialize(cArchive* ar);                                      // 0x00692900
};

struct cVehicle : Vt05 {
    virtual void* Slot14();                 // +0x14
    virtual void  v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void  v28(); virtual void v2c(); virtual void v30(); virtual void v34();
    virtual void  v38(); virtual void v3c(); virtual void v40(); virtual void v44();
    virtual void  v48();
    virtual int   Slot4c();                 // +0x4c
    virtual void  v50(); virtual void v54(); virtual void v58();
    virtual const char* Slot5c();           // +0x5c

    uint32_t pad04[(0x34 - 0x04) / 4];      // +0x004
    cLoco    mLoco;                         // +0x034 (only the vptr is modelled)
    uint32_t pad38[(0xc4 - 0x38) / 4];      // +0x038
    uint32_t mPairIdA;                      // +0x0c4
    uint32_t mPairIdB;                      // +0x0c8
    uint32_t padCC[(0x508 - 0xcc) / 4];     // +0x0cc
    cCombatant mCombatant;                  // +0x508
    uint32_t pad544[(0x5d0 - 0x544) / 4];   // +0x544
    cChild5d0 mChild5d0;                    // +0x5d0
    uint32_t pad5d4[(0x5e8 - 0x5d4) / 4];   // +0x5d4
    cGameDataInner* mpField5e8;             // +0x5e8
    uint32_t pad5ec[(0x638 - 0x5ec) / 4];   // +0x5ec
    cChild638 mChild638;                    // +0x638
    uint32_t pad63c[(0x650 - 0x63c) / 4];   // +0x63c
    cChild650 mChild650;                    // +0x650
    uint32_t pad654[(0x774 - 0x654) / 4];   // +0x654
    uint32_t mField774;                     // +0x774
    uint32_t mField778;                     // +0x778
    uint32_t mField77c;                     // +0x77c
    uint32_t pad780[(0xaf0 - 0x780) / 4];   // +0x780
    cAttachment* mpFieldAF0;                // +0xaf0
    uint32_t mFieldAF4;                     // +0xaf4
    uint32_t mFieldAF8;                     // +0xaf8
    uint32_t padAfc[(0xb1c - 0xafc) / 4];   // +0xafc
    int      mFieldB1c;                     // +0xb1c
    uint32_t mFieldB20;                     // +0xb20
    uint32_t padB24[(0xb90 - 0xb24) / 4];   // +0xb24
    int      mFieldB90;                     // +0xb90
    uint8_t  padB94[0xbce - 0xb94];         // +0xb94
    uint8_t  mFieldBCE;                     // +0xbce
    uint8_t  padBcf[0xc3c - 0xbcf];         // +0xbcf
    Float3   mVecC3c;                       // +0xc3c
    float    mFieldC48;                     // +0xc48
    float    mFieldC4C;                     // +0xc4c
    uint32_t padC50[(0xd04 - 0xc50) / 4];   // +0xc50
    int      mFieldD04;                     // +0xd04
    uint32_t padD08[(0xd24 - 0xd08) / 4];   // +0xd08
    uint32_t mFieldD24;                     // +0xd24
    uint32_t mFieldD28;                     // +0xd28

    void*  BaseFind(uint32_t id);           // 0x00b18460
    bool   BaseWriteAsText(void* ar);       // 0x00bfc860
    char   BaseRemoveOwner();               // 0x00bfc3a0
    bool   BaseWrite(void* ar);             // 0x00b18590

    cVehicle* Find(uint32_t id);            // 0x00c9e610
    void UpdateDamageState();               // 0x00c9e700
    void WriteAsText(void* ar);             // 0x00c9e760
    bool RemoveOwner(int owner);            // 0x00c9e790
    float GetHealthFraction();              // 0x00c9e7c0
    void GetC3C(Float3* out, float* a, float* b);   // 0x00c9e8a0
    float GetFraction();                    // 0x00c9ec00
    bool CanOccupyTerrain(int data);        // 0x00c9e960
    bool Write(cArchive* ar);               // 0x00c9e9e0
    int  GetMode();                         // 0x00c9eaf0
    float GetModeRadius();                  // 0x00c9eb80
    float GetArea();                        // 0x00c9ec50
    void SetDrone(bool on);                 // 0x00c9ec80
    void SetJustEyeCandy(bool on);          // 0x00c9ecb0
    void SetTimer(int v);                   // 0x00c9ee30
    void ConsumeTimer();                    // 0x00c9ee50
    void PlaySomething();                   // 0x00c9eea0
    bool HasBit2000();                      // 0x00c9eed0
    bool IsFlying();                        // 0x00c9eef0
};

struct cConfigManager : Vt10 {
    virtual void v28();
    virtual void v2c();
    virtual uint32_t Slot30(uint32_t id);   // +0x30
};

struct cCivModeStrategy {
    bool HasCivTutorialOccurred(uint32_t id);   // 0x00cf7830
    void DoNext(uint32_t id, int flag);         // 0x00cfa990
};

struct cPlanetModel {
    uint32_t GetAverageRadius(int data);    // 0x00b7e840
    int      GetContinent(int data);        // 0x00b88590
};

struct cCivilization {
    uint32_t pad00[(0x430) / 4];            // +0x000
    uint8_t  mField430;                     // +0x430
    float    Func00bf2170(uint32_t a, uint32_t b);   // 0x00bf2170
};

struct cGameNounManager {
    int GetPlayerEmpireOrMinus1();          // 0x00b1f9d0
    cCivilization* GetPlayerCivilization(); // 0x00b25fb0
    cCivilization* Func00b25f40(int id);    // 0x00b25f40
};

// --- addressed globals (only their addresses are observed here) ---------------------------------
extern const uint8_t gModeFour;             // 0x01654c04
extern const uint8_t gModeFive;             // 0x01654c05
extern const uint8_t gModeTen;              // 0x01654c10
extern const uint8_t gNullObjectKey;        // 0x0137e8e0

extern const char kNameFormat[];            // 0x013f5b98
extern const char kSerializerName[];        // 0x01a80d26
extern const uint32_t kSerializerKey;       // 0x0157cac8
extern const uint8_t kPropIdCivTutorial;    // 0x04ea96cb
extern const uint8_t kCivTutSeen;           // 0x064e6678
extern const uint8_t kCivTutNext;           // 0x064e6679

extern const float kModeScaleA;             // 0x01474900
extern const float kModeScaleB;             // 0x01474904
extern const float kModeScaleC;             // 0x01474908
extern const float kModeScaleD;             // 0x0147490c
extern const float kExtraRadius;            // 0x013eb95c
extern const float kAreaScale;              // 0x013ec5b4
extern const float kTwo;                    // 0x01470f1c
extern const float kHalf;                   // 0x01471064
extern const float kRealOne;                // 0x01485720

extern const uint32_t kRadiusTable1[];      // 0x01474a28
extern const uint32_t kRadiusTable2[];      // 0x014749ec

// --- library / engine entry points --------------------------------------------------------------
const void* GetCurrentGameMode();           // 0x00b5b800
cGameNounManager* NounManager();            // 0x00b3d300
cPlanetModel* PlanetModel();                // 0x00b3d350
cConfigManager* ConfigManager();            // 0x0067dd30
cCivModeStrategy* CivModeStrategyGet();     // 0x00cf74c0
void StringSprintf(cString* out, const char* fmt, ...);                  // 0x00472fe0
void PropertyPairRead(const uint32_t* pair, float* outFirst, float* outSecond);  // 0x00eed0b0
void WriteUint32(uint32_t handle, uint32_t* pValue, int count, int flags);  // 0x0093aa70

struct DefaultRefCounted {
    virtual ~DefaultRefCounted();           // +0x00 (scalar deleting destructor)
    int mnRefCount;                         // +0x04
};

// @ 0x00c9e530
void DestroyTribeToolData()
{
    if (!gTribeToolsLoaded)
        return;
    for (unsigned i = 0; i < 12; ++i) {
        cTribeToolData* pTool = gTribeTools[i];
        if (pTool) {
            pTool->mText.~cString();
            DefaultRefCounted* pAbility = pTool->mAbility.mpObject;
            if (pAbility) {
                unsigned refs = pAbility->mnRefCount;
                refs += -1;
                pAbility->mnRefCount = refs;
                if (refs == 0) {
                    pAbility->mnRefCount = 1;
                    delete pAbility;
                }
            }
            EASTL_allocator_deallocate(pTool);
        }
        gTribeTools[i] = 0;
    }
    gTribeToolsLoaded = false;
}

// @ 0x00c9e5a0
void cLoco::FormatName(cString* out)
{
    // mLoco sits at +0x34 of the complete vehicle object.
    cVehicle* pOwner = (cVehicle*)((char*)this - 0x34);
    StringSprintf(out, kNameFormat, pOwner->Slot5c());
}

// @ 0x00c9e5d0
void TryCivModeTutorial()
{
    if (!ConfigManager()->Slot30((uint32_t)&kPropIdCivTutorial))
        return;
    cCivModeStrategy* pStrategy = CivModeStrategyGet();
    if (pStrategy->HasCivTutorialOccurred((uint32_t)&kCivTutSeen))
        pStrategy->DoNext((uint32_t)&kCivTutNext, 1);
}

// @ 0x00c9e610
cVehicle* cVehicle::Find(uint32_t id)
{
    if (id != (uint32_t)&gNullObjectKey) {
        cVehicle* pFound;
        if ((pFound = (cVehicle*)mLoco.Find(id)) != 0)
            return pFound;
        if ((pFound = (cVehicle*)BaseFind(id)) != 0)
            return pFound;
        if ((pFound = (cVehicle*)mCombatant.Find(id)) != 0)
            return pFound;
        if ((pFound = (cVehicle*)mChild650.Find(id)) != 0)
            return pFound;
        if ((pFound = (cVehicle*)mChild638.Find(id)) != 0)
            return pFound;
        return (cVehicle*)mChild5d0.Find(id);
    }
    return this;
}

// @ 0x00c9e690
bool cLoco::IsLocalPlayer()
{
    if (GetCurrentGameMode() == &gModeTen)
        return false;
    // mLoco sits at +0x34 of the complete vehicle object.
    cVehicle* pOwner = (cVehicle*)((char*)this - 0x34);
    return pOwner->Slot4c() == NounManager()->GetPlayerEmpireOrMinus1();
}

// @ 0x00c9e6d0
uint32_t RadiusTableValue(int a, int b)
{
    if (GetCurrentGameMode() == &gModeFive)
        return kRadiusTable1[b];
    return kRadiusTable2[a * 3 + b];
}

// @ 0x00c9e700
void cVehicle::UpdateDamageState()
{
    if (GetCurrentGameMode() != &gModeFour)
        return;
    if (!mLoco.Slot58())
        return;
    if (kModeScaleA < mCombatant.GetValue())
        return;
    if (mCombatant.GetValue() > 0.0f)
        NounManager()->GetPlayerCivilization()->mField430 = 1;
}

// @ 0x00c9e760
void cVehicle::WriteAsText(void* ar)
{
    BaseWriteAsText(ar);
    if (mField77c > 100)
        mField778 = mField774;
    mField77c = 0;
}

// @ 0x00c9e790
bool cVehicle::RemoveOwner(int owner)
{
    if (!Slot14())
        return false;
    return BaseRemoveOwner() ? true : false;
}

// @ 0x00c9e7c0
float cVehicle::GetHealthFraction()
{
    float value = mCombatant.mValue;
    float ratio = value / mCombatant.GetFraction();
    float lo = 0.0f;
    float hi = kRealOne;
    ratio = ratio > lo ? ratio : lo;
    ratio = ratio < hi ? ratio : hi;
    return NounManager()->Func00b25f40(Slot4c())->Func00bf2170(mFieldB20, mFieldB1c) * (ratio * kHalf);
}

// @ 0x00c9e8a0
void cVehicle::GetC3C(Float3* out, float* a, float* b)
{
    *out = mVecC3c;
    *a = mFieldC48;
    *b = mFieldC4C;
}

// @ 0x00c9e8e0
bool TerrainFlagForType(int type, int data)
{
    cPlanetModel* pModel = PlanetModel();
    switch (type) {
    case 0:
        return (int)(pModel->GetAverageRadius(data) & 0x98000000) != 0;
    case 1:
        return (int)(pModel->GetAverageRadius(data) & 0x58000000) != 0;
    case 2:
        return ((~(pModel->GetAverageRadius(data) >> 29)) & 1) != 0;
    }
    return true;
}

// @ 0x00c9e960
bool cVehicle::CanOccupyTerrain(int data)
{
    if (!TerrainFlagForType(mFieldB1c, data))
        return false;
    if (mFieldB1c == 2)
        return true;
    cPlanetModel* pModel = PlanetModel();
    int continent = pModel->GetContinent(mLoco.Slot2c());
    return continent == pModel->GetContinent(data);
}

// @ 0x00c9e9e0
bool cVehicle::Write(cArchive* ar)
{
    uint32_t value = (uint32_t)&gNullObjectKey;
    WriteUint32(ar->Slot20()->GetHandle(), &value, 1, 0);
    bool ok = BaseWrite(ar) && mCombatant.Write(ar) && mLoco.Write(ar);
    cVarListSerializer serializer(this, kSerializerKey, kSerializerName);
    return serializer.Serialize(ar) && ok;
}

// @ 0x00c9eaf0
int cVehicle::GetMode()
{
    if (mFieldD04 != 0)
        return 6;
    switch (mFieldB1c) {
    case 0: {
        uint8_t low = mFieldAF8;
        uint8_t inverted = ~low;
        return (inverted >> 2) & 1;
    }
    case 1:
        return 2;
    }
    if (mPairIdB == 0x476a98c7)
        return 7;
    if (mFieldAF8 & 1)
        return 4;
    int masked = (mFieldAF8 & 2) != 0;
    return 3 + masked * 2;
}

// @ 0x00c9eb60
float ModeRadiusScale()
{
    if (GetCurrentGameMode() == &gModeTen)
        return kModeScaleC;
    return kModeScaleB;
}

// @ 0x00c9eb80
float cVehicle::GetModeRadius()
{
    // the carrier type is read before each GetMode call in the retail code; the volatile access keeps
    // this load ordered in front of the call (GetMode may clobber ecx on some paths).
    int type = ((volatile const cVehicle*)this)->mFieldB1c;
    float radius;
    if (type == 2) {
        if (GetMode() == 7)
            return kModeScaleD;
        if (GetCurrentGameMode() == &gModeTen)
            radius = kModeScaleC;
        else
            radius = kModeScaleB;
        return radius;
    }
    if (GetMode() == 1)
        return kExtraRadius;
    return 0.0f;
}

// @ 0x00c9ec00
float cVehicle::GetFraction()
{
    float a, b;
    PropertyPairRead(&mPairIdA, &b, &a);
    return mLoco.Slot34() / (a - b);
}

// @ 0x00c9ec50
float cVehicle::GetArea()
{
    return (float)(mFieldB90 * mFieldB90) * kAreaScale;
}

// @ 0x00c9ec80
void cVehicle::SetDrone(bool on)
{
    mFieldBCE = (uint8_t)on;
    if (on)
        mpFieldAF0->mFlagsView.mFlags |= 0x40;
    else
        mpFieldAF0->mFlagsView.mFlags &= ~0x40u;
}

// @ 0x00c9ecb0
void cVehicle::SetJustEyeCandy(bool on)
{
    if (on)
        mpFieldAF0->mFlagsView.mFlags |= 0x80;
    else
        mpFieldAF0->mFlagsView.mFlags &= ~0x80u;
}

// @ 0x00c9ece0
void cLoco::SetValue(float v, int n)
{
    SetProperty(v, n);
}

// @ 0x00c9ed00
int WeaponClassFromHash(uint32_t hash)
{
    switch (hash) {
    case 0x9ad7d4aa: case 0xbc1041e6: case 0xc0b74287: case 0xf670aa43:
        return 0;
    case 0x8f963dcb: case 0xc15695da: case 0x1f2a25b6: case 0x2a5147a9:
        return 1;
    case 0x1a4e0708: case 0x98e03c0d: case 0x441cd3e6: case 0x2090a11b: case 0x449c040f:
        return 2;
    }
    return 0;
}

// @ 0x00c9ed80
int WeaponSlotFromHash(uint32_t hash)
{
    switch (hash) {
    case 0x8f963dcb: case 0x98e03c0d: case 0x441cd3e6: case 0x7d433fad:
        return 0;
    case 0xbc1041e6: case 0xc15695da: case 0x2090a11b:
        // the retail code resolves the game mode here; both outcomes are 0
        if (GetCurrentGameMode() == &gModeTen)
            return 0;
        return 0;
    case 0x9ad7d4aa: case 0x1f2a25b6: case 0x449c040f:
        return 1;
    case 0x1a4e0708: case 0xf670aa43: case 0x2a5147a9:
        return 2;
    case 0xc0b74287:
        return 3;
    }
    return 0;
}

// @ 0x00c9ee30
void cVehicle::SetTimer(int v)
{
    mFieldD28 = (uint32_t)v;
    mFieldD24 = (uint32_t)v;
}

// @ 0x00c9ee50
void cVehicle::ConsumeTimer()
{
    mFieldD24 = mFieldD28;
    mFieldD28 = 0;
}

// @ 0x00c9eea0
void cVehicle::PlaySomething()
{
    mpFieldAF0->mChild.Func(0x1000, 0, kTwo, 0);
}

// @ 0x00c9eed0
bool cVehicle::HasBit2000()
{
    uint32_t bits = mpField5e8->mBits & 0x2000;
    uint32_t extra = 0;
    return (bits | extra) != 0;
}

// @ 0x00c9eef0
bool cVehicle::IsFlying()
{
    switch (mFieldB1c) {
    case 0:
        return ((~(mFieldAF8 >> 2)) & 1) != 0;
    case 1:
        return true;
    case 2:
        return true;
    }
    return false;
}
