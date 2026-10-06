// Slice s00826960: the single function in this slice is
//   SP::cPropertyUI::LoadPropFile   (0x00826960, 4737 bytes, thiscall, ret 0xc)
//
// The debug property-file viewer: fetches the property list (groupID, instanceID) from the
// property manager, clears the UI's hash maps, then adds one row of widgets per property,
// by property type (bool, int32, uint32, float, string8, string16, key, vector2/3/4,
// colorRGB/RGBA, and the array variants of each), and finally sizes the scroll bar.
//
// Module flags: UI module, `/O2 /MD /Gy /TP /arch:SSE /fp:fast` (no /EHsc: the string temporaries
// have no EH frame). Layout: retail offsets (the 2008 PDB's cPropertyUI is 0x160 bytes).
// The array branches compare the zero-extended 16-bit type with 0x8000xxxx constants, so
// they are dead code in the original too; they are kept for completeness.
#include "types.h"

// ---------------------------------------------------------------- EASTL-style pieces
extern wchar_t gEmptyString16[];  // 0x01667bac (EASTL empty-string buffer)

struct string8 {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    uint32_t mAllocator;
};

struct string16 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAllocator;

    string16()
    {
        mpBegin = gEmptyString16;
        mpEnd = gEmptyString16;
        mpCapacity = gEmptyString16 + 1;
    }
    ~string16() { DeallocateSelf(); }
    void DeallocateSelf();  // 0x00933960
    const wchar_t* c_str() const { return mpBegin; }
};

namespace EA {
string16 ConvertToString16(const string8& s);  // 0x0093c6d0
}

void operator_delete__(void* p);  // 0x00f47380 (operator delete[])

// eastl::vector<uint32_t> with the array-new allocator (frees only a block with a count cookie)
struct UIntVector {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    uint32_t mAllocator;

    UIntVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~UIntVector()
    {
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            operator_delete__(mpBegin);
    }
    int size() const { return (int)(mpEnd - mpBegin); }
    bool empty() const { return mpBegin == mpEnd; }
    uint32_t& operator[](uint32_t n) { return mpBegin[n]; }
};

// eastl::hash_map<uint32_t, T*>
struct HashMap {
    uint32_t mHash;
    void** mpBucketArray;
    uint32_t mnBucketCount;
    uint32_t mnElementCount;
    uint32_t mRest[4];

    void DoFreeNodes(void** pBucketArray, uint32_t n);  // 0x00693230
    void clear()
    {
        DoFreeNodes(mpBucketArray, mnBucketCount);
        mnElementCount = 0;
    }
};

// ---------------------------------------------------------------- math / resources
struct Vector2 { float x, y; };
struct Vector3 { float x, y, z; };
struct Vector4 { float x, y, z, w; };

struct ColorRGB {
    float r, g, b;
    ColorRGB() {}
    ColorRGB& operator=(const ColorRGB& c)
    {
        r = c.r;
        g = c.g;
        b = c.b;
        return *this;
    }
};
struct ColorRGBA {
    float r, g, b, a;
    ColorRGBA() {}
    ColorRGBA& operator=(const ColorRGBA& c)
    {
        r = c.r;
        g = c.g;
        b = c.b;
        a = c.a;
        return *this;
    }
};

struct ResourceKey {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
};

// ---------------------------------------------------------------- properties
extern const bool kDefaultBool;       // 0x015d115d
extern const int kDefaultInt32;       // 0x015d1160
extern const uint32_t kDefaultUInt32; // 0x015d1164

enum {
    kTypeBool = 1, kTypeInt32 = 9, kTypeUInt32 = 0xa, kTypeFloat = 0xd, kTypeString8 = 0x12,
    kTypeString16 = 0x13, kTypeKey = 0x20, kTypeVector2 = 0x30, kTypeVector3 = 0x31,
    kTypeColorRGB = 0x32, kTypeVector4 = 0x33, kTypeColorRGBA = 0x34, kTypeArray = 0x80000000
};

struct Property {
    void* mpData;        // +0x00 (array data, or the inline value itself)
    uint32_t pad04;
    int mnItemCount;     // +0x08
    uint32_t pad0c;
    uint16_t mnFlags;    // +0x10 (0x30 = array)
    uint16_t mnType;     // +0x12

    void* GetDataPtr()
    {
        if (mnFlags & 0x30)
            return mpData;
        return mnType ? this : 0;
    }
    // only used once the type is known to be bool
    const bool* GetValueBoolUnchecked() { return (const bool*)((mnFlags & 0x30) ? mpData : this); }
    const int* GetValueInt32()
    {
        return (mnType == kTypeInt32 || mnType == 0x10) ? (const int*)GetDataPtr() : &kDefaultInt32;
    }
    const uint32_t* GetValueUInt32()
    {
        return (mnType == kTypeUInt32 || mnType == 0x10) ? (const uint32_t*)GetDataPtr() : &kDefaultUInt32;
    }

    const float* GetValueFloat();            // 0x0041ea70
    const string8* GetValueString8();        // 0x0060ebf0
    const string16* GetValueString16();      // 0x0068a4f0
    const ResourceKey* GetValueKey();        // 0x006a1030
    const Vector2* GetValueVector2();        // 0x006a0f70
    const Vector3* GetValueVector3();        // 0x00cce910
    const Vector4* GetValueVector4();        // 0x006a0fa0
    const ColorRGB* GetValueColorRGB();      // 0x006a0fd0
    const ColorRGBA* GetValueColorRGBA();    // 0x006a1000
    int GetItemCount();                      // 0x00571ef0
    void* GetValue();                        // 0x00446ff0
};

class cPropertyList {
public:
    virtual int AddRef();
    virtual int Release();                                       // 0x04
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual bool HasProperty(uint32_t id);                       // 0x1c
    virtual void v20();
    virtual void v24();
    virtual Property* GetPropertyObject(uint32_t id);            // 0x28
    virtual void v2c();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3c();
    virtual void v40();
    virtual void GetPropertyIDs(UIntVector& ids);                // 0x44
};

template <class T>
struct intrusive_ptr {
    T* mpObject;
    intrusive_ptr() : mpObject(0) {}
    ~intrusive_ptr()
    {
        if (mpObject)
            mpObject->Release();
    }
    void reset()
    {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
    }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};

class cPropertyManager {
public:
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual const wchar_t* GetPropertyName(uint32_t id);                                   // 0x1c
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID,
                                 intrusive_ptr<cPropertyList>& dst);                       // 0x2c
};
cPropertyManager* PropertyManager();  // 0x0067de30

namespace EA {
namespace ResourceMan {
class IResourceManager {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78();
    virtual bool GetFileName(const ResourceKey& key, string16& name);  // 0x7c
};
IResourceManager* GetManager();  // 0x0067dcd0
}  // namespace ResourceMan
}  // namespace EA

// ---------------------------------------------------------------- UI
class IWindow;

class IWinScrollbar {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20();
    virtual void SetValue(int value, int notify);  // 0x24
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34();
    virtual int GetMaxValue();                     // 0x38
    virtual void SetMaxValue(int value, int notify);  // 0x3c
};

template <class T>
struct AutoRefCount {
    T* mpObject;
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};

// eastl::vector<IWindow*>
struct WindowVector {
    IWindow** mpBegin;
    IWindow** mpEnd;
    IWindow** mpCapacity;
    uint32_t mAllocator;
    IWindow*& operator[](int i) { return mpBegin[i]; }
};

__forceinline int RoundToInt(float f) { __asm cvtss2si eax, f }

namespace SP {

class cPropertyUI {
public:
    void LoadPropFile(uint32_t groupID, uint32_t instanceID, bool refresh);

    void ClearWindows();                                          // 0x008268b0
    void AddLabel(const wchar_t* text);                           // 0x00824e10
    int AddSubWindow(uint32_t propertyID);                        // 0x00824ff0
    void AddBool(int id, bool value, IWindow* parent);            // 0x00825110
    void AddInt(int id, int value, IWindow* parent);              // 0x008252b0
    void AddFloat(int id, float value, IWindow* parent);          // 0x00825930
    void AddString(int id, const wchar_t* value, IWindow* parent);  // 0x00825fc0
    void AddKey(int id, const wchar_t* value, IWindow* parent);   // 0x00826290
    void UpdateLayout();                                          // 0x0081e070

    void NewLine()
    {
        mCurrentX = 0.0f;
        mCurrentY += 30.0f;
    }

    uint32_t pad00[3];
    uint32_t mCurrentGroupID;     // +0x0c
    uint32_t mCurrentInstanceID;  // +0x10
    float mCurrentX;              // +0x14
    float mCurrentY;              // +0x18
    float mCurrentWindowX;        // +0x1c
    float mCurrentWindowY;        // +0x20
    float mPreviousScrollVal;     // +0x24
    float mRefreshScrollVal;      // +0x28
    float mScrollRatio;           // +0x2c
    float mScrollHeight;          // +0x30
    uint32_t mSpinnerButtonID;    // +0x34
    uint32_t pad38[(0x64 - 0x38) / 4];
    AutoRefCount<IWindow> mHolderWindow;  // +0x64
    AutoRefCount<IWinScrollbar> mScrollbar;  // +0x68
    uint32_t pad6c[(0x110 - 0x6c) / 4];
    WindowVector mSubWindows;     // +0x110
    uint32_t pad120[(0x130 - 0x120) / 4];
    HashMap mSpinnerToTextEditMap;   // +0x130
    HashMap mPropToTextEditMap;      // +0x150
    HashMap mPropToToggleButtonMap;  // +0x170
};

void cPropertyUI::LoadPropFile(uint32_t groupID, uint32_t instanceID, bool refresh)
{
    mCurrentGroupID = groupID;
    mCurrentInstanceID = instanceID;
    ClearWindows();
    mSpinnerButtonID = 0;

    intrusive_ptr<cPropertyList> propList;
    UIntVector ids;
    Vector2 vector2;
    Vector3 vector3;
    Vector4 vector4;
    ColorRGB colorRGB;
    ColorRGBA colorRGBA;
    cPropertyManager* propManager = PropertyManager();
    propList.reset();
    propManager->GetPropertyList(instanceID, groupID, propList);

    mPropToTextEditMap.clear();
    mSpinnerToTextEditMap.clear();
    mPropToToggleButtonMap.clear();

    if (propList) {
        propList->GetPropertyIDs(ids);
        if (!ids.empty()) {
            int count = ids.size();
            for (int i = 0; i < count; i++) {
                const wchar_t* name = propManager->GetPropertyName(ids[i]);
                Property* prop = propList->GetPropertyObject(ids[i]);
                uint16_t type = prop->mnType;

                if (type == kTypeBool) {
                    if (*prop->GetValueBoolUnchecked())
                        AddBool(ids[i], true, mHolderWindow);
                    else
                        AddBool(ids[i], false, mHolderWindow);
                    AddLabel(name);
                    NewLine();
                } else if (type == kTypeInt32) {
                    AddLabel(name);
                    AddInt(ids[i], *prop->GetValueInt32(), mHolderWindow);
                    NewLine();
                } else if (type == kTypeUInt32) {
                    AddLabel(name);
                    AddInt(ids[i], *prop->GetValueUInt32(), mHolderWindow);
                    NewLine();
                } else if (type == kTypeFloat) {
                    AddLabel(name);
                    AddFloat(ids[i], *prop->GetValueFloat(), mHolderWindow);
                    NewLine();
                } else if (type == kTypeString8) {
                    AddLabel(name);
                    AddString(ids[i], EA::ConvertToString16(*prop->GetValueString8()).c_str(), mHolderWindow);
                    NewLine();
                } else if (type == kTypeString16) {
                    AddLabel(name);
                    AddString(ids[i], prop->GetValueString16()->c_str(), mHolderWindow);
                    NewLine();
                } else if (type == kTypeKey) {
                    EA::ResourceMan::IResourceManager* resourceManager = EA::ResourceMan::GetManager();
                    const ResourceKey* key = prop->GetValueKey();
                    string16 keyName;
                    resourceManager->GetFileName(*key, keyName);
                    AddLabel(name);
                    AddKey(ids[i], keyName.c_str(), mHolderWindow);
                    NewLine();
                } else if (type == kTypeVector2) {
                    vector2 = *prop->GetValueVector2();
                    AddLabel(name);
                    NewLine();
                    int window = AddSubWindow(ids[i]);
                    AddFloat(1, vector2.x, mSubWindows[window]);
                    AddFloat(2, vector2.y, mSubWindows[window]);
                    NewLine();
                } else if (type == kTypeVector3) {
                    vector3 = *prop->GetValueVector3();
                    AddLabel(name);
                    NewLine();
                    int window = AddSubWindow(ids[i]);
                    AddFloat(1, vector3.x, mSubWindows[window]);
                    AddFloat(2, vector3.y, mSubWindows[window]);
                    AddFloat(3, vector3.z, mSubWindows[window]);
                    NewLine();
                } else if (type == kTypeVector4) {
                    vector4 = *prop->GetValueVector4();
                    AddLabel(name);
                    NewLine();
                    int window = AddSubWindow(ids[i]);
                    AddFloat(1, vector4.x, mSubWindows[window]);
                    AddFloat(2, vector4.y, mSubWindows[window]);
                    AddFloat(2, vector4.z, mSubWindows[window]);  // sic: the original passes 2 twice
                    AddFloat(4, vector4.w, mSubWindows[window]);
                    NewLine();
                } else if (type == kTypeColorRGB) {
                    colorRGB = *prop->GetValueColorRGB();
                    AddLabel(name);
                    NewLine();
                    int window = AddSubWindow(ids[i]);
                    AddFloat(1, colorRGB.r, mSubWindows[window]);
                    AddFloat(2, colorRGB.g, mSubWindows[window]);
                    AddFloat(3, colorRGB.b, mSubWindows[window]);
                    NewLine();
                } else if (type == kTypeColorRGBA) {
                    colorRGBA = *prop->GetValueColorRGBA();
                    AddLabel(name);
                    NewLine();
                    int window = AddSubWindow(ids[i]);
                    AddFloat(1, colorRGBA.r, mSubWindows[window]);
                    AddFloat(2, colorRGBA.g, mSubWindows[window]);
                    AddFloat(3, colorRGBA.b, mSubWindows[window]);
                    AddFloat(4, colorRGBA.a, mSubWindows[window]);
                    NewLine();
                } else if (type == (kTypeArray | kTypeBool)) {
                    int n = prop->GetItemCount();
                    const bool* values = (const bool*)prop->GetValue();
                    AddLabel(name);
                    NewLine();
                    int window = AddSubWindow(ids[i]);
                    for (int j = 0; j < n; j++) {
                        if (values[j])
                            AddBool(j + 1, true, mSubWindows[window]);
                        else
                            AddBool(j + 1, false, mSubWindows[window]);
                        NewLine();
                    }
                } else if (type == (kTypeArray | kTypeInt32)) {
                    int n = prop->GetItemCount();
                    const int* values = (const int*)prop->GetValue();
                    int window = AddSubWindow(ids[i]);
                    AddLabel(name);
                    NewLine();
                    for (int j = 0; j < n; j++) {
                        AddInt(j + 1, values[j], mSubWindows[window]);
                        NewLine();
                    }
                } else if (type == (kTypeArray | kTypeUInt32)) {
                    int n = prop->GetItemCount();
                    const uint32_t* values = (const uint32_t*)prop->GetValue();
                    int window = AddSubWindow(ids[i]);
                    AddLabel(name);
                    NewLine();
                    for (int j = 0; j < n; j++) {
                        AddInt(j + 1, values[j], mSubWindows[window]);
                        NewLine();
                    }
                } else if (type == (kTypeArray | kTypeFloat)) {
                    int n = prop->GetItemCount();
                    const float* values = (const float*)prop->GetValue();
                    int window = AddSubWindow(ids[i]);
                    AddLabel(name);
                    NewLine();
                    for (int j = 0; j < n; j++) {
                        AddFloat(j + 1, values[j], mSubWindows[window]);
                        NewLine();
                    }
                } else if (type == (kTypeArray | kTypeString8)) {
                    int n = prop->GetItemCount();
                    const string8* values = (const string8*)prop->GetValue();
                    int window = AddSubWindow(ids[i]);
                    AddLabel(name);
                    NewLine();
                    for (int j = 0; j < n; j++) {
                        AddString(j + 1, EA::ConvertToString16(values[j]).c_str(), mSubWindows[window]);
                        NewLine();
                    }
                } else if (type == (kTypeArray | kTypeString16)) {
                    int n = prop->GetItemCount();
                    const string16* values = (const string16*)prop->GetValue();
                    int window = AddSubWindow(ids[i]);
                    AddLabel(name);
                    NewLine();
                    for (int j = 0; j < n; j++) {
                        AddString(j + 1, values[j].c_str(), mSubWindows[window]);
                        NewLine();
                    }
                } else if (type == (kTypeArray | kTypeKey)) {
                    EA::ResourceMan::IResourceManager* resourceManager = EA::ResourceMan::GetManager();
                    int n = prop->GetItemCount();
                    const ResourceKey* values = (const ResourceKey*)prop->GetValue();
                    int window = AddSubWindow(ids[i]);
                    AddLabel(name);
                    NewLine();
                    string16 keyName;
                    for (int j = 0; j < n; j++) {
                        resourceManager->GetFileName(values[j], keyName);
                        AddKey(j + 1, keyName.c_str(), mSubWindows[window]);
                        NewLine();
                    }
                } else if (type == (kTypeArray | kTypeVector2)) {
                    int n = prop->GetItemCount();
                    const Vector2* values = (const Vector2*)prop->GetValue();
                    int window = AddSubWindow(ids[i]);
                    AddLabel(name);
                    NewLine();
                    for (int j = 0; j < n; j++) {
                        vector2 = values[j];
                        AddFloat(j + 1, vector2.x, mSubWindows[window]);
                        AddFloat(j + 2, vector2.y, mSubWindows[window]);
                        NewLine();
                    }
                } else if (type == (kTypeArray | kTypeVector3)) {
                    int n = prop->GetItemCount();
                    const Vector3* values = (const Vector3*)prop->GetValue();
                    int window = AddSubWindow(ids[i]);
                    AddLabel(name);
                    NewLine();
                    for (int j = 0; j < n; j++) {
                        vector3 = values[j];
                        AddFloat(j + 1, vector3.x, mSubWindows[window]);
                        AddFloat(j + 2, vector3.y, mSubWindows[window]);
                        AddFloat(j + 3, vector3.z, mSubWindows[window]);
                        NewLine();
                    }
                } else if (type == (kTypeArray | kTypeVector4)) {
                    int n = prop->GetItemCount();
                    const Vector4* values = (const Vector4*)prop->GetValue();
                    int window = AddSubWindow(ids[i]);
                    AddLabel(name);
                    NewLine();
                    for (int j = 0; j < n; j++) {
                        vector4 = values[j];
                        AddFloat(j + 1, vector4.x, mSubWindows[window]);
                        AddFloat(j + 2, vector4.y, mSubWindows[window]);
                        AddFloat(j + 3, vector4.z, mSubWindows[window]);
                        AddFloat(j + 4, vector4.w, mSubWindows[window]);
                        NewLine();
                    }
                } else if (type == (kTypeArray | kTypeColorRGB)) {
                    int n = prop->GetItemCount();
                    const Vector3* values = (const Vector3*)prop->GetValue();
                    int window = AddSubWindow(ids[i]);
                    AddLabel(name);
                    NewLine();
                    for (int j = 0; j < n; j++) {
                        vector3 = values[j];
                        AddFloat(j + 1, vector3.x, mSubWindows[window]);
                        AddFloat(j + 2, vector3.y, mSubWindows[window]);
                        AddFloat(j + 3, vector3.z, mSubWindows[window]);
                        NewLine();
                    }
                } else if (type == (kTypeArray | kTypeColorRGBA)) {
                    int n = prop->GetItemCount();
                    const Vector4* values = (const Vector4*)prop->GetValue();
                    int window = AddSubWindow(ids[i]);
                    AddLabel(name);
                    NewLine();
                    for (int j = 0; j < n; j++) {
                        vector4 = values[j];
                        AddFloat(j + 1, vector4.x, mSubWindows[window]);
                        AddFloat(j + 2, vector4.y, mSubWindows[window]);
                        AddFloat(j + 3, vector4.z, mSubWindows[window]);
                        AddFloat(j + 4, vector4.w, mSubWindows[window]);
                        NewLine();
                    }
                }
            }

            mScrollRatio = mCurrentY / mScrollHeight;
            if (mScrollRatio > 1.0f) {
                float maxValue = (float)mScrollbar->GetMaxValue() / mScrollRatio;
                int newMax = RoundToInt(maxValue);
                mScrollbar->SetMaxValue(newMax, 1);
            }
            if (refresh) {
                float value = mRefreshScrollVal;
                mScrollbar->SetValue(RoundToInt(value), 1);
            }
            UpdateLayout();
        }
    }
}

}  // namespace SP
