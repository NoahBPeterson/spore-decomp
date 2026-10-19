// src/game/SPAudio/SPAudioEventModifier.cpp -- migrated from slice(s) s00a39ce0, s00a38e40 by tools/migrate/rewrite.py
// Object file: SPAudio/SPAudioEventModifier.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/Audio/cEventModifier.h"
#include "EA/Audio/Command.h"
#include "EA/Audio/IConfiguration.h"
#include "EA/ResourceMan/Key.h"
#include "EA/Audio/ResponseCurve.h"
#include "rw/audio/core/System.h"
#include "EA/Audio/VoiceContainer.h"
#include "SP/Audio/cEventModifierPrimitive.h"
#include <ctype.h>
#include <string.h>

// ---- items of slice s00a38e40 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define CAT2(a, b) a##b
#define CAT(a, b) CAT2(a, b)
#define V virtual void CAT(pad_, __COUNTER__)();
#define V4 V V V V
#define V16 V4 V4 V4 V4
void* operator new(unsigned int, const char*, int, int, int, int);
void* operator new(unsigned int, const char*, int, int, const char*, int);   // 0x00f473a0
void* operator new(unsigned int);
void operator delete(void*) throw();     // 0x00f47380
void operator delete[](void*);           // 0x00f47380
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
namespace EA {
struct Property {
    uint32_t* mpData;
    int mPad;
    int mnCount;
    int mnSize;
    uint16_t mnFlags;
    uint16_t mnType;
};
}
namespace EA {
struct RbNode {
    RbNode* mpRight;
    RbNode* mpLeft;
    RbNode* mpParent;
    uint32_t mColor;
    uint32_t mKey;
};
}
namespace EA {
struct RbAnchorNode {
    RbNode* mpRight;
    RbNode* mpLeft;
    RbNode* mpParent;
    uint32_t mColor;
};
}
namespace EA {
struct RbTreeData {
    int mAlloc;
    RbAnchorNode mAnchor;
    int mnSize;
    RbTreeData() : mAnchor() {
        mAnchor.mpRight = (RbNode*)&mAnchor;
        mAnchor.mpLeft = (RbNode*)&mAnchor;
        mAnchor.mpParent = 0;
        *(uint8_t*)&mAnchor.mColor = 0;
        mnSize = 0;
    }
    void DoNukeSubtree(RbNode* node);   // 0x009a9600
};
}
namespace EA {
struct IConfiguration {
    virtual void v0();
    virtual void Release();
    virtual void v2();
    virtual void GetKeys(RbTreeData* out, int flags);
    V V V
    virtual void GetProperty(uint32_t key, Property*& out);
    V
    virtual bool GetBool(uint32_t key, bool* out);
    V4 V V
    virtual const char* GetString(uint32_t key);
};
}
namespace EA {
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
}
namespace EA {
uint32_t FNV1_String8(const char* s, uint32_t seed, int flag);
}
namespace EA {
namespace XHTML {
namespace DOM {
struct Node {
    int Type();   // 0x00fc7e50
};
}
}
}
namespace EA {
namespace Audio {
struct Command_s00a3_8e40 : XHTML::DOM::Node {
    bool GetUint32(uint32_t key, uint32_t* out);          // 0x00a0fab0
    void SetUint64(uint32_t key, uint32_t value);         // 0x00a0fcf0
    bool GetString8(uint32_t key, char* out, uint32_t* cap);   // 0x00a0faf0
    void DeleteParameter(uint32_t key);                   // 0x00a0fd70
};
}
}
namespace EA {
namespace Audio {
struct ResponseCurve_s00a3_8e40 {
    void* mpData;        // +0
    char pad4[0xc];      // +4..+0xf
    void* mpInline;      // +0x10
    char pad14[0x350];   // +0x14..+0x363
    ResponseCurve_s00a3_8e40();                          // 0x00a1aa50
    long double GetOutputValue(float x);      // 0x00a1a110
    ~ResponseCurve_s00a3_8e40() { if (mpData && mpData != mpInline) operator delete[](mpData); }
};
}
}
namespace EA {
namespace Audio {
struct AudioSystem {
    V16 V16 V16 V4 V4 V V V                        // slots 0..58
    virtual char* GetFootName(uint32_t id);        // slot 59, +0xec
    virtual void pad60();                          // slot 60, +0xf0
    virtual uint32_t HashName(const char* s);      // slot 61, +0xf4
    V V                                            // slots 62,63
    virtual bool GetFloat(uint32_t key, float* out);   // slot 64, +0x100
    V4 V4 V4 V                                     // slots 65..77
    virtual bool GetConfiguration(uint32_t instance, AutoRefConfig* out, uint32_t group);  // 78, +0x138
    V4 V4 V4 V V V                                 // slots 79..93
    virtual bool GetConfiguration2(uint32_t hash, AutoRefConfig* out);   // 94, +0x178
};
}
}
namespace EA {
namespace Audio {
AudioSystem* GetSystemAT();   // 0x00a206f0
}
}
uint32_t SPIDFromName(const char* s);   // 0x00571cf0
namespace SP {
namespace Audio {
using namespace EA;
}
}
namespace SP {
namespace Audio {
using namespace EA::Audio;
}
}
namespace SP {
namespace Audio {
struct RefCountTemplate {
    int mRefCount;   // +4
    RefCountTemplate() : mRefCount(0) {}
    virtual ~RefCountTemplate() {}
};
}
}
namespace SP {
namespace Audio {
struct IEventModifier {
    virtual ~IEventModifier() {}
    virtual bool Init() = 0;                                              // slot 1, +4
    virtual void Shutdown() = 0;                                          // slot 2, +8
    virtual void ModifyEvent(Command_s00a3_8e40* cmd, int a, char* dst, int cap) = 0; // slot 3, +0xc
    virtual bool ReadTuningValues(const ResourceKey* key) = 0;            // slot 4, +0x10
    virtual int AddRef() = 0;                                             // slot 5, +0x14
    virtual int Release() = 0;                                            // slot 6, +0x18
};
}
}
namespace SP {
namespace Audio {
struct RefCountBase {
    int mRefCount;   // +4 (after the vptr)
    RefCountBase() : mRefCount(0) {}
};
}
}
namespace SP {
namespace Audio {
struct cEventModifierPrimitive_s00a3_8e40 : RefCountBase, IEventModifier {
    ResourceKey mKey;                 // +8
    AutoRefConfig mConfiguration;     // +0x14
    cEventModifierPrimitive_s00a3_8e40(const char* name);   // 0xa3a530
    virtual ~cEventModifierPrimitive_s00a3_8e40();          // 0xa39230
    virtual bool Init();                         // 0xa3a4b0
    virtual void Shutdown();
    virtual void ModifyEvent(Command_s00a3_8e40* cmd, int a, char* dst, int cap);
    virtual bool ReadTuningValues(const ResourceKey* key);  // 0x00a3a610 (SP::Audio::cEventModifierPrimitive::ReadTuningValues)
    virtual int AddRef();
    virtual int Release();
    __declspec(noinline) void Append(char* dst, int cap, char* str, bool sep);  // 0x00a3a4c0 (SP::Audio::cEventModifierPrimitive::Append)
};
}
}
namespace SP {
namespace Audio {
bool cEventModifierPrimitive_s00a3_8e40::Init() { return true; }
}
}
namespace SP {
namespace Audio {
void cEventModifierPrimitive_s00a3_8e40::Shutdown() {}
}
}
namespace SP {
namespace Audio {
void cEventModifierPrimitive_s00a3_8e40::ModifyEvent(Command_s00a3_8e40*, int, char*, int) {}
}
}
namespace SP {
namespace Audio {
bool cEventModifierPrimitive_s00a3_8e40::ReadTuningValues(const ResourceKey*) { return false; }
}
}
namespace SP {
namespace Audio {
int cEventModifierPrimitive_s00a3_8e40::AddRef() { return ++mRefCount; }
}
}
namespace SP {
namespace Audio {
int cEventModifierPrimitive_s00a3_8e40::Release() { return --mRefCount; }
}
}
namespace SP {
namespace Audio {
struct PrimVector {
    cEventModifierPrimitive_s00a3_8e40** mpBegin;
    cEventModifierPrimitive_s00a3_8e40** mpEnd;
    cEventModifierPrimitive_s00a3_8e40** mpCapacity;
    int mAlloc;
    PrimVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~PrimVector() { if (mpBegin) operator delete[](mpBegin); }
    void resize(unsigned n);   // 0xa39f30
    void DoInsertValue(cEventModifierPrimitive_s00a3_8e40** pos, unsigned n, cEventModifierPrimitive_s00a3_8e40** value); // 0xa39a40
};
}
}
namespace SP {
namespace Audio {
struct UIntMap : RbTreeData {
    ~UIntMap() { DoNukeSubtree(mAnchor.mpParent); }
    void Clear() {
        DoNukeSubtree(mAnchor.mpParent);
        mAnchor.mpRight = (RbNode*)&mAnchor;
        mAnchor.mpLeft = (RbNode*)&mAnchor;
        mAnchor.mpParent = 0;
        *(uint8_t*)&mAnchor.mColor = 0;
        mnSize = 0;
    }
};
}
}
namespace SP {
namespace Audio {
struct SoundHashTable {
    int mAlloc;               // +0x18
    void** mpBucketArray;     // +0x1c
    unsigned mnBucketCount;   // +0x20
    unsigned mnElementCount;  // +0x24
    float mfMaxLoadFactor;    // +0x28
    float mfGrowthFactor;     // +0x2c
    unsigned mnNextResize;    // +0x30
    void DoFreeNodes(void** buckets, unsigned count);   // 0xa39c20
};
}
}
namespace SP {
namespace Audio {
struct cEventModifierPrimitiveFootTypeBase : cEventModifierPrimitive_s00a3_8e40 {
    ResponseCurve_s00a3_8e40 mCurves[10];    // +0x18 .. +0x2200
    cEventModifierPrimitiveFootTypeBase(const char* name);   // 0xa39930
    virtual ~cEventModifierPrimitiveFootTypeBase();          // 0xa39770
    virtual void ModifyEventWithFootName(char* footName, Command_s00a3_8e40* cmd, int unused, char* dst, int cap);
    ResponseCurve_s00a3_8e40* Curve(int off) { return (ResponseCurve_s00a3_8e40*)((char*)this + off); }
};
}
}
namespace SP {
namespace Audio {
struct cEventModifier_s00a3_8e40 : RefCountTemplate {
    PrimVector mEventModifiers;   // +8
    int mPad18;                   // +0x18
    UIntMap mModifierMap;         // +0x1c

    cEventModifier_s00a3_8e40();                                        // 0xa398d0
    virtual ~cEventModifier_s00a3_8e40();                               // 0xa39710
    uint32_t ConvertStringToMaskBit(const char* s) throw();  // 0xa390d0
    bool AddPrimitive(uint32_t idx, cEventModifierPrimitive_s00a3_8e40* p);   // 0xa39280
    bool RemovePrimitive(uint32_t idx);                      // 0xa392d0
    void ReleasePrimitives();                                // 0xa39310
    void ModifyEvent(Command_s00a3_8e40* cmd, uint32_t mask, char* name, int extra);   // 0xa39350
    bool CommandResolve(Command_s00a3_8e40* cmd);                       // 0xa39620
    bool Shutdown();                                         // 0xa39c80
};
}
}
    void* operator new(unsigned int, char*, int, int, char*, int); // 0x00f473a0
    void operator delete[](void*); // 0x00f47380
    void operator delete(void*); // 0x00f47380
// ---- items of slice s00a38e40 end

// ---- items of slice s00a39ce0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char gStrEmpty[];                 // 0x1667bac (shared empty eastl string)
extern ResourceKey gEventModifiersKey;   // 0x15535ac
namespace EA {
struct RbTreeData_s00a3_9ce0 {
    int mAlloc;
    RbAnchorNode mAnchor;
    int mnSize;
    RbNode*& mpRight_() { return mAnchor.mpRight; }
    RbTreeData_s00a3_9ce0() : mAnchor() {
        mAnchor.mpRight = (RbNode*)&mAnchor;
        mAnchor.mpLeft = (RbNode*)&mAnchor;
        mAnchor.mpParent = 0;
        *(uint8_t*)&mAnchor.mColor = 0;
        mnSize = 0;
    }
    void DoNukeSubtree(RbNode* node);   // 0x009a9600
};
}
namespace EA {
struct RbTree : RbTreeData_s00a3_9ce0 {
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
}
namespace EA {
struct RbTreeS : RbTreeData_s00a3_9ce0 {
    ~RbTreeS() { DoNukeSubtree(mAnchor.mpParent); }
};
}
namespace EA {
typedef RbTree KeyList;
}
namespace EA {
typedef RbTreeS KeyListS;
}
namespace EA {
struct IConfiguration_s00a3_9ce0 {
    virtual void v0();
    virtual void Release();
    virtual void v2();
    virtual void GetKeys(RbTreeData_s00a3_9ce0* out, int flags);
    V V V
    virtual void GetProperty(uint32_t key, Property*& out);
    V4 V4
    virtual const char* GetString(uint32_t key);
};
}
namespace EA {
struct AutoRefConfig_s00a3_9ce0 {
    IConfiguration_s00a3_9ce0* mp;
    AutoRefConfig_s00a3_9ce0() : mp(0) {}
    ~AutoRefConfig_s00a3_9ce0() { if (mp) mp->Release(); }
    void Reset() {
        IConfiguration_s00a3_9ce0* p = mp;
        if (p) {
            mp = 0;
            p->Release();
        }
    }
};
}
namespace EA {
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
}
namespace EA {
String8 ConvertToString8(const uint32_t* src);   // 0x0093c570 (returns via the hidden result pointer)
}
namespace EA {
RbNode* RBTreeIncrement(RbNode* n);   // 0x00921580
}
namespace EA {
namespace Audio {
struct Command_s00a3_9ce0 {
    bool GetUint32(uint32_t key, uint32_t* out);  // 0x00a0fab0 (EA::Audio::Command::GetUint32)
    bool GetFloat(uint32_t key, float* out);   // 0x00a0fa70 (named GetBool in symbols; reads a float)
    void SetFloat(uint32_t key, float v);  // 0x00a0fd30 (EA::Audio::Command::SetFloat)
};
}
}
namespace EA {
namespace Audio {
struct ResponseCurve_s00a3_9ce0 {
    float GetOutputValue(float x);  // 0x00a1a110 (EA::Audio::ResponseCurve::GetOutputValue)
};
}
}
namespace EA {
namespace Audio {
struct AudioSystem_s00a3_9ce0 {
    V16 V16 V16 V4 V4 V V V
    virtual char* GetFootName(uint32_t id);   // slot 59, +0xec
    virtual void unused60();
    virtual uint32_t HashName(const char* s);       // slot 61, +0xf4
    V16
    virtual bool GetConfiguration(uint32_t instance, AutoRefConfig_s00a3_9ce0* out, uint32_t group);   // slot 78, +0x138
};
}
}
namespace EA {
namespace Audio {
AudioSystem_s00a3_9ce0* GetSystemAT_s00a3_9ce0();
}
}
namespace SP {
namespace Audio {
struct StrPair {
    uint32_t first;
    String8 second;
    StrPair() {}
    StrPair(const uint32_t& key, const String8& value);   // 0x00b209f0
    StrPair(const StrPair& other);   // 0xb20b90 (register-convention helper in the original)
};
}
}
namespace SP {
namespace Audio {
struct RbIter {
    RbNode* mpNode;
    RbIter() {}
    RbIter(const RbIter& x) : mpNode(x.mpNode) {}
};
}
}
namespace SP {
namespace Audio {
struct TrueType {};
}
}
namespace SP {
namespace Audio {
struct StrNode : RbNode {
    String8 mValue;   // +0x14 (mKey at +0x10)
};
}
}
namespace SP {
namespace Audio {
struct StrMap : RbTreeData_s00a3_9ce0 {
    ~StrMap() { DoNukeSubtree(mAnchor.mpParent); }
    void DoNukeSubtree(RbNode* node);   // 0x00e4b990 (string-valued node nuke)
    StrNode* DoCreateNode(const StrPair& value);   // 0xa3a6d0
    String8& operator[](const uint32_t& key);      // 0xa3a9a0
    RbIter find(const uint32_t& key);
    RbIter DoInsertValue(RbIter hint, const StrPair& v, TrueType unique);   // 0x00a3a8b0
    RbNode* anchor() { return (RbNode*)&mAnchor; }
};
}
}
namespace SP {
namespace Audio {
struct UIntMap_s00a3_9ce0 : RbTreeData_s00a3_9ce0 {
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
}
}
namespace SP {
namespace Audio {
struct IEventModifier_s00a3_9ce0 {
    virtual ~IEventModifier_s00a3_9ce0() {}
    virtual bool Init() = 0;
    virtual void pad2() = 0;
    virtual void ModifyEvent(Command_s00a3_9ce0* cmd, int a, char* dst, int capacity) = 0;
    virtual bool ReadTuningValues(const ResourceKey* key) = 0;
};
}
}
namespace SP {
namespace Audio {
struct cEventModifierPrimitive_s00a3_9ce0 : RefCountBase, IEventModifier_s00a3_9ce0 {
    ResourceKey mKey;               // +8
    AutoRefConfig_s00a3_9ce0 mConfiguration;   // +0x14

    cEventModifierPrimitive_s00a3_9ce0(const char* name)
        : mKey(FNV1_String8(name, 0x811c9dc5, 1), 0x2b9f662, 0x21407ee), mConfiguration() {}
    virtual bool Init();                                    // 0xa3a4b0
    virtual void pad2();
    virtual void ModifyEvent(Command_s00a3_9ce0* cmd, int a, char* dst, int capacity);
    virtual bool ReadTuningValues(const ResourceKey* key);  // 0xa3a610
    virtual int AddRef();
    virtual int Release();
    __declspec(noinline) void Append(char* dst, int capacity, char* str, bool sep);   // 0xa3a4c0
};
}
}
namespace SP {
namespace Audio {
bool cEventModifierPrimitive_s00a3_9ce0::ReadTuningValues(const ResourceKey* key) {
    if (key->instanceID == mKey.instanceID && key->typeID == mKey.typeID &&
        key->groupID == mKey.groupID) {
        AudioSystem_s00a3_9ce0* sys = GetSystemAT_s00a3_9ce0();
        mConfiguration.Reset();
        return sys->GetConfiguration(mKey.instanceID, &mConfiguration, 0x21407ee);
    }
    return false;
}
}
}
namespace SP {
namespace Audio {
extern char gMouthTable[];   // 0x0154df28 (the hashtable's shared empty bucket array)
}
}
namespace SP {
namespace Audio {
struct RehashPolicy {
    float mfMaxLoadFactor;    // 1.0
    float mfGrowthFactor;     // 2.0
    unsigned mnNextResize;
    RehashPolicy() : mfMaxLoadFactor(1.0f), mfGrowthFactor(2.0f), mnNextResize(0) {}
};
}
}
namespace SP {
namespace Audio {
struct SoundHashTable_s00a3_9ce0 {
    int mAlloc;               // +0x18
    void** mpBucketArray;     // +0x1c
    unsigned mnBucketCount;   // +0x20
    unsigned mnElementCount;  // +0x24
    RehashPolicy mRehashPolicy;   // +0x28
    explicit SoundHashTable_s00a3_9ce0(unsigned nBucketCount = 0)
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
    ~SoundHashTable_s00a3_9ce0() {
        DoFreeNodes(mpBucketArray, mnBucketCount);
        mnElementCount = 0;
        DoFreeBuckets(mpBucketArray, mnBucketCount);
    }
    static void DoFreeBuckets(void** buckets, unsigned n) {
        if (n > 1) operator delete(buckets);
    }
};
}
}
namespace SP {
namespace Audio {
struct cEventModifierPrimitiveMouthType : cEventModifierPrimitive_s00a3_9ce0 {
    SoundHashTable_s00a3_9ce0 mTable;   // +0x18
    int mPad34;
    __declspec(noinline) cEventModifierPrimitiveMouthType(const char* name);
};
}
}
namespace SP {
namespace Audio {
struct cEventModifierPrimitiveAlias : cEventModifierPrimitive_s00a3_9ce0 {
    StrMap mMap;   // +0x18 (allocator slot) .. +0x2c
    int mPad30;
    cEventModifierPrimitiveAlias() : cEventModifierPrimitive_s00a3_9ce0("alias") {}
    virtual void ModifyEvent(Command_s00a3_9ce0* cmd, int a, char* name, int capacity);   // 0xa3a670
    virtual bool ReadTuningValues(const ResourceKey* key);              // 0xa3aa80
};
}
}
namespace SP {
namespace Audio {
bool cEventModifierPrimitiveAlias::ReadTuningValues(const ResourceKey* key) {
    if (!cEventModifierPrimitive_s00a3_9ce0::ReadTuningValues(key)) return false;
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
}
}
namespace SP {
namespace Audio {
struct cEventModifierPrimitiveFootTypeBase_s00a3_9ce0 : cEventModifierPrimitive_s00a3_9ce0 {
    char mCurves[0x2200 - 0x18];
    cEventModifierPrimitiveFootTypeBase_s00a3_9ce0(const char* name);   // 0xa39930
    virtual ~cEventModifierPrimitiveFootTypeBase_s00a3_9ce0();
    virtual void ModifyEventWithFootName(char* footName, Command_s00a3_9ce0* cmd, int unused, char* dst, int capacity);
    ResponseCurve_s00a3_9ce0* Curve(int off) { return (ResponseCurve_s00a3_9ce0*)((char*)this + off); }
};
}
}
namespace SP {
namespace Audio {
struct cEventModifierPrimitiveFootType : cEventModifierPrimitiveFootTypeBase_s00a3_9ce0 {
    cEventModifierPrimitiveFootType() : cEventModifierPrimitiveFootTypeBase_s00a3_9ce0("footsteps") {}
    virtual void ModifyEvent(Command_s00a3_9ce0* cmd, int a, char* dst, int capacity);   // 0xa3aea0
};
}
}
namespace SP {
namespace Audio {
struct cEventModifierPrimitiveEpicFootType : cEventModifierPrimitiveFootTypeBase_s00a3_9ce0 {
    cEventModifierPrimitiveEpicFootType() : cEventModifierPrimitiveFootTypeBase_s00a3_9ce0("epicfootsteps") {}
    virtual void ModifyEvent(Command_s00a3_9ce0* cmd, int a, char* dst, int capacity);   // 0xa3af20
    virtual bool ReadTuningValues(const ResourceKey* key);                    // 0xa3af80
};
}
}
namespace SP {
namespace Audio {
struct cEventModifierPrimitiveSurfaceType : cEventModifierPrimitive_s00a3_9ce0 {
    cEventModifierPrimitiveSurfaceType() : cEventModifierPrimitive_s00a3_9ce0("surfacetype") {}
    virtual void ModifyEvent(Command_s00a3_9ce0* cmd, int a, char* dst, int capacity);   // 0xa3b9a0
};
}
}
namespace SP {
namespace Audio {
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
}
}
namespace SP {
namespace Audio {
struct PrimVector_s00a3_9ce0 {
    cEventModifierPrimitive_s00a3_9ce0** mpBegin;
    cEventModifierPrimitive_s00a3_9ce0** mpEnd;
    cEventModifierPrimitive_s00a3_9ce0** mpCapacity;
    int mAlloc;
    void resize(unsigned n);   // 0xa39f30
};
}
}
namespace SP {
namespace Audio {
struct cEventModifier_s00a3_9ce0 {
    int mPad0, mPad4;
    PrimVector_s00a3_9ce0 mEventModifiers;   // +8
    int mPad18;
    UIntMap_s00a3_9ce0 mModifierMap;         // +0x1c
    uint32_t ConvertStringToMaskBit(const char* s) throw();   // 0xa390d0
    bool LoadEventModifiersMap();                           // 0xa39ce0
    bool Init();                                            // 0xa3a180
    void ReadTuningValues(const ResourceKey* key);          // 0xa39f90
};
}
}
// ---- items of slice s00a39ce0 end

// @ 0x00a390d0
namespace SP { namespace Audio {
uint32_t cEventModifier_s00a3_8e40::ConvertStringToMaskBit(const char* s) throw()
{
    if (!strcmp("foottype", s)) return 2;
    if (!strcmp("epicfoottype", s)) return 4;
    if (!strcmp("mouthtype", s)) return 8;
    if (!strcmp("surfacetype", s)) return 0x10;
    if (!strcmp("alias", s)) return 0x20;
    return 0;
}
}}  // namespace SP::Audio

// @ 0x00a39230
namespace SP { namespace Audio {
cEventModifierPrimitive_s00a3_8e40::~cEventModifierPrimitive_s00a3_8e40()
{
}
}}  // namespace SP::Audio

// @ 0x00a39280
namespace SP { namespace Audio {
bool cEventModifier_s00a3_8e40::AddPrimitive(uint32_t idx, cEventModifierPrimitive_s00a3_8e40* p)
{
    if (!p) return false;
    if (idx < 6 && !mEventModifiers.mpBegin[idx]) {
        if (!p->Init()) return false;
        mEventModifiers.mpBegin[idx] = p;
        return true;
    }
    return false;
}
}}  // namespace SP::Audio

// @ 0x00a392d0
namespace SP { namespace Audio {
bool cEventModifier_s00a3_8e40::RemovePrimitive(uint32_t idx)
{
    if (idx >= 6) return false;
    if (mEventModifiers.mpBegin[idx]) {
        mEventModifiers.mpBegin[idx]->Shutdown();
        mEventModifiers.mpBegin[idx] = 0;
        return true;
    }
    return false;
}
}}  // namespace SP::Audio

// @ 0x00a39310
namespace SP { namespace Audio {
void cEventModifier_s00a3_8e40::ReleasePrimitives()
{
    for (int i = 0; i < 6; i++) {
        if (mEventModifiers.mpBegin[i]) {
            cEventModifierPrimitive_s00a3_8e40* p = mEventModifiers.mpBegin[i];
            cEventModifierPrimitive_s00a3_8e40*& slot = mEventModifiers.mpBegin[i];
            slot = 0;
            p->Shutdown();
            p->Release();
        }
    }
}
}}  // namespace SP::Audio

// @ 0x00a39350
namespace SP { namespace Audio {
void cEventModifier_s00a3_8e40::ModifyEvent(Command_s00a3_8e40* cmd, uint32_t mask, char* name, int extra)
{
    uint32_t m = mask | 0x20;
    if (*name == 'v') m = mask | 0x28;
    char buf[200];
    strncpy(buf, name, 200);
    for (int i = 1; i < 6; i++) {
        cEventModifierPrimitive_s00a3_8e40* p = mEventModifiers.mpBegin[i];
        if (p && ((m >> i) & 1)) p->ModifyEvent(cmd, m, name, extra);
    }
    if (!(m & 8)) return;
    AudioSystem* sys = GetSystemAT();
    uint32_t key = FNV1_String8(name, 0x811c9dc5, 1);
    AutoRefConfig cfg;
    if (sys->GetConfiguration2(key, &cfg)) return;
    uint32_t v1;
    if (cmd->GetUint32(0x39fb001, &v1) && v1 != 0) return;
    uint32_t v2;
    if (!cmd->GetUint32(0x39f9e01, &v2)) return;
    int len = (int)strlen(name);
    if (name[len - 3] >= 'a' && name[len - 3] <= 'd') name[len - 3] = 'x';
    if (v2 == 1) return;
    uint32_t key3 = FNV1_String8(name, 0x811c9dc5, 1);
    if (sys->GetConfiguration2(key3, &cfg)) return;
    float f;
    if (sys->GetFloat(0x5ac702f0, &f) && f != 0.0f) {
        char saved[200];
        strcpy(saved, name);
        cmd->SetUint64(0x39f9e01, 1);
        ModifyEvent(cmd, m, name, extra);
        cmd->SetUint64(0x39f9e01, v2);
    }
    uint32_t key4 = FNV1_String8(name, 0x811c9dc5, 1);
    if (sys->GetConfiguration2(key4, &cfg)) return;
    uint32_t v4;
    if (cmd->GetUint32(0x39f9e08, &v4) && v4 >= 5) {
        char saved2[200];
        strcpy(saved2, name);
        cmd->SetUint64(0x39f9e08, 0);
        ModifyEvent(cmd, m, name, extra);
        cmd->SetUint64(0x39f9e08, v4);
        uint32_t id = SPIDFromName(name);
        AutoRefConfig cfg2;
        if (!sys->GetConfiguration(id, &cfg2, 0x21407ee) || !cfg2.mp) {
            strcpy(name, saved2);
            return;
        }
        bool flag = false;
        if (cfg2.mp->GetBool(0x9ef6a6ff, &flag) && flag) return;
        strcpy(name, saved2);
    }
}
}}  // namespace SP::Audio

// @ 0x00a39620
namespace SP { namespace Audio {
bool cEventModifier_s00a3_8e40::CommandResolve(Command_s00a3_8e40* cmd)
{
    if (cmd->Type() != 0x3475365) return false;
    AudioSystem* sys = GetSystemAT();
    char buf[200];
    uint32_t cap = 200;
    if (!cmd->GetString8(0x347537e, buf, &cap)) return false;
    cmd->DeleteParameter(0x347537e);
    uint32_t key = sys->HashName(buf);
    RbNode* anchor = (RbNode*)&mModifierMap.mAnchor;
    RbNode* node = mModifierMap.mAnchor.mpParent;
    RbNode* found = anchor;
    while (node) {
        if (!(node->mKey < key)) { found = node; node = node->mpLeft; }
        else node = node->mpRight;
    }
    uint32_t v = (found == anchor) ? 0 : *(uint32_t*)((char*)found + 0x14);
    ModifyEvent(cmd, v, buf, 200);
    uint32_t k2 = sys->HashName(buf);
    cmd->SetUint64(0x3475381, k2);
    return true;
}
}}  // namespace SP::Audio

// @ 0x00a39710
SP::Audio::cEventModifier::~cEventModifier()
{}

// @ 0x00a39770
namespace SP { namespace Audio {
cEventModifierPrimitiveFootTypeBase::~cEventModifierPrimitiveFootTypeBase()
{}
}}  // namespace SP::Audio

// @ 0x00a398d0
namespace SP { namespace Audio {
cEventModifier_s00a3_8e40::cEventModifier_s00a3_8e40()
: RefCountTemplate(), mModifierMap() {}
}}  // namespace SP::Audio

// @ 0x00a39930
namespace SP { namespace Audio {
cEventModifierPrimitiveFootTypeBase::cEventModifierPrimitiveFootTypeBase(const char* name)
: cEventModifierPrimitive_s00a3_8e40(name) {}
}}  // namespace SP::Audio

// @ 0x00a39a40
namespace SP { namespace Audio {
void PrimVector::DoInsertValue(cEventModifierPrimitive_s00a3_8e40** position, unsigned n, cEventModifierPrimitive_s00a3_8e40** value)
{
    if (n > (unsigned)(mpCapacity - mpEnd)) {
        unsigned oldSize = (unsigned)(mpEnd - mpBegin);
        unsigned newCap = oldSize ? oldSize * 2 : 1;
        unsigned need = oldSize + n;
        unsigned alloc = need > newCap ? need : newCap;
        cEventModifierPrimitive_s00a3_8e40** nd = (cEventModifierPrimitive_s00a3_8e40**)
            operator new(alloc * 4, "EASTL", 0, 0, kEastlFile, 0xd1);
        unsigned pb = (unsigned)(position - mpBegin);
        memcpy(nd, mpBegin, pb * 4);
        cEventModifierPrimitive_s00a3_8e40* v = *value;
        for (unsigned i = 0; i < n; i++) nd[pb + i] = v;
        memcpy(nd + pb + n, position, (unsigned)(mpEnd - position) * 4);
        if (mpBegin) operator delete[](mpBegin);
        mpBegin = nd;
        mpEnd = nd + oldSize + n;
        mpCapacity = nd + alloc;
        return;
    }
    if (n == 0) return;
    cEventModifierPrimitive_s00a3_8e40* v = *value;
    unsigned after = (unsigned)(mpEnd - position);
    if (n < after) {
        memcpy(mpEnd, mpEnd - n, n * 4);
        mpEnd += n;
        memmove(position + n, position, (after - n) * 4);
        for (unsigned i = 0; i < n; i++) position[i] = v;
    } else {
        unsigned extra = n - after;
        for (unsigned i = 0; i < extra; i++) mpEnd[i] = v;
        mpEnd += extra;
        memcpy(mpEnd, position, after * 4);
        mpEnd += after;
        for (unsigned i = 0; i < after; i++) position[i] = v;
    }
}
}}  // namespace SP::Audio

// @ 0x00a39c20
namespace SP { namespace Audio {
void SoundHashTable::DoFreeNodes(void** buckets, unsigned count)
{
    for (unsigned i = 0; i < count; i++) {
        void* node = buckets[i];
        while (node) {
            void* next = *(void**)((char*)node + 0x14);
            char* begin = *(char**)((char*)node + 4);
            if ((*(int*)((char*)node + 0xc) - (int)begin) > 1 && begin)
                operator delete[](begin);
            operator delete(node);
            node = next;
        }
        buckets[i] = 0;
    }
}
}}  // namespace SP::Audio

// @ 0x00a39ce0
namespace SP { namespace Audio {
bool cEventModifier_s00a3_9ce0::LoadEventModifiersMap()
{
    AutoRefConfig_s00a3_9ce0 cfg;
    AudioSystem_s00a3_9ce0* sys = GetSystemAT_s00a3_9ce0();
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
}}  // namespace SP::Audio

// @ 0x00a3a070
namespace SP { namespace Audio {
cEventModifierPrimitiveMouthType::cEventModifierPrimitiveMouthType(const char* name)
: cEventModifierPrimitive_s00a3_9ce0(name) {}
}}  // namespace SP::Audio

// @ 0x00a3a180
namespace SP { namespace Audio {
bool cEventModifier_s00a3_9ce0::Init()
{
    mEventModifiers.resize(6);
    LoadEventModifiersMap();
    AutoRef<cEventModifierPrimitive_s00a3_9ce0> prim;
    PrimVector_s00a3_9ce0* vec = &mEventModifiers;

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
}}  // namespace SP::Audio

// @ 0x00a3a670
namespace SP { namespace Audio {
void cEventModifierPrimitiveAlias::ModifyEvent(Command_s00a3_9ce0* cmd, int a, char* name, int capacity)
{
    AudioSystem_s00a3_9ce0* sys = GetSystemAT_s00a3_9ce0();
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
}}  // namespace SP::Audio
