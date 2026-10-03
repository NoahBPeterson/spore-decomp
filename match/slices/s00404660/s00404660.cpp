// BakerCommand::ParseLine (the "baker" cheat: bake models, show them, flush resources,
// describe rigblocks, toggle the bake queue), the resource-key filter it uses, and
// Resource::ThreadedObject::Release.
//
// This module was built WITHOUT optimization and without C++ EH unwinding:
// compile with /Od /Ob1 /MD /Gy /TP.
//
// /Od notes learned here:
//  - local slot order depends on local NAMES (hash buckets, ties broken by declaration
//    order), so the locals of ParseLine are named to reproduce the original frame.
//  - a parse-time temporary (GroupIDBits(x).bits.category) gives the original
//    "copy to temp, then shr/and straight into the argument" shape; an inline function
//    taking the value as a parameter does not.
//  - `v = f(v, b)` (nested inline) evaluates the right operand of `|` first, while the
//    same expression written out in place evaluates left first.
//  - inline destructors the compiler starts to expand but gives up on (EASTL VectorBase,
//    basic_string) still reserve their locals in the caller's frame.
#include "types.h"
#include <intrin.h>

struct ResourceKey {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
    ResourceKey() : instanceID(0), typeID(0), groupID(0) {}
    // The first parameter is bool-typed in the original (its zero is stored as `xor ecx,ecx`).
    ResourceKey(bool instance, uint32_t type, uint32_t group)
        : instanceID(instance), typeID(type), groupID(group) {}
    bool operator==(const ResourceKey& b) const
    {
        return instanceID == b.instanceID && typeID == b.typeID && groupID == b.groupID;
    }
};

// Group IDs carry a category byte in bits 16..23.
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
    virtual bool IsValid(const ResourceKey& key) = 0;
};

// Matches keys field by field; 0xffffffff is a wildcard, the group is compared under a mask.
struct ResourceKeyFilter : IResourceFilter {
    uint32_t mInstanceID;  // +0x04
    uint32_t mGroupID;     // +0x08
    uint32_t mTypeID;      // +0x0c
    uint32_t mGroupMask;   // +0x10
    ResourceKeyFilter() : mInstanceID(0xffffffff), mGroupID(0xffffffff), mTypeID(0xffffffff), mGroupMask(0xffffffff) {}
    virtual bool IsValid(const ResourceKey& key);
};

// @ 0x00404f10
bool ResourceKeyFilter::IsValid(const ResourceKey& key)
{
    return (mTypeID == 0xffffffff || mTypeID == key.typeID)
        && (mGroupID == 0xffffffff || (mGroupID & mGroupMask) == (key.groupID & mGroupMask))
        && (mInstanceID == 0xffffffff || mInstanceID == key.instanceID);
}

// Matches every key of one type (IsValid at 0x00404460).
struct TypeIDFilter : IResourceFilter {
    uint32_t mTypeID;
    TypeIDFilter(uint32_t typeID) : mTypeID(typeID) {}
    virtual bool IsValid(const ResourceKey& key);
};

// Empty allocator tag passed to the vector constructor.
struct KeyAllocator { KeyAllocator() {} };

// Allocator whose blocks carry a header word in front of the payload.
struct array_allocator {
    void deallocate(void* p, unsigned int)
    {
        if (((int*)p)[-1])
            delete[] (char*)p;
    }
    unsigned int mFlags;
    unsigned int mFlags2;
};

struct true_type {};
struct false_type {};
template <class T> struct has_trivial_destructor : false_type {};
template <class T> inline void destruct_impl(T* first, T* last, false_type)
{
    for (; first < last; ++first)
        first->~T();
}
template <typename T> inline void destruct(T* first, T* last)
{
    destruct_impl(first, last, has_trivial_destructor<T>());
}

template <typename T> struct VectorBase {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    array_allocator mAllocator;
    VectorBase(const KeyAllocator& a);  // 0x00540470
    ~VectorBase()
    {
        if (mpBegin)
            mAllocator.deallocate(mpBegin, (mpCapacity - mpBegin) * sizeof(T));
    }
};

template <typename T> struct vector : VectorBase<T> {
    vector(const KeyAllocator& a = KeyAllocator()) : VectorBase<T>(a) {}
    ~vector() { destruct(this->mpBegin, this->mpEnd); }
    bool empty() const;
    void push_back(const T& value);
    T& front() { return *this->mpBegin; }
    int size() const { return (int)(this->mpEnd - this->mpBegin); }
};
typedef vector<ResourceKey> KeyVector;

extern wchar_t gEmptyString16[];
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

struct IObject {
    virtual int AddRef() = 0;
    virtual int Release() = 0;
};

template <class T> struct intrusive_ptr {
    T* mpObject;
    intrusive_ptr() : mpObject(0) {}
    intrusive_ptr(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~intrusive_ptr() { if (mpObject) mpObject->Release(); }
    T* operator->() const { return mpObject; }
    T* get() const { return mpObject; }
};

class IResourceManager {
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
    virtual bool GetFileName(const ResourceKey& key, string16& name);  // 0x7c
};

class cEditorModel {
public:
    uint32_t pad[3];
    ResourceKey mKey;  // +0x0c
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

class IMessageManager {
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
    virtual void QueueBake(const ResourceKey& key, const BakeRequest& request);  // 0x4c
};

struct MessageArg {
    uint32_t mValue;
    uint32_t mType;
};

namespace Resource {
class ThreadedObject {
public:
    ThreadedObject(int refCount);
    virtual ~ThreadedObject();
    virtual int AddRef();
    virtual int Release();
    volatile long mnRefCount;
};

// @ 0x00404f90
int ThreadedObject::Release()
{
    long refCount = _InterlockedDecrement(&mnRefCount);
    if (refCount != 0)
        return refCount;
    _InterlockedExchange(&mnRefCount, 1);  // keep the count stable while destroying
    delete this;
    return 0;
}
}

struct MessageArgs {
    MessageArg mData[6];
    void SetValue(int index, uint32_t value) { mData[index].mValue = value; }
};

// Message posted to show a baked model in the model viewer (0x40 bytes, vtable 0x013eb844).
class ViewModelMessage : public Resource::ThreadedObject {
public:
    ViewModelMessage() : ThreadedObject(0), mField38(0) {}
    MessageArgs mArgs;    // +0x08
    uint32_t mField38;
    uint32_t mField3C;
};

void* operator new(unsigned int size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);

inline uint32_t MakeGroupSubtype(uint32_t groupID, uint32_t subtype) { return (groupID & 0xffff00ff) | ((subtype & 0xff) << 8); }
inline uint32_t SetGroupSubtype(uint32_t groupID, uint32_t subtype) { groupID = MakeGroupSubtype(groupID, subtype); return groupID; }

IResourceManager* ResourceManager();     // 0x0067dcd0
IGameModeManager* GameModeManager();     // 0x0067dd10
IMessageManager* MessageManager();       // 0x0067dcc0
IRenderManager* RenderManager();         // 0x0067dda0
IBaker* Baker();                         // 0x00401010
void ResourceKeyFromString(ResourceKey* pKey, const char* str, uint32_t defaultType, uint32_t defaultGroup);  // 0x0068d5a0
uint32_t GetTypeForCategory(uint32_t category, int);  // 0x004bbd20
bool IsBakeableType(uint32_t typeID, int);           // 0x004bbe20
void GetDisplayName(const ResourceKey& key, string16& name, int);  // 0x00b1e4d0
void DescribeBlocks(int group, int instance);  // 0x0041c1d0

namespace ArgScript {
    class Line {
    public:
        const char* GetArgumentAt(int index);  // 0x00837f20
        int GetArgumentsCount();               // 0x00837f30
    };
    void PrintF(void* pOutput, const char* fmt, ...);  // 0x00841000

    class ICommand {
    public:
        virtual void ParseLine(Line& line);
        void* mpOutput;
        unsigned int mField8;
        unsigned int mFieldC;
    };

    class OptionParser {
    public:
        const char* GetUsage(const char* name, int verbose);  // 0x0083a2f0
        void Parse(Line& line, void* pOutput);                 // 0x0083b9d0
        bool IsSet(int option) const { return (mFlags & (1 << option)) != 0; }
        unsigned int mData[28];
        unsigned int mFlags;  // +0x70
        unsigned int mData2[21];
    };
}

class BakerCommand : public ArgScript::ICommand {
public:
    virtual void ParseLine(ArgScript::Line& line);

    IBaker* mpBaker;                    // +0x10
    ArgScript::OptionParser mOptions;   // +0x14
    const char* mKeyFilter;             // +0xdc
    int mLimit;                         // +0xe0
    bool mProcessQueue;                 // +0xe4
    int mFilterGroup;                   // +0xe8
    int mFilterInstance;                // +0xec
};

// @ 0x00404660
void BakerCommand::ParseLine(ArgScript::Line& line)
{
    mKeyFilter = 0;
    mLimit = 0;
    if (line.GetArgumentsCount() == 1) {
        ArgScript::PrintF(mpOutput, mOptions.GetUsage(line.GetArgumentAt(0), 1));
        return;
    } else {
        mOptions.Parse(line, mpOutput);
    }

    IResourceManager* resourceManager = ResourceManager();
    ResourceKeyFilter keyFilter;
    KeyVector resourceKeys;

    if (mKeyFilter) {
        ResourceKey key;
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
            ResourceKey modelKey = pEditorModel->mKey;
            if (modelKey == ResourceKey(0, 0, 0)) {
                ArgScript::PrintF(mpOutput, "No key -- you need to save the model first.\n");
                return;
            }
            resourceKeys.push_back(pEditorModel->mKey);
        }
    }

    if (mOptions.IsSet(0) && !resourceKeys.empty()) {
        string16 displayName;
        intrusive_ptr<IObject> pRes;  // never assigned in the original either
        int j = 0;
        int numKeys = resourceKeys.size();
        int numBakes = 0;
        for (; j < numKeys && (mLimit == 0 || numBakes < mLimit); j++) {
            ResourceKey key = resourceKeys.mpBegin[j];
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
            intrusive_ptr<ViewModelMessage> pMsg = new("Editor", 0, 0, 0, 0) ViewModelMessage;
            pMsg->mArgs.SetValue(0, resourceKeys.front().instanceID);
            pMsg->mArgs.SetValue(1, SetGroupSubtype(resourceKeys.front().groupID, 0x62));
            MessageManager()->PostMSG(0x4051e54, pMsg.get(), 0, 0);
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
