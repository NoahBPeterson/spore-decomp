// src/game/SPGonzago/SPMissionFetch.cpp -- migrated from slice(s) s00c54f90, s00c54110, s0133ed00, s00c53180, s00c52080 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPMissionFetch.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cPlanet.h"
#include "SP/cPropertyList.h"
#include "SP/cDataSerializationInfo.h"
#include "EA/Variant.h"
#include "SP/cPropertyManager.h"
#include "SP/cSPMission.h"
#include "SP/cSpeciesProfile.h"
#include "SP/cString.h"
#include "SP/cVarListSerializer.h"
#include "EA/ResourceMan/Key.h"
#include "SP/cGameNounManager.h"

// ---- items of slice s00c52080 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char u8;
typedef unsigned int  u32;
void __cdecl operator_delete_array(void* p);      // 0x00f47380
struct cProperty {
    u8    mPad0000[0x12];
    unsigned short mType12;        // 0x12  property data type (1 = bool, 0xd = float)
    bool* GetBool();               // 0x0041e920
    float* GetFloat();             // 0x0041ea70
};
struct cPropertyList {
    // vtable slot 9 (offset 0x24), true when the key exists
    bool GetProperty(int key, cProperty** out);
};
inline bool cPropertyList::GetProperty(int key, cProperty** out)
{
    return ((bool (__thiscall*)(cPropertyList*, int, cProperty**))
            (*(void***)this)[9])(this, key, out);
}
struct cAllocHeader {
    int mSize;                     // -0x04 from the payload
};
static inline int AllocSize(void* payload)
{
    return ((cAllocHeader*)payload)[-1].mSize;
}
struct cVec3 {
    float x;                       // 0x00
    float y;                       // 0x04
    float z;                       // 0x08
};
struct cVec3Vector {
    cVec3* mpBegin;                // 0x00
    cVec3* mpEnd;                  // 0x04
};
static inline int VT_60_0(void* p)
{
    return ((int (__thiscall*)(void*))(*(void***)p)[0x18])(p);
}
static inline void VT_1A4_1(void* p, int a)
{
    ((void (__thiscall*)(void*, int))(*(void***)p)[0x69])(p, a);
}
static inline void VT_6C_0(void* p)
{
    ((void (__thiscall*)(void*))(*(void***)p)[0x1b])(p);
}
static inline void VT_70_0(void* p)
{
    ((void (__thiscall*)(void*))(*(void***)p)[0x1c])(p);
}
struct cCommManager {
    void RemoveMatching();         // 0x00aea720
};
cCommManager* __stdcall GetCommManager(int a, int b, void* owner);   // 0x00b3d4a0
struct cPlanetCounts {
    u8  mPad00bc[0xbc];
    int mBc;                       // 0xbc
    int mC0;                       // 0xc0
    u8  mPad00c4[0xd0 - 0xc4];
    int mD0;                       // 0xd0
    int mD4;                       // 0xd4
};
struct cPlanet {
    u8             mPad0000[0x13c];
    cPlanetCounts* mpCounts13c;    // 0x13c
};
struct cPlayerInventory {
    u8           mPad0000[0x718];
    cVec3Vector  mItems718;        // 0x718
};
struct cSPSimulatorSpaceGame {
    cPlayerInventory* GetPlayerInventory();   // 0x00a1ad60
};
cSPSimulatorSpaceGame* __cdecl GetUFOSimulator();    // 0x00ffbe50
cVec3* __cdecl FindInventoryItem(cVec3* out, cVec3Vector* list,
                                 cVec3Vector* inventory);  // 0x00c4bdc0
struct cSPMissionFetch {
    u8              mPad0000[0x78];
    u32             mField78;               // 0x78
    u8              mPad007c[0x80 - 0x7c];
    int             mField80;               // 0x80
    u8              mPad0084[0x130 - 0x84];
    u32             mFlags130;              // 0x130
    u8              mPad0134[0x17c - 0x134];
    void*           mpField17c;             // 0x17c
    cPropertyList*  mpPropertyList180;      // 0x180
    u8              mPad0184[0x1f0 - 0x184];
    int             mState1f0;              // 0x1f0
    u32             mTag1f4;                // 0x1f4
    u8              mPad01f8[0x234 - 0x1f8];
    void*           mpData234;              // 0x234
    u8              mPad0238[0x248 - 0x238];
    bool            mFlag248;               // 0x248
    float           mValue24c;              // 0x24c
    void*           mpData250;              // 0x250

    bool  IsActive();                       // 0x00c44c80
    void  GetText(int key, void* out);      // 0x00c487d0
    bool  GetTagString(int tag, void* out); // 0x00c491c0
    void  ProcessTagOut(int out);           // 0x00c49140
    int   GetResponseValue();               // 0x00c44cb0
    int   CalculateDuration();              // 0x00c45a10
    cPlanet* GetTargetPlanet();             // 0x00970b30
    void  ValidateProgressEvent();          // 0x00c44f20
    void  TriggerUIUpdate();                // 0x00c47d80
    void  AfterUpdate();                    // 0x00c472e0
    void  FinishUpdate();                   // 0x00c471c0
    ~cSPMissionFetch();                     // (destructor under test)

    bool  GetTagValue(int tag, void* out);          // 0x00c52080
    int   GetConversationGroupID();                 // 0x00c520d0
    int   GetProgressTextID();                      // 0x00c52130
    void  GetUIMediumDescription(void* out);        // 0x00c52160
    void  GetUILongDescription(void* out);          // 0x00c521c0
    void  ReadDropOffFields();                      // 0x00c52580
    bool  IsHighlighted();                          // 0x00c52600
    int   UpdateDuration();                         // 0x00c528a0
    void  EnterConversationState();                 // 0x00c52e30
    void  EnterStateTwo();                          // 0x00c52ea0
    cSPMissionFetch* Destroy(char flags);           // 0x00c53120
};
struct cFlagState {
    bool mEnabled;                 // 0x00
    u8   mPad0001[3];
};
void __cdecl SP_SetMissionFlag(void* a, void* b, cFlagState state);   // 0x00c52d80
// ---- items of slice s00c52080 end

// ---- items of slice s00c53180 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define VSLOT(n) virtual void _v##n();
class Key {
public:
    uint32_t mInstance;   // +0x00
    uint32_t mType;       // +0x04
    uint32_t mGroup;      // +0x08
};
struct cSPVector3_s00c5_3180 {
    float x, y, z;
};
struct cFetchSample {
    bool mIsAnimal;       // +0x00
    Key mSpeciesKey;      // +0x04
};
struct Quad16;
Quad16* copy(const Quad16* first, const Quad16* last, Quad16* dest);
class WString {
public:
    wchar_t* mpBegin;      // +0x00
    wchar_t* mpEnd;        // +0x04
    wchar_t* mpCapacity;   // +0x08
    WString();                                         // 0x00933910
    WString(const wchar_t* pStr);                      // 0x0041df50
    ~WString();                                        // 0x00933960
    WString& operator=(const WString& rhs);            // 0x0057cb60
    void assign(const wchar_t* first, const wchar_t* last); // 0x00423650
};
class cString {
public:
    uint32_t mnTableId;    // +0x00
    uint32_t mnKey;        // +0x04
    const wchar_t* mpText; // +0x08
    cString();                                  // 0x006b5060
    ~cString();                                 // 0x006b5240
    const wchar_t* GetText();                   // 0x006b55c0
};
class cFetchSampleVector {
public:
    cFetchSample* mpBegin;     // +0x00
    cFetchSample* mpEnd;       // +0x04
    cFetchSample* mpCapacity;  // +0x08
    cFetchSample* DoInsertValue(cFetchSample* pos, const cFetchSample& value); // 0x00c19d10
    void Reserve(uint32_t nCount);                                             // 0x00c53690
    void push_back(const cFetchSample& value);                                 // 0x00c53a50
    void clear();                                                              // 0x00c53a90
};
class cItemList {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7)
    VSLOT(8) VSLOT(9) VSLOT(10) VSLOT(11)
    Key* GetKeys();                // 0x00446ff0
    uint32_t mnPad04;              // +0x04
    int32_t mnCount;               // +0x08
    uint32_t mnPad0c;              // +0x0c
    uint8_t mnFlags;               // +0x10
    uint8_t mnPad11;               // +0x11
    uint16_t mnCount2;             // +0x12
};
class cPropertyList_s00c5_3180 {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7)
    VSLOT(8) VSLOT(9)
    virtual cItemList* FindItems(uint32_t nId);      // +0x28
    virtual void _v2c();
};
class cPropertyValue {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3)
    uint32_t mnPad04;              // +0x04
    int32_t mnValue;               // +0x08
};
class cPropertyManager {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7)
    VSLOT(8) VSLOT(9) VSLOT(10)
    virtual void GetProperty(uint32_t nKey, uint32_t nId, cPropertyValue** ppValue); // +0x2c
};
class cInventoryItem {
public:
    VSLOT(0) VSLOT(1)
    virtual void Release();                          // +0x08
    VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8)
};
class cInventory {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7)
    VSLOT(8) VSLOT(9) VSLOT(10) VSLOT(11) VSLOT(12) VSLOT(13) VSLOT(14)
    VSLOT(15) VSLOT(16) VSLOT(17) VSLOT(18) VSLOT(19) VSLOT(20) VSLOT(21)
    VSLOT(22) VSLOT(23) VSLOT(24) VSLOT(25) VSLOT(26) VSLOT(27) VSLOT(28)
    VSLOT(29) VSLOT(30)
    virtual void AddItem(cInventoryItem* pItem, int32_t nCount, int32_t nFlags); // +0x80
};
class cCommManager_s00c5_3180 {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7)
    VSLOT(8) VSLOT(9)
    virtual bool IsActive();                                   // +0x28
    VSLOT(11) VSLOT(12) VSLOT(13) VSLOT(14) VSLOT(15) VSLOT(16) VSLOT(17)
    VSLOT(18) VSLOT(19) VSLOT(20) VSLOT(21) VSLOT(22) VSLOT(23) VSLOT(24)
    VSLOT(25) VSLOT(26)
    virtual void RemoveMatching(int32_t a, int32_t b, void* pMission); // +0x6c
};
class cSpeciesProfile {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5)
    virtual Key* GetSpeciesKey();                            // +0x18
    VSLOT(7) VSLOT(8)
    virtual cInventoryItem* MakeInventoryItem(void* pName);  // +0x24
    virtual const wchar_t* GetName();                        // +0x28
    uint8_t mnPad04[0x500];       // +0x004
    Key mSpeciesKey;              // +0x504
    uint8_t mnPad510[0x0c];       // +0x510
    const wchar_t* mpDisplayName; // +0x51c
};
class cSpeciesManager {
public:
    cSpeciesProfile* GetSpeciesFromID(const Key* pKey);      // 0x00b90410
};
class cPlanetEco {
public:
    Key* GetCommodityKey();    // 0x00b8dad0
    Key* GetAnimalKey();       // 0x00b8e090
};
class cPlanet_s00c5_3180 {
public:
    uint8_t mnPad00[0xbc];     // +0x000
    Key* mpPlantKeysBegin;     // +0x0bc
    Key* mpPlantKeysEnd;       // +0x0c0
    uint8_t mnPadC4[0x0c];     // +0x0c4
    Key* mpAnimalKeysBegin;    // +0x0d0
    Key* mpAnimalKeysEnd;      // +0x0d4
    uint8_t mnPadD8[0x64];     // +0x0d8
    cPlanetEco* mpEco;         // +0x13c
    cSpeciesProfile* GetRandomAnimalSpecies();   // 0x00c70c10
    cSpeciesProfile* GetRandomPlantSpecies();    // 0x00c70c90
};
class cSpaceGame {
public:
    cInventory* GetPlayerInventory();            // 0x00a1ad60
};
class cSPMission {
public:
    uint8_t mnPad00[0x78];           // +0x000
    float mRewardMoney;              // +0x078
    uint8_t mnPad7c[0xd0];           // +0x07c
    WString mUIText;                 // +0x14c
    uint8_t mnPad158[0x24];          // +0x158
    cSPMission* mpParentMission;     // +0x17c
    cPropertyList_s00c5_3180* mMissionPropList; // +0x180
    int32_t mGiveOnAcceptMoney;      // +0x184
    uint8_t mnPad188[0x68];          // +0x188
    int32_t Update(int32_t nDelta);                        // 0x00c478b0
    void TriggerUIUpdate();                                // 0x00c47d80
    void ValidateProgressEvent();                          // 0x00c44f20
    void Fulfill();                                        // 0x00c2e4e0
    cPlanet_s00c5_3180* GetTargetPlanet();                            // 0x00970b30
    void GetText(uint32_t nTextId, WString* pOut);         // 0x00c487d0
};
class cSPMissionFlight101 : public cSPMission {
public:
    void ValidateHerds();                        // 0x00c55ca0
};
class cSPMissionFetch_s00c5_3180 : public cSPMission {
public:
    int32_t mFetchMissionState;          // +0x1f0
    uint32_t mTypeOfFetch;               // +0x1f4
    Key mFetchArtifactCargoItemID;       // +0x1f8
    cSPVector3_s00c5_3180 mFetchArtifactPos;        // +0x204
    Key mFetchPlantSpeciesKey;           // +0x210
    Key mFetchAnimalSpeciesKey;          // +0x21c
    Key mFetchCommodityKey;              // +0x228
    cFetchSampleVector mSamplerPlate;    // +0x234
    uint8_t mnPad240[0x08];              // +0x240
    bool mDropOffRequired;               // +0x248
    uint8_t mnPad249[0x03];              // +0x249
    float mDropOffDistance;              // +0x24c
    int32_t Update(int32_t nDelta);                     // 0x00c53180
    void Fulfill();                                     // 0x00c532d0
    void GetUIShortDescription(WString* pOut);          // 0x00c53720
    void GetFetchItemName(WString* pOut);               // 0x00c53800
    bool PickFetchItem();                               // 0x00c53bc0
    bool IsSatisfied();                                 // 0x00c52a70
    void OnComplete();                                  // 0x00c52ea0
    void SetFetchState(int32_t nState);                 // 0x00c5ed90
    void Expire();                                      // 0x00c471c0
};
class cDataSerializationInfo {
public:
    uint8_t mnData[0x14];
};
class cVarListSerializer {
public:
    cDataSerializationInfo mDataSerializationInfos[128]; // +0x0000
    int32_t mSerializableVarCount;                       // +0x0a00
    int32_t mSerializedVarCount;                         // +0x0a04
    uint32_t mSignature;                                 // +0x0a08
    void* mpObject;                                      // +0x0a0c
    void* mpSerializerList;                              // +0x0a10
    cVarListSerializer(void* pObject, const char* pName, uint32_t nSignature); // 0x00692f90
    void Serialize(void* pSerializer);                                         // 0x00693e10
};
class cSerializedObject {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5)
    virtual void* GetStream();                 // +0x18
};
class cSerializer {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6)
    virtual void End();                        // +0x1c
    virtual cSerializedObject* GetObject();    // +0x20
};
class cUniverseContext {
public:
    bool IsArchived();     // 0x00bba900
    bool IsPlanet();       // 0x00bb9d40
};
void EA_IO_ReadInt32(void* pStream, uint32_t* pValue, int32_t nCount, int32_t nFlags); // 0x0093a780
const Key* EmptyKey();                                     // 0x016907d4 (three dwords)
cPropertyManager* PropertyManager();                       // 0x0067de30
void GetPropertyAsText(cPropertyValue* pValue, uint32_t nId, cString* pOut); // 0x006a1360
cSpeciesManager* PlantSpeciesManager(const Key* pKey);     // 0x00b3d420
cSpeciesManager* AnimalSpeciesManager(const Key* pKey);    // 0x00b3d450
cSpeciesProfile* GetSpeciesProfile(const Key* pKey);       // 0x004df550
cInventoryItem* MakeInventoryItemFromKey(const Key* pKey); // 0x00ac0cb0
cInventoryItem* MakeArtifactFromKey(Key* pKey);            // 0x00c878d0
void AddCommodityToInventory(const Key* pKey, int32_t nCount); // 0x00b3d3d0
cSpaceGame* SpaceGameGet();                                // 0x01002bd0
cCommManager_s00c5_3180* CommManager();                               // 0x00b3d4a0
void* GetPlayerProperty(void* pInventory);                 // 0x00ff3f00
bool CompareDeclareParam(void* a, void* b);                // 0x004eb930
bool PlayerHasDropCargo(void* pObject);                    // 0x0104bd50
void* GetSetting9(const Key* pKey);                        // 0x00401090
void* MakeNameString(void* p);                             // 0x00c463d0
int32_t GetUniverseContext();                              // 0x01021080
cUniverseContext* GetArchivedContext();                    // 0x01021240
cUniverseContext* GetActivePlanetRecord();                 // 0x010212a0
uint32_t RandomUint32Uniform(uint32_t nRange);             // 0x00a68fb0
void* GetPlanetCapability(cPlanet_s00c5_3180* pPlanet);               // 0x008414c0
cSPMissionFlight101* GetSubMission(cSPMission* pParent, uint32_t nId); // 0x0042227d
// ---- items of slice s00c53180 end

// ---- items of slice s0133ed00 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef void (*AttrFn)();
struct Attribute {
    const char* mpName;    // +0x00  attribute name ("mHealth", ...)
    u32         mKey;      // +0x04  hashed property key
    u32         mOffset;   // +0x08  byte offset of the member in the owner
    u32         mUnk0c;    // +0x0c  uninitialised in the original
    u32         mUnk10;    // +0x10  uninitialised in the original
    u32         mUnk14;    // +0x14  uninitialised in the original
    u32         mFlags18;  // +0x18  always 0
    u32         mFlags1c;  // +0x1c  always 0
    AttrFn      mpfn20;    // +0x20  default/offset accessor (0x692ca0)
    AttrFn      mpfn24;    // +0x24  writer/reader A
    AttrFn      mpfn28;    // +0x28  writer A
    AttrFn      mpfn2c;    // +0x2c  parser/reader A
    AttrFn      mpfn30;    // +0x30  parser A
    AttrFn      mpfn34;    // +0x34  init hook (0xb1fbf0)
    AttrFn      mpfn38;    // +0x38  serialiser
};
Attribute s_fetchAttrs[9];            // 0x01575bd8
#define ATTR(dst, nm, k, off, f0, f1, f2, f3, f4, f5, f6)          \
    do {                                                           \
        Attribute t;                                               \
        t.mpName = (nm);                                           \
        t.mKey = (k);                                              \
        t.mFlags18 = 0;                                            \
        t.mFlags1c = 0;                                            \
        t.mpfn20 = (AttrFn)(f0);                                   \
        t.mpfn24 = (AttrFn)(f1);                                   \
        t.mpfn28 = (AttrFn)(f2);                                   \
        t.mpfn2c = (AttrFn)(f3);                                   \
        t.mpfn30 = (AttrFn)(f4);                                   \
        t.mpfn34 = (AttrFn)(f5);                                   \
        t.mpfn38 = (AttrFn)(f6);                                   \
        t.mOffset = (off);                                         \
        (dst) = t;                                                 \
    } while (0)
// ---- items of slice s0133ed00 end

// ---- items of slice s00c54110 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern wchar_t gEmptyWString[]; // 0x01667bac
struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(const Vec3& o) { x = o.x; y = o.y; z = o.z; }
};
struct Key_s00c5_4110  { uint32_t a, b, c; };
extern Vec3 gDefaultPos;   // 0x016907c8
extern Key_s00c5_4110  gNullKey;      // 0x016907d4
struct WStr {
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity; uint32_t mAlloc;
    WStr() { mpBegin = gEmptyWString; mpEnd = gEmptyWString; mpCapacity = gEmptyWString + 1; }
    void DeallocateSelf();            // 0x00933960
    ~WStr() { DeallocateSelf(); }
};
struct Msg { uint32_t f0; uint32_t f4; uint8_t* src; uint32_t fc; void* f10; uint32_t f14; uint32_t f18; };
struct PosProv {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
    virtual void v10();
    virtual Vec3* GetPos();           // slot 0x2c
};
struct Mission {
    void  TriggerUIUpdate();                 // 0x00c47d80
    void* GetTargetPlanet();                 // 0x00970b30
    void* GetModel();                        // 0x00c45ce0
    void* GetOwnerEmpire();                  // 0x00c451e0
    void  GetText(uint32_t key, WStr* out);  // 0x00c487d0
    void  PostEvent(void* ev);               // 0x00c48e50
    void  FUN_00c5ed90(int a);               // 0x00c5ed90
    void  FUN_00c47180(void* planet);        // 0x00c47180
    void  Complete();                        // 0x00c52ea0
};
struct Avatar {
    void* SpawnArtifact(void* params);       // 0x00ff5d20
};
struct GameNounMgr {
    Avatar* GetAvatar();                     // 0x00b1fdb0
};
struct SpecimenMgr {
    void* Lookup(Msg* m);                    // 0x00b2b1e0
};
struct ArtItem {
    Key_s00c5_4110* GetKey(Key_s00c5_4110* out);                   // 0x00ad2620
};
struct PlantItem {
    Key_s00c5_4110* GetKey(Key_s00c5_4110* out);                   // 0x00c3e1e0
};
struct AnimItem {
    Key_s00c5_4110* GetKey();                           // 0x00c0bc00
};
struct VecP { uint8_t** b; uint8_t** e; };
struct NounMgr {
    VecP* GetAll();                          // 0x00ace2c0
};
struct EventLog {
    void* PostFeedbackEvent(uint32_t a, uint32_t b, int c, int d, int e, int f);  // 0x00dd8640
    void  ModifyEventText(void* ev, wchar_t* text);                               // 0x00dd6df0
};
struct CommMgr {
    void AddEntry(int empire, int ctx, int text, uint32_t key, void* obj, int a, int b); // 0x00aeb160
};
struct StarRec {
    int GetCommContext();                    // 0x00ce6950
};
struct Vec3Vec {
    void push_back(const Vec3* v);           // 0x004739d0
};
void*  __cdecl GetActivePlanet();                  // 0x01021260
GameNounMgr* __cdecl SpaceGameGet_s00c5_4110();               // 0x01002bd0
NounMgr* __cdecl GetNounManager();                 // 0x00b3d300
SpecimenMgr* __cdecl GetSpecimenMgr();             // 0x00b3d3b0
EventLog* __cdecl GetEventLog();                   // 0x00b3d3e0
CommMgr* __cdecl GetCommManager();                 // 0x00b3d4a0
bool   __cdecl KeyEq(const Key_s00c5_4110* a, const Key_s00c5_4110* b);  // 0x004eb930
bool   __cdecl KeyNe(const Key_s00c5_4110* a, const Key_s00c5_4110* b);  // 0x005f78f0
Vec3*  __cdecl FindVec3(Vec3* first, Vec3* last, const Vec3* v);  // 0x00c52d30
ArtItem*   __cdecl CastArt(void* p);               // 0x00c52220
PlantItem* __cdecl CastPlant(void* p);             // 0x00c52240
AnimItem*  __cdecl CastAnimal(void* p);            // 0x00c52260
AnimItem*  __cdecl CastAnimal2(void* p);           // 0x00c4bbe0
bool   __cdecl IsItemARare(Key_s00c5_4110* k);                // 0x0103a3c0
struct SpawnParams {
    uint32_t a; Key_s00c5_4110 pos; uint16_t w; uint8_t b12; uint8_t pad; float f; uint32_t g[4]; uint8_t t28;
};
struct FetchHandler {
    void HandleMessage(uint32_t msg, Msg* m);
    void BaseHandleMessage(uint32_t msg, Msg* m);   // 0x00c4a6b0 cSPMission::HandleMessage

    template<class T> T& F(int off) { return *(T*)((char*)this + off); }
    Mission* Mis() { return (Mission*)((char*)this - 0x34); }
};
static inline int SlotId(Mission* mi) {
    return ((int(__thiscall*)(Mission*))(*(void***)mi)[0xa4 / 4])(mi);
}
struct TerraMgr;
struct PickParams {
    uint32_t mType;              // +0x00
    uint32_t mEa;                // +0x04
    uint32_t mEb;                // +0x08
    uint8_t  mB0c;               // +0x0c
    uint8_t  mB0d;               // +0x0d
    uint8_t  mB0e;               // +0x0e
    uint8_t  mB0f;               // +0x0f
    uint32_t mCost;              // +0x10
    uint32_t mCost2;             // +0x14
    uint32_t mFlags;             // +0x18
    uint32_t mFlags2;            // +0x1c
    uint32_t mF20;               // +0x20
    uint32_t mF24;               // +0x24
    uint32_t mF28;               // +0x28
    uint32_t mF2c;               // +0x2c
    uint32_t mF30;               // +0x30
    uint32_t mPlanet;            // +0x34
    uint32_t mF38;               // +0x38
    uint32_t mF3c;               // +0x3c
    void Ctor();                 // 0x00ba7bd0
    void Dtor();                 // 0x00ba8220
};
struct SpeciesEntry {            // 0x10-byte vector element of +0x234
    uint8_t  mIsEditor;          // +0x00
    uint8_t  mPad01[3];
    Key_s00c5_4110      mKey;               // +0x04
    uint8_t  mPad10[0x10 - 0x04 - sizeof(Key_s00c5_4110)];
};
struct FetchMission {
    // ... [0x000, 0x078) omitted
    uint8_t  mPad000[0x78];
    uint32_t mSubtype;                       // +0x078
    uint8_t  mPad07c[0x180 - 0x7c];
    void*    mpPropTable;                    // +0x180
    uint8_t  mPad184[0x1bc - 0x184];
    int      mStateA;                        // +0x1bc
    uint32_t mSpeciesType;                   // +0x1c0
    uint32_t mFetchType;                     // +0x1c4
    uint8_t  mPad1c8[0x1f0 - 0x1c8];
    int      mValidateState;                 // +0x1f0
    uint32_t mType;                          // +0x1f4
    uint8_t  mPad1f8[0x210 - 0x1f8];
    Key_s00c5_4110      mKeyA;                          // +0x210
    Key_s00c5_4110      mKeyB;                          // +0x21c
    uint8_t  mPad228[0x234 - 0x228];
    SpeciesEntry* mpSpeciesBegin;            // +0x234
    SpeciesEntry* mpSpeciesEnd;              // +0x238

    void ValidateSpecies(Key_s00c5_4110* pKey);         // 0x00c54110
    bool Init();                             // 0x00c54380
    // cSPMission base helpers
    void SetState(int s);                    // 0x00c47cc0
    void FUN_00c48470(Key_s00c5_4110* pKey);            // 0x00c48470
    void FUN_00c53a90();                     // 0x00c53a90
    bool FUN_00c53bc0();                     // 0x00c53bc0
    bool InitBase();                         // 0x00c4ad50 cSPMission::Init
    void ReadDropOffFields();                // 0x00c52580
    uint32_t ReadTargetPlanetType();         // 0x00c45b40
    void* GetPlanetRecordFromTargetType(uint32_t t); // 0x00c474b0
    void FUN_00c47180(void* planet);         // 0x00c47180
    void* GetTargetPlanet();                 // 0x00970b30
    uint32_t ReadTargetAnimalSpeciesType(Key_s00c5_4110* out); // 0x00c45b60
    void GetAnimalSpeciesFromType(uint32_t t, Key_s00c5_4110* out); // 0x00c47610
    void* PickPlanet(PickParams* p);         // 0x00c47e20
    bool HasPickedFetchItem();               // 0x00c52930
    void FUN_00c45250(void* p);              // 0x00c45250
    void FUN_00c4a0c0();                     // 0x00c4a0c0
};
bool  __cdecl KeyEq3(const Key_s00c5_4110* a, const Key_s00c5_4110* b);      // 0x004eb930
void* __cdecl FUN_00401090();                          // 0x00401090 species mgr
void* __cdecl FUN_00b3d420();                          // 0x00b3d420 plant species mgr
struct SpeciesMgr { void* GetByKey(const Key_s00c5_4110* k); };   // 0x004df550 (editor) / 0x00b90410 (plant)
void  __cdecl FUN_00bc1b10(TerraMgr* mgr, void* planet, void* x, void* y); // 0x00bc1b10
void* __cdecl FUN_00b3d3d0(void* p);                   // 0x00b3d3d0
void  FUN_0103aa00(void* p);                           // 0x0103aa00 (thiscall)
void* __cdecl FUN_00c71e30(void* planet);              // 0x00c71e30
bool __cdecl GetPropertyAsKey(void* table, uint32_t id, int* out); // 0x006a1250
typedef void (__thiscall *VFn0)(void* pThis);
typedef bool (__thiscall *VFnB)(void* pThis);
// ---- items of slice s00c54110 end

// ---- items of slice s00c54f90 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* gResourceNone;
typedef int intptr_t;
#define nullptr 0
struct Vec3_s00c5_4f90 {
    float mX;
    float mY;
    float mZ;
};
struct cMethodTable {
    void* mSlots[0x100];
};
struct cDispatchObject {
    cMethodTable* mpMethods;                    // 0x00

    void* Call(int nSlot) {
        return ((void* (*)(void*))mpMethods->mSlots[nSlot >> 2])(this);
    }
    char CallChar(int nSlot) {
        return ((char (*)(void*))mpMethods->mSlots[nSlot >> 2])(this);
    }
    char CallChar1(int nSlot, uint32_t nArg1, void* pArg2) {
        return ((char (*)(void*, uint32_t, void*))mpMethods->mSlots[nSlot >> 2])(this, nArg1,
                                                                                 pArg2);
    }
    void* Call1(int nSlot, uint32_t nArg1) {
        return ((void* (*)(void*, uint32_t))mpMethods->mSlots[nSlot >> 2])(this, nArg1);
    }
    void* Call2(int nSlot, uint32_t nArg1, void* pArg2) {
        return ((void* (*)(void*, uint32_t, void*))mpMethods->mSlots[nSlot >> 2])(this, nArg1,
                                                                                  pArg2);
    }
    void* Call3(int nSlot, uint32_t nArg1, uint32_t nArg2, void* pArg3) {
        return ((void* (*)(void*, uint32_t, uint32_t, void*))mpMethods->mSlots[nSlot >> 2])(
            this, nArg1, nArg2, pArg3);
    }
};
class cSpaceObject {
public:
    uint8_t mPad000[0x120];                     // 0x000
    cDispatchObject mPointingInterface;         // 0x120
};
class cSPMissionFetch_s00c5_4f90 {
public:
    char VerifyTargetPlanet(void* pTarget, void* pOut);
    char SetupHerds();  // 0x00c55b80 (cSPMissionFetch::SetupHerds)
    void* GetTargetPlanet();

    uint8_t mPad000[0x16c];                     // 0x000
    void* mpSelectedHerd;                       // 0x16c
    uint8_t mHerdKeys[0x0c];                    // 0x170
    uint8_t mPad17c[0x74];                      // 0x17c
    int32_t mnState;                            // 0x1f0
    uint32_t mnTargetType;                      // 0x1f4
    uint8_t mPad1f8[0x18];                      // 0x1f8
    uint8_t mToolResource[0x0c];                // 0x210
    uint8_t mSearchA[0x34];                     // 0x21c
    uint8_t mSearchB[0x10];                     // 0x250
};
struct cSearchVector {
    void* mpBegin;                              // 0x00
    void* mpEnd;                                // 0x04
    void* mpCapacity;                           // 0x08
};
class cNounManager {
public:
    cSearchVector* GetAlienSearchList();
    cSearchVector* GetHerdSearchList();
};
void* GetTargetPlanet(void* pMission);
void* NounManager();
char CompareResourceHandle(const void* pHandle, const void* pValue);
void* FindAliensSubMission(void* pSearch, void* pTarget);
void* FindHerdSubMission(void* pSearch, void* pTarget);
void* ProcessAliensSubMission(void* pSearch, void* pOut);
void* ProcessToolSubMission(void* pTool, void* pOut);
void AssignRefCount(void* pDst, void* pValue);
// ---- items of slice s00c54f90 end

// @ 0x00c52080
bool cSPMissionFetch::GetTagValue(int tag, void* out)
{
    if (tag == 0x26eaaa15) {
        VT_1A4_1(this, (int)out);
        return true;
    }
    if (tag == 0x68e2e9c6 && mTag1f4 == 0x69412983) {
        ProcessTagOut((int)out);
        return true;
    }
    return GetTagString(tag, out);
}

// @ 0x00c520d0
int cSPMissionFetch::GetConversationGroupID()
{
    if (VT_60_0(this) == 3) {
        switch (mState1f0) {
        case 0: return (int)0x1a2b6f64;
        case 1: return (int)0x0edce0cd;
        case 2: return (int)0x11965a4d;
        case 3: return (int)0x11fd3bf3;
        }
    }
    return GetResponseValue();
}

// @ 0x00c52130
int cSPMissionFetch::GetProgressTextID()
{
    switch (mState1f0) {
    case 1: return (int)0x96254aee;
    case 2: return (int)0xa2b7bfa8;
    case 3: return (int)0xa2c33a6e;
    }
    return 0;
}

// @ 0x00c52160
void cSPMissionFetch::GetUIMediumDescription(void* out)
{
    if (IsActive()) {
        switch (mState1f0) {
        case 0: GetText(0xd79a86a8, out); break;
        case 2: GetText(0x81128ae1, out); break;
        case 3: GetText(0xa6f2b74a, out); break;
        }
    }
}

// @ 0x00c521c0
void cSPMissionFetch::GetUILongDescription(void* out)
{
    if (IsActive()) {
        switch (mState1f0) {
        case 0: GetText(0x247d8d51, out); break;
        case 2: GetText(0xba93258e, out); break;
        case 3: GetText(0x1ec90679, out); break;
        }
    }
}

// @ 0x00c52580
void cSPMissionFetch::ReadDropOffFields()
{
    mFlag248 = false;
    if (mpPropertyList180 != 0) {
        cProperty* prop;
        if (mpPropertyList180->GetProperty(0x056242c6, &prop)) {
            if (prop->mType12 == 1)
                mFlag248 = *prop->GetBool();
        }
    }
    if (mpPropertyList180 != 0) {
        cProperty* prop;
        if (mpPropertyList180->GetProperty(0x056242c7, &prop)) {
            if (prop->mType12 == 0x0d)
                mValue24c = *prop->GetFloat();
        }
    }
}

// @ 0x00c52600
bool cSPMissionFetch::IsHighlighted()
{
    u32 flags = mFlags130;
    bool b5 = ((flags >> 5) & 1) != 0;
    bool b6 = ((flags >> 6) & 1) != 0;
    if (b5 && !b6)
        return false;
    return true;
}

// @ 0x00c528a0
int cSPMissionFetch::UpdateDuration()
{
    int value = CalculateDuration();
    mField80 = value;
    if (mTag1f4 == 0x23da98ff) {
        cPlanet* planet = GetTargetPlanet();
        if (planet != 0) {
            planet = GetTargetPlanet();
            cPlanetCounts* counts = planet->mpCounts13c;
            int a = (counts->mC0 - counts->mBc) / 12;
            int b = (counts->mD4 - counts->mD0) / 12;
            int cells = a + b;
            mField80 *= cells;
        }
        value = mField80;
    }
    return value;
}

// @ 0x00c52d30
float* FindVec3(float* first, float* last, const float* value)
{
    if (first != last) {
        do {
            if (*first == *value && first[1] == value[1] && first[2] == value[2])
                break;
            first += 3;
        } while (first != last);
    }
    return first;
}

// @ 0x00c52e30
void cSPMissionFetch::EnterConversationState()
{
    if (mState1f0 == 2) {
        void* owner;
        if (mpField17c)
            owner = mpField17c;
        else
            owner = this;
        GetCommManager(-1, -1, owner)->RemoveMatching();
        ValidateProgressEvent();
    }
    VT_70_0(this);
    if (mState1f0 != 3) {
        mState1f0 = 3;
        TriggerUIUpdate();
    }
    AfterUpdate();
    FinishUpdate();
}

// @ 0x00c52ea0
void cSPMissionFetch::EnterStateTwo()
{
    if (mState1f0 != 0 && mState1f0 != 1)
        return;
    VT_6C_0(this);
    if (mState1f0 != 2) {
        mState1f0 = 2;
        TriggerUIUpdate();
    }
    if (mFlag248 && mField78 == 0xbb448992) {
        void* owner;
        if (mpField17c)
            owner = mpField17c;
        else
            owner = this;
        GetCommManager(-1, -1, owner)->RemoveMatching();
    }
    AfterUpdate();
    FinishUpdate();
}

// @ 0x00c52f20
bool FindPlayerItem(cVec3Vector* list, cVec3* out)
{
    if (list->mpBegin != list->mpEnd) {
        cSPSimulatorSpaceGame* sim = GetUFOSimulator();
        cPlayerInventory* inventory = sim->GetPlayerInventory();
        cVec3 local;
        cVec3* item = FindInventoryItem(&local, list, &inventory->mItems718);
        *out = *item;
        return true;
    }
    return false;
}

// @ 0x00c52f80
void SP_SetMissionFlagDefault(void* a, void* b)
{
    cFlagState state;
    state.mEnabled = false;
    SP_SetMissionFlag(a, b, state);
}

// @ 0x00c53120
cSPMissionFetch* cSPMissionFetch::Destroy(char flags)
{
    if (mpData250 != 0 && AllocSize(mpData250) != 0)
        operator_delete_array(mpData250);
    if (mpData234 != 0 && AllocSize(mpData234) != 0)
        operator_delete_array(mpData234);
    this->~cSPMissionFetch();
    if ((flags & 1) != 0)
        operator_delete_array(this);
    return this;
}

// @ 0x00c53180
int32_t cSPMissionFetch_s00c5_3180::Update(int32_t nDelta)
{
    int32_t nResult = cSPMission::Update(nDelta);
    if (nResult != 3)
        return nResult;

    switch (mFetchMissionState) {
    case 0:
        if (IsSatisfied() && !mDropOffRequired) {
            if (!CommManager()->IsActive())
                OnComplete();
        }
        break;
    case 1:
        if (!IsSatisfied()) {
            cInventory* pInventory = SpaceGameGet()->GetPlayerInventory();
            void* pObject = GetPlayerProperty(pInventory);
            if (pObject == 0
                || !(CompareDeclareParam(*(void**)(*(uint8_t**)pObject + 0x18), 0)
                     && PlayerHasDropCargo(pObject))) {
                if (mFetchMissionState != 0) {
                    mFetchMissionState = 0;
                    TriggerUIUpdate();
                }
            }
        }
        break;
    case 2:
        if (!mDropOffRequired && !IsSatisfied())
            SetFetchState(0);
        break;
    default:
        break;
    }

    {
        cSPMission* pParent = mpParentMission != 0 ? mpParentMission : this;
        CommManager()->RemoveMatching(-1, -1, pParent);
        ValidateProgressEvent();
        Expire();
    }

    if (*(const uint32_t*)&mRewardMoney == 0xbb448992 && mpParentMission != 0) {
        cSPMissionFlight101* pFlight = GetSubMission(mpParentMission, 0x0422227d);
        if (pFlight != 0)
            pFlight->ValidateHerds();
    }
    return 3;
}

// @ 0x00c532d0
void cSPMissionFetch_s00c5_3180::Fulfill()
{
    cSPMission::Fulfill();

    switch (mTypeOfFetch) {
    case 0x6d5c48c: {
        cSpeciesManager* pManager = PlantSpeciesManager(&mFetchPlantSpeciesKey);
        cSpeciesProfile* pProfile = pManager->GetSpeciesFromID(&mFetchPlantSpeciesKey);
        if (pProfile == 0)
            break;
        cInventoryItem* pItem = pProfile->MakeInventoryItem(MakeNameString(0));
        SpaceGameGet()->GetPlayerInventory()->AddItem(pItem, 0, 1);
        if (pItem != 0)
            pItem->Release();
        break;
    }
    case 0xbfb44ccc:
        AddCommodityToInventory(&mFetchCommodityKey, 1);
        break;
    case 0xfb3b1635:
    case 0x2dc69129:
    case 0x3e994b2b:
    case 0x69412983: {
        cSpeciesManager* pManager = AnimalSpeciesManager(&mFetchAnimalSpeciesKey);
        cSpeciesProfile* pProfile = pManager->GetSpeciesFromID(&mFetchAnimalSpeciesKey);
        if (pProfile != 0) {
            cInventoryItem* pItem = pProfile->MakeInventoryItem(MakeNameString(0));
            SpaceGameGet()->GetPlayerInventory()->AddItem(pItem, 0, 1);
            if (pItem != 0)
                pItem->Release();
        }
        if (mFetchPlantSpeciesKey.mInstance != EmptyKey()->mInstance
            || mFetchPlantSpeciesKey.mType != EmptyKey()->mType
            || mFetchPlantSpeciesKey.mGroup != EmptyKey()->mGroup) {
            cSpeciesManager* pPlantManager = PlantSpeciesManager(&mFetchPlantSpeciesKey);
            cSpeciesProfile* pPlant = pPlantManager->GetSpeciesFromID(&mFetchPlantSpeciesKey);
            if (pPlant != 0) {
                cInventoryItem* pItem = pPlant->MakeInventoryItem(MakeNameString(0));
                SpaceGameGet()->GetPlayerInventory()->AddItem(pItem, 0, 1);
                if (pItem != 0)
                    pItem->Release();
            }
        }
        break;
    }
    case 0x19ec2c8b: {
        Key key = mFetchArtifactCargoItemID;
        cInventoryItem* pItem = MakeArtifactFromKey(&key);
        if (pItem != 0) {
            SpaceGameGet()->GetPlayerInventory()->AddItem(pItem, 0, 1);
            pItem->Release();
        }
        break;
    }
    case 0x23da98ff: {
        uint32_t nCount = (uint32_t)(mSamplerPlate.mpEnd - mSamplerPlate.mpBegin);
        for (uint32_t i = 0; i < nCount; ++i) {
            cFetchSample* pSample = &mSamplerPlate.mpBegin[i];
            cInventoryItem* pItem = 0;
            if (pSample->mIsAnimal) {
                pItem = MakeInventoryItemFromKey(&pSample->mSpeciesKey);
            } else {
                cSpeciesManager* pManager = PlantSpeciesManager(&pSample->mSpeciesKey);
                cSpeciesProfile* pProfile = pManager->GetSpeciesFromID(&pSample->mSpeciesKey);
                if (pProfile != 0)
                    pItem = pProfile->MakeInventoryItem(MakeNameString(0));
            }
            if (pItem != 0) {
                SpaceGameGet()->GetPlayerInventory()->AddItem(pItem, 0, 1);
                pItem->Release();
            }
        }
        break;
    }
    case 0x7ecbe6f5: {
        Key key;
        key.mInstance = 0x1344c7ff;
        key.mType = 0;
        key.mGroup = 0;
        AddCommodityToInventory(&key, 1);
        break;
    }
    default:
        break;
    }

    OnComplete();
}

// @ 0x00c53720
void cSPMissionFetch_s00c5_3180::GetUIShortDescription(WString* pOut)
{
    if (mUIText.mpBegin == mUIText.mpEnd) {
        uint32_t nTextId;
        cUniverseContext* pContext;
        switch (mFetchMissionState) {
        case 0:
            if (*(const uint32_t*)&mRewardMoney == 0x809ab04a) {
                if (GetUniverseContext() == 1
                    && (pContext = GetArchivedContext()) != 0
                    && pContext->IsArchived()) {
                    nTextId = 0x639f0b00;
                } else if (GetUniverseContext() == 0
                           && (pContext = GetActivePlanetRecord()) != 0
                           && pContext->IsPlanet()) {
                    nTextId = 0x791cfa76;
                } else {
                    nTextId = 0xaad9c0b3;
                }
            } else {
                nTextId = 0xaad9c0b3;
            }
            GetText(nTextId, pOut);
            break;
        case 2:
            GetText(0x4e1f8fa8, pOut);
            break;
        case 3:
            GetText(0x0b4dfecf, pOut);
            break;
        default:
            break;
        }

        if (pOut != &mUIText)
            mUIText.assign(pOut->mpBegin, pOut->mpEnd);
    } else {
        if (pOut != &mUIText)
            pOut->assign(mUIText.mpBegin, mUIText.mpEnd);
    }
}

// @ 0x00c53800
void cSPMissionFetch_s00c5_3180::GetFetchItemName(WString* pOut)
{
    switch (mTypeOfFetch) {
    case 0xbfb44ccc: {
        cString text;
        cPropertyValue* pValue = 0;
        PropertyManager()->GetProperty(mFetchCommodityKey.mInstance, 0x34d97fa, &pValue);
        GetPropertyAsText(pValue, 0x3068d95d, &text);
        WString temp(text.GetText());
        *pOut = temp;
        temp.~WString();
        text.~cString();
        break;
    }
    case 0x19ec2c8b: {
        cString text;
        cPropertyValue* pValue = 0;
        PropertyManager()->GetProperty(mFetchArtifactCargoItemID.mInstance, 0x37d494e, &pValue);
        GetPropertyAsText(pValue, 0x3068d95d, &text);
        WString temp(text.GetText());
        if (pOut != &temp)
            pOut->assign(temp.mpBegin, temp.mpEnd);
        temp.~WString();
        text.~cString();
        break;
    }
    case 0xfb3b1635:
    case 0x2dc69129:
    case 0x6d5c48c:
    case 0x3e994b2b:
    case 0x69412983:
    case 0x736c417f: {
        if (mFetchPlantSpeciesKey.mInstance != EmptyKey()->mInstance
            || mFetchPlantSpeciesKey.mType != EmptyKey()->mType
            || mFetchPlantSpeciesKey.mGroup != EmptyKey()->mGroup) {
            cSpeciesManager* pManager = PlantSpeciesManager(&mFetchPlantSpeciesKey);
            cSpeciesProfile* pProfile = pManager->GetSpeciesFromID(&mFetchPlantSpeciesKey);
            if (pProfile != 0) {
                WString temp(pProfile->GetName());
                *pOut = temp;
                temp.~WString();
            }
        } else if (mFetchAnimalSpeciesKey.mInstance != EmptyKey()->mInstance
                   || mFetchAnimalSpeciesKey.mType != EmptyKey()->mType
                   || mFetchAnimalSpeciesKey.mGroup != EmptyKey()->mGroup) {
            cSpeciesManager* pManager = PlantSpeciesManager(&mFetchAnimalSpeciesKey);
            cSpeciesProfile* pProfile = pManager->GetSpeciesFromID(&mFetchAnimalSpeciesKey);
            if (pProfile != 0) {
                WString temp(pProfile->GetName());
                *pOut = temp;
                temp.~WString();
            }
        }
        break;
    }
    default:
        break;
    }
}

// @ 0x00c53a50
void cFetchSampleVector::push_back(const cFetchSample& value)
{
    if (mpEnd < mpCapacity) {
        cFetchSample* pEnd = mpEnd;
        mpEnd = pEnd + 1;
        if (pEnd != 0)
            *pEnd = value;
    } else {
        DoInsertValue(mpEnd, value);
    }
}

// @ 0x00c53a90
void cFetchSampleVector::clear()
{
    cFetchSample* pEnd = mpEnd;
    cFetchSample* pBegin = mpBegin;
    copy((const Quad16*)pEnd, (const Quad16*)pEnd, (Quad16*)pBegin);
    mpEnd -= pEnd - pBegin;
}

// @ 0x00c53ac0
void ReadFetchSamples(cSerializer* pSerializer, cFetchSampleVector& samples)
{
    cFetchSample sample;

    samples.clear();

    uint32_t nCount = 0;
    cSerializedObject* pObject = pSerializer->GetObject();
    void* pStream = pObject->GetStream();
    EA_IO_ReadInt32(pStream, &nCount, 1, 0);
    samples.Reserve(nCount);

    for (uint32_t i = 0; i < nCount; ++i) {
        sample.mSpeciesKey.mInstance = 0;
        sample.mSpeciesKey.mType = 0;
        sample.mSpeciesKey.mGroup = 0;
        cVarListSerializer serializer(&sample, "FetchSample", 0x01a80d26);
        serializer.Serialize(pSerializer);
        samples.push_back(sample);
    }

    pSerializer->End();
}

// @ 0x00c53bc0
bool cSPMissionFetch_s00c5_3180::PickFetchItem()
{
    switch (mTypeOfFetch) {
    case 0xbfb44ccc: {
        cPlanetEco* pEco = GetTargetPlanet()->mpEco;
        mFetchCommodityKey = *pEco->GetCommodityKey();
        return true;
    }
    case 0x23da98ff: {
        mSamplerPlate.clear();
        cPlanet_s00c5_3180* pPlanet = GetTargetPlanet();
        uint32_t nAnimals = (uint32_t)(pPlanet->mpAnimalKeysEnd - pPlanet->mpAnimalKeysBegin);
        for (uint32_t i = 0; i < nAnimals; ++i) {
            cFetchSample sample;
            sample.mIsAnimal = true;
            sample.mSpeciesKey = pPlanet->mpAnimalKeysBegin[i];
            mSamplerPlate.push_back(sample);
        }
        uint32_t nPlants = (uint32_t)(pPlanet->mpPlantKeysEnd - pPlanet->mpPlantKeysBegin);
        for (uint32_t i = 0; i < nPlants; ++i) {
            cFetchSample sample;
            sample.mIsAnimal = false;
            sample.mSpeciesKey = pPlanet->mpPlantKeysBegin[i];
            mSamplerPlate.push_back(sample);
        }
        return true;
    }
    case 0x19ec2c8b: {
        cItemList* pList = mMissionPropList->FindItems(0x781900a6);
        int32_t nCount;
        if ((pList->mnFlags & 0x30) != 0) {
            nCount = pList->mnCount;
            if (nCount <= 0)
                break;
        } else if (pList->mnCount2 != 0) {
            nCount = 1;
        } else {
            break;
        }
        Key* pKeys = pList->GetKeys();
        uint32_t nIndex = RandomUint32Uniform((uint32_t)nCount);
        mFetchArtifactCargoItemID = pKeys[nIndex];
        return true;
    }
    case 0x2dc69129: {
        mFetchAnimalSpeciesKey = *EmptyKey();
        if (*(const uint32_t*)&mRewardMoney == 0xbb448992 && mpParentMission != 0) {
            cSPMissionFlight101* pFlight = GetSubMission(mpParentMission, 0x0422227d);
            if (pFlight != 0 && pFlight->GetTargetPlanet() != 0) {
                /* parent flight mission already owns a herd target */
            }
        }
        cSpeciesProfile* pProfile = GetTargetPlanet()->GetRandomAnimalSpecies();
        if (pProfile == 0)
            break;
        mFetchAnimalSpeciesKey = pProfile->mSpeciesKey;
        break;
    }
    case 0x3e994b2b:
    case 0x69412983: {
        cPlanet_s00c5_3180* pPlanet = GetTargetPlanet();
        if (pPlanet == 0 || pPlanet->mpEco == 0)
            return true;
        mFetchAnimalSpeciesKey = *pPlanet->mpEco->GetAnimalKey();
        return true;
    }
    case 0x736c417f: {
        mFetchPlantSpeciesKey = *EmptyKey();
        cPlanet_s00c5_3180* pPlanet = GetTargetPlanet();
        void* pCapability = GetPlanetCapability(pPlanet);
        (void)pCapability;
        uint32_t nAnimals = (uint32_t)(pPlanet->mpAnimalKeysEnd - pPlanet->mpAnimalKeysBegin);
        for (uint32_t i = 0; i < nAnimals; ++i) {
            Key key = pPlanet->mpAnimalKeysBegin[i];
            GetSetting9(&key);
            GetSpeciesProfile(&key);
        }
        uint32_t nPlants = (uint32_t)(pPlanet->mpPlantKeysEnd - pPlanet->mpPlantKeysBegin);
        for (uint32_t i = 0; i < nPlants; ++i) {
            Key key = pPlanet->mpPlantKeysBegin[i];
            cSpeciesManager* pManager = PlantSpeciesManager(&key);
            cSpeciesProfile* pProfile = pManager->GetSpeciesFromID(&key);
            if (pProfile != 0)
                pProfile->GetName();
        }
        bool bAnimals = nAnimals > 0;
        bool bPlants = nPlants > 0;
        if (bAnimals && bPlants) {
            if (RandomUint32Uniform(100) > 50) {
                cSpeciesProfile* pProfile = GetTargetPlanet()->GetRandomAnimalSpecies();
                if (pProfile == 0)
                    break;
                mFetchAnimalSpeciesKey = pProfile->mSpeciesKey;
                break;
            }
        } else if (bAnimals) {
            cSpeciesProfile* pProfile = GetTargetPlanet()->GetRandomAnimalSpecies();
            if (pProfile == 0)
                break;
            mFetchAnimalSpeciesKey = pProfile->mSpeciesKey;
            break;
        } else if (!bPlants) {
            break;
        }
        cSpeciesProfile* pProfile = GetTargetPlanet()->GetRandomPlantSpecies();
        if (pProfile == 0)
            break;
        mFetchPlantSpeciesKey = *pProfile->GetSpeciesKey();
        break;
    }
    case 0x7ecbe6f5:
        return true;
    default:
        break;
    }

    if (mFetchArtifactCargoItemID.mInstance == EmptyKey()->mInstance
        && mFetchArtifactCargoItemID.mType == EmptyKey()->mType
        && mFetchArtifactCargoItemID.mGroup == EmptyKey()->mGroup
        && mFetchAnimalSpeciesKey.mInstance == EmptyKey()->mInstance
        && mFetchAnimalSpeciesKey.mType == EmptyKey()->mType
        && mFetchAnimalSpeciesKey.mGroup == EmptyKey()->mGroup
        && mFetchPlantSpeciesKey.mInstance == EmptyKey()->mInstance
        && mFetchPlantSpeciesKey.mType == EmptyKey()->mType
        && mFetchPlantSpeciesKey.mGroup == EmptyKey()->mGroup) {
        mTypeOfFetch = 0xffffffff;
        return false;
    }
    return true;
}

// @ 0x00c54110
void FetchMission::ValidateSpecies(Key_s00c5_4110* pKey)
{
    int i = 0;
    if (mValidateState != 0 && mValidateState != 1)
        goto done;

    switch ((int)mType) {
    case 0x2dc69129:
    case 0xfb3b1635:
    case 0x6d5c48c:
    case 0x3e994b2b:
    case 0x69412983:
    case 0x736c417f:
        goto alt;
    case (int)0x23da98ff: {
        int n = (int)((mpSpeciesEnd - mpSpeciesBegin));   // 0x238 - 0x234 >> 4
        int off = 0;
        for (i = 0; i < n; ++i) {
            char* e = (char*)mpSpeciesBegin + off;
            Key_s00c5_4110* k = (Key_s00c5_4110*)(e + 4);
            void* profile;
            if (*e != 0) {
                profile = ((SpeciesMgr*)FUN_00401090())->GetByKey(k);
            } else {
                profile = ((SpeciesMgr*)FUN_00b3d420())->GetByKey(k);
            }
            if (!profile)
                goto found;
            if (pKey != 0 && KeyEq3(pKey, k))
                goto found;
            off += 0x10;
        }
        FUN_00c48470(pKey);
        return;
    found:
        if (FUN_00c53bc0()) {
            mValidateState = 0;
            FUN_00c48470(pKey);
            return;
        }
        FUN_00c53a90();
        SetState(1);
        goto done;
    }
    default:
        goto done;
    }

alt:
    if (*(uint32_t*)&mKeyA != *(uint32_t*)0x016907d4 ||
        *(uint32_t*)((char*)&mKeyA + 4) != *(uint32_t*)0x016907d8 ||
        *(uint32_t*)((char*)&mKeyA + 8) != *(uint32_t*)0x016907dc) {
        if (((SpeciesMgr*)FUN_00b3d420())->GetByKey(&mKeyA) &&
            (pKey == 0 || !KeyEq3(pKey, &mKeyA))) {
            if (FUN_00c53bc0())
                mValidateState = 0;
            else {
                mKeyA = *(Key_s00c5_4110*)0x016907d4;
                SetState(1);
            }
        }
    }

    if (*(uint32_t*)&mKeyB != *(uint32_t*)0x016907d4 ||
        *(uint32_t*)((char*)&mKeyB + 4) != *(uint32_t*)0x016907d8 ||
        *(uint32_t*)((char*)&mKeyB + 8) != *(uint32_t*)0x016907dc) {
        if (((SpeciesMgr*)FUN_00401090())->GetByKey(&mKeyB) &&
            (pKey == 0 || !KeyEq3(pKey, &mKeyB)) &&
            FUN_00c53bc0()) {
            mValidateState = 0;
            FUN_00c48470(pKey);
            return;
        }
        mKeyB = *(Key_s00c5_4110*)0x016907d4;
        SetState(1);
    }

done:
    FUN_00c48470(pKey);
}

// @ 0x00c54380
bool FetchMission::Init()
{
    int i = 0;
    if (!InitBase())
        return false;

    ((VFn0)(*(void***)this)[0x16c / 4])(this);

    int prop[3] = { 0, 0, 0 };
    if (GetPropertyAsKey(mpPropTable, 0xac10e58a, prop))
        mType = prop[0];

    ReadDropOffFields();
    uint32_t t = ReadTargetPlanetType();
    char one = 1;
    if (t == 0x2ca33bdb) {
        if (mSubtype != 0x809ab04a)
            goto after_pick;
        PickParams pp;
        pp.Ctor();
        pp.mType = 0x38;
        pp.mCost = 2;
        void* pl = PickPlanet(&pp);
        if (pl) {
            void* q = FUN_00b3d3d0(pl);
            FUN_0103aa00(q);
        }
        pp.Dtor();
    } else {
        void* rec = GetPlanetRecordFromTargetType(t);
        if (rec)
            FUN_00c47180(rec);
        if (mSubtype == 0xbb448992) {
            uint32_t sp = ReadTargetAnimalSpeciesType(&mKeyB);
            GetAnimalSpeciesFromType(sp, &mKeyB);
        }
        if (GetTargetPlanet() != 0)
            goto after_pick;

        PickParams pp;
        pp.Ctor();
        pp.mType = 0x38;
        uint32_t ft = mType;
        if ((int)ft > 0x2dc69129) {
            if ((int)ft > 0x736c417f) {
                if (ft == 0x7ecbe6f5)
                    pp.mType = 0x3c;
            } else {
                switch (ft) {
                case 0x736c417f: pp.mB0e = one; pp.mB0d = one; break;
                case 0x3e994b2b: pp.mCost = 0x10; pp.mCost2 = 0x10; break;
                case 0x69412983: pp.mCost = 0x20; pp.mCost2 = 0x20; break;
                default: break;
                }
            }
        } else if (ft == 0x2dc69129) {
            pp.mB0e = one;
        } else if ((int)ft > 0x6d5c48c) {
            if (ft == 0x19ec2c8b)
                pp.mType = 0x3c;
            else if (ft == 0x23da98ff) {
                pp.mB0e = one; pp.mB0d = one;
            }
        } else if (ft == 0x6d5c48c) {
            pp.mB0e = one; pp.mB0d = one;
        } else if (ft == 0xbfb44ccc) {
            pp.mCost = 0x20; pp.mCost2 = 0x20;
        } else if (ft == 0xfb3b1635) {
            pp.mCost = 4; pp.mCost2 = 4;
        }

        void* pl = PickPlanet(&pp);
        if (!pl) {
            pp.Dtor();
            return false;
        }
        FUN_00c47180(pl);
        void* tp = GetTargetPlanet();
        FUN_00bc1b10((TerraMgr*)FUN_00b3d3d0(tp), tp, 0, 0);
        pp.Dtor();
    }

after_pick:
    if (!HasPickedFetchItem() && !FUN_00c53bc0())
        return false;
    ((VFn0)(*(void***)this)[0x188 / 4])(this);
    if (!((VFnB)(*(void***)this)[0x128 / 4])(this))
        return false;
    if (mType == 0x69412983) {
        void* tp = GetTargetPlanet();
        FUN_00c45250(FUN_00c71e30(tp));
    }
    FUN_00c4a0c0();
    ((VFn0)(*(void***)this)[0x170 / 4])(this);
    return true;
}

// @ 0x00c545f0
void FetchHandler::HandleMessage(uint32_t msg, Msg* m)
{
    Key_s00c5_4110 f12plant, f11art2, f11plant, f11art1, f11rare, f12art1, f12art2;
    switch (msg) {
    case 0x2489766: case 0x248976a:
        if (F<int>(0x1bc) != 0) break;
    ui_update:
        if (F<uint32_t>(0x44) == 0x809ab04a)
            Mis()->TriggerUIUpdate();
        break;
    case 0x248975f:
        if (F<uint32_t>(0x1c0) == 0x19ec2c8b) {
            if (F<int>(0x1bc) == 0) {
                Mission* mi = Mis();
                void* target = m->f10;
                if (mi->GetTargetPlanet() == target) {
                    Avatar* av = SpaceGameGet_s00c5_4110()->GetAvatar();
                    if (av) {
                        SpawnParams sp;
                        sp.a = F<uint32_t>(0x1c4);
                        sp.pos.a = F<uint32_t>(0x1d0);
                        sp.pos.b = F<uint32_t>(0x1d4);
                        sp.pos.c = F<uint32_t>(0x1d8);
                        sp.w = 1;
                        sp.g[1] = 0; sp.g[2] = 0; sp.g[3] = 0;
                        sp.t28 = 0x28;
                        sp.b12 = 5; sp.f = 0.0f;
                        sp.g[0] = 0;
                        void* obj = av->SpawnArtifact(&sp);
                        if (obj) {
                            F<Vec3>(0x1d0) = *((PosProv*)((char*)obj + 0x34))->GetPos();
                        } else {
                            F<Vec3>(0x1d0) = gDefaultPos;
                        }
                    }
                }
            }
            break;
        }
        goto ui_update;
    case 0x2e9977e:
        if (F<uint32_t>(0x1c0) == 0x6d5c48c) {
            uint8_t* src = m->src;
            if (src && m->f18 && m->f18 != 0x2ebcd6a6) {
                void* sp = GetSpecimenMgr()->Lookup(m);
                if (sp && KeyEq((Key_s00c5_4110*)sp, &F<Key_s00c5_4110>(0x1dc))) {
                    Vec3 pos = *(Vec3*)(src + 4);
                    Vec3* b = F<Vec3*>(0x21c);
                    Vec3* e = F<Vec3*>(0x220);
                    if (FindVec3(b, e, &pos) == e)
                        ((Vec3Vec*)&F<Vec3*>(0x21c))->push_back(&pos);
                }
            }
        }
        break;
    case 0x3029f12: {
        Mission* mi = Mis();
        void* model = mi->GetModel();
        if (GetActivePlanet() != model) break;
        if (!F<uint8_t>(0x214)) break;
        bool hasTarget = m->f10 != 0;
        uint8_t* src = m->src;
        if (!src) break;
        PosProv* pp;
        switch ((int)F<uint32_t>(0x1c0)) {
        case 0x3e994b2b: case 0x69412983: case (int)0xfb3b1635: {
            AnimItem* a = CastAnimal2(src);
            if (!a) goto done;
            if (!KeyEq(a->GetKey(), &F<Key_s00c5_4110>(0x1e8))) goto done;
            pp = (PosProv*)((char*)a + 0xc0);
            break;
        }
        case (int)0xbfb44ccc: {
            ArtItem* a = CastArt(src);
            if (!a) goto done;
            if (*(int*)((char*)a + 0x658) != 4) goto done;
            if (!KeyEq(a->GetKey(&f12art1), &F<Key_s00c5_4110>(0x1f4))) goto done;
            pp = (PosProv*)((char*)a + 0x34);
            break;
        }
        case 0x19ec2c8b: {
            ArtItem* a = CastArt(src);
            if (!a) goto done;
            if (!KeyEq(a->GetKey(&f12art2), &F<Key_s00c5_4110>(0x1c4))) goto done;
            pp = (PosProv*)((char*)a + 0x34);
            F<Vec3>(0x1d0) = *pp->GetPos();
            break;
        }
        case 0x2dc69129: case 0x6d5c48c: case 0x736c417f: {
            Key_s00c5_4110* kp = &F<Key_s00c5_4110>(0x1dc);
            if (KeyNe(kp, &gNullKey)) {
                PlantItem* a = CastPlant(src);
                if (!a) goto done;
                if (!KeyEq(a->GetKey(&f12plant), kp)) goto done;
                pp = (PosProv*)((char*)a + 0x34);
            } else {
                kp = &F<Key_s00c5_4110>(0x1e8);
                if (!KeyNe(kp, &gNullKey)) goto done;
                AnimItem* a = CastAnimal(src);
                if (!a) goto done;
                if (!KeyEq(a->GetKey(), kp)) goto done;
                pp = (PosProv*)((char*)a + 0xc0);
            }
            break;
        }
        default:
            goto done;
        }
        Vec3 pos = *pp->GetPos();
        if (!hasTarget) break;
        {
            float r = F<float>(0x218);
            float r2 = r * r;
            VecP* list = GetNounManager()->GetAll();
            for (uint8_t** it = list->b; it != list->e; ++it) {
                PosProv* o = (PosProv*)(*it + 0x120);
                Vec3* p = o->GetPos();
                float dz = p->z - pos.z, dy = p->y - pos.y, dx = p->x - pos.x;
                if (r2 > dz * dz + dy * dy + dx * dx) {
                    mi->Complete();
                    goto done;
                }
            }
        }
        {
            WStr text;
            mi->GetText(0x959d4317, &text);
            void* ev = GetEventLog()->PostFeedbackEvent(0xcc0a183b, 0x131a9f54, 0, 0, 1, 0);
            GetEventLog()->ModifyEventText(ev, text.mpBegin);
            mi->PostEvent(ev);
        }
        break;
    }
    case 0x3029f11: {
        Mission* mi = Mis();
        void* tp = mi->GetTargetPlanet();
        bool ok;
        if (tp == 0) {
            if (F<uint32_t>(0x1c0) != 0x7ecbe6f5) goto done;
            ArtItem* a = CastArt(m->src);
            if (!a) goto done;
            ok = IsItemARare(a->GetKey(&f11rare));
        } else {
            void* tp2 = mi->GetTargetPlanet();
            if (GetActivePlanet() != tp2) goto done;
            uint8_t* src = m->src;
            if (!src) goto done;
            switch ((int)F<uint32_t>(0x1c0)) {
            case 0x3e994b2b: case 0x69412983: case (int)0xfb3b1635: {
                AnimItem* a = CastAnimal2(src);
                if (!a) goto done;
                ok = KeyEq(a->GetKey(), &F<Key_s00c5_4110>(0x1e8));
                break;
            }
            case (int)0xbfb44ccc: {
                ArtItem* a = CastArt(src);
                if (!a) goto done;
                if (*(int*)((char*)a + 0x658) != 4) goto done;
                ok = KeyEq(a->GetKey(&f11art1), &F<Key_s00c5_4110>(0x1f4));
                break;
            }
            case 0x19ec2c8b: {
                ArtItem* a = CastArt(src);
                if (!a) goto done;
                if (!KeyEq(a->GetKey(&f11art2), &F<Key_s00c5_4110>(0x1c4))) goto done;
                F<Vec3>(0x1d0) = gDefaultPos;
                goto finish;
            }
            case 0x2dc69129: case 0x6d5c48c: case 0x736c417f: {
                if (KeyNe(&F<Key_s00c5_4110>(0x1dc), &gNullKey)) {
                    PlantItem* a = CastPlant(src);
                    if (!a) goto done;
                    ok = KeyEq(a->GetKey(&f11plant), &F<Key_s00c5_4110>(0x1dc));
                } else {
                    if (!KeyNe(&F<Key_s00c5_4110>(0x1e8), &gNullKey)) goto done;
                    AnimItem* a = CastAnimal(src);
                    if (!a) goto done;
                    ok = KeyEq(a->GetKey(), &F<Key_s00c5_4110>(0x1e8));
                }
                break;
            }
            default:
                goto done;
            }
        }
        if (!ok) break;
    finish:
        if (F<uint8_t>(0x214)) {
            if (F<uint32_t>(0x44) != 0xbb448992) break;
            if (F<int>(0x1bc) != 0) break;
            mi->FUN_00c5ed90(1);
            void* obj = F<void*>(0x148);
            if (!obj) obj = mi;
            int owner = *(int*)((char*)mi->GetModel() + 0x13c);
            int empire = *(int*)((char*)mi->GetOwnerEmpire() + 0x84);
            int text = SlotId(mi);
            int ctx = ((StarRec*)owner)->GetCommContext();
            GetCommManager()->AddEntry(empire, ctx, text, 0x932a66fe, obj, 0, 0);
        } else {
            void* pl = GetActivePlanet();
            if (pl) mi->FUN_00c47180(*(void**)((char*)pl + 0x13c));
            mi->Complete();
        }
        break;
    }
    }
done:
    BaseHandleMessage(msg, m);
}

// @ 0x00c54f90
char cSPMissionFetch_s00c5_4f90::VerifyTargetPlanet(void* pTarget, void* pOut)
{
    if (GetUniverseContext() != 0)
        return 0;

    void* pTargetPlanet = GetTargetPlanet();
    if (GetActivePlanet() != pTargetPlanet)
        return 0;

    if (mnState != 0)
        return 0;

    uint32_t nType = mnTargetType;
    if ((int32_t)nType >= 0x3e994b2c) {
        if (nType == 0x69412983) {
            cSearchVector* pSearch = ((cNounManager*)NounManager())->GetHerdSearchList();
            if (pSearch->mpBegin == pSearch->mpEnd)
                return 0;
            void* pFound = FindHerdSubMission(pSearch, pTarget);
            AssignRefCount(&pFound, pFound);
            if (pTarget == nullptr)
                return 0;
            void* pPosition = ((cSpaceObject*)pTarget)->mPointingInterface.Call(0x2c);
            *(Vec3_s00c5_4f90*)pOut = *(Vec3_s00c5_4f90*)pPosition;
            ((cDispatchObject*)pTarget)->Call(0x04);
            return 1;
        }
        if (nType != 0x736c417f)
            return 0;
        if (CompareResourceHandle(mToolResource, gResourceNone))
            return (char)(intptr_t)ProcessToolSubMission(mSearchB, pOut);
        return (char)(intptr_t)ProcessAliensSubMission(mSearchA, pOut);
    }

    if (nType == 0x3e994b2b) {
        cSearchVector* pSearch = ((cNounManager*)NounManager())->GetHerdSearchList();
        if (pSearch->mpBegin == pSearch->mpEnd)
            return 0;
        void* pFound = FindHerdSubMission(pSearch, pTarget);
        AssignRefCount(&pFound, pFound);
        if (pTarget == nullptr)
            return 0;
        void* pPosition = ((cSpaceObject*)pTarget)->mPointingInterface.Call(0x2c);
        *(Vec3_s00c5_4f90*)pOut = *(Vec3_s00c5_4f90*)pPosition;
        ((cDispatchObject*)pTarget)->Call(0x04);
        return 1;
    }
    if (nType == 0xfb3b1635) {
        cSearchVector* pSearch = ((cNounManager*)NounManager())->GetAlienSearchList();
        if (pSearch->mpBegin == pSearch->mpEnd)
            return 0;
        void* pFound = FindAliensSubMission(pSearch, pTarget);
        AssignRefCount(&pFound, pFound);
        if (pTarget == nullptr)
            return 0;
        void* pPosition = ((cSpaceObject*)pTarget)->mPointingInterface.Call(0x2c);
        *(Vec3_s00c5_4f90*)pOut = *(Vec3_s00c5_4f90*)pPosition;
        ((cDispatchObject*)pTarget)->Call(0x04);
        return 1;
    }
    if (nType == 0x6d5c48c)
        return (char)(intptr_t)ProcessToolSubMission(mSearchB, pOut);
    if (nType == 0x2dc69129)
        return (char)(intptr_t)ProcessAliensSubMission(mSearchA, pOut);
    return 0;
}

// @ 0x01342770
void FUN_01342770()
{
    ATTR(s_fetchAttrs[0], "mFetchMissionState", 0x385389d, 0x1f0,
         0x692ca0, 0x572810, 0x572840, 0x692ff0, 0x694ee0, 0xb1fbf0, 0x57cde0);
    ATTR(s_fetchAttrs[1], "mTypeOfFetch", 0x385389e, 0x1f4,
         0x692ca0, 0x572810, 0x572840, 0x692ff0, 0x694ee0, 0xb1fbf0, 0x57cde0);
    ATTR(s_fetchAttrs[2], "mFetchArtifactCargoItemID", 0x385389f, 0x1f8,
         0x692ca0, 0xae3430, 0xae3450, 0x693150, 0x695080, 0xb1fbf0, 0xae5720);
    ATTR(s_fetchAttrs[3], "mFetchPlantSpeciesKey", 0x3f69492, 0x210,
         0x692ca0, 0xae3430, 0xae3450, 0x693150, 0x695080, 0xb1fbf0, 0xae5720);
    ATTR(s_fetchAttrs[4], "mFetchAnimalSpeciesKey", 0x3f69497, 0x21c,
         0x692ca0, 0xae3430, 0xae3450, 0x693150, 0x695080, 0xb1fbf0, 0xae5720);
    ATTR(s_fetchAttrs[5], "mFetchCommodityKey", 0x3f69498, 0x228,
         0x692ca0, 0xae3430, 0xae3450, 0x693150, 0x695080, 0xb1fbf0, 0xae5720);
    ATTR(s_fetchAttrs[6], "mSamplerPlate", 0x38538a3, 0x234,
         0x692ca0, 0xc53ac0, 0xc52c60, 0xc2e4e0, 0x692fb0, 0xc52cf0, 0xca8710);
    ATTR(s_fetchAttrs[7], "mDropOffRequired", 0x3f69499, 0x248,
         0x692ca0, 0xac8750, 0xac8780, 0x693090, 0x694fa0, 0xb1fbf0, 0x57ce00);
    ATTR(s_fetchAttrs[8], "mDropOffDistance", 0x3f69500, 0x24c,
         0x692ca0, 0x572810, 0xac88f0, 0x6930b0, 0x694fc0, 0xb1fbf0, 0xacbb80);
}
