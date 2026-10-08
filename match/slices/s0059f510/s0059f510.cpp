// Slice s0059f510 -- SP::cSPEditorBlockAbilities layout vector + ability helpers.
// Module flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast.
#include "types.h"

typedef unsigned int size_t;
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void  EASTL_deallocate(void* p);   // 0x00f47380

// ---------------------------------------------------------------------------
// cSPUILayout: 0x18-byte record
// ---------------------------------------------------------------------------
struct cSPUILayout {
    char pad[0x18];
    cSPUILayout();                 // 0x00810000
    ~cSPUILayout();                // 0x00811fe0
    void Shutdown(int flag);       // 0x00811ad0
};

struct UILayoutVector {
    cSPUILayout* mpBegin;
    cSPUILayout* mpEnd;
    cSPUILayout* mpCapacity;
    uint32_t     mAlloc[2];
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    cSPUILayout* erase(cSPUILayout* first, cSPUILayout* last);   // 0x0059f4a0
    void resize(uint32_t newSize);                               // 0x0059f950
};

struct cSPEditorBlockAbilities {
    char          pad[0x24];
    UILayoutVector mLayouts;    // +0x24
    void ShutdownLayouts();     // 0x0059f900
};

// 0xc4-byte ability record whose first field is an object with a vtable
struct AbilityRec {
    void* mpObject;     // +0x0
    char  pad[0xc4 - 4];
};

struct AbilityVector {
    AbilityRec* mpBegin;
    AbilityRec* mpEnd;
    AbilityRec* mpCapacity;
    uint32_t    mAlloc[2];
    int EraseRange(AbilityRec* first, AbilityRec* last);   // 0x0059faa0
};

// 0x18-byte UI-layout constructor (as called from resize)
cSPUILayout* ConstructLayout(cSPUILayout* p, int arg);   // 0x00810020
void VectorInsertFill(UILayoutVector* v, cSPUILayout* pos, uint32_t count, cSPUILayout* value);  // 0x0059f510
void MoveLayouts(UILayoutVector* v, cSPUILayout* dst, cSPUILayout* src);   // 0x0059ee20
cSPUILayout* MoveLayoutArray(UILayoutVector* v, cSPUILayout* out, cSPUILayout* a, cSPUILayout* b, cSPUILayout* c); // 0x0059ef30

// ability helpers
AbilityRec* FindAbilitySlot(AbilityRec* a, AbilityRec* b, AbilityRec* c);  // 0x0059f740

// ===========================================================================
// @ 0x0059f900
void cSPEditorBlockAbilities::ShutdownLayouts()
{
    UILayoutVector* v = &mLayouts;
    int n = (int)(((char*)v->mpEnd - (char*)v->mpBegin) / 0x18);
    if (n > 0) {
        int offset = 0;
        do {
            ((cSPUILayout*)((char*)v->mpBegin + offset))->Shutdown(1);
            offset += 0x18;
        } while (--n != 0);
    }
    v->erase(v->mpBegin, v->mpEnd);
}

// ===========================================================================
// @ 0x0059f950
void UILayoutVector::resize(uint32_t newSize)
{
    uint32_t cur = (uint32_t)(((char*)mpEnd - (char*)mpBegin) / 0x18);
    if (cur < newSize) {
        char tmp[0x18];
        ConstructLayout((cSPUILayout*)tmp, 0);
        VectorInsertFill(this, mpEnd, newSize - cur, (cSPUILayout*)tmp);
        ((cSPUILayout*)tmp)->~cSPUILayout();
    } else {
        erase(mpBegin + newSize, mpEnd);
    }
}

// ===========================================================================
// @ 0x0059f9e0
struct VehicleAbilities {
    void* vptr0;      // +0x0
    void* vptr1;      // +0x4
    char  pad[0x61 - 0x8];
    unsigned char b61, b62, b63;
    int   m64;        // +0x64
    int   m68;        // +0x68
    int   m6c;        // +0x6c
    VehicleAbilities();
};

VehicleAbilities::VehicleAbilities()
{
    m64 = 2;
    b61 = 1;
    b62 = 0;
    b63 = 1;
    m68 = 0xf56d252d;
    m6c = 0x3c02fae0;
}

// ===========================================================================
// @ 0x0059faa0
int AbilityVector::EraseRange(AbilityRec* first, AbilityRec* last)
{
    AbilityRec* p = FindAbilitySlot(first, mpEnd, last);
    AbilityRec* end = mpEnd;
    for (; p < end; p = (AbilityRec*)((char*)p + 0xc4)) {
        void** vtbl = *(void***)p->mpObject;
        void* fn = *(void**)((char*)vtbl + 8);
        (*(void(__thiscall**)(void*, int))fn)(p->mpObject, 0);
    }
    mpEnd = (AbilityRec*)((char*)mpEnd + (((char*)last - (char*)first) / 0xc4) * 0xc4);
    return (int)first;
}

// ===========================================================================
// @ 0x0059f510
void VectorInsertFill(UILayoutVector* v, cSPUILayout* pos, uint32_t count, cSPUILayout* value)
{
    (void)v; (void)pos; (void)count; (void)value;
}

// @ 0x0059f7c0
int SortAbilities(void* a, void* b)
{
    (void)a; (void)b;
    return 0;
}

// @ 0x0059fa50
void* ScalarDeletingDtor(void* p, unsigned char flags)
{
    (void)flags;
    return p;
}

// @ 0x0059fc60  (types for BlockGetAbilities: retail layouts, see s0059e360_b.cpp / s0059d300.cpp)
inline void* operator new(size_t, void* p) { return p; }
void operator delete[](void* p);   // 0x00F47380

namespace EA {
namespace COM {
class IUnknown32 {
public:
    virtual int AddRef() = 0;
    virtual int Release() = 0;
    virtual ~IUnknown32() {}
};
}
template <typename T>
class RefCountVTemplate {
public:
    RefCountVTemplate() : mRefCount(0) {}
    RefCountVTemplate(const RefCountVTemplate&) : mRefCount(0) {}
    RefCountVTemplate& operator=(const RefCountVTemplate&) { return *this; }
    virtual ~RefCountVTemplate() {}
    T mRefCount;
};
}  // namespace EA

struct ResourceKey { uint32_t instanceID, typeID, groupID; };

namespace SP {

struct Property {
    void* mpData;        // +0x00 (array data, or the inline value itself)
    uint32_t pad04;
    int mnItemCount;     // +0x08
    uint32_t pad0c;
    uint16_t mnFlags;    // +0x10 (0x30 = array)
    uint16_t mnType;     // +0x12
};

class cPropertyList {
public:
    virtual int AddRef();
    virtual int Release();
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18();
    virtual bool HasProperty(uint32_t id);                       // +0x1c
    virtual bool GetPropertyAlt(uint32_t id, Property*& result); // +0x20
    virtual bool GetProperty(uint32_t id, Property*& result);    // +0x24
};

template <class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    T** GetAddress()
    {
        if (mpObject) {
            T* p = mpObject;
            mpObject = 0;
            p->Release();
        }
        return &mpObject;
    }
};

class IPropertyManager {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, cPropertyList** result);  // +0x2c
};
IPropertyManager* PropertyManager();                              // 0x0067de30
uint32_t GetPropIDForAbility(uint32_t ability, int level);        // 0x00459370 (cdecl)
uint32_t GetVerbCategory(cPropertyList* icon);                    // 0x004e58c0 (cdecl)
bool IsDietCategory(uint32_t category);                           // 0x004e5910 (cdecl)
bool GetPropertyAsKeyArray(cPropertyList* list, uint32_t id, int* count, ResourceKey** keys);   // 0x006a0ae0 (cdecl)

class cString {
public:
    cString(uint32_t tableID, uint32_t instanceID, const wchar_t* pFallback);   // 0x006b5770
    ~cString();                              // 0x006b5240
    cString& operator=(const cString& x);    // 0x006b5430
    uint32_t pad[5];
};

namespace eastl_ {
struct wstring16 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAllocator;
    ~wstring16()
    {
        if ((mpCapacity - mpBegin) > 1 && mpBegin)
            operator delete[](mpBegin);
    }
};
}

class cSPEditorVerbIconData : public EA::COM::IUnknown32, public EA::RefCountVTemplate<int> {
public:
    cSPEditorVerbIconData();                                // 0x005e5a70
    cSPEditorVerbIconData(const cSPEditorVerbIconData&);    // 0x0059f2a0
    virtual int AddRef();
    virtual int Release();
    virtual ~cSPEditorVerbIconData() {}
    void Init(cPropertyList* pList);                        // 0x005e5470

    bool        mUseDescription;      // +0xc
    bool        mShowLevel;           // +0xd
    bool        mShowHotKey;          // +0xe
    bool        mShowZeroLevel;       // +0xf
    bool        mb10;                 // +0x10
    bool        mb11;                 // +0x11
    int         mHotKeyProp;          // +0x14
    float       mLevel;               // +0x18
    float       mMaxLevel;            // +0x1c
    float       mf20;                 // +0x20
    int         mType;                // +0x24
    uint32_t    mAnimation;           // +0x28
    float       mColor[4];            // +0x2c
    uint32_t    m3c, m40, m44, m48;
    bool        mb4c;                 // +0x4c
    bool        mb4d;                 // +0x4d
    uint32_t    mHotKeyID;            // +0x50
    cString     mName;                // +0x54
    eastl_::wstring16 mHotKeyString;  // +0x68
    int         mArrayIndex;              // +0x78
    int         mPreSpecifiedArrayIndex;  // +0x7c
    uint32_t    mKeys[12];                // +0x80..0xb0
    uint32_t    mB0, mB4, mB8, mBC;
    AutoRefCount<cPropertyList> mPropList;    // +0xc0
};

// vector<cSPEditorVerbIconData> (eastl, sp_vector_allocator), 0xc4-byte elements
struct VerbIconVec {
    cSPEditorVerbIconData* mpBegin;
    cSPEditorVerbIconData* mpEnd;
    cSPEditorVerbIconData* mpCapacity;
    uint32_t mAlloc[2];
    void DoInsertValue(cSPEditorVerbIconData* pos, const cSPEditorVerbIconData& v);   // 0x0059fb10
    void push_back(const cSPEditorVerbIconData& v)
    {
        if (mpEnd < mpCapacity) {
            cSPEditorVerbIconData* p = mpEnd;
            mpEnd = p + 1;
            if (p) new (p) cSPEditorVerbIconData(v);
        } else {
            DoInsertValue(mpEnd, v);
        }
    }
    int EraseRange(cSPEditorVerbIconData* first, cSPEditorVerbIconData* last);   // 0x0059faa0
};

static inline int GetIntProperty(cPropertyList* list, uint32_t id)
{
    int value = 0;
    Property* prop;
    if (list && list->GetProperty(id, prop) && prop->mnType == 9) {
        Property* p = prop;
        if (prop->mnFlags & 0x30)
            p = (Property*)prop->mpData;
        value = *(int*)p;
    }
    return value;
}

extern const uint32_t gAbilityIds[95];    // 0x013f6748

// Fills `out` with one verb-icon entry per ability found in the block's property list
// (falling back to a keyed list of icons, then to Speed/Defense/Power summary entries).
void BlockGetAbilities(VerbIconVec* out, ResourceKey* key, uint32_t listId)
{
    AutoRefCount<cPropertyList> props;
    PropertyManager()->GetPropertyList(key->instanceID, key->groupID, props.GetAddress());
    out->EraseRange(out->mpBegin, out->mpEnd);
    bool bA = false, bB = false, bC = false, bD = false;
    bool bAnyAdded = false;
    Property* prop;
    for (int i = 0; i < 95; i++) {
        if (props.mpObject->HasProperty(gAbilityIds[i])) {
            int level = GetIntProperty(props.mpObject, gAbilityIds[i]);
            uint32_t propId = GetPropIDForAbility(gAbilityIds[i], level);
            if (propId != 0) {
                AutoRefCount<cPropertyList> icon;
                PropertyManager()->GetPropertyList(propId, 0xdd91ac58, icon.GetAddress());
                if (icon.mpObject == 0) {
                    PropertyManager()->GetPropertyList(propId, 0x1b68db4, icon.GetAddress());
                    if (icon.mpObject == 0)
                        continue;
                }
                uint32_t cat = GetVerbCategory(icon.mpObject);
                if (!IsDietCategory(cat)) {
                    cSPEditorVerbIconData d;
                    d.Init(icon.mpObject);
                    d.mLevel = (float)level;
                    if (d.mLevel < 0.0f)
                        d.mShowLevel = false;
                    out->push_back(d);
                    bAnyAdded = true;
                } else {
                    switch ((int)cat) {
                    case (int)0xdfa0d6bf: bA = true; break;
                    case (int)0xd9bcb9f0: bC = true; break;
                    case (int)0xa28a67e8: bA = true; bB = true; break;
                    case 0x2dfb4f9f: bC = true; bB = true; break;
                    case 0x5cd23f68: bB = true; /* fallthrough */
                    case 0x521a15d5: bD = true; break;
                    }
                }
            }
        }
    }
    bool bBoth = bD || (bC && bA);
    if (!bBoth && !bC && !bA) {
      if (!bAnyAdded) {
        if (listId == 0)
            listId = 0x4ecf38a;
        int count = 0;
        ResourceKey* keys;
        if (GetPropertyAsKeyArray(props.mpObject, listId, &count, &keys)) {
            for (int i = 0; i < count; i++) {
                AutoRefCount<cPropertyList> icon;
                if (PropertyManager()->GetPropertyList(keys[i].instanceID, keys[i].groupID, icon.GetAddress())
                    || PropertyManager()->GetPropertyList(keys[i].instanceID, 0x1b68db4, icon.GetAddress())
                    || PropertyManager()->GetPropertyList(keys[i].instanceID, 0xdd91ac58, icon.GetAddress())
                    || PropertyManager()->GetPropertyList(keys[i].instanceID, 0xc85c1f8b, icon.GetAddress())) {
                    cSPEditorVerbIconData d;
                    d.Init(icon.mpObject);
                    out->push_back(d);
                }
            }
        } else {
            int speed = GetIntProperty(props.mpObject, 0x11b78a70);
            int defense = GetIntProperty(props.mpObject, 0x11b78a71);
            int power = GetIntProperty(props.mpObject, 0x11b78a72);
            if (speed > 0) {
                cSPEditorVerbIconData d;
                d.mName = cString(0xd1726890, 0x4bf5d41, L"Speed");
                d.mLevel = (float)speed;
                out->push_back(d);
            }
            if (defense > 0) {
                cSPEditorVerbIconData d;
                d.mName = cString(0xd1726890, 0x4bf5d42, L"Defense");
                d.mLevel = (float)defense;
                out->push_back(d);
            }
            if (power > 0) {
                cSPEditorVerbIconData d;
                d.mName = cString(0xd1726890, 0x4bf5d43, L"Power");
                d.mLevel = (float)power;
                out->push_back(d);
            }
        }
      }
    } else {
        uint32_t grp = bB ? 0xdd91ac58 : 0x1b68db4;
        uint32_t id;
        if (bBoth)
            id = bB ? GetPropIDForAbility(0x4d18972, 0) : GetPropIDForAbility(0x4d192a3, 0);
        else if (bA)
            id = bB ? GetPropIDForAbility(0x22e7847, 0) : GetPropIDForAbility(0x4d192a1, 0);
        else if (bC)
            id = bB ? GetPropIDForAbility(0x22e785c, 0) : GetPropIDForAbility(0x4d192a2, 0);
        else
            id = (uint32_t)prop;
        AutoRefCount<cPropertyList> icon;
        PropertyManager()->GetPropertyList(id, grp, icon.GetAddress());
        cSPEditorVerbIconData d;
        d.Init(icon.mpObject);
        d.mLevel = 0.0f;
        d.mShowLevel = false;
        out->push_back(d);
    }
}

}  // namespace SP
