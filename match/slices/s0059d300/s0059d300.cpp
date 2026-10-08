// Slice s0059d300 -- SP::cSPEditorAnimatedEventInfo messaging / manager events.
// Module flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast (same region as s0059b4b0).
#include "types.h"
#include <intrin.h>
#include <string.h>

typedef unsigned int size_t;
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void  operator delete(void* p);
inline void* operator new(size_t, void* p) { return p; }

namespace EA {
template <typename T>
class RefCountVTemplate {
public:
    RefCountVTemplate() : mnRefCount(0) {}
    virtual ~RefCountVTemplate() {}
    virtual int AddRef() { return ++mnRefCount; }
    virtual int Release()
    {
        int n = (*(volatile int*)&mnRefCount += -1);
        if (n == 0) { mnRefCount = 1; delete this; return 0; }
        return mnRefCount;
    }
protected:
    T mnRefCount;   // +0x8 when preceded by one vptr
};
}  // namespace EA

struct IMessageRC {
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3();
    virtual void m4(); virtual void m5(); virtual void m6(); virtual void m7();
};

namespace SP {

enum eAnimatedEvent { kAnimatedEvent0 = 0 };
struct cSPEditorBlock { char pad[0x10]; };
struct cSPEditorModel { char pad[0x10]; };

class cSPEditorAnimatedEventInfo : public IMessageRC, public EA::RefCountVTemplate<int> {
public:
    cSPEditorAnimatedEventInfo();
    virtual ~cSPEditorAnimatedEventInfo() {}

    void MessagePost(eAnimatedEvent event, cSPEditorBlock* block, cSPEditorModel* model,
                     uint32_t creatureID, bool isBaby, float delayTime, bool doLoop,
                     uint32_t animID, float animSpeed);
    void MessageSend(eAnimatedEvent event, cSPEditorBlock* block, cSPEditorModel* model,
                     uint32_t creatureID, bool isBaby, float delayTime, bool doLoop,
                     uint32_t animID, float animSpeed);

    uint32_t        mAnimatedCreatureID;   // +0xc
    cSPEditorBlock* mSourceBlock;          // +0x10
    cSPEditorModel* mSourceModel;          // +0x14
    eAnimatedEvent  mEvent;                // +0x18
    bool            mIsBaby;               // +0x1c
    float           mDelayTime;            // +0x20
    bool            mDoLoop;               // +0x24
    uint32_t        mAnimID;               // +0x28
    float           mAnimSpeed;            // +0x2c
};

struct IMessageServer {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4();
    virtual void Send(uint32_t msg, void* payload, int a);                  // +0x14
    virtual void Post(uint32_t msg, void* payload, int a, int b);           // +0x18
};

class cSPEditorAnimatedCreatureManager : public EA::RefCountVTemplate<int> {
public:
    void Init(void* pModelWorld, bool flag);          // 0x0059c060
    bool HandleAnimatedEvent(void* e);                // 0x0059d300
    void Update(unsigned int msec);                   // 0x0059d610
    char pad_10[0x48 - 0x10];
};

struct AnimRequest;
struct AnimResult;
struct AnimContext;

class cSPEditorAnimationManager {
public:
    __declspec(noinline) cSPEditorAnimationManager(); // 0x0059dac0
    void Init();                                      // 0x0059db40
    bool GetAnimation(AnimRequest* req, AnimResult* out, AnimContext* ctx);  // 0x0059dc70
    char pad[0x20];
};

}  // namespace SP

using namespace SP;

IMessageServer* MessageServer();   // 0x0067dcc0
void* GetManager();                // 0x0067dcd0
void* PropertyManager();           // 0x0067de30

// ===========================================================================
// @ 0x0059d840
void cSPEditorAnimatedEventInfo::MessagePost(eAnimatedEvent event, cSPEditorBlock* block,
                                             cSPEditorModel* model, uint32_t creatureID, bool isBaby,
                                             float delayTime, bool doLoop, uint32_t animID,
                                             float animSpeed)
{
    IMessageServer* server = MessageServer();
    if (server) {
        mAnimatedCreatureID = creatureID;
        mSourceBlock = block;
        mEvent = event;
        mIsBaby = isBaby;
        mSourceModel = model;
        mDelayTime = delayTime;
        mAnimID = animID;
        mDoLoop = doLoop;
        mAnimSpeed = animSpeed;
        server->Post(0xd1511790, this, 0, 0);
    }
}

// ===========================================================================
// @ 0x0059d8b0
void cSPEditorAnimatedEventInfo::MessageSend(eAnimatedEvent event, cSPEditorBlock* block,
                                             cSPEditorModel* model, uint32_t creatureID, bool isBaby,
                                             float delayTime, bool doLoop, uint32_t animID,
                                             float animSpeed)
{
    IMessageServer* server = MessageServer();
    if (server) {
        mAnimatedCreatureID = creatureID;
        mSourceBlock = block;
        mEvent = event;
        mIsBaby = isBaby;
        mSourceModel = model;
        mDelayTime = delayTime;
        mAnimID = animID;
        mDoLoop = doLoop;
        mAnimSpeed = animSpeed;
        server->Send(0xd1511790, this, 0);
    }
}

// ===========================================================================
// @ 0x0059d930
struct AtomicCounter {
    char pad0[4];
    long mnRefCount;   // +0x4
    int GetRefCount();
};

// @ 0x0059d930
int AtomicCounter::GetRefCount()
{
    return _InterlockedExchangeAdd(&mnRefCount, 0);
}

// @ 0x0059da20
struct RefPair {
    char pad0[4];
    int m4;            // +0x4
    int m8;            // +0x8
    bool Equals(const RefPair& o) const;
};

bool RefPair::Equals(const RefPair& o) const
{
    return o.m4 == m4 && o.m8 == m8;
}

// ===========================================================================
// @ 0x0059da80
struct RandomLinearCongruential { double RandomDoubleUniform(); };
extern RandomLinearCongruential sMathRandom;   // 0x1601760
double RandomRange(float range)
{
    double dRange = range;
    double result = sMathRandom.RandomDoubleUniform() * dRange;
    if (result >= dRange)
        return dRange;
    if (result > 0.0)
        return result;
    return 0.0;
}

// ===========================================================================
// @ 0x0059dac0
cSPEditorAnimationManager::cSPEditorAnimationManager() {}

void* g_pForceMgr;
void ForceAnimationManagerCtor() { g_pForceMgr = new cSPEditorAnimationManager(); }

// ===========================================================================
// @ 0x0059db00
// scalar deleting destructor -- emitted by the compiler from the vtable

// ===========================================================================
// @ 0x0059d960
cSPEditorAnimatedEventInfo::cSPEditorAnimatedEventInfo()
    : mAnimatedCreatureID(0), mSourceBlock(0), mSourceModel(0), mEvent(kAnimatedEvent0),
      mIsBaby(false), mDelayTime(0.0f), mDoLoop(false), mAnimID(0xffffffff), mAnimSpeed(1.0f)
{
}

// ===========================================================================
// @ 0x0059d300
bool SP::cSPEditorAnimatedCreatureManager::HandleAnimatedEvent(void* e)
{
    (void)e;
    return false;
}

// @ 0x0059d610
void SP::cSPEditorAnimatedCreatureManager::Update(unsigned int msec)
{
    (void)msec;
}

// @ 0x0059db40
void cSPEditorAnimationManager::Init() {}

// @ 0x0059dc70
// ---------------------------------------------------------------------------
// GetAnimation support types (retail layouts, checked against the asm).
namespace SP {
class cPropertyList;
struct Key { uint32_t instance, type, group; };       // ResourceKey, 12 bytes
bool __cdecl KeyMatches(const Key* a, const Key* b);   // 0x004a9a90 (0 in b = wildcard)
bool GetPropertyAsKeyArray(cPropertyList* list, uint32_t id, int* count, Key** keys);   // 0x006a0ae0
bool GetPropertyAsChar8Ptr(cPropertyList* list, uint32_t id, const char** value);       // 0x006a1450
void __cdecl EASTL_allocator_deallocate(void* p);                                        // 0x00f47380
extern const uint32_t kDefaultUIntValue;   // 0x015d1164
extern const bool kDefaultBoolValue;       // 0x015d115d

struct Property {
    void* mpData;        // +0x00 (array data, or the inline value itself)
    uint32_t pad04;
    int mnItemCount;     // +0x08
    uint32_t pad0c;
    uint16_t mnFlags;    // +0x10 (0x30 = array)
    uint16_t mnType;     // +0x12
    int GetItemCount()
    {
        if (mnFlags & 0x30) return mnItemCount;
        else if (mnType != 0) return 1;
        return 0;
    }
    void* GetItems()
    {
        if (mnFlags & 0x30) return mpData;
        else if (mnType != 0) return this;
        return 0;
    }
    void* GetValuePtr()
    {
        if (mnFlags & 0x30) return mpData;
        return (void*)((-(int)(uint32_t)mnType >> 31) & (int)this);
    }
};

class cPropertyList {
public:
    virtual int AddRef();
    virtual int Release();
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18();
    virtual bool HasProperty(uint32_t id);                       // +0x1c
    virtual bool GetPropertyAlt(uint32_t id, Property*& result); // +0x20
    virtual bool GetProperty(uint32_t id, Property*& result);    // +0x24
    virtual Property* GetPropertyObject(uint32_t id);            // +0x28
};

template <class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    T* operator->() const { return mpObject; }
};

template <class T> struct SpVector {
    T* mpBegin; T* mpEnd; T* mpCapacity;
    SpVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~SpVector()
    {
        for (T* p = mpBegin; p < mpEnd; ++p) p->~T();
        if (mpBegin && ((int*)mpBegin)[-1]) EASTL_allocator_deallocate(mpBegin);
    }
    void DoInsertValue(T* pos, const T& v);
    void push_back(const T& v)
    {
        if (mpEnd < mpCapacity) { if (mpEnd) new (mpEnd) T(v); ++mpEnd; }
        else DoInsertValue(mpEnd, v);
    }
};
template <> struct SpVector<float> {
    float* mpBegin; float* mpEnd; float* mpCapacity;
    SpVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~SpVector() { if (mpBegin && ((int*)mpBegin)[-1]) EASTL_allocator_deallocate(mpBegin); }
    void DoInsertValue(float* pos, const float& v);   // 0x00455660
    void push_back(const float& v)
    {
        if (mpEnd < mpCapacity) { if (mpEnd) *mpEnd = v; ++mpEnd; }
        else DoInsertValue(mpEnd, v);
    }
};
template <> struct SpVector<char> {
    char* mpBegin; char* mpEnd; char* mpCapacity;
    SpVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~SpVector() { if (mpBegin && ((int*)mpBegin)[-1]) EASTL_allocator_deallocate(mpBegin); }
    void DoInsertValue(char* pos, const char& v);   // 0x00426730
    void push_back(const char& v)
    {
        if (mpEnd < mpCapacity) { if (mpEnd) *mpEnd = v; ++mpEnd; }
        else DoInsertValue(mpEnd, v);
    }
};

struct Entity {                      // editor block
    bool HasAnyBlockFlag();          // 0x00435d40
    Key* GetKey(Key* out);           // 0x00440b90 (copies 12 bytes at +0x5f8)
    char pad0[0x28];
    struct EditorModel* mpModel;     // +0x28 (when used via the request's block)
};
struct EditorModel {
    int GetBlockCount();             // 0x004accf0
    Entity* GetBlock(uint32_t i);    // 0x004accb0
};
struct AnimRequest {
    char pad0[0x10];
    Entity* mpBlock;                 // +0x10
    EditorModel* mpModel;            // +0x14
    uint32_t mAnimID;                // +0x18
    char pad1c[0x28 - 0x1c];
    uint32_t mForcedAnim;            // +0x28
};
struct AnimResult {
    uint32_t mID;                    // +0
    uint32_t mFourCC;                // +4
    bool mFlag;                      // +8
};
struct AnimContext {
    char pad0[0x1c];
    uint32_t mKey;                   // +0x1c
    bool Matches(uint32_t v);        // 0x0059ac90
};
struct AppPropsInner { char pad[0xdc]; int mFlag; };
struct AppProps { char pad[0x3c]; AppPropsInner* mpInner; };
extern AppProps* gAppProps;          // 0x015fd918

typedef SpVector<AutoRefCount<cPropertyList> > AnimListVec;
struct AnimMgrView { char pad[0xc]; AnimListVec mAnimations; };   // +0xc

static const uint32_t kForcedAnimID = 0x248dca26;
}  // namespace SP

bool SP::cSPEditorAnimationManager::GetAnimation(AnimRequest* req, AnimResult* out, AnimContext* ctx)
{
    AnimListVec& anims = ((AnimMgrView*)this)->mAnimations;

    if ((anims.mpBegin != anims.mpEnd || req->mAnimID == kForcedAnimID) && gAppProps->mpInner->mFlag != 0) {
        if (req->mAnimID == kForcedAnimID) {
            if (req->mForcedAnim != 0) {
                out->mID = req->mForcedAnim;
                out->mFlag = true;
                return true;
            }
        }
        else {
            AnimListVec matches;
            SpVector<float> weights;
            int numAnims = anims.mpEnd - anims.mpBegin;
            for (int i = 0; i < numAnims; i++) {
                AutoRefCount<cPropertyList> list(anims.mpBegin[i]);
                if (!list->HasProperty(0xf150ffb0)) continue;
                Property* prop = list->GetPropertyObject(0xf150ffb0);
                int numIDs = prop->GetItemCount();
                Key* ids = (Key*)prop->GetItems();
                int k = 0;
                for (; k < numIDs; k++) {
                    if (ids[k].instance == req->mAnimID) break;
                }
                if (k >= numIDs) continue;

                bool bAllRequired = true;
                int numReq; Key* reqKeys;
                if (GetPropertyAsKeyArray(list.mpObject, 0xff50f753, &numReq, &reqKeys) && numReq > 0) {
                    bAllRequired = false;
                    SpVector<char> found;
                    for (int j = 0; j < numReq; j++) {
                        char zero = 0;
                        found.push_back(zero);
                    }
                    EditorModel* model = req->mpModel;
                    if (!model && req->mpBlock) model = req->mpBlock->mpModel;
                    if (model) {
                        int numBlocks = model->GetBlockCount();
                        for (int b = 0; b < numBlocks; b++) {
                            Entity* blk = model->GetBlock(b);
                            if (blk->HasAnyBlockFlag()) {
                                Key bk;
                                blk->GetKey(&bk);
                                for (int j = 0; j < numReq; j++) {
                                    if (KeyMatches(&bk, &reqKeys[j])) found.mpBegin[j] = 1;
                                }
                            }
                        }
                        bAllRequired = true;
                        for (int j = 0; j < numReq; j++) {
                            if (!found.mpBegin[j]) { bAllRequired = false; break; }
                        }
                    }
                }

                bool bAnyAllowed = true;
                int numAllow; Key* allowKeys;
                if (GetPropertyAsKeyArray(list.mpObject, 0xe99ed6ff, &numAllow, &allowKeys) && numAllow > 0 && req->mpBlock) {
                    bAnyAllowed = false;
                    for (int j = 0; j < numAllow; j++) {
                        Key bk;
                        if (KeyMatches(req->mpBlock->GetKey(&bk), &allowKeys[j])) { bAnyAllowed = true; break; }
                    }
                }

                if (bAllRequired && bAnyAllowed) {
                    matches.push_back(list);
                    float weight = 1.0f;
                    Property* wp;
                    if (list.mpObject && list->GetProperty(0x029eb123, wp) && wp->mnType == 10) {
                        const uint32_t* pv = (const uint32_t*)wp->GetValuePtr();
                        if (ctx->Matches(*pv)) weight = 0.0f;
                    }
                    weights.push_back(weight);
                }
            }

            if (matches.mpBegin != matches.mpEnd) {
                int numWeights = weights.mpEnd - weights.mpBegin;
                float total = 0.0f;
                for (int i = 0; i < numWeights; i++) total = weights.mpBegin[i] + total;
                if (total == 0.0f && numWeights > 0) {
                    for (int i = 0; i < numWeights; i++) weights.mpBegin[i] = 1.0f;
                    for (int i = 0; i < numWeights; i++) total += 1.0f;
                }
                float r = (float)RandomRange(total);
                float acc = 0.0f;
                int idx = 0;
                for (int i = 0; i < numWeights; i++) {
                    acc = weights.mpBegin[i] + acc;
                    idx = i;
                    if (acc > r) break;
                }
                if (idx >= (int)(matches.mpEnd - matches.mpBegin) || idx < 0) idx = 0;

                AutoRefCount<cPropertyList> chosen(matches.mpBegin[idx]);
                if (chosen->HasProperty(0x029eb123)) {
                    Property* p = chosen->GetPropertyObject(0x029eb123);
                    uint16_t t = p->mnType;
                    const uint32_t* idp = (t == 10 || t == 0x10) ? (const uint32_t*)p->GetValuePtr() : &kDefaultUIntValue;
                    out->mID = *idp;
                    const char* name;
                    if (GetPropertyAsChar8Ptr(chosen.mpObject, 0xf711981f, &name)) {
                        char buf[4] = { 0, 0, 0, 0 };
                        strncpy(buf, name, 4);
                        out->mFourCC = ((((uint32_t)(uint8_t)buf[3] << 8 | (uint8_t)buf[2]) << 8 | (uint8_t)buf[1]) << 8) | (uint8_t)buf[0];
                    }
                    if (chosen->HasProperty(0x654234db)) {
                        Property* q = chosen->GetPropertyObject(0x654234db);
                        uint16_t qt = q->mnType;
                        const bool* bp = (qt == 1 || qt == 0x10) ? (const bool*)q->GetValuePtr() : &kDefaultBoolValue;
                        out->mFlag = *bp;
                    }
                    return true;
                }
            }
        }
    }
    out->mID = 0;
    return false;
}
