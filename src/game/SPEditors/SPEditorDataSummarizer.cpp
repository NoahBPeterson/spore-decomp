// src/game/SPEditors/SPEditorDataSummarizer.cpp -- migrated from slice(s) s005580e0, s005570d0, s005567e0, s00555bc0 by tools/migrate/rewrite.py
// Object file: SPEditors/SPEditorDataSummarizer.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/DateTime/DateTime.h"
#include "EA/LimitStopwatch.h"
#include "EA/Thread/Mutex.h"
#include "EA/Stopwatch.h"
#include "EA/Allocator/ZoneObject.h"
#include "SP/FunctionalMatch/DeclareParam.h"
#include <math.h>
#include "EA/ResourceMan/DatabasePackedFile.h"
#include "EA/ResourceMan/PFRecordRead.h"
#include "EA/ResourceMan/Key.h"

// unnamed retail callees and globals (address in the comment)
extern "C" long _InterlockedExchange(volatile long*, long);
extern "C" unsigned int strlen(const char*);
extern "C" int memcmp(const void*, const void*, unsigned int);
#pragma intrinsic(_InterlockedExchange)
#pragma intrinsic(strlen, memcmp)

// ---- items of slice s00555bc0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
class cVehicleModelSummarizer {
public:
    uint32_t GetResType(int arg);
};
}
// ---- items of slice s00555bc0 end

// ---- items of slice s005567e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double __cdecl fabs(double);
#pragma warning(disable: 4100 4189)
#pragma intrinsic(fabs)
namespace SP {
class cBuildingModelSummarizer {
public:
    uint32_t GetResType(int arg);
};
}
namespace SP {
namespace W1G2_56 {
class c56e30 {
public:
    uint32_t pad[0x80];
    void sub(int a, int b);   // @ 0x00556E30
};
}
}
// ---- items of slice s005567e0 end

// ---- items of slice s005570d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char g_vtbl_Summarizer[];        // 0x013ec458
extern char g_vtbl_ScalarDeleting[];    // 0x013f0958
extern char g_vtbl_SummarizerFinal[];   // 0x013f4274
class Property {
public:
    int* GetInt();                   // 0x0041e990
    uint16_t pad[9];
    uint16_t mnType;                 // +0x12 (9 = int32)
};
class PropertyList {
public:
    virtual int AddRef();
    virtual int Release();
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8();
    virtual bool GetProperty(uint32_t propertyID, Property*& result);  // +0x24
};
template <class T> class intrusive_ptr {
public:
    intrusive_ptr(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~intrusive_ptr() { if (mpObject) mpObject->Release(); }
    T* get() const { return mpObject; }
    // Releases the current reference and hands out the raw slot (0x0041d870).
    T** AsOutParam();
    T** Out() { return AsOutParam(); }
    __forceinline intrusive_ptr& operator=(T* pObject)
    {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
    T* mpObject;
};
template <class T> T** intrusive_ptr<T>::AsOutParam()
{
    if (mpObject) { T* pOld = mpObject; mpObject = 0; pOld->Release(); }
    return &mpObject;
}
struct ResourceKey {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
    ResourceKey() { instanceID = 0; typeID = 0; groupID = 0; }
    ResourceKey(int64_t inst, uint32_t type, uint32_t group)
        : instanceID((uint32_t)inst), typeID(type), groupID(group) {}
};
union GroupBits {
    uint32_t value;
    struct {
        uint32_t low : 8;
        uint32_t sub : 8;       // bits 8..15
        uint32_t kind : 8;      // bits 16..23
        uint32_t mid : 6;
        uint32_t top : 2;       // bits 30..31
    };
};
class PropertyManager {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyList** ppDst); // +0x2c
};
PropertyManager* PropertyManager_Get();                                  // 0x0067de30
bool GetPropertyAsKey(PropertyList* p33, uint32_t id, ResourceKey* out); // 0x006a1250
inline void ReadIntProperty(PropertyList* p33, uint32_t id, int& result)
{
    Property* pProp;
    if (p33 && p33->GetProperty(id, pProp) && pProp->mnType == 9)
        result = *pProp->GetInt();
}
inline ResourceKey MakeSuffixKey(const int& count, uint32_t type, uint32_t kind, uint32_t sub)
{
    GroupBits g;
    g.value = 0;
    g.top = 1;
    g.kind = kind;
    g.sub = sub;
    return ResourceKey(count, type, g.value);
}
struct cValidationRoot {
    uint32_t mField;        // +4
    virtual ~cValidationRoot() {}
    cValidationRoot() : mField(0) {}
};
struct cValidationBase : cValidationRoot {
    virtual ~cValidationBase() {}
    cValidationBase() {}
};
namespace SP {
class cContentValidationSummarizer {
public:
    void* vptr;             // +0
    uint32_t mField;        // +4
    cContentValidationSummarizer();
    uint32_t GetResType(int arg);
};
}
namespace SP {
namespace W1G2_57 {
class c557c90 : public cValidationBase {
public:
    ResourceKey mKeyA;          // +0x08 (read from property 0x195e035)
    ResourceKey mKey0, mKey1, mKey2, mKey3, mKey4, mKey5, mKey6, mKey7;   // +0x14 .. +0x68
    virtual ~c557c90() {}
    c557c90();                                      // 0x005570d0
    bool IsAllowed(const ResourceKey& key, int);    // 0x00557cf0
    uint32_t GetResType(int arg);                   // 0x00557c90
};
}
}
namespace SP {
namespace W1G2_57 {
inline bool operator==(const ResourceKey& a, const ResourceKey& b)
{
    return a.instanceID == b.instanceID && a.typeID == b.typeID && a.groupID == b.groupID;
}
}
}
// ---- items of slice s005570d0 end

// ---- items of slice s005580e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
template<int N> inline void ScratchSlots() { uint32_t s[N]; }
namespace eastl {
struct allocator_tag { allocator_tag() {} };
}
namespace eastl {
struct allocator_s0055_80e0 {
    allocator_s0055_80e0() {}
    allocator_s0055_80e0(const allocator_tag& tag);
    const char* mpName;
    uint32_t mFlags;
};
}
namespace eastl {
struct sp_vector_allocator_s0055_80e0 : public allocator_s0055_80e0 { sp_vector_allocator_s0055_80e0() {} };
}
namespace eastl {
template<typename T, typename A>
struct VectorBase_s0055_80e0 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    A mAllocator;
    VectorBase_s0055_80e0() : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator() {}
    VectorBase_s0055_80e0(const allocator_tag& a) : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(a) {}
    ~VectorBase_s0055_80e0();
};
}
namespace eastl {
template<typename T, typename A>
class vector_s0055_80e0 : public VectorBase_s0055_80e0<T, A> {
public:
    vector_s0055_80e0() { ScratchSlots<1>(); }
    vector_s0055_80e0(const vector_s0055_80e0& x);
    ~vector_s0055_80e0();
    void push_back(const T& value);
};
}
namespace eastl {
template<typename T>
inline void destruct(T* first, T* last) {
    for (; first < last; ++first)
        first->~T();
}
}
namespace eastl {
template<typename T>
class vector_s0055_80e0<T, allocator_s0055_80e0> : public VectorBase_s0055_80e0<T, allocator_s0055_80e0> {
public:
    typedef VectorBase_s0055_80e0<T, allocator_s0055_80e0> base_type;
    vector_s0055_80e0(const allocator_tag& a = allocator_tag()) : base_type(a) { ScratchSlots<10>(); }
    ~vector_s0055_80e0() { ScratchSlots<2>(); destruct(base_type::mpBegin, base_type::mpEnd); }
    size_t size() const { return (size_t)(base_type::mpEnd - base_type::mpBegin); }
    T& operator[](size_t n) { return *(base_type::mpBegin + n); }
};
}
namespace SP {
namespace FunctionalMatch {
enum eType_s0055_80e0 {
    kInteger_s0055_80e0 = 48342877,
    kFloat_s0055_80e0 = 48343039,
    kTerminal_s0055_80e0 = 48343507,
    kNotEqual_s0055_80e0 = 0xcba453f7
};
}
}
namespace SP {
namespace FunctionalMatch {
struct DeclareParam_s0055_80e0 {
    unsigned int mParameter;
    eType_s0055_80e0 mType;
    union { int mIntVal; float mFloatVal; };
    DeclareParam_s0055_80e0();
    DeclareParam_s0055_80e0(unsigned int param, float value);
    DeclareParam_s0055_80e0(unsigned int param, int value);
};
}
}
struct ResourceKey_s0055_80e0 {
    uint32_t mInstanceID;
    uint32_t mTypeID;
    uint32_t mGroupID;
    ResourceKey_s0055_80e0() : mInstanceID(0), mTypeID(0), mGroupID(0) {}
    ResourceKey_s0055_80e0(uint32_t instance, uint32_t type, uint32_t group)
        : mInstanceID(instance), mTypeID(type), mGroupID(group) {}
};
namespace EA {
namespace IO {
struct IStream_s0055_80e0;
}
}
struct IPFRecord {
    virtual void v0();
    virtual int AddRef();
    virtual int Release();
    virtual void v3();
    virtual ResourceKey_s0055_80e0& GetKey();
    virtual void v5();
    virtual EA::IO::IStream_s0055_80e0* GetStream();
};
template<typename T>
struct IntrusivePtr {
    T* mpObject;
    IntrusivePtr() : mpObject(0) {}
    ~IntrusivePtr() { if (mpObject) mpObject->Release(); }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
    T* detach() {
        T* const pTemp = mpObject;
        mpObject = 0;
        return pTemp;
    }
    IntrusivePtr& operator=(T* pObject) {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
    T** operator&() {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
        return &mpObject;
    }
};
struct DatabasePackedFile_s0055_80e0 {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
    virtual void v0c();
    virtual bool OpenRecord(const ResourceKey_s0055_80e0& key, IPFRecord** ppRecord, int accessFlags, int a, int b, int c);  // 0x008da3d0 (DatabasePackedFile::OpenRecord)
    virtual void v0e();
    virtual bool CloseRecord(IPFRecord* pRecord);  // 0x008d9a10 (DatabasePackedFile::CloseRecord)
};
namespace SP {
 struct ResourceObject; 
}
struct IResourceManager {
    virtual void v00(); virtual void v01(); virtual void v02();
    virtual bool GetResource(const ResourceKey_s0055_80e0& key, SP::ResourceObject** ppResource, int a, int b, int c, int d);
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
    virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15();
    virtual DatabasePackedFile_s0055_80e0* FindDatabase(const ResourceKey_s0055_80e0& key);
};
namespace EA {
namespace ResourceMan {
 IResourceManager* GetManager(); 
}
}
namespace SP {
struct ResourceObject {
    virtual int AddRef();
    virtual int Release();
};
}
namespace SP {
struct cResourceBase_s0055_80e0 : public ResourceObject {
    int mnRefCount;
    ResourceKey_s0055_80e0 mKey;
    cResourceBase_s0055_80e0();
    void* AsInterface(uint32_t iid);  // 0x006abe20 (SP::cResourceBase::AsInterface)
    void SetResourceKey(const ResourceKey_s0055_80e0& key) { mKey = key; }
};
}
namespace SP {
struct cCreationResource;
}
namespace EA {
template<typename T> struct RefCountTemplate_s0055_80e0 { T mnRefCount; int Release(); };
}
struct cSummaryBase { virtual void f(); };
struct cSummaryData : public cSummaryBase, public EA::RefCountTemplate_s0055_80e0<int> {};
struct Hash128 { uint32_t mData[4]; };
extern Hash128 kCategoryCreature;
extern Hash128 kCategoryBuilding;
extern Hash128 kCategoryVehicle;
extern Hash128 kCategoryUFO;
extern Hash128 kCategoryCell;
template<> struct IntrusivePtr<SP::ResourceObject> {
    SP::ResourceObject* mpObject;
    IntrusivePtr() : mpObject(0) {}
    IntrusivePtr(SP::ResourceObject* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~IntrusivePtr() { if (mpObject) mpObject->Release(); }
    SP::ResourceObject* get() const { return mpObject; }
    SP::ResourceObject** GetAddressForUpdate();
    SP::ResourceObject** AsPPTypeParam() { return GetAddressForUpdate(); }
};
typedef IntrusivePtr<SP::ResourceObject> ResourceObjectPtr;
struct cSummaryRecord {
    int64_t GetTimestamp();
};
template<typename T> T* resource_cast(ResourceObjectPtr& p);
namespace SP {
struct cCreationResource : public cResourceBase_s0055_80e0 {
    uint32_t mField14;
    uint32_t mModelType;
    Hash128 GetCategory(bool b);
    uint32_t GetModelType() const { return mModelType; }
};
}
namespace SP {
bool FUN_004f3d60(Hash128 a, Hash128 b);
}
namespace SP {
bool GetPartIDs(cCreationResource* pResource, eastl::vector_s0055_80e0<uint32_t, eastl::allocator_s0055_80e0>& ids);
}
namespace SP {
bool AddCellUpgradeParts(cCreationResource* pResource, uint32_t instanceID, bool checkLevel);
}
namespace SP {
using namespace FunctionalMatch;
}
namespace SP {
class cContentValidationSummarizer_s0055_80e0 {
public:
    bool ExtractParameters(const ResourceKey_s0055_80e0& key, eastl::vector_s0055_80e0<DeclareParam_s0055_80e0, eastl::sp_vector_allocator_s0055_80e0>& params);
};
}
// ---- items of slice s005580e0 end

// @ 0x005567c0
namespace SP {
uint32_t cVehicleModelSummarizer::GetResType(int arg)
{
    if (!arg)
        return 0x24682294;
    return 0xffffffff;
}
}  // namespace SP

// @ 0x00556e10
namespace SP {
uint32_t cBuildingModelSummarizer::GetResType(int arg)
{
    if (arg == 0)
        return 0x2399be55;
    return 0xffffffff;
}
}  // namespace SP

// @ 0x00556e30
namespace SP { namespace W1G2_56 {
void c56e30::sub(int a, int b)
{
}
}}  // namespace SP::W1G2_56

// @ 0x005570d0
namespace SP { namespace W1G2_57 {
c557c90::c557c90()
{
    const uint32_t h = 0x280852f1;
    intrusive_ptr<PropertyList> p33(0);
    PropertyManager_Get()->GetPropertyList(h, 0x2ae0c7e, p33.Out());
    if (p33.get()) {
        uint32_t n9 = 0x4ea8a07;
        int count = 0;
        ReadIntProperty(p33.get(), n9, count);
        mKey0 = MakeSuffixKey(count, 0x476a98c7, 0x65, 0x62);
        uint32_t q = 0x4ea8f1a;
        uint32_t n3 = 0x65cce6d;
        uint32_t v13 = 0x65cce70;
        uint32_t v40 = 0x65cce73;
        uint32_t v34 = 0x65cf1b6;
        uint32_t n29 = 0x65e3a82;
        uint32_t t22 = 0x65e3a85;
        int v20 = 0;
        ReadIntProperty(p33.get(), q, v20);
        mKey1 = MakeSuffixKey(v20, 0x2399be55, 0x63, 0x62);
        ReadIntProperty(p33.get(), n3, v20);
        mKey2 = MakeSuffixKey(v20, 0x2399be55, 0x63, 0x62);
        ReadIntProperty(p33.get(), v13, v20);
        mKey3 = MakeSuffixKey(v20, 0x2399be55, 0x63, 0x62);
        ReadIntProperty(p33.get(), v40, v20);
        mKey4 = MakeSuffixKey(v20, 0x2399be55, 0x63, 0x62);
        ReadIntProperty(p33.get(), v34, v20);
        mKey5 = MakeSuffixKey(v20, 0x24682294, 0x64, 0x62);
        ReadIntProperty(p33.get(), t22, v20);
        mKey6 = MakeSuffixKey(v20, 0x24682294, 0x64, 0x62);
        ReadIntProperty(p33.get(), n29, v20);
        mKey7 = MakeSuffixKey(v20, 0x24682294, 0x64, 0x62);
    }
    p33 = 0;
    PropertyManager_Get()->GetPropertyList(0xcdf8d12f, 0x2ae0c7e, p33.Out());
    const uint32_t elem = 0x195e035;
    GetPropertyAsKey(p33.get(), elem, &mKeyA);
}
}}  // namespace SP::W1G2_57

// @ 0x00557c90
namespace SP { namespace W1G2_57 {
uint32_t c557c90::GetResType(int arg)
{
    switch (arg) {
    case 0: return 0x476a98c7;
    case 1: return 0x2399be55;
    case 2: return 0x2b978c46;
    case 3: return 0x24682294;
    }
    return 0xffffffff;
}
}}  // namespace SP::W1G2_57

// @ 0x00557cf0
namespace SP { namespace W1G2_57 {
bool c557c90::IsAllowed(const ResourceKey& key, int)
{
    if (key == mKey0 || key == mKey1 || key == mKey2 || key == mKey3 || key == mKey4 ||
        key == mKey5 || key == mKey6 || key == mKey7 || key == mKeyA)
        return false;
    else
        return true;
}
}}  // namespace SP::W1G2_57

// @ 0x00557fc0
namespace SP {
cContentValidationSummarizer::cContentValidationSummarizer()
{
    vptr = g_vtbl_Summarizer;
    mField = 0;
    vptr = g_vtbl_ScalarDeleting;
    vptr = g_vtbl_SummarizerFinal;
}
}  // namespace SP

// @ 0x00558080
namespace SP {
uint32_t cContentValidationSummarizer::GetResType(int arg)
{
    switch (arg) {
    case 0: return 0x3d97a8e4;
    case 1: return 0x2b978c46;
    case 2: return 0x2399be55;
    case 3: return 0x24682294;
    case 4: return 0x476a98c7;
    }
    return 0xffffffff;
}
}  // namespace SP

// @ 0x005582a0
namespace SP {
bool cContentValidationSummarizer_s0055_80e0::ExtractParameters(const ResourceKey_s0055_80e0& key, eastl::vector_s0055_80e0<DeclareParam_s0055_80e0, eastl::sp_vector_allocator_s0055_80e0>& params)
{
    IntrusivePtr<cSummaryData> spSummary;
    IResourceManager* pResMngr = EA::ResourceMan::GetManager();
    ResourceObjectPtr pResourceObject;
    if (!pResMngr || !pResMngr->GetResource(key, pResourceObject.AsPPTypeParam(), 0, 0, 0, 0))
        return false;

    cCreationResource* pCreation = (cCreationResource*)pResourceObject.get();
    Hash128 categoryHash = pCreation->GetCategory(true);
    bool creatureModel = FUN_004f3d60(categoryHash, kCategoryCreature);
    bool buildingType = FUN_004f3d60(categoryHash, kCategoryBuilding);
    bool bVehicle = FUN_004f3d60(categoryHash, kCategoryVehicle);
    bool isUFOModel = FUN_004f3d60(categoryHash, kCategoryUFO);
    bool isCellModel = FUN_004f3d60(categoryHash, kCategoryCell);

    if (creatureModel) {
        ResourceKey_s0055_80e0 summaryKey = pCreation->mKey;
        summaryKey.mTypeID = 0x30bdee3;
        ResourceObjectPtr pSummaryResource(0);
        if (EA::ResourceMan::GetManager()->GetResource(summaryKey, pSummaryResource.AsPPTypeParam(), 0, 0, 0, 0)) {
            cSummaryRecord* pRecord = resource_cast<cSummaryRecord>(pSummaryResource);
            if (pRecord->GetTimestamp() == -1 && pCreation->GetModelType() == 0xdfad9f51) {
                creatureModel = false;
                buildingType = false;
            }
        }
    }

    if (pCreation->GetModelType() == 0x37148141 || pCreation->GetModelType() == 0xb8669ec9 ||
        pCreation->GetModelType() == 0xbcd73e89) {
        creatureModel = false;
        bVehicle = false;
        isUFOModel = true;
        isCellModel = true;
        buildingType = false;
    }

    params.push_back(DeclareParam_s0055_80e0(0x54a32960, creatureModel != 0));
    params.push_back(DeclareParam_s0055_80e0(0x54a32961, bVehicle != 0));
    params.push_back(DeclareParam_s0055_80e0(0x665f917, isCellModel != 0));
    params.push_back(DeclareParam_s0055_80e0(0x67b82d8, buildingType != 0));

    uint32_t creatureKind = pCreation->GetModelType();
    if (creatureKind == 0xdfad9f51 && creatureModel && AddCellUpgradeParts(pCreation, 0xef18a560, true))
        params.push_back(DeclareParam_s0055_80e0(0x52def3f, 0x2f01d6d3));

    eastl::vector_s0055_80e0<uint32_t, eastl::allocator_s0055_80e0> idList;
    if (GetPartIDs(pCreation, idList)) {
        for (uint32_t i = 0; i < idList.size(); i++)
            params.push_back(DeclareParam_s0055_80e0(0x17a1c72d, (int)idList[i]));
    }
    return isUFOModel;
}
}  // namespace SP
