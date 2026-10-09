// s00cf5540: SP::cCityInputStrategy::HandleMessage (00cf5540, 6266 bytes).
// Civ-stage city input strategy message handler. `this` is the IHandlerRC subobject at +0x3c of
// cCityInputStrategy (member calls go through `lea ecx,[esi-0x3c]`). Retail layout differs from the
// 2008 PDB, so the object fields below are named from use, at retail offsets from the full object.
// Module flags: /O2, /arch:SSE (movss copies), no /EHsc (no EH frame despite string/vector locals).
#include "../../include/types.h"

#define VPAD(n) virtual void vpad##n()

extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    Vector3 operator-(const Vector3& b) const { return Vector3(x - b.x, y - b.y, z - b.z); }
    float Length() const { return (float)sqrt((double)(z * z + y * y + x * x)); }
};
struct Quaternion { float x, y, z, w; };

// ---------------------------------------------------------------------------------------------
// EA::Variant (only what the reply path needs)
struct Variant {
    uint32_t mData[4];
    uint16_t mFlags;    // +0x10
    uint16_t mTypeId;   // +0x12
    Variant(const int& v);                 // 005bf350
    void Destruct(int);                    // 0093db80
    void* GetObject();                     // 00bd6a60
    __forceinline ~Variant() { if (mFlags & 4) Destruct(0); }
};

struct IParameterList {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6);
    virtual Variant* GetParameter(int index);              // +0x1c
    virtual void SetParameter(int index, const Variant& v); // +0x20
};

struct IMessage {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3);
    virtual IParameterList* GetParameters();   // +0x10
    virtual IParameterList* GetResults();      // +0x14
};

// The message object posted with id 0xb2699148 (built below with SlotMessage).
struct SlotMessage {
    virtual void Destroy();
    virtual int AddRef();
    virtual int Release();
    uint32_t pad04;
    int mValue;           // +0x08
    uint32_t pad0c[9];
    uint32_t mMessageId;  // +0x30
    uint32_t pad34[3];
    SlotMessage* Construct(int);   // 00421c80
};

// ---------------------------------------------------------------------------------------------
// Game objects
struct cGameData {
    virtual int AddRef();
    virtual int Release();
    VPAD(2);
    virtual void* Cast(uint32_t iid) const;                  // +0x0c
};

struct cSpatialObject {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8); VPAD(9); VPAD(10);
    virtual const Vector3& GetPosition() const;               // +0x2c
    VPAD(12); VPAD(13); VPAD(14); VPAD(15); VPAD(16); VPAD(17); VPAD(18); VPAD(19); VPAD(20); VPAD(21);
    virtual bool IsPlayerOwned() const;                       // +0x58
};

// cGameData-derived objects with their cSpatialObject interface at +0x34.
struct cSpatialGameData {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8); VPAD(9); VPAD(10); VPAD(11);
    virtual cGameData* GetOwnerObject(int);                   // +0x30
    uint32_t pad04[12];
    cSpatialObject mSpatial;                                  // +0x34
};

struct cBuildingCityHall : cSpatialGameData {
    VPAD(13); VPAD(14); VPAD(15); VPAD(16); VPAD(17); VPAD(18); VPAD(19); VPAD(20); VPAD(21); VPAD(22);
    VPAD(23); VPAD(24); VPAD(25); VPAD(26); VPAD(27); VPAD(28); VPAD(29); VPAD(30); VPAD(31); VPAD(32);
    virtual struct cCityHallUI* GetUI();                      // +0x84
};
struct cCityHallUI { void Refresh(); };                       // 00be32b0

struct cCity : cSpatialGameData {
    int GetPopulation();                                      // 00bd8b80
    float GetHappinessValue();                                // 00bd7d00
    cBuildingCityHall* GetCityHall();                         // 00bd9b40
    void GetBounds(Vector3* pCenter, float* pRadius);         // 00bd7f70
    Vector3 GetCenter();                                      // 00bd9480
};

struct cCityPlaced {          // the city returned by EndObjectPlacement; second interface at +0x120
    uint32_t pad[0x120 / 4];
    cSpatialObject mOwned;    // +0x120
    int GetPopulation();      // 00bd8b80
    float GetHappinessValue();// 00bd7d00
};

struct CityVector { cCity** mpBegin; cCity** mpEnd; cCity** mpCapacity; };

struct cCivilization {
    uint32_t pad[0xb0 / 4];
    CityVector mCities;                                       // +0xb0
    CityVector& GetCities();                                  // 00bef6c0 (+0x9c)
    void SetTradeRoute(int commodityId, const Vector3& pos);  // 00bf8a70
};

struct cVehicle { void DisbandUnit(bool); };                  // 00caa610
struct cCommodityNode { void* GetOwner(); };                  // 00bfdf80

// Element type of the selection vectors: holds a cSpatialObject (an AutoRefCount).
struct SpatialRef { cSpatialObject* mpObject; };
struct cSelectedObject { uint32_t pad[0xb20 / 4]; int mPurpose; int mOwnerKind; };  // +0xb20, +0xb24
cSelectedObject* ToSelectedObject(const SpatialRef& r);       // 00bd8440

struct SpatialVector {
    SpatialRef* mpBegin;
    SpatialRef* mpEnd;
    SpatialRef* mpCapacity;
    SpatialVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~SpatialVector();                                         // 00ad92d0
};

// ---------------------------------------------------------------------------------------------
// Managers / singletons
struct IInputController { virtual void vpad0(); };

struct cGameInputManager {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7);
    virtual void PushController(IInputController* p, int a, int b);     // +0x20
    VPAD(9); VPAD(10); VPAD(11); VPAD(12); VPAD(13); VPAD(14); VPAD(15); VPAD(16); VPAD(17);
    VPAD(18); VPAD(19); VPAD(20); VPAD(21); VPAD(22); VPAD(23); VPAD(24);
    virtual void SetState(uint32_t id, bool b);                         // +0x64
};
cGameInputManager* GameInputManager();                                  // 00b3d250

struct cGameTimeManager {
    uint32_t pad[0x48 / 4];
    uint8_t mPauseFlags;                                                // +0x48
    void DecPauseGate(uint32_t id);                                     // 00b32250
    void IncPauseGate(uint32_t id);                                     // 00b32220
};
cGameTimeManager* GameTimeManager();                                    // 00b3d380

struct cGameTerrainCursor {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8); VPAD(9);
    VPAD(10); VPAD(11); VPAD(12); VPAD(13); VPAD(14); VPAD(15); VPAD(16); VPAD(17); VPAD(18); VPAD(19);
    VPAD(20); VPAD(21); VPAD(22);
    virtual void GetSelection(SpatialVector& out);                      // +0x5c
    virtual void GetSelectionFiltered(SpatialVector& out, const void* filter);  // +0x60
    virtual void ClearSelection();                                      // +0x64
    VPAD(26); VPAD(27);
    virtual int GetSelectionCount();                                    // +0x70
    VPAD(29); VPAD(30); VPAD(31);
    virtual void SetSelection(SpatialVector& v, int);                   // +0x80
    VPAD(33); VPAD(34); VPAD(35); VPAD(36); VPAD(37); VPAD(38); VPAD(39); VPAD(40); VPAD(41); VPAD(42);
    VPAD(43); VPAD(44); VPAD(45); VPAD(46); VPAD(47); VPAD(48); VPAD(49); VPAD(50); VPAD(51); VPAD(52);
    VPAD(53);
    virtual void SetRectangleSelect(bool b);                            // +0xd8
    virtual bool IsRectangleSelect();                                   // +0xdc
};
cGameTerrainCursor* GetGameTerrainCursor();                             // 00b30d70
extern const char g_SelectableCityFilter[];                             // 0137e8e0

struct cTerrainSphere {
    void SetPickPriorities(int mode, SpatialVector* pSel);              // 00c7ad00
    void SetBanModePickPriorities(int mode, SpatialVector* pSel);       // 00c79e20
    void SetPickMode(uint32_t id);                                      // 00c77bf0
};
struct cGameNounManager {
    cTerrainSphere* GetTerrainSphere();                                 // 00f67d90
    cCivilization* GetPlayerCivilization();                             // 00b25fb0
    void* GetPlanetRoot();                                              // 00ace2c0
};
cGameNounManager* NounManager();                                        // 00b3d300

struct cTerrainCameraController {
    uint32_t pad[4];
    bool mbEdgeScroll;                                                  // +0x10
    const Vector3* GetAnchorDirection1();                               // 00b10260
    void MoveTo(const Vector3& pos, bool a, bool b);                    // 00b146a0
    Vector3 GetTarget();                                                // 00b137d0
    void SetOrientation(const Vector3& pos, const Quaternion& q, int);  // 00b12dd0
    void SetZoom(float a, float b, float c);                            // 00b10340
};
cTerrainCameraController* TerrainCameraController();                    // 00b3d280

struct cCameraManager {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8); VPAD(9);
    VPAD(10); VPAD(11); VPAD(12);
    virtual cGameData* GetHoveredObject();                              // +0x34
    virtual Vector3 PickTerrain(int mode, Vector3 v);                   // +0x38
};
cCameraManager* CameraManager();                                        // 00b3d240

struct cBehaviorManager {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4);
    virtual int ToggleDebug(int v);                                     // +0x14
};
cBehaviorManager* BehaviorManager();                                    // 00b3d260

struct IVisualEffect {
    virtual int AddRef();
    virtual int Release();
    virtual void Start(int);                                            // +0x08
};
struct VisualEffectRef {
    IVisualEffect* mpObject;
    VisualEffectRef() : mpObject(0) {}
    __forceinline ~VisualEffectRef() { if (mpObject) mpObject->Release(); }
    IVisualEffect** AsPPTypeParam();                                    // 00a16f40
};
struct cEffectsManager {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8); VPAD(9); VPAD(10);
    virtual bool CreateVisualEffect(uint32_t id, int, IVisualEffect** pp); // +0x2c
};
cEffectsManager* EffectsManager();                                      // 0067ddd0

struct IMessageServer {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5);
    virtual void PostMessage(uint32_t id, void* pMsg, int, int);        // +0x18
};
IMessageServer* MessageServer();                                        // 0067dcc0

struct cWindowManagerObj { VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7);
    VPAD(8); VPAD(9); VPAD(10); VPAD(11); VPAD(12); VPAD(13); VPAD(14); VPAD(15);
    virtual void* FindWindowByID(uint32_t id); };                       // +0x40
struct cApp { VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8); VPAD(9);
    VPAD(10); VPAD(11); VPAD(12); VPAD(13); VPAD(14); VPAD(15); VPAD(16); VPAD(17); VPAD(18); VPAD(19);
    virtual cWindowManagerObj* GetWindowManager(); };                   // +0x50
cApp* App();                                                            // 0067dd10
struct cTimeControlWindow { void SetPaused(bool b); };                  // 00b10c40
cTimeControlWindow* ToTimeControlWindow(void* w);                       // 00b5cc20

struct cSPUIEventLog {
    bool GetPositionOfLastEvent(Vector3* pPos);                         // 00dd6810
    void PostFeedbackEvent(uint32_t a, uint32_t b, int, int, int, int); // 00dd8640
};
cSPUIEventLog* EventLog();                                              // 00b3d3e0

struct cSPUICursorManager { void SetLocalCursor(uint32_t id); };        // 00801bb0
cSPUICursorManager* CursorManager();                                    // 0067cab0

struct cPlanetModel {
    Quaternion BuildSurfaceOrientation(const Vector3& pos, const Vector3& dir);  // 00b7f250
};
cPlanetModel* PlanetModel();                                            // 00b3d350

struct cCheatManager { bool IsActive(); };                              // 00ae9390
cCheatManager* CheatManager();                                          // 00b3d4a0
struct cConsole { void Open(int); };                                    // 00e190c0
cConsole* Console();                                                    // 00b3d3f0

struct cSaveManager { bool IsSaving(); };                               // 00ac80f0
cSaveManager* SaveManager();                                            // 00b3d4d0

struct cCommunityEditor {
    uint32_t pad[0x40 / 4];
    int mObjectID;                                                      // +0x40
    uint32_t pad44[(0x2f4 - 0x44) / 4];
    int mDefaultIndex;                                                  // +0x2f4
    void Activate(cGameData* p);                                        // 00d0e170
    void Deactivate(int, int);                                          // 00d100b0
    void SelectIndex(int idx);                                          // 00d09690
    bool IsBusy();                                                      // 00d09660
    bool CanClose();                                                    // 00d0a160
};

struct cBanner { void Update(); };                                      // 00e35350
struct cScoreTarget { void Show(int kind, Vector3 pos); };              // 00ae37c0
cScoreTarget* ScoreTarget();                                            // 00b26930

struct string16 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAllocator;
    __forceinline string16(const wchar_t* p) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(p); }
    __forceinline ~string16() { DeallocateSelf(); }
    void RangeInitialize(const wchar_t* p);                             // 00579a90
    void DeallocateSelf();                                              // 00933960
};

struct cCivUI {
    void ShowMessage(const string16& s);                                // 00af1450
    void ShowCityInfo(void* p);                                         // 00ce9c30
    void SetMixedSelection(bool b);                                     // 00ce9550
    void HideTooltip();                                                 // 00ce9560
    void PointCompass(const Vector3* dir);                              // 00ce9d30
    void PlaceTradeMarker(const Vector3& pos);                          // 00cea6f0
};
struct cSpecialPowersPanel { uint32_t pad[0x140 / 4]; int mActivePower; void SelectPower(int id); };  // +0x140, 00cf1be0

struct cCivModeStrategy {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8);
    virtual void SetUIState(int state, int);                            // +0x24
    uint32_t pad04[9];
    bool mbEditorLaunched;                                              // +0x28
    static cCivModeStrategy* Get();                                     // 00cf74c0
    void SetCameraTrackObject(cSpatialObject* p);                       // 00cf8d70
    void DoNextCivTutorial(uint32_t id, bool b);                        // 00cfa990
    bool HasCivTutorialOccurred(uint32_t id);                           // 00cf7830
    cCivUI* GetUI();                                                    // 00cf7500
    cSpecialPowersPanel* GetPowersPanel();                              // 00cf74f0
    cSpatialGameData* GetTrackedObject();                               // 00c44f10
    void OnEditorExit();                                                // 00cf9ba0
    void HandleCheat(IMessage* pMsg);                                   // 00cf7a10
};

// Editor launch data (0x9c bytes)
struct cEditorLaunchData {
    virtual void Destroy();
    virtual int AddRef();
    virtual int Release();
    uint32_t pad04[2];
    uint32_t mEditorID;        // +0x0c
    uint32_t pad10[9];
    bool mb34, mb35, mb36, mb37, mb38, mb39, mb3a, mb3b, mb3c, mb3d;  // +0x34..+0x3d
    uint8_t pad3e[0x64 - 0x3e];
    bool mb64;                 // +0x64
    uint8_t pad65[0x90 - 0x65];
    uint32_t mModelType;       // +0x90
    uint32_t pad94[2];
    cEditorLaunchData();       // 005a9080
};
void EditorLaunch(cEditorLaunchData* p);                                // 005a9200
extern bool g_bEditorLaunchedFromCiv;                                   // 01686af0

// Smart pointer whose (inlined) destructor releases unconditionally, as in the binary.
template <class T> struct RefHolder {
    T* mpObject;
    RefHolder(T* p);           // 0061df40 (AddRef if non-null)
    __forceinline ~RefHolder() { mpObject->Release(); }
};

void* operator new(unsigned int size, const char* name, int, int, const char*, int);
extern const char kAppName[];                                           // "App"

// Free functions / casts
void* GetObjectFromVariant(Variant* v);
cGameData* ToGameData(void* p);                                         // 00c9f060
void* ToIUnknown(void* p);                                              // 00b18e00
cVehicle* ToVehicle(cSpatialObject* p);                                 // 00b33e60
cCity* ToCity(cSpatialGameData* p);                                     // 00b33e60 (same function)
cSpatialGameData* ToSpatialGameData(cGameData* p);                      // 00ae6760
cBuildingCityHall* ToCityHall(cGameData* p);                            // 00cf7d20
cCommodityNode* ToCommodityNode(cGameData* p);                          // 00e34f10
cCity* FindCityAt(void* root, const Vector3& pos);                      // 00ac9dd0
cCityPlaced* EndObjectPlacement(int objectId);                          // 00ac86d0
void* GetCurrentGameMode();                                             // 00b5b800
extern char g_CivGameMode;                                              // 01654c04
bool CalloutMessageBox(void* a, void* b);                               // 00809db0
extern bool g_bQuitCalloutShown;                                        // 0158198c
extern char g_QuitCallout[], g_QuitCalloutText[];                       // 01581988, 01581970
extern char g_SaveCallout[], g_SaveCalloutText[];                       // 01581990, 0158197c
extern int g_CivDebugCounter;                                           // 0169cc88
extern Vector3 g_CursorPos;                                             // 0169cc8c
extern Vector3 g_CheatPlopPos;                                          // 0167ae14
extern Vector3 g_CheatPlopStart;                                        // 0167ae08
extern bool g_bCheatPlopStarted;                                        // 0167ade8
extern int g_BehaviorDebugState;                                        // 01581810
extern float g_CityCameraPitch;                                         // 01581814
bool Vector3Equal(const Vector3* a, const Vector3* b);                  // 004232c0
bool Vector3NotEqual(const Vector3* a, const Vector3* b);               // 0041dd30
Vector3 normalized_safe(const Vector3& v);                              // 00449c20
bool IsValidTradeRoute(int commodityId, const Vector3* pos);            // 00bda2f0
int GetSpecialPowerId(uint32_t key);                                    // 00e053c0

struct cUIBanningContent {
    static void EndBanMode(int);                                        // 00dd1840
    static bool IsDialogShown();                                        // 00dd1220
    static void ShowConfirmationDialog(cGameData* p);                   // 00dd1aa0
    static bool CanBan(cGameData* p);                                   // 00dd18b0
};
void EndCommodityMode(int);                                             // 00e09a50
void ShowCommodityInfo(cGameData* p);                                   // 00e09bf0

// ---------------------------------------------------------------------------------------------
struct cInputStrategyBase { virtual void vpad0(); };
struct cInputControllerBase : IInputController { uint32_t pad[(0x3c - 0x8) / 4]; };   // at +4

struct tGonzagoInputControllerStateMachine : IInputController { uint32_t pad[(0x3c - 4) / 4]; };

struct Stopwatch {
    uint64_t mnStartTime;
    uint64_t mnTotalElapsedTime;
    uint32_t mnUnits;
    float mfCoefficient;
    void Reset() { mnStartTime = 0; mnTotalElapsedTime = 0; }
    void Restart();                                                     // 00571e80
};

struct GameDataRef {
    cGameData* mpObject;
    GameDataRef& operator=(cGameData* p);                               // 00b5f950
    __forceinline void Clear() {
        if (mpObject) {
            cGameData* p = mpObject;
            mpObject = 0;
            p->Release();
        }
    }
};

struct IHandlerRC {
    virtual bool HandleMessage(uint32_t messageID, IMessage* pMessage) = 0;
};

class cCityInputStrategy : public cInputStrategyBase, public cInputControllerBase, public IHandlerRC {
public:
    virtual bool HandleMessage(uint32_t messageID, IMessage* pMessage);

    void OnCommunityEditorLaunched();                                       // 00cf2fd0
    void OnCommodityEditorLaunched();                                       // 00cf3040
    void SetDefaultPickPriorities();                                        // 00cf28f0
    void SetInputEnabled(bool b);                                           // 00cf1500
    int OnMouseMove(cGameData* p, int n);                                   // 00cf1630
    int UpdateMovingObject(cGameData* p, int n);                            // 00cf16f0
    int OnMouseWheel(cGameData* p, int n);                                  // 00cf15e0
    int OnTradeRouteClick(cGameData* p, int n);                             // 00ce8ab0
    int DoObjectInteraction(cGameData* p, int n);                           // 00cf3bf0
    void OnHover(cGameData* p, bool b);                                     // 00cf1810
    int UpdateObjectPlacement(cGameData* p, int n);                         // 00cf18b0
    int OnRightClick(cGameData* p, int n);                                  // 00cf4440
    int AddTribeMember(cGameData* p, int n);                                // 00cf1aa0
    int RemoveTribeMember(cGameData* p, int n);                             // 00cf1ad0
    void BeginSelection(cGameData* p, int n);                               // 00cf50e0
    int MenuOff(cGameData* p, int n);                                       // 00cf1060
    int EndSelection(cGameData* p, int n, const Vector3& pos);              // 00cf2520
    int OnKeyUp(cGameData* p, int n);                                       // 00cf1560
    int OnKeyDown(cGameData* p, int n);                                     // 00cf1000

    uint32_t pad40[3];                                  // +0x40
    cCivModeStrategy* mpModeStrategy;                   // +0x4c
    uint32_t pad50[(0x80 - 0x50) / 4];
    cCommunityEditor* mpCommunityEditor;                // +0x80
    tGonzagoInputControllerStateMachine mEditorMachine; // +0x84
    Stopwatch mTrackingTimer;                           // +0xc0
    GameDataRef mObjectToCenterCameraOn;                // +0xd8
    bool mbTimeControlPaused;                           // +0xdc
    uint32_t pade0;
    cBanner* mpBanner;                                  // +0xe4
    uint32_t pade8[(0x110 - 0xe8) / 4];
    cBuildingCityHall* mpCityHallSelected;              // +0x110
    uint32_t pad114[(0x130 - 0x114) / 4];
    cCity* mpCitySelected;                              // +0x130
    bool mbLaunchEditorPending;                         // +0x134
    bool mbQuitRequested;                               // +0x135
    uint8_t pad136[2];
    uint32_t mPendingCallout;                           // +0x138
    void* mpTurretSelected;                             // +0x13c
    int mCommodityNodeSelected;                         // +0x140
};

bool cCityInputStrategy::HandleMessage(uint32_t messageID, IMessage* pMessage)
{
    if (messageID == 0x238de9c) {
        mbQuitRequested = true;
        return true;
    }
    if (messageID == 0x44eaa93) {
        OnCommunityEditorLaunched();
        GameInputManager()->SetState(0x49363f1, true);
        return true;
    }
    if (messageID == 0x452e0ca) {
        GameInputManager()->SetState(0x49363f1, true);
        mpTurretSelected = 0;
        SetDefaultPickPriorities();
        cUIBanningContent::EndBanMode(1);
        return true;
    }
    if (messageID == 0x620222b) {
        OnCommodityEditorLaunched();
        GameInputManager()->SetState(0x6264b4d, true);
        return true;
    }
    if (messageID == 0x620271c) {
        GameInputManager()->SetState(0x6264b4d, true);
        mpTurretSelected = 0;
        SetDefaultPickPriorities();
        EndCommodityMode(1);
        return true;
    }
    if (messageID == 0x158cd75) {
        g_CivDebugCounter++;
        return true;
    }
    if (messageID == 0x2cb6a8f) {
        if (!g_bQuitCalloutShown)
            CalloutMessageBox(g_QuitCallout, g_QuitCalloutText);
        return true;
    }
    if (messageID == 0xb2699148) {
        if (mpCommunityEditor && mpCityHallSelected) {
            if (!mpCityHallSelected->mSpatial.IsPlayerOwned())
                return true;
            mCommodityNodeSelected = -1;
            cCivModeStrategy::Get()->SetCameraTrackObject(0);
            SetInputEnabled(false);
            mpBanner->Update();
            ScoreTarget()->Show(6, mpCityHallSelected->mSpatial.GetPosition());
            mpCommunityEditor->Activate(ToGameData(mpCityHallSelected->GetOwnerObject(0)));
            if (pMessage) {
                int index = ((SlotMessage*)pMessage)->mValue;
                if (index == -1) {
                    index = mpCommunityEditor->mDefaultIndex;
                    if (index == -1)
                        index = 0;
                }
                mpCommunityEditor->SelectIndex(index);
            }
            GameInputManager()->PushController(&mEditorMachine, 0, 0);
        }
        return true;
    }
    if (messageID == 0xb2699149) {
        if (mpCommunityEditor) {
            cCityPlaced* pCity = EndObjectPlacement(mpCommunityEditor->mObjectID);
            if (pCity && GetCurrentGameMode() == &g_CivGameMode && pCity->mOwned.IsPlayerOwned()) {
                if (pCity->GetPopulation() >= 400)
                    cCivModeStrategy::Get()->DoNextCivTutorial(0x34646619, true);
                if (pCity->GetHappinessValue() >= 60.0f)
                    cCivModeStrategy::Get()->DoNextCivTutorial(0xbb7368ed, true);
            }
            SetInputEnabled(true);
            mpCommunityEditor->Deactivate(0, 1);
            GameInputManager()->PushController(static_cast<cInputControllerBase*>(this), 0, 0);
            cCivModeStrategy::Get()->OnEditorExit();
        }
        return true;
    }
    if (messageID == 0x445f729) {
        if (mbLaunchEditorPending) {
            mbLaunchEditorPending = false;
            GameTimeManager()->DecPauseGate(0x4bf38a7);
            GameTimeManager()->IncPauseGate(0x4bf38a6);
            cCivModeStrategy::Get()->mbEditorLaunched = true;
            RefHolder<cEditorLaunchData> data(new ("App", 0, 0, 0, 0) cEditorLaunchData());
            cEditorLaunchData* p = data.mpObject;
            p->mEditorID = 0x96b24187;
            p->mModelType = 0x116d51d;
            p->mb34 = false;
            p->mb36 = true;
            p->mb38 = true;
            p->mb37 = true;
            p->mb39 = false;
            p->mb3b = false;
            p->mb3c = true;
            p->mb3d = true;
            p->mb64 = true;
            EditorLaunch(p);
            g_bEditorLaunchedFromCiv = true;
        }
        return true;
    }
    if (messageID == 0x4e54d0c) {
        GameInputManager()->SetState(0x4e54bb3, true);
        return true;
    }
    if (messageID == 0x4e52fda) {
        if (!SaveManager()->IsSaving()) {
            if (CalloutMessageBox(g_SaveCallout, g_SaveCalloutText)) {
                GameTimeManager()->IncPauseGate(0x4bf38a7);
                return true;
            }
            mPendingCallout = 0x5107b19;
        }
        return true;
    }
    if (messageID == 0x37033e2) {
        SpatialVector selection;
        GetGameTerrainCursor()->GetSelection(selection);
        for (SpatialRef* it = selection.mpBegin; it != selection.mpEnd; ++it) {
            cVehicle* pVehicle = ToVehicle(it->mpObject);
            if (pVehicle)
                pVehicle->DisbandUnit(true);
        }
        GetGameTerrainCursor()->ClearSelection();
        return true;
    }

    // Messages carrying (object, int) parameters; the int result is written back to the message.
    IParameterList* pParams = pMessage->GetParameters();
    void* pObject = pParams->GetParameter(0)->GetObject();
    cGameData* pGameData = ToGameData(pObject);
    ToIUnknown(pObject);
    int nParam = *(int*)pParams->GetParameter(1);
    int result = 0;
    bool bFromCityHall = false;

    switch (messageID) {
    case 0x10f366c:
    case 0x129736e:
        break;
    case 0x1284eb7:
        result = OnMouseMove(pGameData, nParam);
        break;
    case 0x14bd14d:
        result = UpdateMovingObject(pGameData, nParam);
        break;
    case 0x154b4ee: {
        VisualEffectRef effect;
        cEffectsManager* pEffects = EffectsManager();
        if (pEffects->CreateVisualEffect(0x4cab5702, 0, effect.AsPPTypeParam()) && effect.mpObject)
            effect.mpObject->Start(0);
        if (GameTimeManager()->mPauseFlags & 1)
            GameTimeManager()->DecPauseGate(0x4bf38a7);
        SetInputEnabled(true);
        break;
    }
    case 0x15268fc:
        if (nParam == 0) {
            mTrackingTimer.Reset();
            mObjectToCenterCameraOn.Clear();
        } else if (nParam == 1) {
            mTrackingTimer.Restart();
            if (pGameData && !pGameData->Cast(0xed7fc07)) {
                mObjectToCenterCameraOn = pGameData;
                cCivModeStrategy::Get()->SetCameraTrackObject(0);
                break;
            }
        }
        cCivModeStrategy::Get()->SetCameraTrackObject(0);
        break;
    case 0x1590e88:
        result = OnMouseWheel(pGameData, nParam);
        break;
    case 0x1aeb328:
        g_BehaviorDebugState = BehaviorManager()->ToggleDebug(g_BehaviorDebugState);
        if (!GetGameTerrainCursor()->GetSelectionCount())
            result = 1;
        break;
    case 0x1cbf999: {
        g_bCheatPlopStarted = true;
        Vector3 pos = CameraManager()->PickTerrain(0, g_CursorPos);
        g_CheatPlopPos = pos;
        g_CheatPlopStart = pos;
        break;
    }
    case 0x1cbf99a:
        g_CheatPlopPos = CameraManager()->PickTerrain(0, g_CursorPos);
        break;
    case 0x2c35d56: {
        cBuildingCityHall* pHall = ToCityHall(pGameData);
        if (pHall)
            pHall->GetUI()->Refresh();
        break;
    }
    case 0x345b779: {
        SpatialVector selection;
        GetGameTerrainCursor()->GetSelection(selection);
        NounManager()->GetTerrainSphere()->SetBanModePickPriorities(nParam, &selection);
        break;
    }
    case 0x345b784: {
        SpatialVector selection;
        GetGameTerrainCursor()->GetSelectionCount();
        NounManager()->GetTerrainSphere()->SetPickPriorities(nParam, &selection);
        GetGameTerrainCursor()->ClearSelection();
        GetGameTerrainCursor()->SetSelection(selection, 0);
        if (!GetGameTerrainCursor()->GetSelectionCount())
            result = 1;
        break;
    }
    case 0x346048a: {
        cSpatialGameData* p = ToSpatialGameData(pGameData);
        if (p)
            cCivModeStrategy::Get()->GetUI()->ShowCityInfo(p);
        if (!GetGameTerrainCursor()->GetSelectionCount())
            result = 1;
        break;
    }
    case 0x34b0d5e: {
        // Cycle the camera through the player's cities.
        cCivilization* pCiv = NounManager()->GetPlayerCivilization();
        if (!pCiv || pCiv->mCities.mpBegin == pCiv->mCities.mpEnd)
            break;
        bool bTrack = false;
        cCity* pNext;
        cCity* pCurrent = ToCity(cCivModeStrategy::Get()->GetTrackedObject());
        if (!pCurrent) {
            SpatialVector selection;
            GetGameTerrainCursor()->GetSelectionFiltered(selection, g_SelectableCityFilter);
            if (selection.mpBegin != selection.mpEnd) {
                Vector3 anchor = *TerrainCameraController()->GetAnchorDirection1();
                cSpatialGameData* pSel = (cSpatialGameData*)ToSelectedObject(*selection.mpBegin);
                const Vector3& pos = pSel->mSpatial.GetPosition();
                if ((pos - anchor).Length() > 100.0f) {
                    TerrainCameraController()->MoveTo(pSel->mSpatial.GetPosition(), true, true);
                    pNext = (cCity*)pSel;
                } else if (!cCivModeStrategy::Get()->GetTrackedObject()) {
                    pNext = (cCity*)pSel;
                    bTrack = true;
                } else {
                    pNext = *pCiv->mCities.mpBegin;
                    bTrack = true;
                }
            } else {
                pNext = *pCiv->mCities.mpBegin;
                bTrack = true;
            }
        } else {
            cCity** it = pCiv->mCities.mpBegin;
            cCity** end = pCiv->mCities.mpEnd;
            while (it != end && *it != pCurrent)
                ++it;
            if (it == end) {
                pNext = *pCiv->mCities.mpBegin;
            } else {
                ++it;
                if (it == end)
                    it = pCiv->mCities.mpBegin;
                pNext = *it;
            }
            bTrack = true;
        }
        if (bTrack)
            cCivModeStrategy::Get()->SetCameraTrackObject(pNext ? &pNext->mSpatial : 0);
        else
            cCivModeStrategy::Get()->SetCameraTrackObject(0);
        break;
    }
    case 0x34c6e46: {
        Vector3 pos;
        if (EventLog()->GetPositionOfLastEvent(&pos) && TerrainCameraController())
            TerrainCameraController()->MoveTo(pos, true, false);
        break;
    }
    case 0x3702b31: {
        cTerrainCameraController* pCamera = TerrainCameraController();
        if (pCamera) {
            pCamera->mbEdgeScroll = !pCamera->mbEdgeScroll;
            if (pCamera->mbEdgeScroll) {
                string16 s(L"Edge Scroll ON");
                cCivModeStrategy::Get()->GetUI()->ShowMessage(s);
            } else {
                string16 s(L"Edge Scroll OFF");
                cCivModeStrategy::Get()->GetUI()->ShowMessage(s);
            }
        }
        break;
    }
    case 0x3702b35: {
        cGameTerrainCursor* pCursor = GetGameTerrainCursor();
        GetGameTerrainCursor()->SetRectangleSelect(!pCursor->IsRectangleSelect());
        if (GetGameTerrainCursor()->IsRectangleSelect()) {
            string16 s(L"Rectangle Select ON");
            cCivModeStrategy::Get()->GetUI()->ShowMessage(s);
        } else {
            string16 s(L"Rectangle Select OFF");
            cCivModeStrategy::Get()->GetUI()->ShowMessage(s);
        }
        break;
    }
    case 0x3702d53: {
        // Cycle the selected city and move the camera to it.
        cCivilization* pCiv = NounManager()->GetPlayerCivilization();
        if (!pCiv)
            break;
        bool bAdvanced = false;
        if (mpCitySelected) {
            CityVector& cities = pCiv->GetCities();
            cCity** it = cities.mpBegin;
            cCity** end = cities.mpEnd;
            if (it == end)
                break;
            while (*it != mpCitySelected) {
                if (++it == end)
                    break;
            }
            if (it != end && ++it != end) {
                mpCitySelected = *it;
                bAdvanced = true;
            }
        }
        if (!bAdvanced)
            mpCitySelected = *pCiv->GetCities().mpBegin;
        if (mpCitySelected && TerrainCameraController()) {
            TerrainCameraController()->MoveTo(mpCitySelected->GetCenter(), true, true);
            cCivModeStrategy::Get()->SetCameraTrackObject(0);
        }
        break;
    }
    case 0x432408c:
        cCivModeStrategy::Get()->SetCameraTrackObject(0);
        break;
    case 0x4910afb:
        // Frame the city under the camera target.
        if (TerrainCameraController()) {
            cCity* pCity = FindCityAt(NounManager()->GetPlanetRoot(), TerrainCameraController()->GetTarget());
            if (pCity) {
                Vector3 center;
                float radius;
                pCity->GetBounds(&center, &radius);
                const Vector3& hallPos = pCity->GetCityHall()->mSpatial.GetPosition();
                Vector3 dir = normalized_safe(hallPos - center);
                Quaternion q = PlanetModel()->BuildSurfaceOrientation(center, dir);
                TerrainCameraController()->SetOrientation(center, q, 0);
                TerrainCameraController()->SetZoom(0.0f, g_CityCameraPitch * 0.5f, radius);
            }
        }
        break;
    case 0x49363f2:
        if (!cUIBanningContent::IsDialogShown() && pGameData)
            cUIBanningContent::ShowConfirmationDialog(pGameData);
        break;
    case 0x49363f3:
        OnCommunityEditorLaunched();
        GameInputManager()->SetState(0x49363f1, true);
        break;
    case 0x51dab6f: {
        bFromCityHall = false;
        cCommodityNode* pNode = ToCommodityNode(pGameData);
        if (pNode && pNode->GetOwner()) {
            SpatialVector selection;
            GetGameTerrainCursor()->GetSelectionFiltered(selection, g_SelectableCityFilter);
            for (SpatialRef* it = selection.mpBegin; it != selection.mpEnd; ++it) {
                if (ToSelectedObject(*it)->mPurpose == 2) {
                    bFromCityHall = true;
                    break;
                }
            }
        }
        if (bFromCityHall) {
            result = OnTradeRouteClick(pGameData, nParam);
            break;
        }
        DoObjectInteraction(pGameData, nParam);
        result = 2;
        break;
    }
    case 0x567fefd: {
        SpatialVector selection;
        GetGameTerrainCursor()->GetSelection(selection);
        if (selection.mpBegin != selection.mpEnd) {
            bool bHasNeutral = false;
            bool bHasOwned = false;
            for (SpatialRef* it = selection.mpBegin; it != selection.mpEnd; ++it) {
                if (bHasNeutral && bHasOwned)
                    break;
                int kind = ToSelectedObject(*it)->mOwnerKind;
                bHasNeutral = bHasNeutral || kind == 0;
                bHasOwned = bHasOwned || kind == 1;
            }
            cCivModeStrategy::Get()->GetUI()->SetMixedSelection(!bHasOwned);
        }
        break;
    }
    case 0x576439b: {
        Vector3 pos = CameraManager()->PickTerrain(0, g_CursorPos);
        if (!Vector3Equal(&pos, &g_CursorPos) && IsValidTradeRoute(mCommodityNodeSelected, &pos)) {
            cCivModeStrategy::Get()->GetUI()->PlaceTradeMarker(pos);
            cCivilization* pCiv = NounManager()->GetPlayerCivilization();
            if (pCiv)
                pCiv->SetTradeRoute(mCommodityNodeSelected, pos);
            mCommodityNodeSelected = -1;
        } else {
            result = 2;
            if (Vector3NotEqual(&pos, &g_CursorPos))
                EventLog()->PostFeedbackEvent(0x1ac1d4a1, 0xaa9a8ed7, 0, 0, 1, 0);
        }
        break;
    }
    case 0x5949f1d:
        if (!CheatManager()->IsActive())
            Console()->Open(0);
        break;
    case 0x5baaaff:
        mpCityHallSelected = ToCityHall(pGameData);
        bFromCityHall = true;
        // fall through
    case 0x71d4dfc9: {
        NounManager()->GetTerrainSphere()->SetPickMode(0x52da1f5);
        SlotMessage* pNew = (SlotMessage*)operator new(0x40, "App", 0, 0, 0, 0);
        RefHolder<SlotMessage> msg(pNew ? pNew->Construct(0) : 0);
        SlotMessage* p = msg.mpObject;
        p->mMessageId = 0xb2699148;
        int index;
        if (bFromCityHall)
            index = -1;
        else if (nParam == 0x37e8514)
            index = 1;
        else if (nParam == 0x4d2b5fd)
            index = 4;
        else
            index = 0;
        p->mValue = index;
        MessageServer()->PostMessage(p->mMessageId, p, 0, 0);
        GetGameTerrainCursor()->ClearSelection();
        break;
    }
    case 0x5bac952:
        result = OnTradeRouteClick(pGameData, nParam);
        break;
    case 0x5fa3b4d:
        cCivModeStrategy::Get()->GetUI()->HideTooltip();
        break;
    case 0x5fb4a1e:
        if (TerrainCameraController()) {
            cCivModeStrategy::Get()->GetUI()->HideTooltip();
            cCivModeStrategy::Get()->GetUI()->PointCompass(TerrainCameraController()->GetAnchorDirection1());
        }
        break;
    case 0x6264b4e:
        if (pGameData)
            ShowCommodityInfo(pGameData);
        break;
    case 0x6264b4f:
        OnCommodityEditorLaunched();
        GameInputManager()->SetState(0x6264b4d, true);
        break;
    case 0x6396006:
        if (pGameData && cUIBanningContent::CanBan(pGameData))
            CursorManager()->SetLocalCursor(0xf212a38b);
        else
            CursorManager()->SetLocalCursor(0x5ecbdffd);
        break;
    case 0x6417055: {
        bool bReleased = (unsigned)nParam < 1;
        OnHover(ToGameData(CameraManager()->GetHoveredObject()), bReleased);
        if (!bReleased) {
            if (mpModeStrategy->HasCivTutorialOccurred(0x64e6671))
                mpModeStrategy->DoNextCivTutorial(0x64e6673, true);
            mpModeStrategy->SetCameraTrackObject(0);
        }
        break;
    }
    case 0x6417056: {
        bool bPaused = (unsigned)nParam > 0;
        cTimeControlWindow* pWindow = ToTimeControlWindow(App()->GetWindowManager()->FindWindowByID(0xe3057616));
        if (pWindow)
            pWindow->SetPaused(bPaused);
        if (mbTimeControlPaused && !bPaused && mpCommunityEditor && !mpCommunityEditor->IsBusy() &&
            mpModeStrategy && mpModeStrategy->HasCivTutorialOccurred(0x64e6666) &&
            !mpModeStrategy->HasCivTutorialOccurred(0x64e666f))
            mpModeStrategy->DoNextCivTutorial(0x64e666f, true);
        mbTimeControlPaused = bPaused;
        break;
    }
    case 0x68f1a98:
    case 0x68f1a9b:
    case 0x68f1a9e:
    case 0x68f1aa1: {
        uint32_t key;
        if (messageID == 0x68f1a98)
            key = 0x5a55b10;
        else if (messageID == 0x68f1a9b)
            key = 0x5a55b20;
        else if (messageID == 0x68f1a9e)
            key = 0x5a55b30;
        else
            key = 0x5a55b40;
        int powerId = GetSpecialPowerId(key);
        if (powerId != -1) {
            if (cCivModeStrategy::Get()->GetPowersPanel()->mActivePower != powerId)
                cCivModeStrategy::Get()->GetPowersPanel()->SelectPower(powerId);
            else
                cCivModeStrategy::Get()->SetUIState(0x1b, 0);
        }
        break;
    }
    case 0x2ff25b8e:
        result = UpdateObjectPlacement(pGameData, nParam);
        break;
    case 0x2ff284ac:
        result = OnRightClick(pGameData, nParam);
        break;
    case 0x4ff25ba4:
        result = RemoveTribeMember(pGameData, nParam);
        break;
    case 0x503ac5d2:
        result = AddTribeMember(pGameData, nParam);
        break;
    case 0x6ff518e4:
        BeginSelection(pGameData, nParam);
        result = DoObjectInteraction(pGameData, nParam);
        break;
    case 0x7035d3bd:
        cCivModeStrategy::Get()->HandleCheat(pMessage);
        break;
    case 0x71d4dfc8:
        if (mpCommunityEditor) {
            if (!mpCommunityEditor->CanClose())
                result = 2;
            else
                MessageServer()->PostMessage(0xb2699149, 0, 0, 0);
        }
        break;
    case 0x902074f6:
        result = MenuOff(pGameData, nParam);
        break;
    case 0x9020a143:
        BeginSelection(pGameData, nParam);
        result = EndSelection(pGameData, nParam, CameraManager()->PickTerrain(0, g_CursorPos));
        break;
    case 0x9020a144: {
        cSpatialGameData* p = ToSpatialGameData(pGameData);
        if (p)
            cCivModeStrategy::Get()->SetCameraTrackObject(&p->mSpatial);
        break;
    }
    case 0x90651625:
        break;
    case 0xd0063856:
        result = OnKeyDown(pGameData, nParam);
        break;
    case 0xd020a136:
        result = OnKeyUp(pGameData, nParam);
        break;
    default:
        return false;
    }

    IParameterList* pResults = pMessage->GetResults();
    pResults->SetParameter(0, Variant(result));
    return false;
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
