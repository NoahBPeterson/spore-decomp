// Slice s00447150: the single function in this slice is
//   SP::cSPEditorBlock::InitializeHandleData   (0x00447150, 4653 bytes, thiscall, ret 4)
//
// Reads the "modelHandle*" / sound-link properties of a rigblock's part property list and
// wires up the block's deform handles: per-key handle lookup, stretch sounds, hidden flags,
// symmetric-handle links (template and per-part), placement types, the animation-sound map
// and the sound-parameter map.
//
// Module flags: editor /Od region, `/Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast` (no /EHsc).
// Layout: retail offsets (the 2008 PDB's cSPEditorBlock is 0x548 bytes; retail is larger).
// Property names come from SporeModder-FX's registry (tools/hashnames.py).
#include "types.h"

// ---------------------------------------------------------------- EASTL-style pieces
template <class T>
struct AutoRefCount {
    T* mpObject;
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};

// Reserved /Od frame space of inline callees that cl declined to inline (their calls are
// out of line here); reproduces the original's frame holes.
template <int N>
inline void ScratchSlots()
{
    uint32_t s[N];
}

template <class T>
struct vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator;

    int size() const { return (int)(mpEnd - mpBegin); }
    T& operator[](int i) { return mpBegin[i]; }
    void push_back(const T& value);     // out of line (0x005402c0)
};

// eastl::fixed_vector<T, N>: three pointers, the fixed_vector_allocator (overflow allocator,
// pool begin), then the inline buffer at +0x18.
template <class T, int N>
struct fixed_vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[3];
    T mBuffer[N];

    fixed_vector();  // out of line (0x00533360)
    ~fixed_vector()
    {
        for (T* p = mpBegin; p < mpEnd; ++p)
            p->~T();
        ScratchSlots<3>();  // DoFree's frame (declined inline)
        DoFree();
    }
    void DoFree();  // out of line (0x004c0b80): frees mpBegin unless it is the inline buffer

    int size() const { return (int)(mpEnd - mpBegin); }
    T& operator[](int i) { return mpBegin[i]; }
    void resize(unsigned int n);        // out of line (0x00454b80)
};

struct string8 {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    uint32_t mAllocator;

    void assign(const char* pBegin, const char* pEnd);  // 0x00454cb0
    string8& operator=(const string8& x)
    {
        if (&x != this)
            assign(x.mpBegin, x.mpEnd);
        return *this;
    }
};

template <class T1, class T2>
struct pair {
    T1 first;
    T2 second;
    pair() : first(), second() {}
};

struct ResourceKey {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
};

// ---------------------------------------------------------------- properties
struct Property {
    void* mpData;        // +0x00 (array data, or the inline value itself)
    uint32_t pad04;
    int mnItemCount;     // +0x08
    uint32_t pad0c;
    uint16_t mnFlags;    // +0x10 (0x30 = array)
    uint16_t mnType;     // +0x12

    unsigned int GetItemCount()
    {
        if (mnFlags & 0x30)
            return mnItemCount;
        else if (mnType != 0)
            return 1;
        return 0;
    }
    void* GetItems()
    {
        if (mnFlags & 0x30)
            return mpData;
        else if (mnType != 0)
            return this;
        return 0;
    }
};

class cPropertyList {
public:
    virtual int AddRef();
    virtual int Release();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void SetProperty(uint32_t id, const Property* p);
    virtual int RemoveProperty(uint32_t id);
    virtual bool HasProperty(uint32_t id);                       // 0x1c
    virtual bool GetPropertyAlt(uint32_t id, Property*& result); // 0x20
    virtual bool GetProperty(uint32_t id, Property*& result);    // 0x24
    virtual Property* GetPropertyObject(uint32_t id);            // 0x28
};

// App::Property::GetArrayBool
bool GetArrayBool(cPropertyList* list, uint32_t id, int& cnt, bool*& values);  // 0x006a0760

// ---------------------------------------------------------------- editor types
namespace SP {

struct cSPEditorHandleDeform {
    uint32_t pad000[0x8c / 4];
    uint32_t mHandleID;                      // +0x8c (cModelDeformationHandle id)
    uint32_t pad090[(0xac - 0x90) / 4];
    uint32_t mPinningType;                   // +0xac
    uint32_t mAxisToIgnore;                  // +0xb0
    cSPEditorHandleDeform* mSymmetricHandle; // +0xb4
    uint32_t pad0b8[(0x11c - 0xb8) / 4];
    string8 mSoundString;                    // +0x11c
    uint32_t pad12c[(0x1d4 - 0x12c) / 4];
    bool mIsHiddenHandle;                    // +0x1d4
    bool mDoNotPlaceHandle;                  // +0x1d5
};

struct UIntMap {  // eastl::map<uint32_t, uint32_t>
    uint32_t mData[7];
    void Reserve(int n);                      // 0x00454640
    uint32_t& operator[](const uint32_t& key);  // 0x00454750
};

typedef vector<pair<uint32_t, cSPEditorHandleDeform*> > SoundParamVector;
struct SoundParameterMap {  // eastl::map<uint32_t, vector<pair<uint32_t, cSPEditorHandleDeform*> > >
    uint32_t mData[7];
    SoundParamVector& operator[](const uint32_t& key);  // 0x004544d0
};

extern uint32_t kModelSignModifierHandleID;  // 0x015d25b0
extern uint32_t kLimbTypeHandleID;           // 0x015d2180
extern uint32_t kMuscleScaleHandleID;        // 0x015d22a4

class cSPEditorBlock {
public:
    int GetModelSignModifier();              // 0x0043c0a0
    int FindDeformHandleIndex(uint32_t id);  // 0x0043c120
    void InitializeHandleData(cPropertyList* propList);

    uint32_t pad000[3];
    AutoRefCount<cPropertyList> mPropList;   // +0x0c
    uint32_t pad010[(0x1b0 - 0x10) / 4];
    int mModelSignModifier;                  // +0x1b0
    int mModelSignModifierHandle;            // +0x1b4
    int mLimbTypeHandle;                     // +0x1b8
    int mMuscleScaleHandle;                  // +0x1bc
    uint32_t pad1c0[(0x614 - 0x1c0) / 4];
    SoundParameterMap mSoundParameterMap;    // +0x614
    UIntMap mAnimationSoundMap;              // +0x630
    uint32_t pad64c[(0x6cc - 0x64c) / 4];
    vector<AutoRefCount<cSPEditorHandleDeform> > mDeformationHandles;  // +0x6cc
};

void cSPEditorBlock::InitializeHandleData(cPropertyList* propList)
{
    fixed_vector<cSPEditorHandleDeform*, 8> handles;
    ScratchSlots<2>();

    mModelSignModifier = GetModelSignModifier();

    mModelSignModifierHandle = FindDeformHandleIndex(kModelSignModifierHandleID);
    if (mModelSignModifierHandle != -1)
        mDeformationHandles[mModelSignModifierHandle]->mDoNotPlaceHandle = true;
    mLimbTypeHandle = FindDeformHandleIndex(kLimbTypeHandleID);
    if (mLimbTypeHandle != -1)
        mDeformationHandles[mLimbTypeHandle]->mDoNotPlaceHandle = true;
    mMuscleScaleHandle = FindDeformHandleIndex(kMuscleScaleHandleID);
    if (mMuscleScaleHandle != -1)
        mDeformationHandles[mMuscleScaleHandle]->mDoNotPlaceHandle = true;

    int nNumHandles = mDeformationHandles.size();

    if (propList->HasProperty(0x8ecb344a)) {  // modelHandleKeys
        Property* prop = propList->GetPropertyObject(0x8ecb344a);
        int cnt = prop->GetItemCount();
        ResourceKey* keyArray = (ResourceKey*)prop->GetItems();
        ScratchSlots<3>();
        handles.resize(cnt);
        for (int i = 0; i < cnt; i++) {
            uint32_t id = keyArray[i].instanceID;
            handles[i] = 0;
            for (int j = 0; j < nNumHandles; j++) {
                if (mDeformationHandles[j]->mHandleID == id)
                    handles[i] = mDeformationHandles[j];
            }
        }
    }

    if (propList->HasProperty(0x3644a2c5)) {  // modelHandleStretchSounds
        Property* prop = propList->GetPropertyObject(0x3644a2c5);
        if (prop->mnType == 0x12) {
            int cnt = prop->GetItemCount();
            string8* sounds = (string8*)prop->GetItems();
            for (int i = 0; i < cnt; i++) {
                if (i < handles.size() && handles[i] != 0)
                    handles[i]->mSoundString = sounds[i];
            }
        }
    }

    if (propList->HasProperty(0x04604b04)) {  // modelHandleIsHidden
        int cnt = 0;
        bool* hidden;
        GetArrayBool(mPropList, 0x04604b04, cnt, hidden);
        for (int i = 0; i < cnt; i++) {
            if (i < handles.size() && handles[i] != 0)
                handles[i]->mIsHiddenHandle = hidden[i];
        }
    }

    if (propList->HasProperty(0x87fe8a14)) {  // modelHandleLinkedHandlesTemplate
        Property* prop = propList->GetPropertyObject(0x87fe8a14);
        int cnt = prop->GetItemCount();
        ResourceKey* keyArray = (ResourceKey*)prop->GetItems();
        for (int i = 0; i < cnt; i++) {
            uint32_t idA = keyArray[i].groupID;
            uint32_t idB = keyArray[i].instanceID;
            cSPEditorHandleDeform* handleA = 0;
            cSPEditorHandleDeform* handleB = 0;
            for (int j = 0; j < nNumHandles; j++) {
                if (mDeformationHandles[j]->mHandleID == idA)
                    handleA = mDeformationHandles[j];
                if (mDeformationHandles[j]->mHandleID == idB)
                    handleB = mDeformationHandles[j];
            }
            if (handleB != 0 && handleA != 0) {
                handleA->mSymmetricHandle = handleB;
                handleB->mSymmetricHandle = handleA;
            }
        }
    }

    if (propList->HasProperty(0x45101f3e)) {  // modelHandleLinkedHandles
        Property* prop = propList->GetPropertyObject(0x45101f3e);
        int cnt = prop->GetItemCount();
        ResourceKey* keyArray = (ResourceKey*)prop->GetItems();
        for (int i = 0; i < cnt; i++) {
            uint32_t idA = keyArray[i].groupID;
            uint32_t idB = keyArray[i].instanceID;
            cSPEditorHandleDeform* handleA = 0;
            cSPEditorHandleDeform* handleB = 0;
            bool bClear = idB == 0x2ca33bdb;  // "None"
            for (int j = 0; j < nNumHandles; j++) {
                if (mDeformationHandles[j]->mHandleID == idA)
                    handleA = mDeformationHandles[j];
                if (!bClear && mDeformationHandles[j]->mHandleID == idB)
                    handleB = mDeformationHandles[j];
            }
            if (handleB != 0 && handleA != 0) {
                handleA->mSymmetricHandle = handleB;
                handleB->mSymmetricHandle = handleA;
            } else if (bClear && handleA != 0) {
                if (handleA->mSymmetricHandle != 0)
                    handleA->mSymmetricHandle->mSymmetricHandle = 0;
                handleA->mSymmetricHandle = 0;
            }
        }
    }

    if (propList->HasProperty(0x3b58c554)) {  // modelHandlePlacementTypesTemplate
        Property* prop = propList->GetPropertyObject(0x3b58c554);
        int cnt = prop->GetItemCount();
        ResourceKey* keyArray = (ResourceKey*)prop->GetItems();
        for (int i = 0; i < cnt; i++) {
            uint32_t placementType = keyArray[i].instanceID;
            uint32_t id = keyArray[i].groupID;
            for (int j = 0; j < nNumHandles; j++) {
                if (mDeformationHandles[j]->mHandleID == id) {
                    mDeformationHandles[j]->mPinningType = placementType;
                    if (placementType == 0x9e6e561c)  // IgnoreAxis
                        mDeformationHandles[j]->mAxisToIgnore = keyArray[i].typeID;
                }
            }
        }
    }

    if (propList->HasProperty(0x23fc767e)) {  // modelHandlePlacementTypes
        Property* prop = propList->GetPropertyObject(0x23fc767e);
        int cnt = prop->GetItemCount();
        ResourceKey* keyArray = (ResourceKey*)prop->GetItems();
        for (int i = 0; i < cnt; i++) {
            uint32_t placementType = keyArray[i].instanceID;
            uint32_t id = keyArray[i].groupID;
            for (int j = 0; j < nNumHandles; j++) {
                if (mDeformationHandles[j]->mHandleID == id) {
                    mDeformationHandles[j]->mPinningType = placementType;
                    if (placementType == 0x9e6e561c)  // IgnoreAxis
                        mDeformationHandles[j]->mAxisToIgnore = keyArray[i].typeID;
                }
            }
        }
    }

    if (propList->HasProperty(0xb75fd502)) {  // modelAnimationSoundLinks
        Property* prop = propList->GetPropertyObject(0xb75fd502);
        int cnt = prop->GetItemCount();
        ResourceKey* keyArray = (ResourceKey*)prop->GetItems();
        ScratchSlots<8>();
        mAnimationSoundMap.Reserve(cnt);
        for (int i = 0; i < cnt; i++) {
            uint32_t sound = keyArray[i].instanceID;
            uint32_t anim = keyArray[i].groupID;
            mAnimationSoundMap[anim] = sound;
        }
    }

    if (propList->HasProperty(0x41f72519)) {  // modelSoundParameters
        Property* prop = propList->GetPropertyObject(0x41f72519);
        int cnt = prop->GetItemCount();
        ResourceKey* keyArray = (ResourceKey*)prop->GetItems();
        for (int i = 0; i < cnt; i++) {
            uint32_t group = keyArray[i].groupID;
            uint32_t handleId = keyArray[i].typeID;
            uint32_t parameterID = keyArray[i].instanceID;
            cSPEditorHandleDeform* foundHandle = 0;
            for (int j = 0; j < nNumHandles; j++) {
                if (mDeformationHandles[j]->mHandleID == handleId)
                    foundHandle = mDeformationHandles[j];
            }
            pair<uint32_t, cSPEditorHandleDeform*> entry;
            entry.first = parameterID;
            entry.second = foundHandle;
            ScratchSlots<63>();
            mSoundParameterMap[group].push_back(entry);
        }
    }
}

}  // namespace SP
