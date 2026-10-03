// Slice s00406ac0: a large editor/state record's copy-assignment, a couple of
// property-list helpers (App::PropertyList bool lookups) and a ResourceKey remap loop.
//
// This module was built WITHOUT optimization and without EH:
//   compile with /Od /Ob1 /MD /Gy /TP
//
// /Od notes that matter for byte-exactness here:
//  - Stack slots of named locals are ordered by the compiler (name-dependent), so
//    some local names below were chosen because they reproduce the original layout.
//  - Inline (in-class) helpers are expanded at /Ob1 and keep their own slots.

#include "types.h"

// ---------------------------------------------------------------------------
// Minimal EASTL-style support
// ---------------------------------------------------------------------------
struct false_type {};
template <class T> struct is_integral : public false_type {};

class RefCounted {
public:
    virtual int AddRef();
    virtual int Release();
};

template <class T> class intrusive_ptr {
public:
    intrusive_ptr() : mpObject(0) {}
    ~intrusive_ptr() { if (mpObject) mpObject->Release(); }

    T* get() const { return mpObject; }

    // Drops the current reference and hands out the raw slot, for APIs that
    // fill an intrusive_ptr through a T** out-parameter.
    T** AsOutParam()
    {
        if (mpObject) { T* pOld = mpObject; mpObject = 0; pOld->Release(); }
        return &mpObject;
    }

    intrusive_ptr& operator=(const intrusive_ptr& ip) { return operator=(ip.mpObject); }
    intrusive_ptr& operator=(T* pObject)
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

// ---------------------------------------------------------------------------
// ResourceKey / group ID bitfields
// ---------------------------------------------------------------------------
struct ResourceKey {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
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

// ---------------------------------------------------------------------------
// App::Property / App::PropertyList / App::PropertyManager (subset)
// ---------------------------------------------------------------------------
class Property {
public:
    bool* GetValueBool();            // 0x0041e920
    uint16_t pad[9];
    uint16_t mnType;                 // +0x12  (1 = bool)
};

class PropertyList {
public:
    virtual int AddRef();
    virtual int Release();
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8();
    virtual bool GetProperty(uint32_t propertyID, Property*& result);  // +0x24
};

class PropertyManager {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyList** ppDst); // +0x2c
};
PropertyManager* PropertyManager_Get();   // 0x0067de30

// @ 0x00407190
// Reads a bool property; returns false if the list is null, the property is
// missing or not of bool type.
bool GetBoolProperty(PropertyList* list, uint32_t propertyID, bool& result)
{
    Property* pProp;
    bool* pValue;   // unused; keeps the original frame layout
    if (list && list->GetProperty(propertyID, pProp) && pProp->mnType == 1) {
        result = *pProp->GetValueBool();
        return true;
    }
    return false;
}

// Same as GetBoolProperty, expanded inline at its call sites.
inline bool GetBoolPropertyInline(PropertyList* list, uint32_t propertyID, bool& result)
{
    Property* pProp;
    bool* pValue;
    if (list && list->GetProperty(propertyID, pProp) && pProp->mnType == 1) {
        result = *pProp->GetValueBool();
        return true;
    }
    return false;
}

// Out-of-line GetBoolProperty call through an inline wrapper. The three unused
// locals stand in for the slots the original compiler reserved at these call
// sites (an inline expansion that was not performed).
inline void GetBoolPropertyOutOfLine(const intrusive_ptr<PropertyList>& list, uint32_t propertyID, bool& result)
{
    uint32_t reserved0, reserved1, reserved2;
    GetBoolProperty(list.get(), propertyID, result);
}

const uint32_t kPropEnabled          = 0x3704e55;
const uint32_t kPropEnabledSecondary = 0x3704e56;

// ---------------------------------------------------------------------------
// 0x00406ef0: is a resource flagged in its property list?
// Groups of kind 0x62 come in two variants (0 and 1); both must be flagged.
// ---------------------------------------------------------------------------
struct ResourceFlagQuery {
    bool IsFlagged(const ResourceKey& key, bool requireSecondary);
};

// @ 0x00406ef0
bool ResourceFlagQuery::IsFlagged(const ResourceKey& key, bool requireSecondary)
{
    if (MakeGroup(key.groupID).kind == 0x62) {
        uint32_t primaryGroup = WithVariant(key.groupID, 0);
        uint32_t otherGroup = WithVariant(key.groupID, 1);
        bool baseFlag = false;
        bool flag1 = false;
        intrusive_ptr<PropertyList> pPropList;
        if (PropertyManager_Get()->GetPropertyList(key.instanceID, primaryGroup, pPropList.AsOutParam()))
            GetBoolPropertyOutOfLine(pPropList, kPropEnabled, baseFlag);
        if (PropertyManager_Get()->GetPropertyList(key.instanceID, otherGroup, pPropList.AsOutParam()))
            GetBoolPropertyOutOfLine(pPropList, kPropEnabled, flag1);
        return baseFlag && flag1;
    }
    bool flag = false;
    intrusive_ptr<PropertyList> pPropList;
    if (PropertyManager_Get()->GetPropertyList(key.instanceID, key.groupID, pPropList.AsOutParam())) {
        GetBoolPropertyInline(pPropList.get(), kPropEnabled, flag);
        if (flag && requireSecondary) {
            flag = false;
            GetBoolPropertyInline(pPropList.get(), kPropEnabledSecondary, flag);
        }
    }
    return flag;
}

// ---------------------------------------------------------------------------
// 0x00406e90: two virtual predicates OR-ed together.
// ---------------------------------------------------------------------------
class IPredicateTarget {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6();
    virtual bool TestA(void* arg, int flags);     // +0x1c
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14();
    virtual bool TestB(void* arg);                // +0x3c
    bool TestAny(void* arg);
};

// @ 0x00406e90
bool IPredicateTarget::TestAny(void* arg)
{
    return TestA(arg, 0) || TestB(arg);
}

// ---------------------------------------------------------------------------
// 0x004071e0: apply a ResourceKey to every key pair of a vector.
// ---------------------------------------------------------------------------
bool KeysDiffer(const ResourceKey& a, const ResourceKey& b);       // 0x0041dd30
void RemapKey(ResourceKey& key, const ResourceKey& replacement);    // 0x0041ddb0
extern ResourceKey kNullKey;                                        // 0x015d1564

struct KeyPair { ResourceKey a; ResourceKey b; };

template <class T> struct vector {
    T* mpBegin; T* mpEnd; T* mpCapacity;
    int size() const { return mpEnd - mpBegin; }
    T& operator[](int i) { return mpBegin[i]; }
};

struct KeyRemapper {
    void Apply(vector<KeyPair>& pairs, ResourceKey key);
};

// @ 0x004071e0
void KeyRemapper::Apply(vector<KeyPair>& pairs, ResourceKey key)
{
    if (KeysDiffer(key, kNullKey)) {
        for (int i = 0, size = pairs.size(); i < size; i++) {
            KeyPair& pair = pairs[i];
            RemapKey(pair.a, key);
            RemapKey(pair.b, key);
        }
    }
}

// ---------------------------------------------------------------------------
// 0x00406ac0: copy-assignment of a large (0xccc byte) record built from
// fixed_vector-style containers (begin/end pointers + inline storage).
// Container operator= are inline: "if (this != &x) { clear; assign(x.begin(), x.end()); }".
// ---------------------------------------------------------------------------
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
    intrusive_ptr<RefCounted> mpOwner;    // +0x008
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
