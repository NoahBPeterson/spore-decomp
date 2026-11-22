// src/game/SPGonzago/_at_01070000.cpp -- migrated from slice(s) s0107b260, s01074bb0 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_01070000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPCreatureBase.h"
#include "SP/cEmpire.h"
#include "SP/cPlanet.h"
#include "SP/cSpeciesProfile.h"
#include "SP/cString.h"
#include "SP/cInputStrategy.h"
#include "SP/cPropertyList.h"
#include "SP/cPropertyManager.h"
#include "SP/cSPMission.h"
#include "SP/cSPPlanetaryArtifact.h"

// ---- items of slice s01074bb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint;
struct IWindow {
virtual void s00();
virtual void s04();
virtual void s08();
virtual void s0c();
    virtual IWindow* Get10();                                        // 0x10
virtual void s14();
virtual void s18();
virtual void s1c();
virtual void s20();
virtual void s24();
virtual void s28();
virtual void s2c();
virtual void s30();
virtual void s34();
virtual void s38();
virtual void s3c();
virtual void s40();
virtual void s44();
virtual void s48();
virtual void s4c();
virtual void s50();
virtual void s54();
virtual void s58();
virtual void s5c();
virtual void s60();
virtual void s64();
virtual void s68();
virtual void s6c();
virtual void s70();
virtual void s74();
virtual void s78();
    virtual void SetVisible(int a, int b);                           // 0x7c
virtual void s80();
virtual void s84();
virtual void s88();
virtual void s8c();
virtual void s90();
virtual void s94();
virtual void s98();
virtual void s9c();
virtual void sA0();
virtual void sA4();
virtual void sA8();
virtual void sAC();
virtual void sB0();
virtual void sB4();
virtual void sB8();
virtual void sBC();
virtual void sC0();
virtual void sC4();
virtual void sC8();
virtual void sCC();
virtual void sD0();
virtual void sD4();
virtual void sD8();
    virtual void FDC(void* p);                                       // 0xdc
virtual void sE0();
virtual void sE4();
virtual void sE8();
virtual void sEC();
    virtual IWindow* F0(uint id, int flag);                          // 0xf0
virtual void sF4();
virtual void sF8();
virtual void sFC();
virtual void s100();
virtual void s104();
    virtual void F108(void* p);                                      // 0x108
};
struct cString {
    char d[0x14]; const wchar_t* GetText(int flags);    // 0x006b55c0 (ret 4)
    void Load(uint a, const wchar_t* b, int c);         // 0x006b54b0 (ret 0xc)
};
struct Layout {
    virtual void v00();
    virtual void v04();
    virtual void Release();                        // +0x08
    IWindow* FindWindowByID(uint id, int flag);    // 0x008105b0 (ret 8)
};
struct cTrading {
    char pad0[0x10];
    IWindow* m10;            // +0x10
    void*    m14;            // +0x14
    void*    m18;            // +0x18
    IWindow* m1c;            // +0x1c
    void*    m20;            // +0x20
    void*    m24;            // +0x24
    char pad1[0xb4 - 0x28];
    cString  mStrB4;         // +0xb4
    cString  mStrC8;         // +0xc8
    cString  mStrDC;         // +0xdc
    cString  mStrF0;         // +0xf0
    Layout*  mLayout;        // +0x104
    char pad2[0x11c - 0x108];
    char mFlag11C;           // +0x11c
    char pad3[0x120 - 0x11d];
    int  mId120;             // +0x120
    unsigned char mFlag124;  // +0x124

    int  F1075450();
    void F1075490();
    void F1075510();
    void F1075570();
    void SetMidPanel();
    void RemoveExistingItem();
    void F1075760();
    void F1075810(int flag, void* item);
    void F1075990();
};
// ---- items of slice s01074bb0 end

// ---- items of slice s0107b260 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t gUniverseTuningMessageIds[];       // 0x0149c6b4
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
EA::Messaging::Server_s0107_b260* MessageServer(); // 0x0067dcc0
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
class cPropertyManager {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7)
    VSLOT(8) VSLOT(9) VSLOT(10)
    virtual void GetProperty(uint32_t nKey, uint32_t nId,
                             cPropertyList** ppProperty); // +0x2c
};
cPropertyManager* PropertyManager(); // 0x0067de30
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

// @ 0x01075490
void cTrading::F1075490()
{
    mFlag11C = 0;
    mStrB4.Load(0x2db6dad3, (const wchar_t*)0x679ed24, 0);
    mStrC8.Load(0x2db6dad3, (const wchar_t*)0x679eac6, 0);
    mStrDC.Load(0x2db6dad3, (const wchar_t*)0x679eac5, 0);
    mStrF0.Load(0xba5c1bf, (const wchar_t*)0xa0bb7099, 0);
}

// @ 0x0107bcc0
cUniverseSimulatorTuning::cUniverseSimulatorTuning()
{
    mLoyaltyBoosterTimeBonusFactor = 1.0f;
    mBioStabilizerInfectionTimeBonusFactor = 1.0f;
    mBioStabilizerCollapseTimeBonusFactor = 1.0f;
    mUberTurretProtectionFactor = 1.0f;
    mBuildingsForTargetingHomePlanet = 100;

    mAutoHandler.mpServer = MessageServer();
    mAutoHandler.mpHandler = this;
    mAutoHandler.mpIdArray = gUniverseTuningMessageIds;
    mAutoHandler.mnIdArrayCount = 1;
    mAutoHandler.mnPriority = 0;
    if (mAutoHandler.mpServer != 0)
        mAutoHandler.mpServer->AddHandler(this, 0xf62def);
}

// @ 0x0107bed0
void cUniverseSimulatorTuning::Init()
{
    cPropertyManager* pManager = PropertyManager();
    cPropertyList* pOldProperty = mPropertyList.mpObject;
    if (pOldProperty != 0) {
        mPropertyList.mpObject = 0;
        pOldProperty->Release();
    }
    pManager->GetProperty(0x3e9793b5, 0x2ae0c7e, &mPropertyList.mpObject);
    UpdateTuning();
}
