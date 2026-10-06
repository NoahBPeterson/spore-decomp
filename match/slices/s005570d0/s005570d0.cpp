// Slice s005570d0: SP/Simulator content-validation summarizer. Unoptimized /Od module.
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast
#include "types.h"

// ---------------------------------------------------------------------------
// Refcounted property p33 access (subset)
// ---------------------------------------------------------------------------
class Property {
public:
    int* GetInt();                   // 0x0041e990
    uint16_t pad[9];
    uint16_t mnType;                 // +0x12 (9 = int32)
};

class PropertyList {
public:
    virtual int AddRef();
    virtual int Release();
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8();
    virtual bool GetProperty(uint32_t propertyID, Property*& result);  // +0x24
};

template <class T> class intrusive_ptr {
public:
    intrusive_ptr(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~intrusive_ptr() { if (mpObject) mpObject->Release(); }
    T* get() const { return mpObject; }
    // Releases the current reference and hands out the raw slot (0x0041d870).
    T** AsOutParam();
    T** Out() { return AsOutParam(); }
    __forceinline intrusive_ptr& operator=(T* pObject)
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

template <class T> T** intrusive_ptr<T>::AsOutParam()
{
    if (mpObject) { T* pOld = mpObject; mpObject = 0; pOld->Release(); }
    return &mpObject;
}

struct ResourceKey {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
    ResourceKey() { instanceID = 0; typeID = 0; groupID = 0; }
    ResourceKey(int64_t inst, uint32_t type, uint32_t group)
        : instanceID((uint32_t)inst), typeID(type), groupID(group) {}
};

// Resource group id: kind bytes sit in bits 8..23, top two bits are a flag.
union GroupBits {
    uint32_t value;
    struct {
        uint32_t low : 8;
        uint32_t sub : 8;       // bits 8..15
        uint32_t kind : 8;      // bits 16..23
        uint32_t mid : 6;
        uint32_t top : 2;       // bits 30..31
    };
};

class PropertyManager {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyList** ppDst); // +0x2c
};
PropertyManager* PropertyManager_Get();                                  // 0x0067de30
bool GetPropertyAsKey(PropertyList* p33, uint32_t id, ResourceKey* out); // 0x006a1250

inline void ReadIntProperty(PropertyList* p33, uint32_t id, int& result)
{
    Property* pProp;
    if (p33 && p33->GetProperty(id, pProp) && pProp->mnType == 9)
        result = *pProp->GetInt();
}

inline ResourceKey MakeSuffixKey(const int& count, uint32_t type, uint32_t kind, uint32_t sub)
{
    GroupBits g;
    g.value = 0;
    g.top = 1;
    g.kind = kind;
    g.sub = sub;
    return ResourceKey(count, type, g.value);
}

// vtables (data)
extern char g_vtbl_Summarizer[];        // 0x013ec458
extern char g_vtbl_ScalarDeleting[];    // 0x013f0958
extern char g_vtbl_c557c90[];           // 0x013f4250
extern char g_vtbl_SummarizerFinal[];   // 0x013f4274

// Base chain (vtables 0x013ec458 -> 0x013f0958 -> derived).
struct cValidationRoot {
    uint32_t mField;        // +4
    virtual ~cValidationRoot() {}
    cValidationRoot() : mField(0) {}
};
struct cValidationBase : cValidationRoot {
    virtual ~cValidationBase() {}
    cValidationBase() {}
};

namespace SP {

// @ 0x00557FC0
class cContentValidationSummarizer {
public:
    void* vptr;             // +0
    uint32_t mField;        // +4
    cContentValidationSummarizer();
    uint32_t GetResType(int arg);
};
cContentValidationSummarizer::cContentValidationSummarizer()
{
    vptr = g_vtbl_Summarizer;
    mField = 0;
    vptr = g_vtbl_ScalarDeleting;
    vptr = g_vtbl_SummarizerFinal;
}

// @ 0x00558080
uint32_t cContentValidationSummarizer::GetResType(int arg) {
    switch (arg) {
    case 0: return 0x3d97a8e4;
    case 1: return 0x2b978c46;
    case 2: return 0x2399be55;
    case 3: return 0x24682294;
    case 4: return 0x476a98c7;
    }
    return 0xffffffff;
}

namespace W1G2_57 {

// Content-validation summarizer for editor "W1G2" resources: ten resource keys,
// a given key is "allowed" when it matches none of the eight blacklisted ones.
class c557c90 : public cValidationBase {
public:
    ResourceKey mKeyA;          // +0x08 (read from property 0x195e035)
    ResourceKey mKey0, mKey1, mKey2, mKey3, mKey4, mKey5, mKey6, mKey7;   // +0x14 .. +0x68
    virtual ~c557c90() {}
    c557c90();                                      // 0x005570d0
    bool IsAllowed(const ResourceKey& key, int);    // 0x00557cf0
    uint32_t GetResType(int arg);                   // 0x00557c90
};

inline bool operator==(const ResourceKey& a, const ResourceKey& b)
{
    return a.instanceID == b.instanceID && a.typeID == b.typeID && a.groupID == b.groupID;
}

// @ 0x00557C90
uint32_t c557c90::GetResType(int arg) {
    switch (arg) {
    case 0: return 0x476a98c7;
    case 1: return 0x2399be55;
    case 2: return 0x2b978c46;
    case 3: return 0x24682294;
    }
    return 0xffffffff;
}

// @ 0x005570D0
// Local names here (h, p33, elem, count, q, n3, ...) are a name-hash fit that reproduces the
// original /Od stack-slot order; the roles are: h = property-file id, p33 = property list,
// count = hashed int property, q..t22 = the eight property ids.
c557c90::c557c90()
{
    const uint32_t h = 0x280852f1;
    intrusive_ptr<PropertyList> p33(0);
    PropertyManager_Get()->GetPropertyList(h, 0x2ae0c7e, p33.Out());
    if (p33.get()) {
        uint32_t n9 = 0x4ea8a07;
        int count = 0;
        ReadIntProperty(p33.get(), n9, count);
        mKey0 = MakeSuffixKey(count, 0x476a98c7, 0x65, 0x62);
        uint32_t q = 0x4ea8f1a;
        uint32_t n3 = 0x65cce6d;
        uint32_t v13 = 0x65cce70;
        uint32_t v40 = 0x65cce73;
        uint32_t v34 = 0x65cf1b6;
        uint32_t n29 = 0x65e3a82;
        uint32_t t22 = 0x65e3a85;
        int v20 = 0;
        ReadIntProperty(p33.get(), q, v20);
        mKey1 = MakeSuffixKey(v20, 0x2399be55, 0x63, 0x62);
        ReadIntProperty(p33.get(), n3, v20);
        mKey2 = MakeSuffixKey(v20, 0x2399be55, 0x63, 0x62);
        ReadIntProperty(p33.get(), v13, v20);
        mKey3 = MakeSuffixKey(v20, 0x2399be55, 0x63, 0x62);
        ReadIntProperty(p33.get(), v40, v20);
        mKey4 = MakeSuffixKey(v20, 0x2399be55, 0x63, 0x62);
        ReadIntProperty(p33.get(), v34, v20);
        mKey5 = MakeSuffixKey(v20, 0x24682294, 0x64, 0x62);
        ReadIntProperty(p33.get(), t22, v20);
        mKey6 = MakeSuffixKey(v20, 0x24682294, 0x64, 0x62);
        ReadIntProperty(p33.get(), n29, v20);
        mKey7 = MakeSuffixKey(v20, 0x24682294, 0x64, 0x62);
    }
    p33 = 0;
    PropertyManager_Get()->GetPropertyList(0xcdf8d12f, 0x2ae0c7e, p33.Out());
    const uint32_t elem = 0x195e035;
    GetPropertyAsKey(p33.get(), elem, &mKeyA);
}

// @ 0x00557CF0
bool c557c90::IsAllowed(const ResourceKey& key, int)
{
    if (key == mKey0 || key == mKey1 || key == mKey2 || key == mKey3 || key == mKey4 ||
        key == mKey5 || key == mKey6 || key == mKey7 || key == mKeyA)
        return false;
    else
        return true;
}

}
}
