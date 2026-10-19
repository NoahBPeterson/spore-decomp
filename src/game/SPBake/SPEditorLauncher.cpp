// src/game/SPBake/SPEditorLauncher.cpp -- migrated from slice(s) s005a8d20, s00432f10 by tools/migrate/rewrite.py
// Object file: SPBake/SPEditorLauncher.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <math.h>

// ---- items of slice s00432f10 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Settings { uint32_t pad[15]; int* flags; bool Has(int i) { return flags[i] != 0; } };
extern Settings* g_settings;           // 0x015fd918
// ---- items of slice s00432f10 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern Settings* g_settings;           // 0x015fd918

// ---- items of slice s005a8d20 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" long __cdecl _InterlockedExchange(long volatile* target, long value);
#pragma intrinsic(_InterlockedExchange)
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void  operator delete[](void* p);  // 0x00f47380
inline void* operator new(size_t, void* p) { return p; }
struct ResourceKey {
    uint32_t instanceID;   // +0x0
    uint32_t typeID;       // +0x4
    uint32_t groupID;      // +0x8
    ResourceKey() : instanceID(0), typeID(0), groupID(0) {}
};
struct Quaternion { float x, y, z, w; };
struct Matrix3 {
    float m[9];
    Matrix3& SetRotation(const Quaternion& q);   // 0x0041CB40
};
Matrix3 operator*(const Matrix3& a, const Matrix3& b);   // 0x0041DE20
namespace EA {
template <typename T>
class RefCountTemplate_s005a_8d20 {
public:
    RefCountTemplate_s005a_8d20() : mnRefCount(0) {}
    virtual ~RefCountTemplate_s005a_8d20() {}
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
}
namespace EA {
template <typename T>
class AutoRefCount_s005a_8d20 {
public:
    T* mpObject;
    AutoRefCount_s005a_8d20() : mpObject(0) {}
    AutoRefCount_s005a_8d20(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    AutoRefCount_s005a_8d20(const AutoRefCount_s005a_8d20& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount_s005a_8d20() { if (mpObject) mpObject->Release(); }
    AutoRefCount_s005a_8d20& operator=(T* pObject)
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
}
namespace EA {
namespace COM {
class IUnknown32_s005a_8d20 {
public:
    virtual int AddRef() = 0;
    virtual int Release() = 0;
};
}
}
namespace EA {
namespace Messaging {
class IMessageRC_s005a_8d20 {
public:
    virtual ~IMessageRC_s005a_8d20() {}
    virtual int AddRef() = 0;
    virtual int Release() = 0;
};
}
}
namespace eastl {
struct allocator_s005a_8d20 {};
}
namespace eastl {
struct sp_vector_allocator_s005a_8d20 {
    uint32_t mData[2];
    sp_vector_allocator_s005a_8d20() {}
    void deallocate(void* p, size_t)
    {
        if (((uint32_t*)p)[-1])
            operator delete[](p);
    }
};
}
namespace eastl {
struct true_type {};
}
namespace eastl {
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
}
namespace eastl {
template <typename T>
class basic_string_s005a_8d20 {
public:
    T*        mpBegin;
    T*        mpEnd;
    T*        mpCapacity;
    allocator_s005a_8d20 mAllocator;
    basic_string_s005a_8d20();
    ~basic_string_s005a_8d20()
    {
        if ((mpCapacity - mpBegin) > 1 && mpBegin)
            operator delete[](mpBegin);
    }
};
}
namespace eastl {
extern wchar_t gEmptyString16[2];   // 0x01667BAC
}
namespace eastl {
template <> inline basic_string_s005a_8d20<wchar_t>::basic_string_s005a_8d20()
    : mpBegin(gEmptyString16), mpEnd(gEmptyString16), mpCapacity(gEmptyString16 + 1)
{
}
}
namespace eastl {
template <typename T>
struct copy_result {
    T* mpResult;
    copy_result() {}
};
}
namespace eastl {
template <typename T, typename Tag>
copy_result<T> uninitialized_copy_impl(const T* first, const T* last, T* dest, Tag);   // 0x004E8EE0 (AutoRefCount instance)
}
namespace eastl {
struct false_type { false_type() {} };
}
namespace eastl {
template <typename T>
inline T* uninitialized_copy_ptr(const T* first, const T* last, T* result)
{
    const copy_result<T> r = uninitialized_copy_impl(first, last, result, false_type());
    return r.mpResult;
}
}
namespace eastl {
template <typename T>
struct VectorBase_s005a_8d20 {
    T*                  mpBegin;      // +0x0
    T*                  mpEnd;        // +0x4
    T*                  mpCapacity;   // +0x8
    sp_vector_allocator_s005a_8d20 mAllocator;   // +0xc
    VectorBase_s005a_8d20() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    VectorBase_s005a_8d20(size_t n, const sp_vector_allocator_s005a_8d20& allocator_s005a_8d20);   // 0x0066AEC0 (folded)
    ~VectorBase_s005a_8d20()
    {
        if (mpBegin)
            mAllocator.deallocate(mpBegin, (char*)mpCapacity - (char*)mpBegin);
    }
};
}
namespace eastl {
template <typename T>
class vector_s005a_8d20 : public VectorBase_s005a_8d20<T> {
public:
    vector_s005a_8d20() {}
    vector_s005a_8d20(const vector_s005a_8d20& x) : VectorBase_s005a_8d20<T>((size_t)(x.mpEnd - x.mpBegin), x.mAllocator)
    {
        this->mpEnd = uninitialized_copy_ptr(x.mpBegin, x.mpEnd, this->mpBegin);
    }
    ~vector_s005a_8d20() { DoDestroyValues(this->mpBegin, this->mpEnd); }
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
            DoInsertValue(this->mpEnd, value);  // 0x00621fc0 (eastl::vector::DoInsertValue)
    }
};
}
namespace eastl {
template <typename T1, typename T2>
struct pair_s005a_8d20 {
    T1 first;
    T2 second;
    __forceinline pair_s005a_8d20(const T1& a, const T2& b) : first(a), second(b) {}
};
}
namespace eastl {
struct rbtree_node_base_s005a_8d20 {
    rbtree_node_base_s005a_8d20* mpNodeRight;
    rbtree_node_base_s005a_8d20* mpNodeLeft;
    rbtree_node_base_s005a_8d20* mpNodeParent;
    char              mColor;
};
}
namespace eastl {
template <typename T>
struct rbtree_node_s005a_8d20 : public rbtree_node_base_s005a_8d20 {
    T mValue;   // +0x10
};
}
namespace eastl {
template <typename T>
struct rbtree_iterator_s005a_8d20 {
    typedef rbtree_node_s005a_8d20<T> node_type;
    node_type* mpNode;
    rbtree_iterator_s005a_8d20() : mpNode(0) {}
    explicit rbtree_iterator_s005a_8d20(const node_type* pNode) : mpNode((node_type*)pNode) {}
    rbtree_iterator_s005a_8d20(const rbtree_iterator_s005a_8d20& x) : mpNode(x.mpNode) {}
    T* operator->() const { return &mpNode->mValue; }
    bool operator==(const rbtree_iterator_s005a_8d20& x) const { return mpNode == x.mpNode; }
    bool operator!=(const rbtree_iterator_s005a_8d20& x) const { return mpNode != x.mpNode; }
};
}
namespace eastl {
template <typename T>
struct less_s005a_8d20 { bool operator()(const T& a, const T& b) const { return a < b; } };
}
namespace eastl {
template <typename Key, typename T>
class map_s005a_8d20 {
public:
    typedef pair_s005a_8d20<const Key, T>          value_type;
    typedef rbtree_node_s005a_8d20<value_type>     node_type;
    typedef rbtree_iterator_s005a_8d20<value_type> iterator;

    less_s005a_8d20<Key>        mCompare;
    rbtree_node_base_s005a_8d20 mAnchor;
    uint32_t         mnSize;
    allocator_s005a_8d20        mAllocator;

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
        rbtree_node_base_s005a_8d20* pRangeEnd = &mAnchor;
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
}
namespace SP {
class cPropertyList_s005a_8d20 {
public:
    virtual int AddRef();
    virtual int Release();
};
}
typedef eastl::vector_s005a_8d20<EA::AutoRefCount_s005a_8d20<SP::cPropertyList_s005a_8d20> > PropertyListVector;
typedef eastl::map_s005a_8d20<uint32_t, PropertyListVector> EditorPropListMap;
namespace SP {
namespace Editor {
class cAppMode {
public:
    virtual void Unk0(); virtual void Unk1(); virtual void Unk2(); virtual void Unk3();
    virtual void Unk4(); virtual void Unk5(); virtual void Unk6(); virtual void Unk7();
    virtual void Unk8(); virtual void Unk9(); virtual void Unk10(); virtual void Unk11();
    virtual void Unk12(); virtual void Unk13();
    virtual uint32_t GetModeID();   // slot 14
};
}
}
namespace SP {
namespace Editor {
cAppMode* App();   // 0x0067DD10
}
}
namespace SP {
namespace Editor {
class cEditorLaunchData_s005a_8d20 : public EA::Messaging::IMessageRC_s005a_8d20, public EA::RefCountTemplate_s005a_8d20<int> {
public:
    cEditorLaunchData_s005a_8d20();
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
    eastl::basic_string_s005a_8d20<wchar_t> mAlternateName;           // +0x40
    eastl::basic_string_s005a_8d20<wchar_t> mAlternateDescription;    // +0x50
    float                        mf60;                     // +0x60
    bool                         mb64;                     // +0x64
    bool                         mb65;                     // +0x65
    bool                         mb66;                     // +0x66
    uint32_t                     m68;                      // +0x68
    bool                         mb6c;                     // +0x6c
    bool                         mb6d;                     // +0x6d
    bool                         mb6e;                     // +0x6e
    bool                         mb6f;                     // +0x6f
    eastl::vector_s005a_8d20<uint32_t>      mList;                    // +0x70
    uint32_t                     m84;                      // +0x84
    uint32_t                     m88;                      // +0x88
    uint32_t                     m8c;                      // +0x8c
    uint32_t                     mCallerID;                // +0x90
    EA::AutoRefCount_s005a_8d20<EA::COM::IUnknown32_s005a_8d20> mCallerData;     // +0x94
    EA::AutoRefCount_s005a_8d20<EA::Messaging::IMessageRC_s005a_8d20> mpReturnMessage;   // +0x98
};
}
}
namespace SP {
namespace Editor {
extern eastl::bitset<128> kDefaultValidationLevel;   // 0x015DA7C4
}
}
namespace SP {
namespace Editor {
bool Launch(cEditorLaunchData_s005a_8d20* pData);
}
}
namespace SP {
namespace Editor {
bool Launch(uint32_t config, const ResourceKey& modelKey, uint32_t callerID,
            EA::COM::IUnknown32_s005a_8d20* pCallerData, eastl::bitset<128> validationLevel, bool canSwitchEditor);
}
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
template class eastl::map_s005a_8d20<uint32_t, PropertyListVector>;
// ---- items of slice s005a8d20 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
uint32_t GetEditorConfigForModel(const ResourceKey* key);  // 0x005a8f80 (stays in the slice: not this object's)

// @ 0x00432f10
int RemapTypeId(int id)
{
    switch (id) {
    case 0xdfad9f51: return 0x1d2ec0a4;
    case 0x9ea3031a: {
        Settings* s = g_settings;
        if (s->Has(0x46)) return 0x5bf8f774;
        else return 0x465c50ba;
    }
    case 0x372e2c04: return 0x156276d1;
    case 0xccc35c46: return 0x9adf00a9;
    case 0x65672ade: return 0x37e82da1;
    case 0x4178b8e8: return 0xa56567f7;
    case 0x99e92f05: return 0x99e92f05;
    case 0x4e3f7777: return 0x4e3f7777;
    case 0xbdd15f3d: return 0xbdd15f3d;
    case 0x47c10953: return 0x8707be7d;
    case 0x72c49181: return 0x72c49181;
    case 0x7d433fad: return 0x7d433fad;
    case 0x8f963dcb: return 0x8f963dcb;
    case 0x441cd3e6: return 0x441cd3e6;
    case 0xf670aa43: return 0xf670aa43;
    case 0x2a5147a9: return 0x2a5147a9;
    case 0x1a4e0708: return 0x1a4e0708;
    case 0x9ad7d4aa: return 0x9ad7d4aa;
    case 0x1f2a25b6: return 0x1f2a25b6;
    case 0x449c040f: return 0x449c040f;
    case 0xbc1041e6: return 0xbc1041e6;
    case 0xc15695da: return 0xc15695da;
    case 0x2090a11b: return 0x2090a11b;
    case 0xc0b74287: return 0xc0b74287;
    case 0x98e03c0d: return 0x96b24187;
    case 0xbcd73e89: return 0x1c7eca95;
    case 0xb8669ec9: return 0x1c7eca95;
    case 0x37148141: return 0x1c7eca95;
    }
    return -1;
}

// @ 0x005a9200
bool SP::Editor::Launch(SP::Editor::cEditorLaunchData_s005a_8d20* pData)
{
    pData->mCallingAppModeID = SP::Editor::App()->GetModeID();
    if (pData->mEditorValidationLevel.none())
        pData->mEditorValidationLevel = SP::Editor::kDefaultValidationLevel;
    if (pData->mConfig == (uint32_t)-1)
        pData->mConfig = GetEditorConfigForModel(&pData->mModelKey);

    cMessageServer* server = MessageServer();
    server->PostMessage(0xb03bc30c, pData, 0, 0);

    EA::AutoRefCount_s005a_8d20<cEditorLaunchMessage> msg(new ("App", 0, 0, 0, 0) cEditorLaunchMessage());
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
bool SP::Editor::Launch(uint32_t config, const ResourceKey& modelKey, uint32_t callerID, EA::COM::IUnknown32_s005a_8d20* pCallerData, eastl::bitset<128> validationLevel, bool canSwitchEditor)
{
    EA::AutoRefCount_s005a_8d20<SP::Editor::cEditorLaunchData_s005a_8d20> data(new ("App", 0, 0, 0, 0) SP::Editor::cEditorLaunchData_s005a_8d20());
    data->mCallingAppModeID = SP::Editor::App()->GetModeID();
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
        data->mEditorValidationLevel = SP::Editor::kDefaultValidationLevel;
    else
        data->mEditorValidationLevel = validationLevel;
    return SP::Editor::Launch(data);
}

// @ 0x005a9610
void CopyConstructEditorPropListEntry(void* p, const EditorPropListMap::value_type& x)
{
    new (p) EditorPropListMap::value_type(x);
}
