// src/game/SPBake/SPEditorBaker.cpp -- migrated from slice(s) s004157d0, s0042f160, s0041bd50, s0041aaa0, s0041a0c0, s00419780, s00417210, s00412900, s004111e0, s00410d70, s0040d2d0, s0040ccb0, s0040aeb0, s004063d0, s00401200, s00411b90, s00407280, s0041c1d0, s005609a0, s0041aa40, s00419000, s004186c0, s00417d60, s00417600, s00416990, s00416180, s00414e30, s004145c0, s00413cc0, s004124b0, s0040eb70, s0040e5b0, s0040a9c0, s0040a170, s004098a0, s00406ac0, s00405000, s00404660, s00404480, s00403af0, s0042f9d0, s004035d0, s00402cc0, s00402470, s00401b80 by tools/migrate/rewrite.py
// Object file: SPBake/SPEditorBaker.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cJob.h"

// unnamed retail callees and globals (address in the comment)
extern "C" long __cdecl _InterlockedExchangeAdd(volatile long*, long);
extern "C" long __cdecl _InterlockedIncrement(volatile long*);
extern "C" long __cdecl _InterlockedDecrement(volatile long*);
extern bool gbLoadExtraResources;  // 0x015D115C
#include <string.h>
#include "SP/cJobManager.h"
#include "EA/ArgScript/cIParser.h"
#include "EA/Audio/ConfigurationAggregate.h"
#include "SP/cCreatureAbility.h"
#include "SP/cEditorResource.h"
#include "SP/cEditorBaker.h"
#include "EA/ArgScript/cArgumentSpec.h"
#include "EA/ArgScript/cArguments.h"
#include "EA/Audio/FactoryBinarySampleData.h"
#include <intrin.h>
#include "EA/ArgScript/cCommandBase.h"
#include "EA/Variant.h"
#include "SP/cDirectPropertyList.h"
#include "cSPBoundingBox.h"
#include "cSPVector3.h"
#include <math.h>
#include "SP/cSPEditorBlock.h"
#include "SP/cPropertyList.h"
#include <new>
#include "cSPMatrix3.h"
#include "cSPTransform.h"
#include "SP/cIModelWorld.h"
#include "EA/LimitStopwatch.h"
#include "EA/ResourceMan/DatabasePackedFile.h"
#include "EA/IO/FileStream.h"
#include "EA/IO/MemoryStream.h"
#include "rw/graphics/EmbeddedState.h"
#include "EA/Stopwatch.h"
#pragma intrinsic(memcmp)
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedIncrement, _InterlockedDecrement)

// ---- items of slice s00401b80 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct IRefCounted {
    virtual int AddRef();
    virtual int Release();
};
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
template <class T> struct SimplePtr {
    T* mpObject;

    SimplePtr() : mpObject(0) {}
    ~SimplePtr() {
        if (mpObject)
            mpObject->Release();
    }
};
struct DefaultRefCounted_s0040_1b80 {
    int Release();  // 0x00453540
};
struct Object690120 {
    int Release();  // 0x00690120
};
struct AtomicRefCounted {
    void* vftable;
    uint32_t mField4;
    volatile long mnRefCount;

    void AddRef() { _InterlockedIncrement(&mnRefCount); }
    int Release();
};
struct PackedIdHolder {
    uint32_t mField0;
    uint32_t mField4;
    uint32_t mPackedId;
};
struct ResourceKey {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
};
struct ReferenceHolder {
    uint32_t mField0;
    uint32_t mField4;
    uint32_t mField8;
    uint32_t mFieldC;
    uint32_t mField10;
    RefPtr<DefaultRefCounted_s0040_1b80> mpRef14;
    RefPtr<DefaultRefCounted_s0040_1b80> mpRef18;
    SimplePtr<Object690120> mpRef1C;
    intrusive_ptr<IRefCounted> mpRef20;
    intrusive_ptr<IRefCounted> mpRefs[3];

    ~ReferenceHolder();
};
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
// ---- items of slice s00401b80 end

// ---- items of slice s00402470 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t g_PreloadPropertyGroup;  // 0x015D12B8
struct ResourceKey_s0040_2470 {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;

    ResourceKey_s0040_2470() : instanceID(0), typeID(0), groupID(0) {}
    // The first parameter is bool-typed in the original (its zero is stored as `xor ecx,ecx`).
    ResourceKey_s0040_2470(bool instance, uint32_t type, uint32_t group)
        : instanceID(instance), typeID(type), groupID(group) {}
};
struct Object {
    virtual int AddRef();
    virtual int Release();
};
template <class T>
struct intrusive_ptr_s0040_2470 {
    T* mpObject;

    intrusive_ptr_s0040_2470() : mpObject(0) {}
    intrusive_ptr_s0040_2470(T* p) : mpObject(p) {
        if (mpObject)
            mpObject->AddRef();
    }
    ~intrusive_ptr_s0040_2470() {
        if (mpObject)
            mpObject->Release();
    }
    T* get() const { return mpObject; }
    intrusive_ptr_s0040_2470& operator=(T* pObject) {
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
    intrusive_ptr_s0040_2470* GetOutRef();  // out-of-line (0x0041D870)
    intrusive_ptr_s0040_2470& Out() { return *GetOutRef(); }
};
struct PropertyList : Object {};
typedef intrusive_ptr_s0040_2470<PropertyList> PropertyListPtr;
namespace Property {
bool GetKeyValue(PropertyList* pList, uint32_t propertyID, ResourceKey_s0040_2470* dst);  // 0x006A1250
}
namespace Property {
bool GetUInt32(PropertyList* pList, uint32_t propertyID, uint32_t* dst);  // 0x006A12A0
}
namespace Property {
inline bool GetKey(PropertyList* pList, uint32_t propertyID, ResourceKey_s0040_2470* dst) {
    return GetKeyValue(pList, propertyID, dst);
}
}
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
void ConvertKeyType(ResourceKey_s0040_2470* key, uint32_t typeID, int flags);  // 0x0068C6D0
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
template <>
struct intrusive_ptr_s0040_2470<LoadHandle> {
    LoadHandle* mpObject;

    LoadHandle* get() const { return mpObject; }
    intrusive_ptr_s0040_2470& operator=(LoadHandle* pObject) {
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
    ResourceKey_s0040_2470 mKey;                       // +0x00
    intrusive_ptr_s0040_2470<LoadHandle> mpHandle;     // +0x0C
    vector<ResourceKey_s0040_2470, 6> mKeys;           // +0x10
    vector<uint32_t, 7> mResources;         // +0x24
    vector<uint32_t, 7> mFiles;             // +0x38
    intrusive_ptr_s0040_2470<Object> mpObjects[6];     // +0x4C
    bool mbActive;                          // +0x64
    bool mbFlag;                            // +0x65

    void AddKey(ResourceKey_s0040_2470 key);  // 0x004021A0
    void AddResource(uint32_t instanceID, uint32_t groupID, int flags);  // 0x00402390
    void Gather(PreloadSource* pSource, bool bSkipKeys);
    void Start(const ResourceKey_s0040_2470& key, bool flag);
    LoadHandle* GetHandle();
    Preloader* Self();
    bool IsFinished();
    void Reset();
};
// ---- items of slice s00402470 end

// ---- items of slice s00402cc0 begin (TODO(rewrite): local stubs, replace by canonical classes)
template <class T> class intrusive_ptr_s0040_2cc0 {
public:
    intrusive_ptr_s0040_2cc0() : mpObject(0) {}
    ~intrusive_ptr_s0040_2cc0() { if (mpObject) mpObject->Release(); }
    intrusive_ptr_s0040_2cc0& operator=(T* pObject) {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject) pObject->AddRef();
            mpObject = pObject;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
    T* get() const { return mpObject; }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
    T** GetAddress();       // 0x0041d870
    T** AsOutParam() { return GetAddress(); }
    T* mpObject;
};
template <class T> class vector_s0040_2cc0 {
public:
    bool empty() const;     // 0x00526430
    void push_back(const T& v); // 0x004b54b0
    T& back() { return *(mpEnd - 1); }
    void pop_back() { --mpEnd; }
    int size() const { return (int)(mpEnd - mpBegin); }
    T& operator[](int i) { return mpBegin[i]; }
    T* begin() { return mpBegin; }
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    unsigned int mAllocator[2];
};
class Object_s0040_2cc0 {
public:
    virtual int AddRef();
    virtual int Release();
};
class Result : public Object_s0040_2cc0 {};
class Slot : public Object_s0040_2cc0 {
public:
    virtual void v2(); virtual void v3();
    virtual bool IsFinished();                      // +0x10
    virtual bool GetResult(Result** ppResult);      // +0x14
};
class Editor : public Object_s0040_2cc0 {
public:
    int GetMode();          // 0x0068f970
    bool IsPlayMode() {
        switch (GetMode()) {
        case 7:
        case 8:
            return true;
        default:
            return false;
        }
    }
    bool IsEditing() { return ((1 << GetMode()) & 0x3c) != 0; }
    void Refresh();         // 0x006909b0
};
struct BlockRequest { unsigned int a, b, c; };
class Item : public Object_s0040_2cc0 {
public:
    unsigned char mFlags;
    bool IsHidden() const { return (mFlags & 1) != 0; }
};
class IFactory {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void Create(BlockRequest* req, Slot** ppSlot, Result** ppResult,
                        int a, int b, int c, int d, int e);       // +0x10
};
IFactory* GetFactory();     // 0x0067dcd0
class IItemManager {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13();
    virtual void Process(Item* item, Editor* editor);               // +0x38
};
IItemManager* GetItemManager();  // 0x0067dd60
class IUndoManager {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void BeginBatch();   // +0x20
    virtual void EndBatch();     // +0x24
};
IUndoManager* GetUndoManager();  // 0x0068f4d0
void PostMessage(int id, Result* result);     // 0x006ac0a0
Result* CombineResults(intrusive_ptr_s0040_2cc0<Result>* results);   // 0x00421eb0
inline bool IsPlayMode(int mode) { return mode >= 7 && mode <= 8; }
class BlockLoader {
public:
    void Update();
    void ApplyResult(Result* result, bool flag);    // 0x00402470
    void Finish();                                  // 0x00402b30

    unsigned int mVTable;
    unsigned int mField4;
    unsigned int mField8;
    intrusive_ptr_s0040_2cc0<Editor> mpEditor;                 // +0x0c
    vector_s0040_2cc0<BlockRequest> mRequests;                 // +0x10
    vector_s0040_2cc0<intrusive_ptr_s0040_2cc0<Result> > mResults;        // +0x24
    vector_s0040_2cc0<intrusive_ptr_s0040_2cc0<Item> > mItems;                           // +0x38
    intrusive_ptr_s0040_2cc0<Slot> mSlots[6];                  // +0x4c
    bool mbApplyResults;                            // +0x64
    bool mbApplyFlag;                               // +0x65
};
struct DefaultAlloc { DefaultAlloc() {} };
struct Container20 {                      // 0x20 bytes, ctor 0x005640f0
    Container20(const DefaultAlloc& a = DefaultAlloc());
    unsigned int mData[8];
};
struct BlockDataCache {                   // 0x24 bytes, ctor 0x00928cd0
    BlockDataCache(int a, int b, void* (*f1)(), void* (*f2)(), const char* name);
    unsigned int mData[9];
};
void* BlockAlloc();
void* BlockFree();
template <class T> struct RefPtr_s0040_2cc0 {
    RefPtr_s0040_2cc0() : mpObject(0) {}
    T* mpObject;
};
struct PtrVector {
    PtrVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    void** mpBegin;
    void** mpEnd;
    void** mpCapacity;
    unsigned int mAllocator[2];
};
struct PtrVector2 {
    PtrVector2() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    void** mpBegin;
    void** mpEnd;
    void** mpCapacity;
    unsigned int mAllocator[3];
};
struct Slot2C {
    Slot2C(const DefaultAlloc& a = DefaultAlloc());
    unsigned int mData[11];
};
struct SlotArray {
    SlotArray() {}
    Slot2C mSlots[8];
};
struct Obj30 { Obj30(); unsigned int d[12]; };
struct Obj68 { Obj68(); unsigned int d[26]; };
struct ObjBig { ObjBig(); unsigned int d[(0x1100 - 0x330) / 4]; };
struct Obj38 { Obj38(); unsigned int d[14]; };
struct Obj18 { Obj18(int n, int flags); unsigned int d[6]; };
struct Range5 {
    Range5() : a(0), b(0), c(0), d(0), e(0) {}
    unsigned int a, b, c, d, e;
};
class IRefCounted_s0040_2cc0 { public: virtual int AddRef(); };
class IBaseB0 { public: virtual void f0(); };
class IBaseB : public IBaseB0 { public: virtual void f0(); };
class IBaseC { public: IBaseC() : mField(0) {} virtual void g0(); unsigned int mField; };
class EditorBlockData : public IRefCounted_s0040_2cc0, public IBaseB, public IBaseC {
public:
    EditorBlockData();
    virtual int AddRef();
    virtual void f0();
    virtual void g0();

    Container20 mContainer10;      // +0x10
    Container20 mContainer30;      // +0x30
    BlockDataCache mCache;         // +0x50
    RefPtr_s0040_2cc0<void> mRef74;
    RefPtr_s0040_2cc0<void> mRef78;
    RefPtr_s0040_2cc0<void> mRef7C;
    RefPtr_s0040_2cc0<void> mRef80;
    RefPtr_s0040_2cc0<void> mRef84;
    RefPtr_s0040_2cc0<void> mRef88;
    RefPtr_s0040_2cc0<void> mRef8C;
    PtrVector mVector90;           // +0x90
    PtrVector2 mVectorA4;          // +0xa4
    RefPtr_s0040_2cc0<void> mRefBC;
    bool mFlagC0;
    int mFieldC4;
    SlotArray mSlots;              // +0xc8
    Obj30 mObj228;
    bool mFlag258;
    bool mFlag259;
    Obj68 mObj25C;
    bool mFlag2C4;
    Obj68 mObj2C8;
    ObjBig mObj330;
    Obj38 mObj1100;
    Obj18 mObj1138;
    Obj18 mObj1150;
    Range5 mRange1168;
    RefPtr_s0040_2cc0<void> mRef117C;
    bool mFlag1180;
    Container20 mContainers[6];    // +0x1184
};
// ---- items of slice s00402cc0 end

// ---- items of slice s004035d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct PtrVector_s0040_35d0 {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    PtrVector_s0040_35d0() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
};
struct RangeSettings {
    int mID;
    bool mbEnabled;
    PtrVector_s0040_35d0 mItems;
    int mIndex0; float mMin0; float mMax0;
    int mIndex1; float mMin1; float mMax1;
    int mIndex2; float mMin2; float mMax2;
    RangeSettings();
};
struct ResourceKey_s0040_35d0 {
    uint32_t mInstanceID;
    uint16_t mTypeLo;
    uint16_t mTypeHi;
    ResourceKey_s0040_35d0(uint32_t instanceID = 0x2ea8fb98, uint16_t typeLo = 0, uint16_t typeHi = 4)
        : mInstanceID(instanceID), mTypeLo(typeLo), mTypeHi(typeHi) {}
};
struct RawPtr {
    void* mpObject;
    RawPtr() : mpObject(0) {}
};
struct KeyedRecord {
    void* mpOwner;
    void* mpData;
    void* mpExtra;
    ResourceKey_s0040_35d0 mKey;
    RawPtr mRef14, mRef18, mRef1C, mRef20;
    RawPtr mSlots[3];
    KeyedRecord();
};
struct BatchTarget {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool Apply(uint32_t context, uint32_t item, uint32_t userData);  // slot 0x2C
};
inline bool ApplyAll(BatchTarget* target, uint32_t context, uint32_t* items, uint32_t count,
                     uint32_t userData) {
    bool ok = true;
    for (uint32_t i = 0; i < count; i++)
        if (!target->Apply(context, items[i], userData))
            ok = false;
    return ok;
}
struct PendingBatch {
    BatchTarget* mpTarget;
    uint32_t mContext;
    uint32_t* mpItems;
    uint32_t mnCount;
    uint32_t mUserData;

    bool Flush();
    ~PendingBatch() { if (mpTarget) Flush(); }
};
struct IVirtualRefCounted { virtual int AddRef(); virtual int Release(); };
template <class T> struct intrusive_ptr_s0040_35d0 {
    T* mpObject;
    ~intrusive_ptr_s0040_35d0() { if (mpObject) mpObject->Release(); }
};
namespace Resource_s0040_35d0 {
 struct ThreadedObject { int Release(); }; 
}
struct RefObject690 { int Release(); };   // released via 0x00690120
struct DefaultRefCounted {
    virtual ~DefaultRefCounted() {}
    int mnRefCount;
    int AddRef() { return mnRefCount++ + 1; }
    int Release();
};
struct Member10Base { uint32_t d[8]; ~Member10Base(); };                        // 0x0041fac0
struct Member10 : Member10Base { ~Member10() { uint32_t unused0, unused1; } };
struct Member30Base { uint32_t d[8]; ~Member30Base(); };                        // 0x004e0f20
struct Member30 : Member30Base { ~Member30() { uint32_t unused0, unused1; } };
struct Member50Base { uint32_t d[9]; ~Member50Base(); };                        // 0x00928dc0
struct Member50 : Member50Base { ~Member50() { uint32_t unused0, unused1; } };
struct Member90Base { uint32_t d[5]; ~Member90Base(); };                        // 0x00540520
struct Member90 : Member90Base { ~Member90() { uint32_t unused; } };
struct MemberA4Base { uint32_t d[6]; ~MemberA4Base(); };                        // 0x004e1bf0
struct MemberA4 : MemberA4Base { ~MemberA4() { uint32_t unused; } };
struct Slot2C_s0040_35d0 {  // 0x004200b0
    uint32_t d[11];
    ~Slot2C_s0040_35d0();
};
struct SlotArray8 {
    Slot2C_s0040_35d0 mSlots[8];
    ~SlotArray8();
};
struct Member228Base { uint32_t d[13]; ~Member228Base(); };                     // 0x00401f20
struct Member228 : Member228Base { ~Member228() { uint32_t unused0, unused1; } };
struct Member68 { uint32_t d[26]; ~Member68(); };                               // 0x004020e0
struct Member330 { uint32_t d[(0x1168 - 0x330) / 4]; ~Member330(); };          // 0x00417fe0
struct Entry20 { uint32_t d[8]; ~Entry20(); };                                  // 0x005534b0
struct SystemInterface : IVirtualRefCounted {};
struct SystemListener { virtual ~SystemListener() {} };
struct GameSystem : SystemInterface, SystemListener, DefaultRefCounted {
    Member10 m10;
    Member30 m30;
    Member50 m50;
    intrusive_ptr_s0040_35d0<IVirtualRefCounted> m74, m78, m7C;
    intrusive_ptr_s0040_35d0<RefObject690> m80;
    intrusive_ptr_s0040_35d0<Resource_s0040_35d0::ThreadedObject> m84;
    intrusive_ptr_s0040_35d0<DefaultRefCounted> m88, m8C;
    Member90 m90;
    MemberA4 mA4;
    intrusive_ptr_s0040_35d0<DefaultRefCounted> mBC;
    uint32_t mC0, mC4;
    SlotArray8 mC8;
    Member228 m228;
    Member68 m25C;
    uint32_t m2C4;
    Member68 m2C8;
    Member330 m330;
    PendingBatch mPending;
    intrusive_ptr_s0040_35d0<IVirtualRefCounted> m117C;
    uint32_t m1180;
    Entry20 mEntries[6];

    virtual int AddRef();
    ~GameSystem();
};
// ---- items of slice s004035d0 end

// ---- items of slice s0042f9d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" long __cdecl _InterlockedExchange(long volatile* target, long value);
#pragma intrinsic(_InterlockedExchange)
void* __cdecl EASTL_allocator_allocate(uint32_t size, const char* name, int flags, int align,
                                       const char* file, int line);
void  __cdecl EASTL_allocator_deallocate(void* p); // 0x00f47380
void* __cdecl memcpy(void* dst, const void* src, unsigned int n);
struct WideFixedBuf {
    wchar_t* mBegin;
    wchar_t* mEnd;
    wchar_t* mCapacity;
    void ReleaseHeap();                                   // @ 0x004292A0
    WideFixedBuf& append(const wchar_t* pBegin, const wchar_t* pEnd);
};
template <int N> inline void ScratchSlots() { uint32_t slots[N]; }
inline const uint32_t& MaxRef(const uint32_t& a, const uint32_t& b) { return (a < b) ? b : a; }
inline wchar_t* CopyWide(const wchar_t* first, const wchar_t* last, wchar_t* dest)
{
    memcpy(dest, first, (last - first) * 2);
    return dest + (last - first);
}
inline wchar_t* DoAllocate(uint32_t n)
{
    void* p = EASTL_allocator_allocate(
        n * 2, "Editor", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
    return (wchar_t*)p;
}
struct ThunkB0_4036a0 { virtual void f(); };
struct ThunkB1_4036a0 { virtual void f(); };
struct ThunkD_4036a0 : ThunkB0_4036a0, ThunkB1_4036a0 { void f(); ThunkD_4036a0(); };
struct ThunkB0_410d40 { virtual void f(); };
struct ThunkB1_410d40 { virtual void f(); };
struct ThunkD_410d40 : ThunkB0_410d40, ThunkB1_410d40 { void f(); ThunkD_410d40(); };
struct ThunkB0_41a9f0 { virtual void f(); };
struct ThunkB1_41a9f0 { virtual void f(); };
struct ThunkD_41a9f0 : ThunkB0_41a9f0, ThunkB1_41a9f0 { void f(); ThunkD_41a9f0(); };
struct DelB0 { virtual ~DelB0(); };
struct DelB1 { virtual ~DelB1(); };
struct DelB2 { virtual ~DelB2(); };
struct DelObj : DelB0, DelB1, DelB2 {
    virtual ~DelObj();                                    // @ 0x004037B0
    void operator delete(void* p) { EASTL_allocator_deallocate(p); }
    DelObj();
};
struct EdB0 { virtual ~EdB0(); };
struct EdB1 { virtual ~EdB1(); };
struct EditorResourceD : EdB0, EdB1 { virtual ~EditorResourceD(); EditorResourceD(); };
struct Property_s0042_f9d0 {
    char pad[0x12];
    uint16_t type;                                        // +0x12, 9 = int, 0xd = float
    int*   GetInt();                                      // @ 0x0041E990
    float* GetFloat();                                    // @ 0x0041EA70
};
struct IPropHost {
    virtual void _v0();
    virtual void Release();                               // +0x04
virtual void _v2();
virtual void _v3();
virtual void _v4();
virtual void _v5();
virtual void _v6();
virtual void _v7();
virtual void _v8();
    virtual bool GetProp(uint32_t key, Property_s0042_f9d0** out);   // +0x24
};
struct IResourceMgr {
virtual void _v0();
virtual void _v1();
virtual void _v2();
virtual void _v3();
virtual void _v4();
virtual void _v5();
virtual void _v6();
virtual void _v7();
virtual void _v8();
virtual void _v9();
virtual void _v10();
    virtual bool Find(uint32_t a, uint32_t b, IPropHost** out);   // +0x2c
};
struct ISettings {
virtual void _v0();
virtual void _v1();
virtual void _v2();
virtual void _v3();
virtual void _v4();
virtual void _v5();
virtual void _v6();
virtual void _v7();
virtual void _v8();
virtual void _v9();
virtual void _v10();
virtual void _v11();
virtual void _v12();
virtual void _v13();
virtual void _v14();
virtual void _v15();
virtual void _v16();
virtual void _v17();
virtual void _v18();
virtual void _v19();
virtual void _v20();
virtual void _v21();
virtual void _v22();
virtual void _v23();
virtual void _v24();
virtual void _v25();
virtual void _v26();
virtual void _v27();
virtual void _v28();
virtual void _v29();
virtual void _v30();
virtual void _v31();
virtual void _v32();
virtual void _v33();
virtual void _v34();
virtual void _v35();
virtual void _v36();
virtual void _v37();
virtual void _v38();
virtual void _v39();
virtual void _v40();
virtual void _v41();
virtual void _v42();
    virtual void Get_ac(void* out);                       // +0xac
    virtual void _v44();
    virtual void Get_b4(void* out);                       // +0xb4
    virtual void Get_b8(void* out);                       // +0xb8
virtual void _v47();
virtual void _v48();
virtual void _v49();
virtual void _v50();
virtual void _v51();
virtual void _v52();
virtual void _v53();
virtual void _v54();
virtual void _v55();
virtual void _v56();
virtual void _v57();
virtual void _v58();
virtual void _v59();
    virtual void Set_f0(uint16_t v);                      // +0xf0
};
struct IBuilder {
virtual void _v0();
virtual void _v1();
virtual void _v2();
virtual void _v3();
virtual void _v4();
virtual void _v5();
virtual void _v6();
virtual void _v7();
virtual void _v8();
virtual void _v9();
virtual void _v10();
virtual void _v11();
virtual void _v12();
virtual void _v13();
    virtual void Build(uint32_t flags, void* a, void* b, void* c, void* d, void* e, void* tbl,
                       uint32_t f, int mode, void* g, void* h, void* i);   // +0x38
};
extern IPropHost* g_pApp;                                 // 0x015FD918
void  __cdecl Unk777ae0(int a, int b, int c);             // @ 0x00777AE0
void* __cdecl GetUnk67dd60();                             // @ 0x0067DD60
ISettings*    __cdecl GetSettings();                      // @ 0x0067DD40
IBuilder*     __cdecl GetBuilder();                       // @ 0x0067DDB0
IResourceMgr* __cdecl GetResourceMgr();                   // @ 0x0067DE30
struct PropHostRef {
    IPropHost* p;
    PropHostRef() { p = 0; }
    ~PropHostRef() { if (p) p->Release(); }
    operator IPropHost*() { return p; }
    IPropHost** operator&()
    {
        if (p) {
            IPropHost* old = p;
            p = 0;
            old->Release();
        }
        return &p;
    }
};
inline bool TryGetInt(IPropHost* h, uint32_t key, int& out)
{
    Property_s0042_f9d0* pEntry;
    int temp;
    if (h && h->GetProp(key, &pEntry) && pEntry->type == 9) {
        out = *pEntry->GetInt();
        return true;
    }
    return false;
}
inline bool TryGetUInt(IPropHost* propHost, uint32_t key, uint32_t& outValue)
{
    Property_s0042_f9d0* pValue;
    int typeId;
    if (propHost && propHost->GetProp(key, &pValue) && pValue->type == 9) {
        outValue = *(uint32_t*)pValue->GetInt();
        return true;
    }
    return false;
}
struct cEditorResource { cEditorResource() {} virtual void _e0(); };
struct BakeSprites : cEditorResource { BakeSprites() {} virtual void _b0(); };
struct AtomicInt_s0042_f9d0 {
    long mValue;
    AtomicInt_s0042_f9d0() { Set(0); }
    void Set(long x) { _InterlockedExchange(&mValue, x); }
};
struct cCreatureAbility {
    AtomicInt_s0042_f9d0 mRefCount;
    cCreatureAbility() {}
    virtual void _c0();
};
struct RefVector {
    void* mBegin; void* mEnd; void* mCap;
    RefVector() { mBegin = 0; mEnd = 0; mCap = 0; }
    ~RefVector();                                         // @ 0x0041EB80
    RefVector& operator=(const RefVector& o);             // @ 0x0041EBE0
};
struct AllocTag { AllocTag() {} };
struct Vector8Base {
    uint32_t mData[5];
    Vector8Base(const AllocTag&);                         // @ 0x00540470
    ~Vector8Base();                                       // @ 0x00564580
    Vector8Base& operator=(const Vector8Base& o);         // @ 0x004269B0
};
struct Vector8 : Vector8Base {
    bool mFlag;                                           // +0x14
    Vector8() : Vector8Base(AllocTag()) {}
    Vector8& operator=(const Vector8& o)
    {
        Vector8Base::operator=(o);
        bool f = o.mFlag;
        mFlag = f;
        return *this;
    }
};
struct Elem24Vec {
    void* mBegin; void* mEnd; void* mCap;
    Elem24Vec() { mBegin = 0; mEnd = 0; mCap = 0; }
    ~Elem24Vec();                                         // @ 0x00421230
    Elem24Vec& operator=(const Elem24Vec& o);             // @ 0x00421290
};
struct Transform56 { uint32_t data[14]; };
struct TransformVec {
    Transform56* mBegin; Transform56* mEnd; Transform56* mCap;
    TransformVec() { mBegin = 0; mEnd = 0; mCap = 0; }
    Transform56* begin() { return mBegin; }
    ~TransformVec() { for (Transform56* p = mBegin; p < mEnd; ++p) {} FreeStorage(); }
    void FreeStorage();                                   // @ 0x00427440
    TransformVec& operator=(const TransformVec& o);       // @ 0x0041E0D0
};
struct IMgr {
virtual void _v0();
virtual void _v1();
virtual void _v2();
virtual void _v3();
virtual void _v4();
    virtual void Notify(uint32_t id, int a, int b);       // +0x14
    virtual void Notify4(uint32_t id, int a, int b, int c);   // +0x18
};
IMgr* __cdecl GetMgr();                                   // @ 0x0067DCC0
struct BakeSpritesResource : BakeSprites, cCreatureAbility {
    RefVector    mVecA;       // +0x0c
    uint32_t     mField18;    // +0x18
    uint32_t     mField1c;    // +0x1c
    uint32_t     mField20;    // +0x20
    uint32_t     mField24;    // +0x24
    uint32_t     mField28;    // +0x28
    RefVector    mVecB;       // +0x2c
    uint32_t     mField38;    // +0x38
    uint32_t     mField3c;    // +0x3c
    Vector8      mVec8;       // +0x40
    Elem24Vec    mElems;      // +0x58
    uint32_t     mField64;    // +0x64
    uint32_t     mField68;    // +0x68
    TransformVec mTransforms; // +0x6c
    uint32_t     mField78;    // +0x78
    uint32_t     mField7c;    // +0x7c
    bool         mFlag80;     // +0x80

    BakeSpritesResource();                                // @ 0x004301E0
    void Run(int unused);                                 // @ 0x0042FF30
    void* operator new(unsigned size)
    {
        ScratchSlots<3>();
        return EASTL_allocator_allocate(size, "Graphics", 0, 0, 0, 0);
    }
    virtual ~BakeSpritesResource()                        // @ 0x00430320
    {
        if (!mFlag80) {
            GetMgr()->Notify4(0x355dad8, 0, 0, 0);
        }
        // Frame filler: the original reserves unused slots here (they also size the
        // compiler-generated scalar deleting destructor at 0x004302F0).
        ScratchSlots<13>();
    }
    void operator delete(void* p) { EASTL_allocator_deallocate(p); }
};
// ---- items of slice s0042f9d0 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
bool __cdecl BakeSpritesCreate(RefVector* vecA, uint32_t f24, uint32_t f28, uint32_t f20, RefVector* vecB, Vector8* v8, Elem24Vec* elems, TransformVec* xf);  // 0x0042ffb0 (stays in the slice: not this object's)

// ---- items of slice s00403af0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const unsigned int kMessageIDs[13];  // 0x0150C008
extern int kSortTableCount;      // 0x013EC430
void* operator new[](unsigned int size, const char* pName, int flags, unsigned int debugFlags,
                     const char* pFile, int line);
void* operator new(unsigned int size, const char* pName, int flags, unsigned int debugFlags,
                   const char* pFile, int line);
unsigned int FNVHash(const char* s, unsigned int seed, int lowercase);
inline unsigned int HashString(const char* s) { return FNVHash(s, 0x811c9dc5, 1); }
template <class T> struct intrusive_ptr_s0040_3af0 {
    T* mpObject;
    intrusive_ptr_s0040_3af0() : mpObject(0) {}
    ~intrusive_ptr_s0040_3af0() { if (mpObject) mpObject->Release(); }
    intrusive_ptr_s0040_3af0& operator=(T* pObject) {
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
    T* operator->() const { return mpObject; }
    T* get() const { return mpObject; }
    intrusive_ptr_s0040_3af0& ReleaseRef();   // out of line: releases and nulls, returns *this
    T** AsOutParam() { return &ReleaseRef().mpObject; }
};
void AddListeners(struct IMessageManager* pManager, struct IMessageListener* pListener,
                  const unsigned int* pIDs, unsigned int count);
struct ResourceKey_s0040_3af0 {
    unsigned int instanceID;
    unsigned int typeID;
    unsigned int groupID;
};
struct IObject {
    virtual int AddRef() = 0;
    virtual int Release() = 0;
};
struct IWindowGroup : IObject {
    virtual void v08(); virtual void v0c(); virtual void v10();
    virtual IWindowGroup* FindWindowByID(unsigned int id, int a, int b);
    virtual void v018(); virtual void v01c(); virtual void v020(); virtual void v024(); virtual void v028(); virtual void v02c(); virtual void v030(); virtual void v034(); virtual void v038(); virtual void v03c(); virtual void v040(); virtual void v044(); virtual void v048(); virtual void v04c(); virtual void v050(); virtual void v054(); virtual void v058(); virtual void v05c(); virtual void v060(); virtual void v064(); virtual void v068(); virtual void v06c(); virtual void v070(); virtual void v074(); virtual void v078(); virtual void v07c(); virtual void v080(); virtual void v084(); virtual void v088(); virtual void v08c(); virtual void v090(); virtual void v094(); virtual void v098(); virtual void v09c(); virtual void v0a0(); virtual void v0a4(); virtual void v0a8(); virtual void v0ac(); virtual void v0b0(); virtual void v0b4(); virtual void v0b8(); virtual void v0bc(); virtual void v0c0(); virtual void v0c4(); virtual void v0c8(); virtual void v0cc(); virtual void v0d0(); virtual void v0d4(); virtual void v0d8(); virtual void v0dc(); virtual void v0e0(); virtual void v0e4(); virtual void v0e8(); virtual void v0ec(); virtual void v0f0(); virtual void v0f4(); virtual void v0f8(); virtual void v0fc(); virtual void v100(); virtual void v104(); virtual void v108(); virtual void v10c(); virtual void v110(); virtual void v114(); virtual void v118(); virtual void v11c(); virtual void v120();
    // 0x124
    virtual void SetFlag(int flag, int a, int b);
    virtual void v128(); virtual void v12c(); virtual void v130();
    virtual void SetVisible(bool visible);
};
struct IWindowManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual IWindowGroup* FindWindowByID(unsigned int id, int a, int b);
};
IWindowManager* WindowManager();  // 0x0067DD80
struct DefaultRefCounted_s0040_3af0 {
    void* vtable;
    int mnRefCount;
    int AddRef() { return mnRefCount++ + 1; }
    int Release();
};
struct cBlockData : DefaultRefCounted_s0040_3af0 {
    unsigned int pad[10];
    cBlockData();
};
struct cBakeQueue : DefaultRefCounted_s0040_3af0 {
    unsigned int pad[36];
    cBakeQueue(float scale);
};
struct IMessageListener { virtual void v00(); };
struct IMessageManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20();
    virtual void AddListener(IMessageListener* listener, unsigned int messageID);
};
IMessageManager* MessageManager();  // 0x0067DCC0
void AddListeners(IMessageManager* pManager, IMessageListener* pListener, const unsigned int* pIDs, unsigned int count);  // 0x004043f0 (defined below; used by a stub's inline body)
struct MessageRegistration {
    IMessageManager* mpManager;
    IMessageListener* mpListener;
    const unsigned int* mpIDs;
    unsigned int mnCount;
    int mbRegistered;
    void Init(IMessageManager* pManager, IMessageListener* pListener, const unsigned int* pIDs, unsigned int count) {
        mpManager = pManager;
        mpListener = pListener;
        mpIDs = pIDs;
        mnCount = count;
        mbRegistered = 0;
        if (pManager && pListener && mpIDs)
            AddListeners(pManager, pListener, pIDs, count);
    }
};
struct BakerCommand { BakerCommand(void* owner); unsigned int pad[60]; };
void Function_0067de20();
struct KeyAllocator { KeyAllocator() {} };
template <class T> inline void destruct(T* first, T* last) { for (; first < last; ++first) first->~T(); }
template <class T> inline void destruct(T** first, T** last) {}
template <class T> struct VectorBase {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    KeyAllocator mAllocator;
    unsigned int mPad;
    VectorBase(const KeyAllocator& a);
    ~VectorBase();
};
template <class T> struct vector_s0040_3af0 : VectorBase<T> {
    vector_s0040_3af0(const KeyAllocator& a) : VectorBase<T>(a) {}
    ~vector_s0040_3af0() { destruct(mpBegin, mpEnd); }
    void reserve(unsigned int n);
    unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
    T& operator[](unsigned int n) { return mpBegin[n]; }
};
struct IStream {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28();
    virtual int GetSize();
    virtual void Read(void* buf, int n);
};
struct IResourceRecord {
    virtual void v00(); virtual int AddRef(); virtual int Release(); virtual void v0c(); virtual void v10();
    virtual void v14();
    virtual IStream* GetStream();
};
struct IDatabase {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2c(); virtual void v30();
    virtual bool OpenRecord(const ResourceKey_s0040_3af0& key, IResourceRecord** ppRecord, int a, int b, int c, int d);
    virtual void v38();
    virtual void CloseRecord(IResourceRecord* pRecord);
};
namespace Skinner {
class PaintSystem {
public:
    virtual ~PaintSystem() {}
    virtual bool IsEqual(const PaintSystem& other) const = 0;
    static void operator delete(void* p) { EASTL_allocator_deallocate(p); }
};
}
namespace Skinner {
class IdPaintSystem : public PaintSystem {
public:
    IdPaintSystem(unsigned int id) : mId(id) {}
    virtual bool IsEqual(const PaintSystem& other) const;
    unsigned int mId;
};
}
struct IResourceManager_s0040_3af0 {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34();
    virtual void FindRecords(vector_s0040_3af0<ResourceKey_s0040_3af0>* keys, const Skinner::PaintSystem& filter, vector_s0040_3af0<IDatabase*>* dbs);
};
IResourceManager_s0040_3af0* ResourceManager_s0040_3af0();  // 0x0067DCD0
struct BufferPool { void* Alloc(int size, int flags); };
struct BufferMap { void*& operator[](const unsigned __int64& key); };
struct PropertyID {
    unsigned int mIndex : 8;
    unsigned int mGroup : 8;
    unsigned int mType : 8;
    unsigned int mUnused : 6;
    unsigned int mKind : 2;
    PropertyID(int type, int group) {
        *(unsigned int*)this = 0;
        mKind = 1;
        mType = type;
        mGroup = group;
    }
};
struct IPropList : IObject {};
struct IPropManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28();
    virtual bool GetPropertyListImpl(unsigned int name, PropertyID id, IPropList** ppList);

};
IPropManager* PropManager();  // 0x0067DE30
bool GetPropertyKeys(IPropList* list, unsigned int id, int* count, ResourceKey_s0040_3af0** keys);
bool GetPropertyFloats(IPropList* list, unsigned int id, int* count, float** values);
struct FloatMap { float& operator[](const ResourceKey_s0040_3af0& key); unsigned int pad[8]; };
struct Blob56 { unsigned int d[14]; Blob56(); };
struct SortEntry { unsigned int a, b, c; };
struct SortLess {};
void SortEntries(SortEntry* first, SortEntry* last, SortLess compare);
extern SortEntry kSortTable[];  // 0x0150C050
struct Base0 { virtual void v00(); };
class cBaker : public Base0, public IMessageListener {
public:
    virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18(); virtual void v1c();
    virtual bool Initialize();
    void Reset(int);          // 0x00411890
    void LoadSettings();      // 0x004124b0

    unsigned int pad08[(0x30 - 0x08) / 4];
    BufferMap mBuffers;       // 0x30
    unsigned int pad34[(0x50 - 0x34) / 4];
    BufferPool mPool;         // 0x50
    unsigned int pad54[(0x74 - 0x54) / 4];
    intrusive_ptr_s0040_3af0<IWindowGroup> mpWindow;      // 0x74
    intrusive_ptr_s0040_3af0<IWindowGroup> mpProgress;    // 0x78
    unsigned int pad7c[(0x88 - 0x7c) / 4];
    intrusive_ptr_s0040_3af0<cBlockData> mpBlockData;     // 0x88
    intrusive_ptr_s0040_3af0<cBakeQueue> mpQueue;         // 0x8c
    unsigned int pad90[(0xb8 - 0x90) / 4];
    bool mbBaking;                             // 0xb8
    unsigned int padbc[(0x1100 - 0xbc) / 4];
    Blob56 mSettings;                          // 0x1100
    unsigned int pad1138[(0x1168 - 0x1138) / 4];
    MessageRegistration mMessages;             // 0x1168
    unsigned int pad117c[(0x1184 - 0x117c) / 4];
    FloatMap mGeomInfo[6];                     // 0x1184
};
// ---- items of slice s00403af0 end

// forward declarations: helpers defined later in VA order (rewrite.py forward_protos)
inline void sort(SortEntry* first, SortEntry* last, SortLess compare);   // defined at 0x00404430, called earlier in the TU

// ---- items of slice s00404480 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct LinearAllocator {
    void* mpVTable;
    void* mpBegin;
    char* mpEnd;      // +0x08
    char* mpCurrent;  // +0x0c
    char* mpLast;     // +0x10

    bool Grow(unsigned int size);  // 0x00928ba0
    void* Allocate(unsigned int size, bool allowGrow);
};
namespace ArgScript {
    class ICommand {
    public:
        ICommand();
        virtual void ParseLine(void* line);
        unsigned int mField4;
        unsigned int mField8;
        unsigned int mFieldC;
    };
}
namespace ArgScript {
    class CommandBase : public ICommand {
    public:
        virtual void ParseLine(void* line);
    };
}
namespace ArgScript {
    class OptionParser {
    public:
        OptionParser(int mode);                                  // 0x0083a9f0
        void AddOptions(const char* description, ...);           // 0x0083bcd0
        void PrintUsage(const char* name, void* stream);         // 0x0083a2f0
        unsigned int mData[50];
    };
}
class BakerCommand_s0040_4480 : public ArgScript::CommandBase {
public:
    BakerCommand_s0040_4480(void* pBaker);
    virtual void ParseLine(void* line);
    void Description(void* stream);

    void* mpBaker;                      // +0x10
    ArgScript::OptionParser mOptions;   // +0x14
    const char* mKeyFilter;             // +0xdc
    int mLimit;                         // +0xe0
    bool mProcessQueue;                 // +0xe4
    int mFilterGroup;                   // +0xe8
    int mFilterInstance;                // +0xec
};
// ---- items of slice s00404480 end

// ---- items of slice s00404660 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern wchar_t gEmptyString16[];
struct ResourceKey_s0040_4660 {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
    ResourceKey_s0040_4660() : instanceID(0), typeID(0), groupID(0) {}
    // The first parameter is bool-typed in the original (its zero is stored as `xor ecx,ecx`).
    ResourceKey_s0040_4660(bool instance, uint32_t type, uint32_t group)
        : instanceID(instance), typeID(type), groupID(group) {}
    bool operator==(const ResourceKey_s0040_4660& b) const
    {
        return instanceID == b.instanceID && typeID == b.typeID && groupID == b.groupID;
    }
};
union GroupIDBits {
    uint32_t value;
    struct {
        uint32_t low : 16;
        uint32_t category : 8;
        uint32_t high : 8;
    } bits;
    GroupIDBits(uint32_t v) : value(v) {}
};
struct IResourceFilter {
    virtual ~IResourceFilter() {}
    virtual bool IsValid(const ResourceKey_s0040_4660& key) = 0;
};
struct ResourceKeyFilter : IResourceFilter {
    uint32_t mInstanceID;  // +0x04
    uint32_t mGroupID;     // +0x08
    uint32_t mTypeID;      // +0x0c
    uint32_t mGroupMask;   // +0x10
    ResourceKeyFilter() : mInstanceID(0xffffffff), mGroupID(0xffffffff), mTypeID(0xffffffff), mGroupMask(0xffffffff) {}
    virtual bool IsValid(const ResourceKey_s0040_4660& key);
};
struct TypeIDFilter : IResourceFilter {
    uint32_t mTypeID;
    TypeIDFilter(uint32_t typeID) : mTypeID(typeID) {}
    virtual bool IsValid(const ResourceKey_s0040_4660& key);
};
struct array_allocator {
    void deallocate(void* p, unsigned int)
    {
        if (((int*)p)[-1])
            delete[] (char*)p;
    }
    unsigned int mFlags;
    unsigned int mFlags2;
};
struct false_type {};
template <class T> struct has_trivial_destructor : false_type {};
template <class T> inline void destruct_impl(T* first, T* last, false_type)
{
    for (; first < last; ++first)
        first->~T();
}
template <typename T> inline void destruct_s0040_4660(T* first, T* last)
{
    destruct_impl(first, last, has_trivial_destructor<T>());
}
template <typename T> struct VectorBase_s0040_4660 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    array_allocator mAllocator;
    VectorBase_s0040_4660(const KeyAllocator& a);  // 0x00540470
    ~VectorBase_s0040_4660()
    {
        if (mpBegin)
            mAllocator.deallocate(mpBegin, (mpCapacity - mpBegin) * sizeof(T));
    }
};
template <typename T> struct vector_s0040_4660 : VectorBase_s0040_4660<T> {
    vector_s0040_4660(const KeyAllocator& a = KeyAllocator()) : VectorBase_s0040_4660<T>(a) {}
    ~vector_s0040_4660() { destruct_s0040_4660(this->mpBegin, this->mpEnd); }
    bool empty() const;
    void push_back(const T& value);
    T& front() { return *this->mpBegin; }
    int size() const { return (int)(this->mpEnd - this->mpBegin); }
};
typedef vector_s0040_4660<ResourceKey_s0040_4660> KeyVector;
struct StringAllocator { StringAllocator() {} };
struct allocator {
    void deallocate(void* p, unsigned int) { delete[] (char*)p; }
    unsigned int mFlags;
};
struct string16 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    allocator mAllocator;
    string16(const StringAllocator& a = StringAllocator()) : mpBegin(0), mpEnd(0), mpCapacity(0)
    {
        mpBegin = gEmptyString16;
        mpEnd = mpBegin;
        mpCapacity = mpBegin + 1;
    }
    ~string16() { DeallocateSelf(); }
    void DeallocateSelf()
    {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin, (unsigned int)(mpCapacity - mpBegin));
    }
    void DoFree(wchar_t* p, unsigned int n)
    {
        if (p)
            mAllocator.deallocate(p, n * sizeof(wchar_t));
    }
    const wchar_t* c_str() const { return mpBegin; }
};
template <class T> struct intrusive_ptr_s0040_4660 {
    T* mpObject;
    intrusive_ptr_s0040_4660() : mpObject(0) {}
    intrusive_ptr_s0040_4660(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~intrusive_ptr_s0040_4660() { if (mpObject) mpObject->Release(); }
    T* operator->() const { return mpObject; }
    T* get() const { return mpObject; }
};
class IResourceManager_s0040_4660 {
public:
    virtual void f00(); virtual void f04(); virtual void f08(); virtual void f0c();
    virtual void f10(); virtual void f14(); virtual void f18(); virtual void f1c();
    virtual void f20(); virtual void f24(); virtual void f28(); virtual void f2c();
    virtual void f30(); virtual void f34();
    virtual int GetResourceKeyList(KeyVector* pKeys, IResourceFilter* pFilter, int flags); // 0x38
    virtual void f3c(); virtual void f40(); virtual void f44(); virtual void f48(); virtual void f4c();
    virtual void f50(); virtual void f54(); virtual void f58(); virtual void f5c();
    virtual void f60(); virtual void f64(); virtual void f68(); virtual void f6c();
    virtual int ReleaseResources(int flags, IResourceFilter* pFilter);  // 0x70
    virtual void f74(); virtual void f78();
    virtual bool GetFileName(const ResourceKey_s0040_4660& key, string16& name);  // 0x7c
};
class cEditorModel {
public:
    uint32_t pad[3];
    ResourceKey_s0040_4660 mKey;  // +0x0c
};
class cEditor {
public:
    virtual void f00(); virtual void f04(); virtual void f08(); virtual void f0c();
    virtual void f10(); virtual void f14(); virtual void f18(); virtual void f1c();
    virtual void f20(); virtual void f24(); virtual void f28(); virtual void f2c();
    virtual void f30(); virtual void f34(); virtual void f38(); virtual void f3c();
    virtual cEditorModel* GetEditorModel();  // 0x40
};
class IGameModeManager {
public:
    virtual void f00(); virtual void f04(); virtual void f08(); virtual void f0c();
    virtual void f10(); virtual void f14(); virtual void f18(); virtual void f1c();
    virtual void f20(); virtual void f24();
    virtual bool SetActiveMode(uint32_t modeID);  // 0x28
    virtual cEditor* GetActiveMode();             // 0x2c
    virtual void f30(); virtual void f34();
    virtual uint32_t GetActiveModeID();           // 0x38
};
class IMessageManager_s0040_4660 {
public:
    virtual void f00(); virtual void f04(); virtual void f08(); virtual void f0c();
    virtual void f10(); virtual void f14();
    virtual void PostMSG(uint32_t messageID, void* pMessage, void* p2, void* p3);  // 0x18
};
class IRenderManager {
public:
    virtual void f00(); virtual void f04(); virtual void f08(); virtual void f0c();
    virtual void f10(); virtual void f14(); virtual void f18(); virtual void f1c();
    virtual void f20(); virtual void f24(); virtual void f28(); virtual void f2c();
    virtual void f30(); virtual void f34(); virtual void f38(); virtual void f3c();
    virtual void f40();
    virtual void DumpRTTs();  // 0x44
};
struct BakeRequest {
    uint32_t mID;
    uint16_t mFlags;
    uint16_t mPriority;
};
class IBaker {
public:
    virtual void f00(); virtual void f04(); virtual void f08(); virtual void f0c();
    virtual void f10(); virtual void f14(); virtual void f18(); virtual void f1c();
    virtual void SetProcessQueue(bool enable);  // 0x20
    virtual void f24(); virtual void f28(); virtual void f2c();
    virtual void f30(); virtual void f34(); virtual void f38(); virtual void f3c();
    virtual void f40(); virtual void f44(); virtual void f48();
    virtual void QueueBake(const ResourceKey_s0040_4660& key, const BakeRequest& request);  // 0x4c
};
struct MessageArg {
    uint32_t mValue;
    uint32_t mType;
};
namespace Resource_s0040_4660 {
class ThreadedObject_s0040_4660 {
public:
    ThreadedObject_s0040_4660(int refCount);
    virtual ~ThreadedObject_s0040_4660();
    virtual int AddRef();
    virtual int Release();
    volatile long mnRefCount;
};
}
struct MessageArgs {
    MessageArg mData[6];
    void SetValue(int index, uint32_t value) { mData[index].mValue = value; }
};
class ViewModelMessage : public Resource_s0040_4660::ThreadedObject_s0040_4660 {
public:
    ViewModelMessage() : ThreadedObject_s0040_4660(0), mField38(0) {}
    MessageArgs mArgs;    // +0x08
    uint32_t mField38;
    uint32_t mField3C;
};
void* operator new(unsigned int size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
inline uint32_t MakeGroupSubtype(uint32_t groupID, uint32_t subtype) { return (groupID & 0xffff00ff) | ((subtype & 0xff) << 8); }
inline uint32_t SetGroupSubtype(uint32_t groupID, uint32_t subtype) { groupID = MakeGroupSubtype(groupID, subtype); return groupID; }
IResourceManager_s0040_4660* ResourceManager_s0040_4660();     // 0x0067dcd0
IGameModeManager* GameModeManager();     // 0x0067dd10
IMessageManager_s0040_4660* MessageManager_s0040_4660();       // 0x0067dcc0
IRenderManager* RenderManager();         // 0x0067dda0
IBaker* Baker();                         // 0x00401010
void ResourceKeyFromString(ResourceKey_s0040_4660* pKey, const char* str, uint32_t defaultType, uint32_t defaultGroup);  // 0x0068d5a0
uint32_t GetTypeForCategory(uint32_t category, int);  // 0x004bbd20
bool IsBakeableType(uint32_t typeID, int);           // 0x004bbe20
void GetDisplayName(const ResourceKey_s0040_4660& key, string16& name, int);  // 0x00b1e4d0
void DescribeBlocks(int group, int instance);  // 0x0041c1d0
namespace ArgScript {
    class Line {
    public:
        const char* GetArgumentAt(int index);  // 0x00837f20
        int GetArgumentsCount();               // 0x00837f30
    };
}
namespace ArgScript {
    void PrintF(void* pOutput, const char* fmt, ...);  // 0x00841000
}
namespace ArgScript {
    class ICommand_s0040_4660 {
    public:
        virtual void ParseLine(Line& line);
        void* mpOutput;
        unsigned int mField8;
        unsigned int mFieldC;
    };
}
namespace ArgScript {
    class OptionParser_s0040_4660 {
    public:
        const char* GetUsage(const char* name, int verbose);  // 0x0083a2f0
        void Parse(Line& line, void* pOutput);                 // 0x0083b9d0
        bool IsSet(int option) const { return (mFlags & (1 << option)) != 0; }
        unsigned int mData[28];
        unsigned int mFlags;  // +0x70
        unsigned int mData2[21];
    };
}
class BakerCommand_s0040_4660 : public ArgScript::ICommand_s0040_4660 {
public:
    virtual void ParseLine(ArgScript::Line& line);

    IBaker* mpBaker;                    // +0x10
    ArgScript::OptionParser_s0040_4660 mOptions;   // +0x14
    const char* mKeyFilter;             // +0xdc
    int mLimit;                         // +0xe0
    bool mProcessQueue;                 // +0xe4
    int mFilterGroup;                   // +0xe8
    int mFilterInstance;                // +0xec
};
// ---- items of slice s00404660 end

// ---- items of slice s00405000 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace eastl {
    class allocator_s0040_5000 { public:
        inline void deallocate(void* p, unsigned int) { delete[] (char*)p; }
        unsigned int mFlags;
    };
}
namespace eastl {
    template <typename T>
    struct basic_string_s0040_5000 {
        T* mpBegin;
        T* mpEnd;
        T* mpCapacity;
        allocator_s0040_5000 mAllocator;

        inline ~basic_string_s0040_5000() { DeallocateSelf(); }
        inline void DeallocateSelf() {
            if ((mpCapacity - mpBegin) > 1)
                DoFree(mpBegin, (unsigned int)(mpCapacity - mpBegin));
        }
        inline void DoFree(T* p, unsigned int n) {
            if (p)
                mAllocator.deallocate(p, n * sizeof(T));
        }
    };
}
namespace eastl {
    typedef basic_string_s0040_5000<char> string;
}
namespace eastl {
    struct array_allocator_s0040_5000 {
        inline void deallocate(void* p, unsigned int) {
            if (((int*)p)[-1])
                delete[] (char*)p;
        }
        unsigned int mFlags;
        unsigned int mFlags2;
    };
}
namespace eastl {
    template <typename T>
    inline void destruct_s0040_5000(T* first, T* last) {
        for (; first < last; ++first)
            first->~T();
    }
}
namespace eastl {
    template <typename T>
    struct VectorBase_s0040_5000 {
        T* mpBegin;
        T* mpEnd;
        T* mpCapacity;
        array_allocator_s0040_5000 mAllocator;

        inline ~VectorBase_s0040_5000() {
            if (mpBegin)
                mAllocator.deallocate(mpBegin, (mpCapacity - mpBegin) * sizeof(T));
        }
    };
}
namespace eastl {
    template <typename T>
    class vector_s0040_5000 : public VectorBase_s0040_5000<T> { public:
        inline ~vector_s0040_5000() { destruct_s0040_5000(this->mpBegin, this->mpEnd); }
    };
}
namespace ArgScript {
    struct OptionArg {                  // 0x20
        unsigned int mType;
        eastl::string mName;
        unsigned int mData[3];
    };
}
namespace ArgScript {
    struct Option {                     // 0x38
        eastl::string mName;
        eastl::string mDescription;
        eastl::vector_s0040_5000<OptionArg> mArgs;
        unsigned int mFlags;
    };
}
namespace ArgScript {
    struct Flag {                       // 0x18
        eastl::string mName;
        unsigned int mData[2];
    };
}
namespace ArgScript {
    struct OptionIndex {
        ~OptionIndex();
        unsigned int mData[17];
    };
}
namespace ArgScript {
    class OptionParser_s0040_5000 {
    public:
        OptionParser_s0040_5000(int mode);                                  // 0x0083a9f0
        void AddOptions(const char* description, ...);           // 0x0083bcd0
        void PrintUsage(const char* name, void* stream);         // 0x0083a2f0

        eastl::string mName;             // +0x00
        eastl::string mDescription;      // +0x10
        eastl::string mUsage;            // +0x20
        eastl::vector_s0040_5000<OptionArg> mArgs;  // +0x30
        eastl::vector_s0040_5000<Option> mOptions;  // +0x44
        eastl::vector_s0040_5000<Flag> mFlags;      // +0x58
        unsigned int mFlagMask[2];       // +0x6c
        OptionIndex mIndex;              // +0x74
        eastl::string mLastError;        // +0xb8
    };
}
namespace ArgScript {
    class ICommand_s0040_5000 {
    public:
        ICommand_s0040_5000();
        virtual ~ICommand_s0040_5000();                     // 0x0083c750
        virtual void ParseLine(void* line);
        unsigned int mField4;
        unsigned int mField8;
        unsigned int mFieldC;
    };
}
class BakerCommand_s0040_5000 : public ArgScript::ICommand_s0040_5000 {
public:
    BakerCommand_s0040_5000(void* pBaker);  // 0x00405000 (BakerCommand::BakerCommand_s0040_5000)
    virtual ~BakerCommand_s0040_5000() {}
    virtual void ParseLine(void* line);  // 0x00404660 (BakerCommand::ParseLine)
    void Description(void* stream);  // 0x00404630 (BakerCommand::Description)

    void* mpBaker;                      // +0x10
    ArgScript::OptionParser_s0040_5000 mOptions;   // +0x14
    const char* mKeyFilter;             // +0xdc
    int mLimit;                         // +0xe0
    bool mProcessQueue;                 // +0xe4
    int mFilterGroup;                   // +0xe8
    int mFilterInstance;                // +0xec
};
template <typename T>
class intrusive_ptr_s0040_5000 {
public:
    T* mpObject;

    intrusive_ptr_s0040_5000() : mpObject(0) {}
    ~intrusive_ptr_s0040_5000() { if (mpObject) mpObject->Release(); }
    T* get() const { return mpObject; }
    T* operator->() const { return mpObject; }

    intrusive_ptr_s0040_5000& operator=(const intrusive_ptr_s0040_5000& ip) { return operator=(ip.mpObject); }
    intrusive_ptr_s0040_5000& operator=(T* pObject) {
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
};
class DefaultRefCounted_s0040_5000 {
public:
    virtual ~DefaultRefCounted_s0040_5000();

    int AddRef() {
        int count = mnRefCount + 1;
        mnRefCount = mnRefCount + 1;
        return count;
    }
    int Release();                      // 0x00453540
    void Unload();                      // 0x0055bee0

    int mnRefCount;
};
class BakeJob {
public:
    int AddRef();                       // 0x0068f950
    int Release();                      // 0x00690120
    void Cancel(int reason);            // 0x00692400
};
class IVirtualRefCounted_s0040_5000 {
public:
    virtual int AddRef() = 0;
    virtual int Release() = 0;
};
struct ResourceID {
    ResourceID() : mInstance(0), mGroup(0), mType(0) {}
    unsigned int mInstance;
    unsigned int mGroup;
    unsigned int mType;
};
struct BakeFormat {
    BakeFormat() : mTypeID(0x2ea8fb98), mLod(0), mFlags(4) {}
    unsigned int mTypeID;
    unsigned short mLod;
    unsigned short mFlags;
};
struct BakeEntry {
    ResourceID mKey;                               // +0x00
    BakeFormat mFormat;                            // +0x0c
    intrusive_ptr_s0040_5000<DefaultRefCounted_s0040_5000> mpModel;                         // +0x14
    intrusive_ptr_s0040_5000<DefaultRefCounted_s0040_5000> mpRig;                         // +0x18
    intrusive_ptr_s0040_5000<BakeJob> mpJob;                  // +0x1c
    intrusive_ptr_s0040_5000<IVirtualRefCounted_s0040_5000> mpTarget;    // +0x20
    intrusive_ptr_s0040_5000<IVirtualRefCounted_s0040_5000> mpOutputs[3]; // +0x24
};
class ICheatManager {
public:
    static ICheatManager* Get();                   // 0x0067de20
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
    virtual void RemoveCheat(const char* name);    // +0x1c
};
class IMessageManager_s0040_5000 {
public:
    static IMessageManager_s0040_5000* Get();                 // 0x0067dd80
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
    virtual void RemoveListener(unsigned int messageID);  // +0x18
};
struct KeyList {
    void* mpVTable;
    unsigned int mpBegin;
    unsigned int mpEnd;
    unsigned int mnCount;
    void Erase(unsigned int first, unsigned int last);   // 0x004e3590
    inline void clear() {
        Erase(mpBegin, mpEnd);
        mnCount = 0;
    }
};
struct LinearAllocator_s0040_5000 {
    void* mpVTable;
    unsigned int mpBegin;
    unsigned int mpEnd;
    unsigned int mpCurrent;
    unsigned int mpLast;
    void FreeTo(unsigned int p);                   // 0x00928c40
    inline void Reset(unsigned int p) {
        if (p > mpBegin && p < mpEnd) {
            mpCurrent = 0;
            mpLast = mpCurrent;
        } else
            FreeTo(p);
    }
};
class IBakeTarget {
public:
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
    virtual bool Process(unsigned int context, unsigned int item, unsigned int flags);  // +0x2c

    inline bool ProcessAll(unsigned int context, const unsigned int* items, unsigned int count,
                           unsigned int flags) {
        bool ok = true;
        for (unsigned int i = 0; i < count; i++) {
            if (!Process(context, items[i], flags))
                ok = false;
        }
        return ok;
    }
};
struct BakeBatch {
    IBakeTarget* mpTarget;
    unsigned int mContext;
    unsigned int* mpItems;
    unsigned int mnCount;
    unsigned int mFlags;

    inline bool Flush() {
        bool result = false;
        if (mpTarget) {
            IBakeTarget* target = mpTarget;
            mpTarget = 0;
            result = target->ProcessAll(mContext, mpItems, mnCount, mFlags);
        }
        return result;
    }
};
struct BakeQueue {
    void Clear();                                  // 0x00402b30
    unsigned int mData[26];
};
struct BakeMap {
    struct node_iterator {                         // 0x14
        void* mpNode;
        unsigned int mData[4];

        BakeEntry* operator->() const;             // 0x005658b0
        bool operator==(const node_iterator& x) const { return mpNode == x.mpNode; }
    };

    struct iterator {                              // 0x1c
        void* mpList;
        node_iterator mIt;
        void* mpListEnd;

        iterator& operator++();                    // 0x00421f00
        BakeEntry* operator->() const { return mIt.operator->(); }
        BakeEntry& operator*() const { return *mIt.operator->(); }
        bool operator==(const iterator& x) const {
            return mpList == x.mpList && (mpList == mpListEnd || mIt == x.mIt);
        }
        bool operator!=(const iterator& x) const { return !(*this == x); }
    };

    iterator begin();                              // 0x00420200
    iterator end();                                // 0x00420350
    void clear();                                  // 0x00420440
    unsigned int mData[0x58];
};
class Baker_s0040_5000 {
public:
    void CancelAll();  // 0x004051e0 (Baker::CancelAll)
    void Shutdown();  // 0x004055b0 (Baker::Shutdown)

    unsigned int mPad00[12];
    KeyList mBakedKeys;                            // +0x30
    unsigned int mPad40[4];
    LinearAllocator_s0040_5000 mArena;                        // +0x50
    unsigned int mPad64[4];
    intrusive_ptr_s0040_5000<IVirtualRefCounted_s0040_5000> mpWindow;    // +0x74
    intrusive_ptr_s0040_5000<IVirtualRefCounted_s0040_5000> mpLayout;    // +0x78
    unsigned int mPad7c[3];
    intrusive_ptr_s0040_5000<DefaultRefCounted_s0040_5000> mpModelRes;   // +0x88
    intrusive_ptr_s0040_5000<DefaultRefCounted_s0040_5000> mpRigRes;     // +0x8c
    unsigned int mPad90[14];
    BakeMap mQueued;                               // +0xc8
    BakeEntry mCurrent;                            // +0x228
    unsigned char mPad258;
    bool mbBaking;                                 // +0x259
    unsigned char mPad25a[2];
    BakeQueue mPending;                            // +0x25c
    bool mbProcessQueue;                           // +0x2c4
    unsigned char mPad2c5[3];
    BakeQueue mDeferred;                           // +0x2c8
    unsigned int mPad330[(0x1168 - 0x330) / 4];
    BakeBatch mBatch;                              // +0x1168
};
// ---- items of slice s00405000 end

// ---- items of slice s00406ac0 begin (TODO(rewrite): local stubs, replace by canonical classes)
template <class T> struct is_integral : public false_type {};
class RefCounted_s0040_6ac0 {
public:
    virtual int AddRef();
    virtual int Release();
};
template <class T> class intrusive_ptr_s0040_6ac0 {
public:
    intrusive_ptr_s0040_6ac0() : mpObject(0) {}
    ~intrusive_ptr_s0040_6ac0() { if (mpObject) mpObject->Release(); }

    T* get() const { return mpObject; }

    // Drops the current reference and hands out the raw slot, for APIs that
    // fill an intrusive_ptr through a T** out-parameter.
    T** AsOutParam()
    {
        if (mpObject) { T* pOld = mpObject; mpObject = 0; pOld->Release(); }
        return &mpObject;
    }

    intrusive_ptr_s0040_6ac0& operator=(const intrusive_ptr_s0040_6ac0& ip) { return operator=(ip.mpObject); }
    intrusive_ptr_s0040_6ac0& operator=(T* pObject)
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
union GroupID {
    uint32_t value;
    struct {
        uint32_t low : 16;
        uint32_t kind : 8;      // bits 16..23
        uint32_t variant : 5;   // bits 24..28
        uint32_t high : 3;
    };
};
inline GroupID MakeGroup(uint32_t v) { GroupID g; g.value = v; return g; }
inline uint32_t WithVariant(uint32_t groupID, uint32_t variant)
{
    GroupID g;
    g.value = groupID;
    g.variant = variant;
    return g.value;
}
class Property_s0040_6ac0 {
public:
    bool* GetValueBool();            // 0x0041e920
    uint16_t pad[9];
    uint16_t mnType;                 // +0x12  (1 = bool)
};
class PropertyList_s0040_6ac0 {
public:
    virtual int AddRef();  // 0x00432be0 (PropertyList::AddRef)
    virtual int Release();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
    virtual bool GetProperty(uint32_t propertyID, Property_s0040_6ac0*& result);  // +0x24
};
class PropertyManager_s0040_6ac0 {
public:
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
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyList_s0040_6ac0** ppDst); // +0x2c
};
PropertyManager_s0040_6ac0* PropertyManager_Get();   // 0x0067de30
inline bool GetBoolPropertyInline(PropertyList_s0040_6ac0* list, uint32_t propertyID, bool& result)
{
    Property_s0040_6ac0* pProp;
    bool* pValue;
    if (list && list->GetProperty(propertyID, pProp) && pProp->mnType == 1) {
        result = *pProp->GetValueBool();
        return true;
    }
    return false;
}
bool GetBoolProperty(PropertyList_s0040_6ac0* list, uint32_t propertyID, bool& result);  // 0x00407190 (defined below; used by a stub's inline body)
inline void GetBoolPropertyOutOfLine(const intrusive_ptr_s0040_6ac0<PropertyList_s0040_6ac0>& list, uint32_t propertyID, bool& result)
{
    uint32_t reserved0, reserved1, reserved2;
    GetBoolProperty(list.get(), propertyID, result);
}
const uint32_t kPropEnabled          = 0x3704e55;
const uint32_t kPropEnabledSecondary = 0x3704e56;
struct ResourceFlagQuery {
    bool IsFlagged(const ResourceKey& key, bool requireSecondary);
};
class IPredicateTarget {
public:
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
    virtual bool TestA(void* arg, int flags);     // +0x1c
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
    virtual bool TestB(void* arg);                // +0x3c
    bool TestAny(void* arg);
};
bool KeysDiffer(const ResourceKey& a, const ResourceKey& b);       // 0x0041dd30
void RemapKey(ResourceKey& key, const ResourceKey& replacement);    // 0x0041ddb0
extern ResourceKey kNullKey;                                        // 0x015d1564
struct KeyPair { ResourceKey a; ResourceKey b; };
template <class T> struct vector_s0040_6ac0 {
    T* mpBegin; T* mpEnd; T* mpCapacity;
    int size() const { return mpEnd - mpBegin; }
    T& operator[](int i) { return mpBegin[i]; }
};
struct KeyRemapper {
    void Apply(vector_s0040_6ac0<KeyPair>& pairs, ResourceKey key);
};
struct Elem0C { uint32_t d[6]; };
class FixedVectorA {
public:
    Elem0C* mpBegin; Elem0C* mpEnd;
    uint32_t mStorage[0xd8 / 4 - 2];
    Elem0C* begin() const { return mpBegin; }
    Elem0C* end() const { return mpEnd; }
    Elem0C* erase(Elem0C* first, Elem0C* last);                                   // 0x0050f740
    template <class InputIterator> void DoAssign(InputIterator first, InputIterator last, false_type); // 0x0042c2a0
    template <class InputIterator> void assign(InputIterator first, InputIterator last)
    {
        false_type unused;
        DoAssign(first, last, is_integral<InputIterator>());
    }
    FixedVectorA& operator=(const FixedVectorA& x)
    {
        if (this != &x) {
            erase(mpBegin, mpEnd);
            assign(x.begin(), x.end());
        }
        return *this;
    }
};
class FixedVectorB {
public:
    void* mpBegin; void* mpEnd;
    uint32_t mStorage[0x398 / 4 - 2];
    void* begin() const { return mpBegin; }
    void* end() const { return mpEnd; }
    void* erase(void* first, void* last);                     // 0x004238c0
    void DoAssign(const void* first, const void* last);       // 0x00422d90
    void assign(const void* first, const void* last) { DoAssign(first, last); }
    FixedVectorB& operator=(const FixedVectorB& x)
    {
        if (this != &x) {
            erase(mpBegin, mpEnd);
            assign(x.begin(), x.end());
        }
        return *this;
    }
};
class FixedVectorC {
public:
    void* mpBegin; void* mpEnd;
    uint32_t mStorage[0xd8 / 4 - 2];
    void* begin() const { return mpBegin; }
    void* end() const { return mpEnd; }
    void* erase(void* first, void* last);                     // 0x0050f740
    void DoAssign(const void* first, const void* last);       // 0x00422d60
    void assign(const void* first, const void* last) { DoAssign(first, last); }
    FixedVectorC& operator=(const FixedVectorC& x)
    {
        if (this != &x) {
            erase(mpBegin, mpEnd);
            assign(x.begin(), x.end());
        }
        return *this;
    }
};
class FixedVectorD {
public:
    void* mpBegin; void* mpEnd;
    uint32_t mStorage[0x58 / 4 - 2];
    void* begin() const { return mpBegin; }
    void* end() const { return mpEnd; }
    void* erase(void* first, void* last);                     // 0x004769b0
    void DoAssign(const void* first, const void* last);       // 0x00422dc0
    void assign(const void* first, const void* last) { DoAssign(first, last); }
    FixedVectorD& operator=(const FixedVectorD& x)
    {
        if (this != &x) {
            erase(mpBegin, mpEnd);
            assign(x.begin(), x.end());
        }
        return *this;
    }
};
class FixedVectorE {
public:
    void* mpBegin; void* mpEnd;
    uint32_t mStorage[0x118 / 4 - 2];
    void* begin() const { return mpBegin; }
    void* end() const { return mpEnd; }
    void clear();                                             // 0x004208f0
    void DoAssign(const void* first, const void* last);       // 0x00422dc0
    void assign(const void* first, const void* last) { DoAssign(first, last); }
    FixedVectorE& operator=(const FixedVectorE& x)
    {
        if (this != &x) {
            clear();
            assign(x.begin(), x.end());
        }
        return *this;
    }
};
class FixedVectorF {
public:
    void* mpBegin; void* mpEnd;
    uint32_t mStorage[0x118 / 4 - 2];
    void* begin() const { return mpBegin; }
    void* end() const { return mpEnd; }
    void clear();                                             // 0x00420980
    void DoAssign(const void* first, const void* last);       // 0x00422df0
    void assign(const void* first, const void* last) { DoAssign(first, last); }
    FixedVectorF& operator=(const FixedVectorF& x)
    {
        if (this != &x) {
            clear();
            assign(x.begin(), x.end());
        }
        return *this;
    }
};
class FixedListG {
public:
    uint32_t mData[0x118 / 4];
    FixedListG& operator=(const FixedListG& x);   // 0x0041d140
};
class MapH {
public:
    uint32_t mData[0x20 / 4];
    void DoCopy(const MapH& x);                   // 0x00420b10
    MapH& operator=(const MapH& x) { DoCopy(x); return *this; }
};
struct EditorSnapshot {
    bool mbActive;                        // +0x000
    float mfValue;                        // +0x004
    intrusive_ptr_s0040_6ac0<RefCounted_s0040_6ac0> mpOwner;    // +0x008
    FixedVectorA mItems;                  // +0x00c
    FixedVectorB mEntries;                // +0x0e4
    FixedVectorC mIndices;                // +0x47c
    FixedVectorB mEntries2;               // +0x554
    FixedVectorD mSmall;                  // +0x8ec
    uint32_t mField944;                   // +0x944
    float mField948;                      // +0x948
    float mField94C;                      // +0x94c
    uint32_t mField950;                   // +0x950
    uint32_t mField954;                   // +0x954
    uint32_t mField958;                   // +0x958
    uint32_t mField95C;                   // +0x95c
    FixedVectorE mListE;                  // +0x960
    FixedVectorF mListF;                  // +0xa78
    FixedListG mListG;                    // +0xb90
    MapH mMap;                            // +0xca8
    uint32_t mFieldCC8;                   // +0xcc8

    EditorSnapshot& operator=(const EditorSnapshot& x);
};
// ---- items of slice s00406ac0 end

// ---- items of slice s004098a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kFloatMax;     // 0x013EB258
#pragma intrinsic(fabs)
struct Vec3Data {
    float x, y, z;
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};
struct Vector3 : Vec3Data {
    Vector3() {}
    Vector3(float ax, float ay, float az) { x = ax; y = ay; z = az; }
    Vector3(const Vec3Data& o) { x = o.x; y = o.y; z = o.z; }
    Vector3(const Vector3& o) { x = o.x; y = o.y; z = o.z; }
    Vector3& operator=(const Vector3& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
struct Matrix3 {
    Vec3Data m[3];
    Matrix3() {}
    Matrix3(const Matrix3& o);  // 0x0041CB40
    void Assign(const Matrix3& o);  // 0x0041CB40
    Matrix3& operator=(const Matrix3& o) { Assign(o); return *this; }
    Vec3Data& operator[](int i) { return m[i]; }
    const Vec3Data& operator[](int i) const { return m[i]; }
};
Vector3 operator-(const Vec3Data& a, const Vec3Data& b);    // 0x0041DB10
Vector3 operator+(const Vec3Data& a, const Vec3Data& b);    // 0x0041DC10
Vector3 operator*(const Vec3Data& a, const float& s);      // 0x0041DCA0
Vector3 operator*(const float& s, const Vec3Data& a);      // 0x0041DE40
Vec3Data& operator*=(Vec3Data& a, const float& s);          // 0x0041DBA0
Vector3 operator*(const Vec3Data& v, const Matrix3& m);    // 0x0041DAF0 (calls 0x00423160)
extern Matrix3 g_IdentityMatrix;  // 0x015D1434
extern Vector3 g_ZeroVector;      // 0x015D1564
struct BoundingBox {
    Vec3Data min;
    Vec3Data max;
    void Reset();                                    // 0x00409C00
    void SetCenterRadius(const Vector3& center, float r);  // 0x00409CE0
    Vector3& GetCenter(Vector3& out) const;          // 0x00409B90
    void TransformBy(const struct Transform& t);     // 0x00409DD0
};
struct Transform {
    unsigned short mFlags;    // bit0 = scaled, bit1 = rotated
    unsigned short mVersion;  // bumped on every change
    Vector3 mPos;
    float mScale;
    Matrix3 mRot;

    Transform();                                // 0x00409930
    void RotateY(float angle);                  // 0x004099B0
    void Scale(float s);                        // 0x00409B30
    float GetScale() const { return mScale; }
    bool IsRotated() const { return (mFlags & 2) != 0; }
};
struct Matrix3Raw { float f[9]; };
Vector3 operator*(const Vec3Data& v, const Matrix3Raw& m);   // 0x0041DAF0
struct Vector3Copyable {
    float x, y, z;
    Vector3Copyable(const Vector3Copyable& o);
};
template <int N> inline void PadN() { unsigned int s[N]; }
// ---- items of slice s004098a0 end

// ---- items of slice s0040a170 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_Manager;   // 0x15fd918
struct ResourceKey_s0040_a170 {
    uint32_t instance;   // +0
    uint32_t type;       // +4
    uint32_t group;      // +8; byte 1 / byte 2 hold sub-type tags
};
struct KeyFlags {
    uint32_t id;         // +0
    uint16_t flags;      // +4: 0x1 = add, 0x20 = skip, 0x100 = extra
    uint16_t index;      // +6
};
struct RefCounted;
// 0x1c-byte container iterator returned by the slot map (420270 / 420120 / find_if).
struct Iter28_s0040_a170 { uint32_t v[7]; };
// 0x30-byte keyed record stored in the slot map: v[0..2] key, v[3] info->id,
// v[4] flags|index<<16, v[5..11] refcounted pointers.
struct KeyedRecord_s0040_a170 { uint32_t v[12]; };
extern void* EASTL_allocator_allocate(uint32_t size, const char* name, uint32_t, uint32_t, uint32_t, uint32_t);
// The container helpers take `this` in ECX and pop their stack arguments themselves (ret N); model
// that with __fastcall plus an unused EDX filler.
extern bool  FUN_00401d90(const ResourceKey_s0040_a170* k);                              // cdecl, 1 arg
extern void* __fastcall FUN_00423110(void* self, int, uint32_t);                          // ctor (ret 4)
extern void* __fastcall FUN_00421c80(void* self, int, uint32_t);                          // ctor (ret 4)
extern bool  __fastcall FUN_006a25a0(void* self, int, uint32_t);                          // ret 4
extern void  FUN_0068c700(ResourceKey_s0040_a170* k, int);
extern void  FUN_0068c6d0(ResourceKey_s0040_a170* k, uint32_t, int);
extern void  __fastcall FUN_004036e0(void* self);                                          // KeyedRecord ctor
extern void* __fastcall FUN_00401e40(void* self);                                          // 0x18-byte modifier ctor
extern void  __fastcall FUN_00401ef0(void* self, int, const ResourceKey_s0040_a170* key);   // ret 4
extern void  __fastcall FUN_00401f20(void* self);                                          // KeyedRecord dtor
extern void* __fastcall FUN_005658b0(void* self);                                          // *(void**)self
extern void  __fastcall FUN_004063d0(void* self, int, const KeyedRecord_s0040_a170* src);   // copy ctor (ret 4)
extern void  __fastcall FUN_00453540(void* self);                                          // release
struct Notifier {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5();
    virtual void Post(uint32_t msg, void* payload, int, int); // slot 6 (+0x18)
};
Notifier* GetNotifier();     // FUN_0067dcc0
struct ResourceMessenger {   // FUN_0067de30 result; vtable slot 11 (+0x2c) = send
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10();
    virtual void Send(uint32_t id, uint32_t tagged, RefCounted** outRef);
};
ResourceMessenger* GetResourceMessenger();   // @ 0x0067de30
struct SlotMap {};           // lives at EditorList+0xc8
extern void  __fastcall FUN_00420270(void* self, int, Iter28_s0040_a170* out, uint32_t idx);            // upper_bound (ret 8)
extern void  __fastcall FUN_00420120(void* self, int, Iter28_s0040_a170* out, uint32_t idx);            // lower_bound (ret 8)
extern void  __fastcall FUN_004204f0(void* self, int, const KeyedRecord_s0040_a170* rec, uint32_t idx); // push front (ret 8)
extern void  __fastcall FUN_004204d0(void* self, int, const KeyedRecord_s0040_a170* rec, uint32_t idx); // replace (ret 8)
extern void  __fastcall FUN_00420390(void* self, int, Iter28_s0040_a170 it, void* out);                 // assign (ret 0x20)
extern Iter28_s0040_a170* FUN_00422140(Iter28_s0040_a170* out, Iter28_s0040_a170 first,
                                       Iter28_s0040_a170 last, const KeyFlags* info,
                                       const ResourceKey_s0040_a170* key);                          // find_if
struct EditorList {
    char pad[0xc4];          // vptr + 0xc4 == slots at +0xc8
    SlotMap slots;
    void ApplyEntry(const ResourceKey_s0040_a170* key, const KeyFlags* info);   // @ 0x0040a170
    bool HandleKey(const ResourceKey_s0040_a170* key, const KeyFlags* info);    // @ 0x0040a590
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6();
    virtual bool Accept(const ResourceKey_s0040_a170* k, bool extra);   // slot 7 (+0x1c)
};
extern void  __fastcall EditorList_Prepare(EditorList* self, int, ResourceKey_s0040_a170* k);                 // FUN_00407280 (ret 4)
extern void  __fastcall EditorList_Forward(EditorList* self, int, ResourceKey_s0040_a170* k, const void* extra); // FUN_004157d0 (ret 8)
static inline bool IsEditorType(const ResourceKey_s0040_a170* k)
{
    return k->type == 0x2b978c46 || k->type == 0x438f6347 || k->type == 0x3d97a8e4;
}
// ---- items of slice s0040a170 end

// ---- items of slice s0040a9c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct GroupId {
    uint32_t value;
    uint32_t GetKind() const { return (value >> 16) & 0xff; }
    uint32_t GetSub() const { return (value >> 24) & 0x1f; }
    void SetSub(uint32_t s) { value = (value & 0xe0ffffff) | ((s & 0x1f) << 24); }
};
struct ResourceKey_s0040_a9c0 {
    uint32_t instance;
    uint32_t type;
    GroupId group;
};
struct Vector3_s0040_a9c0 {
    float x, y, z;
    Vector3_s0040_a9c0() {}
    Vector3_s0040_a9c0(const Vector3_s0040_a9c0& o) : x(o.x), y(o.y), z(o.z) {}
};
struct RefCounted_s0040_a9c0 {
    virtual void AddRef();
    virtual void Release();
};
struct PropertyHolder : RefCounted_s0040_a9c0 {
    uint32_t pad[11];
    uint32_t extra;         // +0x30
    uint32_t GetExtra() const { return extra; }
};
struct RefCounted {
    virtual void AddRef();
    virtual void Release();
};
struct PropRef {
    PropertyHolder* p;
    PropRef() : p(0) {}
    PropertyHolder** operator&() {
        if (p) { PropertyHolder* t = p; p = 0; t->Release(); }
        return &p;
    }
    PropertyHolder* operator->() const { return p; }
};
struct cPropertyList : RefCounted_s0040_a9c0 {
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
    virtual void v10();
    virtual void LoadImpl(PropertyHolder* props);   // +0x2c
    uint32_t pad[13];
    cPropertyList();
    void Init(uint32_t extra);                       // 0x6A1710
    void Load(PropertyHolder* props) { LoadImpl(props); }
};
inline void* operator new(size_t size, const char* tag, int a, int b, int c, int d);
struct ResourceManager_s0040_a9c0 {
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
    virtual bool HasResource(uint32_t instance, uint32_t group);                          // +0x28
    virtual bool OpenProperties(uint32_t instance, uint32_t group, PropertyHolder** out); // +0x2c
    virtual void v12();
    virtual void StoreProperties(cPropertyList* list, uint32_t instance, uint32_t group); // +0x34
};
ResourceManager_s0040_a9c0* GetResourceManager();                                  // 0x67DE30
void GetBoolProperty(PropertyHolder* p, uint32_t id, bool* out);        // 0x407190
void* AllocateTagged(uint32_t size, const char* name, int, int, int, int); // 0xF473A0
inline void* operator new(size_t size, const char* tag, int a, int b, int c, int d)
{
    return AllocateTagged(size, tag, a, b, c, d);
}
void SavePropertyList(cPropertyList* l, int flag);                      // 0x6B2090
struct WorldObject {
    uint32_t pad[4];
    int flag;                                        // +0x10
    int GetFlag() const { return flag; }
    void GetPosition(Vector3_s0040_a9c0* out, int a, int b, int c);   // 0x44AE00
};
struct World {
    int GetObjectCount();                            // 0x4ACCF0
    WorldObject* GetObject(int index);               // 0x4ACCB0
};
struct ObjectVector {
    WorldObject** begin; WorldObject** end; WorldObject** cap;
    void Resize(int n);                              // 0x4207E0
    void Remove(WorldObject** it);                   // 0x422380
    int Size() const { return (int)(end - begin); }
};
struct Notifier_s0040_a9c0 { void Notify(void* who); };         // 0x422280
void GetWorldCenter(Vector3_s0040_a9c0* out, World* w);         // 0x46BFD0
void SetWorldCenter(World* w, Vector3_s0040_a9c0 v, int flag);  // 0x4934D0
void UpdateWorld(World* w);                          // 0x4B7660
Vector3_s0040_a9c0 VectorSub(const Vector3_s0040_a9c0& a, const Vector3_s0040_a9c0& b);  // 0x41DB10
float VectorLength(const Vector3_s0040_a9c0* v);
struct NearbyObjectList {
    char pad0[0x228]; uint32_t m_unk228;
    char pad1[4];     uint32_t m_unk230;
    char pad2[0x334 - 0x234]; World* m_world;
    char pad3[0x430 - 0x338]; float m_maxDistance;
    char pad4[0xd80 - 0x434]; int m_count;
    char pad5[0xd8c - 0xd84]; ObjectVector m_objects;
    char pad6[0x10f4 - 0xd98]; uint32_t m_dirty;
    void Refresh(void* listener);
};
struct KeyCopier {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
    virtual bool CanCopy(const ResourceKey_s0040_a9c0* key, int flag);                 // +0x1c
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
    virtual bool CopyKey(const ResourceKey_s0040_a9c0* src, const ResourceKey_s0040_a9c0* dst);   // +0x50

    bool Copy(const ResourceKey_s0040_a9c0* src, const ResourceKey_s0040_a9c0* dst);
    void RefreshList();
};
// ---- items of slice s0040a9c0 end

// ---- items of slice s0040e5b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t g_SomeKey;        // 0x015D13E8
struct Releasable {
    virtual void v0();
    virtual void Release();                 // slot 1
};
struct Msg {                                // FUN_0067dcc0() result: message dispatcher
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void Post(uint32_t id, int a, int b);                 // slot 5
    virtual void Post4(uint32_t id, int a, int b, int c);         // slot 6
};
struct Sink {                               // FUN_0067de30() result
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10();
    virtual void Set(uint32_t v);                                 // slot 11
};
struct PathProvider {                       // returned by slot 11 of the app object
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15();
    virtual void* GetName();                                      // slot 16 (0x40)
    virtual uint32_t Lookup(uint32_t key, Releasable** out);      // slot 17 (0x44)
};
struct App {                                // FUN_0067dd10() result
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10();
    virtual PathProvider* GetPathProvider();                      // slot 11 (0x2c)
    virtual void v12(); virtual void v13();
    virtual uint32_t GetKind();                                   // slot 14 (0x38)
};
struct Dir {                                // FUN_006b1f90() result
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual const wchar_t* GetDirName();                          // slot 10 (0x28)
};
struct Prop {                               // object queried through slot 9 (0x24)
    char pad[0x12];
    uint16_t type;
};
struct Provider {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual bool GetProp(uint32_t id, Prop** out);                // slot 9 (0x24)
};
App* GetApp();                    // FUN_0067dd10
Sink* GetSink();                  // FUN_0067de30
Msg* GetMsgManager();             // FUN_0067dcc0
bool __cdecl QueryInterfaceRaw(Releasable* obj, uint32_t id, void** out);   // FUN_006a12e0
Dir* __cdecl GetDir(void* p);                                               // FUN_006b1f90
void __cdecl FormatPath(wchar_t* dst, const wchar_t* fmt, ...);             // FUN_0041e050
void __cdecl ReleaseBlock(void* p);                                         // EASTL_allocator_deallocate
void __cdecl ProcessLayout(void*, uint32_t, uint32_t, uint32_t, void*, void*, void*, void*); // FUN_0042ff00
struct PathNameRef { wchar_t* GetString(); };   // FUN_004ae000 (thiscall on GetName() result)
struct ValueRef { uint32_t* Get(); };           // FUN_0041e990 (thiscall)
struct RefPtr_s0040_e5b0 {
    Releasable* p;
    inline Releasable** Reset() {
        if (p) {
            Releasable* t = p;
            p = 0;
            t->Release();
        }
        return &p;
    }
};
inline bool Query(Releasable* obj, void** out) {
    uint32_t scratch[24];
    const uint32_t id = 0x70104290;      // interface id
    return QueryInterfaceRaw(obj, id, out);
}
struct Str {                                    // FUN_00406ac0 target
    char pad[4];
    void Assign(uint32_t v);
};
struct BigScratch {                             // 0xccc-byte stack object (FUN_00418120 / FUN_00418240)
    uint32_t data[0x333];
    uint32_t Init();
    void Done();
};
struct Range {                                  // 16-byte-element vector (begin/end)
    char* begin;
    char* end;
    void Erase(char* first, char* last);        // FUN_00548690
    inline int size() const { return (end - begin) >> 4; }
    inline void clear() { uint32_t scratch[6]; Erase(begin, end); }
};
struct Range2 {
    char* begin;
    char* end;
    char* Clear(char* first, char* last);       // FUN_00426280, returns first
    inline void clear() { uint32_t scratch[11]; Clear(begin, end); }
};
struct Flags { char pad[4]; uint16_t flags; };
struct Obj {
    char p0[0x228];
    uint32_t f228;
    char p1[4];
    uint32_t f230;
    Flags opts;                                 // 0x234
    char p2[0x24c - 0x23c];
    Provider* provider;                         // 0x24c
    char p3[0x338 - 0x250];
    char lay338[0x14];                          // 0x338
    Range2 r34c;                                // 0x34c
    char p5[0x374 - 0x354];
    char f374[0x28];
    char f39c[0x14];
    char f3b0[0x18];
    char f3c8[0x30];
    uint32_t f3f8;
    uint32_t f3fc;
    wchar_t path[8];                            // 0x400
    Range vec;                                  // 0x410
    char p6[0x42c - 0x418];
    Str str42c;                                 // 0x42c

    bool OnClear(int arg);      // 0x40e9c0 (message 0x029D252F)
    bool OnReset(int arg);      // 0x40eab0 (message 0x02458018)
    bool OnA(int arg);          // 0x40e5b0
    bool Fn40eb70();
    bool Fn40f110();
    bool Fn40f3f0(int);
    bool Fn40f4a0(int);
    bool Fn40f820(int);
    bool Fn40fc00(int);
    bool Fn40fe00(int);
    bool Fn4103c0(int);
    bool Fn410dd0(int);
    bool Fn410f90(int);
};
struct Dispatcher {   // this = Obj + 4 (second base)
    char pad[0x255];
    uint8_t enabled;
    bool Handle(uint32_t id, int arg);
};
// ---- items of slice s0040e5b0 end

// ---- items of slice s0040eb70 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kOne;                                      // 0x01485720 (1.0f)
#define VS1(p) virtual void p##_a();
#define VS2(p) VS1(p##0) VS1(p##1)
#define VS4(p) VS2(p##0) VS2(p##1)
#define VS8(p) VS4(p##0) VS4(p##1)
#define VS16(p) VS8(p##0) VS8(p##1)
#define VS32(p) VS16(p##0) VS16(p##1)
#define VS64(p) VS32(p##0) VS32(p##1)
struct M9 {
    float m[9];
};
struct Matrix3_s0040_eb70 : M9 {
    Matrix3_s0040_eb70& operator=(const Matrix3_s0040_eb70& o) {
        M9::operator=(o);
        return *this;
    }
};
struct Vector3_s0040_eb70 {
    float x, y, z;
    Vector3_s0040_eb70& operator=(const Vector3_s0040_eb70& o) {
        x = o.x;
        y = o.y;
        z = o.z;
        return *this;
    }
    Vector3_s0040_eb70& MulAssign(const Matrix3_s0040_eb70& m);  // v = v * m
};
Vector3_s0040_eb70 operator*(const Vector3_s0040_eb70& v, const Matrix3_s0040_eb70& m);        // 0x0041DAF0
Vector3_s0040_eb70& operator*=(Vector3_s0040_eb70& v, const float& s);              // 0x0041DBA0
Matrix3_s0040_eb70* Matrix3Inverse(Matrix3_s0040_eb70* out, const Matrix3_s0040_eb70* m);      // 0x0041DED0
inline Vector3_s0040_eb70& Vector3_s0040_eb70::MulAssign(const Matrix3_s0040_eb70& m) {
    *this = *this * m;
    return *this;
}
struct Source;
struct PartTransform {
    uint32_t pad0;
    Vector3_s0040_eb70 mPosition;   // +0x04
    float mScale;        // +0x10
    Matrix3_s0040_eb70 mRotation;   // +0x14
    uint32_t pad1[(0x74 - 0x38) / 4];
    Source* mpSource;    // +0x74
    uint32_t pad2[(0x7C - 0x78) / 4];

    void Invert();                       // 0x0040EFA0
    Source* GetSource() { return mpSource; }
    void Rebuild(const void* xform);     // 0x00537DC0
};
struct Counted;
struct CountedOwner {
    VS64(a) VS16(b) VS8(c) VS4(d)             // 92 slots
    virtual void SetBit(Counted* obj, bool bit);  // slot 92 (+0x170)
};
struct Bits32 {
    uint32_t mWord;
    bool Test(unsigned n) const {
        if (n < 32) {
            uint32_t w = mWord;
            return (w & (1u << (n % 32))) != 0;
        }
        return false;
    }
};
struct Counted {
    CountedOwner* mpOwner;
    Bits32 mBits;
    uint32_t pad[(0x40 - 8) / 4];
    int mRefCount;  // +0x40, plain (non-atomic)

    int Release();
};
struct Field0 { uint32_t d[5]; Field0(const Field0&); };   // 0x0041F6C0
struct Field1 { uint32_t d[5]; Field1(const Field1&); };   // 0x0041F840
struct Field2 { uint32_t d[5]; Field2(const Field2&); };   // 0x00535DA0
struct Field3 { uint32_t d[5]; Field3(const Field3&); };   // 0x0041FA20
struct HolderBase {
    virtual void BaseV0();
    long mRefCount;  // +4
    HolderBase() {
        long* target = &mRefCount;
        {
            uint32_t dead[32];  // dead local of the original inline expansion (frame size)
        }
        _InterlockedExchange(target, 0);
    }
};
struct PartHolder : HolderBase {
    Field0 mA;   // +0x08
    Field1 mB;   // +0x1C
    Field2 mC;   // +0x30
    Field3 mD;   // +0x44

    PartHolder(const PartHolder* src);   // 0x0040F070
    virtual void HolderV0();
    void Release();                      // 0x00404F90 (ThreadedObject::Release)
    void AddRef() { _InterlockedIncrement(&mRefCount); }
};
struct Messenger {
    VS4(a) VS2(b)                                            // 6 slots
    virtual void Post(unsigned msg, int a, int b, int c);    // slot 6 (+0x18)
};
struct Service2 {
    VS16(a) VS1(b)                                           // 17 slots
    virtual void Run(unsigned id);                           // slot 17 (+0x44)
};
Messenger* GetMessenger();   // 0x0067DCC0
Service2* GetService2();     // 0x0067DDB0
struct PropList;
void __cdecl GetProp(PropList* p, unsigned id, void* out);       // 0x006A12A0
void __cdecl GetBoolProp(PropList* p, unsigned id, bool* out);   // 0x00407190
struct PropList {
    VS8(a) VS1(b)                                            // 9 slots
    virtual bool Find(unsigned id, struct PropValue** out);  // slot 9 (+0x24)
    void Get(unsigned id, void* out) { GetProp(this, id, out); }
    void GetBool(unsigned id, bool* out) { GetBoolProp(this, id, out); }
};
struct PropValue {
    uint32_t pad0[0x12 / 4];
    uint16_t pad1;
    uint16_t mType;  // +0x12
    bool* GetBool();  // 0x0041E920
};
struct Source {
    VS2(a) VS1(b)                                                 // 3 slots
    virtual Counted* Lookup(unsigned a, unsigned b, int c);  // slot 3 (+0x0C)
};
struct Key;  // part resource key
template <class T> struct PtrVec {
    T** mpBegin;
    T** mpEnd;
    T** mpCap;
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
    T* At(unsigned i) const {
        T** p = mpBegin + i;
        return *p;
    }
};
struct Alloc {
    uint32_t d[2];
    Alloc() {}
    Alloc(const AllocTag&);            // 0x00429360
};
struct IntVec {
    int* mpBegin;
    int* mpEnd;
    int* mpCap;
    Alloc mAlloc;
    uint32_t mPad[3];
    IntVec();                       // 0x0041D590
    ~IntVec();                      // 0x004209B0
    void push_back(const int& v);   // 0x00422380
    bool empty() const;             // 0x00526430
    int* data() const {
        uint32_t dead[8];
        {
            int* r = mpBegin;
            return r;
        }
    }
};
struct PartXform38 {
    uint32_t d[0x38 / 4];
};
void* EASTL_allocator_allocate(unsigned size, const char* name, int a, int b, int c, int d);  // 0x00F473A0
inline void* operator new(unsigned size, const char* name) {
    uint32_t dead[1];
    return EASTL_allocator_allocate(size, name, 0, 0, 0, 0);
}
void __cdecl ApplyPart(Key* key, PartXform38* xf, int mode);     // 0x006DBED0
void __cdecl FitPart(PartXform38* xf, Key* key);                 // 0x00734D00
void __cdecl TouchPart(Key* key, int a, int mode);               // 0x007541B0
int __cdecl QueryPart(Key* key, int a, int b, int c, int d);     // 0x0071DDC0
void __cdecl ApplyShapes(Key* key, unsigned count, int* data);   // 0x00738610
void __cdecl Collect(void* vec, Source* src, unsigned key, int flag);  // 0x004303E0
void __cdecl Merge(void* vec, unsigned a, unsigned b, int c, void* d, int e);  // 0x00755810
struct HolderVec {
    uint32_t d[3];
    void push_back(PartHolder** p);   // 0x0041EF20
};
struct KeyVec {
    Key** mpBegin;
    Key** mpEnd;
    Key** mpCap;
    Alloc mAlloc;
    KeyVec() : mpBegin(0), mpEnd(0), mpCap(0) {}
    KeyVec(const AllocTag& t) : mpBegin(0), mpEnd(0), mpCap(0), mAlloc(t) {
        {
            uint32_t dead[3];
        }
    }
    ~KeyVec();                         // 0x0041EB80
    void reserve(unsigned n);          // 0x004E0880
    void push_back(Key** p);           // 0x0041EF20
};
template <class T> struct HolderPtr {
    T* mp;
    HolderPtr(T* p) : mp(p) {
        if (mp)
            mp->AddRef();
    }
    ~HolderPtr() {
        if (mp)
            mp->Release();
    }
};
template <class T> struct IntrusivePtr {
    T* mp;
    IntrusivePtr& operator=(T* p) {
        if (p != mp) {
            T* old = mp;
            {
                uint32_t dead[2];
            }
            if (p)
                ++p->mRefCount;
            mp = p;
            if (old)
                old->Release();
        }
        return *this;
    }
};
struct EditorPartList {
    uint32_t pad0[0x74 / 4];
    Source* mpSource;                  // +0x074
    Source* GetSource() {
        {
            uint32_t dead[3];
        }
        return mpSource;
    }
    Source* GetSourcePlain() { return mpSource; }
    Source* GetSourceWide() {
        {
            uint32_t dead[4];
        }
        return mpSource;
    }
    uint32_t pad1[(0x238 - 0x78) / 4];
    uint16_t mFlags;                   // +0x238
    uint16_t pad2;
    uint32_t pad3[(0x24C - 0x23C) / 4];
    PropList* mpProps;                 // +0x24C
    uint32_t pad4[(0x338 - 0x250) / 4];
    PtrVec<Key> mKeys;                 // +0x338
    uint32_t pad5[(0x34C - 0x344) / 4];
    HolderVec mHolders;                // +0x34C
    uint32_t pad6[(0x360 - 0x358) / 4];
    unsigned char* mpEnabled;          // +0x360
    uint32_t pad7[(0x374 - 0x364) / 4];
    PartXform38* mpXf38;               // +0x374
    uint32_t pad8[(0x388 - 0x378) / 4];
    PartTransform* mpXf7C;             // +0x388
    uint32_t pad9[(0x3F0 - 0x38C) / 4];
    IntrusivePtr<Counted> mpCached;    // +0x3F0
    uint32_t pad10;
    int mStart;                        // +0x3F8
    int mCount;                        // +0x3FC

    PartTransform* At7c(int i) { return &mpXf7C[i]; }
    PartXform38* At38(int i) {
        PartXform38* p = &mpXf38[i];
        return p;
    }
    __forceinline void ReadFlag(bool& out) {
        uint32_t dead[16];
        PropList* props = mpProps;
        if (props) {
            PropValue* value;
            if (props->Find(0x521FC0E, &value) && value->mType == 1)
                out = *value->GetBool();
        }
        {
            uint32_t dead2[1];
        }
    }
    bool ProcessBatch();               // 0x0040EB70
    bool Rescan();                     // 0x0040F110
};
// ---- items of slice s0040eb70 end

// ---- items of slice s004124b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t g_ResourceGroup;
struct Tag { Tag() {} };
struct Entry { uint32_t key; int count; int offset; };
struct IRefCounted_s0041_24b0;
struct RefSlot { IRefCounted_s0041_24b0* p; IRefCounted_s0041_24b0** Out(); };
struct IRefCounted_s0041_24b0 {
    virtual void Unused0() {}
    virtual void Release() {}
};
struct IResourceManager_s0041_24b0 {
    virtual void v00() {} virtual void v01() {} virtual void v02() {} virtual void v03() {}
    virtual void v04() {} virtual void v05() {} virtual void v06() {} virtual void v07() {}
    virtual void v08() {} virtual void v09() {} virtual void v0a() {}
    virtual bool GetResource(uint32_t key, uint32_t group, IRefCounted_s0041_24b0** out);       // +0x2c
    virtual void v0c() {} virtual void v0d() {} virtual void v0e() {} virtual void v0f() {}
    virtual void v10() {} virtual void v11() {}     virtual void GetKeys(uint32_t group, struct KeyVector_s0041_24b0* out);                      // +0x48
};
struct KeyVector_s0041_24b0 {
    uint32_t* begin; uint32_t* end; uint32_t* cap; uint32_t alloc;
    KeyVector_s0041_24b0(const Tag&);
    uint32_t& operator[](int i) { return begin[i]; }
    int size() { return end - begin; }
    void Destroy();
};
struct EntryVector { Entry* begin; Entry* end; void Destroy(Entry* b, Entry* e); void clear() { Destroy(begin, end); } };
struct IntVector {
    int* begin; int* end;
    void Clear(int* b, int* e);
    void clear() { Clear(begin, end); }
    int size() { return end - begin; }
    void Insert(int* where, void* first, void* last, Tag tag);
    void append(void* first, void* last) { Insert(end, first, last, Tag()); }
};
struct Owner {
    char pad[0x90];
    EntryVector entries;   // 0x90
    uint32_t pad2[3];
    IntVector offsets;     // 0xa4
    void GrowEntries();    // FUN_0041ffc0
    void Rebuild();
};
IResourceManager_s0041_24b0* GetResourceManager_s0041_24b0();
struct IntVector;
void* GetCompareFn();
void SortEntriesImpl(Entry* b, Entry* e, void* cmp, Tag tag);
inline void SortEntries_s0041_24b0(Entry* b, Entry* e) { SortEntriesImpl(b, e, GetCompareFn(), Tag()); }
bool GetArrayProp(IRefCounted_s0041_24b0* o, uint32_t id, int* count, Entry** data);
bool GetArrayPropB(IRefCounted_s0041_24b0* o, uint32_t id, int* count, int** data);
bool GetArrayPropC(IRefCounted_s0041_24b0* o, uint32_t id, int* count, void** data);
// ---- items of slice s004124b0 end

// ---- items of slice s00413cc0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(_InterlockedIncrement)
struct Vector3_s0041_3cc0 {
    float x, y, z;
    Vector3_s0041_3cc0() {}
    Vector3_s0041_3cc0(const Vector3_s0041_3cc0& o) : x(o.x), y(o.y), z(o.z) {}
    Vector3_s0041_3cc0& operator=(const Vector3_s0041_3cc0& o) { x = o.x; y = o.y; z = o.z; return *this; }
    float& operator[](int i) { return (&x)[i]; }
};
Vector3_s0041_3cc0* CrossLike(Vector3_s0041_3cc0* out, const void* a, const void* b);   // 0x0041db10
void    ScaleInPlace(Vector3_s0041_3cc0* v, const Vector3_s0041_3cc0* s);         // 0x0041dba0
Vector3_s0041_3cc0* Combine(Vector3_s0041_3cc0* out, const void* a, const Vector3_s0041_3cc0* v);  // 0x0041dc10
template <typename T>
inline const T& min_ref(const T& a, const T& b) { return (a > b) ? b : a; }
namespace Resource_s0041_3cc0 {
struct ThreadedObject_s0041_3cc0 {
    void* vtable;
    long mnRefCount;
    int AddRef() { uint32_t unused0, unused1, unused2; return _InterlockedIncrement(&mnRefCount); }
    int Release();                                  // 0x00404f90
};
}
struct LoadHandle_s0041_3cc0 {
    int AddRef();                                   // 0x0068f950
    int Release();                                  // 0x00690120
    void Cancel();                                  // 0x006926b0
    void Attach(void* owner);                       // 0x004227d0
    uint32_t pad[6];
    uint32_t mFlags;                                // +0x18
    void SetFlags(uint32_t f) { mFlags = f; }
};
template <class T> struct intrusive_ptr_s0041_3cc0 {
    T* mpObject;
    intrusive_ptr_s0041_3cc0() : mpObject(0) {}
    ~intrusive_ptr_s0041_3cc0() { if (mpObject) mpObject->Release(); }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
    T* get() const { return mpObject; }
    T* detach() { T* p = mpObject; mpObject = 0; return p; }
    intrusive_ptr_s0041_3cc0& operator=(const intrusive_ptr_s0041_3cc0& ip) { return operator=(ip.mpObject); }
    T** operator&() {
        if (mpObject) {
            T* p = mpObject;
            mpObject = 0;
            p->Release();
        }
        return &mpObject;
    }
    intrusive_ptr_s0041_3cc0& operator=(T* pObject) {
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
};
struct PointArray {
    Vector3_s0041_3cc0 v[3];
    Vector3_s0041_3cc0& operator[](int i) { return v[i]; }
};
struct ClipEntry {                                  // 0x8c
    int16_t mId;                                    // +0x00
    int16_t mParent;                                // +0x02
    int16_t mLink;                                  // +0x04
    uint16_t pad06;
    uint16_t mFlags;                                // +0x08
    uint8_t padA;
    uint8_t mType;                                  // +0x0b
    uint32_t pad0C[(0x2c - 0x0c) / 4];
    float mTime;                                    // +0x2c
    PointArray mPos;                                // +0x30
    Vector3_s0041_3cc0 mDir;                                   // +0x54
    uint32_t pad60[(0x8c - 0x60) / 4];
};
struct ClipEntryList {                              // begin/end of 0x8c-byte entries
    ClipEntry* mpBegin;
    ClipEntry* mpEnd;
    int size() const { return (int)(mpEnd - mpBegin); }
};
struct ClipModel {
    uint32_t pad[0x98 / 4];
    ClipEntryList mEntries;                         // +0x98
};
struct ClipNode {
    bool Test(float t);                             // 0x004f96a0
    void Finish(int flag);                          // 0x004fc320
};
struct ClipSkin {
    void Reset();                                   // 0x00508400
};
struct Clip : Resource_s0041_3cc0::ThreadedObject_s0041_3cc0 {
    intrusive_ptr_s0041_3cc0<ClipModel> mpModel;               // +0x08
    uint32_t pad0C[(0x34 - 0x0c) / 4];
    intrusive_ptr_s0041_3cc0<ClipSkin> mpSkin;                 // +0x34
    intrusive_ptr_s0041_3cc0<ClipNode> mpNode;                 // +0x38
    float mTime;                                    // +0x3c
};
Vector3_s0041_3cc0 SamplePosition(const Vector3_s0041_3cc0* a, const Vector3_s0041_3cc0* b, float t);   // 0x004a5c70
float   SampleScale(float t);                                          // 0x004a5c00
struct IFactory_s0041_3cc0 {
virtual void v0();
virtual void v4();
virtual void v8();
virtual void vc();
    virtual void Create(LoadHandle_s0041_3cc0** out);
    static IFactory_s0041_3cc0* Get();                         // 0x0068f4d0
};
struct IntVector_s0041_3cc0 {
    int* mpBegin;
    int* mpEnd;
    int* mpCapacity;
    IntVector_s0041_3cc0(int n, int value);                    // 0x00422740
    ~IntVector_s0041_3cc0() { for (int* p = mpBegin; p < mpEnd; ++p) {} Free(); }
    void Free();                                    // 0x004c0b80
    int& operator[](int i) { return mpBegin[i]; }
};
struct Mixer {
    void Reset();                                   // 0x004fd520
    int AddKey(Vector3_s0041_3cc0* pos, float a, float b, int id);                  // 0x004fcc20
    void Link(int from, int to, float w, uint32_t flags);                // 0x004fcca0
    void SetRoot(ClipNode* node);                   // 0x004fd380
};
struct Solver {
    uint32_t pad[0x1c / 4];
    uint32_t mField1C;                              // +0x1c
    bool Run(ClipNode* a, ClipSkin* b, float t);          // 0x005400a0
    bool Apply(bool flag);                          // 0x0053eda0
    void Finish();                                  // 0x00540210
};
class ClipPlayer {
public:
    bool BuildBlend(Clip* src);               // 0x00413de0
    bool Advance(Clip* t, float time, bool flag);   // 0x004142e0
    void Rewind(int unused);                        // 0x004143e0
    bool Step(Clip* t, float time);           // 0x00414420
    bool Start(Clip* clip, float time, LoadHandle_s0041_3cc0** out);   // 0x00414470
    int  BuildChain(ClipEntry* e, int count, int i, int prev, int id, int link, int h);   // 0x00412900

    uint32_t pad00[0x80 / 4];
    intrusive_ptr_s0041_3cc0<LoadHandle_s0041_3cc0> mpHandle;             // +0x80
    intrusive_ptr_s0041_3cc0<Clip> mpCurrent; // +0x84
    intrusive_ptr_s0041_3cc0<Mixer> mpMixer;                   // +0x88
    intrusive_ptr_s0041_3cc0<Solver> mpSolver;                 // +0x8c
};
// ---- items of slice s00413cc0 end

// ---- items of slice s004145c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern unsigned int g_015d13e8;
struct DefaultRefCounted_s0041_45c0 {
    void* vtable;
    int mnRefCount;
    int AddRef() { return mnRefCount++ + 1; }
    int Release();
};
struct ThreadedObject_s0041_45c0 {
    void* vtable;
    volatile long mnRefCount;
    void AddRef() { _InterlockedIncrement(&mnRefCount); }
    void Release();
};
struct IRefCounted_s0041_45c0 {
    virtual int AddRef() = 0;
    virtual int Release() = 0;
};
struct ResourceKey_s0041_45c0 {
    unsigned int instanceID, typeID, groupID;
    ResourceKey_s0041_45c0();
};
struct ExtraInfo { int a; unsigned short flags; unsigned short pad; };   // 8 bytes; low flag bits tested below
struct Property_s0041_45c0 {
    char pad0[0x12]; unsigned short type;
    int* GetInt();  // 0x0041e990 (Property::GetInt)
    bool* GetBool();
};
struct IPropList_s0041_45c0 : IRefCounted_s0041_45c0 {
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
    virtual bool GetProperty(unsigned int id, Property_s0041_45c0** pp);
};
struct IPropManager_s0041_45c0 {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
    virtual void v28();
    virtual bool GetPropertyList(unsigned int a, unsigned int b, IPropList_s0041_45c0** pp);
};
IPropManager_s0041_45c0* PropManager_s0041_45c0();
template <class T> struct ip {
    T* p;
    ip() : p(0) {}
    ip(T* o) : p(o) { if (p) p->AddRef(); }
    ~ip() { if (p) p->Release(); }
    void assign(T* o) { T* const pTemp = p; int d1, d2, d3; if (o) o->AddRef(); p = o; if (pTemp) pTemp->Release(); }
    ip& operator=(T* o) { if (o != p) { T* const pTemp = p; int d1, d2, d3; if (o) o->AddRef(); p = o; if (pTemp) pTemp->Release(); } return *this; }
    T* get() const { return p; }
    T* operator->() const { return p; }
    T** AsOutParam() { if (p) { T* t = p; p = 0; t->Release(); } return &p; }
    ip& ReleaseRef();   // out of line
    __forceinline void reset() { if (p) assign(0); }
    T** AsOutParamX() { return &ReleaseRef().p; }
};
template <class T> struct tip {
    T* p;
    tip& operator=(T* o) { if (o != p) { T* const pTemp = p; if (o) o->AddRef(); p = o; if (pTemp) pTemp->Release(); } return *this; }
};
struct ItemBase : DefaultRefCounted_s0041_45c0 { unsigned pad[(0x6b-8)/4]; char p1[3]; bool f6b; bool f6c; };
typedef ItemBase Item_s0041_45c0;
struct V3 { int x, y, z; };
struct DefTail {              // Def + 0x18
    int nameHash; int x1c;
    int ids[3];               // 0x20
    int ids2[3];              // 0x2c
    V3 pos[3];                // 0x38
};
struct Def {
    void* vt; int rc;
    ResourceKey_s0041_45c0 key;       // 8
    int x14;
    DefTail tail;          // 0x18
};
struct DefRef : ThreadedObject_s0041_45c0 {
    Def* pDef;             // 8
    Def* GetDef() const { return pDef; }
};
struct Entry_s0041_45c0 : DefaultRefCounted_s0041_45c0 {   // 0x84 bytes
    tip<ThreadedObject_s0041_45c0> owner;   // 8
    ResourceKey_s0041_45c0 key;            // 0xc
    int ids[4];                 // 0x18
    int ids2[3];                // 0x28
    int pad34;
    V3 pos[3];                  // 0x38
    int flags;                  // 0x5c
    int priority;               // 0x60
    bool b64, b65, b66, b67, b68, b69, b6a, b6b;
    unsigned pad6c[(0x84 - 0x6c) / 4];
    Entry_s0041_45c0();
};
unsigned int SetKeyType(ResourceKey_s0041_45c0* k, int a, int b);         // 0x68c6d0
unsigned int HashName(int v);                                  // 0x4bb860
unsigned int ResolveName(int v);                               // 0x432f10
bool GetArrayImpl(IPropList_s0041_45c0* l, unsigned int id, int* count, int** arr);   // 0x6a0840
struct SlotTail { int a; int b; ip<IRefCounted_s0041_45c0> cb; SlotTail(ip<Entry_s0041_45c0>* pe); };
struct Slot_s0041_45c0 {  // 0x24 bytes
    ResourceKey_s0041_45c0 key; ExtraInfo extra; int pad; SlotTail tail;
    int pad2[3];
    Slot_s0041_45c0(ip<Entry_s0041_45c0>* pe) : tail(pe) { int u0, u1, u2, u3, u4, u5, u6, u7, u8, u9, u10, u11; }
    ~Slot_s0041_45c0();
};
struct Container { void Add(Slot_s0041_45c0* s, int); };  // 0x4204f0
inline void GetIntProp_s0041_45c0(IPropList_s0041_45c0* l, unsigned int id, int& out) {
    Property_s0041_45c0* p;
    if (l && l->GetProperty(id, &p) && p->type == 9) out = *p->GetInt();
}
inline void GetBoolProp_s0041_45c0(IPropList_s0041_45c0* l, unsigned int id, bool& out) {
    Property_s0041_45c0* p;
    if (l && l->GetProperty(id, &p) && p->type == 1) out = *p->GetBool();
}
struct GroupBits_s0041_45c0 { unsigned int raw; unsigned int Type() const { return (raw >> 16) & 0xff; } GroupBits_s0041_45c0(unsigned int v) : raw(v) {} };
struct PropArray { int* data; int count; unsigned int id; PropArray() : count(0), id(0x5e68c2e) {} };
struct PaletteEditor {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
    virtual bool TestPlacement(V3* pos, int a);
    virtual void v48();
    virtual void ApplyPlacement(V3* pos, ExtraInfo* extra);
    void Refresh(int);   // 0x00411890
    unsigned pad0[(0xbc-4)/4];
    ip<Item_s0041_45c0> m_item;               // 0xbc
    unsigned pad4[2];
    Container m_container;         // 0xc8
    char pad5[3];
    unsigned pad1[(0x228-0xcc)/4];
    V3 m_pos;                      // 0x228
    ExtraInfo m_pair; unsigned padx;
    ip<Item_s0041_45c0> m_cur;
    unsigned pad2[(0x258-0x244)/4];
    bool m_dirty; bool m_b259;
    unsigned pad3[(0x2c4-0x25c)/4];
    bool m_b2c4;
    bool SetItem(Item_s0041_45c0* n);
    bool AddEntry(DefRef* src, ExtraInfo* extra, IRefCounted_s0041_45c0* cb);
};
struct EditorObject {
    unsigned pad[0x78 / 4];
    int m_field78;
    int GetField78();
    int Field78() const { return m_field78; }
};
// ---- items of slice s004145c0 end

// ---- items of slice s00414e30 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3_s0041_4e30 {
    float x, y, z;
    float& operator[](int i) { return (&x)[i]; }
};
struct Vector3Init : Vector3_s0041_4e30 {
    Vector3Init(float ax, float ay, float az) { x = ax; y = ay; z = az; }
};
struct Cell { uint8_t b[3]; };
struct BoundsHeader {
    Vector3_s0041_4e30 minv;         // +0x00
    Vector3_s0041_4e30 maxv;         // +0x0C
    float   cell;         // +0x18  quantization step
    uint8_t dims[8];      // +0x1C  subdivision count per level (0 terminates)
    Cell    cells[1];     // +0x24
};
struct IntPair {
    int first, second;
};
struct Range_s0041_4e30 : IntPair {
    Range_s0041_4e30() { first = 0; second = 0; }
    Range_s0041_4e30& operator=(const IntPair& p) { first = p.first; second = p.second; return *this; }
};
Vector3_s0041_4e30* Lerp(Vector3_s0041_4e30* out, Vector3_s0041_4e30& a, Vector3_s0041_4e30& b, float t);
struct BoundsSampler {
    BoundsHeader* data;       // +0x00
    int           levels;     // +0x04
    Range_s0041_4e30         range[8];   // +0x08
    float         weight[8];  // +0x48
    unsigned int  total;      // +0x68

    IntPair* CellRange(IntPair* out, int axis, int stride, float t, float* frac);
    void     Collect(unsigned int cell, int level, Vector3_s0041_4e30* mn, Vector3_s0041_4e30* mx);
    void     CellBounds(unsigned int cell, Vector3_s0041_4e30& mn, Vector3_s0041_4e30& mx);
    void     Init(BoundsHeader* hdr, float* weights, int nWeights, Vector3_s0041_4e30* mn, Vector3_s0041_4e30* mx);
};
inline float Clamp01(float v, float lo, float hi)
{
    v = (lo > v) ? lo : v;
    v = (v < hi) ? v : hi;
    return v;
}
struct BoundsNode {          // hash node: key at +0, value at +8
    BoundsNode*   next;      // (layout of the first words is not exercised here)
    uint32_t      keyPad;
    BoundsHeader* value;
};
struct BoundsIter { BoundsNode* node; BoundsNode** bucket; };
struct BoundsTable {         // lives at BoundsLibrary+0x30
    uint32_t       pad0;
    BoundsNode**   buckets;  // +0x04
    unsigned int   bucketCount;  // +0x08
    // 0x0041FB20: find(out iterator, key)
    BoundsIter* Find(BoundsIter* out, const uint64_t* key);

    BoundsIter End() {
        BoundsIter it;
        it.bucket = buckets + bucketCount;
        it.node = *it.bucket;
        return it;
    }
};
inline bool operator!=(const BoundsIter& a, const BoundsIter& b) { return a.node != b.node; }
struct BoundsLibrary {
    uint32_t    pad[12];     // +0x00
    BoundsTable table;       // +0x30

    bool Query(unsigned int idLo, unsigned int idHi, float* weights, int nWeights, Vector3_s0041_4e30* mn, Vector3_s0041_4e30* mx);
};
struct ResourceKey_s0041_4e30 {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
    ResourceKey_s0041_4e30() : instanceID(0), typeID(0), groupID(0) {}
};
struct RefCounted_s0041_4e30 {
    virtual int AddRef();
    virtual int Release();
};
template <class T>
struct intrusive_ptr_s0041_4e30 {
    T* mpObject;
    T* get() const { return mpObject; }
    T** AsPointer() {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
        return &mpObject;
    }
};
struct PropertyList_s0041_4e30 : RefCounted_s0041_4e30 {};
typedef intrusive_ptr_s0041_4e30<PropertyList_s0041_4e30> PropertyListPtr_s0041_4e30;
struct PropManager_s0041_4e30 {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool GetPropertyList(unsigned int instanceID, unsigned int groupID, PropertyList_s0041_4e30** dst);  // +0x2C
};
PropManager_s0041_4e30* GetPropManager();  // 0x0067DE30
struct PropertyListMap {
    // 0x0041CD60: operator[](key) -> slot
    PropertyListPtr_s0041_4e30* Slot(const uint64_t* key);
};
struct PropertyListCache {
    uint32_t        pad[4];
    PropertyListMap map;     // +0x10

    PropertyList_s0041_4e30* Get(unsigned int instanceID, unsigned int groupID);
};
bool GetKeyValue(PropertyList_s0041_4e30* pList, unsigned int propertyID, ResourceKey_s0041_4e30* dst);
void ConvertKeyType(ResourceKey_s0041_4e30* key, unsigned int typeID, int flags);
struct ResourceManager_s0041_4e30 {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3C();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4C();
    virtual void v50(); virtual void v54();
    virtual int ResourceExists(ResourceKey_s0041_4e30* key);  // +0x58
};
ResourceManager_s0041_4e30* GetResourceManager_s0041_4e30();  // 0x0067DCD0
struct ConfigManager_s0041_4e30 {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3C();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4C();
    virtual void v50(); virtual void v54();
    virtual PropertyList_s0041_4e30* FindPropertyList(unsigned int instanceID, unsigned int groupID);  // +0x58

    bool FindModelKey(unsigned int instanceID, unsigned int groupID, ResourceKey_s0041_4e30* dst);
};
// ---- items of slice s00414e30 end

// ---- items of slice s00416180 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct GroupBits { uint32_t lo : 16; uint32_t tag : 8; uint32_t flags : 5; uint32_t hi : 3; };
struct ResourceKey_s0041_6180 {
    uint32_t instance, type;
    union { uint32_t group; GroupBits bits; };
};
void __cdecl ResourceKey_SetFlags(ResourceKey_s0041_6180* k, int flags);   // 0x0068c700
inline uint32_t BitsTag(uint32_t v) { uint32_t r = v; return (r >> 16) & 0xff; }
inline uint32_t BitsClearFlags(uint32_t v, uint32_t n) { ((GroupBits*)&v)->flags = n; return v; }
struct Entry_s0041_6180 {
    ResourceKey_s0041_6180 key;
    int id;
    inline bool KeyEquals(const ResourceKey_s0041_6180& o) const
    {
        return key.instance == o.instance && key.type == o.type && key.group == o.group;
    }
};
struct IterSub {
    int w[4];
    IterSub() {}
    IterSub(const IterSub& o);   // 0x00420050
    Entry_s0041_6180* __fastcall Deref();   // 0x005658b0 (ecx = &sub)
    inline bool operator==(const IterSub& o) const { return w[0] == o.w[0]; }
};
struct Iter {
    int cur;
    IterSub sub;
    int f5, f6;
    Iter() {}
    Iter(const Iter& o) : cur(o.cur), sub(o.sub), f5(o.f5), f6(o.f6) {}
    bool operator==(const Iter& o) const
    {
        return cur == o.cur && (cur == f6 || sub == o.sub);
    }
    inline bool operator!=(const Iter& o) const { return !(*this == o); }
    inline Entry_s0041_6180* operator->() { return sub.Deref(); }
    Iter& Next();                // 0x00421f00
};
struct EntryList {
    int pad[1];
    Iter* Begin(Iter* out);          // 0x00420200
    Iter* End(Iter* out);            // 0x00420350
    Iter Erase(Iter it);             // 0x00420390
};
struct Message {
    Message(int type);               // 0x00423110
    virtual void vf0();
    int pad[13];
};
struct EditorMessage : Message {
    int unk38;
    int pad3c;
    static inline void* operator new(unsigned sz, const char* name, int a, int b, int c, int d)
    {
        return EASTL_allocator_allocate(sz, name, a, b, c, d);
    }
    EditorMessage(int type) : Message(type) { unk38 = 0; }
    virtual void vf0();
    inline void SetField(unsigned i, int v) { *(int*)((char*)this + i * 8 + 8) = v; }
};
struct Dispatcher_s0041_6180 {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual void v3(); virtual void v4(); virtual void v5();
    virtual void Post(int type, Message* msg, int a, int b);
};
Dispatcher_s0041_6180* GetDispatcher();                                    // 0x0067dcc0
struct Manager { void __thiscall Method(void* p); };           // 0x00522a40
Manager* GetManager();                                          // 0x00401080
struct EditorPanel {
    char pad0[0xc8];
    EntryList entries;          // 0xc8
    char pad1[0x228 - 0xc8 - 4];
    ResourceKey_s0041_6180 activeKey;      // 0x228
    int activeId;               // 0x234
    char pad2[0x240 - 0x238];
    void* target;               // 0x240
    char pad3[0x259 - 0x244];
    bool flagA;                 // 0x259
    char pad4[0x2c4 - 0x25a];
    bool flagB;                 // 0x2c4

    inline void* GetTarget() { return target; }
    bool HasHandler(ResourceKey_s0041_6180* k, int id);
    bool HasId(int id);
    bool HasHandlerNormalized(ResourceKey_s0041_6180* k);
    bool Activate(ResourceKey_s0041_6180* k, int id);
    void __thiscall CommitAndReset(int a);   // 0x00411890
};
// ---- items of slice s00416180 end

// ---- items of slice s00416990 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct ResourceKey_s0041_6990 { uint32_t instance, type, group; };
struct Payload { int id, extra; };
struct Entry_s0041_6990 {
    ResourceKey_s0041_6990 key;
    union { Payload val; struct { int id, extra; }; };
    Entry_s0041_6990() {}
    Entry_s0041_6990(const ResourceKey_s0041_6990& k, const Payload& p) : key(k), val(p) {}
    inline bool KeyEquals(const ResourceKey_s0041_6990& o) const
    {
        return key.instance == o.instance && key.type == o.type && key.group == o.group;
    }
};
struct IterSub_s0041_6990 {
    int w[4];
    IterSub_s0041_6990() {}
    IterSub_s0041_6990(const IterSub_s0041_6990& o);   // 0x00420050
    Entry_s0041_6990* __fastcall Deref();   // 0x005658b0 (ecx = &sub)
    inline bool operator==(const IterSub_s0041_6990& o) const { return w[0] == o.w[0]; }
};
struct Iter_s0041_6990 {
    int cur;
    IterSub_s0041_6990 sub;
    int f5, f6;
    Iter_s0041_6990() {}
    Iter_s0041_6990(const Iter_s0041_6990& o) : cur(o.cur), sub(o.sub), f5(o.f5), f6(o.f6) {}
    bool operator==(const Iter_s0041_6990& o) const
    {
        return cur == o.cur && (cur == f6 || sub == o.sub);
    }
    inline bool operator!=(const Iter_s0041_6990& o) const { return !(*this == o); }
    inline Entry_s0041_6990* operator->() { return sub.Deref(); }
    Iter_s0041_6990& Next();                // 0x00421f00
};
struct EntryList_s0041_6990 {
    int pad[1];
    Iter_s0041_6990* Begin(Iter_s0041_6990* out);            // 0x00420200
    Iter_s0041_6990* End(Iter_s0041_6990* out);              // 0x00420350
    Iter_s0041_6990* BeginC(Iter_s0041_6990* out);           // 0x004201a0
    Iter_s0041_6990* EndC(Iter_s0041_6990* out);             // 0x004202f0
    Iter_s0041_6990 EndCV();
    Iter_s0041_6990* Erase(Iter_s0041_6990* out, Iter_s0041_6990 it);   // 0x00420390
    Iter_s0041_6990 ErasePV(Iter_s0041_6990 it);
    int Size();                        // 0x00420480
};
struct EditorMessage_s0041_6990 : Message {
    int unk38;
    int unk3c;
    EditorMessage_s0041_6990(int type) : Message(type) { unk38 = 0; }
    virtual void vf0();
    inline void SetField(unsigned i, int v) { *(int*)((char*)this + i * 8 + 8) = v; }
};
void* __cdecl operator new(unsigned sz, const char* name, int a, int b, int c, int d);  // 0x00f473a0
struct Dispatcher_s0041_6990 {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual void v3(); virtual void v4(); virtual void v5();
    virtual void Post(int type, Message* msg, int a, int b);
};
Dispatcher_s0041_6990* GetDispatcher_s0041_6990();                                    // 0x0067dcc0
struct EntrySink { void __thiscall Add(const Entry_s0041_6990* e); };      // 0x004227f0
struct HIter {
    int* node;
    int** bucket;
    HIter() {}
    HIter(int* n, int** b) : node(n), bucket(b) {}
    inline bool operator!=(const HIter& o) const { return node != o.node; }
};
struct Slot_s0041_6990 {
    int pad0;
    int** buckets;     // +4
    int bucketIdx;     // +8
    char pad1[0x20 - 12];
    void __thiscall Find(HIter* out, const ResourceKey_s0041_6990* key);   // 0x00421950
    inline HIter End()
    {
        int** p = buckets + bucketIdx;
        return HIter(*p, p);
    }
};
struct KeyedEvent { int pad[2]; ResourceKey_s0041_6990 key; };
inline int KeyGroupTag(uint32_t v) { return (v >> 16) & 0xff; }
struct EditorPanel_s0041_6990 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16();
    virtual bool OnActivate(Entry_s0041_6990* e, int id);   // +0x44

    char pad0[0xc0 - 4];
    bool noEntries;             // 0xc0
    char pad0b[3];
    int pressCount;             // 0xc4
    EntryList_s0041_6990 entries;          // 0xc8
    char pad1[0x228 - 0xc8 - 4];
    Entry_s0041_6990 active;               // 0x228 (key 0x228, id 0x234, extra 0x238)
    char pad2[0x259 - 0x23c];
    bool flagA;                 // 0x259
    char pad4[0x2c4 - 0x25a];
    bool flagB;                 // 0x2c4
    char pad5[0x1184 - 0x2c5];
    Slot_s0041_6990 slots[6];              // 0x1184

    bool ActivateById(int id);
    bool ActivateByKey(ResourceKey_s0041_6990* k);
    void AdjustPressCount(bool release);
    int CountPending();
    int CountWithId(int id);
    bool GetActiveKey(ResourceKey_s0041_6990* out);
    void CollectAll(EntrySink* out);
    float GetSlotValue(KeyedEvent* ev);
};
// ---- items of slice s00416990 end

// ---- items of slice s00417600 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern wchar_t gEmptyWString[];                              // 0x01667bac
template <class T> struct intrusive_ptr_s0041_7600 {
    T* mpObject;
    intrusive_ptr_s0041_7600() : mpObject(0) {}
    ~intrusive_ptr_s0041_7600() { if (mpObject) mpObject->Release(); }
    T* operator->() const { return mpObject; }
    T* get() const { return mpObject; }
    T* Ptr() const { T* p = mpObject; return p; }
    void Reset() {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
    }
    intrusive_ptr_s0041_7600& operator=(T* pObject) {
        T* const pTemp = mpObject;
        if (pObject) pObject->AddRef();
        mpObject = pObject;
        if (pTemp) pTemp->Release();
        return *this;
    }
    T** GetAddress();   // 0x0041d870 (releases, returns out-param slot)
    T** AsOutParam() { return GetAddress(); }
};
struct ResourceKey_s0041_7600 {
    uint32_t instance, type, group;
    uint32_t GetGroup() const { return group; }
};
inline uint32_t KeyGroupTag_s0041_7600(uint32_t v) { uint32_t r = v; return (r >> 16) & 0xff; }
inline uint32_t KeyFlags_s0041_7600(uint32_t v) { uint32_t r = v; return (r >> 24) & 0x1f; }
inline uint32_t KeyWithFlags(uint32_t v, uint32_t n) { ((GroupBits*)&v)->flags = n; return v; }
struct Variant {
    uint32_t data[4];
    uint16_t flags;
    uint16_t type;
    Variant(const bool& b) : flags(0), type(0) {
        type = 1;
        flags = 2;
        Store((bool*)&b);
    }
    void Store(bool* p);        // 0x00422e20
    void Free(int a);           // 0x0093db80
    ~Variant() { if (flags & 4) Free(0); }
};
struct IResource : IRefCounted {
    virtual void v2(); virtual void v3(); virtual void v4();
    virtual void SetProperty(uint32_t id, const Variant& v);      // +0x14
};
void MarkUsed(IResource* r, int flag);                       // 0x006b2090
struct IResourceManager_s0041_7600 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10();
    virtual bool Load(uint32_t instance, uint32_t group, IResource** out);   // +0x2c
};
IResourceManager_s0041_7600* GetResourceManager_s0041_7600();                      // 0x0067de30
template <> IResource** intrusive_ptr_s0041_7600<IResource>::GetAddress();
struct WString {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    WString() : mpBegin(0), mpEnd(0), mpCapacity(0)
    {
        mpBegin = gEmptyWString;
        mpEnd = mpBegin;
        mpCapacity = mpBegin + 1;
    }
    int rfind(const wchar_t* s, int pos, int n) const;       // 0x00423700
    int rfind(wchar_t c, int pos) const;                     // 0x0041dfc0
    void erase(int pos, int n);                              // 0x004228e0
    ~WString();                                              // 0x004237d0
};
struct IWindow {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12();
    virtual bool Contains(ResourceKey_s0041_7600* key, int a, int b, int c, int d, int e);   // +0x34
};
void SyncState();                                            // 0x006b4840
void* LookupName(uint32_t nameAddr);                         // 0x006b1f90
IWindow* FindWindow(void* name);                             // 0x00422950
struct HitEntry { uint32_t a, b, c; };
template <class T> struct vector_s0041_7600 {
    T* mpBegin; T* mpEnd; T* mpCapacity;
    void Free();                                             // 0x005156b0
};
struct QueryBase {
    uint32_t instance, group, a, b;
    __forceinline QueryBase() : instance(-1), group(-1), a(-1), b(-1) {}
    __forceinline virtual ~QueryBase() {}
};
struct Query_s0041_7600 : QueryBase {
    vector_s0041_7600<HitEntry> list;
    __forceinline Query_s0041_7600() { list.mpBegin = 0; list.mpEnd = 0; list.mpCapacity = 0; }
    __forceinline virtual ~Query_s0041_7600() {
        for (HitEntry* p = list.mpBegin; p < list.mpEnd; ++p) {}
        list.Free();
    }
};
struct IEditorServices {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual bool Lookup(ResourceKey_s0041_7600* key, IRefCounted** out, int, int, int, int);                 // +0x0c
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void Register(IRefCounted* listener, int, IWindow* win, int, ResourceKey_s0041_7600* key);       // +0x20
    virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12();
    virtual void v13(); virtual void Collect(vector_s0041_7600<HitEntry>* out, Query_s0041_7600* q, int a);             // +0x38
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
    virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
    virtual void v30();
    virtual void GetPath(ResourceKey_s0041_7600* key, WString* out);                                         // +0x7c
    virtual void SetExt(ResourceKey_s0041_7600* key, const wchar_t* ext);                                    // +0x80
};
IEditorServices* GetServices();                              // 0x0067dcd0
void BuildKey(ResourceKey_s0041_7600* key, WString* ext, const wchar_t* path);   // 0x0068d0d0
struct Panel {
    void Apply(ResourceKey_s0041_7600* key, bool flag, void* extra);
};
void Process(vector_s0041_7600<HitEntry>* list, void* extra, const wchar_t* name, IWindow* a, IWindow* b, bool flag);   // 0x00417210
struct EditorBlockData_s0041_7600 {
    EditorBlockData_s0041_7600() throw();      // 0x00403240
    char* GetSlotArea();
    uint32_t pad[0x1100 / 4];
    char slotArea[0x148];
};
// ---- items of slice s00417600 end

// ---- items of slice s00417d60 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kZero;
extern uint16_t gEmptyString;
struct PhantomTemps { PhantomTemps() {} uint32_t pad[16]; };
class RefCounted_s0041_7d60 {
public:
    virtual int AddRef();
    virtual int Release();
};
template <class T> class intrusive_ptr_s0041_7d60 {
public:
    intrusive_ptr_s0041_7d60() : mpObject(0) {}
    intrusive_ptr_s0041_7d60(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~intrusive_ptr_s0041_7d60() { if (mpObject) mpObject->Release(); }
    T* get() const { return mpObject; }
    void Reset()
    {
        if (mpObject) { T* pOld = mpObject; mpObject = 0; pOld->Release(); }
    }
    T* mpObject;
};
template <class T> class owned_ptr {
public:
    owned_ptr() : mpValue(0) {}
    ~owned_ptr() { if (mpValue) mpValue->Destroy(); }
    T* mpValue;
};
template <int ID> struct Owned { void Destroy(); };
struct DefaultRefCounted_s0041_7d60 { void Release(); };
struct RcObject { int vptrPad; DefaultRefCounted_s0041_7d60 rc; };
class rc_ptr {
public:
    rc_ptr() : mpObject(0) {}
    ~rc_ptr() { if (mpObject) mpObject->rc.Release(); }
    RcObject* mpObject;
};
struct Alloc8 {
    Alloc8(const AllocTag&);
    uint32_t pad[2];
};
template <int ID> struct Init20 {
    Init20(const AllocTag& a = AllocTag()) { Init(a); }
    void Init(const AllocTag&);
    ~Init20();
    uint32_t pad[5];
};
template <int ID> struct Vec20 {
    Vec20(const AllocTag& a = AllocTag()) : mpBegin(0), mpEnd(0), mpCap(0), mAlloc(a) {}
    ~Vec20();
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCap;
    Alloc8 mAlloc;
};
template <int ELEM, int ID, int SIZE> struct RangeVecTag {
    RangeVecTag(const AllocTag& a = AllocTag()) { Init(a); }
    void Init(const AllocTag&);
    void Free();
    ~RangeVecTag()
    {
        for (char* p = (char*)mpBegin; p < (char*)mpEnd; p += ELEM) {}
        Free();
    }
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t pad[(SIZE - 8) / 4];
};
template <int ELEM, int ID, int SIZE> struct RangeVec {
    RangeVec();
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t pad[(SIZE - 8) / 4];
    void Free();
    ~RangeVec()
    {
        for (char* p = (char*)mpBegin; p < (char*)mpEnd; p += ELEM) {}
        Free();
    }
};
template <int ID, int SIZE> struct OutVec {
    OutVec();
    ~OutVec();
    uint32_t pad[SIZE / 4];
};
struct TagMember {
    TagMember(const AllocTag& a = AllocTag());
    ~TagMember();
    uint32_t pad[8];
};
struct SmallString {
    SmallString() : mpBegin(0), mpEnd(0), mpCap(0)
    {
        mpBegin = &gEmptyString;
        mpEnd = mpBegin;
        mpCap = mpBegin + 1;
    }
    ~SmallString();
    uint16_t* mpBegin;
    uint16_t* mpEnd;
    uint16_t* mpCap;
    uint32_t mAlloc;
};
struct PtrTriple {
    PtrTriple() : mpBegin(0), mpEnd(0), mpCap(0) {}
    ~PtrTriple();
    uint32_t mpBegin, mpEnd, mpCap;
    uint32_t pad[2];
};
struct PtrPair {
    PtrPair() : mpBegin(0), mpEnd(0) {}
    uint32_t mpBegin, mpEnd;
};
struct SubState {
    SubState();
    ~SubState();

    uint8_t mFlag;                                   // +0x000
    float mScale;                                    // +0x004
    intrusive_ptr_s0041_7d60<RefCounted_s0041_7d60> mpRef;                 // +0x008
    RangeVec<12, 0, 0xd8> mListA;                    // +0x00c
    RangeVec<0x38, 1, 0x398> mListB;                 // +0x0e4
    RangeVec<12, 0, 0xd8> mListC;                    // +0x47c
    RangeVec<0x38, 1, 0x398> mListD;                 // +0x554
    RangeVec<4, 2, 0x58> mListE;                     // +0x8ec
    int mCount;                                      // +0x944
    float mValueA;                                   // +0x948
    float mValueB;                                   // +0x94c
    int mPad950;                                     // +0x950
    int mFieldA;                                     // +0x954
    int mFieldB;                                     // +0x958
    int mFieldC;                                     // +0x95c
    RangeVec<4, 3, 0x118> mIdsA;                     // +0x960
    OutVec<4, 0x118> mIdsB;                          // +0xa78
    RangeVec<4, 3, 0x118> mIdsC;                     // +0xb90
    TagMember mTable;                                // +0xca8
    uint32_t mPadCC8;                                // +0xcc8 (assigned below)
};
struct ToolState {
    ToolState();
    ~ToolState();

    owned_ptr<Owned<0> > mpOwnedA;                   // +0x000
    rc_ptr mpRc;                                     // +0x004
    Init20<0> mA;                                    // +0x008
    Init20<1> mB;                                    // +0x01c
    Init20<2> mC;                                    // +0x030
    Init20<3> mD;                                    // +0x044
    Vec20<0> mV0;                                    // +0x058
    Vec20<1> mV1;                                    // +0x06c
    RangeVecTag<8, 0, 0x18> mV2;                     // +0x080
    Vec20<2> mV3;                                    // +0x098
    Vec20<3> mV4;                                    // +0x0ac
    owned_ptr<Owned<1> > mpOwnedB;                   // +0x0c0
    owned_ptr<Owned<2> > mpOwnedC;                   // +0x0c4
    int mCountA;                                     // +0x0c8
    int mCapacity;                                   // +0x0cc
    SmallString mName;                               // +0x0d0
    PtrTriple mItems;                                // +0x0e0
    uint8_t mFlagA;                                  // +0x0f4
    uint8_t mFlagB;                                  // +0x0f5
    int mMode;                                       // +0x0f8
    SubState mSub;                                   // +0x0fc
    PtrPair mTail;                                   // +0xdc8
};
struct PropEntry {                                   // 0x20 bytes
    uint32_t pad[4];
    uint32_t mValue;                                 // +0x10
    uint32_t pad2[3];
};
struct PropList_s0041_7d60 {
    uint32_t pad[2];
    PropEntry* mpEntries;                            // +0x08
};
uint32_t* FindProp(PropList_s0041_7d60* list, int id, int a, int b, int c);   // FUN_0071de40
int FindPropIndex(PropList_s0041_7d60* list, int id, int a, int b, int c);    // FUN_0071ddc0
struct PropKey { uint32_t a, b, c; };
class Manager1 {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10();
    virtual bool Load(int a, int b, RefCounted_s0041_7d60** out);          // slot 11 (+0x2c)
};
class Manager2 {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4();
    virtual bool Find(const PropKey* key, RefCounted_s0041_7d60** out);    // slot 5 (+0x14)
};
Manager1* GetManager1();                                         // FUN_0067de30
Manager2* GetManager2();                                         // FUN_0067dcd0
bool GetPropKey(RefCounted_s0041_7d60* obj, int id, PropKey* out);          // FUN_006a1250
struct RefVector_s0041_7d60 {
    void push_back(const intrusive_ptr_s0041_7d60<RefCounted_s0041_7d60>& p);           // FUN_004b54b0
    uint32_t pad[5];
};
struct Loader {
    uint32_t pad[3];
    RefVector_s0041_7d60 mRefs;                                             // +0x0c
    void LoadAll(int a, int b);
};
// ---- items of slice s00417d60 end

// ---- items of slice s004186c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t g_PropListGroup;  // 0x015D13E8
extern const float kDefaultScale;  // 0x013EBA80
extern const float kDefaultItemScale;  // 0x013EB2B0
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedExchange, _InterlockedIncrement)
struct DefaultRefCounted_s0041_86c0 {
    uint32_t pad0;
    int mRefCount;
    void Release();  // 0x00453540
    void AddRef() { int r = mRefCount + 1; mRefCount = mRefCount + 1; }
};
struct ItemA : DefaultRefCounted_s0041_86c0 {  // 0x1D0 bytes
    ItemA();  // 0x00507380
    uint32_t pad[(0x1d0 - 8) / 4];
};
struct ItemB : DefaultRefCounted_s0041_86c0 {  // 0xF8 bytes
    ItemB(float f);  // 0x004F85B0
    uint32_t pad[(0xf8 - 8) / 4];
};
template <class T>
struct intrusive_ptr_s0041_86c0 {
    T* mpObject;
    intrusive_ptr_s0041_86c0() : mpObject(0) {}
    ~intrusive_ptr_s0041_86c0() {
        if (mpObject)
            mpObject->Release();
    }
    T* get() const { return mpObject; }
    intrusive_ptr_s0041_86c0& operator=(T* pObject) {
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
};
struct EditorSource;
struct ThreadedObject_s0041_86c0 {  // 0xBC bytes
    uint32_t pad0;
    int mRefCount;  // +4, bumped with lock xadd
    uint32_t pad08[(0x34 - 8) / 4];
    intrusive_ptr_s0041_86c0<DefaultRefCounted_s0041_86c0> mpItemA;  // +0x34
    intrusive_ptr_s0041_86c0<DefaultRefCounted_s0041_86c0> mpItemB;  // +0x38
    uint32_t pad3C[(0xbc - 0x3c) / 4];
    ThreadedObject_s0041_86c0(EditorSource* pOwner);  // 0x004C6DF0
    void Method1();  // 0x004CA6E0
    void Method2();  // 0x004CB340
    void Method3();  // 0x004CB820
    void Release();  // 0x00404F90
};
template <>
struct intrusive_ptr_s0041_86c0<ThreadedObject_s0041_86c0> {
    ThreadedObject_s0041_86c0* mpObject;
    intrusive_ptr_s0041_86c0() : mpObject(0) {}
    ~intrusive_ptr_s0041_86c0() {
        if (mpObject)
            mpObject->Release();
    }
    ThreadedObject_s0041_86c0* get() const { return mpObject; }
    intrusive_ptr_s0041_86c0& operator=(ThreadedObject_s0041_86c0* pObject) {
        if (pObject != mpObject) {
            ThreadedObject_s0041_86c0* const pTemp = mpObject;
            if (pObject)
                _InterlockedIncrement((long*)&pObject->mRefCount);
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
};
struct PropertyListValue {
    uint32_t pad00[4];
    uint16_t pad10;
    uint16_t type;  // +0x12
    float* GetFloat();  // 0x0041EA70
};
struct PropertyList_s0041_86c0 : Object {
    virtual void v08(); virtual void v0C(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1C(); virtual void v20();
    virtual bool GetProperty(uint32_t id, PropertyListValue** dst);  // +0x24
};
struct PropertyListPtr_s0041_86c0 {
    PropertyList_s0041_86c0* mpObject;
    PropertyListPtr_s0041_86c0() : mpObject(0) {}
    ~PropertyListPtr_s0041_86c0() {
        if (mpObject)
            mpObject->Release();
    }
    PropertyList_s0041_86c0* get() const { return mpObject; }
    PropertyList_s0041_86c0** OutImpl();  // 0x0041D870
    PropertyList_s0041_86c0** Out() { return OutImpl(); }
};
struct PropManager_s0041_86c0 {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyList_s0041_86c0** dst);  // +0x2C
    static PropManager_s0041_86c0* GetImpl();  // 0x0067DE30
    static PropManager_s0041_86c0* Get() { return GetImpl(); }
};
struct LoadHandle_s0041_86c0 {
    uint32_t pad00[6];
    uint32_t mState;  // +0x18
    void Release();  // 0x00690120
    void SetState(uint32_t s) { mState = s; }
    void Attach(void* p);  // 0x00422990 (editor resource)
    void SetTarget(void* p);  // 0x0068F9B0
    void Finish();  // 0x006909B0
    void Add(LoadHandle_s0041_86c0* h);  // 0x00691380
    bool Process(void* res);  // 0x004229F0
    void ProcessB(void* res);  // 0x00422A10
    void OnBegin(void* p);  // 0x004229B0
    void OnEnd(void* p);  // 0x004229D0
};
struct HandlePtr {
    LoadHandle_s0041_86c0* mpObject;
    HandlePtr() : mpObject(0) {}
    ~HandlePtr() {
        if (mpObject)
            mpObject->Release();
    }
    LoadHandle_s0041_86c0* get() const { return mpObject; }
    LoadHandle_s0041_86c0* operator->() const { return mpObject; }
    LoadHandle_s0041_86c0** OutImpl();  // 0x0041D940
    LoadHandle_s0041_86c0** AsPointer() {
        if (mpObject) {
            LoadHandle_s0041_86c0* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
        return &mpObject;
    }
    LoadHandle_s0041_86c0** Out() { return OutImpl(); }
    LoadHandle_s0041_86c0* Detach() {
        LoadHandle_s0041_86c0* p = mpObject;
        mpObject = 0;
        return p;
    }
};
struct LoadManager_s0041_86c0 {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C();
    virtual bool OpenHandle(LoadHandle_s0041_86c0** dst);  // +0x10
    virtual void v14(); virtual void v18(); virtual void v1C();
    virtual void Lock();  // +0x20
    virtual void Unlock();  // +0x24
};
LoadManager_s0041_86c0* GetLoadManager_s0041_86c0();  // 0x0068F4D0
struct ConfigRoot {
    void Begin(ThreadedObject_s0041_86c0* pThreaded, float scale, LoadHandle_s0041_86c0** pOut);  // 0x00414470
};
ConfigRoot* GetConfigRoot();  // 0x00401010
int LookupIndex(uint32_t key);  // 0x00432F10
struct SubBase {
    ~SubBase();  // 0x0041EB80
    uint32_t pad[5];
};
struct MemberA { ~MemberA(); uint32_t pad[5]; };  // 0x004B5440 (0x14)
struct MemberB { ~MemberB(); uint32_t pad[5]; };  // 0x00432D60 (0x14)
struct Elem38 { uint32_t pad[14]; };
struct Elem10 { uint32_t pad[4]; };
struct Vec38 {
    Elem38* mpBegin;
    Elem38* mpEnd;
    uint32_t pad[3];
    void FreeData();  // 0x00427440
    ~Vec38() {
        Elem38* p = mpBegin;
        uint32_t dead[3];
        for (; p < mpEnd; ++p) {}
        FreeData();
    }
};
struct Vec10 {
    Elem10* mpBegin;
    Elem10* mpEnd;
    uint32_t pad[3];
    void FreeData();  // 0x00554B10
    ~Vec10() {
        Elem10* p = mpBegin;
        uint32_t dead[3];
        for (; p < mpEnd; ++p) {}
        FreeData();
    }
};
struct DeadTail {
    ~DeadTail() { uint32_t post[8]; }
};
struct SubObject : SubBase, DeadTail {  // size 0x8C
    Vec10 mVec14;
    Vec38 mVec28;
    Vec38 mVec3C;
    SubBase mBase50;
    MemberA mMember64;
    MemberB mMember78;
    SubObject();  // 0x00460F80
    ~SubObject();
};
struct TailObject {  // at +0xBC
    TailObject();  // 0x0041D360
    void Reserve(int n);  // 0x004E0880
    ~TailObject();  // 0x0041E640
    uint32_t pad[1];
};
struct IntrusiveAtomic {
    int mValue;
    IntrusiveAtomic() { _InterlockedExchange((long*)&mValue, 0); }
};
struct Gap28 {
    uint32_t a, b;
    Gap28() { uint32_t unused; }
};
struct DeadHead {
    ~DeadHead() { uint32_t pre[7]; }
};
struct EditorBaseP {
    virtual int AddRef();
    virtual int Release();
    virtual ~EditorBaseP() {}
};
struct EditorBaseQ : EditorBaseP {
    EditorBaseQ() {}
};
struct EditorBaseR {
    virtual void rf0();
    IntrusiveAtomic mCount;
    EditorBaseR() {}
    ~EditorBaseR() {}
};
struct Vec3Zero {
    uint32_t a, b, c;
    Vec3Zero() : a(0), b(0), c(0) {}
};
struct KeyPair_s0041_86c0 {
    uint32_t id;
    uint16_t a, b;
    KeyPair_s0041_86c0() : id(0x2ea8fb98), a(0), b(4) {}
};
int ConvertValue(uint32_t v);  // 0x004BB860
struct Elem8C { uint32_t pad[35]; };
struct Vec8C {
    Elem8C* mpBegin;
    Elem8C* mpEnd;
    uint32_t pad[3];
    int size() const { return (int)(mpEnd - mpBegin); }
};
struct EditorSource : Object {  // owner object / creation source
    uint32_t f04, f08, f0C, f10, f14;
    uint32_t f18;
    uint32_t pad1C[(0x98 - 0x1C) / 4];
    Vec8C mItems;  // +0x98
};
struct EditorResource : EditorBaseQ, EditorBaseR {
    intrusive_ptr_s0041_86c0<EditorSource> mpOwner;  // +0x0C
    Vec3Zero mVec;                        // +0x10
    KeyPair_s0041_86c0 mKey;                         // +0x1C
    intrusive_ptr_s0041_86c0<ThreadedObject_s0041_86c0> mpThreaded;  // +0x24
    Gap28 mGap;                           // +0x28
    SubObject mSub;                       // +0x30
    TailObject mTail;                     // +0xBC
    uint32_t pad[(0x2d4 - 0xc0) / 4 - 1];
    DeadHead mDeadHead;

    EditorResource();  // 0x00418870
    bool Setup(LoadHandle_s0041_86c0* pParent);  // 0x00418AE0
    void NotifyA(LoadHandle_s0041_86c0* pParent);  // 0x00418F90
    bool NotifyB(LoadHandle_s0041_86c0* pParent);  // 0x00418FD0
    static void operator delete(void* p);  // 0x00F47380
};
inline void DeadPad5() { uint32_t dead[6]; }
struct ResPtr {
    EditorResource* mpObject;
    ResPtr(EditorResource* p) : mpObject(p) {
        if (mpObject)
            mpObject->AddRef();
    }
    ~ResPtr() {
        if (mpObject)
            mpObject->Release();
    }
    EditorResource* get() const { return mpObject; }
    EditorResource* operator->() const { return mpObject; }
    operator EditorResource*() const { return mpObject; }
};
// ---- items of slice s004186c0 end

// ---- items of slice s00419000 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(int64_t*);
extern uint32_t g_DefaultKey;                         // 0x015d126c
struct Item_s0041_9000 { char d[0x8c]; };
struct ItemVec { Item_s0041_9000* begin; Item_s0041_9000* end; int size() const { return (int)(end - begin); } };
struct ModelData { uint32_t pad[0x26]; ItemVec items; uint32_t pad2[0x12]; float* weights; };
struct Owner_s0041_9000 { uint32_t pad[2]; ModelData* data; ModelData* GetData() { return data; } uint32_t pad2[0x21]; uint32_t f90; };
struct SlotA { uint32_t p[5]; void __thiscall Reserve(int n); };
struct SlotB { uint32_t p[5]; void __thiscall Assign(uint32_t* src); };
struct SlotC { uint32_t p[5]; void __thiscall Reserve(int n); };
struct SlotD { uint32_t p[5]; void __thiscall Reserve(int n); };
struct SlotE { uint32_t p[5]; void __thiscall Reserve(int n); };
struct Task;
struct Request { uint32_t pad[7]; uint32_t f1c; void __thiscall Dispatch(Task* t); };
struct Task {
    uint32_t pad[9];
    Owner_s0041_9000* owner;
    uint32_t pad2;
    uint32_t f2c;
    SlotA a; SlotB b; SlotC c; SlotC c2; SlotA a2; SlotD d; SlotE e;
    void __thiscall Prepare(Request* req);
};
struct TimeBudget {
    uint32_t pad[6];
    int64_t deadline;                      // +0x18
    void __thiscall Init(int ms, int flag);   // 0x0093A560
    void __thiscall Arm(int a, int b);        // 0x0093A480
};
struct Transform_s0041_9000 {  // 0x5C bytes with 4-byte header
    uint32_t pad[0x17];
    void __thiscall Construct();
};
struct SceneObj { uint32_t pad0; uint32_t state; uint16_t flags; uint16_t refCount; uint32_t f0c[3]; uint32_t f18; uint32_t f1c[9]; int refs; };
struct Engine {
    virtual void v0(); virtual void v1(); virtual void v2();          // +0x00
    virtual SceneObj* Lookup(uint32_t a, uint32_t b, int c);          // +0x0C
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();   // +0x10
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();   // +0x20
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();   // +0x30
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();   // +0x40
    virtual void v20(); virtual void v21();                           // +0x50
    virtual void Prepare(SceneObj* o);                                // +0x58
    virtual void v23();                                               // +0x5C
    virtual Engine* Module();                                         // +0x60
    virtual void v25(); virtual void v26(); virtual void v27();       // +0x64
    virtual void SetA(SceneObj* o, int idx, float v, int z, int w);   // +0x70
    virtual void SetB(SceneObj* o, int idx, float v, int z);          // +0x74
    virtual void SetC(SceneObj* o, int idx, float v, int z);          // +0x78
    virtual void v31();                                               // +0x7C
    virtual char Query(SceneObj* o, int idx, float* lo, float* hi, int z); // +0x80
    virtual void v33(); virtual void v34(); virtual void v35(); virtual void v36();   // +0x84
    virtual void v37(); virtual void v38(); virtual void v39(); virtual void v40();   // +0x94
    virtual void v41(); virtual void v42(); virtual void v43(); virtual void v44();   // +0xA4
    virtual void v45(); virtual void v46(); virtual void v47(); virtual void v48();   // +0xB4
    virtual void v49(); virtual void v50(); virtual void v51(); virtual void v52();   // +0xC4
    virtual void v53(); virtual void v54(); virtual void v55(); virtual void v56();   // +0xD4
    virtual void v57();                                               // +0xE4
    virtual int Enumerate(SceneObj* o, Transform_s0041_9000* out, int max);       // +0xE8
};
Engine* GetEngine();                                  // 0x00401010
void __fastcall ReleaseObj(SceneObj*);               // 0x0040f360 (thiscall)
void __fastcall PollLoader(void* self);              // 0x0041e6a0 (thiscall)
struct Finisher { char __thiscall Done(void* task); };   // 0x00422a30
struct LoadTask {
    uint32_t pad[9];
    Owner_s0041_9000* owner;          // +0x24
    uint32_t pad2[0x25];
    SceneObj** objs;       // +0xBC
    SceneObj** objsEnd;    // +0xC0
    char Run(Finisher* fin);
};
// ---- items of slice s00419000 end

// ---- items of slice s0041aa40 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Elem24 { unsigned int pad[6]; };
struct Elem24VectorBase {
    Elem24* mpBegin;
    Elem24* mpEnd;
    Elem24* mpCapacity;
    bool Collect(unsigned int a, unsigned int b);   // FUN_0041aaa0
    ~Elem24VectorBase();                            // FUN_004fd940
};
struct Elem24Vector : Elem24VectorBase {
    Elem24Vector() { mpBegin = 0; mpEnd = 0; mpCapacity = 0; }
    ~Elem24Vector() {
        for (Elem24* p = mpBegin; p < mpEnd; ++p) {
        }
        {
            unsigned int dead1[3];   // dead debug local of the original inline dtor
        }
    }
};
struct Elem24VectorWithStorage : Elem24Vector {
    unsigned int storage[21];
};
// ---- items of slice s0041aa40 end

// ---- items of slice s005609a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct CEditorResourceThunk {
    virtual int f(void* p);
};
}
// ---- items of slice s005609a0 end

// ---- items of slice s0041c1d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t g_ResType0, g_ResType1, g_ResType2, g_ResType3, g_ResType4, g_ResType5;   // 0x015d13b8,0x15d117c,0x15d1248,0x15d1174,0x15d1254,0x15d132c
struct ResKey3 { uint32_t mInstance, mGroup, mType; };      // 12-byte key in the property array
struct IPropertyList {                       // vtable only needs Release at +4
    virtual void v0();
    virtual void Release();
};
struct PropListPtr {                         // EA::AutoRefCount<PropertyList>
    IPropertyList* mp;
    void** AsPPVoidParam();                  // 0x0041d870
};
struct IPropertyManager {                    // SP::PropertyManager() 0x0067de30
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
    virtual void GetPropertyList(int instance, int group, void** out);       // +0x2c
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
    virtual void GetPropertyIDs(uint32_t typeID, void* idsVec);             // +0x48
};
IPropertyManager* PropertyManager();         // 0x0067de30
struct KeySet {
    uint32_t mAlloc;
    void* mpEnd;                             // +4  (header node)
    void* mpBegin;                           // +8  (leftmost)
    void* mpRoot;                            // +0xc
    uint32_t pad[3];
    KeySet(const uint8_t* tag);              // 0x004b5980
    void Insert(void* outPair, ResKey3* key, bool b);   // 0x004290c0 DoInsertValue_unique
    void Find(void* outIter, ResKey3* key);              // 0x00422b00
    void DoNuke(void* root);                             // 0x004e8a30
};
struct KeyIter {
    void* mpNode;
    KeyIter(void* node);                     // 0x00566c50
    KeyIter& operator++();                   // 0x00422c50
    ResKey3& operator*();                    // 0x00564f50
};
struct AuxAlloc { uint32_t a, b; AuxAlloc(const uint8_t* tag); };   // 0x00429360
struct IdVec {                               // SimpleVector<uint32_t>
    uint32_t* mpBegin; uint32_t* mpEnd; uint32_t* mpCap;
    AuxAlloc mAlloc;
    IdVec(const uint8_t* tag) : mAlloc(tag) { mpBegin = 0; mpEnd = 0; mpCap = 0; }
    void erase(uint32_t* first, uint32_t* last);   // 0x004769b0
    void FreeAll();                                // 0x00425990
};
struct WideBufA { uint32_t mpData; uint32_t pad[0x85]; WideBufA(); void ReleaseHeap(); };  // 0x0041d660 / 0x004292a0
struct WideBufB { uint32_t mpData; uint32_t pad[0x107]; WideBufB(); void ReleaseHeap(); }; // 0x0041d6c0 / 0x004292a0
struct ByteBuf  { uint32_t mpData; uint32_t pad[0x87]; ByteBuf(); void ReleaseHeap(); };   // 0x0041d720 / 0x00429300
struct IStream_s0041_c1d0 { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
virtual void v12();
                 virtual void Write(const void* data, uint32_t size); };       // +0x38
struct IRecord { virtual void v0(); virtual void v1(); virtual void Release();   // +8
virtual void v3();
virtual void v4();
virtual void v5();
                 virtual IStream_s0041_c1d0* GetStream();                                   // +0x18
virtual void v7();
virtual void v8();
                 virtual void Close(); };                                        // +0x24
struct ResKeyRec { uint32_t mInstance, mType, mGroup; };    // key passed to OpenRecord, 0x10 bytes incl. pad
struct IRecordCounted { char pad[0x40]; int mRefCount; void Release(); };       // Counted::Release 0x0040f360
struct IDatabaseDir {                                                           // Baker()->vcall(0x60)
virtual void v0();
virtual void v1();
virtual void v2();
    virtual IRecordCounted* GetRecord(uint32_t id, uint32_t type, int mode);    // +0xc
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
    virtual void Process(IRecordCounted* rec);                                  // +0x58
};
struct IBakerLike {                                                             // Baker() 0x00401010
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
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
    virtual IDatabaseDir* GetDatabaseDir();                                     // +0x60
};
IBakerLike* Baker_s0041_c1d0();                                                            // 0x00401010
struct IPkgSecondary { virtual void AddRef(); virtual void Release(); };         // sub-object at +4
struct IPkgPrimary {
virtual void v0();
virtual void Release();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
    virtual void Open(int mode, int access, int flags);                          // +0x18
    virtual void Close();                                                        // +0x1c
virtual void v8();
virtual void v9();
virtual void v10();
    virtual void SetPath(const wchar_t* path);                                   // +0x2c
    virtual void v12();
    virtual bool OpenRecord(ResKeyRec* key, IRecord** out, int a, int b, int c, int d);   // +0x34
};
struct DatabasePackedFile : IPkgPrimary, IPkgSecondary {
    char pad[0x380];
    DatabasePackedFile(const wchar_t* path, void* alloc);                        // 0x008d9f80
    bool SetHoleUse(int mode, float f);                                          // 0x008d8530
};
struct MemoryStream {
    uint32_t pad[9];
    MemoryStream(void* a, void* b, const char* name);       // 0x0093c270
    void AddRef();                                          // 0x0083f5d0
    void SetOption(int opt, float v);                       // 0x0093bb40
    void SetSize(int n);                                    // 0x0093c370
    bool SetPosition(int off, int type);                    // 0x0093c0c0
    uint32_t GetSize();                                     // 0x00fc7e50
    void* GetData();                                        // 0x0093ba70
    void Destroy();                                         // 0x0093bde0
};
struct FileStream {
    uint32_t pad[0x8c];
    FileStream(const wchar_t* path);                        // 0x00931e10
    bool Open(int a, int b, int c, int d);                  // 0x009318f0
    void Write(const void* data, uint32_t size);            // 0x00931d30
    void Close();                                           // 0x00931a70
    ~FileStream();                                          // 0x00931e70
};
struct Transform_s0041_c1d0 {  // 0x00409930
    uint32_t pad[0x16];
    Transform_s0041_c1d0();
};
struct XfSlot { uint32_t mHead; Transform_s0041_c1d0 mXf; };           // 0x5c bytes
void  FormatPath(void* wideBuf, const wchar_t* fmt, ...);   // 0x004c0530 (cdecl)
const wchar_t* GetBasePath();                               // 0x00688cf0
void* ZoneObject_new(int size, const char* name, int a, int b, int c, int d);   // 0x00926020
void  CreateDirectoryPath(const wchar_t* path);             // 0x00932960
bool  GetArrayProperty(IPropertyList* list, uint32_t id, int* count, ResKey3** arr);  // 0x006a0ae0 (cdecl)
bool  CollectAndDestroy(IRecordCounted* rec, MemoryStream* ms);   // 0x0041aa40 (cdecl)
// ---- items of slice s0041c1d0 end

// ---- items of slice s00407280 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const char g_GraphicsTag[];
struct ResourceKey_s0040_7280 { uint32_t instance, type, group; };
struct IRefCounted_s0040_7280 {
    virtual void AddRef();
    virtual void Release();
};
struct PropertyList_s0040_7280 : IRefCounted_s0040_7280 {
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
    virtual void SetProperty(uint32_t id, void* value);        // +0x14
    virtual bool HasProperty(uint32_t id);                     // +0x1c (slot 7)
    virtual bool GetProperty(uint32_t id, void* outInfo);      // +0x24
};
struct PropertyInfo { char pad[0x12]; short type; };
struct ResourceManager_s0040_7280 {
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
    virtual bool GetResource(uint32_t group, uint32_t instance, void* outRef);  // +0x2c
    virtual void v12();
    virtual void SetResource(PropertyList_s0040_7280* list, uint32_t instance, uint32_t group); // +0x34
};
struct ResourceFactory {
virtual void v0();
virtual void v1();
virtual void v2();
    virtual bool Create(ResourceKey_s0040_7280* key, void* out, int, int, int, int);       // +0xc
};
struct Part { char pad[0x1d8]; };
struct Model {
    char pad0[0x18]; uint32_t kind;
    char pad1[0x80]; Part* partsBegin; Part* partsEnd;
};
struct MeshEntry { uint16_t flags, count; float data[12]; };           // 0x38 bytes
ResourceManager_s0040_7280* GetResourceManager_s0040_7280();      // FUN_0067de30
ResourceFactory* GetResourceFactory();      // FUN_0067dcd0
int  MakeKey(void* scratch);                // FUN_0041d870
Model* LookupModel(void* ref);              // FUN_00421eb0
void* AllocPropertyList(uint32_t, const char*, int, int, int, int);
PropertyList_s0040_7280* ConstructPropertyList(void* mem);   // Editor::cPropertyList::cPropertyList
void FlushProperty(int);                    // FUN_0093db80
void AddPartBounds(void* acc, Part* p);
void BuildPartEntry(MeshEntry* out, Part* p);
static void CommitProperty(PropertyList_s0040_7280* list, uint32_t id, void* value) {
    uint16_t info[2] = { 0, 0 };
    list->SetProperty(id, value);
    if (info[0] & 4) FlushProperty(0);
}
struct SettingsBuilder {
    void* vtbl;
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
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
    virtual void GetBounds(uint32_t a, uint32_t b, float* outMin, float* outMax, uint32_t c); // +0x54

    void BuildGraphicsProperties(ResourceKey_s0040_7280* key);
};
// ---- items of slice s00407280 end

// ---- items of slice s00411b90 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace A {
struct Owned_s0041_1b90 {  // 68f950 / 690120
    void __thiscall AddRef();
    void __thiscall Release();
};
}
namespace A {
struct Shared { char pad[0x40]; int refCount; void __thiscall Release(); };
}
namespace A {
inline void AssignShared(Shared** pdst, Shared* src) {
    if (src != *pdst) { Shared* old = *pdst; if (src) src->refCount++; *pdst = src; if (old) old->Release(); }
}                            // 40f360
}
namespace A {
struct Opaque4 { uint32_t pad; void __thiscall Set(uint32_t); };
}
namespace A {
struct SeqA { uint32_t pad[5]; void __thiscall Assign(const SeqA&); };    // 41ebe0
}
namespace A {
struct SeqB { uint32_t pad[5]; void __thiscall Assign(const SeqB&); };    // 420e30
}
namespace A {
struct SeqC { uint32_t pad[5]; void __thiscall Assign(const SeqC&); };    // 41e0d0
}
namespace A {
struct SeqD { uint32_t pad[5]; void __thiscall Assign(const SeqD&); };    // 41f320
}
namespace A {
struct Block80 { uint32_t pad[5]; uint8_t flag; uint8_t q[3]; void __thiscall CopyBase(const Block80&);
    inline void Assign(const Block80& o) { const Block80* sr = &o; Block80* d = this; d->CopyBase(*sr); uint8_t t = sr->flag; d->flag = t; } }; // 4269b0
}
namespace A {
struct SeqE { uint32_t pad[5]; void __thiscall Assign(const SeqE&); };    // 421290
}
namespace A {
struct Range_s0041_1b90 {  // 423650
    uint32_t* first;
    uint32_t* last;
    void __thiscall Assign(uint32_t*, uint32_t*);
};
}
namespace A {
struct SeqF { uint32_t pad[5]; void __thiscall Assign(const SeqF&); };    // 421670
}
namespace A {
struct SeqG { uint32_t pad[5]; void __thiscall Assign(const SeqG&); };    // 406ac0
}
namespace A {
struct Obj_s0041_1b90 {
    Owned_s0041_1b90* owned;        // 0x00
    Opaque4 f04;         // 0x04
    SeqA f08;            // 0x08
    SeqA f1c;            // 0x1c
    SeqB f30;            // 0x30
    SeqC f44;            // 0x44
    SeqD f58;            // 0x58
    SeqA f6c;            // 0x6c
    Block80 f80;         // 0x80
    SeqE f98;            // 0x98
    SeqA fac;            // 0xac
    Shared* c0;         // 0xc0
    Shared* c4;         // 0xc4
    uint32_t c8, cc;
    Range_s0041_1b90 d0;            // 0xd0 (container header)
    uint32_t pad2[2];
    SeqF fe0;
    uint8_t f4a, f4b; uint8_t pp[2];
    uint32_t f8;
    SeqG fc;
    uint32_t big[(0xdc8 - 0x110) / 4];
    uint32_t t0, t1;
    Obj_s0041_1b90& operator=(const Obj_s0041_1b90&);
};
}
namespace B {
struct IRelease { virtual void v0(); virtual void Release(); };
}
namespace B {
struct IProps {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
    virtual void SetValue(uint32_t id, void* v);
};
}
namespace B {
struct IResMgr {
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
    virtual bool Open(uint32_t inst, uint32_t key, uint32_t arg);
};
}
namespace B {
struct IIter {
virtual void v0();
virtual void v1();
virtual void v2();
    virtual bool Next(void* key, IRelease** out, int, int, int, int);
};
}
namespace B {
struct TransformHdr { uint32_t pad; float x, y, pad2, z; };
}
namespace B {
struct ModelEntry { uint32_t pad; uint16_t type; uint16_t pad2; TransformHdr* hdr; };
}
namespace B {
struct ModelList { uint32_t pad[2]; ModelEntry** items; bool __thiscall IsEmpty(); };
}
namespace B {
struct Inner { uint32_t pad[0x2e]; ModelList* models; };
}
namespace B {
struct Mid { uint32_t pad[2]; Inner* inner; };
}
namespace B {
struct Cam { char pad[0x70]; float x, y, z; };
}
namespace B {
struct Cell_s0041_1b90 { uint32_t pad[2]; Mid* mid; };
}
namespace B {
struct Counter { uint32_t pad[5]; float scale; };
}
namespace B {
struct Obj2;
}
namespace B {
IResMgr* GetResMgr();
}
namespace B {
int64_t __fastcall ReadCounter(Counter*);
}
namespace B {
void __fastcall UpdateCounter(Counter*);
}
namespace B {
IIter* GetIter();
}
namespace B {
bool __cdecl GetBoolProperty(IProps*, uint32_t, bool*);
}
namespace B {
uint32_t __cdecl GetNameId(uint32_t);
}
namespace B {
void* __cdecl AllocBuf(uint32_t);
}
namespace B {
void __cdecl BindKey(uint32_t, uint32_t, void*, int);
}
namespace B {
void __cdecl PutBack(void*, int);
}
namespace B {
void __cdecl ApplyProps(IProps*, uint32_t, int);
}
namespace B {
struct Obj2 {
    virtual void vf0();
    virtual void vf1();
    virtual void vf2();
    virtual void vf3();
    virtual void vf4();
    virtual void vf5();
    virtual void vf6();
    virtual void vf7();
    virtual void vf8();
    virtual void vf9();
    virtual void vf10();
    virtual void vf11();
    virtual void vf12();
    virtual void vf13();
    virtual void vf14();
    virtual void vf15();
    virtual void vf16();
    virtual void vf17();
    virtual void vf18();
    virtual void vf19();
    virtual void vf20();
    virtual void vf21();
    virtual void vf22();
    virtual void vf23();
    virtual void vf24();
    virtual void vf25();
    virtual void vf26();
    virtual void vf27();
    virtual void SetPreBaked(uint32_t* key, bool v, const wchar_t* name);
    char pad0[0x74 - 4];
    uint32_t f74;
    char pad1[0x228 - 0x78];
    uint32_t keyInst, keyType, keyGroup;   // 0x228
    uint32_t f234;
    uint16_t flags;                        // 0x238
    char pad3[0x240 - 0x23a];
    Cell_s0041_1b90* cell;                            // 0x240
    char pad4[0x1114 - 0x244];
    int cntA;
    char pad5[0x1120 - 0x1118];
    int cntB;
    float sumA;
    float lastA;
    char pad6[0x1138 - 0x112c];
    Counter c1;
    Counter c2;
    void ApplyBlend(uint32_t* key, float a, float b);
    void Tick();
};
}
namespace B {
struct IKeyHolder { virtual void v0(); virtual void Release(); };
}
namespace B {
bool __cdecl FindEntry(IKeyHolder*, uint32_t, uint32_t*);   // 0x6a1250
}
namespace B {
struct Str16 { uint32_t pad[4]; uint16_t kind; uint16_t flags; };
}
namespace B {
void __fastcall MakeStr(Str16* s, uint32_t* v);   // 0x422eb0
}
namespace B {
void __cdecl FreeStr(int);                          // 0x93db80
}
// ---- items of slice s00411b90 end

// ---- items of slice s00401200 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct IRefCounted_s0040_1200 {
    virtual int AddRef() = 0;
    virtual int Release() = 0;
};
struct RefPtr_s0040_1200 {
    IRefCounted_s0040_1200* mpObject;
    RefPtr_s0040_1200(IRefCounted_s0040_1200* p);  // 0x0041CC20
    ~RefPtr_s0040_1200() { if (mpObject) mpObject->Release(); }
};
struct DataBlock {
    int mnCount;
    char* mpData;
    uint16_t mnElementSize;
    uint16_t mnStride;
    RefPtr_s0040_1200 mpOwner;

    DataBlock(int count, uint16_t elementSize, uint16_t stride)
        : mnCount(count), mpData(0), mnElementSize(elementSize), mnStride(stride), mpOwner(0) {}
    DataBlock(const DataBlock& other);  // 0x00401B80

    uint32_t& At(int i) { return *(uint32_t*)(mpData + mnStride * i); }
};
struct TypedBlock : DataBlock {
    TypedBlock(const DataBlock& b) : DataBlock(b) {}
};
struct BlockKey {
    int mType;
    int mIndex;
    int mA;
    int mB;
    BlockKey(int type, int index, int a, int b) : mType(type), mIndex(index), mA(a), mB(b) {}
};
struct BlockEntry {  // 0x20 bytes
    BlockKey mKey;
    DataBlock mBlock;
    BlockEntry(int type, int index, int a, int b, const DataBlock& block)
        : mKey(type, index, a, b), mBlock(block)
    {
        int unused1;  // stand-ins for two dead stack slots in the original
        int unused2;
    }
};
struct BlockArray {
    BlockEntry* mpBegin;
    void push_back(const BlockEntry& e);  // 0x0041F7D0
};
struct BlockContainer {
    int mUnk0;
    int mUnk4;
    BlockArray mEntries;
};
int FindBlock(BlockContainer* c, int type, int index, int a, int b);  // 0x0071DDC0
void AllocateBlock(DataBlock* block);                                 // 0x00720070
struct Thing {
    uint32_t pad[2];
    uint32_t mFlags;
    void* Cast(uint32_t typeId);  // 0x011EDCF0
    int HasIndex() const { return (mFlags & 8) != 0; }
};
struct Object_s0040_1200 {
    uint32_t pad;
    Thing* mpThing;
};
struct IObjectManager {
virtual void f00();
virtual void f04();
virtual void f08();
virtual void f0c();
virtual void f10();
virtual void f14();
virtual void f18();
virtual void f1c();
virtual void f20();
virtual void f24();
    virtual Object_s0040_1200* GetObject(uint32_t id);  // slot 0x28
};
IObjectManager* GetObjectManager();  // 0x0067DD70
inline uint32_t* GetIndexComponent(Thing* t)
{
    if (t && t->HasIndex())
        return (uint32_t*)t->Cast(0x20f);
    return 0;
}
// ---- items of slice s00401200 end

// ---- items of slice s004063d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
template <class T> class intrusive_ptr_s0040_63d0 {
public:
    intrusive_ptr_s0040_63d0() : mpObject(0) {}
    intrusive_ptr_s0040_63d0(const intrusive_ptr_s0040_63d0& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~intrusive_ptr_s0040_63d0() { if (mpObject) mpObject->Release(); }
    T* get() const { return mpObject; }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
    intrusive_ptr_s0040_63d0& Reset();                                  // e.g. 0x0041d9f0 (non-inline)
    T** AsPointer() { return &Reset().mpObject; }
    intrusive_ptr_s0040_63d0& operator=(const intrusive_ptr_s0040_63d0& x) { return operator=(x.mpObject); }
    intrusive_ptr_s0040_63d0& operator=(T* pObject) {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject) pObject->AddRef();
            mpObject = pObject;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
    T* mpObject;
};
struct ResourceKey_s0040_63d0 { unsigned int instanceID, typeID, groupID; };
class DefaultRefCounted_s0040_63d0 {
    public: int AddRef();
    int Release();  // 0x00453540 (DefaultRefCounted::Release)
    int mnRefCount;
};
struct Property_s0040_63d0 {
    unsigned int pad[4]; unsigned short pad10; unsigned short mnType;
float* GetValueFloat();
bool* GetValueBool();
int* GetValueInt32();
};
class PropertyList_s0040_63d0 {
public:
virtual int AddRef();
virtual int Release();
virtual void f8();
virtual void fc();
virtual void f10();
virtual void f14();
virtual void f18();
virtual void f1c();
virtual void f20();
    virtual bool GetProperty(unsigned int id, Property_s0040_63d0*& prop);
};
class IPropManager_s0040_63d0 {
public:
virtual void f0();
virtual void f4();
virtual void f8();
virtual void fc();
virtual void f10();
virtual void f14();
virtual void f18();
virtual void f1c();
virtual void f20();
virtual void f24();
virtual void f28();
    virtual bool GetPropertyList(unsigned int instanceID, unsigned int groupID, PropertyList_s0040_63d0** ppList);
};
IPropManager_s0040_63d0* PropManager_s0040_63d0();   // 0x0067de30
class IEditorModel { public: virtual void f0(); };
class EditorModel : public IEditorModel, public DefaultRefCounted_s0040_63d0 {
public:
    void Init(void* p, int a, int b, bool c);   // 0x004ae260
    unsigned int GetCount();                    // 0x004accf0
};
bool LoadEditorModel(const ResourceKey_s0040_63d0& key, EditorModel** ppModel, int flags);  // 0x004badd0
class Task_s0040_63d0 {
public:
    int AddRef();     // 0x0068f950
    int Release();    // 0x00690120
    int GetState();   // 0x0068f970
    bool IsReady() { switch (GetState()) { case 7: case 8: return true; default: return false; } }
    void SetOwner(void* owner);  // 0x00421f40
    void Start();     // 0x006909b0
    void SetField18(int v) { mField18 = v; }
    unsigned int pad[6];
    int mField18;
};
class ITaskManager {
public:
virtual void f0();
virtual void f4();
virtual void f8();
virtual void fc();
    virtual bool CreateTask(Task_s0040_63d0** pp);
};
ITaskManager* TaskManager();  // 0x0068f4d0
class SimpleRefCounted {
public:
    int AddRef() { return mnRefCount++ + 1; }
    int Release();
    void* mpVTable;
    int mnRefCount;
};
class IRefCounted_s0040_63d0 {
public:
    virtual int AddRef() = 0;
    virtual int Release() = 0;
};
struct Int2 { int x, y; };
struct EditorLoadRequest {
    ResourceKey_s0040_63d0 mKey;                          // 0x00
    Int2 mParams;                              // 0x0c
    intrusive_ptr_s0040_63d0<SimpleRefCounted> mpA;       // 0x14
    intrusive_ptr_s0040_63d0<SimpleRefCounted> mpB;       // 0x18
    intrusive_ptr_s0040_63d0<Task_s0040_63d0> mpTask;                // 0x1c
    intrusive_ptr_s0040_63d0<IRefCounted_s0040_63d0> mpOwner;        // 0x20
    intrusive_ptr_s0040_63d0<IRefCounted_s0040_63d0> mpListeners[3]; // 0x24
};
inline void ReadFloat(PropertyList_s0040_63d0* pList, unsigned int id, float& value) {
    Property_s0040_63d0* prop;
    if (pList && pList->GetProperty(id, prop) && prop->mnType == 0xd) value = *prop->GetValueFloat();
}
inline void ReadBool(PropertyList_s0040_63d0* pList, unsigned int id, bool& value) {
    Property_s0040_63d0* prop;
    if (pList && pList->GetProperty(id, prop) && prop->mnType == 1) value = *prop->GetValueBool();
}
inline void ReadInt(PropertyList_s0040_63d0* pList, unsigned int id, int& value) {
    Property_s0040_63d0* prop;
    if (pList && pList->GetProperty(id, prop) && prop->mnType == 9) value = *prop->GetValueInt32();
}
struct EditorData {
    EditorData();                                   // 0x00418120
    ~EditorData();                                  // 0x00418240
    EditorData& operator=(const EditorData& other); // 0x00406ac0
    bool mbValid;
    float mfScale;
    intrusive_ptr_s0040_63d0<PropertyList_s0040_63d0> mpPropList;
    unsigned int pad[(0xccc - 0xc) / 4];   // model/rigblock vectors etc.
};
struct EditorState { unsigned int pad[5]; bool mbDirty; };   // refcounted, +0x14 dirty flag
class ModelHolder { public: ModelHolder& operator=(EditorModel* p); EditorModel* mp; };  // 0x0041d980
class EditorLoader {
public:
    bool Load();
    unsigned int pad0[0x74/4];
    void* mp74;
    void* GetEditorContext() const { return mp74; }
    unsigned int pad78[(0x228-0x78)/4];
    ResourceKey_s0040_63d0 mKey;               // 0x228
    unsigned int pad234;
    unsigned short mFlags;          // 0x238
    unsigned short pad23a;
    intrusive_ptr_s0040_63d0<EditorState> mpState;  // 0x23c
    unsigned int pad240[(0x330-0x240)/4];
    intrusive_ptr_s0040_63d0<Task_s0040_63d0> mpTask;  // 0x330
    ModelHolder mModel;             // 0x334
    unsigned int pad338[(0x424-0x338)/4];
    bool mb424;
    bool mb425;
    unsigned short pad426;
    int mn428;
    EditorData mData;               // 0x42c
};
// ---- items of slice s004063d0 end

// ---- items of slice s0040aeb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const char kEditorAllocName[];   // 0x013eb430
extern const float kPartYaw;            // 0x015d1318
struct Vector3_s0040_aeb0 { float x, y, z; };
struct Matrix3_s0040_aeb0 { float m[9]; };
struct Modifier {
    uint16_t flags;      // +0x00
    uint16_t count;      // +0x02
    Vector3_s0040_aeb0  pos;        // +0x04
    float    scale;      // +0x10
    Matrix3_s0040_aeb0  rot;        // +0x14
    // 0x38 bytes total

    void AssignCopy(const Modifier& o);   // 0x0040ce80  (copy constructor)
    void Accumulate(const Modifier& o);   // 0x0040ccb0  (pos/rot/scale accumulate)
    void AccumulateScaled(const Modifier& o); // 0x0040cd80
    void PreRotateY(float angle);         // 0x006baa70
    void AssignFrom(const Modifier& o);   // 0x00537dc0  (cSPTransform::operator=)
};
class Property_s0040_aeb0 {
public:
    bool*  GetBool();         // 0x0041e920
    int*   GetUIntValue();    // 0x0041ea00 (PDB: GetUInt)
    float* GetFloat();        // 0x0041ea70

    uint16_t pad[9];          // +0x00
    uint16_t mnType;          // +0x12  (1 = bool, 0xa = int, 0xd = float)
};
class PropertyList_s0040_aeb0 {
public:
    virtual int  AddRef();                                    // +0x00 0x00432be0
    virtual int  Release();                                   // +0x04
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
    virtual bool GetProperty(uint32_t propertyID, Property_s0040_aeb0*& result);  // +0x24
};
void* __cdecl FUN_00f473a0(int size, const char* tag, int a, int b, int c, int d);
struct EditorRefSlot {               // { object pointer, released via its vtable or 0x453540 }
    void* mpObject;                  // +0x00
    void* GetRaw();                  // 0x0041d900
    void* GetParam();                // 0x0041d870
    void  Release();                 // 0x00453540
};
struct AutoRefPair {                 // { int id; void* object; } used by 0x0041cc20
    int   mId;
    void* mpObject;
};
struct RefVector_s0040_aeb0 {
    void*  mpBegin;                  // +0x00
    void*  mpEnd;                    // +0x04
    void*  mpCapacity;               // +0x08
    void*  mAllocator;               // +0x0c

    void  Construct(const void* tag);          // 0x00540470  (VSet ctor)
    bool  empty() const;                       // 0x00526430
    void  erase(void* first, void* last);      // 0x00426280
    void  resize(int n);                       // 0x0041ee90
    void  push_back(void* const& value);       // 0x0041ef20
    int   size() const { return ((char*)mpEnd - (char*)mpBegin) >> 2; }
    void* at(int i) const { return ((void**)mpBegin)[i]; }
};
struct ByteVector {
    uint8_t* mpBegin; uint8_t* mpEnd; uint8_t* mpCapacity; void* mAllocator;
    void push_back(const uint8_t& value);      // 0x00421080
};
struct ModifierVector {
    Modifier* mpBegin; Modifier* mpEnd; Modifier* mpCapacity; void* mAllocator;
    void push_back(const Modifier& value);     // 0x0041e460
};
struct Item7cVector {                          // baked-animation block, 0x7c bytes each
    void* mpBegin; void* mpEnd; void* mpCapacity; void* mAllocator;
    void push_back(const void* value);         // 0x0041f650
    int  size() const { return ((char*)mpEnd - (char*)mpBegin) / 0x7c; }
};
struct TripleVector {                          // three-float elements
    void* mpBegin; void* mpEnd; void* mpCapacity; void* mAllocator;
    void push_back(const Vector3_s0040_aeb0& value);      // 0x004206f0
    int   size() const { return ((char*)mpEnd - (char*)mpBegin) / 0xc; }
};
struct IntVector_s0040_aeb0 {
    int* mpBegin; int* mpEnd; int* mpCapacity; void* mAllocator;
    void push_back(const int& value);          // 0x00422380
    int  size() const { return mpEnd - mpBegin; }
};
struct PartAbilitySlot;                        // forward (ability object built per material)
struct Item24 {                                // element of the +0x3c8 vector
    RefVector_s0040_aeb0 mKeys;                           // +0x00
    uint32_t  mExtra;                          // +0x14
    void Destroy();                            // 0x00421190
};
struct Item24Vector {
    Item24* mpBegin; Item24* mpEnd; Item24* mpCapacity; void* mAllocator;
    void push_back(const Item24& value);       // 0x004215f0
};
struct IntMap {                                // eastl hash map, 0x18 bytes
    int* mpBuckets;                            // +0x00
    int* mpEndNode;                            // +0x04
    int  mBucketCount;                         // +0x08
    int  mPad0c;
    int  mPad10;
    int  mPad14;

    int* operator[](int* key);                 // 0x004210f0
};
struct AbilityMap {                            // map<PartAbilitySlot*, int> at +0x10d4
    int* mpBuckets; int* mpEndNode; int mBucketCount; int mPad0c; int mPad10; int mPad14;
    void Find(int** out, PartAbilitySlot** value);        // 0x00420b50
    int* operator[](PartAbilitySlot** key);               // 0x0041d1f0
};
struct PairIter { int* mpNode; int* mpEnd; };
struct PairMap {                               // intrusive node map used for materials
    int  mPad00;
    int* mpEndNode;                            // +0x04
    void Find(PairIter* out, int key);         // 0x00426d90
};
struct PartKeyVec {
    void* mpBegin; void* mpEnd; void* mpCapacity; void* mAllocator;
    void Init(int count);                      // 0x0041d0c0
    void Done();                               // 0x004209b0
};
struct TransformVec2 {                         // 0x30-byte transform array (0x41d510)
    void* mpBegin; void* mpEnd; void* mpCapacity; void* mAllocator;
    void Init(int count);                      // 0x0041d510
    void Done();                               // 0x004222a0
};
class MaterialManager {
public:
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
    virtual void* GetMaterial(int key);        // +0x28
};
struct EmbeddedState {
    uint32_t mPad00;
    uint32_t mPad04;
    uint32_t mFlags;                           // +0x08
    int D3D9GetShaderData(int which);          // 0x011edcf0
};
struct Material {
    uint32_t mPad00;
    EmbeddedState* mpState;                    // +0x04
};
struct StreamInfo {                            // copied by 0x401b80 (0x10 bytes)
    uint32_t mCount;                           // +0x00
    int*     mpBase;                           // +0x04
    uint16_t mStride0;                         // +0x08
    uint16_t mStride;                          // +0x0a
    void*    mpRef;                            // +0x0c

    void Init(const void* src);                // 0x00401b80
    int* Slot(int i) const { return (int*)((char*)mpBase + (uint32_t)mStride * i); }
};
struct TagEntry {
    uint32_t mPad00;
    uint32_t mPad04;
    void*    mpData;                           // +0x08
};
struct TagObject {
    uint32_t   mPad00;
    uint32_t   mPad04;
    TagEntry** mEntries;                       // +0x08
    int  FindTag(int tag);                     // 0x0077cad0
};
struct PartAbilitySlot {
    uint32_t  mPad00;                          // +0x00 (vptr)
    uint32_t  mPad04;                          // +0x04
    RefVector_s0040_aeb0 mAbilities;                      // +0x08
    void Ctor();                               // 0x0077d1d0
    void Push(int value);                      // 0x0077d970
};
struct ListAbility {
    uint32_t  mPad00;                          // +0x00 (vptr)
    uint32_t  mRefCount;                       // +0x04
    void Ctor();                               // 0x0040d160
};
struct SlotAbility {                           // 0x70-byte shader/ability wrapper
    uint32_t mPad[0x1c];
    void Ctor();                               // 0x0040d010
    void SetResource(int a, void* b);          // 0x0077cb10
    void SetSlot0(int a, int b);               // 0x00777a60
    void SetSlot1(int a, int b);               // 0x00777a80
};
class ResourceManager_s0040_aeb0 {
public:
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
    virtual void* Create(uint32_t a, uint32_t b, uint32_t c, int flag); // +0x1c
};
struct ResourceKey_s0040_aeb0 {                           // 12-byte rw resource key
    uint32_t mName;                            // +0x00
    uint32_t mType;                            // +0x04
    uint32_t mFlags;                           // +0x08
};
struct RefCounted_s0040_aeb0 {
    void Release();                            // 0x00402420
};
struct CreatureAbility {
    uint32_t mPad00;
    uint16_t mId;                              // +0x04
    uint16_t mValue;                           // +0x06
    void*    mpData;                           // +0x08
    void Ctor(uint16_t id, uint16_t value, void* data);  // 0x0040cfd0
};
struct Ability20 : CreatureAbility {           // 0x20-byte ability built for a stream entry
    uint32_t mField0c, mField10, mField14, mField18, mField1c;
};
struct AbilityData {                           // 0x2c-byte ability-data block
    void Ctor(const void* twoEntries);         // 0x0041d490
};
struct ColorKey {                              // 0x14-byte default colour key
    uint8_t type, r, g, b;
    float   a, b2, c, d;
    void Ctor();                               // 0x0040cf60
};
void  __cdecl VectorCtorIterator(void* dst, int elems, int count, void* ctor); // 0x00401930
struct PartModel;
struct EditorPart;
class PartManager {
public:
virtual void v0();
virtual void v1();
    virtual int  GetPartCount(PartModel* model);                        // +0x84
    virtual void GetData3(PartModel* model, int* out, int index);       // +0x88
    virtual void GetData2(PartModel* model, int* out);                  // +0x8c
    virtual void GetPartKeys(PartModel* model, int* out);               // +0x90
    virtual void* CreateInstance(PartModel* model, int arg);            // +0xa8
    virtual void GetKeys(PartModel* model, RefVector_s0040_aeb0* keys, Modifier* xf); // +0xf0
    virtual bool BuildKeys(PartModel* model, RefVector_s0040_aeb0* keys, void* a, void* b,
                           Modifier* xf);                               // +0x100
    virtual Modifier* GetKeyType(PartModel* model);                     // +0x108
};
struct EditorPart {
    uint32_t    mPad00[4];
    PartModel*  mpModel;                       // +0x10
    uint32_t    mPad14;
    PartManager* mpManager;                    // +0x18
    uint8_t     mPad1c[0x1d8 - 0x1c];
    float       mScale;                        // +0x1d8
    uint8_t     mPad1dc[0x3e0 - 0x1dc];
    int         mField3e0;                     // +0x3e0
    uint8_t     mPad3e4[0xdc8 - 0x3e4];
    uint32_t    mFlagsBits;                    // +0xdc8
    uint32_t    mFlagsDcc;                     // +0xdcc

    bool GetResourceKey(uint32_t* out);        // 0x0043bf20 (this = part)
};
struct PartModel {
    uint32_t   mPad00[2];
    Modifier   mTransform;                     // +0x08  (0x38 bytes)
    uint8_t    mPad40[0x90 - 0x40];
    PropertyList_s0040_aeb0* mpProperties;                // +0x90
};
struct Editor_s0040_aeb0;
struct EditorArg {
    void Finish(Editor_s0040_aeb0* self);                 // 0x00422280
};
struct Editor_s0040_aeb0 {
    uint32_t   mPad000[0x238 / 4];
    uint16_t   mFlags238;                      // +0x238
    uint8_t    mPad23a[0x338 - 0x23a];
    RefVector_s0040_aeb0  mAbilities;                     // +0x338  (index -> ability pointer)
    RefVector_s0040_aeb0  mPartKeys;                      // +0x34c
    ByteVector mEnabledFlags;                  // +0x360
    ModifierVector mComposedXforms;            // +0x374
    Item7cVector mBakedAnims;                  // +0x388
    RefVector_s0040_aeb0  mInstances;                     // +0x39c  (model instances)
    IntMap     mAbilityIndexMap;               // +0x3b0
    Item24Vector mEntries;                     // +0x3c8
    IntVector_s0040_aeb0  mEntryIndices;                  // +0x3dc
    uint8_t    mPad3f0[0x438 - 0x3f0];
    TripleVector mVarA;                        // +0x438
    uint8_t    mPad44c[0x510 - 0x44c];
    ModifierVector mVarB;                      // +0x510
    uint8_t    mPad524[0x8a8 - 0x524];
    ModifierVector mVarC;                      // +0x8a8
    uint8_t    mPad8bc[0x980 - 0x8bc];
    TripleVector mVarD;                        // +0x980
    uint8_t    mPad994[0xd18 - 0x994];
    IntVector_s0040_aeb0  mVarE;                          // +0xd18
    uint8_t    mPadd2c[0xd70 - 0xd2c];
    int        mThreshold;                     // +0xd70
    float      mScaleLimit;                    // +0xd74
    float      mScaleUsed;                     // +0xd78
    uint8_t    mPadd7c[0xd84 - 0xd7c];
    int        mTotalCost;                     // +0xd84
    int        mFirstFlag;                     // +0xd88
    RefVector_s0040_aeb0  mParts;                         // +0xd8c
    uint8_t    mPadd9c[0x10d4 - 0xd9c];
    AbilityMap mSlotIndexMap;                  // +0x10d4
    uint8_t    mPad10ec[0x10f4 - 0x10ec];
    uint32_t   mCurIndex;                      // +0x10f4
    int        mCounterA;                      // +0x10f8
    int        mCounterB;                      // +0x10fc

    void ProcessCurrentPart(void* arg);
    void ProcessSkipped(void* arg);             // 0x0040d2d0
};
int   __cdecl FUN_0071dd80(int key, int flag);                       // 0x0071dd80
void  __cdecl FUN_007387f0(int key);                                 // 0x007387f0
bool  __cdecl FUN_00756860(void* entry, PartManager* mgr, PartModel* model, void* instance);
void  __cdecl FUN_00401990(void* ability);                            // 0x00401990
int   __cdecl FUN_0071ddc0(void* ability, int a, int b, int c, int d); // 0x0071ddc0
void* __cdecl FUN_0067dd70();                                         // 0x0067dd70 (MaterialManager)
int   __cdecl FUN_00932e80(const char* name, uint32_t seed, int flag);  // 0x00932e80 (FNVHash)
int   __cdecl FUN_0077d710(int tagEntry);                             // 0x0077d710
ResourceManager_s0040_aeb0* __cdecl FUN_0067dd60();                              // 0x0067dd60
void  __cdecl FUN_006c1ae0(void* baker, void* param);                 // 0x006c1ae0
void  __cdecl FUN_00409930(void* p);                                  // 0x00409930
void  __cdecl FUN_00472540(void* p);                                  // 0x00472540
void  __cdecl FUN_004a9b10(void* p);                                  // 0x004a9b10
void  __cdecl FUN_0041cc20(void* p, void* value);                     // 0x0041cc20
void  __cdecl FUN_0041ccc0(void* p, void* value);                     // 0x0041ccc0
bool  __cdecl FUN_006a0ae0(PropertyList_s0040_aeb0* props, uint32_t id, int* count, void** base);
bool  __cdecl FUN_006a0c30(PropertyList_s0040_aeb0* props, uint32_t id, int* count, void** base);
bool  __cdecl FUN_006a1250(PropertyList_s0040_aeb0* props, uint32_t id, float* out); // 0x006a1250
bool  __cdecl FUN_0040cf10(PropertyList_s0040_aeb0* props, uint32_t id, float* out); // 0x0040cf10
void  __cdecl FUN_0041eb80(void* p);                                  // 0x0041eb80
void  __cdecl FUN_00732270(void* src, void* out);                     // 0x00732270
Modifier* __cdecl FUN_0043d220(EditorPart* part);                     // 0x0043d220
// ---- items of slice s0040aeb0 end

// ---- items of slice s0040ccb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3_s0040_ccb0 {
    float x, y, z;
    Vector3_s0040_ccb0() {}
    Vector3_s0040_ccb0(const Vector3_s0040_ccb0& o) : x(o.x), y(o.y), z(o.z) {}
    void Transform(const struct Matrix3_s0040_ccb0& m);
    Vector3_s0040_ccb0& operator=(const Vector3_s0040_ccb0& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
struct Matrix3_s0040_ccb0 {
    struct Data { float f[9]; } d;
    Matrix3_s0040_ccb0& operator=(const Matrix3_s0040_ccb0& o) { d = o.d; return *this; }
    Matrix3_s0040_ccb0() {}
    Matrix3_s0040_ccb0(const Matrix3_s0040_ccb0& o);   // 0x0041cb40 (out of line copy ctor)
};
Vector3_s0040_ccb0 operator*(const Vector3_s0040_ccb0& v, const float& s);           // 0x0041dca0
Vector3_s0040_ccb0 operator*(const Vector3_s0040_ccb0& v, const Matrix3_s0040_ccb0& m);         // 0x0041daf0
Matrix3_s0040_ccb0 operator*(const Matrix3_s0040_ccb0& a, const Matrix3_s0040_ccb0& b);         // 0x0041de20
Vector3_s0040_ccb0& operator*=(Vector3_s0040_ccb0& a, const float& s);               // 0x0041dba0
inline void Vector3_s0040_ccb0::Transform(const Matrix3_s0040_ccb0& m) { *this = *this * m; }
struct ColorKey_s0040_ccb0 {
    uint8_t type;       // +0
    uint8_t r, g, b;    // +1..+3
    float a;            // +4
    float b2;           // +8
    float c;            // +0xc
    float d;            // +0x10
    ColorKey_s0040_ccb0();  // 0x0040cf60 (ColorKey::ColorKey_s0040_ccb0)
};
struct AtomicRefCounted_s0040_ccb0 { void Release(); };   // 0x00402420
struct RefPtr_s0040_ccb0 {
    AtomicRefCounted_s0040_ccb0* mpObject;
    RefPtr_s0040_ccb0() : mpObject(0) {}
    ~RefPtr_s0040_ccb0() { if (mpObject) mpObject->Release(); }
};
struct RefSlot_s0040_ccb0 {
    int key;
    RefPtr_s0040_ccb0 mpRef;
    int value[2];
};
struct SlotTable {
    int count;
    RefSlot_s0040_ccb0 slots[6];
    SlotTable() : count(0) {}
};
class CreatureAbility_s0040_ccb0 {
public:
    CreatureAbility_s0040_ccb0(uint16_t a, uint16_t b, void* c)
        : mId(a), mValue(b), mpData(c) {}
    virtual ~CreatureAbility_s0040_ccb0() {}
    uint16_t mId;       // +4
    uint16_t mValue;    // +6
    void* mpData;       // +8
};
class SlotAbility_s0040_ccb0 : public CreatureAbility_s0040_ccb0 {
public:
    SlotAbility_s0040_ccb0();  // 0x0040d010 (SlotAbility::SlotAbility_s0040_ccb0)
    static void operator delete(void* p) { EASTL_allocator_deallocate(p); }
    SlotTable mSlots;   // +0x0c
};
struct Allocator { const char* mpName; uint32_t mFlags; Allocator() {} };
template <class T>
struct VectorBase_s0040_ccb0 {
    T* mpBegin; T* mpEnd; T* mpCapacity;
    Allocator mAllocator;
    VectorBase_s0040_ccb0() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~VectorBase_s0040_ccb0();    // 0x0050ea50 frees the storage
};
struct OpaqueVector {
    void* mpBegin; void* mpEnd; void* mpCapacity;
    Allocator mAllocator;
    OpaqueVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~OpaqueVector();
};
struct OpaqueVectorA : OpaqueVector {
    ~OpaqueVectorA();   // 0x0041f760
};
struct OpaqueVectorB : OpaqueVector {
    ~OpaqueVectorB();   // 0x0041f8e0
};
struct OpaqueVectorC : OpaqueVector {
    ~OpaqueVectorC();   // 0x004b5440
};
struct Entry20_s0040_ccb0 { uint32_t data[5]; };
template <class T>
struct vector_s0040_ccb0 : VectorBase_s0040_ccb0<T> {
    vector_s0040_ccb0() {}
    ~vector_s0040_ccb0() {
        for (T* p = this->mpBegin; p < this->mpEnd; ++p)
            p->~T();
    }
};
struct AtomicInt {
    volatile long mValue;
    AtomicInt(long v) {
        long unused;   // reproduces an extra frame slot of the original
        Set(v);
    }
    void Set(long v) { _InterlockedExchange(&mValue, v); }
};
class RefCountedAbility {
public:
    RefCountedAbility() : mRefCount(0) {}
    virtual ~RefCountedAbility() {}
    AtomicInt mRefCount;   // +4
};
class ListAbility_s0040_ccb0 : public RefCountedAbility {
public:
    ListAbility_s0040_ccb0();  // 0x0040d160 (ListAbility::ListAbility_s0040_ccb0)
    static void operator delete(void* p) { EASTL_allocator_deallocate(p); }
    OpaqueVectorA mA;          // +0x08
    OpaqueVectorB mB;          // +0x1C
    vector_s0040_ccb0<Entry20_s0040_ccb0> mEntries;  // +0x30
    OpaqueVectorC mC;          // +0x44
};
// ---- items of slice s0040ccb0 end

// ---- items of slice s0040d2d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int g_KeyA;  // 0x13eb2cc
extern int g_KeyB;  // 0x13eb2d0
extern int g_KeyC;  // 0x13eb2d4
extern int g_KeyD;  // 0x13eb2c4
extern int g_KeyE;  // 0x13eb2c8
struct PropVal {
    unsigned char data[16];
    uint16_t flags;
    uint16_t type;
    PropVal() : flags(0), type(0) {}
};
struct PropInfo { char pad[0x12]; short typeId; };
struct IPropertyBag {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void SetProperty(uint32_t id, void* val);          // +0x14
    virtual void v6();
    virtual bool HasProperty(uint32_t id);                      // +0x1c
    virtual void v8();
    virtual bool GetPropertyInfo(uint32_t id, PropInfo** out); // +0x24
};
struct IModelData { virtual int GetPartRoot(); };               // slot at +4
struct RangeVec_s0040_d2d0 { int* begin; int* end; };
struct KeyedFloat { uint32_t key; float value; };
struct KeyedFloatList { KeyedFloat* first; KeyedFloat* last; };
bool __fastcall IsEditorMode(void* self);                                  // 0x526430
void __fastcall InitEmptyA(void* p);                                       // 0x409930
void __cdecl    LocalCleanup1();                                           // 0x472540
void __cdecl    LocalCleanup2();                                           // 0x4a9b10
void __cdecl    LocalCleanup3();                                           // 0x4ad330
void __fastcall FinishRefresh(void* self);                                 // 0x422360
void __fastcall WrapInt(void* p);                                          // 0x422eb0
void __cdecl    FreePropVal(int);                                          // 0x93db80
float* __cdecl  GetDefaultScale();                                         // 0x41ea70
void __cdecl    ApplyScale(float);                                         // 0x409b30
void __cdecl    WrapArray(int, int, void* base, int stride, int count);    // 0x93dd80
void __cdecl    InitBool(char*);                                           // 0x540470
void __fastcall CollectKeyedFloats(void* model, KeyedFloatList* out);      // 0x4333c0
void __fastcall WrapFloat(float* p);                                       // 0x428060
void __cdecl    FreeKeyedFloats();                                         // 0x45daf0
void __fastcall WrapPtr(void* p);                                          // 0x4279d0
int  __fastcall GetPartInfo(int part, void* tmp);                          // 0x41df50
void __cdecl    PostPart();                                                // 0x4237d0
void __fastcall WrapKey(void* p);                                          // 0x427fd0
// ---- items of slice s0040d2d0 end

// ---- items of slice s00410d70 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct MessageManager_s0041_0d70 {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
    virtual void Post3(uint32_t id, uint32_t a, uint32_t b);       // +0x14
    virtual void Post4(uint32_t id, uint32_t a, uint32_t b, uint32_t c); // +0x18
};
MessageManager_s0041_0d70* __cdecl GetMessageManager();            // 0x0067dcc0
struct CursorSource {          // FUN_0067dd40; slot 47 (+0xbc) fills a pair of ids
virtual void p0();
virtual void p1();
virtual void p2();
virtual void p3();
virtual void p4();
virtual void p5();
virtual void p6();
virtual void p7();
virtual void p8();
virtual void p9();
virtual void p10();
virtual void p11();
virtual void p12();
virtual void p13();
virtual void p14();
virtual void p15();
virtual void p16();
virtual void p17();
virtual void p18();
virtual void p19();
virtual void p20();
virtual void p21();
virtual void p22();
virtual void p23();
virtual void p24();
virtual void p25();
virtual void p26();
virtual void p27();
virtual void p28();
virtual void p29();
virtual void p30();
virtual void p31();
virtual void p32();
virtual void p33();
virtual void p34();
virtual void p35();
virtual void p36();
virtual void p37();
virtual void p38();
virtual void p39();
virtual void p40();
virtual void p41();
virtual void p42();
virtual void p43();
virtual void p44();
virtual void p45();
virtual void p46();
    virtual void GetCurrent(uint32_t* out);
    virtual void q48();
};
CursorSource* __cdecl GetCursorSource();                // 0x0067dd40
struct SlotInfo { uint32_t pad[3]; uint16_t mX; uint16_t mY; };   // mX at +0xc, mY at +0xe
struct SlotTable_s0041_0d70 {             // FUN_0067dda0; slot 6 (+0x18) looks an entry up by key
virtual void p0();
virtual void p1();
virtual void p2();
virtual void p3();
virtual void p4();
virtual void p5();
    virtual SlotInfo* Lookup(uint32_t lo, uint32_t hi);
};
SlotTable_s0041_0d70* __cdecl GetSlotTable();                      // 0x0067dda0
struct Callback {
    uint32_t d[5];
    Callback(const Callback& o);                        // 0x0041eae0
};
struct Request_s0041_0d70 {               // object returned by FUN_00761420
    int Open(int a, int b, uint32_t* out);              // 0x011ef750
    int GetHandle(int a);                               // 0x011f0000
    void Close(uint32_t* h);                            // 0x011ef880
};
struct SlotRef {
    void Bind(uint32_t h, int handle, int c);           // 0x011f0440
};
struct FlagCheck { bool IsSet(); };                     // 0x00526430
Request_s0041_0d70* __cdecl CreateRequest(uint16_t x, uint16_t y, int a, int b, int c);   // 0x00761420
void __cdecl DestroyRequest(Request_s0041_0d70* r);                                       // 0x00761110
void __cdecl SubmitCallback(Callback cb, Request_s0041_0d70* r, int arg);                 // 0x0046f2a0
struct EditorHost {            // object with vtable slot 7 (+0x1c) not needed here
    uint8_t pad0[0x238];
    uint16_t mFlags;           // +0x238
    uint8_t pad1[0x338 - 0x23a];
    uint8_t mCallbackObj[0x400 - 0x338];
    int mCallbackArg;          // +0x400
    uint8_t pad2[0x424 - 0x404];
    bool mbPending;            // +0x424
    bool mbHaveOwner;          // +0x425
    uint8_t pad3[2];
    int mOwner;                // +0x428
    bool OnUpdate(int unused);
};
struct OwnerHolder {                 // *(this+0x3f0) points at one of these; its first field is the live object
    struct Target { virtual void v(); } * mpObj;
};
void __fastcall ReleaseHolder(void* p);                // 0x0040f360 (thiscall)
struct RangeVector {                 // 16-byte elements, pointer at +0xc of each
    uint8_t* mpBegin;
    uint8_t* mpEnd;
    uint8_t* mpCap;
    void DestroyRange(void* first, void* last);        // 0x00548690
    int Count() { return (mpEnd - mpBegin) >> 4; }
    void* PtrAt(int i) { return *(void**)(mpBegin + i * 16 + 0xc); }
};
struct Timer {                       // 0x93a2e0 / 0x93a3a0 helpers
    uint8_t pad[0x14];
    float mScale;
    void Update();                   // 0x0093a2e0
    int64_t Read();                  // 0x0093a3a0
};
struct TimeSource {                  // FUN_0067dd40, slot 10 (+0x28)
virtual void p0();
virtual void p1();
virtual void p2();
virtual void p3();
virtual void p4();
virtual void p5();
virtual void p6();
virtual void p7();
virtual void p8();
virtual void p9();
    virtual void Tick();
};
TimeSource* __cdecl GetTimeSource();                   // 0x0067dd40
struct EditorHost2 {
    void** vp;                                          // virtual slot 28 (+0x70) = SetPrebaked
    uint8_t pad0[0x228 - 4];
    uint8_t mSub[0x10];                                 // +0x228
    uint16_t mFlags;                                    // +0x238
    uint8_t pad1[2];
    uint32_t mpResource;                                // +0x23c
    uint8_t pad2[0x3f0 - 0x240];
    OwnerHolder* mpHolder;                              // +0x3f0
    uint8_t pad3[0x410 - 0x3f4];
    RangeVector mVec;                                   // +0x410
    uint8_t pad4[0x1114 - 0x41c];
    int mFrameCount;                                    // +0x1114
    uint8_t pad5[0x112c - 0x1118];
    int mBakeCount;                                     // +0x112c
    float mTotalTime;                                   // +0x1130
    float mLastTime;                                    // +0x1134
    Timer mTimerA;                                      // +0x1138
    Timer mTimerB;                                      // +0x1150
    bool OnFrame(int unused);
    void SubStep(void* sub, float b, float a);          // 0x004111e0
    void Finish(int arg);                               // 0x00411890
};
// ---- items of slice s00410d70 end

// ---- items of slice s004111e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SendSel {
extern void* __cdecl EASTL_allocator_allocate(uint32_t size, const char* name, uint32_t a, uint32_t b, uint32_t c, uint32_t d);
}
namespace SendSel {
struct Variant_s0041_11e0 {
    uint8_t data[16];
    uint16_t flags;
    uint16_t type;
    void SetFlags(uint16_t f) { flags = f; }
    void SetType(uint16_t t) { type = t; }
    void Construct(const bool* b);  // 0x0093dd80 (SendSel::Variant::Construct)
    void Free(int);
    Variant_s0041_11e0(const bool* b) { SetFlags(0); SetType(0); SetType(1); SetFlags(2); Construct(b); }
    ~Variant_s0041_11e0() { if (flags & 4) Free(0); }
};
}
namespace SendSel {
struct Id {
    uint32_t raw;
    uint32_t Type() const { return (raw >> 16) & 0xff; }
    void SetClass(uint32_t v) { raw = (raw & 0xe0ffffff) | ((v & 0x1f) << 24); }
};
}
namespace SendSel {
inline Id WithClass(Id i, uint32_t c) { i.SetClass(c); return i; }
}
namespace SendSel {
inline uint32_t TypeOf(uint32_t raw) { return (raw >> 16) & 0xff; }
}
namespace SendSel {
struct Slots {
    struct Slot { uint32_t v, pad; } slot[5];
    uint32_t id30;
    uint32_t pad34;
    void Set(int i, uint32_t v) { slot[i].v = v; }
    void SetF(int i, float v) { *(float*)&slot[i].v = v; }
};
}
namespace SendSel {
struct Msg_s0041_11e0 {
    void* vtbl;
    uint32_t pad4;
    Slots s;
    uint32_t f38;
    uint32_t pad3c;
    Msg_s0041_11e0(uint32_t id);        // 0x423110
    void Base2Init();        // 0x40fd50
    void Destroy();          // 0x421cf0
    void Set(int i, uint32_t v) { s.Set(i, v); }
    void SetF(int i, float v) { s.SetF(i, v); }
};
}
namespace SendSel {
struct MsgMgr {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
    virtual void Post(uint32_t id, Msg_s0041_11e0* m, uint32_t a, uint32_t b);
};
}
namespace SendSel {
struct Target {
    virtual void v0();
    virtual void Release();                         // +4
virtual void v2();
virtual void v3();
virtual void v4();
    virtual void SetProp(uint32_t id, Variant_s0041_11e0* v);  // +0x14
    virtual void v6();
    virtual bool Has(uint32_t id);                  // +0x1c
};
}
namespace SendSel {
struct TRef {
    Target* p;
    Target** Out();                 // 0x41d870
    bool Has(uint32_t id) { return p->Has(id); }
    void SetBool(uint32_t id, bool b) { Variant_s0041_11e0 v(&b); p->SetProp(id, &v); }
};
}
namespace SendSel {
struct Lookup {
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
    virtual void Find(uint32_t a, uint32_t b, Target** out);   // +0x2c
};
}
namespace SendSel {
struct Params { uint32_t a, b, c; };
}
namespace SendSel {
extern MsgMgr* __cdecl GetMsgMgr();
}
namespace SendSel {
extern Lookup* __cdecl GetLookup();
}
namespace SendSel {
extern void __cdecl FreeTarget(Target* t, int);
}
namespace SendSel {
struct Panel_s0041_11e0 {
    uint8_t pad0[0x234];
    uint32_t arg234;
    uint16_t flags238;
    uint8_t pad23a[0x258 - 0x23a];
    uint8_t sentFlag;

    void PostSelectionMessages(Params* p, float f1, float f2);
};
}
namespace SendSel {
#define NEW_HMSG(var, idv) \
    Msg_s0041_11e0* tmp##var; \
    void* raw##var = EASTL_allocator_allocate(0x40, "Editor", 0, 0, 0, 0); \
    if (raw##var) { \
        Slots* sl = (Slots*)((char*)raw##var + 8); \
        sl->id30 = idv; \
        ((Msg_s0041_11e0*)raw##var)->Base2Init(); \
        ((Msg_s0041_11e0*)raw##var)->vtbl = (void*)0x13eb90c; \
        ((Msg_s0041_11e0*)raw##var)->vtbl = (void*)0x13eb844; \
        ((Msg_s0041_11e0*)raw##var)->f38 = 0; \
        tmp##var = (Msg_s0041_11e0*)raw##var; \
    } else tmp##var = 0; \
    var = tmp##var;
}
namespace ResetSel {
struct TmpA { uint32_t d[12]; TmpA* Init(); void Fini(); };
}
namespace ResetSel {
struct TmpB { uint32_t d[0xdd0/4]; TmpB* Init(); void Fini(); };
}
namespace ResetSel {
struct Preloader_s0041_11e0 { void Reset(); };
}
namespace ResetSel {
struct Obj330 { void Release(int); void Free(); };
}
namespace ResetSel {
struct SPtr {
    Obj330* p;
    Obj330* Get() { return p; }
    Obj330* operator->() { return p; }
    void Reset() {
        if (p) {
            Obj330* o = p;
            p = 0;
            if (o) o->Free();
        }
    }
};
}
namespace ResetSel {
struct Sel { void Set(const TmpA*); };
}
namespace ResetSel {
struct PtrHolder { void Set(const TmpB*); };
}
namespace ResetSel {
struct Msg_s0041_11e0 {
    void* vtbl;
    uint32_t pad4;
    struct Slot { uint32_t v, pad; } slot[5];
    uint32_t id30;
    uint32_t pad34;
    uint32_t f38;
    uint32_t pad3c;
    Msg_s0041_11e0(uint32_t id);
    static void* operator new(unsigned size, const char* name);
    void Set(int i, uint32_t v) { slot[i].v = v; }
};
}
namespace ResetSel {
struct BMsg : Msg_s0041_11e0 {
    BMsg(uint32_t id) : Msg_s0041_11e0(id) { vtbl = (void*)0x13eb844; f38 = 0; }
};
}
namespace ResetSel {
extern void* __cdecl EASTL_allocator_allocate(uint32_t size, const char* name, uint32_t a, uint32_t b, uint32_t c, uint32_t d);
}
namespace ResetSel {
inline void* Msg_s0041_11e0::operator new(unsigned size, const char* name) { return EASTL_allocator_allocate(size, name, 0, 0, 0, 0); }
}
namespace ResetSel {
struct MsgMgr {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
    virtual void Post(uint32_t id, Msg_s0041_11e0* m, uint32_t a, uint32_t b);
};
}
namespace ResetSel {
struct Panel_s0041_11e0 {
    uint8_t pad0[0x228];
    uint32_t selId;      // 0x228
    uint32_t arg22c;
    uint32_t arg230;
    uint32_t arg234;
    uint8_t pad238[0x258 - 0x238];
    uint8_t sentFlag;    // 0x258
    uint8_t flag259;
    uint8_t pad25a[2];
    Preloader_s0041_11e0 preloader; // 0x25c
    uint8_t pad25d[0x2c4 - 0x25d];
    uint8_t flag2c4;
    uint8_t pad2c5[0x330 - 0x2c5];
    SPtr obj330;      // 0x330

    void CommitAndReset(bool flag);
};
}
namespace ResetSel {
extern MsgMgr* __cdecl GetMsgMgr();
}
// ---- items of slice s004111e0 end

// ---- items of slice s00412900 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace A {
struct Vec3 { float x, y, z; };
}
namespace A {
Vec3* __cdecl Vec3Sub(Vec3* out, const Vec3* a, const Vec3* b);                       // 41db10
}
namespace A {
Vec3* __cdecl Vec3SubScaled(Vec3* out, const Vec3* a, const Vec3* b, const float* s); // 41db10 (4-arg call site)
}
namespace A {
Vec3* __cdecl Vec3Unary(Vec3* out, const Vec3* v);                                    // 41dca0
}
namespace A {
Vec3* __cdecl Vec3Add(Vec3* out, const Vec3* a, const Vec3* b);                       // 41dc10
}
namespace A {
void  __cdecl Vec3Normalize(Vec3* v, const Vec3* ref);                                // 41ddb0
}
namespace A {
float __cdecl Vec3Length(const Vec3* v);                                              // 413d60
}
namespace A {
float __cdecl Vec3Length2(const Vec3* v);                                             // 40ae50
}
namespace A {
Vec3* __cdecl Vec3Transform(Vec3* out, const Vec3* v, const Vec3* m);                 // unchecked helper
}
namespace A {
Vec3* __cdecl Vec3Curve(Vec3* out, const Vec3* a, const Vec3* b, const Vec3* c, const Vec3* d, float t); // 4224b0
}
namespace A {
Vec3* __cdecl Vec3Blend(Vec3* out, const Vec3* a, const Vec3* b, float t, const float* w, const Vec3* c); // 413cc0
}
namespace A {
void  __cdecl GetFloatProp(int obj, uint32_t id, float* v);                           // 40cf10
}
namespace A {
void  __cdecl GetIntProp(int obj, uint32_t id, int* v);                               // 6a12a0
}
namespace A {
int*  __cdecl FindFirst(int* begin, int* end, const int* key);                        // 422430
}
namespace A {
struct PointList { char pad[8]; char* first; char* last; };
}
namespace A {
struct Path {
    int AddPoint(const Vec3* pos, float w, float width, uint32_t color);   // 4fcc20
    void Link(int a, int b, float w, uint32_t color);                      // 4fcca0
};
}
namespace A {
struct Node {                 // sizeof 0x8c
    uint16_t pad0;
    int16_t  parent;          // 0x04
    uint16_t flags;           // 0x08 (low byte at 8, type byte at 0xb)
    char     pad1[0x30 - 0x0a];
    Vec3     axis;            // 0x30
    char     pad2[0x54 - 0x3c];
    Vec3     pos;             // 0x54
    char     pad3[0x70 - 0x60];
    float    radius;          // 0x70
    float    t;               // 0x74
    float    w0;              // 0x78
    float    w1;              // 0x7c
    char     pad4[0x84 - 0x80];
    int      keyB;            // 0x84
    int      keyA;            // 0x88
};
}
namespace A {
struct Builder {
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
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
    virtual int LookupEffect(int a, int b);   // slot 0x58/4 = 22
    char pad[0x90 - 4 - 23 * 4 + 0];          // up to 0x90 -> fields at 0x90.. (approx)
    PointList tracks;   // 0x90 (param_1[0x24])
    char* tracksEnd;    // 0x94
    char pad2[0x88 - 0x08 + 0];
    int  dataBase;      // 0xa4 (param_1[0x29])
    Path* path;         // 0x88 in Ghidra's index 0x22 (approx)
    int BuildRope(Node* nodes, int count, int idx, uint32_t colA, uint32_t colB, uint32_t colMid, int prev);
};
}
namespace A {
static const float kLinkW = 0.3f;     // 0x3e99999a
}
namespace A {
static const float kOne_s0041_2900   = 1.0f;
}
// ---- items of slice s00412900 end

// ---- items of slice s00417210 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct WString_s0041_7210 {
    wchar_t* cur; wchar_t* begin; wchar_t* end; int pad[2];
    wchar_t buf[386];
    inline wchar_t* Data() { return cur; }
};
void __fastcall WString_Init(WString_s0041_7210* s);   // 0x0041d600
void __fastcall WString_Free(WString_s0041_7210* s);   // 0x004292a0
struct ResKey { uint32_t instance, type, group; };
struct KeyVec_s0041_7210 { ResKey* first; ResKey* last; inline ResKey* At(int i) { return first + i; } };
struct Handler {
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
    virtual const wchar_t* GetExt(wchar_t* name);          // +0x28
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
    virtual bool GetName(ResKey* k, wchar_t* out);         // +0x64
};
struct Manager_s0041_7210 {
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
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
    virtual int FindHandler(ResKey* k);                    // +0x58
};
Manager_s0041_7210* GetManager_s0041_7210();                                      // 0x0067dcd0
int __cdecl swprintf_like(void* dst, const wchar_t* fmt, ...); // 0x004c0530
void __cdecl CreateDirs(wchar_t* path);                     // 0x00932960
Handler* __cdecl LookupHandler(int id);                     // 0x00422950
bool __cdecl FileExists(wchar_t* path);                     // 0x00931fa0
void __cdecl SetFileAttr(wchar_t* path, int a, int b);      // 0x009320a0
void __cdecl CopyFileTo(const wchar_t* src, wchar_t* dst, int overwrite); // 0x00932030
void __cdecl RunProcess(const wchar_t* exe, const wchar_t* verb, const wchar_t* args, int wait); // 0x006bb4b0
void __cdecl RunProcess(const wchar_t* exe, const wchar_t* a, const wchar_t* b, const wchar_t* c, int wait); // 0x006bb4b0
struct WStringOps {
    int __thiscall Find(int ch, int pos);                   // 0x004f6ab0
    void __thiscall Erase(int pos, int n);                  // 0x004228e0
    void __thiscall Insert(int pos, const wchar_t* s);      // 0x00422880
};
// ---- items of slice s00417210 end

// ---- items of slice s00419780 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct ThreadedObject_s0041_9780 {
    void* vtbl;
    long  refCount;
    void AddRef() { _InterlockedIncrement(&refCount); }
    void Release();          // Resource::ThreadedObject::Release @ 0x00404F90
};
struct ObjectRef {
    ThreadedObject_s0041_9780* p;
    ObjectRef& operator=(const ObjectRef& o) {
        if (o.p != p) {
            ThreadedObject_s0041_9780* old = p;
            if (o.p) o.p->AddRef();
            p = o.p;
            if (old) old->Release();
        }
        return *this;
    }
};
struct ResultList {
    ObjectRef* items;
    int        count;
    ResultList(unsigned char* tag);      // @ 0x00540470
    void Destroy();                      // @ 0x0041EB80
    void Assign(ObjectRef* items, int count);  // @ 0x00426280
    bool IsEmpty();                      // @ 0x00526430
    void Release2(ObjectRef* items, int count); // @ 0x004243E0
    void Free();                         // @ 0x00425990
    ObjectRef* begin() { return items + 0; }
};
struct Transform_s0041_9780 { Transform_s0041_9780(); };       // @ 0x00409930
struct Accumulator { uint32_t data[0x38 / 4]; void Add(void* v); };   // @ 0x00537DC0
struct Modifier_s0041_9780 : Accumulator { void AccumulateScaled(void* v); };    // @ 0x0040CD80
struct ModelBehavior {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v0a();
    virtual void v0b();
    virtual void v0c();
    virtual void v0d();
    virtual void v0e();
    virtual void v0f();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v1a();
    virtual void v1b();
    virtual void Prepare(void* e, int id, int mode, float f, int z);
    virtual void SetValue(void* e, int id, float v, int z);
    virtual void SetExtra(void* e, int id, float v, int z);
    virtual void v1f();
    virtual bool GetRange(void* e, int id, float* lo, float* hi, int z);
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v2a();
    virtual void v2b();
    virtual void v2c();
    virtual void v2d();
    virtual void v2e();
    virtual void v2f();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v3a();
    virtual void v3b();
    virtual void v3c();
    virtual void QueryResults(void* e, ResultList* out);
    virtual void v3e();
    virtual void v3f();
    virtual bool Evaluate(void* e, ResultList* list, int a, int b, Transform_s0041_9780* t);
    virtual void v41();
    virtual int  GetBaseWeight(void* e);
};
struct ModelRecord {          // sizeof == 0x8c
    char     pad0[8];
    uint16_t flags;           // +8   (bit0: skip, bit3: already evaluated)
    uint8_t  hasAnimation;    // +0xa
    char     pad1[0x8c - 0xb];
};
struct ModelRecordVector {    // at model+0x98
    ModelRecord* begin;
    ModelRecord* end;
    int size() const { return (int)(end - begin); }
};
struct ModelData_s0041_9780 {
    char pad0[0x98];
    ModelRecordVector records;      // +0x98
};
struct SceneRegistry { void Register(void* arrays); };   // 0x0041EBE0
struct Scene {
    char          pad0[8];
    ModelData_s0041_9780*    model;            // +8
    char          pad0c[0xa4 - 0x0c];
    SceneRegistry registry;         // +0xa4
};
void SubmitScene(Scene* s, void* a, void* b, uint32_t x, uint32_t y, void* cb);   // 0x00469BB0 cdecl
struct PropertyList;                // opaque
struct Entity {                      // per-model runtime entry (table element)
    ModelBehavior* behavior;         // +0
    char     pad4[4];
    char     transformSlot[0x88];    // +8   (inline modifier data)
    PropertyList* props;             // +0x90
};
struct IntSlot   { void Set(void* p); };             // 0x0041D8B0
struct ObjSlot   { void Set(void* p); };             // 0x004535D0
struct TargetPtr { void operator=(void* p); };       // 0x0041CC60
struct RequestState;                          // forward
struct ArrayBlock {
    ObjectRef*   refs;               // +0x00
    char         pad04[0x24];
    Accumulator* weights;            // +0x28 (0x38-byte elements)
    char         pad2c[0x0c];
    Modifier_s0041_9780*    modifiers;          // +0x3c (0x38-byte elements)
    char         pad40[0x10];
    IntSlot*     intSlots;           // +0x50
    char         pad54[0x0c];
    ObjSlot*     objSlots;           // +0x64
    char         pad68[0x0c];
    TargetPtr*   targets;            // +0x78
};
struct Updater;
struct RequestState {
    char pad0[0x1c];
    int  resumeIndex;                       // +0x1c
    bool Finish(Updater* u);                // 0x00422A70
    bool Abort(Updater* u);                 // 0x00422A50
    void Queue(Updater* u);                 // 0x00422A90
};
struct Updater {
    char        pad0[0x18];
    uint32_t    flags18;                    // +0x18
    char        pad1c[4];
    uint16_t    flags20;                    // +0x20
    char        pad22[2];
    Scene*      scene;                      // +0x24
    char        pad28[4];
    int         budget;                     // +0x2c
    ArrayBlock* arrays() { return (ArrayBlock*)((char*)this + 0x30); }
    char        pad30[0xbc - 0x30];
    Entity**    entities;                   // +0xbc
    bool UpdateModels(RequestState* st);    // 0x00419780
    void Dispatch(void* cb);                // 0x00419FF0
};
inline uint32_t SetByte1(uint32_t v, uint32_t b) {
    return (v & 0xffff00ffu) | ((b & 0xffu) << 8);
}
// ---- items of slice s00419780 end

// ---- items of slice s0041a0c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* vtEditorResource[];       // 0x013eb938
extern void* vtAbility[];              // 0x013ef094
extern void* vtMsg[]; extern void* vtBehavior[];
void* __fastcall MemberInit(void* m);   // 0x0041d3c0
void __fastcall MemberDtor(void* m);   // 0x004b5440
void __cdecl Dealloc(void*);           // 0x00f47380 EASTL_allocator_deallocate
struct P { virtual int AddRef() = 0; virtual int Release() = 0; virtual void* Destroy(unsigned flags); /* 0x00517400 */ };
struct A_s0041_a0c0 : P {};
struct RefCount { long rc; RefCount() { _InterlockedExchange(&rc, 0); } };
struct Ability { virtual void* Destroy(unsigned flags); /* 0x0041d780 */ RefCount rc; };
struct D : A_s0041_a0c0, Ability {
    char member[0xb8];
    D();
    virtual int AddRef();   // 0x00461290
    virtual int Release();  // 0x00472970
    virtual void* Destroy(unsigned flags);
    virtual int Handle(void* argument);  // 0x00561150
};
template<int N> inline void ReserveFrame(){ uint32_t frame[N]; }
struct ResKey_s0041_a0c0 {
    uint32_t a : 8;
    uint32_t type : 8;     // bits 8..15: 0x71 / 0x62
    uint32_t b : 8;
    uint32_t c : 5;        // bits 24..28: 1 for the third key
    uint32_t d : 3;
    inline ResKey_s0041_a0c0 WithType(int t) const { ResKey_s0041_a0c0 r = *this; r.type = t; return r; }
    inline ResKey_s0041_a0c0 WithC(int v) const { ResKey_s0041_a0c0 r = *this; r.c = v; return r; }
};
struct PropList_s0041_a0c0;
struct Value { uint32_t a, b, c; };
struct PropList_s0041_a0c0 {
    virtual void v0();
    virtual void Release();          // +4
virtual void v2();
virtual void v3();
    virtual void SetProp(uint32_t id, void* v);   // +0x14 (index 5)
    virtual void v6();
    virtual bool HasProp(uint32_t id);            // +0x1c (index 7)
virtual void v8();
virtual void v9();
    virtual void* GetProp(uint32_t id);           // +0x28 (index 10)
    virtual void CopyFrom(PropList_s0041_a0c0* o);           // +0x2c (index 11)
};
struct ResMgr {
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
    virtual void GetResource(uint32_t group, uint32_t key, void** out);   // +0x2c
};
struct Dispatcher_s0041_a0c0 {
virtual void v0();
virtual void v1();
virtual void v2();
    virtual bool Load(Value* v, void** out, int, int, int, int);  // +0xc
};
struct MsgDispatcher {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
    virtual void Post(uint32_t msgid, void* msg, int);   // +0x14
};
struct MsgArg { uint32_t v, pad; };
struct BehaviorMessage {
    void* vtbl; uint32_t pad4;
    MsgArg args[3];
    uint32_t pad20[4];
    uint32_t msgId;          // +0x30
    uint32_t pad34;
    uint32_t field38;
    inline MsgArg& Arg(int i) { return args[i]; }
};
struct Variant_s0041_a0c0 { char data[16]; uint16_t flags; uint16_t type; };
struct AbilityIface { virtual void v0(); virtual void Release(); };
ResMgr* __cdecl GetResMgr_s0041_a0c0();                 // 0x0067de30
void** __fastcall OutPtr(void** pp);         // 0x0041d870
bool __cdecl PropGet(void* list, uint32_t id, void* out);    // 0x006a1250
bool __cdecl IsUserCreature();               // 0x00461510 (placeholder name)
Dispatcher_s0041_a0c0* __cdecl GetLoader();             // 0x0067dcd0
void* __cdecl Deref(void** pp);              // 0x00422ab0
void __fastcall CopyIt(void* dst, void* src);// 0x004535d0
void __fastcall MsgInit(void* m, uint32_t id);   // 0x00423110
MsgDispatcher* __cdecl GetMsgs();            // 0x0067dcc0
void __fastcall ValueCopy(void* dst, void* src); // 0x00422f40
void __fastcall ValueFree(void* v, int);     // 0x0093db80
void __fastcall BehInit(void* m);            // 0x0040fd50
void __fastcall MsgFree(void* m);            // 0x00421cf0
bool __fastcall IsBusy(void* p);             // 0x00526430
void* __cdecl Alloc(uint32_t sz, const char* name, int, int, int, int);  // 0x00f473a0
void __fastcall Register(AbilityIface* a, uint32_t id, uint32_t key);   // 0x00418500
void* __cdecl Fun401010(void* a, void* b, void* c);   // 0x00401010
void __fastcall Fun4147b0(void* r);          // 0x004147b0
struct EditorBake {
    EditorBake();
    virtual void AddRef();
    virtual void Release();
};
struct Part_s0041_a0c0 {
    char pad0[0x10];
    uint32_t id;          // +0x10
    char pad1[4];
    ResKey_s0041_a0c0 key;           // +0x18
    char pad2[4];
    uint16_t flags;       // +0x20
    char pad3[2];
    void* owner;          // +0x24
    bool Bake();
};
// ---- items of slice s0041a0c0 end

// ---- items of slice s0041aaa0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vec3_s0041_aaa0 { float x, y, z; };
struct Bounds { Vec3_s0041_aaa0 lo, hi; };               // 0x18 bytes
struct Transform_s0041_aaa0 { uint32_t d[0x5c / 4]; };   // 0x5c bytes
void __fastcall Transform_Ctor(Transform_s0041_aaa0*);   // placeholders for thiscall helpers
struct IController {
    virtual void p0();
    virtual void p1();
    virtual void p2();
    virtual void p3();
    virtual void p4();
    virtual void p5();
    virtual void p6();
    virtual void p7();
    virtual void p8();
    virtual void p9();
    virtual void p10();
    virtual void p11();
    virtual void p12();
    virtual void p13();
    virtual void p14();
    virtual void p15();
    virtual void p16();
    virtual void p17();
    virtual void p18();
    virtual void p19();
    virtual void p20();
    virtual void p21();
    virtual void p22();
    virtual void p23();
    virtual void p24();
    virtual void p25();
    virtual void p26();
    virtual void p27();
    virtual void p28();
    virtual void SetParam(void* obj, int id, float value, int flags);               // slot 29, 0x74
    virtual void p30();
    virtual void p31();
    virtual void GetParamRange(void* obj, int id, float* lo, float* hi, int fl);    // slot 32, 0x80
    virtual void p33();
    virtual void p34();
    virtual void p35();
    virtual void p36();
    virtual void p37();
    virtual void p38();
    virtual void p39();
    virtual void p40();
    virtual void p41();
    virtual void p42();
    virtual void p43();
    virtual void p44();
    virtual void p45();
    virtual void p46();
    virtual void p47();
    virtual void p48();
    virtual void p49();
    virtual void p50();
    virtual void p51();
    virtual void p52();
    virtual void p53();
    virtual void p54();
    virtual void p55();
    virtual void p56();
    virtual void p57();
    virtual int  EnumParams(void* obj, void* out, int max);                         // slot 58, 0xe8
    virtual void p59();
    virtual void p60();
    virtual void GetComponents(void* obj, void* outVec);                            // slot 61, 0xf4
};
struct IWriter {
    virtual void p0();
    virtual void p1();
    virtual void p2();
    virtual void p3();
    virtual void p4();
    virtual void p5();
    virtual void p6();
    virtual void p7();
    virtual void p8();
    virtual void p9();
    virtual void p10();
    virtual void p11();
    virtual void p12();
    virtual void p13();
    virtual void Write(const void* data, int size);                                 // slot 14, 0x38
};
void __cdecl  BoundsReset();                                  // 0x409c00
Vec3_s0041_aaa0* __cdecl Vec3Min(Vec3_s0041_aaa0* out, const Vec3_s0041_aaa0* a, const Vec3_s0041_aaa0* b); // 0x41c0c0
Vec3_s0041_aaa0* __cdecl Vec3Max(Vec3_s0041_aaa0* out, const Vec3_s0041_aaa0* a, const Vec3_s0041_aaa0* b); // 0x41bfb0
Vec3_s0041_aaa0* __cdecl Vec3Sub_s0041_aaa0(Vec3_s0041_aaa0* out, const Vec3_s0041_aaa0* a, const Vec3_s0041_aaa0* b); // 0x41db10
float __cdecl Vec3Length(const Vec3_s0041_aaa0* v);                      // 0x41bf30
int   __cdecl FindComponentIndex(unsigned id, int a, int b, int c, int d); // 0x71ddc0
void  __cdecl AccumulateComponent(int p);                     // 0x41bd50
void  __cdecl Cleanup1();                                     // 0x41eb80
struct ParamSweep {
    Bounds* begin;        // 0x00
    Bounds* end;          // 0x04
    int     pad08[3];
    int     counts[8];    // 0x14
    int     handles[8];   // 0x34
    int     numParams;    // 0x54
    IController* ctl;     // 0x58
    void*   obj;          // 0x5c

    // @ 0x41aaa0
    bool Build(void* object, IWriter* out);
};
static inline unsigned QuantNibble(float v, float step)
{
    float q = v / step;
    int c = (int)floorf(q + 0.5f);
    if ((float)c < q) c++;
    unsigned u = 15;
    return (unsigned)(c < 16 ? c : u) & 0xf;
}
// ---- items of slice s0041aaa0 end

// ---- items of slice s0041bd50 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3_s0041_bd50 {
    float x, y, z;
    Vector3_s0041_bd50() {}
    Vector3_s0041_bd50(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    inline float& operator[](int i) { return (&x)[i]; }
    inline const float& operator[](int i) const { return (&x)[i]; }
};
template <class T> inline const T& Max(const T& a, const T& b) { return (a < b) ? b : a; }
template <class T> inline const T& Min(const T& a, const T& b) { return (b < a) ? b : a; }
struct BoundingBox_s0041_bd50 {
    Vector3_s0041_bd50 lo;
    Vector3_s0041_bd50 hi;
    inline bool IsEmpty() const { return lo[0] > hi[0]; }
    void Extend(const Vector3_s0041_bd50& p);
};
// ---- items of slice s0041bd50 end

// ---- items of slice s0042f160 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Alloc_s0042_f160 {
    uint32_t pad;
    const char* mpName;
    Alloc_s0042_f160& operator=(const Alloc_s0042_f160& x)
    {
        mpName = x.mpName;
        return *this;
    }
};
struct WString_s0042_f160 {
    uint16_t* mpBegin;
    uint16_t* mpEnd;
    uint16_t* mpCapacity;
    Alloc_s0042_f160 mAllocator;

    WString_s0042_f160(const WString_s0042_f160& x);
    void AllocateSelf(const uint16_t* b, const uint16_t* e);  // 0x00423820
    void FreeBuffer();                                         // 0x004237d0
    void Resize(uint32_t n);                                   // 0x00429520
    void Swap(WString_s0042_f160& x);                                     // 0x0042f620
    void SetCapacity(uint32_t n);                              // 0x0042f360
    WString_s0042_f160& AssignRange(const uint16_t* b, const uint16_t* e);    // 0x0042f920
    void Assign(const uint16_t* b, const uint16_t* e);         // 0x00423650
    void EraseRange(uint16_t* b, uint16_t* e);                 // 0x0042e2f0
    void AppendRange(const uint16_t* b, const uint16_t* e);    // 0x0042f9d0
};
struct DequeElem {
    uint32_t data[12];
    DequeElem& operator=(const DequeElem& x);  // 0x00405440
};
struct DequeIter {
    DequeElem* mpCurrent;
    DequeElem* mpBegin;
    DequeElem* mpEnd;
    DequeElem** mpCurrentArrayPtr;

    DequeIter(const DequeIter& x);   // 0x00420050
    DequeElem& operator*() const;    // 0x005658b0
    DequeIter& operator++();         // 0x004253c0
    DequeIter& operator--();         // 0x0042f840
};
inline bool operator!=(const DequeIter& a, const DequeIter& b) { return a.mpCurrent != b.mpCurrent; }
struct ThreadedObject_s0042_f160 {
    uint32_t pad;
    volatile long mnRefCount;
    void Release();  // 0x00404f90
};
struct ThreadedPtr {
    ThreadedObject_s0042_f160* mpObject;
    ThreadedPtr& operator=(const ThreadedPtr& x)
    {
        return operator=(x.mpObject);
    }
    ThreadedPtr& operator=(ThreadedObject_s0042_f160* p)
    {
        ThreadedObject_s0042_f160* old;
        uint32_t dead[3];
        if (p != mpObject) {
            old = mpObject;
            if (p)
                _InterlockedIncrement(&p->mnRefCount);
            mpObject = p;
            if (old)
                old->Release();
        }
        return *this;
    }
};
struct ThreadedHolder {
    uint32_t mID;
    ThreadedPtr mPtr;
    ThreadedHolder& operator=(const ThreadedHolder& x);
};
// ---- items of slice s0042f160 end

// ---- items of slice s004157d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void*   __cdecl FUN_00f473a0(uint32_t size, const char* name, uint32_t a, uint32_t b, uint32_t c, uint32_t d);  // 0x00f473a0
extern char    __cdecl FUN_006a25a0();                  // 0x006a25a0
extern void    __cdecl FUN_00471830(void* a, void* b);  // 0x00471830
extern char    __cdecl FUN_004204f0();                  // 0x004204f0
extern char    __cdecl FUN_004204d0();                  // 0x004204d0
extern int     __cdecl FUN_0068f950();                  // 0x0068f950
extern int     __cdecl FUN_00690120();                  // 0x00690120
extern void*   g_AppProperties;                         // 0x015fd918
struct MsgKey {                 // the incoming message key triple
    uint32_t mKey0;             // +0x00
    uint32_t mKey1;             // +0x04
    uint32_t mKey2;             // +0x08
};
struct MsgArgs {                // the incoming message args
    uint32_t mId;               // +0x00
    uint16_t mFlags;            // +0x04
    uint16_t mValue;            // +0x06
};
struct Slot_s0041_57d0 { uint32_t v, pad; };
struct Slots_s0041_57d0 {
    Slot_s0041_57d0 slot[5];               // +0x00
    uint32_t id30;              // +0x28 (object+0x30)
    uint32_t pad34;             // +0x2c
    void Set(int i, uint32_t v) { slot[i].v = v; }
};
struct Msg_s0041_57d0 {
    void* vtbl;                 // +0x00
    uint32_t pad4;              // +0x04
    Slots_s0041_57d0 s;                    // +0x08
    uint32_t f38;               // +0x38
    uint32_t pad3c;             // +0x3c
    Msg_s0041_57d0(uint32_t id);           // 0x423110
    void Base2Init();           // 0x40fd50
    void Set(int i, uint32_t v) { s.Set(i, v); }
    static void* operator new(unsigned size, const char* name);
};
struct BMsg_s0041_57d0 : Msg_s0041_57d0 {
    BMsg_s0041_57d0(uint32_t id) : Msg_s0041_57d0(id) { vtbl = (void*)0x13eb844; f38 = 0; }
};
struct MsgMgr_s0041_57d0 {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
    virtual void Post(uint32_t id, Msg_s0041_57d0* m, uint32_t a, uint32_t b);     // +0x18
};
struct Target_s0041_57d0 {
    virtual int  AddRef();                                  // +0x00
    virtual int  Release();                                 // +0x04
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
    virtual void F2c(void* a);                              // +0x2c
};
struct TRef_s0041_57d0 {
    Target_s0041_57d0* p;                                              // +0x00
    Target_s0041_57d0** Out();                                         // 0x41d870
};
struct KeyedRecord_s0041_57d0 {
    uint32_t mKey00;            // +0x00
    uint32_t mKey04;            // +0x04
    uint32_t mKey08;            // +0x08
    uint32_t mField0C;          // +0x0c
    uint16_t mFlags10;          // +0x10
    uint16_t mValue12;          // +0x12
    void*    mField14;          // +0x14
    void*    mField18;          // +0x18
    TRef_s0041_57d0     mJob1C;            // +0x1c
    void*    mField20;          // +0x20
    TRef_s0041_57d0     mSlots24[4];       // +0x24
    KeyedRecord_s0041_57d0();              // 0x4036e0
    void Destroy();             // 0x401f20
};
extern void*   __cdecl GetManager_s0041_57d0();                    // 0x0067dcd0
extern MsgMgr_s0041_57d0* __cdecl GetMsgMgr_s0041_57d0();                     // 0x0067dcc0
extern char    __cdecl FUN_00469920(uint32_t key, uint32_t id, Target_s0041_57d0** out);   // 0x00469920
extern char    __cdecl FUN_004bafc0(void* msg, Target_s0041_57d0** out);                   // 0x004bafc0
extern void*   __cdecl FUN_004186c0(void* a, void* b, Target_s0041_57d0** out);            // 0x004186c0
inline void* Msg_s0041_57d0::operator new(unsigned size, const char* name)
{
    return FUN_00f473a0((uint32_t)size, name, 0u, 0u, 0u, 0u);
}
#define ASSIGN_REF(dst, src) \
    do { \
        if ((src) != (dst).p) { \
            Target_s0041_57d0* old_ = (dst).p; \
            if (src) (src)->AddRef(); \
            (dst).p = (src); \
            if (old_) old_->Release(); \
        } \
    } while (0)
#define ASSIGN_JOB(dst, src) \
    do { \
        if ((src) != (dst).p) { \
            Target_s0041_57d0* old_ = (dst).p; \
            if (src) ((int(__thiscall*)(void*))FUN_0068f950)(src); \
            (dst).p = (src); \
            if (old_) ((int(__thiscall*)(void*))FUN_00690120)(old_); \
        } \
    } while (0)
#define RELEASE_REF(t) do { if ((t).p) (t).p->Release(); } while (0)
#define RELEASE_JOB(t) do { if (t) ((int(__thiscall*)(void*))FUN_00690120)(t); } while (0)
#define NEW_HMSG_s0041_57d0(var, idv) \
    Msg_s0041_57d0* tmp##var; \
    void* raw##var = FUN_00f473a0(0x40u, kEditorAllocName, 0u, 0u, 0u, 0u); \
    if (raw##var) { \
        ((Msg_s0041_57d0*)raw##var)->s.id30 = (idv); \
        ((Msg_s0041_57d0*)raw##var)->Base2Init(); \
        ((Msg_s0041_57d0*)raw##var)->vtbl = (void*)0x13eb90c; \
        ((Msg_s0041_57d0*)raw##var)->vtbl = (void*)0x13eb844; \
        ((Msg_s0041_57d0*)raw##var)->f38 = 0; \
        tmp##var = (Msg_s0041_57d0*)raw##var; \
    } else tmp##var = 0; \
    var = tmp##var;
struct Handler_s0041_57d0 {
    void**  mpVtbl;                     // +0x00
    uint8_t mPad04[0x0c8 - 0x04];
    uint8_t mRecordSet[0x2c * 0x40];    // +0x0c8
    bool HandleMessage(const MsgKey* msg, const MsgArgs* args);   // 0x004157d0
};
// ---- items of slice s004157d0 end

// @ 0x00401990
void ConvertObjectIdsToIndices(BlockContainer* container)
{
    int i0 = FindBlock(container, 0x15, 0, 6, 8);
    if (i0 < 0)
        return;
    TypedBlock a(container->mEntries.mpBegin[i0].mBlock);
    DataBlock b(a.mnCount, 4, 4);
    AllocateBlock(&b);
    for (int i = 0, n = a.mnCount; i < n; ++i) {
        uint32_t handle = a.At(i);
        Object_s0040_1200* object = GetObjectManager()->GetObject(handle);
        uint32_t* comp = GetIndexComponent(object->mpThing);
        uint32_t value = comp ? *comp : 0xffffffff;
        b.At(i) = value;
    }
    container->mEntries.push_back(BlockEntry(0x14, 0, 6, 8, b));
}

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

// @ 0x00401f20
ReferenceHolder::~ReferenceHolder()
{}

// @ 0x00401ff0
ResourceCollector::ResourceCollector()
: mHandle(), mField4(0), mField8(0), mbField64(false), mbField65(false)
{
    uint32_t unused;
}

// @ 0x004020e0
ResourceCollector::~ResourceCollector()
{}

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

// @ 0x00402470
void Preloader::Gather(PreloadSource* pSource, bool bSkipKeys)
{
    mKeys.reserve(pSource->items.size() * 4);
    mResources.reserve(pSource->items.size() * 4);
    int total = 0;
    for (int index = 0, itemCount = pSource->items.size(); !bSkipKeys && index < itemCount; ++index) {
        PreloadItem& item = pSource->items.mpBegin[index];
        PropertyListPtr pList;
        if (PropManager::Get()->GetPropertyList(item.instanceID, item.groupID, pList.Out())) {
            for (int j = 0; j < 4; ++j) {
                ResourceKey_s0040_2470 key;
                if (Property::GetKey(pList.get(), 0xf9efbb + j, &key)) {
                    AddKey(key);
                    if (j == 0) {
                        ConvertKeyType(&key, 0x61, 0);
                        AddKey(key);
                    }
                }
            }
            ResourceKey_s0040_2470 key2;
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
            ResourceKey_s0040_2470 key;
            if (Property::GetKey(pProps.get(), 0x2424655, &key))
                AddResource(key.instanceID, key.groupID, 4);
            if (Property::GetKey(pProps.get(), 0x2424657, &key))
                AddResource(key.instanceID, key.groupID, 4);
            if (Property::GetKey(pProps.get(), 0x2424656, &key))
                AddResource(key.instanceID, key.groupID, 4);
        }
    }
}

// @ 0x004029f0
void Preloader::Start(const ResourceKey_s0040_2470& key, bool flag)
{
    Reset();
    GetLoadManager()->OpenHandle(mpHandle.AsPointer());
    intrusive_ptr_s0040_2470<LoadHandle>::Validate(mpHandle.get());
    mKey = key;
    mKeys.push_back(key);
    mbActive = true;
    mbFlag = flag;
}

// @ 0x00402a90
LoadHandle* Preloader::GetHandle()
{
    return mpHandle.get();
}

// @ 0x00402ab0
Preloader* Preloader::Self()
{
    return this;
}

// @ 0x00402ac0
bool Preloader::IsFinished()
{
    return !mpHandle.get() || IsLoadFinished(mpHandle.get());
}

// @ 0x00402b30
void Preloader::Reset()
{
    if (mpHandle.get()) {
        mpHandle.get()->Cancel(true);
        mpHandle = 0;
    }
    mKey = ResourceKey_s0040_2470(false, 0, 0);
    mbActive = false;
    mbFlag = false;
    mKeys.clear();
    mResources.clear();
    mFiles.clear();
    for (int i = 0; i < 6; ++i)
        mpObjects[i] = 0;
}

// @ 0x00402cc0
void BlockLoader::Update()
{
    if (!mpEditor || mpEditor->IsPlayMode() || mpEditor->IsEditing())
        return;
    {
        int idleSlots = 0;
        for (int i = 0; i < 6; i++) {
            if (mSlots[i]) {
                intrusive_ptr_s0040_2cc0<Result> result;
                if (mSlots[i]->IsFinished()) {
                    if (mSlots[i]->GetResult(result.AsOutParam())) {
                        PostMessage(9, result);
                        mResults.push_back(result);
                    }
                    mSlots[i] = 0;
                }
            }
            while (!mSlots[i] && !mRequests.empty()) {
                BlockRequest request = mRequests.back();
                mRequests.pop_back();
                intrusive_ptr_s0040_2cc0<Result> result;
                GetFactory()->Create(&request, mSlots[i].AsOutParam(), result.AsOutParam(), 0, 0, 0, 0, 0);
                if (result) {
                    PostMessage(9, result);
                    mResults.push_back(result);
                    mSlots[i] = 0;
                }
            }
            if (!mSlots[i])
                idleSlots++;
        }
        if (idleSlots == 6) {
            if (mbApplyResults) {
                mbApplyResults = false;
                intrusive_ptr_s0040_2cc0<Result> combined;
                if (!mResults.empty())
                    combined = CombineResults(mResults.begin());
                if (combined)
                    ApplyResult(combined, mbApplyFlag);
                else
                    Finish();
            } else {
                GetUndoManager()->BeginBatch();
                int i = 0;
                for (int count = mItems.size(); i < count; i++) {
                    if (!mItems[i]->IsHidden())
                        GetItemManager()->Process(mItems[i], mpEditor);
                }
                mpEditor->Refresh();
                GetUndoManager()->EndBatch();
            }
        }
    }
}

// @ 0x00403240
EditorBlockData::EditorBlockData()
: mCache(0, -1, BlockAlloc, BlockFree, "Editor/BlockData"),
      mFlagC0(true), mFieldC4(0), mFlag258(false), mFlag259(false), mFlag2C4(false),
      mObj1138(5, 0), mObj1150(5, 0), mFlag1180(false)
{
}

// @ 0x004035d0
RangeSettings::RangeSettings()
: mID(0), mbEnabled(false), mItems(),
      mIndex0(0), mMin0(0.0f), mMax0(0.0f),
      mIndex1(0), mMin1(0.0f), mMax1(0.0f),
      mIndex2(0), mMin2(0.0f), mMax2(0.0f) {}

// @ 0x004036a0
int GameSystem::AddRef()
{ return DefaultRefCounted::AddRef(); }

// @ 0x004036e0
KeyedRecord::KeyedRecord()
: mpOwner(0), mpData(0), mpExtra(0) {}

// @ 0x004037b0
GameSystem::~GameSystem()
{ uint32_t unused0, unused1, unused2; }

// @ 0x004039f0
bool PendingBatch::Flush()
{
    bool result = false;
    if (mpTarget) {
        BatchTarget* target = mpTarget;
        mpTarget = 0;
        result = ApplyAll(target, mContext, mpItems, mnCount, mUserData);
    }
    return result;
}

// @ 0x00403aa0
SlotArray8::~SlotArray8()
{}

// @ 0x00403af0
bool cBaker::Initialize()
{
    SortEntry* pTable = kSortTable;
    sort(pTable, pTable + kSortTableCount, SortLess());

    mSettings = Blob56();

    mpWindow = WindowManager()->FindWindowByID(0x227d899, 0, 0);
    mpWindow->SetFlag(1, 0, 0);
    mpWindow->SetVisible(true);
    mpProgress = WindowManager()->FindWindowByID(0x227d89a, 0, 0);
    mpProgress->SetVisible(false);

    mpBlockData = new("Editor", 0, 0, 0, 0) cBlockData();
    mpQueue = new("Editor", 0, 0, 0, 0) cBakeQueue(1.0f);

    mMessages.Init(MessageManager(), this, kMessageIDs, 13);
    Reset(0);
    new("Editor", 0, 0, 0, 0) BakerCommand(this);
    Function_0067de20();

    vector_s0040_3af0<ResourceKey_s0040_3af0> keys((KeyAllocator()));
    vector_s0040_3af0<IDatabase*> dbList((KeyAllocator()));
    keys.reserve(0x800);
    ((IResourceManager_s0040_3af0 *)ResourceManager_s0040_3af0())->FindRecords(&keys, Skinner::IdPaintSystem(0x5caa5e28), &dbList);

    for (int i = 0, n = (int)keys.size(); i < n; i++) {
        ResourceKey_s0040_3af0 key = keys[i];
        IDatabase* pDB = dbList[i];
        intrusive_ptr_s0040_3af0<IResourceRecord> pRecord;
        if (pDB) {
            if (pDB->OpenRecord(key, pRecord.AsOutParam(), 1, 6, 1, 0)) {
                IStream* pStream = pRecord->GetStream();
                int size = pStream->GetSize();
                if (size >= 0x24 && size < 100000) {
                    void* pData = mPool.Alloc(size, 1);
                    pStream->Read(pData, size);
                    unsigned __int64 fullID = key.instanceID | ((unsigned __int64)key.groupID << 32);
                    mBuffers[fullID] = pData;
                }
                pDB->CloseRecord(pRecord.get());
            }
        }
    }

    mbBaking = false;
    LoadSettings();

    for (int i = 0; i < 6; i++) {
        int type = i + 'a';
        intrusive_ptr_s0040_3af0<IPropList> pList;
        if (PropManager()->GetPropertyListImpl(HashString("GeomInfo"), PropertyID(type, 1), pList.AsOutParam())) {
            int keyCount;
            ResourceKey_s0040_3af0* pKeyList;
            int valueCount;
            float* pValues;
            if (GetPropertyKeys(pList.get(), 0x66f235b, &keyCount, &pKeyList) &&
                GetPropertyFloats(pList.get(), 0x66f235c, &valueCount, &pValues) &&
                keyCount == valueCount) {
                for (int j = 0; j < keyCount; j++)
                    mGeomInfo[i][pKeyList[j]] = pValues[j];
            }
        }
    }
    return true;
}

// @ 0x004043f0
void AddListeners(IMessageManager* pManager, IMessageListener* pListener, const unsigned int* pIDs, unsigned int count)
{
    for (unsigned int i = 0; i < count; i++)
        pManager->AddListener(pListener, pIDs[i]);
}

// @ 0x00404430
inline void sort(SortEntry* first, SortEntry* last, SortLess compare)
{ SortEntries(first, last, compare); }

// @ 0x00404460
namespace Skinner {
bool IdPaintSystem::IsEqual(const PaintSystem& other) const
{
    return static_cast<const IdPaintSystem&>(other).mId == mId;
}
}  // namespace Skinner

// @ 0x00404480
void* LinearAllocator::Allocate(unsigned int size, bool allowGrow)
{
    size = (size + 7) & ~7u;
    if (allowGrow && (int)(mpEnd - (mpCurrent + size)) < 0) {
        if (!Grow(size))
            return 0;
    }
    void* result = mpCurrent;
    mpCurrent = mpCurrent + size;
    mpLast = mpCurrent;
    return result;
}

// @ 0x00404500
BakerCommand_s0040_4480::BakerCommand_s0040_4480(void* pBaker)
: mpBaker(pBaker), mOptions(1)
{
    mOptions.AddOptions("Baker system management.",
        "-bake^ [<keyFilter:cstring>]", 0, &mKeyFilter,
            "bake given buildings/vehicles/creatures/etc., switch to model viewer unless noSwitch is specified",
        "-toData^", 6,
            "after baking, promote baked resources to Data, ready for checking in as shipped content",
        "-show^", 0xb, "show result of baking in the model viewer",
        "-force^", 8, "force the baker to perform a full bake, ignoring existing resources on disk",
        "-hires^", 0xe, "bake with high lod model present",
        "-flush^", 1, "flush resman after each bake",
        "-rtts^", 2, "show rtt list after each bake",
        "-limit <n:int>", &mLimit, "bake at most n models",
        "-describeBlocks^", 3,
            "dump text descriptions for all rigblocks to basePath or UserData/Debug/BlockDescriptions.",
        "-filter^ <group:int> <instance:int>", 4, &mFilterGroup, &mFilterInstance,
            "filter by manifest list for describeBlocks cheat",
        "-processQueue^ <bool>", 5, &mProcessQueue, "enable or disable processing of queued items",
        "-dumpProfs^", 7, "dump timing information for bakes completed",
        "-fastDevMode^", 0xc, "enable 'fast' mode until game restart (extremely low quality)",
        0);
}

// @ 0x00404630
void BakerCommand_s0040_4480::Description(void* stream)
{
    mOptions.PrintUsage("baker", stream);
}

// @ 0x00404660
void BakerCommand_s0040_4660::ParseLine(ArgScript::Line& line)
{
    mKeyFilter = 0;
    mLimit = 0;
    if (line.GetArgumentsCount() == 1) {
        ArgScript::PrintF(mpOutput, mOptions.GetUsage(line.GetArgumentAt(0), 1));
        return;
    } else {
        mOptions.Parse(line, mpOutput);
    }

    IResourceManager_s0040_4660* resourceManager = ResourceManager_s0040_4660();
    ResourceKeyFilter keyFilter;
    KeyVector resourceKeys;

    if (mKeyFilter) {
        ResourceKey_s0040_4660 key;
        ResourceKeyFromString(&key, mKeyFilter, 0xffffffff, 0xffffffff);
        keyFilter.mInstanceID = key.instanceID;
        keyFilter.mGroupID = key.groupID;
        keyFilter.mTypeID = key.typeID;
        resourceManager->GetResourceKeyList(&resourceKeys, &keyFilter, 0);
        if (resourceKeys.empty())
            resourceKeys.push_back(key);
    } else if (GameModeManager()->GetActiveModeID() == 0xdbdba1) {
        cEditor* activeMode = GameModeManager()->GetActiveMode();
        cEditorModel* pEditorModel = 0;
        cEditor* pEditor = activeMode;
        pEditorModel = pEditor->GetEditorModel();
        if (pEditorModel) {
            ResourceKey_s0040_4660 modelKey = pEditorModel->mKey;
            if (modelKey == ResourceKey_s0040_4660(0, 0, 0)) {
                ArgScript::PrintF(mpOutput, "No key -- you need to save the model first.\n");
                return;
            }
            resourceKeys.push_back(pEditorModel->mKey);
        }
    }

    if (mOptions.IsSet(0) && !resourceKeys.empty()) {
        string16 displayName;
        intrusive_ptr_s0040_4660<IObject> pRes;  // never assigned in the original either
        int j = 0;
        int numKeys = resourceKeys.size();
        int numBakes = 0;
        for (; j < numKeys && (mLimit == 0 || numBakes < mLimit); j++) {
            ResourceKey_s0040_4660 key = resourceKeys.mpBegin[j];
            if (key.typeID == 0x1a99b06b || key.typeID == 0xffffffff)
                key.typeID = GetTypeForCategory(GroupIDBits(key.groupID).bits.category, 0);
            if (!IsBakeableType(key.typeID, 0))
                continue;
            numBakes++;
            resourceManager->GetFileName(key, displayName);
            GetDisplayName(key, displayName, 0);
            ArgScript::PrintF(mpOutput, "queuing %ls for bake\n", displayName.c_str());
            BakeRequest request;
            request.mID = 0x2ea8fb98;
            request.mFlags = 0;
            request.mPriority = 4;
            if (mOptions.IsSet(6))
                request.mFlags |= 0x40;
            if (mOptions.IsSet(8))
                request.mFlags |= 0x20;
            if (mOptions.IsSet(0xe))
                request.mFlags |= 0x100;
            if (GroupIDBits(key.groupID).bits.category == 0x6b)
                request.mFlags |= 0x10;
            mpBaker->QueueBake(key, request);
        }
        if (mOptions.IsSet(0xb)) {
            GameModeManager()->SetActiveMode(0xb44a3f);
            intrusive_ptr_s0040_4660<ViewModelMessage> pMsg = new("Editor", 0, 0, 0, 0) ViewModelMessage;
            pMsg->mArgs.SetValue(0, resourceKeys.front().instanceID);
            pMsg->mArgs.SetValue(1, SetGroupSubtype(resourceKeys.front().groupID, 0x62));
            MessageManager_s0040_4660()->PostMSG(0x4051e54, pMsg.get(), 0, 0);
        }
    }

    if (mOptions.IsSet(2))
        RenderManager()->DumpRTTs();

    if (mOptions.IsSet(1)) {
        TypeIDFilter filterA(0x1c135da);
        resourceManager->ReleaseResources(0, &filterA);
        TypeIDFilter filterB(0xe6bce5);
        resourceManager->ReleaseResources(0, &filterB);
    }

    if (mOptions.IsSet(3)) {
        if (mOptions.IsSet(4))
            DescribeBlocks(mFilterGroup, mFilterInstance);
        else
            DescribeBlocks(0, 0);
    }

    if (mOptions.IsSet(5))
        Baker()->SetProcessQueue(mProcessQueue);
}

// @ 0x00404f10
bool ResourceKeyFilter::IsValid(const ResourceKey_s0040_4660& key)
{
    return (mTypeID == 0xffffffff || mTypeID == key.typeID)
        && (mGroupID == 0xffffffff || (mGroupID & mGroupMask) == (key.groupID & mGroupMask))
        && (mInstanceID == 0xffffffff || mInstanceID == key.instanceID);
}

// @ 0x00404f90
namespace Resource_s0040_4660 {
int ThreadedObject_s0040_4660::Release()
{
    long refCount = _InterlockedDecrement(&mnRefCount);
    if (refCount != 0)
        return refCount;
    _InterlockedExchange(&mnRefCount, 1);  // keep the count stable while destroying
    delete this;
    return 0;
}
}  // namespace Resource_s0040_4660

// 0x00405000 (byte-exact lifted version: match/slices/s00405000/s00405000_lifted.cpp)
BakerCommand_s0040_5000::BakerCommand_s0040_5000(void* pBaker)
: mpBaker(pBaker), mOptions(1)
{
    mOptions.AddOptions("Baker system management.",
        "-bake^ [<keyFilter:cstring>]", 0, &mKeyFilter,
            "bake given buildings/vehicles/creatures/etc., switch to model viewer unless noSwitch is specified",
        "-toData^", 6,
            "after baking, promote baked resources to Data, ready for checking in as shipped content",
        "-show^", 0xb, "show result of baking in the model viewer",
        "-force^", 8, "force the baker to perform a full bake, ignoring existing resources on disk",
        "-hires^", 0xe, "bake with high lod model present",
        "-flush^", 1, "flush resman after each bake",
        "-rtts^", 2, "show rtt list after each bake",
        "-limit <n:int>", &mLimit, "bake at most n models",
        "-describeBlocks^", 3,
            "dump text descriptions for all rigblocks to basePath or UserData/Debug/BlockDescriptions.",
        "-filter^ <group:int> <instance:int>", 4, &mFilterGroup, &mFilterInstance,
            "filter by manifest list for describeBlocks cheat",
        "-processQueue^ <bool>", 5, &mProcessQueue, "enable or disable processing of queued items",
        "-dumpProfs^", 7, "dump timing information for bakes completed",
        "-fastDevMode^", 0xc, "enable 'fast' mode until game restart (extremely low quality)",
        0);
}

// @ 0x004051e0
void Baker_s0040_5000::CancelAll()
{
    mPending.Clear();
    mDeferred.Clear();
    mbProcessQueue = false;

    if (mCurrent.mpJob.get())
        mCurrent.mpJob->Cancel(0);
    if (mCurrent.mpModel.get())
        mCurrent.mpModel->Unload();
    mCurrent = BakeEntry();
    mbBaking = false;

    for (BakeMap::iterator it = mQueued.begin(); it != mQueued.end(); ++it) {
        if (it->mpJob.get())
            it->mpJob->Cancel(0);
        if (it->mpModel.get())
            it->mpModel->Unload();
        *it = BakeEntry();
    }
    mQueued.clear();
}

// @ 0x00405440
void AssignBakeEntry(BakeEntry& dst, const BakeEntry& src)
{ dst = src; }

// @ 0x004055b0
void Baker_s0040_5000::Shutdown()
{    struct LocalHelper {
        static __forceinline int AddRef(DefaultRefCounted_s0040_5000* p) {
            return p->mnRefCount++ + 1;
        }
        static __forceinline void ClearRef(intrusive_ptr_s0040_5000<DefaultRefCounted_s0040_5000>* self, DefaultRefCounted_s0040_5000* pObject) {
            if (pObject != self->mpObject) {
                DefaultRefCounted_s0040_5000* const pTemp = self->mpObject;
                unsigned int scratch[3];
                if (pObject)
                    AddRef(pObject);
                self->mpObject = pObject;
                if (pTemp)
                    pTemp->Release();
            }
        }
    };
    ICheatManager::Get()->RemoveCheat("baker");
    mpWindow = 0;
    mpLayout = 0;
    IMessageManager_s0040_5000::Get()->RemoveListener(0x227d899);
    IMessageManager_s0040_5000::Get()->RemoveListener(0x227d89a);
    LocalHelper::ClearRef(&mpModelRes, 0);
    LocalHelper::ClearRef(&mpRigRes, 0);
    mBatch.Flush();
    mArena.Reset(0);
    mBakedKeys.clear();}

// @ 0x004063d0
EditorLoadRequest* CloneLoadRequest(const EditorLoadRequest& request)
{
    return new EditorLoadRequest(request);
}

// @ 0x00406570
bool EditorLoader::Load()
{
    ResourceKey_s0040_63d0 key = mKey;
    intrusive_ptr_s0040_63d0<EditorModel> pModel;
    if (mpTask && !mpTask->IsReady())
        return false;
    if (mData.mbValid)
        mData = EditorData();
    if (!LoadEditorModel(key, pModel.AsPointer(), 0))
        return false;
    pModel->Init(GetEditorContext(), 0, 0, true);
    if (pModel->GetCount() <= 0)
        return false;
    mb424 = (mFlags & 8) != 0;
    mpState->mbDirty = true;
    intrusive_ptr_s0040_63d0<PropertyList_s0040_63d0>& propList = mData.mpPropList;
    mb425 = false;
    mn428 = 0;
    if (PropManager_s0040_63d0()->GetPropertyList(key.instanceID, key.groupID, propList.AsPointer())) {
        ReadFloat(propList.get(), 0x2f35189, mData.mfScale);
        ReadBool(propList.get(), 0x339ff24, mb425);
        ReadInt(propList.get(), 0x339ffa9, mn428);
    }
    intrusive_ptr_s0040_63d0<Task_s0040_63d0> pTask;
    if (!TaskManager()->CreateTask(pTask.AsPointer()))
        return false;
    pTask->SetField18(1);
    pTask->SetOwner(this);
    mData.mbValid = true;
    mpTask = pTask;
    mModel = pModel.mpObject;
    pTask->Start();
    return true;
}

// @ 0x00406ac0
EditorSnapshot& EditorSnapshot::operator=(const EditorSnapshot& x)
{
    mbActive = x.mbActive;
    mfValue = x.mfValue;
    mpOwner = x.mpOwner;
    mItems = x.mItems;
    mEntries = x.mEntries;
    mIndices = x.mIndices;
    mEntries2 = x.mEntries2;
    mSmall = x.mSmall;
    mField944 = x.mField944;
    mField948 = x.mField948;
    mField94C = x.mField94C;
    mField950 = x.mField950;
    mField954 = x.mField954;
    mField958 = x.mField958;
    mField95C = x.mField95C;
    mListE = x.mListE;
    mListF = x.mListF;
    mListG = x.mListG;
    mMap = x.mMap;
    mFieldCC8 = x.mFieldCC8;
    return *this;
}

// @ 0x00406e90
bool IPredicateTarget::TestAny(void* arg)
{
    return TestA(arg, 0) || TestB(arg);
}

// @ 0x00406ef0
bool ResourceFlagQuery::IsFlagged(const ResourceKey& key, bool requireSecondary)
{
    if (MakeGroup(key.groupID).kind == 0x62) {
        uint32_t primaryGroup = WithVariant(key.groupID, 0);
        uint32_t otherGroup = WithVariant(key.groupID, 1);
        bool baseFlag = false;
        bool flag1 = false;
        intrusive_ptr_s0040_6ac0<PropertyList_s0040_6ac0> pPropList;
        if (PropertyManager_Get()->GetPropertyList(key.instanceID, primaryGroup, pPropList.AsOutParam()))
            GetBoolPropertyOutOfLine(pPropList, kPropEnabled, baseFlag);
        if (PropertyManager_Get()->GetPropertyList(key.instanceID, otherGroup, pPropList.AsOutParam()))
            GetBoolPropertyOutOfLine(pPropList, kPropEnabled, flag1);
        return baseFlag && flag1;
    }
    bool flag = false;
    intrusive_ptr_s0040_6ac0<PropertyList_s0040_6ac0> pPropList;
    if (PropertyManager_Get()->GetPropertyList(key.instanceID, key.groupID, pPropList.AsOutParam())) {
        GetBoolPropertyInline(pPropList.get(), kPropEnabled, flag);
        if (flag && requireSecondary) {
            flag = false;
            GetBoolPropertyInline(pPropList.get(), kPropEnabledSecondary, flag);
        }
    }
    return flag;
}

// @ 0x00407190
bool GetBoolProperty(PropertyList_s0040_6ac0* list, uint32_t propertyID, bool& result)
{
    Property_s0040_6ac0* pProp;
    bool* pValue;   // unused; keeps the original frame layout
    if (list && list->GetProperty(propertyID, pProp) && pProp->mnType == 1) {
        result = *pProp->GetValueBool();
        return true;
    }
    return false;
}

// @ 0x004071e0
void KeyRemapper::Apply(vector_s0040_6ac0<KeyPair>& pairs, ResourceKey key)
{
    if (KeysDiffer(key, kNullKey)) {
        for (int i = 0, size = pairs.size(); i < size; i++) {
            KeyPair& pair = pairs[i];
            RemapKey(pair.a, key);
            RemapKey(pair.b, key);
        }
    }
}

// @ 0x00407280
void SettingsBuilder::BuildGraphicsProperties(ResourceKey_s0040_7280* key)
{
    PropertyList_s0040_7280* result = 0;     // list being produced (ebp-0x1590)
    char ref[0x100];
    ResourceManager_s0040_7280* rm = GetResourceManager_s0040_7280();
    rm->GetResource(key->instance, key->group, (void*)(unsigned)MakeKey(&result));

    ResourceKey_s0040_7280 modelKey = *key;
    ResourceFactory* rf = GetResourceFactory();
    int modelRef = 0;
    if (!rf->Create(key, (void*)(unsigned)MakeKey(ref), 0, 0, 0, 0)) {
        if (result) result->Release();
        return;
    }
    Model* model = LookupModel(&modelRef);
    if (!model) { if (result) result->Release(); return; }

    // Optional secondary key (type 0x30bdee3) resolved through the factory.
    modelKey.type = 0x30bdee3;
    PropertyList_s0040_7280* extra = 0;
    if (rf->Create(&modelKey, (void*)(unsigned)MakeKey(ref), 0, 0, 0, 0)) {
        PropertyList_s0040_7280* found = (PropertyList_s0040_7280*)LookupModel(&modelRef);
        if (found != extra) {
            PropertyList_s0040_7280* old = extra;
            if (found) found->AddRef();
            extra = found;
            if (old) old->Release();
        }
    }

    if (!result) {
        void* mem = AllocPropertyList(0x38, g_GraphicsTag, 0, 0, 0, 0);
        PropertyList_s0040_7280* fresh = mem ? ConstructPropertyList(mem) : 0;
        if (fresh != result) {
            PropertyList_s0040_7280* old = result;
            if (fresh) fresh->AddRef();
            result = fresh;
            if (old) old->Release();
        }
    }

    // Seed scale from an existing float property, defaulting to 1.0.
    float scale = 1.0f;
    PropertyInfo* info = 0;
    if (result->GetProperty(0xfba611, &info) && info->type == 0xd)
        scale = *(float*)LookupModel(&info);

    // Per-part pass: accumulate dominant extent and per-part volumes.
    int partCount = (int)(model->partsEnd - model->partsBegin);
    float maxVolume = 0.0f;
    float bestWeight = 0.0f;
    uint32_t bestId = 0, bestScale = 0;
    for (int i = 0; i < partCount; ++i) {
        Part* part = &model->partsBegin[i];
        MeshEntry entry; BuildPartEntry(&entry, part);
        entry.flags |= 4; entry.count += 2;
        entry.flags |= 2; entry.count += 1;
        float lo[3], hi[3];
        GetBounds(((uint32_t*)part)[1], ((uint32_t*)part)[0], lo, hi, ((uint32_t*)part)[0x24]);
        if (hi[0] < lo[0]) { /* swap handled by helper */ }
        AddPartBounds(&entry, part);
    }

    // Commit the standard properties (all via the vtable +0x14 setter).
    CommitProperty(result, 0xf1fae962, 0);
    CommitProperty(result, 0xf1fae963, 0);
    CommitProperty(result, 0x4c71061, 0);
    CommitProperty(result, 0x4c71062, 0);
    CommitProperty(result, 0x519e304, 0);
    CommitProperty(result, 0x5b567d1, 0);
    CommitProperty(result, 0x4ff954a, 0);

    // Model-kind dependent default (property 0x46d0560): hashed kind switch in the original.
    switch (model->kind) {
    case 0x8f963dcb: case 0xc15695da: case 0x2a5147a9: case 0x1f2a25b6:
        CommitProperty(result, 0x46d0560, 0); break;
    case 0x98e03c0d: case 0x1a4e0708: case 0x2090a11b: case 0x441cd3e6: case 0x449c040f:
        CommitProperty(result, 0x46d0560, 0); break;
    case 0xc0b74287: case 0x9ad7d4aa: case 0xbc1041e6: case 0xf670aa43: case 0x7d433fad:
        CommitProperty(result, 0x46d0560, 0); break;
    default: break;
    }
    if (!result->HasProperty(0x4a5b8d2)) {
        if (model->kind == 0x47c10953 || model->kind == 0x72c49181)
            CommitProperty(result, 0x4a5b8d2, 0);
    }

    GetResourceManager_s0040_7280()->SetResource(result, key->instance, key->group);

    // Group 'b' variant: publish a second list when property 0x339ff24 is a set bool.
    if ((key->group >> 30) == 1 && ((key->group >> 8) & 0xff) == 0x62) {
        PropertyInfo* pi = 0; char flag = 0;
        if (result && result->GetProperty(0x339ff24, &pi) && pi->type == 1) flag = 1;
        if (flag) {
            void* mem = AllocPropertyList(0x38, "Graphics", 0, 0, 0, 0);
            PropertyList_s0040_7280* second = mem ? ConstructPropertyList(mem) : 0;
            if (second) second->AddRef();
            GetResourceManager_s0040_7280()->SetResource(second, key->instance,
                                              (key->group & 0xffff00ff) | 0x7e00);
            if (second) second->Release();
        }
    }

    if (extra)  extra->Release();
    if (result) result->Release();
}

// @ 0x004098a0
Vector3Copyable::Vector3Copyable(const Vector3Copyable& o)
{
    x = o.x;
    y = o.y;
    z = o.z;
}

// @ 0x004098e0
Vector3& MulMatrixAssign(Vector3& dst, const Matrix3& m)
{
    dst = dst * m;
    return dst;
}

// @ 0x00409930
Transform::Transform()
: mFlags(0), mVersion(0), mPos(g_ZeroVector), mScale(1.0f)
{
    PadN<11>();  // unused locals present in the original frame
    mRot = g_IdentityMatrix;
}

// @ 0x004099b0
void Transform::RotateY(float angle)
{
    float s = (float)sin(angle);
    float c = (float)cos(angle);
    Vector3 r0 = mRot[0];
    Vector3 r1 = mRot[1];
    mRot[0] = c * r0 + s * r1;
    mRot[1] = (-s) * r0 + c * r1;
    mFlags |= 2;
    mVersion++;
}

// @ 0x00409b30
void Transform::Scale(float s)
{
    mScale *= s;
    mPos *= s;
    mFlags |= 1;
    mVersion++;
}

// @ 0x00409b90
Vector3& BoundingBox::GetCenter(Vector3& out) const
{
    out = (min + max) * 0.5f;
    return out;
}

// @ 0x00409c00
void BoundingBox::Reset()
{
    min = Vector3(kFloatMax, kFloatMax, kFloatMax);
    max = Vector3(-kFloatMax, -kFloatMax, -kFloatMax);
}

// @ 0x00409ce0
void BoundingBox::SetCenterRadius(const Vector3& center, float r)
{
    min[0] = center[0] - r;
    min[1] = center[1] - r;
    min[2] = center[2] - r;
    max[0] = center[0] + r;
    max[1] = center[1] + r;
    max[2] = center[2] + r;
}

// @ 0x0040a170
void EditorList::ApplyEntry(const ResourceKey_s0040_a170* key, const KeyFlags* info)
{
    Iter28_s0040_a170 last, first, cur, endIter;
    void* sm = &slots;

    FUN_00420270(sm, 0, &last, info->index);        // upper_bound(idx)
    FUN_00420120(sm, 0, &first, info->index);       // lower_bound(idx)
    FUN_00422140(&cur, first, last, info, key);     // find_if over [first,last)
    FUN_00420270(sm, 0, &endIter, info->index);     // upper_bound(idx) again (the "end")

    bool exists = (cur.v[0] == endIter.v[0]) &&
                  (cur.v[0] == cur.v[6] || cur.v[1] == endIter.v[1]);
    if (exists) {
        KeyedRecord_s0040_a170 rec;
        FUN_004036e0(&rec);                         // KeyedRecord ctor (tag, zeroed refs)
        void* mem = EASTL_allocator_allocate(0x18, "Editor", 0, 0, 0, 0);
        void* mod = mem ? FUN_00401e40(mem) : 0;
        if (mod != (void*)rec.v[5]) {               // intrusive-ptr assign into rec.v[5]
            if (mod) ++*(uint32_t*)((char*)mod + 4);
            void* old = (void*)rec.v[5];
            rec.v[5] = (uint32_t)mod;
            if (old) FUN_00453540(old);
        }
        FUN_00401ef0(mod, 0, key);                  // modifier takes a copy of the key
        rec.v[0] = key->instance;
        rec.v[1] = key->type;
        rec.v[2] = key->group;
        rec.v[3] = info->id;
        rec.v[4] = info->flags | ((uint32_t)info->index << 16);
        ResourceMessenger* m = GetResourceMessenger();
        m->Send(key->instance, (key->group & 0xffff00ffu) | (0x62u << 8), (RefCounted**)&rec.v[9]);
        m = GetResourceMessenger();
        m->Send(key->instance, (key->group & 0xffff00ffu) | (0x7eu << 8), (RefCounted**)&rec.v[10]);
        if (info->flags & 1)
            FUN_004204f0(sm, 0, &rec, info->index);
        else
            FUN_004204d0(sm, 0, &rec, info->index);
        FUN_00401f20(&rec);
    } else {
        if (info->flags & 0x100) {
            KeyedRecord_s0040_a170* e = (KeyedRecord_s0040_a170*)FUN_005658b0(&cur.v[1]);
            *(uint16_t*)&e->v[4] |= 0x100;
        }
        if (info->flags & 1) {
            KeyedRecord_s0040_a170* e = (KeyedRecord_s0040_a170*)FUN_005658b0(&cur.v[1]);
            KeyedRecord_s0040_a170 rec;
            FUN_004063d0(&rec, 0, e);               // copy the slot's record
            uint32_t dst;
            FUN_00420390(sm, 0, cur, &dst);         // assign at the found iterator
            FUN_004204f0(sm, 0, &rec, info->index);
            FUN_00401f20(&rec);
        }
    }
}

// @ 0x0040a590
bool EditorList::HandleKey(const ResourceKey_s0040_a170* key, const KeyFlags* info)
{
    bool needNotify;
    if (((key->group >> 30) & 3) != 1)
        needNotify = true;
    else
        needNotify = FUN_00401d90(key);

    if (needNotify) {
        uint32_t* msg = (uint32_t*)EASTL_allocator_allocate(0x40, "Editor", 0, 0, 0, 0);
        if (msg) {
            FUN_00423110(msg, 0, 0x695e243);
            msg[0]  = 0x13eb844;   // message vtable
            msg[14] = 0;           // +0x38
        }
        msg[2]  = key->instance;
        msg[4]  = key->group;
        msg[6]  = key->type;
        msg[8]  = info->id;
        msg[10] = 1;
        GetNotifier()->Post(0x695e243, msg, 0, 0);
        return false;
    }

    if (IsEditorType(key)) {
        struct { uint32_t id; uint16_t f; uint16_t i; } ki = { info->id, info->flags, info->index };
        ResourceKey_s0040_a170 k = *key;
        if (((key->group >> 16) & 0xff) == 0x6b) ki.f |= 0x10;
        if (((k.group >> 16) & 0xff) == 0x62) FUN_0068c700(&k, 0);
        EditorList_Forward(this, 0, &k, &ki);
        return true;
    }

    ResourceKey_s0040_a170 k = *key;
    if (((key->group >> 8) & 0xff) == 0x7e) FUN_0068c6d0(&k, 0x62, 0);

    bool handled = false;
    if (!(info->flags & 0x20) && FUN_006a25a0(g_Manager, 0, 0x26cd3a5))
        handled = Accept(&k, (info->flags & 0x100) != 0);

    if (handled) {
        uint32_t* msg = (uint32_t*)EASTL_allocator_allocate(0x40, "Editor", 0, 0, 0, 0);
        if (msg) msg = (uint32_t*)FUN_00421c80(msg, 0, 0x695e243);
        msg[2]  = key->instance;
        msg[4]  = key->group;
        msg[6]  = key->type;
        msg[8]  = info->id;
        msg[10] = 0;
        GetNotifier()->Post(0x695e243, msg, 0, 0);
        return true;
    }
    EditorList_Prepare(this, 0, &k);
    ApplyEntry(&k, info);
    return true;
}

// @ 0x0040a9c0
bool KeyCopier::Copy(const ResourceKey_s0040_a9c0* src, const ResourceKey_s0040_a9c0* dst)
{
    if (!CanCopy(src, 0))
        return false;
    if (src->type != dst->type || src->group.value != dst->group.value)
        return false;

    ResourceManager_s0040_a9c0* mgr = GetResourceManager();
    if (mgr->HasResource(dst->instance, dst->group.value))
        return false;

    bool copied = false;
    PropRef props;

    if (mgr->OpenProperties(src->instance, src->group.value, &props)) {
        bool flag = false;
        GetBoolProperty(props.p, 0x66FADBD, &flag);
        if (flag) {
            cPropertyList* list = new ("Editor", 0, 0, 0, 0) cPropertyList();
            if (list) list->AddRef();
            list->Init(props->extra);
            list->Load(props.p);
            mgr->StoreProperties(list, dst->instance, dst->group.value);
            SavePropertyList(list, 1);
            copied = true;
            if (list) list->Release();
        }
    }
    if (src->group.GetKind() == 0x62 && src->group.GetSub() == 0) {
        ResourceKey_s0040_a9c0 a = *src;
        ResourceKey_s0040_a9c0 b = *dst;
        a.group.SetSub(1);
        b.group = a.group;
        if (copied && CopyKey(&a, &b))
            copied = true;
        else
            copied = false;
    }
    bool result = copied;
    if (props.p) props.p->Release();
    return result;
}

// @ 0x0040ac70
void NearbyObjectList::Refresh(void* listener)
{
    World* world = m_world;
    uint32_t unusedA = m_unk228;       // dead copies kept by the original
    uint32_t unusedB = m_unk230;
    Vector3_s0040_a9c0 center;
    GetWorldCenter(&center, world);
    SetWorldCenter(world, center, 0);
    UpdateWorld(world);

    int* pCount = &m_count;
    *pCount = world->GetObjectCount();
    ObjectVector* list = &m_objects;
    list->Resize(*pCount);

    float maxDist = m_maxDistance;
    for (int i = 0; i < *pCount; i++) {
        WorldObject* obj = world->GetObject(i);
        if (obj) {
            int flag = obj->GetFlag();
            Vector3_s0040_a9c0 objPos;
            obj->GetPosition(&objPos, 1, 0, 0);
            Vector3_s0040_a9c0 origin;
            Vector3_s0040_a9c0 delta = VectorSub(origin, objPos);
            float dist = VectorLength(&delta);
            if (flag && dist >= maxDist)
                list->Remove(&obj);
        }
    }
    *pCount = list->Size();
    m_dirty = 0;
    ((Notifier_s0040_a9c0*)listener)->Notify(this);
}

// @ 0x0040ae50
float VectorLength(const Vector3_s0040_a9c0* v)
{
    return sqrtf(v->x * v->x + v->y * v->y + v->z * v->z);
}

// @ 0x0040aeb0
void Editor_s0040_aeb0::ProcessCurrentPart(void* arg)
{
    if (mCurIndex >= (uint32_t)mParts.size()) {
        ProcessSkipped(arg);
        return;
    }

    const bool editorMode = (mFlags238 & 0x100) != 0;

    EditorPart* part = (EditorPart*)mParts.at((int)mCurIndex);
    PartModel*  model = part->mpModel;
    PartManager* mgr  = part->mpManager;

    // ------------------------------------------------------------------
    // "disabled" property (bool, id 0x065fc9ab) on the part's model
    // ------------------------------------------------------------------
    bool enabled = true;
    PropertyList_s0040_aeb0* props = model->mpProperties;
    if (props != 0) {
        Property_s0040_aeb0* prop = 0;
        Property_s0040_aeb0* check = 0;
        if (props != 0 && props->GetProperty(0x065fc9ab, check) && check->mnType == 1) {
            prop = check;
        }
        if (prop != 0) {
            enabled = !*prop->GetBool();
        }
    }

    // ------------------------------------------------------------------
    // save the model transform, rotate it for this placement, instantiate
    // ------------------------------------------------------------------
    Modifier savedXf;
    savedXf.AssignCopy(model->mTransform);
    model->mTransform.PreRotateY(kPartYaw);

    void* instance = mgr->CreateInstance(model, -1);

    RefVector_s0040_aeb0 keys;
    keys.Construct(&savedXf);                    // tag argument is a dummy local in the original
    EditorRefSlot baker;                         // [ebp-0x60]: filled by BuildKeys (animation baker)
    baker.mpObject = 0;
    EditorRefSlot other;                         // [ebp-0xb0]: filled by BuildKeys
    other.mpObject = 0;

    Modifier composedXf;
    composedXf.AssignCopy(model->mTransform);
    composedXf.Accumulate(*mgr->GetKeyType(model));   // ComposeTransforms(key)

    Modifier keyXf;
    keyXf.AssignCopy(composedXf);

    void* bakerSlot = baker.GetParam();          // 0x0041d870: release, return &mpObject
    void* otherSlot = other.GetRaw();            // 0x0041d900: release, return &mpObject

    bool built = mgr->BuildKeys(model, &keys, bakerSlot, otherSlot, &keyXf);
    if (!built) {
        mgr->GetKeys(model, &keys, &keyXf);
        for (int i = 0; i < keys.size(); i++) {
            FUN_007387f0((int)keys.at(i));
        }
    }
    else {
        int cost = 0;
        if (!keys.empty()) {
            cost = FUN_0071dd80((int)keys.at(0), 5);
        }
        if (mTotalCost + cost <= 0x40) {
            if (mCurIndex == 0) {
                mFirstFlag = 1;
            }
            mTotalCost += cost;
        }
        else {
            if (baker.mpObject != 0) {
                void** vt = *(void***)baker.mpObject;
                ((void (__thiscall*)(void*))vt[1])(baker.mpObject);   // Release
                baker.mpObject = 0;
            }
            if (other.mpObject != 0) {
                other.Release();                 // 0x00453540
                other.mpObject = 0;
            }
            keys.erase(keys.mpBegin, keys.mpEnd);
            mgr->GetKeys(model, &keys, &keyXf);
            for (int i = 0; i < keys.size(); i++) {
                FUN_007387f0((int)keys.at(i));
            }
        }
    }

    // ------------------------------------------------------------------
    // a part always carries at least one ability: an empty key list gets a
    // fresh ListAbility, a non-empty one is truncated to its first entry
    // ------------------------------------------------------------------
    if (keys.empty()) {
        ListAbility* listAbility = (ListAbility*)FUN_00f473a0(
            0x58, kEditorAllocName, 0, 0, 0, 0);
        if (listAbility != 0) {
            listAbility->Ctor();                 // 0x0040d160 ListAbility ctor
            _InterlockedIncrement((volatile long*)&listAbility->mRefCount);
        }
        keys.push_back(listAbility);
        if (listAbility != 0) {
            ((void (__thiscall*)(void*))0x00404f90)(listAbility);  // drop temp ref
        }
    }
    else {
        if (keys.size() > 1) {
            keys.resize(1);
        }
    }
    keys.resize(1);

    void* ability = keys.at(0);
    mInstances.push_back(instance);
    int instanceIndex = mInstances.size() - 1;
    mAbilities.push_back(ability);
    mComposedXforms.push_back(keyXf);
    mEnabledFlags.push_back(*(const uint8_t*)&enabled);

    // ------------------------------------------------------------------
    // baked-animation block (+0x388): either the animations published by the
    // baker object, or an empty transform pair
    // ------------------------------------------------------------------
    if (baker.mpObject != 0 && FUN_0071dd80((int)ability, 5) > 0) {
        void* b = baker.mpObject;
        void** vt = *(void***)b;
        ((void (__thiscall*)(void*))vt[0])(b);                   // AddRef
        FUN_006c1ae0(b, baker.GetParam());                       // GetBakedAnimations
        baker.mpObject = 0;

        uint8_t block[0x7c];
        FUN_00409930(block);                                     // Transform ctor
        *(Modifier*)(block + 0x38) = keyXf;                      // copy ctor in the original
        AutoRefPair refA;                                        // [ebp-0x106c] { -1, baker }
        refA.mId = -1;
        refA.mpObject = 0;
        FUN_0041cc20(&refA, b);                                  // 0x0041cc20 ctor
        EditorRefSlot refB;
        refB.mpObject = 0;
        FUN_0041ccc0(&refB, other.mpObject);                     // 0x0041ccc0 init
        mBakedAnims.push_back(block);
        FUN_00472540(&refB);                                     // ~EditorRefSlot
        FUN_004a9b10(&refA);                                     // ~AutoRefCount

        vt = *(void***)b;
        ((void (__thiscall*)(void*))vt[1])(b);                   // Release
    }
    else {
        uint8_t block[0x7c];
        FUN_00409930(block);                                     // Transform ctor
        FUN_00409930(block + 0x38);                              // second Transform ctor
        AutoRefPair refA;
        refA.mId = 0;
        refA.mpObject = 0;
        EditorRefSlot refB;
        refB.mpObject = 0;
        mBakedAnims.push_back(block);
        FUN_00472540(&refB);
        FUN_004a9b10(&refA);
    }

    // ------------------------------------------------------------------
    // ability-index bookkeeping
    // ------------------------------------------------------------------
    int abilitySlot = mAbilities.size() - 1;
    *mAbilityIndexMap[&abilitySlot] = instanceIndex;

    Item24 entry;
    entry.mKeys.Construct(&savedXf);
    entry.mExtra = 0;
    mEntries.push_back(entry);
    entry.Destroy();

    Item24* lastEntry = (Item24*)((char*)mEntries.mpEnd - 0x18);
    FUN_00756860(lastEntry, mgr, model, instance);

    // ------------------------------------------------------------------
    // editor mode: material streams -> per-material ability/shader objects
    // ------------------------------------------------------------------
    if (editorMode) {
        FUN_00401990(ability);

        int streamIdxA = FUN_0071ddc0(ability, 0x14, 0, 6, 8);
        int streamIdxB = FUN_0071ddc0(ability, 0x15, 0, 6, 8);
        if (streamIdxA >= 0 && streamIdxB >= 0) {
            StreamInfo streamA;
            StreamInfo streamB;
            streamA.Init((char*)ability + 8 + streamIdxA * 0x20 + 0x10);
            streamB.Init((char*)ability + 8 + streamIdxB * 0x20 + 0x10);

            MaterialManager* materialMgr = (MaterialManager*)FUN_0067dd70();
            PairMap* pairMap = (PairMap*)((char*)mEntries.mpEnd - 0x18);

            for (int i = 0; i < (int)streamA.mCount; i++) {
                Material* material = (Material*)materialMgr->GetMaterial(*streamB.Slot(i));
                EmbeddedState* state = material->mpState;
                int shader244 = 0;
                if (state != 0 && (state->mFlags & 8) != 0) {
                    shader244 = state->D3D9GetShaderData(0x244);
                }
                state = material->mpState;
                int shader217 = 0;
                if (state != 0 && (state->mFlags & 8) != 0) {
                    shader217 = state->D3D9GetShaderData(0x217);
                }

                PairIter found;
                pairMap->Find(&found, *streamA.Slot(i));
                int* node = found.mpNode;
                if (node == found.mpEnd) {
                    node = pairMap->mpEndNode;
                }
                TagObject* tagObj = 0;
                if (node != pairMap->mpEndNode) {
                    tagObj = (TagObject*)node[1];
                }

                PartAbilitySlot* slot = (PartAbilitySlot*)FUN_00f473a0(
                    0x1c, kEditorAllocName, 0, 0, 0, 0);
                if (slot != 0) {
                    slot->Ctor();                  // 0x0077d1d0
                    _InterlockedIncrement((volatile long*)&slot->mPad04);
                }

                int idx212 = tagObj != 0 ? tagObj->FindTag(0x212) : -1;
                TagEntry* entry212 = (idx212 >= 0) ? tagObj->mEntries[idx212] : 0;
                void* data212 = entry212 != 0 ? entry212->mpData : 0;

                int idx213 = tagObj != 0 ? tagObj->FindTag(0x213) : -1;
                TagEntry* entry213 = (idx213 >= 0) ? tagObj->mEntries[idx213] : 0;
                void* data213 = entry213 != 0 ? entry213->mpData : 0;

                int idx20d = tagObj != 0 ? tagObj->FindTag(0x20d) : -1;

                if (data212 == 0) {
                    if (data213 != 0) {
                        ColorKey color;
                        color.Ctor();                // 0x0040cf60
                        Ability20* a = (Ability20*)FUN_00f473a0(
                            0x20, kEditorAllocName, 0, 0, 0, 0);
                        if (a != 0) {
                            a->Ctor(0x210, 0x14, 0);
                            a->mField0c = 2;
                            a->mField10 = *(uint32_t*)((char*)data213 + 0x20);
                            a->mField14 = *(uint32_t*)((char*)data213 + 0x24);
                            a->mField18 = *(uint32_t*)((char*)data213 + 0x28);
                            a->mField1c = *(uint32_t*)((char*)data213 + 0x2c);
                            slot->Push((int)a);
                        }
                        uint32_t twoEntries[8];
                        VectorCtorIterator(twoEntries, 0x10, 2, (void*)0x00402ab0);
                        for (int k = 0; k < 8; k++) {
                            twoEntries[k] = *(uint32_t*)((char*)data213 + k * 4);
                        }
                        AbilityData* data = (AbilityData*)FUN_00f473a0(
                            0x2c, kEditorAllocName, 0, 0, 0, 0);
                        if (data != 0) {
                            data->Ctor(twoEntries);  // 0x0041d490
                            slot->Push((int)data);
                        }
                    }
                }
                else {
                    ColorKey color;
                    color.Ctor();                    // 0x0040cf60
                    Ability20* a = (Ability20*)FUN_00f473a0(
                        0x20, kEditorAllocName, 0, 0, 0, 0);
                    if (a != 0) {
                        a->Ctor(0x210, 0x14, 0);
                        a->mField0c = 2;
                        a->mField10 = *(uint32_t*)((char*)data212 + 0x1c);
                        a->mField14 = *(uint32_t*)((char*)data212 + 0x0c);
                        a->mField18 = 0x3f800000;
                        a->mField1c = 0x3e99999a;
                        slot->Push((int)a);
                    }
                    uint32_t twoEntries[8];
                    VectorCtorIterator(twoEntries, 0x10, 2, (void*)0x00402ab0);
                    twoEntries[0] = *(uint32_t*)((char*)data212 + 0x00);
                    twoEntries[1] = *(uint32_t*)((char*)data212 + 0x04);
                    twoEntries[2] = *(uint32_t*)((char*)data212 + 0x08);
                    twoEntries[3] = 0x3f800000;
                    twoEntries[4] = *(uint32_t*)((char*)data212 + 0x10);
                    twoEntries[5] = *(uint32_t*)((char*)data212 + 0x14);
                    twoEntries[6] = *(uint32_t*)((char*)data212 + 0x18);
                    twoEntries[7] = 0x3f800000;
                    AbilityData* data = (AbilityData*)FUN_00f473a0(
                        0x2c, kEditorAllocName, 0, 0, 0, 0);
                    if (data != 0) {
                        data->Ctor(twoEntries);      // 0x0041d490
                        slot->Push((int)data);
                    }
                }

                // shader/state selection
                if (shader244 == 0) {
                    if (shader217 == 0) {
                        if (idx20d >= 0) {
                            int* tagged = (int*)((char*)tagObj->mEntries + idx20d * 4);
                            slot->Push(FUN_0077d710(*tagged));  // 0x0077d710
                        }
                    }
                    else {
                        ResourceKey_s0040_aeb0 key;
                        key.mName = 0;
                        if (!part->GetResourceKey(&key.mName)) {   // 0x0043bf20
                            key.mName = 0xffffffff;
                        }
                        key.mType  = 0x2f4e681c;
                        key.mFlags = 0x40602100;

                        ResourceManager_s0040_aeb0* resMgr = FUN_0067dd60();
                        RefCounted_s0040_aeb0* res = (RefCounted_s0040_aeb0*)resMgr->Create(
                            key.mName, key.mType, key.mFlags, 2);
                        if (res != 0) {
                            _InterlockedIncrement((volatile long*)((char*)res + 8));
                        }
                        bool have = (res != 0) &&
                                    (((*(uint8_t*)((char*)res + 4)) & 4) == 0);
                        if (!have) {
                            key.mName = FUN_00932e80("black", 0x811c9dc5, 1);
                            resMgr = FUN_0067dd60();
                            RefCounted_s0040_aeb0* other = (RefCounted_s0040_aeb0*)resMgr->Create(
                                key.mName, key.mType, key.mFlags, 0);
                            if (other != res) {
                                RefCounted_s0040_aeb0* old = res;
                                if (other != 0) {
                                    _InterlockedIncrement((volatile long*)((char*)other + 8));
                                }
                                res = other;
                                if (old != 0) {
                                    old->Release();
                                }
                            }
                        }
                        if (res != 0) {
                            SlotAbility* sa = (SlotAbility*)FUN_00f473a0(
                                0x70, kEditorAllocName, 0, 0, 0, 0);
                            if (sa != 0) {
                                sa->Ctor();               // 0x0040d010
                                sa->SetResource(0, res);  // 0x0077cb10
                                sa->SetSlot0(0, 1);       // 0x00777a60
                                sa->SetSlot1(0, 2);       // 0x00777a80
                                slot->Push((int)sa);
                            }
                        }
                        if (res != 0) {
                            res->Release();               // 0x00402420
                        }
                    }
                }

                // publish the ability index into the stream slot, or -1
                if (!slot->mAbilities.empty()) {
                    mCounterA++;
                    int* foundNode = 0;
                    mSlotIndexMap.Find(&foundNode, &slot);
                    int* endNode = (int*)((char*)mSlotIndexMap.mpEndNode
                                          + mSlotIndexMap.mBucketCount * 4);
                    if (foundNode[0] == *endNode) {
                        int newIndex = mEntryIndices.size();
                        mEntryIndices.push_back(newIndex);
                        *mSlotIndexMap[&slot] = newIndex;
                        *streamA.Slot(i) = newIndex;
                        mCounterB++;
                    }
                    else {
                        *streamA.Slot(i) = foundNode[1];
                    }
                }
                else {
                    *streamA.Slot(i) = -1;
                }

                if (slot != 0) {
                    ((void (__thiscall*)(void*))0x00404f90)(slot);
                }
            }

            if (streamA.mpRef != 0) {
                ((void (__thiscall*)(void*))((void**)streamA.mpRef)[1])(streamA.mpRef);
            }
            if (streamB.mpRef != 0) {
                ((void (__thiscall*)(void*))((void**)streamB.mpRef)[1])(streamB.mpRef);
            }
        }
    }

    // ------------------------------------------------------------------
    // per-part property tables
    // ------------------------------------------------------------------
    props = model->mpProperties;
    if (props != 0) {
        int count = 0;
        void* base = 0;
        if (FUN_006a0ae0(props, 0x32f4549, &count, &base)) {
            uint32_t bits = part->mFlagsDcc;
            if ((bits & 0x80) != 0) {
                Modifier* partXf = FUN_0043d220(part);
                Modifier tmp;
                tmp.AssignCopy(model->mTransform);
                tmp.Accumulate(*partXf);
                Modifier out;
                out.AssignCopy(tmp);
                for (int i = 0; i < count; i++) {
                    mVarA.push_back(*(Vector3_s0040_aeb0*)((char*)base + i * 0xc));
                    mVarB.push_back(out);
                }
            }
            else {
                int have = 0;
                void* table = 0;
                FUN_006a0c30(props, 0x2a907b6, &have, &table);
                for (int i = 0; i < count; i++) {
                    mVarA.push_back(*(Vector3_s0040_aeb0*)((char*)base + i * 0xc));
                    if (i < have) {
                        Modifier tmp;
                        tmp.AssignCopy(model->mTransform);
                        tmp.Accumulate(*(Modifier*)((char*)table + i * 0x38));
                        mVarB.push_back(tmp);
                    }
                    else {
                        mVarB.push_back(model->mTransform);
                    }
                }
            }
        }

        float keyPos[3] = { 0.0f, 0.0f, 0.0f };
        if (FUN_006a1250(props, 0xf1fae962, keyPos)) {
            const int kPartTag = (int)0xc045a9a3;
            int partCount = mgr->GetPartCount(model);        // vtable +0x84
            PartKeyVec keyVec;
            keyVec.Init(partCount);                          // 0x0041d0c0
            int* partKeys = (int*)keyVec.mpBegin;
            mgr->GetPartKeys(model, partKeys);               // vtable +0x90

            Modifier partXf;                                 // [ebp-0x3b4]
            FUN_00409930(&partXf);
            for (int i = 0; i < partCount; i++) {
                if (partKeys[i] != kPartTag) {
                    continue;
                }
                Modifier secondXf;                           // [ebp-0x1048]
                FUN_00409930(&secondXf);
                TransformVec2 tvec;
                tvec.Init(partCount);                        // 0x0041d510
                void* keyData = tvec.mpBegin;
                mgr->GetData2(model, (int*)keyData);         // vtable +0x8c
                FUN_00732270((char*)keyData + i * 0x30, &partXf);
                mgr->GetData3(model, (int*)keyData, 0);      // vtable +0x88
                FUN_00732270((char*)keyData + i * 0x30, &secondXf);
                partXf.Accumulate(secondXf);                 // 0x0040ccb0
                partXf.AccumulateScaled(*mgr->GetKeyType(model)); // 0x0040cd80
                tvec.Done();                                 // 0x004222a0
                break;
            }

            int newIndex = -1;
            if (!keys.empty()) {
                newIndex = mBakedAnims.size() - 1;
            }
            Modifier tmp;
            tmp.AssignCopy(model->mTransform);
            tmp.Accumulate(partXf);
            Modifier out;
            out.AssignCopy(tmp);
            mVarD.push_back(*(Vector3_s0040_aeb0*)keyPos);
            mVarB.push_back(out);
            mVarE.push_back(newIndex);
            if (part->mField3e0 == 0) {
                mVarD.push_back(*(Vector3_s0040_aeb0*)keyPos);
                mVarB.push_back(out);
                mVarE.push_back(newIndex);
            }
            keyVec.Done();                                   // 0x004209b0
        }

        float thresholdValue = 0.0f;
        int haveInt = 0;
        Property_s0040_aeb0* p = 0;
        if (props != 0 && props->GetProperty(0x46d0560, p) && p->mnType == 0xa) {
            thresholdValue = (float)*p->GetUIntValue();
            haveInt = 1;
        }
        float scaled = 0.0f;
        if (haveInt && FUN_0040cf10(props, 0x46d0572, &scaled)) {
            float s = scaled * part->mScale;
            if (mScaleLimit <= s && s != mScaleLimit) {
                mThreshold = (int)thresholdValue;
                mScaleUsed = part->mScale;
            }
        }
    }

    model->mTransform.AssignFrom(savedXf);
    FUN_00472540(&other);
    FUN_004a9b10(&baker);
    FUN_0041eb80(&keys);

    mCurIndex++;
    ((EditorArg*)arg)->Finish(this);
}

// @ 0x0040cf60
ColorKey_s0040_ccb0::ColorKey_s0040_ccb0()
{
    type = 2;
    a = kZero;
    b2 = kZero;
    c = kOne;
    d = kZero;
    r = 0x5c;
    g = 0x44;
    b = 0x26;
}

// @ 0x0040cfd0
// The constructor is an in-class (inline) definition. This helper (not in the
// original) keeps one out-of-line copy of it alive so it is emitted as a symbol.
#pragma inline_depth(0)
void* KeepCreatureAbilityCtor(void* mem, uint16_t a, uint16_t b, void* c)
{
    return new (mem) CreatureAbility_s0040_ccb0(a, b, c);
}
#pragma inline_depth()

// @ 0x0040d010
SlotAbility_s0040_ccb0::SlotAbility_s0040_ccb0()
: CreatureAbility_s0040_ccb0(0x20d, 100, &mSlots)
{
    memset(&mSlots, 0, sizeof(mSlots));
}

// @ 0x0040d160
ListAbility_s0040_ccb0::ListAbility_s0040_ccb0()
{
}

// @ 0x0040d2d0
void __fastcall RefreshProperties(char* self)
{
    int*  model = *(int**)(self + 0x334);
    void* flagsBlock = self + 0x234;
    void* editorBlock = self + 0x388;
    (void)flagsBlock;

    if (!IsEditorMode(editorBlock)) {
        char tmpA[0x40]; (void)tmpA;
        InitEmptyA(0); InitEmptyA(0);
        LocalCleanup1();
        LocalCleanup2();
    }

    IPropertyBag** bagPtr = (IPropertyBag**)(self + 0x434);
    if (*bagPtr == 0) {
        LocalCleanup3();
        FinishRefresh(self);
        return;
    }

    RangeVec_s0040_d2d0* vecA = (RangeVec_s0040_d2d0*)(self + 0x438);
    RangeVec_s0040_d2d0* vecB = (RangeVec_s0040_d2d0*)(self + 0x510);
    RangeVec_s0040_d2d0* vecC = (RangeVec_s0040_d2d0*)(self + 0x8a8);
    RangeVec_s0040_d2d0* vecD = (RangeVec_s0040_d2d0*)(self + 0x980);
    RangeVec_s0040_d2d0* vecE = (RangeVec_s0040_d2d0*)(self + 0xd18);
    int*      keyOrPtr = (int*)(self + 0xd70);
    void*     keyVal   = self + 0xd78;

    {
        PropVal v; v.type = 9; v.flags = 2;
        WrapInt(self + 0xd88);
        (*bagPtr)->SetProperty(0x7ff150b, &v);
        if (v.flags & 4) FreePropVal(0);
    }

    if (!IsEditorMode(editorBlock)) {
        float scale = 1.0f;
        bool haveScale;
        PropInfo* info;
        if (*bagPtr == 0 || !(*bagPtr)->GetPropertyInfo(0xfba611, &info) || info->typeId != 0xd) {
            haveScale = false;
        } else {
            scale = *GetDefaultScale();
            haveScale = true;
        }
        if (haveScale) {
            int n = (vecB->end - vecB->begin) / 14;
            for (int i = 0; i < n; i++) ApplyScale(*(int*)&scale);
        }
        PropVal p1, p2;
        WrapArray(0x20, 0x98, vecA->begin, 0xc, (vecA->end - vecA->begin) / 3);
        WrapArray(0x38, 0x98, vecB->begin, 0x38, (vecB->end - vecB->begin) / 14);
        (*bagPtr)->SetProperty(0x2a907b5, &p1);
        (*bagPtr)->SetProperty(0x2a907b6, &p2);
        if (p2.flags & 4) FreePropVal(0);
        if (p1.flags & 4) FreePropVal(0);
    }

    if (!IsEditorMode(editorBlock)) {
        float scale = 1.0f;
        bool haveScale;
        PropInfo* info;
        if (*bagPtr == 0 || !(*bagPtr)->GetPropertyInfo(0xfba611, &info) || info->typeId != 0xd) {
            haveScale = false;
        } else {
            scale = *GetDefaultScale();
            haveScale = true;
        }
        if (haveScale) {
            int n = (vecD->end - vecD->begin) / 14;
            for (int i = 0; i < n; i++) ApplyScale(*(int*)&scale);
        }
        PropVal a, b, c;
        WrapArray(0x20, 0x98, vecC->begin, 0xc, (vecC->end - vecC->begin) / 3);
        WrapArray(0x38, 0x98, vecD->begin, 0x38, (vecD->end - vecD->begin) / 14);
        WrapArray(9, 0x98, vecE->begin, 4, vecE->end - vecE->begin);
        (*bagPtr)->SetProperty(0xf1fae962, &a);
        (*bagPtr)->SetProperty(0xf1fae963, &b);
        (*bagPtr)->SetProperty(0x4caccce, &c);
        if (c.flags & 4) FreePropVal(0);
        if (b.flags & 4) FreePropVal(0);
        if (a.flags & 4) FreePropVal(0);
    }

    if ((*bagPtr)->HasProperty(0x720be500) && (*bagPtr)->HasProperty(0x720be501) &&
        (*bagPtr)->HasProperty(0x720be502)) {
        char dummy;
        InitBool(&dummy);
        KeyedFloatList list;
        CollectKeyedFloats(model, &list);
        float total = 0.0f;
        int count = list.last - list.first;
        for (int i = 0; i < count; i++) {
            float v = list.first[i].value * 0.1;
            uint32_t k = list.first[i].key;
            if (k < 0x11b78a72) {
                if (k == 0x11b78a71) {
                    PropVal pv; WrapFloat(&v);
                    (*bagPtr)->SetProperty(0x720be502, &pv);
                    if (pv.flags & 4) FreePropVal(0);
                } else if (k > 0x6329467) {
                    if (k < 0x632946b) { total += v; }
                    else if (k == 0x11b78a70) {
                        PropVal pv; WrapFloat(&v);
                        (*bagPtr)->SetProperty(0x720be500, &pv);
                        if (pv.flags & 4) FreePropVal(0);
                    }
                }
            } else if (k == 0x11b78a72) {
                total += v;
            }
        }
        PropVal pt; WrapFloat(&total);
        (*bagPtr)->SetProperty(0x720be501, &pt);
        if (pt.flags & 4) FreePropVal(0);
        FreeKeyedFloats();
    }

    int part = ((IModelData*)model)->GetPartRoot();
    if (part != 0) {
        char tmp[20];
        int info = GetPartInfo(part, tmp);
        PropVal pv; WrapPtr((void*)info);
        (*bagPtr)->SetProperty(0x43afa7e, &pv);
        if (pv.flags & 4) FreePropVal(0);
        PostPart();
    }

    int* keyPtr = keyOrPtr;
    if (*keyPtr != 0) {
        PropVal p1; WrapKey(keyPtr);
        (*bagPtr)->SetProperty(0x46d0560, &p1);
        if (p1.flags & 4) FreePropVal(0);
        PropVal p2; WrapFloat((float*)keyVal);
        (*bagPtr)->SetProperty(0x46d0572, &p2);
        if (p2.flags & 4) FreePropVal(0);
    } else {
        int one = 1;
        PropVal p;
        WrapInt(&one);
        (*bagPtr)->SetProperty(0x46d0572, &p);
        if (p.flags & 4) FreePropVal(0);

        int kind = model[0x16];
        int* which = 0;
        switch (kind) {
        case -0x43efbe1a: case -0x65282b56: case -0x3f48bd79: case -0x98f55bd:
        case 0x7d433fad:
            which = &g_KeyA; break;
        case -0x7069c235: case -0x3ea96a26: case 0x1f2a25b6: case 0x2a5147a9:
            which = &g_KeyB; break;
        case 0x1a4e0708: case -0x671fc3f3: case 0x441cd3e6: case 0x2090a11b:
        case 0x449c040f:
            which = &g_KeyC; break;
        }
        if (which) {
            PropVal pk; WrapKey(which);
            (*bagPtr)->SetProperty(0x46d0560, &pk);
            if (pk.flags & 4) FreePropVal(0);
        }
    }

    if (!(*bagPtr)->HasProperty(0x4a5b8d2)) {
        if (model[0x16] == 0x47c10953) {
            PropVal pv; WrapKey(&g_KeyD);
            (*bagPtr)->SetProperty(0x4a5b8d2, &pv);
            if (pv.flags & 4) FreePropVal(0);
        } else if (model[0x16] == 0x72c49181) {
            PropVal pv; WrapKey(&g_KeyE);
            (*bagPtr)->SetProperty(0x4a5b8d2, &pv);
            if (pv.flags & 4) FreePropVal(0);
        }
    }

    bool hasFlag = (*(uint16_t*)(self + 0x238) & 0x100) != 0;
    if (hasFlag) {
        int v1 = *(int*)(self + 0x10fc);
        PropVal pa; WrapInt(&v1);
        (*bagPtr)->SetProperty(0xafb4cda4, &pa);
        if (pa.flags & 4) FreePropVal(0);
        int v2 = *(int*)(self + 0x10f8);
        PropVal pb; WrapInt(&v2);
        (*bagPtr)->SetProperty(0x98e3be5, &pb);
        if (pb.flags & 4) FreePropVal(0);
    }

    LocalCleanup3();
    FinishRefresh(self);
}

// @ 0x0040e5b0
bool Obj::OnA(int)
{
    Flags* o = &opts;
    if (o->flags & 4) {
        RefPtr_s0040_e5b0 res;
        wchar_t* name = L"unknown";
        res.p = 0;
        void* dirOwner;
        if (GetApp()->GetKind() == 0xDBDBA1) {
            PathProvider* pp = GetApp()->GetPathProvider();
            name = ((PathNameRef*)pp->GetName())->GetString();
            GetSink()->Set(pp->Lookup(g_SomeKey, res.Reset()));
        }
        if (Query(res.p, &dirOwner) && GetDir(dirOwner)) {
            FormatPath(path, L"%ls/%ls.zpr", GetDir(dirOwner)->GetDirName(), name);
        } else {
            FormatPath(path, L"%ls.zpr", name);
        }
        if (res.p)
            res.p->Release();
    }
    BigScratch scratch;
    str42c.Assign(scratch.Init());
    scratch.Done();
    GetMsgManager()->Post(0x29D252F, 0, 0);
    return true;
}

// @ 0x0040e800
bool Dispatcher::Handle(uint32_t id, int arg)
{
#define OBJ ((Obj*)((char*)this - 4))
    switch (id) {
    case 0x29D252F: return OBJ->OnClear(arg);
    case 0x2458018: return OBJ->OnReset(arg);
    case 0x67B65F1: return OBJ->Fn40eb70();
    case 0x67B65F2: return OBJ->Fn40f110();
    case 0x245801E: return OBJ->Fn40f3f0(arg);
    case 0x522264D: return OBJ->Fn40f4a0(arg);
    case 0x52DEB99: return OBJ->Fn40f820(arg);
    case 0x5302B02: return OBJ->Fn40fc00(arg);
    case 0x530781E: return OBJ->Fn40fe00(arg);
    case 0x52DEB9E: return OBJ->Fn4103c0(arg);
    case 0x29D3C4C: return OBJ->Fn410dd0(arg);
    case 0x29D57F4:
        if (enabled)
            return OBJ->Fn410f90(arg);
        else
            return false;
        break;
    }
    return false;
#undef OBJ
}

// @ 0x0040e9c0
bool Obj::OnClear(int)
{
    int i = 0;
    int count = vec.size();
    for (; i < count; i = i + 1) {
        void* p = *(void**)(vec.begin + i * 16 + 0xc);
        ReleaseBlock(p);
    }
    vec.clear();
    f3f8 = 0;
    ProcessLayout(lay338, f228, f230, f3f8, f39c, f3b0, f3c8, f374);
    return true;
}

// @ 0x0040eab0
bool Obj::OnReset(int)
{
    // Retain the unused inlined clear frame without reading its storage.
    uint32_t resetFrame[10];
    Range2* clearRange = &r34c;
    clearRange->Clear(clearRange->begin, clearRange->end);
    f3f8 = 0;
    f3fc = 0x10;
    {
        Provider* prov = provider;
        if (prov) {
            Prop* prop;
            if (prov->GetProp(0x67B804D, &prop) && prop->type == 9) {
                f3fc = *((ValueRef*)prop)->Get();
            }
        }
    }
    { uint32_t finalFrame; }
    GetMsgManager()->Post4(0x67B65F1, 0, 0, 0);
    return true;
}

// @ 0x0040eb70
bool EditorPartList::ProcessBatch()
{
    int n = mKeys.size();
    int stop = n;
    if (stop - mStart > mCount)
        stop = mStart + mCount;
    bool pro = (mFlags & 0x100) != 0;
    for (int i = mStart; i < stop; ++i) {
        Key* key = mKeys.At(i);
        PartXform38* xf = &mpXf38[i];
        int b;
        if (pro)
            ApplyPart(key, xf, 2);
        FitPart(&mpXf38[i], mKeys.At(i));
        if (pro) {
            HolderPtr<PartHolder> hold(new ("Editor") PartHolder((const PartHolder*)key));
            TouchPart((Key*)hold.mp, 0, 2);
            mHolders.push_back(&hold.mp);
            IntVec vec;
            int x0 = QueryPart(key, 0x14, 0, 0, 0xe);
            if (x0 >= 0)
                vec.push_back(x0);
            b = QueryPart(key, 8, 2, 0, 0xe);
            if (b >= 0)
                vec.push_back(b);
            if (!vec.empty()) {
                ApplyShapes(key, (unsigned)(vec.mpEnd - vec.mpBegin), vec.data());
            }
        }
        TouchPart(mKeys.At(i), 0, 1);
        if (At7c(i)->GetSource()) {
            mpXf7C[i].Rebuild(At38(i));
            mpXf7C[i].Invert();
        }
    }
    if (stop < n) {
        mStart = stop;
        GetMessenger()->Post(0x67B65F1, 0, 0, 0);
    } else {
        bool ok = true;
        ReadFlag(ok);
        if (ok)
            GetMessenger()->Post(0x67B65F2, 0, 0, 0);
        else
            GetService2()->Run(0x245801E);
    }
    return true;
}

// @ 0x0040efa0
void PartTransform::Invert()
{
    mScale = kOne / mScale;
    Matrix3_s0040_eb70 tmp;
    mRotation = *Matrix3Inverse(&tmp, &mRotation);
    mPosition *= -mScale;
    mPosition.MulAssign(mRotation);
}

// @ 0x0040f070
PartHolder::PartHolder(const PartHolder* src)
: mA(src->mA), mB(src->mB), mC(src->mC), mD(src->mD) {}

// @ 0x0040f110
bool EditorPartList::Rescan()
{
    unsigned filter = 0x40B1A842;
    bool found = false;
    mpProps->Get(0x5B9A4FB, &filter);
    mpProps->GetBool(0x5B9A1EC, &found);
    if (!found) {
        KeyVec keys((AllocTag()));
        keys.reserve(mKeys.size());
        for (unsigned idx = 0; idx < mKeys.size(); ++idx) {
            if (mpEnabled[idx])
                keys.push_back(&mKeys.mpBegin[idx]);
        }
        Merge(&keys, 0x2E9E052, 0x2E9E05E, 0, &mpXf7C, 0);
        mpCached = GetSource()->Lookup(0x2E9E052, 0x2E9E05E, 0);
        KeyVec w;
        Collect(&w, GetSourcePlain(), filter, 0);
    } else {
        Collect(&mKeys, GetSourceWide(), filter, 1);
    }
    return true;
}

extern "C" {
extern void* vtbl_Editor_cEditorResource[];
extern void* vtbl_Simulator_cCreatureAbility[];
extern void* vtbl_BakeJob_Final0[];   // 0x013eb928
extern void* vtbl_BakeJob_Final1[];   // 0x013eb924
}

// Base pieces of the bake job (see s004103c0 for the constructor).
struct BakeJobDtor {
    void** vp;                // +0
    void** vp2;               // +4
    uint32_t pad8;            // +8 (refcount)
    bool mbDone;              // +0xC
    ~BakeJobDtor();
};

// @ 0x00410d70
BakeJobDtor::~BakeJobDtor()
{
    vp = vtbl_BakeJob_Final0;
    vp2 = vtbl_BakeJob_Final1;
    if (!mbDone) {
        GetMessageManager()->Post4(0x29d3c4c, 0, 0, 0);
    }
    vp2 = vtbl_Simulator_cCreatureAbility;
    vp = vtbl_Editor_cEditorResource;
}

// @ 0x00410dd0
bool EditorHost::OnUpdate(int)
{
    if (mFlags & 4) {
        int arg;
        int h;
        uint16_t x;
        uint16_t y;
        SlotInfo* info;
        uint32_t key[2];
        uint32_t handle[7];
        Request_s0041_0d70* req;
        key[0] = 0xffffffff;
        key[1] = 0xffffffff;
        GetCursorSource()->GetCurrent(key);
        info = GetSlotTable()->Lookup(key[0], key[1]);
        y = info->mY;
        x = info->mX;
        req = CreateRequest(x, y, 1, 0x208, 0x15);
        if (req->Open(2, 0, handle)) {
            h = req->GetHandle(0);
            ((SlotRef*)info)->Bind(handle[0], h, 0);
            req->Close(handle);
        }
        if (!((FlagCheck*)mCallbackObj)->IsSet()) {
            arg = mCallbackArg;
            SubmitCallback(*(Callback*)mCallbackObj, req, arg);
        }
        DestroyRequest(req);
    }
    if (mbPending) {
        GetMessageManager()->Post3(0x3fc3f13, 0, 0);
        mbPending = false;
    } else if (!mbHaveOwner || mOwner == 0) {
        GetMessageManager()->Post3(0x29d57f4, 0, 0);
    }
    return true;
}

// @ 0x00410f90
bool EditorHost2::OnFrame(int)
{
    if (mpHolder) {
        OwnerHolder* h = mpHolder;
        ((void (__thiscall*)(void*, void*, int))(*(void***)(*(void***)h))[0x16c / 4])(*(void**)h, h, 0);
        OwnerHolder** pp = &mpHolder;
        if (*pp) {
            OwnerHolder* old = *pp;
            *pp = 0;
            if (old) {
                ReleaseHolder(old);
            }
        }
    }
    int i = 0;
    int n = mVec.Count();
    for (; i < n; ++i) {
        void* p = mVec.PtrAt(i);
        EASTL_allocator_deallocate(p);
    }
    mVec.DestroyRange(mVec.mpBegin, mVec.mpEnd);
    mTimerB.Update();
    float a = (float)mTimerB.Read() * mTimerB.mScale;
    float b = (float)mTimerA.Read() * mTimerA.mScale + a;
    mLastTime = b;
    mTotalTime += b;
    ++mBakeCount;
    if (mFlags & 0x40) {
        uint32_t res = mpResource;
        ((void (__thiscall*)(void*, uint32_t, bool, const wchar_t*))vp[0x70 / 4])
            (this, res + 8, (mFlags & 0x80) != 0, L"PreBaked");
    }
    ++mFrameCount;
    GetTimeSource()->Tick();
    SubStep(mSub, b, a);
    Finish(0);
    return true;
}

// @ 0x004111e0
namespace SendSel {
void Panel_s0041_11e0::PostSelectionMessages(Params* p, float f1, float f2)
{
    Msg_s0041_11e0* mm;
    Msg_s0041_11e0* m2;
    bool owns = !(flags238 & 2);
    TRef target;
    target.p = 0;
    GetLookup()->Find(p->a, p->c, target.Out());
    if (target.p) {
        if (target.Has(0x3704e55)) {
            target.SetBool(0x3704e55, true);
            Msg_s0041_11e0 m(0xf62def);
            m.vtbl = (void*)0x13eb844;
            m.f38 = 0;
            m.Set(0, 0xb1b104);
            m.Set(1, p->c);
            m.Set(2, p->a);
            GetMsgMgr()->Post(0xf62def, &m, 0, 0);
            if (owns) FreeTarget(target.p, 1);
            m.Destroy();
        }
    }
    uint32_t idc = p->c;
    if (TypeOf(idc) == 0x62) {
        Id id2 = WithClass(*(Id*)&p->c, 1);
        GetLookup()->Find(p->a, id2.raw, target.Out());
        if (target.p) {
            if (target.Has(0x3704e55)) {
                target.SetBool(0x3704e55, true);
                Msg_s0041_11e0 m(0xf62def);
                m.vtbl = (void*)0x13eb844;
                m.f38 = 0;
                m.Set(0, 0xb1b104);
                m.Set(1, id2.raw);
                m.Set(2, p->a);
                GetMsgMgr()->Post(0xf62def, &m, 0, 0);
                if (owns) FreeTarget(target.p, 1);
                m.Destroy();
            }
        }
    }
    NEW_HMSG(mm, 0x4d18324)
    mm->Set(0, p->a);
    mm->Set(1, p->c);
    mm->Set(2, p->b);
    mm->SetF(3, f1);
    mm->SetF(4, f2);
    GetMsgMgr()->Post(0x4d18324, mm, 0, 0);
    NEW_HMSG(m2, 0x695e243)
    m2->Set(0, p->a);
    m2->Set(1, p->c);
    m2->Set(2, p->b);
    m2->Set(3, arg234);
    m2->Set(4, 0);
    GetMsgMgr()->Post(0x695e243, m2, 0, 0);
    sentFlag = 1;
    if (target.p) target.p->Release();
}
}  // namespace SendSel

// @ 0x00411890
namespace ResetSel {
void Panel_s0041_11e0::CommitAndReset(bool flag)
{
    TmpB b;
    if ((flag2c4 || flag259) && !sentFlag && selId != 0 && selId != (uint32_t)-1) {
        Msg_s0041_11e0* m = new ("Editor") BMsg(0x695e243);
        m->Set(0, selId);
        m->Set(1, arg230);
        m->Set(2, arg22c);
        m->Set(3, arg234);
        m->Set(4, (flag != 0) + 1);
        GetMsgMgr()->Post(0x695e243, m, 0, 0);
    }
    preloader.Reset();
    { TmpA a; ((Sel*)&selId)->Set(a.Init()); a.Fini(); }
    if (obj330.Get()) {
        obj330->Release(1);
        obj330.Reset();
    }
    ((PtrHolder*)&obj330)->Set(b.Init()); b.Fini();
    flag2c4 = 0;
    flag259 = 0;
    sentFlag = 0;
}
}  // namespace ResetSel

// @ 0x00411b90
namespace A {
Obj_s0041_1b90& Obj_s0041_1b90::operator=(const Obj_s0041_1b90& o)
{
    Owned_s0041_1b90* old;
    Owned_s0041_1b90* n = o.owned;
    if (n != owned) {
        old = owned;
        if (n) n->AddRef();
        owned = n;
        if (old) old->Release();
    }
    f04.Set(o.f04.pad);
    f08.Assign(o.f08);
    f1c.Assign(o.f1c);
    f30.Assign(o.f30);
    f44.Assign(o.f44);
    f58.Assign(o.f58);
    f6c.Assign(o.f6c);
    f80.Assign(o.f80);
    f98.Assign(o.f98);
    fac.Assign(o.fac);
    AssignShared(&c0, o.c0);
    AssignShared(&c4, o.c4);
    c8 = o.c8;
    cc = o.cc;
    if (&o.d0 != &d0) d0.Assign(o.d0.first, o.d0.last);
    fe0.Assign(o.fe0);
    f4a = o.f4a;
    f4b = o.f4b;
    f8 = o.f8;
    fc.Assign(o.fc);
    t0 = o.t0; t1 = o.t1;
    return *this;
}
}  // namespace A

// @ 0x00411e50
namespace B {
void Obj2::Tick()
{
    uint32_t keyI = keyInst;
    uint32_t keyT = keyType;
    uint32_t keyG = keyGroup;
    ModelList* list = cell->mid->inner->models;
    if (list) {
        if (!list->IsEmpty() && (*list->items)->type == 0x210) {
            TransformHdr* h = (*list->items)->hdr;
            h->x = ((Cam*)cell)->x;
            h->y = ((Cam*)cell)->y;
            h->z = ((Cam*)cell)->z;
        }
    }
    IProps* props = 0;
    IResMgr* mgr = GetResMgr();
    if (mgr->Open(keyI, (keyG & 0xffff00ff) | 0x6200, 0)) {
        bool flag;
        if (GetBoolProperty(props, 0x3f32ad2, &flag) && flag) {
            if (keyT == 0x438f6347) {
                uint32_t nameId = GetNameId(0);
                Str16 s;
                s.kind = 2;
                s.flags = 9;
                MakeStr(&s, &nameId);
                props->SetValue(0x4239b99, &s);
                if (s.kind & 4) FreeStr(0);
            }
            ApplyProps(props, f74, 0);
        }
    }
    float a = 0.0f, b = 0.0f;
    UpdateCounter(&c2);
    b = (float)ReadCounter(&c2) * c2.scale;
    a = (float)ReadCounter(&c1) * c1.scale + b;
    lastA = b;
    sumA = sumA + b;
    cntB = cntB + 1;
    if (flags & 0x40)
        SetPreBaked(&keyI, (flags & 0x80) != 0, L"PreBaked");
    cntA = cntA + 1;
    if (!(flags & 2)) {
        void* buf = AllocBuf(0x11ac1ac);
        BindKey(keyInst, keyGroup, buf, 1);
        uint32_t g2 = (keyGroup & 0xffff00ff) | 0xe300;
        BindKey(keyInst, g2, buf, 1);
        if (((keyG >> 16) & 0xff) == 0x62) {
            IKeyHolder* holder = 0;
            IResMgr* m2 = GetResMgr();
            if (holder) { IKeyHolder* t = holder; holder = 0; t->Release(); }
            if (m2->Open(keyI, (keyG & 0xe0ffffff) | 0x01000000, 0)) {
                IIter* it = GetIter();
                for (int i = 0; i < 4; ++i) {
                    uint32_t k[4] = { 0, 0, 0, 0 };
                    if (FindEntry(holder, 0xf9efbb + i, k) && ((k[2] >> 24) & 0x1f) == 1) {
                        IRelease* out = 0;
                        if (it->Next(k, &out, 0, 0, 0, 0)) PutBack(out, 1);
                        if (out) out->Release();
                    }
                }
            }
            if (holder) holder->Release();
        }
    }
    ApplyBlend(&keyInst, a, b);
    if (props) ((IRelease*)props)->Release();
}
}  // namespace B

// @ 0x004124b0
void Owner::Rebuild()
{
    entries.clear();
    offsets.clear();

    IResourceManager_s0041_24b0* mgr = GetResourceManager_s0041_24b0();
    KeyVector_s0041_24b0 keys((Tag()));
    mgr->GetKeys(g_ResourceGroup, &keys);

    for (int i = 0, n = keys.size(); i < n; i++) {
        RefSlot res = {0};
        int subCount; Entry* subs;
        if (mgr->GetResource(keys[i], g_ResourceGroup, res.Out())) {
            if (GetArrayProp(res.p, 0xf05faa79, &subCount, &subs) && subCount != 0) {
                for (int j = 0; j < subCount; j++) {
                    RefSlot sub = {0};
                    int* dataB; int cntA; void* dataA; int cntC; int* dataC; int cntB;
                    if (mgr->GetResource(subs[j].key, g_ResourceGroup, sub.Out())) {
                        if (GetArrayPropC(sub.p, 0x105f5303, &cntA, &dataA) &&
                            GetArrayPropB(sub.p, 0x105f5302, &cntB, &dataB) &&
                            GetArrayPropB(sub.p, 0x105f5304, &cntC, &dataC) &&
                            cntA >= 3 && cntA == cntB && cntA == cntC)
                        {
                            GrowEntries();
                            Entry* e = entries.end - 1;
                            e->key = keys[i];
                            e->count = cntA;
                            e->offset = offsets.size();
                            offsets.append(dataA, (char*)dataA + cntA * 12);
                            offsets.append(dataB, dataB + cntA);
                            offsets.append(dataC, dataC + cntA);
                        }
                    }
                    if (sub.p) sub.p->Release();
                }
            }
        }
        if (res.p) res.p->Release();
    }
    SortEntries_s0041_24b0(entries.begin, entries.end);
    for (uint32_t* p = keys.begin; p < keys.end; p++) {}
    keys.Destroy();
}

// @ 0x00412900
namespace A {
int Builder::BuildRope(Node* nodes, int count, int idx, uint32_t colA, uint32_t colB, uint32_t colMid, int prev)
{
    const uint32_t kPropWidth = 0xfe0926f6, kPropScale = 0xfba611, kPropA = 0x105f54ff, kPropB = 0xf061e767;
    Node* n = nodes + idx;
    float radius = n->radius;
    Vec3 base = n->pos;
    Vec3 dir = { 0.0f, -radius, 0.0f };
    Vec3 tmp;
    dir = *Vec3Transform(&tmp, &dir, &n->axis);
    Vec3Normalize(&dir, &n->pos);

    int fx = LookupEffect(n->keyA, n->keyB);
    if (fx != 0) {
        float minW = 0.5f;
        GetFloatProp(fx, kPropWidth, &minW);
        float minWidth = minW * 0.1f;
        if ((n->flags & 0x10) == 0) {
            float scale = 1.0f; int keyA = 0, keyB = 0;
            GetFloatProp(fx, kPropScale, &scale);
            GetIntProp(fx, kPropA, &keyA);
            GetIntProp(fx, kPropB, &keyB);
            if (keyA == 0 || keyB == 0) {
                Vec3 d1; Vec3 e = *Vec3Sub(&d1, (Vec3*)((char*)n + 0x20), (Vec3*)((char*)n + 0x14));
                float len = Vec3Length(&e);
                float lo = 0.01f;
                const float* pl = (len <= lo) ? &lo : &len;
                float base_w = *pl;
                float w3 = base_w * 3.0f, w27 = base_w * 2.7f, w2 = base_w * 2.0f;
                float half = 0.5f;
                Vec3 t1, t2, t3;
                Vec3 mid = *Vec3Add(&t3, &base, Vec3Unary(&t2, Vec3SubScaled(&t1, &dir, &base, &half)));
                if (prev == -1) prev = path->AddPoint(&base, kOne_s0041_2900, w3, colA | 0x80000000);
                int pm = path->AddPoint(&mid, kOne_s0041_2900, w27, colMid);
                int pe = path->AddPoint(&dir, kOne_s0041_2900, w2, colB | 0x80000000);
                path->Link(prev, pm, kLinkW, colMid);
                path->Link(pm, pe, kLinkW, colMid);
            } else {
                int data = dataBase;
                int* tb = (int*)tracks.pad;  // list begin (approx)
                int* lb = *(int**)&tracks.first;
                int* le = (int*)((char*)lb + ((((char*)tracksEnd - (char*)lb) / 12) * 12));
                int* sa = FindFirst(lb, le, &keyA);
                int* sb = FindFirst(lb, le, &keyB);
                int na = 0, nb = 0;
                int* pa = sa; int* pb = sb;
                for (; pa != le && *pa == keyA; pa += 3) na++;
                for (; pb != le && *pb == keyB; pb += 3) nb++;
                (void)tb;
                if (na == nb) {
                    for (int k = 0; k < na; k++) {
                        int cnt = sa[k * 3 + 1];
                        if (sa[k * 3 + 1] != sa[k * 3 + 1]) break;
                        int offA = data + sa[k * 3 + 2] * 4;
                        int offB = data + sb[k * 3 + 2] * 4;
                        int posA = offA, widA = offA + cnt * 12, wA = offA + cnt * 16;
                        int posB = offB, widB = offB + cnt * 12, wB = offB + cnt * 16;
                        int cur = (*(int*)((char*)path + 0xc) - *(int*)((char*)path + 8)) / 0x18;
                        int start = 0;
                        if (prev == -1) { path->Link(cur, cur + 1, kLinkW, colMid); cur++; }
                        else { path->Link(prev, cur, kLinkW, colMid); start = 1; }
                        for (int i = start; i < cnt; i++) {
                            float tt = n->t, w1 = n->w0, w2 = n->w1;
                            if (w2 < 0.0f) w2 = 1.0f;
                            float a0 = *(float*)(wA + i * 4);
                            float mixed = a0 + (*(float*)(wB + i * 4) - a0) * tt;
                            Vec3 t1, t2, t3, t4, t5;
                            Vec3 p = *Vec3Add(&t3, &base, Vec3Unary(&t2, Vec3SubScaled(&t1, &dir, &base, &mixed)));
                            Vec3 d0 = *Vec3Sub(&t4, &p, &base);
                            float f0 = 1.0f - Vec3Length2(&d0) / radius;
                            Vec3 d1v = *Vec3Sub(&t5, &p, &dir);
                            float f1 = 1.0f - Vec3Length2(&d1v) / radius;
                            float c0 = ((w1 - 0.0f) * f0 + 0.0f + (w2 - 0.0f) * f1 + 0.0f) * scale;
                            float wa = *(float*)(widA + i * 4);
                            float w = (wa + (*(float*)(widB + i * 4) - wa) * tt) * c0;
                            if (w < minWidth) w = minWidth;
                            Vec3 t6, t7, t8;
                            Vec3 pt = *Vec3Transform(&t8, Vec3Unary(&t7, Vec3Blend(&t6, (Vec3*)(i * 12 + posA), (Vec3*)(i * 12 + posB), tt, &c0, &n->axis)), 0);
                            uint32_t col;
                            if (i == 0) col = colA | 0x80000000;
                            else if (i == cnt - 1) col = colB | 0x80000000;
                            else { col = colMid; path->Link(cur, cur + 1, kLinkW, colMid); cur++; }
                            path->AddPoint(&pt, kOne_s0041_2900, w, col);
                        }
                    }
                }
            }
        } else {
            // chained branch: walk following nodes of type 3 that are children of this node
            Vec3 pA = base, pB = dir, pC = base, pD = dir;
            if (n->parent != -1 && (nodes[n->parent].flags & 4)) pC = nodes[n->parent].pos;
            int j = idx;
            for (;;) {
                j++;
                if (j >= count || *((char*)nodes + 0xb + j * 0x8c) != 3 || nodes[j].parent < idx) break;
                if (nodes[j].parent == idx) {
                    Vec3 t9; Vec3 v = { 0.0f, -nodes[j].radius, 0.0f };
                    pD = *Vec3Transform(&t9, &v, &nodes[j].axis);
                    Vec3Normalize(&pD, &nodes[j].pos);
                    break;
                }
            }
            float w1 = n->w0, w2 = n->w1;
            if (w2 < 0.0f) w2 = 1.0f;
            float a = w1 * 0.1f, b = w2 * 0.1f;
            if (a < minWidth) a = minWidth;
            if (b < minWidth) b = minWidth;
            float half = 0.5f; Vec3 t1, t2, t3;
            Vec3 mid = *Vec3Add(&t3, &base, Vec3Unary(&t2, Vec3SubScaled(&t1, &dir, &base, &half)));
            (void)mid;
            if (prev == -1) prev = path->AddPoint(&base, kOne_s0041_2900, a, colA | 0x80000000);
            bool degenerate = !(1.1754944e-38f <= (pA.x < 0 ? -pA.x : pA.x) || 1.1754944e-38f <= (pB.x < 0 ? -pB.x : pB.x));
            if (degenerate) { pC.x = 0.0f; pD.x = 0.0f; }
            int last = prev;
            for (float f = 1.0f; f < 15.0f; f += 1.0f) {
                float t = f / 15.0f;
                Vec3 t4; Vec3 p = *Vec3Curve(&t4, &pC, &pA, &pB, &pD, t);
                int cur = path->AddPoint(&p, kOne_s0041_2900, a + (b - a) * t, colMid);
                path->Link(last, cur, kLinkW, colMid);
                last = cur;
            }
            int fin = path->AddPoint(&dir, kOne_s0041_2900, b, colB | 0x80000000);
            path->Link(last, fin, kLinkW, colMid);
        }
        prev = (*(int*)((char*)path + 0xc) - *(int*)((char*)path + 8)) / 0x18 - 1;
    }
    return prev;
}
}  // namespace A

// @ 0x00413cc0
Vector3_s0041_3cc0* ComputeVector(Vector3_s0041_3cc0* ret, const void* a, const void* b, Vector3_s0041_3cc0 c)
{
    Vector3_s0041_3cc0 tmp;
    Vector3_s0041_3cc0 v = *CrossLike(&tmp, b, a);
    ScaleInPlace(&v, &c);
    Vector3_s0041_3cc0 tmp2;
    *ret = *Combine(&tmp2, a, &v);
    return ret;
}

// @ 0x00413d60
float MinComponent(Vector3_s0041_3cc0* v)
{
    return min_ref(min_ref((*v)[0], (*v)[1]), (*v)[2]);
}

// @ 0x00413de0
bool ClipPlayer::BuildBlend(Clip* src)
{
    if (mpHandle) {
        mpHandle->Cancel();
        mpHandle = 0;
        mpCurrent = 0;
    }
    int count;
    int i;
    float one;
    int prevB;
    int prevH;
    ClipEntry* e;
    float linkWeight;
    linkWeight = 0.3f;
    one = 1.0f;
    e = src->mpModel->mEntries.mpBegin;
    count = src->mpModel->mEntries.size();
    i = 0;
    while (i < count && !(e[i].mFlags & 1))
        i++;
    if (i == count)
        return false;
    mpMixer->Reset();
    prevB = -1;
    prevH = -1;
    for (i = 0; i < count && e[i].mType == 5; i++) {
        ClipEntry* p = &e[i];
        Vector3_s0041_3cc0 pos = SamplePosition(&p->mDir, &p->mPos[2], p->mTime);
        float scale = SampleScale(p->mTime);
        int h = mpMixer->AddKey(&pos, one, scale, p->mId);
        if (i > 0)
            mpMixer->Link(prevH, h, linkWeight, prevB | 0x80000000);
        prevH = h;
        prevB = p->mParent;
    }
    IntVector_s0041_3cc0 handles(count, -1);
    for (; i < count && e[i].mType == 3; i++) {
        ClipEntry* p = &e[i];
        if (p->mFlags & 1) {
            if (p->mLink == -1 || e[p->mLink].mType != 3) {
                prevB = p->mParent - 1;
                prevH = -1;
            } else {
                prevB = e[p->mLink].mParent;
                prevH = handles.mpBegin[p->mLink];
            }
            handles[i] = BuildChain(e, count, i, prevB, p->mParent, p->mId, prevH);
        }
    }
    src->mpNode->Finish(1);
    mpMixer->SetRoot(src->mpNode);
    mpMixer->Reset();
    bool result = true;
    return result;
}

// @ 0x004142e0
bool ClipPlayer::Advance(Clip* t, float time, bool flag)
{
    bool result = false;
    for (;;) {
        if (!(t->mpNode->Test(time) && mpSolver->Run(t->mpNode, t->mpSkin, time)))
            break;
        if (mpSolver->Apply(flag)) {
            result = true;
            break;
        }
        if (!(mpSolver->mField1C && time < 0.5f))
            break;
        time *= 1.2f;
    }
    t->mTime = time;
    mpSolver->Finish();
    return result;
}

// @ 0x004143e0
void ClipPlayer::Rewind(int unused)
{
    Advance(mpCurrent, mpCurrent->mTime, true);
}

// @ 0x00414420
bool ClipPlayer::Step(Clip* t, float time)
{
    bool ok = BuildBlend(t);
    if (!ok) {
        t->mpSkin->Reset();
        return true;
    }
    return Advance(t, time, false);
}

// @ 0x00414470
bool ClipPlayer::Start(Clip* clip, float time, LoadHandle_s0041_3cc0** out)
{
    BuildBlend(clip);
    intrusive_ptr_s0041_3cc0<LoadHandle_s0041_3cc0> handle;
    IFactory_s0041_3cc0::Get()->Create(&handle);
    mpHandle = handle;
    mpCurrent = clip;
    mpCurrent->mTime = time;
    handle.get()->Attach(this);
    handle.get()->SetFlags(0x80000000);
    *out = handle.detach();
    return true;
}

// @ 0x004145c0
bool PaletteEditor::SetItem(Item_s0041_45c0* n)
{
    if (m_item.get() && (m_item->f6c || m_item->f6b)) {
        if (m_cur.get() == m_item.get()) { m_dirty = true; Refresh(0); }
        m_item.reset();
    }
    if (!m_item.get()) {
        m_item = n;
        if (m_b2c4 || m_b259) {
            V3 vec = m_pos;
            ExtraInfo flags = m_pair;
            m_dirty = true;
            if (TestPlacement(&vec, flags.a)) {
                flags.flags |= 1;
                ApplyPlacement(&vec, &flags);
            } else m_dirty = false;
        }
        return true;
    }
    return false;
}

// @ 0x004147b0
bool PaletteEditor::AddEntry(DefRef* src, ExtraInfo* extra, IRefCounted_s0041_45c0* cb)
{
    ResourceKey_s0041_45c0 objKey = src->GetDef()->key;
    objKey.typeID = HashName(src->GetDef()->tail.nameHash);
    int editSize = 0x200;
    int seq = -1;
    bool enableAll = true;
    bool isDebug = false;
    ip<IPropList_s0041_45c0> pDesc;
    if (PropManager_s0041_45c0()->GetPropertyList(objKey.instanceID, objKey.groupID, pDesc.AsOutParamX())) {
        GetIntProp_s0041_45c0(pDesc.get(), 0x4c6ba29, editSize);
        GetIntProp_s0041_45c0(pDesc.get(), 0x52f7b17, seq);
        GetBoolProp_s0041_45c0(pDesc.get(), 0x521fc0e, enableAll);
        GetBoolProp_s0041_45c0(pDesc.get(), 0x680a2b1, isDebug);
    }
    int groupType = GroupBits_s0041_45c0(objKey.groupID).Type();
    bool ok = (groupType == 0x66 || groupType == 0x6b) ? 0 : 1;
    ip<Entry_s0041_45c0> self(new("Editor", 0, 0, 0, 0) Entry_s0041_45c0());
    self->owner = src;
    self->key = objKey;
    SetKeyType(&self->key, 0x29, 0);
    self->flags = editSize;
    self->priority = seq;
    self->b64 = isDebug;
    self->b65 = enableAll;
    self->b66 = ok;
    self->b67 = false;
    self->b68 = !(extra->flags & 2);
    self->b69 = true;
    self->b6a = false;
    if (groupType == 0x6b) {
        self->ids[0] = 0x8ec5176c;
    } else {
        DefTail* rank = &src->GetDef()->tail;
        for (int i = 0; i < 3; i++) {
            self->pos[i] = rank->pos[i];
            self->ids[i] = rank->ids[i];
            self->ids2[i] = rank->ids2[i];
        }
        ip<IPropList_s0041_45c0> otherList;
        if (PropManager_s0041_45c0()->GetPropertyList(ResolveName(rank->nameHash), g_015d13e8, otherList.AsOutParam())) {
            PropArray a2;
            if (GetArrayImpl(otherList.get(), 0x5e68c2e, &a2.count, &a2.data)) {
                for (int jj = 0; jj < 3 && jj < a2.count; jj++) {
                    if (self->ids[jj] == 0) self->ids[jj] = a2.data[jj];
                }
            }
        }
        if (objKey.typeID == 0x2b978c46 && groupType != 0x6b) self->ids[3] = 0xd723b947;
        if (objKey.typeID == 0x3d97a8e4) { self->ids[3] = 0; self->ids[2] = 0; self->ids[1] = 0; }
    }
    Slot_s0041_45c0 cmd(&self);
    cmd.key = objKey;
    cmd.extra = *extra;
    cmd.tail.cb = cb;
    m_container.Add(&cmd, 0);
    m_dirty = true;
    return true;
}

// @ 0x00414e10
int EditorObject::GetField78()
{ return Field78(); }

// @ 0x00414e30
bool BoundsLibrary::Query(unsigned int idLo, unsigned int idHi, float* weights, int nWeights, Vector3_s0041_4e30* mn, Vector3_s0041_4e30* mx)
{    struct FrameHole {
        static __forceinline void Reserve12() { uint32_t s[12]; }
        static __forceinline void Reserve10() { uint32_t s[10]; }
    };
    struct LocalIter : BoundsIter {
        __forceinline LocalIter(BoundsTable* tbl) {
            BoundsNode** tmp1 = tbl->buckets + tbl->bucketCount;
            BoundsNode* tmp2 = *tmp1;
            node = tmp2;
            bucket = tmp1;
        }
    };
    uint64_t key = idLo | ((uint64_t)idHi << 32);
    BoundsIter it;
    table.Find(&it, &key);
    FrameHole::Reserve12();
    if (it != LocalIter(&table)) {
        if (mn) {
            BoundsSampler sampler;
            sampler.Init(it.node->value, weights, nWeights, mn, mx);
            FrameHole::Reserve10();
        }
        if (!mn || (*mn)[0] < (*mx)[0])
            return true;
    }
    if (mn) {
        *mn = Vector3Init(-0.1f, -0.1f, -0.1f);
        *mx = Vector3Init(0.1f, 0.1f, 0.1f);
    }
    return false;
}

// @ 0x00415030
void BoundsSampler::Init(BoundsHeader* hdr, float* weights, int nWeights, Vector3_s0041_4e30* mn, Vector3_s0041_4e30* mx)
{
    int n;
    n = 0;
    while (n < 8 && hdr->dims[n] > 0)
        n++;
    total = 1;
    for (int i = 0; i < n; i++)
        total = hdr->dims[i] * total;
    if (n > 0) {
        data = hdr;
        levels = n;
        for (int j = 0; j < n; j++) {
            int stride = 1;
            for (int k = j + 1; k < n; k++)
                stride = hdr->dims[k] * stride;
            float w;
            if (j < nWeights)
                w = Clamp01(weights[j], 0.0f, 1.0f);
            else
                w = 0.0f;
            IntPair tmp;
            range[j] = *CellRange(&tmp, j, stride, w, &weight[j]);
        }
        Collect(0, 0, mn, mx);
    } else {
        *mn = hdr->minv;
        *mx = hdr->maxv;
    }
}

// @ 0x00415230
IntPair* BoundsSampler::CellRange(IntPair* out, int axis, int stride, float t, float* frac)
{
    int last;
    int idx;
    float scaled;
    int offset;
    last = data->dims[axis] - 1;
    if (last < 1) {
        IntPair r;
        r.second = 0;
        r.first = 0;
        out->first = r.first;
        out->second = r.second;
        return out;
    }
    scaled = (float)last * t;
    idx = (int)scaled;
    *frac = scaled - (float)idx;
    offset = idx * stride;
    if (*frac > 0.0f && idx < last) {
        int nx = offset + stride;
        out->first = offset;
        out->second = nx;
        return out;
    } else {
        out->first = offset;
        out->second = offset;
    }
    return out;
}

// @ 0x00415310
void BoundsSampler::Collect(unsigned int cell, int level, Vector3_s0041_4e30* mn, Vector3_s0041_4e30* mx)
{    if (cell >= total) {
        mn->x = -0.1f; mn->y = -0.1f; mn->z = -0.1f;
        mx->x = 0.1f; mx->y = 0.1f; mx->z = 0.1f;
        return;
    }
    if (level >= levels) {
        CellBounds(cell, *mn, *mx);
        return;
    }
    Collect(cell + range[level].first, level + 1, mn, mx);
    if (range[level].first != range[level].second) {
        Vector3_s0041_4e30 mn2, mx2;
        Collect(cell + range[level].second, level + 1, &mn2, &mx2);
        {
            Vector3_s0041_4e30 tmp1;
            *mn = *Lerp(&tmp1, *mn, mn2, weight[level]);
        }
        {
            Vector3_s0041_4e30 tmp2;
            *mx = *Lerp(&tmp2, *mx, mx2, weight[level]);
        }
        {
            uint32_t u1[7];   // dead locals of the original inlined helpers (frame size only)
            uint32_t u2[7];
            uint32_t u3[15];
        }
    }
}

// @ 0x004154b0
void BoundsSampler::CellBounds(unsigned int cell, Vector3_s0041_4e30& mn, Vector3_s0041_4e30& mx)
{
    uint8_t* c = data->cells[cell].b;
    mn[0] = data->minv[0] - data->cell * (float)(c[0] >> 4);
    mn[1] = data->minv[1] - data->cell * (float)(c[1] >> 4);
    mn[2] = data->minv[2] - data->cell * (float)(c[2] >> 4);
    mx[0] = data->cell * (float)(c[0] & 0xF) + data->maxv[0];
    mx[1] = data->cell * (float)(c[1] & 0xF) + data->maxv[1];
    mx[2] = data->cell * (float)(c[2] & 0xF) + data->maxv[2];
}

static inline void PropertyLookupFrame()
{
    uint32_t slots[28]; // Unread slots from the original inlined lookup layers.
}

// @ 0x00415660
PropertyList_s0041_4e30* PropertyListCache::Get(unsigned int instanceID, unsigned int groupID)
{
    uint64_t key = instanceID | ((uint64_t)groupID << 32);
    PropertyListPtr_s0041_4e30* slot = map.Slot(&key);
    PropertyLookupFrame();
    if (slot->get() == 0) {
        GetPropManager()->GetPropertyList(instanceID, groupID, slot->AsPointer());
    }
    return slot->get();
}

// @ 0x00415730
bool ConfigManager_s0041_4e30::FindModelKey(unsigned int instanceID, unsigned int groupID, ResourceKey_s0041_4e30* dst)
{
    ResourceKey_s0041_4e30 key;
    if (GetKeyValue(FindPropertyList(instanceID, groupID), 0xF9EFBB, &key)) {
        ConvertKeyType(&key, 0x61, 0);
        if (GetResourceManager_s0041_4e30()->ResourceExists(&key)) {
            *dst = key;
            return true;
        }
    }
    return false;
}

// @ 0x004157d0
bool Handler_s0041_57d0::HandleMessage(const MsgKey* msg, const MsgArgs* args)
{
    uint32_t key2   = msg->mKey2;
    uint32_t id71   = (key2 & 0xffff00ff) | (0x71 << 8);
    uint32_t id62   = (key2 & 0xffff00ff) | (0x62 << 8);
    uint32_t packed = 0;
    if (((key2 >> 16) & 0xff) == 0x62)
        packed = (id62 & 0xe0ffffff) | 0x01000000;

    GetManager_s0041_57d0();

    bool ok = true;
    if ((args->mFlags & 0x20) == 0 &&
        ((char(__thiscall*)(void*, uint32_t))(char(__cdecl*)())FUN_006a25a0)(g_AppProperties, 0x26cd3a5) != 0) {
        bool handled = ((char(__thiscall*)(void*, const MsgKey*, uint32_t))mpVtbl[0x1c / 4])(this, msg, 0) != 0;
        if (!handled)
            handled = ((char(__thiscall*)(void*, const MsgKey*, uint32_t))mpVtbl[0x38 / 4])(this, msg, args->mId) != 0;
        ok = !handled;
    }

    if (!ok) {
        Msg_s0041_57d0* m;
        NEW_HMSG_s0041_57d0(m, 0x695e243)
        m->Set(0, msg->mKey0);
        m->Set(1, msg->mKey2);
        m->Set(2, msg->mKey1);
        m->Set(3, args->mId);
        m->Set(4, 0);
        GetMsgMgr_s0041_57d0()->Post(0x695e243, m, 0, 0);
        return true;
    }

    TRef_s0041_57d0 a50, a4c, a54, a5c;
    a50.p = 0;
    a4c.p = 0;
    a54.p = 0;
    a5c.p = 0;
    Target_s0041_57d0* job = 0;

    if (FUN_004bafc0((void*)msg, a50.Out()) == 0) {
        Msg_s0041_57d0* m = new (kEditorAllocName) BMsg_s0041_57d0(0x695e243);
        m->Set(0, msg->mKey0);
        m->Set(1, msg->mKey2);
        m->Set(2, msg->mKey1);
        m->Set(3, args->mId);
        m->Set(4, 1);
        GetMsgMgr_s0041_57d0()->Post(0x695e243, m, 0, 0);
        RELEASE_REF(a5c);
        RELEASE_REF(a54);
        RELEASE_REF(a4c);
        RELEASE_REF(a50);
        return false;
    }

    FUN_00469920(msg->mKey0, id71, a4c.Out());

    if (FUN_00469920(msg->mKey0, id62, a54.Out()) != 0)
        FUN_00471830(a50.p, a54.p);

    if (packed != 0) {
        if (FUN_00469920(msg->mKey0, packed, a5c.Out()) != 0)
            a5c.p->F2c(a54.p);
    }

    job = 0;
    if (FUN_004186c0(a50.p, (void*)args, &job) == 0) {
        Msg_s0041_57d0* m = new (kEditorAllocName) BMsg_s0041_57d0(0x695e243);
        m->Set(0, msg->mKey0);
        m->Set(1, msg->mKey2);
        m->Set(2, msg->mKey1);
        m->Set(3, args->mId);
        m->Set(4, 1);
        GetMsgMgr_s0041_57d0()->Post(0x695e243, m, 0, 0);
        RELEASE_JOB(job);
        RELEASE_REF(a5c);
        RELEASE_REF(a54);
        RELEASE_REF(a4c);
        RELEASE_REF(a50);
        return false;
    }

    KeyedRecord_s0041_57d0 rec;
    ASSIGN_JOB(rec.mJob1C, job);
    rec.mField0C = args->mId;
    rec.mFlags10 = args->mFlags;
    rec.mValue12 = args->mValue;
    rec.mKey00 = msg->mKey0;
    rec.mKey04 = msg->mKey1;
    rec.mKey08 = msg->mKey2;
    ASSIGN_REF(rec.mSlots24[0], a4c.p);
    ASSIGN_REF(rec.mSlots24[1], a54.p);
    ASSIGN_REF(rec.mSlots24[2], a5c.p);
    if (args->mFlags & 1)
        ((char(__thiscall*)(void*, void*, uint32_t))(char(__cdecl*)())FUN_004204f0)(mRecordSet, &rec, args->mValue);
    else
        ((char(__thiscall*)(void*, void*, uint32_t))(char(__cdecl*)())FUN_004204d0)(mRecordSet, &rec, args->mValue);
    rec.Destroy();
    RELEASE_JOB(job);
    RELEASE_REF(a5c);
    RELEASE_REF(a54);
    RELEASE_REF(a4c);
    RELEASE_REF(a50);
    return true;
}

// @ 0x00416180
bool EditorPanel::HasHandler(ResourceKey_s0041_6180* k, int id)
{
    ResourceKey_s0041_6180 key = *k;
    if (BitsTag(key.group) == 0x62) {
        ResourceKey_SetFlags(&key, 0);
    }
    if (flagA || flagB) {
        if (((Entry_s0041_6180*)&activeKey)->KeyEquals(key) && activeId == id)
            return true;
    }
    {
    Iter it, end;
    entries.Begin(&it);
    entries.End(&end);
    for (; it != end; it.Next()) {
        if (it->KeyEquals(key) && it->id == id)
            return true;
    }
    }
    return false;
}

// @ 0x00416320
bool EditorPanel::HasId(int id)
{
    if ((flagA || flagB) && activeId == id)
        return true;
    Iter it, end;
    entries.Begin(&it);
    entries.End(&end);
    for (; it != end; it.Next()) {
        if (it->id == id)
            return true;
    }
    return false;
}

// @ 0x004163f0
bool EditorPanel::HasHandlerNormalized(ResourceKey_s0041_6180* k)
{
    ResourceKey_s0041_6180 key = *k;
    {
    Iter it, end;
    bool isSpecial = (key.type == 0x2b978c46 || key.type == 0x438f6347 || key.type == 0x3d97a8e4);
    if (isSpecial) {
        key.group = BitsClearFlags(key.group, 0);
    }
    if (flagA || flagB) {
        if (((Entry_s0041_6180*)&activeKey)->KeyEquals(key))
            return true;
    }
    entries.Begin(&it);
    entries.End(&end);
    for (; it != end; it.Next()) {
        if (it->KeyEquals(key))
            return true;
    }
    }
    return false;
}

// @ 0x004165a0
bool EditorPanel::Activate(ResourceKey_s0041_6180* k, int id)
{
    if (flagB || flagA) {
        Entry_s0041_6180* e = (Entry_s0041_6180*)&activeKey;
        if (e->KeyEquals(*k) && activeId == id) {
            if (flagB) {
                CommitAndReset(1);
                return true;
            }
            if (flagA && GetTarget()) {
                GetManager()->Method(GetTarget());
                CommitAndReset(1);
                return true;
            }
            return false;
        }
    }
    Iter it, end;
    entries.Begin(&it);
    entries.End(&end);
    while (it != end) {
        Entry_s0041_6180* e = it.operator->();
        if (e->KeyEquals(*k) && it->id == id) {
            EditorMessage* msg = new ("Editor", 0, 0, 0, 0) EditorMessage(0x695e243);
            msg->SetField(0, it->key.instance);
            msg->SetField(1, it->key.group);
            msg->SetField(2, it->key.type);
            msg->SetField(3, it->id);
            msg->SetField(4, 2);
            GetDispatcher()->Post(0x695e243, msg, 0, 0);
            it = entries.Erase(it);
            return true;
        } else {
            it.Next();
        }
    }
    return false;
}

// @ 0x00416990
bool EditorPanel_s0041_6990::ActivateById(int id)
{
    bool found = false;
    if ((flagB || flagA) && active.id == id) {
        found = OnActivate(&active, active.id);
    }
    Iter_s0041_6990 iter, end;
    entries.Begin(&iter);
    entries.End(&end);
    while (iter != end) {
        if (iter->id == id) {
            EditorMessage_s0041_6990* msg = new ("Editor", 0, 0, 0, 0) EditorMessage_s0041_6990(0x695e243);
            msg->SetField(0, iter->key.instance);
            msg->SetField(1, iter->key.group);
            msg->SetField(2, iter->key.type);
            msg->SetField(3, iter->id);
            msg->SetField(4, 2);
            GetDispatcher_s0041_6990()->Post(0x695e243, msg, 0, 0);
            iter = entries.ErasePV(iter);
            found = true;
        } else {
            iter.Next();
        }
    }
    return found;
}

// @ 0x00416c60
bool EditorPanel_s0041_6990::ActivateByKey(ResourceKey_s0041_6990* k)
{
    Iter_s0041_6990 iter, end;
    bool found = false;
    if (flagA || flagB) {
        if (active.KeyEquals(*k)) {
            found = OnActivate(&active, active.id);
        }
    }
    entries.Begin(&iter);
    entries.End(&end);
    while (iter != end) {
        if (iter->KeyEquals(*k)) {
            iter = entries.ErasePV(iter);
            found = true;
        } else {
            iter.Next();
        }
    }
    return found;
}

// @ 0x00416e30
void EditorPanel_s0041_6990::AdjustPressCount(bool release)
{
    if (!release) {
        pressCount++;
    } else {
        pressCount--;
        if (pressCount < 0)
            pressCount = 0;
    }
    noEntries = pressCount == 0;
}

// @ 0x00416eb0
int EditorPanel_s0041_6990::CountPending()
{
    return entries.Size() + ((flagA || flagB) ? 1 : 0);
}

// @ 0x00416f00
int EditorPanel_s0041_6990::CountWithId(int id)
{
    int count = 0;
    Iter_s0041_6990 begin, end;
    entries.Begin(&begin);
    entries.End(&end);
    for (; begin != end; begin.Next()) {
        if (begin->id == id)
            count++;
    }
    return count;
}

// @ 0x00416fb0
bool EditorPanel_s0041_6990::GetActiveKey(ResourceKey_s0041_6990* out)
{
    if (flagA || flagB) {
        if (out) {
            *out = active.key;
        }
        return true;
    }
    return false;
}

// @ 0x00417010
void EditorPanel_s0041_6990::CollectAll(EntrySink* out)
{
    if (flagA || flagB) {
        out->Add(&Entry_s0041_6990(active.key, active.val));
    }
    Iter_s0041_6990 it;
    entries.BeginC(&it);
    for (; it != entries.EndCV(); it.Next()) {
        out->Add(&Entry_s0041_6990(it->key, it->val));
    }
}

// 0x00417150 (byte-exact lifted version: match/slices/s00417150/s00417150.cpp)
float EditorPanel_s0041_6990::GetSlotValue(KeyedEvent* ev)
{
    ResourceKey_s0041_6990* key = &ev->key;
    int tag = KeyGroupTag(key->group);
    if (tag >= 0x61 && tag <= 0x66) {
        HIter found;
        slots[tag - 0x61].Find(&found, key);
        if (found != slots[tag - 0x61].End())
            return *(float*)((char*)found.node + 4);
    }
    return 0.0f;
}

// @ 0x00417210
void __cdecl ExportResources(KeyVec_s0041_7210* keys, const wchar_t* dir, const wchar_t* sub, Handler* h1, Handler* h2, bool checkout)
{
    WString_s0041_7210 unused;
    Manager_s0041_7210* mgr;
    WString_s0041_7210 path;
    wchar_t name[256];
    WString_s0041_7210 destName;
    const wchar_t* base;
    int n, i;
    Handler* h;
    mgr = GetManager_s0041_7210();
    base = GetBasePath();
    WString_Init(&destName);
    WString_Init(&path);
    swprintf_like(&path, L"%ls%ls/%ls/", base, dir, sub);
    CreateDirs(path.Data());
    WString_Init(&unused);
    i = 0;
    n = keys->last - keys->first;
    for (; i < n; ++i) {
        switch (keys->first[i].type) {
        case 0x3d97a8e4: case 0x2399be55: case 0x24682294: case 0x2b978c46:
        case 0x438f6347: case 0x476a98c7:
            continue;
        }
        h = LookupHandler(mgr->FindHandler(keys->At(i)));
        if (h != h1 && h != h2) continue;
        if (!h->GetName(keys->At(i), name)) continue;
        swprintf_like(&destName, L"%ls%ls", h->GetExt(name));
        swprintf_like(&path, L"%ls%ls/%ls/%ls", base, dir, sub, name);
        if (checkout) {
            WString_s0041_7210 q; WString_Init(&q);
            swprintf_like(&q, L"\"%ls\"", path.Data());
            int p;
            while ((p = ((WStringOps*)&q)->Find(0x40, 0)) != -1) {
                ((WStringOps*)&q)->Erase(p, 1);
                ((WStringOps*)&q)->Insert(p, L"%40");
            }
            RunProcess(L"p4.exe", L"edit", q.Data(), 0);
            WString_Free(&q);
        }
        if (FileExists(path.Data()))
            SetFileAttr(path.Data(), 2, 1);
        CopyFileTo(destName.Data(), path.Data(), 1);
        if (checkout) {
            WString_s0041_7210 q2; WString_Init(&q2);
            swprintf_like(&q2, L"\"%ls\"", path.Data());
            RunProcess(L"p4.exe", L"add", L"-f", q2.Data(), 0);
            WString_Free(&q2);
        }
        FileExists(path.Data());
    }
    WString_Free(&unused);
    WString_Free(&path);
    WString_Free(&destName);
}

// @ 0x00417600
void Panel::Apply(ResourceKey_s0041_7600* key, bool flag, void* extra)
{
    const wchar_t* name = 0;
    switch (KeyGroupTag_s0041_7600(key->GetGroup())) {
    case 0x61: name = L"Cell"; break;
    case 0x62: name = L"Creature"; break;
    case 0x63: name = L"Building"; break;
    case 0x64: name = L"Vehicle"; break;
    case 0x65: name = L"UFO"; break;
    case 0x66: name = L"Flora"; break;
    case 0x6b: name = L"Palette"; break;
    }
    if (!name) return;

    intrusive_ptr_s0041_7600<IResource> res;
    if (GetResourceManager_s0041_7600()->Load(key->instance, key->group, res.AsOutParam())) {
        res->SetProperty(0x66fadbd, Variant(true));
        MarkUsed(res.get(), 1);
        if (KeyGroupTag_s0041_7600(key->GetGroup()) == 0x62 && KeyFlags_s0041_7600(key->GetGroup()) == 0) {
            IResourceManager_s0041_7600* mgr = GetResourceManager_s0041_7600();
            res.Reset();
            if (mgr->Load(key->instance, KeyWithFlags(key->group, 1), (IResource**)&res)) {
                res->SetProperty(0x66fadbd, Variant(true));
                MarkUsed(res.get(), 1);
            }
        }
        if (res.get()) res = 0;
    }

    SyncState();
    IWindow* winA = FindWindow(LookupName(0x11ac1ac));
    IWindow* winB = FindWindow(LookupName(0x11ac19c));
    ResourceKey_s0041_7600 key2 = *key;
    key2.type = 0x1a99b06b;
    IEditorServices* services = GetServices();
    intrusive_ptr_s0041_7600<IRefCounted> listener;
    listener.Reset();
    if (services->Lookup(key, &listener.mpObject, 0, 0, 0, 0)) {
        WString path;
        int idx;
        WString ext;
        services->GetPath(key, &path);
        const wchar_t* e1 = L"_@";
        while (*e1) ++e1;
        idx = path.rfind(L"_@", -1, (int)(e1 - L"_@"));
        if (idx == -1) {
            const wchar_t* e2 = L"_0x";
            while (*e2) ++e2;
            idx = path.rfind(L"_0x", -1, (int)(e2 - L"_0x"));
        }
        if (idx == -1) idx = path.rfind(L'.', -1);
        path.erase(idx, -1);
        BuildKey(&key2, &ext, path.mpBegin);
        services->SetExt(&key2, ext.mpBegin);
        services->Register(listener.Ptr(), 0, winB, 0, &key2);
    }
    if ((winA && winA->Contains(&key2, 0, 1, 6, 1, 0)) || (winB && winB->Contains(&key2, 0, 1, 6, 1, 0))) {
        Query_s0041_7600 q;
        q.instance = key->instance;
        q.group = key->group;
        q.b = 0xc0ff0000;
        services->Collect(&q.list, &q, 0);
        Process(&q.list, extra, name, winA, winB, flag);
    }
}

// @ 0x00417cf0
char* EditorBlockData_s0041_7600::GetSlotArea()
{
    return (char*)this + 0x1100;
}

// @ 0x00417d10
EditorBlockData_s0041_7600* CreateEditorBlockData()
{
    return new("Editor", 0, 0, 0, 0) EditorBlockData_s0041_7600();
}

// @ 0x00417d60
ToolState::ToolState()
: mCountA(0), mCapacity(0x10), mFlagA(0), mFlagB(0), mMode(0)
{
}

// 0x00417fe0 (byte-exact lifted version: match/slices/s00417fe0/s00417fe0.cpp)
ToolState::~ToolState()
{
}

// @ 0x00418120
SubState::SubState()
: mFlag((PhantomTemps(), 0)), mScale(kZero), mCount(0), mValueA(kZero), mValueB(kZero),
      mFieldA(0), mFieldB(0), mFieldC(0), mPadCC8(0xffffffff)
{
}

// 0x00418240 (byte-exact lifted version: match/slices/s00418240/s00418240.cpp)
SubState::~SubState()
{
}

// @ 0x00418440
bool CheckMatchingProps(PropList_s0041_7d60* list)
{
    uint32_t* pValue = FindProp(list, 1, -1, 0, 14);
    int firstIndex = FindPropIndex(list, 9, -1, 0, 14);
    if (firstIndex < 0)
        return false;
    PropEntry* firstProp = &list->mpEntries[firstIndex];
    uint32_t firstKey = *pValue;
    uint32_t propertyValue = firstProp->mValue;
    if (firstKey != propertyValue)
        return false;
    int indexB = FindPropIndex(list, 10, -1, 0, 14);
    if (firstIndex < 0)
        return true;
    PropEntry* entryB = &list->mpEntries[indexB];
    uint32_t secondKey = *pValue;
    uint32_t valueB = entryB->mValue;
    if (secondKey != valueB)
        return false;
    return true;
}

// @ 0x00418500
void Loader::LoadAll(int a, int b)
{
    intrusive_ptr_s0041_7d60<RefCounted_s0041_7d60> obj;
    Manager1* mgr = GetManager1();
    obj.Reset();
    if (mgr->Load(a, b, &obj.mpObject)) {
        {
            intrusive_ptr_s0041_7d60<RefCounted_s0041_7d60> ref(obj.get());
            mRefs.push_back(ref);
        }
        for (int i = 0; i < 4; ++i) {
            PropKey key;
            key.a = 0; key.b = 0; key.c = 0;
            if (GetPropKey(obj.get(), i + 0xf9efbb, &key)) {
                intrusive_ptr_s0041_7d60<RefCounted_s0041_7d60> found;
                Manager2* mgr2 = GetManager2();
                found.Reset();
                if (mgr2->Find(&key, &found.mpObject)) {
                    intrusive_ptr_s0041_7d60<RefCounted_s0041_7d60> ref2(found.get());
                    mRefs.push_back(ref2);
                }
            }
        }
    }
}

// @ 0x004186c0
EditorResource* CreateEditorResource(EditorSource* pSource, uint32_t* pKey, LoadHandle_s0041_86c0** pOutHandle)
{
    HandlePtr hLoad;
    if (!((LoadManager_s0041_86c0*)GetLoadManager_s0041_86c0())->OpenHandle(hLoad.Out()))
        return 0;
    DeadPad5();
    ResPtr pRes(new ("Editor", 0, 0, 0, 0) EditorResource);
    pRes->mpOwner = pSource;
    pRes->mVec = *(Vec3Zero*)&pSource->f08;
    pRes->mVec.b = ConvertValue(pSource->f18);
    pRes->mKey = *(KeyPair_s0041_86c0*)pKey;
    hLoad->SetState(1);
    hLoad->Attach(pRes.get());
    hLoad->SetTarget(pRes.get());
    *pOutHandle = hLoad.Detach();
    return pRes;
}

// @ 0x00418870
EditorResource::EditorResource()
{}

// @ 0x00418960
// EditorResource scalar deleting destructor (implicit): the forcing function below makes the compiler emit it out of line
#pragma auto_inline(off)
void rwForceEmit_EditorResource_sdtor(EditorResource* p)
{
    delete p;
}
#pragma auto_inline(on)

// @ 0x00418990
// EditorResource destructor (implicit): the forcing function below makes the compiler emit it out of line
#pragma auto_inline(off)
void rwForceEmit_EditorResource_dtor(EditorResource* p)
{
    p->~EditorResource();
}
#pragma auto_inline(on)

// @ 0x00418a10
SubObject::~SubObject()
{ uint32_t pre[6]; }

// @ 0x00418ae0
bool EditorResource::Setup(LoadHandle_s0041_86c0* pParent)
{
    mpThreaded = new ("Editor", 0, 0, 0, 0) ThreadedObject_s0041_86c0(mpOwner.get());
    mpThreaded.get()->mpItemA = new ("Editor", 0, 0, 0, 0) ItemA;
    mpThreaded.get()->mpItemB = new ("Editor", 0, 0, 0, 0) ItemB(kDefaultItemScale);
    mTail.Reserve(mpOwner.get()->mItems.size());
    float scale = kDefaultScale;
    int idx = LookupIndex(mpOwner.get()->f18);
    if (idx != -1) {
        const uint32_t kPropId = 0x711306ce;
        PropertyListPtr_s0041_86c0 pList;
        if (PropManager_s0041_86c0::Get()->GetPropertyList(idx, g_PropListGroup, pList.Out())) {
            PropertyList_s0041_86c0* pl = pList.get();
            PropertyListValue* pProp;
            if (pl && pl->GetProperty(0x711306ce, &pProp) && pProp->type == 0xd)
                scale = *pProp->GetFloat();
        }
    }
    ConfigRoot* pCfg = GetConfigRoot();
    LoadManager_s0041_86c0* pMgr = (LoadManager_s0041_86c0*)GetLoadManager_s0041_86c0();
    pMgr->Lock();
    HandlePtr h1;
    pCfg->Begin(mpThreaded.get(), scale, h1.Out());
    HandlePtr h2;
    ((LoadManager_s0041_86c0*)GetLoadManager_s0041_86c0())->OpenHandle(h2.Out());
    h2->SetState(0x80000000);
    h2->OnBegin(this);
    h2->Add(h1.get());
    HandlePtr h3;
    ((LoadManager_s0041_86c0*)GetLoadManager_s0041_86c0())->OpenHandle(h3.AsPointer());
    h3->SetState(1);
    h3->OnEnd(this);
    pParent->Add(h2.mpObject);
    pParent->Add(h3.mpObject);
    h1->Finish();
    h2->Finish();
    h3->Finish();
    pMgr->Unlock();
    return pParent->Process(this);
}

// @ 0x00418f90
void EditorResource::NotifyA(LoadHandle_s0041_86c0* pParent)
{
    mpThreaded.get()->Method1();
    mpThreaded.get()->Method2();
    pParent->ProcessB(this);
}

// @ 0x00418fd0
bool EditorResource::NotifyB(LoadHandle_s0041_86c0* pParent)
{
    mpThreaded.get()->Method3();
    return true;
}

// @ 0x00419000
char LoadTask::Run(Finisher* fin)
{
    Engine* eng = GetEngine()->Module();
    ModelData* md = owner->data;
    int count = md->items.size();
    TimeBudget budget;
    budget.Init(4, 0);
    budget.Arm(1, 1);
    SceneObj*** objsP = &objs;
    for (int i = (int)(objsP[1] - objsP[0]); i < count; ++i) {
        int64_t now;
        QueryPerformanceCounter(&now);
        if (budget.deadline - now < 0)
            return fin->Done(this);
        PollLoader(&objs);
        char* it = (char*)md->items.begin + i * 0x8c;
        if (*(uint16_t*)(it + 8) & 1) continue;
        SceneObj* o = eng->Lookup(*(uint32_t*)(it + 0x88), *(uint32_t*)(it + 0x84), 6);
        if (!o) o = eng->Lookup(0x4f5f8ce, g_DefaultKey, 6);
        if (!o) continue;
        SceneObj*& slot = objs[i];
        if (o != slot) {
            SceneObj* old = slot;
            if (o) o->refs++;
            slot = o;
            if (old) ReleaseObj(old);
        }
        o->f18 = *(uint32_t*)(it + 0x2c);
        o->refCount++;
        for (int k = 0; k < 9; ++k) o->f1c[k] = ((uint32_t*)(it + 0x30))[k];
        o->flags |= 2; o->refCount++;
        o->f0c[0] = *(uint32_t*)(it + 0x54); o->f0c[1] = *(uint32_t*)(it + 0x58); o->f0c[2] = *(uint32_t*)(it + 0x5c);
        o->flags |= 4; o->refCount++;
        if (!(o->state & 0x4000)) eng->Prepare(o);
        Transform_s0041_9000 xf[0x20];
        for (int k = 0; k < 0x20; ++k) xf[k].Construct();
        int n = eng->Enumerate(o, xf, 0x20);
        int lim = it[0x11];
        if (n < lim) lim = n;
        for (int j = 0; j < lim; ++j) {
            float lo = 0.0f, hi = 1.0f;
            if (eng->Query(o, ((int*)&xf[j])[0], &lo, &hi, 0)) {
                float v = lo + (hi - lo) * owner->data->weights[*(uint16_t*)(it + 0xe) + j];
                eng->SetA(o, ((int*)&xf[j])[0], 0, 3, 0);
                eng->SetB(o, ((int*)&xf[j])[0], v, 0);
                eng->SetC(o, ((int*)&xf[j])[0], 1.0f, 0);
            }
        }
    }
    return 1;
}

// 0x00419690 (byte-exact lifted version: match/slices/s00419690/s00419690.cpp)
void __thiscall Task::Prepare(Request* req)
{
    f2c = 0;
    Owner_s0041_9000* o = owner;
    SlotA* s = &a;
    ModelData* md = o->GetData();
    ItemVec* v = &md->items;
    int count = v->size();
    s->Reserve(count);
    b.Assign(&o->f90);
    c.Reserve(count);
    c2.Reserve(count);
    a2.Reserve(count);
    d.Reserve(count);
    e.Reserve(count);
    req->f1c = 0;
    req->Dispatch(this);
}

// ---- UpdateModels support stubs (slice s00419780)
struct IRefObject_s0041_9780 {
    virtual void AddRef();
    virtual void Release();
};
struct DefaultRefCounted_s0041_9780 { void Release(); };   // @ 0x00453540
struct TimeBudget_s0041_9780 {
    uint32_t pad[6];
    int64_t deadline;
    TimeBudget_s0041_9780(int a, int b);            // @ 0x0093A560
    void Start(int a, int b);            // @ 0x0093A480
    bool Expired() {
        int64_t now;
        QueryPerformanceCounter(&now);
        int64_t t = now;
        return deadline - t < 0;
    }
};
struct BehaviorRef_s0041_9780  { IRefObject_s0041_9780* p;      void* Get(); void* GetOther(); };  // 0x0041D870
struct CounterRef_s0041_9780   { DefaultRefCounted_s0041_9780* p; void* Get(); };                  // 0x0041D900
int  GetIntProperty(PropertyList* p, uint32_t key, int* count, int** values);      // 0x006A0840 cdecl
int  GetFloatProperty(PropertyList* p, uint32_t key, int* count, float** values);  // 0x006A08B0 cdecl
int  Evaluate5(void* obj, int mode);          // 0x0071DD80 cdecl
bool IsValidResource(void* obj);              // 0x00418440 cdecl
void BindResource(IRefObject_s0041_9780* a, void* b);    // 0x006C1AE0 cdecl
template<class T> inline T ClampF_s0041_9780(T v, T lo, T hi) {
    T r = lo;
    if (lo <= v) r = v;
    if (hi <= r) r = hi;
    return r;
}
inline float Lerp_s0041_9780(float a, float b, float t) { return (b - a) * t + a; }

// @ 0x00419780
bool Updater::UpdateModels(RequestState* st)
{
    uint32_t pendingTemp = 0;
    int limit = 0x80;
    Scene* sc = scene;
    ArrayBlock* arr = arrays();
    ModelData_s0041_9780* model = sc->model;
    ModelRecord* recs = model->records.begin;
    int count = model->records.size();
    Entity** table = &entities[0];

    unsigned char tag;
    ResultList list(&tag);
    TimeBudget_s0041_9780 budget(4, 0);
    budget.Start(1, 1);

    for (int i = st->resumeIndex; i < count; ++i) {
        if (budget.Expired()) {
            st->resumeIndex = i;
            bool r = st->Abort(this);
            list.Release2(list.items, list.count);
            list.Free();
            return r;
        }
        ModelRecord* rec = &recs[i];
        if (table[i] != 0 && !(rec->flags & 1)) {
            ModelBehavior* beh = table[i]->behavior;
            if (rec->hasAnimation && !(rec->flags & 8)) {
                list.Assign(list.items, list.count);
                IRefObject_s0041_9780* animObj = 0;
                DefaultRefCounted_s0041_9780* counter = 0;
                void* cnt = ((CounterRef_s0041_9780*)&counter)->Get();
                void* anim = ((BehaviorRef_s0041_9780*)&animObj)->Get();
                Transform_s0041_9780 xf;
                if (!beh->Evaluate(table[i], &list, (int)anim, (int)cnt, &xf)) {
                    list.Assign(list.items, list.count);
                }
                if (!list.IsEmpty() && IsValidResource(list.begin()->p)) {
                    this->budget += Evaluate5(list.begin()->p, 5);
                    if (this->budget <= limit) {
                        IRefObject_s0041_9780* hold = animObj;
                        if (hold) hold->AddRef();
                        BindResource(hold, ((BehaviorRef_s0041_9780*)&animObj)->GetOther());
                        arr->weights[i].Add((void*)beh->GetBaseWeight(table[i]));
                        arr->modifiers[i].Add(&arr->weights[i]);
                        arr->modifiers[i].AccumulateScaled(&table[i]->transformSlot);
                        arr->intSlots[i].Set(list.begin()->p);
                        arr->objSlots[i].Set(animObj);
                        arr->targets[i] = counter;
                        if (hold) hold->Release();
                    }
                }
                if (counter) counter->Release();
                if (animObj) animObj->Release();
            }

            int*   ids = 0;     int nIds = 0;
            float* weights = 0; int nWeights = 0;
            float* targets = 0; int nTargets = 0;
            GetIntProperty(table[i]->props, 0x59348b4, &nIds, &ids);
            GetFloatProperty(table[i]->props, 0x59348b5, &nWeights, &weights);
            GetFloatProperty(table[i]->props, 0x6861c1e, &nTargets, &targets);

            for (int j = 0; j < nIds && j < nWeights && j < nTargets; ++j) {
                float lo = 0.0f, hi = 1.0f;
                if (beh->GetRange(table[i], ids[j], &lo, &hi, 0)) {
                    beh->Prepare(table[i], ids[j], 3, 0.0f, 0);
                    float t = ClampF_s0041_9780(weights[j], 0.0f, 1.0f);
                    beh->SetValue(table[i], ids[j], Lerp_s0041_9780(lo, hi, t), 0);
                    beh->SetExtra(table[i], ids[j], targets[j], 0);
                }
            }

            list.Assign(list.items, list.count);
            beh->QueryResults(table[i], &list);
            ObjectRef* src;
            ObjectRef  empty = { 0 };
            if (list.IsEmpty()) {
                pendingTemp |= 1;
                src = &empty;
            } else {
                src = list.begin();
            }
            arr->refs[i] = *src;
            if (pendingTemp & 1) {
                pendingTemp &= ~1u;
                if (empty.p) empty.p->Release();
            }
        }
    }
    bool r = st->Finish(this);
    list.Destroy();
    return r;
}

// @ 0x00419ff0
void Updater::Dispatch(void* cb)
{
    uint32_t a; uint32_t y; Scene* s2; uint32_t b; uint32_t x; Scene* s1;   // order drives /Od slots
    a = flags18;
    a = SetByte1(a, 0x71);
    x = a;
    b = flags18;
    b = SetByte1(b, 0x62);
    y = b;
    if (flags20 & 0x10)
        x = 0;
    s1 = scene;
    s1->registry.Register(arrays());
    s2 = scene;
    SubmitScene(s2, (char*)this + 0x10, arrays(), x, y, cb);
    ((RequestState*)cb)->Queue(this);
}

// @ 0x0041a0c0
bool Part_s0041_a0c0::Bake()
{
    PropList_s0041_a0c0* A_s0041_a0c0; PropList_s0041_a0c0* B; PropList_s0041_a0c0* C;
    EditorBake* ed;
    ResKey_s0041_a0c0 k71 = key.WithType(0x71);
    ResKey_s0041_a0c0 k62 = key.WithType(0x62);
    ResKey_s0041_a0c0 k3 = k62.WithC(1);
    if (!(flags & 0x10)) {
        A_s0041_a0c0 = 0; B = 0; C = 0;
        GetResMgr_s0041_a0c0()->GetResource(id, *(uint32_t*)&k71, OutPtr((void**)&A_s0041_a0c0));
        GetResMgr_s0041_a0c0()->GetResource(id, *(uint32_t*)&k62, OutPtr((void**)&B));
        GetResMgr_s0041_a0c0()->GetResource(id, *(uint32_t*)&k3, OutPtr((void**)&C));
        if (B && A_s0041_a0c0) {
            if (IsUserCreature()) {
                PropList_s0041_a0c0* X = 0; PropList_s0041_a0c0* Y = 0;
                Value v = {0, 0, 0};
                if (PropGet(B, 0xf9efbb, &v)) {
                    if (GetLoader()->Load(&v, OutPtr((void**)&X), 0, 0, 0, 0)) {
                        if (PropGet(A_s0041_a0c0, 0xf9efbb, &v)) {
                            if (GetLoader()->Load(&v, OutPtr((void**)&Y), 0, 0, 0, 0)) {
                                char* r1 = (char*)Deref((void**)&X);
                                char* r2 = (char*)Deref((void**)&Y);
                                if (r1 && r2)
                                    CopyIt(r2 + 0x13c, *(void**)(r1 + 0x13c));
                            }
                        }
                    }
                }
                if (Y) Y->Release();
                if (X) X->Release();
            }
            for (int i = 0; i < 4; i++) {
                if (A_s0041_a0c0->HasProp(i + 0xf9efbb))
                    B->SetProp(i + 0xf9efbb, A_s0041_a0c0->GetProp(i + 0xf9efbb));
            }
            BehaviorMessage m1;
            MsgInit(&m1, 0xf62def);
            m1.vtbl = vtMsg;
            m1.field38 = 0;
            m1.Arg(0).v = 0xb1b104;
            m1.Arg(1).v = *(uint32_t*)&k62;
            m1.Arg(2).v = id;
            GetMsgs()->Post(0xf62def, &m1, 0);
            if (C) {
                Value arr[4];
                for (int j = 0; j < 4; j++) { arr[j].a = 0; arr[j].b = 0; arr[j].c = 0; }
                char found[4];
                for (int j = 0; j < 4; j++)
                    found[j] = PropGet(C, j + 0xf9efbb, &arr[j]);
                C->CopyFrom(B);
                for (int j = 0; j < 4; j++) {
                    if (A_s0041_a0c0->HasProp(j + 0xf9efbb)) {
                        C->SetProp(j + 0xf9efbb, A_s0041_a0c0->GetProp(j + 0xf9efbb));
                    } else if (found[j]) {
                        Variant_s0041_a0c0 t;
                        t.flags = 0; t.type = 0; t.type = 0x20; t.flags = 2;
                        ValueCopy(&t, &arr[j]);
                        C->SetProp(j + 0xf9efbb, &t);
                        if (t.flags & 4) ValueFree(&t, 0);
                    }
                }
                BehaviorMessage m2;
                BehInit(&m2);
                m2.msgId = 0xf62def;
                m2.vtbl = vtBehavior; m2.vtbl = vtMsg;
                m2.field38 = 0;
                m2.Arg(0).v = 0xb1b104;
                m2.Arg(1).v = *(uint32_t*)&k3;
                m2.Arg(2).v = id;
                GetMsgs()->Post(0xf62def, &m2, 0);
                MsgFree(&m2);
            }
            MsgFree(&m1);
        }
        if (C) C->Release();
        if (B) B->Release();
        if (A_s0041_a0c0) A_s0041_a0c0->Release();
    }
    if (IsBusy((char*)(*(char**)((char*)owner + 8)) + 0x98))
        return true;
    void* mem = Alloc(0xc4, "Editor", 0, 0, 0, 0);
    ed = mem ? new (mem) EditorBake() : 0;
    if (ed) ed->AddRef();
    Register((AbilityIface*)ed, id, *(uint32_t*)&k62);
    Register((AbilityIface*)ed, id, *(uint32_t*)&k3);
    Fun4147b0(Fun401010(owner, (char*)this + 0x1c, ed));
    if (ed) ed->Release();
    return true;
}

// @ 0x0041a980
D::D()
{ ReserveFrame<1>(); MemberInit(member); }

// @ 0x0041a9f0
void* D::Destroy(unsigned flags)
{
    uint32_t t[5]; (void)t;
    MemberDtor(member);
    *(void***)((char*)this + 4) = vtAbility;
    *(void***)this = vtEditorResource;
    if (flags & 1) Dealloc(this);
    return this;
}

// @ 0x0041aa40
bool CollectAndDestroy(unsigned int a, unsigned int b)
{
    Elem24VectorWithStorage v;
    return v.Collect(a, b);
}

// Byte buffer for 0x0041aaa0: the slice (which declares no operator new[]) lowers new[]/delete[]
// to the scalar ??2/??3 calls; the module's operator new[] overloads would pick ??_U/??_V.
struct RawByte_s0041_aaa0 {
    unsigned char b;
    static void* operator new[](size_t n) { return ::operator new(n); }
    static void operator delete[](void* p) { ::operator delete(p); }
};

// @ 0x0041aaa0
bool ParamSweep::Build(void* object, IWriter* out)
{
    obj = object;
    ctl = *(IController**)object;

    Transform_s0041_aaa0 xforms[32];
    for (int i = 0; i < 32; i++) Transform_Ctor(&xforms[i]);

    int n = ctl->EnumParams(obj, xforms, 32);
    float minV[8], maxV[8];
    float hdr[9];
    hdr[0] = hdr[1] = hdr[2] = hdr[3] = hdr[4] = hdr[5] = hdr[6] = 0.0f;
    hdr[7] = 0.0f; hdr[8] = 0.0f;

    if (n != 0) {
        int total = 1;
        for (int i = 0; i < n; i++) {
            handles[i] = ((int*)&xforms[i])[0];
            ctl->GetParamRange(obj, handles[i], &minV[i], &maxV[i], 0);
            ctl->SetParam(obj, handles[i], minV[i], 0);
            counts[i] = 4;
            total <<= 2;
        }
        for (int i = n; i < 8; i++) { handles[i] = 0; counts[i] = 0; }
        numParams = n;

        int idx[8] = {0, 0, 0, 0, 0, 0, 0, 0};
        for (;;) {
            BoundsReset();
            void* comps[3] = {0, 0, 0};
            ctl->GetComponents(obj, comps);
            int cnt = (int)(((char*)comps[1] - (char*)comps[0]) >> 2);
            for (int i = 0; i < cnt; i++) {
                int e = FindComponentIndex(((unsigned*)comps[0])[i], 1, -1, 3, 0xe);
                if (e >= 0) AccumulateComponent(e);
            }
            int p = numParams - 1;
            while (++idx[p] >= counts[p]) {
                idx[p] = 0;
                ctl->SetParam(obj, handles[p], minV[p], 0);
                if (--p < 0) {
                    // all samples gathered
                    Vec3_s0041_aaa0 lo = begin->lo, hi = begin->hi;
                    Vec3_s0041_aaa0 lo2 = begin->lo, hi2 = begin->hi;
                    for (int k = 1; k < total; k++) {
                        Vec3_s0041_aaa0 t;
                        hi = *Vec3Min(&t, &hi, &begin[k].hi);
                        hi2 = *Vec3Max(&t, &hi2, &begin[k].hi);
                        lo = *Vec3Max(&t, &lo, &begin[k].lo);
                        lo2 = *Vec3Min(&t, &lo2, &begin[k].lo);
                    }
                    Vec3_s0041_aaa0 t1, t2;
                    float l1 = Vec3Length(Vec3Sub_s0041_aaa0(&t1, &lo, &lo2));
                    float l2 = Vec3Length(Vec3Sub_s0041_aaa0(&t2, &hi2, &hi));
                    float step = (l1 <= l2 ? l2 : l1) / 15.0f;
                    hdr[0] = lo.x; hdr[1] = lo.y; hdr[2] = lo.z;
                    hdr[3] = hi.x; hdr[4] = hi.y; hdr[5] = hi.z;
                    hdr[6] = step;
                    unsigned char* pk = (unsigned char*)&hdr[7];
                    for (int k = 0; k < 8; k++) pk[k] = (unsigned char)counts[k];
                    out->Write(hdr, 0x24);

                    unsigned char* buf = (unsigned char*)new RawByte_s0041_aaa0[total * 3];
                    unsigned char* w = buf;
                    for (int k = 0; k < total; k++) {
                        Vec3_s0041_aaa0 a, b, ta, tb;
                        a = *Vec3Sub_s0041_aaa0(&ta, &lo, (Vec3_s0041_aaa0*)&begin[k]);
                        b = *Vec3Sub_s0041_aaa0(&tb, (Vec3_s0041_aaa0*)&begin[k].hi, &hi2);
                        w[0] = (unsigned char)((QuantNibble(a.x, step) << 4) | QuantNibble(b.x, step));
                        w[1] = (unsigned char)((QuantNibble(a.y, step) << 4) | QuantNibble(b.y, step));
                        w[2] = (unsigned char)((QuantNibble(a.z, step) << 4) | QuantNibble(b.z, step));
                        w += 3;
                    }
                    out->Write(buf, total * 3);
                    delete[] (RawByte_s0041_aaa0*)buf;
                    Cleanup1();
                    return true;
                }
            }
            float lo = minV[p];
            float v = lo + ((float)idx[p] / (float)(counts[p] - 1)) * (maxV[p] - lo);
            ctl->SetParam(obj, handles[p], v, 0);
        }
    }

    // no parameters: single sample
    BoundsReset();
    void* comps[3] = {0, 0, 0};
    ctl->GetComponents(obj, comps);
    int cnt = (int)(((char*)comps[1] - (char*)comps[0]) >> 2);
    for (int i = 0; i < cnt; i++) {
        int e = FindComponentIndex(((unsigned*)comps[0])[i], 1, -1, 3, 0xe);
        if (e >= 0) AccumulateComponent(e);
    }
    Cleanup1();
    return false;
}

// @ 0x0041bd50
void BoundingBox_s0041_bd50::Extend(const Vector3_s0041_bd50& p)
{
    if (IsEmpty()) {
        // empty box: seed with the point
        lo = p;
        hi = p;
        return;
    }
    if (lo[0] > p[0]) lo[0] = p[0];
    else if (hi[0] < p[0]) hi[0] = p[0];
    if (lo[1] > p[1]) lo[1] = p[1];
    else if (hi[1] < p[1]) hi[1] = p[1];
    if (lo[2] > p[2]) lo[2] = p[2];
    else if (hi[2] < p[2]) hi[2] = p[2];
}

// @ 0x0041bf30
float MaxComponent(const Vector3_s0041_bd50* v)
{
    return Max(Max((*v)[0], (*v)[1]), (*v)[2]);
}

// @ 0x0041bfb0
Vector3_s0041_bd50 MaxVec(const Vector3_s0041_bd50& a, const Vector3_s0041_bd50& b)
{
    return Vector3_s0041_bd50(Max(a[0], b[0]), Max(a[1], b[1]), Max(a[2], b[2]));
}

// @ 0x0041c0c0
Vector3_s0041_bd50 MinVec(const Vector3_s0041_bd50& a, const Vector3_s0041_bd50& b)
{
    return Vector3_s0041_bd50(Min(a[0], b[0]), Min(a[1], b[1]), Min(a[2], b[2]));
}

// @ 0x0041c1d0
void DumpBlockDescriptions(int group, int instance)
{
    uint8_t tag;
    KeySet seen(&tag);
    bool haveList = group != 0;
    if (haveList) {
        PropListPtr list;
        list.mp = 0;
        PropertyManager()->GetPropertyList(instance, group, list.AsPPVoidParam());
        if (list.mp) {
            int count;
            ResKey3* arr;
            GetArrayProperty(list.mp, 0x53878d0, &count, &arr);
            for (int i = 0; i < count; ++i) {
                arr[i].mGroup = 0;
                ResKey3* key = &arr[i];
                uint8_t dup = 0;
                char outPair[8];
                seen.Insert(outPair, key, dup != 0);
            }
            KeyIter it(seen.mpBegin);
            for (;;) {
                KeyIter e(seen.mpEnd);
                if (!(it.mpNode != e.mpNode)) break;
                ResKey3 copy = *it;
                ++it;
            }
            if (list.mp) list.mp->Release();
        }
    }

    uint8_t tag2;
    IdVec ids(&tag2);
    WideBufA dirPath;
    FormatPath(&dirPath, L"%lsEditors_BlockData.package", GetBasePath());

    DatabasePackedFile* pkg;
    void* mem = ZoneObject_new(0x388, "Editor", 0, 0, 0, 0);
    if (mem) pkg = new (mem) DatabasePackedFile(0, 0);
    else pkg = 0;
    if (pkg) ((IPkgSecondary*)pkg)->AddRef();
    pkg->SetPath(dirPath.mpData ? (const wchar_t*)dirPath.mpData : 0);
    pkg->SetHoleUse(5, -1.0f);
    ((IPkgPrimary*)pkg)->Release();
    pkg->Open(2, 2, 0);
    FormatPath(&dirPath, L"%lsBlockData/", GetBasePath());
    CreateDirectoryPath((const wchar_t*)dirPath.mpData);
    IDatabaseDir* dbdir = Baker_s0041_c1d0()->GetDatabaseDir();

    XfSlot slots[32];
    WideBufB filePath;
    ByteBuf scratch;
    uint32_t types[6];
    types[0] = g_ResType0; types[1] = g_ResType1; types[2] = g_ResType2;
    types[3] = g_ResType3; types[4] = g_ResType4; types[5] = g_ResType5;

    MemoryStream ms(0, 0, "UTF/MemoryStream");
    ms.AddRef();
    ms.SetOption(1, 1.0f);
    ms.SetOption(2, 2.0f);

    for (unsigned t = 0; t < 6; ++t) {
        ids.erase(ids.mpBegin, ids.mpEnd);
        PropertyManager()->GetPropertyIDs(types[t], &ids);
        for (int i = 0; i < (int)(ids.mpEnd - ids.mpBegin); ++i) {
            if (haveList) {
                ResKey3 probe;
                probe.mInstance = ids.mpBegin[i];
                probe.mGroup = 0;
                probe.mType = types[t];
                KeyIter found(0);
                seen.Find(&found, &probe);
                KeyIter e(seen.mpEnd);
                if (found.mpNode == e.mpNode)
                    continue;
            }
            uint32_t* elem = &ids.mpBegin[i];
            IRecordCounted* rec = dbdir->GetRecord(*elem, types[t], 4);
            if (rec)
                rec->mRefCount = rec->mRefCount + 1;
            if (!rec) {
                continue;
            }
            dbdir->Process(rec);
            ms.SetSize(0);
            ms.SetPosition(0, 0);
            if (!CollectAndDestroy(rec, &ms)) {
                rec->Release();
                continue;
            }
            ResKeyRec key;
            key.mInstance = ids.mpBegin[i];
            key.mType = 0x5caa5e28;
            key.mGroup = types[t];
            IRecord* out = 0;
            if (out) {
                IRecord* o = out;
                out = 0;
                o->Release();
            }
            if (pkg->OpenRecord(&key, &out, 2, 2, 1, 0)) {
                IStream_s0041_c1d0* st = out->GetStream();
                st->Write(ms.GetData(), ms.GetSize());
                out->Close();
            }
            uint32_t* elem2 = &ids.mpBegin[i];
            FormatPath(&filePath, L"%s0x%08x!0x%08x.blockdata", (const wchar_t*)dirPath.mpData, types[t], *elem2);
            FileStream fs((const wchar_t*)filePath.mpData);
            if (fs.Open(2, 2, 0, 0)) {
                fs.Write(ms.GetData(), ms.GetSize());
                fs.Close();
            }
            if (out)
                out->Release();
            rec->Release();
        }
    }
    pkg->Close();
    ms.Destroy();
    scratch.ReleaseHeap();
    filePath.ReleaseHeap();
    if (pkg)
        ((IPkgSecondary*)pkg)->Release();
    dirPath.ReleaseHeap();
    for (uint32_t* p = ids.mpBegin; p < ids.mpEnd; ++p) {
    }
    ids.FreeAll();
    seen.DoNuke(seen.mpRoot);
}

// @ 0x0042f720
DequeIter DequeCopyImpl(DequeIter first, DequeIter last, DequeIter result)
{
    uint32_t dead[20];
    for (; first != last; ++result, ++first)
        *result = *first;
    return result;
}

// @ 0x0042f780
DequeIter DequeCopyBackwardImpl(DequeIter first, DequeIter last, DequeIter result)
{
    uint32_t dead[20];
    while (last != first)
        *--result = *--last;
    return result;
}

// @ 0x0042f8b0
ThreadedHolder& ThreadedHolder::operator=(const ThreadedHolder& x)
{
    mID = x.mID;
    mPtr = x.mPtr;
    return *this;
}

// @ 0x0042f920
WString_s0042_f160& WString_s0042_f160::AssignRange(const uint16_t* b, const uint16_t* e)
{
    uint32_t n = (uint32_t)(e - b);
    if (n <= (uint32_t)(mpEnd - mpBegin)) {
        memcpy(mpBegin, b, n * 2);
        EraseRange(mpBegin + n, mpEnd);
    } else {
        memcpy(mpBegin, b, (mpEnd - mpBegin) * 2);
        AppendRange(b + (mpEnd - mpBegin), e);
    }
    return *this;
}

// @ 0x0042f9d0
WideFixedBuf& WideFixedBuf::append(const wchar_t* pBegin, const wchar_t* pEnd)
{
    if (pBegin != pEnd) {
        const uint32_t nOldSize = mEnd - mBegin;
        const uint32_t n = pEnd - pBegin;
        const uint32_t nCapacity = (mCapacity - mBegin) - 1;
        if (nOldSize + n > nCapacity) {
            const uint32_t nLength = MaxRef(nCapacity > 8 ? nCapacity * 2 : 8, nOldSize + n) + 1;
            wchar_t* pNewBegin = DoAllocate(nLength);
            wchar_t* pNewEnd = pNewBegin;
            pNewEnd = CopyWide(mBegin, mEnd, pNewBegin);
            ScratchSlots<3>();
            pNewEnd = CopyWide(pBegin, pEnd, pNewEnd);
            *pNewEnd = 0;
            ReleaseHeap();
            mBegin = pNewBegin;
            mEnd = pNewEnd;
            mCapacity = pNewBegin + nLength;
        } else {
            const wchar_t* pTempBegin = pBegin;
            ++pTempBegin;
            CopyWide(pTempBegin, pEnd, mEnd + 1);
            mEnd[n] = 0;
            *mEnd = *pBegin;
            mEnd = mEnd + n;
        }
    }
    return *this;
}

// @ 0x0042fbb0
ThunkD_4036a0::ThunkD_4036a0()
{}

// @ 0x0042fbc0
ThunkD_410d40::ThunkD_410d40()
{}

// @ 0x0042fbd0
ThunkD_41a9f0::ThunkD_41a9f0()
{}

// @ 0x0042fbe0
DelObj::DelObj()
{}

// @ 0x0042fc20
EditorResourceD::EditorResourceD()
{}

// @ 0x0042fc40
bool __cdecl BakeSpritesLoadAndBuild(void* p1, uint32_t resA, uint32_t resB, uint32_t p4, void* p5, void* p6, void* p7, void* p8)
{
    IPropHost* application = g_pApp;
    Unk777ae0(0x219, 0, 0);
    void* display = GetUnk67dd60();
    ISettings* settingsMgr = GetSettings();
    uint32_t resourceKey[2] = { 0xffffffff, 0xffffffff };
    uint32_t secondKey[2] = { 0xffffffff, 0xffffffff };
    uint32_t keyZ[2] = { 0xffffffff, 0xffffffff };
    IBuilder* creator = GetBuilder();
    int spriteMode = 0;
    uint32_t bakeFlags = 0x100;
    PropHostRef host;
    bool isSet;
    if (GetResourceMgr()->Find(resA, resB, &host)) {
        isSet = TryGetInt(host, 0x4c6ba3c, spriteMode);
        isSet = TryGetUInt(host, 0x4c6ba29, bakeFlags);
    }
    GetSettings()->Set_f0((uint16_t)bakeFlags);
    settingsMgr->Get_ac(resourceKey);
    if (spriteMode == 0) {
        creator->Build(bakeFlags, resourceKey, p1, p5, p6, p7, ((int*)0x02458018), p4, spriteMode, secondKey, keyZ, p8);
    } else if (spriteMode == 1) {
        settingsMgr->Get_b8(secondKey);
        creator->Build(bakeFlags, resourceKey, p1, p5, p6, p7, ((int*)0x02458018), p4, spriteMode, secondKey, keyZ, p8);
    } else if (spriteMode == 2) {
        settingsMgr->Get_b8(secondKey);
        settingsMgr->Get_b4(keyZ);
        creator->Build(bakeFlags, resourceKey, p1, p5, p6, p7, ((int*)0x02458018), p4, spriteMode, secondKey, keyZ, p8);
    }
    return true;
}

// @ 0x0042ff00
void __cdecl BakeSpritesCreateThunk(RefVector* vecA, uint32_t f24, uint32_t f28, uint32_t f20, RefVector* vecB, Vector8* v8, Elem24Vec* elems, TransformVec* xf)
{
    BakeSpritesCreate(vecA, f24, f28, f20, vecB, v8, elems, xf);
}

// @ 0x0042ff30
void BakeSpritesResource::Run(int)
{
    GetMgr()->Notify(0x355dad8, 0, 0);
    mFlag80 = true;
    BakeSpritesLoadAndBuild(&mVecA, mField24, mField28, mField20, &mVecB, &mVec8, &mElems, &mTransforms);
}

// ---- BakeSpritesCreate support stubs (slice s0042f9d0)
struct IScene_s0042_f9d0 {
    virtual void _v0(); virtual void _v1(); virtual void _v2(); virtual void _v3();
    virtual bool Query(void* p);                          // +0x10
    virtual void _v5(); virtual void _v6(); virtual void _v7();
    virtual void Begin();                                 // +0x20
    virtual void End();                                   // +0x24
};
struct SceneGuard_s0042_f9d0 {
    IScene_s0042_f9d0* p;
    void Begin() { p->Begin(); }
    ~SceneGuard_s0042_f9d0() { p->End(); }
};
IScene_s0042_f9d0* __cdecl GetScene();                    // @ 0x0068F4D0
inline void TryGetFloat(IPropHost* host, uint32_t key, float& out)
{
    Property_s0042_f9d0* prop;
    if (host && host->GetProp(key, &prop) && prop->type == 0xd)
        out = *prop->GetFloat();
}
struct SceneObj_s0042_f9d0 {
    uint32_t pad[6];
    uint32_t mState;                                      // +0x18
    void Fn68f9b0(BakeSpritesResource* r);                // @ 0x0068F9B0
    void Fn432dc0(BakeSpritesResource* r);                // @ 0x00432DC0
    void Fn691380(SceneObj_s0042_f9d0* o);                // @ 0x00691380
    void Fn6909b0();                                      // @ 0x006909B0
    void Fn690120();                                      // @ 0x00690120
};
struct ObjRef_s0042_f9d0 {
    SceneObj_s0042_f9d0* p;
    void* GetRaw();                                       // @ 0x0041D940
    void* Get() { return GetRaw(); }
    SceneObj_s0042_f9d0* get() { SceneObj_s0042_f9d0* t = p; return t; }
    SceneObj_s0042_f9d0* operator->() { SceneObj_s0042_f9d0* t = p; return t; }
    ~ObjRef_s0042_f9d0() { if (p) p->Fn690120(); }
};
void __cdecl Unk729300(void* vec, float f, void* a, uint32_t b, uint32_t c, int d, void* e);
inline IScene_s0042_f9d0* GetSceneRef() { IScene_s0042_f9d0* s = GetScene(); return s; }

// @ 0x0042FFB0
bool __cdecl BakeSpritesCreate(RefVector* vecA, uint32_t f24, uint32_t f28, uint32_t f20,
                               RefVector* vecB, Vector8* v8, Elem24Vec* elems, TransformVec* xf)
{
    BakeSpritesResource* newRes = new BakeSpritesResource;
    newRes->mVecA = *vecA;
    newRes->mField24 = f24;
    newRes->mField28 = f28;
    newRes->mField20 = f20;
    newRes->mVecB = *vecB;
    newRes->mVec8 = *v8;
    newRes->mElems = *elems;
    newRes->mTransforms = *xf;

    SceneGuard_s0042_f9d0 sceneGuard;
    sceneGuard.p = GetSceneRef();
    sceneGuard.Begin();
    IScene_s0042_f9d0* sceneRef = GetScene();
    ObjRef_s0042_f9d0 primary;
    primary.p = 0;
    float mult = 1.0f;
    TryGetFloat(g_pApp, 0x444d5b0, mult);
    Unk729300(&newRes->mVecA, mult, primary.Get(), f24, f28, 0, xf->begin());
    ObjRef_s0042_f9d0 secondary;
    secondary.p = 0;
    if (sceneRef->Query(secondary.Get())) {
        secondary.p->Fn68f9b0(newRes);
        secondary.p->Fn432dc0(newRes);
        if (primary.p)
            secondary.p->Fn691380(primary.get());
        secondary->mState = 1;
    }
    if (primary.p)
        primary.p->Fn6909b0();
    secondary.p->Fn6909b0();
    return true;
}

// @ 0x004301E0
BakeSpritesResource::BakeSpritesResource()
{
    int unusedSlot;
    mFlag80 = false;
}

// @ 0x00561150
namespace SP {
int CEditorResourceThunk::f(void* p)
{
    (void)p;
    return 0;
}
}  // namespace SP
