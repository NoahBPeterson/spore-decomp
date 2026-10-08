// Slice s0101bd10: 0x0101c080, the per-frame update of the solar-system camera controller
// (caller-scored PDB candidate: SP::cSPCameraControllerSolarSystem::Update), thiscall, ret 8.
//
// Arguments: the frame time in milliseconds (clamped to 100) and the viewer to drive.
// What it does:
//   * advances the zoom/pan state with the clamped time step,
//   * derives, from the universe context (1 = planet view, 2 = system view, other = galaxy view),
//     the allowed zoom range [lo, hi] and the viewer's clip/FOV style settings,
//   * runs the little zoom state machine (member +0x88) from the current zoom (virtual slot 0x5c),
//   * picks the point the camera looks at (active planet, the player's UFO, a saved position ...),
//   * eases the look-at point and the zoom towards their targets,
//   * adds the optional "camera shake" (sine wobble, global switch 0x15b6dac) to the offsets,
//   * builds the camera-to-world matrix and hands it to the viewer.
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc); x87 mixed in for float calls.
#include "types.h"

#include <math.h>

struct Vector3 {
    float x, y, z;
};

namespace SP {

struct cViewer {
    void SetNear(float v);                       // 0x007c4ba0 (thiscall, ret 4)
    void SetFar(float v);                        // 0x007c4bc0 (thiscall, ret 4)
    void SetViewAngle(float v);                  // 0x007c5350 (thiscall, ret 4)
    void SetCameraToWorld(const float* m);       // 0x007c4c40 (thiscall, ret 4)
};

struct cSpatialObject {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual const Vector3* GetPosition();        // +0x2c
};

struct cSPGameDataUFO {
    uint32_t pad0[0x34 / 4];
    cSpatialObject mSpatial;                     // +0x34
    uint32_t pad38[(0x718 - 0x38) / 4];
    Vector3 mSavedPos;                           // +0x718
    uint32_t pad724[(0x74c - 0x724) / 4];
    bool mHasPos;                                // +0x74c
};

struct cSPSimulatorSpaceGame {
    cSPGameDataUFO* GetPlayerInventory();        // 0x00a1ad60
};

struct IStage { uint32_t pad[0x2c / 4]; int mMode; };        // b3d4d0 -> +0x2c
struct ISpaceGame { bool IsFrozen(); };                      // 0x00b18e40
struct cSpaceLocation {                                       // 0x01021230 result
    const Vector3* GetPosition();                            // 0x00c8b360 (thunk)
    bool IsKnown();                                          // 0x00c8b800 (thunk)
};

int GetUniverseContext();                        // 0x01021080
cSPSimulatorSpaceGame* GetUFOSimulator();        // 0x00ffbe50
IStage* GetStage();                              // 0x00b3d4d0
ISpaceGame* SpaceGameGet();                      // 0x01002bd0
cSpatialObject* GetActivePlanet();               // 0x01021260
cSpaceLocation* GetHomeLocation();               // 0x01021230
void ResetEffectStates();                        // 0x006f3290
// cdecl helpers
void UpdateFocus(Vector3* cur, Vector3* vel, const Vector3* target, float c1, float c1k, float dtms);  // 0x010426a0
void UpdateZoom(float* zoom, float* vel, float target, float v, float v2, float dtms);                   // 0x01042570
void OffsetFromZoom(Vector3* out, const Vector3* in);                                                    // 0x010424c0
void BuildCameraMatrix(const Vector3* target, const Vector3* eye, const Vector3* up, float* out16);      // 0x01043580

extern float gCamK3d0;   // 0x016dd3d0
extern float gCamK3b4;   // 0x016dd3b4
extern float gCamK384;   // 0x016dd384
extern float gCamK374;   // 0x016dd374
extern float gCamK43c;   // 0x016dd43c
extern float gCamK438;   // 0x016dd438
extern float gCamK434;   // 0x016dd434
extern float gCamK354;   // 0x016dd354
extern float gCamK358;   // 0x016dd358
extern float gCamK350;   // 0x016dd350
extern float gCamK34c;   // 0x016dd34c
extern float gCamK3b8;   // 0x016dd3b8
extern float gCamK3cc;   // 0x016dd3cc
extern float gCamK380;   // 0x016dd380
extern float gCamK444;   // 0x016dd444
extern float gCamK448;   // 0x016dd448
extern float gCamK44c;   // 0x016dd44c
extern float gCamK430;   // 0x016dd430
extern float gCamK424;   // 0x016dd424
extern float gCamK42c;   // 0x016dd42c
extern float gCamK420;   // 0x016dd420
extern float gCamK428;   // 0x016dd428
extern float gCamK41c;   // 0x016dd41c
extern float gCamPhase;  // 0x016dda7c
extern float gCamC1;     // 0x015b6db8
extern float gCamC2;     // 0x015b6db4
extern float gCamMinZoom; // 0x015b6db0
extern bool gCamShake;   // 0x015b6dac
extern const Vector3 kCamUp;  // 0x015b6df4

class cSPCameraControllerSolarSystem {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58();
    virtual float GetZoom();                    // +0x5c

    void Update(int ms, cViewer* viewer);       // 0x0101c080

    void FUN_0101aea0(float dt);                // ret 4
    void FUN_0101b160(float a, float b);        // ret 8
    void FUN_01017390();
    void FUN_0101a330(int ms, int zero);        // ret 8
    float FUN_01017790(bool a, bool b);         // ret 8
    void FUN_010180e0(Vector3* out, Vector3 pos, Vector3 dir, int zero);   // ret 0x20

    uint32_t pad04[(0x60 - 4) / 4];
    float mF60;                                  // 0x60
    uint32_t pad64;
    float mZoom;                                 // 0x68
    float mF6c;                                  // 0x6c
    float mF70;                                  // 0x70
    uint32_t pad74[(0x88 - 0x74) / 4];
    int mState;                                  // 0x88
    uint32_t pad8c[(0x98 - 0x8c) / 4];
    Vector3 mFocus;                              // 0x98
    Vector3 mFocusVel;                           // 0xa4
    uint32_t padB0;
    float mTargetZoom;                           // 0xb4
    float mZoomVel[2];                           // 0xb8
    uint8_t padC0[0xd7 - 0xc0];
    bool mSnapped;                               // 0xd7
};

} // namespace SP

using namespace SP;

inline int Min(const int& a, const int& b) { return (a < b) ? a : b; }
inline float MaxSS(float a, float b) { return (a > b) ? a : b; }
inline float MinSS(float a, float b) { return (a < b) ? a : b; }

// @ 0x0101c080
void SP::cSPCameraControllerSolarSystem::Update(int ms, cViewer* viewer)
{
    int ctx = GetUniverseContext();
    FUN_0101aea0((float)Min(ms, 100) * 0.001f);

    uint32_t clamped = Min(ms, 100);
    float dtms = (float)clamped;
    ms = (int)clamped;
    float dt = dtms * 0.001f;

    cSPGameDataUFO* ufo = GetUFOSimulator()->GetPlayerInventory();
    int mode = GetStage()->mMode;
    if (mode != 1 && mode != 2 && !SpaceGameGet()->IsFrozen())
        FUN_0101b160(mF60, dt);

    float zoom = GetZoom();
    float lo = 0.0f;
    if (ctx == 1)
        lo = gCamK3d0;
    else if (ctx == 2)
        lo = gCamK384;
    float hi = 0.0f;
    if (ctx == 1)
        hi = gCamK3b4;
    else if (ctx == 2)
        hi = gCamK374;
    float range[2];
    range[1] = lo;
    range[0] = hi;
    float frac = (zoom - lo) / (hi - lo);

    float nearV = gCamK43c;
    float farV = gCamK438;
    float angle = gCamK434;
    float p, q;
    if (ctx == 2) {
        p = gCamK354;
        q = gCamK358;
        angle = (p - q) * frac + q;
    } else if (ctx == 1) {
        nearV = 1.0f;
        q = gCamK350;
        p = gCamK34c;
        angle = (p - q) * frac + q;
    }
    viewer->SetNear(nearV);
    viewer->SetFar(farV);
    viewer->SetViewAngle(angle);

    float* pZoom = &mZoom;
    if (fabsf(mZoom - mTargetZoom) < 1.5258789e-05f)
        mSnapped = false;
    if (!mSnapped) {
        if (*pZoom > lo && hi > *pZoom)
            FUN_01017390();
    }
    bool follow;
    if (mSnapped) {
        if (ctx == 1) {
            if (zoom > gCamK3b8)
                mState = 3;
            else if (gCamK3cc > zoom)
                mState = 2;
        } else {
            if (gCamK380 > zoom)
                mState = 4;
        }
    } else {
        if (ctx == 2 && mState == 3)
            mState = 0;
    }
    follow = (ctx == 1) && (mState == 4 || mState == 1);

    Vector3 P;
    P.x = gCamK444;
    P.y = gCamK448;
    P.z = gCamK44c;
    if (follow) {
        cSpatialObject* planet = GetActivePlanet();
        if (planet) {
            const Vector3* pos = planet->GetPosition();
            P.x = pos->x; P.y = pos->y; P.z = pos->z;
        }
        if (!mSnapped && ufo->mHasPos) {
            float dx = mFocus.x - P.x, dy = mFocus.y - P.y, dz = mFocus.z - P.z;
            if (0.04f > dx * dx + dy * dy + dz * dz)
                mState = 0;
        }
    } else if (mState == 2) {
        const Vector3* pos = ufo->mSpatial.GetPosition();
        P.x = pos->x; P.y = pos->y; P.z = pos->z;
    } else if (!ufo->mHasPos) {
        P.x = ufo->mSavedPos.x; P.y = ufo->mSavedPos.y; P.z = ufo->mSavedPos.z;
    } else if (ctx == 2) {
        cSpaceLocation* loc = GetHomeLocation();
        if (loc) {
            const Vector3* pos = loc->GetPosition();
            P.x = pos->x; P.y = pos->y; P.z = pos->z;
        }
    } else if (ctx == 1) {
        cSpatialObject* planet = GetActivePlanet();
        if (planet) {
            const Vector3* pos = planet->GetPosition();
            P.x = pos->x; P.y = pos->y; P.z = pos->z;
        }
    }

    UpdateFocus(&mFocus, &mFocusVel, &P, gCamC1, gCamC1 * 0.001f, dtms);
    float v = FUN_01017790(mSnapped, *pZoom > mTargetZoom) * 0.001f;
    UpdateZoom(pZoom, mZoomVel, mTargetZoom, v, gCamC2 * v, dtms);

    if (!mSnapped) {
        float z = *pZoom;
        z = MaxSS(z, range[1]);
        z = MinSS(z, range[0]);
        *pZoom = z;
    }

    Vector3 t3;
    t3.x = *pZoom;
    t3.y = pZoom[1];
    t3.z = pZoom[2];
    if (ctx == 1) {
        if (!GetHomeLocation()->IsKnown() && gCamMinZoom > t3.x)
            t3.x = gCamMinZoom;
    }
    if (gCamShake) {
        gCamPhase = dt + gCamPhase;
        float w = gCamK430 * gCamPhase;
        float half = *pZoom * 0.5f;
        float s = (float)sin(w);
        t3.x = s * gCamK424 + t3.x;
        if (half > t3.x)
            t3.x = half;
        t3.y = (float)sin(gCamK42c * gCamPhase) * gCamK420 + t3.y;
        t3.z = (float)sin(gCamPhase * gCamK428) * gCamK41c + t3.z;
        if (0.01f > t3.z)
            t3.z = 0.01f;
    }

    Vector3 dir;
    OffsetFromZoom(&dir, &t3);
    FUN_0101a330(ms, 0);
    Vector3 out;
    FUN_010180e0(&out, mFocus, dir, 0);
    Vector3 target;
    target.x = out.x + dir.x;
    target.y = out.y + dir.y;
    target.z = out.z + dir.z;
    float matrix[16];
    BuildCameraMatrix(&target, &out, &kCamUp, matrix);
    viewer->SetCameraToWorld(matrix);
    ResetEffectStates();
}
