// Slice s01019f50 -- 0x0101a330 (1638 bytes): per-frame interpolation of a solar-system style camera
// controller (PDB candidate cSPCameraControllerSolarSystem::Interpolate; the retail layout is different,
// members are named by retail offset).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc), x87 fmod, SSE scalar arithmetic.
//
// Argument: elapsed time in milliseconds as a 64-bit unsigned (the fild-pair conversion).
// Flow: pick the zoom range for the universe context, rescale the zoom velocity (+0x80) when the zoom
// range switched, derive the pitch/height from the zoom, then, while the context-switch interpolation
// timer (+0xd0) runs, blend yaw (+0x6c) and pitch (+0x70) from start to target values over 1 second
// (smoothstep) taking the short way round, else send the "interpolation done" message once. In the
// solar-system context (2) the scene's global transform is additionally spun about the world up axis.
// Finally wrap the yaw to (-pi, pi), remember the zoom and store the normalised zoom fraction (+0xbc).
#include "types.h"

#include <math.h>
#pragma intrinsic(fmod)

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};

struct M33 {                                        // plain rw::math::Matrix33 storage
    Vector3 row[3];
    M33 operator*(const M33& b) const               // inlined rw::math::Matrix33 product
    {
        M33 r;
        for (int i = 0; i < 3; ++i) {
            const Vector3& a = row[i];
            r.row[i].x = a.x * b.row[0].x + a.y * b.row[1].x + a.z * b.row[2].x;
            r.row[i].y = a.x * b.row[0].y + a.y * b.row[1].y + a.z * b.row[2].y;
            r.row[i].z = a.x * b.row[0].z + a.y * b.row[1].z + a.z * b.row[2].z;
        }
        return r;
    }
};
struct Matrix3 : M33 {
    Matrix3() {}
    Matrix3& operator=(const Matrix3& m);           // 0x0041cb40 (out of line, thiscall ret 4)
};

// Math::Transform (ModAPI): flags, stamp, offset, scale, rotation; default = identity.
extern Vector3 gZeroOffset;     // 0x016dda64
extern Matrix3 gIdentity;       // 0x016dda40
struct Transform {
    int16_t mnFlags;
    int16_t mnTransformCount;
    Vector3 mOffset;
    float   mfScale;
    Matrix3 mRotation;
    Transform() : mnFlags(0), mnTransformCount(0), mOffset(gZeroOffset), mfScale(1.0f) { mRotation = gIdentity; }
};

Matrix3* MakeRotation(Matrix3* out, const Vector3* axis, float angle);   // 0x00453b20 (cdecl, sret)

extern const Vector3 kWorldUp;        // 0x015b6df4
extern float gZoomMinCtx1;            // 0x016dd3d0
extern float gZoomMinCtx2;            // 0x016dd384
extern float gZoomMaxCtx1;            // 0x016dd3b4
extern float gZoomMaxCtx2;            // 0x016dd374
extern float gTwoPi;                  // 0x016dda3c
extern const float kInterpDuration;   // 0x015b6d90 (1.0)
extern const float kPi;               // 0x015b6dd8
extern const float kHalfPi;           // 0x015b6dd4
extern const float kTwoPiConst;       // 0x015b6dc8

__forceinline float Clamp(float x, float lo, float hi)
{
    __asm {
        movss xmm0, x
        maxss xmm0, lo
        minss xmm0, hi
        movss x, xmm0
    }
    return x;
}

namespace SP {

struct cSPLivingUniverse {
    static int GetUniverseContext();                // 0x01021080
};

struct IMessageServer {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void PostMessage(uint32_t id, int a, int b);   // +0x14
};
IMessageServer* MessageServer();                    // 0x0067dcc0

struct ITransformHost {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14();
    virtual void SetTransform(const Transform* t);  // +0x18
    virtual void v1c();
    virtual void GetTransform(Transform* t);        // +0x20
};
struct cSceneRoot {                                 // singleton at 0x00b3d470
    uint32_t pad00[0x2c / 4];
    ITransformHost* mpTransformHost;                // +0x2c
};
cSceneRoot* GetSceneRoot();                         // 0x00b3d470

class cSolarCameraController {
public:
    void Interpolate(unsigned __int64 deltaMs);     // 0x0101a330

    float GetBaseHeight(int ctx, float zoom);       // 0x010175b0 (thiscall, ret 8, this unused)
    float GetSpinRate(float zoom);                  // 0x01017410 (thiscall, ret 4)

    uint32_t pad00[0x68 / 4];
    float    mZoom;            // +0x68
    float    mYaw;             // +0x6c
    float    mPitch;           // +0x70
    uint32_t pad74[(0x80 - 0x74) / 4];
    float    mZoomScale;       // +0x80
    uint32_t pad84[(0xb0 - 0x84) / 4];
    float    mLastZoom;        // +0xb0
    uint32_t padb4[(0xbc - 0xb4) / 4];
    float    mZoomFraction;    // +0xbc
    float    mStartPitch;      // +0xc0
    float    mTargetPitch;     // +0xc4
    float    mStartYaw;        // +0xc8
    float    mTargetYaw;       // +0xcc
    float    mInterpTimer;     // +0xd0
    bool     mSendDoneMsg;     // +0xd4
};

} // namespace SP

using namespace SP;

// @ 0x0101a330
void SP::cSolarCameraController::Interpolate(unsigned __int64 deltaMs)
{
    float ms = (float)deltaMs;
    float seconds = ms * 0.001f;

    int ctx = cSPLivingUniverse::GetUniverseContext();

    float zoomMin = 0.0f;
    if (ctx == 1)
        zoomMin = gZoomMinCtx1;
    else if (ctx == 2)
        zoomMin = gZoomMinCtx2;
    float zoomMax = 0.0f;
    if (ctx == 1)
        zoomMax = gZoomMaxCtx1;
    else if (ctx == 2)
        zoomMax = gZoomMaxCtx2;

    float zoom = mZoom;
    float lastZoom = mLastZoom;
    float ref = (zoom > lastZoom) ? zoomMax : zoomMin;
    if (lastZoom != ref)
        mZoomScale = ((zoom - ref) * mZoomScale) / (lastZoom - ref);

    float base = GetBaseHeight(ctx, zoom);
    float maxPitch = kHalfPi;
    if (ctx == 2)
        maxPitch = kPi * 0.75f;
    mPitch = Clamp(mZoomScale + base, 0.1f, maxPitch);

    if (kInterpDuration > mInterpTimer) {
        mInterpTimer = mInterpTimer + seconds;
        float t = Clamp(mInterpTimer, 0.0f, kInterpDuration);
        float oldYaw = mStartYaw;
        t = t / kInterpDuration;
        float ease = (3.0f - t * 2.0f) * t * t;

        float dy = (float)fmod(mTargetYaw - mStartYaw, gTwoPi);
        if (dy > kPi)
            dy = dy - gTwoPi;
        else if (dy < -kPi)
            dy = dy + gTwoPi;
        mYaw = dy * ease + oldYaw;

        float oldPitch = mStartPitch;
        float dp = (float)fmod(mTargetPitch - mStartPitch, gTwoPi);
        if (dp > kPi)
            dp = dp - gTwoPi;
        else if (dp < -kPi)
            dp = dp + gTwoPi;
        mPitch = dp * ease + oldPitch;
        mZoomScale = mPitch - base;
    } else if (mSendDoneMsg) {
        mSendDoneMsg = false;
        MessageServer()->PostMessage(0x580d038, 0, 0);
    }

    if (ctx == 2) {
        float spin = GetSpinRate(zoom) * ms;
        mYaw = mYaw + spin;

        Transform t;
        GetSceneRoot()->mpTransformHost->GetTransform(&t);
        Matrix3 rot;
        {
            Matrix3 tmp;
            rot = *MakeRotation(&tmp, &kWorldUp, spin);
        }
        static_cast<M33&>(t.mRotation) = t.mRotation * rot;
        t.mnFlags |= 2;
        t.mnTransformCount++;
        GetSceneRoot()->mpTransformHost->SetTransform(&t);
    }

    float yaw = (float)fmod(mYaw, kTwoPiConst);
    if (yaw >= 3.1415927f)
        yaw = yaw - kTwoPiConst;
    mYaw = yaw;
    mLastZoom = zoom;
    mZoomFraction = Clamp((mZoom - zoomMin) / (zoomMax - zoomMin), 0.0f, 1.0f);
}
