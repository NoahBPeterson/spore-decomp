// SP::Audio::cEventModifier and its primitives (0xa39ce0-0xa3af20).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE. Callees outside the slice are masked relocations,
// so they are declared with the right calling convention only.
#include "types.h"
#include <ctype.h>
#include <string.h>

#define CAT2(a, b) a##b
#define CAT(a, b) CAT2(a, b)
#define V virtual void CAT(pad_, __COUNTER__)();
#define V4 V V V V
#define V16 V4 V4 V4 V4

void* operator new(unsigned int, const char*, int, int, int, int);
void* operator new(unsigned int, const char*, int, int, const char*, int);   // 0x00f473a0
void* operator new(unsigned int);
void operator delete(void*) throw();     // 0x00f47380
void operator delete[](void*);   // 0x00f47380
void operator delete(void*, const char*, int, int, int, int);
void operator delete(void*, const char*, int, int, const char*, int);
inline void* operator new(unsigned int, void* p) { return p; }
inline void operator delete(void*, void*) {}

#define kEastlFile \
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

struct ResourceKey {
    uint32_t instanceID, typeID, groupID;
    ResourceKey(uint32_t i, uint32_t t, uint32_t g) : instanceID(i), typeID(t), groupID(g) {}
};
extern ResourceKey gEventModifiersKey;   // 0x15535ac
extern char* gDefaultFootName;     // 0x155362c
extern char* gEpicFootName;        // 0x1553634
extern char gStrEmpty[];                 // 0x1667bac (shared empty eastl string)
extern char gStrSurfaceA[];              // 0x1433614
extern char gStrSurfaceB[];              // 0x141c53c

namespace EA {
struct Property {
    uint32_t* mpData;
    int mPad;
    int mnCount;
    int mnSize;
    uint16_t mnFlags;
    uint16_t mnType;
};
// eastl::rbtree node of a map/set: right, left, parent, color, then the key.
struct RbNode {
    RbNode* mpRight;
    RbNode* mpLeft;
    RbNode* mpParent;
    uint32_t mColor;
    uint32_t mKey;
};
// Tree object: allocator slot, then the anchor node (right, left, parent, color) and the size.
struct RbAnchorNode {
    RbNode* mpRight;
    RbNode* mpLeft;
    RbNode* mpParent;
    uint32_t mColor;
};
struct RbTreeData {
    int mAlloc;
    RbAnchorNode mAnchor;
    int mnSize;
    RbNode*& mpRight_() { return mAnchor.mpRight; }
    RbTreeData() : mAnchor() {
        mAnchor.mpRight = (RbNode*)&mAnchor;
        mAnchor.mpLeft = (RbNode*)&mAnchor;
        mAnchor.mpParent = 0;
        *(uint8_t*)&mAnchor.mColor = 0;
        mnSize = 0;
    }
    void DoNukeSubtree(RbNode* node);   // 0x009a9600
};
// Destructor with the nuke loop inlined.
struct RbTree : RbTreeData {
    ~RbTree() {
        RbNode* n = mAnchor.mpParent;
        while (n) {
            DoNukeSubtree(n->mpRight);
            RbNode* l = n->mpLeft;
            operator delete(n);
            n = l;
        }
    }
};
// Destructor with one out-of-line DoNukeSubtree call.
struct RbTreeS : RbTreeData {
    ~RbTreeS() { DoNukeSubtree(mAnchor.mpParent); }
};
typedef RbTree KeyList;
typedef RbTreeS KeyListS;

struct IConfiguration {
    virtual void v0();
    virtual void Release();
    virtual void v2();
    virtual void GetKeys(RbTreeData* out, int flags);
    V V V
    virtual void GetProperty(uint32_t key, Property*& out);
    V4 V4
    virtual const char* GetString(uint32_t key);
};
struct AutoRefConfig {
    IConfiguration* mp;
    AutoRefConfig() : mp(0) {}
    ~AutoRefConfig() { if (mp) mp->Release(); }
    void Reset() {
        IConfiguration* p = mp;
        if (p) {
            mp = 0;
            p->Release();
        }
    }
};
struct String8 {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    int mAlloc;
    String8() {
        mpBegin = gStrEmpty;
        mpEnd = gStrEmpty;
        mpCapacity = gStrEmpty + 1;
    }
    String8(const char* s) {
        const char* e = s;
        while (*e++) {}
        unsigned n = (unsigned)(e - (s + 1));
        unsigned size = n + 1;
        char* p;
        char* cap;
        if (size > 1) {
            p = (char*)operator new(size, "EASTL", 0, 0, kEastlFile, 0xd1);
            cap = p + size;
        } else {
            p = gStrEmpty;
            cap = gStrEmpty + 1;
        }
        mpBegin = p;
        mpCapacity = cap;
        memcpy(p, s, n);
        mpEnd = p + n;
        *mpEnd = 0;
    }
    ~String8() { if (mpCapacity - mpBegin > 1 && mpBegin) operator delete[](mpBegin); }
    void assign(const char* b, const char* e);   // 0x00454cb0
    String8& operator=(const String8& x) {
        if (this != &x) assign(x.mpBegin, x.mpEnd);
        return *this;
    }
};
String8 ConvertToString8(const uint32_t* src);   // 0x0093c570 (returns via the hidden result pointer)
uint32_t FNV1_String8(const char* s, uint32_t seed, int flag);
RbNode* RBTreeIncrement(RbNode* n);   // 0x00921580

namespace Audio {
struct Command {
    bool GetUint32(uint32_t key, uint32_t* out);
    bool GetFloat(uint32_t key, float* out);   // 0x00a0fa70 (named GetBool in symbols; reads a float)
    void SetFloat(uint32_t key, float v);
};
struct ResponseCurve {
    float GetOutputValue(float x);
};
struct AudioSystem {
    V16 V16 V16 V4 V4 V V V
    virtual char* GetFootName(uint32_t id);   // slot 59, +0xec
    virtual void unused60();
    virtual uint32_t HashName(const char* s);       // slot 61, +0xf4
    V16
    virtual bool GetConfiguration(uint32_t instance, AutoRefConfig* out, uint32_t group);   // slot 78, +0x138
};
AudioSystem* GetSystemAT();
}
}

namespace SP { namespace Audio {

using namespace EA;
using namespace EA::Audio;

struct StrPair {
    uint32_t first;
    String8 second;
    StrPair() {}
    StrPair(const uint32_t& key, const String8& value);   // 0x00b209f0
    StrPair(const StrPair& other);   // 0xb20b90 (register-convention helper in the original)
};
struct RbIter {
    RbNode* mpNode;
    RbIter() {}
    RbIter(const RbIter& x) : mpNode(x.mpNode) {}
};
struct TrueType {};
struct StrNode : RbNode {
    String8 mValue;   // +0x14 (mKey at +0x10)
};

struct StrMap : RbTreeData {
    ~StrMap() { DoNukeSubtree(mAnchor.mpParent); }
    void DoNukeSubtree(RbNode* node);   // 0x00e4b990 (string-valued node nuke)
    StrNode* DoCreateNode(const StrPair& value);   // 0xa3a6d0
    String8& operator[](const uint32_t& key);      // 0xa3a9a0
    RbIter find(const uint32_t& key);
    RbIter DoInsertValue(RbIter hint, const StrPair& v, TrueType unique);   // 0x00a3a8b0
    RbNode* anchor() { return (RbNode*)&mAnchor; }
};

struct UIntMap : RbTreeData {
    uint32_t& operator[](const uint32_t& key);   // 0x00a2e060
    void Clear() {
        DoNukeSubtree(mAnchor.mpParent);
        mAnchor.mpRight = (RbNode*)&mAnchor;
        mAnchor.mpLeft = (RbNode*)&mAnchor;
        mAnchor.mpParent = 0;
        *(uint8_t*)&mAnchor.mColor = 0;
        mnSize = 0;
    }
};

struct IEventModifier {
    virtual ~IEventModifier() {}
    virtual bool Init() = 0;
    virtual void pad2() = 0;
    virtual void ModifyEvent(Command* cmd, int a, char* dst, int capacity) = 0;
    virtual bool ReadTuningValues(const ResourceKey* key) = 0;
};

struct RefCountBase {
    int mRefCount;   // +4 (after the vptr)
    RefCountBase() : mRefCount(0) {}
};

struct cEventModifierPrimitive : RefCountBase, IEventModifier {
    ResourceKey mKey;               // +8
    AutoRefConfig mConfiguration;   // +0x14

    cEventModifierPrimitive(const char* name)
        : mKey(FNV1_String8(name, 0x811c9dc5, 1), 0x2b9f662, 0x21407ee), mConfiguration() {}
    virtual bool Init();                                    // 0xa3a4b0
    virtual void pad2();
    virtual void ModifyEvent(Command* cmd, int a, char* dst, int capacity);
    virtual bool ReadTuningValues(const ResourceKey* key);  // 0xa3a610
    virtual int AddRef();
    virtual int Release();
    __declspec(noinline) void Append(char* dst, int capacity, char* str, bool sep);   // 0xa3a4c0
};

// 0xa3a4b0
bool cEventModifierPrimitive::Init() {
    ReadTuningValues(&mKey);
    return true;
}

// @ 0xa3a4c0
void cEventModifierPrimitive::Append(char* dst, int capacity, char* str, bool sep) {
    unsigned dstLen = strlen(dst);
    int n = (strlen(str) + sep) ? 1 : (int)dstLen;
    if (n < capacity) {
        if (sep) dst[dstLen++] = '_';
        strcpy(dst + dstLen, str);
    }
}

// 0xa3a530 is the cEventModifierPrimitive constructor above; 0xa3a5b0 is its scalar deleting destructor.

// 0xa3a610
bool cEventModifierPrimitive::ReadTuningValues(const ResourceKey* key) {
    if (key->instanceID == mKey.instanceID && key->typeID == mKey.typeID &&
        key->groupID == mKey.groupID) {
        AudioSystem* sys = GetSystemAT();
        mConfiguration.Reset();
        return sys->GetConfiguration(mKey.instanceID, &mConfiguration, 0x21407ee);
    }
    return false;
}

extern char gMouthTable[];   // 0x0154df28 (the hashtable's shared empty bucket array)

// eastl::prime_rehash_policy
struct RehashPolicy {
    float mfMaxLoadFactor;    // 1.0
    float mfGrowthFactor;     // 2.0
    unsigned mnNextResize;
    RehashPolicy() : mfMaxLoadFactor(1.0f), mfGrowthFactor(2.0f), mnNextResize(0) {}
};

// eastl::hashtable<uint, pair<const uint, string>, SP_STL_Sound, ...>
struct SoundHashTable {
    int mAlloc;               // +0x18
    void** mpBucketArray;     // +0x1c
    unsigned mnBucketCount;   // +0x20
    unsigned mnElementCount;  // +0x24
    RehashPolicy mRehashPolicy;   // +0x28
    explicit SoundHashTable(unsigned nBucketCount = 0)
        : mnBucketCount(0), mnElementCount(0), mRehashPolicy() {
        if (nBucketCount < 2) {
            reset();
        } else {
            mnBucketCount = nBucketCount;
            mpBucketArray = DoAllocateBuckets(nBucketCount);
        }
    }
    void** DoAllocateBuckets(unsigned n);
    void reset() {
        mnBucketCount = 1;
        mpBucketArray = (void**)gMouthTable;
        mnElementCount = 0;
        mRehashPolicy.mnNextResize = 0;
    }
    void DoFreeNodes(void** buckets, unsigned count) throw();   // 0xa39c20
    ~SoundHashTable() {
        DoFreeNodes(mpBucketArray, mnBucketCount);
        mnElementCount = 0;
        DoFreeBuckets(mpBucketArray, mnBucketCount);
    }
    static void DoFreeBuckets(void** buckets, unsigned n) {
        if (n > 1) operator delete(buckets);
    }
};

struct cEventModifierPrimitiveMouthType : cEventModifierPrimitive {
    SoundHashTable mTable;   // +0x18
    int mPad34;
    __declspec(noinline) cEventModifierPrimitiveMouthType(const char* name);
};

// 0xa3a070
cEventModifierPrimitiveMouthType::cEventModifierPrimitiveMouthType(const char* name)
    : cEventModifierPrimitive(name) {}

// 0xa3a0e0 cEventModifierPrimitiveMouthType::~cEventModifierPrimitiveMouthType (implicit destructor, called by its scalar deleting destructor at 0xa3a160)

struct cEventModifierPrimitiveAlias : cEventModifierPrimitive {
    StrMap mMap;   // +0x18 (allocator slot) .. +0x2c
    int mPad30;
    cEventModifierPrimitiveAlias() : cEventModifierPrimitive("alias") {}
    virtual void ModifyEvent(Command* cmd, int a, char* name, int capacity);   // 0xa3a670
    virtual bool ReadTuningValues(const ResourceKey* key);              // 0xa3aa80
};

// 0xa39ff0 cEventModifierPrimitiveAlias::~cEventModifierPrimitiveAlias (implicit destructor, called by its scalar deleting destructor)

// 0xa3a670
void cEventModifierPrimitiveAlias::ModifyEvent(Command* cmd, int a, char* name, int capacity) {
    AudioSystem* sys = GetSystemAT();
    a = (int)sys->HashName(name);   // the original reuses a dead argument slot for the key
    RbIter it = mMap.find((uint32_t&)a);
    if (it.mpNode != mMap.anchor()) {
        const char* s = ((StrNode*)it.mpNode)->mValue.mpBegin;
        char* d = name;
        char c;
        do {
            c = *s;
            *d = c;
            s++;
            d++;
        } while (c != 0);
    }
}

// 0xa3a6d0
StrNode* StrMap::DoCreateNode(const StrPair& value) {
    StrNode* p = (StrNode*)operator new(0x24, "EASTL", 0, 0, kEastlFile, 0xd1);
    new (&p->mKey) StrPair(value);
    return p;
}

// @ 0xa3a9a0 (eastl::map::operator[]: lower_bound, then insert(hint, value_type(key, T())))
String8& StrMap::operator[](const uint32_t& key) {
    RbNode* pRangeEnd = anchor();
    RbNode* pCurrent = mAnchor.mpParent;
    while (pCurrent) {
        if (!(pCurrent->mKey < key)) {
            pRangeEnd = pCurrent;
            pCurrent = pCurrent->mpLeft;
        } else {
            pCurrent = pCurrent->mpRight;
        }
    }
    RbIter itLower;
    itLower.mpNode = pRangeEnd;
    if (itLower.mpNode == anchor() || key < itLower.mpNode->mKey)
        itLower = DoInsertValue(itLower, StrPair(key, String8()), TrueType());
    return ((StrNode*)itLower.mpNode)->mValue;
}

// 0xa3aa80
bool cEventModifierPrimitiveAlias::ReadTuningValues(const ResourceKey* key) {
    if (!cEventModifierPrimitive::ReadTuningValues(key)) return false;
    if (mConfiguration.mp) {
        KeyListS keys;
        mConfiguration.mp->GetKeys(&keys, 1);
        RbNode* it = keys.mAnchor.mpLeft;
        RbNode* end = (RbNode*)&keys.mAnchor;
        while (it != end) {
            uint32_t k = it->mKey;
            const char* str = mConfiguration.mp->GetString(k);
            if (str) {
                String8 s(str);
                mMap[k] = s;
            }
            it = RBTreeIncrement(it);
        }
    }
    return true;
}

struct cEventModifierPrimitiveFootTypeBase : cEventModifierPrimitive {
    char mCurves[0x2200 - 0x18];
    cEventModifierPrimitiveFootTypeBase(const char* name);   // 0xa39930
    virtual ~cEventModifierPrimitiveFootTypeBase();
    virtual void ModifyEventWithFootName(char* footName, Command* cmd, int unused, char* dst, int capacity);
    ResponseCurve* Curve(int off) { return (ResponseCurve*)((char*)this + off); }
};

// 0xa3ac40
void cEventModifierPrimitiveFootTypeBase::ModifyEventWithFootName(char* footName, Command* cmd,
                                                                  int unused, char* dst, int capacity) {
    uint32_t hasName = 0;
    if (!cmd->GetUint32(0x48def6d, &hasName) || hasName == 0) {
        uint32_t id;
        cmd->GetUint32(0x39fa0ab, &id);
        GetSystemAT()->GetFootName(id);
    }
    if (!footName) footName = gDefaultFootName;
    Append(dst, capacity, footName, true);
    uint32_t surface;
    cmd->GetUint32(0x39fa0b1, &surface);
    char* s = (surface & 1) ? gStrSurfaceA : gStrSurfaceB;
    Append(dst, capacity, s, true);
    GetSystemAT();
    uint32_t speed;
    float b1, b2, b3, b4;
    cmd->GetUint32(0x39fa0b8, &speed);
    cmd->GetFloat(0x39fa0be, &b1);
    cmd->GetFloat(0x39fa0c4, &b2);
    cmd->GetFloat(0x39fa0ca, &b3);
    cmd->GetFloat(0x39fa0cf, &b4);
    float r1 = Curve(0x18)->GetOutputValue((float)speed);
    float r2 = Curve(0x6e0)->GetOutputValue(b1);
    float r3 = Curve(0xa44)->GetOutputValue(b2);
    float r4 = Curve(0x37c)->GetOutputValue(b4);
    float r5 = Curve(0xda8)->GetOutputValue(b3);
    float r6 = Curve(0x17d4)->GetOutputValue(b3);
    float r7 = Curve(0x1b38)->GetOutputValue(b1);
    float r8 = Curve(0x1e9c)->GetOutputValue(b2);
    float r9 = Curve(0x110c)->GetOutputValue(b1);
    float r10 = Curve(0x1470)->GetOutputValue(b2) * r9;
    cmd->SetFloat(0x25df0108, r5 * r4 * r3 * r2 * r1);
    cmd->SetFloat(0x71bc3009, r10);
    cmd->SetFloat(0xa26a765f, r8 * r7 * r6);
}

struct cEventModifierPrimitiveFootType : cEventModifierPrimitiveFootTypeBase {
    cEventModifierPrimitiveFootType() : cEventModifierPrimitiveFootTypeBase("footsteps") {}
    virtual void ModifyEvent(Command* cmd, int a, char* dst, int capacity);   // 0xa3aea0
};

struct cEventModifierPrimitiveEpicFootType : cEventModifierPrimitiveFootTypeBase {
    cEventModifierPrimitiveEpicFootType() : cEventModifierPrimitiveFootTypeBase("epicfootsteps") {}
    virtual void ModifyEvent(Command* cmd, int a, char* dst, int capacity);   // 0xa3af20
    virtual bool ReadTuningValues(const ResourceKey* key);                    // 0xa3af80
};

// 0xa3aea0
void cEventModifierPrimitiveFootType::ModifyEvent(Command* cmd, int a, char* dst, int capacity) {
    uint32_t hasName = 0;
    if (!cmd->GetUint32(0x48def6d, &hasName) || hasName == 0) {
        uint32_t id;
        cmd->GetUint32(0x39fa0ab, &id);
        char* name = GetSystemAT()->GetFootName(id);
        ModifyEventWithFootName(name, cmd, a, dst, capacity);
    }
}

// 0xa3af20
void cEventModifierPrimitiveEpicFootType::ModifyEvent(Command* cmd, int a, char* dst, int capacity) {
    uint32_t hasName = 0;
    if (cmd->GetUint32(0x48def6d, &hasName) && hasName != 0)
        ModifyEventWithFootName(gEpicFootName, cmd, a, dst, capacity);
}

struct cEventModifierPrimitiveSurfaceType : cEventModifierPrimitive {
    cEventModifierPrimitiveSurfaceType() : cEventModifierPrimitive("surfacetype") {}
    virtual void ModifyEvent(Command* cmd, int a, char* dst, int capacity);   // 0xa3b9a0
};

// Reference-counted pointer as used by cEventModifier::Init.
template <class T>
struct AutoRef {
    T* mp;
    AutoRef() : mp(0) {}
    ~AutoRef() { if (mp) mp->Release(); }
    AutoRef& operator=(T* p) {
        if (p != mp) {
            T* old = mp;
            if (p) p->AddRef();
            mp = p;
            if (old) old->Release();
        }
        return *this;
    }
    T* operator->() { return mp; }
};

struct PrimVector {
    cEventModifierPrimitive** mpBegin;
    cEventModifierPrimitive** mpEnd;
    cEventModifierPrimitive** mpCapacity;
    int mAlloc;
    void resize(unsigned n);   // 0xa39f30
};

struct cEventModifier {
    int mPad0, mPad4;
    PrimVector mEventModifiers;   // +8
    int mPad18;
    UIntMap mModifierMap;         // +0x1c
    uint32_t ConvertStringToMaskBit(const char* s) throw();   // 0xa390d0
    bool LoadEventModifiersMap();                           // 0xa39ce0
    bool Init();                                            // 0xa3a180
    void ReadTuningValues(const ResourceKey* key);          // 0xa39f90
};

// 0xa39ce0
bool cEventModifier::LoadEventModifiersMap() {
    AutoRefConfig cfg;
    AudioSystem* sys = GetSystemAT();
    cfg.Reset();
    if (!sys->GetConfiguration(gEventModifiersKey.instanceID, &cfg, 0x21407ee)) return false;
    mModifierMap.Clear();
    KeyList keys;
    cfg.mp->GetKeys(&keys, 1);
    RbNode* it = keys.mAnchor.mpLeft;
    RbNode* end = (RbNode*)&keys.mAnchor;
    while (it != end) {
        uint32_t key = it->mKey;
        Property* prop;
        cfg.mp->GetProperty(key, prop);
        if (prop->mnType == 0x13) {
            uint32_t mask = 0;
            uint16_t multi = prop->mnFlags & 0x30;
            int count = multi ? prop->mnCount : 1;
            const uint32_t* str = multi ? prop->mpData : (const uint32_t*)prop;
            if (count > 0) {
                do {
                    String8 s = ConvertToString8(str);
                    str += 4;
                    for (char* p = s.mpBegin; p < s.mpEnd; p++) *p = (char)tolower((unsigned char)*p);
                    mask |= ConvertStringToMaskBit(s.mpBegin);
                } while (--count != 0);
            }
            mModifierMap[key] = mask;
        }
        it = RBTreeIncrement(it);
    }
    return true;
}

// 0xa39f90
void cEventModifier::ReadTuningValues(const ResourceKey* key) {
    if (key->instanceID == gEventModifiersKey.instanceID && key->typeID == gEventModifiersKey.typeID &&
        key->groupID == gEventModifiersKey.groupID)
        LoadEventModifiersMap();
    for (int i = 0; i < 0x18; i += 4) {
        cEventModifierPrimitive** p = (cEventModifierPrimitive**)((char*)mEventModifiers.mpBegin + i);
        if (*p) (*p)->ReadTuningValues(key);
    }
}

// @ 0xa3a180
bool cEventModifier::Init() {
    mEventModifiers.resize(6);
    LoadEventModifiersMap();
    AutoRef<cEventModifierPrimitive> prim;
    PrimVector* vec = &mEventModifiers;

    cEventModifierPrimitiveFootType* foot = new ("Audio", 0, 0, 0, 0) cEventModifierPrimitiveFootType;
    prim = foot;
    prim->AddRef();
    if (!vec->mpBegin[1] && prim->Init()) vec->mpBegin[1] = prim.mp;

    cEventModifierPrimitiveEpicFootType* epic = new ("Audio", 0, 0, 0, 0) cEventModifierPrimitiveEpicFootType;
    prim = epic;
    prim->AddRef();
    if (!vec->mpBegin[2] && prim->Init()) vec->mpBegin[2] = prim.mp;

    cEventModifierPrimitiveMouthType* mouth = new ("Audio", 0, 0, 0, 0) cEventModifierPrimitiveMouthType("mouthtype");
    prim = mouth;
    prim->AddRef();
    if (!vec->mpBegin[3] && prim->Init()) vec->mpBegin[3] = prim.mp;

    cEventModifierPrimitiveSurfaceType* surf = new ("Audio", 0, 0, 0, 0) cEventModifierPrimitiveSurfaceType;
    prim = surf;
    prim->AddRef();
    if (!vec->mpBegin[4] && prim->Init()) vec->mpBegin[4] = prim.mp;

    cEventModifierPrimitiveAlias* alias = new ("Audio", 0, 0, 0, 0) cEventModifierPrimitiveAlias;
    prim = alias;
    prim->AddRef();
    if (!vec->mpBegin[5] && prim->Init()) vec->mpBegin[5] = prim.mp;
    return true;
}

}}
// --- equivalence checker address annotations
    void* operator new(unsigned int, char*, int, int, char*, int); // 0x00f473a0
    void operator delete[](void*); // 0x00f47380

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct EA {
    void GetFloat(unsigned int, float*); // 0x00a0fa70
    void RBTreeIncrement(void*); // 0x00921580
    void ConvertToString8(void*, unsigned int*); // 0x0093c570
    void DoNukeSubtree(void*); // 0x009a9600
    void assign(char*, char*); // 0x00454cb0
};
struct SP {
    void gMouthTable(...); // 0x0154df28
};
}
