// Startup module, 0x00401B80..0x0040246A: a hashed "field set" key (FNV-1 hash + equality
// functors), a key-range predicate, a small ResourceKey-valued ability object, and a loader
// object that collects resources by ResourceKey.
//
// Built without optimization, like the rest of this module:
//   /Od /Ob1 /MD /Gy /TP /arch:SSE   (no /EHsc: no EH frames even around smart-pointer locals)
//
// /Od notes learned here:
//  - Stack slots are handed out scope by scope: the function's own locals first (their
//    order within a scope depends on the local NAMES, not on declaration order; the names
//    in AddResource were found by search), then each inlined function's locals as it is
//    expanded (nested scopes after the enclosing one), and finally the inlined member's
//    spilled `this`. Unused *arrays* keep their slots (unused scalars at inline scope are
//    dropped; at function scope they are kept). The original inline
//    helpers evidently had dead locals (compiled-out debug code); the `deadN[]` arrays
//    below stand in for them so the frame layout matches.
//  - `m()` value-initialization of a POD member emits `xor eax,eax; mov [ecx],eax`.
//  - A single-case `switch` produces the `je; jmp; jmp` ladder seen at 0x00401C65.
//  - memcmp() == 0 is expanded inline (`repe cmpsb`) via #pragma intrinsic.

#include <string.h>
#pragma intrinsic(memcmp)

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;

// ---------------------------------------------------------------------------
// Reference counting
// ---------------------------------------------------------------------------
struct IRefCounted {
    virtual int AddRef();
    virtual int Release();
};

// eastl::intrusive_ptr (virtual AddRef/Release)
template <class T> struct intrusive_ptr {
    T* mpObject;

    intrusive_ptr() : mpObject(0) {}
    intrusive_ptr(const intrusive_ptr& ip) : mpObject(ip.mpObject) {
        if (mpObject)
            mpObject->AddRef();
    }
    ~intrusive_ptr() {
        if (mpObject)
            mpObject->Release();
    }

    // Releases the current object and returns the slot for an out-parameter.
    T** GetAddressForWrite() {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
        {
            uint32_t dead[4];
        }
        return &mpObject;
    }
};

// Smart pointer for classes with a non-virtual Release().
template <class T> struct RefPtr {
    T* mpObject;

    RefPtr() : mpObject(0) {}
    RefPtr(T* p) : mpObject(p) {
        if (mpObject)
            mpObject->AddRef();
    }
    ~RefPtr() {
        uint32_t dead[3];
        if (mpObject)
            mpObject->Release();
    }
};

// Smart pointer without the dead debug locals (other module header).
template <class T> struct SimplePtr {
    T* mpObject;

    SimplePtr() : mpObject(0) {}
    ~SimplePtr() {
        if (mpObject)
            mpObject->Release();
    }
};

struct DefaultRefCounted {
    int Release();  // 0x00453540
};

struct Object690120 {
    int Release();  // 0x00690120
};

extern "C" long __cdecl _InterlockedExchangeAdd(volatile long*, long);
extern "C" long __cdecl _InterlockedIncrement(volatile long*);
extern "C" long __cdecl _InterlockedDecrement(volatile long*);
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedIncrement, _InterlockedDecrement)

// Thread-safe reference count at +8.
struct AtomicRefCounted {
    void* vftable;
    uint32_t mField4;
    volatile long mnRefCount;

    void AddRef() { _InterlockedIncrement(&mnRefCount); }
    int Release();
};

// @ 0x00402420
int AtomicRefCounted::Release()
{
    _InterlockedDecrement(&mnRefCount);
    if (_InterlockedExchangeAdd(&mnRefCount, 0) < 1) {
        _InterlockedIncrement(&mnRefCount);
        return 1;
    }
    return _InterlockedExchangeAdd(&mnRefCount, 0);
}

// ---------------------------------------------------------------------------
// A 16-byte record with an owning reference
// ---------------------------------------------------------------------------
struct PropertyRecord {
    uint32_t mID;
    uint32_t mValue;
    uint16_t mType;
    uint16_t mFlags;
    intrusive_ptr<IRefCounted> mpObject;

    PropertyRecord(const PropertyRecord& other);
};

// @ 0x00401b80
PropertyRecord::PropertyRecord(const PropertyRecord& other)
    : mID(other.mID), mValue(other.mValue), mType(other.mType), mFlags(other.mFlags),
      mpObject(other.mpObject)
{
}

// ---------------------------------------------------------------------------
// Field set key: hash + equality functors for a hash map keyed by a list of fields
// ---------------------------------------------------------------------------
uint32_t FNV1Hash(const void* data, uint32_t length, uint32_t hash);  // 0x00932E50

template <class T> struct vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;

    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    const T& operator[](uint32_t n) const { return mpBegin[n]; }
};

struct Field {
    uint32_t mField0;
    uint16_t mType;
    uint16_t mLength;
    const char* mpData;
};

enum { kFieldTypeNoData = 0x200 };

struct FieldSet {
    uint32_t mField0;
    uint32_t mField4;
    vector<Field*> mFields;
};

struct FieldSetHash {
    uint32_t operator()(const FieldSet& set) const;
};

struct FieldSetEqualTo {
    bool operator()(const FieldSet& a, const FieldSet& b) const;
};

// @ 0x00401bf0
uint32_t FieldSetHash::operator()(const FieldSet& set) const
{
    uint32_t hash = 0x811c9dc5;  // FNV offset basis
    for (uint32_t i = 0, count = set.mFields.size(); i < count; ++i) {
        const Field* field = set.mFields[i];
        hash = FNV1Hash(&field->mType, 2, hash);
        switch (field->mType) {
        case kFieldTypeNoData:
            break;
        default:
            hash = FNV1Hash(field->mpData, field->mLength, hash);
        }
    }
    return hash;
}

// @ 0x00401ca0
bool FieldSetEqualTo::operator()(const FieldSet& a, const FieldSet& b) const
{
    if (a.mFields.size() != b.mFields.size())
        return false;
    for (int i = 0, count = a.mFields.size(); i < count; ++i) {
        const Field* fa = a.mFields[i];
        const Field* fb = b.mFields[i];
        if (fa->mType != fb->mType)
            return false;
        if (fa->mLength != fb->mLength)
            return false;
        if (memcmp(fa->mpData, fb->mpData, fa->mLength) != 0)
            return false;
    }
    return true;
}

// ---------------------------------------------------------------------------
// Key-range predicate on a packed 32-bit id (byte fields)
// ---------------------------------------------------------------------------
struct PackedIdHolder {
    uint32_t mField0;
    uint32_t mField4;
    uint32_t mPackedId;
};

// Returns false for ids of the form 0x?? [a-f|k] [b|~] 00 with the top 5 bits clear or
// byte 2 == 'b'; true otherwise.
// @ 0x00401d90
bool IsOutsideReservedRange(const PackedIdHolder* holder)
{
    uint32_t c = holder->mPackedId;
    uint32_t b = c;
    uint32_t a = b;
    return !((a & 0xff) == 0 && (((a >> 24) & 0x1f) == 0 || ((a >> 16) & 0xff) == 0x62) &&
             (((a >> 8) & 0xff) == 0x62 || ((a >> 8) & 0xff) == 0x7e) &&
             ((a >> 16) & 0xff) >= 0x61 &&
             (((a >> 16) & 0xff) <= 0x66 || ((a >> 16) & 0xff) == 0x6b));
}

// ---------------------------------------------------------------------------
// Ability object holding a ResourceKey value (12 bytes, integer-zeroed, copied whole)
// ---------------------------------------------------------------------------
struct ResourceKey {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
};

// Zero-initialized ResourceKey member
struct ResourceKeyValue : ResourceKey {
    ResourceKeyValue() { instanceID = 0; typeID = 0; groupID = 0; }
};

// Base vtable 0x013EF094
struct AbilityBase {
    int mnRefCount;

    AbilityBase() : mnRefCount(0) {}
    virtual ~AbilityBase() {}
};

// vtable 0x013EB2D8
struct ResourceKeyAbility : AbilityBase {
    ResourceKeyValue mValue;
    bool mbDirty;

    ResourceKeyAbility();
    virtual ~ResourceKeyAbility();
    bool SetValue(const ResourceKeyValue& value);
};

// @ 0x00401e40
ResourceKeyAbility::ResourceKeyAbility() : mbDirty(false) {}

// @ 0x00401ea0 is the compiler-generated scalar deleting destructor (??_G)

// @ 0x00401ed0
ResourceKeyAbility::~ResourceKeyAbility() {}

// @ 0x00401ef0
bool ResourceKeyAbility::SetValue(const ResourceKeyValue& value)
{
    mValue = value;
    mbDirty = false;
    return true;
}

// ---------------------------------------------------------------------------
// An object owning several references (destructor only)
// ---------------------------------------------------------------------------
struct ReferenceHolder {
    uint32_t mField0;
    uint32_t mField4;
    uint32_t mField8;
    uint32_t mFieldC;
    uint32_t mField10;
    RefPtr<DefaultRefCounted> mpRef14;
    RefPtr<DefaultRefCounted> mpRef18;
    SimplePtr<Object690120> mpRef1C;
    intrusive_ptr<IRefCounted> mpRef20;
    intrusive_ptr<IRefCounted> mpRefs[3];

    ~ReferenceHolder();
};

// @ 0x00401f20
ReferenceHolder::~ReferenceHolder() {}

// ---------------------------------------------------------------------------
// Resource collector
// ---------------------------------------------------------------------------
struct Resource : IRefCounted {};

struct IResourceManager {
    virtual void Unk00();
    virtual void Unk04();
    virtual void Unk08();
    virtual void Unk0C();
    virtual void Unk10();
    virtual bool GetResource(const ResourceKey& key, Resource** ppResourceOut);
};
IResourceManager* ResourceManager();  // 0x0067DCD0

struct ICreator {
    virtual void Unk00();
    virtual void Unk04();
    virtual void Unk08();
    virtual void Unk0C();
    virtual void Unk10();
    virtual void Unk14();
    virtual void Unk18();
    virtual void Unk1C();
    virtual AtomicRefCounted* Create(uint32_t a, uint32_t b, const void* params);
};
ICreator* Creator();  // 0x0067DD60

void ConvertKey(ResourceKey* key, int mode);  // 0x0068C700

extern bool gbLoadExtraResources;  // 0x015D115C

// eastl::vector layouts (20 bytes: begin, end, capacity, 8-byte allocator)
struct ResourceKeyVectorBase {
    ResourceKey* mpBegin;
    ResourceKey* mpEnd;
    ResourceKey* mpCapacity;
    uint32_t mAllocator[2];

    ResourceKeyVectorBase() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~ResourceKeyVectorBase();  // 0x005156B0
};

struct ResourceKeyVector : ResourceKeyVectorBase {
    ~ResourceKeyVector() {
        uint32_t dead0[10];
        for (ResourceKey* p = mpBegin; p < mpEnd; ++p)
            p->~ResourceKey();
        {
            uint32_t dead1[3];
        }
    }
    void push_back(const ResourceKey& key);  // 0x004E19A0
};

struct ResourceVector {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    uint32_t mAllocator[2];

    ResourceVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~ResourceVector();                                          // 0x004B5440
    void push_back(const intrusive_ptr<Resource>& resource);   // 0x004B54B0
};

struct CreatedObjectVector {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    uint32_t mAllocator[2];

    CreatedObjectVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~CreatedObjectVector();                                         // 0x00420600
    void push_back(const RefPtr<AtomicRefCounted>& object);         // 0x00420660
};

struct Handle {
    uint32_t mValue;
};

struct ResourceCollector {
    Handle mHandle;
    uint32_t mField4;
    uint32_t mField8;
    SimplePtr<Object690120> mpOwner;
    ResourceKeyVector mMissingKeys;
    ResourceVector mResources;
    CreatedObjectVector mCreated;
    intrusive_ptr<IRefCounted> mpSlots[6];
    bool mbField64;
    bool mbField65;

    ResourceCollector();
    ~ResourceCollector();
    void AddResource(ResourceKey key);
    void AddCreated(uint32_t a, uint32_t b, const void* params);
};

// @ 0x00401ff0
ResourceCollector::ResourceCollector()
    : mHandle(), mField4(0), mField8(0), mbField64(false), mbField65(false)
{
    uint32_t unused;
}

// @ 0x004020e0
ResourceCollector::~ResourceCollector() {}

// @ 0x004021a0
void ResourceCollector::AddResource(ResourceKey key)
{
    intrusive_ptr<Resource> pResource;

    key.typeID = 0x2f4e681b;
    if (ResourceManager()->GetResource(key, pResource.GetAddressForWrite()))
        mResources.push_back(pResource);
    else
        mMissingKeys.push_back(key);

    uint32_t gid = key.groupID;
    uint32_t groupID = gid;
    ResourceKey tempKey;
    if (((groupID >> 30) & 3) == 1 && ((groupID >> 16) & 0xff) == 0x60 &&
        ((groupID >> 24) & 0x1f) == 0) {
        tempKey = key;
        ConvertKey(&tempKey, 1);
        if (ResourceManager()->GetResource(tempKey, pResource.GetAddressForWrite()))
            mResources.push_back(pResource);
        else
            mMissingKeys.push_back(tempKey);
    }

    if (!gbLoadExtraResources)
        return;

    key.typeID = 0x01c135da;
    if (ResourceManager()->GetResource(key, pResource.GetAddressForWrite()))
        mResources.push_back(pResource);
    else
        mMissingKeys.push_back(key);
}

// @ 0x00402390
void ResourceCollector::AddCreated(uint32_t a, uint32_t b, const void* params)
{
    if (params == 0)
        params = 0;
    AtomicRefCounted* object = Creator()->Create(a, b, params);
    if (object) {
        RefPtr<AtomicRefCounted> ref(object);
        mCreated.push_back(ref);
    }
}
