// Slice s00f51680: SP::cGameCameraController::MoveCamera(yaw, pitch, zoom, deltaTime) @ 0x00F51680.
// (PDB caller-scored candidate: SP::cTerrainCameraController::MoveCamera; the class layout is the one
// recovered for cGameCameraController in slice s00f502b0, retail offsets.)
//
// Applies one frame of camera input: the yaw/pitch deltas, the keyboard movement/zoom/rotate keys
// (accelerating over kKeyboardAccelerationTime), the alt-zoom mode, the camera tuning variables, mouse
// or edge scrolling, and finally moves the camera anchor across the planet surface (with a short coast
// after scrolling stops).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <math.h>

// ---- math ----------------------------------------------------------------
struct cSPVector3 {
    float x, y, z;
    cSPVector3() {}
    cSPVector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    bool operator==(const cSPVector3& b) const { return x == b.x && y == b.y && z == b.z; }
    cSPVector3& operator*=(float s) { x *= s; y *= s; z *= s; return *this; }
};
static inline cSPVector3 operator-(const cSPVector3& a, const cSPVector3& b)
{
    cSPVector3 r; r.x = a.x - b.x; r.y = a.y - b.y; r.z = a.z - b.z; return r;
}
struct cSPQuaternion {
    float x, y, z, w;
    cSPQuaternion() {}
    cSPQuaternion(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
    cSPQuaternion& operator*=(float s) { x *= s; y *= s; z *= s; w *= s; return *this; }
};
cSPQuaternion operator*(const cSPQuaternion& a, const cSPQuaternion& b);   // 0x007dcb00
cSPVector3 operator*(const cSPVector3& v, const cSPQuaternion& q);        // 0x0059aed0 (rotate)

static inline cSPQuaternion AxisAngle(const cSPVector3& axis, float angle)
{
    float h = angle * 0.5f;
    float s = sinf(h);
    return cSPQuaternion(s * axis.x, s * axis.y, s * axis.z, cosf(h));
}

// maxss/minss helper of this module
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

namespace eastl {
template <class T> inline const T& max(const T& a, const T& b) { return (a < b) ? b : a; }
}

namespace SP {
cSPVector3 normalized_safe(const cSPVector3& v);                          // 0x00449c20
}

// ---- engine -----------------------------------------------------------------
struct VarMap { float GetVar(const char* name); };                         // 0x007f2590
extern VarMap gCameraVars;                                                 // 0x016c90d8

float KeyboardRamp(float start, float accelerationTime, float time);      // 0x00b0f060

struct IntRect { int left, top, right, bottom; };
struct IWindow {
    IntRect GetRealArea();                                                 // 0x007c4010
};
struct IWindowHolder { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
                       virtual void v4(); virtual void v5(); virtual void v6();
                       virtual IWindow* GetMainWindow(); };                // +0x1c
struct cAppSystem {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38();
    virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual IWindowHolder* GetWindowManager();                             // +0x50
};
struct MouseState { int pad0, pad4; int mX; int mY; };
struct ICursorSource { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
                       virtual void v4(); virtual void v5(); virtual void v6();
                       virtual MouseState* GetMouseState(); };             // +0x1c
struct cCanvas {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38();
    virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50();
    virtual bool IsActive();                                               // +0x54
};
struct IWinProcHost { };
struct IWindowManager2 {
    virtual void v0();
};
cAppSystem* SP_App();                                                      // 0x0067dd10
ICursorSource* SP_CursorSource();                                          // 0x0067dd50
cCanvas* SP_Canvas();                                                      // 0x0067dcf0

namespace EA { namespace UTFWin {
struct IWindowMgr {
    virtual void v000();
    virtual struct IMainWindow* GetMainWindow();                           // +0x04
};
struct IMainWindow {
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03(); virtual void s04();
    virtual void s05(); virtual void s06(); virtual void s07(); virtual void s08(); virtual void s09();
    virtual void s0a(); virtual void s0b(); virtual void s0c(); virtual void s0d(); virtual void s0e();
    virtual void s0f(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13();
    virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18();
    virtual void s19(); virtual void s1a(); virtual void s1b(); virtual void s1c(); virtual void s1d();
    virtual void s1e(); virtual void s1f(); virtual void s20(); virtual void s21(); virtual void s22();
    virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
    virtual void s28(); virtual void s29(); virtual void s2a(); virtual void s2b(); virtual void s2c();
    virtual void s2d(); virtual void s2e(); virtual void s2f(); virtual void s30(); virtual void s31();
    virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35(); virtual void s36();
    virtual void s37(); virtual void s38(); virtual void s39(); virtual void s3a(); virtual void s3b();
    virtual void s3c(); virtual void s3d(); virtual void s3e();
    virtual bool IsMouseInside(int flags);                                 // +0xfc
};
IWindowMgr* GetManager();                                                  // 0x00957f30
}}

namespace SP {

struct cTerrainMapSet { float GetHeightAt(const cSPVector3& pos); };       // 0x00f927c0
struct cTerrainSphere {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual cTerrainMapSet* GetTerrain();                                  // +0xc
    float GetWaterHeight();                                                // 0x00f987f0
    cSPQuaternion BuildSurfaceOrientation(const cSPVector3& dir, const cSPQuaternion& ref);  // 0x00f9c960
};
cTerrainSphere* GetActivePlanetModel();                                    // 0x00f48aa0

extern bool gCameraHasFocus;                                               // 0x016c91cd
extern cSPVector3 gYawAxis;                                                // 0x016c9198
extern float kAnchorCoastFactor;                                           // 0x015b0a88 (= 0.15f)
extern float kAnchorStopTime;                                              // 0x015b0a84 (= 0.2f)
struct ScrollDelta { int x, y; };
extern ScrollDelta gScrollDelta;                                           // 0x016c9050

struct cLocalInputState {
    uint32_t mKeys[8];          // +0x00
    uint32_t mModifiers;        // +0x20
    uint32_t mRest[9];          // +0x24
    bool IsKeyDown(uint32_t vk) const { return ((mKeys[vk >> 5] >> (vk & 0x1f)) & 1) != 0; }
};

class cGameCameraController
{
public:
    template <class T> struct cInterpolationData
    {
        bool targetChanged;    // +0
        bool targetMoving;     // +1
        float currentTime;     // +4
        float targetTime;      // +8
        T start;
        T current;
        T end;
        T target;
        T velocity;
        T targetVelocity;

        __forceinline void SetTarget(const T& value)
        {
            if (!(value == target)) {
                target = value;
                start = current;
                targetChanged = true;
            }
        }
        __forceinline void UpdateTarget(float time)
        {
            targetTime = time;
            targetVelocity *= 0.0f;
            end = target;
            currentTime = 0.0f;
            targetChanged = false;
        }
        void SetTarget(const T& value, bool snap);                         // 0x00f4ff00 (quaternion)
    };

    void MoveCamera(float yaw, float pitch, float zoom, float deltaTime);
    void ApplyMotion(float dx, float dy, float zoom, float rotate, float deltaTime);   // 0x00f4f000
    const cSPVector3& GetAnchorPosition();                                 // 0x00f4faa0

    uint32_t mBase[4];                                          // cICameraController + RefCountTemplate
    bool mDoEdgeScroll;                                         // +0x10
    bool mMouseScrollIsActive;                                  // +0x11
    bool mKeyboardZoomed;                                       // +0x12
    bool mUIZoomIn;                                             // +0x13
    bool mUIZoomOut;                                            // +0x14
    bool mUIRotateR;                                            // +0x15
    bool mUIRotateL;                                            // +0x16
    cInterpolationData<float> mCameraAnchorRadius;              // +0x18
    cInterpolationData<cSPVector3> mCameraAnchorDirection;      // +0x3c
    cInterpolationData<cSPQuaternion> mCameraAnchorOrientation; // +0x90
    cInterpolationData<float> mCameraDistance;                  // +0xfc
    cInterpolationData<float> mCameraPitch;                     // +0x120
    cInterpolationData<float> mCameraYaw;                       // +0x144
    bool mBallisticMotion;                                      // +0x168
    bool mAltZoomMode;                                          // +0x169
    uint32_t mSplines[0x3c];                                    // +0x16c (4 splines, 0x3c each)
    float mLastDeltaTime;                                       // +0x25c
    float mLastZoomEffort;                                      // +0x260
    float mPreRotateAndTimes[10];                               // +0x264
    float mPlayerPreferredTheta;                                // +0x28c
    float mPlayerPreferredPhi;                                  // +0x290
    float mPlayerPreferredDistance;                             // +0x294
    float mMouseRotateSensitivityX;                             // +0x298
    float mMouseRotateSensitivityY;                             // +0x29c
    float mMouseWheelSensitivityZ;                              // +0x2a0
    float mMouseScrollSensitivity;                              // +0x2a4
    float mEdgeScrollSensitivity;                               // +0x2a8
    float mMinCameraPhi;                                        // +0x2ac
    float mMaxCameraPhi;                                        // +0x2b0
    float mMinCameraHeight;                                     // +0x2b4
    uint32_t mPad2b8[(0x308 - 0x2b8) / 4];                      // scratch vars, camera transform
    uint32_t mCameraZoomProgramID;                              // +0x308
    uint32_t mPad30c[(0x31c - 0x30c) / 4];
    cLocalInputState mLocalInputState;                          // +0x31c
    bool mbEnableKeyboardCameraControls;                        // +0x364
    bool mbEnableCollision;                                     // +0x365
    float kKeyboardAccelerationTime;                            // +0x368
    float kKeyboardTranslationSpeed;                            // +0x36c
    float kKeyboardRotationSpeed;                               // +0x370
};

template <> void cGameCameraController::cInterpolationData<cSPQuaternion>::UpdateTarget(float time);   // 0x00b10de0

enum {
    kVK_Control = 0x11, kVK_Left = 0x25, kVK_Up = 0x26, kVK_Right = 0x27, kVK_Down = 0x28,
    kVK_A = 0x41, kVK_D = 0x44, kVK_S = 0x53, kVK_W = 0x57,
    kVK_Numpad2 = 0x62, kVK_Numpad4 = 0x64, kVK_Numpad6 = 0x66, kVK_Numpad8 = 0x68,
    kVK_Add = 0x6b, kVK_Subtract = 0x6d,
    kVK_OemPlus = 0xbb, kVK_OemComma = 0xbc, kVK_OemMinus = 0xbd, kVK_OemPeriod = 0xbe,
};

#define kDegToRad 0.017453292f
#define kEpsilon 1.5258789e-05f

// @ 0x00f51680
void cGameCameraController::MoveCamera(float yaw, float pitch, float zoom, float deltaTime)
{
    static float sForwardTime;
    static float sBackwardTime;
    static float sRightTime;
    static float sLeftTime;
    static float sRotateRightTime;
    static float sRotateLeftTime;
    static bool  sScrolling;
    static float sLastDx;
    static float sLastDy;

    float dy = 0.0f;
    float dx = 0.0f;

    if (fabsf(yaw) > 0.0f)
        mCameraYaw.SetTarget(mCameraYaw.target + yaw);
    if (fabsf(pitch) > 0.0f)
        mCameraPitch.SetTarget(Clamp(mCameraPitch.target + pitch, mMinCameraPhi, mMaxCameraPhi));

    if (mLocalInputState.IsKeyDown(kVK_Control))
        return;
    if (mCameraZoomProgramID == 0 || mBallisticMotion) {
        gScrollDelta.x = 0;
        gScrollDelta.y = 0;
        return;
    }

    float rotate = 0.0f;
    if (mLocalInputState.mModifiers == 0) {
        if (mbEnableKeyboardCameraControls &&
            (mLocalInputState.IsKeyDown(kVK_Numpad8) || mLocalInputState.IsKeyDown(kVK_W) ||
             mLocalInputState.IsKeyDown(kVK_Up))) {
            sForwardTime += deltaTime;
            dy = -(KeyboardRamp(0.0f, kKeyboardAccelerationTime, sForwardTime) * kKeyboardTranslationSpeed);
        } else {
            sForwardTime = 0.0f;
        }
        if (mbEnableKeyboardCameraControls &&
            (mLocalInputState.IsKeyDown(kVK_Numpad2) || mLocalInputState.IsKeyDown(kVK_S) ||
             mLocalInputState.IsKeyDown(kVK_Down))) {
            sBackwardTime += deltaTime;
            dy += KeyboardRamp(0.0f, kKeyboardAccelerationTime, sBackwardTime) * kKeyboardTranslationSpeed;
        } else {
            sBackwardTime = 0.0f;
        }
        if (mbEnableKeyboardCameraControls &&
            (mLocalInputState.IsKeyDown(kVK_Numpad6) || mLocalInputState.IsKeyDown(kVK_D) ||
             mLocalInputState.IsKeyDown(kVK_Right))) {
            sRightTime += deltaTime;
            dx = -(KeyboardRamp(0.0f, kKeyboardAccelerationTime, sRightTime) * kKeyboardTranslationSpeed);
        } else {
            sRightTime = 0.0f;
        }
        if (mbEnableKeyboardCameraControls &&
            (mLocalInputState.IsKeyDown(kVK_Numpad4) || mLocalInputState.IsKeyDown(kVK_A) ||
             mLocalInputState.IsKeyDown(kVK_Left))) {
            sLeftTime += deltaTime;
            dx += KeyboardRamp(0.0f, kKeyboardAccelerationTime, sLeftTime) * kKeyboardTranslationSpeed;
        } else {
            sLeftTime = 0.0f;
        }
        if (mUIZoomIn || (mbEnableKeyboardCameraControls &&
                          (mLocalInputState.IsKeyDown(kVK_Add) || mLocalInputState.IsKeyDown(kVK_OemPlus)))) {
            zoom = mMouseWheelSensitivityZ;
            mKeyboardZoomed = true;
        }
        if (mUIZoomOut || (mbEnableKeyboardCameraControls &&
                           (mLocalInputState.IsKeyDown(kVK_Subtract) || mLocalInputState.IsKeyDown(kVK_OemMinus)))) {
            zoom = -mMouseWheelSensitivityZ;
            mKeyboardZoomed = true;
        }
    }

    if (mUIRotateR || (mbEnableKeyboardCameraControls &&
                       ((mLocalInputState.mModifiers == 0 && mLocalInputState.IsKeyDown(kVK_OemPeriod)) ||
                        (mLocalInputState.mModifiers == 1 && mLocalInputState.IsKeyDown(kVK_Right))))) {
        sRotateRightTime += deltaTime;
        rotate = KeyboardRamp(0.0f, kKeyboardAccelerationTime, sRotateRightTime) * kKeyboardRotationSpeed;
    } else {
        sRotateRightTime = 0.0f;
    }
    if (mUIRotateL || (mbEnableKeyboardCameraControls &&
                       ((mLocalInputState.mModifiers == 0 && mLocalInputState.IsKeyDown(kVK_OemComma)) ||
                        (mLocalInputState.mModifiers == 1 && mLocalInputState.IsKeyDown(kVK_Left))))) {
        sRotateLeftTime += deltaTime;
        rotate -= KeyboardRamp(0.0f, kKeyboardAccelerationTime, sRotateLeftTime) * kKeyboardRotationSpeed;
    } else {
        sRotateLeftTime = 0.0f;
    }

    // Alt-zoom: zooming in past the threshold twice in a row switches to the alternate zoom mode.
    float altZoomThreshold = gCameraVars.GetVar("alt_zoom_threshold");
    if (mLastZoomEffort > 0.0f)
        mLastZoomEffort = eastl::max(mLastZoomEffort - deltaTime, 0.0f);
    if (zoom > 0.0f && !mAltZoomMode && mCameraDistance.current <= altZoomThreshold) {
        if (mLastZoomEffort == 0.0f) {
            mAltZoomMode = true;
            mLastZoomEffort = -1.0f;
        } else if (mLastZoomEffort < 0.0f) {
            mLastZoomEffort = gCameraVars.GetVar("alt_zoom_timer");
        }
    }
    if (zoom < 0.0f && mAltZoomMode && mCameraDistance.current >= altZoomThreshold)
        mAltZoomMode = false;

    ApplyMotion(dx, dy, zoom, rotate, deltaTime);

    // Tuning variables.
    dx = gCameraVars.GetVar("keyboard_scroll_x");
    dy = gCameraVars.GetVar("keyboard_scroll_y");
    mMouseRotateSensitivityX = gCameraVars.GetVar("mouse_rotate_sensitivity_x") * kDegToRad;
    mMouseRotateSensitivityY = gCameraVars.GetVar("mouse_rotate_sensitivity_y") * 0.13962634f;
    mMouseScrollSensitivity = gCameraVars.GetVar("mouse_scroll_sensitivity");

    float distance = eastl::max(0.1f, gCameraVars.GetVar("distance"));
    if (fabsf(mCameraDistance.target - distance) > kEpsilon)
        mCameraDistance.SetTarget(distance);

    mMinCameraHeight = eastl::max(0.1f, gCameraVars.GetVar("min_height"));
    mMaxCameraPhi = gCameraVars.GetVar("max_pitch") * kDegToRad;
    mMinCameraPhi = gCameraVars.GetVar("min_pitch") * kDegToRad;
    float newPitch = Clamp(gCameraVars.GetVar("pitch") * kDegToRad, mMinCameraPhi, mMaxCameraPhi);
    if (fabsf(mCameraPitch.target - newPitch) > kEpsilon)
        mCameraPitch.SetTarget(newPitch);

    if (mMouseScrollIsActive) {
        IntRect area = SP_App()->GetWindowManager()->GetMainWindow()->GetRealArea();
        int centerX = (area.left + area.right) / 2;
        int centerY = (area.top + area.bottom) / 2;
        MouseState* mouse = SP_CursorSource()->GetMouseState();
        float fx = (float)(mouse->mX - centerX) / centerX;
        float fy = (float)(mouse->mY - centerY) / centerY;
        dx += fabsf(fx) * mMouseScrollSensitivity * fx;
        dy -= fy * (fabsf(fy) * mMouseScrollSensitivity);
    } else {
        bool hasFocus = gCameraHasFocus || SP_Canvas()->IsActive();
        if (mDoEdgeScroll && hasFocus &&
            EA::UTFWin::GetManager()->GetMainWindow()->IsMouseInside(1)) {
            float newYaw = gCameraVars.GetVar("yaw") * kDegToRad;
            if (fabsf(mCameraYaw.target - newYaw) > 0.0f)
                mCameraYaw.SetTarget(newYaw);
            float anchorDx = -gCameraVars.GetVar("anchor_delta_x");
            float anchorDy = -gCameraVars.GetVar("anchor_delta_y");
            if (anchorDx != 0.0f || anchorDy != 0.0f) {
                dx = mEdgeScrollSensitivity * anchorDx * deltaTime + dx;
                dy = dy - mEdgeScrollSensitivity * anchorDy * deltaTime;
            }
        }
    }

    float keyboardRotate = gCameraVars.GetVar("keyboard_rotate") * kDegToRad;
    if (fabsf(keyboardRotate) > 0.0f)
        mCameraYaw.SetTarget(mCameraYaw.target + keyboardRotate);

    // Scrolling: keep coasting for one frame after the input stops.
    bool stopped = false;
    if (dx == 0.0f && dy == 0.0f) {
        if (sScrolling)
            stopped = true;
        sScrolling = false;
    } else {
        sScrolling = true;
    }
    if (stopped) {
        dx = sLastDx * kAnchorCoastFactor;
        dy = sLastDy * kAnchorCoastFactor;
    }
    if (sScrolling || stopped) {
        sLastDy = dy;
        sLastDx = dx;
        cSPVector3 move(-dx, -dy, 0.0f);
        cSPQuaternion yawRotation = AxisAngle(gYawAxis, mCameraYaw.current);
        cSPVector3 offset = move * (mCameraAnchorOrientation.current * yawRotation);
        cSPVector3 direction = SP::normalized_safe(GetAnchorPosition() - offset);
        mCameraAnchorDirection.SetTarget(direction);

        cTerrainSphere* planet = GetActivePlanetModel();
        if (planet) {
            float ground = planet->GetTerrain()->GetHeightAt(direction);
            float water = planet->GetWaterHeight();
            mCameraAnchorRadius.SetTarget(mMinCameraHeight + eastl::max(ground, water));
            mCameraAnchorOrientation.SetTarget(
                planet->BuildSurfaceOrientation(direction, mCameraAnchorOrientation.current), false);
        }
        if (stopped) {
            mCameraAnchorDirection.UpdateTarget(kAnchorStopTime);
            mCameraAnchorRadius.UpdateTarget(kAnchorStopTime);
            mCameraAnchorOrientation.UpdateTarget(kAnchorStopTime);
        }
    }
    gScrollDelta.x = 0;
    gScrollDelta.y = 0;
}

}   // namespace SP
