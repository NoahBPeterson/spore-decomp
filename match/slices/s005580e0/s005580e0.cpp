// Slice s005580e0: SP::FunctionalMatch constraints/params, content-validation parameter
// extraction, pill save records and the OTDB parameter resource factory.
// Unoptimized module: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
// Local names were chosen to reproduce the /Od name-hash stack-slot order.
#include "types.h"

template<int N> inline void ScratchSlots() { uint32_t s[N]; }

namespace eastl {
struct allocator_tag { allocator_tag() {} };
struct allocator {
    allocator() {}
    allocator(const allocator_tag& tag);
    const char* mpName;
    uint32_t mFlags;
};
struct sp_vector_allocator : public allocator { sp_vector_allocator() {} };
template<typename T, typename A>
struct VectorBase {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    A mAllocator;
    VectorBase() : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator() {}
    VectorBase(const allocator_tag& a) : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(a) {}
    ~VectorBase();
};
template<typename T, typename A>
class vector : public VectorBase<T, A> {
public:
    vector() { ScratchSlots<1>(); }
    vector(const vector& x);
    ~vector();
    void push_back(const T& value);
};
template<typename T>
inline void destruct(T* first, T* last) {
    for (; first < last; ++first)
        first->~T();
}
template<typename T>
class vector<T, allocator> : public VectorBase<T, allocator> {
public:
    typedef VectorBase<T, allocator> base_type;
    vector(const allocator_tag& a = allocator_tag()) : base_type(a) { ScratchSlots<10>(); }
    ~vector() { ScratchSlots<2>(); destruct(base_type::mpBegin, base_type::mpEnd); }
    size_t size() const { return (size_t)(base_type::mpEnd - base_type::mpBegin); }
    T& operator[](size_t n) { return *(base_type::mpBegin + n); }
};
}

namespace SP {
namespace FunctionalMatch {

enum eType {
    kInteger = 48342877,
    kFloat = 48343039,
    kTerminal = 48343507,
    kNotEqual = 0xcba453f7
};
enum Sentinel { kEndConstraint = 0 };
enum EqualConstraint { kEquals = 0 };
enum RangeConstraint { kBetween = 0 };
enum ToleranceConstraint { kWithin = 0 };
enum NotEqualConstraint { kNotEquals = 0 };
enum AnyConstraint { kAny = 0 };

struct Constraint {
    unsigned int mParameter;
    eType mType;
    union {
        struct { int mMin; int mMax; } mIntVal;
        struct { float mMin; float mMax; } mFloatVal;
    };
    eastl::vector<Constraint, eastl::sp_vector_allocator> mConstraints;

    Constraint();
    Constraint(Sentinel);
    Constraint(unsigned int param, ToleranceConstraint, float value, float tolerance);
    Constraint(unsigned int param, RangeConstraint, float minVal, float maxVal);
    Constraint(unsigned int param, EqualConstraint, int value);
    Constraint(unsigned int param, RangeConstraint, int minVal, int maxVal);
    Constraint(unsigned int param, NotEqualConstraint, int value);
    Constraint(AnyConstraint, eastl::vector<Constraint, eastl::sp_vector_allocator> constraints);
    bool IsCompound() const;
};

struct DeclareParam {
    unsigned int mParameter;
    eType mType;
    union { int mIntVal; float mFloatVal; };
    DeclareParam();
    DeclareParam(unsigned int param, float value);
    DeclareParam(unsigned int param, int value);
};

}
}

struct ResourceKey {
    uint32_t mInstanceID;
    uint32_t mTypeID;
    uint32_t mGroupID;
    ResourceKey() : mInstanceID(0), mTypeID(0), mGroupID(0) {}
    ResourceKey(uint32_t instance, uint32_t type, uint32_t group)
        : mInstanceID(instance), mTypeID(type), mGroupID(group) {}
};

namespace EA { namespace IO {
struct IStream;
bool ReadInt32(IStream* pIS, int32_t* value, size_t count, int endian);
bool WriteUint32(IStream* pIS, const uint32_t* value, size_t count, int endian);
inline bool WriteUint32(IStream* pIS, uint32_t value, int endian) { return WriteUint32(pIS, &value, 1, endian); }
}}

// Database record (vtable: +8 Release, +0x18 GetStream)
struct IPFRecord {
    virtual void v0();
    virtual int AddRef();
    virtual int Release();
    virtual void v3();
    virtual ResourceKey& GetKey();
    virtual void v5();
    virtual EA::IO::IStream* GetStream();
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

struct DatabasePackedFile {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
    virtual void v0c();
    virtual bool OpenRecord(const ResourceKey& key, IPFRecord** ppRecord, int accessFlags, int a, int b, int c);
    virtual void v0e();
    virtual bool CloseRecord(IPFRecord* pRecord);
};

namespace SP { struct ResourceObject; }
struct IResourceManager {
    virtual void v00(); virtual void v01(); virtual void v02();
    virtual bool GetResource(const ResourceKey& key, SP::ResourceObject** ppResource, int a, int b, int c, int d);
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
    virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15();
    virtual DatabasePackedFile* FindDatabase(const ResourceKey& key);
};
namespace EA { namespace ResourceMan { IResourceManager* GetManager(); }}

namespace SP {
DatabasePackedFile* GetSaveArea(uint32_t groupID);
}

void* operator new(size_t size, const char* pName, int flags = 0, unsigned debugFlags = 0, const char* file = 0, int line = 0);

namespace SP {

struct ResourceObject {
    virtual int AddRef();
    virtual int Release();
};

struct cResourceBase : public ResourceObject {
    int mnRefCount;
    ResourceKey mKey;
    cResourceBase();
    void* AsInterface(uint32_t iid);
    void SetResourceKey(const ResourceKey& key) { mKey = key; }
};

struct cCachedResource : public cResourceBase {
    uint32_t mField14;
    cCachedResource() : mField14(0) {}
};

struct ParamAllocator { ParamAllocator() {} };
struct ParamTable {
    uint32_t mData[5];
    ParamTable(const ParamAllocator& allocator = ParamAllocator());
};

class cParameterResource : public cCachedResource {
public:
    __forceinline cParameterResource() {}
    void* AsInterface(uint32_t iid);
    ParamTable mParams;
};

struct cResourceFactoryBase {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08();
    virtual bool Read(IPFRecord* pRecord, ResourceObject* pResource, int flags, uint32_t typeID);
};

class cParameterResourceFactory : public cResourceFactoryBase {
public:
    size_t GetSupportedTypes(uint32_t* types, size_t count);
    bool IsValid(uint32_t typeID, uint32_t subtypeID);
    bool CreateResource(IPFRecord* pRecord, ResourceObject*& pDst, int flags, uint32_t typeID);
};

}

struct Property {
    char pad0[0x12];
    uint16_t mnType;
    int32_t* GetValueInt32();
};

class PropertyList {
public:
    virtual int AddRef();
    virtual int Release();
    virtual void v02(); virtual void v03(); virtual void v04(); virtual void v05(); virtual void v06();
    virtual void v07(); virtual void v08();
    virtual bool GetProperty(uint32_t propertyID, Property*& pProperty) const;
};

class IPropertyManager {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyList** ppList);
};

extern uint32_t kPropGroupID;

namespace SP {
IPropertyManager* PropertyManager();
bool GetPropertyAsKey(const PropertyList* pList, uint32_t propertyID, ResourceKey& key);

inline void GetPropertyInt32(PropertyList* pList, uint32_t propertyID, int32_t& value) {
    Property* pProperty;
    ScratchSlots<1>();
    if (pList && pList->GetProperty(propertyID, pProperty) && pProperty->mnType == 9)
        value = *pProperty->GetValueInt32();
}

struct cCreationResource;
bool FUN_004ef880(cCreationResource* pResource, uint32_t instanceID, int flags);
bool FUN_004efb20(cCreationResource* pResource, uint32_t instanceID, int flags);
bool FUN_004f21e0(cCreationResource* pResource, int32_t value);

}

namespace EA {
template<typename T> struct RefCountTemplate { T mnRefCount; int Release(); };
}
struct cSummaryBase { virtual void f(); };
struct cSummaryData : public cSummaryBase, public EA::RefCountTemplate<int> {};

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
struct cCreationResource : public cResourceBase {
    uint32_t mField14;
    uint32_t mModelType;
    Hash128 GetCategory(bool b);
    uint32_t GetModelType() const { return mModelType; }
};
bool FUN_004f3d60(Hash128 a, Hash128 b);
bool GetPartIDs(cCreationResource* pResource, eastl::vector<uint32_t, eastl::allocator>& ids);
bool AddCellUpgradeParts(cCreationResource* pResource, uint32_t instanceID, bool checkLevel);
using namespace FunctionalMatch;

class cContentValidationSummarizer {
public:
    bool ExtractParameters(const ResourceKey& key, eastl::vector<DeclareParam, eastl::sp_vector_allocator>& params);
};
}


namespace SP {
// @ 0x005580e0
bool AddCellUpgradeParts(cCreationResource* pResource, uint32_t instanceID, bool checkLevel) {
    IntrusivePtr<PropertyList> pPropList;
    PropertyManager()->GetPropertyList(instanceID, kPropGroupID, &pPropList);
    bool ret = false;
    if (pPropList) {
        ResourceKey firstKey;
        bool partValid = false;
        if (GetPropertyAsKey(pPropList, 0xf5cbe065, firstKey))
            partValid = FUN_004ef880(pResource, firstKey.mInstanceID, 0);
        ResourceKey upKey;
        bool bHasUpgrade = false;
        if (GetPropertyAsKey(pPropList, 0x7a926123, upKey))
            bHasUpgrade = FUN_004efb20(pResource, upKey.mInstanceID, 0);
        bool levelOK = false;
        if (checkLevel) {
            int32_t levelValue = 0;
            GetPropertyInt32(pPropList, 0xb1b76a19, levelValue);
            levelOK = FUN_004f21e0(pResource, levelValue);
        } else {
            levelOK = true;
        }
        ret = partValid && bHasUpgrade && levelOK;
    }
    return ret;
}

}

namespace SP {
// @ 0x005582a0
bool cContentValidationSummarizer::ExtractParameters(const ResourceKey& key, eastl::vector<DeclareParam, eastl::sp_vector_allocator>& params) {
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
        ResourceKey summaryKey = pCreation->mKey;
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

    params.push_back(DeclareParam(0x54a32960, creatureModel != 0));
    params.push_back(DeclareParam(0x54a32961, bVehicle != 0));
    params.push_back(DeclareParam(0x665f917, isCellModel != 0));
    params.push_back(DeclareParam(0x67b82d8, buildingType != 0));

    uint32_t creatureKind = pCreation->GetModelType();
    if (creatureKind == 0xdfad9f51 && creatureModel && AddCellUpgradeParts(pCreation, 0xef18a560, true))
        params.push_back(DeclareParam(0x52def3f, 0x2f01d6d3));

    eastl::vector<uint32_t, eastl::allocator> idList;
    if (GetPartIDs(pCreation, idList)) {
        for (uint32_t i = 0; i < idList.size(); i++)
            params.push_back(DeclareParam(0x17a1c72d, (int)idList[i]));
    }
    return isUFOModel;
}

}

namespace SP {
namespace FunctionalMatch {

// @ 0x005587f0
Constraint::Constraint() : mType(kTerminal) {
}

// @ 0x00558830
Constraint::Constraint(Sentinel) : mType(kTerminal) {
}

// @ 0x00558880
Constraint::Constraint(unsigned int param, ToleranceConstraint, float value, float tolerance)
    : mParameter(param), mType(kFloat) {
    mFloatVal.mMin = value - tolerance;
    mFloatVal.mMax = value + tolerance;
}

// @ 0x005588f0
Constraint::Constraint(unsigned int param, RangeConstraint, float minVal, float maxVal)
    : mParameter(param), mType(kFloat) {
    mFloatVal.mMin = minVal;
    mFloatVal.mMax = maxVal;
}

// @ 0x00558960
Constraint::Constraint(unsigned int param, EqualConstraint, int value)
    : mParameter(param), mType(kInteger) {
    mIntVal.mMin = value;
    mIntVal.mMax = value + 1;
}

// @ 0x005589c0
Constraint::Constraint(unsigned int param, RangeConstraint, int minVal, int maxVal)
    : mParameter(param), mType(kInteger) {
    mIntVal.mMin = minVal;
    mIntVal.mMax = maxVal;
}

// @ 0x00558a20
Constraint::Constraint(unsigned int param, NotEqualConstraint, int value) : mType(kNotEqual) {
    Constraint lowRange(param, kBetween, (int)0x80000000, value);
    Constraint highRange(param, kBetween, value + 1, 0x7fffffff);
    mConstraints.push_back(lowRange);
    mConstraints.push_back(highRange);
    ScratchSlots<14>();
}

// @ 0x00558ae0
Constraint::Constraint(AnyConstraint, eastl::vector<Constraint, eastl::sp_vector_allocator> constraints)
    : mType(kNotEqual), mConstraints(constraints) {
    ScratchSlots<18>();
}

// @ 0x00558b20
bool Constraint::IsCompound() const {
    return mType != kInteger && mType != kFloat && mType != kNotEqual;
}

// @ 0x00558b70
DeclareParam::DeclareParam() {
    mType = kTerminal;
}

// @ 0x00558b90
DeclareParam::DeclareParam(unsigned int param, float value) {
    mParameter = param;
    mType = kFloat;
    mFloatVal = value;
}

// @ 0x00558bc0
DeclareParam::DeclareParam(unsigned int param, int value) {
    mParameter = param;
    mType = kInteger;
    mIntVal = value;
}

}
}

namespace SP {

// @ 0x00558bf0
bool IsPillRecordStale(uint32_t instanceID, int expectedValue) {
    bool valid = false;
    ResourceKey key(instanceID, 0x2d5c9b0, 0x11ac19c);
    DatabasePackedFile* pDBPF = EA::ResourceMan::GetManager()->FindDatabase(key);
    if (pDBPF) {
        IntrusivePtr<IPFRecord> pRecord;
        if (pDBPF->OpenRecord(key, &pRecord, 1, 3, 1, 0)) {
            EA::IO::IStream* pStream = pRecord->GetStream();
            int32_t nValue;
            valid = EA::IO::ReadInt32(pStream, &nValue, 1, 0) && nValue == expectedValue;
            valid = valid && EA::IO::ReadInt32(pStream, &nValue, 1, 0) && nValue == 4;
            pDBPF->CloseRecord(pRecord);
        }
    }
    return !valid;
}

// @ 0x00558d50
void WritePillRecord(uint32_t instanceID, uint32_t value) {
    DatabasePackedFile* saveArea = GetSaveArea(0x11ac19c);
    ResourceKey key(instanceID, 0x2d5c9b0, 0x11ac19c);
    IntrusivePtr<IPFRecord> record;
    if (saveArea->OpenRecord(key, &record, 2, 2, 1, 0)) {
        EA::IO::IStream* pStream = record->GetStream();
        EA::IO::WriteUint32(pStream, value, 0);
        EA::IO::WriteUint32(pStream, 4, 0);
        saveArea->CloseRecord(record);
    }
}


// @ 0x00558e40
void* cParameterResource::AsInterface(uint32_t iid) {
    if (iid == 0x670da17)
        return this;
    return cResourceBase::AsInterface(iid);
}

// @ 0x00558e70
size_t cParameterResourceFactory::GetSupportedTypes(uint32_t* types, size_t count) {
    const size_t kCount = 1;
    if (types) {
        if (count < kCount)
            return 0;
        types[0] = 0x2d5c9af;
    }
    return kCount;
}

// @ 0x00558eb0
bool cParameterResourceFactory::IsValid(uint32_t typeID, uint32_t subtypeID) {
    return typeID == 0x2d5c9af && subtypeID == 0x2d5c9af;
}

// @ 0x00558ef0
bool cParameterResourceFactory::CreateResource(IPFRecord* pRecord, ResourceObject*& pDst, int flags, uint32_t typeID) {
    if (typeID == 0x2d5c9af) {
        IntrusivePtr<cParameterResource> pResource;
        pResource = new("OTDB/ParameterResource") cParameterResource();
        if (Read(pRecord, pResource, flags, typeID)) {
            pResource->SetResourceKey(pRecord->GetKey());
            pDst = pResource.detach();
            return true;
        }
    }
    return false;
}

}
