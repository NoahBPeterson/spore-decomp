// Slice s00ffe860: SP::cSPSimulatorPlayerUFO::UpdateUfoKeys (0x00ffe860, 2564 bytes).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (scalar SSE math; the aligned frame comes from the
// _mm_* clamp helper).
//
// Per-frame keyboard handling of the player UFO: bails out while paused / in menus / editors /
// comm screens, then handles the zoom keys (planet camera zoom or terrain-sphere music cue),
// the zoom UI buttons, the camera pan keys and, on a planet, the keyboard flight of the UFO
// (acceleration lerped by altitude, clamped speed, SetPlanetDestinationFromOffset) and the
// keyboard camera rotation.
//
// Member offsets are retail (dev PDB cSPSimulatorPlayerUFO shifted by +0x14 after mAutoMsg).
// Callees that only have FUN_ names are named after their use here (descriptive, not PDB).
#include "types.h"
#include <math.h>
#include <xmmintrin.h>

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4

// SSE clamp helper (inline asm in the original headers: maxss/minss against the memory params)
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

template <typename T> inline const T& Min(const T& a, const T& b) { return (b < a) ? b : a; }

inline float Lerp(float a, float b, float t) { return (b - a) * t + a; }

struct Vector3 { float x, y, z; };

// ---- engine singletons / managers ---------------------------------------------------------
struct cGameTimeManager {
    uint32_t pad00[0x48 / 4];
    uint8_t mFlags;                                           // +0x48 (bit 0: paused)
};
cGameTimeManager* GameTimeManager();                          // 0x00b3d380
bool IsGamePausedOverride();                                  // 0x00805180

struct cMenuState { bool IsActive(); };                       // 0x00a98020
cMenuState* MenuState();                                      // 0x01015df0

struct cCommunityEditor { bool IsOpen(); };                   // 0x00d09660
template <typename T> struct AutoRefCount {
    T* mpObject;
    T* operator->() const { return mpObject; }
    operator bool() const { return mpObject != 0; }
};
struct cSPSimulatorSpaceGame {
    uint32_t pad00[0x20 / 4];
    AutoRefCount<cCommunityEditor> mpCommunityEditor;         // +0x20
    void ChangeCameraByOffset(float dx, float dy);            // 0x01003c60
};
cSPSimulatorSpaceGame* SpaceGameGet();                        // 0x01002bd0

struct cTradeScreen { bool IsOpen(); };                       // 0x00e393b0
cTradeScreen* TradeScreen();                                  // 0x00b3d410

struct cAssetBrowser { uint32_t pad00[0x1c / 4]; bool mbActive; };  // +0x1c
cAssetBrowser* AssetBrowser();                                // 0x00401030

struct cCommManager { bool IsCommScreenActive(); };           // 0x00ae9390
cCommManager* CommManager();                                  // 0x00b3d4a0

struct cSpaceUI { bool IsModalOpen(int which); };             // 0x00e18c70
cSpaceUI* SpaceUI();                                          // 0x00b3d3f0

struct cTutorialManager { bool IsBlockingInput(); };          // 0x00ac80f0
cTutorialManager* TutorialManager();                          // 0x00b3d4d0

struct cSPLivingUniverse { static int GetUniverseContext(); }; // 0x01021080

struct IGameInputManager {
    PV4 PV2
    virtual bool IsTriggered(uint32_t trigger);               // +0x18
};
IGameInputManager* GameInputManager();                        // 0x00b3d250

struct cICameraController;
struct ICameraManager {
    PV8 PV4 PV2
    virtual cICameraController* GetActiveCameraController();  // +0x38
};
struct IApp {
    PV8 PV8 PV4
    virtual ICameraManager* GetCameraManager();               // +0x50
};
IApp* App();                                                  // 0x0067dd10

struct cSPSpacePlanetCameraController {
    void SetZoomVelocity(float v);                            // 0x010171e0
    float GetZoom();                                          // 0x01017220
    bool IsFollowing();                                       // 0x01017260
    void SetFollowing(bool b);                                // 0x01017270
    void Rotate(float angle);                                 // 0x010171b0
};
struct cSPCameraControllerSolarSystem;
struct cDefaultCameraController {
    PV8 PV4 PV2 PV
    virtual void Zoom(int dir, float x, float y, int z);      // +0x3c
    PV8 PV
    virtual void SetZoomedIn(bool b);                         // +0x64
};
cSPSpacePlanetCameraController* interface_cast_PlanetCam(cICameraController* p);   // 0x00c37590
cSPCameraControllerSolarSystem* interface_cast_SolarCam(cICameraController* p);    // 0x00c375b0
cDefaultCameraController* interface_cast_DefaultCam(cICameraController* p);        // 0x00fe7290

struct cPlanetControl { bool CanControl(); };                // 0x00c37170
struct cPlanetInteractor { uint32_t pad00[0x40 / 4]; cPlanetControl* mpActive; };
extern cPlanetInteractor* g_PlanetInteractor;                 // 0x016dba14

struct cTerrainSphere { void PlayMusic(uint32_t id); };       // 0x00c77bf0
struct cNounManager { cTerrainSphere* GetCurrentTerrainSphere(); }; // 0x00f67d90
cNounManager* NounManager();                                  // 0x00b3d300

struct cPlanetModel { float GetMinAltitude(); };              // 0x00b7e4d0
cPlanetModel* PlanetModel();                                  // 0x00b3d350

struct cUFOTuning {
    float GetMinSpeed();                                      // 0x00c37400
    float GetMaxSpeed();                                      // 0x00c37410
    float GetMinAccel();                                      // 0x00c37420
};
cUFOTuning* UFOTuning();                                      // 0x00c37360

struct cSpatialObject {
    PV8 PV2 PV
    virtual Vector3* GetPosition();                           // +0x2c
};
struct cSPPlayerUFOBase {
    virtual void v00();
    uint32_t pad04[(0x34 - 4) / 4];
};
struct cSPPlayerUFO : cSPPlayerUFOBase, cSpatialObject {      // cSpatialObject at +0x34
    uint32_t pad38[(0x604 - 0x38) / 4];
    float mEdgeSpin;                                          // +0x604
    float GetAltitude();                                      // 0x00c37120
};

struct cPropertyList;
bool GetFloatProperty(cPropertyList* list, uint32_t id, float& out);  // 0x0040cf10

// ---- the class --------------------------------------------------------------------------
namespace SP {
struct cSPSimulatorPlayerUFO {
    uint32_t pad00[0x14 / 4];
    bool mUIButton_ZoomIn;                                    // +0x14
    bool mUIButton_ZoomOut;                                   // +0x15
    bool mUIButton_Left;                                      // +0x16
    bool mUIButton_Right;                                     // +0x17
    uint32_t pad18[(0x40 - 0x18) / 4];
    cSPPlayerUFO* mpPlayerUFO;                                // +0x40
    uint32_t pad44[3];
    float mKeyboardVelocity;                                  // +0x50
    bool mVelocityTriggerDown;                                // +0x54
    bool mCameraRotate;                                       // +0x55
    bool mKeyboardJoystick;                                   // +0x56
    bool mAtFarZoom;                                          // +0x57
    uint32_t pad58[(0xa4 - 0x58) / 4];
    cPropertyList* mpCameraPropList;                          // +0xa4

    void SetPlanetDestination(Vector3* pos, int a, int b, int c, int d);   // 0x00ffc350
    void SetPlanetDestinationFromOffset(float x, float y, bool a, bool b, bool c, bool d, bool e);  // 0x00ffe570
    void UpdateUfoKeys(uint32_t deltaMS);
};

// @ 0x00ffe860
void cSPSimulatorPlayerUFO::UpdateUfoKeys(uint32_t deltaMS)
{
    if (!(GameTimeManager()->mFlags & 1) && !IsGamePausedOverride())
        return;
    if (MenuState()->IsActive())
        return;
    if (SpaceGameGet()->mpCommunityEditor && SpaceGameGet()->mpCommunityEditor->IsOpen())
        return;
    if (TradeScreen()->IsOpen())
        return;
    if (AssetBrowser()->mbActive)
        return;
    if (CommManager()->IsCommScreenActive())
        return;
    if (SpaceUI()->IsModalOpen(0))
        return;
    if (SpaceUI()->IsModalOpen(0))
        return;
    if (TutorialManager()->IsBlockingInput())
        return;

    bool onPlanet = cSPLivingUniverse::GetUniverseContext() == 0;
    cSPSpacePlanetCameraController* planetCam;
    if (onPlanet) {
        planetCam = interface_cast_PlanetCam(App()->GetCameraManager()->GetActiveCameraController());
        if (planetCam)
            goto haveCamera;
        return;
    }
    planetCam = 0;
    if (!interface_cast_SolarCam(App()->GetCameraManager()->GetActiveCameraController()))
        return;
haveCamera:
    cPlanetControl* pControl = g_PlanetInteractor->mpActive;
    if (pControl && !pControl->CanControl())
        return;

    float dt = (float)deltaMS;
    float dtSec = dt * 0.001f;

    if (GameInputManager()->IsTriggered(9)) {
        if (onPlanet) {
            planetCam->SetZoomVelocity(0.5f);
        } else {
            cDefaultCameraController* cam = interface_cast_DefaultCam(App()->GetCameraManager()->GetActiveCameraController());
            if (cam)
                cam->Zoom(1, 0.0f, 0.0f, 0);
            NounManager()->GetCurrentTerrainSphere()->PlayMusic(0x5638438);
        }
    }
    if (GameInputManager()->IsTriggered(0x10)) {
        if (onPlanet) {
            planetCam->SetZoomVelocity(-0.5f);
        } else {
            cDefaultCameraController* cam = interface_cast_DefaultCam(App()->GetCameraManager()->GetActiveCameraController());
            if (cam)
                cam->Zoom(-1, 0.0f, 0.0f, 0);
            NounManager()->GetCurrentTerrainSphere()->PlayMusic(0x5638439);
        }
    }

    if (mUIButton_ZoomIn || GameInputManager()->IsTriggered(0x11111111)) {
        if (mKeyboardJoystick) {
            cDefaultCameraController* cam = interface_cast_DefaultCam(App()->GetCameraManager()->GetActiveCameraController());
            if (cam) {
                cam->SetZoomedIn(false);
                mKeyboardJoystick = false;
            }
            if (!onPlanet)
                NounManager()->GetCurrentTerrainSphere()->PlayMusic(0x5638438);
        }
    } else if (mUIButton_ZoomOut || GameInputManager()->IsTriggered(0x22222222)) {
        if (mKeyboardJoystick) {
            cDefaultCameraController* cam = interface_cast_DefaultCam(App()->GetCameraManager()->GetActiveCameraController());
            if (cam) {
                cam->SetZoomedIn(true);
                mKeyboardJoystick = false;
            }
            if (!onPlanet)
                NounManager()->GetCurrentTerrainSphere()->PlayMusic(0x5638439);
        }
    } else {
        mKeyboardJoystick = true;
    }

    if (onPlanet) {
        if (!mCameraRotate && GameInputManager()->IsTriggered(3))
            mpPlayerUFO->mEdgeSpin += 1.0f;
        if (!mCameraRotate && GameInputManager()->IsTriggered(4))
            mpPlayerUFO->mEdgeSpin -= 1.0f;
        if (mUIButton_Left || GameInputManager()->IsTriggered(0x11))
            SpaceGameGet()->ChangeCameraByOffset(dt * -0.3f, 0.0f);
        if (mUIButton_Right || GameInputManager()->IsTriggered(0x12))
            SpaceGameGet()->ChangeCameraByOffset(dt * 0.3f, 0.0f);
    } else {
        if (mUIButton_Left || GameInputManager()->IsTriggered(3) || GameInputManager()->IsTriggered(0x11))
            SpaceGameGet()->ChangeCameraByOffset(dt * -0.3f, 0.0f);
        if (mUIButton_Right || GameInputManager()->IsTriggered(4) || GameInputManager()->IsTriggered(0x12))
            SpaceGameGet()->ChangeCameraByOffset(dt * 0.3f, 0.0f);
        if (GameInputManager()->IsTriggered(7) || GameInputManager()->IsTriggered(1))
            SpaceGameGet()->ChangeCameraByOffset(0.0f, dt * -0.3f);
        if (GameInputManager()->IsTriggered(8) || GameInputManager()->IsTriggered(2))
            SpaceGameGet()->ChangeCameraByOffset(0.0f, dt * 0.3f);
    }

    mUIButton_Left = false;
    mUIButton_Right = false;
    mUIButton_ZoomIn = false;
    mUIButton_ZoomOut = false;

    if (!onPlanet)
        return;

    float t;
    {
        float minAltitude = PlanetModel()->GetMinAltitude();
        float altitude = mpPlayerUFO->GetAltitude() - minAltitude;
        t = 1.0f - Clamp(altitude / (planetCam->GetZoom() - minAltitude), 0.0f, 1.0f);
    }

    int dx = 0;
    int dy = 0;
    bool vertical = false;
    bool up = false;
    bool moved = false;
    if (GameInputManager()->IsTriggered(1)) {
        moved = true;
        dy = -1;
        vertical = true;
    }
    if (GameInputManager()->IsTriggered(2)) {
        moved = true;
        dy = 1;
        vertical = true;
        up = true;
    }
    if (GameInputManager()->IsTriggered(5) || (GameInputManager()->IsTriggered(3) && mCameraRotate)) {
        moved = true;
        dx = -1;
        vertical = false;
    }
    if (GameInputManager()->IsTriggered(6) || (GameInputManager()->IsTriggered(4) && mCameraRotate)) {
        moved = true;
        dx = 1;
        vertical = false;
    }

    if ((mVelocityTriggerDown || fabsf(mpPlayerUFO->mEdgeSpin) > 1.5258789e-05f) && !moved) {
        SetPlanetDestination(mpPlayerUFO->GetPosition(), 1, 0, 1, 0);
    } else if (dx == 0 && dy == 0) {
        mKeyboardVelocity = 0.0f;
    } else {
        float minSpeed = UFOTuning()->GetMinSpeed();
        float maxSpeed = UFOTuning()->GetMaxSpeed();
        float minAccel = UFOTuning()->GetMinAccel();
        maxSpeed = Lerp(minSpeed, maxSpeed, t);
        float accel = (UFOTuning()->GetMaxSpeed() - minAccel) * t;
        mKeyboardVelocity += (accel + minAccel) * dtSec;
        if (mKeyboardVelocity > maxSpeed)
            mKeyboardVelocity = maxSpeed;
        float scale = Min(1.0f, mKeyboardVelocity * dtSec);
        bool following;
        if (planetCam->IsFollowing() && !mCameraRotate) {
            following = true;
        } else {
            following = false;
            mpPlayerUFO->mEdgeSpin = 0.0f;
            if (!GameInputManager()->IsTriggered(0xcccccccc))
                planetCam->SetFollowing(true);
        }
        SetPlanetDestinationFromOffset((float)dx * scale, (float)dy * scale, true, vertical, false, following, up);
    }
    mVelocityTriggerDown = moved;

    if (GameInputManager()->IsTriggered(7)) {
        float minRot = 1.0f;
        GetFloatProperty(mpCameraPropList, 0x195a064, minRot);
        float maxRot = 1.0f;
        GetFloatProperty(mpCameraPropList, 0x195a067, maxRot);
        float rotSpeed = Lerp(minRot, maxRot, t) * 0.05235988f;
        planetCam->Rotate(-(rotSpeed * dtSec));
    }
    if (GameInputManager()->IsTriggered(8)) {
        float minRot = 1.0f;
        GetFloatProperty(mpCameraPropList, 0x195a064, minRot);
        float maxRot = 1.0f;
        GetFloatProperty(mpCameraPropList, 0x195a067, maxRot);
        float rotSpeed = Lerp(minRot, maxRot, t) * 0.05235988f;
        planetCam->Rotate(rotSpeed * dtSec);
    }
}
} // namespace SP
