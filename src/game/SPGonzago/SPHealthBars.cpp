// src/game/SPGonzago/SPHealthBars.cpp -- migrated from slice(s) s0059d300 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPHealthBars.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Variant.h"
#include "SP/cPropertyList.h"
#include "SP/cSPEditorAnimatedCreatureManager.h"
#include "SP/cSPEditorAnimatedEventInfo.h"
#include "SP/cSPEditorAnimationManager.h"
#include "SP/cSPEditorBlock.h"
#include "SP/cSPEditorModel.h"
#include <intrin.h>
#include <string.h>
#include <math.h>

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
struct IMessageRC_s0059_d300 {
virtual void m0();
virtual void m1();
virtual void m2();
virtual void m3();
virtual void m4();
virtual void m5();
virtual void m6();
virtual void m7();
};
namespace SP {
enum eAnimatedEvent { kAnimatedEvent0 = 0 };
}
namespace SP {
class cSPEditorBlock_s0059_d300 { public: char pad[0x10]; };
}
namespace SP {
class cSPEditorModel_s0059_d300 { public: char pad[0x10]; };
}
namespace SP {
class cSPEditorAnimatedEventInfo_s0059_d300 : public IMessageRC_s0059_d300, public EA::RefCountVTemplate_s0059_d300<int> {
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
// ---- items of slice s0059d300 end

// @ 0x0059d960
SP::cSPEditorAnimatedEventInfo_s0059_d300::cSPEditorAnimatedEventInfo_s0059_d300()
: mAnimatedCreatureID(0), mSourceBlock(0), mSourceModel(0), mEvent(SP::kAnimatedEvent0),
      mIsBaby(false), mDelayTime(0.0f), mDoLoop(false), mAnimID(0xffffffff), mAnimSpeed(1.0f)
{
}
