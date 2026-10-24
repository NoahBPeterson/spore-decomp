// Slice s0059f510 -- SP::cSPEditorBlockAbilities layout vector + ability helpers.
// Module flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast.
#include "types.h"

typedef unsigned int size_t;
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void  EASTL_deallocate(void* p);   // 0x00f47380

// ---------------------------------------------------------------------------
// cSPUILayout: 0x18-byte record
// ---------------------------------------------------------------------------
class cSPUILayout { public:
    char pad[0x18];
    cSPUILayout();                          // 0x00810000
    cSPUILayout(const cSPUILayout& x);      // 0x00810020
    ~cSPUILayout();                         // 0x00811fe0
    cSPUILayout& operator=(const cSPUILayout& x);  // 0x00810050
    void Shutdown(int flag);                // 0x00811ad0
};

struct UILayoutVector {
    cSPUILayout* mpBegin;
    cSPUILayout* mpEnd;
    cSPUILayout* mpCapacity;
    uint32_t     mAlloc[2];
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    cSPUILayout* erase(cSPUILayout* first, cSPUILayout* last);   // 0x0059f4a0
    void resize(uint32_t newSize);                               // 0x0059f950
    void insert(cSPUILayout* position, uint32_t n, const cSPUILayout& value);  // 0x0059f510
    ~UILayoutVector();                                           // 0x0059ee80
};

// eastl::map<int, ...> (sp_vector_allocator): compare selector + rbtree anchor.
struct RBNodeBase {
    RBNodeBase* mpNodeRight;
    RBNodeBase* mpNodeLeft;
    RBNodeBase* mpNodeParent;
    char        mColor;
};
namespace SP { struct VerbIconVec; }
struct VerbCategoryMap {
    uint32_t    mCompare;       // +0
    RBNodeBase  mAnchor;        // +4
    int* Find(const int& key);  // 0x004e88a0
    void FreeNodes(void* p);    // 0x004e8a30
    ~VerbCategoryMap() { FreeNodes(mAnchor.mpNodeParent); }
};

struct cSPEditorBlockAbilities {
    char          pad[0x24];
    UILayoutVector mLayouts;            // +0x24
    VerbCategoryMap mVerbCategoryMap;   // +0x38
    void ShutdownLayouts();             // 0x0059f900
    void SortAbilities(SP::VerbIconVec* abilities, VerbCategoryMap* categories);   // 0x0059f7c0
    void* ScalarDeletingDtor(unsigned char flags);   // 0x0059fa50
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

// 0x18-byte UI-layout default construction (as called from resize)
cSPUILayout* ConstructLayout(cSPUILayout* p, int arg);   // 0x00810020

// eastl::vector<cSPUILayout, sp_vector_allocator> algorithm helpers
cSPUILayout* UninitCopy(cSPUILayout* first, cSPUILayout* last, cSPUILayout* dest);       // 0x0059ed60
cSPUILayout* RelocateCommit(cSPUILayout* first, cSPUILayout* last, cSPUILayout* dest);   // 0x0059eda0
cSPUILayout* CopyBackward(cSPUILayout* first, cSPUILayout* last, cSPUILayout* dLast);    // 0x0059ee20
void FillLayouts(cSPUILayout* first, cSPUILayout* last, const cSPUILayout* value);       // 0x0059ef00
cSPUILayout* UninitMove(cSPUILayout** out, cSPUILayout* first, cSPUILayout* last,
                        cSPUILayout* dest, const cSPUILayout* tag);                      // 0x0059ef30
cSPUILayout* UninitFillN(cSPUILayout* first, uint32_t n, const cSPUILayout* value);      // 0x0059ef70

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
    if (newSize > (uint32_t)(((char*)mpEnd - (char*)mpBegin) / 0x18)) {
        // the default-constructed temporary lives in the caller's frame and is destroyed
        // right after the insert
        insert(mpEnd, newSize - (uint32_t)(((char*)mpEnd - (char*)mpBegin) / 0x18), cSPUILayout());
        return;
    }
    erase(mpBegin + newSize, mpEnd);
}

// ===========================================================================
// @ 0x0059f9e0
extern char vtbl_BlockAbilities0[];   // 0x013f6914
extern char vtbl_BlockAbilities1[];   // 0x013f6910

// 12-byte resource key passed by value to the ability base constructor
struct Key3 { uint32_t instanceID, typeID, groupID; };

// 0x60-byte ability base with two vtable words (the base ctor also fills the byte at +0x60,
// which is the first flag byte of the derived record)
struct AbilityBase {
    void* vptr0;      // +0x0
    void* vptr1;      // +0x4
    char  pad[0x60 - 0x8];
    AbilityBase(Key3 key, int ability, int flag0, int flag1, int flag2);   // 0x0059f030
};

struct VehicleAbilities : AbilityBase {
    unsigned char b60, b61, b62, b63;   // +0x60..+0x63
    int   m64;        // +0x64
    int   m68;        // +0x68
    int   m6c;        // +0x6c
    VehicleAbilities(int ability);
};

VehicleAbilities::VehicleAbilities(int ability)
    : AbilityBase(Key3(), ability, 0, 0, 1)
{
    *(void**)this = vtbl_BlockAbilities0;
    *(void**)((char*)this + 4) = vtbl_BlockAbilities1;
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
    AbilityRec* p = FindAbilitySlot(last, mpEnd, first);   // (range end, old end, range start)
    AbilityRec* end = mpEnd;
    // the record itself is the ability object: its first dword is the vtable and the
    // record pointer is the `this` handed to the teardown slot (vtable slot 2)
    for (; p < end; p = (AbilityRec*)((char*)p + 0xc4)) {
        void** vtbl = *(void***)p;
        (*(void(__thiscall**)(void*, int))(vtbl + 2))(p, 0);
    }
    mpEnd = (AbilityRec*)((char*)mpEnd + (((char*)first - (char*)last) / 0xc4) * 0xc4);
    return (int)first;
}

// ===========================================================================
// @ 0x0059f510
void UILayoutVector::insert(cSPUILayout* position, uint32_t n, const cSPUILayout& value)
{
    if (n <= (uint32_t)(mpCapacity - mpEnd)) {
        if (n > 0) {
            cSPUILayout temp(value);
            const uint32_t nExtra = (uint32_t)(mpEnd - position);
            cSPUILayout* const pEnd = mpEnd;
            if (n < nExtra) {
                cSPUILayout* out;
                UninitMove(&out, mpEnd - n, mpEnd, mpEnd, position);
                mpEnd += n;
                CopyBackward(position, pEnd - n, pEnd);
                FillLayouts(position, position + n, &temp);
            } else {
                cSPUILayout* out;
                UninitFillN(mpEnd, n - nExtra, &temp);
                mpEnd += n - nExtra;
                UninitMove(&out, position, pEnd, mpEnd, position);
                mpEnd += nExtra;
                FillLayouts(position, pEnd, &temp);
            }
        }
    } else {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        const uint32_t nGrowSize = nPrevSize ? nPrevSize * 2 : 1;
        const uint32_t nNewSize  = nGrowSize > (nPrevSize + n) ? nGrowSize : (nPrevSize + n);
        cSPUILayout* const pNewData = nNewSize
            ? (cSPUILayout*)operator new(nNewSize * 0x18, "Editor", 0, 0,
                  "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1)
            : 0;
        cSPUILayout* pNewEnd = UninitCopy(mpBegin, position, pNewData);
        RelocateCommit(mpBegin, position, pNewData);
        UninitFillN(pNewEnd, n, &value);
        pNewEnd = pNewEnd + n;
        cSPUILayout* const pNewEnd2 = UninitCopy(position, mpEnd, pNewEnd);
        RelocateCommit(position, mpEnd, pNewEnd);
        if (mpBegin && ((uint32_t*)mpBegin)[-1])
            EASTL_deallocate(mpBegin);
        mpBegin = pNewData;
        mpEnd = pNewEnd2;
        mpCapacity = pNewData + nNewSize;
    }
}

// @ 0x0059fa50
extern char vtbl_BlockAbilities0[];      // 0x013f6914
extern char vtbl_BlockAbilities1[];      // 0x013f6910
extern char vtbl_BlockAbilitiesBase0[];  // 0x013f68c4
extern char vtbl_BlockAbilitiesBase1[];  // 0x013ef094
void* cSPEditorBlockAbilities::ScalarDeletingDtor(unsigned char flags)
{
    *(void**)this = vtbl_BlockAbilities0;
    *(void**)((char*)this + 4) = vtbl_BlockAbilities1;
    ShutdownLayouts();
    mVerbCategoryMap.~VerbCategoryMap();
    mLayouts.~UILayoutVector();
    *(void**)((char*)this + 4) = vtbl_BlockAbilitiesBase1;
    *(void**)this = vtbl_BlockAbilitiesBase0;
    if (flags & 1)
        EASTL_deallocate(this);
    return this;
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
    cSPEditorVerbIconData& operator=(const cSPEditorVerbIconData&);  // 0x0059f0e0
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

// @ 0x0059f7c0
void cSPEditorBlockAbilities::SortAbilities(SP::VerbIconVec* abilities, VerbCategoryMap* categories)
{
    int count = (int)(abilities->mpEnd - abilities->mpBegin) - 1;
    if (count >= 0) {
        bool bSwapped;
        while (bSwapped = false, count > 0) {
            int n = count;
            int i = 0;
            do {
                SP::cSPEditorVerbIconData* a = abilities->mpBegin + i;
                int v1 = *categories->Find(a->mType);
                int v2 = *categories->Find(a[1].mType);
                if (v2 < v1) {
                    SP::cSPEditorVerbIconData temp(*a);
                    *a = a[1];
                    a[1] = temp;
                    bSwapped = true;
                }
                i++;
            } while (--n != 0);
            if (!bSwapped)
                return;
            if (--count < 0)
                return;
        }
    }
    return;
}
