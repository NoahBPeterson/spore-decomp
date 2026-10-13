// src/game/SPBake/SPEditorValidity.cpp -- migrated from slice(s) s00f3b0c0, s004f6630, s004f56f0, s004f3de0, s004f3c50, s004f2d40, s004f1ff0, s004f1350, s004f01f0, s004ef880, s004ee9b0, s004eda30, s004ebe20, s004eb270, s004ea310, s004e95e0 by tools/migrate/rewrite.py
// Object file: SPBake/SPEditorValidity.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ResourceMan/Key.h"
#include "EA/IO/FileStream.h"
#include "EA/ResourceMan/Manager.h"
#include "SP/cSPPalette.h"
#include "EA/Variant.h"
#include "EA/ArgScript/cIParser.h"
#include "EA/Swarm/cIVisualEffect.h"
#include <string.h>
#include <wchar.h>
#include "SP/cDirectPropertyList.h"
#include "cSPBoundingBox.h"
#include "cSPVector3.h"
#include "SP/cEditorResource.h"
#include "SP/cPropertyList.h"
#include "SP/cPropertyManager.h"
#include "SP/cSPEditorModelValidity.h"

// ---- items of slice s004e95e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct DeclareParam { int key; int a; int b; };
struct Manager {
    virtual void m00(); virtual void m01(); virtual void m02(); virtual void m03();
    virtual void m04(); virtual void m05(); virtual void m06(); virtual void m07();
    virtual void m08(); virtual void m09(); virtual void m10(); virtual void m11();
    virtual void m12(); virtual void m13(); virtual void m14(); virtual void m15();
    virtual void m16(); virtual void m17(); virtual void m18(); virtual void m19();
    virtual void m20(); virtual void m21();
    virtual void* Find(int a, int b); // +0x58
};
struct Vec { void push_back(const DeclareParam& v); };
void* GetMgr401010();                                            // 0x00401010
void* GetManager67dcd0();                                        // 0x0067dcd0
bool GetPropertyAsKey(void* holder, int key, void* out);         // 0x006a1250
bool GetPropertyAsKeyInstance(void* holder, int key, int* out);  // 0x006a12a0
bool GetPropertyAsKeyArray(void* holder, int key, int* count, void** array); // 0x006a0ae0
void* InterfaceCast(void** ref);                                 // 0x00421eb0-ish
void* operator new(uint32_t size, const char* name, int, int, int, int); // 0x00f473a0
struct Iface {
    virtual void v00();
    virtual void AddRef();   // +4
    virtual void Release();  // +8
};
struct PaletteIter : Iface {
    PaletteIter();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void SetPalette(void* p);              // 0x005c7bc0
    virtual void* GetFirst(int, int, int, int);    // 0x005c7e80
    virtual void* GetNext(int, int, int, int);     // 0x005c7e20
};
struct cSPPalette : Iface {
    cSPPalette();
    bool Init(void* a, int b, int c, int d, int e, int f, int g); // 0x005c6340
};
struct ResourceMgr {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void FindResource(void* key, void** out, int, int, int, int); // +0xc
};
extern DeclareParam g_15dacc8;
extern DeclareParam g_15dabcc;
void FUN_004e9ca0(Vec* out);
// ---- items of slice s004e95e0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern DeclareParam g_15dacc8;
extern DeclareParam g_15dabcc;

// ---- items of slice s004ea310 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int g_15daa00;
struct FlagWord {
    unsigned int a : 8;
    unsigned int b : 8;
    unsigned int c : 8;
    unsigned int d : 6;
    unsigned int e : 2;
};
void operator delete[](void* p);
template<int N> inline void ScratchSlots() { uint32_t s[N]; }
struct Alloc { Alloc() {} };
struct ResourceKey {
    uint32_t instance, type, group;
    ResourceKey() : instance(0), type(0), group(0) {}
};
struct VectorBase {
    ResourceKey* mpBegin;
    ResourceKey* mpEnd;
    ResourceKey* mpCapacity;
    uint32_t mAllocator;
    ~VectorBase()
    {
        if (mpBegin) {
            unsigned n = (mpCapacity - mpBegin) * sizeof(ResourceKey);
            ResourceKey* p = mpBegin;
            if (((int*)p)[-1] != 0) {
                ResourceKey* q = p;
                operator delete[](q);
            }
        }
    }
};
struct VSet : VectorBase {
    uint32_t mPadding;
    VSet(const Alloc& a = Alloc());   // 0x00540470
    ~VSet() { for (ResourceKey* p = mpBegin; p < mpEnd; ++p) {} }
    void push_back(const DeclareParam& v);
    ResourceKey* begin() { ResourceKey* it = mpBegin; return it; }
    int size() { return mpEnd - mpBegin; }
    ResourceKey* data() { return mpBegin; }
    ResourceKey* end() { ResourceKey* it = mpEnd; return it; }
    ResourceKey* erase(ResourceKey* first, ResourceKey* last);   // 0x0050f740
};
struct Iface_s004e_a310 { virtual void v0(); virtual void Release(); }; // Release at +4
struct PaletteMgr {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10();
    virtual void GetConfig(int cfg, int key, int* out); // +0x2c
    virtual void v12();                                 // +0x30
    virtual void StoreProperties(void* list, int instance, uint32_t group); // +0x34
};
int GetConfigFromModelType(int id);      // 0x00432f10
void* PropertyManager();                 // 0x0067de30
struct Variant {
    uint32_t mData[4];
    unsigned short mnFlags;
    unsigned short mnType;
    // Key-array property (type 0x20), by reference/copy depending on `byCopy`.
    __forceinline Variant(const ResourceKey* data, unsigned count, unsigned short base = 0x80, bool byCopy = true)
        : mnFlags(0), mnType(0)
    {
        if (byCopy)
            Set(0x20, base | 0x10 | 8, data, sizeof(ResourceKey), count);
        else
            Set(0x20, base | 0x20, data, sizeof(ResourceKey), count);
    }
    ~Variant() { if (mnFlags & 4) Destruct(false); }
    void Set(unsigned short type, int flags, const void* data, unsigned size, unsigned count);   // 0x0093dd80
    void Destruct(bool b);   // 0x0093db80
};
struct cPropertyList {
    virtual void AddRef();     // +0x00
    virtual void Release();    // +0x04
    virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void AddProperty(uint32_t id, const Variant* v);   // +0x14
    char pad[0x38 - 4];
    cPropertyList();           // Editor::cPropertyList::cPropertyList, 0x006a1c40
};
struct PropList { virtual void AddRef(); virtual void Release(); };   // the config property list (slot 4 = Release)
struct PropListRef {
    PropList* mpObject;
    PropListRef() : mpObject(0) {}
    ~PropListRef() { if (mpObject) mpObject->Release(); }
    PropList** AsPPVoidParam();   // 0x0041d870
    PropList** operator&() { return AsPPVoidParam(); }
};
struct ListRef {
    cPropertyList* mpObject;
    ListRef(cPropertyList* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~ListRef() { if (mpObject) mpObject->Release(); }
    cPropertyList* get() { return mpObject; }
    cPropertyList* operator->() { return mpObject; }
};
struct ResMgr {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void Write(cPropertyList* list, int a, int area, int b, int c);   // +0x20
};
ResMgr* GetResourceMgr();                       // 0x0067dcd0
int GetSaveArea(int id);                        // 0x006b1f90 (cdecl)
void FUN_004e9fc0(const ResourceKey* key, VSet* out, int kind);   // 0x004e9fc0
void FUN_004ea190(int id, VSet* out, int flag);                    // 0x004ea190
void AddSpecialPaints(int id, VSet* out, int flag);                // 0x004ea310
namespace eastl {
void sort(ResourceKey* first, ResourceKey* last);                  // 0x004f6b70
}
namespace eastl {
ResourceKey* unique(ResourceKey* first, ResourceKey* last);        // 0x004f6830
}
static inline uint32_t MakeFlags(unsigned a, unsigned b, unsigned c)
{
    FlagWord f = {0};
    f.e = 1;
    f.c = c;
    f.b = b;
    f.a = a;
    return *(uint32_t*)&f;
}
// ---- items of slice s004ea310 end

// ---- items of slice s004eb270 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int g_150ca00[];
void FUN_004ea920(int, int, int);
struct Elem16 { DeclareParam k; int extra; };
bool FUN_004eb930(const DeclareParam& a, const DeclareParam& b);  // 0x004eb930 (defined below; used by a stub's inline body)
static inline bool operator==(const Elem16& a, const Elem16& b)
{
    return FUN_004eb930(a.k, b.k) && a.extra == b.extra;
}
// ---- items of slice s004eb270 end

// ---- items of slice s004ebe20 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct PropertyList {
    virtual int AddRef();                  // +0
    virtual int Release();                 // +4
};
struct PropertyListPtr {                   // EA intrusive_ptr<PropertyList>
    PropertyList* mpObject;
    PropertyListPtr() : mpObject(0) {}
    explicit PropertyListPtr(PropertyList* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~PropertyListPtr() { if (mpObject) mpObject->Release(); }
    PropertyListPtr& Reset();              // 0x0041d870 (out of line)
    PropertyListPtr& ResetInline()
    {
        if (mpObject) {
            PropertyList* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
        return *this;
    }
    PropertyList* get() const { return mpObject; }
    PropertyListPtr& Out() { return Reset(); }
};
struct cPropManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyListPtr& pDst);   // +0x2c
    virtual bool GetGlobalPropertyList(uint32_t instanceID, PropertyListPtr& pDst);               // +0x30
};
struct ResourceKey_s004e_be20 {
    uint32_t instanceID, typeID, groupID;
    ResourceKey_s004e_be20() : instanceID(0), typeID(0), groupID(0) {}
};
struct WString16 {                         // eastl::basic_string<wchar_t>
    uint32_t mData[4];
    void push_back(wchar_t c);             // 0x004f6510
};
struct ValidityBits {                      // eastl::bitset<128>
    uint32_t mWord[4];
    uint32_t& DoGetWord(uint32_t i) { return mWord[i >> 5]; }
    __forceinline void set(uint32_t i, bool value = true)
    {
        if (i < 128) {
            if (value)
                DoGetWord(i) |= (1u << (i % 32));
            else
                DoGetWord(i) &= ~(1u << (i % 32));
        }
    }
    void operator|=(const ValidityBits& x)
    {
        for (uint32_t i = 0; i < 4; i++)
            mWord[i] |= x.mWord[i];
    }
    ValidityBits& flip();                  // 0x004f65d0 (out of line)
};
struct KeyVector;
struct KeyMap {                            // eastl::map<uint32_t, vector<ResourceKey-ish>>
    KeyVector& operator[](const uint32_t& key);   // 0x004f6720
};
struct cDirectPropertyList;
template <int N> inline void ScratchSlots_s004e_be20() { uint32_t s[N]; }
namespace SP {
cPropManager* PropertyManager();                                                       // 0x0067de30
}
namespace SP {
bool GetPropertyAsUInt(PropertyList* p, uint32_t id, uint32_t* out);                   // 0x00410370
}
namespace SP {
bool GetPropertyAsString16(PropertyList* p, uint32_t id, WString16* out);              // 0x006a1400
}
namespace SP {
bool GetPropertyAsIntArray(PropertyList* p, uint32_t id, uint32_t* count, int** out);  // 0x006a07d0
}
namespace SP {
bool GetPropertyAsKey(PropertyList* p, uint32_t id, ResourceKey_s004e_be20* out);                 // 0x006a1250
}
namespace SP {
extern cDirectPropertyList* sAppProperties;                                            // 0x015fd918
}
namespace SP {
inline void CheckAppProperties() { cDirectPropertyList* pAppProps = sAppProperties; }
}
namespace SP {
namespace Editor {
 uint32_t GetConfigFromModelType(uint32_t modelType);   // 0x00432f10
}
}
namespace SP {
namespace EditorValidity {
void ReadKeysFromFile(uint32_t instanceID, KeyVector& dst);                           // 0x004eb270
}
}
namespace SP {
namespace EditorValidity {
void ExpandValidity(ValidityBits* bits);                                               // 0x004eba00
}
}
namespace SP {
namespace EditorValidity {
extern bool sInitialized;                  // 0x015da6e4
}
}
namespace SP {
namespace EditorValidity {
extern uint32_t sValidityVersion;          // 0x015da6e0
}
}
namespace SP {
namespace EditorValidity {
extern WString16 sValidityChars;           // 0x015da7d4
}
}
namespace SP {
namespace EditorValidity {
extern ValidityBits sBits784;              // 0x015da784
}
}
namespace SP {
namespace EditorValidity {
extern ValidityBits sBits7c4;              // 0x015da7c4
}
}
namespace SP {
namespace EditorValidity {
extern ValidityBits sBits9c8;              // 0x015da9c8
}
}
namespace SP {
namespace EditorValidity {
extern ValidityBits sBits8e0;              // 0x015da8e0
}
}
namespace SP {
namespace EditorValidity {
extern ValidityBits sBitsb94;              // 0x015dab94
}
}
namespace SP {
namespace EditorValidity {
extern ValidityBits sBitsa40;              // 0x015daa40
}
}
namespace SP {
namespace EditorValidity {
extern ValidityBits sBits7ec;              // 0x015da7ec
}
}
namespace SP {
namespace EditorValidity {
extern ValidityBits sBitsc10;              // 0x015dac10
}
}
namespace SP {
namespace EditorValidity {
extern ValidityBits sBitsb18;              // 0x015dab18
}
}
namespace SP {
namespace EditorValidity {
extern ValidityBits sBits80c;              // 0x015da80c
}
}
namespace SP {
namespace EditorValidity {
extern ValidityBits sBits860;              // 0x015da860
}
}
namespace SP {
namespace EditorValidity {
extern KeyMap sLegalParts;                 // 0x015da960
}
}
namespace SP {
namespace EditorValidity {
extern KeyMap sLegalPaints;                // 0x015da884
}
}
namespace SP {
namespace EditorValidity {
extern uint32_t kGroupEditorConfigs;       // 0x015daa00
}
}
namespace SP {
namespace EditorValidity {
extern uint32_t kEditorModelTypes[];       // 0x0150ca00 (27 entries)
}
}
// ---- items of slice s004ebe20 end

// ---- items of slice s004eda30 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const wchar_t kReservedName[];     // 0x13ec468
#pragma intrinsic(wcscmp)
struct Flags128 {
    uint32_t mWord[4];
    uint32_t& DoGetWord(uint32_t i) { return mWord[i >> 5]; }
    __forceinline void set(uint32_t i, bool value) {
        if (i < 128) {
            if (value) DoGetWord(i) |= 1u << (i % 32);
            else DoGetWord(i) &= ~(1u << (i % 32));
        }
    }
};
struct EntryVec { char* mpBegin; char* mpEnd; };
struct IRef {
    virtual void AddRef();     // +0
    virtual void Release();    // +4
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
    virtual bool Has(uint32_t id);                     // +0x1c
    virtual void v8();
    virtual bool Get(uint32_t id, void** ppProp);      // +0x24
};
struct ResPtr {
    IRef* mp;
    ResPtr(IRef* p) : mp(p) { if (mp) mp->AddRef(); }
    ~ResPtr() { if (mp) mp->Release(); }
    IRef** GetAddr();          // 0x41d870
    IRef** operator&() { return GetAddr(); }
};
struct ResEntry { int a; int b; uint32_t rest[(0x1d8 - 8) / 4]; ResEntry(const ResEntry& src); };   // 0x4721e0 copy ctor
struct PropMgr {
    virtual void m00(); virtual void m01(); virtual void m02(); virtual void m03();
    virtual void m04(); virtual void m05(); virtual void m06(); virtual void m07();
    virtual void m08(); virtual void m09(); virtual void m10();
    virtual int GetResource(int b, int a, IRef** out);    // +0x2c
};
bool GetBoolProperty(IRef* p, uint32_t id, bool* out);   // 0x407190
struct PropVal {
    char pad[0x12]; unsigned short type;
    float* GetFloat();   // 0x41ea70
};
struct WString { unsigned find(unsigned short c, unsigned pos) const; };   // 0x4f6ab0
extern WString gBadChars;                         // 0x15da7d4
struct PVSlot { int pad; PropVal* p; };
// ---- items of slice s004eda30 end

// ---- items of slice s004ee9b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" float __cdecl sqrtf(float);
extern uint32_t g_ModelGroup;                                        // 0x015daa00
struct Property {
    char pad[0x12];
    uint16_t mType;                 // +0x12 (1 = bool, 0xd = float)
    bool* GetBool();                // 0x0041e920
    float* GetFloat();              // 0x0041ea70
};
struct PropertyList_s004e_e9b0 {
    virtual int Release_();         // 0
    virtual int Release();          // +4
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
    virtual void v7(); virtual void v8();
    virtual bool GetProperty(uint32_t id, Property*& out);   // +0x24
};
struct PropListRef_s004e_e9b0 {
    PropertyList_s004e_e9b0* mp;
    PropListRef_s004e_e9b0() : mp(0) { if (mp) mp->Release_(); }
    ~PropListRef_s004e_e9b0() { if (mp) mp->Release(); }
    PropListRef_s004e_e9b0* operator&();       // 0x0041d870 (releases old, returns this)
};
struct PropertyManager_s004e_e9b0 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10();
    virtual void GetPropertyList(uint32_t type, uint32_t group, PropListRef_s004e_e9b0* out);   // +0x2c
};
struct EntryOwner {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21();
    virtual PropertyList_s004e_e9b0* GetPropertyList(uint32_t instance, uint32_t group);   // +0x58
};
struct Vec3f {
    float v[3];
    float operator[](int i) const { return v[i]; }
};
struct LimbEntry {                  // 0x1d8 bytes
    uint32_t group;                 // +0x00
    uint32_t instance;              // +0x04
    int      parent;                // +0x08
    char     pad0[8];
    Vec3f    pos;                   // +0x14
    char     pad1[0x1d8 - 0x20];
};
struct LimbVec {
    LimbEntry* mpBegin;
    LimbEntry* mpEnd;
    LimbEntry& operator[](int i) { return mpBegin[i]; }
    int size() const { return (int)(mpEnd - mpBegin); }
};
struct Model {
    char pad0[0x18];
    uint32_t modelType;             // +0x18
    char pad1[0x98 - 0x1c];
    LimbVec mLimbs;                 // +0x98
};
struct ValidityBits_s004e_e9b0 {               // bitset<128>
    uint32_t w[4];
    __forceinline void set(unsigned pos, bool val)
    {
        if (pos < 0x80) {
            if (val) {
                uint32_t* p = &w[pos >> 5];
                *p |= 1u << (pos % 32);
            } else {
                uint32_t* p = &w[pos >> 5];
                *p &= ~(1u << (pos % 32));
            }
        }
    }
};
EntryOwner* FUN_00401010();                                         // 0x00401010
PropertyList_s004e_e9b0* FUN_004ee930(int idx, Model* model);                   // 0x004ee930
void GetBoolProperty(PropertyList_s004e_e9b0* pl, uint32_t id, bool& dst);      // 0x00407190
PropertyManager_s004e_e9b0* PropertyManager_Get();                              // 0x0067de30 (SP::PropertyManager)
uint32_t RemapTypeId(uint32_t type);                                 // 0x00432f10
// ---- items of slice s004ee9b0 end

// ---- items of slice s004ef880 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_ProfileTick;                          // 0x015fd918
struct ValidityBits_s004e_f880 {
    uint32_t mWord[4];
    uint32_t& DoGetWord(uint32_t i) { return mWord[i >> 5]; }
    __forceinline ValidityBits_s004e_f880& set(uint32_t i, bool value) {
        if (i < 128) {
            if (value)
                DoGetWord(i) |= (1u << (i % 32));
            else
                DoGetWord(i) &= ~(1u << (i % 32));
        }
        return *this;
    }
};
struct RefCounted {
    virtual int AddRef();
    virtual int Release();
};
template<class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount(T* p = 0) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    operator T*() const { return mpObject; }
    T** GetAddress();               // @ 0x0041d870
    T** AsPPointer() { return GetAddress(); }
};
struct Property_s004e_f880 {
    char pad[0x12];
    uint16_t mType;                 // +0x12 (1 = bool)
    bool* GetBool();                // @ 0x0041e920
};
struct cPropertyList_s004e_f880 : RefCounted {
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
    virtual void v7(); virtual void v8();
    virtual bool GetProperty(uint32_t id, Property_s004e_f880*& out);   // +0x24
};
uint32_t GetConfigFromModelType(uint32_t modelType); // @ 0x00432f10 (RemapTypeId)
extern uint32_t kEditorConfigGroup;                  // 0x015daa00
struct ProfileScope {
    void* mTick;
    ProfileScope(void* t) : mTick(t) {}
};
inline void TouchProfileTick() { ProfileScope scope(g_ProfileTick); }   // value read, then discarded
inline void GetPropertyBool(cPropertyList_s004e_f880* pList, uint32_t id, bool& dst) {
    Property_s004e_f880* prop;
    if (pList && pList->GetProperty(id, prop) && prop->mType == 1)
        dst = *prop->GetBool();
}
typedef uint32_t PartPtr;
struct PartHandle {
    uint32_t mValue;
    operator uint32_t() const { return mValue; }
};
struct Elem16_s004e_f880 {
    PartPtr mKey;
    uint32_t pad[3];
};
inline bool operator==(const Elem16_s004e_f880& a, const PartPtr& b) { return a.mKey == b; }
struct Elem16Vec {
    Elem16_s004e_f880* mpBegin;
    Elem16_s004e_f880* mpEnd;
    Elem16_s004e_f880* begin() { return mpBegin; }
    Elem16_s004e_f880* end() { return mpEnd; }
    bool empty() const;             // @ 0x00526430
    Elem16_s004e_f880* Find(PartHandle id);
};
struct Elem16Map {
    Elem16Vec& operator[](const uint32_t& key);      // @ 0x004f6720
};
extern Elem16Map g_AllowedParts;                     // 0x015da884
inline Elem16_s004e_f880* FindElem(Elem16_s004e_f880* first, Elem16_s004e_f880* last, PartPtr value) {
    while (first != last && !(*first == value))
        ++first;
    return first;
}
inline Elem16_s004e_f880* Elem16Vec::Find(PartHandle id) { return FindElem(begin(), end(), id.mValue); }
struct cEditorBlock {
    uint32_t pad0[0xd4 / 4];
    int mnPartCount;                // +0xd4
    uint32_t pad1[(0xf8 - 0xd8) / 4];
    uint32_t mPartIDs[1];           // +0xf8
    PartHandle GetPartID(int i) { PartHandle h = { mPartIDs[i] }; return h; }
    uint32_t pad2[(0x1d8 - 0xfc) / 4];
};
struct BlockVec {
    cEditorBlock* mpBegin;
    cEditorBlock* mpEnd;
};
struct cEditorModel {
    uint32_t pad0[6];
    uint32_t mModelType;            // +0x18
    uint32_t pad1;
    uint32_t mSlotIDs[3];           // +0x20
    PartHandle GetSlotID(int i) { PartHandle h = { mSlotIDs[i] }; return h; }
    uint32_t pad2[(0x98 - 0x2c) / 4];
    BlockVec mBlocks;               // +0x98
};
// ---- items of slice s004ef880 end

// ---- items of slice s004f01f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double __cdecl fabs(double);
extern const float kMinSizeDefault;                  // 0x013f106c (FLT_MIN)
#pragma intrinsic(fabs)
struct ValidityBits_s004f_01f0 {
    uint32_t mWord[4];
    uint32_t& DoGetWord(uint32_t i) { return mWord[i >> 5]; }
    __forceinline ValidityBits_s004f_01f0& set(uint32_t i, bool value) {
        if (i < 128) {
            if (value)
                DoGetWord(i) |= (1u << (i % 32));
            else
                DoGetWord(i) &= ~(1u << (i % 32));
        }
        return *this;
    }
};
struct Property_s004f_01f0 {
    char pad[0x12];
    uint16_t mType;                 // +0x12 (0xd = float)
    float* GetFloat();              // @ 0x0041ea70
};
struct cPropertyList_s004f_01f0 : RefCounted {
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
    virtual void v7(); virtual void v8();
    virtual bool GetProperty(uint32_t id, Property_s004f_01f0*& out);   // +0x24
};
struct cPropertyManager {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10();
    virtual bool GetPropertyList(uint32_t id, uint32_t group, cPropertyList_s004f_01f0** ppOut);   // +0x2c
};
struct Vector3 {
    float v[3];
    Vector3() {}
    Vector3(float x, float y, float z) { v[0] = x; v[1] = y; v[2] = z; }
    float& operator[](int i) { return v[i]; }
};
struct Matrix3Base {
    float m[9];
    Matrix3Base();                  // @ 0x00402ab0 (out of line, empty)
};
struct Matrix3 : Matrix3Base {
    Matrix3() {}
    Matrix3(const Matrix3Base& o) { *(Matrix3Base*)this = o; }
};
Matrix3Base MultiplyMatrix(const Matrix3Base& a, const Matrix3Base& b);   // @ 0x0041de20
struct Transform {
    uint16_t mnFlags;               // +0x00
    uint16_t mnTransformCount;      // +0x02
    Vector3 mOffset;                // +0x04
    float mfScale;                  // +0x10
    Matrix3Base mRotation;          // +0x14
    Transform();                    // @ 0x00409930
    Transform& SetOffset(const Vector3& value) {
        mOffset = value;
        mnFlags |= 4;
        mnTransformCount++;
        return *this;
    }
    Transform& SetRotation(const Matrix3& value) {
        mRotation = value;
        mnFlags |= 2;
        mnTransformCount++;
        return *this;
    }
    Transform& SetScale(float value) {
        mfScale = value;
        mnTransformCount++;
        return *this;
    }
};
struct BoundingBox {
    Vector3 mMin;
    Vector3 mMax;
    BoundingBox();                                  // @ 0x00409c00 (min=+FLT_MAX, max=-FLT_MAX)
    void ApplyTransform(const Transform& t);        // @ 0x00409dd0
    void Add(const BoundingBox& b);                 // @ 0x0043f050
};
struct cEditorModelBlock {
    uint32_t mGroupID;              // +0x00
    uint32_t mInstanceID;           // +0x04
    uint32_t pad08[2];
    float mScale;                   // +0x10
    Vector3 mPosition;              // +0x14
    uint32_t pad20[6];
    Matrix3Base mOrientation;       // +0x38
    Matrix3Base mBaseOrientation;   // +0x5c
    uint32_t pad80[4];
    uint32_t mModelFlags;           // +0x90
    uint32_t mBoundsInfo[8];        // +0x94
    uint32_t padb4[(0x1d8 - 0xb4) / 4];
    cEditorModelBlock(const cEditorModelBlock& o);  // @ 0x004721e0
};
struct BlockVec_s004f_01f0 {
    cEditorModelBlock* mpBegin;
    cEditorModelBlock* mpEnd;
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    cEditorModelBlock& operator[](int i) { return mpBegin[i]; }
};
struct cEditorModel_s004f_01f0 {
    uint32_t pad0[6];
    uint32_t mModelType;            // +0x18
    uint32_t pad1[(0x98 - 0x1c) / 4];
    BlockVec_s004f_01f0 mBlocks;               // +0x98
};
struct cModelManager {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20();
    virtual bool GetBoundingBox(uint32_t instance, uint32_t group, uint32_t* info, uint32_t flags,
                                Vector3* pMin, Vector3* pMax);                  // +0x54
    virtual cPropertyList_s004f_01f0* GetPropertyList(uint32_t instance, uint32_t group);   // +0x58
};
cModelManager* ModelManager();      // @ 0x00401010
inline void GetPropertyFloat(cPropertyList_s004f_01f0* pList, uint32_t id, float& dst) {
    Property_s004f_01f0* prop;
    if (pList && pList->GetProperty(id, prop) && prop->mType == 0xd)
        dst = *prop->GetFloat();
}
inline float fabsf(float _X) { return (float)fabs((double)_X); }
// ---- items of slice s004f01f0 end

// ---- items of slice s004f1350 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct ValidityBits_s004f_1350 {
    uint32_t mWord[4];
    uint32_t& DoGetWord(uint32_t i) { return mWord[i >> 5]; }
    __forceinline ValidityBits_s004f_1350& set(uint32_t i, bool value) {
        if (i < 128) {
            if (value)
                DoGetWord(i) |= (1u << (i % 32));
            else
                DoGetWord(i) &= ~(1u << (i % 32));
        }
        return *this;
    }
};
struct Property_s004f_1350 {
    char pad[0x12];
    uint16_t mType;                 // +0x12 (1 = bool, 9 = int32, 0xd = float)
    bool* GetBool();                // @ 0x0041e920
    int* GetInt32();                // @ 0x0041e990
    float* GetFloat();              // @ 0x0041ea70
};
struct cPropertyList_s004f_1350 : RefCounted {
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
    virtual void v7(); virtual void v8();
    virtual bool GetProperty(uint32_t id, Property_s004f_1350*& out);   // +0x24
};
struct cModelManager_s004f_1350 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
    virtual void v25(); virtual void v26();
    virtual float GetComplexity(cPropertyList_s004f_1350* pList);                           // +0x6c
};
struct cEditorModelBlock_s004f_1350 {
    uint32_t mGroupID;              // +0x00
    uint32_t mInstanceID;           // +0x04
    uint32_t pad08;
    int mSymmetricParent;           // +0x0c (-1 = none)
    uint32_t pad10[(0x80 - 0x10) / 4];
    char pad80;
    bool mbIsSymmetric;             // +0x81
    char pad82[2];
    uint32_t pad84[(0x1d8 - 0x84) / 4];
    cEditorModelBlock_s004f_1350(const cEditorModelBlock_s004f_1350& o);  // @ 0x004721e0
};
struct BlockVec_s004f_1350 {
    cEditorModelBlock_s004f_1350* mpBegin;
    cEditorModelBlock_s004f_1350* mpEnd;
    int size() const { return (int)(mpEnd - mpBegin); }
    cEditorModelBlock_s004f_1350& operator[](int i) { return mpBegin[i]; }
};
struct cEditorModel_s004f_1350 {
    uint32_t pad0[6];
    uint32_t mModelType;            // +0x18
    uint32_t pad1[(0x98 - 0x1c) / 4];
    BlockVec_s004f_1350 mBlocks;               // +0x98
};
inline void GetPropertyInt(cPropertyList_s004f_1350* pList, uint32_t id, int& dst) {
    Property_s004f_1350* prop;
    if (pList && pList->GetProperty(id, prop) && prop->mType == 9)
        dst = *prop->GetInt32();
}
inline void GetPropertyFloat_s004f_1350(cPropertyList_s004f_1350* pList, uint32_t id, float& dst) {
    Property_s004f_1350* prop;
    if (pList && pList->GetProperty(id, prop) && prop->mType == 0xd)
        dst = *prop->GetFloat();
}
inline void GetPropertyBool_s004f_1350(cPropertyList_s004f_1350* pList, uint32_t id, bool& dst) {
    Property_s004f_1350* prop;
    if (pList && pList->GetProperty(id, prop) && prop->mType == 1)
        dst = *prop->GetBool();
}
// ---- items of slice s004f1350 end

// ---- items of slice s004f1ff0 begin (TODO(rewrite): local stubs, replace by canonical classes)
float FUN_004f1ff0(int a);
// ---- items of slice s004f1ff0 end

// ---- items of slice s004f2d40 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int g_150c924[];
struct Entry { int a; int b; };
extern Entry g_150c920[];
struct Bits128 { uint32_t w[4]; };
// ---- items of slice s004f2d40 end

// ---- items of slice s004f3c50 begin (TODO(rewrite): local stubs, replace by canonical classes)
inline bool AnyBit(const Bits128& x)
{
    for (unsigned int i = 0; i < 4; i++)
        if (x.w[i] != 0)
            return true;
    return false;
}
// ---- items of slice s004f3c50 end

// ---- items of slice s004f3de0 begin (TODO(rewrite): local stubs, replace by canonical classes)
template<int N> struct bitset {
    uint32_t mWord[(N + 31) / 32];

    bitset() { reset(); }
    __forceinline void reset() {
        for (uint32_t i = 0; i < (N + 31) / 32; i++)
            mWord[i] = 0;
    }
    uint32_t& DoGetWord(uint32_t i) { return mWord[i >> 5]; }
    uint32_t DoGetWord(uint32_t i) const { return mWord[i >> 5]; }
    __forceinline bool test(uint32_t i) const {
        if (i < N)
            return (DoGetWord(i) & (1u << (i % 32))) != 0;
        return false;
    }
    __forceinline bitset& set(uint32_t i, bool value) {
        if (i < N) {
            if (value)
                DoGetWord(i) |= (1u << (i % 32));
            else
                DoGetWord(i) &= ~(1u << (i % 32));
        }
        return *this;
    }
};
typedef bitset<128> ValidityBits_s004f_3de0;
namespace EA {
namespace ResourceMan {
struct Key_s004f_3de0 {
    uint32_t instanceID;   // +0
    uint32_t typeID;       // +4
    uint32_t groupID;      // +8
    Key_s004f_3de0() : instanceID(0), typeID(0), groupID(0) {}
};
}
}
template<class T> struct AutoRefCount_s004f_3de0 {
    T* mpObject;
    AutoRefCount_s004f_3de0() : mpObject(0) {}
    AutoRefCount_s004f_3de0(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount_s004f_3de0() { if (mpObject) mpObject->Release(); }
    T* get() const { return mpObject; }
    // Releases the held object, then hands out the slot for an out-parameter.
    T** AsPPointer() {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
        return &mpObject;
    }
};
namespace SP {
struct cPropertyList_s004f_3de0 : RefCounted {
    bool HasProperty(uint32_t propID);                       // @ 0x6a25a0
};
}
namespace SP {
struct cPropertyManager_s004f_3de0 {
    virtual void _v00(); virtual void _v01(); virtual void _v02(); virtual void _v03();
    virtual void _v04(); virtual void _v05(); virtual void _v06(); virtual void _v07();
    virtual void _v08(); virtual void _v09(); virtual void _v10();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, cPropertyList_s004f_3de0** ppOut);  // +0x2c
};
}
namespace SP {
bool GetPropertyAsKey(const cPropertyList_s004f_3de0* pList, uint32_t propID, EA::ResourceMan::Key_s004f_3de0* pKey);  // @ 0x6a1250
}
namespace SP {
struct cEditorModel_s004f_3de0 {
    uint32_t pad0[2];
    EA::ResourceMan::Key_s004f_3de0 mKey;                               // +0x08
    uint32_t pad1;
    uint32_t mModelType;                                     // +0x18
    uint32_t GetModelType() const { return mModelType; }
};
}
struct cEditorResource {
    uint32_t pad[0x78 / 4];
    void* mName;                                             // +0x78
    void* GetName();                                         // @ 0x414e10 (returns mName)
};
extern SP::cPropertyList_s004f_3de0* sAppProperties_s004f_3de0;                    // 0x15fd918
extern uint32_t kMinBlockCount;                              // 0x15da6e0
namespace SP {
struct cSPEditorModelValidity_s004f_3de0 {
    enum eValidityTests {
        kValidityTooComplex = 0,
        kValidityOverBudget = 1,
        kValidityIncomplete = 2,
        kValidityUnloadableTextures = 3,
        kValidityInvalidName = 4,
        kValidityInvalidParts = 5,
        kValidityInvalidParents = 6,
        kValidityInvalidScales = 7,
        kValidityOutOfBounds = 8,
        kValidityTooSmall = 9,
        kValidityNoMouth = 10,
        kValidityNotPainted = 11,
        kValidityStatsOutOfRange = 12,
        kValidityHasFloatingParts = 13,
        kValidityUnloadableBlocks = 14,
        kValidityInvalidSymmetry = 15,
        kValidityMissingPacks = 16,
        kValidityHasZeroBlocks = 17,
        kValidityInvalidPaint = 18,
        kValidityIntersectingEndEffectors = 19,
        kValidityBlankName = 20,
        kValidityBadCharacters = 21,
        kValidityTooSmallX = 22,
        kValidityTooSmallY = 23,
        kValidityTooSmallZ = 24,
        kValidityTooSmallAbsoluteZ = 25,
        kValidityFailedLoad = 26,
        kValidityInvalidLimb = 27,
        kValidityNoReason = 28
    };

    static ValidityBits_s004f_3de0 CalculateValidity(cEditorModel_s004f_3de0* model, ValidityBits_s004f_3de0 tests, bool bStopOnFirstFailure);
};  // namespace SP
}
void TestMissingPacks(SP::cEditorModel_s004f_3de0* model, ValidityBits_s004f_3de0& validity);         // @ 0x4edeb0
void TestUnloadableBlocks(SP::cEditorModel_s004f_3de0* model, ValidityBits_s004f_3de0& validity);     // @ 0x4ee3b0
void TestUnloadableTextures(SP::cEditorModel_s004f_3de0* model, ValidityBits_s004f_3de0& validity);   // @ 0x4ecec0
void TestSymmetry(SP::cEditorModel_s004f_3de0* model, ValidityBits_s004f_3de0& validity);             // @ 0x4ed7f0
void TestParents(SP::cEditorModel_s004f_3de0* model, ValidityBits_s004f_3de0& validity);              // @ 0x4ed320
void TestLimbs(SP::cEditorModel_s004f_3de0* model, ValidityBits_s004f_3de0& validity);                // @ 0x4ee9b0
void TestScales(SP::cEditorModel_s004f_3de0* model, ValidityBits_s004f_3de0& validity);               // @ 0x4ee560
void TestParts(SP::cEditorModel_s004f_3de0* model, uint32_t partsListID, ValidityBits_s004f_3de0& validity);  // @ 0x4ef880
void TestPaint(SP::cEditorModel_s004f_3de0* model, uint32_t paintListID, ValidityBits_s004f_3de0& validity);  // @ 0x4efb20
bool HasEnoughBlocks(SP::cEditorModel_s004f_3de0* model, uint32_t minBlocks, int flags);   // @ 0x4eda30
void TestComplexity(SP::cEditorModel_s004f_3de0* model, ValidityBits_s004f_3de0& validity);           // @ 0x4f1350
void TestName(void* name, ValidityBits_s004f_3de0& validity);                              // @ 0x4edf40
void TestBounds(SP::cEditorModel_s004f_3de0* model, ValidityBits_s004f_3de0& validity);               // @ 0x4ef190
void TestSize(SP::cEditorModel_s004f_3de0* model, ValidityBits_s004f_3de0& validity);                 // @ 0x4f01f0
void TestVehicleStatsInRange(SP::cEditorModel_s004f_3de0* model, ValidityBits_s004f_3de0& validity);  // @ 0x4f2610
void TestBudget(SP::cEditorModel_s004f_3de0* model, ValidityBits_s004f_3de0& validity);               // @ 0x4f2210
void TestFloatingParts(SP::cEditorModel_s004f_3de0* model, ValidityBits_s004f_3de0& validity);        // @ 0x4f3650
void TestEndEffectors(SP::cEditorModel_s004f_3de0* model, ValidityBits_s004f_3de0& validity);         // @ 0x4f31c0
inline SP::cPropertyList_s004f_3de0* AppProperties() { return sAppProperties_s004f_3de0; }
using SP::cSPEditorModelValidity_s004f_3de0;
// ---- items of slice s004f3de0 end

// ---- items of slice s004f56f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct wstring {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    unsigned int find(wchar_t c, unsigned int pos);
    void reserve(unsigned int n);        // 0x0042e610 (WString_reserve)
    void push_back(wchar_t c);           // 0x004f6510
};
extern wstring g_15da7d4;
struct Key { int a; int pad; int c; };
struct Obj {
    int f0;
    int f1;
    Obj(uint32_t a, uint32_t b) : f0(a), f1(b) {}
    bool Compare(const Key* k);
};
struct Bits {
    uint32_t w[4];
    Bits* Flip();
};
inline const unsigned int& max_alt(const unsigned int& a, const unsigned int& b)
{
    return (a < b) ? b : a;
}
struct Property_s004f_56f0 {
    char pad[0x12];
    unsigned short mType;
    bool* GetBool();                       // 0x0041e920
};
struct PropertyList_s004f_56f0 {
    virtual int Release_();                // 0
    virtual int Release();                 // +4
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
    virtual void v7(); virtual void v8();
    virtual bool GetProperty(uint32_t id, Property_s004f_56f0*& out);   // +0x24
};
struct PropListRef_s004f_56f0 {
    PropertyList_s004f_56f0* mp;
    PropListRef_s004f_56f0() : mp(0) { if (mp) mp->Release_(); }
    ~PropListRef_s004f_56f0() { if (mp) mp->Release(); }
    PropListRef_s004f_56f0* operator&();              // 0x0041d870
};
struct PropertyManager_s004f_56f0 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10();
    virtual bool GetPropertyListV(uint32_t type, uint32_t group, PropListRef_s004f_56f0* out);   // +0x2c
    inline bool GetPropertyList(uint32_t modelType, PropListRef_s004f_56f0* out);
};
inline bool PropertyManager_s004f_56f0::GetPropertyList(uint32_t modelType, PropListRef_s004f_56f0* out)
{
    return GetPropertyListV(RemapTypeId(modelType), g_ModelGroup, out);
}
struct LimbEntry_s004f_56f0 {                         // 0x1d8 bytes
    uint32_t group;                        // +0x00
    uint32_t instance;                     // +0x04
    char pad0[0xd4 - 8];
    int nIds;                              // +0xd4
    char pad1[0xf8 - 0xd8];
    uint32_t ids[1];                       // +0xf8
    char pad2[0x1d8 - 0xfc];
    uint32_t GetId(int i) const { return ids[i]; }
};
struct LimbVec_s004f_56f0 {
    LimbEntry_s004f_56f0* mpBegin;
    LimbEntry_s004f_56f0* mpEnd;
};
struct Model_s004f_56f0 {
    virtual int AddRef_();
    virtual int Release();
    char pad0[0x18 - 4];
    uint32_t modelType;                    // +0x18
    char pad1[4];
    uint32_t slots[3];                     // +0x20
    char pad2[0x98 - 0x2c];
    LimbVec_s004f_56f0 mLimbs;                        // +0x98
    uint32_t GetSlot(int i) const { return slots[i]; }
};
struct ModelRef {
    Model_s004f_56f0* mp;
    ModelRef() : mp(0) { if (mp) mp->AddRef_(); }
    ~ModelRef() { if (mp) mp->Release(); }
    ModelRef* operator&();                 // 0x0041d870 (same shape)
};
struct ResourceManager {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual bool GetResource(const Key* key, ModelRef* out, int, int, int, int);   // +0x0c
};
struct Elem16_s004f_56f0 : Key { uint32_t d; };       // 16 bytes
struct Elem16Vec_s004f_56f0 {
    Elem16_s004f_56f0* mpBegin;
    Elem16_s004f_56f0* mpEnd;
    Elem16_s004f_56f0* mpCap;
    Elem16_s004f_56f0* begin() { return mpBegin; }
    Elem16_s004f_56f0* end() { return mpEnd; }
    bool GetResourceTypeFromModelType();   // 0x00526430
};
struct KeyMap_s004f_56f0 { Elem16Vec_s004f_56f0* operator[](const uint32_t& k); };   // 0x004f6720 (thiscall, ret 4)
extern KeyMap_s004f_56f0 g_Map1_s004f_56f0;                      // 0x015da960
extern KeyMap_s004f_56f0 g_Map2_s004f_56f0;                      // 0x015da884
extern uint32_t kGroupEditorPaints;        // 0x015da880
struct UIntVec {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCap;
    uint32_t* begin() { return mpBegin; }
    uint32_t* end() { return mpEnd; }
    void erase(uint32_t* b, uint32_t* e);          // 0x004769b0
    void push_back(const uint32_t& v);             // 0x00454860
};
struct KeyVec {
    Key* mpBegin;
    Key* mpEnd;
    Key* mpCap;
    Key* begin() { return mpBegin; }
    Key* end() { return mpEnd; }
    void erase(Key* b, Key* e);                    // 0x0050f740 (copy_impl do_copy, ecx=this)
    void DoInsertValue(const Key& v);              // 0x004e19a0
};
struct KeyPred {
    uint32_t f0, f1;
    bool operator()(const Key* k) const { return k->c == f0 && k->a == f1; }
};
ResourceManager* ResourceManager_Get();            // 0x0067dcd0
void GetPropertyAsKeyInstance(PropertyList_s004f_56f0* pl, uint32_t id, uint32_t* out);   // 0x006a12a0
int FindKeyIndex(Elem16_s004f_56f0* b, Elem16_s004f_56f0* e, Obj k);     // 0x004f68f0
int FindIdIndex(Elem16_s004f_56f0* b, Elem16_s004f_56f0* e, uint32_t v); // 0x004f69e0
inline void GetBoolInline(PropertyList_s004f_56f0* pl, uint32_t id, bool& dst)
{
    if (pl) {
        Property_s004f_56f0* p;
        if (pl->GetProperty(id, p) && p->mType == 1)
            dst = *p->GetBool();
    }
}
inline uint32_t* FindU32(uint32_t* first, uint32_t* last, const uint32_t& v)
{
    while (first != last && *first != v) ++first;
    return first;
}
inline Elem16_s004f_56f0* FindElem_s004f_56f0(Elem16_s004f_56f0* first, Elem16_s004f_56f0* last, const uint32_t& v)
{
    while (first != last && first->a != v) ++first;
    return first;
}
inline Key* FindKeyA(Key* first, Key* last, const uint32_t& v)
{
    while (first != last && first->a != v) ++first;
    return first;
}
inline Elem16_s004f_56f0* FindIfObj(Elem16_s004f_56f0* first, Elem16_s004f_56f0* last, Obj pred)
{
    while (first != last && !pred.Compare(first)) ++first;
    return first;
}
inline Key* FindIfPred(Key* first, Key* last, KeyPred pred)
{
    while (first != last && !pred(first)) ++first;
    return first;
}
// ---- items of slice s004f56f0 end

// ---- items of slice s004f6630 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __cdecl EASTL_Allocate(void* alloc, size_t n, size_t align, size_t offset);  // 0x0042DEE0
void  __cdecl EASTL_allocator_deallocate(void* p);                                 // 0x00F47380
template <int N> inline void ScratchSlots_s004f_6630() { uint32_t s[N]; }
struct sp_vector_allocator { const char* mpName; };
namespace EA {
namespace ResourceMan {
struct Key_s004f_6630 {
    uint32_t mInstance;
    uint32_t mType;
    uint32_t mGroup;
};
}
}
namespace EA {
namespace ResourceMan {
inline bool operator<(const Key_s004f_6630& a, const Key_s004f_6630& b)
{
    if (a.mInstance != b.mInstance) return a.mInstance < b.mInstance;
    if (a.mGroup != b.mGroup) return a.mGroup < b.mGroup;
    return a.mType < b.mType;
}
}
}
namespace EA {
namespace ResourceMan {
inline bool operator==(const Key_s004f_6630& a, const Key_s004f_6630& b)
{
    return (a.mInstance == b.mInstance) && (a.mType == b.mType) && (a.mGroup == b.mGroup);
}
}
}
using EA::ResourceMan::Key_s004f_6630;
struct Elem16_s004f_6630 { uint32_t mData[4]; };
struct Elem16Vector {
    Elem16_s004f_6630* mpBegin;
    Elem16_s004f_6630* mpEnd;
    Elem16_s004f_6630* mpCapacity;
    sp_vector_allocator mAllocator;
    uint32_t mExtra;

    Elem16Vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    Elem16Vector(const Elem16Vector& x);
    ~Elem16Vector() {
        for (Elem16_s004f_6630* p = mpBegin; p < mpEnd; ++p) {}
        ScratchSlots_s004f_6630<3>();
        DoFreeBase();
    }
    void DoFreeBase();                                 // ~VectorBase, 0x00554B10
    void reserve(size_t n);

    inline Elem16_s004f_6630* DoAllocate(size_t n) {
        return n ? (Elem16_s004f_6630*)EASTL_Allocate(&mAllocator, n * sizeof(Elem16_s004f_6630), 4, 0) : 0;
    }
    inline void deallocate(void* p, size_t n) {
        if (((uint32_t*)p)[-1]) {
            void* q = p;
            EASTL_allocator_deallocate(q);
        }
    }
    inline void DoFree(Elem16_s004f_6630* p, size_t n) {
        if (p)
            deallocate(p, n * sizeof(Elem16_s004f_6630));
    }
};
struct rbtree_node_base {
    rbtree_node_base* mpNodeRight;
    rbtree_node_base* mpNodeLeft;
    rbtree_node_base* mpNodeParent;
    char mColor;
};
struct value_type {
    uint32_t first;
    Elem16Vector second;
    value_type(const uint32_t& a, const Elem16Vector& b) : first(a), second(b) {}
};
struct Node : rbtree_node_base {
    value_type mValue;
};
struct MapIterator {
    Node* mpNode;
    MapIterator(rbtree_node_base* pNode);              // 0x00566C50
    MapIterator(const MapIterator& x);                 // 0x005673E0
    MapIterator& operator--();                         // 0x00422C50
    value_type& operator*() const;                     // 0x00564F50
};
inline bool operator==(const MapIterator& a, const MapIterator& b) { return a.mpNode == b.mpNode; }
struct true_type {};
struct InsertResult {
    MapIterator first;
    bool second;
};
struct less_uint {
    bool operator()(const uint32_t& a, const uint32_t& b) const { return a < b; }
};
struct UIntMap {
    less_uint mCompare;
    rbtree_node_base mAnchor;
    size_t mnSize;
    sp_vector_allocator mAllocator;

    MapIterator lower_bound(const uint32_t& key);      // 0x004B5E90
    MapIterator end() { return MapIterator(&mAnchor); }
    InsertResult insert(MapIterator position, const value_type& value);  // 0x004F6B30
    MapIterator DoInsertValueImpl(rbtree_node_base* pNodeParent, const value_type& value, bool bForceToLeft);  // 0x004F7180
    InsertResult DoInsertValue(const value_type& value, true_type);    // 0x004F76C0
    MapIterator DoInsertValue(MapIterator position, const value_type& value, true_type);
    InsertResult insert_unique(const value_type& value) { return DoInsertValue(value, true_type()); }
    Elem16Vector& operator[](const uint32_t& key);
};
struct PriorityEntry {
    uint32_t mType;
    uint32_t mField4;
    uint32_t mGroup;
    int      mId;
};
struct PriorityInfo {
    uint32_t mField0;
    int mPriority;
};
struct PriorityManager {
    PriorityInfo* Find(int id);                        // 0x007DB5E0
};
PriorityManager* GetPriorityManager();                 // 0x0067DEA0
struct GroupTypeKey {
    uint32_t mGroup;
    uint32_t mType;
    GroupTypeKey(uint32_t group, uint32_t type) : mGroup(group), mType(type) {}
};
struct TypeKey {
    uint32_t mType;
    TypeKey(uint32_t type) : mType(type) {}
};
inline bool operator==(const PriorityEntry& e, const TypeKey& k) { return e.mType == k.mType; }
inline bool operator==(const PriorityEntry& e, const GroupTypeKey& k) { return (e.mGroup == k.mGroup) && (e.mType == k.mType); }
// ---- items of slice s004f6630 end

// @ 0x004e9950
void Collect9950(DeclareParam param, Vec* out)
{
    void* mgr = GetMgr401010();
    void* holder = ((Manager*)mgr)->Find(param.key, param.b);
    if (holder == 0)
        return;
    if (GetPropertyAsKey(holder, 0x3a3b9d21, &param))
        out->push_back(param);
    if (GetPropertyAsKey(holder, 0x18c1dbe0, &param))
        out->push_back(param);
    if (GetPropertyAsKey(holder, 0xf48eb09, &param))
        out->push_back(param);
    if (!GetPropertyAsKey(holder, 0x22e8410, &param)) {
        out->push_back(param);
    } else {
        ResourceMgr* rm = (ResourceMgr*)GetManager67dcd0();
        void* ref = 0;
        if (ref)
            ((Iface*)ref)->Release();
        rm->FindResource(&param, &ref, 0, 0, 0, 0);
        if (ref) {
            void* res = InterfaceCast(&ref);
            if (res) {
                char* vec = (char*)res + 0x98;
                int begin = *(int*)vec;
                int count = (*(int*)(vec + 4) - begin) / 0x1d8;
                for (int i = 0; i < count; i++) {
                    DeclareParam d;
                    d.key = *(int*)(begin + i * 0x1d8 + 4);
                    d.a = param.a;
                    d.b = *(int*)(begin + i * 0x1d8);
                    Collect9950(d, out);
                }
            }
        }
        if (ref)
            ((Iface*)ref)->Release();
    }
}
















// @ 0x004e9b40
void AddPaintKeys(DeclareParam param, Vec* out)
{
    int mid, elem, n17, p9;
    int owner, v8, n6, t33;
    void* p40;
    void* s;
    int n5;
    void* t2;
    int t23;
    int p1;
    n17 = 0x2196ad5;
    elem = 0xbd110a25;
    mid = 0xdee3d8a8;
    p9 = 0xb0e066a7;
    p40 = GetMgr401010();
    s = ((Manager*)p40)->Find(param.key, param.b);
    if (s != 0) {
        n5 = 0;
        if (GetPropertyAsKeyInstance(s, 0x2196ad5, &n5)) {
            if (n5 == 0xbd110a25) {
                out->push_back(param);
            } else if (n5 == (int)0xdee3d8a8) {
                t23 = 0;
                if (GetPropertyAsKeyArray(s, 0xb0e066a7, &t23, &t2)) {
                    for (p1 = 0; p1 < t23; p1++) {
                        if (*(int*)((char*)t2 + p1 * 0xc) != 0)
                            out->push_back(*(DeclareParam*)((char*)t2 + p1 * 0xc));
                    }
                }
            }
        }
    }
}
















// @ 0x004e9c40
void UpgradeParts(DeclareParam param, Vec* out)
{
    int hi;                       // ebp-0x14  manager
    int v9;                       // ebp-0x10  hole
    int key;                      // ebp-0xc   hole
    const int n28 = 0xf45f59d7;   // ebp-8     key constant
    int p30;                      // ebp-4     holder
    hi = (int)GetMgr401010();
    p30 = (int)((Manager*)hi)->Find(param.key, param.b);
    if (p30 != 0) {
        if (GetPropertyAsKey((void*)p30, 0xf45f59d7, &param))
            out->push_back(param);
    }
}
















// @ 0x004e9fc0
void FUN_004e9fc0(int modelType, Vec* out, int kind)
{
    cSPPalette* pal = new ("Editor", 0, 0, 0, 0) cSPPalette();
    if (pal != 0) {
        pal->AddRef();
        if (pal->Init((void*)modelType, -1, 0, 0, 0, 0, 0)) {
            PaletteIter* it = new ("Editor", 0, 0, 0, 0) PaletteIter();
            if (it != 0) {
                it->AddRef();
                it->SetPalette(pal);
                void* node = it->GetFirst(0, 0, 0, 0);
                while (node != 0) {
                    DeclareParam d;
                    d.key = *(int*)((char*)node + 0xc);
                    d.a = *(int*)((char*)node + 0x10);
                    d.b = *(int*)((char*)node + 0x14);
                    if (kind == 0)
                        Collect9950(d, out);
                    else if (kind == 1)
                        AddPaintKeys(d, out);
                    node = it->GetNext(0, 0, 0, 0);
                }
            }
            if (it != 0)
                it->Release();
        }
        pal->Release();
    }
}
















// @ 0x004ea190
void FUN_004ea190(int id, Vec* out, int flag)
{
    DeclareParam d;
    switch (id) {
    case 0xdfad9f51:
        d.key = (int)0xc15cfa84;
        d.a = 0;
        d.b = (int)(0x40000000u | (0x61u << 16) | (0x60u << 8));
        out->push_back(d);
        break;
    case 0x372e2c04:
    case 0x9ea3031a:
    case 0xccc35c46:
    case 0x4178b8e8:
    case 0x65672ade:
        d.key = 0xd05c53a3;
        d.a = 0;
        d.b = (int)(0x40000000u | (0x62u << 16) | (0x60u << 8));
        out->push_back(d);
        out->push_back(g_15dacc8);
        out->push_back(g_15dabcc);
        if (flag != 0x5bf8f774)
            FUN_004e9ca0(out);
        break;
    }
}















// @ 0x004ea720
FlagWord FUN_004ea720(int p1, int p2)
{
    FlagWord f = {0};
    f.e = 1;
    f.c = p1;
    f.b = p2;
    return f;
}















// @ 0x004ea780
void FUN_004ea780(int id, int tag, VSet* out, int param4)
{
    int v22;
    int v14;
    int v3, v1, p20;
    int idx;
    int t33;
    int t28, n36;
    void* n32;
    switch (id) {
    case 0x4178b8e8: FUN_004ea780(0x65672ade, tag, out, param4); break;
    case 0x65672ade: FUN_004ea780(0xccc35c46, tag, out, param4); break;
    case 0xccc35c46: FUN_004ea780(0x372e2c04, tag, out, param4); break;
    case 0x372e2c04: FUN_004ea780(0x9ea3031a, tag, out, param4); break;
    }
    if (tag == 0x7a926123 && id == 0x9ea3031a && param4 != 0x5bf8f774)
        FUN_004ea780(0xdfad9f51, tag, out, param4);
    v14 = 0;
    v22 = GetConfigFromModelType(id);
    if (param4 != 0)
        v22 = param4;
    n32 = PropertyManager();
    if (v14)
        ((Iface_s004e_a310*)v14)->Release();
    ((PaletteMgr*)n32)->GetConfig(v22, g_15daa00, &v14);
    if (v14) {
        p20 = 0;
        v1 = 0;
        v3 = 0;
        t33 = v14;
        if (GetPropertyAsKey((void*)t33, tag, &p20))
            out->push_back(*(DeclareParam*)&p20);
    }
    if (v14)
        ((Iface_s004e_a310*)v14)->Release();
}















// @ 0x004ea920
void FUN_004ea920(int modelType, int instance, int param3)
{
    VSet d;
    FUN_004ea780(modelType, 0xf5cbe065, &d, param3);
    VSet next;
    for (unsigned i = 0; i < (unsigned)(d.mpEnd - d.mpBegin); ++i)
        FUN_004e9fc0(&d.mpBegin[i], &next, 0);
    FUN_004ea190(modelType, &next, param3);
    eastl::sort(next.begin(), next.end());
    next.erase(eastl::unique(next.begin(), next.end()), next.end());
    ScratchSlots<4>();

    VSet size;
    FUN_004ea780(modelType, 0x7a926123, &size, param3);
    if (modelType == 0x7d433fad || modelType == (int)0x8f963dcb || modelType == 0x441cd3e6 ||
        modelType == (int)0xf670aa43 || modelType == 0x2a5147a9 || modelType == 0x1a4e0708 ||
        modelType == (int)0x9ad7d4aa || modelType == 0x1f2a25b6 || modelType == 0x449c040f ||
        modelType == (int)0xbc1041e6 || modelType == (int)0xc15695da || modelType == 0x2090a11b ||
        modelType == (int)0x98e03c0d || modelType == (int)0xc0b74287)
        FUN_004ea780(0x99e92f05, 0x7a926123, &size, param3);
    if (modelType == (int)0x99e92f05 || modelType == 0x4e3f7777 || modelType == (int)0xbdd15f3d ||
        modelType == 0x47c10953 || modelType == 0x72c49181)
        FUN_004ea780(0x7d433fad, 0x7a926123, &size, param3);
    if (param3 == (int)0xe46c381e)
        FUN_004ea780(0x9ea3031a, 0x7a926123, &size, 0);

    VSet n4;
    for (unsigned it = 0, len = size.mpEnd - size.mpBegin; it < len; ++it)
        FUN_004e9fc0(&size.mpBegin[it], &n4, 1);
    AddSpecialPaints(modelType, &n4, param3);
    eastl::sort(n4.begin(), n4.end());
    n4.erase(eastl::unique(n4.begin(), n4.end()), n4.end());
    ScratchSlots<4>();

    PropListRef src;
    int other = GetConfigFromModelType(modelType);
    if (param3 != 0)
        other = param3;
    ((PaletteMgr*)PropertyManager())->GetConfig(other, g_15daa00, (int*)&src);
    ResourceKey t15;
    if (src.mpObject)
        GetPropertyAsKey(src.mpObject, 0xf5cbe065, &t15);
    ResourceKey buf;
    if (src.mpObject)
        GetPropertyAsKey(src.mpObject, 0x7a926123, &buf);
    const uint32_t alloc = 0x53878d0;

    ListRef v39(new ("Editor", 0, 0, 0, 0) cPropertyList());
    Variant v11(next.data(), next.size());
    v39->AddProperty(alloc, &v11);
    ListRef p29(new ("Editor", 0, 0, 0, 0) cPropertyList());
    Variant pos(n4.data(), n4.size());
    p29->AddProperty(alloc, &pos);

    uint32_t result = MakeFlags(t15.instance, 0x7b, 0x6b);
    uint32_t n8 = MakeFlags(buf.instance, 0x7b, 0x6b);
    int p19 = instance;
    ((PaletteMgr*)PropertyManager())->StoreProperties(v39.mpObject, p19, result);
    ((PaletteMgr*)PropertyManager())->StoreProperties(p29.mpObject, p19, n8);
    GetResourceMgr()->Write(v39.get(), 0, GetSaveArea(0x11ac19e), 0, 0);
    GetResourceMgr()->Write(p29.get(), 0, GetSaveArea(0x11ac19e), 0, 0);
}














// @ 0x004eb930
bool FUN_004eb930(const DeclareParam& a, const DeclareParam& b)
{
    int r;
    if (a.key == b.key && a.a == b.a && a.b == b.b)
        r = 1;
    else
        r = 0;
    return *(bool*)&r;
}














// @ 0x004eb980
void FUN_004eb980(void)
{
    int v33 = 1;
    int n40 = 0;
    int len = 0x1b;
    for (; n40 < len; n40++)
        FUN_004ea920(g_150ca00[n40], 1, 0);
    FUN_004ea920(0x9ea3031a, 1, 0x5bf8f774);
    FUN_004ea920(0x9ea3031a, 1, 0xe46c381e);
}













// @ 0x004ebe20
namespace SP {
namespace EditorValidity {
void InitializeValidityData()
{
    if (!sInitialized) {
        const uint32_t validityID = 0xcc271289;
        PropertyListPtr pValidityList(0);
        PropertyManager()->GetGlobalPropertyList(validityID, pValidityList.Out());
        ScratchSlots_s004e_be20<11>();
        if (pValidityList.mpObject) {
            // Property IDs. The single-letter names are neutral on purpose: at /Od cl orders a
            // scope's locals by a hash of their names, and these reproduce the original frame.
            const uint32_t kL = 0x530593e;      // validity data version -> sValidityVersion
            const uint32_t kC = 0x56c4406;      // declared, never read
            const uint32_t kQ = 0x56c4407;      // -> sBits784
            const uint32_t kA = 0x56c4408;      // -> sBits7c4 (-1 = all of sBits784)
            const uint32_t kD = 0x14975ade;     // -> sBits9c8
            const uint32_t kK = 0x56c4409;      // -> sBitsb94 (-1 = all of sBits7c4)
            const uint32_t kF = 0x56c440a;      // -> sBitsa40 (-1 = all of sBitsb94)
            const uint32_t kG = 0x56c440b;      // -> sBits7ec
            const uint32_t kM = 0x665f744;      // -> sBits8e0
            const uint32_t kB = 0x6779140;      // -> sBitsc10
            const uint32_t kI = 0x6786653;      // -> sBitsb18
            const uint32_t kH = 0x67b80bc;      // -> sBits80c
            GetPropertyAsUInt(pValidityList.mpObject, kL, &sValidityVersion);
            const uint32_t kJ = 0x5304e04;      // extra characters string -> sValidityChars
            GetPropertyAsString16(pValidityList.mpObject, kJ, &sValidityChars);
            sValidityChars.push_back(L'"');
            sValidityChars.push_back(L'#');

            uint32_t numTypes;
            int* pTypes;

            numTypes = 0;
            GetPropertyAsIntArray(pValidityList.mpObject, kQ, &numTypes, &pTypes);
            for (int i = 0; i < (int)numTypes; i++) {
                if (pTypes[i] == -1) {     // "all" (-1) is ignored for this set
                } else {
                    sBits784.set(pTypes[i]);
                }
            }
            ExpandValidity(&sBits784);

            numTypes = 0;
            GetPropertyAsIntArray(pValidityList.mpObject, kA, &numTypes, &pTypes);
            for (int j = 0; j < (int)numTypes; j++) {
                if (pTypes[j] == -1)
                    sBits7c4 |= sBits784;
                else
                    sBits7c4.set(pTypes[j]);
            }
            ExpandValidity(&sBits7c4);

            numTypes = 0;
            GetPropertyAsIntArray(pValidityList.mpObject, kD, &numTypes, &pTypes);
            for (int k = 0; k < (int)numTypes; k++)
                sBits9c8.set(pTypes[k]);
            ExpandValidity(&sBits9c8);

            numTypes = 0;
            GetPropertyAsIntArray(pValidityList.mpObject, kM, &numTypes, &pTypes);
            for (int l = 0; l < (int)numTypes; l++)
                sBits8e0.set(pTypes[l]);
            ExpandValidity(&sBits8e0);

            numTypes = 0;
            GetPropertyAsIntArray(pValidityList.mpObject, kK, &numTypes, &pTypes);
            for (int m = 0; m < (int)numTypes; m++) {
                if (pTypes[m] == -1)
                    sBitsb94 |= sBits7c4;
                else
                    sBitsb94.set(pTypes[m]);
            }
            ExpandValidity(&sBitsb94);

            numTypes = 0;
            GetPropertyAsIntArray(pValidityList.mpObject, kF, &numTypes, &pTypes);
            for (int n = 0; n < (int)numTypes; n++) {
                if (pTypes[n] == -1)
                    sBitsa40 |= sBitsb94;
                else
                    sBitsa40.set(pTypes[n]);
            }
            ExpandValidity(&sBitsa40);

            numTypes = 0;
            GetPropertyAsIntArray(pValidityList.mpObject, kG, &numTypes, &pTypes);
            for (int o = 0; o < (int)numTypes; o++) {
                if (pTypes[o] == -1) {
                } else {
                    sBits7ec.set(pTypes[o]);
                }
            }
            ExpandValidity(&sBits7ec);

            numTypes = 0;
            GetPropertyAsIntArray(pValidityList.mpObject, kB, &numTypes, &pTypes);
            for (int p = 0; p < (int)numTypes; p++) {
                if (pTypes[p] == -1) {
                } else {
                    sBitsc10.set(pTypes[p]);
                }
            }
            ExpandValidity(&sBitsc10);

            numTypes = 0;
            GetPropertyAsIntArray(pValidityList.mpObject, kI, &numTypes, &pTypes);
            for (int q = 0; q < (int)numTypes; q++) {
                if (pTypes[q] == -1) {
                } else {
                    sBitsb18.set(pTypes[q]);
                }
            }
            ExpandValidity(&sBitsb18);

            numTypes = 0;
            GetPropertyAsIntArray(pValidityList.mpObject, kH, &numTypes, &pTypes);
            for (int r = 0; r < (int)numTypes; r++) {
                if (pTypes[r] == -1) {
                } else {
                    sBits80c.set(pTypes[r]);
                }
            }
            ExpandValidity(&sBits80c);
            ScratchSlots_s004e_be20<1>();

            sBits860.flip();
        }

        for (int typeIdx = 0, numModelTypes = 27; typeIdx < numModelTypes; typeIdx++) {
            uint32_t configID = GetConfigFromModelType(kEditorModelTypes[typeIdx]);
            PropertyListPtr pEditorConfig;
            if (PropertyManager()->GetPropertyList(configID, kGroupEditorConfigs, pEditorConfig.ResetInline())) {
                ResourceKey_s004e_be20 legalPartsKey;
                if (::SP::GetPropertyAsKey(pEditorConfig.get(), 0xf5cbe065, &legalPartsKey))
                    ReadKeysFromFile(legalPartsKey.instanceID, sLegalParts[legalPartsKey.instanceID]);
                ScratchSlots_s004e_be20<17>();
                ResourceKey_s004e_be20 legalPaintsKey;
                if (::SP::GetPropertyAsKey(pEditorConfig.get(), 0x7a926123, &legalPaintsKey))
                    ReadKeysFromFile(legalPaintsKey.instanceID, sLegalPaints[legalPaintsKey.instanceID]);
                ScratchSlots_s004e_be20<17>();
                CheckAppProperties();
            }
        }

        uint32_t cfgID = 0xe46c381e;
        PropertyListPtr pList;
        if (PropertyManager()->GetPropertyList(cfgID, kGroupEditorConfigs, pList.ResetInline())) {
            ResourceKey_s004e_be20 legalPartsKey;
            if (::SP::GetPropertyAsKey(pList.get(), 0xf5cbe065, &legalPartsKey))
                ReadKeysFromFile(legalPartsKey.instanceID, sLegalParts[legalPartsKey.instanceID]);
            ScratchSlots_s004e_be20<17>();
            ResourceKey_s004e_be20 legalPaintsKey;
            if (::SP::GetPropertyAsKey(pList.get(), 0x7a926123, &legalPaintsKey))
                ReadKeysFromFile(legalPaintsKey.instanceID, sLegalPaints[legalPaintsKey.instanceID]);
            ScratchSlots_s004e_be20<17>();
        }
        cfgID = 0xef18a560;
        if (PropertyManager()->GetPropertyList(cfgID, kGroupEditorConfigs, pList.ResetInline())) {
            ResourceKey_s004e_be20 legalPartsKey;
            if (::SP::GetPropertyAsKey(pList.get(), 0xf5cbe065, &legalPartsKey))
                ReadKeysFromFile(legalPartsKey.instanceID, sLegalParts[legalPartsKey.instanceID]);
            ScratchSlots_s004e_be20<18>();
            ResourceKey_s004e_be20 legalPaintsKey;
            if (::SP::GetPropertyAsKey(pList.get(), 0x7a926123, &legalPaintsKey))
                ReadKeysFromFile(legalPaintsKey.instanceID, sLegalPaints[legalPaintsKey.instanceID]);
            ScratchSlots_s004e_be20<17>();
        }
        ScratchSlots_s004e_be20<3>();
        sInitialized = true;
    }
}
}
}  // namespace SP::EditorValidity












// @ 0x004eda30
bool FUN_004eda30(char* res, int need, Flags128* flags)
{
    int key = *(int*)(res + 0x18);
    bool isSingleType = false;
    switch (key) {
    case 0x372e2c04: case (int)0x9ea3031a: case (int)0xccc35c46: case (int)0xdfad9f51:
    case 0x4178b8e8: case 0x65672ade:
        isSingleType = true;
        break;
    }
    if (isSingleType) {
        int good = 0;
        EntryVec* p15 = (EntryVec*)(res + 0x98);
        int iEntry = 0;
        int size = (int)(p15->mpEnd - p15->mpBegin) / 0x1d8;
        for (; iEntry < size; iEntry++) {
            ResEntry entry(*(ResEntry*)(p15->mpBegin + iEntry * 0x1d8));
            ResPtr p(0);
            ((PropMgr*)SP::PropertyManager())->GetResource(entry.b, entry.a, &p);
            if (!p.mp) {
                if (flags) flags->set(2, true);
                return false;
            }
            bool b = false;
            if (p.mp) GetBoolProperty(p.mp, 0xafff3a14, &b);
            if (b) good++;
        }
        if (good < 2) {
            if (flags) flags->set(2, true);
            return false;
        }
        return true;
    }
    EntryVec* v2 = (EntryVec*)(res + 0x98);
    if ((int)(v2->mpEnd - v2->mpBegin) / 0x1d8 < need) {
        if (flags) flags->set(2, true);
        return false;
    }
    if (flags) flags->set(2, false);
    return true;
}












// @ 0x004edeb0
bool FUN_004edeb0(int unused, Flags128* flags)
{
    (void)unused;
    if (flags)
        flags->set(16, false);
    return true;
}












// @ 0x004edf40
bool FUN_004edf40(const wchar_t* name, Flags128* flags)
{
    wchar_t ch = *name;
    if (wcscmp(name, kReservedName) == 0) {
        if (flags) {
            flags->set(20, true);
            flags->set(4, true);
        }
        return false;
    }
    for (int i = 0; i < 0x100 && ch != 0 && ch != 0; i++) {
        ch = name[i];
        if (gBadChars.find(ch, 0) != 0xffffffff) {
            if (flags) {
                flags->set(21, true);
                flags->set(4, true);
            }
            return false;
        }
    }
    if (flags) {
        flags->set(21, false);
        flags->set(20, false);
        flags->set(4, false);
    }
    return true;
}












// @ 0x004ee3b0
bool FUN_004ee3b0(char* res, Flags128* flags)
{
    EntryVec* p15 = (EntryVec*)(res + 0x98);
    int iEntry = 0;
    int size = (int)(p15->mpEnd - p15->mpBegin) / 0x1d8;
    for (; iEntry < size; iEntry++) {
        Manager* n35 = (Manager*)GetMgr401010();
        char* p12 = p15->mpBegin + iEntry * 0x1d8;
        char* v18 = p15->mpBegin + iEntry * 0x1d8;
        if (!n35->Find(*(int*)(v18 + 4), *(int*)p12)) {
            if (flags) flags->set(14, true);
            return false;
        }
    }
    if (flags) flags->set(14, false);
    return true;
}












// @ 0x004ee560
bool FUN_004ee560(char* res, Flags128* flags)
{
    EntryVec* p15 = (EntryVec*)(res + 0x98);
    int iEntry = 0;
    int size = (int)(p15->mpEnd - p15->mpBegin) / 0x1d8;
    for (; iEntry < size; iEntry++) {
        Manager* mgr = (Manager*)GetMgr401010();
        char* p12 = p15->mpBegin + iEntry * 0x1d8;
        char* v18 = p15->mpBegin + iEntry * 0x1d8;
        IRef* prop = (IRef*)mgr->Find(*(int*)(v18 + 4), *(int*)p12);
        float lo, hi;
        if (!prop) {
            if (flags) flags->set(7, true);
            return false;
        }
        if (prop->Has(0xf023ed73)) {
            PVSlot pv1;
            if (prop && prop->Get(0xf023ed73, (void**)&pv1.p) && pv1.p->type == 0xd)
                lo = *pv1.p->GetFloat();
            if (*(float*)(p15->mpBegin + iEntry * 0x1d8 + 0x10) < lo - 1.5258789e-05f) {
                if (flags) flags->set(7, true);
                return false;
            }
        }
        if (prop->Has(0xf023ed79)) {
            PVSlot pv2;
            if (prop && prop->Get(0xf023ed79, (void**)&pv2.p) && pv2.p->type == 0xd)
                hi = *pv2.p->GetFloat();
            if (hi + 1.5258789e-05f < *(float*)(p15->mpBegin + iEntry * 0x1d8 + 0x10)) {
                if (flags) flags->set(7, true);
                return false;
            }
        }
    }
    if (flags) flags->set(7, false);
    return true;
}












// @ 0x004ee930
int FUN_004ee930(unsigned int index, int res)
{
    int p12, p15, v18, n35;
    p15 = res + 0x98;
    if (index >= (unsigned int)((*(int*)(p15 + 4) - *(int*)p15) / 0x1d8))
        return 0;
    n35 = (int)GetMgr401010();
    p12 = *(int*)p15 + (int)index * 0x1d8;
    v18 = *(int*)p15 + (int)index * 0x1d8;
    return (int)((Manager*)n35)->Find(*(int*)(v18 + 4), *(int*)p12);
}











// @ 0x004ee9b0
bool TestLimbs(Model* model, ValidityBits_s004e_e9b0* flags)
{
    int type = (int)model->modelType;
    bool isRelevant = false;
    switch (type) {
    case 0x372e2c04: case (int)0x9ea3031a: case (int)0xccc35c46: case (int)0xdfad9f51:
    case 0x4178b8e8: case 0x65672ade:
        isRelevant = true;
    }
    if (!isRelevant) {
        if (flags) flags->set(27, false);
        return true;
    }
    LimbVec* pv = &model->mLimbs;
    int i = 0;
    int n = pv->size();
    for (; i < n; i++) {
        PropertyList_s004e_e9b0* pl = FUN_00401010()->GetPropertyList((*pv)[i].instance, (*pv)[i].group);
        if (!pl) {
            if (flags) flags->set(27, true);
            return false;
        }
        bool b = false;
        GetBoolProperty(pl, 0x4ff31eec, b);
        if (b) {
            int parent = (*pv)[i].parent;
            PropertyList_s004e_e9b0* pp = FUN_004ee930(parent, model);
            if (!pp) {
                if (flags) flags->set(27, true);
                return false;
            }
            bool b1 = false;
            GetBoolProperty(pp, 0x4ff31eec, b1);
            bool b2 = false;
            GetBoolProperty(pp, 0x6ff31f12, b2);
            bool b3 = false;
            GetBoolProperty(pp, 0xafff3a14, b3);
            if (!b3 && (!b1 || !b2)) {
                if (flags) flags->set(27, true);
                return false;
            }
            bool isChain = false;
            if (pl) {
                Property* prop;
                if (pl->GetProperty(0x6ff31f12, prop) && prop->mType == 1)
                    isChain = *prop->GetBool();
            }
            if (isChain) {
                int nB = 0;
                int nA = 0;
                bool ok = true;
                for (unsigned j = 0; j < (unsigned)n; j++) {
                    if ((*pv)[j].parent == i) {
                        PropertyList_s004e_e9b0* cp = FUN_004ee930(j, model);
                        bool ca = false;
                        if (cp) {
                            Property* p1;
                            if (cp->GetProperty(0x4ff31eec, p1) && p1->mType == 1)
                                ca = *p1->GetBool();
                        }
                        bool cb = false;
                        if (cp) {
                            Property* p2;
                            if (cp->GetProperty(0x6ff31f12, p2) && p2->mType == 1)
                                cb = *p2->GetBool();
                        }
                        if (cb && ca)
                            nB++;
                        else if (ca)
                            nA++;
                    }
                }
                if (!ok) {
                    if (flags) flags->set(27, true);
                    return false;
                }
                if (nA == 0 && nB == 0) {
                    if (flags) flags->set(27, true);
                    return false;
                }
            }
        }
    }
    if (flags) flags->set(27, false);
    return true;
}











// @ 0x004ef190
bool TestBounds(Model* model, ValidityBits_s004e_e9b0* flags)
{
    LimbVec* pv = &model->mLimbs;
    uint32_t type = model->modelType;
    PropListRef_s004e_e9b0 cfg;
    PropertyManager_s004e_e9b0* pm = PropertyManager_Get();
    pm->GetPropertyList(RemapTypeId(type), g_ModelGroup, &cfg);
    if (!cfg.mp) {
        if (flags) flags->set(8, true);
        return false;
    }
    float maxRadius, maxZ, minZ;
    if (cfg.mp) {
        PropertyList_s004e_e9b0* c1 = cfg.mp;
        Property* p1;
        if (c1 && c1->GetProperty(0x700db77d, p1) && p1->mType == 0xd)
            maxRadius = *p1->GetFloat();
        PropertyList_s004e_e9b0* c2 = cfg.mp;
        Property* p2;
        if (c2 && c2->GetProperty(0x2704959d, p2) && p2->mType == 0xd)
            maxZ = *p2->GetFloat();
        PropertyList_s004e_e9b0* c3 = cfg.mp;
        Property* p3;
        if (c3 && c3->GetProperty(0x44c7f29f, p3) && p3->mType == 0xd)
            minZ = *p3->GetFloat();
        maxRadius = maxRadius / 2.0f;
        int i = 0;
        int n = pv->size();
        for (; i < n; i++) {
            bool flag = false;
            PropertyList_s004e_e9b0* pl = FUN_00401010()->GetPropertyList((*pv)[i].instance, (*pv)[i].group);
            if (!pl) {
                if (flags) flags->set(8, true);
                return false;
            }
            if (pl) {
                Property* p4;
                if (pl->GetProperty(0x538a895, p4) && p4->mType == 1)
                    flag = *p4->GetBool();
            }
            if (!flag) {
                LimbEntry* e = &(*pv)[i];
                if (e->pos[2] > maxZ || minZ > (*pv)[i].pos[2]) {
                    if (flags) flags->set(8, true);
                    return false;
                }
                LimbEntry* e2 = &(*pv)[i];
                LimbEntry* e3 = &(*pv)[i];
                float x = e3->pos[0];
                float y = e2->pos[1];
                float dist = sqrtf(x * x + y * y);
                if (dist > maxRadius) {
                    if (flags) flags->set(8, true);
                    return false;
                }
            }
        }
    }
    if (flags) flags->set(8, false);
    return true;
}










// @ 0x004efb20
struct PMgr_s004ef880 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10();
    virtual bool GetPropertyList(uint32_t id, uint32_t group, cPropertyList_s004e_f880** ppOut);   // +0x2c
};
bool CheckRequiredParts(cEditorModel* model, uint32_t key, ValidityBits_s004e_f880* validity)
{
    bool p13 = true;
    bool prev = false;
    uint32_t t10 = model->mModelType;
    AutoRefCount<cPropertyList_s004e_f880> n23;
    int p16, n35, n29;
    BlockVec* n22;
    cEditorBlock* p11;
    int p14;
    ((PMgr_s004ef880*)SP::PropertyManager())->GetPropertyList(GetConfigFromModelType(t10), kEditorConfigGroup,
                                       n23.AsPPointer());
    if (!n23) {
        if (validity)
            validity->set(0x12, true);
        return false;
    }

    if (n23)
        GetPropertyBool(n23, 0x300de90b, prev);

    ScratchSlots<17>();
    Elem16Vec* p30 = &g_AllowedParts[key];
    if (p30->empty()) {
        if (validity)
            validity->set(0x12, false);
        return true;
    }

    if (prev) {
        for (p16 = 0; p16 < 3; p16++) {
            if (model->mSlotIDs[p16]) {
                if (p30->Find(model->GetSlotID(p16)) == p30->end()) {
                    if (validity)
                        validity->set(0x12, true);
                    return false;
                }
            }
            TouchProfileTick();
        }
    } else {
        n22 = &model->mBlocks;
        p11 = 0;
        for (n35 = 0, p14 = (int)(n22->mpEnd - n22->mpBegin); n35 < p14 && p13; n35++) {
            p11 = n22->mpBegin + n35;
            for (n29 = 0; n29 < p11->mnPartCount; n29++) {
                if (p30->Find(p11->GetPartID(n29)) == p30->end()) {
                    if (validity)
                        validity->set(0x12, true);
                    return false;
                }
                TouchProfileTick();
            }
        }
    }

    if (validity)
        validity->set(0x12, !p13);
    return p13;
}









// @ 0x004f01f0
enum {
    kValidityTooSmall = 9,
    kValidityTooSmallX = 22,
    kValidityTooSmallY = 23,
    kValidityTooSmallZ = 24,
    kValidityTooSmallAbsoluteZ = 25
};
bool TestSize(cEditorModel_s004f_01f0* model, ValidityBits_s004f_01f0* validity)
{
    BlockVec_s004f_01f0* blocks = &model->mBlocks;
    Vector3 minSize = Vector3(kMinSizeDefault, kMinSizeDefault, kMinSizeDefault);
    float minHeight = kMinSizeDefault;

    if (validity) {
        validity->set(kValidityTooSmallX, false);
        validity->set(kValidityTooSmallY, false);
        validity->set(kValidityTooSmallZ, false);
        validity->set(kValidityTooSmall, false);
        validity->set(kValidityTooSmallAbsoluteZ, false);
    }

    uint32_t modelType = model->mModelType;
    AutoRefCount<cPropertyList_s004f_01f0> config;
    ((cPropertyManager*)SP::PropertyManager())->GetPropertyList(GetConfigFromModelType(modelType), kEditorConfigGroup,
                                       config.AsPPointer());
    if (!config) {
        if (validity)
            validity->set(kValidityTooSmall, true);
        return false;
    }

    if (config) {
        GetPropertyFloat(config, 0x538b032, minSize[0]);
        GetPropertyFloat(config, 0x538b033, minSize[1]);
        GetPropertyFloat(config, 0x538b031, minSize[2]);
        GetPropertyFloat(config, 0x538b034, minHeight);
    }

    if (blocks->size() == 0) {
        if (validity) {
            validity->set(kValidityTooSmallX, true);
            validity->set(kValidityTooSmallY, true);
            validity->set(kValidityTooSmallZ, true);
            validity->set(kValidityTooSmall, true);
            validity->set(kValidityTooSmallAbsoluteZ, true);
        }
        return true;
    }

    BoundingBox bbox;
    bool valid = blocks->size() > 0;
    for (int i = 0, n = (int)blocks->size(); i < n; i++) {
        cEditorModelBlock block((*blocks)[i]);
        AutoRefCount<cPropertyList_s004f_01f0> blockProps =
            ModelManager()->GetPropertyList(block.mInstanceID, block.mGroupID);
        if (!blockProps) {
            if (validity)
                validity->set(kValidityTooSmall, true);
            return false;
        }
        if (blockProps) {
            BoundingBox blockBox;
            bool hasBox = ModelManager()->GetBoundingBox(block.mInstanceID, block.mGroupID,
                block.mBoundsInfo, block.mModelFlags, &blockBox.mMin, &blockBox.mMax);
            if (hasBox) {
                Transform t;
                t.SetOffset(block.mPosition);
                t.SetRotation(MultiplyMatrix(block.mBaseOrientation, block.mOrientation));
                t.SetScale(block.mScale);
                blockBox.ApplyTransform(t);
                bbox.Add(blockBox);
            } else {
                valid = false;
            }
        }
    }

    if (!valid)
        return true;

    if (minHeight > bbox.mMax[2]) {
        if (validity) {
            validity->set(kValidityTooSmallAbsoluteZ, true);
            validity->set(kValidityTooSmall, true);
        }
        return false;
    }

    for (int axis = 0; axis < 3; axis++) {
        if (minSize[axis] > fabsf(bbox.mMax[axis] - bbox.mMin[axis])) {
            if (validity) {
                switch (axis) {
                case 0: validity->set(kValidityTooSmallX, true); break;
                case 1: validity->set(kValidityTooSmallY, true); break;
                case 2: validity->set(kValidityTooSmallZ, true); break;
                }
                validity->set(kValidityTooSmall, true);
            }
            return false;
        }
    }
    return true;
}








// @ 0x004f1350
enum { kValidityTooComplex = 0 };
struct PMgr_s004f1350 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10();
    virtual bool GetPropertyList(uint32_t id, uint32_t group, cPropertyList_s004f_1350** ppOut);   // +0x2c
};
bool TestComplexity(cEditorModel_s004f_1350* model, ValidityBits_s004f_1350* validity)
{
    BlockVec_s004f_1350* n20 = &model->mBlocks;   // blocks
    float v1 = 0.0f;   // max complexity cost (0x066f72ae)
    bool self = false;   // symmetric copies count double (0x300dd020)

    uint32_t r = model->mModelType;   // model type
    AutoRefCount<cPropertyList_s004f_1350> p28;   // editor config property list
    ((PMgr_s004f1350*)SP::PropertyManager())->GetPropertyList(GetConfigFromModelType(r), kEditorConfigGroup,
                                       p28.AsPPointer());
    if (!p28) {
        if (validity)
            validity->set(kValidityTooComplex, true);
        return false;
    }

    int mid;   // limit 0x9187aee3
    int t30;   // limit 0x047c1d1b
    int p;   // limit 0x04dbc51f
    int j;   // max bones (0x0684a675)
    if (p28) {
        GetPropertyInt(p28, 0x9187aee3, mid);
        GetPropertyInt(p28, 0x047c1d1b, t30);
        GetPropertyInt(p28, 0x04dbc51f, p);
        GetPropertyFloat_s004f_1350(p28, 0x066f72ae, v1);
        GetPropertyInt(p28, 0x0684a675, j);
        GetPropertyBool_s004f_1350(p28, 0x300dd020, self);
    }

    int n = 0;   // total of 0x51fa9dfa
    int obj = 0;   // total of 0x3c652302
    int n29 = 0;   // total of 0x04460b63 flags
    float n18 = 0.0f;   // total complexity cost
    int v15 = 0;   // total bones
    bool hash = false;   // block not counted (0x02437197)
    for (int loopI = 0, loopN = n20->size(); loopI < loopN; loopI++) {
        cEditorModelBlock_s004f_1350 t12((*n20)[loopI]);   // block copy
        AutoRefCount<cPropertyList_s004f_1350> p10;   // block property list
        ((PMgr_s004f1350*)SP::PropertyManager())->GetPropertyList(t12.mInstanceID, t12.mGroupID,
                                           p10.AsPPointer());
        if (!p10) {
            if (validity)
                validity->set(kValidityTooComplex, true);
            return false;
        }

        int chunk = 0;   // block 0x51fa9dfa
        int w = 0;   // block 0x3c652302
        int n34 = 0;   // block 0x04460b63
        int p39 = 1;   // block bones
        float src = 0.0f;   // block complexity cost
        bool last = false;   // block has no symmetric copy (0xafff3a14)
        if (p10) {
            hash = false;
            GetPropertyBool_s004f_1350(p10, 0x02437197, hash);
            if (hash)
                continue;
            GetPropertyInt(p10, 0x51fa9dfa, chunk);
            GetPropertyInt(p10, 0x3c652302, w);
            GetPropertyInt(p10, 0x04460b63, n34);
            GetPropertyBool_s004f_1350(p10, 0xafff3a14, last);
            src = ((cModelManager_s004f_1350*)ModelManager())->GetComplexity(p10);
        }

        if (n34 != 2)
            n34 = 1;
        else
            n34 = 0;

        if (self && !last && t12.mSymmetricParent == -1 && !t12.mbIsSymmetric) {
            chunk *= 2;
            w *= 2;
            n34 *= 2;
            src *= 2.0f;
            p39 *= 2;
        }

        n29 += n34;
        obj += w;
        n += chunk;
        n18 += src;
        v15 += p39;
    }

    if (p != -1 && n29 > p) {
        if (validity)
            validity->set(kValidityTooComplex, true);
        return false;
    }
    if (mid != -1 && n > t30) {
        if (validity)
            validity->set(kValidityTooComplex, true);
        return false;
    }
    if (t30 != -1 && obj > mid) {
        if (validity)
            validity->set(kValidityTooComplex, true);
        return false;
    }
    if (v1 > 0.0f && n18 > v1) {
        if (validity)
            validity->set(kValidityTooComplex, true);
        return false;
    }
    if (j > 0.0f && v15 > j) {
        if (validity)
            validity->set(kValidityTooComplex, true);
        return false;
    }

    if (validity)
        validity->set(kValidityTooComplex, false);
    return true;
}







// @ 0x004f21e0
bool FUN_004f21e0(int a, int b)
{
    float f = FUN_004f1ff0(a);
    if (f <= (float)b)
        return true;
    return false;
}






// @ 0x004f3b40
int FUN_004f3b40(Bits128 a, Bits128 b)
{
    int best = -1;
    bool found = false;
    unsigned int i;
    int bestIdx;
    for (i = 0; i < 0x1c; i++) {
        bool inA = false;
        if (i < 0x80)
            inA = (a.w[i >> 5] & (1u << (i % 0x20))) != 0;
        if (inA) {
            bool inB = false;
            if (i < 0x80)
                inB = (b.w[i >> 5] & (1u << (i % 0x20))) != 0;
            if (inB) {
                int cand = g_150c924[i * 2];
                if (cand > best) {
                    best = cand;
                    bestIdx = i;
                    found = true;
                }
            }
        }
    }
    if (found)
        return bestIdx;
    return 0x1c;
}






// @ 0x004f3c40
int FUN_004f3c40(int i)
{
    return g_150c920[i].a;
}





// @ 0x004f3d60
bool FUN_004f3d60(Bits128 a, Bits128 b)
{
    unsigned int i;
    for (i = 0; i < 4; i++)
        a.w[i] &= b.w[i];
    return !AnyBit(a);
}




// @ 0x004f3de0
namespace EA { namespace ResourceMan {
struct ResourceObject : ::RefCounted { virtual void* Cast(uint32_t); };
}}
typedef AutoRefCount_s004f_3de0<EA::ResourceMan::ResourceObject> ResObjPtr3de0;
struct ResMgr3de0 {
    virtual void _v00(); virtual void _v01(); virtual void _v02();
    virtual bool GetResource(const EA::ResourceMan::Key_s004f_3de0&, EA::ResourceMan::ResourceObject**, int, int, int, int);
};
ResMgr3de0* GetResMgr3de0();              // @ 0x67dcd0
cEditorResource* objCast3de0(ResObjPtr3de0&);   // @ 0x421f60
ValidityBits_s004f_3de0 SP::cSPEditorModelValidity_s004f_3de0::CalculateValidity(cEditorModel_s004f_3de0* model, ValidityBits_s004f_3de0 tests, bool bStopOnFirstFailure)
{
    ValidityBits_s004f_3de0 validity;

    if (AppProperties()->HasProperty(0x055d7ca1))   // validation disabled by app property
        return validity;

    if (tests.test(kValidityMissingPacks)) {
        TestMissingPacks(model, validity);
        if (validity.test(kValidityMissingPacks) && bStopOnFirstFailure)
            return validity;
    }
    if (tests.test(kValidityUnloadableBlocks)) {
        TestUnloadableBlocks(model, validity);
        if (validity.test(kValidityUnloadableBlocks) && bStopOnFirstFailure)
            return validity;
    }
    if (tests.test(kValidityUnloadableTextures)) {
        TestUnloadableTextures(model, validity);
        if (validity.test(kValidityUnloadableTextures) && bStopOnFirstFailure)
            return validity;
    }
    if (tests.test(kValidityInvalidSymmetry)) {
        TestSymmetry(model, validity);
        if (validity.test(kValidityInvalidSymmetry) && bStopOnFirstFailure)
            return validity;
    }
    if (tests.test(kValidityInvalidParents)) {
        TestParents(model, validity);
        if (validity.test(kValidityInvalidParents) && bStopOnFirstFailure)
            return validity;
    }
    if (tests.test(kValidityInvalidLimb)) {
        TestLimbs(model, validity);
        if (validity.test(kValidityInvalidLimb) && bStopOnFirstFailure)
            return validity;
    }
    if (tests.test(kValidityInvalidScales)) {
        TestScales(model, validity);
        if (validity.test(kValidityInvalidScales) && bStopOnFirstFailure)
            return validity;
    }
    if (tests.test(kValidityInvalidParts)) {
        uint32_t modelConfig = Editor::GetConfigFromModelType(model->GetModelType());
        AutoRefCount_s004f_3de0<cPropertyList_s004f_3de0> propList;
        if (((SP::cPropertyManager_s004f_3de0*)SP::PropertyManager())->GetPropertyList(modelConfig, kEditorConfigGroup, propList.AsPPointer())) {
            EA::ResourceMan::Key_s004f_3de0 partsKey;
            if (GetPropertyAsKey(propList.get(), 0xf5cbe065, &partsKey))
                TestParts(model, partsKey.instanceID, validity);
            else
                validity.set(kValidityInvalidParts, true);
        } else {
            validity.set(kValidityInvalidParts, true);
        }
        if (validity.test(kValidityInvalidParts) && bStopOnFirstFailure)
            return validity;
    }
    if (tests.test(kValidityInvalidPaint)) {
        uint32_t modelConfig = Editor::GetConfigFromModelType(model->GetModelType());
        AutoRefCount_s004f_3de0<cPropertyList_s004f_3de0> propList;
        if (((SP::cPropertyManager_s004f_3de0*)SP::PropertyManager())->GetPropertyList(modelConfig, kEditorConfigGroup, propList.AsPPointer())) {
            EA::ResourceMan::Key_s004f_3de0 paintKey;
            if (::SP::GetPropertyAsKey(propList.get(), 0x7a926123, &paintKey))
                TestPaint(model, paintKey.instanceID, validity);
            else
                validity.set(kValidityInvalidPaint, true);
        } else {
            validity.set(kValidityInvalidPaint, true);
        }
        if (validity.test(kValidityInvalidPaint) && bStopOnFirstFailure)
            return validity;
    }
    if (tests.test(kValidityHasZeroBlocks)) {
        validity.set(kValidityHasZeroBlocks, !HasEnoughBlocks(model, 1, 0));
        if (validity.test(kValidityHasZeroBlocks) && bStopOnFirstFailure)
            return validity;
    }
    if (tests.test(kValidityIncomplete)) {
        validity.set(kValidityIncomplete, !HasEnoughBlocks(model, kMinBlockCount, 0));
        if (validity.test(kValidityIncomplete) && bStopOnFirstFailure)
            return validity;
    }
    if (tests.test(kValidityTooComplex)) {
        TestComplexity(model, validity);
        if (validity.test(kValidityTooComplex) && bStopOnFirstFailure)
            return validity;
    }
    if (tests.test(kValidityInvalidName)) {
        EA::ResourceMan::Key_s004f_3de0 nameKey = model->mKey;
        nameKey.typeID = 0x030bdee3;
        ResObjPtr3de0 resource(0);
        if (GetResMgr3de0()->GetResource(nameKey, resource.AsPPointer(), 0, 0, 0, 0)) {
            ::cEditorResource* pResource = objCast3de0(resource);
            TestName(pResource->GetName(), validity);
        } else {
            validity.set(kValidityInvalidName, true);
        }
        if (validity.test(kValidityInvalidName) && bStopOnFirstFailure)
            return validity;
    }
    if (tests.test(kValidityOutOfBounds)) {
        TestBounds(model, validity);
        if (validity.test(kValidityOutOfBounds) && bStopOnFirstFailure)
            return validity;
    }
    if (tests.test(kValidityTooSmall)) {
        TestSize(model, validity);
        if (validity.test(kValidityTooSmall) && bStopOnFirstFailure)
            return validity;
    }
    if (tests.test(kValidityStatsOutOfRange)) {
        TestVehicleStatsInRange(model, validity);
        if (validity.test(kValidityStatsOutOfRange) && bStopOnFirstFailure)
            return validity;
    }
    if (tests.test(kValidityOverBudget)) {
        TestBudget(model, validity);
        if (validity.test(kValidityOverBudget) && bStopOnFirstFailure)
            return validity;
    }
    if (tests.test(kValidityHasFloatingParts)) {
        TestFloatingParts(model, validity);
        if (validity.test(kValidityHasFloatingParts) && bStopOnFirstFailure)
            return validity;
    }
    if (tests.test(kValidityIntersectingEndEffectors)) {
        TestEndEffectors(model, validity);
        if (validity.test(kValidityIntersectingEndEffectors) && bStopOnFirstFailure)
            return validity;
    }
    return validity;
}



// @ 0x004f56f0
bool FUN_004f56f0(wchar_t c)
{
    if (g_15da7d4.find(c, 0) != (unsigned int)-1)
        return false;
    return true;
}



// @ 0x004f5720
bool FUN_004f5720(Model_s004f_56f0* model, UIntVec* out)
{
    out->erase(out->mpBegin, out->mpEnd);
    if (model) {
        uint32_t type = model->modelType;
        PropListRef_s004f_56f0 cfg;
        if (model) {
            PropertyManager_s004f_56f0* pm = (PropertyManager_s004f_56f0*)PropertyManager_Get();
            if (pm->GetPropertyList(model->modelType, &cfg)) {
                uint32_t k1 = 0, k2 = 0;
                bool flag = false;
                GetPropertyAsKeyInstance(cfg.mp, 0xf5cbe065, &k1);
                GetPropertyAsKeyInstance(cfg.mp, 0x7a926123, &k2);
                GetBoolInline(cfg.mp, 0x300de90b, flag);
                Elem16Vec_s004f_56f0* v1 = g_Map1_s004f_56f0[k1];
                Elem16Vec_s004f_56f0* v2 = g_Map2_s004f_56f0[k2];
                if (v2->GetResourceTypeFromModelType() || v1->GetResourceTypeFromModelType())
                    return false;
                LimbVec_s004f_56f0* limbs = &model->mLimbs;
                LimbEntry_s004f_56f0* limb = 0;
                int i = 0;
                int count = (int)(limbs->mpEnd - limbs->mpBegin);
                for (; i < count; i++) {
                    limb = &limbs->mpBegin[i];
                    Obj key(limb->group, limb->instance);
                    uint32_t idx = FindKeyIndex(v1->begin(), v1->end(), key);
                    if (idx != -1) {
                        uint32_t* it = FindU32(out->begin(), out->end(), idx);
                        if (it == out->end())
                            out->push_back(idx);
                    }
                }
                if (flag) {
                    for (int s = 0; s < 3; s++) {
                        if (model->slots[s] != 0) {
                            uint32_t id = model->GetSlot(s);
                            uint32_t idx = FindIdIndex(v2->begin(), v2->end(), id);
                            if (idx != -1) {
                                uint32_t* it = FindU32(out->begin(), out->end(), idx);
                                if (it == out->end())
                                    out->push_back(idx);
                            }
                        }
                    }
                } else {
                    LimbVec_s004f_56f0* l2 = &model->mLimbs;
                    LimbEntry_s004f_56f0* e = 0;
                    int j = 0;
                    int n2 = (int)(l2->mpEnd - l2->mpBegin);
                    for (; j < n2; j++) {
                        e = &l2->mpBegin[j];
                        for (int m = 0; m < e->nIds; m++) {
                            uint32_t id = e->GetId(m);
                            uint32_t idx = FindIdIndex(v2->begin(), v2->end(), id);
                            if (idx != -1) {
                                uint32_t* it = FindU32(out->begin(), out->end(), idx);
                                if (it == out->end())
                                    out->push_back(idx);
                            }
                        }
                    }
                }
            }
        }
        return true;
    } else {
        return false;
    }
}



// @ 0x004f5c60
bool GetListOfUnknownPartsAndPaints(const Key* modelKey, KeyVec* parts, KeyVec* paints)
{
    parts->erase(parts->mpBegin, parts->mpEnd);
    paints->erase(paints->mpBegin, paints->mpEnd);
    ModelRef ref;
    if (ResourceManager_Get()->GetResource(modelKey, &ref, 0, 0, 0, 0)) {
        Model_s004f_56f0* model = ref.mp;
        if (model) {
            uint32_t type = model->modelType;
            PropListRef_s004f_56f0 cfg;
            if (model) {
                PropertyManager_s004f_56f0* pm = (PropertyManager_s004f_56f0*)PropertyManager_Get();
            if (pm->GetPropertyList(model->modelType, &cfg)) {
                    uint32_t k1 = 0, k2 = 0;
                    bool flag = false;
                    GetPropertyAsKeyInstance(cfg.mp, 0xf5cbe065, &k1);
                    GetPropertyAsKeyInstance(cfg.mp, 0x7a926123, &k2);
                    GetBoolInline(cfg.mp, 0x300de90b, flag);
                    Elem16Vec_s004f_56f0* v1 = g_Map1_s004f_56f0[k1];
                    Elem16Vec_s004f_56f0* v2 = g_Map2_s004f_56f0[k2];
                    if (v2->GetResourceTypeFromModelType() || v1->GetResourceTypeFromModelType())
                        return false;
                    LimbVec_s004f_56f0* limbs = &model->mLimbs;
                    LimbEntry_s004f_56f0* limb = 0;
                    int i = 0;
                    int count = (int)(limbs->mpEnd - limbs->mpBegin);
                    for (; i < count; i++) {
                        limb = &limbs->mpBegin[i];
                        Obj key(limb->group, limb->instance);
                        Elem16_s004f_56f0* it = FindIfObj(v1->begin(), v1->end(), key);
                        if (it == v1->end()) {
                            Obj key2(limb->group, limb->instance);
                            KeyPred pred;
                            pred.f0 = key2.f0;
                            pred.f1 = key2.f1;
                            Key* p = FindIfPred(parts->begin(), parts->end(), pred);
                            if (p == parts->end()) {
                                Key k;
                                k.a = limb->instance;
                                k.pad = 0xb1b104;
                                k.c = limb->group;
                                parts->DoInsertValue(k);
                            }
                        }
                    }
                    if (flag) {
                        for (int s = 0; s < 3; s++) {
                            if (model->slots[s] != 0) {
                                uint32_t id = model->GetSlot(s);
                                Elem16_s004f_56f0* it = FindElem_s004f_56f0(v2->begin(), v2->end(), id);
                                if (it == v2->end()) {
                                    uint32_t id2 = model->GetSlot(s);
                                    if (FindKeyA(paints->begin(), paints->end(), id2) == paints->end()) {
                                        Key k;
                                        k.a = model->GetSlot(s);
                                        k.pad = 0xb1b104;
                                        k.c = kGroupEditorPaints;
                                        paints->DoInsertValue(k);
                                    }
                                }
                            }
                        }
                    } else {
                        LimbVec_s004f_56f0* l2 = &model->mLimbs;
                        LimbEntry_s004f_56f0* e = 0;
                        int j = 0;
                        int n2 = (int)(l2->mpEnd - l2->mpBegin);
                        for (; j < n2; j++) {
                            e = &l2->mpBegin[j];
                            for (int m = 0; m < e->nIds; m++) {
                                uint32_t id = e->GetId(m);
                                Elem16_s004f_56f0* it = FindElem_s004f_56f0(v2->begin(), v2->end(), id);
                                if (it == v2->end()) {
                                    uint32_t id2 = e->GetId(m);
                                    if (FindKeyA(paints->begin(), paints->end(), id2) == paints->end()) {
                                        Key k;
                                        k.a = e->GetId(m);
                                        k.pad = 0xb1b104;
                                        k.c = kGroupEditorPaints;
                                        paints->DoInsertValue(k);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return true;
}



// @ 0x004f64d0
bool Obj::Compare(const Key* k)
{
    return k->c == f0 && k->a == f1;
}



// @ 0x004f6510
void wstring::push_back(wchar_t c)
{
    if ((mpEnd + 1) == mpCapacity) {
        const unsigned int nLen = (unsigned int)(mpEnd - mpBegin) + 1;
        const unsigned int n2 = (unsigned int)(mpCapacity - mpBegin) - 1;
        const unsigned int nNeed = (n2 > 8) ? (2 * n2) : 8;
        reserve(max_alt(nNeed, nLen));
    }
    *mpEnd++ = c;
    *mpEnd = 0;
}



// @ 0x004f65d0
Bits* Bits::Flip()
{
    unsigned int i;
    for (i = 0; i < 4; i++)
        w[i] = ~w[i];
    return this;
}


// @ 0x004f6720
Elem16Vector& UIntMap::operator[](const uint32_t& key)
{
    MapIterator itLower(lower_bound(key));
    if ((itLower == end()) || mCompare(key, (*itLower).first)) {
        itLower = insert(itLower, value_type(key, Elem16Vector())).first;
    }
    return (*itLower).second;
}


// @ 0x004f68f0
template <class T>
inline PriorityEntry* find(PriorityEntry* first, PriorityEntry* last, const T& value)
{
    while ((first != last) && !(*first == value))
        ++first;
    return first;
}
int FindLowestPriority(PriorityEntry* first, PriorityEntry* last, uint32_t group, uint32_t type)
{
    int minPriority = 0x7FFFFFFF;
    int bestId = -1;
    PriorityEntry* cur = first;
    for (;;) {
        cur = find(cur, last, GroupTypeKey(group, type));
        if (cur != last) {
            const int id = cur->mId;
            PriorityInfo* const pInfo = GetPriorityManager() ? GetPriorityManager()->Find(id) : 0;
            if (pInfo) {
                const int priority = pInfo->mPriority;
                if (priority < minPriority) {
                    minPriority = priority;
                    bestId = id;
                }
            }
            ++cur;
        } else
            break;
    }
    return bestId;
}

// @ 0x00f3b2c0
int __stdcall _E366(int x)
{
    if (x < 2) return 0;
    if (x < 4) return 0xb1d38c08;
    if (x == 4) return 0xfa14571d;
    return 0;
}
