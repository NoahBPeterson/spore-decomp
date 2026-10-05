// Slice s0059d300 -- SP::cSPEditorAnimatedEventInfo messaging / manager events.
// Module flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast (same region as s0059b4b0).
#include "types.h"
#include <intrin.h>

typedef unsigned int size_t;
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void  operator delete(void* p);

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

class cSPEditorAnimationManager {
public:
    __declspec(noinline) cSPEditorAnimationManager(); // 0x0059dac0
    void Init();                                      // 0x0059db40
    void* GetAnimation(void* a, void* b, void* c);    // 0x0059dc70
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
void* SP::cSPEditorAnimationManager::GetAnimation(void* a, void* b, void* c)
{
    (void)a; (void)b; (void)c;
    return 0;
}
