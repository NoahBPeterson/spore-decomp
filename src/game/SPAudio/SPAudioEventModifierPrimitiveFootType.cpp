// src/game/SPAudio/SPAudioEventModifierPrimitiveFootType.cpp -- migrated from slice(s) s00a39ce0 by tools/migrate/rewrite.py
// Object file: SPAudio/SPAudioEventModifierPrimitiveFootType.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Audio/Command.h"
#include "EA/Audio/IConfiguration.h"
#include "EA/Audio/ResponseCurve.h"
#include "SP/Audio/cEventModifier.h"
#include "SP/Audio/cEventModifierPrimitive.h"

// unnamed retail callees and globals (address in the comment)
extern char* gDefaultFootName;     // 0x155362c
extern char* gEpicFootName;        // 0x1553634
extern char gStrEmpty[];                 // 0x1667bac (shared empty eastl string)
extern char gStrSurfaceA[];              // 0x1433614
extern char gStrSurfaceB[];              // 0x141c53c
#include <ctype.h>
#include <string.h>

// ---- items of slice s00a39ce0 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
}
namespace EA {
struct RbTreeS : RbTreeData {
    ~RbTreeS() { DoNukeSubtree(mAnchor.mpParent); }
};
}
namespace EA {
typedef RbTreeS KeyListS;
}
namespace EA {
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
uint32_t FNV1_String8(const char* s, uint32_t seed, int flag);
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
struct AudioSystem {
    V16 V16 V16 V4 V4 V V V
    virtual char* GetFootName(uint32_t id);   // slot 59, +0xec
    virtual void unused60();
    virtual uint32_t HashName(const char* s);       // slot 61, +0xf4
    V16
    virtual bool GetConfiguration(uint32_t instance, AutoRefConfig* out, uint32_t group);   // slot 78, +0x138
};
}
}
namespace EA {
namespace Audio {
AudioSystem* GetSystemAT();
}
}
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
struct StrMap : RbTreeData {
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
struct IEventModifier {
    virtual ~IEventModifier() {}
    virtual bool Init() = 0;
    virtual void pad2() = 0;
    virtual void ModifyEvent(Command_s00a3_9ce0* cmd, int a, char* dst, int capacity) = 0;
    virtual bool ReadTuningValues(const ResourceKey* key) = 0;
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
struct cEventModifierPrimitive_s00a3_9ce0 : RefCountBase, IEventModifier {
    ResourceKey mKey;               // +8
    AutoRefConfig mConfiguration;   // +0x14

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
        AudioSystem* sys = GetSystemAT();
        mConfiguration.Reset();
        return sys->GetConfiguration(mKey.instanceID, &mConfiguration, 0x21407ee);
    }
    return false;
}
}
}
namespace SP {
namespace Audio {
class cEventModifierPrimitiveAlias : public cEventModifierPrimitive_s00a3_9ce0 { public:
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
class cEventModifierPrimitiveFootTypeBase : public cEventModifierPrimitive_s00a3_9ce0 { public:
    char mCurves[0x2200 - 0x18];
    cEventModifierPrimitiveFootTypeBase(const char* name);   // 0xa39930
    virtual ~cEventModifierPrimitiveFootTypeBase();
    virtual void ModifyEventWithFootName(char* footName, Command_s00a3_9ce0* cmd, int unused, char* dst, int capacity);
    ResponseCurve_s00a3_9ce0* Curve(int off) { return (ResponseCurve_s00a3_9ce0*)((char*)this + off); }
};
}
}
namespace SP {
namespace Audio {
class cEventModifierPrimitiveFootType : public cEventModifierPrimitiveFootTypeBase { public:
    cEventModifierPrimitiveFootType() : cEventModifierPrimitiveFootTypeBase("footsteps") {}
    virtual void ModifyEvent(Command_s00a3_9ce0* cmd, int a, char* dst, int capacity);   // 0xa3aea0
};
}
}
namespace SP {
namespace Audio {
class cEventModifierPrimitiveEpicFootType : public cEventModifierPrimitiveFootTypeBase { public:
    cEventModifierPrimitiveEpicFootType() : cEventModifierPrimitiveFootTypeBase("epicfootsteps") {}
    virtual void ModifyEvent(Command_s00a3_9ce0* cmd, int a, char* dst, int capacity);   // 0xa3af20
    virtual bool ReadTuningValues(const ResourceKey* key);                    // 0xa3af80
};
}
}
    void* operator new(unsigned int, char*, int, int, char*, int); // 0x00f473a0
    void operator delete[](void*); // 0x00f47380
// ---- items of slice s00a39ce0 end

// @ 0x00a3ac40
namespace SP { namespace Audio {
void cEventModifierPrimitiveFootTypeBase::ModifyEventWithFootName(char* footName, Command_s00a3_9ce0* cmd, int unused, char* dst, int capacity)
{
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
}}  // namespace SP::Audio

// @ 0x00a3aea0
namespace SP { namespace Audio {
void cEventModifierPrimitiveFootType::ModifyEvent(Command_s00a3_9ce0* cmd, int a, char* dst, int capacity)
{
    uint32_t hasName = 0;
    if (!cmd->GetUint32(0x48def6d, &hasName) || hasName == 0) {
        uint32_t id;
        cmd->GetUint32(0x39fa0ab, &id);
        char* name = GetSystemAT()->GetFootName(id);
        ModifyEventWithFootName(name, cmd, a, dst, capacity);
    }
}
}}  // namespace SP::Audio

// @ 0x00a3af20
namespace SP { namespace Audio {
void cEventModifierPrimitiveEpicFootType::ModifyEvent(Command_s00a3_9ce0* cmd, int a, char* dst, int capacity)
{
    uint32_t hasName = 0;
    if (cmd->GetUint32(0x48def6d, &hasName) && hasName != 0)
        ModifyEventWithFootName(gEpicFootName, cmd, a, dst, capacity);
}
}}  // namespace SP::Audio
