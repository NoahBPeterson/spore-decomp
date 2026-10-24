// Slice s0107b260: SP::cSPUITools panel population/message plumbing,
// SP::cUniverseSimulatorTuning construction/tuning, and the
// SP::cWalkAroundInputStrategy constructor/destructor/message handler.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"

#define VSLOT(n) virtual void _v##n();

// ---------------------------------------------------------------------------
// shared value types
// ---------------------------------------------------------------------------
class Key {
public:
    uint32_t mInstance;   // +0x00
    uint32_t mType;       // +0x04
    uint32_t mGroup;      // +0x08
};

class cSPMission {
public:
    uint8_t mnPad00[0x17c];       // +0x000
    cSPMission* mpParentMission;  // +0x17c
};

template <class T>
class AutoRefCount {
public:
    T* mpObject;                 // +0x00
    AutoRefCount() : mpObject(0) {}
    ~AutoRefCount()
    {
        if (mpObject != 0)
            mpObject->Release();
    }
    AutoRefCount& operator=(T* pObject); // 0x00b5f950
};

namespace EA {
using ::AutoRefCount;

namespace Messaging {

class IHandler {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3)
};

class Server {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7)
    VSLOT(8)
    virtual void AddHandler(IHandler* pHandler, uint32_t nMessageId); // +0x24
};

void RemoveHandler(Server* pServer, IHandler* pHandler, uint32_t* pIds,
                   uint32_t nIdCount, int32_t nPriority); // 0x00571db0

class AutoHandler {
public:
    Server* mpServer;            // +0x00
    IHandler* mpHandler;         // +0x04
    uint32_t* mpIdArray;         // +0x08
    uint32_t mnIdArrayCount;     // +0x0c
    int32_t mnPriority;          // +0x10
    AutoHandler()
        : mpServer(0), mpHandler(0), mpIdArray(0), mnIdArrayCount(0),
          mnPriority(0) {}
    ~AutoHandler()
    {
        if (mpServer != 0) {
            Server* pServer = mpServer;
            mpServer = 0;
            RemoveHandler(pServer, mpHandler, mpIdArray, mnIdArrayCount,
                          mnPriority);
        }
    }
};

} // namespace Messaging
} // namespace EA

EA::Messaging::Server* MessageServer(); // 0x0067dcc0

// ---------------------------------------------------------------------------
// property objects
// ---------------------------------------------------------------------------
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

void GetToolAvailability(cPropertyList* pProperty, uint32_t* pnTool,
                         uint32_t* pnAvailability); // 0x0107b120

class cUniverseTuningMessage {
public:
    uint8_t mnPad00[0x18];       // +0x00
    uint32_t mnType;             // +0x18
};

// ---------------------------------------------------------------------------
// SP::cUniverseSimulatorTuning (shipping layout is 0x30 bytes)
// ---------------------------------------------------------------------------
class cUniverseSimulatorTuning : public EA::Messaging::IHandler {
public:
    EA::AutoRefCount<cPropertyList> mPropertyList; // +0x04
    EA::Messaging::AutoHandler mAutoHandler;       // +0x08
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

extern uint32_t gUniverseTuningMessageIds[];       // 0x0149c6b4

// ---------------------------------------------------------------------------
// external UI helpers used by the tool panel methods
// ---------------------------------------------------------------------------
class cUIObject {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6)
    virtual void* GetItem();       // +0x1c
    virtual uint32_t GetTypeId();  // +0x20
};

class cToolsEvent {
public:
    cUIObject* mpObject;         // +0x00
    uint32_t mnPad04;            // +0x04
    uint32_t mnType;             // +0x08
    uint32_t mnPad0c;            // +0x0c
    void* mpCard;                // +0x10
};

class cLeftPanel {
public:
    void Reset();                // 0x00e36620
};

class cSelectionManager {
public:
    void Select(void* pObject);  // 0x00e30a60
};

class cNounManager {
public:
    uint8_t mnPad00[0x5c];          // +0x000
    cSelectionManager* mpSelection; // +0x05c
};

cNounManager* NounManager();        // 0x00b3d3f0

class cMissionCard {
public:
    virtual void AddRef();          // +0x00
    virtual void Release();         // +0x04
    uint8_t mnPad04[0x178];         // +0x004
    cSPMission* mpParentMission;    // +0x17c
};

class cSPUITools {
public:
    __declspec(noinline) bool PopulateSelected(cUIObject* pObject); // 0x0107b260
    __declspec(noinline) void PopulateRight();                      // 0x0107b760
    void Open(uint32_t nSlot);                                      // 0x0107bb00
};

class cToolsPanelLeft {
public:
    uint8_t mnPad00[0xb0];       // +0x000
    cLeftPanel mLeftPanel;       // +0x0b0
    bool PopulateLeft(uint32_t nMessage, cToolsEvent* pEvent); // 0x0107b6f0
};

class cUIMissionCardPanel {
public:
    virtual bool OnMessage(uint32_t nMessage, cToolsEvent* pEvent); // 0x00e18600
    uint8_t mnPad04[0x138];      // +0x004
    cMissionCard* mpSelectedMission; // +0x13c
};

class cToolsMessage : public cUIMissionCardPanel {
public:
    bool OnMessage(uint32_t nMessage, cToolsEvent* pEvent); // 0x0107bc30
};

// ---------------------------------------------------------------------------
// SP::cWalkAroundInputStrategy
// ---------------------------------------------------------------------------
class IWinText {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3)
    virtual void Release();      // +0x10
    uint8_t mnPad14[0x64c];      // +0x014
    float mHighlightAlpha;       // +0x660
};

class cSPPlanetaryArtifact {
public:
    VSLOT(0)
    virtual void Release();      // +0x04
};

class cInputStrategy {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3)
    virtual ~cInputStrategy();
    uint8_t mnPad04[0x38];       // +0x004
};

class cSPUICursorStrategy {
public:
    VSLOT(0) VSLOT(1)
    virtual ~cSPUICursorStrategy();
    uint8_t mnPad04[4];          // +0x004
};

class IWinProc {
public:
    VSLOT(0) VSLOT(1) VSLOT(2)
    virtual ~IWinProc();
};

class IHandlerRC {
public:
    VSLOT(0) VSLOT(1)
    virtual ~IHandlerRC();
};

template <class T>
class RefCountVTemplate {
public:
    VSLOT(0) VSLOT(1)
    virtual ~RefCountVTemplate();
    int32_t mnRefCount;          // +0x004
};

class cCreatureModeInputStrategy : public cInputStrategy,
                                   public cSPUICursorStrategy,
                                   public IWinProc,
                                   public IHandlerRC,
                                   public RefCountVTemplate<int> {
public:
    cCreatureModeInputStrategy();
    virtual ~cCreatureModeInputStrategy();
    uint8_t mnPad54[0x80];       // +0x054
    AutoRefCount<IWinText> mHoverText; // +0x0d4
    uint8_t mnPadD8[0x30];       // +0x0d8
    bool HandleMessage(uint32_t nMessage, cToolsEvent* pEvent); // 0x00d37c40
};

class cWalkAroundInputStrategy : public cCreatureModeInputStrategy {
public:
    EA::Messaging::AutoHandler mAutoHandler;          // +0x108
    AutoRefCount<cSPPlanetaryArtifact> mpCollectingArtifact; // +0x11c
    cWalkAroundInputStrategy();
    virtual ~cWalkAroundInputStrategy();
    bool HandleMessage(uint32_t nMessage, cToolsEvent* pEvent); // 0x0107bf40
};

class cUniverseContext {
public:
    bool IsAvailable();          // 0x00a98020
};

cUniverseContext* GetUniverseContext(); // 0x01015df0

// ---------------------------------------------------------------------------
// small helper state used by the large panel-population routines
// ---------------------------------------------------------------------------
class cPropertyKey {
public:
    uint32_t mInstance;          // +0x00
    uint32_t mType;              // +0x04
    uint32_t mGroup;             // +0x08
};

class cPanelHost {
public:
    uint8_t mnPad00[0x44];       // +0x000
    cUIObject* mpWindow;         // +0x044
};

// ---------------------------------------------------------------------------
// SP::cToolsPanelLeft::PopulateLeft
// @ 0x0107b6f0
// ---------------------------------------------------------------------------
bool cToolsPanelLeft::PopulateLeft(uint32_t nMessage, cToolsEvent* pEvent)
{
    (void)nMessage;
    switch (pEvent->mnType) {
    case 0x1b:
        if (pEvent->mpObject->GetTypeId() == 0x51aff90) {
            cSelectionManager* pSelection = NounManager()->mpSelection;
            void* pItem = pEvent->mpObject->GetItem();
            pSelection->Select(pItem);
            ((cSPUITools*)((char*)this - 8))->PopulateSelected(pEvent->mpObject);
        }
        break;
    case 0x1c:
        mLeftPanel.Reset();
        break;
    default:
        break;
    }
    return false;
}

// ---------------------------------------------------------------------------
// SP::cSPUITools::Open
// @ 0x0107bb00
// ---------------------------------------------------------------------------
void cSPUITools::Open(uint32_t nSlot)
{
    (void)nSlot;
}

// ---------------------------------------------------------------------------
// SP::cToolsMessage::OnMessage
// @ 0x0107bc30
// ---------------------------------------------------------------------------
bool cToolsMessage::OnMessage(uint32_t nMessage, cToolsEvent* pEvent)
{
    if (nMessage == 0xb3d53f95) {
        NounManager()->mpSelection->Select(mpSelectedMission->mpParentMission);

        cMissionCard* pNewCard = (cMissionCard*)pEvent->mpCard;
        cMissionCard* pOldCard = mpSelectedMission;
        if (pNewCard != pOldCard) {
            if (pNewCard != 0)
                pNewCard->AddRef();
            mpSelectedMission = pNewCard;
            if (pOldCard != 0)
                pOldCard->Release();
        }
        ((cSPUITools*)((char*)this - 0xc))->PopulateRight();
        return true;
    }
    return cUIMissionCardPanel::OnMessage(nMessage, pEvent);
}

// ---------------------------------------------------------------------------
// SP::cUniverseSimulatorTuning::cUniverseSimulatorTuning
// @ 0x0107bcc0
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// SP::cUniverseSimulatorTuning::UpdateTuning
// @ 0x0107bd40
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// SP::cUniverseSimulatorTuning::~cUniverseSimulatorTuning
// (the shipping scalar-deleting destructor lives at 0x0107be40)
// @ 0x0107be40
// ---------------------------------------------------------------------------
cUniverseSimulatorTuning::~cUniverseSimulatorTuning()
{
}

// ---------------------------------------------------------------------------
// SP::cUniverseSimulatorTuning::HandleMessage
// @ 0x0107bea0
// ---------------------------------------------------------------------------
bool cUniverseSimulatorTuning::HandleMessage(uint32_t nMessage,
                                             cUniverseTuningMessage* pMessage)
{
    if (nMessage == 0xf62def && pMessage->mnType == 0x3e9793b5)
        UpdateTuning();
    return false;
}

// ---------------------------------------------------------------------------
// SP::cUniverseSimulatorTuning::Init
// @ 0x0107bed0
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// SP::cWalkAroundInputStrategy::HandleMessage
// @ 0x0107bf40
// ---------------------------------------------------------------------------
bool cWalkAroundInputStrategy::HandleMessage(uint32_t nMessage,
                                             cToolsEvent* pEvent)
{
    if (!GetUniverseContext()->IsAvailable())
        return false;

    cMissionCard* pCard = 0;
    if (pEvent != 0) {
        cUIObject* pObject = pEvent->mpObject;
        if (pObject != 0)
            pCard = (cMissionCard*)pObject->GetItem();
    }

    if (nMessage == 0x3f3eb2c || nMessage == 0x17dab3f || nMessage == 0x1a53705)
        return false;

    if (nMessage == 0x2df01f2) {
        if (pCard == 0)
            return false;
        mHoverText.mpObject = 0;
        return true;
    }
    return cCreatureModeInputStrategy::HandleMessage(nMessage, pEvent);
}

// ---------------------------------------------------------------------------
// SP::cWalkAroundInputStrategy::cWalkAroundInputStrategy
// @ 0x0107c0b0
// ---------------------------------------------------------------------------
cWalkAroundInputStrategy::cWalkAroundInputStrategy()
{
}

// ---------------------------------------------------------------------------
// SP::cWalkAroundInputStrategy::~cWalkAroundInputStrategy
// @ 0x0107c160
// ---------------------------------------------------------------------------
cWalkAroundInputStrategy::~cWalkAroundInputStrategy()
{
}

// ---------------------------------------------------------------------------
// SP::cSPUITools::PopulateSelected
// @ 0x0107b260
// ---------------------------------------------------------------------------
bool cSPUITools::PopulateSelected(cUIObject* pObject)
{
    cPropertyList* pProperty = 0;
    uint32_t nTool = 0;
    uint32_t nAvailability = 0;

    cPropertyManager* pManager = PropertyManager();
    if (pProperty != 0) {
        pProperty->Release();
        pProperty = 0;
    }
    nTool = pObject->GetTypeId();
    pManager->GetProperty(0x30608f0b, nTool, &pProperty);
    GetToolAvailability(pProperty, &nTool, &nAvailability);
    if (pProperty != 0) {
        pProperty->Release();
        pProperty = 0;
    }
    return nAvailability != 0;
}

// ---------------------------------------------------------------------------
// SP::cSPUITools::PopulateRight
// @ 0x0107b760
// ---------------------------------------------------------------------------
void cSPUITools::PopulateRight()
{
    cPropertyList* pProperty = 0;
    uint32_t nTool = 0;
    uint32_t nAvailability = 0;

    cPropertyManager* pManager = PropertyManager();
    if (pProperty != 0) {
        pProperty->Release();
        pProperty = 0;
    }
    pManager->GetProperty(0x30608f0b, nTool, &pProperty);
    GetToolAvailability(pProperty, &nTool, &nAvailability);
    if (pProperty != 0) {
        pProperty->Release();
        pProperty = 0;
    }
}
