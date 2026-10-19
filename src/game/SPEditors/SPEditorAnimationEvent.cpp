// src/game/SPEditors/SPEditorAnimationEvent.cpp -- migrated from slice(s) s0059d300, s0059acb0 by tools/migrate/rewrite.py
// Object file: SPEditors/SPEditorAnimationEvent.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPEditorAnimatedEventInfo.h"
#include "SP/cAnimatingCreature.h"
#include <math.h>
#include <intrin.h>
#include "EA/Variant.h"
#include "SP/cPropertyList.h"
#include "SP/cSPEditorAnimatedCreatureManager.h"
#include "SP/cSPEditorAnimationManager.h"
#include "SP/cSPEditorBlock.h"
#include "SP/cSPEditorModel.h"
#include <string.h>

// ---- items of slice s0059acb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace Simulator {
class cAnimatingCreature {
public:
    char pad0[0x70];
    uint32_t mFlags;                // +0x70
    char pad74[0x150 - 0x74];
    uint8_t mByte150;               // +0x150
    void AddRef();                  // 0x00a02c30
    void Release();                 // 0x00a05270
    bool IsSomething(int a);        // 0x00a02b20
};
}
namespace Simulator {
class cAnimatedData {
public:
    virtual void slot0();           // vptr at +0
    int mField04;                   // +0x04
    cAnimatingCreature* mpCreature; // +0x08
    int mField0c;                   // +0x0c
    int mField10, mField14, mField18;   // +0x10..0x18
    int mField1c;                   // +0x1c
    float mVec0[3];                 // +0x20
    float mVec1[3];                 // +0x2c
    float mVec2[3];                 // +0x38
    float mField44, mField48;       // +0x44, +0x48
    float mField4c;                 // +0x4c
    float mField50;                 // +0x50
    bool mField54, mField55;        // +0x54, +0x55
    float mField58, mField5c, mField60;   // +0x58 target
    float mField64, mField68, mField6c;   // +0x64 copy
    bool mField70;                  // +0x70
    float mField74, mField78, mField7c;   // +0x74..0x7c
    float mField80;                 // +0x80
    bool mField84;                  // +0x84

    void FUN_0059ae20(cAnimatingCreature* p, int a);   // 0x0059ae20
    void FUN_0059ae60();                               // 0x0059ae60
    bool FUN_0059ae80();                               // 0x0059ae80
    void FUN_0059aea0(char b);                         // 0x0059aea0
    void* FUN_0059ace0();                              // 0x0059ace0
    void* FUN_0059b0b0(char flags);                    // 0x0059b0b0
    void FUN_0059b2f0(float angle, char update);       // 0x0059b2f0
    void FUN_0059b390();                               // 0x0059b390
    void FUN_0059b420(char b);                         // 0x0059b420
    void FUN_0059aed0(float* out, const float* q, const float* v);  // 0x0059aed0
    void SetTargetPosition(int a, float angle);        // 0x0059b0f0
};
}
// ---- items of slice s0059acb0 end

// ---- items of slice s0059d300 begin (TODO(rewrite): local stubs, replace by canonical classes)
void  operator delete(void* p);
namespace EA {
template <typename T>
class RefCountVTemplate_s0059_d300 {
public:
    RefCountVTemplate_s0059_d300() : mnRefCount(0) {}
    virtual ~RefCountVTemplate_s0059_d300() {}
    virtual int AddRef() { return ++mnRefCount; }
    virtual int Release()
    {
        int n = (*(volatile int*)&mnRefCount += -1);
        if (n == 0) { mnRefCount = 1; delete this; return 0; }
        return mnRefCount;
    }
protected:
    T mnRefCount;   // +0x8 when preceded by one vptr
};  // namespace EA
}
struct IMessageRC {
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3();
    virtual void m4(); virtual void m5(); virtual void m6(); virtual void m7();
};
namespace SP {
enum eAnimatedEvent { kAnimatedEvent0 = 0 };
}
namespace SP {
struct cSPEditorBlock_s0059_d300 { char pad[0x10]; };
}
namespace SP {
struct cSPEditorModel_s0059_d300 { char pad[0x10]; };
}
namespace SP {
class cSPEditorAnimatedEventInfo_s0059_d300 : public IMessageRC, public EA::RefCountVTemplate_s0059_d300<int> {
public:
    cSPEditorAnimatedEventInfo_s0059_d300();
    virtual ~cSPEditorAnimatedEventInfo_s0059_d300() {}

    void MessagePost(eAnimatedEvent event, cSPEditorBlock_s0059_d300* block, cSPEditorModel_s0059_d300* model,
                     uint32_t creatureID, bool isBaby, float delayTime, bool doLoop,
                     uint32_t animID, float animSpeed);
    void MessageSend(eAnimatedEvent event, cSPEditorBlock_s0059_d300* block, cSPEditorModel_s0059_d300* model,
                     uint32_t creatureID, bool isBaby, float delayTime, bool doLoop,
                     uint32_t animID, float animSpeed);

    uint32_t        mAnimatedCreatureID;   // +0xc
    cSPEditorBlock_s0059_d300* mSourceBlock;          // +0x10
    cSPEditorModel_s0059_d300* mSourceModel;          // +0x14
    eAnimatedEvent  mEvent;                // +0x18
    bool            mIsBaby;               // +0x1c
    float           mDelayTime;            // +0x20
    bool            mDoLoop;               // +0x24
    uint32_t        mAnimID;               // +0x28
    float           mAnimSpeed;            // +0x2c
};
}
namespace SP {
struct IMessageServer {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4();
    virtual void Send(uint32_t msg, void* payload, int a);                  // +0x14
    virtual void Post(uint32_t msg, void* payload, int a, int b);           // +0x18
};
}
SP::IMessageServer* MessageServer();   // 0x0067dcc0
struct AtomicCounter {
    char pad0[4];
    long mnRefCount;   // +0x4
    int GetRefCount();
};
// ---- items of slice s0059d300 end

// @ 0x0059aea0
void Simulator::cAnimatedData::FUN_0059aea0(char b)
{
    Simulator::cAnimatingCreature* p = mpCreature;
    if (p) {
        p->mByte150 = b;
        p = mpCreature;
        if (b)
            p->mFlags |= 0x80;
        else
            p->mFlags &= ~0x80u;
    }
}

// @ 0x0059d840
void SP::cSPEditorAnimatedEventInfo::MessagePost(SP::cSPEditorAnimatedEventInfo::eAnimatedEvent event, SP::cSPEditorBlock * block, SP::cSPEditorModel * model, unsigned int creatureID, bool isBaby, float delayTime, bool doLoop, unsigned int animID, float animSpeed)
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

// @ 0x0059d8b0
void SP::cSPEditorAnimatedEventInfo_s0059_d300::MessageSend(SP::eAnimatedEvent event, SP::cSPEditorBlock_s0059_d300* block, SP::cSPEditorModel_s0059_d300* model, uint32_t creatureID, bool isBaby, float delayTime, bool doLoop, uint32_t animID, float animSpeed)
{
    SP::IMessageServer* server = MessageServer();
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

// @ 0x0059d930
int AtomicCounter::GetRefCount()
{
    return _InterlockedExchangeAdd(&mnRefCount, 0);
}
