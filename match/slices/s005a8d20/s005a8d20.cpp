// slice s005a8d20 — SP::Editor launch path (cEditorLaunchData, Editor::Launch), the editor
// property-list registry map, hand badness calculator and assorted editor helpers.
// Module flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <math.h>

typedef unsigned int size_t;
extern "C" long __cdecl _InterlockedExchange(long volatile* target, long value);
#pragma intrinsic(_InterlockedExchange)

// EA allocator entry points (0x00F473A0 / 0x00F47380)
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void  operator delete[](void* p);
inline void* operator new(size_t, void* p) { return p; }

struct ResourceKey {
    uint32_t instanceID;   // +0x0
    uint32_t typeID;       // +0x4
    uint32_t groupID;      // +0x8
    ResourceKey() : instanceID(0), typeID(0), groupID(0) {}
};

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    Vector3 operator-(const Vector3& b) const { return Vector3(x - b.x, y - b.y, z - b.z); }
    float Dot(const Vector3& b) const { return x * b.x + y * b.y + z * b.z; }
};
struct Quaternion { float x, y, z, w; };
struct Matrix3 {
    float m[9];
    Matrix3& SetRotation(const Quaternion& q);   // 0x0041CB40
};
Matrix3 operator*(const Matrix3& a, const Matrix3& b);   // 0x0041DE20

// SP::Transform (ModAPI layout)
struct Transform {
    uint16_t mnFlags;            // +0x0
    uint16_t mnTransformCount;   // +0x2
    Vector3  mOffset;            // +0x4
    float    mfScale;            // +0x10
    Matrix3  mRotation;          // +0x14
    void SetOffset(const Vector3& offset)
    {
        mOffset = offset;
        mnFlags |= 4;
        mnTransformCount++;
    }
    void SetRotation(const Matrix3& rotation)
    {
        mnFlags |= 2;
        mnTransformCount++;
        mRotation = rotation;
    }
};

namespace EA {

template <typename T>
class RefCountTemplate {
public:
    RefCountTemplate() : mnRefCount(0) {}
    virtual ~RefCountTemplate() {}
    int AddRef() { return ++mnRefCount; }
    int Release()
    {
        int n = (*(volatile int*)&mnRefCount += -1);
        if (n == 0) {
            mnRefCount = 1;
            delete this;
            return 0;
        }
        return mnRefCount;
    }
    T mnRefCount;
};

template <typename T>
class AutoRefCount {
public:
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    AutoRefCount& operator=(T* pObject)
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
    T** AsPPTypeParam()
    {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
        return &mpObject;
    }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};

namespace COM {
class IUnknown32 {
public:
    virtual int AddRef() = 0;
    virtual int Release() = 0;
};
}

namespace Messaging {
class IMessageRC {
public:
    virtual ~IMessageRC() {}
    virtual int AddRef() = 0;
    virtual int Release() = 0;
};
}

}  // namespace EA

namespace eastl {

struct allocator {};
struct sp_vector_allocator {
    uint32_t mData[2];
    sp_vector_allocator() {}
    void deallocate(void* p, size_t)
    {
        if (((uint32_t*)p)[-1])
            operator delete[](p);
    }
};
struct true_type {};

template <size_t N>
struct bitset {
    uint32_t mWord[N / 32];
    bitset() { reset(); }
    void reset() { for (size_t i = 0; i < N / 32; i++) mWord[i] = 0; }
    bool any() const
    {
        for (size_t i = 0; i < N / 32; i++) {
            if (mWord[i])
                return true;
        }
        return false;
    }
    bool none() const { return !any(); }
};

template <typename T>
class basic_string {
public:
    T*        mpBegin;
    T*        mpEnd;
    T*        mpCapacity;
    allocator mAllocator;
    basic_string();
    ~basic_string()
    {
        if ((mpCapacity - mpBegin) > 1 && mpBegin)
            operator delete[](mpBegin);
    }
};
extern wchar_t gEmptyString16[2];   // 0x01667BAC
template <> inline basic_string<wchar_t>::basic_string()
    : mpBegin(gEmptyString16), mpEnd(gEmptyString16), mpCapacity(gEmptyString16 + 1)
{
}

template <typename T>
struct copy_result {
    T* mpResult;
    copy_result() {}
};
template <typename T, typename Tag>
copy_result<T> uninitialized_copy_impl(const T* first, const T* last, T* dest, Tag);   // 0x004E8EE0 (AutoRefCount instance)
struct false_type { false_type() {} };
template <typename T>
inline T* uninitialized_copy_ptr(const T* first, const T* last, T* result)
{
    const copy_result<T> r = uninitialized_copy_impl(first, last, result, false_type());
    return r.mpResult;
}

template <typename T>
struct VectorBase {
    T*                  mpBegin;      // +0x0
    T*                  mpEnd;        // +0x4
    T*                  mpCapacity;   // +0x8
    sp_vector_allocator mAllocator;   // +0xc
    VectorBase() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    VectorBase(size_t n, const sp_vector_allocator& allocator);   // 0x0066AEC0 (folded)
    ~VectorBase()
    {
        if (mpBegin)
            mAllocator.deallocate(mpBegin, (char*)mpCapacity - (char*)mpBegin);
    }
};

template <typename T>
class vector : public VectorBase<T> {
public:
    vector() {}
    vector(const vector& x) : VectorBase<T>((size_t)(x.mpEnd - x.mpBegin), x.mAllocator)
    {
        this->mpEnd = uninitialized_copy_ptr(x.mpBegin, x.mpEnd, this->mpBegin);
    }
    ~vector() { DoDestroyValues(this->mpBegin, this->mpEnd); }
    void DoDestroyValues(T* first, T* last)
    {
        for (; first < last; ++first)
            first->~T();
    }
    T* begin() { return this->mpBegin; }
    T* end() { return this->mpEnd; }
    T* DoInsertValue(T* position, const T& value);   // 0x004B6000 (AutoRefCount<cPropertyList> instance)
    void push_back(const T& value)
    {
        if (this->mpEnd < this->mpCapacity)
            ::new (this->mpEnd++) T(value);
        else
            DoInsertValue(this->mpEnd, value);
    }
};

template <typename T1, typename T2>
struct pair {
    T1 first;
    T2 second;
    __forceinline pair(const T1& a, const T2& b) : first(a), second(b) {}
};

struct rbtree_node_base {
    rbtree_node_base* mpNodeRight;
    rbtree_node_base* mpNodeLeft;
    rbtree_node_base* mpNodeParent;
    char              mColor;
};

template <typename T>
struct rbtree_node : public rbtree_node_base {
    T mValue;   // +0x10
};

template <typename T>
struct rbtree_iterator {
    typedef rbtree_node<T> node_type;
    node_type* mpNode;
    rbtree_iterator() : mpNode(0) {}
    explicit rbtree_iterator(const node_type* pNode) : mpNode((node_type*)pNode) {}
    rbtree_iterator(const rbtree_iterator& x) : mpNode(x.mpNode) {}
    T* operator->() const { return &mpNode->mValue; }
    bool operator==(const rbtree_iterator& x) const { return mpNode == x.mpNode; }
    bool operator!=(const rbtree_iterator& x) const { return mpNode != x.mpNode; }
};

template <typename T>
struct less { bool operator()(const T& a, const T& b) const { return a < b; } };

template <typename Key, typename T>
class map {
public:
    typedef pair<const Key, T>          value_type;
    typedef rbtree_node<value_type>     node_type;
    typedef rbtree_iterator<value_type> iterator;

    less<Key>        mCompare;
    rbtree_node_base mAnchor;
    uint32_t         mnSize;
    allocator        mAllocator;

    iterator end() { return iterator((node_type*)&mAnchor); }
    void reset()
    {
        mAnchor.mpNodeRight  = &mAnchor;
        mAnchor.mpNodeLeft   = &mAnchor;
        mAnchor.mpNodeParent = 0;
        mAnchor.mColor       = 0;
        mnSize               = 0;
    }
    void clear()
    {
        DoNukeSubtree((node_type*)mAnchor.mpNodeParent);
        reset();
    }
    iterator find(const Key& key);                                                   // 0x00E5C780 (folded)
    iterator DoInsertValue(iterator position, const value_type& value, true_type);  // 0x005A9820
    iterator insert(iterator position, const value_type& value)
    {
        return DoInsertValue(position, value, true_type());
    }
    iterator lower_bound(const Key& key)
    {
        node_type*        pCurrent  = (node_type*)mAnchor.mpNodeParent;
        rbtree_node_base* pRangeEnd = &mAnchor;
        while (pCurrent) {
            if (!mCompare(pCurrent->mValue.first, key)) {
                pRangeEnd = pCurrent;
                pCurrent  = (node_type*)pCurrent->mpNodeLeft;
            } else
                pCurrent = (node_type*)pCurrent->mpNodeRight;
        }
        return iterator((node_type*)pRangeEnd);
    }
    T& operator[](const Key& key);
    void DoFreeNode(node_type* pNode)
    {
        pNode->~node_type();
        operator delete[](pNode);
    }
    void DoNukeSubtree(node_type* pNode);
};

}  // namespace eastl

namespace SP {

class cPropertyList {
public:
    virtual int AddRef();
    virtual int Release();
};

class cResource {
public:
    virtual int AddRef();
    virtual int Release();
    char pad_4[0x18 - 0x4];
    uint32_t mTypeID;   // +0x18
};

class cResourceManager {
public:
    virtual void Unk0(); virtual void Unk1(); virtual void Unk2();
    virtual bool GetResource(const ResourceKey& key, cResource** ppResource, int a, int b, int c, int d);   // slot 3
};
cResourceManager* ResourceManager();   // 0x0067DCD0

class cPropertyManager {
public:
    virtual void Unk0(); virtual void Unk1(); virtual void Unk2(); virtual void Unk3();
    virtual void Unk4(); virtual void Unk5(); virtual void Unk6(); virtual void Unk7();
    virtual void Unk8(); virtual void Unk9(); virtual void Unk10();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, cPropertyList** ppList);   // slot 11
};
cPropertyManager* PropertyManager();   // 0x0067DE30
uint32_t RemapTypeId(uint32_t typeID);   // 0x00432F10
extern uint32_t kEditorPropertyGroup;    // 0x01510F44

class cSPEditorModelPart;
struct cSPModelObject {
    char      pad_0[8];
    Transform mTransform;   // +0x8
};
class cSPEditorRigblockModel {
public:
    virtual void Unk0(); virtual void Unk1(); virtual void Unk2(); virtual void Unk3();
    virtual void Unk4(); virtual void Unk5(); virtual void Unk6(); virtual void Unk7();
    virtual void Unk8();
    virtual Vector3 GetPosition();   // slot 9
    void UpdateModelTransforms();

    char pad_4[0x10 - 0x4];
    cSPEditorRigblockModel* mpParent;   // +0x10
    cSPModelObject*         mpModel;    // +0x14
    cSPModelObject*         mpModelLOD; // +0x18
    char pad_1c[0x5c - 0x1c];
    Quaternion              mOrientation;   // +0x5c
    char pad_6c[0x60 + 0x5c - 0x6c];
};

class cSPEditorHandBadnessCalculator {
public:
    void* AsInterface(uint32_t typeID);
};

}  // namespace SP

using namespace SP;

// @ 0x005a8d20
void cSPEditorRigblockModel::UpdateModelTransforms()
{
    if (mpModel && mpModelLOD) {
        Vector3 position = GetPosition();
        mpModel->mTransform.SetOffset(position);
        mpModelLOD->mTransform.SetOffset(position);
        Matrix3 rotation;
        rotation.SetRotation(mOrientation);
        if (mpParent)
            rotation = rotation * *(Matrix3*)((char*)mpParent + 0x60);
        mpModel->mTransform.SetRotation(rotation);
        mpModelLOD->mTransform.SetRotation(rotation);
    }
}

// @ 0x005a8e10
void* cSPEditorHandBadnessCalculator::AsInterface(uint32_t typeID)
{
    return (typeID == 0xee3f516e || typeID == 0x212d6eb) ? this : 0;
}

// @ 0x005a8ea0
template bool eastl::bitset<128>::none() const;

// @ 0x005a8ed0
bool GetPropertyListForResource(ResourceKey key, cPropertyList** ppList)
{
    EA::AutoRefCount<cResource> resource;
    if (ResourceManager()->GetResource(key, resource.AsPPTypeParam(), 0, 0, 0, 0) && resource &&
        PropertyManager()->GetPropertyList(RemapTypeId(resource->mTypeID), kEditorPropertyGroup, ppList))
        return true;
    return false;
}

class cResourceProperties {
public:
    virtual int AddRef(); virtual int Release(); virtual void Unk2();
    virtual struct cPropertyEntry* GetProperty(uint32_t propID);   // slot 3
};
struct cPropertyEntry { char pad_0[0x18]; uint32_t mValue; };

// @ 0x005a8f80
static uint32_t GetEditorConfigForModel(const ResourceKey* key)
{
    uint32_t config;
    cResourceManager* manager = ResourceManager();
    EA::AutoRefCount<cResourceProperties> resource;
    cPropertyEntry* entry;
    if (manager->GetResource(*key, (cResource**)&resource.mpObject, 0, 0, 0, 0) && resource &&
        (entry = resource->GetProperty(0x3c609f8)) != 0)
        return RemapTypeId(entry->mValue);
    switch (key->typeID) {
    case 0x2b978c46: config = 0x465c50ba; break;
    case 0x24682294: config = 0x99f87089; break;
    case 0x2399be55: config = 0xd817cd63; break;
    case 0x3d97a8e4: config = 0x3615a30b; break;
    case 0x476a98c7: config = 0x96b24187; break;
    case 0x438f6347: config = 0x1c7eca95; break;
    default: config = (uint32_t)(cResourceProperties*)resource; break;
    }
    return config;
}

typedef eastl::vector<EA::AutoRefCount<cPropertyList> > PropertyListVector;
typedef eastl::map<uint32_t, PropertyListVector> EditorPropListMap;
extern EditorPropListMap sEditorPropLists;   // 0x0151102C

// @ 0x005a9050
PropertyListVector* FindEditorPropertyLists(uint32_t id)
{
    EditorPropListMap::iterator it = sEditorPropLists.find(id);
    if (it != sEditorPropLists.end())
        return &it->second;
    return 0;
}

namespace SP { namespace Editor {

class cAppMode {
public:
    virtual void Unk0(); virtual void Unk1(); virtual void Unk2(); virtual void Unk3();
    virtual void Unk4(); virtual void Unk5(); virtual void Unk6(); virtual void Unk7();
    virtual void Unk8(); virtual void Unk9(); virtual void Unk10(); virtual void Unk11();
    virtual void Unk12(); virtual void Unk13();
    virtual uint32_t GetModeID();   // slot 14
};
cAppMode* App();   // 0x0067DD10

class cEditorLaunchData : public EA::Messaging::IMessageRC, public EA::RefCountTemplate<int> {
public:
    cEditorLaunchData();
    virtual int AddRef();
    virtual int Release();

    uint32_t                     mConfig;                  // +0xc
    ResourceKey                  mModelKey;                // +0x10
    uint32_t                     mCallingAppModeID;        // +0x1c
    bool                         mIsFirstTimeInEditor;     // +0x20
    eastl::bitset<128>           mEditorValidationLevel;   // +0x24
    bool                         mCanSwitchEditor;         // +0x34
    bool                         mUseAlternateName;        // +0x35
    bool                         mShowLoadButton;          // +0x36
    bool                         mShowSaveButton;          // +0x37
    bool                         mShowNewButton;           // +0x38
    bool                         mConfirmOnExit;           // +0x39
    bool                         mPublishOnExit;           // +0x3a
    bool                         mb3b;                     // +0x3b
    bool                         mb3c;                     // +0x3c
    bool                         mb3d;                     // +0x3d
    eastl::basic_string<wchar_t> mAlternateName;           // +0x40
    eastl::basic_string<wchar_t> mAlternateDescription;    // +0x50
    float                        mf60;                     // +0x60
    bool                         mb64;                     // +0x64
    bool                         mb65;                     // +0x65
    bool                         mb66;                     // +0x66
    uint32_t                     m68;                      // +0x68
    bool                         mb6c;                     // +0x6c
    bool                         mb6d;                     // +0x6d
    bool                         mb6e;                     // +0x6e
    bool                         mb6f;                     // +0x6f
    eastl::vector<uint32_t>      mList;                    // +0x70
    uint32_t                     m84;                      // +0x84
    uint32_t                     m88;                      // +0x88
    uint32_t                     m8c;                      // +0x8c
    uint32_t                     mCallerID;                // +0x90
    EA::AutoRefCount<EA::COM::IUnknown32> mCallerData;     // +0x94
    EA::AutoRefCount<EA::Messaging::IMessageRC> mpReturnMessage;   // +0x98
};

extern eastl::bitset<128> kDefaultValidationLevel;   // 0x015DA7C4

bool Launch(cEditorLaunchData* pData);
bool Launch(uint32_t config, const ResourceKey& modelKey, uint32_t callerID,
            EA::COM::IUnknown32* pCallerData, eastl::bitset<128> validationLevel, bool canSwitchEditor);

}}  // namespace SP::Editor

using namespace SP::Editor;

// @ 0x005a9080
cEditorLaunchData::cEditorLaunchData()
    : mConfig((uint32_t)-1), mCallingAppModeID(App()->GetModeID()), mIsFirstTimeInEditor(false),
      mCanSwitchEditor(false), mUseAlternateName(false), mShowLoadButton(false), mShowSaveButton(false),
      mShowNewButton(false), mConfirmOnExit(true), mPublishOnExit(false), mb3b(true), mb3c(false), mb3d(true),
      mf60(0.0f), mb64(false), mb65(false), mb66(false), m68(0), mb6c(false), mb6d(true), mb6e(true), mb6f(false),
      m84(0), m88(0), m8c(0), mCallerID(0)
{
}

// @ 0x005a9170
// (implicit) cEditorLaunchData::~cEditorLaunchData()
void DestroyEditorLaunchData(cEditorLaunchData* p)
{
    p->cEditorLaunchData::~cEditorLaunchData();
}

class cMessageServer {
public:
    virtual void Unk0(); virtual void Unk1(); virtual void Unk2(); virtual void Unk3();
    virtual void Unk4(); virtual void Unk5();
    virtual void PostMessage(uint32_t messageID, void* pMessage, int a, int b);   // slot 6
};
cMessageServer* MessageServer();   // 0x0067DCC0

struct cMessageData {
    cMessageData() : mID(0) {}
    long     mnRefCount;   // +0x4
    uint32_t mType;        // +0x8
    uint32_t pad_c[9];
    uint32_t mID;          // +0x30
    uint32_t pad_34;
};
class cMessageBase : public cMessageData {
public:
    cMessageBase() { _InterlockedExchange(&mnRefCount, 0); }
    virtual void Unk0();
    virtual int AddRef();
    virtual int Release();
};
class cEditorLaunchMessage : public cMessageBase {
public:
    cEditorLaunchMessage() : m38(0) {}
    virtual int AddRef();
    uint32_t m38;          // +0x38
    uint32_t pad_3c;
};

struct cGameModeManager { void SetMode(uint32_t modeID); };                      // 0x00801BB0
cGameModeManager* GameModeManager();                                             // 0x0067CAB0
struct cTutorialFlags { void SetFlags(uint32_t propID, uint32_t mask, bool value); };   // 0x00676ED0
cTutorialFlags* TutorialFlags();                                                 // 0x00675250
struct cAppSettings { char pad_0[0x118]; int mbDisableTutorials; };
struct cAppPropertiesHolder { char pad_0[0x3c]; cAppSettings* mpSettings; };
extern cAppPropertiesHolder* sAppProperties;   // 0x015FD918

// @ 0x005a9200
bool SP::Editor::Launch(cEditorLaunchData* pData)
{
    pData->mCallingAppModeID = App()->GetModeID();
    if (pData->mEditorValidationLevel.none())
        pData->mEditorValidationLevel = kDefaultValidationLevel;
    if (pData->mConfig == (uint32_t)-1)
        pData->mConfig = GetEditorConfigForModel(&pData->mModelKey);

    cMessageServer* server = MessageServer();
    server->PostMessage(0xb03bc30c, pData, 0, 0);

    EA::AutoRefCount<cEditorLaunchMessage> msg(new ("App", 0, 0, 0, 0) cEditorLaunchMessage());
    msg->mID   = 0xe11332;
    msg->mType = 0xdbdba1;
    server->PostMessage(msg->mID, msg, 0, 0);
    GameModeManager()->SetMode(0x1003);

    int editorIndex = 0;
    switch ((int)pData->mConfig) {
    case (int)0x96b24187: editorIndex = 15; break;
    case (int)0xa56567f7: case (int)0x37e82da1: editorIndex = 14; break;
    case (int)0xbc1041e6: case (int)0xc15695da: case (int)0x2090a11b: editorIndex = 13; break;
    case (int)0x1a4e0708: case (int)0x441cd3e6: case (int)0x449c040f: editorIndex = 12; break;
    case (int)0x8f963dcb: case (int)0x1f2a25b6: case (int)0x2a5147a9: editorIndex = 11; break;
    case (int)0x9ad7d4aa: case (int)0xf670aa43: case (int)0x7d433fad: editorIndex = 10; break;
    case (int)0x99e92f05: case (int)0x8707be7d: case (int)0xbdd15f3d: case (int)0x4e3f7777: case (int)0x72c49181: editorIndex = 9; break;
    case (int)0x9adf00a9: editorIndex = 8; break;
    case (int)0x156276d1: case (int)0x247e2615: editorIndex = 7; break;
    case (int)0xb7af8ff8: case (int)0x281f5960: case (int)0x290adace: case (int)0x312e9d6a: case (int)0x465c50ba: case (int)0x5bf8f774:
        editorIndex = 6; break;
    case (int)0x1d2ec0a0: case (int)0x1d2ec0a4: case (int)0x1d2ec0a5: case (int)0x1d2ec0a6: case (int)0x1d2ec0a7: editorIndex = 5; break;
    }
    if (!sAppProperties->mpSettings->mbDisableTutorials && editorIndex)
        TutorialFlags()->SetFlags(0xd082675a, 1 << editorIndex, true);
    return true;
}

// @ 0x005a94d0
bool SP::Editor::Launch(uint32_t config, const ResourceKey& modelKey, uint32_t callerID,
                        EA::COM::IUnknown32* pCallerData, eastl::bitset<128> validationLevel, bool canSwitchEditor)
{
    EA::AutoRefCount<cEditorLaunchData> data(new ("App", 0, 0, 0, 0) cEditorLaunchData());
    data->mCallingAppModeID = App()->GetModeID();
    data->mModelKey         = modelKey;
    data->mConfig           = config;
    data->mCallerID         = callerID;
    data->mCallerData       = pCallerData;
    data->mCanSwitchEditor  = canSwitchEditor;
    data->mb64              = true;
    if (canSwitchEditor) {
        data->mShowLoadButton = true;
        data->mShowNewButton  = true;
        data->mShowSaveButton = true;
        data->mb3c            = false;
        data->mb3d            = false;
    }
    if (validationLevel.none())
        data->mEditorValidationLevel = kDefaultValidationLevel;
    else
        data->mEditorValidationLevel = validationLevel;
    return Launch(data);
}

// @ 0x005a9610
// (implicit) pair<const uint32_t, vector<AutoRefCount<cPropertyList>>> copy constructor
void CopyConstructEditorPropListEntry(void* p, const EditorPropListMap::value_type& x)
{
    new (p) EditorPropListMap::value_type(x);
}

// @ 0x005a97a0
template <typename Key, typename T>
void eastl::map<Key, T>::DoNukeSubtree(node_type* pNode)
{
    while (pNode) {
        DoNukeSubtree((node_type*)pNode->mpNodeRight);
        node_type* const pNodeLeft = (node_type*)pNode->mpNodeLeft;
        DoFreeNode(pNode);
        pNode = pNodeLeft;
    }
}

// @ 0x005a98f0
void ClearEditorPropertyLists()
{
    sEditorPropLists.clear();
}

// @ 0x005a9930
template <typename Key, typename T>
T& eastl::map<Key, T>::operator[](const Key& key)
{
    iterator itLower(lower_bound(key));
    if ((itLower == end()) || mCompare(key, itLower->first))
        itLower = insert(itLower, value_type(key, T()));
    return itLower->second;
}

template class eastl::map<uint32_t, PropertyListVector>;

class cPropertyListEx : public cPropertyList {
public:
    virtual void Unk2(); virtual void Unk3(); virtual void Unk4(); virtual void Unk5(); virtual void Unk6();
    virtual bool HasProperty(uint32_t propID);                  // slot 7
    virtual void Unk8(); virtual void Unk9();
    virtual struct cKeyArrayProperty* GetProperty(uint32_t propID);   // slot 10
};
struct cKeyArrayProperty {
    ResourceKey* mpKeys;     // +0x0 (or inline value)
    uint32_t     pad_4;
    int          mnCount;    // +0x8
    uint32_t     pad_c;
    uint16_t     mnFlags;    // +0x10
    uint16_t     mnType;     // +0x12
};
class cPropertyManagerEx : public cPropertyManager {
public:
    virtual void Unk12(); virtual void Unk13(); virtual void Unk14(); virtual void Unk15(); virtual void Unk16();
    virtual void Unk17();
    virtual void GetPropertyListIDs(uint32_t groupID, eastl::vector<uint32_t>* pIDs);   // slot 18
};

// @ 0x005a9a00
static void RegisterEditorPropertyLists(uint32_t groupID)
{
    eastl::vector<uint32_t> ids;
    ((cPropertyManagerEx*)PropertyManager())->GetPropertyListIDs(groupID, &ids);
    for (uint32_t* it = ids.begin(); it != ids.end(); ++it) {
        EA::AutoRefCount<cPropertyList> propList;
        PropertyManager()->GetPropertyList(*it, groupID, propList.AsPPTypeParam());
        if (propList && ((cPropertyListEx*)propList.mpObject)->HasProperty(0x1b7dd74)) {
            cKeyArrayProperty* prop = ((cPropertyListEx*)propList.mpObject)->GetProperty(0x1b7dd74);
            if (prop->mnType == 0x20) {
                ResourceKey* keys = (prop->mnFlags & 0x30) ? prop->mpKeys : (ResourceKey*)prop;
                int count = (prop->mnFlags & 0x30) ? prop->mnCount : 1;
                for (int i = 0; i < count; i++, keys++)
                    sEditorPropLists[keys->instanceID].push_back(propList);
            }
        }
    }
}

// @ 0x005a9b60
void RegisterAllEditorPropertyLists()
{
    RegisterEditorPropertyLists(0xdd91ac58);
    RegisterEditorPropertyLists(0x1b68db4);
}

class cEditorBlockBase {
public:
    virtual void Unk0();
};
class cEditorBlock : public cEditorBlockBase, public EA::RefCountTemplate<int> {
public:
    bool IsLocked();   // 0x004ADC40
};
struct cEditorModelBase;
typedef eastl::vector<EA::AutoRefCount<cPropertyList> > BlockList;
void GetBlockPile(cEditorModelBase* model, BlockList* blocks, int flags);                    // 0x0048C790
void SelectBlocks(cEditorModelBase* model, BlockList* blocks);                               // 0x004961D0
void SnapBlocks(cEditorModelBase* model, BlockList* blocks);                                 // 0x004A8860
namespace SP { namespace EditorUtils {
void SetSymmetricBlocksUIState(cEditorModelBase* model, BlockList* blocks, int state);      // 0x004A7F30
}}
struct cEditorModelBase { char pad_0[0x28]; cEditorBlock* mpActiveBlock; };

class cEditorSelectionHandler {
public:
    bool HandleMessage(uint32_t a, uint32_t b, uint32_t c, uint32_t d);
    char pad_0[0x1c];
    cEditorModelBase* mpModel;   // +0x1c
    char pad_20[0x2c - 0x20];
    BlockList mBlocks;           // +0x2c
};

// @ 0x005a9bc0
bool cEditorSelectionHandler::HandleMessage(uint32_t, uint32_t, uint32_t, uint32_t)
{
    cEditorBlock* block = mpModel->mpActiveBlock;
    if (block)
        block->AddRef();
    GetBlockPile(mpModel, &mBlocks, 0);
    SelectBlocks(mpModel, &mBlocks);
    if (!block->IsLocked())
        SnapBlocks(mpModel, &mBlocks);
    SP::EditorUtils::SetSymmetricBlocksUIState(mpModel, &mBlocks, 0);
    if (block)
        block->Release();
    return false;
}

// @ 0x005a9c40
bool IntersectRaySphere(const Vector3& origin, const Vector3& direction, const Vector3& center, float radius,
                        float* pDistance)
{
    Vector3 d = origin - center;
    float a = direction.Dot(direction);
    float b = direction.Dot(d);
    float c = d.Dot(d) - radius * radius;
    float discriminant = b * b - c * a;
    if (discriminant < 0.0f)
        return false;
    double s  = sqrt(discriminant);
    float  t0 = (float)(-b - s);
    if (s - b < 0.0)
        return false;
    if (pDistance) {
        if (t0 <= 0.0f)
            *pDistance = 0.0f;
        else
            *pDistance = t0 / a;
    }
    return true;
}


