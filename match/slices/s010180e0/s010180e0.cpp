// Slice s010180e0 -- 0x010180e0: clips a point against a four-plane wedge built around a direction
// (ConeClip). thiscall, 8 stack arguments (ret 0x20), the 8th is unused by the original.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"
#include <math.h>
#pragma intrinsic(sqrt)

template <class T> inline const T &Max(const T &a, const T &b) { return (a < b) ? b : a; }
template <class T> inline const T &Min(const T &a, const T &b) { return (b < a) ? b : a; }

extern float g_016dd390;   // 0x016dd390
extern float g_016dd38c;   // 0x016dd38c

struct ConeClip {
    char  pad00[0x8c];
    float cx, cy, cz;       // +0x8c, +0x90, +0x94
    char  pad98[0xbc - 0x98];
    float mRatio;           // +0xbc

    void Clip(float *out, float px, float py, float pz, float dx, float dy, float dz, float unused);
};

// ConeClip::Clip @ 0x010180e0
void ConeClip::Clip(float *out, float px, float py, float pz, float dx, float dy, float dz, float unused)
{
    float r = mRatio;
    float t0 = 1.0f - r;
    float ey = py - cy;
    float ez = pz - cz;
    float ex = px - cx;
    out[0] = px;
    out[1] = py;
    out[2] = pz;
    if (1.0f < (ez * ez + ey * ey) + ex * ex) {
        float s3c = px - (cx + dx);
        float s38 = py - (cy + dy);
        float s34 = pz - (cz + dz);
        float s48 = px - cx;
        float s44 = py - cy;
        float s40 = pz - cz;

        float inv = 1.0f / sqrtf(dy * dy + (dz * dz + dx * dx));
        dz = inv * dz;
        dx = inv * dx;
        dy = dy * inv;
        float ny = -dy;
        inv = 1.0f / sqrtf(dx * dx + ny * ny);
        float a2c = dx * inv;
        float a28 = inv * 0.0f;
        inv = inv * ny;
        float a24 = -dz * a2c - ny * a28;
        float a20 = a28 * -dx - -dz * inv;
        float a1c = ny * inv - a2c * -dx;

        float k = r * g_016dd390;
        float a4 = dz * k + a1c;
        float ac = dx * k + a24;
        float a8 = dy * k + a20;
        float n = 1.0f / sqrtf(ac * ac + (a8 * a8 + a4 * a4));
        ac = n * ac;
        a8 = a8 * n;
        a4 = a4 * n;
        a1c = dz * k - a1c;
        a24 = dx * k - a24;
        a20 = dy * k - a20;
        n = 1.0f / sqrtf(a24 * a24 + (a20 * a20 + a1c * a1c));
        a24 = n * a24;
        a20 = a20 * n;
        a1c = a1c * n;

        k = r * g_016dd38c;
        float a18 = dx * k + inv;
        float a10 = dz * k + a28;
        float a14 = dy * k + a2c;
        n = 1.0f / sqrtf(a14 * a14 + (a10 * a10 + a18 * a18));
        a10 = a10 * n;
        a14 = a14 * n;
        float f2 = dx * k - inv;
        a28 = dz * k - a28;
        a2c = dy * k - a2c;
        float n2 = 1.0f / sqrtf(a2c * a2c + (a28 * a28 + f2 * f2));

        float t = (ac * s3c + a4 * s34) + a8 * s38;
        if (0.0f < t)
            t0 = Max(t0, t / ((ac * s48 + a4 * s40) + a8 * s44));
        t = (a24 * s3c + a1c * s34) + a20 * s38;
        if (0.0f < t)
            t0 = Max(t0, t / ((a24 * s48 + a1c * s40) + a20 * s44));
        t = ((n * a18) * s3c + a10 * s34) + a14 * s38;
        if (0.0f < t)
            t0 = Max(t0, t / (((n * a18) * s48 + a10 * s40) + a14 * s44));
        t = ((a28 * n2) * s34 + (a2c * n2) * s38) + (n2 * f2) * s3c;
        if (0.0f < t)
            t0 = Max(t0, t / (((a28 * n2) * s40 + (a2c * n2) * s44) + (n2 * f2) * s48));

        float f = Min(t0, 1.0f);
        float oy = cy, oz = cz;
        out[0] = cx + (px - cx) * f;
        out[1] = oy + (py - oy) * f;
        out[2] = oz + (pz - oz) * f;
    }
}

// ---------------------------------------------------------------- planet camera
namespace SP {

struct Vector3 { float x, y, z; };

// Camera rig hung off the player inventory at +0x34.
class cInventoryCamera {
 public:
  virtual void pv00(); virtual void pv01(); virtual void pv02(); virtual void pv03();
  virtual void pv04(); virtual void pv05(); virtual void pv06(); virtual void pv07();
  virtual void pv08(); virtual void pv09(); virtual void pv10();
  virtual Vector3* GetPosition();   // +0x2c
};

class cPlayerInventory {
 public:
  char pad00[0x34];
  cInventoryCamera mCamera;         // +0x34
  char pad38[0x74c - 0x38];
  bool mbCameraOverride;            // +0x74c
  char pad74d[0x750 - 0x74d];
  Vector3 mCameraOverridePos;       // +0x750
};

class cSPSimulatorSpaceGame {
 public:
  cPlayerInventory* GetPlayerInventory();   // 0x00a1ad60
};

cSPSimulatorSpaceGame* GetUFOSimulator();   // 0x00ffbe50

// Game clock; bit 0 of the flags at +0x48 pauses the scripted camera.
class cGameTimeManager {
 public:
  char pad00[0x48];
  uint32_t mnFlags;                 // +0x48
};
cGameTimeManager* GameTimeManager();   // 0x00b3d380

class cSPSpacePlanetCameraController {
 public:
  float GetCurrentZoom();           // 0x010187c0
};

// @ 0x010187c0
// Distance of the planet camera from the inventory's camera anchor (or from the scripted
// override position while the game clock is running).
float cSPSpacePlanetCameraController::GetCurrentZoom()
{
  cPlayerInventory* pInventory = GetUFOSimulator()->GetPlayerInventory();
  const Vector3* pPos;
  if (pInventory->mbCameraOverride && (GameTimeManager()->mnFlags & 1) == 0) {
    pPos = &pInventory->mCameraOverridePos;
  } else {
    pPos = pInventory->mCamera.GetPosition();
  }
  return sqrtf(pPos->x * pPos->x + pPos->y * pPos->y + pPos->z * pPos->z);
}

}  // namespace SP
