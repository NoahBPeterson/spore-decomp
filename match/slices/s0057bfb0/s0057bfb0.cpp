// slice s0057bfb0 — SP::cAppModeEditorBase helpers, typed-value XML writers, EASTL string bits.
#include "types.h"
#include <string.h>
#include <intrin.h>

// ---------------------------------------------------------------------------------------------
// EA allocator entry points (0x00F473A0 / 0x00F47380)
void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void  operator delete[](void* p);
inline void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{ return operator new[](size, pName, flags, debugFlags, file, line); }
inline void operator delete(void*, const char*, int, unsigned, const char*, int) {}

namespace eastl {

struct allocator {
    void* allocate(size_t n) { return operator new[](n, "Editor", 0, 0, 0, 0); }
    void deallocate(void* p) { operator delete[](p); }
};

extern wchar_t gEmptyString16[2];   // 0x01667BAC
extern char    gEmptyString8[1];

template <typename T> struct EmptyStr;
template <> struct EmptyStr<wchar_t> { static wchar_t* Get() { return gEmptyString16; } };
template <> struct EmptyStr<char>    { static char*    Get() { return (char*)gEmptyString16; } };

template <typename T>
inline size_t CharStrlen(const T* p) { const T* q = p; while (*q) ++q; return (size_t)(q - p); }
template <>
inline size_t CharStrlen<char>(const char* p) { return strlen(p); }

template <typename T>
inline T* CharStringUninitializedCopy(const T* pSource, const T* pEnd, T* pDest)
{
    memcpy(pDest, pSource, (size_t)(pEnd - pSource) * sizeof(T));
    return pDest + (pEnd - pSource);
}

template <typename T, typename Allocator = allocator>
class basic_string {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    Allocator mAllocator;

    basic_string() : mpBegin(EmptyStr<T>::Get()), mpEnd(EmptyStr<T>::Get()), mpCapacity(EmptyStr<T>::Get() + 1) {}
    basic_string(const basic_string& x);
    struct CtorDoNotInitialize {};
    basic_string(CtorDoNotInitialize, size_t n) : mpBegin(0), mpEnd(0), mpCapacity(0) { AllocateSelf(n + 1); *mpEnd = 0; }
    basic_string(const T* p) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(p); }
    ~basic_string() { DeallocateSelf(); }

    basic_string& operator=(const basic_string& x);

    bool empty() const { return mpBegin == mpEnd; }
    const T* c_str() const { return mpBegin; }
    T* data() { return mpBegin; }
    size_t size() const { return (size_t)(mpEnd - mpBegin); }

    void AllocateSelf(size_t n);
    void RangeInitialize(const T* pBegin, const T* pEnd)
    {
        const size_t n = (size_t)(pEnd - pBegin);
        AllocateSelf(n + 1);
        mpEnd = CharStringUninitializedCopy(pBegin, pEnd, mpBegin);
        *mpEnd = 0;
    }
    void RangeInitialize(const T* pBegin);
    void DeallocateSelf()
    {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin);
    }
    void DoFree(T* p) { if (p) mAllocator.deallocate(p); }
    basic_string& assign(const T* pBegin, const T* pEnd);
    basic_string& append(const T* pBegin, const T* pEnd);
    int sprintf(const char* fmt, ...);
};

typedef basic_string<char> string;
typedef basic_string<wchar_t> string16;

struct fixed_vector_allocator {
    allocator mOverflowAllocator;
    void* mpPoolBegin;
    void deallocate(void* p) { if (p != mpPoolBegin) mOverflowAllocator.deallocate(p); }
};

template <typename T, int nodeCount, bool bEnableOverflow = true>
class fixed_string : public basic_string<T, fixed_vector_allocator> {
public:
    ~fixed_string();
};

} // namespace eastl

// ---------------------------------------------------------------------------------------------
// 0x0057CB10: eastl::string copy constructor (out-of-line instance)
template <typename T, typename A>
eastl::basic_string<T, A>::basic_string(const basic_string<T, A>& x) : mpBegin(0), mpEnd(0), mpCapacity(0)
{
    RangeInitialize(x.mpBegin, x.mpEnd);
}
// @ 0x0057cb10 ??0?$basic_string@DU
template eastl::basic_string<char>::basic_string(const eastl::basic_string<char>&);

// @ 0x0057cb60
template <>
eastl::basic_string<wchar_t>& eastl::basic_string<wchar_t>::operator=(const basic_string<wchar_t>& x)
{
    if (&x != this)
        assign(x.mpBegin, x.mpEnd);
    return *this;
}

// @ 0x0057cc10
template <>
void eastl::basic_string<char>::RangeInitialize(const char* pBegin)
{
    RangeInitialize(pBegin, pBegin + CharStrlen(pBegin));
}

// @ 0x0057cba0  operator+(const string16&, const wchar_t*)
eastl::string16 operator+(const eastl::string16& a, const wchar_t* p)
{
    const size_t n = eastl::CharStrlen(p);
    eastl::string16::CtorDoNotInitialize cDNI;
    eastl::string16 result(cDNI, a.size() + n);
    result.append(a.mpBegin, a.mpEnd);
    result.append(p, p + n);
    return result;
}

// @ 0x0057cb80 ??1?$fixed_string
// eastl::fixed_string<wchar_t,16,1>::~fixed_string
template <>
eastl::fixed_string<wchar_t, 16, true>::~fixed_string()
{
}

// ---------------------------------------------------------------------------------------------
// EA runtime bits
namespace EA {
namespace Thread {
inline long AtomicFetchAdd(volatile long* p, long v) { return _InterlockedExchangeAdd(p, v); }
template <typename T>
struct AtomicInt {
    volatile long mValue;
    T GetValue() { return (T)AtomicFetchAdd(&mValue, 0); }
    void SetValue(T v) { _InterlockedExchange(&mValue, v); }
    T Increment() { return (T)AtomicFetchAdd(&mValue, 1) + 1; }
    T Decrement() { return (T)AtomicFetchAdd(&mValue, -1) - 1; }
};
}

template <typename T>
class AutoRefCount {
public:
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    AutoRefCount& operator=(T* p)
    {
        if (p != mpObject) {
            T* const pTemp = mpObject;
            if (p) p->AddRef();
            mpObject = p;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
    AutoRefCount& operator=(const AutoRefCount& x) { return operator=(x.mpObject); }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};

// Instances whose copy-ctor / assignment were emitted out of line (0x005725D0 / 0x005766E0).
template <typename T>
class AutoRefCountX {
public:
    T* mpObject;
    AutoRefCountX(const AutoRefCountX& x);
    ~AutoRefCountX() { if (mpObject) mpObject->Release(); }
    AutoRefCountX& operator=(const AutoRefCountX& x);
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};

namespace ResourceMan {
struct Key {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
};
}

namespace Messaging {
// Plain message payload (no constructor): used directly for stack messages.
template <int N>
class MessageData {
public:
    union Data {
        uint32_t mUint32;
        int32_t  mInt32;
        float    mFloat;
        uint64_t mUint64;
    };
    Data mData[N];
    uint32_t mId;
};

template <int N>
class MessageBasic : public MessageData<N> {
public:
    MessageBasic() { this->mId = 0; }
};

class IMessageRC {
public:
    virtual int AddRef() = 0;
    virtual int Release() = 0;
};

class MessageRC : public IMessageRC {
public:
    Thread::AtomicInt<int> mRefCount;
    MessageRC() { mRefCount.SetValue(0); }
    virtual int AddRef();
    virtual int Release();
};

template <int N>
class MessageBasicRC : public MessageBasic<N>, public MessageRC {
public:
};

class IMessageServer {
public:
    virtual void _v0(); virtual void _v1(); virtual void _v2(); virtual void _v3(); virtual void _v4();
    virtual bool MessageSend(uint32_t id, void* pMessage, int flags);
};
} // namespace Messaging
} // namespace EA

namespace UI {
// vtable 0x013EB844; destructor 0x00421CF0
class BehaviorMessage : public EA::Messaging::MessageBasicRC<5> {
public:
    uint32_t mFlags;   // +0x38
    BehaviorMessage(uint32_t id) : mFlags(0)
    {
        mId = id;
        mData[0].mUint32 = 0;
        mData[1].mUint32 = 0xFFFFFFFF;
        mData[2].mUint32 = 0;
    }
    ~BehaviorMessage();
};
}

namespace SP {
EA::Messaging::IMessageServer* MessageServer();

struct Property {
    char pad_0[0x12];
    short mType;           // +0x12
    int* GetInt();         // 0x0041E990
};

class cPropertyList {
public:
    virtual void _v0(); virtual void _v1(); virtual void _v2(); virtual void _v3(); virtual void _v4();
    virtual void _v5(); virtual void _v6(); virtual void _v7(); virtual void _v8();
    virtual bool GetProperty(uint32_t propertyID, Property*& result);
};

class cSPEditorBlock {
public:
    virtual void _v0();
    virtual int AddRef();
    virtual int Release();
};

class cBlockTray {   // +0x434 of the editor
public:
    virtual void _v0();
    virtual int GetCount(int tray);
    virtual void _v2(); virtual void _v3(); virtual void _v4(); virtual void _v5(); virtual void _v6(); virtual void _v7(); virtual void _v8();
    virtual void SetCount(int tray, int count);
    virtual void _v10(); virtual void _v11();
    virtual void AddBlock(cSPEditorBlock* block);
};

class cSPEditorUI {
public:
    void SetMode(int mode);                                    // 0x005DDA30
    void SetSelected(uint32_t controlID, bool a, bool b);      // 0x005DCF20
    void ShowPaintThemeExport();                               // 0x005DD4A0
};

class cRefObject {
public:
    virtual int AddRef();
    virtual int Release();
};

class cEditorConfigData {
public:
    virtual void _v0();
    virtual int AddRef();
    virtual int Release();
};

namespace Editor {
struct cEditorLaunchData {
    virtual void _v0();
    virtual int AddRef();
    virtual int Release();
    char pad_4[0x8];
    int mConfig;                          // +0xc
    EA::ResourceMan::Key mModelKey;       // +0x10
    char pad_1c[0x65 - 0x1c];
    bool m65;                             // +0x65
    char pad_66[0x6e - 0x66];
    bool m6e;                             // +0x6e
    char pad_6f[0x90 - 0x6f];
    uint32_t m90;                         // +0x90
    cRefObject* m94;                      // +0x94
    EA::AutoRefCountX<cEditorLaunchData> mParent;   // +0x98
};
}

class cEditorLaunchState {   // 0x48 bytes, ctor 0x00579C80
public:
    virtual void _v0();
    virtual int AddRef();
    virtual int Release();
    char pad_4[0x8];
    uint32_t m0c;                         // +0xc
    EA::AutoRefCount<cRefObject> m10;     // +0x10
    uint32_t m14;                         // +0x14
    EA::ResourceMan::Key mKey;            // +0x18
    char pad_24[0x44 - 0x24];
    bool mbActive;                        // +0x44
    bool m45;                             // +0x45
    char pad_46[2];
    cEditorLaunchState();
};

struct cSPEditorModel {
    char pad_0[0x18];
    char mBlocks[0x58 - 0x18];            // +0x18
    uint32_t m58;                         // +0x58
    const wchar_t* GetFilePath();         // 0x004AE000
};

struct cSkinMeshData { char pad_0[8]; char* mpBegin; char* mpEnd; };   // 12-byte elements
struct cSPEditorSkin {
    char pad_0[0x34];
    cSkinMeshData* mpMesh;                // +0x34
    char pad_38[0x7c - 0x38];
    char* mVertsBegin;                    // +0x7c (20-byte elements)
    char* mVertsEnd;                      // +0x80
    void Rebuild0();                      // 0x004CA6E0
    void Rebuild1();                      // 0x004CB340
    void Rebuild2();                      // 0x004CB820
};

struct UpdateFlags { bool a; bool b; int c; UpdateFlags() : a(false), b(false), c(0) {} };

class cSPEditorSkinManager {
public:
    cSPEditorSkin* GetSkin(bool create);  // 0x004C49E0
    bool HasPaintData();                  // 0x004C4630
    void ApplyPaintTheme(const wchar_t* path, const wchar_t* dir);   // 0x004C5980
    void Update(int a, int b, UpdateFlags flags);                    // 0x004C38E0
};

struct cPaintThemeSource { void GetPath(uint32_t id, eastl::string16* out); };   // 0x005F9230
cPaintThemeSource* GetPaintThemeSource();                                        // 0x005F7930

namespace EditorUtils { bool ExportToXMFAndBlocks(cSPEditorModel* model, cSPEditorSkin* skin, const wchar_t* path); }

struct cBakeManager { void Bake(uint32_t themeID); };   // 0x004B2BB0

struct cTrayRow { bool* mpStates; char pad_4[0x10]; };   // 0x14 bytes

class cAppModeEditorBase {
public:
    struct cSPEditorLocalState {
        char pad_0[8];
        int mBudget;                       // +0x8
        int mState;                        // +0xc
        uint32_t mThemeID;                 // +0x10
        bool mIsPainted;                   // +0x14
        bool mIsModelDirty;                // +0x15
        EA::ResourceMan::Key mPaintLikeThisKey;   // +0x18
        uint32_t mPaintLikeThisGroupId;    // +0x24
        uint32_t mPaintLikeThisItemId;     // +0x28
    };
    char pad_0[0x24];
    cPropertyList* mpPropList;  // +0x24
    char pad_28[0x50];
    cSPEditorUI* mDevUI;  // +0x78
    char pad_7c[0x1c];
    cSPEditorModel* mEditorSaveModel;  // +0x98
    char pad_9c[0xb4];
    cSPEditorSkinManager* mSaveLoadFactory;  // +0x150
    char pad_154[0x44];
    int mTransitionState;  // +0x198
    char pad_19c[0x4];
    int m1a0;  // +0x1a0
    int m1a4;  // +0x1a4
    int mPendingLaunch;  // +0x1a8
    char pad_1ac[0x20];
    EA::AutoRefCountX<Editor::cEditorLaunchData> mLaunchData;  // +0x1cc
    char pad_1d0[0xd0];
    cBakeManager* mpBakeManager;  // +0x2a0
    char pad_2a4[0x4d];
    bool m2f1;  // +0x2f1
    char pad_2f2[0x4];
    bool m2f6;  // +0x2f6
    char pad_2f7[0x13d];
    cBlockTray* mpBlockTray;  // +0x434
    char pad_438[0x7a];
    bool mIsPainted;  // +0x4b2
    bool mIsModelDirty;  // +0x4b3
    char pad_4b4[0x8];
    EA::AutoRefCount<cEditorLaunchState> mLaunchState;  // +0x4bc
    char pad_4c0[0x18];
    bool* mpTrayStates;  // +0x4d8
    char pad_4dc[0x2c];
    cTrayRow mTrayRows[6];  // +0x508
    bool mTrayActive[6];  // +0x580

    void RefreshBlockTray();                                     // 0x0057BFB0
    void ProcessPendingLaunch();                                 // 0x0057C0E0
    void CreateLaunchState();                                    // 0x0057C1E0
    void SetLocalState(cSPEditorLocalState* state);              // 0x0057C2F0
    void SetTrayState(int index, bool value);                    // 0x0057C530
    bool ExportPaintTheme(bool showDialog);                      // 0x0057C590
    bool IsBlockAllowed(cSPEditorBlock* block);                  // 0x00577C40
    void SetCurrentConfig(int config, EA::ResourceMan::Key key); // 0x00579720
    void RelaunchFrom(cEditorLaunchState* state);                // 0x0057A710
    int GetCurrentTrayRow();                                     // 0x00576140
};

struct sp_vector_allocator {
    const char* mpName;
    int mFlags;
    void deallocate(void* p) { if (((int*)p)[-1] != 0) operator delete[](p); }
};

template <typename T>
inline void destruct(T* first, T* last)
{
    for (; first < last; ++first)
        first->~T();
}

template <typename T>
class sp_vector {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator mAllocator;
    sp_vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~sp_vector()
    {
        destruct(mpBegin, mpEnd);
        if (mpBegin)
            mAllocator.deallocate(mpBegin);
    }
    size_t size() const { return (size_t)(mpEnd - mpBegin); }
    T& operator[](size_t i) { return mpBegin[i]; }
};

void GetEditorBlocks(void* blockList, sp_vector<EA::AutoRefCount<cSPEditorBlock> >& out);   // 0x00491900

// @ 0x0057bfb0
void cAppModeEditorBase::RefreshBlockTray()
{
    sp_vector<EA::AutoRefCount<cSPEditorBlock> > blocks;
    GetEditorBlocks(mEditorSaveModel->mBlocks, blocks);

    int maxCount = 0;
    cPropertyList* propList = mpPropList;
    Property* prop;
    if (propList && propList->GetProperty(0x0664EA09, prop) && prop->mType == 9)
        maxCount = *prop->GetInt();

    size_t count = blocks.size();
    for (size_t i = 0; i < count; ++i) {
        EA::AutoRefCount<cSPEditorBlock> block = blocks[i];
        if (!m2f6 || IsBlockAllowed(block))
            mpBlockTray->AddBlock(block);
    }

    if (mpBlockTray->GetCount(0) < maxCount)
        mpBlockTray->SetCount(0, maxCount);
}

// @ 0x0057c0e0
void cAppModeEditorBase::ProcessPendingLaunch()
{
    if (mPendingLaunch != 1 || m1a0 != 0 || m1a4 != 0 || mTransitionState != 0 || !mLaunchState)
        return;

    if (!mLaunchState->mbActive && mLaunchData && mLaunchData->mParent) {
        EA::AutoRefCountX<Editor::cEditorLaunchData> parent(mLaunchData->mParent);
        mLaunchData = parent;
        if (mLaunchData->mModelKey.instanceID == 0)
            mLaunchData->mModelKey = mLaunchState->mKey;
        SetCurrentConfig(mLaunchData->mConfig, mLaunchData->mModelKey);
    } else {
        RelaunchFrom(mLaunchState);
    }
    mPendingLaunch = 0;
}

// @ 0x0057c1e0
void cAppModeEditorBase::CreateLaunchState()
{
    if (mLaunchData) {
        mLaunchState = new ("Editor", 0, 0, 0, 0) cEditorLaunchState();
        mLaunchState->m0c = mLaunchData->m90;
        mLaunchState->m10 = mLaunchData->m94;
        mLaunchState->mKey = mLaunchData->mModelKey;
        mLaunchState->m14 = mEditorSaveModel->m58;
        mLaunchState->mbActive = true;
        mLaunchState->m45 = mLaunchData->m65;
    }
}

// @ 0x0057c440 ?SendEditorStateChanged
__forceinline void SendEditorStateChanged()
{
    UI::BehaviorMessage msg(0x05090434);
    MessageServer()->MessageSend(msg.mId, &msg, 0);
}

// @ 0x0057c2f0
void cAppModeEditorBase::SetLocalState(cSPEditorLocalState* state)
{
    EA::Messaging::MessageData<6> msg;
    if (!state)
        return;

    mpBlockTray->SetCount(0, state->mBudget);
    if (mDevUI) {
        mDevUI->SetMode(state->mState);
        switch (state->mState) {
        case 0: mDevUI->SetSelected(0xF019C2E7, true, true); break;
        case 1: mDevUI->SetSelected(0xF019C2F3, true, true); break;
        case 2: mDevUI->SetSelected(0x70218642, true, true); break;
        }
    }
    if (mpBakeManager && !m2f1 && state->mThemeID)
        mpBakeManager->Bake(state->mThemeID);

    mIsPainted = state->mIsPainted;
    mIsModelDirty = state->mIsModelDirty;

    if (state->mPaintLikeThisKey.instanceID) {
        msg.mId = 0;
        msg.mData[0].mUint32 = state->mPaintLikeThisKey.groupID;
        msg.mData[1].mUint32 = state->mPaintLikeThisKey.instanceID;
        msg.mData[2].mUint32 = state->mPaintLikeThisKey.typeID;
        msg.mData[3].mUint32 = state->mPaintLikeThisGroupId;
        msg.mData[4].mUint32 = state->mPaintLikeThisItemId;
        MessageServer()->MessageSend(0x057A4BC9, &msg, 0);
    }
    SendEditorStateChanged();
}

// @ 0x0057c530
void cAppModeEditorBase::SetTrayState(int index, bool value)
{
    mpTrayStates[index] = value;
    int row = GetCurrentTrayRow();
    if (row < 6 && mLaunchData && mLaunchData->m6e) {
        if (index == 6)
            mTrayActive[row] = mTrayRows[row].mpStates[6];
        mTrayRows[row].mpStates[index] = value;
    }
}

}  // namespace SP
namespace EA { namespace IO { int SplitPath(const wchar_t* path, wchar_t* drive, wchar_t* dir, wchar_t* fname, wchar_t* ext, int flags); } }
namespace SP {

// NM 0x0057c590: skin->mpMesh is reloaded instead of kept in eax; model pointer lands in ecx instead of edi
// @ 0x0057c590
bool cAppModeEditorBase::ExportPaintTheme(bool showDialog)
{
    if (showDialog) {
        if (mDevUI)
            mDevUI->ShowPaintThemeExport();
        return true;
    }

    cSPEditorSkin* skin = mSaveLoadFactory ? mSaveLoadFactory->GetSkin(true) : 0;
    if (!mEditorSaveModel || !skin)
        return false;

    eastl::string16 path;
    cPaintThemeSource* source = GetPaintThemeSource();
    if (source) {
        source->GetPath(0x2B978C46, &path);
        if (path.empty())
            return false;

        wchar_t fileName[260];
        EA::IO::SplitPath(mEditorSaveModel->GetFilePath(), 0, 0, fileName, 0, 4);
        const wchar_t* pathStr = path.c_str();

        bool sameTopology;
        if (skin->mpMesh &&
            (int)(skin->mVertsEnd - skin->mVertsBegin) / 20 == (int)(skin->mpMesh->mpEnd - skin->mpMesh->mpBegin) / 12)
            sameTopology = true;
        else
            sameTopology = false;

        if (mSaveLoadFactory->HasPaintData() && sameTopology) {
            mSaveLoadFactory->ApplyPaintTheme(pathStr, fileName);
        } else {
            mSaveLoadFactory->Update(0, 1, UpdateFlags());
            skin->Rebuild0();
            skin->Rebuild1();
            skin->Rebuild2();
        }

        return EditorUtils::ExportToXMFAndBlocks(mEditorSaveModel, mSaveLoadFactory ? mSaveLoadFactory->GetSkin(true) : 0, pathStr);
    }
    return false;
}

} // namespace SP

// ---------------------------------------------------------------------------------------------
namespace SP {

// Ref-counted base with vtable 0x013EF094 (shared by many editor classes).
class cRefCountedBase {
public:
    virtual ~cRefCountedBase() {}
};
class __declspec(novtable) IRefCounted {
public:
    virtual ~IRefCounted() {}
    EA::Thread::AtomicInt<int> mRefCount;    // +0x8 in derived objects
};

// Intrusively counted payload whose count lives at +8.
struct cSharedPayload {
    char pad_0[8];
    EA::Thread::AtomicInt<int> mRefCount;   // +0x8
    void Destroy() {}
    int Release()
    {
        mRefCount.Decrement();
        if (mRefCount.GetValue() < 1) {
            mRefCount.Increment();
            Destroy();
            return 0;
        }
        return mRefCount.GetValue();
    }
};

template <typename T>
struct IntrusivePtr {
    T* mpObject;
    ~IntrusivePtr() { if (mpObject) mpObject->Release(); }
};

class cPaletteCategory {
public:
    cRefCountedBase mBase;                   // +0x0 (embedded, vtable 0x013EF094)
    char pad_4[0x10];
    IntrusivePtr<cSharedPayload> mpShared;   // +0x14
    char pad_18[0x10];
    sp_vector<char> mItems;                  // +0x28
    ~cPaletteCategory();
};

// NM 0x0057c4b0: atomic ops reuse one pointer register (original copies eax per op); extra epilogue
// @ 0x0057c4b0 ??1cPaletteCategory
cPaletteCategory::~cPaletteCategory()
{
}

template <typename T>
class sp_byte_vector : public sp_vector<T> {
public:
    void reserve(size_t n);
};

// @ 0x0057cc60 ?reserve@
template <>
void sp_byte_vector<char>::reserve(size_t n)
{
    if (n > (size_t)(mpCapacity - mpBegin)) {
        char* const pNewData = n ? (char*)operator new[](n, "Editor", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
        memcpy(pNewData, mpBegin, (size_t)(mpEnd - mpBegin));
        if (mpBegin)
            mAllocator.deallocate(mpBegin);
        const ptrdiff_t nPrevSize = mpEnd - mpBegin;
        mpBegin = pNewData;
        mpEnd = pNewData + nPrevSize;
        mpCapacity = pNewData + n;
    }
}

// Interface at +0 of editor resources.
class __declspec(novtable) IEditorResource {
public:
    virtual int AddRef() = 0;
    virtual int Release() = 0;
};

// vtables 0x013EB938 / 0x013EF094
struct cResourceName {
    eastl::string16 mName;                   // +0xc in cEditorResource
    cResourceName(const wchar_t* name) : mName(name) {}
};

class cEditorResource : public cResourceName, public IEditorResource, public IRefCounted {
public:
    cEditorResource(const wchar_t* name) : cResourceName(name) { mRefCount.SetValue(0); }
    virtual ~cEditorResource() {}
};

// vtables 0x013F5884 / 0x013F5880, 0x1C bytes
class cEditorNamedResource : public cEditorResource {
public:
    cEditorNamedResource(const wchar_t* name) : cEditorResource(name) {}
    virtual int AddRef();
    virtual int Release();
    virtual ~cEditorNamedResource();
};

// NM 0x0057ccf0: base vptr stores emitted in order +0,+4 (original +4,+0)
// @ 0x0057ccf0 ??_GcEditorNamedResource
cEditorNamedResource::~cEditorNamedResource()
{
}

struct cResourceSlot {
    cEditorResource* mpResource;
    uint32_t mExtra;
};

struct cResourceTable {
    char pad_0[8];
    cResourceSlot mSlots[6];     // +0x8
    uint32_t mValidMask;         // +0x38
    void SetResource(int index, const wchar_t* name);
};

// @ 0x0057cd40 ?SetResourceName
void SetResourceName(cResourceTable* table, int index, const wchar_t* name)
{
    cEditorNamedResource* res = new ("App", 0, 0, 0, 0) cEditorNamedResource(name);
    if ((table->mValidMask & (1u << index)) && table->mSlots[index].mpResource)
        table->mSlots[index].mpResource->Release();
    table->mSlots[index].mpResource = res;
    if (res)
        res->AddRef();
    table->mValidMask |= (1u << index);
}

// vtables 0x013EB918 / 0x013EF094
class cLocaleChangeMessageBase : public IEditorResource, public IRefCounted {
public:
    virtual ~cLocaleChangeMessageBase() {}
};

class cLocaleChangeMessage : public cLocaleChangeMessageBase {
public:
    char pad_8[0x8];
    EA::AutoRefCount<cRefObject> mpTarget;        // +0x10 (released through slot 1)
    char pad_14[0x10];
    eastl::string16 mText;                        // +0x24
    virtual ~cLocaleChangeMessage();
};

// NM 0x0057ce20: original omits the entry vptr stores (only base vptrs restored at the end)
// @ 0x0057ce20 ??_GcLocaleChangeMessage@
cLocaleChangeMessage::~cLocaleChangeMessage()
{
}

} // namespace SP

// ---------------------------------------------------------------------------------------------
// Typed value -> XML element writers
namespace EA {
eastl::string16 ConvertToString16(const char* p, int length = -1);   // 0x0093C5A0
eastl::string16 ConvertToString16(const eastl::string& s);           // 0x0093C6D0
}

namespace SP {

class IXmlWriter {
public:
    virtual bool BeginElement(const wchar_t* name) = 0;
    virtual bool EndElement(const wchar_t* name) = 0;
    virtual bool WriteAttribute(const wchar_t* name, const wchar_t* value) = 0;
    virtual bool WriteCharacters(const wchar_t* text) = 0;
};

template <typename T>
struct cTypedValueToStringT {
    static bool sbWriteType;
    static void Write(eastl::string& out, const T& value);
};

template <typename T>
bool WriteTypedValue(IXmlWriter* writer, const char* name, const T& value, const wchar_t* typeName)
{
    bool result = true;
    eastl::string str;
    cTypedValueToStringT<T>::Write(str, value);
    if (!str.empty()) {
        eastl::string16 name16(name ? EA::ConvertToString16(name) : eastl::string16());
        eastl::string16 text(EA::ConvertToString16(str));
        const wchar_t* element = name16.empty() ? typeName : name16.c_str();
        if (writer->BeginElement(element) &&
            (name16.empty() || !cTypedValueToStringT<T>::sbWriteType || writer->WriteAttribute(L"type", typeName)) &&
            writer->WriteCharacters(text.c_str()) &&
            writer->EndElement(element))
            result = true;
        else
            result = false;
    }
    return result;
}

// NM 0x0057c770: element/attribute short-circuit chain and stack slots of the string temporaries differ
// @ 0x0057c770 ??$WriteTypedValue@_K
template bool WriteTypedValue<unsigned __int64>(IXmlWriter*, const char*, const unsigned __int64&, const wchar_t*);
// NM 0x0057c940: element/attribute short-circuit chain and stack slots of the string temporaries differ
// @ 0x0057c940 ??$WriteTypedValue@M
template bool WriteTypedValue<float>(IXmlWriter*, const char*, const float&, const wchar_t*);

} // namespace SP
