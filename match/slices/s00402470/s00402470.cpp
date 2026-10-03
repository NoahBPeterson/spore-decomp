// Resource preloader: gathers the resource keys referenced by a set of
// property lists and tracks one asynchronous load handle.
//
// This module was built WITHOUT optimization and without C++ EH:
//   /Od /Ob1 /MD /Gy /TP
// (frame pointer, every local in memory, only inline-marked functions expanded;
// intrusive_ptr locals with destructors produce no EH frame, so no /EHsc).
//
// /Od notes learned here:
//  - local slot order depends on local NAMES, not only declaration order
//    (Gather's loop counters / outputs are named to reproduce the original layout).
//  - inline functions that take an argument which is a memory load get a stack slot
//    for it, even if the body is empty; dead locals inside inline functions still
//    reserve stack slots (used below to reproduce the original frame sizes).
//  - a `switch` with two adjacent cases compiles to `cmp lo; jl; cmp hi; jle; jmp`.
//  - a constant-0 bool argument converted to uint32_t is stored via `xor reg,reg`.
#include "types.h"

struct ResourceKey {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;

    ResourceKey() : instanceID(0), typeID(0), groupID(0) {}
    // The first parameter is bool-typed in the original (its zero is stored as `xor ecx,ecx`).
    ResourceKey(bool instance, uint32_t type, uint32_t group)
        : instanceID(instance), typeID(type), groupID(group) {}
};

// Ref-counted object with virtual AddRef (slot 0) / Release (slot 1).
struct Object {
    virtual int AddRef();
    virtual int Release();
};

template <class T>
struct intrusive_ptr {
    T* mpObject;

    intrusive_ptr() : mpObject(0) {}
    intrusive_ptr(T* p) : mpObject(p) {
        if (mpObject)
            mpObject->AddRef();
    }
    ~intrusive_ptr() {
        if (mpObject)
            mpObject->Release();
    }
    T* get() const { return mpObject; }
    intrusive_ptr& operator=(T* pObject) {
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
    // Releases the current object and hands out the raw slot as an out parameter.
    T** AsPointer() {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
        return &mpObject;
    }
    intrusive_ptr* GetOutRef();  // out-of-line (0x0041D870)
    intrusive_ptr& Out() { return *GetOutRef(); }
};

struct PropertyList : Object {};
typedef intrusive_ptr<PropertyList> PropertyListPtr;

namespace Property {
bool GetKeyValue(PropertyList* pList, uint32_t propertyID, ResourceKey* dst);  // 0x006A1250
bool GetUInt32(PropertyList* pList, uint32_t propertyID, uint32_t* dst);  // 0x006A12A0
inline bool GetKey(PropertyList* pList, uint32_t propertyID, ResourceKey* dst) {
    return GetKeyValue(pList, propertyID, dst);
}
}  // namespace Property

struct PropManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyListPtr& dst);  // +0x2C
    static PropManager* Get();  // 0x0067DE30
};

struct ConfigManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3C();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4C();
    virtual void v50(); virtual void v54();
    virtual PropertyList* FindPropertyList(uint32_t instanceID, uint32_t groupID);  // +0x58
};
ConfigManager* GetConfigManager();  // 0x00401010

void ConvertKeyType(ResourceKey* key, uint32_t typeID, int flags);  // 0x0068C6D0
extern uint32_t g_PreloadPropertyGroup;  // 0x015D12B8

// EASTL-style vector (16+ bytes). kDeadSlots: dead locals of the original inline clear().
template <class T, int kDeadSlots>
struct vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[2];

    int size() const { return (int)(mpEnd - mpBegin); }
    void reserve(int n);
    void push_back(const T& value);
    T* erase(T* first, T* last);
    void clear() {
        uint32_t unused[kDeadSlots];
        erase(mpBegin, mpEnd);
    }
};

struct PreloadItem {  // 0x1D8 bytes
    uint32_t groupID;
    uint32_t instanceID;
    uint32_t pad08[(0xd4 - 0x08) / 4];
    int resourceCount;
    uint32_t pad0D8[(0xf8 - 0xd8) / 4];
    uint32_t resourceIDs[(0x1d8 - 0xf8) / 4];
};

struct PreloadSource {
    uint32_t pad00[0x98 / 4];
    vector<PreloadItem, 7> items;
};

struct LoadHandle {
    void AddRef();  // 0x0068F950
    void Release();  // 0x00690120
    void Cancel(bool b);  // 0x00692400
    int GetState();  // 0x0068F970
};

// intrusive_ptr for LoadHandle (non-virtual AddRef/Release).
template <>
struct intrusive_ptr<LoadHandle> {
    LoadHandle* mpObject;

    LoadHandle* get() const { return mpObject; }
    intrusive_ptr& operator=(LoadHandle* pObject) {
        if (pObject != mpObject) {
            LoadHandle* const pTemp = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
    LoadHandle** AsPointer() {
        if (mpObject) {
            LoadHandle* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
        return &mpObject;
    }
    // Compiled-out validation hook; its parameter and two dead locals still take stack slots.
    static void Validate(LoadHandle* p) { uint32_t a, b; }
};

struct LoadManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C();
    virtual void OpenHandle(LoadHandle** dst);  // +0x10
};
LoadManager* GetLoadManager();  // 0x0068F4D0

enum { kLoadStateDone = 7, kLoadStateFailed = 8 };

inline bool IsLoadFinished(LoadHandle* pHandle) {
    switch (pHandle->GetState()) {
    case kLoadStateDone:
    case kLoadStateFailed:
        return true;
    default:
        return false;
    }
}

struct Preloader {
    ResourceKey mKey;                       // +0x00
    intrusive_ptr<LoadHandle> mpHandle;     // +0x0C
    vector<ResourceKey, 6> mKeys;           // +0x10
    vector<uint32_t, 7> mResources;         // +0x24
    vector<uint32_t, 7> mFiles;             // +0x38
    intrusive_ptr<Object> mpObjects[6];     // +0x4C
    bool mbActive;                          // +0x64
    bool mbFlag;                            // +0x65

    void AddKey(ResourceKey key);  // 0x004021A0
    void AddResource(uint32_t instanceID, uint32_t groupID, int flags);  // 0x00402390
    void Gather(PreloadSource* pSource, bool bSkipKeys);
    void Start(const ResourceKey& key, bool flag);
    LoadHandle* GetHandle();
    Preloader* Self();
    bool IsFinished();
    void Reset();
};

// @ 0x00402470
void Preloader::Gather(PreloadSource* pSource, bool bSkipKeys) {
    mKeys.reserve(pSource->items.size() * 4);
    mResources.reserve(pSource->items.size() * 4);
    int total = 0;
    for (int index = 0, itemCount = pSource->items.size(); !bSkipKeys && index < itemCount; ++index) {
        PreloadItem& item = pSource->items.mpBegin[index];
        PropertyListPtr pList;
        if (PropManager::Get()->GetPropertyList(item.instanceID, item.groupID, pList.Out())) {
            for (int j = 0; j < 4; ++j) {
                ResourceKey key;
                if (Property::GetKey(pList.get(), 0xf9efbb + j, &key)) {
                    AddKey(key);
                    if (j == 0) {
                        ConvertKeyType(&key, 0x61, 0);
                        AddKey(key);
                    }
                }
            }
            ResourceKey key2;
            if (Property::GetKey(pList.get(), 0xf9efc0, &key2))
                AddKey(key2);
        }
        total += item.resourceCount * 2;
    }
    mFiles.reserve(total);
    mResources.reserve(mResources.size() + mKeys.size());
    for (int index = 0, itemCount = pSource->items.size(); index < itemCount; ++index) {
        PreloadItem& item = pSource->items.mpBegin[index];
        for (int j = 0, m = item.resourceCount; j < m; ++j) {
            PropertyListPtr pList;
            if (PropManager::Get()->GetPropertyList(item.resourceIDs[j], g_PreloadPropertyGroup,
                                                    *(PropertyListPtr*)pList.AsPointer())) {
                uint32_t low = 0, high = 0;
                Property::GetUInt32(pList.get(), 0xb0e066a4, &low);
                Property::GetUInt32(pList.get(), 0xb0e066a5, &high);
                if (low && high) {
                    AddResource(low, 0, 0);
                    AddResource(high, 0, 0);
                }
            }
        }
        PropertyListPtr pProps(GetConfigManager()->FindPropertyList(item.instanceID, item.groupID));
        if (pProps.get()) {
            ResourceKey key;
            if (Property::GetKey(pProps.get(), 0x2424655, &key))
                AddResource(key.instanceID, key.groupID, 4);
            if (Property::GetKey(pProps.get(), 0x2424657, &key))
                AddResource(key.instanceID, key.groupID, 4);
            if (Property::GetKey(pProps.get(), 0x2424656, &key))
                AddResource(key.instanceID, key.groupID, 4);
        }
    }
}

// @ 0x004029F0
void Preloader::Start(const ResourceKey& key, bool flag) {
    Reset();
    GetLoadManager()->OpenHandle(mpHandle.AsPointer());
    intrusive_ptr<LoadHandle>::Validate(mpHandle.get());
    mKey = key;
    mKeys.push_back(key);
    mbActive = true;
    mbFlag = flag;
}

// @ 0x00402A90
LoadHandle* Preloader::GetHandle() {
    return mpHandle.get();
}

// @ 0x00402AB0
Preloader* Preloader::Self() {
    return this;
}

// @ 0x00402AC0
bool Preloader::IsFinished() {
    return !mpHandle.get() || IsLoadFinished(mpHandle.get());
}

// @ 0x00402B30
void Preloader::Reset() {
    if (mpHandle.get()) {
        mpHandle.get()->Cancel(true);
        mpHandle = 0;
    }
    mKey = ResourceKey(false, 0, 0);
    mbActive = false;
    mbFlag = false;
    mKeys.clear();
    mResources.clear();
    mFiles.clear();
    for (int i = 0; i < 6; ++i)
        mpObjects[i] = 0;
}
