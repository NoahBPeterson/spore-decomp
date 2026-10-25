#include "game/types.h"
#include "SP/cInputStrategy.h"
#include "SP/cPropertyList.h"
#include "SP/cPropertyManager.h"
#include "SP/cSPMission.h"
#include "SP/cSPPlanetaryArtifact.h"

// ---- items of slice s0107b260 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define VSLOT(n) virtual void _v##n();
template <class T>
class AutoRefCount_s0107_b260 {
public:
    T* mpObject;                 // +0x00
    AutoRefCount_s0107_b260() : mpObject(0) {}
    ~AutoRefCount_s0107_b260()
    {
        if (mpObject != 0)
            mpObject->Release();
    }
    AutoRefCount_s0107_b260& operator=(T* pObject); // 0x00b5f950
};
namespace EA {
using ::AutoRefCount_s0107_b260;
}
namespace EA {
namespace Messaging {
class IHandler_s0107_b260 {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3)
};
}
}
namespace EA {
namespace Messaging {
class Server_s0107_b260 {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7)
    VSLOT(8)
    virtual void AddHandler(IHandler_s0107_b260* pHandler, uint32_t nMessageId); // +0x24
};
}
}
namespace EA {
namespace Messaging {
void RemoveHandler(Server_s0107_b260* pServer, IHandler_s0107_b260* pHandler, uint32_t* pIds,
                   uint32_t nIdCount, int32_t nPriority); // 0x00571db0
}
}
namespace EA {
namespace Messaging {
class AutoHandler_s0107_b260 {
public:
    Server_s0107_b260* mpServer;            // +0x00
    IHandler_s0107_b260* mpHandler;         // +0x04
    uint32_t* mpIdArray;         // +0x08
    uint32_t mnIdArrayCount;     // +0x0c
    int32_t mnPriority;          // +0x10
    AutoHandler_s0107_b260()
        : mpServer(0), mpHandler(0), mpIdArray(0), mnIdArrayCount(0),
          mnPriority(0) {}
    ~AutoHandler_s0107_b260()
    {
        if (mpServer != 0) {
            Server_s0107_b260* pServer = mpServer;
            mpServer = 0;
            RemoveHandler(pServer, mpHandler, mpIdArray, mnIdArrayCount,
                          mnPriority);
        }
    }
};
}
}
class cPropertyValue {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7)
    VSLOT(8)
    uint8_t mnPad04[0x0e];       // +0x004
    uint16_t mnType;             // +0x012
    float* GetFloat();           // 0x0041ea70
    int32_t* GetInt();           // 0x0041e990
};
class cPropertyList {
public:
    VSLOT(0)
    virtual void Release();                                            // +0x04
    VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7) VSLOT(8)
    virtual bool FindProperty(uint32_t nKey, cPropertyValue** ppValue); // +0x24
};
class cUniverseTuningMessage {
public:
    uint8_t mnPad00[0x18];       // +0x00
    uint32_t mnType;             // +0x18
};
class cUniverseSimulatorTuning : public EA::Messaging::IHandler_s0107_b260 {
public:
    EA::AutoRefCount_s0107_b260<cPropertyList> mPropertyList; // +0x04
    EA::Messaging::AutoHandler_s0107_b260 mAutoHandler;       // +0x08
    float mLoyaltyBoosterTimeBonusFactor;          // +0x1c
    float mBioStabilizerInfectionTimeBonusFactor;  // +0x20
    float mBioStabilizerCollapseTimeBonusFactor;   // +0x24
    float mUberTurretProtectionFactor;             // +0x28
    int32_t mBuildingsForTargetingHomePlanet;      // +0x2c
    cUniverseSimulatorTuning();
    virtual ~cUniverseSimulatorTuning();
    virtual bool HandleMessage(uint32_t nMessage, cUniverseTuningMessage* pMessage);
    void Init();                                   // 0x0107bed0
    void UpdateTuning();                           // 0x0107bd40
};
// ---- items of slice s0107b260 end

// @ 0x0107bd40
void cUniverseSimulatorTuning::UpdateTuning()
{
    cPropertyValue* pValue;

    if (mPropertyList.mpObject != 0) {
        if (mPropertyList.mpObject->FindProperty(0x4f8e875, &pValue)
            && pValue->mnType == 13)
            mLoyaltyBoosterTimeBonusFactor = *pValue->GetFloat();
    }
    if (mPropertyList.mpObject != 0) {
        if (mPropertyList.mpObject->FindProperty(0x4f8e87b, &pValue)
            && pValue->mnType == 13)
            mBioStabilizerInfectionTimeBonusFactor = *pValue->GetFloat();
    }
    if (mPropertyList.mpObject != 0) {
        if (mPropertyList.mpObject->FindProperty(0x4f8e88b, &pValue)
            && pValue->mnType == 13)
            mBioStabilizerCollapseTimeBonusFactor = *pValue->GetFloat();
    }
    if (mPropertyList.mpObject != 0) {
        if (mPropertyList.mpObject->FindProperty(0x4f8e892, &pValue)
            && pValue->mnType == 13)
            mUberTurretProtectionFactor = *pValue->GetFloat();
    }
    if (mPropertyList.mpObject != 0) {
        if (mPropertyList.mpObject->FindProperty(0x52f0f6a, &pValue)
            && pValue->mnType == 9)
            mBuildingsForTargetingHomePlanet = *pValue->GetInt();
    }
}

// @ 0x0107bea0
bool cUniverseSimulatorTuning::HandleMessage(uint32_t nMessage, cUniverseTuningMessage* pMessage)
{
    if (nMessage == 0xf62def && pMessage->mnType == 0x3e9793b5)
        UpdateTuning();
    return false;
}
