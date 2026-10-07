// Slice s00fe0f40: SP::cAppModeSpace::HandleSimulationUpdate (0x00fe0f40, 2647 bytes).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (scalar SSE math, __asm float helpers, no /EHsc needed).
//
// Per-frame update of the space game mode: counts down a delayed message, waits for the
// planet-entry bakes, drives the solar->planet and entry->new-game transitions, the scripted
// tutorial steps, then ticks the simulator subsystems (game time, UFO keys, community editor,
// every game noun of one type, tool effects), runs the player's current space tool, handles
// mouse-driven planet navigation / edge spin, the camera mouse wheel, the UI and finally the
// planet-follow camera.
//
// Member offsets are retail (dev PDB cAppModeSpace shifted by +0x5c and extended). Callees that
// only have FUN_ names are named after their use here (descriptive, not PDB).
#include "types.h"
#include <math.h>

#pragma warning(disable : 4035)

// EA float->int64 helper: fistp in the current (round-to-nearest) mode. The 8-aligned result
// is what gives the caller its `and esp,-8` frame.
inline int64_t FloatToInt64(float f)
{
    __declspec(align(8)) int64_t result;
    __asm fld f
    __asm fistp result
    return result;
}

// float->int with the current MXCSR rounding (asm helper in the original).
__forceinline int RoundToInt(float f) { __asm cvtss2si eax, f }

__forceinline float Clamp(float value, float minValue, float maxValue)
{
    __asm {
        movss xmm0, value
        maxss xmm0, minValue
        minss xmm0, maxValue
        movss value, xmm0
    }
    return value;
}

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4

struct Vector2 {
    float x, y;
};

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
    Vector3 operator*(float s) const { return Vector3(x * s, y * s, z * s); }
};

struct Matrix3 { float m[9]; };

// cSPTransform (0x38 bytes)
struct Transform {
    uint16_t mFlags;
    uint16_t mChangeCount;
    Vector3 mOffset;      // +0x04
    float mScale;         // +0x10
    Matrix3 mRotation;    // +0x14
    Transform();          // 0x00409930
};

struct ResourceKey {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
};

struct Rect {
    int left, top, right, bottom;
};

Vector3 normalized_safe(const Vector3& v);                   // 0x00449c20

void operator delete[](void* p);                              // 0x00f47380

namespace eastl {
struct ListNodeBase {
    ListNodeBase* mpNext;
    ListNodeBase* mpPrev;
};
template <typename T>
struct ListNode : public ListNodeBase {
    T mValue;
};
template <typename T>
struct list {
    typedef ListNode<T> node_type;
    ListNodeBase mNode;
    uint32_t mAllocator;

    bool empty() const { return mNode.mpNext == &mNode; }
    T& front() { return ((node_type*)mNode.mpNext)->mValue; }
    void pop_front()
    {
        node_type* pNode = (node_type*)mNode.mpNext;
        pNode->mpPrev->mpNext = pNode->mpNext;
        pNode->mpNext->mpPrev = pNode->mpPrev;
        operator delete[](pNode);
    }
};
}  // namespace eastl

namespace EA {
struct Stopwatch {
    uint32_t data[6];
    uint64_t GetElapsedTime() const;                          // 0x0093a5e0
};
}

namespace SP {

// ----------------------------------------------------------------------------- managers

struct IMessageManager {                                      // FUN_0067dd20()
    PV8 PV2
    virtual void PostMSG(uint32_t messageID);                 // +0x28
};
IMessageManager* MessageManager();                            // 0x0067dd20

struct IBakeManager {                                         // FUN_00401010()
    PV8 PV4 PV2 PV
    virtual bool IsBaked(const ResourceKey& key);             // +0x3c
};
IBakeManager* BakeManager();                                  // 0x00401010

struct cTerrainSphere {
    PV4
    virtual struct cPlanetCenter* GetCenter();                // +0x10
    PV8 PV4 PV2 PV
    virtual bool IsReady();                                   // +0x50
};
struct cPlanetCenter {
    Vector3 GetPosition();                                    // 0x00fb8db0
};

struct cPlanetModel {
    uint32_t pad00[0x24 / 4];
    cTerrainSphere* mpTerrain;                                // +0x24
    void FinishPlanetLoad();                                  // 0x00b84270
    void ActivatePlanet();                                    // 0x00b88420
    float GetMinAltitude();                                   // 0x00b7e4d0
};
cPlanetModel* PlanetModel();                                  // 0x00b3d350

struct cPlanetRenderer { void OnPlanetEntered(); };           // 0x00b515e0
cPlanetRenderer* PlanetRenderer();                            // 0x00b3d310

struct cTutorialManager {                                     // FUN_00b3d410()
    bool IsActive();                                          // 0x00e36fa0
    void StartIntro();                                        // 0x00e36de0
    bool IsIntroDone();                                       // 0x00e36dd0
    void StartStep2();                                        // 0x00e3b1f0
    bool IsStep2Done();                                       // 0x00e36e10
    void Finish(int a, const char* name, int b);              // 0x00e3e350
};
cTutorialManager* TutorialManager();                          // 0x00b3d410
extern const char g_tutorialFinishName[];                     // 0x01654c05

struct cTestSystem {
    uint32_t pad00[0x70 / 4];
    eastl::ListNodeBase mTests;                               // +0x70
};
extern cTestSystem* sTestSystem;                              // 0x015fd928

struct cGameState { uint32_t pad00[0x2c / 4]; int mState; };  // +0x2c
cGameState* GameState();                                      // 0x00b3d4d0

struct cEmpire { int* GetCities(); };                         // 0x00c30f90
struct cSPLivingUniverse {
    static cEmpire* GetPlayerEmpire();                        // 0x01021300
    static int GetUniverseContext();                          // 0x01021080
};
void OnPlayerEmpireHasNoCities();                             // 0x00e1dc70

struct cSimulatorSystem {                                     // FUN_00b3d230()
    PV8 PV2 PV
    virtual void Update(int deltaMS);                         // +0x2c
    virtual void PostUpdate(int deltaMS);                     // +0x30
    void UpdateMessages(int deltaMS);                         // 0x00b5e9a0
};
cSimulatorSystem* SimulatorSystem();                          // 0x00b3d230

struct cGameTimeManager {
    uint32_t pad00[0x48 / 4];
    uint8_t mFlags;                                           // +0x48 (bit 0: paused)
    int UpdateTime(int deltaMS);                              // 0x00b31c60
};
cGameTimeManager* GameTimeManager();                          // 0x00b3d380
void UpdateGameTime(int gameDeltaMS);                         // 0x01022920

struct cSPUISpace { void UpdateUI(int deltaMS); };                   // 0x010743a0
struct cCommunityEditor {
    void HandleSimulationUpdate(int deltaMS);                 // 0x00d124e0
    bool IsOpen();                                            // 0x00d09660
};

struct cSpatialObject {
    PV8 PV2 PV
    virtual const Vector3& GetPosition();                     // +0x2c
};

struct cSPSpaceToolData;
struct cSPPlayerUFO {
    uint32_t pad00[0x34 / 4];
    cSpatialObject mSpatial;                                  // +0x34
    uint32_t pad38[(0x604 - 0x38) / 4];
    float mEdgeSpin;                                          // +0x604
    cSPSpaceToolData* GetActiveTool();                        // 0x00ff3f00
    float GetAltitude();                                      // 0x00c37120
};

struct cSpaceGameFlags {
    uint8_t mBits;
    bool IsSet(uint8_t flag) const { return (mBits & flag) != 0; }
};

struct cSPSimulatorSpaceGame {
    uint32_t pad00[0x14 / 4];
    cSPUISpace* mpUI;                                         // +0x14
    uint32_t pad18[2];
    cCommunityEditor* mpCommunityEditor;                      // +0x20
    uint32_t pad24[(0x50 - 0x24) / 4];
    cSpaceGameFlags mFlags;                                   // +0x50
    cSPPlayerUFO* GetPlayerUFO();                             // 0x00a1ad60
    void UpdateUfoKeys(int deltaMS);                          // 0x00ffe860
    void UpdateSpaceGame(int gameDeltaMS);                    // 0x00ffcab0
    void SetPlanetDestinationFromOffset(float x, float y, bool a, bool b, bool c, bool d, bool e);  // 0x00ffe570
};
cSPSimulatorSpaceGame* SpaceGame();                           // 0x00ffbe50

struct cGameNoun {
    virtual int AddRef();                                     // +0x00
    virtual int Release();                                    // +0x04
    PV8 PV8 PV4 PV2
    virtual void UpdateGameTime(int gameDeltaMS);             // +0x60
    uint8_t pad[0x135 - 4];
    bool mbNeedsUpdate;                                       // +0x135
};
struct cGameNounVector {
    cGameNoun** mpBegin;
    cGameNoun** mpEnd;
    cGameNoun** mpCapacity;
    uint32_t mAllocator;
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    cGameNoun* const& operator[](uint32_t i) const { return mpBegin[i]; }
};
struct cGameDataVector {
    uint32_t pad00;
    cGameNounVector mData;                                    // +0x04
};
typedef void* (*GameDataFn)();
void* GameData_Create();                                      // 0x00cd7d10
void* GameData_Cast();                                        // 0x00d3d420
void* GameData_Write();                                       // 0x00cdb110
void* GameData_Read();                                        // 0x00b1e520
struct cGameNounManager {
    cGameDataVector* GetGameDataVector(GameDataFn a, GameDataFn b, GameDataFn c, GameDataFn d, uint32_t type);  // 0x00b21340
};
cGameNounManager* NounManager();                              // 0x00b3d300

struct cToolStrategy {
    PV8 PV2 PV
    virtual void Update(cSPSpaceToolData* tool, Vector3* pos);  // +0x2c
    PV2 PV
    virtual void GetTargetPosition(Vector3* pos);             // +0x3c
};
struct cSPSpaceToolData {
    cToolStrategy* GetStrategy();                             // 0x0104f930
    bool IsContinuous();                                      // 0x0104bd50
    int GetActiveSlot();                                      // 0x0104be00
};
struct cSPToolManager {
    void UpdateToolEffects();                                 // 0x0104f2a0
    void PlayerUseToolContinuous(cSPSpaceToolData* tool, Vector3* pos, int deltaMS);  // 0x01051090
    void PlayerUseToolStart(cSPSpaceToolData* tool, Vector3* pos, bool b);           // 0x01050bb0
};
cSPToolManager* ToolManager();                                // 0x00b3d390

struct cUpdater470 { void Update470(int deltaMS); };          // 0x010377f0
struct cUpdater490 { void Update490(int deltaMS); };          // 0x00ae8510
cUpdater470* Updater470();                                    // 0x00b3d470
cUpdater490* Updater490();                                    // 0x00b3d490

struct IGameInputManager {
    PV4 PV2
    virtual bool IsTriggered(uint32_t controlID);             // +0x18
};
IGameInputManager* GameInputManager();                        // 0x00b3d250

struct cViewer {
    Rect GetViewport();                                       // 0x007c4010
    void GetCameraTransform(Transform* t);                    // 0x007c40f0
};
struct IWindowLayout {
    PV2 PV
    virtual struct cUIWindow* FindWindowByID(uint32_t id);    // +0x0c
};
struct cUIWindow { float GetMaxZoom(); };                     // 0x01017220
struct IRenderer {
    PV4 PV2 PV
    virtual cViewer* GetViewer();                             // +0x1c
    PV2 PV
    virtual void Update(int deltaMS);                         // +0x2c
    PV2
    virtual IWindowLayout* GetWindowLayout();                 // +0x38
};
struct IApp {
    PV8 PV8 PV4
    virtual IRenderer* GetRenderer();                         // +0x50
};
IApp* App();                                                  // 0x0067dd10

struct MouseState {
    int mWidth;                                               // +0x00
    int mHeight;                                              // +0x04
    int mX;                                                   // +0x08
    int mY;                                                   // +0x0c
    char mbInWindow;                                          // +0x10
};
struct IInputManager {
    PV4 PV2 PV
    virtual MouseState* GetMouseState();                      // +0x1c
};
IInputManager* InputManager();                                // 0x0067dd50

struct IConfigManager {
    PV8 PV4
    virtual int GetBool(uint32_t id);                         // +0x30
};
IConfigManager* ConfigManager();                              // 0x0067dd30

struct cCameraSettings {
    float GetMinZoomX();                                      // 0x00c373b0
    float GetMaxZoomX();                                      // 0x00c373c0
    float GetMinZoomY();                                      // 0x00c373d0
    float GetMaxZoomY();                                      // 0x00c373e0
};
cCameraSettings* CameraSettings();                            // 0x00c37360

struct ICamera {
    PV2 PV
    virtual void Refresh();                                   // +0x0c
    PV8
    virtual void SetTarget(Vector3* pos);                     // +0x30
    PV
    virtual void SetPositionAndDirection(Vector3* pos, Vector3* dir);  // +0x38
    virtual void SetCameraPosition(Vector3* pos);             // +0x3c
    PV2 PV
    virtual uint32_t GetCameraType();                         // +0x4c
};
ICamera* ActiveCamera();                                      // 0x0067ddc0

void Camera_Update(float delta);                              // 0x00b6dbd0
void Cursor_Update(float x, float y);                            // 0x00804f10

struct cLocalInputState {
    void OnMouseWheel(float x, float y, uint32_t button);        // 0x00697b20
};

extern const Vector3 kToolTargetDefault;                      // 0x016d9944

class cAppModeSpace {
public:
    uint32_t pad000[0xc8 / 4];
    cLocalInputState mLocalInputState;                        // +0xc8
    uint8_t pad0c9[0xe8 - 0xc9];
    uint32_t mRotateButton;                                   // +0xe8
    uint8_t pad0ec;
    bool mMMBDown;                                            // +0xed
    bool mRMBDown;                                            // +0xee
    uint8_t pad0ef[0x110 - 0xef];
    EA::Stopwatch mMMBPlanetTimer;                            // +0x110
    Vector2 mMousePosition;                                   // +0x128
    bool mbWheelHandled;                                      // +0x130
    bool mbCheckEmpire;                                       // +0x131
    uint8_t pad132[0x15c - 0x132];
    cSPSimulatorSpaceGame* mpSimulatorSpaceGame;              // +0x15c
    uint32_t pad160;
    uint32_t mElapsedBakeTimeForTransitionMS;                 // +0x164
    uint8_t pad168[2];
    bool mBakingForPlanetEntryEnded;                          // +0x16a
    uint8_t pad16b[0x170 - 0x16b];
    eastl::list<ResourceKey> mNeedsBakingForTransition;       // +0x170
    uint8_t pad17c[0x18d - 0x17c];
    bool mbToolBlocked;                                       // +0x18d
    bool mbTutorial;                                          // +0x18e
    bool mbTutorialIntro;                                     // +0x18f
    bool mbTutorialStep2;                                     // +0x190
    bool mbTutorialStep3;                                     // +0x191
    bool mbTutorialFinish;                                    // +0x192
    uint8_t pad193;
    uint32_t mDelayedMessageCounter;                          // +0x194

    void CompleteTransitionFromSolarToPlanet();               // 0x00fe0c60
    void CompleteTransitionFromEntryToNewGame();              // 0x00fdbc20
    void TransitionFromCivToSpace(bool a, bool b);            // 0x00fdba50
    void HandleSimulationUpdate(float delta1, float delta2);
};

// 0x00fe0f40
void cAppModeSpace::HandleSimulationUpdate(float delta1, float delta2)
{
    if (mDelayedMessageCounter > 0) {
        if (--mDelayedMessageCounter == 0) {
            MessageManager()->PostMSG(0x21851ebe);
        }
        return;
    }

    if (!mNeedsBakingForTransition.empty()) {
        IBakeManager* pBakeManager = BakeManager();
        while (!pBakeManager->IsBaked(mNeedsBakingForTransition.front())) {
            mNeedsBakingForTransition.pop_front();
            if (mNeedsBakingForTransition.empty()) {
                mBakingForPlanetEntryEnded = true;
                break;
            }
        }
    }

    mElapsedBakeTimeForTransitionMS += (uint32_t)FloatToInt64(delta2 * 1000.0f);

    if (mpSimulatorSpaceGame->mFlags.IsSet(2)) {
        if (PlanetModel()->mpTerrain->IsReady() &&
            (mBakingForPlanetEntryEnded || mElapsedBakeTimeForTransitionMS > 15000)) {
            PlanetModel()->FinishPlanetLoad();
            PlanetRenderer()->OnPlanetEntered();
            PlanetModel()->ActivatePlanet();
            CompleteTransitionFromSolarToPlanet();
        }
    }

    int deltaMS = RoundToInt(delta2 * 1000.0f);
    RoundToInt(delta1 * 1000.0f);

    if (mpSimulatorSpaceGame->mFlags.IsSet(0x10)) {
        if (mBakingForPlanetEntryEnded) {
            CompleteTransitionFromEntryToNewGame();
            TransitionFromCivToSpace(true, true);
        } else {
            SimulatorSystem()->UpdateMessages(deltaMS);
            return;
        }
    }

    if (mbTutorial && TutorialManager()->IsActive() &&
        (!sTestSystem || sTestSystem->mTests.mpNext == &sTestSystem->mTests)) {
        if (mbTutorialIntro) {
            TutorialManager()->StartIntro();
            mbTutorialIntro = false;
            mbTutorialStep2 = true;
            return;
        }
        if (mbTutorialStep2 && TutorialManager()->IsIntroDone()) {
            TutorialManager()->StartStep2();
            mbTutorialStep2 = false;
            mbTutorialStep3 = true;
            return;
        }
        if (mbTutorialStep3 && TutorialManager()->IsStep2Done()) {
            mbTutorialStep3 = false;
            mbTutorialFinish = true;
            return;
        }
        if (mbTutorialFinish) {
            mbTutorialFinish = false;
            TutorialManager()->Finish(0, g_tutorialFinishName, 1);
            return;
        }
        SimulatorSystem()->UpdateMessages(deltaMS);
        return;
    }

    if (mbCheckEmpire) {
        int state = GameState()->mState;
        if (state != 1 && state != 2) {
            mbCheckEmpire = false;
            if (*cSPLivingUniverse::GetPlayerEmpire()->GetCities() == 0) {
                OnPlayerEmpireHasNoCities();
            }
        }
    }

    int context = cSPLivingUniverse::GetUniverseContext();
    cSimulatorSystem* pSimulator = SimulatorSystem();
    int gameDeltaMS = GameTimeManager()->UpdateTime(deltaMS);
    UpdateGameTime(gameDeltaMS);
    pSimulator->Update(deltaMS);
    bool paused = (GameTimeManager()->mFlags & 1) != 0;
    SpaceGame()->UpdateUfoKeys(deltaMS);
    if (mpSimulatorSpaceGame->mpCommunityEditor) {
        mpSimulatorSpaceGame->mpCommunityEditor->HandleSimulationUpdate(deltaMS);
    }

    if (!paused) {
        const cGameNounVector& nouns = NounManager()->GetGameDataVector(
            (GameDataFn)GameData_Create, (GameDataFn)GameData_Cast, (GameDataFn)GameData_Write,
            (GameDataFn)GameData_Read, 0xce9f6639)->mData;
        uint32_t count = nouns.size();
        for (uint32_t i = 0; i < count; i++) {
            cGameNoun* pNoun = nouns[i];
            if (pNoun) {
                pNoun->AddRef();
                if (pNoun->mbNeedsUpdate) {
                    pNoun->UpdateGameTime(gameDeltaMS);
                }
                pNoun->Release();
            }
        }
        ToolManager()->UpdateToolEffects();
    }

    Updater470()->Update470(deltaMS);
    Updater490()->Update490(deltaMS);

    if (!paused) {
        cSPSpaceToolData* pTool = mpSimulatorSpaceGame->GetPlayerUFO()->GetActiveTool();
        cToolStrategy* pStrategy;
        if (pTool && (pStrategy = pTool->GetStrategy()) != 0) {
            Vector3 target = kToolTargetDefault;
            pStrategy->GetTargetPosition(&target);
            pStrategy->Update(pTool, &target);
            if (GameInputManager()->IsTriggered(0xdddddddd) &&
                !GameInputManager()->IsTriggered(0xcdcdcdcd)) {
                if (pTool->IsContinuous()) {
                    ToolManager()->PlayerUseToolContinuous(pTool, &target, deltaMS);
                } else if (pTool->GetActiveSlot() != -1 && !mbToolBlocked) {
                    ToolManager()->PlayerUseToolStart(pTool, &target, true);
                }
            }
        }

        if (context == 0) {
            IWindowLayout* pLayout = App()->GetRenderer()->GetWindowLayout();
            cUIWindow* pWindow;
            if (pLayout && (pWindow = pLayout->FindWindowByID(0x303154cd)) != 0) {
                if (GameInputManager()->IsTriggered(0xcccccccc) &&
                    mMMBPlanetTimer.GetElapsedTime() > 250) {
                    MouseState* pMouse = InputManager()->GetMouseState();
                    float mouseX = (float)pMouse->mX;
                    float mouseY = (float)pMouse->mY;
                    Rect viewport = App()->GetRenderer()->GetViewer()->GetViewport();
                    int centerX = (viewport.right + viewport.left) / 2;
                    int centerY = (viewport.bottom + viewport.top) / 2;
                    cSPPlayerUFO* pUFO = SpaceGame()->GetPlayerUFO();
                    float minAltitude = PlanetModel()->GetMinAltitude();
                    float t = (pUFO->GetAltitude() - minAltitude) / (pWindow->GetMaxZoom() - minAltitude);
                    t = Clamp(t, 0.0f, 1.0f);
                    float s = 1.0f - t;
                    float minX = CameraSettings()->GetMinZoomX();
                    float rangeX = (CameraSettings()->GetMaxZoomX() - minX) * s;
                    float minY = CameraSettings()->GetMinZoomY();
                    float rangeY = (CameraSettings()->GetMaxZoomY() - minY) * s;
                    pUFO->mEdgeSpin = 0.0f;
                    float cx = (float)centerX;
                    float cy = (float)centerY;
                    SpaceGame()->SetPlanetDestinationFromOffset(
                        ((mouseX - cx) / cx) * (rangeY + minY),
                        ((mouseY - cy) / cy) * (rangeX + minX),
                        false, true, false, false, false);
                } else {
                    MouseState* pMouse = InputManager()->GetMouseState();
                    bool inWindow = pMouse->mbInWindow != 0;
                    if (ConfigManager()->GetBool(0x636ec26) && inWindow) {
                        float x = (float)pMouse->mX;
                        float width = (float)pMouse->mWidth;
                        if (x >= 0.0f && width > x) {
                            float dist = x;
                            bool right;
                            if (x > width * 0.5f) {
                                dist = width - x;
                                right = true;
                            } else {
                                right = false;
                            }
                            if (fabs(dist * 0.25) <= 1.0) {
                                float spin = right ? -1.0f : 1.0f;
                                SpaceGame()->GetPlayerUFO()->mEdgeSpin = spin;
                            }
                        }
                    }
                }
            }
        }
    }

    if (!mbWheelHandled && mpSimulatorSpaceGame && mpSimulatorSpaceGame->mpCommunityEditor &&
        !mpSimulatorSpaceGame->mpCommunityEditor->IsOpen()) {
        bool doWheel = false;
        switch (context) {
        case 0:
            doWheel = GameInputManager()->IsTriggered(0xcdcdcdcd);
            break;
        case 1:
        case 2:
            doWheel = mMMBDown || mRMBDown;
            break;
        }
        if (doWheel) {
            Cursor_Update(mMousePosition.x, mMousePosition.y);
            mLocalInputState.OnMouseWheel(mMousePosition.x, mMousePosition.y, mRotateButton);
        }
    }
    mbWheelHandled = false;

    App()->GetRenderer()->Update(deltaMS);
    SpaceGame()->UpdateSpaceGame(gameDeltaMS);
    mpSimulatorSpaceGame->mpUI->UpdateUI(deltaMS);
    Camera_Update(delta2);

    if (ActiveCamera() && context == 0) {
        if (ActiveCamera()->GetCameraType() == 0x5e51c01) {
            cSPPlayerUFO* pUFO = SpaceGame()->GetPlayerUFO();
            if (pUFO) {
                Vector3 dir = normalized_safe(pUFO->mSpatial.GetPosition());
                Vector3 pos = dir * 500.0f;
                ActiveCamera()->SetPositionAndDirection(&pos, &dir);
            }
            cViewer* pViewer = App()->GetRenderer()->GetViewer();
            if (pViewer) {
                Transform xf;
                pViewer->GetCameraTransform(&xf);
                ActiveCamera()->SetCameraPosition(&xf.mOffset);
            }
            if (PlanetModel() && PlanetModel()->mpTerrain) {
                Vector3 center = PlanetModel()->mpTerrain->GetCenter()->GetPosition();
                ActiveCamera()->SetTarget(&center);
                ActiveCamera()->Refresh();
            }
        }
    }

    pSimulator->PostUpdate(deltaMS);
    pSimulator->UpdateMessages(deltaMS);
    mbToolBlocked = false;
}

}  // namespace SP
