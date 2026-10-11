// SP::Audio::cEmitterSndPlayer / cEventModifier and primitives (0xa38e40-0xa39c80).
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

extern int gAudioLock;   // 0x016e61a8

namespace EA {
struct Property {
    uint32_t* mpData;
    int mPad;
    int mnCount;
    int mnSize;
    uint16_t mnFlags;
    uint16_t mnType;
};
struct RbNode {
    RbNode* mpRight;
    RbNode* mpLeft;
    RbNode* mpParent;
    uint32_t mColor;
    uint32_t mKey;
};
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
    RbTreeData() : mAnchor() {
        mAnchor.mpRight = (RbNode*)&mAnchor;
        mAnchor.mpLeft = (RbNode*)&mAnchor;
        mAnchor.mpParent = 0;
        *(uint8_t*)&mAnchor.mColor = 0;
        mnSize = 0;
    }
    void DoNukeSubtree(RbNode* node);   // 0x009a9600
};

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
};
uint32_t FNV1_String8(const char* s, uint32_t seed, int flag);
RbNode* RBTreeIncrement(RbNode* n);   // 0x00921580

namespace XHTML { namespace DOM {
struct Node {
    int Type();   // 0x00fc7e50
};
}}
namespace Audio {
struct Command : XHTML::DOM::Node {
    bool GetUint32(uint32_t key, uint32_t* out);          // 0x00a0fab0
    void SetUint64(uint32_t key, uint32_t value);         // 0x00a0fcf0
    bool GetString8(uint32_t key, char* out, uint32_t* cap);   // 0x00a0faf0
    void DeleteParameter(uint32_t key);                   // 0x00a0fd70
};
// The real curve object is 0x364 bytes with a heap buffer; GetOutputValue returns long double
// (x87 st0), so the declared return type must be long double.
struct ResponseCurve {
    void* mpData;        // +0
    char pad4[0xc];      // +4..+0xf
    void* mpInline;      // +0x10
    char pad14[0x350];   // +0x14..+0x363
    ResponseCurve();                          // 0x00a1aa50
    long double GetOutputValue(float x);      // 0x00a1a110
    ~ResponseCurve() { if (mpData && mpData != mpInline) operator delete[](mpData); }
};
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
AudioSystem* GetSystemAT();   // 0x00a206f0

struct EmitterSndPlayer {
    char pad0[0x10];
    ResponseCurve mAttenuationCurve;   // +0x10..+0x373
    char pad374[0x18];                 // +0x374..+0x38b
    char pad38c[0x984];                // +0x38c..+0xd0f
    int md10;                          // +0xd10
    char padd14[0xec];                 // +0xd14..+0xdff
    bool CreateVoice();                        // 0x00a13300
    bool GetProperty(uint32_t key, float* out);   // 0x00a11a60
    void Reset();                              // 0x00a124a0
};
struct VoiceContainer {
    void* FindPlugin(uint32_t id);   // 0x00a34230
};
}}
namespace rw { namespace audio { namespace core {
struct System {
    void IsCommandComplete(int cmd, float v);   // 0x0112ccf0
    void GetLevel(int a, float* out);           // 0x0112cc80
};
}}}
struct AudioLockObj {
    void Lock();     // 0x0112c600
    void Unlock();   // 0x0112c620
};
extern AudioLockObj* gAudioLockObj;   // 0x016e61a8
uint32_t SPIDFromName(const char* s);   // 0x00571cf0
__declspec(noinline) void* eastl_VecInsert(void* dst, void* src, unsigned bytes) { return memcpy(dst, src, bytes); }   // 0x011e0744

namespace SP { namespace Audio {

using namespace EA;
using namespace EA::Audio;

// ---------------------------------------------------------------------------
// @ 0x00a38e40
// ---------------------------------------------------------------------------
struct cEmitterSndPlayer : EmitterSndPlayer {
    void* mpE00;   // +0xe00
    float mE04;    // +0xe04

    long double ComputeGainAttenuation(float a, float b, float c, float d);
    bool CreateVoice();
    void Reset();
    void SetCommandComplete(float t);
    bool GetProperty(uint32_t key, float* out);
};

// @ 0x00a38e40
long double cEmitterSndPlayer::ComputeGainAttenuation(float a, float b, float c, float d) {
    if (c <= a) {
        if (b != 0.0f) {
            if (d < a) return 0.0L;
            return mAttenuationCurve.GetOutputValue((a - c) / (d - c));
        }
    }
    return 1.0L;
}

// @ 0x00a38ea0
bool cEmitterSndPlayer::CreateVoice() {
    if (!EmitterSndPlayer::CreateVoice()) return false;
    void* p = ((VoiceContainer*)((char*)this + 0x38c))->FindPlugin(0x56754d31);
    mpE00 = p;
    return true;
}

// @ 0x00a38ed0
void cEmitterSndPlayer::Reset() {
    mpE00 = 0;
    EmitterSndPlayer::Reset();
}

// @ 0x00a38ee0
void cEmitterSndPlayer::SetCommandComplete(float t) {
    rw::audio::core::System* s = (rw::audio::core::System*)mpE00;
    if (s) {
        int v;
        if (mE04 > t) v = 1;
        else v = 0;
        s->IsCommandComplete(0x12, (float)v);
    }
}

// @ 0x00a38fe0
bool cEmitterSndPlayer::GetProperty(uint32_t key, float* out) {
    if (key != 0x6fa19f04) return EmitterSndPlayer::GetProperty(key, out);
    if (mpE00) {
        if (gAudioLockObj) gAudioLockObj->Lock();
        rw::audio::core::System* s = (rw::audio::core::System*)mpE00;
        if (md10 == 1) {
            s->GetLevel(1, out);
        } else {
            float a, b;
            s->GetLevel(0, &a);
            s->GetLevel(2, &b);
            *out = (b + a) * 0.5f;
        }
        if (gAudioLockObj) gAudioLockObj->Unlock();
    }
    return true;
}

// ---------------------------------------------------------------------------
// cEventModifier and its primitives
// ---------------------------------------------------------------------------
struct RefCountTemplate {
    int mRefCount;   // +4
    RefCountTemplate() : mRefCount(0) {}
    virtual ~RefCountTemplate() {}
};

struct IEventModifier {
    virtual ~IEventModifier() {}
    virtual bool Init() = 0;                                              // slot 1, +4
    virtual void Shutdown() = 0;                                          // slot 2, +8
    virtual void ModifyEvent(Command* cmd, int a, char* dst, int cap) = 0; // slot 3, +0xc
    virtual bool ReadTuningValues(const ResourceKey* key) = 0;            // slot 4, +0x10
    virtual int AddRef() = 0;                                             // slot 5, +0x14
    virtual int Release() = 0;                                            // slot 6, +0x18
};

struct RefCountBase {
    int mRefCount;   // +4 (after the vptr)
    RefCountBase() : mRefCount(0) {}
};

struct cEventModifierPrimitive : RefCountBase, IEventModifier {
    ResourceKey mKey;                 // +8
    AutoRefConfig mConfiguration;     // +0x14
    cEventModifierPrimitive(const char* name);   // 0xa3a530
    virtual ~cEventModifierPrimitive();          // 0xa39230
    virtual bool Init();                         // 0xa3a4b0
    virtual void Shutdown();
    virtual void ModifyEvent(Command* cmd, int a, char* dst, int cap);
    virtual bool ReadTuningValues(const ResourceKey* key);
    virtual int AddRef();
    virtual int Release();
    __declspec(noinline) void Append(char* dst, int cap, char* str, bool sep);
};

// @ 0x00a39230
cEventModifierPrimitive::~cEventModifierPrimitive() {
}

bool cEventModifierPrimitive::Init() { return true; }
void cEventModifierPrimitive::Shutdown() {}
void cEventModifierPrimitive::ModifyEvent(Command*, int, char*, int) {}
bool cEventModifierPrimitive::ReadTuningValues(const ResourceKey*) { return false; }
int cEventModifierPrimitive::AddRef() { return ++mRefCount; }
int cEventModifierPrimitive::Release() { return --mRefCount; }

struct PrimVector {
    cEventModifierPrimitive** mpBegin;
    cEventModifierPrimitive** mpEnd;
    cEventModifierPrimitive** mpCapacity;
    int mAlloc;
    PrimVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~PrimVector() { if (mpBegin) operator delete[](mpBegin); }
    void resize(unsigned n);   // 0xa39f30
    void DoInsertValue(cEventModifierPrimitive** pos, unsigned n, cEventModifierPrimitive** value); // 0xa39a40
};

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

// eastl::hashtable<uint, pair<const uint, string>, SP_STL_Sound, ...>
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

// @ 0x00a39c20
void SoundHashTable::DoFreeNodes(void** buckets, unsigned count) {
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

struct cEventModifierPrimitiveFootTypeBase : cEventModifierPrimitive {
    ResponseCurve mCurves[10];    // +0x18 .. +0x2200
    cEventModifierPrimitiveFootTypeBase(const char* name);   // 0xa39930
    virtual ~cEventModifierPrimitiveFootTypeBase();          // 0xa39770
    virtual void ModifyEventWithFootName(char* footName, Command* cmd, int unused, char* dst, int cap);
    ResponseCurve* Curve(int off) { return (ResponseCurve*)((char*)this + off); }
};

// @ 0x00a39770
cEventModifierPrimitiveFootTypeBase::~cEventModifierPrimitiveFootTypeBase() {}

// @ 0x00a39930
cEventModifierPrimitiveFootTypeBase::cEventModifierPrimitiveFootTypeBase(const char* name)
    : cEventModifierPrimitive(name) {}

struct cEventModifier : RefCountTemplate {
    PrimVector mEventModifiers;   // +8
    int mPad18;                   // +0x18
    UIntMap mModifierMap;         // +0x1c

    cEventModifier();                                        // 0xa398d0
    virtual ~cEventModifier();                               // 0xa39710
    uint32_t ConvertStringToMaskBit(const char* s) throw();  // 0xa390d0
    bool AddPrimitive(uint32_t idx, cEventModifierPrimitive* p);   // 0xa39280
    bool RemovePrimitive(uint32_t idx);                      // 0xa392d0
    void ReleasePrimitives();                                // 0xa39310
    void ModifyEvent(Command* cmd, uint32_t mask, char* name, int extra);   // 0xa39350
    bool CommandResolve(Command* cmd);                       // 0xa39620
    bool Shutdown();                                         // 0xa39c80
};

// @ 0x00a398d0
cEventModifier::cEventModifier() : RefCountTemplate(), mModifierMap() {}

// @ 0x00a39710
cEventModifier::~cEventModifier() {}

// @ 0x00a390d0
uint32_t cEventModifier::ConvertStringToMaskBit(const char* s) throw() {
    if (!strcmp("foottype", s)) return 2;
    if (!strcmp("epicfoottype", s)) return 4;
    if (!strcmp("mouthtype", s)) return 8;
    if (!strcmp("surfacetype", s)) return 0x10;
    if (!strcmp("alias", s)) return 0x20;
    return 0;
}

// @ 0x00a39280
bool cEventModifier::AddPrimitive(uint32_t idx, cEventModifierPrimitive* p) {
    if (!p) return false;
    if (idx < 6 && !mEventModifiers.mpBegin[idx]) {
        if (!p->Init()) return false;
        mEventModifiers.mpBegin[idx] = p;
        return true;
    }
    return false;
}

// @ 0x00a392d0
bool cEventModifier::RemovePrimitive(uint32_t idx) {
    if (idx >= 6) return false;
    if (mEventModifiers.mpBegin[idx]) {
        mEventModifiers.mpBegin[idx]->Shutdown();
        mEventModifiers.mpBegin[idx] = 0;
        return true;
    }
    return false;
}

// @ 0x00a39310
void cEventModifier::ReleasePrimitives() {
    for (int i = 0; i < 6; i++) {
        if (mEventModifiers.mpBegin[i]) {
            cEventModifierPrimitive* p = mEventModifiers.mpBegin[i];
            cEventModifierPrimitive*& slot = mEventModifiers.mpBegin[i];
            slot = 0;
            p->Shutdown();
            p->Release();
        }
    }
}

// @ 0x00a39350 (structural reconstruction; heavily optimised recursive routine)
void cEventModifier::ModifyEvent(Command* cmd, uint32_t mask, char* name, int extra) {
    uint32_t m = mask | 0x20;
    if (*name == 'v') m = mask | 0x28;
    char buf[200];
    strncpy(buf, name, 200);
    for (int i = 1; i < 6; i++) {
        cEventModifierPrimitive* p = mEventModifiers.mpBegin[i];
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

// @ 0x00a39620
bool cEventModifier::CommandResolve(Command* cmd) {
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

// @ 0x00a39c80
bool cEventModifier::Shutdown() {
    ReleasePrimitives();
    eastl_VecInsert(mEventModifiers.mpBegin, mEventModifiers.mpEnd, 0);
    mEventModifiers.mpEnd -= (mEventModifiers.mpEnd - mEventModifiers.mpBegin);
    mModifierMap.Clear();
    return true;
}

// @ 0x00a39a40
void PrimVector::DoInsertValue(cEventModifierPrimitive** position, unsigned n, cEventModifierPrimitive** value) {
    if (n > (unsigned)(mpCapacity - mpEnd)) {
        unsigned oldSize = (unsigned)(mpEnd - mpBegin);
        unsigned newCap = oldSize ? oldSize * 2 : 1;
        unsigned need = oldSize + n;
        unsigned alloc = need > newCap ? need : newCap;
        cEventModifierPrimitive** nd = (cEventModifierPrimitive**)
            operator new(alloc * 4, "EASTL", 0, 0, kEastlFile, 0xd1);
        unsigned pb = (unsigned)(position - mpBegin);
        memcpy(nd, mpBegin, pb * 4);
        cEventModifierPrimitive* v = *value;
        for (unsigned i = 0; i < n; i++) nd[pb + i] = v;
        memcpy(nd + pb + n, position, (unsigned)(mpEnd - position) * 4);
        if (mpBegin) operator delete[](mpBegin);
        mpBegin = nd;
        mpEnd = nd + oldSize + n;
        mpCapacity = nd + alloc;
        return;
    }
    if (n == 0) return;
    cEventModifierPrimitive* v = *value;
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

}}
// --- equivalence checker address annotations
    void* operator new(unsigned int, char*, int, int, char*, int); // 0x00f473a0
    void operator delete[](void*); // 0x00f47380
    void operator delete(void*); // 0x00f47380

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct EA {
    void FNV1_String8(void); // 0x00932e80
    void RBTreeIncrement(void*); // 0x00921580
    void DoNukeSubtree(void*); // 0x009a9600
};
struct SP {
    void gAudioLock(...); // 0x016e61a8
};
}
