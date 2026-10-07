// slice s00587a20 -- SP::cAppModeEditorBase::Deactivate (2891 B).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc: the message local gets no EH frame).
//
// Deactivate is the mirror of Activate (slice s0058e6d0, which documents the retail layout of
// cAppModeEditorBase; offsets here were re-confirmed against this function's disassembly). It posts
// the "editor deactivated" behavior message, posts the editor-results message for the launch data,
// restores the UI layer / camera / hints, shuts down and releases every editor sub-system
// (models, spine, factories, rollovers, budget, naming, play mode, palettes, editor UI, background
// models, animated-creature manager, shadow world), deactivates the model worlds, clears input
// states, removes the message listeners and accumulates the active time.
//
// Names come from ModAPI `Editors::cEditor`, the Activate slice and the cards; names of callees
// without an evidence-backed name are descriptive.
#include "types.h"

typedef unsigned int size_t;

extern "C" long __cdecl _InterlockedExchange(volatile long* target, long value);
#pragma intrinsic(_InterlockedExchange)

// EA allocator new: new("Editor", 0, 0, 0, 0) T(...)
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct ResourceKey {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
};

// ---------------------------------------------------------------------------------------------
// EA::AutoRefCount (inline assignment; reset() is `= NULL`).
template <class T>
class AutoRefCount {
public:
    T* mpObject;

    AutoRefCount& operator=(T* pObject)
    {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};

// EA::RefCountTemplate-style inline release (refcount right after the vptr; 1 is stored back
// before the deleting dtor runs).
class RefCountTemplate {
public:
    virtual ~RefCountTemplate();
    int mnRefCount;

    int AddRef() { return ++mnRefCount; }
    int Release()
    {
        int n = --*(volatile int*)&mnRefCount;
        if (n == 0) {
            mnRefCount = 1;
            delete this;
            return 0;
        }
        return n;
    }
};

// Reference-counted interfaces, by the vtable slot of AddRef/Release.
class IRefCounted0 {   // AddRef +0, Release +4
public:
    virtual int AddRef();
    virtual int Release();
};
class IRefCounted4 {   // AddRef +4, Release +8
public:
    virtual void _v00();
    virtual int AddRef();
    virtual int Release();
};

// ---------------------------------------------------------------------------------------------
// Graphics
class IModelWorld;
class cMWModel {   // Graphics::Model
public:
    IModelWorld* mpWorld;   // +00
    uint32_t mFlags;        // +04
    uint32_t mTransform[14];
    int mnRefCount;         // +40

    int AddRef() { return ++mnRefCount; }
    int Release();
};

class ILightingWorld : public IRefCounted0 {};

class IModelWorld {
public:
#define VS(n) virtual void _v##n();
    VS(00) VS(04) VS(08) VS(0C) VS(10) VS(14) VS(18) VS(1C) VS(20) VS(24) VS(28) VS(2C) VS(30) VS(34) VS(38) VS(3C)
    VS(40) VS(44) VS(48) VS(4C) VS(50) VS(54) VS(58) VS(5C) VS(60) VS(64) VS(68) VS(6C) VS(70) VS(74) VS(78) VS(7C)
    VS(80) VS(84) VS(88) VS(8C) VS(90) VS(94) VS(98) VS(9C) VS(A0) VS(A4) VS(A8) VS(AC) VS(B0) VS(B4) VS(B8) VS(BC)
    VS(C0) VS(C4) VS(C8) VS(CC) VS(D0) VS(D4) VS(D8) VS(DC) VS(E0) VS(E4) VS(E8) VS(EC) VS(F0) VS(F4) VS(F8) VS(FC)
    VS(100) VS(104) VS(108) VS(10C) VS(110) VS(114) VS(118) VS(11C) VS(120) VS(124) VS(128) VS(12C) VS(130)
    virtual void SetActive(bool active);                                              // 134h
    VS(138) VS(13C)
    virtual int SetLightingWorld(ILightingWorld* pWorld, int indexDrawSet, bool drawShadows);  // 140h
    VS(144) VS(148) VS(14C) VS(150) VS(154) VS(158) VS(15C) VS(160) VS(164) VS(168)
    virtual void SetInWorld(cMWModel* model, bool inWorld);                          // 16Ch
    virtual void DestroyModel(cMWModel* model, bool flag);                            // 170h
};

inline int cMWModel::Release()
{
    if (mnRefCount > 1) {
        mnRefCount = mnRefCount - 1;
        return mnRefCount;
    }
    mpWorld->DestroyModel(this, (bool)((mFlags >> 31) & 1));
    return 0;
}

class IEffectsWorld {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08();
    virtual void SetState(int state);   // 0Ch
    virtual void _v10(); virtual void _v14(); virtual void _v18(); virtual void _v1C();
    virtual void _v20(); virtual void _v24(); virtual void _v28(); virtual void _v2C(); virtual void _v30();
    virtual void Deactivate();          // 34h
};

class IShadowWorld : public IRefCounted0 {
public:
    virtual void _v08(); virtual void _v0C(); virtual void _v10(); virtual void _v14(); virtual void _v18();
    virtual void _v1C(); virtual void _v20();
    virtual void Clear();               // 24h
    virtual void SetActive(bool active);   // 28h
};

class cEffectsManager {
public:
    VS(00) VS(04) VS(08) VS(0C) VS(10) VS(14) VS(18) VS(1C) VS(20) VS(24) VS(28) VS(2C) VS(30) VS(34) VS(38) VS(3C)
    VS(40) VS(44) VS(48) VS(4C) VS(50) VS(54)
    virtual void SetActiveWorld(IEffectsWorld* world);   // 58h
    VS(5C) VS(60) VS(64) VS(68) VS(6C) VS(70) VS(74) VS(78) VS(7C) VS(80) VS(84) VS(88) VS(8C) VS(90) VS(94)
    virtual void SetFlags(int flags, int value);   // 98h
};

class cModelManager {
public:
    VS(00) VS(04) VS(08) VS(0C) VS(10) VS(14) VS(18) VS(1C) VS(20)
    virtual void SetSaveModelWorld(IModelWorld* world);   // 24h
};

class cRenderTarget {
public:
    VS(00) VS(04) VS(08) VS(0C) VS(10) VS(14) VS(18) VS(1C)
    virtual void ClearValue(uint32_t value);   // 20h
};
class cRenderTargets {
public:
    VS(00) VS(04) VS(08) VS(0C) VS(10) VS(14) VS(18) VS(1C)
    virtual cRenderTarget* GetTarget();   // 20h
};

class cRenderManager {
public:
    IModelWorld* GetUILayerModelWorld();   // 0x006c10e0
};

class cViewer {
public:
    void SetViewAngleY(float angle);   // 0x007c53d0
};

class cApp {
public:
    VS(00) VS(04) VS(08) VS(0C) VS(10) VS(14) VS(18) VS(1C) VS(20) VS(24) VS(28) VS(2C) VS(30) VS(34) VS(38) VS(3C)
    VS(40) VS(44) VS(48) VS(4C) VS(50) VS(54)
    virtual cViewer* GetViewer();   // 58h
};

class cCheatManager {
public:
    VS(00) VS(04) VS(08) VS(0C) VS(10) VS(14) VS(18)
    virtual void RemoveCheats(const char* tag);   // 1Ch
};

class cInputManager {
public:
    VS(00) VS(04) VS(08) VS(0C) VS(10) VS(14) VS(18) VS(1C) VS(20) VS(24) VS(28) VS(2C) VS(30) VS(34) VS(38) VS(3C)
    VS(40) VS(44) VS(48) VS(4C)
    virtual void ClearState(int state);   // 50h
};

class cGameInputManager {
public:
    VS(00) VS(04) VS(08) VS(0C) VS(10) VS(14) VS(18) VS(1C) VS(20) VS(24) VS(28)
    virtual void Reset();   // 2Ch
};

class IAudioSystem {
public:
    VS(00) VS(04) VS(08) VS(0C) VS(10) VS(14) VS(18) VS(1C) VS(20) VS(24) VS(28) VS(2C) VS(30) VS(34)
    virtual void SetGroup(uint32_t id);                    // 38h
    VS(3C)
    virtual void SetValue(uint32_t id, uint32_t value);    // 40h
    VS(44) VS(48) VS(4C) VS(50) VS(54)
    virtual void Commit();                                 // 58h
};
#undef VS

class cHintManager {
public:
    void ClearHints();                        // 0x0067ca40
    void SetEnabled(bool enabled, bool b);    // 0x0067c420
};

class cPropertyUI {
public:
    void DestroyAllElems();   // 0x0067a120
};

class cDisplayObject {
public:
    char pad[0xb9];
    bool mbFlagB9;   // +b9
};
class cDisplayManager {
public:
    cDisplayObject* GetPrimary();     // 0x0113ae10
    cDisplayObject* GetSecondary();   // 0x00801920
};

class cSwarmManager {
public:
    void ClearEditorEffects();   // 0x0045ab30
};

class cCursorManager {
public:
    void SetLocalCursor(uint32_t id);   // 0x00801bb0
};

class IWindow {
public:
    virtual void _v00();
};
class IWindowManager {
public:
    virtual void _v00();
    virtual IWindow* GetMainWindow();   // 04h
};
class cMainWinBase {
public:
    virtual void _v00();
};
class cSPUIMainWin : public cMainWinBase, public IWindow {
public:
    uint64_t GetTimeStamp();   // 0x008130a0
};

class cDirectPropertyList {
public:
    char pad[0x3c];
    struct cConfig { char pad[0x118]; int mnValue118; }* mpConfig;   // +3c
    void SetIntProperty(uint32_t id, int value);   // 0x006a1880
};

class IHandler;
class IMessageServer {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0C(); virtual void _v10();
    virtual void PostMSG(uint32_t messageID, void* msg, int arg);                  // 14h
    virtual void PostMessage(uint32_t messageID, IRefCounted4* msg, int a, int b);  // 18h
};

// ---------------------------------------------------------------------------------------------
// Behavior message posted when the editor deactivates (vtable 0x013eb844, base 0x013eb90c).
class cBehaviorMessage {
public:
    virtual void _v00();
    volatile long mnRefCount;   // +04
    cBehaviorMessage() { _InterlockedExchange(&mnRefCount, 0); }
};
// The message ID lives in a non-polymorphic base that MSVC places after the vptr base but
// constructs first, which is why the ID store precedes the base vtable store.
struct cMessageHeader {
    uint32_t mModeID;        // +08
    uint32_t field_C[9];
    uint32_t mMessageID;     // +30
    uint32_t field_34;
    cMessageHeader(uint32_t id) : mMessageID(id) {}
};
class cEditorDeactivatedMessage : public cMessageHeader, public cBehaviorMessage {
public:
    void* mpData;            // +38
    uint32_t field_3C;

    cEditorDeactivatedMessage() : cMessageHeader(0x60c874f), mpData(0) {}
    virtual void _v00();
    ~cEditorDeactivatedMessage();   // 0x00421cf0
};

// Editor launch data (Editor::cEditorLaunchData).
class cEditorLaunchData : public IRefCounted4 {
public:
    uint32_t pad04[3];
    ResourceKey mModelKey;           // +10
    uint32_t pad1C[29];
    uint32_t mCallerID;              // +90
    IRefCounted0* mpCallerData;      // +94
};

// Editor results message (0x30c11c7), 0x48 bytes; ctor 0x00579c80.
class cEditorResultsMessage : public IRefCounted4 {
public:
    uint32_t pad04[2];
    uint32_t mCallerID;                     // +0c
    AutoRefCount<IRefCounted0> mpCallerData;  // +10
    uint32_t mModelID;                      // +14
    ResourceKey mModelKey;                  // +18
    uint32_t pad24[8];
    bool mbAccepted;                        // +44

    cEditorResultsMessage();   // 0x00579c80
};

// ---------------------------------------------------------------------------------------------
// Editor sub-systems.
namespace SP {

class cSPEditorBlock : public IRefCounted4 {
public:
    char pad04[0xdc8 - 4];
    uint32_t mBlockFlags;   // +dc8
    bool IsFlagSet1() const { return ((mBlockFlags >> 1) & 1) != 0; }
    void SetUIState(int state, bool b);   // 0x0043a9a0
};

class cSPEditorHandle : public IRefCounted0 {
public:
    cSPEditorBlock* GetRigblock();   // 0x0047e6c0
};

class cSPEditorModel : public IRefCounted4, public RefCountTemplate {
public:
    uint32_t pad0C[19];
    uint32_t mModelID;   // +58
    using RefCountTemplate::AddRef;
    using RefCountTemplate::Release;
    void ClearSelection();   // 0x004ad280
    void ClearBlocks();      // 0x004ad330
};

class cSPEditorSpine : public IRefCounted4 {
public:
    void ClearVertebrae();   // 0x005d31b0
};
class cSPResourceFactory : public IRefCounted0 {
public:
    void Shutdown();   // 0x004c4eb0
};
class cRollover : public IRefCounted0 {
public:
    virtual void _v08(); virtual void _v0C(); virtual void _v10(); virtual void _v14(); virtual void _v18();
    virtual void _v1C(); virtual void _v20();
    virtual void Shutdown();   // 24h
};
class cSPVerbTrayCollection : public IRefCounted0 {
public:
    virtual void _v08(); virtual void _v0C(); virtual void _v10(); virtual void _v14();
    virtual void Shutdown();   // 18h
};
class cSPEditorBudget {
public:
    virtual void _v00(); virtual void _v04();
    virtual int AddRef();    // 08h
    virtual int Release();   // 0Ch
    void Shutdown();         // 0x004581d0
};
class cSPEditorComplexityMeter : public IRefCounted0 {
public:
    void Shutdown();   // 0x00ed0660
};
class cSPEditorStatsPanel : public IRefCounted0 {
public:
    void Shutdown();   // 0x0059a3b0
};
class cSPEditorNaming : public IRefCounted0 {
public:
    void Shutdown();   // 0x005bfb90
};
class cSPPlayMode : public IRefCounted4 {
public:
    void Shutdown();   // 0x0062c910
};
class cSPEditorPaintTheme : public IRefCounted0 {
public:
    void Reset();   // 0x004b27c0
};
class cSPPaletteUI : public IRefCounted0 {
public:
    void Shutdown();   // 0x005cba90
};
class cSPPalette : public IRefCounted4 {
public:
    void Shutdown();   // 0x005c5c20
};
class cSPEditorUIBase {
public:
    virtual void _v00();
};
class cSPEditorUI : public cSPEditorUIBase, public IRefCounted0 {
public:
    void Shutdown();   // 0x005de870
};
class cSPEditorAnimatedCreatureManager : public RefCountTemplate {
public:
    void Shutdown();   // 0x0059c640
};
class cEditorTool : public IRefCounted0 {
public:
    virtual void _v08(); virtual void _v0C(); virtual void _v10(); virtual void _v14(); virtual void _v18();
    virtual void _v1C(); virtual void _v20(); virtual void _v24(); virtual void _v28(); virtual void _v2C();
    virtual void Shutdown();   // 30h
};

cApp* App();                          // 0x0067dd10
IMessageServer* MessageServer();      // 0x0067dcc0
cCheatManager* CheatManager();        // 0x0067de20
cRenderTargets* RenderTargets();      // 0x0067de40
cHintManager* HintManager();          // 0x0067cac0
cPropertyUI* PropertyUI();            // 0x0067caf0
cRenderManager* RenderManager();      // 0x0067cad0
cDisplayManager* DisplayManager();    // 0x00401020
cSwarmManager* SwarmManager();        // 0x00401050
cEffectsManager* EffectsManager();    // 0x0067ddd0
cModelManager* ModelManager();        // 0x0067dd80
cInputManager* InputManager();        // 0x0067dd50
cGameInputManager* GameInputManager();  // 0x0067dd40
IWindowManager* WindowManager();      // 0x0067caa0
cCursorManager* CursorManager();      // 0x0067cab0
void SetShaderParam(int id, void* pValue, int arg);   // 0x00777ae0

extern cDirectPropertyList* g_pAppProperties;   // 0x015fd918
extern uint32_t* g_pRenderFlags;                // 0x016f6ee0
extern uint32_t g_RenderTargetValue;            // 0x015eebec

}  // namespace SP

namespace EA { namespace Audio { IAudioSystem* GetSystemAT(); } }   // 0x00a206f0
namespace EA { namespace Messaging {
void RemoveHandler(IMessageServer* pServer, IHandler* pHandler, const uint32_t* pIDs, int count, int flags);  // 0x00571db0
} }

// Registers one handler for a fixed list of message IDs (stored on the editor so it can unregister).
struct cMessageListenerRegistration {
    IMessageServer* mpServer;
    IHandler* mpHandler;
    const uint32_t* mpMessageIDs;
    int mnCount;
    int mnFlags;

    void Unregister()
    {
        if (mpServer) {
            IMessageServer* pServer = mpServer;
            mpServer = 0;
            EA::Messaging::RemoveHandler(pServer, mpHandler, mpMessageIDs, mnCount, mnFlags);
        }
    }
};

// ---------------------------------------------------------------------------------------------
class cIAppMode {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0C(); virtual void _v10(); virtual void _v14();
    virtual void _v18(); virtual void _v1C(); virtual void _v20(); virtual void _v24(); virtual void _v28(); virtual void _v2C();
    virtual void _v30(); virtual void _v34(); virtual void _v38(); virtual void _v3C(); virtual void _v40();
    virtual uint32_t GetModeID();        // 44h
    virtual void _v48();
    virtual void ClearUndoRedo();        // 4Ch
};

namespace SP {

class cAppModeEditorBase : public cIAppMode {
public:
    uint32_t pad004[29];
    /* 078h */ AutoRefCount<cSPEditorUI> mpEditorUI;
    /* 07Ch */ AutoRefCount<cSPPlayMode> mpPlayMode;
    /* 080h */ ILightingWorld* mpLightingWorld;
    /* 084h */ IModelWorld* mpMainModelWorld;
    /* 088h */ IModelWorld* mSaveModelWorld;
    /* 08Ch */ IModelWorld* mpBackgroundModelWorld;
    /* 090h */ void* mpPhysicsWorld;
    /* 094h */ IEffectsWorld* mpEffectWorld;
    /* 098h */ AutoRefCount<cSPEditorModel> mpEditorModel;
    /* 09Ch */ AutoRefCount<cSPEditorModel> mpEditorSaveModel;
    /* 0A0h */ AutoRefCount<cMWModel> mpPedestalModel;
    /* 0A4h */ AutoRefCount<cMWModel> mpTestEnvironmentModel;
    /* 0A8h */ AutoRefCount<cMWModel> mpBackgroundModel;
    /* 0ACh */ AutoRefCount<cMWModel> mpPlayModeBackgroundModel;
    uint32_t pad0B0[8];
    /* 0D0h */ AutoRefCount<IRefCounted4> mpUndoQueue;
    /* 0D4h */ AutoRefCount<cSPEditorBlock> mpPreviousSelectedBlock;
    uint32_t pad0D8[3];
    /* 0E4h */ AutoRefCount<cSPEditorHandle> mpRolloverHandle;
    /* 0E8h */ bool mTorsoUIState;
    /* 0E9h */ bool mbTorsoInEffectsMask;
    uint8_t pad0EA[2];
    uint32_t pad0EC[22];
    /* 144h */ bool field_144;
    uint8_t pad145[3];
    /* 148h */ AutoRefCount<cEditorTool> mpTool;
    /* 14Ch */ AutoRefCount<cSPEditorSpine> mpSpine;
    /* 150h */ AutoRefCount<cSPResourceFactory> mpSaveLoadFactory;
    /* 154h */ AutoRefCount<cSPResourceFactory> mpTextureFactory;
    uint32_t pad158[21];
    /* 1ACh */ AutoRefCount<ILightingWorld> mpUILayerOldLightingWorld;
    uint32_t pad1B0[7];
    /* 1CCh */ AutoRefCount<cEditorLaunchData> mpLaunchData;
    uint32_t pad1D0[15];
    uint8_t pad20C[2];
    /* 20Eh */ bool mbBackgroundMusic;
    uint8_t pad20F[1];
    uint32_t pad210[33];
    /* 294h */ AutoRefCount<IShadowWorld> mpShadowWorld;
    uint32_t pad298[1];
    /* 29Ch */ AutoRefCount<cSPEditorPaintTheme> mDefaultPaintTheme;
    /* 2A0h */ AutoRefCount<cSPEditorPaintTheme> mCurrentPaintTheme;
    /* 2A4h */ AutoRefCount<cSPVerbTrayCollection> mVerbIconTray;
    uint32_t pad2A8[2];
    /* 2B0h */ bool mIsActive;
    uint8_t pad2B1[3];
    uint32_t pad2B4[39];
    /* 350h */ AutoRefCount<cSPEditorBudget> mpBudget;
    /* 354h */ AutoRefCount<cSPEditorComplexityMeter> mpComplexityMeter;
    /* 358h */ AutoRefCount<cSPEditorNaming> mpNaming;
    /* 35Ch */ AutoRefCount<cSPEditorStatsPanel> mpStatsPanel;
    /* 360h */ AutoRefCount<cSPEditorAnimatedCreatureManager> mpAnimCreatureManager;
    /* 364h */ int field_364;
    /* 368h */ int field_368;
    uint32_t pad36C[5];
    /* 380h */ AutoRefCount<IRefCounted4> mpCreationController;
    /* 384h */ bool field_384;
    /* 385h */ bool field_385;
    uint8_t pad386[2];
    uint32_t pad388[12];
    /* 3B8h */ AutoRefCount<cSPPalette> mpPaintPalette;
    /* 3BCh */ AutoRefCount<cSPPaletteUI> mpPaintPaletteUI;
    /* 3C0h */ AutoRefCount<cSPPalette> mpPartsPalette;
    /* 3C4h */ AutoRefCount<cSPPaletteUI> mpPartsPaletteUI;
    uint32_t pad3C8[28];
    /* 438h */ uint64_t mnActivateTime;
    /* 440h */ uint64_t mnModelStartTime;
    /* 448h */ uint64_t mnTotalActiveTime;
    /* 450h */ int field_450;
    uint32_t pad454[16];
    /* 494h */ AutoRefCount<cRollover> mpSellBackRollover;
    /* 498h */ AutoRefCount<cRollover> mpSellBackRollover2;
    /* 49Ch */ AutoRefCount<cRollover> mpMessageRollover;
    /* 4A0h */ AutoRefCount<cRollover> mpDetachedRollover;
    /* 4A4h */ AutoRefCount<cRollover> mpDetachedRollover2;
    uint32_t pad4A8[3];
    uint8_t pad4B4[2];
    /* 4B6h */ bool field_4B6;
    uint8_t pad4B7[1];
    uint32_t pad4B8[1];
    /* 4BCh */ AutoRefCount<IRefCounted4> mpCameraController;
    uint32_t pad4C0[4];
    /* 4D0h */ float field_4D0;
    uint32_t pad4D4[64];
    /* 5D4h */ cMessageListenerRegistration mMessageRegistration;

    bool SetMode(int mode, bool bForce);            // 0x00587270
    void RemoveTorsoFromEffectsMask();              // 0x005772b0
    void SetSelection(int a, int b);                // 0x00573c00
    void SetRolloverHandle(int handle, bool b);     // 0x00573d70
    void DestroyEditorWidgets(bool b);              // 0x005dbb60
    void HideDebugUI();                             // 0x005dbb50

    void Deactivate();   // 0x00587a20
};

// @ 0x00587a20
void cAppModeEditorBase::Deactivate()
{
    if (mpEffectWorld)
        mpEffectWorld->Deactivate();
    g_pAppProperties->SetIntProperty(0xb, field_450);
    mIsActive = false;
    if (PropertyUI())
        PropertyUI()->DestroyAllElems();

    cEditorDeactivatedMessage msg;
    msg.mModeID = GetModeID();
    MessageServer()->PostMSG(msg.mMessageID, &msg, 0);

    *g_pRenderFlags &= ~1u;
    ClearUndoRedo();
    mpCreationController = 0;
    HintManager()->ClearHints();
    HintManager()->SetEnabled(field_144, true);
    if (App())
        App()->GetViewer()->SetViewAngleY(field_4D0);
    mpCameraController = 0;
    DestroyEditorWidgets(true);
    if (g_pAppProperties->mpConfig->mnValue118)
        HideDebugUI();
    CheatManager()->RemoveCheats("editor");
    RenderTargets()->GetTarget()->ClearValue(g_RenderTargetValue);

    if (mpLaunchData) {
        cEditorResultsMessage* pResults = new ("Editor", 0, 0, 0, 0) cEditorResultsMessage();
        if (pResults)
            pResults->AddRef();
        pResults->mCallerID = mpLaunchData->mCallerID;
        pResults->mpCallerData = mpLaunchData->mpCallerData;
        pResults->mModelKey = mpLaunchData->mModelKey;
        pResults->mModelID = mpEditorModel->mModelID;
        pResults->mbAccepted = true;
        MessageServer()->PostMessage(0x30c11c7, pResults, 0, 0);
        mpLaunchData = 0;
        pResults->Release();
    }

    if (App())
        SetMode(0, true);
    if (RenderManager()->GetUILayerModelWorld() && mpUILayerOldLightingWorld)
        RenderManager()->GetUILayerModelWorld()->SetLightingWorld(mpUILayerOldLightingWorld, 0, true);
    RemoveTorsoFromEffectsMask();
    SetSelection(0, -1);

    if (cSPEditorBlock* pBlock = mpPreviousSelectedBlock) {
        if (!pBlock->IsFlagSet1()) {
            if (mpRolloverHandle && mpRolloverHandle->GetRigblock() == pBlock)
                SetRolloverHandle(0, true);
            mpPreviousSelectedBlock->SetUIState(0, true);
        }
        mpPreviousSelectedBlock = 0;
    }
    if (mTorsoUIState)
        mTorsoUIState = false;
    if (mbTorsoInEffectsMask) {
        RemoveTorsoFromEffectsMask();
        mbTorsoInEffectsMask = false;
    }

    if (IAudioSystem* pAudio = EA::Audio::GetSystemAT()) {
        pAudio->SetGroup(0x347536b);
        pAudio->SetValue(0x3475385, 0x1d6253c0);
        pAudio->SetValue(0x34753a0, 0);
        pAudio->Commit();
    }
    if (IAudioSystem* pAudio = EA::Audio::GetSystemAT()) {
        pAudio->SetGroup(0x347536b);
        pAudio->SetValue(0x3475385, 0xb07c3bbf);
        pAudio->SetValue(0x34753a0, 0);
        pAudio->Commit();
    }
    mbBackgroundMusic = false;
    SwarmManager()->ClearEditorEffects();
    EffectsManager()->SetFlags(0x10, 0);

    if (mpEditorModel) {
        mpEditorModel->ClearSelection();
        mpEditorModel->ClearBlocks();
        mpEditorModel = 0;
    }
    if (mpEditorSaveModel) {
        mpEditorSaveModel->ClearSelection();
        mpEditorSaveModel->ClearBlocks();
        mpEditorSaveModel = 0;
    }
    if (mpSpine) {
        mpSpine->ClearVertebrae();
        mpSpine = 0;
    }
    if (mpSaveLoadFactory) {
        mpSaveLoadFactory->Shutdown();
        mpSaveLoadFactory = 0;
    }
    if (mpTextureFactory) {
        mpTextureFactory->Shutdown();
        mpTextureFactory = 0;
    }
    if (cDisplayObject* p = DisplayManager()->GetPrimary())
        p->mbFlagB9 = field_4B6;
    if (cDisplayObject* p = DisplayManager()->GetSecondary())
        p->mbFlagB9 = field_4B6;
    if (mpSellBackRollover) {
        mpSellBackRollover->Shutdown();
        mpSellBackRollover = 0;
    }
    if (mpSellBackRollover2) {
        mpSellBackRollover2->Shutdown();
        mpSellBackRollover2 = 0;
    }
    if (mpMessageRollover) {
        mpMessageRollover->Shutdown();
        mpMessageRollover = 0;
    }
    if (mpDetachedRollover) {
        mpDetachedRollover->Shutdown();
        mpDetachedRollover = 0;
    }
    if (mpDetachedRollover2) {
        mpDetachedRollover2->Shutdown();
        mpDetachedRollover2 = 0;
    }
    if (mVerbIconTray) {
        mVerbIconTray->Shutdown();
        mVerbIconTray = 0;
    }
    if (mpBudget) {
        mpBudget->Shutdown();
        mpBudget = 0;
    }
    if (mpComplexityMeter) {
        mpComplexityMeter->Shutdown();
        mpComplexityMeter = 0;
    }
    if (mpStatsPanel) {
        mpStatsPanel->Shutdown();
        mpStatsPanel = 0;
    }
    if (mpNaming) {
        mpNaming->Shutdown();
        mpNaming = 0;
    }
    if (mpPlayMode) {
        mpPlayMode->Shutdown();
        mpPlayMode = 0;
    }
    if (mDefaultPaintTheme) {
        mDefaultPaintTheme->Reset();
        mDefaultPaintTheme = 0;
    }
    if (mCurrentPaintTheme) {
        mCurrentPaintTheme->Reset();
        mCurrentPaintTheme = 0;
    }
    if (mpPaintPaletteUI) {
        mpPaintPaletteUI->Shutdown();
        mpPaintPaletteUI = 0;
    }
    if (mpPaintPalette) {
        mpPaintPalette->Shutdown();
        mpPaintPalette = 0;
    }
    if (mpPartsPaletteUI) {
        mpPartsPaletteUI->Shutdown();
        mpPartsPaletteUI = 0;
    }
    if (mpPartsPalette) {
        mpPartsPalette->Shutdown();
        mpPartsPalette = 0;
    }
    if (mpEditorUI) {
        mpEditorUI->Shutdown();
        mpEditorUI = 0;
    }
    mpRolloverHandle = 0;
    if (mpPedestalModel) {
        mpPedestalModel->mpWorld->SetInWorld(mpPedestalModel, false);
        mpPedestalModel = 0;
    }
    if (mpTestEnvironmentModel) {
        mpTestEnvironmentModel->mpWorld->SetInWorld(mpTestEnvironmentModel, false);
        mpTestEnvironmentModel = 0;
    }
    if (mpBackgroundModel) {
        mpBackgroundModel->mpWorld->SetInWorld(mpBackgroundModel, false);
        mpBackgroundModel = 0;
    }
    if (mpPlayModeBackgroundModel) {
        mpPlayModeBackgroundModel->mpWorld->SetInWorld(mpPlayModeBackgroundModel, false);
        mpPlayModeBackgroundModel = 0;
    }
    if (mpAnimCreatureManager) {
        mpAnimCreatureManager->Shutdown();
        mpAnimCreatureManager = 0;
    }
    field_385 = false;
    field_384 = false;
    field_364 = 0;
    field_368 = 0;
    if (mpTool) {
        mpTool->Shutdown();
        mpTool = 0;
    }
    mpUndoQueue = 0;
    if (mpShadowWorld) {
        mpShadowWorld->SetActive(false);
        mpShadowWorld->Clear();
        mpShadowWorld = 0;
    }
    if (mpMainModelWorld)
        mpMainModelWorld->SetActive(false);
    if (mpBackgroundModelWorld)
        mpBackgroundModelWorld->SetActive(false);
    ModelManager()->SetSaveModelWorld(0);
    InputManager()->ClearState(0xf);
    InputManager()->ClearState(0xc);
    InputManager()->ClearState(0xd);
    InputManager()->ClearState(0x1a);
    InputManager()->ClearState(0x11);
    InputManager()->ClearState(0x14);
    if (mpEffectWorld) {
        mpEffectWorld->SetState(2);
        EffectsManager()->SetActiveWorld(0);
    }
    GameInputManager()->Reset();
    mMessageRegistration.Unregister();

    IWindow* pWindow = WindowManager()->GetMainWindow();
    cSPUIMainWin* pMainWin = static_cast<cSPUIMainWin*>(pWindow);
    mnTotalActiveTime += pMainWin->GetTimeStamp() - mnActivateTime;
    CursorManager()->SetLocalCursor(0x1002);
    SetShaderParam(0x238, 0, 1);
    SetShaderParam(0x236, 0, 1);
}

}  // namespace SP
